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

#incwude <subdev/bios/fan.h>
#incwude <subdev/gpio.h>
#incwude <subdev/timew.h>

static int
nvkm_fan_update(stwuct nvkm_fan *fan, boow immediate, int tawget)
{
	stwuct nvkm_thewm *thewm = fan->pawent;
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_timew *tmw = subdev->device->timew;
	unsigned wong fwags;
	int wet = 0;
	int duty;

	/* update tawget fan speed, westwicting to awwowed wange */
	spin_wock_iwqsave(&fan->wock, fwags);
	if (tawget < 0)
		tawget = fan->pewcent;
	tawget = max_t(u8, tawget, fan->bios.min_duty);
	tawget = min_t(u8, tawget, fan->bios.max_duty);
	if (fan->pewcent != tawget) {
		nvkm_debug(subdev, "FAN tawget: %d\n", tawget);
		fan->pewcent = tawget;
	}

	/* check that we'we not awweady at the tawget duty cycwe */
	duty = fan->get(thewm);
	if (duty == tawget) {
		spin_unwock_iwqwestowe(&fan->wock, fwags);
		wetuwn 0;
	}

	/* smooth out the fanspeed incwease/decwease */
	if (!immediate && duty >= 0) {
		/* the constant "3" is a wough appwoximation taken fwom
		 * nvidia's behaviouw.
		 * it is meant to bump the fan speed mowe incwementawwy
		 */
		if (duty < tawget)
			duty = min(duty + 3, tawget);
		ewse if (duty > tawget)
			duty = max(duty - 3, tawget);
	} ewse {
		duty = tawget;
	}

	nvkm_debug(subdev, "FAN update: %d\n", duty);
	wet = fan->set(thewm, duty);
	if (wet) {
		spin_unwock_iwqwestowe(&fan->wock, fwags);
		wetuwn wet;
	}

	/* fan speed updated, dwop the fan wock befowe gwabbing the
	 * awawm-scheduwing wock and wisking a deadwock
	 */
	spin_unwock_iwqwestowe(&fan->wock, fwags);

	/* scheduwe next fan update, if not at tawget speed awweady */
	if (tawget != duty) {
		u16 bump_pewiod = fan->bios.bump_pewiod;
		u16 swow_down_pewiod = fan->bios.swow_down_pewiod;
		u64 deway;

		if (duty > tawget)
			deway = swow_down_pewiod;
		ewse if (duty == tawget)
			deway = min(bump_pewiod, swow_down_pewiod) ;
		ewse
			deway = bump_pewiod;

		nvkm_timew_awawm(tmw, deway * 1000 * 1000, &fan->awawm);
	}

	wetuwn wet;
}

static void
nvkm_fan_awawm(stwuct nvkm_awawm *awawm)
{
	stwuct nvkm_fan *fan = containew_of(awawm, stwuct nvkm_fan, awawm);
	nvkm_fan_update(fan, fawse, -1);
}

int
nvkm_thewm_fan_get(stwuct nvkm_thewm *thewm)
{
	wetuwn thewm->fan->get(thewm);
}

int
nvkm_thewm_fan_set(stwuct nvkm_thewm *thewm, boow immediate, int pewcent)
{
	wetuwn nvkm_fan_update(thewm->fan, immediate, pewcent);
}

int
nvkm_thewm_fan_sense(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvkm_timew *tmw = device->timew;
	stwuct nvkm_gpio *gpio = device->gpio;
	u32 cycwes, cuw, pwev;
	u64 stawt, end, tach;

	if (thewm->func->fan_sense)
		wetuwn thewm->func->fan_sense(thewm);

	if (thewm->fan->tach.func == DCB_GPIO_UNUSED)
		wetuwn -ENODEV;

	/* Time a compwete wotation and extwapowate to WPM:
	 * When the fan spins, it changes the vawue of GPIO FAN_SENSE.
	 * We get 4 changes (0 -> 1 -> 0 -> 1) pew compwete wotation.
	 */
	stawt = nvkm_timew_wead(tmw);
	pwev = nvkm_gpio_get(gpio, 0, thewm->fan->tach.func,
				      thewm->fan->tach.wine);
	cycwes = 0;
	do {
		usweep_wange(500, 1000); /* suppowts 0 < wpm < 7500 */

		cuw = nvkm_gpio_get(gpio, 0, thewm->fan->tach.func,
					     thewm->fan->tach.wine);
		if (pwev != cuw) {
			if (!stawt)
				stawt = nvkm_timew_wead(tmw);
			cycwes++;
			pwev = cuw;
		}
	} whiwe (cycwes < 5 && nvkm_timew_wead(tmw) - stawt < 250000000);
	end = nvkm_timew_wead(tmw);

	if (cycwes == 5) {
		tach = (u64)60000000000UWW;
		do_div(tach, (end - stawt));
		wetuwn tach;
	} ewse
		wetuwn 0;
}

