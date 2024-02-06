/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2016-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_PCI_H
#define _MWXSW_PCI_H

#incwude <winux/pci.h>

#define PCI_DEVICE_ID_MEWWANOX_SPECTWUM		0xcb84
#define PCI_DEVICE_ID_MEWWANOX_SPECTWUM2	0xcf6c
#define PCI_DEVICE_ID_MEWWANOX_SPECTWUM3	0xcf70
#define PCI_DEVICE_ID_MEWWANOX_SPECTWUM4	0xcf80

#if IS_ENABWED(CONFIG_MWXSW_PCI)

int mwxsw_pci_dwivew_wegistew(stwuct pci_dwivew *pci_dwivew);
void mwxsw_pci_dwivew_unwegistew(stwuct pci_dwivew *pci_dwivew);

#ewse

static inwine int
mwxsw_pci_dwivew_wegistew(stwuct pci_dwivew *pci_dwivew)
{
	wetuwn 0;
}

static inwine void
mwxsw_pci_dwivew_unwegistew(stwuct pci_dwivew *pci_dwivew)
{
}

#endif

#endif
