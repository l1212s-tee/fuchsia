// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

use {
    fidl_fuchsia_wlan_mlme as fidl_mlme,
    std::convert::TryInto,
    wlan_common::{
        channel::Channel,
        ie::{
            intersect::*, parse_ht_capabilities, parse_vht_capabilities, HtCapabilities,
            SupportedRate, VhtCapabilities,
        },
        mac::CapabilityInfo,
    },
    zerocopy::AsBytes,
};

/// Capabilities that takes the iface device's capabilities based on the channel a client is trying
/// to join, the PHY parameters that is overridden by user's command line input and the BSS the
/// client are is trying to join.
/// They are stored in the form of IEs because at some point they will be transmitted in
/// (Re)Association Request and (Re)Association Response frames.
#[derive(Debug, PartialEq)]
pub struct JoinCapabilities {
    pub channel: Channel,
    pub cap_info: CapabilityInfo,
    pub rates: Vec<SupportedRate>,
    pub ht_cap: Option<HtCapabilities>,
    pub vht_cap: Option<VhtCapabilities>,
}

#[derive(Debug, PartialEq)]
pub struct PeerCapabilities {
    pub cap_info: CapabilityInfo,
    pub rates: Vec<SupportedRate>,
    pub ht_cap: Option<HtCapabilities>,
    pub vht_cap: Option<VhtCapabilities>,
}

// Performs capability negotiation between us as a client and an AP.
pub fn intersect_with_ap(
    client: &JoinCapabilities,
    ap: PeerCapabilities,
) -> Option<JoinCapabilities> {
    // Safe to unwrap. intersect_rates must have succeeded before we initiate the association.
    // TODO(eyw): This will be changed to return an Error in a later patch where we handle
    // Association Response frames in Rust instead of C++
    let rates =
        intersect_rates(ApRates(&ap.rates[..]), ClientRates(&client.rates[..])).unwrap_or(vec![]);
    Some(JoinCapabilities { rates, ..intersect(client, &ap) })
}

// Performs capability negotiation between us as an AP and a remote client.
#[allow(unused)]
pub fn intersect_with_remote_client(
    ap: &JoinCapabilities,
    remote_client: PeerCapabilities,
) -> Option<JoinCapabilities> {
    // Safe to unwrap. Otherwise we would have rejected the association from this remote client.
    let rates =
        intersect_rates(ApRates(&ap.rates[..]), ClientRates(&remote_client.rates[..])).ok()?;
    Some(JoinCapabilities { rates, ..intersect(ap, &remote_client) })
}

fn intersect(ours: &JoinCapabilities, theirs: &PeerCapabilities) -> JoinCapabilities {
    // Every bit is a boolean so bit-wise and is sufficient
    let cap_info = CapabilityInfo(ours.cap_info.raw() & theirs.cap_info.raw());
    let ht_cap = match (ours.ht_cap, theirs.ht_cap) {
        // Intersect is NOT necessarily symmetrical. Our own capabilities prevails.
        (Some(ours), Some(theirs)) => Some(ours.intersect(&theirs)),
        _ => None,
    };
    let vht_cap = match (ours.vht_cap, theirs.vht_cap) {
        // Intersect is NOT necessarily symmetrical. Our own capabilities prevails.
        (Some(ours), Some(theirs)) => Some(ours.intersect(&theirs)),
        _ => None,
    };
    JoinCapabilities { channel: ours.channel, cap_info, rates: vec![], ht_cap, vht_cap }
}

impl From<fidl_mlme::AssociateConfirm> for PeerCapabilities {
    fn from(ac: fidl_mlme::AssociateConfirm) -> Self {
        let cap_info = CapabilityInfo(ac.cap_info);
        let rates = ac.rates.iter().map(|&r| SupportedRate(r)).collect();
        // Both are safe to unwrap because the size of bytes are guaranteed to match the IEs.
        let ht_cap = ac.ht_cap.map(|h| *parse_ht_capabilities(&h.bytes[..]).unwrap());
        let vht_cap = ac.vht_cap.map(|v| *parse_vht_capabilities(&v.bytes[..]).unwrap());
        PeerCapabilities { cap_info, rates, ht_cap, vht_cap }
    }
}

impl From<JoinCapabilities> for fidl_mlme::NegotiatedCapabilities {
    fn from(jc: JoinCapabilities) -> Self {
        // Both try_into().unwrap() are safe because there are tests in the CQ that guarantee the
        // length of the slice produced by as_bytes() matches the length or the destination array
        // in FIDL.
        // See //src/connectivity/wlan/lib/common/rust/src/ie/parse.rs for |to_and_from_fidl_*|
        let ht_cap = jc
            .ht_cap
            .map(|h| fidl_mlme::HtCapabilities { bytes: h.as_bytes().try_into().unwrap() });
        let vht_cap = jc
            .vht_cap
            .map(|v| fidl_mlme::VhtCapabilities { bytes: v.as_bytes().try_into().unwrap() });
        Self {
            channel: jc.channel.to_fidl(),
            cap_info: jc.cap_info.raw(),
            rates: jc.rates.as_bytes().to_vec(),
            ht_cap: ht_cap.map(Box::new),
            vht_cap: vht_cap.map(Box::new),
        }
    }
}

#[cfg(test)]
mod tests {
    use {
        super::*,
        fidl_fuchsia_wlan_common as fidl_common,
        wlan_common::{ie, mac},
    };

