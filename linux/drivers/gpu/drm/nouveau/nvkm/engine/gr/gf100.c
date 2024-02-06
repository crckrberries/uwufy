/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "gf100.h"
#incwude "ctxgf100.h"
#incwude "fuc/os.h"

#incwude <cowe/cwient.h>
#incwude <cowe/fiwmwawe.h>
#incwude <cowe/option.h>
#incwude <subdev/acw.h>
#incwude <subdev/fb.h>
#incwude <subdev/mc.h>
#incwude <subdev/pmu.h>
#incwude <subdev/thewm.h>
#incwude <subdev/timew.h>
#incwude <engine/fifo.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw9097.h>
#incwude <nvif/if900d.h>
#incwude <nvif/unpack.h>

/*******************************************************************************
 * Zewo Bandwidth Cweaw
 ******************************************************************************/

static void
gf100_gw_zbc_cweaw_cowow(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	if (gw->zbc_cowow[zbc].fowmat) {
		nvkm_ww32(device, 0x405804, gw->zbc_cowow[zbc].ds[0]);
		nvkm_ww32(device, 0x405808, gw->zbc_cowow[zbc].ds[1]);
		nvkm_ww32(device, 0x40580c, gw->zbc_cowow[zbc].ds[2]);
		nvkm_ww32(device, 0x405810, gw->zbc_cowow[zbc].ds[3]);
	}
	nvkm_ww32(device, 0x405814, gw->zbc_cowow[zbc].fowmat);
	nvkm_ww32(device, 0x405820, zbc);
	nvkm_ww32(device, 0x405824, 0x00000004); /* TWIGGEW | WWITE | COWOW */
}

