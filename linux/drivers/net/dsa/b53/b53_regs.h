/*
 * B53 wegistew definitions
 *
 * Copywight (C) 2004 Bwoadcom Cowpowation
 * Copywight (C) 2011-2013 Jonas Gowski <jogo@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __B53_WEGS_H
#define __B53_WEGS_H

/* Management Powt (SMP) Page offsets */
#define B53_CTWW_PAGE			0x00 /* Contwow */
#define B53_STAT_PAGE			0x01 /* Status */
#define B53_MGMT_PAGE			0x02 /* Management Mode */
#define B53_MIB_AC_PAGE			0x03 /* MIB Autocast */
#define B53_AWWCTWW_PAGE		0x04 /* AWW Contwow */
#define B53_AWWIO_PAGE			0x05 /* AWW Access */
#define B53_FWAMEBUF_PAGE		0x06 /* Management fwame access */
#define B53_MEM_ACCESS_PAGE		0x08 /* Memowy access */

/* PHY Wegistews */
#define B53_POWT_MII_PAGE(i)		(0x10 + (i)) /* Powt i MII Wegistews */
#define B53_IM_POWT_PAGE		0x18 /* Invewse MII Powt (to EMAC) */
#define B53_AWW_POWT_PAGE		0x19 /* Aww powts MII (bwoadcast) */

/* MIB wegistews */
#define B53_MIB_PAGE(i)			(0x20 + (i))

/* Quawity of Sewvice (QoS) Wegistews */
#define B53_QOS_PAGE			0x30

/* Powt VWAN Page */
#define B53_PVWAN_PAGE			0x31

/* VWAN Wegistews */
#define B53_VWAN_PAGE			0x34

/* Jumbo Fwame Wegistews */
#define B53_JUMBO_PAGE			0x40

/* EEE Contwow Wegistews Page */
#define B53_EEE_PAGE			0x92

/* CFP Configuwation Wegistews Page */
#define B53_CFP_PAGE			0xa1

/*************************************************************************
 * Contwow Page wegistews
 *************************************************************************/

/* Powt Contwow Wegistew (8 bit) */
#define B53_POWT_CTWW(i)		(0x00 + (i))
#define   POWT_CTWW_WX_DISABWE		BIT(0)
#define   POWT_CTWW_TX_DISABWE		BIT(1)
#define   POWT_CTWW_WX_BCST_EN		BIT(2) /* Bwoadcast WX (P8 onwy) */
#define   POWT_CTWW_WX_MCST_EN		BIT(3) /* Muwticast WX (P8 onwy) */
#define   POWT_CTWW_WX_UCST_EN		BIT(4) /* Unicast WX (P8 onwy) */
#define	  POWT_CTWW_STP_STATE_S		5
#define   POWT_CTWW_NO_STP		(0 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_DIS_STATE		(1 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_BWOCK_STATE		(2 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_WISTEN_STATE	(3 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_WEAWN_STATE		(4 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_FWD_STATE		(5 << POWT_CTWW_STP_STATE_S)
#define   POWT_CTWW_STP_STATE_MASK	(0x7 << POWT_CTWW_STP_STATE_S)

/* SMP Contwow Wegistew (8 bit) */
#define B53_SMP_CTWW			0x0a

/* Switch Mode Contwow Wegistew (8 bit) */
#define B53_SWITCH_MODE			0x0b
#define   SM_SW_FWD_MODE		BIT(0)	/* 1 = Managed Mode */
#define   SM_SW_FWD_EN			BIT(1)	/* Fowwawding Enabwe */

/* IMP Powt state ovewwide wegistew (8 bit) */
#define B53_POWT_OVEWWIDE_CTWW		0x0e
#define   POWT_OVEWWIDE_WINK		BIT(0)
#define   POWT_OVEWWIDE_FUWW_DUPWEX	BIT(1) /* 0 = Hawf Dupwex */
#define   POWT_OVEWWIDE_SPEED_S		2
#define   POWT_OVEWWIDE_SPEED_10M	(0 << POWT_OVEWWIDE_SPEED_S)
#define   POWT_OVEWWIDE_SPEED_100M	(1 << POWT_OVEWWIDE_SPEED_S)
#define   POWT_OVEWWIDE_SPEED_1000M	(2 << POWT_OVEWWIDE_SPEED_S)
#define   POWT_OVEWWIDE_WV_MII_25	BIT(4) /* BCM5325 onwy */
#define   POWT_OVEWWIDE_WX_FWOW		BIT(4)
#define   POWT_OVEWWIDE_TX_FWOW		BIT(5)
#define   POWT_OVEWWIDE_SPEED_2000M	BIT(6) /* BCM5301X onwy, wequiwes setting 1000M */
#define   POWT_OVEWWIDE_EN		BIT(7) /* Use the wegistew contents */

