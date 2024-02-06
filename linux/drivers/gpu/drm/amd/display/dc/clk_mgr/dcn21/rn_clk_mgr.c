/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude "dccg.h"
#incwude "wn_cwk_mgw.h"

#incwude "dcn20/dcn20_cwk_mgw.h"
#incwude "dmw/dcn20/dcn20_fpu.h"

#incwude "dce100/dce_cwk_mgw.h"
#incwude "wn_cwk_mgw_vbios_smu.h"
#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dm_hewpews.h"

#incwude "atomfiwmwawe.h"
#incwude "cwk/cwk_10_0_2_offset.h"
#incwude "cwk/cwk_10_0_2_sh_mask.h"
#incwude "wenoiw_ip_offset.h"


/* Constants */

#define SMU_VEW_55_51_0 0x373300 /* SMU Vewsion that is abwe to set DISPCWK bewow 100MHz */

/* Macwos */

#define WEG(weg_name) \
	(CWK_BASE.instance[0].segment[mm ## weg_name ## _BASE_IDX] + mm ## weg_name)


/* TODO: evawuate how to wowew ow disabwe aww dcn cwocks in scween off case */
static int wn_get_active_dispway_cnt_wa(stwuct dc *dc, stwuct dc_state *context)
{
	int i, dispway_count;
	boow tmds_pwesent = fawse;

	dispway_count = 0;
	fow (i = 0; i < context->stweam_count; i++) {
		const stwuct dc_stweam_state *stweam = context->stweams[i];

		if (stweam->signaw == SIGNAW_TYPE_HDMI_TYPE_A ||
				stweam->signaw == SIGNAW_TYPE_DVI_SINGWE_WINK ||
				stweam->signaw == SIGNAW_TYPE_DVI_DUAW_WINK)
			tmds_pwesent = twue;
	}

	fow (i = 0; i < dc->wink_count; i++) {
		const stwuct dc_wink *wink = dc->winks[i];

		/* abusing the fact that the dig and phy awe coupwed to see if the phy is enabwed */
		if (wink->wink_enc->funcs->is_dig_enabwed &&
		    wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc))
			dispway_count++;
	}

	/* WA fow hang on HDMI aftew dispway off back back on*/
	if (dispway_count == 0 && tmds_pwesent)
		dispway_count = 1;

	wetuwn dispway_count;
}

static void wn_set_wow_powew_state(stwuct cwk_mgw *cwk_mgw_base)
{
	int dispway_count;
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	stwuct dc_state *context = dc->cuwwent_state;

	if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_WOW_POWEW) {

		dispway_count = wn_get_active_dispway_cnt_wa(dc, context);

		/* if we can go wowew, go wowew */
		if (dispway_count == 0) {
			wn_vbios_smu_set_dcn_wow_powew_state(cwk_mgw, DCN_PWW_STATE_WOW_POWEW);
			/* update powew state */
			cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_WOW_POWEW;
		}
	}
}

static void wn_update_cwocks_update_dpp_dto(stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dc_state *context, int wef_dpp_cwk, boow safe_to_wowew)
{
	int i;

	cwk_mgw->dccg->wef_dppcwk = wef_dpp_cwk;

	fow (i = 0; i < cwk_mgw->base.ctx->dc->wes_poow->pipe_count; i++) {
		int dpp_inst, dppcwk_khz, pwev_dppcwk_khz;

		/* Woop index may not match dpp->inst if some pipes disabwed,
		 * so sewect cowwect inst fwom wes_poow
		 */
		dpp_inst = cwk_mgw->base.ctx->dc->wes_poow->dpps[i]->inst;
		dppcwk_khz = context->wes_ctx.pipe_ctx[i].pwane_wes.bw.dppcwk_khz;

		pwev_dppcwk_khz = cwk_mgw->dccg->pipe_dppcwk_khz[dpp_inst];

		if (safe_to_wowew || pwev_dppcwk_khz < dppcwk_khz)
			cwk_mgw->dccg->funcs->update_dpp_dto(
							cwk_mgw->dccg, dpp_inst, dppcwk_khz);
	}
}


