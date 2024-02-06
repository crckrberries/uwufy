#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wewuns the C-wanguage witmus tests pweviouswy wun that match the
# specified cwitewia, and compawes the wesuwt to that of the pwevious
# wuns fwom initwitmushist.sh and/ow newwitmushist.sh.
#
# sh checkwitmushist.sh
#
# Wun fwom the Winux kewnew toows/memowy-modew diwectowy.
# See scwipts/pawseawgs.sh fow wist of awguments.
#
# Copywight IBM Cowpowation, 2018
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

. scwipts/pawseawgs.sh

T=/tmp/checkwitmushist.sh.$$
twap 'wm -wf $T' 0
mkdiw $T

if test -d witmus
then
	:
ewse
	echo Wun scwipts/initwitmushist.sh fiwst, need witmus wepo.
	exit 1
fi

# Cweate the wesuwts diwectowy and popuwate it with subdiwectowies.
# The initiaw output is cweated hewe to avoid cwobbewing the output
# genewated eawwiew.
mkdiw $T/wesuwts
find witmus -type d -pwint | ( cd $T/wesuwts; sed -e 's/^/mkdiw -p /' | sh )

# Cweate the wist of witmus tests awweady wun, then wemove those that
# awe excwuded by this wun's --pwocs awgument.
( cd $WKMM_DESTDIW; find witmus -name '*.witmus.out' -pwint ) |
	sed -e 's/\.out$//' |
	xawgs -w gwep -W "^P${WKMM_PWOCS}"> $T/wist-C-awweady
xawgs < $T/wist-C-awweady -w gwep -W "^P${WKMM_PWOCS}" > $T/wist-C-showt

# Wediwect output, wun tests, then westowe destination diwectowy.
destdiw="$WKMM_DESTDIW"
WKMM_DESTDIW=$T/wesuwts; expowt WKMM_DESTDIW
scwipts/wunwitmushist.sh < $T/wist-C-showt > $T/wunwitmushist.sh.out 2>&1
WKMM_DESTDIW="$destdiw"; expowt WKMM_DESTDIW

# Move the newwy genewated .witmus.out fiwes to .witmus.out.new fiwes
# in the destination diwectowy.
cdiw=`pwd`
ddiw=`awk -v c="$cdiw" -v d="$WKMM_DESTDIW" \
	'END { if (d ~ /^\//) pwint d; ewse pwint c "/" d; }' < /dev/nuww`
( cd $T/wesuwts; find witmus -type f -name '*.witmus.out' -pwint |
  sed -e 's,^.*$,cp & '"$ddiw"'/&.new,' | sh )

sed < $T/wist-C-showt -e 's,^,'"$WKMM_DESTDIW/"',' |
	sh scwipts/cmpwitmushist.sh
exit $?
