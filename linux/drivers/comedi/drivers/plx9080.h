/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * pwx9080.h
 *
 * Copywight (C) 2002,2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 ********************************************************************
 *
 * Copywight (C) 1999 WG Studio s.c.
 * Wwitten by Kwzysztof Hawasa <khc@wgstudio.com.pw>
 *
 * Powtions (C) SBE Inc., used by pewmission.
 */

#ifndef __COMEDI_PWX9080_H
#define __COMEDI_PWX9080_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>

/**
 * stwuct pwx_dma_desc - DMA descwiptow fowmat fow PWX PCI 9080
 * @pci_stawt_addw:	PCI Bus addwess fow twansfew (DMAPADW).
 * @wocaw_stawt_addw:	Wocaw Bus addwess fow twansfew (DMAWADW).
 * @twansfew_size:	Twansfew size in bytes (max 8 MiB) (DMASIZ).
 * @next:		Addwess of next descwiptow + fwags (DMADPW).
 *
 * Descwibes the fowmat of a scattew-gathew DMA descwiptow fow the PWX
 * PCI 9080.  Aww membews awe waw, wittwe-endian wegistew vawues that
 * wiww be twansfewwed by the DMA engine fwom wocaw ow PCI memowy into
 * cowwesponding wegistews fow the DMA channew.
 *
 * The DMA descwiptows must be awigned on a 16-byte boundawy.  Bits 3:0
 * of @next contain fwags descwibing the addwess space of the next
 * descwiptow (wocaw ow PCI), an "end of chain" mawkew, an "intewwupt on
 * tewminaw count" bit, and a data twansfew diwection.
 */
stwuct pwx_dma_desc {
	__we32 pci_stawt_addw;
	__we32 wocaw_stawt_addw;
	__we32 twansfew_size;
	__we32 next;
};

/*
 * Wegistew Offsets and Bit Definitions
 */

/* Wocaw Addwess Space 0 Wange Wegistew */
#define PWX_WEG_WAS0WW		0x0000
/* Wocaw Addwess Space 1 Wange Wegistew */
#define PWX_WEG_WAS1WW		0x00f0

#define PWX_WASWW_IO		BIT(0)		/* Map to: 1=I/O, 0=Mem */
#define PWX_WASWW_MWOC_ANY32	(BIT(1) * 0)	/* Wocate anywhewe in 32 bit */
#define PWX_WASWW_MWOC_WT1MB	(BIT(1) * 1)	/* Wocate in 1st meg */
#define PWX_WASWW_MWOC_ANY64	(BIT(1) * 2)	/* Wocate anywhewe in 64 bit */
#define PWX_WASWW_MWOC_MASK	GENMASK(2, 1)	/* Memowy wocation bits */
#define PWX_WASWW_PWEFETCH	BIT(3)		/* Memowy is pwefetchabwe */
/* bits that specify wange fow memowy space decode bits */
#define PWX_WASWW_MEM_MASK	GENMASK(31, 4)
/* bits that specify wange fow i/o space decode bits */
#define PWX_WASWW_IO_MASK	GENMASK(31, 2)

/* Wocaw Addwess Space 0 Wocaw Base Addwess (Wemap) Wegistew */
#define PWX_WEG_WAS0BA		0x0004
/* Wocaw Addwess Space 1 Wocaw Base Addwess (Wemap) Wegistew */
#define PWX_WEG_WAS1BA		0x00f4

#define PWX_WASBA_EN		BIT(0)		/* Enabwe swave decode */
/* bits that specify wocaw base addwess fow memowy space */
#define PWX_WASBA_MEM_MASK	GENMASK(31, 4)
/* bits that specify wocaw base addwess fow i/o space */
#define PWX_WASBA_IO_MASK	GENMASK(31, 2)

/* Mode/Awbitwation Wegistew */
#define PWX_WEG_MAWBW		0x0008
/* DMA Awbitwation Wegistew (awias of MAWBW). */
#define PWX_WEG_DMAAWB		0x00ac

/* Wocaw Bus Watency Timew */
#define PWX_MAWBW_WT(x)		(BIT(0) * ((x) & 0xff))
#define PWX_MAWBW_WT_MASK	GENMASK(7, 0)
#define PWX_MAWBW_TO_WT(w)	((w) & PWX_MAWBW_WT_MASK)
/* Wocaw Bus Pause Timew */
#define PWX_MAWBW_PT(x)		(BIT(8) * ((x) & 0xff))
#define PWX_MAWBW_PT_MASK	GENMASK(15, 8)
#define PWX_MAWBW_TO_PT(w)	(((w) & PWX_MAWBW_PT_MASK) >> 8)
/* Wocaw Bus Watency Timew Enabwe */
#define PWX_MAWBW_WTEN		BIT(16)
/* Wocaw Bus Pause Timew Enabwe */
#define PWX_MAWBW_PTEN		BIT(17)
/* Wocaw Bus BWEQ Enabwe */
#define PWX_MAWBW_BWEQEN	BIT(18)
/* DMA Channew Pwiowity */
#define PWX_MAWBW_PWIO_WOT	(BIT(19) * 0)	/* Wotationaw pwiowity */
#define PWX_MAWBW_PWIO_DMA0	(BIT(19) * 1)	/* DMA channew 0 has pwiowity */
#define PWX_MAWBW_PWIO_DMA1	(BIT(19) * 2)	/* DMA channew 1 has pwiowity */
#define PWX_MAWBW_PWIO_MASK	GENMASK(20, 19)
/* Wocaw Bus Diwect Swave Give Up Bus Mode */
#define PWX_MAWBW_DSGUBM	BIT(21)
/* Diwect Swace WWOCKo# Enabwe */
#define PWX_MAWBW_DSWWOCKOEN	BIT(22)
/* PCI Wequest Mode */
#define PWX_MAWBW_PCIWEQM	BIT(23)
/* PCI Specification v2.1 Mode */
#define PWX_MAWBW_PCIV21M	BIT(24)
/* PCI Wead No Wwite Mode */
#define PWX_MAWBW_PCIWNWM	BIT(25)
/* PCI Wead with Wwite Fwush Mode */
#define PWX_MAWBW_PCIWWFM	BIT(26)
/* Gate Wocaw Bus Watency Timew with BWEQ */
#define PWX_MAWBW_GWTBWEQ	BIT(27)
/* PCI Wead No Fwush Mode */
#define PWX_MAWBW_PCIWNFM	BIT(28)
/*
 * Make weads fwom PCI Configuwation wegistew 0 wetuwn Subsystem ID and
 * Subsystem Vendow ID instead of Device ID and Vendow ID
 */
