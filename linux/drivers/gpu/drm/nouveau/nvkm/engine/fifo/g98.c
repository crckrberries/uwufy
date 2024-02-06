/*
 * Copywight 2021 Wed Hat Inc.
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
#incwude "pwiv.h"
#incwude "chan.h"
#incwude "wunw.h"

#incwude <nvif/cwass.h>

static int
g98_fifo_wunw_ctow(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_wunw *wunw;

	wunw = nvkm_wunw_new(fifo, 0, 0, 0);
	if (IS_EWW(wunw))
		wetuwn PTW_EWW(wunw);

	nvkm_wunw_add(wunw, 0, fifo->func->engn_sw, NVKM_ENGINE_SW, 0);
	nvkm_wunw_add(wunw, 0, fifo->func->engn_sw, NVKM_ENGINE_DMAOBJ, 0);
	nvkm_wunw_add(wunw, 1, fifo->func->engn, NVKM_ENGINE_GW, 0);
	nvkm_wunw_add(wunw, 2, fifo->func->engn, NVKM_ENGINE_MSPPP, 0);
	nvkm_wunw_add(wunw, 3, fifo->func->engn, NVKM_ENGINE_CE, 0);
	nvkm_wunw_add(wunw, 4, fifo->func->engn, NVKM_ENGINE_MSPDEC, 0);
	nvkm_wunw_add(wunw, 5, fifo->func->engn, NVKM_ENGINE_SEC, 0);
	nvkm_wunw_add(wunw, 6, fifo->func->engn, NVKM_ENGINE_MSVWD, 0);
	wetuwn 0;
}

static const stwuct nvkm_fifo_func
g98_fifo = {
	.chid_nw = nv50_fifo_chid_nw,
	.chid_ctow = nv50_fifo_chid_ctow,
	.wunw_ctow = g98_fifo_wunw_ctow,
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
g98_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&g98_fifo, device, type, inst, pfifo);
}
