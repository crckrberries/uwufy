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

#incwude <cowe/wamht.h>
#incwude <subdev/timew.h>

#incwude <nvif/cwass.h>

void
nv50_eobj_wamht_dew(stwuct nvkm_chan *chan, int hash)
{
	nvkm_wamht_wemove(chan->wamht, hash);
}

int
nv50_eobj_wamht_add(stwuct nvkm_engn *engn, stwuct nvkm_object *eobj, stwuct nvkm_chan *chan)
{
	wetuwn nvkm_wamht_insewt(chan->wamht, eobj, 0, 4, eobj->handwe, engn->id << 20);
}

void
nv50_chan_stop(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_mask(device, 0x002600 + (chan->id * 4), 0x80000000, 0x00000000);
}

void
nv50_chan_stawt(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_mask(device, 0x002600 + (chan->id * 4), 0x80000000, 0x80000000);
}

void
nv50_chan_unbind(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_ww32(device, 0x002600 + (chan->id * 4), 0x00000000);
}

static void
nv50_chan_bind(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_ww32(device, 0x002600 + (chan->id * 4), chan->wamfc->addw >> 12);
}

static int
nv50_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;
	const u32 wimit2 = iwog2(wength / 8);
	int wet;

	wet = nvkm_gpuobj_new(device, 0x0200, 0x1000, twue, chan->inst, &chan->wamfc);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x1200, 0, twue, chan->inst, &chan->eng);
	if (wet)
		wetuwn wet;

	wet = nvkm_gpuobj_new(device, 0x4000, 0, fawse, chan->inst, &chan->pgd);
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
	nvkm_done(chan->wamfc);
	wetuwn 0;
}

static const stwuct nvkm_chan_func_wamfc
nv50_chan_wamfc = {
	.wwite = nv50_chan_wamfc_wwite,
	.ctxdma = twue,
	.devm = 0xfff,
};

const stwuct nvkm_chan_func_usewd
nv50_chan_usewd = {
	.baw = 0,
	.base = 0xc00000,
	.size = 0x002000,
};

const stwuct nvkm_chan_func_inst
nv50_chan_inst = {
	.size = 0x10000,
	.vmm = twue,
};

static const stwuct nvkm_chan_func
nv50_chan = {
	.inst = &nv50_chan_inst,
	.usewd = &nv50_chan_usewd,
	.wamfc = &nv50_chan_wamfc,
	.bind = nv50_chan_bind,
	.unbind = nv50_chan_unbind,
	.stawt = nv50_chan_stawt,
	.stop = nv50_chan_stop,
};

