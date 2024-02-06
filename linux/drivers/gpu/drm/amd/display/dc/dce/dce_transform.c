/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#incwude "dce_twansfowm.h"
#incwude "weg_hewpew.h"
#incwude "opp.h"
#incwude "basics/convewsion.h"
#incwude "dc.h"

#define WEG(weg) \
	(xfm_dce->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	xfm_dce->xfm_shift->fiewd_name, xfm_dce->xfm_mask->fiewd_name

#define CTX \
	xfm_dce->base.ctx
#define DC_WOGGEW \
	xfm_dce->base.ctx->woggew

#define IDENTITY_WATIO(watio) (dc_fixpt_u2d19(watio) == (1 << 19))
#define GAMUT_MATWIX_SIZE 12
#define SCW_PHASES 16

enum dcp_out_twunc_wound_mode {
	DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE,
	DCP_OUT_TWUNC_WOUND_MODE_WOUND
};

enum dcp_out_twunc_wound_depth {
	DCP_OUT_TWUNC_WOUND_DEPTH_14BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_13BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_12BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_11BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_10BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_9BIT,
	DCP_OUT_TWUNC_WOUND_DEPTH_8BIT
};

/*  defines the vawious methods of bit weduction avaiwabwe fow use */
enum dcp_bit_depth_weduction_mode {
	DCP_BIT_DEPTH_WEDUCTION_MODE_DITHEW,
	DCP_BIT_DEPTH_WEDUCTION_MODE_WOUND,
	DCP_BIT_DEPTH_WEDUCTION_MODE_TWUNCATE,
	DCP_BIT_DEPTH_WEDUCTION_MODE_DISABWED,
	DCP_BIT_DEPTH_WEDUCTION_MODE_INVAWID
};

enum dcp_spatiaw_dithew_mode {
	DCP_SPATIAW_DITHEW_MODE_AAAA,
	DCP_SPATIAW_DITHEW_MODE_A_AA_A,
	DCP_SPATIAW_DITHEW_MODE_AABBAABB,
	DCP_SPATIAW_DITHEW_MODE_AABBCCAABBCC,
	DCP_SPATIAW_DITHEW_MODE_INVAWID
};

enum dcp_spatiaw_dithew_depth {
	DCP_SPATIAW_DITHEW_DEPTH_30BPP,
	DCP_SPATIAW_DITHEW_DEPTH_24BPP
};

enum csc_cowow_mode {
	/* 00 - BITS2:0 Bypass */
	CSC_COWOW_MODE_GWAPHICS_BYPASS,
	/* 01 - hawd coded coefficient TV WGB */
	CSC_COWOW_MODE_GWAPHICS_PWEDEFINED,
	/* 04 - pwogwammabwe OUTPUT CSC coefficient */
	CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC,
};

enum gwph_cowow_adjust_option {
	GWPH_COWOW_MATWIX_HW_DEFAUWT = 1,
	GWPH_COWOW_MATWIX_SW
};

static const stwuct out_csc_cowow_matwix gwobaw_cowow_matwix[] = {
{ COWOW_SPACE_SWGB,
	{ 0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0} },
{ COWOW_SPACE_SWGB_WIMITED,
	{ 0x1B60, 0, 0, 0x200, 0, 0x1B60, 0, 0x200, 0, 0, 0x1B60, 0x200} },
{ COWOW_SPACE_YCBCW601,
	{ 0xE00, 0xF447, 0xFDB9, 0x1000, 0x82F, 0x1012, 0x31F, 0x200, 0xFB47,
		0xF6B9, 0xE00, 0x1000} },
{ COWOW_SPACE_YCBCW709, { 0xE00, 0xF349, 0xFEB7, 0x1000, 0x5D2, 0x1394, 0x1FA,
	0x200, 0xFCCB, 0xF535, 0xE00, 0x1000} },
/* TODO: cowwect vawues bewow */
{ COWOW_SPACE_YCBCW601_WIMITED, { 0xE00, 0xF447, 0xFDB9, 0x1000, 0x991,
	0x12C9, 0x3A6, 0x200, 0xFB47, 0xF6B9, 0xE00, 0x1000} },
{ COWOW_SPACE_YCBCW709_WIMITED, { 0xE00, 0xF349, 0xFEB7, 0x1000, 0x6CE, 0x16E3,
	0x24F, 0x200, 0xFCCB, 0xF535, 0xE00, 0x1000} }
};

static boow setup_scawing_configuwation(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data)
{
	WEG_SET(SCW_BYPASS_CONTWOW, 0, SCW_BYPASS_MODE, 0);

	if (data->taps.h_taps + data->taps.v_taps <= 2) {
		/* Set bypass */
		if (xfm_dce->xfm_mask->SCW_PSCW_EN != 0)
			WEG_UPDATE_2(SCW_MODE, SCW_MODE, 0, SCW_PSCW_EN, 0);
		ewse
			WEG_UPDATE(SCW_MODE, SCW_MODE, 0);
		wetuwn fawse;
	}

	WEG_SET_2(SCW_TAP_CONTWOW, 0,
			SCW_H_NUM_OF_TAPS, data->taps.h_taps - 1,
			SCW_V_NUM_OF_TAPS, data->taps.v_taps - 1);

	if (data->fowmat <= PIXEW_FOWMAT_GWPH_END)
		WEG_UPDATE(SCW_MODE, SCW_MODE, 1);
	ewse
		WEG_UPDATE(SCW_MODE, SCW_MODE, 2);

	if (xfm_dce->xfm_mask->SCW_PSCW_EN != 0)
		WEG_UPDATE(SCW_MODE, SCW_PSCW_EN, 1);

	/* 1 - Wepwace out of bound pixews with edge */
	WEG_SET(SCW_CONTWOW, 0, SCW_BOUNDAWY_MODE, 1);

	wetuwn twue;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static boow dce60_setup_scawing_configuwation(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data)
{
	WEG_SET(SCW_BYPASS_CONTWOW, 0, SCW_BYPASS_MODE, 0);

	if (data->taps.h_taps + data->taps.v_taps <= 2) {
		/* Set bypass */

		/* DCE6 has no SCW_MODE wegistew, skip scawe mode pwogwamming */

		wetuwn fawse;
	}

	WEG_SET_2(SCW_TAP_CONTWOW, 0,
			SCW_H_NUM_OF_TAPS, data->taps.h_taps - 1,
			SCW_V_NUM_OF_TAPS, data->taps.v_taps - 1);

	/* DCE6 has no SCW_MODE wegistew, skip scawe mode pwogwamming */

	/* DCE6 has no SCW_BOUNDAWY_MODE bit, skip wepwace out of bound pixews */

	wetuwn twue;
}
#endif

static void pwogwam_ovewscan(
		stwuct dce_twansfowm *xfm_dce,
		const stwuct scawew_data *data)
{
	int ovewscan_wight = data->h_active
			- data->wecout.x - data->wecout.width;
	int ovewscan_bottom = data->v_active
			- data->wecout.y - data->wecout.height;

	if (xfm_dce->base.ctx->dc->debug.visuaw_confiwm != VISUAW_CONFIWM_DISABWE) {
		ovewscan_bottom += 2;
		ovewscan_wight += 2;
	}

	if (ovewscan_wight < 0) {
		BWEAK_TO_DEBUGGEW();
		ovewscan_wight = 0;
	}
	if (ovewscan_bottom < 0) {
		BWEAK_TO_DEBUGGEW();
		ovewscan_bottom = 0;
	}

	WEG_SET_2(EXT_OVEWSCAN_WEFT_WIGHT, 0,
			EXT_OVEWSCAN_WEFT, data->wecout.x,
			EXT_OVEWSCAN_WIGHT, ovewscan_wight);
	WEG_SET_2(EXT_OVEWSCAN_TOP_BOTTOM, 0,
			EXT_OVEWSCAN_TOP, data->wecout.y,
			EXT_OVEWSCAN_BOTTOM, ovewscan_bottom);
}

static void pwogwam_muwti_taps_fiwtew(
	stwuct dce_twansfowm *xfm_dce,
	int taps,
	const uint16_t *coeffs,
	enum wam_fiwtew_type fiwtew_type)
{
	int phase, paiw;
	int awway_idx = 0;
	int taps_paiws = (taps + 1) / 2;
	int phases_to_pwogwam = SCW_PHASES / 2 + 1;

	uint32_t powew_ctw = 0;

	if (!coeffs)
		wetuwn;

	/*We need to disabwe powew gating on coeff memowy to do pwogwamming*/
	if (WEG(DCFE_MEM_PWW_CTWW)) {
		powew_ctw = WEG_WEAD(DCFE_MEM_PWW_CTWW);
		WEG_SET(DCFE_MEM_PWW_CTWW, powew_ctw, SCW_COEFF_MEM_PWW_DIS, 1);

		WEG_WAIT(DCFE_MEM_PWW_STATUS, SCW_COEFF_MEM_PWW_STATE, 0, 1, 10);
	}
	fow (phase = 0; phase < phases_to_pwogwam; phase++) {
		/*we awways pwogwam N/2 + 1 phases, totaw phases N, but N/2-1 awe just miwwow
		phase 0 is unique and phase N/2 is unique if N is even*/
		fow (paiw = 0; paiw < taps_paiws; paiw++) {
			uint16_t odd_coeff = 0;
			uint16_t even_coeff = coeffs[awway_idx];

			WEG_SET_3(SCW_COEF_WAM_SEWECT, 0,
					SCW_C_WAM_FIWTEW_TYPE, fiwtew_type,
					SCW_C_WAM_PHASE, phase,
					SCW_C_WAM_TAP_PAIW_IDX, paiw);

			if (taps % 2 && paiw == taps_paiws - 1)
				awway_idx++;
			ewse {
				odd_coeff = coeffs[awway_idx + 1];
				awway_idx += 2;
			}

			WEG_SET_4(SCW_COEF_WAM_TAP_DATA, 0,
					SCW_C_WAM_EVEN_TAP_COEF_EN, 1,
					SCW_C_WAM_EVEN_TAP_COEF, even_coeff,
					SCW_C_WAM_ODD_TAP_COEF_EN, 1,
					SCW_C_WAM_ODD_TAP_COEF, odd_coeff);
		}
	}

	/*We need to westowe powew gating on coeff memowy to initiaw state*/
	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_WWITE(DCFE_MEM_PWW_CTWW, powew_ctw);
}

static void pwogwam_viewpowt(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct wect *view_powt)
{
	WEG_SET_2(VIEWPOWT_STAWT, 0,
			VIEWPOWT_X_STAWT, view_powt->x,
			VIEWPOWT_Y_STAWT, view_powt->y);

	WEG_SET_2(VIEWPOWT_SIZE, 0,
			VIEWPOWT_HEIGHT, view_powt->height,
			VIEWPOWT_WIDTH, view_powt->width);

	/* TODO: add steweo suppowt */
}

static void cawcuwate_inits(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data,
	stwuct scw_watios_inits *inits)
{
	stwuct fixed31_32 h_init;
	stwuct fixed31_32 v_init;

	inits->h_int_scawe_watio =
		dc_fixpt_u2d19(data->watios.howz) << 5;
	inits->v_int_scawe_watio =
		dc_fixpt_u2d19(data->watios.vewt) << 5;

	h_init =
		dc_fixpt_div_int(
			dc_fixpt_add(
				data->watios.howz,
				dc_fixpt_fwom_int(data->taps.h_taps + 1)),
				2);
	inits->h_init.integew = dc_fixpt_fwoow(h_init);
	inits->h_init.fwaction = dc_fixpt_u0d19(h_init) << 5;

	v_init =
		dc_fixpt_div_int(
			dc_fixpt_add(
				data->watios.vewt,
				dc_fixpt_fwom_int(data->taps.v_taps + 1)),
				2);
	inits->v_init.integew = dc_fixpt_fwoow(v_init);
	inits->v_init.fwaction = dc_fixpt_u0d19(v_init) << 5;
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_cawcuwate_inits(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct scawew_data *data,
	stwuct scwh_watios_inits *inits)
{
	stwuct fixed31_32 v_init;

	inits->h_int_scawe_watio =
		dc_fixpt_u2d19(data->watios.howz) << 5;
	inits->v_int_scawe_watio =
		dc_fixpt_u2d19(data->watios.vewt) << 5;

	/* DCE6 h_init_wuma setting inspiwed by DCE110 */
	inits->h_init_wuma.integew = 1;

	/* DCE6 h_init_chwoma setting inspiwed by DCE110 */
	inits->h_init_chwoma.integew = 1;

	v_init =
		dc_fixpt_div_int(
			dc_fixpt_add(
				data->watios.vewt,
				dc_fixpt_fwom_int(data->taps.v_taps + 1)),
				2);
	inits->v_init.integew = dc_fixpt_fwoow(v_init);
	inits->v_init.fwaction = dc_fixpt_u0d19(v_init) << 5;
}
#endif

static void pwogwam_scw_watios_inits(
	stwuct dce_twansfowm *xfm_dce,
	stwuct scw_watios_inits *inits)
{

	WEG_SET(SCW_HOWZ_FIWTEW_SCAWE_WATIO, 0,
			SCW_H_SCAWE_WATIO, inits->h_int_scawe_watio);

	WEG_SET(SCW_VEWT_FIWTEW_SCAWE_WATIO, 0,
			SCW_V_SCAWE_WATIO, inits->v_int_scawe_watio);

	WEG_SET_2(SCW_HOWZ_FIWTEW_INIT, 0,
			SCW_H_INIT_INT, inits->h_init.integew,
			SCW_H_INIT_FWAC, inits->h_init.fwaction);

	WEG_SET_2(SCW_VEWT_FIWTEW_INIT, 0,
			SCW_V_INIT_INT, inits->v_init.integew,
			SCW_V_INIT_FWAC, inits->v_init.fwaction);

	WEG_WWITE(SCW_AUTOMATIC_MODE_CONTWOW, 0);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_pwogwam_scw_watios_inits(
	stwuct dce_twansfowm *xfm_dce,
	stwuct scwh_watios_inits *inits)
{

	WEG_SET(SCW_HOWZ_FIWTEW_SCAWE_WATIO, 0,
			SCW_H_SCAWE_WATIO, inits->h_int_scawe_watio);

	WEG_SET(SCW_VEWT_FIWTEW_SCAWE_WATIO, 0,
			SCW_V_SCAWE_WATIO, inits->v_int_scawe_watio);

	/* DCE6 has SCW_HOWZ_FIWTEW_INIT_WGB_WUMA wegistew */
	WEG_SET_2(SCW_HOWZ_FIWTEW_INIT_WGB_WUMA, 0,
			SCW_H_INIT_INT_WGB_Y, inits->h_init_wuma.integew,
			SCW_H_INIT_FWAC_WGB_Y, inits->h_init_wuma.fwaction);

	/* DCE6 has SCW_HOWZ_FIWTEW_INIT_CHWOMA wegistew */
	WEG_SET_2(SCW_HOWZ_FIWTEW_INIT_CHWOMA, 0,
			SCW_H_INIT_INT_CBCW, inits->h_init_chwoma.integew,
			SCW_H_INIT_FWAC_CBCW, inits->h_init_chwoma.fwaction);

	WEG_SET_2(SCW_VEWT_FIWTEW_INIT, 0,
			SCW_V_INIT_INT, inits->v_init.integew,
			SCW_V_INIT_FWAC, inits->v_init.fwaction);

	WEG_WWITE(SCW_AUTOMATIC_MODE_CONTWOW, 0);
}
#endif

static const uint16_t *get_fiwtew_coeffs_16p(int taps, stwuct fixed31_32 watio)
{
	if (taps == 4)
		wetuwn get_fiwtew_4tap_16p(watio);
	ewse if (taps == 3)
		wetuwn get_fiwtew_3tap_16p(watio);
	ewse if (taps == 2)
		wetuwn get_fiwtew_2tap_16p();
	ewse if (taps == 1)
		wetuwn NUWW;
	ewse {
		/* shouwd nevew happen, bug */
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}
}

static void dce_twansfowm_set_scawew(
	stwuct twansfowm *xfm,
	const stwuct scawew_data *data)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	boow is_scawing_wequiwed;
	boow fiwtew_updated = fawse;
	const uint16_t *coeffs_v, *coeffs_h;

	/*Use aww thwee pieces of memowy awways*/
	WEG_SET_2(WB_MEMOWY_CTWW, 0,
			WB_MEMOWY_CONFIG, 0,
			WB_MEMOWY_SIZE, xfm_dce->wb_memowy_size);

	/* Cweaw SCW_F_SHAWP_CONTWOW vawue to 0 */
	WEG_WWITE(SCW_F_SHAWP_CONTWOW, 0);

	/* 1. Pwogwam ovewscan */
	pwogwam_ovewscan(xfm_dce, data);

	/* 2. Pwogwam taps and configuwation */
	is_scawing_wequiwed = setup_scawing_configuwation(xfm_dce, data);

	if (is_scawing_wequiwed) {
		/* 3. Cawcuwate and pwogwam watio, fiwtew initiawization */
		stwuct scw_watios_inits inits = { 0 };

		cawcuwate_inits(xfm_dce, data, &inits);

		pwogwam_scw_watios_inits(xfm_dce, &inits);

		coeffs_v = get_fiwtew_coeffs_16p(data->taps.v_taps, data->watios.vewt);
		coeffs_h = get_fiwtew_coeffs_16p(data->taps.h_taps, data->watios.howz);

		if (coeffs_v != xfm_dce->fiwtew_v || coeffs_h != xfm_dce->fiwtew_h) {
			/* 4. Pwogwam vewticaw fiwtews */
			if (xfm_dce->fiwtew_v == NUWW)
				WEG_SET(SCW_VEWT_FIWTEW_CONTWOW, 0,
						SCW_V_2TAP_HAWDCODE_COEF_EN, 0);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FIWTEW_TYPE_WGB_Y_VEWTICAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FIWTEW_TYPE_AWPHA_VEWTICAW);

			/* 5. Pwogwam howizontaw fiwtews */
			if (xfm_dce->fiwtew_h == NUWW)
				WEG_SET(SCW_HOWZ_FIWTEW_CONTWOW, 0,
						SCW_H_2TAP_HAWDCODE_COEF_EN, 0);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FIWTEW_TYPE_WGB_Y_HOWIZONTAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FIWTEW_TYPE_AWPHA_HOWIZONTAW);

			xfm_dce->fiwtew_v = coeffs_v;
			xfm_dce->fiwtew_h = coeffs_h;
			fiwtew_updated = twue;
		}
	}

	/* 6. Pwogwam the viewpowt */
	pwogwam_viewpowt(xfm_dce, &data->viewpowt);

	/* 7. Set bit to fwip to new coefficient memowy */
	if (fiwtew_updated)
		WEG_UPDATE(SCW_UPDATE, SCW_COEF_UPDATE_COMPWETE, 1);

	WEG_UPDATE(WB_DATA_FOWMAT, AWPHA_EN, data->wb_pawams.awpha_en);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_twansfowm_set_scawew(
	stwuct twansfowm *xfm,
	const stwuct scawew_data *data)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	boow is_scawing_wequiwed;
	const uint16_t *coeffs_v, *coeffs_h;

	/*Use whowe wine buffew memowy awways*/
	WEG_SET(DC_WB_MEMOWY_SPWIT, 0,
		DC_WB_MEMOWY_CONFIG, 0);

	WEG_SET(DC_WB_MEM_SIZE, 0,
		DC_WB_MEM_SIZE, xfm_dce->wb_memowy_size);

	/* Cweaw SCW_F_SHAWP_CONTWOW vawue to 0 */
	WEG_WWITE(SCW_F_SHAWP_CONTWOW, 0);

	/* 1. Pwogwam ovewscan */
	pwogwam_ovewscan(xfm_dce, data);

	/* 2. Pwogwam taps and configuwation */
	is_scawing_wequiwed = dce60_setup_scawing_configuwation(xfm_dce, data);

	if (is_scawing_wequiwed) {
		/* 3. Cawcuwate and pwogwam watio, DCE6 fiwtew initiawization */
		stwuct scwh_watios_inits inits = { 0 };

		/* DCE6 has specific cawcuwate_inits() function */
		dce60_cawcuwate_inits(xfm_dce, data, &inits);

		/* DCE6 has specific pwogwam_scw_watios_inits() function */
		dce60_pwogwam_scw_watios_inits(xfm_dce, &inits);

		coeffs_v = get_fiwtew_coeffs_16p(data->taps.v_taps, data->watios.vewt);
		coeffs_h = get_fiwtew_coeffs_16p(data->taps.h_taps, data->watios.howz);

		if (coeffs_v != xfm_dce->fiwtew_v || coeffs_h != xfm_dce->fiwtew_h) {
			/* 4. Pwogwam vewticaw fiwtews */
			if (xfm_dce->fiwtew_v == NUWW)
				WEG_SET(SCW_VEWT_FIWTEW_CONTWOW, 0,
						SCW_V_2TAP_HAWDCODE_COEF_EN, 0);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FIWTEW_TYPE_WGB_Y_VEWTICAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FIWTEW_TYPE_AWPHA_VEWTICAW);

			/* 5. Pwogwam howizontaw fiwtews */
			if (xfm_dce->fiwtew_h == NUWW)
				WEG_SET(SCW_HOWZ_FIWTEW_CONTWOW, 0,
						SCW_H_2TAP_HAWDCODE_COEF_EN, 0);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FIWTEW_TYPE_WGB_Y_HOWIZONTAW);
			pwogwam_muwti_taps_fiwtew(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FIWTEW_TYPE_AWPHA_HOWIZONTAW);

			xfm_dce->fiwtew_v = coeffs_v;
			xfm_dce->fiwtew_h = coeffs_h;
		}
	}

	/* 6. Pwogwam the viewpowt */
	pwogwam_viewpowt(xfm_dce, &data->viewpowt);

	/* DCE6 has no SCW_COEF_UPDATE_COMPWETE bit to fwip to new coefficient memowy */

	/* DCE6 DATA_FOWMAT wegistew does not suppowt AWPHA_EN */
}
#endif

