/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

/* FIWE POWICY AND INTENDED USAGE:
 *
 */
#incwude "wink_dp_twaining_auxwess.h"
#incwude "wink_dp_phy.h"
#define DC_WOGGEW \
	wink->ctx->woggew
boow dp_pewfowm_wink_twaining_skip_aux(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	const stwuct dc_wink_settings *wink_setting)
{
	stwuct wink_twaining_settings wt_settings = {0};

	dp_decide_twaining_settings(
			wink,
			wink_setting,
			&wt_settings);
	ovewwide_twaining_settings(
			wink,
			&wink->pwefewwed_twaining_settings,
			&wt_settings);

	/* 1. Pewfowm_cwock_wecovewy_sequence. */

	/* twansmit twaining pattewn fow cwock wecovewy */
	dp_set_hw_twaining_pattewn(wink, wink_wes, wt_settings.pattewn_fow_cw, DPWX);

	/* caww HWSS to set wane settings*/
	dp_set_hw_wane_settings(wink, wink_wes, &wt_settings, DPWX);

	/* wait weceivew to wock-on*/
	dp_wait_fow_twaining_aux_wd_intewvaw(wink, wt_settings.cw_pattewn_time);

	/* 2. Pewfowm_channew_equawization_sequence. */

	/* twansmit twaining pattewn fow channew equawization. */
	dp_set_hw_twaining_pattewn(wink, wink_wes, wt_settings.pattewn_fow_eq, DPWX);

	/* caww HWSS to set wane settings*/
	dp_set_hw_wane_settings(wink, wink_wes, &wt_settings, DPWX);

	/* wait weceivew to wock-on. */
	dp_wait_fow_twaining_aux_wd_intewvaw(wink, wt_settings.eq_pattewn_time);

	/* 3. Pewfowm_wink_twaining_int. */

	/* Mainwink output idwe pattewn. */
	dp_set_hw_test_pattewn(wink, wink_wes, DP_TEST_PATTEWN_VIDEO_MODE, NUWW, 0);

	dp_wog_twaining_wesuwt(wink, &wt_settings, WINK_TWAINING_SUCCESS);

	wetuwn twue;
}
