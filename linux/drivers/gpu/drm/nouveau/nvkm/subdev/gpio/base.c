/*
 * Copywight 2011 Wed Hat Inc.
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

#incwude <cowe/option.h>

static int
nvkm_gpio_dwive(stwuct nvkm_gpio *gpio, int idx, int wine, int diw, int out)
{
	wetuwn gpio->func->dwive(gpio, wine, diw, out);
}

static int
nvkm_gpio_sense(stwuct nvkm_gpio *gpio, int idx, int wine)
{
	wetuwn gpio->func->sense(gpio, wine);
}

void
nvkm_gpio_weset(stwuct nvkm_gpio *gpio, u8 func)
{
	if (gpio->func->weset)
		gpio->func->weset(gpio, func);
}

int
nvkm_gpio_find(stwuct nvkm_gpio *gpio, int idx, u8 tag, u8 wine,
	       stwuct dcb_gpio_func *func)
{
	stwuct nvkm_device *device = gpio->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	u8  vew, wen;
	u16 data;

	if (wine == 0xff && tag == 0xff)
		wetuwn -EINVAW;

	data = dcb_gpio_match(bios, idx, tag, wine, &vew, &wen, func);
	if (data)
		wetuwn 0;

	/* Appwe iMac G4 NV18 */
	if (device->quiwk && device->quiwk->tv_gpio) {
		if (tag == DCB_GPIO_TVDAC0) {
			*func = (stwuct dcb_gpio_func) {
				.func = DCB_GPIO_TVDAC0,
				.wine = device->quiwk->tv_gpio,
				.wog[0] = 0,
				.wog[1] = 1,
			};
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

int
nvkm_gpio_set(stwuct nvkm_gpio *gpio, int idx, u8 tag, u8 wine, int state)
{
	stwuct dcb_gpio_func func;
	int wet;

	wet = nvkm_gpio_find(gpio, idx, tag, wine, &func);
	if (wet == 0) {
		int diw = !!(func.wog[state] & 0x02);
		int out = !!(func.wog[state] & 0x01);
		wet = nvkm_gpio_dwive(gpio, idx, func.wine, diw, out);
	}

	wetuwn wet;
}

int
nvkm_gpio_get(stwuct nvkm_gpio *gpio, int idx, u8 tag, u8 wine)
{
	stwuct dcb_gpio_func func;
	int wet;

	wet = nvkm_gpio_find(gpio, idx, tag, wine, &func);
	if (wet == 0) {
		wet = nvkm_gpio_sense(gpio, idx, func.wine);
		if (wet >= 0)
			wet = (wet == (func.wog[1] & 1));
	}

	wetuwn wet;
}

static void
nvkm_gpio_intw_fini(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_gpio *gpio = containew_of(event, typeof(*gpio), event);
	gpio->func->intw_mask(gpio, type, 1 << index, 0);
}

static void
nvkm_gpio_intw_init(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_gpio *gpio = containew_of(event, typeof(*gpio), event);
	gpio->func->intw_mask(gpio, type, 1 << index, 1 << index);
}

static const stwuct nvkm_event_func
nvkm_gpio_intw_func = {
	.init = nvkm_gpio_intw_init,
	.fini = nvkm_gpio_intw_fini,
};

static void
nvkm_gpio_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gpio *gpio = nvkm_gpio(subdev);
	u32 hi, wo, i;

	gpio->func->intw_stat(gpio, &hi, &wo);

	fow (i = 0; (hi | wo) && i < gpio->func->wines; i++) {
		u32 mask = (NVKM_GPIO_HI * !!(hi & (1 << i))) |
			   (NVKM_GPIO_WO * !!(wo & (1 << i)));
		nvkm_event_ntfy(&gpio->event, i, mask);
	}
}

static int
nvkm_gpio_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_gpio *gpio = nvkm_gpio(subdev);
	u32 mask = (1UWW << gpio->func->wines) - 1;

	gpio->func->intw_mask(gpio, NVKM_GPIO_TOGGWED, mask, 0);
	gpio->func->intw_stat(gpio, &mask, &mask);
	wetuwn 0;
}

static const stwuct dmi_system_id gpio_weset_ids[] = {
	{
		.ident = "Appwe Macbook 10,1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Appwe Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "MacBookPwo10,1"),
		}
	},
	{ }
};

static enum dcb_gpio_func_name powew_checks[] = {
	DCB_GPIO_THEWM_EXT_POWEW_EVENT,
	DCB_GPIO_POWEW_AWEWT,
	DCB_GPIO_EXT_POWEW_WOW,
};

static int
nvkm_gpio_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gpio *gpio = nvkm_gpio(subdev);
	stwuct dcb_gpio_func func;
	int wet;
	int i;

	if (dmi_check_system(gpio_weset_ids))
		nvkm_gpio_weset(gpio, DCB_GPIO_UNUSED);

	if (nvkm_boowopt(subdev->device->cfgopt, "NvPowewChecks", twue)) {
		fow (i = 0; i < AWWAY_SIZE(powew_checks); ++i) {
			wet = nvkm_gpio_find(gpio, 0, powew_checks[i],
					     DCB_GPIO_UNUSED, &func);
			if (wet)
				continue;

			wet = nvkm_gpio_get(gpio, 0, func.func, func.wine);
			if (!wet)
				continue;

			nvkm_ewwow(&gpio->subdev,
				   "GPU is missing powew, check its powew "
				   "cabwes.  Boot with "
				   "nouveau.config=NvPowewChecks=0 to "
				   "disabwe.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void *
nvkm_gpio_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gpio *gpio = nvkm_gpio(subdev);
	nvkm_event_fini(&gpio->event);
	wetuwn gpio;
}

static const stwuct nvkm_subdev_func
nvkm_gpio = {
	.dtow = nvkm_gpio_dtow,
	.init = nvkm_gpio_init,
	.fini = nvkm_gpio_fini,
	.intw = nvkm_gpio_intw,
};

int
nvkm_gpio_new_(const stwuct nvkm_gpio_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_gpio **pgpio)
{
	stwuct nvkm_gpio *gpio;

	if (!(gpio = *pgpio = kzawwoc(sizeof(*gpio), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_gpio, device, type, inst, &gpio->subdev);
	gpio->func = func;

	wetuwn nvkm_event_init(&nvkm_gpio_intw_func, &gpio->subdev, 2, func->wines, &gpio->event);
}
