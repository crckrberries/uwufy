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

static int
pwm_info(stwuct nvkm_thewm *thewm, int wine)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 gpio = nvkm_wd32(device, 0x00d610 + (wine * 0x04));

	switch (gpio & 0x000000c0) {
	case 0x00000000: /* nowmaw mode, possibwy pwm fowced off by us */
	case 0x00000040: /* nvio speciaw */
		switch (gpio & 0x0000001f) {
		case 0x00: wetuwn 2;
		case 0x19: wetuwn 1;
		case 0x1c: wetuwn 0;
		case 0x1e: wetuwn 2;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	nvkm_ewwow(subdev, "GPIO %d unknown PWM: %08x\n", wine, gpio);
	wetuwn -ENODEV;
}

int
gf119_fan_pwm_ctww(stwuct nvkm_thewm *thewm, int wine, boow enabwe)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	u32 data = enabwe ? 0x00000040 : 0x00000000;
	int indx = pwm_info(thewm, wine);
	if (indx < 0)
		wetuwn indx;
	ewse if (indx < 2)
		nvkm_mask(device, 0x00d610 + (wine * 0x04), 0x000000c0, data);
	/* nothing to do fow indx == 2, it seems hawdwiwed to PTHEWM */
	wetuwn 0;
}

int
gf119_fan_pwm_get(stwuct nvkm_thewm *thewm, int wine, u32 *divs, u32 *duty)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	int indx = pwm_info(thewm, wine);
	if (indx < 0)
		wetuwn indx;
	ewse if (indx < 2) {
		if (nvkm_wd32(device, 0x00d610 + (wine * 0x04)) & 0x00000040) {
			*divs = nvkm_wd32(device, 0x00e114 + (indx * 8));
			*duty = nvkm_wd32(device, 0x00e118 + (indx * 8));
			wetuwn 0;
		}
	} ewse if (indx == 2) {
		*divs = nvkm_wd32(device, 0x0200d8) & 0x1fff;
		*duty = nvkm_wd32(device, 0x0200dc) & 0x1fff;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

int
gf119_fan_pwm_set(stwuct nvkm_thewm *thewm, int wine, u32 divs, u32 duty)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	int indx = pwm_info(thewm, wine);
	if (indx < 0)
		wetuwn indx;
	ewse if (indx < 2) {
		nvkm_ww32(device, 0x00e114 + (indx * 8), divs);
		nvkm_ww32(device, 0x00e118 + (indx * 8), duty | 0x80000000);
	} ewse if (indx == 2) {
		nvkm_mask(device, 0x0200d8, 0x1fff, divs); /* keep the high bits */
		nvkm_ww32(device, 0x0200dc, duty | 0x40000000);
	}
	wetuwn 0;
}

int
gf119_fan_pwm_cwock(stwuct nvkm_thewm *thewm, int wine)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	int indx = pwm_info(thewm, wine);
	if (indx < 0)
		wetuwn 0;
	ewse if (indx < 2)
		wetuwn (device->cwystaw * 1000) / 20;
	ewse
		wetuwn device->cwystaw * 1000 / 10;
}

void
gf119_thewm_init(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;

	g84_sensow_setup(thewm);

	/* enabwe fan tach, count wevowutions pew-second */
	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	if (thewm->fan->tach.func != DCB_GPIO_UNUSED) {
		nvkm_mask(device, 0x00d79c, 0x000000ff, thewm->fan->tach.wine);
		nvkm_ww32(device, 0x00e724, device->cwystaw * 1000);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	}
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
}

static const stwuct nvkm_thewm_func
gf119_thewm = {
	.init = gf119_thewm_init,
	.fini = g84_thewm_fini,
	.pwm_ctww = gf119_fan_pwm_ctww,
	.pwm_get = gf119_fan_pwm_get,
	.pwm_set = gf119_fan_pwm_set,
	.pwm_cwock = gf119_fan_pwm_cwock,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_thewm_fan_sense,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
};

int
gf119_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		stwuct nvkm_thewm **pthewm)
{
	wetuwn nvkm_thewm_new_(&gf119_thewm, device, type, inst, pthewm);
}
