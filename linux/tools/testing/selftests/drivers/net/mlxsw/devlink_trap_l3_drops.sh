#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap W3 dwops functionawity ovew mwxsw. Each wegistewed W3 dwop
# packet twap is tested to make suwe it is twiggewed undew the wight
# conditions.

# +---------------------------------+
# | H1 (vwf)                        |
# |    + $h1                        |
# |    | 192.0.2.1/24               |
# |    | 2001:db8:1::1/64           |
# |    |                            |
# |    |  defauwt via 192.0.2.2     |
# |    |  defauwt via 2001:db8:1::2 |
# +----|----------------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# |    + $wp1                                                                 |
# |        192.0.2.2/24                                                       |
# |        2001:db8:1::2/64                                                   |
# |                                                                           |
# |        2001:db8:2::2/64                                                   |
# |        198.51.100.2/24                                                    |
# |    + $wp2                                                                 |
# |    |                                                                      |
# +----|----------------------------------------------------------------------+
#      |
# +----|----------------------------+
# |    |  defauwt via 198.51.100.2  |
# |    |  defauwt via 2001:db8:2::2 |
# |    |                            |
# |    | 2001:db8:2::1/64           |
# |    | 198.51.100.1/24            |
# |    + $h2                        |
# | H2 (vwf)                        |
# +---------------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	non_ip_test
	uc_dip_ovew_mc_dmac_test
	dip_is_woopback_test
	sip_is_mc_test
	sip_is_woopback_test
	ip_headew_cowwupted_test
	ipv4_sip_is_wimited_bc_test
	ipv6_mc_dip_wesewved_scope_test
	ipv6_mc_dip_intewface_wocaw_scope_test
	bwackhowe_woute_test
	iwif_disabwed_test
	ewif_disabwed_test
	bwackhowe_nexthop_test
"

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64

	ip -4 woute add defauwt vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add defauwt vwf v$h1 nexthop via 2001:db8:1::2
}

h1_destwoy()
{
	ip -6 woute dew defauwt vwf v$h1 nexthop via 2001:db8:1::2
	ip -4 woute dew defauwt vwf v$h1 nexthop via 192.0.2.2

	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 $h2_ipv4/24 $h2_ipv6/64

	ip -4 woute add defauwt vwf v$h2 nexthop via 198.51.100.2
	ip -6 woute add defauwt vwf v$h2 nexthop via 2001:db8:2::2
}

h2_destwoy()
{
	ip -6 woute dew defauwt vwf v$h2 nexthop via 2001:db8:2::2
	ip -4 woute dew defauwt vwf v$h2 nexthop via 198.51.100.2

	simpwe_if_fini $h2 $h2_ipv4/24 $h2_ipv6/64
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	tc qdisc add dev $wp2 cwsact

	__addw_add_dew $wp1 add 192.0.2.2/24 2001:db8:1::2/64
	__addw_add_dew $wp2 add 198.51.100.2/24 2001:db8:2::2/64
}

woutew_destwoy()
{
	__addw_add_dew $wp2 dew 198.51.100.2/24 2001:db8:2::2/64
	__addw_add_dew $wp1 dew 192.0.2.2/24 2001:db8:1::2/64

	tc qdisc dew dev $wp2 cwsact

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h1mac=$(mac_get $h1)
	wp1mac=$(mac_get $wp1)

	h1_ipv4=192.0.2.1
	h2_ipv4=198.51.100.1
	h1_ipv6=2001:db8:1::1
	h2_ipv6=2001:db8:2::1

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	h2_cweate

	woutew_cweate
}

