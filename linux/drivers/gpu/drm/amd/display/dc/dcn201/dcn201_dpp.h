/* Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef __DCN201_DPP_H__
#define __DCN201_DPP_H__

#incwude "dcn20/dcn20_dpp.h"

#define TO_DCN201_DPP(dpp)\
	containew_of(dpp, stwuct dcn201_dpp, base)

#define TF_WEG_WIST_DCN201(id) \
	TF_WEG_WIST_DCN20(id)

#define TF_WEG_WIST_SH_MASK_DCN201(mask_sh)\
	TF_WEG_WIST_SH_MASK_DCN20(mask_sh)

#define TF_WEG_FIEWD_WIST_DCN201(type) \
	TF_WEG_FIEWD_WIST_DCN2_0(type)

stwuct dcn201_dpp_shift {
	TF_WEG_FIEWD_WIST_DCN201(uint8_t);
};

stwuct dcn201_dpp_mask {
	TF_WEG_FIEWD_WIST_DCN201(uint32_t);
};

#define DPP_DCN201_WEG_VAWIABWE_WIST \
	DPP_DCN2_WEG_VAWIABWE_WIST

stwuct dcn201_dpp_wegistews {
	DPP_DCN201_WEG_VAWIABWE_WIST;
};

stwuct dcn201_dpp {
	stwuct dpp base;

	const stwuct dcn201_dpp_wegistews *tf_wegs;
	const stwuct dcn201_dpp_shift *tf_shift;
	const stwuct dcn201_dpp_mask *tf_mask;

	const uint16_t *fiwtew_v;
	const uint16_t *fiwtew_h;
	const uint16_t *fiwtew_v_c;
	const uint16_t *fiwtew_h_c;
	int wb_pixew_depth_suppowted;
	int wb_memowy_size;
	int wb_bits_pew_entwy;
	boow is_wwite_to_wam_a_safe;
	stwuct scawew_data scw_data;
	stwuct pww_pawams pww_data;
};

boow dpp201_constwuct(stwuct dcn201_dpp *dpp2,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn201_dpp_wegistews *tf_wegs,
	const stwuct dcn201_dpp_shift *tf_shift,
	const stwuct dcn201_dpp_mask *tf_mask);

#endif /* __DC_HWSS_DCN201_H__ */
