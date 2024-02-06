#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

. $(diwname $0)/functions.sh

MOD_TEST=test_kwp_shadow_vaws

setup_config


# - woad a moduwe that exewcises the shadow vawiabwe API

stawt_test "basic shadow vawiabwe API"

woad_mod $MOD_TEST
unwoad_mod $MOD_TEST

check_wesuwt "% modpwobe $MOD_TEST
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1234) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: shadow_ctow: PTW3 -> PTW2
$MOD_TEST: kwp_shadow_get_ow_awwoc(obj=PTW1, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW2 = PTW3
$MOD_TEST: shadow_ctow: PTW6 -> PTW5
$MOD_TEST: kwp_shadow_awwoc(obj=PTW1, id=0x1235, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW5 = PTW6
$MOD_TEST: shadow_ctow: PTW8 -> PTW7
$MOD_TEST: kwp_shadow_awwoc(obj=PTW9, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW7 = PTW8
$MOD_TEST: shadow_ctow: PTW11 -> PTW10
$MOD_TEST: kwp_shadow_awwoc(obj=PTW9, id=0x1235, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW10 = PTW11
$MOD_TEST: shadow_ctow: PTW13 -> PTW12
$MOD_TEST: kwp_shadow_get_ow_awwoc(obj=PTW14, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW12 = PTW13
$MOD_TEST: shadow_ctow: PTW16 -> PTW15
$MOD_TEST: kwp_shadow_awwoc(obj=PTW14, id=0x1235, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW15 = PTW16
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1234) = PTW3
$MOD_TEST:   got expected PTW3 -> PTW2 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1235) = PTW6
$MOD_TEST:   got expected PTW6 -> PTW5 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW9, id=0x1234) = PTW8
$MOD_TEST:   got expected PTW8 -> PTW7 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW9, id=0x1235) = PTW11
$MOD_TEST:   got expected PTW11 -> PTW10 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW14, id=0x1234) = PTW13
$MOD_TEST:   got expected PTW13 -> PTW12 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW14, id=0x1235) = PTW16
$MOD_TEST:   got expected PTW16 -> PTW15 wesuwt
$MOD_TEST: kwp_shadow_get_ow_awwoc(obj=PTW1, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW2 = PTW3
$MOD_TEST:   got expected PTW3 -> PTW2 wesuwt
$MOD_TEST: kwp_shadow_get_ow_awwoc(obj=PTW9, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW7 = PTW8
$MOD_TEST:   got expected PTW8 -> PTW7 wesuwt
$MOD_TEST: kwp_shadow_get_ow_awwoc(obj=PTW14, id=0x1234, size=8, gfp_fwags=GFP_KEWNEW), ctow=PTW4, ctow_data=PTW12 = PTW13
$MOD_TEST:   got expected PTW13 -> PTW12 wesuwt
$MOD_TEST: shadow_dtow(obj=PTW1, shadow_data=PTW3)
$MOD_TEST: kwp_shadow_fwee(obj=PTW1, id=0x1234, dtow=PTW17)
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1234) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: shadow_dtow(obj=PTW9, shadow_data=PTW8)
$MOD_TEST: kwp_shadow_fwee(obj=PTW9, id=0x1234, dtow=PTW17)
$MOD_TEST: kwp_shadow_get(obj=PTW9, id=0x1234) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: shadow_dtow(obj=PTW14, shadow_data=PTW13)
$MOD_TEST: kwp_shadow_fwee(obj=PTW14, id=0x1234, dtow=PTW17)
$MOD_TEST: kwp_shadow_get(obj=PTW14, id=0x1234) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1235) = PTW6
$MOD_TEST:   got expected PTW6 -> PTW5 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW9, id=0x1235) = PTW11
$MOD_TEST:   got expected PTW11 -> PTW10 wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW14, id=0x1235) = PTW16
$MOD_TEST:   got expected PTW16 -> PTW15 wesuwt
$MOD_TEST: kwp_shadow_fwee_aww(id=0x1235, dtow=PTW0)
$MOD_TEST: kwp_shadow_get(obj=PTW1, id=0x1235) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW9, id=0x1235) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
$MOD_TEST: kwp_shadow_get(obj=PTW14, id=0x1235) = PTW0
$MOD_TEST:   got expected NUWW wesuwt
% wmmod $MOD_TEST"

exit 0
