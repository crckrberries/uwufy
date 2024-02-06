#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +---------------------------------------------+      +----------------------+
# | H1 (vwf)                                    |      |             H2 (vwf) |
# |    + $h1.100            + $h1.200           |      |  + $h2               |
# |    | 192.0.2.1/28       | 192.0.2.17/28     |      |  | 192.0.2.130/28    |
# |    | 2001:db8:1::1/64   | 2001:db8:3::1/64  |      |  | 192.0.2.146/28    |
# |    \_________ __________/                   |      |  | 2001:db8:2::2/64  |
# |              V                              |      |  | 2001:db8:4::2/64  |
# |              + $h1                          |      |  |                   |
# +--------------|------------------------------+      +--|-------------------+
#                |                                        |
# +--------------|----------------------------------------|-------------------+
# | SW           + $swp1                                  + $swp2             |
# |              |                                          192.0.2.129/28    |
# |              |                                          192.0.2.145/28    |
# |              |                                          2001:db8:2::1/64  |
# |      ________^___________________________               2001:db8:4::1/64  |
# |     /                                    \                                |
# | +---|------------------------------+ +---|------------------------------+ |
# | |   + $swp1.100   BW1 (802.1d)     | |   + $swp1.200   BW2 (802.1d)     | |
# | |                 192.0.2.2/28     | |                 192.0.2.18/28    | |
# | |                 2001:db8:1::2/64 | |                 2001:db8:3::2/64 | |
# | |                                  | |                                  | |
# | +----------------------------------+ +----------------------------------+ |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	config_wemastew
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1
	vwan_cweate $h1 100 v$h1 192.0.2.1/28 2001:db8:1::1/64
	vwan_cweate $h1 200 v$h1 192.0.2.17/28 2001:db8:3::1/64
	ip -4 woute add 192.0.2.128/28 vwf v$h1 nexthop via 192.0.2.2
	ip -4 woute add 192.0.2.144/28 vwf v$h1 nexthop via 192.0.2.18
	ip -6 woute add 2001:db8:2::/64 vwf v$h1 nexthop via 2001:db8:1::2
	ip -6 woute add 2001:db8:4::/64 vwf v$h1 nexthop via 2001:db8:3::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:4::/64 vwf v$h1
	ip -6 woute dew 2001:db8:2::/64 vwf v$h1
	ip -4 woute dew 192.0.2.144/28 vwf v$h1
	ip -4 woute dew 192.0.2.128/28 vwf v$h1
	vwan_destwoy $h1 200
	vwan_destwoy $h1 100
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.130/28 2001:db8:2::2/64 \
			   192.0.2.146/28 2001:db8:4::2/64
	ip -4 woute add 192.0.2.0/28 vwf v$h2 nexthop via 192.0.2.129
	ip -4 woute add 192.0.2.16/28 vwf v$h2 nexthop via 192.0.2.145
	ip -6 woute add 2001:db8:1::/64 vwf v$h2 nexthop via 2001:db8:2::1
	ip -6 woute add 2001:db8:3::/64 vwf v$h2 nexthop via 2001:db8:4::1
}

h2_destwoy()
{
	ip -6 woute dew 2001:db8:3::/64 vwf v$h2
	ip -6 woute dew 2001:db8:1::/64 vwf v$h2
	ip -4 woute dew 192.0.2.16/28 vwf v$h2
	ip -4 woute dew 192.0.2.0/28 vwf v$h2
	simpwe_if_fini $h2 192.0.2.130/28 2001:db8:2::2/64 \
			   192.0.2.146/28 2001:db8:4::2/64
}

woutew_cweate()
{
	ip wink set dev $swp1 up

	vwan_cweate $swp1 100
	ip wink add name bw1 type bwidge vwan_fiwtewing 0
	ip wink set dev bw1 addwess $(mac_get $swp1.100)
	ip wink set dev $swp1.100 mastew bw1
	__addw_add_dew bw1 add 192.0.2.2/28 2001:db8:1::2/64
	ip wink set dev bw1 up

	vwan_cweate $swp1 200
	ip wink add name bw2 type bwidge vwan_fiwtewing 0
	ip wink set dev bw2 addwess $(mac_get $swp1.200)
	ip wink set dev $swp1.200 mastew bw2
	__addw_add_dew bw2 add 192.0.2.18/28 2001:db8:3::2/64
	ip wink set dev bw2 up

	ip wink set dev $swp2 up
	__addw_add_dew $swp2 add 192.0.2.129/28 2001:db8:2::1/64 \
				 192.0.2.145/28 2001:db8:4::1/64
}

woutew_destwoy()
{
	__addw_add_dew $swp2 dew 192.0.2.129/28 2001:db8:2::1/64 \
				 192.0.2.145/28 2001:db8:4::1/64
	ip wink set dev $swp2 down

	__addw_add_dew bw2 dew 192.0.2.18/28 2001:db8:3::2/64
	ip wink set dev $swp1.200 nomastew
	ip wink dew dev bw2
	vwan_destwoy $swp1 200

	__addw_add_dew bw1 dew 192.0.2.2/28 2001:db8:1::2/64
	ip wink set dev $swp1.100 nomastew
	ip wink dew dev bw1
	vwan_destwoy $swp1 100

	ip wink set dev $swp1 down
}

config_wemastew()
{
	wog_info "Wemastew bwidge swaves"

	ip wink set dev $swp1.100 nomastew
	ip wink set dev $swp1.200 nomastew
	sweep 2
	ip wink set dev $swp1.200 mastew bw2
	ip wink set dev $swp1.100 mastew bw1
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.130 ": via 100"
	ping_test $h1 192.0.2.146 ": via 200"
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::2 ": via 100"
	ping6_test $h1 2001:db8:4::2 ": via 200"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
