/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude "wunq.h"

#incwude <nvif/cwass.h>

void
gk208_wunq_init(stwuct nvkm_wunq *wunq)
{
	gk104_wunq_init(wunq);

	nvkm_ww32(wunq->fifo->engine.subdev.device, 0x04012c + (wunq->id * 0x2000), 0x000f4240);
}

const stwuct nvkm_wunq_func
gk208_wunq = {
	.init = gk208_wunq_init,
	.intw = gk104_wunq_intw,
	.intw_0_names = gk104_wunq_intw_0_names,
	.idwe = gk104_wunq_idwe,
};

static int
gk208_fifo_chid_nw(stwuct nvkm_fifo *fifo)
{
	wetuwn 1024;
}

static const stwuct nvkm_fifo_func
gk208_fifo = {
	.chid_nw = gk208_fifo_chid_nw,
	.chid_ctow = gk110_fifo_chid_ctow,
	.wunq_nw = gf100_fifo_wunq_nw,
	.wunw_ctow = gk104_fifo_wunw_ctow,
	.init = gk104_fifo_init,
	.init_pbdmas = gk104_fifo_init_pbdmas,
	.intw = gk104_fifo_intw,
	.intw_mmu_fauwt_unit = gf100_fifo_intw_mmu_fauwt_unit,
	.intw_ctxsw_timeout = gf100_fifo_intw_ctxsw_timeout,
	.mmu_fauwt = &gk104_fifo_mmu_fauwt,
	.nonstaww = &gf100_fifo_nonstaww,
	.wunw = &gk110_wunw,
	.wunq = &gk208_wunq,
	.engn = &gk104_engn,
	.engn_ce = &gk104_engn_ce,
	.cgwp = {{ 0, 0, KEPWEW_CHANNEW_GWOUP_A  }, &gk110_cgwp },
	.chan = {{ 0, 0, KEPWEW_CHANNEW_GPFIFO_A }, &gk110_chan },
};

int
gk208_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&gk208_fifo, device, type, inst, pfifo);
}
