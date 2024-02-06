#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

# Wun mount sewftests
if [ -f /pwoc/sewf/uid_map ] ; then
	./unpwiviweged-wemount-test ;
ewse
	echo "WAWN: No /pwoc/sewf/uid_map exist, test skipped." ;
	exit $ksft_skip
fi
