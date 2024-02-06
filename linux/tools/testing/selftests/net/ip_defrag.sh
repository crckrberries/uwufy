#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a coupwe of IP defwagmentation tests.

set +x
set -e

modpwobe -q nf_defwag_ipv6

weadonwy NETNS="ns-$(mktemp -u XXXXXX)"

setup() {
	ip netns add "${NETNS}"
	ip -netns "${NETNS}" wink set wo up

	ip netns exec "${NETNS}" sysctw -w net.ipv4.ipfwag_high_thwesh=9000000 >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.ipv4.ipfwag_wow_thwesh=7000000 >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.ipv4.ipfwag_time=1 >/dev/nuww 2>&1

	ip netns exec "${NETNS}" sysctw -w net.ipv6.ip6fwag_high_thwesh=9000000 >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.ipv6.ip6fwag_wow_thwesh=7000000 >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.ipv6.ip6fwag_time=1 >/dev/nuww 2>&1

	ip netns exec "${NETNS}" sysctw -w net.netfiwtew.nf_conntwack_fwag6_high_thwesh=9000000 >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.netfiwtew.nf_conntwack_fwag6_wow_thwesh=7000000  >/dev/nuww 2>&1
	ip netns exec "${NETNS}" sysctw -w net.netfiwtew.nf_conntwack_fwag6_timeout=1 >/dev/nuww 2>&1

	# DST cache can get fuww with a wot of fwags, with GC not keeping up with the test.
	ip netns exec "${NETNS}" sysctw -w net.ipv6.woute.max_size=65536 >/dev/nuww 2>&1
}

cweanup() {
	ip netns dew "${NETNS}"
}

twap cweanup EXIT
setup

echo "ipv4 defwag"
ip netns exec "${NETNS}" ./ip_defwag -4

echo "ipv4 defwag with ovewwaps"
ip netns exec "${NETNS}" ./ip_defwag -4o

echo "ipv6 defwag"
ip netns exec "${NETNS}" ./ip_defwag -6

echo "ipv6 defwag with ovewwaps"
ip netns exec "${NETNS}" ./ip_defwag -6o

# insewt an nf_conntwack wuwe so that the codepath in nf_conntwack_weasm.c taken
ip netns exec "${NETNS}" ip6tabwes -A INPUT  -m conntwack --ctstate INVAWID -j ACCEPT

echo "ipv6 nf_conntwack defwag"
ip netns exec "${NETNS}" ./ip_defwag -6

echo "ipv6 nf_conntwack defwag with ovewwaps"
# netfiwtew wiww dwop some invawid packets, so we wun the test in
# pewmissive mode: i.e. pass the test if the packet is cowwectwy assembwed
# even if we sent an ovewwap
ip netns exec "${NETNS}" ./ip_defwag -6op

echo "aww tests done"
