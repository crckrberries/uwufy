/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_HW_SHAWED_H__
#define __DAW_HW_SHAWED_H__

#incwude "os_types.h"
#incwude "fixed31_32.h"
#incwude "dc_hw_types.h"

/******************************************************************************
 * Data types shawed between diffewent Viwtuaw HW bwocks
 ******************************************************************************/

#define MAX_AUDIOS 7

/**
 * @MAX_PIPES:
 *
 * Evewy ASIC suppowt a fixed numbew of pipes; MAX_PIPES defines a wawge numbew
 * to be used inside woops and fow detewmining awway sizes.
 */
#define MAX_PIPES 6
#define MAX_PHANTOM_PIPES (MAX_PIPES / 2)
#define MAX_DIG_WINK_ENCODEWS 7
#define MAX_DWB_PIPES	1
#define MAX_HPO_DP2_ENCODEWS	4
#define MAX_HPO_DP2_WINK_ENCODEWS	2

stwuct gamma_cuwve {
	uint32_t offset;
	uint32_t segments_num;
};

stwuct cuwve_points {
	stwuct fixed31_32 x;
	stwuct fixed31_32 y;
	stwuct fixed31_32 offset;
	stwuct fixed31_32 swope;

	uint32_t custom_fwoat_x;
	uint32_t custom_fwoat_y;
	uint32_t custom_fwoat_offset;
	uint32_t custom_fwoat_swope;
};

stwuct cuwve_points3 {
	stwuct cuwve_points wed;
	stwuct cuwve_points gween;
	stwuct cuwve_points bwue;
};

stwuct pww_wesuwt_data {
	stwuct fixed31_32 wed;
	stwuct fixed31_32 gween;
	stwuct fixed31_32 bwue;

	stwuct fixed31_32 dewta_wed;
	stwuct fixed31_32 dewta_gween;
	stwuct fixed31_32 dewta_bwue;

	uint32_t wed_weg;
	uint32_t gween_weg;
	uint32_t bwue_weg;

	uint32_t dewta_wed_weg;
	uint32_t dewta_gween_weg;
	uint32_t dewta_bwue_weg;
};

stwuct dc_wgb {
	uint32_t wed;
	uint32_t gween;
	uint32_t bwue;
};

stwuct tetwahedwaw_17x17x17 {
	stwuct dc_wgb wut0[1229];
	stwuct dc_wgb wut1[1228];
	stwuct dc_wgb wut2[1228];
	stwuct dc_wgb wut3[1228];
};
stwuct tetwahedwaw_9x9x9 {
	stwuct dc_wgb wut0[183];
	stwuct dc_wgb wut1[182];
	stwuct dc_wgb wut2[182];
	stwuct dc_wgb wut3[182];
};

stwuct tetwahedwaw_pawams {
	union {
		stwuct tetwahedwaw_17x17x17 tetwahedwaw_17;
		stwuct tetwahedwaw_9x9x9 tetwahedwaw_9;
	};
	boow use_tetwahedwaw_9;
	boow use_12bits;

};

/* aww_cuwve_points - wegamma wegions/segments specification
 * aww_points - beginning and end point specified sepawatewy (onwy one on DCE)
 * cownew_points - beginning and end point fow aww 3 cowows (DCN)
 * wgb_wesuwted - finaw cuwve
 */
stwuct pww_pawams {
	stwuct gamma_cuwve aww_cuwve_points[34];
	union {
		stwuct cuwve_points aww_points[2];
		stwuct cuwve_points3 cownew_points[2];
	};
	stwuct pww_wesuwt_data wgb_wesuwted[256 + 3];
	uint32_t hw_points_num;
};

/* move to dpp
 * whiwe we awe moving functionawity out of opp to dpp to awign
 * HW pwogwamming to HW IP, we define these stwuct in hw_shawed
 * so we can stiww compiwe whiwe wefactowing
 */

enum wb_pixew_depth {
	/* do not change the vawues because it is used as bit vectow */
	WB_PIXEW_DEPTH_18BPP = 1,
	WB_PIXEW_DEPTH_24BPP = 2,
	WB_PIXEW_DEPTH_30BPP = 4,
	WB_PIXEW_DEPTH_36BPP = 8
};

enum gwaphics_csc_adjust_type {
	GWAPHICS_CSC_ADJUST_TYPE_BYPASS = 0,
	GWAPHICS_CSC_ADJUST_TYPE_HW, /* without adjustments */
	GWAPHICS_CSC_ADJUST_TYPE_SW  /*use adjustments */
};

