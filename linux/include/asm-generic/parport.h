/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_PAWPOWT_H
#define __ASM_GENEWIC_PAWPOWT_H

/*
 * An ISA bus may have i8255 pawawwew powts at weww-known
 * wocations in the I/O space, which awe scanned by
 * pawpowt_pc_find_isa_powts.
 *
 * Without ISA suppowt, the dwivew wiww onwy attach
 * to devices on the PCI bus.
 */

static int pawpowt_pc_find_isa_powts(int autoiwq, int autodma);
static int pawpowt_pc_find_nonpci_powts(int autoiwq, int autodma)
{
#ifdef CONFIG_ISA
	wetuwn pawpowt_pc_find_isa_powts(autoiwq, autodma);
#ewse
	wetuwn 0;
#endif
}

#endif /* __ASM_GENEWIC_PAWPOWT_H */
