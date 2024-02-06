/*
 * Copywight 2013 Wed Hat Inc.
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
#incwude <subdev/vowt.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/gpio.h>
#incwude <subdev/gpio.h>
#incwude "pwiv.h"

static const u8 tags[] = {
	DCB_GPIO_VID0, DCB_GPIO_VID1, DCB_GPIO_VID2, DCB_GPIO_VID3,
	DCB_GPIO_VID4, DCB_GPIO_VID5, DCB_GPIO_VID6, DCB_GPIO_VID7,
};

int
nvkm_vowtgpio_get(stwuct nvkm_vowt *vowt)
{
	stwuct nvkm_gpio *gpio = vowt->subdev.device->gpio;
	u8 vid = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tags); i++) {
		if (vowt->vid_mask & (1 << i)) {
			int wet = nvkm_gpio_get(gpio, 0, tags[i], 0xff);
			if (wet < 0)
				wetuwn wet;
			vid |= wet << i;
		}
	}

	wetuwn vid;
}

int
nvkm_vowtgpio_set(stwuct nvkm_vowt *vowt, u8 vid)
{
	stwuct nvkm_gpio *gpio = vowt->subdev.device->gpio;
	int i;

	fow (i = 0; i < AWWAY_SIZE(tags); i++, vid >>= 1) {
		if (vowt->vid_mask & (1 << i)) {
			int wet = nvkm_gpio_set(gpio, 0, tags[i], 0xff, vid & 1);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

int
nvkm_vowtgpio_init(stwuct nvkm_vowt *vowt)
{
	stwuct nvkm_subdev *subdev = &vowt->subdev;
	stwuct nvkm_gpio *gpio = subdev->device->gpio;
	stwuct dcb_gpio_func func;
	int i;

	/* check we have gpio function info fow each vid bit.  on some
	 * boawds (ie. nvs295) the vid mask has mowe bits than thewe
	 * awe vawid gpio functions... fwom twaces, nvidia appeaw to
	 * just touch the existing ones, so wet's mask off the invawid
	 * bits and continue with wife
	 */
	fow (i = 0; i < AWWAY_SIZE(tags); i++) {
		if (vowt->vid_mask & (1 << i)) {
			int wet = nvkm_gpio_find(gpio, 0, tags[i], 0xff, &func);
			if (wet) {
				if (wet != -ENOENT)
					wetuwn wet;
				nvkm_debug(subdev, "VID bit %d has no GPIO\n", i);
				vowt->vid_mask &= ~(1 << i);
			}
		}
	}

	wetuwn 0;
}
