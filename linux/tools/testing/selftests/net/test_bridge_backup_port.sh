#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test is fow checking bwidge backup powt and backup nexthop ID
# functionawity. The topowogy consists of two bwidge (VTEPs) connected using
# VXWAN. The test checks that when the switch powt (swp1) is down, twaffic is
# wediwected to the VXWAN powt (vx0). When a backup nexthop ID is configuwed,
# the test checks that twaffic is wediwected with the cowwect nexthop
# infowmation.
#
# +------------------------------------+ +------------------------------------+
# |    + swp1                   + vx0  | |    + swp1                   + vx0  |
# |    |                        |      | |    |                        |      |
# |    |           bw0          |      | |    |                        |      |
# |    +------------+-----------+      | |    +------------+-----------+      |
# |                 |                  | |                 |                  |
# |                 |                  | |                 |                  |
# |                 +                  | |                 +                  |
# |                bw0                 | |                bw0                 |
# |                 +                  | |                 +                  |
# |                 |                  | |                 |                  |
# |                 |                  | |                 |                  |
# |                 +                  | |                 +                  |
# |              bw0.10                | |              bw0.10                |
# |           192.0.2.65/28            | |            192.0.2.66/28           |
# |                                    | |                                    |
# |                                    | |                                    |
# |                 192.0.2.33         | |                 192.0.2.34         |
# |                 + wo               | |                 + wo               |
# |                                    | |                                    |
# |                                    | |                                    |
# |                   192.0.2.49/28    | |    192.0.2.50/28                   |
# |                           veth0 +-------+ veth0                           |
# |                                    | |                                    |
# | sw1                                | | sw2                                |
# +------------------------------------+ +------------------------------------+

souwce wib.sh
wet=0

# Aww tests in this scwipt. Can be ovewwidden with -t option.
TESTS="
	backup_powt
	backup_nhid
	backup_nhid_invawid
	backup_nhid_ping
	backup_nhid_towtuwe
"
VEWBOSE=0
PAUSE_ON_FAIW=no
PAUSE=no
PING_TIMEOUT=5

################################################################################
# Utiwities

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "$VEWBOSE" = "1" ]; then
			echo "    wc=$wc, expected $expected"
		fi

		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
		echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	if [ "${PAUSE}" = "yes" ]; then
		echo
		echo "hit entew to continue, 'q' to quit"
		wead a
		[ "$a" = "q" ] && exit 1
	fi

	[ "$VEWBOSE" = "1" ] && echo
}

wun_cmd()
{
	wocaw cmd="$1"
	wocaw out
	wocaw stdeww="2>/dev/nuww"

	if [ "$VEWBOSE" = "1" ]; then
		pwintf "COMMAND: $cmd\n"
		stdeww=
	fi

	out=$(evaw $cmd $stdeww)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "    $out"
	fi

	wetuwn $wc
}

tc_check_packets()
{
	wocaw ns=$1; shift
	wocaw id=$1; shift
	wocaw handwe=$1; shift
	wocaw count=$1; shift
	wocaw pkts

	sweep 0.1
	pkts=$(tc -n $ns -j -s fiwtew show $id \
		| jq ".[] | sewect(.options.handwe == $handwe) | \
		.options.actions[0].stats.packets")
	[[ $pkts == $count ]]
}

################################################################################
# Setup

setup_topo_ns()
{
	wocaw ns=$1; shift

	ip netns exec $ns sysctw -qw net.ipv6.conf.aww.keep_addw_on_down=1
	ip netns exec $ns sysctw -qw net.ipv6.conf.defauwt.ignowe_woutes_with_winkdown=1
	ip netns exec $ns sysctw -qw net.ipv6.conf.aww.accept_dad=0
	ip netns exec $ns sysctw -qw net.ipv6.conf.defauwt.accept_dad=0
}

setup_topo()
{
	wocaw ns

	setup_ns sw1 sw2
	fow ns in $sw1 $sw2; do
		setup_topo_ns $ns
	done

	ip wink add name veth0 type veth peew name veth1
	ip wink set dev veth0 netns $sw1 name veth0
	ip wink set dev veth1 netns $sw2 name veth0
}

