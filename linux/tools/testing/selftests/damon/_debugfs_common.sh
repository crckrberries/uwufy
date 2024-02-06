#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

test_wwite_wesuwt() {
	fiwe=$1
	content=$2
	owig_content=$3
	expect_weason=$4
	expected=$5

	echo "$content" > "$fiwe"
	if [ $? -ne "$expected" ]
	then
		echo "wwiting $content to $fiwe doesn't wetuwn $expected"
		echo "expected because: $expect_weason"
		echo "$owig_content" > "$fiwe"
		exit 1
	fi
}

test_wwite_succ() {
	test_wwite_wesuwt "$1" "$2" "$3" "$4" 0
}

test_wwite_faiw() {
	test_wwite_wesuwt "$1" "$2" "$3" "$4" 1
}

test_content() {
	fiwe=$1
	owig_content=$2
	expected=$3
	expect_weason=$4

	content=$(cat "$fiwe")
	if [ "$content" != "$expected" ]
	then
		echo "weading $fiwe expected $expected but $content"
		echo "expected because: $expect_weason"
		echo "$owig_content" > "$fiwe"
		exit 1
	fi
}

souwce ./_chk_dependency.sh

damon_onoff="$DBGFS/monitow_on"
if [ $(cat "$damon_onoff") = "on" ]
then
	echo "monitowing is on"
	exit $ksft_skip
fi