/*****************************************************************************
 * set_cwamp
 *
 * @pawam depth : bit depth to set the cwamp to (shouwd match denowm)
 *
 * @bwief
 *     Pwogwams cwamp accowding to panew bit depth.
 *
 *******************************************************************************/
static void set_cwamp(
	stwuct dce_twansfowm *xfm_dce,
	enum dc_cowow_depth depth)
{
	int cwamp_max = 0;

	/* At the cwamp bwock the data wiww be MSB awigned, so we set the max
	 * cwamp accowdingwy.
	 * Fow exampwe, the max vawue fow 6 bits MSB awigned (14 bit bus) wouwd
	 * be "11 1111 0000 0000" in binawy, so 0x3F00.
	 */
	switch (depth) {
	case COWOW_DEPTH_666:
		/* 6bit MSB awigned on 14 bit bus '11 1111 0000 0000' */
		cwamp_max = 0x3F00;
		bweak;
	case COWOW_DEPTH_888:
		/* 8bit MSB awigned on 14 bit bus '11 1111 1100 0000' */
		cwamp_max = 0x3FC0;
		bweak;
	case COWOW_DEPTH_101010:
		/* 10bit MSB awigned on 14 bit bus '11 1111 1111 0000' */
		cwamp_max = 0x3FF0;
		bweak;
	case COWOW_DEPTH_121212:
		/* 12bit MSB awigned on 14 bit bus '11 1111 1111 1100' */
		cwamp_max = 0x3FFC;
		bweak;
	defauwt:
		cwamp_max = 0x3FC0;
		BWEAK_TO_DEBUGGEW(); /* Invawid cwamp bit depth */
	}
	WEG_SET_2(OUT_CWAMP_CONTWOW_B_CB, 0,
			OUT_CWAMP_MIN_B_CB, 0,
			OUT_CWAMP_MAX_B_CB, cwamp_max);

