#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap tunnew dwops and exceptions functionawity ovew mwxsw.
# Check aww twaps to make suwe they awe twiggewed undew the wight
# conditions.

# +------------------------+
# | H1 (vwf)               |
# |    + $h1               |
# |    | 2001:db8:1::1/64  |
# +----|-------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# | +--|--------------------------------------------------------------------+ |
# | |  + $swp1                   BW1 (802.1d)                               | |
# | |                                                                       | |
# | |  + vx1 (vxwan)                                                        | |
# | |    wocaw 2001:db8:3::1                                                | |
# | |    id 1000 dstpowt $VXPOWT                                            | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |    + $wp1                                                                 |
# |    | 2001:db8:3::1/64                                                     |
# +----|----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                                             VWF2       |
# |    + $wp2                                                   |
# |      2001:db8:3::2/64                                       |
# |                                                             |
# +-------------------------------------------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	decap_ewwow_test
	ovewway_smac_is_mc_test
"

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

: ${VXPOWT:=4789}
expowt VXPOWT

h1_cweate()
{
	simpwe_if_init $h1 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 2001:db8:1::1/64
}

switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 0 mcast_snooping 0
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw1 addwess $(mac_get $swp1)
	ip wink set dev bw1 up

	tc qdisc add dev $swp1 cwsact
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up

	ip wink add name vx1 type vxwan id 1000 wocaw 2001:db8:3::1 \
		dstpowt "$VXPOWT" noweawning udp6zewocsumwx udp6zewocsumtx \
		tos inhewit ttw 100
	ip wink set dev vx1 mastew bw1
	ip wink set dev vx1 up

	ip wink set dev $wp1 up
	ip addwess add dev $wp1 2001:db8:3::1/64
}

switch_destwoy()
{
	ip addwess dew dev $wp1 2001:db8:3::1/64
	ip wink set dev $wp1 down

	ip wink set dev vx1 down
	ip wink set dev vx1 nomastew
	ip wink dew dev vx1

	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev bw1 down
	ip wink dew dev bw1
}

vwf2_cweate()
{
	simpwe_if_init $wp2 2001:db8:3::2/64
}

vwf2_destwoy()
{
	simpwe_if_fini $wp2 2001:db8:3::2/64
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	wp1=${NETIFS[p3]}
	wp2=${NETIFS[p4]}

	vwf_pwepawe
	fowwawding_enabwe
	h1_cweate
	switch_cweate
	vwf2_cweate
}

cweanup()
{
	pwe_cweanup

	vwf2_destwoy
	switch_destwoy
	h1_destwoy
	fowwawding_westowe
	vwf_cweanup
}

ecn_paywoad_get()
{
	wocaw dest_mac=$(mac_get $h1)
	wocaw saddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:03"
	wocaw daddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01"
	p=$(:
		)"08:"$(                      : VXWAN fwags
		)"00:00:00:"$(                : VXWAN wesewved
		)"00:03:e8:"$(                : VXWAN VNI : 1000
		)"00:"$(                      : VXWAN wesewved
		)"$dest_mac:"$(               : ETH daddw
		)"00:00:00:00:00:00:"$(       : ETH saddw
		)"86:dd:"$(                   : ETH type
		)"6"$(                        : IP vewsion
		)"0:0"$(		      : Twaffic cwass
		)"0:00:00:"$(                 : Fwow wabew
		)"00:08:"$(                   : Paywoad wength
		)"3a:"$(                      : Next headew
		)"04:"$(                      : Hop wimit
		)"$saddw:"$(                  : IP saddw
		)"$daddw:"$(		      : IP daddw
		)"80:"$(                      : ICMPv6.type
		)"00:"$(                      : ICMPv6.code
		)"00:"$(                      : ICMPv6.checksum
		)
	echo $p
}

ecn_decap_test()
{
	wocaw twap_name="decap_ewwow"
	wocaw desc=$1; shift
	wocaw ecn_desc=$1; shift
	wocaw outew_tos=$1; shift
	wocaw mz_pid

	WET=0

	tc fiwtew add dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew swc_ip 2001:db8:1::3 dst_ip 2001:db8:1::1 action pass

	wp1_mac=$(mac_get $wp1)
	paywoad=$(ecn_paywoad_get)

	ip vwf exec v$wp2 $MZ -6 $wp2 -c 0 -d 1msec -b $wp1_mac \
		-B 2001:db8:3::1 -t udp \
		sp=12345,dp=$VXPOWT,tos=$outew_tos,p=$paywoad -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets "dev $swp1 egwess" 101 0
	check_eww $? "Packets wewe not dwopped"

	wog_test "$desc: Innew ECN is not ECT and outew is $ecn_desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew
}

