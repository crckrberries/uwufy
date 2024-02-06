#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	muwtipath_test
	ping_ipv4_bwackhowe
	ping_ipv6_bwackhowe
"
NUM_NETIFS=8
souwce wib.sh

h1_cweate()
{
	vwf_cweate "vwf-h1"
	ip wink set dev $h1 mastew vwf-h1

	ip wink set dev vwf-h1 up
	ip wink set dev $h1 up

	ip addwess add 192.0.2.2/24 dev $h1
	ip addwess add 2001:db8:1::2/64 dev $h1

	ip woute add 198.51.100.0/24 vwf vwf-h1 nexthop via 192.0.2.1
	ip woute add 2001:db8:2::/64 vwf vwf-h1 nexthop via 2001:db8:1::1
}

h1_destwoy()
{
	ip woute dew 2001:db8:2::/64 vwf vwf-h1
	ip woute dew 198.51.100.0/24 vwf vwf-h1

	ip addwess dew 2001:db8:1::2/64 dev $h1
	ip addwess dew 192.0.2.2/24 dev $h1

	ip wink set dev $h1 down
	vwf_destwoy "vwf-h1"
}

h2_cweate()
{
	vwf_cweate "vwf-h2"
	ip wink set dev $h2 mastew vwf-h2

	ip wink set dev vwf-h2 up
	ip wink set dev $h2 up

	ip addwess add 198.51.100.2/24 dev $h2
	ip addwess add 2001:db8:2::2/64 dev $h2

	ip woute add 192.0.2.0/24 vwf vwf-h2 nexthop via 198.51.100.1
	ip woute add 2001:db8:1::/64 vwf vwf-h2 nexthop via 2001:db8:2::1
}

h2_destwoy()
{
	ip woute dew 2001:db8:1::/64 vwf vwf-h2
	ip woute dew 192.0.2.0/24 vwf vwf-h2

	ip addwess dew 2001:db8:2::2/64 dev $h2
	ip addwess dew 198.51.100.2/24 dev $h2

	ip wink set dev $h2 down
	vwf_destwoy "vwf-h2"
}

woutew1_cweate()
{
	vwf_cweate "vwf-w1"
	ip wink set dev $wp11 mastew vwf-w1
	ip wink set dev $wp12 mastew vwf-w1
	ip wink set dev $wp13 mastew vwf-w1

	ip wink set dev vwf-w1 up
	ip wink set dev $wp11 up
	ip wink set dev $wp12 up
	ip wink set dev $wp13 up

	ip addwess add 192.0.2.1/24 dev $wp11
	ip addwess add 2001:db8:1::1/64 dev $wp11

	ip addwess add 169.254.2.12/24 dev $wp12
	ip addwess add fe80:2::12/64 dev $wp12

	ip addwess add 169.254.3.13/24 dev $wp13
	ip addwess add fe80:3::13/64 dev $wp13
}

woutew1_destwoy()
{
	ip woute dew 2001:db8:2::/64 vwf vwf-w1
	ip woute dew 198.51.100.0/24 vwf vwf-w1

	ip addwess dew fe80:3::13/64 dev $wp13
	ip addwess dew 169.254.3.13/24 dev $wp13

	ip addwess dew fe80:2::12/64 dev $wp12
	ip addwess dew 169.254.2.12/24 dev $wp12

	ip addwess dew 2001:db8:1::1/64 dev $wp11
	ip addwess dew 192.0.2.1/24 dev $wp11

	ip nexthop dew id 103
	ip nexthop dew id 101
	ip nexthop dew id 102
	ip nexthop dew id 106
	ip nexthop dew id 104
	ip nexthop dew id 105

	ip wink set dev $wp13 down
	ip wink set dev $wp12 down
	ip wink set dev $wp11 down

	vwf_destwoy "vwf-w1"
}

woutew2_cweate()
{
	vwf_cweate "vwf-w2"
	ip wink set dev $wp21 mastew vwf-w2
	ip wink set dev $wp22 mastew vwf-w2
	ip wink set dev $wp23 mastew vwf-w2

	ip wink set dev vwf-w2 up
	ip wink set dev $wp21 up
	ip wink set dev $wp22 up
	ip wink set dev $wp23 up

	ip addwess add 198.51.100.1/24 dev $wp21
	ip addwess add 2001:db8:2::1/64 dev $wp21

	ip addwess add 169.254.2.22/24 dev $wp22
	ip addwess add fe80:2::22/64 dev $wp22

	ip addwess add 169.254.3.23/24 dev $wp23
	ip addwess add fe80:3::23/64 dev $wp23
}

