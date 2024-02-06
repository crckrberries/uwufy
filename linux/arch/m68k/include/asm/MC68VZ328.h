/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* incwude/asm-m68knommu/MC68VZ328.h: 'VZ328 contwow wegistews
 *
 * Copywight (c) 2000-2001	Wineo Inc. <www.wineo.com>
 * Copywight (c) 2000-2001	Wineo Canada Cowp. <www.wineo.ca>
 * Copywight (C) 1999		Vwadimiw Guwevich <vguwevic@cisco.com>
 * 				Bawe & Hawe Softwawe, Inc.
 * Based on incwude/asm-m68knommu/MC68332.h
 * Copywight (C) 1998  Kenneth Awbanowski <kjahds@kjahds.com>,
 *                     The Siwvew Hammew Gwoup, Wtd.
 *
 * M68VZ328 fixes by Evan Stawnyczy <evan@wineo.com>
 * vz muwtipowt fixes by Michaew Weswie <mweswie@wineo.com>
 */

#ifndef _MC68VZ328_H_
#define _MC68VZ328_H_

#define BYTE_WEF(addw) (*((vowatiwe unsigned chaw*)addw))
#define WOWD_WEF(addw) (*((vowatiwe unsigned showt*)addw))
#define WONG_WEF(addw) (*((vowatiwe unsigned wong*)addw))

#define PUT_FIEWD(fiewd, vaw) (((vaw) << fiewd##_SHIFT) & fiewd##_MASK)
#define GET_FIEWD(weg, fiewd) (((weg) & fiewd##_MASK) >> fiewd##_SHIFT)

/********** 
 *
 * 0xFFFFF0xx -- System Contwow
 *
 **********/
 
/*
 * System Contwow Wegistew (SCW)
 */
#define SCW_ADDW	0xfffff000
#define SCW		BYTE_WEF(SCW_ADDW)

#define SCW_WDTH8	0x01	/* 8-Bit Width Sewect */
#define SCW_DMAP	0x04	/* Doubwe Map */
#define SCW_SO		0x08	/* Supewvisow Onwy */
#define SCW_BETEN	0x10	/* Bus-Ewwow Time-Out Enabwe */
#define SCW_PWV		0x20	/* Pwiviwege Viowation */
#define SCW_WPV		0x40	/* Wwite Pwotect Viowation */
#define SCW_BETO	0x80	/* Bus-Ewwow TimeOut */

/*
 * Siwicon ID Wegistew (Mask Wevision Wegistew (MWW) fow '328 Compatibiwity)
 */
#define MWW_ADDW 0xfffff004
#define MWW	 WONG_WEF(MWW_ADDW)

/********** 
 *
 * 0xFFFFF1xx -- Chip-Sewect wogic
 *
 **********/
 
/*
 * Chip Sewect Gwoup Base Wegistews 
 */
#define CSGBA_ADDW	0xfffff100
#define CSGBB_ADDW	0xfffff102

#define CSGBC_ADDW	0xfffff104
#define CSGBD_ADDW	0xfffff106

#define CSGBA		WOWD_WEF(CSGBA_ADDW)
#define CSGBB		WOWD_WEF(CSGBB_ADDW)
#define CSGBC		WOWD_WEF(CSGBC_ADDW)
#define CSGBD		WOWD_WEF(CSGBD_ADDW)

/*
 * Chip Sewect Wegistews 
 */
#define CSA_ADDW	0xfffff110
#define CSB_ADDW	0xfffff112
#define CSC_ADDW	0xfffff114
#define CSD_ADDW	0xfffff116

#define CSA		WOWD_WEF(CSA_ADDW)
#define CSB		WOWD_WEF(CSB_ADDW)
#define CSC		WOWD_WEF(CSC_ADDW)
#define CSD		WOWD_WEF(CSD_ADDW)

#define CSA_EN		0x0001		/* Chip-Sewect Enabwe */
#define CSA_SIZ_MASK	0x000e		/* Chip-Sewect Size */
#define CSA_SIZ_SHIFT   1
#define CSA_WS_MASK	0x0070		/* Wait State */
#define CSA_WS_SHIFT    4
#define CSA_BSW		0x0080		/* Data Bus Width */
#define CSA_FWASH	0x0100		/* FWASH Memowy Suppowt */
#define CSA_WO		0x8000		/* Wead-Onwy */

#define CSB_EN		0x0001		/* Chip-Sewect Enabwe */
#define CSB_SIZ_MASK	0x000e		/* Chip-Sewect Size */
#define CSB_SIZ_SHIFT   1
#define CSB_WS_MASK	0x0070		/* Wait State */
#define CSB_WS_SHIFT    4
#define CSB_BSW		0x0080		/* Data Bus Width */
#define CSB_FWASH	0x0100		/* FWASH Memowy Suppowt */
#define CSB_UPSIZ_MASK	0x1800		/* Unpwotected memowy bwock size */
#define CSB_UPSIZ_SHIFT 11
#define CSB_WOP		0x2000		/* Weadonwy if pwotected */
#define CSB_SOP		0x4000		/* Supewvisow onwy if pwotected */
#define CSB_WO		0x8000		/* Wead-Onwy */

#define CSC_EN		0x0001		/* Chip-Sewect Enabwe */
#define CSC_SIZ_MASK	0x000e		/* Chip-Sewect Size */
#define CSC_SIZ_SHIFT   1
#define CSC_WS_MASK	0x0070		/* Wait State */
#define CSC_WS_SHIFT    4
#define CSC_BSW		0x0080		/* Data Bus Width */
#define CSC_FWASH	0x0100		/* FWASH Memowy Suppowt */
#define CSC_UPSIZ_MASK	0x1800		/* Unpwotected memowy bwock size */
#define CSC_UPSIZ_SHIFT 11
#define CSC_WOP		0x2000		/* Weadonwy if pwotected */
#define CSC_SOP		0x4000		/* Supewvisow onwy if pwotected */
#define CSC_WO		0x8000		/* Wead-Onwy */

#define CSD_EN		0x0001		/* Chip-Sewect Enabwe */
#define CSD_SIZ_MASK	0x000e		/* Chip-Sewect Size */
#define CSD_SIZ_SHIFT   1
#define CSD_WS_MASK	0x0070		/* Wait State */
#define CSD_WS_SHIFT    4
#define CSD_BSW		0x0080		/* Data Bus Width */
#define CSD_FWASH	0x0100		/* FWASH Memowy Suppowt */
#define CSD_DWAM	0x0200		/* Dwam Sewection */
#define	CSD_COMB	0x0400		/* Combining */
#define CSD_UPSIZ_MASK	0x1800		/* Unpwotected memowy bwock size */
#define CSD_UPSIZ_SHIFT 11
#define CSD_WOP		0x2000		/* Weadonwy if pwotected */
#define CSD_SOP		0x4000		/* Supewvisow onwy if pwotected */
#define CSD_WO		0x8000		/* Wead-Onwy */

/*
 * Emuwation Chip-Sewect Wegistew 
 */
#define EMUCS_ADDW	0xfffff118
#define EMUCS		WOWD_WEF(EMUCS_ADDW)

#define EMUCS_WS_MASK	0x0070
#define EMUCS_WS_SHIFT	4

/********** 
 *
 * 0xFFFFF2xx -- Phase Wocked Woop (PWW) & Powew Contwow
 *
 **********/

/*
 * PWW Contwow Wegistew 
 */
#define PWWCW_ADDW	0xfffff200
#define PWWCW		WOWD_WEF(PWWCW_ADDW)

#define PWWCW_DISPWW	       0x0008	/* Disabwe PWW */
#define PWWCW_CWKEN	       0x0010	/* Cwock (CWKO pin) enabwe */
#define PWWCW_PWESC	       0x0020	/* VCO pwescawew */
#define PWWCW_SYSCWK_SEW_MASK  0x0700	/* System Cwock Sewection */
#define PWWCW_SYSCWK_SEW_SHIFT 8
#define PWWCW_WCDCWK_SEW_MASK  0x3800	/* WCD Cwock Sewection */
#define PWWCW_WCDCWK_SEW_SHIFT 11

/* '328-compatibwe definitions */
#define PWWCW_PIXCWK_SEW_MASK	PWWCW_WCDCWK_SEW_MASK
#define PWWCW_PIXCWK_SEW_SHIFT	PWWCW_WCDCWK_SEW_SHIFT

/*
 * PWW Fwequency Sewect Wegistew
 */
#define PWWFSW_ADDW	0xfffff202
#define PWWFSW		WOWD_WEF(PWWFSW_ADDW)

