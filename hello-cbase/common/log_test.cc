// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <vector>

#include "base/logging.h"
#include "hello-cbase/common/standard_out.hh"


void LogTest()
{
    // logging test
    OutputString("\nRunning log test\n\n");

    // show some examples of logging
    if (VLOG_IS_ON(2)) {
        OutputString("vlog is on 2\n");
    }

    LOG(INFO) << "printed in debug and release";
    DLOG(INFO) << "only printed when compiled with debug flags";
    VLOG(1) << "printed when you run with --v=1 or more";
    LOG_ASSERT(1);
    DLOG_ASSERT(1);
}