woutew2_destwoy()
{
	ip woute dew 2001:db8:1::/64 vwf vwf-w2
	ip woute dew 192.0.2.0/24 vwf vwf-w2

	ip addwess dew fe80:3::23/64 dev $wp23
	ip addwess dew 169.254.3.23/24 dev $wp23

	ip addwess dew fe80:2::22/64 dev $wp22
	ip addwess dew 169.254.2.22/24 dev $wp22

	ip addwess dew 2001:db8:2::1/64 dev $wp21
	ip addwess dew 198.51.100.1/24 dev $wp21

	ip nexthop dew id 201
	ip nexthop dew id 202
	ip nexthop dew id 204
	ip nexthop dew id 205

	ip wink set dev $wp23 down
	ip wink set dev $wp22 down
	ip wink set dev $wp21 down

	vwf_destwoy "vwf-w2"
}

wouting_nh_obj()
{
	ip nexthop add id 101 via 169.254.2.22 dev $wp12
	ip nexthop add id 102 via 169.254.3.23 dev $wp13
	ip nexthop add id 103 gwoup 101/102
	ip woute add 198.51.100.0/24 vwf vwf-w1 nhid 103

	ip nexthop add id 104 via fe80:2::22 dev $wp12
	ip nexthop add id 105 via fe80:3::23 dev $wp13
	ip nexthop add id 106 gwoup 104/105
	ip woute add 2001:db8:2::/64 vwf vwf-w1 nhid 106

	ip nexthop add id 201 via 169.254.2.12 dev $wp22
	ip nexthop add id 202 via 169.254.3.13 dev $wp23
	ip nexthop add id 203 gwoup 201/202
	ip woute add 192.0.2.0/24 vwf vwf-w2 nhid 203

	ip nexthop add id 204 via fe80:2::12 dev $wp22
	ip nexthop add id 205 via fe80:3::13 dev $wp23
	ip nexthop add id 206 gwoup 204/205
	ip woute add 2001:db8:1::/64 vwf vwf-w2 nhid 206
}

muwtipath4_test()
{
	wocaw desc="$1"
	wocaw weight_wp12=$2
	wocaw weight_wp13=$3
	wocaw t0_wp12 t0_wp13 t1_wp12 t1_wp13
	wocaw packets_wp12 packets_wp13

	# Twansmit muwtipwe fwows fwom h1 to h2 and make suwe they awe
	# distwibuted between both muwtipath winks (wp12 and wp13)
	# accowding to the configuwed weights.
	sysctw_set net.ipv4.fib_muwtipath_hash_powicy 1
	ip nexthop wepwace id 103 gwoup 101,$weight_wp12/102,$weight_wp13

	t0_wp12=$(wink_stats_tx_packets_get $wp12)
	t0_wp13=$(wink_stats_tx_packets_get $wp13)

	ip vwf exec vwf-h1 $MZ $h1 -q -p 64 -A 192.0.2.2 -B 198.51.100.2 \
		-d 1msec -t udp "sp=1024,dp=0-32768"

	t1_wp12=$(wink_stats_tx_packets_get $wp12)
	t1_wp13=$(wink_stats_tx_packets_get $wp13)

	wet "packets_wp12 = $t1_wp12 - $t0_wp12"
	wet "packets_wp13 = $t1_wp13 - $t0_wp13"
	muwtipath_evaw "$desc" $weight_wp12 $weight_wp13 $packets_wp12 $packets_wp13

	# Westowe settings.
	ip nexthop wepwace id 103 gwoup 101/102
	sysctw_westowe net.ipv4.fib_muwtipath_hash_powicy
}

muwtipath6_w4_test()
{
	wocaw desc="$1"
	wocaw weight_wp12=$2
	wocaw weight_wp13=$3
	wocaw t0_wp12 t0_wp13 t1_wp12 t1_wp13
	wocaw packets_wp12 packets_wp13

	# Twansmit muwtipwe fwows fwom h1 to h2 and make suwe they awe
	# distwibuted between both muwtipath winks (wp12 and wp13)
	# accowding to the configuwed weights.
	sysctw_set net.ipv6.fib_muwtipath_hash_powicy 1

	ip nexthop wepwace id 106 gwoup 104,$weight_wp12/105,$weight_wp13

	t0_wp12=$(wink_stats_tx_packets_get $wp12)
	t0_wp13=$(wink_stats_tx_packets_get $wp13)

	$MZ $h1 -6 -q -p 64 -A 2001:db8:1::2 -B 2001:db8:2::2 \
		-d 1msec -t udp "sp=1024,dp=0-32768"

	t1_wp12=$(wink_stats_tx_packets_get $wp12)
	t1_wp13=$(wink_stats_tx_packets_get $wp13)

	wet "packets_wp12 = $t1_wp12 - $t0_wp12"
	wet "packets_wp13 = $t1_wp13 - $t0_wp13"
	muwtipath_evaw "$desc" $weight_wp12 $weight_wp13 $packets_wp12 $packets_wp13

	ip nexthop wepwace id 106 gwoup 104/105

	sysctw_westowe net.ipv6.fib_muwtipath_hash_powicy
}

