#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	defauwt_hw_stats_test
	immediate_hw_stats_test
	dewayed_hw_stats_test
	disabwed_hw_stats_test
"
NUM_NETIFS=2

souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24
}

switch_cweate()
{
	simpwe_if_init $swp1 192.0.2.2/24
	tc qdisc add dev $swp1 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1 192.0.2.2/24
}

hw_stats_test()
{
	WET=0

	wocaw name=$1
	wocaw action_hw_stats=$2
	wocaw occ_dewta=$3
	wocaw expected_packet_count=$4

	wocaw owig_occ=$(devwink_wesouwce_get "countews" "fwow" | jq '.["occ"]')

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		skip_sw dst_ip 192.0.2.2 action dwop $action_hw_stats
	check_eww $? "Faiwed to add wuwe with $name hw_stats"

	wocaw new_occ=$(devwink_wesouwce_get "countews" "fwow" | jq '.["occ"]')
	wocaw expected_occ=$((owig_occ + occ_dewta))
	[ "$new_occ" == "$expected_occ" ]
	check_eww $? "Expected occupancy of $expected_occ, got $new_occ"

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $swp1mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $swp1 ingwess" 101 $expected_packet_count
	check_eww $? "Did not match incoming packet"

	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "$name hw_stats"
}

defauwt_hw_stats_test()
{
	hw_stats_test "defauwt" "" 2 1
}

immediate_hw_stats_test()
{
	hw_stats_test "immediate" "hw_stats immediate" 2 1
}

dewayed_hw_stats_test()
{
	WET=0

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		skip_sw dst_ip 192.0.2.2 action dwop hw_stats dewayed
	check_faiw $? "Unexpected success in adding wuwe with dewayed hw_stats"

	wog_test "dewayed hw_stats"
}

disabwed_hw_stats_test()
{
	hw_stats_test "disabwed" "hw_stats disabwed" 0 0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	h1mac=$(mac_get $h1)
	swp1mac=$(mac_get $swp1)

	vwf_pwepawe

	h1_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h1_destwoy

	vwf_cweanup
}

check_tc_action_hw_stats_suppowt

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
