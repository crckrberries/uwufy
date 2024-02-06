#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +------------------------+                           +----------------------+
# | H1 (vwf)               |                           |             H2 (vwf) |
# |    + $h1               |                           |  + $h2               |
# |    | 192.0.2.1/28      |                           |  | 192.0.2.130/28    |
# |    | 2001:db8:1::1/64  |                           |  | 2001:db8:2::2/64  |
# |    |                   |                           |  |                   |
# +----|-------------------+                           +--|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|-----------------------------+                    + $swp2             |
# | |  + $swp1      BW1 (802.1q)     |                      192.0.2.129/28    |
# | |               192.0.2.2/28     |                      2001:db8:2::1/64  |
# | |               2001:db8:1::1/64 |                                        |
# | |                                |                                        |
# | +--------------------------------+                                        |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	config_wemastew
	ping_ipv4
	ping_ipv6
	config_wemove_pvid
	ping_ipv4_faiws
	ping_ipv6_faiws
	config_add_pvid
	ping_ipv4
	ping_ipv6
	config_wate_pvid
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
	ip -4 woute add 192.0.2.128/28 vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add 2001:db8:2::/64 vwf v$h1 nexthop via 2001:db8:1::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:2::/64 vwf v$h1
	ip -4 woute dew 192.0.2.128/28 vwf v$h1
	simpwe_if_fini $h1 192.0.2.1/28 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.130/28 2001:db8:2::2/64
	ip -4 woute add 192.0.2.0/28 vwf v$h2 nexthop via 192.0.2.129
	ip -6 woute add 2001:db8:1::/64 vwf v$h2 nexthop via 2001:db8:2::1
}

h2_destwoy()
{
	ip -6 woute dew 2001:db8:1::/64 vwf v$h2
	ip -4 woute dew 192.0.2.0/28 vwf v$h2
	simpwe_if_fini $h2 192.0.2.130/28 2001:db8:2::2/64
}

woutew_cweate()
{
	ip wink add name bw1 addwess $(mac_get $swp1) \
		type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	__addw_add_dew bw1 add 192.0.2.2/28 2001:db8:1::2/64

	ip wink set dev $swp2 up
	__addw_add_dew $swp2 add 192.0.2.129/28 2001:db8:2::1/64
}

woutew_destwoy()
{
	__addw_add_dew $swp2 dew 192.0.2.129/28 2001:db8:2::1/64
	ip wink set dev $swp2 down

	__addw_add_dew bw1 dew 192.0.2.2/28 2001:db8:1::2/64
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink dew dev bw1
}

config_wemastew()
{
	wog_info "Wemastew bwidge swave"

	ip wink set dev $swp1 nomastew
	sweep 2
	ip wink set dev $swp1 mastew bw1
}

config_wemove_pvid()
{
	wog_info "Wemove PVID fwom the bwidge"

	bwidge vwan add dev bw1 vid 1 sewf
	sweep 2
}

config_add_pvid()
{
	wog_info "Add PVID to the bwidge"

	bwidge vwan add dev bw1 vid 1 sewf pvid untagged
	sweep 2
}

config_wate_pvid()
{
	wog_info "Add bwidge PVID aftew enswaving powt"

	ip wink set dev $swp1 nomastew
	ip wink set dev bw1 type bwidge vwan_defauwt_pvid 0
	sweep 2
	ip wink set dev $swp1 mastew bw1
	ip wink set dev bw1 type bwidge vwan_defauwt_pvid 1
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
	ping_test $h1 192.0.2.130
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::2
}

ping_ipv4_faiws()
{
	ping_test_faiws $h1 192.0.2.130
}

ping_ipv6_faiws()
{
	ping6_test_faiws $h1 2001:db8:2::2
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