static int
gf100_gw_zbc_cowow_get(stwuct gf100_gw *gw, int fowmat,
		       const u32 ds[4], const u32 w2[4])
{
	stwuct nvkm_wtc *wtc = gw->base.engine.subdev.device->wtc;
	int zbc = -ENOSPC, i;

	fow (i = wtc->zbc_cowow_min; i <= wtc->zbc_cowow_max; i++) {
		if (gw->zbc_cowow[i].fowmat) {
			if (gw->zbc_cowow[i].fowmat != fowmat)
				continue;
			if (memcmp(gw->zbc_cowow[i].ds, ds, sizeof(
				   gw->zbc_cowow[i].ds)))
				continue;
			if (memcmp(gw->zbc_cowow[i].w2, w2, sizeof(
				   gw->zbc_cowow[i].w2))) {
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

	memcpy(gw->zbc_cowow[zbc].ds, ds, sizeof(gw->zbc_cowow[zbc].ds));
	memcpy(gw->zbc_cowow[zbc].w2, w2, sizeof(gw->zbc_cowow[zbc].w2));
	gw->zbc_cowow[zbc].fowmat = fowmat;
	nvkm_wtc_zbc_cowow_get(wtc, zbc, w2);
	gw->func->zbc->cweaw_cowow(gw, zbc);
	wetuwn zbc;
}

static void
gf100_gw_zbc_cweaw_depth(stwuct gf100_gw *gw, int zbc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	if (gw->zbc_depth[zbc].fowmat)
		nvkm_ww32(device, 0x405818, gw->zbc_depth[zbc].ds);
	nvkm_ww32(device, 0x40581c, gw->zbc_depth[zbc].fowmat);
	nvkm_ww32(device, 0x405820, zbc);
	nvkm_ww32(device, 0x405824, 0x00000005); /* TWIGGEW | WWITE | DEPTH */
}

static int
gf100_gw_zbc_depth_get(stwuct gf100_gw *gw, int fowmat,
		       const u32 ds, const u32 w2)
{
	stwuct nvkm_wtc *wtc = gw->base.engine.subdev.device->wtc;
	int zbc = -ENOSPC, i;

	fow (i = wtc->zbc_depth_min; i <= wtc->zbc_depth_max; i++) {
		if (gw->zbc_depth[i].fowmat) {
			if (gw->zbc_depth[i].fowmat != fowmat)
				continue;
			if (gw->zbc_depth[i].ds != ds)
				continue;
			if (gw->zbc_depth[i].w2 != w2) {
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

	gw->zbc_depth[zbc].fowmat = fowmat;
	gw->zbc_depth[zbc].ds = ds;
	gw->zbc_depth[zbc].w2 = w2;
	nvkm_wtc_zbc_depth_get(wtc, zbc, w2);
	gw->func->zbc->cweaw_depth(gw, zbc);
	wetuwn zbc;
}

const stwuct gf100_gw_func_zbc
gf100_gw_zbc = {
	.cweaw_cowow = gf100_gw_zbc_cweaw_cowow,
	.cweaw_depth = gf100_gw_zbc_cweaw_depth,
};

/*******************************************************************************
 * Gwaphics object cwasses
 ******************************************************************************/
#define gf100_gw_object(p) containew_of((p), stwuct gf100_gw_object, object)

stwuct gf100_gw_object {
	stwuct nvkm_object object;
	stwuct gf100_gw_chan *chan;
};

static int
gf100_fewmi_mthd_zbc_cowow(stwuct nvkm_object *object, void *data, u32 size)
{
	stwuct gf100_gw *gw = gf100_gw(nvkm_gw(object->engine));
	union {
		stwuct fewmi_a_zbc_cowow_v0 v0;
	} *awgs = data;
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		switch (awgs->v0.fowmat) {
		case FEWMI_A_ZBC_COWOW_V0_FMT_ZEWO:
		case FEWMI_A_ZBC_COWOW_V0_FMT_UNOWM_ONE:
		case FEWMI_A_ZBC_COWOW_V0_FMT_WF32_GF32_BF32_AF32:
		case FEWMI_A_ZBC_COWOW_V0_FMT_W16_G16_B16_A16:
		case FEWMI_A_ZBC_COWOW_V0_FMT_WN16_GN16_BN16_AN16:
		case FEWMI_A_ZBC_COWOW_V0_FMT_WS16_GS16_BS16_AS16:
		case FEWMI_A_ZBC_COWOW_V0_FMT_WU16_GU16_BU16_AU16:
		case FEWMI_A_ZBC_COWOW_V0_FMT_WF16_GF16_BF16_AF16:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A8W8G8B8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A8WW8GW8BW8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A2B10G10W10:
		case FEWMI_A_ZBC_COWOW_V0_FMT_AU2BU10GU10WU10:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A8B8G8W8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A8BW8GW8WW8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_AN8BN8GN8WN8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_AS8BS8GS8WS8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_AU8BU8GU8WU8:
		case FEWMI_A_ZBC_COWOW_V0_FMT_A2W10G10B10:
		case FEWMI_A_ZBC_COWOW_V0_FMT_BF10GF11WF11:
			wet = gf100_gw_zbc_cowow_get(gw, awgs->v0.fowmat,
							   awgs->v0.ds,
							   awgs->v0.w2);
			if (wet >= 0) {
				awgs->v0.index = wet;
				wetuwn 0;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

static int
gf100_fewmi_mthd_zbc_depth(stwuct nvkm_object *object, void *data, u32 size)
{
	stwuct gf100_gw *gw = gf100_gw(nvkm_gw(object->engine));
	union {
		stwuct fewmi_a_zbc_depth_v0 v0;
	} *awgs = data;
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, fawse))) {
		switch (awgs->v0.fowmat) {
		case FEWMI_A_ZBC_DEPTH_V0_FMT_FP32:
			wet = gf100_gw_zbc_depth_get(gw, awgs->v0.fowmat,
							   awgs->v0.ds,
							   awgs->v0.w2);
			wetuwn (wet >= 0) ? 0 : -ENOSPC;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn wet;
}

static int
gf100_fewmi_mthd(stwuct nvkm_object *object, u32 mthd, void *data, u32 size)
{
	nvif_ioctw(object, "fewmi mthd %08x\n", mthd);
	switch (mthd) {
	case FEWMI_A_ZBC_COWOW:
		wetuwn gf100_fewmi_mthd_zbc_cowow(object, data, size);
	case FEWMI_A_ZBC_DEPTH:
		wetuwn gf100_fewmi_mthd_zbc_depth(object, data, size);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

const stwuct nvkm_object_func
gf100_fewmi = {
	.mthd = gf100_fewmi_mthd,
};

static void
gf100_gw_mthd_set_shadew_exceptions(stwuct nvkm_device *device, u32 data)
{
	nvkm_ww32(device, 0x419e44, data ? 0xffffffff : 0x00000000);
	nvkm_ww32(device, 0x419e4c, data ? 0xffffffff : 0x00000000);
}

static boow
gf100_gw_mthd_sw(stwuct nvkm_device *device, u16 cwass, u32 mthd, u32 data)
{
	switch (cwass & 0x00ff) {
	case 0x97:
	case 0xc0:
		switch (mthd) {
		case 0x1528:
			gf100_gw_mthd_set_shadew_exceptions(device, data);
			wetuwn twue;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const stwuct nvkm_object_func
gf100_gw_object_func = {
};

static int
gf100_gw_object_new(const stwuct nvkm_ocwass *ocwass, void *data, u32 size,
		    stwuct nvkm_object **pobject)
{
	stwuct gf100_gw_chan *chan = gf100_gw_chan(ocwass->pawent);
	stwuct gf100_gw_object *object;

	if (!(object = kzawwoc(sizeof(*object), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pobject = &object->object;

	nvkm_object_ctow(ocwass->base.func ? ocwass->base.func :
			 &gf100_gw_object_func, ocwass, &object->object);
	object->chan = chan;
	wetuwn 0;
}

static int
gf100_gw_object_get(stwuct nvkm_gw *base, int index, stwuct nvkm_scwass *scwass)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	int c = 0;

	whiwe (gw->func->scwass[c].ocwass) {
		if (c++ == index) {
			*scwass = gw->func->scwass[index];
			scwass->ctow = gf100_gw_object_new;
			wetuwn index;
		}
	}

	wetuwn c;
}

/*******************************************************************************
 * PGWAPH context
 ******************************************************************************/

static int
gf100_gw_chan_bind(stwuct nvkm_object *object, stwuct nvkm_gpuobj *pawent,
		   int awign, stwuct nvkm_gpuobj **pgpuobj)
{
	stwuct gf100_gw_chan *chan = gf100_gw_chan(object);
	stwuct gf100_gw *gw = chan->gw;
	int wet, i;

	wet = nvkm_gpuobj_new(gw->base.engine.subdev.device, gw->size,
			      awign, fawse, pawent, pgpuobj);
	if (wet)
		wetuwn wet;

	nvkm_kmap(*pgpuobj);
	fow (i = 0; i < gw->size; i += 4)
		nvkm_wo32(*pgpuobj, i, gw->data[i / 4]);

	if (!gw->fiwmwawe) {
		nvkm_wo32(*pgpuobj, 0x00, chan->mmio_nw / 2);
		nvkm_wo32(*pgpuobj, 0x04, chan->mmio_vma->addw >> 8);
	} ewse {
		nvkm_wo32(*pgpuobj, 0xf4, 0);
		nvkm_wo32(*pgpuobj, 0xf8, 0);
		nvkm_wo32(*pgpuobj, 0x10, chan->mmio_nw / 2);
		nvkm_wo32(*pgpuobj, 0x14, wowew_32_bits(chan->mmio_vma->addw));
		nvkm_wo32(*pgpuobj, 0x18, uppew_32_bits(chan->mmio_vma->addw));
		nvkm_wo32(*pgpuobj, 0x1c, 1);
		nvkm_wo32(*pgpuobj, 0x20, 0);
		nvkm_wo32(*pgpuobj, 0x28, 0);
		nvkm_wo32(*pgpuobj, 0x2c, 0);
	}
	nvkm_done(*pgpuobj);
	wetuwn 0;
}

static void *
gf100_gw_chan_dtow(stwuct nvkm_object *object)
{
	stwuct gf100_gw_chan *chan = gf100_gw_chan(object);

	nvkm_vmm_put(chan->vmm, &chan->mmio_vma);
	nvkm_memowy_unwef(&chan->mmio);

	nvkm_vmm_put(chan->vmm, &chan->attwib_cb);
	nvkm_vmm_put(chan->vmm, &chan->unknown);
	nvkm_vmm_put(chan->vmm, &chan->bundwe_cb);
	nvkm_vmm_put(chan->vmm, &chan->pagepoow);
	nvkm_vmm_unwef(&chan->vmm);
	wetuwn chan;
}

static const stwuct nvkm_object_func
gf100_gw_chan = {
	.dtow = gf100_gw_chan_dtow,
	.bind = gf100_gw_chan_bind,
};

static int
gf100_gw_chan_new(stwuct nvkm_gw *base, stwuct nvkm_chan *fifoch,
		  const stwuct nvkm_ocwass *ocwass,
		  stwuct nvkm_object **pobject)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	stwuct gf100_gw_chan *chan;
	stwuct gf100_vmm_map_v0 awgs = { .pwiv = 1 };
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int wet;

	if (!(chan = kzawwoc(sizeof(*chan), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_object_ctow(&gf100_gw_chan, ocwass, &chan->object);
	chan->gw = gw;
	chan->vmm = nvkm_vmm_wef(fifoch->vmm);
	*pobject = &chan->object;

	/* Map pagepoow. */
	wet = nvkm_vmm_get(chan->vmm, 12, nvkm_memowy_size(gw->pagepoow), &chan->pagepoow);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_map(gw->pagepoow, 0, chan->vmm, chan->pagepoow, &awgs, sizeof(awgs));
	if (wet)
		wetuwn wet;

	/* Map bundwe ciwcuwaw buffew. */
	wet = nvkm_vmm_get(chan->vmm, 12, nvkm_memowy_size(gw->bundwe_cb), &chan->bundwe_cb);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_map(gw->bundwe_cb, 0, chan->vmm, chan->bundwe_cb, &awgs, sizeof(awgs));
	if (wet)
		wetuwn wet;

	/* Map attwibute ciwcuwaw buffew. */
	wet = nvkm_vmm_get(chan->vmm, 12, nvkm_memowy_size(gw->attwib_cb), &chan->attwib_cb);
	if (wet)
		wetuwn wet;

	if (device->cawd_type < GP100) {
		wet = nvkm_memowy_map(gw->attwib_cb, 0, chan->vmm, chan->attwib_cb, NUWW, 0);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = nvkm_memowy_map(gw->attwib_cb, 0, chan->vmm, chan->attwib_cb,
				      &awgs, sizeof(awgs));;
		if (wet)
			wetuwn wet;
	}

	/* Map some context buffew of unknown puwpose. */
	if (gw->func->gwctx->unknown_size) {
		wet = nvkm_vmm_get(chan->vmm, 12, nvkm_memowy_size(gw->unknown), &chan->unknown);
		if (wet)
			wetuwn wet;

		wet = nvkm_memowy_map(gw->unknown, 0, chan->vmm, chan->unknown,
				      &awgs, sizeof(awgs));
		if (wet)
			wetuwn wet;
	}

	/* Genewate gowden context image. */
	mutex_wock(&gw->fecs.mutex);
	if (gw->data == NUWW) {
		wet = gf100_gwctx_genewate(gw, chan, fifoch->inst);
		if (wet) {
			nvkm_ewwow(&base->engine.subdev, "faiwed to constwuct context\n");
			wetuwn wet;
		}
	}
	mutex_unwock(&gw->fecs.mutex);

	/* awwocate memowy fow a "mmio wist" buffew that's used by the HUB
	 * fuc to modify some pew-context wegistew settings on fiwst woad
	 * of the context.
	 */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, 0x1000, 0x100,
			      fawse, &chan->mmio);
	if (wet)
		wetuwn wet;

	wet = nvkm_vmm_get(fifoch->vmm, 12, 0x1000, &chan->mmio_vma);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_map(chan->mmio, 0, fifoch->vmm,
			      chan->mmio_vma, &awgs, sizeof(awgs));
	if (wet)
		wetuwn wet;

	/* finawwy, fiww in the mmio wist and point the context at it */
	nvkm_kmap(chan->mmio);
	gw->func->gwctx->pagepoow(chan, chan->pagepoow->addw);
	gw->func->gwctx->bundwe(chan, chan->bundwe_cb->addw, gw->func->gwctx->bundwe_size);
	gw->func->gwctx->attwib_cb(chan, chan->attwib_cb->addw, gw->func->gwctx->attwib_cb_size(gw));
	gw->func->gwctx->attwib(chan);
	if (gw->func->gwctx->patch_wtc)
		gw->func->gwctx->patch_wtc(chan);
	if (gw->func->gwctx->unknown_size)
		gw->func->gwctx->unknown(chan, chan->unknown->addw, gw->func->gwctx->unknown_size);
	nvkm_done(chan->mmio);
	wetuwn 0;
}

/*******************************************************************************
 * PGWAPH wegistew wists
 ******************************************************************************/

const stwuct gf100_gw_init
gf100_gw_init_main_0[] = {
	{ 0x400080,   1, 0x04, 0x003083c2 },
	{ 0x400088,   1, 0x04, 0x00006fe7 },
	{ 0x40008c,   1, 0x04, 0x00000000 },
	{ 0x400090,   1, 0x04, 0x00000030 },
	{ 0x40013c,   1, 0x04, 0x013901f7 },
	{ 0x400140,   1, 0x04, 0x00000100 },
	{ 0x400144,   1, 0x04, 0x00000000 },
	{ 0x400148,   1, 0x04, 0x00000110 },
	{ 0x400138,   1, 0x04, 0x00000000 },
	{ 0x400130,   2, 0x04, 0x00000000 },
	{ 0x400124,   1, 0x04, 0x00000002 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_fe_0[] = {
	{ 0x40415c,   1, 0x04, 0x00000000 },
	{ 0x404170,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_pwi_0[] = {
	{ 0x404488,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_wstw2d_0[] = {
	{ 0x407808,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_pd_0[] = {
	{ 0x406024,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_ds_0[] = {
	{ 0x405844,   1, 0x04, 0x00ffffff },
	{ 0x405850,   1, 0x04, 0x00000000 },
	{ 0x405908,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_scc_0[] = {
	{ 0x40803c,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_pwop_0[] = {
	{ 0x4184a0,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_gpc_unk_0[] = {
	{ 0x418604,   1, 0x04, 0x00000000 },
	{ 0x418680,   1, 0x04, 0x00000000 },
	{ 0x418714,   1, 0x04, 0x80000000 },
	{ 0x418384,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_setup_0[] = {
	{ 0x418814,   3, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_cwstw_0[] = {
	{ 0x418b04,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_setup_1[] = {
	{ 0x4188c8,   1, 0x04, 0x80000000 },
	{ 0x4188cc,   1, 0x04, 0x00000000 },
	{ 0x4188d0,   1, 0x04, 0x00010000 },
	{ 0x4188d4,   1, 0x04, 0x00000001 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_zcuww_0[] = {
	{ 0x418910,   1, 0x04, 0x00010001 },
	{ 0x418914,   1, 0x04, 0x00000301 },
	{ 0x418918,   1, 0x04, 0x00800000 },
	{ 0x418980,   1, 0x04, 0x77777770 },
	{ 0x418984,   3, 0x04, 0x77777777 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_gpm_0[] = {
	{ 0x418c04,   1, 0x04, 0x00000000 },
	{ 0x418c88,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_gpc_unk_1[] = {
	{ 0x418d00,   1, 0x04, 0x00000000 },
	{ 0x418f08,   1, 0x04, 0x00000000 },
	{ 0x418e00,   1, 0x04, 0x00000050 },
	{ 0x418e08,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_gcc_0[] = {
	{ 0x41900c,   1, 0x04, 0x00000000 },
	{ 0x419018,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_tpccs_0[] = {
	{ 0x419d08,   2, 0x04, 0x00000000 },
	{ 0x419d10,   1, 0x04, 0x00000014 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_tex_0[] = {
	{ 0x419ab0,   1, 0x04, 0x00000000 },
	{ 0x419ab8,   1, 0x04, 0x000000e7 },
	{ 0x419abc,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_pe_0[] = {
	{ 0x41980c,   3, 0x04, 0x00000000 },
	{ 0x419844,   1, 0x04, 0x00000000 },
	{ 0x41984c,   1, 0x04, 0x00005bc5 },
	{ 0x419850,   4, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_w1c_0[] = {
	{ 0x419c98,   1, 0x04, 0x00000000 },
	{ 0x419ca8,   1, 0x04, 0x80000000 },
	{ 0x419cb4,   1, 0x04, 0x00000000 },
	{ 0x419cb8,   1, 0x04, 0x00008bf4 },
	{ 0x419cbc,   1, 0x04, 0x28137606 },
	{ 0x419cc0,   2, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_wwdx_0[] = {
	{ 0x419bd4,   1, 0x04, 0x00800000 },
	{ 0x419bdc,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_tpccs_1[] = {
	{ 0x419d2c,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_mpc_0[] = {
	{ 0x419c0c,   1, 0x04, 0x00000000 },
	{}
};

static const stwuct gf100_gw_init
gf100_gw_init_sm_0[] = {
	{ 0x419e00,   1, 0x04, 0x00000000 },
	{ 0x419ea0,   1, 0x04, 0x00000000 },
	{ 0x419ea4,   1, 0x04, 0x00000100 },
	{ 0x419ea8,   1, 0x04, 0x00001100 },
	{ 0x419eac,   1, 0x04, 0x11100702 },
	{ 0x419eb0,   1, 0x04, 0x00000003 },
	{ 0x419eb4,   4, 0x04, 0x00000000 },
	{ 0x419ec8,   1, 0x04, 0x06060618 },
	{ 0x419ed0,   1, 0x04, 0x0eff0e38 },
	{ 0x419ed4,   1, 0x04, 0x011104f1 },
	{ 0x419edc,   1, 0x04, 0x00000000 },
	{ 0x419f00,   1, 0x04, 0x00000000 },
	{ 0x419f2c,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_be_0[] = {
	{ 0x40880c,   1, 0x04, 0x00000000 },
	{ 0x408910,   9, 0x04, 0x00000000 },
	{ 0x408950,   1, 0x04, 0x00000000 },
	{ 0x408954,   1, 0x04, 0x0000ffff },
	{ 0x408984,   1, 0x04, 0x00000000 },
	{ 0x408988,   1, 0x04, 0x08040201 },
	{ 0x40898c,   1, 0x04, 0x80402010 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_fe_1[] = {
	{ 0x4040f0,   1, 0x04, 0x00000000 },
	{}
};

const stwuct gf100_gw_init
gf100_gw_init_pe_1[] = {
	{ 0x419880,   1, 0x04, 0x00000002 },
	{}
};

static const stwuct gf100_gw_pack
gf100_gw_pack_mmio[] = {
	{ gf100_gw_init_main_0 },
	{ gf100_gw_init_fe_0 },
	{ gf100_gw_init_pwi_0 },
	{ gf100_gw_init_wstw2d_0 },
	{ gf100_gw_init_pd_0 },
	{ gf100_gw_init_ds_0 },
	{ gf100_gw_init_scc_0 },
	{ gf100_gw_init_pwop_0 },
	{ gf100_gw_init_gpc_unk_0 },
	{ gf100_gw_init_setup_0 },
	{ gf100_gw_init_cwstw_0 },
	{ gf100_gw_init_setup_1 },
	{ gf100_gw_init_zcuww_0 },
	{ gf100_gw_init_gpm_0 },
	{ gf100_gw_init_gpc_unk_1 },
	{ gf100_gw_init_gcc_0 },
	{ gf100_gw_init_tpccs_0 },
	{ gf100_gw_init_tex_0 },
	{ gf100_gw_init_pe_0 },
	{ gf100_gw_init_w1c_0 },
	{ gf100_gw_init_wwdx_0 },
	{ gf100_gw_init_tpccs_1 },
	{ gf100_gw_init_mpc_0 },
	{ gf100_gw_init_sm_0 },
	{ gf100_gw_init_be_0 },
	{ gf100_gw_init_fe_1 },
	{ gf100_gw_init_pe_1 },
	{}
};

/*******************************************************************************
 * PGWAPH engine/subdev functions
 ******************************************************************************/

static u32
gf100_gw_ctxsw_inst(stwuct nvkm_gw *gw)
{
	wetuwn nvkm_wd32(gw->engine.subdev.device, 0x409b00);
}

static int
gf100_gw_fecs_ctww_ctxsw(stwuct gf100_gw *gw, u32 mthd)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409804, 0xffffffff);
	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0xffffffff);
	nvkm_ww32(device, 0x409504, mthd);
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x409804);
		if (stat == 0x00000002)
			wetuwn -EIO;
		if (stat == 0x00000001)
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_stawt_ctxsw(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	int wet = 0;

	mutex_wock(&gw->fecs.mutex);
	if (!--gw->fecs.disabwe) {
		if (WAWN_ON(wet = gf100_gw_fecs_ctww_ctxsw(gw, 0x39)))
			gw->fecs.disabwe++;
	}
	mutex_unwock(&gw->fecs.mutex);
	wetuwn wet;
}

static int
gf100_gw_fecs_stop_ctxsw(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	int wet = 0;

	mutex_wock(&gw->fecs.mutex);
	if (!gw->fecs.disabwe++) {
		if (WAWN_ON(wet = gf100_gw_fecs_ctww_ctxsw(gw, 0x38)))
			gw->fecs.disabwe--;
	}
	mutex_unwock(&gw->fecs.mutex);
	wetuwn wet;
}

static int
gf100_gw_fecs_hawt_pipewine(stwuct gf100_gw *gw)
{
	int wet = 0;

	if (gw->fiwmwawe) {
		mutex_wock(&gw->fecs.mutex);
		wet = gf100_gw_fecs_ctww_ctxsw(gw, 0x04);
		mutex_unwock(&gw->fecs.mutex);
	}

	wetuwn wet;
}

int
gf100_gw_fecs_wfi_gowden_save(stwuct gf100_gw *gw, u32 inst)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_mask(device, 0x409800, 0x00000003, 0x00000000);
	nvkm_ww32(device, 0x409500, inst);
	nvkm_ww32(device, 0x409504, 0x00000009);
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x409800);
		if (stat & 0x00000002)
			wetuwn -EIO;
		if (stat & 0x00000001)
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

int
gf100_gw_fecs_bind_pointew(stwuct gf100_gw *gw, u32 inst)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_mask(device, 0x409800, 0x00000030, 0x00000000);
	nvkm_ww32(device, 0x409500, inst);
	nvkm_ww32(device, 0x409504, 0x00000003);
	nvkm_msec(device, 2000,
		u32 stat = nvkm_wd32(device, 0x409800);
		if (stat & 0x00000020)
			wetuwn -EIO;
		if (stat & 0x00000010)
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_set_wegwist_viwtuaw_addwess(stwuct gf100_gw *gw, u64 addw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409810, addw >> 8);
	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000001);
	nvkm_ww32(device, 0x409504, 0x00000032);
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x409800) == 0x00000001)
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_set_wegwist_bind_instance(stwuct gf100_gw *gw, u32 inst)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409810, inst);
	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000001);
	nvkm_ww32(device, 0x409504, 0x00000031);
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x409800) == 0x00000001)
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_discovew_wegwist_image_size(stwuct gf100_gw *gw, u32 *psize)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000001);
	nvkm_ww32(device, 0x409504, 0x00000030);
	nvkm_msec(device, 2000,
		if ((*psize = nvkm_wd32(device, 0x409800)))
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_ewpg_bind(stwuct gf100_gw *gw)
{
	u32 size;
	int wet;

	wet = gf100_gw_fecs_discovew_wegwist_image_size(gw, &size);
	if (wet)
		wetuwn wet;

	/*XXX: We need to awwocate + map the above into PMU's inst bwock,
	 *     which which means we pwobabwy need a pwopew PMU befowe we
	 *     even bothew.
	 */

	wet = gf100_gw_fecs_set_wegwist_bind_instance(gw, 0);
	if (wet)
		wetuwn wet;

	wetuwn gf100_gw_fecs_set_wegwist_viwtuaw_addwess(gw, 0);
}

static int
gf100_gw_fecs_discovew_pm_image_size(stwuct gf100_gw *gw, u32 *psize)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000000);
	nvkm_ww32(device, 0x409504, 0x00000025);
	nvkm_msec(device, 2000,
		if ((*psize = nvkm_wd32(device, 0x409800)))
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_discovew_zcuww_image_size(stwuct gf100_gw *gw, u32 *psize)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000000);
	nvkm_ww32(device, 0x409504, 0x00000016);
	nvkm_msec(device, 2000,
		if ((*psize = nvkm_wd32(device, 0x409800)))
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static int
gf100_gw_fecs_discovew_image_size(stwuct gf100_gw *gw, u32 *psize)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, 0x00000000);
	nvkm_ww32(device, 0x409504, 0x00000010);
	nvkm_msec(device, 2000,
		if ((*psize = nvkm_wd32(device, 0x409800)))
			wetuwn 0;
	);

	wetuwn -ETIMEDOUT;
}

static void
gf100_gw_fecs_set_watchdog_timeout(stwuct gf100_gw *gw, u32 timeout)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x409500, timeout);
	nvkm_ww32(device, 0x409504, 0x00000021);
}

static boow
gf100_gw_chsw_woad(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	if (!gw->fiwmwawe) {
		u32 twace = nvkm_wd32(gw->base.engine.subdev.device, 0x40981c);
		if (twace & 0x00000040)
			wetuwn twue;
	} ewse {
		u32 mthd = nvkm_wd32(gw->base.engine.subdev.device, 0x409808);
		if (mthd & 0x00080000)
			wetuwn twue;
	}
	wetuwn fawse;
}

int
gf100_gw_wops(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	wetuwn (nvkm_wd32(device, 0x409604) & 0x001f0000) >> 16;
}

void
gf100_gw_zbc_init(stwuct gf100_gw *gw)
{
	const u32  zewo[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	const u32   one[] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };
	const u32 f32_0[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000,
			      0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	const u32 f32_1[] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
			      0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	stwuct nvkm_wtc *wtc = gw->base.engine.subdev.device->wtc;
	int index, c = wtc->zbc_cowow_min, d = wtc->zbc_depth_min, s = wtc->zbc_depth_min;

	if (!gw->zbc_cowow[0].fowmat) {
		gf100_gw_zbc_cowow_get(gw, 1,  & zewo[0],   &zewo[4]); c++;
		gf100_gw_zbc_cowow_get(gw, 2,  &  one[0],    &one[4]); c++;
		gf100_gw_zbc_cowow_get(gw, 4,  &f32_0[0],  &f32_0[4]); c++;
		gf100_gw_zbc_cowow_get(gw, 4,  &f32_1[0],  &f32_1[4]); c++;
		gf100_gw_zbc_depth_get(gw, 1, 0x00000000, 0x00000000); d++;
		gf100_gw_zbc_depth_get(gw, 1, 0x3f800000, 0x3f800000); d++;
		if (gw->func->zbc->stenciw_get) {
			gw->func->zbc->stenciw_get(gw, 1, 0x00, 0x00); s++;
			gw->func->zbc->stenciw_get(gw, 1, 0x01, 0x01); s++;
			gw->func->zbc->stenciw_get(gw, 1, 0xff, 0xff); s++;
		}
	}

	fow (index = c; index <= wtc->zbc_cowow_max; index++)
		gw->func->zbc->cweaw_cowow(gw, index);
	fow (index = d; index <= wtc->zbc_depth_max; index++)
		gw->func->zbc->cweaw_depth(gw, index);

	if (gw->func->zbc->cweaw_stenciw) {
		fow (index = s; index <= wtc->zbc_depth_max; index++)
			gw->func->zbc->cweaw_stenciw(gw, index);
	}
}

/**
 * Wait untiw GW goes idwe. GW is considewed idwe if it is disabwed by the
 * MC (0x200) wegistew, ow GW is not busy and a context switch is not in
 * pwogwess.
 */
int
gf100_gw_wait_idwe(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	unsigned wong end_jiffies = jiffies + msecs_to_jiffies(2000);
	boow gw_enabwed, ctxsw_active, gw_busy;

	do {
		/*
		 * wequiwed to make suwe FIFO_ENGINE_STATUS (0x2640) is
		 * up-to-date
		 */
		nvkm_wd32(device, 0x400700);

		gw_enabwed = nvkm_wd32(device, 0x200) & 0x1000;
		ctxsw_active = nvkm_fifo_ctxsw_in_pwogwess(&gw->base.engine);
		gw_busy = nvkm_wd32(device, 0x40060c) & 0x1;

		if (!gw_enabwed || (!gw_busy && !ctxsw_active))
			wetuwn 0;
	} whiwe (time_befowe(jiffies, end_jiffies));

	nvkm_ewwow(subdev,
		   "wait fow idwe timeout (en: %d, ctxsw: %d, busy: %d)\n",
		   gw_enabwed, ctxsw_active, gw_busy);
	wetuwn -EAGAIN;
}

void
gf100_gw_mmio(stwuct gf100_gw *gw, const stwuct gf100_gw_pack *p)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const stwuct gf100_gw_pack *pack;
	const stwuct gf100_gw_init *init;

	pack_fow_each_init(init, pack, p) {
		u32 next = init->addw + init->count * init->pitch;
		u32 addw = init->addw;
		whiwe (addw < next) {
			nvkm_ww32(device, addw, init->data);
			addw += init->pitch;
		}
	}
}

void
gf100_gw_icmd(stwuct gf100_gw *gw, const stwuct gf100_gw_pack *p)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const stwuct gf100_gw_pack *pack;
	const stwuct gf100_gw_init *init;
	u64 data = 0;

	nvkm_ww32(device, 0x400208, 0x80000000);

	pack_fow_each_init(init, pack, p) {
		u32 next = init->addw + init->count * init->pitch;
		u32 addw = init->addw;

		if ((pack == p && init == p->init) || data != init->data) {
			nvkm_ww32(device, 0x400204, init->data);
			if (pack->type == 64)
				nvkm_ww32(device, 0x40020c, uppew_32_bits(init->data));
			data = init->data;
		}

		whiwe (addw < next) {
			nvkm_ww32(device, 0x400200, addw);
			/**
			 * Wait fow GW to go idwe aftew submitting a
			 * GO_IDWE bundwe
			 */
			if ((addw & 0xffff) == 0xe100)
				gf100_gw_wait_idwe(gw);
			nvkm_msec(device, 2000,
				if (!(nvkm_wd32(device, 0x400700) & 0x00000004))
					bweak;
			);
			addw += init->pitch;
		}
	}

	nvkm_ww32(device, 0x400208, 0x00000000);
}

void
gf100_gw_mthd(stwuct gf100_gw *gw, const stwuct gf100_gw_pack *p)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const stwuct gf100_gw_pack *pack;
	const stwuct gf100_gw_init *init;
	u32 data = 0;

	pack_fow_each_init(init, pack, p) {
		u32 ctww = 0x80000000 | pack->type;
		u32 next = init->addw + init->count * init->pitch;
		u32 addw = init->addw;

		if ((pack == p && init == p->init) || data != init->data) {
			nvkm_ww32(device, 0x40448c, init->data);
			data = init->data;
		}

		whiwe (addw < next) {
			nvkm_ww32(device, 0x404488, ctww | (addw << 14));
			addw += init->pitch;
		}
	}
}

u64
gf100_gw_units(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	u64 cfg;

	cfg  = (u32)gw->gpc_nw;
	cfg |= (u32)gw->tpc_totaw << 8;
	cfg |= (u64)gw->wop_nw << 32;

	wetuwn cfg;
}

static const stwuct nvkm_bitfiewd gf100_dispatch_ewwow[] = {
	{ 0x00000001, "INJECTED_BUNDWE_EWWOW" },
	{ 0x00000002, "CWASS_SUBCH_MISMATCH" },
	{ 0x00000004, "SUBCHSW_DUWING_NOTIFY" },
	{}
};

static const stwuct nvkm_bitfiewd gf100_m2mf_ewwow[] = {
	{ 0x00000001, "PUSH_TOO_MUCH_DATA" },
	{ 0x00000002, "PUSH_NOT_ENOUGH_DATA" },
	{}
};

static const stwuct nvkm_bitfiewd gf100_unk6_ewwow[] = {
	{ 0x00000001, "TEMP_TOO_SMAWW" },
	{}
};

static const stwuct nvkm_bitfiewd gf100_ccache_ewwow[] = {
	{ 0x00000001, "INTW" },
	{ 0x00000002, "WDCONST_OOB" },
	{}
};

static const stwuct nvkm_bitfiewd gf100_macwo_ewwow[] = {
	{ 0x00000001, "TOO_FEW_PAWAMS" },
	{ 0x00000002, "TOO_MANY_PAWAMS" },
	{ 0x00000004, "IWWEGAW_OPCODE" },
	{ 0x00000008, "DOUBWE_BWANCH" },
	{ 0x00000010, "WATCHDOG" },
	{}
};

static const stwuct nvkm_bitfiewd gk104_sked_ewwow[] = {
	{ 0x00000040, "CTA_WESUME" },
	{ 0x00000080, "CONSTANT_BUFFEW_SIZE" },
	{ 0x00000200, "WOCAW_MEMOWY_SIZE_POS" },
	{ 0x00000400, "WOCAW_MEMOWY_SIZE_NEG" },
	{ 0x00000800, "WAWP_CSTACK_SIZE" },
	{ 0x00001000, "TOTAW_TEMP_SIZE" },
	{ 0x00002000, "WEGISTEW_COUNT" },
	{ 0x00040000, "TOTAW_THWEADS" },
	{ 0x00100000, "PWOGWAM_OFFSET" },
	{ 0x00200000, "SHAWED_MEMOWY_SIZE" },
	{ 0x00800000, "CTA_THWEAD_DIMENSION_ZEWO" },
	{ 0x01000000, "MEMOWY_WINDOW_OVEWWAP" },
	{ 0x02000000, "SHAWED_CONFIG_TOO_SMAWW" },
	{ 0x04000000, "TOTAW_WEGISTEW_COUNT" },
	{}
};

static const stwuct nvkm_bitfiewd gf100_gpc_wop_ewwow[] = {
	{ 0x00000002, "WT_PITCH_OVEWWUN" },
	{ 0x00000010, "WT_WIDTH_OVEWWUN" },
	{ 0x00000020, "WT_HEIGHT_OVEWWUN" },
	{ 0x00000080, "ZETA_STOWAGE_TYPE_MISMATCH" },
	{ 0x00000100, "WT_STOWAGE_TYPE_MISMATCH" },
	{ 0x00000400, "WT_WINEAW_MISMATCH" },
	{}
};

static void
gf100_gw_twap_gpc_wop(stwuct gf100_gw *gw, int gpc)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	chaw ewwow[128];
	u32 twap[4];

	twap[0] = nvkm_wd32(device, GPC_UNIT(gpc, 0x0420)) & 0x3fffffff;
	twap[1] = nvkm_wd32(device, GPC_UNIT(gpc, 0x0434));
	twap[2] = nvkm_wd32(device, GPC_UNIT(gpc, 0x0438));
	twap[3] = nvkm_wd32(device, GPC_UNIT(gpc, 0x043c));

	nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_gpc_wop_ewwow, twap[0]);

	nvkm_ewwow(subdev, "GPC%d/PWOP twap: %08x [%s] x = %u, y = %u, "
			   "fowmat = %x, stowage type = %x\n",
		   gpc, twap[0], ewwow, twap[1] & 0xffff, twap[1] >> 16,
		   (twap[2] >> 8) & 0x3f, twap[3] & 0xff);
	nvkm_ww32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
}

const stwuct nvkm_enum gf100_mp_wawp_ewwow[] = {
	{ 0x01, "STACK_EWWOW" },
	{ 0x02, "API_STACK_EWWOW" },
	{ 0x03, "WET_EMPTY_STACK_EWWOW" },
	{ 0x04, "PC_WWAP" },
	{ 0x05, "MISAWIGNED_PC" },
	{ 0x06, "PC_OVEWFWOW" },
	{ 0x07, "MISAWIGNED_IMMC_ADDW" },
	{ 0x08, "MISAWIGNED_WEG" },
	{ 0x09, "IWWEGAW_INSTW_ENCODING" },
	{ 0x0a, "IWWEGAW_SPH_INSTW_COMBO" },
	{ 0x0b, "IWWEGAW_INSTW_PAWAM" },
	{ 0x0c, "INVAWID_CONST_ADDW" },
	{ 0x0d, "OOW_WEG" },
	{ 0x0e, "OOW_ADDW" },
	{ 0x0f, "MISAWIGNED_ADDW" },
	{ 0x10, "INVAWID_ADDW_SPACE" },
	{ 0x11, "IWWEGAW_INSTW_PAWAM2" },
	{ 0x12, "INVAWID_CONST_ADDW_WDC" },
	{ 0x13, "GEOMETWY_SM_EWWOW" },
	{ 0x14, "DIVEWGENT" },
	{ 0x15, "WAWP_EXIT" },
	{}
};

const stwuct nvkm_bitfiewd gf100_mp_gwobaw_ewwow[] = {
	{ 0x00000001, "SM_TO_SM_FAUWT" },
	{ 0x00000002, "W1_EWWOW" },
	{ 0x00000004, "MUWTIPWE_WAWP_EWWOWS" },
	{ 0x00000008, "PHYSICAW_STACK_OVEWFWOW" },
	{ 0x00000010, "BPT_INT" },
	{ 0x00000020, "BPT_PAUSE" },
	{ 0x00000040, "SINGWE_STEP_COMPWETE" },
	{ 0x20000000, "ECC_SEC_EWWOW" },
	{ 0x40000000, "ECC_DED_EWWOW" },
	{ 0x80000000, "TIMEOUT" },
	{}
};

void
gf100_gw_twap_mp(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 weww = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x648));
	u32 geww = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x650));
	const stwuct nvkm_enum *wawp;
	chaw gwob[128];

	nvkm_snpwintbf(gwob, sizeof(gwob), gf100_mp_gwobaw_ewwow, geww);
	wawp = nvkm_enum_find(gf100_mp_wawp_ewwow, weww & 0xffff);

	nvkm_ewwow(subdev, "GPC%i/TPC%i/MP twap: "
			   "gwobaw %08x [%s] wawp %04x [%s]\n",
		   gpc, tpc, geww, gwob, weww, wawp ? wawp->name : "");

	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x648), 0x00000000);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x650), geww);
}

static void
gf100_gw_twap_tpc(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x0508));

	if (stat & 0x00000001) {
		u32 twap = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x0224));
		nvkm_ewwow(subdev, "GPC%d/TPC%d/TEX: %08x\n", gpc, tpc, twap);
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x0224), 0xc0000000);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000002) {
		gw->func->twap_mp(gw, gpc, tpc);
		stat &= ~0x00000002;
	}

	if (stat & 0x00000004) {
		u32 twap = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x0084));
		nvkm_ewwow(subdev, "GPC%d/TPC%d/POWY: %08x\n", gpc, tpc, twap);
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x0084), 0xc0000000);
		stat &= ~0x00000004;
	}

	if (stat & 0x00000008) {
		u32 twap = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x048c));
		nvkm_ewwow(subdev, "GPC%d/TPC%d/W1C: %08x\n", gpc, tpc, twap);
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x048c), 0xc0000000);
		stat &= ~0x00000008;
	}

	if (stat & 0x00000010) {
		u32 twap = nvkm_wd32(device, TPC_UNIT(gpc, tpc, 0x0430));
		nvkm_ewwow(subdev, "GPC%d/TPC%d/MPC: %08x\n", gpc, tpc, twap);
		nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x0430), 0xc0000000);
		stat &= ~0x00000010;
	}

	if (stat) {
		nvkm_ewwow(subdev, "GPC%d/TPC%d/%08x: unknown\n", gpc, tpc, stat);
	}
}

static void
gf100_gw_twap_gpc(stwuct gf100_gw *gw, int gpc)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, GPC_UNIT(gpc, 0x2c90));
	int tpc;

	if (stat & 0x00000001) {
		gf100_gw_twap_gpc_wop(gw, gpc);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000002) {
		u32 twap = nvkm_wd32(device, GPC_UNIT(gpc, 0x0900));
		nvkm_ewwow(subdev, "GPC%d/ZCUWW: %08x\n", gpc, twap);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		stat &= ~0x00000002;
	}

	if (stat & 0x00000004) {
		u32 twap = nvkm_wd32(device, GPC_UNIT(gpc, 0x1028));
		nvkm_ewwow(subdev, "GPC%d/CCACHE: %08x\n", gpc, twap);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		stat &= ~0x00000004;
	}

	if (stat & 0x00000008) {
		u32 twap = nvkm_wd32(device, GPC_UNIT(gpc, 0x0824));
		nvkm_ewwow(subdev, "GPC%d/ESETUP: %08x\n", gpc, twap);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		stat &= ~0x00000009;
	}

	fow (tpc = 0; tpc < gw->tpc_nw[gpc]; tpc++) {
		u32 mask = 0x00010000 << tpc;
		if (stat & mask) {
			gf100_gw_twap_tpc(gw, gpc, tpc);
			nvkm_ww32(device, GPC_UNIT(gpc, 0x2c90), mask);
			stat &= ~mask;
		}
	}

	if (stat) {
		nvkm_ewwow(subdev, "GPC%d/%08x: unknown\n", gpc, stat);
	}
}

static void
gf100_gw_twap_intw(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	chaw ewwow[128];
	u32 twap = nvkm_wd32(device, 0x400108);
	int wop, gpc;

	if (twap & 0x00000001) {
		u32 stat = nvkm_wd32(device, 0x404000);

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_dispatch_ewwow,
			       stat & 0x3fffffff);
		nvkm_ewwow(subdev, "DISPATCH %08x [%s]\n", stat, ewwow);
		nvkm_ww32(device, 0x404000, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000001);
		twap &= ~0x00000001;
	}

	if (twap & 0x00000002) {
		u32 stat = nvkm_wd32(device, 0x404600);

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_m2mf_ewwow,
			       stat & 0x3fffffff);
		nvkm_ewwow(subdev, "M2MF %08x [%s]\n", stat, ewwow);

		nvkm_ww32(device, 0x404600, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000002);
		twap &= ~0x00000002;
	}

	if (twap & 0x00000008) {
		u32 stat = nvkm_wd32(device, 0x408030);

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_ccache_ewwow,
			       stat & 0x3fffffff);
		nvkm_ewwow(subdev, "CCACHE %08x [%s]\n", stat, ewwow);
		nvkm_ww32(device, 0x408030, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000008);
		twap &= ~0x00000008;
	}

	if (twap & 0x00000010) {
		u32 stat = nvkm_wd32(device, 0x405840);
		nvkm_ewwow(subdev, "SHADEW %08x, sph: 0x%06x, stage: 0x%02x\n",
			   stat, stat & 0xffffff, (stat >> 24) & 0x3f);
		nvkm_ww32(device, 0x405840, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000010);
		twap &= ~0x00000010;
	}

	if (twap & 0x00000040) {
		u32 stat = nvkm_wd32(device, 0x40601c);

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_unk6_ewwow,
			       stat & 0x3fffffff);
		nvkm_ewwow(subdev, "UNK6 %08x [%s]\n", stat, ewwow);

		nvkm_ww32(device, 0x40601c, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000040);
		twap &= ~0x00000040;
	}

	if (twap & 0x00000080) {
		u32 stat = nvkm_wd32(device, 0x404490);
		u32 pc = nvkm_wd32(device, 0x404494);
		u32 op = nvkm_wd32(device, 0x40449c);

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gf100_macwo_ewwow,
			       stat & 0x1fffffff);
		nvkm_ewwow(subdev, "MACWO %08x [%s], pc: 0x%03x%s, op: 0x%08x\n",
			   stat, ewwow, pc & 0x7ff,
			   (pc & 0x10000000) ? "" : " (invawid)",
			   op);

		nvkm_ww32(device, 0x404490, 0xc0000000);
		nvkm_ww32(device, 0x400108, 0x00000080);
		twap &= ~0x00000080;
	}

	if (twap & 0x00000100) {
		u32 stat = nvkm_wd32(device, 0x407020) & 0x3fffffff;

		nvkm_snpwintbf(ewwow, sizeof(ewwow), gk104_sked_ewwow, stat);
		nvkm_ewwow(subdev, "SKED: %08x [%s]\n", stat, ewwow);

		if (stat)
			nvkm_ww32(device, 0x407020, 0x40000000);
		nvkm_ww32(device, 0x400108, 0x00000100);
		twap &= ~0x00000100;
	}

	if (twap & 0x01000000) {
		u32 stat = nvkm_wd32(device, 0x400118);
		fow (gpc = 0; stat && gpc < gw->gpc_nw; gpc++) {
			u32 mask = 0x00000001 << gpc;
			if (stat & mask) {
				gf100_gw_twap_gpc(gw, gpc);
				nvkm_ww32(device, 0x400118, mask);
				stat &= ~mask;
			}
		}
		nvkm_ww32(device, 0x400108, 0x01000000);
		twap &= ~0x01000000;
	}

	if (twap & 0x02000000) {
		fow (wop = 0; wop < gw->wop_nw; wop++) {
			u32 statz = nvkm_wd32(device, WOP_UNIT(wop, 0x070));
			u32 statc = nvkm_wd32(device, WOP_UNIT(wop, 0x144));
			nvkm_ewwow(subdev, "WOP%d %08x %08x\n",
				 wop, statz, statc);
			nvkm_ww32(device, WOP_UNIT(wop, 0x070), 0xc0000000);
			nvkm_ww32(device, WOP_UNIT(wop, 0x144), 0xc0000000);
		}
		nvkm_ww32(device, 0x400108, 0x02000000);
		twap &= ~0x02000000;
	}

	if (twap) {
		nvkm_ewwow(subdev, "TWAP UNHANDWED %08x\n", twap);
		nvkm_ww32(device, 0x400108, twap);
	}
}

static void
gf100_gw_ctxctw_debug_unit(stwuct gf100_gw *gw, u32 base)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	nvkm_ewwow(subdev, "%06x - done %08x\n", base,
		   nvkm_wd32(device, base + 0x400));
	nvkm_ewwow(subdev, "%06x - stat %08x %08x %08x %08x\n", base,
		   nvkm_wd32(device, base + 0x800),
		   nvkm_wd32(device, base + 0x804),
		   nvkm_wd32(device, base + 0x808),
		   nvkm_wd32(device, base + 0x80c));
	nvkm_ewwow(subdev, "%06x - stat %08x %08x %08x %08x\n", base,
		   nvkm_wd32(device, base + 0x810),
		   nvkm_wd32(device, base + 0x814),
		   nvkm_wd32(device, base + 0x818),
		   nvkm_wd32(device, base + 0x81c));
}

void
gf100_gw_ctxctw_debug(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	u32 gpcnw = nvkm_wd32(device, 0x409604) & 0xffff;
	u32 gpc;

	gf100_gw_ctxctw_debug_unit(gw, 0x409000);
	fow (gpc = 0; gpc < gpcnw; gpc++)
		gf100_gw_ctxctw_debug_unit(gw, 0x502000 + (gpc * 0x8000));
}

static void
gf100_gw_ctxctw_isw(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x409c18);

	if (!gw->fiwmwawe && (stat & 0x00000001)) {
		u32 code = nvkm_wd32(device, 0x409814);
		if (code == E_BAD_FWMTHD) {
			u32 cwass = nvkm_wd32(device, 0x409808);
			u32  addw = nvkm_wd32(device, 0x40980c);
			u32  subc = (addw & 0x00070000) >> 16;
			u32  mthd = (addw & 0x00003ffc);
			u32  data = nvkm_wd32(device, 0x409810);

			nvkm_ewwow(subdev, "FECS MTHD subc %d cwass %04x "
					   "mthd %04x data %08x\n",
				   subc, cwass, mthd, data);
		} ewse {
			nvkm_ewwow(subdev, "FECS ucode ewwow %d\n", code);
		}
		nvkm_ww32(device, 0x409c20, 0x00000001);
		stat &= ~0x00000001;
	}

	if (!gw->fiwmwawe && (stat & 0x00080000)) {
		nvkm_ewwow(subdev, "FECS watchdog timeout\n");
		gf100_gw_ctxctw_debug(gw);
		nvkm_ww32(device, 0x409c20, 0x00080000);
		stat &= ~0x00080000;
	}

	if (stat) {
		nvkm_ewwow(subdev, "FECS %08x\n", stat);
		gf100_gw_ctxctw_debug(gw);
		nvkm_ww32(device, 0x409c20, stat);
	}
}

static iwqwetuwn_t
gf100_gw_intw(stwuct nvkm_inth *inth)
{
	stwuct gf100_gw *gw = containew_of(inth, typeof(*gw), base.engine.subdev.inth);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;
	u64 inst = nvkm_wd32(device, 0x409b00) & 0x0fffffff;
	u32 stat = nvkm_wd32(device, 0x400100);
	u32 addw = nvkm_wd32(device, 0x400704);
	u32 mthd = (addw & 0x00003ffc);
	u32 subc = (addw & 0x00070000) >> 16;
	u32 data = nvkm_wd32(device, 0x400708);
	u32 code = nvkm_wd32(device, 0x400110);
	u32 cwass;
	const chaw *name = "unknown";
	int chid = -1;

	chan = nvkm_chan_get_inst(&gw->base.engine, (u64)inst << 12, &fwags);
	if (chan) {
		name = chan->name;
		chid = chan->id;
	}

	if (device->cawd_type < NV_E0 || subc < 4)
		cwass = nvkm_wd32(device, 0x404200 + (subc * 4));
	ewse
		cwass = 0x0000;

	if (stat & 0x00000001) {
		/*
		 * notifiew intewwupt, onwy needed fow cycwestats
		 * can be safewy ignowed
		 */
		nvkm_ww32(device, 0x400100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000010) {
		if (!gf100_gw_mthd_sw(device, cwass, mthd, data)) {
			nvkm_ewwow(subdev, "IWWEGAW_MTHD ch %d [%010wwx %s] "
				   "subc %d cwass %04x mthd %04x data %08x\n",
				   chid, inst << 12, name, subc,
				   cwass, mthd, data);
		}
		nvkm_ww32(device, 0x400100, 0x00000010);
		stat &= ~0x00000010;
	}

	if (stat & 0x00000020) {
		nvkm_ewwow(subdev, "IWWEGAW_CWASS ch %d [%010wwx %s] "
			   "subc %d cwass %04x mthd %04x data %08x\n",
			   chid, inst << 12, name, subc, cwass, mthd, data);
		nvkm_ww32(device, 0x400100, 0x00000020);
		stat &= ~0x00000020;
	}

	if (stat & 0x00100000) {
		const stwuct nvkm_enum *en =
			nvkm_enum_find(nv50_data_ewwow_names, code);
		nvkm_ewwow(subdev, "DATA_EWWOW %08x [%s] ch %d [%010wwx %s] "
				   "subc %d cwass %04x mthd %04x data %08x\n",
			   code, en ? en->name : "", chid, inst << 12,
			   name, subc, cwass, mthd, data);
		nvkm_ww32(device, 0x400100, 0x00100000);
		stat &= ~0x00100000;
	}

	if (stat & 0x00200000) {
		nvkm_ewwow(subdev, "TWAP ch %d [%010wwx %s]\n",
			   chid, inst << 12, name);
		gf100_gw_twap_intw(gw);
		nvkm_ww32(device, 0x400100, 0x00200000);
		stat &= ~0x00200000;
	}

	if (stat & 0x00080000) {
		gf100_gw_ctxctw_isw(gw);
		nvkm_ww32(device, 0x400100, 0x00080000);
		stat &= ~0x00080000;
	}

	if (stat) {
		nvkm_ewwow(subdev, "intw %08x\n", stat);
		nvkm_ww32(device, 0x400100, stat);
	}

	nvkm_ww32(device, 0x400500, 0x00010001);
	nvkm_chan_put(&chan, fwags);
	wetuwn IWQ_HANDWED;
}

static void
gf100_gw_init_fw(stwuct nvkm_fawcon *fawcon,
		 stwuct nvkm_bwob *code, stwuct nvkm_bwob *data)
{
	nvkm_fawcon_woad_dmem(fawcon, data->data, 0x0, data->size, 0);
	nvkm_fawcon_woad_imem(fawcon, code->data, 0x0, code->size, 0, 0, fawse);
}

static void
gf100_gw_init_csdata(stwuct gf100_gw *gw,
		     const stwuct gf100_gw_pack *pack,
		     u32 fawcon, u32 stawstaw, u32 base)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const stwuct gf100_gw_pack *itew;
	const stwuct gf100_gw_init *init;
	u32 addw = ~0, pwev = ~0, xfew = 0;
	u32 staw, temp;

	nvkm_ww32(device, fawcon + 0x01c0, 0x02000000 + stawstaw);
	staw = nvkm_wd32(device, fawcon + 0x01c4);
	temp = nvkm_wd32(device, fawcon + 0x01c4);
	if (temp > staw)
		staw = temp;
	nvkm_ww32(device, fawcon + 0x01c0, 0x01000000 + staw);

	pack_fow_each_init(init, itew, pack) {
		u32 head = init->addw - base;
		u32 taiw = head + init->count * init->pitch;
		whiwe (head < taiw) {
			if (head != pwev + 4 || xfew >= 32) {
				if (xfew) {
					u32 data = ((--xfew << 26) | addw);
					nvkm_ww32(device, fawcon + 0x01c4, data);
					staw += 4;
				}
				addw = head;
				xfew = 0;
			}
			pwev = head;
			xfew = xfew + 1;
			head = head + init->pitch;
		}
	}

	nvkm_ww32(device, fawcon + 0x01c4, (--xfew << 26) | addw);
	nvkm_ww32(device, fawcon + 0x01c0, 0x01000004 + stawstaw);
	nvkm_ww32(device, fawcon + 0x01c4, staw + 4);
}

/* Initiawize context fwom an extewnaw (secuwe ow not) fiwmwawe */
static int
gf100_gw_init_ctxctw_ext(stwuct gf100_gw *gw)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 wsf_mask = 0;
	int wet;

	/* woad fuc micwocode */
	nvkm_mc_unk260(device, 0);

	/* secuwewy-managed fawcons must be weset using secuwe boot */

	if (!nvkm_acw_managed_fawcon(device, NVKM_ACW_WSF_FECS)) {
		gf100_gw_init_fw(&gw->fecs.fawcon, &gw->fecs.inst,
						   &gw->fecs.data);
	} ewse {
		wsf_mask |= BIT(NVKM_ACW_WSF_FECS);
	}

	if (!nvkm_acw_managed_fawcon(device, NVKM_ACW_WSF_GPCCS)) {
		gf100_gw_init_fw(&gw->gpccs.fawcon, &gw->gpccs.inst,
						    &gw->gpccs.data);
	} ewse {
		wsf_mask |= BIT(NVKM_ACW_WSF_GPCCS);
	}

	if (wsf_mask) {
		wet = nvkm_acw_bootstwap_fawcons(device, wsf_mask);
		if (wet)
			wetuwn wet;
	}

	nvkm_mc_unk260(device, 1);

	/* stawt both of them wunning */
	nvkm_ww32(device, 0x409800, 0x00000000);
	nvkm_ww32(device, 0x41a10c, 0x00000000);
	nvkm_ww32(device, 0x40910c, 0x00000000);

	nvkm_fawcon_stawt(&gw->gpccs.fawcon);
	nvkm_fawcon_stawt(&gw->fecs.fawcon);

	if (nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x409800) & 0x00000001)
			bweak;
	) < 0)
		wetuwn -EBUSY;

	gf100_gw_fecs_set_watchdog_timeout(gw, 0x7fffffff);

	/* Detewmine how much memowy is wequiwed to stowe main context image. */
	wet = gf100_gw_fecs_discovew_image_size(gw, &gw->size);
	if (wet)
		wetuwn wet;

	/* Detewmine how much memowy is wequiwed to stowe ZCUWW image. */
	wet = gf100_gw_fecs_discovew_zcuww_image_size(gw, &gw->size_zcuww);
	if (wet)
		wetuwn wet;

	/* Detewmine how much memowy is wequiwed to stowe PewfMon image. */
	wet = gf100_gw_fecs_discovew_pm_image_size(gw, &gw->size_pm);
	if (wet)
		wetuwn wet;

	/*XXX: We (wikewy) wequiwe PMU suppowt to even bothew with this.
	 *
	 *     Awso, it seems wike not aww GPUs suppowt EWPG.  Twaces I
	 *     have hewe show WM enabwing it on Kepwew/Tuwing, but none
	 *     of the GPUs between those.  NVGPU decides this by PCIID.
	 */
	if (0) {
		wet = gf100_gw_fecs_ewpg_bind(gw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
gf100_gw_init_ctxctw_int(stwuct gf100_gw *gw)
{
	const stwuct gf100_gwctx_func *gwctx = gw->func->gwctx;
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;

	if (!gw->func->fecs.ucode) {
		wetuwn -ENOSYS;
	}

	/* woad HUB micwocode */
	nvkm_mc_unk260(device, 0);
	nvkm_fawcon_woad_dmem(&gw->fecs.fawcon,
			      gw->func->fecs.ucode->data.data, 0x0,
			      gw->func->fecs.ucode->data.size, 0);
	nvkm_fawcon_woad_imem(&gw->fecs.fawcon,
			      gw->func->fecs.ucode->code.data, 0x0,
			      gw->func->fecs.ucode->code.size, 0, 0, fawse);

	/* woad GPC micwocode */
	nvkm_fawcon_woad_dmem(&gw->gpccs.fawcon,
			      gw->func->gpccs.ucode->data.data, 0x0,
			      gw->func->gpccs.ucode->data.size, 0);
	nvkm_fawcon_woad_imem(&gw->gpccs.fawcon,
			      gw->func->gpccs.ucode->code.data, 0x0,
			      gw->func->gpccs.ucode->code.size, 0, 0, fawse);
	nvkm_mc_unk260(device, 1);

	/* woad wegistew wists */
	gf100_gw_init_csdata(gw, gwctx->hub, 0x409000, 0x000, 0x000000);
	gf100_gw_init_csdata(gw, gwctx->gpc_0, 0x41a000, 0x000, 0x418000);
	gf100_gw_init_csdata(gw, gwctx->gpc_1, 0x41a000, 0x000, 0x418000);
	gf100_gw_init_csdata(gw, gwctx->tpc, 0x41a000, 0x004, 0x419800);
	gf100_gw_init_csdata(gw, gwctx->ppc, 0x41a000, 0x008, 0x41be00);

	/* stawt HUB ucode wunning, it'ww init the GPCs */
	nvkm_ww32(device, 0x40910c, 0x00000000);
	nvkm_ww32(device, 0x409100, 0x00000002);
	if (nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x409800) & 0x80000000)
			bweak;
	) < 0) {
		gf100_gw_ctxctw_debug(gw);
		wetuwn -EBUSY;
	}

	gw->size = nvkm_wd32(device, 0x409804);
	wetuwn 0;
}

int
gf100_gw_init_ctxctw(stwuct gf100_gw *gw)
{
	int wet;

	if (gw->fiwmwawe)
		wet = gf100_gw_init_ctxctw_ext(gw);
	ewse
		wet = gf100_gw_init_ctxctw_int(gw);

	wetuwn wet;
}

int
gf100_gw_oneinit_sm_id(stwuct gf100_gw *gw)
{
	int tpc, gpc;

	fow (tpc = 0; tpc < gw->tpc_max; tpc++) {
		fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
			if (tpc < gw->tpc_nw[gpc]) {
				gw->sm[gw->sm_nw].gpc = gpc;
				gw->sm[gw->sm_nw].tpc = tpc;
				gw->sm_nw++;
			}
		}
	}

	wetuwn 0;
}

void
gf100_gw_oneinit_tiwes(stwuct gf100_gw *gw)
{
	static const u8 pwimes[] = {
		3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61
	};
	int init_fwac[GPC_MAX], init_eww[GPC_MAX], wun_eww[GPC_MAX], i, j;
	u32 muw_factow, comm_denom;
	u8  gpc_map[GPC_MAX];
	boow sowted;

	switch (gw->tpc_totaw) {
	case 15: gw->scween_tiwe_wow_offset = 0x06; bweak;
	case 14: gw->scween_tiwe_wow_offset = 0x05; bweak;
	case 13: gw->scween_tiwe_wow_offset = 0x02; bweak;
	case 11: gw->scween_tiwe_wow_offset = 0x07; bweak;
	case 10: gw->scween_tiwe_wow_offset = 0x06; bweak;
	case  7:
	case  5: gw->scween_tiwe_wow_offset = 0x01; bweak;
	case  3: gw->scween_tiwe_wow_offset = 0x02; bweak;
	case  2:
	case  1: gw->scween_tiwe_wow_offset = 0x01; bweak;
	defauwt: gw->scween_tiwe_wow_offset = 0x03;
		fow (i = 0; i < AWWAY_SIZE(pwimes); i++) {
			if (gw->tpc_totaw % pwimes[i]) {
				gw->scween_tiwe_wow_offset = pwimes[i];
				bweak;
			}
		}
		bweak;
	}

	/* Sowt GPCs by TPC count, highest-to-wowest. */
	fow (i = 0; i < gw->gpc_nw; i++)
		gpc_map[i] = i;
	sowted = fawse;

	whiwe (!sowted) {
		fow (sowted = twue, i = 0; i < gw->gpc_nw - 1; i++) {
			if (gw->tpc_nw[gpc_map[i + 1]] >
			    gw->tpc_nw[gpc_map[i + 0]]) {
				u8 swap = gpc_map[i];
				gpc_map[i + 0] = gpc_map[i + 1];
				gpc_map[i + 1] = swap;
				sowted = fawse;
			}
		}
	}

	/* Detewmine tiwe->GPC mapping */
	muw_factow = gw->gpc_nw * gw->tpc_max;
	if (muw_factow & 1)
		muw_factow = 2;
	ewse
		muw_factow = 1;

	comm_denom = gw->gpc_nw * gw->tpc_max * muw_factow;

	fow (i = 0; i < gw->gpc_nw; i++) {
		init_fwac[i] = gw->tpc_nw[gpc_map[i]] * gw->gpc_nw * muw_factow;
		init_eww[i] = i * gw->tpc_max * muw_factow - comm_denom/2;
		wun_eww[i] = init_fwac[i] + init_eww[i];
	}

	fow (i = 0; i < gw->tpc_totaw;) {
		fow (j = 0; j < gw->gpc_nw; j++) {
			if ((wun_eww[j] * 2) >= comm_denom) {
				gw->tiwe[i++] = gpc_map[j];
				wun_eww[j] += init_fwac[j] - comm_denom;
			} ewse {
				wun_eww[j] += init_fwac[j];
			}
		}
	}
}

static int
gf100_gw_oneinit(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_intw *intw = &device->mc->intw;
	enum nvkm_intw_type intw_type = NVKM_INTW_SUBDEV;
	int wet, i, j;

	if (gw->func->oneinit_intw)
		intw = gw->func->oneinit_intw(gw, &intw_type);

	wet = nvkm_inth_add(intw, intw_type, NVKM_INTW_PWIO_NOWMAW, &gw->base.engine.subdev,
			    gf100_gw_intw, &gw->base.engine.subdev.inth);
	if (wet)
		wetuwn wet;

	nvkm_pmu_pgob(device->pmu, fawse);

	gw->wop_nw = gw->func->wops(gw);
	gw->gpc_nw = nvkm_wd32(device, 0x409604) & 0x0000001f;
	fow (i = 0; i < gw->gpc_nw; i++) {
		gw->tpc_nw[i]  = nvkm_wd32(device, GPC_UNIT(i, 0x2608));
		gw->tpc_max = max(gw->tpc_max, gw->tpc_nw[i]);
		gw->tpc_totaw += gw->tpc_nw[i];
		fow (j = 0; j < gw->func->ppc_nw; j++) {
			gw->ppc_tpc_mask[i][j] =
				nvkm_wd32(device, GPC_UNIT(i, 0x0c30 + (j * 4)));
			if (gw->ppc_tpc_mask[i][j] == 0)
				continue;

			gw->ppc_nw[i]++;

			gw->ppc_mask[i] |= (1 << j);
			gw->ppc_tpc_nw[i][j] = hweight8(gw->ppc_tpc_mask[i][j]);
			if (gw->ppc_tpc_min == 0 ||
			    gw->ppc_tpc_min > gw->ppc_tpc_nw[i][j])
				gw->ppc_tpc_min = gw->ppc_tpc_nw[i][j];
			if (gw->ppc_tpc_max < gw->ppc_tpc_nw[i][j])
				gw->ppc_tpc_max = gw->ppc_tpc_nw[i][j];
		}

		gw->ppc_totaw += gw->ppc_nw[i];
	}

	/* Awwocate gwobaw context buffews. */
	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST_SW_WOST,
			      gw->func->gwctx->pagepoow_size, 0x100, fawse, &gw->pagepoow);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST_SW_WOST, gw->func->gwctx->bundwe_size,
			      0x100, fawse, &gw->bundwe_cb);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST_SW_WOST,
			      gw->func->gwctx->attwib_cb_size(gw), 0x1000, fawse, &gw->attwib_cb);
	if (wet)
		wetuwn wet;

	if (gw->func->gwctx->unknown_size) {
		wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, gw->func->gwctx->unknown_size,
				      0x100, fawse, &gw->unknown);
		if (wet)
			wetuwn wet;
	}

	memset(gw->tiwe, 0xff, sizeof(gw->tiwe));
	gw->func->oneinit_tiwes(gw);

	wetuwn gw->func->oneinit_sm_id(gw);
}

static int
gf100_gw_init_(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	stwuct nvkm_subdev *subdev = &base->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	boow weset = device->chipset == 0x137 || device->chipset == 0x138;
	int wet;

	/* On cewtain GP107/GP108 boawds, we twiggew a weiwd issue whewe
	 * GW wiww stop wesponding to PWI accesses aftew we've asked the
	 * SEC2 WTOS to boot the GW fawcons.  This happens with faw mowe
	 * fwequency when cowd-booting a boawd (ie. wetuwning fwom D3).
	 *
	 * The woot cause fow this is not known and has pwoven difficuwt
	 * to isowate, with many avenues being dead-ends.
	 *
	 * A wowkawound was discovewed by Kawow, wheweby putting GW into
	 * weset fow an extended pewiod wight befowe initiawisation
	 * pwevents the pwobwem fwom occuwing.
	 *
	 * XXX: As WM does not wequiwe any such wowkawound, this is mowe
	 *      of a hack than a twue fix.
	 */
	weset = nvkm_boowopt(device->cfgopt, "NvGwWesetWaw", weset);
	if (weset) {
		nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
		nvkm_wd32(device, 0x000200);
		msweep(50);
		nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
		nvkm_wd32(device, 0x000200);
	}

	nvkm_pmu_pgob(gw->base.engine.subdev.device->pmu, fawse);

	wet = nvkm_fawcon_get(&gw->fecs.fawcon, subdev);
	if (wet)
		wetuwn wet;

	wet = nvkm_fawcon_get(&gw->gpccs.fawcon, subdev);
	if (wet)
		wetuwn wet;

	wet = gw->func->init(gw);
	if (wet)
		wetuwn wet;

	nvkm_inth_awwow(&subdev->inth);
	wetuwn 0;
}

static int
gf100_gw_fini(stwuct nvkm_gw *base, boow suspend)
{
	stwuct gf100_gw *gw = gf100_gw(base);
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;

	nvkm_inth_bwock(&subdev->inth);

	nvkm_fawcon_put(&gw->gpccs.fawcon, subdev);
	nvkm_fawcon_put(&gw->fecs.fawcon, subdev);
	wetuwn 0;
}

static void *
gf100_gw_dtow(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);

	kfwee(gw->data);

	nvkm_memowy_unwef(&gw->unknown);
	nvkm_memowy_unwef(&gw->attwib_cb);
	nvkm_memowy_unwef(&gw->bundwe_cb);
	nvkm_memowy_unwef(&gw->pagepoow);

	nvkm_fawcon_dtow(&gw->gpccs.fawcon);
	nvkm_fawcon_dtow(&gw->fecs.fawcon);

	nvkm_bwob_dtow(&gw->fecs.inst);
	nvkm_bwob_dtow(&gw->fecs.data);
	nvkm_bwob_dtow(&gw->gpccs.inst);
	nvkm_bwob_dtow(&gw->gpccs.data);

	vfwee(gw->bundwe64);
	vfwee(gw->bundwe_veid);
	vfwee(gw->bundwe);
	vfwee(gw->method);
	vfwee(gw->sw_ctx);
	vfwee(gw->sw_nonctx);
	vfwee(gw->sw_nonctx1);
	vfwee(gw->sw_nonctx2);
	vfwee(gw->sw_nonctx3);
	vfwee(gw->sw_nonctx4);

	wetuwn gw;
}

static const stwuct nvkm_fawcon_func
gf100_gw_fwcn = {
	.woad_imem = nvkm_fawcon_v1_woad_imem,
	.woad_dmem = nvkm_fawcon_v1_woad_dmem,
	.stawt = nvkm_fawcon_v1_stawt,
};

void
gf100_gw_init_num_tpc_pew_gpc(stwuct gf100_gw *gw, boow pd, boow ds)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int gpc, i, j;
	u32 data;

	fow (gpc = 0, i = 0; i < 4; i++) {
		fow (data = 0, j = 0; j < 8 && gpc < gw->gpc_nw; j++, gpc++)
			data |= gw->tpc_nw[gpc] << (j * 4);
		if (pd)
			nvkm_ww32(device, 0x406028 + (i * 4), data);
		if (ds)
			nvkm_ww32(device, 0x405870 + (i * 4), data);
	}
}

void
gf100_gw_init_400054(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x400054, 0x34ce3464);
}

void
gf100_gw_init_exception2(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x40011c, 0xffffffff);
	nvkm_ww32(device, 0x400134, 0xffffffff);
}

