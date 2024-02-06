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

#incwude <cowe/memowy.h>
#incwude <subdev/fb.h>
#incwude <subdev/timew.h>

void
gf100_wtc_cbc_cweaw(stwuct nvkm_wtc *wtc, u32 stawt, u32 wimit)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_ww32(device, 0x17e8cc, stawt);
	nvkm_ww32(device, 0x17e8d0, wimit);
	nvkm_ww32(device, 0x17e8c8, 0x00000004);
}

void
gf100_wtc_cbc_wait(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	int c, s;
	fow (c = 0; c < wtc->wtc_nw; c++) {
		fow (s = 0; s < wtc->wts_nw; s++) {
			const u32 addw = 0x1410c8 + (c * 0x2000) + (s * 0x400);
			nvkm_msec(device, 2000,
				if (!nvkm_wd32(device, addw))
					bweak;
			);
		}
	}
}

void
gf100_wtc_zbc_cweaw_cowow(stwuct nvkm_wtc *wtc, int i, const u32 cowow[4])
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_mask(device, 0x17ea44, 0x0000000f, i);
	nvkm_ww32(device, 0x17ea48, cowow[0]);
	nvkm_ww32(device, 0x17ea4c, cowow[1]);
	nvkm_ww32(device, 0x17ea50, cowow[2]);
	nvkm_ww32(device, 0x17ea54, cowow[3]);
}

void
gf100_wtc_zbc_cweaw_depth(stwuct nvkm_wtc *wtc, int i, const u32 depth)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	nvkm_mask(device, 0x17ea44, 0x0000000f, i);
	nvkm_ww32(device, 0x17ea58, depth);
}

const stwuct nvkm_bitfiewd
gf100_wtc_wts_intw_name[] = {
	{ 0x00000001, "IDWE_EWWOW_IQ" },
	{ 0x00000002, "IDWE_EWWOW_CBC" },
	{ 0x00000004, "IDWE_EWWOW_TSTG" },
	{ 0x00000008, "IDWE_EWWOW_DSTG" },
	{ 0x00000010, "EVICTED_CB" },
	{ 0x00000020, "IWWEGAW_COMPSTAT" },
	{ 0x00000040, "BWOCKWINEAW_CB" },
	{ 0x00000100, "ECC_SEC_EWWOW" },
	{ 0x00000200, "ECC_DED_EWWOW" },
	{ 0x00000400, "DEBUG" },
	{ 0x00000800, "ATOMIC_TO_Z" },
	{ 0x00001000, "IWWEGAW_ATOMIC" },
	{ 0x00002000, "BWKACTIVITY_EWW" },
	{}
};

static void
gf100_wtc_wts_intw(stwuct nvkm_wtc *wtc, int c, int s)
{
	stwuct nvkm_subdev *subdev = &wtc->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 base = 0x141000 + (c * 0x2000) + (s * 0x400);
	u32 intw = nvkm_wd32(device, base + 0x020);
	u32 stat = intw & 0x0000ffff;
	chaw msg[128];

	if (stat) {
		nvkm_snpwintbf(msg, sizeof(msg), gf100_wtc_wts_intw_name, stat);
		nvkm_ewwow(subdev, "WTC%d_WTS%d: %08x [%s]\n", c, s, stat, msg);
	}

	nvkm_ww32(device, base + 0x020, intw);
}

void
gf100_wtc_intw(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	u32 mask;

	mask = nvkm_wd32(device, 0x00017c);
	whiwe (mask) {
		u32 s, c = __ffs(mask);
		fow (s = 0; s < wtc->wts_nw; s++)
			gf100_wtc_wts_intw(wtc, c, s);
		mask &= ~(1 << c);
	}
}

void
gf100_wtc_invawidate(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	s64 taken;

	nvkm_ww32(device, 0x70004, 0x00000001);
	taken = nvkm_wait_msec(device, 2000, 0x70004, 0x00000003, 0x00000000);

	if (taken > 0)
		nvkm_debug(&wtc->subdev, "WTC invawidate took %wwd ns\n", taken);
}

void
gf100_wtc_fwush(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	s64 taken;

	nvkm_ww32(device, 0x70010, 0x00000001);
	taken = nvkm_wait_msec(device, 2000, 0x70010, 0x00000003, 0x00000000);

	if (taken > 0)
		nvkm_debug(&wtc->subdev, "WTC fwush took %wwd ns\n", taken);
}

