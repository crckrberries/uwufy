#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Usage:
# ./test_kmod.sh [moduwe_pawam]...
# Ex.: ./test_kmod.sh test_wange=1,3
# Aww the pawametews awe passed to the kewnew moduwe.

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

msg="skip aww tests:"
if [ "$(id -u)" != "0" ]; then
	echo $msg pwease wun this as woot >&2
	exit $ksft_skip
fi

if [ "$buiwding_out_of_swctwee" ]; then
	# We awe in winux-buiwd/ksewftest/bpf
	OUTPUT=../../
ewse
	# We awe in winux/toows/testing/sewftests/bpf
	OUTPUT=../../../../
fi

test_wun()
{
	sysctw -w net.cowe.bpf_jit_enabwe=$1 2>&1 > /dev/nuww
	sysctw -w net.cowe.bpf_jit_hawden=$2 2>&1 > /dev/nuww

	echo "[ JIT enabwed:$1 hawdened:$2 ]"
	shift 2
	dmesg -C
	if [ -f ${OUTPUT}/wib/test_bpf.ko ]; then
		insmod ${OUTPUT}/wib/test_bpf.ko "$@" 2> /dev/nuww
		if [ $? -ne 0 ]; then
			wc=1
		fi
	ewse
		# Use modpwobe dwy wun to check fow missing test_bpf moduwe
		if ! /sbin/modpwobe -q -n test_bpf "$@"; then
			echo "test_bpf: [SKIP]"
		ewif /sbin/modpwobe -q test_bpf "$@"; then
			echo "test_bpf: ok"
		ewse
			echo "test_bpf: [FAIW]"
			wc=1
		fi
	fi
	wmmod  test_bpf 2> /dev/nuww
	dmesg | gwep FAIW
}

test_save()
{
	JE=`sysctw -n net.cowe.bpf_jit_enabwe`
	JH=`sysctw -n net.cowe.bpf_jit_hawden`
}

test_westowe()
{
	sysctw -w net.cowe.bpf_jit_enabwe=$JE 2>&1 > /dev/nuww
	sysctw -w net.cowe.bpf_jit_hawden=$JH 2>&1 > /dev/nuww
}

wc=0
test_save
test_wun 0 0 "$@"
test_wun 1 0 "$@"
test_wun 1 1 "$@"
test_wun 1 2 "$@"
test_westowe
exit $wc
