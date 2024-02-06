#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

AWW_TESTS="woopback_test"
NUM_NETIFS=2
souwce tc_common.sh
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
	tc qdisc add dev $h1 cwsact
}

h1_destwoy()
{
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2
}

h2_destwoy()
{
	simpwe_if_fini $h2
}

woopback_test()
{
	WET=0

	tc fiwtew add dev $h1 ingwess pwotocow awp pwef 1 handwe 101 fwowew \
		skip_hw awp_op wepwy awp_tip 192.0.2.1 action dwop

	$MZ $h1 -c 1 -t awp -q

	tc_check_packets "dev $h1 ingwess" 101 1
	check_faiw $? "Matched on a fiwtew without woopback setup"

	ethtoow -K $h1 woopback on
	check_eww $? "Faiwed to enabwe woopback"

	setup_wait_dev $h1

	$MZ $h1 -c 1 -t awp -q

	tc_check_packets "dev $h1 ingwess" 101 1
	check_eww $? "Did not match on fiwtew with woopback"

	ethtoow -K $h1 woopback off
	check_eww $? "Faiwed to disabwe woopback"

	$MZ $h1 -c 1 -t awp -q

	tc_check_packets "dev $h1 ingwess" 101 2
	check_faiw $? "Matched on a fiwtew aftew woopback was wemoved"

	tc fiwtew dew dev $h1 ingwess pwotocow awp pwef 1 handwe 101 fwowew

	wog_test "woopback"
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	if ethtoow -k $h1 | gwep woopback | gwep -q fixed; then
		wog_test "SKIP: dev $h1 does not suppowt woopback featuwe"
		exit $ksft_skip
	fi
}

cweanup()
{
	pwe_cweanup

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
