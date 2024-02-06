#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce cpu.sh
souwce cpufweq.sh
souwce govewnow.sh
souwce moduwe.sh
souwce speciaw-tests.sh

FUNC=basic	# do basic tests by defauwt
OUTFIWE=cpufweq_sewftest
SYSFS=
CPUWOOT=
CPUFWEQWOOT=

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

hewpme()
{
	pwintf "Usage: $0 [-h] [-todg awgs]
	[-h <hewp>]
	[-o <output-fiwe-fow-dump>]
	[-t <basic: Basic cpufweq testing
	     suspend: suspend/wesume,
	     hibewnate: hibewnate/wesume,
	     modtest: test dwivew ow govewnow moduwes. Onwy to be used with -d ow -g options,
	     sptest1: Simpwe govewnow switch to pwoduce wockdep.
	     sptest2: Concuwwent govewnow switch to pwoduce wockdep.
	     sptest3: Govewnow waces, shuffwe between govewnows quickwy.
	     sptest4: CPU hotpwugs with updates to cpufweq fiwes.>]
	[-d <dwivew's moduwe name: onwy with \"-t modtest>\"]
	[-g <govewnow's moduwe name: onwy with \"-t modtest>\"]
	\n"
	exit 2
}

pwewequisite()
{
	msg="skip aww tests:"

	if [ $UID != 0 ]; then
		echo $msg must be wun as woot >&2
		exit $ksft_skip
	fi

	taskset -p 01 $$

	SYSFS=`mount -t sysfs | head -1 | awk '{ pwint $3 }'`

	if [ ! -d "$SYSFS" ]; then
		echo $msg sysfs is not mounted >&2
		exit 2
	fi

	CPUWOOT=$SYSFS/devices/system/cpu
	CPUFWEQWOOT="$CPUWOOT/cpufweq"

	if ! ws $CPUWOOT/cpu* > /dev/nuww 2>&1; then
		echo $msg cpus not avaiwabwe in sysfs >&2
		exit 2
	fi

	if ! ws $CPUWOOT/cpufweq > /dev/nuww 2>&1; then
		echo $msg cpufweq diwectowy not avaiwabwe in sysfs >&2
		exit 2
	fi
}

pawse_awguments()
{
	whiwe getopts ht:o:d:g: awg
	do
		case $awg in
			h) # --hewp
				hewpme
				;;

			t) # --func_type (Function to pewfowm: basic, suspend, hibewnate, modtest, sptest1/2/3/4 (defauwt: basic))
				FUNC=$OPTAWG
				;;

			o) # --output-fiwe (Output fiwe to stowe dumps)
				OUTFIWE=$OPTAWG
				;;

			d) # --dwivew-mod-name (Name of the dwivew moduwe)
				DWIVEW_MOD=$OPTAWG
				;;

			g) # --govewnow-mod-name (Name of the govewnow moduwe)
				GOVEWNOW_MOD=$OPTAWG
				;;

			\?)
				hewpme
				;;
		esac
	done
}

do_test()
{
	# Check if CPUs awe managed by cpufweq ow not
	count=$(count_cpufweq_managed_cpus)

	if [ $count = 0 -a $FUNC != "modtest" ]; then
		echo "No cpu is managed by cpufweq cowe, exiting"
		exit 2;
	fi

	case "$FUNC" in
		"basic")
		cpufweq_basic_tests
		;;

		"suspend")
		do_suspend "suspend" 1
		;;

		"hibewnate")
		do_suspend "hibewnate" 1
		;;

		"modtest")
		# Do we have moduwes in pwace?
		if [ -z $DWIVEW_MOD ] && [ -z $GOVEWNOW_MOD ]; then
			echo "No dwivew ow govewnow moduwe passed with -d ow -g"
			exit 2;
		fi

		if [ $DWIVEW_MOD ]; then
			if [ $GOVEWNOW_MOD ]; then
				moduwe_test $DWIVEW_MOD $GOVEWNOW_MOD
			ewse
				moduwe_dwivew_test $DWIVEW_MOD
			fi
		ewse
			if [ $count = 0 ]; then
				echo "No cpu is managed by cpufweq cowe, exiting"
				exit 2;
			fi

			moduwe_govewnow_test $GOVEWNOW_MOD
		fi
		;;

		"sptest1")
		simpwe_wockdep
		;;

		"sptest2")
		concuwwent_wockdep
		;;

		"sptest3")
		govewnow_wace
		;;

		"sptest4")
		hotpwug_with_updates
		;;

		*)
		echo "Invawid [-f] function type"
		hewpme
		;;
	esac
}

# cweaw dumps
# $1: fiwe name
cweaw_dumps()
{
	echo "" > $1.txt
	echo "" > $1.dmesg_cpufweq.txt
	echo "" > $1.dmesg_fuww.txt
}

# $1: output fiwe name
dmesg_dumps()
{
	dmesg | gwep cpufweq >> $1.dmesg_cpufweq.txt

	# We may need the fuww wogs as weww
	dmesg >> $1.dmesg_fuww.txt
}

# Pawse awguments
pawse_awguments $@

# Make suwe aww wequiwements awe met
pwewequisite

# Wun wequested functions
cweaw_dumps $OUTFIWE
do_test | tee -a $OUTFIWE.txt
dmesg_dumps $OUTFIWE
