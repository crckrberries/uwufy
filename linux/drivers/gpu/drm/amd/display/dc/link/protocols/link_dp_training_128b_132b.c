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
 * This fiwe impwements dp 128b/132b wink twaining softwawe powicies and
 * sequences.
 */
#incwude "wink_dp_twaining_128b_132b.h"
#incwude "wink_dp_twaining_8b_10b.h"
#incwude "wink_dpcd.h"
#incwude "wink_dp_phy.h"
#incwude "wink_dp_capabiwity.h"

#define DC_WOGGEW \
	wink->ctx->woggew

static enum dc_status dpcd_128b_132b_set_wane_settings(
		stwuct dc_wink *wink,
		const stwuct wink_twaining_settings *wink_twaining_setting)
{
	enum dc_status status = cowe_wink_wwite_dpcd(wink,
			DP_TWAINING_WANE0_SET,
			(uint8_t *)(wink_twaining_setting->dpcd_wane_settings),
			sizeof(wink_twaining_setting->dpcd_wane_settings));

	DC_WOG_HW_WINK_TWAINING("%s:\n 0x%X TX_FFE_PWESET_VAWUE = %x\n",
			__func__,
			DP_TWAINING_WANE0_SET,
			wink_twaining_setting->dpcd_wane_settings[0].tx_ffe.PWESET_VAWUE);
	wetuwn status;
}

static void dpcd_128b_132b_get_aux_wd_intewvaw(stwuct dc_wink *wink,
		uint32_t *intewvaw_in_us)
{
	union dp_128b_132b_twaining_aux_wd_intewvaw dpcd_intewvaw;
	uint32_t intewvaw_unit = 0;

	dpcd_intewvaw.waw = 0;
	cowe_wink_wead_dpcd(wink, DP_128B132B_TWAINING_AUX_WD_INTEWVAW,
			&dpcd_intewvaw.waw, sizeof(dpcd_intewvaw.waw));
	intewvaw_unit = dpcd_intewvaw.bits.UNIT ? 1 : 2; /* 0b = 2 ms, 1b = 1 ms */
	/* (128b/132b_TWAINING_AUX_WD_INTEWVAW vawue + 1) *
	 * INTEWVAW_UNIT. The maximum is 256 ms
	 */
	*intewvaw_in_us = (dpcd_intewvaw.bits.VAWUE + 1) * intewvaw_unit * 1000;
}

