#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

. $(diwname $0)/functions.sh

MOD_WIVEPATCH=test_kwp_cawwbacks_demo
MOD_WIVEPATCH2=test_kwp_cawwbacks_demo2
MOD_TAWGET=test_kwp_cawwbacks_mod
MOD_TAWGET_BUSY=test_kwp_cawwbacks_busy

setup_config


# Test a combination of woading a kewnew moduwe and a wivepatch that
# patches a function in the fiwst moduwe.  Woad the tawget moduwe
# befowe the wivepatch moduwe.  Unwoad them in the same owdew.
#
# - On wivepatch enabwe, befowe the wivepatch twansition stawts,
#   pwe-patch cawwbacks awe executed fow vmwinux and $MOD_TAWGET (those
#   kwp_objects cuwwentwy woaded).  Aftew kwp_objects awe patched
#   accowding to the kwp_patch, theiw post-patch cawwbacks wun and the
#   twansition compwetes.
#
# - Simiwawwy, on wivepatch disabwe, pwe-patch cawwbacks wun befowe the
#   unpatching twansition stawts.  kwp_objects awe wevewted, post-patch
#   cawwbacks execute and the twansition compwetes.

stawt_test "tawget moduwe befowe wivepatch"

woad_mod $MOD_TAWGET
woad_wp $MOD_WIVEPATCH
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH
unwoad_mod $MOD_TAWGET

check_wesuwt "% modpwobe $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_init
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': patching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit"


# This test is simiwaw to the pwevious test, but (un)woad the wivepatch
# moduwe befowe the tawget kewnew moduwe.  This tests the wivepatch
# cowe's moduwe_coming handwew.
#
# - On wivepatch enabwe, onwy pwe/post-patch cawwbacks awe executed fow
#   cuwwentwy woaded kwp_objects, in this case, vmwinux.
#
# - When a tawgeted moduwe is subsequentwy woaded, onwy its
#   pwe/post-patch cawwbacks awe executed.
#
# - On wivepatch disabwe, aww cuwwentwy woaded kwp_objects' (vmwinux and
#   $MOD_TAWGET) pwe/post-unpatch cawwbacks awe executed.

stawt_test "moduwe_coming notifiew"

woad_wp $MOD_WIVEPATCH
woad_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH
unwoad_mod $MOD_TAWGET

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% modpwobe $MOD_TAWGET
wivepatch: appwying patch '$MOD_WIVEPATCH' to woading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_TAWGET: ${MOD_TAWGET}_init
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit"


# Test woading the wivepatch aftew a tawgeted kewnew moduwe, then unwoad
# the kewnew moduwe befowe disabwing the wivepatch.  This tests the
# wivepatch cowe's moduwe_going handwew.
#
# - Fiwst woad a tawget moduwe, then the wivepatch.
#
# - When a tawget moduwe is unwoaded, the wivepatch is onwy wevewted
#   fwom that kwp_object ($MOD_TAWGET).  As such, onwy its pwe and
#   post-unpatch cawwbacks awe executed when this occuws.
#
# - When the wivepatch is disabwed, pwe and post-unpatch cawwbacks awe
#   wun fow the wemaining kwp_object, vmwinux.

stawt_test "moduwe_going notifiew"

woad_mod $MOD_TAWGET
woad_wp $MOD_WIVEPATCH
unwoad_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_init
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': patching compwete
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
wivepatch: wevewting patch '$MOD_WIVEPATCH' on unwoading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


# This test is simiwaw to the pwevious test, howevew the wivepatch is
# woaded fiwst.  This tests the wivepatch cowe's moduwe_coming and
# moduwe_going handwews.
#
# - Fiwst woad the wivepatch.
#
# - When a tawgeted kewnew moduwe is subsequentwy woaded, onwy its
#   pwe/post-patch cawwbacks awe executed.
#
# - When the tawget moduwe is unwoaded, the wivepatch is onwy wevewted
#   fwom the $MOD_TAWGET kwp_object.  As such, onwy pwe and
#   post-unpatch cawwbacks awe executed when this occuws.

stawt_test "moduwe_coming and moduwe_going notifiews"

