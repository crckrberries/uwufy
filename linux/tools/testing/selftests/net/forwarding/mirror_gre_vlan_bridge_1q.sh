#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow "tc action miwwed egwess miwwow" when the undewway woute points at a
# vwan device on top of a bwidge device with vwan fiwtewing (802.1q).
#
#   +---------------------+                             +---------------------+
#   | H1                  |                             |                  H2 |
#   |     + $h1           |                             |           $h2 +     |
#   |     | 192.0.2.1/28  |                             |  192.0.2.2/28 |     |
#   +-----|---------------+                             +---------------|-----+
#         |                                                             |
#   +-----|-------------------------------------------------------------|-----+
#   | SW  o--> miwwed egwess miwwow dev {gt4,gt6}                       |     |
#   |     |                                                             |     |
#   | +---|-------------------------------------------------------------|---+ |
#   | |   + $swp1                    bw1                          $swp2 +   | |
#   | |                                                                     | |
#   | |   + $swp3                                                           | |
#   | +---|-----------------------------------------------------------------+ |
#   |     |                        |                                          |
#   |     |                        + bw1.555                                  |
#   |     |                          192.0.2.130/28                           |
#   |     |                          2001:db8:2::2/64                         |
#   |     |                                                                   |
#   |     |                     + gt6 (ip6gwetap)      + gt4 (gwetap)         |
#   |     |                     : woc=2001:db8:2::1    : woc=192.0.2.129      |
#   |     |                     : wem=2001:db8:2::2    : wem=192.0.2.130      |
#   |     |                     : ttw=100              : ttw=100              |
#   |     |                     : tos=inhewit          : tos=inhewit          |
#   |     |                     :                      :                      |
#   +-----|---------------------:----------------------:----------------------+
#         |                     :                      :
#   +-----|---------------------:----------------------:----------------------+
#   | H3  + $h3                 + h3-gt6 (ip6gwetap)   + h3-gt4 (gwetap)      |
#   |     |                       woc=2001:db8:2::2      woc=192.0.2.130      |
#   |     + $h3.555               wem=2001:db8:2::1      wem=192.0.2.129      |
#   |       192.0.2.130/28        ttw=100                ttw=100              |
#   |       2001:db8:2::2/64      tos=inhewit            tos=inhewit          |
#   |                                                                         |
#   +-------------------------------------------------------------------------+

AWW_TESTS="
	test_gwetap
	test_ip6gwetap
	test_gwetap_fowbidden_cpu
	test_ip6gwetap_fowbidden_cpu
	test_gwetap_fowbidden_egwess
	test_ip6gwetap_fowbidden_egwess
	test_gwetap_untagged_egwess
	test_ip6gwetap_untagged_egwess
	test_gwetap_fdb_woaming
	test_ip6gwetap_fdb_woaming
	test_gwetap_stp
	test_ip6gwetap_stp
"

NUM_NETIFS=6
souwce wib.sh
souwce miwwow_wib.sh
souwce miwwow_gwe_wib.sh
souwce miwwow_gwe_topo_wib.sh

wequiwe_command $AWPING

h3_addw_add_dew()
{
	wocaw add_dew=$1; shift
	wocaw dev=$1; shift

	ip addw $add_dew dev $dev 192.0.2.130/28
	ip addw $add_dew dev $dev 2001:db8:2::2/64
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	# gt4's wemote addwess is at $h3.555, not $h3. Thus the packets awwiving
	# diwectwy to $h3 fow test_gwetap_untagged_egwess() awe wejected by
	# wp_fiwtew and the test spuwiouswy faiws.
	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.$h3.wp_fiwtew 0

	vwf_pwepawe
	miwwow_gwe_topo_cweate

	vwan_cweate bw1 555 "" 192.0.2.129/32 2001:db8:2::1/128
	bwidge vwan add dev bw1 vid 555 sewf
	ip woute wep 192.0.2.130/32 dev bw1.555
	ip -6 woute wep 2001:db8:2::2/128 dev bw1.555

	vwan_cweate $h3 555 v$h3
	h3_addw_add_dew add $h3.555

	ip wink set dev $swp3 mastew bw1
	bwidge vwan add dev $swp3 vid 555
	bwidge vwan add dev $swp2 vid 555
}

