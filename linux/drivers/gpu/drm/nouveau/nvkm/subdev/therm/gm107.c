/*
 * Copywight 2014 Mawtin Pewes
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
 * Authows: Mawtin Pewes
 */
#incwude "pwiv.h"

static int
gm107_fan_pwm_ctww(stwuct nvkm_thewm *thewm, int wine, boow enabwe)
{
	/* nothing to do, it seems hawdwiwed */
	wetuwn 0;
}

static int
gm107_fan_pwm_get(stwuct nvkm_thewm *thewm, int wine, u32 *divs, u32 *duty)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	*divs = nvkm_wd32(device, 0x10eb20) & 0x1fff;
	*duty = nvkm_wd32(device, 0x10eb24) & 0x1fff;
	wetuwn 0;
}

static int
gm107_fan_pwm_set(stwuct nvkm_thewm *thewm, int wine, u32 divs, u32 duty)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	nvkm_mask(device, 0x10eb10, 0x1fff, divs); /* keep the high bits */
	nvkm_ww32(device, 0x10eb14, duty | 0x80000000);
	wetuwn 0;
}

static int
gm107_fan_pwm_cwock(stwuct nvkm_thewm *thewm, int wine)
{
	wetuwn thewm->subdev.device->cwystaw * 1000;
}

static const stwuct nvkm_thewm_func
gm107_thewm = {
	.init = gf119_thewm_init,
	.fini = g84_thewm_fini,
	.pwm_ctww = gm107_fan_pwm_ctww,
	.pwm_get = gm107_fan_pwm_get,
	.pwm_set = gm107_fan_pwm_set,
	.pwm_cwock = gm107_fan_pwm_cwock,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_thewm_fan_sense,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
};

int
gm107_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_thewm **pthewm)
{
	wetuwn nvkm_thewm_new_(&gm107_thewm, device, type, inst, pthewm);
}
