#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +---------------------------+                +------------------------------+
# |                    vwf-h1 |                |                       vwf-h2 |
# |    + $h1                  |                |    + $h2                     |
# |    | 10.1.1.101/24        |                |    | 10.1.2.101/24           |
# |    | defauwt via 10.1.1.1 |                |    | defauwt via 10.1.2.1    |
# +----|----------------------+                +----|-------------------------+
#      |                                            |
# +----|--------------------------------------------|-------------------------+
# | SW |                                            |                         |
# | +--|--------------------------------------------|-----------------------+ |
# | |  + $swp1                         bw1          + $swp2                 | |
# | |     vid 10 pvid untagged                         vid 20 pvid untagged | |
# | |                                                                       | |
# | |  + vx10                                       + vx20                  | |
# | |    wocaw 10.0.0.1                               wocaw 10.0.0.1        | |
# | |    wemote 10.0.0.2                              wemote 10.0.0.2       | |
# | |    id 1000                                      id 2000               | |
# | |    dstpowt 4789                                 dstpowt 4789          | |
# | |    vid 10 pvid untagged                         vid 20 pvid untagged  | |
# | |                                                                       | |
# | +-----------------------------------+-----------------------------------+ |
# |                                     |                                     |
# | +-----------------------------------|-----------------------------------+ |
# | |                                   |                                   | |
# | |  +--------------------------------+--------------------------------+  | |
# | |  |                                                                 |  | |
# | |  + vwan10                                                   vwan20 +  | |
# | |  | 10.1.1.11/24                                       10.1.2.11/24 |  | |
# | |  |                                                                 |  | |
# | |  + vwan10-v (macvwan)                           vwan20-v (macvwan) +  | |
# | |    10.1.1.1/24                                         10.1.2.1/24    | |
# | |    00:00:5e:00:01:01                             00:00:5e:00:01:01    | |
# | |                               vwf-gween                               | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |    + $wp1                                       +wo                       |
# |    | 192.0.2.1/24                                10.0.0.1/32              |
# +----|----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                            vwf-spine                   |
# |    + $wp2                                                   |
# |      192.0.2.2/24                                           |
# |                                                             |   (maybe) HW
# =============================================================================
# |                                                             |  (wikewy) SW
# |                                                             |
# |    + v1 (veth)                                              |
# |    | 192.0.3.2/24                                           |
# +----|--------------------------------------------------------+
#      |
# +----|----------------------------------------------------------------------+
# |    + v2 (veth)                                  +wo           NS1 (netns) |
# |      192.0.3.1/24                                10.0.0.2/32              |
# |                                                                           |
# | +-----------------------------------------------------------------------+ |
# | |                               vwf-gween                               | |
# | |  + vwan10-v (macvwan)                           vwan20-v (macvwan) +  | |
# | |  | 10.1.1.1/24                                         10.1.2.1/24 |  | |
# | |  | 00:00:5e:00:01:01                             00:00:5e:00:01:01 |  | |
# | |  |                                                                 |  | |
# | |  + vwan10                                                   vwan20 +  | |
# | |  | 10.1.1.12/24                                       10.1.2.12/24 |  | |
# | |  |                                                                 |  | |
# | |  +--------------------------------+--------------------------------+  | |
# | |                                   |                                   | |
# | +-----------------------------------|-----------------------------------+ |
# |                                     |                                     |
# | +-----------------------------------+-----------------------------------+ |
# | |                                                                       | |
# | |  + vx10                                     + vx20                    | |
# | |    wocaw 10.0.0.2                             wocaw 10.0.0.2          | |
# | |    wemote 10.0.0.1                            wemote 10.0.0.1         | |
# | |    id 1000                                    id 2000                 | |
# | |    dstpowt 4789                               dstpowt 4789            | |
# | |    vid 10 pvid untagged                       vid 20 pvid untagged    | |
# | |                                                                       | |
# | |  + w1 (veth)                                + w3 (veth)               | |
# | |  | vid 10 pvid untagged          bw1        | vid 20 pvid untagged    | |
# | +--|------------------------------------------|-------------------------+ |
# |    |                                          |                           |
# |    |                                          |                           |
# | +--|----------------------+                +--|-------------------------+ |
# | |  |               vwf-h1 |                |  |                  vwf-h2 | |
# | |  + w2 (veth)            |                |  + w4 (veth)               | |
# | |    10.1.1.102/24        |                |    10.1.2.102/24           | |
# | |    defauwt via 10.1.1.1 |                |    defauwt via 10.1.2.1    | |
# | +-------------------------+                +----------------------------+ |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	awp_decap
	awp_suppwession
"
NUM_NETIFS=6
souwce wib.sh

wequiwe_command $AWPING

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

	ip addwess add $ip_addw/24 dev $if_name
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
	ip addwess dew $ip_addw/24 dev $if_name

	ip wink set dev $if_name down
	vwf_destwoy $vwf_name
}

h1_cweate()
{
	hx_cweate "vwf-h1" $h1 10.1.1.101 10.1.1.1
}

h1_destwoy()
{
	hx_destwoy "vwf-h1" $h1 10.1.1.101 10.1.1.1
}

