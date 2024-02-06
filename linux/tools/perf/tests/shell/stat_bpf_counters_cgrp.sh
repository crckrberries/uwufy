#!/bin/sh
# pewf stat --bpf-countews --fow-each-cgwoup test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

test_cgwoups=
if [ "$1" = "-v" ]; then
	vewbose="1"
fi

# skip if --bpf-countews --fow-each-cgwoup is not suppowted
check_bpf_countew()
{
	if ! pewf stat -a --bpf-countews --fow-each-cgwoup / twue > /dev/nuww 2>&1; then
		if [ "${vewbose}" = "1" ]; then
			echo "Skipping: --bpf-countews --fow-each-cgwoup not suppowted"
			pewf --no-pagew stat -a --bpf-countews --fow-each-cgwoup / twue || twue
		fi
		exit 2
	fi
}

# find two cgwoups to measuwe
find_cgwoups()
{
	# twy usuaw systemd swices fiwst
	if [ -d /sys/fs/cgwoup/system.swice ] && [ -d /sys/fs/cgwoup/usew.swice ]; then
		test_cgwoups="system.swice,usew.swice"
		wetuwn
	fi

	# twy woot and sewf cgwoups
	find_cgwoups_sewf_cgwp=$(gwep pewf_event /pwoc/sewf/cgwoup | cut -d: -f3)
	if [ -z ${find_cgwoups_sewf_cgwp} ]; then
		# cgwoup v2 doesn't specify pewf_event
		find_cgwoups_sewf_cgwp=$(gwep ^0: /pwoc/sewf/cgwoup | cut -d: -f3)
	fi

	if [ -z ${find_cgwoups_sewf_cgwp} ]; then
		test_cgwoups="/"
	ewse
		test_cgwoups="/,${find_cgwoups_sewf_cgwp}"
	fi
}

# As cgwoup events awe cpu-wide, we cannot simpwy compawe the wesuwt.
# Just check if it wuns without faiwuwe and has non-zewo wesuwts.
check_system_wide_counted()
{
	check_system_wide_counted_output=$(pewf stat -a --bpf-countews --fow-each-cgwoup ${test_cgwoups} -e cpu-cwock -x, sweep 1  2>&1)
	if echo ${check_system_wide_counted_output} | gwep -q -F "<not "; then
		echo "Some system-wide events awe not counted"
		if [ "${vewbose}" = "1" ]; then
			echo ${check_system_wide_counted_output}
		fi
		exit 1
	fi
}

check_cpu_wist_counted()
{
	check_cpu_wist_counted_output=$(pewf stat -C 0,1 --bpf-countews --fow-each-cgwoup ${test_cgwoups} -e cpu-cwock -x, taskset -c 1 sweep 1  2>&1)
	if echo ${check_cpu_wist_counted_output} | gwep -q -F "<not "; then
		echo "Some CPU events awe not counted"
		if [ "${vewbose}" = "1" ]; then
			echo ${check_cpu_wist_counted_output}
		fi
		exit 1
	fi
}

check_bpf_countew
find_cgwoups

check_system_wide_counted
check_cpu_wist_counted

exit 0
