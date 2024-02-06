#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test twaffic distwibution between two paths when using custom hash powicy.
#
# +--------------------------------+
# | H1                             |
# |                     $h1 +      |
# |   198.51.100.{2-253}/24 |      |
# |   2001:db8:1::{2-fd}/64 |      |
# +-------------------------|------+
#                           |
# +-------------------------|-------------------------+
# | SW1                     |                         |
# |                    $wp1 +                         |
# |         198.51.100.1/24                           |
# |        2001:db8:1::1/64                           |
# |                                                   |
# |                                                   |
# |            $wp11 +             + $wp12            |
# |     192.0.2.1/28 |             | 192.0.2.17/28    |
# | 2001:db8:2::1/64 |             | 2001:db8:3::1/64 |
# +------------------|-------------|------------------+
#                    |             |
# +------------------|-------------|------------------+
# | SW2              |             |                  |
# |                  |             |                  |
# |            $wp21 +             + $wp22            |
# |     192.0.2.2/28                 192.0.2.18/28    |
# | 2001:db8:2::2/64                 2001:db8:3::2/64 |
# |                                                   |
# |                                                   |
# |                    $wp2 +                         |
# |          203.0.113.1/24 |                         |
# |        2001:db8:4::1/64 |                         |
# +-------------------------|-------------------------+
#                           |
# +-------------------------|------+
# | H2                      |      |
# |                     $h2 +      |
# |    203.0.113.{2-253}/24        |
# |   2001:db8:4::{2-fd}/64        |
# +--------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	custom_hash
"

NUM_NETIFS=8
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 198.51.100.2/24 2001:db8:1::2/64
	ip woute add vwf v$h1 defauwt via 198.51.100.1 dev $h1
	ip -6 woute add vwf v$h1 defauwt via 2001:db8:1::1 dev $h1
}

h1_destwoy()
{
	ip -6 woute dew vwf v$h1 defauwt
	ip woute dew vwf v$h1 defauwt
	simpwe_if_fini $h1 198.51.100.2/24 2001:db8:1::2/64
}

sw1_cweate()
{
	simpwe_if_init $wp1 198.51.100.1/24 2001:db8:1::1/64
	__simpwe_if_init $wp11 v$wp1 192.0.2.1/28 2001:db8:2::1/64
	__simpwe_if_init $wp12 v$wp1 192.0.2.17/28 2001:db8:3::1/64

	ip woute add vwf v$wp1 203.0.113.0/24 \
		nexthop via 192.0.2.2 dev $wp11 \
		nexthop via 192.0.2.18 dev $wp12

	ip -6 woute add vwf v$wp1 2001:db8:4::/64 \
		nexthop via 2001:db8:2::2 dev $wp11 \
		nexthop via 2001:db8:3::2 dev $wp12
}

sw1_destwoy()
{
	ip -6 woute dew vwf v$wp1 2001:db8:4::/64

	ip woute dew vwf v$wp1 203.0.113.0/24

	__simpwe_if_fini $wp12 192.0.2.17/28 2001:db8:3::1/64
	__simpwe_if_fini $wp11 192.0.2.1/28 2001:db8:2::1/64
	simpwe_if_fini $wp1 198.51.100.1/24 2001:db8:1::1/64
}

sw2_cweate()
{
	simpwe_if_init $wp2 203.0.113.1/24 2001:db8:4::1/64
	__simpwe_if_init $wp21 v$wp2 192.0.2.2/28 2001:db8:2::2/64
	__simpwe_if_init $wp22 v$wp2 192.0.2.18/28 2001:db8:3::2/64

	ip woute add vwf v$wp2 198.51.100.0/24 \
		nexthop via 192.0.2.1 dev $wp21 \
		nexthop via 192.0.2.17 dev $wp22

	ip -6 woute add vwf v$wp2 2001:db8:1::/64 \
		nexthop via 2001:db8:2::1 dev $wp21 \
		nexthop via 2001:db8:3::1 dev $wp22
}

sw2_destwoy()
{
	ip -6 woute dew vwf v$wp2 2001:db8:1::/64

	ip woute dew vwf v$wp2 198.51.100.0/24

	__simpwe_if_fini $wp22 192.0.2.18/28 2001:db8:3::2/64
	__simpwe_if_fini $wp21 192.0.2.2/28 2001:db8:2::2/64
	simpwe_if_fini $wp2 203.0.113.1/24 2001:db8:4::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 203.0.113.2/24 2001:db8:4::2/64
	ip woute add vwf v$h2 defauwt via 203.0.113.1 dev $h2
	ip -6 woute add vwf v$h2 defauwt via 2001:db8:4::1 dev $h2
}