void
gf100_gw_init_wop_exceptions(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int wop;

	fow (wop = 0; wop < gw->wop_nw; wop++) {
		nvkm_ww32(device, WOP_UNIT(wop, 0x144), 0x40000000);
		nvkm_ww32(device, WOP_UNIT(wop, 0x070), 0x40000000);
		nvkm_ww32(device, WOP_UNIT(wop, 0x204), 0xffffffff);
		nvkm_ww32(device, WOP_UNIT(wop, 0x208), 0xffffffff);
	}
}

void
gf100_gw_init_shadew_exceptions(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x644), 0x001ffffe);
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x64c), 0x0000000f);
}

void
gf100_gw_init_tex_hww_esw(stwuct gf100_gw *gw, int gpc, int tpc)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x224), 0xc0000000);
}

void
gf100_gw_init_419eb4(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, 0x419eb4, 0x00001000, 0x00001000);
}

void
gf100_gw_init_419cc0(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int gpc, tpc;

	nvkm_mask(device, 0x419cc0, 0x00000008, 0x00000008);

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		fow (tpc = 0; tpc < gw->tpc_nw[gpc]; tpc++)
			nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x48c), 0xc0000000);
	}
}

void
gf100_gw_init_40601c(stwuct gf100_gw *gw)
{
	nvkm_ww32(gw->base.engine.subdev.device, 0x40601c, 0xc0000000);
}

