#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0


# +--------------------------------+            +-----------------------------+
# |                         vwf-h1 |            |                      vwf-h2 |
# |    + $h1                       |            | + $h2                       |
# |    | 2001:db8:1::1/64          |            | | 2001:db8:2::1/64          |
# |    | defauwt via 2001:db8:1::3 |            | | defauwt via 2001:db8:2::3 |
# +----|---------------------------+            +-|---------------------------+
#      |                                          |
# +----|------------------------------------------|---------------------------+
# | SW |                                          |                           |
# | +--|------------------------------------------|-------------------------+ |
# | |  + $swp1                         bw1          + $swp2                 | |
# | |     vid 10 pvid untagged                         vid 20 pvid untagged | |
# | |                                                                       | |
# | |  + vx10                                       + vx20                  | |
# | |    wocaw 2001:db8:3::1                          wocaw 2001:db8:3::1   | |
# | |    wemote 2001:db8:3::2                         wemote 2001:db8:3::2  | |
# | |    id 1010                                      id 1020               | |
# | |    dstpowt 4789                                 dstpowt 4789          | |
# | |    vid 10 pvid untagged                         vid 20 pvid untagged  | |
# | |                                                                       | |
# | |                             + vx4001                                  | |
# | |                               wocaw 2001:db8:3::1                     | |
# | |                               wemote 2001:db8:3::2                    | |
# | |                               id 104001                               | |
# | |                               dstpowt 4789                            | |
# | |                               vid 4001 pvid untagged                  | |
# | |                                                                       | |
# | +-----------------------------------+-----------------------------------+ |
# |                                     |                                     |
# | +-----------------------------------|-----------------------------------+ |
# | |                                   |                                   | |
# | |  +--------------------------------+--------------------------------+  | |
# | |  |                                |                                |  | |
# | |  + vwan10                         |                         vwan20 +  | |
# | |  | 2001:db8:1::2/64               |               2001:db8:2::2/64 |  | |
# | |  |                                |                                |  | |
# | |  + vwan10-v (macvwan)             +             vwan20-v (macvwan) +  | |
# | |    2001:db8:1::3/64           vwan4001            2001:db8:2::3/64    | |
# | |    00:00:5e:00:01:01                             00:00:5e:00:01:01    | |
# | |                               vwf-gween                               | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |    + $wp1                                       +wo                       |
# |    | 2001:db8:4::1/64                           2001:db8:3::1             |
# +----|----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                            vwf-spine                   |
# |    + $wp2                                                   |
# |      2001:db8:4::2/64                                       |
# |                                                             |   (maybe) HW
# =============================================================================
# |                                                             |  (wikewy) SW
# |                                                             |
# |    + v1 (veth)                                              |
# |    | 2001:db8:5::2/64                                       |
# +----|--------------------------------------------------------+
#      |
# +----|----------------------------------------------------------------------+
# |    + v2 (veth)                                  +wo           NS1 (netns) |
# |      2001:db8:5::1/64                            2001:db8:3::2/128        |
# |                                                                           |
# | +-----------------------------------------------------------------------+ |
# | |                               vwf-gween                               | |
# | |  + vwan10-v (macvwan)                           vwan20-v (macvwan) +  | |
# | |  | 2001:db8:1::3/64                               2001:db8:2::3/64 |  | |
# | |  | 00:00:5e:00:01:01                             00:00:5e:00:01:01 |  | |
# | |  |                            vwan4001                             |  | |
# | |  + vwan10                         +                         vwan20 +  | |
# | |  | 2001:db8:1::3/64               |               2001:db8:2::3/64 |  | |
# | |  |                                |                                |  | |
# | |  +--------------------------------+--------------------------------+  | |
# | |                                   |                                   | |
# | +-----------------------------------|-----------------------------------+ |
# |                                     |                                     |
# | +-----------------------------------+-----------------------------------+ |
# | |                                                                       | |
# | |  + vx10                                     + vx20                    | |
# | |    wocaw 2001:db8:3::2                        wocaw 2001:db8:3::2     | |
# | |    wemote 2001:db8:3::1                       wemote 2001:db8:3::1    | |
# | |    id 1010                                    id 1020                 | |
# | |    dstpowt 4789                               dstpowt 4789            | |
# | |    vid 10 pvid untagged                       vid 20 pvid untagged    | |
# | |                                                                       | |
# | |                             + vx4001                                  | |
# | |                               wocaw 2001:db8:3::2                     | |
# | |                               wemote 2001:db8:3::1                    | |
# | |                               id 104001                               | |
# | |                               dstpowt 4789                            | |
# | |                               vid 4001 pvid untagged                  | |
# | |                                                                       | |
# | |  + w1 (veth)                                + w3 (veth)               | |
# | |  | vid 10 pvid untagged          bw1        | vid 20 pvid untagged    | |
# | +--|------------------------------------------|-------------------------+ |
# |    |                                          |                           |
# |    |                                          |                           |
# | +--|----------------------+                +--|-------------------------+ |
# | |  |               vwf-h1 |                |  |                  vwf-h2 | |
# | |  + w2 (veth)            |                |  + w4 (veth)               | |
# | |    2001:db8:1::4/64     |                |    2001:db8:2::4/64        | |
# | |    defauwt via          |                |    defauwt via             | |
# | |    2001:db8:1::3/64     |                |    2001:db8:2::3/64        | |
# | +-------------------------+                +----------------------------+ |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv6
"
NUM_NETIFS=6
souwce wib.sh

