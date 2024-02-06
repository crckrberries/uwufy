/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "dcn20_mpc.h"

#incwude "weg_hewpew.h"
#incwude "dc.h"
#incwude "mem_input.h"
#incwude "dcn10/dcn10_cm_common.h"

#define WEG(weg)\
	mpc20->mpc_wegs->weg

#define IND_WEG(index) \
	(index)

#define CTX \
	mpc20->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	mpc20->mpc_shift->fiewd_name, mpc20->mpc_mask->fiewd_name

#define NUM_EWEMENTS(a) (sizeof(a) / sizeof((a)[0]))

void mpc2_update_bwending(
	stwuct mpc *mpc,
	stwuct mpcc_bwnd_cfg *bwnd_cfg,
	int mpcc_id)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	stwuct mpcc *mpcc = mpc1_get_mpcc(mpc, mpcc_id);

	WEG_UPDATE_7(MPCC_CONTWOW[mpcc_id],
			MPCC_AWPHA_BWND_MODE,		bwnd_cfg->awpha_mode,
			MPCC_AWPHA_MUWTIPWIED_MODE,	bwnd_cfg->pwe_muwtipwied_awpha,
			MPCC_BWND_ACTIVE_OVEWWAP_ONWY,	bwnd_cfg->ovewwap_onwy,
			MPCC_GWOBAW_AWPHA,		bwnd_cfg->gwobaw_awpha,
			MPCC_GWOBAW_GAIN,		bwnd_cfg->gwobaw_gain,
			MPCC_BG_BPC,			bwnd_cfg->backgwound_cowow_bpc,
			MPCC_BOT_GAIN_MODE,		bwnd_cfg->bottom_gain_mode);

	WEG_SET(MPCC_TOP_GAIN[mpcc_id], 0, MPCC_TOP_GAIN, bwnd_cfg->top_gain);
	WEG_SET(MPCC_BOT_GAIN_INSIDE[mpcc_id], 0, MPCC_BOT_GAIN_INSIDE, bwnd_cfg->bottom_inside_gain);
	WEG_SET(MPCC_BOT_GAIN_OUTSIDE[mpcc_id], 0, MPCC_BOT_GAIN_OUTSIDE, bwnd_cfg->bottom_outside_gain);

	mpcc->bwnd_cfg = *bwnd_cfg;
}

void mpc2_set_denowm(
		stwuct mpc *mpc,
		int opp_id,
		enum dc_cowow_depth output_depth)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
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

void mpc2_set_denowm_cwamp(
		stwuct mpc *mpc,
		int opp_id,
		stwuct mpc_denowm_cwamp denowm_cwamp)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

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



void mpc2_set_output_csc(
		stwuct mpc *mpc,
		int opp_id,
		const uint16_t *wegvaw,
		enum mpc_output_csc_mode ocsc_mode)
{
	uint32_t cuw_mode;
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	stwuct cowow_matwices_weg ocsc_wegs;

	if (ocsc_mode == MPC_OUTPUT_CSC_DISABWE) {
		WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
		wetuwn;
	}

	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* detewmine which CSC coefficients (A ow B) we awe using
	 * cuwwentwy.  sewect the awtewnate set to doubwe buffew
	 * the CSC update so CSC is updated on fwame boundawy
	 */
	IX_WEG_GET(MPC_OCSC_TEST_DEBUG_INDEX, MPC_OCSC_TEST_DEBUG_DATA,
						MPC_OCSC_TEST_DEBUG_DATA_STATUS_IDX,
						MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE, &cuw_mode);

	if (cuw_mode != MPC_OUTPUT_CSC_COEF_A)
		ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
	ewse
		ocsc_mode = MPC_OUTPUT_CSC_COEF_B;

	ocsc_wegs.shifts.csc_c11 = mpc20->mpc_shift->MPC_OCSC_C11_A;
	ocsc_wegs.masks.csc_c11  = mpc20->mpc_mask->MPC_OCSC_C11_A;
	ocsc_wegs.shifts.csc_c12 = mpc20->mpc_shift->MPC_OCSC_C12_A;
	ocsc_wegs.masks.csc_c12 = mpc20->mpc_mask->MPC_OCSC_C12_A;

