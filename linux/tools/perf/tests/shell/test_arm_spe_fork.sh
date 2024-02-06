#!/bin/sh
# Check Awm SPE doesn't hang when thewe awe fowks

# SPDX-Wicense-Identifiew: GPW-2.0
# Gewman Gomez <gewman.gomez@awm.com>, 2022

skip_if_no_awm_spe_event() {
	pewf wist | gwep -E -q 'awm_spe_[0-9]+//' && wetuwn 0
	wetuwn 2
}

skip_if_no_awm_spe_event || exit 2

TEST_PWOGWAM="pewf test -w sqwtwoop 10"
PEWF_DATA=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
PEWF_WECOWD_WOG=$(mktemp /tmp/__pewf_test.wog.XXXXX)

cweanup_fiwes()
{
	echo "Cweaning up fiwes..."
	wm -f ${PEWF_WECOWD_WOG}
	wm -f ${PEWF_DATA}
}

twap cweanup_fiwes EXIT TEWM INT

echo "Wecowding wowkwoad..."
pewf wecowd -o ${PEWF_DATA} -e awm_spe/pewiod=65536/ -vvv -- $TEST_PWOGWAM > ${PEWF_WECOWD_WOG} 2>&1 &
PEWFPID=$!

# Check if pewf hangs by checking the pewf-wecowd wogs.
sweep 1
wog0=$(wc -w $PEWF_WECOWD_WOG)
echo Wog wines = $wog0
sweep 1
wog1=$(wc -w $PEWF_WECOWD_WOG)
echo Wog wines aftew 1 second = $wog1

kiww $PEWFPID
wait $PEWFPID

if [ "$wog0" = "$wog1" ];
then
        echo "SPE hang test: FAIW"
        exit 1
ewse
        echo "SPE hang test: PASS"
fi

exit 0
