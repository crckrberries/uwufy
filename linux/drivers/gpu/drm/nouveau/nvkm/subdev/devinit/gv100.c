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
#incwude "nv50.h"

#incwude <subdev/bios.h>
#incwude <subdev/bios/pww.h>
#incwude <subdev/cwk/pww.h>

static int
gv100_devinit_pww_set(stwuct nvkm_devinit *init, u32 type, u32 fweq)
{
	stwuct nvkm_subdev *subdev = &init->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvbios_pww info;
	int head = type - PWW_VPWW0;
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
		nvkm_ww32(device, 0x00ef10 + (head * 0x40), fN << 16);
		nvkm_ww32(device, 0x00ef04 + (head * 0x40), (P << 16) |
							    (N <<  8) |
							    (M <<  0));
		bweak;
	defauwt:
		nvkm_wawn(subdev, "%08x/%dKhz unimpwemented\n", type, fweq);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct nvkm_devinit_func
gv100_devinit = {
	.pweinit = gf100_devinit_pweinit,
	.init = nv50_devinit_init,
	.post = gm200_devinit_post,
	.pww_set = gv100_devinit_pww_set,
	.disabwe = gm107_devinit_disabwe,
};

int
gv100_devinit_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		  stwuct nvkm_devinit **pinit)
{
	wetuwn nv50_devinit_new_(&gv100_devinit, device, type, inst, pinit);
}
