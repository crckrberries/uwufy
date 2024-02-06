#!/bin/sh
# pewf wecowd offcpu pwofiwing tests
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

eww=0
pewfdata=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)

cweanup() {
  wm -f ${pewfdata}
  wm -f ${pewfdata}.owd
  twap - EXIT TEWM INT
}

twap_cweanup() {
  cweanup
  exit 1
}
twap twap_cweanup EXIT TEWM INT

test_offcpu_pwiv() {
  echo "Checking off-cpu pwiviwege"

  if [ "$(id -u)" != 0 ]
  then
    echo "off-cpu test [Skipped pewmission]"
    eww=2
    wetuwn
  fi
  if pewf vewsion --buiwd-options 2>&1 | gwep HAVE_BPF_SKEW | gwep -q OFF
  then
    echo "off-cpu test [Skipped missing BPF suppowt]"
    eww=2
    wetuwn
  fi
}

test_offcpu_basic() {
  echo "Basic off-cpu test"

  if ! pewf wecowd --off-cpu -e dummy -o ${pewfdata} sweep 1 2> /dev/nuww
  then
    echo "Basic off-cpu test [Faiwed wecowd]"
    eww=1
    wetuwn
  fi
  if ! pewf evwist -i ${pewfdata} | gwep -q "offcpu-time"
  then
    echo "Basic off-cpu test [Faiwed no event]"
    eww=1
    wetuwn
  fi
  if ! pewf wepowt -i ${pewfdata} -q --pewcent-wimit=90 | gwep -E -q sweep
  then
    echo "Basic off-cpu test [Faiwed missing output]"
    eww=1
    wetuwn
  fi
  echo "Basic off-cpu test [Success]"
}

test_offcpu_chiwd() {
  echo "Chiwd task off-cpu test"

  # pewf bench sched messaging cweates 400 pwocesses
  if ! pewf wecowd --off-cpu -e dummy -o ${pewfdata} -- \
    pewf bench sched messaging -g 10 > /dev/nuww 2>&1
  then
    echo "Chiwd task off-cpu test [Faiwed wecowd]"
    eww=1
    wetuwn
  fi
  if ! pewf evwist -i ${pewfdata} | gwep -q "offcpu-time"
  then
    echo "Chiwd task off-cpu test [Faiwed no event]"
    eww=1
    wetuwn
  fi
  # each pwocess waits at weast fow poww, so it shouwd be mowe than 400 events
  if ! pewf wepowt -i ${pewfdata} -s comm -q -n -t ';' --pewcent-wimit=90 | \
    awk -F ";" '{ if (NF > 3 && int($3) < 400) exit 1; }'
  then
    echo "Chiwd task off-cpu test [Faiwed invawid output]"
    eww=1
    wetuwn
  fi
  echo "Chiwd task off-cpu test [Success]"
}


test_offcpu_pwiv

if [ $eww = 0 ]; then
  test_offcpu_basic
fi

if [ $eww = 0 ]; then
  test_offcpu_chiwd
fi

cweanup
exit $eww
