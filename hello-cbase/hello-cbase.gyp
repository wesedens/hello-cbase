# Copyright 2012 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

{
  'variables': {
    'chromium_code': 1,
  },
  'includes': [
    #'unittests.gypi',
    'hello-cbase.gypi',
    '../build/util/version.gypi',
  ],
  'target_defaults': {
    'actions': [{
      'action_name': 'Make cbase_version.cc',
      'variables': {
        'make_version_cc_path': 'tools/build/make_version_cc.py',
      },
      'inputs': [
        '<(make_version_cc_path)',
        'VERSION',
      ],
      'outputs': [
        '<(INTERMEDIATE_DIR)/cbase_version.cc',
      ],
      'action': [
        'python',
        '<(make_version_cc_path)',
        '<@(_outputs)',
        '<(version_full)',
      ],
      'process_outputs_as_sources': 1,
    },],
  },
  'targets': [
    {
      'target_name': 'build_all',
      'type': 'none',
      'dependencies': [
        '<(DEPTH)/base/base.gyp:*',
        'common/common.gyp:*',
      ],
    },
    #{
    #  # New unittests should be added to unittests.gypi.
    #  'target_name': 'build_unittests',
    #  'type': 'none',
    #  'dependencies': [
    #    '<@(unittests)',
    #  ],
    #},
    {
      'target_name': 'cbase_version_header',
      'type': 'none',
      'hard_dependency': 1,
      'actions': [
        {
          'action_name': 'version_header',
          'variables': {
            'lastchange_path':
              '<(DEPTH)/build/util/LASTCHANGE',
          },
          'inputs': [
            '<(version_path)',
            '<(branding_path)',
            #'<(lastchange_path)',
            'version.h.in',
          ],
          'outputs': [
            '<(SHARED_INTERMEDIATE_DIR)/version.h',
          ],
          'action': [
            'python',
            '<(version_py_path)',
            '-f', '<(version_path)',
            '-f', '<(branding_path)',
            #'-f', '<(lastchange_path)',
            'version.h.in',
            '<@(_outputs)',
          ],
          'message': 'Generating version header file: <@(_outputs)',
        },
      ],
    },
  ],
}
