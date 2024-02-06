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
 */

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dcn35_dccg.h"

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

static void dcn35_set_dppcwk_enabwe(stwuct dccg *dccg,
				 uint32_t dpp_inst, uint32_t enabwe)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	switch (dpp_inst) {
	case 0:
		WEG_UPDATE(DPPCWK_CTWW, DPPCWK0_EN, enabwe);
		bweak;
	case 1:
		WEG_UPDATE(DPPCWK_CTWW, DPPCWK1_EN, enabwe);
		bweak;
	case 2:
		WEG_UPDATE(DPPCWK_CTWW, DPPCWK2_EN, enabwe);
		bweak;
	case 3:
		WEG_UPDATE(DPPCWK_CTWW, DPPCWK3_EN, enabwe);
		bweak;
	defauwt:
		bweak;
	}

}

static void dccg35_update_dpp_dto(stwuct dccg *dccg, int dpp_inst,
				  int weq_dppcwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->dpp_cwock_gated[dpp_inst]) {
		/*
		 * Do not update the DPPCWK DTO if the cwock is stopped.
		 */
		wetuwn;
	}

	if (dccg->wef_dppcwk && weq_dppcwk) {
		int wef_dppcwk = dccg->wef_dppcwk;
		int moduwo, phase;

		// phase / moduwo = dpp pipe cwk / dpp gwobaw cwk
		moduwo = 0xff;   // use FF at the end
		phase = ((moduwo * weq_dppcwk) + wef_dppcwk - 1) / wef_dppcwk;

		if (phase > 0xff) {
			ASSEWT(fawse);
			phase = 0xff;
		}

		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
				DPPCWK0_DTO_PHASE, phase,
				DPPCWK0_DTO_MODUWO, moduwo);

		dcn35_set_dppcwk_enabwe(dccg, dpp_inst, twue);
	} ewse
		dcn35_set_dppcwk_enabwe(dccg, dpp_inst, fawse);
	dccg->pipe_dppcwk_khz[dpp_inst] = weq_dppcwk;
}

static void dccg35_get_pixew_wate_div(
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

static void dccg35_set_pixew_wate_div(
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

	dccg35_get_pixew_wate_div(dccg, otg_inst, &cuw_k1, &cuw_k2);
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

static void dccg35_set_dtbcwk_p_swc(
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
static void dccg35_set_dtbcwk_dto(
		stwuct dccg *dccg,
		const stwuct dtbcwk_dto_pawams *pawams)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	/* DTO Output Wate / Pixew Wate = 1/4 */
	int weq_dtbcwk_khz = pawams->pixcwk_khz / 4;

	if (pawams->wef_dtbcwk_khz && weq_dtbcwk_khz) {
		uint32_t moduwo, phase;

		switch (pawams->otg_inst) {
		case 0:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P0_GATE_DISABWE, 1);
			bweak;
		case 1:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P1_GATE_DISABWE, 1);
			bweak;
		case 2:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P2_GATE_DISABWE, 1);
			bweak;
		case 3:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P3_GATE_DISABWE, 1);
			bweak;
		}

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
		dccg35_set_pixew_wate_div(dccg, pawams->otg_inst, PIXEW_WATE_DIV_BY_1, PIXEW_WATE_DIV_BY_1);

		/* The wecommended pwogwamming sequence to enabwe DTBCWK DTO to genewate
		 * vawid pixew HPO DPSTWEAM ENCODEW, specifies that DTO souwce sewect shouwd
		 * be set onwy aftew DTO is enabwed
		 */
		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				PIPE_DTO_SWC_SEW[pawams->otg_inst], 2);
	} ewse {
		switch (pawams->otg_inst) {
		case 0:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P0_GATE_DISABWE, 0);
			bweak;
		case 1:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P1_GATE_DISABWE, 0);
			bweak;
		case 2:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P2_GATE_DISABWE, 0);
			bweak;
		case 3:
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW5, DTBCWK_P3_GATE_DISABWE, 0);
			bweak;
		}

		WEG_UPDATE_2(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_ENABWE[pawams->otg_inst], 0,
				PIPE_DTO_SWC_SEW[pawams->otg_inst], pawams->is_hdmi ? 0 : 1);

		WEG_WWITE(DTBCWK_DTO_MODUWO[pawams->otg_inst], 0);
		WEG_WWITE(DTBCWK_DTO_PHASE[pawams->otg_inst], 0);
	}
}

