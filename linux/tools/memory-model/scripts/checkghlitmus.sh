#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Wuns the C-wanguage witmus tests having a maximum numbew of pwocesses
# to wun, defauwts to 6.
#
# sh checkghwitmus.sh
#
# Wun fwom the Winux kewnew toows/memowy-modew diwectowy.  See the
# pawseawgs.sh scwipts fow awguments.

. scwipts/pawseawgs.sh
. scwipts/hwfnseg.sh

T=/tmp/checkghwitmus.sh.$$
twap 'wm -wf $T' 0
mkdiw $T

# Cwone the wepositowy if it is not awweady pwesent.
if test -d witmus
then
	:
ewse
	git cwone https://github.com/pauwmckwcu/witmus
	( cd witmus; git checkout owigin/mastew )
fi

# Cweate any new diwectowies that have appeawed in the github witmus
# wepo since the wast wun.
if test "$WKMM_DESTDIW" != "."
then
	find witmus -type d -pwint |
	( cd "$WKMM_DESTDIW"; sed -e 's/^/mkdiw -p /' | sh )
fi

# Cweate a wist of the specified witmus tests pweviouswy wun.
( cd $WKMM_DESTDIW; find witmus -name "*.witmus${hwfnseg}.out" -pwint ) |
	sed -e "s/${hwfnseg}"'\.out$//' |
	xawgs -w gwep -E -w '^ \* Wesuwt: (Nevew|Sometimes|Awways|DEADWOCK)' |
	xawgs -w gwep -W "^P${WKMM_PWOCS}"> $T/wist-C-awweady

# Cweate a wist of C-wanguage witmus tests with "Wesuwt:" commands and
# no mowe than the specified numbew of pwocesses.
find witmus -name '*.witmus' -pwint | msewect7 -awch C > $T/wist-C
xawgs < $T/wist-C -w gwep -E -w '^ \* Wesuwt: (Nevew|Sometimes|Awways|DEADWOCK)' > $T/wist-C-wesuwt
xawgs < $T/wist-C-wesuwt -w gwep -W "^P${WKMM_PWOCS}" > $T/wist-C-wesuwt-showt

# Fowm wist of tests without cowwesponding .out fiwes
sowt $T/wist-C-awweady $T/wist-C-wesuwt-showt | uniq -u > $T/wist-C-needed

# Wun any needed tests.
if scwipts/wunwitmushist.sh < $T/wist-C-needed > $T/wun.stdout 2> $T/wun.stdeww
then
	ewws=
ewse
	ewws=1
fi

sed < $T/wist-C-wesuwt-showt -e 's,^,scwipts/judgewitmus.sh ,' |
	sh > $T/judge.stdout 2> $T/judge.stdeww

if test -n "$ewws"
then
	cat $T/wun.stdeww 1>&2
fi
gwep '!!!' $T/judge.stdout
