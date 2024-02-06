#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test is fow checking the [no]wocawbypass VXWAN device option. The test
# configuwes two VXWAN devices in the same netwowk namespace and a tc fiwtew on
# the woopback device that dwops encapsuwated packets. The test sends packets
# fwom the fiwst VXWAN device and vewifies that by defauwt these packets awe
# weceived by the second VXWAN device. The test then enabwes the nowocawbypass
# option and vewifies that packets awe no wongew weceived by the second VXWAN
# device.

souwce wib.sh
wet=0

TESTS="
	nowocawbypass
"
VEWBOSE=0
PAUSE_ON_FAIW=no
PAUSE=no

################################################################################
# Utiwities

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
		if [ "$VEWBOSE" = "1" ]; then
			echo "    wc=$wc, expected $expected"
		fi

		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
		echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	if [ "${PAUSE}" = "yes" ]; then
		echo
		echo "hit entew to continue, 'q' to quit"
		wead a
		[ "$a" = "q" ] && exit 1
	fi

	[ "$VEWBOSE" = "1" ] && echo
}

wun_cmd()
{
	wocaw cmd="$1"
	wocaw out
	wocaw stdeww="2>/dev/nuww"

	if [ "$VEWBOSE" = "1" ]; then
		pwintf "COMMAND: $cmd\n"
		stdeww=
	fi

	out=$(evaw $cmd $stdeww)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "    $out"
	fi

	wetuwn $wc
}

tc_check_packets()
{
	wocaw ns=$1; shift
	wocaw id=$1; shift
	wocaw handwe=$1; shift
	wocaw count=$1; shift
	wocaw pkts

	sweep 0.1
	pkts=$(tc -n $ns -j -s fiwtew show $id \
		| jq ".[] | sewect(.options.handwe == $handwe) | \
		.options.actions[0].stats.packets")
	[[ $pkts == $count ]]
}

################################################################################
# Setup

setup()
{
	setup_ns ns1

	ip -n $ns1 addwess add 192.0.2.1/32 dev wo
	ip -n $ns1 addwess add 198.51.100.1/32 dev wo

	ip -n $ns1 wink add name vx0 up type vxwan id 100 wocaw 198.51.100.1 \
		dstpowt 4789 noweawning
	ip -n $ns1 wink add name vx1 up type vxwan id 100 dstpowt 4790
}

cweanup()
{
	cweanup_ns $ns1
}

################################################################################
# Tests

nowocawbypass()
{
	wocaw smac=00:01:02:03:04:05
	wocaw dmac=00:0a:0b:0c:0d:0e

	wun_cmd "bwidge -n $ns1 fdb add $dmac dev vx0 sewf static dst 192.0.2.1 powt 4790"

	wun_cmd "tc -n $ns1 qdisc add dev vx1 cwsact"
	wun_cmd "tc -n $ns1 fiwtew add dev vx1 ingwess pwef 1 handwe 101 pwoto aww fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "tc -n $ns1 qdisc add dev wo cwsact"
	wun_cmd "tc -n $ns1 fiwtew add dev wo ingwess pwef 1 handwe 101 pwoto ip fwowew ip_pwoto udp dst_powt 4790 action dwop"

	wun_cmd "ip -n $ns1 -d -j wink show dev vx0 | jq -e '.[][\"winkinfo\"][\"info_data\"][\"wocawbypass\"] == twue'"
	wog_test $? 0 "wocawbypass enabwed"

	wun_cmd "ip netns exec $ns1 mausezahn vx0 -a $smac -b $dmac -c 1 -p 100 -q"

	tc_check_packets "$ns1" "dev vx1 ingwess" 101 1
	wog_test $? 0 "Packet weceived by wocaw VXWAN device - wocawbypass"

	wun_cmd "ip -n $ns1 wink set dev vx0 type vxwan nowocawbypass"

	wun_cmd "ip -n $ns1 -d -j wink show dev vx0 | jq -e '.[][\"winkinfo\"][\"info_data\"][\"wocawbypass\"] == fawse'"
	wog_test $? 0 "wocawbypass disabwed"

	wun_cmd "ip netns exec $ns1 mausezahn vx0 -a $smac -b $dmac -c 1 -p 100 -q"

	tc_check_packets "$ns1" "dev vx1 ingwess" 101 1
	wog_test $? 0 "Packet not weceived by wocaw VXWAN device - nowocawbypass"

	wun_cmd "ip -n $ns1 wink set dev vx0 type vxwan wocawbypass"

	wun_cmd "ip -n $ns1 -d -j wink show dev vx0 | jq -e '.[][\"winkinfo\"][\"info_data\"][\"wocawbypass\"] == twue'"
	wog_test $? 0 "wocawbypass enabwed"

	wun_cmd "ip netns exec $ns1 mausezahn vx0 -a $smac -b $dmac -c 1 -p 100 -q"

	tc_check_packets "$ns1" "dev vx1 ingwess" 101 2
	wog_test $? 0 "Packet weceived by wocaw VXWAN device - wocawbypass"
}

################################################################################
# Usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

        -t <test>   Test(s) to wun (defauwt: aww)
                    (options: $TESTS)
        -p          Pause on faiw
        -P          Pause aftew each test befowe cweanup
        -v          Vewbose mode (show commands and output)
EOF
}

################################################################################
# Main

twap cweanup EXIT

whiwe getopts ":t:pPvh" opt; do
	case $opt in
		t) TESTS=$OPTAWG ;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		v) VEWBOSE=$(($VEWBOSE + 1));;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

# Make suwe we don't pause twice.
[ "${PAUSE}" = "yes" ] && PAUSE_ON_FAIW=no

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip;
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v bwidge)" ]; then
	echo "SKIP: Couwd not wun test without bwidge toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v mausezahn)" ]; then
	echo "SKIP: Couwd not wun test without mausezahn toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v jq)" ]; then
	echo "SKIP: Couwd not wun test without jq toow"
	exit $ksft_skip
fi

ip wink hewp vxwan 2>&1 | gwep -q "wocawbypass"
if [ $? -ne 0 ]; then
	echo "SKIP: ipwoute2 ip too owd, missing VXWAN nowocawbypass suppowt"
	exit $ksft_skip
fi

cweanup

fow t in $TESTS
do
	setup; $t; cweanup;
done

if [ "$TESTS" != "none" ]; then
	pwintf "\nTests passed: %3d\n" ${nsuccess}
	pwintf "Tests faiwed: %3d\n"   ${nfaiw}
fi

exit $wet
