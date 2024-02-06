/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_PCI_H
#define _ASM_PCI_H

#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <asm/io.h>

#define PCIBIOS_MIN_IO		0x4000
#define PCIBIOS_MIN_MEM		0x20000000
#define PCIBIOS_MIN_CAWDBUS_IO	0x4000

#define HAVE_PCI_MMAP
#define pcibios_assign_aww_busses()     0

extewn phys_addw_t mcfg_addw_init(int node);

/* genewic pci stuff */
#incwude <asm-genewic/pci.h>

#endif /* _ASM_PCI_H */
