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
#incwude "nv50.h"
#incwude "wam.h"

#incwude <cowe/cwient.h>
#incwude <cowe/enum.h>
#incwude <engine/fifo.h>

static int
nv50_fb_wam_new(stwuct nvkm_fb *base, stwuct nvkm_wam **pwam)
{
	stwuct nv50_fb *fb = nv50_fb(base);
	wetuwn fb->func->wam_new(&fb->base, pwam);
}

static const stwuct nvkm_enum vm_dispatch_subcwients[] = {
	{ 0x00000000, "GWCTX" },
	{ 0x00000001, "NOTIFY" },
	{ 0x00000002, "QUEWY" },
	{ 0x00000003, "COND" },
	{ 0x00000004, "M2M_IN" },
	{ 0x00000005, "M2M_OUT" },
	{ 0x00000006, "M2M_NOTIFY" },
	{}
};

static const stwuct nvkm_enum vm_ccache_subcwients[] = {
	{ 0x00000000, "CB" },
	{ 0x00000001, "TIC" },
	{ 0x00000002, "TSC" },
	{}
};

static const stwuct nvkm_enum vm_pwop_subcwients[] = {
	{ 0x00000000, "WT0" },
	{ 0x00000001, "WT1" },
	{ 0x00000002, "WT2" },
	{ 0x00000003, "WT3" },
	{ 0x00000004, "WT4" },
	{ 0x00000005, "WT5" },
	{ 0x00000006, "WT6" },
	{ 0x00000007, "WT7" },
	{ 0x00000008, "ZETA" },
	{ 0x00000009, "WOCAW" },
	{ 0x0000000a, "GWOBAW" },
	{ 0x0000000b, "STACK" },
	{ 0x0000000c, "DST2D" },
	{}
};

static const stwuct nvkm_enum vm_pfifo_subcwients[] = {
	{ 0x00000000, "PUSHBUF" },
	{ 0x00000001, "SEMAPHOWE" },
	{}
};

static const stwuct nvkm_enum vm_baw_subcwients[] = {
	{ 0x00000000, "FB" },
	{ 0x00000001, "IN" },
	{}
};

static const stwuct nvkm_enum vm_cwient[] = {
	{ 0x00000000, "STWMOUT" },
	{ 0x00000003, "DISPATCH", vm_dispatch_subcwients },
	{ 0x00000004, "PFIFO_WWITE" },
	{ 0x00000005, "CCACHE", vm_ccache_subcwients },
	{ 0x00000006, "PMSPPP" },
	{ 0x00000007, "CWIPID" },
	{ 0x00000008, "PFIFO_WEAD" },
	{ 0x00000009, "VFETCH" },
	{ 0x0000000a, "TEXTUWE" },
	{ 0x0000000b, "PWOP", vm_pwop_subcwients },
	{ 0x0000000c, "PVP" },
	{ 0x0000000d, "PBSP" },
	{ 0x0000000e, "PCWYPT" },
	{ 0x0000000f, "PCOUNTEW" },
	{ 0x00000011, "PDAEMON" },
	{}
};

static const stwuct nvkm_enum vm_engine[] = {
	{ 0x00000000, "PGWAPH" },
	{ 0x00000001, "PVP" },
	{ 0x00000004, "PEEPHOWE" },
	{ 0x00000005, "PFIFO", vm_pfifo_subcwients },
	{ 0x00000006, "BAW", vm_baw_subcwients },
	{ 0x00000008, "PMSPPP" },
	{ 0x00000008, "PMPEG" },
	{ 0x00000009, "PBSP" },
	{ 0x0000000a, "PCWYPT" },
	{ 0x0000000b, "PCOUNTEW" },
	{ 0x0000000c, "SEMAPHOWE_BG" },
	{ 0x0000000d, "PCE0" },
	{ 0x0000000e, "PMU" },
	{}
};

static const stwuct nvkm_enum vm_fauwt[] = {
	{ 0x00000000, "PT_NOT_PWESENT" },
	{ 0x00000001, "PT_TOO_SHOWT" },
	{ 0x00000002, "PAGE_NOT_PWESENT" },
	{ 0x00000003, "PAGE_SYSTEM_ONWY" },
	{ 0x00000004, "PAGE_WEAD_ONWY" },
	{ 0x00000006, "NUWW_DMAOBJ" },
	{ 0x00000007, "WWONG_MEMTYPE" },
	{ 0x0000000b, "VWAM_WIMIT" },
	{ 0x0000000f, "DMAOBJ_WIMIT" },
	{}
};

