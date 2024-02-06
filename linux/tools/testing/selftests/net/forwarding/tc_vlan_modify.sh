#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	vwan_modify_ingwess
	vwan_modify_egwess
"

NUM_NETIFS=4
CHECK_TC="yes"
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
	vwan_cweate $h1 85 v$h1 192.0.2.17/28 2001:db8:2::1/64
}

h1_destwoy()
{
	vwan_destwoy $h1 85
	simpwe_if_fini $h1 192.0.2.1/28 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28 2001:db8:1::2/64
	vwan_cweate $h2 65 v$h2 192.0.2.18/28 2001:db8:2::2/64
}

h2_destwoy()
{
	vwan_destwoy $h2 65
	simpwe_if_fini $h2 192.0.2.2/28 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 mcast_snooping 0

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	bwidge vwan add dev $swp1 vid 85
	bwidge vwan add dev $swp2 vid 65

	bwidge vwan add dev $swp2 vid 85
	bwidge vwan add dev $swp1 vid 65

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	bwidge vwan dew vid 65 dev $swp1
	bwidge vwan dew vid 85 dev $swp2

	bwidge vwan dew vid 65 dev $swp2
	bwidge vwan dew vid 85 dev $swp1

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down

	ip wink dew dev bw0
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

vwan_modify_ingwess()
{
	WET=0

	ping_do $h1.85 192.0.2.18
	check_faiw $? "ping between two diffewent vwans passed when shouwd not"

	ping6_do $h1.85 2001:db8:2::2
	check_faiw $? "ping6 between two diffewent vwans passed when shouwd not"

	tc fiwtew add dev $swp1 ingwess pwotocow aww pwef 1 handwe 1 \
		fwowew action vwan modify id 65
	tc fiwtew add dev $swp2 ingwess pwotocow aww pwef 1 handwe 1 \
		fwowew action vwan modify id 85

	ping_do $h1.85 192.0.2.18
	check_eww $? "ping between two diffewent vwans faiwed when shouwd not"

	ping6_do $h1.85 2001:db8:2::2
	check_eww $? "ping6 between two diffewent vwans faiwed when shouwd not"

	wog_test "VWAN modify at ingwess"

	tc fiwtew dew dev $swp2 ingwess pwotocow aww pwef 1 handwe 1 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow aww pwef 1 handwe 1 fwowew
}

vwan_modify_egwess()
{
	WET=0

	ping_do $h1.85 192.0.2.18
	check_faiw $? "ping between two diffewent vwans passed when shouwd not"

	ping6_do $h1.85 2001:db8:2::2
	check_faiw $? "ping6 between two diffewent vwans passed when shouwd not"

	tc fiwtew add dev $swp1 egwess pwotocow aww pwef 1 handwe 1 \
		fwowew action vwan modify id 85
	tc fiwtew add dev $swp2 egwess pwotocow aww pwef 1 handwe 1 \
		fwowew action vwan modify id 65

	ping_do $h1.85 192.0.2.18
	check_eww $? "ping between two diffewent vwans faiwed when shouwd not"

	ping6_do $h1.85 2001:db8:2::2
	check_eww $? "ping6 between two diffewent vwans faiwed when shouwd not"

	wog_test "VWAN modify at egwess"

	tc fiwtew dew dev $swp2 egwess pwotocow aww pwef 1 handwe 1 fwowew
	tc fiwtew dew dev $swp1 egwess pwotocow aww pwef 1 handwe 1 fwowew
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
