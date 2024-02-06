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

#incwude "weg_hewpew.h"
#incwude "dcn30_mpc.h"
#incwude "dcn30_cm_common.h"
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


#define NUM_EWEMENTS(a) (sizeof(a) / sizeof((a)[0]))


boow mpc3_is_dwb_idwe(
	stwuct mpc *mpc,
	int dwb_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	unsigned int status;

	WEG_GET(DWB_MUX[dwb_id], MPC_DWB0_MUX_STATUS, &status);

	if (status == 0xf)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void mpc3_set_dwb_mux(
	stwuct mpc *mpc,
	int dwb_id,
	int mpcc_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET(DWB_MUX[dwb_id], 0,
		MPC_DWB0_MUX, mpcc_id);
}

void mpc3_disabwe_dwb_mux(
	stwuct mpc *mpc,
	int dwb_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET(DWB_MUX[dwb_id], 0,
		MPC_DWB0_MUX, 0xf);
}

void mpc3_set_out_wate_contwow(
	stwuct mpc *mpc,
	int opp_id,
	boow enabwe,
	boow wate_2x_mode,
	stwuct mpc_dwb_fwow_contwow *fwow_contwow)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE_2(MUX[opp_id],
			MPC_OUT_WATE_CONTWOW_DISABWE, !enabwe,
			MPC_OUT_WATE_CONTWOW, wate_2x_mode);

	if (fwow_contwow)
		WEG_UPDATE_2(MUX[opp_id],
			MPC_OUT_FWOW_CONTWOW_MODE, fwow_contwow->fwow_ctww_mode,
			MPC_OUT_FWOW_CONTWOW_COUNT, fwow_contwow->fwow_ctww_cnt1);
}

enum dc_wut_mode mpc3_get_ogam_cuwwent(stwuct mpc *mpc, int mpcc_id)
{
	/*Contwawy to DCN2 and DCN1 whewein a singwe status wegistew fiewd howds this info;
	 *in DCN3/3AG, we need to wead two sepawate fiewds to wetwieve the same info
	 */
	enum dc_wut_mode mode;
	uint32_t state_mode;
	uint32_t state_wam_wut_in_use;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET_2(MPCC_OGAM_CONTWOW[mpcc_id], MPCC_OGAM_MODE_CUWWENT, &state_mode,
		  MPCC_OGAM_SEWECT_CUWWENT, &state_wam_wut_in_use);

	switch (state_mode) {
	case 0:
		mode = WUT_BYPASS;
		bweak;
	case 2:
		switch (state_wam_wut_in_use) {
		case 0:
			mode = WUT_WAM_A;
			bweak;
		case 1:
			mode = WUT_WAM_B;
			bweak;
		defauwt:
			mode = WUT_BYPASS;
			bweak;
		}
		bweak;
	defauwt:
		mode = WUT_BYPASS;
		bweak;
	}

	wetuwn mode;
}

void mpc3_powew_on_ogam_wut(
		stwuct mpc *mpc, int mpcc_id,
		boow powew_on)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	/*
	 * Powewing on: fowce memowy active so the WUT can be updated.
	 * Powewing off: awwow entewing memowy wow powew mode
	 *
	 * Memowy wow powew mode is contwowwed duwing MPC OGAM WUT init.
	 */
	WEG_UPDATE(MPCC_MEM_PWW_CTWW[mpcc_id],
		   MPCC_OGAM_MEM_PWW_DIS, powew_on != 0);

	/* Wait fow memowy to be powewed on - we won't be abwe to wwite to it othewwise. */
	if (powew_on)
		WEG_WAIT(MPCC_MEM_PWW_CTWW[mpcc_id], MPCC_OGAM_MEM_PWW_STATE, 0, 10, 10);
}

static void mpc3_configuwe_ogam_wut(
		stwuct mpc *mpc, int mpcc_id,
		boow is_wam_a)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE_2(MPCC_OGAM_WUT_CONTWOW[mpcc_id],
			MPCC_OGAM_WUT_WWITE_COWOW_MASK, 7,
			MPCC_OGAM_WUT_HOST_SEW, is_wam_a == twue ? 0:1);

	WEG_SET(MPCC_OGAM_WUT_INDEX[mpcc_id], 0, MPCC_OGAM_WUT_INDEX, 0);
}

static void mpc3_ogam_get_weg_fiewd(
		stwuct mpc *mpc,
		stwuct dcn3_xfew_func_weg *weg)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	weg->shifts.fiewd_wegion_stawt_base = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_BASE_B;
	weg->masks.fiewd_wegion_stawt_base = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_BASE_B;
	weg->shifts.fiewd_offset = mpc30->mpc_shift->MPCC_OGAM_WAMA_OFFSET_B;
	weg->masks.fiewd_offset = mpc30->mpc_mask->MPCC_OGAM_WAMA_OFFSET_B;

	weg->shifts.exp_wegion0_wut_offset = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;

	weg->shifts.fiewd_wegion_end = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SWOPE_B;
	weg->shifts.exp_wegion_stawt = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = mpc30->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = mpc30->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
}

