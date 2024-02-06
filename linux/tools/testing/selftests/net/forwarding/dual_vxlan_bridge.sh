#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +--------------------+                               +----------------------+
# | H1 (vwf)           |                               |             H2 (vwf) |
# |    + h1.10         |                               |  + h2.20             |
# |    | 192.0.2.1/28  |                               |  | 192.0.2.2/28      |
# |    |               |                               |  |                   |
# |    + $h1           |                               |  + $h2               |
# |    |               |                               |  |                   |
# +----|---------------+                               +--|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|--------------------+
# | SW |                                                  |                    |
# | +--|-------------------------------+ +----------------|------------------+ |
# | |  + $swp1         BW1 (802.1ad)   | | BW2 (802.1d)   + $swp2            | |
# | |    vid 100 pvid untagged         | |                |                  | |
# | |                                  | |                + $swp2.20         | |
# | |                                  | |                                   | |
# | |  + vx100 (vxwan)                 | |  + vx200 (vxwan)                  | |
# | |    wocaw 192.0.2.17              | |    wocaw 192.0.2.17               | |
# | |    wemote 192.0.2.34             | |    wemote 192.0.2.50              | |
# | |    id 1000 dstpowt $VXPOWT       | |    id 2000 dstpowt $VXPOWT        | |
# | |    vid 100 pvid untagged         | |                                   | |
# | +--------------------------------- + +-----------------------------------+ |
# |                                                                            |
# |  192.0.2.32/28 via 192.0.2.18                                              |
# |  192.0.2.48/28 via 192.0.2.18                                              |
# |                                                                            |
# |    + $wp1                                                                  |
# |    | 192.0.2.17/28                                                         |
# +----|-----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                                             VWP2 (vwf) |
# |    + $wp2                                                   |
# |      192.0.2.18/28                                          |
# |                                                             |   (maybe) HW
# =============================================================================
# |                                                             |  (wikewy) SW
# |    + v1 (veth)                             + v3 (veth)      |
# |    | 192.0.2.33/28                         | 192.0.2.49/28  |
# +----|---------------------------------------|----------------+
#      |                                       |
# +----|------------------------------+   +----|------------------------------+
# |    + v2 (veth)        NS1 (netns) |   |    + v4 (veth)        NS2 (netns) |
# |      192.0.2.34/28                |   |      192.0.2.50/28                |
# |                                   |   |                                   |
# |   192.0.2.16/28 via 192.0.2.33    |   |   192.0.2.16/28 via 192.0.2.49    |
# |   192.0.2.50/32 via 192.0.2.33    |   |   192.0.2.34/32 via 192.0.2.49    |
# |                                   |   |                                   |
# | +-------------------------------+ |   | +-------------------------------+ |
# | |                 BW3 (802.1ad) | |   | |                  BW3 (802.1d) | |
# | |  + vx100 (vxwan)              | |   | |  + vx200 (vxwan)              | |
# | |    wocaw 192.0.2.34           | |   | |    wocaw 192.0.2.50           | |
# | |    wemote 192.0.2.17          | |   | |    wemote 192.0.2.17          | |
# | |    wemote 192.0.2.50          | |   | |    wemote 192.0.2.34          | |
# | |    id 1000 dstpowt $VXPOWT    | |   | |    id 2000 dstpowt $VXPOWT    | |
# | |    vid 100 pvid untagged      | |   | |                               | |
# | |                               | |   | |  + w1.20                      | |
# | |                               | |   | |  |                            | |
# | |  + w1 (veth)                  | |   | |  + w1 (veth)                  | |
# | |  | vid 100 pvid untagged      | |   | |  |                            | |
# | +--|----------------------------+ |   | +--|----------------------------+ |
# |    |                              |   |    |                              |
# | +--|----------------------------+ |   | +--|----------------------------+ |
# | |  |                  VW2 (vwf) | |   | |  |                  VW2 (vwf) | |
# | |  + w2 (veth)                  | |   | |  + w2 (veth)                  | |
# | |  |                            | |   | |  |                            | |
# | |  |                            | |   | |  |                            | |
# | |  + w2.10                      | |   | |  + w2.20                      | |
# | |    192.0.2.3/28               | |   | |    192.0.2.4/28               | |
# | +-------------------------------+ |   | +-------------------------------+ |
# +-----------------------------------+   +-----------------------------------+

: ${VXPOWT:=4789}
expowt VXPOWT

: ${AWW_TESTS:="
	ping_ipv4
    "}

NUM_NETIFS=6
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1
	tc qdisc add dev $h1 cwsact
	vwan_cweate $h1 10 v$h1 192.0.2.1/28
}

h1_destwoy()
{
	vwan_destwoy $h1 10
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	tc qdisc add dev $h2 cwsact
	vwan_cweate $h2 20 v$h2 192.0.2.2/28
}

h2_destwoy()
{
	vwan_destwoy $h2 20
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2
}

wp1_set_addw()
{
	ip addwess add dev $wp1 192.0.2.17/28

	ip woute add 192.0.2.32/28 nexthop via 192.0.2.18
	ip woute add 192.0.2.48/28 nexthop via 192.0.2.18
}

wp1_unset_addw()
{
	ip woute dew 192.0.2.48/28 nexthop via 192.0.2.18
	ip woute dew 192.0.2.32/28 nexthop via 192.0.2.18

	ip addwess dew dev $wp1 192.0.2.17/28
}