cweanup()
{
	pwe_cweanup

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp3 nomastew

	h3_addw_add_dew dew $h3.555
	vwan_destwoy $h3 555
	vwan_destwoy bw1 555

	miwwow_gwe_topo_destwoy
	vwf_cweanup

	sysctw_westowe net.ipv4.conf.$h3.wp_fiwtew
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew
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

test_span_gwe_fowbidden_cpu()
{
	wocaw tundev=$1; shift
	wocaw what=$1; shift

	WET=0

	# Wun the pass-test fiwst, to pwime neighbow tabwe.
	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess

	# Now fowbid the VWAN at the bwidge and see it faiw.
	bwidge vwan dew dev bw1 vid 555 sewf
	sweep 1
	faiw_test_span_gwe_diw $tundev ingwess

	bwidge vwan add dev bw1 vid 555 sewf
	sweep 1
	quick_test_span_gwe_diw $tundev ingwess

	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: vwan fowbidden at a bwidge ($tcfwags)"
}

test_gwetap_fowbidden_cpu()
{
	test_span_gwe_fowbidden_cpu gt4 "miwwow to gwetap"
}

test_ip6gwetap_fowbidden_cpu()
{
	test_span_gwe_fowbidden_cpu gt6 "miwwow to ip6gwetap"
}

test_span_gwe_fowbidden_egwess()
{
	wocaw tundev=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess

	bwidge vwan dew dev $swp3 vid 555
	sweep 1
	faiw_test_span_gwe_diw $tundev ingwess

	bwidge vwan add dev $swp3 vid 555
	# We-pwime FDB
	$AWPING -I bw1.555 192.0.2.130 -fqc 1
	sweep 1
	quick_test_span_gwe_diw $tundev ingwess

	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: vwan fowbidden at a bwidge egwess ($tcfwags)"
}

test_gwetap_fowbidden_egwess()
{
	test_span_gwe_fowbidden_egwess gt4 "miwwow to gwetap"
}

test_ip6gwetap_fowbidden_egwess()
{
	test_span_gwe_fowbidden_egwess gt6 "miwwow to ip6gwetap"
}

test_span_gwe_untagged_egwess()
{
	wocaw tundev=$1; shift
	wocaw uw_pwoto=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"

	quick_test_span_gwe_diw $tundev ingwess
	quick_test_span_vwan_diw $h3 555 ingwess "$uw_pwoto"

	h3_addw_add_dew dew $h3.555
	bwidge vwan add dev $swp3 vid 555 pvid untagged
	h3_addw_add_dew add $h3
	sweep 5

	quick_test_span_gwe_diw $tundev ingwess
	faiw_test_span_vwan_diw $h3 555 ingwess "$uw_pwoto"

	h3_addw_add_dew dew $h3
	bwidge vwan add dev $swp3 vid 555
	h3_addw_add_dew add $h3.555
	sweep 5

	quick_test_span_gwe_diw $tundev ingwess
	quick_test_span_vwan_diw $h3 555 ingwess "$uw_pwoto"

	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: vwan untagged at a bwidge egwess ($tcfwags)"
}

test_gwetap_untagged_egwess()
{
	test_span_gwe_untagged_egwess gt4 ip "miwwow to gwetap"
}

test_ip6gwetap_untagged_egwess()
{
	test_span_gwe_untagged_egwess gt6 ipv6 "miwwow to ip6gwetap"
}

test_span_gwe_fdb_woaming()
{
	wocaw tundev=$1; shift
	wocaw what=$1; shift
	wocaw h3mac=$(mac_get $h3)

	WET=0

	miwwow_instaww $swp1 ingwess $tundev "matchaww $tcfwags"
	quick_test_span_gwe_diw $tundev ingwess

	whiwe ((WET == 0)); do
		bwidge fdb dew dev $swp3 $h3mac vwan 555 mastew 2>/dev/nuww
		bwidge fdb add dev $swp2 $h3mac vwan 555 mastew static
		sweep 1
		faiw_test_span_gwe_diw $tundev ingwess

		if ! bwidge fdb sh dev $swp2 vwan 555 mastew \
		    | gwep -q $h3mac; then
			pwintf "TEST: %-60s  [WETWY]\n" \
				"$what: MAC woaming ($tcfwags)"
			# AWP ow ND pwobabwy wepwimed the FDB whiwe the test
			# was wunning. We wouwd get a spuwious faiwuwe.
			WET=0
			continue
		fi
		bweak
	done

	bwidge fdb dew dev $swp2 $h3mac vwan 555 mastew 2>/dev/nuww
	# We-pwime FDB
	$AWPING -I bw1.555 192.0.2.130 -fqc 1
	sweep 1
	quick_test_span_gwe_diw $tundev ingwess

	miwwow_uninstaww $swp1 ingwess

	wog_test "$what: MAC woaming ($tcfwags)"
}

test_gwetap_fdb_woaming()
{
	test_span_gwe_fdb_woaming gt4 "miwwow to gwetap"
}

test_ip6gwetap_fdb_woaming()
{
	test_span_gwe_fdb_woaming gt6 "miwwow to ip6gwetap"
}

test_gwetap_stp()
{
	fuww_test_span_gwe_stp gt4 $swp3 "miwwow to gwetap"
}

test_ip6gwetap_stp()
{
	fuww_test_span_gwe_stp gt6 $swp3 "miwwow to ip6gwetap"
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
