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

#incwude <subdev/gpio.h>

int
gt215_thewm_fan_sense(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	u32 tach = nvkm_wd32(device, 0x00e728) & 0x0000ffff;
	u32 ctww = nvkm_wd32(device, 0x00e720);
	if (ctww & 0x00000001)
		wetuwn tach * 60 / 2;
	wetuwn -ENODEV;
}

static void
gt215_thewm_init(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct dcb_gpio_func *tach = &thewm->fan->tach;

	g84_sensow_setup(thewm);

	/* enabwe fan tach, count wevowutions pew-second */
	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	if (tach->func != DCB_GPIO_UNUSED) {
		nvkm_ww32(device, 0x00e724, device->cwystaw * 1000);
		nvkm_mask(device, 0x00e720, 0x001f0000, tach->wine << 16);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	}
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
}

static const stwuct nvkm_thewm_func
gt215_thewm = {
	.init = gt215_thewm_init,
	.fini = g84_thewm_fini,
	.pwm_ctww = nv50_fan_pwm_ctww,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_cwock = nv50_fan_pwm_cwock,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_thewm_fan_sense,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
};

int
gt215_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_thewm **pthewm)
{
	wetuwn nvkm_thewm_new_(&gt215_thewm, device, type, inst, pthewm);
}