	WEG_SET_2(OUT_CWAMP_CONTWOW_G_Y, 0,
			OUT_CWAMP_MIN_G_Y, 0,
			OUT_CWAMP_MAX_G_Y, cwamp_max);

	WEG_SET_2(OUT_CWAMP_CONTWOW_W_CW, 0,
			OUT_CWAMP_MIN_W_CW, 0,
			OUT_CWAMP_MAX_W_CW, cwamp_max);
}

/*******************************************************************************
 * set_wound
 *
 * @bwief
 *     Pwogwams Wound/Twuncate
 *
 * @pawam [in] mode  :wound ow twuncate
 * @pawam [in] depth :bit depth to wound/twuncate to
 OUT_WOUND_TWUNC_MODE 3:0 0xA Output data wound ow twuncate mode
 POSSIBWE VAWUES:
      00 - twuncate to u0.12
      01 - twuncate to u0.11
      02 - twuncate to u0.10
      03 - twuncate to u0.9
      04 - twuncate to u0.8
      05 - wesewved
      06 - twuncate to u0.14
      07 - twuncate to u0.13		set_weg_fiewd_vawue(
			vawue,
			cwamp_max,
			OUT_CWAMP_CONTWOW_W_CW,
			OUT_CWAMP_MAX_W_CW);
      08 - wound to u0.12
      09 - wound to u0.11
      10 - wound to u0.10
      11 - wound to u0.9
      12 - wound to u0.8
      13 - wesewved
      14 - wound to u0.14
      15 - wound to u0.13

 ******************************************************************************/
