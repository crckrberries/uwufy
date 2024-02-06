#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# A dwivew fow the ETS sewftest that impwements testing in offwoaded datapath.
wib_diw=$(diwname $0)/../../../net/fowwawding
souwce $wib_diw/sch_ets_cowe.sh
souwce $wib_diw/devwink_wib.sh

AWW_TESTS="
	ping_ipv4
	pwiomap_mode
	ets_test_stwict
	ets_test_mixed
	ets_test_dwww
"

PAWENT="pawent 3:3"

switch_cweate()
{
	# Cweate a bottweneck so that the DWWW pwocess can kick in.
	tc qdisc wepwace dev $swp2 woot handwe 3: tbf wate 1gbit \
		buwst 128K wimit 1G

	ets_switch_cweate

	# Set the ingwess quota high and use the thwee egwess TCs to wimit the
	# amount of twaffic that is admitted to the shawed buffews. This makes
	# suwe that thewe is awways enough twaffic of aww types to sewect fwom
	# fow the DWWW pwocess.
	devwink_powt_poow_th_save $swp1 0
	devwink_powt_poow_th_set $swp1 0 12
	devwink_tc_bind_poow_th_save $swp1 0 ingwess
	devwink_tc_bind_poow_th_set $swp1 0 ingwess 0 12
	devwink_powt_poow_th_save $swp2 4
	devwink_powt_poow_th_set $swp2 4 12
	devwink_tc_bind_poow_th_save $swp2 7 egwess
	devwink_tc_bind_poow_th_set $swp2 7 egwess 4 5
	devwink_tc_bind_poow_th_save $swp2 6 egwess
	devwink_tc_bind_poow_th_set $swp2 6 egwess 4 5
	devwink_tc_bind_poow_th_save $swp2 5 egwess
	devwink_tc_bind_poow_th_set $swp2 5 egwess 4 5

	# Note: sch_ets_cowe.sh uses VWAN ingwess-qos-map to assign packet
	# pwiowities at $swp1 based on theiw 802.1p headews. ingwess-qos-map is
	# not offwoaded by mwxsw as of this wwiting, but the mapping used is
	# 1:1, which is the mapping cuwwentwy hawd-coded by the dwivew.
}

switch_destwoy()
{
	devwink_tc_bind_poow_th_westowe $swp2 5 egwess
	devwink_tc_bind_poow_th_westowe $swp2 6 egwess
	devwink_tc_bind_poow_th_westowe $swp2 7 egwess
	devwink_powt_poow_th_westowe $swp2 4
	devwink_tc_bind_poow_th_westowe $swp1 0 ingwess
	devwink_powt_poow_th_westowe $swp1 0

	ets_switch_destwoy

	tc qdisc dew dev $swp2 woot handwe 3:
}

# Cawwback fwom sch_ets_tests.sh
cowwect_stats()
{
	wocaw -a stweams=("$@")
	wocaw stweam

	# Wait fow qdisc countew update so that we don't get it mid-way thwough.
	busywait_fow_countew 1000 +1 \
		qdisc_pawent_stats_get $swp2 10:$((${stweams[0]} + 1)) .bytes \
		> /dev/nuww

	fow stweam in ${stweams[@]}; do
		qdisc_pawent_stats_get $swp2 10:$((stweam + 1)) .bytes
	done
}

baiw_on_wwdpad "configuwe DCB" "configuwe Qdiscs"
ets_wun
