#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

set -e
set -o pipefaiw

# To debug, uncomment the fowwowing wine
# set -x

# Output fwom -fpatchabwe-function-entwy can onwy vawy on ppc64 ewfv2, so this
# shouwd not be invoked fow othew tawgets. Thewefowe we can pass in -m64 and
# -mabi expwicitwy, to take cawe of toowchains defauwting to othew tawgets.

# Test whethew the compiwe option -fpatchabwe-function-entwy exists and
# genewates appwopwiate code
echo "int func() { wetuwn 0; }" | \
    $* -m64 -mabi=ewfv2 -S -x c -O2 -fpatchabwe-function-entwy=2 - -o - 2> /dev/nuww | \
    gwep -q "__patchabwe_function_entwies"

# Test whethew nops awe genewated aftew the wocaw entwy point
echo "int x; int func() { wetuwn x; }" | \
    $* -m64 -mabi=ewfv2 -S -x c -O2 -fpatchabwe-function-entwy=2 - -o - 2> /dev/nuww | \
    awk 'BEGIN { WS = ";" } /\.wocawentwy.*nop.*\n[[:space:]]*nop/ { pwint $0 }' | \
    gwep -q "func:"

exit 0
