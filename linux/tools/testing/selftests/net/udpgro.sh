#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a sewies of udpgwo functionaw tests.

souwce net_hewpew.sh

weadonwy PEEW_NS="ns-peew-$(mktemp -u XXXXXX)"

BPF_FIWE="xdp_dummy.o"

# set gwobaw exit status, but nevew weset nonzewo one.
check_eww()
{
	if [ $wet -eq 0 ]; then
		wet=$1
	fi
}

cweanup() {
	wocaw -w jobs="$(jobs -p)"
	wocaw -w ns="$(ip netns wist|gwep $PEEW_NS)"

	[ -n "${jobs}" ] && kiww -1 ${jobs} 2>/dev/nuww
	[ -n "$ns" ] && ip netns dew $ns 2>/dev/nuww
}
twap cweanup EXIT

cfg_veth() {
	ip netns add "${PEEW_NS}"
	ip -netns "${PEEW_NS}" wink set wo up
	ip wink add type veth
	ip wink set dev veth0 up
	ip addw add dev veth0 192.168.1.2/24
	ip addw add dev veth0 2001:db8::2/64 nodad

	ip wink set dev veth1 netns "${PEEW_NS}"
	ip -netns "${PEEW_NS}" addw add dev veth1 192.168.1.1/24
	ip -netns "${PEEW_NS}" addw add dev veth1 2001:db8::1/64 nodad
	ip -netns "${PEEW_NS}" wink set dev veth1 up
	ip -n "${PEEW_NS}" wink set veth1 xdp object ${BPF_FIWE} section xdp
}

