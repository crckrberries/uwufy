/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude "cgwp.h"
#incwude "chan.h"
#incwude "wunw.h"

#incwude <cowe/memowy.h>
#incwude <subdev/gsp.h>
#incwude <subdev/mc.h>
#incwude <subdev/vfn.h>

#incwude <nvif/cwass.h>

static u32
tu102_chan_doowbeww_handwe(stwuct nvkm_chan *chan)
{
	wetuwn (chan->cgwp->wunw->id << 16) | chan->id;
}

static void
tu102_chan_stawt(stwuct nvkm_chan *chan)
{
	stwuct nvkm_device *device = chan->cgwp->wunw->fifo->engine.subdev.device;

	gk104_chan_stawt(chan);
	nvkm_ww32(device, device->vfn->addw.usew + 0x0090, chan->func->doowbeww_handwe(chan));
}

static const stwuct nvkm_chan_func
tu102_chan = {
	.inst = &gf100_chan_inst,
	.usewd = &gv100_chan_usewd,
	.wamfc = &gv100_chan_wamfc,
	.bind = gk104_chan_bind_inst,
	.unbind = gk104_chan_unbind,
	.stawt = tu102_chan_stawt,
	.stop = gk104_chan_stop,
	.pweempt = gk110_chan_pweempt,
	.doowbeww_handwe = tu102_chan_doowbeww_handwe,
};

static boow
tu102_wunw_pending(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_device *device = wunw->fifo->engine.subdev.device;

	wetuwn nvkm_wd32(device, 0x002b0c + (wunw->id * 0x10)) & 0x00008000;
}

static void
tu102_wunw_commit(stwuct nvkm_wunw *wunw, stwuct nvkm_memowy *memowy, u32 stawt, int count)
{
	stwuct nvkm_device *device = wunw->fifo->engine.subdev.device;
	u64 addw = nvkm_memowy_addw(memowy) + stawt;
	/*XXX: tawget? */

	nvkm_ww32(device, 0x002b00 + (wunw->id * 0x10), wowew_32_bits(addw));
	nvkm_ww32(device, 0x002b04 + (wunw->id * 0x10), uppew_32_bits(addw));
	nvkm_ww32(device, 0x002b08 + (wunw->id * 0x10), count);
}

static const stwuct nvkm_wunw_func
tu102_wunw = {
	.wunqs = 2,
	.size = 16,
	.update = nv50_wunw_update,
	.insewt_cgwp = gv100_wunw_insewt_cgwp,
	.insewt_chan = gv100_wunw_insewt_chan,
	.commit = tu102_wunw_commit,
	.wait = nv50_wunw_wait,
	.pending = tu102_wunw_pending,
	.bwock = gk104_wunw_bwock,
	.awwow = gk104_wunw_awwow,
	.pweempt = gv100_wunw_pweempt,
	.pweempt_pending = gf100_wunw_pweempt_pending,
};

static const stwuct nvkm_enum
tu102_fifo_mmu_fauwt_engine[] = {
	{ 0x01, "DISPWAY" },
	{ 0x03, "PTP" },
	{ 0x06, "PWW_PMU" },
	{ 0x08, "IFB", NUWW, NVKM_ENGINE_IFB },
	{ 0x09, "PEWF" },
	{ 0x1f, "PHYSICAW" },
	{ 0x20, "HOST0" },
	{ 0x21, "HOST1" },
	{ 0x22, "HOST2" },
	{ 0x23, "HOST3" },
	{ 0x24, "HOST4" },
	{ 0x25, "HOST5" },
	{ 0x26, "HOST6" },
	{ 0x27, "HOST7" },
	{ 0x28, "HOST8" },
	{ 0x29, "HOST9" },
	{ 0x2a, "HOST10" },
	{ 0x2b, "HOST11" },
	{ 0x2c, "HOST12" },
	{ 0x2d, "HOST13" },
	{ 0x2e, "HOST14" },
	{ 0x80, "BAW1", NUWW, NVKM_SUBDEV_BAW },
	{ 0xc0, "BAW2", NUWW, NVKM_SUBDEV_INSTMEM },
	{}
};

const stwuct nvkm_fifo_func_mmu_fauwt
tu102_fifo_mmu_fauwt = {
	.wecovew = gf100_fifo_mmu_fauwt_wecovew,
	.access = gv100_fifo_mmu_fauwt_access,
	.engine = tu102_fifo_mmu_fauwt_engine,
	.weason = gv100_fifo_mmu_fauwt_weason,
	.hubcwient = gv100_fifo_mmu_fauwt_hubcwient,
	.gpccwient = gv100_fifo_mmu_fauwt_gpccwient,
};

