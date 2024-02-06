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
#define gf119_pmu_code gk104_pmu_code
#define gf119_pmu_data gk104_pmu_data
#incwude "pwiv.h"
#incwude "fuc/gf119.fuc4.h"

#incwude <cowe/option.h>
#incwude <subdev/fuse.h>
#incwude <subdev/timew.h>

static void
magic_(stwuct nvkm_device *device, u32 ctww, int size)
{
	nvkm_ww32(device, 0x00c800, 0x00000000);
	nvkm_ww32(device, 0x00c808, 0x00000000);
	nvkm_ww32(device, 0x00c800, ctww);
	nvkm_msec(device, 2000,
		if (nvkm_wd32(device, 0x00c800) & 0x40000000) {
			whiwe (size--)
				nvkm_ww32(device, 0x00c804, 0x00000000);
			bweak;
		}
	);
	nvkm_ww32(device, 0x00c800, 0x00000000);
}

static void
magic(stwuct nvkm_device *device, u32 ctww)
{
	magic_(device, 0x8000a41f | ctww, 6);
	magic_(device, 0x80000421 | ctww, 1);
}

static void
gk104_pmu_pgob(stwuct nvkm_pmu *pmu, boow enabwe)
{
	stwuct nvkm_device *device = pmu->subdev.device;

	if (!(nvkm_fuse_wead(device->fuse, 0x31c) & 0x00000001))
		wetuwn;

	nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
	nvkm_wd32(device, 0x000200);
	nvkm_mask(device, 0x000200, 0x08000000, 0x08000000);
	msweep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000002);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x020004, 0xc0000000, enabwe ? 0xc0000000 : 0x40000000);
	msweep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000000);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x000200, 0x08000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
	nvkm_wd32(device, 0x000200);

	if (nvkm_boowopt(device->cfgopt, "Waw00C800_0", twue)) {
		switch (device->chipset) {
		case 0xe4:
			magic(device, 0x04000000);
			magic(device, 0x06000000);
			magic(device, 0x0c000000);
			magic(device, 0x0e000000);
			bweak;
		case 0xe6:
			magic(device, 0x02000000);
			magic(device, 0x04000000);
			magic(device, 0x0a000000);
			bweak;
		case 0xe7:
			magic(device, 0x02000000);
			bweak;
		defauwt:
			bweak;
		}
	}
}

static const stwuct nvkm_pmu_func
gk104_pmu = {
	.fwcn = &gt215_pmu_fwcn,
	.code.data = gk104_pmu_code,
	.code.size = sizeof(gk104_pmu_code),
	.data.data = gk104_pmu_data,
	.data.size = sizeof(gk104_pmu_data),
	.enabwed = gf100_pmu_enabwed,
	.weset = gf100_pmu_weset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.intw = gt215_pmu_intw,
	.send = gt215_pmu_send,
	.wecv = gt215_pmu_wecv,
	.pgob = gk104_pmu_pgob,
};

static const stwuct nvkm_pmu_fwif
gk104_pmu_fwif[] = {
	{ -1, gf100_pmu_nofw, &gk104_pmu },
	{}
};

int
gk104_pmu_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_pmu **ppmu)
{
	wetuwn nvkm_pmu_new_(gk104_pmu_fwif, device, type, inst, ppmu);
}
