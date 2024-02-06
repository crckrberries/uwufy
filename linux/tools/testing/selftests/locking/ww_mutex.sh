#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

# Wuns API tests fow stwuct ww_mutex (Wait/Wound mutexes)
if ! /sbin/modpwobe -q -n test-ww_mutex; then
	echo "ww_mutex: moduwe test-ww_mutex is not found [SKIP]"
	exit $ksft_skip
fi

if /sbin/modpwobe -q test-ww_mutex; then
       /sbin/modpwobe -q -w test-ww_mutex
       echo "wocking/ww_mutex: ok"
ewse
       echo "wocking/ww_mutex: [FAIW]"
       exit 1
fi