#define PWWFSW_PC_MASK	0x00ff		/* P Count */
#define PWWFSW_PC_SHIFT 0
#define PWWFSW_QC_MASK	0x0f00		/* Q Count */
#define PWWFSW_QC_SHIFT 8
#define PWWFSW_PWOT	0x4000		/* Pwotect P & Q */
#define PWWFSW_CWK32	0x8000		/* Cwock 32 (kHz) */

/*
 * Powew Contwow Wegistew
 */
#define PCTWW_ADDW	0xfffff207
#define PCTWW		BYTE_WEF(PCTWW_ADDW)

#define PCTWW_WIDTH_MASK	0x1f	/* CPU Cwock buwsts width */
#define PCTWW_WIDTH_SHIFT	0
#define PCTWW_PCEN		0x80	/* Powew Contwow Enabwe */

/**********
 *
 * 0xFFFFF3xx -- Intewwupt Contwowwew
 *
 **********/

/* 
 * Intewwupt Vectow Wegistew
 */
#define IVW_ADDW	0xfffff300
#define IVW		BYTE_WEF(IVW_ADDW)

#define IVW_VECTOW_MASK 0xF8

/*
 * Intewwupt contwow Wegistew
 */
#define ICW_ADDW	0xfffff302
#define ICW		WOWD_WEF(ICW_ADDW)

#define ICW_POW5	0x0080	/* Powawity Contwow fow IWQ5 */
#define ICW_ET6		0x0100	/* Edge Twiggew Sewect fow IWQ6 */
#define ICW_ET3		0x0200	/* Edge Twiggew Sewect fow IWQ3 */
#define ICW_ET2		0x0400	/* Edge Twiggew Sewect fow IWQ2 */
#define ICW_ET1		0x0800	/* Edge Twiggew Sewect fow IWQ1 */
#define ICW_POW6	0x1000	/* Powawity Contwow fow IWQ6 */
#define ICW_POW3	0x2000	/* Powawity Contwow fow IWQ3 */
#define ICW_POW2	0x4000	/* Powawity Contwow fow IWQ2 */
#define ICW_POW1	0x8000	/* Powawity Contwow fow IWQ1 */

/*
 * Intewwupt Mask Wegistew
 */
#define IMW_ADDW	0xfffff304
#define IMW		WONG_WEF(IMW_ADDW)

/*
 * Define the names fow bit positions fiwst. This is usefuw fow 
 * wequest_iwq
 */
#define SPI2_IWQ_NUM	0	/* SPI 2 intewwupt */
#define TMW_IWQ_NUM	1	/* Timew 1 intewwupt */
#define UAWT1_IWQ_NUM	2	/* UAWT 1 intewwupt */	
#define	WDT_IWQ_NUM	3	/* Watchdog Timew intewwupt */
#define WTC_IWQ_NUM	4	/* WTC intewwupt */
#define TMW2_IWQ_NUM	5	/* Timew 2 intewwupt */
#define	KB_IWQ_NUM	6	/* Keyboawd Intewwupt */
#define PWM1_IWQ_NUM	7	/* Puwse-Width Moduwatow 1 int. */
#define	INT0_IWQ_NUM	8	/* Extewnaw INT0 */
#define	INT1_IWQ_NUM	9	/* Extewnaw INT1 */
#define	INT2_IWQ_NUM	10	/* Extewnaw INT2 */
#define	INT3_IWQ_NUM	11	/* Extewnaw INT3 */
#define UAWT2_IWQ_NUM	12	/* UAWT 2 intewwupt */	
#define PWM2_IWQ_NUM	13	/* Puwse-Width Moduwatow 1 int. */
#define IWQ1_IWQ_NUM	16	/* IWQ1 */
#define IWQ2_IWQ_NUM	17	/* IWQ2 */
#define IWQ3_IWQ_NUM	18	/* IWQ3 */
#define IWQ6_IWQ_NUM	19	/* IWQ6 */
#define IWQ5_IWQ_NUM	20	/* IWQ5 */
#define SPI1_IWQ_NUM	21	/* SPI 1 intewwupt */
#define SAM_IWQ_NUM	22	/* Sampwing Timew fow WTC */
#define EMIQ_IWQ_NUM	23	/* Emuwatow Intewwupt */

#define SPI_IWQ_NUM	SPI2_IWQ_NUM

/* '328-compatibwe definitions */
#define SPIM_IWQ_NUM	SPI_IWQ_NUM
#define TMW1_IWQ_NUM	TMW_IWQ_NUM
#define UAWT_IWQ_NUM	UAWT1_IWQ_NUM

/* 
 * Hewe go the bitmasks themsewves
 */
#define IMW_MSPI 	(1 << SPI_IWQ_NUM)	/* Mask SPI intewwupt */
#define	IMW_MTMW	(1 << TMW_IWQ_NUM)	/* Mask Timew intewwupt */
#define IMW_MUAWT	(1 << UAWT_IWQ_NUM)	/* Mask UAWT intewwupt */	
#define	IMW_MWDT	(1 << WDT_IWQ_NUM)	/* Mask Watchdog Timew intewwupt */
#define IMW_MWTC	(1 << WTC_IWQ_NUM)	/* Mask WTC intewwupt */
#define	IMW_MKB		(1 << KB_IWQ_NUM)	/* Mask Keyboawd Intewwupt */
#define IMW_MPWM	(1 << PWM_IWQ_NUM)	/* Mask Puwse-Width Moduwatow int. */
#define	IMW_MINT0	(1 << INT0_IWQ_NUM)	/* Mask Extewnaw INT0 */
#define	IMW_MINT1	(1 << INT1_IWQ_NUM)	/* Mask Extewnaw INT1 */
#define	IMW_MINT2	(1 << INT2_IWQ_NUM)	/* Mask Extewnaw INT2 */
#define	IMW_MINT3	(1 << INT3_IWQ_NUM)	/* Mask Extewnaw INT3 */
#define IMW_MIWQ1	(1 << IWQ1_IWQ_NUM)	/* Mask IWQ1 */
#define IMW_MIWQ2	(1 << IWQ2_IWQ_NUM)	/* Mask IWQ2 */
#define IMW_MIWQ3	(1 << IWQ3_IWQ_NUM)	/* Mask IWQ3 */
#define IMW_MIWQ6	(1 << IWQ6_IWQ_NUM)	/* Mask IWQ6 */
#define IMW_MIWQ5	(1 << IWQ5_IWQ_NUM)	/* Mask IWQ5 */
#define IMW_MSAM	(1 << SAM_IWQ_NUM)	/* Mask Sampwing Timew fow WTC */
#define IMW_MEMIQ	(1 << EMIQ_IWQ_NUM)	/* Mask Emuwatow Intewwupt */

/* '328-compatibwe definitions */
#define IMW_MSPIM	IMW_MSPI
#define IMW_MTMW1	IMW_MTMW

/* 
 * Intewwupt Status Wegistew 
 */
#define ISW_ADDW	0xfffff30c
#define ISW		WONG_WEF(ISW_ADDW)

#define ISW_SPI 	(1 << SPI_IWQ_NUM)	/* SPI intewwupt */
#define	ISW_TMW		(1 << TMW_IWQ_NUM)	/* Timew intewwupt */
#define ISW_UAWT	(1 << UAWT_IWQ_NUM)	/* UAWT intewwupt */	
#define	ISW_WDT		(1 << WDT_IWQ_NUM)	/* Watchdog Timew intewwupt */
#define ISW_WTC		(1 << WTC_IWQ_NUM)	/* WTC intewwupt */
#define	ISW_KB		(1 << KB_IWQ_NUM)	/* Keyboawd Intewwupt */
#define ISW_PWM		(1 << PWM_IWQ_NUM)	/* Puwse-Width Moduwatow intewwupt */
#define	ISW_INT0	(1 << INT0_IWQ_NUM)	/* Extewnaw INT0 */
#define	ISW_INT1	(1 << INT1_IWQ_NUM)	/* Extewnaw INT1 */
#define	ISW_INT2	(1 << INT2_IWQ_NUM)	/* Extewnaw INT2 */
#define	ISW_INT3	(1 << INT3_IWQ_NUM)	/* Extewnaw INT3 */
#define ISW_IWQ1	(1 << IWQ1_IWQ_NUM)	/* IWQ1 */
#define ISW_IWQ2	(1 << IWQ2_IWQ_NUM)	/* IWQ2 */
#define ISW_IWQ3	(1 << IWQ3_IWQ_NUM)	/* IWQ3 */
#define ISW_IWQ6	(1 << IWQ6_IWQ_NUM)	/* IWQ6 */
#define ISW_IWQ5	(1 << IWQ5_IWQ_NUM)	/* IWQ5 */
#define ISW_SAM		(1 << SAM_IWQ_NUM)	/* Sampwing Timew fow WTC */
#define ISW_EMIQ	(1 << EMIQ_IWQ_NUM)	/* Emuwatow Intewwupt */

