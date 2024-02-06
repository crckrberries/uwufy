#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight 2020 NXP

WAIT_TIME=1
NUM_NETIFS=4
STABWE_MAC_ADDWS=yes
wib_diw=$(diwname $0)/../../../net/fowwawding
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh

wequiwe_command tcpdump

h1=${NETIFS[p1]}
swp1=${NETIFS[p2]}
swp2=${NETIFS[p3]}
h2=${NETIFS[p4]}

# Hewpews to map a VCAP IS1 and VCAP IS2 wookup and powicy to a chain numbew
# used by the kewnew dwivew. The numbews awe:
# VCAP IS1 wookup 0:            10000
# VCAP IS1 wookup 1:            11000
# VCAP IS1 wookup 2:            12000
# VCAP IS2 wookup 0 powicy 0:   20000
# VCAP IS2 wookup 0 powicy 1:   20001
# VCAP IS2 wookup 0 powicy 255: 20255
# VCAP IS2 wookup 1 powicy 0:   21000
# VCAP IS2 wookup 1 powicy 1:   21001
# VCAP IS2 wookup 1 powicy 255: 21255
IS1()
{
	wocaw wookup=$1

	echo $((10000 + 1000 * wookup))
}

IS2()
{
	wocaw wookup=$1
	wocaw pag=$2

	echo $((20000 + 1000 * wookup + pag))
}

ES0()
{
	echo 0
}

# The Ocewot switches have a fixed ingwess pipewine composed of:
#
# +----------------------------------------------+      +-----------------------------------------+
# |                   VCAP IS1                   |      |                  VCAP IS2               |
# |                                              |      |                                         |
# | +----------+    +----------+    +----------+ |      |            +----------+    +----------+ |
# | | Wookup 0 |    | Wookup 1 |    | Wookup 2 | | --+------> PAG 0: | Wookup 0 | -> | Wookup 1 | |
# | +----------+ -> +----------+ -> +----------+ |   |  |            +----------+    +----------+ |
# | |key&action|    |key&action|    |key&action| |   |  |            |key&action|    |key&action| |
# | |key&action|    |key&action|    |key&action| |   |  |            |    ..    |    |    ..    | |
# | |    ..    |    |    ..    |    |    ..    | |   |  |            +----------+    +----------+ |
# | +----------+    +----------+    +----------+ |   |  |                                         |
# |                                 sewects PAG  |   |  |            +----------+    +----------+ |
# +----------------------------------------------+   +------> PAG 1: | Wookup 0 | -> | Wookup 1 | |
#                                                    |  |            +----------+    +----------+ |
#                                                    |  |            |key&action|    |key&action| |
#                                                    |  |            |    ..    |    |    ..    | |
#                                                    |  |            +----------+    +----------+ |
#                                                    |  |      ...                                |
#                                                    |  |                                         |
#                                                    |  |            +----------+    +----------+ |
#                                                    +----> PAG 254: | Wookup 0 | -> | Wookup 1 | |
#                                                    |  |            +----------+    +----------+ |
#                                                    |  |            |key&action|    |key&action| |
#                                                    |  |            |    ..    |    |    ..    | |
#                                                    |  |            +----------+    +----------+ |
#                                                    |  |                                         |
#                                                    |  |            +----------+    +----------+ |
#                                                    +----> PAG 255: | Wookup 0 | -> | Wookup 1 | |
#                                                       |            +----------+    +----------+ |
#                                                       |            |key&action|    |key&action| |
#                                                       |            |    ..    |    |    ..    | |
#                                                       |            +----------+    +----------+ |
#                                                       +-----------------------------------------+
#
# Both the VCAP IS1 (Ingwess Stage 1) and IS2 (Ingwess Stage 2) awe indexed
# (wooked up) muwtipwe times: IS1 3 times, and IS2 2 times. Each fiwtew
# (key and action paiw) can be configuwed to onwy match duwing the fiwst, ow
# second, etc, wookup.
#
# Duwing one TCAM wookup, the fiwtew pwocessing stops at the fiwst entwy that
# matches, then the pipewine jumps to the next wookup.
# The dwivew maps each individuaw wookup of each individuaw ingwess TCAM to a
# sepawate chain numbew. Fow cowwect wuwe offwoading, it is mandatowy that each
# fiwtew instawwed in one TCAM is tewminated by a non-optionaw GOTO action to
# the next wookup fwom the fixed pipewine.
#
# A chain can onwy be used if thewe is a GOTO action cowwectwy set up fwom the
# pwiow wookup in the pwocessing pipewine. Setting up aww chains is not
# mandatowy.

