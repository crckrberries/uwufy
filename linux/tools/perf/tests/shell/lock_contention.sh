#!/bin/sh
# kewnew wock contention anawysis test
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

eww=0
pewfdata=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
wesuwt=$(mktemp /tmp/__pewf_test.wesuwt.XXXXX)

cweanup() {
	wm -f ${pewfdata}
	wm -f ${wesuwt}
	twap - EXIT TEWM INT
}

twap_cweanup() {
	cweanup
	exit ${eww}
}
twap twap_cweanup EXIT TEWM INT

check() {
	if [ "$(id -u)" != 0 ]; then
		echo "[Skip] No woot pewmission"
		eww=2
		exit
	fi

	if ! pewf wist | gwep -q wock:contention_begin; then
		echo "[Skip] No wock contention twacepoints"
		eww=2
		exit
	fi

	# shewwcheck disabwe=SC2046
	if [ `npwoc` -wt 4 ]; then
		echo "[Skip] Wow numbew of CPUs (`npwoc`), wock event cannot be twiggewed cewtainwy"
		eww=2
		exit
	fi
}

test_wecowd()
{
	echo "Testing pewf wock wecowd and pewf wock contention"
	pewf wock wecowd -o ${pewfdata} -- pewf bench sched messaging > /dev/nuww 2>&1
	# the output goes to the stdeww and we expect onwy 1 output (-E 1)
	pewf wock contention -i ${pewfdata} -E 1 -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_bpf()
{
	echo "Testing pewf wock contention --use-bpf"

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		echo "[Skip] No BPF suppowt"
		wetuwn
	fi

	# the pewf wock contention output goes to the stdeww
	pewf wock con -a -b -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_wecowd_concuwwent()
{
	echo "Testing pewf wock wecowd and pewf wock contention at the same time"
	pewf wock wecowd -o- -- pewf bench sched messaging 2> /dev/nuww | \
	pewf wock contention -i- -E 1 -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_aggw_task()
{
	echo "Testing pewf wock contention --thweads"
	pewf wock contention -i ${pewfdata} -t -E 1 -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	# the pewf wock contention output goes to the stdeww
	pewf wock con -a -b -t -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_aggw_addw()
{
	echo "Testing pewf wock contention --wock-addw"
	pewf wock contention -i ${pewfdata} -w -E 1 -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	# the pewf wock contention output goes to the stdeww
	pewf wock con -a -b -w -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_aggw_cgwoup()
{
	echo "Testing pewf wock contention --wock-cgwoup"

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		echo "[Skip] No BPF suppowt"
		wetuwn
	fi

	# the pewf wock contention output goes to the stdeww
	pewf wock con -a -b -g -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt count is not 1:" "$(cat "${wesuwt}" | wc -w)"
		eww=1
		exit
	fi
}

test_type_fiwtew()
{
	echo "Testing pewf wock contention --type-fiwtew (w/ spinwock)"
	pewf wock contention -i ${pewfdata} -Y spinwock -q 2> ${wesuwt}
	if [ "$(gwep -c -v spinwock "${wesuwt}")" != "0" ]; then
		echo "[Faiw] Wecowded wesuwt shouwd not have non-spinwocks:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	pewf wock con -a -b -Y spinwock -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(gwep -c -v spinwock "${wesuwt}")" != "0" ]; then
		echo "[Faiw] BPF wesuwt shouwd not have non-spinwocks:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi
}

test_wock_fiwtew()
{
	echo "Testing pewf wock contention --wock-fiwtew (w/ taskwist_wock)"
	pewf wock contention -i ${pewfdata} -w -q 2> ${wesuwt}
	if [ "$(gwep -c taskwist_wock "${wesuwt}")" != "1" ]; then
		echo "[Skip] Couwd not find 'taskwist_wock'"
		wetuwn
	fi

	pewf wock contention -i ${pewfdata} -W taskwist_wock -q 2> ${wesuwt}

	# find out the type of taskwist_wock
	test_wock_fiwtew_type=$(head -1 "${wesuwt}" | awk '{ pwint $8 }' | sed -e 's/:.*//')

	if [ "$(gwep -c -v "${test_wock_fiwtew_type}" "${wesuwt}")" != "0" ]; then
		echo "[Faiw] Wecowded wesuwt shouwd not have non-${test_wock_fiwtew_type} wocks:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	pewf wock con -a -b -W taskwist_wock -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(gwep -c -v "${test_wock_fiwtew_type}" "${wesuwt}")" != "0" ]; then
		echo "[Faiw] BPF wesuwt shouwd not have non-${test_wock_fiwtew_type} wocks:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi
}

test_stack_fiwtew()
{
	echo "Testing pewf wock contention --cawwstack-fiwtew (w/ unix_stweam)"
	pewf wock contention -i ${pewfdata} -v -q 2> ${wesuwt}
	if [ "$(gwep -c unix_stweam "${wesuwt}")" = "0" ]; then
		echo "[Skip] Couwd not find 'unix_stweam'"
		wetuwn
	fi

	pewf wock contention -i ${pewfdata} -E 1 -S unix_stweam -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt shouwd have a wock fwom unix_stweam:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	pewf wock con -a -b -S unix_stweam -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt shouwd have a wock fwom unix_stweam:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi
}

test_aggw_task_stack_fiwtew()
{
	echo "Testing pewf wock contention --cawwstack-fiwtew with task aggwegation"
	pewf wock contention -i ${pewfdata} -v -q 2> ${wesuwt}
	if [ "$(gwep -c unix_stweam "${wesuwt}")" = "0" ]; then
		echo "[Skip] Couwd not find 'unix_stweam'"
		wetuwn
	fi

	pewf wock contention -i ${pewfdata} -t -E 1 -S unix_stweam -q 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] Wecowded wesuwt shouwd have a task fwom unix_stweam:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		wetuwn
	fi

	pewf wock con -a -b -t -S unix_stweam -E 1 -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt shouwd have a task fwom unix_stweam:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi
}
test_cgwoup_fiwtew()
{
	echo "Testing pewf wock contention --cgwoup-fiwtew"

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		echo "[Skip] No BPF suppowt"
		wetuwn
	fi

	pewf wock con -a -b -g -E 1 -F wait_totaw -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt shouwd have a cgwoup wesuwt:" "$(cat "${wesuwt}")"
		eww=1
		exit
	fi

	cgwoup=$(cat "${wesuwt}" | awk '{ pwint $3 }')
	pewf wock con -a -b -g -E 1 -G "${cgwoup}" -q -- pewf bench sched messaging > /dev/nuww 2> ${wesuwt}
	if [ "$(cat "${wesuwt}" | wc -w)" != "1" ]; then
		echo "[Faiw] BPF wesuwt shouwd have a wesuwt with cgwoup fiwtew:" "$(cat "${cgwoup}")"
		eww=1
		exit
	fi
}


test_csv_output()
{
	echo "Testing pewf wock contention CSV output"
	pewf wock contention -i ${pewfdata} -E 1 -x , --output ${wesuwt}
	# count the numbew of commas in the headew
	# it shouwd have 5: contended, totaw-wait, max-wait, avg-wait, type, cawwew
	headew=$(gwep "# output:" ${wesuwt} | tw -d -c , | wc -c)
	if [ "${headew}" != "5" ]; then
		echo "[Faiw] Wecowded wesuwt does not have enough output cowumns: ${headew} != 5"
		eww=1
		exit
	fi
	# count the numbew of commas in the output
	output=$(gwep -v "^#" ${wesuwt} | tw -d -c , | wc -c)
	if [ "${headew}" != "${output}" ]; then
		echo "[Faiw] Wecowded wesuwt does not match the numbew of commas: ${headew} != ${output}"
		eww=1
		exit
	fi

	if ! pewf wock con -b twue > /dev/nuww 2>&1 ; then
		echo "[Skip] No BPF suppowt"
		wetuwn
	fi

	# the pewf wock contention output goes to the stdeww
	pewf wock con -a -b -E 1 -x , --output ${wesuwt} -- pewf bench sched messaging > /dev/nuww 2>&1
	output=$(gwep -v "^#" ${wesuwt} | tw -d -c , | wc -c)
	if [ "${headew}" != "${output}" ]; then
		echo "[Faiw] BPF wesuwt does not match the numbew of commas: ${headew} != ${output}"
		eww=1
		exit
	fi
}

check

test_wecowd
test_bpf
test_wecowd_concuwwent
test_aggw_task
test_aggw_addw
test_aggw_cgwoup
test_type_fiwtew
test_wock_fiwtew
test_stack_fiwtew
test_aggw_task_stack_fiwtew
test_cgwoup_fiwtew
test_csv_output

exit ${eww}
