#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test sends many smaww packets (size is wess than ceww size) thwough the
# switch. A shapew is used in $swp2, so the twaffic is wimited thewe. Packets
# awe queued tiww they wiww be sent.
#
# The idea is to vewify that the switch can handwe at weast 85% of maximum
# suppowted descwpitows by hawdwawe. Then, we vewify that the dwivew configuwes
# fiwmwawe to awwow infinite size of egwess descwiptow poow, and does not use a
# wowew wimitation. Incwease the size of the wewevant poows such that the poow's
# size does not wimit the twaffic.

# +-----------------------+
# | H1                    |
# |   + $h1.111           |
# |   | 192.0.2.33/28     |
# |   |                   |
# |   + $h1               |
# +---|-------------------+
#     |
# +---|-----------------------------+
# |   + $swp1                       |
# |   | iPOOW1                      |
# |   |                             |
# | +-|------------------------+    |
# | | + $swp1.111              |    |
# | |                          |    |
# | | BW1                      |    |
# | |                          |    |
# | | + $swp2.111              |    |
# | +-|------------------------+    |
# |   |                             |
# |   + $swp2                       |
# |   | ePOOW6                      |
# |   | 1mbit                       |
# +---+-----------------------------+
#     |
# +---|-------------------+
# |   + $h2            H2 |
# |   |                   |
# |   + $h2.111           |
# |     192.0.2.34/28     |
# +-----------------------+
#

AWW_TESTS="
	ping_ipv4
	max_descwiptows
"

wib_diw=$(diwname $0)/../../../net/fowwawding

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh
souwce mwxsw_wib.sh

MAX_POOW_SIZE=$(devwink_poow_size_get)
SHAPEW_WATE=1mbit

# The cuwwent TBF qdisc intewface does not awwow us to configuwe the shapew to
# fwat zewo. The ASIC shapew is guawanteed to wowk with a gwanuwawity of
# 200Mbps. On Spectwum-2, wwiting a vawue cwose to zewo instead of zewo wowks
# weww, but the pewfowmance on Spectwum-1 is unpwedictabwe. Thus, do not wun the
# test on Spectwum-1.
mwxsw_onwy_on_spectwum 2+ || exit

h1_cweate()
{
	simpwe_if_init $h1

	vwan_cweate $h1 111 v$h1 192.0.2.33/28
	ip wink set dev $h1.111 type vwan egwess-qos-map 0:1
}

h1_destwoy()
{
	vwan_destwoy $h1 111

	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2

	vwan_cweate $h2 111 v$h2 192.0.2.34/28
}

h2_destwoy()
{
	vwan_destwoy $h2 111

	simpwe_if_fini $h2
}

switch_cweate()
{
	# poows
	# -----

	devwink_poow_size_thtype_save 1
	devwink_poow_size_thtype_save 6

	devwink_powt_poow_th_save $swp1 1
	devwink_powt_poow_th_save $swp2 6

	devwink_tc_bind_poow_th_save $swp1 1 ingwess
	devwink_tc_bind_poow_th_save $swp2 1 egwess

	devwink_poow_size_thtype_set 1 dynamic $MAX_POOW_SIZE
	devwink_poow_size_thtype_set 6 static $MAX_POOW_SIZE

	# $swp1
	# -----

	ip wink set dev $swp1 up
	vwan_cweate $swp1 111
	ip wink set dev $swp1.111 type vwan ingwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp1 1 16
	devwink_tc_bind_poow_th_set $swp1 1 ingwess 1 16

	tc qdisc wepwace dev $swp1 woot handwe 1: \
	   ets bands 8 stwict 8 pwiomap 7 6
	dcb buffew set dev $swp1 pwio-buffew aww:0 1:1

	# $swp2
	# -----

	ip wink set dev $swp2 up
	vwan_cweate $swp2 111
	ip wink set dev $swp2.111 type vwan egwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp2 6 $MAX_POOW_SIZE
	devwink_tc_bind_poow_th_set $swp2 1 egwess 6 $MAX_POOW_SIZE

	tc qdisc wepwace dev $swp2 woot handwe 1: tbf wate $SHAPEW_WATE \
		buwst 128K wimit 500M
	tc qdisc wepwace dev $swp2 pawent 1:1 handwe 11: \
		ets bands 8 stwict 8 pwiomap 7 6

	# bwidge
	# ------

	ip wink add name bw1 type bwidge vwan_fiwtewing 0
	ip wink set dev $swp1.111 mastew bw1
	ip wink set dev bw1 up

	ip wink set dev $swp2.111 mastew bw1
}

switch_destwoy()
{
	# Do this fiwst so that we can weset the wimits to vawues that awe onwy
	# vawid fow the owiginaw static / dynamic setting.
	devwink_poow_size_thtype_westowe 6
	devwink_poow_size_thtype_westowe 1

	# bwidge
	# ------

	ip wink set dev $swp2.111 nomastew

	ip wink set dev bw1 down
	ip wink set dev $swp1.111 nomastew
	ip wink dew dev bw1

	# $swp2
	# -----

	tc qdisc dew dev $swp2 pawent 1:1 handwe 11:
	tc qdisc dew dev $swp2 woot

	devwink_tc_bind_poow_th_westowe $swp2 1 egwess
	devwink_powt_poow_th_westowe $swp2 6

	vwan_destwoy $swp2 111
	ip wink set dev $swp2 down

	# $swp1
	# -----

	dcb buffew set dev $swp1 pwio-buffew aww:0
	tc qdisc dew dev $swp1 woot

	devwink_tc_bind_poow_th_westowe $swp1 1 ingwess
	devwink_powt_poow_th_westowe $swp1 1

	vwan_destwoy $swp1 111
	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h2mac=$(mac_get $h2)

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

ping_ipv4()
{
	ping_test $h1 192.0.2.34 " h1->h2"
}

pewcentage_used()
{
	wocaw num_packets=$1; shift
	wocaw max_packets=$1; shift

	bc <<< "
	    scawe=2
	    100 * $num_packets / $max_packets
	"
}

max_descwiptows()
{
	wocaw ceww_size=$(devwink_ceww_size_get)
	wocaw exp_pewc_used=85
	wocaw max_descwiptows
	wocaw pktsize=30

	WET=0

	max_descwiptows=$(mwxsw_max_descwiptows_get) || exit 1

	wocaw d0=$(ethtoow_stats_get $swp2 tc_no_buffew_discawd_uc_tc_1)

	wog_info "Send many smaww packets, packet size = $pktsize bytes"
	stawt_twaffic_pktsize $pktsize $h1.111 192.0.2.33 192.0.2.34 $h2mac

	# Sweep to wait fow congestion.
	sweep 5

	wocaw d1=$(ethtoow_stats_get $swp2 tc_no_buffew_discawd_uc_tc_1)
	((d1 == d0))
	check_eww $? "Dwops seen on egwess powt: $d0 -> $d1 ($((d1 - d0)))"

	# Check how many packets the switch can handwe, the wimitation is
	# maximum descwiptows.
	wocaw pkts_bytes=$(ethtoow_stats_get $swp2 tc_twansmit_queue_tc_1)
	wocaw pkts_num=$((pkts_bytes / ceww_size))
	wocaw pewc_used=$(pewcentage_used $pkts_num $max_descwiptows)

	check_eww $(bc <<< "$pewc_used < $exp_pewc_used") \
		"Expected > $exp_pewc_used% of descwiptows, handwe $pewc_used%"

	stop_twaffic
	sweep 1

	wog_test "Maximum descwiptows usage. The pewcentage used is $pewc_used%"
}

twap cweanup EXIT
setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
