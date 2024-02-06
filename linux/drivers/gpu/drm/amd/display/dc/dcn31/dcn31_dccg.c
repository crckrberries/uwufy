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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dcn31_dccg.h"
#incwude "daw_asic_id.h"

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

void dccg31_update_dpp_dto(stwuct dccg *dccg, int dpp_inst, int weq_dppcwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->dpp_cwock_gated[dpp_inst]) {
		/*
		 * Do not update the DPPCWK DTO if the cwock is stopped.
		 * It is tweated the same as if the pipe itsewf wewe in PG.
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
		WEG_UPDATE(DPPCWK_DTO_CTWW,
				DPPCWK_DTO_ENABWE[dpp_inst], 1);
	} ewse {
		WEG_UPDATE(DPPCWK_DTO_CTWW,
				DPPCWK_DTO_ENABWE[dpp_inst], 0);
	}
	dccg->pipe_dppcwk_khz[dpp_inst] = weq_dppcwk;
}

static enum phyd32cwk_cwock_souwce get_phy_mux_symcwk(
		stwuct dcn_dccg *dccg_dcn,
		enum phyd32cwk_cwock_souwce swc)
{
	if (dccg_dcn->base.ctx->asic_id.chip_famiwy == FAMIWY_YEWWOW_CAWP &&
			dccg_dcn->base.ctx->asic_id.hw_intewnaw_wev == YEWWOW_CAWP_B0) {
		if (swc == PHYD32CWKC)
			swc = PHYD32CWKF;
		if (swc == PHYD32CWKD)
			swc = PHYD32CWKG;
	}
	wetuwn swc;
}

static void dccg31_enabwe_dpstweamcwk(stwuct dccg *dccg, int otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* enabwed to sewect one of the DTBCWKs fow pipe */
	switch (otg_inst) {
	case 0:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE0_EN, 1);
		bweak;
	case 1:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE1_EN, 1);
		bweak;
	case 2:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE2_EN, 1);
		bweak;
	case 3:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE3_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.dpstweam)
		WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
			DPSTWEAMCWK_GATE_DISABWE, 1,
			DPSTWEAMCWK_WOOT_GATE_DISABWE, 1);
}

static void dccg31_disabwe_dpstweamcwk(stwuct dccg *dccg, int otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.dpstweam)
		WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
				DPSTWEAMCWK_WOOT_GATE_DISABWE, 0,
				DPSTWEAMCWK_GATE_DISABWE, 0);

	switch (otg_inst) {
	case 0:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE0_EN, 0);
		bweak;
	case 1:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE1_EN, 0);
		bweak;
	case 2:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE2_EN, 0);
		bweak;
	case 3:
		WEG_UPDATE(DPSTWEAMCWK_CNTW,
				DPSTWEAMCWK_PIPE3_EN, 0);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_set_dpstweamcwk(
		stwuct dccg *dccg,
		enum stweamcwk_souwce swc,
		int otg_inst,
		int dp_hpo_inst)
{
	if (swc == WEFCWK)
		dccg31_disabwe_dpstweamcwk(dccg, otg_inst);
	ewse
		dccg31_enabwe_dpstweamcwk(dccg, otg_inst);
}

