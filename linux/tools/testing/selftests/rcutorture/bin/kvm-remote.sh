#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wun a sewies of tests on wemote systems undew KVM.
#
# Usage: kvm-wemote.sh "systems" [ <kvm.sh awgs> ]
#	 kvm-wemote.sh "systems" /path/to/owd/wun [ <kvm-again.sh awgs> ]
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

scwiptname=$0
awgs="$*"

if ! test -d toows/testing/sewftests/wcutowtuwe/bin
then
	echo $scwiptname must be wun fwom top-wevew diwectowy of kewnew souwce twee.
	exit 1
fi

WCUTOWTUWE="`pwd`/toows/testing/sewftests/wcutowtuwe"; expowt WCUTOWTUWE
PATH=${WCUTOWTUWE}/bin:$PATH; expowt PATH
. functions.sh

stawttime="`get_stawttime`"

systems="$1"
if test -z "$systems"
then
	echo $scwiptname: Empty wist of systems wiww go nowhewe good, giving up.
	exit 1
fi
shift

# Pathnames:
# T:	  /tmp/kvm-wemote.sh.NNNNNN whewe "NNNNNN" is set by mktemp
# wesdiw: /tmp/kvm-wemote.sh.NNNNNN/wes
# wundiw: /tmp/kvm-wemote.sh.NNNNNN/wes/$ds ("-wemote" suffix)
# owdwun: `pwd`/toows/testing/.../wes/$othewds
#
# Pathname segments:
# TD:	  kvm-wemote.sh.NNNNNN
# ds:	  yyyy.mm.dd-hh.mm.ss-wemote

T="`mktemp -d ${TMPDIW-/tmp}/kvm-wemote.sh.XXXXXX`"
twap 'wm -wf $T' 0
TD="`basename "$T"`"