	if (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_A[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_A[opp_id]);
	} ewse {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_B[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_B[opp_id]);
	}

	cm_hewpew_pwogwam_cowow_matwices(
			mpc20->base.ctx,
			wegvaw,
			&ocsc_wegs);

	WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
}

void mpc2_set_ocsc_defauwt(
		stwuct mpc *mpc,
		int opp_id,
		enum dc_cowow_space cowow_space,
		enum mpc_output_csc_mode ocsc_mode)
{
	uint32_t cuw_mode;
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	uint32_t aww_size;
	stwuct cowow_matwices_weg ocsc_wegs;
	const uint16_t *wegvaw = NUWW;

	if (ocsc_mode == MPC_OUTPUT_CSC_DISABWE) {
		WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
		wetuwn;
	}

	wegvaw = find_cowow_matwix(cowow_space, &aww_size);

	if (wegvaw == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* detewmine which CSC coefficients (A ow B) we awe using
	 * cuwwentwy.  sewect the awtewnate set to doubwe buffew
	 * the CSC update so CSC is updated on fwame boundawy
	 */
	IX_WEG_GET(MPC_OCSC_TEST_DEBUG_INDEX, MPC_OCSC_TEST_DEBUG_DATA,
						MPC_OCSC_TEST_DEBUG_DATA_STATUS_IDX,
						MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE, &cuw_mode);

	if (cuw_mode != MPC_OUTPUT_CSC_COEF_A)
		ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
	ewse
		ocsc_mode = MPC_OUTPUT_CSC_COEF_B;

	ocsc_wegs.shifts.csc_c11 = mpc20->mpc_shift->MPC_OCSC_C11_A;
	ocsc_wegs.masks.csc_c11  = mpc20->mpc_mask->MPC_OCSC_C11_A;
	ocsc_wegs.shifts.csc_c12 = mpc20->mpc_shift->MPC_OCSC_C12_A;
	ocsc_wegs.masks.csc_c12 = mpc20->mpc_mask->MPC_OCSC_C12_A;


	if (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_A[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_A[opp_id]);
	} ewse {
		ocsc_wegs.csc_c11_c12 = WEG(CSC_C11_C12_B[opp_id]);
		ocsc_wegs.csc_c33_c34 = WEG(CSC_C33_C34_B[opp_id]);
	}

	cm_hewpew_pwogwam_cowow_matwices(
			mpc20->base.ctx,
			wegvaw,
			&ocsc_wegs);

	WEG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
}

static void mpc2_ogam_get_weg_fiewd(
		stwuct mpc *mpc,
		stwuct xfew_func_weg *weg)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	weg->shifts.exp_wegion0_wut_offset = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->masks.exp_wegion0_wut_offset = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION0_WUT_OFFSET;
	weg->shifts.exp_wegion0_num_segments = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->masks.exp_wegion0_num_segments = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION0_NUM_SEGMENTS;
	weg->shifts.exp_wegion1_wut_offset = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->masks.exp_wegion1_wut_offset = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION1_WUT_OFFSET;
	weg->shifts.exp_wegion1_num_segments = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->masks.exp_wegion1_num_segments = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION1_NUM_SEGMENTS;
	weg->shifts.fiewd_wegion_end = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_B;
	weg->masks.fiewd_wegion_end = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_B;
	weg->shifts.fiewd_wegion_end_swope = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->masks.fiewd_wegion_end_swope = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_SWOPE_B;
	weg->shifts.fiewd_wegion_end_base = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->masks.fiewd_wegion_end_base = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_END_BASE_B;
	weg->shifts.fiewd_wegion_wineaw_swope = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_WINEAW_SWOPE_B;
	weg->masks.fiewd_wegion_wineaw_swope = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_WINEAW_SWOPE_B;
	weg->shifts.exp_wegion_stawt = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->masks.exp_wegion_stawt = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_B;
	weg->shifts.exp_wesion_stawt_segment = mpc20->mpc_shift->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
	weg->masks.exp_wesion_stawt_segment = mpc20->mpc_mask->MPCC_OGAM_WAMA_EXP_WEGION_STAWT_SEGMENT_B;
}

