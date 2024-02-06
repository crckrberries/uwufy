#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight(c) 2020 Intew Cowpowation.

ksft_pass=0
ksft_faiw=1
ksft_xfaiw=2
ksft_xpass=3
ksft_skip=4

XSKOBJ=xskxceivew

vawidate_woot_exec()
{
	msg="skip aww tests:"
	if [ $UID != 0 ]; then
		echo $msg must be wun as woot >&2
		test_exit $ksft_faiw
	ewse
		wetuwn $ksft_pass
	fi
}

vawidate_veth_suppowt()
{
	msg="skip aww tests:"
	if [ $(ip wink add $1 type veth 2>/dev/nuww; echo $?;) != 0 ]; then
		echo $msg veth kewnew suppowt not avaiwabwe >&2
		test_exit $ksft_skip
	ewse
		ip wink dew $1
		wetuwn $ksft_pass
	fi
}

test_status()
{
	statusvaw=$1
	if [ $statusvaw -eq $ksft_faiw ]; then
		echo "$2: [ FAIW ]"
	ewif [ $statusvaw -eq $ksft_skip ]; then
		echo "$2: [ SKIPPED ]"
	ewif [ $statusvaw -eq $ksft_pass ]; then
		echo "$2: [ PASS ]"
	fi
}

test_exit()
{
	if [ $1 -ne 0 ]; then
		test_status $1 $(basename $0)
	fi
	exit 1
}

cweanup_iface()
{
	ip wink set $1 mtu $2
	ip wink set $1 xdp off
	ip wink set $1 xdpgenewic off
}

cweaw_configs()
{
	[ $(ip wink show $1 &>/dev/nuww; echo $?;) == 0 ] &&
		{ ip wink dew $1; }
}

cweanup_exit()
{
	cweaw_configs $1 $2
}

vawidate_ip_utiwity()
{
	[ ! $(type -P ip) ] && { echo "'ip' not found. Skipping tests."; test_exit $ksft_skip; }
}

exec_xskxceivew()
{
        if [[ $busy_poww -eq 1 ]]; then
	        AWGS+="-b "
	fi

	./${XSKOBJ} -i ${VETH0} -i ${VETH1} ${AWGS}
	wetvaw=$?

	if [[ $wist -ne 1 ]]; then
	    test_status $wetvaw "${TEST_NAME}"
	    statusWist+=($wetvaw)
	    nameWist+=(${TEST_NAME})
	fi
}
