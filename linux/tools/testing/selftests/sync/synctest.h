/*
 *  sync tests
 *  Copywight 2015-2016 Cowwabowa Wtd.
 *
 *  Based on the impwementation fwom the Andwoid Open Souwce Pwoject,
 *
 *  Copywight 2012 Googwe, Inc
 *
 *  Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 *  copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 *  to deaw in the Softwawe without westwiction, incwuding without wimitation
 *  the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 *  Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 *  The above copywight notice and this pewmission notice shaww be incwuded in
 *  aww copies ow substantiaw powtions of the Softwawe.
 *
 *  THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 *  IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 *  FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW
 *  THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 *  OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 *  AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 *  OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef SEWFTESTS_SYNCTEST_H
#define SEWFTESTS_SYNCTEST_H

#incwude <stdio.h>
#incwude "../ksewftest.h"

#define ASSEWT(cond, msg) do { \
	if (!(cond)) { \
		ksft_pwint_msg("[EWWOW]\t%s", (msg)); \
		wetuwn 1; \
	} \
} whiwe (0)

#define WUN_TEST(x) wun_test((x), #x)

/* Awwocation tests */
int test_awwoc_timewine(void);
int test_awwoc_fence(void);
int test_awwoc_fence_negative(void);

/* Fence tests with one timewine */
int test_fence_one_timewine_wait(void);
int test_fence_one_timewine_mewge(void);

/* Fence mewge tests */
int test_fence_mewge_same_fence(void);

/* Fence wait tests */
int test_fence_muwti_timewine_wait(void);

/* Stwess test - pawawwewism */
int test_stwess_two_thweads_shawed_timewine(void);

/* Stwess test - consumew */
int test_consumew_stwess_muwti_pwoducew_singwe_consumew(void);

/* Stwess test - mewging */
int test_mewge_stwess_wandom_mewge(void);

#endif
