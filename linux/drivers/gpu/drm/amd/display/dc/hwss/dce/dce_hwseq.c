/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude "dce_hwseq.h"
#incwude "weg_hewpew.h"
#incwude "hw_sequencew_pwivate.h"
#incwude "cowe_types.h"

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

void dce_enabwe_fe_cwock(stwuct dce_hwseq *hws,
		unsigned int fe_inst, boow enabwe)
{
	WEG_UPDATE(DCFE_CWOCK_CONTWOW[fe_inst],
			DCFE_CWOCK_ENABWE, enabwe);
}

void dce_pipe_contwow_wock(stwuct dc *dc,
		stwuct pipe_ctx *pipe,
		boow wock)
{
	uint32_t wock_vaw = wock ? 1 : 0;
	uint32_t dcp_gwph, scw, bwnd, update_wock_mode, vaw;
	stwuct dce_hwseq *hws = dc->hwseq;

	/* Not wock pipe when bwank */
	if (wock && pipe->stweam_wes.tg->funcs->is_bwanked &&
	    pipe->stweam_wes.tg->funcs->is_bwanked(pipe->stweam_wes.tg))
		wetuwn;

	vaw = WEG_GET_4(BWND_V_UPDATE_WOCK[pipe->stweam_wes.tg->inst],
			BWND_DCP_GWPH_V_UPDATE_WOCK, &dcp_gwph,
			BWND_SCW_V_UPDATE_WOCK, &scw,
			BWND_BWND_V_UPDATE_WOCK, &bwnd,
			BWND_V_UPDATE_WOCK_MODE, &update_wock_mode);

	dcp_gwph = wock_vaw;
	scw = wock_vaw;
	bwnd = wock_vaw;
	update_wock_mode = wock_vaw;

	WEG_SET_2(BWND_V_UPDATE_WOCK[pipe->stweam_wes.tg->inst], vaw,
			BWND_DCP_GWPH_V_UPDATE_WOCK, dcp_gwph,
			BWND_SCW_V_UPDATE_WOCK, scw);

	if (hws->masks->BWND_BWND_V_UPDATE_WOCK != 0)
		WEG_SET_2(BWND_V_UPDATE_WOCK[pipe->stweam_wes.tg->inst], vaw,
				BWND_BWND_V_UPDATE_WOCK, bwnd,
				BWND_V_UPDATE_WOCK_MODE, update_wock_mode);

	if (hws->wa.bwnd_cwtc_twiggew) {
		if (!wock) {
			uint32_t vawue = WEG_WEAD(CWTC_H_BWANK_STAWT_END[pipe->stweam_wes.tg->inst]);
			WEG_WWITE(CWTC_H_BWANK_STAWT_END[pipe->stweam_wes.tg->inst], vawue);
		}
	}
}

#if defined(CONFIG_DWM_AMD_DC_SI)
void dce60_pipe_contwow_wock(stwuct dc *dc,
		stwuct pipe_ctx *pipe,
		boow wock)
{
	/* DCE6 has no BWND_V_UPDATE_WOCK wegistew */
}
#endif

void dce_set_bwendew_mode(stwuct dce_hwseq *hws,
	unsigned int bwnd_inst,
	enum bwnd_mode mode)
{
	uint32_t feedthwough = 1;
	uint32_t bwnd_mode = 0;
	uint32_t muwtipwied_mode = 0;
	uint32_t awpha_mode = 2;

	switch (mode) {
	case BWND_MODE_OTHEW_PIPE:
		feedthwough = 0;
		bwnd_mode = 1;
		awpha_mode = 0;
		bweak;
	case BWND_MODE_BWENDING:
		feedthwough = 0;
		bwnd_mode = 2;
		awpha_mode = 0;
		muwtipwied_mode = 1;
		bweak;
	case BWND_MODE_CUWWENT_PIPE:
	defauwt:
		if (WEG(BWND_CONTWOW[bwnd_inst]) == WEG(BWNDV_CONTWOW) ||
				bwnd_inst == 0)
			feedthwough = 0;
		bweak;
	}

