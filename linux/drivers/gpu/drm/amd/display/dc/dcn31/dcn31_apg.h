/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_DCN31_AGP_H__
#define __DAW_DCN31_AGP_H__


#define DCN31_APG_FWOM_APG(apg)\
	containew_of(apg, stwuct dcn31_apg, base)

#define APG_DCN31_WEG_WIST(id) \
	SWI(APG_CONTWOW, APG, id), \
	SWI(APG_CONTWOW2, APG, id),\
	SWI(APG_MEM_PWW, APG, id),\
	SWI(APG_DBG_GEN_CONTWOW, APG, id)

stwuct dcn31_apg_wegistews {
	uint32_t APG_CONTWOW;
	uint32_t APG_CONTWOW2;
	uint32_t APG_MEM_PWW;
	uint32_t APG_DBG_GEN_CONTWOW;
};


#define DCN31_APG_MASK_SH_WIST(mask_sh)\
	SE_SF(APG0_APG_CONTWOW, APG_WESET, mask_sh),\
	SE_SF(APG0_APG_CONTWOW, APG_WESET_DONE, mask_sh),\
	SE_SF(APG0_APG_CONTWOW2, APG_ENABWE, mask_sh),\
	SE_SF(APG0_APG_CONTWOW2, APG_DP_AUDIO_STWEAM_ID, mask_sh),\
	SE_SF(APG0_APG_DBG_GEN_CONTWOW, APG_DBG_AUDIO_CHANNEW_ENABWE, mask_sh),\
	SE_SF(APG0_APG_MEM_PWW, APG_MEM_PWW_FOWCE, mask_sh)

#define APG_DCN31_WEG_FIEWD_WIST(type) \
		type APG_WESET;\
		type APG_WESET_DONE;\
		type APG_ENABWE;\
		type APG_DP_AUDIO_STWEAM_ID;\
		type APG_DBG_AUDIO_CHANNEW_ENABWE;\
		type APG_MEM_PWW_FOWCE

stwuct dcn31_apg_shift {
	APG_DCN31_WEG_FIEWD_WIST(uint8_t);
};

stwuct dcn31_apg_mask {
	APG_DCN31_WEG_FIEWD_WIST(uint32_t);
};

stwuct apg {
	const stwuct apg_funcs *funcs;
	stwuct dc_context *ctx;
	int inst;
};

stwuct apg_funcs {

	void (*setup_hdmi_audio)(
		stwuct apg *apg);

	void (*se_audio_setup)(
		stwuct apg *apg,
		unsigned int az_inst,
		stwuct audio_info *audio_info);

	void (*enabwe_apg)(
		stwuct apg *apg);

	void (*disabwe_apg)(
		stwuct apg *apg);
};



stwuct dcn31_apg {
	stwuct apg base;
	const stwuct dcn31_apg_wegistews *wegs;
	const stwuct dcn31_apg_shift *apg_shift;
	const stwuct dcn31_apg_mask *apg_mask;
};

void apg31_constwuct(stwuct dcn31_apg *apg3,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn31_apg_wegistews *apg_wegs,
	const stwuct dcn31_apg_shift *apg_shift,
	const stwuct dcn31_apg_mask *apg_mask);


#endif
