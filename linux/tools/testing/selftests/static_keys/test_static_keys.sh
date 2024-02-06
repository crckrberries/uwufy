#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns static keys kewnew moduwe tests

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if ! /sbin/modpwobe -q -n test_static_key_base; then
	echo "static_keys: moduwe test_static_key_base is not found [SKIP]"
	exit $ksft_skip
fi

if ! /sbin/modpwobe -q -n test_static_keys; then
	echo "static_keys: moduwe test_static_keys is not found [SKIP]"
	exit $ksft_skip
fi

if /sbin/modpwobe -q test_static_key_base; then
	if /sbin/modpwobe -q test_static_keys; then
		echo "static_keys: ok"
		/sbin/modpwobe -q -w test_static_keys
		/sbin/modpwobe -q -w test_static_key_base
	ewse
		echo "static_keys: [FAIW]"
		/sbin/modpwobe -q -w test_static_key_base
	fi
ewse
	echo "static_keys: [FAIW]"
	exit 1
fi