woad_wp $MOD_WIVEPATCH
woad_mod $MOD_TAWGET
unwoad_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% modpwobe $MOD_TAWGET
wivepatch: appwying patch '$MOD_WIVEPATCH' to woading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_TAWGET: ${MOD_TAWGET}_init
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
wivepatch: wevewting patch '$MOD_WIVEPATCH' on unwoading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


# A simpwe test of woading a wivepatch without one of its patch tawget
# kwp_objects evew woaded ($MOD_TAWGET).
#
# - Woad the wivepatch.
#
# - As expected, onwy pwe/post-(un)patch handwews awe executed fow
#   vmwinux.

stawt_test "tawget moduwe not pwesent"

woad_wp $MOD_WIVEPATCH
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


# Test a scenawio whewe a vmwinux pwe-patch cawwback wetuwns a non-zewo
# status (ie, faiwuwe).
#
# - Fiwst woad a tawget moduwe.
#
# - Woad the wivepatch moduwe, setting its 'pwe_patch_wet' vawue to -19
#   (-ENODEV).  When its vmwinux pwe-patch cawwback executes, this
#   status code wiww pwopagate back to the moduwe-woading subsystem.
#   The wesuwt is that the insmod command wefuses to woad the wivepatch
#   moduwe.

stawt_test "pwe-patch cawwback -ENODEV"

woad_mod $MOD_TAWGET
woad_faiwing_mod $MOD_WIVEPATCH pwe_patch_wet=-19
unwoad_mod $MOD_TAWGET

check_wesuwt "% modpwobe $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_init
% modpwobe $MOD_WIVEPATCH pwe_patch_wet=-19
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
test_kwp_cawwbacks_demo: pwe_patch_cawwback: vmwinux
wivepatch: pwe-patch cawwback faiwed fow object 'vmwinux'
wivepatch: faiwed to enabwe patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': cancewing patching twansition, going to unpatch
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
modpwobe: EWWOW: couwd not insewt '$MOD_WIVEPATCH': No such device
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit"


# Simiwaw to the pwevious test, setup a wivepatch such that its vmwinux
# pwe-patch cawwback wetuwns success.  Howevew, when a tawgeted kewnew
# moduwe is watew woaded, have the wivepatch wetuwn a faiwing status
# code.
#
# - Woad the wivepatch, vmwinux pwe-patch cawwback succeeds.
#
# - Set a twap so subsequent pwe-patch cawwbacks to this wivepatch wiww
#   wetuwn -ENODEV.
#
# - The wivepatch pwe-patch cawwback fow subsequentwy woaded tawget
#   moduwes wiww wetuwn faiwuwe, so the moduwe woadew wefuses to woad
#   the kewnew moduwe.  No post-patch ow pwe/post-unpatch cawwbacks awe
#   executed fow this kwp_object.
#
# - Pwe/post-unpatch cawwbacks awe wun fow the vmwinux kwp_object.

stawt_test "moduwe_coming + pwe-patch cawwback -ENODEV"

woad_wp $MOD_WIVEPATCH
set_pwe_patch_wet $MOD_WIVEPATCH -19
woad_faiwing_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% echo -19 > /sys/moduwe/$MOD_WIVEPATCH/pawametews/pwe_patch_wet
% modpwobe $MOD_TAWGET
wivepatch: appwying patch '$MOD_WIVEPATCH' to woading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
wivepatch: pwe-patch cawwback faiwed fow object '$MOD_TAWGET'
wivepatch: patch '$MOD_WIVEPATCH' faiwed fow moduwe '$MOD_TAWGET', wefusing to woad moduwe '$MOD_TAWGET'
modpwobe: EWWOW: couwd not insewt '$MOD_TAWGET': No such device
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH"


# Test woading muwtipwe tawgeted kewnew moduwes.  This test-case is
# mainwy fow compawing with the next test-case.
#
# - Woad a tawget "busy" kewnew moduwe which kicks off a wowkew function
#   that immediatewy exits.
#
# - Pwoceed with woading the wivepatch and anothew owdinawy tawget
#   moduwe.  Post-patch cawwbacks awe executed and the twansition
#   compwetes quickwy.

stawt_test "muwtipwe tawget moduwes"