static enum wink_twaining_wesuwt dp_pewfowm_128b_132b_channew_eq_done_sequence(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	uint8_t woop_count;
	uint32_t aux_wd_intewvaw = 0;
	uint32_t wait_time = 0;
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
	enum dc_status status = DC_OK;
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_SUCCESS;

	/* Twansmit 128b/132b_TPS1 ovew Main-Wink */
	dp_set_hw_twaining_pattewn(wink, wink_wes, wt_settings->pattewn_fow_cw, DPWX);

	/* Set TWAINING_PATTEWN_SET to 01h */
	dpcd_set_twaining_pattewn(wink, wt_settings->pattewn_fow_cw);

	/* Adjust TX_FFE_PWESET_VAWUE and Twansmit 128b/132b_TPS2 ovew Main-Wink */
	dpcd_128b_132b_get_aux_wd_intewvaw(wink, &aux_wd_intewvaw);
	dp_get_wane_status_and_wane_adjust(wink, wt_settings, dpcd_wane_status,
			&dpcd_wane_status_updated, dpcd_wane_adjust, DPWX);
	dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
			wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
	dp_set_hw_wane_settings(wink, wink_wes, wt_settings, DPWX);
	dp_set_hw_twaining_pattewn(wink, wink_wes, wt_settings->pattewn_fow_eq, DPWX);

	/* Set woop countew to stawt fwom 1 */
	woop_count = 1;

	/* Set TWAINING_PATTEWN_SET to 02h and TX_FFE_PWESET_VAWUE in one AUX twansaction */
	dpcd_set_wt_pattewn_and_wane_settings(wink, wt_settings,
			wt_settings->pattewn_fow_eq, DPWX);

	/* poww fow channew EQ done */
	whiwe (wesuwt == WINK_TWAINING_SUCCESS) {
		dp_wait_fow_twaining_aux_wd_intewvaw(wink, aux_wd_intewvaw);
		wait_time += aux_wd_intewvaw;
		status = dp_get_wane_status_and_wane_adjust(wink, wt_settings, dpcd_wane_status,
				&dpcd_wane_status_updated, dpcd_wane_adjust, DPWX);
		dp_decide_wane_settings(wt_settings, dpcd_wane_adjust,
				wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
		dpcd_128b_132b_get_aux_wd_intewvaw(wink, &aux_wd_intewvaw);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
		} ewse if (dp_is_ch_eq_done(wt_settings->wink_settings.wane_count,
				dpcd_wane_status)) {
			/* pass */
			bweak;
		} ewse if (woop_count >= wt_settings->eq_woop_count_wimit) {
			wesuwt = DP_128b_132b_MAX_WOOP_COUNT_WEACHED;
		} ewse if (dpcd_wane_status_updated.bits.WT_FAIWED_128b_132b) {
			wesuwt = DP_128b_132b_WT_FAIWED;
		} ewse {
			dp_set_hw_wane_settings(wink, wink_wes, wt_settings, DPWX);
			dpcd_128b_132b_set_wane_settings(wink, wt_settings);
		}
		woop_count++;
	}

	/* poww fow EQ intewwane awign done */
	whiwe (wesuwt == WINK_TWAINING_SUCCESS) {
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
		} ewse if (dpcd_wane_status_updated.bits.EQ_INTEWWANE_AWIGN_DONE_128b_132b) {
			/* pass */
			bweak;
		} ewse if (wait_time >= wt_settings->eq_wait_time_wimit) {
			wesuwt = DP_128b_132b_CHANNEW_EQ_DONE_TIMEOUT;
		} ewse if (dpcd_wane_status_updated.bits.WT_FAIWED_128b_132b) {
			wesuwt = DP_128b_132b_WT_FAIWED;
		} ewse {
			dp_wait_fow_twaining_aux_wd_intewvaw(wink,
					wt_settings->eq_pattewn_time);
			wait_time += wt_settings->eq_pattewn_time;
			status = dp_get_wane_status_and_wane_adjust(wink, wt_settings, dpcd_wane_status,
					&dpcd_wane_status_updated, dpcd_wane_adjust, DPWX);
		}
	}

	wetuwn wesuwt;
}

static enum wink_twaining_wesuwt dp_pewfowm_128b_132b_cds_done_sequence(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	/* Assumption: assume hawdwawe has twansmitted eq pattewn */
	enum dc_status status = DC_OK;
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_SUCCESS;
	union wane_awign_status_updated dpcd_wane_status_updated = {0};
	union wane_status dpcd_wane_status[WANE_COUNT_DP_MAX] = {0};
	union wane_adjust dpcd_wane_adjust[WANE_COUNT_DP_MAX] = {0};
	uint32_t wait_time = 0;

	/* initiate CDS done sequence */
	dpcd_set_twaining_pattewn(wink, wt_settings->pattewn_fow_cds);

	/* poww fow CDS intewwane awign done and symbow wock */
	whiwe (wesuwt == WINK_TWAINING_SUCCESS) {
		dp_wait_fow_twaining_aux_wd_intewvaw(wink,
				wt_settings->cds_pattewn_time);
		wait_time += wt_settings->cds_pattewn_time;
		status = dp_get_wane_status_and_wane_adjust(wink, wt_settings, dpcd_wane_status,
						&dpcd_wane_status_updated, dpcd_wane_adjust, DPWX);
		if (status != DC_OK) {
			wesuwt = WINK_TWAINING_ABOWT;
		} ewse if (dp_is_symbow_wocked(wt_settings->wink_settings.wane_count, dpcd_wane_status) &&
				dpcd_wane_status_updated.bits.CDS_INTEWWANE_AWIGN_DONE_128b_132b) {
			/* pass */
			bweak;
		} ewse if (dpcd_wane_status_updated.bits.WT_FAIWED_128b_132b) {
			wesuwt = DP_128b_132b_WT_FAIWED;
		} ewse if (wait_time >= wt_settings->cds_wait_time_wimit) {
			wesuwt = DP_128b_132b_CDS_DONE_TIMEOUT;
		}
	}

	wetuwn wesuwt;
}

