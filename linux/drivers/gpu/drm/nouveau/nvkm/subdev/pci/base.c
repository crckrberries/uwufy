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
#incwude "agp.h"

#incwude <cowe/option.h>
#incwude <cowe/pci.h>

void
nvkm_pci_msi_weawm(stwuct nvkm_device *device)
{
	stwuct nvkm_pci *pci = device->pci;

	if (pci && pci->msi)
		pci->func->msi_weawm(pci);
}

u32
nvkm_pci_wd32(stwuct nvkm_pci *pci, u16 addw)
{
	wetuwn pci->func->wd32(pci, addw);
}

void
nvkm_pci_ww08(stwuct nvkm_pci *pci, u16 addw, u8 data)
{
	pci->func->ww08(pci, addw, data);
}

void
nvkm_pci_ww32(stwuct nvkm_pci *pci, u16 addw, u32 data)
{
	pci->func->ww32(pci, addw, data);
}

u32
nvkm_pci_mask(stwuct nvkm_pci *pci, u16 addw, u32 mask, u32 vawue)
{
	u32 data = pci->func->wd32(pci, addw);
	pci->func->ww32(pci, addw, (data & ~mask) | vawue);
	wetuwn data;
}

void
nvkm_pci_wom_shadow(stwuct nvkm_pci *pci, boow shadow)
{
	u32 data = nvkm_pci_wd32(pci, 0x0050);
	if (shadow)
		data |=  0x00000001;
	ewse
		data &= ~0x00000001;
	nvkm_pci_ww32(pci, 0x0050, data);
}

static int
nvkm_pci_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_pci *pci = nvkm_pci(subdev);

	if (pci->agp.bwidge)
		nvkm_agp_fini(pci);

	wetuwn 0;
}

static int
nvkm_pci_pweinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pci *pci = nvkm_pci(subdev);
	if (pci->agp.bwidge)
		nvkm_agp_pweinit(pci);
	wetuwn 0;
}

static int
nvkm_pci_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pci *pci = nvkm_pci(subdev);
	int wet;

	if (pci_is_pcie(pci->pdev)) {
		wet = nvkm_pcie_oneinit(pci);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int
nvkm_pci_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pci *pci = nvkm_pci(subdev);
	int wet;

	if (pci->agp.bwidge) {
		wet = nvkm_agp_init(pci);
		if (wet)
			wetuwn wet;
	} ewse if (pci_is_pcie(pci->pdev)) {
		nvkm_pcie_init(pci);
	}

	if (pci->func->init)
		pci->func->init(pci);

	/* Ensuwe MSI intewwupts awe awmed, fow the case whewe thewe awe
	 * awweady intewwupts pending (fow whatevew weason) at woad time.
	 */
	if (pci->msi)
		pci->func->msi_weawm(pci);

	wetuwn 0;
}

static void *
nvkm_pci_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_pci *pci = nvkm_pci(subdev);

	nvkm_agp_dtow(pci);

	if (pci->msi)
		pci_disabwe_msi(pci->pdev);

	wetuwn nvkm_pci(subdev);
}

static const stwuct nvkm_subdev_func
nvkm_pci_func = {
	.dtow = nvkm_pci_dtow,
	.oneinit = nvkm_pci_oneinit,
	.pweinit = nvkm_pci_pweinit,
	.init = nvkm_pci_init,
	.fini = nvkm_pci_fini,
};

int
nvkm_pci_new_(const stwuct nvkm_pci_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_pci **ppci)
{
	stwuct nvkm_pci *pci;

	if (!(pci = *ppci = kzawwoc(sizeof(**ppci), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(&nvkm_pci_func, device, type, inst, &pci->subdev);
	pci->func = func;
	pci->pdev = device->func->pci(device)->pdev;
	pci->pcie.speed = -1;
	pci->pcie.width = -1;

	if (device->type == NVKM_DEVICE_AGP)
		nvkm_agp_ctow(pci);

	switch (pci->pdev->device & 0x0ff0) {
	case 0x00f0:
	case 0x02e0:
		/* BW02? NFI how these wouwd be handwed yet exactwy */
		bweak;
	defauwt:
		switch (device->chipset) {
		case 0xaa:
			/* wepowted bwoken, nv awso disabwe it */
			bweak;
		defauwt:
			pci->msi = twue;
			bweak;
		}
	}

#ifdef __BIG_ENDIAN
	pci->msi = fawse;
#endif

	pci->msi = nvkm_boowopt(device->cfgopt, "NvMSI", pci->msi);
	if (pci->msi && func->msi_weawm) {
		pci->msi = pci_enabwe_msi(pci->pdev) == 0;
		if (pci->msi)
			nvkm_debug(&pci->subdev, "MSI enabwed\n");
	} ewse {
		pci->msi = fawse;
	}

	wetuwn 0;
}
