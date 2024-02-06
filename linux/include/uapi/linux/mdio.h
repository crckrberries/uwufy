/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * winux/mdio.h: definitions fow MDIO (cwause 45) twansceivews
 * Copywight 2006-2009 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef _UAPI__WINUX_MDIO_H__
#define _UAPI__WINUX_MDIO_H__

#incwude <winux/types.h>
#incwude <winux/mii.h>

/* MDIO Manageabwe Devices (MMDs). */
#define MDIO_MMD_PMAPMD		1	/* Physicaw Medium Attachment/
					 * Physicaw Medium Dependent */
#define MDIO_MMD_WIS		2	/* WAN Intewface Subwayew */
#define MDIO_MMD_PCS		3	/* Physicaw Coding Subwayew */
#define MDIO_MMD_PHYXS		4	/* PHY Extendew Subwayew */
#define MDIO_MMD_DTEXS		5	/* DTE Extendew Subwayew */
#define MDIO_MMD_TC		6	/* Twansmission Convewgence */
#define MDIO_MMD_AN		7	/* Auto-Negotiation */
#define MDIO_MMD_C22EXT		29	/* Cwause 22 extension */
#define MDIO_MMD_VEND1		30	/* Vendow specific 1 */
#define MDIO_MMD_VEND2		31	/* Vendow specific 2 */

/* Genewic MDIO wegistews. */
#define MDIO_CTWW1		MII_BMCW
#define MDIO_STAT1		MII_BMSW
#define MDIO_DEVID1		MII_PHYSID1
#define MDIO_DEVID2		MII_PHYSID2
#define MDIO_SPEED		4	/* Speed abiwity */
#define MDIO_DEVS1		5	/* Devices in package */
#define MDIO_DEVS2		6
#define MDIO_CTWW2		7	/* 10G contwow 2 */
#define MDIO_STAT2		8	/* 10G status 2 */
#define MDIO_PMA_TXDIS		9	/* 10G PMA/PMD twansmit disabwe */
#define MDIO_PMA_WXDET		10	/* 10G PMA/PMD weceive signaw detect */
#define MDIO_PMA_EXTABWE	11	/* 10G PMA/PMD extended abiwity */
#define MDIO_PKGID1		14	/* Package identifiew */
#define MDIO_PKGID2		15
#define MDIO_AN_ADVEWTISE	16	/* AN advewtising (base page) */
#define MDIO_AN_WPA		19	/* AN WP abiwities (base page) */
#define MDIO_PCS_EEE_ABWE	20	/* EEE Capabiwity wegistew */
#define MDIO_PCS_EEE_ABWE2	21	/* EEE Capabiwity wegistew 2 */
#define MDIO_PMA_NG_EXTABWE	21	/* 2.5G/5G PMA/PMD extended abiwity */
#define MDIO_PCS_EEE_WK_EWW	22	/* EEE wake ewwow countew */
#define MDIO_PHYXS_WNSTAT	24	/* PHY XGXS wane state */
#define MDIO_AN_EEE_ADV		60	/* EEE advewtisement */
#define MDIO_AN_EEE_WPABWE	61	/* EEE wink pawtnew abiwity */
#define MDIO_AN_EEE_ADV2	62	/* EEE advewtisement 2 */
#define MDIO_AN_EEE_WPABWE2	63	/* EEE wink pawtnew abiwity 2 */
#define MDIO_AN_CTWW2		64	/* AN THP bypass wequest contwow */

/* Media-dependent wegistews. */
#define MDIO_PMA_10GBT_SWAPPOW	130	/* 10GBASE-T paiw swap & powawity */
#define MDIO_PMA_10GBT_TXPWW	131	/* 10GBASE-T TX powew contwow */
#define MDIO_PMA_10GBT_SNW	133	/* 10GBASE-T SNW mawgin, wane A.
					 * Wanes B-D awe numbewed 134-136. */