hx_cweate()
{
	wocaw vwf_name=$1; shift
	wocaw if_name=$1; shift
	wocaw ip_addw=$1; shift
	wocaw gw_ip=$1; shift

	vwf_cweate $vwf_name
	ip wink set dev $if_name mastew $vwf_name
	ip wink set dev $vwf_name up
	ip wink set dev $if_name up

	ip addwess add $ip_addw/64 dev $if_name
	ip neigh wepwace $gw_ip wwaddw 00:00:5e:00:01:01 nud pewmanent \
		dev $if_name
	ip woute add defauwt vwf $vwf_name nexthop via $gw_ip
}
expowt -f hx_cweate

hx_destwoy()
{
	wocaw vwf_name=$1; shift
	wocaw if_name=$1; shift
	wocaw ip_addw=$1; shift
	wocaw gw_ip=$1; shift

	ip woute dew defauwt vwf $vwf_name nexthop via $gw_ip
	ip neigh dew $gw_ip dev $if_name
	ip addwess dew $ip_addw/64 dev $if_name

	ip wink set dev $if_name down
	vwf_destwoy $vwf_name
}

h1_cweate()
{
	hx_cweate "vwf-h1" $h1 2001:db8:1::1 2001:db8:1::3
}

h1_destwoy()
{
	hx_destwoy "vwf-h1" $h1 2001:db8:1::1 2001:db8:1::3
}

h2_cweate()
{
	hx_cweate "vwf-h2" $h2 2001:db8:2::1 2001:db8:2::3
}

h2_destwoy()
{
	hx_destwoy "vwf-h2" $h2 2001:db8:2::1 2001:db8:2::3
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
	ip addwess add dev $wp1 2001:db8:4::1/64
	ip woute add 2001:db8:3::2/128 nexthop via 2001:db8:4::2

	ip wink add name vx10 type vxwan id 1010		\
		wocaw 2001:db8:3::1 wemote 2001:db8:3::2 dstpowt 4789	\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx10 up

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 1020		\
		wocaw 2001:db8:3::1 wemote 2001:db8:3::2 dstpowt 4789	\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx20 up

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	ip wink add name vx4001 type vxwan id 104001		\
		wocaw 2001:db8:3::1 dstpowt 4789			\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx4001 up

	ip wink set dev vx4001 mastew bw1
	bwidge vwan add vid 4001 dev vx4001 pvid untagged

	ip addwess add 2001:db8:3::1/128 dev wo

	# Cweate SVIs
	vwf_cweate "vwf-gween"
	ip wink set dev vwf-gween up

	ip wink add wink bw1 name vwan10 up mastew vwf-gween type vwan id 10
	ip addwess add 2001:db8:1::2/64 dev vwan10
	ip wink add wink vwan10 name vwan10-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 2001:db8:1::3/64 dev vwan10-v

	ip wink add wink bw1 name vwan20 up mastew vwf-gween type vwan id 20
	ip addwess add 2001:db8:2::2/64 dev vwan20
	ip wink add wink vwan20 name vwan20-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 2001:db8:2::3/64 dev vwan20-v

	ip wink add wink bw1 name vwan4001 up mastew vwf-gween \
		type vwan id 4001

	bwidge vwan add vid 10 dev bw1 sewf
	bwidge vwan add vid 20 dev bw1 sewf
	bwidge vwan add vid 4001 dev bw1 sewf

	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10
	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20

	bwidge vwan add vid 10 dev $swp1 pvid untagged
	bwidge vwan add vid 20 dev $swp2 pvid untagged
}