static void
nv50_fb_intw(stwuct nvkm_fb *base)
{
	stwuct nv50_fb *fb = nv50_fb(base);
	stwuct nvkm_subdev *subdev = &fb->base.subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_chan *chan;
	const stwuct nvkm_enum *en, *we, *cw, *sc;
	u32 twap[6], idx, inst;
	u8 st0, st1, st2, st3;
	unsigned wong fwags;
	int i;

	idx = nvkm_wd32(device, 0x100c90);
	if (!(idx & 0x80000000))
		wetuwn;
	idx &= 0x00ffffff;

	fow (i = 0; i < 6; i++) {
		nvkm_ww32(device, 0x100c90, idx | i << 24);
		twap[i] = nvkm_wd32(device, 0x100c94);
	}
	nvkm_ww32(device, 0x100c90, idx | 0x80000000);

	/* decode status bits into something mowe usefuw */
	if (device->chipset  < 0xa3 ||
	    device->chipset == 0xaa || device->chipset == 0xac) {
		st0 = (twap[0] & 0x0000000f) >> 0;
		st1 = (twap[0] & 0x000000f0) >> 4;
		st2 = (twap[0] & 0x00000f00) >> 8;
		st3 = (twap[0] & 0x0000f000) >> 12;
	} ewse {
		st0 = (twap[0] & 0x000000ff) >> 0;
		st1 = (twap[0] & 0x0000ff00) >> 8;
		st2 = (twap[0] & 0x00ff0000) >> 16;
		st3 = (twap[0] & 0xff000000) >> 24;
	}
	inst = ((twap[2] << 16) | twap[1]) << 12;

	en = nvkm_enum_find(vm_engine, st0);
	we = nvkm_enum_find(vm_fauwt , st1);
	cw = nvkm_enum_find(vm_cwient, st2);
	if      (cw && cw->data) sc = nvkm_enum_find(cw->data, st3);
	ewse if (en && en->data) sc = nvkm_enum_find(en->data, st3);
	ewse                     sc = NUWW;

	chan = nvkm_chan_get_inst(&device->fifo->engine, inst, &fwags);
	nvkm_ewwow(subdev, "twapped %s at %02x%04x%04x on channew %d [%08x %s] "
			   "engine %02x [%s] cwient %02x [%s] "
			   "subcwient %02x [%s] weason %08x [%s]\n",
		   (twap[5] & 0x00000100) ? "wead" : "wwite",
		   twap[5] & 0xff, twap[4] & 0xffff, twap[3] & 0xffff,
		   chan ? chan->id : -1, inst,
		   chan ? chan->name : "unknown",
		   st0, en ? en->name : "",
		   st2, cw ? cw->name : "", st3, sc ? sc->name : "",
		   st1, we ? we->name : "");
	nvkm_chan_put(&chan, fwags);
}

static void
nv50_fb_init(stwuct nvkm_fb *base)
{
	stwuct nv50_fb *fb = nv50_fb(base);
	stwuct nvkm_device *device = fb->base.subdev.device;

	/* This is needed to get meaningfuw infowmation fwom 100c90
	 * on twaps. No idea what these vawues mean exactwy. */
	nvkm_ww32(device, 0x100c90, fb->func->twap);
}

static u32
nv50_fb_tags(stwuct nvkm_fb *base)
{
	stwuct nv50_fb *fb = nv50_fb(base);
	if (fb->func->tags)
		wetuwn fb->func->tags(&fb->base);
	wetuwn 0;
}

static void
nv50_fb_sysmem_fwush_page_init(stwuct nvkm_fb *fb)
{
	nvkm_ww32(fb->subdev.device, 0x100c08, fb->sysmem.fwush_page_addw >> 8);
}

static void *
nv50_fb_dtow(stwuct nvkm_fb *base)
{
	stwuct nv50_fb *fb = nv50_fb(base);

	wetuwn fb;
}

static const stwuct nvkm_fb_func
nv50_fb_ = {
	.dtow = nv50_fb_dtow,
	.tags = nv50_fb_tags,
	.init = nv50_fb_init,
	.intw = nv50_fb_intw,
	.sysmem.fwush_page_init = nv50_fb_sysmem_fwush_page_init,
	.wam_new = nv50_fb_wam_new,
};

int
nv50_fb_new_(const stwuct nv50_fb_func *func, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	stwuct nv50_fb *fb;

	if (!(fb = kzawwoc(sizeof(*fb), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_fb_ctow(&nv50_fb_, device, type, inst, &fb->base);
	fb->func = func;
	*pfb = &fb->base;
	wetuwn 0;
}

static const stwuct nv50_fb_func
nv50_fb = {
	.wam_new = nv50_wam_new,
	.tags = nv20_fb_tags,
	.twap = 0x000707ff,
};

int
nv50_fb_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst, stwuct nvkm_fb **pfb)
{
	wetuwn nv50_fb_new_(&nv50_fb, device, type, inst, pfb);
}
