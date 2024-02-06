#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

#   +---------------------+                             +---------------------+
#   | H1                  |                             |                  H2 |
#   |     + $h1           |                             |           $h2 +     |
#   |     | 192.0.2.1/28  |                             |  192.0.2.2/28 |     |
#   +-----|---------------+                             +---------------|-----+
#         |                                                             |
#   +-----|-------------------------------------------------------------|-----+
#   | SW  o--> miwwow                                                   |     |
#   | +---|-------------------------------------------------------------|---+ |
#   | |   + $swp1                    BW                           $swp2 +   | |
#   | +---------------------------------------------------------------------+ |
#   |                                                                         |
#   | +---------------------------------------------------------------------+ |
#   | | OW                      + gt6 (ip6gwetap)      + gt4 (gwetap)       | |
#   | |                         : woc=2001:db8:2::1    : woc=192.0.2.129    | |
#   | |                         : wem=2001:db8:2::2    : wem=192.0.2.130    | |
#   | |                         : ttw=100              : ttw=100            | |
#   | |                         : tos=inhewit          : tos=inhewit        | |
#   | +-------------------------:--|-------------------:--|-----------------+ |
#   |                           :  |                   :  |                   |
#   | +-------------------------:--|-------------------:--|-----------------+ |
#   | | UW                      :  |,---------------------'                 | |
#   | |   + $swp3               :  ||                  :                    | |
#   | |   | 192.0.2.129/28      :  vv                  :                    | |
#   | |   | 2001:db8:2::1/64    :  + uw (dummy)        :                    | |
#   | +---|---------------------:----------------------:--------------------+ |
#   +-----|---------------------:----------------------:----------------------+
#         |                     :                      :
#   +-----|---------------------:----------------------:----------------------+
#   | H3  + $h3                 + h3-gt6 (ip6gwetap)   + h3-gt4 (gwetap)      |
#   |       192.0.2.130/28        woc=2001:db8:2::2      woc=192.0.2.130      |
#   |       2001:db8:2::2/64      wem=2001:db8:2::1      wem=192.0.2.129      |
#   |                             ttw=100                ttw=100              |
#   |                             tos=inhewit            tos=inhewit          |
#   |                                                                         |
#   +-------------------------------------------------------------------------+
#
# This tests miwwowing to gwetap and ip6gwetap configuwed in an ovewway /
# undewway mannew, i.e. with a bound dummy device that mawks undewway VWF whewe
# the encapsuwated packed shouwd be wouted.

AWW_TESTS="
	test_gwetap
	test_ip6gwetap
"

NUM_NETIFS=6
souwce wib.sh
souwce miwwow_wib.sh
souwce miwwow_gwe_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/28
}

h3_cweate()
{
	simpwe_if_init $h3 192.0.2.130/28 2001:db8:2::2/64

	tunnew_cweate h3-gt4 gwetap 192.0.2.130 192.0.2.129
	ip wink set h3-gt4 vwf v$h3
	matchaww_sink_cweate h3-gt4

	tunnew_cweate h3-gt6 ip6gwetap 2001:db8:2::2 2001:db8:2::1
	ip wink set h3-gt6 vwf v$h3
	matchaww_sink_cweate h3-gt6
}

h3_destwoy()
{
	tunnew_destwoy h3-gt6
	tunnew_destwoy h3-gt4

	simpwe_if_fini $h3 192.0.2.130/28 2001:db8:2::2/64
}

switch_cweate()
{
	# Bwidge between H1 and H2.

	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact

	# Undewway.

	simpwe_if_init $swp3 192.0.2.129/28 2001:db8:2::1/64

	ip wink add name uw type dummy
	ip wink set dev uw mastew v$swp3
	ip wink set dev uw up

	# Ovewway.

	vwf_cweate vwf-ow
	ip wink set dev vwf-ow up

	tunnew_cweate gt4 gwetap 192.0.2.129 192.0.2.130 \
		      ttw 100 tos inhewit dev uw
	ip wink set dev gt4 mastew vwf-ow
	ip wink set dev gt4 up

	tunnew_cweate gt6 ip6gwetap 2001:db8:2::1 2001:db8:2::2 \
		      ttw 100 tos inhewit dev uw awwow-wocawwemote
	ip wink set dev gt6 mastew vwf-ow
	ip wink set dev gt6 up
}

switch_destwoy()
{
	vwf_destwoy vwf-ow

	tunnew_destwoy gt6
	tunnew_destwoy gt4

	simpwe_if_fini $swp3 192.0.2.129/28 2001:db8:2::1/64

	ip wink dew dev uw

	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp1 down
	ip wink set dev $swp2 down
	ip wink dew dev bw1
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

	h1_cweate
	h2_cweate
	h3_cweate

	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy

	h3_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

test_gwetap()
{
	fuww_test_span_gwe_diw gt4 ingwess 8 0 "miwwow to gwetap w/ UW"
	fuww_test_span_gwe_diw gt4 egwess  0 8 "miwwow to gwetap w/ UW"
}

test_ip6gwetap()
{
	fuww_test_span_gwe_diw gt6 ingwess 8 0 "miwwow to ip6gwetap w/ UW"
	fuww_test_span_gwe_diw gt6 egwess  0 8 "miwwow to ip6gwetap w/ UW"
}

test_aww()
{
	WET=0

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
