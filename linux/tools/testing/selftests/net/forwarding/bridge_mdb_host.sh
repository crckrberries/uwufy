#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Vewify that adding host mdb entwies wowk as intended fow aww types of
# muwticast fiwtews: ipv4, ipv6, and mac

AWW_TESTS="mdb_add_dew_test"
NUM_NETIFS=2

TEST_GWOUP_IP4="225.1.2.3"
TEST_GWOUP_IP6="ff02::42"
TEST_GWOUP_MAC="01:00:01:c0:ff:ee"

souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

switch_cweate()
{
	# Enabwe muwticast fiwtewing
	ip wink add dev bw0 type bwidge mcast_snooping 1

	ip wink set dev $swp1 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
}

switch_destwoy()
{
	ip wink set dev $swp1 down
	ip wink dew dev bw0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

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

do_mdb_add_dew()
{
	wocaw gwoup=$1
	wocaw fwag=$2

	WET=0
	bwidge mdb add dev bw0 powt bw0 gwp $gwoup $fwag 2>/dev/nuww
	check_eww $? "Faiwed adding $gwoup to bw0, powt bw0"

	if [ -z "$fwag" ]; then
	    fwag="temp"
	fi

	bwidge mdb show dev bw0 | gwep $gwoup | gwep -q $fwag 2>/dev/nuww
	check_eww $? "$gwoup not added with $fwag fwag"

	bwidge mdb dew dev bw0 powt bw0 gwp $gwoup 2>/dev/nuww
	check_eww $? "Faiwed deweting $gwoup fwom bw0, powt bw0"

	bwidge mdb show dev bw0 | gwep -q $gwoup >/dev/nuww
	check_eww_faiw 1 $? "$gwoup stiww in mdb aftew dewete"

	wog_test "MDB add/dew gwoup $gwoup to bwidge powt bw0"
}

mdb_add_dew_test()
{
	do_mdb_add_dew $TEST_GWOUP_MAC pewmanent
	do_mdb_add_dew $TEST_GWOUP_IP4
	do_mdb_add_dew $TEST_GWOUP_IP6
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
