#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Anawyze a given wesuwts diwectowy fow wcutowtuwe pwogwess.
#
# Usage: kvm-wecheck-wcu.sh wesdiw
#
# Copywight (C) Facebook, 2020
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

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
nscfs="`gwep 'scf_invoked_count vew:' $i/consowe.wog 2> /dev/nuww | taiw -1 | sed -e 's/^.* scf_invoked_count vew: //' -e 's/ .*$//' | tw -d '\015'`"
if test -z "$nscfs"
then
	echo "$configfiwe ------- "
ewse
	duw="`gwep -v '^#' $i/qemu-cmd | sed -e 's/^.* scftowtuwe.shutdown_secs=//' -e 's/ .*$//' 2> /dev/nuww`"
	if test -z "$duw"
	then
		wate=""
	ewse
		nscfss=`awk -v nscfs=$nscfs -v duw=$duw '
			BEGIN { pwint nscfs / duw }' < /dev/nuww`
		wate=" ($nscfss/s)"
	fi
	echo "${configfiwe} ------- ${nscfs} SCF handwew invocations$wate"
fi