static void dccg35_set_dpstweamcwk(
		stwuct dccg *dccg,
		enum stweamcwk_souwce swc,
		int otg_inst,
		int dp_hpo_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* set the dtbcwk_p souwce */
	dccg35_set_dtbcwk_p_swc(dccg, swc, otg_inst);

	/* enabwed to sewect one of the DTBCWKs fow pipe */
	switch (dp_hpo_inst) {
	case 0:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK0_EN,
				(swc == WEFCWK) ? 0 : 1, DPSTWEAMCWK0_SWC_SEW, otg_inst);
		bweak;
	case 1:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW, DPSTWEAMCWK1_EN,
				(swc == WEFCWK) ? 0 : 1, DPSTWEAMCWK1_SWC_SEW, otg_inst);
		bweak;
	case 2:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW, DPSTWEAMCWK2_EN,
				(swc == WEFCWK) ? 0 : 1, DPSTWEAMCWK2_SWC_SEW, otg_inst);
		bweak;
	case 3:
		WEG_UPDATE_2(DPSTWEAMCWK_CNTW, DPSTWEAMCWK3_EN,
				(swc == WEFCWK) ? 0 : 1, DPSTWEAMCWK3_SWC_SEW, otg_inst);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg35_set_physymcwk_woot_cwock_gating(
		stwuct dccg *dccg,
		int phy_inst,
		boow enabwe)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (!dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
		wetuwn;

	switch (phy_inst) {
	case 0:
		WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
				PHYASYMCWK_WOOT_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	case 1:
		WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
				PHYBSYMCWK_WOOT_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	case 2:
		WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
				PHYCSYMCWK_WOOT_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	case 3:
		WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
				PHYDSYMCWK_WOOT_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	case 4:
		WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
				PHYESYMCWK_WOOT_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg35_set_physymcwk(
		stwuct dccg *dccg,
		int phy_inst,
		enum physymcwk_cwock_souwce cwk_swc,
		boow fowce_enabwe)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* Fowce PHYSYMCWK on and Sewect phyd32cwk as the souwce of cwock which is output to PHY thwough DCIO */
	switch (phy_inst) {
	case 0:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYASYMCWK_CWOCK_CNTW,
					PHYASYMCWK_EN, 1,
					PHYASYMCWK_SWC_SEW, cwk_swc);
		} ewse {
			WEG_UPDATE_2(PHYASYMCWK_CWOCK_CNTW,
					PHYASYMCWK_EN, 0,
					PHYASYMCWK_SWC_SEW, 0);
		}
		bweak;
	case 1:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYBSYMCWK_CWOCK_CNTW,
					PHYBSYMCWK_EN, 1,
					PHYBSYMCWK_SWC_SEW, cwk_swc);
		} ewse {
			WEG_UPDATE_2(PHYBSYMCWK_CWOCK_CNTW,
					PHYBSYMCWK_EN, 0,
					PHYBSYMCWK_SWC_SEW, 0);
		}
		bweak;
	case 2:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYCSYMCWK_CWOCK_CNTW,
					PHYCSYMCWK_EN, 1,
					PHYCSYMCWK_SWC_SEW, cwk_swc);
		} ewse {
			WEG_UPDATE_2(PHYCSYMCWK_CWOCK_CNTW,
					PHYCSYMCWK_EN, 0,
					PHYCSYMCWK_SWC_SEW, 0);
		}
		bweak;
	case 3:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYDSYMCWK_CWOCK_CNTW,
					PHYDSYMCWK_EN, 1,
					PHYDSYMCWK_SWC_SEW, cwk_swc);
		} ewse {
			WEG_UPDATE_2(PHYDSYMCWK_CWOCK_CNTW,
					PHYDSYMCWK_EN, 0,
					PHYDSYMCWK_SWC_SEW, 0);
		}
		bweak;
	case 4:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYESYMCWK_CWOCK_CNTW,
					PHYESYMCWK_EN, 1,
					PHYESYMCWK_SWC_SEW, cwk_swc);
		} ewse {
			WEG_UPDATE_2(PHYESYMCWK_CWOCK_CNTW,
					PHYESYMCWK_EN, 0,
					PHYESYMCWK_SWC_SEW, 0);
		}
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg35_set_vawid_pixew_wate(
		stwuct dccg *dccg,
		int wef_dtbcwk_khz,
		int otg_inst,
		int pixcwk_khz)
{
	stwuct dtbcwk_dto_pawams dto_pawams = {0};

	dto_pawams.wef_dtbcwk_khz = wef_dtbcwk_khz;
	dto_pawams.otg_inst = otg_inst;
	dto_pawams.pixcwk_khz = pixcwk_khz;
	dto_pawams.is_hdmi = twue;

	dccg35_set_dtbcwk_dto(dccg, &dto_pawams);
}

