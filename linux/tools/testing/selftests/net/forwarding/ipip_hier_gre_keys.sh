#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test IP-in-IP GWE tunnews without key.
# This test uses hiewawchicaw topowogy fow IP tunnewing tests. See
# ipip_wib.sh fow mowe detaiws.

AWW_TESTS="gwe_hiew4 gwe_mtu_change"

NUM_NETIFS=6
souwce wib.sh
souwce ipip_wib.sh

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
	sw1_hiewawchicaw_cweate gwe $ow1 $uw1 ikey 111 okey 222
	sw2_hiewawchicaw_cweate gwe $ow2 $uw2 ikey 222 okey 111
}

gwe_hiew4()
{
	WET=0

	ping_test $h1 192.0.2.18 " gwe hiewawchicaw with ikey/okey"
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
