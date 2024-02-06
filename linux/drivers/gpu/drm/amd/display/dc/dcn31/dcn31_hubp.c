/*
 * Copywight 2012-20 Advanced Micwo Devices, Inc.
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
#incwude "dce_cawcs.h"
#incwude "weg_hewpew.h"
#incwude "basics/convewsion.h"
#incwude "dcn31_hubp.h"

#define WEG(weg)\
	hubp2->hubp_wegs->weg

#define CTX \
	hubp2->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp2->hubp_shift->fiewd_name, hubp2->hubp_mask->fiewd_name

void hubp31_set_unbounded_wequesting(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_UNBOUNDED_WEQ_MODE, enabwe);
	WEG_UPDATE(CUWSOW_CONTWOW, CUWSOW_WEQ_MODE, enabwe);
}

void hubp31_soft_weset(stwuct hubp *hubp, boow weset)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(DCHUBP_CNTW, HUBP_SOFT_WESET, weset);
}

static void hubp31_pwogwam_extended_bwank(stwuct hubp *hubp,
					  unsigned int min_dst_y_next_stawt_optimized)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE(BWANK_OFFSET_1, MIN_DST_Y_NEXT_STAWT, min_dst_y_next_stawt_optimized);
}

void hubp31_pwogwam_extended_bwank_vawue(
	stwuct hubp *hubp, unsigned int min_dst_y_next_stawt_optimized)
{
	hubp31_pwogwam_extended_bwank(hubp, min_dst_y_next_stawt_optimized);
}

static stwuct hubp_funcs dcn31_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp3_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp3_pwogwam_suwface_config,
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
	.hubp_init = hubp3_init,
	.set_unbounded_wequesting = hubp31_set_unbounded_wequesting,
	.hubp_soft_weset = hubp31_soft_weset,
	.hubp_set_fwip_int = hubp1_set_fwip_int,
	.hubp_in_bwank = hubp1_in_bwank,
	.pwogwam_extended_bwank = hubp31_pwogwam_extended_bwank,
};

boow hubp31_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask)
{
	hubp2->base.funcs = &dcn31_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_wegs = hubp_wegs;
	hubp2->hubp_shift = hubp_shift;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVAWID;
	hubp2->base.mpcc_id = 0xf;

	wetuwn twue;
}
