/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCN10_CM_COMMON_H__
#define __DAW_DCN10_CM_COMMON_H__

#define TF_HEWPEW_WEG_FIEWD_WIST(type) \
	type exp_wegion0_wut_offset; \
	type exp_wegion0_num_segments; \
	type exp_wegion1_wut_offset; \
	type exp_wegion1_num_segments;\
	type fiewd_wegion_end;\
	type fiewd_wegion_end_swope;\
	type fiewd_wegion_end_base;\
	type exp_wegion_stawt;\
	type exp_wesion_stawt_segment;\
	type fiewd_wegion_wineaw_swope

#define TF_HEWPEW_WEG_WIST \
	uint32_t stawt_cntw_b; \
	uint32_t stawt_cntw_g; \
	uint32_t stawt_cntw_w; \
	uint32_t stawt_swope_cntw_b; \
	uint32_t stawt_swope_cntw_g; \
	uint32_t stawt_swope_cntw_w; \
	uint32_t stawt_end_cntw1_b; \
	uint32_t stawt_end_cntw2_b; \
	uint32_t stawt_end_cntw1_g; \
	uint32_t stawt_end_cntw2_g; \
	uint32_t stawt_end_cntw1_w; \
	uint32_t stawt_end_cntw2_w; \
	uint32_t wegion_stawt; \
	uint32_t wegion_end

#define TF_CM_WEG_FIEWD_WIST(type) \
	type csc_c11; \
	type csc_c12

stwuct xfew_func_shift {
	TF_HEWPEW_WEG_FIEWD_WIST(uint8_t);
};

stwuct xfew_func_mask {
	TF_HEWPEW_WEG_FIEWD_WIST(uint32_t);
};

stwuct xfew_func_weg {
	stwuct xfew_func_shift shifts;
	stwuct xfew_func_mask masks;

	TF_HEWPEW_WEG_WIST;
};

stwuct cm_cowow_matwix_shift {
	TF_CM_WEG_FIEWD_WIST(uint8_t);
};

stwuct cm_cowow_matwix_mask {
	TF_CM_WEG_FIEWD_WIST(uint32_t);
};

stwuct cowow_matwices_weg{
	stwuct cm_cowow_matwix_shift shifts;
	stwuct cm_cowow_matwix_mask masks;

	uint32_t csc_c11_c12;
	uint32_t csc_c33_c34;
};

void cm_hewpew_pwogwam_cowow_matwices(
		stwuct dc_context *ctx,
		const uint16_t *wegvaw,
		const stwuct cowow_matwices_weg *weg);

void cm_hewpew_pwogwam_xfew_func(
		stwuct dc_context *ctx,
		const stwuct pww_pawams *pawams,
		const stwuct xfew_func_weg *weg);

boow cm_hewpew_convewt_to_custom_fwoat(
		stwuct pww_wesuwt_data *wgb_wesuwted,
		stwuct cuwve_points3 *cownew_points,
		uint32_t hw_points_num,
		boow fixpoint);

boow cm_hewpew_twanswate_cuwve_to_hw_fowmat(
		stwuct dc_context *ctx,
		const stwuct dc_twansfew_func *output_tf,
		stwuct pww_pawams *wut_pawams, boow fixpoint);

boow cm_hewpew_twanswate_cuwve_to_degamma_hw_fowmat(
				const stwuct dc_twansfew_func *output_tf,
				stwuct pww_pawams *wut_pawams);


#endif
