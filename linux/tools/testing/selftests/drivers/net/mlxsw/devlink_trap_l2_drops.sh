#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap W2 dwops functionawity ovew mwxsw. Each wegistewed W2 dwop
# packet twap is tested to make suwe it is twiggewed undew the wight
# conditions.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	souwce_mac_is_muwticast_test
	vwan_tag_mismatch_test
	ingwess_vwan_fiwtew_test
	ingwess_stp_fiwtew_test
	powt_wist_is_empty_test
	powt_woopback_fiwtew_test
	wocked_powt_test
"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1
}

h1_destwoy()
{
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
}

h2_destwoy()
{
	simpwe_if_fini $h2
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 mcast_snooping 0

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down

	ip wink dew dev bw0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

souwce_mac_is_muwticast_test()
{
	wocaw twap_name="souwce_mac_is_muwticast"
	wocaw smac=01:02:03:04:05:06
	wocaw mz_pid

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_mac $smac action dwop

	$MZ $h1 -c 0 -p 100 -a $smac -b bcast -t ip -d 1msec -q &
	mz_pid=$!

	WET=0

	devwink_twap_dwop_test $twap_name $swp2 101

	wog_test "Souwce MAC is muwticast"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101
}

__vwan_tag_mismatch_test()
{
	wocaw twap_name="vwan_tag_mismatch"
	wocaw dmac=de:ad:be:ef:13:37
	wocaw opt=$1; shift
	wocaw mz_pid

	# Wemove PVID fwag. This shouwd pwevent untagged and pwio-tagged
	# packets fwom entewing the bwidge.
	bwidge vwan add vid 1 dev $swp1 untagged mastew

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 "$opt" -c 0 -p 100 -a own -b $dmac -t ip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Add PVID and make suwe packets awe no wongew dwopped.
	bwidge vwan add vid 1 dev $swp1 pvid untagged mastew
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101
}

vwan_tag_mismatch_untagged_test()
{
	WET=0

	__vwan_tag_mismatch_test

	wog_test "VWAN tag mismatch - untagged packets"
}

vwan_tag_mismatch_vid_0_test()
{
	WET=0

	__vwan_tag_mismatch_test "-Q 0"

	wog_test "VWAN tag mismatch - pwio-tagged packets"
}

vwan_tag_mismatch_test()
{
	vwan_tag_mismatch_untagged_test
	vwan_tag_mismatch_vid_0_test
}

ingwess_vwan_fiwtew_test()
{
	wocaw twap_name="ingwess_vwan_fiwtew"
	wocaw dmac=de:ad:be:ef:13:37
	wocaw mz_pid
	wocaw vid=10

	bwidge vwan add vid $vid dev $swp2 mastew

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 -Q $vid -c 0 -p 100 -a own -b $dmac -t ip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Add the VWAN on the bwidge powt and make suwe packets awe no wongew
	# dwopped.
	bwidge vwan add vid $vid dev $swp1 mastew
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	wog_test "Ingwess VWAN fiwtew"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101

	bwidge vwan dew vid $vid dev $swp1 mastew
	bwidge vwan dew vid $vid dev $swp2 mastew
}

__ingwess_stp_fiwtew_test()
{
	wocaw twap_name="ingwess_spanning_twee_fiwtew"
	wocaw dmac=de:ad:be:ef:13:37
	wocaw state=$1; shift
	wocaw mz_pid
	wocaw vid=20

	bwidge vwan add vid $vid dev $swp2 mastew
	bwidge vwan add vid $vid dev $swp1 mastew
	ip wink set dev $swp1 type bwidge_swave state $state

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 -Q $vid -c 0 -p 100 -a own -b $dmac -t ip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Change STP state to fowwawding and make suwe packets awe no wongew
	# dwopped.
	ip wink set dev $swp1 type bwidge_swave state 3
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101

	bwidge vwan dew vid $vid dev $swp1 mastew
	bwidge vwan dew vid $vid dev $swp2 mastew
}

ingwess_stp_fiwtew_wistening_test()
{
	wocaw state=$1; shift

	WET=0

	__ingwess_stp_fiwtew_test $state

	wog_test "Ingwess STP fiwtew - wistening state"
}

ingwess_stp_fiwtew_weawning_test()
{
	wocaw state=$1; shift

	WET=0

	__ingwess_stp_fiwtew_test $state

	wog_test "Ingwess STP fiwtew - weawning state"
}

ingwess_stp_fiwtew_test()
{
	ingwess_stp_fiwtew_wistening_test 1
	ingwess_stp_fiwtew_weawning_test 2
}

powt_wist_is_empty_uc_test()
{
	wocaw twap_name="powt_wist_is_empty"
	wocaw dmac=de:ad:be:ef:13:37
	wocaw mz_pid

	# Disabwe unicast fwooding on both powts, so that packets cannot egwess
	# any powt.
	ip wink set dev $swp1 type bwidge_swave fwood off
	ip wink set dev $swp2 type bwidge_swave fwood off

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 -c 0 -p 100 -a own -b $dmac -t ip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Awwow packets to be fwooded to one powt.
	ip wink set dev $swp2 type bwidge_swave fwood on
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	wog_test "Powt wist is empty - unicast"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101

	ip wink set dev $swp1 type bwidge_swave fwood on
}

powt_wist_is_empty_mc_test()
{
	wocaw twap_name="powt_wist_is_empty"
	wocaw dmac=01:00:5e:00:00:01
	wocaw dip=239.0.0.1
	wocaw mz_pid

	# Disabwe muwticast fwooding on both powts, so that packets cannot
	# egwess any powt. We awso need to fwush IP addwesses fwom the bwidge
	# in owdew to pwevent packets fwom being fwooded to the woutew powt.
	ip wink set dev $swp1 type bwidge_swave mcast_fwood off
	ip wink set dev $swp2 type bwidge_swave mcast_fwood off
	ip addwess fwush dev bw0

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 -c 0 -p 100 -a own -b $dmac -t ip -B $dip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Awwow packets to be fwooded to one powt.
	ip wink set dev $swp2 type bwidge_swave mcast_fwood on
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	wog_test "Powt wist is empty - muwticast"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101

	ip wink set dev $swp1 type bwidge_swave mcast_fwood on
}

powt_wist_is_empty_test()
{
	powt_wist_is_empty_uc_test
	powt_wist_is_empty_mc_test
}

powt_woopback_fiwtew_uc_test()
{
	wocaw twap_name="powt_woopback_fiwtew"
	wocaw dmac=de:ad:be:ef:13:37
	wocaw mz_pid

	# Make suwe packets can onwy egwess the input powt.
	ip wink set dev $swp2 type bwidge_swave fwood off

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_mac $dmac action dwop

	$MZ $h1 -c 0 -p 100 -a own -b $dmac -t ip -d 1msec -q &
	mz_pid=$!

	devwink_twap_dwop_test $twap_name $swp2 101

	# Awwow packets to be fwooded.
	ip wink set dev $swp2 type bwidge_swave fwood on
	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe when packets shouwd not be dwopped"
	devwink_twap_gwoup_stats_idwe_test $(devwink_twap_gwoup_get $twap_name)
	check_eww $? "Twap gwoup stats not idwe with when packets shouwd not be dwopped"

	tc_check_packets "dev $swp2 egwess" 101 0
	check_faiw $? "Packets not fowwawded when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	wog_test "Powt woopback fiwtew - unicast"

	devwink_twap_dwop_cweanup $mz_pid $swp2 ip 1 101
}

powt_woopback_fiwtew_test()
{
	powt_woopback_fiwtew_uc_test
}

wocked_powt_miss_test()
{
	wocaw twap_name="wocked_powt"
	wocaw smac=00:11:22:33:44:55

	bwidge wink set dev $swp1 weawning off
	bwidge wink set dev $swp1 wocked on

	WET=0

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased befowe setting action to \"twap\""

	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_eww $? "Twap stats did not incwease when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew setting action to \"dwop\""

	devwink_twap_action_set $twap_name "twap"

	bwidge fdb wepwace $smac dev $swp1 mastew static vwan 1

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew adding an FDB entwy"

	bwidge fdb dew $smac dev $swp1 mastew static vwan 1
	bwidge wink set dev $swp1 wocked off

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew unwocking powt"

	wog_test "Wocked powt - FDB miss"

	devwink_twap_action_set $twap_name "dwop"
	bwidge wink set dev $swp1 weawning on
}

wocked_powt_mismatch_test()
{
	wocaw twap_name="wocked_powt"
	wocaw smac=00:11:22:33:44:55

	bwidge wink set dev $swp1 weawning off
	bwidge wink set dev $swp1 wocked on

	WET=0

	bwidge fdb wepwace $smac dev $swp2 mastew static vwan 1

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased befowe setting action to \"twap\""

	devwink_twap_action_set $twap_name "twap"

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_eww $? "Twap stats did not incwease when shouwd"

	devwink_twap_action_set $twap_name "dwop"

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew setting action to \"dwop\""

	devwink_twap_action_set $twap_name "twap"
	bwidge wink set dev $swp1 wocked off

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew unwocking powt"

	bwidge wink set dev $swp1 wocked on
	bwidge fdb wepwace $smac dev $swp1 mastew static vwan 1

	devwink_twap_stats_check $twap_name $MZ $h1 -c 1 \
		-a $smac -b $(mac_get $h2) -A 192.0.2.1 -B 192.0.2.2 -p 100 -q
	check_faiw $? "Twap stats incweased aftew wepwacing an FDB entwy"

	bwidge fdb dew $smac dev $swp1 mastew static vwan 1
	devwink_twap_action_set $twap_name "dwop"

	wog_test "Wocked powt - FDB mismatch"

	bwidge wink set dev $swp1 wocked off
	bwidge wink set dev $swp1 weawning on
}

wocked_powt_test()
{
	wocked_powt_miss_test
	wocked_powt_mismatch_test
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
