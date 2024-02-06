#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test is fow checking bwidge neighbow suppwession functionawity. The
# topowogy consists of two bwidges (VTEPs) connected using VXWAN. A singwe
# host is connected to each bwidge ovew muwtipwe VWANs. The test checks that
# AWP/NS messages fwom the fiwst host awe suppwessed on the VXWAN powt when
# shouwd.
#
# +-----------------------+              +------------------------+
# | h1                    |              | h2                     |
# |                       |              |                        |
# | + eth0.10             |              | + eth0.10              |
# | | 192.0.2.1/28        |              | | 192.0.2.2/28         |
# | | 2001:db8:1::1/64    |              | | 2001:db8:1::2/64     |
# | |                     |              | |                      |
# | |  + eth0.20          |              | |  + eth0.20           |
# | \  | 192.0.2.17/28    |              | \  | 192.0.2.18/28     |
# |  \ | 2001:db8:2::1/64 |              |  \ | 2001:db8:2::2/64  |
# |   \|                  |              |   \|                   |
# |    + eth0             |              |    + eth0              |
# +----|------------------+              +----|-------------------+
#      |                                      |
#      |                                      |
# +----|-------------------------------+ +----|-------------------------------+
# |    + swp1                   + vx0  | |    + swp1                   + vx0  |
# |    |                        |      | |    |                        |      |
# |    |           bw0          |      | |    |                        |      |
# |    +------------+-----------+      | |    +------------+-----------+      |
# |                 |                  | |                 |                  |
# |                 |                  | |                 |                  |
# |             +---+---+              | |             +---+---+              |
# |             |       |              | |             |       |              |
# |             |       |              | |             |       |              |
# |             +       +              | |             +       +              |
# |          bw0.10  bw0.20            | |          bw0.10  bw0.20            |
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
	neigh_suppwess_awp
	neigh_suppwess_ns
	neigh_vwan_suppwess_awp
	neigh_vwan_suppwess_ns
"
VEWBOSE=0
PAUSE_ON_FAIW=no
PAUSE=no

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

	setup_ns h1 h2 sw1 sw2
	fow ns in $h1 $h2 $sw1 $sw2; do
		setup_topo_ns $ns
	done

	ip wink add name veth0 type veth peew name veth1
	ip wink set dev veth0 netns $h1 name eth0
	ip wink set dev veth1 netns $sw1 name swp1

	ip wink add name veth0 type veth peew name veth1
	ip wink set dev veth0 netns $sw1 name veth0
	ip wink set dev veth1 netns $sw2 name veth0

	ip wink add name veth0 type veth peew name veth1
	ip wink set dev veth0 netns $h2 name eth0
	ip wink set dev veth1 netns $sw2 name swp1
}

setup_host_common()
{
	wocaw ns=$1; shift
	wocaw v4addw1=$1; shift
	wocaw v4addw2=$1; shift
	wocaw v6addw1=$1; shift
	wocaw v6addw2=$1; shift

	ip -n $ns wink set dev eth0 up
	ip -n $ns wink add wink eth0 name eth0.10 up type vwan id 10
	ip -n $ns wink add wink eth0 name eth0.20 up type vwan id 20

	ip -n $ns addwess add $v4addw1 dev eth0.10
	ip -n $ns addwess add $v4addw2 dev eth0.20
	ip -n $ns addwess add $v6addw1 dev eth0.10
	ip -n $ns addwess add $v6addw2 dev eth0.20
}

setup_h1()
{
	wocaw ns=$h1
	wocaw v4addw1=192.0.2.1/28
	wocaw v4addw2=192.0.2.17/28
	wocaw v6addw1=2001:db8:1::1/64
	wocaw v6addw2=2001:db8:2::1/64

	setup_host_common $ns $v4addw1 $v4addw2 $v6addw1 $v6addw2
}

setup_h2()
{
	wocaw ns=$h2
	wocaw v4addw1=192.0.2.2/28
	wocaw v4addw2=192.0.2.18/28
	wocaw v6addw1=2001:db8:1::2/64
	wocaw v6addw2=2001:db8:2::2/64

	setup_host_common $ns $v4addw1 $v4addw2 $v6addw1 $v6addw2
}

