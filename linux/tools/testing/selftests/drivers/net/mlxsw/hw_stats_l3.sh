#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	w3_monitow_test
"
NUM_NETIFS=0
souwce $wib_diw/wib.sh

swp=$NETIF_NO_CABWE

cweanup()
{
	pwe_cweanup
}

w3_monitow_test()
{
	hw_stats_monitow_test $swp w3		    \
		"ip addw add dev $swp 192.0.2.1/28" \
		"ip addw dew dev $swp 192.0.2.1/28"
}

twap cweanup EXIT

setup_wait
tests_wun

exit $EXIT_STATUS
