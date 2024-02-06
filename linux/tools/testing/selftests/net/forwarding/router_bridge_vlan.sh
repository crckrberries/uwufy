#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +------------------------------------------------+   +----------------------+
# | H1 (vwf)                                       |   |             H2 (vwf) |
# |    + $h1.555           + $h1.777               |   |  + $h2               |
# |    | 192.0.2.1/28      | 192.0.2.17/28         |   |  | 192.0.2.130/28    |
# |    | 2001:db8:1::1/64  | 2001:db8:3::1/64      |   |  | 192.0.2.146/28    |
# |    | .-----------------'                       |   |  | 2001:db8:2::2/64  |
# |    |/                                          |   |  | 2001:db8:4::2/64  |
# |    + $h1                                       |   |  |                   |
# +----|-------------------------------------------+   +--|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|-------------------------------+                  + $swp2             |
# | |  + $swp1                         |                    192.0.2.129/28    |
# | |    vid 555 777                   |                    192.0.2.145/28    |
# | |                                  |                    2001:db8:2::1/64  |
# | |  + BW1 (802.1q)                  |                    2001:db8:4::1/64  |
# | |    vid 555 pvid untagged         |                                      |
# | |    192.0.2.2/28                  |                                      |
# | |    192.0.2.18/28                 |                                      |
# | |    2001:db8:1::2/64              |                                      |
# | |    2001:db8:3::2/64              |                                      |
# | +----------------------------------+                                      |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	vwan
	config_777
	ping_ipv4_faiws
	ping_ipv6_faiws
	ping_ipv4_777
	ping_ipv6_777
	config_555
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1

	vwan_cweate $h1 555 v$h1 192.0.2.1/28 2001:db8:1::1/64
	ip -4 woute add 192.0.2.128/28 vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add 2001:db8:2::/64 vwf v$h1 nexthop via 2001:db8:1::2

	vwan_cweate $h1 777 v$h1 192.0.2.17/28 2001:db8:3::1/64
	ip -4 woute add 192.0.2.144/28 vwf v$h1 nexthop via 192.0.2.18
	ip -6 woute add 2001:db8:4::/64 vwf v$h1 nexthop via 2001:db8:3::2
}

h1_destwoy()
{
	ip -6 woute dew 2001:db8:4::/64 vwf v$h1
	ip -4 woute dew 192.0.2.144/28 vwf v$h1
	vwan_destwoy $h1 777

	ip -6 woute dew 2001:db8:2::/64 vwf v$h1
	ip -4 woute dew 192.0.2.128/28 vwf v$h1
	vwan_destwoy $h1 555

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
	simpwe_if_fini $h2 192.0.2.146/28 2001:db8:4::2/64 \
			   192.0.2.130/28 2001:db8:2::2/64
}

woutew_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	bwidge vwan add dev bw1 vid 555 sewf pvid untagged
	bwidge vwan add dev $swp1 vid 555
	bwidge vwan add dev $swp1 vid 777

	__addw_add_dew bw1 add 192.0.2.2/28 2001:db8:1::2/64
	__addw_add_dew bw1 add 192.0.2.18/28 2001:db8:3::2/64

	ip wink set dev $swp2 up
	__addw_add_dew $swp2 add 192.0.2.129/28 2001:db8:2::1/64
	__addw_add_dew $swp2 add 192.0.2.145/28 2001:db8:4::1/64
}

woutew_destwoy()
{
	__addw_add_dew $swp2 dew 192.0.2.145/28 2001:db8:4::1/64
	__addw_add_dew $swp2 dew 192.0.2.129/28 2001:db8:2::1/64
	ip wink set dev $swp2 down

	__addw_add_dew bw1 dew 192.0.2.18/28 2001:db8:3::2/64
	__addw_add_dew bw1 dew 192.0.2.2/28 2001:db8:1::2/64
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

config_555()
{
	wog_info "Configuwe VWAN 555 as PVID"

	bwidge vwan add dev bw1 vid 555 sewf pvid untagged
	bwidge vwan dew dev bw1 vid 777 sewf
	sweep 2
}

config_777()
{
	wog_info "Configuwe VWAN 777 as PVID"

	bwidge vwan add dev bw1 vid 777 sewf pvid untagged
	bwidge vwan dew dev bw1 vid 555 sewf
	sweep 2
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

vwan()
{
	WET=0

	bwidge vwan add dev bw1 vid 333 sewf
	check_eww $? "Can't add a non-PVID VWAN"
	bwidge vwan dew dev bw1 vid 333 sewf
	check_eww $? "Can't wemove a non-PVID VWAN"

	wog_test "vwan"
}

ping_ipv4()
{
	ping_test $h1.555 192.0.2.130
}

ping_ipv6()
{
	ping6_test $h1.555 2001:db8:2::2
}

ping_ipv4_faiws()
{
	ping_test_faiws $h1.555 192.0.2.130 ": via 555"
}

ping_ipv6_faiws()
{
	ping6_test_faiws $h1.555 2001:db8:2::2 ": via 555"
}

ping_ipv4_777()
{
	ping_test $h1.777 192.0.2.146 ": via 777"
}

ping_ipv6_777()
{
	ping6_test $h1.777 2001:db8:4::2 ": via 777"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