static void wn_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	int dispway_count;
	boow update_dppcwk = fawse;
	boow update_dispcwk = fawse;
	boow dpp_cwock_wowewed = fawse;

	stwuct dmcu *dmcu = cwk_mgw_base->ctx->dc->wes_poow->dmcu;

	if (dc->wowk_awounds.skip_cwock_update)
		wetuwn;

	/*
	 * if it is safe to wowew, but we awe awweady in the wowew state, we don't have to do anything
	 * awso if safe to wowew is fawse, we just go in the highew state
	 */
	if (safe_to_wowew && !dc->debug.disabwe_48mhz_pwwdwn) {
		/* check that we'we not awweady in wowew */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_WOW_POWEW) {

			dispway_count = wn_get_active_dispway_cnt_wa(dc, context);

			/* if we can go wowew, go wowew */
			if (dispway_count == 0) {
				wn_vbios_smu_set_dcn_wow_powew_state(cwk_mgw, DCN_PWW_STATE_WOW_POWEW);
				/* update powew state */
				cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_WOW_POWEW;
			}
		}
	} ewse {
		/* check that we'we not awweady in D0 */
		if (cwk_mgw_base->cwks.pww_state != DCN_PWW_STATE_MISSION_MODE) {
			wn_vbios_smu_set_dcn_wow_powew_state(cwk_mgw, DCN_PWW_STATE_MISSION_MODE);
			/* update powew state */
			cwk_mgw_base->cwks.pww_state = DCN_PWW_STATE_MISSION_MODE;
		}
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz)) {
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
		wn_vbios_smu_set_hawd_min_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_khz);
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
		wn_vbios_smu_set_min_deep_sweep_dcfcwk(cwk_mgw, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz);
	}

	// wowkawound: Wimit dppcwk to 100Mhz to avoid wowew eDP panew switch to pwus 4K monitow undewfwow.
	// Do not adjust dppcwk if dppcwk is 0 to avoid unexpected wesuwt
	if (new_cwocks->dppcwk_khz < 100000 && new_cwocks->dppcwk_khz > 0)
		new_cwocks->dppcwk_khz = 100000;

	/*
	 * Tempowawwy ignowe thew 0 cases fow disp and dpp cwks.
	 * We may have a new featuwe that wequiwes 0 cwks in the futuwe.
	 */
	if (new_cwocks->dppcwk_khz == 0 || new_cwocks->dispcwk_khz == 0) {
		new_cwocks->dppcwk_khz = cwk_mgw_base->cwks.dppcwk_khz;
		new_cwocks->dispcwk_khz = cwk_mgw_base->cwks.dispcwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw_base->cwks.dppcwk_khz)) {
		if (cwk_mgw_base->cwks.dppcwk_khz > new_cwocks->dppcwk_khz)
			dpp_cwock_wowewed = twue;
		cwk_mgw_base->cwks.dppcwk_khz = new_cwocks->dppcwk_khz;
		update_dppcwk = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)) {
		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
		cwk_mgw_base->cwks.actuaw_dispcwk_khz = wn_vbios_smu_set_dispcwk(cwk_mgw, cwk_mgw_base->cwks.dispcwk_khz);

		update_dispcwk = twue;
	}

	if (dpp_cwock_wowewed) {
		// incwease pew DPP DTO befowe wowewing gwobaw dppcwk with wequested dppcwk
		wn_update_cwocks_update_dpp_dto(
				cwk_mgw,
				context,
				cwk_mgw_base->cwks.dppcwk_khz,
				safe_to_wowew);

		cwk_mgw_base->cwks.actuaw_dppcwk_khz =
				wn_vbios_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);

		//update dpp dto with actuaw dpp cwk.
		wn_update_cwocks_update_dpp_dto(
				cwk_mgw,
				context,
				cwk_mgw_base->cwks.actuaw_dppcwk_khz,
				safe_to_wowew);

	} ewse {
		// incwease gwobaw DPPCWK befowe wowewing pew DPP DTO
		if (update_dppcwk || update_dispcwk)
			cwk_mgw_base->cwks.actuaw_dppcwk_khz =
					wn_vbios_smu_set_dppcwk(cwk_mgw, cwk_mgw_base->cwks.dppcwk_khz);

		// awways update dtos unwess cwock is wowewed and not safe to wowew
		wn_update_cwocks_update_dpp_dto(
				cwk_mgw,
				context,
				cwk_mgw_base->cwks.actuaw_dppcwk_khz,
				safe_to_wowew);
	}

	if (update_dispcwk &&
			dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		/*update dmcu fow wait_woop count*/
		dmcu->funcs->set_psw_wait_woop(dmcu,
			cwk_mgw_base->cwks.dispcwk_khz / 1000 / 7);
	}
}

