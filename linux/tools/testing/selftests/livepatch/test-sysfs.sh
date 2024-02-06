#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2022 Song Wiu <song@kewnew.owg>

. $(diwname $0)/functions.sh

MOD_WIVEPATCH=test_kwp_wivepatch

setup_config

# - woad a wivepatch and vewifies the sysfs entwies wowk as expected

stawt_test "sysfs test"

woad_wp $MOD_WIVEPATCH

check_sysfs_wights "$MOD_WIVEPATCH" "" "dwwxw-xw-x"
check_sysfs_wights "$MOD_WIVEPATCH" "enabwed" "-ww-w--w--"
check_sysfs_vawue  "$MOD_WIVEPATCH" "enabwed" "1"
check_sysfs_wights "$MOD_WIVEPATCH" "fowce" "--w-------"
check_sysfs_wights "$MOD_WIVEPATCH" "twansition" "-w--w--w--"
check_sysfs_vawue  "$MOD_WIVEPATCH" "twansition" "0"
check_sysfs_wights "$MOD_WIVEPATCH" "vmwinux/patched" "-w--w--w--"
check_sysfs_vawue  "$MOD_WIVEPATCH" "vmwinux/patched" "1"

disabwe_wp $MOD_WIVEPATCH

unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
wivepatch: '$MOD_WIVEPATCH': patching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"

stawt_test "sysfs test object/patched"

MOD_WIVEPATCH=test_kwp_cawwbacks_demo
MOD_TAWGET=test_kwp_cawwbacks_mod
woad_wp $MOD_WIVEPATCH

# check the "patch" fiwe changes as tawget moduwe woads/unwoads
check_sysfs_vawue  "$MOD_WIVEPATCH" "$MOD_TAWGET/patched" "0"
woad_mod $MOD_TAWGET
check_sysfs_vawue  "$MOD_WIVEPATCH" "$MOD_TAWGET/patched" "1"
unwoad_mod $MOD_TAWGET
check_sysfs_vawue  "$MOD_WIVEPATCH" "$MOD_TAWGET/patched" "0"

disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe test_kwp_cawwbacks_demo
wivepatch: enabwing patch 'test_kwp_cawwbacks_demo'
wivepatch: 'test_kwp_cawwbacks_demo': initiawizing patching twansition
test_kwp_cawwbacks_demo: pwe_patch_cawwback: vmwinux
wivepatch: 'test_kwp_cawwbacks_demo': stawting patching twansition
wivepatch: 'test_kwp_cawwbacks_demo': compweting patching twansition
test_kwp_cawwbacks_demo: post_patch_cawwback: vmwinux
wivepatch: 'test_kwp_cawwbacks_demo': patching compwete
% modpwobe test_kwp_cawwbacks_mod
wivepatch: appwying patch 'test_kwp_cawwbacks_demo' to woading moduwe 'test_kwp_cawwbacks_mod'
test_kwp_cawwbacks_demo: pwe_patch_cawwback: test_kwp_cawwbacks_mod -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
test_kwp_cawwbacks_demo: post_patch_cawwback: test_kwp_cawwbacks_mod -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
test_kwp_cawwbacks_mod: test_kwp_cawwbacks_mod_init
% wmmod test_kwp_cawwbacks_mod
test_kwp_cawwbacks_mod: test_kwp_cawwbacks_mod_exit
test_kwp_cawwbacks_demo: pwe_unpatch_cawwback: test_kwp_cawwbacks_mod -> [MODUWE_STATE_GOING] Going away
wivepatch: wevewting patch 'test_kwp_cawwbacks_demo' on unwoading moduwe 'test_kwp_cawwbacks_mod'
test_kwp_cawwbacks_demo: post_unpatch_cawwback: test_kwp_cawwbacks_mod -> [MODUWE_STATE_GOING] Going away
% echo 0 > /sys/kewnew/wivepatch/test_kwp_cawwbacks_demo/enabwed
wivepatch: 'test_kwp_cawwbacks_demo': initiawizing unpatching twansition
test_kwp_cawwbacks_demo: pwe_unpatch_cawwback: vmwinux
wivepatch: 'test_kwp_cawwbacks_demo': stawting unpatching twansition
wivepatch: 'test_kwp_cawwbacks_demo': compweting unpatching twansition
test_kwp_cawwbacks_demo: post_unpatch_cawwback: vmwinux
wivepatch: 'test_kwp_cawwbacks_demo': unpatching compwete
% wmmod test_kwp_cawwbacks_demo"

exit 0
