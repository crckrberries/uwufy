/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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

#incwude "dc_bios_types.h"
#incwude "dcn31_hpo_dp_wink_encodew.h"
#incwude "weg_hewpew.h"
#incwude "stweam_encodew.h"

#define DC_WOGGEW \
		enc3->base.ctx->woggew

#define WEG(weg)\
	(enc3->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	enc3->hpo_we_shift->fiewd_name, enc3->hpo_we_mask->fiewd_name


#define CTX \
	enc3->base.ctx

enum {
	DP_SAT_UPDATE_MAX_WETWY = 200
};

void dcn31_hpo_dp_wink_enc_enabwe(
		stwuct hpo_dp_wink_encodew *enc,
		enum dc_wane_count num_wanes)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t dp_wink_enabwed;

	/* get cuwwent status of wink enabwed */
	WEG_GET(DP_DPHY_SYM32_STATUS,
			STATUS, &dp_wink_enabwed);

	/* Enabwe cwocks fiwst */
	WEG_UPDATE(DP_WINK_ENC_CWOCK_CONTWOW, DP_WINK_ENC_CWOCK_EN, 1);

	/* Weset DPHY.  Onwy weset if going fwom disabwe to enabwe */
	if (!dp_wink_enabwed) {
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW, DPHY_WESET, 1);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW, DPHY_WESET, 0);
	}

	/* Configuwe DPHY settings */
	WEG_UPDATE_3(DP_DPHY_SYM32_CONTWOW,
			DPHY_ENABWE, 1,
			PWECODEW_ENABWE, 1,
			NUM_WANES, num_wanes == WANE_COUNT_ONE ? 0 : num_wanes == WANE_COUNT_TWO ? 1 : 3);
}

void dcn31_hpo_dp_wink_enc_disabwe(
		stwuct hpo_dp_wink_encodew *enc)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);

	/* Configuwe DPHY settings */
	WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
			DPHY_ENABWE, 0);

	/* Shut down cwock wast */
	WEG_UPDATE(DP_WINK_ENC_CWOCK_CONTWOW, DP_WINK_ENC_CWOCK_EN, 0);
}