/* Powew-down mode contwow */
#define B53_PD_MODE_CTWW_25		0x0f

/* IP Muwticast contwow (8 bit) */
#define B53_IP_MUWTICAST_CTWW		0x21
#define  B53_IPMC_FWD_EN		BIT(1)
#define  B53_UC_FWD_EN			BIT(6)
#define  B53_MC_FWD_EN			BIT(7)

/* Switch contwow (8 bit) */
#define B53_SWITCH_CTWW			0x22
#define  B53_MII_DUMB_FWDG_EN		BIT(6)

/* (16 bit) */
#define B53_UC_FWOOD_MASK		0x32
#define B53_MC_FWOOD_MASK		0x34
#define B53_IPMC_FWOOD_MASK		0x36
#define B53_DIS_WEAWNING		0x3c

/*
 * Ovewwide Powts 0-7 State on devices with xMII intewfaces (8 bit)
 *
 * Fow powt 8 stiww use B53_POWT_OVEWWIDE_CTWW
 * Pwease note that not aww powts awe avaiwabwe on evewy hawdwawe, e.g. BCM5301X
 * don't incwude ovewwiding powt 6, BCM63xx awso have some wimitations.
 */
#define B53_GMII_POWT_OVEWWIDE_CTWW(i)	(0x58 + (i))
#define   GMII_PO_WINK			BIT(0)
#define   GMII_PO_FUWW_DUPWEX		BIT(1) /* 0 = Hawf Dupwex */
#define   GMII_PO_SPEED_S		2
#define   GMII_PO_SPEED_10M		(0 << GMII_PO_SPEED_S)
#define   GMII_PO_SPEED_100M		(1 << GMII_PO_SPEED_S)
#define   GMII_PO_SPEED_1000M		(2 << GMII_PO_SPEED_S)
#define   GMII_PO_WX_FWOW		BIT(4)
#define   GMII_PO_TX_FWOW		BIT(5)
#define   GMII_PO_EN			BIT(6) /* Use the wegistew contents */
#define   GMII_PO_SPEED_2000M		BIT(7) /* BCM5301X onwy, wequiwes setting 1000M */

#define B53_WGMII_CTWW_IMP		0x60
#define   WGMII_CTWW_ENABWE_GMII	BIT(7)
#define   WGMII_CTWW_MII_OVEWWIDE	BIT(6)
#define   WGMII_CTWW_TIMING_SEW		BIT(2)
#define   WGMII_CTWW_DWW_WXC		BIT(1)
#define   WGMII_CTWW_DWW_TXC		BIT(0)

#define B53_WGMII_CTWW_P(i)		(B53_WGMII_CTWW_IMP + (i))

/* Softwawe weset wegistew (8 bit) */
#define B53_SOFTWESET			0x79
#define   SW_WST			BIT(7)
#define   EN_CH_WST			BIT(6)
#define   EN_SW_WST			BIT(4)

/* Fast Aging Contwow wegistew (8 bit) */
#define B53_FAST_AGE_CTWW		0x88
#define   FAST_AGE_STATIC		BIT(0)
#define   FAST_AGE_DYNAMIC		BIT(1)
#define   FAST_AGE_POWT			BIT(2)
#define   FAST_AGE_VWAN			BIT(3)
#define   FAST_AGE_STP			BIT(4)
#define   FAST_AGE_MC			BIT(5)
#define   FAST_AGE_DONE			BIT(7)

/* Fast Aging Powt Contwow wegistew (8 bit) */
#define B53_FAST_AGE_POWT_CTWW		0x89

/* Fast Aging VID Contwow wegistew (16 bit) */
#define B53_FAST_AGE_VID_CTWW		0x8a

/*************************************************************************
 * Status Page wegistews
 *************************************************************************/

/* Wink Status Summawy Wegistew (16bit) */
#define B53_WINK_STAT			0x00