static void set_wound(
	stwuct dce_twansfowm *xfm_dce,
	enum dcp_out_twunc_wound_mode mode,
	enum dcp_out_twunc_wound_depth depth)
{
	int depth_bits = 0;
	int mode_bit = 0;

	/*  set up bit depth */
	switch (depth) {
	case DCP_OUT_TWUNC_WOUND_DEPTH_14BIT:
		depth_bits = 6;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_13BIT:
		depth_bits = 7;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_12BIT:
		depth_bits = 0;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_11BIT:
		depth_bits = 1;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_10BIT:
		depth_bits = 2;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_9BIT:
		depth_bits = 3;
		bweak;
	case DCP_OUT_TWUNC_WOUND_DEPTH_8BIT:
		depth_bits = 4;
		bweak;
	defauwt:
		depth_bits = 4;
		BWEAK_TO_DEBUGGEW(); /* Invawid dcp_out_twunc_wound_depth */
	}

	/*  set up wound ow twuncate */
	switch (mode) {
	case DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE:
		mode_bit = 0;
		bweak;
	case DCP_OUT_TWUNC_WOUND_MODE_WOUND:
		mode_bit = 1;
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW(); /* Invawid dcp_out_twunc_wound_mode */
	}

	depth_bits |= mode_bit << 3;

	WEG_SET(OUT_WOUND_CONTWOW, 0, OUT_WOUND_TWUNC_MODE, depth_bits);
}

/*****************************************************************************
 * set_dithew
 *
 * @bwief
 *     Pwogwams Dithew
 *
 * @pawam [in] dithew_enabwe        : enabwe dithew
 * @pawam [in] dithew_mode           : dithew mode to set
 * @pawam [in] dithew_depth          : bit depth to dithew to
 * @pawam [in] fwame_wandom_enabwe    : enabwe fwame wandom
 * @pawam [in] wgb_wandom_enabwe      : enabwe wgb wandom
 * @pawam [in] highpass_wandom_enabwe : enabwe highpass wandom
 *
 ******************************************************************************/

static void set_dithew(
	stwuct dce_twansfowm *xfm_dce,
	boow dithew_enabwe,
	enum dcp_spatiaw_dithew_mode dithew_mode,
	enum dcp_spatiaw_dithew_depth dithew_depth,
	boow fwame_wandom_enabwe,
	boow wgb_wandom_enabwe,
	boow highpass_wandom_enabwe)
{
	int dithew_depth_bits = 0;
	int dithew_mode_bits = 0;

	switch (dithew_mode) {
	case DCP_SPATIAW_DITHEW_MODE_AAAA:
		dithew_mode_bits = 0;
		bweak;
	case DCP_SPATIAW_DITHEW_MODE_A_AA_A:
		dithew_mode_bits = 1;
		bweak;
	case DCP_SPATIAW_DITHEW_MODE_AABBAABB:
		dithew_mode_bits = 2;
		bweak;
	case DCP_SPATIAW_DITHEW_MODE_AABBCCAABBCC:
		dithew_mode_bits = 3;
		bweak;
	defauwt:
		/* Invawid dcp_spatiaw_dithew_mode */
		BWEAK_TO_DEBUGGEW();
	}

	switch (dithew_depth) {
	case DCP_SPATIAW_DITHEW_DEPTH_30BPP:
		dithew_depth_bits = 0;
		bweak;
	case DCP_SPATIAW_DITHEW_DEPTH_24BPP:
		dithew_depth_bits = 1;
		bweak;
	defauwt:
		/* Invawid dcp_spatiaw_dithew_depth */
		BWEAK_TO_DEBUGGEW();
	}

	/*  wwite the wegistew */
	WEG_SET_6(DCP_SPATIAW_DITHEW_CNTW, 0,
			DCP_SPATIAW_DITHEW_EN, dithew_enabwe,
			DCP_SPATIAW_DITHEW_MODE, dithew_mode_bits,
			DCP_SPATIAW_DITHEW_DEPTH, dithew_depth_bits,
			DCP_FWAME_WANDOM_ENABWE, fwame_wandom_enabwe,
			DCP_WGB_WANDOM_ENABWE, wgb_wandom_enabwe,
			DCP_HIGHPASS_WANDOM_ENABWE, highpass_wandom_enabwe);
}

/*****************************************************************************
 * dce_twansfowm_bit_depth_weduction_pwogwam
 *
 * @bwief
 *     Pwogwams the DCP bit depth weduction wegistews (Cwamp, Wound/Twuncate,
 *      Dithew) fow dce
 *
 * @pawam depth : bit depth to set the cwamp to (shouwd match denowm)
 *
 ******************************************************************************/
static void pwogwam_bit_depth_weduction(
	stwuct dce_twansfowm *xfm_dce,
	enum dc_cowow_depth depth,
	const stwuct bit_depth_weduction_pawams *bit_depth_pawams)
{
	enum dcp_out_twunc_wound_depth twunc_wound_depth;
	enum dcp_out_twunc_wound_mode twunc_mode;
	boow spatiaw_dithew_enabwe;

	ASSEWT(depth <= COWOW_DEPTH_121212); /* Invawid cwamp bit depth */

	spatiaw_dithew_enabwe = bit_depth_pawams->fwags.SPATIAW_DITHEW_ENABWED;
	/* Defauwt to 12 bit twuncation without wounding */
	twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_12BIT;
	twunc_mode = DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE;

	if (bit_depth_pawams->fwags.TWUNCATE_ENABWED) {
		/* Don't enabwe dithewing if twuncation is enabwed */
		spatiaw_dithew_enabwe = fawse;
		twunc_mode = bit_depth_pawams->fwags.TWUNCATE_MODE ?
			     DCP_OUT_TWUNC_WOUND_MODE_WOUND :
			     DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE;

		if (bit_depth_pawams->fwags.TWUNCATE_DEPTH == 0 ||
		    bit_depth_pawams->fwags.TWUNCATE_DEPTH == 1)
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_8BIT;
		ewse if (bit_depth_pawams->fwags.TWUNCATE_DEPTH == 2)
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_10BIT;
		ewse {
			/*
			 * Invawid twuncate/wound depth. Setting hewe to 12bit
			 * to pwevent use-befowe-initiawize ewwows.
			 */
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_12BIT;
			BWEAK_TO_DEBUGGEW();
		}
	}

	set_cwamp(xfm_dce, depth);
	set_wound(xfm_dce, twunc_mode, twunc_wound_depth);
	set_dithew(xfm_dce,
		   spatiaw_dithew_enabwe,
		   DCP_SPATIAW_DITHEW_MODE_A_AA_A,
		   DCP_SPATIAW_DITHEW_DEPTH_30BPP,
		   bit_depth_pawams->fwags.FWAME_WANDOM,
		   bit_depth_pawams->fwags.WGB_WANDOM,
		   bit_depth_pawams->fwags.HIGHPASS_WANDOM);
}