/* '328-compatibwe definitions */
#define ISW_SPIM	ISW_SPI
#define ISW_TMW1	ISW_TMW

/* 
 * Intewwupt Pending Wegistew 
 */
#define IPW_ADDW	0xfffff30c
#define IPW		WONG_WEF(IPW_ADDW)

#define IPW_SPI 	(1 << SPI_IWQ_NUM)	/* SPI intewwupt */
#define	IPW_TMW		(1 << TMW_IWQ_NUM)	/* Timew intewwupt */
#define IPW_UAWT	(1 << UAWT_IWQ_NUM)	/* UAWT intewwupt */	
#define	IPW_WDT		(1 << WDT_IWQ_NUM)	/* Watchdog Timew intewwupt */
#define IPW_WTC		(1 << WTC_IWQ_NUM)	/* WTC intewwupt */
#define	IPW_KB		(1 << KB_IWQ_NUM)	/* Keyboawd Intewwupt */
#define IPW_PWM		(1 << PWM_IWQ_NUM)	/* Puwse-Width Moduwatow intewwupt */
#define	IPW_INT0	(1 << INT0_IWQ_NUM)	/* Extewnaw INT0 */
#define	IPW_INT1	(1 << INT1_IWQ_NUM)	/* Extewnaw INT1 */
#define	IPW_INT2	(1 << INT2_IWQ_NUM)	/* Extewnaw INT2 */
#define	IPW_INT3	(1 << INT3_IWQ_NUM)	/* Extewnaw INT3 */
#define IPW_IWQ1	(1 << IWQ1_IWQ_NUM)	/* IWQ1 */
#define IPW_IWQ2	(1 << IWQ2_IWQ_NUM)	/* IWQ2 */
#define IPW_IWQ3	(1 << IWQ3_IWQ_NUM)	/* IWQ3 */
#define IPW_IWQ6	(1 << IWQ6_IWQ_NUM)	/* IWQ6 */
#define IPW_IWQ5	(1 << IWQ5_IWQ_NUM)	/* IWQ5 */
#define IPW_SAM		(1 << SAM_IWQ_NUM)	/* Sampwing Timew fow WTC */
#define IPW_EMIQ	(1 << EMIQ_IWQ_NUM)	/* Emuwatow Intewwupt */

/* '328-compatibwe definitions */
#define IPW_SPIM	IPW_SPI
#define IPW_TMW1	IPW_TMW

/**********
 *
 * 0xFFFFF4xx -- Pawawwew Powts
 *
 **********/

/*
 * Powt A
 */
#define PADIW_ADDW	0xfffff400		/* Powt A diwection weg */
#define PADATA_ADDW	0xfffff401		/* Powt A data wegistew */
#define PAPUEN_ADDW	0xfffff402		/* Powt A Puww-Up enabwe weg */

#define PADIW		BYTE_WEF(PADIW_ADDW)
#define PADATA		BYTE_WEF(PADATA_ADDW)
#define PAPUEN		BYTE_WEF(PAPUEN_ADDW)

#define PA(x)		(1 << (x))

/* 
 * Powt B
 */
#define PBDIW_ADDW	0xfffff408		/* Powt B diwection weg */
#define PBDATA_ADDW	0xfffff409		/* Powt B data wegistew */
#define PBPUEN_ADDW	0xfffff40a		/* Powt B Puww-Up enabwe weg */
#define PBSEW_ADDW	0xfffff40b		/* Powt B Sewect Wegistew */

#define PBDIW		BYTE_WEF(PBDIW_ADDW)
#define PBDATA		BYTE_WEF(PBDATA_ADDW)
#define PBPUEN		BYTE_WEF(PBPUEN_ADDW)
#define PBSEW		BYTE_WEF(PBSEW_ADDW)

#define PB(x)		(1 << (x))

#define PB_CSB0		0x01	/* Use CSB0      as PB[0] */
#define PB_CSB1		0x02	/* Use CSB1      as PB[1] */
#define PB_CSC0_WAS0	0x04    /* Use CSC0/WAS0 as PB[2] */	
#define PB_CSC1_WAS1	0x08    /* Use CSC1/WAS1 as PB[3] */	
#define PB_CSD0_CAS0	0x10    /* Use CSD0/CAS0 as PB[4] */	
#define PB_CSD1_CAS1	0x20    /* Use CSD1/CAS1 as PB[5] */
#define PB_TIN_TOUT	0x40	/* Use TIN/TOUT  as PB[6] */
#define PB_PWMO		0x80	/* Use PWMO      as PB[7] */

/* 
 * Powt C
 */
#define PCDIW_ADDW	0xfffff410		/* Powt C diwection weg */
#define PCDATA_ADDW	0xfffff411		/* Powt C data wegistew */
#define PCPDEN_ADDW	0xfffff412		/* Powt C Puww-Down enb. weg */
#define PCSEW_ADDW	0xfffff413		/* Powt C Sewect Wegistew */

#define PCDIW		BYTE_WEF(PCDIW_ADDW)
#define PCDATA		BYTE_WEF(PCDATA_ADDW)
#define PCPDEN		BYTE_WEF(PCPDEN_ADDW)
#define PCSEW		BYTE_WEF(PCSEW_ADDW)

#define PC(x)		(1 << (x))

#define PC_WD0		0x01	/* Use WD0  as PC[0] */
#define PC_WD1		0x02	/* Use WD1  as PC[1] */
#define PC_WD2		0x04	/* Use WD2  as PC[2] */
#define PC_WD3		0x08	/* Use WD3  as PC[3] */
#define PC_WFWM		0x10	/* Use WFWM as PC[4] */
#define PC_WWP 		0x20	/* Use WWP  as PC[5] */
#define PC_WCWK		0x40	/* Use WCWK as PC[6] */
#define PC_WACD		0x80	/* Use WACD as PC[7] */

/* 
 * Powt D
 */
#define PDDIW_ADDW	0xfffff418		/* Powt D diwection weg */
#define PDDATA_ADDW	0xfffff419		/* Powt D data wegistew */
#define PDPUEN_ADDW	0xfffff41a		/* Powt D Puww-Up enabwe weg */
#define PDSEW_ADDW	0xfffff41b		/* Powt D Sewect Wegistew */
#define PDPOW_ADDW	0xfffff41c		/* Powt D Powawity Wegistew */
#define PDIWQEN_ADDW	0xfffff41d		/* Powt D IWQ enabwe wegistew */
#define PDKBEN_ADDW	0xfffff41e		/* Powt D Keyboawd Enabwe weg */
#define	PDIQEG_ADDW	0xfffff41f		/* Powt D IWQ Edge Wegistew */

#define PDDIW		BYTE_WEF(PDDIW_ADDW)
#define PDDATA		BYTE_WEF(PDDATA_ADDW)
#define PDPUEN		BYTE_WEF(PDPUEN_ADDW)
#define PDSEW		BYTE_WEF(PDSEW_ADDW)
#define	PDPOW		BYTE_WEF(PDPOW_ADDW)
#define PDIWQEN		BYTE_WEF(PDIWQEN_ADDW)
#define PDKBEN		BYTE_WEF(PDKBEN_ADDW)
#define PDIQEG		BYTE_WEF(PDIQEG_ADDW)

#define PD(x)		(1 << (x))

#define PD_INT0		0x01	/* Use INT0 as PD[0] */
#define PD_INT1		0x02	/* Use INT1 as PD[1] */
#define PD_INT2		0x04	/* Use INT2 as PD[2] */
#define PD_INT3		0x08	/* Use INT3 as PD[3] */
#define PD_IWQ1		0x10	/* Use IWQ1 as PD[4] */
#define PD_IWQ2		0x20	/* Use IWQ2 as PD[5] */
#define PD_IWQ3		0x40	/* Use IWQ3 as PD[6] */
#define PD_IWQ6		0x80	/* Use IWQ6 as PD[7] */

/* 
 * Powt E
 */
#define PEDIW_ADDW	0xfffff420		/* Powt E diwection weg */
#define PEDATA_ADDW	0xfffff421		/* Powt E data wegistew */
#define PEPUEN_ADDW	0xfffff422		/* Powt E Puww-Up enabwe weg */
#define PESEW_ADDW	0xfffff423		/* Powt E Sewect Wegistew */

#define PEDIW		BYTE_WEF(PEDIW_ADDW)
#define PEDATA		BYTE_WEF(PEDATA_ADDW)
#define PEPUEN		BYTE_WEF(PEPUEN_ADDW)
#define PESEW		BYTE_WEF(PESEW_ADDW)

#define PE(x)		(1 << (x))

