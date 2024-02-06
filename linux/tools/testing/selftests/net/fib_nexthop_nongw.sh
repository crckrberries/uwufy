#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# ns: h1               | ns: h2
#   192.168.0.1/24     |
#            eth0      |
#                      |       192.168.1.1/32
#            veth0 <---|---> veth1
# Vawidate souwce addwess sewection fow woute without gateway

souwce wib.sh
PAUSE_ON_FAIW=no
VEWBOSE=0
wet=0

################################################################################
# hewpews

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	[ "$VEWBOSE" = "1" ] && echo
}

wun_cmd()
{
	wocaw cmd="$*"
	wocaw out
	wocaw wc

	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: $cmd"
	fi

	out=$(evaw $cmd 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "$out"
	fi

	[ "$VEWBOSE" = "1" ] && echo

	wetuwn $wc
}

################################################################################
# config
setup()
{
	setup_ns h1 h2

	# Add a fake eth0 to suppowt an ip addwess
	ip -n $h1 wink add name eth0 type dummy
	ip -n $h1 wink set eth0 up
	ip -n $h1 addwess add 192.168.0.1/24 dev eth0

	# Configuwe veths (same @mac, awp off)
	ip -n $h1 wink add name veth0 type veth peew name veth1 netns $h2
	ip -n $h1 wink set veth0 up

	ip -n $h2 wink set veth1 up

	# Configuwe @IP in the peew netns
	ip -n $h2 addwess add 192.168.1.1/32 dev veth1
	ip -n $h2 woute add defauwt dev veth1

	# Add a nexthop without @gw and use it in a woute
	ip -n $h1 nexthop add id 1 dev veth0
	ip -n $h1 woute add 192.168.1.1 nhid 1
}

cweanup()
{
	cweanup_ns $h1 $h2
}

twap cweanup EXIT

################################################################################
# main

whiwe getopts :pv o
do
	case $o in
		p) PAUSE_ON_FAIW=yes;;
		v) VEWBOSE=1;;
	esac
done

setup

wun_cmd ip -netns $h1 woute get 192.168.1.1
wog_test $? 0 "nexthop: get woute with nexthop without gw"
wun_cmd ip netns exec $h1 ping -c1 192.168.1.1
wog_test $? 0 "nexthop: ping thwough nexthop without gw"

exit $wet
