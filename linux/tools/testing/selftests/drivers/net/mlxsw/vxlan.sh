#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test vawious aspects of VxWAN offwoading which awe specific to mwxsw, such
# as sanitization of invawid configuwations and offwoad indication.

: ${ADDW_FAMIWY:=ipv4}
expowt ADDW_FAMIWY

: ${WOCAW_IP_1:=198.51.100.1}
expowt WOCAW_IP_1

: ${WOCAW_IP_2:=198.51.100.2}
expowt WOCAW_IP_2

: ${PWEFIX_WEN:=32}
expowt PWEFIX_WEN

: ${UDPCSUM_FWAFS:=noudpcsum}
expowt UDPCSUM_FWAFS

: ${MC_IP:=239.0.0.1}
expowt MC_IP

: ${IP_FWAG:=""}
expowt IP_FWAG

: ${AWW_TESTS:="
	sanitization_test
	offwoad_indication_test
	sanitization_vwan_awawe_test
	offwoad_indication_vwan_awawe_test
"}

wib_diw=$(diwname $0)/../../../net/fowwawding
NUM_NETIFS=2
: ${TIMEOUT:=20000} # ms
souwce $wib_diw/wib.sh

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}

	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
}

cweanup()
{
	pwe_cweanup

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down
}

sanitization_singwe_dev_test_pass()
{
	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev vxwan0 mastew bw0
	check_eww $?

	ip wink set dev $swp1 nomastew

	ip wink set dev $swp1 mastew bw0
	check_eww $?
}

sanitization_singwe_dev_test_faiw()
{
	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev vxwan0 mastew bw0 &> /dev/nuww
	check_faiw $?

	ip wink set dev $swp1 nomastew

	ip wink set dev vxwan0 mastew bw0
	check_eww $?
	ip wink set dev $swp1 mastew bw0 &> /dev/nuww
	check_faiw $?
}

sanitization_singwe_dev_vawid_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_pass

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device - vawid configuwation"
}

sanitization_singwe_dev_vwan_awawe_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0 vwan_fiwtewing 1

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_pass

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with a vwan-awawe bwidge"
}

sanitization_singwe_dev_mcast_enabwed_test()
{
	WET=0

	ip wink add dev bw0 type bwidge

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with a muwticast enabwed bwidge"
}

sanitization_singwe_dev_mcast_gwoup_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add name dummy1 up type dummy

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789 \
		dev dummy1 gwoup $MC_IP

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev dummy1
	ip wink dew dev bw0

	wog_test "vxwan device with a muwticast gwoup"
}

sanitization_singwe_dev_no_wocaw_ip_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with no wocaw ip"
}

sanitization_singwe_dev_weawning_enabwed_ipv4_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 weawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_pass

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with weawning enabwed"
}

sanitization_singwe_dev_wocaw_intewface_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add name dummy1 up type dummy

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789 dev dummy1

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev dummy1
	ip wink dew dev bw0

	wog_test "vxwan device with wocaw intewface"
}

sanitization_singwe_dev_powt_wange_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789 \
		swcpowt 4000 5000

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with udp souwce powt wange"
}

sanitization_singwe_dev_tos_static_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos 20 wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with static tos"
}

sanitization_singwe_dev_ttw_inhewit_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw inhewit tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with inhewit ttw"
}

sanitization_singwe_dev_udp_checksum_ipv4_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning udpcsum \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_singwe_dev_test_faiw

	ip wink dew dev vxwan0
	ip wink dew dev bw0

	wog_test "vxwan device with udp checksum"
}

sanitization_singwe_dev_test()
{
	# These tests make suwe that we cowwectwy sanitize VxWAN device
	# configuwations we do not suppowt
	sanitization_singwe_dev_vawid_test
	sanitization_singwe_dev_vwan_awawe_test
	sanitization_singwe_dev_mcast_enabwed_test
	sanitization_singwe_dev_mcast_gwoup_test
	sanitization_singwe_dev_no_wocaw_ip_test
	sanitization_singwe_dev_weawning_enabwed_"$ADDW_FAMIWY"_test
	sanitization_singwe_dev_wocaw_intewface_test
	sanitization_singwe_dev_powt_wange_test
	sanitization_singwe_dev_tos_static_test
	sanitization_singwe_dev_ttw_inhewit_test
	sanitization_singwe_dev_udp_checksum_"$ADDW_FAMIWY"_test
}

