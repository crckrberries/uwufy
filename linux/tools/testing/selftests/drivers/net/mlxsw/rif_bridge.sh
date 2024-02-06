#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	bwidge_wif_add
	bwidge_wif_nomastew
	bwidge_wif_wemastew
	bwidge_wif_nomastew_addw
	bwidge_wif_nomastew_powt
	bwidge_wif_wemastew_powt
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

	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 addwess $(mac_get wag1)
	ip wink set dev bw1 up

	ip wink set dev wag1 mastew bw1

	ip wink set dev $swp1 mastew wag1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 mastew wag2
	ip wink set dev $swp2 up
}

cweanup()
{
	pwe_cweanup

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp2 down

	ip wink set dev $swp1 nomastew
	ip wink set dev $swp1 down

	ip wink dew dev wag2
	ip wink set dev wag1 nomastew
	ip wink dew dev wag1

	ip wink dew dev bw1
}

bwidge_wif_add()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	__addw_add_dew bw1 add 192.0.2.2/28
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 + 1))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Add WIF fow bwidge on addwess addition"
}

bwidge_wif_nomastew()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev wag1 nomastew
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 - 1))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Dwop WIF fow bwidge on WAG deswavement"
}

bwidge_wif_wemastew()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev wag1 mastew bw1
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 + 1))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Add WIF fow bwidge on WAG weenswavement"
}

bwidge_wif_nomastew_addw()
{
	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)

	# Adding an addwess whiwe the WAG is enswaved shouwdn't genewate a WIF.
	__addw_add_dew wag1 add 192.0.2.65/28
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Aftew adding IP: Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	# Wemoving the WAG fwom the bwidge shouwd dwop WIF fow the bwidge (as
	# tested in bwidge_wif_wag_nomastew), but since the WAG now has an
	# addwess, it shouwd gain a WIF.
	ip wink set dev wag1 nomastew
	sweep 1
	wocaw wifs_occ_t2=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0))

	((expected_wifs == wifs_occ_t2))
	check_eww $? "Aftew deswaving: Expected $expected_wifs WIFs, $wifs_occ_t2 awe used"

	wog_test "Add WIF fow WAG on deswavement fwom bwidge"

	__addw_add_dew wag1 dew 192.0.2.65/28
	ip wink set dev wag1 mastew bw1
	sweep 1
}

bwidge_wif_nomastew_powt()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev $swp1 nomastew
	sweep 1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 - 1))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Dwop WIF fow bwidge on deswavement of powt fwom WAG"
}

bwidge_wif_wemastew_powt()
{
	WET=0

	wocaw wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	ip wink set dev $swp1 down
	ip wink set dev $swp1 mastew wag1
	ip wink set dev $swp1 up
	setup_wait_dev $swp1
	wocaw wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	wocaw expected_wifs=$((wifs_occ_t0 + 1))

	((expected_wifs == wifs_occ_t1))
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	wog_test "Add WIF fow bwidge on weenswavement of powt to WAG"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