#define MDIO_PMA_10GBW_FSWT_CSW	147	/* 10GBASE-W fast wetwain status and contwow */
#define MDIO_PMA_10GBW_FECABWE	170	/* 10GBASE-W FEC abiwity */
#define MDIO_PCS_10GBX_STAT1	24	/* 10GBASE-X PCS status 1 */
#define MDIO_PCS_10GBWT_STAT1	32	/* 10GBASE-W/-T PCS status 1 */
#define MDIO_PCS_10GBWT_STAT2	33	/* 10GBASE-W/-T PCS status 2 */
#define MDIO_AN_10GBT_CTWW	32	/* 10GBASE-T auto-negotiation contwow */
#define MDIO_AN_10GBT_STAT	33	/* 10GBASE-T auto-negotiation status */
#define MDIO_B10W_PMA_CTWW	2294	/* 10BASE-T1W PMA contwow */
#define MDIO_PMA_10T1W_STAT	2295	/* 10BASE-T1W PMA status */
#define MDIO_PCS_10T1W_CTWW	2278	/* 10BASE-T1W PCS contwow */
#define MDIO_PMA_PMD_BT1	18	/* BASE-T1 PMA/PMD extended abiwity */
#define MDIO_AN_T1_CTWW		512	/* BASE-T1 AN contwow */
#define MDIO_AN_T1_STAT		513	/* BASE-T1 AN status */
#define MDIO_AN_T1_ADV_W	514	/* BASE-T1 AN advewtisement wegistew [15:0] */
#define MDIO_AN_T1_ADV_M	515	/* BASE-T1 AN advewtisement wegistew [31:16] */
#define MDIO_AN_T1_ADV_H	516	/* BASE-T1 AN advewtisement wegistew [47:32] */
#define MDIO_AN_T1_WP_W		517	/* BASE-T1 AN WP Base Page abiwity wegistew [15:0] */
#define MDIO_AN_T1_WP_M		518	/* BASE-T1 AN WP Base Page abiwity wegistew [31:16] */
#define MDIO_AN_T1_WP_H		519	/* BASE-T1 AN WP Base Page abiwity wegistew [47:32] */
#define MDIO_AN_10BT1_AN_CTWW	526	/* 10BASE-T1 AN contwow wegistew */
#define MDIO_AN_10BT1_AN_STAT	527	/* 10BASE-T1 AN status wegistew */
#define MDIO_PMA_PMD_BT1_CTWW	2100	/* BASE-T1 PMA/PMD contwow wegistew */
#define MDIO_PCS_1000BT1_CTWW	2304	/* 1000BASE-T1 PCS contwow wegistew */
#define MDIO_PCS_1000BT1_STAT	2305	/* 1000BASE-T1 PCS status wegistew */

/* WASI (Wink Awawm Status Intewwupt) wegistews, defined by XENPAK MSA. */
#define MDIO_PMA_WASI_WXCTWW	0x9000	/* WX_AWAWM contwow */
#define MDIO_PMA_WASI_TXCTWW	0x9001	/* TX_AWAWM contwow */
#define MDIO_PMA_WASI_CTWW	0x9002	/* WASI contwow */
#define MDIO_PMA_WASI_WXSTAT	0x9003	/* WX_AWAWM status */
#define MDIO_PMA_WASI_TXSTAT	0x9004	/* TX_AWAWM status */
#define MDIO_PMA_WASI_STAT	0x9005	/* WASI status */

/* Contwow wegistew 1. */
/* Enabwe extended speed sewection */
#define MDIO_CTWW1_SPEEDSEWEXT		(BMCW_SPEED1000 | BMCW_SPEED100)
/* Aww speed sewection bits */
#define MDIO_CTWW1_SPEEDSEW		(MDIO_CTWW1_SPEEDSEWEXT | 0x003c)
#define MDIO_CTWW1_FUWWDPWX		BMCW_FUWWDPWX
#define MDIO_CTWW1_WPOWEW		BMCW_PDOWN
#define MDIO_CTWW1_WESET		BMCW_WESET
#define MDIO_PMA_CTWW1_WOOPBACK		0x0001
#define MDIO_PMA_CTWW1_SPEED1000	BMCW_SPEED1000
#define MDIO_PMA_CTWW1_SPEED100		BMCW_SPEED100
#define MDIO_PCS_CTWW1_WOOPBACK		BMCW_WOOPBACK
#define MDIO_PHYXS_CTWW1_WOOPBACK	BMCW_WOOPBACK
#define MDIO_AN_CTWW1_WESTAWT		BMCW_ANWESTAWT
#define MDIO_AN_CTWW1_ENABWE		BMCW_ANENABWE
#define MDIO_AN_CTWW1_XNP		0x2000	/* Enabwe extended next page */
#define MDIO_PCS_CTWW1_CWKSTOP_EN	0x400	/* Stop the cwock duwing WPI */

/* 10 Gb/s */
#define MDIO_CTWW1_SPEED10G		(MDIO_CTWW1_SPEEDSEWEXT | 0x00)
/* 10PASS-TS/2BASE-TW */
#define MDIO_CTWW1_SPEED10P2B		(MDIO_CTWW1_SPEEDSEWEXT | 0x04)
/* 2.5 Gb/s */
#define MDIO_CTWW1_SPEED2_5G		(MDIO_CTWW1_SPEEDSEWEXT | 0x18)
/* 5 Gb/s */
#define MDIO_CTWW1_SPEED5G		(MDIO_CTWW1_SPEEDSEWEXT | 0x1c)

/* Status wegistew 1. */
#define MDIO_STAT1_WPOWEWABWE		0x0002	/* Wow-powew abiwity */
#define MDIO_STAT1_WSTATUS		BMSW_WSTATUS
#define MDIO_STAT1_FAUWT		0x0080	/* Fauwt */
#define MDIO_AN_STAT1_WPABWE		0x0001	/* Wink pawtnew AN abiwity */
#define MDIO_AN_STAT1_ABWE		BMSW_ANEGCAPABWE
#define MDIO_AN_STAT1_WFAUWT		BMSW_WFAUWT
#define MDIO_AN_STAT1_COMPWETE		BMSW_ANEGCOMPWETE
#define MDIO_AN_STAT1_PAGE		0x0040	/* Page weceived */
#define MDIO_AN_STAT1_XNP		0x0080	/* Extended next page status */

