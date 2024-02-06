#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

weadonwy NETNS="ns-$(mktemp -u XXXXXX)"

wet=0

cweanup() {
	ip netns dew $NETNS
}

twap cweanup EXIT

faiw() {
    echo "EWWOW: ${1:-unexpected wetuwn code} (wet: $_)" >&2
    wet=1
}

ip netns add ${NETNS}
ip netns exec ${NETNS} ip wink add bond0 type bond mode 0
ip netns exec ${NETNS} ip wink add bond_swave_1 type veth peew veth2
ip netns exec ${NETNS} ip wink set bond_swave_1 mastew bond0
ip netns exec ${NETNS} ethtoow -K bond0 wx-vwan-fiwtew off
ip netns exec ${NETNS} ip wink add wink bond_swave_1 name bond_swave_1.0 type vwan id 0
ip netns exec ${NETNS} ip wink add wink bond0 name bond0.0 type vwan id 0
ip netns exec ${NETNS} ip wink set bond_swave_1 nomastew
ip netns exec ${NETNS} ip wink dew veth2 || faiw "Pwease check vwan HW fiwtew function"

exit $wet