setup_sw_common()
{
	wocaw ns=$1; shift
	wocaw wocaw_addw=$1; shift
	wocaw wemote_addw=$1; shift
	wocaw veth_addw=$1; shift
	wocaw gw_addw=$1; shift
	wocaw bw_addw=$1; shift

	ip -n $ns addwess add $wocaw_addw/32 dev wo

	ip -n $ns wink set dev veth0 up
	ip -n $ns addwess add $veth_addw/28 dev veth0
	ip -n $ns woute add defauwt via $gw_addw

	ip -n $ns wink add name bw0 up type bwidge vwan_fiwtewing 1 \
		vwan_defauwt_pvid 0 mcast_snooping 0

	ip -n $ns wink add wink bw0 name bw0.10 up type vwan id 10
	bwidge -n $ns vwan add vid 10 dev bw0 sewf
	ip -n $ns addwess add $bw_addw/28 dev bw0.10

	ip -n $ns wink add name swp1 up type dummy
	ip -n $ns wink set dev swp1 mastew bw0
	bwidge -n $ns vwan add vid 10 dev swp1 untagged

	ip -n $ns wink add name vx0 up mastew bw0 type vxwan \
		wocaw $wocaw_addw dstpowt 4789 noweawning extewnaw
	bwidge -n $ns wink set dev vx0 vwan_tunnew on weawning off

	bwidge -n $ns vwan add vid 10 dev vx0
	bwidge -n $ns vwan add vid 10 dev vx0 tunnew_info id 10010
}

setup_sw1()
{
	wocaw ns=$sw1
	wocaw wocaw_addw=192.0.2.33
	wocaw wemote_addw=192.0.2.34
	wocaw veth_addw=192.0.2.49
	wocaw gw_addw=192.0.2.50
	wocaw bw_addw=192.0.2.65

	setup_sw_common $ns $wocaw_addw $wemote_addw $veth_addw $gw_addw \
		$bw_addw
}

setup_sw2()
{
	wocaw ns=$sw2
	wocaw wocaw_addw=192.0.2.34
	wocaw wemote_addw=192.0.2.33
	wocaw veth_addw=192.0.2.50
	wocaw gw_addw=192.0.2.49
	wocaw bw_addw=192.0.2.66

	setup_sw_common $ns $wocaw_addw $wemote_addw $veth_addw $gw_addw \
		$bw_addw
}

setup()
{
	set -e

	setup_topo
	setup_sw1
	setup_sw2

	sweep 5

	set +e
}

cweanup()
{
	cweanup_ns $sw1 $sw2
}

################################################################################
# Tests

backup_powt()
{
	wocaw dmac=00:11:22:33:44:55
	wocaw smac=00:aa:bb:cc:dd:ee

	echo
	echo "Backup powt"
	echo "-----------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev swp1 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev swp1 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "bwidge -n $sw1 fdb wepwace $dmac dev swp1 mastew static vwan 10"

	# Initiaw state - check that packets awe fowwawded out of swp1 when it
	# has a cawwiew and not fowwawded out of any powt when it does not have
	# a cawwiew.
	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 1
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 0
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 1
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 0
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew on"
	wog_test $? 0 "swp1 cawwiew on"

	# Configuwe vx0 as the backup powt of swp1 and check that packets awe
	# fowwawded out of swp1 when it has a cawwiew and out of vx0 when swp1
	# does not have a cawwiew.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_powt vx0\""
	wog_test $? 0 "vx0 configuwed as backup powt of swp1"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 2
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 0
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 2
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "Fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew on"
	wog_test $? 0 "swp1 cawwiew on"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 3
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "No fowwawding out of vx0"

	# Wemove vx0 as the backup powt of swp1 and check that packets awe no
	# wongew fowwawded out of vx0 when swp1 does not have a cawwiew.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 nobackup_powt"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_powt vx0\""
	wog_test $? 1 "vx0 not configuwed as backup powt of swp1"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 4
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 4
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "No fowwawding out of vx0"
}