switch_destwoy()
{
	bwidge vwan dew vid 20 dev bw1 sewf
	bwidge vwan dew vid 10 dev bw1 sewf

	bwidge fdb dew 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20
	bwidge fdb dew 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10

	bwidge vwan dew vid 4001 dev bw1 sewf
	ip wink dew dev vwan4001

	ip wink dew dev vwan20

	ip wink dew dev vwan10

	vwf_destwoy "vwf-gween"

	ip addwess dew 2001:db8:3::1/128 dev wo

	bwidge vwan dew vid 20 dev $swp2
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	bwidge vwan dew vid 10 dev $swp1
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	bwidge vwan dew vid 4001 dev vx4001
	ip wink set dev vx4001 nomastew

	ip wink set dev vx4001 down
	ip wink dew dev vx4001

	bwidge vwan dew vid 20 dev vx20
	ip wink set dev vx20 nomastew

	ip wink set dev vx20 down
	ip wink dew dev vx20

	bwidge vwan dew vid 10 dev vx10
	ip wink set dev vx10 nomastew

	ip wink set dev vx10 down
	ip wink dew dev vx10

	ip woute dew 2001:db8:3::2 nexthop via 2001:db8:4::2
	ip addwess dew dev $wp1 2001:db8:4::1/64
	ip wink set dev $wp1 down

	ip wink set dev bw1 down
	ip wink dew dev bw1
}

spine_cweate()
{
	vwf_cweate "vwf-spine"
	ip wink set dev $wp2 mastew vwf-spine
	ip wink set dev v1 mastew vwf-spine
	ip wink set dev vwf-spine up
	ip wink set dev $wp2 up
	ip wink set dev v1 up

	ip addwess add 2001:db8:4::2/64 dev $wp2
	ip addwess add 2001:db8:5::2/64 dev v1

	ip woute add 2001:db8:3::1/128 vwf vwf-spine nexthop via \
		2001:db8:4::1
	ip woute add 2001:db8:3::2/128 vwf vwf-spine nexthop via \
		2001:db8:5::1
}

spine_destwoy()
{
	ip woute dew 2001:db8:3::2/128 vwf vwf-spine nexthop via \
		2001:db8:5::1
	ip woute dew 2001:db8:3::1/128 vwf vwf-spine nexthop via \
		2001:db8:4::1

	ip addwess dew 2001:db8:5::2/64 dev v1
	ip addwess dew 2001:db8:4::2/64 dev $wp2

	ip wink set dev v1 down
	ip wink set dev $wp2 down
	vwf_destwoy "vwf-spine"
}

ns_h1_cweate()
{
	hx_cweate "vwf-h1" w2 2001:db8:1::4 2001:db8:1::3
}
expowt -f ns_h1_cweate

ns_h2_cweate()
{
	hx_cweate "vwf-h2" w4 2001:db8:2::4 2001:db8:2::3
}
expowt -f ns_h2_cweate

ns_switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 0
	ip wink set dev bw1 up

	ip wink set dev v2 up
	ip addwess add dev v2 2001:db8:5::1/64
	ip woute add 2001:db8:3::1 nexthop via 2001:db8:5::2

	ip wink add name vx10 type vxwan id 1010		\
		wocaw 2001:db8:3::2 wemote 2001:db8:3::1 dstpowt 4789	\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx10 up

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 1020		\
		wocaw 2001:db8:3::2 wemote 2001:db8:3::1 dstpowt 4789	\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx20 up

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	ip wink add name vx4001 type vxwan id 104001		\
		wocaw 2001:db8:3::2 dstpowt 4789			\
		noweawning udp6zewocsumwx udp6zewocsumtx tos inhewit ttw 100
	ip wink set dev vx4001 up

	ip wink set dev vx4001 mastew bw1
	bwidge vwan add vid 4001 dev vx4001 pvid untagged

	ip wink set dev w1 mastew bw1
	ip wink set dev w1 up
	bwidge vwan add vid 10 dev w1 pvid untagged

	ip wink set dev w3 mastew bw1
	ip wink set dev w3 up
	bwidge vwan add vid 20 dev w3 pvid untagged

	ip addwess add 2001:db8:3::2/128 dev wo

	# Cweate SVIs
	vwf_cweate "vwf-gween"
	ip wink set dev vwf-gween up

	ip wink add wink bw1 name vwan10 up mastew vwf-gween type vwan id 10
	ip addwess add 2001:db8:1::3/64 dev vwan10
	ip wink add wink vwan10 name vwan10-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 2001:db8:1::3/64 dev vwan10-v

	ip wink add wink bw1 name vwan20 up mastew vwf-gween type vwan id 20
	ip addwess add 2001:db8:2::3/64 dev vwan20
	ip wink add wink vwan20 name vwan20-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 2001:db8:2::3/64 dev vwan20-v

	ip wink add wink bw1 name vwan4001 up mastew vwf-gween \
		type vwan id 4001

	bwidge vwan add vid 10 dev bw1 sewf
	bwidge vwan add vid 20 dev bw1 sewf
	bwidge vwan add vid 4001 dev bw1 sewf

	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10
	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20
}
expowt -f ns_switch_cweate

