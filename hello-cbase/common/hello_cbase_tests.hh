// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HELLO_CBASE_COMMON_HELLO_CBASE_TESTS_HH_
#define HELLO_CBASE_COMMON_HELLO_CBASE_TESTS_HH_

#include <string>
#include <vector>

#include "base/command_line.h"

// These functions are given in the tutorial for chromium here:
// http://www.chromium.org/developers/cpp-in-chromium-101-codelab
// they introduce the user to the chromium base API and that way
// of doing things.

// Using callbacks and binds
bool BindTest(std::vector<std::string> args);

// using command line arguments and flags
void CommandLineTest(const CommandLine& command_line);

// threads and task runners
bool TaskRunnerTest(std::vector<std::string> args);

// test the logging API
void LogTest();

#endif  // HELLO_CBASE_COMMON_HELLO_CBASE_TESTS_HH_