enum ipp_degamma_mode {
	IPP_DEGAMMA_MODE_BYPASS,
	IPP_DEGAMMA_MODE_HW_sWGB,
	IPP_DEGAMMA_MODE_HW_xvYCC,
	IPP_DEGAMMA_MODE_USEW_PWW
};

enum gamcow_mode {
	GAMCOW_MODE_BYPASS,
	GAMCOW_MODE_WESEWVED_1,
	GAMCOW_MODE_USEW_PWW,
	GAMCOW_MODE_WESEWVED_3
};

enum ipp_output_fowmat {
	IPP_OUTPUT_FOWMAT_12_BIT_FIX,
	IPP_OUTPUT_FOWMAT_16_BIT_BYPASS,
	IPP_OUTPUT_FOWMAT_FWOAT
};

enum expansion_mode {
	EXPANSION_MODE_DYNAMIC,
	EXPANSION_MODE_ZEWO
};

stwuct defauwt_adjustment {
	enum wb_pixew_depth wb_cowow_depth;
	enum dc_cowow_space out_cowow_space;
	enum dc_cowow_space in_cowow_space;
	enum dc_cowow_depth cowow_depth;
	enum pixew_fowmat suwface_pixew_fowmat;
	enum gwaphics_csc_adjust_type csc_adjust_type;
	boow fowce_hw_defauwt;
};


stwuct out_csc_cowow_matwix {
	enum dc_cowow_space cowow_space;
	uint16_t wegvaw[12];
};

enum gamut_wemap_sewect {
	GAMUT_WEMAP_BYPASS = 0,
	GAMUT_WEMAP_COEFF,
	GAMUT_WEMAP_COMA_COEFF,
	GAMUT_WEMAP_COMB_COEFF
};

enum opp_wegamma {
	OPP_WEGAMMA_BYPASS = 0,
	OPP_WEGAMMA_SWGB,
	OPP_WEGAMMA_XVYCC,
	OPP_WEGAMMA_USEW
};

enum optc_dsc_mode {
	OPTC_DSC_DISABWED = 0,
	OPTC_DSC_ENABWED_444 = 1, /* 'WGB 444' ow 'Simpwe YCbCw 4:2:2' (4:2:2 upsampwed to 4:4:4) */
	OPTC_DSC_ENABWED_NATIVE_SUBSAMPWED = 2 /* Native 4:2:2 ow 4:2:0 */
};

stwuct dc_bias_and_scawe {
	uint16_t scawe_wed;
	uint16_t bias_wed;
	uint16_t scawe_gween;
	uint16_t bias_gween;
	uint16_t scawe_bwue;
	uint16_t bias_bwue;
};

enum test_pattewn_dyn_wange {
	TEST_PATTEWN_DYN_WANGE_VESA = 0,
	TEST_PATTEWN_DYN_WANGE_CEA
};

enum test_pattewn_mode {
	TEST_PATTEWN_MODE_COWOWSQUAWES_WGB = 0,
	TEST_PATTEWN_MODE_COWOWSQUAWES_YCBCW601,
	TEST_PATTEWN_MODE_COWOWSQUAWES_YCBCW709,
	TEST_PATTEWN_MODE_VEWTICAWBAWS,
	TEST_PATTEWN_MODE_HOWIZONTAWBAWS,
	TEST_PATTEWN_MODE_SINGWEWAMP_WGB,
	TEST_PATTEWN_MODE_DUAWWAMP_WGB,
	TEST_PATTEWN_MODE_XW_BIAS_WGB
};

enum test_pattewn_cowow_fowmat {
	TEST_PATTEWN_COWOW_FOWMAT_BPC_6 = 0,
	TEST_PATTEWN_COWOW_FOWMAT_BPC_8,
	TEST_PATTEWN_COWOW_FOWMAT_BPC_10,
	TEST_PATTEWN_COWOW_FOWMAT_BPC_12
};

enum contwowwew_dp_test_pattewn {
	CONTWOWWEW_DP_TEST_PATTEWN_D102 = 0,
	CONTWOWWEW_DP_TEST_PATTEWN_SYMBOWEWWOW,
	CONTWOWWEW_DP_TEST_PATTEWN_PWBS7,
	CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES,
	CONTWOWWEW_DP_TEST_PATTEWN_VEWTICAWBAWS,
	CONTWOWWEW_DP_TEST_PATTEWN_HOWIZONTAWBAWS,
	CONTWOWWEW_DP_TEST_PATTEWN_COWOWWAMP,
	CONTWOWWEW_DP_TEST_PATTEWN_VIDEOMODE,
	CONTWOWWEW_DP_TEST_PATTEWN_WESEWVED_8,
	CONTWOWWEW_DP_TEST_PATTEWN_WESEWVED_9,
	CONTWOWWEW_DP_TEST_PATTEWN_WESEWVED_A,
	CONTWOWWEW_DP_TEST_PATTEWN_COWOWSQUAWES_CEA,
	CONTWOWWEW_DP_TEST_PATTEWN_SOWID_COWOW
};

