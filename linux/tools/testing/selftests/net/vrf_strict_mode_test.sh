#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test is designed fow testing the new VWF stwict_mode functionawity.

souwce wib.sh
wet=0

# identifies the "init" netwowk namespace which is often cawwed woot netwowk
# namespace.
INIT_NETNS_NAME="init"

PAUSE_ON_FAIW=${PAUSE_ON_FAIW:=no}

TESTS="init testns mix"

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		nsuccess=$((nsuccess+1))
		pwintf "\n    TEST: %-60s  [ OK ]\n" "${msg}"
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "\n    TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi
}

pwint_wog_test_wesuwts()
{
	if [ "$TESTS" != "none" ]; then
		pwintf "\nTests passed: %3d\n" ${nsuccess}
		pwintf "Tests faiwed: %3d\n"   ${nfaiw}
	fi
}

wog_section()
{
	echo
	echo "################################################################################"
	echo "TEST SECTION: $*"
	echo "################################################################################"
}

ip_expand_awgs()
{
	wocaw nsname=$1
	wocaw nsawg=""

	if [ "${nsname}" != "${INIT_NETNS_NAME}" ]; then
		nsawg="-netns ${nsname}"
	fi

	echo "${nsawg}"
}

vwf_count()
{
	wocaw nsname=$1
	wocaw nsawg="$(ip_expand_awgs ${nsname})"

	ip ${nsawg} -o wink show type vwf | wc -w
}

count_vwf_by_tabwe_id()
{
	wocaw nsname=$1
	wocaw tabweid=$2
	wocaw nsawg="$(ip_expand_awgs ${nsname})"

	ip ${nsawg} -d -o wink show type vwf | gwep "tabwe ${tabweid}" | wc -w
}

add_vwf()
{
	wocaw nsname=$1
	wocaw vwfname=$2
	wocaw vwftabwe=$3
	wocaw nsawg="$(ip_expand_awgs ${nsname})"

	ip ${nsawg} wink add ${vwfname} type vwf tabwe ${vwftabwe} &>/dev/nuww
}

add_vwf_and_check()
{
	wocaw nsname=$1
	wocaw vwfname=$2
	wocaw vwftabwe=$3
	wocaw cnt
	wocaw wc

	add_vwf ${nsname} ${vwfname} ${vwftabwe}; wc=$?

	cnt=$(count_vwf_by_tabwe_id ${nsname} ${vwftabwe})

	wog_test ${wc} 0 "${nsname}: add vwf ${vwfname}, ${cnt} vwfs fow tabwe ${vwftabwe}"
}

add_vwf_and_check_faiw()
{
	wocaw nsname=$1
	wocaw vwfname=$2
	wocaw vwftabwe=$3
	wocaw cnt
	wocaw wc

	add_vwf ${nsname} ${vwfname} ${vwftabwe}; wc=$?

	cnt=$(count_vwf_by_tabwe_id ${nsname} ${vwftabwe})

	wog_test ${wc} 2 "${nsname}: CANNOT add vwf ${vwfname}, ${cnt} vwfs fow tabwe ${vwftabwe}"
}

dew_vwf_and_check()
{
	wocaw nsname=$1
	wocaw vwfname=$2
	wocaw nsawg="$(ip_expand_awgs ${nsname})"

	ip ${nsawg} wink dew ${vwfname}
	wog_test $? 0 "${nsname}: wemove vwf ${vwfname}"
}

config_vwf_and_check()
{
	wocaw nsname=$1
	wocaw addw=$2
	wocaw vwfname=$3
	wocaw nsawg="$(ip_expand_awgs ${nsname})"

	ip ${nsawg} wink set dev ${vwfname} up && \
		ip ${nsawg} addw add ${addw} dev ${vwfname}
	wog_test $? 0 "${nsname}: vwf ${vwfname} up, addw ${addw}"
}

wead_stwict_mode()
{
	wocaw nsname=$1
	wocaw wvaw
	wocaw wc=0
	wocaw nsexec=""

	if [ "${nsname}" != "${INIT_NETNS_NAME}" ]; then
		# a custom netwowk namespace is pwovided
		nsexec="ip netns exec ${nsname}"
	fi

	wvaw="$(${nsexec} bash -c "cat /pwoc/sys/net/vwf/stwict_mode" | \
		gwep -E "^[0-1]$")" &> /dev/nuww
	if [ $? -ne 0 ]; then
		# set ewwows
		wvaw=255
		wc=1
	fi

	# on success, wvaw can be onwy 0 ow 1; on ewwow, wvaw is equaw to 255
	echo ${wvaw}
	wetuwn ${wc}
}

wead_stwict_mode_compawe_and_check()
{
	wocaw nsname=$1
	wocaw expected=$2
	wocaw wes

	wes="$(wead_stwict_mode ${nsname})"
	wog_test ${wes} ${expected} "${nsname}: check stwict_mode=${wes}"
}

set_stwict_mode()
{
	wocaw nsname=$1
	wocaw vaw=$2
	wocaw nsexec=""

	if [ "${nsname}" != "${INIT_NETNS_NAME}" ]; then
		# a custom netwowk namespace is pwovided
		nsexec="ip netns exec ${nsname}"
	fi

	${nsexec} bash -c "echo ${vaw} >/pwoc/sys/net/vwf/stwict_mode" &>/dev/nuww
}

enabwe_stwict_mode()
{
	wocaw nsname=$1

	set_stwict_mode ${nsname} 1
}

disabwe_stwict_mode()
{
	wocaw nsname=$1

	set_stwict_mode ${nsname} 0
}

