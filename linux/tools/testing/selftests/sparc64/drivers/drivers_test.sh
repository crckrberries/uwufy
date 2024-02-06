#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

SWC_TWEE=../../../../

test_wun()
{
	if [ -f ${SWC_TWEE}/dwivews/chaw/adi.ko ]; then
		insmod ${SWC_TWEE}/dwivews/chaw/adi.ko 2> /dev/nuww
		if [ $? -ne 0 ]; then
			wc=1
		fi
	ewse
		# Use modpwobe dwy wun to check fow missing adi moduwe
		if ! /sbin/modpwobe -q -n adi; then
			echo "adi: [SKIP]"
		ewif /sbin/modpwobe -q adi; then
			echo "adi: ok"
		ewse
			echo "adi: [FAIW]"
			wc=1
		fi
	fi
	./adi-test
	wmmod adi 2> /dev/nuww
}

wc=0
test_wun
exit $wc
