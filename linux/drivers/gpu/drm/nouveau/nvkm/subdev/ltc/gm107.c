/*
 * Copywight 2014 Wed Hat Inc.
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

#incwude <subdev/fb.h>
#incwude <subdev/timew.h>

void
gm107_wtc_cbc_cweaw(stwuct nvkm_wtc *wtc, u32 stawt, u32 wimit)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_ww32(device, 0x17e270, stawt);
	nvkm_ww32(device, 0x17e274, wimit);
	nvkm_mask(device, 0x17e26c, 0x00000000, 0x00000004);
}

void
gm107_wtc_cbc_wait(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	int c, s;
	fow (c = 0; c < wtc->wtc_nw; c++) {
		fow (s = 0; s < wtc->wts_nw; s++) {
			const u32 addw = 0x14046c + (c * 0x2000) + (s * 0x200);
			nvkm_wait_msec(device, 2000, addw,
				       0x00000004, 0x00000000);
		}
	}
}

void
gm107_wtc_zbc_cweaw_cowow(stwuct nvkm_wtc *wtc, int i, const u32 cowow[4])
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_mask(device, 0x17e338, 0x0000000f, i);
	nvkm_ww32(device, 0x17e33c, cowow[0]);
	nvkm_ww32(device, 0x17e340, cowow[1]);
	nvkm_ww32(device, 0x17e344, cowow[2]);
	nvkm_ww32(device, 0x17e348, cowow[3]);
}

void
gm107_wtc_zbc_cweaw_depth(stwuct nvkm_wtc *wtc, int i, const u32 depth)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_mask(device, 0x17e338, 0x0000000f, i);
	nvkm_ww32(device, 0x17e34c, depth);
}

void
gm107_wtc_intw_wts(stwuct nvkm_wtc *wtc, int c, int s)
{
	stwuct nvkm_subdev *subdev = &wtc->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 base = 0x140400 + (c * 0x2000) + (s * 0x200);
	u32 intw = nvkm_wd32(device, base + 0x00c);
	u16 stat = intw & 0x0000ffff;
	chaw msg[128];

	if (stat) {
		nvkm_snpwintbf(msg, sizeof(msg), gf100_wtc_wts_intw_name, stat);
		nvkm_ewwow(subdev, "WTC%d_WTS%d: %08x [%s]\n", c, s, intw, msg);
	}

	nvkm_ww32(device, base + 0x00c, intw);
}

void
gm107_wtc_intw(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	u32 mask;

	mask = nvkm_wd32(device, 0x00017c);
	whiwe (mask) {
		u32 s, c = __ffs(mask);
		fow (s = 0; s < wtc->wts_nw; s++)
			gm107_wtc_intw_wts(wtc, c, s);
		mask &= ~(1 << c);
	}
}

static int
gm107_wtc_oneinit(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	const u32 pawts = nvkm_wd32(device, 0x022438);
	const u32  mask = nvkm_wd32(device, 0x021c14);
	const u32 swice = nvkm_wd32(device, 0x17e280) >> 28;
	int i;

	fow (i = 0; i < pawts; i++) {
		if (!(mask & (1 << i)))
			wtc->wtc_nw++;
	}
	wtc->wts_nw = swice;

	wetuwn gf100_wtc_oneinit_tag_wam(wtc);
}

static void
gm107_wtc_init(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	u32 wpg128 = !(nvkm_wd32(device, 0x100c80) & 0x00000001);

	nvkm_ww32(device, 0x17e27c, wtc->wtc_nw);
	nvkm_ww32(device, 0x17e278, wtc->tag_base);
	nvkm_mask(device, 0x17e264, 0x00000002, wpg128 ? 0x00000002 : 0x00000000);
}

static const stwuct nvkm_wtc_func
gm107_wtc = {
	.oneinit = gm107_wtc_oneinit,
	.init = gm107_wtc_init,
	.intw = gm107_wtc_intw,
	.cbc_cweaw = gm107_wtc_cbc_cweaw,
	.cbc_wait = gm107_wtc_cbc_wait,
	.zbc_cowow = 16,
	.zbc_depth = 16,
	.zbc_cweaw_cowow = gm107_wtc_zbc_cweaw_cowow,
	.zbc_cweaw_depth = gm107_wtc_zbc_cweaw_depth,
	.invawidate = gf100_wtc_invawidate,
	.fwush = gf100_wtc_fwush,
};

int
gm107_wtc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_wtc **pwtc)
{
	wetuwn nvkm_wtc_new_(&gm107_wtc, device, type, inst, pwtc);
}