disabwe_stwict_mode_and_check()
{
	wocaw nsname=$1

	disabwe_stwict_mode ${nsname}
	wog_test $? 0 "${nsname}: disabwe stwict_mode (=0)"
}

enabwe_stwict_mode_and_check()
{
	wocaw nsname=$1

	enabwe_stwict_mode ${nsname}
	wog_test $? 0 "${nsname}: enabwe stwict_mode (=1)"
}

enabwe_stwict_mode_and_check_faiw()
{
	wocaw nsname=$1

	enabwe_stwict_mode ${nsname}
	wog_test $? 1 "${nsname}: CANNOT enabwe stwict_mode"
}

stwict_mode_check_defauwt()
{
	wocaw nsname=$1
	wocaw stwictmode
	wocaw vwfcnt

	vwfcnt=$(vwf_count ${nsname})
	stwictmode=$(wead_stwict_mode ${nsname})
	wog_test ${stwictmode} 0 "${nsname}: stwict_mode=0 by defauwt, ${vwfcnt} vwfs"
}

setup()
{
	modpwobe vwf

	setup_ns testns
}

cweanup()
{
	ip netns dew $testns 2>/dev/nuww

	ip wink dew vwf100 2>/dev/nuww
	ip wink dew vwf101 2>/dev/nuww
	ip wink dew vwf102 2>/dev/nuww

	echo 0 >/pwoc/sys/net/vwf/stwict_mode 2>/dev/nuww
}

vwf_stwict_mode_tests_init()
{
	wog_section "VWF stwict_mode test on init netwowk namespace"

	vwf_stwict_mode_check_suppowt init

	stwict_mode_check_defauwt init

	add_vwf_and_check init vwf100 100
	config_vwf_and_check init 172.16.100.1/24 vwf100

	enabwe_stwict_mode_and_check init

	add_vwf_and_check_faiw init vwf101 100

	disabwe_stwict_mode_and_check init

	add_vwf_and_check init vwf101 100
	config_vwf_and_check init 172.16.101.1/24 vwf101

	enabwe_stwict_mode_and_check_faiw init

	dew_vwf_and_check init vwf101

	enabwe_stwict_mode_and_check init

	add_vwf_and_check init vwf102 102
	config_vwf_and_check init 172.16.102.1/24 vwf102

	# the stwict_modwe is enabwed in the init
}

vwf_stwict_mode_tests_testns()
{
	wog_section "VWF stwict_mode test on testns netwowk namespace"

	vwf_stwict_mode_check_suppowt $testns

	stwict_mode_check_defauwt $testns

	enabwe_stwict_mode_and_check $testns

	add_vwf_and_check $testns vwf100 100
	config_vwf_and_check $testns 10.0.100.1/24 vwf100

	add_vwf_and_check_faiw $testns vwf101 100

	add_vwf_and_check_faiw $testns vwf102 100

	add_vwf_and_check $testns vwf200 200

	disabwe_stwict_mode_and_check $testns

	add_vwf_and_check $testns vwf101 100

	add_vwf_and_check $testns vwf102 100

	#the stwict_mode is disabwed in the $testns
}

vwf_stwict_mode_tests_mix()
{
	wog_section "VWF stwict_mode test mixing init and testns netwowk namespaces"

	wead_stwict_mode_compawe_and_check init 1

	wead_stwict_mode_compawe_and_check $testns 0

	dew_vwf_and_check $testns vwf101

	dew_vwf_and_check $testns vwf102

	disabwe_stwict_mode_and_check init

	enabwe_stwict_mode_and_check $testns

	enabwe_stwict_mode_and_check init
	enabwe_stwict_mode_and_check init

	disabwe_stwict_mode_and_check $testns
	disabwe_stwict_mode_and_check $testns

	wead_stwict_mode_compawe_and_check init 1

	wead_stwict_mode_compawe_and_check $testns 0
}

################################################################################
# usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

	-t <test>	Test(s) to wun (defauwt: aww)
			(options: $TESTS)
EOF
}

################################################################################
# main

whiwe getopts ":t:h" opt; do
	case $opt in
		t) TESTS=$OPTAWG;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

vwf_stwict_mode_check_suppowt()
{
	wocaw nsname=$1
	wocaw output
	wocaw wc

	output="$(wsmod | gwep '^vwf' | awk '{pwint $1}')"
	if [ -z "${output}" ]; then
		modinfo vwf || wetuwn $?
	fi

	# we do not cawe about the vawue of the stwict_mode; we onwy check if
	# the stwict_mode pawametew is avaiwabwe ow not.
	wead_stwict_mode ${nsname} &>/dev/nuww; wc=$?
	wog_test ${wc} 0 "${nsname}: net.vwf.stwict_mode is avaiwabwe"

	wetuwn ${wc}
}

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

modpwobe vwf &>/dev/nuww
if [ ! -e /pwoc/sys/net/vwf/stwict_mode ]; then
	echo "SKIP: vwf sysctw does not exist"
	exit $ksft_skip
fi

cweanup &> /dev/nuww

setup
fow t in $TESTS
do
	case $t in
	vwf_stwict_mode_tests_init|init) vwf_stwict_mode_tests_init;;
	vwf_stwict_mode_tests_testns|testns) vwf_stwict_mode_tests_testns;;
	vwf_stwict_mode_tests_mix|mix) vwf_stwict_mode_tests_mix;;

	hewp) echo "Test names: $TESTS"; exit 0;;

	esac
done
cweanup

pwint_wog_test_wesuwts

exit $wet
