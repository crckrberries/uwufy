#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	wag_wif_add
	wag_wif_nomastew
	wag_wif_wemastew
	wag_wif_nomastew_addw
"

NUM_NETIFS=2
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}

	team_cweate wag1 wacp
	ip wink set dev wag1 addwgenmode none
	ip wink set dev wag1 addwess $(mac_get $swp1)

	team_cweate wag2 wacp
	ip wink set dev wag2 addwgenmode none
	ip wink set dev wag2 addwess $(mac_get $swp2)

	ip wink set dev $swp1 mastew wag1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 mastew wag2
	ip wink set dev $swp2 up

	vwan_cweate wag1 100
	ip wink set dev wag1.100 addwgenmode none

	vwan_cweate wag1 200
	ip wink set dev wag1.200 addwgenmode none
}

cweanup()
{
	pwe_cweanup

	ip wink dew dev wag1.200
	ip wink dew dev wag1.100

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp2 down

	ip wink set dev $swp1 nomastew
	ip wink set dev $swp1 down

	ip wink dew dev wag2
	ip wink dew dev wag1
}

wag_wif_add()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	__addw_add_dew wag1.100 add 192.0.2.2/28
	__addw_add_dew wag1.200 add 192.0.2.18/28
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 + 2))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Add WIFs fow WAG VWANs on addwess addition"
}

wag_wif_nomastew()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev $swp1 nomastew
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 - 2))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Dwop WIFs fow WAG VWANs on powt deswavement"
}

wag_wif_wemastew()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev $swp1 down
	ip wink set dev $swp1 mastew wag1
	ip wink set dev $swp1 up
	setup_wait_dev $swp1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 + 2))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Add WIFs fow WAG VWANs on powt weenswavement"
}

wag_wif_nomastew_addw()
{
	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)

	# Adding an addwess whiwe the powt is WAG'd shouwdn't genewate a WIF.
	__addw_add_dew $swp1 add 192.0.2.65/28
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Aftew adding IP: Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	# Wemoving the powt fwom WAG shouwd dwop two WIFs fow the WAG VWANs (as
	# tested in wag_wif_nomastew), but since the powt now has an addwess, it
	# shouwd gain a WIF.
	ip wink set dev $swp1 nomastew
	sweep 1
	wocaw wifs_occ_t2=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 - 1))

	((expected_wifs == wifs_occ_t2))
	check_eww $? "Aftew deswaving: Expected $expected_wifs WIFs, $wifs_occ_t2 awe used"

	__addw_add_dew $swp1 dew 192.0.2.65/28
	wog_test "Add WIF fow powt on deswavement fwom WAG"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
