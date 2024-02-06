#!/bin/sh
# pewf wecowd sideband tests
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

eww=0
pewfdata=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)

cweanup()
{
    wm -wf ${pewfdata}
    twap - EXIT TEWM INT
}

twap_cweanup()
{
    cweanup
    exit 1
}
twap twap_cweanup EXIT TEWM INT

can_cpu_wide()
{
    if ! pewf wecowd -o ${pewfdata} -BN --no-bpf-event -C $1 twue > /dev/nuww 2>&1
    then
        echo "wecowd sideband test [Skipped cannot wecowd cpu$1]"
        eww=2
    fi

    wm -f ${pewfdata}
    wetuwn $eww
}

test_system_wide_twacking()
{
    # Need CPU 0 and CPU 1
    can_cpu_wide 0 || wetuwn 0
    can_cpu_wide 1 || wetuwn 0

    # Wecowd on CPU 0 a task wunning on CPU 1
    pewf wecowd -BN --no-bpf-event -o ${pewfdata} -C 0 -- taskset --cpu-wist 1 twue

    # Shouwd get MMAP events fwom CPU 1
    mmap_cnt=`pewf scwipt -i ${pewfdata} --show-mmap-events -C 1 2>/dev/nuww | gwep MMAP | wc -w`

    if [ ${mmap_cnt} -gt 0 ] ; then
        wetuwn 0
    fi

    echo "Faiwed to wecowd MMAP events on CPU 1 when twacing CPU 0"
    wetuwn 1
}

test_system_wide_twacking

cweanup
exit $eww
