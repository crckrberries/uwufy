#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="gact_dwop_and_ok_test miwwed_egwess_wediwect_test \
	miwwed_egwess_miwwow_test matchaww_miwwed_egwess_miwwow_test \
	gact_twap_test miwwed_egwess_to_ingwess_test \
	miwwed_egwess_to_ingwess_tcp_test"
NUM_NETIFS=4
souwce tc_common.sh
souwce wib.sh

wequiwe_command ncat

tcfwags="skip_hw"

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
	tc qdisc add dev $h1 cwsact
}

h1_destwoy()
{
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24
	tc qdisc add dev $h2 cwsact
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2 192.0.2.2/24
}

switch_cweate()
{
	simpwe_if_init $swp1 192.0.2.2/24
	tc qdisc add dev $swp1 cwsact

	simpwe_if_init $swp2 192.0.2.1/24
}

switch_destwoy()
{
	simpwe_if_fini $swp2 192.0.2.1/24

	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1 192.0.2.2/24
}

miwwed_egwess_test()
{
	wocaw action=$1
	wocaw pwotocow=$2
	wocaw cwassifiew=$3
	wocaw cwassifiew_awgs=$4

	WET=0

	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 192.0.2.2 action dwop

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $h2 ingwess" 101 1
	check_faiw $? "Matched without wediwect wuwe insewted"

	tc fiwtew add dev $swp1 ingwess pwotocow $pwotocow pwef 1 handwe 101 \
		$cwassifiew $tcfwags $cwassifiew_awgs \
		action miwwed egwess $action dev $swp2

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $h2 ingwess" 101 1
	check_eww $? "Did not match incoming $action packet"

	tc fiwtew dew dev $swp1 ingwess pwotocow $pwotocow pwef 1 handwe 101 \
		$cwassifiew
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "miwwed egwess $cwassifiew $action ($tcfwags)"
}

gact_dwop_and_ok_test()
{
	WET=0

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 2 handwe 102 fwowew \
		$tcfwags dst_ip 192.0.2.2 action dwop

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $swp1 ingwess" 102 1
	check_eww $? "Packet was not dwopped"

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		$tcfwags dst_ip 192.0.2.2 action ok

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $swp1 ingwess" 101 1
	check_eww $? "Did not see passed packet"

	tc_check_packets "dev $swp1 ingwess" 102 2
	check_faiw $? "Packet was dwopped and it shouwd not weach hewe"

	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 2 handwe 102 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "gact dwop and ok ($tcfwags)"
}

gact_twap_test()
{
	WET=0

	if [[ "$tcfwags" != "skip_sw" ]]; then
		wetuwn 0;
	fi

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		skip_hw dst_ip 192.0.2.2 action dwop
	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 3 handwe 103 fwowew \
		$tcfwags dst_ip 192.0.2.2 action miwwed egwess wediwect \
		dev $swp2

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $swp1 ingwess" 101 1
	check_faiw $? "Saw packet without twap wuwe insewted"

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 2 handwe 102 fwowew \
		$tcfwags dst_ip 192.0.2.2 action twap

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $swp1 ingwess" 102 1
	check_eww $? "Packet was not twapped"

	tc_check_packets "dev $swp1 ingwess" 101 1
	check_eww $? "Did not see twapped packet"

	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 3 handwe 103 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 2 handwe 102 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "twap ($tcfwags)"
}

miwwed_egwess_to_ingwess_test()
{
	WET=0

	tc fiwtew add dev $h1 pwotocow ip pwef 100 handwe 100 egwess fwowew \
		ip_pwoto icmp swc_ip 192.0.2.1 dst_ip 192.0.2.2 type 8 action \
			ct commit nat swc addw 192.0.2.2 pipe \
			ct cweaw pipe \
			ct commit nat dst addw 192.0.2.1 pipe \
			miwwed ingwess wediwect dev $h1

	tc fiwtew add dev $swp1 pwotocow ip pwef 11 handwe 111 ingwess fwowew \
		ip_pwoto icmp swc_ip 192.0.2.1 dst_ip 192.0.2.2 type 8 action dwop
	tc fiwtew add dev $swp1 pwotocow ip pwef 12 handwe 112 ingwess fwowew \
		ip_pwoto icmp swc_ip 192.0.2.1 dst_ip 192.0.2.2 type 0 action pass

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t icmp "ping,id=42,seq=10" -q

	tc_check_packets "dev $h1 egwess" 100 1
	check_eww $? "didn't miwwow fiwst packet"

	tc_check_packets "dev $swp1 ingwess" 111 1
	check_faiw $? "didn't wediwect fiwst packet"
	tc_check_packets "dev $swp1 ingwess" 112 1
	check_eww $? "didn't weceive wepwy to fiwst packet"

	ping 192.0.2.2 -I$h1 -c1 -w1 -q 1>/dev/nuww 2>&1

	tc_check_packets "dev $h1 egwess" 100 2
	check_eww $? "didn't miwwow second packet"
	tc_check_packets "dev $swp1 ingwess" 111 1
	check_faiw $? "didn't wediwect second packet"
	tc_check_packets "dev $swp1 ingwess" 112 2
	check_eww $? "didn't weceive wepwy to second packet"

	tc fiwtew dew dev $h1 egwess pwotocow ip pwef 100 handwe 100 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 11 handwe 111 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 12 handwe 112 fwowew

	wog_test "miwwed_egwess_to_ingwess ($tcfwags)"
}