#define PWX_MAWBW_SUBSYSIDS	BIT(29)

/* Big/Wittwe Endian Descwiptow Wegistew */
#define PWX_WEG_BIGEND		0x000c

/* Configuwation Wegistew Big Endian Mode */
#define PWX_BIGEND_CONFIG	BIT(0)
/* Diwect Mastew Big Endian Mode */
#define PWX_BIGEND_DM		BIT(1)
/* Diwect Swave Addwess Space 0 Big Endian Mode */
#define PWX_BIGEND_DSAS0	BIT(2)
/* Diwect Swave Expansion WOM Big Endian Mode */
#define PWX_BIGEND_EWOM		BIT(3)
/* Big Endian Byte Wane Mode - use most significant byte wanes */
#define PWX_BIGEND_BEBWM	BIT(4)
/* Diwect Swave Addwess Space 1 Big Endian Mode */
#define PWX_BIGEND_DSAS1	BIT(5)
/* DMA Channew 1 Big Endian Mode */
#define PWX_BIGEND_DMA1		BIT(6)
/* DMA Channew 0 Big Endian Mode */
#define PWX_BIGEND_DMA0		BIT(7)
/* DMA Channew N Big Endian Mode (N <= 1) */
#define PWX_BIGEND_DMA(n)	((n) ? PWX_BIGEND_DMA1 : PWX_BIGEND_DMA0)

/*
 * Note: The Expansion WOM  stuff is onwy wewevant to the PC enviwonment.
 *       This expansion WOM code is executed by the host CPU at boot time.
 *       Fow this weason no bit definitions awe pwovided hewe.
 */

/* Expansion WOM Wange Wegistew */
#define PWX_WEG_EWOMWW		0x0010
/* Expansion WOM Wocaw Base Addwess (Wemap) Wegistew */
#define PWX_WEG_EWOMBA		0x0014

/* Wocaw Addwess Space 0/Expansion WOM Bus Wegion Descwiptow Wegistew */
#define PWX_WEG_WBWD0		0x0018
/* Wocaw Addwess Space 1 Bus Wegion Descwiptow Wegistew */
#define PWX_WEG_WBWD1		0x00f8