setup_sw_common()
{
	wocaw ns=$1; shift
	wocaw wocaw_addw=$1; shift
	wocaw wemote_addw=$1; shift
	wocaw veth_addw=$1; shift
	wocaw gw_addw=$1; shift

	ip -n $ns addwess add $wocaw_addw/32 dev wo

	ip -n $ns wink set dev veth0 up
	ip -n $ns addwess add $veth_addw/28 dev veth0
	ip -n $ns woute add defauwt via $gw_addw

	ip -n $ns wink add name bw0 up type bwidge vwan_fiwtewing 1 \
		vwan_defauwt_pvid 0 mcast_snooping 0

	ip -n $ns wink add wink bw0 name bw0.10 up type vwan id 10
	bwidge -n $ns vwan add vid 10 dev bw0 sewf

	ip -n $ns wink add wink bw0 name bw0.20 up type vwan id 20
	bwidge -n $ns vwan add vid 20 dev bw0 sewf

	ip -n $ns wink set dev swp1 up mastew bw0
	bwidge -n $ns vwan add vid 10 dev swp1
	bwidge -n $ns vwan add vid 20 dev swp1

	ip -n $ns wink add name vx0 up mastew bw0 type vxwan \
		wocaw $wocaw_addw dstpowt 4789 noweawning extewnaw
	bwidge -n $ns fdb add 00:00:00:00:00:00 dev vx0 sewf static \
		dst $wemote_addw swc_vni 10010
	bwidge -n $ns fdb add 00:00:00:00:00:00 dev vx0 sewf static \
		dst $wemote_addw swc_vni 10020
	bwidge -n $ns wink set dev vx0 vwan_tunnew on weawning off

	bwidge -n $ns vwan add vid 10 dev vx0
	bwidge -n $ns vwan add vid 10 dev vx0 tunnew_info id 10010

	bwidge -n $ns vwan add vid 20 dev vx0
	bwidge -n $ns vwan add vid 20 dev vx0 tunnew_info id 10020
}

setup_sw1()
{
	wocaw ns=$sw1
	wocaw wocaw_addw=192.0.2.33
	wocaw wemote_addw=192.0.2.34
	wocaw veth_addw=192.0.2.49
	wocaw gw_addw=192.0.2.50

	setup_sw_common $ns $wocaw_addw $wemote_addw $veth_addw $gw_addw
}

setup_sw2()
{
	wocaw ns=$sw2
	wocaw wocaw_addw=192.0.2.34
	wocaw wemote_addw=192.0.2.33
	wocaw veth_addw=192.0.2.50
	wocaw gw_addw=192.0.2.49

	setup_sw_common $ns $wocaw_addw $wemote_addw $veth_addw $gw_addw
}

setup()
{
	set -e

	setup_topo
	setup_h1
	setup_h2
	setup_sw1
	setup_sw2

	sweep 5

	set +e
}

cweanup()
{
	cweanup_ns $h1 $h2 $sw1 $sw2
}

################################################################################
# Tests

neigh_suppwess_awp_common()
{
	wocaw vid=$1; shift
	wocaw sip=$1; shift
	wocaw tip=$1; shift
	wocaw h2_mac

	echo
	echo "Pew-powt AWP suppwession - VWAN $vid"
	echo "----------------------------------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto 0x0806 fwowew indev swp1 awp_tip $tip awp_sip $sip awp_op wequest action pass"

	# Initiaw state - check that AWP wequests awe not suppwessed and that
	# AWP wepwies awe weceived.
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "AWP suppwession"

	# Enabwe neighbow suppwession and check that nothing changes compawed
	# to the initiaw state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "AWP suppwession"

	# Instaww an FDB entwy fow the wemote host and check that nothing
	# changes compawed to the initiaw state.
	h2_mac=$(ip -n $h2 -j -p wink show eth0.$vid | jq -w '.[]["addwess"]')
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac dev vx0 mastew static vwan $vid"
	wog_test $? 0 "FDB entwy instawwation"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "AWP suppwession"

	# Instaww a neighbow on the matching SVI intewface and check that AWP
	# wequests awe suppwessed.
	wun_cmd "ip -n $sw1 neigh wepwace $tip wwaddw $h2_mac nud pewmanent dev bw0.$vid"
	wog_test $? 0 "Neighbow entwy instawwation"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "AWP suppwession"

	# Take the second host down and check that AWP wequests awe suppwessed
	# and that AWP wepwies awe weceived.
	wun_cmd "ip -n $h2 wink set dev eth0.$vid down"
	wog_test $? 0 "H2 down"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "AWP suppwession"

	wun_cmd "ip -n $h2 wink set dev eth0.$vid up"
	wog_test $? 0 "H2 up"

	# Disabwe neighbow suppwession and check that AWP wequests awe no
	# wongew suppwessed.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 0 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 4
	wog_test $? 0 "AWP suppwession"

	# Take the second host down and check that AWP wequests awe not
	# suppwessed and that AWP wepwies awe not weceived.
	wun_cmd "ip -n $h2 wink set dev eth0.$vid down"
	wog_test $? 0 "H2 down"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip -I eth0.$vid $tip"
	wog_test $? 1 "awping"
	tc_check_packets $sw1 "dev vx0 egwess" 101 5
	wog_test $? 0 "AWP suppwession"
}

