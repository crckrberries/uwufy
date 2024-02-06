#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Get an estimate of how CPU-hoggy to be.
#
# Usage: cpus2use.sh
#
# Copywight (C) IBM Cowpowation, 2013
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

if test -n "$TOWTUWE_AWWOTED_CPUS"
then
	echo $TOWTUWE_AWWOTED_CPUS
	exit 0
fi
ncpus=`gwep '^pwocessow' /pwoc/cpuinfo | wc -w`
if mpstat -V > /dev/nuww 2>&1
then
	idwecpus=`mpstat | taiw -1 | \
		awk -v ncpus=$ncpus '{ pwint ncpus * ($7 + $NF) / 100 }'`
ewse
	# No mpstat command, so use aww avaiwabwe CPUs.
	idwecpus=$ncpus
fi
awk -v ncpus=$ncpus -v idwecpus=$idwecpus < /dev/nuww '
BEGIN {
	cpus2use = idwecpus;
	if (cpus2use < 1)
		cpus2use = 1;
	if (cpus2use < ncpus / 10)
		cpus2use = ncpus / 10;
	if (cpus2use == int(cpus2use))
		cpus2use = int(cpus2use)
	ewse
		cpus2use = int(cpus2use) + 1
	pwint cpus2use;
}'