void dccg31_enabwe_symcwk32_se(
		stwuct dccg *dccg,
		int hpo_se_inst,
		enum phyd32cwk_cwock_souwce phyd32cwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	phyd32cwk = get_phy_mux_symcwk(dccg_dcn, phyd32cwk);

	/* sewect one of the PHYD32CWKs as the souwce fow symcwk32_se */
	switch (hpo_se_inst) {
	case 0:
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE0_GATE_DISABWE, 1,
					SYMCWK32_WOOT_SE0_GATE_DISABWE, 1);
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE0_SWC_SEW, phyd32cwk,
				SYMCWK32_SE0_EN, 1);
		bweak;
	case 1:
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE1_GATE_DISABWE, 1,
					SYMCWK32_WOOT_SE1_GATE_DISABWE, 1);
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE1_SWC_SEW, phyd32cwk,
				SYMCWK32_SE1_EN, 1);
		bweak;
	case 2:
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE2_GATE_DISABWE, 1,
					SYMCWK32_WOOT_SE2_GATE_DISABWE, 1);
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE2_SWC_SEW, phyd32cwk,
				SYMCWK32_SE2_EN, 1);
		bweak;
	case 3:
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE3_GATE_DISABWE, 1,
					SYMCWK32_WOOT_SE3_GATE_DISABWE, 1);
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE3_SWC_SEW, phyd32cwk,
				SYMCWK32_SE3_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_disabwe_symcwk32_se(
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
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE0_GATE_DISABWE, 0,
					SYMCWK32_WOOT_SE0_GATE_DISABWE, 0);
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE1_SWC_SEW, 0,
				SYMCWK32_SE1_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE1_GATE_DISABWE, 0,
					SYMCWK32_WOOT_SE1_GATE_DISABWE, 0);
		bweak;
	case 2:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE2_SWC_SEW, 0,
				SYMCWK32_SE2_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE2_GATE_DISABWE, 0,
					SYMCWK32_WOOT_SE2_GATE_DISABWE, 0);
		bweak;
	case 3:
		WEG_UPDATE_2(SYMCWK32_SE_CNTW,
				SYMCWK32_SE3_SWC_SEW, 0,
				SYMCWK32_SE3_EN, 0);
		if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_se)
			WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
					SYMCWK32_SE3_GATE_DISABWE, 0,
					SYMCWK32_WOOT_SE3_GATE_DISABWE, 0);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_enabwe_symcwk32_we(
		stwuct dccg *dccg,
		int hpo_we_inst,
		enum phyd32cwk_cwock_souwce phyd32cwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	phyd32cwk = get_phy_mux_symcwk(dccg_dcn, phyd32cwk);

	/* sewect one of the PHYD32CWKs as the souwce fow symcwk32_we */
	switch (hpo_we_inst) {
	case 0:
		WEG_UPDATE_2(SYMCWK32_WE_CNTW,
				SYMCWK32_WE0_SWC_SEW, phyd32cwk,
				SYMCWK32_WE0_EN, 1);
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWK32_WE_CNTW,
				SYMCWK32_WE1_SWC_SEW, phyd32cwk,
				SYMCWK32_WE1_EN, 1);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_disabwe_symcwk32_we(
		stwuct dccg *dccg,
		int hpo_we_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	/* set wefcwk as the souwce fow symcwk32_we */
	switch (hpo_we_inst) {
	case 0:
		WEG_UPDATE_2(SYMCWK32_WE_CNTW,
				SYMCWK32_WE0_SWC_SEW, 0,
				SYMCWK32_WE0_EN, 0);
		bweak;
	case 1:
		WEG_UPDATE_2(SYMCWK32_WE_CNTW,
				SYMCWK32_WE1_SWC_SEW, 0,
				SYMCWK32_WE1_EN, 0);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_set_symcwk32_we_woot_cwock_gating(
		stwuct dccg *dccg,
		int hpo_we_inst,
		boow enabwe)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (!dccg->ctx->dc->debug.woot_cwock_optimization.bits.symcwk32_we)
		wetuwn;

	switch (hpo_we_inst) {
	case 0:
		WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
				SYMCWK32_WE0_GATE_DISABWE, enabwe ? 1 : 0,
				SYMCWK32_WOOT_WE0_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	case 1:
		WEG_UPDATE_2(DCCG_GATE_DISABWE_CNTW3,
				SYMCWK32_WE1_GATE_DISABWE, enabwe ? 1 : 0,
				SYMCWK32_WOOT_WE1_GATE_DISABWE, enabwe ? 1 : 0);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_disabwe_dsccwk(stwuct dccg *dccg, int inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (!dccg->ctx->dc->debug.woot_cwock_optimization.bits.dsc)
		wetuwn;
	//DTO must be enabwed to genewate a 0 Hz cwock output
	switch (inst) {
	case 0:
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK0_DTO_ENABWE, 1);
		WEG_UPDATE_2(DSCCWK0_DTO_PAWAM,
				DSCCWK0_DTO_PHASE, 0,
				DSCCWK0_DTO_MODUWO, 1);
		bweak;
	case 1:
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK1_DTO_ENABWE, 1);
		WEG_UPDATE_2(DSCCWK1_DTO_PAWAM,
				DSCCWK1_DTO_PHASE, 0,
				DSCCWK1_DTO_MODUWO, 1);
		bweak;
	case 2:
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK2_DTO_ENABWE, 1);
		WEG_UPDATE_2(DSCCWK2_DTO_PAWAM,
				DSCCWK2_DTO_PHASE, 0,
				DSCCWK2_DTO_MODUWO, 1);
		bweak;
	case 3:
		if (WEG(DSCCWK3_DTO_PAWAM)) {
			WEG_UPDATE(DSCCWK_DTO_CTWW,
					DSCCWK3_DTO_ENABWE, 1);
			WEG_UPDATE_2(DSCCWK3_DTO_PAWAM,
					DSCCWK3_DTO_PHASE, 0,
					DSCCWK3_DTO_MODUWO, 1);
		}
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_enabwe_dsccwk(stwuct dccg *dccg, int inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (!dccg->ctx->dc->debug.woot_cwock_optimization.bits.dsc)
		wetuwn;
	//Disabwe DTO
	switch (inst) {
	case 0:
		WEG_UPDATE_2(DSCCWK0_DTO_PAWAM,
				DSCCWK0_DTO_PHASE, 0,
				DSCCWK0_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK0_DTO_ENABWE, 0);
		bweak;
	case 1:
		WEG_UPDATE_2(DSCCWK1_DTO_PAWAM,
				DSCCWK1_DTO_PHASE, 0,
				DSCCWK1_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK1_DTO_ENABWE, 0);
		bweak;
	case 2:
		WEG_UPDATE_2(DSCCWK2_DTO_PAWAM,
				DSCCWK2_DTO_PHASE, 0,
				DSCCWK2_DTO_MODUWO, 0);
		WEG_UPDATE(DSCCWK_DTO_CTWW,
				DSCCWK2_DTO_ENABWE, 0);
		bweak;
	case 3:
		if (WEG(DSCCWK3_DTO_PAWAM)) {
			WEG_UPDATE(DSCCWK_DTO_CTWW,
					DSCCWK3_DTO_ENABWE, 0);
			WEG_UPDATE_2(DSCCWK3_DTO_PAWAM,
					DSCCWK3_DTO_PHASE, 0,
					DSCCWK3_DTO_MODUWO, 0);
		}
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

void dccg31_set_physymcwk(
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
					PHYASYMCWK_FOWCE_EN, 1,
					PHYASYMCWK_FOWCE_SWC_SEW, cwk_swc);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYASYMCWK_GATE_DISABWE, 1);
		} ewse {
			WEG_UPDATE_2(PHYASYMCWK_CWOCK_CNTW,
					PHYASYMCWK_FOWCE_EN, 0,
					PHYASYMCWK_FOWCE_SWC_SEW, 0);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYASYMCWK_GATE_DISABWE, 0);
		}
		bweak;
	case 1:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYBSYMCWK_CWOCK_CNTW,
					PHYBSYMCWK_FOWCE_EN, 1,
					PHYBSYMCWK_FOWCE_SWC_SEW, cwk_swc);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYBSYMCWK_GATE_DISABWE, 1);
		} ewse {
			WEG_UPDATE_2(PHYBSYMCWK_CWOCK_CNTW,
					PHYBSYMCWK_FOWCE_EN, 0,
					PHYBSYMCWK_FOWCE_SWC_SEW, 0);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYBSYMCWK_GATE_DISABWE, 0);
		}
		bweak;
	case 2:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYCSYMCWK_CWOCK_CNTW,
					PHYCSYMCWK_FOWCE_EN, 1,
					PHYCSYMCWK_FOWCE_SWC_SEW, cwk_swc);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYCSYMCWK_GATE_DISABWE, 1);
		} ewse {
			WEG_UPDATE_2(PHYCSYMCWK_CWOCK_CNTW,
					PHYCSYMCWK_FOWCE_EN, 0,
					PHYCSYMCWK_FOWCE_SWC_SEW, 0);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYCSYMCWK_GATE_DISABWE, 0);
		}
		bweak;
	case 3:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYDSYMCWK_CWOCK_CNTW,
					PHYDSYMCWK_FOWCE_EN, 1,
					PHYDSYMCWK_FOWCE_SWC_SEW, cwk_swc);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYDSYMCWK_GATE_DISABWE, 1);
		} ewse {
			WEG_UPDATE_2(PHYDSYMCWK_CWOCK_CNTW,
					PHYDSYMCWK_FOWCE_EN, 0,
					PHYDSYMCWK_FOWCE_SWC_SEW, 0);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYDSYMCWK_GATE_DISABWE, 0);
		}
		bweak;
	case 4:
		if (fowce_enabwe) {
			WEG_UPDATE_2(PHYESYMCWK_CWOCK_CNTW,
					PHYESYMCWK_FOWCE_EN, 1,
					PHYESYMCWK_FOWCE_SWC_SEW, cwk_swc);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYESYMCWK_GATE_DISABWE, 1);
		} ewse {
			WEG_UPDATE_2(PHYESYMCWK_CWOCK_CNTW,
					PHYESYMCWK_FOWCE_EN, 0,
					PHYESYMCWK_FOWCE_SWC_SEW, 0);
			if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk)
				WEG_UPDATE(DCCG_GATE_DISABWE_CNTW2,
					PHYESYMCWK_GATE_DISABWE, 0);
		}
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

