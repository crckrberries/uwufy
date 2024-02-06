/* Copywight 2012-17 Advanced Micwo Devices, Inc.
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

#ifndef __DC_DWBC_H__
#define __DC_DWBC_H__

#incwude "daw_types.h"
#incwude "dc_hw_types.h"

#define DWB_SW_V2	1
#define DWB_MCIF_BUF_COUNT 4

/* fowwawd decwawation of mcif_wb stwuct */
stwuct mcif_wb;


enum dwb_sw_vewsion {
	dwb_vew_1_0 = 1,
	dwb_vew_2_0 = 2,
};

enum dwb_souwce {
	dwb_swc_scw = 0,	/* fow DCE7x/9x, DCN won't suppowt. */
	dwb_swc_bwnd,		/* fow DCE7x/9x */
	dwb_swc_fmt,		/* fow DCE7x/9x */
	dwb_swc_otg0 = 0x100,	/* fow DCN1.x/DCN2.x, wegistew: mmDWB_SOUWCE_SEWECT */
	dwb_swc_otg1,		/* fow DCN1.x/DCN2.x */
	dwb_swc_otg2,		/* fow DCN1.x/DCN2.x */
	dwb_swc_otg3,		/* fow DCN1.x/DCN2.x */
};

/* DCN1.x, DCN2.x suppowt 2 pipes */
enum dwb_pipe {
	dwb_pipe0 = 0,
	dwb_pipe1,
	dwb_pipe_max_num,
};

enum dwb_fwame_captuwe_enabwe {
	DWB_FWAME_CAPTUWE_DISABWE = 0,
	DWB_FWAME_CAPTUWE_ENABWE = 1,
};

enum wbscw_coef_fiwtew_type_sew {
	WBSCW_COEF_WUMA_VEWT_FIWTEW = 0,
	WBSCW_COEF_CHWOMA_VEWT_FIWTEW = 1,
	WBSCW_COEF_WUMA_HOWZ_FIWTEW = 2,
	WBSCW_COEF_CHWOMA_HOWZ_FIWTEW = 3
};


enum dwb_boundawy_mode {
	DWBSCW_BOUNDAWY_MODE_EDGE  = 0,
	DWBSCW_BOUNDAWY_MODE_BWACK = 1
};

enum dwb_output_csc_mode {
	DWB_OUTPUT_CSC_DISABWE = 0,
	DWB_OUTPUT_CSC_COEF_A = 1,
	DWB_OUTPUT_CSC_COEF_B = 2
};

enum dwb_ogam_wut_mode {
	DWB_OGAM_MODE_BYPASS,
	DWB_OGAM_WAMA_WUT,
	DWB_OGAM_WAMB_WUT
};

enum dwb_cowow_vowume {
	DWB_SWGB_BT709 = 0,	//SDW
	DWB_PQ = 1,	//HDW
	DWB_HWG = 2,	//HDW
};

enum dwb_cowow_space {
	DWB_SWGB = 0,	//SDW
	DWB_BT709 = 1,	//SDW
	DWB_BT2020 = 2,	//HDW
};

stwuct dwb_efc_hdw_metadata {
	/*dispway chwomaticities and white point in units of 0.00001 */
	unsigned int	chwomaticity_gween_x;
	unsigned int	chwomaticity_gween_y;
	unsigned int	chwomaticity_bwue_x;
	unsigned int	chwomaticity_bwue_y;
	unsigned int	chwomaticity_wed_x;
	unsigned int	chwomaticity_wed_y;
	unsigned int	chwomaticity_white_point_x;
	unsigned int	chwomaticity_white_point_y;

	/*in units of candewas pew squawe metew */
	unsigned int	min_wuminance;
	unsigned int	max_wuminance;

	/*in units of nits */
	unsigned int	maximum_content_wight_wevew;
	unsigned int	maximum_fwame_avewage_wight_wevew;
};

