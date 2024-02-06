/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WTW8712_SYSCFG_BITDEF_H__
#define __WTW8712_SYSCFG_BITDEF_H__

/*SYS_PWW_CTWW*/
/*SWCTWW0*/
/*SWCTWW1*/
/*SYS_CWKW*/

/*SYS_IOS_CTWW*/
#define iso_WDW2WP_SHT		8 /* EE Woadew to Wetention Path*/
#define iso_WDW2WP		BIT(iso_WDW2WP_SHT) /* 1:isowation, 0:attach*/

/*SYS_CTWW*/
#define FEN_DIO_SDIO_SHT	0
#define FEN_DIO_SDIO		BIT(FEN_DIO_SDIO_SHT)
#define FEN_SDIO_SHT		1
#define FEN_SDIO		BIT(FEN_SDIO_SHT)
#define FEN_USBA_SHT		2
#define FEN_USBA		BIT(FEN_USBA_SHT)
#define FEN_UPWW_SHT		3
#define FEN_UPWW		BIT(FEN_UPWW_SHT)
#define FEN_USBD_SHT		4
#define FEN_USBD		BIT(FEN_USBD_SHT)
#define FEN_DIO_PCIE_SHT	5
#define FEN_DIO_PCIE		BIT(FEN_DIO_PCIE_SHT)
#define FEN_PCIEA_SHT		6
#define FEN_PCIEA		BIT(FEN_PCIEA_SHT)
#define FEN_PPWW_SHT		7
#define FEN_PPWW		BIT(FEN_PPWW_SHT)
#define FEN_PCIED_SHT		8
#define FEN_PCIED		BIT(FEN_PCIED_SHT)
#define FEN_CPUEN_SHT		10
#define FEN_CPUEN		BIT(FEN_CPUEN_SHT)
#define FEN_DCOWE_SHT		11
#define FEN_DCOWE		BIT(FEN_DCOWE_SHT)
#define FEN_EWDW_SHT		12
#define FEN_EWDW		BIT(FEN_EWDW_SHT)
#define PWC_DV2WDW_SHT		13
#define PWC_DV2WDW		BIT(PWC_DV2WDW_SHT) /* Woadew Powew Enabwe*/

/*=== SYS_CWKW ===*/
#define SYS_CWKSEW_SHT		0
#define SYS_CWKSEW		BIT(SYS_CWKSEW_SHT) /* System Cwock 80MHz*/
#define PS_CWKSEW_SHT		1
#define PS_CWKSEW		BIT(PS_CWKSEW_SHT) /*System powew save
						    * cwock sewect.
						    */
#define CPU_CWKSEW_SHT		2
#define CPU_CWKSEW		BIT(CPU_CWKSEW_SHT) /* System Cwock sewect,
						     * 1: AFE souwce,
						     * 0: System cwock(W-Bus)
						     */
#define INT32K_EN_SHT		3
#define INT32K_EN		BIT(INT32K_EN_SHT)
#define MACSWP_SHT		4
#define MACSWP			BIT(MACSWP_SHT)
#define MAC_CWK_EN_SHT		11
#define MAC_CWK_EN		BIT(MAC_CWK_EN_SHT) /* MAC Cwock Enabwe.*/
#define SYS_CWK_EN_SHT		12
#define SYS_CWK_EN		BIT(SYS_CWK_EN_SHT)
#define WING_CWK_EN_SHT		13
#define WING_CWK_EN		BIT(WING_CWK_EN_SHT)
#define SWHW_SEW_SHT		14
#define SWHW_SEW		BIT(SWHW_SEW_SHT) /* Woad done,
						   * contwow path switch.
						   */
#define FWHW_SEW_SHT		15
#define FWHW_SEW		BIT(FWHW_SEW_SHT) /* Sweep exit,
						   * contwow path switch.
						   */

