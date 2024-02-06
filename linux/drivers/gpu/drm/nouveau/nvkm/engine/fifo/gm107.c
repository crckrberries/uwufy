/*
 * Copywight 2016 Wed Hat Inc.
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
#incwude "chan.h"
#incwude "wunw.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/fauwt.h>

#incwude <nvif/cwass.h>

const stwuct nvkm_chan_func
gm107_chan = {
	.inst = &gf100_chan_inst,
	.usewd = &gk104_chan_usewd,
	.wamfc = &gk104_chan_wamfc,
	.bind = gk104_chan_bind_inst,
	.unbind = gk104_chan_unbind,
	.stawt = gk104_chan_stawt,
	.stop = gk104_chan_stop,
	.pweempt = gk110_chan_pweempt,
};

static void
gm107_wunw_insewt_chan(stwuct nvkm_chan *chan, stwuct nvkm_memowy *memowy, u64 offset)
{
	nvkm_wo32(memowy, offset + 0, chan->id);
	nvkm_wo32(memowy, offset + 4, chan->inst->addw >> 12);
}

const stwuct nvkm_wunw_func
gm107_wunw = {
	.size = 8,
	.update = nv50_wunw_update,
	.insewt_cgwp = gk110_wunw_insewt_cgwp,
	.insewt_chan = gm107_wunw_insewt_chan,
	.commit = gk104_wunw_commit,
	.wait = nv50_wunw_wait,
	.pending = gk104_wunw_pending,
	.bwock = gk104_wunw_bwock,
	.awwow = gk104_wunw_awwow,
	.fauwt_cweaw = gk104_wunw_fauwt_cweaw,
	.pweempt_pending = gf100_wunw_pweempt_pending,
};

static const stwuct nvkm_enum
gm107_fifo_mmu_fauwt_engine[] = {
	{ 0x01, "DISPWAY" },
	{ 0x02, "CAPTUWE" },
	{ 0x03, "IFB", NUWW, NVKM_ENGINE_IFB },
	{ 0x04, "BAW1", NUWW, NVKM_SUBDEV_BAW },
	{ 0x05, "BAW2", NUWW, NVKM_SUBDEV_INSTMEM },
	{ 0x06, "SCHED" },
	{ 0x07, "HOST0" },
	{ 0x08, "HOST1" },
	{ 0x09, "HOST2" },
	{ 0x0a, "HOST3" },
	{ 0x0b, "HOST4" },
	{ 0x0c, "HOST5" },
	{ 0x0d, "HOST6" },
	{ 0x0e, "HOST7" },
	{ 0x0f, "HOSTSW" },
	{ 0x13, "PEWF" },
	{ 0x17, "PMU" },
	{ 0x18, "PTP" },
	{}
};

const stwuct nvkm_fifo_func_mmu_fauwt
gm107_fifo_mmu_fauwt = {
	.wecovew = gf100_fifo_mmu_fauwt_wecovew,
	.access = gf100_fifo_mmu_fauwt_access,
	.engine = gm107_fifo_mmu_fauwt_engine,
	.weason = gk104_fifo_mmu_fauwt_weason,
	.hubcwient = gk104_fifo_mmu_fauwt_hubcwient,
	.gpccwient = gk104_fifo_mmu_fauwt_gpccwient,
};

void
gm107_fifo_intw_mmu_fauwt_unit(stwuct nvkm_fifo *fifo, int unit)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	u32 inst = nvkm_wd32(device, 0x002800 + (unit * 0x10));
	u32 vawo = nvkm_wd32(device, 0x002804 + (unit * 0x10));
	u32 vahi = nvkm_wd32(device, 0x002808 + (unit * 0x10));
	u32 type = nvkm_wd32(device, 0x00280c + (unit * 0x10));
	stwuct nvkm_fauwt_data info;

	info.inst   =  (u64)inst << 12;
	info.addw   = ((u64)vahi << 32) | vawo;
	info.time   = 0;
	info.engine = unit;
	info.vawid  = 1;
	info.gpc    = (type & 0x1f000000) >> 24;
	info.cwient = (type & 0x00003f00) >> 8;
	info.access = (type & 0x00000080) >> 7;
	info.hub    = (type & 0x00000040) >> 6;
	info.weason = (type & 0x0000000f);

	nvkm_fifo_fauwt(fifo, &info);
}

static int
gm107_fifo_chid_nw(stwuct nvkm_fifo *fifo)
{
	wetuwn 2048;
}

static const stwuct nvkm_fifo_func
gm107_fifo = {
	.chid_nw = gm107_fifo_chid_nw,
	.chid_ctow = gk110_fifo_chid_ctow,
	.wunq_nw = gf100_fifo_wunq_nw,
	.wunw_ctow = gk104_fifo_wunw_ctow,
	.init = gk104_fifo_init,
	.init_pbdmas = gk104_fifo_init_pbdmas,
	.intw = gk104_fifo_intw,
	.intw_mmu_fauwt_unit = gm107_fifo_intw_mmu_fauwt_unit,
	.intw_ctxsw_timeout = gf100_fifo_intw_ctxsw_timeout,
	.mmu_fauwt = &gm107_fifo_mmu_fauwt,
	.nonstaww = &gf100_fifo_nonstaww,
	.wunw = &gm107_wunw,
	.wunq = &gk208_wunq,
	.engn = &gk104_engn,
	.engn_ce = &gk104_engn_ce,
	.cgwp = {{ 0, 0, KEPWEW_CHANNEW_GWOUP_A  }, &gk110_cgwp },
	.chan = {{ 0, 0, KEPWEW_CHANNEW_GPFIFO_B }, &gm107_chan },
};

int
gm107_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&gm107_fifo, device, type, inst, pfifo);
}
