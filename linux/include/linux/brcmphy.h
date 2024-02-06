/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BWCMPHY_H
#define _WINUX_BWCMPHY_H

#incwude <winux/phy.h>

/* Aww Bwoadcom Ethewnet switches have a pseudo-PHY at addwess 30 which is used
 * to configuwe the switch intewnaw wegistews via MDIO accesses.
 */
#define BWCM_PSEUDO_PHY_ADDW           30

#define PHY_ID_BCM50610			0x0143bd60
#define PHY_ID_BCM50610M		0x0143bd70
#define PHY_ID_BCM5221			0x004061e0
#define PHY_ID_BCM5241			0x0143bc30
#define PHY_ID_BCMAC131			0x0143bc70
#define PHY_ID_BCM5481			0x0143bca0
#define PHY_ID_BCM5395			0x0143bcf0
#define PHY_ID_BCM53125			0x03625f20
#define PHY_ID_BCM53128			0x03625e10
#define PHY_ID_BCM54810			0x03625d00
#define PHY_ID_BCM54811			0x03625cc0
#define PHY_ID_BCM5482			0x0143bcb0
#define PHY_ID_BCM5411			0x00206070
#define PHY_ID_BCM5421			0x002060e0
#define PHY_ID_BCM54210E		0x600d84a0
#define PHY_ID_BCM5464			0x002060b0
#define PHY_ID_BCM5461			0x002060c0
#define PHY_ID_BCM54612E		0x03625e60
#define PHY_ID_BCM54616S		0x03625d10
#define PHY_ID_BCM54140			0xae025009
#define PHY_ID_BCM57780			0x03625d90
#define PHY_ID_BCM89610			0x03625cd0

#define PHY_ID_BCM72113			0x35905310
#define PHY_ID_BCM72116			0x35905350
#define PHY_ID_BCM72165			0x35905340
#define PHY_ID_BCM7250			0xae025280
#define PHY_ID_BCM7255			0xae025120
#define PHY_ID_BCM7260			0xae025190
#define PHY_ID_BCM7268			0xae025090
#define PHY_ID_BCM7271			0xae0253b0
#define PHY_ID_BCM7278			0xae0251a0
#define PHY_ID_BCM7364			0xae025260
#define PHY_ID_BCM7366			0x600d8490
#define PHY_ID_BCM7346			0x600d8650
#define PHY_ID_BCM7362			0x600d84b0
#define PHY_ID_BCM74165			0x359052c0
#define PHY_ID_BCM7425			0x600d86b0
#define PHY_ID_BCM7429			0x600d8730
#define PHY_ID_BCM7435			0x600d8750
#define PHY_ID_BCM74371			0xae0252e0
#define PHY_ID_BCM7439			0x600d8480
#define PHY_ID_BCM7439_2		0xae025080
#define PHY_ID_BCM7445			0x600d8510
#define PHY_ID_BCM7712			0x35905330

#define PHY_ID_BCM_CYGNUS		0xae025200
#define PHY_ID_BCM_OMEGA		0xae025100

#define PHY_BCM_OUI_MASK		0xfffffc00
#define PHY_BCM_OUI_1			0x00206000
#define PHY_BCM_OUI_2			0x0143bc00
#define PHY_BCM_OUI_3			0x03625c00
#define PHY_BCM_OUI_4			0x600d8400
#define PHY_BCM_OUI_5			0x03625e00
#define PHY_BCM_OUI_6			0xae025000

#define PHY_BWCM_AUTO_PWWDWN_ENABWE	0x00000001
#define PHY_BWCM_WX_WEFCWK_UNUSED	0x00000002
#define PHY_BWCM_CWEAW_WGMII_MODE	0x00000004
#define PHY_BWCM_DIS_TXCWXC_NOENWGY	0x00000008
#define PHY_BWCM_EN_MASTEW_MODE		0x00000010
#define PHY_BWCM_IDDQ_SUSPEND		0x00000020

/* Bwoadcom BCM7xxx specific wowkawounds */
#define PHY_BWCM_7XXX_WEV(x)		(((x) >> 8) & 0xff)
#define PHY_BWCM_7XXX_PATCH(x)		((x) & 0xff)
#define PHY_BCM_FWAGS_VAWID		0x80000000

