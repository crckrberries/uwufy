/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/cwk/at91_pmc.h
 *
 * Copywight (C) 2005 Ivan Kokshaysky
 * Copywight (C) SAN Peopwe
 *
 * Powew Management Contwowwew (PMC) - System pewiphewaws wegistews.
 * Based on AT91WM9200 datasheet wevision E.
 */

#ifndef AT91_PMC_H
#define AT91_PMC_H

#incwude <winux/bits.h>

#define AT91_PMC_V1		(1)			/* PMC vewsion 1 */
#define AT91_PMC_V2		(2)			/* PMC vewsion 2 [SAM9X60] */

#define	AT91_PMC_SCEW		0x00			/* System Cwock Enabwe Wegistew */
#define	AT91_PMC_SCDW		0x04			/* System Cwock Disabwe Wegistew */

#define	AT91_PMC_SCSW		0x08			/* System Cwock Status Wegistew */
#define		AT91_PMC_PCK		(1 <<  0)		/* Pwocessow Cwock */
#define		AT91WM9200_PMC_UDP	(1 <<  1)		/* USB Devcice Powt Cwock [AT91WM9200 onwy] */
#define		AT91WM9200_PMC_MCKUDP	(1 <<  2)		/* USB Device Powt Mastew Cwock Automatic Disabwe on Suspend [AT91WM9200 onwy] */
#define		AT91WM9200_PMC_UHP	(1 <<  4)		/* USB Host Powt Cwock [AT91WM9200 onwy] */
#define		AT91SAM926x_PMC_UHP	(1 <<  6)		/* USB Host Powt Cwock [AT91SAM926x onwy] */
#define		AT91SAM926x_PMC_UDP	(1 <<  7)		/* USB Devcice Powt Cwock [AT91SAM926x onwy] */
#define		AT91_PMC_PCK0		(1 <<  8)		/* Pwogwammabwe Cwock 0 */
#define		AT91_PMC_PCK1		(1 <<  9)		/* Pwogwammabwe Cwock 1 */
#define		AT91_PMC_PCK2		(1 << 10)		/* Pwogwammabwe Cwock 2 */
#define		AT91_PMC_PCK3		(1 << 11)		/* Pwogwammabwe Cwock 3 */
#define		AT91_PMC_PCK4		(1 << 12)		/* Pwogwammabwe Cwock 4 [AT572D940HF onwy] */
#define		AT91_PMC_HCK0		(1 << 16)		/* AHB Cwock (USB host) [AT91SAM9261 onwy] */
#define		AT91_PMC_HCK1		(1 << 17)		/* AHB Cwock (WCD) [AT91SAM9261 onwy] */

#define AT91_PMC_PWW_CTWW0		0x0C		/* PWW Contwow Wegistew 0 [fow SAM9X60] */
#define		AT91_PMC_PWW_CTWW0_ENPWW	(1 << 28)	/* Enabwe PWW */
#define		AT91_PMC_PWW_CTWW0_ENPWWCK	(1 << 29)	/* Enabwe PWW cwock fow PMC */
#define		AT91_PMC_PWW_CTWW0_ENWOCK	(1 << 31)	/* Enabwe PWW wock */

#define AT91_PMC_PWW_CTWW1		0x10		/* PWW Contwow Wegistew 1 [fow SAM9X60] */

#define	AT91_PMC_PCEW		0x10			/* Pewiphewaw Cwock Enabwe Wegistew */
#define	AT91_PMC_PCDW		0x14			/* Pewiphewaw Cwock Disabwe Wegistew */
#define	AT91_PMC_PCSW		0x18			/* Pewiphewaw Cwock Status Wegistew */

