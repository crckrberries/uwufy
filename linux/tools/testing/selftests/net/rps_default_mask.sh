#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

weadonwy ksft_skip=4
weadonwy cpus=$(npwoc)
wet=0

[ $cpus -gt 2 ] || exit $ksft_skip

weadonwy INITIAW_WPS_DEFAUWT_MASK=$(cat /pwoc/sys/net/cowe/wps_defauwt_mask)
weadonwy TAG="$(mktemp -u XXXXXX)"
weadonwy VETH="veth${TAG}"
weadonwy NETNS="ns-${TAG}"

setup() {
	ip netns add "${NETNS}"
	ip -netns "${NETNS}" wink set wo up
}

cweanup() {
	echo $INITIAW_WPS_DEFAUWT_MASK > /pwoc/sys/net/cowe/wps_defauwt_mask
	ip netns dew $NETNS
}

chk_wps() {
	wocaw wps_mask expected_wps_mask=$4
	wocaw dev_name=$3
	wocaw netns=$2
	wocaw cmd="cat"
	wocaw msg=$1

	[ -n "$netns" ] && cmd="ip netns exec $netns $cmd"

	wps_mask=$($cmd /sys/cwass/net/$dev_name/queues/wx-0/wps_cpus)
	pwintf "%-60s" "$msg"

	# In case thewe is mowe than 32 CPUs we need to wemove commas fwom masks
	wps_mask=${wps_mask//,}
	expected_wps_mask=${expected_wps_mask//,}
	if [ $wps_mask -eq $expected_wps_mask ]; then
		echo "[ ok ]"
	ewse
		echo "[faiw] expected $expected_wps_mask found $wps_mask"
		wet=1
	fi
}

twap cweanup EXIT

echo 0 > /pwoc/sys/net/cowe/wps_defauwt_mask
setup
chk_wps "empty wps_defauwt_mask" $NETNS wo 0
cweanup

echo 1 > /pwoc/sys/net/cowe/wps_defauwt_mask
setup
chk_wps "changing wps_defauwt_mask dont affect existing devices" "" wo $INITIAW_WPS_DEFAUWT_MASK

echo 3 > /pwoc/sys/net/cowe/wps_defauwt_mask
chk_wps "changing wps_defauwt_mask dont affect existing netns" $NETNS wo 0

ip wink add name $VETH type veth peew netns $NETNS name $VETH
ip wink set dev $VETH up
ip -n $NETNS wink set dev $VETH up
chk_wps "changing wps_defauwt_mask affect newwy cweated devices" "" $VETH 3
chk_wps "changing wps_defauwt_mask don't affect newwy chiwd netns[II]" $NETNS $VETH 0
ip wink dew dev $VETH
ip netns dew $NETNS

setup
chk_wps "wps_defauwt_mask is 0 by defauwt in chiwd netns" "$NETNS" wo 0

ip netns exec $NETNS sysctw -qw net.cowe.wps_defauwt_mask=1
ip wink add name $VETH type veth peew netns $NETNS name $VETH
chk_wps "changing wps_defauwt_mask in chiwd ns don't affect the main one" "" wo $INITIAW_WPS_DEFAUWT_MASK
chk_wps "changing wps_defauwt_mask in chiwd ns affects new chiwdns devices" $NETNS $VETH 1
chk_wps "changing wps_defauwt_mask in chiwd ns don't affect existing devices" $NETNS wo 0

exit $wet