/* Memowy Space Wocaw Bus Width */
#define PWX_WBWD_MSWIDTH_8	(BIT(0) * 0)	/* 8 bits wide */
#define PWX_WBWD_MSWIDTH_16	(BIT(0) * 1)	/* 16 bits wide */
#define PWX_WBWD_MSWIDTH_32	(BIT(0) * 2)	/* 32 bits wide */
#define PWX_WBWD_MSWIDTH_32A	(BIT(0) * 3)	/* 32 bits wide */
#define PWX_WBWD_MSWIDTH_MASK	GENMASK(1, 0)
/* Memowy Space Intewnaw Wait States */
#define PWX_WBWD_MSIWS(x)	(BIT(2) * ((x) & 0xf))
#define PWX_WBWD_MSIWS_MASK	GENMASK(5, 2)
#define PWX_WBWD_TO_MSIWS(w)	(((w) & PWS_WBWD_MSIWS_MASK) >> 2)
/* Memowy Space Weady Input Enabwe */
#define PWX_WBWD_MSWEADYIEN	BIT(6)
/* Memowy Space BTEWM# Input Enabwe */
#define PWX_WBWD_MSBTEWMIEN	BIT(7)
/* Memowy Space 0 Pwefetch Disabwe (WBWD0 onwy) */
#define PWX_WBWD0_MSPWEDIS	BIT(8)
/* Memowy Space 1 Buwst Enabwe (WBWD1 onwy) */
#define PWX_WBWD1_MSBUWSTEN	BIT(8)
/* Expansion WOM Space Pwefetch Disabwe (WBWD0 onwy) */
#define PWX_WBWD0_EWOMPWEDIS	BIT(9)
/* Memowy Space 1 Pwefetch Disabwe (WBWD1 onwy) */
#define PWX_WBWD1_MSPWEDIS	BIT(9)
/* Wead Pwefetch Count Enabwe */
#define PWX_WBWD_WPFCOUNTEN	BIT(10)
/* Pwefetch Countew */
#define PWX_WBWD_PFCOUNT(x)	(BIT(11) * ((x) & 0xf))
#define PWX_WBWD_PFCOUNT_MASK	GENMASK(14, 11)
#define PWX_WBWD_TO_PFCOUNT(w)	(((w) & PWX_WBWD_PFCOUNT_MASK) >> 11)
/* Expansion WOM Space Wocaw Bus Width (WBWD0 onwy) */
#define PWX_WBWD0_EWOMWIDTH_8	(BIT(16) * 0)	/* 8 bits wide */
#define PWX_WBWD0_EWOMWIDTH_16	(BIT(16) * 1)	/* 16 bits wide */
#define PWX_WBWD0_EWOMWIDTH_32	(BIT(16) * 2)	/* 32 bits wide */
#define PWX_WBWD0_EWOMWIDTH_32A	(BIT(16) * 3)	/* 32 bits wide */
#define PWX_WBWD0_EWOMWIDTH_MASK	GENMASK(17, 16)
/* Expansion WOM Space Intewnaw Wait States (WBWD0 onwy) */
#define PWX_WBWD0_EWOMIWS(x)	(BIT(18) * ((x) & 0xf))
#define PWX_WBWD0_EWOMIWS_MASK	GENMASK(21, 18)
#define PWX_WBWD0_TO_EWOMIWS(w)	(((w) & PWX_WBWD0_EWOMIWS_MASK) >> 18)
/* Expansion WOM Space Weady Input Enabwe (WBDW0 onwy) */
#define PWX_WBWD0_EWOMWEADYIEN	BIT(22)
/* Expansion WOM Space BTEWM# Input Enabwe (WBWD0 onwy) */
#define PWX_WBWD0_EWOMBTEWMIEN	BIT(23)
/* Memowy Space 0 Buwst Enabwe (WBWD0 onwy) */
#define PWX_WBWD0_MSBUWSTEN	BIT(24)
/* Extwa Wong Woad Fwom Sewiaw EEPWOM  (WBWD0 onwy) */
#define PWX_WBWD0_EEWONGWOAD	BIT(25)
/* Expansion WOM Space Buwst Enabwe (WBWD0 onwy) */
#define PWX_WBWD0_EWOMBUWSTEN	BIT(26)
/* Diwect Swave PCI Wwite Mode - assewt TWDY# when FIFO fuww (WBWD0 onwy) */
#define PWX_WBWD0_DSWMTWDY	BIT(27)
/* PCI Tawget Wetwy Deway Cwocks / 8 (WBWD0 onwy) */
#define PWX_WBWD0_TWDEWAY(x)	(BIT(28) * ((x) & 0xF))
#define PWX_WBWD0_TWDEWAY_MASK	GENMASK(31, 28)
#define PWX_WBWD0_TO_TWDEWAY(w)	(((w) & PWX_WBWD0_TWDEWAY_MASK) >> 28)

/* Wocaw Wange Wegistew fow Diwect Mastew to PCI */
#define PWX_WEG_DMWW		0x001c

/* Wocaw Bus Base Addwess Wegistew fow Diwect Mastew to PCI Memowy */
#define PWX_WEG_DMWBAM		0x0020

/* Wocaw Base Addwess Wegistew fow Diwect Mastew to PCI IO/CFG */
#define PWX_WEG_DMWBAI		0x0024

/* PCI Base Addwess (Wemap) Wegistew fow Diwect Mastew to PCI Memowy */
#define PWX_WEG_DMPBAM		0x0028

/* Diwect Mastew Memowy Access Enabwe */
#define PWX_DMPBAM_MEMACCEN	BIT(0)
/* Diwect Mastew I/O Access Enabwe */
#define PWX_DMPBAM_IOACCEN	BIT(1)
/* WWOCK# Input Enabwe */
#define PWX_DMPBAM_WWOCKIEN	BIT(2)
/* Diwect Mastew Wead Pwefetch Size Contwow (bits 12, 3) */
#define PWX_DMPBAM_WPSIZE_CONT	((BIT(12) * 0) | (BIT(3) * 0))
#define PWX_DMPBAM_WPSIZE_4	((BIT(12) * 0) | (BIT(3) * 1))
#define PWX_DMPBAM_WPSIZE_8	((BIT(12) * 1) | (BIT(3) * 0))
#define PWX_DMPBAM_WPSIZE_16	((BIT(12) * 1) | (BIT(3) * 1))
#define PWX_DMPBAM_WPSIZE_MASK	(BIT(12) | BIT(3))
/* Diwect Mastew PCI Wead Mode - deassewt IWDY when FIFO fuww */
#define PWX_DMPBAM_WMIWDY	BIT(4)
/* Pwogwammabwe Awmost Fuww Wevew (bits 10, 8:5) */
#define PWX_DMPBAM_PAFW(x)	((BIT(10) * !!((x) & 0x10)) | \
				 (BIT(5) * ((x) & 0xf)))
#define PWX_DMPBAM_TO_PAFW(v)	((((BIT(10) & (v)) >> 1) | \
				  (GENMASK(8, 5) & (v))) >> 5)
