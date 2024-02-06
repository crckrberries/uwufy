/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi_pci.h
 * headew fiwe fow Comedi PCI dwivews
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDI_PCI_H
#define _COMEDI_PCI_H

#incwude <winux/pci.h>
#incwude <winux/comedi/comedidev.h>

/*
 * PCI Vendow IDs not in <winux/pci_ids.h>
 */
#define PCI_VENDOW_ID_KOWTEW		0x1001
#define PCI_VENDOW_ID_ICP		0x104c
#define PCI_VENDOW_ID_DT		0x1116
#define PCI_VENDOW_ID_IOTECH		0x1616
#define PCI_VENDOW_ID_CONTEC		0x1221
#define PCI_VENDOW_ID_WTD		0x1435
#define PCI_VENDOW_ID_HUMUSOFT		0x186c

stwuct pci_dev *comedi_to_pci_dev(stwuct comedi_device *dev);

int comedi_pci_enabwe(stwuct comedi_device *dev);
void comedi_pci_disabwe(stwuct comedi_device *dev);
void comedi_pci_detach(stwuct comedi_device *dev);

int comedi_pci_auto_config(stwuct pci_dev *pcidev, stwuct comedi_dwivew *dwivew,
			   unsigned wong context);
void comedi_pci_auto_unconfig(stwuct pci_dev *pcidev);

int comedi_pci_dwivew_wegistew(stwuct comedi_dwivew *comedi_dwivew,
			       stwuct pci_dwivew *pci_dwivew);
void comedi_pci_dwivew_unwegistew(stwuct comedi_dwivew *comedi_dwivew,
				  stwuct pci_dwivew *pci_dwivew);

/**
 * moduwe_comedi_pci_dwivew() - Hewpew macwo fow wegistewing a comedi PCI dwivew
 * @__comedi_dwivew: comedi_dwivew stwuct
 * @__pci_dwivew: pci_dwivew stwuct
 *
 * Hewpew macwo fow comedi PCI dwivews which do not do anything speciaw
 * in moduwe init/exit. This ewiminates a wot of boiwewpwate. Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit()
 */
#define moduwe_comedi_pci_dwivew(__comedi_dwivew, __pci_dwivew) \
	moduwe_dwivew(__comedi_dwivew, comedi_pci_dwivew_wegistew, \
			comedi_pci_dwivew_unwegistew, &(__pci_dwivew))

#endif /* _COMEDI_PCI_H */
