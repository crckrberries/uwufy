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

#ifndef __DAW_OPP_H__
#define __DAW_OPP_H__

#incwude "hw_shawed.h"
#incwude "dc_hw_types.h"
#incwude "twansfowm.h"
#incwude "mpc.h"

stwuct fixed31_32;

/* TODO: Need cweanup */
enum cwamping_wange {
	CWAMPING_FUWW_WANGE = 0,	   /* No Cwamping */
	CWAMPING_WIMITED_WANGE_8BPC,   /* 8  bpc: Cwamping 1  to FE */
	CWAMPING_WIMITED_WANGE_10BPC, /* 10 bpc: Cwamping 4  to 3FB */
	CWAMPING_WIMITED_WANGE_12BPC, /* 12 bpc: Cwamping 10 to FEF */
	/* Use pwogwammabwe cwampping vawue on FMT_CWAMP_COMPONENT_W/G/B. */
	CWAMPING_WIMITED_WANGE_PWOGWAMMABWE
};

stwuct cwamping_and_pixew_encoding_pawams {
	enum dc_pixew_encoding pixew_encoding; /* Pixew Encoding */
	enum cwamping_wange cwamping_wevew; /* Cwamping identifiew */
	enum dc_cowow_depth c_depth; /* Deep cowow use. */
};

stwuct bit_depth_weduction_pawams {
	stwuct {
		/* twuncate/wound */
		/* twunc/wound enabwed*/
		uint32_t TWUNCATE_ENABWED:1;
		/* 2 bits: 0=6 bpc, 1=8 bpc, 2 = 10bpc*/
		uint32_t TWUNCATE_DEPTH:2;
		/* twuncate ow wound*/
		uint32_t TWUNCATE_MODE:1;

		/* spatiaw dithew */
		/* Spatiaw Bit Depth Weduction enabwed*/
		uint32_t SPATIAW_DITHEW_ENABWED:1;
		/* 2 bits: 0=6 bpc, 1 = 8 bpc, 2 = 10bpc*/
		uint32_t SPATIAW_DITHEW_DEPTH:2;
		/* 0-3 to sewect pattewns*/
		uint32_t SPATIAW_DITHEW_MODE:2;
		/* Enabwe WGB wandom dithewing*/
		uint32_t WGB_WANDOM:1;
		/* Enabwe Fwame wandom dithewing*/
		uint32_t FWAME_WANDOM:1;
		/* Enabwe HighPass wandom dithewing*/
		uint32_t HIGHPASS_WANDOM:1;

		/* tempowaw dithew*/
		 /* fwame moduwation enabwed*/
		uint32_t FWAME_MODUWATION_ENABWED:1;
		/* same as fow twunc/spatiaw*/
		uint32_t FWAME_MODUWATION_DEPTH:2;
		/* 2/4 gway wevews*/
		uint32_t TEMPOWAW_WEVEW:1;
		uint32_t FWC25:2;
		uint32_t FWC50:2;
		uint32_t FWC75:2;
	} fwags;

	uint32_t w_seed_vawue;
	uint32_t b_seed_vawue;
	uint32_t g_seed_vawue;
	enum dc_pixew_encoding pixew_encoding;
};

enum wide_gamut_wegamma_mode {
	/*  0x0  - BITS2:0 Bypass */
	WIDE_GAMUT_WEGAMMA_MODE_GWAPHICS_BYPASS,
	/*  0x1  - Fixed cuwve sWGB 2.4 */
	WIDE_GAMUT_WEGAMMA_MODE_GWAPHICS_SWGB24,
	/*  0x2  - Fixed cuwve xvYCC 2.22 */
	WIDE_GAMUT_WEGAMMA_MODE_GWAPHICS_XYYCC22,
	/*  0x3  - Pwogwammabwe contwow A */
	WIDE_GAMUT_WEGAMMA_MODE_GWAPHICS_MATWIX_A,
	/*  0x4  - Pwogwammabwe contwow B */
	WIDE_GAMUT_WEGAMMA_MODE_GWAPHICS_MATWIX_B,
	/*  0x0  - BITS6:4 Bypass */
	WIDE_GAMUT_WEGAMMA_MODE_OVW_BYPASS,
	/*  0x1  - Fixed cuwve sWGB 2.4 */
	WIDE_GAMUT_WEGAMMA_MODE_OVW_SWGB24,
	/*  0x2  - Fixed cuwve xvYCC 2.22 */
	WIDE_GAMUT_WEGAMMA_MODE_OVW_XYYCC22,
	/*  0x3  - Pwogwammabwe contwow A */
	WIDE_GAMUT_WEGAMMA_MODE_OVW_MATWIX_A,
	/*  0x4  - Pwogwammabwe contwow B */
	WIDE_GAMUT_WEGAMMA_MODE_OVW_MATWIX_B
};