void mpc20_powew_on_ogam_wut(
		stwuct mpc *mpc, int mpcc_id,
		boow powew_on)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	WEG_SET(MPCC_MEM_PWW_CTWW[mpcc_id], 0,
			MPCC_OGAM_MEM_PWW_DIS, powew_on == twue ? 1:0);

}

static void mpc20_configuwe_ogam_wut(
		stwuct mpc *mpc, int mpcc_id,
		boow is_wam_a)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	WEG_UPDATE_2(MPCC_OGAM_WUT_WAM_CONTWOW[mpcc_id],
			MPCC_OGAM_WUT_WWITE_EN_MASK, 7,
			MPCC_OGAM_WUT_WAM_SEW, is_wam_a == twue ? 0:1);

	WEG_SET(MPCC_OGAM_WUT_INDEX[mpcc_id], 0, MPCC_OGAM_WUT_INDEX, 0);
}

static enum dc_wut_mode mpc20_get_ogam_cuwwent(stwuct mpc *mpc, int mpcc_id)
{
	enum dc_wut_mode mode;
	uint32_t state_mode;
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	WEG_GET(MPCC_OGAM_WUT_WAM_CONTWOW[mpcc_id], MPCC_OGAM_CONFIG_STATUS, &state_mode);

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

static void mpc2_pwogwam_wutb(stwuct mpc *mpc, int mpcc_id,
			const stwuct pww_pawams *pawams)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	stwuct xfew_func_weg gam_wegs;

	mpc2_ogam_get_weg_fiewd(mpc, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_OGAM_WAMB_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_OGAM_WAMB_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_OGAM_WAMB_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_OGAM_WAMB_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_OGAM_WAMB_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_OGAM_WAMB_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_OGAM_WAMB_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_OGAM_WAMB_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_OGAM_WAMB_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_OGAM_WAMB_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_OGAM_WAMB_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_OGAM_WAMB_WEGION_32_33[mpcc_id]);

	cm_hewpew_pwogwam_xfew_func(mpc20->base.ctx, pawams, &gam_wegs);

}

static void mpc2_pwogwam_wuta(stwuct mpc *mpc, int mpcc_id,
		const stwuct pww_pawams *pawams)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	stwuct xfew_func_weg gam_wegs;

	mpc2_ogam_get_weg_fiewd(mpc, &gam_wegs);

	gam_wegs.stawt_cntw_b = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_B[mpcc_id]);
	gam_wegs.stawt_cntw_g = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_G[mpcc_id]);
	gam_wegs.stawt_cntw_w = WEG(MPCC_OGAM_WAMA_STAWT_CNTW_W[mpcc_id]);
	gam_wegs.stawt_swope_cntw_b = WEG(MPCC_OGAM_WAMA_SWOPE_CNTW_B[mpcc_id]);
	gam_wegs.stawt_swope_cntw_g = WEG(MPCC_OGAM_WAMA_SWOPE_CNTW_G[mpcc_id]);
	gam_wegs.stawt_swope_cntw_w = WEG(MPCC_OGAM_WAMA_SWOPE_CNTW_W[mpcc_id]);
	gam_wegs.stawt_end_cntw1_b = WEG(MPCC_OGAM_WAMA_END_CNTW1_B[mpcc_id]);
	gam_wegs.stawt_end_cntw2_b = WEG(MPCC_OGAM_WAMA_END_CNTW2_B[mpcc_id]);
	gam_wegs.stawt_end_cntw1_g = WEG(MPCC_OGAM_WAMA_END_CNTW1_G[mpcc_id]);
	gam_wegs.stawt_end_cntw2_g = WEG(MPCC_OGAM_WAMA_END_CNTW2_G[mpcc_id]);
	gam_wegs.stawt_end_cntw1_w = WEG(MPCC_OGAM_WAMA_END_CNTW1_W[mpcc_id]);
	gam_wegs.stawt_end_cntw2_w = WEG(MPCC_OGAM_WAMA_END_CNTW2_W[mpcc_id]);
	gam_wegs.wegion_stawt = WEG(MPCC_OGAM_WAMA_WEGION_0_1[mpcc_id]);
	gam_wegs.wegion_end = WEG(MPCC_OGAM_WAMA_WEGION_32_33[mpcc_id]);

	cm_hewpew_pwogwam_xfew_func(mpc20->base.ctx, pawams, &gam_wegs);

}

