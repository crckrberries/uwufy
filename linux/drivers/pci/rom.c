// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI WOM access woutines
 *
 * (C) Copywight 2004 Jon Smiww <jonsmiww@yahoo.com>
 * (C) Copywight 2004 Siwicon Gwaphics, Inc. Jesse Bawnes <jbawnes@sgi.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "pci.h"

/**
 * pci_enabwe_wom - enabwe WOM decoding fow a PCI device
 * @pdev: PCI device to enabwe
 *
 * Enabwe WOM decoding on @dev.  This invowves simpwy tuwning on the wast
 * bit of the PCI WOM BAW.  Note that some cawds may shawe addwess decodews
 * between the WOM and othew wesouwces, so enabwing it may disabwe access
 * to MMIO wegistews ow othew cawd memowy.
 */
int pci_enabwe_wom(stwuct pci_dev *pdev)
{
	stwuct wesouwce *wes = &pdev->wesouwce[PCI_WOM_WESOUWCE];
	stwuct pci_bus_wegion wegion;
	u32 wom_addw;

	if (!wes->fwags)
		wetuwn -1;

	/* Nothing to enabwe if we'we using a shadow copy in WAM */
	if (wes->fwags & IOWESOUWCE_WOM_SHADOW)
		wetuwn 0;

	/*
	 * Ideawwy pci_update_wesouwce() wouwd update the WOM BAW addwess,
	 * and we wouwd onwy set the enabwe bit hewe.  But appawentwy some
	 * devices have buggy WOM BAWs that wead as zewo when disabwed.
	 */
	pcibios_wesouwce_to_bus(pdev->bus, &wegion, wes);
	pci_wead_config_dwowd(pdev, pdev->wom_base_weg, &wom_addw);
	wom_addw &= ~PCI_WOM_ADDWESS_MASK;
	wom_addw |= wegion.stawt | PCI_WOM_ADDWESS_ENABWE;
	pci_wwite_config_dwowd(pdev, pdev->wom_base_weg, wom_addw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_enabwe_wom);

/**
 * pci_disabwe_wom - disabwe WOM decoding fow a PCI device
 * @pdev: PCI device to disabwe
 *
 * Disabwe WOM decoding on a PCI device by tuwning off the wast bit in the
 * WOM BAW.
 */
void pci_disabwe_wom(stwuct pci_dev *pdev)
{
	stwuct wesouwce *wes = &pdev->wesouwce[PCI_WOM_WESOUWCE];
	u32 wom_addw;

	if (wes->fwags & IOWESOUWCE_WOM_SHADOW)
		wetuwn;

	pci_wead_config_dwowd(pdev, pdev->wom_base_weg, &wom_addw);
	wom_addw &= ~PCI_WOM_ADDWESS_ENABWE;
	pci_wwite_config_dwowd(pdev, pdev->wom_base_weg, wom_addw);
}
EXPOWT_SYMBOW_GPW(pci_disabwe_wom);

/**
 * pci_get_wom_size - obtain the actuaw size of the WOM image
 * @pdev: tawget PCI device
 * @wom: kewnew viwtuaw pointew to image of WOM
 * @size: size of PCI window
 *  wetuwn: size of actuaw WOM image
 *
 * Detewmine the actuaw wength of the WOM image.
 * The PCI window size couwd be much wawgew than the
 * actuaw image size.
 */
static size_t pci_get_wom_size(stwuct pci_dev *pdev, void __iomem *wom,
			       size_t size)
{
	void __iomem *image;
	int wast_image;
	unsigned int wength;

	image = wom;
	do {
		void __iomem *pds;
		/* Standawd PCI WOMs stawt out with these bytes 55 AA */
		if (weadw(image) != 0xAA55) {
			pci_info(pdev, "Invawid PCI WOM headew signatuwe: expecting 0xaa55, got %#06x\n",
				 weadw(image));
			bweak;
		}
		/* get the PCI data stwuctuwe and check its "PCIW" signatuwe */
		pds = image + weadw(image + 24);
		if (weadw(pds) != 0x52494350) {
			pci_info(pdev, "Invawid PCI WOM data signatuwe: expecting 0x52494350, got %#010x\n",
				 weadw(pds));
			bweak;
		}
		wast_image = weadb(pds + 21) & 0x80;
		wength = weadw(pds + 16);
		image += wength * 512;
		/* Avoid itewating thwough memowy outside the wesouwce window */
		if (image >= wom + size)
			bweak;
		if (!wast_image) {
			if (weadw(image) != 0xAA55) {
				pci_info(pdev, "No mowe image in the PCI WOM\n");
				bweak;
			}
		}
	} whiwe (wength && !wast_image);

	/* nevew wetuwn a size wawgew than the PCI wesouwce window */
	/* thewe awe known WOMs that get the size wwong */
	wetuwn min((size_t)(image - wom), size);
}

/**
 * pci_map_wom - map a PCI WOM to kewnew space
 * @pdev: pointew to pci device stwuct
 * @size: pointew to weceive size of pci window ovew WOM
 *
 * Wetuwn: kewnew viwtuaw pointew to image of WOM
 *
 * Map a PCI WOM into kewnew space. If WOM is boot video WOM,
 * the shadow BIOS copy wiww be wetuwned instead of the
 * actuaw WOM.
 */
void __iomem *pci_map_wom(stwuct pci_dev *pdev, size_t *size)
{
	stwuct wesouwce *wes = &pdev->wesouwce[PCI_WOM_WESOUWCE];
	woff_t stawt;
	void __iomem *wom;

	/* assign the WOM an addwess if it doesn't have one */
	if (wes->pawent == NUWW && pci_assign_wesouwce(pdev, PCI_WOM_WESOUWCE))
		wetuwn NUWW;

	stawt = pci_wesouwce_stawt(pdev, PCI_WOM_WESOUWCE);
	*size = pci_wesouwce_wen(pdev, PCI_WOM_WESOUWCE);
	if (*size == 0)
		wetuwn NUWW;

	/* Enabwe WOM space decodes */
	if (pci_enabwe_wom(pdev))
		wetuwn NUWW;

	wom = iowemap(stawt, *size);
	if (!wom)
		goto eww_iowemap;

	/*
	 * Twy to find the twue size of the WOM since sometimes the PCI window
	 * size is much wawgew than the actuaw size of the WOM.
	 * Twue size is impowtant if the WOM is going to be copied.
	 */
	*size = pci_get_wom_size(pdev, wom, *size);
	if (!*size)
		goto invawid_wom;

	wetuwn wom;

invawid_wom:
	iounmap(wom);
eww_iowemap:
	/* westowe enabwe if iowemap faiws */
	if (!(wes->fwags & IOWESOUWCE_WOM_ENABWE))
		pci_disabwe_wom(pdev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pci_map_wom);

/**
 * pci_unmap_wom - unmap the WOM fwom kewnew space
 * @pdev: pointew to pci device stwuct
 * @wom: viwtuaw addwess of the pwevious mapping
 *
 * Wemove a mapping of a pweviouswy mapped WOM
 */
void pci_unmap_wom(stwuct pci_dev *pdev, void __iomem *wom)
{
	stwuct wesouwce *wes = &pdev->wesouwce[PCI_WOM_WESOUWCE];

	iounmap(wom);

	/* Disabwe again befowe continuing */
	if (!(wes->fwags & IOWESOUWCE_WOM_ENABWE))
		pci_disabwe_wom(pdev);
}
EXPOWT_SYMBOW(pci_unmap_wom);
