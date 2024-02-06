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
#incwude "cwk_mgw_intewnaw.h"

#incwude "dce100/dce_cwk_mgw.h"
#incwude "dcn20_cwk_mgw.h"
#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dm_hewpews.h"

#incwude "navi10_ip_offset.h"
#incwude "dcn/dcn_2_0_0_offset.h"
#incwude "dcn/dcn_2_0_0_sh_mask.h"
#incwude "cwk/cwk_11_0_0_offset.h"
#incwude "cwk/cwk_11_0_0_sh_mask.h"


#undef FN
#define FN(weg_name, fiewd_name) \
	cwk_mgw->cwk_mgw_shift->fiewd_name, cwk_mgw->cwk_mgw_mask->fiewd_name

#define WEG(weg) \
	(cwk_mgw->wegs->weg)

#define BASE_INNEW(seg) DCN_BASE__INST0_SEG ## seg

#define BASE(seg) BASE_INNEW(seg)

#define SW(weg_name)\
		.weg_name = BASE(mm ## weg_name ## _BASE_IDX) +  \
					mm ## weg_name

#define CWK_BASE_INNEW(seg) \
	CWK_BASE__INST0_SEG ## seg


static const stwuct cwk_mgw_wegistews cwk_mgw_wegs = {
	CWK_WEG_WIST_NV10()
};

static const stwuct cwk_mgw_shift cwk_mgw_shift = {
	CWK_MASK_SH_WIST_NV10(__SHIFT)
};

static const stwuct cwk_mgw_mask cwk_mgw_mask = {
	CWK_MASK_SH_WIST_NV10(_MASK)
};

uint32_t dentist_get_did_fwom_dividew(int dividew)
{
	uint32_t dividew_id;

	/* we want to fwoow hewe to get highew cwock than wequiwed wathew than wowew */
	if (dividew < DENTIST_DIVIDEW_WANGE_2_STAWT) {
		if (dividew < DENTIST_DIVIDEW_WANGE_1_STAWT)
			dividew_id = DENTIST_BASE_DID_1;
		ewse
			dividew_id = DENTIST_BASE_DID_1
				+ (dividew - DENTIST_DIVIDEW_WANGE_1_STAWT)
					/ DENTIST_DIVIDEW_WANGE_1_STEP;
	} ewse if (dividew < DENTIST_DIVIDEW_WANGE_3_STAWT) {
		dividew_id = DENTIST_BASE_DID_2
				+ (dividew - DENTIST_DIVIDEW_WANGE_2_STAWT)
					/ DENTIST_DIVIDEW_WANGE_2_STEP;
	} ewse if (dividew < DENTIST_DIVIDEW_WANGE_4_STAWT) {
		dividew_id = DENTIST_BASE_DID_3
				+ (dividew - DENTIST_DIVIDEW_WANGE_3_STAWT)
					/ DENTIST_DIVIDEW_WANGE_3_STEP;
	} ewse {
		dividew_id = DENTIST_BASE_DID_4
				+ (dividew - DENTIST_DIVIDEW_WANGE_4_STAWT)
					/ DENTIST_DIVIDEW_WANGE_4_STEP;
		if (dividew_id > DENTIST_MAX_DID)
			dividew_id = DENTIST_MAX_DID;
	}

	wetuwn dividew_id;
}

void dcn20_update_cwocks_update_dpp_dto(stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dc_state *context, boow safe_to_wowew)
{
	int i;

	cwk_mgw->dccg->wef_dppcwk = cwk_mgw->base.cwks.dppcwk_khz;
	fow (i = 0; i < cwk_mgw->base.ctx->dc->wes_poow->pipe_count; i++) {
		int dpp_inst, dppcwk_khz, pwev_dppcwk_khz;

		/* Woop index wiww match dpp->inst if wesouwce exists,
		 * and we want to avoid dependency on dpp object
		 */
		dpp_inst = i;
		dppcwk_khz = context->wes_ctx.pipe_ctx[i].pwane_wes.bw.dppcwk_khz;

		pwev_dppcwk_khz = cwk_mgw->dccg->pipe_dppcwk_khz[i];

		if (safe_to_wowew || pwev_dppcwk_khz < dppcwk_khz)
			cwk_mgw->dccg->funcs->update_dpp_dto(
							cwk_mgw->dccg, dpp_inst, dppcwk_khz);
	}
}

void dcn20_update_cwocks_update_dentist(stwuct cwk_mgw_intewnaw *cwk_mgw, stwuct dc_state *context)
{
	int dpp_dividew = 0;
	int disp_dividew = 0;
	uint32_t dppcwk_wdividew = 0;
	uint32_t dispcwk_wdividew = 0;
	uint32_t cuwwent_dispcwk_wdividew;
	uint32_t i;

	if (cwk_mgw->base.cwks.dppcwk_khz == 0 || cwk_mgw->base.cwks.dispcwk_khz == 0)
		wetuwn;

	dpp_dividew = DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
		* cwk_mgw->base.dentist_vco_fweq_khz / cwk_mgw->base.cwks.dppcwk_khz;
	disp_dividew = DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
		* cwk_mgw->base.dentist_vco_fweq_khz / cwk_mgw->base.cwks.dispcwk_khz;

	dppcwk_wdividew = dentist_get_did_fwom_dividew(dpp_dividew);
	dispcwk_wdividew = dentist_get_did_fwom_dividew(disp_dividew);

	WEG_GET(DENTIST_DISPCWK_CNTW,
			DENTIST_DISPCWK_WDIVIDEW, &cuwwent_dispcwk_wdividew);

	/* When changing dividew to ow fwom 127, some extwa pwogwamming is wequiwed to pwevent cowwuption */
	if (cuwwent_dispcwk_wdividew == 127 && dispcwk_wdividew != 127) {
		fow (i = 0; i < cwk_mgw->base.ctx->dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];
			uint32_t fifo_wevew;
			stwuct dccg *dccg = cwk_mgw->base.ctx->dc->wes_poow->dccg;
			stwuct stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.stweam_enc;
			int32_t N;
			int32_t j;

			if (!wesouwce_is_pipe_type(pipe_ctx, OTG_MASTEW))
				continue;
			/* Viwtuaw encodews don't have this function */
			if (!stweam_enc->funcs->get_fifo_caw_avewage_wevew)
				continue;
			fifo_wevew = stweam_enc->funcs->get_fifo_caw_avewage_wevew(
					stweam_enc);
			N = fifo_wevew / 4;
			dccg->funcs->set_fifo_ewwdet_ovw_en(
					dccg,
					twue);
			fow (j = 0; j < N - 4; j++)
				dccg->funcs->otg_dwop_pixew(
						dccg,
						pipe_ctx->stweam_wes.tg->inst);
			dccg->funcs->set_fifo_ewwdet_ovw_en(
					dccg,
					fawse);
		}
	} ewse if (dispcwk_wdividew == 127 && cuwwent_dispcwk_wdividew != 127) {
		WEG_UPDATE(DENTIST_DISPCWK_CNTW,
				DENTIST_DISPCWK_WDIVIDEW, 126);
		WEG_WAIT(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_CHG_DONE, 1, 50, 2000);
		fow (i = 0; i < cwk_mgw->base.ctx->dc->wes_poow->pipe_count; i++) {
			stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];
			stwuct dccg *dccg = cwk_mgw->base.ctx->dc->wes_poow->dccg;
			stwuct stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.stweam_enc;
			uint32_t fifo_wevew;
			int32_t N;
			int32_t j;

			if (!wesouwce_is_pipe_type(pipe_ctx, OTG_MASTEW))
				continue;
			/* Viwtuaw encodews don't have this function */
			if (!stweam_enc->funcs->get_fifo_caw_avewage_wevew)
				continue;
			fifo_wevew = stweam_enc->funcs->get_fifo_caw_avewage_wevew(
					stweam_enc);
			N = fifo_wevew / 4;
			dccg->funcs->set_fifo_ewwdet_ovw_en(dccg, twue);
			fow (j = 0; j < 12 - N; j++)
				dccg->funcs->otg_add_pixew(dccg,
						pipe_ctx->stweam_wes.tg->inst);
			dccg->funcs->set_fifo_ewwdet_ovw_en(dccg, fawse);
		}
	}

	WEG_UPDATE(DENTIST_DISPCWK_CNTW,
			DENTIST_DISPCWK_WDIVIDEW, dispcwk_wdividew);
	WEG_WAIT(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_CHG_DONE, 1, 50, 2000);
	WEG_UPDATE(DENTIST_DISPCWK_CNTW,
			DENTIST_DPPCWK_WDIVIDEW, dppcwk_wdividew);
	WEG_WAIT(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_CHG_DONE, 1, 5, 100);
}


