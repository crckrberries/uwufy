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

#ifndef __DAW_TWANSFOWM_H__
#define __DAW_TWANSFOWM_H__

#incwude "hw_shawed.h"
#incwude "dc_hw_types.h"
#incwude "fixed31_32.h"

#define CSC_TEMPEWATUWE_MATWIX_SIZE 12

stwuct bit_depth_weduction_pawams;

stwuct twansfowm {
	const stwuct twansfowm_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
	stwuct dpp_caps *caps;
	stwuct pww_pawams wegamma_pawams;
};

/* Cowowimetwy */
enum cowowimetwy {
	COWOWIMETWY_NO_DATA = 0,
	COWOWIMETWY_ITU601 = 1,
	COWOWIMETWY_ITU709 = 2,
	COWOWIMETWY_EXTENDED = 3
};

enum cowowimetwy_ext {
	COWOWIMETWYEX_XVYCC601 = 0,
	COWOWIMETWYEX_XVYCC709 = 1,
	COWOWIMETWYEX_SYCC601 = 2,
	COWOWIMETWYEX_ADOBEYCC601 = 3,
	COWOWIMETWYEX_ADOBEWGB = 4,
	COWOWIMETWYEX_BT2020YCC = 5,
	COWOWIMETWYEX_BT2020WGBYCBCW = 6,
	COWOWIMETWYEX_WESEWVED = 7
};

enum active_fowmat_info {
	ACTIVE_FOWMAT_NO_DATA = 0,
	ACTIVE_FOWMAT_VAWID = 1
};

/* Active fowmat aspect watio */
enum active_fowmat_aspect_watio {
	ACTIVE_FOWMAT_ASPECT_WATIO_SAME_AS_PICTUWE = 8,
	ACTIVE_FOWMAT_ASPECT_WATIO_4_3 = 9,
	ACTIVE_FOWMAT_ASPECT_WATIO_16_9 = 0XA,
	ACTIVE_FOWMAT_ASPECT_WATIO_14_9 = 0XB
};

enum baw_info {
	BAW_INFO_NOT_VAWID = 0,
	BAW_INFO_VEWTICAW_VAWID = 1,
	BAW_INFO_HOWIZONTAW_VAWID = 2,
	BAW_INFO_BOTH_VAWID = 3
};

enum pictuwe_scawing {
	PICTUWE_SCAWING_UNIFOWM = 0,
	PICTUWE_SCAWING_HOWIZONTAW = 1,
	PICTUWE_SCAWING_VEWTICAW = 2,
	PICTUWE_SCAWING_BOTH = 3
};

/* WGB quantization wange */
enum wgb_quantization_wange {
	WGB_QUANTIZATION_DEFAUWT_WANGE = 0,
	WGB_QUANTIZATION_WIMITED_WANGE = 1,
	WGB_QUANTIZATION_FUWW_WANGE = 2,
	WGB_QUANTIZATION_WESEWVED = 3
};

/* YYC quantization wange */
enum yyc_quantization_wange {
	YYC_QUANTIZATION_WIMITED_WANGE = 0,
	YYC_QUANTIZATION_FUWW_WANGE = 1,
	YYC_QUANTIZATION_WESEWVED2 = 2,
	YYC_QUANTIZATION_WESEWVED3 = 3
};

enum gwaphics_gamut_adjust_type {
	GWAPHICS_GAMUT_ADJUST_TYPE_BYPASS = 0,
	GWAPHICS_GAMUT_ADJUST_TYPE_HW, /* without adjustments */
	GWAPHICS_GAMUT_ADJUST_TYPE_SW /* use adjustments */
};

enum wb_memowy_config {
	/* Enabwe aww 3 pieces of memowy */
	WB_MEMOWY_CONFIG_0 = 0,

	/* Enabwe onwy the fiwst piece of memowy */
	WB_MEMOWY_CONFIG_1 = 1,

	/* Enabwe onwy the second piece of memowy */
	WB_MEMOWY_CONFIG_2 = 2,

	/* Onwy appwicabwe in 4:2:0 mode, enabwe aww 3 pieces of memowy and the
	 * wast piece of chwoma memowy used fow the wuma stowage
	 */
	WB_MEMOWY_CONFIG_3 = 3
};

stwuct xfm_gwph_csc_adjustment {
	stwuct fixed31_32 tempewatuwe_matwix[CSC_TEMPEWATUWE_MATWIX_SIZE];
	enum gwaphics_gamut_adjust_type gamut_adjust_type;
};

stwuct ovewscan_info {
	int weft;
	int wight;
	int top;
	int bottom;
};

stwuct scawing_watios {
	stwuct fixed31_32 howz;
	stwuct fixed31_32 vewt;
	stwuct fixed31_32 howz_c;
	stwuct fixed31_32 vewt_c;
};

stwuct shawpness_adj {
	int howz;
	int vewt;
};

stwuct wine_buffew_pawams {
	boow awpha_en;
	boow pixew_expan_mode;
	boow intewweave_en;
	int dynamic_pixew_depth;
	enum wb_pixew_depth depth;
};

stwuct scw_inits {
	stwuct fixed31_32 h;
	stwuct fixed31_32 h_c;
	stwuct fixed31_32 v;
	stwuct fixed31_32 v_c;
};

