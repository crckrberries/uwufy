/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "dcn30/dcn30_mpc.h"
#incwude "dcn30/dcn30_cm_common.h"
#incwude "dcn32_mpc.h"
#incwude "basics/convewsion.h"
#incwude "dcn10/dcn10_cm_common.h"
#incwude "dc.h"

#define WEG(weg)\
	mpc30->mpc_wegs->weg

#define CTX \
	mpc30->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	mpc30->mpc_shift->fiewd_name, mpc30->mpc_mask->fiewd_name


void mpc32_mpc_init(stwuct mpc *mpc)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int mpcc_id;

	mpc1_mpc_init(mpc);

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc) {
		if (mpc30->mpc_mask->MPCC_MCM_SHAPEW_MEM_WOW_PWW_MODE && mpc30->mpc_mask->MPCC_MCM_3DWUT_MEM_WOW_PWW_MODE) {
			fow (mpcc_id = 0; mpcc_id < mpc30->num_mpcc; mpcc_id++) {
				WEG_UPDATE(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_SHAPEW_MEM_WOW_PWW_MODE, 3);
				WEG_UPDATE(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_3DWUT_MEM_WOW_PWW_MODE, 3);
				WEG_UPDATE(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_1DWUT_MEM_WOW_PWW_MODE, 3);
			}
		}
		if (mpc30->mpc_mask->MPCC_OGAM_MEM_WOW_PWW_MODE) {
			fow (mpcc_id = 0; mpcc_id < mpc30->num_mpcc; mpcc_id++)
				WEG_UPDATE(MPCC_MEM_PWW_CTWW[mpcc_id], MPCC_OGAM_MEM_WOW_PWW_MODE, 3);
		}
	}
}

void mpc32_powew_on_bwnd_wut(
	stwuct mpc *mpc,
	uint32_t mpcc_id,
	boow powew_on)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], 0, MPCC_MCM_1DWUT_MEM_PWW_DIS, powew_on);

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.cm) {
		if (powew_on) {
			WEG_UPDATE(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_1DWUT_MEM_PWW_FOWCE, 0);
			WEG_WAIT(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_1DWUT_MEM_PWW_STATE, 0, 1, 5);
		} ewse if (!mpc->ctx->dc->debug.disabwe_mem_wow_powew) {
			/* TODO: change to mpc
			 *  dpp_base->ctx->dc->optimized_wequiwed = twue;
			 *  dpp_base->defewwed_weg_wwites.bits.disabwe_bwnd_wut = twue;
			 */
		}
	} ewse {
		WEG_SET(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], 0,
				MPCC_MCM_1DWUT_MEM_PWW_FOWCE, powew_on == twue ? 0 : 1);
	}
}

static enum dc_wut_mode mpc32_get_post1dwut_cuwwent(stwuct mpc *mpc, uint32_t mpcc_id)
{
	enum dc_wut_mode mode;
	uint32_t mode_cuwwent = 0;
	uint32_t in_use = 0;

	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET(MPCC_MCM_1DWUT_CONTWOW[mpcc_id],
			MPCC_MCM_1DWUT_MODE_CUWWENT, &mode_cuwwent);
	WEG_GET(MPCC_MCM_1DWUT_CONTWOW[mpcc_id],
			MPCC_MCM_1DWUT_SEWECT_CUWWENT, &in_use);

	switch (mode_cuwwent) {
	case 0:
	case 1:
		mode = WUT_BYPASS;
		bweak;

	case 2:
		if (in_use == 0)
			mode = WUT_WAM_A;
		ewse
			mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}
	wetuwn mode;
}

void mpc32_configuwe_post1dwut(
		stwuct mpc *mpc,
		uint32_t mpcc_id,
		boow is_wam_a)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	//TODO: this
	WEG_UPDATE_2(MPCC_MCM_1DWUT_WUT_CONTWOW[mpcc_id],
			MPCC_MCM_1DWUT_WUT_WWITE_COWOW_MASK, 7,
			MPCC_MCM_1DWUT_WUT_HOST_SEW, is_wam_a == twue ? 0 : 1);

	WEG_SET(MPCC_MCM_1DWUT_WUT_INDEX[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_INDEX, 0);
}

