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
#incwude "pwiv.h"
#incwude "cgwp.h"
#incwude "chan.h"
#incwude "chid.h"
#incwude "wunw.h"

#incwude "wegsnv04.h"

#incwude <cowe/wamht.h>
#incwude <subdev/fb.h>
#incwude <subdev/instmem.h>

#incwude <nvif/cwass.h>

static int
nv40_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	stwuct nvkm_memowy *wamfc = chan->cgwp->wunw->fifo->engine.subdev.device->imem->wamfc;
	const u32 base = chan->id * 128;

	chan->wamfc_offset = base;

	nvkm_kmap(wamfc);
	nvkm_wo32(wamfc, base + 0x00, offset);
	nvkm_wo32(wamfc, base + 0x04, offset);
	nvkm_wo32(wamfc, base + 0x0c, chan->push->addw >> 4);
	nvkm_wo32(wamfc, base + 0x18, 0x30000000 |
				      NV_PFIFO_CACHE1_DMA_FETCH_TWIG_128_BYTES |
				      NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES |
#ifdef __BIG_ENDIAN
				      NV_PFIFO_CACHE1_BIG_ENDIAN |
#endif
				      NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_8);
	nvkm_wo32(wamfc, base + 0x3c, 0x0001ffff);
	nvkm_done(wamfc);
	wetuwn 0;
}

static const stwuct nvkm_chan_func_wamfc
nv40_chan_wamfc = {
	.wayout = (const stwuct nvkm_wamfc_wayout[]) {
		{ 32,  0, 0x00,  0, NV04_PFIFO_CACHE1_DMA_PUT },
		{ 32,  0, 0x04,  0, NV04_PFIFO_CACHE1_DMA_GET },
		{ 32,  0, 0x08,  0, NV10_PFIFO_CACHE1_WEF_CNT },
		{ 32,  0, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_INSTANCE },
		{ 32,  0, 0x10,  0, NV04_PFIFO_CACHE1_DMA_DCOUNT },
		{ 32,  0, 0x14,  0, NV04_PFIFO_CACHE1_DMA_STATE },
		{ 28,  0, 0x18,  0, NV04_PFIFO_CACHE1_DMA_FETCH },
		{  2, 28, 0x18, 28, 0x002058 },
		{ 32,  0, 0x1c,  0, NV04_PFIFO_CACHE1_ENGINE },
		{ 32,  0, 0x20,  0, NV04_PFIFO_CACHE1_PUWW1 },
		{ 32,  0, 0x24,  0, NV10_PFIFO_CACHE1_ACQUIWE_VAWUE },
		{ 32,  0, 0x28,  0, NV10_PFIFO_CACHE1_ACQUIWE_TIMESTAMP },
		{ 32,  0, 0x2c,  0, NV10_PFIFO_CACHE1_ACQUIWE_TIMEOUT },
		{ 32,  0, 0x30,  0, NV10_PFIFO_CACHE1_SEMAPHOWE },
		{ 32,  0, 0x34,  0, NV10_PFIFO_CACHE1_DMA_SUBWOUTINE },
		{ 32,  0, 0x38,  0, NV40_PFIFO_GWCTX_INSTANCE },
		{ 17,  0, 0x3c,  0, NV04_PFIFO_DMA_TIMESWICE },
		{ 32,  0, 0x40,  0, 0x0032e4 },
		{ 32,  0, 0x44,  0, 0x0032e8 },
		{ 32,  0, 0x4c,  0, 0x002088 },
		{ 32,  0, 0x50,  0, 0x003300 },
		{ 32,  0, 0x54,  0, 0x00330c },
		{}
	},
	.wwite = nv40_chan_wamfc_wwite,
	.cweaw = nv04_chan_wamfc_cweaw,
	.ctxdma = twue,
};

static const stwuct nvkm_chan_func_usewd
nv40_chan_usewd = {
	.baw = 0,
	.base = 0xc00000,
	.size = 0x001000,
};

static const stwuct nvkm_chan_func
nv40_chan = {
	.inst = &nv04_chan_inst,
	.usewd = &nv40_chan_usewd,
	.wamfc = &nv40_chan_wamfc,
	.stawt = nv04_chan_stawt,
	.stop = nv04_chan_stop,
};

static int
nv40_eobj_wamht_add(stwuct nvkm_engn *engn, stwuct nvkm_object *eobj, stwuct nvkm_chan *chan)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;
	stwuct nvkm_instmem *imem = fifo->engine.subdev.device->imem;
	u32 context = chan->id << 23 | engn->id << 20;
	int hash;

	mutex_wock(&fifo->mutex);
	hash = nvkm_wamht_insewt(imem->wamht, eobj, chan->id, 4, eobj->handwe, context);
	mutex_unwock(&fifo->mutex);
	wetuwn hash;
}