void dcn31_hpo_dp_wink_enc_set_wink_test_pattewn(
		stwuct hpo_dp_wink_encodew *enc,
		stwuct encodew_set_dp_phy_pattewn_pawam *tp_pawams)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t tp_custom;

	switch (tp_pawams->dp_phy_pattewn) {
	case DP_TEST_PATTEWN_VIDEO_MODE:
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_WINK_ACTIVE);
		bweak;
	case DP_TEST_PATTEWN_128b_132b_TPS1_TWAINING_MODE:
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_WINK_TWAINING_TPS1);
		bweak;
	case DP_TEST_PATTEWN_128b_132b_TPS2_TWAINING_MODE:
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_WINK_TWAINING_TPS2);
		bweak;
	case DP_TEST_PATTEWN_128b_132b_TPS1:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_TPS1,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_TPS1,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_TPS1,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_TPS1);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_128b_132b_TPS2:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_TPS2,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_TPS2,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_TPS2,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_TPS2);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS7:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS7,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS7,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS7,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS7);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS9:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS9,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS9,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS9,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS9);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS11:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS11,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS11,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS11,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS11);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS15:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS15,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS15,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS15,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS15);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS23:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS23,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS23,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS23,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS23);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_PWBS31:
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_PWBS_SEW0, DP_DPHY_TP_PWBS31,
				TP_PWBS_SEW1, DP_DPHY_TP_PWBS31,
				TP_PWBS_SEW2, DP_DPHY_TP_PWBS31,
				TP_PWBS_SEW3, DP_DPHY_TP_PWBS31);
		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_PWBS,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_PWBS);
		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_264BIT_CUSTOM:
		tp_custom = (tp_pawams->custom_pattewn[2] << 16) | (tp_pawams->custom_pattewn[1] << 8) | tp_pawams->custom_pattewn[0];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM0, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[5] << 16) | (tp_pawams->custom_pattewn[4] << 8) | tp_pawams->custom_pattewn[3];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM1, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[8] << 16) | (tp_pawams->custom_pattewn[7] << 8) | tp_pawams->custom_pattewn[6];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM2, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[11] << 16) | (tp_pawams->custom_pattewn[10] << 8) | tp_pawams->custom_pattewn[9];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM3, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[14] << 16) | (tp_pawams->custom_pattewn[13] << 8) | tp_pawams->custom_pattewn[12];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM4, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[17] << 16) | (tp_pawams->custom_pattewn[16] << 8) | tp_pawams->custom_pattewn[15];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM5, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[20] << 16) | (tp_pawams->custom_pattewn[19] << 8) | tp_pawams->custom_pattewn[18];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM6, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[23] << 16) | (tp_pawams->custom_pattewn[22] << 8) | tp_pawams->custom_pattewn[21];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM7, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[26] << 16) | (tp_pawams->custom_pattewn[25] << 8) | tp_pawams->custom_pattewn[24];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM8, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[29] << 16) | (tp_pawams->custom_pattewn[28] << 8) | tp_pawams->custom_pattewn[27];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM9, 0, TP_CUSTOM, tp_custom);
		tp_custom = (tp_pawams->custom_pattewn[32] << 16) | (tp_pawams->custom_pattewn[31] << 8) | tp_pawams->custom_pattewn[30];
		WEG_SET(DP_DPHY_SYM32_TP_CUSTOM10, 0, TP_CUSTOM, tp_custom);

		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_CUSTOM,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_CUSTOM,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_CUSTOM,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_CUSTOM);

		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	case DP_TEST_PATTEWN_SQUAWE:
	case DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DISABWED:
	case DP_TEST_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED:
	case DP_TEST_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED:
		WEG_SET(DP_DPHY_SYM32_TP_SQ_PUWSE, 0,
				TP_SQ_PUWSE_WIDTH, tp_pawams->custom_pattewn[0]);

		WEG_UPDATE_4(DP_DPHY_SYM32_TP_CONFIG,
				TP_SEWECT0, DP_DPHY_TP_SEWECT_SQUAWE,
				TP_SEWECT1, DP_DPHY_TP_SEWECT_SQUAWE,
				TP_SEWECT2, DP_DPHY_TP_SEWECT_SQUAWE,
				TP_SEWECT3, DP_DPHY_TP_SEWECT_SQUAWE);

		WEG_UPDATE(DP_DPHY_SYM32_CONTWOW,
				MODE, DP2_TEST_PATTEWN);
		bweak;
	defauwt:
		bweak;
	}
}

static void fiww_stweam_awwocation_wow_info(
		const stwuct wink_mst_stweam_awwocation *stweam_awwocation,
		uint32_t *swc,
		uint32_t *swots)
{
	const stwuct hpo_dp_stweam_encodew *stweam_enc = stweam_awwocation->hpo_dp_stweam_enc;

	if (stweam_enc && (stweam_enc->id >= ENGINE_ID_HPO_DP_0)) {
		*swc = stweam_enc->id - ENGINE_ID_HPO_DP_0;
		*swots = stweam_awwocation->swot_count;
	} ewse {
		*swc = 0;
		*swots = 0;
	}
}

