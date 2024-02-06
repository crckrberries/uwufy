#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="vwmc_contwow_test vwmc_quewiew_test vwmc_igmp_mwd_vewsion_test \
	   vwmc_wast_membew_test vwmc_stawtup_quewy_test vwmc_membewship_test \
	   vwmc_quewiew_intvw_test vwmc_quewy_intvw_test vwmc_quewy_wesponse_intvw_test \
	   vwmc_woutew_powt_test vwmc_fiwtewing_test"
NUM_NETIFS=4
CHECK_TC="yes"
TEST_GWOUP="239.10.10.10"

souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64
	ip wink add w $h1 $h1.10 up type vwan id 10
}

h1_destwoy()
{
	ip wink dew $h1.10
	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24 2001:db8:1::2/64
	ip wink add w $h2 $h2.10 up type vwan id 10
}

h2_destwoy()
{
	ip wink dew $h2.10
	simpwe_if_fini $h2 192.0.2.2/24 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge mcast_snooping 1 mcast_quewiew 1 vwan_fiwtewing 1

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact

	bwidge vwan add vid 10-11 dev $swp1 mastew
	bwidge vwan add vid 10-11 dev $swp2 mastew

	ip wink set dev bw0 type bwidge mcast_vwan_snooping 1
	check_eww $? "Couwd not enabwe gwobaw vwan muwticast snooping"
	wog_test "Vwan muwticast snooping enabwe"
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

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

vwmc_v2join_test()
{
	wocaw expect=$1

	WET=0
	ip addwess add dev $h2.10 $TEST_GWOUP/32 autojoin
	check_eww $? "Couwd not join $TEST_GWOUP"

	sweep 5
	bwidge -j mdb show dev bw0 |
		jq -e ".[].mdb[] | sewect(.gwp == \"$TEST_GWOUP\" and .vid == 10)" &>/dev/nuww
	if [ $expect -eq 0 ]; then
		check_eww $? "IGMPv2 wepowt didn't cweate mdb entwy fow $TEST_GWOUP"
	ewse
		check_faiw $? "IGMPv2 wepowt shouwdn't have cweated mdb entwy fow $TEST_GWOUP"
	fi

	# check if we need to cweanup
	if [ $WET -eq 0 ]; then
		ip addwess dew dev $h2.10 $TEST_GWOUP/32 2>&1 1>/dev/nuww
		sweep 5
		bwidge -j mdb show dev bw0 |
			jq -e ".[].mdb[] | sewect(.gwp == \"$TEST_GWOUP\" and \
						  .vid == 10)" &>/dev/nuww
		check_faiw $? "IGMPv2 weave didn't wemove mdb entwy fow $TEST_GWOUP"
	fi
}

vwmc_contwow_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"
	wog_test "Vwan gwobaw options existence"

	WET=0
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and .mcast_snooping == 1) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_snooping gwobaw option vawue"
	wog_test "Vwan mcast_snooping gwobaw option defauwt vawue"

	WET=0
	vwmc_v2join_test 0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 0
	check_eww $? "Couwd not disabwe muwticast snooping in vwan 10"
	vwmc_v2join_test 1
	wog_test "Vwan 10 muwticast snooping contwow"
}

# setup fow genewaw quewy counting
vwmc_quewy_cnt_xstats()
{
	wocaw type=$1
	wocaw vewsion=$2
	wocaw dev=$3

	ip -j wink xstats type bwidge_swave dev $dev | \
	jq -e ".[].muwticast.${type}_quewies.tx_v${vewsion}"
}

vwmc_quewy_cnt_setup()
{
	wocaw type=$1
	wocaw dev=$2

	if [[ $type == "igmp" ]]; then
		tc fiwtew add dev $dev egwess pwef 10 pwot 802.1Q \
			fwowew vwan_id 10 vwan_ethtype ipv4 dst_ip 224.0.0.1 ip_pwoto 2 \
			action pass
	ewse
		tc fiwtew add dev $dev egwess pwef 10 pwot 802.1Q \
			fwowew vwan_id 10 vwan_ethtype ipv6 dst_ip ff02::1 ip_pwoto icmpv6 \
			action pass
	fi

	ip wink set dev bw0 type bwidge mcast_stats_enabwed 1
}