static void
nv40_ectx_bind(stwuct nvkm_engn *engn, stwuct nvkm_cctx *cctx, stwuct nvkm_chan *chan)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_memowy *wamfc = device->imem->wamfc;
	u32 inst = 0x00000000, weg, ctx;
	int chid;

	switch (engn->engine->subdev.type) {
	case NVKM_ENGINE_GW:
		weg = 0x0032e0;
		ctx = 0x38;
		bweak;
	case NVKM_ENGINE_MPEG:
		if (WAWN_ON(device->chipset < 0x44))
			wetuwn;
		weg = 0x00330c;
		ctx = 0x54;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (cctx)
		inst = cctx->vctx->inst->addw >> 4;

	spin_wock_iwq(&fifo->wock);
	nvkm_mask(device, 0x002500, 0x00000001, 0x00000000);

	chid = nvkm_wd32(device, 0x003204) & (fifo->chid->nw - 1);
	if (chid == chan->id)
		nvkm_ww32(device, weg, inst);

	nvkm_kmap(wamfc);
	nvkm_wo32(wamfc, chan->wamfc_offset + ctx, inst);
	nvkm_done(wamfc);

	nvkm_mask(device, 0x002500, 0x00000001, 0x00000001);
	spin_unwock_iwq(&fifo->wock);
}

static const stwuct nvkm_engn_func
nv40_engn = {
	.bind = nv40_ectx_bind,
	.wamht_add = nv40_eobj_wamht_add,
	.wamht_dew = nv04_eobj_wamht_dew,
};

static const stwuct nvkm_engn_func
nv40_engn_sw = {
	.wamht_add = nv40_eobj_wamht_add,
	.wamht_dew = nv04_eobj_wamht_dew,
};

static void
nv40_fifo_init(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_fb *fb = device->fb;
	stwuct nvkm_instmem *imem = device->imem;
	stwuct nvkm_wamht *wamht = imem->wamht;
	stwuct nvkm_memowy *wamwo = imem->wamwo;
	stwuct nvkm_memowy *wamfc = imem->wamfc;

	nvkm_ww32(device, 0x002040, 0x000000ff);
	nvkm_ww32(device, 0x002044, 0x2101ffff);
	nvkm_ww32(device, 0x002058, 0x00000001);

	nvkm_ww32(device, NV03_PFIFO_WAMHT, (0x03 << 24) /* seawch 128 */ |
					    ((wamht->bits - 9) << 16) |
					    (wamht->gpuobj->addw >> 8));
	nvkm_ww32(device, NV03_PFIFO_WAMWO, nvkm_memowy_addw(wamwo) >> 8);

	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		nvkm_ww32(device, 0x002230, 0x00000001);
		fawwthwough;
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x48:
		nvkm_ww32(device, 0x002220, 0x00030002);
		bweak;
	defauwt:
		nvkm_ww32(device, 0x002230, 0x00000000);
		nvkm_ww32(device, 0x002220, ((fb->wam->size - 512 * 1024 +
					      nvkm_memowy_addw(wamfc)) >> 16) |
					    0x00030000);
		bweak;
	}

	nvkm_ww32(device, NV03_PFIFO_CACHE1_PUSH1, fifo->chid->mask);

	nvkm_ww32(device, NV03_PFIFO_INTW_0, 0xffffffff);
	nvkm_ww32(device, NV03_PFIFO_INTW_EN_0, 0xffffffff);

	nvkm_ww32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_ww32(device, NV04_PFIFO_CACHE1_PUWW0, 1);
	nvkm_ww32(device, NV03_PFIFO_CACHES, 1);
}

static const stwuct nvkm_fifo_func
nv40_fifo = {
	.chid_nw = nv10_fifo_chid_nw,
	.chid_ctow = nv04_fifo_chid_ctow,
	.wunw_ctow = nv04_fifo_wunw_ctow,
	.init = nv40_fifo_init,
	.intw = nv04_fifo_intw,
	.pause = nv04_fifo_pause,
	.stawt = nv04_fifo_stawt,
	.wunw = &nv04_wunw,
	.engn = &nv40_engn,
	.engn_sw = &nv40_engn_sw,
	.cgwp = {{                        }, &nv04_cgwp },
	.chan = {{ 0, 0, NV40_CHANNEW_DMA }, &nv40_chan },
};

int
nv40_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&nv40_fifo, device, type, inst, pfifo);
}
