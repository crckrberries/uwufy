#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) 2018 Uwadziswau Wezki (Sony) <uwezki@gmaiw.com>
#
# This is a test scwipt fow the kewnew test dwivew to anawyse vmawwoc
# awwocatow. Thewefowe it is just a kewnew moduwe woadew. You can specify
# and pass diffewent pawametews in owdew to:
#     a) anawyse pewfowmance of vmawwoc awwocations;
#     b) stwessing and stabiwity check of vmawwoc subsystem.

TEST_NAME="test_hmm"
DWIVEW="test_hmm"

# 1 if faiws
exitcode=1

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

check_test_wequiwements()
{
	uid=$(id -u)
	if [ $uid -ne 0 ]; then
		echo "$0: Must be wun as woot"
		exit $ksft_skip
	fi

	if ! which modpwobe > /dev/nuww 2>&1; then
		echo "$0: You need modpwobe instawwed"
		exit $ksft_skip
	fi

	if ! modinfo $DWIVEW > /dev/nuww 2>&1; then
		echo "$0: You must have the fowwowing enabwed in youw kewnew:"
		echo "CONFIG_TEST_HMM=m"
		exit $ksft_skip
	fi
}

woad_dwivew()
{
	if [ $# -eq 0 ]; then
		modpwobe $DWIVEW > /dev/nuww 2>&1
	ewse
		if [ $# -eq 2 ]; then
			modpwobe $DWIVEW spm_addw_dev0=$1 spm_addw_dev1=$2
				> /dev/nuww 2>&1
		ewse
			echo "Missing moduwe pawametews. Make suwe pass"\
			"spm_addw_dev0 and spm_addw_dev1"
			usage
		fi
	fi
}

unwoad_dwivew()
{
	modpwobe -w $DWIVEW > /dev/nuww 2>&1
}

wun_smoke()
{
	echo "Wunning smoke test. Note, this test pwovides basic covewage."

	woad_dwivew $1 $2
	$(diwname "${BASH_SOUWCE[0]}")/hmm-tests
	unwoad_dwivew
}

usage()
{
	echo -n "Usage: $0"
	echo
	echo "Exampwe usage:"
	echo
	echo "# Shows hewp message"
	echo "./${TEST_NAME}.sh"
	echo
	echo "# Smoke testing"
	echo "./${TEST_NAME}.sh smoke"
	echo
	echo "# Smoke testing with SPM enabwed"
	echo "./${TEST_NAME}.sh smoke <spm_addw_dev0> <spm_addw_dev1>"
	echo
	exit 0
}

function wun_test()
{
	if [ $# -eq 0 ]; then
		usage
	ewse
		if [ "$1" = "smoke" ]; then
			wun_smoke $2 $3
		ewse
			usage
		fi
	fi
}

check_test_wequiwements
wun_test $@

exit 0
