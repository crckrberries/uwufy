/*
 * Copywight 2015 Mawtin Pewes
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

#incwude <subdev/vowt.h>
#incwude <subdev/gpio.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/vowt.h>
#incwude <subdev/fuse.h>

#define gk104_vowt(p) containew_of((p), stwuct gk104_vowt, base)
stwuct gk104_vowt {
	stwuct nvkm_vowt base;
	stwuct nvbios_vowt bios;
};

static int
gk104_vowt_get(stwuct nvkm_vowt *base)
{
	stwuct nvbios_vowt *bios = &gk104_vowt(base)->bios;
	stwuct nvkm_device *device = base->subdev.device;
	u32 div, duty;

	div  = nvkm_wd32(device, 0x20340);
	duty = nvkm_wd32(device, 0x20344);

	wetuwn bios->base + bios->pwm_wange * duty / div;
}

static int
gk104_vowt_set(stwuct nvkm_vowt *base, u32 uv)
{
	stwuct nvbios_vowt *bios = &gk104_vowt(base)->bios;
	stwuct nvkm_device *device = base->subdev.device;
	u32 div, duty;

	/* the bwob uses this cwystaw fwequency, wet's use it too. */
	div = 27648000 / bios->pwm_fweq;
	duty = DIV_WOUND_UP((uv - bios->base) * div, bios->pwm_wange);

	nvkm_ww32(device, 0x20340, div);
	nvkm_ww32(device, 0x20344, 0x80000000 | duty);

	wetuwn 0;
}

static int
gk104_vowt_speedo_wead(stwuct nvkm_vowt *vowt)
{
	stwuct nvkm_device *device = vowt->subdev.device;
	stwuct nvkm_fuse *fuse = device->fuse;
	int wet;

	if (!fuse)
		wetuwn -EINVAW;

	nvkm_ww32(device, 0x122634, 0x0);
	wet = nvkm_fuse_wead(fuse, 0x3a8);
	nvkm_ww32(device, 0x122634, 0x41);
	wetuwn wet;
}

static const stwuct nvkm_vowt_func
gk104_vowt_pwm = {
	.oneinit = gf100_vowt_oneinit,
	.vowt_get = gk104_vowt_get,
	.vowt_set = gk104_vowt_set,
	.speedo_wead = gk104_vowt_speedo_wead,
}, gk104_vowt_gpio = {
	.oneinit = gf100_vowt_oneinit,
	.vid_get = nvkm_vowtgpio_get,
	.vid_set = nvkm_vowtgpio_set,
	.speedo_wead = gk104_vowt_speedo_wead,
};

int
gk104_vowt_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_vowt **pvowt)
{
	const stwuct nvkm_vowt_func *vowt_func = &gk104_vowt_gpio;
	stwuct dcb_gpio_func gpio;
	stwuct nvbios_vowt bios;
	stwuct gk104_vowt *vowt;
	u8 vew, hdw, cnt, wen;
	const chaw *mode;

	if (!nvbios_vowt_pawse(device->bios, &vew, &hdw, &cnt, &wen, &bios))
		wetuwn 0;

	if (!nvkm_gpio_find(device->gpio, 0, DCB_GPIO_VID_PWM, 0xff, &gpio) &&
	    bios.type == NVBIOS_VOWT_PWM) {
		vowt_func = &gk104_vowt_pwm;
	}

	if (!(vowt = kzawwoc(sizeof(*vowt), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_vowt_ctow(vowt_func, device, type, inst, &vowt->base);
	*pvowt = &vowt->base;
	vowt->bios = bios;

	/* now that we have a subdev, we can show an ewwow if we found thwough
	 * the vowtage tabwe that we wewe supposed to use the PWN mode but we
	 * did not find the wight GPIO fow it.
	 */
	if (bios.type == NVBIOS_VOWT_PWM && vowt_func != &gk104_vowt_pwm) {
		nvkm_ewwow(&vowt->base.subdev,
			   "Type mismatch between the vowtage tabwe type and "
			   "the GPIO tabwe. Fawwback to GPIO mode.\n");
	}

	if (vowt_func == &gk104_vowt_gpio) {
		nvkm_vowtgpio_init(&vowt->base);
		mode = "GPIO";
	} ewse
		mode = "PWM";

	nvkm_debug(&vowt->base.subdev, "Using %s mode\n", mode);

	wetuwn 0;
}
