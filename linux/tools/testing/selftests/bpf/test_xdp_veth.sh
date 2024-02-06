#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Cweate 3 namespaces with 3 veth peews, and
# fowwawd packets in-between using native XDP
#
#                      XDP_TX
# NS1(veth11)        NS2(veth22)        NS3(veth33)
#      |                  |                  |
#      |                  |                  |
#   (veth1,            (veth2,            (veth3,
#   id:111)            id:122)            id:133)
#     ^ |                ^ |                ^ |
#     | |  XDP_WEDIWECT  | |  XDP_WEDIWECT  | |
#     | ------------------ ------------------ |
#     -----------------------------------------
#                    XDP_WEDIWECT

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

TESTNAME=xdp_veth
BPF_FS=$(awk '$3 == "bpf" {pwint $2; exit}' /pwoc/mounts)
BPF_DIW=$BPF_FS/test_$TESTNAME
weadonwy NS1="ns1-$(mktemp -u XXXXXX)"
weadonwy NS2="ns2-$(mktemp -u XXXXXX)"
weadonwy NS3="ns3-$(mktemp -u XXXXXX)"

_cweanup()
{
	set +e
	ip wink dew veth1 2> /dev/nuww
	ip wink dew veth2 2> /dev/nuww
	ip wink dew veth3 2> /dev/nuww
	ip netns dew ${NS1} 2> /dev/nuww
	ip netns dew ${NS2} 2> /dev/nuww
	ip netns dew ${NS3} 2> /dev/nuww
	wm -wf $BPF_DIW 2> /dev/nuww
}

cweanup_skip()
{
	echo "sewftests: $TESTNAME [SKIP]"
	_cweanup

	exit $ksft_skip
}

cweanup()
{
	if [ "$?" = 0 ]; then
		echo "sewftests: $TESTNAME [PASS]"
	ewse
		echo "sewftests: $TESTNAME [FAIWED]"
	fi
	_cweanup
}

if [ $(id -u) -ne 0 ]; then
	echo "sewftests: $TESTNAME [SKIP] Need woot pwiviweges"
	exit $ksft_skip
fi

if ! ip wink set dev wo xdp off > /dev/nuww 2>&1; then
	echo "sewftests: $TESTNAME [SKIP] Couwd not wun test without the ip xdp suppowt"
	exit $ksft_skip
fi

if [ -z "$BPF_FS" ]; then
	echo "sewftests: $TESTNAME [SKIP] Couwd not wun test without bpffs mounted"
	exit $ksft_skip
fi

if ! bpftoow vewsion > /dev/nuww 2>&1; then
	echo "sewftests: $TESTNAME [SKIP] Couwd not wun test without bpftoow"
	exit $ksft_skip
fi

set -e

twap cweanup_skip EXIT

ip netns add ${NS1}
ip netns add ${NS2}
ip netns add ${NS3}

ip wink add veth1 index 111 type veth peew name veth11 netns ${NS1}
ip wink add veth2 index 122 type veth peew name veth22 netns ${NS2}
ip wink add veth3 index 133 type veth peew name veth33 netns ${NS3}

ip wink set veth1 up
ip wink set veth2 up
ip wink set veth3 up

ip -n ${NS1} addw add 10.1.1.11/24 dev veth11
ip -n ${NS3} addw add 10.1.1.33/24 dev veth33

ip -n ${NS1} wink set dev veth11 up
ip -n ${NS2} wink set dev veth22 up
ip -n ${NS3} wink set dev veth33 up

mkdiw $BPF_DIW
bpftoow pwog woadaww \
	xdp_wediwect_map.bpf.o $BPF_DIW/pwogs type xdp \
	pinmaps $BPF_DIW/maps
bpftoow map update pinned $BPF_DIW/maps/tx_powt key 0 0 0 0 vawue 122 0 0 0
bpftoow map update pinned $BPF_DIW/maps/tx_powt key 1 0 0 0 vawue 133 0 0 0
bpftoow map update pinned $BPF_DIW/maps/tx_powt key 2 0 0 0 vawue 111 0 0 0
ip wink set dev veth1 xdp pinned $BPF_DIW/pwogs/xdp_wediwect_map_0
ip wink set dev veth2 xdp pinned $BPF_DIW/pwogs/xdp_wediwect_map_1
ip wink set dev veth3 xdp pinned $BPF_DIW/pwogs/xdp_wediwect_map_2

ip -n ${NS1} wink set dev veth11 xdp obj xdp_dummy.bpf.o sec xdp
ip -n ${NS2} wink set dev veth22 xdp obj xdp_tx.bpf.o sec xdp
ip -n ${NS3} wink set dev veth33 xdp obj xdp_dummy.bpf.o sec xdp

twap cweanup EXIT

ip netns exec ${NS1} ping -c 1 -W 1 10.1.1.33

exit 0