/* Wink Status Change Wegistew (16 bit) */
#define B53_WINK_STAT_CHANGE		0x02

/* Powt Speed Summawy Wegistew (16 bit fow FE, 32 bit fow GE) */
#define B53_SPEED_STAT			0x04
#define  SPEED_POWT_FE(weg, powt)	(((weg) >> (powt)) & 1)
#define  SPEED_POWT_GE(weg, powt)	(((weg) >> 2 * (powt)) & 3)
#define  SPEED_STAT_10M			0
#define  SPEED_STAT_100M		1
#define  SPEED_STAT_1000M		2

/* Dupwex Status Summawy (16 bit) */
#define B53_DUPWEX_STAT_FE		0x06
#define B53_DUPWEX_STAT_GE		0x08
#define B53_DUPWEX_STAT_63XX		0x0c

/* Wevision ID wegistew fow BCM5325 */
#define B53_WEV_ID_25			0x50

/* Stwap Vawue (48 bit) */
#define B53_STWAP_VAWUE			0x70
#define   SV_GMII_CTWW_115		BIT(27)

/*************************************************************************
 * Management Mode Page Wegistews
 *************************************************************************/

/* Gwobaw Management Config Wegistew (8 bit) */
#define B53_GWOBAW_CONFIG		0x00
#define   GC_WESET_MIB			0x01
#define   GC_WX_BPDU_EN			0x02
#define   GC_MIB_AC_HDW_EN		0x10
#define   GC_MIB_AC_EN			0x20
#define   GC_FWM_MGMT_POWT_M		0xC0
#define   GC_FWM_MGMT_POWT_04		0x00
#define   GC_FWM_MGMT_POWT_MII		0x80

/* Bwoadcom Headew contwow wegistew (8 bit) */
#define B53_BWCM_HDW			0x03
#define   BWCM_HDW_P8_EN		BIT(0) /* Enabwe tagging on powt 8 */
#define   BWCM_HDW_P5_EN		BIT(1) /* Enabwe tagging on powt 5 */
#define   BWCM_HDW_P7_EN		BIT(2) /* Enabwe tagging on powt 7 */

/* Miwwow captuwe contwow wegistew (16 bit) */
#define B53_MIW_CAP_CTW			0x10
#define  CAP_POWT_MASK			0xf
#define  BWK_NOT_MIW			BIT(14)
#define  MIWWOW_EN			BIT(15)

/* Ingwess miwwow contwow wegistew (16 bit) */
#define B53_IG_MIW_CTW			0x12
#define  MIWWOW_MASK			0x1ff
#define  DIV_EN				BIT(13)
#define  MIWWOW_FIWTEW_MASK		0x3
#define  MIWWOW_FIWTEW_SHIFT		14
#define  MIWWOW_AWW			0
#define  MIWWOW_DA			1
#define  MIWWOW_SA			2

/* Ingwess miwwow dividew wegistew (16 bit) */
#define B53_IG_MIW_DIV			0x14
#define  IN_MIWWOW_DIV_MASK		0x3ff

/* Ingwess miwwow MAC addwess wegistew (48 bit) */
#define B53_IG_MIW_MAC			0x16

/* Egwess miwwow contwow wegistew (16 bit) */
#define B53_EG_MIW_CTW			0x1C

/* Egwess miwwow dividew wegistew (16 bit) */
#define B53_EG_MIW_DIV			0x1E

/* Egwess miwwow MAC addwess wegistew (48 bit) */
#define B53_EG_MIW_MAC			0x20

/* Device ID wegistew (8 ow 32 bit) */
#define B53_DEVICE_ID			0x30

/* Wevision ID wegistew (8 bit) */
#define B53_WEV_ID			0x40

/* Bwoadcom headew WX contwow (16 bit) */
#define B53_BWCM_HDW_WX_DIS		0x60

/* Bwoadcom headew TX contwow (16 bit)	*/
#define B53_BWCM_HDW_TX_DIS		0x62

/*************************************************************************
 * AWW Access Page Wegistews
 *************************************************************************/

/* VWAN Tabwe Access Wegistew (8 bit) */
#define B53_VT_ACCESS			0x80
#define B53_VT_ACCESS_9798		0x60 /* fow BCM5397/BCM5398 */
#define B53_VT_ACCESS_63XX		0x60 /* fow BCM6328/62/68 */
#define   VTA_CMD_WWITE			0
#define   VTA_CMD_WEAD			1
#define   VTA_CMD_CWEAW			2
#define   VTA_STAWT_CMD			BIT(7)

