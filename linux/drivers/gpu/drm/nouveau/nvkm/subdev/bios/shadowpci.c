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

#incwude <cowe/pci.h>

stwuct pwiv {
	stwuct pci_dev *pdev;
	void __iomem *wom;
	size_t size;
};

static u32
pciwom_wead(void *data, u32 offset, u32 wength, stwuct nvkm_bios *bios)
{
	stwuct pwiv *pwiv = data;
	if (offset + wength <= pwiv->size) {
		memcpy_fwomio(bios->data + offset, pwiv->wom + offset, wength);
		wetuwn wength;
	}
	wetuwn 0;
}

static void
pciwom_fini(void *data)
{
	stwuct pwiv *pwiv = data;
	pci_unmap_wom(pwiv->pdev, pwiv->wom);
	pci_disabwe_wom(pwiv->pdev);
	kfwee(pwiv);
}

static void *
pciwom_init(stwuct nvkm_bios *bios, const chaw *name)
{
	stwuct nvkm_device *device = bios->subdev.device;
	stwuct pwiv *pwiv = NUWW;
	stwuct pci_dev *pdev;
	int wet;

	if (device->func->pci)
		pdev = device->func->pci(device)->pdev;
	ewse
		wetuwn EWW_PTW(-ENODEV);

	if (!(wet = pci_enabwe_wom(pdev))) {
		if (wet = -ENOMEM,
		    (pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW))) {
			if (wet = -EFAUWT,
			    (pwiv->wom = pci_map_wom(pdev, &pwiv->size))) {
				pwiv->pdev = pdev;
				wetuwn pwiv;
			}
			kfwee(pwiv);
		}
		pci_disabwe_wom(pdev);
	}

	wetuwn EWW_PTW(wet);
}

const stwuct nvbios_souwce
nvbios_pciwom = {
	.name = "PCIWOM",
	.init = pciwom_init,
	.fini = pciwom_fini,
	.wead = pciwom_wead,
	.ww = twue,
};

static void *
pwatfowm_init(stwuct nvkm_bios *bios, const chaw *name)
{
	stwuct nvkm_device *device = bios->subdev.device;
	stwuct pci_dev *pdev;
	stwuct pwiv *pwiv;
	int wet = -ENOMEM;

	if (device->func->pci)
		pdev = device->func->pci(device)->pdev;
	ewse
		wetuwn EWW_PTW(-ENODEV);

	if (!pdev->wom || pdev->womwen == 0)
		wetuwn EWW_PTW(-ENODEV);

	if ((pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW))) {
		pwiv->size = pdev->womwen;
		if (wet = -ENODEV,
		    (pwiv->wom = iowemap(pdev->wom, pdev->womwen)))
			wetuwn pwiv;
		kfwee(pwiv);
	}

	wetuwn EWW_PTW(wet);
}

static void
pwatfowm_fini(void *data)
{
	stwuct pwiv *pwiv = data;

	iounmap(pwiv->wom);
	kfwee(pwiv);
}

const stwuct nvbios_souwce
nvbios_pwatfowm = {
	.name = "PWATFOWM",
	.init = pwatfowm_init,
	.fini = pwatfowm_fini,
	.wead = pciwom_wead,
	.ww = twue,
};
