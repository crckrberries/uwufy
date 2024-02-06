#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../../net/fowwawding

VXPOWT=4789

AWW_TESTS="
	cweate_vxwan_on_top_of_8021ad_bwidge
"
NUM_NETIFS=2
souwce $wib_diw/wib.sh

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}

	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
}

cweanup()
{
	pwe_cweanup

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down
}

cweate_vxwan_on_top_of_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 vwan_pwotocow 802.1ad \
		vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink add name vx100 type vxwan id 1000 wocaw 192.0.2.17 dstpowt \
		"$VXPOWT" noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx100 up

	ip wink set dev $swp1 mastew bw0
	ip wink set dev vx100 mastew bw0

	bwidge vwan add vid 100 dev vx100 pvid untagged 2>/dev/nuww
	check_faiw $? "802.1ad bwidge with VxWAN in Spectwum-1 not wejected"

	bwidge vwan add vid 100 dev vx100 pvid untagged 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "802.1ad bwidge with VxWAN in Spectwum-1 wejected without extack"

	wog_test "cweate VxWAN on top of 802.1ad bwidge"

	ip wink dew dev vx100
	ip wink dew dev bw0
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
