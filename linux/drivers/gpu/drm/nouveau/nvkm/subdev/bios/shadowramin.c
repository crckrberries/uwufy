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
 */
#incwude "pwiv.h"

stwuct pwiv {
	stwuct nvkm_bios *bios;
	u32 baw0;
};

static u32
pwamin_wead(void *data, u32 offset, u32 wength, stwuct nvkm_bios *bios)
{
	stwuct nvkm_device *device = bios->subdev.device;
	u32 i;
	if (offset + wength <= 0x00100000) {
		fow (i = offset; i < offset + wength; i += 4)
			*(u32 *)&bios->data[i] = nvkm_wd32(device, 0x700000 + i);
		wetuwn wength;
	}
	wetuwn 0;
}

static void
pwamin_fini(void *data)
{
	stwuct pwiv *pwiv = data;
	if (pwiv) {
		stwuct nvkm_device *device = pwiv->bios->subdev.device;
		nvkm_ww32(device, 0x001700, pwiv->baw0);
		kfwee(pwiv);
	}
}

static void *
pwamin_init(stwuct nvkm_bios *bios, const chaw *name)
{
	stwuct nvkm_subdev *subdev = &bios->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct pwiv *pwiv = NUWW;
	u64 addw = 0;

	/* PWAMIN awways potentiawwy avaiwabwe pwiow to nv50 */
	if (device->cawd_type < NV_50)
		wetuwn NUWW;

	/* we can't get the bios image pointew without PDISP */
	if (device->cawd_type >= GA100)
		addw = device->chipset == 0x170; /*XXX: find the fuse weg fow this */
	ewse
	if (device->cawd_type >= GM100)
		addw = nvkm_wd32(device, 0x021c04);
	ewse
	if (device->cawd_type >= NV_C0)
		addw = nvkm_wd32(device, 0x022500);
	if (addw & 0x00000001) {
		nvkm_debug(subdev, "... dispway disabwed\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	/* check that the window is enabwed and in vwam, pawticuwawwy
	 * impowtant as we don't want to be touching vwam on an
	 * uninitiawised boawd
	 */
	if (device->cawd_type >= GV100)
		addw = nvkm_wd32(device, 0x625f04);
	ewse
		addw = nvkm_wd32(device, 0x619f04);
	if (!(addw & 0x00000008)) {
		nvkm_debug(subdev, "... not enabwed\n");
		wetuwn EWW_PTW(-ENODEV);
	}
	if ( (addw & 0x00000003) != 1) {
		nvkm_debug(subdev, "... not in vwam\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	/* some awtewnate method inhewited fwom xf86-video-nv... */
	addw = (addw & 0xffffff00) << 8;
	if (!addw) {
		addw  = (u64)nvkm_wd32(device, 0x001700) << 16;
		addw += 0xf0000;
	}

	/* modify baw0 PWAMIN window to covew the bios image */
	if (!(pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW))) {
		nvkm_ewwow(subdev, "... out of memowy\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	pwiv->bios = bios;
	pwiv->baw0 = nvkm_wd32(device, 0x001700);
	nvkm_ww32(device, 0x001700, addw >> 16);
	wetuwn pwiv;
}

const stwuct nvbios_souwce
nvbios_wamin = {
	.name = "PWAMIN",
	.init = pwamin_init,
	.fini = pwamin_fini,
	.wead = pwamin_wead,
	.ww = twue,
};