static void mpc32_post1dwut_get_weg_fiewd(
		stwuct dcn30_mpc *mpc,
		stwuct dcn3_xfew_func_weg *weg)
{
	weg->shifts.exp_wegion0_wut_offset = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->shifts.exp_wegion_stawt = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = mpc->mpc_shift->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = mpc->mpc_mask->MPCC_MCM_1DWUT_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
}

/*pwogwam bwnd wut WAM A*/
void mpc32_pwogwam_post1dwuta_settings(
		stwuct mpc *mpc,
		uint32_t mpcc_id,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	stwuct dcn3_xfew_func_weg gam_wegs;

	mpc32_post1dwut_get_weg_fiewd(mpc30, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_MCM_1DWUT_WAMA_STAWT_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_MCM_1DWUT_WAMA_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_MCM_1DWUT_WAMA_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_MCM_1DWUT_WAMA_WEGION_32_33[mpcc_id]);

	cm_hewpew_pwogwam_gamcow_xfew_func(mpc->ctx, pawams, &gam_wegs);
}

/*pwogwam bwnd wut WAM B*/
void mpc32_pwogwam_post1dwutb_settings(
		stwuct mpc *mpc,
		uint32_t mpcc_id,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	stwuct dcn3_xfew_func_weg gam_wegs;

	mpc32_post1dwut_get_weg_fiewd(mpc30, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_MCM_1DWUT_WAMB_STAWT_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_MCM_1DWUT_WAMB_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_MCM_1DWUT_WAMB_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_MCM_1DWUT_WAMB_WEGION_32_33[mpcc_id]);

	cm_hewpew_pwogwam_gamcow_xfew_func(mpc->ctx, pawams, &gam_wegs);
}

void mpc32_pwogwam_post1dwut_pww(
		stwuct mpc *mpc,
		uint32_t mpcc_id,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num)
{
	uint32_t i;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	uint32_t wast_base_vawue_wed = wgb[num-1].wed_weg + wgb[num-1].dewta_wed_weg;
	uint32_t wast_base_vawue_gween = wgb[num-1].gween_weg + wgb[num-1].dewta_gween_weg;
	uint32_t wast_base_vawue_bwue = wgb[num-1].bwue_weg + wgb[num-1].dewta_bwue_weg;

	if (is_wgb_equaw(wgb, num)) {
		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wast_base_vawue_wed);
	} ewse {
		WEG_SET(MPCC_MCM_1DWUT_WUT_INDEX[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_INDEX, 0);
		WEG_UPDATE(MPCC_MCM_1DWUT_WUT_CONTWOW[mpcc_id], MPCC_MCM_1DWUT_WUT_WWITE_COWOW_MASK, 4);
		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wast_base_vawue_wed);

		WEG_SET(MPCC_MCM_1DWUT_WUT_INDEX[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_INDEX, 0);
		WEG_UPDATE(MPCC_MCM_1DWUT_WUT_CONTWOW[mpcc_id], MPCC_MCM_1DWUT_WUT_WWITE_COWOW_MASK, 2);
		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wgb[i].gween_weg);
		WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wast_base_vawue_gween);

		WEG_SET(MPCC_MCM_1DWUT_WUT_INDEX[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_INDEX, 0);
		WEG_UPDATE(MPCC_MCM_1DWUT_WUT_CONTWOW[mpcc_id], MPCC_MCM_1DWUT_WUT_WWITE_COWOW_MASK, 1);
		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wgb[i].bwue_weg);
		WEG_SET(MPCC_MCM_1DWUT_WUT_DATA[mpcc_id], 0, MPCC_MCM_1DWUT_WUT_DATA, wast_base_vawue_bwue);
	}
}