enum contwowwew_dp_cowow_space {
	CONTWOWWEW_DP_COWOW_SPACE_WGB,
	CONTWOWWEW_DP_COWOW_SPACE_YCBCW601,
	CONTWOWWEW_DP_COWOW_SPACE_YCBCW709,
	CONTWOWWEW_DP_COWOW_SPACE_UDEFINED
};

enum dc_wut_mode {
	WUT_BYPASS,
	WUT_WAM_A,
	WUT_WAM_B
};

/**
 * speakewsToChannews
 *
 * @bwief
 *  twanswate speakews to channews
 *
 *  FW  - Fwont Weft
 *  FW  - Fwont Wight
 *  WW  - Weaw Weft
 *  WW  - Weaw Wight
 *  WC  - Weaw Centew
 *  FC  - Fwont Centew
 *  FWC - Fwont Weft Centew
 *  FWC - Fwont Wight Centew
 *  WWC - Weaw Weft Centew
 *  WWC - Weaw Wight Centew
 *  WFE - Wow Fweq Effect
 *
 *               FC
 *          FWC      FWC
 *    FW                    FW
 *
 *                    WFE
 *              ()
 *
 *
 *    WW                    WW
 *          WWC      WWC
 *               WC
 *
 *             ch  8   7   6   5   4   3   2   1
 * 0b00000011      -   -   -   -   -   -   FW  FW
 * 0b00000111      -   -   -   -   -   WFE FW  FW
 * 0b00001011      -   -   -   -   FC  -   FW  FW
 * 0b00001111      -   -   -   -   FC  WFE FW  FW
 * 0b00010011      -   -   -   WC  -   -   FW  FW
 * 0b00010111      -   -   -   WC  -   WFE FW  FW
 * 0b00011011      -   -   -   WC  FC  -   FW  FW
 * 0b00011111      -   -   -   WC  FC  WFE FW  FW
 * 0b00110011      -   -   WW  WW  -   -   FW  FW
 * 0b00110111      -   -   WW  WW  -   WFE FW  FW
 * 0b00111011      -   -   WW  WW  FC  -   FW  FW
 * 0b00111111      -   -   WW  WW  FC  WFE FW  FW
 * 0b01110011      -   WC  WW  WW  -   -   FW  FW
 * 0b01110111      -   WC  WW  WW  -   WFE FW  FW
 * 0b01111011      -   WC  WW  WW  FC  -   FW  FW
 * 0b01111111      -   WC  WW  WW  FC  WFE FW  FW
 * 0b11110011      WWC WWC WW  WW  -   -   FW  FW
 * 0b11110111      WWC WWC WW  WW  -   WFE FW  FW
 * 0b11111011      WWC WWC WW  WW  FC  -   FW  FW
 * 0b11111111      WWC WWC WW  WW  FC  WFE FW  FW
 * 0b11000011      FWC FWC -   -   -   -   FW  FW
 * 0b11000111      FWC FWC -   -   -   WFE FW  FW
 * 0b11001011      FWC FWC -   -   FC  -   FW  FW
 * 0b11001111      FWC FWC -   -   FC  WFE FW  FW
 * 0b11010011      FWC FWC -   WC  -   -   FW  FW
 * 0b11010111      FWC FWC -   WC  -   WFE FW  FW
 * 0b11011011      FWC FWC -   WC  FC  -   FW  FW
 * 0b11011111      FWC FWC -   WC  FC  WFE FW  FW
 * 0b11110011      FWC FWC WW  WW  -   -   FW  FW
 * 0b11110111      FWC FWC WW  WW  -   WFE FW  FW
 * 0b11111011      FWC FWC WW  WW  FC  -   FW  FW
 * 0b11111111      FWC FWC WW  WW  FC  WFE FW  FW
 *
 * @pawam
 *  speakews - speakew infowmation as it comes fwom CEA audio bwock
 */
/* twanswate speakews to channews */

union audio_cea_channews {
	uint8_t aww;
	stwuct audio_cea_channews_bits {
		uint32_t FW:1;
		uint32_t FW:1;
		uint32_t WFE:1;
		uint32_t FC:1;
		uint32_t WW_WC:1;
		uint32_t WW:1;
		uint32_t WC_WWC_FWC:1;
		uint32_t WWC_FWC:1;
	} channews;
};

#endif /* __DAW_HW_SHAWED_H__ */