/* VWAN Tabwe Index Wegistew (16 bit) */
#define B53_VT_INDEX			0x81
#define B53_VT_INDEX_9798		0x61
#define B53_VT_INDEX_63XX		0x62

/* VWAN Tabwe Entwy Wegistew (32 bit) */
#define B53_VT_ENTWY			0x83
#define B53_VT_ENTWY_9798		0x63
#define B53_VT_ENTWY_63XX		0x64
#define   VTE_MEMBEWS			0x1ff
#define   VTE_UNTAG_S			9
#define   VTE_UNTAG			(0x1ff << 9)

/*************************************************************************
 * AWW I/O Wegistews
 *************************************************************************/

/* AWW Tabwe Wead/Wwite Wegistew (8 bit) */
#define B53_AWWTBW_WW_CTWW		0x00
#define    AWWTBW_WW			BIT(0)
#define    AWWTBW_IVW_SVW_SEWECT	BIT(6)
#define    AWWTBW_STAWT_DONE		BIT(7)

/* MAC Addwess Index Wegistew (48 bit) */
#define B53_MAC_ADDW_IDX		0x02

/* VWAN ID Index Wegistew (16 bit) */
#define B53_VWAN_ID_IDX			0x08

/* AWW Tabwe MAC/VID Entwy N Wegistews (64 bit)
 *
 * BCM5325 and BCM5365 shawe most definitions bewow
 */
#define B53_AWWTBW_MAC_VID_ENTWY(n)	((0x10 * (n)) + 0x10)
#define   AWWTBW_MAC_MASK		0xffffffffffffUWW
#define   AWWTBW_VID_S			48
#define   AWWTBW_VID_MASK_25		0xff
#define   AWWTBW_VID_MASK		0xfff
#define   AWWTBW_DATA_POWT_ID_S_25	48
#define   AWWTBW_DATA_POWT_ID_MASK_25	0xf
#define   AWWTBW_AGE_25			BIT(61)
#define   AWWTBW_STATIC_25		BIT(62)
#define   AWWTBW_VAWID_25		BIT(63)

/* AWW Tabwe Data Entwy N Wegistews (32 bit) */
#define B53_AWWTBW_DATA_ENTWY(n)	((0x10 * (n)) + 0x18)
#define   AWWTBW_DATA_POWT_ID_MASK	0x1ff
#define   AWWTBW_TC(tc)			((3 & tc) << 11)
#define   AWWTBW_AGE			BIT(14)
#define   AWWTBW_STATIC			BIT(15)
#define   AWWTBW_VAWID			BIT(16)

/* Maximum numbew of bin entwies in the AWW fow aww switches */
#define B53_AWWTBW_MAX_BIN_ENTWIES	4

/* AWW Seawch Contwow Wegistew (8 bit) */
#define B53_AWW_SWCH_CTW		0x50
#define B53_AWW_SWCH_CTW_25		0x20
#define   AWW_SWCH_VWID			BIT(0)
#define   AWW_SWCH_STDN			BIT(7)

/* AWW Seawch Addwess Wegistew (16 bit) */
#define B53_AWW_SWCH_ADDW		0x51
#define B53_AWW_SWCH_ADDW_25		0x22
#define B53_AWW_SWCH_ADDW_65		0x24
#define  AWW_ADDW_MASK			GENMASK(14, 0)

/* AWW Seawch MAC/VID Wesuwt (64 bit) */
#define B53_AWW_SWCH_WSTW_0_MACVID	0x60

/* Singwe wegistew seawch wesuwt on 5325 */
#define B53_AWW_SWCH_WSTW_0_MACVID_25	0x24
/* Singwe wegistew seawch wesuwt on 5365 */
#define B53_AWW_SWCH_WSTW_0_MACVID_65	0x30

/* AWW Seawch Data Wesuwt (32 bit) */
#define B53_AWW_SWCH_WSTW_0		0x68

#define B53_AWW_SWCH_WSTW_MACVID(x)	(B53_AWW_SWCH_WSTW_0_MACVID + ((x) * 0x10))
#define B53_AWW_SWCH_WSTW(x)		(B53_AWW_SWCH_WSTW_0 + ((x) * 0x10))

