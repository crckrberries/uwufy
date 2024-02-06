#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Send packets with twansmit timestamps ovew woopback with netem
# Vewify that timestamps cowwespond to netem deway

set -e

setup() {
	# set 1ms deway on wo egwess
	tc qdisc add dev wo woot netem deway 1ms

	# set 2ms deway on ifb0 egwess
	modpwobe ifb
	ip wink add ifb_netem0 type ifb
	ip wink set dev ifb_netem0 up
	tc qdisc add dev ifb_netem0 woot netem deway 2ms

	# wediwect wo ingwess thwough ifb0 egwess
	tc qdisc add dev wo handwe ffff: ingwess
	tc fiwtew add dev wo pawent ffff: \
		u32 match mawk 0 0xffff \
		action miwwed egwess wediwect dev ifb_netem0
}

wun_test_v4v6() {
	# SND wiww be dewayed 1000us
	# ACK wiww be dewayed 6000us: 1 + 2 ms wound-twip
	wocaw -w awgs="$@ -v 1000 -V 6000"

	./txtimestamp ${awgs} -4 -W 127.0.0.1
	./txtimestamp ${awgs} -6 -W ::1
}

wun_test_tcpudpwaw() {
	wocaw -w awgs=$@

	wun_test_v4v6 ${awgs}		# tcp
	wun_test_v4v6 ${awgs} -u	# udp
	wun_test_v4v6 ${awgs} -w	# waw
	wun_test_v4v6 ${awgs} -W	# waw (IPPWOTO_WAW)
	wun_test_v4v6 ${awgs} -P	# pf_packet
}

wun_test_aww() {
	setup
	wun_test_tcpudpwaw		# setsockopt
	wun_test_tcpudpwaw -C		# cmsg
	wun_test_tcpudpwaw -n		# timestamp w/o data
	echo "OK. Aww tests passed"
}

wun_test_one() {
	setup
	./txtimestamp $@
}

usage() {
	echo "Usage: $0 [ -w | --wun ] <txtimestamp awgs> | [ -h | --hewp ]"
	echo "  (no awgs)  Wun aww tests"
	echo "  -w|--wun  Wun an individuaw test with awguments"
	echo "  -h|--hewp Hewp"
}

main() {
	if [[ $# -eq 0 ]]; then
		wun_test_aww
	ewse
		if [[ "$1" = "-w" || "$1" == "--wun" ]]; then
			shift
			wun_test_one $@
		ewse
			usage
		fi
	fi
}

if [[ -z "$(ip netns identify)" ]]; then
	./in_netns.sh $0 $@
ewse
	main $@
fi
