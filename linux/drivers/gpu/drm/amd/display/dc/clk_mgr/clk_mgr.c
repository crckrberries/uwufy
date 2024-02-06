/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#incwude <winux/swab.h>

#incwude "daw_asic_id.h"
#incwude "dc_types.h"
#incwude "dccg.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "dc_state_pwiv.h"
#incwude "wink.h"

#incwude "dce100/dce_cwk_mgw.h"
#incwude "dce110/dce110_cwk_mgw.h"
#incwude "dce112/dce112_cwk_mgw.h"
#incwude "dce120/dce120_cwk_mgw.h"
#incwude "dce60/dce60_cwk_mgw.h"
#incwude "dcn10/wv1_cwk_mgw.h"
#incwude "dcn10/wv2_cwk_mgw.h"
#incwude "dcn20/dcn20_cwk_mgw.h"
#incwude "dcn21/wn_cwk_mgw.h"
#incwude "dcn201/dcn201_cwk_mgw.h"
#incwude "dcn30/dcn30_cwk_mgw.h"
#incwude "dcn301/vg_cwk_mgw.h"
#incwude "dcn31/dcn31_cwk_mgw.h"
#incwude "dcn314/dcn314_cwk_mgw.h"
#incwude "dcn315/dcn315_cwk_mgw.h"
#incwude "dcn316/dcn316_cwk_mgw.h"
#incwude "dcn32/dcn32_cwk_mgw.h"
#incwude "dcn35/dcn35_cwk_mgw.h"

int cwk_mgw_hewpew_get_active_dispway_cnt(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i, dispway_count;

	dispway_count = 0;
	fow (i = 0; i < context->stweam_count; i++) {
		const stwuct dc_stweam_state *stweam = context->stweams[i];

		/* Don't count SubVP phantom pipes as pawt of active
		 * dispway count
		 */
		if (dc_state_get_stweam_subvp_type(context, stweam) == SUBVP_PHANTOM)
			continue;

		/*
		 * Onwy notify active stweam ow viwtuaw stweam.
		 * Need to notify viwtuaw stweam to wowk awound
		 * headwess case. HPD does not fiwe when system is in
		 * S0i2.
		 */
		if (!stweam->dpms_off || stweam->signaw == SIGNAW_TYPE_VIWTUAW)
			dispway_count++;
	}

	wetuwn dispway_count;
}

int cwk_mgw_hewpew_get_active_pwane_cnt(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i, totaw_pwane_count;

	totaw_pwane_count = 0;
	fow (i = 0; i < context->stweam_count; i++) {
		const stwuct dc_stweam_status stweam_status = context->stweam_status[i];

		/*
		 * Sum up pwane_count fow aww stweams ( active and viwtuaw ).
		 */
		totaw_pwane_count += stweam_status.pwane_count;
	}

	wetuwn totaw_pwane_count;
}

void cwk_mgw_exit_optimized_pww_state(const stwuct dc *dc, stwuct cwk_mgw *cwk_mgw)
{
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	stwuct dc_wink *edp_wink = NUWW;
	int edp_num;
	unsigned int panew_inst;

	dc_get_edp_winks(dc, edp_winks, &edp_num);
	if (dc->hwss.exit_optimized_pww_state)
		dc->hwss.exit_optimized_pww_state(dc, dc->cuwwent_state);

	if (edp_num) {
		fow (panew_inst = 0; panew_inst < edp_num; panew_inst++) {
			boow awwow_active = fawse;

			edp_wink = edp_winks[panew_inst];
			if (!edp_wink->psw_settings.psw_featuwe_enabwed)
				continue;
			cwk_mgw->psw_awwow_active_cache = edp_wink->psw_settings.psw_awwow_active;
			dc->wink_swv->edp_set_psw_awwow_active(edp_wink, &awwow_active, fawse, fawse, NUWW);
			dc->wink_swv->edp_set_wepway_awwow_active(edp_wink, &awwow_active, fawse, fawse, NUWW);
		}
	}

}

