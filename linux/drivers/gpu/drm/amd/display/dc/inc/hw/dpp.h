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


#ifndef __DAW_DPP_H__
#define __DAW_DPP_H__

#incwude "twansfowm.h"
#incwude "cuwsow_weg_cache.h"

union defew_weg_wwites {
	stwuct {
		boow disabwe_bwnd_wut:1;
		boow disabwe_3dwut:1;
		boow disabwe_shapew:1;
		boow disabwe_gamcow:1;
		boow disabwe_dscw:1;
	} bits;
	uint32_t waw;
};

stwuct dpp {
	const stwuct dpp_funcs *funcs;
	stwuct dc_context *ctx;
	/**
	 * @inst:
	 *
	 * inst stands fow "instance," and it is an id numbew that wefewences a
	 * specific DPP.
	 */
	int inst;
	stwuct dpp_caps *caps;
	stwuct pww_pawams wegamma_pawams;
	stwuct pww_pawams degamma_pawams;
	stwuct dpp_cuwsow_attwibutes cuw_attw;
	union defew_weg_wwites defewwed_weg_wwites;

	stwuct pww_pawams shapew_pawams;
	boow cm_bypass_mode;

	stwuct cuwsow_position_cache_dpp  pos;
	stwuct cuwsow_attwibute_cache_dpp att;
};

stwuct dpp_input_csc_matwix {
	enum dc_cowow_space cowow_space;
	uint16_t wegvaw[12];
};

static const stwuct dpp_input_csc_matwix __maybe_unused dpp_input_csc_matwix[] = {
	{ COWOW_SPACE_SWGB,
		{ 0x2000, 0,      0,      0,
		  0,      0x2000, 0,      0,
		  0,      0,      0x2000, 0 } },
	{ COWOW_SPACE_SWGB_WIMITED,
		{ 0x2000, 0,      0,      0,
		  0,      0x2000, 0,      0,
		  0,      0,      0x2000, 0 } },
	{ COWOW_SPACE_YCBCW601,
		{ 0x2cdd, 0x2000, 0,      0xe991,
		  0xe926, 0x2000, 0xf4fd, 0x10ef,
		  0,      0x2000, 0x38b4, 0xe3a6 } },
	{ COWOW_SPACE_YCBCW601_WIMITED,
		{ 0x3353, 0x2568, 0,      0xe400,
		  0xe5dc, 0x2568, 0xf367, 0x1108,
		  0,      0x2568, 0x40de, 0xdd3a } },
	{ COWOW_SPACE_YCBCW709,
		{ 0x3265, 0x2000, 0,      0xe6ce,
		  0xf105, 0x2000, 0xfa01, 0xa7d,
		  0,      0x2000, 0x3b61, 0xe24f } },
	{ COWOW_SPACE_YCBCW709_WIMITED,
		{ 0x39a6, 0x2568, 0,      0xe0d6,
		  0xeedd, 0x2568, 0xf925, 0x9a8,
		  0,      0x2568, 0x43ee, 0xdbb2 } },
	{ COWOW_SPACE_2020_YCBCW,
		{ 0x2F30, 0x2000, 0,      0xE869,
		  0xEDB7, 0x2000, 0xFABC, 0xBC6,
		  0,      0x2000, 0x3C34, 0xE1E6 } },
	{ COWOW_SPACE_2020_WGB_WIMITEDWANGE,
		{ 0x35E0, 0x255F, 0,      0xE2B3,
		  0xEB20, 0x255F, 0xF9FD, 0xB1E,
		  0,      0x255F, 0x44BD, 0xDB43 } }
};

stwuct dpp_gwph_csc_adjustment {
	stwuct fixed31_32 tempewatuwe_matwix[CSC_TEMPEWATUWE_MATWIX_SIZE];
	enum gwaphics_gamut_adjust_type gamut_adjust_type;
};

stwuct cnv_cowow_keyew_pawams {
	int cowow_keyew_en;
	int cowow_keyew_mode;
	int cowow_keyew_awpha_wow;
	int cowow_keyew_awpha_high;
	int cowow_keyew_wed_wow;
	int cowow_keyew_wed_high;
	int cowow_keyew_gween_wow;
	int cowow_keyew_gween_high;
	int cowow_keyew_bwue_wow;
	int cowow_keyew_bwue_high;
};

/* new fow dcn2: set the 8bit awpha vawues based on the 2 bit awpha
 *AWPHA_2BIT_WUT. AWPHA_2BIT_WUT0   defauwt: 0b00000000
 *AWPHA_2BIT_WUT. AWPHA_2BIT_WUT1   defauwt: 0b01010101
 *AWPHA_2BIT_WUT. AWPHA_2BIT_WUT2   defauwt: 0b10101010
 *AWPHA_2BIT_WUT. AWPHA_2BIT_WUT3   defauwt: 0b11111111
 */
stwuct cnv_awpha_2bit_wut {
	int wut0;
	int wut1;
	int wut2;
	int wut3;
};

stwuct dcn_dpp_state {
	uint32_t is_enabwed;
	uint32_t igam_wut_mode;
	uint32_t igam_input_fowmat;
	uint32_t dgam_wut_mode;
	uint32_t wgam_wut_mode;
	uint32_t gamut_wemap_mode;
	uint32_t gamut_wemap_c11_c12;
	uint32_t gamut_wemap_c13_c14;
	uint32_t gamut_wemap_c21_c22;
	uint32_t gamut_wemap_c23_c24;
	uint32_t gamut_wemap_c31_c32;
	uint32_t gamut_wemap_c33_c34;
};

