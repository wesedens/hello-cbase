// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/strings/utf_string_conversions.h"
#include "base/version.h"
#include "hello-cbase/common/cbase_constants.hh"
#include "hello-cbase/common/cbase_switches.hh"
#include "hello-cbase/common/hello_cbase_tests.hh"
#include "hello-cbase/common/standard_out.hh"
#include "version.h"  // NOLINT



#if defined(OS_WIN)
    // The native command line string type.
    typedef std::wstring StringType;
#elif defined(OS_POSIX)
    typedef std::string StringType;
#endif

typedef std::vector<StringType> StringVector;


namespace {

std::vector<std::string> GetArgs(const CommandLine& cmdline)
{
    CommandLine::StringVector in_args = cmdline.GetArgs();
#if defined(OS_WIN)
    std::vector<std::string> out_args;
    for (size_t i = 0; i < in_args.size(); i++)
        out_args.push_back(base::WideToUTF8(in_args[i]));
    return out_args;
#else
    return in_args;
#endif
}

bool LogInit()
{
    // init the logging api
    logging::LoggingSettings setting;
    setting.logging_dest = logging::LOG_DEFAULT;
    return logging::InitLogging(setting);
}

}  // namespace


int main(int argc, char* argv[])
{
    static Version cbase_version(CBASE_VERSION_STRING);
    base::AtExitManager exit_manager;
    int retval = 0;

#if defined(OS_WIN)
    CommandLine::set_slash_is_not_a_switch();
#endif

    CHECK(CommandLine::Init(argc, argv));

    const CommandLine&       cmdline = *CommandLine::ForCurrentProcess();
    std::vector<std::string> args    = GetArgs(cmdline);

    // windows has to be difficult
#if defined(OS_WIN)
    const StringType  pname        = cmdline.GetProgram().BaseName().value();
    const std::string program_name = std::string(pname.begin(), pname.end());
#else
    const StringType  program_name = cmdline.GetProgram().BaseName().value();
#endif

    const std::string version = cbase_version.GetString();

    // we go to all the trouble of creating the version file, it'd be nice
    // if we used it
    OutputString(program_name, DECORATION_BLUE);
    OutputString(" [--bind-test] [--log-test] [--thread-test]\n"
                 "            [--command-line-test] [<args>]\n");
    OutputString("version macro  : " +version +"\n");
    OutputString("version        : " + std::string(cbase::kCbaseVersion) +"\n");
    OutputString("lastchange hash: " LASTCHANGE_STRING "\n");


// TODO: fix this for windows
#if !defined(OS_WIN)
    CHECK(LogInit());
#endif

    if (cmdline.HasSwitch(switches::kLogTest)) {
        // logging test
        LogTest();
    }

    if (cmdline.HasSwitch(switches::kBindTest)) {
        // Bind and callback test
        if (!BindTest(args)) {
            retval = -1;
        }
    }

    if (cmdline.HasSwitch(switches::kThreadTest)) {
        // task and thread test
        if (TaskRunnerTest(args)) {
            retval = -1;
        }
    }

    if (cmdline.HasSwitch(switches::kCommandLineTest)) {
        // command line arguments test
        CommandLineTest(cmdline);
    }

    return retval;
}