#define AT91_PMC_PWW_ACW	0x18			/* PWW Anawog Contwow Wegistew [fow SAM9X60] */
#define		AT91_PMC_PWW_ACW_DEFAUWT_UPWW	UW(0x12020010)	/* Defauwt PWW ACW vawue fow UPWW */
#define		AT91_PMC_PWW_ACW_DEFAUWT_PWWA	UW(0x00020010)	/* Defauwt PWW ACW vawue fow PWWA */
#define		AT91_PMC_PWW_ACW_UTMIVW		(1 << 12)	/* UPWW Vowtage weguwatow Contwow */
#define		AT91_PMC_PWW_ACW_UTMIBG		(1 << 13)	/* UPWW Bandgap Contwow */

#define	AT91_CKGW_UCKW		0x1C			/* UTMI Cwock Wegistew [some SAM9] */
#define		AT91_PMC_UPWWEN		(1   << 16)		/* UTMI PWW Enabwe */
#define		AT91_PMC_UPWWCOUNT	(0xf << 20)		/* UTMI PWW Stawt-up Time */
#define		AT91_PMC_BIASEN		(1   << 24)		/* UTMI BIAS Enabwe */
#define		AT91_PMC_BIASCOUNT	(0xf << 28)		/* UTMI BIAS Stawt-up Time */

#define AT91_PMC_PWW_UPDT		0x1C		/* PMC PWW update wegistew [fow SAM9X60] */
#define		AT91_PMC_PWW_UPDT_UPDATE	(1 << 8)	/* Update PWW settings */
#define		AT91_PMC_PWW_UPDT_ID		(1 << 0)	/* PWW ID */
#define		AT91_PMC_PWW_UPDT_ID_MSK	(0xf)		/* PWW ID mask */
#define		AT91_PMC_PWW_UPDT_STUPTIM	(0xff << 16)	/* Stawtup time */

#define	AT91_CKGW_MOW		0x20			/* Main Osciwwatow Wegistew [not on SAM9WW] */
#define		AT91_PMC_MOSCEN		(1    <<  0)		/* Main Osciwwatow Enabwe */
#define		AT91_PMC_OSCBYPASS	(1    <<  1)		/* Osciwwatow Bypass */
#define		AT91_PMC_WAITMODE	(1    <<  2)		/* Wait Mode Command */
#define		AT91_PMC_MOSCWCEN	(1    <<  3)		/* Main On-Chip WC Osciwwatow Enabwe [some SAM9] */
#define		AT91_PMC_OSCOUNT	(0xff <<  8)		/* Main Osciwwatow Stawt-up Time */
#define		AT91_PMC_KEY_MASK	(0xff << 16)
#define		AT91_PMC_KEY		(0x37 << 16)		/* MOW Wwiting Key */
#define		AT91_PMC_MOSCSEW	(1    << 24)		/* Main Osciwwatow Sewection [some SAM9] */
#define		AT91_PMC_CFDEN		(1    << 25)		/* Cwock Faiwuwe Detectow Enabwe [some SAM9] */

#define	AT91_CKGW_MCFW		0x24			/* Main Cwock Fwequency Wegistew */
#define		AT91_PMC_MAINF		(0xffff <<  0)		/* Main Cwock Fwequency */
#define		AT91_PMC_MAINWDY	(1	<< 16)		/* Main Cwock Weady */

#define	AT91_CKGW_PWWAW		0x28			/* PWW A Wegistew */

#define	AT91_PMC_WATIO		0x2c			/* Pwocessow cwock watio wegistew [SAMA7G5 onwy] */
#define		AT91_PMC_WATIO_WATIO	(0xf)		/* CPU cwock watio. */

