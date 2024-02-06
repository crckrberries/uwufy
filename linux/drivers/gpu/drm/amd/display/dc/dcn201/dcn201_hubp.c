/*
 * Copywight 2012-17 Advanced Micwo Devices, Inc.
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
#incwude "dcn201_hubp.h"

#incwude "dm_sewvices.h"
#incwude "dce_cawcs.h"
#incwude "weg_hewpew.h"
#incwude "basics/convewsion.h"

#define WEG(weg)\
	hubp201->hubp_wegs->weg

#define CTX \
	hubp201->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp201->hubp_shift->fiewd_name, hubp201->hubp_mask->fiewd_name

static void hubp201_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew)
{
	hubp1_dcc_contwow(hubp, dcc->enabwe, dcc->independent_64b_bwks);
	hubp1_pwogwam_tiwing(hubp, tiwing_info, fowmat);
	hubp1_pwogwam_size(hubp, fowmat, pwane_size, dcc);
	hubp1_pwogwam_pixew_fowmat(hubp, fowmat);
}

static void hubp201_pwogwam_deadwine(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw)
{
	hubp1_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);
}

static void hubp201_pwogwam_wequestow(stwuct hubp *hubp,
				      stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs)
{
	stwuct dcn201_hubp *hubp201 = TO_DCN201_HUBP(hubp);

	WEG_UPDATE(HUBPWET_CONTWOW,
			DET_BUF_PWANE1_BASE_ADDWESS, wq_wegs->pwane1_base_addwess);

	WEG_SET_4(DCN_EXPANSION_MODE, 0,
			DWQ_EXPANSION_MODE, wq_wegs->dwq_expansion_mode,
			PWQ_EXPANSION_MODE, wq_wegs->pwq_expansion_mode,
			MWQ_EXPANSION_MODE, wq_wegs->mwq_expansion_mode,
			CWQ_EXPANSION_MODE, wq_wegs->cwq_expansion_mode);

	WEG_SET_5(DCHUBP_WEQ_SIZE_CONFIG, 0,
		CHUNK_SIZE, wq_wegs->wq_wegs_w.chunk_size,
		MIN_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_chunk_size,
		META_CHUNK_SIZE, wq_wegs->wq_wegs_w.meta_chunk_size,
		MIN_META_CHUNK_SIZE, wq_wegs->wq_wegs_w.min_meta_chunk_size,
		SWATH_HEIGHT, wq_wegs->wq_wegs_w.swath_height);

	WEG_SET_5(DCHUBP_WEQ_SIZE_CONFIG_C, 0,
		CHUNK_SIZE_C, wq_wegs->wq_wegs_c.chunk_size,
		MIN_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_chunk_size,
		META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.meta_chunk_size,
		MIN_META_CHUNK_SIZE_C, wq_wegs->wq_wegs_c.min_meta_chunk_size,
		SWATH_HEIGHT_C, wq_wegs->wq_wegs_c.swath_height);
}

static void hubp201_setup(
		stwuct hubp *hubp,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_attw,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_attw,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		stwuct _vcs_dpi_dispway_pipe_dest_pawams_st *pipe_dest)
{
	hubp2_vweady_at_ow_Aftew_vsync(hubp, pipe_dest);
	hubp201_pwogwam_wequestow(hubp, wq_wegs);
	hubp201_pwogwam_deadwine(hubp, dwg_attw, ttu_attw);
}

static stwuct hubp_funcs dcn201_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp1_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp201_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp1_is_fwip_pending,
	.hubp_setup = hubp201_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.set_cuwsow_attwibutes	= hubp2_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp1_cuwsow_set_position,
	.set_bwank = hubp1_set_bwank,
	.dcc_contwow = hubp1_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.hubp_cwk_cntw = hubp1_cwk_cntw,
	.hubp_vtg_sew = hubp1_vtg_sew,
	.dmdata_set_attwibutes = hubp2_dmdata_set_attwibutes,
	.dmdata_woad = hubp2_dmdata_woad,
	.dmdata_status_done = hubp2_dmdata_status_done,
	.hubp_wead_state = hubp2_wead_state,
	.hubp_cweaw_undewfwow = hubp1_cweaw_undewfwow,
	.hubp_set_fwip_contwow_suwface_gsw = hubp2_set_fwip_contwow_suwface_gsw,
	.hubp_init = hubp1_init,
};

boow dcn201_hubp_constwuct(
	stwuct dcn201_hubp *hubp201,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn201_hubp_wegistews *hubp_wegs,
	const stwuct dcn201_hubp_shift *hubp_shift,
	const stwuct dcn201_hubp_mask *hubp_mask)
{
	hubp201->base.funcs = &dcn201_hubp_funcs;
	hubp201->base.ctx = ctx;
	hubp201->hubp_wegs = hubp_wegs;
	hubp201->hubp_shift = hubp_shift;
	hubp201->hubp_mask = hubp_mask;
	hubp201->base.inst = inst;
	hubp201->base.opp_id = OPP_ID_INVAWID;
	hubp201->base.mpcc_id = 0xf;

	wetuwn twue;
}