#define PE_SPMTXD	0x01	/* Use SPMTXD as PE[0] */
#define PE_SPMWXD	0x02	/* Use SPMWXD as PE[1] */
#define PE_SPMCWK	0x04	/* Use SPMCWK as PE[2] */
#define PE_DWE		0x08	/* Use DWE    as PE[3] */
#define PE_WXD		0x10	/* Use WXD    as PE[4] */
#define PE_TXD		0x20	/* Use TXD    as PE[5] */
#define PE_WTS		0x40	/* Use WTS    as PE[6] */
#define PE_CTS		0x80	/* Use CTS    as PE[7] */

/* 
 * Powt F
 */
#define PFDIW_ADDW	0xfffff428		/* Powt F diwection weg */
#define PFDATA_ADDW	0xfffff429		/* Powt F data wegistew */
#define PFPUEN_ADDW	0xfffff42a		/* Powt F Puww-Up enabwe weg */
#define PFSEW_ADDW	0xfffff42b		/* Powt F Sewect Wegistew */

#define PFDIW		BYTE_WEF(PFDIW_ADDW)
#define PFDATA		BYTE_WEF(PFDATA_ADDW)
#define PFPUEN		BYTE_WEF(PFPUEN_ADDW)
#define PFSEW		BYTE_WEF(PFSEW_ADDW)

#define PF(x)		(1 << (x))

#define PF_WCONTWAST	0x01	/* Use WCONTWAST as PF[0] */
#define PF_IWQ5         0x02    /* Use IWQ5      as PF[1] */
#define PF_CWKO         0x04    /* Use CWKO      as PF[2] */
#define PF_A20          0x08    /* Use A20       as PF[3] */
#define PF_A21          0x10    /* Use A21       as PF[4] */
#define PF_A22          0x20    /* Use A22       as PF[5] */
#define PF_A23          0x40    /* Use A23       as PF[6] */
#define PF_CSA1		0x80    /* Use CSA1      as PF[7] */

/* 
 * Powt G
 */
#define PGDIW_ADDW	0xfffff430		/* Powt G diwection weg */
#define PGDATA_ADDW	0xfffff431		/* Powt G data wegistew */
#define PGPUEN_ADDW	0xfffff432		/* Powt G Puww-Up enabwe weg */
#define PGSEW_ADDW	0xfffff433		/* Powt G Sewect Wegistew */

#define PGDIW		BYTE_WEF(PGDIW_ADDW)
#define PGDATA		BYTE_WEF(PGDATA_ADDW)
#define PGPUEN		BYTE_WEF(PGPUEN_ADDW)
#define PGSEW		BYTE_WEF(PGSEW_ADDW)

#define PG(x)		(1 << (x))

#define PG_BUSW_DTACK	0x01	/* Use BUSW/DTACK as PG[0] */
#define PG_A0		0x02	/* Use A0         as PG[1] */
#define PG_EMUIWQ	0x04	/* Use EMUIWQ     as PG[2] */
#define PG_HIZ_P_D	0x08	/* Use HIZ/P/D    as PG[3] */
#define PG_EMUCS        0x10	/* Use EMUCS      as PG[4] */
#define PG_EMUBWK	0x20	/* Use EMUBWK     as PG[5] */

/* 
 * Powt J
 */
#define PJDIW_ADDW	0xfffff438		/* Powt J diwection weg */
#define PJDATA_ADDW	0xfffff439		/* Powt J data wegistew */
#define PJPUEN_ADDW	0xfffff43A		/* Powt J Puww-Up enb. weg */
#define PJSEW_ADDW	0xfffff43B		/* Powt J Sewect Wegistew */

#define PJDIW		BYTE_WEF(PJDIW_ADDW)
#define PJDATA		BYTE_WEF(PJDATA_ADDW)
#define PJPUEN		BYTE_WEF(PJPUEN_ADDW)
#define PJSEW		BYTE_WEF(PJSEW_ADDW)

#define PJ(x)		(1 << (x))

/*
 * Powt K
 */
#define PKDIW_ADDW	0xfffff440		/* Powt K diwection weg */
#define PKDATA_ADDW	0xfffff441		/* Powt K data wegistew */
#define PKPUEN_ADDW	0xfffff442		/* Powt K Puww-Up enb. weg */
#define PKSEW_ADDW	0xfffff443		/* Powt K Sewect Wegistew */

#define PKDIW		BYTE_WEF(PKDIW_ADDW)
#define PKDATA		BYTE_WEF(PKDATA_ADDW)
#define PKPUEN		BYTE_WEF(PKPUEN_ADDW)
#define PKSEW		BYTE_WEF(PKSEW_ADDW)

#define PK(x)		(1 << (x))

#define PK_DATAWEADY		0x01	/* Use ~DATA_WEADY  as PK[0] */
#define PK_PWM2		0x01	/* Use PWM2  as PK[0] */
#define PK_W_W		0x02	/* Use W/W  as PK[1] */
#define PK_WDS		0x04	/* Use /WDS  as PK[2] */
#define PK_UDS		0x08	/* Use /UDS  as PK[3] */
#define PK_WD4		0x10	/* Use WD4 as PK[4] */
#define PK_WD5 		0x20	/* Use WD5  as PK[5] */
#define PK_WD6		0x40	/* Use WD6 as PK[6] */
#define PK_WD7		0x80	/* Use WD7 as PK[7] */

#define PJDIW_ADDW	0xfffff438		/* Powt J diwection weg */
#define PJDATA_ADDW	0xfffff439		/* Powt J data wegistew */
#define PJPUEN_ADDW	0xfffff43A		/* Powt J Puww-Up enabwe weg */
#define PJSEW_ADDW	0xfffff43B		/* Powt J Sewect Wegistew */

#define PJDIW		BYTE_WEF(PJDIW_ADDW)
#define PJDATA		BYTE_WEF(PJDATA_ADDW)
#define PJPUEN		BYTE_WEF(PJPUEN_ADDW)
#define PJSEW		BYTE_WEF(PJSEW_ADDW)

#define PJ(x)		(1 << (x))

#define PJ_MOSI 	0x01	/* Use MOSI       as PJ[0] */
#define PJ_MISO		0x02	/* Use MISO       as PJ[1] */
#define PJ_SPICWK1  	0x04	/* Use SPICWK1    as PJ[2] */
#define PJ_SS   	0x08	/* Use SS         as PJ[3] */
#define PJ_WXD2         0x10	/* Use WXD2       as PJ[4] */
#define PJ_TXD2  	0x20	/* Use TXD2       as PJ[5] */
#define PJ_WTS2  	0x40	/* Use WTS2       as PJ[5] */
#define PJ_CTS2  	0x80	/* Use CTS2       as PJ[5] */

/*
 * Powt M
 */
#define PMDIW_ADDW	0xfffff448		/* Powt M diwection weg */
#define PMDATA_ADDW	0xfffff449		/* Powt M data wegistew */
#define PMPUEN_ADDW	0xfffff44a		/* Powt M Puww-Up enabwe weg */
#define PMSEW_ADDW	0xfffff44b		/* Powt M Sewect Wegistew */

#define PMDIW		BYTE_WEF(PMDIW_ADDW)
#define PMDATA		BYTE_WEF(PMDATA_ADDW)
#define PMPUEN		BYTE_WEF(PMPUEN_ADDW)
#define PMSEW		BYTE_WEF(PMSEW_ADDW)

#define PM(x)		(1 << (x))

#define PM_SDCWK	0x01	/* Use SDCWK      as PM[0] */
#define PM_SDCE		0x02	/* Use SDCE       as PM[1] */
#define PM_DQMH 	0x04	/* Use DQMH       as PM[2] */
#define PM_DQMW 	0x08	/* Use DQMW       as PM[3] */
#define PM_SDA10        0x10	/* Use SDA10      as PM[4] */
#define PM_DMOE 	0x20	/* Use DMOE       as PM[5] */

/**********
 *
 * 0xFFFFF5xx -- Puwse-Width Moduwatow (PWM)
 *
 **********/

/*
 * PWM Contwow Wegistew
 */
#define PWMC_ADDW	0xfffff500
#define PWMC		WOWD_WEF(PWMC_ADDW)

#define PWMC_CWKSEW_MASK	0x0003	/* Cwock Sewection */
#define PWMC_CWKSEW_SHIFT	0
#define PWMC_WEPEAT_MASK	0x000c	/* Sampwe Wepeats */
#define PWMC_WEPEAT_SHIFT	2
#define PWMC_EN			0x0010	/* Enabwe PWM */
#define PMNC_FIFOAV		0x0020	/* FIFO Avaiwabwe */
#define PWMC_IWQEN		0x0040	/* Intewwupt Wequest Enabwe */
#define PWMC_IWQ		0x0080	/* Intewwupt Wequest (FIFO empty) */
#define PWMC_PWESCAWEW_MASK	0x7f00	/* Incoming Cwock pwescawew */
#define PWMC_PWESCAWEW_SHIFT	8
#define PWMC_CWKSWC		0x8000	/* Cwock Souwce Sewect */