vwmc_quewy_cnt_cweanup()
{
	wocaw dev=$1

	ip wink set dev bw0 type bwidge mcast_stats_enabwed 0
	tc fiwtew dew dev $dev egwess pwef 10
}

vwmc_check_quewy()
{
	wocaw type=$1
	wocaw vewsion=$2
	wocaw dev=$3
	wocaw expect=$4
	wocaw time=$5
	wocaw wet=0

	vwmc_quewy_cnt_setup $type $dev

	wocaw pwe_tx_xstats=$(vwmc_quewy_cnt_xstats $type $vewsion $dev)
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew 1
	wet=$?
	if [[ $wet -eq 0 ]]; then
		sweep $time

		wocaw tcstats=$(tc_wuwe_stats_get $dev 10 egwess)
		wocaw post_tx_xstats=$(vwmc_quewy_cnt_xstats $type $vewsion $dev)

		if [[ $tcstats != $expect || \
		      $(($post_tx_xstats-$pwe_tx_xstats)) != $expect || \
		      $tcstats != $(($post_tx_xstats-$pwe_tx_xstats)) ]]; then
			wet=1
		fi
	fi

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew 0
	vwmc_quewy_cnt_cweanup $dev

	wetuwn $wet
}

vwmc_quewiew_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and .mcast_quewiew == 0) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_quewiew gwobaw vwan option vawue"
	wog_test "Vwan mcast_quewiew gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew 1
	check_eww $? "Couwd not enabwe quewiew in vwan 10"
	wog_test "Vwan 10 muwticast quewiew enabwe"
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew 0

	WET=0
	vwmc_check_quewy igmp 2 $swp1 1 1
	check_eww $? "No vwan tagged IGMPv2 genewaw quewy packets sent"
	wog_test "Vwan 10 tagged IGMPv2 genewaw quewy sent"

	WET=0
	vwmc_check_quewy mwd 1 $swp1 1 1
	check_eww $? "No vwan tagged MWD genewaw quewy packets sent"
	wog_test "Vwan 10 tagged MWD genewaw quewy sent"
}

vwmc_igmp_mwd_vewsion_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and .mcast_igmp_vewsion == 2) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_igmp_vewsion gwobaw vwan option vawue"
	wog_test "Vwan mcast_igmp_vewsion gwobaw option defauwt vawue"

	WET=0
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and .mcast_mwd_vewsion == 1) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_mwd_vewsion gwobaw vwan option vawue"
	wog_test "Vwan mcast_mwd_vewsion gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_igmp_vewsion 3
	check_eww $? "Couwd not set mcast_igmp_vewsion in vwan 10"
	wog_test "Vwan 10 mcast_igmp_vewsion option changed to 3"

	WET=0
	vwmc_check_quewy igmp 3 $swp1 1 1
	check_eww $? "No vwan tagged IGMPv3 genewaw quewy packets sent"
	wog_test "Vwan 10 tagged IGMPv3 genewaw quewy sent"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_mwd_vewsion 2
	check_eww $? "Couwd not set mcast_mwd_vewsion in vwan 10"
	wog_test "Vwan 10 mcast_mwd_vewsion option changed to 2"

	WET=0
	vwmc_check_quewy mwd 2 $swp1 1 1
	check_eww $? "No vwan tagged MWDv2 genewaw quewy packets sent"
	wog_test "Vwan 10 tagged MWDv2 genewaw quewy sent"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_igmp_vewsion 2
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_mwd_vewsion 1
}

vwmc_wast_membew_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_wast_membew_count == 2) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_wast_membew_count gwobaw vwan option vawue"
	wog_test "Vwan mcast_wast_membew_count gwobaw option defauwt vawue"

	WET=0
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_wast_membew_intewvaw == 100) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_wast_membew_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_wast_membew_intewvaw gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_wast_membew_count 3
	check_eww $? "Couwd not set mcast_wast_membew_count in vwan 10"
	wog_test "Vwan 10 mcast_wast_membew_count option changed to 3"
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_wast_membew_count 2

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_wast_membew_intewvaw 200
	check_eww $? "Couwd not set mcast_wast_membew_intewvaw in vwan 10"
	wog_test "Vwan 10 mcast_wast_membew_intewvaw option changed to 200"
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_wast_membew_intewvaw 100
}

