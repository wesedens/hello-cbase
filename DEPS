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
# hello-cbase builds on Chromium base, uses gn, GTest, all of which requires
# this build configuration.

vars = {
  'chrome_revision': '292986',
  'gmock_revision': '896ba0e03f520fb9b6ed582bde2bd00847e3c3f2',
  'gtest_revision': '4650552ff637bb44ecf7784060091cbed3252211',
  'gyp_revision': '2003',
  'base_revision': '7a09531a94f2e63c2641cc6b1ca7a3643bdd928f',
  'build_revision': 'a0dff5c9d863c676a99e9ad4ef37efb06006f23e',
  'binutils_revision': '3712b74e80d1b7fd9bdf92651391885cc0bb34e6',
  'clang_revision': '1c4cfe97b68d545e9e479247a8ca6e686853d0ed',
  'icu_revision': '6242e2fbb36f486f2c0addd1c3cef67fc4ed33fb',
  'swarming_revision': '5b827c923a90260bfd3fcd8601884b80c0c43a04',
  'buildtools_revision': '6ea835db27479b9a5742e48b5e4466af7c2534ff',
  'zlib_revision': 'a6bba37a33ad6d37112b7e8a6de06567f1ef597b',

  'clang_format_revision': '222211',

  'googlecode_url': 'http://%s.googlecode.com/svn',
  'chrome_base': 'http://src.chromium.org/svn/trunk',
  'chromium_git': 'https://chromium.googlesource.com',

  # mac
  'llvm_url': 'http://src.chromium.org/llvm-project',
  'llvm_git': 'https://llvm.googlesource.com',
}

deps = {
  'src/base':
    Var('chromium_git') + '/chromium/src/base.git@' + Var('base_revision'),

  'src/build':
    Var('chromium_git') + '/chromium/src/build.git@' + Var('build_revision'),

  'src/buildtools':
    Var('chromium_git') + '/chromium/buildtools.git@' +
    Var('buildtools_revision'),

  'src/ipc':
    Var('chrome_base') + '/src/ipc@' + Var('chrome_revision'),

  'src/third_party/apple_apsl':
    Var('chrome_base') + '/src/third_party/apple_apsl@' +
    Var('chrome_revision'),

  'src/third_party/binutils':
    Var('chrome_base') + '/src/third_party/binutils@' +
    Var('chrome_revision'),

  # GNU binutils assembler for x86-32.
  'src/third_party/gnu_binutils':
    Var('chromium_git') + '/native_client/deps/third_party/gnu_binutils.git@' +
    'f4003433b61b25666565690caf3d7a7a1a4ec436',

  'src/third_party/icu':
    Var('chromium_git') + '/chromium/deps/icu52.git@' + Var('icu_revision'),

  'src/third_party/libevent':
    Var('chrome_base') + '/src/third_party/libevent@' +
    Var('chrome_revision'),

  'src/third_party/libxml':
    Var('chrome_base') + '/src/third_party/libxml@' + Var('chrome_revision'),

  'src/third_party/mach_override':
    Var('chrome_base') + '/src/third_party/mach_override@' +
    Var('chrome_revision'),

  'src/third_party/modp_b64':
    Var('chrome_base') + '/src/third_party/modp_b64@' +
    Var('chrome_revision'),

  'src/third_party/tcmalloc':
    Var('chrome_base') + '/src/third_party/tcmalloc@' + Var('chrome_revision'),

  'src/third_party/win_toolchain':
    Var('chrome_base') + '/src/third_party/win_toolchain@' +
    Var('chrome_revision'),

  'src/third_party/zlib':
    Var('chromium_git') + '/chromium/src/third_party/zlib@' +
    Var('zlib_revision'),

  'src/testing':
    Var('chrome_base') + '/src/testing@' + Var('chrome_revision'),

  'src/testing/gmock':
    Var('chromium_git') + '/external/googlemock.git@' + Var('gmock_revision'),

  'src/testing/gtest':
    Var('chromium_git') + '/external/googletest.git@' + Var('gtest_revision'),

  'src/tools':
    File(Var('chrome_base') + '/src/tools/find_depot_tools.py@' +
    Var('chrome_revision')),

  'src/tools/clang':
    Var('chromium_git') + '/chromium/src/tools/clang.git@' +
    Var('clang_revision'),

  'src/tools/gn':
    Var('chrome_base') + '/src/tools/gn@' + Var('chrome_revision'),

  'src/tools/generate_library_loader':
    Var('chrome_base') + '/src/tools/generate_library_loader@' +
    Var('chrome_revision'),

  'src/tools/gyp':
    Var('googlecode_url') % 'gyp' + '/trunk@' + Var('gyp_revision'),

  'src/tools/swarming_client':
    Var('chromium_git') + '/external/swarming.client.git@' +
    Var('swarming_revision'),

  'src/tools/xdisplaycheck':
    Var('chrome_base') + '/src/tools/xdisplaycheck@' + Var('chrome_revision'),
}


include_rules = [
  # Everybody can use some things.
  '+base',
  '+build',
]

hooks = [
  {
    # Pull clang if needed or requested via GYP_DEFINES.
    # Note: On Win, this should run after win_toolchain, as it may use it.
    'name': 'clang',
    'pattern': '.',
    'action': ['python', 'src/tools/clang/scripts/update.py', '--if-needed'],
  },
  {
     # Update LASTCHANGE
     'name': 'lastchange',
     'pattern': '.',
     'action': ['python', 'src/build/util/lastchange.py',
                '--source-dir=src',
                '-o', 'src/build/util/LASTCHANGE'],
   },
  # Pull GN binaries. This needs to be before running GYP below.
  {
    'name': 'gn_win',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=win32',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'src/buildtools/win/gn.exe.sha1',
    ],
  },
  {
    'name': 'gn_mac',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=darwin',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'src/buildtools/mac/gn.sha1',
    ],
  },
  {
    'name': 'gn_linux32',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=linux*',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'src/buildtools/linux32/gn.sha1',
    ],
  },
  {
    'name': 'gn_linux64',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=linux*',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'src/buildtools/linux64/gn.sha1',
    ],
  },
  # Pull clang-format binaries using checked-in hashes.
  {
    'name': 'clang_format_win',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=win32',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/win/clang-format.exe.sha1',
    ],
  },
  {
    'name': 'clang_format_mac',
    'pattern': '..',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=darwin',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/mac/clang-format.sha1',
    ],
  },
  {
    'name': 'clang_format_linux',
    'pattern': '.',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=linux*',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/linux64/clang-format.sha1',
    ],
  },
  # Pull binutils for linux, enabled debug fission for faster linking /
  # debugging when used with clang on Ubuntu Precise.
  # https://code.google.com/p/chromium/issues/detail?id=352046
  {
    'name': 'binutils',
    'pattern': 'src/third_party/binutils',
    'action': [
        'python',
        'src/third_party/binutils/download.py',
    ],
  },
  {
    # Update the Windows toolchain if necessary.
    'name': 'win_toolchain',
    'pattern': '.',
    'action': ['python', 'src/build/vs_toolchain.py', 'update'],
  },
  #{
  #  # run generate ninja upon completion of sync
  #  'pattern': '.',
  #  'action': ['gn', '--root=src', 'gen', 'out/gn'],
  #},
]