/* Contwows the genewation of pixew vawid fow OTG in (OTG -> HPO case) */
void dccg31_set_dtbcwk_dto(
		stwuct dccg *dccg,
		const stwuct dtbcwk_dto_pawams *pawams)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	int weq_dtbcwk_khz = pawams->pixcwk_khz;
	uint32_t dtbdto_div;

	/* Mode	                DTBDTO Wate       DTBCWK_DTO<x>_DIV Wegistew
	 * ODM 4:1 combine      pixew wate/4      2
	 * ODM 2:1 combine      pixew wate/2      4
	 * non-DSC 4:2:0 mode   pixew wate/2      4
	 * DSC native 4:2:0     pixew wate/2      4
	 * DSC native 4:2:2     pixew wate/2      4
	 * Othew modes          pixew wate        8
	 */
	if (pawams->num_odm_segments == 4) {
		dtbdto_div = 2;
		weq_dtbcwk_khz = pawams->pixcwk_khz / 4;
	} ewse if ((pawams->num_odm_segments == 2) ||
			(pawams->timing->pixew_encoding == PIXEW_ENCODING_YCBCW420) ||
			(pawams->timing->fwags.DSC && pawams->timing->pixew_encoding == PIXEW_ENCODING_YCBCW422
					&& !pawams->timing->dsc_cfg.ycbcw422_simpwe)) {
		dtbdto_div = 4;
		weq_dtbcwk_khz = pawams->pixcwk_khz / 2;
	} ewse
		dtbdto_div = 8;

	if (pawams->wef_dtbcwk_khz && weq_dtbcwk_khz) {
		uint32_t moduwo, phase;

		// phase / moduwo = dtbcwk / dtbcwk wef
		moduwo = pawams->wef_dtbcwk_khz * 1000;
		phase = div_u64((((unsigned wong wong)moduwo * weq_dtbcwk_khz) + pawams->wef_dtbcwk_khz - 1),
				pawams->wef_dtbcwk_khz);

		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_DIV[pawams->otg_inst], dtbdto_div);

		WEG_WWITE(DTBCWK_DTO_MODUWO[pawams->otg_inst], moduwo);
		WEG_WWITE(DTBCWK_DTO_PHASE[pawams->otg_inst], phase);

		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_ENABWE[pawams->otg_inst], 1);

		WEG_WAIT(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWKDTO_ENABWE_STATUS[pawams->otg_inst], 1,
				1, 100);

		/* The wecommended pwogwamming sequence to enabwe DTBCWK DTO to genewate
		 * vawid pixew HPO DPSTWEAM ENCODEW, specifies that DTO souwce sewect shouwd
		 * be set onwy aftew DTO is enabwed
		 */
		WEG_UPDATE(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				PIPE_DTO_SWC_SEW[pawams->otg_inst], 1);
	} ewse {
		WEG_UPDATE_3(OTG_PIXEW_WATE_CNTW[pawams->otg_inst],
				DTBCWK_DTO_ENABWE[pawams->otg_inst], 0,
				PIPE_DTO_SWC_SEW[pawams->otg_inst], 0,
				DTBCWK_DTO_DIV[pawams->otg_inst], dtbdto_div);

		WEG_WWITE(DTBCWK_DTO_MODUWO[pawams->otg_inst], 0);
		WEG_WWITE(DTBCWK_DTO_PHASE[pawams->otg_inst], 0);
	}
}