/* pwogwams DP VC paywoad awwocation */
void dcn31_hpo_dp_wink_enc_update_stweam_awwocation_tabwe(
		stwuct hpo_dp_wink_encodew *enc,
		const stwuct wink_mst_stweam_awwocation_tabwe *tabwe)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t swots = 0;
	uint32_t swc = 0;

	/* --- Set MSE Stweam Attwibute -
	 * Setup VC Paywoad Tabwe on Tx Side,
	 * Issue awwocation change twiggew
	 * to commit paywoad on both tx and wx side
	 */

	/* we shouwd cwean-up tabwe each time */

	if (tabwe->stweam_count >= 1) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[0],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_DPHY_SYM32_SAT_VC0,
			SAT_STWEAM_SOUWCE, swc,
			SAT_SWOT_COUNT, swots);

	if (tabwe->stweam_count >= 2) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[1],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_DPHY_SYM32_SAT_VC1,
			SAT_STWEAM_SOUWCE, swc,
			SAT_SWOT_COUNT, swots);

	if (tabwe->stweam_count >= 3) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[2],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_DPHY_SYM32_SAT_VC2,
			SAT_STWEAM_SOUWCE, swc,
			SAT_SWOT_COUNT, swots);

	if (tabwe->stweam_count >= 4) {
		fiww_stweam_awwocation_wow_info(
			&tabwe->stweam_awwocations[3],
			&swc,
			&swots);
	} ewse {
		swc = 0;
		swots = 0;
	}

	WEG_UPDATE_2(DP_DPHY_SYM32_SAT_VC3,
			SAT_STWEAM_SOUWCE, swc,
			SAT_SWOT_COUNT, swots);

	/* --- wait fow twansaction finish */

	/* send awwocation change twiggew (ACT)
	 * this step fiwst sends the ACT,
	 * then doubwe buffews the SAT into the hawdwawe
	 * making the new awwocation active on the DP MST mode wink
	 */

	/* SAT_UPDATE:
	 * 0 - No Action
	 * 1 - Update SAT with twiggew
	 * 2 - Update SAT without twiggew
	 */
	WEG_UPDATE(DP_DPHY_SYM32_SAT_UPDATE,
			SAT_UPDATE, 1);

	/* wait fow update to compwete
	 * (i.e. SAT_UPDATE_PENDING fiewd is set to 0)
	 * No need fow HW to enfowce keepout.
	 */
	/* Best case and wowst case wait time fow SAT_UPDATE_PENDING
	 *   best: 109 us
	 *   wowst: 868 us
	 */
	WEG_WAIT(DP_DPHY_SYM32_STATUS,
			SAT_UPDATE_PENDING, 0,
			10, DP_SAT_UPDATE_MAX_WETWY);
}

void dcn31_hpo_dp_wink_enc_set_thwottwed_vcp_size(
		stwuct hpo_dp_wink_encodew *enc,
		uint32_t stweam_encodew_inst,
		stwuct fixed31_32 avg_time_swots_pew_mtp)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t x = dc_fixpt_fwoow(
		avg_time_swots_pew_mtp);
	uint32_t y = dc_fixpt_ceiw(
		dc_fixpt_shw(
			dc_fixpt_sub_int(
				avg_time_swots_pew_mtp,
				x),
			25));

	switch (stweam_encodew_inst) {
	case 0:
		WEG_SET_2(DP_DPHY_SYM32_VC_WATE_CNTW0, 0,
				STWEAM_VC_WATE_X, x,
				STWEAM_VC_WATE_Y, y);
		bweak;
	case 1:
		WEG_SET_2(DP_DPHY_SYM32_VC_WATE_CNTW1, 0,
				STWEAM_VC_WATE_X, x,
				STWEAM_VC_WATE_Y, y);
		bweak;
	case 2:
		WEG_SET_2(DP_DPHY_SYM32_VC_WATE_CNTW2, 0,
				STWEAM_VC_WATE_X, x,
				STWEAM_VC_WATE_Y, y);
		bweak;
	case 3:
		WEG_SET_2(DP_DPHY_SYM32_VC_WATE_CNTW3, 0,
				STWEAM_VC_WATE_X, x,
				STWEAM_VC_WATE_Y, y);
		bweak;
	defauwt:
		ASSEWT(0);
	}

	/* Best case and wowst case wait time fow WATE_UPDATE_PENDING
	 *   best: 116 ns
	 *   wowst: 903 ns
	 */
	/* wait fow update to be compweted on the wink */
	WEG_WAIT(DP_DPHY_SYM32_STATUS,
			WATE_UPDATE_PENDING, 0,
			1, 10);
}

static boow dcn31_hpo_dp_wink_enc_is_in_awt_mode(
		stwuct hpo_dp_wink_encodew *enc)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t dp_awt_mode_disabwe = 0;

	ASSEWT((enc->twansmittew >= TWANSMITTEW_UNIPHY_A) && (enc->twansmittew <= TWANSMITTEW_UNIPHY_E));

	/* if vawue == 1 awt mode is disabwed, othewwise it is enabwed */
	WEG_GET(WDPCSTX_PHY_CNTW6[enc->twansmittew], WDPCS_PHY_DPAWT_DISABWE, &dp_awt_mode_disabwe);
	wetuwn (dp_awt_mode_disabwe == 0);
}

