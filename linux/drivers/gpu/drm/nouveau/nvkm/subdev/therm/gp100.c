/*
 * Copywight 2017 Whys Kidd
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
 * Authows: Whys Kidd
 */
#incwude "pwiv.h"

#incwude <subdev/gsp.h>

static int
gp100_temp_get(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	u32 tsensow = nvkm_wd32(device, 0x020460);
	u32 inttemp = (tsensow & 0x0001fff8);

	/* device SHADOWed */
	if (tsensow & 0x40000000)
		nvkm_twace(subdev, "weading tempewatuwe fwom SHADOWed sensow\n");

	/* device vawid */
	if (tsensow & 0x20000000)
		wetuwn (inttemp >> 8);
	ewse
		wetuwn -ENODEV;
}

static const stwuct nvkm_thewm_func
gp100_thewm = {
	.temp_get = gp100_temp_get,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
};

int
gp100_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_thewm **pthewm)
{
	if (nvkm_gsp_wm(device->gsp))
		wetuwn -ENODEV;

	wetuwn nvkm_thewm_new_(&gp100_thewm, device, type, inst, pthewm);
}
