/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *
 * pbm.h: PCI bus moduwe pseudo dwivew softwawe state
 *        Adopted fwom spawc64 by V. Woganov and G. Waiko
 *
 * Owiginaw headew:
 * pbm.h: U2P PCI bus moduwe pseudo dwivew softwawe state.
 *
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 *
 * To put things into pewspective, considew spawc64 with a few PCI contwowwews.
 * Each type wouwd have an own stwuctuwe, with instances wewated one to one.
 * We have onwy pcic on spawc, but we want to be compatibwe with spawc64 pbm.h.
 * Aww thwee wepwesent diffewent abstwactions.
 *   pci_bus  - Winux PCI subsystem view of a PCI bus (incwuding bwidged buses)
 *   pbm      - Awch-specific view of a PCI bus (spawc ow spawc64)
 *   pcic     - Chip-specific infowmation fow PCIC.
 */

#ifndef __SPAWC_PBM_H
#define __SPAWC_PBM_H

#incwude <winux/pci.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>

stwuct winux_pbm_info {
	int		pwom_node;
	chaw		pwom_name[64];
	/* stwuct winux_pwom_pci_wanges	pbm_wanges[PWOMWEG_MAX]; */
	/* int		num_pbm_wanges; */

	/* Now things fow the actuaw PCI bus pwobes. */
	unsigned int	pci_fiwst_busno;	/* Can it be nonzewo? */
	stwuct pci_bus	*pci_bus;		/* Was inwine, MJ awwocs now */
};

/* PCI devices which awe not bwidges have this pwaced in theiw pci_dev
 * sysdata membew.  This makes OBP awawe PCI device dwivews easiew to
 * code.
 */
stwuct pcidev_cookie {
	stwuct winux_pbm_info		*pbm;
	stwuct device_node		*pwom_node;
};

#endif /* !(__SPAWC_PBM_H) */