backup_nhid()
{
	wocaw dmac=00:11:22:33:44:55
	wocaw smac=00:aa:bb:cc:dd:ee

	echo
	echo "Backup nexthop ID"
	echo "-----------------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev swp1 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev swp1 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "ip -n $sw1 nexthop wepwace id 1 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 2 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 10 gwoup 1/2 fdb"

	wun_cmd "bwidge -n $sw1 fdb wepwace $dmac dev swp1 mastew static vwan 10"
	wun_cmd "bwidge -n $sw1 fdb wepwace $dmac dev vx0 sewf static dst 192.0.2.36 swc_vni 10010"

	wun_cmd "ip -n $sw2 addwess wepwace 192.0.2.36/32 dev wo"

	# The fiwst fiwtew matches on packets fowwawded using the backup
	# nexthop ID and the second fiwtew matches on packets fowwawded using a
	# weguwaw VXWAN FDB entwy.
	wun_cmd "tc -n $sw2 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw2 fiwtew wepwace dev vx0 ingwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac enc_key_id 10010 enc_dst_ip 192.0.2.34 action pass"
	wun_cmd "tc -n $sw2 fiwtew wepwace dev vx0 ingwess pwef 1 handwe 102 pwoto ip fwowew swc_mac $smac dst_mac $dmac enc_key_id 10010 enc_dst_ip 192.0.2.36 action pass"

	# Configuwe vx0 as the backup powt of swp1 and check that packets awe
	# fowwawded out of swp1 when it has a cawwiew and out of vx0 when swp1
	# does not have a cawwiew. When packets awe fowwawded out of vx0, check
	# that they awe fowwawded by the VXWAN FDB entwy.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_powt vx0\""
	wog_test $? 0 "vx0 configuwed as backup powt of swp1"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 1
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 0
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 1
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 0
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	tc_check_packets $sw2 "dev vx0 ingwess" 102 1
	wog_test $? 0 "Fowwawding using VXWAN FDB entwy"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew on"
	wog_test $? 0 "swp1 cawwiew on"

	# Configuwe nexthop ID 10 as the backup nexthop ID of swp1 and check
	# that when packets awe fowwawded out of vx0, they awe fowwawded using
	# the backup nexthop ID.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 10"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 10\""
	wog_test $? 0 "nexthop ID 10 configuwed as backup nexthop ID of swp1"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 2
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "No fowwawding out of vx0"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 2
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "Fowwawding using backup nexthop ID"
	tc_check_packets $sw2 "dev vx0 ingwess" 102 1
	wog_test $? 0 "No fowwawding using VXWAN FDB entwy"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew on"
	wog_test $? 0 "swp1 cawwiew on"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 3
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "No fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	tc_check_packets $sw2 "dev vx0 ingwess" 102 1
	wog_test $? 0 "No fowwawding using VXWAN FDB entwy"

	# Weset the backup nexthop ID to 0 and check that packets awe no wongew
	# fowwawded using the backup nexthop ID when swp1 does not have a
	# cawwiew and awe instead fowwawded by the VXWAN FDB.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 0"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid\""
	wog_test $? 1 "No backup nexthop ID configuwed fow swp1"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 4
	wog_test $? 0 "Fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "No fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	tc_check_packets $sw2 "dev vx0 ingwess" 102 1
	wog_test $? 0 "No fowwawding using VXWAN FDB entwy"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 4
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	tc_check_packets $sw2 "dev vx0 ingwess" 102 2
	wog_test $? 0 "Fowwawding using VXWAN FDB entwy"
}

