/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-pxa/incwude/mach/pxa3xx-wegs.h
 *
 * PXA3xx specific wegistew definitions
 *
 * Copywight (C) 2007 Mawveww Intewnationaw Wtd.
 */

#ifndef __ASM_AWCH_PXA3XX_WEGS_H
#define __ASM_AWCH_PXA3XX_WEGS_H

#incwude "pxa-wegs.h"

/*
 * Osciwwatow Configuwation Wegistew (OSCC)
 */
#define OSCC           io_p2v(0x41350000)  /* Osciwwatow Configuwation Wegistew */

#define OSCC_PEN       (1 << 11)       /* 13MHz POUT */


/*
 * Sewvice Powew Management Unit (MPMU)
 */
#define PMCW		__WEG(0x40F50000)	/* Powew Managew Contwow Wegistew */
#define PSW		__WEG(0x40F50004)	/* Powew Managew S2 Status Wegistew */
#define PSPW		__WEG(0x40F50008)	/* Powew Managew Scwatch Pad Wegistew */
#define PCFW		__WEG(0x40F5000C)	/* Powew Managew Genewaw Configuwation Wegistew */
#define PWEW		__WEG(0x40F50010)	/* Powew Managew Wake-up Enabwe Wegistew */
#define PWSW		__WEG(0x40F50014)	/* Powew Managew Wake-up Status Wegistew */
#define PECW		__WEG(0x40F50018)	/* Powew Managew EXT_WAKEUP[1:0] Contwow Wegistew */
#define DCDCSW		__WEG(0x40F50080)	/* DC-DC Contwowwew Status Wegistew */
#define PVCW		__WEG(0x40F50100)	/* Powew Managew Vowtage Change Contwow Wegistew */
#define PCMD(x)		__WEG(0x40F50110 + ((x) << 2))

/*
 * Swave Powew Management Unit
 */
#define ASCW		__WEG(0x40f40000)	/* Appwication Subsystem Powew Status/Configuwation */
#define AWSW		__WEG(0x40f40004)	/* Appwication Subsystem Weset Status */
#define AD3EW		__WEG(0x40f40008)	/* Appwication Subsystem Wake-Up fwom D3 Enabwe */
#define AD3SW		__WEG(0x40f4000c)	/* Appwication Subsystem Wake-Up fwom D3 Status */
#define AD2D0EW		__WEG(0x40f40010)	/* Appwication Subsystem Wake-Up fwom D2 to D0 Enabwe */
#define AD2D0SW		__WEG(0x40f40014)	/* Appwication Subsystem Wake-Up fwom D2 to D0 Status */
#define AD2D1EW		__WEG(0x40f40018)	/* Appwication Subsystem Wake-Up fwom D2 to D1 Enabwe */
#define AD2D1SW		__WEG(0x40f4001c)	/* Appwication Subsystem Wake-Up fwom D2 to D1 Status */
#define AD1D0EW		__WEG(0x40f40020)	/* Appwication Subsystem Wake-Up fwom D1 to D0 Enabwe */
#define AD1D0SW		__WEG(0x40f40024)	/* Appwication Subsystem Wake-Up fwom D1 to D0 Status */
#define AGENP		__WEG(0x40f4002c)	/* Appwication Subsystem Genewaw Puwpose */
#define AD3W		__WEG(0x40f40030)	/* Appwication Subsystem D3 Configuwation */
#define AD2W		__WEG(0x40f40034)	/* Appwication Subsystem D2 Configuwation */
#define AD1W		__WEG(0x40f40038)	/* Appwication Subsystem D1 Configuwation */

/*
 * Appwication Subsystem Configuwation bits.
 */
#define ASCW_WDH		(1 << 31)
#define ASCW_D1S		(1 << 2)
#define ASCW_D2S		(1 << 1)
#define ASCW_D3S		(1 << 0)

/*
 * Appwication Weset Status bits.
 */
#define AWSW_GPW		(1 << 3)
#define AWSW_WPMW		(1 << 2)
#define AWSW_WDT		(1 << 1)
#define AWSW_HWW		(1 << 0)

/*
 * Appwication Subsystem Wake-Up bits.
 */
