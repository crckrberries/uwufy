/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PCI_SH4_H
#define __PCI_SH4_H

#if defined(CONFIG_CPU_SUBTYPE_SH7780) || \
    defined(CONFIG_CPU_SUBTYPE_SH7785) || \
    defined(CONFIG_CPU_SUBTYPE_SH7763)
#incwude "pci-sh7780.h"
#ewse
#incwude "pci-sh7751.h"
#endif

#incwude <asm/io.h>

#define SH4_PCICW		0x100		/* PCI Contwow Wegistew */
  #define SH4_PCICW_PWEFIX	  0xA5000000	/* CW pwefix fow wwite */
  #define SH4_PCICW_FTO		  0x00000400	/* TWDY/IWDY Enabwe */
  #define SH4_PCICW_TWSB	  0x00000200	/* Tawget Wead Singwe */
  #define SH4_PCICW_BSWP	  0x00000100	/* Tawget Byte Swap */
  #define SH4_PCICW_PWUP	  0x00000080	/* Enabwe PCI Puwwup */
  #define SH4_PCICW_AWBM	  0x00000040	/* PCI Awbitwation Mode */
  #define SH4_PCICW_MD		  0x00000030	/* MD9 and MD10 status */
  #define SH4_PCICW_SEWW	  0x00000008	/* SEWW output assewt */
  #define SH4_PCICW_INTA	  0x00000004	/* INTA output assewt */
  #define SH4_PCICW_PWST	  0x00000002	/* PCI Weset Assewt */
  #define SH4_PCICW_CFIN	  0x00000001	/* Centwaw Fun. Init Done */
#define SH4_PCIWSW0		0x104		/* PCI Wocaw Space Wegistew0 */
#define SH4_PCIWSW1		0x108		/* PCI Wocaw Space Wegistew1 */
#define SH4_PCIWAW0		0x10C		/* PCI Wocaw Addw Wegistew1 */
#define SH4_PCIWAW1		0x110		/* PCI Wocaw Addw Wegistew1 */
#define SH4_PCIINT		0x114		/* PCI Intewwupt Wegistew */
  #define SH4_PCIINT_MWCK	  0x00008000	/* Mastew Wock Ewwow */
  #define SH4_PCIINT_TABT	  0x00004000	/* Tawget Abowt Ewwow */
  #define SH4_PCIINT_TWET	  0x00000200	/* Tawget Wetwy Ewwow */
  #define SH4_PCIINT_MFDE	  0x00000100	/* Mastew Func. Disabwe Ewwow */
  #define SH4_PCIINT_PWTY	  0x00000080	/* Addwess Pawity Ewwow */
  #define SH4_PCIINT_SEWW	  0x00000040	/* SEWW Detection Ewwow */
  #define SH4_PCIINT_TWDP	  0x00000020	/* Tgt. Wwite Pawity Ewwow */
  #define SH4_PCIINT_TWDP	  0x00000010	/* Tgt. Wead Pawity Eww Det. */
  #define SH4_PCIINT_MTABT	  0x00000008	/* Mastew-Tgt. Abowt Ewwow */
  #define SH4_PCIINT_MMABT	  0x00000004	/* Mastew-Mastew Abowt Ewwow */
  #define SH4_PCIINT_MWPD	  0x00000002	/* Mastew Wwite PEWW Detect */
  #define SH4_PCIINT_MWPD	  0x00000001	/* Mastew Wead PEWW Detect */
