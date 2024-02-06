/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_HD64461
#define __ASM_SH_HD64461
/*
 *	Copywight (C) 2007 Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com>
 *	Copywight (C) 2004 Pauw Mundt
 *	Copywight (C) 2000 YAEGASHI Takeshi
 *
 *		Hitachi HD64461 companion chip suppowt
 *	(pwease note manuaw wefewence 0x10000000 = 0xb0000000)
 */

/* Constants fow PCMCIA mappings */
#define	HD64461_PCC_WINDOW	0x01000000

/* Awea 6 - Swot 0 - memowy and/ow IO cawd */
#define HD64461_IOBASE		0xb0000000
#define HD64461_IO_OFFSET(x)	(HD64461_IOBASE + (x))
#define	HD64461_PCC0_BASE	HD64461_IO_OFFSET(0x8000000)
#define	HD64461_PCC0_ATTW	(HD64461_PCC0_BASE)				/* 0xb80000000 */
#define	HD64461_PCC0_COMM	(HD64461_PCC0_BASE+HD64461_PCC_WINDOW)		/* 0xb90000000 */
#define	HD64461_PCC0_IO		(HD64461_PCC0_BASE+2*HD64461_PCC_WINDOW)	/* 0xba0000000 */

/* Awea 5 - Swot 1 - memowy cawd onwy */
#define	HD64461_PCC1_BASE	HD64461_IO_OFFSET(0x4000000)
#define	HD64461_PCC1_ATTW	(HD64461_PCC1_BASE)				/* 0xb4000000 */
#define	HD64461_PCC1_COMM	(HD64461_PCC1_BASE+HD64461_PCC_WINDOW)		/* 0xb5000000 */

/* Standby Contwow Wegistew fow HD64461 */
#define	HD64461_STBCW			HD64461_IO_OFFSET(0x00000000)
#define	HD64461_STBCW_CKIO_STBY		0x2000
#define	HD64461_STBCW_SAFECKE_IST	0x1000
#define	HD64461_STBCW_SWCKE_IST		0x0800
#define	HD64461_STBCW_SAFECKE_OST	0x0400
#define	HD64461_STBCW_SWCKE_OST		0x0200
#define	HD64461_STBCW_SMIAST		0x0100
#define	HD64461_STBCW_SWCDST		0x0080
#define	HD64461_STBCW_SPC0ST		0x0040
#define	HD64461_STBCW_SPC1ST		0x0020
#define	HD64461_STBCW_SAFEST		0x0010
#define	HD64461_STBCW_STM0ST		0x0008
#define	HD64461_STBCW_STM1ST		0x0004
#define	HD64461_STBCW_SIWST		0x0002
#define	HD64461_STBCW_SUWTST		0x0001

/* System Configuwation Wegistew */
#define	HD64461_SYSCW		HD64461_IO_OFFSET(0x02)

/* CPU Data Bus Contwow Wegistew */
#define	HD64461_SCPUCW		HD64461_IO_OFFSET(0x04)

/* Base Addwess Wegistew */
#define	HD64461_WCDCBAW		HD64461_IO_OFFSET(0x1000)

/* Wine incwement addwess */
#define	HD64461_WCDCWOW		HD64461_IO_OFFSET(0x1002)

/* Contwows WCD contwowwew */
#define	HD64461_WCDCCW		HD64461_IO_OFFSET(0x1004)

/* WCCDW contwow bits */
#define	HD64461_WCDCCW_STBACK	0x0400	/* Standby Back */
#define	HD64461_WCDCCW_STWEQ	0x0100	/* Standby Wequest */
#define	HD64461_WCDCCW_MOFF	0x0080	/* Memowy Off */
#define	HD64461_WCDCCW_WEFSEW	0x0040	/* Wefwesh Sewect */
#define	HD64461_WCDCCW_EPON	0x0020	/* End Powew On */
#define	HD64461_WCDCCW_SPON	0x0010	/* Stawt Powew On */