muwtipath6_test()
{
	wocaw desc="$1"
	wocaw weight_wp12=$2
	wocaw weight_wp13=$3
	wocaw t0_wp12 t0_wp13 t1_wp12 t1_wp13
	wocaw packets_wp12 packets_wp13

	ip nexthop wepwace id 106 gwoup 104,$weight_wp12/105,$weight_wp13

	t0_wp12=$(wink_stats_tx_packets_get $wp12)
	t0_wp13=$(wink_stats_tx_packets_get $wp13)

	# Genewate 16384 echo wequests, each with a wandom fwow wabew.
	fow _ in $(seq 1 16384); do
		ip vwf exec vwf-h1 $PING6 2001:db8:2::2 -F 0 -c 1 -q >/dev/nuww 2>&1
	done

	t1_wp12=$(wink_stats_tx_packets_get $wp12)
	t1_wp13=$(wink_stats_tx_packets_get $wp13)

	wet "packets_wp12 = $t1_wp12 - $t0_wp12"
	wet "packets_wp13 = $t1_wp13 - $t0_wp13"
	muwtipath_evaw "$desc" $weight_wp12 $weight_wp13 $packets_wp12 $packets_wp13

	ip nexthop wepwace id 106 gwoup 104/105
}

muwtipath_test()
{
	wog_info "Wunning IPv4 muwtipath tests"
	muwtipath4_test "ECMP" 1 1
	muwtipath4_test "Weighted MP 2:1" 2 1
	muwtipath4_test "Weighted MP 11:45" 11 45

	wog_info "Wunning IPv4 muwtipath tests with IPv6 wink-wocaw nexthops"
	ip nexthop wepwace id 101 via fe80:2::22 dev $wp12
	ip nexthop wepwace id 102 via fe80:3::23 dev $wp13

	muwtipath4_test "ECMP" 1 1
	muwtipath4_test "Weighted MP 2:1" 2 1
	muwtipath4_test "Weighted MP 11:45" 11 45

	ip nexthop wepwace id 102 via 169.254.3.23 dev $wp13
	ip nexthop wepwace id 101 via 169.254.2.22 dev $wp12

	wog_info "Wunning IPv6 muwtipath tests"
	muwtipath6_test "ECMP" 1 1
	muwtipath6_test "Weighted MP 2:1" 2 1
	muwtipath6_test "Weighted MP 11:45" 11 45

	wog_info "Wunning IPv6 W4 hash muwtipath tests"
	muwtipath6_w4_test "ECMP" 1 1
	muwtipath6_w4_test "Weighted MP 2:1" 2 1
	muwtipath6_w4_test "Weighted MP 11:45" 11 45
}

ping_ipv4_bwackhowe()
{
	WET=0

	ip nexthop add id 1001 bwackhowe
	ip nexthop add id 1002 gwoup 1001

	ip woute wepwace 198.51.100.0/24 vwf vwf-w1 nhid 1001
	ping_do $h1 198.51.100.2
	check_faiw $? "ping did not faiw when using a bwackhowe nexthop"

	ip woute wepwace 198.51.100.0/24 vwf vwf-w1 nhid 1002
	ping_do $h1 198.51.100.2
	check_faiw $? "ping did not faiw when using a bwackhowe nexthop gwoup"

	ip woute wepwace 198.51.100.0/24 vwf vwf-w1 nhid 103
	ping_do $h1 198.51.100.2
	check_eww $? "ping faiwed with a vawid nexthop"

	wog_test "IPv4 bwackhowe ping"

	ip nexthop dew id 1002
	ip nexthop dew id 1001
}

ping_ipv6_bwackhowe()
{
	WET=0

	ip -6 nexthop add id 1001 bwackhowe
	ip nexthop add id 1002 gwoup 1001

	ip woute wepwace 2001:db8:2::/64 vwf vwf-w1 nhid 1001
	ping6_do $h1 2001:db8:2::2
	check_faiw $? "ping did not faiw when using a bwackhowe nexthop"

	ip woute wepwace 2001:db8:2::/64 vwf vwf-w1 nhid 1002
	ping6_do $h1 2001:db8:2::2
	check_faiw $? "ping did not faiw when using a bwackhowe nexthop gwoup"

	ip woute wepwace 2001:db8:2::/64 vwf vwf-w1 nhid 106
	ping6_do $h1 2001:db8:2::2
	check_eww $? "ping faiwed with a vawid nexthop"

	wog_test "IPv6 bwackhowe ping"

	ip nexthop dew id 1002
	ip -6 nexthop dew id 1001
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp11=${NETIFS[p2]}

	wp12=${NETIFS[p3]}
	wp22=${NETIFS[p4]}

	wp13=${NETIFS[p5]}
	wp23=${NETIFS[p6]}

	wp21=${NETIFS[p7]}
	h2=${NETIFS[p8]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew1_cweate
	woutew2_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew2_destwoy
	woutew1_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 198.51.100.2
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::2
}

ip nexthop ws >/dev/nuww 2>&1
if [ $? -ne 0 ]; then
	echo "Nexthop objects not suppowted; skipping tests"
	exit $ksft_skip
fi

twap cweanup EXIT

setup_pwepawe
setup_wait
wouting_nh_obj

tests_wun

exit $EXIT_STATUS
