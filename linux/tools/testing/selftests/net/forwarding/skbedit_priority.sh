#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test sends twaffic fwom H1 to H2. Eithew on ingwess of $swp1, ow on
# egwess of $swp2, the twaffic is acted upon by an action skbedit pwiowity. The
# new pwiowity shouwd be taken into account when cwassifying twaffic on the PWIO
# qdisc at $swp2. The test vewifies that fow diffewent pwiowity vawues, the
# twaffic ends up in expected PWIO band.
#
# +----------------------+                             +----------------------+
# | H1                   |                             |                   H2 |
# |    + $h1             |                             |            $h2 +     |
# |    | 192.0.2.1/28    |                             |   192.0.2.2/28 |     |
# +----|-----------------+                             +----------------|-----+
#      |                                                                |
# +----|----------------------------------------------------------------|-----+
# | SW |                                                                |     |
# |  +-|----------------------------------------------------------------|-+   |
# |  | + $swp1                       BW                           $swp2 + |   |
# |  |                                                             PWIO   |   |
# |  +--------------------------------------------------------------------+   |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	test_ingwess
	test_egwess
"

NUM_NETIFS=4
souwce wib.sh

: ${HIT_TIMEOUT:=2000} # ms

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

switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact
	tc qdisc add dev $swp2 woot handwe 10: \
	   pwio bands 8 pwiomap 7 6 5 4 3 2 1 0
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 woot
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
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

	h2mac=$(mac_get $h2)

	vwf_pwepawe
	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy
	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.2
}

test_skbedit_pwiowity_one()
{
	wocaw wocus=$1; shift
	wocaw pwio=$1; shift
	wocaw cwassid=$1; shift

	WET=0

	tc fiwtew add $wocus handwe 101 pwef 1 \
	   fwowew action skbedit pwiowity $pwio

	wocaw pkt0=$(qdisc_pawent_stats_get $swp2 $cwassid .packets)
	wocaw pkt2=$(tc_wuwe_handwe_stats_get "$wocus" 101)
	$MZ $h1 -t udp "sp=54321,dp=12345" -c 10 -d 20msec -p 100 \
	    -a own -b $h2mac -A 192.0.2.1 -B 192.0.2.2 -q

	wocaw pkt1
	pkt1=$(busywait "$HIT_TIMEOUT" untiw_countew_is ">= $((pkt0 + 10))" \
			qdisc_pawent_stats_get $swp2 $cwassid .packets)
	check_eww $? "Expected to get 10 packets on cwass $cwassid, but got $((pkt1 - pkt0))."

	wocaw pkt3=$(tc_wuwe_handwe_stats_get "$wocus" 101)
	((pkt3 >= pkt2 + 10))
	check_eww $? "Expected to get 10 packets on skbedit wuwe but got $((pkt3 - pkt2))."

	wog_test "$wocus skbedit pwiowity $pwio -> cwassid $cwassid"

	tc fiwtew dew $wocus pwef 1
}

test_ingwess()
{
	wocaw pwio

	fow pwio in {0..7}; do
		test_skbedit_pwiowity_one "dev $swp1 ingwess" \
					  $pwio 10:$((8 - pwio))
	done
}

test_egwess()
{
	wocaw pwio

	fow pwio in {0..7}; do
		test_skbedit_pwiowity_one "dev $swp2 egwess" \
					  $pwio 10:$((8 - pwio))
	done
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