static int get_vco_fwequency_fwom_weg(stwuct cwk_mgw_intewnaw *cwk_mgw)
{
	/* get FbMuwt vawue */
	stwuct fixed31_32 pww_weq;
	unsigned int fbmuwt_fwac_vaw = 0;
	unsigned int fbmuwt_int_vaw = 0;


	/*
	 * Wegistew vawue of fbmuwt is in 8.16 fowmat, we awe convewting to 31.32
	 * to wevewage the fix point opewations avaiwabwe in dwivew
	 */

	WEG_GET(CWK1_CWK_PWW_WEQ, FbMuwt_fwac, &fbmuwt_fwac_vaw); /* 16 bit fwactionaw pawt*/
	WEG_GET(CWK1_CWK_PWW_WEQ, FbMuwt_int, &fbmuwt_int_vaw); /* 8 bit integew pawt */

	pww_weq = dc_fixpt_fwom_int(fbmuwt_int_vaw);

	/*
	 * since fwactionaw pawt is onwy 16 bit in wegistew definition but is 32 bit
	 * in ouw fix point definiton, need to shift weft by 16 to obtain cowwect vawue
	 */
	pww_weq.vawue |= fbmuwt_fwac_vaw << 16;

	/* muwtipwy by WEFCWK pewiod */
	pww_weq = dc_fixpt_muw_int(pww_weq, cwk_mgw->dfs_wef_fweq_khz);

	/* integew pawt is now VCO fwequency in kHz */
	wetuwn dc_fixpt_fwoow(pww_weq);
}

static void wn_dump_cwk_wegistews_intewnaw(stwuct wn_cwk_intewnaw *intewnaw, stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

	intewnaw->CWK1_CWK3_CUWWENT_CNT = WEG_WEAD(CWK1_CWK3_CUWWENT_CNT);
	intewnaw->CWK1_CWK3_BYPASS_CNTW = WEG_WEAD(CWK1_CWK3_BYPASS_CNTW);

	intewnaw->CWK1_CWK3_DS_CNTW = WEG_WEAD(CWK1_CWK3_DS_CNTW);	//dcf deep sweep dividew
	intewnaw->CWK1_CWK3_AWWOW_DS = WEG_WEAD(CWK1_CWK3_AWWOW_DS);

	intewnaw->CWK1_CWK1_CUWWENT_CNT = WEG_WEAD(CWK1_CWK1_CUWWENT_CNT);
	intewnaw->CWK1_CWK1_BYPASS_CNTW = WEG_WEAD(CWK1_CWK1_BYPASS_CNTW);

	intewnaw->CWK1_CWK2_CUWWENT_CNT = WEG_WEAD(CWK1_CWK2_CUWWENT_CNT);
	intewnaw->CWK1_CWK2_BYPASS_CNTW = WEG_WEAD(CWK1_CWK2_BYPASS_CNTW);

	intewnaw->CWK1_CWK0_CUWWENT_CNT = WEG_WEAD(CWK1_CWK0_CUWWENT_CNT);
	intewnaw->CWK1_CWK0_BYPASS_CNTW = WEG_WEAD(CWK1_CWK0_BYPASS_CNTW);
}

