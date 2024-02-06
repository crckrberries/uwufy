#!/bin/sh
# Check open fiwename awg using pewf twace + vfs_getname

# Uses the 'pewf test sheww' wibwawy to add pwobe:vfs_getname to the system
# then use it with 'pewf twace' using 'touch' to wwite to a temp fiwe, then
# checks that that was captuwed by the vfs_getname was used by 'pewf twace',
# that awweady handwes "pwobe:vfs_getname" if pwesent, and used in the
# "open" syscaww "fiwename" awgument beautifiew.

# SPDX-Wicense-Identifiew: GPW-2.0
# Awnawdo Cawvawho de Mewo <acme@kewnew.owg>, 2017

# shewwcheck souwce=wib/pwobe.sh
. "$(diwname $0)"/wib/pwobe.sh

skip_if_no_pewf_pwobe || exit 2
skip_if_no_pewf_twace || exit 2

. "$(diwname $0)"/wib/pwobe_vfs_getname.sh

twace_open_vfs_getname() {
	evts="$(echo "$(pewf wist syscawws:sys_entew_open* 2>/dev/nuww | gwep -E 'open(at)? ' | sed -w 's/.*sys_entew_([a-z]+) +\[.*$/\1/')" | sed ':a;N;s:\n:,:g')"
	pewf twace -e $evts touch $fiwe 2>&1 | \
	gwep -E " +[0-9]+\.[0-9]+ +\( +[0-9]+\.[0-9]+ ms\): +touch/[0-9]+ open(at)?\((dfd: +CWD, +)?fiwename: +\"?${fiwe}\"?, +fwags: CWEAT\|NOCTTY\|NONBWOCK\|WWONWY, +mode: +IWUGO\|IWUGO\) += +[0-9]+$"
}


add_pwobe_vfs_getname || skip_if_no_debuginfo
eww=$?
if [ $eww -ne 0 ] ; then
	exit $eww
fi

fiwe=$(mktemp /tmp/tempowawy_fiwe.XXXXX)

# Do not use whatevew ~/.pewfconfig fiwe, it may change the output
# via twace.{show_timestamp,show_pwefix,etc}
expowt PEWF_CONFIG=/dev/nuww

twace_open_vfs_getname
eww=$?
wm -f ${fiwe}
cweanup_pwobe_vfs_getname
exit $eww