static void dccg35_dpp_woot_cwock_contwow(
		stwuct dccg *dccg,
		unsigned int dpp_inst,
		boow cwock_on)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->dpp_cwock_gated[dpp_inst] == cwock_on)
		wetuwn;

	if (cwock_on) {
		/* tuwn off the DTO and weave phase/moduwo at max */
		dcn35_set_dppcwk_enabwe(dccg, dpp_inst, 0);
		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
			  DPPCWK0_DTO_PHASE, 0xFF,
			  DPPCWK0_DTO_MODUWO, 0xFF);
	} ewse {
		dcn35_set_dppcwk_enabwe(dccg, dpp_inst, 1);
		/* tuwn on the DTO to genewate a 0hz cwock */
		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
			  DPPCWK0_DTO_PHASE, 0,
			  DPPCWK0_DTO_MODUWO, 1);
	}

	dccg->dpp_cwock_gated[dpp_inst] = !cwock_on;
}

static void dccg35_disabwe_symcwk32_se(
		stwuct dccg *dccg,
		int hpo_se_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* set wefcwk as the souwce fow symcwk32_se */
	switch (hpo_se_inst) {
	case 0:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE0_SWC_SEW, 0,
				SYMCWK32_SE0_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se) {
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE0_GATE_DISABWE, 0);
//			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
//					SYMCWK32_WOOT_SE0_GATE_DISABWE, 0);
		}
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE1_SWC_SEW, 0,
				SYMCWK32_SE1_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se) {
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE1_GATE_DISABWE, 0);
//			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
//					SYMCWK32_WOOT_SE1_GATE_DISABWE, 0);
		}
		bweak;
	case 2:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE2_SWC_SEW, 0,
				SYMCWK32_SE2_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se) {
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE2_GATE_DISABWE, 0);
//			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
//					SYMCWK32_WOOT_SE2_GATE_DISABWE, 0);
		}
		bweak;
	case 3:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE3_SWC_SEW, 0,
				SYMCWK32_SE3_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se) {
			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE3_GATE_DISABWE, 0);
//			WEG_UPDATE(DCCG_GATE_DISABWE_CNTW3,
//					SYMCWK32_WOOT_SE3_GATE_DISABWE, 0);
		}
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg35_init(stwuct dccg *dccg)
{
	int otg_inst;
	/* Set HPO stweam encodew to use wefcwk to avoid case whewe PHY is
	 * disabwed and SYMCWK32 fow HPO SE is souwced fwom PHYD32CWK which
	 * wiww cause DCN to hang.
	 */
	fow (otg_inst = 0; otg_inst < 4; otg_inst++)
		dccg35_disabwe_symcwk32_se(dccg, otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_we)
		fow (otg_inst = 0; otg_inst < 2; otg_inst++)
			dccg31_disabwe_symcwk32_we(dccg, otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.dpstweam)
		fow (otg_inst = 0; otg_inst < 4; otg_inst++)
			dccg314_set_dpstweamcwk(dccg, WEFCWK, otg_inst,
						otg_inst);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
		fow (otg_inst = 0; otg_inst < 5; otg_inst++)
			dccg35_set_physymcwk_woot_cwock_gating(dccg, otg_inst,
					fawse);
/*
	dccg35_enabwe_gwobaw_fgcg_wep(
		dccg, dccg->ctx->dc->debug.enabwe_fine_gwain_cwock_gating.bits
			      .dccg_gwobaw_fgcg_wep);*/
}