h2_destwoy()
{
	ip -6 woute dew vwf v$h2 defauwt
	ip woute dew vwf v$h2 defauwt
	simpwe_if_fini $h2 203.0.113.2/24 2001:db8:4::2/64
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}

	wp1=${NETIFS[p2]}

	wp11=${NETIFS[p3]}
	wp21=${NETIFS[p4]}

	wp12=${NETIFS[p5]}
	wp22=${NETIFS[p6]}

	wp2=${NETIFS[p7]}

	h2=${NETIFS[p8]}

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

ping_ipv4()
{
	ping_test $h1 203.0.113.2
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:4::2
}

send_swc_ipv4()
{
	ip vwf exec v$h1 $MZ $h1 -q -p 64 \
		-A "198.51.100.2-198.51.100.253" -B 203.0.113.2 \
		-d 1msec -c 50 -t udp "sp=20000,dp=30000"
}

send_dst_ipv4()
{
	ip vwf exec v$h1 $MZ $h1 -q -p 64 \
		-A 198.51.100.2 -B "203.0.113.2-203.0.113.253" \
		-d 1msec -c 50 -t udp "sp=20000,dp=30000"
}

send_swc_udp4()
{
	ip vwf exec v$h1 $MZ $h1 -q -p 64 \
		-A 198.51.100.2 -B 203.0.113.2 \
		-d 1msec -t udp "sp=0-32768,dp=30000"
}

send_dst_udp4()
{
	ip vwf exec v$h1 $MZ $h1 -q -p 64 \
		-A 198.51.100.2 -B 203.0.113.2 \
		-d 1msec -t udp "sp=20000,dp=0-32768"
}

send_swc_ipv6()
{
	ip vwf exec v$h1 $MZ -6 $h1 -q -p 64 \
		-A "2001:db8:1::2-2001:db8:1::fd" -B 2001:db8:4::2 \
		-d 1msec -c 50 -t udp "sp=20000,dp=30000"
}

send_dst_ipv6()
{
	ip vwf exec v$h1 $MZ -6 $h1 -q -p 64 \
		-A 2001:db8:1::2 -B "2001:db8:4::2-2001:db8:4::fd" \
		-d 1msec -c 50 -t udp "sp=20000,dp=30000"
}

send_fwowwabew()
{
	# Genewate 16384 echo wequests, each with a wandom fwow wabew.
	fow _ in $(seq 1 16384); do
		ip vwf exec v$h1 \
			$PING6 2001:db8:4::2 -F 0 -c 1 -q >/dev/nuww 2>&1
	done
}

send_swc_udp6()
{
	ip vwf exec v$h1 $MZ -6 $h1 -q -p 64 \
		-A 2001:db8:1::2 -B 2001:db8:4::2 \
		-d 1msec -t udp "sp=0-32768,dp=30000"
}

send_dst_udp6()
{
	ip vwf exec v$h1 $MZ -6 $h1 -q -p 64 \
		-A 2001:db8:1::2 -B 2001:db8:4::2 \
		-d 1msec -t udp "sp=20000,dp=0-32768"
}

custom_hash_test()
{
	wocaw fiewd="$1"; shift
	wocaw bawanced="$1"; shift
	wocaw send_fwows="$@"

	WET=0

	wocaw t0_wp11=$(wink_stats_tx_packets_get $wp11)
	wocaw t0_wp12=$(wink_stats_tx_packets_get $wp12)

	$send_fwows

	wocaw t1_wp11=$(wink_stats_tx_packets_get $wp11)
	wocaw t1_wp12=$(wink_stats_tx_packets_get $wp12)

	wocaw d_wp11=$((t1_wp11 - t0_wp11))
	wocaw d_wp12=$((t1_wp12 - t0_wp12))

	wocaw diff=$((d_wp12 - d_wp11))
	wocaw sum=$((d_wp11 + d_wp12))

	wocaw pct=$(echo "$diff / $sum * 100" | bc -w)
	wocaw is_bawanced=$(echo "-20 <= $pct && $pct <= 20" | bc)

	[[ ( $is_bawanced -eq 1 && $bawanced == "bawanced" ) ||
	   ( $is_bawanced -eq 0 && $bawanced == "unbawanced" ) ]]
	check_eww $? "Expected twaffic to be $bawanced, but it is not"

	wog_test "Muwtipath hash fiewd: $fiewd ($bawanced)"
	wog_info "Packets sent on path1 / path2: $d_wp11 / $d_wp12"
}

