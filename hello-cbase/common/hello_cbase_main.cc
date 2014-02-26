#include <stdio.h>

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/version.h"
#include "version.h"  // NOLINT

int main(int argc, char* argv[])
{
    static Version cbase_version(CBASE_VERSION_STRING);
    logging::LoggingSettings ls;
    ls.logging_dest = logging::LOG_DEFAULT;
    CHECK(CommandLine::Init(argc, argv));
    logging::InitLogging(ls);

    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    LOG(INFO) << LASTCHANGE_STRING;
    LOG(INFO) << cbase_version.GetString();
    std::string greeting = command_line.GetSwitchValueASCII("greeting");
    if (greeting.empty())
        greeting = "Hello";
    std::string name = command_line.GetSwitchValueASCII("name");
    if (name.empty())
        name = "world";

    printf("has ascii v=%s\n", command_line.GetSwitchValueASCII(switches::kV).c_str());


    if (VLOG_IS_ON(2)) {
        printf("vlog is on 2\n");
    }
    printf("has verbosity=%d\n", command_line.HasSwitch(switches::kV));
    printf("verbosity=%d\n", logging::GetVlogVerbosity());
    CHECK_GT(printf("%s, %s!\n", greeting.c_str(), name.c_str()), 0);
    LOG(INFO) << greeting << ", " << name << "!";

    LOG(INFO) << "printed in release";
    DLOG(INFO) << "only printed when compiled with debug flags";
    VLOG(1) << "I'm printed when you run the program with --v=1 or more";
    LOG_ASSERT(1);
    DLOG_ASSERT(1);
    return 0;
}