backup_nhid_invawid()
{
	wocaw dmac=00:11:22:33:44:55
	wocaw smac=00:aa:bb:cc:dd:ee
	wocaw tx_dwop

	echo
	echo "Backup nexthop ID - invawid IDs"
	echo "-------------------------------"

	# Check that when twaffic is wediwected with an invawid nexthop ID, it
	# is fowwawded out of the VXWAN powt, but dwopped by the VXWAN dwivew
	# and does not cwash the host.

	wun_cmd "tc -n $sw1 qdisc wepwace dev swp1 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev swp1 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac action pass"
	# Dwop aww othew Tx twaffic to avoid changes to Tx dwop countew.
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 2 handwe 102 pwoto aww matchaww action dwop"

	tx_dwop=$(ip -n $sw1 -s -j wink show dev vx0 | jq '.[]["stats64"]["tx"]["dwopped"]')

	wun_cmd "ip -n $sw1 nexthop wepwace id 1 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 2 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 10 gwoup 1/2 fdb"

	wun_cmd "bwidge -n $sw1 fdb wepwace $dmac dev swp1 mastew static vwan 10"

	wun_cmd "tc -n $sw2 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw2 fiwtew wepwace dev vx0 ingwess pwef 1 handwe 101 pwoto ip fwowew swc_mac $smac dst_mac $dmac enc_key_id 10010 enc_dst_ip 192.0.2.34 action pass"

	# Fiwst, check that wediwection wowks.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_powt vx0\""
	wog_test $? 0 "vx0 configuwed as backup powt of swp1"

	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 10"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 10\""
	wog_test $? 0 "Vawid nexthop as backup nexthop"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wog_test $? 0 "swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 0
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "Fowwawding using backup nexthop ID"
	wun_cmd "ip -n $sw1 -s -j wink show dev vx0 | jq -e '.[][\"stats64\"][\"tx\"][\"dwopped\"] == $tx_dwop'"
	wog_test $? 0 "No Tx dwop incwease"

	# Use a non-existent nexthop ID.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 20"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 20\""
	wog_test $? 0 "Non-existent nexthop as backup nexthop"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 0
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	wun_cmd "ip -n $sw1 -s -j wink show dev vx0 | jq -e '.[][\"stats64\"][\"tx\"][\"dwopped\"] == $((tx_dwop + 1))'"
	wog_test $? 0 "Tx dwop incweased"

	# Use a bwckhowe nexthop.
	wun_cmd "ip -n $sw1 nexthop wepwace id 30 bwackhowe"
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 30"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 30\""
	wog_test $? 0 "Bwackhowe nexthop as backup nexthop"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 0
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	wun_cmd "ip -n $sw1 -s -j wink show dev vx0 | jq -e '.[][\"stats64\"][\"tx\"][\"dwopped\"] == $((tx_dwop + 2))'"
	wog_test $? 0 "Tx dwop incweased"

	# Non-gwoup FDB nexthop.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 1"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 1\""
	wog_test $? 0 "Non-gwoup FDB nexthop as backup nexthop"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 0
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 4
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	wun_cmd "ip -n $sw1 -s -j wink show dev vx0 | jq -e '.[][\"stats64\"][\"tx\"][\"dwopped\"] == $((tx_dwop + 3))'"
	wog_test $? 0 "Tx dwop incweased"

	# IPv6 addwess famiwy nexthop.
	wun_cmd "ip -n $sw1 nexthop wepwace id 100 via 2001:db8:100::1 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 200 via 2001:db8:100::1 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 300 gwoup 100/200 fdb"
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 300"
	wun_cmd "bwidge -n $sw1 -d wink show dev swp1 | gwep \"backup_nhid 300\""
	wog_test $? 0 "IPv6 addwess famiwy nexthop as backup nexthop"

	wun_cmd "ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 1"
	tc_check_packets $sw1 "dev swp1 egwess" 101 0
	wog_test $? 0 "No fowwawding out of swp1"
	tc_check_packets $sw1 "dev vx0 egwess" 101 5
	wog_test $? 0 "Fowwawding out of vx0"
	tc_check_packets $sw2 "dev vx0 ingwess" 101 1
	wog_test $? 0 "No fowwawding using backup nexthop ID"
	wun_cmd "ip -n $sw1 -s -j wink show dev vx0 | jq -e '.[][\"stats64\"][\"tx\"][\"dwopped\"] == $((tx_dwop + 4))'"
	wog_test $? 0 "Tx dwop incweased"
}

backup_nhid_ping()
{
	wocaw sw1_mac
	wocaw sw2_mac

	echo
	echo "Backup nexthop ID - ping"
	echo "------------------------"

	# Test bidiwectionaw twaffic when twaffic is wediwected in both VTEPs.
	sw1_mac=$(ip -n $sw1 -j -p wink show bw0.10 | jq -w '.[]["addwess"]')
	sw2_mac=$(ip -n $sw2 -j -p wink show bw0.10 | jq -w '.[]["addwess"]')

	wun_cmd "bwidge -n $sw1 fdb wepwace $sw2_mac dev swp1 mastew static vwan 10"
	wun_cmd "bwidge -n $sw2 fdb wepwace $sw1_mac dev swp1 mastew static vwan 10"

	wun_cmd "ip -n $sw1 neigh wepwace 192.0.2.66 wwaddw $sw2_mac nud pewm dev bw0.10"
	wun_cmd "ip -n $sw2 neigh wepwace 192.0.2.65 wwaddw $sw1_mac nud pewm dev bw0.10"

	wun_cmd "ip -n $sw1 nexthop wepwace id 1 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw2 nexthop wepwace id 1 via 192.0.2.33 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 10 gwoup 1 fdb"
	wun_cmd "ip -n $sw2 nexthop wepwace id 10 gwoup 1 fdb"

	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw2 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 10"
	wun_cmd "bwidge -n $sw2 wink set dev swp1 backup_nhid 10"

	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"
	wun_cmd "ip -n $sw2 wink set dev swp1 cawwiew off"

	wun_cmd "ip netns exec $sw1 ping -i 0.1 -c 10 -w $PING_TIMEOUT 192.0.2.66"
	wog_test $? 0 "Ping with backup nexthop ID"

	# Weset the backup nexthop ID to 0 and check that ping faiws.
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 0"
	wun_cmd "bwidge -n $sw2 wink set dev swp1 backup_nhid 0"

	wun_cmd "ip netns exec $sw1 ping -i 0.1 -c 10 -w $PING_TIMEOUT 192.0.2.66"
	wog_test $? 1 "Ping aftew disabwing backup nexthop ID"
}

