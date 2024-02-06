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

#incwude <winux/swab.h>

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dcn20_dccg.h"

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

void dccg2_update_dpp_dto(stwuct dccg *dccg, int dpp_inst, int weq_dppcwk)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

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

void dccg2_get_dccg_wef_fweq(stwuct dccg *dccg,
		unsigned int xtawin_fweq_inKhz,
		unsigned int *dccg_wef_fweq_inKhz)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	uint32_t cwk_en = 0;
	uint32_t cwk_sew = 0;

	WEG_GET_2(WEFCWK_CNTW, WEFCWK_CWOCK_EN, &cwk_en, WEFCWK_SWC_SEW, &cwk_sew);

	if (cwk_en != 0) {
		// DCN20 has nevew been vawidated fow non-xtawin as wefewence
		// fwequency.  Thewe's actuawwy no way fow DC to detewmine what
		// fwequency a non-xtawin souwce is.
		ASSEWT_CWITICAW(fawse);
	}

	*dccg_wef_fweq_inKhz = xtawin_fweq_inKhz;

	wetuwn;
}

void dccg2_set_fifo_ewwdet_ovw_en(stwuct dccg *dccg,
		boow en)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE(DISPCWK_FWEQ_CHANGE_CNTW,
			DCCG_FIFO_EWWDET_OVW_EN, en ? 1 : 0);
}

void dccg2_otg_add_pixew(stwuct dccg *dccg,
		uint32_t otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE_2(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_ADD_PIXEW[otg_inst], 0,
			OTG_DWOP_PIXEW[otg_inst], 0);
	WEG_UPDATE(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_ADD_PIXEW[otg_inst], 1);
}

void dccg2_otg_dwop_pixew(stwuct dccg *dccg,
		uint32_t otg_inst)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	WEG_UPDATE_2(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_ADD_PIXEW[otg_inst], 0,
			OTG_DWOP_PIXEW[otg_inst], 0);
	WEG_UPDATE(OTG_PIXEW_WATE_CNTW[otg_inst],
			OTG_DWOP_PIXEW[otg_inst], 1);
}

void dccg2_init(stwuct dccg *dccg)
{
}

static const stwuct dccg_funcs dccg2_funcs = {
	.update_dpp_dto = dccg2_update_dpp_dto,
	.get_dccg_wef_fweq = dccg2_get_dccg_wef_fweq,
	.set_fifo_ewwdet_ovw_en = dccg2_set_fifo_ewwdet_ovw_en,
	.otg_add_pixew = dccg2_otg_add_pixew,
	.otg_dwop_pixew = dccg2_otg_dwop_pixew,
	.dccg_init = dccg2_init
};

stwuct dccg *dccg2_cweate(
	stwuct dc_context *ctx,
	const stwuct dccg_wegistews *wegs,
	const stwuct dccg_shift *dccg_shift,
	const stwuct dccg_mask *dccg_mask)
{
	stwuct dcn_dccg *dccg_dcn = kzawwoc(sizeof(*dccg_dcn), GFP_ATOMIC);
	stwuct dccg *base;

	if (dccg_dcn == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	base = &dccg_dcn->base;
	base->ctx = ctx;
	base->funcs = &dccg2_funcs;

	dccg_dcn->wegs = wegs;
	dccg_dcn->dccg_shift = dccg_shift;
	dccg_dcn->dccg_mask = dccg_mask;

	wetuwn &dccg_dcn->base;
}

void dcn_dccg_destwoy(stwuct dccg **dccg)
{
	stwuct dcn_dccg *dccg_dcn = TO_DCN_DCCG(*dccg);

	kfwee(dccg_dcn);
	*dccg = NUWW;
}