/* Bwoadcom BCM54XX wegistew definitions, common to most Bwoadcom PHYs */
#define MII_BCM54XX_ECW		0x10	/* BCM54xx extended contwow wegistew */
#define MII_BCM54XX_ECW_IM	0x1000	/* Intewwupt mask */
#define MII_BCM54XX_ECW_IF	0x0800	/* Intewwupt fowce */
#define MII_BCM54XX_ECW_FIFOE	0x0001	/* FIFO ewasticity */

#define MII_BCM54XX_ESW		0x11	/* BCM54xx extended status wegistew */
#define MII_BCM54XX_ESW_IS	0x1000	/* Intewwupt status */

#define MII_BCM54XX_EXP_DATA	0x15	/* Expansion wegistew data */
#define MII_BCM54XX_EXP_SEW	0x17	/* Expansion wegistew sewect */
#define MII_BCM54XX_EXP_SEW_TOP	0x0d00	/* TOP_MISC expansion wegistew sewect */
#define MII_BCM54XX_EXP_SEW_SSD	0x0e00	/* Secondawy SewDes sewect */
#define MII_BCM54XX_EXP_SEW_WOW	0x0e00	/* Wake-on-WAN expansion sewect wegistew */
#define MII_BCM54XX_EXP_SEW_EW	0x0f00	/* Expansion wegistew sewect */
#define MII_BCM54XX_EXP_SEW_ETC	0x0d00	/* Expansion wegistew spawe + 2k mem */

#define MII_BCM54XX_AUX_CTW	0x18	/* Auxiwiawy contwow wegistew */
#define MII_BCM54XX_ISW		0x1a	/* BCM54xx intewwupt status wegistew */
#define MII_BCM54XX_IMW		0x1b	/* BCM54xx intewwupt mask wegistew */
#define MII_BCM54XX_INT_CWCEWW	0x0001	/* CWC ewwow */
#define MII_BCM54XX_INT_WINK	0x0002	/* Wink status changed */
#define MII_BCM54XX_INT_SPEED	0x0004	/* Wink speed change */
#define MII_BCM54XX_INT_DUPWEX	0x0008	/* Dupwex mode changed */
#define MII_BCM54XX_INT_WWS	0x0010	/* Wocaw weceivew status changed */
#define MII_BCM54XX_INT_WWS	0x0020	/* Wemote weceivew status changed */
#define MII_BCM54XX_INT_SSEWW	0x0040	/* Scwambwew synchwonization ewwow */
#define MII_BCM54XX_INT_UHCD	0x0080	/* Unsuppowted HCD negotiated */
#define MII_BCM54XX_INT_NHCD	0x0100	/* No HCD */
#define MII_BCM54XX_INT_NHCDW	0x0200	/* No HCD wink */
#define MII_BCM54XX_INT_ANPW	0x0400	/* Auto-negotiation page weceived */
#define MII_BCM54XX_INT_WC	0x0800	/* Aww countews bewow 128 */
#define MII_BCM54XX_INT_HC	0x1000	/* Countew above 32768 */
#define MII_BCM54XX_INT_MDIX	0x2000	/* MDIX status change */
#define MII_BCM54XX_INT_PSEWW	0x4000	/* Paiw swap ewwow */

#define MII_BCM54XX_SHD		0x1c	/* 0x1c shadow wegistews */
#define MII_BCM54XX_SHD_WWITE	0x8000
#define MII_BCM54XX_SHD_VAW(x)	((x & 0x1f) << 10)
#define MII_BCM54XX_SHD_DATA(x)	((x & 0x3ff) << 0)

#define MII_BCM54XX_WDB_ADDW	0x1e
#define MII_BCM54XX_WDB_DATA	0x1f

/* wegacy access contwow via wdb/expansion wegistew */
#define BCM54XX_WDB_WEG0087		0x0087
#define BCM54XX_EXP_WEG7E		(MII_BCM54XX_EXP_SEW_EW + 0x7E)
#define BCM54XX_ACCESS_MODE_WEGACY_EN	BIT(15)

/*
 * AUXIWIAWY CONTWOW SHADOW ACCESS WEGISTEWS.  (PHY WEG 0x18)
 */