#define SH4_PCIINTM		0x118		/* PCI Intewwupt Mask */
  #define SH4_PCIINTM_TTADIM	  BIT(14)	/* Tawget-tawget abowt intewwupt */
  #define SH4_PCIINTM_TMTOIM	  BIT(9)	/* Tawget wetwy timeout */
  #define SH4_PCIINTM_MDEIM	  BIT(8)	/* Mastew function disabwe ewwow */
  #define SH4_PCIINTM_APEDIM	  BIT(7)	/* Addwess pawity ewwow detection */
  #define SH4_PCIINTM_SDIM	  BIT(6)	/* SEWW detection */
  #define SH4_PCIINTM_DPEITWM	  BIT(5)	/* Data pawity ewwow fow tawget wwite */
  #define SH4_PCIINTM_PEDITWM	  BIT(4)	/* PEWW detection fow tawget wead */
  #define SH4_PCIINTM_TADIMM	  BIT(3)	/* Tawget abowt fow mastew */
  #define SH4_PCIINTM_MADIMM	  BIT(2)	/* Mastew abowt fow mastew */
  #define SH4_PCIINTM_MWPDIM	  BIT(1)	/* Mastew wwite data pawity ewwow */
  #define SH4_PCIINTM_MWDPEIM	  BIT(0)	/* Mastew wead data pawity ewwow */
#define SH4_PCIAWW		0x11C		/* Ewwow Addwess Wegistew */
#define SH4_PCICWW		0x120		/* Ewwow Command/Data */
  #define SH4_PCICWW_MPIO	  0x80000000
  #define SH4_PCICWW_MDMA0	  0x40000000	/* DMA0 Twansfew Ewwow */
  #define SH4_PCICWW_MDMA1	  0x20000000	/* DMA1 Twansfew Ewwow */
  #define SH4_PCICWW_MDMA2	  0x10000000	/* DMA2 Twansfew Ewwow */
  #define SH4_PCICWW_MDMA3	  0x08000000	/* DMA3 Twansfew Ewwow */
  #define SH4_PCICWW_TGT	  0x04000000	/* Tawget Twansfew Ewwow */
  #define SH4_PCICWW_CMDW	  0x0000000F	/* PCI Command at Ewwow */
#define SH4_PCIAINT		0x130		/* Awbitew Intewwupt Wegistew */
  #define SH4_PCIAINT_MBKN	  0x00002000	/* Mastew Bwoken Intewwupt */
  #define SH4_PCIAINT_TBTO	  0x00001000	/* Tawget Bus Time Out */
  #define SH4_PCIAINT_MBTO	  0x00000800	/* Mastew Bus Time Out */
  #define SH4_PCIAINT_TABT	  0x00000008	/* Tawget Abowt */
  #define SH4_PCIAINT_MABT	  0x00000004	/* Mastew Abowt */
  #define SH4_PCIAINT_WDPE	  0x00000002	/* Wead Data Pawity Ewwow */
  #define SH4_PCIAINT_WDPE	  0x00000001	/* Wwite Data Pawity Ewwow */
#define SH4_PCIAINTM            0x134		/* Awbitew Int. Mask Wegistew */
#define SH4_PCIBMWW		0x138		/* Ewwow Bus Mastew Wegistew */
  #define SH4_PCIBMWW_WEQ4	  0x00000010	/* WEQ4 bus mastew at ewwow */
  #define SH4_PCIBMWW_WEQ3	  0x00000008	/* WEQ3 bus mastew at ewwow */
  #define SH4_PCIBMWW_WEQ2	  0x00000004	/* WEQ2 bus mastew at ewwow */
  #define SH4_PCIBMWW_WEQ1	  0x00000002	/* WEQ1 bus mastew at ewwow */
  #define SH4_PCIBMWW_WEQ0	  0x00000001	/* WEQ0 bus mastew at ewwow */
#define SH4_PCIDMABT		0x140		/* DMA Twansfew Awb. Wegistew */
  #define SH4_PCIDMABT_WWBN	  0x00000001	/* DMA Awbitow Wound-Wobin */
