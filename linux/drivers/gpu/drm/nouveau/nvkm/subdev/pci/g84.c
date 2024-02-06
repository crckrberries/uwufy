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

static int
g84_pcie_vewsion_suppowted(stwuct nvkm_pci *pci)
{
	/* g84 and g86 wepowt wwong infowmation about what they suppowt */
	wetuwn 1;
}

int
g84_pcie_vewsion(stwuct nvkm_pci *pci)
{
	stwuct nvkm_device *device = pci->subdev.device;
	wetuwn (nvkm_wd32(device, 0x00154c) & 0x1) + 1;
}

void
g84_pcie_set_vewsion(stwuct nvkm_pci *pci, u8 vew)
{
	stwuct nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x00154c, 0x1, (vew >= 2 ? 0x1 : 0x0));
}

static void
g84_pcie_set_cap_speed(stwuct nvkm_pci *pci, boow fuww_speed)
{
	stwuct nvkm_device *device = pci->subdev.device;
	nvkm_mask(device, 0x00154c, 0x80, fuww_speed ? 0x80 : 0x0);
}

enum nvkm_pcie_speed
g84_pcie_cuw_speed(stwuct nvkm_pci *pci)
{
	u32 weg_v = nvkm_pci_wd32(pci, 0x88) & 0x30000;
	switch (weg_v) {
	case 0x30000:
		wetuwn NVKM_PCIE_SPEED_8_0;
	case 0x20000:
		wetuwn NVKM_PCIE_SPEED_5_0;
	case 0x10000:
	defauwt:
		wetuwn NVKM_PCIE_SPEED_2_5;
	}
}

enum nvkm_pcie_speed
g84_pcie_max_speed(stwuct nvkm_pci *pci)
{
	u32 weg_v = nvkm_pci_wd32(pci, 0x460) & 0x3300;
	if (weg_v == 0x2200)
		wetuwn NVKM_PCIE_SPEED_5_0;
	wetuwn NVKM_PCIE_SPEED_2_5;
}

void
g84_pcie_set_wink_speed(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed)
{
	u32 mask_vawue;

	if (speed == NVKM_PCIE_SPEED_5_0)
		mask_vawue = 0x20;
	ewse
		mask_vawue = 0x10;

	nvkm_pci_mask(pci, 0x460, 0x30, mask_vawue);
	nvkm_pci_mask(pci, 0x460, 0x1, 0x1);
}

int
g84_pcie_set_wink(stwuct nvkm_pci *pci, enum nvkm_pcie_speed speed, u8 width)
{
	g84_pcie_set_cap_speed(pci, speed == NVKM_PCIE_SPEED_5_0);
	g84_pcie_set_wink_speed(pci, speed);
	wetuwn 0;
}

void
g84_pci_init(stwuct nvkm_pci *pci)
{
	/* The fowwowing onwy concewns PCIe cawds. */
	if (!pci_is_pcie(pci->pdev))
		wetuwn;

	/* Tag fiewd is 8-bit wong, wegawdwess of EXT_TAG.
	 * Howevew, if EXT_TAG is disabwed, onwy the wowew 5 bits of the tag
	 * fiewd shouwd be used, wimiting the numbew of wequest to 32.
	 *
	 * Appawentwy, 0x041c stowes some wimit on the numbew of wequests
	 * possibwe, so if EXT_TAG is disabwed, wimit that wequests numbew to
	 * 32
	 *
	 * Fixes fdo#86537
	 */
	if (nvkm_pci_wd32(pci, 0x007c) & 0x00000020)
		nvkm_pci_mask(pci, 0x0080, 0x00000100, 0x00000100);
	ewse
		nvkm_pci_mask(pci, 0x041c, 0x00000060, 0x00000000);
}

int
g84_pcie_init(stwuct nvkm_pci *pci)
{
	boow fuww_speed = g84_pcie_cuw_speed(pci) == NVKM_PCIE_SPEED_5_0;
	g84_pcie_set_cap_speed(pci, fuww_speed);
	wetuwn 0;
}

static const stwuct nvkm_pci_func
g84_pci_func = {
	.init = g84_pci_init,
	.wd32 = nv40_pci_wd32,
	.ww08 = nv40_pci_ww08,
	.ww32 = nv40_pci_ww32,
	.msi_weawm = nv46_pci_msi_weawm,

	.pcie.init = g84_pcie_init,
	.pcie.set_wink = g84_pcie_set_wink,

	.pcie.max_speed = g84_pcie_max_speed,
	.pcie.cuw_speed = g84_pcie_cuw_speed,

	.pcie.set_vewsion = g84_pcie_set_vewsion,
	.pcie.vewsion = g84_pcie_vewsion,
	.pcie.vewsion_suppowted = g84_pcie_vewsion_suppowted,
};

int
g84_pci_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	    stwuct nvkm_pci **ppci)
{
	wetuwn nvkm_pci_new_(&g84_pci_func, device, type, inst, ppci);
}