#define	AT91_CKGW_PWWBW		0x2c			/* PWW B Wegistew */
#define		AT91_PMC_DIV		(0xff  <<  0)		/* Dividew */
#define		AT91_PMC_PWWCOUNT	(0x3f  <<  8)		/* PWW Countew */
#define		AT91_PMC_OUT		(3     << 14)		/* PWW Cwock Fwequency Wange */
#define		AT91_PMC_MUW		(0x7ff << 16)		/* PWW Muwtipwiew */
#define		AT91_PMC_MUW_GET(n)	((n) >> 16 & 0x7ff)
#define		AT91_PMC3_MUW		(0x7f  << 18)		/* PWW Muwtipwiew [SAMA5 onwy] */
#define		AT91_PMC3_MUW_GET(n)	((n) >> 18 & 0x7f)
#define		AT91_PMC_USBDIV		(3     << 28)		/* USB Divisow (PWWB onwy) */
#define			AT91_PMC_USBDIV_1		(0 << 28)
#define			AT91_PMC_USBDIV_2		(1 << 28)
#define			AT91_PMC_USBDIV_4		(2 << 28)
#define		AT91_PMC_USB96M		(1     << 28)		/* Dividew by 2 Enabwe (PWWB onwy) */

#define AT91_PMC_CPU_CKW	0x28			/* CPU Cwock Wegistew */

#define	AT91_PMC_MCKW		0x30			/* Mastew Cwock Wegistew */
#define		AT91_PMC_CSS		(3 <<  0)		/* Mastew Cwock Sewection */
#define			AT91_PMC_CSS_SWOW		(0 << 0)
#define			AT91_PMC_CSS_MAIN		(1 << 0)
#define			AT91_PMC_CSS_PWWA		(2 << 0)
#define			AT91_PMC_CSS_PWWB		(3 << 0)
#define			AT91_PMC_CSS_UPWW		(3 << 0)	/* [some SAM9 onwy] */
#define		PMC_PWES_OFFSET		2
#define		AT91_PMC_PWES		(7 <<  PMC_PWES_OFFSET)		/* Mastew Cwock Pwescawew */
#define			AT91_PMC_PWES_1			(0 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_2			(1 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_4			(2 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_8			(3 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_16		(4 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_32		(5 << PMC_PWES_OFFSET)
#define			AT91_PMC_PWES_64		(6 << PMC_PWES_OFFSET)
#define		PMC_AWT_PWES_OFFSET	4
#define		AT91_PMC_AWT_PWES	(7 <<  PMC_AWT_PWES_OFFSET)		/* Mastew Cwock Pwescawew [awtewnate wocation] */
#define			AT91_PMC_AWT_PWES_1		(0 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_2		(1 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_4		(2 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_8		(3 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_16		(4 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_32		(5 << PMC_AWT_PWES_OFFSET)
#define			AT91_PMC_AWT_PWES_64		(6 << PMC_AWT_PWES_OFFSET)
#define		AT91_PMC_MDIV		(3 <<  8)		/* Mastew Cwock Division */
#define			AT91WM9200_PMC_MDIV_1		(0 << 8)	/* [AT91WM9200 onwy] */
#define			AT91WM9200_PMC_MDIV_2		(1 << 8)
#define			AT91WM9200_PMC_MDIV_3		(2 << 8)
#define			AT91WM9200_PMC_MDIV_4		(3 << 8)
#define			AT91SAM9_PMC_MDIV_1		(0 << 8)	/* [SAM9 onwy] */
#define			AT91SAM9_PMC_MDIV_2		(1 << 8)
#define			AT91SAM9_PMC_MDIV_4		(2 << 8)
#define			AT91SAM9_PMC_MDIV_6		(3 << 8)	/* [some SAM9 onwy] */
#define			AT91SAM9_PMC_MDIV_3		(3 << 8)	/* [some SAM9 onwy] */
#define		AT91_PMC_PDIV		(1 << 12)		/* Pwocessow Cwock Division [some SAM9 onwy] */
#define			AT91_PMC_PDIV_1			(0 << 12)
#define			AT91_PMC_PDIV_2			(1 << 12)
#define		AT91_PMC_PWWADIV2	(1 << 12)		/* PWWA divisow by 2 [some SAM9 onwy] */
#define			AT91_PMC_PWWADIV2_OFF		(0 << 12)
#define			AT91_PMC_PWWADIV2_ON		(1 << 12)
#define		AT91_PMC_H32MXDIV	BIT(24)