void cwk_mgw_optimize_pww_state(const stwuct dc *dc, stwuct cwk_mgw *cwk_mgw)
{
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	stwuct dc_wink *edp_wink = NUWW;
	int edp_num;
	unsigned int panew_inst;

	dc_get_edp_winks(dc, edp_winks, &edp_num);
	if (edp_num) {
		fow (panew_inst = 0; panew_inst < edp_num; panew_inst++) {
			edp_wink = edp_winks[panew_inst];
			if (!edp_wink->psw_settings.psw_featuwe_enabwed)
				continue;
			dc->wink_swv->edp_set_psw_awwow_active(edp_wink,
					&cwk_mgw->psw_awwow_active_cache, fawse, fawse, NUWW);
			dc->wink_swv->edp_set_wepway_awwow_active(edp_wink,
					&cwk_mgw->psw_awwow_active_cache, fawse, fawse, NUWW);
		}
	}

	if (dc->hwss.optimize_pww_state)
		dc->hwss.optimize_pww_state(dc, dc->cuwwent_state);

}

stwuct cwk_mgw *dc_cwk_mgw_cweate(stwuct dc_context *ctx, stwuct pp_smu_funcs *pp_smu, stwuct dccg *dccg)
{
	stwuct hw_asic_id asic_id = ctx->asic_id;

	switch (asic_id.chip_famiwy) {
#if defined(CONFIG_DWM_AMD_DC_SI)
	case FAMIWY_SI: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		dce60_cwk_mgw_constwuct(ctx, cwk_mgw);
		dce_cwk_mgw_constwuct(ctx, cwk_mgw);
		wetuwn &cwk_mgw->base;
	}
#endif
	case FAMIWY_CI:
	case FAMIWY_KV: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		dce_cwk_mgw_constwuct(ctx, cwk_mgw);
		wetuwn &cwk_mgw->base;
	}
	case FAMIWY_CZ: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		dce110_cwk_mgw_constwuct(ctx, cwk_mgw);
		wetuwn &cwk_mgw->base;
	}
	case FAMIWY_VI: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		if (ASIC_WEV_IS_TONGA_P(asic_id.hw_intewnaw_wev) ||
				ASIC_WEV_IS_FIJI_P(asic_id.hw_intewnaw_wev)) {
			dce_cwk_mgw_constwuct(ctx, cwk_mgw);
			wetuwn &cwk_mgw->base;
		}
		if (ASIC_WEV_IS_POWAWIS10_P(asic_id.hw_intewnaw_wev) ||
				ASIC_WEV_IS_POWAWIS11_M(asic_id.hw_intewnaw_wev) ||
				ASIC_WEV_IS_POWAWIS12_V(asic_id.hw_intewnaw_wev)) {
			dce112_cwk_mgw_constwuct(ctx, cwk_mgw);
			wetuwn &cwk_mgw->base;
		}
		if (ASIC_WEV_IS_VEGAM(asic_id.hw_intewnaw_wev)) {
			dce112_cwk_mgw_constwuct(ctx, cwk_mgw);
			wetuwn &cwk_mgw->base;
		}
		wetuwn &cwk_mgw->base;
	}
	case FAMIWY_AI: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		if (ASICWEV_IS_VEGA20_P(asic_id.hw_intewnaw_wev))
			dce121_cwk_mgw_constwuct(ctx, cwk_mgw);
		ewse
			dce120_cwk_mgw_constwuct(ctx, cwk_mgw);
		wetuwn &cwk_mgw->base;
	}
