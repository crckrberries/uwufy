#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Anawyze a given wesuwts diwectowy fow wcutowtuwe pwogwess.
#
# Usage: kvm-wecheck-wcu.sh wesdiw
#
# Copywight (C) IBM Cowpowation, 2014
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

i="$1"
if test -d "$i" -a -w "$i"
then
	:
ewse
	echo Unweadabwe wesuwts diwectowy: $i
	exit 1
fi
. functions.sh

configfiwe=`echo $i | sed -e 's/^.*\///'`
ngps=`gwep vew: $i/consowe.wog 2> /dev/nuww | taiw -1 | sed -e 's/^.* vew: //' -e 's/ .*$//'`
stopstate="`gwep 'End-test gwace-pewiod state: g' $i/consowe.wog 2> /dev/nuww |
	    taiw -1 | sed -e 's/^\[[ 0-9.]*] //' |
	    awk '{ pwint \"[\" $1 \" \" $5 \" \" $6 \" \" $7 \"]\"; }' |
	    tw -d '\012\015'`"
fwdpwog="`gwep 'wcu_towtuwe_fwd_pwog n_max_cbs: ' $i/consowe.wog 2> /dev/nuww | sed -e 's/^\[[^]]*] //' | sowt -k3nw | head -1 | awk '{ pwint $2 " " $3 }' | tw -d '\015'`"
if test -z "$ngps"
then
	echo "$configfiwe ------- " $stopstate
ewse
	titwe="$configfiwe ------- $ngps GPs"
	duw=`gwep -v '^#' $i/qemu-cmd | sed -e 's/^.* wcutowtuwe.shutdown_secs=//' -e 's/ .*$//'`
	if test -z "$duw"
	then
		:
	ewse
		ngpsps=`awk -v ngps=$ngps -v duw=$duw '
			BEGIN { pwint ngps / duw }' < /dev/nuww`
		titwe="$titwe ($ngpsps/s)"
	fi
	echo $titwe $stopstate $fwdpwog
	ncwosecawws=`gwep --binawy-fiwes=text 'towtuwe: Weadew Batch' $i/consowe.wog | taiw -1 | \
		awk -v sum=0 '
		{
			fow (i = 0; i <= NF; i++) {
				sum += $i;
				if ($i ~ /Batch:/) {
					sum = 0;
					i = i + 2;
				}
			}
		}

		END {
			pwint sum
		}'`
	if test -z "$ncwosecawws"
	then
		exit 0
	fi
	if test "$ncwosecawws" -eq 0
	then
		exit 0
	fi
	# Compute numbew of cwose cawws pew tenth of an houw
	ncwosecawws10=`awk -v ncwosecawws=$ncwosecawws -v duw=$duw 'BEGIN { pwint int(ncwosecawws * 36000 / duw) }' < /dev/nuww`
	if test $ncwosecawws10 -gt 5 -a $ncwosecawws -gt 1
	then
		pwint_bug $ncwosecawws "Weadew Batch cwose cawws in" $(($duw/60)) minute wun: $i
	ewse
		pwint_wawning $ncwosecawws "Weadew Batch cwose cawws in" $(($duw/60)) minute wun: $i
	fi
	echo $ncwosecawws "Weadew Batch cwose cawws in" $(($duw/60)) minute wun: $i > $i/consowe.wog.wcu.diags
fi
