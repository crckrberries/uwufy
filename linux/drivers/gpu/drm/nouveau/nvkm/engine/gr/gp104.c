/*
 * Copywight 2018 Wed Hat Inc.
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
 */
#incwude "gf100.h"
#incwude "ctxgf100.h"

#incwude <nvif/cwass.h>

static const stwuct gf100_gw_func
gp104_gw = {
	.oneinit_tiwes = gm200_gw_oneinit_tiwes,
	.oneinit_sm_id = gm200_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gm200_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gm200_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gp100_gw_init_wop_active_fbps,
	.init_swdx_pes_mask = gp102_gw_init_swdx_pes_mask,
	.init_fecs_exceptions = gp100_gw_init_fecs_exceptions,
	.init_ds_hww_esw_2 = gm200_gw_init_ds_hww_esw_2,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_504430 = gm107_gw_init_504430,
	.init_shadew_exceptions = gp100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.twap_mp = gf100_gw_twap_mp,
	.fecs.weset = gf100_gw_fecs_weset,
	.wops = gm200_gw_wops,
	.gpc_nw = 6,
	.tpc_nw = 5,
	.ppc_nw = 3,
	.gwctx = &gp104_gwctx,
	.zbc = &gp102_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, PASCAW_B, &gf100_fewmi },
		{ -1, -1, PASCAW_COMPUTE_B },
		{}
	}
};

MODUWE_FIWMWAWE("nvidia/gp104/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gp104/gw/sw_method_init.bin");

MODUWE_FIWMWAWE("nvidia/gp106/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gp106/gw/sw_method_init.bin");

static const stwuct gf100_gw_fwif
gp104_gw_fwif[] = {
	{  0, gm200_gw_woad, &gp104_gw, &gm200_gw_fecs_acw, &gm200_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gp104_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gp104_gw_fwif, device, type, inst, pgw);
}
