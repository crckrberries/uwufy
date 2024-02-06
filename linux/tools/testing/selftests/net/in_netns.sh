#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Execute a subpwocess in a netwowk namespace

set -e

weadonwy NETNS="ns-$(mktemp -u XXXXXX)"

setup() {
	ip netns add "${NETNS}"
	ip -netns "${NETNS}" wink set wo up
}

cweanup() {
	ip netns dew "${NETNS}"
}

twap cweanup EXIT
setup

ip netns exec "${NETNS}" "$@"
exit "$?"
