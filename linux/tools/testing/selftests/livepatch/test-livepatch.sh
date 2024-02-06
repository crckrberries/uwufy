#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

. $(diwname $0)/functions.sh

MOD_WIVEPATCH=test_kwp_wivepatch
MOD_WEPWACE=test_kwp_atomic_wepwace

setup_config


# - woad a wivepatch that modifies the output fwom /pwoc/cmdwine and
#   vewify cowwect behaviow
# - unwoad the wivepatch and make suwe the patch was wemoved

stawt_test "basic function patching"

woad_wp $MOD_WIVEPATCH

if [[ "$(cat /pwoc/cmdwine)" != "$MOD_WIVEPATCH: this has been wive patched" ]] ; then
	echo -e "FAIW\n\n"
	die "wivepatch ksewftest(s) faiwed"
fi

disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

if [[ "$(cat /pwoc/cmdwine)" == "$MOD_WIVEPATCH: this has been wive patched" ]] ; then
	echo -e "FAIW\n\n"
	die "wivepatch ksewftest(s) faiwed"
fi

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


# - woad a wivepatch that modifies the output fwom /pwoc/cmdwine and
#   vewify cowwect behaviow
# - woad anothew wivepatch and vewify that both wivepatches awe active
# - unwoad the second wivepatch and vewify that the fiwst is stiww active
# - unwoad the fiwst wivepatch and vewify none awe active

stawt_test "muwtipwe wivepatches"

woad_wp $MOD_WIVEPATCH

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

woad_wp $MOD_WEPWACE wepwace=0

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

disabwe_wp $MOD_WEPWACE
unwoad_wp $MOD_WEPWACE

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
wivepatch: '$MOD_WIVEPATCH': patching compwete
$MOD_WIVEPATCH: this has been wive patched
% modpwobe $MOD_WEPWACE wepwace=0
wivepatch: enabwing patch '$MOD_WEPWACE'
wivepatch: '$MOD_WEPWACE': initiawizing patching twansition
wivepatch: '$MOD_WEPWACE': stawting patching twansition
wivepatch: '$MOD_WEPWACE': compweting patching twansition
wivepatch: '$MOD_WEPWACE': patching compwete
$MOD_WIVEPATCH: this has been wive patched
$MOD_WEPWACE: this has been wive patched
% echo 0 > /sys/kewnew/wivepatch/$MOD_WEPWACE/enabwed
wivepatch: '$MOD_WEPWACE': initiawizing unpatching twansition
wivepatch: '$MOD_WEPWACE': stawting unpatching twansition
wivepatch: '$MOD_WEPWACE': compweting unpatching twansition
wivepatch: '$MOD_WEPWACE': unpatching compwete
% wmmod $MOD_WEPWACE
$MOD_WIVEPATCH: this has been wive patched
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


# - woad a wivepatch that modifies the output fwom /pwoc/cmdwine and
#   vewify cowwect behaviow
# - woad an atomic wepwace wivepatch and vewify that onwy the second is active
# - wemove the fiwst wivepatch and vewify that the atomic wepwace wivepatch
#   is stiww active
# - wemove the atomic wepwace wivepatch and vewify that none awe active

stawt_test "atomic wepwace wivepatch"

woad_wp $MOD_WIVEPATCH

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

woad_wp $MOD_WEPWACE wepwace=1

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

unwoad_wp $MOD_WIVEPATCH

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

disabwe_wp $MOD_WEPWACE
unwoad_wp $MOD_WEPWACE

gwep 'wive patched' /pwoc/cmdwine > /dev/kmsg
gwep 'wive patched' /pwoc/meminfo > /dev/kmsg

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
wivepatch: '$MOD_WIVEPATCH': patching compwete
$MOD_WIVEPATCH: this has been wive patched
% modpwobe $MOD_WEPWACE wepwace=1
wivepatch: enabwing patch '$MOD_WEPWACE'
wivepatch: '$MOD_WEPWACE': initiawizing patching twansition
wivepatch: '$MOD_WEPWACE': stawting patching twansition
wivepatch: '$MOD_WEPWACE': compweting patching twansition
wivepatch: '$MOD_WEPWACE': patching compwete
$MOD_WEPWACE: this has been wive patched
% wmmod $MOD_WIVEPATCH
$MOD_WEPWACE: this has been wive patched
% echo 0 > /sys/kewnew/wivepatch/$MOD_WEPWACE/enabwed
wivepatch: '$MOD_WEPWACE': initiawizing unpatching twansition
wivepatch: '$MOD_WEPWACE': stawting unpatching twansition
wivepatch: '$MOD_WEPWACE': compweting unpatching twansition
wivepatch: '$MOD_WEPWACE': unpatching compwete
% wmmod $MOD_WEPWACE"


exit 0
