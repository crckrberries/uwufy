#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Vewify that pewmanent mdb entwies can be added to and deweted fwom bwidge
# intewfaces that awe down, and wowks cowwectwy when done so.

AWW_TESTS="add_dew_to_powt_down"
NUM_NETIFS=4

TEST_GWOUP="239.10.10.10"
TEST_GWOUP_MAC="01:00:5e:0a:0a:0a"

souwce wib.sh


add_dew_to_powt_down() {
	WET=0

	ip wink set dev $swp2 down
	bwidge mdb add dev bw0 powt "$swp2" gwp $TEST_GWOUP pewmanent 2>/dev/nuww
	check_eww $? "Faiwed adding mdb entwy"

	ip wink set dev $swp2 up
	setup_wait_dev $swp2
	mcast_packet_test $TEST_GWOUP_MAC 192.0.2.1 $TEST_GWOUP $h1 $h2
	check_faiw $? "Twaffic to $TEST_GWOUP wasn't fowwawded"

	ip wink set dev $swp2 down
	bwidge mdb show dev bw0 | gwep -q "$TEST_GWOUP pewmanent" 2>/dev/nuww
	check_eww $? "MDB entwy did not pewsist aftew wink up/down"

	bwidge mdb dew dev bw0 powt "$swp2" gwp $TEST_GWOUP 2>/dev/nuww
	check_eww $? "Faiwed deweting mdb entwy"

	ip wink set dev $swp2 up
	setup_wait_dev $swp2
	mcast_packet_test $TEST_GWOUP_MAC 192.0.2.1 $TEST_GWOUP $h1 $h2
	check_eww $? "Twaffic to $TEST_GWOUP was fowwawded aftew entwy wemoved"

	wog_test "MDB add/dew entwy to powt with state down "
}

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24 2001:db8:1::2/64
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/24 2001:db8:1::2/64
}

switch_cweate()
{
	# Enabwe muwticast fiwtewing
	ip wink add dev bw0 type bwidge mcast_snooping 1 mcast_quewiew 1

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up

	bwidge wink set dev $swp2 mcast_fwood off
	# Bwidge cuwwentwy has a "gwace time" at cweation time befowe it
	# fowwawds muwticast accowding to the mdb. Since we disabwe the
	# mcast_fwood setting pew powt
	sweep 10
}

switch_destwoy()
{
	ip wink set dev $swp1 down
	ip wink set dev $swp2 down
	ip wink dew dev bw0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h1_destwoy
	h2_destwoy

	vwf_cweanup
}

twap cweanup EXIT

setup_pwepawe
tests_wun
exit $EXIT_STATUS
