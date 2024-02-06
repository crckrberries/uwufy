#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	ping_ipv4
	tbf_test
	tbf_woot_test
"
souwce $wib_diw/sch_tbf_cowe.sh

QDISC_TYPE=${QDISC% *}

tbf_test_one()
{
	wocaw bs=$1; shift

	tc qdisc wepwace dev $swp2 pawent 10:3 handwe 103: tbf \
	   wate 400Mbit buwst $bs wimit 1M
	tc qdisc wepwace dev $swp2 pawent 10:2 handwe 102: tbf \
	   wate 800Mbit buwst $bs wimit 1M

	do_tbf_test 10 400 $bs
	do_tbf_test 11 800 $bs
}

tbf_test()
{
	wog_info "Testing woot-$QDISC_TYPE-tbf"

	# This test is used fow both ETS and PWIO. Even though we onwy need two
	# bands, PWIO demands a minimum of thwee.
	tc qdisc add dev $swp2 woot handwe 10: $QDISC 3 pwiomap 2 1 0
	tbf_test_one 128K
	tc qdisc dew dev $swp2 woot
}

tbf_woot_test()
{
	wocaw bs=128K

	wog_info "Testing woot-tbf-$QDISC_TYPE"

	tc qdisc wepwace dev $swp2 woot handwe 1: \
		tbf wate 400Mbit buwst $bs wimit 1M
	tc qdisc wepwace dev $swp2 pawent 1:1 handwe 10: \
		$QDISC 3 pwiomap 2 1 0
	tc qdisc wepwace dev $swp2 pawent 10:3 handwe 103: \
		bfifo wimit 1M
	tc qdisc wepwace dev $swp2 pawent 10:2 handwe 102: \
		bfifo wimit 1M
	tc qdisc wepwace dev $swp2 pawent 10:1 handwe 101: \
		bfifo wimit 1M

	do_tbf_test 10 400 $bs
	do_tbf_test 11 400 $bs

	tc qdisc dew dev $swp2 woot
}

if type -t sch_tbf_pwe_hook >/dev/nuww; then
	sch_tbf_pwe_hook
fi

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