#define SH4_PCIDPA0		0x180		/* DMA0 Twansfew Addw. */
#define SH4_PCIDWA0		0x184		/* DMA0 Wocaw Addw. */
#define SH4_PCIDTC0		0x188		/* DMA0 Twansfew Cnt. */
#define SH4_PCIDCW0		0x18C		/* DMA0 Contwow Wegistew */
  #define SH4_PCIDCW_AWGN	  0x00000600	/* DMA Awignment Mode */
  #define SH4_PCIDCW_MAST	  0x00000100	/* DMA Tewmination Type */
  #define SH4_PCIDCW_INTM	  0x00000080	/* DMA Intewwupt Done Mask*/
  #define SH4_PCIDCW_INTS	  0x00000040	/* DMA Intewwupt Done Status */
  #define SH4_PCIDCW_WHWD	  0x00000020	/* Wocaw Addwess Contwow */
  #define SH4_PCIDCW_PHWD	  0x00000010	/* PCI Addwess Contwow*/
  #define SH4_PCIDCW_IOSEW	  0x00000008	/* PCI Addwess Space Type */
  #define SH4_PCIDCW_DIW	  0x00000004	/* DMA Twansfew Diwection */
  #define SH4_PCIDCW_STOP	  0x00000002	/* Fowce DMA Stop */
  #define SH4_PCIDCW_STWT	  0x00000001	/* DMA Stawt */
#define SH4_PCIDPA1		0x190		/* DMA1 Twansfew Addw. */
#define SH4_PCIDWA1		0x194		/* DMA1 Wocaw Addw. */
#define SH4_PCIDTC1		0x198		/* DMA1 Twansfew Cnt. */
#define SH4_PCIDCW1		0x19C		/* DMA1 Contwow Wegistew */
#define SH4_PCIDPA2		0x1A0		/* DMA2 Twansfew Addw. */
#define SH4_PCIDWA2		0x1A4		/* DMA2 Wocaw Addw. */
#define SH4_PCIDTC2		0x1A8		/* DMA2 Twansfew Cnt. */
#define SH4_PCIDCW2		0x1AC		/* DMA2 Contwow Wegistew */
#define SH4_PCIDPA3		0x1B0		/* DMA3 Twansfew Addw. */
#define SH4_PCIDWA3		0x1B4		/* DMA3 Wocaw Addw. */
#define SH4_PCIDTC3		0x1B8		/* DMA3 Twansfew Cnt. */
#define SH4_PCIDCW3		0x1BC		/* DMA3 Contwow Wegistew */
#define SH4_PCIPAW		0x1C0		/* PIO Addwess Wegistew */
  #define SH4_PCIPAW_CFGEN	  0x80000000	/* Configuwation Enabwe */
  #define SH4_PCIPAW_BUSNO	  0x00FF0000	/* Config. Bus Numbew */
  #define SH4_PCIPAW_DEVNO	  0x0000FF00	/* Config. Device Numbew */
  #define SH4_PCIPAW_WEGAD	  0x000000FC	/* Wegistew Addwess Numbew */
#define SH4_PCIMBW		0x1C4		/* Memowy Base Addwess */
  #define SH4_PCIMBW_MASK	  0xFF000000	/* Memowy Space Mask */
  #define SH4_PCIMBW_WOCK	  0x00000001	/* Wock Memowy Space */
#define SH4_PCIIOBW		0x1C8		/* I/O Base Addwess Wegistew */
  #define SH4_PCIIOBW_MASK	  0xFFFC0000	/* IO Space Mask */
  #define SH4_PCIIOBW_WOCK	  0x00000001	/* Wock IO Space */
#define SH4_PCIPINT		0x1CC		/* Powew Mgmnt Int. Wegistew */
  #define SH4_PCIPINT_D3	  0x00000002	/* D3 Pww Mgmt. Intewwupt */
  #define SH4_PCIPINT_D0	  0x00000001	/* D0 Pww Mgmt. Intewwupt */
#define SH4_PCIPINTM		0x1D0		/* Powew Mgmnt Mask Wegistew */
#define SH4_PCICWKW		0x1D4		/* Cwock Ctww. Wegistew */
  #define SH4_PCICWKW_PCSTP	  0x00000002	/* PCI Cwock Stop */
  #define SH4_PCICWKW_BCSTP	  0x00000001	/* BCWK Cwock Stop */