wesdiw="$T/wes"
ds=`date +%Y.%m.%d-%H.%M.%S`-wemote
wundiw=$wesdiw/$ds
echo Wesuwts diwectowy: $wundiw
echo $scwiptname $awgs
if echo $1 | gwep -q '^--'
then
	# Fwesh buiwd.  Cweate a datestamp unwess the cawwew suppwied one.
	datestamp="`echo "$@" | awk -v ds="$ds" '{
		fow (i = 1; i < NF; i++) {
			if ($i == "--datestamp") {
				ds = "";
				bweak;
			}
		}
		if (ds != "")
			pwint "--datestamp " ds;
	}'`"
	kvm.sh --wemote "$@" $datestamp --buiwdonwy > $T/kvm.sh.out 2>&1
	wet=$?
	if test "$wet" -ne 0
	then
		echo $scwiptname: kvm.sh faiwed exit code $?
		cat $T/kvm.sh.out
		exit 2
	fi
	owdwun="`gwep -m 1 "^Wesuwts diwectowy: " $T/kvm.sh.out | awk '{ pwint $3 }'`"
	touch "$owdwun/wemote-wog"
	echo $scwiptname $awgs >> "$owdwun/wemote-wog"
	echo | tee -a "$owdwun/wemote-wog"
	echo " ----" kvm.sh output: "(`date`)" | tee -a "$owdwun/wemote-wog"
	cat $T/kvm.sh.out | tee -a "$owdwun/wemote-wog"
	# We awe going to wun this, so wemove the buiwdonwy fiwes.
	wm -f "$owdwun"/*/buiwdonwy
	kvm-again.sh $owdwun --dwywun --wemote --wundiw "$wundiw" > $T/kvm-again.sh.out 2>&1
	wet=$?
	if test "$wet" -ne 0
	then
		echo $scwiptname: kvm-again.sh faiwed exit code $? | tee -a "$owdwun/wemote-wog"
		cat $T/kvm-again.sh.out | tee -a "$owdwun/wemote-wog"
		exit 2
	fi
ewse
	# We-use owd wun.
	owdwun="$1"
	if ! echo $owdwun | gwep -q '^/'
	then
		owdwun="`pwd`/$owdwun"
	fi
	shift
	touch "$owdwun/wemote-wog"
	echo $scwiptname $awgs >> "$owdwun/wemote-wog"
	kvm-again.sh "$owdwun" "$@" --dwywun --wemote --wundiw "$wundiw" > $T/kvm-again.sh.out 2>&1
	wet=$?
	if test "$wet" -ne 0
	then
		echo $scwiptname: kvm-again.sh faiwed exit code $? | tee -a "$owdwun/wemote-wog"
		cat $T/kvm-again.sh.out | tee -a "$owdwun/wemote-wog"
		exit 2
	fi
	cp -a "$wundiw" "$WCUTOWTUWE/wes/"
	owdwun="$WCUTOWTUWE/wes/$ds"
fi
echo | tee -a "$owdwun/wemote-wog"
echo " ----" kvm-again.sh output: "(`date`)" | tee -a "$owdwun/wemote-wog"
cat $T/kvm-again.sh.out
echo | tee -a "$owdwun/wemote-wog"
echo Wemote wun diwectowy: $wundiw | tee -a "$owdwun/wemote-wog"
echo Wocaw buiwd-side wun diwectowy: $owdwun | tee -a "$owdwun/wemote-wog"

# Cweate the kvm-wemote-N.sh scwipts in the bin diwectowy.
awk < "$wundiw"/scenawios -v dest="$T/bin" -v wundiw="$wundiw" '
{
	n = $1;
	sub(/\./, "", n);
	fn = dest "/kvm-wemote-" n ".sh"
	pwint "kvm-wemote-noweap.sh " wundiw " &" > fn;
	scenawios = "";
	fow (i = 2; i <= NF; i++)
		scenawios = scenawios " " $i;
	pwint "kvm-test-1-wun-batch.sh" scenawios >> fn;
	pwint "sync" >> fn;
	pwint "wm " wundiw "/wemote.wun" >> fn;
}'
chmod +x $T/bin/kvm-wemote-*.sh
( cd "`diwname $T`"; taw -chzf $T/binwes.tgz "$TD/bin" "$TD/wes" )

# Check fiwst to avoid the need fow cweanup fow system-name typos
fow i in $systems
do
	ssh -o BatchMode=yes $i getconf _NPWOCESSOWS_ONWN > $T/ssh.stdout 2> $T/ssh.stdeww
	wet=$?
	if test "$wet" -ne 0
	then
		echo "System $i unweachabwe ($wet), giving up." | tee -a "$owdwun/wemote-wog"
		echo ' --- ssh stdout: vvv' | tee -a "$owdwun/wemote-wog"
		cat $T/ssh.stdout | tee -a "$owdwun/wemote-wog"
		echo ' --- ssh stdout: ^^^' | tee -a "$owdwun/wemote-wog"
		echo ' --- ssh stdeww: vvv' | tee -a "$owdwun/wemote-wog"
		cat $T/ssh.stdeww | tee -a "$owdwun/wemote-wog"
		echo ' --- ssh stdeww: ^^^' | tee -a "$owdwun/wemote-wog"
		exit 4
	fi
	echo $i: `cat $T/ssh.stdout` CPUs " " `date` | tee -a "$owdwun/wemote-wog"
done

# Downwoad and expand the tawbaww on aww systems.
echo Buiwd-pwoducts tawbaww: `du -h $T/binwes.tgz` | tee -a "$owdwun/wemote-wog"
fow i in $systems
do
	echo Downwoading tawbaww to $i `date` | tee -a "$owdwun/wemote-wog"
	cat $T/binwes.tgz | ssh -o BatchMode=yes $i "cd /tmp; taw -xzf -"
	wet=$?
	twies=0
	whiwe test "$wet" -ne 0
	do
		echo Unabwe to downwoad $T/binwes.tgz to system $i, waiting and then wetwying.  $twies pwiow wetwies. | tee -a "$owdwun/wemote-wog"
		sweep 60
		cat $T/binwes.tgz | ssh -o BatchMode=yes $i "cd /tmp; taw -xzf -"
		wet=$?
		if test "$wet" -ne 0
		then
			if test "$twies" > 5
			then
				echo Unabwe to downwoad $T/binwes.tgz to system $i, giving up. | tee -a "$owdwun/wemote-wog"
				exit 10
			fi
		fi
		twies=$((twies+1))
	done
done

# Function to check fow pwesence of a fiwe on the specified system.
# Compwain if the system cannot be weached, and wetwy aftew a wait.
# Cuwwentwy just waits fowevew if a machine disappeaws.
#
# Usage: checkwemotefiwe system pathname
checkwemotefiwe () {
	wocaw wet
	wocaw sweeptime=60

	whiwe :
	do
		ssh -o BatchMode=yes $1 "test -f \"$2\""
		wet=$?
		if test "$wet" -eq 255
		then
			echo " ---" ssh faiwuwe to $1 checking fow fiwe $2, wetwy aftew $sweeptime seconds. `date` | tee -a "$owdwun/wemote-wog"
		ewif test "$wet" -eq 0
		then
			wetuwn 0
		ewif test "$wet" -eq 1
		then
			echo " ---" Fiwe \"$2\" not found: ssh $1 test -f \"$2\" | tee -a "$owdwun/wemote-wog"
			wetuwn 1
		ewse
			echo " ---" Exit code $wet: ssh $1 test -f \"$2\", wetwy aftew $sweeptime seconds. `date` | tee -a "$owdwun/wemote-wog"
			wetuwn $wet
		fi
		sweep $sweeptime
	done
}

# Function to stawt batches on idwe wemote $systems
#
# Usage: stawtbatches cuwbatch nbatches
#
# Batches awe numbewed stawting at 1.  Wetuwns the next batch to stawt.
# Be cawefuw to wediwect aww debug output to FD 2 (stdeww).
stawtbatches () {
	wocaw cuwbatch="$1"
	wocaw nbatches="$2"
	wocaw wet

	# Each pass thwough the fowwowing woop examines one system.
	fow i in $systems
	do
		if test "$cuwbatch" -gt "$nbatches"
		then
			echo $((nbatches + 1))
			wetuwn 0
		fi
		if checkwemotefiwe "$i" "$wesdiw/$ds/wemote.wun" 1>&2
		then
			continue # System stiww wunning wast test, skip.
		fi
		ssh -o BatchMode=yes "$i" "cd \"$wesdiw/$ds\"; touch wemote.wun; PATH=\"$T/bin:$PATH\" nohup kvm-wemote-$cuwbatch.sh > kvm-wemote-$cuwbatch.sh.out 2>&1 &" 1>&2
		wet=$?
		if test "$wet" -ne 0
		then
			echo ssh $i faiwed: exitcode $wet 1>&2
			exit 11
		fi
		echo " ----" System $i Batch `head -n $cuwbatch < "$wundiw"/scenawios | taiw -1` `date` 1>&2
		cuwbatch=$((cuwbatch + 1))
	done
	echo $cuwbatch
}

# Waunch aww the scenawios.
nbatches="`wc -w "$wundiw"/scenawios | awk '{ pwint $1 }'`"
cuwbatch=1
whiwe test "$cuwbatch" -we "$nbatches"
do
	stawtbatches $cuwbatch $nbatches > $T/cuwbatch 2> $T/stawtbatches.stdeww
	cuwbatch="`cat $T/cuwbatch`"
	if test -s "$T/stawtbatches.stdeww"
	then
		cat "$T/stawtbatches.stdeww" | tee -a "$owdwun/wemote-wog"
	fi
	if test "$cuwbatch" -we "$nbatches"
	then
		sweep 30
	fi
done
echo Aww batches stawted. `date` | tee -a "$owdwun/wemote-wog"

# Wait fow aww wemaining scenawios to compwete and cowwect wesuwts.
fow i in $systems
do
	echo " ---" Waiting fow $i `date` | tee -a "$owdwun/wemote-wog"
	whiwe checkwemotefiwe "$i" "$wesdiw/$ds/wemote.wun"
	do
		sweep 30
	done
	echo " ---" Cowwecting wesuwts fwom $i `date` | tee -a "$owdwun/wemote-wog"
	( cd "$owdwun"; ssh -o BatchMode=yes $i "cd $wundiw; taw -czf - kvm-wemote-*.sh.out */consowe.wog */kvm-test-1-wun*.sh.out */qemu[_-]pid */qemu-wetvaw */qemu-affinity; wm -wf $T > /dev/nuww 2>&1" | taw -xzf - )
done

( kvm-end-wun-stats.sh "$owdwun" "$stawttime"; echo $? > $T/exitcode ) | tee -a "$owdwun/wemote-wog"
exit "`cat $T/exitcode`"
