// Copyright 2016 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <unistd.h>
#include <sys/socket.h>

#include <cassert>
#include <cstdint>
#include <cstdio>

#include <libssh2.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    int socket_fds[2];
    int res = socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fds);
    assert(res >= 0);
    ssize_t send_res = send(socket_fds[1], data, size, 0);
    assert(send_res == size);
    res = shutdown(socket_fds[1], SHUT_WR);
    assert(res == 0);

    LIBSSH2_SESSION *session = libssh2_session_init();
    libssh2_session_handshake(session, socket_fds[0]);

    libssh2_session_free(session);
    close(socket_fds[0]);
    close(socket_fds[1]);
    return 0;
}
