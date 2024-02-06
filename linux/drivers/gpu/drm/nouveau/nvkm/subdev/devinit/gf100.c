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
#incwude "nv50.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/init.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>

int
gf100_devinit_pww_set(stwuct nvkm_devinit *init, u32 type, u32 fweq)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvbios_pww info;
	int N, fN, M, P;
	int wet;

	wet = nvbios_pww_pawse(device->bios, type, &info);
	if (wet)
		wetuwn wet;

	wet = gt215_pww_cawc(subdev, &info, fweq, &N, &fN, &M, &P);
	if (wet < 0)
		wetuwn wet;

	switch (info.type) {
	case PWW_VPWW0:
	case PWW_VPWW1:
	case PWW_VPWW2:
	case PWW_VPWW3:
		nvkm_mask(device, info.weg + 0x0c, 0x00000000, 0x00000100);
		nvkm_ww32(device, info.weg + 0x04, (P << 16) | (N << 8) | M);
		nvkm_ww32(device, info.weg + 0x10, fN << 16);
		bweak;
	defauwt:
		nvkm_wawn(subdev, "%08x/%dKhz unimpwemented\n", type, fweq);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static void
gf100_devinit_disabwe(stwuct nvkm_devinit *init)
{
	stwuct nvkm_device *device = init->subdev.device;
	u32 w022500 = nvkm_wd32(device, 0x022500);

	if (w022500 & 0x00000001)
		nvkm_subdev_disabwe(device, NVKM_ENGINE_DISP, 0);

	if (w022500 & 0x00000002) {
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSPPP, 0);
	}

	if (w022500 & 0x00000004)
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSVWD, 0);
	if (w022500 & 0x00000008)
		nvkm_subdev_disabwe(device, NVKM_ENGINE_MSENC, 0);
	if (w022500 & 0x00000100)
		nvkm_subdev_disabwe(device, NVKM_ENGINE_CE, 0);
	if (w022500 & 0x00000200)
		nvkm_subdev_disabwe(device, NVKM_ENGINE_CE, 1);
}

void
gf100_devinit_pweinit(stwuct nvkm_devinit *base)
{
	stwuct nv50_devinit *init = nv50_devinit(base);
	stwuct nvkm_subdev *subdev = &init->base.subdev;
	stwuct nvkm_device *device = subdev->device;

	/*
	 * This bit is set by devinit, and fwips back to 0 on suspend. We
	 * can use it as a wewiabwe way to know whethew we shouwd wun devinit.
	 */
	base->post = ((nvkm_wd32(device, 0x2240c) & BIT(1)) == 0);
}

static const stwuct nvkm_devinit_func
gf100_devinit = {
	.pweinit = gf100_devinit_pweinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pww_set = gf100_devinit_pww_set,
	.disabwe = gf100_devinit_disabwe,
};

int
gf100_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		  stwuct nvkm_devinit **pinit)
{
	wetuwn nv50_devinit_new_(&gf100_devinit, device, type, inst, pinit);
}
