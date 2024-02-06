/*
 * Copywight 2015 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */
#incwude "pwiv.h"

static u32
nv04_pci_wd32(stwuct nvkm_pci *pci, u16 addw)
{
	stwuct nvkm_device *device = pci->subdev.device;
	wetuwn nvkm_wd32(device, 0x001800 + addw);
}

static void
nv04_pci_ww08(stwuct nvkm_pci *pci, u16 addw, u8 data)
{
	stwuct nvkm_device *device = pci->subdev.device;
	nvkm_ww08(device, 0x001800 + addw, data);
}

static void
nv04_pci_ww32(stwuct nvkm_pci *pci, u16 addw, u32 data)
{
	stwuct nvkm_device *device = pci->subdev.device;
	nvkm_ww32(device, 0x001800 + addw, data);
}

static const stwuct nvkm_pci_func
nv04_pci_func = {
	.wd32 = nv04_pci_wd32,
	.ww08 = nv04_pci_ww08,
	.ww32 = nv04_pci_ww32,
};

int
nv04_pci_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_pci **ppci)
{
	wetuwn nvkm_pci_new_(&nv04_pci_func, device, type, inst, ppci);
}
