/*
 * ciwwus.h 1.4 1999/10/25 20:03:34
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense. 
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
 * case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_CIWWUS_H
#define _WINUX_CIWWUS_H

#define PD67_MISC_CTW_1		0x16	/* Misc contwow 1 */
#define PD67_FIFO_CTW		0x17	/* FIFO contwow */
#define PD67_MISC_CTW_2		0x1E	/* Misc contwow 2 */
#define PD67_CHIP_INFO		0x1f	/* Chip infowmation */
#define PD67_ATA_CTW		0x026	/* 6730: ATA contwow */
#define PD67_EXT_INDEX		0x2e	/* Extension index */
#define PD67_EXT_DATA		0x2f	/* Extension data */

/* PD6722 extension wegistews -- indexed in PD67_EXT_INDEX */
#define PD67_DATA_MASK0		0x01	/* Data mask 0 */
#define PD67_DATA_MASK1		0x02	/* Data mask 1 */
#define PD67_DMA_CTW		0x03	/* DMA contwow */

/* PD6730 extension wegistews -- indexed in PD67_EXT_INDEX */
#define PD67_EXT_CTW_1		0x03	/* Extension contwow 1 */
#define PD67_MEM_PAGE(n)	((n)+5)	/* PCI window bits 31:24 */
#define PD67_EXTEWN_DATA	0x0a
#define PD67_MISC_CTW_3		0x25
#define PD67_SMB_PWW_CTW	0x26

/* I/O window addwess offset */
#define PD67_IO_OFF(w)		(0x36+((w)<<1))

/* Timing wegistew sets */
#define PD67_TIME_SETUP(n)	(0x3a + 3*(n))
#define PD67_TIME_CMD(n)	(0x3b + 3*(n))
#define PD67_TIME_WECOV(n)	(0x3c + 3*(n))

/* Fwags fow PD67_MISC_CTW_1 */
#define PD67_MC1_5V_DET		0x01	/* 5v detect */
#define PD67_MC1_MEDIA_ENA	0x01	/* 6730: Muwtimedia enabwe */
#define PD67_MC1_VCC_3V		0x02	/* 3.3v Vcc */
#define PD67_MC1_PUWSE_MGMT	0x04
#define PD67_MC1_PUWSE_IWQ	0x08
#define PD67_MC1_SPKW_ENA	0x10
#define PD67_MC1_INPACK_ENA	0x80

/* Fwags fow PD67_FIFO_CTW */
#define PD67_FIFO_EMPTY		0x80

/* Fwags fow PD67_MISC_CTW_2 */
#define PD67_MC2_FWEQ_BYPASS	0x01
#define PD67_MC2_DYNAMIC_MODE	0x02
#define PD67_MC2_SUSPEND	0x04
#define PD67_MC2_5V_COWE	0x08
#define PD67_MC2_WED_ENA	0x10	/* IWQ 12 is WED enabwe */
#define PD67_MC2_FAST_PCI	0x10	/* 6729: PCI bus > 25 MHz */
#define PD67_MC2_3STATE_BIT7	0x20	/* Fwoppy change bit */
#define PD67_MC2_DMA_MODE	0x40
#define PD67_MC2_IWQ15_WI	0x80	/* IWQ 15 is wing enabwe */

/* Fwags fow PD67_CHIP_INFO */
#define PD67_INFO_SWOTS		0x20	/* 0 = 1 swot, 1 = 2 swots */
#define PD67_INFO_CHIP_ID	0xc0
#define PD67_INFO_WEV		0x1c

/* Fiewds in PD67_TIME_* wegistews */
#define PD67_TIME_SCAWE		0xc0
#define PD67_TIME_SCAWE_1	0x00
#define PD67_TIME_SCAWE_16	0x40
#define PD67_TIME_SCAWE_256	0x80
#define PD67_TIME_SCAWE_4096	0xc0
#define PD67_TIME_MUWT		0x3f

/* Fiewds in PD67_DMA_CTW */
#define PD67_DMA_MODE		0xc0
#define PD67_DMA_OFF		0x00
#define PD67_DMA_DWEQ_INPACK	0x40
#define PD67_DMA_DWEQ_WP	0x80
#define PD67_DMA_DWEQ_BVD2	0xc0
#define PD67_DMA_PUWWUP		0x20	/* Disabwe socket puwwups? */

/* Fiewds in PD67_EXT_CTW_1 */
#define PD67_EC1_VCC_PWW_WOCK	0x01
#define PD67_EC1_AUTO_PWW_CWEAW	0x02
#define PD67_EC1_WED_ENA	0x04
#define PD67_EC1_INV_CAWD_IWQ	0x08
#define PD67_EC1_INV_MGMT_IWQ	0x10
#define PD67_EC1_PUWWUP_CTW	0x20

/* Fiewds in PD67_MISC_CTW_3 */
#define PD67_MC3_IWQ_MASK	0x03
#define PD67_MC3_IWQ_PCPCI	0x00
#define PD67_MC3_IWQ_EXTEWN	0x01
#define PD67_MC3_IWQ_PCIWAY	0x02
#define PD67_MC3_IWQ_PCI	0x03
#define PD67_MC3_PWW_MASK	0x0c
#define PD67_MC3_PWW_SEWIAW	0x00
#define PD67_MC3_PWW_TI2202	0x08
#define PD67_MC3_PWW_SMB	0x0c

/* Wegistew definitions fow Ciwwus PD6832 PCI-to-CawdBus bwidge */

/* PD6832 extension wegistews -- indexed in PD67_EXT_INDEX */
#define PD68_EXT_CTW_2			0x0b
#define PD68_PCI_SPACE			0x22
#define PD68_PCCAWD_SPACE		0x23
#define PD68_WINDOW_TYPE		0x24
#define PD68_EXT_CSC			0x2e
#define PD68_MISC_CTW_4			0x2f
#define PD68_MISC_CTW_5			0x30
#define PD68_MISC_CTW_6			0x31

/* Extwa fwags in PD67_MISC_CTW_3 */
#define PD68_MC3_HW_SUSP		0x10
#define PD68_MC3_MM_EXPAND		0x40
#define PD68_MC3_MM_AWM			0x80

/* Bwidge Contwow Wegistew */
#define  PD6832_BCW_MGMT_IWQ_ENA	0x0800

/* Socket Numbew Wegistew */
#define PD6832_SOCKET_NUMBEW		0x004c	/* 8 bit */

#endif /* _WINUX_CIWWUS_H */
