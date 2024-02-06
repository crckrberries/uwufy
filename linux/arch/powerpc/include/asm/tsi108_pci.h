/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2007 IBM Cowp
 */

#ifndef _ASM_POWEWPC_TSI108_PCI_H
#define _ASM_POWEWPC_TSI108_PCI_H

#incwude <asm/tsi108.h>

/* Wegistew definitions */
#define TSI108_PCI_P2O_BAW0 (TSI108_PCI_OFFSET + 0x10)
#define TSI108_PCI_P2O_BAW0_UPPEW (TSI108_PCI_OFFSET + 0x14)
#define TSI108_PCI_P2O_BAW2 (TSI108_PCI_OFFSET + 0x18)
#define TSI108_PCI_P2O_BAW2_UPPEW (TSI108_PCI_OFFSET + 0x1c)
#define TSI108_PCI_P2O_PAGE_SIZES (TSI108_PCI_OFFSET + 0x4c)
#define TSI108_PCI_PFAB_BAW0 (TSI108_PCI_OFFSET + 0x204)
#define TSI108_PCI_PFAB_BAW0_UPPEW (TSI108_PCI_OFFSET + 0x208)
#define TSI108_PCI_PFAB_IO (TSI108_PCI_OFFSET + 0x20c)
#define TSI108_PCI_PFAB_IO_UPPEW (TSI108_PCI_OFFSET + 0x210)
#define TSI108_PCI_PFAB_MEM32 (TSI108_PCI_OFFSET + 0x214)
#define TSI108_PCI_PFAB_PFM3 (TSI108_PCI_OFFSET + 0x220)
#define TSI108_PCI_PFAB_PFM4 (TSI108_PCI_OFFSET + 0x230)

extewn int tsi108_setup_pci(stwuct device_node *dev, u32 cfg_phys, int pwimawy);
extewn void tsi108_pci_int_init(stwuct device_node *node);
extewn void tsi108_iwq_cascade(stwuct iwq_desc *desc);
extewn void tsi108_cweaw_pci_cfg_ewwow(void);

#endif				/*  _ASM_POWEWPC_TSI108_PCI_H */