#if defined(CONFIG_DWM_AMD_DC_SI)
/*****************************************************************************
 * dce60_twansfowm_bit_depth_weduction pwogwam
 *
 * @bwief
 *     Pwogwams the DCP bit depth weduction wegistews (Cwamp, Wound/Twuncate,
 *      Dithew) fow dce
 *
 * @pawam depth : bit depth to set the cwamp to (shouwd match denowm)
 *
 ******************************************************************************/
static void dce60_pwogwam_bit_depth_weduction(
	stwuct dce_twansfowm *xfm_dce,
	enum dc_cowow_depth depth,
	const stwuct bit_depth_weduction_pawams *bit_depth_pawams)
{
	enum dcp_out_twunc_wound_depth twunc_wound_depth;
	enum dcp_out_twunc_wound_mode twunc_mode;
	boow spatiaw_dithew_enabwe;

	ASSEWT(depth <= COWOW_DEPTH_121212); /* Invawid cwamp bit depth */

	spatiaw_dithew_enabwe = bit_depth_pawams->fwags.SPATIAW_DITHEW_ENABWED;
	/* Defauwt to 12 bit twuncation without wounding */
	twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_12BIT;
	twunc_mode = DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE;

	if (bit_depth_pawams->fwags.TWUNCATE_ENABWED) {
		/* Don't enabwe dithewing if twuncation is enabwed */
		spatiaw_dithew_enabwe = fawse;
		twunc_mode = bit_depth_pawams->fwags.TWUNCATE_MODE ?
			     DCP_OUT_TWUNC_WOUND_MODE_WOUND :
			     DCP_OUT_TWUNC_WOUND_MODE_TWUNCATE;

		if (bit_depth_pawams->fwags.TWUNCATE_DEPTH == 0 ||
		    bit_depth_pawams->fwags.TWUNCATE_DEPTH == 1)
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_8BIT;
		ewse if (bit_depth_pawams->fwags.TWUNCATE_DEPTH == 2)
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_10BIT;
		ewse {
			/*
			 * Invawid twuncate/wound depth. Setting hewe to 12bit
			 * to pwevent use-befowe-initiawize ewwows.
			 */
			twunc_wound_depth = DCP_OUT_TWUNC_WOUND_DEPTH_12BIT;
			BWEAK_TO_DEBUGGEW();
		}
	}

	/* DCE6 has no OUT_CWAMP_CONTWOW_* wegistews - set_cwamp() is skipped */
	set_wound(xfm_dce, twunc_mode, twunc_wound_depth);
	set_dithew(xfm_dce,
		   spatiaw_dithew_enabwe,
		   DCP_SPATIAW_DITHEW_MODE_A_AA_A,
		   DCP_SPATIAW_DITHEW_DEPTH_30BPP,
		   bit_depth_pawams->fwags.FWAME_WANDOM,
		   bit_depth_pawams->fwags.WGB_WANDOM,
		   bit_depth_pawams->fwags.HIGHPASS_WANDOM);
}
#endif

static int dce_twansfowm_get_max_num_of_suppowted_wines(
	stwuct dce_twansfowm *xfm_dce,
	enum wb_pixew_depth depth,
	int pixew_width)
{
	int pixews_pew_entwies = 0;
	int max_pixews_suppowts = 0;

	ASSEWT(pixew_width);

	/* Find numbew of pixews that can fit into a singwe WB entwy and
	 * take fwoow of the vawue since we cannot stowe a singwe pixew
	 * acwoss muwtipwe entwies. */
	switch (depth) {
	case WB_PIXEW_DEPTH_18BPP:
		pixews_pew_entwies = xfm_dce->wb_bits_pew_entwy / 18;
		bweak;

	case WB_PIXEW_DEPTH_24BPP:
		pixews_pew_entwies = xfm_dce->wb_bits_pew_entwy / 24;
		bweak;

	case WB_PIXEW_DEPTH_30BPP:
		pixews_pew_entwies = xfm_dce->wb_bits_pew_entwy / 30;
		bweak;

	case WB_PIXEW_DEPTH_36BPP:
		pixews_pew_entwies = xfm_dce->wb_bits_pew_entwy / 36;
		bweak;

	defauwt:
		DC_WOG_WAWNING("%s: Invawid WB pixew depth",
			__func__);
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	ASSEWT(pixews_pew_entwies);

	max_pixews_suppowts =
			pixews_pew_entwies *
			xfm_dce->wb_memowy_size;

	wetuwn (max_pixews_suppowts / pixew_width);
}

static void set_denowmawization(
	stwuct dce_twansfowm *xfm_dce,
	enum dc_cowow_depth depth)
{
	int denowm_mode = 0;

	switch (depth) {
	case COWOW_DEPTH_666:
		/* 63/64 fow 6 bit output cowow depth */
		denowm_mode = 1;
		bweak;
	case COWOW_DEPTH_888:
		/* Unity fow 8 bit output cowow depth
		 * because pwescawe is disabwed by defauwt */
		denowm_mode = 0;
		bweak;
	case COWOW_DEPTH_101010:
		/* 1023/1024 fow 10 bit output cowow depth */
		denowm_mode = 3;
		bweak;
	case COWOW_DEPTH_121212:
		/* 4095/4096 fow 12 bit output cowow depth */
		denowm_mode = 5;
		bweak;
	case COWOW_DEPTH_141414:
	case COWOW_DEPTH_161616:
	defauwt:
		/* not vawid used case! */
		bweak;
	}

	WEG_SET(DENOWM_CONTWOW, 0, DENOWM_MODE, denowm_mode);
}

static void dce_twansfowm_set_pixew_stowage_depth(
	stwuct twansfowm *xfm,
	enum wb_pixew_depth depth,
	const stwuct bit_depth_weduction_pawams *bit_depth_pawams)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	int pixew_depth, expan_mode;
	enum dc_cowow_depth cowow_depth;

	switch (depth) {
	case WB_PIXEW_DEPTH_18BPP:
		cowow_depth = COWOW_DEPTH_666;
		pixew_depth = 2;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_24BPP:
		cowow_depth = COWOW_DEPTH_888;
		pixew_depth = 1;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_30BPP:
		cowow_depth = COWOW_DEPTH_101010;
		pixew_depth = 0;
		expan_mode  = 1;
		bweak;
	case WB_PIXEW_DEPTH_36BPP:
		cowow_depth = COWOW_DEPTH_121212;
		pixew_depth = 3;
		expan_mode  = 0;
		bweak;
	defauwt:
		cowow_depth = COWOW_DEPTH_101010;
		pixew_depth = 0;
		expan_mode  = 1;
		DC_WOG_DC("The pixew depth %d is not vawid, set COWOW_DEPTH_101010 instead.", depth);
		bweak;
	}

	set_denowmawization(xfm_dce, cowow_depth);
	pwogwam_bit_depth_weduction(xfm_dce, cowow_depth, bit_depth_pawams);

	WEG_UPDATE_2(WB_DATA_FOWMAT,
			PIXEW_DEPTH, pixew_depth,
			PIXEW_EXPAN_MODE, expan_mode);

	if (!(xfm_dce->wb_pixew_depth_suppowted & depth)) {
		/*we shouwd use unsuppowted capabiwities
		 *  unwess it is wequiwed by w/a*/
		DC_WOG_DC("%s: Capabiwity not suppowted", __func__);
	}
}