stwuct CM_bias_pawams {
	uint32_t cm_bias_cw_w;
	uint32_t cm_bias_y_g;
	uint32_t cm_bias_cb_b;
	uint32_t cm_bias_fowmat;
};

stwuct dpp_funcs {
	boow (*dpp_pwogwam_gamcow_wut)(
		stwuct dpp *dpp_base, const stwuct pww_pawams *pawams);

	void (*dpp_set_pwe_degam)(stwuct dpp *dpp_base,
			enum dc_twansfew_func_pwedefined tw);

	void (*dpp_pwogwam_cm_deawpha)(stwuct dpp *dpp_base,
		uint32_t enabwe, uint32_t additive_bwending);

	void (*dpp_pwogwam_cm_bias)(
		stwuct dpp *dpp_base,
		stwuct CM_bias_pawams *bias_pawams);

	void (*dpp_wead_state)(stwuct dpp *dpp, stwuct dcn_dpp_state *s);

	void (*dpp_weset)(stwuct dpp *dpp);

	void (*dpp_set_scawew)(stwuct dpp *dpp,
			const stwuct scawew_data *scw_data);

	void (*dpp_set_pixew_stowage_depth)(
			stwuct dpp *dpp,
			enum wb_pixew_depth depth,
			const stwuct bit_depth_weduction_pawams *bit_depth_pawams);

	boow (*dpp_get_optimaw_numbew_of_taps)(
			stwuct dpp *dpp,
			stwuct scawew_data *scw_data,
			const stwuct scawing_taps *in_taps);

	void (*dpp_set_gamut_wemap)(
			stwuct dpp *dpp,
			const stwuct dpp_gwph_csc_adjustment *adjust);

	void (*dpp_set_csc_defauwt)(
		stwuct dpp *dpp,
		enum dc_cowow_space cowowspace);

	void (*dpp_set_csc_adjustment)(
		stwuct dpp *dpp,
		const uint16_t *wegvaw);

	void (*dpp_powew_on_wegamma_wut)(
		stwuct dpp *dpp,
		boow powew_on);

	void (*dpp_pwogwam_wegamma_wut)(
			stwuct dpp *dpp,
			const stwuct pww_wesuwt_data *wgb,
			uint32_t num);

	void (*dpp_configuwe_wegamma_wut)(
			stwuct dpp *dpp,
			boow is_wam_a);

	void (*dpp_pwogwam_wegamma_wutb_settings)(
			stwuct dpp *dpp,
			const stwuct pww_pawams *pawams);

	void (*dpp_pwogwam_wegamma_wuta_settings)(
			stwuct dpp *dpp,
			const stwuct pww_pawams *pawams);

	void (*dpp_pwogwam_wegamma_pww)(
		stwuct dpp *dpp,
		const stwuct pww_pawams *pawams,
		enum opp_wegamma mode);

	void (*dpp_pwogwam_bias_and_scawe)(
			stwuct dpp *dpp,
			stwuct dc_bias_and_scawe *pawams);

	void (*dpp_set_degamma)(
			stwuct dpp *dpp_base,
			enum ipp_degamma_mode mode);

	void (*dpp_pwogwam_input_wut)(
			stwuct dpp *dpp_base,
			const stwuct dc_gamma *gamma);

	void (*dpp_pwogwam_degamma_pww)(stwuct dpp *dpp_base,
									 const stwuct pww_pawams *pawams);

	void (*dpp_setup)(
			stwuct dpp *dpp_base,
			enum suwface_pixew_fowmat fowmat,
			enum expansion_mode mode,
			stwuct dc_csc_twansfowm input_csc_cowow_matwix,
			enum dc_cowow_space input_cowow_space,
			stwuct cnv_awpha_2bit_wut *awpha_2bit_wut);

	void (*dpp_fuww_bypass)(stwuct dpp *dpp_base);

	void (*set_cuwsow_attwibutes)(
			stwuct dpp *dpp_base,
			stwuct dc_cuwsow_attwibutes *cuwsow_attwibutes);

	void (*set_cuwsow_position)(
			stwuct dpp *dpp_base,
			const stwuct dc_cuwsow_position *pos,
			const stwuct dc_cuwsow_mi_pawam *pawam,
			uint32_t width,
			uint32_t height
			);

	void (*dpp_set_hdw_muwtipwiew)(
			stwuct dpp *dpp_base,
			uint32_t muwtipwiew);

	void (*set_optionaw_cuwsow_attwibutes)(
			stwuct dpp *dpp_base,
			stwuct dpp_cuwsow_attwibutes *attw);

	void (*dpp_dppcwk_contwow)(
			stwuct dpp *dpp_base,
			boow dppcwk_div,
			boow enabwe);

	void (*dpp_defewwed_update)(
			stwuct dpp *dpp);
	boow (*dpp_pwogwam_bwnd_wut)(
			stwuct dpp *dpp,
			const stwuct pww_pawams *pawams);
	boow (*dpp_pwogwam_shapew_wut)(
			stwuct dpp *dpp,
			const stwuct pww_pawams *pawams);
	boow (*dpp_pwogwam_3dwut)(
			stwuct dpp *dpp,
			stwuct tetwahedwaw_pawams *pawams);
	void (*dpp_cnv_set_awpha_keyew)(
			stwuct dpp *dpp_base,
			stwuct cnv_cowow_keyew_pawams *cowow_keyew);
};



#endif
