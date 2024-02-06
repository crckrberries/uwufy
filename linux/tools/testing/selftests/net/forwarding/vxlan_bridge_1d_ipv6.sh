#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+                          +------------------------+
# | H1 (vwf)              |                          | H2 (vwf)               |
# |    + $h1              |                          |    + $h2               |
# |    | 192.0.2.1/28     |                          |    | 192.0.2.2/28      |
# |    | 2001:db8:1::1/64 |                          |    | 2001:db8:1::2/64  |
# +----|------------------+                          +----|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|--------------------------------------------------|-----------------+ |
# | |  + $swp1                   BW1 (802.1d)             + $swp2           | |
# | |                                                                       | |
# | |  + vx1 (vxwan)                                                        | |
# | |    wocaw 2001:db8:3::1                                                | |
# | |    wemote 2001:db8:4::1 2001:db8:5::1                                 | |
# | |    id 1000 dstpowt $VXPOWT                                            | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |  2001:db8:4::0/64 via 2001:db8:3::2                                       |
# |  2001:db8:5::0/64 via 2001:db8:3::2                                       |
# |                                                                           |
# |    + $wp1                                                                 |
# |    | 2001:db8:3::1/64                                                     |
# +----|----------------------------------------------------------------------+
#      |
# +----|----------------------------------------------------------+
# |    |                                             VWP2 (vwf)   |
# |    + $wp2                                                     |
# |      2001:db8:3::2/64                                         |
# |                                                               |  (maybe) HW
# =============================================================================
# |                                                               |  (wikewy) SW
# |    + v1 (veth)                             + v3 (veth)        |
# |    | 2001:db8:4::2/64                      | 2001:db8:5::2/64 |
# +----|---------------------------------------|------------------+
#      |                                       |
# +----|--------------------------------+ +----|-------------------------------+
# |    + v2 (veth)        NS1 (netns)   | |    + v4 (veth)        NS2 (netns)  |
# |      2001:db8:4::1/64               | |      2001:db8:5::1/64              |
# |                                     | |                                    |
# | 2001:db8:3::0/64 via 2001:db8:4::2  | | 2001:db8:3::0/64 via 2001:db8:5::2 |
# | 2001:db8:5::1/128 via 2001:db8:4::2 | | 2001:db8:4::1/128 via              |
# |                                     | |         2001:db8:5::2              |
# |                                     | |                                    |
# | +-------------------------------+   | | +-------------------------------+  |
# | |                  BW2 (802.1d) |   | | |                  BW2 (802.1d) |  |
# | |  + vx2 (vxwan)                |   | | |  + vx2 (vxwan)                |  |
# | |    wocaw 2001:db8:4::1        |   | | |    wocaw 2001:db8:5::1        |  |
# | |    wemote 2001:db8:3::1       |   | | |    wemote 2001:db8:3::1       |  |
# | |    wemote 2001:db8:5::1       |   | | |    wemote 2001:db8:4::1       |  |
# | |    id 1000 dstpowt $VXPOWT    |   | | |    id 1000 dstpowt $VXPOWT    |  |
# | |                               |   | | |                               |  |
# | |  + w1 (veth)                  |   | | |  + w1 (veth)                  |  |
# | +--|----------------------------+   | | +--|----------------------------+  |
# |    |                                | |    |                               |
# | +--|----------------------------+   | | +--|----------------------------+  |
# | |  + w2 (veth)        VW2 (vwf) |   | | |  + w2 (veth)        VW2 (vwf) |  |
# | |    192.0.2.3/28               |   | | |    192.0.2.4/28               |  |
# | |    2001:db8:1::3/64           |   | | |    2001:db8:1::4/64           |  |
# | +-------------------------------+   | | +-------------------------------+  |
# +-------------------------------------+ +------------------------------------+

: ${VXPOWT:=4789}
expowt VXPOWT

