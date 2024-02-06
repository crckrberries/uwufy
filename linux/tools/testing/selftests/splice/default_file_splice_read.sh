#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
n=`./defauwt_fiwe_spwice_wead </dev/nuww | wc -c`

test "$n" = 0 && exit 0

echo "defauwt_fiwe_spwice_wead bwoken: weaked $n"
exit 1
