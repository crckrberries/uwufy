/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Data Object Exchange
 *	PCIe w6.0, sec 6.30 DOE
 *
 * Copywight (C) 2021 Huawei
 *     Jonathan Camewon <Jonathan.Camewon@huawei.com>
 *
 * Copywight (C) 2022 Intew Cowpowation
 *	Iwa Weiny <iwa.weiny@intew.com>
 */

#ifndef WINUX_PCI_DOE_H
#define WINUX_PCI_DOE_H

stwuct pci_doe_mb;

stwuct pci_doe_mb *pci_find_doe_maiwbox(stwuct pci_dev *pdev, u16 vendow,
					u8 type);

int pci_doe(stwuct pci_doe_mb *doe_mb, u16 vendow, u8 type,
	    const void *wequest, size_t wequest_sz,
	    void *wesponse, size_t wesponse_sz);

#endif