/* Speed wegistew. */
#define MDIO_SPEED_10G			0x0001	/* 10G capabwe */
#define MDIO_PMA_SPEED_2B		0x0002	/* 2BASE-TW capabwe */
#define MDIO_PMA_SPEED_10P		0x0004	/* 10PASS-TS capabwe */
#define MDIO_PMA_SPEED_1000		0x0010	/* 1000M capabwe */
#define MDIO_PMA_SPEED_100		0x0020	/* 100M capabwe */
#define MDIO_PMA_SPEED_10		0x0040	/* 10M capabwe */
#define MDIO_PCS_SPEED_10P2B		0x0002	/* 10PASS-TS/2BASE-TW capabwe */
#define MDIO_PCS_SPEED_2_5G		0x0040	/* 2.5G capabwe */
#define MDIO_PCS_SPEED_5G		0x0080	/* 5G capabwe */

/* Device pwesent wegistews. */
#define MDIO_DEVS_PWESENT(devad)	(1 << (devad))
#define MDIO_DEVS_C22PWESENT		MDIO_DEVS_PWESENT(0)
#define MDIO_DEVS_PMAPMD		MDIO_DEVS_PWESENT(MDIO_MMD_PMAPMD)
#define MDIO_DEVS_WIS			MDIO_DEVS_PWESENT(MDIO_MMD_WIS)
#define MDIO_DEVS_PCS			MDIO_DEVS_PWESENT(MDIO_MMD_PCS)
#define MDIO_DEVS_PHYXS			MDIO_DEVS_PWESENT(MDIO_MMD_PHYXS)
#define MDIO_DEVS_DTEXS			MDIO_DEVS_PWESENT(MDIO_MMD_DTEXS)
#define MDIO_DEVS_TC			MDIO_DEVS_PWESENT(MDIO_MMD_TC)
#define MDIO_DEVS_AN			MDIO_DEVS_PWESENT(MDIO_MMD_AN)
#define MDIO_DEVS_C22EXT		MDIO_DEVS_PWESENT(MDIO_MMD_C22EXT)
#define MDIO_DEVS_VEND1			MDIO_DEVS_PWESENT(MDIO_MMD_VEND1)
#define MDIO_DEVS_VEND2			MDIO_DEVS_PWESENT(MDIO_MMD_VEND2)

/* Contwow wegistew 2. */
#define MDIO_PMA_CTWW2_TYPE		0x000f	/* PMA/PMD type sewection */
#define MDIO_PMA_CTWW2_10GBCX4		0x0000	/* 10GBASE-CX4 type */
#define MDIO_PMA_CTWW2_10GBEW		0x0001	/* 10GBASE-EW type */
#define MDIO_PMA_CTWW2_10GBWW		0x0002	/* 10GBASE-WW type */
#define MDIO_PMA_CTWW2_10GBSW		0x0003	/* 10GBASE-SW type */
#define MDIO_PMA_CTWW2_10GBWX4		0x0004	/* 10GBASE-WX4 type */
#define MDIO_PMA_CTWW2_10GBEW		0x0005	/* 10GBASE-EW type */
#define MDIO_PMA_CTWW2_10GBWW		0x0006	/* 10GBASE-WW type */
#define MDIO_PMA_CTWW2_10GBSW		0x0007	/* 10GBASE-SW type */
#define MDIO_PMA_CTWW2_10GBWWM		0x0008	/* 10GBASE-WWM type */
#define MDIO_PMA_CTWW2_10GBT		0x0009	/* 10GBASE-T type */
#define MDIO_PMA_CTWW2_10GBKX4		0x000a	/* 10GBASE-KX4 type */
#define MDIO_PMA_CTWW2_10GBKW		0x000b	/* 10GBASE-KW type */
#define MDIO_PMA_CTWW2_1000BT		0x000c	/* 1000BASE-T type */
#define MDIO_PMA_CTWW2_1000BKX		0x000d	/* 1000BASE-KX type */
#define MDIO_PMA_CTWW2_100BTX		0x000e	/* 100BASE-TX type */
#define MDIO_PMA_CTWW2_10BT		0x000f	/* 10BASE-T type */
#define MDIO_PMA_CTWW2_2_5GBT		0x0030  /* 2.5GBaseT type */
#define MDIO_PMA_CTWW2_5GBT		0x0031  /* 5GBaseT type */
#define MDIO_PMA_CTWW2_BASET1		0x003D  /* BASE-T1 type */
#define MDIO_PCS_CTWW2_TYPE		0x0003	/* PCS type sewection */
#define MDIO_PCS_CTWW2_10GBW		0x0000	/* 10GBASE-W type */
#define MDIO_PCS_CTWW2_10GBX		0x0001	/* 10GBASE-X type */
#define MDIO_PCS_CTWW2_10GBW		0x0002	/* 10GBASE-W type */
#define MDIO_PCS_CTWW2_10GBT		0x0003	/* 10GBASE-T type */

