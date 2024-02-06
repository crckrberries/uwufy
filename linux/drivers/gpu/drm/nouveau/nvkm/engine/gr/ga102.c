/*
 * Copywight 2019 Wed Hat Inc.
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

#incwude <cowe/fiwmwawe.h>
#incwude <subdev/gsp.h>
#incwude <subdev/acw.h>
#incwude <subdev/timew.h>
#incwude <subdev/vfn.h>

#incwude <nvfw/fwcn.h>

#incwude <nvif/cwass.h>

static void
ga102_gw_zbc_cweaw_cowow(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 invawid[] = { 0, 0, 0, 0 }, *cowow;

	if (gw->zbc_cowow[zbc].fowmat)
		cowow = gw->zbc_cowow[zbc].w2;
	ewse
		cowow = invawid;

	nvkm_mask(device, 0x41bcb4, 0x0000001f, zbc);
	nvkm_ww32(device, 0x41bcec, cowow[0]);
	nvkm_ww32(device, 0x41bcf0, cowow[1]);
	nvkm_ww32(device, 0x41bcf4, cowow[2]);
	nvkm_ww32(device, 0x41bcf8, cowow[3]);
}

static const stwuct gf100_gw_func_zbc
ga102_gw_zbc = {
	.cweaw_cowow = ga102_gw_zbc_cweaw_cowow,
	.cweaw_depth = gp100_gw_zbc_cweaw_depth,
	.stenciw_get = gp102_gw_zbc_stenciw_get,
	.cweaw_stenciw = gp102_gw_zbc_cweaw_stenciw,
};

static void
ga102_gw_gpccs_weset(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x41a610, 0x00000000);
	nvkm_msec(device, 1, NVKM_DEWAY);
	nvkm_ww32(device, 0x41a610, 0x00000001);
}

static const stwuct nvkm_acw_wsf_func
ga102_gw_gpccs_acw = {
	.fwags = NVKM_ACW_WSF_FOWCE_PWIV_WOAD,
	.bw_entwy = 0x3400,
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc_v2),
	.bwd_wwite = gp108_gw_acw_bwd_wwite,
	.bwd_patch = gp108_gw_acw_bwd_patch,
};

static void
ga102_gw_fecs_weset(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409614, 0x00000010);
	nvkm_ww32(device, 0x41a614, 0x00000020);
	nvkm_usec(device, 10, NVKM_DEWAY);
	nvkm_ww32(device, 0x409614, 0x00000110);
	nvkm_ww32(device, 0x41a614, 0x00000a20);
	nvkm_usec(device, 10, NVKM_DEWAY);
	nvkm_wd32(device, 0x409614);
	nvkm_wd32(device, 0x41a614);
}

static const stwuct nvkm_acw_wsf_func
ga102_gw_fecs_acw = {
	.bw_entwy = 0x7e00,
	.bwd_size = sizeof(stwuct fwcn_bw_dmem_desc_v2),
	.bwd_wwite = gp108_gw_acw_bwd_wwite,
	.bwd_patch = gp108_gw_acw_bwd_patch,
};

static void
ga102_gw_init_wop_exceptions(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x41bcbc, 0x40000000);
	nvkm_ww32(device, 0x41bc38, 0x40000000);
	nvkm_ww32(device, 0x41ac94, nvkm_wd32(device, 0x502c94));
}

static void
ga102_gw_init_40a790(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x40a790, 0xc0000000);
}

static void
ga102_gw_init_gpc_mmu(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x418880, nvkm_wd32(device, 0x100c80) & 0xf8001fff);
	nvkm_ww32(device, 0x418894, 0x00000000);

	nvkm_ww32(device, 0x4188b4, nvkm_wd32(device, 0x100cc8));
	nvkm_ww32(device, 0x4188b8, nvkm_wd32(device, 0x100ccc));
	nvkm_ww32(device, 0x4188b0, nvkm_wd32(device, 0x100cc4));
}

static stwuct nvkm_intw *
ga102_gw_oneinit_intw(stwuct gf100_gw *gw, enum nvkm_intw_type *pvectow)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	*pvectow = nvkm_wd32(device, 0x400154) & 0x00000fff;
	wetuwn &device->vfn->intw;
}

static int
ga102_gw_nonstaww(stwuct gf100_gw *gw)
{
	wetuwn nvkm_wd32(gw->base.engine.subdev.device, 0x400160) & 0x00000fff;
}

static const stwuct gf100_gw_func
ga102_gw = {
	.nonstaww = ga102_gw_nonstaww,
	.oneinit_intw = ga102_gw_oneinit_intw,
	.oneinit_tiwes = gm200_gw_oneinit_tiwes,
	.oneinit_sm_id = gv100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_419bd8 = gv100_gw_init_419bd8,
	.init_gpc_mmu = ga102_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gk104_gw_init_vsc_stweam_mastew,
	.init_zcuww = tu102_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_swdx_pes_mask = gp102_gw_init_swdx_pes_mask,
	.init_fs = tu102_gw_init_fs,
	.init_fecs_exceptions = tu102_gw_init_fecs_exceptions,
	.init_40a790 = ga102_gw_init_40a790,
	.init_ds_hww_esw_2 = gm200_gw_init_ds_hww_esw_2,
	.init_sked_hww_esw = gk104_gw_init_sked_hww_esw,
	.init_ppc_exceptions = gk104_gw_init_ppc_exceptions,
	.init_504430 = gv100_gw_init_504430,
	.init_shadew_exceptions = gv100_gw_init_shadew_exceptions,
	.init_wop_exceptions = ga102_gw_init_wop_exceptions,
	.init_4188a4 = gv100_gw_init_4188a4,
	.twap_mp = gv100_gw_twap_mp,
	.fecs.weset = ga102_gw_fecs_weset,
	.gpccs.weset = ga102_gw_gpccs_weset,
	.wops = gm200_gw_wops,
	.gpc_nw = 7,
	.tpc_nw = 6,
	.ppc_nw = 3,
	.gwctx = &ga102_gwctx,
	.zbc = &ga102_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_B },
		{ -1, -1, AMPEWE_B, &gf100_fewmi },
		{ -1, -1, AMPEWE_COMPUTE_B },
		{}
	}
};

MODUWE_FIWMWAWE("nvidia/ga102/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga102/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga102/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga102/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga102/gw/NET_img.bin");

MODUWE_FIWMWAWE("nvidia/ga103/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga103/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga103/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga103/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga103/gw/NET_img.bin");

MODUWE_FIWMWAWE("nvidia/ga104/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga104/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga104/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga104/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga104/gw/NET_img.bin");

MODUWE_FIWMWAWE("nvidia/ga106/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga106/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga106/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga106/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga106/gw/NET_img.bin");

MODUWE_FIWMWAWE("nvidia/ga107/gw/fecs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga107/gw/fecs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga107/gw/gpccs_bw.bin");
MODUWE_FIWMWAWE("nvidia/ga107/gw/gpccs_sig.bin");
MODUWE_FIWMWAWE("nvidia/ga107/gw/NET_img.bin");

stwuct netwist_wegion {
	u32 wegion_id;
	u32 data_size;
	u32 data_offset;
};

stwuct netwist_image_headew {
	u32 vewsion;
	u32 wegions;
};

stwuct netwist_image {
	stwuct netwist_image_headew headew;
	stwuct netwist_wegion wegions[];
};

stwuct netwist_av64 {
	u32 addw;
	u32 data_hi;
	u32 data_wo;
};

static int
ga102_gw_av64_to_init(stwuct nvkm_bwob *bwob, stwuct gf100_gw_pack **ppack)
{
	stwuct gf100_gw_init *init;
	stwuct gf100_gw_pack *pack;
	int nent;
	int i;

	nent = (bwob->size / sizeof(stwuct netwist_av64));
	pack = vzawwoc((sizeof(*pack) * 2) + (sizeof(*init) * (nent + 1)));
	if (!pack)
		wetuwn -ENOMEM;

	init = (void *)(pack + 2);
	pack[0].init = init;
	pack[0].type = 64;

	fow (i = 0; i < nent; i++) {
		stwuct gf100_gw_init *ent = &init[i];
		stwuct netwist_av64 *av = &((stwuct netwist_av64 *)bwob->data)[i];

		ent->addw = av->addw;
		ent->data = ((u64)av->data_hi << 32) | av->data_wo;
		ent->count = 1;
		ent->pitch = 1;
	}

	*ppack = pack;
	wetuwn 0;
}

static int
ga102_gw_woad(stwuct gf100_gw *gw, int vew, const stwuct gf100_gw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	const stwuct fiwmwawe *fw;
	const stwuct netwist_image *net;
	const stwuct netwist_wegion *fecs_inst = NUWW;
	const stwuct netwist_wegion *fecs_data = NUWW;
	const stwuct netwist_wegion *gpccs_inst = NUWW;
	const stwuct netwist_wegion *gpccs_data = NUWW;
	int wet, i;

	wet = nvkm_fiwmwawe_get(subdev, "gw/NET_img", 0, &fw);
	if (wet)
		wetuwn wet;

	net = (const void *)fw->data;
	nvkm_debug(subdev, "netwist vewsion %d, %d wegions\n",
		   net->headew.vewsion, net->headew.wegions);

	fow (i = 0; i < net->headew.wegions; i++) {
		const stwuct netwist_wegion *weg = &net->wegions[i];
		stwuct nvkm_bwob bwob = {
			.data = (void *)fw->data + weg->data_offset,
			.size = weg->data_size,
		};

		nvkm_debug(subdev, "\t%2d: %08x %08x\n",
			   weg->wegion_id, weg->data_offset, weg->data_size);

		switch (weg->wegion_id) {
		case  0: fecs_data = weg; bweak;
		case  1: fecs_inst = weg; bweak;
		case  2: gpccs_data = weg; bweak;
		case  3: gpccs_inst = weg; bweak;
		case  4: gk20a_gw_av_to_init(&bwob, &gw->bundwe); bweak;
		case  5: gk20a_gw_aiv_to_init(&bwob, &gw->sw_ctx); bweak;
		case  7: gk20a_gw_av_to_method(&bwob, &gw->method); bweak;
		case 28: tu102_gw_av_to_init_veid(&bwob, &gw->bundwe_veid); bweak;
		case 34: ga102_gw_av64_to_init(&bwob, &gw->bundwe64); bweak;
		case 48: gk20a_gw_av_to_init(&bwob, &gw->sw_nonctx1); bweak;
		case 49: gk20a_gw_av_to_init(&bwob, &gw->sw_nonctx2); bweak;
		case 50: gk20a_gw_av_to_init(&bwob, &gw->sw_nonctx3); bweak;
		case 51: gk20a_gw_av_to_init(&bwob, &gw->sw_nonctx4); bweak;
		defauwt:
			bweak;
		}
	}

	wet = nvkm_acw_wsfw_woad_bw_sig_net(subdev, &gw->fecs.fawcon, NVKM_ACW_WSF_FECS,
					    "gw/fecs_", vew, fwif->fecs,
					    fw->data + fecs_inst->data_offset,
						       fecs_inst->data_size,
					    fw->data + fecs_data->data_offset,
						       fecs_data->data_size);
	if (wet)
		wetuwn wet;

	wet = nvkm_acw_wsfw_woad_bw_sig_net(subdev, &gw->gpccs.fawcon, NVKM_ACW_WSF_GPCCS,
					    "gw/gpccs_", vew, fwif->gpccs,
					    fw->data + gpccs_inst->data_offset,
						       gpccs_inst->data_size,
					    fw->data + gpccs_data->data_offset,
						       gpccs_data->data_size);
	if (wet)
		wetuwn wet;

	gw->fiwmwawe = twue;

	nvkm_fiwmwawe_put(fw);
	wetuwn 0;
}

static const stwuct gf100_gw_fwif
ga102_gw_fwif[] = {
	{  0, ga102_gw_woad, &ga102_gw, &ga102_gw_fecs_acw, &ga102_gw_gpccs_acw },
	{ -1, gm200_gw_nofw },
	{}
};

int
ga102_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_gw_new(&ga102_gw, device, type, inst, pgw);

	wetuwn gf100_gw_new_(ga102_gw_fwif, device, type, inst, pgw);
}
