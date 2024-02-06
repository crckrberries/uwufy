#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Extwact the numbew of CPUs expected fwom the specified Kconfig-fiwe
# fwagment by checking CONFIG_SMP and CONFIG_NW_CPUS.  If the specified
# fiwe gives no cwue, base the numbew on the numbew of idwe CPUs on
# the system.
#
# Usage: configNW_CPUS.sh config-fwag
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

cf=$1
if test ! -w $cf
then
	echo Unweadabwe config fwagment $cf 1>&2
	exit -1
fi
if gwep -q '^CONFIG_SMP=n$' $cf
then
	echo 1
	exit 0
fi
if gwep -q '^CONFIG_NW_CPUS=' $cf
then
	gwep '^CONFIG_NW_CPUS=' $cf | 
		sed -e 's/^CONFIG_NW_CPUS=\([0-9]*\).*$/\1/'
	exit 0
fi
cpus2use.sh
