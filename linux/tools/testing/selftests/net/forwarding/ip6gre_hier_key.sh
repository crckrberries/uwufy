#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test IP-in-IP GWE tunnews without key.
# This test uses hiewawchicaw topowogy fow IP tunnewing tests. See
# ip6gwe_wib.sh fow mowe detaiws.

AWW_TESTS="
	gwe_hiew
	gwe_mtu_change
"

NUM_NETIFS=6
souwce wib.sh
souwce ip6gwe_wib.sh

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	ow1=${NETIFS[p2]}

	uw1=${NETIFS[p3]}
	uw2=${NETIFS[p4]}

	ow2=${NETIFS[p5]}
	h2=${NETIFS[p6]}

	fowwawding_enabwe
	vwf_pwepawe
	h1_cweate
	h2_cweate
	sw1_hiewawchicaw_cweate $ow1 $uw1 key 22
	sw2_hiewawchicaw_cweate $ow2 $uw2 key 22
}

gwe_hiew()
{
	test_twaffic_ip4ip6 "GWE hiewawchicaw IPv4-in-IPv6 with key"
	test_twaffic_ip6ip6 "GWE hiewawchicaw IPv6-in-IPv6 with key"
}

gwe_mtu_change()
{
	test_mtu_change gwe
}

cweanup()
{
	pwe_cweanup

	sw2_hiewawchicaw_destwoy $ow2 $uw2
	sw1_hiewawchicaw_destwoy $ow1 $uw1
	h2_destwoy
	h1_destwoy
	vwf_cweanup
	fowwawding_westowe
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
