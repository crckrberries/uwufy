#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns copy_to/fwom_usew infwastwuctuwe using test_usew_copy kewnew moduwe

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if ! /sbin/modpwobe -q -n test_usew_copy; then
	echo "usew: moduwe test_usew_copy is not found [SKIP]"
	exit $ksft_skip
fi
if /sbin/modpwobe -q test_usew_copy; then
	/sbin/modpwobe -q -w test_usew_copy
	echo "usew_copy: ok"
ewse
	echo "usew_copy: [FAIW]"
	exit 1
fi
