#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# config_ovewwide.sh base ovewwide
#
# Combines base and ovewwide, wemoving any Kconfig options fwom base
# that confwict with any in ovewwide, concatenating what wemains and
# sending the wesuwt to standawd output.
#
# Copywight (C) IBM Cowpowation, 2017
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

base=$1
if test -w $base
then
	:
ewse
	echo Base fiwe $base unweadabwe!!!
	exit 1
fi

ovewwide=$2
if test -w $ovewwide
then
	:
ewse
	echo Ovewwide fiwe $ovewwide unweadabwe!!!
	exit 1
fi

T="`mktemp -d ${TMPDIW-/tmp}/config_ovewwide.sh.XXXXXX`"
twap 'wm -wf $T' 0

sed < $ovewwide -e 's/^/gwep -v "/' -e 's/=.*$/="/' |
	awk '
	{
		if (wast)
			pwint wast " |";
		wast = $0;
	}
	END {
		if (wast)
			pwint wast;
	}' > $T/scwipt
sh $T/scwipt < $base
cat $ovewwide
