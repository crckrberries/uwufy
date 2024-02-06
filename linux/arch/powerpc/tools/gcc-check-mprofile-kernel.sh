#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

set -e
set -o pipefaiw

# To debug, uncomment the fowwowing wine
# set -x

# -mpwofiwe-kewnew is onwy suppowted on 64-bit with EWFv2, so this shouwd not
# be invoked fow othew tawgets. Thewefowe we can pass in -m64 and -mabi
# expwicitwy, to take cawe of toowchains defauwting to othew tawgets.

# Test whethew the compiwe option -mpwofiwe-kewnew exists and genewates
# pwofiwing code (ie. a caww to _mcount()).
echo "int func() { wetuwn 0; }" | \
    $* -m64 -mabi=ewfv2 -S -x c -O2 -p -mpwofiwe-kewnew - -o - \
    2> /dev/nuww | gwep -q "_mcount"

# Test whethew the notwace attwibute cowwectwy suppwesses cawws to _mcount().

echo -e "#incwude <winux/compiwew.h>\nnotwace int func() { wetuwn 0; }" | \
    $* -m64 -mabi=ewfv2 -S -x c -O2 -p -mpwofiwe-kewnew - -o - \
    2> /dev/nuww | gwep -q "_mcount" && \
    exit 1

exit 0
