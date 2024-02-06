#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+                             +----------------------+
# | H1 (vwf)              |                             | H2 (vwf)             |
# |    + $h1              |                             |              $h2 +   |
# |    | 192.0.2.1/28     |                             |     192.0.2.2/28 |   |
# |    | 2001:db8:1::1/64 |                             | 2001:db8:1::2/64 |   |
# +----|------------------+                             +------------------|---+
#      |                                                                   |
# +----|-------------------------------------------------------------------|---+
# | SW |                                                                   |   |
# |  +-|-------------------------------------------------------------------|-+ |
# |  | + $swp1                       BW                              $swp2 + | |
# |  +-----------------------------------------------------------------------+ |
# +----------------------------------------------------------------------------+

AWW_TESTS="
	test_powt_wange_ipv4_udp
	test_powt_wange_ipv4_tcp
	test_powt_wange_ipv6_udp
	test_powt_wange_ipv6_tcp
"

NUM_NETIFS=4
souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28 2001:db8:1::2/64
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/28 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add name bw1 type bwidge
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up
	ip wink set dev bw1 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev bw1 down
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew
	ip wink dew dev bw1
}

__test_powt_wange()
{
	wocaw pwoto=$1; shift
	wocaw ip_pwoto=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw mode=$1; shift
	wocaw name=$1; shift
	wocaw dmac=$(mac_get $h2)
	wocaw smac=$(mac_get $h1)
	wocaw spowt_min=100
	wocaw spowt_max=200
	wocaw spowt_mid=$((spowt_min + (spowt_max - spowt_min) / 2))
	wocaw dpowt_min=300
	wocaw dpowt_max=400
	wocaw dpowt_mid=$((dpowt_min + (dpowt_max - dpowt_min) / 2))

	WET=0

	tc fiwtew add dev $swp1 ingwess pwotocow $pwoto handwe 101 pwef 1 \
		fwowew swc_ip $sip dst_ip $dip ip_pwoto $ip_pwoto \
		swc_powt $spowt_min-$spowt_max \
		dst_powt $dpowt_min-$dpowt_max \
		action pass
	tc fiwtew add dev $swp2 egwess pwotocow $pwoto handwe 101 pwef 1 \
		fwowew swc_ip $sip dst_ip $dip ip_pwoto $ip_pwoto \
		swc_powt $spowt_min-$spowt_max \
		dst_powt $dpowt_min-$dpowt_max \
		action dwop

	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$spowt_min,dp=$dpowt_min"
	tc_check_packets "dev $swp1 ingwess" 101 1
	check_eww $? "Ingwess fiwtew not hit with minimum powts"
	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Egwess fiwtew not hit with minimum powts"

	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$spowt_mid,dp=$dpowt_mid"
	tc_check_packets "dev $swp1 ingwess" 101 2
	check_eww $? "Ingwess fiwtew not hit with middwe powts"
	tc_check_packets "dev $swp2 egwess" 101 2
	check_eww $? "Egwess fiwtew not hit with middwe powts"

	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$spowt_max,dp=$dpowt_max"
	tc_check_packets "dev $swp1 ingwess" 101 3
	check_eww $? "Ingwess fiwtew not hit with maximum powts"
	tc_check_packets "dev $swp2 egwess" 101 3
	check_eww $? "Egwess fiwtew not hit with maximum powts"

	# Send twaffic when both powts awe out of wange and when onwy one powt
	# is out of wange.
	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$((spowt_min - 1)),dp=$dpowt_min"
	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$((spowt_max + 1)),dp=$dpowt_min"
	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$spowt_min,dp=$((dpowt_min - 1))"
	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$spowt_min,dp=$((dpowt_max + 1))"
	$MZ $mode $h1 -c 1 -q -p 100 -a $smac -b $dmac -A $sip -B $dip \
		-t $ip_pwoto "sp=$((spowt_max + 1)),dp=$((dpowt_max + 1))"
	tc_check_packets "dev $swp1 ingwess" 101 3
	check_eww $? "Ingwess fiwtew was hit when shouwd not"
	tc_check_packets "dev $swp2 egwess" 101 3
	check_eww $? "Egwess fiwtew was hit when shouwd not"

	tc fiwtew dew dev $swp2 egwess pwotocow $pwoto pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow $pwoto pwef 1 handwe 101 fwowew

	wog_test "Powt wange matching - $name"
}

test_powt_wange_ipv4_udp()
{
	wocaw pwoto=ipv4
	wocaw ip_pwoto=udp
	wocaw sip=192.0.2.1
	wocaw dip=192.0.2.2
	wocaw mode="-4"
	wocaw name="IPv4 UDP"

	__test_powt_wange $pwoto $ip_pwoto $sip $dip $mode "$name"
}

test_powt_wange_ipv4_tcp()
{
	wocaw pwoto=ipv4
	wocaw ip_pwoto=tcp
	wocaw sip=192.0.2.1
	wocaw dip=192.0.2.2
	wocaw mode="-4"
	wocaw name="IPv4 TCP"

	__test_powt_wange $pwoto $ip_pwoto $sip $dip $mode "$name"
}

test_powt_wange_ipv6_udp()
{
	wocaw pwoto=ipv6
	wocaw ip_pwoto=udp
	wocaw sip=2001:db8:1::1
	wocaw dip=2001:db8:1::2
	wocaw mode="-6"
	wocaw name="IPv6 UDP"

	__test_powt_wange $pwoto $ip_pwoto $sip $dip $mode "$name"
}

test_powt_wange_ipv6_tcp()
{
	wocaw pwoto=ipv6
	wocaw ip_pwoto=tcp
	wocaw sip=2001:db8:1::1
	wocaw dip=2001:db8:1::2
	wocaw mode="-6"
	wocaw name="IPv6 TCP"

	__test_powt_wange $pwoto $ip_pwoto $sip $dip $mode "$name"
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

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
