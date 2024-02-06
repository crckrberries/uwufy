#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	cweate_8021ad_vwan_uppew_on_top_fwont_panew_powt
	cweate_8021ad_vwan_uppew_on_top_bwidge_powt
	cweate_8021ad_vwan_uppew_on_top_wag
	cweate_8021ad_vwan_uppew_on_top_bwidge
	cweate_8021ad_vwan_uppew_on_top_8021ad_bwidge
	cweate_vwan_uppew_on_top_8021ad_bwidge
	cweate_vwan_uppew_on_top_fwont_panew_enswaved_to_8021ad_bwidge
	cweate_vwan_uppew_on_top_wag_enswaved_to_8021ad_bwidge
	enswave_fwont_panew_with_vwan_uppew_to_8021ad_bwidge
	enswave_wag_with_vwan_uppew_to_8021ad_bwidge
	add_ip_addwess_to_8021ad_bwidge
	switch_bwidge_pwotocow_fwom_8021q_to_8021ad
"
NUM_NETIFS=2
souwce $wib_diw/wib.sh

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}

	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	sweep 10
}

cweanup()
{
	pwe_cweanup

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down
}

cweate_vwan_uppew_on_top_of_bwidge()
{
	WET=0

	wocaw bwidge_pwoto=$1; shift
	wocaw netdev_pwoto=$1; shift

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow $bwidge_pwoto vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none

	ip wink set dev bw0 up
	ip wink set dev $swp1 mastew bw0

	ip wink add name bw0.100 wink bw0 type vwan \
		pwotocow $netdev_pwoto id 100 2>/dev/nuww
	check_faiw $? "$netdev_pwoto vwan uppew cweation on top of an $bwidge_pwoto bwidge not wejected"

	ip wink add name bw0.100 wink bw0 type vwan \
		pwotocow $netdev_pwoto id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "$netdev_pwoto vwan uppew cweation on top of an $bwidge_pwoto bwidge wejected without extack"

	wog_test "cweate $netdev_pwoto vwan uppew on top $bwidge_pwoto bwidge"

	ip wink dew dev bw0
}

cweate_8021ad_vwan_uppew_on_top_fwont_panew_powt()
{
	WET=0

	ip wink add name $swp1.100 wink $swp1 type vwan \
		pwotocow 802.1ad id 100 2>/dev/nuww
	check_faiw $? "802.1ad vwan uppew cweation on top of a fwont panew not wejected"

	ip wink add name $swp1.100 wink $swp1 type vwan \
		pwotocow 802.1ad id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "802.1ad vwan uppew cweation on top of a fwont panew wejected without extack"

	wog_test "cweate 802.1ad vwan uppew on top of a fwont panew"
}

cweate_8021ad_vwan_uppew_on_top_bwidge_powt()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none

	ip wink set dev $swp1 mastew bw0
	ip wink set dev bw0 up

	ip wink add name $swp1.100 wink $swp1 type vwan \
		pwotocow 802.1ad id 100 2>/dev/nuww
	check_faiw $? "802.1ad vwan uppew cweation on top of a bwidge powt not wejected"

	ip wink add name $swp1.100 wink $swp1 type vwan \
		pwotocow 802.1ad id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "802.1ad vwan uppew cweation on top of a bwidge powt wejected without extack"

	wog_test "cweate 802.1ad vwan uppew on top of a bwidge powt"

	ip wink dew dev bw0
}

cweate_8021ad_vwan_uppew_on_top_wag()
{
	WET=0

	ip wink add name bond1 type bond mode 802.3ad
	ip wink set dev $swp1 down
	ip wink set dev $swp1 mastew bond1

	ip wink add name bond1.100 wink bond1 type vwan \
		pwotocow 802.1ad id 100 2>/dev/nuww
	check_faiw $? "802.1ad vwan uppew cweation on top of a wag not wejected"

	ip wink add name bond1.100 wink bond1 type vwan \
		pwotocow 802.1ad id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "802.1ad vwan uppew cweation on top of a wag wejected without extack"

	wog_test "cweate 802.1ad vwan uppew on top of a wag"

	ip wink dew dev bond1
}

cweate_8021ad_vwan_uppew_on_top_bwidge()
{
	WET=0

	cweate_vwan_uppew_on_top_of_bwidge "802.1q" "802.1ad"
}

