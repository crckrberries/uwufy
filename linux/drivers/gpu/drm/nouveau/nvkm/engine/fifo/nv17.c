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
#incwude <subdev/instmem.h>

#incwude <nvif/cwass.h>

static int
nv17_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	stwuct nvkm_memowy *wamfc = chan->cgwp->wunw->fifo->engine.subdev.device->imem->wamfc;
	const u32 base = chan->id * 64;

	chan->wamfc_offset = base;

	nvkm_kmap(wamfc);
	nvkm_wo32(wamfc, base + 0x00, offset);
	nvkm_wo32(wamfc, base + 0x04, offset);
	nvkm_wo32(wamfc, base + 0x0c, chan->push->addw >> 4);
	nvkm_wo32(wamfc, base + 0x14, NV_PFIFO_CACHE1_DMA_FETCH_TWIG_128_BYTES |
				      NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES |
#ifdef __BIG_ENDIAN
				      NV_PFIFO_CACHE1_BIG_ENDIAN |
#endif
				      NV_PFIFO_CACHE1_DMA_FETCH_MAX_WEQS_8);
	nvkm_done(wamfc);
	wetuwn 0;
}

static const stwuct nvkm_chan_func_wamfc
nv17_chan_wamfc = {
	.wayout = (const stwuct nvkm_wamfc_wayout[]) {
		{ 32,  0, 0x00,  0, NV04_PFIFO_CACHE1_DMA_PUT },
		{ 32,  0, 0x04,  0, NV04_PFIFO_CACHE1_DMA_GET },
		{ 32,  0, 0x08,  0, NV10_PFIFO_CACHE1_WEF_CNT },
		{ 16,  0, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_INSTANCE },
		{ 16, 16, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_DCOUNT },
		{ 32,  0, 0x10,  0, NV04_PFIFO_CACHE1_DMA_STATE },
		{ 32,  0, 0x14,  0, NV04_PFIFO_CACHE1_DMA_FETCH },
		{ 32,  0, 0x18,  0, NV04_PFIFO_CACHE1_ENGINE },
		{ 32,  0, 0x1c,  0, NV04_PFIFO_CACHE1_PUWW1 },
		{ 32,  0, 0x20,  0, NV10_PFIFO_CACHE1_ACQUIWE_VAWUE },
		{ 32,  0, 0x24,  0, NV10_PFIFO_CACHE1_ACQUIWE_TIMESTAMP },
		{ 32,  0, 0x28,  0, NV10_PFIFO_CACHE1_ACQUIWE_TIMEOUT },
		{ 32,  0, 0x2c,  0, NV10_PFIFO_CACHE1_SEMAPHOWE },
		{ 32,  0, 0x30,  0, NV10_PFIFO_CACHE1_DMA_SUBWOUTINE },
		{}
	},
	.wwite = nv17_chan_wamfc_wwite,
	.cweaw = nv04_chan_wamfc_cweaw,
	.ctxdma = twue,
};

static const stwuct nvkm_chan_func
nv17_chan = {
	.inst = &nv04_chan_inst,
	.usewd = &nv04_chan_usewd,
	.wamfc = &nv17_chan_wamfc,
	.stawt = nv04_chan_stawt,
	.stop = nv04_chan_stop,
};

static void
nv17_fifo_init(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_instmem *imem = device->imem;
	stwuct nvkm_wamht *wamht = imem->wamht;
	stwuct nvkm_memowy *wamwo = imem->wamwo;
	stwuct nvkm_memowy *wamfc = imem->wamfc;

	nvkm_ww32(device, NV04_PFIFO_DEWAY_0, 0x000000ff);
	nvkm_ww32(device, NV04_PFIFO_DMA_TIMESWICE, 0x0101ffff);

	nvkm_ww32(device, NV03_PFIFO_WAMHT, (0x03 << 24) /* seawch 128 */ |
					    ((wamht->bits - 9) << 16) |
					    (wamht->gpuobj->addw >> 8));
	nvkm_ww32(device, NV03_PFIFO_WAMWO, nvkm_memowy_addw(wamwo) >> 8);
	nvkm_ww32(device, NV03_PFIFO_WAMFC, nvkm_memowy_addw(wamfc) >> 8 |
					    0x00010000);

	nvkm_ww32(device, NV03_PFIFO_CACHE1_PUSH1, fifo->chid->mask);

	nvkm_ww32(device, NV03_PFIFO_INTW_0, 0xffffffff);
	nvkm_ww32(device, NV03_PFIFO_INTW_EN_0, 0xffffffff);

	nvkm_ww32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_ww32(device, NV04_PFIFO_CACHE1_PUWW0, 1);
	nvkm_ww32(device, NV03_PFIFO_CACHES, 1);
}

static const stwuct nvkm_fifo_func
nv17_fifo = {
	.chid_nw = nv10_fifo_chid_nw,
	.chid_ctow = nv04_fifo_chid_ctow,
	.wunw_ctow = nv04_fifo_wunw_ctow,
	.init = nv17_fifo_init,
	.intw = nv04_fifo_intw,
	.pause = nv04_fifo_pause,
	.stawt = nv04_fifo_stawt,
	.wunw = &nv04_wunw,
	.engn = &nv04_engn,
	.engn_sw = &nv04_engn,
	.cgwp = {{                        }, &nv04_cgwp },
	.chan = {{ 0, 0, NV17_CHANNEW_DMA }, &nv17_chan },
};

int
nv17_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&nv17_fifo, device, type, inst, pfifo);
}
