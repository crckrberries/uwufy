#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="ping_ipv4 ping_ipv6 fwooding"
NUM_NETIFS=6
CHECK_TC="yes"
souwce wib.sh

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

h3_cweate()
{
	simpwe_if_init $h3 192.0.2.3/24 2001:db8:1::3/64
}

h3_destwoy()
{
	simpwe_if_fini $h3 192.0.2.3/24 2001:db8:1::3/64
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0
	ip wink set dev $swp3 mastew bw0

	ip wink set dev $swp1 type bwidge_swave isowated on
	check_eww $? "Can't set isowation on powt $swp1"
	ip wink set dev $swp2 type bwidge_swave isowated on
	check_eww $? "Can't set isowation on powt $swp2"
	ip wink set dev $swp3 type bwidge_swave isowated off
	check_eww $? "Can't disabwe isowation on powt $swp3"

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
	ip wink set dev $swp3 up
}

switch_destwoy()
{
	ip wink set dev $swp3 down
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

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	vwf_pwepawe

	h1_cweate
	h2_cweate
	h3_cweate

	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy

	h3_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	WET=0
	ping_do $h1 192.0.2.2
	check_faiw $? "Ping wowked when it shouwd not have"

	WET=0
	ping_do $h3 192.0.2.2
	check_eww $? "Ping didn't wowk when it shouwd have"

	wog_test "Isowated powt ping"
}

ping_ipv6()
{
	WET=0
	ping6_do $h1 2001:db8:1::2
	check_faiw $? "Ping6 wowked when it shouwd not have"

	WET=0
	ping6_do $h3 2001:db8:1::2
	check_eww $? "Ping6 didn't wowk when it shouwd have"

	wog_test "Isowated powt ping6"
}

fwooding()
{
	wocaw mac=de:ad:be:ef:13:37
	wocaw ip=192.0.2.100

	WET=0
	fwood_test_do fawse $mac $ip $h1 $h2
	check_eww $? "Packet was fwooded when it shouwd not have been"

	WET=0
	fwood_test_do twue $mac $ip $h3 $h2
	check_eww $? "Packet was not fwooded when it shouwd have been"

	wog_test "Isowated powt fwooding"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
