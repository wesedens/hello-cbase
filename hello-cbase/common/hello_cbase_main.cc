#include <stdio.h>

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/version.h"
#include "version.h"  // NOLINT


typedef std::string StringType;


void logging_test()
{
    // init the logging api
    logging::DcheckState dcheck_state =
        logging::ENABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS;
    logging::LoggingSettings setting;
    setting.logging_dest = logging::LOG_DEFAULT;
    setting.dcheck_state = dcheck_state;
    logging::InitLogging(setting);

    printf("\n\nLogging Example\n");
    // show some examples of logging
    if (VLOG_IS_ON(2)) {
        printf("vlog is on 2\n");
    }

    LOG(INFO) << "printed in debug and release";
    DLOG(INFO) << "only printed when compiled with debug flags";
    VLOG(1) << "printed when you run with --v=1 or more";
    LOG_ASSERT(1);
    DLOG_ASSERT(1);
}


int main(int argc, char* argv[])
{
    static Version cbase_version(CBASE_VERSION_STRING);
    CHECK(CommandLine::Init(argc, argv));
    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    const StringType program_name = command_line.GetProgram().BaseName().value();
    const char* version =cbase_version.GetString().c_str();
    printf("%s: version: %s\n", program_name.c_str(), version);
    printf("lastchange hash: %s\n", LASTCHANGE_STRING);


    std::string greeting = command_line.GetSwitchValueASCII("greeting");
    if (greeting.empty())
        greeting = "Hello";
    std::string name = command_line.GetSwitchValueASCII("name");
    if (name.empty())
        name = "world";

    CHECK_GT(printf("%s, %s!\n", greeting.c_str(), name.c_str()), 0);

    logging_test();

    return 0;
}