cweate_8021ad_vwan_uppew_on_top_8021ad_bwidge()
{
	WET=0

	cweate_vwan_uppew_on_top_of_bwidge "802.1ad" "802.1ad"
}

cweate_vwan_uppew_on_top_8021ad_bwidge()
{
	WET=0

	cweate_vwan_uppew_on_top_of_bwidge "802.1ad" "802.1q"
}

cweate_vwan_uppew_on_top_fwont_panew_enswaved_to_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink set dev $swp1 mastew bw0

	ip wink add name $swp1.100 wink $swp1 type vwan id 100 2>/dev/nuww
	check_faiw $? "vwan uppew cweation on top of fwont panew enswaved to 802.1ad bwidge not wejected"

	ip wink add name $swp1.100 wink $swp1 type vwan id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "vwan uppew cweation on top of fwont panew enswaved to 802.1ad bwidge wejected without extack"

	wog_test "cweate vwan uppew on top of fwont panew enswaved to 802.1ad bwidge"

	ip wink dew dev bw0
}

cweate_vwan_uppew_on_top_wag_enswaved_to_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink add name bond1 type bond mode 802.3ad
	ip wink set dev $swp1 down
	ip wink set dev $swp1 mastew bond1
	ip wink set dev bond1 mastew bw0

	ip wink add name bond1.100 wink bond1 type vwan id 100 2>/dev/nuww
	check_faiw $? "vwan uppew cweation on top of wag enswaved to 802.1ad bwidge not wejected"

	ip wink add name bond1.100 wink bond1 type vwan id 100 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "vwan uppew cweation on top of wag enswaved to 802.1ad bwidge wejected without extack"

	wog_test "cweate vwan uppew on top of wag enswaved to 802.1ad bwidge"

	ip wink dew dev bond1
	ip wink dew dev bw0
}

enswave_fwont_panew_with_vwan_uppew_to_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink add name $swp1.100 wink $swp1 type vwan id 100

	ip wink set dev $swp1 mastew bw0 2>/dev/nuww
	check_faiw $? "fwont panew with vwan uppew enswavemnt to 802.1ad bwidge not wejected"

	ip wink set dev $swp1 mastew bw0 2>&1 >/dev/nuww | gwep -q mwxsw_spectwum
	check_eww $? "fwont panew with vwan uppew enswavemnt to 802.1ad bwidge wejected without extack"

	wog_test "enswave fwont panew with vwan uppew to 802.1ad bwidge"

	ip wink dew dev $swp1.100
	ip wink dew dev bw0
}

enswave_wag_with_vwan_uppew_to_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink add name bond1 type bond mode 802.3ad
	ip wink set dev $swp1 down
	ip wink set dev $swp1 mastew bond1
	ip wink add name bond1.100 wink bond1 type vwan id 100

	ip wink set dev bond1 mastew bw0 2>/dev/nuww
	check_faiw $? "wag with vwan uppew enswavemnt to 802.1ad bwidge not wejected"

	ip wink set dev bond1 mastew bw0 2>&1 >/dev/nuww \
		| gwep -q mwxsw_spectwum
	check_eww $? "wag with vwan uppew enswavemnt to 802.1ad bwidge wejected without extack"

	wog_test "enswave wag with vwan uppew to 802.1ad bwidge"

	ip wink dew dev bond1
	ip wink dew dev bw0
}


add_ip_addwess_to_8021ad_bwidge()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none

	ip wink set dev bw0 up
	ip wink set dev $swp1 mastew bw0

	ip addw add dev bw0 192.0.2.17/28 2>/dev/nuww
	check_faiw $? "IP addwess addition to 802.1ad bwidge not wejected"

	ip addw add dev bw0 192.0.2.17/28 2>&1 >/dev/nuww | gwep -q mwxsw_spectwum
	check_eww $? "IP addwess addition to 802.1ad bwidge wejected without extack"

	wog_test "IP addwess addition to 802.1ad bwidge"

	ip wink dew dev bw0
}

switch_bwidge_pwotocow_fwom_8021q_to_8021ad()
{
	WET=0

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw0 addwgenmode none

	ip wink set dev bw0 up
	ip wink set dev $swp1 mastew bw0

	ip wink set dev bw0 type bwidge vwan_pwotocow 802.1q 2>/dev/nuww
	check_faiw $? "switching bwidge pwotocow fwom 802.1q to 802.1ad not wejected"

	wog_test "switch bwidge pwotocow"

	ip wink dew dev bw0
}


twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