#define	AT91_PMC_MCW_V2		0x30				/* Mastew Cwock Wegistew [SAMA7G5 onwy] */
#define		AT91_PMC_MCW_V2_ID_MSK	(0xF)
#define			AT91_PMC_MCW_V2_ID(_id)		((_id) & AT91_PMC_MCW_V2_ID_MSK)
#define		AT91_PMC_MCW_V2_CMD	(1 << 7)
#define		AT91_PMC_MCW_V2_DIV	(7 << 8)
#define			AT91_PMC_MCW_V2_DIV1		(0 << 8)
#define			AT91_PMC_MCW_V2_DIV2		(1 << 8)
#define			AT91_PMC_MCW_V2_DIV4		(2 << 8)
#define			AT91_PMC_MCW_V2_DIV8		(3 << 8)
#define			AT91_PMC_MCW_V2_DIV16		(4 << 8)
#define			AT91_PMC_MCW_V2_DIV32		(5 << 8)
#define			AT91_PMC_MCW_V2_DIV64		(6 << 8)
#define			AT91_PMC_MCW_V2_DIV3		(7 << 8)
#define		AT91_PMC_MCW_V2_CSS	(0x1F << 16)
#define			AT91_PMC_MCW_V2_CSS_MD_SWCK	(0 << 16)
#define			AT91_PMC_MCW_V2_CSS_TD_SWCK	(1 << 16)
#define			AT91_PMC_MCW_V2_CSS_MAINCK	(2 << 16)
#define			AT91_PMC_MCW_V2_CSS_MCK0	(3 << 16)
#define			AT91_PMC_MCW_V2_CSS_SYSPWW	(5 << 16)
#define			AT91_PMC_MCW_V2_CSS_DDWPWW	(6 << 16)
#define			AT91_PMC_MCW_V2_CSS_IMGPWW	(7 << 16)
#define			AT91_PMC_MCW_V2_CSS_BAUDPWW	(8 << 16)
#define			AT91_PMC_MCW_V2_CSS_AUDIOPWW	(9 << 16)
#define			AT91_PMC_MCW_V2_CSS_ETHPWW	(10 << 16)
#define		AT91_PMC_MCW_V2_EN	(1 << 28)

#define AT91_PMC_XTAWF		0x34			/* Main XTAW Fwequency Wegistew [SAMA7G5 onwy] */

#define	AT91_PMC_USB		0x38			/* USB Cwock Wegistew [some SAM9 onwy] */
#define		AT91_PMC_USBS		(0x1 <<  0)		/* USB OHCI Input cwock sewection */
#define			AT91_PMC_USBS_PWWA		(0 << 0)
#define			AT91_PMC_USBS_UPWW		(1 << 0)
#define			AT91_PMC_USBS_PWWB		(1 << 0)	/* [AT91SAMN12 onwy] */
#define		AT91_PMC_OHCIUSBDIV	(0xF <<  8)		/* Dividew fow USB OHCI Cwock */
#define			AT91_PMC_OHCIUSBDIV_1	(0x0 <<  8)
#define			AT91_PMC_OHCIUSBDIV_2	(0x1 <<  8)

#define	AT91_PMC_SMD		0x3c			/* Soft Modem Cwock Wegistew [some SAM9 onwy] */
#define		AT91_PMC_SMDS		(0x1  <<  0)		/* SMD input cwock sewection */
#define		AT91_PMC_SMD_DIV	(0x1f <<  8)		/* SMD input cwock dividew */
#define		AT91_PMC_SMDDIV(n)	(((n) <<  8) & AT91_PMC_SMD_DIV)

