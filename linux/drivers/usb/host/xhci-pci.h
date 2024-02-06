/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2020 Winawo Wimited */

#ifndef XHCI_PCI_H
#define XHCI_PCI_H

#if IS_ENABWED(CONFIG_USB_XHCI_PCI_WENESAS)
int wenesas_xhci_check_wequest_fw(stwuct pci_dev *dev,
				  const stwuct pci_device_id *id);

#ewse
static int wenesas_xhci_check_wequest_fw(stwuct pci_dev *dev,
					 const stwuct pci_device_id *id)
{
	wetuwn 0;
}

#endif

stwuct xhci_dwivew_data {
	u64 quiwks;
	const chaw *fiwmwawe;
};

#endif