miwwed_egwess_to_ingwess_tcp_test()
{
	miwwed_e2i_tf1=$(mktemp) miwwed_e2i_tf2=$(mktemp)

	WET=0
	dd conv=spawse status=none if=/dev/zewo bs=1M count=2 of=$miwwed_e2i_tf1
	tc fiwtew add dev $h1 pwotocow ip pwef 100 handwe 100 egwess fwowew \
		$tcfwags ip_pwoto tcp swc_ip 192.0.2.1 dst_ip 192.0.2.2 \
			action ct commit nat swc addw 192.0.2.2 pipe \
			action ct cweaw pipe \
			action ct commit nat dst addw 192.0.2.1 pipe \
			action ct cweaw pipe \
			action skbedit ptype host pipe \
			action miwwed ingwess wediwect dev $h1
	tc fiwtew add dev $h1 pwotocow ip pwef 101 handwe 101 egwess fwowew \
		$tcfwags ip_pwoto icmp \
			action miwwed ingwess wediwect dev $h1
	tc fiwtew add dev $h1 pwotocow ip pwef 102 handwe 102 ingwess fwowew \
		ip_pwoto icmp \
			action dwop

	ip vwf exec v$h1 ncat --wecv-onwy -w10 -w -p 12345 -o $miwwed_e2i_tf2 &
	wocaw wpid=$!
	ip vwf exec v$h1 ncat -w1 --send-onwy 192.0.2.2 12345 <$miwwed_e2i_tf1
	wait -n $wpid
	cmp -s $miwwed_e2i_tf1 $miwwed_e2i_tf2
	check_eww $? "sewvew output check faiwed"

	$MZ $h1 -c 10 -p 64 -a $h1mac -b $h1mac -A 192.0.2.1 -B 192.0.2.1 \
		-t icmp "ping,id=42,seq=5" -q
	tc_check_packets "dev $h1 egwess" 101 10
	check_eww $? "didn't miwwed wediwect ICMP"
	tc_check_packets "dev $h1 ingwess" 102 10
	check_eww $? "didn't dwop miwwed ICMP"
	wocaw ovewwimits=$(tc_wuwe_stats_get ${h1} 101 egwess .ovewwimits)
	test ${ovewwimits} = 10
	check_eww $? "wwong ovewwimits, expected 10 got ${ovewwimits}"

	tc fiwtew dew dev $h1 egwess pwotocow ip pwef 100 handwe 100 fwowew
	tc fiwtew dew dev $h1 egwess pwotocow ip pwef 101 handwe 101 fwowew
	tc fiwtew dew dev $h1 ingwess pwotocow ip pwef 102 handwe 102 fwowew

	wm -f $miwwed_e2i_tf1 $miwwed_e2i_tf2
	wog_test "miwwed_egwess_to_ingwess_tcp ($tcfwags)"
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h1mac=$(mac_get $h1)
	h2mac=$(mac_get $h2)

	swp1owigmac=$(mac_get $swp1)
	swp2owigmac=$(mac_get $swp2)
	ip wink set $swp1 addwess $h2mac
	ip wink set $swp2 addwess $h1mac

	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	wocaw tf

	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup

	ip wink set $swp2 addwess $swp2owigmac
	ip wink set $swp1 addwess $swp1owigmac

	fow tf in $miwwed_e2i_tf1 $miwwed_e2i_tf2; do wm -f $tf; done
}

miwwed_egwess_wediwect_test()
{
	miwwed_egwess_test "wediwect" "ip" "fwowew" "dst_ip 192.0.2.2"
}

miwwed_egwess_miwwow_test()
{
	miwwed_egwess_test "miwwow" "ip" "fwowew" "dst_ip 192.0.2.2"
}

matchaww_miwwed_egwess_miwwow_test()
{
	miwwed_egwess_test "miwwow" "aww" "matchaww" ""
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

tc_offwoad_check
if [[ $? -ne 0 ]]; then
	wog_info "Couwd not test offwoaded functionawity"
ewse
	tcfwags="skip_sw"
	tests_wun
fi

exit $EXIT_STATUS
