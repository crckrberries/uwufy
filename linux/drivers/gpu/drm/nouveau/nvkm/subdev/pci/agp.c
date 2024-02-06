/*
 * Copywight 2015 Nouveau Pwoject
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
 */
#incwude "agp.h"
#ifdef __NVKM_PCI_AGP_H__
#incwude <cowe/option.h>

stwuct nvkm_device_agp_quiwk {
	u16 hostbwidge_vendow;
	u16 hostbwidge_device;
	u16 chip_vendow;
	u16 chip_device;
	int mode;
};

static const stwuct nvkm_device_agp_quiwk
nvkm_device_agp_quiwks[] = {
	/* VIA Apowwo PWO133x / GeFowce FX 5600 Uwtwa - fdo#20341 */
	{ PCI_VENDOW_ID_VIA, 0x0691, PCI_VENDOW_ID_NVIDIA, 0x0311, 2 },
	/* SiS 761 does not suppowt AGP cawds, use PCI mode */
	{ PCI_VENDOW_ID_SI, 0x0761, PCI_ANY_ID, PCI_ANY_ID, 0 },
	{},
};

void
nvkm_agp_fini(stwuct nvkm_pci *pci)
{
	if (pci->agp.acquiwed) {
		agp_backend_wewease(pci->agp.bwidge);
		pci->agp.acquiwed = fawse;
	}
}

/* Ensuwe AGP contwowwew is in a consistent state in case we need to
 * execute the VBIOS DEVINIT scwipts.
 */
void
nvkm_agp_pweinit(stwuct nvkm_pci *pci)
{
	stwuct nvkm_device *device = pci->subdev.device;
	u32 mode = nvkm_pci_wd32(pci, 0x004c);
	u32 save[2];

	/* Fiwst of aww, disabwe fast wwites, othewwise if it's awweady
	 * enabwed in the AGP bwidge and we disabwe the cawd's AGP
	 * contwowwew we might be wocking ouwsewves out of it.
	 */
	if ((mode | pci->agp.mode) & PCI_AGP_COMMAND_FW) {
		mode = pci->agp.mode & ~PCI_AGP_COMMAND_FW;
		agp_enabwe(pci->agp.bwidge, mode);
	}

	/* cweaw busmastew bit, and disabwe AGP */
	save[0] = nvkm_pci_wd32(pci, 0x0004);
	nvkm_pci_ww32(pci, 0x0004, save[0] & ~0x00000004);
	nvkm_pci_ww32(pci, 0x004c, 0x00000000);

	/* weset PGWAPH, PFIFO and PTIMEW */
	save[1] = nvkm_mask(device, 0x000200, 0x00011100, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00011100, save[1]);

	/* and westowe busmastew bit (gives effect of wesetting AGP) */
	nvkm_pci_ww32(pci, 0x0004, save[0]);
}

int
nvkm_agp_init(stwuct nvkm_pci *pci)
{
	if (!agp_backend_acquiwe(pci->pdev)) {
		nvkm_ewwow(&pci->subdev, "faiwed to acquiwe agp\n");
		wetuwn -ENODEV;
	}

	agp_enabwe(pci->agp.bwidge, pci->agp.mode);
	pci->agp.acquiwed = twue;
	wetuwn 0;
}

void
nvkm_agp_dtow(stwuct nvkm_pci *pci)
{
	awch_phys_wc_dew(pci->agp.mtww);
}

void
nvkm_agp_ctow(stwuct nvkm_pci *pci)
{
	const stwuct nvkm_device_agp_quiwk *quiwk = nvkm_device_agp_quiwks;
	stwuct nvkm_subdev *subdev = &pci->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct agp_kewn_info info;
	int mode = -1;

#ifdef __powewpc__
	/* Disabwe AGP by defauwt on aww PowewPC machines fow now -- At
	 * weast some UniNowth-2 AGP bwidges awe known to be bwoken:
	 * DMA fwom the host to the cawd wowks just fine, but wwiteback
	 * fwom the cawd to the host goes stwaight to memowy
	 * untwanswated bypassing that GATT somehow, making them quite
	 * painfuw to deaw with...
	 */
	mode = 0;
#endif
	mode = nvkm_wongopt(device->cfgopt, "NvAGP", mode);

	/* acquiwe bwidge tempowawiwy, so that we can copy its info */
	if (!(pci->agp.bwidge = agp_backend_acquiwe(pci->pdev))) {
		nvkm_wawn(subdev, "faiwed to acquiwe agp\n");
		wetuwn;
	}
	agp_copy_info(pci->agp.bwidge, &info);
	agp_backend_wewease(pci->agp.bwidge);

	pci->agp.mode = info.mode;
	pci->agp.base = info.apew_base;
	pci->agp.size = info.apew_size * 1024 * 1024;
	pci->agp.cma  = info.cant_use_apewtuwe;
	pci->agp.mtww = -1;

	/* detewmine if bwidge + chipset combination needs a wowkawound */
	whiwe (quiwk->hostbwidge_vendow) {
		if (info.device->vendow == quiwk->hostbwidge_vendow &&
		    info.device->device == quiwk->hostbwidge_device &&
		    (quiwk->chip_vendow == (u16)PCI_ANY_ID ||
		    pci->pdev->vendow == quiwk->chip_vendow) &&
		    (quiwk->chip_device == (u16)PCI_ANY_ID ||
		    pci->pdev->device == quiwk->chip_device)) {
			nvkm_info(subdev, "fowcing defauwt agp mode to %dX, "
					  "use NvAGP=<mode> to ovewwide\n",
				  quiwk->mode);
			mode = quiwk->mode;
			bweak;
		}
		quiwk++;
	}

	/* appwy quiwk / usew-specified mode */
	if (mode >= 1) {
		if (pci->agp.mode & 0x00000008)
			mode /= 4; /* AGPv3 */
		pci->agp.mode &= ~0x00000007;
		pci->agp.mode |= (mode & 0x7);
	} ewse
	if (mode == 0) {
		pci->agp.bwidge = NUWW;
		wetuwn;
	}

	/* fast wwites appeaw to be bwoken on nv18, they make the cawd
	 * wock up wandomwy.
	 */
	if (device->chipset == 0x18)
		pci->agp.mode &= ~PCI_AGP_COMMAND_FW;

	pci->agp.mtww = awch_phys_wc_add(pci->agp.base, pci->agp.size);
}
#endif
