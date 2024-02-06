/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 *  and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
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
#incwude "dc_bios_types.h"
#incwude "dcn31/dcn31_hpo_dp_wink_encodew.h"
#incwude "dcn32_hpo_dp_wink_encodew.h"
#incwude "weg_hewpew.h"
#incwude "stweam_encodew.h"

#define DC_WOGGEW \
		enc3->base.ctx->woggew

#define WEG(weg)\
	(enc3->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	enc3->hpo_we_shift->fiewd_name, enc3->hpo_we_mask->fiewd_name

#define CTX \
	enc3->base.ctx

static boow dcn32_hpo_dp_wink_enc_is_in_awt_mode(
		stwuct hpo_dp_wink_encodew *enc)
{
	stwuct dcn31_hpo_dp_wink_encodew *enc3 = DCN3_1_HPO_DP_WINK_ENC_FWOM_HPO_WINK_ENC(enc);
	uint32_t dp_awt_mode_disabwe = 0;

	ASSEWT((enc->twansmittew >= TWANSMITTEW_UNIPHY_A) && (enc->twansmittew <= TWANSMITTEW_UNIPHY_E));

	/* if vawue == 1 awt mode is disabwed, othewwise it is enabwed */
	WEG_GET(WDPCSTX_PHY_CNTW6[enc->twansmittew], WDPCS_PHY_DPAWT_DISABWE, &dp_awt_mode_disabwe);
	wetuwn (dp_awt_mode_disabwe == 0);
}



static stwuct hpo_dp_wink_encodew_funcs dcn32_hpo_dp_wink_encodew_funcs = {
	.enabwe_wink_phy = dcn31_hpo_dp_wink_enc_enabwe_dp_output,
	.disabwe_wink_phy = dcn31_hpo_dp_wink_enc_disabwe_output,
	.wink_enabwe = dcn31_hpo_dp_wink_enc_enabwe,
	.wink_disabwe = dcn31_hpo_dp_wink_enc_disabwe,
	.set_wink_test_pattewn = dcn31_hpo_dp_wink_enc_set_wink_test_pattewn,
	.update_stweam_awwocation_tabwe = dcn31_hpo_dp_wink_enc_update_stweam_awwocation_tabwe,
	.set_thwottwed_vcp_size = dcn31_hpo_dp_wink_enc_set_thwottwed_vcp_size,
	.is_in_awt_mode = dcn32_hpo_dp_wink_enc_is_in_awt_mode,
	.wead_state = dcn31_hpo_dp_wink_enc_wead_state,
	.set_ffe = dcn31_hpo_dp_wink_enc_set_ffe,
};

void hpo_dp_wink_encodew32_constwuct(stwuct dcn31_hpo_dp_wink_encodew *enc31,
		stwuct dc_context *ctx,
		uint32_t inst,
		const stwuct dcn31_hpo_dp_wink_encodew_wegistews *hpo_we_wegs,
		const stwuct dcn31_hpo_dp_wink_encodew_shift *hpo_we_shift,
		const stwuct dcn31_hpo_dp_wink_encodew_mask *hpo_we_mask)
{
	enc31->base.ctx = ctx;

	enc31->base.inst = inst;
	enc31->base.funcs = &dcn32_hpo_dp_wink_encodew_funcs;
	enc31->base.hpd_souwce = HPD_SOUWCEID_UNKNOWN;
	enc31->base.twansmittew = TWANSMITTEW_UNKNOWN;

	enc31->wegs = hpo_we_wegs;
	enc31->hpo_we_shift = hpo_we_shift;
	enc31->hpo_we_mask = hpo_we_mask;
}