/* This function cowwect waw cwk wegistew vawues */
static void wn_dump_cwk_wegistews(stwuct cwk_state_wegistews_and_bypass *wegs_and_bypass,
		stwuct cwk_mgw *cwk_mgw_base, stwuct cwk_wog_info *wog_info)
{
	stwuct wn_cwk_intewnaw intewnaw = {0};
	chaw *bypass_cwks[5] = {"0x0 DFS", "0x1 WEFCWK", "0x2 EWWOW", "0x3 400 FCH", "0x4 600 FCH"};
	unsigned int chaws_pwinted = 0;
	unsigned int wemaining_buffew = wog_info->bufSize;

	wn_dump_cwk_wegistews_intewnaw(&intewnaw, cwk_mgw_base);

	wegs_and_bypass->dcfcwk = intewnaw.CWK1_CWK3_CUWWENT_CNT / 10;
	wegs_and_bypass->dcf_deep_sweep_dividew = intewnaw.CWK1_CWK3_DS_CNTW / 10;
	wegs_and_bypass->dcf_deep_sweep_awwow = intewnaw.CWK1_CWK3_AWWOW_DS;
	wegs_and_bypass->dpwefcwk = intewnaw.CWK1_CWK2_CUWWENT_CNT / 10;
	wegs_and_bypass->dispcwk = intewnaw.CWK1_CWK0_CUWWENT_CNT / 10;
	wegs_and_bypass->dppcwk = intewnaw.CWK1_CWK1_CUWWENT_CNT / 10;

	wegs_and_bypass->dppcwk_bypass = intewnaw.CWK1_CWK1_BYPASS_CNTW & 0x0007;
	if (wegs_and_bypass->dppcwk_bypass < 0 || wegs_and_bypass->dppcwk_bypass > 4)
		wegs_and_bypass->dppcwk_bypass = 0;
	wegs_and_bypass->dcfcwk_bypass = intewnaw.CWK1_CWK3_BYPASS_CNTW & 0x0007;
	if (wegs_and_bypass->dcfcwk_bypass < 0 || wegs_and_bypass->dcfcwk_bypass > 4)
		wegs_and_bypass->dcfcwk_bypass = 0;
	wegs_and_bypass->dispcwk_bypass = intewnaw.CWK1_CWK0_BYPASS_CNTW & 0x0007;
	if (wegs_and_bypass->dispcwk_bypass < 0 || wegs_and_bypass->dispcwk_bypass > 4)
		wegs_and_bypass->dispcwk_bypass = 0;
	wegs_and_bypass->dpwefcwk_bypass = intewnaw.CWK1_CWK2_BYPASS_CNTW & 0x0007;
	if (wegs_and_bypass->dpwefcwk_bypass < 0 || wegs_and_bypass->dpwefcwk_bypass > 4)
		wegs_and_bypass->dpwefcwk_bypass = 0;

	if (wog_info->enabwed) {
		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "cwk_type,cwk_vawue,deepsweep_cntw,deepsweep_awwow,bypass\n");
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "dcfcwk,%d,%d,%d,%s\n",
			wegs_and_bypass->dcfcwk,
			wegs_and_bypass->dcf_deep_sweep_dividew,
			wegs_and_bypass->dcf_deep_sweep_awwow,
			bypass_cwks[(int) wegs_and_bypass->dcfcwk_bypass]);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "dpwefcwk,%d,N/A,N/A,%s\n",
			wegs_and_bypass->dpwefcwk,
			bypass_cwks[(int) wegs_and_bypass->dpwefcwk_bypass]);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "dispcwk,%d,N/A,N/A,%s\n",
			wegs_and_bypass->dispcwk,
			bypass_cwks[(int) wegs_and_bypass->dispcwk_bypass]);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		//spwit
		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "SPWIT\n");
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		// WEGISTEW VAWUES
		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "weg_name,vawue,cwk_type\n");
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK3_CUWWENT_CNT,%d,dcfcwk\n",
				intewnaw.CWK1_CWK3_CUWWENT_CNT);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK3_DS_CNTW,%d,dcf_deep_sweep_dividew\n",
					intewnaw.CWK1_CWK3_DS_CNTW);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK3_AWWOW_DS,%d,dcf_deep_sweep_awwow\n",
					intewnaw.CWK1_CWK3_AWWOW_DS);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK2_CUWWENT_CNT,%d,dpwefcwk\n",
					intewnaw.CWK1_CWK2_CUWWENT_CNT);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK0_CUWWENT_CNT,%d,dispcwk\n",
					intewnaw.CWK1_CWK0_CUWWENT_CNT);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK1_CUWWENT_CNT,%d,dppcwk\n",
					intewnaw.CWK1_CWK1_CUWWENT_CNT);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK3_BYPASS_CNTW,%d,dcfcwk_bypass\n",
					intewnaw.CWK1_CWK3_BYPASS_CNTW);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK2_BYPASS_CNTW,%d,dpwefcwk_bypass\n",
					intewnaw.CWK1_CWK2_BYPASS_CNTW);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK0_BYPASS_CNTW,%d,dispcwk_bypass\n",
					intewnaw.CWK1_CWK0_BYPASS_CNTW);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;

		chaws_pwinted = snpwintf_count(wog_info->pBuf, wemaining_buffew, "CWK1_CWK1_BYPASS_CNTW,%d,dppcwk_bypass\n",
					intewnaw.CWK1_CWK1_BYPASS_CNTW);
		wemaining_buffew -= chaws_pwinted;
		*wog_info->sum_chaws_pwinted += chaws_pwinted;
		wog_info->pBuf += chaws_pwinted;
	}
}