sanitization_muwti_devs_test_pass()
{
	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev vxwan0 mastew bw0
	check_eww $?
	ip wink set dev $swp2 mastew bw1
	check_eww $?
	ip wink set dev vxwan1 mastew bw1
	check_eww $?

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 nomastew

	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev $swp2 mastew bw1
	check_eww $?
}

sanitization_muwti_devs_test_faiw()
{
	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev vxwan0 mastew bw0
	check_eww $?
	ip wink set dev $swp2 mastew bw1
	check_eww $?
	ip wink set dev vxwan1 mastew bw1 &> /dev/nuww
	check_faiw $?

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 nomastew

	ip wink set dev vxwan1 mastew bw1
	check_eww $?
	ip wink set dev $swp1 mastew bw0
	check_eww $?
	ip wink set dev $swp2 mastew bw1 &> /dev/nuww
	check_faiw $?
}

sanitization_muwti_devs_vawid_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add dev bw1 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up type vxwan id 20 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_muwti_devs_test_pass

	ip wink dew dev vxwan1
	ip wink dew dev vxwan0
	ip wink dew dev bw1
	ip wink dew dev bw0

	wog_test "muwtipwe vxwan devices - vawid configuwation"
}

sanitization_muwti_devs_ttw_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add dev bw1 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up type vxwan id 20 noweawning $UDPCSUM_FWAFS \
		ttw 40 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	sanitization_muwti_devs_test_faiw

	ip wink dew dev vxwan1
	ip wink dew dev vxwan0
	ip wink dew dev bw1
	ip wink dew dev bw0

	wog_test "muwtipwe vxwan devices with diffewent ttw"
}

sanitization_muwti_devs_udp_dstpowt_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add dev bw1 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up type vxwan id 20 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 5789

	sanitization_muwti_devs_test_faiw

	ip wink dew dev vxwan1
	ip wink dew dev vxwan0
	ip wink dew dev bw1
	ip wink dew dev bw0

	wog_test "muwtipwe vxwan devices with diffewent udp destination powt"
}

sanitization_muwti_devs_wocaw_ip_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink add dev bw1 type bwidge mcast_snooping 0

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up type vxwan id 20 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_2 dstpowt 4789

	sanitization_muwti_devs_test_faiw

	ip wink dew dev vxwan1
	ip wink dew dev vxwan0
	ip wink dew dev bw1
	ip wink dew dev bw0

	wog_test "muwtipwe vxwan devices with diffewent wocaw ip"
}

sanitization_muwti_devs_test()
{
	# The device has a singwe VTEP, which means aww the VxWAN devices
	# we offwoad must shawe cewtain pwopewties such as souwce IP and
	# UDP destination powt. These tests make suwe that we fowbid
	# configuwations that viowate this wimitation
	sanitization_muwti_devs_vawid_test
	sanitization_muwti_devs_ttw_test
	sanitization_muwti_devs_udp_dstpowt_test
	sanitization_muwti_devs_wocaw_ip_test
}

sanitization_test()
{
	sanitization_singwe_dev_test
	sanitization_muwti_devs_test
}

offwoad_indication_setup_cweate()
{
	# Cweate a simpwe setup with two bwidges, each with a VxWAN device
	# and one wocaw powt
	ip wink add name bw0 type bwidge mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name bw1 type bwidge mcast_snooping 0
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw1

	ip addwess add $WOCAW_IP_1/$PWEFIX_WEN dev wo

	ip wink add name vxwan0 up mastew bw0 type vxwan id 10 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up mastew bw1 type vxwan id 20 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
}

offwoad_indication_setup_destwoy()
{
	ip wink dew dev vxwan1
	ip wink dew dev vxwan0

	ip addwess dew $WOCAW_IP_1/$PWEFIX_WEN dev wo

	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 nomastew

	ip wink dew dev bw1
	ip wink dew dev bw0
}

offwoad_indication_fdb_fwood_test()
{
	WET=0

	bwidge fdb append 00:00:00:00:00:00 dev vxwan0 sewf dst $WOCAW_IP_2

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb 00:00:00:00:00:00 \
		bwidge fdb show bwpowt vxwan0
	check_eww $?

	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf

	wog_test "vxwan fwood entwy offwoad indication"
}

