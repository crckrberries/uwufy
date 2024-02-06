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

#incwude <cowe/pci.h>

/* MSI we-awm thwough the PWI appeaws to be bwoken on NV46/NV50/G84/G86/G92,
 * so we access it via awtewnate PCI config space mechanisms.
 */
void
nv46_pci_msi_weawm(stwuct nvkm_pci *pci)
{
	stwuct nvkm_device *device = pci->subdev.device;
	stwuct pci_dev *pdev = device->func->pci(device)->pdev;
	pci_wwite_config_byte(pdev, 0x68, 0xff);
}

static const stwuct nvkm_pci_func
nv46_pci_func = {
	.wd32 = nv40_pci_wd32,
	.ww08 = nv40_pci_ww08,
	.ww32 = nv40_pci_ww32,
	.msi_weawm = nv46_pci_msi_weawm,
};

int
nv46_pci_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	     stwuct nvkm_pci **ppci)
{
	wetuwn nvkm_pci_new_(&nv46_pci_func, device, type, inst, ppci);
}