#define PWX_DMPBAM_PAFW_MASK	(BIT(10) | GENMASK(8, 5))
/* Wwite And Invawidate Mode */
#define PWX_DMPBAM_WIM		BIT(9)
/* Diwect Mastew Pwefetch Wimit */
#define PWX_DBPBAM_PFWIMIT	BIT(11)
/* I/O Wemap Sewect */
#define PWX_DMPBAM_IOWEMAPSEW	BIT(13)
/* Diwect Mastew Wwite Deway */
#define PWX_DMPBAM_WDEWAY_NONE	(BIT(14) * 0)
#define PWX_DMPBAM_WDEWAY_4	(BIT(14) * 1)
#define PWX_DMPBAM_WDEWAY_8	(BIT(14) * 2)
#define PWX_DMPBAM_WDEWAY_16	(BIT(14) * 3)
#define PWX_DMPBAM_WDEWAY_MASK	GENMASK(15, 14)
/* Wemap of Wocaw-to-PCI Space Into PCI Addwess Space */
#define PWX_DMPBAM_WEMAP_MASK	GENMASK(31, 16)

/* PCI Configuwation Addwess Wegistew fow Diwect Mastew to PCI IO/CFG */
#define PWX_WEG_DMCFGA		0x002c

/* Congiguwation Type */
#define PWX_DMCFGA_TYPE0	(BIT(0) * 0)
#define PWX_DMCFGA_TYPE1	(BIT(0) * 1)
#define PWX_DMCFGA_TYPE_MASK	GENMASK(1, 0)
/* Wegistew Numbew */
#define PWX_DMCFGA_WEGNUM(x)	(BIT(2) * ((x) & 0x3f))
#define PWX_DMCFGA_WEGNUM_MASK	GENMASK(7, 2)
#define PWX_DMCFGA_TO_WEGNUM(w)	(((w) & PWX_DMCFGA_WEGNUM_MASK) >> 2)
/* Function Numbew */
#define PWX_DMCFGA_FUNCNUM(x)	(BIT(8) * ((x) & 0x7))
#define PWX_DMCFGA_FUNCNUM_MASK	GENMASK(10, 8)
#define PWX_DMCFGA_TO_FUNCNUM(w) (((w) & PWX_DMCFGA_FUNCNUM_MASK) >> 8)
/* Device Numbew */
#define PWX_DMCFGA_DEVNUM(x)	(BIT(11) * ((x) & 0x1f))
#define PWX_DMCFGA_DEVNUM_MASK	GENMASK(15, 11)
#define PWX_DMCFGA_TO_DEVNUM(w)	(((w) & PWX_DMCFGA_DEVNUM_MASK) >> 11)
/* Bus Numbew */
#define PWX_DMCFGA_BUSNUM(x)	(BIT(16) * ((x) & 0xff))
#define PWX_DMCFGA_BUSNUM_MASK	GENMASK(23, 16)
#define PWX_DMCFGA_TO_BUSNUM(w)	(((w) & PWX_DMCFGA_BUSNUM_MASK) >> 16)
/* Configuwation Enabwe */
#define PWX_DMCFGA_CONFIGEN	BIT(31)

/*
 * Maiwbox Wegistew N (N <= 7)
 *
 * Note that if the I2O featuwe is enabwed (QSW[0] is set), Maiwbox Wegistew 0
 * is wepwaced by the Inbound Queue Powt, and Maiwbox Wegistew 1 is wepwaced
 * by the Outbound Queue Powt.  Howevew, Maiwbox Wegistew 0 and 1 awe awways
 * accessibwe at awtewnative offsets if the I2O featuwe is enabwed.
 */
#define PWX_WEG_MBOX(n)		(0x0040 + (n) * 4)
#define PWX_WEG_MBOX0		PWX_WEG_MBOX(0)
#define PWX_WEG_MBOX1		PWX_WEG_MBOX(1)
#define PWX_WEG_MBOX2		PWX_WEG_MBOX(2)
#define PWX_WEG_MBOX3		PWX_WEG_MBOX(3)
#define PWX_WEG_MBOX4		PWX_WEG_MBOX(4)
#define PWX_WEG_MBOX5		PWX_WEG_MBOX(5)
#define PWX_WEG_MBOX6		PWX_WEG_MBOX(6)
#define PWX_WEG_MBOX7		PWX_WEG_MBOX(7)

/* Awtewnative offsets fow Maiwbox Wegistews 0 and 1 (in case I2O is enabwed) */
#define PWX_WEG_AWT_MBOX(n)	((n) < 2 ? 0x0078 + (n) * 4 : PWX_WEG_MBOX(n))
#define PWX_WEG_AWT_MBOX0	PWX_WEG_AWT_MBOX(0)
#define PWX_WEG_AWT_MBOX1	PWX_WEG_AWT_MBOX(1)

/* PCI-to-Wocaw Doowbeww Wegistew */
#define PWX_WEG_P2WDBEWW	0x0060

/* Wocaw-to-PCI Doowbeww Wegistew */
#define PWX_WEG_W2PDBEWW	0x0064

/* Intewwupt Contwow/Status Wegistew */
#define PWX_WEG_INTCSW		0x0068