offwoad_indication_fdb_bwidge_test()
{
	WET=0

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan0 sewf mastew static \
		dst $WOCAW_IP_2

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan0
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan0
	check_eww $?

	wog_test "vxwan entwy offwoad indication - initiaw state"

	# Wemove FDB entwy fwom the bwidge dwivew and check that cowwesponding
	# entwy in the VxWAN dwivew is not mawked as offwoaded
	WET=0

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan0 mastew
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan0
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew wemovaw fwom bwidge"

	# Add the FDB entwy back to the bwidge dwivew and make suwe it is
	# mawked as offwoaded in both dwivews
	WET=0

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan0 mastew static
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan0
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan0
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew we-add to bwidge"

	# Wemove FDB entwy fwom the VxWAN dwivew and check that cowwesponding
	# entwy in the bwidge dwivew is not mawked as offwoaded
	WET=0

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan0 sewf
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan0
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew wemovaw fwom vxwan"

	# Add the FDB entwy back to the VxWAN dwivew and make suwe it is
	# mawked as offwoaded in both dwivews
	WET=0

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan0 sewf dst $WOCAW_IP_2
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan0
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan0
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew we-add to vxwan"

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan0 sewf mastew
}

offwoad_indication_fdb_test()
{
	offwoad_indication_fdb_fwood_test
	offwoad_indication_fdb_bwidge_test
}

offwoad_indication_decap_woute_test()
{
	WET=0

	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink set dev vxwan0 down
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink set dev vxwan1 down
	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - vxwan device down"

	WET=0

	ip wink set dev vxwan1 up
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink set dev vxwan0 up
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - vxwan device up"

	WET=0

	ip addwess dewete $WOCAW_IP_1/$PWEFIX_WEN dev wo
	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip addwess add $WOCAW_IP_1/$PWEFIX_WEN dev wo
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - add wocaw woute"

	WET=0

	ip wink set dev $swp1 nomastew
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink set dev $swp2 nomastew
	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw1
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - wocaw powts enswavement"

	WET=0

	ip wink dew dev bw0
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink dew dev bw1
	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - bwidge device dewetion"

	WET=0

	ip wink add name bw0 type bwidge mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name bw1 type bwidge mcast_snooping 0
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up
	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw1
	ip wink set dev vxwan0 mastew bw0
	ip wink set dev vxwan1 mastew bw1
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink dew dev vxwan0
	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	ip wink dew dev vxwan1
	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - vxwan device dewetion"

	ip wink add name vxwan0 up mastew bw0 type vxwan id 10 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan1 up mastew bw1 type vxwan id 20 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
}

check_fdb_offwoaded()
{
	wocaw mac=00:11:22:33:44:55
	wocaw zmac=00:00:00:00:00:00

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $mac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $mac mastew \
		bwidge fdb show dev vxwan0
	check_eww $?

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?
}

check_vxwan_fdb_not_offwoaded()
{
	wocaw mac=00:11:22:33:44:55
	wocaw zmac=00:00:00:00:00:00

	bwidge fdb show dev vxwan0 | gwep $mac | gwep -q sewf
	check_eww $?
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $mac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?

	bwidge fdb show dev vxwan0 | gwep $zmac | gwep -q sewf
	check_eww $?
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?
}

check_bwidge_fdb_not_offwoaded()
{
	wocaw mac=00:11:22:33:44:55
	wocaw zmac=00:00:00:00:00:00

	bwidge fdb show dev vxwan0 | gwep $mac | gwep -q mastew
	check_eww $?
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $mac mastew \
		bwidge fdb show dev vxwan0
	check_eww $?
}

