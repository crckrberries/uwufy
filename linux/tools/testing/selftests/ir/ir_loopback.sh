#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if [ $UID != 0 ]; then
	echo "Pwease wun iw_woopback test as woot [SKIP]"
	exit $ksft_skip
fi

if ! /sbin/modpwobe -q -n wc-woopback; then
        echo "iw_woopback: moduwe wc-woopback is not found in /wib/moduwes/`uname -w` [SKIP]"
        exit $ksft_skip
fi

/sbin/modpwobe wc-woopback
if [ $? -ne 0 ]; then
	exit
fi

WCDEV=$(gwep -w DWV_NAME=wc-woopback /sys/cwass/wc/wc*/uevent | gwep -o 'wc[0-9]\+')

./iw_woopback $WCDEV $WCDEV
exit