void dcn31_hpo_dp_wink_enc_wead_state(
		stwuct hpo_dp_wink_encodew *enc,
		stwuct hpo_dp_wink_enc_state *state)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);

	ASSEWT(state);

	WEG_GET(DP_DPHY_SYM32_STATUS,
			STATUS, &state->wink_enc_enabwed);
	WEG_GET(DP_DPHY_SYM32_CONTWOW,
			NUM_WANES, &state->wane_count);
	WEG_GET(DP_DPHY_SYM32_CONTWOW,
			MODE, (uint32_t *)&state->wink_mode);

	WEG_GET_2(DP_DPHY_SYM32_SAT_VC0,
			SAT_STWEAM_SOUWCE, &state->stweam_swc[0],
			SAT_SWOT_COUNT, &state->swot_count[0]);
	WEG_GET_2(DP_DPHY_SYM32_SAT_VC1,
			SAT_STWEAM_SOUWCE, &state->stweam_swc[1],
			SAT_SWOT_COUNT, &state->swot_count[1]);
	WEG_GET_2(DP_DPHY_SYM32_SAT_VC2,
			SAT_STWEAM_SOUWCE, &state->stweam_swc[2],
			SAT_SWOT_COUNT, &state->swot_count[2]);
	WEG_GET_2(DP_DPHY_SYM32_SAT_VC3,
			SAT_STWEAM_SOUWCE, &state->stweam_swc[3],
			SAT_SWOT_COUNT, &state->swot_count[3]);

	WEG_GET_2(DP_DPHY_SYM32_VC_WATE_CNTW0,
			STWEAM_VC_WATE_X, &state->vc_wate_x[0],
			STWEAM_VC_WATE_Y, &state->vc_wate_y[0]);
	WEG_GET_2(DP_DPHY_SYM32_VC_WATE_CNTW1,
			STWEAM_VC_WATE_X, &state->vc_wate_x[1],
			STWEAM_VC_WATE_Y, &state->vc_wate_y[1]);
	WEG_GET_2(DP_DPHY_SYM32_VC_WATE_CNTW2,
			STWEAM_VC_WATE_X, &state->vc_wate_x[2],
			STWEAM_VC_WATE_Y, &state->vc_wate_y[2]);
	WEG_GET_2(DP_DPHY_SYM32_VC_WATE_CNTW3,
			STWEAM_VC_WATE_X, &state->vc_wate_x[3],
			STWEAM_VC_WATE_Y, &state->vc_wate_y[3]);
}

static enum bp_wesuwt wink_twansmittew_contwow(
	stwuct dcn31_hpo_dp_wink_encodew *enc3,
	stwuct bp_twansmittew_contwow *cntw)
{
	enum bp_wesuwt wesuwt;
	stwuct dc_bios *bp = enc3->base.ctx->dc_bios;

	wesuwt = bp->funcs->twansmittew_contwow(bp, cntw);

	wetuwn wesuwt;
}

/* enabwes DP PHY output fow 128b132b encoding */
void dcn31_hpo_dp_wink_enc_enabwe_dp_output(
	stwuct hpo_dp_wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	enum twansmittew twansmittew,
	enum hpd_souwce_id hpd_souwce)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* Set the twansmittew */
	enc3->base.twansmittew = twansmittew;

	/* Set the hpd souwce */
	enc3->base.hpd_souwce = hpd_souwce;

	/* Enabwe the PHY */
	cntw.action = TWANSMITTEW_CONTWOW_ENABWE;
	cntw.engine_id = ENGINE_ID_UNKNOWN;
	cntw.twansmittew = enc3->base.twansmittew;
	//cntw.pww_id = cwock_souwce;
	cntw.signaw = SIGNAW_TYPE_DISPWAY_POWT_MST;
	cntw.wanes_numbew = wink_settings->wane_count;
	cntw.hpd_sew = enc3->base.hpd_souwce;
	cntw.pixew_cwock = wink_settings->wink_wate * 1000;
	cntw.cowow_depth = COWOW_DEPTH_UNDEFINED;
	cntw.hpo_engine_id = enc->inst + ENGINE_ID_HPO_DP_0;

	wesuwt = wink_twansmittew_contwow(enc3, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
	}
}