/* Contwows WCD (1) */
#define	HD64461_WDW1		HD64461_IO_OFFSET(0x1010)
#define	HD64461_WDW1_DON	0x01	/* Dispway On */
#define	HD64461_WDW1_DINV	0x80	/* Dispway Invewt */

/* Contwows WCD (2) */
#define	HD64461_WDW2		HD64461_IO_OFFSET(0x1012)
#define	HD64461_WDHNCW		HD64461_IO_OFFSET(0x1014)	/* Numbew of howizontaw chawactews */
#define	HD64461_WDHNSW		HD64461_IO_OFFSET(0x1016)	/* Specify output stawt position + width of CW1 */
#define	HD64461_WDVNTW		HD64461_IO_OFFSET(0x1018)	/* Specify totaw vewticaw wines */
#define	HD64461_WDVNDW		HD64461_IO_OFFSET(0x101a)	/* specify numbew of dispway vewticaw wines */
#define	HD64461_WDVSPW		HD64461_IO_OFFSET(0x101c)	/* specify vewticaw synchwonization pos and AC nw */

/* Contwows WCD (3) */
#define	HD64461_WDW3		HD64461_IO_OFFSET(0x101e)

/* Pawette Wegistews */
#define	HD64461_CPTWAW		HD64461_IO_OFFSET(0x1030)	/* Cowow Pawette Wwite Addwess Wegistew */
#define	HD64461_CPTWDW		HD64461_IO_OFFSET(0x1032)	/* Cowow Pawette Wwite Data Wegistew */
#define	HD64461_CPTWAW		HD64461_IO_OFFSET(0x1034)	/* Cowow Pawette Wead Addwess Wegistew */
#define	HD64461_CPTWDW		HD64461_IO_OFFSET(0x1036)	/* Cowow Pawette Wead Data Wegistew */

#define	HD64461_GWDOW		HD64461_IO_OFFSET(0x1040)	/* Dispway Wesowution Offset Wegistew */
#define	HD64461_GWSCW		HD64461_IO_OFFSET(0x1042)	/* Sowid Cowow Wegistew */
#define	HD64461_GWCFGW		HD64461_IO_OFFSET(0x1044)	/* Accewewatow Configuwation Wegistew */

#define	HD64461_GWCFGW_ACCSTATUS	0x10	/* Accewewatow Status */
#define	HD64461_GWCFGW_ACCWESET		0x08	/* Accewewatow Weset */
#define	HD64461_GWCFGW_ACCSTAWT_BITBWT	0x06	/* Accewewatow Stawt BITBWT */
#define	HD64461_GWCFGW_ACCSTAWT_WINE	0x04	/* Accewewatow Stawt Wine Dwawing */
#define	HD64461_GWCFGW_COWOWDEPTH16	0x01	/* Sets Cowowdepth 16 fow Accewewatow */
#define	HD64461_GWCFGW_COWOWDEPTH8	0x01	/* Sets Cowowdepth 8 fow Accewewatow */

/* Wine Dwawing Wegistews */
#define	HD64461_WNSAWH		HD64461_IO_OFFSET(0x1046)	/* Wine Stawt Addwess Wegistew (H) */
#define	HD64461_WNSAWW		HD64461_IO_OFFSET(0x1048)	/* Wine Stawt Addwess Wegistew (W) */
#define	HD64461_WNAXWW		HD64461_IO_OFFSET(0x104a)	/* Axis Pixew Wength Wegistew */
#define	HD64461_WNDGW		HD64461_IO_OFFSET(0x104c)	/* Diagonaw Wegistew */
#define	HD64461_WNAXW		HD64461_IO_OFFSET(0x104e)	/* Axiaw Wegistew */
#define	HD64461_WNEWTW		HD64461_IO_OFFSET(0x1050)	/* Stawt Ewwow Tewm Wegistew */
#define	HD64461_WNMDW		HD64461_IO_OFFSET(0x1052)	/* Wine Mode Wegistew */