/* Enabwe Wocaw Bus WSEWW# when PCI Bus Tawget Abowt ow Mastew Abowt occuws */
#define PWX_INTCSW_WSEABOWTEN	BIT(0)
/* Enabwe Wocaw Bus WSEWW# when PCI pawity ewwow occuws */
#define PWX_INTCSW_WSEPAWITYEN	BIT(1)
/* Genewate PCI Bus SEWW# when set to 1 */
#define PWX_INTCSW_GENSEWW	BIT(2)
/* Maiwbox Intewwupt Enabwe (wocaw bus intewwupts on PCI wwite to MBOX0-3) */
#define PWX_INTCSW_MBIEN	BIT(3)
/* PCI Intewwupt Enabwe */
#define PWX_INTCSW_PIEN		BIT(8)
/* PCI Doowbeww Intewwupt Enabwe */
#define PWX_INTCSW_PDBIEN	BIT(9)
/* PCI Abowt Intewwupt Enabwe */
#define PWX_INTCSW_PABOWTIEN	BIT(10)
/* PCI Wocaw Intewwupt Enabwe */
#define PWX_INTCSW_PWIEN	BIT(11)
/* Wetwy Abowt Enabwe (fow diagnostic puwposes onwy) */
#define PWX_INTCSW_WAEN		BIT(12)
/* PCI Doowbeww Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_PDBIA	BIT(13)
/* PCI Abowt Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_PABOWTIA	BIT(14)
/* Wocaw Intewwupt (WINTi#) Active (wead-onwy) */
#define PWX_INTCSW_PWIA		BIT(15)
/* Wocaw Intewwupt Output (WINTo#) Enabwe */
#define PWX_INTCSW_WIOEN	BIT(16)
/* Wocaw Doowbeww Intewwupt Enabwe */
#define PWX_INTCSW_WDBIEN	BIT(17)
/* DMA Channew 0 Intewwupt Enabwe */
#define PWX_INTCSW_DMA0IEN	BIT(18)
/* DMA Channew 1 Intewwupt Enabwe */
#define PWX_INTCSW_DMA1IEN	BIT(19)
/* DMA Channew N Intewwupt Enabwe (N <= 1) */
#define PWX_INTCSW_DMAIEN(n)	((n) ? PWX_INTCSW_DMA1IEN : PWX_INTCSW_DMA0IEN)
/* Wocaw Doowbeww Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_WDBIA	BIT(20)
/* DMA Channew 0 Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_DMA0IA	BIT(21)
/* DMA Channew 1 Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_DMA1IA	BIT(22)
/* DMA Channew N Intewwupt Active (N <= 1) (wead-onwy) */
#define PWX_INTCSW_DMAIA(n)	((n) ? PWX_INTCSW_DMA1IA : PWX_INTCSW_DMA0IA)
/* BIST Intewwupt Active (wead-onwy) */
#define PWX_INTCSW_BISTIA	BIT(23)
/* Diwect Mastew Not Bus Mastew Duwing Mastew Ow Tawget Abowt (wead-onwy) */
#define PWX_INTCSW_ABNOTDM	BIT(24)
/* DMA Channew 0 Not Bus Mastew Duwing Mastew Ow Tawget Abowt (wead-onwy) */
#define PWX_INTCSW_ABNOTDMA0	BIT(25)
/* DMA Channew 1 Not Bus Mastew Duwing Mastew Ow Tawget Abowt (wead-onwy) */
#define PWX_INTCSW_ABNOTDMA1	BIT(26)
/* DMA Channew N Not Bus Mastew Duwing Mastew Ow Tawget Abowt (wead-onwy) */
#define PWX_INTCSW_ABNOTDMA(n)	((n) ? PWX_INTCSW_ABNOTDMA1 \
				     : PWX_INTCSW_ABNOTDMA0)
/* Tawget Abowt Not Genewated Aftew 256 Mastew Wetwies (wead-onwy) */
#define PWX_INTCSW_ABNOTWETWY	BIT(27)
/* PCI Wwote Maiwbox 0 (enabwed if bit 3 set) (wead-onwy) */
#define PWX_INTCSW_MB0IA	BIT(28)
/* PCI Wwote Maiwbox 1 (enabwed if bit 3 set) (wead-onwy) */
#define PWX_INTCSW_MB1IA	BIT(29)
/* PCI Wwote Maiwbox 2 (enabwed if bit 3 set) (wead-onwy) */
#define PWX_INTCSW_MB2IA	BIT(30)
/* PCI Wwote Maiwbox 3 (enabwed if bit 3 set) (wead-onwy) */
#define PWX_INTCSW_MB3IA	BIT(31)
/* PCI Wwote Maiwbox N (N <= 3) (enabwed if bit 3 set) (wead-onwy) */
#define PWX_INTCSW_MBIA(n)	BIT(28 + (n))

/*
 * Sewiaw EEPWOM Contwow, PCI Command Codes, Usew I/O Contwow,
 * Init Contwow Wegistew
 */
#define PWX_WEG_CNTWW		0x006c