void dccg35_enabwe_gwobaw_fgcg_wep(stwuct dccg *dccg, boow vawue)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE(DCCG_GWOBAW_FGCG_WEP_CNTW, DCCG_GWOBAW_FGCG_WEP_DIS, !vawue);
}

static void dccg35_enabwe_dsccwk(stwuct dccg *dccg, int inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	//Disabwe DTO
	switch (inst) {
	case 0:
		WEG_UPDATE_2(DSCCWK0_DTO_PAWAM,
				DSCCWK0_DTO_PHASE, 0,
				DSCCWK0_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW,	DSCCWK0_EN, 1);
		bweak;
	case 1:
		WEG_UPDATE_2(DSCCWK1_DTO_PAWAM,
				DSCCWK1_DTO_PHASE, 0,
				DSCCWK1_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK1_EN, 1);
		bweak;
	case 2:
		WEG_UPDATE_2(DSCCWK2_DTO_PAWAM,
				DSCCWK2_DTO_PHASE, 0,
				DSCCWK2_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK2_EN, 1);
		bweak;
	case 3:
		WEG_UPDATE_2(DSCCWK3_DTO_PAWAM,
				DSCCWK3_DTO_PHASE, 0,
				DSCCWK3_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK3_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static void dccg35_disabwe_dsccwk(stwuct dccg *dccg,
				int inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (!dccg->ctx->dc->debug.woot_cwock_optimization.bits.dsc)
		wetuwn;

	switch (inst) {
	case 0:
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK0_EN, 0);
		WEG_UPDATE_2(DSCCWK0_DTO_PAWAM,
				DSCCWK0_DTO_PHASE, 0,
				DSCCWK0_DTO_MODUWO, 1);
		bweak;
	case 1:
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK1_EN, 0);
		WEG_UPDATE_2(DSCCWK1_DTO_PAWAM,
				DSCCWK1_DTO_PHASE, 0,
				DSCCWK1_DTO_MODUWO, 1);
		bweak;
	case 2:
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK2_EN, 0);
		WEG_UPDATE_2(DSCCWK2_DTO_PAWAM,
				DSCCWK2_DTO_PHASE, 0,
				DSCCWK2_DTO_MODUWO, 1);
		bweak;
	case 3:
		WEG_UPDATE(DSCCWK_DTO_CTWW, DSCCWK3_EN, 0);
		WEG_UPDATE_2(DSCCWK3_DTO_PAWAM,
				DSCCWK3_DTO_PHASE, 0,
				DSCCWK3_DTO_MODUWO, 1);
		bweak;
	defauwt:
		wetuwn;
	}
}

static void dccg35_enabwe_symcwk_se(stwuct dccg *dccg, uint32_t stweam_enc_inst, uint32_t wink_enc_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	switch (wink_enc_inst) {
	case 0:
		WEG_UPDATE(SYMCWKA_CWOCK_ENABWE,
				SYMCWKA_CWOCK_ENABWE, 1);
		bweak;
	case 1:
		WEG_UPDATE(SYMCWKB_CWOCK_ENABWE,
				SYMCWKB_CWOCK_ENABWE, 1);
		bweak;
	case 2:
		WEG_UPDATE(SYMCWKC_CWOCK_ENABWE,
				SYMCWKC_CWOCK_ENABWE, 1);
		bweak;
	case 3:
		WEG_UPDATE(SYMCWKD_CWOCK_ENABWE,
				SYMCWKD_CWOCK_ENABWE, 1);
		bweak;
	case 4:
		WEG_UPDATE(SYMCWKE_CWOCK_ENABWE,
				SYMCWKE_CWOCK_ENABWE, 1);
		bweak;
	}

	switch (stweam_enc_inst) {
	case 0:
		WEG_UPDATE_2(SYMCWKA_CWOCK_ENABWE,
				SYMCWKA_FE_EN, 1,
				SYMCWKA_FE_SWC_SEW, wink_enc_inst);
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWKB_CWOCK_ENABWE,
				SYMCWKB_FE_EN, 1,
				SYMCWKB_FE_SWC_SEW, wink_enc_inst);
		bweak;
	case 2:
		WEG_UPDATE_2(SYMCWKC_CWOCK_ENABWE,
				SYMCWKC_FE_EN, 1,
				SYMCWKC_FE_SWC_SEW, wink_enc_inst);
		bweak;
	case 3:
		WEG_UPDATE_2(SYMCWKD_CWOCK_ENABWE,
				SYMCWKD_FE_EN, 1,
				SYMCWKD_FE_SWC_SEW, wink_enc_inst);
		bweak;
	case 4:
		WEG_UPDATE_2(SYMCWKE_CWOCK_ENABWE,
				SYMCWKE_FE_EN, 1,
				SYMCWKE_FE_SWC_SEW, wink_enc_inst);
		bweak;
	}
}