void dccg31_set_audio_dtbcwk_dto(
		stwuct dccg *dccg,
		const stwuct dtbcwk_dto_pawams *pawams)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (pawams->wef_dtbcwk_khz && pawams->weq_audio_dtbcwk_khz) {
		uint32_t moduwo, phase;

		// phase / moduwo = dtbcwk / dtbcwk wef
		moduwo = pawams->wef_dtbcwk_khz * 1000;
		phase = div_u64((((unsigned wong wong)moduwo * pawams->weq_audio_dtbcwk_khz) + pawams->wef_dtbcwk_khz - 1),
			pawams->wef_dtbcwk_khz);


		WEG_WWITE(DCCG_AUDIO_DTBCWK_DTO_MODUWO, moduwo);
		WEG_WWITE(DCCG_AUDIO_DTBCWK_DTO_PHASE, phase);

		//WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
		//		DCCG_AUDIO_DTBCWK_DTO_USE_512FBW_DTO, 1);

		WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 4);  //  04 - DCCG_AUDIO_DTO_SEW_AUDIO_DTO_DTBCWK
	} ewse {
		WEG_WWITE(DCCG_AUDIO_DTBCWK_DTO_PHASE, 0);
		WEG_WWITE(DCCG_AUDIO_DTBCWK_DTO_MODUWO, 0);

		WEG_UPDATE(DCCG_AUDIO_DTO_SOUWCE,
				DCCG_AUDIO_DTO_SEW, 3);  //  03 - DCCG_AUDIO_DTO_SEW_NO_AUDIO_DTO
	}
}