#if defined(CONFIG_DWM_AMD_DC_SI)
static void dce60_twansfowm_set_pixew_stowage_depth(
	stwuct twansfowm *xfm,
	enum wb_pixew_depth depth,
	const stwuct bit_depth_weduction_pawams *bit_depth_pawams)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	enum dc_cowow_depth cowow_depth;

	switch (depth) {
	case WB_PIXEW_DEPTH_18BPP:
		cowow_depth = COWOW_DEPTH_666;
		bweak;
	case WB_PIXEW_DEPTH_24BPP:
		cowow_depth = COWOW_DEPTH_888;
		bweak;
	case WB_PIXEW_DEPTH_30BPP:
		cowow_depth = COWOW_DEPTH_101010;
		bweak;
	case WB_PIXEW_DEPTH_36BPP:
		cowow_depth = COWOW_DEPTH_121212;
		bweak;
	defauwt:
		cowow_depth = COWOW_DEPTH_101010;
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	set_denowmawization(xfm_dce, cowow_depth);
	dce60_pwogwam_bit_depth_weduction(xfm_dce, cowow_depth, bit_depth_pawams);

	/* DATA_FOWMAT in DCE6 does not have PIXEW_DEPTH and PIXEW_EXPAN_MODE masks */

	if (!(xfm_dce->wb_pixew_depth_suppowted & depth)) {
		/*we shouwd use unsuppowted capabiwities
		 *  unwess it is wequiwed by w/a*/
		DC_WOG_WAWNING("%s: Capabiwity not suppowted",
			__func__);
	}
}
#endif

static void pwogwam_gamut_wemap(
	stwuct dce_twansfowm *xfm_dce,
	const uint16_t *weg_vaw)
{
	if (weg_vaw) {
		WEG_SET_2(GAMUT_WEMAP_C11_C12, 0,
				GAMUT_WEMAP_C11, weg_vaw[0],
				GAMUT_WEMAP_C12, weg_vaw[1]);
		WEG_SET_2(GAMUT_WEMAP_C13_C14, 0,
				GAMUT_WEMAP_C13, weg_vaw[2],
				GAMUT_WEMAP_C14, weg_vaw[3]);
		WEG_SET_2(GAMUT_WEMAP_C21_C22, 0,
				GAMUT_WEMAP_C21, weg_vaw[4],
				GAMUT_WEMAP_C22, weg_vaw[5]);
		WEG_SET_2(GAMUT_WEMAP_C23_C24, 0,
				GAMUT_WEMAP_C23, weg_vaw[6],
				GAMUT_WEMAP_C24, weg_vaw[7]);
		WEG_SET_2(GAMUT_WEMAP_C31_C32, 0,
				GAMUT_WEMAP_C31, weg_vaw[8],
				GAMUT_WEMAP_C32, weg_vaw[9]);
		WEG_SET_2(GAMUT_WEMAP_C33_C34, 0,
				GAMUT_WEMAP_C33, weg_vaw[10],
				GAMUT_WEMAP_C34, weg_vaw[11]);

		WEG_SET(GAMUT_WEMAP_CONTWOW, 0, GWPH_GAMUT_WEMAP_MODE, 1);
	} ewse
		WEG_SET(GAMUT_WEMAP_CONTWOW, 0, GWPH_GAMUT_WEMAP_MODE, 0);

}

/*
 *****************************************************************************
 *  Function: daw_twansfowm_wide_gamut_set_gamut_wemap
 *
 *  @pawam [in] const stwuct xfm_gwph_csc_adjustment *adjust
 *
 *  @wetuwn
 *     void
 *
 *  @note cawcuwate and appwy cowow tempewatuwe adjustment to in Wgb cowow space
 *
 *  @see
 *
 *****************************************************************************
 */
static void dce_twansfowm_set_gamut_wemap(
	stwuct twansfowm *xfm,
	const stwuct xfm_gwph_csc_adjustment *adjust)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	int i = 0;

	if (adjust->gamut_adjust_type != GWAPHICS_GAMUT_ADJUST_TYPE_SW)
		/* Bypass if type is bypass ow hw */
		pwogwam_gamut_wemap(xfm_dce, NUWW);
	ewse {
		stwuct fixed31_32 aww_matwix[GAMUT_MATWIX_SIZE];
		uint16_t aww_weg_vaw[GAMUT_MATWIX_SIZE];

		fow (i = 0; i < GAMUT_MATWIX_SIZE; i++)
			aww_matwix[i] = adjust->tempewatuwe_matwix[i];

		convewt_fwoat_matwix(
			aww_weg_vaw, aww_matwix, GAMUT_MATWIX_SIZE);

		pwogwam_gamut_wemap(xfm_dce, aww_weg_vaw);
	}
}

static uint32_t decide_taps(stwuct fixed31_32 watio, uint32_t in_taps, boow chwoma)
{
	uint32_t taps;

	if (IDENTITY_WATIO(watio)) {
		wetuwn 1;
	} ewse if (in_taps != 0) {
		taps = in_taps;
	} ewse {
		taps = 4;
	}

	if (chwoma) {
		taps /= 2;
		if (taps < 2)
			taps = 2;
	}

	wetuwn taps;
}


boow dce_twansfowm_get_optimaw_numbew_of_taps(
	stwuct twansfowm *xfm,
	stwuct scawew_data *scw_data,
	const stwuct scawing_taps *in_taps)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	int pixew_width = scw_data->viewpowt.width;
	int max_num_of_wines;

	if (xfm_dce->pwescawew_on &&
			(scw_data->viewpowt.width > scw_data->wecout.width))
		pixew_width = scw_data->wecout.width;

	max_num_of_wines = dce_twansfowm_get_max_num_of_suppowted_wines(
		xfm_dce,
		scw_data->wb_pawams.depth,
		pixew_width);

	/* Faiw if in_taps awe impossibwe */
	if (in_taps->v_taps >= max_num_of_wines)
		wetuwn fawse;

	/*
	 * Set taps accowding to this powicy (in this owdew)
	 * - Use 1 fow no scawing
	 * - Use input taps
	 * - Use 4 and weduce as wequiwed by wine buffew size
	 * - Decide chwoma taps if chwoma is scawed
	 *
	 * Ignowe input chwoma taps. Decide based on non-chwoma
	 */
	scw_data->taps.h_taps = decide_taps(scw_data->watios.howz, in_taps->h_taps, fawse);
	scw_data->taps.v_taps = decide_taps(scw_data->watios.vewt, in_taps->v_taps, fawse);
	scw_data->taps.h_taps_c = decide_taps(scw_data->watios.howz_c, in_taps->h_taps, twue);
	scw_data->taps.v_taps_c = decide_taps(scw_data->watios.vewt_c, in_taps->v_taps, twue);

	if (!IDENTITY_WATIO(scw_data->watios.vewt)) {
		/* weduce v_taps if needed but ensuwe we have at weast two */
		if (in_taps->v_taps == 0
				&& max_num_of_wines <= scw_data->taps.v_taps
				&& scw_data->taps.v_taps > 1) {
			scw_data->taps.v_taps = max_num_of_wines - 1;
		}

		if (scw_data->taps.v_taps <= 1)
			wetuwn fawse;
	}

	if (!IDENTITY_WATIO(scw_data->watios.vewt_c)) {
		/* weduce chwoma v_taps if needed but ensuwe we have at weast two */
		if (max_num_of_wines <= scw_data->taps.v_taps_c && scw_data->taps.v_taps_c > 1) {
			scw_data->taps.v_taps_c = max_num_of_wines - 1;
		}

		if (scw_data->taps.v_taps_c <= 1)
			wetuwn fawse;
	}

	/* we've got vawid taps */
	wetuwn twue;
}

static void dce_twansfowm_weset(stwuct twansfowm *xfm)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	xfm_dce->fiwtew_h = NUWW;
	xfm_dce->fiwtew_v = NUWW;
}

static void pwogwam_cowow_matwix(
	stwuct dce_twansfowm *xfm_dce,
	const stwuct out_csc_cowow_matwix *tbw_entwy,
	enum gwph_cowow_adjust_option options)
{
	{
		WEG_SET_2(OUTPUT_CSC_C11_C12, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[0],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[1]);
	}
	{
		WEG_SET_2(OUTPUT_CSC_C13_C14, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[2],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[3]);
	}
	{
		WEG_SET_2(OUTPUT_CSC_C21_C22, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[4],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[5]);
	}
	{
		WEG_SET_2(OUTPUT_CSC_C23_C24, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[6],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[7]);
	}
	{
		WEG_SET_2(OUTPUT_CSC_C31_C32, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[8],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[9]);
	}
	{
		WEG_SET_2(OUTPUT_CSC_C33_C34, 0,
			OUTPUT_CSC_C11, tbw_entwy->wegvaw[10],
			OUTPUT_CSC_C12, tbw_entwy->wegvaw[11]);
	}
}

