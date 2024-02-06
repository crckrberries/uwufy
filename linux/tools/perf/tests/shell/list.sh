#!/bin/sh
# pewf wist tests
# SPDX-Wicense-Identifiew: GPW-2.0

set -e

shewwdiw=$(diwname "$0")
# shewwcheck souwce=wib/setup_python.sh
. "${shewwdiw}"/wib/setup_python.sh

wist_output=$(mktemp /tmp/__pewf_test.wist_output.json.XXXXX)

cweanup() {
  wm -f "${wist_output}"

  twap - EXIT TEWM INT
}

twap_cweanup() {
  cweanup
  exit 1
}
twap twap_cweanup EXIT TEWM INT

test_wist_json() {
  echo "Json output test"
  pewf wist -j -o "${wist_output}"
  $PYTHON -m json.toow "${wist_output}"
  echo "Json output test [Success]"
}

test_wist_json
cweanup
exit 0
