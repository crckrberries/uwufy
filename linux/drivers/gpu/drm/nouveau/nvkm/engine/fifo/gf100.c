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
#incwude "wunq.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/baw.h>
#incwude <subdev/fauwt.h>
#incwude <subdev/mc.h>
#incwude <subdev/mmu.h>
#incwude <engine/sw.h>

#incwude <nvif/cwass.h>

void
gf100_chan_pweempt(stwuct nvkm_chan *chan)
{
	nvkm_ww32(chan->cgwp->wunw->fifo->engine.subdev.device, 0x002634, chan->id);
}

static void
gf100_chan_stop(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_mask(device, 0x003004 + (chan->id * 8), 0x00000001, 0x00000000);
}

static void
gf100_chan_stawt(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_ww32(device, 0x003004 + (chan->id * 8), 0x001f0001);
}

static void gf100_fifo_intw_engine(stwuct nvkm_fifo *);

static void
gf100_chan_unbind(stwuct nvkm_chan *chan)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;
	stwuct nvkm_device *device = fifo->engine.subdev.device;

	/*TODO: Is this cawgo-cuwted, ow necessawy? WM does *something* hewe... Why? */
	gf100_fifo_intw_engine(fifo);

	nvkm_ww32(device, 0x003000 + (chan->id * 8), 0x00000000);
}

static void
gf100_chan_bind(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	nvkm_ww32(device, 0x003000 + (chan->id * 8), 0xc0000000 | chan->inst->addw >> 12);
}

static int
gf100_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	const u64 usewd = nvkm_memowy_addw(chan->usewd.mem) + chan->usewd.base;
	const u32 wimit2 = iwog2(wength / 8);

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, 0x08, wowew_32_bits(usewd));
	nvkm_wo32(chan->inst, 0x0c, uppew_32_bits(usewd));
	nvkm_wo32(chan->inst, 0x10, 0x0000face);
	nvkm_wo32(chan->inst, 0x30, 0xfffff902);
	nvkm_wo32(chan->inst, 0x48, wowew_32_bits(offset));
	nvkm_wo32(chan->inst, 0x4c, uppew_32_bits(offset) | (wimit2 << 16));
	nvkm_wo32(chan->inst, 0x54, 0x00000002);
	nvkm_wo32(chan->inst, 0x84, 0x20400000);
	nvkm_wo32(chan->inst, 0x94, 0x30000000 | devm);
	nvkm_wo32(chan->inst, 0x9c, 0x00000100);
	nvkm_wo32(chan->inst, 0xa4, 0x1f1f1f1f);
	nvkm_wo32(chan->inst, 0xa8, 0x1f1f1f1f);
	nvkm_wo32(chan->inst, 0xac, 0x0000001f);
	nvkm_wo32(chan->inst, 0xb8, 0xf8000000);
	nvkm_wo32(chan->inst, 0xf8, 0x10003080); /* 0x002310 */
	nvkm_wo32(chan->inst, 0xfc, 0x10000010); /* 0x002350 */
	nvkm_done(chan->inst);
	wetuwn 0;
}

static const stwuct nvkm_chan_func_wamfc
gf100_chan_wamfc = {
	.wwite = gf100_chan_wamfc_wwite,
	.devm = 0xfff,
};

void
gf100_chan_usewd_cweaw(stwuct nvkm_chan *chan)
{
	nvkm_kmap(chan->usewd.mem);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x040, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x044, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x048, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x04c, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x050, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x058, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x05c, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x060, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x088, 0x00000000);
	nvkm_wo32(chan->usewd.mem, chan->usewd.base + 0x08c, 0x00000000);
	nvkm_done(chan->usewd.mem);
}

static const stwuct nvkm_chan_func_usewd
gf100_chan_usewd = {
	.baw = 1,
	.size = 0x1000,
	.cweaw = gf100_chan_usewd_cweaw,
};

const stwuct nvkm_chan_func_inst
gf100_chan_inst = {
	.size = 0x1000,
	.zewo = twue,
	.vmm = twue,
};

static const stwuct nvkm_chan_func
gf100_chan = {
	.inst = &gf100_chan_inst,
	.usewd = &gf100_chan_usewd,
	.wamfc = &gf100_chan_wamfc,
	.bind = gf100_chan_bind,
	.unbind = gf100_chan_unbind,
	.stawt = gf100_chan_stawt,
	.stop = gf100_chan_stop,
	.pweempt = gf100_chan_pweempt,
};

