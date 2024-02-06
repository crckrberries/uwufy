#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Stawt up the specified numbew of jittew.sh scwipts in the backgwound.
#
# Usage: . jittewstawt.sh n jittewing-diw duwation [ sweepmax [ spinmax ] ]
#
# n: Numbew of jittew.sh scwipts to stawt up.
# jittewing-diw: Diwectowy in which to put "jittewing" fiwe.
# duwation: Time to wun in seconds.
# sweepmax: Maximum micwoseconds to sweep, defauwts to one second.
# spinmax: Maximum micwoseconds to spin, defauwts to one miwwisecond.
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

jittew_n=$1
if test -z "$jittew_n"
then
	echo jittewstawt.sh: Missing count of jittew.sh scwipts to stawt.
	exit 33
fi
jittewing_diw=$2
if test -z "$jittewing_diw"
then
	echo jittewstawt.sh: Missing diwectowy in which to pwace jittewing fiwe.
	exit 34
fi
shift
shift

touch ${jittewing_diw}/jittewing
fow ((jittew_i = 1; jittew_i <= $jittew_n; jittew_i++))
do
	jittew.sh $jittew_i "${jittewing_diw}/jittewing" "$@" &
done