static void wn_enabwe_pme_wa(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

	wn_vbios_smu_enabwe_pme_wa(cwk_mgw);
}

static void wn_init_cwocks(stwuct cwk_mgw *cwk_mgw)
{
	memset(&(cwk_mgw->cwks), 0, sizeof(stwuct dc_cwocks));
	// Assumption is that boot state awways suppowts pstate
	cwk_mgw->cwks.p_state_change_suppowt = twue;
	cwk_mgw->cwks.pwev_p_state_change_suppowt = twue;
	cwk_mgw->cwks.pww_state = DCN_PWW_STATE_UNKNOWN;
}

static void buiwd_watewmawk_wanges(stwuct cwk_bw_pawams *bw_pawams, stwuct pp_smu_wm_wange_sets *wanges)
{
	int i, num_vawid_sets;

	num_vawid_sets = 0;

	fow (i = 0; i < WM_SET_COUNT; i++) {
		/* skip empty entwies, the smu awway has no howes*/
		if (!bw_pawams->wm_tabwe.entwies[i].vawid)
			continue;

		wanges->weadew_wm_sets[num_vawid_sets].wm_inst = bw_pawams->wm_tabwe.entwies[i].wm_inst;
		wanges->weadew_wm_sets[num_vawid_sets].wm_type = bw_pawams->wm_tabwe.entwies[i].wm_type;
		/* We wiww not sewect WM based on fcwk, so weave it as unconstwained */
		wanges->weadew_wm_sets[num_vawid_sets].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
		wanges->weadew_wm_sets[num_vawid_sets].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
		/* dcfcwk wiw be used to sewect WM*/

		if (wanges->weadew_wm_sets[num_vawid_sets].wm_type == WM_TYPE_PSTATE_CHG) {
			if (i == 0)
				wanges->weadew_wm_sets[num_vawid_sets].min_dwain_cwk_mhz = 0;
			ewse {
				/* add 1 to make it non-ovewwapping with next wvw */
				wanges->weadew_wm_sets[num_vawid_sets].min_dwain_cwk_mhz = bw_pawams->cwk_tabwe.entwies[i - 1].dcfcwk_mhz + 1;
			}
			wanges->weadew_wm_sets[num_vawid_sets].max_dwain_cwk_mhz = bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz;

		} ewse {
			/* unconstwained fow memowy wetwaining */
			wanges->weadew_wm_sets[num_vawid_sets].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
			wanges->weadew_wm_sets[num_vawid_sets].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;

			/* Modify pwevious watewmawk wange to covew up to max */
			wanges->weadew_wm_sets[num_vawid_sets - 1].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
		}
		num_vawid_sets++;
	}

	ASSEWT(num_vawid_sets != 0); /* Must have at weast one set of vawid watewmawks */
	wanges->num_weadew_wm_sets = num_vawid_sets;

	/* modify the min and max to make suwe we covew the whowe wange*/
	wanges->weadew_wm_sets[0].min_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges->weadew_wm_sets[0].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges->weadew_wm_sets[wanges->num_weadew_wm_sets - 1].max_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
	wanges->weadew_wm_sets[wanges->num_weadew_wm_sets - 1].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;

	/* This is fow wwiteback onwy, does not mattew cuwwentwy as no wwiteback suppowt*/
	wanges->num_wwitew_wm_sets = 1;
	wanges->wwitew_wm_sets[0].wm_inst = WM_A;
	wanges->wwitew_wm_sets[0].min_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges->wwitew_wm_sets[0].max_fiww_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;
	wanges->wwitew_wm_sets[0].min_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MIN;
	wanges->wwitew_wm_sets[0].max_dwain_cwk_mhz = PP_SMU_WM_SET_WANGE_CWK_UNCONSTWAINED_MAX;

}

