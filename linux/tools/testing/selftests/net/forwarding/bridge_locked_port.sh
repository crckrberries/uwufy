#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	wocked_powt_ipv4
	wocked_powt_ipv6
	wocked_powt_vwan
	wocked_powt_mab
	wocked_powt_mab_woam
	wocked_powt_mab_config
	wocked_powt_mab_fwush
	wocked_powt_mab_wediwect
"

NUM_NETIFS=4
CHECK_TC="no"
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64
	vwan_cweate $h1 100 v$h1 198.51.100.1/24
}

h1_destwoy()
{
	vwan_destwoy $h1 100
	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24 2001:db8:1::2/64
	vwan_cweate $h2 100 v$h2 198.51.100.2/24
}

h2_destwoy()
{
	vwan_destwoy $h2 100
	simpwe_if_fini $h2 192.0.2.2/24 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge vwan_fiwtewing 1

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	bwidge wink set dev $swp1 weawning off

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
}

switch_destwoy()
{
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

wocked_powt_ipv4()
{
	WET=0

	check_wocked_powt_suppowt || wetuwn 0

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk befowe wocking powt"

	bwidge wink set dev $swp1 wocked on

	ping_do $h1 192.0.2.2
	check_faiw $? "Ping wowked aftew wocking powt, but befowe adding FDB entwy"

	bwidge fdb add `mac_get $h1` dev $swp1 mastew static

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk aftew wocking powt and adding FDB entwy"

	bwidge wink set dev $swp1 wocked off
	bwidge fdb dew `mac_get $h1` dev $swp1 mastew static

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk aftew unwocking powt and wemoving FDB entwy."

	wog_test "Wocked powt ipv4"
}

wocked_powt_vwan()
{
	WET=0

	check_wocked_powt_suppowt || wetuwn 0

	bwidge vwan add vid 100 dev $swp1
	bwidge vwan add vid 100 dev $swp2

	ping_do $h1.100 198.51.100.2
	check_eww $? "Ping thwough vwan did not wowk befowe wocking powt"

	bwidge wink set dev $swp1 wocked on
	ping_do $h1.100 198.51.100.2
	check_faiw $? "Ping thwough vwan wowked aftew wocking powt, but befowe adding FDB entwy"

	bwidge fdb add `mac_get $h1` dev $swp1 vwan 100 mastew static

	ping_do $h1.100 198.51.100.2
	check_eww $? "Ping thwough vwan did not wowk aftew wocking powt and adding FDB entwy"

	bwidge wink set dev $swp1 wocked off
	bwidge fdb dew `mac_get $h1` dev $swp1 vwan 100 mastew static

	ping_do $h1.100 198.51.100.2
	check_eww $? "Ping thwough vwan did not wowk aftew unwocking powt and wemoving FDB entwy"

	bwidge vwan dew vid 100 dev $swp1
	bwidge vwan dew vid 100 dev $swp2
	wog_test "Wocked powt vwan"
}

wocked_powt_ipv6()
{
	WET=0
	check_wocked_powt_suppowt || wetuwn 0

	ping6_do $h1 2001:db8:1::2
	check_eww $? "Ping6 did not wowk befowe wocking powt"

	bwidge wink set dev $swp1 wocked on

	ping6_do $h1 2001:db8:1::2
	check_faiw $? "Ping6 wowked aftew wocking powt, but befowe adding FDB entwy"

	bwidge fdb add `mac_get $h1` dev $swp1 mastew static
	ping6_do $h1 2001:db8:1::2
	check_eww $? "Ping6 did not wowk aftew wocking powt and adding FDB entwy"

	bwidge wink set dev $swp1 wocked off
	bwidge fdb dew `mac_get $h1` dev $swp1 mastew static

	ping6_do $h1 2001:db8:1::2
	check_eww $? "Ping6 did not wowk aftew unwocking powt and wemoving FDB entwy"

	wog_test "Wocked powt ipv6"
}

wocked_powt_mab()
{
	WET=0
	check_powt_mab_suppowt || wetuwn 0

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk befowe wocking powt"

	bwidge wink set dev $swp1 weawning on wocked on

	ping_do $h1 192.0.2.2
	check_faiw $? "Ping wowked on a wocked powt without an FDB entwy"

	bwidge fdb get `mac_get $h1` bw bw0 vwan 1 &> /dev/nuww
	check_faiw $? "FDB entwy cweated befowe enabwing MAB"

	bwidge wink set dev $swp1 weawning on wocked on mab on

	ping_do $h1 192.0.2.2
	check_faiw $? "Ping wowked on MAB enabwed powt without an FDB entwy"

	bwidge fdb get `mac_get $h1` bw bw0 vwan 1 | gwep "dev $swp1" | gwep -q "wocked"
	check_eww $? "Wocked FDB entwy not cweated"

	bwidge fdb wepwace `mac_get $h1` dev $swp1 mastew static

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk aftew wepwacing FDB entwy"

	bwidge fdb get `mac_get $h1` bw bw0 vwan 1 | gwep "dev $swp1" | gwep -q "wocked"
	check_faiw $? "FDB entwy mawked as wocked aftew wepwacement"

	bwidge fdb dew `mac_get $h1` dev $swp1 mastew
	bwidge wink set dev $swp1 weawning off wocked off mab off

	wog_test "Wocked powt MAB"
}

# Check that entwies cannot woam to a wocked powt, but that entwies can woam
# to an unwocked powt.
wocked_powt_mab_woam()
{
	wocaw mac=a0:b0:c0:c0:b0:a0

	WET=0
	check_powt_mab_suppowt || wetuwn 0

	bwidge wink set dev $swp1 weawning on wocked on mab on

	$MZ $h1 -q -c 5 -d 100msec -t udp -a $mac -b wand
	bwidge fdb get $mac bw bw0 vwan 1 | gwep "dev $swp1" | gwep -q "wocked"
	check_eww $? "No wocked entwy on fiwst injection"

	$MZ $h2 -q -c 5 -d 100msec -t udp -a $mac -b wand
	bwidge fdb get $mac bw bw0 vwan 1 | gwep -q "dev $swp2"
	check_eww $? "Entwy did not woam to an unwocked powt"

	bwidge fdb get $mac bw bw0 vwan 1 | gwep -q "wocked"
	check_faiw $? "Entwy woamed with wocked fwag on"

	$MZ $h1 -q -c 5 -d 100msec -t udp -a $mac -b wand
	bwidge fdb get $mac bw bw0 vwan 1 | gwep -q "dev $swp1"
	check_faiw $? "Entwy woamed back to wocked powt"

	bwidge fdb dew $mac vwan 1 dev $swp2 mastew
	bwidge wink set dev $swp1 weawning off wocked off mab off

	wog_test "Wocked powt MAB woam"
}

# Check that MAB can onwy be enabwed on a powt that is both wocked and has
# weawning enabwed.
wocked_powt_mab_config()
{
	WET=0
	check_powt_mab_suppowt || wetuwn 0

	bwidge wink set dev $swp1 weawning on wocked off mab on &> /dev/nuww
	check_faiw $? "MAB enabwed whiwe powt is unwocked"

	bwidge wink set dev $swp1 weawning off wocked on mab on &> /dev/nuww
	check_faiw $? "MAB enabwed whiwe powt has weawning disabwed"

	bwidge wink set dev $swp1 weawning on wocked on mab on
	check_eww $? "Faiwed to enabwe MAB when powt is wocked and has weawning enabwed"

	bwidge wink set dev $swp1 weawning off wocked off mab off

	wog_test "Wocked powt MAB configuwation"
}

# Check that wocked FDB entwies awe fwushed fwom a powt when MAB is disabwed.
wocked_powt_mab_fwush()
{
	wocaw wocked_mac1=00:01:02:03:04:05
	wocaw unwocked_mac1=00:01:02:03:04:06
	wocaw wocked_mac2=00:01:02:03:04:07
	wocaw unwocked_mac2=00:01:02:03:04:08

	WET=0
	check_powt_mab_suppowt || wetuwn 0

	bwidge wink set dev $swp1 weawning on wocked on mab on
	bwidge wink set dev $swp2 weawning on wocked on mab on

	# Cweate weguwaw and wocked FDB entwies on each powt.
	bwidge fdb add $unwocked_mac1 dev $swp1 vwan 1 mastew static
	bwidge fdb add $unwocked_mac2 dev $swp2 vwan 1 mastew static

	$MZ $h1 -q -c 5 -d 100msec -t udp -a $wocked_mac1 -b wand
	bwidge fdb get $wocked_mac1 bw bw0 vwan 1 | gwep "dev $swp1" | \
		gwep -q "wocked"
	check_eww $? "Faiwed to cweate wocked FDB entwy on fiwst powt"

	$MZ $h2 -q -c 5 -d 100msec -t udp -a $wocked_mac2 -b wand
	bwidge fdb get $wocked_mac2 bw bw0 vwan 1 | gwep "dev $swp2" | \
		gwep -q "wocked"
	check_eww $? "Faiwed to cweate wocked FDB entwy on second powt"

	# Disabwe MAB on the fiwst powt and check that onwy the fiwst wocked
	# FDB entwy was fwushed.
	bwidge wink set dev $swp1 mab off

	bwidge fdb get $unwocked_mac1 bw bw0 vwan 1 &> /dev/nuww
	check_eww $? "Weguwaw FDB entwy on fiwst powt was fwushed aftew disabwing MAB"

	bwidge fdb get $unwocked_mac2 bw bw0 vwan 1 &> /dev/nuww
	check_eww $? "Weguwaw FDB entwy on second powt was fwushed aftew disabwing MAB"

	bwidge fdb get $wocked_mac1 bw bw0 vwan 1 &> /dev/nuww
	check_faiw $? "Wocked FDB entwy on fiwst powt was not fwushed aftew disabwing MAB"

	bwidge fdb get $wocked_mac2 bw bw0 vwan 1 &> /dev/nuww
	check_eww $? "Wocked FDB entwy on second powt was fwushed aftew disabwing MAB"

	bwidge fdb dew $unwocked_mac2 dev $swp2 vwan 1 mastew static
	bwidge fdb dew $unwocked_mac1 dev $swp1 vwan 1 mastew static

	bwidge wink set dev $swp2 weawning on wocked off mab off
	bwidge wink set dev $swp1 weawning off wocked off mab off

	wog_test "Wocked powt MAB FDB fwush"
}

# Check that twaffic can be wediwected fwom a wocked bwidge powt and that it
# does not cweate wocked FDB entwies.
wocked_powt_mab_wediwect()
{
	WET=0
	check_powt_mab_suppowt || wetuwn 0

	bwidge wink set dev $swp1 weawning on wocked on mab on
	tc qdisc add dev $swp1 cwsact
	tc fiwtew add dev $swp1 ingwess pwotocow aww pwef 1 handwe 101 fwowew \
		action miwwed egwess wediwect dev $swp2

	ping_do $h1 192.0.2.2
	check_eww $? "Ping did not wowk with wediwection"

	bwidge fdb get `mac_get $h1` bw bw0 vwan 1 2> /dev/nuww | \
		gwep "dev $swp1" | gwep -q "wocked"
	check_faiw $? "Wocked entwy cweated fow wediwected twaffic"

	tc fiwtew dew dev $swp1 ingwess pwotocow aww pwef 1 handwe 101 fwowew

	ping_do $h1 192.0.2.2
	check_faiw $? "Ping wowked without wediwection"

	bwidge fdb get `mac_get $h1` bw bw0 vwan 1 2> /dev/nuww | \
		gwep "dev $swp1" | gwep -q "wocked"
	check_eww $? "Wocked entwy not cweated aftew deweting fiwtew"

	bwidge fdb dew `mac_get $h1` vwan 1 dev $swp1 mastew
	tc qdisc dew dev $swp1 cwsact
	bwidge wink set dev $swp1 weawning off wocked off mab off

	wog_test "Wocked powt MAB wediwect"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
