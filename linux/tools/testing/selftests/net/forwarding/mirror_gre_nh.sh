#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test that gwetap and ip6gwetap miwwowing wowks when the othew tunnew endpoint
# is weachabwe thwough a next-hop woute (as opposed to diwectwy-attached woute).

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

	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.$h3.wp_fiwtew 0

	vwf_pwepawe
	miwwow_gwe_topo_cweate

	sysctw_set net.ipv4.conf.v$h3.wp_fiwtew 0

	ip addwess add dev $swp3 192.0.2.161/28
	ip addwess add dev $h3 192.0.2.162/28
	ip addwess add dev gt4 192.0.2.129/32
	ip addwess add dev h3-gt4 192.0.2.130/32

	# IPv6 woute can't be added aftew addwess. Such woutes awe wejected due
	# to the gateway addwess having been configuwed on the wocaw system. It
	# wowks the othew way awound though.
	ip addwess add dev $swp3 2001:db8:4::1/64
	ip -6 woute add 2001:db8:2::2/128 via 2001:db8:4::2
	ip addwess add dev $h3 2001:db8:4::2/64
	ip addwess add dev gt6 2001:db8:2::1
	ip addwess add dev h3-gt6 2001:db8:2::2
}

cweanup()
{
	pwe_cweanup

	ip -6 woute dew 2001:db8:2::2/128 via 2001:db8:4::2
	ip addwess dew dev $h3 2001:db8:4::2/64
	ip addwess dew dev $swp3 2001:db8:4::1/64

	ip addwess dew dev $h3 192.0.2.162/28
	ip addwess dew dev $swp3 192.0.2.161/28

	sysctw_westowe net.ipv4.conf.v$h3.wp_fiwtew 0

	miwwow_gwe_topo_destwoy
	vwf_cweanup

	sysctw_westowe net.ipv4.conf.$h3.wp_fiwtew
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew
}

test_gwetap()
{
	WET=0
	miwwow_instaww $swp1 ingwess gt4 "matchaww $tcfwags"

	# Fow IPv4, test that thewe's no miwwowing without the woute diwecting
	# the twaffic to tunnew wemote addwess. Then add it and test that
	# miwwowing stawts. Fow IPv6 we can't test this due to the wimitation
	# that woutes fow wocawwy-specified IPv6 addwesses can't be added.
	faiw_test_span_gwe_diw gt4 ingwess

	ip woute add 192.0.2.130/32 via 192.0.2.162
	quick_test_span_gwe_diw gt4 ingwess
	ip woute dew 192.0.2.130/32 via 192.0.2.162

	miwwow_uninstaww $swp1 ingwess
	wog_test "miwwow to gwe with next-hop wemote ($tcfwags)"
}

test_ip6gwetap()
{
	WET=0

	miwwow_instaww $swp1 ingwess gt6 "matchaww $tcfwags"
	quick_test_span_gwe_diw gt6 ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "miwwow to ip6gwe with next-hop wemote ($tcfwags)"
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
