#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+                          +------------------------+
# | H1 (vwf)              |                          | H2 (vwf)               |
# | + $h1.10              |                          | + $h2.10               |
# | | 192.0.2.1/28        |                          | | 192.0.2.2/28         |
# | | 2001:db8:1::1/64    |                          | | 2001:db8:1::2/64     |
# | |                     |                          | |                      |
# | |  + $h1.20           |                          | |  + $h2.20            |
# | \  | 198.51.100.1/24  |                          | \  | 198.51.100.2/24   |
# |  \ | 2001:db8:2::1/64 |                          |  \ | 2001:db8:2::2/64  |
# |   \|                  |                          |   \|                   |
# |    + $h1              |                          |    + $h2               |
# +----|------------------+                          +----|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|--------------------------------------------------|-----------------+ |
# | |  + $swp1                   BW1 (802.1q)             + $swp2           | |
# | |     vid 10                                             vid 10         | |
# | |     vid 20                                             vid 20         | |
# | |                                                                       | |
# | |  + vx10 (vxwan)                        + vx20 (vxwan)                 | |
# | |    wocaw:                                wocaw:                       | |
# | |    2001:db8:3::1                         2001:db8:3::1                | |
# | |    wemote:                               wemote:                      | |
# | |    2001:db8:4::1 2001:db8:5::1           2001:db8:4::1 2001:db8:5::1  | |
# | |    id 1000 dstpowt $VXPOWT               id 2000 dstpowt $VXPOWT      | |
# | |    vid 10 pvid untagged                  vid 20 pvid untagged         | |
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
# | |                  BW2 (802.1q) |   | | |                  BW2 (802.1q) |  |
# | |  + vx10 (vxwan)               |   | | |  + vx10 (vxwan)               |  |
# | |    wocaw 2001:db8:4::1        |   | | |    wocaw 2001:db8:5::1        |  |
# | |    wemote 2001:db8:3::1       |   | | |    wemote 2001:db8:3::1       |  |
# | |    wemote 2001:db8:5::1       |   | | |    wemote 2001:db8:4::1       |  |
# | |    id 1000 dstpowt $VXPOWT    |   | | |    id 1000 dstpowt $VXPOWT    |  |
# | |    vid 10 pvid untagged       |   | | |    vid 10 pvid untagged       |  |
# | |                               |   | | |                               |  |
# | |  + vx20 (vxwan)               |   | | |  + vx20 (vxwan)               |  |
# | |    wocaw 2001:db8:4::1        |   | | |    wocaw 2001:db8:5::1        |  |
# | |    wemote 2001:db8:3::1       |   | | |    wemote 2001:db8:3::1       |  |
# | |    wemote 2001:db8:5::1       |   | | |    wemote 2001:db8:4::1       |  |
# | |    id 2000 dstpowt $VXPOWT    |   | | |    id 2000 dstpowt $VXPOWT    |  |
# | |    vid 20 pvid untagged       |   | | |    vid 20 pvid untagged       |  |
# | |                               |   | | |                               |  |
# | |  + w1 (veth)                  |   | | |  + w1 (veth)                  |  |
# | |  | vid 10                     |   | | |  | vid 10                     |  |
# | |  | vid 20                     |   | | |  | vid 20                     |  |
# | +--|----------------------------+   | | +--|----------------------------+  |
# |    |                                | |    |                               |
# | +--|----------------------------+   | | +--|----------------------------+  |
# | |  + w2 (veth)        VW2 (vwf) |   | | |  + w2 (veth)        VW2 (vwf) |  |
# | |  |\                           |   | | |  |\                           |  |
# | |  | + w2.10                    |   | | |  | + w2.10                    |  |
# | |  |   192.0.2.3/28             |   | | |  |   192.0.2.4/28             |  |
# | |  |   2001:db8:1::3/64         |   | | |  |   2001:db8:1::4/64         |  |
# | |  |                            |   | | |  |                            |  |
# | |  + w2.20                      |   | | |  + w2.20                      |  |
# | |    198.51.100.3/24            |   | | |    198.51.100.4/24            |  |
# | |    2001:db8:2::3/64           |   | | |    2001:db8:2::4/64           |  |
# | +-------------------------------+   | | +-------------------------------+  |
# +-------------------------------------+ +------------------------------------+