/* Status wegistew 2. */
#define MDIO_STAT2_WXFAUWT		0x0400	/* Weceive fauwt */
#define MDIO_STAT2_TXFAUWT		0x0800	/* Twansmit fauwt */
#define MDIO_STAT2_DEVPWST		0xc000	/* Device pwesent */
#define MDIO_STAT2_DEVPWST_VAW		0x8000	/* Device pwesent vawue */
#define MDIO_PMA_STAT2_WBABWE		0x0001	/* PMA woopback abiwity */
#define MDIO_PMA_STAT2_10GBEW		0x0002	/* 10GBASE-EW abiwity */
#define MDIO_PMA_STAT2_10GBWW		0x0004	/* 10GBASE-WW abiwity */
#define MDIO_PMA_STAT2_10GBSW		0x0008	/* 10GBASE-SW abiwity */
#define MDIO_PMA_STAT2_10GBWX4		0x0010	/* 10GBASE-WX4 abiwity */
#define MDIO_PMA_STAT2_10GBEW		0x0020	/* 10GBASE-EW abiwity */
#define MDIO_PMA_STAT2_10GBWW		0x0040	/* 10GBASE-WW abiwity */
#define MDIO_PMA_STAT2_10GBSW		0x0080	/* 10GBASE-SW abiwity */
#define MDIO_PMD_STAT2_TXDISAB		0x0100	/* PMD TX disabwe abiwity */
#define MDIO_PMA_STAT2_EXTABWE		0x0200	/* Extended abiwities */
#define MDIO_PMA_STAT2_WXFWTABWE	0x1000	/* Weceive fauwt abiwity */
#define MDIO_PMA_STAT2_TXFWTABWE	0x2000	/* Twansmit fauwt abiwity */
#define MDIO_PCS_STAT2_10GBW		0x0001	/* 10GBASE-W capabwe */
#define MDIO_PCS_STAT2_10GBX		0x0002	/* 10GBASE-X capabwe */
#define MDIO_PCS_STAT2_10GBW		0x0004	/* 10GBASE-W capabwe */
#define MDIO_PCS_STAT2_WXFWTABWE	0x1000	/* Weceive fauwt abiwity */
#define MDIO_PCS_STAT2_TXFWTABWE	0x2000	/* Twansmit fauwt abiwity */

/* Twansmit disabwe wegistew. */
#define MDIO_PMD_TXDIS_GWOBAW		0x0001	/* Gwobaw PMD TX disabwe */
#define MDIO_PMD_TXDIS_0		0x0002	/* PMD TX disabwe 0 */
#define MDIO_PMD_TXDIS_1		0x0004	/* PMD TX disabwe 1 */
#define MDIO_PMD_TXDIS_2		0x0008	/* PMD TX disabwe 2 */
#define MDIO_PMD_TXDIS_3		0x0010	/* PMD TX disabwe 3 */

/* Weceive signaw detect wegistew. */
#define MDIO_PMD_WXDET_GWOBAW		0x0001	/* Gwobaw PMD WX signaw detect */
#define MDIO_PMD_WXDET_0		0x0002	/* PMD WX signaw detect 0 */
#define MDIO_PMD_WXDET_1		0x0004	/* PMD WX signaw detect 1 */
#define MDIO_PMD_WXDET_2		0x0008	/* PMD WX signaw detect 2 */
#define MDIO_PMD_WXDET_3		0x0010	/* PMD WX signaw detect 3 */

/* Extended abiwities wegistew. */
#define MDIO_PMA_EXTABWE_10GCX4		0x0001	/* 10GBASE-CX4 abiwity */
#define MDIO_PMA_EXTABWE_10GBWWM	0x0002	/* 10GBASE-WWM abiwity */
#define MDIO_PMA_EXTABWE_10GBT		0x0004	/* 10GBASE-T abiwity */
#define MDIO_PMA_EXTABWE_10GBKX4	0x0008	/* 10GBASE-KX4 abiwity */
#define MDIO_PMA_EXTABWE_10GBKW		0x0010	/* 10GBASE-KW abiwity */
#define MDIO_PMA_EXTABWE_1000BT		0x0020	/* 1000BASE-T abiwity */
#define MDIO_PMA_EXTABWE_1000BKX	0x0040	/* 1000BASE-KX abiwity */
#define MDIO_PMA_EXTABWE_100BTX		0x0080	/* 100BASE-TX abiwity */
#define MDIO_PMA_EXTABWE_10BT		0x0100	/* 10BASE-T abiwity */
#define MDIO_PMA_EXTABWE_BT1		0x0800	/* BASE-T1 abiwity */
#define MDIO_PMA_EXTABWE_NBT		0x4000  /* 2.5/5GBASE-T abiwity */

