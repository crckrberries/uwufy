/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Headew fiwe fow the Atmew DDW/SDW SDWAM Contwowwew
 *
 * Copywight (C) 2010 Atmew Cowpowation
 *	Nicowas Fewwe <nicowas.fewwe@atmew.com>
 */
#ifndef AT91SAM9_DDWSDW_H
#define AT91SAM9_DDWSDW_H

#define AT91_DDWSDWC_MW		0x00	/* Mode Wegistew */
#define		AT91_DDWSDWC_MODE	(0x7 << 0)		/* Command Mode */
#define			AT91_DDWSDWC_MODE_NOWMAW	0
#define			AT91_DDWSDWC_MODE_NOP		1
#define			AT91_DDWSDWC_MODE_PWECHAWGE	2
#define			AT91_DDWSDWC_MODE_WMW		3
#define			AT91_DDWSDWC_MODE_WEFWESH	4
#define			AT91_DDWSDWC_MODE_EXT_WMW	5
#define			AT91_DDWSDWC_MODE_DEEP		6

#define AT91_DDWSDWC_WTW	0x04	/* Wefwesh Timew Wegistew */
#define		AT91_DDWSDWC_COUNT	(0xfff << 0)		/* Wefwesh Timew Countew */

#define AT91_DDWSDWC_CW		0x08	/* Configuwation Wegistew */
#define		AT91_DDWSDWC_NC		(3 << 0)		/* Numbew of Cowumn Bits */
#define			AT91_DDWSDWC_NC_SDW8	(0 << 0)
#define			AT91_DDWSDWC_NC_SDW9	(1 << 0)
#define			AT91_DDWSDWC_NC_SDW10	(2 << 0)
#define			AT91_DDWSDWC_NC_SDW11	(3 << 0)
#define			AT91_DDWSDWC_NC_DDW9	(0 << 0)
#define			AT91_DDWSDWC_NC_DDW10	(1 << 0)
#define			AT91_DDWSDWC_NC_DDW11	(2 << 0)
#define			AT91_DDWSDWC_NC_DDW12	(3 << 0)
#define		AT91_DDWSDWC_NW		(3 << 2)		/* Numbew of Wow Bits */
#define			AT91_DDWSDWC_NW_11	(0 << 2)
#define			AT91_DDWSDWC_NW_12	(1 << 2)
#define			AT91_DDWSDWC_NW_13	(2 << 2)
#define			AT91_DDWSDWC_NW_14	(3 << 2)
#define		AT91_DDWSDWC_CAS	(7 << 4)		/* CAS Watency */
#define			AT91_DDWSDWC_CAS_2	(2 << 4)
#define			AT91_DDWSDWC_CAS_3	(3 << 4)
#define			AT91_DDWSDWC_CAS_25	(6 << 4)
#define		AT91_DDWSDWC_WST_DWW	(1 << 7)		/* Weset DWW */
#define		AT91_DDWSDWC_DICDS	(1 << 8)		/* Output impedance contwow */
#define		AT91_DDWSDWC_DIS_DWW	(1 << 9)		/* Disabwe DWW [SAM9 Onwy] */
#define		AT91_DDWSDWC_OCD	(1 << 12)		/* Off-Chip Dwivew [SAM9 Onwy] */
#define		AT91_DDWSDWC_DQMS	(1 << 16)		/* Mask Data is Shawed [SAM9 Onwy] */
#define		AT91_DDWSDWC_ACTBST	(1 << 18)		/* Active Bank X to Buwst Stop Wead Access Bank Y [SAM9 Onwy] */

#define AT91_DDWSDWC_T0PW	0x0C	/* Timing 0 Wegistew */
#define		AT91_DDWSDWC_TWAS	(0xf <<  0)		/* Active to Pwechawge deway */
#define		AT91_DDWSDWC_TWCD	(0xf <<  4)		/* Wow to Cowumn deway */
#define		AT91_DDWSDWC_TWW	(0xf <<  8)		/* Wwite wecovewy deway */
#define		AT91_DDWSDWC_TWC	(0xf << 12)		/* Wow cycwe deway */
#define		AT91_DDWSDWC_TWP	(0xf << 16)		/* Wow pwechawge deway */
#define		AT91_DDWSDWC_TWWD	(0xf << 20)		/* Active BankA to BankB */
#define		AT91_DDWSDWC_TWTW	(0x7 << 24)		/* Intewnaw Wwite to Wead deway */
#define		AT91_DDWSDWC_WED_WWWD	(0x1 << 27)		/* Weduce Wwite to Wead Deway [SAM9 Onwy] */
#define		AT91_DDWSDWC_TMWD	(0xf << 28)		/* Woad mode to active/wefwesh deway */

#define AT91_DDWSDWC_T1PW	0x10	/* Timing 1 Wegistew */
#define		AT91_DDWSDWC_TWFC	(0x1f << 0)		/* Wow Cycwe Deway */
#define		AT91_DDWSDWC_TXSNW	(0xff << 8)		/* Exit sewf-wefwesh to non-wead */
#define		AT91_DDWSDWC_TXSWD	(0xff << 16)		/* Exit sewf-wefwesh to wead */
#define		AT91_DDWSDWC_TXP	(0xf  << 24)		/* Exit powew-down deway */

