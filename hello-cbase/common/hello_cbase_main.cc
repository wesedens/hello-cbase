// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/callback.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/location.h"
#include "base/logging.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/task_runner.h"
#include "base/threading/thread.h"
#include "base/time/time.h"
#include "base/version.h"
#include "version.h"  // NOLINT

#include "cbase_switches.hh"

typedef std::string StringType;
typedef std::vector<StringType> StringVector;

// task runner
namespace {

bool FindNonTrivialFactor(int n, int* factor) {
  // Really naive algorithm.
  for (int i = 2; i < n; ++i) {
    if (n % i == 0) {
      *factor = i;
      return true;
    }
  }
  return false;
}

void FindNonTrivialFactorHelper(int n, int* factor, bool* found) {
  *found = FindNonTrivialFactor(n, factor);
}

void PrintStatusUpdate(base::Time start_time) {
  double num_seconds = (base::Time::Now() - start_time).InSecondsF();
  printf("Waited for %f seconds...\n", num_seconds);
}

void PrintStatusUpdateRepeatedly(
    const scoped_refptr<base::TaskRunner>& task_runner,
    base::Time start_time,
    base::TimeDelta print_interval) {
  PrintStatusUpdate(start_time);
  task_runner->PostDelayedTask(FROM_HERE,
                               base::Bind(PrintStatusUpdateRepeatedly,
                                          task_runner,
                                          start_time,
                                          print_interval),
                               print_interval);
}

}  // namespace

// task and thread test
void TaskRunnerTest(int limit)
{
    base::Thread worker_thread("Worker thread");
    CHECK(worker_thread.Start());

    base::MessageLoop main_loop;
    base::RunLoop     run_loop;

    int factor = 0;
    bool found = false;
    worker_thread.message_loop_proxy()->PostTaskAndReply(
            FROM_HERE,
            base::Bind(&FindNonTrivialFactorHelper, limit, &factor, &found),
            run_loop.QuitClosure());

    PrintStatusUpdateRepeatedly(main_loop.message_loop_proxy(),
            base::Time::Now(),
            base::TimeDelta::FromSeconds(1));

    run_loop.Run();

    worker_thread.Stop();

    if (found) {
        printf("found non-trivial factor %d for %d\n", factor, limit);
        DCHECK_EQ(limit % factor, 0);
    } else {
        printf("%d is prime\n", limit);
    }
}

// bind and callback test
namespace {

struct FibonacciState {
  FibonacciState() : i(0), j(1) {}

  int i, j;
};

int ComputeNextFibonacciNumber(FibonacciState* state) {
  int next = state->i + state->j;
  state->i = state->j;
  state->j = next;
  return state->i;
}

base::Callback<int()> MakeFibonacciClosure() {
  scoped_ptr<FibonacciState> state(new FibonacciState);
  return base::Bind(&ComputeNextFibonacciNumber, base::Owned(state.release()));
}

}  // namespace

void BindTest(int limit)
{
    base::Callback<int()> fibonacci_closure1 = MakeFibonacciClosure();
    base::Callback<int()> fibonacci_closure2 = MakeFibonacciClosure();
    for (int i = 0; i < limit; ++i) {
        int j = fibonacci_closure1.Run();
        int k = fibonacci_closure2.Run();
        DCHECK_EQ(j, k);
        printf("F_%d = %d\n", i, j);
    }
}

void LogInit()
{
    // init the logging api
    logging::DcheckState dcheck_state =
        logging::ENABLE_DCHECK_FOR_NON_OFFICIAL_RELEASE_BUILDS;
    logging::LoggingSettings setting;
    setting.logging_dest = logging::LOG_DEFAULT;
    setting.dcheck_state = dcheck_state;
    logging::InitLogging(setting);
}

void LogTest()
{
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

void CommandLineTest(const CommandLine& command_line)
{
    // command line test
    std::string greeting = command_line.GetSwitchValueASCII("greeting");
    if (greeting.empty())
        greeting = "Hello";
    std::string name = command_line.GetSwitchValueASCII("name");
    if (name.empty())
        name = "world";
    CHECK_GT(printf("%s, %s!\n", greeting.c_str(), name.c_str()), 0);
}


int main(int argc, char* argv[])
{
    static Version cbase_version(CBASE_VERSION_STRING);
    base::AtExitManager exit_manager;
    CHECK(CommandLine::Init(argc, argv));
    const CommandLine& command_line = *CommandLine::ForCurrentProcess();
    const StringType program_name = command_line.GetProgram().BaseName()
        .value();
    const char* version =cbase_version.GetString().c_str();

    // we go to all the trouble of creating the version file, it'd be nice
    // if we used it
    printf("%s: version: %s\n", program_name.c_str(), version);
    printf("lastchange hash: %s\n", LASTCHANGE_STRING);

    StringVector args = command_line.GetArgs();
    LogInit();

    if (command_line.HasSwitch(switches::kLogTest)) {
        // logging test
        printf("\nRunning log test\n\n");

        if (argc <= 1) {
            printf("%s: missing operand\n", argv[0]);
            return -1;
        }
        LogTest();
    }

    if (command_line.HasSwitch(switches::kBindTest)) {
        // Bind and callback test
        printf("\nRunning bind test\n\n");

        if (0 == args.size()) {
            printf("You must provide an argument for bind test\n");
            return -1;
        }

        int n;
        if (!base::StringToInt(args[0].c_str(), &n) || n < 2) {
            printf("%s: invalid n `%s'\n", argv[0], args[0].c_str());
            return -1;
        }
        BindTest(n);
    }

    if (command_line.HasSwitch(switches::kThreadTest)) {
        // task and thread test
        printf("\nRunning thread test\n\n");

        if (0 == args.size()) {
            printf("You must provide an argument for thread test\n");
            return -1;
        }

        int n;
        if (!base::StringToInt(args[0].c_str(), &n) || n < 2) {
            printf("%s: invalid (n > 2) n `%s'\n", argv[0], args[0].c_str());
            return -1;
        }
        TaskRunnerTest(n);
    }

    if (command_line.HasSwitch(switches::kCommandLineTest)) {
        // command line arguments test
        printf("\nRunning command line test\n\n");
        CommandLineTest(command_line);
    }
    return 0;
}