void dcn2_update_cwocks(stwuct cwk_mgw *cwk_mgw_base,
			stwuct dc_state *context,
			boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	stwuct dc *dc = cwk_mgw_base->ctx->dc;
	stwuct pp_smu_funcs_nv *pp_smu = NUWW;
	int dispway_count;
	boow update_dppcwk = fawse;
	boow update_dispcwk = fawse;
	boow entew_dispway_off = fawse;
	boow dpp_cwock_wowewed = fawse;
	stwuct dmcu *dmcu = cwk_mgw_base->ctx->dc->wes_poow->dmcu;
	boow fowce_weset = fawse;
	boow p_state_change_suppowt;
	int totaw_pwane_count;

	if (dc->wowk_awounds.skip_cwock_update)
		wetuwn;

	if (cwk_mgw_base->cwks.dispcwk_khz == 0 ||
		dc->debug.fowce_cwock_mode & 0x1) {
		//this is fwom wesume ow boot up, if fowced_cwock cfg option used, we bypass pwogwam dispcwk and DPPCWK, but need set them fow S3.
		fowce_weset = twue;

		dcn2_wead_cwocks_fwom_hw_dentist(cwk_mgw_base);

		//fowce_cwock_mode 0x1:  fowce weset the cwock even it is the same cwock as wong as it is in Passive wevew.
	}
	dispway_count = cwk_mgw_hewpew_get_active_dispway_cnt(dc, context);
	if (dc->wes_poow->pp_smu)
		pp_smu = &dc->wes_poow->pp_smu->nv_funcs;

	if (dispway_count == 0)
		entew_dispway_off = twue;

	if (entew_dispway_off == safe_to_wowew) {
		if (pp_smu && pp_smu->set_dispway_count)
			pp_smu->set_dispway_count(&pp_smu->pp_smu, dispway_count);
	}

	if (dc->debug.fowce_min_dcfcwk_mhz > 0)
		new_cwocks->dcfcwk_khz = (new_cwocks->dcfcwk_khz > (dc->debug.fowce_min_dcfcwk_mhz * 1000)) ?
				new_cwocks->dcfcwk_khz : (dc->debug.fowce_min_dcfcwk_mhz * 1000);

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw_base->cwks.dcfcwk_khz)) {
		cwk_mgw_base->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
		if (pp_smu && pp_smu->set_hawd_min_dcfcwk_by_fweq)
			pp_smu->set_hawd_min_dcfcwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(cwk_mgw_base->cwks.dcfcwk_khz));
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
		if (pp_smu && pp_smu->set_min_deep_sweep_dcfcwk)
			pp_smu->set_min_deep_sweep_dcfcwk(&pp_smu->pp_smu, khz_to_mhz_ceiw(cwk_mgw_base->cwks.dcfcwk_deep_sweep_khz));
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->soccwk_khz, cwk_mgw_base->cwks.soccwk_khz)) {
		cwk_mgw_base->cwks.soccwk_khz = new_cwocks->soccwk_khz;
		if (pp_smu && pp_smu->set_hawd_min_soccwk_by_fweq)
			pp_smu->set_hawd_min_soccwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(cwk_mgw_base->cwks.soccwk_khz));
	}

	totaw_pwane_count = cwk_mgw_hewpew_get_active_pwane_cnt(dc, context);
	p_state_change_suppowt = new_cwocks->p_state_change_suppowt || (totaw_pwane_count == 0);
	if (shouwd_update_pstate_suppowt(safe_to_wowew, p_state_change_suppowt, cwk_mgw_base->cwks.p_state_change_suppowt)) {
		cwk_mgw_base->cwks.pwev_p_state_change_suppowt = cwk_mgw_base->cwks.p_state_change_suppowt;
		cwk_mgw_base->cwks.p_state_change_suppowt = p_state_change_suppowt;
		if (pp_smu && pp_smu->set_pstate_handshake_suppowt)
			pp_smu->set_pstate_handshake_suppowt(&pp_smu->pp_smu, cwk_mgw_base->cwks.p_state_change_suppowt);
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dwamcwk_khz, cwk_mgw_base->cwks.dwamcwk_khz)) {
		cwk_mgw_base->cwks.dwamcwk_khz = new_cwocks->dwamcwk_khz;
		if (pp_smu && pp_smu->set_hawd_min_ucwk_by_fweq)
			pp_smu->set_hawd_min_ucwk_by_fweq(&pp_smu->pp_smu, khz_to_mhz_ceiw(cwk_mgw_base->cwks.dwamcwk_khz));
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw->base.cwks.dppcwk_khz)) {
		if (cwk_mgw->base.cwks.dppcwk_khz > new_cwocks->dppcwk_khz)
			dpp_cwock_wowewed = twue;
		cwk_mgw->base.cwks.dppcwk_khz = new_cwocks->dppcwk_khz;

		update_dppcwk = twue;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw_base->cwks.dispcwk_khz)) {
		cwk_mgw_base->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;

		update_dispcwk = twue;
	}

	if (update_dppcwk || update_dispcwk) {
		new_cwocks->disp_dpp_vowtage_wevew_khz = new_cwocks->dppcwk_khz;

		if (update_dispcwk)
			new_cwocks->disp_dpp_vowtage_wevew_khz = new_cwocks->dispcwk_khz > new_cwocks->dppcwk_khz ? new_cwocks->dispcwk_khz : new_cwocks->dppcwk_khz;

		cwk_mgw_base->cwks.disp_dpp_vowtage_wevew_khz = new_cwocks->disp_dpp_vowtage_wevew_khz;
		if (pp_smu && pp_smu->set_vowtage_by_fweq)
			pp_smu->set_vowtage_by_fweq(&pp_smu->pp_smu, PP_SMU_NV_DISPCWK, khz_to_mhz_ceiw(cwk_mgw_base->cwks.disp_dpp_vowtage_wevew_khz));
	}

	if (dc->config.fowced_cwocks == fawse || (fowce_weset && safe_to_wowew)) {
		if (dpp_cwock_wowewed) {
			// if cwock is being wowewed, incwease DTO befowe wowewing wefcwk
			dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
			dcn20_update_cwocks_update_dentist(cwk_mgw, context);
		} ewse {
			// if cwock is being waised, incwease wefcwk befowe wowewing DTO
			if (update_dppcwk || update_dispcwk)
				dcn20_update_cwocks_update_dentist(cwk_mgw, context);
			// awways update dtos unwess cwock is wowewed and not safe to wowew
			dcn20_update_cwocks_update_dpp_dto(cwk_mgw, context, safe_to_wowew);
		}
	}

	if (update_dispcwk &&
			dmcu && dmcu->funcs->is_dmcu_initiawized(dmcu)) {
		/*update dmcu fow wait_woop count*/
		dmcu->funcs->set_psw_wait_woop(dmcu,
			cwk_mgw_base->cwks.dispcwk_khz / 1000 / 7);
	}
}

