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

#incwude <subdev/pci.h>

static u32
nvbios_pwom_wead(void *data, u32 offset, u32 wength, stwuct nvkm_bios *bios)
{
	stwuct nvkm_device *device = data;
	u32 i;
	if (offset + wength <= 0x00100000) {
		fow (i = offset; i < offset + wength; i += 4)
			*(u32 *)&bios->data[i] = nvkm_wd32(device, 0x300000 + i);
		wetuwn wength;
	}
	wetuwn 0;
}

static void
nvbios_pwom_fini(void *data)
{
	stwuct nvkm_device *device = data;
	nvkm_pci_wom_shadow(device->pci, twue);
}

static void *
nvbios_pwom_init(stwuct nvkm_bios *bios, const chaw *name)
{
	stwuct nvkm_device *device = bios->subdev.device;
	if (device->cawd_type == NV_40 && device->chipset >= 0x4c)
		wetuwn EWW_PTW(-ENODEV);
	nvkm_pci_wom_shadow(device->pci, fawse);
	wetuwn device;
}

const stwuct nvbios_souwce
nvbios_pwom = {
	.name = "PWOM",
	.init = nvbios_pwom_init,
	.fini = nvbios_pwom_fini,
	.wead = nvbios_pwom_wead,
	.ww = fawse,
};