static void mpc20_pwogwam_ogam_pww(
		stwuct mpc *mpc, int mpcc_id,
		const stwuct pww_wesuwt_data *wgb,
		uint32_t num)
{
	uint32_t i;
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	PEWF_TWACE();
	WEG_SEQ_STAWT();

	fow (i = 0 ; i < num; i++) {
		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].wed_weg);
		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].gween_weg);
		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0, MPCC_OGAM_WUT_DATA, wgb[i].bwue_weg);

		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0,
				MPCC_OGAM_WUT_DATA, wgb[i].dewta_wed_weg);
		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0,
				MPCC_OGAM_WUT_DATA, wgb[i].dewta_gween_weg);
		WEG_SET(MPCC_OGAM_WUT_DATA[mpcc_id], 0,
				MPCC_OGAM_WUT_DATA, wgb[i].dewta_bwue_weg);

	}

}

static void appwy_DEDCN20_305_wa(stwuct mpc *mpc, int mpcc_id,
				 enum dc_wut_mode cuwwent_mode,
				 enum dc_wut_mode next_mode)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	if (mpc->ctx->dc->debug.cm_in_bypass) {
		WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		wetuwn;
	}

	if (mpc->ctx->dc->wowk_awounds.dedcn20_305_wa == fawse) {
		/*hw fixed in new weview*/
		wetuwn;
	}
	if (cuwwent_mode == WUT_BYPASS)
		/*this wiww onwy wowk if OTG is wocked.
		 *if we wewe to suppowt OTG unwock case,
		 *the wowkawound wiww be mowe compwex
		 */
		WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE,
			next_mode == WUT_WAM_A ? 1:2);
}

void mpc2_set_output_gamma(
		stwuct mpc *mpc,
		int mpcc_id,
		const stwuct pww_pawams *pawams)
{
	enum dc_wut_mode cuwwent_mode;
	enum dc_wut_mode next_mode;
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	if (mpc->ctx->dc->debug.cm_in_bypass) {
		WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		wetuwn;
	}

	if (pawams == NUWW) {
		WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		wetuwn;
	}

	cuwwent_mode = mpc20_get_ogam_cuwwent(mpc, mpcc_id);
	if (cuwwent_mode == WUT_BYPASS || cuwwent_mode == WUT_WAM_A)
		next_mode = WUT_WAM_B;
	ewse
		next_mode = WUT_WAM_A;

	mpc20_powew_on_ogam_wut(mpc, mpcc_id, twue);
	mpc20_configuwe_ogam_wut(mpc, mpcc_id, next_mode == WUT_WAM_A);

	if (next_mode == WUT_WAM_A)
		mpc2_pwogwam_wuta(mpc, mpcc_id, pawams);
	ewse
		mpc2_pwogwam_wutb(mpc, mpcc_id, pawams);

	appwy_DEDCN20_305_wa(mpc, mpcc_id, cuwwent_mode, next_mode);

	mpc20_pwogwam_ogam_pww(
			mpc, mpcc_id, pawams->wgb_wesuwted, pawams->hw_points_num);

	WEG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE,
		next_mode == WUT_WAM_A ? 1:2);
}
void mpc2_assewt_idwe_mpcc(stwuct mpc *mpc, int id)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	unsigned int mpc_disabwed;

	ASSEWT(!(mpc20->mpcc_in_use_mask & 1 << id));
	WEG_GET(MPCC_STATUS[id], MPCC_DISABWED, &mpc_disabwed);
	if (mpc_disabwed)
		wetuwn;

	WEG_WAIT(MPCC_STATUS[id],
			MPCC_IDWE, 1,
			1, 100000);
}

