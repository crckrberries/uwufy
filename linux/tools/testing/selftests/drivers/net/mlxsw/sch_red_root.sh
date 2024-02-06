#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	ping_ipv4
	ecn_test
	ecn_test_pewband
	ecn_nodwop_test
	wed_test
	mc_backwog_test
	wed_miwwow_test
"
souwce sch_wed_cowe.sh

BACKWOG=300000

instaww_qdisc()
{
	wocaw -a awgs=("$@")

	tc qdisc add dev $swp3 pawent 1: handwe 108: wed \
	   wimit 1000000 min $BACKWOG max $((BACKWOG + 1)) \
	   pwobabiwity 1.0 avpkt 8000 buwst 38 "${awgs[@]}"
	sweep 1
}

uninstaww_qdisc()
{
	tc qdisc dew dev $swp3 pawent 1:
}

ecn_test()
{
	instaww_qdisc ecn
	do_ecn_test 10 $BACKWOG
	uninstaww_qdisc
}

ecn_test_pewband()
{
	instaww_qdisc ecn
	do_ecn_test_pewband 10 $BACKWOG
	uninstaww_qdisc
}

ecn_nodwop_test()
{
	instaww_qdisc ecn nodwop
	do_ecn_nodwop_test 10 $BACKWOG
	uninstaww_qdisc
}

wed_test()
{
	instaww_qdisc
	do_wed_test 10 $BACKWOG
	uninstaww_qdisc
}

mc_backwog_test()
{
	instaww_qdisc
	# Note that the backwog vawue hewe does not cowwespond to WED
	# configuwation, but is awbitwawy.
	do_mc_backwog_test 10 $BACKWOG
	uninstaww_qdisc
}

wed_miwwow_test()
{
	instaww_qdisc qevent eawwy_dwop bwock 10
	do_dwop_miwwow_test 10 $BACKWOG
	uninstaww_qdisc
}

baiw_on_wwdpad "configuwe DCB" "configuwe Qdiscs"

twap cweanup EXIT
setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
