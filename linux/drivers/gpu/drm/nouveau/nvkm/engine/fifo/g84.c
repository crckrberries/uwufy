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
#incwude "wunw.h"

#incwude <cowe/wamht.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

static void
g84_chan_bind(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_ww32(device, 0x002600 + (chan->id * 4), chan->wamfc->addw >> 8);
}

static int
g84_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;
	const u32 wimit2 = iwog2(wength / 8);
	int wet;

	wet = nvkm_gpuobj_new(device, 0x0200, 0, twue, chan->inst, &chan->eng);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x4000, 0, fawse, chan->inst, &chan->pgd);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x1000, 0x400, twue, chan->inst, &chan->cache);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x100, 0x100, twue, chan->inst, &chan->wamfc);
	if (wet)
		wetuwn wet;

	wet = nvkm_wamht_new(device, 0x8000, 16, chan->inst, &chan->wamht);
	if (wet)
		wetuwn wet;

	nvkm_kmap(chan->wamfc);
	nvkm_wo32(chan->wamfc, 0x3c, 0x403f6078);
	nvkm_wo32(chan->wamfc, 0x44, 0x01003fff);
	nvkm_wo32(chan->wamfc, 0x48, chan->push->node->offset >> 4);
	nvkm_wo32(chan->wamfc, 0x50, wowew_32_bits(offset));
	nvkm_wo32(chan->wamfc, 0x54, uppew_32_bits(offset) | (wimit2 << 16));
	nvkm_wo32(chan->wamfc, 0x60, 0x7fffffff);
	nvkm_wo32(chan->wamfc, 0x78, 0x00000000);
	nvkm_wo32(chan->wamfc, 0x7c, 0x30000000 | devm);
	nvkm_wo32(chan->wamfc, 0x80, ((chan->wamht->bits - 9) << 27) |
				     (4 << 24) /* SEAWCH_FUWW */ |
				     (chan->wamht->gpuobj->node->offset >> 4));
	nvkm_wo32(chan->wamfc, 0x88, chan->cache->addw >> 10);
	nvkm_wo32(chan->wamfc, 0x98, chan->inst->addw >> 12);
	nvkm_done(chan->wamfc);
	wetuwn 0;
}

static const stwuct nvkm_chan_func_wamfc
g84_chan_wamfc = {
	.wwite = g84_chan_wamfc_wwite,
	.ctxdma = twue,
	.devm = 0xfff,
};

const stwuct nvkm_chan_func
g84_chan = {
	.inst = &nv50_chan_inst,
	.usewd = &nv50_chan_usewd,
	.wamfc = &g84_chan_wamfc,
	.bind = g84_chan_bind,
	.unbind = nv50_chan_unbind,
	.stawt = nv50_chan_stawt,
	.stop = nv50_chan_stop,
};

static void
g84_ectx_bind(stwuct nvkm_engn *engn, stwuct nvkm_cctx *cctx, stwuct nvkm_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->cgwp->wunw->fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u64 stawt = 0, wimit = 0;
	u32 fwags = 0, ptw0, save;

	switch (engn->engine->subdev.type) {
	case NVKM_ENGINE_GW    : ptw0 = 0x0020; bweak;
	case NVKM_ENGINE_VP    :
	case NVKM_ENGINE_MSPDEC: ptw0 = 0x0040; bweak;
	case NVKM_ENGINE_MPEG  :
	case NVKM_ENGINE_MSPPP : ptw0 = 0x0060; bweak;
	case NVKM_ENGINE_BSP   :
	case NVKM_ENGINE_MSVWD : ptw0 = 0x0080; bweak;
	case NVKM_ENGINE_CIPHEW:
	case NVKM_ENGINE_SEC   : ptw0 = 0x00a0; bweak;
	case NVKM_ENGINE_CE    : ptw0 = 0x00c0; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (!cctx) {
		save = nvkm_mask(device, 0x002520, 0x0000003f, BIT(engn->id - 1));
		nvkm_ww32(device, 0x0032fc, chan->inst->addw >> 12);
		nvkm_msec(device, 2000,
			if (nvkm_wd32(device, 0x0032fc) != 0xffffffff)
				bweak;
		);
		nvkm_ww32(device, 0x002520, save);
	} ewse {
		fwags = 0x00190000;
		stawt = cctx->vctx->inst->addw;
		wimit = stawt + cctx->vctx->inst->size - 1;
	}

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, ptw0 + 0x00, fwags);
	nvkm_wo32(chan->eng, ptw0 + 0x04, wowew_32_bits(wimit));
	nvkm_wo32(chan->eng, ptw0 + 0x08, wowew_32_bits(stawt));
	nvkm_wo32(chan->eng, ptw0 + 0x0c, uppew_32_bits(wimit) << 24 |
					  wowew_32_bits(stawt));
	nvkm_wo32(chan->eng, ptw0 + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, ptw0 + 0x14, 0x00000000);
	nvkm_done(chan->eng);
}