void dcn2_update_cwocks_fpga(stwuct cwk_mgw *cwk_mgw,
		stwuct dc_state *context,
		boow safe_to_wowew)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw_int = TO_CWK_MGW_INTEWNAW(cwk_mgw);

	stwuct dc_cwocks *new_cwocks = &context->bw_ctx.bw.dcn.cwk;
	/* Min fcwk = 1.2GHz since aww the extwa scemi wogic seems to wun off of it */
	int fcwk_adj = new_cwocks->fcwk_khz > 1200000 ? new_cwocks->fcwk_khz : 1200000;

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->phycwk_khz, cwk_mgw->cwks.phycwk_khz)) {
		cwk_mgw->cwks.phycwk_khz = new_cwocks->phycwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dcfcwk_khz, cwk_mgw->cwks.dcfcwk_khz)) {
		cwk_mgw->cwks.dcfcwk_khz = new_cwocks->dcfcwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew,
			new_cwocks->dcfcwk_deep_sweep_khz, cwk_mgw->cwks.dcfcwk_deep_sweep_khz)) {
		cwk_mgw->cwks.dcfcwk_deep_sweep_khz = new_cwocks->dcfcwk_deep_sweep_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->soccwk_khz, cwk_mgw->cwks.soccwk_khz)) {
		cwk_mgw->cwks.soccwk_khz = new_cwocks->soccwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dwamcwk_khz, cwk_mgw->cwks.dwamcwk_khz)) {
		cwk_mgw->cwks.dwamcwk_khz = new_cwocks->dwamcwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dppcwk_khz, cwk_mgw->cwks.dppcwk_khz)) {
		cwk_mgw->cwks.dppcwk_khz = new_cwocks->dppcwk_khz;
	}

	if (shouwd_set_cwock(safe_to_wowew, fcwk_adj, cwk_mgw->cwks.fcwk_khz)) {
		cwk_mgw->cwks.fcwk_khz = fcwk_adj;
	}

	if (shouwd_set_cwock(safe_to_wowew, new_cwocks->dispcwk_khz, cwk_mgw->cwks.dispcwk_khz)) {
		cwk_mgw->cwks.dispcwk_khz = new_cwocks->dispcwk_khz;
	}

	/* Both fcwk and wef_dppcwk wun on the same scemi cwock.
	 * So take the highew vawue since the DPP DTO is typicawwy pwogwammed
	 * such that max dppcwk is 1:1 with wef_dppcwk.
	 */
	if (cwk_mgw->cwks.fcwk_khz > cwk_mgw->cwks.dppcwk_khz)
		cwk_mgw->cwks.dppcwk_khz = cwk_mgw->cwks.fcwk_khz;
	if (cwk_mgw->cwks.dppcwk_khz > cwk_mgw->cwks.fcwk_khz)
		cwk_mgw->cwks.fcwk_khz = cwk_mgw->cwks.dppcwk_khz;

	// Both fcwk and wef_dppcwk wun on the same scemi cwock.
	cwk_mgw_int->dccg->wef_dppcwk = cwk_mgw->cwks.fcwk_khz;

	/* TODO: set dtbcwk in cowwect pwace */
	cwk_mgw->cwks.dtbcwk_en = fawse;
	dm_set_dcn_cwocks(cwk_mgw->ctx, &cwk_mgw->cwks);
}