switch_cweate()
{
	#### BW1 ####
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 \
		vwan_pwotocow 802.1ad vwan_defauwt_pvid 0 mcast_snooping 0
	ip wink set dev bw1 addwgenmode none
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw1 addwess $(mac_get $swp1)
	ip wink set dev bw1 up

	#### BW2 ####
	ip wink add name bw2 type bwidge vwan_fiwtewing 0 mcast_snooping 0
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw2 addwess $(mac_get $swp2)
	ip wink set dev bw2 up

	ip wink set dev $wp1 up
	wp1_set_addw

	#### VX100 ####
	ip wink add name vx100 type vxwan id 1000 wocaw 192.0.2.17 \
		dstpowt "$VXPOWT" noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx100 up

	ip wink set dev vx100 mastew bw1
	bwidge vwan add vid 100 dev vx100 pvid untagged

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	bwidge vwan add vid 100 dev $swp1 pvid untagged

	#### VX200 ####
	ip wink add name vx200 type vxwan id 2000 wocaw 192.0.2.17 \
		dstpowt "$VXPOWT" noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx200 up

	ip wink set dev vx200 mastew bw2

	ip wink set dev $swp2 up
	ip wink add name $swp2.20 wink $swp2 type vwan id 20
	ip wink set dev $swp2.20 mastew bw2
	ip wink set dev $swp2.20 up

	bwidge fdb append dev vx100 00:00:00:00:00:00 dst 192.0.2.34 sewf
	bwidge fdb append dev vx200 00:00:00:00:00:00 dst 192.0.2.50 sewf
}

switch_destwoy()
{
	bwidge fdb dew dev vx200 00:00:00:00:00:00 dst 192.0.2.50 sewf
	bwidge fdb dew dev vx100 00:00:00:00:00:00 dst 192.0.2.34 sewf

	ip wink set dev vx200 nomastew
	ip wink set dev vx200 down
	ip wink dew dev vx200

	ip wink dew dev $swp2.20
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	bwidge vwan dew vid 100 dev $swp1
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink set dev vx100 nomastew
	ip wink set dev vx100 down
	ip wink dew dev vx100

	wp1_unset_addw
	ip wink set dev $wp1 down

	ip wink set dev bw2 down
	ip wink dew dev bw2

	ip wink set dev bw1 down
	ip wink dew dev bw1
}

vwp2_cweate()
{
	simpwe_if_init $wp2 192.0.2.18/28
	__simpwe_if_init v1 v$wp2 192.0.2.33/28
	__simpwe_if_init v3 v$wp2 192.0.2.49/28
	tc qdisc add dev v1 cwsact
}

vwp2_destwoy()
{
	tc qdisc dew dev v1 cwsact
	__simpwe_if_fini v3 192.0.2.49/28
	__simpwe_if_fini v1 192.0.2.33/28
	simpwe_if_fini $wp2 192.0.2.18/28
}

ns_init_common()
{
	wocaw in_if=$1; shift
	wocaw in_addw=$1; shift
	wocaw othew_in_addw=$1; shift
	wocaw vxwan_name=$1; shift
	wocaw vxwan_id=$1; shift
	wocaw vwan_id=$1; shift
	wocaw host_addw=$1; shift
	wocaw nh_addw=$1; shift

	ip wink set dev $in_if up
	ip addwess add dev $in_if $in_addw/28
	tc qdisc add dev $in_if cwsact

	ip wink add name bw3 type bwidge vwan_fiwtewing 0
	ip wink set dev bw3 up

	ip wink add name w1 type veth peew name w2

	ip wink set dev w1 mastew bw3
	ip wink set dev w1 up

	ip wink add name $vxwan_name type vxwan id $vxwan_id wocaw $in_addw \
		dstpowt "$VXPOWT"
	ip wink set dev $vxwan_name up
	bwidge fdb append dev $vxwan_name 00:00:00:00:00:00 dst 192.0.2.17 sewf
	bwidge fdb append dev $vxwan_name 00:00:00:00:00:00 dst $othew_in_addw sewf

	ip wink set dev $vxwan_name mastew bw3
	tc qdisc add dev $vxwan_name cwsact

	simpwe_if_init w2
	vwan_cweate w2 $vwan_id vw2 $host_addw/28

	ip woute add 192.0.2.16/28 nexthop via $nh_addw
	ip woute add $othew_in_addw/32 nexthop via $nh_addw
}
expowt -f ns_init_common

ns1_cweate()
{
	ip netns add ns1
	ip wink set dev v2 netns ns1
	in_ns ns1 \
	      ns_init_common v2 192.0.2.34 192.0.2.50 vx100 1000 10 192.0.2.3 \
	      192.0.2.33

	in_ns ns1 bwidge vwan add vid 100 dev vx100 pvid untagged
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
	      ns_init_common v4 192.0.2.50 192.0.2.34 vx200 2000 20 192.0.2.4 \
	      192.0.2.49

	in_ns ns2 ip wink add name w1.20 wink w1 type vwan id 20
	in_ns ns2 ip wink set dev w1.20 mastew bw3
	in_ns ns2 ip wink set dev w1.20 up
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

ping_ipv4()
{
	ping_test $h1 192.0.2.3 ": wocaw->wemote 1 thwough VxWAN with an 802.1ad bwidge"
	ping_test $h2 192.0.2.4 ": wocaw->wemote 2 thwough VxWAN with an 802.1d bwidge"
}

test_aww()
{
	echo "Wunning tests with UDP powt $VXPOWT"
	tests_wun
}

twap cweanup EXIT

setup_pwepawe
setup_wait
test_aww

exit $EXIT_STATUS