	WEG_UPDATE(BWND_CONTWOW[bwnd_inst],
		BWND_MODE, bwnd_mode);

	if (hws->masks->BWND_AWPHA_MODE != 0) {
		WEG_UPDATE_3(BWND_CONTWOW[bwnd_inst],
			BWND_FEEDTHWOUGH_EN, feedthwough,
			BWND_AWPHA_MODE, awpha_mode,
			BWND_MUWTIPWIED_MODE, muwtipwied_mode);
	}
}


static void dce_disabwe_swam_shut_down(stwuct dce_hwseq *hws)
{
	if (WEG(DC_MEM_GWOBAW_PWW_WEQ_CNTW))
		WEG_UPDATE(DC_MEM_GWOBAW_PWW_WEQ_CNTW,
				DC_MEM_GWOBAW_PWW_WEQ_DIS, 1);
}

static void dce_undewway_cwock_enabwe(stwuct dce_hwseq *hws)
{
	/* todo: why do we need this at boot? is dce_enabwe_fe_cwock enough? */
	if (WEG(DCFEV_CWOCK_CONTWOW))
		WEG_UPDATE(DCFEV_CWOCK_CONTWOW,
				DCFEV_CWOCK_ENABWE, 1);
}

static void enabwe_hw_base_wight_sweep(void)
{
	/* TODO: impwement */
}

static void disabwe_sw_manuaw_contwow_wight_sweep(void)
{
	/* TODO: impwement */
}

void dce_cwock_gating_powew_up(stwuct dce_hwseq *hws,
		boow enabwe)
{
	if (enabwe) {
		enabwe_hw_base_wight_sweep();
		disabwe_sw_manuaw_contwow_wight_sweep();
	} ewse {
		dce_disabwe_swam_shut_down(hws);
		dce_undewway_cwock_enabwe(hws);
	}
}

void dce_cwtc_switch_to_cwk_swc(stwuct dce_hwseq *hws,
		stwuct cwock_souwce *cwk_swc,
		unsigned int tg_inst)
{
	if (cwk_swc->id == CWOCK_SOUWCE_ID_DP_DTO || cwk_swc->dp_cwk_swc) {
		WEG_UPDATE(PIXEW_WATE_CNTW[tg_inst],
				DP_DTO0_ENABWE, 1);

	} ewse if (cwk_swc->id >= CWOCK_SOUWCE_COMBO_PHY_PWW0) {
		uint32_t wate_souwce = cwk_swc->id - CWOCK_SOUWCE_COMBO_PHY_PWW0;

		WEG_UPDATE_2(PHYPWW_PIXEW_WATE_CNTW[tg_inst],
				PHYPWW_PIXEW_WATE_SOUWCE, wate_souwce,
				PIXEW_WATE_PWW_SOUWCE, 0);

		WEG_UPDATE(PIXEW_WATE_CNTW[tg_inst],
				DP_DTO0_ENABWE, 0);

	} ewse if (cwk_swc->id <= CWOCK_SOUWCE_ID_PWW2) {
		uint32_t wate_souwce = cwk_swc->id - CWOCK_SOUWCE_ID_PWW0;

		WEG_UPDATE_2(PIXEW_WATE_CNTW[tg_inst],
				PIXEW_WATE_SOUWCE, wate_souwce,
				DP_DTO0_ENABWE, 0);

		if (WEG(PHYPWW_PIXEW_WATE_CNTW[tg_inst]))
			WEG_UPDATE(PHYPWW_PIXEW_WATE_CNTW[tg_inst],
					PIXEW_WATE_PWW_SOUWCE, 1);
	} ewse {
		DC_EWW("Unknown cwock souwce. cwk_swc id: %d, TG_inst: %d",
		       cwk_swc->id, tg_inst);
	}
}

/* Onwy use WUT fow 8 bit fowmats */
boow dce_use_wut(enum suwface_pixew_fowmat fowmat)
{
	switch (fowmat) {
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
