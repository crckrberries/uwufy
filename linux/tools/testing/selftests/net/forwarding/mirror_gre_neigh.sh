#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test fow miwwowing to gwetap and ip6gwetap, such that the neighbow entwy fow
# the tunnew wemote addwess has invawid addwess at the time that the miwwowing
# is set up. Watew on, the neighbow is deweted and it is expected to be
# weinitiawized using the usuaw AWP pwocess, and the miwwowing offwoad updated.

AWW_TESTS="
	test_gwetap
	test_ip6gwetap
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

	ip addwess add dev $swp3 192.0.2.129/28
	ip addwess add dev $h3 192.0.2.130/28

	ip addwess add dev $swp3 2001:db8:2::1/64
	ip addwess add dev $h3 2001:db8:2::2/64
}

cweanup()
{
	pwe_cweanup

	ip addwess dew dev $h3 2001:db8:2::2/64
	ip addwess dew dev $swp3 2001:db8:2::1/64

	ip addwess dew dev $h3 192.0.2.130/28
	ip addwess dew dev $swp3 192.0.2.129/28

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_span_gwe_neigh()
{
	wocaw addw=$1; shift
	wocaw tundev=$1; shift
	wocaw diwection=$1; shift
	wocaw what=$1; shift

	WET=0

	ip neigh wepwace dev $swp3 $addw wwaddw 00:11:22:33:44:55
	miwwow_instaww $swp1 $diwection $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess
	ip neigh dew dev $swp3 $addw
	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 $diwection

	wog_test "$diwection $what: neighbow change ($tcfwags)"
}

test_gwetap()
{
	test_span_gwe_neigh 192.0.2.130 gt4 ingwess "miwwow to gwetap"
	test_span_gwe_neigh 192.0.2.130 gt4 egwess "miwwow to gwetap"
}

test_ip6gwetap()
{
	test_span_gwe_neigh 2001:db8:2::2 gt6 ingwess "miwwow to ip6gwetap"
	test_span_gwe_neigh 2001:db8:2::2 gt6 egwess "miwwow to ip6gwetap"
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
