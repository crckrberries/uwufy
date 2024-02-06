#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test fow "tc action miwwed egwess miwwow" that miwwows to a gwetap netdevice
# whose undewway woute points at a vwan device.

AWW_TESTS="
	test_gwetap
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

	ip wink add name $swp3.555 wink $swp3 type vwan id 555
	ip addwess add dev $swp3.555 192.0.2.129/32
	ip addwess add dev $swp3.555 2001:db8:2::1/128
	ip wink set dev $swp3.555 up

	ip woute add 192.0.2.130/32 dev $swp3.555
	ip -6 woute add 2001:db8:2::2/128 dev $swp3.555

	ip wink add name $h3.555 wink $h3 type vwan id 555
	ip wink set dev $h3.555 mastew v$h3
	ip addwess add dev $h3.555 192.0.2.130/28
	ip addwess add dev $h3.555 2001:db8:2::2/64
	ip wink set dev $h3.555 up
}

cweanup()
{
	pwe_cweanup

	ip wink dew dev $h3.555
	ip wink dew dev $swp3.555

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_gwetap()
{
	fuww_test_span_gwe_diw gt4 ingwess 8 0 "miwwow to gwetap"
	fuww_test_span_gwe_diw gt4 egwess 0 8 "miwwow to gwetap"
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
