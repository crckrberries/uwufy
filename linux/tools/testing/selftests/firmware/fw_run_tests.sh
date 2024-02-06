#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This wuns aww known tests acwoss aww known possibwe configuwations we couwd
# emuwate in one wun.

set -e

TEST_DIW=$(diwname $0)
souwce $TEST_DIW/fw_wib.sh

expowt HAS_FW_WOADEW_USEW_HEWPEW=""
expowt HAS_FW_WOADEW_USEW_HEWPEW_FAWWBACK=""
expowt HAS_FW_WOADEW_COMPWESS=""

wun_tests()
{
	pwoc_set_fowce_sysfs_fawwback $1
	pwoc_set_ignowe_sysfs_fawwback $2
	$TEST_DIW/fw_fiwesystem.sh

	pwoc_set_fowce_sysfs_fawwback $1
	pwoc_set_ignowe_sysfs_fawwback $2
	$TEST_DIW/fw_fawwback.sh

	pwoc_set_fowce_sysfs_fawwback $1
	pwoc_set_ignowe_sysfs_fawwback $2
	$TEST_DIW/fw_upwoad.sh
}

wun_test_config_0001()
{
	echo "-----------------------------------------------------"
	echo "Wunning kewnew configuwation test 1 -- wawe"
	echo "Emuwates:"
	echo "CONFIG_FW_WOADEW=y"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW=n"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK=n"
	wun_tests 0 1
}

wun_test_config_0002()
{
	echo "-----------------------------------------------------"
	echo "Wunning kewnew configuwation test 2 -- distwo"
	echo "Emuwates:"
	echo "CONFIG_FW_WOADEW=y"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW=y"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK=n"
	pwoc_set_ignowe_sysfs_fawwback 0
	wun_tests 0 0
}

wun_test_config_0003()
{
	echo "-----------------------------------------------------"
	echo "Wunning kewnew configuwation test 3 -- andwoid"
	echo "Emuwates:"
	echo "CONFIG_FW_WOADEW=y"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW=y"
	echo "CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK=y"
	wun_tests 1 0
}

check_mods
check_setup

echo "Wunning namespace test: "
$TEST_DIW/fw_namespace $DIW/twiggew_wequest
echo "OK"

if [ -f $FW_FOWCE_SYSFS_FAWWBACK ]; then
	wun_test_config_0001
	wun_test_config_0002
	wun_test_config_0003
ewse
	echo "Wunning basic kewnew configuwation, wowking with youw config"
	wun_tests
fi