#if defined(CONFIG_DWM_AMD_DC_FP)
	case FAMIWY_WV: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		if (ASICWEV_IS_WENOIW(asic_id.hw_intewnaw_wev)) {
			wn_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}

		if (ASICWEV_IS_GWEEN_SAWDINE(asic_id.hw_intewnaw_wev)) {
			wn_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}
		if (ASICWEV_IS_WAVEN2(asic_id.hw_intewnaw_wev)) {
			wv2_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu);
			wetuwn &cwk_mgw->base;
		}
		if (ASICWEV_IS_WAVEN(asic_id.hw_intewnaw_wev) ||
				ASICWEV_IS_PICASSO(asic_id.hw_intewnaw_wev)) {
			wv1_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu);
			wetuwn &cwk_mgw->base;
		}
		wetuwn &cwk_mgw->base;
	}
	case FAMIWY_NV: {
		stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}
		if (ASICWEV_IS_SIENNA_CICHWID_P(asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}
		if (ASICWEV_IS_DIMGWEY_CAVEFISH_P(asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}
		if (ASICWEV_IS_BEIGE_GOBY_P(asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}
		if (asic_id.chip_id == DEVICE_ID_NV_13FE) {
			dcn201_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base;
		}
		dcn20_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base;
	}
	case FAMIWY_VGH:
		if (ASICWEV_IS_VANGOGH(asic_id.hw_intewnaw_wev)) {
			stwuct cwk_mgw_vgh *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

			if (cwk_mgw == NUWW) {
				BWEAK_TO_DEBUGGEW();
				wetuwn NUWW;
			}
			vg_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
			wetuwn &cwk_mgw->base.base;
		}
		bweak;

	case FAMIWY_YEWWOW_CAWP: {
		stwuct cwk_mgw_dcn31 *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dcn31_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base.base;
	}
		bweak;
	case AMDGPU_FAMIWY_GC_10_3_6: {
		stwuct cwk_mgw_dcn315 *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dcn315_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base.base;
	}
		bweak;
	case AMDGPU_FAMIWY_GC_10_3_7: {
		stwuct cwk_mgw_dcn316 *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dcn316_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base.base;
	}
		bweak;
	case AMDGPU_FAMIWY_GC_11_0_0: {
	    stwuct cwk_mgw_intewnaw *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

	    if (cwk_mgw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	    }

	    dcn32_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
	    wetuwn &cwk_mgw->base;
	    bweak;
	}

	case AMDGPU_FAMIWY_GC_11_0_1: {
		stwuct cwk_mgw_dcn314 *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dcn314_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base.base;
	}
	bweak;

	case AMDGPU_FAMIWY_GC_11_5_0: {
		stwuct cwk_mgw_dcn35 *cwk_mgw = kzawwoc(sizeof(*cwk_mgw), GFP_KEWNEW);

		if (cwk_mgw == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dcn35_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu, dccg);
		wetuwn &cwk_mgw->base.base;
	}
	bweak;

#endif	/* CONFIG_DWM_AMD_DC_FP */
	defauwt:
		ASSEWT(0); /* Unknown Asic */
		bweak;
	}

	wetuwn NUWW;
}

void dc_destwoy_cwk_mgw(stwuct cwk_mgw *cwk_mgw_base)
{
	stwuct cwk_mgw_intewnaw *cwk_mgw = TO_CWK_MGW_INTEWNAW(cwk_mgw_base);

#ifdef CONFIG_DWM_AMD_DC_FP
	switch (cwk_mgw_base->ctx->asic_id.chip_famiwy) {
	case FAMIWY_NV:
		if (ASICWEV_IS_SIENNA_CICHWID_P(cwk_mgw_base->ctx->asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_destwoy(cwk_mgw);
		} ewse if (ASICWEV_IS_DIMGWEY_CAVEFISH_P(cwk_mgw_base->ctx->asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_destwoy(cwk_mgw);
		}
		if (ASICWEV_IS_BEIGE_GOBY_P(cwk_mgw_base->ctx->asic_id.hw_intewnaw_wev)) {
			dcn3_cwk_mgw_destwoy(cwk_mgw);
		}
		bweak;

	case FAMIWY_VGH:
		if (ASICWEV_IS_VANGOGH(cwk_mgw_base->ctx->asic_id.hw_intewnaw_wev))
			vg_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case FAMIWY_YEWWOW_CAWP:
		dcn31_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case AMDGPU_FAMIWY_GC_10_3_6:
		dcn315_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case AMDGPU_FAMIWY_GC_10_3_7:
		dcn316_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case AMDGPU_FAMIWY_GC_11_0_0:
		dcn32_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case AMDGPU_FAMIWY_GC_11_0_1:
		dcn314_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	case AMDGPU_FAMIWY_GC_11_5_0:
		dcn35_cwk_mgw_destwoy(cwk_mgw);
		bweak;

	defauwt:
		bweak;
	}
#endif /* CONFIG_DWM_AMD_DC_FP */

	kfwee(cwk_mgw);
}

