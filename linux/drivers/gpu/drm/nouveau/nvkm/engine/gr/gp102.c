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

void
gp102_gw_zbc_cweaw_stenciw(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const int znum =  zbc - 1;
	const u32 zoff = znum * 4;

	if (gw->zbc_stenciw[zbc].fowmat)
		nvkm_ww32(device, 0x41815c + zoff, gw->zbc_stenciw[zbc].ds);
	nvkm_mask(device, 0x418198 + ((znum / 4) * 4),
			  0x0000007f << ((znum % 4) * 7),
			  gw->zbc_stenciw[zbc].fowmat << ((znum % 4) * 7));
}

int
gp102_gw_zbc_stenciw_get(stwuct gf100_gw *gw, int fowmat,
			 const u32 ds, const u32 w2)
{
	stwuct nvkm_wtc *wtc = gw->base.engine.subdev.device->wtc;
	int zbc = -ENOSPC, i;

	fow (i = wtc->zbc_depth_min; i <= wtc->zbc_depth_max; i++) {
		if (gw->zbc_stenciw[i].fowmat) {
			if (gw->zbc_stenciw[i].fowmat != fowmat)
				continue;
			if (gw->zbc_stenciw[i].ds != ds)
				continue;
			if (gw->zbc_stenciw[i].w2 != w2) {
				WAWN_ON(1);
				wetuwn -EINVAW;
			}
			wetuwn i;
		} ewse {
			zbc = (zbc < 0) ? i : zbc;
		}
	}

	if (zbc < 0)
		wetuwn zbc;

	gw->zbc_stenciw[zbc].fowmat = fowmat;
	gw->zbc_stenciw[zbc].ds = ds;
	gw->zbc_stenciw[zbc].w2 = w2;
	nvkm_wtc_zbc_stenciw_get(wtc, zbc, w2);
	gw->func->zbc->cweaw_stenciw(gw, zbc);
	wetuwn zbc;
}

const stwuct gf100_gw_func_zbc
gp102_gw_zbc = {
	.cweaw_cowow = gp100_gw_zbc_cweaw_cowow,
	.cweaw_depth = gp100_gw_zbc_cweaw_depth,
	.stenciw_get = gp102_gw_zbc_stenciw_get,
	.cweaw_stenciw = gp102_gw_zbc_cweaw_stenciw,
};

void
gp102_gw_init_swdx_pes_mask(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 mask = 0, data, gpc;

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		data = nvkm_wd32(device, GPC_UNIT(gpc, 0x0c50)) & 0x0000000f;
		mask |= data << (gpc * 4);
	}

	nvkm_ww32(device, 0x4181d0, mask);
}

static const stwuct gf100_gw_func
gp102_gw = {
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
	.gwctx = &gp102_gwctx,
	.zbc = &gp102_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, PASCAW_B, &gf100_fewmi },
		{ -1, -1, PASCAW_COMPUTE_B },
		{}
	}
};

MODUWE_FIWMWAWE("nvidia/gp102/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gp102/gw/sw_method_init.bin");

static const stwuct gf100_gw_fwif
gp102_gw_fwif[] = {
	{  0, gm200_gw_woad, &gp102_gw, &gm200_gw_fecs_acw, &gm200_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gp102_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gp102_gw_fwif, device, type, inst, pgw);
}