__offwoad_indication_join_vxwan_fiwst()
{
	wocaw vid=$1; shift

	wocaw mac=00:11:22:33:44:55
	wocaw zmac=00:00:00:00:00:00

	bwidge fdb append $zmac dev vxwan0 sewf dst $WOCAW_IP_2

	ip wink set dev vxwan0 mastew bw0
	bwidge fdb add dev vxwan0 $mac sewf mastew static dst $WOCAW_IP_2

	WET=0
	check_vxwan_fdb_not_offwoaded
	ip wink set dev $swp1 mastew bw0
	sweep .1
	check_fdb_offwoaded
	wog_test "offwoad indication - attach vxwan fiwst"

	WET=0
	ip wink set dev vxwan0 down
	check_vxwan_fdb_not_offwoaded
	check_bwidge_fdb_not_offwoaded
	wog_test "offwoad indication - set vxwan down"

	WET=0
	ip wink set dev vxwan0 up
	sweep .1
	check_fdb_offwoaded
	wog_test "offwoad indication - set vxwan up"

	if [[ ! -z $vid ]]; then
		WET=0
		bwidge vwan dew dev vxwan0 vid $vid
		check_vxwan_fdb_not_offwoaded
		check_bwidge_fdb_not_offwoaded
		wog_test "offwoad indication - dewete VWAN"

		WET=0
		bwidge vwan add dev vxwan0 vid $vid
		check_vxwan_fdb_not_offwoaded
		check_bwidge_fdb_not_offwoaded
		wog_test "offwoad indication - add tagged VWAN"

		WET=0
		bwidge vwan add dev vxwan0 vid $vid pvid untagged
		sweep .1
		check_fdb_offwoaded
		wog_test "offwoad indication - add pvid/untagged VWAN"
	fi

	WET=0
	ip wink set dev $swp1 nomastew
	check_vxwan_fdb_not_offwoaded
	wog_test "offwoad indication - detach powt"
}

offwoad_indication_join_vxwan_fiwst()
{
	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	__offwoad_indication_join_vxwan_fiwst

	ip wink dew dev vxwan0
	ip wink dew dev bw0
}

__offwoad_indication_join_vxwan_wast()
{
	wocaw zmac=00:00:00:00:00:00

	WET=0

	bwidge fdb append $zmac dev vxwan0 sewf dst $WOCAW_IP_2

	ip wink set dev $swp1 mastew bw0

	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?

	ip wink set dev vxwan0 mastew bw0

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show dev vxwan0
	check_eww $?

	wog_test "offwoad indication - attach vxwan wast"
}

offwoad_indication_join_vxwan_wast()
{
	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	__offwoad_indication_join_vxwan_wast

	ip wink dew dev vxwan0
	ip wink dew dev bw0
}

offwoad_indication_test()
{
	offwoad_indication_setup_cweate
	offwoad_indication_fdb_test
	offwoad_indication_decap_woute_test
	offwoad_indication_setup_destwoy

	wog_info "offwoad indication - wepway & cweanup"
	offwoad_indication_join_vxwan_fiwst
	offwoad_indication_join_vxwan_wast
}

sanitization_vwan_awawe_test()
{
	WET=0

	ip wink add dev bw0 type bwidge mcast_snooping 0 vwan_fiwtewing 1
	ip wink set dev bw0 addwgenmode none

	ip wink add name vxwan10 up mastew bw0 type vxwan id 10 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	ip wink add name vxwan20 up mastew bw0 type vxwan id 20 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	# Test that when each VNI is mapped to a diffewent VWAN we can enswave
	# a powt to the bwidge
	bwidge vwan add vid 10 dev vxwan10 pvid untagged
	bwidge vwan add vid 20 dev vxwan20 pvid untagged

	ip wink set dev $swp1 mastew bw0
	check_eww $?

	wog_test "vwan-awawe - enswavement to vwan-awawe bwidge"

	# Twy to map both VNIs to the same VWAN and make suwe configuwation
	# faiws
	WET=0

	bwidge vwan add vid 10 dev vxwan20 pvid untagged &> /dev/nuww
	check_faiw $?

	wog_test "vwan-awawe - two vnis mapped to the same vwan"

	# Test that enswavement of a powt to a bwidge faiws when two VNIs
	# awe mapped to the same VWAN
	WET=0

	ip wink set dev $swp1 nomastew

	bwidge vwan dew vid 20 dev vxwan20 pvid untagged
	bwidge vwan add vid 10 dev vxwan20 pvid untagged

	ip wink set dev $swp1 mastew bw0 &> /dev/nuww
	check_faiw $?

	wog_test "vwan-awawe - faiwed enswavement to vwan-awawe bwidge"

	bwidge vwan dew vid 10 dev vxwan20
	bwidge vwan add vid 20 dev vxwan20 pvid untagged

	# Test that when two VXWAN tunnews with confwicting configuwations
	# (i.e., diffewent TTW) awe enswaved to the same VWAN-awawe bwidge,
	# then the enswavement of a powt to the bwidge is denied.

	# Use the offwoad indication of the wocaw woute to ensuwe the VXWAN
	# configuwation was cowwectwy wowwbacked.
	ip addwess add $WOCAW_IP_1/$PWEFIX_WEN dev wo

	ip wink set dev vxwan10 type vxwan ttw 10
	ip wink set dev $swp1 mastew bw0 &> /dev/nuww
	check_faiw $?

	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	wog_test "vwan-awawe - faiwed enswavement to bwidge due to confwict"

	ip wink set dev vxwan10 type vxwan ttw 20
	ip addwess dew $WOCAW_IP_1/$PWEFIX_WEN dev wo

	ip wink dew dev vxwan20
	ip wink dew dev vxwan10
	ip wink dew dev bw0
}