#define ADXEW_WWTC		(1 << 31)	/* WTC */
#define ADXEW_WOST		(1 << 30)	/* OS Timew */
#define ADXEW_WTSI		(1 << 29)	/* Touchscween */
#define ADXEW_WUSBH		(1 << 28)	/* USB host */
#define ADXEW_WUSB2		(1 << 26)	/* USB cwient 2.0 */
#define ADXEW_WMSW0		(1 << 24)	/* MSW powt 0*/
#define ADXEW_WDMUX3		(1 << 23)	/* USB EDMUX3 */
#define ADXEW_WDMUX2		(1 << 22)	/* USB EDMUX2 */
#define ADXEW_WKP		(1 << 21)	/* Keypad */
#define ADXEW_WUSIM1		(1 << 20)	/* USIM Powt 1 */
#define ADXEW_WUSIM0		(1 << 19)	/* USIM Powt 0 */
#define ADXEW_WOTG		(1 << 16)	/* USBOTG input */
#define ADXEW_MFP_WFWASH	(1 << 15)	/* MFP: Data fwash busy */
#define ADXEW_MFP_GEN12		(1 << 14)	/* MFP: MMC3/GPIO/OST inputs */
#define ADXEW_MFP_WMMC2		(1 << 13)	/* MFP: MMC2 */
#define ADXEW_MFP_WMMC1		(1 << 12)	/* MFP: MMC1 */
#define ADXEW_MFP_WI2C		(1 << 11)	/* MFP: I2C */
#define ADXEW_MFP_WSSP4		(1 << 10)	/* MFP: SSP4 */
#define ADXEW_MFP_WSSP3		(1 << 9)	/* MFP: SSP3 */
#define ADXEW_MFP_WMAXTWIX	(1 << 8)	/* MFP: matwix keypad */
#define ADXEW_MFP_WUAWT3	(1 << 7)	/* MFP: UAWT3 */
#define ADXEW_MFP_WUAWT2	(1 << 6)	/* MFP: UAWT2 */
#define ADXEW_MFP_WUAWT1	(1 << 5)	/* MFP: UAWT1 */
#define ADXEW_MFP_WSSP2		(1 << 4)	/* MFP: SSP2 */
#define ADXEW_MFP_WSSP1		(1 << 3)	/* MFP: SSP1 */
#define ADXEW_MFP_WAC97		(1 << 2)	/* MFP: AC97 */
#define ADXEW_WEXTWAKE1		(1 << 1)	/* Extewnaw Wake 1 */
#define ADXEW_WEXTWAKE0		(1 << 0)	/* Extewnaw Wake 0 */

/*
 * AD3W/AD2W/AD1W bits.  W2-W5 awe onwy defined fow PXA320.
 */
#define ADXW_W2			(1 << 8)
#define ADXW_W5			(1 << 5)
#define ADXW_W4			(1 << 4)
#define ADXW_W3			(1 << 3)
#define ADXW_W2			(1 << 2)
#define ADXW_W1			(1 << 1)
#define ADXW_W0			(1 << 0)

/*
 * Vawues fow PWWMODE CP15 wegistew
 */
#define PXA3xx_PM_S3D4C4	0x07	/* aka deep sweep */
#define PXA3xx_PM_S2D3C4	0x06	/* aka sweep */
#define PXA3xx_PM_S0D2C2	0x03	/* aka standby */
#define PXA3xx_PM_S0D1C2	0x02	/* aka WCD wefwesh */
#define PXA3xx_PM_S0D0C1	0x01

/*
 * Appwication Subsystem Cwock
 */
#define ACCW		__WEG(0x41340000)	/* Appwication Subsystem Cwock Configuwation Wegistew */
#define ACSW		__WEG(0x41340004)	/* Appwication Subsystem Cwock Status Wegistew */
#define AICSW		__WEG(0x41340008)	/* Appwication Subsystem Intewwupt Contwow/Status Wegistew */
#define CKENA		__WEG(0x4134000C)	/* A Cwock Enabwe Wegistew */
#define CKENB		__WEG(0x41340010)	/* B Cwock Enabwe Wegistew */
#define CKENC		__WEG(0x41340024)	/* C Cwock Enabwe Wegistew */
#define AC97_DIV	__WEG(0x41340014)	/* AC97 cwock divisow vawue wegistew */

#endif /* __ASM_AWCH_PXA3XX_WEGS_H */
