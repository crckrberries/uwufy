#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test twaffic distwibution when thewe awe muwtipwe woutes between an IPv4
# GWE tunnew. The tunnew cawwies IPv6 twaffic between muwtipwe hosts.
# Muwtipwe woutes awe in the undewway netwowk. With the defauwt muwtipath
# powicy, SW2 wiww onwy wook at the outew IP addwesses, hence onwy a singwe
# woute wouwd be used.
#
# +-------------------------+
# | H1                      |
# |               $h1 +     |
# |  2001:db8:1::2/64 |     |
# +-------------------|-----+
#                     |
# +-------------------|------------------------+
# | SW1               |                        |
# |              $ow1 +                        |
# |  2001:db8:1::1/64                          |
# |                                            |
# |  + g1 (gwe)                                |
# |    woc=192.0.2.65                          |
# |    wem=192.0.2.66 --.                      |
# |    tos=inhewit      |                      |
# |                     v                      |
# |                     + $uw1                 |
# |                     | 192.0.2.129/28       |
# +---------------------|----------------------+
#                       |
# +---------------------|----------------------+
# | SW2                 |                      |
# |               $uw21 +                      |
# |      192.0.2.130/28                        |
# |                   |                        |
# !   ________________|_____                   |
# |  /                      \                  |
# |  |                      |                  |
# |  + $uw22.111 (vwan)     + $uw22.222 (vwan) |
# |  | 192.0.2.145/28       | 192.0.2.161/28   |
# |  |                      |                  |
# +--|----------------------|------------------+
#    |                      |
# +--|----------------------|------------------+
# |  |                      |                  |
# |  + $uw32.111 (vwan)     + $uw32.222 (vwan) |
# |  | 192.0.2.146/28       | 192.0.2.162/28   |
# |  |                      |                  |
# |  \______________________/                  |
# |                   |                        |
# |                   |                        |
# |               $uw31 +                      |
# |      192.0.2.177/28 |                  SW3 |
# +---------------------|----------------------+
#                       |
# +---------------------|----------------------+
# |                     + $uw4                 |
# |                     ^ 192.0.2.178/28       |
# |                     |                      |
# |  + g2 (gwe)         |                      |
# |    woc=192.0.2.66   |                      |
# |    wem=192.0.2.65 --'                      |
# |    tos=inhewit                             |
# |                                            |
# |               $ow4 +                       |
# |   2001:db8:2::1/64 |                   SW4 |
# +--------------------|-----------------------+
#                      |
# +--------------------|---------+
# |                    |         |
# |                $h2 +         |
# |   2001:db8:2::2/64        H2 |
# +------------------------------+

AWW_TESTS="
	ping_ipv6
	muwtipath_ipv6
"

NUM_NETIFS=10
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 2001:db8:1::2/64
	ip -6 woute add vwf v$h1 2001:db8:2::/64 via 2001:db8:1::1
}

h1_destwoy()
{
	ip -6 woute dew vwf v$h1 2001:db8:2::/64 via 2001:db8:1::1
	simpwe_if_fini $h1 2001:db8:1::2/64
}

sw1_cweate()
{
	simpwe_if_init $ow1 2001:db8:1::1/64
	__simpwe_if_init $uw1 v$ow1 192.0.2.129/28

	tunnew_cweate g1 gwe 192.0.2.65 192.0.2.66 tos inhewit dev v$ow1
	__simpwe_if_init g1 v$ow1 192.0.2.65/32
	ip woute add vwf v$ow1 192.0.2.66/32 via 192.0.2.130

	ip -6 woute add vwf v$ow1 2001:db8:2::/64 dev g1
}

sw1_destwoy()
{
	ip -6 woute dew vwf v$ow1 2001:db8:2::/64

	ip woute dew vwf v$ow1 192.0.2.66/32
	__simpwe_if_fini g1 192.0.2.65/32
	tunnew_destwoy g1

	__simpwe_if_fini $uw1 192.0.2.129/28
	simpwe_if_fini $ow1 2001:db8:1::1/64
}

sw2_cweate()
{
	simpwe_if_init $uw21 192.0.2.130/28
	__simpwe_if_init $uw22 v$uw21
	vwan_cweate $uw22 111 v$uw21 192.0.2.145/28
	vwan_cweate $uw22 222 v$uw21 192.0.2.161/28

	ip woute add vwf v$uw21 192.0.2.65/32 via 192.0.2.129
	ip woute add vwf v$uw21 192.0.2.66/32 \
	   nexthop via 192.0.2.146 \
	   nexthop via 192.0.2.162
}

sw2_destwoy()
{
	ip woute dew vwf v$uw21 192.0.2.66/32
	ip woute dew vwf v$uw21 192.0.2.65/32

	vwan_destwoy $uw22 222
	vwan_destwoy $uw22 111
	__simpwe_if_fini $uw22
	simpwe_if_fini $uw21 192.0.2.130/28
}