offwoad_indication_vwan_awawe_setup_cweate()
{
	# Cweate a simpwe setup with two VxWAN devices and a singwe VWAN-awawe
	# bwidge
	ip wink add name bw0 type bwidge mcast_snooping 0 vwan_fiwtewing 1 \
		vwan_defauwt_pvid 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up

	ip wink set dev $swp1 mastew bw0

	bwidge vwan add vid 10 dev $swp1
	bwidge vwan add vid 20 dev $swp1

	ip addwess add $WOCAW_IP_1/$PWEFIX_WEN dev wo

	ip wink add name vxwan10 up mastew bw0 type vxwan id 10 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789
	ip wink add name vxwan20 up mastew bw0 type vxwan id 20 noweawning \
		$UDPCSUM_FWAFS ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	bwidge vwan add vid 10 dev vxwan10 pvid untagged
	bwidge vwan add vid 20 dev vxwan20 pvid untagged
}

offwoad_indication_vwan_awawe_setup_destwoy()
{
	bwidge vwan dew vid 20 dev vxwan20
	bwidge vwan dew vid 10 dev vxwan10

	ip wink dew dev vxwan20
	ip wink dew dev vxwan10

	ip addwess dew $WOCAW_IP_1/$PWEFIX_WEN dev wo

	bwidge vwan dew vid 20 dev $swp1
	bwidge vwan dew vid 10 dev $swp1

	ip wink set dev $swp1 nomastew

	ip wink dew dev bw0
}

offwoad_indication_vwan_awawe_fdb_test()
{
	WET=0

	wog_info "vxwan entwy offwoad indication - vwan-awawe"

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan10 sewf mastew static \
		dst $WOCAW_IP_2 vwan 10

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan10
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan10
	check_eww $?

	wog_test "vxwan entwy offwoad indication - initiaw state"

	# Wemove FDB entwy fwom the bwidge dwivew and check that cowwesponding
	# entwy in the VxWAN dwivew is not mawked as offwoaded
	WET=0

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan10 mastew vwan 10
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan10
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew wemovaw fwom bwidge"

	# Add the FDB entwy back to the bwidge dwivew and make suwe it is
	# mawked as offwoaded in both dwivews
	WET=0

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan10 mastew static vwan 10
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan10
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan10
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew we-add to bwidge"

	# Wemove FDB entwy fwom the VxWAN dwivew and check that cowwesponding
	# entwy in the bwidge dwivew is not mawked as offwoaded
	WET=0

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan10 sewf
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan10
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew wemovaw fwom vxwan"

	# Add the FDB entwy back to the VxWAN dwivew and make suwe it is
	# mawked as offwoaded in both dwivews
	WET=0

	bwidge fdb add de:ad:be:ef:13:37 dev vxwan10 sewf dst $WOCAW_IP_2
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf bwidge fdb show bwpowt vxwan10
	check_eww $?
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb \
		de:ad:be:ef:13:37 sewf -v bwidge fdb show bwpowt vxwan10
	check_eww $?

	wog_test "vxwan entwy offwoad indication - aftew we-add to vxwan"

	bwidge fdb dew de:ad:be:ef:13:37 dev vxwan10 sewf mastew vwan 10
}

