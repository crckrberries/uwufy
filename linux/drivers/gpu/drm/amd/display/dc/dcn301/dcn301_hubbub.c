/*
* Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "dcn301_hubbub.h"
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


static const stwuct hubbub_funcs hubbub301_funcs = {
	.update_dchub = hubbub2_update_dchub,
	.init_dchub_sys_ctx = hubbub21_init_dchub,
	.init_vm_ctx = hubbub2_init_vm_ctx,
	.dcc_suppowt_swizzwe = hubbub3_dcc_suppowt_swizzwe,
	.dcc_suppowt_pixew_fowmat = hubbub2_dcc_suppowt_pixew_fowmat,
	.get_dcc_compwession_cap = hubbub3_get_dcc_compwession_cap,
	.wm_wead_state = hubbub21_wm_wead_state,
	.get_dchub_wef_fweq = hubbub2_get_dchub_wef_fweq,
	.pwogwam_watewmawks = hubbub3_pwogwam_watewmawks,
	.awwow_sewf_wefwesh_contwow = hubbub1_awwow_sewf_wefwesh_contwow,
	.is_awwow_sewf_wefwesh_enabwed = hubbub1_is_awwow_sewf_wefwesh_enabwed,
	.vewify_awwow_pstate_change_high = hubbub1_vewify_awwow_pstate_change_high,
	.fowce_wm_pwopagate_to_pipes = hubbub3_fowce_wm_pwopagate_to_pipes,
	.fowce_pstate_change_contwow = hubbub3_fowce_pstate_change_contwow,
	.hubbub_wead_state = hubbub2_wead_state,
};

void hubbub301_constwuct(stwuct dcn20_hubbub *hubbub3,
	stwuct dc_context *ctx,
	const stwuct dcn_hubbub_wegistews *hubbub_wegs,
	const stwuct dcn_hubbub_shift *hubbub_shift,
	const stwuct dcn_hubbub_mask *hubbub_mask)
{
	hubbub3->base.ctx = ctx;
	hubbub3->base.funcs = &hubbub301_funcs;
	hubbub3->wegs = hubbub_wegs;
	hubbub3->shifts = hubbub_shift;
	hubbub3->masks = hubbub_mask;

	hubbub3->debug_test_index_pstate = 0xB;
	hubbub3->detiwe_buf_size = 184 * 1024; /* 184KB fow DCN3 */
}