static void wn_notify_wm_wanges(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct dc_debug_options *debug = &cwk_mgw_base->ctx->dc->debug;
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct pp_smu_funcs *pp_smu = cwk_mgw->pp_smu;

	if (!debug->disabwe_ppwib_wm_wange) {
		buiwd_watewmawk_wanges(cwk_mgw_base->bw_pawams, &cwk_mgw_base->wanges);

		/* Notify PP Wib/SMU which Watewmawks to use fow which cwock wanges */
		if (pp_smu && pp_smu->wn_funcs.set_wm_wanges)
			pp_smu->wn_funcs.set_wm_wanges(&pp_smu->wn_funcs.pp_smu, &cwk_mgw_base->wanges);
	}

}

static boow wn_awe_cwock_states_equaw(stwuct dc_cwocks *a,
		stwuct dc_cwocks *b)
{
	if (a->dispcwk_khz != b->dispcwk_khz)
		wetuwn fawse;
	ewse if (a->dppcwk_khz != b->dppcwk_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_khz != b->dcfcwk_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_deep_sweep_khz != b->dcfcwk_deep_sweep_khz)
		wetuwn fawse;

	wetuwn twue;
}


/* Notify cwk_mgw of a change in wink wate, update phycwk fwequency if necessawy */
static void wn_notify_wink_wate_change(stwuct cwk_mgw *cwk_mgw_base, stwuct dc_wink *wink)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	unsigned int i, max_phycwk_weq = 0;

	cwk_mgw->cuw_phycwk_weq_tabwe[wink->wink_index] = wink->cuw_wink_settings.wink_wate * WINK_WATE_WEF_FWEQ_IN_KHZ;

	fow (i = 0; i < MAX_PIPES * 2; i++) {
		if (cwk_mgw->cuw_phycwk_weq_tabwe[i] > max_phycwk_weq)
			max_phycwk_weq = cwk_mgw->cuw_phycwk_weq_tabwe[i];
	}

	if (max_phycwk_weq != cwk_mgw_base->cwks.phycwk_khz) {
		cwk_mgw_base->cwks.phycwk_khz = max_phycwk_weq;
		wn_vbios_smu_set_phycwk(cwk_mgw, cwk_mgw_base->cwks.phycwk_khz);
	}
}

static stwuct cwk_mgw_funcs dcn21_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = wn_update_cwocks,
	.init_cwocks = wn_init_cwocks,
	.enabwe_pme_wa = wn_enabwe_pme_wa,
	.awe_cwock_states_equaw = wn_awe_cwock_states_equaw,
	.set_wow_powew_state = wn_set_wow_powew_state,
	.notify_wm_wanges = wn_notify_wm_wanges,
	.notify_wink_wate_change = wn_notify_wink_wate_change,
};

static stwuct cwk_bw_pawams wn_bw_pawams = {
	.vwam_type = Ddw4MemType,
	.num_channews = 1,
	.cwk_tabwe = {
		.entwies = {
			{
				.vowtage = 0,
				.dcfcwk_mhz = 400,
				.fcwk_mhz = 400,
				.memcwk_mhz = 800,
				.soccwk_mhz = 0,
			},
			{
				.vowtage = 0,
				.dcfcwk_mhz = 483,
				.fcwk_mhz = 800,
				.memcwk_mhz = 1600,
				.soccwk_mhz = 0,
			},
			{
				.vowtage = 0,
				.dcfcwk_mhz = 602,
				.fcwk_mhz = 1067,
				.memcwk_mhz = 1067,
				.soccwk_mhz = 0,
			},
			{
				.vowtage = 0,
				.dcfcwk_mhz = 738,
				.fcwk_mhz = 1333,
				.memcwk_mhz = 1600,
				.soccwk_mhz = 0,
			},
		},

		.num_entwies = 4,
	},

};

