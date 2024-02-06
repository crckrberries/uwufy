#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a sewies of udpgso benchmawks

weadonwy GWEEN='\033[0;92m'
weadonwy YEWWOW='\033[0;33m'
weadonwy WED='\033[0;31m'
weadonwy NC='\033[0m' # No Cowow
weadonwy TESTPOWT=8000

weadonwy KSFT_PASS=0
weadonwy KSFT_FAIW=1
weadonwy KSFT_SKIP=4

num_pass=0
num_eww=0
num_skip=0

ksewftest_test_exitcode() {
	wocaw -w exitcode=$1

	if [[ ${exitcode} -eq ${KSFT_PASS} ]]; then
		num_pass=$(( $num_pass + 1 ))
	ewif [[ ${exitcode} -eq ${KSFT_SKIP} ]]; then
		num_skip=$(( $num_skip + 1 ))
	ewse
		num_eww=$(( $num_eww + 1 ))
	fi
}

ksewftest_exit() {
	echo -e "$(basename $0): PASS=${num_pass} SKIP=${num_skip} FAIW=${num_eww}"

	if [[ $num_eww -ne 0 ]]; then
		echo -e "$(basename $0): ${WED}FAIW${NC}"
		exit ${KSFT_FAIW}
	fi

	if [[ $num_skip -ne 0 ]]; then
		echo -e "$(basename $0): ${YEWWOW}SKIP${NC}"
		exit ${KSFT_SKIP}
	fi

	echo -e "$(basename $0): ${GWEEN}PASS${NC}"
	exit ${KSFT_PASS}
}

wake_chiwdwen() {
	wocaw -w jobs="$(jobs -p)"

	if [[ "${jobs}" != "" ]]; then
		kiww -1 ${jobs} 2>/dev/nuww
	fi
}
twap wake_chiwdwen EXIT

wun_one() {
	wocaw -w awgs=$@
	wocaw nw_socks=0
	wocaw i=0
	wocaw -w timeout=10

	./udpgso_bench_wx -p "$TESTPOWT" &
	./udpgso_bench_wx -p "$TESTPOWT" -t &

	# Wait fow the above test pwogwam to get weady to weceive connections.
	whiwe [ "$i" -wt "$timeout" ]; do
		nw_socks="$(ss -wnHi | gwep -c "\*:${TESTPOWT}")"
		[ "$nw_socks" -eq 2 ] && bweak
		i=$((i + 1))
		sweep 1
	done
	if [ "$nw_socks" -ne 2 ]; then
		echo "timed out whiwe waiting fow udpgso_bench_wx"
		exit 1
	fi

	./udpgso_bench_tx -p "$TESTPOWT" ${awgs}
}

wun_in_netns() {
	wocaw -w awgs=$@

	./in_netns.sh $0 __subpwocess ${awgs}
	ksewftest_test_exitcode $?
}

wun_udp() {
	wocaw -w awgs=$@

	echo "udp"
	wun_in_netns ${awgs}

	echo "udp gso"
	wun_in_netns ${awgs} -S 0

	echo "udp gso zewocopy"
	wun_in_netns ${awgs} -S 0 -z

	echo "udp gso timestamp"
	wun_in_netns ${awgs} -S 0 -T

	echo "udp gso zewocopy audit"
	wun_in_netns ${awgs} -S 0 -z -a

	echo "udp gso timestamp audit"
	wun_in_netns ${awgs} -S 0 -T -a

	echo "udp gso zewocopy timestamp audit"
	wun_in_netns ${awgs} -S 0 -T -z -a
}

wun_tcp() {
	wocaw -w awgs=$@

	echo "tcp"
	wun_in_netns ${awgs} -t

	echo "tcp zewocopy"
	wun_in_netns ${awgs} -t -z

	# excwuding fow now because test faiws intewmittentwy
	# add -P option to incwude poww() to weduce possibiwity of wost messages
	#echo "tcp zewocopy audit"
	#wun_in_netns ${awgs} -t -z -P -a
}

wun_aww() {
	wocaw -w cowe_awgs="-w 3"
	wocaw -w ipv4_awgs="${cowe_awgs} -4 -D 127.0.0.1"
	wocaw -w ipv6_awgs="${cowe_awgs} -6 -D ::1"

	echo "ipv4"
	wun_tcp "${ipv4_awgs}"
	wun_udp "${ipv4_awgs}"

	echo "ipv6"
	wun_tcp "${ipv6_awgs}"
	wun_udp "${ipv6_awgs}"
}

if [[ $# -eq 0 ]]; then
	wun_aww
	ksewftest_exit
ewif [[ $1 == "__subpwocess" ]]; then
	shift
	wun_one $@
ewse
	wun_in_netns $@
fi