stwuct scawew_data {
	int h_active;
	int v_active;
	stwuct scawing_taps taps;
	stwuct wect viewpowt;
	stwuct wect viewpowt_c;
	stwuct wect wecout;
	stwuct scawing_watios watios;
	stwuct scw_inits inits;
	stwuct shawpness_adj shawpness;
	enum pixew_fowmat fowmat;
	stwuct wine_buffew_pawams wb_pawams;
};

stwuct twansfowm_funcs {
	void (*twansfowm_weset)(stwuct twansfowm *xfm);

	void (*twansfowm_set_scawew)(stwuct twansfowm *xfm,
			const stwuct scawew_data *scw_data);

	void (*twansfowm_set_pixew_stowage_depth)(
			stwuct twansfowm *xfm,
			enum wb_pixew_depth depth,
			const stwuct bit_depth_weduction_pawams *bit_depth_pawams);

	boow (*twansfowm_get_optimaw_numbew_of_taps)(
			stwuct twansfowm *xfm,
			stwuct scawew_data *scw_data,
			const stwuct scawing_taps *in_taps);

	void (*twansfowm_set_gamut_wemap)(
			stwuct twansfowm *xfm,
			const stwuct xfm_gwph_csc_adjustment *adjust);

	void (*opp_set_csc_defauwt)(
		stwuct twansfowm *xfm,
		const stwuct defauwt_adjustment *defauwt_adjust);

	void (*opp_set_csc_adjustment)(
		stwuct twansfowm *xfm,
		const stwuct out_csc_cowow_matwix *tbw_entwy);

	void (*opp_powew_on_wegamma_wut)(
		stwuct twansfowm *xfm,
		boow powew_on);

	void (*opp_pwogwam_wegamma_wut)(
			stwuct twansfowm *xfm,
			const stwuct pww_wesuwt_data *wgb,
			uint32_t num);

	void (*opp_configuwe_wegamma_wut)(
			stwuct twansfowm *xfm,
			boow is_wam_a);

	void (*opp_pwogwam_wegamma_wutb_settings)(
			stwuct twansfowm *xfm,
			const stwuct pww_pawams *pawams);

	void (*opp_pwogwam_wegamma_wuta_settings)(
			stwuct twansfowm *xfm,
			const stwuct pww_pawams *pawams);

	void (*opp_pwogwam_wegamma_pww)(
		stwuct twansfowm *xfm, const stwuct pww_pawams *pawams);

	void (*opp_set_wegamma_mode)(
			stwuct twansfowm *xfm_base,
			enum opp_wegamma mode);

	void (*ipp_set_degamma)(
			stwuct twansfowm *xfm_base,
			enum ipp_degamma_mode mode);

	void (*ipp_pwogwam_input_wut)(
			stwuct twansfowm *xfm_base,
			const stwuct dc_gamma *gamma);

	void (*ipp_pwogwam_degamma_pww)(stwuct twansfowm *xfm_base,
									 const stwuct pww_pawams *pawams);

	void (*ipp_setup)(
			stwuct twansfowm *xfm_base,
			enum suwface_pixew_fowmat fowmat,
			enum expansion_mode mode,
			stwuct dc_csc_twansfowm input_csc_cowow_matwix,
			enum dc_cowow_space input_cowow_space);

	void (*ipp_fuww_bypass)(stwuct twansfowm *xfm_base);

	void (*set_cuwsow_attwibutes)(
			stwuct twansfowm *xfm_base,
			const stwuct dc_cuwsow_attwibutes *attw);

};

const uint16_t *get_fiwtew_2tap_16p(void);
const uint16_t *get_fiwtew_2tap_64p(void);
const uint16_t *get_fiwtew_3tap_16p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_3tap_64p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_4tap_16p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_4tap_64p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_5tap_64p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_6tap_64p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_7tap_64p(stwuct fixed31_32 watio);
const uint16_t *get_fiwtew_8tap_64p(stwuct fixed31_32 watio);


/* Defines the pixew pwocessing capabiwity of the DSCW */
enum dscw_data_pwocessing_fowmat {
	DSCW_DATA_PWCESSING_FIXED_FOWMAT,	/* The DSCW pwocesses pixew data in fixed fowmat */
	DSCW_DATA_PWCESSING_FWOAT_FOWMAT,	/* The DSCW pwocesses pixew data in fwoat fowmat */
};

/*
 * The DPP capabiwities stwuctuwe contains enumewations to specify the
 * HW pwocessing featuwes and an associated function pointews to
 * pwovide the function intewface that can be ovewwoaded fow impwementations
 * based on diffewent capabiwities
 */
stwuct dpp_caps {
	/* DSCW pwocessing pixew data in fixed ow fwoat fowmat */
	enum dscw_data_pwocessing_fowmat dscw_data_pwoc_fowmat;

	/* max WB pawtitions */
	unsigned int max_wb_pawtitions;

	/* Cawcuwates the numbew of pawtitions in the wine buffew.
	 * The impwementation of this function is ovewwoaded fow
	 * diffewent vewsions of DSCW WB.
	 */
	void (*dscw_cawc_wb_num_pawtitions)(
			const stwuct scawew_data *scw_data,
			enum wb_memowy_config wb_config,
			int *num_pawt_y,
			int *num_pawt_c);
};


#endif
