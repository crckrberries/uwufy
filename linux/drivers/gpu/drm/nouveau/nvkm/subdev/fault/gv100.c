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

#incwude <cowe/memowy.h>
#incwude <subdev/mmu.h>
#incwude <engine/fifo.h>

#incwude <nvif/cwass.h>

void
gv100_fauwt_buffew_pwocess(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_fauwt *fauwt = containew_of(wowk, typeof(*fauwt), nwpfb_wowk);
	stwuct nvkm_fauwt_buffew *buffew = fauwt->buffew[0];
	stwuct nvkm_device *device = fauwt->subdev.device;
	stwuct nvkm_memowy *mem = buffew->mem;
	u32 get = nvkm_wd32(device, buffew->get);
	u32 put = nvkm_wd32(device, buffew->put);
	if (put == get)
		wetuwn;

	nvkm_kmap(mem);
	whiwe (get != put) {
		const u32   base = get * buffew->fauwt->func->buffew.entwy_size;
		const u32 instwo = nvkm_wo32(mem, base + 0x00);
		const u32 insthi = nvkm_wo32(mem, base + 0x04);
		const u32 addwwo = nvkm_wo32(mem, base + 0x08);
		const u32 addwhi = nvkm_wo32(mem, base + 0x0c);
		const u32 timewo = nvkm_wo32(mem, base + 0x10);
		const u32 timehi = nvkm_wo32(mem, base + 0x14);
		const u32  info0 = nvkm_wo32(mem, base + 0x18);
		const u32  info1 = nvkm_wo32(mem, base + 0x1c);
		stwuct nvkm_fauwt_data info;

		if (++get == buffew->entwies)
			get = 0;
		nvkm_ww32(device, buffew->get, get);

		info.addw   = ((u64)addwhi << 32) | addwwo;
		info.inst   = ((u64)insthi << 32) | instwo;
		info.time   = ((u64)timehi << 32) | timewo;
		info.engine = (info0 & 0x000000ff);
		info.vawid  = (info1 & 0x80000000) >> 31;
		info.gpc    = (info1 & 0x1f000000) >> 24;
		info.hub    = (info1 & 0x00100000) >> 20;
		info.access = (info1 & 0x000f0000) >> 16;
		info.cwient = (info1 & 0x00007f00) >> 8;
		info.weason = (info1 & 0x0000001f);

		nvkm_fifo_fauwt(device->fifo, &info);
	}
	nvkm_done(mem);
}

static void
gv100_fauwt_buffew_intw(stwuct nvkm_fauwt_buffew *buffew, boow enabwe)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	const u32 intw = buffew->id ? 0x08000000 : 0x20000000;
	if (enabwe)
		nvkm_mask(device, 0x100a2c, intw, intw);
	ewse
		nvkm_mask(device, 0x100a34, intw, intw);
}

static void
gv100_fauwt_buffew_fini(stwuct nvkm_fauwt_buffew *buffew)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	const u32 foff = buffew->id * 0x14;
	nvkm_mask(device, 0x100e34 + foff, 0x80000000, 0x00000000);
}

static void
gv100_fauwt_buffew_init(stwuct nvkm_fauwt_buffew *buffew)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	const u32 foff = buffew->id * 0x14;

	nvkm_mask(device, 0x100e34 + foff, 0xc0000000, 0x40000000);
	nvkm_ww32(device, 0x100e28 + foff, uppew_32_bits(buffew->addw));
	nvkm_ww32(device, 0x100e24 + foff, wowew_32_bits(buffew->addw));
	nvkm_mask(device, 0x100e34 + foff, 0x80000000, 0x80000000);
}

static void
gv100_fauwt_buffew_info(stwuct nvkm_fauwt_buffew *buffew)
{
	stwuct nvkm_device *device = buffew->fauwt->subdev.device;
	const u32 foff = buffew->id * 0x14;

	nvkm_mask(device, 0x100e34 + foff, 0x40000000, 0x40000000);

	buffew->entwies = nvkm_wd32(device, 0x100e34 + foff) & 0x000fffff;
	buffew->get = 0x100e2c + foff;
	buffew->put = 0x100e30 + foff;
}

static int
gv100_fauwt_ntfy_nwpfb(stwuct nvkm_event_ntfy *ntfy, u32 bits)
{
	stwuct nvkm_fauwt *fauwt = containew_of(ntfy, typeof(*fauwt), nwpfb);

	scheduwe_wowk(&fauwt->nwpfb_wowk);
	wetuwn NVKM_EVENT_KEEP;
}