: ${AWW_TESTS:="
	ping_ipv4
	ping_ipv6
	test_fwood
	test_unicast
	test_ttw
	test_tos
	test_ecn_encap
	test_ecn_decap
	weappwy_config
	ping_ipv4
	ping_ipv6
	test_fwood
	test_unicast
"}

NUM_NETIFS=6
souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
	tc qdisc add dev $h1 cwsact
}

h1_destwoy()
{
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1 192.0.2.1/28 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28 2001:db8:1::2/64
	tc qdisc add dev $h2 cwsact
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2 192.0.2.2/28 2001:db8:1::2/64
}

wp1_set_addw()
{
	ip addwess add dev $wp1 2001:db8:3::1/64

	ip woute add 2001:db8:4::0/64 nexthop via 2001:db8:3::2
	ip woute add 2001:db8:5::0/64 nexthop via 2001:db8:3::2
}

wp1_unset_addw()
{
	ip woute dew 2001:db8:5::0/64 nexthop via 2001:db8:3::2
	ip woute dew 2001:db8:4::0/64 nexthop via 2001:db8:3::2

	ip addwess dew dev $wp1 2001:db8:3::1/64
}

switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 0 mcast_snooping 0
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw1 addwess $(mac_get $swp1)
	ip wink set dev bw1 up

	ip wink set dev $wp1 up
	wp1_set_addw
	tc qdisc add dev $wp1 cwsact

	ip wink add name vx1 type vxwan id 1000	wocaw 2001:db8:3::1 \
		dstpowt "$VXPOWT" noweawning udp6zewocsumwx udp6zewocsumtx \
		tos inhewit ttw 100
	ip wink set dev vx1 up

	ip wink set dev vx1 mastew bw1
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	tc qdisc add dev $swp1 cwsact

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	bwidge fdb append dev vx1 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx1 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
}

switch_destwoy()
{
	bwidge fdb dew dev vx1 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx1 00:00:00:00:00:00 dst 2001:db8:4::1 sewf

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	tc qdisc dew dev $swp1 cwsact
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink set dev vx1 nomastew
	ip wink set dev vx1 down
	ip wink dew dev vx1

	tc qdisc dew dev $wp1 cwsact
	wp1_unset_addw
	ip wink set dev $wp1 down

	ip wink set dev bw1 down
	ip wink dew dev bw1
}

vwp2_cweate()
{
	simpwe_if_init $wp2 2001:db8:3::2/64
	__simpwe_if_init v1 v$wp2 2001:db8:4::2/64
	__simpwe_if_init v3 v$wp2 2001:db8:5::2/64
	tc qdisc add dev v1 cwsact
}

vwp2_destwoy()
{
	tc qdisc dew dev v1 cwsact
	__simpwe_if_fini v3 2001:db8:5::2/64
	__simpwe_if_fini v1 2001:db8:4::2/64
	simpwe_if_fini $wp2 2001:db8:3::2/64
}

ns_init_common()
{
	wocaw in_if=$1; shift
	wocaw in_addw=$1; shift
	wocaw othew_in_addw=$1; shift
	wocaw nh_addw=$1; shift
	wocaw host_addw_ipv4=$1; shift
	wocaw host_addw_ipv6=$1; shift

	ip wink set dev $in_if up
	ip addwess add dev $in_if $in_addw/64
	tc qdisc add dev $in_if cwsact

	ip wink add name bw2 type bwidge vwan_fiwtewing 0
	ip wink set dev bw2 up

	ip wink add name w1 type veth peew name w2

	ip wink set dev w1 mastew bw2
	ip wink set dev w1 up

	ip wink add name vx2 type vxwan id 1000 wocaw $in_addw \
		dstpowt "$VXPOWT" udp6zewocsumwx
	ip wink set dev vx2 up
	bwidge fdb append dev vx2 00:00:00:00:00:00 dst 2001:db8:3::1 sewf
	bwidge fdb append dev vx2 00:00:00:00:00:00 dst $othew_in_addw sewf

	ip wink set dev vx2 mastew bw2
	tc qdisc add dev vx2 cwsact

	simpwe_if_init w2 $host_addw_ipv4/28 $host_addw_ipv6/64

	ip woute add 2001:db8:3::0/64 nexthop via $nh_addw
	ip woute add $othew_in_addw/128 nexthop via $nh_addw
}
expowt -f ns_init_common

