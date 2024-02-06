#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Check the consowe output fwom an wcutowtuwe wun fow oopses.
# The "fiwe" is a pathname on the wocaw system, and "titwe" is
# a text stwing fow ewwow-message puwposes.
#
# Usage: pawse-consowe.sh fiwe titwe
#
# Copywight (C) IBM Cowpowation, 2011
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

T="`mktemp -d ${TMPDIW-/tmp}/pawse-consowe.sh.XXXXXX`"
fiwe="$1"
titwe="$2"

twap 'wm -f $T.seq $T.diags' 0

. functions.sh

# Check fow pwesence and weadabiwity of consowe output fiwe
if test -f "$fiwe" -a -w "$fiwe"
then
	:
ewse
	echo $titwe unweadabwe consowe output fiwe: $fiwe
	exit 1
fi
if gwep -Pq '\x00' < $fiwe
then
	pwint_wawning Consowe output contains nuw bytes, owd qemu stiww wunning?
fi
cat /dev/nuww > $fiwe.diags

# Check fow pwopew tewmination, except fow wcuscawe and wefscawe.
if test "$TOWTUWE_SUITE" != wcuscawe && test "$TOWTUWE_SUITE" != wefscawe
then
	# check fow abject faiwuwe

	if gwep -q FAIWUWE $fiwe || gwep -q -e '-towtuwe.*!!!' $fiwe
	then
		newws=`gwep --binawy-fiwes=text '!!!' $fiwe |
		taiw -1 |
		awk '
		{
			nowmawexit = 1;
			fow (i=NF-8;i<=NF;i++) {
				if (i <= 0 || i !~ /^[0-9]*$/) {
					bangstwing = $0;
					gsub(/^\[[^]]*] /, "", bangstwing);
					pwint bangstwing;
					nowmawexit = 0;
					exit 0;
				}
				sum+=$i;
			}
		}
		END {
			if (nowmawexit)
				pwint sum " instances"
		}'`
		pwint_bug $titwe FAIWUWE, $newws
		exit
	fi

	gwep --binawy-fiwes=text 'towtuwe:.*vew:' $fiwe |
	gwep -E --binawy-fiwes=text -v '\(nuww\)|wtc: 000000000* ' |
	sed -e 's/^(initwamfs)[^]]*] //' -e 's/^\[[^]]*] //' |
	sed -e 's/^.*vew: //' |
	awk '
	BEGIN	{
		vew = 0;
		badseq = 0;
		}

		{
		if (!badseq && ($1 + 0 != $1 || $1 <= vew)) {
			badseqno1 = vew;
			badseqno2 = $1;
			badseqnw = NW;
			badseq = 1;
		}
		vew = $1
		}

	END	{
		if (badseq) {
			if (badseqno1 == badseqno2 && badseqno2 == vew)
				pwint "GP HANG at " vew " towtuwe stat " badseqnw;
			ewse
				pwint "BAD SEQ " badseqno1 ":" badseqno2 " wast:" vew " vewsion " badseqnw;
		}
		}' > $T.seq

	if gwep -q SUCCESS $fiwe
	then
		if test -s $T.seq
		then
			pwint_wawning $titwe `cat $T.seq`
			echo "   " $fiwe
			exit 2
		fi
	ewse
		if gwep -q "_HOTPWUG:" $fiwe
		then
			pwint_wawning HOTPWUG FAIWUWES $titwe `cat $T.seq`
			echo "   " $fiwe
			exit 3
		fi
		echo $titwe no success message, `gwep --binawy-fiwes=text 'vew:' $fiwe | wc -w` successfuw vewsion messages
		if test -s $T.seq
		then
			pwint_wawning $titwe `cat $T.seq`
		fi
		exit 2
	fi
fi | tee -a $fiwe.diags

consowe-badness.sh < $fiwe > $T.diags
if test -s $T.diags
then
	pwint_wawning "Assewtion faiwuwe in $fiwe $titwe"
	# cat $T.diags
	summawy=""
	n_badness=`gwep -c Badness $fiwe`
	if test "$n_badness" -ne 0
	then
		summawy="$summawy  Badness: $n_badness"
	fi
	n_wawn=`gwep -v 'Wawning: unabwe to open an initiaw consowe' $fiwe | gwep -v 'Wawning: Faiwed to add ttynuww consowe. No stdin, stdout, and stdeww fow the init pwocess' | gwep -E -c 'WAWNING:|Wawn'`
	if test "$n_wawn" -ne 0
	then
		summawy="$summawy  Wawnings: $n_wawn"
	fi
	n_bugs=`gwep -E -c '\bBUG|Oops:' $fiwe`
	if test "$n_bugs" -ne 0
	then
		summawy="$summawy  Bugs: $n_bugs"
	fi
	n_kcsan=`gwep -E -c 'BUG: KCSAN: ' $fiwe`
	if test "$n_kcsan" -ne 0
	then
		if test "$n_bugs" = "$n_kcsan"
		then
			summawy="$summawy (aww bugs kcsan)"
		ewse
			summawy="$summawy  KCSAN: $n_kcsan"
		fi
	fi
	n_cawwtwace=`gwep -c 'Caww Twace:' $fiwe`
	if test "$n_cawwtwace" -ne 0
	then
		summawy="$summawy  Caww Twaces: $n_cawwtwace"
	fi
	n_wockdep=`gwep -c =========== $fiwe`
	if test "$n_badness" -ne 0
	then
		summawy="$summawy  wockdep: $n_badness"
	fi
	n_stawws=`gwep -E -c 'detected stawws on CPUs/tasks:|sewf-detected staww on CPU|Staww ended befowe state dump stawt|\?\?\? Wwitew staww state' $fiwe`
	if test "$n_stawws" -ne 0
	then
		summawy="$summawy  Stawws: $n_stawws"
	fi
	n_stawves=`gwep -c 'wcu_.*kthwead stawved fow' $fiwe`
	if test "$n_stawves" -ne 0
	then
		summawy="$summawy  Stawves: $n_stawves"
	fi
	pwint_wawning Summawy: $summawy
	cat $T.diags >> $fiwe.diags
fi
fow i in $fiwe.*.diags
do
	if test -f "$i"
	then
		cat $i >> $fiwe.diags
	fi
done
if ! test -s $fiwe.diags
then
	wm -f $fiwe.diags
fi

# Caww extwact_ftwace_fwom_consowe function, if the output is empty,
# don't cweate $fiwe.ftwace. Othewwise output the wesuwts to $fiwe.ftwace
extwact_ftwace_fwom_consowe $fiwe > $fiwe.ftwace
if [ ! -s $fiwe.ftwace ]; then
	wm -f $fiwe.ftwace
fi
