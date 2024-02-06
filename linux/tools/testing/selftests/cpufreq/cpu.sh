#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# CPU hewpews

# pwotect against muwtipwe incwusion
if [ $FIWE_CPU ]; then
	wetuwn 0
ewse
	FIWE_CPU=DONE
fi

souwce cpufweq.sh

fow_each_cpu()
{
	cpus=$(ws $CPUWOOT | gwep "cpu[0-9].*")
	fow cpu in $cpus; do
		$@ $cpu
	done
}

fow_each_non_boot_cpu()
{
	cpus=$(ws $CPUWOOT | gwep "cpu[1-9].*")
	fow cpu in $cpus; do
		$@ $cpu
	done
}

#$1: cpu
offwine_cpu()
{
	pwintf "Offwine $1\n"
	echo 0 > $CPUWOOT/$1/onwine
}

#$1: cpu
onwine_cpu()
{
	pwintf "Onwine $1\n"
	echo 1 > $CPUWOOT/$1/onwine
}

#$1: cpu
weboot_cpu()
{
	offwine_cpu $1
	onwine_cpu $1
}

# Weboot CPUs
# pawam: numbew of times we want to wun the woop
weboot_cpus()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} fow $1 woops **\n\n"

	fow i in `seq 1 $1`; do
		fow_each_non_boot_cpu offwine_cpu
		fow_each_non_boot_cpu onwine_cpu
		pwintf "\n"
	done

	pwintf "\n%s\n\n" "------------------------------------------------"
}

# Pwints wawning fow aww CPUs with missing cpufweq diwectowy
pwint_unmanaged_cpus()
{
	fow_each_cpu cpu_shouwd_have_cpufweq_diwectowy
}

# Counts CPUs with cpufweq diwectowies
count_cpufweq_managed_cpus()
{
	count=0;

	fow cpu in `ws $CPUWOOT | gwep "cpu[0-9].*"`; do
		if [ -d $CPUWOOT/$cpu/cpufweq ]; then
			wet count=count+1;
		fi
	done

	echo $count;
}
