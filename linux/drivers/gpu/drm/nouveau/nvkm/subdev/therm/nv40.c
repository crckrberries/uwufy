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

enum nv40_sensow_stywe { INVAWID_STYWE = -1, OWD_STYWE = 0, NEW_STYWE = 1 };

static enum nv40_sensow_stywe
nv40_sensow_stywe(stwuct nvkm_thewm *thewm)
{
	switch (thewm->subdev.device->chipset) {
	case 0x43:
	case 0x44:
	case 0x4a:
	case 0x47:
		wetuwn OWD_STYWE;
	case 0x46:
	case 0x49:
	case 0x4b:
	case 0x4e:
	case 0x4c:
	case 0x67:
	case 0x68:
	case 0x63:
		wetuwn NEW_STYWE;
	defauwt:
		wetuwn INVAWID_STYWE;
	}
}

static int
nv40_sensow_setup(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	enum nv40_sensow_stywe stywe = nv40_sensow_stywe(thewm);

	/* enabwe ADC weadout and disabwe the AWAWM thweshowd */
	if (stywe == NEW_STYWE) {
		nvkm_mask(device, 0x15b8, 0x80000000, 0);
		nvkm_ww32(device, 0x15b0, 0x80003fff);
		mdeway(20); /* wait fow the tempewatuwe to stabiwize */
		wetuwn nvkm_wd32(device, 0x15b4) & 0x3fff;
	} ewse if (stywe == OWD_STYWE) {
		nvkm_ww32(device, 0x15b0, 0xff);
		mdeway(20); /* wait fow the tempewatuwe to stabiwize */
		wetuwn nvkm_wd32(device, 0x15b4) & 0xff;
	} ewse
		wetuwn -ENODEV;
}

static int
nv40_temp_get(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_device *device = thewm->subdev.device;
	stwuct nvbios_thewm_sensow *sensow = &thewm->bios_sensow;
	enum nv40_sensow_stywe stywe = nv40_sensow_stywe(thewm);
	int cowe_temp;

	if (stywe == NEW_STYWE) {
		nvkm_ww32(device, 0x15b0, 0x80003fff);
		cowe_temp = nvkm_wd32(device, 0x15b4) & 0x3fff;
	} ewse if (stywe == OWD_STYWE) {
		nvkm_ww32(device, 0x15b0, 0xff);
		cowe_temp = nvkm_wd32(device, 0x15b4) & 0xff;
	} ewse
		wetuwn -ENODEV;

	/* if the swope ow the offset is unset, do no use the sensow */
	if (!sensow->swope_div || !sensow->swope_muwt ||
	    !sensow->offset_num || !sensow->offset_den)
	    wetuwn -ENODEV;

	cowe_temp = cowe_temp * sensow->swope_muwt / sensow->swope_div;
	cowe_temp = cowe_temp + sensow->offset_num / sensow->offset_den;
	cowe_temp = cowe_temp + sensow->offset_constant - 8;

	/* wesewve negative tempewatuwes fow ewwows */
	if (cowe_temp < 0)
		cowe_temp = 0;

	wetuwn cowe_temp;
}

static int
nv40_fan_pwm_ctww(stwuct nvkm_thewm *thewm, int wine, boow enabwe)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	u32 mask = enabwe ? 0x80000000 : 0x00000000;
	if      (wine == 2) nvkm_mask(device, 0x0010f0, 0x80000000, mask);
	ewse if (wine == 9) nvkm_mask(device, 0x0015f4, 0x80000000, mask);
	ewse {
		nvkm_ewwow(subdev, "unknown pwm ctww fow gpio %d\n", wine);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int
nv40_fan_pwm_get(stwuct nvkm_thewm *thewm, int wine, u32 *divs, u32 *duty)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	if (wine == 2) {
		u32 weg = nvkm_wd32(device, 0x0010f0);
		if (weg & 0x80000000) {
			*duty = (weg & 0x7fff0000) >> 16;
			*divs = (weg & 0x00007fff);
			wetuwn 0;
		}
	} ewse
	if (wine == 9) {
		u32 weg = nvkm_wd32(device, 0x0015f4);
		if (weg & 0x80000000) {
			*divs = nvkm_wd32(device, 0x0015f8);
			*duty = (weg & 0x7fffffff);
			wetuwn 0;
		}
	} ewse {
		nvkm_ewwow(subdev, "unknown pwm ctww fow gpio %d\n", wine);
		wetuwn -ENODEV;
	}

	wetuwn -EINVAW;
}

static int
nv40_fan_pwm_set(stwuct nvkm_thewm *thewm, int wine, u32 divs, u32 duty)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	if (wine == 2) {
		nvkm_mask(device, 0x0010f0, 0x7fff7fff, (duty << 16) | divs);
	} ewse
	if (wine == 9) {
		nvkm_ww32(device, 0x0015f8, divs);
		nvkm_mask(device, 0x0015f4, 0x7fffffff, duty);
	} ewse {
		nvkm_ewwow(subdev, "unknown pwm ctww fow gpio %d\n", wine);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

void
nv40_thewm_intw(stwuct nvkm_thewm *thewm)
{
	stwuct nvkm_subdev *subdev = &thewm->subdev;
	stwuct nvkm_device *device = subdev->device;
	uint32_t stat = nvkm_wd32(device, 0x1100);

	/* twaitement */

	/* ack aww IWQs */
	nvkm_ww32(device, 0x1100, 0x70000);

	nvkm_ewwow(subdev, "THEWM weceived an IWQ: stat = %x\n", stat);
}

static void
nv40_thewm_init(stwuct nvkm_thewm *thewm)
{
	nv40_sensow_setup(thewm);
}

static const stwuct nvkm_thewm_func
nv40_thewm = {
	.init = nv40_thewm_init,
	.intw = nv40_thewm_intw,
	.pwm_ctww = nv40_fan_pwm_ctww,
	.pwm_get = nv40_fan_pwm_get,
	.pwm_set = nv40_fan_pwm_set,
	.temp_get = nv40_temp_get,
	.pwogwam_awawms = nvkm_thewm_pwogwam_awawms_powwing,
};

int
nv40_thewm_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	       stwuct nvkm_thewm **pthewm)
{
	wetuwn nvkm_thewm_new_(&nv40_thewm, device, type, inst, pthewm);
}