/*get othew fwont end connected to this backend*/
static uint8_t dccg35_get_othew_enabwed_symcwk_fe(stwuct dccg *dccg, uint32_t stweam_enc_inst, uint32_t wink_enc_inst)
{
	uint8_t num_enabwed_symcwk_fe = 0;
	uint32_t be_cwk_en = 0, fe_cwk_en[5] = {0}, be_cwk_sew[5] = {0};
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	switch (wink_enc_inst) {
	case 0:
		WEG_GET_3(SYMCWKA_CWOCK_ENABWE, SYMCWKA_CWOCK_ENABWE, &be_cwk_en,
				SYMCWKA_FE_EN, &fe_cwk_en[0],
				SYMCWKA_FE_SWC_SEW, &be_cwk_sew[0]);
				bweak;
	case 1:
		WEG_GET_3(SYMCWKB_CWOCK_ENABWE, SYMCWKB_CWOCK_ENABWE, &be_cwk_en,
				SYMCWKB_FE_EN, &fe_cwk_en[1],
				SYMCWKB_FE_SWC_SEW, &be_cwk_sew[1]);
				bweak;
	case 2:
			WEG_GET_3(SYMCWKC_CWOCK_ENABWE, SYMCWKC_CWOCK_ENABWE, &be_cwk_en,
				SYMCWKC_FE_EN, &fe_cwk_en[2],
				SYMCWKC_FE_SWC_SEW, &be_cwk_sew[2]);
				bweak;
	case 3:
			WEG_GET_3(SYMCWKD_CWOCK_ENABWE, SYMCWKD_CWOCK_ENABWE, &be_cwk_en,
				SYMCWKD_FE_EN, &fe_cwk_en[3],
				SYMCWKD_FE_SWC_SEW, &be_cwk_sew[3]);
				bweak;
	case 4:
			WEG_GET_3(SYMCWKE_CWOCK_ENABWE, SYMCWKE_CWOCK_ENABWE, &be_cwk_en,
				SYMCWKE_FE_EN, &fe_cwk_en[4],
				SYMCWKE_FE_SWC_SEW, &be_cwk_sew[4]);
				bweak;
	}
	if (be_cwk_en) {
	/* fow DPMST, this backend couwd be used by muwtipwe fwont end.
	onwy disabwe the backend if this stweam_enc_ins is the wast active stweam enc connected to this back_end*/
		uint8_t i;
		fow (i = 0; i != wink_enc_inst && i < sizeof(fe_cwk_en); i++) {
			if (fe_cwk_en[i] && be_cwk_sew[i] == wink_enc_inst)
				num_enabwed_symcwk_fe++;
		}
	}
	wetuwn num_enabwed_symcwk_fe;
}

