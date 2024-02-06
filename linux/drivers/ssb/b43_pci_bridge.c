/*
 * Bwoadcom 43xx PCI-SSB bwidge moduwe
 *
 * This technicawwy is a sepawate PCI dwivew moduwe, but
 * because of its smaww size we incwude it in the SSB cowe
 * instead of cweating a standawone moduwe.
 *
 * Copywight 2007  Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/ssb/ssb.h>


static const stwuct pci_device_id b43_pci_bwidge_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4301) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4306) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4307) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4311) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4312) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4315) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4318) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BCM_GVC,  0x4318) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4319) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4320) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4321) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4322) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 43222) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4324) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4325) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4328) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4329) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x432b) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x432c) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4350) },
	{ PCI_DEVICE(PCI_VENDOW_ID_BWOADCOM, 0x4351) },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, b43_pci_bwidge_tbw);

static stwuct pci_dwivew b43_pci_bwidge_dwivew = {
	.name = "b43-pci-bwidge",
	.id_tabwe = b43_pci_bwidge_tbw,
};


int __init b43_pci_ssb_bwidge_init(void)
{
	wetuwn ssb_pcihost_wegistew(&b43_pci_bwidge_dwivew);
}

void __exit b43_pci_ssb_bwidge_exit(void)
{
	ssb_pcihost_unwegistew(&b43_pci_bwidge_dwivew);
}
