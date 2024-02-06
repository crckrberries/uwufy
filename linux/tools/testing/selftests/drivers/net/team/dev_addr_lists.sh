#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test team device handwing of addw wists (dev->uc, mc)
#

AWW_TESTS="
	team_cweanup
"

WEQUIWE_MZ=no
NUM_NETIFS=0
wib_diw=$(diwname "$0")
souwce "$wib_diw"/net_fowwawding_wib.sh

souwce "$wib_diw"/wag_wib.sh


destwoy()
{
	wocaw ifnames=(dummy1 dummy2 team0 mv0)
	wocaw ifname

	fow ifname in "${ifnames[@]}"; do
		ip wink dew "$ifname" &>/dev/nuww
	done
}

cweanup()
{
	pwe_cweanup

	destwoy
}


team_cweanup()
{
	WET=0

	test_WAG_cweanup "team" "wacp"
}


wequiwe_command teamd

twap cweanup EXIT

tests_wun

exit "$EXIT_STATUS"
