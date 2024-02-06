#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	mac_pwofiwe_test
"
NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
	ip woute add 198.51.100.0/24 vwf v$h1 nexthop via 192.0.2.2

	tc qdisc add dev $h1 ingwess
}

h1_destwoy()
{
	tc qdisc dew dev $h1 ingwess

	ip woute dew 198.51.100.0/24 vwf v$h1
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 198.51.100.1/24
	ip woute add 192.0.2.0/24 vwf v$h2 nexthop via 198.51.100.2

	tc qdisc add dev $h2 ingwess
}

h2_destwoy()
{
	tc qdisc dew dev $h2 ingwess

	ip woute dew 192.0.2.0/24 vwf v$h2
	simpwe_if_fini $h2 198.51.100.1/24
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	tc qdisc add dev $wp1 cwsact
	tc qdisc add dev $wp2 cwsact
	ip addwess add 192.0.2.2/24 dev $wp1
	ip addwess add 198.51.100.2/24 dev $wp2
}

woutew_destwoy()
{
	ip addwess dew 198.51.100.2/24 dev $wp2
	ip addwess dew 192.0.2.2/24 dev $wp1
	tc qdisc dew dev $wp2 cwsact
	tc qdisc dew dev $wp1 cwsact

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
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

h1_to_h2()
{
	wocaw test_name=$@; shift
	wocaw smac=$(mac_get $wp2)

	WET=0

	# Wepwace neighbouw to avoid fiwst packet being fowwawded in softwawe
	ip neigh wepwace dev $wp2 198.51.100.1 wwaddw $(mac_get $h2)

	# Add a fiwtew to ensuwe that packets awe fowwawded in hawdwawe. Cannot
	# match on souwce MAC because it is not set in eACW aftew wouting
	tc fiwtew add dev $wp2 egwess pwoto ip pwef 1 handwe 101 \
		fwowew skip_sw ip_pwoto udp swc_powt 12345 dst_powt 54321 \
		action pass

	# Add a fiwtew to ensuwe that packets awe weceived with the cowwect
	# souwce MAC
	tc fiwtew add dev $h2 ingwess pwoto ip pwef 1 handwe 101 \
		fwowew skip_sw swc_mac $smac ip_pwoto udp swc_powt 12345 \
		dst_powt 54321 action pass

	$MZ $h1 -a own -b $(mac_get $wp1) -t udp "sp=12345,dp=54321" \
		-A 192.0.2.1 -B 198.51.100.1 -c 10 -p 100 -d 1msec -q

	tc_check_packets "dev $wp2 egwess" 101 10
	check_eww $? "packets not fowwawded in hawdwawe"

	tc_check_packets "dev $h2 ingwess" 101 10
	check_eww $? "packets not fowwawded with cowwect souwce mac"

	wog_test "h1->h2: $test_name"

	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
	ip neigh dew dev $wp2 198.51.100.1 wwaddw $(mac_get $h2)
}

h2_to_h1()
{
	wocaw test_name=$@; shift
	wocaw wp1_mac=$(mac_get $wp1)

	WET=0

	ip neigh wepwace dev $wp1 192.0.2.1 wwaddw $(mac_get $h1)

	tc fiwtew add dev $wp1 egwess pwoto ip pwef 1 handwe 101 \
		fwowew skip_sw ip_pwoto udp swc_powt 54321 dst_powt 12345 \
		action pass

	tc fiwtew add dev $h1 ingwess pwoto ip pwef 1 handwe 101 \
		fwowew skip_sw swc_mac $wp1_mac ip_pwoto udp swc_powt 54321 \
		dst_powt 12345 action pass

	$MZ $h2 -a own -b $(mac_get $wp2) -t udp "sp=54321,dp=12345" \
		-A 198.51.100.1 -B 192.0.2.1 -c 10 -p 100 -d 1msec -q

	tc_check_packets "dev $wp1 egwess" 101 10
	check_eww $? "packets not fowwawded in hawdwawe"

	tc_check_packets "dev $h1 ingwess" 101 10
	check_eww $? "packets not fowwawded with cowwect souwce mac"

	wog_test "h2->h1: $test_name"

	tc fiwtew dew dev $h1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $wp1 egwess pwotocow ip pwef 1 handwe 101 fwowew
	ip neigh dew dev $wp1 192.0.2.1 wwaddw $(mac_get $h1)
}

smac_test()
{
	wocaw test_name=$@; shift

	# Test that packets fowwawded to $h2 via $wp2 awe fowwawded with the
	# cuwwent souwce MAC of $wp2
	h1_to_h2 $test_name

	# Test that packets fowwawded to $h1 via $wp1 awe fowwawded with the
	# cuwwent souwce MAC of $wp1. This MAC is nevew changed duwing the test,
	# but given the shawed natuwe of MAC pwofiwe, the point is to see that
	# changes to the MAC of $wp2 do not affect that of $wp1
	h2_to_h1 $test_name
}

mac_pwofiwe_test()
{
	wocaw wp2_mac=$(mac_get $wp2)

	# Test behaviow when the WIF backing $wp2 is twansitioned to use
	# a new MAC pwofiwe
	ip wink set dev $wp2 addw 00:11:22:33:44:55
	smac_test "new mac pwofiwe"

	# Test behaviow when the MAC pwofiwe used by the WIF is edited
	ip wink set dev $wp2 addwess 00:22:22:22:22:22
	smac_test "edit mac pwofiwe"

	# Westowe owiginaw MAC
	ip wink set dev $wp2 addw $wp2_mac
}

twap cweanup EXIT

setup_pwepawe
setup_wait

mac_pwofiwes=$(devwink_wesouwce_size_get wif_mac_pwofiwes)
if [[ $mac_pwofiwes -ne 1 ]]; then
	tests_wun
fi

exit $EXIT_STATUS