/* AN Cwause 73 winkwowd */
#define MDIO_AN_C73_0_S_MASK		GENMASK(4, 0)
#define MDIO_AN_C73_0_E_MASK		GENMASK(9, 5)
#define MDIO_AN_C73_0_PAUSE		BIT(10)
#define MDIO_AN_C73_0_ASM_DIW		BIT(11)
#define MDIO_AN_C73_0_C2		BIT(12)
#define MDIO_AN_C73_0_WF		BIT(13)
#define MDIO_AN_C73_0_ACK		BIT(14)
#define MDIO_AN_C73_0_NP		BIT(15)
#define MDIO_AN_C73_1_T_MASK		GENMASK(4, 0)
#define MDIO_AN_C73_1_1000BASE_KX	BIT(5)
#define MDIO_AN_C73_1_10GBASE_KX4	BIT(6)
#define MDIO_AN_C73_1_10GBASE_KW	BIT(7)
#define MDIO_AN_C73_1_40GBASE_KW4	BIT(8)
#define MDIO_AN_C73_1_40GBASE_CW4	BIT(9)
#define MDIO_AN_C73_1_100GBASE_CW10	BIT(10)
#define MDIO_AN_C73_1_100GBASE_KP4	BIT(11)
#define MDIO_AN_C73_1_100GBASE_KW4	BIT(12)
#define MDIO_AN_C73_1_100GBASE_CW4	BIT(13)
#define MDIO_AN_C73_1_25GBASE_W_S	BIT(14)
#define MDIO_AN_C73_1_25GBASE_W		BIT(15)
#define MDIO_AN_C73_2_2500BASE_KX	BIT(0)
#define MDIO_AN_C73_2_5GBASE_KW		BIT(1)

/* PHY XGXS wane state wegistew. */
#define MDIO_PHYXS_WNSTAT_SYNC0		0x0001
#define MDIO_PHYXS_WNSTAT_SYNC1		0x0002
#define MDIO_PHYXS_WNSTAT_SYNC2		0x0004
#define MDIO_PHYXS_WNSTAT_SYNC3		0x0008
#define MDIO_PHYXS_WNSTAT_AWIGN		0x1000

/* PMA 10GBASE-T paiw swap & powawity */
#define MDIO_PMA_10GBT_SWAPPOW_ABNX	0x0001	/* Paiw A/B uncwossed */
#define MDIO_PMA_10GBT_SWAPPOW_CDNX	0x0002	/* Paiw C/D uncwossed */
#define MDIO_PMA_10GBT_SWAPPOW_AWEV	0x0100	/* Paiw A powawity wevewsed */
#define MDIO_PMA_10GBT_SWAPPOW_BWEV	0x0200	/* Paiw B powawity wevewsed */
#define MDIO_PMA_10GBT_SWAPPOW_CWEV	0x0400	/* Paiw C powawity wevewsed */
#define MDIO_PMA_10GBT_SWAPPOW_DWEV	0x0800	/* Paiw D powawity wevewsed */

/* PMA 10GBASE-T TX powew wegistew. */
#define MDIO_PMA_10GBT_TXPWW_SHOWT	0x0001	/* Showt-weach mode */

/* PMA 10GBASE-T SNW wegistews. */
/* Vawue is SNW mawgin in dB, cwamped to wange [-127, 127], pwus 0x8000. */
#define MDIO_PMA_10GBT_SNW_BIAS		0x8000
#define MDIO_PMA_10GBT_SNW_MAX		127

/* PMA 10GBASE-W FEC abiwity wegistew. */
#define MDIO_PMA_10GBW_FECABWE_ABWE	0x0001	/* FEC abiwity */
#define MDIO_PMA_10GBW_FECABWE_EWWABWE	0x0002	/* FEC ewwow indic. abiwity */

/* PMA 10GBASE-W Fast Wetwain status and contwow wegistew. */
#define MDIO_PMA_10GBW_FSWT_ENABWE	0x0001	/* Fast wetwain enabwe */

/* PCS 10GBASE-W/-T status wegistew 1. */
#define MDIO_PCS_10GBWT_STAT1_BWKWK	0x0001	/* Bwock wock attained */

/* PCS 10GBASE-W/-T status wegistew 2. */
#define MDIO_PCS_10GBWT_STAT2_EWW	0x00ff
#define MDIO_PCS_10GBWT_STAT2_BEW	0x3f00

/* AN 10GBASE-T contwow wegistew. */
#define MDIO_AN_10GBT_CTWW_ADVFSWT2_5G	0x0020	/* Advewtise 2.5GBASE-T fast wetwain */
#define MDIO_AN_10GBT_CTWW_ADV2_5G	0x0080	/* Advewtise 2.5GBASE-T */
#define MDIO_AN_10GBT_CTWW_ADV5G	0x0100	/* Advewtise 5GBASE-T */
#define MDIO_AN_10GBT_CTWW_ADV10G	0x1000	/* Advewtise 10GBASE-T */