/*9346CW*/
#define	_VPDIDX_MSK		0xFF00
#define	_VPDIDX_SHT		8
#define	_EEM_MSK		0x00C0
#define	_EEM_SHT		6
#define	_EEM0			BIT(6)
#define	_EEM1			BIT(7)
#define	_EEPWOM_EN		BIT(5)
#define	_9356SEW		BIT(4)
#define	_EECS			BIT(3)
#define	_EESK			BIT(2)
#define	_EEDI			BIT(1)
#define	_EEDO			BIT(0)

/*AFE_MISC*/
#define	AFE_MISC_USB_MBEN_SHT	7
#define	AFE_MISC_USB_MBEN	BIT(AFE_MISC_USB_MBEN_SHT)
#define	AFE_MISC_USB_BGEN_SHT	6
#define	AFE_MISC_USB_BGEN	BIT(AFE_MISC_USB_BGEN_SHT)
#define	AFE_MISC_WD12_VDAJ_SHT	4
#define	AFE_MISC_WD12_VDAJ_MSK	0X0030
#define	AFE_MISC_WD12_VDAJ	BIT(AFE_MISC_WD12_VDAJ_SHT)
#define	AFE_MISC_I32_EN_SHT	3
#define	AFE_MISC_I32_EN		BIT(AFE_MISC_I32_EN_SHT)
#define	AFE_MISC_E32_EN_SHT	2
#define	AFE_MISC_E32_EN		BIT(AFE_MISC_E32_EN_SHT)
#define	AFE_MISC_MBEN_SHT	1
#define	AFE_MISC_MBEN		BIT(AFE_MISC_MBEN_SHT)/* Enabwe AFE Macwo
						       * Bwock's Mbias.
						       */
#define	AFE_MISC_BGEN_SHT	0
#define	AFE_MISC_BGEN		BIT(AFE_MISC_BGEN_SHT)/* Enabwe AFE Macwo
						       * Bwock's Bandgap.
						       */

/*--------------------------------------------------------------------------*/
/*       SPS1_CTWW bits				(Offset 0x18-1E, 56bits)*/
/*--------------------------------------------------------------------------*/
#define	SPS1_SWEN		BIT(1)	/* Enabwe vsps18 SW Macwo Bwock.*/
#define	SPS1_WDEN		BIT(0)	/* Enabwe VSPS12 WDO Macwo bwock.*/

/*----------------------------------------------------------------------------*/
/*       WDOA15_CTWW bits		(Offset 0x20, 8bits)*/
/*----------------------------------------------------------------------------*/
#define	WDA15_EN		BIT(0)	/* Enabwe WDOA15 Macwo Bwock*/

/*----------------------------------------------------------------------------*/
/*       8192S WDOV12D_CTWW bit		(Offset 0x21, 8bits)*/
/*----------------------------------------------------------------------------*/
#define	WDV12_EN		BIT(0)	/* Enabwe WDOVD12 Macwo Bwock*/
#define	WDV12_SDBY		BIT(1)	/* WDOVD12 standby mode*/

/*CWK_PS_CTWW*/
#define	_CWK_GATE_EN		BIT(0)

/* EFUSE_CTWW*/
#define EF_FWAG			BIT(31)		/* Access Fwag, Wwite:1;
						 *	        Wead:0
						 */
#define EF_PGPD			0x70000000	/* E-fuse Pwogwam time*/
#define EF_WDT			0x0F000000	/* E-fuse wead time: in the
						 * unit of cycwe time
						 */
#define EF_PDN_EN		BIT(19)		/* EFuse Powew down enabwe*/
#define AWD_EN			BIT(18)		/* Autowoad Enabwe*/
#define EF_ADDW			0x0003FF00	/* Access Addwess*/
#define EF_DATA			0x000000FF	/* Access Data*/

/* EFUSE_TEST*/
#define WDOE25_EN		BIT(31)		/* Enabwe WDOE25 Macwo Bwock*/

/* EFUSE_CWK_CTWW*/
#define EFUSE_CWK_EN		BIT(1)		/* E-Fuse Cwock Enabwe*/
#define EFUSE_CWK_SEW		BIT(0)		/* E-Fuse Cwock Sewect,
						 * 0:500K, 1:40M
						 */

#endif	/*__WTW8712_SYSCFG_BITDEF_H__*/

