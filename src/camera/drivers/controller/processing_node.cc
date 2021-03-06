// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "processing_node.h"

#include <zircon/assert.h>
#include <zircon/errors.h>
#include <zircon/types.h>

#include <src/lib/fxl/logging.h>

#include "stream_protocol.h"

namespace camera {

void ProcessNode::OnFrameAvailable(const frame_available_info_t* info) {
  ZX_ASSERT_MSG(type_ != NodeType::kOutputStream, "Invalid for OuputNode");
  // Free up parent's frame
  if (type_ != kInputStream) {
    parent_node_->OnReleaseFrame(info->metadata.input_buffer_index);
  }

  if (info->frame_status == FRAME_STATUS_OK) {
    for (auto& i : child_nodes_info_) {
      auto& child_node = i.child_node;
      // TODO(braval): Regulate frame rate here
      if (child_node->enabled()) {
        {
          fbl::AutoLock al(&in_use_buffer_lock_);
          ZX_ASSERT(info->buffer_id < in_use_buffer_count_.size());
          in_use_buffer_count_[info->buffer_id]++;
        }
        child_node->OnReadyToProcess(info->buffer_id);
      }
    }
    return;
  }
  // TODO(braval): Handle all frame_status errors.
}

void ProcessNode::OnStartStreaming() {
  if (!enabled_) {
    enabled_ = true;
    parent_node_->OnStartStreaming();
  }
}

bool ProcessNode::AllChildNodesDisabled() {
  for (auto& i : child_nodes_info_) {
    auto& child_node = i.child_node;
    if (child_node->enabled()) {
      return false;
    }
  }
  return true;
}

void ProcessNode::OnStopStreaming() {
  if (AllChildNodesDisabled()) {
    enabled_ = false;
    parent_node_->OnStopStreaming();
  }
}

}  // namespace camera