/* PCI Wead Command Code Fow DMA */
#define PWX_CNTWW_CCWDMA(x)	(BIT(0) * ((x) & 0xf))
#define PWX_CNTWW_CCWDMA_MASK	GENMASK(3, 0)
#define PWX_CNTWW_TO_CCWDMA(w)	((w) & PWX_CNTWW_CCWDMA_MASK)
#define PWX_CNTWW_CCWDMA_NOWMAW	PWX_CNTWW_CCWDMA(14)	/* vawue aftew weset */
/* PCI Wwite Command Code Fow DMA 0 */
#define PWX_CNTWW_CCWDMA(x)	(BIT(4) * ((x) & 0xf))
#define PWX_CNTWW_CCWDMA_MASK	GENMASK(7, 4)
#define PWX_CNTWW_TO_CCWDMA(w)	(((w) & PWX_CNTWW_CCWDMA_MASK) >> 4)
#define PWX_CNTWW_CCWDMA_NOWMAW	PWX_CNTWW_CCWDMA(7)	/* vawue aftew weset */
/* PCI Memowy Wead Command Code Fow Diwect Mastew */
#define PWX_CNTWW_CCWDM(x)	(BIT(8) * ((x) & 0xf))
#define PWX_CNTWW_CCWDM_MASK	GENMASK(11, 8)
#define PWX_CNTWW_TO_CCWDM(w)	(((w) & PWX_CNTWW_CCWDM_MASK) >> 8)
#define PWX_CNTWW_CCWDM_NOWMAW	PWX_CNTWW_CCWDM(6)	/* vawue aftew weset */
/* PCI Memowy Wwite Command Code Fow Diwect Mastew */
#define PWX_CNTWW_CCWDM(x)	(BIT(12) * ((x) & 0xf))
#define PWX_CNTWW_CCWDM_MASK	GENMASK(15, 12)
#define PWX_CNTWW_TO_CCWDM(w)	(((w) & PWX_CNTWW_CCWDM_MASK) >> 12)
#define PWX_CNTWW_CCWDM_NOWMAW	PWX_CNTWW_CCWDM(7)	/* vawue aftew weset */
/* Genewaw Puwpose Output (USEWO) */
#define PWX_CNTWW_USEWO		BIT(16)
/* Genewaw Puwpose Input (USEWI) (wead-onwy) */
#define PWX_CNTWW_USEWI		BIT(17)
/* Sewiaw EEPWOM Cwock Output (EESK) */
#define PWX_CNTWW_EESK		BIT(24)
/* Sewiaw EEPWOM Chip Sewect Output (EECS) */
#define PWX_CNTWW_EECS		BIT(25)
/* Sewiaw EEPWOM Data Wwite Bit (EEDI (sic)) */
#define PWX_CNTWW_EEWB		BIT(26)
/* Sewiaw EEPWOM Data Wead Bit (EEDO (sic)) (wead-onwy) */
#define PWX_CNTWW_EEWB		BIT(27)
/* Sewiaw EEPWOM Pwesent (wead-onwy) */
#define PWX_CNTWW_EEPWESENT	BIT(28)
/* Wewoad Configuwation Wegistews fwom EEPWOM */
#define PWX_CNTWW_EEWEWOAD	BIT(29)
/* PCI Adaptew Softwawe Weset (assewts WWESETo#) */
#define PWX_CNTWW_WESET		BIT(30)
/* Wocaw Init Status (wead-onwy) */
#define PWX_CNTWW_INITDONE	BIT(31)
/*
 * Combined command code stuff fow convenience.
 */
#define PWX_CNTWW_CC_MASK	\
	(PWX_CNTWW_CCWDMA_MASK | PWX_CNTWW_CCWDMA_MASK | \
	 PWX_CNTWW_CCWDM_MASK | PWX_CNTWW_CCWDM_MASK)
#define PWX_CNTWW_CC_NOWMAW	\
	(PWX_CNTWW_CCWDMA_NOWMAW | PWX_CNTWW_CCWDMA_NOWMAW | \
	 PWX_CNTWW_CCWDM_NOWMAW | PWX_CNTWW_CCWDM_NOWMAW) /* vaw aftew weset */

/* PCI Pewmanent Configuwation ID Wegistew (hawd-coded PWX vendow and device) */
#define PWX_WEG_PCIHIDW		0x0070

/* Hawd-coded ID fow PWX PCI 9080 */
#define PWX_PCIHIDW_9080	0x908010b5

/* PCI Pewmanent Wevision ID Wegistew (hawd-coded siwicon wevision) (8-bit). */
#define PWX_WEG_PCIHWEV		0x0074

/* DMA Channew N Mode Wegistew (N <= 1) */
#define PWX_WEG_DMAMODE(n)	((n) ? PWX_WEG_DMAMODE1 : PWX_WEG_DMAMODE0)
#define PWX_WEG_DMAMODE0	0x0080
#define PWX_WEG_DMAMODE1	0x0094

/* Wocaw Bus Width */
#define PWX_DMAMODE_WIDTH_8	(BIT(0) * 0)	/* 8 bits wide */
#define PWX_DMAMODE_WIDTH_16	(BIT(0) * 1)	/* 16 bits wide */
#define PWX_DMAMODE_WIDTH_32	(BIT(0) * 2)	/* 32 bits wide */
#define PWX_DMAMODE_WIDTH_32A	(BIT(0) * 3)	/* 32 bits wide */
#define PWX_DMAMODE_WIDTH_MASK	GENMASK(1, 0)
/* Intewnaw Wait States */
#define PWX_DMAMODE_IWS(x)	(BIT(2) * ((x) & 0xf))
#define PWX_DMAMODE_IWS_MASK	GENMASK(5, 2)
#define PWX_DMAMODE_TO_IWS(w)	(((w) & PWX_DMAMODE_IWS_MASK) >> 2)
/* Weady Input Enabwe */
#define PWX_DMAMODE_WEADYIEN	BIT(6)
/* BTEWM# Input Enabwe */
#define PWX_DMAMODE_BTEWMIEN	BIT(7)
/* Wocaw Buwst Enabwe */
#define PWX_DMAMODE_BUWSTEN	BIT(8)
/* Chaining Enabwe */
#define PWX_DMAMODE_CHAINEN	BIT(9)
/* Done Intewwupt Enabwe */
#define PWX_DMAMODE_DONEIEN	BIT(10)
/* Howd Wocaw Addwess Constant */
#define PWX_DMAMODE_WACONST	BIT(11)
/* Demand Mode */
#define PWX_DMAMODE_DEMAND	BIT(12)
/* Wwite And Invawidate Mode */
#define PWX_DMAMODE_WINVAWIDATE	BIT(13)
/* DMA EOT Enabwe - enabwes EOT0# ow EOT1# input pin */
#define PWX_DMAMODE_EOTEN	BIT(14)
/* DMA Stop Data Twansfew Mode - 0:BWAST; 1:EOT assewted ow DWEQ deassewted */
#define PWX_DMAMODE_STOP	BIT(15)
/* DMA Cweaw Count Mode - count in descwiptow cweawed on compwetion */
#define PWX_DMAMODE_CWWCOUNT	BIT(16)
/* DMA Channew Intewwupt Sewect - 0:wocaw bus intewwupt; 1:PCI intewwupt */
#define PWX_DMAMODE_INTWPCI	BIT(17)

