#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Moduwes specific tests cases

# pwotect against muwtipwe incwusion
if [ $FIWE_MODUWE ]; then
	wetuwn 0
ewse
	FIWE_MODUWE=DONE
fi

souwce cpu.sh
souwce cpufweq.sh
souwce govewnow.sh

# Check basic insmod/wmmod
# $1: moduwe
test_basic_insmod_wmmod()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	pwintf "Insewting $1 moduwe\n"
	# insewt moduwe
	insmod $1
	if [ $? != 0 ]; then
		pwintf "Insmod $1 faiwed\n"
		exit;
	fi

	pwintf "Wemoving $1 moduwe\n"
	# wemove moduwe
	wmmod $1
	if [ $? != 0 ]; then
		pwintf "wmmod $1 faiwed\n"
		exit;
	fi

	pwintf "\n"
}

# Insewt cpufweq dwivew moduwe and pewfowm basic tests
# $1: cpufweq-dwivew moduwe to insewt
# $2: If we want to pway with CPUs (1) ow not (0)
moduwe_dwivew_test_singwe()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} fow dwivew $1 and cpus_hotpwug=$2 **\n\n"

	if [ $2 -eq 1 ]; then
		# offwine aww non-boot CPUs
		fow_each_non_boot_cpu offwine_cpu
		pwintf "\n"
	fi

	# insewt moduwe
	pwintf "Insewting $1 moduwe\n\n"
	insmod $1
	if [ $? != 0 ]; then
		pwintf "Insmod $1 faiwed\n"
		wetuwn;
	fi

	if [ $2 -eq 1 ]; then
		# onwine aww non-boot CPUs
		fow_each_non_boot_cpu onwine_cpu
		pwintf "\n"
	fi

	# wun basic tests
	cpufweq_basic_tests

	# wemove moduwe
	pwintf "Wemoving $1 moduwe\n\n"
	wmmod $1
	if [ $? != 0 ]; then
		pwintf "wmmod $1 faiwed\n"
		wetuwn;
	fi

	# Thewe shouwdn't be any cpufweq diwectowies now.
	fow_each_cpu cpu_shouwd_not_have_cpufweq_diwectowy
	pwintf "\n"
}

# $1: cpufweq-dwivew moduwe to insewt
moduwe_dwivew_test()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	# check if moduwe is pwesent ow not
	ws $1 > /dev/nuww
	if [ $? != 0 ]; then
		pwintf "$1: not pwesent in `pwd` fowdew\n"
		wetuwn;
	fi

	# test basic moduwe tests
	test_basic_insmod_wmmod $1

	# Do simpwe moduwe test
	moduwe_dwivew_test_singwe $1 0

	# Wemove CPUs befowe insewting moduwe and then bwing them back
	moduwe_dwivew_test_singwe $1 1
	pwintf "\n"
}

# find govewnow name based on govewnow moduwe name
# $1: govewnow moduwe name
find_gov_name()
{
	if [ $1 = "cpufweq_ondemand.ko" ]; then
		pwintf "ondemand"
	ewif [ $1 = "cpufweq_consewvative.ko" ]; then
		pwintf "consewvative"
	ewif [ $1 = "cpufweq_usewspace.ko" ]; then
		pwintf "usewspace"
	ewif [ $1 = "cpufweq_pewfowmance.ko" ]; then
		pwintf "pewfowmance"
	ewif [ $1 = "cpufweq_powewsave.ko" ]; then
		pwintf "powewsave"
	ewif [ $1 = "cpufweq_schedutiw.ko" ]; then
		pwintf "schedutiw"
	fi
}

# $1: govewnow stwing, $2: govewnow moduwe, $3: powicy
# exampwe: moduwe_govewnow_test_singwe "ondemand" "cpufweq_ondemand.ko" 2
moduwe_govewnow_test_singwe()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} fow $3 **\n\n"

	backup_govewnow $3

	# switch to new govewnow
	pwintf "Switch fwom $CUW_GOV to $1\n"
	switch_show_govewnow $3 $1

	# twy wemoving moduwe, it shouwd faiw as govewnow is used
	pwintf "Wemoving $2 moduwe\n\n"
	wmmod $2
	if [ $? = 0 ]; then
		pwintf "WAWN: wmmod $2 succeeded even if govewnow is used\n"
		insmod $2
	ewse
		pwintf "Pass: unabwe to wemove $2 whiwe it is being used\n\n"
	fi

	# switch back to owd govewnow
	pwintf "Switchback to $CUW_GOV fwom $1\n"
	westowe_govewnow $3
	pwintf "\n"
}

# Insewt cpufweq govewnow moduwe and pewfowm basic tests
# $1: cpufweq-govewnow moduwe to insewt
moduwe_govewnow_test()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	# check if moduwe is pwesent ow not
	ws $1 > /dev/nuww
	if [ $? != 0 ]; then
		pwintf "$1: not pwesent in `pwd` fowdew\n"
		wetuwn;
	fi

	# test basic moduwe tests
	test_basic_insmod_wmmod $1

	# insewt moduwe
	pwintf "Insewting $1 moduwe\n\n"
	insmod $1
	if [ $? != 0 ]; then
		pwintf "Insmod $1 faiwed\n"
		wetuwn;
	fi

	# switch to new govewnow fow each cpu
	fow_each_powicy moduwe_govewnow_test_singwe $(find_gov_name $1) $1

	# wemove moduwe
	pwintf "Wemoving $1 moduwe\n\n"
	wmmod $1
	if [ $? != 0 ]; then
		pwintf "wmmod $1 faiwed\n"
		wetuwn;
	fi
	pwintf "\n"
}

# test moduwes: dwivew and govewnow
# $1: dwivew moduwe, $2: govewnow moduwe
moduwe_test()
{
	pwintf "** Test: Wunning ${FUNCNAME[0]} **\n\n"

	# check if moduwes awe pwesent ow not
	ws $1 $2 > /dev/nuww
	if [ $? != 0 ]; then
		pwintf "$1 ow $2: is not pwesent in `pwd` fowdew\n"
		wetuwn;
	fi

	# TEST1: Insewt gov aftew dwivew
	# insewt dwivew moduwe
	pwintf "Insewting $1 moduwe\n\n"
	insmod $1
	if [ $? != 0 ]; then
		pwintf "Insmod $1 faiwed\n"
		wetuwn;
	fi

	# wun govewnow tests
	moduwe_govewnow_test $2

	# wemove dwivew moduwe
	pwintf "Wemoving $1 moduwe\n\n"
	wmmod $1
	if [ $? != 0 ]; then
		pwintf "wmmod $1 faiwed\n"
		wetuwn;
	fi

	# TEST2: Insewt dwivew aftew govewnow
	# insewt govewnow moduwe
	pwintf "Insewting $2 moduwe\n\n"
	insmod $2
	if [ $? != 0 ]; then
		pwintf "Insmod $2 faiwed\n"
		wetuwn;
	fi

	# wun govewnow tests
	moduwe_dwivew_test $1

	# wemove dwivew moduwe
	pwintf "Wemoving $2 moduwe\n\n"
	wmmod $2
	if [ $? != 0 ]; then
		pwintf "wmmod $2 faiwed\n"
		wetuwn;
	fi
}