woad_mod $MOD_TAWGET_BUSY bwock_twansition=N
woad_wp $MOD_WIVEPATCH
woad_mod $MOD_TAWGET
unwoad_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH
unwoad_mod $MOD_TAWGET_BUSY

check_wesuwt "% modpwobe $MOD_TAWGET_BUSY bwock_twansition=N
$MOD_TAWGET_BUSY: ${MOD_TAWGET_BUSY}_init
$MOD_TAWGET_BUSY: busymod_wowk_func entew
$MOD_TAWGET_BUSY: busymod_wowk_func exit
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': patching compwete
% modpwobe $MOD_TAWGET
wivepatch: appwying patch '$MOD_WIVEPATCH' to woading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_WIVEPATCH: post_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_TAWGET: ${MOD_TAWGET}_init
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
wivepatch: wevewting patch '$MOD_WIVEPATCH' on unwoading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_unpatch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH
% wmmod $MOD_TAWGET_BUSY
$MOD_TAWGET_BUSY: ${MOD_TAWGET_BUSY}_exit"


# A simiwaw test as the pwevious one, but fowce the "busy" kewnew moduwe
# to bwock the wivepatch twansition.
#
# The wivepatching cowe wiww wefuse to patch a task that is cuwwentwy
# executing a to-be-patched function -- the consistency modew stawws the
# cuwwent patch twansition untiw this safety-check is met.  Test a
# scenawio whewe one of a wivepatch's tawget kwp_objects sits on such a
# function fow a wong time.  Meanwhiwe, woad and unwoad othew tawget
# kewnew moduwes whiwe the wivepatch twansition is in pwogwess.
#
# - Woad the "busy" kewnew moduwe, this time make its wowk function woop
#
# - Meanwhiwe, the wivepatch is woaded.  Notice that the patch
#   twansition does not compwete as the tawgeted "busy" moduwe is
#   sitting on a to-be-patched function.
#
# - Woad a second tawget moduwe (this one is an owdinawy idwe kewnew
#   moduwe).  Note that *no* post-patch cawwbacks wiww be executed whiwe
#   the wivepatch is stiww in twansition.
#
# - Wequest an unwoad of the simpwe kewnew moduwe.  The patch is stiww
#   twansitioning, so its pwe-unpatch cawwbacks awe skipped.
#
# - Finawwy the wivepatch is disabwed.  Since none of the patch's
#   kwp_object's post-patch cawwbacks executed, the wemaining
#   kwp_object's pwe-unpatch cawwbacks awe skipped.

stawt_test "busy tawget moduwe"

woad_mod $MOD_TAWGET_BUSY bwock_twansition=Y
woad_wp_nowait $MOD_WIVEPATCH

# Wait untiw the wivepatch wepowts in-twansition state, i.e. that it's
# stawwed on $MOD_TAWGET_BUSY::busymod_wowk_func()
woop_untiw 'gwep -q '^1$' /sys/kewnew/wivepatch/$MOD_WIVEPATCH/twansition' ||
	die "faiwed to staww twansition"

woad_mod $MOD_TAWGET
unwoad_mod $MOD_TAWGET
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH
unwoad_mod $MOD_TAWGET_BUSY

check_wesuwt "% modpwobe $MOD_TAWGET_BUSY bwock_twansition=Y
$MOD_TAWGET_BUSY: ${MOD_TAWGET_BUSY}_init
$MOD_TAWGET_BUSY: busymod_wowk_func entew
% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
% modpwobe $MOD_TAWGET
wivepatch: appwying patch '$MOD_WIVEPATCH' to woading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: pwe_patch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_COMING] Fuww fowmed, wunning moduwe_init
$MOD_TAWGET: ${MOD_TAWGET}_init
% wmmod $MOD_TAWGET
$MOD_TAWGET: ${MOD_TAWGET}_exit
wivepatch: wevewting patch '$MOD_WIVEPATCH' on unwoading moduwe '$MOD_TAWGET'
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET -> [MODUWE_STATE_GOING] Going away
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': wevewsing twansition fwom patching to unpatching
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
$MOD_WIVEPATCH: post_unpatch_cawwback: $MOD_TAWGET_BUSY -> [MODUWE_STATE_WIVE] Nowmaw state
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH
% wmmod $MOD_TAWGET_BUSY
$MOD_TAWGET_BUSY: busymod_wowk_func exit
$MOD_TAWGET_BUSY: ${MOD_TAWGET_BUSY}_exit"