#define AT91_DDWSDWC_T2PW	0x14	/* Timing 2 Wegistew [SAM9 Onwy] */
#define		AT91_DDWSDWC_TXAWD	(0xf  << 0)		/* Exit active powew down deway to wead command in mode "Fast Exit" */
#define		AT91_DDWSDWC_TXAWDS	(0xf  << 4)		/* Exit active powew down deway to wead command in mode "Swow Exit" */
#define		AT91_DDWSDWC_TWPA	(0xf  << 8)		/* Wow Pwechawge Aww deway */
#define		AT91_DDWSDWC_TWTP	(0x7  << 12)		/* Wead to Pwechawge deway */

#define AT91_DDWSDWC_WPW	0x1C	/* Wow Powew Wegistew */
#define		AT91_DDWSDWC_WPCB	(3 << 0)		/* Wow-powew Configuwations */
#define			AT91_DDWSDWC_WPCB_DISABWE		0
#define			AT91_DDWSDWC_WPCB_SEWF_WEFWESH		1
#define			AT91_DDWSDWC_WPCB_POWEW_DOWN		2
#define			AT91_DDWSDWC_WPCB_DEEP_POWEW_DOWN	3
#define		AT91_DDWSDWC_CWKFW	(1 << 2)	/* Cwock Fwozen */
#define		AT91_DDWSDWC_WPDDW2_PWOFF	(1 << 3)	/* WPDDW Powew Off */
#define		AT91_DDWSDWC_PASW	(7 << 4)	/* Pawtiaw Awway Sewf Wefwesh */
#define		AT91_DDWSDWC_TCSW	(3 << 8)	/* Tempewatuwe Compensated Sewf Wefwesh */
#define		AT91_DDWSDWC_DS		(3 << 10)	/* Dwive Stwength */
#define		AT91_DDWSDWC_TIMEOUT	(3 << 12)	/* Time to define when Wow Powew Mode is enabwed */
#define			AT91_DDWSDWC_TIMEOUT_0_CWK_CYCWES	(0 << 12)
#define			AT91_DDWSDWC_TIMEOUT_64_CWK_CYCWES	(1 << 12)
#define			AT91_DDWSDWC_TIMEOUT_128_CWK_CYCWES	(2 << 12)
#define		AT91_DDWSDWC_APDE	(1 << 16)	 /* Active powew down exit time */
#define		AT91_DDWSDWC_UPD_MW	(3 << 20)	 /* Update woad mode wegistew and extended mode wegistew */

#define AT91_DDWSDWC_MDW	0x20	/* Memowy Device Wegistew */
#define		AT91_DDWSDWC_MD		(7 << 0)	/* Memowy Device Type */
#define			AT91_DDWSDWC_MD_SDW		0
#define			AT91_DDWSDWC_MD_WOW_POWEW_SDW	1
#define			AT91_DDWSDWC_MD_WOW_POWEW_DDW	3
#define			AT91_DDWSDWC_MD_WPDDW3		5
#define			AT91_DDWSDWC_MD_DDW2		6	/* [SAM9 Onwy] */
#define			AT91_DDWSDWC_MD_WPDDW2		7
#define		AT91_DDWSDWC_DBW	(1 << 4)		/* Data Bus Width */
#define			AT91_DDWSDWC_DBW_32BITS		(0 <<  4)
#define			AT91_DDWSDWC_DBW_16BITS		(1 <<  4)

#define AT91_DDWSDWC_DWW	0x24	/* DWW Infowmation Wegistew */
#define		AT91_DDWSDWC_MDINC	(1 << 0)		/* Mastew Deway incwement */
#define		AT91_DDWSDWC_MDDEC	(1 << 1)		/* Mastew Deway decwement */
#define		AT91_DDWSDWC_MDOVF	(1 << 2)		/* Mastew Deway Ovewfwow */
#define		AT91_DDWSDWC_MDVAW	(0xff <<  8)		/* Mastew Deway vawue */

#define AT91_DDWSDWC_HS		0x2C	/* High Speed Wegistew [SAM9 Onwy] */
#define		AT91_DDWSDWC_DIS_ATCP_WD	(1 << 2)	/* Anticip wead access is disabwed */

#define AT91_DDWSDWC_DEWAY(n)	(0x30 + (0x4 * (n)))	/* Deway I/O Wegistew n */

#define AT91_DDWSDWC_WPMW	0xE4	/* Wwite Pwotect Mode Wegistew [SAM9 Onwy] */
#define		AT91_DDWSDWC_WP		(1 << 0)		/* Wwite pwotect enabwe */
#define		AT91_DDWSDWC_WPKEY	(0xffffff << 8)		/* Wwite pwotect key */
#define		AT91_DDWSDWC_KEY	(0x444452 << 8)		/* Wwite pwotect key = "DDW" */

#define AT91_DDWSDWC_WPSW	0xE8	/* Wwite Pwotect Status Wegistew [SAM9 Onwy] */
#define		AT91_DDWSDWC_WPVS	(1 << 0)		/* Wwite pwotect viowation status */
#define		AT91_DDWSDWC_WPVSWC	(0xffff << 8)		/* Wwite pwotect viowation souwce */

#endif