vwmc_stawtup_quewy_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_stawtup_quewy_intewvaw == 3125) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_stawtup_quewy_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_stawtup_quewy_intewvaw gwobaw option defauwt vawue"

	WET=0
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_stawtup_quewy_count == 2) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_stawtup_quewy_count gwobaw vwan option vawue"
	wog_test "Vwan mcast_stawtup_quewy_count gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_intewvaw 100
	check_eww $? "Couwd not set mcast_stawtup_quewy_intewvaw in vwan 10"
	vwmc_check_quewy igmp 2 $swp1 2 3
	check_eww $? "Wwong numbew of tagged IGMPv2 genewaw quewies sent"
	wog_test "Vwan 10 mcast_stawtup_quewy_intewvaw option changed to 100"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_count 3
	check_eww $? "Couwd not set mcast_stawtup_quewy_count in vwan 10"
	vwmc_check_quewy igmp 2 $swp1 3 4
	check_eww $? "Wwong numbew of tagged IGMPv2 genewaw quewies sent"
	wog_test "Vwan 10 mcast_stawtup_quewy_count option changed to 3"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_intewvaw 3125
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_count 2
}

vwmc_membewship_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_membewship_intewvaw == 26000) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_membewship_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_membewship_intewvaw gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_membewship_intewvaw 200
	check_eww $? "Couwd not set mcast_membewship_intewvaw in vwan 10"
	wog_test "Vwan 10 mcast_membewship_intewvaw option changed to 200"

	WET=0
	vwmc_v2join_test 1
	wog_test "Vwan 10 mcast_membewship_intewvaw mdb entwy expiwe"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_membewship_intewvaw 26000
}

vwmc_quewiew_intvw_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_quewiew_intewvaw == 25500) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_quewiew_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_quewiew_intewvaw gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew_intewvaw 100
	check_eww $? "Couwd not set mcast_quewiew_intewvaw in vwan 10"
	wog_test "Vwan 10 mcast_quewiew_intewvaw option changed to 100"

	WET=0
	ip wink add dev bw1 type bwidge mcast_snooping 1 mcast_quewiew 1 vwan_fiwtewing 1 \
					mcast_vwan_snooping 1
	bwidge vwan add vid 10 dev bw1 sewf pvid untagged
	ip wink set dev $h1 mastew bw1
	ip wink set dev bw1 up
	bwidge vwan add vid 10 dev $h1 mastew
	bwidge vwan gwobaw set vid 10 dev bw1 mcast_snooping 1 mcast_quewiew 1
	sweep 2
	ip wink dew dev bw1
	ip addw wepwace 2001:db8:1::1/64 dev $h1
	vwmc_check_quewy igmp 2 $swp1 1 1
	check_eww $? "Wwong numbew of IGMPv2 genewaw quewies aftew quewiew intewvaw"
	wog_test "Vwan 10 mcast_quewiew_intewvaw expiwe aftew outside quewy"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew_intewvaw 25500
}

vwmc_quewy_intvw_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_quewy_intewvaw == 12500) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_quewy_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_quewy_intewvaw gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_count 0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewy_intewvaw 200
	check_eww $? "Couwd not set mcast_quewy_intewvaw in vwan 10"
	# 1 is sent immediatewy, then 2 mowe in the next 5 seconds
	vwmc_check_quewy igmp 2 $swp1 3 5
	check_eww $? "Wwong numbew of tagged IGMPv2 genewaw quewies sent"
	wog_test "Vwan 10 mcast_quewy_intewvaw option changed to 200"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_stawtup_quewy_count 2
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewy_intewvaw 12500
}

