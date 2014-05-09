// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/command_line.h"
#include "hello-cbase/common/standard_out.hh"


void CommandLineTest(const CommandLine& command_line)
{
    // command line arguments test
    OutputString("\nRunning command line test\n\n");

    // command line test
    std::string greeting = command_line.GetSwitchValueASCII("greeting");
    if (greeting.empty())
        greeting = "Hello";
    std::string name = command_line.GetSwitchValueASCII("name");
    if (name.empty())
        name = "world";
    OutputString(greeting +", " +name +"\n");
}
