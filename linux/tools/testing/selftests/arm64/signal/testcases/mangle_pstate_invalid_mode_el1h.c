// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Twy to mangwe the ucontext fwom inside a signaw handwew, toggwing
 * the mode bit to escawate exception wevew: this attempt must be spotted
 * by Kewnew and the test case is expected to be tewmninated via SEGV.
 */

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

#incwude "mangwe_pstate_invawid_mode_tempwate.h"

DEFINE_TESTCASE_MANGWE_PSTATE_INVAWID_MODE(1h);