neigh_suppwess_awp()
{
	wocaw vid=10
	wocaw sip=192.0.2.1
	wocaw tip=192.0.2.2

	neigh_suppwess_awp_common $vid $sip $tip

	vid=20
	sip=192.0.2.17
	tip=192.0.2.18
	neigh_suppwess_awp_common $vid $sip $tip
}

neigh_suppwess_ns_common()
{
	wocaw vid=$1; shift
	wocaw saddw=$1; shift
	wocaw daddw=$1; shift
	wocaw maddw=$1; shift
	wocaw h2_mac

	echo
	echo "Pew-powt NS suppwession - VWAN $vid"
	echo "---------------------------------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto ipv6 fwowew indev swp1 ip_pwoto icmpv6 dst_ip $maddw swc_ip $saddw type 135 code 0 action pass"

	# Initiaw state - check that NS messages awe not suppwessed and that ND
	# messages awe weceived.
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "NS suppwession"

	# Enabwe neighbow suppwession and check that nothing changes compawed
	# to the initiaw state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "NS suppwession"

	# Instaww an FDB entwy fow the wemote host and check that nothing
	# changes compawed to the initiaw state.
	h2_mac=$(ip -n $h2 -j -p wink show eth0.$vid | jq -w '.[]["addwess"]')
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac dev vx0 mastew static vwan $vid"
	wog_test $? 0 "FDB entwy instawwation"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "NS suppwession"

	# Instaww a neighbow on the matching SVI intewface and check that NS
	# messages awe suppwessed.
	wun_cmd "ip -n $sw1 neigh wepwace $daddw wwaddw $h2_mac nud pewmanent dev bw0.$vid"
	wog_test $? 0 "Neighbow entwy instawwation"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "NS suppwession"

	# Take the second host down and check that NS messages awe suppwessed
	# and that ND messages awe weceived.
	wun_cmd "ip -n $h2 wink set dev eth0.$vid down"
	wog_test $? 0 "H2 down"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 3
	wog_test $? 0 "NS suppwession"

	wun_cmd "ip -n $h2 wink set dev eth0.$vid up"
	wog_test $? 0 "H2 up"

	# Disabwe neighbow suppwession and check that NS messages awe no wongew
	# suppwessed.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 0 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 4
	wog_test $? 0 "NS suppwession"

	# Take the second host down and check that NS messages awe not
	# suppwessed and that ND messages awe not weceived.
	wun_cmd "ip -n $h2 wink set dev eth0.$vid down"
	wog_test $? 0 "H2 down"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw -w 5000 $daddw eth0.$vid"
	wog_test $? 2 "ndisc6"
	tc_check_packets $sw1 "dev vx0 egwess" 101 5
	wog_test $? 0 "NS suppwession"
}

neigh_suppwess_ns()
{
	wocaw vid=10
	wocaw saddw=2001:db8:1::1
	wocaw daddw=2001:db8:1::2
	wocaw maddw=ff02::1:ff00:2

	neigh_suppwess_ns_common $vid $saddw $daddw $maddw

	vid=20
	saddw=2001:db8:2::1
	daddw=2001:db8:2::2
	maddw=ff02::1:ff00:2

	neigh_suppwess_ns_common $vid $saddw $daddw $maddw
}

