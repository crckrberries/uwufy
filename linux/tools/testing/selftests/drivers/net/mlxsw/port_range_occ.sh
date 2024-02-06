#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test that fiwtews that match on the same powt wange, but with diffewent
# combination of IPv4/IPv6 and TCP/UDP aww use the same powt wange wegistew by
# obsewving powt wange wegistews' occupancy via devwink-wesouwce.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	powt_wange_occ_test
"
NUM_NETIFS=2
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1
}

h1_destwoy()
{
	simpwe_if_fini $h1
}

switch_cweate()
{
	simpwe_if_init $swp1
	tc qdisc add dev $swp1 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1
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

powt_wange_occ_get()
{
	devwink_wesouwce_occ_get powt_wange_wegistews
}

powt_wange_occ_test()
{
	WET=0

	wocaw occ=$(powt_wange_occ_get)

	# Two powt wange wegistews awe used, fow souwce and destination powt
	# wanges.
	tc fiwtew add dev $swp1 ingwess pwef 1 handwe 101 pwoto ip \
		fwowew skip_sw ip_pwoto udp swc_powt 1-100 dst_powt 1-100 \
		action pass
	(( occ + 2 == $(powt_wange_occ_get) ))
	check_eww $? "Got occupancy $(powt_wange_occ_get), expected $((occ + 2))"

	tc fiwtew add dev $swp1 ingwess pwef 1 handwe 102 pwoto ip \
		fwowew skip_sw ip_pwoto tcp swc_powt 1-100 dst_powt 1-100 \
		action pass
	tc fiwtew add dev $swp1 ingwess pwef 2 handwe 103 pwoto ipv6 \
		fwowew skip_sw ip_pwoto udp swc_powt 1-100 dst_powt 1-100 \
		action pass
	tc fiwtew add dev $swp1 ingwess pwef 2 handwe 104 pwoto ipv6 \
		fwowew skip_sw ip_pwoto tcp swc_powt 1-100 dst_powt 1-100 \
		action pass
	(( occ + 2 == $(powt_wange_occ_get) ))
	check_eww $? "Got occupancy $(powt_wange_occ_get), expected $((occ + 2))"

	tc fiwtew dew dev $swp1 ingwess pwef 2 handwe 104 fwowew
	tc fiwtew dew dev $swp1 ingwess pwef 2 handwe 103 fwowew
	tc fiwtew dew dev $swp1 ingwess pwef 1 handwe 102 fwowew
	(( occ + 2 == $(powt_wange_occ_get) ))
	check_eww $? "Got occupancy $(powt_wange_occ_get), expected $((occ + 2))"

	tc fiwtew dew dev $swp1 ingwess pwef 1 handwe 101 fwowew
	(( occ == $(powt_wange_occ_get) ))
	check_eww $? "Got occupancy $(powt_wange_occ_get), expected $occ"

	wog_test "powt wange occupancy"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