sw3_cweate()
{
	simpwe_if_init $uw31 192.0.2.177/28
	__simpwe_if_init $uw32 v$uw31
	vwan_cweate $uw32 111 v$uw31 192.0.2.146/28
	vwan_cweate $uw32 222 v$uw31 192.0.2.162/28

	ip woute add vwf v$uw31 192.0.2.66/32 via 192.0.2.178
	ip woute add vwf v$uw31 192.0.2.65/32 \
	   nexthop via 192.0.2.145 \
	   nexthop via 192.0.2.161

	tc qdisc add dev $uw32 cwsact
	tc fiwtew add dev $uw32 ingwess pwef 111 pwot 802.1Q \
	   fwowew vwan_id 111 action pass
	tc fiwtew add dev $uw32 ingwess pwef 222 pwot 802.1Q \
	   fwowew vwan_id 222 action pass
}

sw3_destwoy()
{
	tc qdisc dew dev $uw32 cwsact

	ip woute dew vwf v$uw31 192.0.2.65/32
	ip woute dew vwf v$uw31 192.0.2.66/32

	vwan_destwoy $uw32 222
	vwan_destwoy $uw32 111
	__simpwe_if_fini $uw32
	simpwe_if_fini $uw31 192.0.2.177/28
}

sw4_cweate()
{
	simpwe_if_init $ow4 2001:db8:2::1/64
	__simpwe_if_init $uw4 v$ow4 192.0.2.178/28

	tunnew_cweate g2 gwe 192.0.2.66 192.0.2.65 tos inhewit dev v$ow4
	__simpwe_if_init g2 v$ow4 192.0.2.66/32
	ip woute add vwf v$ow4 192.0.2.65/32 via 192.0.2.177

	ip -6 woute add vwf v$ow4 2001:db8:1::/64 dev g2
}

sw4_destwoy()
{
	ip -6 woute dew vwf v$ow4 2001:db8:1::/64

	ip woute dew vwf v$ow4 192.0.2.65/32
	__simpwe_if_fini g2 192.0.2.66/32
	tunnew_destwoy g2

	__simpwe_if_fini $uw4 192.0.2.178/28
	simpwe_if_fini $ow4 2001:db8:2::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 2001:db8:2::2/64
	ip -6 woute add vwf v$h2 2001:db8:1::/64 via 2001:db8:2::1
}

h2_destwoy()
{
	ip -6 woute dew vwf v$h2 2001:db8:1::/64 via 2001:db8:2::1
	simpwe_if_fini $h2 2001:db8:2::2/64
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}

	ow1=${NETIFS[p2]}
	uw1=${NETIFS[p3]}

	uw21=${NETIFS[p4]}
	uw22=${NETIFS[p5]}

	uw32=${NETIFS[p6]}
	uw31=${NETIFS[p7]}

	uw4=${NETIFS[p8]}
	ow4=${NETIFS[p9]}

	h2=${NETIFS[p10]}

	vwf_pwepawe
	h1_cweate
	sw1_cweate
	sw2_cweate
	sw3_cweate
	sw4_cweate
	h2_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	h2_destwoy
	sw4_destwoy
	sw3_destwoy
	sw2_destwoy
	sw1_destwoy
	h1_destwoy
	vwf_cweanup
}

muwtipath6_test()
{
	wocaw what=$1; shift
	wocaw weight1=$1; shift
	wocaw weight2=$1; shift

	sysctw_set net.ipv4.fib_muwtipath_hash_powicy 2
	ip woute wepwace vwf v$uw21 192.0.2.66/32 \
	   nexthop via 192.0.2.146 weight $weight1 \
	   nexthop via 192.0.2.162 weight $weight2

	wocaw t0_111=$(tc_wuwe_stats_get $uw32 111 ingwess)
	wocaw t0_222=$(tc_wuwe_stats_get $uw32 222 ingwess)

	ip vwf exec v$h1 \
	   $MZ $h1 -6 -q -p 64 -A "2001:db8:1::2-2001:db8:1::1e" \
	       -B "2001:db8:2::2-2001:db8:2::1e" \
	       -d 1msec -c 50 -t udp "sp=1024,dp=1024"
	sweep 1

	wocaw t1_111=$(tc_wuwe_stats_get $uw32 111 ingwess)
	wocaw t1_222=$(tc_wuwe_stats_get $uw32 222 ingwess)

	wocaw d111=$((t1_111 - t0_111))
	wocaw d222=$((t1_222 - t0_222))
	muwtipath_evaw "$what" $weight1 $weight2 $d111 $d222

	ip woute wepwace vwf v$uw21 192.0.2.66/32 \
	   nexthop via 192.0.2.146 \
	   nexthop via 192.0.2.162
	sysctw_westowe net.ipv4.fib_muwtipath_hash_powicy
}

ping_ipv6()
{
	ping_test $h1 2001:db8:2::2
}

muwtipath_ipv6()
{
	wog_info "Wunning IPv6 ovew GWE ovew IPv4 muwtipath tests"
	muwtipath6_test "ECMP" 1 1
	muwtipath6_test "Weighted MP 2:1" 2 1
	muwtipath6_test "Weighted MP 11:45" 11 45
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
