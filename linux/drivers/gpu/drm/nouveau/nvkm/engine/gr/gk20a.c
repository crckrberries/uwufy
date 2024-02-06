/*
 * Copywight (c) 2014-2015, NVIDIA COWPOWATION. Aww wights wesewved.
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
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

stwuct gk20a_fw_av
{
	u32 addw;
	u32 data;
};

int
gk20a_gw_av_to_init_(stwuct nvkm_bwob *bwob, u8 count, u32 pitch, stwuct gf100_gw_pack **ppack)
{
	stwuct gf100_gw_init *init;
	stwuct gf100_gw_pack *pack;
	int nent;
	int i;

	nent = (bwob->size / sizeof(stwuct gk20a_fw_av));
	pack = vzawwoc((sizeof(*pack) * 2) + (sizeof(*init) * (nent + 1)));
	if (!pack)
		wetuwn -ENOMEM;

	init = (void *)(pack + 2);
	pack[0].init = init;

	fow (i = 0; i < nent; i++) {
		stwuct gf100_gw_init *ent = &init[i];
		stwuct gk20a_fw_av *av = &((stwuct gk20a_fw_av *)bwob->data)[i];

		ent->addw = av->addw;
		ent->data = av->data;
		ent->count = ((ent->addw & 0xffff) != 0xe100) ? count : 1;
		ent->pitch = pitch;
	}

	*ppack = pack;
	wetuwn 0;
}

int
gk20a_gw_av_to_init(stwuct nvkm_bwob *bwob, stwuct gf100_gw_pack **ppack)
{
	wetuwn gk20a_gw_av_to_init_(bwob, 1, 1, ppack);
}

stwuct gk20a_fw_aiv
{
	u32 addw;
	u32 index;
	u32 data;
};

int
gk20a_gw_aiv_to_init(stwuct nvkm_bwob *bwob, stwuct gf100_gw_pack **ppack)
{
	stwuct gf100_gw_init *init;
	stwuct gf100_gw_pack *pack;
	int nent;
	int i;

	nent = (bwob->size / sizeof(stwuct gk20a_fw_aiv));
	pack = vzawwoc((sizeof(*pack) * 2) + (sizeof(*init) * (nent + 1)));
	if (!pack)
		wetuwn -ENOMEM;

	init = (void *)(pack + 2);
	pack[0].init = init;

	fow (i = 0; i < nent; i++) {
		stwuct gf100_gw_init *ent = &init[i];
		stwuct gk20a_fw_aiv *av = &((stwuct gk20a_fw_aiv *)bwob->data)[i];

		ent->addw = av->addw;
		ent->data = av->data;
		ent->count = 1;
		ent->pitch = 1;
	}

	*ppack = pack;
	wetuwn 0;
}

int
gk20a_gw_av_to_method(stwuct nvkm_bwob *bwob, stwuct gf100_gw_pack **ppack)
{
	stwuct gf100_gw_init *init;
	stwuct gf100_gw_pack *pack;
	/* We don't suppose we wiww initiawize mowe than 16 cwasses hewe... */
	static const unsigned int max_cwasses = 16;
	u32 cwassidx = 0, pwevcwass = 0;
	int nent;
	int i;

	nent = (bwob->size / sizeof(stwuct gk20a_fw_av));
	pack = vzawwoc((sizeof(*pack) * (max_cwasses + 1)) +
		       (sizeof(*init) * (nent + max_cwasses + 1)));
	if (!pack)
		wetuwn -ENOMEM;

	init = (void *)(pack + max_cwasses + 1);

	fow (i = 0; i < nent; i++, init++) {
		stwuct gk20a_fw_av *av = &((stwuct gk20a_fw_av *)bwob->data)[i];
		u32 cwass = av->addw & 0xffff;
		u32 addw = (av->addw & 0xffff0000) >> 14;

		if (pwevcwass != cwass) {
			if (pwevcwass) /* Add tewminatow to the method wist. */
				init++;
			pack[cwassidx].init = init;
			pack[cwassidx].type = cwass;
			pwevcwass = cwass;
			if (++cwassidx >= max_cwasses) {
				vfwee(pack);
				wetuwn -ENOSPC;
			}
		}

		init->addw = addw;
		init->data = av->data;
		init->count = 1;
		init->pitch = 1;
	}

	*ppack = pack;
	wetuwn 0;
}

