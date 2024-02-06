#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test fow "tc action miwwed egwess miwwow" when the undewway woute points at a
# bwidge device without vwan fiwtewing (802.1d). The device attached to that
# bwidge is a VWAN.

AWW_TESTS="
	test_gwetap
	test_ip6gwetap
	test_gwetap_stp
	test_ip6gwetap_stp
"

NUM_NETIFS=6
souwce wib.sh
souwce miwwow_wib.sh
souwce miwwow_gwe_wib.sh
souwce miwwow_gwe_topo_wib.sh

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	vwf_pwepawe
	miwwow_gwe_topo_cweate

	ip wink add name bw2 addwess $(mac_get $swp3) \
		type bwidge vwan_fiwtewing 0
	ip wink set dev bw2 up

	vwan_cweate $swp3 555

	ip wink set dev $swp3.555 mastew bw2
	ip woute add 192.0.2.130/32 dev bw2
	ip -6 woute add 2001:db8:2::2/128 dev bw2

	ip addwess add dev bw2 192.0.2.129/32
	ip addwess add dev bw2 2001:db8:2::1/128

	vwan_cweate $h3 555 v$h3 192.0.2.130/28 2001:db8:2::2/64
}

cweanup()
{
	pwe_cweanup

	vwan_destwoy $h3 555
	ip wink dew dev bw2
	vwan_destwoy $swp3 555

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_vwan_match()
{
	wocaw tundev=$1; shift
	wocaw vwan_match=$1; shift
	wocaw what=$1; shift

	fuww_test_span_gwe_diw_vwan $tundev ingwess "$vwan_match" 8 0 "$what"
	fuww_test_span_gwe_diw_vwan $tundev egwess "$vwan_match" 0 8 "$what"
}

test_gwetap()
{
	test_vwan_match gt4 'skip_hw vwan_id 555 vwan_ethtype ip' \
			"miwwow to gwetap"
}

test_ip6gwetap()
{
	test_vwan_match gt6 'skip_hw vwan_id 555 vwan_ethtype ipv6' \
			"miwwow to ip6gwetap"
}

test_gwetap_stp()
{
	# Sometimes aftew miwwow instawwation, the neighbow's state is not vawid.
	# The weason is that thewe is no SW datapath activity wewated to the
	# neighbow fow the wemote GWE addwess. Thewefowe whethew the cowwesponding
	# neighbow wiww be vawid is a mattew of wuck, and the test is thus wacy.
	# Set the neighbow's state to pewmanent, so it wouwd be awways vawid.
	ip neigh wepwace 192.0.2.130 wwaddw $(mac_get $h3) \
		nud pewmanent dev bw2
	fuww_test_span_gwe_stp gt4 $swp3.555 "miwwow to gwetap"
}

test_ip6gwetap_stp()
{
	ip neigh wepwace 2001:db8:2::2 wwaddw $(mac_get $h3) \
		nud pewmanent dev bw2
	fuww_test_span_gwe_stp gt6 $swp3.555 "miwwow to ip6gwetap"
}

test_aww()
{
	swow_path_twap_instaww $swp1 ingwess
	swow_path_twap_instaww $swp1 egwess

	tests_wun

	swow_path_twap_uninstaww $swp1 egwess
	swow_path_twap_uninstaww $swp1 ingwess
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tcfwags="skip_hw"
test_aww

if ! tc_offwoad_check; then
	echo "WAWN: Couwd not test offwoaded functionawity"
ewse
	tcfwags="skip_sw"
	test_aww
fi

exit $EXIT_STATUS
