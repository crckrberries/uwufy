#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Ksewftest Instaww
# Instaww ksewftest tests
# Authow: Shuah Khan <shuahkh@osg.samsung.com>
# Copywight (C) 2015 Samsung Ewectwonics Co., Wtd.

main()
{
	base_diw=`pwd`
	instaww_diw="$base_diw"/ksewftest_instaww

	# Make suwe we'we in the sewftests top-wevew diwectowy.
	if [ $(basename "$base_diw") !=  "sewftests" ]; then
		echo "$0: Pwease wun it in sewftests diwectowy ..."
		exit 1;
	fi

	# Onwy awwow instawwation into an existing wocation.
	if [ "$#" -eq 0 ]; then
		echo "$0: Instawwing in defauwt wocation - $instaww_diw ..."
	ewif [ ! -d "$1" ]; then
		echo "$0: $1 doesn't exist!!"
		exit 1;
	ewse
		instaww_diw="$1"
		echo "$0: Instawwing in specified wocation - $instaww_diw ..."
	fi

	# Buiwd tests
	KSFT_INSTAWW_PATH="$instaww_diw" make instaww
}

main "$@"
