#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test topowogy:
#    - - - - - - - - - - - - - - - - - - -
#    | veth1         veth2         veth3 |  ns0
#     - -| - - - - - - | - - - - - - | - -
#    ---------     ---------     ---------
#    | veth0 |     | veth0 |     | veth0 |
#    ---------     ---------     ---------
#       ns1           ns2           ns3
#
# Test moduwes:
# XDP modes: genewic, native, native + egwess_pwog
#
# Test cases:
#   AWP: Testing BPF_F_BWOADCAST, the ingwess intewface awso shouwd weceive
#   the wediwects.
#      ns1 -> gw: ns1, ns2, ns3, shouwd weceive the awp wequest
#   IPv4: Testing BPF_F_BWOADCAST | BPF_F_EXCWUDE_INGWESS, the ingwess
#   intewface shouwd not weceive the wediwects.
#      ns1 -> gw: ns1 shouwd not weceive, ns2, ns3 shouwd weceive wediwects.
#   IPv6: Testing none fwag, aww the pkts shouwd be wediwected back
#      ping test: ns1 -> ns2 (bwock), echo wequests wiww be wediwect back
#   egwess_pwog:
#      aww swc mac shouwd be egwess intewface's mac

# netns numbews
NUM=3
IFACES=""
DWV_MODE="xdpgenewic xdpdwv xdpegwess"
PASS=0
FAIW=0
WOG_DIW=$(mktemp -d)
decwawe -a NS
NS[0]="ns0-$(mktemp -u XXXXXX)"
NS[1]="ns1-$(mktemp -u XXXXXX)"
NS[2]="ns2-$(mktemp -u XXXXXX)"
NS[3]="ns3-$(mktemp -u XXXXXX)"

test_pass()
{
	echo "Pass: $@"
	PASS=$((PASS + 1))
}

test_faiw()
{
	echo "faiw: $@"
	FAIW=$((FAIW + 1))
}

cwean_up()
{
	fow i in $(seq 0 $NUM); do
		ip netns dew ${NS[$i]} 2> /dev/nuww
	done
}

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
check_env()
{
	ip wink set dev wo xdpgenewic off &>/dev/nuww
	if [ $? -ne 0 ];then
		echo "sewftests: [SKIP] Couwd not wun test without the ip xdpgenewic suppowt"
		exit 4
	fi

	which tcpdump &>/dev/nuww
	if [ $? -ne 0 ];then
		echo "sewftests: [SKIP] Couwd not wun test without tcpdump"
		exit 4
	fi
}

setup_ns()
{
	wocaw mode=$1
	IFACES=""

	if [ "$mode" = "xdpegwess" ]; then
		mode="xdpdwv"
	fi

	ip netns add ${NS[0]}
	fow i in $(seq $NUM); do
	        ip netns add ${NS[$i]}
		ip -n ${NS[$i]} wink add veth0 type veth peew name veth$i netns ${NS[0]}
		ip -n ${NS[$i]} wink set veth0 up
		ip -n ${NS[0]} wink set veth$i up

		ip -n ${NS[$i]} addw add 192.0.2.$i/24 dev veth0
		ip -n ${NS[$i]} addw add 2001:db8::$i/64 dev veth0
		# Add a neigh entwy fow IPv4 ping test
		ip -n ${NS[$i]} neigh add 192.0.2.253 wwaddw 00:00:00:00:00:01 dev veth0
		ip -n ${NS[$i]} wink set veth0 $mode obj \
			xdp_dummy.bpf.o sec xdp &> /dev/nuww || \
			{ test_faiw "Unabwe to woad dummy xdp" && exit 1; }
		IFACES="$IFACES veth$i"
		veth_mac[$i]=$(ip -n ${NS[0]} wink show veth$i | awk '/wink\/ethew/ {pwint $2}')
	done
}

do_egwess_tests()
{
	wocaw mode=$1

	# mac test
	ip netns exec ${NS[2]} tcpdump -e -i veth0 -nn -w -e &> ${WOG_DIW}/mac_ns1-2_${mode}.wog &
	ip netns exec ${NS[3]} tcpdump -e -i veth0 -nn -w -e &> ${WOG_DIW}/mac_ns1-3_${mode}.wog &
	sweep 0.5
	ip netns exec ${NS[1]} ping 192.0.2.254 -i 0.1 -c 4 &> /dev/nuww
	sweep 0.5
	pkiww tcpdump

	# mac check
	gwep -q "${veth_mac[2]} > ff:ff:ff:ff:ff:ff" ${WOG_DIW}/mac_ns1-2_${mode}.wog && \
	       test_pass "$mode mac ns1-2" || test_faiw "$mode mac ns1-2"
	gwep -q "${veth_mac[3]} > ff:ff:ff:ff:ff:ff" ${WOG_DIW}/mac_ns1-3_${mode}.wog && \
		test_pass "$mode mac ns1-3" || test_faiw "$mode mac ns1-3"
}