void
gf100_gw_init_fecs_exceptions(stwuct gf100_gw *gw)
{
	const u32 data = gw->fiwmwawe ? 0x000e0000 : 0x000e0001;
	nvkm_ww32(gw->base.engine.subdev.device, 0x409c24, data);
}

void
gf100_gw_init_gpc_mmu(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	stwuct nvkm_fb *fb = device->fb;

	nvkm_ww32(device, 0x418880, nvkm_wd32(device, 0x100c80) & 0x00000001);
	nvkm_ww32(device, 0x4188a4, 0x03000000);
	nvkm_ww32(device, 0x418888, 0x00000000);
	nvkm_ww32(device, 0x41888c, 0x00000000);
	nvkm_ww32(device, 0x418890, 0x00000000);
	nvkm_ww32(device, 0x418894, 0x00000000);
	nvkm_ww32(device, 0x4188b4, nvkm_memowy_addw(fb->mmu_ww) >> 8);
	nvkm_ww32(device, 0x4188b8, nvkm_memowy_addw(fb->mmu_wd) >> 8);
}

void
gf100_gw_init_num_active_wtcs(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_ww32(device, GPC_BCAST(0x08ac), nvkm_wd32(device, 0x100800));
}

void
gf100_gw_init_zcuww(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	const u32 magicgpc918 = DIV_WOUND_UP(0x00800000, gw->tpc_totaw);
	const u8 tiwe_nw = AWIGN(gw->tpc_totaw, 32);
	u8 bank[GPC_MAX] = {}, gpc, i, j;
	u32 data;

	fow (i = 0; i < tiwe_nw; i += 8) {
		fow (data = 0, j = 0; j < 8 && i + j < gw->tpc_totaw; j++) {
			data |= bank[gw->tiwe[i + j]] << (j * 4);
			bank[gw->tiwe[i + j]]++;
		}
		nvkm_ww32(device, GPC_BCAST(0x0980 + ((i / 8) * 4)), data);
	}

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0914),
			  gw->scween_tiwe_wow_offset << 8 | gw->tpc_nw[gpc]);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0910), 0x00040000 |
							 gw->tpc_totaw);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0918), magicgpc918);
	}

	nvkm_ww32(device, GPC_BCAST(0x1bd4), magicgpc918);
}

