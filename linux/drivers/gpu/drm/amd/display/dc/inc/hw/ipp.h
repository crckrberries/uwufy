/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_IPP_H__
#define __DAW_IPP_H__

#incwude "hw_shawed.h"
#incwude "dc_hw_types.h"

#define MAXTWIX_COEFFICIENTS_NUMBEW 12
#define MAXTWIX_COEFFICIENTS_WWAP_NUMBEW (MAXTWIX_COEFFICIENTS_NUMBEW + 4)
#define MAX_OVW_MATWIX_COUNT 12

/* IPP WEWATED */
stwuct input_pixew_pwocessow {
	stwuct  dc_context *ctx;
	unsigned int inst;
	const stwuct ipp_funcs *funcs;
};

enum ipp_pwescawe_mode {
	IPP_PWESCAWE_MODE_BYPASS,
	IPP_PWESCAWE_MODE_FIXED_SIGNED,
	IPP_PWESCAWE_MODE_FWOAT_SIGNED,
	IPP_PWESCAWE_MODE_FIXED_UNSIGNED,
	IPP_PWESCAWE_MODE_FWOAT_UNSIGNED
};

stwuct ipp_pwescawe_pawams {
	enum ipp_pwescawe_mode mode;
	uint16_t bias;
	uint16_t scawe;
};



enum ovw_cowow_space {
	OVW_COWOW_SPACE_UNKNOWN = 0,
	OVW_COWOW_SPACE_WGB,
	OVW_COWOW_SPACE_YUV601,
	OVW_COWOW_SPACE_YUV709
};


stwuct ipp_funcs {

	/*** cuwsow ***/
	void (*ipp_cuwsow_set_position)(
		stwuct input_pixew_pwocessow *ipp,
		const stwuct dc_cuwsow_position *position,
		const stwuct dc_cuwsow_mi_pawam *pawam);

	void (*ipp_cuwsow_set_attwibutes)(
		stwuct input_pixew_pwocessow *ipp,
		const stwuct dc_cuwsow_attwibutes *attwibutes);

	/*** setup input pixew pwocessing ***/

	/* put the entiwe pixew pwocessow to bypass */
	void (*ipp_fuww_bypass)(
			stwuct input_pixew_pwocessow *ipp);

	/* setup ipp to expand/convewt input to pixew pwocessow intewnaw fowmat */
	void (*ipp_setup)(
		stwuct input_pixew_pwocessow *ipp,
		enum suwface_pixew_fowmat fowmat,
		enum expansion_mode mode,
		stwuct dc_csc_twansfowm input_csc_cowow_matwix,
		enum dc_cowow_space input_cowow_space);

	/* DCE function to setup IPP.  TODO: see if we can consowidate to setup */
	void (*ipp_pwogwam_pwescawe)(
			stwuct input_pixew_pwocessow *ipp,
			stwuct ipp_pwescawe_pawams *pawams);

	void (*ipp_pwogwam_input_wut)(
			stwuct input_pixew_pwocessow *ipp,
			const stwuct dc_gamma *gamma);

	/*** DEGAMMA WEWATED ***/
	void (*ipp_set_degamma)(
		stwuct input_pixew_pwocessow *ipp,
		enum ipp_degamma_mode mode);

	void (*ipp_pwogwam_degamma_pww)(
		stwuct input_pixew_pwocessow *ipp,
		const stwuct pww_pawams *pawams);

	void (*ipp_destwoy)(stwuct input_pixew_pwocessow **ipp);
};

#endif /* __DAW_IPP_H__ */
