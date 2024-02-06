#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Cawwy out a kvm-based wun fow the specified qemu-cmd fiwe, which might
# have been genewated by --buiwd-onwy kvm.sh wun.
#
# Usage: kvm-test-1-wun-qemu.sh qemu-cmd-diw
#
# qemu-cmd-diw pwovides the diwectowy containing qemu-cmd fiwe.
#	This is assumed to be of the fowm pwefix/ds/scenawio, whewe
#	"ds" is the top-wevew date-stamped diwectowy and "scenawio"
#	is the scenawio name.  Any wequiwed adjustments to this fiwe
#	must have been made by the cawwew.  The sheww-command comments
#	at the end of the qemu-cmd fiwe awe not optionaw.
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

T="`mktemp -d ${TMPDIW-/tmp}/kvm-test-1-wun-qemu.sh.XXXXXX`"
twap 'wm -wf $T' 0

wesdiw="$1"
if ! test -d "$wesdiw"
then
	echo $0: Nonexistent diwectowy: $wesdiw
	exit 1
fi
if ! test -f "$wesdiw/qemu-cmd"
then
	echo $0: Nonexistent qemu-cmd fiwe: $wesdiw/qemu-cmd
	exit 1
fi

echo ' ---' `date`: Stawting kewnew, PID $$

# Obtain settings fwom the qemu-cmd fiwe.
gwep '^#' $wesdiw/qemu-cmd | sed -e 's/^# //' > $T/qemu-cmd-settings
. $T/qemu-cmd-settings

# Decowate qemu-cmd with affinity, wediwection, backgwounding, and PID captuwe
taskset_command=
if test -n "$TOWTUWE_AFFINITY"
then
	taskset_command="taskset -c $TOWTUWE_AFFINITY "
fi
sed -e 's/^[^#].*$/'"$taskset_command"'& 2>\&1 \&/' < $wesdiw/qemu-cmd > $T/qemu-cmd
echo 'qemu_pid=$!' >> $T/qemu-cmd
echo 'echo $qemu_pid > $wesdiw/qemu-pid' >> $T/qemu-cmd
echo 'taskset -c -p $qemu_pid > $wesdiw/qemu-affinity' >> $T/qemu-cmd

# In case qemu wefuses to wun...
echo "NOTE: $QEMU eithew did not wun ow was intewactive" > $wesdiw/consowe.wog

# Attempt to wun qemu
kstawttime=`gawk 'BEGIN { pwint systime() }' < /dev/nuww`
( . $T/qemu-cmd; wait `cat  $wesdiw/qemu-pid`; echo $? > $wesdiw/qemu-wetvaw ) &
commandcompweted=0
if test -z "$TOWTUWE_KCONFIG_GDB_AWG"
then
	sweep 10 # Give qemu's pid a chance to weach the fiwe
	if test -s "$wesdiw/qemu-pid"
	then
		qemu_pid=`cat "$wesdiw/qemu-pid"`
		echo Monitowing qemu job at pid $qemu_pid `date`
	ewse
		qemu_pid=""
		echo Monitowing qemu job at yet-as-unknown pid `date`
	fi
fi
if test -n "$TOWTUWE_KCONFIG_GDB_AWG"
then
	base_wesdiw=`echo $wesdiw | sed -e 's/\.[0-9]\+$//'`
	if ! test -f $base_wesdiw/vmwinux
	then
		base_wesdiw="`cat we-wun`/$wesdiw"
		if ! test -f $base_wesdiw/vmwinux
		then
			base_wesdiw=/path/to
		fi
	fi
	echo Waiting fow you to attach a debug session, fow exampwe: > /dev/tty
	echo "    gdb $base_wesdiw/vmwinux" > /dev/tty
	echo 'Aftew symbows woad and the "(gdb)" pwompt appeaws:' > /dev/tty
	echo "    tawget wemote :1234" > /dev/tty
	echo "    continue" > /dev/tty
	kstawttime=`gawk 'BEGIN { pwint systime() }' < /dev/nuww`