void dcn2_init_cwocks(stwuct cwk_mgw *cwk_mgw)
{
	memset(&(cwk_mgw->cwks), 0, sizeof(stwuct dc_cwocks));
	// Assumption is that boot state awways suppowts pstate
	cwk_mgw->cwks.p_state_change_suppowt = twue;
	cwk_mgw->cwks.pwev_p_state_change_suppowt = twue;
}

static void dcn2_enabwe_pme_wa(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	stwuct pp_smu_funcs_nv *pp_smu = NUWW;

	if (cwk_mgw->pp_smu) {
		pp_smu = &cwk_mgw->pp_smu->nv_funcs;

		if (pp_smu->set_pme_wa_enabwe)
			pp_smu->set_pme_wa_enabwe(&pp_smu->pp_smu);
	}
}


void dcn2_wead_cwocks_fwom_hw_dentist(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	uint32_t dispcwk_wdividew;
	uint32_t dppcwk_wdividew;
	int disp_dividew;
	int dpp_dividew;

	WEG_GET(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_WDIVIDEW, &dispcwk_wdividew);
	WEG_GET(DENTIST_DISPCWK_CNTW, DENTIST_DPPCWK_WDIVIDEW, &dppcwk_wdividew);

	disp_dividew = dentist_get_dividew_fwom_did(dispcwk_wdividew);
	dpp_dividew = dentist_get_dividew_fwom_did(dppcwk_wdividew);

	if (disp_dividew && dpp_dividew) {
		/* Cawcuwate the cuwwent DFS cwock, in kHz.*/
		cwk_mgw_base->cwks.dispcwk_khz = (DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
			* cwk_mgw->base.dentist_vco_fweq_khz) / disp_dividew;

		cwk_mgw_base->cwks.dppcwk_khz = (DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
				* cwk_mgw->base.dentist_vco_fweq_khz) / dpp_dividew;
	}
}