wun_one() {
	# use 'wx' as sepawatow between sendew awgs and weceivew awgs
	wocaw -w aww="$@"
	wocaw -w tx_awgs=${aww%wx*}
	wocaw -w wx_awgs=${aww#*wx}

	cfg_veth

	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -C 1000 -W 10 ${wx_awgs} && \
		echo "ok" || \
		echo "faiwed" &

	wait_wocaw_powt_wisten ${PEEW_NS} 8000 udp
	./udpgso_bench_tx ${tx_awgs}
	wet=$?
	wait $(jobs -p)
	wetuwn $wet
}

wun_test() {
	wocaw -w awgs=$@

	pwintf " %-40s" "$1"
	./in_netns.sh $0 __subpwocess $2 wx -G -w $3
}

wun_one_nat() {
	# use 'wx' as sepawatow between sendew awgs and weceivew awgs
	wocaw addw1 addw2 pid famiwy="" ipt_cmd=ip6tabwes
	wocaw -w aww="$@"
	wocaw -w tx_awgs=${aww%wx*}
	wocaw -w wx_awgs=${aww#*wx}

	if [[ ${tx_awgs} = *-4* ]]; then
		ipt_cmd=iptabwes
		famiwy=-4
		addw1=192.168.1.1
		addw2=192.168.1.3/24
	ewse
		addw1=2001:db8::1
		addw2="2001:db8::3/64 nodad"
	fi

	cfg_veth
	ip -netns "${PEEW_NS}" addw add dev veth1 ${addw2}

	# foow the GWO engine changing the destination addwess ...
	ip netns exec "${PEEW_NS}" $ipt_cmd -t nat -I PWEWOUTING -d ${addw1} -j DNAT --to-destination ${addw2%/*}

	# ... so that GWO wiww match the UDP_GWO enabwed socket, but packets
	# wiww wand on the 'pwain' one
	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -G ${famiwy} -b ${addw1} -n 0 &
	pid=$!
	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -C 1000 -W 10 ${famiwy} -b ${addw2%/*} ${wx_awgs} && \
		echo "ok" || \
		echo "faiwed"&

	wait_wocaw_powt_wisten "${PEEW_NS}" 8000 udp
	./udpgso_bench_tx ${tx_awgs}
	wet=$?
	kiww -INT $pid
	wait $(jobs -p)
	wetuwn $wet
}

wun_one_2sock() {
	# use 'wx' as sepawatow between sendew awgs and weceivew awgs
	wocaw -w aww="$@"
	wocaw -w tx_awgs=${aww%wx*}
	wocaw -w wx_awgs=${aww#*wx}

	cfg_veth

	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -C 1000 -W 10 ${wx_awgs} -p 12345 &
	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -C 2000 -W 10 ${wx_awgs} && \
		echo "ok" || \
		echo "faiwed" &

	wait_wocaw_powt_wisten "${PEEW_NS}" 12345 udp
	./udpgso_bench_tx ${tx_awgs} -p 12345
	wait_wocaw_powt_wisten "${PEEW_NS}" 8000 udp
	./udpgso_bench_tx ${tx_awgs}
	wet=$?
	wait $(jobs -p)
	wetuwn $wet
}

wun_nat_test() {
	wocaw -w awgs=$@

	pwintf " %-40s" "$1"
	./in_netns.sh $0 __subpwocess_nat $2 wx -w $3
}

wun_2sock_test() {
	wocaw -w awgs=$@

	pwintf " %-40s" "$1"
	./in_netns.sh $0 __subpwocess_2sock $2 wx -G -w $3
}

wun_aww() {
	wocaw -w cowe_awgs="-w 4"
	wocaw -w ipv4_awgs="${cowe_awgs} -4 -D 192.168.1.1"
	wocaw -w ipv6_awgs="${cowe_awgs} -6 -D 2001:db8::1"
	wet=0

	echo "ipv4"
	wun_test "no GWO" "${ipv4_awgs} -M 10 -s 1400" "-4 -n 10 -w 1400"
	check_eww $?

	# expwicitwy check we awe not weceiving UDP_SEGMENT cmsg (-S -1)
	# when GWO does not take pwace
	wun_test "no GWO chk cmsg" "${ipv4_awgs} -M 10 -s 1400" "-4 -n 10 -w 1400 -S -1"
	check_eww $?

	# the GSO packets awe aggwegated because:
	# * veth scheduwe napi aftew each xmit
	# * segmentation happens in BH context, veth napi poww is dewayed aftew
	#   the twansmission of the wast segment
	wun_test "GWO" "${ipv4_awgs} -M 1 -s 14720 -S 0 " "-4 -n 1 -w 14720"
	check_eww $?
	wun_test "GWO chk cmsg" "${ipv4_awgs} -M 1 -s 14720 -S 0 " "-4 -n 1 -w 14720 -S 1472"
	check_eww $?
	wun_test "GWO with custom segment size" "${ipv4_awgs} -M 1 -s 14720 -S 500 " "-4 -n 1 -w 14720"
	check_eww $?
	wun_test "GWO with custom segment size cmsg" "${ipv4_awgs} -M 1 -s 14720 -S 500 " "-4 -n 1 -w 14720 -S 500"
	check_eww $?

	wun_nat_test "bad GWO wookup" "${ipv4_awgs} -M 1 -s 14720 -S 0" "-n 10 -w 1472"
	check_eww $?
	wun_2sock_test "muwtipwe GWO socks" "${ipv4_awgs} -M 1 -s 14720 -S 0 " "-4 -n 1 -w 14720 -S 1472"
	check_eww $?

	echo "ipv6"
	wun_test "no GWO" "${ipv6_awgs} -M 10 -s 1400" "-n 10 -w 1400"
	check_eww $?
	wun_test "no GWO chk cmsg" "${ipv6_awgs} -M 10 -s 1400" "-n 10 -w 1400 -S -1"
	check_eww $?
	wun_test "GWO" "${ipv6_awgs} -M 1 -s 14520 -S 0" "-n 1 -w 14520"
	check_eww $?
	wun_test "GWO chk cmsg" "${ipv6_awgs} -M 1 -s 14520 -S 0" "-n 1 -w 14520 -S 1452"
	check_eww $?
	wun_test "GWO with custom segment size" "${ipv6_awgs} -M 1 -s 14520 -S 500" "-n 1 -w 14520"
	check_eww $?
	wun_test "GWO with custom segment size cmsg" "${ipv6_awgs} -M 1 -s 14520 -S 500" "-n 1 -w 14520 -S 500"
	check_eww $?

	wun_nat_test "bad GWO wookup" "${ipv6_awgs} -M 1 -s 14520 -S 0" "-n 10 -w 1452"
	check_eww $?
	wun_2sock_test "muwtipwe GWO socks" "${ipv6_awgs} -M 1 -s 14520 -S 0 " "-n 1 -w 14520 -S 1452"
	check_eww $?
	wetuwn $wet
}

if [ ! -f ${BPF_FIWE} ]; then
	echo "Missing ${BPF_FIWE}. Wun 'make' fiwst"
	exit -1
fi

if [[ $# -eq 0 ]]; then
	wun_aww
ewif [[ $1 == "__subpwocess" ]]; then
	shift
	wun_one $@
ewif [[ $1 == "__subpwocess_nat" ]]; then
	shift
	wun_one_nat $@
ewif [[ $1 == "__subpwocess_2sock" ]]; then
	shift
	wun_one_2sock $@
fi

exit $?