    impl From<JoinCapabilities> for PeerCapabilities {
        fn from(join_cap: JoinCapabilities) -> Self {
            let JoinCapabilities { channel: _, cap_info, rates, ht_cap, vht_cap } = join_cap;
            Self { cap_info, rates, ht_cap, vht_cap }
        }
    }

    fn fake_client_join_cap() -> JoinCapabilities {
        JoinCapabilities {
            channel: Channel {
                primary: 42,
                cbw: wlan_common::channel::Cbw::Cbw80P80 { secondary80: 52 },
            },
            cap_info: mac::CapabilityInfo(0x1234),
            rates: [101, 102, 103, 104].iter().cloned().map(SupportedRate).collect(),
            ht_cap: Some(HtCapabilities {
                ht_cap_info: ie::HtCapabilityInfo(0).with_rx_stbc(2).with_tx_stbc(false),
                ..ie::fake_ht_capabilities()
            }),
            vht_cap: Some(ie::fake_vht_capabilities()),
        }
    }

    fn fake_ap_join_cap() -> JoinCapabilities {
        JoinCapabilities {
            channel: Channel { primary: 24, cbw: wlan_common::channel::Cbw::Cbw40 },
            cap_info: mac::CapabilityInfo(0x4321),
            // 101 + 128 turns it into a basic rate
            rates: [101 + 128, 102, 9].iter().cloned().map(SupportedRate).collect(),
            ht_cap: Some(HtCapabilities {
                ht_cap_info: ie::HtCapabilityInfo(0).with_rx_stbc(1).with_tx_stbc(true),
                ..ie::fake_ht_capabilities()
            }),
            vht_cap: Some(ie::fake_vht_capabilities()),
        }
    }

    #[test]
    fn client_intersect_with_ap() {
        assert_eq!(
            intersect_with_ap(&fake_client_join_cap(), fake_ap_join_cap().into())
                .expect("should be valid"),
            JoinCapabilities {
                cap_info: mac::CapabilityInfo(0x0220),
                rates: [229, 102].iter().cloned().map(SupportedRate).collect(),
                ht_cap: Some(HtCapabilities {
                    ht_cap_info: ie::HtCapabilityInfo(0).with_rx_stbc(2).with_tx_stbc(false),
                    ..ie::fake_ht_capabilities()
                }),
                ..fake_client_join_cap()
            }
        );
    }

    #[test]
    fn ap_intersect_with_remote_client() {
        assert_eq!(
            intersect_with_remote_client(&fake_ap_join_cap(), fake_client_join_cap().into())
                .expect("should be valid"),
            JoinCapabilities {
                cap_info: mac::CapabilityInfo(0x0220),
                rates: [229, 102].iter().cloned().map(SupportedRate).collect(),
                ht_cap: Some(HtCapabilities {
                    ht_cap_info: ie::HtCapabilityInfo(0).with_rx_stbc(0).with_tx_stbc(true),
                    ..ie::fake_ht_capabilities()
                }),
                ..fake_ap_join_cap()
            }
        );
    }

    #[test]
    fn fidl_assoc_conf_to_cap() {
        let ac = fidl_mlme::AssociateConfirm {
            result_code: fidl_mlme::AssociateResultCodes::Success,
            association_id: 123,
            cap_info: 0x1234,
            rates: vec![125, 126, 127, 128, 129],
            ht_cap: Some(Box::new(fidl_mlme::HtCapabilities {
                bytes: ie::fake_ht_capabilities().as_bytes().try_into().unwrap(),
            })),
            vht_cap: Some(Box::new(fidl_mlme::VhtCapabilities {
                bytes: ie::fake_vht_capabilities().as_bytes().try_into().unwrap(),
            })),
        };
        let cap: PeerCapabilities = ac.into();
        assert_eq!(
            cap,
            PeerCapabilities {
                cap_info: mac::CapabilityInfo(0x1234),
                rates: [125u8, 126, 127, 128, 129].iter().cloned().map(ie::SupportedRate).collect(),
                ht_cap: Some(ie::fake_ht_capabilities()),
                vht_cap: Some(ie::fake_vht_capabilities()),
            }
        );
    }

    #[test]
    fn cap_to_fidl_negotiated_cap() {
        let cap = JoinCapabilities {
            channel: Channel {
                primary: 123,
                cbw: wlan_common::channel::Cbw::Cbw80P80 { secondary80: 42 },
            },
            cap_info: mac::CapabilityInfo(0x1234),
            rates: [125u8, 126, 127, 128, 129].iter().cloned().map(ie::SupportedRate).collect(),
            ht_cap: Some(ie::fake_ht_capabilities()),
            vht_cap: Some(ie::fake_vht_capabilities()),
        };
        let fidl_cap: fidl_mlme::NegotiatedCapabilities = cap.into();
        assert_eq!(
            fidl_cap,
            fidl_mlme::NegotiatedCapabilities {
                channel: fidl_fuchsia_wlan_common::WlanChan {
                    primary: 123,
                    cbw: fidl_common::Cbw::Cbw80P80,
                    secondary80: 42,
                },
                cap_info: 0x1234,
                rates: vec![125, 126, 127, 128, 129],
                ht_cap: Some(Box::new(fidl_mlme::HtCapabilities {
                    bytes: ie::fake_ht_capabilities().as_bytes().try_into().unwrap()
                })),
                vht_cap: Some(Box::new(fidl_mlme::VhtCapabilities {
                    bytes: ie::fake_vht_capabilities().as_bytes().try_into().unwrap()
                })),
            }
        );
    }
}