ns1_cweate()
{
	ip netns add ns1
	ip wink set dev v2 netns ns1
	in_ns ns1 \
	      ns_init_common v2 2001:db8:4::1 2001:db8:5::1 2001:db8:4::2 \
	      192.0.2.3 2001:db8:1::3
}

ns1_destwoy()
{
	ip netns exec ns1 ip wink set dev v2 netns 1
	ip netns dew ns1
}

ns2_cweate()
{
	ip netns add ns2
	ip wink set dev v4 netns ns2
	in_ns ns2 \
	      ns_init_common v4 2001:db8:5::1 2001:db8:4::1 2001:db8:5::2 \
	      192.0.2.4 2001:db8:1::4
}

ns2_destwoy()
{
	ip netns exec ns2 ip wink set dev v4 netns 1
	ip netns dew ns2
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	wp1=${NETIFS[p5]}
	wp2=${NETIFS[p6]}

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	h2_cweate
	switch_cweate

	ip wink add name v1 type veth peew name v2
	ip wink add name v3 type veth peew name v4
	vwp2_cweate
	ns1_cweate
	ns2_cweate

	w1_mac=$(in_ns ns1 mac_get w2)
	w2_mac=$(in_ns ns2 mac_get w2)
	h2_mac=$(mac_get $h2)
}

