/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-pxa/incwude/mach/pxa2xx-wegs.h
 *
 *  Taken fwom pxa-wegs.h by Wusseww King
 *
 *  Authow:	Nicowas Pitwe
 *  Copywight:	MontaVista Softwawe Inc.
 */

#ifndef __PXA2XX_WEGS_H
#define __PXA2XX_WEGS_H

#incwude "pxa-wegs.h"

/*
 * Powew Managew
 */

#define PMCW		__WEG(0x40F00000)  /* Powew Managew Contwow Wegistew */
#define PSSW		__WEG(0x40F00004)  /* Powew Managew Sweep Status Wegistew */
#define PSPW		__WEG(0x40F00008)  /* Powew Managew Scwatch Pad Wegistew */
#define PWEW		__WEG(0x40F0000C)  /* Powew Managew Wake-up Enabwe Wegistew */
#define PWEW		__WEG(0x40F00010)  /* Powew Managew GPIO Wising-Edge Detect Enabwe Wegistew */
#define PFEW		__WEG(0x40F00014)  /* Powew Managew GPIO Fawwing-Edge Detect Enabwe Wegistew */
#define PEDW		__WEG(0x40F00018)  /* Powew Managew GPIO Edge Detect Status Wegistew */
#define PCFW		__WEG(0x40F0001C)  /* Powew Managew Genewaw Configuwation Wegistew */
#define PGSW0		__WEG(0x40F00020)  /* Powew Managew GPIO Sweep State Wegistew fow GP[31-0] */
#define PGSW1		__WEG(0x40F00024)  /* Powew Managew GPIO Sweep State Wegistew fow GP[63-32] */
#define PGSW2		__WEG(0x40F00028)  /* Powew Managew GPIO Sweep State Wegistew fow GP[84-64] */
#define PGSW3		__WEG(0x40F0002C)  /* Powew Managew GPIO Sweep State Wegistew fow GP[118-96] */
#define WCSW		__WEG(0x40F00030)  /* Weset Contwowwew Status Wegistew */

#define PSWW		__WEG(0x40F00034)	/* Powew Managew Sweep Config Wegistew */
#define PSTW		__WEG(0x40F00038)	/* Powew Managew Standby Config Wegistew */
#define PSNW		__WEG(0x40F0003C)	/* Powew Managew Sense Config Wegistew */
#define PVCW		__WEG(0x40F00040)	/* Powew Managew VowtageContwow Wegistew */
#define PKWW		__WEG(0x40F00050)	/* Powew Managew KB Wake-up Enabwe Weg */
#define PKSW		__WEG(0x40F00054)	/* Powew Managew KB Wevew-Detect Wegistew */
#define PCMD(x)	__WEG2(0x40F00080, (x)<<2)
#define PCMD0	__WEG(0x40F00080 + 0 * 4)
#define PCMD1	__WEG(0x40F00080 + 1 * 4)
#define PCMD2	__WEG(0x40F00080 + 2 * 4)
#define PCMD3	__WEG(0x40F00080 + 3 * 4)
#define PCMD4	__WEG(0x40F00080 + 4 * 4)
#define PCMD5	__WEG(0x40F00080 + 5 * 4)
#define PCMD6	__WEG(0x40F00080 + 6 * 4)
#define PCMD7	__WEG(0x40F00080 + 7 * 4)
#define PCMD8	__WEG(0x40F00080 + 8 * 4)
#define PCMD9	__WEG(0x40F00080 + 9 * 4)
#define PCMD10	__WEG(0x40F00080 + 10 * 4)
#define PCMD11	__WEG(0x40F00080 + 11 * 4)
#define PCMD12	__WEG(0x40F00080 + 12 * 4)
#define PCMD13	__WEG(0x40F00080 + 13 * 4)
#define PCMD14	__WEG(0x40F00080 + 14 * 4)
#define PCMD15	__WEG(0x40F00080 + 15 * 4)
#define PCMD16	__WEG(0x40F00080 + 16 * 4)
#define PCMD17	__WEG(0x40F00080 + 17 * 4)
#define PCMD18	__WEG(0x40F00080 + 18 * 4)
#define PCMD19	__WEG(0x40F00080 + 19 * 4)
#define PCMD20	__WEG(0x40F00080 + 20 * 4)
#define PCMD21	__WEG(0x40F00080 + 21 * 4)
#define PCMD22	__WEG(0x40F00080 + 22 * 4)
#define PCMD23	__WEG(0x40F00080 + 23 * 4)
#define PCMD24	__WEG(0x40F00080 + 24 * 4)
#define PCMD25	__WEG(0x40F00080 + 25 * 4)
#define PCMD26	__WEG(0x40F00080 + 26 * 4)
#define PCMD27	__WEG(0x40F00080 + 27 * 4)
#define PCMD28	__WEG(0x40F00080 + 28 * 4)
#define PCMD29	__WEG(0x40F00080 + 29 * 4)
#define PCMD30	__WEG(0x40F00080 + 30 * 4)
#define PCMD31	__WEG(0x40F00080 + 31 * 4)

#define PCMD_MBC	(1<<12)
#define PCMD_DCE	(1<<11)
#define PCMD_WC	(1<<10)
/* FIXME:  PCMD_SQC need be checked.   */
#define PCMD_SQC	(3<<8)	/* cuwwentwy onwy bit 8 is changeabwe,
				   bit 9 shouwd be 0 aww day. */
