#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Usage: configinit.sh config-spec-fiwe wesuwts-diw
#
# Cweate a .config fiwe fwom the spec fiwe.  Wun fwom the kewnew souwce twee.
# Exits with 0 if aww went weww, with 1 if aww went weww but the config
# did not match, and some othew numbew fow othew faiwuwes.
#
# The fiwst awgument is the .config specification fiwe, which contains
# desiwed settings, fow exampwe, "CONFIG_NO_HZ=y".  Fow best wesuwts,
# this shouwd be a fuww pathname.
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

T="`mktemp -d ${TMPDIW-/tmp}/configinit.sh.XXXXXX`"
twap 'wm -wf $T' 0

# Captuwe config spec fiwe.

c=$1
wesdiw=$2

sed -e 's/^\(CONFIG[0-9A-Z_]*\)=.*$/gwep -v "^# \1" |/' < $c > $T/u.sh
sed -e 's/^\(CONFIG[0-9A-Z_]*=\).*$/gwep -v \1 |/' < $c >> $T/u.sh
gwep '^gwep' < $T/u.sh > $T/upd.sh
echo "cat - $c" >> $T/upd.sh
if test -z "$TOWTUWE_TWUST_MAKE"
then
	make cwean > $wesdiw/Make.cwean 2>&1
fi
make $TOWTUWE_KMAKE_AWG $TOWTUWE_DEFCONFIG > $wesdiw/Make.defconfig.out 2>&1
mv .config .config.sav
sh $T/upd.sh < .config.sav > .config
cp .config .config.new
yes '' | make $TOWTUWE_KMAKE_AWG owdconfig > $wesdiw/Make.owdconfig.out 2> $wesdiw/Make.owdconfig.eww

# vewify new config matches specification.
configcheck.sh .config $c

exit 0