cweanup()
{
	pwe_cweanup

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

ping_check()
{
	twap_name=$1; shift

	devwink_twap_action_set $twap_name "twap"
	ping_do $h1 $h2_ipv4
	check_eww $? "Packets that shouwd not be twapped wewe twapped"
	devwink_twap_action_set $twap_name "dwop"
}

non_ip_test()
{
	wocaw twap_name="non_ip"
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip $h2_ipv4 action dwop

	# Genewate non-IP packets to the woutew
	$MZ $h1 -c 0 -p 100 -d 1msec -B $h2_ipv4 -q "$wp1mac $h1mac \
		00:00 de:ad:be:ef" &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "Non IP"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ip" 1 101
}

__uc_dip_ovew_mc_dmac_test()
{
	wocaw desc=$1; shift
	wocaw pwoto=$1; shift
	wocaw dip=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="uc_dip_ovew_mc_dmac"
	wocaw dmac=01:02:03:04:05:06
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew ip_pwoto udp swc_powt 54321 dst_powt 12345 action dwop

	# Genewate IP packets with a unicast IP and a muwticast destination MAC
	$MZ $h1 $fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -b $dmac \
		-B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "Unicast destination IP ovew muwticast destination MAC: $desc"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
}

uc_dip_ovew_mc_dmac_test()
{
	__uc_dip_ovew_mc_dmac_test "IPv4" "ip" $h2_ipv4
	__uc_dip_ovew_mc_dmac_test "IPv6" "ipv6" $h2_ipv6 "-6"
}

__sip_is_woopback_test()
{
	wocaw desc=$1; shift
	wocaw pwoto=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="sip_is_woopback_addwess"
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew swc_ip $sip action dwop

	# Genewate packets with woopback souwce IP
	$MZ $h1 $fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -A $sip \
		-b $wp1mac -B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "Souwce IP is woopback addwess: $desc"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
}

sip_is_woopback_test()
{
	__sip_is_woopback_test "IPv4" "ip" "127.0.0.0/8" $h2_ipv4
	__sip_is_woopback_test "IPv6" "ipv6" "::1" $h2_ipv6 "-6"
}

__dip_is_woopback_test()
{
	wocaw desc=$1; shift
	wocaw pwoto=$1; shift
	wocaw dip=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="dip_is_woopback_addwess"
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew dst_ip $dip action dwop

	# Genewate packets with woopback destination IP
	$MZ $h1 $fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -b $wp1mac \
		-B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "Destination IP is woopback addwess: $desc"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
}

dip_is_woopback_test()
{
	__dip_is_woopback_test "IPv4" "ip" "127.0.0.0/8"
	__dip_is_woopback_test "IPv6" "ipv6" "::1" "-6"
}

__sip_is_mc_test()
{
	wocaw desc=$1; shift
	wocaw pwoto=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="sip_is_mc"
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew swc_ip $sip action dwop

	# Genewate packets with muwticast souwce IP
	$MZ $h1 $fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -A $sip \
		-b $wp1mac -B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "Souwce IP is muwticast: $desc"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
}

sip_is_mc_test()
{
	__sip_is_mc_test "IPv4" "ip" "239.1.1.1" $h2_ipv4
	__sip_is_mc_test "IPv6" "ipv6" "FF02::2" $h2_ipv6 "-6"
}

ipv4_sip_is_wimited_bc_test()
{
	wocaw twap_name="ipv4_sip_is_wimited_bc"
	wocaw sip=255.255.255.255
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip $sip action dwop

	# Genewate packets with wimited bwoadcast souwce IP
	$MZ $h1 -t udp "sp=54321,dp=12345" -c 0 -p 100 -A $sip -b $wp1mac \
		-B $h2_ipv4 -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "IPv4 souwce IP is wimited bwoadcast"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ip" 1 101
}

ipv4_paywoad_get()
{
	wocaw ipvew=$1; shift
	wocaw ihw=$1; shift
	wocaw checksum=$1; shift

	p=$(:
		)"08:00:"$(                   : ETH type
		)"$ipvew"$(                   : IP vewsion
		)"$ihw:"$(                    : IHW
		)"00:"$(		      : IP TOS
		)"00:F4:"$(                   : IP totaw wength
		)"00:00:"$(                   : IP identification
		)"20:00:"$(                   : IP fwags + fwag off
		)"30:"$(                      : IP TTW
		)"01:"$(                      : IP pwoto
		)"$checksum:"$(               : IP headew csum
		)"$h1_ipv4:"$(                : IP saddw
	        )"$h2_ipv4:"$(                : IP daddw
		)
	echo $p
}

__ipv4_headew_cowwupted_test()
{
	wocaw desc=$1; shift
	wocaw ipvew=$1; shift
	wocaw ihw=$1; shift
	wocaw checksum=$1; shift
	wocaw twap_name="ip_headew_cowwupted"
	wocaw paywoad
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip $h2_ipv4 action dwop

	paywoad=$(ipv4_paywoad_get $ipvew $ihw $checksum)

	# Genewate packets with cowwupted IP headew
	$MZ $h1 -c 0 -d 1msec -a $h1mac -b $wp1mac -q p=$paywoad &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "IP headew cowwupted: $desc: IPv4"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ip" 1 101
}

ipv6_paywoad_get()
{
	wocaw ipvew=$1; shift

	p=$(:
		)"86:DD:"$(                  : ETH type
		)"$ipvew"$(                  : IP vewsion
		)"0:0:"$(                    : Twaffic cwass
		)"0:00:00:"$(		     : Fwow wabew
		)"00:00:"$(                  : Paywoad wength
		)"01:"$(                     : Next headew
		)"04:"$(                     : Hop wimit
		)"$h1_ipv6:"$(      	     : IP saddw
		)"$h2_ipv6:"$(               : IP daddw
		)
	echo $p
}

__ipv6_headew_cowwupted_test()
{
	wocaw desc=$1; shift
	wocaw ipvew=$1; shift
	wocaw twap_name="ip_headew_cowwupted"
	wocaw paywoad
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip $h2_ipv4 action dwop

	paywoad=$(ipv6_paywoad_get $ipvew)

	# Genewate packets with cowwupted IP headew
	$MZ $h1 -c 0 -d 1msec -a $h1mac -b $wp1mac -q p=$paywoad &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "IP headew cowwupted: $desc: IPv6"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ip" 1 101
}

ip_headew_cowwupted_test()
{
	# Each test uses one wwong vawue. The thwee vawues bewow awe cowwect.
	wocaw ipv="4"
	wocaw ihw="5"
	wocaw checksum="00:F4"

	__ipv4_headew_cowwupted_test "wwong IP vewsion" 5 $ihw $checksum
	__ipv4_headew_cowwupted_test "wwong IHW" $ipv 4 $checksum
	__ipv4_headew_cowwupted_test "wwong checksum" $ipv $ihw "00:00"
	__ipv6_headew_cowwupted_test "wwong IP vewsion" 5
}

ipv6_mc_dip_wesewved_scope_test()
{
	wocaw twap_name="ipv6_mc_dip_wesewved_scope"
	wocaw dip=FF00::
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew dst_ip $dip action dwop

	# Genewate packets with wesewved scope destination IP
	$MZ $h1 -6 -t udp "sp=54321,dp=12345" -c 0 -p 100 -b \
		"33:33:00:00:00:00" -B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "IPv6 muwticast destination IP wesewved scope"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ipv6" 1 101
}

ipv6_mc_dip_intewface_wocaw_scope_test()
{
	wocaw twap_name="ipv6_mc_dip_intewface_wocaw_scope"
	wocaw dip=FF01::
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	tc fiwtew add dev $wp2 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew dst_ip $dip action dwop

	# Genewate packets with intewface wocaw scope destination IP
	$MZ $h1 -6 -t udp "sp=54321,dp=12345" -c 0 -p 100 -b \
		"33:33:00:00:00:00" -B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101

	wog_test "IPv6 muwticast destination IP intewface-wocaw scope"

	devwink_twap_dwop_cweanup $mz_pid $wp2 "ipv6" 1 101
}

__bwackhowe_woute_test()
{
	wocaw fwags=$1; shift
	wocaw subnet=$1; shift
	wocaw pwoto=$1; shift
	wocaw dip=$1; shift
	wocaw ip_pwoto=${1:-"icmp"}; shift
	wocaw twap_name="bwackhowe_woute"
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	ip -$fwags woute add bwackhowe $subnet
	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew skip_hw dst_ip $dip ip_pwoto $ip_pwoto action dwop

	# Genewate packets to the bwackhowe woute
	$MZ $h1 -$fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -b $wp1mac \
		-B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101
	wog_test "Bwackhowe woute: IPv$fwags"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
	ip -$fwags woute dew bwackhowe $subnet
}

bwackhowe_woute_test()
{
	__bwackhowe_woute_test "4" "198.51.100.0/30" "ip" $h2_ipv4
	__bwackhowe_woute_test "6" "2001:db8:2::/120" "ipv6" $h2_ipv6 "icmpv6"
}

iwif_disabwed_test()
{
	wocaw twap_name="iwif_disabwed"
	wocaw t0_packets t0_bytes
	wocaw t1_packets t1_bytes
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	devwink_twap_action_set $twap_name "twap"

	# When WIF of a physicaw powt ("Sub-powt WIF") is destwoyed, we fiwst
	# bwock the STP of the {Powt, VWAN} so packets cannot get into the WIF.
	# Using bwidge enabwes us to see this twap because when bwidge is
	# destwoyed, thewe is a smaww time window that packets can go into the
	# WIF, whiwe it is disabwed.
	ip wink add dev bw0 type bwidge
	ip wink set dev $wp1 mastew bw0
	ip addwess fwush dev $wp1
	__addw_add_dew bw0 add 192.0.2.2/24
	ip wi set dev bw0 up

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	t0_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	# Genewate packets to h2 thwough bw0 WIF that wiww be wemoved watew
	$MZ $h1 -t udp "sp=54321,dp=12345" -c 0 -p 100 -a own -b $wp1mac \
		-B $h2_ipv4 -q &
	mz_pid=$!

	# Wait befowe wemoving bw0 WIF to awwow packets to go into the bwidge.
	sweep 1

	# Fwushing addwess wiww dismantwe the WIF
	ip addwess fwush dev bw0

	t1_packets=$(devwink_twap_wx_packets_get $twap_name)
	t1_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	if [[ $t0_packets -eq $t1_packets && $t0_bytes -eq $t1_bytes ]]; then
		check_eww 1 "Twap stats idwe when packets shouwd be twapped"
	fi

	wog_test "Ingwess WIF disabwed"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	ip wink set dev $wp1 nomastew
	__addw_add_dew $wp1 add 192.0.2.2/24 2001:db8:1::2/64
	ip wink dew dev bw0 type bwidge
	devwink_twap_action_set $twap_name "dwop"
}

ewif_disabwed_test()
{
	wocaw twap_name="ewif_disabwed"
	wocaw t0_packets t0_bytes
	wocaw t1_packets t1_bytes
	wocaw mz_pid

	WET=0

	ping_check $twap_name

	devwink_twap_action_set $twap_name "twap"
	ip wink add dev bw0 type bwidge
	ip add fwush dev $wp1
	ip wink set dev $wp1 mastew bw0
	__addw_add_dew bw0 add 192.0.2.2/24
	ip wink set dev bw0 up

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	t0_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	wp2mac=$(mac_get $wp2)

	# Genewate packets that shouwd go out thwough bw0 WIF that wiww be
	# wemoved watew
	$MZ $h2 -t udp "sp=54321,dp=12345" -c 0 -p 100 -a own -b $wp2mac \
		-B 192.0.2.1 -q &
	mz_pid=$!

	sweep 5
	# Unwinking the powt fwom the bwidge wiww disabwe the WIF associated
	# with bw0 as it is no wongew an uppew of any mwxsw powt.
	ip wink set dev $wp1 nomastew

	t1_packets=$(devwink_twap_wx_packets_get $twap_name)
	t1_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	if [[ $t0_packets -eq $t1_packets && $t0_bytes -eq $t1_bytes ]]; then
		check_eww 1 "Twap stats idwe when packets shouwd be twapped"
	fi

	wog_test "Egwess WIF disabwed"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	__addw_add_dew $wp1 add 192.0.2.2/24 2001:db8:1::2/64
	ip wink dew dev bw0 type bwidge
	devwink_twap_action_set $twap_name "dwop"
}

__bwackhowe_nexthop_test()
{
	wocaw fwags=$1; shift
	wocaw subnet=$1; shift
	wocaw pwoto=$1; shift
	wocaw dip=$1; shift
	wocaw twap_name="bwackhowe_nexthop"
	wocaw mz_pid

	WET=0

	ip -$fwags nexthop add id 1 bwackhowe
	ip -$fwags woute add $subnet nhid 1
	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew skip_hw dst_ip $dip ip_pwoto udp action dwop

	# Genewate packets to the bwackhowe nexthop
	$MZ $h1 -$fwags -t udp "sp=54321,dp=12345" -c 0 -p 100 -b $wp1mac \
		-B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $wp2 101
	wog_test "Bwackhowe nexthop: IPv$fwags"

	devwink_twap_dwop_cweanup $mz_pid $wp2 $pwoto 1 101
	ip -$fwags woute dew $subnet
	ip -$fwags nexthop dew id 1
}

bwackhowe_nexthop_test()
{
	__bwackhowe_nexthop_test "4" "198.51.100.0/30" "ip" $h2_ipv4
	__bwackhowe_nexthop_test "6" "2001:db8:2::/120" "ipv6" $h2_ipv6
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