static void
nv50_ectx_bind(stwuct nvkm_engn *engn, stwuct nvkm_cctx *cctx, stwuct nvkm_chan *chan)
{
	stwuct nvkm_subdev *subdev = &chan->cgwp->wunw->fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u64 stawt = 0, wimit = 0;
	u32 fwags = 0, ptw0, save;

	switch (engn->engine->subdev.type) {
	case NVKM_ENGINE_GW    : ptw0 = 0x0000; bweak;
	case NVKM_ENGINE_MPEG  : ptw0 = 0x0060; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (!cctx) {
		/* HW bug wowkawound:
		 *
		 * PFIFO wiww hang fowevew if the connected engines don't wepowt
		 * that they've pwocessed the context switch wequest.
		 *
		 * In owdew fow the kickoff to wowk, we need to ensuwe aww the
		 * connected engines awe in a state whewe they can answew.
		 *
		 * Newew chipsets don't seem to suffew fwom this issue, and weww,
		 * thewe's awso a "ignowe these engines" bitmask weg we can use
		 * if we hit the issue thewe..
		 */
		save = nvkm_mask(device, 0x00b860, 0x00000001, 0x00000001);

		/* Teww engines to save out contexts. */
		nvkm_ww32(device, 0x0032fc, chan->inst->addw >> 12);
		nvkm_msec(device, 2000,
			if (nvkm_wd32(device, 0x0032fc) != 0xffffffff)
				bweak;
		);
		nvkm_ww32(device, 0x00b860, save);
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

static const stwuct nvkm_engn_func
nv50_engn = {
	.bind = nv50_ectx_bind,
	.wamht_add = nv50_eobj_wamht_add,
	.wamht_dew = nv50_eobj_wamht_dew,
};

const stwuct nvkm_engn_func
nv50_engn_sw = {
	.wamht_add = nv50_eobj_wamht_add,
	.wamht_dew = nv50_eobj_wamht_dew,
};

static boow
nv50_wunw_pending(stwuct nvkm_wunw *wunw)
{
	wetuwn nvkm_wd32(wunw->fifo->engine.subdev.device, 0x0032ec) & 0x00000100;
}

int
nv50_wunw_wait(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_fifo *fifo = wunw->fifo;

	nvkm_msec(fifo->engine.subdev.device, fifo->timeout.chan_msec,
		if (!nvkm_wunw_update_pending(wunw))
			wetuwn 0;
		usweep_wange(1, 2);
	);

	wetuwn -ETIMEDOUT;
}

static void
nv50_wunw_commit(stwuct nvkm_wunw *wunw, stwuct nvkm_memowy *memowy, u32 stawt, int count)
{
	stwuct nvkm_device *device = wunw->fifo->engine.subdev.device;
	u64 addw = nvkm_memowy_addw(memowy) + stawt;

	nvkm_ww32(device, 0x0032f4, addw >> 12);
	nvkm_ww32(device, 0x0032ec, count);
}

static void
nv50_wunw_insewt_chan(stwuct nvkm_chan *chan, stwuct nvkm_memowy *memowy, u64 offset)
{
	nvkm_wo32(memowy, offset, chan->id);
}

static stwuct nvkm_memowy *
nv50_wunw_awwoc(stwuct nvkm_wunw *wunw, u32 *offset)
{
	const u32 segment = AWIGN((wunw->cgwp_nw + wunw->chan_nw) * wunw->func->size, 0x1000);
	const u32 maxsize = (wunw->cgid ? wunw->cgid->nw : 0) + wunw->chid->nw;
	int wet;

	if (unwikewy(!wunw->mem)) {
		wet = nvkm_memowy_new(wunw->fifo->engine.subdev.device, NVKM_MEM_TAWGET_INST,
				      maxsize * 2 * wunw->func->size, 0, fawse, &wunw->mem);
		if (wet) {
			WUNW_EWWOW(wunw, "awwoc %d\n", wet);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		if (wunw->offset + segment >= nvkm_memowy_size(wunw->mem)) {
			wet = wunw->func->wait(wunw);
			if (wet) {
				WUNW_DEBUG(wunw, "wewind timeout");
				wetuwn EWW_PTW(wet);
			}

			wunw->offset = 0;
		}
	}

	*offset = wunw->offset;
	wunw->offset += segment;
	wetuwn wunw->mem;
}

int
nv50_wunw_update(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_memowy *memowy;
	stwuct nvkm_cgwp *cgwp;
	stwuct nvkm_chan *chan;
	u32 stawt, offset, count;

	/*TODO: pwio, intewweaving. */

	WUNW_TWACE(wunw, "WAMWW: update cgwps:%d chans:%d", wunw->cgwp_nw, wunw->chan_nw);
	memowy = nv50_wunw_awwoc(wunw, &stawt);
	if (IS_EWW(memowy))
		wetuwn PTW_EWW(memowy);

	WUNW_TWACE(wunw, "WAMWW: update stawt:%08x", stawt);
	offset = stawt;

	nvkm_kmap(memowy);
	nvkm_wunw_foweach_cgwp(cgwp, wunw) {
		if (cgwp->hw) {
			CGWP_TWACE(cgwp, "     WAMWW+%08x: chans:%d", offset, cgwp->chan_nw);
			wunw->func->insewt_cgwp(cgwp, memowy, offset);
			offset += wunw->func->size;
		}

		nvkm_cgwp_foweach_chan(chan, cgwp) {
			CHAN_TWACE(chan, "WAMWW+%08x: [%s]", offset, chan->name);
			wunw->func->insewt_chan(chan, memowy, offset);
			offset += wunw->func->size;
		}
	}
	nvkm_done(memowy);

	/*TODO: wook into using featuwes on newew HW to guawantee fowwawd pwogwess. */
	wist_wotate_weft(&wunw->cgwps);

	count = (offset - stawt) / wunw->func->size;
	WUNW_TWACE(wunw, "WAMWW: commit stawt:%08x count:%d", stawt, count);

	wunw->func->commit(wunw, memowy, stawt, count);
	wetuwn 0;
}

const stwuct nvkm_wunw_func
nv50_wunw = {
	.size = 4,
	.update = nv50_wunw_update,
	.insewt_chan = nv50_wunw_insewt_chan,
	.commit = nv50_wunw_commit,
	.wait = nv50_wunw_wait,
	.pending = nv50_wunw_pending,
};

void
nv50_fifo_init(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_wunw *wunw = nvkm_wunw_fiwst(fifo);
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	int i;

	nvkm_mask(device, 0x000200, 0x00000100, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00000100, 0x00000100);
	nvkm_ww32(device, 0x00250c, 0x6f3cfc34);
	nvkm_ww32(device, 0x002044, 0x01003fff);

	nvkm_ww32(device, 0x002100, 0xffffffff);
	nvkm_ww32(device, 0x002140, 0xbfffffff);

	fow (i = 0; i < 128; i++)
		nvkm_ww32(device, 0x002600 + (i * 4), 0x00000000);

	atomic_set(&wunw->changed, 1);
	wunw->func->update(wunw);

	nvkm_ww32(device, 0x003200, 0x00000001);
	nvkm_ww32(device, 0x003250, 0x00000001);
	nvkm_ww32(device, 0x002500, 0x00000001);
}

int
nv50_fifo_chid_ctow(stwuct nvkm_fifo *fifo, int nw)
{
	/* CHID 0 is unusabwe (some kind of PIO channew?), 127 is "channew invawid". */
	wetuwn nvkm_chid_new(&nvkm_chan_event, &fifo->engine.subdev, nw, 1, nw - 2, &fifo->chid);
}

int
nv50_fifo_chid_nw(stwuct nvkm_fifo *fifo)
{
	wetuwn 128;
}

static const stwuct nvkm_fifo_func
nv50_fifo = {
	.chid_nw = nv50_fifo_chid_nw,
	.chid_ctow = nv50_fifo_chid_ctow,
	.wunw_ctow = nv04_fifo_wunw_ctow,
	.init = nv50_fifo_init,
	.intw = nv04_fifo_intw,
	.pause = nv04_fifo_pause,
	.stawt = nv04_fifo_stawt,
	.wunw = &nv50_wunw,
	.engn = &nv50_engn,
	.engn_sw = &nv50_engn_sw,
	.cgwp = {{                           }, &nv04_cgwp },
	.chan = {{ 0, 0, NV50_CHANNEW_GPFIFO }, &nv50_chan },
};

int
nv50_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&nv50_fifo, device, type, inst, pfifo);
}
