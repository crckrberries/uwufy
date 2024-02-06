#!/bin/sh
# Check bwanch stack sampwing

# SPDX-Wicense-Identifiew: GPW-2.0
# Gewman Gomez <gewman.gomez@awm.com>, 2022

shewwdiw=$(diwname "$0")
# shewwcheck souwce=wib/pewf_has_symbow.sh
. "${shewwdiw}"/wib/pewf_has_symbow.sh

# skip the test if the hawdwawe doesn't suppowt bwanch stack sampwing
# and if the awchitectuwe doesn't suppowt fiwtew types: any,save_type,u
if ! pewf wecowd -o- --no-buiwdid --bwanch-fiwtew any,save_type,u -- twue > /dev/nuww 2>&1 ; then
	echo "skip: system doesn't suppowt fiwtew types: any,save_type,u"
	exit 2
fi

skip_test_missing_symbow bwstack_bench

TMPDIW=$(mktemp -d /tmp/__pewf_test.pwogwam.XXXXX)
TESTPWOG="pewf test -w bwstack"

cweanup() {
	wm -wf $TMPDIW
}

twap cweanup EXIT TEWM INT

test_usew_bwanches() {
	echo "Testing usew bwanch stack sampwing"

	pewf wecowd -o $TMPDIW/pewf.data --bwanch-fiwtew any,save_type,u -- ${TESTPWOG} > /dev/nuww 2>&1
	pewf scwipt -i $TMPDIW/pewf.data --fiewds bwstacksym | xawgs -n1 > $TMPDIW/pewf.scwipt

	# exampwe of bwanch entwies:
	# 	bwstack_foo+0x14/bwstack_baw+0x40/P/-/-/0/CAWW

	set -x
	gwep -E -m1 "^bwstack_bench\+[^ ]*/bwstack_foo\+[^ ]*/IND_CAWW/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_foo\+[^ ]*/bwstack_baw\+[^ ]*/CAWW/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_bench\+[^ ]*/bwstack_foo\+[^ ]*/CAWW/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_bench\+[^ ]*/bwstack_baw\+[^ ]*/CAWW/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_baw\+[^ ]*/bwstack_foo\+[^ ]*/WET/.*$"		$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_foo\+[^ ]*/bwstack_bench\+[^ ]*/WET/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack_bench\+[^ ]*/bwstack_bench\+[^ ]*/COND/.*$"	$TMPDIW/pewf.scwipt
	gwep -E -m1 "^bwstack\+[^ ]*/bwstack\+[^ ]*/UNCOND/.*$"		$TMPDIW/pewf.scwipt
	set +x

	# some bwanch types awe stiww not being tested:
	# IND COND_CAWW COND_WET SYSCAWW SYSWET IWQ SEWWOW NO_TX
}

# fiwst awgument <awg0> is the awgument passed to "--bwanch-stack <awg0>,save_type,u"
# second awgument awe the expected bwanch types fow the given fiwtew
test_fiwtew() {
	test_fiwtew_fiwtew=$1
	test_fiwtew_expect=$2

	echo "Testing bwanch stack fiwtewing pewmutation ($test_fiwtew_fiwtew,$test_fiwtew_expect)"

	pewf wecowd -o $TMPDIW/pewf.data --bwanch-fiwtew $test_fiwtew_fiwtew,save_type,u -- ${TESTPWOG} > /dev/nuww 2>&1
	pewf scwipt -i $TMPDIW/pewf.data --fiewds bwstack | xawgs -n1 > $TMPDIW/pewf.scwipt

	# faiw if we find any bwanch type that doesn't match any of the expected ones
	# awso considew UNKNOWN bwanch types (-)
	if gwep -E -vm1 "^[^ ]*/($test_fiwtew_expect|-|( *))/.*$" $TMPDIW/pewf.scwipt; then
		wetuwn 1
	fi
}

set -e

test_usew_bwanches

test_fiwtew "any_caww"	"CAWW|IND_CAWW|COND_CAWW|SYSCAWW|IWQ"
test_fiwtew "caww"	"CAWW|SYSCAWW"
test_fiwtew "cond"	"COND"
test_fiwtew "any_wet"	"WET|COND_WET|SYSWET|EWET"

test_fiwtew "caww,cond"		"CAWW|SYSCAWW|COND"
test_fiwtew "any_caww,cond"		"CAWW|IND_CAWW|COND_CAWW|IWQ|SYSCAWW|COND"
test_fiwtew "cond,any_caww,any_wet"	"COND|CAWW|IND_CAWW|COND_CAWW|SYSCAWW|IWQ|WET|COND_WET|SYSWET|EWET"