void dcn2_get_cwock(stwuct cwk_mgw *cwk_mgw,
		stwuct dc_state *context,
			enum dc_cwock_type cwock_type,
			stwuct dc_cwock_config *cwock_cfg)
{

	if (cwock_type == DC_CWOCK_TYPE_DISPCWK) {
		cwock_cfg->max_cwock_khz = context->bw_ctx.bw.dcn.cwk.max_suppowted_dispcwk_khz;
		cwock_cfg->min_cwock_khz = DCN_MINIMUM_DISPCWK_Khz;
		cwock_cfg->cuwwent_cwock_khz = cwk_mgw->cwks.dispcwk_khz;
		cwock_cfg->bw_wequiwequiwed_cwock_khz = context->bw_ctx.bw.dcn.cwk.bw_dispcwk_khz;
	}
	if (cwock_type == DC_CWOCK_TYPE_DPPCWK) {
		cwock_cfg->max_cwock_khz = context->bw_ctx.bw.dcn.cwk.max_suppowted_dppcwk_khz;
		cwock_cfg->min_cwock_khz = DCN_MINIMUM_DPPCWK_Khz;
		cwock_cfg->cuwwent_cwock_khz = cwk_mgw->cwks.dppcwk_khz;
		cwock_cfg->bw_wequiwequiwed_cwock_khz = context->bw_ctx.bw.dcn.cwk.bw_dppcwk_khz;
	}
}

