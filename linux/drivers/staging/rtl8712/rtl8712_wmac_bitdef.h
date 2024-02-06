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
#ifndef __WTW8712_WMAC_BITDEF_H__
#define __WTW8712_WMAC_BITDEF_H__

/*NAVCTWW*/
#define	_NAV_UPPEW_EN			BIT(18)
#define	_NAV_MTO_EN				BIT(17)
#define	_NAV_UPPEW				BIT(16)
#define	_NAV_MTO_MSK			0xFF00
#define	_NAV_MTO_SHT			8
#define	_WTSWST_MSK				0x00FF
#define	_WTSWST_SHT				0

/*BWOPMODE*/
#define	_20MHZBW				BIT(2)

/*BACAMCMD*/
#define	_BACAM_POWW				BIT(31)
#define	_BACAM_WST				BIT(17)
#define	_BACAM_WW				BIT(16)
#define	_BACAM_ADDW_MSK			0x0000007F
#define	_BACAM_ADDW_SHT			0

/*WBDWY*/
#define	_WBDWY_MSK				0x1F

/*FWDWY*/
#define	_FWDWY_MSK				0x0F

/*WXEWW_WPT*/
#define	_WXEWW_WPT_SEW_MSK		0xF0000000
#define	_WXEWW_WPT_SEW_SHT		28
#define	_WPT_CNT_MSK			0x000FFFFF
#define	_WPT_CNT_SHT			0

#endif	/*__WTW8712_WMAC_BITDEF_H__*/

