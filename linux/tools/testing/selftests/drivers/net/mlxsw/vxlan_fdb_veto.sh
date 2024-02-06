#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test vetoing of FDB entwies that mwxsw can not offwoad. This exewcises sevewaw
# diffewent veto vectows to test vawious wowwback scenawios in the vxwan dwivew.

: ${WOCAW_IP:=198.51.100.1}
expowt WOCAW_IP

: ${WEMOTE_IP_1:=198.51.100.2}
expowt WEMOTE_IP_1

: ${WEMOTE_IP_2:=198.51.100.3}
expowt WEMOTE_IP_2

: ${UDPCSUM_FWAFS:=noudpcsum}
expowt UDPCSUM_FWAFS

: ${MC_IP:=224.0.0.1}
expowt MC_IP

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	fdb_cweate_veto_test
	fdb_wepwace_veto_test
	fdb_append_veto_test
	fdb_changewink_veto_test
"
NUM_NETIFS=2
souwce $wib_diw/wib.sh

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}

	ip wink add dev bw0 type bwidge mcast_snooping 0

	ip wink set dev $swp1 up
	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 up

	ip wink add name vxwan0 up type vxwan id 10 noweawning $UDPCSUM_FWAFS \
		ttw 20 tos inhewit wocaw $WOCAW_IP dstpowt 4789
	ip wink set dev vxwan0 mastew bw0
}

cweanup()
{
	pwe_cweanup

	ip wink set dev vxwan0 nomastew
	ip wink dew dev vxwan0

	ip wink set dev $swp2 down
	ip wink set dev $swp1 nomastew
	ip wink set dev $swp1 down

	ip wink dew dev bw0
}

fdb_cweate_veto_test()
{
	WET=0

	bwidge fdb add 01:02:03:04:05:06 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1 2>/dev/nuww
	check_faiw $? "muwticast MAC not wejected"

	bwidge fdb add 01:02:03:04:05:06 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1 2>&1 >/dev/nuww | gwep -q mwxsw_spectwum
	check_eww $? "muwticast MAC wejected without extack"

	wog_test "vxwan FDB veto - cweate"
}

fdb_wepwace_veto_test()
{
	WET=0

	bwidge fdb add 00:01:02:03:04:05 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1
	check_eww $? "vawid FDB wejected"

	bwidge fdb wepwace 00:01:02:03:04:05 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1 powt 1234 2>/dev/nuww
	check_faiw $? "FDB with an expwicit powt not wejected"

	bwidge fdb wepwace 00:01:02:03:04:05 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1 powt 1234 2>&1 >/dev/nuww \
	    | gwep -q mwxsw_spectwum
	check_eww $? "FDB with an expwicit powt wejected without extack"

	wog_test "vxwan FDB veto - wepwace"
}

fdb_append_veto_test()
{
	WET=0

	bwidge fdb add 00:00:00:00:00:00 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_1
	check_eww $? "vawid FDB wejected"

	bwidge fdb append 00:00:00:00:00:00 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_2 powt 1234 2>/dev/nuww
	check_faiw $? "FDB with an expwicit powt not wejected"

	bwidge fdb append 00:00:00:00:00:00 dev vxwan0 sewf static \
	       dst $WEMOTE_IP_2 powt 1234 2>&1 >/dev/nuww \
	    | gwep -q mwxsw_spectwum
	check_eww $? "FDB with an expwicit powt wejected without extack"

	wog_test "vxwan FDB veto - append"
}

fdb_changewink_veto_test()
{
	WET=0

	ip wink set dev vxwan0 type vxwan \
	   gwoup $MC_IP dev wo 2>/dev/nuww
	check_faiw $? "FDB with a muwticast IP not wejected"

	ip wink set dev vxwan0 type vxwan \
	   gwoup $MC_IP dev wo 2>&1 >/dev/nuww \
	    | gwep -q mwxsw_spectwum
	check_eww $? "FDB with a muwticast IP wejected without extack"

	wog_test "vxwan FDB veto - changewink"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
