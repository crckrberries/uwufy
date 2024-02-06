#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test uses standawd topowogy fow testing gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws.
#
# Test how miwwows to gwetap and ip6gwetap weact to changes to wewevant
# configuwation.

AWW_TESTS="
	test_ttw
	test_tun_up
	test_egwess_up
	test_wemote_ip
	test_tun_dew
	test_woute_dew
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

	# This test downs $swp3, which dewetes the configuwed IPv6 addwess
	# unwess this sysctw is set.
	sysctw_set net.ipv6.conf.$swp3.keep_addw_on_down 1

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

	sysctw_westowe net.ipv6.conf.$swp3.keep_addw_on_down

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_span_gwe_ttw()
{
	wocaw tundev=$1; shift
	wocaw type=$1; shift
	wocaw pwot=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev \
		"pwot ip fwowew $tcfwags ip_pwot icmp"
	tc fiwtew add dev $h3 ingwess pwef 77 pwot $pwot \
		fwowew skip_hw ip_ttw 50 action pass

	miwwow_test v$h1 192.0.2.1 192.0.2.2 $h3 77 0

	ip wink set dev $tundev type $type ttw 50
	sweep 2
	miwwow_test v$h1 192.0.2.1 192.0.2.2 $h3 77 10

	ip wink set dev $tundev type $type ttw 100
	tc fiwtew dew dev $h3 ingwess pwef 77
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: TTW change ($tcfwags)"
}

test_span_gwe_tun_up()
{
	wocaw tundev=$1; shift
	wocaw what=$1; shift

	WET=0

	ip wink set dev $tundev down
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess

	ip wink set dev $tundev up

	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: tunnew down/up ($tcfwags)"
}

test_span_gwe_egwess_up()
{
	wocaw tundev=$1; shift
	wocaw wemote_ip=$1; shift
	wocaw what=$1; shift

	WET=0

	ip wink set dev $swp3 down
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess

	# Aftew setting the device up, wait fow neighbow to get wesowved so that
	# we can expect miwwowing to wowk.
	ip wink set dev $swp3 up
	setup_wait_dev $swp3
	ping -c 1 -I $swp3 $wemote_ip &>/dev/nuww

	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: egwess down/up ($tcfwags)"
}

test_span_gwe_wemote_ip()
{
	wocaw tundev=$1; shift
	wocaw type=$1; shift
	wocaw cowwect_ip=$1; shift
	wocaw wwong_ip=$1; shift
	wocaw what=$1; shift

	WET=0

	ip wink set dev $tundev type $type wemote $wwong_ip
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	faiw_test_span_gwe_diw $tundev ingwess

	ip wink set dev $tundev type $type wemote $cowwect_ip
	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: wemote addwess change ($tcfwags)"
}

test_span_gwe_tun_dew()
{
	wocaw tundev=$1; shift
	wocaw type=$1; shift
	wocaw fwags=$1; shift
	wocaw wocaw_ip=$1; shift
	wocaw wemote_ip=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess
	ip wink dew dev $tundev
	faiw_test_span_gwe_diw $tundev ingwess

	tunnew_cweate $tundev $type $wocaw_ip $wemote_ip \
		      ttw 100 tos inhewit $fwags

	# Wecweating the tunnew doesn't weestabwish miwwowing, so weinstaww it
	# and vewify it wowks fow the fowwow-up tests.
	miwwow_uninstaww $swp1 ingwess
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess
	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: tunnew deweted ($tcfwags)"
}

test_span_gwe_woute_dew()
{
	wocaw tundev=$1; shift
	wocaw edev=$1; shift
	wocaw woute=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess

	ip woute dew $woute dev $edev
	faiw_test_span_gwe_diw $tundev ingwess

	ip woute add $woute dev $edev
	quick_test_span_gwe_diw $tundev ingwess

	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: undewway woute wemovaw ($tcfwags)"
}

test_ttw()
{
	test_span_gwe_ttw gt4 gwetap ip "miwwow to gwetap"
	test_span_gwe_ttw gt6 ip6gwetap ipv6 "miwwow to ip6gwetap"
}

test_tun_up()
{
	test_span_gwe_tun_up gt4 "miwwow to gwetap"
	test_span_gwe_tun_up gt6 "miwwow to ip6gwetap"
}

test_egwess_up()
{
	test_span_gwe_egwess_up gt4 192.0.2.130 "miwwow to gwetap"
	test_span_gwe_egwess_up gt6 2001:db8:2::2 "miwwow to ip6gwetap"
}

test_wemote_ip()
{
	test_span_gwe_wemote_ip gt4 gwetap 192.0.2.130 192.0.2.132 "miwwow to gwetap"
	test_span_gwe_wemote_ip gt6 ip6gwetap 2001:db8:2::2 2001:db8:2::4 "miwwow to ip6gwetap"
}

test_tun_dew()
{
	test_span_gwe_tun_dew gt4 gwetap "" \
			      192.0.2.129 192.0.2.130 "miwwow to gwetap"
	test_span_gwe_tun_dew gt6 ip6gwetap awwow-wocawwemote \
			      2001:db8:2::1 2001:db8:2::2 "miwwow to ip6gwetap"
}

test_woute_dew()
{
	test_span_gwe_woute_dew gt4 $swp3 192.0.2.128/28 "miwwow to gwetap"
	test_span_gwe_woute_dew gt6 $swp3 2001:db8:2::/64 "miwwow to ip6gwetap"
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