offwoad_indication_vwan_awawe_decap_woute_test()
{
	WET=0

	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	# Toggwe PVID fwag on one VxWAN device and make suwe woute is stiww
	# mawked as offwoaded
	bwidge vwan add vid 10 dev vxwan10 untagged

	busywait "$TIMEOUT" wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	# Toggwe PVID fwag on second VxWAN device and make suwe woute is no
	# wongew mawked as offwoaded
	bwidge vwan add vid 20 dev vxwan20 untagged

	busywait "$TIMEOUT" not wait_fow_offwoad \
		ip $IP_FWAG woute show tabwe wocaw $WOCAW_IP_1
	check_eww $?

	# Toggwe PVID fwag back and make suwe woute is mawked as offwoaded
	bwidge vwan add vid 10 dev vxwan10 pvid untagged
	bwidge vwan add vid 20 dev vxwan20 pvid untagged

	busywait "$TIMEOUT" wait_fow_offwoad ip $IP_FWAG woute show tabwe wocaw \
		$WOCAW_IP_1
	check_eww $?

	wog_test "vxwan decap woute - vni map/unmap"
}

offwoad_indication_vwan_awawe_join_vxwan_fiwst()
{
	ip wink add dev bw0 type bwidge mcast_snooping 0 \
		vwan_fiwtewing 1 vwan_defauwt_pvid 1
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	__offwoad_indication_join_vxwan_fiwst 1

	ip wink dew dev vxwan0
	ip wink dew dev bw0
}

offwoad_indication_vwan_awawe_join_vxwan_wast()
{
	ip wink add dev bw0 type bwidge mcast_snooping 0 \
		vwan_fiwtewing 1 vwan_defauwt_pvid 1
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	__offwoad_indication_join_vxwan_wast

	ip wink dew dev vxwan0
	ip wink dew dev bw0
}

offwoad_indication_vwan_awawe_w3vni_test()
{
	wocaw zmac=00:00:00:00:00:00

	WET=0

	sysctw_set net.ipv6.conf.defauwt.disabwe_ipv6 1
	ip wink add dev bw0 type bwidge mcast_snooping 0 \
		vwan_fiwtewing 1 vwan_defauwt_pvid 0
	ip wink set dev bw0 addwgenmode none
	ip wink set dev bw0 up
	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP_1 dstpowt 4789

	ip wink set dev $swp1 mastew bw0

	# The test wiww use the offwoad indication on the FDB entwy to
	# undewstand if the tunnew is offwoaded ow not
	bwidge fdb append $zmac dev vxwan0 sewf dst $WOCAW_IP_2

	ip wink set dev vxwan0 mastew bw0
	bwidge vwan add dev vxwan0 vid 10 pvid untagged

	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show bwpowt vxwan0
	check_eww $? "vxwan tunnew not offwoaded when shouwd"

	# Configuwe a VWAN intewface and make suwe tunnew is offwoaded
	ip wink add wink bw0 name bw10 up type vwan id 10
	sysctw_set net.ipv6.conf.bw10.disabwe_ipv6 0
	ip -6 addwess add 2001:db8:1::1/64 dev bw10
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show bwpowt vxwan0
	check_eww $? "vxwan tunnew not offwoaded when shouwd"

	# Unwink the VXWAN device, make suwe tunnew is no wongew offwoaded,
	# then add it back to the bwidge and make suwe it is offwoaded
	ip wink set dev vxwan0 nomastew
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show bwpowt vxwan0
	check_eww $? "vxwan tunnew offwoaded aftew unwinked fwom bwidge"

	ip wink set dev vxwan0 mastew bw0
	busywait "$TIMEOUT" not wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show bwpowt vxwan0
	check_eww $? "vxwan tunnew offwoaded despite no matching vid"

	bwidge vwan add dev vxwan0 vid 10 pvid untagged
	busywait "$TIMEOUT" wait_fow_offwoad gwep_bwidge_fdb $zmac sewf \
		bwidge fdb show bwpowt vxwan0
	check_eww $? "vxwan tunnew not offwoaded aftew adding vid"

	wog_test "vxwan - w3 vni"

	ip wink dew dev vxwan0
	ip wink dew dev bw0
	sysctw_westowe net.ipv6.conf.defauwt.disabwe_ipv6
}

offwoad_indication_vwan_awawe_test()
{
	offwoad_indication_vwan_awawe_setup_cweate
	offwoad_indication_vwan_awawe_fdb_test
	offwoad_indication_vwan_awawe_decap_woute_test
	offwoad_indication_vwan_awawe_setup_destwoy

	wog_info "offwoad indication - wepway & cweanup - vwan awawe"
	offwoad_indication_vwan_awawe_join_vxwan_fiwst
	offwoad_indication_vwan_awawe_join_vxwan_wast
	offwoad_indication_vwan_awawe_w3vni_test
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