static boow configuwe_gwaphics_mode(
	stwuct dce_twansfowm *xfm_dce,
	enum csc_cowow_mode config,
	enum gwaphics_csc_adjust_type csc_adjust_type,
	enum dc_cowow_space cowow_space)
{
	WEG_SET(OUTPUT_CSC_CONTWOW, 0,
		OUTPUT_CSC_GWPH_MODE, 0);

	if (csc_adjust_type == GWAPHICS_CSC_ADJUST_TYPE_SW) {
		if (config == CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC) {
			WEG_SET(OUTPUT_CSC_CONTWOW, 0,
				OUTPUT_CSC_GWPH_MODE, 4);
		} ewse {

			switch (cowow_space) {
			case COWOW_SPACE_SWGB:
				/* by pass */
				WEG_SET(OUTPUT_CSC_CONTWOW, 0,
					OUTPUT_CSC_GWPH_MODE, 0);
				bweak;
			case COWOW_SPACE_SWGB_WIMITED:
				/* TV WGB */
				WEG_SET(OUTPUT_CSC_CONTWOW, 0,
					OUTPUT_CSC_GWPH_MODE, 1);
				bweak;
			case COWOW_SPACE_YCBCW601:
			case COWOW_SPACE_YCBCW601_WIMITED:
				/* YCbCw601 */
				WEG_SET(OUTPUT_CSC_CONTWOW, 0,
					OUTPUT_CSC_GWPH_MODE, 2);
				bweak;
			case COWOW_SPACE_YCBCW709:
			case COWOW_SPACE_YCBCW709_WIMITED:
				/* YCbCw709 */
				WEG_SET(OUTPUT_CSC_CONTWOW, 0,
					OUTPUT_CSC_GWPH_MODE, 3);
				bweak;
			defauwt:
				wetuwn fawse;
			}
		}
	} ewse if (csc_adjust_type == GWAPHICS_CSC_ADJUST_TYPE_HW) {
		switch (cowow_space) {
		case COWOW_SPACE_SWGB:
			/* by pass */
			WEG_SET(OUTPUT_CSC_CONTWOW, 0,
				OUTPUT_CSC_GWPH_MODE, 0);
			bweak;
		case COWOW_SPACE_SWGB_WIMITED:
			/* TV WGB */
			WEG_SET(OUTPUT_CSC_CONTWOW, 0,
				OUTPUT_CSC_GWPH_MODE, 1);
			bweak;
		case COWOW_SPACE_YCBCW601:
		case COWOW_SPACE_YCBCW601_WIMITED:
			/* YCbCw601 */
			WEG_SET(OUTPUT_CSC_CONTWOW, 0,
				OUTPUT_CSC_GWPH_MODE, 2);
			bweak;
		case COWOW_SPACE_YCBCW709:
		case COWOW_SPACE_YCBCW709_WIMITED:
			 /* YCbCw709 */
			WEG_SET(OUTPUT_CSC_CONTWOW, 0,
				OUTPUT_CSC_GWPH_MODE, 3);
			bweak;
		defauwt:
			wetuwn fawse;
		}

	} ewse
		/* by pass */
		WEG_SET(OUTPUT_CSC_CONTWOW, 0,
			OUTPUT_CSC_GWPH_MODE, 0);

	wetuwn twue;
}

void dce110_opp_set_csc_adjustment(
	stwuct twansfowm *xfm,
	const stwuct out_csc_cowow_matwix *tbw_entwy)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	enum csc_cowow_mode config =
			CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC;

	pwogwam_cowow_matwix(
			xfm_dce, tbw_entwy, GWPH_COWOW_MATWIX_SW);

	/*  We did evewything ,now pwogwam DxOUTPUT_CSC_CONTWOW */
	configuwe_gwaphics_mode(xfm_dce, config, GWAPHICS_CSC_ADJUST_TYPE_SW,
			tbw_entwy->cowow_space);
}

void dce110_opp_set_csc_defauwt(
	stwuct twansfowm *xfm,
	const stwuct defauwt_adjustment *defauwt_adjust)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);
	enum csc_cowow_mode config =
			CSC_COWOW_MODE_GWAPHICS_PWEDEFINED;

	if (defauwt_adjust->fowce_hw_defauwt == fawse) {
		const stwuct out_csc_cowow_matwix *ewm;
		/* cuwwentwy pawametew not in use */
		enum gwph_cowow_adjust_option option =
			GWPH_COWOW_MATWIX_HW_DEFAUWT;
		uint32_t i;
		/*
		 * HW defauwt fawse we pwogwam wocawwy defined matwix
		 * HW defauwt twue  we use pwedefined hw matwix and we
		 * do not need to pwogwam matwix
		 * OEM wants the HW defauwt via wuntime pawametew.
		 */
		option = GWPH_COWOW_MATWIX_SW;

		fow (i = 0; i < AWWAY_SIZE(gwobaw_cowow_matwix); ++i) {
			ewm = &gwobaw_cowow_matwix[i];
			if (ewm->cowow_space != defauwt_adjust->out_cowow_space)
				continue;
			/* pwogwam the matwix with defauwt vawues fwom this
			 * fiwe */
			pwogwam_cowow_matwix(xfm_dce, ewm, option);
			config = CSC_COWOW_MODE_GWAPHICS_OUTPUT_CSC;
			bweak;
		}
	}

	/* configuwe the what we pwogwammed :
	 * 1. Defauwt vawues fwom this fiwe
	 * 2. Use hawdwawe defauwt fwom WOM_A and we do not need to pwogwam
	 * matwix */

	configuwe_gwaphics_mode(xfm_dce, config,
		defauwt_adjust->csc_adjust_type,
		defauwt_adjust->out_cowow_space);
}

static void pwogwam_pww(stwuct dce_twansfowm *xfm_dce,
			const stwuct pww_pawams *pawams)
{
	int wetvaw;
	uint8_t max_twies = 10;
	uint8_t countew = 0;
	uint32_t i = 0;
	const stwuct pww_wesuwt_data *wgb = pawams->wgb_wesuwted;

	/* Powew on WUT memowy */
	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_UPDATE(DCFE_MEM_PWW_CTWW,
			   DCP_WEGAMMA_MEM_PWW_DIS, 1);
	ewse
		WEG_UPDATE(DCFE_MEM_WIGHT_SWEEP_CNTW,
			   WEGAMMA_WUT_WIGHT_SWEEP_DIS, 1);

	whiwe (countew < max_twies) {
		if (WEG(DCFE_MEM_PWW_STATUS)) {
			WEG_GET(DCFE_MEM_PWW_STATUS,
				DCP_WEGAMMA_MEM_PWW_STATE,
				&wetvaw);

			if (wetvaw == 0)
				bweak;
			++countew;
		} ewse {
			WEG_GET(DCFE_MEM_WIGHT_SWEEP_CNTW,
				WEGAMMA_WUT_MEM_PWW_STATE,
				&wetvaw);

			if (wetvaw == 0)
				bweak;
			++countew;
		}
	}

	if (countew == max_twies) {
		DC_WOG_WAWNING("%s: wegamma wut was not powewed on "
				"in a timewy mannew,"
				" pwogwamming stiww pwoceeds\n",
				__func__);
	}

	WEG_UPDATE(WEGAMMA_WUT_WWITE_EN_MASK,
		   WEGAMMA_WUT_WWITE_EN_MASK, 7);

	WEG_WWITE(WEGAMMA_WUT_INDEX, 0);

	/* Pwogwam WEGAMMA_WUT_DATA */
	whiwe (i != pawams->hw_points_num) {

		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->wed_weg);
		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->gween_weg);
		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->bwue_weg);
		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->dewta_wed_weg);
		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->dewta_gween_weg);
		WEG_WWITE(WEGAMMA_WUT_DATA, wgb->dewta_bwue_weg);

		++wgb;
		++i;
	}

	/*  we awe done with DCP WUT memowy; we-enabwe wow powew mode */
	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_UPDATE(DCFE_MEM_PWW_CTWW,
			   DCP_WEGAMMA_MEM_PWW_DIS, 0);
	ewse
		WEG_UPDATE(DCFE_MEM_WIGHT_SWEEP_CNTW,
			   WEGAMMA_WUT_WIGHT_SWEEP_DIS, 0);
}

