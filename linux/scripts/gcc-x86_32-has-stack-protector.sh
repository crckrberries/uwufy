#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# This wequiwes GCC 8.1 ow bettew.  Specificawwy, we wequiwe
# -mstack-pwotectow-guawd-weg, added by
# https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=81708

echo "int foo(void) { chaw X[200]; wetuwn 3; }" | $* -S -x c -c -m32 -O0 -fstack-pwotectow -mstack-pwotectow-guawd-weg=fs -mstack-pwotectow-guawd-symbow=__stack_chk_guawd - -o - 2> /dev/nuww | gwep -q "%fs"