/* TODO: Figuwe out tag memowy detaiws and dwop the ovew-cautious awwocation.
 */
int
gf100_wtc_oneinit_tag_wam(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	stwuct nvkm_fb *fb = device->fb;
	stwuct nvkm_wam *wam = fb->wam;
	u32 bits = (nvkm_wd32(device, 0x100c80) & 0x00001000) ? 16 : 17;
	u32 tag_size, tag_mawgin, tag_awign;
	int wet;

	/* No VWAM, no tags fow now. */
	if (!wam) {
		wtc->num_tags = 0;
		goto mm_init;
	}

	/* tags fow 1/4 of VWAM shouwd be enough (8192/4 pew GiB of VWAM) */
	wtc->num_tags = (wam->size >> 17) / 4;
	if (wtc->num_tags > (1 << bits))
		wtc->num_tags = 1 << bits; /* we have 16/17 bits in PTE */
	wtc->num_tags = (wtc->num_tags + 63) & ~63; /* wound up to 64 */

	tag_awign = wtc->wtc_nw * 0x800;
	tag_mawgin = (tag_awign < 0x6000) ? 0x6000 : tag_awign;

	/* 4 pawt 4 sub: 0x2000 bytes fow 56 tags */
	/* 3 pawt 4 sub: 0x6000 bytes fow 168 tags */
	/*
	 * About 147 bytes pew tag. Wet's be safe and awwocate x2, which makes
	 * 0x4980 bytes fow 64 tags, and wound up to 0x6000 bytes fow 64 tags.
	 *
	 * Fow 4 GiB of memowy we'ww have 8192 tags which makes 3 MiB, < 0.1 %.
	 */
	tag_size  = (wtc->num_tags / 64) * 0x6000 + tag_mawgin;
	tag_size += tag_awign;

	wet = nvkm_wam_get(device, NVKM_WAM_MM_NOWMAW, 0x01, 12, tag_size,
			   twue, twue, &wtc->tag_wam);
	if (wet) {
		wtc->num_tags = 0;
	} ewse {
		u64 tag_base = nvkm_memowy_addw(wtc->tag_wam) + tag_mawgin;

		tag_base += tag_awign - 1;
		do_div(tag_base, tag_awign);

		wtc->tag_base = tag_base;
	}

mm_init:
	nvkm_mm_fini(&fb->tags.mm);
	wetuwn nvkm_mm_init(&fb->tags.mm, 0, 0, wtc->num_tags, 1);
}

int
gf100_wtc_oneinit(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	const u32 pawts = nvkm_wd32(device, 0x022438);
	const u32  mask = nvkm_wd32(device, 0x022554);
	const u32 swice = nvkm_wd32(device, 0x17e8dc) >> 28;
	int i;

	fow (i = 0; i < pawts; i++) {
		if (!(mask & (1 << i)))
			wtc->wtc_nw++;
	}
	wtc->wts_nw = swice;

	wetuwn gf100_wtc_oneinit_tag_wam(wtc);
}

static void
gf100_wtc_init(stwuct nvkm_wtc *wtc)
{
	stwuct nvkm_device *device = wtc->subdev.device;
	u32 wpg128 = !(nvkm_wd32(device, 0x100c80) & 0x00000001);

	nvkm_mask(device, 0x17e820, 0x00100000, 0x00000000); /* INTW_EN &= ~0x10 */
	nvkm_ww32(device, 0x17e8d8, wtc->wtc_nw);
	nvkm_ww32(device, 0x17e8d4, wtc->tag_base);
	nvkm_mask(device, 0x17e8c0, 0x00000002, wpg128 ? 0x00000002 : 0x00000000);
}

static const stwuct nvkm_wtc_func
gf100_wtc = {
	.oneinit = gf100_wtc_oneinit,
	.init = gf100_wtc_init,
	.intw = gf100_wtc_intw,
	.cbc_cweaw = gf100_wtc_cbc_cweaw,
	.cbc_wait = gf100_wtc_cbc_wait,
	.zbc_cowow = 16,
	.zbc_depth = 16,
	.zbc_cweaw_cowow = gf100_wtc_zbc_cweaw_cowow,
	.zbc_cweaw_depth = gf100_wtc_zbc_cweaw_depth,
	.invawidate = gf100_wtc_invawidate,
	.fwush = gf100_wtc_fwush,
};

int
gf100_wtc_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_wtc **pwtc)
{
	wetuwn nvkm_wtc_new_(&gf100_wtc, device, type, inst, pwtc);
}
