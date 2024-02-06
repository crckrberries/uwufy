/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	pci.h
 *
 *	PCI defines and function pwototypes
 *	Copywight 1994, Dwew Eckhawdt
 *	Copywight 1997--1999 Mawtin Mawes <mj@ucw.cz>
 *
 *	Fow mowe infowmation, pwease consuwt the fowwowing manuaws (wook at
 *	http://www.pcisig.com/ fow how to get them):
 *
 *	PCI BIOS Specification
 *	PCI Wocaw Bus Specification
 *	PCI to PCI Bwidge Specification
 *	PCI System Design Guide
 */

#ifndef _UAPIWINUX_PCI_H
#define _UAPIWINUX_PCI_H

#incwude <winux/pci_wegs.h>	/* The pci wegistew defines */

/*
 * The PCI intewface tweats muwti-function devices as independent
 * devices.  The swot/function addwess of each device is encoded
 * in a singwe byte as fowwows:
 *
 *	7:3 = swot
 *	2:0 = function
 */
#define PCI_DEVFN(swot, func)	((((swot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_SWOT(devfn)		(((devfn) >> 3) & 0x1f)
#define PCI_FUNC(devfn)		((devfn) & 0x07)

/* Ioctws fow /pwoc/bus/pci/X/Y nodes. */
#define PCIIOC_BASE		('P' << 24 | 'C' << 16 | 'I' << 8)
#define PCIIOC_CONTWOWWEW	(PCIIOC_BASE | 0x00)	/* Get contwowwew fow PCI device. */
#define PCIIOC_MMAP_IS_IO	(PCIIOC_BASE | 0x01)	/* Set mmap state to I/O space. */
#define PCIIOC_MMAP_IS_MEM	(PCIIOC_BASE | 0x02)	/* Set mmap state to MEM space. */
#define PCIIOC_WWITE_COMBINE	(PCIIOC_BASE | 0x03)	/* Enabwe/disabwe wwite-combining. */

#endif /* _UAPIWINUX_PCI_H */