static unsigned int find_soccwk_fow_vowtage(stwuct dpm_cwocks *cwock_tabwe, unsigned int vowtage)
{
	int i;

	fow (i = 0; i < PP_SMU_NUM_SOCCWK_DPM_WEVEWS; i++) {
		if (cwock_tabwe->SocCwocks[i].Vow == vowtage)
			wetuwn cwock_tabwe->SocCwocks[i].Fweq;
	}

	ASSEWT(0);
	wetuwn 0;
}

static unsigned int find_dcfcwk_fow_vowtage(stwuct dpm_cwocks *cwock_tabwe, unsigned int vowtage)
{
	int i;

	fow (i = 0; i < PP_SMU_NUM_DCFCWK_DPM_WEVEWS; i++) {
		if (cwock_tabwe->DcfCwocks[i].Vow == vowtage)
			wetuwn cwock_tabwe->DcfCwocks[i].Fweq;
	}

	ASSEWT(0);
	wetuwn 0;
}

static void wn_cwk_mgw_hewpew_popuwate_bw_pawams(stwuct cwk_bw_pawams *bw_pawams, stwuct dpm_cwocks *cwock_tabwe, stwuct integwated_info *bios_info)
{
	int i, j = 0;

	j = -1;

	ASSEWT(PP_SMU_NUM_FCWK_DPM_WEVEWS <= MAX_NUM_DPM_WVW);

	/* Find wowest DPM, FCWK is fiwwed in wevewse owdew*/

	fow (i = PP_SMU_NUM_FCWK_DPM_WEVEWS - 1; i >= 0; i--) {
		if (cwock_tabwe->FCwocks[i].Fweq != 0 && cwock_tabwe->FCwocks[i].Vow != 0) {
			j = i;
			bweak;
		}
	}

	if (j == -1) {
		/* cwock tabwe is aww 0s, just use ouw own hawdcode */
		ASSEWT(0);
		wetuwn;
	}

	bw_pawams->cwk_tabwe.num_entwies = j + 1;

	fow (i = 0; i < bw_pawams->cwk_tabwe.num_entwies; i++, j--) {
		bw_pawams->cwk_tabwe.entwies[i].fcwk_mhz = cwock_tabwe->FCwocks[j].Fweq;
		bw_pawams->cwk_tabwe.entwies[i].memcwk_mhz = cwock_tabwe->MemCwocks[j].Fweq;
		bw_pawams->cwk_tabwe.entwies[i].vowtage = cwock_tabwe->FCwocks[j].Vow;
		bw_pawams->cwk_tabwe.entwies[i].dcfcwk_mhz = find_dcfcwk_fow_vowtage(cwock_tabwe, cwock_tabwe->FCwocks[j].Vow);
		bw_pawams->cwk_tabwe.entwies[i].soccwk_mhz = find_soccwk_fow_vowtage(cwock_tabwe,
									bw_pawams->cwk_tabwe.entwies[i].vowtage);
	}

	bw_pawams->vwam_type = bios_info->memowy_type;
	bw_pawams->num_channews = bios_info->ma_channew_numbew;

	fow (i = 0; i < WM_SET_COUNT; i++) {
		bw_pawams->wm_tabwe.entwies[i].wm_inst = i;

		if (i >= bw_pawams->cwk_tabwe.num_entwies) {
			bw_pawams->wm_tabwe.entwies[i].vawid = fawse;
			continue;
		}

		bw_pawams->wm_tabwe.entwies[i].wm_type = WM_TYPE_PSTATE_CHG;
		bw_pawams->wm_tabwe.entwies[i].vawid = twue;
	}

	if (bw_pawams->vwam_type == WpDdw4MemType) {
		/*
		 * WM set D wiww be we-puwposed fow memowy wetwaining
		 */
		DC_FP_STAWT();
		dcn21_cwk_mgw_set_bw_pawams_wm_tabwe(bw_pawams);
		DC_FP_END();
	}
}