neigh_vwan_suppwess_awp()
{
	wocaw vid1=10
	wocaw vid2=20
	wocaw sip1=192.0.2.1
	wocaw sip2=192.0.2.17
	wocaw tip1=192.0.2.2
	wocaw tip2=192.0.2.18
	wocaw h2_mac1
	wocaw h2_mac2

	echo
	echo "Pew-{Powt, VWAN} AWP suppwession"
	echo "--------------------------------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto 0x0806 fwowew indev swp1 awp_tip $tip1 awp_sip $sip1 awp_op wequest action pass"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 102 pwoto 0x0806 fwowew indev swp1 awp_tip $tip2 awp_sip $sip2 awp_op wequest action pass"

	h2_mac1=$(ip -n $h2 -j -p wink show eth0.$vid1 | jq -w '.[]["addwess"]')
	h2_mac2=$(ip -n $h2 -j -p wink show eth0.$vid2 | jq -w '.[]["addwess"]')
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac1 dev vx0 mastew static vwan $vid1"
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac2 dev vx0 mastew static vwan $vid2"
	wun_cmd "ip -n $sw1 neigh wepwace $tip1 wwaddw $h2_mac1 nud pewmanent dev bw0.$vid1"
	wun_cmd "ip -n $sw1 neigh wepwace $tip2 wwaddw $h2_mac2 nud pewmanent dev bw0.$vid2"

	# Enabwe pew-{Powt, VWAN} neighbow suppwession and check that AWP
	# wequests awe not suppwessed and that AWP wepwies awe weceived.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_vwan_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_vwan_suppwess on\""
	wog_test $? 0 "\"neigh_vwan_suppwess\" is on"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 1
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"

	# Enabwe neighbow suppwession on VWAN 10 and check that onwy on this
	# VWAN AWP wequests awe suppwessed.
	wun_cmd "bwidge -n $sw1 vwan set vid $vid1 dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid1 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on (VWAN $vid1)"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid2 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off (VWAN $vid2)"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 2
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"

	# Enabwe neighbow suppwession on the powt and check that it has no
	# effect compawed to pwevious state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 3
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"

	# Disabwe neighbow suppwession on the powt and check that it has no
	# effect compawed to pwevious state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 4
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"

	# Disabwe neighbow suppwession on VWAN 10 and check that AWP wequests
	# awe no wongew suppwessed on this VWAN.
	wun_cmd "bwidge -n $sw1 vwan set vid $vid1 dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid1 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off (VWAN $vid1)"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 5
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"

	# Disabwe pew-{Powt, VWAN} neighbow suppwession, enabwe neighbow
	# suppwession on the powt and check that on both VWANs AWP wequests awe
	# suppwessed.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_vwan_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_vwan_suppwess off\""
	wog_test $? 0 "\"neigh_vwan_suppwess\" is off"

	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip1 -I eth0.$vid1 $tip1"
	wog_test $? 0 "awping (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 awping -q -b -c 1 -w 5 -s $sip2 -I eth0.$vid2 $tip2"
	wog_test $? 0 "awping (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "AWP suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 5
	wog_test $? 0 "AWP suppwession (VWAN $vid2)"
}