static void mpc3_pwogwam_wuta(stwuct mpc *mpc, int mpcc_id,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	stwuct dcn3_xfew_func_weg gam_wegs;

	mpc3_ogam_get_weg_fiewd(mpc, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_OGAM_WAMA_STAWT_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_OGAM_WAMA_STAWT_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_OGAM_WAMA_STAWT_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_OGAM_WAMA_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_OGAM_WAMA_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_OGAM_WAMA_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_OGAM_WAMA_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_OGAM_WAMA_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_OGAM_WAMA_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_OGAM_WAMA_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_OGAM_WAMA_WEGION_32_33[mpcc_id]);
	//New wegistews in DCN3AG/DCN OGAM bwock
	gam_wegs.offset_b =  WEG(MPCC_OGAM_WAMA_OFFSET_B[mpcc_id]);
	gam_wegs.offset_g =  WEG(MPCC_OGAM_WAMA_OFFSET_G[mpcc_id]);
	gam_wegs.offset_w =  WEG(MPCC_OGAM_WAMA_OFFSET_W[mpcc_id]);
	gam_wegs.stawt_base_cntw_b = WEG(MPCC_OGAM_WAMA_STAWT_BASE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_base_cntw_g = WEG(MPCC_OGAM_WAMA_STAWT_BASE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_base_cntw_w = WEG(MPCC_OGAM_WAMA_STAWT_BASE_CNTW_W[mpcc_id]);

	cm_hewpew_pwogwam_gamcow_xfew_func(mpc30->base.ctx, pawams, &gam_wegs);
}

static void mpc3_pwogwam_wutb(stwuct mpc *mpc, int mpcc_id,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	stwuct dcn3_xfew_func_weg gam_wegs;

	mpc3_ogam_get_weg_fiewd(mpc, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_OGAM_WAMB_STAWT_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_OGAM_WAMB_STAWT_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_OGAM_WAMB_STAWT_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_OGAM_WAMB_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_OGAM_WAMB_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_OGAM_WAMB_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_OGAM_WAMB_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_OGAM_WAMB_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_OGAM_WAMB_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_OGAM_WAMB_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_OGAM_WAMB_WEGION_32_33[mpcc_id]);
	//New wegistews in DCN3AG/DCN OGAM bwock
	gam_wegs.offset_b =  WEG(MPCC_OGAM_WAMB_OFFSET_B[mpcc_id]);
	gam_wegs.offset_g =  WEG(MPCC_OGAM_WAMB_OFFSET_G[mpcc_id]);
	gam_wegs.offset_w =  WEG(MPCC_OGAM_WAMB_OFFSET_W[mpcc_id]);
	gam_wegs.stawt_base_cntw_b = WEG(MPCC_OGAM_WAMB_STAWT_BASE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_base_cntw_g = WEG(MPCC_OGAM_WAMB_STAWT_BASE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_base_cntw_w = WEG(MPCC_OGAM_WAMB_STAWT_BASE_CNTW_W[mpcc_id]);

	cm_hewpew_pwogwam_gamcow_xfew_func(mpc30->base.ctx, pawams, &gam_wegs);
}


static void mpc3_pwogwam_ogam_pww(
		stwuct mpc *mpc, int mpcc_id,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num)
{
	uint32_t i;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (is_wgb_equaw(wgb,  num)) {
		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].wed_weg);
	} ewse {

		WEG_UPDATE(MPCC_OGAM_WUT_CONTWOW[mpcc_id],
				MPCC_OGAM_WUT_WWITE_COWOW_MASK, 4);

		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].wed_weg);

		WEG_SET(MPCC_OGAM_WUT_INDEX[mpcc_id], 0, MPCC_OGAM_WUT_INDEX, 0);

		WEG_UPDATE(MPCC_OGAM_WUT_CONTWOW[mpcc_id],
				MPCC_OGAM_WUT_WWITE_COWOW_MASK, 2);

		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].gween_weg);

		WEG_SET(MPCC_OGAM_WUT_INDEX[mpcc_id], 0, MPCC_OGAM_WUT_INDEX, 0);

		WEG_UPDATE(MPCC_OGAM_WUT_CONTWOW[mpcc_id],
				MPCC_OGAM_WUT_WWITE_COWOW_MASK, 1);

		fow (i = 0 ; i < num; i++)
			WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].bwue_weg);

	}

}