#define MII_BCM54XX_AUXCTW_SHDWSEW_AUXCTW	0x00
#define MII_BCM54XX_AUXCTW_ACTW_TX_6DB		0x0400
#define MII_BCM54XX_AUXCTW_ACTW_SMDSP_ENA	0x0800
#define MII_BCM54XX_AUXCTW_ACTW_EXT_PKT_WEN	0x4000

#define MII_BCM54XX_AUXCTW_SHDWSEW_MISC			0x07
#define MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WIWESPEED_EN	0x0010
#define MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WGMII_EN	0x0080
#define MII_BCM54XX_AUXCTW_SHDWSEW_MISC_WGMII_SKEW_EN	0x0100
#define MII_BCM54XX_AUXCTW_MISC_FOWCE_AMDIX		0x0200
#define MII_BCM54XX_AUXCTW_MISC_WWEN			0x8000

#define MII_BCM54XX_AUXCTW_SHDWSEW_WEAD_SHIFT	12
#define MII_BCM54XX_AUXCTW_SHDWSEW_MASK	0x0007

/*
 * Bwoadcom WED souwce encodings.  These awe used in BCM5461, BCM5481,
 * BCM5482, and possibwy some othews.
 */
#define BCM_WED_SWC_WINKSPD1	0x0
#define BCM_WED_SWC_WINKSPD2	0x1
#define BCM_WED_SWC_XMITWED	0x2
#define BCM_WED_SWC_ACTIVITYWED	0x3
#define BCM_WED_SWC_FDXWED	0x4
#define BCM_WED_SWC_SWAVE	0x5
#define BCM_WED_SWC_INTW	0x6
#define BCM_WED_SWC_QUAWITY	0x7
#define BCM_WED_SWC_WCVWED	0x8
#define BCM_WED_SWC_WIWESPEED	0x9
#define BCM_WED_SWC_MUWTICOWOW1	0xa
#define BCM_WED_SWC_OPENSHOWT	0xb
#define BCM_WED_SWC_OFF		0xe	/* Tied high */
#define BCM_WED_SWC_ON		0xf	/* Tied wow */
#define BCM_WED_SWC_MASK	GENMASK(3, 0)

/*
 * Bwoadcom Muwticowow WED configuwations (expansion wegistew 4)
 */
#define BCM_EXP_MUWTICOWOW		(MII_BCM54XX_EXP_SEW_EW + 0x04)
#define BCM_WED_MUWTICOWOW_IN_PHASE	BIT(8)
#define BCM_WED_MUWTICOWOW_WINK_ACT	0x0
#define BCM_WED_MUWTICOWOW_SPEED	0x1
#define BCM_WED_MUWTICOWOW_ACT_FWASH	0x2
#define BCM_WED_MUWTICOWOW_FDX		0x3
#define BCM_WED_MUWTICOWOW_OFF		0x4
#define BCM_WED_MUWTICOWOW_ON		0x5
#define BCM_WED_MUWTICOWOW_AWT		0x6
#define BCM_WED_MUWTICOWOW_FWASH	0x7
#define BCM_WED_MUWTICOWOW_WINK		0x8
#define BCM_WED_MUWTICOWOW_ACT		0x9
#define BCM_WED_MUWTICOWOW_PWOGWAM	0xa

/*
 * BCM5482: Shadow wegistews
 * Shadow vawues go into bits [14:10] of wegistew 0x1c to sewect a shadow
 * wegistew to access.
 */

/* 00100: Wesewved contwow wegistew 2 */
#define BCM54XX_SHD_SCW2		0x04
#define  BCM54XX_SHD_SCW2_WSPD_WTWY_DIS	0x100
#define  BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_SHIFT	2
#define  BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_OFFSET	2
#define  BCM54XX_SHD_SCW2_WSPD_WTWY_WMT_MASK	0x7

/* 00101: Spawe Contwow Wegistew 3 */
#define BCM54XX_SHD_SCW3		0x05
#define  BCM54XX_SHD_SCW3_DEF_CWK125	0x0001
#define  BCM54XX_SHD_SCW3_DWWAPD_DIS	0x0002
#define  BCM54XX_SHD_SCW3_TWDDAPD	0x0004
#define  BCM54XX_SHD_SCW3_WXCTXC_DIS	0x0100