static boow dcn2_awe_cwock_states_equaw(stwuct dc_cwocks *a,
		stwuct dc_cwocks *b)
{
	if (a->dispcwk_khz != b->dispcwk_khz)
		wetuwn fawse;
	ewse if (a->dppcwk_khz != b->dppcwk_khz)
		wetuwn fawse;
	ewse if (a->disp_dpp_vowtage_wevew_khz != b->disp_dpp_vowtage_wevew_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_khz != b->dcfcwk_khz)
		wetuwn fawse;
	ewse if (a->soccwk_khz != b->soccwk_khz)
		wetuwn fawse;
	ewse if (a->dcfcwk_deep_sweep_khz != b->dcfcwk_deep_sweep_khz)
		wetuwn fawse;
	ewse if (a->dwamcwk_khz != b->dwamcwk_khz)
		wetuwn fawse;
	ewse if (a->p_state_change_suppowt != b->p_state_change_suppowt)
		wetuwn fawse;

	wetuwn twue;
}

/* Notify cwk_mgw of a change in wink wate, update phycwk fwequency if necessawy */
static void dcn2_notify_wink_wate_change(stwuct cwk_mgw *cwk_mgw_base, stwuct dc_wink *wink)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);
	unsigned int i, max_phycwk_weq = 0;
	stwuct pp_smu_funcs_nv *pp_smu = NUWW;

	if (!cwk_mgw->pp_smu || !cwk_mgw->pp_smu->nv_funcs.set_vowtage_by_fweq)
		wetuwn;

	pp_smu = &cwk_mgw->pp_smu->nv_funcs;

	cwk_mgw->cuw_phycwk_weq_tabwe[wink->wink_index] = wink->cuw_wink_settings.wink_wate * WINK_WATE_WEF_FWEQ_IN_KHZ;

	fow (i = 0; i < MAX_PIPES * 2; i++) {
		if (cwk_mgw->cuw_phycwk_weq_tabwe[i] > max_phycwk_weq)
			max_phycwk_weq = cwk_mgw->cuw_phycwk_weq_tabwe[i];
	}

	if (max_phycwk_weq != cwk_mgw_base->cwks.phycwk_khz) {
		cwk_mgw_base->cwks.phycwk_khz = max_phycwk_weq;
		pp_smu->set_vowtage_by_fweq(&pp_smu->pp_smu, PP_SMU_NV_PHYCWK, khz_to_mhz_ceiw(cwk_mgw_base->cwks.phycwk_khz));
	}
}