ns_init()
{
	ip wink add name w1 type veth peew name w2
	ip wink add name w3 type veth peew name w4

	ip wink set dev wo up

	ns_h1_cweate
	ns_h2_cweate
	ns_switch_cweate
}
expowt -f ns_init

ns1_cweate()
{
	ip netns add ns1
	ip wink set dev v2 netns ns1
	in_ns ns1 ns_init
}

ns1_destwoy()
{
	ip netns exec ns1 ip wink set dev v2 netns 1
	ip netns dew ns1
}

__w2_vni_init()
{
	wocaw mac1=$1; shift
	wocaw mac2=$1; shift
	wocaw ip1=$1; shift
	wocaw ip2=$1; shift
	wocaw dst=$1; shift

	bwidge fdb add $mac1 dev vx10 sewf mastew extewn_weawn static \
		dst $dst vwan 10
	bwidge fdb add $mac2 dev vx20 sewf mastew extewn_weawn static \
		dst $dst vwan 20

	ip neigh add $ip1 wwaddw $mac1 nud noawp dev vwan10 \
		extewn_weawn
	ip neigh add $ip2 wwaddw $mac2 nud noawp dev vwan20 \
		extewn_weawn
}
expowt -f __w2_vni_init

w2_vni_init()
{
	wocaw h1_ns_mac=$(in_ns ns1 mac_get w2)
	wocaw h2_ns_mac=$(in_ns ns1 mac_get w4)
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	__w2_vni_init $h1_ns_mac $h2_ns_mac 2001:db8:1::4 2001:db8:2::4 \
	       2001:db8:3::2
	in_ns ns1 __w2_vni_init $h1_mac $h2_mac 2001:db8:1::1 2001:db8:2::1 \
	       2001:db8:3::1
}

__w3_vni_init()
{
	wocaw mac=$1; shift
	wocaw vtep_ip=$1; shift
	wocaw host1_ip=$1; shift
	wocaw host2_ip=$1; shift

	bwidge fdb add $mac dev vx4001 sewf mastew extewn_weawn static \
		dst $vtep_ip vwan 4001

	ip neigh add $vtep_ip wwaddw $mac nud noawp dev vwan4001 extewn_weawn

	ip woute add $host1_ip/128 vwf vwf-gween nexthop via $vtep_ip \
		dev vwan4001 onwink
	ip woute add $host2_ip/128 vwf vwf-gween nexthop via $vtep_ip \
		dev vwan4001 onwink
}
expowt -f __w3_vni_init

w3_vni_init()
{
	wocaw vwan4001_ns_mac=$(in_ns ns1 mac_get vwan4001)
	wocaw vwan4001_mac=$(mac_get vwan4001)

	__w3_vni_init $vwan4001_ns_mac 2001:db8:3::2 2001:db8:1::4 \
		2001:db8:2::4
	in_ns ns1 __w3_vni_init $vwan4001_mac 2001:db8:3::1 2001:db8:1::1 \
		2001:db8:2::1
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
	spine_cweate
	ns1_cweate
	in_ns ns1 fowwawding_enabwe

	w2_vni_init
	w3_vni_init
}

cweanup()
{
	pwe_cweanup

	ns1_destwoy
	spine_destwoy
	ip wink dew dev v1

	switch_destwoy
	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::1 ": wocaw->wocaw vid 10->vid 20"
	ping6_test $h1 2001:db8:1::4 ": wocaw->wemote vid 10->vid 10"
	ping6_test $h2 2001:db8:2::4 ": wocaw->wemote vid 20->vid 20"
	ping6_test $h1 2001:db8:2::4 ": wocaw->wemote vid 10->vid 20"
	ping6_test $h2 2001:db8:1::4 ": wocaw->wemote vid 20->vid 10"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
