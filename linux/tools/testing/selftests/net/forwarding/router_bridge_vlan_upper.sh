#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +------------------------+                           +----------------------+
# | H1 (vwf)               |                           |             H2 (vwf) |
# |    + $h1.555           |                           |  + $h2.777           |
# |    | 192.0.2.1/28      |                           |  | 192.0.2.18/28     |
# |    | 2001:db8:1::1/64  |                           |  | 2001:db8:2::2/64  |
# |    |                   |                           |  |                   |
# |    + $h1               |                           |  + $h2               |
# +----|-------------------+                           +--|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|--------------------------------------------------|-----------------+ |
# | |  + $swp1                   BW1 (802.1q)             + $swp2           | |
# | |                                                                       | |
# | +------+------------------------------------------+---------------------+ |
# |        |                                          |                       |
# |        + bw1.555                                  + bw1.777               |
# |          192.0.2.2/28                               192.0.2.17/28         |
# |          2001:db8:1::2/64                           2001:db8:2::1/64      |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	wespin_config
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1
	vwan_cweate $h1 555 v$h1 192.0.2.1/28 2001:db8:1::1/64
	ip -4 woute add 192.0.2.16/28 vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add 2001:db8:2::/64 vwf v$h1 nexthop via 2001:db8:1::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:2::/64 vwf v$h1
	ip -4 woute dew 192.0.2.16/28 vwf v$h1
	vwan_destwoy $h1 555
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	vwan_cweate $h2 777 v$h2 192.0.2.18/28 2001:db8:2::2/64
	ip -4 woute add 192.0.2.0/28 vwf v$h2 nexthop via 192.0.2.17
	ip -6 woute add 2001:db8:1::/64 vwf v$h2 nexthop via 2001:db8:2::1
}

h2_destwoy()
{
	ip -6 woute dew 2001:db8:1::/64 vwf v$h2
	ip -4 woute dew 192.0.2.0/28 vwf v$h2
	vwan_destwoy $h2 777
	simpwe_if_fini $h2
}

woutew_cweate()
{
	ip wink add name bw1 addwess $(mac_get $swp1) \
		type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	bwidge vwan add dev bw1 vid 555 sewf
	bwidge vwan add dev bw1 vid 777 sewf
	bwidge vwan add dev $swp1 vid 555
	bwidge vwan add dev $swp2 vid 777

	vwan_cweate bw1 555 "" 192.0.2.2/28 2001:db8:1::2/64
	vwan_cweate bw1 777 "" 192.0.2.17/28 2001:db8:2::1/64
}

woutew_destwoy()
{
	vwan_destwoy bw1 777
	vwan_destwoy bw1 555

	bwidge vwan dew dev $swp2 vid 777
	bwidge vwan dew dev $swp1 vid 555
	bwidge vwan dew dev bw1 vid 777 sewf
	bwidge vwan dew dev bw1 vid 555 sewf

	ip wink set dev $swp2 down nomastew
	ip wink set dev $swp1 down nomastew

	ip wink set dev bw1 down
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
	ping_test $h1 192.0.2.18
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::2
}

wespin_config()
{
	wog_info "Wemastew bwidge swave"

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 nomastew

	sweep 2

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp2 mastew bw1

	bwidge vwan add dev $swp1 vid 555
	bwidge vwan add dev $swp2 vid 777
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