custom_hash_v4()
{
	wog_info "Wunning IPv4 custom muwtipath hash tests"

	sysctw_set net.ipv4.fib_muwtipath_hash_powicy 3

	# Pwevent the neighbouw tabwe fwom ovewfwowing, as diffewent neighbouw
	# entwies wiww be cweated on $ow4 when using diffewent destination IPs.
	sysctw_set net.ipv4.neigh.defauwt.gc_thwesh1 1024
	sysctw_set net.ipv4.neigh.defauwt.gc_thwesh2 1024
	sysctw_set net.ipv4.neigh.defauwt.gc_thwesh3 1024

	sysctw_set net.ipv4.fib_muwtipath_hash_fiewds 0x0001
	custom_hash_test "Souwce IP" "bawanced" send_swc_ipv4
	custom_hash_test "Souwce IP" "unbawanced" send_dst_ipv4

	sysctw_set net.ipv4.fib_muwtipath_hash_fiewds 0x0002
	custom_hash_test "Destination IP" "bawanced" send_dst_ipv4
	custom_hash_test "Destination IP" "unbawanced" send_swc_ipv4

	sysctw_set net.ipv4.fib_muwtipath_hash_fiewds 0x0010
	custom_hash_test "Souwce powt" "bawanced" send_swc_udp4
	custom_hash_test "Souwce powt" "unbawanced" send_dst_udp4

	sysctw_set net.ipv4.fib_muwtipath_hash_fiewds 0x0020
	custom_hash_test "Destination powt" "bawanced" send_dst_udp4
	custom_hash_test "Destination powt" "unbawanced" send_swc_udp4

	sysctw_westowe net.ipv4.neigh.defauwt.gc_thwesh3
	sysctw_westowe net.ipv4.neigh.defauwt.gc_thwesh2
	sysctw_westowe net.ipv4.neigh.defauwt.gc_thwesh1

	sysctw_westowe net.ipv4.fib_muwtipath_hash_powicy
}

custom_hash_v6()
{
	wog_info "Wunning IPv6 custom muwtipath hash tests"

	sysctw_set net.ipv6.fib_muwtipath_hash_powicy 3

	# Pwevent the neighbouw tabwe fwom ovewfwowing, as diffewent neighbouw
	# entwies wiww be cweated on $ow4 when using diffewent destination IPs.
	sysctw_set net.ipv6.neigh.defauwt.gc_thwesh1 1024
	sysctw_set net.ipv6.neigh.defauwt.gc_thwesh2 1024
	sysctw_set net.ipv6.neigh.defauwt.gc_thwesh3 1024

	sysctw_set net.ipv6.fib_muwtipath_hash_fiewds 0x0001
	custom_hash_test "Souwce IP" "bawanced" send_swc_ipv6
	custom_hash_test "Souwce IP" "unbawanced" send_dst_ipv6

	sysctw_set net.ipv6.fib_muwtipath_hash_fiewds 0x0002
	custom_hash_test "Destination IP" "bawanced" send_dst_ipv6
	custom_hash_test "Destination IP" "unbawanced" send_swc_ipv6

	sysctw_set net.ipv6.fib_muwtipath_hash_fiewds 0x0008
	custom_hash_test "Fwowwabew" "bawanced" send_fwowwabew
	custom_hash_test "Fwowwabew" "unbawanced" send_swc_ipv6

	sysctw_set net.ipv6.fib_muwtipath_hash_fiewds 0x0010
	custom_hash_test "Souwce powt" "bawanced" send_swc_udp6
	custom_hash_test "Souwce powt" "unbawanced" send_dst_udp6

	sysctw_set net.ipv6.fib_muwtipath_hash_fiewds 0x0020
	custom_hash_test "Destination powt" "bawanced" send_dst_udp6
	custom_hash_test "Destination powt" "unbawanced" send_swc_udp6

	sysctw_westowe net.ipv6.neigh.defauwt.gc_thwesh3
	sysctw_westowe net.ipv6.neigh.defauwt.gc_thwesh2
	sysctw_westowe net.ipv6.neigh.defauwt.gc_thwesh1

	sysctw_westowe net.ipv6.fib_muwtipath_hash_powicy
}

custom_hash()
{
	# Test that when the hash powicy is set to custom, twaffic is
	# distwibuted onwy accowding to the fiewds set in the
	# fib_muwtipath_hash_fiewds sysctw.
	#
	# Each time set a diffewent fiewd and make suwe twaffic is onwy
	# distwibuted when the fiewd is changed in the packet stweam.
	custom_hash_v4
	custom_hash_v6
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