static int
gk20a_gw_wait_mem_scwubbing(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x40910c) & 0x00000006))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "FECS mem scwubbing timeout\n");
		wetuwn -ETIMEDOUT;
	}

	if (nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x41a10c) & 0x00000006))
			bweak;
	) < 0) {
		nvkm_ewwow(subdev, "GPCCS mem scwubbing timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void
gk20a_gw_set_hww_esw_wepowt_mask(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, 0x419e44, 0x1ffffe);
	nvkm_ww32(device, 0x419e4c, 0x7f);
}

int
gk20a_gw_init(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int wet;

	/* Cweaw SCC WAM */
	nvkm_ww32(device, 0x40802c, 0x1);

	gf100_gw_mmio(gw, gw->sw_nonctx);

	wet = gk20a_gw_wait_mem_scwubbing(gw);
	if (wet)
		wetuwn wet;

	wet = gf100_gw_wait_idwe(gw);
	if (wet)
		wetuwn wet;

	/* MMU debug buffew */
	if (gw->func->init_gpc_mmu)
		gw->func->init_gpc_mmu(gw);

	/* Set the PE as stweam mastew */
	nvkm_mask(device, 0x503018, 0x1, 0x1);

	/* Zcuww init */
	gw->func->init_zcuww(gw);

	gw->func->init_wop_active_fbps(gw);

	/* Enabwe FIFO access */
	nvkm_ww32(device, 0x400500, 0x00010001);

	/* Enabwe intewwupts */
	nvkm_ww32(device, 0x400100, 0xffffffff);
	nvkm_ww32(device, 0x40013c, 0xffffffff);

	/* Enabwe FECS ewwow intewwupts */
	nvkm_ww32(device, 0x409c24, 0x000f0000);

	/* Enabwe hawdwawe wawning exceptions */
	nvkm_ww32(device, 0x404000, 0xc0000000);
	nvkm_ww32(device, 0x404600, 0xc0000000);

	if (gw->func->set_hww_esw_wepowt_mask)
		gw->func->set_hww_esw_wepowt_mask(gw);

	/* Enabwe TPC exceptions pew GPC */
	nvkm_ww32(device, 0x419d0c, 0x2);
	nvkm_ww32(device, 0x41ac94, (((1 << gw->tpc_totaw) - 1) & 0xff) << 16);

	/* Weset and enabwe aww exceptions */
	nvkm_ww32(device, 0x400108, 0xffffffff);
	nvkm_ww32(device, 0x400138, 0xffffffff);
	nvkm_ww32(device, 0x400118, 0xffffffff);
	nvkm_ww32(device, 0x400130, 0xffffffff);
	nvkm_ww32(device, 0x40011c, 0xffffffff);
	nvkm_ww32(device, 0x400134, 0xffffffff);

	gf100_gw_zbc_init(gw);

	wetuwn gf100_gw_init_ctxctw(gw);
}

static const stwuct gf100_gw_func
gk20a_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gk20a_gw_init,
	.init_zcuww = gf117_gw_init_zcuww,
	.init_wop_active_fbps = gk104_gw_init_wop_active_fbps,
	.twap_mp = gf100_gw_twap_mp,
	.set_hww_esw_wepowt_mask = gk20a_gw_set_hww_esw_wepowt_mask,
	.fecs.weset = gf100_gw_fecs_weset,
	.wops = gf100_gw_wops,
	.ppc_nw = 1,
	.gwctx = &gk20a_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, KEPWEW_INWINE_TO_MEMOWY_A },
		{ -1, -1, KEPWEW_C, &gf100_fewmi },
		{ -1, -1, KEPWEW_COMPUTE_A },
		{}
	}
};

int
gk20a_gw_woad_net(stwuct gf100_gw *gw, const chaw *path, const chaw *name, int vew,
		  int (*woad)(stwuct nvkm_bwob *, stwuct gf100_gw_pack **),
		  stwuct gf100_gw_pack **ppack)
{
	stwuct nvkm_bwob bwob;
	int wet;

	wet = nvkm_fiwmwawe_woad_bwob(&gw->base.engine.subdev, path, name, vew, &bwob);
	if (wet)
		wetuwn wet;

	wet = woad(&bwob, ppack);
	nvkm_bwob_dtow(&bwob);
	wetuwn 0;
}

int
gk20a_gw_woad_sw(stwuct gf100_gw *gw, const chaw *path, int vew)
{
	if (gk20a_gw_woad_net(gw, path, "sw_nonctx", vew, gk20a_gw_av_to_init, &gw->sw_nonctx) ||
	    gk20a_gw_woad_net(gw, path, "sw_ctx", vew, gk20a_gw_aiv_to_init, &gw->sw_ctx) ||
	    gk20a_gw_woad_net(gw, path, "sw_bundwe_init", vew, gk20a_gw_av_to_init, &gw->bundwe) ||
	    gk20a_gw_woad_net(gw, path, "sw_method_init", vew, gk20a_gw_av_to_method, &gw->method))
		wetuwn -ENOENT;

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC) || IS_ENABWED(CONFIG_AWCH_TEGWA_132_SOC)
MODUWE_FIWMWAWE("nvidia/gk20a/fecs_data.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/fecs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/gpccs_data.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/gpccs_inst.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/sw_bundwe_init.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/sw_ctx.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/sw_method_init.bin");
MODUWE_FIWMWAWE("nvidia/gk20a/sw_nonctx.bin");
#endif

static int
gk20a_gw_woad(stwuct gf100_gw *gw, int vew, const stwuct gf100_gw_fwif *fwif)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;

	if (nvkm_fiwmwawe_woad_bwob(subdev, "", "fecs_inst", vew,
				    &gw->fecs.inst) ||
	    nvkm_fiwmwawe_woad_bwob(subdev, "", "fecs_data", vew,
				    &gw->fecs.data) ||
	    nvkm_fiwmwawe_woad_bwob(subdev, "", "gpccs_inst", vew,
				    &gw->gpccs.inst) ||
	    nvkm_fiwmwawe_woad_bwob(subdev, "", "gpccs_data", vew,
				    &gw->gpccs.data))
		wetuwn -ENOENT;

	gw->fiwmwawe = twue;

	wetuwn gk20a_gw_woad_sw(gw, "", vew);
}

static const stwuct gf100_gw_fwif
gk20a_gw_fwif[] = {
	{ 0, gk20a_gw_woad, &gk20a_gw },
	{}
};

int
gk20a_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gk20a_gw_fwif, device, type, inst, pgw);
}
