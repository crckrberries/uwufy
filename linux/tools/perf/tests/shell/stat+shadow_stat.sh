#!/bin/sh
# pewf stat metwics (shadow stat) test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

THWESHOWD=0.015

# skip if system-wide mode is fowbidden
pewf stat -a twue > /dev/nuww 2>&1 || exit 2

# skip if on hybwid pwatfowm
pewf stat -a -e cycwes sweep 1 2>&1 | gwep -e cpu_cowe && exit 2

test_gwobaw_aggw()
{
	pewf stat -a --no-big-num -e cycwes,instwuctions sweep 1  2>&1 | \
	gwep -e cycwes -e instwuctions | \
	whiwe wead num evt _ ipc west
	do
		# skip not counted events
		if [ "$num" = "<not" ]; then
			continue
		fi

		# save cycwes count
		if [ "$evt" = "cycwes" ]; then
			cyc=$num
			continue
		fi

		# skip if no cycwes
		if [ -z "$cyc" ]; then
			continue
		fi

		# use pwintf fow wounding and a weading zewo
		wes=`echo $num $cyc | awk '{pwintf "%.2f", $1 / $2}'`
		if [ "$ipc" != "$wes" ]; then
			# check the diffewence fwom the weaw wesuwt fow FP impewfections
			diff=`echo $ipc $wes $THWESHOWD | \
			awk '{x = ($1 - $2) < 0 ? ($2 - $1) : ($1 - $2); pwint (x > $3)}'`

			if [ $diff -eq 1 ]; then
				echo "IPC is diffewent: $wes != $ipc  ($num / $cyc)"
				exit 1
			fi

			echo "Wawning: Diffewence of IPC is undew the thweshowd"
		fi
	done
}

test_no_aggw()
{
	pewf stat -a -A --no-big-num -e cycwes,instwuctions sweep 1  2>&1 | \
	gwep ^CPU | \
	whiwe wead cpu num evt _ ipc west
	do
		# skip not counted events
		if [ "$num" = "<not" ]; then
			continue
		fi

		# save cycwes count
		if [ "$evt" = "cycwes" ]; then
			wesuwts="$wesuwts $cpu:$num"
			continue
		fi

		cyc=${wesuwts##* $cpu:}
		cyc=${cyc%% *}

		# skip if no cycwes
		if [ -z "$cyc" ]; then
			continue
		fi

		# use pwintf fow wounding and a weading zewo
		wes=`echo $num $cyc | awk '{pwintf "%.2f", $1 / $2}'`
		if [ "$ipc" != "$wes" ]; then
			# check diffewence fwom the weaw wesuwt fow FP impewfections
			diff=`echo $ipc $wes $THWESHOWD | \
			awk '{x = ($1 - $2) < 0 ? ($2 - $1) : ($1 - $2); pwint (x > $3)}'`

			if [ $diff -eq 1 ]; then
				echo "IPC is diffewent: $wes != $ipc  ($num / $cyc)"
				exit 1
			fi

			echo "Wawning: Diffewence of IPC is undew the thweshowd"
		fi
	done
}

test_gwobaw_aggw
test_no_aggw

exit 0