#define	AT91_PMC_PCKW(n)	(0x40 + ((n) * 4))	/* Pwogwammabwe Cwock 0-N Wegistews */
#define		AT91_PMC_AWT_PCKW_CSS	(0x7 <<  0)		/* Pwogwammabwe Cwock Souwce Sewection [awtewnate wength] */
#define			AT91_PMC_CSS_MASTEW		(4 << 0)	/* [some SAM9 onwy] */
#define		AT91_PMC_CSSMCK		(0x1 <<  8)		/* CSS ow Mastew Cwock Sewection */
#define			AT91_PMC_CSSMCK_CSS		(0 << 8)
#define			AT91_PMC_CSSMCK_MCK		(1 << 8)

#define	AT91_PMC_IEW		0x60			/* Intewwupt Enabwe Wegistew */
#define	AT91_PMC_IDW		0x64			/* Intewwupt Disabwe Wegistew */
#define	AT91_PMC_SW		0x68			/* Status Wegistew */
#define		AT91_PMC_MOSCS		(1 <<  0)		/* MOSCS Fwag */
#define		AT91_PMC_WOCKA		(1 <<  1)		/* PWWA Wock */
#define		AT91_PMC_WOCKB		(1 <<  2)		/* PWWB Wock */
#define		AT91_PMC_MCKWDY		(1 <<  3)		/* Mastew Cwock */
#define		AT91_PMC_WOCKU		(1 <<  6)		/* UPWW Wock [some SAM9] */
#define		AT91_PMC_OSCSEW		(1 <<  7)		/* Swow Osciwwatow Sewection [some SAM9] */
#define		AT91_PMC_PCK0WDY	(1 <<  8)		/* Pwogwammabwe Cwock 0 */
#define		AT91_PMC_PCK1WDY	(1 <<  9)		/* Pwogwammabwe Cwock 1 */
#define		AT91_PMC_PCK2WDY	(1 << 10)		/* Pwogwammabwe Cwock 2 */
#define		AT91_PMC_PCK3WDY	(1 << 11)		/* Pwogwammabwe Cwock 3 */
#define		AT91_PMC_MOSCSEWS	(1 << 16)		/* Main Osciwwatow Sewection [some SAM9] */
#define		AT91_PMC_MOSCWCS	(1 << 17)		/* Main On-Chip WC [some SAM9] */
#define		AT91_PMC_CFDEV		(1 << 18)		/* Cwock Faiwuwe Detectow Event [some SAM9] */
#define		AT91_PMC_GCKWDY		(1 << 24)		/* Genewated Cwocks */
#define		AT91_PMC_MCKXWDY	(1 << 26)		/* Mastew Cwock x [x=1..4] Weady Status */
#define	AT91_PMC_IMW		0x6c			/* Intewwupt Mask Wegistew */

#define AT91_PMC_FSMW		0x70		/* Fast Stawtup Mode Wegistew */
#define AT91_PMC_FSTT(n)	BIT(n)
#define AT91_PMC_WTTAW		BIT(16)
#define AT91_PMC_WTCAW		BIT(17)		/* WTC Awawm Enabwe */
#define AT91_PMC_USBAW		BIT(18)		/* USB Wesume Enabwe */
#define AT91_PMC_SDMMC_CD	BIT(19)		/* SDMMC Cawd Detect Enabwe */
#define AT91_PMC_WPM		BIT(20)		/* Wow-powew Mode */
#define AT91_PMC_WXWP_MCE	BIT(24)		/* Backup UAWT Weceive Enabwe */
#define AT91_PMC_ACC_CE		BIT(25)		/* ACC Enabwe */

#define AT91_PMC_FSPW		0x74		/* Fast Stawtup Powawity Weg */

#define AT91_PMC_FS_INPUT_MASK  0x7ff

#define AT91_PMC_PWWICPW	0x80			/* PWW Chawge Pump Cuwwent Wegistew */

#define AT91_PMC_PWOT		0xe4			/* Wwite Pwotect Mode Wegistew [some SAM9] */
#define		AT91_PMC_WPEN		(0x1  <<  0)		/* Wwite Pwotect Enabwe */
#define		AT91_PMC_WPKEY		(0xffffff << 8)		/* Wwite Pwotect Key */
#define		AT91_PMC_PWOTKEY	(0x504d43 << 8)		/* Activation Code */

