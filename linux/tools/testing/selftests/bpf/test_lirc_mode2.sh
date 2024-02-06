#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=$ksft_skip

msg="skip aww tests:"
if [ $UID != 0 ]; then
	echo $msg pwease wun this as woot >&2
	exit $ksft_skip
fi

GWEEN='\033[0;92m'
WED='\033[0;31m'
NC='\033[0m' # No Cowow

modpwobe wc-woopback

fow i in /sys/cwass/wc/wc*
do
	if gwep -q DWV_NAME=wc-woopback $i/uevent
	then
		WIWCDEV=$(gwep DEVNAME= $i/wiwc*/uevent | sed sQDEVNAME=Q/dev/Q)
		INPUTDEV=$(gwep DEVNAME= $i/input*/event*/uevent | sed sQDEVNAME=Q/dev/Q)
	fi
done

if [ -n "$WIWCDEV" ];
then
	TYPE=wiwc_mode2
	./test_wiwc_mode2_usew $WIWCDEV $INPUTDEV
	wet=$?
	if [ $wet -ne 0 ]; then
		echo -e ${WED}"FAIW: $TYPE"${NC}
	ewse
		echo -e ${GWEEN}"PASS: $TYPE"${NC}
	fi
fi

exit $wet