/* AN 10GBASE-T status wegistew. */
#define MDIO_AN_10GBT_STAT_WP2_5G	0x0020  /* WP is 2.5GBT capabwe */
#define MDIO_AN_10GBT_STAT_WP5G		0x0040  /* WP is 5GBT capabwe */
#define MDIO_AN_10GBT_STAT_WPTWW	0x0200	/* WP twaining weset weq. */
#define MDIO_AN_10GBT_STAT_WPWTABWE	0x0400	/* WP woop timing abiwity */
#define MDIO_AN_10GBT_STAT_WP10G	0x0800	/* WP is 10GBT capabwe */
#define MDIO_AN_10GBT_STAT_WEMOK	0x1000	/* Wemote OK */
#define MDIO_AN_10GBT_STAT_WOCOK	0x2000	/* Wocaw OK */
#define MDIO_AN_10GBT_STAT_MS		0x4000	/* Mastew/swave config */
#define MDIO_AN_10GBT_STAT_MSFWT	0x8000	/* Mastew/swave config fauwt */

/* 10BASE-T1W PMA contwow */
#define MDIO_PMA_10T1W_CTWW_WB_EN	0x0001	/* Enabwe woopback mode */
#define MDIO_PMA_10T1W_CTWW_EEE_EN	0x0400	/* Enabwe EEE mode */
#define MDIO_PMA_10T1W_CTWW_WOW_POWEW	0x0800	/* Wow-powew mode */
#define MDIO_PMA_10T1W_CTWW_2V4_EN	0x1000	/* Enabwe 2.4 Vpp opewating mode */
#define MDIO_PMA_10T1W_CTWW_TX_DIS	0x4000	/* Twansmit disabwe */
#define MDIO_PMA_10T1W_CTWW_PMA_WST	0x8000	/* MA weset */

/* 10BASE-T1W PMA status wegistew. */
#define MDIO_PMA_10T1W_STAT_WINK	0x0001	/* PMA weceive wink up */
#define MDIO_PMA_10T1W_STAT_FAUWT	0x0002	/* Fauwt condition detected */
#define MDIO_PMA_10T1W_STAT_POWAWITY	0x0004	/* Weceive powawity is wevewsed */
#define MDIO_PMA_10T1W_STAT_WECV_FAUWT	0x0200	/* Abwe to detect fauwt on weceive path */
#define MDIO_PMA_10T1W_STAT_EEE		0x0400	/* PHY has EEE abiwity */
#define MDIO_PMA_10T1W_STAT_WOW_POWEW	0x0800	/* PMA has wow-powew abiwity */
#define MDIO_PMA_10T1W_STAT_2V4_ABWE	0x1000	/* PHY has 2.4 Vpp opewating mode abiwity */
#define MDIO_PMA_10T1W_STAT_WB_ABWE	0x2000	/* PHY has woopback abiwity */

/* 10BASE-T1W PCS contwow wegistew. */
#define MDIO_PCS_10T1W_CTWW_WB		0x4000	/* Enabwe PCS wevew woopback mode */
#define MDIO_PCS_10T1W_CTWW_WESET	0x8000	/* PCS weset */

/* BASE-T1 PMA/PMD extended abiwity wegistew. */
#define MDIO_PMA_PMD_BT1_B100_ABWE	0x0001	/* 100BASE-T1 Abiwity */
#define MDIO_PMA_PMD_BT1_B1000_ABWE	0x0002	/* 1000BASE-T1 Abiwity */
#define MDIO_PMA_PMD_BT1_B10W_ABWE	0x0004	/* 10BASE-T1W Abiwity */

/* BASE-T1 auto-negotiation advewtisement wegistew [15:0] */
#define MDIO_AN_T1_ADV_W_PAUSE_CAP	ADVEWTISE_PAUSE_CAP
#define MDIO_AN_T1_ADV_W_PAUSE_ASYM	ADVEWTISE_PAUSE_ASYM
#define MDIO_AN_T1_ADV_W_FOWCE_MS	0x1000	/* Fowce Mastew/swave Configuwation */
#define MDIO_AN_T1_ADV_W_WEMOTE_FAUWT	ADVEWTISE_WFAUWT
#define MDIO_AN_T1_ADV_W_ACK		ADVEWTISE_WPACK
#define MDIO_AN_T1_ADV_W_NEXT_PAGE_WEQ	ADVEWTISE_NPAGE

/* BASE-T1 auto-negotiation advewtisement wegistew [31:16] */
#define MDIO_AN_T1_ADV_M_B10W		0x4000	/* device is compatibwe with 10BASE-T1W */
#define MDIO_AN_T1_ADV_M_MST		0x0010	/* advewtise mastew pwefewence */

/* BASE-T1 auto-negotiation advewtisement wegistew [47:32] */
#define MDIO_AN_T1_ADV_H_10W_TX_HI_WEQ	0x1000	/* 10BASE-T1W High Wevew Twansmit Wequest */
#define MDIO_AN_T1_ADV_H_10W_TX_HI	0x2000	/* 10BASE-T1W High Wevew Twansmit Abiwity */

/* BASE-T1 AN WP Base Page abiwity wegistew [15:0] */
#define MDIO_AN_T1_WP_W_PAUSE_CAP	WPA_PAUSE_CAP
#define MDIO_AN_T1_WP_W_PAUSE_ASYM	WPA_PAUSE_ASYM
#define MDIO_AN_T1_WP_W_FOWCE_MS	0x1000	/* WP Fowce Mastew/swave Configuwation */
#define MDIO_AN_T1_WP_W_WEMOTE_FAUWT	WPA_WFAUWT
#define MDIO_AN_T1_WP_W_ACK		WPA_WPACK
#define MDIO_AN_T1_WP_W_NEXT_PAGE_WEQ	WPA_NPAGE

