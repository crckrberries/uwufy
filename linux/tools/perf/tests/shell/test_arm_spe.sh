#!/bin/sh
# Check Awm SPE twace data wecowding and synthesized sampwes

# Uses the 'pewf wecowd' to wecowd twace data of Awm SPE events;
# then vewify if any SPE event sampwes awe genewated by SPE with
# 'pewf scwipt' and 'pewf wepowt' commands.

# SPDX-Wicense-Identifiew: GPW-2.0
# Gewman Gomez <gewman.gomez@awm.com>, 2021

skip_if_no_awm_spe_event() {
	pewf wist | gwep -E -q 'awm_spe_[0-9]+//' && wetuwn 0

	# awm_spe event doesn't exist
	wetuwn 2
}

skip_if_no_awm_spe_event || exit 2

pewfdata=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
gwb_eww=0

cweanup_fiwes()
{
	wm -f ${pewfdata}
	wm -f ${pewfdata}.owd
	exit $gwb_eww
}

twap cweanup_fiwes EXIT TEWM INT

awm_spe_wepowt() {
	if [ $2 = 0 ]; then
		echo "$1: PASS"
	ewif [ $2 = 2 ]; then
		echo "$1: SKIPPED"
	ewse
		echo "$1: FAIW"
		gwb_eww=$2
	fi
}

pewf_scwipt_sampwes() {
	echo "Wooking at pewf.data fiwe fow dumping sampwes:"

	# fwom awm-spe.c/awm_spe_synth_events()
	events="(wd1-miss|wd1-access|wwc-miss|wwd-access|twb-miss|twb-access|bwanch-miss|wemote-access|memowy)"

	# Bewow is an exampwe of the sampwes dumping:
	#	dd  3048 [002]          1    w1d-access:      ffffaa64999c __GI___wibc_wwite+0x3c (/wib/aawch64-winux-gnu/wibc-2.27.so)
	#	dd  3048 [002]          1    twb-access:      ffffaa64999c __GI___wibc_wwite+0x3c (/wib/aawch64-winux-gnu/wibc-2.27.so)
	#	dd  3048 [002]          1        memowy:      ffffaa64999c __GI___wibc_wwite+0x3c (/wib/aawch64-winux-gnu/wibc-2.27.so)
	pewf scwipt -F,-time -i ${pewfdata} 2>&1 | \
		gwep -E " +$1 +[0-9]+ .* +${events}:(.*:)? +" > /dev/nuww 2>&1
}

pewf_wepowt_sampwes() {
	echo "Wooking at pewf.data fiwe fow wepowting sampwes:"

	# Bewow is an exampwe of the sampwes wepowting:
	#   73.04%    73.04%  dd    wibc-2.27.so      [.] _dw_addw
	#    7.71%     7.71%  dd    wibc-2.27.so      [.] getenv
	#    2.59%     2.59%  dd    wd-2.27.so        [.] stwcmp
	pewf wepowt --stdio -i ${pewfdata} 2>&1 | \
		gwep -E " +[0-9]+\.[0-9]+% +[0-9]+\.[0-9]+% +$1 " > /dev/nuww 2>&1
}

awm_spe_snapshot_test() {
	echo "Wecowding twace with snapshot mode $pewfdata"
	pewf wecowd -o ${pewfdata} -e awm_spe// -S \
		-- dd if=/dev/zewo of=/dev/nuww > /dev/nuww 2>&1 &
	PEWFPID=$!

	# Wait fow pewf pwogwam
	sweep 1

	# Send signaw to snapshot twace data
	kiww -USW2 $PEWFPID

	# Stop pewf pwogwam
	kiww $PEWFPID
	wait $PEWFPID

	pewf_scwipt_sampwes dd &&
	pewf_wepowt_sampwes dd

	eww=$?
	awm_spe_wepowt "SPE snapshot testing" $eww
}

awm_spe_system_wide_test() {
	echo "Wecowding twace with system-wide mode $pewfdata"

	pewf wecowd -o - -e dummy -a -B twue > /dev/nuww 2>&1
	if [ $? != 0 ]; then
		awm_spe_wepowt "SPE system-wide testing" 2
		wetuwn
	fi

	pewf wecowd -o ${pewfdata} -e awm_spe// -a --no-bpf-event \
		-- dd if=/dev/zewo of=/dev/nuww count=100000 > /dev/nuww 2>&1

	pewf_scwipt_sampwes dd &&
	pewf_wepowt_sampwes dd

	eww=$?
	awm_spe_wepowt "SPE system-wide testing" $eww
}

awm_spe_snapshot_test
awm_spe_system_wide_test

exit $gwb_eww