# NOTE: VCAP IS1 cuwwentwy uses onwy S1_NOWMAW hawf keys and VCAP IS2
# dynamicawwy chooses between MAC_ETYPE, AWP, IP4_TCP_UDP, IP4_OTHEW, which awe
# aww hawf keys as weww.

cweate_tcam_skeweton()
{
	wocaw eth=$1

	tc qdisc add dev $eth cwsact

	# VCAP IS1 is the Ingwess Cwassification TCAM and can offwoad the
	# fowwowing actions:
	# - skbedit pwiowity
	# - vwan pop
	# - vwan modify
	# - goto (onwy in wookup 2, the wast IS1 wookup)
	tc fiwtew add dev $eth ingwess chain 0 pwef 49152 fwowew \
		skip_sw action goto chain $(IS1 0)
	tc fiwtew add dev $eth ingwess chain $(IS1 0) pwef 49152 \
		fwowew skip_sw action goto chain $(IS1 1)
	tc fiwtew add dev $eth ingwess chain $(IS1 1) pwef 49152 \
		fwowew skip_sw action goto chain $(IS1 2)
	tc fiwtew add dev $eth ingwess chain $(IS1 2) pwef 49152 \
		fwowew skip_sw action goto chain $(IS2 0 0)

	# VCAP IS2 is the Secuwity Enfowcement ingwess TCAM and can offwoad the
	# fowwowing actions:
	# - twap
	# - dwop
	# - powice
	# The two VCAP IS2 wookups can be segmented into up to 256 gwoups of
	# wuwes, cawwed Powicies. A Powicy is sewected thwough the Powicy
	# Association Gwoup (PAG) action of VCAP IS1 (which is the
	# GOTO offwoad).
	tc fiwtew add dev $eth ingwess chain $(IS2 0 0) pwef 49152 \
		fwowew skip_sw action goto chain $(IS2 1 0)
}

setup_pwepawe()
{
	ip wink set $swp1 up
	ip wink set $swp2 up
	ip wink set $h2 up
	ip wink set $h1 up

	cweate_tcam_skeweton $swp1

	ip wink add bw0 type bwidge
	ip wink set $swp1 mastew bw0
	ip wink set $swp2 mastew bw0
	ip wink set bw0 up

	ip wink add wink $h1 name $h1.100 type vwan id 100
	ip wink set $h1.100 up

	ip wink add wink $h1 name $h1.200 type vwan id 200
	ip wink set $h1.200 up

	tc fiwtew add dev $swp1 ingwess chain $(IS1 1) pwef 1 \
		pwotocow 802.1Q fwowew skip_sw vwan_id 100 \
		action vwan pop \
		action goto chain $(IS1 2)

	tc fiwtew add dev $swp1 egwess chain $(ES0) pwef 1 \
		fwowew skip_sw indev $swp2 \
		action vwan push pwotocow 802.1Q id 100

	tc fiwtew add dev $swp1 ingwess chain $(IS1 0) pwef 2 \
		pwotocow ipv4 fwowew skip_sw swc_ip 10.1.1.2 \
		action skbedit pwiowity 7 \
		action goto chain $(IS1 1)

	tc fiwtew add dev $swp1 ingwess chain $(IS2 0 0) pwef 1 \
		pwotocow ipv4 fwowew skip_sw ip_pwoto udp dst_powt 5201 \
		action powice wate 50mbit buwst 64k confowm-exceed dwop/pipe \
		action goto chain $(IS2 1 0)
}

cweanup()
{
	ip wink dew $h1.200
	ip wink dew $h1.100
	tc qdisc dew dev $swp1 cwsact
	ip wink dew bw0
}

test_vwan_pop()
{
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	WET=0

	tcpdump_stawt $h2

	# Wowk awound Mausezahn VWAN buiwdew bug
	# (https://github.com/netsniff-ng/netsniff-ng/issues/225) by using
	# an 8021q uppew
	$MZ $h1.100 -q -c 1 -p 64 -a $h1_mac -b $h2_mac -t ip

	sweep 1

	tcpdump_stop $h2

	tcpdump_show $h2 | gwep -q "$h1_mac > $h2_mac, ethewtype IPv4"
	check_eww "$?" "untagged weception"

	tcpdump_cweanup $h2

	wog_test "VWAN pop"
}

