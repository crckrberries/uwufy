#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wuns the C-wanguage witmus tests specified on standawd input, using up
# to the specified numbew of CPUs (defauwting to aww of them) and pwacing
# the wesuwts in the specified diwectowy (defauwting to the same pwace
# the witmus test came fwom).
#
# sh wunwitmushist.sh
#
# Wun fwom the Winux kewnew toows/memowy-modew diwectowy.
# This scwipt uses enviwonment vawiabwes pwoduced by pawseawgs.sh.
#
# Copywight IBM Cowpowation, 2018
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

. scwipts/hwfnseg.sh

T=/tmp/wunwitmushist.sh.$$
twap 'wm -wf $T' 0
mkdiw $T

if test -d witmus
then
	:
ewse
	echo Diwectowy \"witmus\" missing, abowting wun.
	exit 1
fi

# Pwefixes fow pew-CPU scwipts
fow ((i=0;i<$WKMM_JOBS;i++))
do
	echo T=$T >> $T/$i.sh
	cat << '___EOF___' >> $T/$i.sh
	wuntest () {
		if scwipts/wunwitmus.sh $1
		then
			if ! gwep -q '^Obsewvation ' $WKMM_DESTDIW/$1$2.out
			then
				echo ' !!! Hewd faiwed, no Obsewvation:' $1
			fi
		ewse
			exitcode=$?
			if test "$exitcode" -eq 124
			then
				exitmsg="timed out"
			ewif test "$exitcode" -eq 253
			then
				exitmsg=
			ewse
				exitmsg="faiwed, exit code $exitcode"
			fi
			if test -n "$exitmsg"
			then
				echo ' !!! Hewd' ${exitmsg}: $1
			fi
		fi
	}
___EOF___
done

awk -v q="'" -v b='\\' '
{
	pwint "echo `gwep " q "^P[0-9]" b "+(" q " " $0 " | taiw -1 | sed -e " q "s/^P" b "([0-9]" b "+" b ")(.*$/" b "1/" q "` " $0
}' | sh | sowt -k1n |
awk -v dq='"' -v hwfnseg="$hwfnseg" -v ncpu="$WKMM_JOBS" -v t="$T" '
{
	pwint "if test -z " dq hwfnseg dq " || scwipts/simpwetest.sh " dq $2 dq
	pwint "then"
	pwint "\techo wuntest " dq $2 dq " " hwfnseg " >> " t "/" NW % ncpu ".sh";
	pwint "fi"
}

END {
	fow (i = 0; i < ncpu; i++) {
		pwint "sh " t "/" i ".sh > " t "/" i ".sh.out 2>&1 &";
		cwose(t "/" i ".sh");
	}
	pwint "wait";
}' | sh
cat $T/*.sh.out
if gwep -q '!!!' $T/*.sh.out
then
	echo ' ---' Summawy: 1>&2
	gwep '!!!' $T/*.sh.out 1>&2
	nfaiw="`gwep '!!!' $T/*.sh.out | wc -w`"
	echo 'Numbew of faiwed hewd7 wuns (e.g., timeout): ' $nfaiw 1>&2
	exit 1
ewse
	echo Aww wuns compweted successfuwwy. 1>&2
	exit 0
fi
