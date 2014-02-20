# Copyright 2012 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# hello-cbase builds on Chrome base, uses GYP, GTest, all of which requires
# this build configuration.

vars = {
  "chrome_revision": "202420",
  "gmock_revision": "453",
  "gtest_revision": "664",
  "gyp_revision": "1719",

  "chrome_base": "http://src.chromium.org/svn/trunk",
}

deps = {
  "src/base":
    Var("chrome_base") + "/src/base@" + Var("chrome_revision"),

  "src/third_party/zlib":
    Var("chrome_base") + "/src/third_party/zlib@" +
        Var("chrome_revision"),
  "src/third_party/libevent":
    Var("chrome_base") + "/src/third_party/libevent@" +
        Var("chrome_revision"),
  "src/third_party/icu":
    Var("chrome_base") + "/deps/third_party/icu46@" +
        Var("chrome_revision"),
  "src/third_party/modp_b64":
    Var("chrome_base") + "/src/third_party/modp_b64@" +
        Var("chrome_revision"),
  "src/third_party/tcmalloc":
    Var("chrome_base") + "/src/third_party/tcmalloc@" +
        Var("chrome_revision"),

  "src/net/third_party/nss":
    Var("chrome_base") + "/src/net/third_party/nss@" +
        Var("chrome_revision"),

  "src/build":
    Var("chrome_base") + "/src/build@" + Var("chrome_revision"),

  "src/testing":
    Var("chrome_base") + "/src/testing@" + Var("chrome_revision"),
  "src/testing/gmock":
    "http://googlemock.googlecode.com/svn/trunk@" + Var("gmock_revision"),
  "src/testing/gtest":
    "http://googletest.googlecode.com/svn/trunk@" + Var("gtest_revision"),

  "src/tools/gyp":
    "http://gyp.googlecode.com/svn/trunk@" + Var("gyp_revision"),
  "src/tools/xdisplaycheck":
    Var("chrome_base") + "/tools/xdisplaycheck/@" + Var("chrome_revision"),
}


include_rules = [
  # Everybody can use some things.
  "+base",
  "+build",
]

hooks = [
  {
    # A change to a .gyp, .gypi, or to GYP itself should run the generator.
    "pattern": ".",
    "action": ["python",
               "src/build/gyp_chromium",
               "--include=src/hello-cbase/hello-cbase.gypi",
               "src/hello-cbase/hello-cbase.gyp"],
  },
]
