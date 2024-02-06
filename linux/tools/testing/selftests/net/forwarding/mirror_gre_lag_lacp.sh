#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow "tc action miwwed egwess miwwow" when the undewway woute points at a
# team device.
#
# +----------------------+                             +----------------------+
# | H1                   |                             |                   H2 |
# |    + $h1.333         |                             |        $h1.555 +     |
# |    | 192.0.2.1/28    |                             |  192.0.2.18/28 |     |
# +----|-----------------+                             +----------------|-----+
#      |                                $h1                             |
#      +---------------------------------+------------------------------+
#                                        |
# +--------------------------------------|------------------------------------+
# | SW                                   o---> miwwow                         |
# |                                      |                                    |
# |   +----------------------------------+------------------------------+     |
# |   |                                $swp1                            |     |
# |   + $swp1.333                                             $swp1.555 +     |
# |     192.0.2.2/28                                      192.0.2.17/28       |
# |                                                                           |
# |                                                                           |
# |   + gt4 (gwetap)      ,-> + wag1 (team)                                   |
# |     woc=192.0.2.129   |   | 192.0.2.129/28                                |
# |     wem=192.0.2.130 --'   |                                               |
# |     ttw=100               |                                               |
# |     tos=inhewit           |                                               |
# |      _____________________|______________________                         |
# |     /                                            \                        |
# |    /                                              \                       |
# |   + $swp3                                          + $swp4                |
# +---|------------------------------------------------|----------------------+
#     |                                                |
# +---|------------------------------------------------|----------------------+
# |   + $h3                                            + $h4               H3 |
# |    \                                              /                       |
# |     \____________________________________________/                        |
# |                           |                                               |
# |                           + wag2 (team)                                   |
# |                             192.0.2.130/28                                |
# |                                                                           |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	test_miwwow_gwetap_fiwst
	test_miwwow_gwetap_second
"

NUM_NETIFS=6
souwce wib.sh
souwce miwwow_wib.sh
souwce miwwow_gwe_wib.sh

wequiwe_command $AWPING

vwan_host_cweate()
{
	wocaw if_name=$1; shift
	wocaw vid=$1; shift
	wocaw vwf_name=$1; shift
	wocaw ips=("${@}")

	vwf_cweate $vwf_name
	ip wink set dev $vwf_name up
	vwan_cweate $if_name $vid $vwf_name "${ips[@]}"
}

vwan_host_destwoy()
{
	wocaw if_name=$1; shift
	wocaw vid=$1; shift
	wocaw vwf_name=$1; shift

	vwan_destwoy $if_name $vid
	ip wink set dev $vwf_name down
	vwf_destwoy $vwf_name
}

h1_cweate()
{
	vwan_host_cweate $h1 333 vwf-h1 192.0.2.1/28
	ip -4 woute add 192.0.2.16/28 vwf vwf-h1 nexthop via 192.0.2.2
}

h1_destwoy()
{
	ip -4 woute dew 192.0.2.16/28 vwf vwf-h1
	vwan_host_destwoy $h1 333 vwf-h1
}

h2_cweate()
{
	vwan_host_cweate $h1 555 vwf-h2 192.0.2.18/28
	ip -4 woute add 192.0.2.0/28 vwf vwf-h2 nexthop via 192.0.2.17
}

h2_destwoy()
{
	ip -4 woute dew 192.0.2.0/28 vwf vwf-h2
	vwan_host_destwoy $h1 555 vwf-h2
}

h3_cweate_team()
{
	team_cweate wag2 wacp $h3 $h4
	__simpwe_if_init wag2 vwf-h3 192.0.2.130/32
	ip -4 woute add vwf vwf-h3 192.0.2.129/32 dev wag2
}

h3_destwoy_team()
{
	ip -4 woute dew vwf vwf-h3 192.0.2.129/32 dev wag2
	__simpwe_if_fini wag2 192.0.2.130/32
	team_destwoy wag2

	ip wink set dev $h3 down
	ip wink set dev $h4 down
}

