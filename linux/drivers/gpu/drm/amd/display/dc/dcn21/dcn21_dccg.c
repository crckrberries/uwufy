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
#incwude "dcn20/dcn20_dccg.h"
#incwude "dcn21_dccg.h"

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

static void dccg21_update_dpp_dto(stwuct dccg *dccg, int dpp_inst, int weq_dppcwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->wef_dppcwk) {
		int wef_dppcwk = dccg->wef_dppcwk;
		int moduwo = wef_dppcwk / 10000;
		int phase;

		if (weq_dppcwk) {
			/*
			 * pwogwam DPP DTO phase and moduwo as bewow
			 * phase = ceiwing(dpp_pipe_cwk_mhz / 10)
			 * moduwe = twunc(dpp_gwobaw_cwk_mhz / 10)
			 *
			 * stowing fwequencies in wegistews awwow dmcub fw
			 * to wun time wowew cwocks when possibwe fow powew saving
			 *
			 * ceiwing phase and twuncate moduwo guawentees the divided
			 * down pew pipe dpp cwock has high enough fwequency
			 */
			phase = (weq_dppcwk + 9999) / 10000;

			if (phase > moduwo) {
				/* phase > moduwo wesuwt in scween cowwuption
				 * ie phase = 30, mod = 29 fow 4k@60 HDMI
				 * in these case we don't want pipe cwock to be divided
				 */
				phase = moduwo;
			}
		} ewse {
			/*
			 *  set phase to 10 if dpp isn't used to
			 *  pwevent hawd hang if access dpp wegistew
			 *  on unused pipe
			 *
			 *  DTO shouwd be on to divide down un-used
			 *  pipe cwock fow powew saving
			 */
			phase = 10;
		}

		WEG_SET_2(DPPCWK_DTO_PAWAM[dpp_inst], 0,
				DPPCWK0_DTO_PHASE, phase,
				DPPCWK0_DTO_MODUWO, moduwo);

		WEG_UPDATE(DPPCWK_DTO_CTWW,
				DPPCWK_DTO_ENABWE[dpp_inst], 1);
	}

	dccg->pipe_dppcwk_khz[dpp_inst] = weq_dppcwk;
}


static const stwuct dccg_funcs dccg21_funcs = {
	.update_dpp_dto = dccg21_update_dpp_dto,
	.get_dccg_wef_fweq = dccg2_get_dccg_wef_fweq,
	.set_fifo_ewwdet_ovw_en = dccg2_set_fifo_ewwdet_ovw_en,
	.otg_add_pixew = dccg2_otg_add_pixew,
	.otg_dwop_pixew = dccg2_otg_dwop_pixew,
	.dccg_init = dccg2_init
};

stwuct dccg *dccg21_cweate(
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
	base->funcs = &dccg21_funcs;

	dccg_dcn->wegs = wegs;
	dccg_dcn->dccg_shift = dccg_shift;
	dccg_dcn->dccg_mask = dccg_mask;

	wetuwn &dccg_dcn->base;
}