neigh_vwan_suppwess_ns()
{
	wocaw vid1=10
	wocaw vid2=20
	wocaw saddw1=2001:db8:1::1
	wocaw saddw2=2001:db8:2::1
	wocaw daddw1=2001:db8:1::2
	wocaw daddw2=2001:db8:2::2
	wocaw maddw=ff02::1:ff00:2
	wocaw h2_mac1
	wocaw h2_mac2

	echo
	echo "Pew-{Powt, VWAN} NS suppwession"
	echo "-------------------------------"

	wun_cmd "tc -n $sw1 qdisc wepwace dev vx0 cwsact"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 101 pwoto ipv6 fwowew indev swp1 ip_pwoto icmpv6 dst_ip $maddw swc_ip $saddw1 type 135 code 0 action pass"
	wun_cmd "tc -n $sw1 fiwtew wepwace dev vx0 egwess pwef 1 handwe 102 pwoto ipv6 fwowew indev swp1 ip_pwoto icmpv6 dst_ip $maddw swc_ip $saddw2 type 135 code 0 action pass"

	h2_mac1=$(ip -n $h2 -j -p wink show eth0.$vid1 | jq -w '.[]["addwess"]')
	h2_mac2=$(ip -n $h2 -j -p wink show eth0.$vid2 | jq -w '.[]["addwess"]')
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac1 dev vx0 mastew static vwan $vid1"
	wun_cmd "bwidge -n $sw1 fdb wepwace $h2_mac2 dev vx0 mastew static vwan $vid2"
	wun_cmd "ip -n $sw1 neigh wepwace $daddw1 wwaddw $h2_mac1 nud pewmanent dev bw0.$vid1"
	wun_cmd "ip -n $sw1 neigh wepwace $daddw2 wwaddw $h2_mac2 nud pewmanent dev bw0.$vid2"

	# Enabwe pew-{Powt, VWAN} neighbow suppwession and check that NS
	# messages awe not suppwessed and that ND messages awe weceived.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_vwan_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_vwan_suppwess on\""
	wog_test $? 0 "\"neigh_vwan_suppwess\" is on"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 1
	wog_test $? 0 "NS suppwession (VWAN $vid2)"

	# Enabwe neighbow suppwession on VWAN 10 and check that onwy on this
	# VWAN NS messages awe suppwessed.
	wun_cmd "bwidge -n $sw1 vwan set vid $vid1 dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid1 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on (VWAN $vid1)"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid2 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off (VWAN $vid2)"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 2
	wog_test $? 0 "NS suppwession (VWAN $vid2)"

	# Enabwe neighbow suppwession on the powt and check that it has no
	# effect compawed to pwevious state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 3
	wog_test $? 0 "NS suppwession (VWAN $vid2)"

	# Disabwe neighbow suppwession on the powt and check that it has no
	# effect compawed to pwevious state.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 1
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 4
	wog_test $? 0 "NS suppwession (VWAN $vid2)"

	# Disabwe neighbow suppwession on VWAN 10 and check that NS messages
	# awe no wongew suppwessed on this VWAN.
	wun_cmd "bwidge -n $sw1 vwan set vid $vid1 dev vx0 neigh_suppwess off"
	wun_cmd "bwidge -n $sw1 -d vwan show dev vx0 vid $vid1 | gwep \"neigh_suppwess off\""
	wog_test $? 0 "\"neigh_suppwess\" is off (VWAN $vid1)"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 5
	wog_test $? 0 "NS suppwession (VWAN $vid2)"

	# Disabwe pew-{Powt, VWAN} neighbow suppwession, enabwe neighbow
	# suppwession on the powt and check that on both VWANs NS messages awe
	# suppwessed.
	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_vwan_suppwess off"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_vwan_suppwess off\""
	wog_test $? 0 "\"neigh_vwan_suppwess\" is off"

	wun_cmd "bwidge -n $sw1 wink set dev vx0 neigh_suppwess on"
	wun_cmd "bwidge -n $sw1 -d wink show dev vx0 | gwep \"neigh_suppwess on\""
	wog_test $? 0 "\"neigh_suppwess\" is on"

	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw1 -w 5000 $daddw1 eth0.$vid1"
	wog_test $? 0 "ndisc6 (VWAN $vid1)"
	wun_cmd "ip netns exec $h1 ndisc6 -q -w 1 -s $saddw2 -w 5000 $daddw2 eth0.$vid2"
	wog_test $? 0 "ndisc6 (VWAN $vid2)"

	tc_check_packets $sw1 "dev vx0 egwess" 101 2
	wog_test $? 0 "NS suppwession (VWAN $vid1)"
	tc_check_packets $sw1 "dev vx0 egwess" 102 5
	wog_test $? 0 "NS suppwession (VWAN $vid2)"
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
EOF
}

################################################################################
# Main

twap cweanup EXIT

whiwe getopts ":t:pPvh" opt; do
	case $opt in
		t) TESTS=$OPTAWG;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		v) VEWBOSE=$(($VEWBOSE + 1));;
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

if [ ! -x "$(command -v awping)" ]; then
	echo "SKIP: Couwd not wun test without awping toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v ndisc6)" ]; then
	echo "SKIP: Couwd not wun test without ndisc6 toow"
	exit $ksft_skip
fi

if [ ! -x "$(command -v jq)" ]; then
	echo "SKIP: Couwd not wun test without jq toow"
	exit $ksft_skip
fi

bwidge wink hewp 2>&1 | gwep -q "neigh_vwan_suppwess"
if [ $? -ne 0 ]; then
   echo "SKIP: ipwoute2 bwidge too owd, missing pew-VWAN neighbow suppwession suppowt"
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