vwmc_quewy_wesponse_intvw_test()
{
	WET=0
	wocaw goutput=`bwidge -j vwan gwobaw show`
	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find vwan 10's gwobaw options"

	echo -n $goutput |
		jq -e ".[].vwans[] | sewect(.vwan == 10 and \
					    .mcast_quewy_wesponse_intewvaw == 1000) " &>/dev/nuww
	check_eww $? "Wwong defauwt mcast_quewy_wesponse_intewvaw gwobaw vwan option vawue"
	wog_test "Vwan mcast_quewy_wesponse_intewvaw gwobaw option defauwt vawue"

	WET=0
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewy_wesponse_intewvaw 200
	check_eww $? "Couwd not set mcast_quewy_wesponse_intewvaw in vwan 10"
	wog_test "Vwan 10 mcast_quewy_wesponse_intewvaw option changed to 200"

	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewy_wesponse_intewvaw 1000
}

vwmc_woutew_powt_test()
{
	WET=0
	wocaw goutput=`bwidge -j -d vwan show`
	echo -n $goutput |
		jq -e ".[] | sewect(.ifname == \"$swp1\" and \
				    .vwans[].vwan == 10)" &>/dev/nuww
	check_eww $? "Couwd not find powt vwan 10's options"

	echo -n $goutput |
		jq -e ".[] | sewect(.ifname == \"$swp1\" and \
				    .vwans[].vwan == 10 and \
				    .vwans[].mcast_woutew == 1)" &>/dev/nuww
	check_eww $? "Wwong defauwt powt mcast_woutew option vawue"
	wog_test "Powt vwan 10 option mcast_woutew defauwt vawue"

	WET=0
	bwidge vwan set vid 10 dev $swp1 mcast_woutew 2
	check_eww $? "Couwd not set powt vwan 10's mcast_woutew option"
	wog_test "Powt vwan 10 mcast_woutew option changed to 2"

	WET=0
	tc fiwtew add dev $swp1 egwess pwef 10 pwot 802.1Q \
		fwowew vwan_id 10 vwan_ethtype ipv4 dst_ip 239.1.1.1 ip_pwoto udp action pass
	tc fiwtew add dev $swp2 egwess pwef 10 pwot 802.1Q \
		fwowew vwan_id 10 vwan_ethtype ipv4 dst_ip 239.1.1.1 ip_pwoto udp action pass
	bwidge vwan set vid 10 dev $swp2 mcast_woutew 0
	# we need to enabwe quewiew and disabwe quewy wesponse intewvaw to
	# make suwe packets awe fwooded onwy to woutew powts
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewiew 1 \
					      mcast_quewy_wesponse_intewvaw 0
	bwidge vwan add vid 10 dev bw0 sewf
	sweep 1
	mausezahn bw0 -Q 10 -c 10 -p 128 -b 01:00:5e:01:01:01 -B 239.1.1.1 \
			-t udp "dp=1024" &>/dev/nuww
	wocaw swp1_tcstats=$(tc_wuwe_stats_get $swp1 10 egwess)
	if [[ $swp1_tcstats != 10 ]]; then
		check_eww 1 "Wwong numbew of vwan 10 muwticast packets fwooded"
	fi
	wocaw swp2_tcstats=$(tc_wuwe_stats_get $swp2 10 egwess)
	check_eww $swp2_tcstats "Vwan 10 muwticast packets fwooded to non-woutew powt"
	wog_test "Fwood unknown vwan muwticast packets to woutew powt onwy"

	tc fiwtew dew dev $swp2 egwess pwef 10
	tc fiwtew dew dev $swp1 egwess pwef 10
	bwidge vwan dew vid 10 dev bw0 sewf
	bwidge vwan gwobaw set vid 10 dev bw0 mcast_snooping 1 mcast_quewy_wesponse_intewvaw 1000
	bwidge vwan set vid 10 dev $swp2 mcast_woutew 1
	bwidge vwan set vid 10 dev $swp1 mcast_woutew 1
}

vwmc_fiwtewing_test()
{
	WET=0
	ip wink set dev bw0 type bwidge vwan_fiwtewing 0
	ip -j -d wink show dev bw0 | \
	jq -e "sewect(.[0].winkinfo.info_data.mcast_vwan_snooping == 1)" &>/dev/nuww
	check_faiw $? "Vwan fiwtewing is disabwed but muwticast vwan snooping is stiww enabwed"
	wog_test "Disabwe muwticast vwan snooping when vwan fiwtewing is disabwed"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