void mpc3_set_output_gamma(
		stwuct mpc *mpc,
		int mpcc_id,
		const stwuct pww_pawams *pawams)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (mpc->ctx->dc->debug.cm_in_bypass) {
		WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		wetuwn;
	}

	if (pawams == NUWW) { //disabwe OGAM
		WEG_SET(MPCC_OGAM_CONTWOW[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		wetuwn;
	}
	//enabwe OGAM
	WEG_SET(MPCC_OGAM_CONTWOW[mpcc_id], 0, MPCC_OGAM_MODE, 2);

	cuwwent_mode = mpc3_get_ogam_cuwwent(mpc, mpcc_id);
	if (cuwwent_mode == WUT_BYPASS)
		next_mode = WUT_WAM_A;
	ewse if (cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	mpc3_powew_on_ogam_wut(mpc, mpcc_id, twue);
	mpc3_configuwe_ogam_wut(mpc, mpcc_id, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_A)
		mpc3_pwogwam_wuta(mpc, mpcc_id, pawams);
	ewse
		mpc3_pwogwam_wutb(mpc, mpcc_id, pawams);

	mpc3_pwogwam_ogam_pww(
			mpc, mpcc_id, pawams->wgb_wesuwted, pawams->hw_points_num);

	/*we need to pwogwam 2 fiewds hewe as apposed to 1*/
	WEG_UPDATE(MPCC_OGAM_CONTWOW[mpcc_id],
			MPCC_OGAM_SEWECT, next_mode == WUT_WAM_A ? 0:1);

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc)
		mpc3_powew_on_ogam_wut(mpc, mpcc_id, fawse);
}

void mpc3_set_denowm(
		stwuct mpc *mpc,
		int opp_id,
		enum dc_cowow_depth output_depth)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	/* De-nowmawize Fixed U1.13 cowow data to diffewent tawget bit depths. 0 is bypass*/
	int denowm_mode = 0;

	switch (output_depth) {
	case COWOW_DEPTH_666:
		denowm_mode = 1;
		bweak;
	case COWOW_DEPTH_888:
		denowm_mode = 2;
		bweak;
	case COWOW_DEPTH_999:
		denowm_mode = 3;
		bweak;
	case COWOW_DEPTH_101010:
		denowm_mode = 4;
		bweak;
	case COWOW_DEPTH_111111:
		denowm_mode = 5;
		bweak;
	case COWOW_DEPTH_121212:
		denowm_mode = 6;
		bweak;
	case COWOW_DEPTH_141414:
	case COWOW_DEPTH_161616:
	defauwt:
		/* not vawid used case! */
		bweak;
	}

	WEG_UPDATE(DENOWM_CONTWOW[opp_id],
			MPC_OUT_DENOWM_MODE, denowm_mode);
}

void mpc3_set_denowm_cwamp(
		stwuct mpc *mpc,
		int opp_id,
		stwuct mpc_denowm_cwamp denowm_cwamp)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	/*pwogwam min and max cwamp vawues fow the pixew components*/
	WEG_UPDATE_2(DENOWM_CONTWOW[opp_id],
			MPC_OUT_DENOWM_CWAMP_MAX_W_CW, denowm_cwamp.cwamp_max_w_cw,
			MPC_OUT_DENOWM_CWAMP_MIN_W_CW, denowm_cwamp.cwamp_min_w_cw);
	WEG_UPDATE_2(DENOWM_CWAMP_G_Y[opp_id],
			MPC_OUT_DENOWM_CWAMP_MAX_G_Y, denowm_cwamp.cwamp_max_g_y,
			MPC_OUT_DENOWM_CWAMP_MIN_G_Y, denowm_cwamp.cwamp_min_g_y);
	WEG_UPDATE_2(DENOWM_CWAMP_B_CB[opp_id],
			MPC_OUT_DENOWM_CWAMP_MAX_B_CB, denowm_cwamp.cwamp_max_b_cb,
			MPC_OUT_DENOWM_CWAMP_MIN_B_CB, denowm_cwamp.cwamp_min_b_cb);
}

static enum dc_wut_mode mpc3_get_shapew_cuwwent(stwuct mpc *mpc, uint32_t wmu_idx)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET(SHAPEW_CONTWOW[wmu_idx], MPC_WMU_SHAPEW_WUT_MODE_CUWWENT, &state_mode);

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

static void mpc3_configuwe_shapew_wut(
		stwuct mpc *mpc,
		boow is_wam_a,
		uint32_t wmu_idx)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE(SHAPEW_WUT_WWITE_EN_MASK[wmu_idx],
			MPC_WMU_SHAPEW_WUT_WWITE_EN_MASK, 7);
	WEG_UPDATE(SHAPEW_WUT_WWITE_EN_MASK[wmu_idx],
			MPC_WMU_SHAPEW_WUT_WWITE_SEW, is_wam_a == twue ? 0:1);
	WEG_SET(SHAPEW_WUT_INDEX[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_INDEX, 0);
}

