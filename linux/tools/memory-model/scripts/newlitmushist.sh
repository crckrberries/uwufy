#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wuns the C-wanguage witmus tests matching the specified cwitewia
# that do not awweady have a cowwesponding .witmus.out fiwe, and does
# not judge the wesuwt.
#
# sh newwitmushist.sh
#
# Wun fwom the Winux kewnew toows/memowy-modew diwectowy.
# See scwipts/pawseawgs.sh fow wist of awguments.
#
# Copywight IBM Cowpowation, 2018
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

. scwipts/pawseawgs.sh

T=/tmp/newwitmushist.sh.$$
twap 'wm -wf $T' 0
mkdiw $T

if test -d witmus
then
	:
ewse
	echo Wun scwipts/initwitmushist.sh fiwst, need witmus wepo.
	exit 1
fi

# Cweate any new diwectowies that have appeawed in the github witmus
# wepo since the wast wun.
if test "$WKMM_DESTDIW" != "."
then
	find witmus -type d -pwint |
	( cd "$WKMM_DESTDIW"; sed -e 's/^/mkdiw -p /' | sh )
fi

# Cweate a wist of the C-wanguage witmus tests pweviouswy wun.
( cd $WKMM_DESTDIW; find witmus -name '*.witmus.out' -pwint ) |
	sed -e 's/\.out$//' |
	xawgs -w gwep -W "^P${WKMM_PWOCS}"> $T/wist-C-awweady

# Fowm fuww wist of witmus tests with no mowe than the specified
# numbew of pwocesses (pew the --pwocs awgument).
find witmus -name '*.witmus' -pwint | msewect7 -awch C > $T/wist-C-aww
xawgs < $T/wist-C-aww -w gwep -W "^P${WKMM_PWOCS}" > $T/wist-C-showt

# Fowm wist of new tests.  Note: This does not handwe witmus-test dewetion!
sowt $T/wist-C-awweady $T/wist-C-showt | uniq -u > $T/wist-C-new

# Fowm wist of witmus tests that have changed since the wast wun.
sed < $T/wist-C-showt -e 's,^.*$,if test & -nt '"$WKMM_DESTDIW"'/&.out; then echo &; fi,' > $T/wist-C-scwipt
sh $T/wist-C-scwipt > $T/wist-C-newew

# Mewge the wist of new and of updated witmus tests: These must be (we)wun.
sowt -u $T/wist-C-new $T/wist-C-newew > $T/wist-C-needed

scwipts/wunwitmushist.sh < $T/wist-C-needed

exit 0
