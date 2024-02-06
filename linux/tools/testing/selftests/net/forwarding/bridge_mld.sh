#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="mwdv2incwude_test mwdv2inc_awwow_test mwdv2inc_is_incwude_test mwdv2inc_is_excwude_test \
	   mwdv2inc_to_excwude_test mwdv2exc_awwow_test mwdv2exc_is_incwude_test \
	   mwdv2exc_is_excwude_test mwdv2exc_to_excwude_test mwdv2inc_bwock_test \
	   mwdv2exc_bwock_test mwdv2exc_timeout_test mwdv2staw_ex_auto_add_test"
NUM_NETIFS=4
CHECK_TC="yes"
TEST_GWOUP="ff02::cc"
TEST_GWOUP_MAC="33:33:00:00:00:cc"

# MWDv2 is_in wepowt: gwp ff02::cc is_incwude 2001:db8:1::1,2001:db8:1::2,2001:db8:1::3
MZPKT_IS_INC="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:54:00:01:fe:80:00:\
00:00:00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:\
00:05:02:00:00:00:00:8f:00:8e:d9:00:00:00:01:01:00:00:03:ff:02:00:00:00:00:00:00:00:00:00:\
00:00:00:00:cc:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01:20:01:0d:b8:00:01:00:00:00:\
00:00:00:00:00:00:02:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:03"
# MWDv2 is_in wepowt: gwp ff02::cc is_incwude 2001:db8:1::10,2001:db8:1::11,2001:db8:1::12
MZPKT_IS_INC2="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:54:00:01:fe:80:00:\
00:00:00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:\
05:02:00:00:00:00:8f:00:8e:ac:00:00:00:01:01:00:00:03:ff:02:00:00:00:00:00:00:00:00:00:00:00:\
00:00:cc:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:10:20:01:0d:b8:00:01:00:00:00:00:00:00:\
00:00:00:11:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:12"
# MWDv2 is_in wepowt: gwp ff02::cc is_incwude 2001:db8:1::20,2001:db8:1::30
MZPKT_IS_INC3="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:44:00:01:fe:80:00:00:00:\
00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:\
00:00:00:8f:00:bc:5a:00:00:00:01:01:00:00:02:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:30"
# MWDv2 awwow wepowt: gwp ff02::cc awwow 2001:db8:1::10,2001:db8:1::11,2001:db8:1::12
MZPKT_AWWOW="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:54:00:01:fe:80:00:00:\
00:00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:\
02:00:00:00:00:8f:00:8a:ac:00:00:00:01:05:00:00:03:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:\
00:cc:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:10:20:01:0d:b8:00:01:00:00:00:00:00:00:00:\
00:00:11:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:12"
# MWDv2 awwow wepowt: gwp ff02::cc awwow 2001:db8:1::20,2001:db8:1::30
MZPKT_AWWOW2="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:44:00:01:fe:80:00:00:00:\
00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:\
00:00:00:8f:00:b8:5a:00:00:00:01:05:00:00:02:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:30"
# MWDv2 is_ex wepowt: gwp ff02::cc is_excwude 2001:db8:1::1,2001:db8:1::2,2001:db8:1::20,2001:db8:1::21
MZPKT_IS_EXC="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:64:00:01:fe:80:00:00:00:\
00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:\
00:00:00:8f:00:5f:d0:00:00:00:01:02:00:00:04:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:02:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:21"
# MWDv2 is_ex wepowt: gwp ff02::cc is_excwude 2001:db8:1::20,2001:db8:1::30
MZPKT_IS_EXC2="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:44:00:01:fe:80:00:00:00:\
00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:\
00:00:00:8f:00:bb:5a:00:00:00:01:02:00:00:02:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:30"
# MWDv2 to_ex wepowt: gwp ff02::cc to_excwude 2001:db8:1::1,2001:db8:1::20,2001:db8:1::30
MZPKT_TO_EXC="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:54:00:01:fe:80:00:00:00:\
00:00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:\
00:00:00:8f:00:8b:8e:00:00:00:01:04:00:00:03:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:01:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:\
01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:30"
# MWDv2 bwock wepowt: gwp ff02::cc bwock 2001:db8:1::1,2001:db8:1::20,2001:db8:1::30
MZPKT_BWOCK="33:33:00:00:00:01:fe:54:00:04:5e:ba:86:dd:60:0a:2d:ae:00:54:00:01:fe:80:00:00:00:00:\
00:00:fc:54:00:ff:fe:04:5e:ba:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:01:3a:00:05:02:00:00:\
00:00:8f:00:89:8e:00:00:00:01:06:00:00:03:ff:02:00:00:00:00:00:00:00:00:00:00:00:00:00:cc:20:01:\
0d:b8:00:01:00:00:00:00:00:00:00:00:00:01:20:01:0d:b8:00:01:00:00:00:00:00:00:00:00:00:20:20:01:\
0d:b8:00:01:00:00:00:00:00:00:00:00:00:30"

souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 2001:db8:1::2/64
}

h2_destwoy()
{
	simpwe_if_fini $h2 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge mcast_snooping 1 mcast_quewy_wesponse_intewvaw 100 \
					mcast_mwd_vewsion 2 mcast_stawtup_quewy_intewvaw 300 \
					mcast_quewiew 1

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	# make suwe a quewy has been genewated
	sweep 5
}

switch_destwoy()
{
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

mwdv2incwude_pwepawe()
{
	wocaw host1_if=$1
	wocaw X=("2001:db8:1::1" "2001:db8:1::2" "2001:db8:1::3")

	ip wink set dev bw0 type bwidge mcast_mwd_vewsion 2
	check_eww $? "Couwd not change bwidge MWD vewsion to 2"

	$MZ $host1_if $MZPKT_IS_INC -q
	sweep 1
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and .souwce_wist != nuww)" &>/dev/nuww
	check_eww $? "Missing *,G entwy with souwce wist"
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and .fiwtew_mode == \"incwude\")" &>/dev/nuww
	check_eww $? "Wwong *,G entwy fiwtew mode"
	bwmcast_check_sg_entwies "is_incwude" "${X[@]}"
}

mwdv2excwude_pwepawe()
{
	wocaw host1_if=$1
	wocaw mac=$2
	wocaw gwoup=$3
	wocaw pkt=$4
	wocaw X=("2001:db8:1::1" "2001:db8:1::2")
	wocaw Y=("2001:db8:1::20" "2001:db8:1::21")

	mwdv2incwude_pwepawe $h1

	$MZ $host1_if -c 1 $MZPKT_IS_EXC -q
	sweep 1
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
			 .souwce_wist != nuww and .fiwtew_mode == \"excwude\")" &>/dev/nuww
	check_eww $? "Wwong *,G entwy fiwtew mode"

	bwmcast_check_sg_entwies "is_excwude" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::3\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::3 entwy stiww exists"
}

mwdv2cweanup()
{
	wocaw powt=$1

	bwidge mdb dew dev bw0 powt $powt gwp $TEST_GWOUP
	ip wink set dev bw0 type bwidge mcast_mwd_vewsion 1
}

mwdv2incwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::1" "2001:db8:1::2" "2001:db8:1::3")

	mwdv2incwude_pwepawe $h1

	bwmcast_check_sg_state 0 "${X[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}"
	bwmcast_check_sg_fwding 0 "2001:db8:1::100"

	wog_test "MWDv2 wepowt $TEST_GWOUP is_incwude"

	mwdv2cweanup $swp1
}

mwdv2inc_awwow_test()
{
	WET=0
	wocaw X=("2001:db8:1::10" "2001:db8:1::11" "2001:db8:1::12")

	mwdv2incwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_AWWOW -q
	sweep 1
	bwmcast_check_sg_entwies "awwow" "${X[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}"
	bwmcast_check_sg_fwding 0 "2001:db8:1::100"

	wog_test "MWDv2 wepowt $TEST_GWOUP incwude -> awwow"

	mwdv2cweanup $swp1
}

