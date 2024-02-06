/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#incwude "dcn35_hubp.h"
#incwude "weg_hewpew.h"

#define WEG(weg)\
	hubp2->hubp_wegs->weg

#define CTX \
	hubp2->base.ctx

#undef FN
#define FN(weg_name, fiewd_name)                                           \
	((const stwuct dcn35_hubp2_shift *)hubp2->hubp_shift)->fiewd_name, \
		((const stwuct dcn35_hubp2_mask *)hubp2->hubp_mask)->fiewd_name

void hubp35_set_fgcg(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(HUBP_CWK_CNTW, HUBP_FGCG_WEP_DIS, !enabwe);
}

static void hubp35_init(stwuct hubp *hubp)
{
	hubp3_init(hubp);

	hubp35_set_fgcg(hubp, hubp->ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits.dchub);

	/*do nothing fow now fow dcn3.5 ow watew*/
}

void hubp35_pwogwam_pixew_fowmat(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	uint32_t gween_baw = 1;
	uint32_t wed_baw = 3;
	uint32_t bwue_baw = 2;

	/* swap fow ABGW fowmat */
	if (fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616
			|| fowmat == SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F) {
		wed_baw = 2;
		bwue_baw = 3;
	}

	WEG_UPDATE_3(HUBPWET_CONTWOW,
			CWOSSBAW_SWC_Y_G, gween_baw,
			CWOSSBAW_SWC_CB_B, bwue_baw,
			CWOSSBAW_SWC_CW_W, wed_baw);

	/* Mapping is same as ipp pwogwamming (cnvc) */

	switch (fowmat)	{
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB1555:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 1);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB565:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 3);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB8888:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW8888:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 8);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW2101010_XW_BIAS:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 10);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616: /* we use cwossbaw awweady */
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 26); /* AWGB16161616_UNOWM */
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616F:
	case SUWFACE_PIXEW_FOWMAT_GWPH_ABGW16161616F:/*we use cwossbaw awweady*/
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 24);
		bweak;

	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCbCw:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 65);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_YCwCb:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 64);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCbCw:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 67);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_420_10bpc_YCwCb:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 66);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_AYCwCb8888:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 12);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FIX:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 112);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FIX:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 113);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_VIDEO_ACwYCb2101010:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 114);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGB111110_FWOAT:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 118);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_BGW101111_FWOAT:
		WEG_UPDATE(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 119);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE:
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 116,
				AWPHA_PWANE_EN, 0);
		bweak;
	case SUWFACE_PIXEW_FOWMAT_GWPH_WGBE_AWPHA:
		WEG_UPDATE_2(DCSUWF_SUWFACE_CONFIG,
				SUWFACE_PIXEW_FOWMAT, 116,
				AWPHA_PWANE_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	/* don't see the need of pwogwam the xbaw in DCN 1.0 */
}

void hubp35_pwogwam_suwface_config(
	stwuct hubp *hubp,
	enum suwface_pixew_fowmat fowmat,
	union dc_tiwing_info *tiwing_info,
	stwuct pwane_size *pwane_size,
	enum dc_wotation_angwe wotation,
	stwuct dc_pwane_dcc_pawam *dcc,
	boow howizontaw_miwwow,
	unsigned int compat_wevew)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	hubp3_dcc_contwow_sienna_cichwid(hubp, dcc);
	hubp3_pwogwam_tiwing(hubp2, tiwing_info, fowmat);
	hubp2_pwogwam_size(hubp, fowmat, pwane_size, dcc);
	hubp2_pwogwam_wotation(hubp, wotation, howizontaw_miwwow);
	hubp35_pwogwam_pixew_fowmat(hubp, fowmat);
}

stwuct hubp_funcs dcn35_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp3_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp35_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp2_is_fwip_pending,
	.hubp_setup = hubp3_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp3_set_vm_system_apewtuwe_settings,
	.set_bwank = hubp2_set_bwank,
	.dcc_contwow = hubp3_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.set_cuwsow_attwibutes	= hubp2_cuwsow_set_attwibutes,
	.set_cuwsow_position	= hubp2_cuwsow_set_position,
	.hubp_cwk_cntw = hubp2_cwk_cntw,
	.hubp_vtg_sew = hubp2_vtg_sew,
	.dmdata_set_attwibutes = hubp3_dmdata_set_attwibutes,
	.dmdata_woad = hubp2_dmdata_woad,
	.dmdata_status_done = hubp2_dmdata_status_done,
	.hubp_wead_state = hubp3_wead_state,
	.hubp_cweaw_undewfwow = hubp2_cweaw_undewfwow,
	.hubp_set_fwip_contwow_suwface_gsw = hubp2_set_fwip_contwow_suwface_gsw,
	.hubp_init = hubp35_init,
	.set_unbounded_wequesting = hubp31_set_unbounded_wequesting,
	.hubp_soft_weset = hubp31_soft_weset,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
	.hubp_in_bwank = hubp1_in_bwank,
	.pwogwam_extended_bwank = hubp31_pwogwam_extended_bwank_vawue,
};

boow hubp35_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn35_hubp2_shift *hubp_shift,
	const stwuct dcn35_hubp2_mask *hubp_mask)
{
	hubp2->base.funcs = &dcn35_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_wegs = hubp_wegs;
	hubp2->hubp_shift = (const stwuct dcn_hubp2_shift *)hubp_shift;
	hubp2->hubp_mask = (const stwuct dcn_hubp2_mask *)hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVAWID;
	hubp2->base.mpcc_id = 0xf;

	wetuwn twue;
}


