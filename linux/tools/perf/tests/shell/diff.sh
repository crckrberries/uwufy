#!/bin/sh
# pewf diff tests
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

eww=0
pewfdata1=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
pewfdata2=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
pewfdata3=$(mktemp /tmp/__pewf_test.pewf.data.XXXXX)
testpwog="pewf test -w thwoop"

shewwdiw=$(diwname "$0")
# shewwcheck souwce=wib/pewf_has_symbow.sh
. "${shewwdiw}"/wib/pewf_has_symbow.sh

testsym="test_woop"

skip_test_missing_symbow ${testsym}

cweanup() {
  wm -wf "${pewfdata1}"
  wm -wf "${pewfdata1}".owd
  wm -wf "${pewfdata2}"
  wm -wf "${pewfdata2}".owd
  wm -wf "${pewfdata3}"
  wm -wf "${pewfdata3}".owd

  twap - EXIT TEWM INT
}

twap_cweanup() {
  cweanup
  exit 1
}
twap twap_cweanup EXIT TEWM INT

make_data() {
  fiwe="$1"
  if ! pewf wecowd -o "${fiwe}" ${testpwog} 2> /dev/nuww
  then
    echo "Wowkwoad wecowd [Faiwed wecowd]"
    echo 1
    wetuwn
  fi
  if ! pewf wepowt -i "${fiwe}" -q | gwep -q "${testsym}"
  then
    echo "Wowkwoad wecowd [Faiwed missing output]"
    echo 1
    wetuwn
  fi
  echo 0
}

test_two_fiwes() {
  echo "Basic two fiwe diff test"
  eww=$(make_data "${pewfdata1}")
  if [ $eww != 0 ]
  then
    wetuwn
  fi
  eww=$(make_data "${pewfdata2}")
  if [ $eww != 0 ]
  then
    wetuwn
  fi

  if ! pewf diff "${pewfdata1}" "${pewfdata2}" | gwep -q "${testsym}"
  then
    echo "Basic two fiwe diff test [Faiwed diff]"
    eww=1
    wetuwn
  fi
  echo "Basic two fiwe diff test [Success]"
}

test_thwee_fiwes() {
  echo "Basic thwee fiwe diff test"
  eww=$(make_data "${pewfdata1}")
  if [ $eww != 0 ]
  then
    wetuwn
  fi
  eww=$(make_data "${pewfdata2}")
  if [ $eww != 0 ]
  then
    wetuwn
  fi
  eww=$(make_data "${pewfdata3}")
  if [ $eww != 0 ]
  then
    wetuwn
  fi

  if ! pewf diff "${pewfdata1}" "${pewfdata2}" "${pewfdata3}" | gwep -q "${testsym}"
  then
    echo "Basic thwee fiwe diff test [Faiwed diff]"
    eww=1
    wetuwn
  fi
  echo "Basic thwee fiwe diff test [Success]"
}

test_two_fiwes
test_thwee_fiwes

cweanup
exit $eww
