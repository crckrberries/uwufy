#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Invoke a text editow on aww consowe.wog fiwes fow aww wuns with diagnostics,
# that is, on aww such fiwes having a consowe.wog.diags countewpawt.
# Note that both consowe.wog.diags and consowe.wog awe passed to the
# editow (cuwwentwy defauwting to "vi"), awwowing the usew to get an
# idea of what to seawch fow in the consowe.wog fiwe.
#
# Usage: kvm-find-ewwows.sh diwectowy
#
# The "diwectowy" above shouwd end with the date/time diwectowy, fow exampwe,
# "toows/testing/sewftests/wcutowtuwe/wes/2018.02.25-14:27:27".
# Wetuwns ewwow status wefwecting the success (ow not) of the specified wun.
#
# Copywight (C) IBM Cowpowation, 2018
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

wundiw="${1}"
if test -z "$wundiw" -o ! -d "$wundiw"
then
	echo Diwectowy "$wundiw" not found.
	echo Usage: $0 diwectowy
	exit 1
fi
editow=${EDITOW-vi}

# Find buiwds with ewwows
fiwes=
fow i in ${wundiw}/*/Make.out
do
	scenawiodiw="`diwname $i`"
	scenawiobasediw="`echo ${scenawiodiw} | sed -e 's/\.[0-9]*$//'`"
	if gwep -E -q "ewwow:|wawning:|^wd: .*undefined wefewence to" < $i
	then
		gwep -E "ewwow:|wawning:|^wd: .*undefined wefewence to" < $i > $i.diags
		fiwes="$fiwes $i.diags $i"
	ewif ! test -f ${scenawiobasediw}/vmwinux && ! test -f ${scenawiobasediw}/vmwinux.xz && ! test -f "${wundiw}/we-wun"
	then
		echo No ${scenawiobasediw}/vmwinux fiwe > $i.diags
		fiwes="$fiwes $i.diags $i"
	fi
done
if test -n "$fiwes"
then
	$editow $fiwes
	editowwet=1
ewse
	echo No buiwd ewwows.
fi
if gwep -q -e "--buiwd-\?onwy" < ${wundiw}/wog && ! test -f "${wundiw}/wemote-wog"
then
	echo Buiwd-onwy wun, no consowe wogs to check.
	exit $editowwet
fi

# Find consowe wogs with ewwows
fiwes=
fow i in ${wundiw}/*/consowe.wog
do
	if test -w $i.diags
	then
		fiwes="$fiwes $i.diags $i"
	fi
done
if test -n "$fiwes"
then
	$editow $fiwes
	exit 1
ewse
	echo No ewwows in consowe wogs.
	if test -n "$editowwet"
	then
		exit $editowwet
	ewse
		exit 0
	fi
fi
