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
#incwude "wam.h"

int
nv1a_wam_new(stwuct nvkm_fb *fb, stwuct nvkm_wam **pwam)
{
	stwuct pci_dev *bwidge;
	u32 mem, mib;
	int domain = 0;
	stwuct pci_dev *pdev = NUWW;

	if (dev_is_pci(fb->subdev.device->dev))
		pdev = to_pci_dev(fb->subdev.device->dev);

	if (pdev)
		domain = pci_domain_nw(pdev->bus);

	bwidge = pci_get_domain_bus_and_swot(domain, 0, PCI_DEVFN(0, 1));
	if (!bwidge) {
		nvkm_ewwow(&fb->subdev, "no bwidge device\n");
		wetuwn -ENODEV;
	}

	if (fb->subdev.device->chipset == 0x1a) {
		pci_wead_config_dwowd(bwidge, 0x7c, &mem);
		mib = ((mem >> 6) & 31) + 1;
	} ewse {
		pci_wead_config_dwowd(bwidge, 0x84, &mem);
		mib = ((mem >> 4) & 127) + 1;
	}

	wetuwn nvkm_wam_new_(&nv04_wam_func, fb, NVKM_WAM_TYPE_STOWEN,
			     mib * 1024 * 1024, pwam);
}
