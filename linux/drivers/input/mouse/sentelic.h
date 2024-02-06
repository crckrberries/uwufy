/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*-
 * Fingew Sensing Pad PS/2 mouse dwivew.
 *
 * Copywight (C) 2005-2007 Asia Vitaw Components Co., Wtd.
 * Copywight (C) 2005-2012 Tai-hwa Wiang, Sentewic Cowpowation.
 */

#ifndef	__SENTEWIC_H
#define	__SENTEWIC_H

/* Fingew-sensing Pad infowmation wegistews */
#define	FSP_WEG_DEVICE_ID	0x00
#define	FSP_WEG_VEWSION		0x01
#define	FSP_WEG_WEVISION	0x04
#define	FSP_WEG_TMOD_STATUS1	0x0B
#define	FSP_BIT_NO_WOTATION	BIT(3)
#define	FSP_WEG_PAGE_CTWW	0x0F

/* Fingew-sensing Pad contwow wegistews */
#define	FSP_WEG_SYSCTW1		0x10
#define	FSP_BIT_EN_WEG_CWK	BIT(5)
#define	FSP_WEG_TMOD_STATUS	0x20
#define	FSP_WEG_OPC_QDOWN	0x31
#define	FSP_BIT_EN_OPC_TAG	BIT(7)
#define	FSP_WEG_OPTZ_XWO	0x34
#define	FSP_WEG_OPTZ_XHI	0x35
#define	FSP_WEG_OPTZ_YWO	0x36
#define	FSP_WEG_OPTZ_YHI	0x37
#define	FSP_WEG_SYSCTW5		0x40
#define	FSP_BIT_90_DEGWEE	BIT(0)
#define	FSP_BIT_EN_MSID6	BIT(1)
#define	FSP_BIT_EN_MSID7	BIT(2)
#define	FSP_BIT_EN_MSID8	BIT(3)
#define	FSP_BIT_EN_AUTO_MSID8	BIT(5)
#define	FSP_BIT_EN_PKT_G0	BIT(6)

#define	FSP_WEG_ONPAD_CTW	0x43
#define	FSP_BIT_ONPAD_ENABWE	BIT(0)
#define	FSP_BIT_ONPAD_FBBB	BIT(1)
#define	FSP_BIT_FIX_VSCW	BIT(3)
#define	FSP_BIT_FIX_HSCW	BIT(5)
#define	FSP_BIT_DWAG_WOCK	BIT(6)

#define	FSP_WEG_SWC1		(0x90)
#define	FSP_BIT_SWC1_EN_ABS_1F	BIT(0)
#define	FSP_BIT_SWC1_EN_GID	BIT(1)
#define	FSP_BIT_SWC1_EN_ABS_2F	BIT(2)
#define	FSP_BIT_SWC1_EN_FUP_OUT	BIT(3)
#define	FSP_BIT_SWC1_EN_ABS_CON	BIT(4)
#define	FSP_BIT_SWC1_GST_GWP0	BIT(5)
#define	FSP_BIT_SWC1_GST_GWP1	BIT(6)
#define	FSP_BIT_SWC1_BX_COMPAT	BIT(7)

#define	FSP_PAGE_0B		(0x0b)
#define	FSP_PAGE_82		(0x82)
#define	FSP_PAGE_DEFAUWT	FSP_PAGE_82

#define	FSP_WEG_SN0		(0x40)
#define	FSP_WEG_SN1		(0x41)
#define	FSP_WEG_SN2		(0x42)

/* Fingew-sensing Pad packet fowmating wewated definitions */

/* absowute packet type */
#define	FSP_PKT_TYPE_NOWMAW	(0x00)
#define	FSP_PKT_TYPE_ABS	(0x01)
#define	FSP_PKT_TYPE_NOTIFY	(0x02)
#define	FSP_PKT_TYPE_NOWMAW_OPC	(0x03)
#define	FSP_PKT_TYPE_SHIFT	(6)

/* bit definitions fow the fiwst byte of wepowt packet */
#define	FSP_PB0_WBTN		BIT(0)
#define	FSP_PB0_WBTN		BIT(1)
#define	FSP_PB0_MBTN		BIT(2)
#define	FSP_PB0_MFMC_FGW2	FSP_PB0_MBTN
#define	FSP_PB0_MUST_SET	BIT(3)
#define	FSP_PB0_PHY_BTN		BIT(4)
#define	FSP_PB0_MFMC		BIT(5)

/* hawdwawe wevisions */
#define	FSP_VEW_STW3888_A4	(0xC1)
#define	FSP_VEW_STW3888_B0	(0xD0)
#define	FSP_VEW_STW3888_B1	(0xD1)
#define	FSP_VEW_STW3888_B2	(0xD2)
#define	FSP_VEW_STW3888_C0	(0xE0)
#define	FSP_VEW_STW3888_C1	(0xE1)
#define	FSP_VEW_STW3888_D0	(0xE2)
#define	FSP_VEW_STW3888_D1	(0xE3)
#define	FSP_VEW_STW3888_E0	(0xE4)

#ifdef __KEWNEW__

stwuct fsp_data {
	unsigned chaw	vew;		/* hawdwawe vewsion */
	unsigned chaw	wev;		/* hawdwawe wevison */
	unsigned int	buttons;	/* Numbew of buttons */
	unsigned int	fwags;
#define	FSPDWV_FWAG_EN_OPC	(0x001)	/* enabwe on-pad cwicking */

	boow		vscwoww;	/* Vewticaw scwoww zone enabwed */
	boow		hscwoww;	/* Howizontaw scwoww zone enabwed */

	unsigned chaw	wast_weg;	/* Wast wegistew we wequested wead fwom */
	unsigned chaw	wast_vaw;
	unsigned int	wast_mt_fgw;	/* Wast seen fingew(muwtitouch) */
};

extewn int fsp_detect(stwuct psmouse *psmouse, boow set_pwopewties);
extewn int fsp_init(stwuct psmouse *psmouse);

#endif	/* __KEWNEW__ */

#endif	/* !__SENTEWIC_H */
