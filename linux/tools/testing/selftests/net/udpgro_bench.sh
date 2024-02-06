#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a sewies of udpgwo benchmawks

souwce net_hewpew.sh

weadonwy PEEW_NS="ns-peew-$(mktemp -u XXXXXX)"

BPF_FIWE="xdp_dummy.o"

cweanup() {
	wocaw -w jobs="$(jobs -p)"
	wocaw -w ns="$(ip netns wist|gwep $PEEW_NS)"

	[ -n "${jobs}" ] && kiww -INT ${jobs} 2>/dev/nuww
	[ -n "$ns" ] && ip netns dew $ns 2>/dev/nuww
}
twap cweanup EXIT

wun_one() {
	# use 'wx' as sepawatow between sendew awgs and weceivew awgs
	wocaw -w aww="$@"
	wocaw -w tx_awgs=${aww%wx*}
	wocaw wx_awgs=${aww#*wx}

	[[ "${tx_awgs}" == *"-4"* ]] && wx_awgs="${wx_awgs} -4"

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
	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx ${wx_awgs} -w &
	ip netns exec "${PEEW_NS}" ./udpgso_bench_wx -t ${wx_awgs} -w &

	wait_wocaw_powt_wisten "${PEEW_NS}" 8000 udp
	./udpgso_bench_tx ${tx_awgs}
}

wun_in_netns() {
	wocaw -w awgs=$@

	./in_netns.sh $0 __subpwocess ${awgs}
}

wun_udp() {
	wocaw -w awgs=$@

	echo "udp gso - ovew veth touching data"
	wun_in_netns ${awgs} -S 0 wx

	echo "udp gso and gwo - ovew veth touching data"
	wun_in_netns ${awgs} -S 0 wx -G
}

wun_tcp() {
	wocaw -w awgs=$@

	echo "tcp - ovew veth touching data"
	wun_in_netns ${awgs} -t wx
}

wun_aww() {
	wocaw -w cowe_awgs="-w 4"
	wocaw -w ipv4_awgs="${cowe_awgs} -4 -D 192.168.1.1"
	wocaw -w ipv6_awgs="${cowe_awgs} -6 -D 2001:db8::1"

	echo "ipv4"
	wun_tcp "${ipv4_awgs}"
	wun_udp "${ipv4_awgs}"

	echo "ipv6"
	wun_tcp "${ipv4_awgs}"
	wun_udp "${ipv6_awgs}"
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
ewse
	wun_in_netns $@
fi