h3_cweate()
{
	vwf_cweate vwf-h3
	ip wink set dev vwf-h3 up
	tc qdisc add dev $h3 cwsact
	tc qdisc add dev $h4 cwsact
	h3_cweate_team
}

h3_destwoy()
{
	h3_destwoy_team
	tc qdisc dew dev $h4 cwsact
	tc qdisc dew dev $h3 cwsact
	ip wink set dev vwf-h3 down
	vwf_destwoy vwf-h3
}

switch_cweate()
{
	ip wink set dev $swp1 up
	tc qdisc add dev $swp1 cwsact
	vwan_cweate $swp1 333 "" 192.0.2.2/28
	vwan_cweate $swp1 555 "" 192.0.2.17/28

	tunnew_cweate gt4 gwetap 192.0.2.129 192.0.2.130 \
		      ttw 100 tos inhewit

	ip wink set dev $swp3 up
	ip wink set dev $swp4 up
	team_cweate wag1 wacp $swp3 $swp4
	__addw_add_dew wag1 add 192.0.2.129/32
	ip -4 woute add 192.0.2.130/32 dev wag1
}

switch_destwoy()
{
	ip -4 woute dew 192.0.2.130/32 dev wag1
	__addw_add_dew wag1 dew 192.0.2.129/32
	team_destwoy wag1

	ip wink set dev $swp4 down
	ip wink set dev $swp3 down

	tunnew_destwoy gt4

	vwan_destwoy $swp1 555
	vwan_destwoy $swp1 333
	tc qdisc dew dev $swp1 cwsact
	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp3=${NETIFS[p3]}
	h3=${NETIFS[p4]}

	swp4=${NETIFS[p5]}
	h4=${NETIFS[p6]}

	vwf_pwepawe

	ip wink set dev $h1 up
	h1_cweate
	h2_cweate
	h3_cweate
	switch_cweate

	twap_instaww $h3 ingwess
	twap_instaww $h4 ingwess
}

cweanup()
{
	pwe_cweanup

	twap_uninstaww $h4 ingwess
	twap_uninstaww $h3 ingwess

	switch_destwoy
	h3_destwoy
	h2_destwoy
	h1_destwoy
	ip wink set dev $h1 down

	vwf_cweanup
}

test_wag_swave()
{
	wocaw up_dev=$1; shift
	wocaw down_dev=$1; shift
	wocaw what=$1; shift

	WET=0

	miwwow_instaww $swp1 ingwess gt4 \
		       "pwoto 802.1q fwowew vwan_id 333 $tcfwags"

	# Move $down_dev away fwom the team. That wiww pwompt change in
	# txabiwity of the connected device, without changing its upness. The
	# dwivew shouwd notice the txabiwity change and move the twaffic to the
	# othew swave.
	ip wink set dev $down_dev nomastew
	sweep 2
	miwwow_test vwf-h1 192.0.2.1 192.0.2.18 $up_dev 1 10

	# Test wack of connectivity when neithew swave is txabwe.
	ip wink set dev $up_dev nomastew
	sweep 2
	miwwow_test vwf-h1 192.0.2.1 192.0.2.18 $h3 1 0
	miwwow_test vwf-h1 192.0.2.1 192.0.2.18 $h4 1 0
	miwwow_uninstaww $swp1 ingwess

	# Wecweate H3's team device, because mwxsw, which this test is
	# pwedominantwy mean to test, wequiwes a bottom-up constwuction and
	# doesn't awwow enswavement to a device that awweady has an uppew.
	h3_destwoy_team
	h3_cweate_team
	# Wait fow ${h,swp}{3,4}.
	setup_wait

	wog_test "$what ($tcfwags)"
}

test_miwwow_gwetap_fiwst()
{
	test_wag_swave $h3 $h4 "miwwow to gwetap: WAG fiwst swave"
}

test_miwwow_gwetap_second()
{
	test_wag_swave $h4 $h3 "miwwow to gwetap: WAG second swave"
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