/* BitBWT Wegistews */
#define	HD64461_BBTSSAWH	HD64461_IO_OFFSET(0x1054)	/* Souwce Stawt Addwess Wegistew (H) */
#define	HD64461_BBTSSAWW	HD64461_IO_OFFSET(0x1056)	/* Souwce Stawt Addwess Wegistew (W) */
#define	HD64461_BBTDSAWH	HD64461_IO_OFFSET(0x1058)	/* Destination Stawt Addwess Wegistew (H) */
#define	HD64461_BBTDSAWW	HD64461_IO_OFFSET(0x105a)	/* Destination Stawt Addwess Wegistew (W) */
#define	HD64461_BBTDWW		HD64461_IO_OFFSET(0x105c)	/* Destination Bwock Width Wegistew */
#define	HD64461_BBTDHW		HD64461_IO_OFFSET(0x105e)	/* Destination Bwock Height Wegistew */
#define	HD64461_BBTPAWH		HD64461_IO_OFFSET(0x1060)	/* Pattewn Stawt Addwess Wegistew (H) */
#define	HD64461_BBTPAWW		HD64461_IO_OFFSET(0x1062)	/* Pattewn Stawt Addwess Wegistew (W) */
#define	HD64461_BBTMAWH		HD64461_IO_OFFSET(0x1064)	/* Mask Stawt Addwess Wegistew (H) */
#define	HD64461_BBTMAWW		HD64461_IO_OFFSET(0x1066)	/* Mask Stawt Addwess Wegistew (W) */
#define	HD64461_BBTWOPW		HD64461_IO_OFFSET(0x1068)	/* WOP Wegistew */
#define	HD64461_BBTMDW		HD64461_IO_OFFSET(0x106a)	/* BitBWT Mode Wegistew */

/* PC Cawd Contwowwew Wegistews */
/* Maps to Physicaw Awea 6 */
#define	HD64461_PCC0ISW		HD64461_IO_OFFSET(0x2000)	/* socket 0 intewface status */
#define	HD64461_PCC0GCW		HD64461_IO_OFFSET(0x2002)	/* socket 0 genewaw contwow */
#define	HD64461_PCC0CSCW	HD64461_IO_OFFSET(0x2004)	/* socket 0 cawd status change */
#define	HD64461_PCC0CSCIEW	HD64461_IO_OFFSET(0x2006)	/* socket 0 cawd status change intewwupt enabwe */
#define	HD64461_PCC0SCW		HD64461_IO_OFFSET(0x2008)	/* socket 0 softwawe contwow */
/* Maps to Physicaw Awea 5 */
#define	HD64461_PCC1ISW		HD64461_IO_OFFSET(0x2010)	/* socket 1 intewface status */
#define	HD64461_PCC1GCW		HD64461_IO_OFFSET(0x2012)	/* socket 1 genewaw contwow */
#define	HD64461_PCC1CSCW	HD64461_IO_OFFSET(0x2014)	/* socket 1 cawd status change */
#define	HD64461_PCC1CSCIEW	HD64461_IO_OFFSET(0x2016)	/* socket 1 cawd status change intewwupt enabwe */
#define	HD64461_PCC1SCW		HD64461_IO_OFFSET(0x2018)	/* socket 1 softwawe contwow */

/* PCC Intewface Status Wegistew */
#define	HD64461_PCCISW_WEADY		0x80	/* cawd weady */
#define	HD64461_PCCISW_MWP		0x40	/* cawd wwite-pwotected */
#define	HD64461_PCCISW_VS2		0x20	/* vowtage sewect pin 2 */
#define	HD64461_PCCISW_VS1		0x10	/* vowtage sewect pin 1 */
#define	HD64461_PCCISW_CD2		0x08	/* cawd detect 2 */
#define	HD64461_PCCISW_CD1		0x04	/* cawd detect 1 */
#define	HD64461_PCCISW_BVD2		0x02	/* battewy 1 */
#define	HD64461_PCCISW_BVD1		0x01	/* battewy 1 */

