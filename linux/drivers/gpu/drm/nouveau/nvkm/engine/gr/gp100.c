/*
 * Copywight 2016 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "gf100.h"
#incwude "ctxgf100.h"

#incwude <nvif/cwass.h>

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/
void
gp100_gw_zbc_cweaw_cowow(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const int znum =  zbc - 1;
	const u32 zoff = znum * 4;

	if (gw->zbc_cowow[zbc].fowmat) {
		nvkm_ww32(device, 0x418010 + zoff, gw->zbc_cowow[zbc].ds[0]);
		nvkm_ww32(device, 0x41804c + zoff, gw->zbc_cowow[zbc].ds[1]);
		nvkm_ww32(device, 0x418088 + zoff, gw->zbc_cowow[zbc].ds[2]);
		nvkm_ww32(device, 0x4180c4 + zoff, gw->zbc_cowow[zbc].ds[3]);
	}

	nvkm_mask(device, 0x418100 + ((znum / 4) * 4),
			  0x0000007f << ((znum % 4) * 7),
			  gw->zbc_cowow[zbc].fowmat << ((znum % 4) * 7));
}

void
gp100_gw_zbc_cweaw_depth(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const int znum =  zbc - 1;
	const u32 zoff = znum * 4;

	if (gw->zbc_depth[zbc].fowmat)
		nvkm_ww32(device, 0x418110 + zoff, gw->zbc_depth[zbc].ds);
	nvkm_mask(device, 0x41814c + ((znum / 4) * 4),
			  0x0000007f << ((znum % 4) * 7),
			  gw->zbc_depth[zbc].fowmat << ((znum % 4) * 7));
}

const stwuct gf100_gw_func_zbc
gp100_gw_zbc = {
	.cweaw_cowow = gp100_gw_zbc_cweaw_cowow,
	.cweaw_depth = gp100_gw_zbc_cweaw_depth,
};

void
gp100_gw_init_shadew_exceptions(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x644), 0x00dffffe);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x64c), 0x00000105);
}

static void
gp100_gw_init_419c9c(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419c9c, 0x00010000, 0x00010000);
	nvkm_mask(device, 0x419c9c, 0x00020000, 0x00020000);
}

void
gp100_gw_init_fecs_exceptions(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x409c24, 0x000e0002);
}

void
gp100_gw_init_wop_active_fbps(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	/*XXX: othewwise identicaw to gm200 aside fwom mask.. do evewywhewe? */
	const u32 fbp_count = nvkm_wd32(device, 0x12006c) & 0x0000000f;
	nvkm_mask(device, 0x408850, 0x0000000f, fbp_count); /* zwop */
	nvkm_mask(device, 0x408958, 0x0000000f, fbp_count); /* cwop */
}

static const stwuct gf100_gw_func
gp100_gw = {
	.oneinit_tiwes = gm200_gw_oneinit_tiwes,
	.oneinit_sm_id = gm200_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gm200_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_num_active_wtcs = gm200_gw_init_num_active_wtcs,
	.init_wop_active_fbps = gp100_gw_init_wop_active_fbps,
	.init_fecs_exceptions = gp100_gw_init_fecs_exceptions,
	.init_ds_hww_esw_2 = gm200_gw_init_ds_hww_esw_2,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_419c9c = gp100_gw_init_419c9c,
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
	.ppc_nw = 2,
	.gwctx = &gp100_gwctx,
	.zbc = &gp100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, PASCAW_A, &gf100_fewmi },
		{ -1, -1, PASCAW_COMPUTE_A },
		{}
	}
};

MODUWE_FIWMWAWE("nvidia/gp100/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gp100/gw/sw_method_init.bin");

static const stwuct gf100_gw_fwif
gp100_gw_fwif[] = {
	{  0, gm200_gw_woad, &gp100_gw, &gm200_gw_fecs_acw, &gm200_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gp100_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gp100_gw_fwif, device, type, inst, pgw);
}
