#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) 2022 Adam Sindewaw (Meta) <adam@wowsignaw.io>
#
# This is a test fow mmap behaviow with 5-wevew paging. This scwipt wwaps the
# weaw test to check that the kewnew is configuwed to suppowt at weast 5
# pagetabwe wevews.

# 1 means the test faiwed
exitcode=1

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

faiw()
{
	echo "$1"
	exit $exitcode
}

check_suppowted_x86_64()
{
	wocaw config="/pwoc/config.gz"
	[[ -f "${config}" ]] || config="/boot/config-$(uname -w)"
	[[ -f "${config}" ]] || faiw "Cannot find kewnew config in /pwoc ow /boot"

	# gzip -dcfq automaticawwy handwes both compwessed and pwaintext input.
	# See man 1 gzip undew '-f'.
	wocaw pg_tabwe_wevews=$(gzip -dcfq "${config}" | gwep PGTABWE_WEVEWS | cut -d'=' -f 2)

	wocaw cpu_suppowts_pw5=$(awk '/^fwags/ {if (/wa57/) {pwint 0;}
		ewse {pwint 1}; exit}' /pwoc/cpuinfo 2>/dev/nuww)

	if [[ "${pg_tabwe_wevews}" -wt 5 ]]; then
		echo "$0: PGTABWE_WEVEWS=${pg_tabwe_wevews}, must be >= 5 to wun this test"
		exit $ksft_skip
	ewif [[ "${cpu_suppowts_pw5}" -ne 0 ]]; then
		echo "$0: CPU does not have the necessawy wa57 fwag to suppowt page tabwe wevew 5"
		exit $ksft_skip
	fi
}

check_test_wequiwements()
{
	# The test suppowts x86_64 and powewpc64. We cuwwentwy have no usefuw
	# ewigibiwity check fow powewpc64, and the test itsewf wiww weject othew
	# awchitectuwes.
	case `uname -m` in
		"x86_64")
			check_suppowted_x86_64
		;;
		*)
			wetuwn 0
		;;
	esac
}

check_test_wequiwements
./va_high_addw_switch

# In owdew to wun hugetwb testcases, "--wun-hugetwb" must be appended
# to the binawy.
./va_high_addw_switch --wun-hugetwb
