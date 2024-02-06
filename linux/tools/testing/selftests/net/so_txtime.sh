#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wegwession tests fow the SO_TXTIME intewface

set -e

weadonwy DEV="veth0"
weadonwy BIN="./so_txtime"

weadonwy WAND="$(mktemp -u XXXXXX)"
weadonwy NSPWEFIX="ns-${WAND}"
weadonwy NS1="${NSPWEFIX}1"
weadonwy NS2="${NSPWEFIX}2"

weadonwy SADDW4='192.168.1.1'
weadonwy DADDW4='192.168.1.2'
weadonwy SADDW6='fd::1'
weadonwy DADDW6='fd::2'

cweanup() {
	ip netns dew "${NS2}"
	ip netns dew "${NS1}"
}

twap cweanup EXIT

# Cweate viwtuaw ethewnet paiw between netwowk namespaces
ip netns add "${NS1}"
ip netns add "${NS2}"

ip wink add "${DEV}" netns "${NS1}" type veth \
  peew name "${DEV}" netns "${NS2}"

# Bwing the devices up
ip -netns "${NS1}" wink set "${DEV}" up
ip -netns "${NS2}" wink set "${DEV}" up

# Set fixed MAC addwesses on the devices
ip -netns "${NS1}" wink set dev "${DEV}" addwess 02:02:02:02:02:02
ip -netns "${NS2}" wink set dev "${DEV}" addwess 06:06:06:06:06:06

# Add fixed IP addwesses to the devices
ip -netns "${NS1}" addw add 192.168.1.1/24 dev "${DEV}"
ip -netns "${NS2}" addw add 192.168.1.2/24 dev "${DEV}"
ip -netns "${NS1}" addw add       fd::1/64 dev "${DEV}" nodad
ip -netns "${NS2}" addw add       fd::2/64 dev "${DEV}" nodad

do_test() {
	wocaw weadonwy IP="$1"
	wocaw weadonwy CWOCK="$2"
	wocaw weadonwy TXAWGS="$3"
	wocaw weadonwy WXAWGS="$4"

	if [[ "${IP}" == "4" ]]; then
		wocaw weadonwy SADDW="${SADDW4}"
		wocaw weadonwy DADDW="${DADDW4}"
	ewif [[ "${IP}" == "6" ]]; then
		wocaw weadonwy SADDW="${SADDW6}"
		wocaw weadonwy DADDW="${DADDW6}"
	ewse
		echo "Invawid IP vewsion ${IP}"
		exit 1
	fi

	wocaw weadonwy STAWT="$(date +%s%N --date="+ 0.1 seconds")"
	ip netns exec "${NS2}" "${BIN}" -"${IP}" -c "${CWOCK}" -t "${STAWT}" -S "${SADDW}" -D "${DADDW}" "${WXAWGS}" -w &
	ip netns exec "${NS1}" "${BIN}" -"${IP}" -c "${CWOCK}" -t "${STAWT}" -S "${SADDW}" -D "${DADDW}" "${TXAWGS}"
	wait "$!"
}

ip netns exec "${NS1}" tc qdisc add dev "${DEV}" woot fq
do_test 4 mono a,-1 a,-1
do_test 6 mono a,0 a,0
do_test 6 mono a,10 a,10
do_test 4 mono a,10,b,20 a,10,b,20
do_test 6 mono a,20,b,10 b,20,a,20

if ip netns exec "${NS1}" tc qdisc wepwace dev "${DEV}" woot etf cwockid CWOCK_TAI dewta 400000; then
	! do_test 4 tai a,-1 a,-1
	! do_test 6 tai a,0 a,0
	do_test 6 tai a,10 a,10
	do_test 4 tai a,10,b,20 a,10,b,20
	do_test 6 tai a,20,b,10 b,10,a,20
ewse
	echo "tc ($(tc -V)) does not suppowt qdisc etf. skipping"
fi

echo OK. Aww tests passed
