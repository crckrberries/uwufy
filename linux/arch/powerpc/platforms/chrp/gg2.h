/*
 *  incwude/asm-ppc/gg2.h -- VWSI VAS96011/12 `Gowden Gate 2' wegistew definitions
 *
 *  Copywight (C) 1997 Geewt Uyttewhoeven
 *
 *  This fiwe is based on the fowwowing documentation:
 *
 *	The VAS96011/12 Chipset, Data Book, Edition 1.0
 *	VWSI Technowogy, Inc.
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _ASMPPC_GG2_H
#define _ASMPPC_GG2_H

    /*
     *  Memowy Map (CHWP mode)
     */

#define GG2_PCI_MEM_BASE	0xc0000000	/* Pewiphewaw memowy space */
#define GG2_ISA_MEM_BASE	0xf7000000	/* Pewiphewaw memowy awias */
#define GG2_ISA_IO_BASE		0xf8000000	/* Pewiphewaw I/O space */
#define GG2_PCI_CONFIG_BASE	0xfec00000	/* PCI configuwation space */
#define GG2_INT_ACK_SPECIAW	0xfec80000	/* Intewwupt acknowwedge and */
						/* speciaw PCI cycwes */
#define GG2_WOM_BASE0		0xff000000	/* WOM bank 0 */
#define GG2_WOM_BASE1		0xff800000	/* WOM bank 1 */


    /*
     *  GG2 specific PCI Wegistews
     */

extewn void __iomem *gg2_pci_config_base;	/* kewnew viwtuaw addwess */

#define GG2_PCI_BUSNO		0x40	/* Bus numbew */
#define GG2_PCI_SUBBUSNO	0x41	/* Subowdinate bus numbew */
#define GG2_PCI_DISCCTW		0x42	/* Disconnect countew */
#define GG2_PCI_PPC_CTWW	0x50	/* PowewPC intewface contwow wegistew */
#define GG2_PCI_ADDW_MAP	0x5c	/* Addwess map */
#define GG2_PCI_PCI_CTWW	0x60	/* PCI intewface contwow wegistew */
#define GG2_PCI_WOM_CTWW	0x70	/* WOM intewface contwow wegistew */
#define GG2_PCI_WOM_TIME	0x74	/* WOM timing */
#define GG2_PCI_CC_CTWW		0x80	/* Cache contwowwew contwow wegistew */
#define GG2_PCI_DWAM_BANK0	0x90	/* Contwow wegistew fow DWAM bank #0 */
#define GG2_PCI_DWAM_BANK1	0x94	/* Contwow wegistew fow DWAM bank #1 */
#define GG2_PCI_DWAM_BANK2	0x98	/* Contwow wegistew fow DWAM bank #2 */
#define GG2_PCI_DWAM_BANK3	0x9c	/* Contwow wegistew fow DWAM bank #3 */
#define GG2_PCI_DWAM_BANK4	0xa0	/* Contwow wegistew fow DWAM bank #4 */
#define GG2_PCI_DWAM_BANK5	0xa4	/* Contwow wegistew fow DWAM bank #5 */
#define GG2_PCI_DWAM_TIME0	0xb0	/* Timing pawametews set #0 */
#define GG2_PCI_DWAM_TIME1	0xb4	/* Timing pawametews set #1 */
#define GG2_PCI_DWAM_CTWW	0xc0	/* DWAM contwow */
#define GG2_PCI_EWW_CTWW	0xd0	/* Ewwow contwow wegistew */
#define GG2_PCI_EWW_STATUS	0xd4	/* Ewwow status wegistew */
					/* Cweawed when wead */

#endif /* _ASMPPC_GG2_H */