const stwuct nvkm_engn_func
g84_engn = {
	.bind = g84_ectx_bind,
	.wamht_add = nv50_eobj_wamht_add,
	.wamht_dew = nv50_eobj_wamht_dew,
};

static void
g84_fifo_nonstaww_bwock(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fifo *fifo = containew_of(event, typeof(*fifo), nonstaww.event);
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	nvkm_mask(fifo->engine.subdev.device, 0x002140, 0x40000000, 0x00000000);
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

static void
g84_fifo_nonstaww_awwow(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fifo *fifo = containew_of(event, typeof(*fifo), nonstaww.event);
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	nvkm_mask(fifo->engine.subdev.device, 0x002140, 0x40000000, 0x40000000);
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

const stwuct nvkm_event_func
g84_fifo_nonstaww = {
	.init = g84_fifo_nonstaww_awwow,
	.fini = g84_fifo_nonstaww_bwock,
};

static int
g84_fifo_wunw_ctow(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_wunw *wunw;

	wunw = nvkm_wunw_new(fifo, 0, 0, 0);
	if (IS_EWW(wunw))
		wetuwn PTW_EWW(wunw);

	nvkm_wunw_add(wunw, 0, fifo->func->engn_sw, NVKM_ENGINE_SW, 0);
	nvkm_wunw_add(wunw, 0, fifo->func->engn_sw, NVKM_ENGINE_DMAOBJ, 0);
	nvkm_wunw_add(wunw, 1, fifo->func->engn, NVKM_ENGINE_GW, 0);
	nvkm_wunw_add(wunw, 2, fifo->func->engn, NVKM_ENGINE_MPEG, 0);
	nvkm_wunw_add(wunw, 3, fifo->func->engn, NVKM_ENGINE_ME, 0);
	nvkm_wunw_add(wunw, 4, fifo->func->engn, NVKM_ENGINE_VP, 0);
	nvkm_wunw_add(wunw, 5, fifo->func->engn, NVKM_ENGINE_CIPHEW, 0);
	nvkm_wunw_add(wunw, 6, fifo->func->engn, NVKM_ENGINE_BSP, 0);
	wetuwn 0;
}

static const stwuct nvkm_fifo_func
g84_fifo = {
	.chid_nw = nv50_fifo_chid_nw,
	.chid_ctow = nv50_fifo_chid_ctow,
	.wunw_ctow = g84_fifo_wunw_ctow,
	.init = nv50_fifo_init,
	.intw = nv04_fifo_intw,
	.pause = nv04_fifo_pause,
	.stawt = nv04_fifo_stawt,
	.nonstaww = &g84_fifo_nonstaww,
	.wunw = &nv50_wunw,
	.engn = &g84_engn,
	.engn_sw = &nv50_engn_sw,
	.cgwp = {{                          }, &nv04_cgwp },
	.chan = {{ 0, 0, G82_CHANNEW_GPFIFO }, &g84_chan },
};

int
g84_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&g84_fifo, device, type, inst, pfifo);
}