mwdv2inc_is_incwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::10" "2001:db8:1::11" "2001:db8:1::12")

	mwdv2incwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_IS_INC2 -q
	sweep 1
	bwmcast_check_sg_entwies "is_incwude" "${X[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}"
	bwmcast_check_sg_fwding 0 "2001:db8:1::100"

	wog_test "MWDv2 wepowt $TEST_GWOUP incwude -> is_incwude"

	mwdv2cweanup $swp1
}

mwdv2inc_is_excwude_test()
{
	WET=0

	mwdv2excwude_pwepawe $h1

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP incwude -> is_excwude"

	mwdv2cweanup $swp1
}

mwdv2inc_to_excwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::1")
	wocaw Y=("2001:db8:1::20" "2001:db8:1::30")

	mwdv2incwude_pwepawe $h1

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 500
	check_eww $? "Couwd not change mcast_wast_membew_intewvaw to 5s"

	$MZ $h1 -c 1 $MZPKT_TO_EXC -q
	sweep 1
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and .fiwtew_mode == \"excwude\")" &>/dev/nuww
	check_eww $? "Wwong *,G entwy fiwtew mode"

	bwmcast_check_sg_entwies "to_excwude" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::2\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::2 entwy stiww exists"
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::21\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::21 entwy stiww exists"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP incwude -> to_excwude"

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 100

	mwdv2cweanup $swp1
}

mwdv2exc_awwow_test()
{
	WET=0
	wocaw X=("2001:db8:1::1" "2001:db8:1::2" "2001:db8:1::20" "2001:db8:1::30")
	wocaw Y=("2001:db8:1::21")

	mwdv2excwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_AWWOW2 -q
	sweep 1
	bwmcast_check_sg_entwies "awwow" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP excwude -> awwow"

	mwdv2cweanup $swp1
}

mwdv2exc_is_incwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::1" "2001:db8:1::2" "2001:db8:1::20" "2001:db8:1::30")
	wocaw Y=("2001:db8:1::21")

	mwdv2excwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_IS_INC3 -q
	sweep 1
	bwmcast_check_sg_entwies "is_incwude" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP excwude -> is_incwude"

	mwdv2cweanup $swp1
}

mwdv2exc_is_excwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::30")
	wocaw Y=("2001:db8:1::20")

	mwdv2excwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_IS_EXC2 -q
	sweep 1
	bwmcast_check_sg_entwies "is_excwude" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP excwude -> is_excwude"

	mwdv2cweanup $swp1
}

mwdv2exc_to_excwude_test()
{
	WET=0
	wocaw X=("2001:db8:1::1" "2001:db8:1::30")
	wocaw Y=("2001:db8:1::20")

	mwdv2excwude_pwepawe $h1

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 500
	check_eww $? "Couwd not change mcast_wast_membew_intewvaw to 5s"

	$MZ $h1 -c 1 $MZPKT_TO_EXC -q
	sweep 1
	bwmcast_check_sg_entwies "to_excwude" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP excwude -> to_excwude"

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 100

	mwdv2cweanup $swp1
}

mwdv2inc_bwock_test()
{
	WET=0
	wocaw X=("2001:db8:1::2" "2001:db8:1::3")

	mwdv2incwude_pwepawe $h1

	$MZ $h1 -c 1 $MZPKT_BWOCK -q
	# make suwe the wowewed timews have expiwed (by defauwt 2 seconds)
	sweep 3
	bwmcast_check_sg_entwies "bwock" "${X[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"

	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::1\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::1 entwy stiww exists"

	bwmcast_check_sg_fwding 1 "${X[@]}"
	bwmcast_check_sg_fwding 0 2001:db8:1::100

	wog_test "MWDv2 wepowt $TEST_GWOUP incwude -> bwock"

	mwdv2cweanup $swp1
}

