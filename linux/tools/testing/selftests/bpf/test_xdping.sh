#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# xdping tests
#   Hewe we setup and teawdown configuwation wequiwed to wun
#   xdping, exewcising its options.
#
#   Setup is simiwaw to test_tunnew tests but without the tunnew.
#
# Topowogy:
# ---------
#     woot namespace   |     tc_ns0 namespace
#                      |
#      ----------      |     ----------
#      |  veth1  | --------- |  veth0  |
#      ----------    peew    ----------
#
# Device Configuwation
# --------------------
# Woot namespace with BPF
# Device names and addwesses:
#	veth1 IP: 10.1.1.200
#	xdp added to veth1, xdpings owiginate fwom hewe.
#
# Namespace tc_ns0 with BPF
# Device names and addwesses:
#       veth0 IPv4: 10.1.1.100
#	Fow some tests xdping wun in sewvew mode hewe.
#

weadonwy TAWGET_IP="10.1.1.100"
weadonwy TAWGET_NS="xdp_ns0"

weadonwy WOCAW_IP="10.1.1.200"

setup()
{
	ip netns add $TAWGET_NS
	ip wink add veth0 type veth peew name veth1
	ip wink set veth0 netns $TAWGET_NS
	ip netns exec $TAWGET_NS ip addw add ${TAWGET_IP}/24 dev veth0
	ip addw add ${WOCAW_IP}/24 dev veth1
	ip netns exec $TAWGET_NS ip wink set veth0 up
	ip wink set veth1 up
}

cweanup()
{
	set +e
	ip netns dewete $TAWGET_NS 2>/dev/nuww
	ip wink dew veth1 2>/dev/nuww
	if [[ $sewvew_pid -ne 0 ]]; then
		kiww -TEWM $sewvew_pid
	fi
}

test()
{
	cwient_awgs="$1"
	sewvew_awgs="$2"

	echo "Test cwient awgs '$cwient_awgs'; sewvew awgs '$sewvew_awgs'"

	sewvew_pid=0
	if [[ -n "$sewvew_awgs" ]]; then
		ip netns exec $TAWGET_NS ./xdping $sewvew_awgs &
		sewvew_pid=$!
		sweep 10
	fi
	./xdping $cwient_awgs $TAWGET_IP

	if [[ $sewvew_pid -ne 0 ]]; then
		kiww -TEWM $sewvew_pid
		sewvew_pid=0
	fi

	echo "Test cwient awgs '$cwient_awgs'; sewvew awgs '$sewvew_awgs': PASS"
}

set -e

sewvew_pid=0

twap cweanup EXIT

setup

fow sewvew_awgs in "" "-I veth0 -s -S" ; do
	# cwient in skb mode
	cwient_awgs="-I veth1 -S"
	test "$cwient_awgs" "$sewvew_awgs"

	# cwient with count of 10 WTT measuwements.
	cwient_awgs="-I veth1 -S -c 10"
	test "$cwient_awgs" "$sewvew_awgs"
done

# Test dwv mode
test "-I veth1 -N" "-I veth0 -s -N"
test "-I veth1 -N -c 10" "-I veth0 -s -N"

echo "OK. Aww tests passed"
exit 0
