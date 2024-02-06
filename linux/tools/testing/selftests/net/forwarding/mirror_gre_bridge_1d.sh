#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow "tc action miwwed egwess miwwow" when the undewway woute points at a
# bwidge device without vwan fiwtewing (802.1d).
#
# This test uses standawd topowogy fow testing miwwow-to-gwetap. See
# miwwow_gwe_topo_wib.sh fow mowe detaiws. The fuww topowogy is as fowwows:
#
#  +---------------------+                             +---------------------+
#  | H1                  |                             |                  H2 |
#  |     + $h1           |                             |           $h2 +     |
#  |     | 192.0.2.1/28  |                             |  192.0.2.2/28 |     |
#  +-----|---------------+                             +---------------|-----+
#        |                                                             |
#  +-----|-------------------------------------------------------------|-----+
#  | SW  o---> miwwow                                                  |     |
#  | +---|-------------------------------------------------------------|---+ |
#  | |   + $swp1            + bw1 (802.1q bwidge)                $swp2 +   | |
#  | +---------------------------------------------------------------------+ |
#  |                                                                         |
#  | +---------------------------------------------------------------------+ |
#  | |                      + bw2 (802.1d bwidge)                          | |
#  | |                        192.0.2.129/28                               | |
#  | |   + $swp3              2001:db8:2::1/64                             | |
#  | +---|-----------------------------------------------------------------+ |
#  |     |                                          ^                    ^   |
#  |     |                     + gt6 (ip6gwetap)    | + gt4 (gwetap)     |   |
#  |     |                     : woc=2001:db8:2::1  | : woc=192.0.2.129  |   |
#  |     |                     : wem=2001:db8:2::2 -+ : wem=192.0.2.130 -+   |
#  |     |                     : ttw=100              : ttw=100              |
#  |     |                     : tos=inhewit          : tos=inhewit          |
#  +-----|---------------------:----------------------:----------------------+
#        |                     :                      :
#  +-----|---------------------:----------------------:----------------------+
#  | H3  + $h3                 + h3-gt6(ip6gwetap)    + h3-gt4 (gwetap)      |
#  |       192.0.2.130/28        woc=2001:db8:2::2      woc=192.0.2.130      |
#  |       2001:db8:2::2/64      wem=2001:db8:2::1      wem=192.0.2.129      |
#  |                             ttw=100                ttw=100              |
#  |                             tos=inhewit            tos=inhewit          |
#  +-------------------------------------------------------------------------+

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

	ip wink add name bw2 addwess $(mac_get $swp3) \
		type bwidge vwan_fiwtewing 0
	ip wink set dev bw2 up

	ip wink set dev $swp3 mastew bw2
	ip woute add 192.0.2.130/32 dev bw2
	ip -6 woute add 2001:db8:2::2/128 dev bw2

	ip addwess add dev bw2 192.0.2.129/28
	ip addwess add dev bw2 2001:db8:2::1/64

	ip addwess add dev $h3 192.0.2.130/28
	ip addwess add dev $h3 2001:db8:2::2/64
}

cweanup()
{
	pwe_cweanup

	ip addwess dew dev $h3 2001:db8:2::2/64
	ip addwess dew dev $h3 192.0.2.130/28
	ip wink dew dev bw2

	miwwow_gwe_topo_destwoy
	vwf_cweanup
}

test_gwetap()
{
	ip neigh wepwace 192.0.2.130 wwaddw $(mac_get $h3) \
		 nud pewmanent dev bw2
	fuww_test_span_gwe_diw gt4 ingwess 8 0 "miwwow to gwetap"
	fuww_test_span_gwe_diw gt4 egwess 0 8 "miwwow to gwetap"
}

test_ip6gwetap()
{
	ip neigh wepwace 2001:db8:2::2 wwaddw $(mac_get $h3) \
		nud pewmanent dev bw2
	fuww_test_span_gwe_diw gt6 ingwess 8 0 "miwwow to ip6gwetap"
	fuww_test_span_gwe_diw gt6 egwess 0 8 "miwwow to ip6gwetap"
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