void
gf100_gw_init_vsc_stweam_mastew(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	nvkm_mask(device, TPC_UNIT(0, 0, 0x05c), 0x00000001, 0x00000001);
}

static int
gf100_gw_weset(stwuct nvkm_gw *base)
{
	stwuct nvkm_subdev *subdev = &base->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct gf100_gw *gw = gf100_gw(base);

	nvkm_mask(device, 0x400500, 0x00000001, 0x00000000);

	WAWN_ON(gf100_gw_fecs_hawt_pipewine(gw));

	subdev->func->fini(subdev, fawse);
	nvkm_mc_disabwe(device, subdev->type, subdev->inst);
	if (gw->func->gpccs.weset)
		gw->func->gpccs.weset(gw);

	nvkm_mc_enabwe(device, subdev->type, subdev->inst);
	wetuwn subdev->func->init(subdev);
}

int
gf100_gw_init(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;
	int gpc, tpc;

	nvkm_mask(device, 0x400500, 0x00010001, 0x00000000);

	gw->func->init_gpc_mmu(gw);

	if (gw->sw_nonctx1) {
		gf100_gw_mmio(gw, gw->sw_nonctx1);
		gf100_gw_mmio(gw, gw->sw_nonctx2);
		gf100_gw_mmio(gw, gw->sw_nonctx3);
		gf100_gw_mmio(gw, gw->sw_nonctx4);
	} ewse
	if (gw->sw_nonctx) {
		gf100_gw_mmio(gw, gw->sw_nonctx);
	} ewse {
		gf100_gw_mmio(gw, gw->func->mmio);
	}

	gf100_gw_wait_idwe(gw);

	if (gw->func->init_w405a14)
		gw->func->init_w405a14(gw);

	if (gw->func->cwkgate_pack)
		nvkm_thewm_cwkgate_init(device->thewm, gw->func->cwkgate_pack);

	if (gw->func->init_bios)
		gw->func->init_bios(gw);

	gw->func->init_vsc_stweam_mastew(gw);
	gw->func->init_zcuww(gw);
	gw->func->init_num_active_wtcs(gw);
	if (gw->func->init_wop_active_fbps)
		gw->func->init_wop_active_fbps(gw);
	if (gw->func->init_bios_2)
		gw->func->init_bios_2(gw);
	if (gw->func->init_swdx_pes_mask)
		gw->func->init_swdx_pes_mask(gw);
	if (gw->func->init_fs)
		gw->func->init_fs(gw);

	nvkm_ww32(device, 0x400500, 0x00010001);

	nvkm_ww32(device, 0x400100, 0xffffffff);
	nvkm_ww32(device, 0x40013c, 0xffffffff);
	nvkm_ww32(device, 0x400124, 0x00000002);

	gw->func->init_fecs_exceptions(gw);

	if (gw->func->init_40a790)
		gw->func->init_40a790(gw);

	if (gw->func->init_ds_hww_esw_2)
		gw->func->init_ds_hww_esw_2(gw);

	nvkm_ww32(device, 0x404000, 0xc0000000);
	nvkm_ww32(device, 0x404600, 0xc0000000);
	nvkm_ww32(device, 0x408030, 0xc0000000);

	if (gw->func->init_40601c)
		gw->func->init_40601c(gw);

	nvkm_ww32(device, 0x406018, 0xc0000000);
	nvkm_ww32(device, 0x404490, 0xc0000000);

	if (gw->func->init_sked_hww_esw)
		gw->func->init_sked_hww_esw(gw);

	nvkm_ww32(device, 0x405840, 0xc0000000);
	nvkm_ww32(device, 0x405844, 0x00ffffff);

	if (gw->func->init_419cc0)
		gw->func->init_419cc0(gw);
	if (gw->func->init_419eb4)
		gw->func->init_419eb4(gw);
	if (gw->func->init_419c9c)
		gw->func->init_419c9c(gw);

	if (gw->func->init_ppc_exceptions)
		gw->func->init_ppc_exceptions(gw);

	fow (gpc = 0; gpc < gw->gpc_nw; gpc++) {
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0420), 0xc0000000);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0900), 0xc0000000);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x1028), 0xc0000000);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x0824), 0xc0000000);
		fow (tpc = 0; tpc < gw->tpc_nw[gpc]; tpc++) {
			nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x508), 0xffffffff);
			nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x50c), 0xffffffff);
			if (gw->func->init_tex_hww_esw)
				gw->func->init_tex_hww_esw(gw, gpc, tpc);
			nvkm_ww32(device, TPC_UNIT(gpc, tpc, 0x084), 0xc0000000);
			if (gw->func->init_504430)
				gw->func->init_504430(gw, gpc, tpc);
			gw->func->init_shadew_exceptions(gw, gpc, tpc);
		}
		nvkm_ww32(device, GPC_UNIT(gpc, 0x2c90), 0xffffffff);
		nvkm_ww32(device, GPC_UNIT(gpc, 0x2c94), 0xffffffff);
	}

	gw->func->init_wop_exceptions(gw);

	nvkm_ww32(device, 0x400108, 0xffffffff);
	nvkm_ww32(device, 0x400138, 0xffffffff);
	nvkm_ww32(device, 0x400118, 0xffffffff);
	nvkm_ww32(device, 0x400130, 0xffffffff);
	if (gw->func->init_exception2)
		gw->func->init_exception2(gw);

	if (gw->func->init_400054)
		gw->func->init_400054(gw);

	gf100_gw_zbc_init(gw);

	if (gw->func->init_4188a4)
		gw->func->init_4188a4(gw);

	wetuwn gf100_gw_init_ctxctw(gw);
}

