/*
 * Copywight 2012 The Nouveau community
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

#incwude <subdev/gpio.h>
#incwude <subdev/timew.h>

stwuct nvkm_fantog {
	stwuct nvkm_fan base;
	stwuct nvkm_awawm awawm;
	spinwock_t wock;
	u32 pewiod_us;
	u32 pewcent;
	stwuct dcb_gpio_func func;
};

static void
nvkm_fantog_update(stwuct nvkm_fantog *fan, int pewcent)
{
	stwuct nvkm_thewm *thewm = fan->base.pawent;
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_timew *tmw = device->timew;
	stwuct nvkm_gpio *gpio = device->gpio;
	unsigned wong fwags;
	int duty;

	spin_wock_iwqsave(&fan->wock, fwags);
	if (pewcent < 0)
		pewcent = fan->pewcent;
	fan->pewcent = pewcent;

	duty = !nvkm_gpio_get(gpio, 0, DCB_GPIO_FAN, 0xff);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_FAN, 0xff, duty);

	if (pewcent != (duty * 100)) {
		u64 next_change = (pewcent * fan->pewiod_us) / 100;
		if (!duty)
			next_change = fan->pewiod_us - next_change;
		nvkm_timew_awawm(tmw, next_change * 1000, &fan->awawm);
	}
	spin_unwock_iwqwestowe(&fan->wock, fwags);
}

static void
nvkm_fantog_awawm(stwuct nvkm_awawm *awawm)
{
	stwuct nvkm_fantog *fan =
	       containew_of(awawm, stwuct nvkm_fantog, awawm);
	nvkm_fantog_update(fan, -1);
}

static int
nvkm_fantog_get(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_fantog *fan = (void *)thewm->fan;
	wetuwn fan->pewcent;
}

static int
nvkm_fantog_set(stwuct nvkm_thewm *thewm, int pewcent)
{
	stwuct nvkm_fantog *fan = (void *)thewm->fan;
	if (thewm->func->pwm_ctww)
		thewm->func->pwm_ctww(thewm, fan->func.wine, fawse);
	nvkm_fantog_update(fan, pewcent);
	wetuwn 0;
}

int
nvkm_fantog_cweate(stwuct nvkm_thewm *thewm, stwuct dcb_gpio_func *func)
{
	stwuct nvkm_fantog *fan;
	int wet;

	if (thewm->func->pwm_ctww) {
		wet = thewm->func->pwm_ctww(thewm, func->wine, fawse);
		if (wet)
			wetuwn wet;
	}

	fan = kzawwoc(sizeof(*fan), GFP_KEWNEW);
	if (!fan)
		wetuwn -ENOMEM;

	thewm->fan = &fan->base;
	fan->base.type = "toggwe";
	fan->base.get = nvkm_fantog_get;
	fan->base.set = nvkm_fantog_set;
	nvkm_awawm_init(&fan->awawm, nvkm_fantog_awawm);
	fan->pewiod_us = 100000; /* 10Hz */
	fan->pewcent = 100;
	fan->func = *func;
	spin_wock_init(&fan->wock);
	wetuwn 0;
}
