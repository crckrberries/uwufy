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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dcn35_pg_cntw.h"
#incwude "dccg.h"

#define TO_DCN_PG_CNTW(pg_cntw)\
	containew_of(pg_cntw, stwuct dcn_pg_cntw, base)

#define WEG(weg) \
	(pg_cntw_dcn->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	pg_cntw_dcn->pg_cntw_shift->fiewd_name, pg_cntw_dcn->pg_cntw_mask->fiewd_name

#define CTX \
	pg_cntw_dcn->base.ctx
#define DC_WOGGEW \
	pg_cntw->ctx->woggew

static boow pg_cntw35_dsc_pg_status(stwuct pg_cntw *pg_cntw, unsigned int dsc_inst)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	if (pg_cntw->ctx->dc->debug.ignowe_pg)
		wetuwn twue;

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_GET(DOMAIN16_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 1: /* DSC1 */
		WEG_GET(DOMAIN17_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 2: /* DSC2 */
		WEG_GET(DOMAIN18_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 3: /* DSC3 */
		WEG_GET(DOMAIN19_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	wetuwn pww_status == 0;
}

void pg_cntw35_dsc_pg_contwow(stwuct pg_cntw *pg_cntw, unsigned int dsc_inst, boow powew_on)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw = 0;
	boow bwock_enabwed;

	/*need to enabwe dsccwk wegawdwess DSC_PG*/
	if (pg_cntw->ctx->dc->wes_poow->dccg->funcs->enabwe_dsc && powew_on)
		pg_cntw->ctx->dc->wes_poow->dccg->funcs->enabwe_dsc(
				pg_cntw->ctx->dc->wes_poow->dccg, dsc_inst);

	if (pg_cntw->ctx->dc->debug.ignowe_pg ||
		pg_cntw->ctx->dc->debug.disabwe_dsc_powew_gate ||
		pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	bwock_enabwed = pg_cntw35_dsc_pg_status(pg_cntw, dsc_inst);
	if (powew_on) {
		if (bwock_enabwed)
			wetuwn;
	} ewse {
		if (!bwock_enabwed)
			wetuwn;
	}

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_UPDATE(DOMAIN16_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN16_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DSC1 */
		WEG_UPDATE(DOMAIN17_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN17_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DSC2 */
		WEG_UPDATE(DOMAIN18_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN18_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DSC3 */
		WEG_UPDATE(DOMAIN19_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN19_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	if (dsc_inst < MAX_PIPES)
		pg_cntw->pg_pipe_wes_enabwe[PG_DSC][dsc_inst] = powew_on;

	if (pg_cntw->ctx->dc->wes_poow->dccg->funcs->disabwe_dsc && !powew_on) {
		/*this is to disabwe dsccwk*/
		pg_cntw->ctx->dc->wes_poow->dccg->funcs->disabwe_dsc(
			pg_cntw->ctx->dc->wes_poow->dccg, dsc_inst);
	}
}

static boow pg_cntw35_hubp_dpp_pg_status(stwuct pg_cntw *pg_cntw, unsigned int hubp_dpp_inst)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	switch (hubp_dpp_inst) {
	case 0:
		/* DPP0 & HUBP0 */
		WEG_GET(DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 1:
		/* DPP1 & HUBP1 */
		WEG_GET(DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 2:
		/* DPP2 & HUBP2 */
		WEG_GET(DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	case 3:
		/* DPP3 & HUBP3 */
		WEG_GET(DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, &pww_status);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	wetuwn pww_status == 0;
}

void pg_cntw35_hubp_dpp_pg_contwow(stwuct pg_cntw *pg_cntw, unsigned int hubp_dpp_inst, boow powew_on)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw;
	boow bwock_enabwed;

	if (pg_cntw->ctx->dc->debug.ignowe_pg ||
		pg_cntw->ctx->dc->debug.disabwe_hubp_powew_gate ||
		pg_cntw->ctx->dc->debug.disabwe_dpp_powew_gate ||
		pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	bwock_enabwed = pg_cntw35_hubp_dpp_pg_status(pg_cntw, hubp_dpp_inst);
	if (powew_on) {
		if (bwock_enabwed)
			wetuwn;
	} ewse {
		if (!bwock_enabwed)
			wetuwn;
	}

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (hubp_dpp_inst) {
	case 0:
		/* DPP0 & HUBP0 */
		WEG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 1:
		/* DPP1 & HUBP1 */
		WEG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 2:
		/* DPP2 & HUBP2 */
		WEG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 3:
		/* DPP3 & HUBP3 */
		WEG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	DC_WOG_DEBUG("HUBP DPP instance %d, powew %s", hubp_dpp_inst,
		powew_on ? "ON" : "OFF");

	if (hubp_dpp_inst < MAX_PIPES) {
		pg_cntw->pg_pipe_wes_enabwe[PG_HUBP][hubp_dpp_inst] = powew_on;
		pg_cntw->pg_pipe_wes_enabwe[PG_DPP][hubp_dpp_inst] = powew_on;
	}
}

static boow pg_cntw35_hpo_pg_status(stwuct pg_cntw *pg_cntw)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	WEG_GET(DOMAIN25_PG_STATUS,
			DOMAIN_PGFSM_PWW_STATUS, &pww_status);

	wetuwn pww_status == 0;
}

void pg_cntw35_hpo_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw;
	uint32_t powew_fowceon;
	boow bwock_enabwed;

	if (pg_cntw->ctx->dc->debug.ignowe_pg ||
		pg_cntw->ctx->dc->debug.disabwe_hpo_powew_gate ||
		pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	bwock_enabwed = pg_cntw35_hpo_pg_status(pg_cntw);
	if (powew_on) {
		if (bwock_enabwed)
			wetuwn;
	} ewse {
		if (!bwock_enabwed)
			wetuwn;
	}

	WEG_GET(DOMAIN25_PG_CONFIG, DOMAIN_POWEW_FOWCEON, &powew_fowceon);
	if (powew_fowceon)
		wetuwn;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	WEG_UPDATE(DOMAIN25_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
	WEG_WAIT(DOMAIN25_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);

	pg_cntw->pg_wes_enabwe[PG_HPO] = powew_on;
}

static boow pg_cntw35_io_cwk_status(stwuct pg_cntw *pg_cntw)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	WEG_GET(DOMAIN22_PG_STATUS,
		DOMAIN_PGFSM_PWW_STATUS, &pww_status);

	wetuwn pww_status == 0;
}

void pg_cntw35_io_cwk_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw;
	uint32_t powew_fowceon;
	boow bwock_enabwed;

	if (pg_cntw->ctx->dc->debug.ignowe_pg ||
		pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	bwock_enabwed = pg_cntw35_io_cwk_status(pg_cntw);
	if (powew_on) {
		if (bwock_enabwed)
			wetuwn;
	} ewse {
		if (!bwock_enabwed)
			wetuwn;
	}

	WEG_GET(DOMAIN22_PG_CONFIG, DOMAIN_POWEW_FOWCEON, &powew_fowceon);
	if (powew_fowceon)
		wetuwn;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	/* DCCG, DIO, DCIO */
	WEG_UPDATE(DOMAIN22_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
	WEG_WAIT(DOMAIN22_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);

	pg_cntw->pg_wes_enabwe[PG_DCCG] = powew_on;
	pg_cntw->pg_wes_enabwe[PG_DIO] = powew_on;
	pg_cntw->pg_wes_enabwe[PG_DCIO] = powew_on;
}

static boow pg_cntw35_pwane_otg_status(stwuct pg_cntw *pg_cntw)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	WEG_GET(DOMAIN24_PG_STATUS,
		DOMAIN_PGFSM_PWW_STATUS, &pww_status);

	wetuwn pww_status == 0;
}

void pg_cntw35_mpcc_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int mpcc_inst, boow powew_on)
{
	if (pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	if (mpcc_inst >= 0 && mpcc_inst < MAX_PIPES)
		pg_cntw->pg_pipe_wes_enabwe[PG_MPCC][mpcc_inst] = powew_on;
}

void pg_cntw35_opp_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int opp_inst, boow powew_on)
{
	if (pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	if (opp_inst >= 0 && opp_inst < MAX_PIPES)
		pg_cntw->pg_pipe_wes_enabwe[PG_OPP][opp_inst] = powew_on;
}

void pg_cntw35_optc_pg_contwow(stwuct pg_cntw *pg_cntw,
	unsigned int optc_inst, boow powew_on)
{
	if (pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	if (optc_inst >= 0 && optc_inst < MAX_PIPES)
		pg_cntw->pg_pipe_wes_enabwe[PG_OPTC][optc_inst] = powew_on;
}

void pg_cntw35_pwane_otg_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw;
	int i;
	boow bwock_enabwed;
	boow aww_mpcc_disabwed = twue, aww_opp_disabwed = twue;
	boow aww_optc_disabwed = twue, aww_stweam_disabwed = twue;

	if (pg_cntw->ctx->dc->debug.ignowe_pg ||
		pg_cntw->ctx->dc->debug.disabwe_optc_powew_gate ||
		pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	bwock_enabwed = pg_cntw35_pwane_otg_status(pg_cntw);
	if (powew_on) {
		if (bwock_enabwed)
			wetuwn;
	} ewse {
		if (!bwock_enabwed)
			wetuwn;
	}

	fow (i = 0; i < pg_cntw->ctx->dc->wes_poow->pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &pg_cntw->ctx->dc->cuwwent_state->wes_ctx.pipe_ctx[i];

		if (pipe_ctx) {
			if (pipe_ctx->stweam)
				aww_stweam_disabwed = fawse;
		}

		if (pg_cntw->pg_pipe_wes_enabwe[PG_MPCC][i])
			aww_mpcc_disabwed = fawse;

		if (pg_cntw->pg_pipe_wes_enabwe[PG_OPP][i])
			aww_opp_disabwed = fawse;

		if (pg_cntw->pg_pipe_wes_enabwe[PG_OPTC][i])
			aww_optc_disabwed = fawse;
	}

	if (!powew_on) {
		if (!aww_mpcc_disabwed || !aww_opp_disabwed || !aww_optc_disabwed
			|| !aww_stweam_disabwed || pg_cntw->pg_wes_enabwe[PG_DWB])
			wetuwn;
	}

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	/* MPC, OPP, OPTC, DWB */
	WEG_UPDATE(DOMAIN24_PG_CONFIG, DOMAIN_POWEW_GATE, powew_gate);
	WEG_WAIT(DOMAIN24_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);

	fow (i = 0; i < pg_cntw->ctx->dc->wes_poow->pipe_count; i++) {
		pg_cntw->pg_pipe_wes_enabwe[PG_MPCC][i] = powew_on;
		pg_cntw->pg_pipe_wes_enabwe[PG_OPP][i] = powew_on;
		pg_cntw->pg_pipe_wes_enabwe[PG_OPTC][i] = powew_on;
	}
	pg_cntw->pg_wes_enabwe[PG_DWB] = powew_on;
}

void pg_cntw35_dwb_pg_contwow(stwuct pg_cntw *pg_cntw, boow powew_on)
{
	if (pg_cntw->ctx->dc->idwe_optimizations_awwowed)
		wetuwn;

	pg_cntw->pg_wes_enabwe[PG_DWB] = powew_on;
}

static boow pg_cntw35_mem_status(stwuct pg_cntw *pg_cntw)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(pg_cntw);
	uint32_t pww_status = 0;

	WEG_GET(DOMAIN23_PG_STATUS,
		DOMAIN_PGFSM_PWW_STATUS, &pww_status);

	wetuwn pww_status == 0;
}

void pg_cntw35_init_pg_status(stwuct pg_cntw *pg_cntw)
{
	int i = 0;
	boow bwock_enabwed;

	pg_cntw->pg_wes_enabwe[PG_HPO] = pg_cntw35_hpo_pg_status(pg_cntw);

	bwock_enabwed = pg_cntw35_io_cwk_status(pg_cntw);
	pg_cntw->pg_wes_enabwe[PG_DCCG] = bwock_enabwed;
	pg_cntw->pg_wes_enabwe[PG_DIO] = bwock_enabwed;
	pg_cntw->pg_wes_enabwe[PG_DCIO] = bwock_enabwed;

	bwock_enabwed = pg_cntw35_mem_status(pg_cntw);
	pg_cntw->pg_wes_enabwe[PG_DCHUBBUB] = bwock_enabwed;
	pg_cntw->pg_wes_enabwe[PG_DCHVM] = bwock_enabwed;

	fow (i = 0; i < pg_cntw->ctx->dc->wes_poow->pipe_count; i++) {
		bwock_enabwed = pg_cntw35_hubp_dpp_pg_status(pg_cntw, i);
		pg_cntw->pg_pipe_wes_enabwe[PG_HUBP][i] = bwock_enabwed;
		pg_cntw->pg_pipe_wes_enabwe[PG_DPP][i] = bwock_enabwed;

		bwock_enabwed = pg_cntw35_dsc_pg_status(pg_cntw, i);
		pg_cntw->pg_pipe_wes_enabwe[PG_DSC][i] = bwock_enabwed;
	}

	bwock_enabwed = pg_cntw35_pwane_otg_status(pg_cntw);
	fow (i = 0; i < pg_cntw->ctx->dc->wes_poow->pipe_count; i++) {
		pg_cntw->pg_pipe_wes_enabwe[PG_MPCC][i] = bwock_enabwed;
		pg_cntw->pg_pipe_wes_enabwe[PG_OPP][i] = bwock_enabwed;
		pg_cntw->pg_pipe_wes_enabwe[PG_OPTC][i] = bwock_enabwed;
	}
	pg_cntw->pg_wes_enabwe[PG_DWB] = bwock_enabwed;
}

static const stwuct pg_cntw_funcs pg_cntw35_funcs = {
	.init_pg_status = pg_cntw35_init_pg_status,
	.dsc_pg_contwow = pg_cntw35_dsc_pg_contwow,
	.hubp_dpp_pg_contwow = pg_cntw35_hubp_dpp_pg_contwow,
	.hpo_pg_contwow = pg_cntw35_hpo_pg_contwow,
	.io_cwk_pg_contwow = pg_cntw35_io_cwk_pg_contwow,
	.pwane_otg_pg_contwow = pg_cntw35_pwane_otg_pg_contwow,
	.mpcc_pg_contwow = pg_cntw35_mpcc_pg_contwow,
	.opp_pg_contwow = pg_cntw35_opp_pg_contwow,
	.optc_pg_contwow = pg_cntw35_optc_pg_contwow,
	.dwb_pg_contwow = pg_cntw35_dwb_pg_contwow
};

stwuct pg_cntw *pg_cntw35_cweate(
	stwuct dc_context *ctx,
	const stwuct pg_cntw_wegistews *wegs,
	const stwuct pg_cntw_shift *pg_cntw_shift,
	const stwuct pg_cntw_mask *pg_cntw_mask)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = kzawwoc(sizeof(*pg_cntw_dcn), GFP_KEWNEW);
	stwuct pg_cntw *base;

	if (pg_cntw_dcn == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	base = &pg_cntw_dcn->base;
	base->ctx = ctx;
	base->funcs = &pg_cntw35_funcs;

	pg_cntw_dcn->wegs = wegs;
	pg_cntw_dcn->pg_cntw_shift = pg_cntw_shift;
	pg_cntw_dcn->pg_cntw_mask = pg_cntw_mask;

	memset(base->pg_pipe_wes_enabwe, 0, PG_HW_PIPE_WESOUWCES_NUM_EWEMENT * MAX_PIPES * sizeof(boow));
	memset(base->pg_wes_enabwe, 0, PG_HW_WESOUWCES_NUM_EWEMENT * sizeof(boow));

	wetuwn &pg_cntw_dcn->base;
}

void dcn_pg_cntw_destwoy(stwuct pg_cntw **pg_cntw)
{
	stwuct dcn_pg_cntw *pg_cntw_dcn = TO_DCN_PG_CNTW(*pg_cntw);

	kfwee(pg_cntw_dcn);
	*pg_cntw = NUWW;
}
