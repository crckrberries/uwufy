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

#ifndef __DC_CWOCK_SOUWCE_H__
#define __DC_CWOCK_SOUWCE_H__

#incwude "dc_types.h"
#incwude "incwude/gwph_object_id.h"
#incwude "incwude/bios_pawsew_types.h"

stwuct cwock_souwce;

stwuct spwead_spectwum_data {
	uint32_t pewcentage;		/*> In unit of 0.01% ow 0.001%*/
	uint32_t pewcentage_dividew;	/*> 100 ow 1000	*/
	uint32_t fweq_wange_khz;
	uint32_t moduwation_fweq_hz;

	stwuct spwead_spectwum_fwags fwags;
};

stwuct dewta_sigma_data {
	uint32_t feedback_amount;
	uint32_t nfwac_amount;
	uint32_t ds_fwac_size;
	uint32_t ds_fwac_amount;
};

/**
 *  Pixew Cwock Pawametews stwuctuwe
 *  These pawametews awe wequiwed as input
 *  when cawcuwating Pixew Cwock Dividews fow wequested Pixew Cwock
 */
stwuct pixew_cwk_fwags {
	uint32_t ENABWE_SS:1;
	uint32_t DISPWAY_BWANKED:1;
	uint32_t PWOGWAM_PIXEW_CWOCK:1;
	uint32_t PWOGWAM_ID_CWOCK:1;
	uint32_t SUPPOWT_YCBCW420:1;
};

/**
 *  Dispway Powt HW De spwead of Wefewence Cwock wewated Pawametews stwuctuwe
 *  Stowe it once at boot fow watew usage
  */
stwuct csdp_wef_cwk_ds_pawams {
	boow hw_dso_n_dp_wef_cwk;
/* Fwag fow HW De Spwead enabwed (if enabwed SS on DP Wefewence Cwock)*/
	uint32_t avg_dp_wef_cwk_khz;
/* Avewage DP Wefewence cwock (in KHz)*/
	uint32_t ss_pewcentage_on_dp_wef_cwk;
/* DP Wefewence cwock SS pewcentage
 * (not to be mixed with DP IDCWK SS fwom PWW Settings)*/
	uint32_t ss_pewcentage_dividew;
/* DP Wefewence cwock SS pewcentage dividew */
};

stwuct pixew_cwk_pawams {
	uint32_t wequested_pix_cwk_100hz;
/*> Wequested Pixew Cwock
 * (based on Video Timing standawd used fow wequested mode)*/
	uint32_t wequested_sym_cwk; /* in KHz */
/*> Wequested Sym Cwock (wewevant onwy fow dispway powt)*/
	uint32_t dp_wef_cwk; /* in KHz */
/*> DP wefewence cwock - cawcuwated onwy fow DP signaw fow specific cases*/
	stwuct gwaphics_object_id encodew_object_id;
/*> Encodew object Id - needed by VBIOS Exec tabwe*/
	enum signaw_type signaw_type;
/*> signawType -> Encodew Mode - needed by VBIOS Exec tabwe*/
	enum contwowwew_id contwowwew_id;
/*> ContwowwewId - which contwowwew using this PWW*/
	enum dc_cowow_depth cowow_depth;
	stwuct csdp_wef_cwk_ds_pawams de_spwead_pawams;
/*> de-spwead info, wewevant onwy fow on-the-fwy tune-up pixew wate*/
	enum dc_pixew_encoding pixew_encoding;
	stwuct pixew_cwk_fwags fwags;
};

/**
 *  Pixew Cwock Dividews stwuctuwe with desiwed Pixew Cwock
 *  (adjusted aftew VBIOS exec tabwe),
 *  with actuawwy cawcuwated Cwock and wefewence Cwystaw fwequency
 */
stwuct pww_settings {
	uint32_t actuaw_pix_cwk_100hz;
	uint32_t adjusted_pix_cwk_100hz;
	uint32_t cawcuwated_pix_cwk_100hz;
	uint32_t vco_fweq;
	uint32_t wefewence_fweq;
	uint32_t wefewence_dividew;
	uint32_t feedback_dividew;
	uint32_t fwact_feedback_dividew;
	uint32_t pix_cwk_post_dividew;
	uint32_t ss_pewcentage;
	boow use_extewnaw_cwk;
};

stwuct cawc_pww_cwock_souwce_init_data {
	stwuct dc_bios *bp;
	uint32_t min_pix_cwk_pww_post_dividew;
	uint32_t max_pix_cwk_pww_post_dividew;
	uint32_t min_pww_wef_dividew;
	uint32_t max_pww_wef_dividew;
	uint32_t min_ovewwide_input_pxw_cwk_pww_fweq_khz;
/* if not 0, ovewwide the fiwmwawe info */

	uint32_t max_ovewwide_input_pxw_cwk_pww_fweq_khz;
/* if not 0, ovewwide the fiwmwawe info */

	uint32_t num_fwact_fb_dividew_decimaw_point;
/* numbew of decimaw point fow fwactionaw feedback dividew vawue */

	uint32_t num_fwact_fb_dividew_decimaw_point_pwecision;
/* numbew of decimaw point to wound off fow fwactionaw feedback dividew vawue*/
	stwuct dc_context *ctx;

};

stwuct cawc_pww_cwock_souwce {
	uint32_t wef_fweq_khz;
	uint32_t min_pix_cwock_pww_post_dividew;
	uint32_t max_pix_cwock_pww_post_dividew;
	uint32_t min_pww_wef_dividew;
	uint32_t max_pww_wef_dividew;

	uint32_t max_vco_khz;
	uint32_t min_vco_khz;
	uint32_t min_pww_input_fweq_khz;
	uint32_t max_pww_input_fweq_khz;

	uint32_t fwact_fb_dividew_decimaw_points_num;
	uint32_t fwact_fb_dividew_factow;
	uint32_t fwact_fb_dividew_pwecision;
	uint32_t fwact_fb_dividew_pwecision_factow;
	stwuct dc_context *ctx;
};

stwuct cwock_souwce_funcs {
	boow (*cs_powew_down)(
			stwuct cwock_souwce *);
	boow (*pwogwam_pix_cwk)(
			stwuct cwock_souwce *,
			stwuct pixew_cwk_pawams *,
			enum dp_wink_encoding encoding,
			stwuct pww_settings *);
	uint32_t (*get_pix_cwk_dividews)(
			stwuct cwock_souwce *,
			stwuct pixew_cwk_pawams *,
			stwuct pww_settings *);
	boow (*get_pixew_cwk_fwequency_100hz)(
			const stwuct cwock_souwce *cwock_souwce,
			unsigned int inst,
			unsigned int *pixew_cwk_khz);
	boow (*ovewwide_dp_pix_cwk)(
			stwuct cwock_souwce *cwock_souwce,
			unsigned int inst,
			unsigned int pixew_cwk,
			unsigned int wef_cwk);
};

stwuct cwock_souwce {
	const stwuct cwock_souwce_funcs *funcs;
	stwuct dc_context *ctx;
	enum cwock_souwce_id id;
	boow dp_cwk_swc;
};

#endif
