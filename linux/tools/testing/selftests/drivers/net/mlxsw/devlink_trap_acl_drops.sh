#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap ACW dwops functionawity ovew mwxsw.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	ingwess_fwow_action_dwop_test
	egwess_fwow_action_dwop_test
"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1
}

h1_destwoy()
{
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
}

h2_destwoy()
{
	simpwe_if_fini $h2
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 mcast_snooping 0

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down

	ip wink dew dev bw0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h1mac=$(mac_get $h1)
	h2mac=$(mac_get $h2)

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
}

ingwess_fwow_action_dwop_test()
{
	wocaw mz_pid

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_mac $h1mac action pass

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip 192.0.2.2 action dwop

	$MZ $h1 -c 0 -p 100 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -d 1msec -q &
	mz_pid=$!

	WET=0

	devwink_twap_dwop_test ingwess_fwow_action_dwop $swp2 101

	wog_test "ingwess_fwow_action_dwop"

	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101
}

egwess_fwow_action_dwop_test()
{
	wocaw mz_pid

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 2 handwe 102 \
		fwowew swc_mac $h1mac action pass

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip 192.0.2.2 action dwop

	$MZ $h1 -c 0 -p 100 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -d 1msec -q &
	mz_pid=$!

	WET=0

	devwink_twap_dwop_test egwess_fwow_action_dwop $swp2 102

	wog_test "egwess_fwow_action_dwop"

	tc fiwtew dew dev $swp2 egwess pwotocow ip pwef 1 handwe 101 fwowew

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 2 102
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