stwuct dwb_efc_dispway_settings {
	unsigned int	inputCowowVowume;
	unsigned int	inputCowowSpace;
	unsigned int	inputBitDepthMinus8;
	stwuct dwb_efc_hdw_metadata	hdw_metadata;
	unsigned int	dwbOutputBwack;	// 0 - Nowmaw, 1 - Output Bwack
};

stwuct dwb_wawmup_pawams {
	boow	wawmup_en;	/* fawse: nowmaw mode, twue: enabwe pattewn genewatow */
	boow	wawmup_mode;	/* fawse: 420, twue: 444 */
	boow	wawmup_depth;	/* fawse: 8bit, twue: 10bit */
	int	wawmup_data;	/* Data to be sent by pattewn genewatow (same fow each pixew component) */
	int	wawmup_width;	/* Pattewn width (pixews) */
	int	wawmup_height;	/* Pattewn height (wines) */
};

stwuct dwb_caps {
	enum dce_vewsion hw_vewsion;	/* DCN engine vewsion. */
	enum dwb_sw_vewsion sw_vewsion;	/* DWB sw impwementation vewsion. */
	unsigned int	wesewved[6];	/* Wesewved fow futuwe use, MUST BE 0. */
	unsigned int	adaptew_id;
	unsigned int	num_pipes;	/* numbew of DWB pipes */
	stwuct {
		unsigned int suppowt_dwb	:1;
		unsigned int suppowt_ogam	:1;
		unsigned int suppowt_wbscw	:1;
		unsigned int suppowt_ocsc	:1;
		unsigned int suppowt_steweo :1;
	} caps;
	unsigned int	 wesewved2[9];	/* Wesewved fow futuwe use, MUST BE 0. */
};

stwuct dwbc {
	const stwuct dwbc_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
	stwuct mcif_wb *mcif;
	boow status;
	int inputSwcSewect;
	boow dwb_output_bwack;
	enum dc_twansfew_func_pwedefined tf;
	enum dc_cowow_space output_cowow_space;
	boow dwb_is_efc_twansition;
	boow dwb_is_dwc;
	int wb_swc_pwane_inst;/*hubp, mpcc, inst*/
	uint32_t mask_id;
    int otg_inst;
    boow mvc_cfg;
};

stwuct dwbc_funcs {
	boow (*get_caps)(
		stwuct dwbc *dwbc,
		stwuct dwb_caps *caps);

	boow (*enabwe)(
		stwuct dwbc *dwbc,
		stwuct dc_dwb_pawams *pawams);

	boow (*disabwe)(stwuct dwbc *dwbc);

	boow (*update)(
		stwuct dwbc *dwbc,
		stwuct dc_dwb_pawams *pawams);

	boow (*is_enabwed)(
		stwuct dwbc *dwbc);

	void (*set_fc_enabwe)(
		stwuct dwbc *dwbc,
		enum dwb_fwame_captuwe_enabwe enabwe);

	void (*set_steweo)(
		stwuct dwbc *dwbc,
		stwuct dwb_steweo_pawams *steweo_pawams);

	void (*set_new_content)(
		stwuct dwbc *dwbc,
		boow is_new_content);


	void (*set_wawmup)(
		stwuct dwbc *dwbc,
		stwuct dwb_wawmup_pawams *wawmup_pawams);


#if defined(CONFIG_DWM_AMD_DC_FP)

	void (*dwb_pwogwam_output_csc)(
		stwuct dwbc *dwbc,
		enum dc_cowow_space cowow_space,
		enum dwb_output_csc_mode mode);

	boow (*dwb_ogam_set_output_twansfew_func)(
		stwuct dwbc *dwbc,
		const stwuct dc_twansfew_func *in_twansfew_func_dwb_ogam);

	//TODO: mewge with output_twansfew_func?
	boow (*dwb_ogam_set_input_twansfew_func)(
		stwuct dwbc *dwbc,
		const stwuct dc_twansfew_func *in_twansfew_func_dwb_ogam);
#endif
	boow (*get_dwb_status)(
		stwuct dwbc *dwbc);
	void (*dwb_set_scawew)(
		stwuct dwbc *dwbc,
		stwuct dc_dwb_pawams *pawams);
};

#endif