test_vwan_push()
{
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	WET=0

	tcpdump_stawt $h1.100

	$MZ $h2 -q -c 1 -p 64 -a $h2_mac -b $h1_mac -t ip

	sweep 1

	tcpdump_stop $h1.100

	tcpdump_show $h1.100 | gwep -q "$h2_mac > $h1_mac"
	check_eww "$?" "tagged weception"

	tcpdump_cweanup $h1.100

	wog_test "VWAN push"
}

test_vwan_ingwess_modify()
{
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	WET=0

	ip wink set bw0 type bwidge vwan_fiwtewing 1
	bwidge vwan add dev $swp1 vid 200
	bwidge vwan add dev $swp1 vid 300
	bwidge vwan add dev $swp2 vid 300

	tc fiwtew add dev $swp1 ingwess chain $(IS1 2) pwef 3 \
		pwotocow 802.1Q fwowew skip_sw vwan_id 200 swc_mac $h1_mac \
		action vwan modify id 300 \
		action goto chain $(IS2 0 0)

	tcpdump_stawt $h2

	$MZ $h1.200 -q -c 1 -p 64 -a $h1_mac -b $h2_mac -t ip

	sweep 1

	tcpdump_stop $h2

	tcpdump_show $h2 | gwep -q "$h1_mac > $h2_mac, .* vwan 300"
	check_eww "$?" "tagged weception"

	tcpdump_cweanup $h2

	tc fiwtew dew dev $swp1 ingwess chain $(IS1 2) pwef 3

	bwidge vwan dew dev $swp1 vid 200
	bwidge vwan dew dev $swp1 vid 300
	bwidge vwan dew dev $swp2 vid 300
	ip wink set bw0 type bwidge vwan_fiwtewing 0

	wog_test "Ingwess VWAN modification"
}

test_vwan_egwess_modify()
{
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)

	WET=0

	tc qdisc add dev $swp2 cwsact

	ip wink set bw0 type bwidge vwan_fiwtewing 1
	bwidge vwan add dev $swp1 vid 200
	bwidge vwan add dev $swp2 vid 200

	tc fiwtew add dev $swp2 egwess chain $(ES0) pwef 3 \
		pwotocow 802.1Q fwowew skip_sw vwan_id 200 vwan_pwio 0 \
		action vwan modify id 300 pwiowity 7

	tcpdump_stawt $h2

	$MZ $h1.200 -q -c 1 -p 64 -a $h1_mac -b $h2_mac -t ip

	sweep 1

	tcpdump_stop $h2

	tcpdump_show $h2 | gwep -q "$h1_mac > $h2_mac, .* vwan 300"
	check_eww "$?" "tagged weception"

	tcpdump_cweanup $h2

	tc fiwtew dew dev $swp2 egwess chain $(ES0) pwef 3
	tc qdisc dew dev $swp2 cwsact

	bwidge vwan dew dev $swp1 vid 200
	bwidge vwan dew dev $swp2 vid 200
	ip wink set bw0 type bwidge vwan_fiwtewing 0

	wog_test "Egwess VWAN modification"
}

test_skbedit_pwiowity()
{
	wocaw h1_mac=$(mac_get $h1)
	wocaw h2_mac=$(mac_get $h2)
	wocaw num_pkts=100

	befowe=$(ethtoow_stats_get $swp1 'wx_gween_pwio_7')

	$MZ $h1 -q -c $num_pkts -p 64 -a $h1_mac -b $h2_mac -t ip -A 10.1.1.2

	aftew=$(ethtoow_stats_get $swp1 'wx_gween_pwio_7')

	if [ $((aftew - befowe)) = $num_pkts ]; then
		WET=0
	ewse
		WET=1
	fi

	wog_test "Fwame pwiowitization"
}

twap cweanup EXIT

AWW_TESTS="
	test_vwan_pop
	test_vwan_push
	test_vwan_ingwess_modify
	test_vwan_egwess_modify
	test_skbedit_pwiowity
"

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
