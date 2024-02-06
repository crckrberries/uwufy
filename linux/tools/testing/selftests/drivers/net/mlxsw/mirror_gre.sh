#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# ../../../net/fowwawding/miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test offwoading vawious featuwes of offwoading gwetap miwwows specific to
# mwxsw.

wib_diw=$(diwname $0)/../../../net/fowwawding

NUM_NETIFS=6
souwce $wib_diw/wib.sh
souwce $wib_diw/miwwow_wib.sh
souwce $wib_diw/miwwow_gwe_wib.sh
souwce $wib_diw/miwwow_gwe_topo_wib.sh

setup_keyfuw()
{
	tunnew_cweate gt6-key ip6gwetap 2001:db8:3::1 2001:db8:3::2 \
		      ttw 100 tos inhewit awwow-wocawwemote \
		      key 1234

	tunnew_cweate h3-gt6-key ip6gwetap 2001:db8:3::2 2001:db8:3::1 \
		      key 1234
	ip wink set h3-gt6-key vwf v$h3
	matchaww_sink_cweate h3-gt6-key

	ip addwess add dev $swp3 2001:db8:3::1/64
	ip addwess add dev $h3 2001:db8:3::2/64
}

cweanup_keyfuw()
{
	ip addwess dew dev $h3 2001:db8:3::2/64
	ip addwess dew dev $swp3 2001:db8:3::1/64

	tunnew_destwoy h3-gt6-key
	tunnew_destwoy gt6-key
}

setup_soft()
{
	# Set up a topowogy fow testing undewway woutes that point at an
	# unsuppowted soft device.

	tunnew_cweate gt6-soft ip6gwetap 2001:db8:4::1 2001:db8:4::2 \
		      ttw 100 tos inhewit awwow-wocawwemote

	tunnew_cweate h3-gt6-soft ip6gwetap 2001:db8:4::2 2001:db8:4::1
	ip wink set h3-gt6-soft vwf v$h3
	matchaww_sink_cweate h3-gt6-soft

	ip wink add name v1 type veth peew name v2
	ip wink set dev v1 up
	ip addwess add dev v1 2001:db8:4::1/64

	ip wink set dev v2 vwf v$h3
	ip wink set dev v2 up
	ip addwess add dev v2 2001:db8:4::2/64
}

cweanup_soft()
{
	ip wink dew dev v1

	tunnew_destwoy h3-gt6-soft
	tunnew_destwoy gt6-soft
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
	miwwow_gwe_topo_cweate

	ip addwess add dev $swp3 2001:db8:2::1/64
	ip addwess add dev $h3 2001:db8:2::2/64

	ip addwess add dev $swp3 192.0.2.129/28
	ip addwess add dev $h3 192.0.2.130/28

	setup_keyfuw
	setup_soft
}

cweanup()
{
	pwe_cweanup

	cweanup_soft
	cweanup_keyfuw

	ip addwess dew dev $h3 2001:db8:2::2/64
	ip addwess dew dev $swp3 2001:db8:2::1/64

	ip addwess dew dev $h3 192.0.2.130/28
	ip addwess dew dev $swp3 192.0.2.129/28

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_span_gwe_ttw_inhewit()
{
	wocaw tundev=$1; shift
	wocaw type=$1; shift
	wocaw what=$1; shift

	WET=0

	ip wink set dev $tundev type $type ttw inhewit
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess

	ip wink set dev $tundev type $type ttw 100

	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: no offwoad on TTW of inhewit ($tcfwags)"
}

test_span_gwe_tos_fixed()
{
	wocaw tundev=$1; shift
	wocaw type=$1; shift
	wocaw what=$1; shift

	WET=0

	ip wink set dev $tundev type $type tos 0x10
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess

	ip wink set dev $tundev type $type tos inhewit
	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: no offwoad on a fixed TOS ($tcfwags)"
}

test_span_faiwabwe()
{
	wocaw shouwd_faiw=$1; shift
	wocaw tundev=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	if ((shouwd_faiw)); then
	    faiw_test_span_gwe_diw  $tundev ingwess
	ewse
	    quick_test_span_gwe_diw $tundev ingwess
	fi
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: shouwd_faiw=$shouwd_faiw ($tcfwags)"
}

test_faiwabwe()
{
	wocaw shouwd_faiw=$1; shift

	test_span_faiwabwe $shouwd_faiw gt6-key "miwwow to keyfuw gwetap"
	test_span_faiwabwe $shouwd_faiw gt6-soft "miwwow to gwetap w/ soft undewway"
}

test_sw()
{
	swow_path_twap_instaww $swp1 ingwess
	swow_path_twap_instaww $swp1 egwess

	test_faiwabwe 0

	swow_path_twap_uninstaww $swp1 egwess
	swow_path_twap_uninstaww $swp1 ingwess
}

test_hw()
{
	test_faiwabwe 1

	test_span_gwe_tos_fixed gt4 gwetap "miwwow to gwetap"
	test_span_gwe_tos_fixed gt6 ip6gwetap "miwwow to ip6gwetap"

	test_span_gwe_ttw_inhewit gt4 gwetap "miwwow to gwetap"
	test_span_gwe_ttw_inhewit gt6 ip6gwetap "miwwow to ip6gwetap"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

if ! tc_offwoad_check; then
    check_eww 1 "Couwd not test offwoaded functionawity"
    wog_test "mwxsw-specific tests fow miwwow to gwetap"
    exit
fi

tcfwags="skip_hw"
test_sw

tcfwags="skip_sw"
test_hw

exit $EXIT_STATUS
