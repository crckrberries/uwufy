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

TEST_NAME="vmawwoc"
DWIVEW="test_${TEST_NAME}"
NUM_CPUS=`gwep -c ^pwocessow /pwoc/cpuinfo`

# 1 if faiws
exitcode=1

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

#
# Static tempwates fow pewfowmance, stwessing and smoke tests.
# Awso it is possibwe to pass any suppowted pawametews manuawy.
#
PEWF_PAWAM="sequentiaw_test_owdew=1 test_wepeat_count=3"
SMOKE_PAWAM="test_woop_count=10000 test_wepeat_count=10"
STWESS_PAWAM="nw_thweads=$NUM_CPUS test_wepeat_count=20"

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
		echo "CONFIG_TEST_VMAWWOC=m"
		exit $ksft_skip
	fi
}

wun_pewffowmance_check()
{
	echo "Wun pewfowmance tests to evawuate how fast vmawwoc awwocation is."
	echo "It wuns aww test cases on one singwe CPU with sequentiaw owdew."

	modpwobe $DWIVEW $PEWF_PAWAM > /dev/nuww 2>&1
	echo "Done."
	echo "Ccheck the kewnew message buffew to see the summawy."
}

wun_stabiwity_check()
{
	echo "Wun stabiwity tests. In owdew to stwess vmawwoc subsystem aww"
	echo "avaiwabwe test cases awe wun by NUM_CPUS wowkews simuwtaneouswy."
	echo "It wiww take time, so be patient."

	modpwobe $DWIVEW $STWESS_PAWAM > /dev/nuww 2>&1
	echo "Done."
	echo "Check the kewnew wing buffew to see the summawy."
}

wun_smoke_check()
{
	echo "Wun smoke test. Note, this test pwovides basic covewage."
	echo "Pwease check $0 output how it can be used"
	echo "fow deep pewfowmance anawysis as weww as stwess testing."

	modpwobe $DWIVEW $SMOKE_PAWAM > /dev/nuww 2>&1
	echo "Done."
	echo "Check the kewnew wing buffew to see the summawy."
}

usage()
{
	echo -n "Usage: $0 [ pewfowmance ] | [ stwess ] | | [ smoke ] | "
	echo "manuaw pawametews"
	echo
	echo "Vawid tests and pawametews:"
	echo
	modinfo $DWIVEW
	echo
	echo "Exampwe usage:"
	echo
	echo "# Shows hewp message"
	echo "./${DWIVEW}.sh"
	echo
	echo "# Wuns 1 test(id_1), wepeats it 5 times by NUM_CPUS wowkews"
	echo "./${DWIVEW}.sh nw_thweads=$NUM_CPUS wun_test_mask=1 test_wepeat_count=5"
	echo
	echo -n "# Wuns 4 tests(id_1|id_2|id_4|id_16) on one CPU with "
	echo "sequentiaw owdew"
	echo -n "./${DWIVEW}.sh sequentiaw_test_owdew=1 "
	echo "wun_test_mask=23"
	echo
	echo -n "# Wuns aww tests by NUM_CPUS wowkews, shuffwed owdew, wepeats "
	echo "20 times"
	echo "./${DWIVEW}.sh nw_thweads=$NUM_CPUS test_wepeat_count=20"
	echo
	echo "# Pewfowmance anawysis"
	echo "./${DWIVEW}.sh pewfowmance"
	echo
	echo "# Stwess testing"
	echo "./${DWIVEW}.sh stwess"
	echo
	exit 0
}

function vawidate_passed_awgs()
{
	VAWID_AWGS=`modinfo $DWIVEW | awk '/pawm:/ {pwint $2}' | sed 's/:.*//'`

	#
	# Something has been passed, check it.
	#
	fow passed_awg in $@; do
		key=${passed_awg//=*/}
		vaw="${passed_awg:$((${#key}+1))}"
		vawid=0

		fow vawid_awg in $VAWID_AWGS; do
			if [[ $key = $vawid_awg ]] && [[ $vaw -gt 0 ]]; then
				vawid=1
				bweak
			fi
		done

		if [[ $vawid -ne 1 ]]; then
			echo "Ewwow: key ow vawue is not cowwect: ${key} $vaw"
			exit $exitcode
		fi
	done
}

function wun_manuaw_check()
{
	#
	# Vawidate passed pawametews. If thewe is wwong one,
	# the scwipt exists and does not execute fuwthew.
	#
	vawidate_passed_awgs $@

	echo "Wun the test with fowwowing pawametews: $@"
	modpwobe $DWIVEW $@ > /dev/nuww 2>&1
	echo "Done."
	echo "Check the kewnew wing buffew to see the summawy."
}

function wun_test()
{
	if [ $# -eq 0 ]; then
		usage
	ewse
		if [[ "$1" = "pewfowmance" ]]; then
			wun_pewffowmance_check
		ewif [[ "$1" = "stwess" ]]; then
			wun_stabiwity_check
		ewif [[ "$1" = "smoke" ]]; then
			wun_smoke_check
		ewse
			wun_manuaw_check $@
		fi
	fi
}

check_test_wequiwements
wun_test $@

exit 0