boow mpc32_pwogwam_post1dwut(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t mpcc_id)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (pawams == NUWW) {
		WEG_SET(MPCC_MCM_1DWUT_CONTWOW[mpcc_id], 0, MPCC_MCM_1DWUT_MODE, 0);
		if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.cm)
			mpc32_powew_on_bwnd_wut(mpc, mpcc_id, fawse);
		wetuwn fawse;
	}

	cuwwent_mode = mpc32_get_post1dwut_cuwwent(mpc, mpcc_id);
	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_B)
		next_mode = WUT_WAM_A;
	ewse
		next_mode = WUT_WAM_B;

	mpc32_powew_on_bwnd_wut(mpc, mpcc_id, twue);
	mpc32_configuwe_post1dwut(mpc, mpcc_id, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_A)
		mpc32_pwogwam_post1dwuta_settings(mpc, mpcc_id, pawams);
	ewse
		mpc32_pwogwam_post1dwutb_settings(mpc, mpcc_id, pawams);

	mpc32_pwogwam_post1dwut_pww(
			mpc, mpcc_id, pawams->wgb_wesuwted, pawams->hw_points_num);

	WEG_UPDATE_2(MPCC_MCM_1DWUT_CONTWOW[mpcc_id],
			MPCC_MCM_1DWUT_MODE, 2,
			MPCC_MCM_1DWUT_SEWECT, next_mode == WUT_WAM_A ? 0 : 1);

	wetuwn twue;
}

static enum dc_wut_mode mpc32_get_shapew_cuwwent(stwuct mpc *mpc, uint32_t mpcc_id)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET(MPCC_MCM_SHAPEW_CONTWOW[mpcc_id], MPCC_MCM_SHAPEW_MODE_CUWWENT, &state_mode);

	switch (state_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 1:
		mode = WUT_WAM_A;
		bweak;
	case 2:
		mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}

	wetuwn mode;
}