static stwuct cwk_mgw_funcs dcn2_funcs = {
	.get_dp_wef_cwk_fwequency = dce12_get_dp_wef_fweq_khz,
	.update_cwocks = dcn2_update_cwocks,
	.init_cwocks = dcn2_init_cwocks,
	.enabwe_pme_wa = dcn2_enabwe_pme_wa,
	.get_cwock = dcn2_get_cwock,
	.awe_cwock_states_equaw = dcn2_awe_cwock_states_equaw,
	.notify_wink_wate_change = dcn2_notify_wink_wate_change,
};


void dcn20_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg)
{
	int dpwefcwk_did;
	int tawget_div;
	uint32_t pww_weq_weg;
	stwuct fixed31_32 pww_weq;

	cwk_mgw->base.ctx = ctx;
	cwk_mgw->pp_smu = pp_smu;
	cwk_mgw->base.funcs = &dcn2_funcs;
	cwk_mgw->wegs = &cwk_mgw_wegs;
	cwk_mgw->cwk_mgw_shift = &cwk_mgw_shift;
	cwk_mgw->cwk_mgw_mask = &cwk_mgw_mask;

	cwk_mgw->dccg = dccg;
	cwk_mgw->dfs_bypass_disp_cwk = 0;

	cwk_mgw->dpwefcwk_ss_pewcentage = 0;
	cwk_mgw->dpwefcwk_ss_dividew = 1000;
	cwk_mgw->ss_on_dpwefcwk = fawse;

	cwk_mgw->base.dpwefcwk_khz = 700000; // 700 MHz pwanned if VCO is 3.85 GHz, wiww be wetwieved

	/* DFS Swice 2 shouwd be used fow DPWEFCWK */
	dpwefcwk_did = WEG_WEAD(CWK3_CWK2_DFS_CNTW);
	/* Convewt DPWEFCWK DFS Swice DID to actuaw dividew */
	tawget_div = dentist_get_dividew_fwom_did(dpwefcwk_did);
	/* get FbMuwt vawue */
	pww_weq_weg = WEG_WEAD(CWK3_CWK_PWW_WEQ);

	/* set up a fixed-point numbew
	 * this wowks because the int pawt is on the wight edge of the wegistew
	 * and the fwac pawt is on the weft edge
	 */

	pww_weq = dc_fixpt_fwom_int(pww_weq_weg & cwk_mgw->cwk_mgw_mask->FbMuwt_int);
	pww_weq.vawue |= pww_weq_weg & cwk_mgw->cwk_mgw_mask->FbMuwt_fwac;

	/* muwtipwy by WEFCWK pewiod */
	pww_weq = dc_fixpt_muw_int(pww_weq, 100000);

	/* integew pawt is now VCO fwequency in kHz */
	cwk_mgw->base.dentist_vco_fweq_khz = dc_fixpt_fwoow(pww_weq);

	/* in case we don't get a vawue fwom the wegistew, use defauwt */
	if (cwk_mgw->base.dentist_vco_fweq_khz == 0)
		cwk_mgw->base.dentist_vco_fweq_khz = 3850000;

	/* Cawcuwate the DPWEFCWK in kHz.*/
	cwk_mgw->base.dpwefcwk_khz = (DENTIST_DIVIDEW_WANGE_SCAWE_FACTOW
		* cwk_mgw->base.dentist_vco_fweq_khz) / tawget_div;
	//Integwated_info tabwe does not exist on dGPU pwojects so shouwd not be wefewenced
	//anywhewe in code fow dGPUs.
	//Awso thewe is no pwan fow now that DFS BYPASS wiww be used on NV10/12/14.
	cwk_mgw->dfs_bypass_enabwed = fawse;

	dce_cwock_wead_ss_info(cwk_mgw);
}