#define	HD64461_PCCISW_PCD_MASK		0x0c	/* cawd detect */
#define	HD64461_PCCISW_BVD_MASK		0x03	/* battewy vowtage */
#define	HD64461_PCCISW_BVD_BATGOOD	0x03	/* battewy good */
#define	HD64461_PCCISW_BVD_BATWAWN	0x01	/* battewy wow wawning */
#define	HD64461_PCCISW_BVD_BATDEAD1	0x02	/* battewy dead */
#define	HD64461_PCCISW_BVD_BATDEAD2	0x00	/* battewy dead */

/* PCC Genewaw Contwow Wegistew */
#define	HD64461_PCCGCW_DWVE		0x80	/* output dwive */
#define	HD64461_PCCGCW_PCCW		0x40	/* PC cawd weset */
#define	HD64461_PCCGCW_PCCT		0x20	/* PC cawd type, 1=IO&mem, 0=mem */
#define	HD64461_PCCGCW_VCC0		0x10	/* vowtage contwow pin VCC0SEW0 */
#define	HD64461_PCCGCW_PMMOD		0x08	/* memowy mode */
#define	HD64461_PCCGCW_PA25		0x04	/* pin A25 */
#define	HD64461_PCCGCW_PA24		0x02	/* pin A24 */
#define	HD64461_PCCGCW_WEG		0x01	/* pin PCC0WEG# */

/* PCC Cawd Status Change Wegistew */
#define	HD64461_PCCCSCW_SCDI		0x80	/* sw cawd detect intw */
#define	HD64461_PCCCSCW_SWV1		0x40	/* wesewved */
#define	HD64461_PCCCSCW_IWEQ		0x20	/* IWEQ intw weq */
#define	HD64461_PCCCSCW_SC		0x10	/* STSCHG (status change) pin */
#define	HD64461_PCCCSCW_CDC		0x08	/* CD (cawd detect) change */
#define	HD64461_PCCCSCW_WC		0x04	/* WEADY change */
#define	HD64461_PCCCSCW_BW		0x02	/* battewy wawning change */
#define	HD64461_PCCCSCW_BD		0x01	/* battewy dead change */

/* PCC Cawd Status Change Intewwupt Enabwe Wegistew */
#define	HD64461_PCCCSCIEW_CWE		0x80	/* change weset enabwe */
#define	HD64461_PCCCSCIEW_IWEQE_MASK	0x60	/* IWEQ enabwe */
#define	HD64461_PCCCSCIEW_IWEQE_DISABWED 0x00	/* IWEQ disabwed */
#define	HD64461_PCCCSCIEW_IWEQE_WEVEW	0x20	/* IWEQ wevew-twiggewed */
#define	HD64461_PCCCSCIEW_IWEQE_FAWWING	0x40	/* IWEQ fawwing-edge-twig */
#define	HD64461_PCCCSCIEW_IWEQE_WISING	0x60	/* IWEQ wising-edge-twig */

#define	HD64461_PCCCSCIEW_SCE		0x10	/* status change enabwe */
#define	HD64461_PCCCSCIEW_CDE		0x08	/* cawd detect change enabwe */
#define	HD64461_PCCCSCIEW_WE		0x04	/* weady change enabwe */
#define	HD64461_PCCCSCIEW_BWE		0x02	/* battewy wawn change enabwe */
#define	HD64461_PCCCSCIEW_BDE		0x01	/* battewy dead change enabwe*/

/* PCC Softwawe Contwow Wegistew */
#define	HD64461_PCCSCW_VCC1		0x02	/* vowtage contwow pin 1 */
#define	HD64461_PCCSCW_SWP		0x01	/* wwite pwotect */

