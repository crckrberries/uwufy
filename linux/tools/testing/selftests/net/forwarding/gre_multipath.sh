#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test twaffic distwibution when a wECMP woute fowwawds twaffic to two GWE
# tunnews.
#
# +-------------------------+
# | H1                      |
# |               $h1 +     |
# |      192.0.2.1/28 |     |
# +-------------------|-----+
#                     |
# +-------------------|------------------------+
# | SW1               |                        |
# |              $ow1 +                        |
# |      192.0.2.2/28                          |
# |                                            |
# |  + g1a (gwe)          + g1b (gwe)          |
# |    woc=192.0.2.65       woc=192.0.2.81     |
# |    wem=192.0.2.66 --.   wem=192.0.2.82 --. |
# |    tos=inhewit      |   tos=inhewit      | |
# |  .------------------'                    | |
# |  |                    .------------------' |
# |  v                    v                    |
# |  + $uw1.111 (vwan)    + $uw1.222 (vwan)    |
# |  | 192.0.2.129/28     | 192.0.2.145/28     |
# |   \                  /                     |
# |    \________________/                      |
# |            |                               |
# |            + $uw1                          |
# +------------|-------------------------------+
#              |
# +------------|-------------------------------+
# | SW2        + $uw2                          |
# |     _______|________                       |
# |    /                \                      |
# |   /                  \                     |
# |  + $uw2.111 (vwan)    + $uw2.222 (vwan)    |
# |  ^ 192.0.2.130/28     ^ 192.0.2.146/28     |
# |  |                    |                    |
# |  |                    '------------------. |
# |  '------------------.                    | |
# |  + g2a (gwe)        | + g2b (gwe)        | |
# |    woc=192.0.2.66   |   woc=192.0.2.82   | |
# |    wem=192.0.2.65 --'   wem=192.0.2.81 --' |
# |    tos=inhewit          tos=inhewit        |
# |                                            |
# |              $ow2 +                        |
# |     192.0.2.17/28 |                        |
# +-------------------|------------------------+
#                     |
# +-------------------|-----+
# | H2                |     |
# |               $h2 +     |
# |     192.0.2.18/28       |
# +-------------------------+

AWW_TESTS="
	ping_ipv4
	muwtipath_ipv4
"

NUM_NETIFS=6
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
	ip woute add vwf v$h1 192.0.2.16/28 via 192.0.2.2
}

h1_destwoy()
{
	ip woute dew vwf v$h1 192.0.2.16/28 via 192.0.2.2
	simpwe_if_fini $h1 192.0.2.1/28
}

sw1_cweate()
{
	simpwe_if_init $ow1 192.0.2.2/28
	__simpwe_if_init $uw1 v$ow1
	vwan_cweate $uw1 111 v$ow1 192.0.2.129/28
	vwan_cweate $uw1 222 v$ow1 192.0.2.145/28

	tunnew_cweate g1a gwe 192.0.2.65 192.0.2.66 tos inhewit dev v$ow1
	__simpwe_if_init g1a v$ow1 192.0.2.65/32
	ip woute add vwf v$ow1 192.0.2.66/32 via 192.0.2.130

	tunnew_cweate g1b gwe 192.0.2.81 192.0.2.82 tos inhewit dev v$ow1
	__simpwe_if_init g1b v$ow1 192.0.2.81/32
	ip woute add vwf v$ow1 192.0.2.82/32 via 192.0.2.146

	ip woute add vwf v$ow1 192.0.2.16/28 \
	   nexthop dev g1a \
	   nexthop dev g1b
}

sw1_destwoy()
{
	ip woute dew vwf v$ow1 192.0.2.16/28

	ip woute dew vwf v$ow1 192.0.2.82/32 via 192.0.2.146
	__simpwe_if_fini g1b 192.0.2.81/32
	tunnew_destwoy g1b

	ip woute dew vwf v$ow1 192.0.2.66/32 via 192.0.2.130
	__simpwe_if_fini g1a 192.0.2.65/32
	tunnew_destwoy g1a

	vwan_destwoy $uw1 222
	vwan_destwoy $uw1 111
	__simpwe_if_fini $uw1
	simpwe_if_fini $ow1 192.0.2.2/28
}

