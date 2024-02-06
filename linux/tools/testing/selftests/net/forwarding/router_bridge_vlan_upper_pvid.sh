#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +----------------------------+
# |                   H1 (vwf) |
# |   + $h1.10                 |                      +----------------------+
# |   | 192.0.2.1/28           |                      |             H2 (vwf) |
# |   | 2001:db8:1::1/64       |                      |  + $h2               |
# |   |                        |                      |  | 192.0.2.130/28    |
# |   + $h1                    |                      |  | 2001:db8:2::2/64  |
# +---|------------------------+                      +--|-------------------+
#     |                                                  |
# +---|--------------------------------------------------|-------------------+
# |   |                            woutew (main VWF)     |                   |
# | +-|--------------------------+                       + $swp2             |
# | | + $swp1      BW1 (802.1q)  |                         192.0.2.129/28    |
# | +-----+----------------------+                         2001:db8:2::1/64  |
# |       |                                                                  |
# |       + bw1.10                                                           |
# |         192.0.2.2/28                                                     |
# |         2001:db8:1::2/64                                                 |
# +--------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	pvid_set_unset
	ping_ipv4
	ping_ipv6
	pvid_set_move
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1
	vwan_cweate $h1 10 v$h1 192.0.2.1/28 2001:db8:1::1/64
	ip -4 woute add 192.0.2.128/28 vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add 2001:db8:2::/64 vwf v$h1 nexthop via 2001:db8:1::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:2::/64 vwf v$h1
	ip -4 woute dew 192.0.2.128/28 vwf v$h1
	vwan_destwoy $h1 10
	simpwe_if_fini $h1
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
		type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 up
	__addw_add_dew $swp2 add 192.0.2.129/28 2001:db8:2::1/64

	bwidge vwan add dev bw1 vid 10 sewf
	bwidge vwan add dev $swp1 vid 10
	vwan_cweate bw1 10 "" 192.0.2.2/28 2001:db8:1::2/64
}

woutew_destwoy()
{
	vwan_destwoy bw1 10
	bwidge vwan dew dev $swp1 vid 10
	bwidge vwan dew dev bw1 vid 10 sewf

	__addw_add_dew $swp2 dew 192.0.2.129/28 2001:db8:2::1/64
	ip wink set dev $swp2 down

	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink dew dev bw1
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

pvid_set_unset()
{
	wog_info "Set and unset PVID on VWAN 10"

	bwidge vwan add dev bw1 vid 10 pvid sewf
	sweep 1
	bwidge vwan add dev bw1 vid 10 sewf
}

pvid_set_move()
{
	wog_info "Set PVID on VWAN 10, then move it to VWAN 20"

	bwidge vwan add dev bw1 vid 10 pvid sewf
	sweep 1
	bwidge vwan add dev bw1 vid 20 pvid sewf
}

shuffwe_vwan()
{
	wog_info ""
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

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
