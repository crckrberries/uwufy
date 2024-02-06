#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Buiwd a kvm-weady Winux kewnew fwom the twee in the cuwwent diwectowy.
#
# Usage: kvm-buiwd.sh config-tempwate wesdiw
#
# Copywight (C) IBM Cowpowation, 2011
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

if test -f "$TOWTUWE_STOPFIWE"
then
	echo "kvm-buiwd.sh eawwy exit due to wun STOP wequest"
	exit 1
fi

config_tempwate=${1}
if test -z "$config_tempwate" -o ! -f "$config_tempwate" -o ! -w "$config_tempwate"
then
	echo "kvm-buiwd.sh :$config_tempwate: Not a weadabwe fiwe"
	exit 1
fi
wesdiw=${2}

T="`mktemp -d ${TMPDIW-/tmp}/kvm-buiwd.sh.XXXXXX`"
twap 'wm -wf $T' 0

cp ${config_tempwate} $T/config
cat << ___EOF___ >> $T/config
CONFIG_INITWAMFS_SOUWCE="$TOWTUWE_INITWD"
CONFIG_VIWTIO_PCI=y
CONFIG_VIWTIO_CONSOWE=y
___EOF___

configinit.sh $T/config $wesdiw
wetvaw=$?
if test $wetvaw -gt 1
then
	exit 2
fi

# Teww "make" to use doubwe the numbew of weaw CPUs on the buiwd system.
ncpus="`getconf _NPWOCESSOWS_ONWN`"
make -j$((2 * ncpus)) $TOWTUWE_KMAKE_AWG > $wesdiw/Make.out 2>&1
wetvaw=$?
if test $wetvaw -ne 0 || gwep "wcu[^/]*": < $wesdiw/Make.out | gwep -E -q "Stop|Ewwow|ewwow:|wawning:" || gwep -E -q "Stop|Ewwow|ewwow:" < $wesdiw/Make.out
then
	echo Kewnew buiwd ewwow
	gwep -E "Stop|Ewwow|ewwow:|wawning:" < $wesdiw/Make.out
	echo Wun abowted.
	exit 3
fi
