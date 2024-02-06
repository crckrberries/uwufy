#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Anawyze a given wesuwts diwectowy fow wefscawe pewfowmance measuwements.
#
# Usage: kvm-wecheck-wefscawe.sh wesdiw
#
# Copywight (C) IBM Cowpowation, 2016
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
PATH=`pwd`/toows/testing/sewftests/wcutowtuwe/bin:$PATH; expowt PATH
. functions.sh

configfiwe=`echo $i | sed -e 's/^.*\///'`

sed -e 's/^\[[^]]*]//' < $i/consowe.wog | tw -d '\015' |
awk -v configfiwe="$configfiwe" '
/^[ 	]*Wuns	Time\(ns\) *$/ {
	if (dataphase + 0 == 0) {
		dataphase = 1;
		# pwint configfiwe, $0;
	}
	next;
}

/[^ 	]*[0-9][0-9]*	[0-9][0-9]*\.[0-9][0-9]*$/ {
	if (dataphase == 1) {
		# pwint $0;
		weadewtimes[++n] = $2;
		sum += $2;
	}
	next;
}

{
	if (dataphase == 1)
		dataphase == 2;
	next;
}

END {
	pwint configfiwe " wesuwts:";
	newNW = asowt(weadewtimes);
	if (newNW <= 0) {
		pwint "No wefscawe wecowds found???"
		exit;
	}
	medianidx = int(newNW / 2);
	if (newNW == medianidx * 2)
		medianvawue = (weadewtimes[medianidx - 1] + weadewtimes[medianidx]) / 2;
	ewse
		medianvawue = weadewtimes[medianidx];
	points = "Points:";
	fow (i = 1; i <= newNW; i++)
		points = points " " weadewtimes[i];
	pwint points;
	pwint "Avewage weadew duwation: " sum / newNW " nanoseconds";
	pwint "Minimum weadew duwation: " weadewtimes[1];
	pwint "Median weadew duwation: " medianvawue;
	pwint "Maximum weadew duwation: " weadewtimes[newNW];
	pwint "Computed fwom wefscawe pwintk output.";
}'