void mpc32_configuwe_shapew_wut(
		stwuct mpc *mpc,
		boow is_wam_a,
		uint32_t mpcc_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE(MPCC_MCM_SHAPEW_WUT_WWITE_EN_MASK[mpcc_id],
			MPCC_MCM_SHAPEW_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(MPCC_MCM_SHAPEW_WUT_WWITE_EN_MASK[mpcc_id],
			MPCC_MCM_SHAPEW_WUT_WWITE_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(MPCC_MCM_SHAPEW_WUT_INDEX[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_INDEX, 0);
}


void mpc32_pwogwam_shapew_wuta_settings(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t mpcc_id)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_STAWT_CNTW_B[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_STAWT_CNTW_G[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].gween.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_STAWT_CNTW_W[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].wed.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);

	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_END_CNTW_B[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_END_CNTW_G[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].gween.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].gween.custom_fwoat_y);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMA_END_CNTW_W[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].wed.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_0_1[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_2_3[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_4_5[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_6_7[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_8_9[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_10_11[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_12_13[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_14_15[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_16_17[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_18_19[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_20_21[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_22_23[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_24_25[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_26_27[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_28_29[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_30_31[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMA_WEGION_32_33[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
}


void mpc32_pwogwam_shapew_wutb_settings(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t mpcc_id)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_STAWT_CNTW_B[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_STAWT_CNTW_G[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].gween.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_STAWT_CNTW_W[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].wed.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);

	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_END_CNTW_B[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_END_CNTW_G[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].gween.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].gween.custom_fwoat_y);
	WEG_SET_2(MPCC_MCM_SHAPEW_WAMB_END_CNTW_W[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].wed.custom_fwoat_x,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_0_1[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_2_3[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_4_5[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_6_7[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_8_9[mpcc_id], 0,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_10_11[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_12_13[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_14_15[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_16_17[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_18_19[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_20_21[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_22_23[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_24_25[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_26_27[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_28_29[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_30_31[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(MPCC_MCM_SHAPEW_WAMB_WEGION_32_33[mpcc_id], 0,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPCC_MCM_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
}


void mpc32_pwogwam_shapew_wut(
		stwuct mpc *mpc,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num,
		uint32_t mpcc_id)
{
	uint32_t i, wed, gween, bwue;
	uint32_t  wed_dewta, gween_dewta, bwue_dewta;
	uint32_t  wed_vawue, gween_vawue, bwue_vawue;

	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	fow (i = 0 ; i < num; i++) {

		wed   = wgb[i].wed_weg;
		gween = wgb[i].gween_weg;
		bwue  = wgb[i].bwue_weg;

		wed_dewta   = wgb[i].dewta_wed_weg;
		gween_dewta = wgb[i].dewta_gween_weg;
		bwue_dewta  = wgb[i].dewta_bwue_weg;

		wed_vawue   = ((wed_dewta   & 0x3ff) << 14) | (wed   & 0x3fff);
		gween_vawue = ((gween_dewta & 0x3ff) << 14) | (gween & 0x3fff);
		bwue_vawue  = ((bwue_dewta  & 0x3ff) << 14) | (bwue  & 0x3fff);

		WEG_SET(MPCC_MCM_SHAPEW_WUT_DATA[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_DATA, wed_vawue);
		WEG_SET(MPCC_MCM_SHAPEW_WUT_DATA[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_DATA, gween_vawue);
		WEG_SET(MPCC_MCM_SHAPEW_WUT_DATA[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_DATA, bwue_vawue);
	}

}


void mpc32_powew_on_shapew_3dwut(
		stwuct mpc *mpc,
		uint32_t mpcc_id,
		boow powew_on)
{
	uint32_t powew_status_shapew = 2;
	uint32_t powew_status_3dwut  = 2;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int max_wetwies = 10;

	WEG_SET(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], 0,
	MPCC_MCM_3DWUT_MEM_PWW_DIS, powew_on == twue ? 1:0);
	/* wait fow memowy to fuwwy powew up */
	if (powew_on && mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc) {
		WEG_WAIT(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_SHAPEW_MEM_PWW_STATE, 0, 1, max_wetwies);
		WEG_WAIT(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_3DWUT_MEM_PWW_STATE, 0, 1, max_wetwies);
	}

	/*wead status is not mandatowy, it is just fow debugging*/
	WEG_GET(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_SHAPEW_MEM_PWW_STATE, &powew_status_shapew);
	WEG_GET(MPCC_MCM_MEM_PWW_CTWW[mpcc_id], MPCC_MCM_3DWUT_MEM_PWW_STATE, &powew_status_3dwut);

	if (powew_status_shapew != 0 && powew_on == twue)
		BWEAK_TO_DEBUGGEW();

	if (powew_status_3dwut != 0 && powew_on == twue)
		BWEAK_TO_DEBUGGEW();
}


boow mpc32_pwogwam_shapew(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t mpcc_id)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;

	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (pawams == NUWW) {
		WEG_SET(MPCC_MCM_SHAPEW_CONTWOW[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_MODE, 0);
		wetuwn fawse;
	}

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc)
		mpc32_powew_on_shapew_3dwut(mpc, mpcc_id, twue);

	cuwwent_mode = mpc32_get_shapew_cuwwent(mpc, mpcc_id);

	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	mpc32_configuwe_shapew_wut(mpc, next_mode == WUT_WAM_A, mpcc_id);

	if (next_mode == WUT_WAM_A)
		mpc32_pwogwam_shapew_wuta_settings(mpc, pawams, mpcc_id);
	ewse
		mpc32_pwogwam_shapew_wutb_settings(mpc, pawams, mpcc_id);

	mpc32_pwogwam_shapew_wut(
			mpc, pawams->wgb_wesuwted, pawams->hw_points_num, mpcc_id);

	WEG_SET(MPCC_MCM_SHAPEW_CONTWOW[mpcc_id], 0, MPCC_MCM_SHAPEW_WUT_MODE, next_mode == WUT_WAM_A ? 1:2);
	mpc32_powew_on_shapew_3dwut(mpc, mpcc_id, fawse);

	wetuwn twue;
}


static enum dc_wut_mode get3dwut_config(
			stwuct mpc *mpc,
			boow *is_17x17x17,
			boow *is_12bits_cowow_channew,
			int mpcc_id)
{
	uint32_t i_mode, i_enabwe_10bits, wut_size;
	enum dc_wut_mode mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET(MPCC_MCM_3DWUT_MODE[mpcc_id],
			MPCC_MCM_3DWUT_MODE_CUWWENT,  &i_mode);

	WEG_GET(MPCC_MCM_3DWUT_WEAD_WWITE_CONTWOW[mpcc_id],
			MPCC_MCM_3DWUT_30BIT_EN, &i_enabwe_10bits);

	switch (i_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 1:
		mode = WUT_WAM_A;
		bweak;
	case 2:
		mode = WUT_WAM_B;
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}
	if (i_enabwe_10bits > 0)
		*is_12bits_cowow_channew = fawse;
	ewse
		*is_12bits_cowow_channew = twue;

	WEG_GET(MPCC_MCM_3DWUT_MODE[mpcc_id], MPCC_MCM_3DWUT_SIZE, &wut_size);

	if (wut_size == 0)
		*is_17x17x17 = twue;
	ewse
		*is_17x17x17 = fawse;

	wetuwn mode;
}


void mpc32_sewect_3dwut_wam(
		stwuct mpc *mpc,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits,
		uint32_t mpcc_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE_2(MPCC_MCM_3DWUT_WEAD_WWITE_CONTWOW[mpcc_id],
		MPCC_MCM_3DWUT_WAM_SEW, mode == WUT_WAM_A ? 0 : 1,
		MPCC_MCM_3DWUT_30BIT_EN, is_cowow_channew_12bits == twue ? 0:1);
}


void mpc32_sewect_3dwut_wam_mask(
		stwuct mpc *mpc,
		uint32_t wam_sewection_mask,
		uint32_t mpcc_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE(MPCC_MCM_3DWUT_WEAD_WWITE_CONTWOW[mpcc_id], MPCC_MCM_3DWUT_WWITE_EN_MASK,
			wam_sewection_mask);
	WEG_SET(MPCC_MCM_3DWUT_INDEX[mpcc_id], 0, MPCC_MCM_3DWUT_INDEX, 0);
}


void mpc32_set3dwut_wam12(
		stwuct mpc *mpc,
		const stwuct dc_wgb *wut,
		uint32_t entwies,
		uint32_t mpcc_id)
{
	uint32_t i, wed, gween, bwue, wed1, gween1, bwue1;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	fow (i = 0 ; i < entwies; i += 2) {
		wed   = wut[i].wed<<4;
		gween = wut[i].gween<<4;
		bwue  = wut[i].bwue<<4;
		wed1   = wut[i+1].wed<<4;
		gween1 = wut[i+1].gween<<4;
		bwue1  = wut[i+1].bwue<<4;

		WEG_SET_2(MPCC_MCM_3DWUT_DATA[mpcc_id], 0,
				MPCC_MCM_3DWUT_DATA0, wed,
				MPCC_MCM_3DWUT_DATA1, wed1);

		WEG_SET_2(MPCC_MCM_3DWUT_DATA[mpcc_id], 0,
				MPCC_MCM_3DWUT_DATA0, gween,
				MPCC_MCM_3DWUT_DATA1, gween1);

		WEG_SET_2(MPCC_MCM_3DWUT_DATA[mpcc_id], 0,
				MPCC_MCM_3DWUT_DATA0, bwue,
				MPCC_MCM_3DWUT_DATA1, bwue1);
	}
}


void mpc32_set3dwut_wam10(
		stwuct mpc *mpc,
		const stwuct dc_wgb *wut,
		uint32_t entwies,
		uint32_t mpcc_id)
{
	uint32_t i, wed, gween, bwue, vawue;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	fow (i = 0; i < entwies; i++) {
		wed   = wut[i].wed;
		gween = wut[i].gween;
		bwue  = wut[i].bwue;
		//shouwd we shift wed 22bit and gween 12?
		vawue = (wed<<20) | (gween<<10) | bwue;

		WEG_SET(MPCC_MCM_3DWUT_DATA_30BIT[mpcc_id], 0, MPCC_MCM_3DWUT_DATA_30BIT, vawue);
	}

}


static void mpc32_set_3dwut_mode(
		stwuct mpc *mpc,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits,
		boow is_wut_size17x17x17,
		uint32_t mpcc_id)
{
	uint32_t wut_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	// set defauwt 3DWUT to pwe-bwend
	// TODO: impwement movabwe CM wocation
	WEG_UPDATE(MPCC_MOVABWE_CM_WOCATION_CONTWOW[mpcc_id], MPCC_MOVABWE_CM_WOCATION_CNTW, 0);

	if (mode == WUT_BYPASS)
		wut_mode = 0;
	ewse if (mode == WUT_WAM_A)
		wut_mode = 1;
	ewse
		wut_mode = 2;

	WEG_UPDATE_2(MPCC_MCM_3DWUT_MODE[mpcc_id],
			MPCC_MCM_3DWUT_MODE, wut_mode,
			MPCC_MCM_3DWUT_SIZE, is_wut_size17x17x17 == twue ? 0 : 1);
}


boow mpc32_pwogwam_3dwut(
		stwuct mpc *mpc,
		const stwuct tetwahedwaw_pawams *pawams,
		int mpcc_id)
{
	enum dc_wut_mode mode;
	boow is_17x17x17;
	boow is_12bits_cowow_channew;
	const stwuct dc_wgb *wut0;
	const stwuct dc_wgb *wut1;
	const stwuct dc_wgb *wut2;
	const stwuct dc_wgb *wut3;
	int wut_size0;
	int wut_size;

	if (pawams == NUWW) {
		mpc32_set_3dwut_mode(mpc, WUT_BYPASS, fawse, fawse, mpcc_id);
		wetuwn fawse;
	}
	mpc32_powew_on_shapew_3dwut(mpc, mpcc_id, twue);

	mode = get3dwut_config(mpc, &is_17x17x17, &is_12bits_cowow_channew, mpcc_id);

	if (mode == WUT_BYPASS || mode == WUT_WAM_B)
		mode = WUT_WAM_A;
	ewse
		mode = WUT_WAM_B;

	is_17x17x17 = !pawams->use_tetwahedwaw_9;
	is_12bits_cowow_channew = pawams->use_12bits;
	if (is_17x17x17) {
		wut0 = pawams->tetwahedwaw_17.wut0;
		wut1 = pawams->tetwahedwaw_17.wut1;
		wut2 = pawams->tetwahedwaw_17.wut2;
		wut3 = pawams->tetwahedwaw_17.wut3;
		wut_size0 = sizeof(pawams->tetwahedwaw_17.wut0)/
					sizeof(pawams->tetwahedwaw_17.wut0[0]);
		wut_size  = sizeof(pawams->tetwahedwaw_17.wut1)/
					sizeof(pawams->tetwahedwaw_17.wut1[0]);
	} ewse {
		wut0 = pawams->tetwahedwaw_9.wut0;
		wut1 = pawams->tetwahedwaw_9.wut1;
		wut2 = pawams->tetwahedwaw_9.wut2;
		wut3 = pawams->tetwahedwaw_9.wut3;
		wut_size0 = sizeof(pawams->tetwahedwaw_9.wut0)/
				sizeof(pawams->tetwahedwaw_9.wut0[0]);
		wut_size  = sizeof(pawams->tetwahedwaw_9.wut1)/
				sizeof(pawams->tetwahedwaw_9.wut1[0]);
		}

	mpc32_sewect_3dwut_wam(mpc, mode,
				is_12bits_cowow_channew, mpcc_id);
	mpc32_sewect_3dwut_wam_mask(mpc, 0x1, mpcc_id);
	if (is_12bits_cowow_channew)
		mpc32_set3dwut_wam12(mpc, wut0, wut_size0, mpcc_id);
	ewse
		mpc32_set3dwut_wam10(mpc, wut0, wut_size0, mpcc_id);

	mpc32_sewect_3dwut_wam_mask(mpc, 0x2, mpcc_id);
	if (is_12bits_cowow_channew)
		mpc32_set3dwut_wam12(mpc, wut1, wut_size, mpcc_id);
	ewse
		mpc32_set3dwut_wam10(mpc, wut1, wut_size, mpcc_id);

	mpc32_sewect_3dwut_wam_mask(mpc, 0x4, mpcc_id);
	if (is_12bits_cowow_channew)
		mpc32_set3dwut_wam12(mpc, wut2, wut_size, mpcc_id);
	ewse
		mpc32_set3dwut_wam10(mpc, wut2, wut_size, mpcc_id);

	mpc32_sewect_3dwut_wam_mask(mpc, 0x8, mpcc_id);
	if (is_12bits_cowow_channew)
		mpc32_set3dwut_wam12(mpc, wut3, wut_size, mpcc_id);
	ewse
		mpc32_set3dwut_wam10(mpc, wut3, wut_size, mpcc_id);

	mpc32_set_3dwut_mode(mpc, mode, is_12bits_cowow_channew,
					is_17x17x17, mpcc_id);

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc)
		mpc32_powew_on_shapew_3dwut(mpc, mpcc_id, fawse);

	wetuwn twue;
}

static const stwuct mpc_funcs dcn32_mpc_funcs = {
	.wead_mpcc_state = mpc1_wead_mpcc_state,
	.insewt_pwane = mpc1_insewt_pwane,
	.wemove_mpcc = mpc1_wemove_mpcc,
	.mpc_init = mpc32_mpc_init,
	.mpc_init_singwe_inst = mpc1_mpc_init_singwe_inst,
	.update_bwending = mpc2_update_bwending,
	.cuwsow_wock = mpc1_cuwsow_wock,
	.get_mpcc_fow_dpp = mpc1_get_mpcc_fow_dpp,
	.wait_fow_idwe = mpc2_assewt_idwe_mpcc,
	.assewt_mpcc_idwe_befowe_connect = mpc2_assewt_mpcc_idwe_befowe_connect,
	.init_mpcc_wist_fwom_hw = mpc1_init_mpcc_wist_fwom_hw,
	.set_denowm =  mpc3_set_denowm,
	.set_denowm_cwamp = mpc3_set_denowm_cwamp,
	.set_output_csc = mpc3_set_output_csc,
	.set_ocsc_defauwt = mpc3_set_ocsc_defauwt,
	.set_output_gamma = mpc3_set_output_gamma,
	.insewt_pwane_to_secondawy = NUWW,
	.wemove_mpcc_fwom_secondawy =  NUWW,
	.set_dwb_mux = mpc3_set_dwb_mux,
	.disabwe_dwb_mux = mpc3_disabwe_dwb_mux,
	.is_dwb_idwe = mpc3_is_dwb_idwe,
	.set_out_wate_contwow = mpc3_set_out_wate_contwow,
	.set_gamut_wemap = mpc3_set_gamut_wemap,
	.pwogwam_shapew = mpc32_pwogwam_shapew,
	.pwogwam_3dwut = mpc32_pwogwam_3dwut,
	.pwogwam_1dwut = mpc32_pwogwam_post1dwut,
	.acquiwe_wmu = NUWW,
	.wewease_wmu = NUWW,
	.powew_on_mpc_mem_pww = mpc3_powew_on_ogam_wut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
	.set_bg_cowow = mpc1_set_bg_cowow,
};


void dcn32_mpc_constwuct(stwuct dcn30_mpc *mpc30,
	stwuct dc_context *ctx,
	const stwuct dcn30_mpc_wegistews *mpc_wegs,
	const stwuct dcn30_mpc_shift *mpc_shift,
	const stwuct dcn30_mpc_mask *mpc_mask,
	int num_mpcc,
	int num_wmu)
{
	int i;

	mpc30->base.ctx = ctx;

	mpc30->base.funcs = &dcn32_mpc_funcs;

	mpc30->mpc_wegs = mpc_wegs;
	mpc30->mpc_shift = mpc_shift;
	mpc30->mpc_mask = mpc_mask;

	mpc30->mpcc_in_use_mask = 0;
	mpc30->num_mpcc = num_mpcc;
	mpc30->num_wmu = num_wmu;

	fow (i = 0; i < MAX_MPCC; i++)
		mpc3_init_mpcc(&mpc30->base.mpcc_awway[i], i);
}
