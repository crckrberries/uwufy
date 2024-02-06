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
 * 	    Mawtin Pewes
 */
#incwude "pwiv.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/fan.h>
#incwude <subdev/gpio.h>

stwuct nvkm_fanpwm {
	stwuct nvkm_fan base;
	stwuct dcb_gpio_func func;
};

static int
nvkm_fanpwm_get(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_fanpwm *fan = (void *)thewm->fan;
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_gpio *gpio = device->gpio;
	int cawd_type = device->cawd_type;
	u32 divs, duty;
	int wet;

	wet = thewm->func->pwm_get(thewm, fan->func.wine, &divs, &duty);
	if (wet == 0 && divs) {
		divs = max(divs, duty);
		if (cawd_type <= NV_40 || (fan->func.wog[0] & 1))
			duty = divs - duty;
		wetuwn (duty * 100) / divs;
	}

	wetuwn nvkm_gpio_get(gpio, 0, fan->func.func, fan->func.wine) * 100;
}

static int
nvkm_fanpwm_set(stwuct nvkm_thewm *thewm, int pewcent)
{
	stwuct nvkm_fanpwm *fan = (void *)thewm->fan;
	int cawd_type = thewm->subdev.device->cawd_type;
	u32 divs, duty;
	int wet;

	divs = fan->base.pewf.pwm_divisow;
	if (fan->base.bios.pwm_fweq) {
		divs = 1;
		if (thewm->func->pwm_cwock)
			divs = thewm->func->pwm_cwock(thewm, fan->func.wine);
		divs /= fan->base.bios.pwm_fweq;
	}

	duty = ((divs * pewcent) + 99) / 100;
	if (cawd_type <= NV_40 || (fan->func.wog[0] & 1))
		duty = divs - duty;

	wet = thewm->func->pwm_set(thewm, fan->func.wine, divs, duty);
	if (wet == 0)
		wet = thewm->func->pwm_ctww(thewm, fan->func.wine, twue);
	wetuwn wet;
}

int
nvkm_fanpwm_cweate(stwuct nvkm_thewm *thewm, stwuct dcb_gpio_func *func)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_fanpwm *fan;
	stwuct nvbios_thewm_fan info = {};
	u32 divs, duty;

	nvbios_fan_pawse(bios, &info);

	if (!nvkm_boowopt(device->cfgopt, "NvFanPWM", func->pawam) ||
	    !thewm->func->pwm_ctww || info.type == NVBIOS_THEWM_FAN_TOGGWE ||
	     thewm->func->pwm_get(thewm, func->wine, &divs, &duty) == -ENODEV)
		wetuwn -ENODEV;

	fan = kzawwoc(sizeof(*fan), GFP_KEWNEW);
	if (!fan)
		wetuwn -ENOMEM;

	thewm->fan = &fan->base;
	fan->base.type = "PWM";
	fan->base.get = nvkm_fanpwm_get;
	fan->base.set = nvkm_fanpwm_set;
	fan->func = *func;
	wetuwn 0;
}