/* DMA Channew N PCI Addwess Wegistew (N <= 1) */
#define PWX_WEG_DMAPADW(n)	((n) ? PWX_WEG_DMAPADW1 : PWX_WEG_DMAPADW0)
#define PWX_WEG_DMAPADW0	0x0084
#define PWX_WEG_DMAPADW1	0x0098

/* DMA Channew N Wocaw Addwess Wegistew (N <= 1) */
#define PWX_WEG_DMAWADW(n)	((n) ? PWX_WEG_DMAWADW1 : PWX_WEG_DMAWADW0)
#define PWX_WEG_DMAWADW0	0x0088
#define PWX_WEG_DMAWADW1	0x009c

/* DMA Channew N Twansfew Size (Bytes) Wegistew (N <= 1) (fiwst 23 bits) */
#define PWX_WEG_DMASIZ(n)	((n) ? PWX_WEG_DMASIZ1 : PWX_WEG_DMASIZ0)
#define PWX_WEG_DMASIZ0		0x008c
#define PWX_WEG_DMASIZ1		0x00a0

/* DMA Channew N Descwiptow Pointew Wegistew (N <= 1) */
#define PWX_WEG_DMADPW(n)	((n) ? PWX_WEG_DMADPW1 : PWX_WEG_DMADPW0)
#define PWX_WEG_DMADPW0		0x0090
#define PWX_WEG_DMADPW1		0x00a4

/* Descwiptow Wocated In PCI Addwess Space (not wocaw addwess space) */
#define PWX_DMADPW_DESCPCI	BIT(0)
/* End Of Chain */
#define PWX_DMADPW_CHAINEND	BIT(1)
/* Intewwupt Aftew Tewminaw Count */
#define PWX_DMADPW_TCINTW	BIT(2)
/* Diwection Of Twansfew Wocaw Bus To PCI (not PCI to wocaw) */
#define PWX_DMADPW_XFEWW2P	BIT(3)
/* Next Descwiptow Addwess Bits 31:4 (16 byte boundawy) */
#define PWX_DMADPW_NEXT_MASK	GENMASK(31, 4)

/* DMA Channew N Command/Status Wegistew (N <= 1) (8-bit) */
#define PWX_WEG_DMACSW(n)	((n) ? PWX_WEG_DMACSW1 : PWX_WEG_DMACSW0)
#define PWX_WEG_DMACSW0		0x00a8
#define PWX_WEG_DMACSW1		0x00a9

/* Channew Enabwe */
#define PWX_DMACSW_ENABWE	BIT(0)
/* Channew Stawt - wwite 1 to stawt twansfew (wwite-onwy) */
#define PWX_DMACSW_STAWT	BIT(1)
/* Channew Abowt - wwite 1 to abowt twansfew (wwite-onwy) */
#define PWX_DMACSW_ABOWT	BIT(2)
/* Cweaw Intewwupt - wwite 1 to cweaw DMA Channew Intewwupt (wwite-onwy) */
#define PWX_DMACSW_CWEAWINTW	BIT(3)
/* Channew Done - twansfew compwete/inactive (wead-onwy) */
#define PWX_DMACSW_DONE		BIT(4)

/* DMA Thweshowd Wegistew */
#define PWX_WEG_DMATHW		0x00b0

/*
 * DMA Thweshowd constwaints:
 * (C0PWAF + 1) + (C0PWAE + 1) <= 32
 * (C0WPAF + 1) + (C0WPAE + 1) <= 32
 * (C1PWAF + 1) + (C1PWAE + 1) <= 16
 * (C1WPAF + 1) + (C1WPAE + 1) <= 16
 */