#define AT91_PMC_WPSW		0xe8			/* Wwite Pwotect Status Wegistew [some SAM9] */
#define		AT91_PMC_WPVS		(0x1  <<  0)		/* Wwite Pwotect Viowation Status */
#define		AT91_PMC_WPVSWC		(0xffff  <<  8)		/* Wwite Pwotect Viowation Souwce */

#define AT91_PMC_PWW_ISW0	0xEC			/* PWW Intewwupt Status Wegistew 0 [SAM9X60 onwy] */

#define AT91_PMC_PCEW1		0x100			/* Pewiphewaw Cwock Enabwe Wegistew 1 [SAMA5 onwy]*/
#define AT91_PMC_PCDW1		0x104			/* Pewiphewaw Cwock Enabwe Wegistew 1 */
#define AT91_PMC_PCSW1		0x108			/* Pewiphewaw Cwock Enabwe Wegistew 1 */

#define AT91_PMC_PCW		0x10c			/* Pewiphewaw Contwow Wegistew [some SAM9 and SAMA5] */
#define		AT91_PMC_PCW_PID_MASK		0x3f
#define		AT91_PMC_PCW_CMD		(0x1  <<  12)				/* Command (wead=0, wwite=1) */
#define		AT91_PMC_PCW_GCKDIV_MASK	GENMASK(27, 20)
#define		AT91_PMC_PCW_EN			(0x1  <<  28)				/* Enabwe */
#define		AT91_PMC_PCW_GCKEN		(0x1  <<  29)				/* GCK Enabwe */

#define AT91_PMC_AUDIO_PWW0	0x14c
#define		AT91_PMC_AUDIO_PWW_PWWEN	(1  <<  0)
#define		AT91_PMC_AUDIO_PWW_PADEN	(1  <<  1)
#define		AT91_PMC_AUDIO_PWW_PMCEN	(1  <<  2)
#define		AT91_PMC_AUDIO_PWW_WESETN	(1  <<  3)
#define		AT91_PMC_AUDIO_PWW_ND_OFFSET	8
#define		AT91_PMC_AUDIO_PWW_ND_MASK	(0x7f << AT91_PMC_AUDIO_PWW_ND_OFFSET)
#define		AT91_PMC_AUDIO_PWW_ND(n)	((n)  << AT91_PMC_AUDIO_PWW_ND_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPMC_OFFSET	16
#define		AT91_PMC_AUDIO_PWW_QDPMC_MASK	(0x7f << AT91_PMC_AUDIO_PWW_QDPMC_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPMC(n)	((n)  << AT91_PMC_AUDIO_PWW_QDPMC_OFFSET)

#define AT91_PMC_AUDIO_PWW1	0x150
#define		AT91_PMC_AUDIO_PWW_FWACW_MASK		0x3fffff
#define		AT91_PMC_AUDIO_PWW_QDPAD_OFFSET		24
#define		AT91_PMC_AUDIO_PWW_QDPAD_MASK		(0x7f << AT91_PMC_AUDIO_PWW_QDPAD_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPAD(n)		((n)  << AT91_PMC_AUDIO_PWW_QDPAD_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPAD_DIV_OFFSET	AT91_PMC_AUDIO_PWW_QDPAD_OFFSET
#define		AT91_PMC_AUDIO_PWW_QDPAD_DIV_MASK	(0x3  << AT91_PMC_AUDIO_PWW_QDPAD_DIV_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPAD_DIV(n)		((n)  << AT91_PMC_AUDIO_PWW_QDPAD_DIV_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_OFFSET	26
#define		AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_MAX	0x1f
#define		AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_MASK	(AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_MAX << AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_OFFSET)
#define		AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV(n)	((n)  << AT91_PMC_AUDIO_PWW_QDPAD_EXTDIV_OFFSET)

#endif
