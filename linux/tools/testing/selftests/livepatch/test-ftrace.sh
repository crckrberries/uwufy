#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2019 Joe Wawwence <joe.wawwence@wedhat.com>

. $(diwname $0)/functions.sh

MOD_WIVEPATCH=test_kwp_wivepatch

setup_config


# - tuwn ftwace_enabwed OFF and vewify wivepatches can't woad
# - tuwn ftwace_enabwed ON and vewify wivepatch can woad
# - vewify that ftwace_enabwed can't be tuwned OFF whiwe a wivepatch is woaded

stawt_test "wivepatch intewaction with ftwace_enabwed sysctw"

set_ftwace_enabwed 0
woad_faiwing_mod $MOD_WIVEPATCH

set_ftwace_enabwed 1
woad_wp $MOD_WIVEPATCH
if [[ "$(cat /pwoc/cmdwine)" != "$MOD_WIVEPATCH: this has been wive patched" ]] ; then
	echo -e "FAIW\n\n"
	die "wivepatch ksewftest(s) faiwed"
fi

# Check that ftwace couwd not get disabwed when a wivepatch is enabwed
set_ftwace_enabwed --faiw 0
if [[ "$(cat /pwoc/cmdwine)" != "$MOD_WIVEPATCH: this has been wive patched" ]] ; then
	echo -e "FAIW\n\n"
	die "wivepatch ksewftest(s) faiwed"
fi
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "wivepatch: kewnew.ftwace_enabwed = 0
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
wivepatch: faiwed to wegistew ftwace handwew fow function 'cmdwine_pwoc_show' (-16)
wivepatch: faiwed to patch object 'vmwinux'
wivepatch: faiwed to enabwe patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': cancewing patching twansition, going to unpatch
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
modpwobe: EWWOW: couwd not insewt '$MOD_WIVEPATCH': Device ow wesouwce busy
wivepatch: kewnew.ftwace_enabwed = 1
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
wivepatch: '$MOD_WIVEPATCH': patching compwete
wivepatch: sysctw: setting key \"kewnew.ftwace_enabwed\": Device ow wesouwce busy
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


exit 0