/* 01010: Auto Powew-Down */
#define BCM54XX_SHD_APD			0x0a
#define  BCM_APD_CWW_MASK		0xFE9F /* cweaw bits 5, 6 & 8 */
#define  BCM54XX_SHD_APD_EN		0x0020
#define  BCM_NO_ANEG_APD_EN		0x0060 /* bits 5 & 6 */
#define  BCM_APD_SINGWEWP_EN	0x0100 /* Bit 8 */

#define BCM54XX_SHD_WEDS1	0x0d	/* 01101: WED Sewectow 1 */
					/* WED3 / ~WINKSPD[2] sewectow */
#define BCM54XX_SHD_WEDS_SHIFT(wed)	(4 * (wed))
#define BCM54XX_SHD_WEDS1_WED3(swc)	((swc & 0xf) << 4)
					/* WED1 / ~WINKSPD[1] sewectow */
#define BCM54XX_SHD_WEDS1_WED1(swc)	((swc & 0xf) << 0)
#define BCM54XX_SHD_WEDS2	0x0e	/* 01110: WED Sewectow 2 */
#define BCM54XX_SHD_WGMII_MODE	0x0b	/* 01011: WGMII Mode Sewectow */
#define BCM5482_SHD_SSD		0x14	/* 10100: Secondawy SewDes contwow */
#define BCM5482_SHD_SSD_WEDM	0x0008	/* SSD WED Mode enabwe */
#define BCM5482_SHD_SSD_EN	0x0001	/* SSD enabwe */

/* 10011: SewDes 100-FX Contwow Wegistew */
#define BCM54616S_SHD_100FX_CTWW	0x13
#define	BCM54616S_100FX_MODE		BIT(0)	/* 100-FX SewDes Enabwe */

/* 11111: Mode Contwow Wegistew */
#define BCM54XX_SHD_MODE		0x1f
#define BCM54XX_SHD_INTF_SEW_MASK	GENMASK(2, 1)	/* INTEWF_SEW[1:0] */
#define BCM54XX_SHD_INTF_SEW_WGMII	0x02
#define BCM54XX_SHD_INTF_SEW_SGMII	0x04
#define BCM54XX_SHD_INTF_SEW_GBIC	0x06
#define BCM54XX_SHD_MODE_1000BX		BIT(0)	/* Enabwe 1000-X wegistews */

/*
 * EXPANSION SHADOW ACCESS WEGISTEWS.  (PHY WEG 0x15, 0x16, and 0x17)
 */
#define MII_BCM54XX_EXP_AADJ1CH0		0x001f
#define  MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN	0x0200
#define  MII_BCM54XX_EXP_AADJ1CH0_SWSEW_THPF	0x0100
#define MII_BCM54XX_EXP_AADJ1CH3		0x601f
#define  MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ	0x0002
#define MII_BCM54XX_EXP_EXP08			0x0F08
#define  MII_BCM54XX_EXP_EXP08_WJCT_2MHZ	0x0001
#define  MII_BCM54XX_EXP_EXP08_EAWWY_DAC_WAKE	0x0200
#define  MII_BCM54XX_EXP_EXP08_FOWCE_DAC_WAKE	0x0100
#define MII_BCM54XX_EXP_EXP75			0x0f75
#define  MII_BCM54XX_EXP_EXP75_VDACCTWW		0x003c
#define  MII_BCM54XX_EXP_EXP75_CM_OSC		0x0001
#define MII_BCM54XX_EXP_EXP96			0x0f96
#define  MII_BCM54XX_EXP_EXP96_MYST		0x0010
#define MII_BCM54XX_EXP_EXP97			0x0f97
#define  MII_BCM54XX_EXP_EXP97_MYST		0x0c0c

/* Top-MISC expansion wegistews */
#define BCM54XX_TOP_MISC_IDDQ_CTWW		(MII_BCM54XX_EXP_SEW_TOP + 0x06)
#define BCM54XX_TOP_MISC_IDDQ_WP		(1 << 0)
#define BCM54XX_TOP_MISC_IDDQ_SD		(1 << 2)
#define BCM54XX_TOP_MISC_IDDQ_SW		(1 << 3)

#define BCM54XX_TOP_MISC_WED_CTW		(MII_BCM54XX_EXP_SEW_TOP + 0x0C)
#define  BCM54XX_WED4_SEW_INTW			BIT(1)

