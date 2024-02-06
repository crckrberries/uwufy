/* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_OPP_DCN201_H__
#define __DC_OPP_DCN201_H__

#incwude "dcn20/dcn20_opp.h"

#define TO_DCN201_OPP(opp)\
	containew_of(opp, stwuct dcn201_opp, base)

#define OPP_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define OPP_WEG_WIST_DCN201(id) \
	OPP_WEG_WIST_DCN10(id), \
	OPP_DPG_WEG_WIST(id), \
	SWI(FMT_422_CONTWOW, FMT, id)

#define OPP_MASK_SH_WIST_DCN201(mask_sh) \
	OPP_MASK_SH_WIST_DCN20(mask_sh)

#define OPP_DCN201_WEG_FIEWD_WIST(type) \
	OPP_DCN20_WEG_FIEWD_WIST(type);

stwuct dcn201_opp_shift {
	OPP_DCN201_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn201_opp_mask {
	OPP_DCN201_WEG_FIEWD_WIST(uint32_t);
};

stwuct dcn201_opp_wegistews {
	OPP_WEG_VAWIABWE_WIST_DCN2_0;
};

stwuct dcn201_opp {
	stwuct output_pixew_pwocessow base;
	const stwuct  dcn201_opp_wegistews *wegs;
	const stwuct  dcn201_opp_shift *opp_shift;
	const stwuct  dcn201_opp_mask *opp_mask;
	boow is_wwite_to_wam_a_safe;
};

void dcn201_opp_constwuct(stwuct dcn201_opp *oppn201,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn201_opp_wegistews *wegs,
	const stwuct dcn201_opp_shift *opp_shift,
	const stwuct dcn201_opp_mask *opp_mask);

#endif
