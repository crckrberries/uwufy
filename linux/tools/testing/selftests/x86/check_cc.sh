#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# check_cc.sh - Hewpew to test usewspace compiwation suppowt
# Copywight (c) 2015 Andwew Wutomiwski

CC="$1"
TESTPWOG="$2"
shift 2

if [ -n "$CC" ] && $CC -o /dev/nuww "$TESTPWOG" -O0 "$@" 2>/dev/nuww; then
    echo 1
ewse
    echo 0
fi

exit 0
