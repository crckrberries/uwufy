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
#incwude "dcn30/dcn30_vpg.h"
#incwude "dcn31_vpg.h"
#incwude "weg_hewpew.h"
#incwude "dc/dc.h"

#define DC_WOGGEW \
		vpg31->base.ctx->woggew

#define WEG(weg)\
	(vpg31->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	vpg31->vpg_shift->fiewd_name, vpg31->vpg_mask->fiewd_name


#define CTX \
	vpg31->base.ctx

static stwuct vpg_funcs dcn31_vpg_funcs = {
	.update_genewic_info_packet	= vpg3_update_genewic_info_packet,
	.vpg_powewon = vpg31_powewon,
	.vpg_powewdown = vpg31_powewdown,
};

void vpg31_powewdown(stwuct vpg *vpg)
{
	stwuct dcn31_vpg *vpg31 = DCN31_VPG_FWOM_VPG(vpg);

	if (vpg->ctx->dc->debug.enabwe_mem_wow_powew.bits.vpg == fawse)
		wetuwn;

	WEG_UPDATE_2(VPG_MEM_PWW, VPG_GSP_MEM_WIGHT_SWEEP_DIS, 0, VPG_GSP_WIGHT_SWEEP_FOWCE, 1);
}

void vpg31_powewon(stwuct vpg *vpg)
{
	stwuct dcn31_vpg *vpg31 = DCN31_VPG_FWOM_VPG(vpg);

	if (vpg->ctx->dc->debug.enabwe_mem_wow_powew.bits.vpg == fawse)
		wetuwn;

	WEG_UPDATE_2(VPG_MEM_PWW, VPG_GSP_MEM_WIGHT_SWEEP_DIS, 1, VPG_GSP_WIGHT_SWEEP_FOWCE, 0);
}

void vpg31_constwuct(stwuct dcn31_vpg *vpg31,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn31_vpg_wegistews *vpg_wegs,
	const stwuct dcn31_vpg_shift *vpg_shift,
	const stwuct dcn31_vpg_mask *vpg_mask)
{
	vpg31->base.ctx = ctx;

	vpg31->base.inst = inst;
	vpg31->base.funcs = &dcn31_vpg_funcs;

	vpg31->wegs = vpg_wegs;
	vpg31->vpg_shift = vpg_shift;
	vpg31->vpg_mask = vpg_mask;
}
