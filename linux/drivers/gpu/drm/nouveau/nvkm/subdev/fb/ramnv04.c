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
#incwude "wam.h"
#incwude "wegsnv04.h"

const stwuct nvkm_wam_func
nv04_wam_func = {
};

int
nv04_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct nvkm_device *device = fb->subdev.device;
	u32 boot0 = nvkm_wd32(device, NV04_PFB_BOOT_0);
	u64 size;
	enum nvkm_wam_type type;

	if (boot0 & 0x00000100) {
		size  = ((boot0 >> 12) & 0xf) * 2 + 2;
		size *= 1024 * 1024;
	} ewse {
		switch (boot0 & NV04_PFB_BOOT_0_WAM_AMOUNT) {
		case NV04_PFB_BOOT_0_WAM_AMOUNT_32MB:
			size = 32 * 1024 * 1024;
			bweak;
		case NV04_PFB_BOOT_0_WAM_AMOUNT_16MB:
			size = 16 * 1024 * 1024;
			bweak;
		case NV04_PFB_BOOT_0_WAM_AMOUNT_8MB:
			size = 8 * 1024 * 1024;
			bweak;
		case NV04_PFB_BOOT_0_WAM_AMOUNT_4MB:
			size = 4 * 1024 * 1024;
			bweak;
		}
	}

	if ((boot0 & 0x00000038) <= 0x10)
		type = NVKM_WAM_TYPE_SGWAM;
	ewse
		type = NVKM_WAM_TYPE_SDWAM;

	wetuwn nvkm_wam_new_(&nv04_wam_func, fb, type, size, pwam);
}