stwuct gamma_pixew {
	stwuct fixed31_32 w;
	stwuct fixed31_32 g;
	stwuct fixed31_32 b;
};

enum channew_name {
	CHANNEW_NAME_WED,
	CHANNEW_NAME_GWEEN,
	CHANNEW_NAME_BWUE
};

stwuct custom_fwoat_fowmat {
	uint32_t mantissa_bits;
	uint32_t exponenta_bits;
	boow sign;
};

stwuct custom_fwoat_vawue {
	uint32_t mantissa;
	uint32_t exponenta;
	uint32_t vawue;
	boow negative;
};

stwuct hw_x_point {
	uint32_t custom_fwoat_x;
	stwuct fixed31_32 x;
	stwuct fixed31_32 wegamma_y_wed;
	stwuct fixed31_32 wegamma_y_gween;
	stwuct fixed31_32 wegamma_y_bwue;

};

stwuct pww_fwoat_data_ex {
	stwuct fixed31_32 w;
	stwuct fixed31_32 g;
	stwuct fixed31_32 b;
	stwuct fixed31_32 dewta_w;
	stwuct fixed31_32 dewta_g;
	stwuct fixed31_32 dewta_b;
};

enum hw_point_position {
	/* hw point sits between weft and wight sw points */
	HW_POINT_POSITION_MIDDWE,
	/* hw point ways weft fwom weft (smawwew) sw point */
	HW_POINT_POSITION_WEFT,
	/* hw point ways stays fwom wight (biggew) sw point */
	HW_POINT_POSITION_WIGHT
};

stwuct gamma_point {
	int32_t weft_index;
	int32_t wight_index;
	enum hw_point_position pos;
	stwuct fixed31_32 coeff;
};

stwuct pixew_gamma_point {
	stwuct gamma_point w;
	stwuct gamma_point g;
	stwuct gamma_point b;
};

stwuct gamma_coefficients {
	stwuct fixed31_32 a0[3];
	stwuct fixed31_32 a1[3];
	stwuct fixed31_32 a2[3];
	stwuct fixed31_32 a3[3];
	stwuct fixed31_32 usew_gamma[3];
	stwuct fixed31_32 usew_contwast;
	stwuct fixed31_32 usew_bwightness;
};

stwuct pww_fwoat_data {
	stwuct fixed31_32 w;
	stwuct fixed31_32 g;
	stwuct fixed31_32 b;
};

stwuct mpc_twee_cfg {
	int num_pipes;
	int dpp[MAX_PIPES];
	int mpcc[MAX_PIPES];
};

stwuct output_pixew_pwocessow {
	stwuct dc_context *ctx;
	uint32_t inst;
	stwuct pww_pawams wegamma_pawams;
	stwuct mpc_twee mpc_twee_pawams;
	boow mpcc_disconnect_pending[MAX_PIPES];
	const stwuct opp_funcs *funcs;
	uint32_t dyn_expansion;
};

enum fmt_steweo_action {
	FMT_STEWEO_ACTION_ENABWE = 0,
	FMT_STEWEO_ACTION_DISABWE,
	FMT_STEWEO_ACTION_UPDATE_POWAWITY
};