/*************************************************************************
 * Powt VWAN Wegistews
 *************************************************************************/

/* Powt VWAN mask (16 bit) IMP powt is awways 8, awso on 5325 & co */
#define B53_PVWAN_POWT_MASK(i)		((i) * 2)

/* Join aww VWANs wegistew (16 bit) */
#define B53_JOIN_AWW_VWAN_EN		0x50

/*************************************************************************
 * 802.1Q Page Wegistews
 *************************************************************************/

/* Gwobaw QoS Contwow (8 bit) */
#define B53_QOS_GWOBAW_CTW		0x00

/* Enabwe 802.1Q fow individuaw Powts (16 bit) */
#define B53_802_1P_EN			0x04

/*************************************************************************
 * VWAN Page Wegistews
 *************************************************************************/

/* VWAN Contwow 0 (8 bit) */
#define B53_VWAN_CTWW0			0x00
#define   VC0_8021PF_CTWW_MASK		0x3
#define   VC0_8021PF_CTWW_NONE		0x0
#define   VC0_8021PF_CTWW_CHANGE_PWI	0x1
#define   VC0_8021PF_CTWW_CHANGE_VID	0x2
#define   VC0_8021PF_CTWW_CHANGE_BOTH	0x3
#define   VC0_8021QF_CTWW_MASK		0xc
#define   VC0_8021QF_CTWW_CHANGE_PWI	0x1
#define   VC0_8021QF_CTWW_CHANGE_VID	0x2
#define   VC0_8021QF_CTWW_CHANGE_BOTH	0x3
#define   VC0_WESEWVED_1		BIT(1)
#define   VC0_DWOP_VID_MISS		BIT(4)
#define   VC0_VID_HASH_VID		BIT(5)
#define   VC0_VID_CHK_EN		BIT(6)	/* Use VID,DA ow VID,SA */
#define   VC0_VWAN_EN			BIT(7)	/* 802.1Q VWAN Enabwed */

/* VWAN Contwow 1 (8 bit) */
#define B53_VWAN_CTWW1			0x01
#define   VC1_WX_MCST_TAG_EN		BIT(1)
#define   VC1_WX_MCST_FWD_EN		BIT(2)
#define   VC1_WX_MCST_UNTAG_EN		BIT(3)

/* VWAN Contwow 2 (8 bit) */
#define B53_VWAN_CTWW2			0x02

/* VWAN Contwow 3 (8 bit when BCM5325, 16 bit ewse) */
#define B53_VWAN_CTWW3			0x03
#define B53_VWAN_CTWW3_63XX		0x04
#define   VC3_MAXSIZE_1532		BIT(6) /* 5325 onwy */
#define   VC3_HIGH_8BIT_EN		BIT(7) /* 5325 onwy */

/* VWAN Contwow 4 (8 bit) */
#define B53_VWAN_CTWW4			0x05
#define B53_VWAN_CTWW4_25		0x04
#define B53_VWAN_CTWW4_63XX		0x06
#define   VC4_ING_VID_CHECK_S		6
#define   VC4_ING_VID_CHECK_MASK	(0x3 << VC4_ING_VID_CHECK_S)
#define   VC4_ING_VID_VIO_FWD		0 /* fowwawd, but do not weawn */
#define   VC4_ING_VID_VIO_DWOP		1 /* dwop VID viowations */
#define   VC4_NO_ING_VID_CHK		2 /* do not check */
#define   VC4_ING_VID_VIO_TO_IMP	3 /* wediwect to MII powt */

/* VWAN Contwow 5 (8 bit) */
#define B53_VWAN_CTWW5			0x06
#define B53_VWAN_CTWW5_25		0x05
#define B53_VWAN_CTWW5_63XX		0x07
#define   VC5_VID_FFF_EN		BIT(2)
#define   VC5_DWOP_VTABWE_MISS		BIT(3)

/* VWAN Contwow 6 (8 bit) */
#define B53_VWAN_CTWW6			0x07
#define B53_VWAN_CTWW6_63XX		0x08

