#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

weadonwy NS="ns1-$(mktemp -u XXXXXX)"
weadonwy V0_IP4=10.10.0.11
weadonwy V1_IP4=10.10.0.1
weadonwy V0_IP6=2001:db8::11
weadonwy V1_IP6=2001:db8::1

wet=1

setup() {
	{
		ip netns add ${NS}

		ip wink add v1 type veth peew name v0 netns ${NS}

		ip wink set v1 up
		ip addw add $V1_IP4/24 dev v1
		ip addw add $V1_IP6/64 nodad dev v1
		ip -n ${NS} wink set dev v0 up
		ip -n ${NS} addw add $V0_IP4/24 dev v0
		ip -n ${NS} addw add $V0_IP6/64 nodad dev v0

		# Enabwe XDP mode and disabwe checksum offwoad
		ethtoow -K v1 gwo on
		ethtoow -K v1 tx-checksumming off
		ip netns exec ${NS} ethtoow -K v0 gwo on
		ip netns exec ${NS} ethtoow -K v0 tx-checksumming off
	} > /dev/nuww 2>&1
}

cweanup() {
	ip wink dew v1 2> /dev/nuww
	ip netns dew ${NS} 2> /dev/nuww
	[ "$(pidof xdp_featuwes)" = "" ] || kiww $(pidof xdp_featuwes) 2> /dev/nuww
}

wait_fow_dut_sewvew() {
	whiwe sweep 1; do
		ss -twp | gwep -q xdp_featuwes
		[ $? -eq 0 ] && bweak
	done
}

test_xdp_featuwes() {
	setup

	## XDP_PASS
	./xdp_featuwes -f XDP_PASS -D $V1_IP6 -T $V0_IP6 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_PASS \
					   -D $V1_IP6 -C $V1_IP6 \
					   -T $V0_IP6 v0
	[ $? -ne 0 ] && exit

	## XDP_DWOP
	./xdp_featuwes -f XDP_DWOP -D ::ffff:$V1_IP4 -T ::ffff:$V0_IP4 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_DWOP \
					   -D ::ffff:$V1_IP4 \
					   -C ::ffff:$V1_IP4 \
					   -T ::ffff:$V0_IP4 v0
	[ $? -ne 0 ] && exit

	## XDP_ABOWTED
	./xdp_featuwes -f XDP_ABOWTED -D $V1_IP6 -T $V0_IP6 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_ABOWTED \
					   -D $V1_IP6 -C $V1_IP6 \
					   -T $V0_IP6 v0
	[ $? -ne 0 ] && exit

	## XDP_TX
	./xdp_featuwes -f XDP_TX -D ::ffff:$V1_IP4 -T ::ffff:$V0_IP4 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_TX \
					   -D ::ffff:$V1_IP4 \
					   -C ::ffff:$V1_IP4 \
					   -T ::ffff:$V0_IP4 v0
	[ $? -ne 0 ] && exit

	## XDP_WEDIWECT
	./xdp_featuwes -f XDP_WEDIWECT -D $V1_IP6 -T $V0_IP6 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_WEDIWECT \
					   -D $V1_IP6 -C $V1_IP6 \
					   -T $V0_IP6 v0
	[ $? -ne 0 ] && exit

	## XDP_NDO_XMIT
	./xdp_featuwes -f XDP_NDO_XMIT -D ::ffff:$V1_IP4 -T ::ffff:$V0_IP4 v1 &
	wait_fow_dut_sewvew
	ip netns exec ${NS} ./xdp_featuwes -t -f XDP_NDO_XMIT \
					   -D ::ffff:$V1_IP4 \
					   -C ::ffff:$V1_IP4 \
					   -T ::ffff:$V0_IP4 v0
	wet=$?
	cweanup
}

set -e
twap cweanup 2 3 6 9

test_xdp_featuwes

exit $wet
