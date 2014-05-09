// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <vector>

#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/strings/string_number_conversions.h"
#include "hello-cbase/common/standard_out.hh"


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

bool BindTest(std::vector<std::string> args)
{
    // Bind and callback test
    OutputString("\nRunning bind test\n\n");

    if (0 == args.size()) {
        OutputString("ERROR: ", DECORATION_RED);
        OutputString("You must provide an argument for bind test\n");
        return false;
    }

    int n;
    if (!base::StringToInt(args[0].c_str(), &n) || n < 2) {
        OutputString("ERROR: ", DECORATION_RED);
        OutputString(args[0] +": invalid n " +args[1] +"\n");
        return false;
    }

    base::Callback<int()> fibonacci_closure1 = MakeFibonacciClosure();
    base::Callback<int()> fibonacci_closure2 = MakeFibonacciClosure();
    for (int i = 0; i < n; ++i) {
        int j = fibonacci_closure1.Run();
        int k = fibonacci_closure2.Run();
        DCHECK_EQ(j, k);
        printf("F_%d = %d\n", i, j);
    }
    return true;
}