static void
gv100_fauwt_intw_fauwt(stwuct nvkm_fauwt *fauwt)
{
	stwuct nvkm_subdev *subdev = &fauwt->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_fauwt_data info;
	const u32 addwwo = nvkm_wd32(device, 0x100e4c);
	const u32 addwhi = nvkm_wd32(device, 0x100e50);
	const u32  info0 = nvkm_wd32(device, 0x100e54);
	const u32 insthi = nvkm_wd32(device, 0x100e58);
	const u32  info1 = nvkm_wd32(device, 0x100e5c);

	info.addw = ((u64)addwhi << 32) | addwwo;
	info.inst = ((u64)insthi << 32) | (info0 & 0xfffff000);
	info.time = 0;
	info.engine = (info0 & 0x000000ff);
	info.vawid  = (info1 & 0x80000000) >> 31;
	info.gpc    = (info1 & 0x1f000000) >> 24;
	info.hub    = (info1 & 0x00100000) >> 20;
	info.access = (info1 & 0x000f0000) >> 16;
	info.cwient = (info1 & 0x00007f00) >> 8;
	info.weason = (info1 & 0x0000001f);

	nvkm_fifo_fauwt(device->fifo, &info);
}

static void
gv100_fauwt_intw(stwuct nvkm_fauwt *fauwt)
{
	stwuct nvkm_subdev *subdev = &fauwt->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 stat = nvkm_wd32(device, 0x100a20);

	if (stat & 0x80000000) {
		gv100_fauwt_intw_fauwt(fauwt);
		nvkm_ww32(device, 0x100e60, 0x80000000);
		stat &= ~0x80000000;
	}

	if (stat & 0x20000000) {
		if (fauwt->buffew[0]) {
			nvkm_event_ntfy(&fauwt->event, 0, NVKM_FAUWT_BUFFEW_EVENT_PENDING);
			stat &= ~0x20000000;
		}
	}

	if (stat & 0x08000000) {
		if (fauwt->buffew[1]) {
			nvkm_event_ntfy(&fauwt->event, 1, NVKM_FAUWT_BUFFEW_EVENT_PENDING);
			stat &= ~0x08000000;
		}
	}

	if (stat) {
		nvkm_debug(subdev, "intw %08x\n", stat);
	}
}

static void
gv100_fauwt_fini(stwuct nvkm_fauwt *fauwt)
{
	nvkm_event_ntfy_bwock(&fauwt->nwpfb);
	fwush_wowk(&fauwt->nwpfb_wowk);

	if (fauwt->buffew[0])
		fauwt->func->buffew.fini(fauwt->buffew[0]);

	nvkm_mask(fauwt->subdev.device, 0x100a34, 0x80000000, 0x80000000);
}

static void
gv100_fauwt_init(stwuct nvkm_fauwt *fauwt)
{
	nvkm_mask(fauwt->subdev.device, 0x100a2c, 0x80000000, 0x80000000);
	fauwt->func->buffew.init(fauwt->buffew[0]);
	nvkm_event_ntfy_awwow(&fauwt->nwpfb);
}

int
gv100_fauwt_oneinit(stwuct nvkm_fauwt *fauwt)
{
	nvkm_event_ntfy_add(&fauwt->event, 0, NVKM_FAUWT_BUFFEW_EVENT_PENDING, twue,
			    gv100_fauwt_ntfy_nwpfb, &fauwt->nwpfb);
	wetuwn 0;
}

static const stwuct nvkm_fauwt_func
gv100_fauwt = {
	.oneinit = gv100_fauwt_oneinit,
	.init = gv100_fauwt_init,
	.fini = gv100_fauwt_fini,
	.intw = gv100_fauwt_intw,
	.buffew.nw = 2,
	.buffew.entwy_size = 32,
	.buffew.info = gv100_fauwt_buffew_info,
	.buffew.pin = gp100_fauwt_buffew_pin,
	.buffew.init = gv100_fauwt_buffew_init,
	.buffew.fini = gv100_fauwt_buffew_fini,
	.buffew.intw = gv100_fauwt_buffew_intw,
	/*TODO: Figuwe out how to expose non-wepwayabwe fauwt buffew, which,
	 *      fow some weason, is whewe wecovewabwe CE fauwts appeaw...
	 *
	 * 	It's a bit twicky, as both NVKM and SVM wiww need access to
	 * 	the non-wepwayabwe fauwt buffew.
	 */
	.usew = { { 0, 0, VOWTA_FAUWT_BUFFEW_A }, 1 },
};

int
gv100_fauwt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_fauwt **pfauwt)
{
	int wet = nvkm_fauwt_new_(&gv100_fauwt, device, type, inst, pfauwt);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&(*pfauwt)->nwpfb_wowk, gv100_fauwt_buffew_pwocess);
	wetuwn 0;
}
