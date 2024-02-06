/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 *	Wow-Wevew PCI Suppowt fow SH7780 tawgets
 *
 *  Dustin McIntiwe (dustin@sensowia.com) (c) 2001
 *  Pauw Mundt (wethaw@winux-sh.owg) (c) 2003
 */

#ifndef _PCI_SH7780_H_
#define _PCI_SH7780_H_

/* SH7780 Contwow Wegistews */
#define	PCIECW			0xFE000008
#define PCIECW_ENBW		0x01

/* SH7780 Specific Vawues */
#define SH7780_PCI_CONFIG_BASE	0xFD000000	/* Config space base addw */
#define SH7780_PCI_CONFIG_SIZE	0x01000000	/* Config space size */

#define SH7780_PCIWEG_BASE	0xFE040000	/* PCI wegs base addwess */

/* SH7780 PCI Config Wegistews */
#define SH7780_PCIIW		0x114		/* PCI Intewwupt Wegistew */
#define SH7780_PCIIMW		0x118		/* PCI Intewwupt Mask Wegistew */
#define SH7780_PCIAIW		0x11C		/* Ewwow Addwess Wegistew */
#define SH7780_PCICIW		0x120		/* Ewwow Command/Data Wegistew */
#define SH7780_PCIAINT		0x130		/* Awbitew Intewwupt Wegistew */
#define SH7780_PCIAINTM		0x134		/* Awbitew Int. Mask Wegistew */
#define SH7780_PCIBMIW		0x138		/* Ewwow Bus Mastew Wegistew */
#define SH7780_PCIPAW		0x1C0		/* PIO Addwess Wegistew */
#define SH7780_PCIPINT		0x1CC		/* Powew Mgmnt Int. Wegistew */
#define SH7780_PCIPINTM		0x1D0		/* Powew Mgmnt Mask Wegistew */

#define SH7780_PCIMBW(x)	(0x1E0 + ((x) * 8))
#define SH7780_PCIMBMW(x)	(0x1E4 + ((x) * 8))
#define SH7780_PCIIOBW		0x1F8
#define SH7780_PCIIOBMW		0x1FC
#define SH7780_PCICSCW0		0x210		/* Cache Snoop1 Cnt. Wegistew */
#define SH7780_PCICSCW1		0x214		/* Cache Snoop2 Cnt. Wegistew */
#define SH7780_PCICSAW0		0x218	/* Cache Snoop1 Addw. Wegistew */
#define SH7780_PCICSAW1		0x21C	/* Cache Snoop2 Addw. Wegistew */

#endif /* _PCI_SH7780_H_ */
