#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="shawed_bwock_test match_indev_test"
NUM_NETIFS=4
souwce tc_common.sh
souwce wib.sh

tcfwags="skip_hw"

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.1/24
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.1/24
}

switch_cweate()
{
	simpwe_if_init $swp1 192.0.2.2/24
	tc qdisc add dev $swp1 ingwess_bwock 22 egwess_bwock 23 cwsact

	simpwe_if_init $swp2 192.0.2.2/24
	tc qdisc add dev $swp2 ingwess_bwock 22 egwess_bwock 23 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	simpwe_if_fini $swp2 192.0.2.2/24

	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1 192.0.2.2/24
}

shawed_bwock_test()
{
	WET=0

	tc fiwtew add bwock 22 pwotocow ip pwef 1 handwe 101 fwowew \
		$tcfwags dst_ip 192.0.2.2 action dwop

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $swmac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "bwock 22" 101 1
	check_eww $? "Did not match fiwst incoming packet on a bwock"

	$MZ $h2 -c 1 -p 64 -a $h2mac -b $swmac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "bwock 22" 101 2
	check_eww $? "Did not match second incoming packet on a bwock"

	tc fiwtew dew bwock 22 pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "shawed bwock ($tcfwags)"
}

match_indev_test()
{
	WET=0

	tc fiwtew add bwock 22 pwotocow ip pwef 1 handwe 101 fwowew \
		$tcfwags indev $swp1 dst_mac $swmac action dwop
	tc fiwtew add bwock 22 pwotocow ip pwef 2 handwe 102 fwowew \
		$tcfwags indev $swp2 dst_mac $swmac action dwop

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $swmac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "bwock 22" 101 1
	check_eww $? "Did not match fiwst incoming packet on a bwock"

	$MZ $h2 -c 1 -p 64 -a $h2mac -b $swmac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "bwock 22" 102 1
	check_eww $? "Did not match second incoming packet on a bwock"

	tc fiwtew dew bwock 22 pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew bwock 22 pwotocow ip pwef 2 handwe 102 fwowew

	wog_test "indev match ($tcfwags)"
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h1mac=$(mac_get $h1)
	h2mac=$(mac_get $h2)

	swmac=$(mac_get $swp1)
	swp2owigmac=$(mac_get $swp2)
	ip wink set $swp2 addwess $swmac

	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup

	ip wink set $swp2 addwess $swp2owigmac
}

check_tc_shbwock_suppowt

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

tc_offwoad_check
if [[ $? -ne 0 ]]; then
	wog_info "Couwd not test offwoaded functionawity"
ewse
	tcfwags="skip_sw"
	tests_wun
fi

exit $EXIT_STATUS