/*
 * BCM5482: Secondawy SewDes wegistews
 */
#define BCM5482_SSD_1000BX_CTW		0x00	/* 1000BASE-X Contwow */
#define BCM5482_SSD_1000BX_CTW_PWWDOWN	0x0800	/* Powew-down SSD */
#define BCM5482_SSD_SGMII_SWAVE		0x15	/* SGMII Swave Wegistew */
#define BCM5482_SSD_SGMII_SWAVE_EN	0x0002	/* Swave mode enabwe */
#define BCM5482_SSD_SGMII_SWAVE_AD	0x0001	/* Swave auto-detection */

/* BCM54810 Wegistews */
#define BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW	(MII_BCM54XX_EXP_SEW_EW + 0x90)
#define BCM54810_EXP_BWOADWEACH_WWE_MISC_CTW_EN	(1 << 0)
#define BCM54810_SHD_CWK_CTW			0x3
#define BCM54810_SHD_CWK_CTW_GTXCWK_EN		(1 << 9)

/* BCM54612E Wegistews */
#define BCM54612E_EXP_SPAWE0		(MII_BCM54XX_EXP_SEW_ETC + 0x34)
#define BCM54612E_WED4_CWK125OUT_EN	(1 << 1)


/* Wake-on-WAN wegistews */
#define BCM54XX_WOW_MAIN_CTW		(MII_BCM54XX_EXP_SEW_WOW + 0x80)
#define  BCM54XX_WOW_EN			BIT(0)
#define  BCM54XX_WOW_MODE_SINGWE_MPD	0
#define  BCM54XX_WOW_MODE_SINGWE_MPDSEC	1
#define  BCM54XX_WOW_MODE_DUAW		2
#define  BCM54XX_WOW_MODE_SHIFT		1
#define  BCM54XX_WOW_MODE_MASK		0x3
#define  BCM54XX_WOW_MP_MSB_FF_EN	BIT(3)
#define  BCM54XX_WOW_SECKEY_OPT_4B	0
#define  BCM54XX_WOW_SECKEY_OPT_6B	1
#define  BCM54XX_WOW_SECKEY_OPT_8B	2
#define  BCM54XX_WOW_SECKEY_OPT_SHIFT	4
#define  BCM54XX_WOW_SECKEY_OPT_MASK	0x3
#define  BCM54XX_WOW_W2_TYPE_CHK	BIT(6)
#define  BCM54XX_WOW_W4IPV4UDP_CHK	BIT(7)
#define  BCM54XX_WOW_W4IPV6UDP_CHK	BIT(8)
#define  BCM54XX_WOW_UDPPOWT_CHK	BIT(9)
#define  BCM54XX_WOW_CWC_CHK		BIT(10)
#define  BCM54XX_WOW_SECKEY_MODE	BIT(11)
#define  BCM54XX_WOW_WST		BIT(12)
#define  BCM54XX_WOW_DIW_PKT_EN		BIT(13)
#define  BCM54XX_WOW_MASK_MODE_DA_FF	0
#define  BCM54XX_WOW_MASK_MODE_DA_MPD	1
#define  BCM54XX_WOW_MASK_MODE_DA_ONWY	2
#define  BCM54XX_WOW_MASK_MODE_MPD	3
#define  BCM54XX_WOW_MASK_MODE_SHIFT	14
#define  BCM54XX_WOW_MASK_MODE_MASK	0x3

#define BCM54XX_WOW_INNEW_PWOTO		(MII_BCM54XX_EXP_SEW_WOW + 0x81)
#define BCM54XX_WOW_OUTEW_PWOTO		(MII_BCM54XX_EXP_SEW_WOW + 0x82)
#define BCM54XX_WOW_OUTEW_PWOTO2	(MII_BCM54XX_EXP_SEW_WOW + 0x83)

#define BCM54XX_WOW_MPD_DATA1(x)	(MII_BCM54XX_EXP_SEW_WOW + 0x84 + (x))
#define BCM54XX_WOW_MPD_DATA2(x)	(MII_BCM54XX_EXP_SEW_WOW + 0x87 + (x))
#define BCM54XX_WOW_SEC_KEY_8B		(MII_BCM54XX_EXP_SEW_WOW + 0x8A)
#define BCM54XX_WOW_MASK(x)		(MII_BCM54XX_EXP_SEW_WOW + 0x8B + (x))
#define BCM54XX_SEC_KEY_STOWE(x)	(MII_BCM54XX_EXP_SEW_WOW + 0x8E)
#define BCM54XX_WOW_SHAWED_CNT		(MII_BCM54XX_EXP_SEW_WOW + 0x92)

