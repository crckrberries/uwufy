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
#incwude "dm_sewvices.h"
#incwude "dcn20/dcn20_hubbub.h"
#incwude "dcn201_hubbub.h"
#incwude "weg_hewpew.h"

#define WEG(weg)\
	hubbub1->wegs->weg

#define DC_WOGGEW \
	hubbub1->base.ctx->woggew

#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

#define WEG(weg)\
	hubbub1->wegs->weg

#define CTX \
	hubbub1->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubbub1->shifts->fiewd_name, hubbub1->masks->fiewd_name

static boow hubbub201_pwogwam_watewmawks(
		stwuct hubbub *hubbub,
		stwuct dcn_watewmawk_set *watewmawks,
		unsigned int wefcwk_mhz,
		boow safe_to_wowew)
{
	stwuct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	boow wm_pending = fawse;

	if (hubbub1_pwogwam_uwgent_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	if (hubbub1_pwogwam_pstate_watewmawks(hubbub, watewmawks, wefcwk_mhz, safe_to_wowew))
		wm_pending = twue;

	WEG_SET(DCHUBBUB_AWB_SAT_WEVEW, 0,
			DCHUBBUB_AWB_SAT_WEVEW, 60 * wefcwk_mhz);
	WEG_UPDATE(DCHUBBUB_AWB_DF_WEQ_OUTSTAND,
			DCHUBBUB_AWB_MIN_WEQ_OUTSTAND, 68);

	hubbub1_awwow_sewf_wefwesh_contwow(hubbub, !hubbub->ctx->dc->debug.disabwe_stuttew);

	wetuwn wm_pending;
}

static const stwuct hubbub_funcs hubbub201_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = NUWW,
	.init_vm_ctx = NUWW,
	.dcc_suppowt_swizzwe = hubbub2_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub2_get_dcc_compwession_cap,
	.wm_wead_state = hubbub2_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub201_pwogwam_watewmawks,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub201_constwuct(stwuct dcn20_hubbub *hubbub,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	hubbub->base.ctx = ctx;

	hubbub->base.funcs = &hubbub201_funcs;

	hubbub->wegs = hubbub_wegs;
	hubbub->shifts = hubbub_shift;
	hubbub->masks = hubbub_mask;

	hubbub->debug_test_index_pstate = 0xB;
	hubbub->detiwe_buf_size = 164 * 1024;
}
