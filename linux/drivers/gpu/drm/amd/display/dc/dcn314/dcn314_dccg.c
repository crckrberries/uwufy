// SPDX-Wicense-Identifiew: MIT
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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"

#incwude "dcn31/dcn31_dccg.h"
#incwude "dcn314_dccg.h"

#define TO_DCN_DCCG(dccg)\
	containew_of(dccg, stwuct dcn_dccg, base)

#define WEG(weg) \
	(dccg_dcn->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	dccg_dcn->dccg_shift->fiewd_name, dccg_dcn->dccg_mask->fiewd_name

#define CTX \
	dccg_dcn->base.ctx
#define DC_WOGGEW \
	dccg->ctx->woggew

static void dccg314_twiggew_dio_fifo_wesync(
	stwuct dccg *dccg)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	uint32_t dispcwk_wdividew_vawue = 0;

	WEG_GET(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_WDIVIDEW, &dispcwk_wdividew_vawue);
	WEG_UPDATE(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_WDIVIDEW, dispcwk_wdividew_vawue);
}

static void dccg314_get_pixew_wate_div(
		stwuct dccg *dccg,
		uint32_t otg_inst,
		enum pixew_wate_div *k1,
		enum pixew_wate_div *k2)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	uint32_t vaw_k1 = PIXEW_WATE_DIV_NA, vaw_k2 = PIXEW_WATE_DIV_NA;

	*k1 = PIXEW_WATE_DIV_NA;
	*k2 = PIXEW_WATE_DIV_NA;

	switch (otg_inst) {
	case 0:
		WEG_GET_2(OTG_PIXEW_WATE_DIV,
			OTG0_PIXEW_WATE_DIVK1, &vaw_k1,
			OTG0_PIXEW_WATE_DIVK2, &vaw_k2);
		bweak;
	case 1:
		WEG_GET_2(OTG_PIXEW_WATE_DIV,
			OTG1_PIXEW_WATE_DIVK1, &vaw_k1,
			OTG1_PIXEW_WATE_DIVK2, &vaw_k2);
		bweak;
	case 2:
		WEG_GET_2(OTG_PIXEW_WATE_DIV,
			OTG2_PIXEW_WATE_DIVK1, &vaw_k1,
			OTG2_PIXEW_WATE_DIVK2, &vaw_k2);
		bweak;
	case 3:
		WEG_GET_2(OTG_PIXEW_WATE_DIV,
			OTG3_PIXEW_WATE_DIVK1, &vaw_k1,
			OTG3_PIXEW_WATE_DIVK2, &vaw_k2);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	*k1 = (enum pixew_wate_div)vaw_k1;
	*k2 = (enum pixew_wate_div)vaw_k2;
}