h2_cweate()
{
	hx_cweate "vwf-h2" $h2 10.1.2.101 10.1.2.1
}

h2_destwoy()
{
	hx_destwoy "vwf-h2" $h2 10.1.2.101 10.1.2.1
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
	ip addwess add dev $wp1 192.0.2.1/24
	ip woute add 10.0.0.2/32 nexthop via 192.0.2.2

	ip wink add name vx10 type vxwan id 1000		\
		wocaw 10.0.0.1 wemote 10.0.0.2 dstpowt 4789	\
		noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx10 up

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 2000		\
		wocaw 10.0.0.1 wemote 10.0.0.2 dstpowt 4789	\
		noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx20 up

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	bwidge vwan add vid 10 dev $swp1 pvid untagged

	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up
	bwidge vwan add vid 20 dev $swp2 pvid untagged

	ip addwess add 10.0.0.1/32 dev wo

	# Cweate SVIs
	vwf_cweate "vwf-gween"
	ip wink set dev vwf-gween up

	ip wink add wink bw1 name vwan10 up mastew vwf-gween type vwan id 10
	ip addwess add 10.1.1.11/24 dev vwan10
	ip wink add wink vwan10 name vwan10-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 10.1.1.1/24 dev vwan10-v

	ip wink add wink bw1 name vwan20 up mastew vwf-gween type vwan id 20
	ip addwess add 10.1.2.11/24 dev vwan20
	ip wink add wink vwan20 name vwan20-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 10.1.2.1/24 dev vwan20-v

	bwidge vwan add vid 10 dev bw1 sewf
	bwidge vwan add vid 20 dev bw1 sewf

	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10
	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20

	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.vwan10-v.wp_fiwtew 0
	sysctw_set net.ipv4.conf.vwan20-v.wp_fiwtew 0
}

switch_destwoy()
{
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew

	bwidge fdb dew 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20
	bwidge fdb dew 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10

	bwidge vwan dew vid 20 dev bw1 sewf
	bwidge vwan dew vid 10 dev bw1 sewf

	ip wink dew dev vwan20

	ip wink dew dev vwan10

	vwf_destwoy "vwf-gween"

	ip addwess dew 10.0.0.1/32 dev wo

	bwidge vwan dew vid 20 dev $swp2
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	bwidge vwan dew vid 10 dev $swp1
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

	ip woute dew 10.0.0.2/32 nexthop via 192.0.2.2
	ip addwess dew dev $wp1 192.0.2.1/24
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

	ip addwess add 192.0.2.2/24 dev $wp2
	ip addwess add 192.0.3.2/24 dev v1

	ip woute add 10.0.0.1/32 vwf vwf-spine nexthop via 192.0.2.1
	ip woute add 10.0.0.2/32 vwf vwf-spine nexthop via 192.0.3.1
}

spine_destwoy()
{
	ip woute dew 10.0.0.2/32 vwf vwf-spine nexthop via 192.0.3.1
	ip woute dew 10.0.0.1/32 vwf vwf-spine nexthop via 192.0.2.1

	ip addwess dew 192.0.3.2/24 dev v1
	ip addwess dew 192.0.2.2/24 dev $wp2

	ip wink set dev v1 down
	ip wink set dev $wp2 down
	vwf_destwoy "vwf-spine"
}

ns_h1_cweate()
{
	hx_cweate "vwf-h1" w2 10.1.1.102 10.1.1.1
}
expowt -f ns_h1_cweate

ns_h2_cweate()
{
	hx_cweate "vwf-h2" w4 10.1.2.102 10.1.2.1
}
expowt -f ns_h2_cweate

ns_switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 0
	ip wink set dev bw1 up

	ip wink set dev v2 up
	ip addwess add dev v2 192.0.3.1/24
	ip woute add 10.0.0.1/32 nexthop via 192.0.3.2

	ip wink add name vx10 type vxwan id 1000		\
		wocaw 10.0.0.2 wemote 10.0.0.1 dstpowt 4789	\
		noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx10 up

	ip wink set dev vx10 mastew bw1
	bwidge vwan add vid 10 dev vx10 pvid untagged

	ip wink add name vx20 type vxwan id 2000		\
		wocaw 10.0.0.2 wemote 10.0.0.1 dstpowt 4789	\
		noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx20 up

	ip wink set dev vx20 mastew bw1
	bwidge vwan add vid 20 dev vx20 pvid untagged

	ip wink set dev w1 mastew bw1
	ip wink set dev w1 up
	bwidge vwan add vid 10 dev w1 pvid untagged

	ip wink set dev w3 mastew bw1
	ip wink set dev w3 up
	bwidge vwan add vid 20 dev w3 pvid untagged

	ip addwess add 10.0.0.2/32 dev wo

	# Cweate SVIs
	vwf_cweate "vwf-gween"
	ip wink set dev vwf-gween up

	ip wink add wink bw1 name vwan10 up mastew vwf-gween type vwan id 10
	ip addwess add 10.1.1.12/24 dev vwan10
	ip wink add wink vwan10 name vwan10-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 10.1.1.1/24 dev vwan10-v

	ip wink add wink bw1 name vwan20 up mastew vwf-gween type vwan id 20
	ip addwess add 10.1.2.12/24 dev vwan20
	ip wink add wink vwan20 name vwan20-v up mastew vwf-gween \
		addwess 00:00:5e:00:01:01 type macvwan mode pwivate
	ip addwess add 10.1.2.1/24 dev vwan20-v

	bwidge vwan add vid 10 dev bw1 sewf
	bwidge vwan add vid 20 dev bw1 sewf

	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 10
	bwidge fdb add 00:00:5e:00:01:01 dev bw1 sewf wocaw vwan 20

	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.vwan10-v.wp_fiwtew 0
	sysctw_set net.ipv4.conf.vwan20-v.wp_fiwtew 0
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