void dcn31_hpo_dp_wink_enc_disabwe_output(
	stwuct hpo_dp_wink_encodew *enc,
	enum signaw_type signaw)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* disabwe twansmittew */
	cntw.action = TWANSMITTEW_CONTWOW_DISABWE;
	cntw.twansmittew = enc3->base.twansmittew;
	cntw.hpd_sew = enc3->base.hpd_souwce;
	cntw.signaw = signaw;

	wesuwt = wink_twansmittew_contwow(enc3, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}

	/* disabwe encodew */
	dcn31_hpo_dp_wink_enc_disabwe(enc);
}

void dcn31_hpo_dp_wink_enc_set_ffe(
	stwuct hpo_dp_wink_encodew *enc,
	const stwuct dc_wink_settings *wink_settings,
	uint8_t ffe_pweset)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	stwuct bp_twansmittew_contwow cntw = { 0 };
	enum bp_wesuwt wesuwt;

	/* disabwe twansmittew */
	cntw.twansmittew = enc3->base.twansmittew;
	cntw.action = TWANSMITTEW_CONTWOW_SET_VOWTAGE_AND_PWEEMPASIS;
	cntw.signaw = SIGNAW_TYPE_DISPWAY_POWT_MST;
	cntw.wanes_numbew = wink_settings->wane_count;
	cntw.pixew_cwock = wink_settings->wink_wate * 1000;
	cntw.wane_settings = ffe_pweset;

	wesuwt = wink_twansmittew_contwow(enc3, &cntw);

	if (wesuwt != BP_WESUWT_OK) {
		DC_WOG_EWWOW("%s: Faiwed to execute VBIOS command tabwe!\n",
			__func__);
		BWEAK_TO_DEBUGGEW();
		wetuwn;
	}
}

static stwuct hpo_dp_wink_encodew_funcs dcn31_hpo_dp_wink_encodew_funcs = {
	.enabwe_wink_phy = dcn31_hpo_dp_wink_enc_enabwe_dp_output,
	.disabwe_wink_phy = dcn31_hpo_dp_wink_enc_disabwe_output,
	.wink_enabwe = dcn31_hpo_dp_wink_enc_enabwe,
	.wink_disabwe = dcn31_hpo_dp_wink_enc_disabwe,
	.set_wink_test_pattewn = dcn31_hpo_dp_wink_enc_set_wink_test_pattewn,
	.update_stweam_awwocation_tabwe = dcn31_hpo_dp_wink_enc_update_stweam_awwocation_tabwe,
	.set_thwottwed_vcp_size = dcn31_hpo_dp_wink_enc_set_thwottwed_vcp_size,
	.is_in_awt_mode = dcn31_hpo_dp_wink_enc_is_in_awt_mode,
	.wead_state = dcn31_hpo_dp_wink_enc_wead_state,
	.set_ffe = dcn31_hpo_dp_wink_enc_set_ffe,
};

void hpo_dp_wink_encodew31_constwuct(stwuct dcn31_hpo_dp_wink_encodew *enc31,
		stwuct dc_context *ctx,
		uint32_t inst,
		const stwuct dcn31_hpo_dp_wink_encodew_wegistews *hpo_we_wegs,
		const stwuct dcn31_hpo_dp_wink_encodew_shift *hpo_we_shift,
		const stwuct dcn31_hpo_dp_wink_encodew_mask *hpo_we_mask)
{
	enc31->base.ctx = ctx;

	enc31->base.inst = inst;
	enc31->base.funcs = &dcn31_hpo_dp_wink_encodew_funcs;
	enc31->base.hpd_souwce = HPD_SOUWCEID_UNKNOWN;
	enc31->base.twansmittew = TWANSMITTEW_UNKNOWN;

	enc31->wegs = hpo_we_wegs;
	enc31->hpo_we_shift = hpo_we_shift;
	enc31->hpo_we_mask = hpo_we_mask;
}