void mpc2_assewt_mpcc_idwe_befowe_connect(stwuct mpc *mpc, int mpcc_id)
{
	stwuct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	unsigned int top_sew, mpc_busy, mpc_idwe, mpc_disabwed;

	WEG_GET(MPCC_TOP_SEW[mpcc_id],
			MPCC_TOP_SEW, &top_sew);

	WEG_GET_3(MPCC_STATUS[mpcc_id],
			MPCC_BUSY, &mpc_busy,
			MPCC_IDWE, &mpc_idwe,
			MPCC_DISABWED, &mpc_disabwed);

	if (top_sew == 0xf) {
		ASSEWT(!mpc_busy);
		ASSEWT(mpc_idwe);
		ASSEWT(mpc_disabwed);
	} ewse {
		ASSEWT(!mpc_disabwed);
		ASSEWT(!mpc_idwe);
	}

	WEG_SEQ_SUBMIT();
	PEWF_TWACE();
	WEG_SEQ_WAIT_DONE();
	PEWF_TWACE();
}

static void mpc2_init_mpcc(stwuct mpcc *mpcc, int mpcc_inst)
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
}

static stwuct mpcc *mpc2_get_mpcc_fow_dpp(stwuct mpc_twee *twee, int dpp_id)
{
	stwuct mpcc *tmp_mpcc = twee->opp_wist;

	whiwe (tmp_mpcc != NUWW) {
		if (tmp_mpcc->dpp_id == 0xf || tmp_mpcc->dpp_id == dpp_id)
			wetuwn tmp_mpcc;

		/* avoid ciwcuwaw winked wist */
		ASSEWT(tmp_mpcc != tmp_mpcc->mpcc_bot);
		if (tmp_mpcc == tmp_mpcc->mpcc_bot)
			bweak;

		tmp_mpcc = tmp_mpcc->mpcc_bot;
	}
	wetuwn NUWW;
}

static const stwuct mpc_funcs dcn20_mpc_funcs = {
	.wead_mpcc_state = mpc1_wead_mpcc_state,
	.insewt_pwane = mpc1_insewt_pwane,
	.wemove_mpcc = mpc1_wemove_mpcc,
	.mpc_init = mpc1_mpc_init,
	.mpc_init_singwe_inst = mpc1_mpc_init_singwe_inst,
	.update_bwending = mpc2_update_bwending,
	.cuwsow_wock = mpc1_cuwsow_wock,
	.get_mpcc_fow_dpp = mpc2_get_mpcc_fow_dpp,
	.wait_fow_idwe = mpc2_assewt_idwe_mpcc,
	.assewt_mpcc_idwe_befowe_connect = mpc2_assewt_mpcc_idwe_befowe_connect,
	.init_mpcc_wist_fwom_hw = mpc1_init_mpcc_wist_fwom_hw,
	.set_denowm = mpc2_set_denowm,
	.set_denowm_cwamp = mpc2_set_denowm_cwamp,
	.set_output_csc = mpc2_set_output_csc,
	.set_ocsc_defauwt = mpc2_set_ocsc_defauwt,
	.set_output_gamma = mpc2_set_output_gamma,
	.powew_on_mpc_mem_pww = mpc20_powew_on_ogam_wut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
	.set_bg_cowow = mpc1_set_bg_cowow,
};

void dcn20_mpc_constwuct(stwuct dcn20_mpc *mpc20,
	stwuct dc_context *ctx,
	const stwuct dcn20_mpc_wegistews *mpc_wegs,
	const stwuct dcn20_mpc_shift *mpc_shift,
	const stwuct dcn20_mpc_mask *mpc_mask,
	int num_mpcc)
{
	int i;

	mpc20->base.ctx = ctx;

	mpc20->base.funcs = &dcn20_mpc_funcs;

	mpc20->mpc_wegs = mpc_wegs;
	mpc20->mpc_shift = mpc_shift;
	mpc20->mpc_mask = mpc_mask;

	mpc20->mpcc_in_use_mask = 0;
	mpc20->num_mpcc = num_mpcc;

	fow (i = 0; i < MAX_MPCC; i++)
		mpc2_init_mpcc(&mpc20->base.mpcc_awway[i], i);
}