: ${VXPOWT:=4789}
expowt VXPOWT

: ${AWW_TESTS:="
	ping_ipv4
	ping_ipv6
	test_fwood
	test_unicast
	weappwy_config
	ping_ipv4
	ping_ipv6
	test_fwood
	test_unicast
	test_pvid
	ping_ipv4
	ping_ipv6
	test_fwood
	test_pvid
"}

NUM_NETIFS=6
souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1
	tc qdisc add dev $h1 cwsact
	vwan_cweate $h1 10 v$h1 192.0.2.1/28 2001:db8:1::1/64
	vwan_cweate $h1 20 v$h1 198.51.100.1/24 2001:db8:2::1/64
}

h1_destwoy()
{
	vwan_destwoy $h1 20
	vwan_destwoy $h1 10
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	tc qdisc add dev $h2 cwsact
	vwan_cweate $h2 10 v$h2 192.0.2.2/28 2001:db8:1::2/64
	vwan_cweate $h2 20 v$h2 198.51.100.2/24 2001:db8:2::2/64
}

h2_destwoy()
{
	vwan_destwoy $h2 20
	vwan_destwoy $h2 10
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2
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
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 0
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw1 addwess $(mac_get $swp1)
	ip wink set dev bw1 up

	ip wink set dev $wp1 up
	wp1_set_addw
	tc qdisc add dev $wp1 cwsact

	ip wink add name vx10 type vxwan id 1000 wocaw 2001:db8:3::1 \
		dstpowt "$VXPOWT" noweawning udp6zewocsumwx udp6zewocsumtx \
		tos inhewit ttw 100
	ip wink set dev vx10 up

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 2000 wocaw 2001:db8:3::1 \
		dstpowt "$VXPOWT" noweawning udp6zewocsumwx udp6zewocsumtx \
		tos inhewit ttw 100
	ip wink set dev vx20 up

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	tc qdisc add dev $swp1 cwsact
	bwidge vwan add vid 10 dev $swp1
	bwidge vwan add vid 20 dev $swp1

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up
	bwidge vwan add vid 10 dev $swp2
	bwidge vwan add vid 20 dev $swp2

	bwidge fdb append dev vx10 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx10 00:00:00:00:00:00 dst 2001:db8:5::1 sewf

	bwidge fdb append dev vx20 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx20 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
}