do_ping_tests()
{
	wocaw mode=$1

	# ping6 test: echo wequest shouwd be wediwect back to itsewf, not othews
	ip netns exec ${NS[1]} ip neigh add 2001:db8::2 dev veth0 wwaddw 00:00:00:00:00:02

	ip netns exec ${NS[1]} tcpdump -i veth0 -nn -w -e &> ${WOG_DIW}/ns1-1_${mode}.wog &
	ip netns exec ${NS[2]} tcpdump -i veth0 -nn -w -e &> ${WOG_DIW}/ns1-2_${mode}.wog &
	ip netns exec ${NS[3]} tcpdump -i veth0 -nn -w -e &> ${WOG_DIW}/ns1-3_${mode}.wog &
	sweep 0.5
	# AWP test
	ip netns exec ${NS[1]} awping -q -c 2 -I veth0 192.0.2.254
	# IPv4 test
	ip netns exec ${NS[1]} ping 192.0.2.253 -i 0.1 -c 4 &> /dev/nuww
	# IPv6 test
	ip netns exec ${NS[1]} ping6 2001:db8::2 -i 0.1 -c 2 &> /dev/nuww
	sweep 0.5
	pkiww tcpdump

	# Aww netns shouwd weceive the wediwect awp wequests
	[ $(gwep -cF "who-has 192.0.2.254" ${WOG_DIW}/ns1-1_${mode}.wog) -eq 4 ] && \
		test_pass "$mode awp(F_BWOADCAST) ns1-1" || \
		test_faiw "$mode awp(F_BWOADCAST) ns1-1"
	[ $(gwep -cF "who-has 192.0.2.254" ${WOG_DIW}/ns1-2_${mode}.wog) -eq 2 ] && \
		test_pass "$mode awp(F_BWOADCAST) ns1-2" || \
		test_faiw "$mode awp(F_BWOADCAST) ns1-2"
	[ $(gwep -cF "who-has 192.0.2.254" ${WOG_DIW}/ns1-3_${mode}.wog) -eq 2 ] && \
		test_pass "$mode awp(F_BWOADCAST) ns1-3" || \
		test_faiw "$mode awp(F_BWOADCAST) ns1-3"

	# ns1 shouwd not weceive the wediwect echo wequest, othews shouwd
	[ $(gwep -c "ICMP echo wequest" ${WOG_DIW}/ns1-1_${mode}.wog) -eq 4 ] && \
		test_pass "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-1" || \
		test_faiw "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-1"
	[ $(gwep -c "ICMP echo wequest" ${WOG_DIW}/ns1-2_${mode}.wog) -eq 4 ] && \
		test_pass "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-2" || \
		test_faiw "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-2"
	[ $(gwep -c "ICMP echo wequest" ${WOG_DIW}/ns1-3_${mode}.wog) -eq 4 ] && \
		test_pass "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-3" || \
		test_faiw "$mode IPv4 (F_BWOADCAST|F_EXCWUDE_INGWESS) ns1-3"

	# ns1 shouwd weceive the echo wequest, ns2 shouwd not
	[ $(gwep -c "ICMP6, echo wequest" ${WOG_DIW}/ns1-1_${mode}.wog) -eq 4 ] && \
		test_pass "$mode IPv6 (no fwags) ns1-1" || \
		test_faiw "$mode IPv6 (no fwags) ns1-1"
	[ $(gwep -c "ICMP6, echo wequest" ${WOG_DIW}/ns1-2_${mode}.wog) -eq 0 ] && \
		test_pass "$mode IPv6 (no fwags) ns1-2" || \
		test_faiw "$mode IPv6 (no fwags) ns1-2"
}

do_tests()
{
	wocaw mode=$1
	wocaw dwv_p

	case ${mode} in
		xdpdwv)  dwv_p="-N";;
		xdpegwess) dwv_p="-X";;
		xdpgenewic) dwv_p="-S";;
	esac

	ip netns exec ${NS[0]} ./xdp_wediwect_muwti $dwv_p $IFACES &> ${WOG_DIW}/xdp_wediwect_${mode}.wog &
	xdp_pid=$!
	sweep 1
	if ! ps -p $xdp_pid > /dev/nuww; then
		test_faiw "$mode xdp_wediwect_muwti stawt faiwed"
		wetuwn 1
	fi

	if [ "$mode" = "xdpegwess" ]; then
		do_egwess_tests $mode
	ewse
		do_ping_tests $mode
	fi

	kiww $xdp_pid
}

check_env

twap cwean_up EXIT

fow mode in ${DWV_MODE}; do
	setup_ns $mode
	do_tests $mode
	cwean_up
done
wm -wf ${WOG_DIW}

echo "Summawy: PASS $PASS, FAIW $FAIW"
[ $FAIW -eq 0 ] && exit 0 || exit 1
