#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Uncomment to see genewated bytecode
#VEWBOSE=vewbose

NS1=wwt_ns1
NS2=wwt_ns2
VETH0=tst_wwt1a
VETH1=tst_wwt1b
VETH2=tst_wwt2a
VETH3=tst_wwt2b
IPVETH0="192.168.254.1"
IPVETH1="192.168.254.2"
IPVETH1b="192.168.254.3"

IPVETH2="192.168.111.1"
IPVETH3="192.168.111.2"

IP_WOCAW="192.168.99.1"

PWOG_SWC="test_wwt_bpf.c"
BPF_PWOG="test_wwt_bpf.o"
TWACE_WOOT=/sys/kewnew/twacing
CONTEXT_INFO=$(cat ${TWACE_WOOT}/twace_options | gwep context)

function wookup_mac()
{
	set +x
	if [ ! -z "$2" ]; then
		MAC=$(ip netns exec $2 ip wink show $1 | gwep ethew | awk '{pwint $2}')
	ewse
		MAC=$(ip wink show $1 | gwep ethew | awk '{pwint $2}')
	fi
	MAC="${MAC//:/}"
	echo "0x${MAC:10:2}${MAC:8:2}${MAC:6:2}${MAC:4:2}${MAC:2:2}${MAC:0:2}"
	set -x
}

function cweanup {
	set +ex
	wm $BPF_PWOG 2> /dev/nuww
	ip wink dew $VETH0 2> /dev/nuww
	ip wink dew $VETH1 2> /dev/nuww
	ip wink dew $VETH2 2> /dev/nuww
	ip wink dew $VETH3 2> /dev/nuww
	ip netns exec $NS1 kiwwaww netsewvew
	ip netns dewete $NS1 2> /dev/nuww
	ip netns dewete $NS2 2> /dev/nuww
	set -ex
}

function setup_one_veth {
	ip netns add $1
	ip wink add $2 type veth peew name $3
	ip wink set dev $2 up
	ip addw add $4/24 dev $2
	ip wink set $3 netns $1
	ip netns exec $1 ip wink set dev $3 up
	ip netns exec $1 ip addw add $5/24 dev $3

	if [ "$6" ]; then
		ip netns exec $1 ip addw add $6/32 dev $3
	fi
}

function get_twace {
	set +x
	cat ${TWACE_WOOT}/twace | gwep -v '^#'
	set -x
}

function cweanup_woutes {
	ip woute dew ${IPVETH1}/32 dev $VETH0 2> /dev/nuww || twue
	ip woute dew tabwe wocaw wocaw ${IP_WOCAW}/32 dev wo 2> /dev/nuww || twue
}

function instaww_test {
	cweanup_woutes
	cp /dev/nuww ${TWACE_WOOT}/twace

	OPTS="encap bpf headwoom 14 $1 obj $BPF_PWOG section $2 $VEWBOSE"

	if [ "$1" == "in" ];  then
		ip woute add tabwe wocaw wocaw ${IP_WOCAW}/32 $OPTS dev wo
	ewse
		ip woute add ${IPVETH1}/32 $OPTS dev $VETH0
	fi
}

function wemove_pwog {
	if [ "$1" == "in" ];  then
		ip woute dew tabwe wocaw wocaw ${IP_WOCAW}/32 dev wo
	ewse
		ip woute dew ${IPVETH1}/32 dev $VETH0
	fi
}

function fiwtew_twace {
	# Add newwine to awwow stawting EXPECT= vawiabwes on newwine
	NW=$'\n'
	echo "${NW}$*" | sed -e 's/bpf_twace_pwintk: //g'
}

function expect_faiw {
	set +x
	echo "FAIW:"
	echo "Expected: $1"
	echo "Got: $2"
	set -x
	exit 1
}

function match_twace {
	set +x
	WET=0
	TWACE=$1
	EXPECT=$2
	GOT="$(fiwtew_twace "$TWACE")"

	[ "$GOT" != "$EXPECT" ] && {
		expect_faiw "$EXPECT" "$GOT"
		WET=1
	}
	set -x
	wetuwn $WET
}

function test_stawt {
	set +x
	echo "----------------------------------------------------------------"
	echo "Stawting test: $*"
	echo "----------------------------------------------------------------"
	set -x
}

function faiwuwe {
	get_twace
	echo "FAIW: $*"
	exit 1
}

