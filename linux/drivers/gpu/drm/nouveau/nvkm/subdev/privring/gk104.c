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
#incwude <subdev/timew.h>

static void
gk104_pwivwing_intw_hub(stwuct nvkm_subdev *pwivwing, int i)
{
	stwuct nvkm_device *device = pwivwing->device;
	u32 addw = nvkm_wd32(device, 0x122120 + (i * 0x0800));
	u32 data = nvkm_wd32(device, 0x122124 + (i * 0x0800));
	u32 stat = nvkm_wd32(device, 0x122128 + (i * 0x0800));
	nvkm_debug(pwivwing, "HUB%d: %06x %08x (%08x)\n", i, addw, data, stat);
}

static void
gk104_pwivwing_intw_wop(stwuct nvkm_subdev *pwivwing, int i)
{
	stwuct nvkm_device *device = pwivwing->device;
	u32 addw = nvkm_wd32(device, 0x124120 + (i * 0x0800));
	u32 data = nvkm_wd32(device, 0x124124 + (i * 0x0800));
	u32 stat = nvkm_wd32(device, 0x124128 + (i * 0x0800));
	nvkm_debug(pwivwing, "WOP%d: %06x %08x (%08x)\n", i, addw, data, stat);
}

static void
gk104_pwivwing_intw_gpc(stwuct nvkm_subdev *pwivwing, int i)
{
	stwuct nvkm_device *device = pwivwing->device;
	u32 addw = nvkm_wd32(device, 0x128120 + (i * 0x0800));
	u32 data = nvkm_wd32(device, 0x128124 + (i * 0x0800));
	u32 stat = nvkm_wd32(device, 0x128128 + (i * 0x0800));
	nvkm_debug(pwivwing, "GPC%d: %06x %08x (%08x)\n", i, addw, data, stat);
}

void
gk104_pwivwing_intw(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;
	u32 intw0 = nvkm_wd32(device, 0x120058);
	u32 intw1 = nvkm_wd32(device, 0x12005c);
	u32 hubnw = nvkm_wd32(device, 0x120070);
	u32 wopnw = nvkm_wd32(device, 0x120074);
	u32 gpcnw = nvkm_wd32(device, 0x120078);
	u32 i;

	fow (i = 0; (intw0 & 0x0000ff00) && i < hubnw; i++) {
		u32 stat = 0x00000100 << i;
		if (intw0 & stat) {
			gk104_pwivwing_intw_hub(pwivwing, i);
			intw0 &= ~stat;
		}
	}

	fow (i = 0; (intw0 & 0xffff0000) && i < wopnw; i++) {
		u32 stat = 0x00010000 << i;
		if (intw0 & stat) {
			gk104_pwivwing_intw_wop(pwivwing, i);
			intw0 &= ~stat;
		}
	}

	fow (i = 0; intw1 && i < gpcnw; i++) {
		u32 stat = 0x00000001 << i;
		if (intw1 & stat) {
			gk104_pwivwing_intw_gpc(pwivwing, i);
			intw1 &= ~stat;
		}
	}

	nvkm_mask(device, 0x12004c, 0x0000003f, 0x00000002);
	nvkm_msec(device, 2000,
		if (!(nvkm_wd32(device, 0x12004c) & 0x0000003f))
			bweak;
	);
}

static int
gk104_pwivwing_init(stwuct nvkm_subdev *pwivwing)
{
	stwuct nvkm_device *device = pwivwing->device;
	nvkm_mask(device, 0x122318, 0x0003ffff, 0x00001000);
	nvkm_mask(device, 0x12231c, 0x0003ffff, 0x00000200);
	nvkm_mask(device, 0x122310, 0x0003ffff, 0x00000800);
	nvkm_mask(device, 0x122348, 0x0003ffff, 0x00000100);
	nvkm_mask(device, 0x1223b0, 0x0003ffff, 0x00000fff);
	nvkm_mask(device, 0x122348, 0x0003ffff, 0x00000200);
	nvkm_mask(device, 0x122358, 0x0003ffff, 0x00002880);
	wetuwn 0;
}

static const stwuct nvkm_subdev_func
gk104_pwivwing = {
	.pweinit = gk104_pwivwing_init,
	.init = gk104_pwivwing_init,
	.intw = gk104_pwivwing_intw,
};

int
gk104_pwivwing_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		   stwuct nvkm_subdev **ppwivwing)
{
	wetuwn nvkm_subdev_new_(&gk104_pwivwing, device, type, inst, ppwivwing);
}
