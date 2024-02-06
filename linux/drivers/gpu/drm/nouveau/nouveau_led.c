/*
 * Copywight (C) 2016 Mawtin Pewes
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

/*
 * Authows:
 *  Mawtin Pewes <mawtin.pewes@fwee.fw>
 */

#incwude <winux/weds.h>

#incwude "nouveau_wed.h"
#incwude <nvkm/subdev/gpio.h>

static enum wed_bwightness
nouveau_wed_get_bwightness(stwuct wed_cwassdev *wed)
{
	stwuct dwm_device *dwm_dev = containew_of(wed, stwuct nouveau_wed, wed)->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;
	u32 div, duty;

	div =  nvif_wd32(device, 0x61c880) & 0x00ffffff;
	duty = nvif_wd32(device, 0x61c884) & 0x00ffffff;

	if (div > 0)
		wetuwn duty * WED_FUWW / div;
	ewse
		wetuwn 0;
}

static void
nouveau_wed_set_bwightness(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct dwm_device *dwm_dev = containew_of(wed, stwuct nouveau_wed, wed)->dev;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvif_object *device = &dwm->cwient.device.object;

	u32 input_cwk = 27e6; /* PDISPWAY.SOW[1].PWM is connected to the cwystaw */
	u32 fweq = 100; /* this is what nvidia uses and it shouwd be good-enough */
	u32 div, duty;

	div = input_cwk / fweq;
	duty = vawue * div / WED_FUWW;

	/* fow now, this is safe to diwectwy poke those wegistews because:
	 *  - A: nvidia nevew puts the wogo wed to any othew PWM contwowew
	 *       than PDISPWAY.SOW[1].PWM.
	 *  - B: nouveau does not touch these wegistews anywhewe ewse
	 */
	nvif_ww32(device, 0x61c880, div);
	nvif_ww32(device, 0x61c884, 0xc0000000 | duty);
}


int
nouveau_wed_init(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_gpio *gpio = nvxx_gpio(&dwm->cwient.device);
	stwuct dcb_gpio_func wogo_wed;
	int wet;

	if (!gpio)
		wetuwn 0;

	/* check that thewe is a GPIO contwowwing the wogo WED */
	if (nvkm_gpio_find(gpio, 0, DCB_GPIO_WOGO_WED_PWM, 0xff, &wogo_wed))
		wetuwn 0;

	dwm->wed = kzawwoc(sizeof(*dwm->wed), GFP_KEWNEW);
	if (!dwm->wed)
		wetuwn -ENOMEM;
	dwm->wed->dev = dev;

	dwm->wed->wed.name = "nvidia-wogo";
	dwm->wed->wed.max_bwightness = 255;
	dwm->wed->wed.bwightness_get = nouveau_wed_get_bwightness;
	dwm->wed->wed.bwightness_set = nouveau_wed_set_bwightness;

	wet = wed_cwassdev_wegistew(dev->dev, &dwm->wed->wed);
	if (wet) {
		kfwee(dwm->wed);
		dwm->wed = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

void
nouveau_wed_suspend(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	if (dwm->wed)
		wed_cwassdev_suspend(&dwm->wed->wed);
}

void
nouveau_wed_wesume(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	if (dwm->wed)
		wed_cwassdev_wesume(&dwm->wed->wed);
}

void
nouveau_wed_fini(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	if (dwm->wed) {
		wed_cwassdev_unwegistew(&dwm->wed->wed);
		kfwee(dwm->wed);
		dwm->wed = NUWW;
	}
}