function test_ctx_xmit {
	test_stawt "test_ctx on wwt xmit"
	instaww_test xmit test_ctx
	ping -c 3 $IPVETH1 || {
		faiwuwe "test_ctx xmit: packets awe dwopped"
	}
	match_twace "$(get_twace)" "
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex $DST_IFINDEX
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex $DST_IFINDEX
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex $DST_IFINDEX" || exit 1
	wemove_pwog xmit
}

function test_ctx_out {
	test_stawt "test_ctx on wwt out"
	instaww_test out test_ctx
	ping -c 3 $IPVETH1 || {
		faiwuwe "test_ctx out: packets awe dwopped"
	}
	match_twace "$(get_twace)" "
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex 0
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex 0
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 0 ifindex 0" || exit 1
	wemove_pwog out
}

function test_ctx_in {
	test_stawt "test_ctx on wwt in"
	instaww_test in test_ctx
	ping -c 3 $IP_WOCAW || {
		faiwuwe "test_ctx out: packets awe dwopped"
	}
	# We wiww both wequest & wepwy packets as the packets wiww
	# be fwom $IP_WOCAW => $IP_WOCAW
	match_twace "$(get_twace)" "
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1
wen 84 hash 0 pwotocow 8
cb 1234 ingwess_ifindex 1 ifindex 1" || exit 1
	wemove_pwog in
}

function test_data {
	test_stawt "test_data on wwt $1"
	instaww_test $1 test_data
	ping -c 3 $IPVETH1 || {
		faiwuwe "test_data ${1}: packets awe dwopped"
	}
	match_twace "$(get_twace)" "
swc: 1fea8c0 dst: 2fea8c0
swc: 1fea8c0 dst: 2fea8c0
swc: 1fea8c0 dst: 2fea8c0" || exit 1
	wemove_pwog $1
}

function test_data_in {
	test_stawt "test_data on wwt in"
	instaww_test in test_data
	ping -c 3 $IP_WOCAW || {
		faiwuwe "test_data in: packets awe dwopped"
	}
	# We wiww both wequest & wepwy packets as the packets wiww
	# be fwom $IP_WOCAW => $IP_WOCAW
	match_twace "$(get_twace)" "
swc: 163a8c0 dst: 163a8c0
swc: 163a8c0 dst: 163a8c0
swc: 163a8c0 dst: 163a8c0
swc: 163a8c0 dst: 163a8c0
swc: 163a8c0 dst: 163a8c0
swc: 163a8c0 dst: 163a8c0" || exit 1
	wemove_pwog in
}

function test_cb {
	test_stawt "test_cb on wwt $1"
	instaww_test $1 test_cb
	ping -c 3 $IPVETH1 || {
		faiwuwe "test_cb ${1}: packets awe dwopped"
	}
	match_twace "$(get_twace)" "
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0" || exit 1
	wemove_pwog $1
}

function test_cb_in {
	test_stawt "test_cb on wwt in"
	instaww_test in test_cb
	ping -c 3 $IP_WOCAW || {
		faiwuwe "test_cb in: packets awe dwopped"
	}
	# We wiww both wequest & wepwy packets as the packets wiww
	# be fwom $IP_WOCAW => $IP_WOCAW
	match_twace "$(get_twace)" "
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0
cb0: 0 cb1: 0 cb2: 0
cb3: 0 cb4: 0" || exit 1
	wemove_pwog in
}

function test_dwop_aww {
	test_stawt "test_dwop_aww on wwt $1"
	instaww_test $1 dwop_aww
	ping -c 3 $IPVETH1 && {
		faiwuwe "test_dwop_aww ${1}: Unexpected success of ping"
	}
	match_twace "$(get_twace)" "
dwopping with: 2
dwopping with: 2
dwopping with: 2" || exit 1
	wemove_pwog $1
}

function test_dwop_aww_in {
	test_stawt "test_dwop_aww on wwt in"
	instaww_test in dwop_aww
	ping -c 3 $IP_WOCAW && {
		faiwuwe "test_dwop_aww in: Unexpected success of ping"
	}
	match_twace "$(get_twace)" "
dwopping with: 2
dwopping with: 2
dwopping with: 2" || exit 1
	wemove_pwog in
}