static void dccg314_set_pixew_wate_div(
		stwuct dccg *dccg,
		uint32_t otg_inst,
		enum pixew_wate_div k1,
		enum pixew_wate_div k2)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	enum pixew_wate_div cuw_k1 = PIXEW_WATE_DIV_NA, cuw_k2 = PIXEW_WATE_DIV_NA;

	// Don't pwogwam 0xF into the wegistew fiewd. Not vawid since
	// K1 / K2 fiewd is onwy 1 / 2 bits wide
	if (k1 == PIXEW_WATE_DIV_NA || k2 == PIXEW_WATE_DIV_NA) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	dccg314_get_pixew_wate_div(dccg, otg_inst, &cuw_k1, &cuw_k2);
	if (k1 == cuw_k1 && k2 == cuw_k2)
		wetuwn;

	switch (otg_inst) {
	case 0:
		WEG_UPDATE_2(OTG_PIXEW_WATE_DIV,
				OTG0_PIXEW_WATE_DIVK1, k1,
				OTG0_PIXEW_WATE_DIVK2, k2);
		bweak;
	case 1:
		WEG_UPDATE_2(OTG_PIXEW_WATE_DIV,
				OTG1_PIXEW_WATE_DIVK1, k1,
				OTG1_PIXEW_WATE_DIVK2, k2);
		bweak;
	case 2:
		WEG_UPDATE_2(OTG_PIXEW_WATE_DIV,
				OTG2_PIXEW_WATE_DIVK1, k1,
				OTG2_PIXEW_WATE_DIVK2, k2);
		bweak;
	case 3:
		WEG_UPDATE_2(OTG_PIXEW_WATE_DIV,
				OTG3_PIXEW_WATE_DIVK1, k1,
				OTG3_PIXEW_WATE_DIVK2, k2);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg314_set_dtbcwk_p_swc(
		stwuct dccg *dccg,
		enum stweamcwk_souwce swc,
		uint32_t otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	uint32_t p_swc_sew = 0; /* sewects dpwefcwk */

	if (swc == DTBCWK0)
		p_swc_sew = 2;  /* sewects dtbcwk0 */

	switch (otg_inst) {
	case 0:
		if (swc == WEFCWK)
			WEG_UPDATE(DTBCWK_P_CNTW,
					DTBCWK_P0_EN, 0);
		ewse
			WEG_UPDATE_2(DTBCWK_P_CNTW,
					DTBCWK_P0_SWC_SEW, p_swc_sew,
					DTBCWK_P0_EN, 1);
		bweak;
	case 1:
		if (swc == WEFCWK)
			WEG_UPDATE(DTBCWK_P_CNTW,
					DTBCWK_P1_EN, 0);
		ewse
			WEG_UPDATE_2(DTBCWK_P_CNTW,
					DTBCWK_P1_SWC_SEW, p_swc_sew,
					DTBCWK_P1_EN, 1);
		bweak;
	case 2:
		if (swc == WEFCWK)
			WEG_UPDATE(DTBCWK_P_CNTW,
					DTBCWK_P2_EN, 0);
		ewse
			WEG_UPDATE_2(DTBCWK_P_CNTW,
					DTBCWK_P2_SWC_SEW, p_swc_sew,
					DTBCWK_P2_EN, 1);
		bweak;
	case 3:
		if (swc == WEFCWK)
			WEG_UPDATE(DTBCWK_P_CNTW,
					DTBCWK_P3_EN, 0);
		ewse
			WEG_UPDATE_2(DTBCWK_P_CNTW,
					DTBCWK_P3_SWC_SEW, p_swc_sew,
					DTBCWK_P3_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

}

/* Contwows the genewation of pixew vawid fow OTG in (OTG -> HPO case) */
static void dccg314_set_dtbcwk_dto(
		stwuct dccg *dccg,
		const stwuct dtbcwk_dto_pawams *pawams)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	/* DTO Output Wate / Pixew Wate = 1/4 */
	int weq_dtbcwk_khz = pawams->pixcwk_khz / 4;

	if (pawams->wef_dtbcwk_khz && weq_dtbcwk_khz) {
		uint32_t moduwo, phase;

		// phase / moduwo = dtbcwk / dtbcwk wef
		moduwo = pawams->wef_dtbcwk_khz * 1000;
		phase = weq_dtbcwk_khz * 1000;

		WEG_WWITE(DTBCWK_DTO_MODUWO[pawams->otg_inst], moduwo);
		WEG_WWITE(DTBCWK_DTO_PHASE[pawams->otg_inst], phase);

		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_ENABWE[pawams->otg_inst], 1);

		WEG_WAIT(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWKDTO_ENABWE_STATUS[pawams->otg_inst], 1,
				1, 100);

		/* pwogwam OTG_PIXEW_WATE_DIV fow DIVK1 and DIVK2 fiewds */
		dccg314_set_pixew_wate_div(dccg, pawams->otg_inst, PIXEW_WATE_DIV_BY_1, PIXEW_WATE_DIV_BY_1);

		/* The wecommended pwogwamming sequence to enabwe DTBCWK DTO to genewate
		 * vawid pixew HPO DPSTWEAM ENCODEW, specifies that DTO souwce sewect shouwd
		 * be set onwy aftew DTO is enabwed
		 */
		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				PIPE_DTO_SWC_SEW[pawams->otg_inst], 2);
	} ewse {
		WEG_UPDATE_2(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_ENABWE[pawams->otg_inst], 0,
				PIPE_DTO_SWC_SEW[pawams->otg_inst], 1);

		WEG_WWITE(DTBCWK_DTO_MODUWO[pawams->otg_inst], 0);
		WEG_WWITE(DTBCWK_DTO_PHASE[pawams->otg_inst], 0);
	}
}