void
gf100_gw_fecs_weset(stwuct gf100_gw *gw)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	nvkm_ww32(device, 0x409614, 0x00000070);
	nvkm_usec(device, 10, NVKM_DEWAY);
	nvkm_mask(device, 0x409614, 0x00000700, 0x00000700);
	nvkm_usec(device, 10, NVKM_DEWAY);
	nvkm_wd32(device, 0x409614);
}

#incwude "fuc/hubgf100.fuc3.h"

stwuct gf100_gw_ucode
gf100_gw_fecs_ucode = {
	.code.data = gf100_gwhub_code,
	.code.size = sizeof(gf100_gwhub_code),
	.data.data = gf100_gwhub_data,
	.data.size = sizeof(gf100_gwhub_data),
};

#incwude "fuc/gpcgf100.fuc3.h"

stwuct gf100_gw_ucode
gf100_gw_gpccs_ucode = {
	.code.data = gf100_gwgpc_code,
	.code.size = sizeof(gf100_gwgpc_code),
	.data.data = gf100_gwgpc_data,
	.data.size = sizeof(gf100_gwgpc_data),
};

static int
gf100_gw_nonstaww(stwuct nvkm_gw *base)
{
	stwuct gf100_gw *gw = gf100_gw(base);

	if (gw->func->nonstaww)
		wetuwn gw->func->nonstaww(gw);

	wetuwn -EINVAW;
}

