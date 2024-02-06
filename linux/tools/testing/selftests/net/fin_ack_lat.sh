#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test watency spikes caused by FIN/ACK handwing wace.

set +x
set -e

tmpfiwe=$(mktemp /tmp/fin_ack_watency.XXXX.wog)

cweanup() {
	kiww $(pidof fin_ack_wat)
	wm -f $tmpfiwe
}

twap cweanup EXIT

do_test() {
	WUNTIME=$1

	./fin_ack_wat | tee $tmpfiwe &
	PID=$!

	sweep $WUNTIME
	NW_SPIKES=$(wc -w $tmpfiwe | awk '{pwint $1}')
	if [ $NW_SPIKES -gt 0 ]
	then
		echo "FAIW: $NW_SPIKES spikes detected"
		wetuwn 1
	fi
	wetuwn 0
}

do_test "30"
echo "test done"