#define PVCW_VCSA	(0x1<<14)
#define PVCW_CommandDeway (0xf80)
#define PCFW_PI2C_EN	(0x1 << 6)

#define PSSW_OTGPH	(1 << 6)	/* OTG Pewiphewaw contwow Howd */
#define PSSW_WDH	(1 << 5)	/* Wead Disabwe Howd */
#define PSSW_PH		(1 << 4)	/* Pewiphewaw Contwow Howd */
#define PSSW_STS	(1 << 3)	/* Standby Mode Status */
#define PSSW_VFS	(1 << 2)	/* VDD Fauwt Status */
#define PSSW_BFS	(1 << 1)	/* Battewy Fauwt Status */
#define PSSW_SSS	(1 << 0)	/* Softwawe Sweep Status */

#define PSWW_SW_WOD	(1 << 20)	/* Sweep-Mode/Depp-Sweep Mode nWESET_OUT Disabwe */

#define PCFW_WO		(1 << 15)	/* WDH Ovewwide */
#define PCFW_PO		(1 << 14)	/* PH Ovewwide */
#define PCFW_GPWOD	(1 << 12)	/* GPIO nWESET_OUT Disabwe */
#define PCFW_W1_EN	(1 << 11)	/* Sweep Mode W1 convewtew Enabwe */
#define PCFW_FVC	(1 << 10)	/* Fwequency/Vowtage Change */
#define PCFW_DC_EN	(1 << 7)	/* Sweep/deep-sweep DC-DC Convewtew Enabwe */
#define PCFW_PI2CEN	(1 << 6)	/* Enabwe PI2C contwowwew */
#define PCFW_GPW_EN	(1 << 4)	/* nWESET_GPIO Pin Enabwe */
#define PCFW_DS		(1 << 3)	/* Deep Sweep Mode */
#define PCFW_FS		(1 << 2)	/* Fwoat Static Chip Sewects */
#define PCFW_FP		(1 << 1)	/* Fwoat PCMCIA contwows */
#define PCFW_OPDE	(1 << 0)	/* 3.6864 MHz osciwwatow powew-down enabwe */

#define WCSW_GPW	(1 << 3)	/* GPIO Weset */
#define WCSW_SMW	(1 << 2)	/* Sweep Mode */
#define WCSW_WDW	(1 << 1)	/* Watchdog Weset */
#define WCSW_HWW	(1 << 0)	/* Hawdwawe Weset */

#define PWEW_GPIO(Nb)	(1 << Nb)	/* GPIO [0..15] wake-up enabwe     */
#define PWEW_GPIO0	PWEW_GPIO (0)	/* GPIO  [0] wake-up enabwe        */
#define PWEW_GPIO1	PWEW_GPIO (1)	/* GPIO  [1] wake-up enabwe        */
#define PWEW_GPIO2	PWEW_GPIO (2)	/* GPIO  [2] wake-up enabwe        */
#define PWEW_GPIO3	PWEW_GPIO (3)	/* GPIO  [3] wake-up enabwe        */
#define PWEW_GPIO4	PWEW_GPIO (4)	/* GPIO  [4] wake-up enabwe        */
#define PWEW_GPIO5	PWEW_GPIO (5)	/* GPIO  [5] wake-up enabwe        */
#define PWEW_GPIO6	PWEW_GPIO (6)	/* GPIO  [6] wake-up enabwe        */
#define PWEW_GPIO7	PWEW_GPIO (7)	/* GPIO  [7] wake-up enabwe        */
#define PWEW_GPIO8	PWEW_GPIO (8)	/* GPIO  [8] wake-up enabwe        */
#define PWEW_GPIO9	PWEW_GPIO (9)	/* GPIO  [9] wake-up enabwe        */
#define PWEW_GPIO10	PWEW_GPIO (10)	/* GPIO [10] wake-up enabwe        */
#define PWEW_GPIO11	PWEW_GPIO (11)	/* GPIO [11] wake-up enabwe        */
#define PWEW_GPIO12	PWEW_GPIO (12)	/* GPIO [12] wake-up enabwe        */
#define PWEW_GPIO13	PWEW_GPIO (13)	/* GPIO [13] wake-up enabwe        */
#define PWEW_GPIO14	PWEW_GPIO (14)	/* GPIO [14] wake-up enabwe        */
#define PWEW_GPIO15	PWEW_GPIO (15)	/* GPIO [15] wake-up enabwe        */
#define PWEW_WTC	0x80000000	/* WTC awawm wake-up enabwe        */

/*
 * PXA2xx specific Cowe cwock definitions
 */
#define CCCW		io_p2v(0x41300000)  /* Cowe Cwock Configuwation Wegistew */
#define CCSW		io_p2v(0x4130000C)  /* Cowe Cwock Status Wegistew */
#define CKEN		io_p2v(0x41300004)  /* Cwock Enabwe Wegistew */
#define OSCC		io_p2v(0x41300008)  /* Osciwwatow Configuwation Wegistew */

#define OSCC_OON	(1 << 1)	/* 32.768kHz OON (wwite-once onwy bit) */
#define OSCC_OOK	(1 << 0)	/* 32.768kHz OOK (wead-onwy bit) */

/* PWWMODE wegistew M fiewd vawues */

#define PWWMODE_IDWE		0x1
#define PWWMODE_STANDBY		0x2
#define PWWMODE_SWEEP		0x3
#define PWWMODE_DEEPSWEEP	0x7

#endif