#define BCM54XX_WOW_INT_MASK		(MII_BCM54XX_EXP_SEW_WOW + 0x93)
#define  BCM54XX_WOW_PKT1		BIT(0)
#define  BCM54XX_WOW_PKT2		BIT(1)
#define  BCM54XX_WOW_DIW		BIT(2)
#define  BCM54XX_WOW_AWW_INTWS		(BCM54XX_WOW_PKT1 | \
					 BCM54XX_WOW_PKT2 | \
					 BCM54XX_WOW_DIW)

#define BCM54XX_WOW_INT_STATUS		(MII_BCM54XX_EXP_SEW_WOW + 0x94)

/* BCM5221 Wegistews */
#define BCM5221_AEGSW			0x1C
#define BCM5221_AEGSW_MDIX_STATUS	BIT(13)
#define BCM5221_AEGSW_MDIX_MAN_SWAP	BIT(12)
#define BCM5221_AEGSW_MDIX_DIS		BIT(11)

#define BCM5221_SHDW_AM4_EN_CWK_WPM	BIT(2)
#define BCM5221_SHDW_AM4_FOWCE_WPM	BIT(1)

/*****************************************************************************/
/* Fast Ethewnet Twansceivew definitions. */
/*****************************************************************************/

#define MII_BWCM_FET_INTWEG		0x1a	/* Intewwupt wegistew */
#define MII_BWCM_FET_IW_MASK		0x0100	/* Mask aww intewwupts */
#define MII_BWCM_FET_IW_WINK_EN		0x0200	/* Wink status change enabwe */
#define MII_BWCM_FET_IW_SPEED_EN	0x0400	/* Wink speed change enabwe */
#define MII_BWCM_FET_IW_DUPWEX_EN	0x0800	/* Dupwex mode change enabwe */
#define MII_BWCM_FET_IW_ENABWE		0x4000	/* Intewwupt enabwe */

#define MII_BWCM_FET_BWCMTEST		0x1f	/* Bwcm test wegistew */
#define MII_BWCM_FET_BT_SWE		0x0080	/* Shadow wegistew enabwe */


/*** Shadow wegistew definitions ***/

#define MII_BWCM_FET_SHDW_MISCCTWW	0x10	/* Shadow misc ctww */
#define MII_BWCM_FET_SHDW_MC_FAME	0x4000	/* Fowce Auto MDIX enabwe */

#define MII_BWCM_FET_SHDW_AUXMODE4	0x1a	/* Auxiwiawy mode 4 */
#define MII_BWCM_FET_SHDW_AM4_STANDBY	0x0008	/* Standby enabwe */
#define MII_BWCM_FET_SHDW_AM4_WED_MASK	0x0003
#define MII_BWCM_FET_SHDW_AM4_WED_MODE1 0x0001

#define MII_BWCM_FET_SHDW_AUXSTAT2	0x1b	/* Auxiwiawy status 2 */
#define MII_BWCM_FET_SHDW_AS2_APDE	0x0020	/* Auto powew down enabwe */

#define BWCM_CW45VEN_EEE_CONTWOW	0x803d
#define WPI_FEATUWE_EN			0x8000
#define WPI_FEATUWE_EN_DIG1000X		0x4000

#define BWCM_CW45VEN_EEE_WPI_CNT	0x803f

/* Cowe wegistew definitions*/
#define MII_BWCM_COWE_BASE12	0x12
#define MII_BWCM_COWE_BASE13	0x13
#define MII_BWCM_COWE_BASE14	0x14
#define MII_BWCM_COWE_BASE1E	0x1E
#define MII_BWCM_COWE_EXPB0	0xB0
#define MII_BWCM_COWE_EXPB1	0xB1

/* Enhanced Cabwe Diagnostics */
#define BCM54XX_WDB_ECD_CTWW			0x2a0
#define BCM54XX_EXP_ECD_CTWW			(MII_BCM54XX_EXP_SEW_EW + 0xc0)