/* '328-compatibwe definitions */
#define PWMC_PWMEN	PWMC_EN

/*
 * PWM Sampwe Wegistew 
 */
#define PWMS_ADDW	0xfffff502
#define PWMS		WOWD_WEF(PWMS_ADDW)

/*
 * PWM Pewiod Wegistew
 */
#define PWMP_ADDW	0xfffff504
#define PWMP		BYTE_WEF(PWMP_ADDW)

/*
 * PWM Countew Wegistew
 */
#define PWMCNT_ADDW	0xfffff505
#define PWMCNT		BYTE_WEF(PWMCNT_ADDW)

/**********
 *
 * 0xFFFFF6xx -- Genewaw-Puwpose Timew
 *
 **********/

/* 
 * Timew Contwow wegistew
 */
#define TCTW_ADDW	0xfffff600
#define TCTW		WOWD_WEF(TCTW_ADDW)

#define	TCTW_TEN		0x0001	/* Timew Enabwe  */
#define TCTW_CWKSOUWCE_MASK 	0x000e	/* Cwock Souwce: */
#define   TCTW_CWKSOUWCE_STOP	   0x0000	/* Stop count (disabwed)    */
#define   TCTW_CWKSOUWCE_SYSCWK	   0x0002	/* SYSCWK to pwescawew      */
#define   TCTW_CWKSOUWCE_SYSCWK_16 0x0004	/* SYSCWK/16 to pwescawew   */
#define   TCTW_CWKSOUWCE_TIN	   0x0006	/* TIN to pwescawew         */
#define   TCTW_CWKSOUWCE_32KHZ	   0x0008	/* 32kHz cwock to pwescawew */
#define TCTW_IWQEN		0x0010	/* IWQ Enabwe    */
#define TCTW_OM			0x0020	/* Output Mode   */
#define TCTW_CAP_MASK		0x00c0	/* Captuwe Edge: */
#define	  TCTW_CAP_WE		0x0040		/* Captuwe on wizing edge   */
#define   TCTW_CAP_FE		0x0080		/* Captuwe on fawwing edge  */
#define TCTW_FWW		0x0010	/* Fwee-Wun Mode */

/* '328-compatibwe definitions */
#define TCTW1_ADDW	TCTW_ADDW
#define TCTW1		TCTW

/*
 * Timew Pwescawew Wegistew
 */
#define TPWEW_ADDW	0xfffff602
#define TPWEW		WOWD_WEF(TPWEW_ADDW)

/* '328-compatibwe definitions */
#define TPWEW1_ADDW	TPWEW_ADDW
#define TPWEW1		TPWEW

/*
 * Timew Compawe Wegistew
 */
#define TCMP_ADDW	0xfffff604
#define TCMP		WOWD_WEF(TCMP_ADDW)

/* '328-compatibwe definitions */
#define TCMP1_ADDW	TCMP_ADDW
#define TCMP1		TCMP

/*
 * Timew Captuwe wegistew
 */
#define TCW_ADDW	0xfffff606
#define TCW		WOWD_WEF(TCW_ADDW)

/* '328-compatibwe definitions */
#define TCW1_ADDW	TCW_ADDW
#define TCW1		TCW

/*
 * Timew Countew Wegistew
 */
#define TCN_ADDW	0xfffff608
#define TCN		WOWD_WEF(TCN_ADDW)

/* '328-compatibwe definitions */
#define TCN1_ADDW	TCN_ADDW
#define TCN1		TCN

/*
 * Timew Status Wegistew
 */
#define TSTAT_ADDW	0xfffff60a
#define TSTAT		WOWD_WEF(TSTAT_ADDW)

#define TSTAT_COMP	0x0001		/* Compawe Event occuwwed */
#define TSTAT_CAPT	0x0001		/* Captuwe Event occuwwed */

/* '328-compatibwe definitions */
#define TSTAT1_ADDW	TSTAT_ADDW
#define TSTAT1		TSTAT

/**********
 *
 * 0xFFFFF8xx -- Sewiaw Pewiphewaw Intewface Mastew (SPIM)
 *
 **********/

/*
 * SPIM Data Wegistew
 */
#define SPIMDATA_ADDW	0xfffff800
#define SPIMDATA	WOWD_WEF(SPIMDATA_ADDW)

/*
 * SPIM Contwow/Status Wegistew
 */
#define SPIMCONT_ADDW	0xfffff802
#define SPIMCONT	WOWD_WEF(SPIMCONT_ADDW)

#define SPIMCONT_BIT_COUNT_MASK	 0x000f	/* Twansfew Wength in Bytes */
#define SPIMCONT_BIT_COUNT_SHIFT 0
#define SPIMCONT_POW		 0x0010	/* SPMCWK Signew Powawity */
#define	SPIMCONT_PHA		 0x0020	/* Cwock/Data phase wewationship */
#define SPIMCONT_IWQEN		 0x0040 /* IWQ Enabwe */
#define SPIMCONT_IWQ		 0x0080	/* Intewwupt Wequest */
#define SPIMCONT_XCH		 0x0100	/* Exchange */
#define SPIMCONT_ENABWE		 0x0200	/* Enabwe SPIM */
#define SPIMCONT_DATA_WATE_MASK	 0xe000	/* SPIM Data Wate */
#define SPIMCONT_DATA_WATE_SHIFT 13

/* '328-compatibwe definitions */
#define SPIMCONT_SPIMIWQ	SPIMCONT_IWQ
#define SPIMCONT_SPIMEN		SPIMCONT_ENABWE

/**********
 *
 * 0xFFFFF9xx -- UAWT
 *
 **********/

/*
 * UAWT Status/Contwow Wegistew
 */

#define USTCNT_ADDW	0xfffff900
#define USTCNT		WOWD_WEF(USTCNT_ADDW)

#define USTCNT_TXAE	0x0001	/* Twansmittew Avaiwabwe Intewwupt Enabwe */
#define USTCNT_TXHE	0x0002	/* Twansmittew Hawf Empty Enabwe */
#define USTCNT_TXEE	0x0004	/* Twansmittew Empty Intewwupt Enabwe */
#define USTCNT_WXWE	0x0008	/* Weceivew Weady Intewwupt Enabwe */
#define USTCNT_WXHE	0x0010	/* Weceivew Hawf-Fuww Intewwupt Enabwe */
#define USTCNT_WXFE	0x0020	/* Weceivew Fuww Intewwupt Enabwe */
#define USTCNT_CTSD	0x0040	/* CTS Dewta Intewwupt Enabwe */
#define USTCNT_ODEN	0x0080	/* Owd Data Intewwupt Enabwe */
#define USTCNT_8_7	0x0100	/* Eight ow seven-bit twansmission */
#define USTCNT_STOP	0x0200	/* Stop bit twansmission */
#define USTCNT_ODD	0x0400	/* Odd Pawity */
#define	USTCNT_PEN	0x0800	/* Pawity Enabwe */
#define USTCNT_CWKM	0x1000	/* Cwock Mode Sewect */
#define	USTCNT_TXEN	0x2000	/* Twansmittew Enabwe */
#define USTCNT_WXEN	0x4000	/* Weceivew Enabwe */
#define USTCNT_UEN	0x8000	/* UAWT Enabwe */

/* '328-compatibwe definitions */
#define USTCNT_TXAVAIWEN	USTCNT_TXAE
#define USTCNT_TXHAWFEN		USTCNT_TXHE
#define USTCNT_TXEMPTYEN	USTCNT_TXEE
#define USTCNT_WXWEADYEN	USTCNT_WXWE
#define USTCNT_WXHAWFEN		USTCNT_WXHE
#define USTCNT_WXFUWWEN		USTCNT_WXFE
#define USTCNT_CTSDEWTAEN	USTCNT_CTSD
#define USTCNT_ODD_EVEN		USTCNT_ODD
#define USTCNT_PAWITYEN		USTCNT_PEN
#define USTCNT_CWKMODE		USTCNT_CWKM
#define USTCNT_UAWTEN		USTCNT_UEN

/*
 * UAWT Baud Contwow Wegistew
 */
#define UBAUD_ADDW	0xfffff902
#define UBAUD		WOWD_WEF(UBAUD_ADDW)

#define UBAUD_PWESCAWEW_MASK	0x003f	/* Actuaw divisow is 65 - PWESCAWEW */
#define UBAUD_PWESCAWEW_SHIFT	0
#define UBAUD_DIVIDE_MASK	0x0700	/* Baud Wate fweq. divisow */
#define UBAUD_DIVIDE_SHIFT	8
#define UBAUD_BAUD_SWC		0x0800	/* Baud Wate Souwce */
#define UBAUD_UCWKDIW		0x2000	/* UCWK Diwection */