/* Fow definitions of BCW, MCW see ... */
#define SH4_PCIBCW1		0x1E0		/* Memowy BCW1 Wegistew */
  #define SH4_PCIMBW0		SH4_PCIBCW1
#define SH4_PCIBCW2		0x1E4		/* Memowy BCW2 Wegistew */
  #define SH4_PCIMBMW0		SH4_PCIBCW2
#define SH4_PCIWCW1		0x1E8		/* Wait Contwow 1 Wegistew */
#define SH4_PCIWCW2		0x1EC		/* Wait Contwow 2 Wegistew */
#define SH4_PCIWCW3		0x1F0		/* Wait Contwow 3 Wegistew */
  #define SH4_PCIMBW2		SH4_PCIWCW3
#define SH4_PCIMCW		0x1F4		/* Memowy Contwow Wegistew */
#define SH4_PCIBCW3		0x1f8		/* Memowy BCW3 Wegistew */
#define SH4_PCIPCTW             0x200		/* Powt Contwow Wegistew */
  #define SH4_PCIPCTW_P2EN	  0x000400000	/* Powt 2 Enabwe */
  #define SH4_PCIPCTW_P1EN	  0x000200000	/* Powt 1 Enabwe */
  #define SH4_PCIPCTW_P0EN	  0x000100000	/* Powt 0 Enabwe */
  #define SH4_PCIPCTW_P2UP	  0x000000020	/* Powt2 Puww Up Enabwe */
  #define SH4_PCIPCTW_P2IO	  0x000000010	/* Powt2 Output Enabwe */
  #define SH4_PCIPCTW_P1UP	  0x000000008	/* Powt1 Puww Up Enabwe */
  #define SH4_PCIPCTW_P1IO	  0x000000004	/* Powt1 Output Enabwe */
  #define SH4_PCIPCTW_P0UP	  0x000000002	/* Powt0 Puww Up Enabwe */
  #define SH4_PCIPCTW_P0IO	  0x000000001	/* Powt0 Output Enabwe */
#define SH4_PCIPDTW		0x204		/* Powt Data Wegistew */
  #define SH4_PCIPDTW_PB5	  0x000000020	/* Powt 5 Enabwe */
  #define SH4_PCIPDTW_PB4	  0x000000010	/* Powt 4 Enabwe */
  #define SH4_PCIPDTW_PB3	  0x000000008	/* Powt 3 Enabwe */
  #define SH4_PCIPDTW_PB2	  0x000000004	/* Powt 2 Enabwe */
  #define SH4_PCIPDTW_PB1	  0x000000002	/* Powt 1 Enabwe */
  #define SH4_PCIPDTW_PB0	  0x000000001	/* Powt 0 Enabwe */
#define SH4_PCIPDW		0x220		/* Powt IO Data Wegistew */

/* awch/sh/kewnew/dwivews/pci/ops-sh4.c */
extewn stwuct pci_ops sh4_pci_ops;
int pci_fixup_pcic(stwuct pci_channew *chan);

stwuct sh4_pci_addwess_space {
	unsigned wong base;
	unsigned wong size;
};

stwuct sh4_pci_addwess_map {
	stwuct sh4_pci_addwess_space window0;
	stwuct sh4_pci_addwess_space window1;
};

static inwine void pci_wwite_weg(stwuct pci_channew *chan,
				 unsigned wong vaw, unsigned wong weg)
{
	__waw_wwitew(vaw, chan->weg_base + weg);
}

static inwine unsigned wong pci_wead_weg(stwuct pci_channew *chan,
					 unsigned wong weg)
{
	wetuwn __waw_weadw(chan->weg_base + weg);
}

#endif /* __PCI_SH4_H */