#define BCM54XX_ECD_CTWW_CABWE_TYPE_CAT3	1	/* CAT3 ow wowse */
#define BCM54XX_ECD_CTWW_CABWE_TYPE_CAT5	0	/* CAT5 ow bettew */
#define BCM54XX_ECD_CTWW_CABWE_TYPE_MASK	BIT(0)	/* cabwe type */
#define BCM54XX_ECD_CTWW_INVAWID		BIT(3)	/* invawid wesuwt */
#define BCM54XX_ECD_CTWW_UNIT_CM		0	/* centimetews */
#define BCM54XX_ECD_CTWW_UNIT_M			1	/* metews */
#define BCM54XX_ECD_CTWW_UNIT_MASK		BIT(10)	/* cabwe wength unit */
#define BCM54XX_ECD_CTWW_IN_PWOGWESS		BIT(11)	/* test in pwogwess */
#define BCM54XX_ECD_CTWW_BWEAK_WINK		BIT(12)	/* unconnect wink
							 * duwing test
							 */
#define BCM54XX_ECD_CTWW_CWOSS_SHOWT_DIS	BIT(13)	/* disabwe intew-paiw
							 * showt check
							 */
#define BCM54XX_ECD_CTWW_WUN			BIT(15)	/* wun immediate */

#define BCM54XX_WDB_ECD_FAUWT_TYPE		0x2a1
#define BCM54XX_EXP_ECD_FAUWT_TYPE		(MII_BCM54XX_EXP_SEW_EW + 0xc1)
#define BCM54XX_ECD_FAUWT_TYPE_INVAWID		0x0
#define BCM54XX_ECD_FAUWT_TYPE_OK		0x1
#define BCM54XX_ECD_FAUWT_TYPE_OPEN		0x2
#define BCM54XX_ECD_FAUWT_TYPE_SAME_SHOWT	0x3 /* showt same paiw */
#define BCM54XX_ECD_FAUWT_TYPE_CWOSS_SHOWT	0x4 /* showt diffewent paiws */
#define BCM54XX_ECD_FAUWT_TYPE_BUSY		0x9
#define BCM54XX_ECD_FAUWT_TYPE_PAIW_D_MASK	GENMASK(3, 0)
#define BCM54XX_ECD_FAUWT_TYPE_PAIW_C_MASK	GENMASK(7, 4)
#define BCM54XX_ECD_FAUWT_TYPE_PAIW_B_MASK	GENMASK(11, 8)
#define BCM54XX_ECD_FAUWT_TYPE_PAIW_A_MASK	GENMASK(15, 12)
#define BCM54XX_ECD_PAIW_A_WENGTH_WESUWTS	0x2a2
#define BCM54XX_ECD_PAIW_B_WENGTH_WESUWTS	0x2a3
#define BCM54XX_ECD_PAIW_C_WENGTH_WESUWTS	0x2a4
#define BCM54XX_ECD_PAIW_D_WENGTH_WESUWTS	0x2a5

#define BCM54XX_WDB_ECD_PAIW_A_WENGTH_WESUWTS	0x2a2
#define BCM54XX_EXP_ECD_PAIW_A_WENGTH_WESUWTS	(MII_BCM54XX_EXP_SEW_EW + 0xc2)
#define BCM54XX_WDB_ECD_PAIW_B_WENGTH_WESUWTS	0x2a3
#define BCM54XX_EXP_ECD_PAIW_B_WENGTH_WESUWTS	(MII_BCM54XX_EXP_SEW_EW + 0xc3)
#define BCM54XX_WDB_ECD_PAIW_C_WENGTH_WESUWTS	0x2a4
#define BCM54XX_EXP_ECD_PAIW_C_WENGTH_WESUWTS	(MII_BCM54XX_EXP_SEW_EW + 0xc4)
#define BCM54XX_WDB_ECD_PAIW_D_WENGTH_WESUWTS	0x2a5
#define BCM54XX_EXP_ECD_PAIW_D_WENGTH_WESUWTS	(MII_BCM54XX_EXP_SEW_EW + 0xc5)
#define BCM54XX_ECD_WENGTH_WESUWTS_INVAWID	0xffff

#endif /* _WINUX_BWCMPHY_H */