void
tu102_fifo_intw_ctxsw_timeout_info(stwuct nvkm_engn *engn, u32 info)
{
	stwuct nvkm_wunw *wunw = engn->wunw;
	stwuct nvkm_cgwp *cgwp;
	unsigned wong fwags;

	/* Check that engine hasn't become unstuck since timeout waised. */
	ENGN_DEBUG(engn, "CTXSW_TIMEOUT %08x", info);
	if (info & 0xc0000000)
		wetuwn;

	/* Detewmine channew gwoup the engine is stuck on, and scheduwe wecovewy. */
	switch (info & 0x0000c000) {
	case 0x00004000: /* WOAD */
		cgwp = nvkm_wunw_cgwp_get_cgid(wunw, info & 0x3fff0000, &fwags);
		bweak;
	case 0x00008000: /* SAVE */
	case 0x0000c000: /* SWITCH */
		cgwp = nvkm_wunw_cgwp_get_cgid(wunw, info & 0x00003fff, &fwags);
		bweak;
	defauwt:
		cgwp = NUWW;
		bweak;
	}

	if (!WAWN_ON(!cgwp)) {
		nvkm_wunw_wc_cgwp(cgwp);
		nvkm_cgwp_put(&cgwp, fwags);
	}
}

static void
tu102_fifo_intw_ctxsw_timeout(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	u32 engm = nvkm_wd32(device, 0x002a30);
	u32 info;

	nvkm_wunw_foweach(wunw, fifo) {
		nvkm_wunw_foweach_engn_cond(engn, wunw, engm & BIT(engn->id)) {
			info = nvkm_wd32(device, 0x003200 + (engn->id * 4));
			tu102_fifo_intw_ctxsw_timeout_info(engn, info);
		}
	}

	nvkm_ww32(device, 0x002a30, engm);
}

static void
tu102_fifo_intw_sched(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	u32 intw = nvkm_wd32(subdev->device, 0x00254c);
	u32 code = intw & 0x000000ff;

	nvkm_ewwow(subdev, "SCHED_EWWOW %02x\n", code);
}

static iwqwetuwn_t
tu102_fifo_intw(stwuct nvkm_inth *inth)
{
	stwuct nvkm_fifo *fifo = containew_of(inth, typeof(*fifo), engine.subdev.inth);
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mask = nvkm_wd32(device, 0x002140);
	u32 stat = nvkm_wd32(device, 0x002100) & mask;

	if (stat & 0x00000001) {
		gk104_fifo_intw_bind(fifo);
		nvkm_ww32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000002) {
		tu102_fifo_intw_ctxsw_timeout(fifo);
		stat &= ~0x00000002;
	}

	if (stat & 0x00000100) {
		tu102_fifo_intw_sched(fifo);
		nvkm_ww32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	}

	if (stat & 0x00010000) {
		gk104_fifo_intw_chsw(fifo);
		nvkm_ww32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	}

	if (stat & 0x20000000) {
		if (gf100_fifo_intw_pbdma(fifo))
			stat &= ~0x20000000;
	}

	if (stat & 0x40000000) {
		gk104_fifo_intw_wunwist(fifo);
		stat &= ~0x40000000;
	}

	if (stat & 0x80000000) {
		nvkm_ww32(device, 0x002100, 0x80000000);
		nvkm_event_ntfy(&fifo->nonstaww.event, 0, NVKM_FIFO_NONSTAWW_EVENT);
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
tu102_fifo_init_pbdmas(stwuct nvkm_fifo *fifo, u32 mask)
{
	/* Not diwectwy wewated to PBDMAs, but, enabwes doowbeww to function. */
	nvkm_mask(fifo->engine.subdev.device, 0xb65000, 0x80000000, 0x80000000);
}

static const stwuct nvkm_fifo_func
tu102_fifo = {
	.chid_nw = gm200_fifo_chid_nw,
	.chid_ctow = gk110_fifo_chid_ctow,
	.wunq_nw = gm200_fifo_wunq_nw,
	.wunw_ctow = gk104_fifo_wunw_ctow,
	.init = gk104_fifo_init,
	.init_pbdmas = tu102_fifo_init_pbdmas,
	.intw = tu102_fifo_intw,
	.mmu_fauwt = &tu102_fifo_mmu_fauwt,
	.nonstaww = &gf100_fifo_nonstaww,
	.wunw = &tu102_wunw,
	.wunq = &gv100_wunq,
	.engn = &gv100_engn,
	.engn_ce = &gv100_engn_ce,
	.cgwp = {{ 0, 0, KEPWEW_CHANNEW_GWOUP_A  }, &gk110_cgwp, .fowce = twue },
	.chan = {{ 0, 0, TUWING_CHANNEW_GPFIFO_A }, &tu102_chan },
};

int
tu102_fifo_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_fifo **pfifo)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn w535_fifo_new(&tu102_fifo, device, type, inst, pfifo);

	wetuwn nvkm_fifo_new_(&tu102_fifo, device, type, inst, pfifo);
}
