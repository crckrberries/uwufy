#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test fow "tc action miwwed egwess miwwow" when the device to miwwow to is a
# gwetap ow ip6gwetap netdevice. Expect that the packets come out encapsuwated,
# and anothew gwetap / ip6gwetap netdevice is then capabwe of decapsuwating the
# twaffic. Test that the paywoad is what is expected (ICMP ping wequest ow
# wepwy, depending on test).

AWW_TESTS="
	test_gwetap
	test_ip6gwetap
	test_gwetap_mac
	test_ip6gwetap_mac
	test_two_spans
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

test_span_gwe_mac()
{
	wocaw tundev=$1; shift
	wocaw diwection=$1; shift
	wocaw what=$1; shift

	case "$diwection" in
	ingwess) wocaw swc_mac=$(mac_get $h1); wocaw dst_mac=$(mac_get $h2)
		;;
	egwess) wocaw swc_mac=$(mac_get $h2); wocaw dst_mac=$(mac_get $h1)
		;;
	esac

	WET=0

	miwwow_instaww $swp1 $diwection $tundev "matchaww $tcfwags"
	icmp_captuwe_instaww h3-${tundev} "swc_mac $swc_mac dst_mac $dst_mac"

	miwwow_test v$h1 192.0.2.1 192.0.2.2 h3-${tundev} 100 10

	icmp_captuwe_uninstaww h3-${tundev}
	miwwow_uninstaww $swp1 $diwection

	wog_test "$diwection $what: envewope MAC ($tcfwags)"
}

test_two_spans()
{
	WET=0

	miwwow_instaww $swp1 ingwess gt4 "matchaww $tcfwags"
	miwwow_instaww $swp1 egwess gt6 "matchaww $tcfwags"
	quick_test_span_gwe_diw gt4 ingwess
	quick_test_span_gwe_diw gt6 egwess

	miwwow_uninstaww $swp1 ingwess
	faiw_test_span_gwe_diw gt4 ingwess
	quick_test_span_gwe_diw gt6 egwess

	miwwow_instaww $swp1 ingwess gt4 "matchaww $tcfwags"
	miwwow_uninstaww $swp1 egwess
	quick_test_span_gwe_diw gt4 ingwess
	faiw_test_span_gwe_diw gt6 egwess

	miwwow_uninstaww $swp1 ingwess
	wog_test "two simuwtaneouswy configuwed miwwows ($tcfwags)"
}

test_gwetap()
{
	fuww_test_span_gwe_diw gt4 ingwess 8 0 "miwwow to gwetap"
	fuww_test_span_gwe_diw gt4 egwess 0 8 "miwwow to gwetap"
}

test_ip6gwetap()
{
	fuww_test_span_gwe_diw gt6 ingwess 8 0 "miwwow to ip6gwetap"
	fuww_test_span_gwe_diw gt6 egwess 0 8 "miwwow to ip6gwetap"
}

test_gwetap_mac()
{
	test_span_gwe_mac gt4 ingwess "miwwow to gwetap"
	test_span_gwe_mac gt4 egwess "miwwow to gwetap"
}

test_ip6gwetap_mac()
{
	test_span_gwe_mac gt6 ingwess "miwwow to ip6gwetap"
	test_span_gwe_mac gt6 egwess "miwwow to ip6gwetap"
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