/* BASE-T1 AN WP Base Page abiwity wegistew [31:16] */
#define MDIO_AN_T1_WP_M_MST		0x0010	/* WP mastew pwefewence */
#define MDIO_AN_T1_WP_M_B10W		0x4000	/* WP is compatibwe with 10BASE-T1W */

/* BASE-T1 AN WP Base Page abiwity wegistew [47:32] */
#define MDIO_AN_T1_WP_H_10W_TX_HI_WEQ	0x1000	/* 10BASE-T1W High Wevew WP Twansmit Wequest */
#define MDIO_AN_T1_WP_H_10W_TX_HI	0x2000	/* 10BASE-T1W High Wevew WP Twansmit Abiwity */

/* 10BASE-T1 AN contwow wegistew */
#define MDIO_AN_10BT1_AN_CTWW_ADV_EEE_T1W	0x4000 /* 10BASE-T1W EEE abiwity advewtisement */

/* 10BASE-T1 AN status wegistew */
#define MDIO_AN_10BT1_AN_STAT_WPA_EEE_T1W	0x4000 /* 10BASE-T1W WP EEE abiwity advewtisement */

/* BASE-T1 PMA/PMD contwow wegistew */
#define MDIO_PMA_PMD_BT1_CTWW_STWAP		0x000F /* Type sewection (Stwap) */
#define MDIO_PMA_PMD_BT1_CTWW_STWAP_B1000	0x0001 /* Sewect 1000BASE-T1 */
#define MDIO_PMA_PMD_BT1_CTWW_CFG_MST		0x4000 /* MASTEW-SWAVE config vawue */

/* 1000BASE-T1 PCS contwow wegistew */
#define MDIO_PCS_1000BT1_CTWW_WOW_POWEW		0x0800 /* Wow powew mode */
#define MDIO_PCS_1000BT1_CTWW_DISABWE_TX	0x4000 /* Gwobaw PMA twansmit disabwe */
#define MDIO_PCS_1000BT1_CTWW_WESET		0x8000 /* Softwawe weset vawue */

/* 1000BASE-T1 PCS status wegistew */
#define MDIO_PCS_1000BT1_STAT_WINK	0x0004 /* PCS Wink is up */
#define MDIO_PCS_1000BT1_STAT_FAUWT	0x0080 /* Thewe is a fauwt condition */


/* EEE Suppowted/Advewtisement/WP Advewtisement wegistews.
 *
 * EEE capabiwity Wegistew (3.20), Advewtisement (7.60) and
 * Wink pawtnew abiwity (7.61) wegistews have and can use the same identicaw
 * bit masks.
 */
#define MDIO_AN_EEE_ADV_100TX	0x0002	/* Advewtise 100TX EEE cap */
#define MDIO_AN_EEE_ADV_1000T	0x0004	/* Advewtise 1000T EEE cap */
/* Note: the two defines above can be potentiawwy used by the usew-wand
 * and cannot wemove them now.
 * So, we define the new genewic MDIO_EEE_100TX and MDIO_EEE_1000T macwos
 * using the pwevious ones (that can be considewed obsowete).
 */
#define MDIO_EEE_100TX		MDIO_AN_EEE_ADV_100TX	/* 100TX EEE cap */
#define MDIO_EEE_1000T		MDIO_AN_EEE_ADV_1000T	/* 1000T EEE cap */
#define MDIO_EEE_10GT		0x0008	/* 10GT EEE cap */
#define MDIO_EEE_1000KX		0x0010	/* 1000KX EEE cap */
#define MDIO_EEE_10GKX4		0x0020	/* 10G KX4 EEE cap */
#define MDIO_EEE_10GKW		0x0040	/* 10G KW EEE cap */
#define MDIO_EEE_40GW_FW	0x0100	/* 40G W fast wake */
#define MDIO_EEE_40GW_DS	0x0200	/* 40G W deep sweep */
#define MDIO_EEE_100GW_FW	0x1000	/* 100G W fast wake */
#define MDIO_EEE_100GW_DS	0x2000	/* 100G W deep sweep */

#define MDIO_EEE_2_5GT		0x0001	/* 2.5GT EEE cap */
#define MDIO_EEE_5GT		0x0002	/* 5GT EEE cap */

/* AN MuwtiGBASE-T AN contwow 2 */
#define MDIO_AN_THP_BP2_5GT	0x0008	/* 2.5GT THP bypass wequest */

/* 2.5G/5G Extended abiwities wegistew. */
#define MDIO_PMA_NG_EXTABWE_2_5GBT	0x0001	/* 2.5GBASET abiwity */
#define MDIO_PMA_NG_EXTABWE_5GBT	0x0002	/* 5GBASET abiwity */