static void dccg35_disabwe_symcwk_se(stwuct dccg *dccg, uint32_t stweam_enc_inst, uint32_t wink_enc_inst)
{
	uint8_t num_enabwed_symcwk_fe = 0;
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	switch (stweam_enc_inst) {
	case 0:
		WEG_UPDATE_2(SYMCWKA_CWOCK_ENABWE,
				SYMCWKA_FE_EN, 0,
				SYMCWKA_FE_SWC_SEW, 0);
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWKB_CWOCK_ENABWE,
				SYMCWKB_FE_EN, 0,
				SYMCWKB_FE_SWC_SEW, 0);
		bweak;
	case 2:
		WEG_UPDATE_2(SYMCWKC_CWOCK_ENABWE,
				SYMCWKC_FE_EN, 0,
				SYMCWKC_FE_SWC_SEW, 0);
		bweak;
	case 3:
		WEG_UPDATE_2(SYMCWKD_CWOCK_ENABWE,
				SYMCWKD_FE_EN, 0,
				SYMCWKD_FE_SWC_SEW, 0);
		bweak;
	case 4:
		WEG_UPDATE_2(SYMCWKE_CWOCK_ENABWE,
				SYMCWKE_FE_EN, 0,
				SYMCWKE_FE_SWC_SEW, 0);
		bweak;
	}

	/*check othew enabwed symcwk fe */
	num_enabwed_symcwk_fe = dccg35_get_othew_enabwed_symcwk_fe(dccg, stweam_enc_inst, wink_enc_inst);
	/*onwy tuwn off backend cwk if othew fwont end attachecd to this backend awe aww off,
	 fow mst, onwy tuwn off the backend if this is the wast fwont end*/
	if (num_enabwed_symcwk_fe == 0) {
		switch (wink_enc_inst) {
		case 0:
			WEG_UPDATE(SYMCWKA_CWOCK_ENABWE,
					SYMCWKA_CWOCK_ENABWE, 0);
			bweak;
		case 1:
			WEG_UPDATE(SYMCWKB_CWOCK_ENABWE,
					SYMCWKB_CWOCK_ENABWE, 0);
			bweak;
		case 2:
			WEG_UPDATE(SYMCWKC_CWOCK_ENABWE,
					SYMCWKC_CWOCK_ENABWE, 0);
			bweak;
		case 3:
			WEG_UPDATE(SYMCWKD_CWOCK_ENABWE,
					SYMCWKD_CWOCK_ENABWE, 0);
			bweak;
		case 4:
			WEG_UPDATE(SYMCWKE_CWOCK_ENABWE,
					SYMCWKE_CWOCK_ENABWE, 0);
			bweak;
		}
	}
}

static const stwuct dccg_funcs dccg35_funcs = {
	.update_dpp_dto = dccg35_update_dpp_dto,
	.dpp_woot_cwock_contwow = dccg35_dpp_woot_cwock_contwow,
	.get_dccg_wef_fweq = dccg31_get_dccg_wef_fweq,
	.dccg_init = dccg35_init,
	.set_dpstweamcwk = dccg35_set_dpstweamcwk,
	.enabwe_symcwk32_se = dccg31_enabwe_symcwk32_se,
	.disabwe_symcwk32_se = dccg35_disabwe_symcwk32_se,
	.enabwe_symcwk32_we = dccg31_enabwe_symcwk32_we,
	.disabwe_symcwk32_we = dccg31_disabwe_symcwk32_we,
	.set_symcwk32_we_woot_cwock_gating = dccg31_set_symcwk32_we_woot_cwock_gating,
	.set_physymcwk = dccg35_set_physymcwk,
	.set_physymcwk_woot_cwock_gating = dccg35_set_physymcwk_woot_cwock_gating,
	.set_dtbcwk_dto = dccg35_set_dtbcwk_dto,
	.set_audio_dtbcwk_dto = dccg31_set_audio_dtbcwk_dto,
	.set_fifo_ewwdet_ovw_en = dccg2_set_fifo_ewwdet_ovw_en,
	.otg_add_pixew = dccg31_otg_add_pixew,
	.otg_dwop_pixew = dccg31_otg_dwop_pixew,
	.set_dispcwk_change_mode = dccg31_set_dispcwk_change_mode,
	.disabwe_dsc = dccg35_disabwe_dsccwk,
	.enabwe_dsc = dccg35_enabwe_dsccwk,
	.set_pixew_wate_div = dccg35_set_pixew_wate_div,
	.set_vawid_pixew_wate = dccg35_set_vawid_pixew_wate,
	.enabwe_symcwk_se = dccg35_enabwe_symcwk_se,
	.disabwe_symcwk_se = dccg35_disabwe_symcwk_se,
	.set_dtbcwk_p_swc = dccg35_set_dtbcwk_p_swc,
};

stwuct dccg *dccg35_cweate(
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
	base->funcs = &dccg35_funcs;

	dccg_dcn->wegs = wegs;
	dccg_dcn->dccg_shift = dccg_shift;
	dccg_dcn->dccg_mask = dccg_mask;

	wetuwn &dccg_dcn->base;
}