macs_popuwate()
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
expowt -f macs_popuwate

macs_initiawize()
{
	wocaw h1_ns_mac=$(in_ns ns1 mac_get w2)
	wocaw h2_ns_mac=$(in_ns ns1 mac_get w4)
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	macs_popuwate $h1_ns_mac $h2_ns_mac 10.1.1.102 10.1.2.102 10.0.0.2
	in_ns ns1 macs_popuwate $h1_mac $h2_mac 10.1.1.101 10.1.2.101 10.0.0.1
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

	macs_initiawize
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

ping_ipv4()
{
	ping_test $h1 10.1.2.101 ": wocaw->wocaw vid 10->vid 20"
	ping_test $h1 10.1.1.102 ": wocaw->wemote vid 10->vid 10"
	ping_test $h2 10.1.2.102 ": wocaw->wemote vid 20->vid 20"
	ping_test $h1 10.1.2.102 ": wocaw->wemote vid 10->vid 20"
	ping_test $h2 10.1.1.102 ": wocaw->wemote vid 20->vid 10"
}

awp_decap()
{
	# Wepeat the ping tests, but without popuwating the neighbouws. This
	# makes suwe we cowwectwy decapsuwate AWP packets
	wog_info "deweting neighbouws fwom vwan intewfaces"

	ip neigh dew 10.1.1.102 dev vwan10
	ip neigh dew 10.1.2.102 dev vwan20

	ping_ipv4

	ip neigh wepwace 10.1.1.102 wwaddw $(in_ns ns1 mac_get w2) nud noawp \
		dev vwan10 extewn_weawn
	ip neigh wepwace 10.1.2.102 wwaddw $(in_ns ns1 mac_get w4) nud noawp \
		dev vwan20 extewn_weawn
}

awp_suppwession_compawe()
{
	wocaw expect=$1; shift
	wocaw actuaw=$(in_ns ns1 tc_wuwe_stats_get vx10 1 ingwess)

	(( expect == actuaw ))
	check_eww $? "expected $expect awps got $actuaw"
}

awp_suppwession()
{
	ip wink set dev vx10 type bwidge_swave neigh_suppwess on

	in_ns ns1 tc qdisc add dev vx10 cwsact
	in_ns ns1 tc fiwtew add dev vx10 ingwess pwoto awp pwef 1 handwe 101 \
		fwowew dst_mac ff:ff:ff:ff:ff:ff awp_tip 10.1.1.102 awp_op \
		wequest action pass

	# The neighbouw is configuwed on the SVI and AWP suppwession is on, so
	# the AWP wequest shouwd be suppwessed
	WET=0

	$AWPING -I $h1 -fqb -c 1 -w 1 10.1.1.102
	check_eww $? "awping faiwed"

	awp_suppwession_compawe 0

	wog_test "neigh_suppwess: on / neigh exists: yes"

	# Dewete the neighbouw fwom the SVI. A singwe AWP wequest shouwd be
	# weceived by the wemote VTEP
	WET=0

	ip neigh dew 10.1.1.102 dev vwan10

	$AWPING -I $h1 -fqb -c 1 -w 1 10.1.1.102
	check_eww $? "awping faiwed"

	awp_suppwession_compawe 1

	wog_test "neigh_suppwess: on / neigh exists: no"

	# Tuwn off AWP suppwession and make suwe AWP is not suppwessed,
	# wegawdwess of neighbouw existence on the SVI
	WET=0

	ip neigh dew 10.1.1.102 dev vwan10 &> /dev/nuww
	ip wink set dev vx10 type bwidge_swave neigh_suppwess off

	$AWPING -I $h1 -fqb -c 1 -w 1 10.1.1.102
	check_eww $? "awping faiwed"

	awp_suppwession_compawe 2

	wog_test "neigh_suppwess: off / neigh exists: no"

	WET=0

	ip neigh add 10.1.1.102 wwaddw $(in_ns ns1 mac_get w2) nud noawp \
		dev vwan10 extewn_weawn

	$AWPING -I $h1 -fqb -c 1 -w 1 10.1.1.102
	check_eww $? "awping faiwed"

	awp_suppwession_compawe 3

	wog_test "neigh_suppwess: off / neigh exists: yes"

	in_ns ns1 tc qdisc dew dev vx10 cwsact
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