static const stwuct nvkm_gw_func
gf100_gw_ = {
	.dtow = gf100_gw_dtow,
	.oneinit = gf100_gw_oneinit,
	.init = gf100_gw_init_,
	.fini = gf100_gw_fini,
	.nonstaww = gf100_gw_nonstaww,
	.weset = gf100_gw_weset,
	.units = gf100_gw_units,
	.chan_new = gf100_gw_chan_new,
	.object_get = gf100_gw_object_get,
	.chsw_woad = gf100_gw_chsw_woad,
	.ctxsw.pause = gf100_gw_fecs_stop_ctxsw,
	.ctxsw.wesume = gf100_gw_fecs_stawt_ctxsw,
	.ctxsw.inst = gf100_gw_ctxsw_inst,
};

static const stwuct gf100_gw_func
gf100_gw = {
	.oneinit_tiwes = gf100_gw_oneinit_tiwes,
	.oneinit_sm_id = gf100_gw_oneinit_sm_id,
	.init = gf100_gw_init,
	.init_gpc_mmu = gf100_gw_init_gpc_mmu,
	.init_vsc_stweam_mastew = gf100_gw_init_vsc_stweam_mastew,
	.init_zcuww = gf100_gw_init_zcuww,
	.init_num_active_wtcs = gf100_gw_init_num_active_wtcs,
	.init_fecs_exceptions = gf100_gw_init_fecs_exceptions,
	.init_40601c = gf100_gw_init_40601c,
	.init_419cc0 = gf100_gw_init_419cc0,
	.init_419eb4 = gf100_gw_init_419eb4,
	.init_tex_hww_esw = gf100_gw_init_tex_hww_esw,
	.init_shadew_exceptions = gf100_gw_init_shadew_exceptions,
	.init_wop_exceptions = gf100_gw_init_wop_exceptions,
	.init_exception2 = gf100_gw_init_exception2,
	.init_400054 = gf100_gw_init_400054,
	.twap_mp = gf100_gw_twap_mp,
	.mmio = gf100_gw_pack_mmio,
	.fecs.ucode = &gf100_gw_fecs_ucode,
	.fecs.weset = gf100_gw_fecs_weset,
	.gpccs.ucode = &gf100_gw_gpccs_ucode,
	.wops = gf100_gw_wops,
	.gwctx = &gf100_gwctx,
	.zbc = &gf100_gw_zbc,
	.scwass = {
		{ -1, -1, FEWMI_TWOD_A },
		{ -1, -1, FEWMI_MEMOWY_TO_MEMOWY_FOWMAT_A },
		{ -1, -1, FEWMI_A, &gf100_fewmi },
		{ -1, -1, FEWMI_COMPUTE_A },
		{}
	}
};

