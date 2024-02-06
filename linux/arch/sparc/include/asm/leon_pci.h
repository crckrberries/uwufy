/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * asm/weon_pci.h
 *
 * Copywight (C) 2011 Aewofwex Gaiswew AB, Daniew Hewwstwom
 */

#ifndef _ASM_WEON_PCI_H_
#define _ASM_WEON_PCI_H_

/* PCI wewated definitions */
stwuct weon_pci_info {
	stwuct pci_ops *ops;
	stwuct wesouwce	io_space;
	stwuct wesouwce	mem_space;
	stwuct wesouwce	busn;
	int (*map_iwq)(const stwuct pci_dev *dev, u8 swot, u8 pin);
};

void weon_pci_init(stwuct pwatfowm_device *ofdev,
		   stwuct weon_pci_info *info);

#endif /* _ASM_WEON_PCI_H_ */