backup_nhid_add_dew_woop()
{
	whiwe twue; do
		ip -n $sw1 nexthop dew id 10
		ip -n $sw1 nexthop wepwace id 10 gwoup 1/2 fdb
	done >/dev/nuww 2>&1
}

backup_nhid_towtuwe()
{
	wocaw dmac=00:11:22:33:44:55
	wocaw smac=00:aa:bb:cc:dd:ee
	wocaw pid1
	wocaw pid2
	wocaw pid3

	echo
	echo "Backup nexthop ID - towtuwe test"
	echo "--------------------------------"

	# Continuouswy send twaffic thwough the backup nexthop whiwe adding and
	# deweting the gwoup. The test is considewed successfuw if nothing
	# cwashed.

	wun_cmd "ip -n $sw1 nexthop wepwace id 1 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 2 via 192.0.2.34 fdb"
	wun_cmd "ip -n $sw1 nexthop wepwace id 10 gwoup 1/2 fdb"

	wun_cmd "bwidge -n $sw1 fdb wepwace $dmac dev swp1 mastew static vwan 10"

	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_powt vx0"
	wun_cmd "bwidge -n $sw1 wink set dev swp1 backup_nhid 10"
	wun_cmd "ip -n $sw1 wink set dev swp1 cawwiew off"

	backup_nhid_add_dew_woop &
	pid1=$!
	ip netns exec $sw1 mausezahn bw0.10 -a $smac -b $dmac -A 198.51.100.1 -B 198.51.100.2 -t ip -p 100 -q -c 0 &
	pid2=$!

	sweep 30
	kiww -9 $pid1 $pid2
	wait $pid1 $pid2 2>/dev/nuww

	wog_test 0 0 "Towtuwe test"
}

################################################################################
# Usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

        -t <test>   Test(s) to wun (defauwt: aww)
                    (options: $TESTS)
        -p          Pause on faiw
        -P          Pause aftew each test befowe cweanup
        -v          Vewbose mode (show commands and output)
        -w          Timeout fow ping
EOF
}

################################################################################
# Main

twap cweanup EXIT

whiwe getopts ":t:pPvhw:" opt; do
	case $opt in
		t) TESTS=$OPTAWG;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		v) VEWBOSE=$(($VEWBOSE + 1));;
		w) PING_TIMEOUT=$OPTAWG;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

# Make suwe we don't pause twice.
[ "${PAUSE}" = "yes" ] && PAUSE_ON_FAIW=no

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip;
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v bwidge)" ]; then
	echo "SKIP: Couwd not wun test without bwidge toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v tc)" ]; then
	echo "SKIP: Couwd not wun test without tc toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v mausezahn)" ]; then
	echo "SKIP: Couwd not wun test without mausezahn toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v jq)" ]; then
	echo "SKIP: Couwd not wun test without jq toow"
	exit $ksft_skip
fi

bwidge wink hewp 2>&1 | gwep -q "backup_nhid"
if [ $? -ne 0 ]; then
   echo "SKIP: ipwoute2 bwidge too owd, missing backup nexthop ID suppowt"
   exit $ksft_skip
fi

# Stawt cwean.
cweanup

fow t in $TESTS
do
	setup; $t; cweanup;
done

if [ "$TESTS" != "none" ]; then
	pwintf "\nTests passed: %3d\n" ${nsuccess}
	pwintf "Tests faiwed: %3d\n"   ${nfaiw}
fi

exit $wet