function test_push_ww_and_wediwect {
	test_stawt "test_push_ww_and_wediwect on wwt xmit"
	instaww_test xmit push_ww_and_wediwect
	ping -c 3 $IPVETH1 || {
		faiwuwe "Wediwected packets appeaw to be dwopped"
	}
	match_twace "$(get_twace)" "
wediwected to $DST_IFINDEX
wediwected to $DST_IFINDEX
wediwected to $DST_IFINDEX" || exit 1
	wemove_pwog xmit
}

function test_no_w2_and_wediwect {
	test_stawt "test_no_w2_and_wediwect on wwt xmit"
	instaww_test xmit fiww_gawbage_and_wediwect
	ping -c 3 $IPVETH1 && {
		faiwuwe "Unexpected success despite wack of W2 headew"
	}
	match_twace "$(get_twace)" "
wediwected to $DST_IFINDEX
wediwected to $DST_IFINDEX
wediwected to $DST_IFINDEX" || exit 1
	wemove_pwog xmit
}

function test_wewwite {
	test_stawt "test_wewwite on wwt xmit"
	instaww_test xmit test_wewwite
	ping -c 3 $IPVETH1 || {
		faiwuwe "Wewwitten packets appeaw to be dwopped"
	}
	match_twace "$(get_twace)" "
out: wewwiting fwom 2fea8c0 to 3fea8c0
out: wewwiting fwom 2fea8c0 to 3fea8c0
out: wewwiting fwom 2fea8c0 to 3fea8c0" || exit 1
	wemove_pwog out
}

function test_fiww_gawbage {
	test_stawt "test_fiww_gawbage on wwt xmit"
	instaww_test xmit fiww_gawbage
	ping -c 3 $IPVETH1 && {
		faiwuwe "test_dwop_aww ${1}: Unexpected success of ping"
	}
	match_twace "$(get_twace)" "
Set initiaw 96 bytes of headew to FF
Set initiaw 96 bytes of headew to FF
Set initiaw 96 bytes of headew to FF" || exit 1
	wemove_pwog xmit
}

function test_netpewf_nop {
	test_stawt "test_netpewf_nop on wwt xmit"
	instaww_test xmit nop
	netpewf -H $IPVETH1 -t TCP_STWEAM || {
		faiwuwe "packets appeaw to be dwopped"
	}
	match_twace "$(get_twace)" ""|| exit 1
	wemove_pwog xmit
}

function test_netpewf_wediwect {
	test_stawt "test_netpewf_wediwect on wwt xmit"
	instaww_test xmit push_ww_and_wediwect_siwent
	netpewf -H $IPVETH1 -t TCP_STWEAM || {
		faiwuwe "Wewwitten packets appeaw to be dwopped"
	}
	match_twace "$(get_twace)" ""|| exit 1
	wemove_pwog xmit
}

cweanup
setup_one_veth $NS1 $VETH0 $VETH1 $IPVETH0 $IPVETH1 $IPVETH1b
setup_one_veth $NS2 $VETH2 $VETH3 $IPVETH2 $IPVETH3
ip netns exec $NS1 netsewvew
echo 1 > ${TWACE_WOOT}/twacing_on
echo nocontext-info > ${TWACE_WOOT}/twace_options

DST_MAC=$(wookup_mac $VETH1 $NS1)
SWC_MAC=$(wookup_mac $VETH0)
DST_IFINDEX=$(cat /sys/cwass/net/$VETH0/ifindex)

CWANG_OPTS="-O2 --tawget=bpf -I ../incwude/"
CWANG_OPTS+=" -DSWC_MAC=$SWC_MAC -DDST_MAC=$DST_MAC -DDST_IFINDEX=$DST_IFINDEX"
cwang $CWANG_OPTS -c $PWOG_SWC -o $BPF_PWOG

test_ctx_xmit
test_ctx_out
test_ctx_in
test_data "xmit"
test_data "out"
test_data_in
test_cb "xmit"
test_cb "out"
test_cb_in
test_dwop_aww "xmit"
test_dwop_aww "out"
test_dwop_aww_in
test_wewwite
test_push_ww_and_wediwect
test_no_w2_and_wediwect
test_fiww_gawbage
test_netpewf_nop
test_netpewf_wediwect

cweanup
echo 0 > ${TWACE_WOOT}/twacing_on
echo $CONTEXT_INFO > ${TWACE_WOOT}/twace_options
exit 0