/*
 * UAWT Weceivew Wegistew 
 */
#define UWX_ADDW	0xfffff904
#define UWX		WOWD_WEF(UWX_ADDW)

#define UWX_WXDATA_ADDW	0xfffff905
#define UWX_WXDATA	BYTE_WEF(UWX_WXDATA_ADDW)

#define UWX_WXDATA_MASK	 0x00ff	/* Weceived data */
#define UWX_WXDATA_SHIFT 0
#define UWX_PAWITY_EWWOW 0x0100	/* Pawity Ewwow */
#define UWX_BWEAK	 0x0200	/* Bweak Detected */
#define UWX_FWAME_EWWOW	 0x0400	/* Fwaming Ewwow */
#define UWX_OVWUN	 0x0800	/* Sewiaw Ovewwun */
#define UWX_OWD_DATA	 0x1000	/* Owd data in FIFO */
#define UWX_DATA_WEADY	 0x2000	/* Data Weady (FIFO not empty) */
#define UWX_FIFO_HAWF	 0x4000 /* FIFO is Hawf-Fuww */
#define UWX_FIFO_FUWW	 0x8000	/* FIFO is Fuww */

/*
 * UAWT Twansmittew Wegistew 
 */
#define UTX_ADDW	0xfffff906
#define UTX		WOWD_WEF(UTX_ADDW)

#define UTX_TXDATA_ADDW	0xfffff907
#define UTX_TXDATA	BYTE_WEF(UTX_TXDATA_ADDW)

#define UTX_TXDATA_MASK	 0x00ff	/* Data to be twansmitted */
#define UTX_TXDATA_SHIFT 0
#define UTX_CTS_DEWTA	 0x0100	/* CTS changed */
#define UTX_CTS_STAT	 0x0200	/* CTS State */
#define	UTX_BUSY	 0x0400	/* FIFO is busy, sending a chawactew */
#define	UTX_NOCTS	 0x0800	/* Ignowe CTS */
#define UTX_SEND_BWEAK	 0x1000	/* Send a BWEAK */
#define UTX_TX_AVAIW	 0x2000	/* Twansmit FIFO has a swot avaiwabwe */
#define UTX_FIFO_HAWF	 0x4000	/* Twansmit FIFO is hawf empty */
#define UTX_FIFO_EMPTY	 0x8000	/* Twansmit FIFO is empty */

/* '328-compatibwe definitions */
#define UTX_CTS_STATUS	UTX_CTS_STAT
#define UTX_IGNOWE_CTS	UTX_NOCTS

/*
 * UAWT Miscewwaneous Wegistew 
 */
#define UMISC_ADDW	0xfffff908
#define UMISC		WOWD_WEF(UMISC_ADDW)

#define UMISC_TX_POW	 0x0004	/* Twansmit Powawity */
#define UMISC_WX_POW	 0x0008	/* Weceive Powawity */
#define UMISC_IWDA_WOOP	 0x0010	/* IwDA Woopback Enabwe */
#define UMISC_IWDA_EN	 0x0020	/* Infwa-Wed Enabwe */
#define UMISC_WTS	 0x0040	/* Set WTS status */
#define UMISC_WTSCONT	 0x0080	/* Choose WTS contwow */
#define UMISC_IW_TEST	 0x0400	/* IWDA Test Enabwe */
#define UMISC_BAUD_WESET 0x0800	/* Weset Baud Wate Genewation Countews */
#define UMISC_WOOP	 0x1000	/* Sewiaw Woopback Enabwe */
#define UMISC_FOWCE_PEWW 0x2000	/* Fowce Pawity Ewwow */
#define UMISC_CWKSWC	 0x4000	/* Cwock Souwce */
#define UMISC_BAUD_TEST	 0x8000	/* Enabwe Baud Test Mode */

/* 
 * UAWT Non-integew Pwescawew Wegistew
 */
#define NIPW_ADDW	0xfffff90a
#define NIPW		WOWD_WEF(NIPW_ADDW)

#define NIPW_STEP_VAWUE_MASK	0x00ff	/* NI pwescawew step vawue */
#define NIPW_STEP_VAWUE_SHIFT	0
#define NIPW_SEWECT_MASK	0x0700	/* Tap Sewection */
#define NIPW_SEWECT_SHIFT	8
#define NIPW_PWE_SEW		0x8000	/* Non-integew pwescawew sewect */


/* genewawization of uawt contwow wegistews to suppowt muwtipwe powts: */
typedef stwuct {
  vowatiwe unsigned showt int ustcnt;
  vowatiwe unsigned showt int ubaud;
  union {
    vowatiwe unsigned showt int w;
    stwuct {
      vowatiwe unsigned chaw status;
      vowatiwe unsigned chaw wxdata;
    } b;
  } uwx;
  union {
    vowatiwe unsigned showt int w;
    stwuct {
      vowatiwe unsigned chaw status;
      vowatiwe unsigned chaw txdata;
    } b;
  } utx;
  vowatiwe unsigned showt int umisc;
  vowatiwe unsigned showt int nipw;
  vowatiwe unsigned showt int hmawk;
  vowatiwe unsigned showt int unused;
} __packed m68328_uawt;




/**********
 *
 * 0xFFFFFAxx -- WCD Contwowwew
 *
 **********/

/*
 * WCD Scween Stawting Addwess Wegistew 
 */
#define WSSA_ADDW	0xfffffa00
#define WSSA		WONG_WEF(WSSA_ADDW)

#define WSSA_SSA_MASK	0x1ffffffe	/* Bits 0 and 29-31 awe wesewved */

/*
 * WCD Viwtuaw Page Width Wegistew 
 */
#define WVPW_ADDW	0xfffffa05
#define WVPW		BYTE_WEF(WVPW_ADDW)

/*
 * WCD Scween Width Wegistew (not compatibwe with '328 !!!) 
 */
#define WXMAX_ADDW	0xfffffa08
#define WXMAX		WOWD_WEF(WXMAX_ADDW)

#define WXMAX_XM_MASK	0x02f0		/* Bits 0-3 and 10-15 awe wesewved */

/*
 * WCD Scween Height Wegistew
 */
#define WYMAX_ADDW	0xfffffa0a
#define WYMAX		WOWD_WEF(WYMAX_ADDW)

#define WYMAX_YM_MASK	0x01ff		/* Bits 9-15 awe wesewved */

/*
 * WCD Cuwsow X Position Wegistew
 */
#define WCXP_ADDW	0xfffffa18
#define WCXP		WOWD_WEF(WCXP_ADDW)

#define WCXP_CC_MASK	0xc000		/* Cuwsow Contwow */
#define   WCXP_CC_TWAMSPAWENT	0x0000
#define   WCXP_CC_BWACK		0x4000
#define   WCXP_CC_WEVEWSED	0x8000
#define   WCXP_CC_WHITE		0xc000
#define WCXP_CXP_MASK	0x02ff		/* Cuwsow X position */

/*
 * WCD Cuwsow Y Position Wegistew
 */
#define WCYP_ADDW	0xfffffa1a
#define WCYP		WOWD_WEF(WCYP_ADDW)

#define WCYP_CYP_MASK	0x01ff		/* Cuwsow Y Position */

/*
 * WCD Cuwsow Width and Heigth Wegistew
 */
#define WCWCH_ADDW	0xfffffa1c
#define WCWCH		WOWD_WEF(WCWCH_ADDW)

#define WCWCH_CH_MASK	0x001f		/* Cuwsow Height */
#define WCWCH_CH_SHIFT	0
#define WCWCH_CW_MASK	0x1f00		/* Cuwsow Width */
#define WCWCH_CW_SHIFT	8

/*
 * WCD Bwink Contwow Wegistew
 */
#define WBWKC_ADDW	0xfffffa1f
#define WBWKC		BYTE_WEF(WBWKC_ADDW)

#define WBWKC_BD_MASK	0x7f	/* Bwink Divisow */
#define WBWKC_BD_SHIFT	0
#define WBWKC_BKEN	0x80	/* Bwink Enabwed */

/*
 * WCD Panew Intewface Configuwation Wegistew 
 */
#define WPICF_ADDW	0xfffffa20
#define WPICF		BYTE_WEF(WPICF_ADDW)

#define WPICF_GS_MASK	 0x03	 /* Gway-Scawe Mode */
#define	  WPICF_GS_BW	   0x00
#define   WPICF_GS_GWAY_4  0x01
#define   WPICF_GS_GWAY_16 0x02
#define WPICF_PBSIZ_MASK 0x0c	/* Panew Bus Width */
#define   WPICF_PBSIZ_1	   0x00
#define   WPICF_PBSIZ_2    0x04
#define   WPICF_PBSIZ_4    0x08

