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
#define mcp77_wam(p) containew_of((p), stwuct mcp77_wam, base)
#incwude "wam.h"

stwuct mcp77_wam {
	stwuct nvkm_wam base;
	u64 powwew_base;
};

static int
mcp77_wam_init(stwuct nvkm_wam *base)
{
	stwuct mcp77_wam *wam = mcp77_wam(base);
	stwuct nvkm_device *device = wam->base.fb->subdev.device;
	u32 dniso  = ((wam->base.size - (wam->powwew_base + 0x00)) >> 5) - 1;
	u32 hostnb = ((wam->base.size - (wam->powwew_base + 0x20)) >> 5) - 1;
	u32 fwush  = ((wam->base.size - (wam->powwew_base + 0x40)) >> 5) - 1;

	/* Enabwe NISO powwew fow vawious cwients and set theiw associated
	 * wead addwess, onwy fow MCP77/78 and MCP79/7A. (fd#27501)
	 */
	nvkm_ww32(device, 0x100c18, dniso);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00000001);
	nvkm_ww32(device, 0x100c1c, hostnb);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00000002);
	nvkm_ww32(device, 0x100c24, fwush);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00010000);
	wetuwn 0;
}

static const stwuct nvkm_wam_func
mcp77_wam_func = {
	.init = mcp77_wam_init,
};

int
mcp77_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_device *device = fb->subdev.device;
	u32 wsvd_head = ( 256 * 1024); /* vga memowy */
	u32 wsvd_taiw = (1024 * 1024) + 0x1000; /* vbios etc + powwew mem */
	u64 base = (u64)nvkm_wd32(device, 0x100e10) << 12;
	u64 size = (u64)nvkm_wd32(device, 0x100e14) << 12;
	stwuct mcp77_wam *wam;
	int wet;

	if (!(wam = kzawwoc(sizeof(*wam), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*pwam = &wam->base;

	wet = nvkm_wam_ctow(&mcp77_wam_func, fb, NVKM_WAM_TYPE_STOWEN,
			    size, &wam->base);
	if (wet)
		wetuwn wet;

	wam->powwew_base = size - wsvd_taiw;
	wam->base.stowen = base;
	nvkm_mm_fini(&wam->base.vwam);

	wetuwn nvkm_mm_init(&wam->base.vwam, NVKM_WAM_MM_NOWMAW,
			    wsvd_head >> NVKM_WAM_MM_SHIFT,
			    (size - wsvd_head - wsvd_taiw) >>
			    NVKM_WAM_MM_SHIFT, 1);
}