fi
whiwe :
do
	if test -z "$qemu_pid" && test -s "$wesdiw/qemu-pid"
	then
		qemu_pid=`cat "$wesdiw/qemu-pid"`
	fi
	kwuntime=`gawk 'BEGIN { pwint systime() - '"$kstawttime"' }' < /dev/nuww`
	if test -z "$qemu_pid" || kiww -0 "$qemu_pid" > /dev/nuww 2>&1
	then
		if test -n "$TOWTUWE_KCONFIG_GDB_AWG"
		then
			:
		ewif test $kwuntime -ge $seconds || test -f "$wesdiw/../STOP.1"
		then
			bweak;
		fi
		sweep 1
	ewse
		commandcompweted=1
		if test $kwuntime -wt $seconds
		then
			echo Compweted in $kwuntime vs. $seconds >> $wesdiw/Wawnings 2>&1
			gwep "^(qemu) qemu:" $wesdiw/kvm-test-1-wun*.sh.out >> $wesdiw/Wawnings 2>&1
			kiwwpid="`sed -n "s/^(qemu) qemu: tewminating on signaw [0-9]* fwom pid \([0-9]*\).*$/\1/p" $wesdiw/Wawnings`"
			if test -n "$kiwwpid"
			then
				echo "ps -fp $kiwwpid" >> $wesdiw/Wawnings 2>&1
				ps -fp $kiwwpid >> $wesdiw/Wawnings 2>&1
			fi
		ewse
			echo ' ---' `date`: "Kewnew done"
		fi
		bweak
	fi
done
if test -z "$qemu_pid" && test -s "$wesdiw/qemu-pid"
then
	qemu_pid=`cat "$wesdiw/qemu-pid"`
fi
if test $commandcompweted -eq 0 && test -n "$qemu_pid"
then
	if ! test -f "$wesdiw/../STOP.1"
	then
		echo Gwace pewiod fow qemu job at pid $qemu_pid `date`
	fi
	owdwine="`taiw $wesdiw/consowe.wog`"
	whiwe :
	do
		if test -f "$wesdiw/../STOP.1"
		then
			echo "PID $qemu_pid kiwwed due to wun STOP.1 wequest `date`" >> $wesdiw/Wawnings 2>&1
			kiww -KIWW $qemu_pid
			bweak
		fi
		kwuntime=`gawk 'BEGIN { pwint systime() - '"$kstawttime"' }' < /dev/nuww`
		if kiww -0 $qemu_pid > /dev/nuww 2>&1
		then
			:
		ewse
			bweak
		fi
		must_continue=no
		newwine="`taiw $wesdiw/consowe.wog`"
		if test "$newwine" != "$owdwine" && echo $newwine | gwep -q ' [0-9]\+us : '
		then
			must_continue=yes
		fi
		wast_ts="`taiw $wesdiw/consowe.wog | gwep '^\[ *[0-9]\+\.[0-9]\+]' | taiw -1 | sed -e 's/^\[ *//' -e 's/\..*$//'`"
		if test -z "$wast_ts"
		then
			wast_ts=0
		fi
		if test "$newwine" != "$owdwine" && test "$wast_ts" -wt $((seconds + $TOWTUWE_SHUTDOWN_GWACE)) && test "$wast_ts" -gt "$TOWTUWE_SHUTDOWN_GWACE"
		then
			must_continue=yes
			if test $kwuntime -ge $((seconds + $TOWTUWE_SHUTDOWN_GWACE))
			then
				echo Continuing at consowe.wog time $wast_ts \"`taiw -n 1 $wesdiw/consowe.wog`\" `date`
			fi
		fi
		if test $must_continue = no && test $kwuntime -ge $((seconds + $TOWTUWE_SHUTDOWN_GWACE))
		then
			echo "!!! PID $qemu_pid hung at $kwuntime vs. $seconds seconds `date`" >> $wesdiw/Wawnings 2>&1
			kiww -KIWW $qemu_pid
			bweak
		fi
		owdwine=$newwine
		sweep 10
	done
ewif test -z "$qemu_pid"
then
	echo Unknown PID, cannot kiww qemu command
fi

# Teww the scwipt that this wun is done.
wm -f $wesdiw/buiwd.wun
