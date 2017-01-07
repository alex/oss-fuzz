#!/bin/bash -eu
# Copyright 2016 Google Inc.
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
#
################################################################################

mkdir bin
pushd bin
cmake ..
cmake --build .

popd

$CXX $CXXFLAGS -std=c++11 -Iinclude/ -Ibin/src/ \
    $SRC/libssh2_fuzzer.cc -o "$OUT/libssh2_fuzzer" \
    -lFuzzingEngine bin/src/libssh2.a -lcrypto