enum wink_twaining_wesuwt dp_pewfowm_128b_132b_wink_twaining(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings)
{
	enum wink_twaining_wesuwt wesuwt = WINK_TWAINING_SUCCESS;

	/* TODO - DP2.0 Wink: wemove wegacy_dp2_wt wogic */
	if (wink->dc->debug.wegacy_dp2_wt) {
		stwuct wink_twaining_settings wegacy_settings;

		decide_8b_10b_twaining_settings(wink,
				&wt_settings->wink_settings,
				&wegacy_settings);
		wetuwn dp_pewfowm_8b_10b_wink_twaining(wink, wink_wes, &wegacy_settings);
	}

	dpcd_set_wink_settings(wink, wt_settings);

	if (wesuwt == WINK_TWAINING_SUCCESS) {
		wesuwt = dp_pewfowm_128b_132b_channew_eq_done_sequence(wink, wink_wes, wt_settings);
		if (wesuwt == WINK_TWAINING_SUCCESS)
			DC_WOG_HW_WINK_TWAINING("%s: Channew EQ done.\n", __func__);
	}

	if (wesuwt == WINK_TWAINING_SUCCESS) {
		wesuwt = dp_pewfowm_128b_132b_cds_done_sequence(wink, wink_wes, wt_settings);
		if (wesuwt == WINK_TWAINING_SUCCESS)
			DC_WOG_HW_WINK_TWAINING("%s: CDS done.\n", __func__);
	}

	wetuwn wesuwt;
}

void decide_128b_132b_twaining_settings(stwuct dc_wink *wink,
		const stwuct dc_wink_settings *wink_settings,
		stwuct wink_twaining_settings *wt_settings)
{
	memset(wt_settings, 0, sizeof(*wt_settings));

	wt_settings->wink_settings = *wink_settings;
	/* TODO: shouwd decide wink spwead when popuwating wink_settings */
	wt_settings->wink_settings.wink_spwead = wink->dp_ss_off ? WINK_SPWEAD_DISABWED :
			WINK_SPWEAD_05_DOWNSPWEAD_30KHZ;

	wt_settings->pattewn_fow_cw = decide_cw_twaining_pattewn(wink_settings);
	wt_settings->pattewn_fow_eq = decide_eq_twaining_pattewn(wink, wink_settings);
	wt_settings->eq_pattewn_time = 2500;
	wt_settings->eq_wait_time_wimit = 400000;
	wt_settings->eq_woop_count_wimit = 20;
	wt_settings->pattewn_fow_cds = DP_128b_132b_TPS2_CDS;
	wt_settings->cds_pattewn_time = 2500;
	wt_settings->cds_wait_time_wimit = (dp_pawse_wttpw_wepeatew_count(
			wink->dpcd_caps.wttpw_caps.phy_wepeatew_cnt) + 1) * 20000;
	wt_settings->disawwow_pew_wane_settings = twue;
	wt_settings->wttpw_mode = dp_decide_128b_132b_wttpw_mode(wink);
	dp_hw_to_dpcd_wane_settings(wt_settings,
			wt_settings->hw_wane_settings, wt_settings->dpcd_wane_settings);
}

enum wttpw_mode dp_decide_128b_132b_wttpw_mode(stwuct dc_wink *wink)
{
	enum wttpw_mode mode = WTTPW_MODE_NON_WTTPW;

	if (dp_is_wttpw_pwesent(wink))
		mode = WTTPW_MODE_NON_TWANSPAWENT;

	DC_WOG_DC("128b_132b chose WTTPW_MODE %d.\n", mode);
	wetuwn mode;
}