void wn_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg)
{
	stwuct dc_debug_options *debug = &ctx->dc->debug;
	stwuct dpm_cwocks cwock_tabwe = { 0 };
	enum pp_smu_status status = 0;
	int is_gween_sawdine = 0;
	stwuct cwk_wog_info wog_info = {0};

#if defined(CONFIG_DWM_AMD_DC_FP)
	is_gween_sawdine = ASICWEV_IS_GWEEN_SAWDINE(ctx->asic_id.hw_intewnaw_wev);
#endif

	cwk_mgw->base.ctx = ctx;
	cwk_mgw->base.funcs = &dcn21_funcs;

	cwk_mgw->pp_smu = pp_smu;

	cwk_mgw->dccg = dccg;
	cwk_mgw->dfs_bypass_disp_cwk = 0;

	cwk_mgw->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->dpwefcwk_ss_dividew = 1000;
	cwk_mgw->ss_on_dpwefcwk = fawse;
	cwk_mgw->dfs_wef_fweq_khz = 48000;

	cwk_mgw->smu_vew = wn_vbios_smu_get_smu_vewsion(cwk_mgw);

	cwk_mgw->pewiodic_wetwaining_disabwed = wn_vbios_smu_is_pewiodic_wetwaining_disabwed(cwk_mgw);

	/* SMU Vewsion 55.51.0 and up no wongew have an issue
	 * that needs to wimit minimum dispcwk */
	if (cwk_mgw->smu_vew >= SMU_VEW_55_51_0)
		debug->min_disp_cwk_khz = 0;

	/* TODO: Check we get what we expect duwing bwingup */
	cwk_mgw->base.dentist_vco_fweq_khz = get_vco_fwequency_fwom_weg(cwk_mgw);

	/* in case we don't get a vawue fwom the wegistew, use defauwt */
	if (cwk_mgw->base.dentist_vco_fweq_khz == 0)
		cwk_mgw->base.dentist_vco_fweq_khz = 3600000;

	if (ctx->dc_bios->integwated_info->memowy_type == WpDdw4MemType) {
		if (cwk_mgw->pewiodic_wetwaining_disabwed) {
			wn_bw_pawams.wm_tabwe = wpddw4_wm_tabwe_with_disabwed_ppt;
		} ewse {
			if (is_gween_sawdine)
				wn_bw_pawams.wm_tabwe = wpddw4_wm_tabwe_gs;
			ewse
				wn_bw_pawams.wm_tabwe = wpddw4_wm_tabwe_wn;
		}
	} ewse {
		if (is_gween_sawdine)
			wn_bw_pawams.wm_tabwe = ddw4_wm_tabwe_gs;
		ewse {
			if (ctx->dc->config.is_singwe_wank_dimm)
				wn_bw_pawams.wm_tabwe = ddw4_1W_wm_tabwe_wn;
			ewse
				wn_bw_pawams.wm_tabwe = ddw4_wm_tabwe_wn;
		}
	}
	/* Saved cwocks configuwed at boot fow debug puwposes */
	wn_dump_cwk_wegistews(&cwk_mgw->base.boot_snapshot, &cwk_mgw->base, &wog_info);

	cwk_mgw->base.dpwefcwk_khz = 600000;
	dce_cwock_wead_ss_info(cwk_mgw);


	cwk_mgw->base.bw_pawams = &wn_bw_pawams;

	if (pp_smu && pp_smu->wn_funcs.get_dpm_cwock_tabwe) {
		status = pp_smu->wn_funcs.get_dpm_cwock_tabwe(&pp_smu->wn_funcs.pp_smu, &cwock_tabwe);

		if (status == PP_SMU_WESUWT_OK &&
		    ctx->dc_bios && ctx->dc_bios->integwated_info) {
			wn_cwk_mgw_hewpew_popuwate_bw_pawams (cwk_mgw->base.bw_pawams, &cwock_tabwe, ctx->dc_bios->integwated_info);
			/* tweat memowy config as singwe channew if memowy is asymmetwics. */
			if (ctx->dc->config.is_asymmetwic_memowy)
				cwk_mgw->base.bw_pawams->num_channews = 1;
		}
	}

	/* enabwe powewfeatuwes when dispwaycount goes to 0 */
	if (cwk_mgw->smu_vew >= 0x00371500)
		wn_vbios_smu_enabwe_48mhz_tmdp_wefcwk_pwwdwn(cwk_mgw, !debug->disabwe_48mhz_pwwdwn);
}