static void wegamma_config_wegions_and_segments(stwuct dce_twansfowm *xfm_dce,
						const stwuct pww_pawams *pawams)
{
	const stwuct gamma_cuwve *cuwve;

	WEG_SET_2(WEGAMMA_CNTWA_STAWT_CNTW, 0,
		  WEGAMMA_CNTWA_EXP_WEGION_STAWT, pawams->aww_points[0].custom_fwoat_x,
		  WEGAMMA_CNTWA_EXP_WEGION_STAWT_SEGMENT, 0);

	WEG_SET(WEGAMMA_CNTWA_SWOPE_CNTW, 0,
		WEGAMMA_CNTWA_EXP_WEGION_WINEAW_SWOPE, pawams->aww_points[0].custom_fwoat_swope);

	WEG_SET(WEGAMMA_CNTWA_END_CNTW1, 0,
		WEGAMMA_CNTWA_EXP_WEGION_END, pawams->aww_points[1].custom_fwoat_x);

	WEG_SET_2(WEGAMMA_CNTWA_END_CNTW2, 0,
		  WEGAMMA_CNTWA_EXP_WEGION_END_BASE, pawams->aww_points[1].custom_fwoat_y,
		  WEGAMMA_CNTWA_EXP_WEGION_END_SWOPE, pawams->aww_points[1].custom_fwoat_swope);

	cuwve = pawams->aww_cuwve_points;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_0_1, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_2_3, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_4_5, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_6_7, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_8_9, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_10_11, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_12_13, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
	cuwve += 2;

	WEG_SET_4(WEGAMMA_CNTWA_WEGION_14_15, 0,
		  WEGAMMA_CNTWA_EXP_WEGION0_WUT_OFFSET, cuwve[0].offset,
		  WEGAMMA_CNTWA_EXP_WEGION0_NUM_SEGMENTS, cuwve[0].segments_num,
		  WEGAMMA_CNTWA_EXP_WEGION1_WUT_OFFSET, cuwve[1].offset,
		  WEGAMMA_CNTWA_EXP_WEGION1_NUM_SEGMENTS, cuwve[1].segments_num);
}



void dce110_opp_pwogwam_wegamma_pww(stwuct twansfowm *xfm,
				    const stwuct pww_pawams *pawams)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	/* Setup wegions */
	wegamma_config_wegions_and_segments(xfm_dce, pawams);

	/* Pwogwam PWW */
	pwogwam_pww(xfm_dce, pawams);
}

void dce110_opp_powew_on_wegamma_wut(stwuct twansfowm *xfm,
				     boow powew_on)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	if (WEG(DCFE_MEM_PWW_CTWW))
		WEG_UPDATE_2(DCFE_MEM_PWW_CTWW,
			     DCP_WEGAMMA_MEM_PWW_DIS, powew_on,
			     DCP_WUT_MEM_PWW_DIS, powew_on);
	ewse
		WEG_UPDATE_2(DCFE_MEM_WIGHT_SWEEP_CNTW,
			    WEGAMMA_WUT_WIGHT_SWEEP_DIS, powew_on,
			    DCP_WUT_WIGHT_SWEEP_DIS, powew_on);

}

void dce110_opp_set_wegamma_mode(stwuct twansfowm *xfm,
				 enum opp_wegamma mode)
{
	stwuct dce_twansfowm *xfm_dce = TO_DCE_TWANSFOWM(xfm);

	WEG_SET(WEGAMMA_CONTWOW, 0,
		GWPH_WEGAMMA_MODE, mode);
}

static const stwuct twansfowm_funcs dce_twansfowm_funcs = {
	.twansfowm_weset = dce_twansfowm_weset,
	.twansfowm_set_scawew = dce_twansfowm_set_scawew,
	.twansfowm_set_gamut_wemap = dce_twansfowm_set_gamut_wemap,
	.opp_set_csc_adjustment = dce110_opp_set_csc_adjustment,
	.opp_set_csc_defauwt = dce110_opp_set_csc_defauwt,
	.opp_powew_on_wegamma_wut = dce110_opp_powew_on_wegamma_wut,
	.opp_pwogwam_wegamma_pww = dce110_opp_pwogwam_wegamma_pww,
	.opp_set_wegamma_mode = dce110_opp_set_wegamma_mode,
	.twansfowm_set_pixew_stowage_depth = dce_twansfowm_set_pixew_stowage_depth,
	.twansfowm_get_optimaw_numbew_of_taps = dce_twansfowm_get_optimaw_numbew_of_taps
};

#if defined(CONFIG_DWM_AMD_DC_SI)
static const stwuct twansfowm_funcs dce60_twansfowm_funcs = {
	.twansfowm_weset = dce_twansfowm_weset,
	.twansfowm_set_scawew = dce60_twansfowm_set_scawew,
	.twansfowm_set_gamut_wemap = dce_twansfowm_set_gamut_wemap,
	.opp_set_csc_adjustment = dce110_opp_set_csc_adjustment,
	.opp_set_csc_defauwt = dce110_opp_set_csc_defauwt,
	.opp_powew_on_wegamma_wut = dce110_opp_powew_on_wegamma_wut,
	.opp_pwogwam_wegamma_pww = dce110_opp_pwogwam_wegamma_pww,
	.opp_set_wegamma_mode = dce110_opp_set_wegamma_mode,
	.twansfowm_set_pixew_stowage_depth = dce60_twansfowm_set_pixew_stowage_depth,
	.twansfowm_get_optimaw_numbew_of_taps = dce_twansfowm_get_optimaw_numbew_of_taps
};
#endif

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

void dce_twansfowm_constwuct(
	stwuct dce_twansfowm *xfm_dce,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dce_twansfowm_wegistews *wegs,
	const stwuct dce_twansfowm_shift *xfm_shift,
	const stwuct dce_twansfowm_mask *xfm_mask)
{
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.inst = inst;
	xfm_dce->base.funcs = &dce_twansfowm_funcs;

	xfm_dce->wegs = wegs;
	xfm_dce->xfm_shift = xfm_shift;
	xfm_dce->xfm_mask = xfm_mask;

	xfm_dce->pwescawew_on = twue;
	xfm_dce->wb_pixew_depth_suppowted =
			WB_PIXEW_DEPTH_18BPP |
			WB_PIXEW_DEPTH_24BPP |
			WB_PIXEW_DEPTH_30BPP |
			WB_PIXEW_DEPTH_36BPP;

	xfm_dce->wb_bits_pew_entwy = WB_BITS_PEW_ENTWY;
	xfm_dce->wb_memowy_size = WB_TOTAW_NUMBEW_OF_ENTWIES; /*0x6B0*/
}

#if defined(CONFIG_DWM_AMD_DC_SI)
void dce60_twansfowm_constwuct(
	stwuct dce_twansfowm *xfm_dce,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dce_twansfowm_wegistews *wegs,
	const stwuct dce_twansfowm_shift *xfm_shift,
	const stwuct dce_twansfowm_mask *xfm_mask)
{
	xfm_dce->base.ctx = ctx;

	xfm_dce->base.inst = inst;
	xfm_dce->base.funcs = &dce60_twansfowm_funcs;

	xfm_dce->wegs = wegs;
	xfm_dce->xfm_shift = xfm_shift;
	xfm_dce->xfm_mask = xfm_mask;

	xfm_dce->pwescawew_on = twue;
	xfm_dce->wb_pixew_depth_suppowted =
			WB_PIXEW_DEPTH_18BPP |
			WB_PIXEW_DEPTH_24BPP |
			WB_PIXEW_DEPTH_30BPP |
			WB_PIXEW_DEPTH_36BPP;

	xfm_dce->wb_bits_pew_entwy = WB_BITS_PEW_ENTWY;
	xfm_dce->wb_memowy_size = WB_TOTAW_NUMBEW_OF_ENTWIES; /*0x6B0*/
}
#endif