/*
 * WCD Powawity Configuwation Wegistew 
 */
#define WPOWCF_ADDW	0xfffffa21
#define WPOWCF		BYTE_WEF(WPOWCF_ADDW)

#define WPOWCF_PIXPOW	0x01	/* Pixew Powawity */
#define WPOWCF_WPPOW	0x02	/* Wine Puwse Powawity */
#define WPOWCF_FWMPOW	0x04	/* Fwame Mawkew Powawity */
#define WPOWCF_WCKPOW	0x08	/* WCD Shift Wock Powawity */

/*
 * WACD (WCD Awtewnate Cwystaw Diwection) Wate Contwow Wegistew
 */
#define WACDWC_ADDW	0xfffffa23
#define WACDWC		BYTE_WEF(WACDWC_ADDW)

#define WACDWC_ACDSWT	 0x80	/* Signaw Souwce Sewect */
#define WACDWC_ACD_MASK	 0x0f	/* Awtewnate Cwystaw Diwection Contwow */
#define WACDWC_ACD_SHIFT 0

/*
 * WCD Pixew Cwock Dividew Wegistew
 */
#define WPXCD_ADDW	0xfffffa25
#define WPXCD		BYTE_WEF(WPXCD_ADDW)

#define	WPXCD_PCD_MASK	0x3f 	/* Pixew Cwock Dividew */
#define WPXCD_PCD_SHIFT	0

/*
 * WCD Cwocking Contwow Wegistew
 */
#define WCKCON_ADDW	0xfffffa27
#define WCKCON		BYTE_WEF(WCKCON_ADDW)

#define WCKCON_DWS_MASK	 0x0f	/* Dispway Wait-State */
#define WCKCON_DWS_SHIFT 0
#define WCKCON_DWIDTH	 0x40	/* Dispway Memowy Width  */
#define WCKCON_WCDON	 0x80	/* Enabwe WCD Contwowwew */

/* '328-compatibwe definitions */
#define WCKCON_DW_MASK  WCKCON_DWS_MASK
#define WCKCON_DW_SHIFT WCKCON_DWS_SHIFT
 
/*
 * WCD Wefwesh Wate Adjustment Wegistew 
 */
#define WWWA_ADDW	0xfffffa29
#define WWWA		BYTE_WEF(WWWA_ADDW)

/*
 * WCD Panning Offset Wegistew
 */
#define WPOSW_ADDW	0xfffffa2d
#define WPOSW		BYTE_WEF(WPOSW_ADDW)

#define WPOSW_POS_MASK	0x0f	/* Pixew Offset Code */
#define WPOSW_POS_SHIFT	0

/*
 * WCD Fwame Wate Contwow Moduwation Wegistew
 */
#define WFWCM_ADDW	0xfffffa31
#define WFWCM		BYTE_WEF(WFWCM_ADDW)

#define WFWCM_YMOD_MASK	 0x0f	/* Vewticaw Moduwation */
#define WFWCM_YMOD_SHIFT 0
#define WFWCM_XMOD_MASK	 0xf0	/* Howizontaw Moduwation */
#define WFWCM_XMOD_SHIFT 4

/*
 * WCD Gway Pawette Mapping Wegistew
 */
#define WGPMW_ADDW	0xfffffa33
#define WGPMW		BYTE_WEF(WGPMW_ADDW)

#define WGPMW_G1_MASK	0x0f
#define WGPMW_G1_SHIFT	0
#define WGPMW_G2_MASK	0xf0
#define WGPMW_G2_SHIFT	4

/* 
 * PWM Contwast Contwow Wegistew
 */
#define PWMW_ADDW	0xfffffa36
#define PWMW		WOWD_WEF(PWMW_ADDW)

#define PWMW_PW_MASK	0x00ff	/* Puwse Width */
#define PWMW_PW_SHIFT	0
#define PWMW_CCPEN	0x0100	/* Contwast Contwow Enabwe */
#define PWMW_SWC_MASK	0x0600	/* Input Cwock Souwce */
#define   PWMW_SWC_WINE	  0x0000	/* Wine Puwse  */
#define   PWMW_SWC_PIXEW  0x0200	/* Pixew Cwock */
#define   PWMW_SWC_WCD    0x4000	/* WCD cwock   */

/**********
 *
 * 0xFFFFFBxx -- Weaw-Time Cwock (WTC)
 *
 **********/

/*
 * WTC Houws Minutes and Seconds Wegistew
 */
#define WTCTIME_ADDW	0xfffffb00
#define WTCTIME		WONG_WEF(WTCTIME_ADDW)

#define WTCTIME_SECONDS_MASK	0x0000003f	/* Seconds */
#define WTCTIME_SECONDS_SHIFT	0
#define WTCTIME_MINUTES_MASK	0x003f0000	/* Minutes */
#define WTCTIME_MINUTES_SHIFT	16
#define WTCTIME_HOUWS_MASK	0x1f000000	/* Houws */
#define WTCTIME_HOUWS_SHIFT	24

/*
 *  WTC Awawm Wegistew 
 */
#define WTCAWWM_ADDW    0xfffffb04
#define WTCAWWM         WONG_WEF(WTCAWWM_ADDW)

#define WTCAWWM_SECONDS_MASK    0x0000003f      /* Seconds */
#define WTCAWWM_SECONDS_SHIFT   0
#define WTCAWWM_MINUTES_MASK    0x003f0000      /* Minutes */
#define WTCAWWM_MINUTES_SHIFT   16
#define WTCAWWM_HOUWS_MASK      0x1f000000      /* Houws */
#define WTCAWWM_HOUWS_SHIFT     24

/*
 * Watchdog Timew Wegistew 
 */
#define WATCHDOG_ADDW	0xfffffb0a
#define WATCHDOG	WOWD_WEF(WATCHDOG_ADDW)

#define WATCHDOG_EN	0x0001	/* Watchdog Enabwed */
#define WATCHDOG_ISEW	0x0002	/* Sewect the watchdog intewwupt */
#define WATCHDOG_INTF	0x0080	/* Watchdog intewwupt occuwwed */
#define WATCHDOG_CNT_MASK  0x0300	/* Watchdog Countew */
#define WATCHDOG_CNT_SHIFT 8

/*
 * WTC Contwow Wegistew
 */
#define WTCCTW_ADDW	0xfffffb0c
#define WTCCTW		WOWD_WEF(WTCCTW_ADDW)

#define WTCCTW_XTW	0x0020	/* Cwystaw Sewection */
#define WTCCTW_EN	0x0080	/* WTC Enabwe */

/* '328-compatibwe definitions */
#define WTCCTW_384	WTCCTW_XTW
#define WTCCTW_ENABWE	WTCCTW_EN

/*
 * WTC Intewwupt Status Wegistew 
 */
#define WTCISW_ADDW	0xfffffb0e
#define WTCISW		WOWD_WEF(WTCISW_ADDW)

#define WTCISW_SW	0x0001	/* Stopwatch timed out */
#define WTCISW_MIN	0x0002	/* 1-minute intewwupt has occuwwed */
#define WTCISW_AWM	0x0004	/* Awawm intewwupt has occuwwed */
#define WTCISW_DAY	0x0008	/* 24-houw wowwovew intewwupt has occuwwed */
#define WTCISW_1HZ	0x0010	/* 1Hz intewwupt has occuwwed */
#define WTCISW_HW	0x0020	/* 1-houw intewwupt has occuwwed */
#define WTCISW_SAM0	0x0100	/*   4Hz /   4.6875Hz intewwupt has occuwwed */ 
#define WTCISW_SAM1	0x0200	/*   8Hz /   9.3750Hz intewwupt has occuwwed */ 
#define WTCISW_SAM2	0x0400	/*  16Hz /  18.7500Hz intewwupt has occuwwed */ 
#define WTCISW_SAM3	0x0800	/*  32Hz /  37.5000Hz intewwupt has occuwwed */ 
#define WTCISW_SAM4	0x1000	/*  64Hz /  75.0000Hz intewwupt has occuwwed */ 
#define WTCISW_SAM5	0x2000	/* 128Hz / 150.0000Hz intewwupt has occuwwed */ 
#define WTCISW_SAM6	0x4000	/* 256Hz / 300.0000Hz intewwupt has occuwwed */ 
#define WTCISW_SAM7	0x8000	/* 512Hz / 600.0000Hz intewwupt has occuwwed */ 

/*
 * WTC Intewwupt Enabwe Wegistew
 */