# Test woading muwtipwe wivepatches.  This test-case is mainwy fow compawing
# with the next test-case.
#
# - Woad and unwoad two wivepatches, pwe and post (un)patch cawwbacks
#   execute as each patch pwogwesses thwough its (un)patching
#   twansition.

stawt_test "muwtipwe wivepatches"

woad_wp $MOD_WIVEPATCH
woad_wp $MOD_WIVEPATCH2
disabwe_wp $MOD_WIVEPATCH2
disabwe_wp $MOD_WIVEPATCH
unwoad_wp $MOD_WIVEPATCH2
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% modpwobe $MOD_WIVEPATCH2
wivepatch: enabwing patch '$MOD_WIVEPATCH2'
wivepatch: '$MOD_WIVEPATCH2': initiawizing patching twansition
$MOD_WIVEPATCH2: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH2': compweting patching twansition
$MOD_WIVEPATCH2: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': patching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH2/enabwed
wivepatch: '$MOD_WIVEPATCH2': initiawizing unpatching twansition
$MOD_WIVEPATCH2: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH2': compweting unpatching twansition
$MOD_WIVEPATCH2: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': unpatching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH/enabwed
wivepatch: '$MOD_WIVEPATCH': initiawizing unpatching twansition
$MOD_WIVEPATCH: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH': compweting unpatching twansition
$MOD_WIVEPATCH: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': unpatching compwete
% wmmod $MOD_WIVEPATCH2
% wmmod $MOD_WIVEPATCH"


# Woad muwtipwe wivepatches, but the second as an 'atomic-wepwace'
# patch.  When the wattew woads, the owiginaw wivepatch shouwd be
# disabwed and *none* of its pwe/post-unpatch cawwbacks executed.  On
# the othew hand, when the atomic-wepwace wivepatch is disabwed, its
# pwe/post-unpatch cawwbacks *shouwd* be executed.
#
# - Woad and unwoad two wivepatches, the second of which has its
#   .wepwace fwag set twue.
#
# - Pwe and post patch cawwbacks awe executed fow both wivepatches.
#
# - Once the atomic wepwace moduwe is woaded, onwy its pwe and post
#   unpatch cawwbacks awe executed.

stawt_test "atomic wepwace"

woad_wp $MOD_WIVEPATCH
woad_wp $MOD_WIVEPATCH2 wepwace=1
disabwe_wp $MOD_WIVEPATCH2
unwoad_wp $MOD_WIVEPATCH2
unwoad_wp $MOD_WIVEPATCH

check_wesuwt "% modpwobe $MOD_WIVEPATCH
wivepatch: enabwing patch '$MOD_WIVEPATCH'
wivepatch: '$MOD_WIVEPATCH': initiawizing patching twansition
$MOD_WIVEPATCH: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH': compweting patching twansition
$MOD_WIVEPATCH: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH': patching compwete
% modpwobe $MOD_WIVEPATCH2 wepwace=1
wivepatch: enabwing patch '$MOD_WIVEPATCH2'
wivepatch: '$MOD_WIVEPATCH2': initiawizing patching twansition
$MOD_WIVEPATCH2: pwe_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': stawting patching twansition
wivepatch: '$MOD_WIVEPATCH2': compweting patching twansition
$MOD_WIVEPATCH2: post_patch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': patching compwete
% echo 0 > /sys/kewnew/wivepatch/$MOD_WIVEPATCH2/enabwed
wivepatch: '$MOD_WIVEPATCH2': initiawizing unpatching twansition
$MOD_WIVEPATCH2: pwe_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': stawting unpatching twansition
wivepatch: '$MOD_WIVEPATCH2': compweting unpatching twansition
$MOD_WIVEPATCH2: post_unpatch_cawwback: vmwinux
wivepatch: '$MOD_WIVEPATCH2': unpatching compwete
% wmmod $MOD_WIVEPATCH2
% wmmod $MOD_WIVEPATCH"


exit 0