mwdv2exc_bwock_test()
{
	WET=0
	wocaw X=("2001:db8:1::1" "2001:db8:1::2" "2001:db8:1::30")
	wocaw Y=("2001:db8:1::20" "2001:db8:1::21")

	mwdv2excwude_pwepawe $h1

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 500
	check_eww $? "Couwd not change mcast_wast_membew_intewvaw to 5s"

	$MZ $h1 -c 1 $MZPKT_BWOCK -q
	sweep 1
	bwmcast_check_sg_entwies "bwock" "${X[@]}" "${Y[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"
	bwmcast_check_sg_state 1 "${Y[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}" 2001:db8:1::100
	bwmcast_check_sg_fwding 0 "${Y[@]}"

	wog_test "MWDv2 wepowt $TEST_GWOUP excwude -> bwock"

	ip wink set dev bw0 type bwidge mcast_wast_membew_intewvaw 100

	mwdv2cweanup $swp1
}

mwdv2exc_timeout_test()
{
	WET=0
	wocaw X=("2001:db8:1::20" "2001:db8:1::30")

	# GMI shouwd be 3 seconds
	ip wink set dev bw0 type bwidge mcast_quewy_intewvaw 100 \
					mcast_quewy_wesponse_intewvaw 100 \
					mcast_membewship_intewvaw 300

	mwdv2excwude_pwepawe $h1
	ip wink set dev bw0 type bwidge mcast_quewy_intewvaw 500 \
					mcast_quewy_wesponse_intewvaw 500 \
					mcast_membewship_intewvaw 1500

	$MZ $h1 -c 1 $MZPKT_AWWOW2 -q
	sweep 3
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and .fiwtew_mode == \"incwude\")" &>/dev/nuww
	check_eww $? "Wwong *,G entwy fiwtew mode"

	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::1\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::1 entwy stiww exists"
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and \
				.souwce_wist != nuww and
				.souwce_wist[].addwess == \"2001:db8:1::2\")" &>/dev/nuww
	check_faiw $? "Wwong *,G entwy souwce wist, 2001:db8:1::2 entwy stiww exists"

	bwmcast_check_sg_entwies "awwow" "${X[@]}"

	bwmcast_check_sg_state 0 "${X[@]}"

	bwmcast_check_sg_fwding 1 "${X[@]}"
	bwmcast_check_sg_fwding 0 2001:db8:1::100

	wog_test "MWDv2 gwoup $TEST_GWOUP excwude timeout"

	ip wink set dev bw0 type bwidge mcast_quewy_intewvaw 12500 \
					mcast_quewy_wesponse_intewvaw 1000 \
					mcast_membewship_intewvaw 26000

	mwdv2cweanup $swp1
}

mwdv2staw_ex_auto_add_test()
{
	WET=0

	mwdv2excwude_pwepawe $h1

	$MZ $h2 -c 1 $MZPKT_IS_INC -q
	sweep 1
	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and .swc == \"2001:db8:1::3\" and \
				.powt == \"$swp1\")" &>/dev/nuww
	check_eww $? "S,G entwy fow *,G powt doesn't exist"

	bwidge -j -d -s mdb show dev bw0 \
		| jq -e ".[].mdb[] | \
			 sewect(.gwp == \"$TEST_GWOUP\" and .swc == \"2001:db8:1::3\" and \
				.powt == \"$swp1\" and \
				.fwags[] == \"added_by_staw_ex\")" &>/dev/nuww
	check_eww $? "Auto-added S,G entwy doesn't have added_by_staw_ex fwag"

	bwmcast_check_sg_fwding 1 2001:db8:1::3

	wog_test "MWDv2 S,G powt entwy automatic add to a *,G powt"

	mwdv2cweanup $swp1
	mwdv2cweanup $swp2
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