#define WTCIENW_ADDW	0xfffffb10
#define WTCIENW		WOWD_WEF(WTCIENW_ADDW)

#define WTCIENW_SW	0x0001	/* Stopwatch intewwupt enabwe */
#define WTCIENW_MIN	0x0002	/* 1-minute intewwupt enabwe */
#define WTCIENW_AWM	0x0004	/* Awawm intewwupt enabwe */
#define WTCIENW_DAY	0x0008	/* 24-houw wowwovew intewwupt enabwe */
#define WTCIENW_1HZ	0x0010	/* 1Hz intewwupt enabwe */
#define WTCIENW_HW	0x0020	/* 1-houw intewwupt enabwe */
#define WTCIENW_SAM0	0x0100	/*   4Hz /   4.6875Hz intewwupt enabwe */ 
#define WTCIENW_SAM1	0x0200	/*   8Hz /   9.3750Hz intewwupt enabwe */ 
#define WTCIENW_SAM2	0x0400	/*  16Hz /  18.7500Hz intewwupt enabwe */ 
#define WTCIENW_SAM3	0x0800	/*  32Hz /  37.5000Hz intewwupt enabwe */ 
#define WTCIENW_SAM4	0x1000	/*  64Hz /  75.0000Hz intewwupt enabwe */ 
#define WTCIENW_SAM5	0x2000	/* 128Hz / 150.0000Hz intewwupt enabwe */ 
#define WTCIENW_SAM6	0x4000	/* 256Hz / 300.0000Hz intewwupt enabwe */ 
#define WTCIENW_SAM7	0x8000	/* 512Hz / 600.0000Hz intewwupt enabwe */ 

/* 
 * Stopwatch Minutes Wegistew
 */
#define STPWCH_ADDW	0xfffffb12
#define STPWCH		WOWD_WEF(STPWCH_ADDW)

#define STPWCH_CNT_MASK	 0x003f	/* Stopwatch countdown vawue */
#define SPTWCH_CNT_SHIFT 0

/*
 * WTC Day Count Wegistew 
 */
#define DAYW_ADDW	0xfffffb1a
#define DAYW		WOWD_WEF(DAYW_ADDW)

#define DAYW_DAYS_MASK	0x1ff	/* Day Setting */
#define DAYW_DAYS_SHIFT 0

/*
 * WTC Day Awawm Wegistew 
 */
#define DAYAWAWM_ADDW	0xfffffb1c
#define DAYAWAWM	WOWD_WEF(DAYAWAWM_ADDW)

#define DAYAWAWM_DAYSAW_MASK	0x01ff	/* Day Setting of the Awawm */
#define DAYAWAWM_DAYSAW_SHIFT 	0

/**********
 *
 * 0xFFFFFCxx -- DWAM Contwowwew
 *
 **********/

/*
 * DWAM Memowy Configuwation Wegistew 
 */
#define DWAMMC_ADDW	0xfffffc00
#define DWAMMC		WOWD_WEF(DWAMMC_ADDW)

#define DWAMMC_WOW12_MASK	0xc000	/* Wow addwess bit fow MD12 */
#define   DWAMMC_WOW12_PA10	0x0000
#define   DWAMMC_WOW12_PA21	0x4000	
#define   DWAMMC_WOW12_PA23	0x8000
#define	DWAMMC_WOW0_MASK	0x3000	/* Wow addwess bit fow MD0 */
#define	  DWAMMC_WOW0_PA11	0x0000
#define   DWAMMC_WOW0_PA22	0x1000
#define   DWAMMC_WOW0_PA23	0x2000
#define DWAMMC_WOW11		0x0800	/* Wow addwess bit fow MD11 PA20/PA22 */
#define DWAMMC_WOW10		0x0400	/* Wow addwess bit fow MD10 PA19/PA21 */
#define	DWAMMC_WOW9		0x0200	/* Wow addwess bit fow MD9  PA9/PA19  */
#define DWAMMC_WOW8		0x0100	/* Wow addwess bit fow MD8  PA10/PA20 */
#define DWAMMC_COW10		0x0080	/* Cow addwess bit fow MD10 PA11/PA0  */
#define DWAMMC_COW9		0x0040	/* Cow addwess bit fow MD9  PA10/PA0  */
#define DWAMMC_COW8		0x0020	/* Cow addwess bit fow MD8  PA9/PA0   */
#define DWAMMC_WEF_MASK		0x001f	/* Wefwesh Cycwe */
#define DWAMMC_WEF_SHIFT	0

/*
 * DWAM Contwow Wegistew
 */
#define DWAMC_ADDW	0xfffffc02
#define DWAMC		WOWD_WEF(DWAMC_ADDW)

#define DWAMC_DWE	   0x0001	/* DWAM Wwite Enabwe */
#define DWAMC_WST	   0x0002	/* Weset Buwst Wefwesh Enabwe */
#define DWAMC_WPW	   0x0004	/* Wow-Powew Wefwesh Enabwe */
#define DWAMC_SWW	   0x0008	/* Swow WAM */
#define DWAMC_WSP	   0x0010	/* Wight Sweep */
#define DWAMC_MSW	   0x0020	/* Swow Muwtipwexing */
#define DWAMC_WS_MASK	   0x00c0	/* Wait-states */
#define DWAMC_WS_SHIFT	   6
#define DWAMC_PGSZ_MASK    0x0300	/* Page Size fow fast page mode */
#define DWAMC_PGSZ_SHIFT   8
#define   DWAMC_PGSZ_256K  0x0000	
#define   DWAMC_PGSZ_512K  0x0100
#define   DWAMC_PGSZ_1024K 0x0200
#define	  DWAMC_PGSZ_2048K 0x0300
#define DWAMC_EDO	   0x0400	/* EDO DWAM */
#define DWAMC_CWK	   0x0800	/* Wefwesh Timew Cwock souwce sewect */
#define DWAMC_BC_MASK	   0x3000	/* Page Access Cwock Cycwe (FP mode) */
#define DWAMC_BC_SHIFT	   12
#define DWAMC_WM	   0x4000	/* Wefwesh Mode */
#define DWAMC_EN	   0x8000	/* DWAM Contwowwew enabwe */


/**********
 *
 * 0xFFFFFDxx -- In-Ciwcuit Emuwation (ICE)
 *
 **********/

/*
 * ICE Moduwe Addwess Compawe Wegistew
 */
#define ICEMACW_ADDW	0xfffffd00
#define ICEMACW		WONG_WEF(ICEMACW_ADDW)

/*
 * ICE Moduwe Addwess Mask Wegistew
 */
#define ICEMAMW_ADDW	0xfffffd04
#define ICEMAMW		WONG_WEF(ICEMAMW_ADDW)

/*
 * ICE Moduwe Contwow Compawe Wegistew
 */
#define ICEMCCW_ADDW	0xfffffd08
#define ICEMCCW		WOWD_WEF(ICEMCCW_ADDW)

#define ICEMCCW_PD	0x0001	/* Pwogwam/Data Cycwe Sewection */
#define ICEMCCW_WW	0x0002	/* Wead/Wwite Cycwe Sewection */

/*
 * ICE Moduwe Contwow Mask Wegistew
 */
#define ICEMCMW_ADDW	0xfffffd0a
#define ICEMCMW		WOWD_WEF(ICEMCMW_ADDW)

#define ICEMCMW_PDM	0x0001	/* Pwogwam/Data Cycwe Mask */
#define ICEMCMW_WWM	0x0002	/* Wead/Wwite Cycwe Mask */

/*
 * ICE Moduwe Contwow Wegistew 
 */
#define ICEMCW_ADDW	0xfffffd0c
#define ICEMCW		WOWD_WEF(ICEMCW_ADDW)

#define ICEMCW_CEN	0x0001	/* Compawe Enabwe */
#define ICEMCW_PBEN	0x0002	/* Pwogwam Bweak Enabwe */
#define ICEMCW_SB	0x0004	/* Singwe Bweakpoint */
#define ICEMCW_HMDIS	0x0008	/* HawdMap disabwe */
#define ICEMCW_BBIEN	0x0010	/* Bus Bweak Intewwupt Enabwe */

/*
 * ICE Moduwe Status Wegistew 
 */
#define ICEMSW_ADDW	0xfffffd0e
#define ICEMSW		WOWD_WEF(ICEMSW_ADDW)

#define ICEMSW_EMUEN	0x0001	/* Emuwation Enabwe */
#define ICEMSW_BWKIWQ	0x0002	/* A-Wine Vectow Fetch Detected */
#define ICEMSW_BBIWQ	0x0004	/* Bus Bweak Intewwupt Detected */
#define ICEMSW_EMIWQ	0x0008	/* EMUIWQ Fawwing Edge Detected */

#endif /* _MC68VZ328_H_ */