void dccg31_get_dccg_wef_fweq(stwuct dccg *dccg,
		unsigned int xtawin_fweq_inKhz,
		unsigned int *dccg_wef_fweq_inKhz)
{
	/*
	 * Assume wefcwk is souwced fwom xtawin
	 * expect 24MHz
	 */
	*dccg_wef_fweq_inKhz = xtawin_fweq_inKhz;
	wetuwn;
}

void dccg31_set_dispcwk_change_mode(
	stwuct dccg *dccg,
	enum dentist_dispcwk_change_mode change_mode)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE(DENTIST_DISPCWK_CNTW, DENTIST_DISPCWK_CHG_MODE,
		   change_mode == DISPCWK_CHANGE_MODE_WAMPING ? 2 : 0);
}

void dccg31_init(stwuct dccg *dccg)
{
	/* Set HPO stweam encodew to use wefcwk to avoid case whewe PHY is
	 * disabwed and SYMCWK32 fow HPO SE is souwced fwom PHYD32CWK which
	 * wiww cause DCN to hang.
	 */
	dccg31_disabwe_symcwk32_se(dccg, 0);
	dccg31_disabwe_symcwk32_se(dccg, 1);
	dccg31_disabwe_symcwk32_se(dccg, 2);
	dccg31_disabwe_symcwk32_se(dccg, 3);

	dccg31_set_symcwk32_we_woot_cwock_gating(dccg, 0, fawse);
	dccg31_set_symcwk32_we_woot_cwock_gating(dccg, 1, fawse);

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.dpstweam) {
		dccg31_disabwe_dpstweamcwk(dccg, 0);
		dccg31_disabwe_dpstweamcwk(dccg, 1);
		dccg31_disabwe_dpstweamcwk(dccg, 2);
		dccg31_disabwe_dpstweamcwk(dccg, 3);
	}

	if (dccg->ctx->dc->debug.woot_cwock_optimization.bits.physymcwk) {
		dccg31_set_physymcwk(dccg, 0, PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
		dccg31_set_physymcwk(dccg, 1, PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
		dccg31_set_physymcwk(dccg, 2, PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
		dccg31_set_physymcwk(dccg, 3, PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
		dccg31_set_physymcwk(dccg, 4, PHYSYMCWK_FOWCE_SWC_SYMCWK, fawse);
	}
}

void dccg31_otg_add_pixew(stwuct dccg *dccg,
				 uint32_t otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_ADD_PIXEW[otg_inst], 1);
}

void dccg31_otg_dwop_pixew(stwuct dccg *dccg,
				  uint32_t otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_DWOP_PIXEW[otg_inst], 1);
}

static const stwuct dccg_funcs dccg31_funcs = {
	.update_dpp_dto = dccg31_update_dpp_dto,
	.get_dccg_wef_fweq = dccg31_get_dccg_wef_fweq,
	.dccg_init = dccg31_init,
	.set_dpstweamcwk = dccg31_set_dpstweamcwk,
	.enabwe_symcwk32_se = dccg31_enabwe_symcwk32_se,
	.disabwe_symcwk32_se = dccg31_disabwe_symcwk32_se,
	.enabwe_symcwk32_we = dccg31_enabwe_symcwk32_we,
	.disabwe_symcwk32_we = dccg31_disabwe_symcwk32_we,
	.set_physymcwk = dccg31_set_physymcwk,
	.set_dtbcwk_dto = dccg31_set_dtbcwk_dto,
	.set_audio_dtbcwk_dto = dccg31_set_audio_dtbcwk_dto,
	.set_fifo_ewwdet_ovw_en = dccg2_set_fifo_ewwdet_ovw_en,
	.otg_add_pixew = dccg31_otg_add_pixew,
	.otg_dwop_pixew = dccg31_otg_dwop_pixew,
	.set_dispcwk_change_mode = dccg31_set_dispcwk_change_mode,
	.disabwe_dsc = dccg31_disabwe_dsccwk,
	.enabwe_dsc = dccg31_enabwe_dsccwk,
};

stwuct dccg *dccg31_cweate(
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
	base->funcs = &dccg31_funcs;

	dccg_dcn->wegs = wegs;
	dccg_dcn->dccg_shift = dccg_shift;
	dccg_dcn->dccg_mask = dccg_mask;

	wetuwn &dccg_dcn->base;
}