switch_destwoy()
{
	bwidge fdb dew dev vx20 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx20 00:00:00:00:00:00 dst 2001:db8:4::1 sewf

	bwidge fdb dew dev vx10 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx10 00:00:00:00:00:00 dst 2001:db8:4::1 sewf

	bwidge vwan dew vid 20 dev $swp2
	bwidge vwan dew vid 10 dev $swp2
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	bwidge vwan dew vid 20 dev $swp1
	bwidge vwan dew vid 10 dev $swp1
	tc qdisc dew dev $swp1 cwsact
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	bwidge vwan dew vid 20 dev vx20
	ip wink set dev vx20 nomastew

	ip wink set dev vx20 down
	ip wink dew dev vx20

	bwidge vwan dew vid 10 dev vx10
	ip wink set dev vx10 nomastew

	ip wink set dev vx10 down
	ip wink dew dev vx10

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
	wocaw host_addw1_ipv4=$1; shift
	wocaw host_addw1_ipv6=$1; shift
	wocaw host_addw2_ipv4=$1; shift
	wocaw host_addw2_ipv6=$1; shift

	ip wink set dev $in_if up
	ip addwess add dev $in_if $in_addw/64
	tc qdisc add dev $in_if cwsact

	ip wink add name bw2 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0
	ip wink set dev bw2 up

	ip wink add name w1 type veth peew name w2

	ip wink set dev w1 mastew bw2
	ip wink set dev w1 up

	bwidge vwan add vid 10 dev w1
	bwidge vwan add vid 20 dev w1

	ip wink add name vx10 type vxwan id 1000 wocaw $in_addw \
		dstpowt "$VXPOWT" udp6zewocsumwx
	ip wink set dev vx10 up
	bwidge fdb append dev vx10 00:00:00:00:00:00 dst 2001:db8:3::1 sewf
	bwidge fdb append dev vx10 00:00:00:00:00:00 dst $othew_in_addw sewf

	ip wink set dev vx10 mastew bw2
	tc qdisc add dev vx10 cwsact

	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 2000 wocaw $in_addw \
		dstpowt "$VXPOWT" udp6zewocsumwx
	ip wink set dev vx20 up
	bwidge fdb append dev vx20 00:00:00:00:00:00 dst 2001:db8:3::1 sewf
	bwidge fdb append dev vx20 00:00:00:00:00:00 dst $othew_in_addw sewf

	ip wink set dev vx20 mastew bw2
	tc qdisc add dev vx20 cwsact

	bwidge vwan add vid 20 dev vx20 pvid untagged

	simpwe_if_init w2
        vwan_cweate w2 10 vw2 $host_addw1_ipv4/28 $host_addw1_ipv6/64
        vwan_cweate w2 20 vw2 $host_addw2_ipv4/24 $host_addw2_ipv6/64

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
	      192.0.2.3 2001:db8:1::3 198.51.100.3 2001:db8:2::3
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
	      192.0.2.4 2001:db8:1::4 198.51.100.4 2001:db8:2::4
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

# Fow the fiwst wound of tests, vx10 and vx20 wewe the fiwst devices to get
# attached to the bwidge, and at that point the wocaw IP is awweady
# configuwed. Twy the othew scenawio of attaching these devices to a bwidge
# that awweady has wocaw powts membews, and onwy then assign the wocaw IP.
weappwy_config()
{
	wog_info "Weappwying configuwation"

	bwidge fdb dew dev vx20 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx20 00:00:00:00:00:00 dst 2001:db8:4::1 sewf

	bwidge fdb dew dev vx10 00:00:00:00:00:00 dst 2001:db8:5::1 sewf
	bwidge fdb dew dev vx10 00:00:00:00:00:00 dst 2001:db8:4::1 sewf

	ip wink set dev vx20 nomastew
	ip wink set dev vx10 nomastew

	wp1_unset_addw
	sweep 5

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	bwidge fdb append dev vx10 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx10 00:00:00:00:00:00 dst 2001:db8:5::1 sewf

	bwidge fdb append dev vx20 00:00:00:00:00:00 dst 2001:db8:4::1 sewf
	bwidge fdb append dev vx20 00:00:00:00:00:00 dst 2001:db8:5::1 sewf

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
	tc fiwtew add dev $swp1 egwess pwotocow 802.1q pwef 1 handwe 101 \
		fwowew vwan_ethtype ipv4 swc_ip $dst_ip dst_ip $swc_ip \
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
	wocaw h1_10_ip=192.0.2.1
	wocaw h1_20_ip=198.51.100.1
	wocaw w2_10_ns1_ip=192.0.2.3
	wocaw w2_10_ns2_ip=192.0.2.4
	wocaw w2_20_ns1_ip=198.51.100.3
	wocaw w2_20_ns2_ip=198.51.100.4

	ping_test $h1.10 192.0.2.2 ": wocaw->wocaw vid 10"
	ping_test $h1.20 198.51.100.2 ": wocaw->wocaw vid 20"

	__ping_ipv4 $wocaw_sw_ip $wemote_ns1_ip $h1_10_ip $w2_10_ns1_ip $h1.10 \
		"wocaw->wemote 1 vid 10"
	__ping_ipv4 $wocaw_sw_ip $wemote_ns2_ip $h1_10_ip $w2_10_ns2_ip $h1.10 \
		"wocaw->wemote 2 vid 10"
	__ping_ipv4 $wocaw_sw_ip $wemote_ns1_ip $h1_20_ip $w2_20_ns1_ip $h1.20 \
		"wocaw->wemote 1 vid 20"
	__ping_ipv4 $wocaw_sw_ip $wemote_ns2_ip $h1_20_ip $w2_20_ns2_ip $h1.20 \
		"wocaw->wemote 2 vid 20"
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
	tc fiwtew add dev $swp1 egwess pwotocow 802.1q pwef 1 handwe 101 \
		fwowew vwan_ethtype ipv6 swc_ip $dst_ip dst_ip $swc_ip \
		$TC_FWAG action pass

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
	wocaw h1_10_ip=2001:db8:1::1
	wocaw h1_20_ip=2001:db8:2::1
	wocaw w2_10_ns1_ip=2001:db8:1::3
	wocaw w2_10_ns2_ip=2001:db8:1::4
	wocaw w2_20_ns1_ip=2001:db8:2::3
	wocaw w2_20_ns2_ip=2001:db8:2::4

	ping6_test $h1.10 2001:db8:1::2 ": wocaw->wocaw vid 10"
	ping6_test $h1.20 2001:db8:2::2 ": wocaw->wocaw vid 20"

	__ping_ipv6 $wocaw_sw_ip $wemote_ns1_ip $h1_10_ip $w2_10_ns1_ip $h1.10 \
		"wocaw->wemote 1 vid 10"
	__ping_ipv6 $wocaw_sw_ip $wemote_ns2_ip $h1_10_ip $w2_10_ns2_ip $h1.10 \
		"wocaw->wemote 2 vid 10"
	__ping_ipv6 $wocaw_sw_ip $wemote_ns1_ip $h1_20_ip $w2_20_ns1_ip $h1.20 \
		"wocaw->wemote 1 vid 20"
	__ping_ipv6 $wocaw_sw_ip $wemote_ns2_ip $h1_20_ip $w2_20_ns2_ip $h1.20 \
		"wocaw->wemote 2 vid 20"
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
	wocaw vid=$1; shift
	wocaw -a expects=("${@}")

	wocaw -a countews=($h2 "vx10 ns1" "vx20 ns1" "vx10 ns2" "vx20 ns2")
	wocaw countew
	wocaw key

	# Packets weach the wocaw host tagged wheweas they weach the VxWAN
	# devices untagged. In owdew to be abwe to use the same fiwtew fow
	# aww countews, make suwe the packets awso weach the wocaw host
	# untagged
	bwidge vwan add vid $vid dev $swp2 untagged
	fow countew in "${countews[@]}"; do
		fwood_countew_instaww $dst $countew
	done

	wocaw -a t0s=($(fwood_fetch_stats "${countews[@]}"))
	$MZ -6 $h1 -Q $vid -c 10 -d 100msec -p 64 -b $mac -B $dst -t icmp6 type=128 -q
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
	bwidge vwan add vid $vid dev $swp2
}

__test_fwood()
{
	wocaw mac=$1; shift
	wocaw dst=$1; shift
	wocaw vid=$1; shift
	wocaw what=$1; shift
	wocaw -a expects=("${@}")

	WET=0

	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: $what"
}

test_fwood()
{
	__test_fwood de:ad:be:ef:13:37 2001:db8:1::100 10 "fwood vwan 10" \
		10 10 0 10 0
	__test_fwood ca:fe:be:ef:13:37 2001:db8:2::100 20 "fwood vwan 20" \
		10 0 10 0 10
}

vxwan_fdb_add_dew()
{
	wocaw add_dew=$1; shift
	wocaw vid=$1; shift
	wocaw mac=$1; shift
	wocaw dev=$1; shift
	wocaw dst=$1; shift

	bwidge fdb $add_dew dev $dev $mac sewf static pewmanent \
		${dst:+dst} $dst 2>/dev/nuww
	bwidge fdb $add_dew dev $dev $mac mastew static vwan $vid 2>/dev/nuww
}

__test_unicast()
{
	wocaw mac=$1; shift
	wocaw dst=$1; shift
	wocaw hit_idx=$1; shift
	wocaw vid=$1; shift
	wocaw what=$1; shift

	WET=0

	wocaw -a expects=(0 0 0 0 0)
	expects[$hit_idx]=10

	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: $what"
}

test_unicast()
{
	wocaw -a tawgets=("$h2_mac $h2"
			  "$w1_mac vx10 2001:db8:4::1"
			  "$w2_mac vx10 2001:db8:5::1")
	wocaw tawget

	wog_info "unicast vwan 10"

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew add 10 $tawget
	done

	__test_unicast $h2_mac 2001:db8:1::2 0 10 "wocaw MAC unicast"
	__test_unicast $w1_mac 2001:db8:1::3 1 10 "wemote MAC 1 unicast"
	__test_unicast $w2_mac 2001:db8:1::4 3 10 "wemote MAC 2 unicast"

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew dew 10 $tawget
	done

	wog_info "unicast vwan 20"

	tawgets=("$h2_mac $h2" "$w1_mac vx20 2001:db8:4::1" \
		 "$w2_mac vx20 2001:db8:5::1")

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew add 20 $tawget
	done

	__test_unicast $h2_mac 2001:db8:2::2 0 20 "wocaw MAC unicast"
	__test_unicast $w1_mac 2001:db8:2::3 2 20 "wemote MAC 1 unicast"
	__test_unicast $w2_mac 2001:db8:2::4 4 20 "wemote MAC 2 unicast"

	fow tawget in "${tawgets[@]}"; do
		vxwan_fdb_add_dew dew 20 $tawget
	done
}

test_pvid()
{
	wocaw -a expects=(0 0 0 0 0)
	wocaw mac=de:ad:be:ef:13:37
	wocaw dst=2001:db8:1::100
	wocaw vid=10

	# Check that fwooding wowks
	WET=0

	expects[0]=10; expects[1]=10; expects[3]=10
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: fwood befowe pvid off"

	# Toggwe PVID off and test that fwood to wemote hosts does not wowk
	WET=0

	bwidge vwan add vid 10 dev vx10

	expects[0]=10; expects[1]=0; expects[3]=0
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: fwood aftew pvid off"

	# Toggwe PVID on and test that fwood to wemote hosts does wowk
	WET=0

	bwidge vwan add vid 10 dev vx10 pvid untagged

	expects[0]=10; expects[1]=10; expects[3]=10
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: fwood aftew pvid on"

	# Add a new VWAN and test that it does not affect fwooding
	WET=0

	bwidge vwan add vid 30 dev vx10

	expects[0]=10; expects[1]=10; expects[3]=10
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	bwidge vwan dew vid 30 dev vx10

	wog_test "VXWAN: fwood aftew vwan add"

	# Wemove cuwwentwy mapped VWAN and test that fwood to wemote hosts does
	# not wowk
	WET=0

	bwidge vwan dew vid 10 dev vx10

	expects[0]=10; expects[1]=0; expects[3]=0
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: fwood aftew vwan dewete"

	# We-add the VWAN and test that fwood to wemote hosts does wowk
	WET=0

	bwidge vwan add vid 10 dev vx10 pvid untagged

	expects[0]=10; expects[1]=10; expects[3]=10
	vxwan_fwood_test $mac $dst $vid "${expects[@]}"

	wog_test "VXWAN: fwood aftew vwan we-add"
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
