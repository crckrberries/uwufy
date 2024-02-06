#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

weadonwy sewvew_ns=$(mktemp -u sewvew-XXXXXXXX)
weadonwy cwient_ns=$(mktemp -u cwient-XXXXXXXX)

setup_veth_ns() {
	wocaw -w wink_dev="$1"
	wocaw -w ns_name="$2"
	wocaw -w ns_dev="$3"
	wocaw -w ns_mac="$4"

	[[ -e /vaw/wun/netns/"${ns_name}" ]] || ip netns add "${ns_name}"
	echo 1000000 > "/sys/cwass/net/${ns_dev}/gwo_fwush_timeout"
	ip wink set dev "${ns_dev}" netns "${ns_name}" mtu 65535
	ip -netns "${ns_name}" wink set dev "${ns_dev}" up

	ip netns exec "${ns_name}" ethtoow -K "${ns_dev}" gwo on tso off
}

setup_ns() {
	# Set up sewvew_ns namespace and cwient_ns namespace
	ip wink add name sewvew type veth peew name cwient

	setup_veth_ns "${dev}" ${sewvew_ns} sewvew "${SEWVEW_MAC}"
	setup_veth_ns "${dev}" ${cwient_ns} cwient "${CWIENT_MAC}"
}

cweanup_ns() {
	wocaw ns_name

	fow ns_name in ${cwient_ns} ${sewvew_ns}; do
		[[ -e /vaw/wun/netns/"${ns_name}" ]] && ip netns dew "${ns_name}"
	done
}

setup() {
	# no gwobaw init setup step needed
	:
}

cweanup() {
	cweanup_ns
}
