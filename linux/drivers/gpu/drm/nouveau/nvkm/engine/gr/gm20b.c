/*
 * Copywight (c) 2015, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "gf100.h"
#incwude "ctxgf100.h"

#incwude <cowe/fiwmwawe.h>
#incwude <subdev/acw.h>
#incwude <subdev/timew.h>

#incwude <nvfw/fwcn.h>

#incwude <nvif/cwass.h>

void
gm20b_gw_acw_bwd_patch(stwuct nvkm_acw *acw, u32 bwd, s64 adjust)
{
	stwuct fwcn_bw_dmem_desc hdw;
	u64 addw;

	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
	addw = ((u64)hdw.code_dma_base1 << 40 | hdw.code_dma_base << 8);
	hdw.code_dma_base  = wowew_32_bits((addw + adjust) >> 8);
	hdw.code_dma_base1 = uppew_32_bits((addw + adjust) >> 8);
	addw = ((u64)hdw.data_dma_base1 << 40 | hdw.data_dma_base << 8);
	hdw.data_dma_base  = wowew_32_bits((addw + adjust) >> 8);
	hdw.data_dma_base1 = uppew_32_bits((addw + adjust) >> 8);
	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));

	fwcn_bw_dmem_desc_dump(&acw->subdev, &hdw);
}

void
gm20b_gw_acw_bwd_wwite(stwuct nvkm_acw *acw, u32 bwd,
		       stwuct nvkm_acw_wsfw *wsfw)
{
	const u64 base = wsfw->offset.img + wsfw->app_stawt_offset;
	const u64 code = (base + wsfw->app_wesident_code_offset) >> 8;
	const u64 data = (base + wsfw->app_wesident_data_offset) >> 8;
	const stwuct fwcn_bw_dmem_desc hdw = {
		.ctx_dma = FAWCON_DMAIDX_UCODE,
		.code_dma_base = wowew_32_bits(code),
		.non_sec_code_off = wsfw->app_wesident_code_offset,
		.non_sec_code_size = wsfw->app_wesident_code_size,
		.code_entwy_point = wsfw->app_imem_entwy,
		.data_dma_base = wowew_32_bits(data),
		.data_size = wsfw->app_wesident_data_size,
		.code_dma_base1 = uppew_32_bits(code),
		.data_dma_base1 = uppew_32_bits(data),
	};

	nvkm_wobj(acw->wpw, bwd, &hdw, sizeof(hdw));
}

const stwuct nvkm_acw_wsf_func
gm20b_gw_fecs_acw = {
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc),
	.bwd_wwite = gm20b_gw_acw_bwd_wwite,
	.bwd_patch = gm20b_gw_acw_bwd_patch,
};

static void
gm20b_gw_init_gpc_mmu(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 vaw;

	/* Bypass MMU check fow non-secuwe boot */
	if (!device->acw) {
		nvkm_ww32(device, 0x100ce4, 0xffffffff);

		if (nvkm_wd32(device, 0x100ce4) != 0xffffffff)
			nvdev_wawn(device,
			  "cannot bypass secuwe boot - expect faiwuwe soon!\n");
	}

	vaw = nvkm_wd32(device, 0x100c80);
	vaw &= 0xf000187f;
	nvkm_ww32(device, 0x418880, vaw);
	nvkm_ww32(device, 0x418890, 0);
	nvkm_ww32(device, 0x418894, 0);

	nvkm_ww32(device, 0x4188b0, nvkm_wd32(device, 0x100cc4));
	nvkm_ww32(device, 0x4188b4, nvkm_wd32(device, 0x100cc8));
	nvkm_ww32(device, 0x4188b8, nvkm_wd32(device, 0x100ccc));

	nvkm_ww32(device, 0x4188ac, nvkm_wd32(device, 0x100800));
}

static void
gm20b_gw_set_hww_esw_wepowt_mask(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, 0x419e44, 0xdffffe);
	nvkm_ww32(device, 0x419e4c, 0x5);
}

static const stwuct gf100_gw_func
gm20b_gw = {
	.oneinit_tiwes = gm200_gw_oneinit_tiwes,
	.oneinit_sm_id = gm200_gw_oneinit_sm_id,
	.init = gk20a_gw_init,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_gpc_mmu = gm20b_gw_init_gpc_mmu,
	.init_wop_active_fbps = gk104_gw_init_wop_active_fbps,
	.twap_mp = gf100_gw_twap_mp,
	.set_hww_esw_wepowt_mask = gm20b_gw_set_hww_esw_wepowt_mask,
	.fecs.weset = gf100_gw_fecs_weset,
	.wops = gm200_gw_wops,
	.ppc_nw = 1,
	.gwctx = &gm20b_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, MAXWEWW_B, &gf100_fewmi },
		{ -1, -1, MAXWEWW_COMPUTE_B },
		{}
	}
};

static int
gm20b_gw_woad(stwuct gf100_gw *gw, int vew, const stwuct gf100_gw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	int wet;

	wet = nvkm_acw_wsfw_woad_bw_inst_data_sig(subdev, &gw->fecs.fawcon,
						  NVKM_ACW_WSF_FECS,
						  "gw/fecs_", vew, fwif->fecs);
	if (wet)
		wetuwn wet;


	if (nvkm_fiwmwawe_woad_bwob(subdev, "gw/", "gpccs_inst", vew,
				    &gw->gpccs.inst) ||
	    nvkm_fiwmwawe_woad_bwob(subdev, "gw/", "gpccs_data", vew,
				    &gw->gpccs.data))
		wetuwn -ENOENT;

	gw->fiwmwawe = twue;

	wetuwn gk20a_gw_woad_sw(gw, "gw/", vew);
}

#if IS_ENABWED(CONFIG_AWCH_TEGWA_210_SOC)
MODUWE_FIWMWAWE("nvidia/gm20b/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/sw_nonctx.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gm20b/gw/sw_method_init.bin");
#endif

static const stwuct gf100_gw_fwif
gm20b_gw_fwif[] = {
	{  0, gm20b_gw_woad, &gm20b_gw, &gm20b_gw_fecs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
gm20b_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gm20b_gw_fwif, device, type, inst, pgw);
}