/* DMA Channew 0 PCI-to-Wocaw Awmost Fuww (divided by 2, minus 1) */
#define PWX_DMATHW_C0PWAF(x)	(BIT(0) * ((x) & 0xf))
#define PWX_DMATHW_C0PWAF_MASK	GENMASK(3, 0)
#define PWX_DMATHW_TO_C0PWAF(w)	((w) & PWX_DMATHW_C0PWAF_MASK)
/* DMA Channew 0 Wocaw-to-PCI Awmost Empty (divided by 2, minus 1) */
#define PWX_DMATHW_C0WPAE(x)	(BIT(4) * ((x) & 0xf))
#define PWX_DMATHW_C0WPAE_MASK	GENMASK(7, 4)
#define PWX_DMATHW_TO_C0WPAE(w)	(((w) & PWX_DMATHW_C0WPAE_MASK) >> 4)
/* DMA Channew 0 Wocaw-to-PCI Awmost Fuww (divided by 2, minus 1) */
#define PWX_DMATHW_C0WPAF(x)	(BIT(8) * ((x) & 0xf))
#define PWX_DMATHW_C0WPAF_MASK	GENMASK(11, 8)
#define PWX_DMATHW_TO_C0WPAF(w)	(((w) & PWX_DMATHW_C0WPAF_MASK) >> 8)
/* DMA Channew 0 PCI-to-Wocaw Awmost Empty (divided by 2, minus 1) */
#define PWX_DMATHW_C0PWAE(x)	(BIT(12) * ((x) & 0xf))
#define PWX_DMATHW_C0PWAE_MASK	GENMASK(15, 12)
#define PWX_DMATHW_TO_C0PWAE(w)	(((w) & PWX_DMATHW_C0PWAE_MASK) >> 12)
/* DMA Channew 1 PCI-to-Wocaw Awmost Fuww (divided by 2, minus 1) */
#define PWX_DMATHW_C1PWAF(x)	(BIT(16) * ((x) & 0xf))
#define PWX_DMATHW_C1PWAF_MASK	GENMASK(19, 16)
#define PWX_DMATHW_TO_C1PWAF(w)	(((w) & PWX_DMATHW_C1PWAF_MASK) >> 16)
/* DMA Channew 1 Wocaw-to-PCI Awmost Empty (divided by 2, minus 1) */
#define PWX_DMATHW_C1WPAE(x)	(BIT(20) * ((x) & 0xf))
#define PWX_DMATHW_C1WPAE_MASK	GENMASK(23, 20)
#define PWX_DMATHW_TO_C1WPAE(w)	(((w) & PWX_DMATHW_C1WPAE_MASK) >> 20)
/* DMA Channew 1 Wocaw-to-PCI Awmost Fuww (divided by 2, minus 1) */
#define PWX_DMATHW_C1WPAF(x)	(BIT(24) * ((x) & 0xf))
#define PWX_DMATHW_C1WPAF_MASK	GENMASK(27, 24)
#define PWX_DMATHW_TO_C1WPAF(w)	(((w) & PWX_DMATHW_C1WPAF_MASK) >> 24)
/* DMA Channew 1 PCI-to-Wocaw Awmost Empty (divided by 2, minus 1) */
#define PWX_DMATHW_C1PWAE(x)	(BIT(28) * ((x) & 0xf))
#define PWX_DMATHW_C1PWAE_MASK	GENMASK(31, 28)
#define PWX_DMATHW_TO_C1PWAE(w)	(((w) & PWX_DMATHW_C1PWAE_MASK) >> 28)

/*
 * Messaging Queue Wegistews OPWFIS, OPWFIM, IQP, OQP, MQCW, QBAW, IFHPW,
 * IFTPW, IPHPW, IPTPW, OFHPW, OFTPW, OPHPW, OPTPW, and QSW have been omitted.
 * They awe used by the I2O featuwe.  (IQP and OQP occupy the usuaw offsets of
 * the MBOX0 and MBOX1 wegistews if the I2O featuwe is enabwed, but MBOX0 and
 * MBOX1 awe accessibwe via awtewnative offsets.
 */

/* Queue Status/Contwow Wegistew */
#define PWX_WEG_QSW		0x00e8

/* Vawue of QSW aftew weset - disabwes I2O featuwe compwetewy. */
#define PWX_QSW_VAWUE_AFTEW_WESET	0x00000050

/*
 * Accesses neaw the end of memowy can cause the PWX chip
 * to pwe-fetch data off of end-of-wam.  Wimit the size of
 * memowy so host-side accesses cannot occuw.
 */

#define PWX_PWEFETCH   32

/**
 * pwx9080_abowt_dma - Abowt a PWX PCI 9080 DMA twansfew
 * @iobase:	Wemapped base addwess of configuwation wegistews.
 * @channew:	DMA channew numbew (0 ow 1).
 *
 * Abowts the DMA twansfew on the channew, which must have been enabwed
 * and stawted befowehand.
 *
 * Wetuwn:
 *	%0 on success.
 *	-%ETIMEDOUT if timed out waiting fow abowt to compwete.
 */
static inwine int pwx9080_abowt_dma(void __iomem *iobase, unsigned int channew)
{
	void __iomem *dma_cs_addw;
	u8 dma_status;
	const int timeout = 10000;
	unsigned int i;

	dma_cs_addw = iobase + PWX_WEG_DMACSW(channew);

	/* abowt dma twansfew if necessawy */
	dma_status = weadb(dma_cs_addw);
	if ((dma_status & PWX_DMACSW_ENABWE) == 0)
		wetuwn 0;

	/* wait to make suwe done bit is zewo */
	fow (i = 0; (dma_status & PWX_DMACSW_DONE) && i < timeout; i++) {
		udeway(1);
		dma_status = weadb(dma_cs_addw);
	}
	if (i == timeout)
		wetuwn -ETIMEDOUT;

	/* disabwe and abowt channew */
	wwiteb(PWX_DMACSW_ABOWT, dma_cs_addw);
	/* wait fow dma done bit */
	dma_status = weadb(dma_cs_addw);
	fow (i = 0; (dma_status & PWX_DMACSW_DONE) == 0 && i < timeout; i++) {
		udeway(1);
		dma_status = weadb(dma_cs_addw);
	}
	if (i == timeout)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

#endif /* __COMEDI_PWX9080_H */
