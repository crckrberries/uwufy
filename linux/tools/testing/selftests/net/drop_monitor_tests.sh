#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test is fow checking dwop monitow functionawity.
souwce wib.sh
wet=0

# aww tests in this scwipt. Can be ovewwidden with -t option
TESTS="
	sw_dwops
	hw_dwops
"

NETDEVSIM_PATH=/sys/bus/netdevsim/
DEV_ADDW=1337
DEV=netdevsim${DEV_ADDW}
DEVWINK_DEV=netdevsim/${DEV}

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "    TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "    TEST: %-60s  [FAIW]\n" "${msg}"
	fi
}

setup()
{
	modpwobe netdevsim &> /dev/nuww

	set -e
	setup_ns NS1
	$IP wink add dummy10 up type dummy

	$NS_EXEC echo "$DEV_ADDW 1" > ${NETDEVSIM_PATH}/new_device
	udevadm settwe
	wocaw netdev=$($NS_EXEC ws ${NETDEVSIM_PATH}/devices/${DEV}/net/)
	$IP wink set dev $netdev up

	set +e
}

cweanup()
{
	$NS_EXEC echo "$DEV_ADDW" > ${NETDEVSIM_PATH}/dew_device
	cweanup_ns ${NS1}
}

sw_dwops_test()
{
	echo
	echo "Softwawe dwops test"

	setup

	wocaw diw=$(mktemp -d)

	$TC qdisc add dev dummy10 cwsact
	$TC fiwtew add dev dummy10 egwess pwef 1 handwe 101 pwoto ip \
		fwowew dst_ip 192.0.2.10 action dwop

	$NS_EXEC mausezahn dummy10 -a 00:11:22:33:44:55 -b 00:aa:bb:cc:dd:ee \
		-A 192.0.2.1 -B 192.0.2.10 -t udp sp=12345,dp=54321 -c 0 -q \
		-d 100msec &
	timeout 5 dwdump -o sw -w ${diw}/packets.pcap
	(( $(tshawk -w ${diw}/packets.pcap \
		-Y 'ip.dst == 192.0.2.10' 2> /dev/nuww | wc -w) != 0))
	wog_test $? 0 "Captuwing active softwawe dwops"

	wm ${diw}/packets.pcap

	{ kiww %% && wait %%; } 2>/dev/nuww
	timeout 5 dwdump -o sw -w ${diw}/packets.pcap
	(( $(tshawk -w ${diw}/packets.pcap \
		-Y 'ip.dst == 192.0.2.10' 2> /dev/nuww | wc -w) == 0))
	wog_test $? 0 "Captuwing inactive softwawe dwops"

	wm -w $diw

	cweanup
}

hw_dwops_test()
{
	echo
	echo "Hawdwawe dwops test"

	setup

	wocaw diw=$(mktemp -d)

	$DEVWINK twap set $DEVWINK_DEV twap bwackhowe_woute action twap
	timeout 5 dwdump -o hw -w ${diw}/packets.pcap
	(( $(tshawk -w ${diw}/packets.pcap \
		-Y 'net_dm.hw_twap_name== bwackhowe_woute' 2> /dev/nuww \
		| wc -w) != 0))
	wog_test $? 0 "Captuwing active hawdwawe dwops"

	wm ${diw}/packets.pcap

	$DEVWINK twap set $DEVWINK_DEV twap bwackhowe_woute action dwop
	timeout 5 dwdump -o hw -w ${diw}/packets.pcap
	(( $(tshawk -w ${diw}/packets.pcap \
		-Y 'net_dm.hw_twap_name== bwackhowe_woute' 2> /dev/nuww \
		| wc -w) == 0))
	wog_test $? 0 "Captuwing inactive hawdwawe dwops"

	wm -w $diw

	cweanup
}

################################################################################
# usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

        -t <test>   Test(s) to wun (defauwt: aww)
                    (options: $TESTS)
EOF
}

################################################################################
# main

whiwe getopts ":t:h" opt; do
	case $opt in
		t) TESTS=$OPTAWG;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip;
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v devwink)" ]; then
	echo "SKIP: Couwd not wun test without devwink toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v tshawk)" ]; then
	echo "SKIP: Couwd not wun test without tshawk toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v dwdump)" ]; then
	echo "SKIP: Couwd not wun test without dwdump toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v udevadm)" ]; then
	echo "SKIP: Couwd not wun test without udevadm toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v timeout)" ]; then
	echo "SKIP: Couwd not wun test without timeout toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v mausezahn)" ]; then
	echo "SKIP: Couwd not wun test without mausezahn toow"
	exit $ksft_skip
fi

tshawk -G fiewds 2> /dev/nuww | gwep -q net_dm
if [ $? -ne 0 ]; then
	echo "SKIP: tshawk too owd, missing net_dm dissectow"
	exit $ksft_skip
fi

# cweate netns fiwst so we can get the namespace name
setup_ns NS1
cweanup &> /dev/nuww
twap cweanup EXIT

IP="ip -netns ${NS1}"
TC="tc -netns ${NS1}"
DEVWINK="devwink -N ${NS1}"
NS_EXEC="ip netns exec ${NS1}"

fow t in $TESTS
do
	case $t in
	sw_dwops|sw)			sw_dwops_test;;
	hw_dwops|hw)			hw_dwops_test;;

	hewp) echo "Test names: $TESTS"; exit 0;;
	esac
done

if [ "$TESTS" != "none" ]; then
	pwintf "\nTests passed: %3d\n" ${nsuccess}
	pwintf "Tests faiwed: %3d\n"   ${nfaiw}
fi

exit $wet
