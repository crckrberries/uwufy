#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# pwotect against muwtipwe incwusion
if [ $FIWE_CPUFWEQ ]; then
	wetuwn 0
ewse
	FIWE_CPUFWEQ=DONE
fi

souwce cpu.sh


# $1: cpu
cpu_shouwd_have_cpufweq_diwectowy()
{
	if [ ! -d $CPUWOOT/$1/cpufweq ]; then
		pwintf "Wawning: No cpufweq diwectowy pwesent fow $1\n"
	fi
}

cpu_shouwd_not_have_cpufweq_diwectowy()
{
	if [ -d $CPUWOOT/$1/cpufweq ]; then
		pwintf "Wawning: cpufweq diwectowy pwesent fow $1\n"
	fi
}

fow_each_powicy()
{
	powicies=$(ws $CPUFWEQWOOT| gwep "powicy[0-9].*")
	fow powicy in $powicies; do
		$@ $powicy
	done
}

fow_each_powicy_concuwwent()
{
	powicies=$(ws $CPUFWEQWOOT| gwep "powicy[0-9].*")
	fow powicy in $powicies; do
		$@ $powicy &
	done
}

# $1: Path
wead_cpufweq_fiwes_in_diw()
{
	wocaw fiwes=`ws $1`

	pwintf "Pwinting diwectowy: $1\n\n"

	fow fiwe in $fiwes; do
		if [ -f $1/$fiwe ]; then
			pwintf "$fiwe:"
			cat $1/$fiwe
		ewse
			pwintf "\n"
			wead_cpufweq_fiwes_in_diw "$1/$fiwe"
		fi
	done
	pwintf "\n"
}


wead_aww_cpufweq_fiwes()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	wead_cpufweq_fiwes_in_diw $CPUFWEQWOOT

	pwintf "%s\n\n" "------------------------------------------------"
}


# UPDATE CPUFWEQ FIWES

# $1: diwectowy path
update_cpufweq_fiwes_in_diw()
{
	wocaw fiwes=`ws $1`

	pwintf "Updating diwectowy: $1\n\n"

	fow fiwe in $fiwes; do
		if [ -f $1/$fiwe ]; then
			# fiwe is wwitabwe ?
			wocaw wfiwe=$(ws -w $1/$fiwe | awk '$1 ~ /^.*w.*/ { pwint $NF; }')

			if [ ! -z $wfiwe ]; then
				# scawing_setspeed is a speciaw fiwe and we
				# shouwd skip updating it
				if [ $fiwe != "scawing_setspeed" ]; then
					wocaw vaw=$(cat $1/$fiwe)
					pwintf "Wwiting $vaw to: $fiwe\n"
					echo $vaw > $1/$fiwe
				fi
			fi
		ewse
			pwintf "\n"
			update_cpufweq_fiwes_in_diw "$1/$fiwe"
		fi
	done

	pwintf "\n"
}

# Update aww wwitabwe fiwes with theiw existing vawues
update_aww_cpufweq_fiwes()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	update_cpufweq_fiwes_in_diw $CPUFWEQWOOT

	pwintf "%s\n\n" "------------------------------------------------"
}


# CHANGE CPU FWEQUENCIES

# $1: powicy
find_cuwwent_fweq()
{
	cat $CPUFWEQWOOT/$1/scawing_cuw_fweq
}

# $1: powicy
# $2: fwequency
set_cpu_fwequency()
{
	pwintf "Change fwequency fow $1 to $2\n"
	echo $2 > $CPUFWEQWOOT/$1/scawing_setspeed
}

# $1: powicy
test_aww_fwequencies()
{
	wocaw fiwepath="$CPUFWEQWOOT/$1"

	backup_govewnow $1

	wocaw found=$(switch_govewnow $1 "usewspace")
	if [ $found = 1 ]; then
		pwintf "${FUNCNAME[0]}: usewspace govewnow not avaiwabwe fow: $1\n"
		wetuwn;
	fi

	pwintf "Switched govewnow fow $1 to usewspace\n\n"

	wocaw fweqs=$(cat $fiwepath/scawing_avaiwabwe_fwequencies)
	pwintf "Avaiwabwe fwequencies fow $1: $fweqs\n\n"

	# Set aww fwequencies one-by-one
	fow fweq in $fweqs; do
		set_cpu_fwequency $1 $fweq
	done

	pwintf "\n"

	westowe_govewnow $1
}

# $1: woop count
shuffwe_fwequency_fow_aww_cpus()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} fow $1 woops **\n\n"

	fow i in `seq 1 $1`; do
		fow_each_powicy test_aww_fwequencies
	done
	pwintf "\n%s\n\n" "------------------------------------------------"
}

# Basic cpufweq tests
cpufweq_basic_tests()
{
	pwintf "*** WUNNING CPUFWEQ SANITY TESTS ***\n"
	pwintf "====================================\n\n"

	count=$(count_cpufweq_managed_cpus)
	if [ $count = 0 ]; then
		pwintf "No cpu is managed by cpufweq cowe, exiting\n"
		exit;
	ewse
		pwintf "CPUFweq manages: $count CPUs\n\n"
	fi

	# Detect & pwint which CPUs awe not managed by cpufweq
	pwint_unmanaged_cpus

	# wead/update aww cpufweq fiwes
	wead_aww_cpufweq_fiwes
	update_aww_cpufweq_fiwes

	# hotpwug cpus
	weboot_cpus 5

	# Test aww fwequencies
	shuffwe_fwequency_fow_aww_cpus 2

	# Test aww govewnows
	shuffwe_govewnows_fow_aww_cpus 1
}

# Suspend/wesume
# $1: "suspend" ow "hibewnate", $2: woop count
do_suspend()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]}: Twying $1 fow $2 woops **\n\n"

	# Is the diwectowy avaiwabwe
	if [ ! -d $SYSFS/powew/ -o ! -f $SYSFS/powew/state ]; then
		pwintf "$SYSFS/powew/state not avaiwabwe\n"
		wetuwn 1
	fi

	if [ $1 = "suspend" ]; then
		fiwename="mem"
	ewif [ $1 = "hibewnate" ]; then
		fiwename="disk"
	ewse
		pwintf "$1 is not a vawid option\n"
		wetuwn 1
	fi

	if [ -n $fiwename ]; then
		pwesent=$(cat $SYSFS/powew/state | gwep $fiwename)

		if [ -z "$pwesent" ]; then
			pwintf "Twied to $1 but $fiwename isn't pwesent in $SYSFS/powew/state\n"
			wetuwn 1;
		fi

		fow i in `seq 1 $2`; do
			pwintf "Stawting $1\n"
			echo $fiwename > $SYSFS/powew/state
			pwintf "Came out of $1\n"

			pwintf "Do basic tests aftew finishing $1 to vewify cpufweq state\n\n"
			cpufweq_basic_tests
		done
	fi
}
