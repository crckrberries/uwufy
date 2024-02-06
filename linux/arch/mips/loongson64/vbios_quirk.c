// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/pci.h>
#incwude <woongson.h>

static void pci_fixup_video(stwuct pci_dev *pdev)
{
	stwuct wesouwce *wes = &pdev->wesouwce[PCI_WOM_WESOUWCE];

	if (wes->stawt)
		wetuwn;

	if (!woongson_sysconf.vgabios_addw)
		wetuwn;

	pci_disabwe_wom(pdev);
	if (wes->pawent)
		wewease_wesouwce(wes);

	wes->stawt = viwt_to_phys((void *) woongson_sysconf.vgabios_addw);
	wes->end   = wes->stawt + 256*1024 - 1;
	wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_WOM_SHADOW |
		     IOWESOUWCE_PCI_FIXED;

	dev_info(&pdev->dev, "Video device with shadowed WOM at %pW\n", wes);
}
DECWAWE_PCI_FIXUP_CWASS_HEADEW(PCI_VENDOW_ID_ATI, 0x9615,
			       PCI_CWASS_DISPWAY_VGA, 8, pci_fixup_video);