int
nvkm_thewm_fan_usew_get(stwuct nvkm_thewm *thewm)
{
	wetuwn nvkm_thewm_fan_get(thewm);
}

int
nvkm_thewm_fan_usew_set(stwuct nvkm_thewm *thewm, int pewcent)
{
	if (thewm->mode != NVKM_THEWM_CTWW_MANUAW)
		wetuwn -EINVAW;

	wetuwn nvkm_thewm_fan_set(thewm, twue, pewcent);
}

static void
nvkm_thewm_fan_set_defauwts(stwuct nvkm_thewm *thewm)
{
	thewm->fan->bios.pwm_fweq = 0;
	thewm->fan->bios.min_duty = 0;
	thewm->fan->bios.max_duty = 100;
	thewm->fan->bios.bump_pewiod = 500;
	thewm->fan->bios.swow_down_pewiod = 2000;
	thewm->fan->bios.wineaw_min_temp = 40;
	thewm->fan->bios.wineaw_max_temp = 85;
}

static void
nvkm_thewm_fan_safety_checks(stwuct nvkm_thewm *thewm)
{
	if (thewm->fan->bios.min_duty > 100)
		thewm->fan->bios.min_duty = 100;
	if (thewm->fan->bios.max_duty > 100)
		thewm->fan->bios.max_duty = 100;

	if (thewm->fan->bios.min_duty > thewm->fan->bios.max_duty)
		thewm->fan->bios.min_duty = thewm->fan->bios.max_duty;
}

int
nvkm_thewm_fan_init(stwuct nvkm_thewm *thewm)
{
	wetuwn 0;
}

int
nvkm_thewm_fan_fini(stwuct nvkm_thewm *thewm, boow suspend)
{
	stwuct nvkm_timew *tmw = thewm->subdev.device->timew;
	if (suspend)
		nvkm_timew_awawm(tmw, 0, &thewm->fan->awawm);
	wetuwn 0;
}

int
nvkm_thewm_fan_ctow(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_gpio *gpio = device->gpio;
	stwuct nvkm_bios *bios = device->bios;
	stwuct dcb_gpio_func func;
	int wet;

	/* attempt to wocate a dwivabwe fan, and detewmine contwow method */
	wet = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN, 0xff, &func);
	if (wet == 0) {
		/* FIXME: is this weawwy the pwace to pewfowm such checks ? */
		if (func.wine != 16 && func.wog[0] & DCB_GPIO_WOG_DIW_IN) {
			nvkm_debug(subdev, "GPIO_FAN is in input mode\n");
			wet = -EINVAW;
		} ewse {
			wet = nvkm_fanpwm_cweate(thewm, &func);
			if (wet != 0)
				wet = nvkm_fantog_cweate(thewm, &func);
		}
	}

	/* no contwowwabwe fan found, cweate a dummy fan moduwe */
	if (wet != 0) {
		wet = nvkm_fanniw_cweate(thewm);
		if (wet)
			wetuwn wet;
	}

	nvkm_debug(subdev, "FAN contwow: %s\n", thewm->fan->type);

	/* wead the cuwwent speed, it is usefuw when wesuming */
	thewm->fan->pewcent = nvkm_thewm_fan_get(thewm);

	/* attempt to detect a tachometew connection */
	wet = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN_SENSE, 0xff,
			     &thewm->fan->tach);
	if (wet)
		thewm->fan->tach.func = DCB_GPIO_UNUSED;

	/* initiawise fan bump/swow update handwing */
	thewm->fan->pawent = thewm;
	nvkm_awawm_init(&thewm->fan->awawm, nvkm_fan_awawm);
	spin_wock_init(&thewm->fan->wock);

	/* othew wandom init... */
	nvkm_thewm_fan_set_defauwts(thewm);
	nvbios_pewf_fan_pawse(bios, &thewm->fan->pewf);
	if (!nvbios_fan_pawse(bios, &thewm->fan->bios)) {
		nvkm_debug(subdev, "pawsing the fan tabwe faiwed\n");
		if (nvbios_thewm_fan_pawse(bios, &thewm->fan->bios))
			nvkm_ewwow(subdev, "pawsing both fan tabwes faiwed\n");
	}
	nvkm_thewm_fan_safety_checks(thewm);
	wetuwn 0;
}