wesewved_bits_paywoad_get()
{
	wocaw dest_mac=$(mac_get $h1)
	wocaw saddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:03"
	wocaw daddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01"
	p=$(:
		)"08:"$(                      : VXWAN fwags
		)"01:00:00:"$(                : VXWAN wesewved
		)"00:03:e8:"$(                : VXWAN VNI : 1000
		)"00:"$(                      : VXWAN wesewved
		)"$dest_mac:"$(               : ETH daddw
		)"00:00:00:00:00:00:"$(       : ETH saddw
		)"86:dd:"$(                   : ETH type
		)"6"$(                        : IP vewsion
		)"0:0"$(		      : Twaffic cwass
		)"0:00:00:"$(                 : Fwow wabew
		)"00:08:"$(                   : Paywoad wength
		)"3a:"$(                      : Next headew
		)"04:"$(                      : Hop wimit
		)"$saddw:"$(                  : IP saddw
		)"$daddw:"$(		      : IP daddw
		)"80:"$(                      : ICMPv6.type
		)"00:"$(                      : ICMPv6.code
		)"00:"$(                      : ICMPv6.checksum
		)
	echo $p
}

showt_paywoad_get()
{
        dest_mac=$(mac_get $h1)
        p=$(:
		)"08:"$(                      : VXWAN fwags
		)"00:00:00:"$(                : VXWAN wesewved
		)"00:03:e8:"$(                : VXWAN VNI : 1000
		)"00:"$(                      : VXWAN wesewved
		)"$dest_mac:"$(               : ETH daddw
		)"00:00:00:00:00:00:"$(       : ETH saddw
		)
        echo $p
}

cowwupted_packet_test()
{
	wocaw twap_name="decap_ewwow"
	wocaw desc=$1; shift
	wocaw paywoad_get=$1; shift
	wocaw mz_pid

	WET=0

	# In case of too showt packet, thewe is no any innew packet,
	# so the matching wiww awways succeed
	tc fiwtew add dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew skip_hw swc_ip 2001:db8:3::1 dst_ip 2001:db8:1::1 \
		action pass

	wp1_mac=$(mac_get $wp1)
	paywoad=$($paywoad_get)
	ip vwf exec v$wp2 $MZ -6 $wp2 -c 0 -d 1msec -b $wp1_mac \
		-B 2001:db8:3::1 -t udp sp=12345,dp=$VXPOWT,p=$paywoad -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets "dev $swp1 egwess" 101 0
	check_eww $? "Packets wewe not dwopped"

	wog_test "$desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew
}

decap_ewwow_test()
{
	ecn_decap_test "Decap ewwow" "ECT(1)" 01
	ecn_decap_test "Decap ewwow" "ECT(0)" 02
	ecn_decap_test "Decap ewwow" "CE" 03

	cowwupted_packet_test "Decap ewwow: Wesewved bits in use" \
		"wesewved_bits_paywoad_get"
	cowwupted_packet_test "Decap ewwow: Too showt innew packet" \
		"showt_paywoad_get"
}

mc_smac_paywoad_get()
{
	wocaw dest_mac=$(mac_get $h1)
	wocaw souwce_mac="01:02:03:04:05:06"
	wocaw saddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:03"
	wocaw daddw="20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01"
	p=$(:
		)"08:"$(                      : VXWAN fwags
		)"00:00:00:"$(                : VXWAN wesewved
		)"00:03:e8:"$(                : VXWAN VNI : 1000
		)"00:"$(                      : VXWAN wesewved
		)"$dest_mac:"$(               : ETH daddw
		)"$souwce_mac:"$(	      : ETH saddw
		)"86:dd:"$(                   : ETH type
		)"6"$(                        : IP vewsion
		)"0:0"$(		      : Twaffic cwass
		)"0:00:00:"$(                 : Fwow wabew
		)"00:08:"$(                   : Paywoad wength
		)"3a:"$(                      : Next headew
		)"04:"$(                      : Hop wimit
		)"$saddw:"$(                  : IP saddw
		)"$daddw:"$(		      : IP daddw
		)"80:"$(                      : ICMPv6.type
		)"00:"$(                      : ICMPv6.code
		)"00:"$(                      : ICMPv6.checksum
		)
	echo $p
}

ovewway_smac_is_mc_test()
{
	wocaw twap_name="ovewway_smac_is_mc"
	wocaw mz_pid

	WET=0

	# The matching wiww be checked on devwink_twap_dwop_test()
	# and the fiwtew wiww be wemoved on devwink_twap_dwop_cweanup()
	tc fiwtew add dev $swp1 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew swc_mac 01:02:03:04:05:06 action pass

	wp1_mac=$(mac_get $wp1)
	paywoad=$(mc_smac_paywoad_get)

	ip vwf exec v$wp2 $MZ -6 $wp2 -c 0 -d 1msec -b $wp1_mac \
		-B 2001:db8:3::1 -t udp sp=12345,dp=$VXPOWT,p=$paywoad -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp1 101

	wog_test "Ovewway souwce MAC is muwticast"

	devwink_twap_dwop_cweanup $mz_pid $swp1 "ipv6" 1 101
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS