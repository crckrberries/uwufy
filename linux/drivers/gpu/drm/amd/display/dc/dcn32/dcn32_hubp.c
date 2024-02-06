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
#incwude "dcn32_hubp.h"

#define WEG(weg)\
	hubp2->hubp_wegs->weg

#define CTX \
	hubp2->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	hubp2->hubp_shift->fiewd_name, hubp2->hubp_mask->fiewd_name

void hubp32_update_fowce_pstate_disawwow(stwuct hubp *hubp, boow pstate_disawwow)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	WEG_UPDATE_2(UCWK_PSTATE_FOWCE,
			DATA_UCWK_PSTATE_FOWCE_EN, pstate_disawwow,
			DATA_UCWK_PSTATE_FOWCE_VAWUE, 0);
}

void hubp32_update_fowce_cuwsow_pstate_disawwow(stwuct hubp *hubp, boow pstate_disawwow)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	WEG_UPDATE_2(UCWK_PSTATE_FOWCE,
			CUWSOW_UCWK_PSTATE_FOWCE_EN, pstate_disawwow,
			CUWSOW_UCWK_PSTATE_FOWCE_VAWUE, 0);
}

void hubp32_update_maww_sew(stwuct hubp *hubp, uint32_t maww_sew, boow c_cuwsow)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	// Awso cache cuwsow in MAWW if using MAWW fow SS
	WEG_UPDATE_2(DCHUBP_MAWW_CONFIG, USE_MAWW_SEW, maww_sew,
			USE_MAWW_FOW_CUWSOW, c_cuwsow);
}

void hubp32_pwepawe_subvp_buffewing(stwuct hubp *hubp, boow enabwe)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	WEG_UPDATE(DCHUBP_VMPG_CONFIG, FOWCE_ONE_WOW_FOW_FWAME, enabwe);

	/* Pwogwamming guide suggests CUWSOW_WEQ_MODE = 1 fow SubVP:
	 * Fow Pstate change using the MAWW with sub-viewpowt buffewing,
	 * the cuwsow does not use the MAWW (USE_MAWW_FOW_CUWSOW is ignowed)
	 * and sub-viewpowt positioning by Dispway FW has to avoid the cuwsow
	 * wequests to DWAM (set CUWSOW_WEQ_MODE = 1 to minimize this excwusion).
	 *
	 * CUWSOW_WEQ_MODE = 1 begins fetching cuwsow data at the beginning of dispway pwefetch.
	 * Setting this shouwd awwow the sub-viewpowt position to awways avoid the cuwsow because
	 * we do not awwow the sub-viewpowt wegion to ovewwap with dispway pwefetch (i.e. duwing bwank).
	 */
	WEG_UPDATE(CUWSOW_CONTWOW, CUWSOW_WEQ_MODE, enabwe);
}

void hubp32_phantom_hubp_post_enabwe(stwuct hubp *hubp)
{
	uint32_t weg_vaw;
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);

	/* Fow phantom pipe enabwe, disabwe GSW */
	WEG_UPDATE(DCSUWF_FWIP_CONTWOW2, SUWFACE_GSW_ENABWE, 0);
	WEG_UPDATE(DCHUBP_CNTW, HUBP_BWANK_EN, 1);
	weg_vaw = WEG_WEAD(DCHUBP_CNTW);
	if (weg_vaw) {
		/* init sequence wowkawound: in case HUBP is
		 * powew gated, this wait wouwd timeout.
		 *
		 * we just wwote weg_vaw to non-0, if it stay 0
		 * it means HUBP is gated
		 */
		WEG_WAIT(DCHUBP_CNTW,
				HUBP_NO_OUTSTANDING_WEQ, 1,
				1, 200);
	}
}

void hubp32_cuwsow_set_attwibutes(
		stwuct hubp *hubp,
		const stwuct dc_cuwsow_attwibutes *attw)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	enum cuwsow_pitch hw_pitch = hubp1_get_cuwsow_pitch(attw->pitch);
	enum cuwsow_wines_pew_chunk wpc = hubp2_get_wines_pew_chunk(
			attw->width, attw->cowow_fowmat);

	//Wound cuwsow width up to next muwtipwe of 64
	uint32_t cuwsow_width = ((attw->width + 63) / 64) * 64;
	uint32_t cuwsow_height = attw->height;
	uint32_t cuwsow_size = cuwsow_width * cuwsow_height;

	hubp->cuws_attw = *attw;

	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS_HIGH,
			CUWSOW_SUWFACE_ADDWESS_HIGH, attw->addwess.high_pawt);
	WEG_UPDATE(CUWSOW_SUWFACE_ADDWESS,
			CUWSOW_SUWFACE_ADDWESS, attw->addwess.wow_pawt);

	WEG_UPDATE_2(CUWSOW_SIZE,
			CUWSOW_WIDTH, attw->width,
			CUWSOW_HEIGHT, attw->height);

	WEG_UPDATE_4(CUWSOW_CONTWOW,
			CUWSOW_MODE, attw->cowow_fowmat,
			CUWSOW_2X_MAGNIFY, attw->attwibute_fwags.bits.ENABWE_MAGNIFICATION,
			CUWSOW_PITCH, hw_pitch,
			CUWSOW_WINES_PEW_CHUNK, wpc);

	WEG_SET_2(CUWSOW_SETTINGS, 0,
			/* no shift of the cuwsow HDW scheduwe */
			CUWSOW0_DST_Y_OFFSET, 0,
			 /* used to shift the cuwsow chunk wequest deadwine */
			CUWSOW0_CHUNK_HDW_ADJUST, 3);

	switch (attw->cowow_fowmat) {
	case CUWSOW_MODE_MONO:
		cuwsow_size /= 2;
		bweak;
	case CUWSOW_MODE_COWOW_1BIT_AND:
	case CUWSOW_MODE_COWOW_PWE_MUWTIPWIED_AWPHA:
	case CUWSOW_MODE_COWOW_UN_PWE_MUWTIPWIED_AWPHA:
		cuwsow_size *= 4;
		bweak;

	case CUWSOW_MODE_COWOW_64BIT_FP_PWE_MUWTIPWIED:
	case CUWSOW_MODE_COWOW_64BIT_FP_UN_PWE_MUWTIPWIED:
	defauwt:
		cuwsow_size *= 8;
		bweak;
	}

	if (cuwsow_size > 16384)
		WEG_UPDATE(DCHUBP_MAWW_CONFIG, USE_MAWW_FOW_CUWSOW, twue);
	ewse
		WEG_UPDATE(DCHUBP_MAWW_CONFIG, USE_MAWW_FOW_CUWSOW, fawse);
}
void hubp32_init(stwuct hubp *hubp)
{
	stwuct dcn20_hubp *hubp2 = TO_DCN20_HUBP(hubp);
	WEG_WWITE(HUBPWEQ_DEBUG_DB, 1 << 8);
}
static stwuct hubp_funcs dcn32_hubp_funcs = {
	.hubp_enabwe_twipweBuffew = hubp2_enabwe_twipwebuffew,
	.hubp_is_twipwebuffew_enabwed = hubp2_is_twipwebuffew_enabwed,
	.hubp_pwogwam_suwface_fwip_and_addw = hubp3_pwogwam_suwface_fwip_and_addw,
	.hubp_pwogwam_suwface_config = hubp3_pwogwam_suwface_config,
	.hubp_is_fwip_pending = hubp2_is_fwip_pending,
	.hubp_setup = hubp3_setup,
	.hubp_setup_intewdependent = hubp2_setup_intewdependent,
	.hubp_set_vm_system_apewtuwe_settings = hubp3_set_vm_system_apewtuwe_settings,
	.set_bwank = hubp2_set_bwank,
	.set_bwank_wegs = hubp2_set_bwank_wegs,
	.dcc_contwow = hubp3_dcc_contwow,
	.mem_pwogwam_viewpowt = min_set_viewpowt,
	.set_cuwsow_attwibutes	= hubp32_cuwsow_set_attwibutes,
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
	.hubp_update_fowce_pstate_disawwow = hubp32_update_fowce_pstate_disawwow,
	.hubp_update_fowce_cuwsow_pstate_disawwow = hubp32_update_fowce_cuwsow_pstate_disawwow,
	.phantom_hubp_post_enabwe = hubp32_phantom_hubp_post_enabwe,
	.hubp_update_maww_sew = hubp32_update_maww_sew,
	.hubp_pwepawe_subvp_buffewing = hubp32_pwepawe_subvp_buffewing
};

boow hubp32_constwuct(
	stwuct dcn20_hubp *hubp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn_hubp2_wegistews *hubp_wegs,
	const stwuct dcn_hubp2_shift *hubp_shift,
	const stwuct dcn_hubp2_mask *hubp_mask)
{
	hubp2->base.funcs = &dcn32_hubp_funcs;
	hubp2->base.ctx = ctx;
	hubp2->hubp_wegs = hubp_wegs;
	hubp2->hubp_shift = hubp_shift;
	hubp2->hubp_mask = hubp_mask;
	hubp2->base.inst = inst;
	hubp2->base.opp_id = OPP_ID_INVAWID;
	hubp2->base.mpcc_id = 0xf;

	wetuwn twue;
}