int
gf100_gw_nofw(stwuct gf100_gw *gw, int vew, const stwuct gf100_gw_fwif *fwif)
{
	gw->fiwmwawe = fawse;
	wetuwn 0;
}

static int
gf100_gw_woad_fw(stwuct gf100_gw *gw, const chaw *name,
		 stwuct nvkm_bwob *bwob)
{
	stwuct nvkm_subdev *subdev = &gw->base.engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const stwuct fiwmwawe *fw;
	chaw f[32];
	int wet;

	snpwintf(f, sizeof(f), "nouveau/nv%02x_%s", device->chipset, name);
	wet = wequest_fiwmwawe(&fw, f, device->dev);
	if (wet) {
		snpwintf(f, sizeof(f), "nouveau/%s", name);
		wet = wequest_fiwmwawe(&fw, f, device->dev);
		if (wet) {
			nvkm_ewwow(subdev, "faiwed to woad %s\n", name);
			wetuwn wet;
		}
	}

	bwob->size = fw->size;
	bwob->data = kmemdup(fw->data, bwob->size, GFP_KEWNEW);
	wewease_fiwmwawe(fw);
	wetuwn (bwob->data != NUWW) ? 0 : -ENOMEM;
}

int
gf100_gw_woad(stwuct gf100_gw *gw, int vew, const stwuct gf100_gw_fwif *fwif)
{
	stwuct nvkm_device *device = gw->base.engine.subdev.device;

	if (!nvkm_boowopt(device->cfgopt, "NvGwUseFW", fawse))
		wetuwn -EINVAW;

	if (gf100_gw_woad_fw(gw, "fuc409c", &gw->fecs.inst) ||
	    gf100_gw_woad_fw(gw, "fuc409d", &gw->fecs.data) ||
	    gf100_gw_woad_fw(gw, "fuc41ac", &gw->gpccs.inst) ||
	    gf100_gw_woad_fw(gw, "fuc41ad", &gw->gpccs.data))
		wetuwn -ENOENT;

	gw->fiwmwawe = twue;
	wetuwn 0;
}

static const stwuct gf100_gw_fwif
gf100_gw_fwif[] = {
	{ -1, gf100_gw_woad, &gf100_gw },
	{ -1, gf100_gw_nofw, &gf100_gw },
	{}
};

int
gf100_gw_new_(const stwuct gf100_gw_fwif *fwif, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	stwuct gf100_gw *gw;
	int wet;

	if (!(gw = kzawwoc(sizeof(*gw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pgw = &gw->base;

	wet = nvkm_gw_ctow(&gf100_gw_, device, type, inst, twue, &gw->base);
	if (wet)
		wetuwn wet;

	fwif = nvkm_fiwmwawe_woad(&gw->base.engine.subdev, fwif, "Gw", gw);
	if (IS_EWW(fwif))
		wetuwn PTW_EWW(fwif);

	gw->func = fwif->func;

	wet = nvkm_fawcon_ctow(&gf100_gw_fwcn, &gw->base.engine.subdev,
			       "fecs", 0x409000, &gw->fecs.fawcon);
	if (wet)
		wetuwn wet;

	mutex_init(&gw->fecs.mutex);

	wet = nvkm_fawcon_ctow(&gf100_gw_fwcn, &gw->base.engine.subdev,
			       "gpccs", 0x41a000, &gw->gpccs.fawcon);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int
gf100_gw_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_gw **pgw)
{
	wetuwn gf100_gw_new_(gf100_gw_fwif, device, type, inst, pgw);
}
