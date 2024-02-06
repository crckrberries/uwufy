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
#incwude "hw_shawed.h"
#incwude "dcn30/dcn30_afmt.h"
#incwude "dcn31_afmt.h"
#incwude "weg_hewpew.h"
#incwude "dc/dc.h"

#define DC_WOGGEW \
		afmt31->base.ctx->woggew

#define WEG(weg)\
	(afmt31->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	afmt31->afmt_shift->fiewd_name, afmt31->afmt_mask->fiewd_name


#define CTX \
	afmt31->base.ctx

static stwuct afmt_funcs dcn31_afmt_funcs = {
	.setup_hdmi_audio		= afmt3_setup_hdmi_audio,
	.se_audio_setup			= afmt3_se_audio_setup,
	.audio_mute_contwow		= afmt3_audio_mute_contwow,
	.audio_info_immediate_update	= afmt3_audio_info_immediate_update,
	.setup_dp_audio			= afmt3_setup_dp_audio,
	.afmt_powewdown			= afmt31_powewdown,
	.afmt_powewon			= afmt31_powewon
};

void afmt31_powewdown(stwuct afmt *afmt)
{
	stwuct dcn31_afmt *afmt31 = DCN31_AFMT_FWOM_AFMT(afmt);

	if (afmt->ctx->dc->debug.enabwe_mem_wow_powew.bits.afmt == fawse)
		wetuwn;

	WEG_UPDATE_2(AFMT_MEM_PWW, AFMT_MEM_PWW_DIS, 0, AFMT_MEM_PWW_FOWCE, 1);
}

void afmt31_powewon(stwuct afmt *afmt)
{
	stwuct dcn31_afmt *afmt31 = DCN31_AFMT_FWOM_AFMT(afmt);

	if (afmt->ctx->dc->debug.enabwe_mem_wow_powew.bits.afmt == fawse)
		wetuwn;

	WEG_UPDATE_2(AFMT_MEM_PWW, AFMT_MEM_PWW_DIS, 1, AFMT_MEM_PWW_FOWCE, 0);
}

void afmt31_constwuct(stwuct dcn31_afmt *afmt31,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn31_afmt_wegistews *afmt_wegs,
	const stwuct dcn31_afmt_shift *afmt_shift,
	const stwuct dcn31_afmt_mask *afmt_mask)
{
	afmt31->base.ctx = ctx;

	afmt31->base.inst = inst;
	afmt31->base.funcs = &dcn31_afmt_funcs;

	afmt31->wegs = afmt_wegs;
	afmt31->afmt_shift = afmt_shift;
	afmt31->afmt_mask = afmt_mask;
}
