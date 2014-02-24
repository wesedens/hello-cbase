#include <stdio.h>

#include "common_cbase.hh"

#include "base/command_line.h"
#include "base/logging.h"

int main(int argc, char* argv[])
{
    CHECK(CommandLine::Init(argc, argv));

    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    std::string greeting = command_line.GetSwitchValueASCII("greeting");
    if (greeting.empty())
        greeting = "Hello";
    std::string name = command_line.GetSwitchValueASCII("name");
    if (name.empty())
        name = "world";

    CHECK_GT(printf("%s, %s!\n", greeting.c_str(), name.c_str()), 0);
    LOG(INFO) << greeting << ", " << name << "!";

    common_print();

    LOG(INFO) << "Found 3 cookies";
    DLOG(INFO) << "Found Debug cookies";
    VLOG(1) << "I'm printed when you run the program with --v=1 or more";
    LOG_ASSERT(1);
    DLOG_ASSERT(1);
    return 0;
}