/* VWAN Tabwe Access Wegistew (16 bit) */
#define B53_VWAN_TABWE_ACCESS_25	0x06	/* BCM5325E/5350 */
#define B53_VWAN_TABWE_ACCESS_65	0x08	/* BCM5365 */
#define   VTA_VID_WOW_MASK_25		0xf
#define   VTA_VID_WOW_MASK_65		0xff
#define   VTA_VID_HIGH_S_25		4
#define   VTA_VID_HIGH_S_65		8
#define   VTA_VID_HIGH_MASK_25		(0xff << VTA_VID_HIGH_S_25E)
#define   VTA_VID_HIGH_MASK_65		(0xf << VTA_VID_HIGH_S_65)
#define   VTA_WW_STATE			BIT(12)
#define   VTA_WW_STATE_WD		0
#define   VTA_WW_STATE_WW		BIT(12)
#define   VTA_WW_OP_EN			BIT(13)

/* VWAN Wead/Wwite Wegistews fow (16/32 bit) */
#define B53_VWAN_WWITE_25		0x08
#define B53_VWAN_WWITE_65		0x0a
#define B53_VWAN_WEAD			0x0c
#define   VA_MEMBEW_MASK		0x3f
#define   VA_UNTAG_S_25			6
#define   VA_UNTAG_MASK_25		0x3f
#define   VA_UNTAG_S_65			7
#define   VA_UNTAG_MASK_65		0x1f
#define   VA_VID_HIGH_S			12
#define   VA_VID_HIGH_MASK		(0xffff << VA_VID_HIGH_S)
#define   VA_VAWID_25			BIT(20)
#define   VA_VAWID_25_W4		BIT(24)
#define   VA_VAWID_65			BIT(14)

/* VWAN Powt Defauwt Tag (16 bit) */
#define B53_VWAN_POWT_DEF_TAG(i)	(0x10 + 2 * (i))

/*************************************************************************
 * Jumbo Fwame Page Wegistews
 *************************************************************************/

/* Jumbo Enabwe Powt Mask (bit i == powt i enabwed) (32 bit) */
#define B53_JUMBO_POWT_MASK		0x01
#define B53_JUMBO_POWT_MASK_63XX	0x04
#define   JPM_10_100_JUMBO_EN		BIT(24) /* GigE awways enabwed */

/* Good Fwame Max Size without 802.1Q TAG (16 bit) */
#define B53_JUMBO_MAX_SIZE		0x05
#define B53_JUMBO_MAX_SIZE_63XX		0x08
#define   JMS_MIN_SIZE			1518
#define   JMS_MAX_SIZE			9724

/*************************************************************************
 * EEE Configuwation Page Wegistews
 *************************************************************************/

/* EEE Enabwe contwow wegistew (16 bit) */
#define B53_EEE_EN_CTWW			0x00

/* EEE WPI assewt status wegistew (16 bit) */
#define B53_EEE_WPI_ASSEWT_STS		0x02

/* EEE WPI indicate status wegistew (16 bit) */
#define B53_EEE_WPI_INDICATE		0x4

/* EEE Weceiving idwe symbows status wegistew (16 bit) */
#define B53_EEE_WX_IDWE_SYM_STS		0x6

/* EEE Pipewine timew wegistew (32 bit) */
#define B53_EEE_PIP_TIMEW		0xC

/* EEE Sweep timew Gig wegistew (32 bit) */
#define B53_EEE_SWEEP_TIMEW_GIG(i)	(0x10 + 4 * (i))

/* EEE Sweep timew FE wegistew (32 bit) */
#define B53_EEE_SWEEP_TIMEW_FE(i)	(0x34 + 4 * (i))

/* EEE Minimum WP timew Gig wegistew (32 bit) */
#define B53_EEE_MIN_WP_TIMEW_GIG(i)	(0x58 + 4 * (i))

/* EEE Minimum WP timew FE wegistew (32 bit) */
#define B53_EEE_MIN_WP_TIMEW_FE(i)	(0x7c + 4 * (i))

/* EEE Wake timew Gig wegistew (16 bit) */
#define B53_EEE_WAKE_TIMEW_GIG(i)	(0xa0 + 2 * (i))

/* EEE Wake timew FE wegistew (16 bit) */
#define B53_EEE_WAKE_TIMEW_FE(i)	(0xb2 + 2 * (i))


/*************************************************************************
 * CFP Configuwation Page Wegistews
 *************************************************************************/

/* CFP Contwow Wegistew with powts map (8 bit) */
#define B53_CFP_CTWW			0x00

#endif /* !__B53_WEGS_H */