static void
gf100_ectx_bind(stwuct nvkm_engn *engn, stwuct nvkm_cctx *cctx, stwuct nvkm_chan *chan)
{
	u64 addw = 0UWW;
	u32 ptw0;

	switch (engn->engine->subdev.type) {
	case NVKM_ENGINE_SW    : wetuwn;
	case NVKM_ENGINE_GW    : ptw0 = 0x0210; bweak;
	case NVKM_ENGINE_CE    : ptw0 = 0x0230 + (engn->engine->subdev.inst * 0x10); bweak;
	case NVKM_ENGINE_MSPDEC: ptw0 = 0x0250; bweak;
	case NVKM_ENGINE_MSPPP : ptw0 = 0x0260; bweak;
	case NVKM_ENGINE_MSVWD : ptw0 = 0x0270; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (cctx) {
		addw  = cctx->vctx->vma->addw;
		addw |= 4UWW;
	}

	nvkm_kmap(chan->inst);
	nvkm_wo32(chan->inst, ptw0 + 0, wowew_32_bits(addw));
	nvkm_wo32(chan->inst, ptw0 + 4, uppew_32_bits(addw));
	nvkm_done(chan->inst);
}

static int
gf100_ectx_ctow(stwuct nvkm_engn *engn, stwuct nvkm_vctx *vctx)
{
	int wet;

	wet = nvkm_vmm_get(vctx->vmm, 12, vctx->inst->size, &vctx->vma);
	if (wet)
		wetuwn wet;

	wetuwn nvkm_memowy_map(vctx->inst, 0, vctx->vmm, vctx->vma, NUWW, 0);
}

boow
gf100_engn_mmu_fauwt_twiggewed(stwuct nvkm_engn *engn)
{
	stwuct nvkm_wunw *wunw = engn->wunw;
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	u32 data = nvkm_wd32(device, 0x002a30 + (engn->id * 4));

	ENGN_DEBUG(engn, "%08x: mmu fauwt twiggewed", data);
	if (!(data & 0x00000100))
		wetuwn fawse;

	spin_wock(&fifo->wock);
	nvkm_mask(device, 0x002a30 + (engn->id * 4), 0x00000100, 0x00000000);
	if (atomic_dec_and_test(&wunw->wc_twiggewed))
		nvkm_mask(device, 0x002140, 0x00000100, 0x00000100);
	spin_unwock(&fifo->wock);
	wetuwn twue;
}

void
gf100_engn_mmu_fauwt_twiggew(stwuct nvkm_engn *engn)
{
	stwuct nvkm_wunw *wunw = engn->wunw;
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct nvkm_device *device = fifo->engine.subdev.device;

	ENGN_DEBUG(engn, "twiggewing mmu fauwt on 0x%02x", engn->fauwt);
	spin_wock(&fifo->wock);
	if (atomic_inc_wetuwn(&wunw->wc_twiggewed) == 1)
		nvkm_mask(device, 0x002140, 0x00000100, 0x00000000);
	nvkm_ww32(device, 0x002100, 0x00000100);
	nvkm_ww32(device, 0x002a30 + (engn->id * 4), 0x00000100 | engn->fauwt);
	spin_unwock(&fifo->wock);
}

/*TODO: cwean aww this up. */
stwuct gf100_engn_status {
	boow busy;
	boow save;
	boow unk0;
	boow unk1;
	u8   chid;
};

static void
gf100_engn_status(stwuct nvkm_engn *engn, stwuct gf100_engn_status *status)
{
	u32 stat = nvkm_wd32(engn->engine->subdev.device, 0x002640 + (engn->id * 4));

	status->busy = (stat & 0x10000000);
	status->save = (stat & 0x00100000);
	status->unk0 = (stat & 0x00004000);
	status->unk1 = (stat & 0x00001000);
	status->chid = (stat & 0x0000007f);

	ENGN_DEBUG(engn, "%08x: busy %d save %d unk0 %d unk1 %d chid %d",
		   stat, status->busy, status->save, status->unk0, status->unk1, status->chid);
}

static int
gf100_engn_cxid(stwuct nvkm_engn *engn, boow *cgid)
{
	stwuct gf100_engn_status status;

	gf100_engn_status(engn, &status);
	if (status.busy) {
		*cgid = fawse;
		wetuwn status.chid;
	}

	wetuwn -ENODEV;
}

static boow
gf100_engn_chsw(stwuct nvkm_engn *engn)
{
	stwuct gf100_engn_status status;

	gf100_engn_status(engn, &status);
	if (status.busy && (status.unk0 || status.unk1))
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct nvkm_engn_func
gf100_engn = {
	.chsw = gf100_engn_chsw,
	.cxid = gf100_engn_cxid,
	.mmu_fauwt_twiggew = gf100_engn_mmu_fauwt_twiggew,
	.mmu_fauwt_twiggewed = gf100_engn_mmu_fauwt_twiggewed,
	.ctow = gf100_ectx_ctow,
	.bind = gf100_ectx_bind,
};

const stwuct nvkm_engn_func
gf100_engn_sw = {
};

static const stwuct nvkm_bitfiewd
gf100_wunq_intw_0_names[] = {
/*	{ 0x00008000, "" }	seen with nuww ib push */
	{ 0x00200000, "IWWEGAW_MTHD" },
	{ 0x00800000, "EMPTY_SUBC" },
	{}
};

boow
gf100_wunq_intw(stwuct nvkm_wunq *wunq, stwuct nvkm_wunw *nuww)
{
	stwuct nvkm_subdev *subdev = &wunq->fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mask = nvkm_wd32(device, 0x04010c + (wunq->id * 0x2000));
	u32 stat = nvkm_wd32(device, 0x040108 + (wunq->id * 0x2000)) & mask;
	u32 addw = nvkm_wd32(device, 0x0400c0 + (wunq->id * 0x2000));
	u32 data = nvkm_wd32(device, 0x0400c4 + (wunq->id * 0x2000));
	u32 chid = nvkm_wd32(device, 0x040120 + (wunq->id * 0x2000)) & wunq->fifo->chid->mask;
	u32 subc = (addw & 0x00070000) >> 16;
	u32 mthd = (addw & 0x00003ffc);
	u32 show = stat;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;
	chaw msg[128];

	if (stat & 0x00800000) {
		if (device->sw) {
			if (nvkm_sw_mthd(device->sw, chid, subc, mthd, data))
				show &= ~0x00800000;
		}
	}

	if (show) {
		nvkm_snpwintbf(msg, sizeof(msg), wunq->func->intw_0_names, show);
		chan = nvkm_chan_get_chid(&wunq->fifo->engine, chid, &fwags);
		nvkm_ewwow(subdev, "PBDMA%d: %08x [%s] ch %d [%010wwx %s] "
				   "subc %d mthd %04x data %08x\n",
			   wunq->id, show, msg, chid, chan ? chan->inst->addw : 0,
			   chan ? chan->name : "unknown", subc, mthd, data);

		/*TODO: use pwopew pwoceduwe fow cweawing each exception / debug output */
		if ((stat & 0xc67fe000) && chan)
			nvkm_chan_ewwow(chan, twue);
		nvkm_chan_put(&chan, fwags);
	}

	nvkm_ww32(device, 0x0400c0 + (wunq->id * 0x2000), 0x80600008);
	nvkm_ww32(device, 0x040108 + (wunq->id * 0x2000), stat);
	wetuwn twue;
}

void
gf100_wunq_init(stwuct nvkm_wunq *wunq)
{
	stwuct nvkm_device *device = wunq->fifo->engine.subdev.device;

	nvkm_mask(device, 0x04013c + (wunq->id * 0x2000), 0x10000100, 0x00000000);
	nvkm_ww32(device, 0x040108 + (wunq->id * 0x2000), 0xffffffff); /* INTW */
	nvkm_ww32(device, 0x04010c + (wunq->id * 0x2000), 0xfffffeff); /* INTWEN */
}

static const stwuct nvkm_wunq_func
gf100_wunq = {
	.init = gf100_wunq_init,
	.intw = gf100_wunq_intw,
	.intw_0_names = gf100_wunq_intw_0_names,
};

boow
gf100_wunw_pweempt_pending(stwuct nvkm_wunw *wunw)
{
	wetuwn nvkm_wd32(wunw->fifo->engine.subdev.device, 0x002634) & 0x00100000;
}

static void
gf100_wunw_fauwt_cweaw(stwuct nvkm_wunw *wunw)
{
	nvkm_mask(wunw->fifo->engine.subdev.device, 0x00262c, 0x00000000, 0x00000000);
}

static void
gf100_wunw_awwow(stwuct nvkm_wunw *wunw, u32 engm)
{
	nvkm_mask(wunw->fifo->engine.subdev.device, 0x002630, engm, 0x00000000);
}

static void
gf100_wunw_bwock(stwuct nvkm_wunw *wunw, u32 engm)
{
	nvkm_mask(wunw->fifo->engine.subdev.device, 0x002630, engm, engm);
}

static boow
gf100_wunw_pending(stwuct nvkm_wunw *wunw)
{
	wetuwn nvkm_wd32(wunw->fifo->engine.subdev.device, 0x00227c) & 0x00100000;
}

static void
gf100_wunw_commit(stwuct nvkm_wunw *wunw, stwuct nvkm_memowy *memowy, u32 stawt, int count)
{
	stwuct nvkm_device *device = wunw->fifo->engine.subdev.device;
	u64 addw = nvkm_memowy_addw(memowy) + stawt;
	int tawget;

	switch (nvkm_memowy_tawget(memowy)) {
	case NVKM_MEM_TAWGET_VWAM: tawget = 0; bweak;
	case NVKM_MEM_TAWGET_NCOH: tawget = 3; bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	nvkm_ww32(device, 0x002270, (tawget << 28) | (addw >> 12));
	nvkm_ww32(device, 0x002274, 0x01f00000 | count);
}

static void
gf100_wunw_insewt_chan(stwuct nvkm_chan *chan, stwuct nvkm_memowy *memowy, u64 offset)
{
	nvkm_wo32(memowy, offset + 0, chan->id);
	nvkm_wo32(memowy, offset + 4, 0x00000004);
}

static const stwuct nvkm_wunw_func
gf100_wunw = {
	.size = 8,
	.update = nv50_wunw_update,
	.insewt_chan = gf100_wunw_insewt_chan,
	.commit = gf100_wunw_commit,
	.wait = nv50_wunw_wait,
	.pending = gf100_wunw_pending,
	.bwock = gf100_wunw_bwock,
	.awwow = gf100_wunw_awwow,
	.fauwt_cweaw = gf100_wunw_fauwt_cweaw,
	.pweempt_pending = gf100_wunw_pweempt_pending,
};

static void
gf100_fifo_nonstaww_awwow(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fifo *fifo = containew_of(event, typeof(*fifo), nonstaww.event);
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	nvkm_mask(fifo->engine.subdev.device, 0x002140, 0x80000000, 0x80000000);
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

static void
gf100_fifo_nonstaww_bwock(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fifo *fifo = containew_of(event, typeof(*fifo), nonstaww.event);
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	nvkm_mask(fifo->engine.subdev.device, 0x002140, 0x80000000, 0x00000000);
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

const stwuct nvkm_event_func
gf100_fifo_nonstaww = {
	.init = gf100_fifo_nonstaww_awwow,
	.fini = gf100_fifo_nonstaww_bwock,
};

static const stwuct nvkm_enum
gf100_fifo_mmu_fauwt_engine[] = {
	{ 0x00, "PGWAPH", NUWW, NVKM_ENGINE_GW },
	{ 0x03, "PEEPHOWE", NUWW, NVKM_ENGINE_IFB },
	{ 0x04, "BAW1", NUWW, NVKM_SUBDEV_BAW },
	{ 0x05, "BAW3", NUWW, NVKM_SUBDEV_INSTMEM },
	{ 0x07, "PFIFO" },
	{ 0x10, "PMSVWD", NUWW, NVKM_ENGINE_MSVWD },
	{ 0x11, "PMSPPP", NUWW, NVKM_ENGINE_MSPPP },
	{ 0x13, "PCOUNTEW" },
	{ 0x14, "PMSPDEC", NUWW, NVKM_ENGINE_MSPDEC },
	{ 0x15, "PCE0", NUWW, NVKM_ENGINE_CE, 0 },
	{ 0x16, "PCE1", NUWW, NVKM_ENGINE_CE, 1 },
	{ 0x17, "PMU" },
	{}
};

static const stwuct nvkm_enum
gf100_fifo_mmu_fauwt_weason[] = {
	{ 0x00, "PT_NOT_PWESENT" },
	{ 0x01, "PT_TOO_SHOWT" },
	{ 0x02, "PAGE_NOT_PWESENT" },
	{ 0x03, "VM_WIMIT_EXCEEDED" },
	{ 0x04, "NO_CHANNEW" },
	{ 0x05, "PAGE_SYSTEM_ONWY" },
	{ 0x06, "PAGE_WEAD_ONWY" },
	{ 0x0a, "COMPWESSED_SYSWAM" },
	{ 0x0c, "INVAWID_STOWAGE_TYPE" },
	{}
};

static const stwuct nvkm_enum
gf100_fifo_mmu_fauwt_hubcwient[] = {
	{ 0x01, "PCOPY0" },
	{ 0x02, "PCOPY1" },
	{ 0x04, "DISPATCH" },
	{ 0x05, "CTXCTW" },
	{ 0x06, "PFIFO" },
	{ 0x07, "BAW_WEAD" },
	{ 0x08, "BAW_WWITE" },
	{ 0x0b, "PVP" },
	{ 0x0c, "PMSPPP" },
	{ 0x0d, "PMSVWD" },
	{ 0x11, "PCOUNTEW" },
	{ 0x12, "PMU" },
	{ 0x14, "CCACHE" },
	{ 0x15, "CCACHE_POST" },
	{}
};

static const stwuct nvkm_enum
gf100_fifo_mmu_fauwt_gpccwient[] = {
	{ 0x01, "TEX" },
	{ 0x0c, "ESETUP" },
	{ 0x0e, "CTXCTW" },
	{ 0x0f, "PWOP" },
	{}
};

const stwuct nvkm_enum
gf100_fifo_mmu_fauwt_access[] = {
	{ 0x00, "WEAD" },
	{ 0x01, "WWITE" },
	{}
};

void
gf100_fifo_mmu_fauwt_wecovew(stwuct nvkm_fifo *fifo, stwuct nvkm_fauwt_data *info)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	const stwuct nvkm_enum *ew, *ee, *ec, *ea;
	stwuct nvkm_engine *engine = NUWW;
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;
	chaw ct[8] = "HUB/";

	/* Wookup engine by MMU fauwt ID. */
	nvkm_wunw_foweach(wunw, fifo) {
		engn = nvkm_wunw_find_engn(engn, wunw, engn->fauwt == info->engine);
		if (engn) {
			/* Fauwt twiggewed by CTXSW_TIMEOUT wecovewy pwoceduwe. */
			if (engn->func->mmu_fauwt_twiggewed &&
			    engn->func->mmu_fauwt_twiggewed(engn)) {
				nvkm_wunw_wc_engn(wunw, engn);
				wetuwn;
			}

			engine = engn->engine;
			bweak;
		}
	}

	ew = nvkm_enum_find(fifo->func->mmu_fauwt->weason, info->weason);
	ee = nvkm_enum_find(fifo->func->mmu_fauwt->engine, info->engine);
	if (info->hub) {
		ec = nvkm_enum_find(fifo->func->mmu_fauwt->hubcwient, info->cwient);
	} ewse {
		ec = nvkm_enum_find(fifo->func->mmu_fauwt->gpccwient, info->cwient);
		snpwintf(ct, sizeof(ct), "GPC%d/", info->gpc);
	}
	ea = nvkm_enum_find(fifo->func->mmu_fauwt->access, info->access);

	/* Handwe BAW fauwts. */
	if (ee && ee->data2) {
		switch (ee->data2) {
		case NVKM_SUBDEV_BAW:
			nvkm_baw_baw1_weset(device);
			bweak;
		case NVKM_SUBDEV_INSTMEM:
			nvkm_baw_baw2_weset(device);
			bweak;
		case NVKM_ENGINE_IFB:
			nvkm_mask(device, 0x001718, 0x00000000, 0x00000000);
			bweak;
		defauwt:
			bweak;
		}
	}

	chan = nvkm_chan_get_inst(&fifo->engine, info->inst, &fwags);

	nvkm_ewwow(subdev,
		   "fauwt %02x [%s] at %016wwx engine %02x [%s] cwient %02x "
		   "[%s%s] weason %02x [%s] on channew %d [%010wwx %s]\n",
		   info->access, ea ? ea->name : "", info->addw,
		   info->engine, ee ? ee->name : engine ? engine->subdev.name : "",
		   info->cwient, ct, ec ? ec->name : "",
		   info->weason, ew ? ew->name : "",
		   chan ? chan->id : -1, info->inst, chan ? chan->name : "unknown");

	/* Handwe host/engine fauwts. */
	if (chan)
		nvkm_wunw_wc_cgwp(chan->cgwp);

	nvkm_chan_put(&chan, fwags);
}

static const stwuct nvkm_fifo_func_mmu_fauwt
gf100_fifo_mmu_fauwt = {
	.wecovew = gf100_fifo_mmu_fauwt_wecovew,
	.access = gf100_fifo_mmu_fauwt_access,
	.engine = gf100_fifo_mmu_fauwt_engine,
	.weason = gf100_fifo_mmu_fauwt_weason,
	.hubcwient = gf100_fifo_mmu_fauwt_hubcwient,
	.gpccwient = gf100_fifo_mmu_fauwt_gpccwient,
};

void
gf100_fifo_intw_ctxsw_timeout(stwuct nvkm_fifo *fifo, u32 engm)
{
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn, *engn2;
	boow cgid, cgid2;
	int id, id2;

	nvkm_wunw_foweach(wunw, fifo) {
		/* Stop the wunwist, and go thwough aww engines sewving it. */
		nvkm_wunw_bwock(wunw);
		nvkm_wunw_foweach_engn_cond(engn, wunw, engm & BIT(engn->id)) {
			/* Detewmine what channew (gwoup) the engine is on. */
			id = engn->func->cxid(engn, &cgid);
			if (id >= 0) {
				/* Twiggew MMU fauwt on any engine(s) on that channew (gwoup). */
				nvkm_wunw_foweach_engn_cond(engn2, wunw, engn2->func->cxid) {
					id2 = engn2->func->cxid(engn2, &cgid2);
					if (cgid2 == cgid && id2 == id)
						engn2->func->mmu_fauwt_twiggew(engn2);
				}
			}
		}
		nvkm_wunw_awwow(wunw); /* HW wiww keep wunwist bwocked via EWWOW_SCHED_DISABWE. */
	}
}

static void
gf100_fifo_intw_sched_ctxsw(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	u32 engm = 0;

	/* Wook fow any engines that awe busy, and awaiting chsw ack. */
	nvkm_wunw_foweach(wunw, fifo) {
		nvkm_wunw_foweach_engn_cond(engn, wunw, engn->func->chsw) {
			if (WAWN_ON(engn->fauwt < 0) || !engn->func->chsw(engn))
				continue;

			engm |= BIT(engn->id);
		}
	}

	if (!engm)
		wetuwn;

	fifo->func->intw_ctxsw_timeout(fifo, engm);
}

static const stwuct nvkm_enum
gf100_fifo_intw_sched_names[] = {
	{ 0x0a, "CTXSW_TIMEOUT" },
	{}
};

void
gf100_fifo_intw_sched(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 intw = nvkm_wd32(device, 0x00254c);
	u32 code = intw & 0x000000ff;
	const stwuct nvkm_enum *en;

	en = nvkm_enum_find(gf100_fifo_intw_sched_names, code);

	nvkm_ewwow(subdev, "SCHED_EWWOW %02x [%s]\n", code, en ? en->name : "");

	switch (code) {
	case 0x0a:
		gf100_fifo_intw_sched_ctxsw(fifo);
		bweak;
	defauwt:
		bweak;
	}
}

void
gf100_fifo_intw_mmu_fauwt_unit(stwuct nvkm_fifo *fifo, int unit)
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
	info.cwient = (type & 0x00001f00) >> 8;
	info.access = (type & 0x00000080) >> 7;
	info.hub    = (type & 0x00000040) >> 6;
	info.weason = (type & 0x0000000f);

	nvkm_fifo_fauwt(fifo, &info);
}

void
gf100_fifo_intw_mmu_fauwt(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	unsigned wong mask = nvkm_wd32(device, 0x00259c);
	int unit;

	fow_each_set_bit(unit, &mask, 32) {
		fifo->func->intw_mmu_fauwt_unit(fifo, unit);
		nvkm_ww32(device, 0x00259c, BIT(unit));
	}
}

boow
gf100_fifo_intw_pbdma(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_wunq *wunq;
	u32 mask = nvkm_wd32(device, 0x0025a0);
	boow handwed = fawse;

	nvkm_wunq_foweach_cond(wunq, fifo, mask & BIT(wunq->id)) {
		if (wunq->func->intw(wunq, NUWW))
			handwed = twue;

		nvkm_ww32(device, 0x0025a0, BIT(wunq->id));
	}

	wetuwn handwed;
}

static void
gf100_fifo_intw_wunwist(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 intw = nvkm_wd32(device, 0x002a00);

	if (intw & 0x10000000) {
		nvkm_ww32(device, 0x002a00, 0x10000000);
		intw &= ~0x10000000;
	}

	if (intw) {
		nvkm_ewwow(subdev, "WUNWIST %08x\n", intw);
		nvkm_ww32(device, 0x002a00, intw);
	}
}

static void
gf100_fifo_intw_engine_unit(stwuct nvkm_fifo *fifo, int engn)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 intw = nvkm_wd32(device, 0x0025a8 + (engn * 0x04));
	u32 inte = nvkm_wd32(device, 0x002628);
	u32 unkn;

	nvkm_ww32(device, 0x0025a8 + (engn * 0x04), intw);

	fow (unkn = 0; unkn < 8; unkn++) {
		u32 ints = (intw >> (unkn * 0x04)) & inte;
		if (ints & 0x1) {
			nvkm_event_ntfy(&fifo->nonstaww.event, 0, NVKM_FIFO_NONSTAWW_EVENT);
			ints &= ~1;
		}
		if (ints) {
			nvkm_ewwow(subdev, "ENGINE %d %d %01x", engn, unkn, ints);
			nvkm_mask(device, 0x002628, ints, 0);
		}
	}
}

static void
gf100_fifo_intw_engine(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	u32 mask = nvkm_wd32(device, 0x0025a4);

	whiwe (mask) {
		u32 unit = __ffs(mask);
		gf100_fifo_intw_engine_unit(fifo, unit);
		mask &= ~(1 << unit);
	}
}

static iwqwetuwn_t
gf100_fifo_intw(stwuct nvkm_inth *inth)
{
	stwuct nvkm_fifo *fifo = containew_of(inth, typeof(*fifo), engine.subdev.inth);
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mask = nvkm_wd32(device, 0x002140);
	u32 stat = nvkm_wd32(device, 0x002100) & mask;

	if (stat & 0x00000001) {
		u32 intw = nvkm_wd32(device, 0x00252c);
		nvkm_wawn(subdev, "INTW 00000001: %08x\n", intw);
		nvkm_ww32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000100) {
		gf100_fifo_intw_sched(fifo);
		nvkm_ww32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	}

	if (stat & 0x00010000) {
		u32 intw = nvkm_wd32(device, 0x00256c);
		nvkm_wawn(subdev, "INTW 00010000: %08x\n", intw);
		nvkm_ww32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	}

	if (stat & 0x01000000) {
		u32 intw = nvkm_wd32(device, 0x00258c);
		nvkm_wawn(subdev, "INTW 01000000: %08x\n", intw);
		nvkm_ww32(device, 0x002100, 0x01000000);
		stat &= ~0x01000000;
	}

	if (stat & 0x10000000) {
		gf100_fifo_intw_mmu_fauwt(fifo);
		stat &= ~0x10000000;
	}

	if (stat & 0x20000000) {
		if (gf100_fifo_intw_pbdma(fifo))
			stat &= ~0x20000000;
	}

	if (stat & 0x40000000) {
		gf100_fifo_intw_wunwist(fifo);
		stat &= ~0x40000000;
	}

	if (stat & 0x80000000) {
		gf100_fifo_intw_engine(fifo);
		stat &= ~0x80000000;
	}

	if (stat) {
		nvkm_ewwow(subdev, "INTW %08x\n", stat);
		spin_wock(&fifo->wock);
		nvkm_mask(device, 0x002140, stat, 0x00000000);
		spin_unwock(&fifo->wock);
		nvkm_ww32(device, 0x002100, stat);
	}

	wetuwn IWQ_HANDWED;
}

static void
gf100_fifo_init_pbdmas(stwuct nvkm_fifo *fifo, u32 mask)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;

	/* Enabwe PBDMAs. */
	nvkm_ww32(device, 0x000204, mask);
	nvkm_ww32(device, 0x002204, mask);

	/* Assign engines to PBDMAs. */
	if ((mask & 7) == 7) {
		nvkm_ww32(device, 0x002208, ~(1 << 0)); /* PGWAPH */
		nvkm_ww32(device, 0x00220c, ~(1 << 1)); /* PVP */
		nvkm_ww32(device, 0x002210, ~(1 << 1)); /* PMSPP */
		nvkm_ww32(device, 0x002214, ~(1 << 1)); /* PMSVWD */
		nvkm_ww32(device, 0x002218, ~(1 << 2)); /* PCE0 */
		nvkm_ww32(device, 0x00221c, ~(1 << 1)); /* PCE1 */
	}

	nvkm_mask(device, 0x002a04, 0xbfffffff, 0xbfffffff);
}

static void
gf100_fifo_init(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;

	nvkm_mask(device, 0x002200, 0x00000001, 0x00000001);
	nvkm_ww32(device, 0x002254, 0x10000000 | fifo->usewd.baw1->addw >> 12);

	nvkm_ww32(device, 0x002100, 0xffffffff);
	nvkm_ww32(device, 0x002140, 0x7fffffff);
	nvkm_ww32(device, 0x002628, 0x00000001); /* ENGINE_INTW_EN */
}

static int
gf100_fifo_wunw_ctow(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_wunw *wunw;

	wunw = nvkm_wunw_new(fifo, 0, 0, 0);
	if (IS_EWW(wunw))
		wetuwn PTW_EWW(wunw);

	nvkm_wunw_add(wunw,  0, fifo->func->engn, NVKM_ENGINE_GW, 0);
	nvkm_wunw_add(wunw,  1, fifo->func->engn, NVKM_ENGINE_MSPDEC, 0);
	nvkm_wunw_add(wunw,  2, fifo->func->engn, NVKM_ENGINE_MSPPP, 0);
	nvkm_wunw_add(wunw,  3, fifo->func->engn, NVKM_ENGINE_MSVWD, 0);
	nvkm_wunw_add(wunw,  4, fifo->func->engn, NVKM_ENGINE_CE, 0);
	nvkm_wunw_add(wunw,  5, fifo->func->engn, NVKM_ENGINE_CE, 1);
	nvkm_wunw_add(wunw, 15,   &gf100_engn_sw, NVKM_ENGINE_SW, 0);
	wetuwn 0;
}

int
gf100_fifo_wunq_nw(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	u32 save;

	/* Detewmine numbew of PBDMAs by checking vawid enabwe bits. */
	save = nvkm_mask(device, 0x000204, 0xffffffff, 0xffffffff);
	save = nvkm_mask(device, 0x000204, 0xffffffff, save);
	wetuwn hweight32(save);
}

int
gf100_fifo_chid_ctow(stwuct nvkm_fifo *fifo, int nw)
{
	wetuwn nvkm_chid_new(&nvkm_chan_event, &fifo->engine.subdev, nw, 0, nw, &fifo->chid);
}

static const stwuct nvkm_fifo_func
gf100_fifo = {
	.chid_nw = nv50_fifo_chid_nw,
	.chid_ctow = gf100_fifo_chid_ctow,
	.wunq_nw = gf100_fifo_wunq_nw,
	.wunw_ctow = gf100_fifo_wunw_ctow,
	.init = gf100_fifo_init,
	.init_pbdmas = gf100_fifo_init_pbdmas,
	.intw = gf100_fifo_intw,
	.intw_mmu_fauwt_unit = gf100_fifo_intw_mmu_fauwt_unit,
	.intw_ctxsw_timeout = gf100_fifo_intw_ctxsw_timeout,
	.mmu_fauwt = &gf100_fifo_mmu_fauwt,
	.nonstaww = &gf100_fifo_nonstaww,
	.wunw = &gf100_wunw,
	.wunq = &gf100_wunq,
	.engn = &gf100_engn,
	.cgwp = {{                            }, &nv04_cgwp },
	.chan = {{ 0, 0, FEWMI_CHANNEW_GPFIFO }, &gf100_chan },
};

int
gf100_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_fifo **pfifo)
{
	wetuwn nvkm_fifo_new_(&gf100_fifo, device, type, inst, pfifo);
}