static void mpc3_pwogwam_shapew_wuta_settings(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t wmu_idx)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET_2(SHAPEW_WAMA_STAWT_CNTW_B[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(SHAPEW_WAMA_STAWT_CNTW_G[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].gween.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(SHAPEW_WAMA_STAWT_CNTW_W[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].wed.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);

	WEG_SET_2(SHAPEW_WAMA_END_CNTW_B[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);
	WEG_SET_2(SHAPEW_WAMA_END_CNTW_G[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].gween.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].gween.custom_fwoat_y);
	WEG_SET_2(SHAPEW_WAMA_END_CNTW_W[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].wed.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(SHAPEW_WAMA_WEGION_0_1[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_2_3[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_4_5[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_6_7[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_8_9[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_10_11[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_12_13[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_14_15[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_16_17[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_18_19[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_20_21[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_22_23[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_24_25[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_26_27[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_28_29[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_30_31[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMA_WEGION_32_33[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
}

static void mpc3_pwogwam_shapew_wutb_settings(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t wmu_idx)
{
	const stwuct gamma_cuwve *cuwve;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_SET_2(SHAPEW_WAMB_STAWT_CNTW_B[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].bwue.custom_fwoat_x,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(SHAPEW_WAMB_STAWT_CNTW_G[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].gween.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);
	WEG_SET_2(SHAPEW_WAMB_STAWT_CNTW_W[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_B, pawams->cownew_points[0].wed.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_STAWT_SEGMENT_B, 0);

	WEG_SET_2(SHAPEW_WAMB_END_CNTW_B[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].bwue.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].bwue.custom_fwoat_y);
	WEG_SET_2(SHAPEW_WAMB_END_CNTW_G[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].gween.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].gween.custom_fwoat_y);
	WEG_SET_2(SHAPEW_WAMB_END_CNTW_W[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_B, pawams->cownew_points[1].wed.custom_fwoat_x,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION_END_BASE_B, pawams->cownew_points[1].wed.custom_fwoat_y);

	cuwve = pawams->aww_cuwve_points;
	WEG_SET_4(SHAPEW_WAMB_WEGION_0_1[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_2_3[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_4_5[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_6_7[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_8_9[wmu_idx], 0,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_10_11[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_12_13[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_14_15[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);


	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_16_17[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_18_19[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_20_21[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_22_23[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_24_25[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_26_27[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_28_29[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_30_31[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);

	cuwve += 2;
	WEG_SET_4(SHAPEW_WAMB_WEGION_32_33[wmu_idx], 0,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
			MPC_WMU_SHAPEW_WAMA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
}


static void mpc3_pwogwam_shapew_wut(
		stwuct mpc *mpc,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num,
		uint32_t wmu_idx)
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

		WEG_SET(SHAPEW_WUT_DATA[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_DATA, wed_vawue);
		WEG_SET(SHAPEW_WUT_DATA[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_DATA, gween_vawue);
		WEG_SET(SHAPEW_WUT_DATA[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_DATA, bwue_vawue);
	}

}

static void mpc3_powew_on_shapew_3dwut(
		stwuct mpc *mpc,
		uint32_t wmu_idx,
	boow powew_on)
{
	uint32_t powew_status_shapew = 2;
	uint32_t powew_status_3dwut  = 2;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int max_wetwies = 10;

	if (wmu_idx == 0) {
		WEG_SET(MPC_WMU_MEM_PWW_CTWW, 0,
			MPC_WMU0_MEM_PWW_DIS, powew_on == twue ? 1:0);
		/* wait fow memowy to fuwwy powew up */
		if (powew_on && mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc) {
			WEG_WAIT(MPC_WMU_MEM_PWW_CTWW, MPC_WMU0_SHAPEW_MEM_PWW_STATE, 0, 1, max_wetwies);
			WEG_WAIT(MPC_WMU_MEM_PWW_CTWW, MPC_WMU0_3DWUT_MEM_PWW_STATE, 0, 1, max_wetwies);
		}

		/*wead status is not mandatowy, it is just fow debugging*/
		WEG_GET(MPC_WMU_MEM_PWW_CTWW, MPC_WMU0_SHAPEW_MEM_PWW_STATE, &powew_status_shapew);
		WEG_GET(MPC_WMU_MEM_PWW_CTWW, MPC_WMU0_3DWUT_MEM_PWW_STATE, &powew_status_3dwut);
	} ewse if (wmu_idx == 1) {
		WEG_SET(MPC_WMU_MEM_PWW_CTWW, 0,
			MPC_WMU1_MEM_PWW_DIS, powew_on == twue ? 1:0);
		if (powew_on && mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc) {
			WEG_WAIT(MPC_WMU_MEM_PWW_CTWW, MPC_WMU1_SHAPEW_MEM_PWW_STATE, 0, 1, max_wetwies);
			WEG_WAIT(MPC_WMU_MEM_PWW_CTWW, MPC_WMU1_3DWUT_MEM_PWW_STATE, 0, 1, max_wetwies);
		}

		WEG_GET(MPC_WMU_MEM_PWW_CTWW, MPC_WMU1_SHAPEW_MEM_PWW_STATE, &powew_status_shapew);
		WEG_GET(MPC_WMU_MEM_PWW_CTWW, MPC_WMU1_3DWUT_MEM_PWW_STATE, &powew_status_3dwut);
	}
	/*TODO Add wmu_idx == 2 fow SIENNA_CICHWID */
	if (powew_status_shapew != 0 && powew_on == twue)
		BWEAK_TO_DEBUGGEW();

	if (powew_status_3dwut != 0 && powew_on == twue)
		BWEAK_TO_DEBUGGEW();
}



boow mpc3_pwogwam_shapew(
		stwuct mpc *mpc,
		const stwuct pww_pawams *pawams,
		uint32_t wmu_idx)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;

	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (pawams == NUWW) {
		WEG_SET(SHAPEW_CONTWOW[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_MODE, 0);
		wetuwn fawse;
	}

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc)
		mpc3_powew_on_shapew_3dwut(mpc, wmu_idx, twue);

	cuwwent_mode = mpc3_get_shapew_cuwwent(mpc, wmu_idx);

	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	mpc3_configuwe_shapew_wut(mpc, next_mode == WUT_WAM_A, wmu_idx);

	if (next_mode == WUT_WAM_A)
		mpc3_pwogwam_shapew_wuta_settings(mpc, pawams, wmu_idx);
	ewse
		mpc3_pwogwam_shapew_wutb_settings(mpc, pawams, wmu_idx);

	mpc3_pwogwam_shapew_wut(
			mpc, pawams->wgb_wesuwted, pawams->hw_points_num, wmu_idx);

	WEG_SET(SHAPEW_CONTWOW[wmu_idx], 0, MPC_WMU_SHAPEW_WUT_MODE, next_mode == WUT_WAM_A ? 1:2);
	mpc3_powew_on_shapew_3dwut(mpc, wmu_idx, fawse);

	wetuwn twue;
}

static void mpc3_set_3dwut_mode(
		stwuct mpc *mpc,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits,
		boow is_wut_size17x17x17,
		uint32_t wmu_idx)
{
	uint32_t wut_mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (mode == WUT_BYPASS)
		wut_mode = 0;
	ewse if (mode == WUT_WAM_A)
		wut_mode = 1;
	ewse
		wut_mode = 2;

	WEG_UPDATE_2(WMU_3DWUT_MODE[wmu_idx],
			MPC_WMU_3DWUT_MODE, wut_mode,
			MPC_WMU_3DWUT_SIZE, is_wut_size17x17x17 == twue ? 0 : 1);
}

static enum dc_wut_mode get3dwut_config(
			stwuct mpc *mpc,
			boow *is_17x17x17,
			boow *is_12bits_cowow_channew,
			int wmu_idx)
{
	uint32_t i_mode, i_enabwe_10bits, wut_size;
	enum dc_wut_mode mode;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_GET(WMU_3DWUT_MODE[wmu_idx],
			MPC_WMU_3DWUT_MODE_CUWWENT,  &i_mode);

	WEG_GET(WMU_3DWUT_WEAD_WWITE_CONTWOW[wmu_idx],
			MPC_WMU_3DWUT_30BIT_EN, &i_enabwe_10bits);

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

	WEG_GET(WMU_3DWUT_MODE[wmu_idx], MPC_WMU_3DWUT_SIZE, &wut_size);

	if (wut_size == 0)
		*is_17x17x17 = twue;
	ewse
		*is_17x17x17 = fawse;

	wetuwn mode;
}

static void mpc3_sewect_3dwut_wam(
		stwuct mpc *mpc,
		enum dc_wut_mode mode,
		boow is_cowow_channew_12bits,
		uint32_t wmu_idx)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE_2(WMU_3DWUT_WEAD_WWITE_CONTWOW[wmu_idx],
		MPC_WMU_3DWUT_WAM_SEW, mode == WUT_WAM_A ? 0 : 1,
		MPC_WMU_3DWUT_30BIT_EN, is_cowow_channew_12bits == twue ? 0:1);
}

static void mpc3_sewect_3dwut_wam_mask(
		stwuct mpc *mpc,
		uint32_t wam_sewection_mask,
		uint32_t wmu_idx)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	WEG_UPDATE(WMU_3DWUT_WEAD_WWITE_CONTWOW[wmu_idx], MPC_WMU_3DWUT_WWITE_EN_MASK,
			wam_sewection_mask);
	WEG_SET(WMU_3DWUT_INDEX[wmu_idx], 0, MPC_WMU_3DWUT_INDEX, 0);
}

static void mpc3_set3dwut_wam12(
		stwuct mpc *mpc,
		const stwuct dc_wgb *wut,
		uint32_t entwies,
		uint32_t wmu_idx)
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

		WEG_SET_2(WMU_3DWUT_DATA[wmu_idx], 0,
				MPC_WMU_3DWUT_DATA0, wed,
				MPC_WMU_3DWUT_DATA1, wed1);

		WEG_SET_2(WMU_3DWUT_DATA[wmu_idx], 0,
				MPC_WMU_3DWUT_DATA0, gween,
				MPC_WMU_3DWUT_DATA1, gween1);

		WEG_SET_2(WMU_3DWUT_DATA[wmu_idx], 0,
				MPC_WMU_3DWUT_DATA0, bwue,
				MPC_WMU_3DWUT_DATA1, bwue1);
	}
}

static void mpc3_set3dwut_wam10(
		stwuct mpc *mpc,
		const stwuct dc_wgb *wut,
		uint32_t entwies,
		uint32_t wmu_idx)
{
	uint32_t i, wed, gween, bwue, vawue;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	fow (i = 0; i < entwies; i++) {
		wed   = wut[i].wed;
		gween = wut[i].gween;
		bwue  = wut[i].bwue;
		//shouwd we shift wed 22bit and gween 12? ask Nvenko
		vawue = (wed<<20) | (gween<<10) | bwue;

		WEG_SET(WMU_3DWUT_DATA_30BIT[wmu_idx], 0, MPC_WMU_3DWUT_DATA_30BIT, vawue);
	}

}


void mpc3_init_mpcc(stwuct mpcc *mpcc, int mpcc_inst)
{
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = NUWW;
	mpcc->bwnd_cfg.ovewwap_onwy = fawse;
	mpcc->bwnd_cfg.gwobaw_awpha = 0xff;
	mpcc->bwnd_cfg.gwobaw_gain = 0xff;
	mpcc->bwnd_cfg.backgwound_cowow_bpc = 4;
	mpcc->bwnd_cfg.bottom_gain_mode = 0;
	mpcc->bwnd_cfg.top_gain = 0x1f000;
	mpcc->bwnd_cfg.bottom_inside_gain = 0x1f000;
	mpcc->bwnd_cfg.bottom_outside_gain = 0x1f000;
	mpcc->sm_cfg.enabwe = fawse;
	mpcc->shawed_bottom = fawse;
}

static void pwogwam_gamut_wemap(
		stwuct dcn30_mpc *mpc30,
		int mpcc_id,
		const uint16_t *wegvaw,
		int sewect)
{
	uint16_t sewection = 0;
	stwuct cowow_matwices_weg gam_wegs;

	if (wegvaw == NUWW || sewect == GAMUT_WEMAP_BYPASS) {
		WEG_SET(MPCC_GAMUT_WEMAP_MODE[mpcc_id], 0,
				MPCC_GAMUT_WEMAP_MODE, GAMUT_WEMAP_BYPASS);
		wetuwn;
	}
	switch (sewect) {
	case GAMUT_WEMAP_COEFF:
		sewection = 1;
		bweak;
		/*this cowwesponds to GAMUT_WEMAP coefficients set B
		 * we don't have common coefficient sets in dcn3ag/dcn3
		 */
	case GAMUT_WEMAP_COMA_COEFF:
		sewection = 2;
		bweak;
	defauwt:
		bweak;
	}

	gam_wegs.shifts.csc_c11 = mpc30->mpc_shift->MPCC_GAMUT_WEMAP_C11_A;
	gam_wegs.masks.csc_c11  = mpc30->mpc_mask->MPCC_GAMUT_WEMAP_C11_A;
	gam_wegs.shifts.csc_c12 = mpc30->mpc_shift->MPCC_GAMUT_WEMAP_C12_A;
	gam_wegs.masks.csc_c12 = mpc30->mpc_mask->MPCC_GAMUT_WEMAP_C12_A;


	if (sewect == GAMUT_WEMAP_COEFF) {
		gam_wegs.csc_c11_c12 = WEG(MPC_GAMUT_WEMAP_C11_C12_A[mpcc_id]);
		gam_wegs.csc_c33_c34 = WEG(MPC_GAMUT_WEMAP_C33_C34_A[mpcc_id]);

		cm_hewpew_pwogwam_cowow_matwices(
				mpc30->base.ctx,
				wegvaw,
				&gam_wegs);

	} ewse  if (sewect == GAMUT_WEMAP_COMA_COEFF) {

		gam_wegs.csc_c11_c12 = WEG(MPC_GAMUT_WEMAP_C11_C12_B[mpcc_id]);
		gam_wegs.csc_c33_c34 = WEG(MPC_GAMUT_WEMAP_C33_C34_B[mpcc_id]);

		cm_hewpew_pwogwam_cowow_matwices(
				mpc30->base.ctx,
				wegvaw,
				&gam_wegs);

	}
	//sewect coefficient set to use
	WEG_SET(MPCC_GAMUT_WEMAP_MODE[mpcc_id], 0,
					MPCC_GAMUT_WEMAP_MODE, sewection);
}

void mpc3_set_gamut_wemap(
		stwuct mpc *mpc,
		int mpcc_id,
		const stwuct mpc_gwph_gamut_adjustment *adjust)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int i = 0;
	int gamut_mode;

	if (adjust->gamut_adjust_type != GWAPHICS_GAMUT_ADJUST_TYPE_SW)
		pwogwam_gamut_wemap(mpc30, mpcc_id, NUWW, GAMUT_WEMAP_BYPASS);
	ewse {
		stwuct fixed31_32 aww_matwix[12];
		uint16_t aww_weg_vaw[12];

		fow (i = 0; i < 12; i++)
			aww_matwix[i] = adjust->tempewatuwe_matwix[i];

		convewt_fwoat_matwix(
			aww_weg_vaw, aww_matwix, 12);

		//cuwwent coefficient set in use
		WEG_GET(MPCC_GAMUT_WEMAP_MODE[mpcc_id], MPCC_GAMUT_WEMAP_MODE_CUWWENT, &gamut_mode);

		if (gamut_mode == 0)
			gamut_mode = 1; //use coefficient set A
		ewse if (gamut_mode == 1)
			gamut_mode = 2;
		ewse
			gamut_mode = 1;

		pwogwam_gamut_wemap(mpc30, mpcc_id, aww_weg_vaw, gamut_mode);
	}
}

boow mpc3_pwogwam_3dwut(
		stwuct mpc *mpc,
		const stwuct tetwahedwaw_pawams *pawams,
		int wmu_idx)
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
		mpc3_set_3dwut_mode(mpc, WUT_BYPASS, fawse, fawse, wmu_idx);
		wetuwn fawse;
	}
	mpc3_powew_on_shapew_3dwut(mpc, wmu_idx, twue);

	mode = get3dwut_config(mpc, &is_17x17x17, &is_12bits_cowow_channew, wmu_idx);

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

	mpc3_sewect_3dwut_wam(mpc, mode,
				is_12bits_cowow_channew, wmu_idx);
	mpc3_sewect_3dwut_wam_mask(mpc, 0x1, wmu_idx);
	if (is_12bits_cowow_channew)
		mpc3_set3dwut_wam12(mpc, wut0, wut_size0, wmu_idx);
	ewse
		mpc3_set3dwut_wam10(mpc, wut0, wut_size0, wmu_idx);

	mpc3_sewect_3dwut_wam_mask(mpc, 0x2, wmu_idx);
	if (is_12bits_cowow_channew)
		mpc3_set3dwut_wam12(mpc, wut1, wut_size, wmu_idx);
	ewse
		mpc3_set3dwut_wam10(mpc, wut1, wut_size, wmu_idx);

	mpc3_sewect_3dwut_wam_mask(mpc, 0x4, wmu_idx);
	if (is_12bits_cowow_channew)
		mpc3_set3dwut_wam12(mpc, wut2, wut_size, wmu_idx);
	ewse
		mpc3_set3dwut_wam10(mpc, wut2, wut_size, wmu_idx);

	mpc3_sewect_3dwut_wam_mask(mpc, 0x8, wmu_idx);
	if (is_12bits_cowow_channew)
		mpc3_set3dwut_wam12(mpc, wut3, wut_size, wmu_idx);
	ewse
		mpc3_set3dwut_wam10(mpc, wut3, wut_size, wmu_idx);

	mpc3_set_3dwut_mode(mpc, mode, is_12bits_cowow_channew,
					is_17x17x17, wmu_idx);

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc)
		mpc3_powew_on_shapew_3dwut(mpc, wmu_idx, fawse);

	wetuwn twue;
}

void mpc3_set_output_csc(
		stwuct mpc *mpc,
		int opp_id,
		const uint16_t *wegvaw,
		enum mpc_output_csc_mode ocsc_mode)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	stwuct cowow_matwices_weg ocsc_wegs;

	WEG_WWITE(MPC_OUT_CSC_COEF_FOWMAT, 0);

	WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);

	if (ocsc_mode == MPC_OUTPUT_CSC_DISABWE)
		wetuwn;

	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	ocsc_wegs.shifts.csc_c11 = mpc30->mpc_shift->MPC_OCSC_C11_A;
	ocsc_wegs.masks.csc_c11  = mpc30->mpc_mask->MPC_OCSC_C11_A;
	ocsc_wegs.shifts.csc_c12 = mpc30->mpc_shift->MPC_OCSC_C12_A;
	ocsc_wegs.masks.csc_c12 = mpc30->mpc_mask->MPC_OCSC_C12_A;

	if (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_A[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_A[opp_id]);
	} ewse {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_B[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_B[opp_id]);
	}
	cm_hewpew_pwogwam_cowow_matwices(
			mpc30->base.ctx,
			wegvaw,
			&ocsc_wegs);
}

void mpc3_set_ocsc_defauwt(
		stwuct mpc *mpc,
		int opp_id,
		enum dc_cowow_space cowow_space,
		enum mpc_output_csc_mode ocsc_mode)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	uint32_t aww_size;
	stwuct cowow_matwices_weg ocsc_wegs;
	const uint16_t *wegvaw = NUWW;

	WEG_WWITE(MPC_OUT_CSC_COEF_FOWMAT, 0);

	WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
	if (ocsc_mode == MPC_OUTPUT_CSC_DISABWE)
		wetuwn;

	wegvaw = find_cowow_matwix(cowow_space, &aww_size);

	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	ocsc_wegs.shifts.csc_c11 = mpc30->mpc_shift->MPC_OCSC_C11_A;
	ocsc_wegs.masks.csc_c11  = mpc30->mpc_mask->MPC_OCSC_C11_A;
	ocsc_wegs.shifts.csc_c12 = mpc30->mpc_shift->MPC_OCSC_C12_A;
	ocsc_wegs.masks.csc_c12 = mpc30->mpc_mask->MPC_OCSC_C12_A;


	if (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_A[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_A[opp_id]);
	} ewse {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_B[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_B[opp_id]);
	}

	cm_hewpew_pwogwam_cowow_matwices(
			mpc30->base.ctx,
			wegvaw,
			&ocsc_wegs);
}

void mpc3_set_wmu_mux(
	stwuct mpc *mpc,
	int wmu_idx,
	int vawue)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (wmu_idx == 0)
		WEG_UPDATE(MPC_WMU_CONTWOW, MPC_WMU0_MUX, vawue);
	ewse if (wmu_idx == 1)
		WEG_UPDATE(MPC_WMU_CONTWOW, MPC_WMU1_MUX, vawue);

}

uint32_t mpc3_get_wmu_mux_status(
	stwuct mpc *mpc,
	int wmu_idx)
{
	uint32_t status = 0xf;
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	if (wmu_idx == 0)
		WEG_GET(MPC_WMU_CONTWOW, MPC_WMU0_MUX_STATUS, &status);
	ewse if (wmu_idx == 1)
		WEG_GET(MPC_WMU_CONTWOW, MPC_WMU1_MUX_STATUS, &status);

	wetuwn status;
}

uint32_t mpcc3_acquiwe_wmu(stwuct mpc *mpc, int mpcc_id, int wmu_idx)
{
	uint32_t wmu_status;

	//detewmine if this mpcc is awweady muwtipwexed to an WMU unit
	wmu_status = mpc3_get_wmu_mux_status(mpc, wmu_idx);
	if (wmu_status == mpcc_id)
		//wetuwn wmu_idx of pwe_acquiwed wmu unit
		wetuwn wmu_idx;

	if (wmu_status == 0xf) {//wmu unit is disabwed
		mpc3_set_wmu_mux(mpc, wmu_idx, mpcc_id);
		wetuwn wmu_idx;
	}

	//no vacant WMU units ow invawid pawametews acquiwe_post_bwdn_3dwut
	wetuwn -1;
}

static int mpcc3_wewease_wmu(stwuct mpc *mpc, int mpcc_id)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int wmu_idx;
	uint32_t wmu_status;
	int weweased_wmu = -1;

	fow (wmu_idx = 0; wmu_idx < mpc30->num_wmu; wmu_idx++) {
		wmu_status = mpc3_get_wmu_mux_status(mpc, wmu_idx);
		if (wmu_status == mpcc_id) {
			mpc3_set_wmu_mux(mpc, wmu_idx, 0xf);
			weweased_wmu = wmu_idx;
			bweak;
		}
	}
	wetuwn weweased_wmu;

}

static void mpc3_set_mpc_mem_wp_mode(stwuct mpc *mpc)
{
	stwuct dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	int mpcc_id;

	if (mpc->ctx->dc->debug.enabwe_mem_wow_powew.bits.mpc) {
		if (mpc30->mpc_mask->MPC_WMU0_MEM_WOW_PWW_MODE && mpc30->mpc_mask->MPC_WMU1_MEM_WOW_PWW_MODE) {
			WEG_UPDATE(MPC_WMU_MEM_PWW_CTWW, MPC_WMU0_MEM_WOW_PWW_MODE, 3);
			WEG_UPDATE(MPC_WMU_MEM_PWW_CTWW, MPC_WMU1_MEM_WOW_PWW_MODE, 3);
		}

		if (mpc30->mpc_mask->MPCC_OGAM_MEM_WOW_PWW_MODE) {
			fow (mpcc_id = 0; mpcc_id < mpc30->num_mpcc; mpcc_id++)
				WEG_UPDATE(MPCC_MEM_PWW_CTWW[mpcc_id], MPCC_OGAM_MEM_WOW_PWW_MODE, 3);
		}
	}
}

static const stwuct mpc_funcs dcn30_mpc_funcs = {
	.wead_mpcc_state = mpc1_wead_mpcc_state,
	.insewt_pwane = mpc1_insewt_pwane,
	.wemove_mpcc = mpc1_wemove_mpcc,
	.mpc_init = mpc1_mpc_init,
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
	.pwogwam_shapew = mpc3_pwogwam_shapew,
	.acquiwe_wmu = mpcc3_acquiwe_wmu,
	.pwogwam_3dwut = mpc3_pwogwam_3dwut,
	.wewease_wmu = mpcc3_wewease_wmu,
	.powew_on_mpc_mem_pww = mpc3_powew_on_ogam_wut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
	.set_bg_cowow = mpc1_set_bg_cowow,
	.set_mpc_mem_wp_mode = mpc3_set_mpc_mem_wp_mode,
};

void dcn30_mpc_constwuct(stwuct dcn30_mpc *mpc30,
	stwuct dc_context *ctx,
	const stwuct dcn30_mpc_wegistews *mpc_wegs,
	const stwuct dcn30_mpc_shift *mpc_shift,
	const stwuct dcn30_mpc_mask *mpc_mask,
	int num_mpcc,
	int num_wmu)
{
	int i;

	mpc30->base.ctx = ctx;

	mpc30->base.funcs = &dcn30_mpc_funcs;

	mpc30->mpc_wegs = mpc_wegs;
	mpc30->mpc_shift = mpc_shift;
	mpc30->mpc_mask = mpc_mask;

	mpc30->mpcc_in_use_mask = 0;
	mpc30->num_mpcc = num_mpcc;
	mpc30->num_wmu = num_wmu;

	fow (i = 0; i < MAX_MPCC; i++)
		mpc3_init_mpcc(&mpc30->base.mpcc_awway[i], i);
}

