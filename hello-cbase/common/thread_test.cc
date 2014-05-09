// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include "base/bind.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/threading/thread.h"
#include "hello-cbase/common/standard_out.hh"

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

void FindNonTrivialFactorHelper(int n, int* factor, bool* found)
{
  *found = FindNonTrivialFactor(n, factor);
}

void PrintStatusUpdate(base::Time start_time)
{
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
bool TaskRunnerTest(std::vector<std::string> args)
{
    // task and thread test
    OutputString("\nRunning thread test\n\n");

    if (0 == args.size()) {
        OutputString("ERROR: ", DECORATION_RED);
        OutputString("You must provide an argument for thread test\n");
        return false;
    }

    int n;
    if (!base::StringToInt(args[0].c_str(), &n) || n < 2) {
        OutputString("ERROR: ", DECORATION_RED);
        printf("'%s': invalid (n > 2) n `%s'\n", args[0].c_str(),
                args[0].c_str());
        return false;
    }

    base::Thread worker_thread("Worker thread");
    CHECK(worker_thread.Start());

    base::MessageLoop main_loop;
    base::RunLoop     run_loop;

    int factor = 0;
    bool found = false;
    worker_thread.message_loop_proxy()->PostTaskAndReply(
            FROM_HERE,
            base::Bind(&FindNonTrivialFactorHelper, n, &factor, &found),
            run_loop.QuitClosure());

    PrintStatusUpdateRepeatedly(main_loop.message_loop_proxy(),
            base::Time::Now(),
            base::TimeDelta::FromSeconds(1));

    run_loop.Run();

    worker_thread.Stop();

    if (found) {
        printf("found non-trivial factor %d for %d\n", factor, n);
        DCHECK_EQ(n % factor, 0);
    } else {
        printf("%d is prime\n", n);
    }
    return true;
}