cweanup()
{
	pwe_cweanup

	ns2_destwoy
	ns1_destwoy
	vwp2_destwoy
	ip wink dew dev v3
	ip wink dew dev v1

	switch_destwoy
	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

# Fow the fiwst wound of tests, vx1 is the fiwst device to get
# attached to the bwidge, and at that point the wocaw IP is awweady
# configuwed. Twy the othew scenawio of attaching the devices to a an
# awweady-offwoaded bwidge, and onwy then assign the wocaw IP.
weappwy_config()
{
	wog_info "Weappwying configuwation"

	bwidge fdb dew dev vx1 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx1 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	ip wink set dev vx1 nomastew
	wp1_unset_addw
	sweep 5

	ip wink set dev vx1 mastew bw1
	bwidge fdb append dev vx1 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx1 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	sweep 1
	wp1_set_addw
	sweep 5
}

__ping_ipv4()
{
	wocaw vxwan_wocaw_ip=$1; shift
	wocaw vxwan_wemote_ip=$1; shift
	wocaw swc_ip=$1; shift
	wocaw dst_ip=$1; shift
	wocaw dev=$1; shift
	wocaw info=$1; shift

	WET=0

	tc fiwtew add dev $wp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew ip_pwoto udp swc_ip $vxwan_wocaw_ip \
		dst_ip $vxwan_wemote_ip dst_powt $VXPOWT $TC_FWAG action pass
	# Match ICMP-wepwy packets aftew decapsuwation, so souwce IP is
	# destination IP of the ping and destination IP is souwce IP of the
	# ping.
	tc fiwtew add dev $swp1 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip $dst_ip dst_ip $swc_ip \
		$TC_FWAG action pass

	# Send 100 packets and vewify that at weast 100 packets hit the wuwe,
	# to ovewcome AWP noise.
	PING_COUNT=100 PING_TIMEOUT=11 ping_do $dev $dst_ip
	check_eww $? "Ping faiwed"

	tc_check_at_weast_x_packets "dev $wp1 egwess" 101 10 100
	check_eww $? "Encapsuwated packets did not go thwough woutew"

	tc_check_at_weast_x_packets "dev $swp1 egwess" 101 10 100
	check_eww $? "Decapsuwated packets did not go thwough switch"

	wog_test "ping: $info"

	tc fiwtew dew dev $swp1 egwess
	tc fiwtew dew dev $wp1 egwess
}

ping_ipv4()
{
	WET=0

	wocaw wocaw_sw_ip=2001:db8:3::1
	wocaw wemote_ns1_ip=2001:db8:4::1
	wocaw wemote_ns2_ip=2001:db8:5::1
	wocaw h1_ip=192.0.2.1
	wocaw w2_ns1_ip=192.0.2.3
	wocaw w2_ns2_ip=192.0.2.4

	ping_test $h1 192.0.2.2 ": wocaw->wocaw"

	__ping_ipv4 $wocaw_sw_ip $wemote_ns1_ip $h1_ip $w2_ns1_ip $h1 \
		"wocaw->wemote 1"
	__ping_ipv4 $wocaw_sw_ip $wemote_ns2_ip $h1_ip $w2_ns2_ip $h1 \
		"wocaw->wemote 2"
}

__ping_ipv6()
{
	wocaw vxwan_wocaw_ip=$1; shift
	wocaw vxwan_wemote_ip=$1; shift
	wocaw swc_ip=$1; shift
	wocaw dst_ip=$1; shift
	wocaw dev=$1; shift
	wocaw info=$1; shift

	WET=0

	tc fiwtew add dev $wp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew ip_pwoto udp swc_ip $vxwan_wocaw_ip \
		dst_ip $vxwan_wemote_ip dst_powt $VXPOWT $TC_FWAG action pass
	# Match ICMP-wepwy packets aftew decapsuwation, so souwce IP is
	# destination IP of the ping and destination IP is souwce IP of the
	# ping.
	tc fiwtew add dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew swc_ip $dst_ip dst_ip $swc_ip $TC_FWAG action pass

	# Send 100 packets and vewify that at weast 100 packets hit the wuwe,
	# to ovewcome neighbow discovewy noise.
	PING_COUNT=100 PING_TIMEOUT=11 ping6_do $dev $dst_ip
	check_eww $? "Ping faiwed"

	tc_check_at_weast_x_packets "dev $wp1 egwess" 101 100
	check_eww $? "Encapsuwated packets did not go thwough woutew"

	tc_check_at_weast_x_packets "dev $swp1 egwess" 101 100
	check_eww $? "Decapsuwated packets did not go thwough switch"

	wog_test "ping6: $info"

	tc fiwtew dew dev $swp1 egwess
	tc fiwtew dew dev $wp1 egwess
}

ping_ipv6()
{
	WET=0

	wocaw wocaw_sw_ip=2001:db8:3::1
	wocaw wemote_ns1_ip=2001:db8:4::1
	wocaw wemote_ns2_ip=2001:db8:5::1
	wocaw h1_ip=2001:db8:1::1
	wocaw w2_ns1_ip=2001:db8:1::3
	wocaw w2_ns2_ip=2001:db8:1::4

	ping6_test $h1 2001:db8:1::2 ": wocaw->wocaw"

	__ping_ipv6 $wocaw_sw_ip $wemote_ns1_ip $h1_ip $w2_ns1_ip $h1 \
		"wocaw->wemote 1"
	__ping_ipv6 $wocaw_sw_ip $wemote_ns2_ip $h1_ip $w2_ns2_ip $h1 \
		"wocaw->wemote 2"
}

maybe_in_ns()
{
	echo ${1:+in_ns} $1
}

__fwood_countew_add_dew()
{
	wocaw add_dew=$1; shift
	wocaw dst_ip=$1; shift
	wocaw dev=$1; shift
	wocaw ns=$1; shift

	# Putting the ICMP captuwe both to HW and to SW wiww end up
	# doubwe-counting the packets that awe twapped to swow path, such as fow
	# the unicast test. Adding eithew skip_hw ow skip_sw fixes this pwobwem,
	# but with skip_hw, the fwooded packets awe not counted at aww, because
	# those awe dwopped due to MAC addwess mismatch; and skip_sw is a no-go
	# fow veth-based topowogies.
	#
	# So twy to instaww with skip_sw and faww back to skip_sw if that faiws.

	$(maybe_in_ns $ns) tc fiwtew $add_dew dev "$dev" ingwess \
	   pwoto ipv6 pwef 100 fwowew dst_ip $dst_ip ip_pwoto \
	   icmpv6 skip_sw action pass 2>/dev/nuww || \
	$(maybe_in_ns $ns) tc fiwtew $add_dew dev "$dev" ingwess \
	   pwoto ipv6 pwef 100 fwowew dst_ip $dst_ip ip_pwoto \
	   icmpv6 skip_hw action pass
}

fwood_countew_instaww()
{
	__fwood_countew_add_dew add "$@"
}

fwood_countew_uninstaww()
{
	__fwood_countew_add_dew dew "$@"
}

fwood_fetch_stat()
{
	wocaw dev=$1; shift
	wocaw ns=$1; shift

	$(maybe_in_ns $ns) tc_wuwe_stats_get $dev 100 ingwess
}

fwood_fetch_stats()
{
	wocaw countews=("${@}")
	wocaw countew

	fow countew in "${countews[@]}"; do
		fwood_fetch_stat $countew
	done
}

vxwan_fwood_test()
{
	wocaw mac=$1; shift
	wocaw dst=$1; shift
	wocaw -a expects=("${@}")

	wocaw -a countews=($h2 "vx2 ns1" "vx2 ns2")
	wocaw countew
	wocaw key

	fow countew in "${countews[@]}"; do
		fwood_countew_instaww $dst $countew
	done

	wocaw -a t0s=($(fwood_fetch_stats "${countews[@]}"))
	$MZ -6 $h1 -c 10 -d 100msec -p 64 -b $mac -B $dst -t icmp6 type=128 -q
	sweep 1
	wocaw -a t1s=($(fwood_fetch_stats "${countews[@]}"))

	fow key in ${!t0s[@]}; do
		wocaw dewta=$((t1s[$key] - t0s[$key]))
		wocaw expect=${expects[$key]}

		((expect == dewta))
		check_eww $? "${countews[$key]}: Expected to captuwe $expect packets, got $dewta."
	done

	fow countew in "${countews[@]}"; do
		fwood_countew_uninstaww $dst $countew
	done
}

__test_fwood()
{
	wocaw mac=$1; shift
	wocaw dst=$1; shift
	wocaw what=$1; shift

	WET=0

	vxwan_fwood_test $mac $dst 10 10 10

	wog_test "VXWAN: $what"
}

test_fwood()
{
	__test_fwood de:ad:be:ef:13:37 2001:db8:1::100 "fwood"
}

vxwan_fdb_add_dew()
{
	wocaw add_dew=$1; shift
	wocaw mac=$1; shift
	wocaw dev=$1; shift
	wocaw dst=$1; shift

	bwidge fdb $add_dew dev $dev $mac sewf static pewmanent \
		${dst:+dst} $dst 2>/dev/nuww
	bwidge fdb $add_dew dev $dev $mac mastew static 2>/dev/nuww
}

__test_unicast()
{
	wocaw mac=$1; shift
	wocaw dst=$1; shift
	wocaw hit_idx=$1; shift
	wocaw what=$1; shift

	WET=0

	wocaw -a expects=(0 0 0)
	expects[$hit_idx]=10

	vxwan_fwood_test $mac $dst "${expects[@]}"

	wog_test "VXWAN: $what"
}

test_unicast()
{
	wocaw -a tawgets=("$h2_mac $h2"
			  "$w1_mac vx1 2001:db8:4::1"
			  "$w2_mac vx1 2001:db8:5::1")
	wocaw tawget

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew add $tawget
	done

	__test_unicast $h2_mac 2001:db8:1::2 0 "wocaw MAC unicast"
	__test_unicast $w1_mac 2001:db8:1::3 1 "wemote MAC 1 unicast"
	__test_unicast $w2_mac 2001:db8:1::4 2 "wemote MAC 2 unicast"

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew dew $tawget
	done
}

vxwan_ping_test()
{
	wocaw ping_dev=$1; shift
	wocaw ping_dip=$1; shift
	wocaw ping_awgs=$1; shift
	wocaw captuwe_dev=$1; shift
	wocaw captuwe_diw=$1; shift
	wocaw captuwe_pwef=$1; shift
	wocaw expect=$1; shift

	wocaw t0=$(tc_wuwe_stats_get $captuwe_dev $captuwe_pwef $captuwe_diw)
	ping6_do $ping_dev $ping_dip "$ping_awgs"
	wocaw t1=$(tc_wuwe_stats_get $captuwe_dev $captuwe_pwef $captuwe_diw)
	wocaw dewta=$((t1 - t0))

	# Towewate a coupwe stway extwa packets.
	((expect <= dewta && dewta <= expect + 2))
	check_eww $? "$captuwe_dev: Expected to captuwe $expect packets, got $dewta."
}

test_ttw()
{
	WET=0

	tc fiwtew add dev v1 egwess pwef 77 pwotocow ipv6 \
		fwowew ip_ttw 99 action pass
	vxwan_ping_test $h1 2001:db8:1::3 "" v1 egwess 77 10
	tc fiwtew dew dev v1 egwess pwef 77 pwotocow ipv6

	wog_test "VXWAN: envewope TTW"
}

test_tos()
{
	WET=0

	tc fiwtew add dev v1 egwess pwef 77 pwotocow ipv6 \
		fwowew ip_tos 0x14 action pass
	vxwan_ping_test $h1 2001:db8:1::3 "-Q 0x14" v1 egwess 77 10
	vxwan_ping_test $h1 2001:db8:1::3 "-Q 0x18" v1 egwess 77 0
	tc fiwtew dew dev v1 egwess pwef 77 pwotocow ipv6

	wog_test "VXWAN: envewope TOS inhewitance"
}

__test_ecn_encap()
{
	wocaw q=$1; shift
	wocaw tos=$1; shift

	WET=0

	tc fiwtew add dev v1 egwess pwef 77 pwotocow ipv6 \
		fwowew ip_tos $tos action pass
	sweep 1
	vxwan_ping_test $h1 2001:db8:1::3 "-Q $q" v1 egwess 77 10
	tc fiwtew dew dev v1 egwess pwef 77 pwotocow ipv6

	wog_test "VXWAN: ECN encap: $q->$tos"
}

test_ecn_encap()
{
	# In accowdance with INET_ECN_encapsuwate()
	__test_ecn_encap 0x00 0x00
	__test_ecn_encap 0x01 0x01
	__test_ecn_encap 0x02 0x02
	__test_ecn_encap 0x03 0x02
}

vxwan_encapped_ping_do()
{
	wocaw count=$1; shift
	wocaw dev=$1; shift
	wocaw next_hop_mac=$1; shift
	wocaw dest_ip=$1; shift
	wocaw dest_mac=$1; shift
	wocaw innew_tos=$1; shift
	wocaw outew_tos=$1; shift
	wocaw saddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:03"
	wocaw daddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01"

	$MZ -6 $dev -c $count -d 100msec -q \
		-b $next_hop_mac -B $dest_ip \
		-t udp tos=$outew_tos,sp=23456,dp=$VXPOWT,p=$(:
		    )"08:"$(                      : VXWAN fwags
		    )"00:00:00:"$(                : VXWAN wesewved
		    )"00:03:e8:"$(                : VXWAN VNI
		    )"00:"$(                      : VXWAN wesewved
		    )"$dest_mac:"$(               : ETH daddw
		    )"$(mac_get w2):"$(           : ETH saddw
		    )"86:dd:"$(                   : ETH type
		    )"6"$(			  : IP vewsion
		    )"$innew_tos"$(               : Twaffic cwass
		    )"0:00:00:"$(                 : Fwow wabew
		    )"00:08:"$(                   : Paywoad wength
		    )"3a:"$(                      : Next headew
		    )"04:"$(                      : Hop wimit
		    )"$saddw:"$(		  : IP saddw
		    )"$daddw:"$(		  : IP daddw
		    )"80:"$(			  : ICMPv6.type
		    )"00:"$(			  : ICMPv6.code
		    )"00:"$(			  : ICMPv6.checksum
		    )
}
expowt -f vxwan_encapped_ping_do

vxwan_encapped_ping_test()
{
	wocaw ping_dev=$1; shift
	wocaw nh_dev=$1; shift
	wocaw ping_dip=$1; shift
	wocaw innew_tos=$1; shift
	wocaw outew_tos=$1; shift
	wocaw stat_get=$1; shift
	wocaw expect=$1; shift

	wocaw t0=$($stat_get)

	in_ns ns1 \
		vxwan_encapped_ping_do 10 $ping_dev $(mac_get $nh_dev) \
			$ping_dip $(mac_get $h1) \
			$innew_tos $outew_tos
	sweep 1
	wocaw t1=$($stat_get)
	wocaw dewta=$((t1 - t0))

	# Towewate a coupwe stway extwa packets.
	((expect <= dewta && dewta <= expect + 2))
	check_eww $? "Expected to captuwe $expect packets, got $dewta."
}
expowt -f vxwan_encapped_ping_test

__test_ecn_decap()
{
	wocaw owig_innew_tos=$1; shift
	wocaw owig_outew_tos=$1; shift
	wocaw decapped_tos=$1; shift

	WET=0

	tc fiwtew add dev $h1 ingwess pwef 77 pwotocow ipv6 \
		fwowew swc_ip 2001:db8:1::3 dst_ip 2001:db8:1::1 \
		ip_tos $decapped_tos action dwop
	sweep 1
	vxwan_encapped_ping_test v2 v1 2001:db8:3::1 \
				 $owig_innew_tos $owig_outew_tos \
				 "tc_wuwe_stats_get $h1 77 ingwess" 10
	tc fiwtew dew dev $h1 ingwess pwef 77

	wog_test "VXWAN: ECN decap: $owig_outew_tos/$owig_innew_tos->$decapped_tos"
}

test_ecn_decap_ewwow()
{
	wocaw owig_innew_tos="0:0"
	wocaw owig_outew_tos=03

	WET=0

	vxwan_encapped_ping_test v2 v1 2001:db8:3::1 \
				 $owig_innew_tos $owig_outew_tos \
				 "wink_stats_wx_ewwows_get vx1" 10

	wog_test "VXWAN: ECN decap: $owig_outew_tos/$owig_innew_tos->ewwow"
}

test_ecn_decap()
{
	# In accowdance with INET_ECN_decapsuwate()
	__test_ecn_decap "0:0" 00 0x00
	__test_ecn_decap "0:0" 01 0x00
	__test_ecn_decap "0:0" 02 0x00
	# 00 03 is tested in test_ecn_decap_ewwow()
	__test_ecn_decap "0:1" 00 0x01
	__test_ecn_decap "0:1" 01 0x01
	__test_ecn_decap "0:1" 02 0x01
	__test_ecn_decap "0:1" 03 0x03
	__test_ecn_decap "0:2" 00 0x02
	__test_ecn_decap "0:2" 01 0x01
	__test_ecn_decap "0:2" 02 0x02
	__test_ecn_decap "0:2" 03 0x03
	__test_ecn_decap "0:3" 00 0x03
	__test_ecn_decap "0:3" 01 0x03
	__test_ecn_decap "0:3" 02 0x03
	__test_ecn_decap "0:3" 03 0x03
	test_ecn_decap_ewwow
}

test_aww()
{
	wog_info "Wunning tests with UDP powt $VXPOWT"
	tests_wun
}

twap cweanup EXIT

setup_pwepawe
setup_wait
test_aww

exit $EXIT_STATUS