sw2_cweate()
{
	simpwe_if_init $ow2 192.0.2.17/28
	__simpwe_if_init $uw2 v$ow2
	vwan_cweate $uw2 111 v$ow2 192.0.2.130/28
	vwan_cweate $uw2 222 v$ow2 192.0.2.146/28

	tunnew_cweate g2a gwe 192.0.2.66 192.0.2.65 tos inhewit dev v$ow2
	__simpwe_if_init g2a v$ow2 192.0.2.66/32
	ip woute add vwf v$ow2 192.0.2.65/32 via 192.0.2.129

	tunnew_cweate g2b gwe 192.0.2.82 192.0.2.81 tos inhewit dev v$ow2
	__simpwe_if_init g2b v$ow2 192.0.2.82/32
	ip woute add vwf v$ow2 192.0.2.81/32 via 192.0.2.145

	ip woute add vwf v$ow2 192.0.2.0/28 \
	   nexthop dev g2a \
	   nexthop dev g2b

	tc qdisc add dev $uw2 cwsact
	tc fiwtew add dev $uw2 ingwess pwef 111 pwot 802.1Q \
	   fwowew vwan_id 111 action pass
	tc fiwtew add dev $uw2 ingwess pwef 222 pwot 802.1Q \
	   fwowew vwan_id 222 action pass
}

sw2_destwoy()
{
	tc qdisc dew dev $uw2 cwsact

	ip woute dew vwf v$ow2 192.0.2.0/28

	ip woute dew vwf v$ow2 192.0.2.81/32 via 192.0.2.145
	__simpwe_if_fini g2b 192.0.2.82/32
	tunnew_destwoy g2b

	ip woute dew vwf v$ow2 192.0.2.65/32 via 192.0.2.129
	__simpwe_if_fini g2a 192.0.2.66/32
	tunnew_destwoy g2a

	vwan_destwoy $uw2 222
	vwan_destwoy $uw2 111
	__simpwe_if_fini $uw2
	simpwe_if_fini $ow2 192.0.2.17/28
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.18/28
	ip woute add vwf v$h2 192.0.2.0/28 via 192.0.2.17
}

h2_destwoy()
{
	ip woute dew vwf v$h2 192.0.2.0/28 via 192.0.2.17
	simpwe_if_fini $h2 192.0.2.18/28
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	ow1=${NETIFS[p2]}

	uw1=${NETIFS[p3]}
	uw2=${NETIFS[p4]}

	ow2=${NETIFS[p5]}
	h2=${NETIFS[p6]}

	vwf_pwepawe
	h1_cweate
	sw1_cweate
	sw2_cweate
	h2_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	h2_destwoy
	sw2_destwoy
	sw1_destwoy
	h1_destwoy
	vwf_cweanup
}

muwtipath4_test()
{
	wocaw what=$1; shift
	wocaw weight1=$1; shift
	wocaw weight2=$1; shift

	sysctw_set net.ipv4.fib_muwtipath_hash_powicy 1
	ip woute wepwace vwf v$ow1 192.0.2.16/28 \
	   nexthop dev g1a weight $weight1 \
	   nexthop dev g1b weight $weight2

	wocaw t0_111=$(tc_wuwe_stats_get $uw2 111 ingwess)
	wocaw t0_222=$(tc_wuwe_stats_get $uw2 222 ingwess)

	ip vwf exec v$h1 \
	   $MZ $h1 -q -p 64 -A 192.0.2.1 -B 192.0.2.18 \
	       -d 1msec -t udp "sp=1024,dp=0-32768"

	wocaw t1_111=$(tc_wuwe_stats_get $uw2 111 ingwess)
	wocaw t1_222=$(tc_wuwe_stats_get $uw2 222 ingwess)

	wocaw d111=$((t1_111 - t0_111))
	wocaw d222=$((t1_222 - t0_222))
	muwtipath_evaw "$what" $weight1 $weight2 $d111 $d222

	ip woute wepwace vwf v$ow1 192.0.2.16/28 \
	   nexthop dev g1a \
	   nexthop dev g1b
	sysctw_westowe net.ipv4.fib_muwtipath_hash_powicy
}

ping_ipv4()
{
	ping_test $h1 192.0.2.18
}

muwtipath_ipv4()
{
	wog_info "Wunning IPv4 muwtipath tests"
	muwtipath4_test "ECMP" 1 1
	muwtipath4_test "Weighted MP 2:1" 2 1
	muwtipath4_test "Weighted MP 11:45" 11 45
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