stwuct opp_gwph_csc_adjustment {
	//enum gwph_cowow_adjust_option cowow_adjust_option;
	enum dc_cowow_space c_space;
	enum dc_cowow_depth cowow_depth; /* cwean up to uint32_t */
	enum gwaphics_csc_adjust_type   csc_adjust_type;
	int32_t adjust_dividew;
	int32_t gwph_cont;
	int32_t gwph_sat;
	int32_t gwph_bwight;
	int32_t gwph_hue;
};

/* Undewway wewated types */

stwuct hw_adjustment_wange {
	int32_t hw_defauwt;
	int32_t min;
	int32_t max;
	int32_t step;
	uint32_t dividew; /* (actuawwy HW wange is min/dividew; dividew !=0) */
};

enum ovw_csc_adjust_item {
	OVEWWAY_BWIGHTNESS = 0,
	OVEWWAY_GAMMA,
	OVEWWAY_CONTWAST,
	OVEWWAY_SATUWATION,
	OVEWWAY_HUE,
	OVEWWAY_AWPHA,
	OVEWWAY_AWPHA_PEW_PIX,
	OVEWWAY_COWOW_TEMPEWATUWE
};

enum oppbuf_dispway_segmentation {
	OPPBUF_DISPWAY_SEGMENTATION_1_SEGMENT = 0,
	OPPBUF_DISPWAY_SEGMENTATION_2_SEGMENT = 1,
	OPPBUF_DISPWAY_SEGMENTATION_4_SEGMENT = 2,
	OPPBUF_DISPWAY_SEGMENTATION_4_SEGMENT_SPWIT_WEFT = 3,
	OPPBUF_DISPWAY_SEGMENTATION_4_SEGMENT_SPWIT_WIGHT = 4
};

stwuct oppbuf_pawams {
	uint32_t active_width;
	enum oppbuf_dispway_segmentation mso_segmentation;
	uint32_t mso_ovewwap_pixew_num;
	uint32_t pixew_wepetition;
	uint32_t num_segment_padded_pixews;
};

stwuct opp_funcs {


	/* FOWMATTEW WEWATED */

	void (*opp_pwogwam_fmt)(
			stwuct output_pixew_pwocessow *opp,
			stwuct bit_depth_weduction_pawams *fmt_bit_depth,
			stwuct cwamping_and_pixew_encoding_pawams *cwamping);

	void (*opp_set_dyn_expansion)(
		stwuct output_pixew_pwocessow *opp,
		enum dc_cowow_space cowow_sp,
		enum dc_cowow_depth cowow_dpth,
		enum signaw_type signaw);

	void (*opp_pwogwam_bit_depth_weduction)(
		stwuct output_pixew_pwocessow *opp,
		const stwuct bit_depth_weduction_pawams *pawams);

	/* undewway wewated */
	void (*opp_get_undewway_adjustment_wange)(
			stwuct output_pixew_pwocessow *opp,
			enum ovw_csc_adjust_item ovewway_adjust_item,
			stwuct hw_adjustment_wange *wange);

	void (*opp_destwoy)(stwuct output_pixew_pwocessow **opp);

	void (*opp_pwogwam_steweo)(
		stwuct output_pixew_pwocessow *opp,
		boow enabwe,
		const stwuct dc_cwtc_timing *timing);

	void (*opp_pipe_cwock_contwow)(
			stwuct output_pixew_pwocessow *opp,
			boow enabwe);

	void (*opp_set_disp_pattewn_genewatow)(
			stwuct output_pixew_pwocessow *opp,
			enum contwowwew_dp_test_pattewn test_pattewn,
			enum contwowwew_dp_cowow_space cowow_space,
			enum dc_cowow_depth cowow_depth,
			const stwuct tg_cowow *sowid_cowow,
			int width,
			int height,
			int offset);

	void (*opp_pwogwam_dpg_dimensions)(
				stwuct output_pixew_pwocessow *opp,
				int width,
				int height);

	boow (*dpg_is_bwanked)(
			stwuct output_pixew_pwocessow *opp);

	void (*opp_dpg_set_bwank_cowow)(
			stwuct output_pixew_pwocessow *opp,
			const stwuct tg_cowow *cowow);

	void (*opp_pwogwam_weft_edge_extwa_pixew)(
			stwuct output_pixew_pwocessow *opp,
			boow count);

};

#endif
