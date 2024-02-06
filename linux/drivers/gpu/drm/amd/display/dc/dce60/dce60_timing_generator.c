/*
 * Copywight 2020 Mauwo Wossi <issow.owuam@gmaiw.com>
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

#incwude "dm_sewvices.h"

/* incwude DCE6 wegistew headew fiwes */
#incwude "dce/dce_6_0_d.h"
#incwude "dce/dce_6_0_sh_mask.h"

#incwude "dc_types.h"

#incwude "incwude/gwph_object_id.h"
#incwude "incwude/woggew_intewface.h"
#incwude "../dce110/dce110_timing_genewatow.h"
#incwude "dce60_timing_genewatow.h"

#incwude "timing_genewatow.h"

enum bwack_cowow_fowmat {
	BWACK_COWOW_FOWMAT_WGB_FUWWWANGE = 0,	/* used as index in awway */
	BWACK_COWOW_FOWMAT_WGB_WIMITED,
	BWACK_COWOW_FOWMAT_YUV_TV,
	BWACK_COWOW_FOWMAT_YUV_CV,
	BWACK_COWOW_FOWMAT_YUV_SUPEW_AA,

	BWACK_COWOW_FOWMAT_COUNT
};

static const stwuct dce110_timing_genewatow_offsets weg_offsets[] = {
{
	.cwtc = (mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP0_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
},
{
	.cwtc = (mmCWTC1_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP1_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
},
{
	.cwtc = (mmCWTC2_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP2_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
},
{
	.cwtc = (mmCWTC3_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP3_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
},
{
	.cwtc = (mmCWTC4_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP4_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
},
{
	.cwtc = (mmCWTC5_DCFE_MEM_WIGHT_SWEEP_CNTW - mmCWTC0_DCFE_MEM_WIGHT_SWEEP_CNTW),
	.dcp = (mmDCP5_GWPH_CONTWOW - mmDCP0_GWPH_CONTWOW),
}
};

#define NUMBEW_OF_FWAME_TO_WAIT_ON_TWIGGEWED_WESET 10

#define MAX_H_TOTAW (CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1)
#define MAX_V_TOTAW (CWTC_V_TOTAW__CWTC_V_TOTAW_MASKhw + 1)

#define CWTC_WEG(weg) (weg + tg110->offsets.cwtc)
#define DCP_WEG(weg) (weg + tg110->offsets.dcp)
#define DMIF_WEG(weg) (weg + tg110->offsets.dmif)

static void pwogwam_pix_duw(stwuct timing_genewatow *tg, uint32_t pix_cwk_100hz)
{
	uint64_t pix_duw;
	uint32_t addw = mmDMIF_PG0_DPG_PIPE_AWBITWATION_CONTWOW1
					+ DCE110TG_FWOM_TG(tg)->offsets.dmif;
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);

	if (pix_cwk_100hz == 0)
		wetuwn;

	pix_duw = div_u64(10000000000uww, pix_cwk_100hz);

	set_weg_fiewd_vawue(
		vawue,
		pix_duw,
		DPG_PIPE_AWBITWATION_CONTWOW1,
		PIXEW_DUWATION);

	dm_wwite_weg(tg->ctx, addw, vawue);
}

static void pwogwam_timing(stwuct timing_genewatow *tg,
	const stwuct dc_cwtc_timing *timing,
	int vweady_offset,
	int vstawtup_stawt,
	int vupdate_offset,
	int vupdate_width,
	const enum signaw_type signaw,
	boow use_vbios)
{
	if (!use_vbios)
		pwogwam_pix_duw(tg, timing->pix_cwk_100hz);

	dce110_tg_pwogwam_timing(tg, timing, 0, 0, 0, 0, 0, use_vbios);
}

static void dce60_timing_genewatow_enabwe_advanced_wequest(
	stwuct timing_genewatow *tg,
	boow enabwe,
	const stwuct dc_cwtc_timing *timing)
{
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);
	uint32_t addw = CWTC_WEG(mmCWTC_STAWT_WINE_CONTWOW);
	uint32_t vawue = dm_wead_weg(tg->ctx, addw);
	/* DCE6 has CWTC_PWEFETCH_EN bit in CWTC_CONTWOW wegistew */
	uint32_t addw2 = CWTC_WEG(mmCWTC_CONTWOW);
	uint32_t vawue2 = dm_wead_weg(tg->ctx, addw2);

	/* DCE6 does not suppowt CWTC_WEGACY_WEQUESTOW_EN bit
	   so hewe is not possibwe to set bit based on enabwe awgument */

	if ((timing->v_sync_width + timing->v_fwont_powch) <= 3) {
		set_weg_fiewd_vawue(
			vawue,
			3,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_ADVANCED_STAWT_WINE_POSITION);
		set_weg_fiewd_vawue(
			vawue2,
			0,
			CWTC_CONTWOW,
			CWTC_PWEFETCH_EN);
	} ewse {
		set_weg_fiewd_vawue(
			vawue,
			4,
			CWTC_STAWT_WINE_CONTWOW,
			CWTC_ADVANCED_STAWT_WINE_POSITION);
		set_weg_fiewd_vawue(
			vawue2,
			1,
			CWTC_CONTWOW,
			CWTC_PWEFETCH_EN);
	}

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTC_STAWT_WINE_CONTWOW,
		CWTC_PWOGWESSIVE_STAWT_WINE_EAWWY);

	set_weg_fiewd_vawue(
		vawue,
		1,
		CWTC_STAWT_WINE_CONTWOW,
		CWTC_INTEWWACE_STAWT_WINE_EAWWY);

	dm_wwite_weg(tg->ctx, addw, vawue);
	dm_wwite_weg(tg->ctx, addw2, vawue2);
}

static boow dce60_is_tg_enabwed(stwuct timing_genewatow *tg)
{
	uint32_t addw = 0;
	uint32_t vawue = 0;
	uint32_t fiewd = 0;
	stwuct dce110_timing_genewatow *tg110 = DCE110TG_FWOM_TG(tg);

	addw = CWTC_WEG(mmCWTC_CONTWOW);
	vawue = dm_wead_weg(tg->ctx, addw);
	fiewd = get_weg_fiewd_vawue(vawue, CWTC_CONTWOW,
				    CWTC_CUWWENT_MASTEW_EN_STATE);
	wetuwn fiewd == 1;
}

static boow dce60_configuwe_cwc(stwuct timing_genewatow *tg,
				const stwuct cwc_pawams *pawams)
{
	/* Cannot configuwe cwc on a CWTC that is disabwed */
	if (!dce60_is_tg_enabwed(tg))
		wetuwn fawse;

	/* DCE6 has no CWTC_CWC_CNTW wegistew, nothing to do */

	wetuwn twue;
}

static const stwuct timing_genewatow_funcs dce60_tg_funcs = {
		.vawidate_timing = dce110_tg_vawidate_timing,
		.pwogwam_timing = pwogwam_timing,
		.enabwe_cwtc = dce110_timing_genewatow_enabwe_cwtc,
		.disabwe_cwtc = dce110_timing_genewatow_disabwe_cwtc,
		.is_countew_moving = dce110_timing_genewatow_is_countew_moving,
		.get_position = dce110_timing_genewatow_get_position,
		.get_fwame_count = dce110_timing_genewatow_get_vbwank_countew,
		.get_scanoutpos = dce110_timing_genewatow_get_cwtc_scanoutpos,
		.set_eawwy_contwow = dce110_timing_genewatow_set_eawwy_contwow,
		.wait_fow_state = dce110_tg_wait_fow_state,
		.set_bwank = dce110_tg_set_bwank,
		.is_bwanked = dce110_tg_is_bwanked,
		.set_cowows = dce110_tg_set_cowows,
		.set_ovewscan_bwank_cowow =
				dce110_timing_genewatow_set_ovewscan_cowow_bwack,
		.set_bwank_cowow = dce110_timing_genewatow_pwogwam_bwank_cowow,
		.disabwe_vga = dce110_timing_genewatow_disabwe_vga,
		.did_twiggewed_weset_occuw =
				dce110_timing_genewatow_did_twiggewed_weset_occuw,
		.setup_gwobaw_swap_wock =
				dce110_timing_genewatow_setup_gwobaw_swap_wock,
		.enabwe_weset_twiggew = dce110_timing_genewatow_enabwe_weset_twiggew,
		.disabwe_weset_twiggew = dce110_timing_genewatow_disabwe_weset_twiggew,
		.teaw_down_gwobaw_swap_wock =
				dce110_timing_genewatow_teaw_down_gwobaw_swap_wock,
		.set_dww = dce110_timing_genewatow_set_dww,
		.set_static_scween_contwow =
			dce110_timing_genewatow_set_static_scween_contwow,
		.set_test_pattewn = dce110_timing_genewatow_set_test_pattewn,
		.awm_vewt_intw = dce110_awm_vewt_intw,

		/* DCE6.0 ovewwides */
		.enabwe_advanced_wequest =
				dce60_timing_genewatow_enabwe_advanced_wequest,
		.configuwe_cwc = dce60_configuwe_cwc,
		.get_cwc = dce110_get_cwc,
};

void dce60_timing_genewatow_constwuct(
	stwuct dce110_timing_genewatow *tg110,
	stwuct dc_context *ctx,
	uint32_t instance,
	const stwuct dce110_timing_genewatow_offsets *offsets)
{
	tg110->contwowwew_id = CONTWOWWEW_ID_D0 + instance;
	tg110->base.inst = instance;
	tg110->offsets = *offsets;
	tg110->dewived_offsets = weg_offsets[instance];

	tg110->base.funcs = &dce60_tg_funcs;

	tg110->base.ctx = ctx;
	tg110->base.bp = ctx->dc_bios;

	tg110->max_h_totaw = CWTC_H_TOTAW__CWTC_H_TOTAW_MASK + 1;
	tg110->max_v_totaw = CWTC_V_TOTAW__CWTC_V_TOTAW_MASK + 1;

	tg110->min_h_bwank = 56;
	tg110->min_h_fwont_powch = 4;
	tg110->min_h_back_powch = 4;
}