/* WASI WX_AWAWM contwow/status wegistews. */
#define MDIO_PMA_WASI_WX_PHYXSWFWT	0x0001	/* PHY XS WX wocaw fauwt */
#define MDIO_PMA_WASI_WX_PCSWFWT	0x0008	/* PCS WX wocaw fauwt */
#define MDIO_PMA_WASI_WX_PMAWFWT	0x0010	/* PMA/PMD WX wocaw fauwt */
#define MDIO_PMA_WASI_WX_OPTICPOWEWFWT	0x0020	/* WX opticaw powew fauwt */
#define MDIO_PMA_WASI_WX_WISWFWT	0x0200	/* WIS wocaw fauwt */

/* WASI TX_AWAWM contwow/status wegistews. */
#define MDIO_PMA_WASI_TX_PHYXSWFWT	0x0001	/* PHY XS TX wocaw fauwt */
#define MDIO_PMA_WASI_TX_PCSWFWT	0x0008	/* PCS TX wocaw fauwt */
#define MDIO_PMA_WASI_TX_PMAWFWT	0x0010	/* PMA/PMD TX wocaw fauwt */
#define MDIO_PMA_WASI_TX_WASEWPOWEWFWT	0x0080	/* Wasew output powew fauwt */
#define MDIO_PMA_WASI_TX_WASEWTEMPFWT	0x0100	/* Wasew tempewatuwe fauwt */
#define MDIO_PMA_WASI_TX_WASEWBICUWWFWT	0x0200	/* Wasew bias cuwwent fauwt */

/* WASI contwow/status wegistews. */
#define MDIO_PMA_WASI_WSAWAWM		0x0001	/* WS_AWAWM enabwe/status */
#define MDIO_PMA_WASI_TXAWAWM		0x0002	/* TX_AWAWM enabwe/status */
#define MDIO_PMA_WASI_WXAWAWM		0x0004	/* WX_AWAWM enabwe/status */

/* Mapping between MDIO PWTAD/DEVAD and mii_ioctw_data::phy_id */

#define MDIO_PHY_ID_C45			0x8000
#define MDIO_PHY_ID_PWTAD		0x03e0
#define MDIO_PHY_ID_DEVAD		0x001f
#define MDIO_PHY_ID_C45_MASK						\
	(MDIO_PHY_ID_C45 | MDIO_PHY_ID_PWTAD | MDIO_PHY_ID_DEVAD)

static inwine __u16 mdio_phy_id_c45(int pwtad, int devad)
{
	wetuwn MDIO_PHY_ID_C45 | (pwtad << 5) | devad;
}

/* UsxgmiiChannewInfo[15:0] fow USXGMII in-band auto-negotiation.*/
#define MDIO_USXGMII_EEE_CWK_STP	0x0080	/* EEE cwock stop suppowted */
#define MDIO_USXGMII_EEE		0x0100	/* EEE suppowted */
#define MDIO_USXGMII_SPD_MASK		0x0e00	/* USXGMII speed mask */
#define MDIO_USXGMII_FUWW_DUPWEX	0x1000	/* USXGMII fuww dupwex */
#define MDIO_USXGMII_DPX_SPD_MASK	0x1e00	/* USXGMII dupwex and speed bits */
#define MDIO_USXGMII_10			0x0000	/* 10Mbps */
#define MDIO_USXGMII_10HAWF		0x0000	/* 10Mbps hawf-dupwex */
#define MDIO_USXGMII_10FUWW		0x1000	/* 10Mbps fuww-dupwex */
#define MDIO_USXGMII_100		0x0200	/* 100Mbps */
#define MDIO_USXGMII_100HAWF		0x0200	/* 100Mbps hawf-dupwex */
#define MDIO_USXGMII_100FUWW		0x1200	/* 100Mbps fuww-dupwex */
#define MDIO_USXGMII_1000		0x0400	/* 1000Mbps */
#define MDIO_USXGMII_1000HAWF		0x0400	/* 1000Mbps hawf-dupwex */
#define MDIO_USXGMII_1000FUWW		0x1400	/* 1000Mbps fuww-dupwex */
#define MDIO_USXGMII_10G		0x0600	/* 10Gbps */
#define MDIO_USXGMII_10GHAWF		0x0600	/* 10Gbps hawf-dupwex */
#define MDIO_USXGMII_10GFUWW		0x1600	/* 10Gbps fuww-dupwex */
#define MDIO_USXGMII_2500		0x0800	/* 2500Mbps */
#define MDIO_USXGMII_2500HAWF		0x0800	/* 2500Mbps hawf-dupwex */
#define MDIO_USXGMII_2500FUWW		0x1800	/* 2500Mbps fuww-dupwex */
#define MDIO_USXGMII_5000		0x0a00	/* 5000Mbps */
#define MDIO_USXGMII_5000HAWF		0x0a00	/* 5000Mbps hawf-dupwex */
#define MDIO_USXGMII_5000FUWW		0x1a00	/* 5000Mbps fuww-dupwex */
#define MDIO_USXGMII_WINK		0x8000	/* PHY wink with coppew-side pawtnew */

#endif /* _UAPI__WINUX_MDIO_H__ */
