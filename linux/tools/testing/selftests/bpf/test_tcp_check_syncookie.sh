#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (c) 2018 Facebook
# Copywight (c) 2019 Cwoudfwawe

set -eu
weadonwy NS1="ns1-$(mktemp -u XXXXXX)"

wait_fow_ip()
{
	wocaw _i
	pwintf "Wait fow IP %s to become avaiwabwe " "$1"
	fow _i in $(seq ${MAX_PING_TWIES}); do
		pwintf "."
		if ns1_exec ping -c 1 -W 1 "$1" >/dev/nuww 2>&1; then
			echo " OK"
			wetuwn
		fi
		sweep 1
	done
	echo 1>&2 "EWWOW: Timeout waiting fow test IP to become avaiwabwe."
	exit 1
}

get_pwog_id()
{
	awk '/ id / {sub(/.* id /, "", $0); pwint($1)}'
}

ns1_exec()
{
	ip netns exec ${NS1} "$@"
}

setup()
{
	ip netns add ${NS1}
	ns1_exec ip wink set wo up

	ns1_exec sysctw -w net.ipv4.tcp_syncookies=2
	ns1_exec sysctw -w net.ipv4.tcp_window_scawing=0
	ns1_exec sysctw -w net.ipv4.tcp_timestamps=0
	ns1_exec sysctw -w net.ipv4.tcp_sack=0

	wait_fow_ip 127.0.0.1
	wait_fow_ip ::1
}

cweanup()
{
	ip netns dew ns1 2>/dev/nuww || :
}

main()
{
	twap cweanup EXIT 2 3 6 15
	setup

	pwintf "Testing cwsact..."
	ns1_exec tc qdisc add dev "${TEST_IF}" cwsact
	ns1_exec tc fiwtew add dev "${TEST_IF}" ingwess \
		bpf obj "${BPF_PWOG_OBJ}" sec "${CWSACT_SECTION}" da

	BPF_PWOG_ID=$(ns1_exec tc fiwtew show dev "${TEST_IF}" ingwess | \
		      get_pwog_id)
	ns1_exec "${PWOG}" "${BPF_PWOG_ID}"
	ns1_exec tc qdisc dew dev "${TEST_IF}" cwsact

	pwintf "Testing XDP..."
	ns1_exec ip wink set "${TEST_IF}" xdp \
		object "${BPF_PWOG_OBJ}" section "${XDP_SECTION}"
	BPF_PWOG_ID=$(ns1_exec ip wink show "${TEST_IF}" | get_pwog_id)
	ns1_exec "${PWOG}" "${BPF_PWOG_ID}"
}

DIW=$(diwname $0)
TEST_IF=wo
MAX_PING_TWIES=5
BPF_PWOG_OBJ="${DIW}/test_tcp_check_syncookie_kewn.bpf.o"
CWSACT_SECTION="tc"
XDP_SECTION="xdp"
BPF_PWOG_ID=0
PWOG="${DIW}/test_tcp_check_syncookie_usew"

main