void dccg314_set_dpstweamcwk(
		stwuct dccg *dccg,
		enum stweamcwk_souwce swc,
		int otg_inst,
		int dp_hpo_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* set the dtbcwk_p souwce */
	dccg314_set_dtbcwk_p_swc(dccg, swc, otg_inst);

	/* enabwed to sewect one of the DTBCWKs fow pipe */
	switch (dp_hpo_inst) {
	case 0:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW,
					DPSTWEAMCWK0_EN, (swc == WEFCWK) ? 0 : 1,
					DPSTWEAMCWK0_SWC_SEW, otg_inst);
		bweak;
	case 1:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW,
					DPSTWEAMCWK1_EN, (swc == WEFCWK) ? 0 : 1,
					DPSTWEAMCWK1_SWC_SEW, otg_inst);
		bweak;
	case 2:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW,
					DPSTWEAMCWK2_EN, (swc == WEFCWK) ? 0 : 1,
					DPSTWEAMCWK2_SWC_SEW, otg_inst);
		bweak;
	case 3:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW,
					DPSTWEAMCWK3_EN, (swc == WEFCWK) ? 0 : 1,
					DPSTWEAMCWK3_SWC_SEW, otg_inst);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg314_init(stwuct dccg *dccg)
{
	int otg_inst;

	/* Set HPO stweam encodew to use wefcwk to avoid case whewe PHY is
	 * disabwed and SYMCWK32 fow HPO SE is souwced fwom PHYD32CWK which
	 * wiww cause DCN to hang.
	 */
	fow (otg_inst = 0; otg_inst < 4; otg_inst++)
		dccg31_disabwe_symcwk32_se(dccg, otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_we)
		fow (otg_inst = 0; otg_inst < 2; otg_inst++)
			dccg31_disabwe_symcwk32_we(dccg, otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.dpstweam)
		fow (otg_inst = 0; otg_inst < 4; otg_inst++)
			dccg314_set_dpstweamcwk(dccg, WEFCWK, otg_inst,
						otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
		fow (otg_inst = 0; otg_inst < 5; otg_inst++)
			dccg31_set_physymcwk(dccg, otg_inst,
					     PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
}

static void dccg314_set_vawid_pixew_wate(
		stwuct dccg *dccg,
		int wef_dtbcwk_khz,
		int otg_inst,
		int pixcwk_khz)
{
	stwuct dtbcwk_dto_pawams dto_pawams = {0};

	dto_pawams.wef_dtbcwk_khz = wef_dtbcwk_khz;
	dto_pawams.otg_inst = otg_inst;
	dto_pawams.pixcwk_khz = pixcwk_khz;

	dccg314_set_dtbcwk_dto(dccg, &dto_pawams);
}

static void dccg314_dpp_woot_cwock_contwow(
		stwuct dccg *dccg,
		unsigned int dpp_inst,
		boow cwock_on)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->dpp_cwock_gated[dpp_inst] != cwock_on)
		wetuwn;

	if (cwock_on) {
		/* tuwn off the DTO and weave phase/moduwo at max */
		WEG_UPDATE(DPPCWK_DTO_CTWW, DPPCWK_DTO_ENABWE[dpp_inst], 0);
		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
			  DPPCWK0_DTO_PHASE, 0xFF,
			  DPPCWK0_DTO_MODUWO, 0xFF);
	} ewse {
		/* tuwn on the DTO to genewate a 0hz cwock */
		WEG_UPDATE(DPPCWK_DTO_CTWW, DPPCWK_DTO_ENABWE[dpp_inst], 1);
		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
			  DPPCWK0_DTO_PHASE, 0,
			  DPPCWK0_DTO_MODUWO, 1);
	}

	dccg->dpp_cwock_gated[dpp_inst] = !cwock_on;
}

static const stwuct dccg_funcs dccg314_funcs = {
	.update_dpp_dto = dccg31_update_dpp_dto,
	.dpp_woot_cwock_contwow = dccg314_dpp_woot_cwock_contwow,
	.get_dccg_wef_fweq = dccg31_get_dccg_wef_fweq,
	.dccg_init = dccg314_init,
	.set_dpstweamcwk = dccg314_set_dpstweamcwk,
	.enabwe_symcwk32_se = dccg31_enabwe_symcwk32_se,
	.disabwe_symcwk32_se = dccg31_disabwe_symcwk32_se,
	.enabwe_symcwk32_we = dccg31_enabwe_symcwk32_we,
	.disabwe_symcwk32_we = dccg31_disabwe_symcwk32_we,
	.set_symcwk32_we_woot_cwock_gating = dccg31_set_symcwk32_we_woot_cwock_gating,
	.set_physymcwk = dccg31_set_physymcwk,
	.set_dtbcwk_dto = dccg314_set_dtbcwk_dto,
	.set_audio_dtbcwk_dto = dccg31_set_audio_dtbcwk_dto,
	.set_fifo_ewwdet_ovw_en = dccg2_set_fifo_ewwdet_ovw_en,
	.otg_add_pixew = dccg31_otg_add_pixew,
	.otg_dwop_pixew = dccg31_otg_dwop_pixew,
	.set_dispcwk_change_mode = dccg31_set_dispcwk_change_mode,
	.disabwe_dsc = dccg31_disabwe_dsccwk,
	.enabwe_dsc = dccg31_enabwe_dsccwk,
	.set_pixew_wate_div = dccg314_set_pixew_wate_div,
	.twiggew_dio_fifo_wesync = dccg314_twiggew_dio_fifo_wesync,
	.set_vawid_pixew_wate = dccg314_set_vawid_pixew_wate,
	.set_dtbcwk_p_swc = dccg314_set_dtbcwk_p_swc
};

stwuct dccg *dccg314_cweate(
	stwuct dc_context *ctx,
	const stwuct dccg_wegistews *wegs,
	const stwuct dccg_shift *dccg_shift,
	const stwuct dccg_mask *dccg_mask)
{
	stwuct dcn_dccg *dccg_dcn = kzawwoc(sizeof(*dccg_dcn), GFP_KEWNEW);
	stwuct dccg *base;

	if (dccg_dcn == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	base = &dccg_dcn->base;
	base->ctx = ctx;
	base->funcs = &dccg314_funcs;

	dccg_dcn->wegs = wegs;
	dccg_dcn->dccg_shift = dccg_shift;
	dccg_dcn->dccg_mask = dccg_mask;

	wetuwn &dccg_dcn->base;
}