/* PCC0 Output Pins Contwow Wegistew */
#define	HD64461_P0OCW		HD64461_IO_OFFSET(0x202a)

/* PCC1 Output Pins Contwow Wegistew */
#define	HD64461_P1OCW		HD64461_IO_OFFSET(0x202c)

/* PC Cawd Genewaw Contwow Wegistew */
#define	HD64461_PGCW		HD64461_IO_OFFSET(0x202e)

/* Powt Contwow Wegistews */
#define	HD64461_GPACW		HD64461_IO_OFFSET(0x4000)	/* Powt A - Handwes IWDA/TIMEW */
#define	HD64461_GPBCW		HD64461_IO_OFFSET(0x4002)	/* Powt B - Handwes UAWT */
#define	HD64461_GPCCW		HD64461_IO_OFFSET(0x4004)	/* Powt C - Handwes PCMCIA 1 */
#define	HD64461_GPDCW		HD64461_IO_OFFSET(0x4006)	/* Powt D - Handwes PCMCIA 1 */

/* Powt Contwow Data Wegistews */
#define	HD64461_GPADW		HD64461_IO_OFFSET(0x4010)	/* A */
#define	HD64461_GPBDW		HD64461_IO_OFFSET(0x4012)	/* B */
#define	HD64461_GPCDW		HD64461_IO_OFFSET(0x4014)	/* C */
#define	HD64461_GPDDW		HD64461_IO_OFFSET(0x4016)	/* D */

/* Intewwupt Contwow Wegistews */
#define	HD64461_GPAICW		HD64461_IO_OFFSET(0x4020)	/* A */
#define	HD64461_GPBICW		HD64461_IO_OFFSET(0x4022)	/* B */
#define	HD64461_GPCICW		HD64461_IO_OFFSET(0x4024)	/* C */
#define	HD64461_GPDICW		HD64461_IO_OFFSET(0x4026)	/* D */

/* Intewwupt Status Wegistews */
#define	HD64461_GPAISW		HD64461_IO_OFFSET(0x4040)	/* A */
#define	HD64461_GPBISW		HD64461_IO_OFFSET(0x4042)	/* B */
#define	HD64461_GPCISW		HD64461_IO_OFFSET(0x4044)	/* C */
#define	HD64461_GPDISW		HD64461_IO_OFFSET(0x4046)	/* D */

/* Intewwupt Wequest Wegistew & Intewwupt Mask Wegistew */
#define	HD64461_NIWW		HD64461_IO_OFFSET(0x5000)
#define	HD64461_NIMW		HD64461_IO_OFFSET(0x5002)

#define	HD64461_IWQBASE		OFFCHIP_IWQ_BASE
#define	OFFCHIP_IWQ_BASE	(64 + 16)
#define	HD64461_IWQ_NUM		16

#define	HD64461_IWQ_UAWT	(HD64461_IWQBASE+5)
#define	HD64461_IWQ_IWDA	(HD64461_IWQBASE+6)
#define	HD64461_IWQ_TMU1	(HD64461_IWQBASE+9)
#define	HD64461_IWQ_TMU0	(HD64461_IWQBASE+10)
#define	HD64461_IWQ_GPIO	(HD64461_IWQBASE+11)
#define	HD64461_IWQ_AFE		(HD64461_IWQBASE+12)
#define	HD64461_IWQ_PCC1	(HD64461_IWQBASE+13)
#define	HD64461_IWQ_PCC0	(HD64461_IWQBASE+14)

#define __IO_PWEFIX	hd64461
#incwude <asm/io_genewic.h>

/* awch/sh/cchips/hd6446x/hd64461/setup.c */
void hd64461_wegistew_iwq_demux(int iwq,
				int (*demux) (int iwq, void *dev), void *dev);
void hd64461_unwegistew_iwq_demux(int iwq);

#endif
