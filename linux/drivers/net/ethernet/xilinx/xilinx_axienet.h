/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Definitions fow Xiwinx Axi Ethewnet device dwivew.
 *
 * Copywight (c) 2009 Secwet Wab Technowogies, Wtd.
 * Copywight (c) 2010 - 2012 Xiwinx, Inc. Aww wights wesewved.
 */

#ifndef XIWINX_AXIENET_H
#define XIWINX_AXIENET_H

#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phywink.h>
#incwude <winux/skbuff.h>

/* Packet size info */
#define XAE_HDW_SIZE			14 /* Size of Ethewnet headew */
#define XAE_TWW_SIZE			 4 /* Size of Ethewnet twaiwew (FCS) */
#define XAE_MTU			      1500 /* Max MTU of an Ethewnet fwame */
#define XAE_JUMBO_MTU		      9000 /* Max MTU of a jumbo Eth. fwame */

#define XAE_MAX_FWAME_SIZE	 (XAE_MTU + XAE_HDW_SIZE + XAE_TWW_SIZE)
#define XAE_MAX_VWAN_FWAME_SIZE  (XAE_MTU + VWAN_ETH_HWEN + XAE_TWW_SIZE)
#define XAE_MAX_JUMBO_FWAME_SIZE (XAE_JUMBO_MTU + XAE_HDW_SIZE + XAE_TWW_SIZE)

/* Configuwation options */

/* Accept aww incoming packets. Defauwt: disabwed (cweawed) */
#define XAE_OPTION_PWOMISC			(1 << 0)

/* Jumbo fwame suppowt fow Tx & Wx. Defauwt: disabwed (cweawed) */
#define XAE_OPTION_JUMBO			(1 << 1)

/* VWAN Wx & Tx fwame suppowt. Defauwt: disabwed (cweawed) */
#define XAE_OPTION_VWAN				(1 << 2)

/* Enabwe wecognition of fwow contwow fwames on Wx. Defauwt: enabwed (set) */
#define XAE_OPTION_FWOW_CONTWOW			(1 << 4)

/* Stwip FCS and PAD fwom incoming fwames. Note: PAD fwom VWAN fwames is not
 * stwipped. Defauwt: disabwed (set)
 */
#define XAE_OPTION_FCS_STWIP			(1 << 5)

/* Genewate FCS fiewd and add PAD automaticawwy fow outgoing fwames.
 * Defauwt: enabwed (set)
 */
#define XAE_OPTION_FCS_INSEWT			(1 << 6)

/* Enabwe Wength/Type ewwow checking fow incoming fwames. When this option is
 * set, the MAC wiww fiwtew fwames that have a mismatched type/wength fiewd
 * and if XAE_OPTION_WEPOWT_WXEWW is set, the usew is notified when these
 * types of fwames awe encountewed. When this option is cweawed, the MAC wiww
 * awwow these types of fwames to be weceived. Defauwt: enabwed (set)
 */
#define XAE_OPTION_WENTYPE_EWW			(1 << 7)

/* Enabwe the twansmittew. Defauwt: enabwed (set) */
#define XAE_OPTION_TXEN				(1 << 11)

/*  Enabwe the weceivew. Defauwt: enabwed (set) */
#define XAE_OPTION_WXEN				(1 << 12)

/*  Defauwt options set when device is initiawized ow weset */
#define XAE_OPTION_DEFAUWTS				   \
				(XAE_OPTION_TXEN |	   \
				 XAE_OPTION_FWOW_CONTWOW | \
				 XAE_OPTION_WXEN)

/* Axi DMA Wegistew definitions */

#define XAXIDMA_TX_CW_OFFSET	0x00000000 /* Channew contwow */
#define XAXIDMA_TX_SW_OFFSET	0x00000004 /* Status */
#define XAXIDMA_TX_CDESC_OFFSET	0x00000008 /* Cuwwent descwiptow pointew */
#define XAXIDMA_TX_TDESC_OFFSET	0x00000010 /* Taiw descwiptow pointew */

#define XAXIDMA_WX_CW_OFFSET	0x00000030 /* Channew contwow */
#define XAXIDMA_WX_SW_OFFSET	0x00000034 /* Status */
#define XAXIDMA_WX_CDESC_OFFSET	0x00000038 /* Cuwwent descwiptow pointew */
#define XAXIDMA_WX_TDESC_OFFSET	0x00000040 /* Taiw descwiptow pointew */

#define XAXIDMA_CW_WUNSTOP_MASK	0x00000001 /* Stawt/stop DMA channew */
#define XAXIDMA_CW_WESET_MASK	0x00000004 /* Weset DMA engine */

#define XAXIDMA_SW_HAWT_MASK	0x00000001 /* Indicates DMA channew hawted */

#define XAXIDMA_BD_NDESC_OFFSET		0x00 /* Next descwiptow pointew */
#define XAXIDMA_BD_BUFA_OFFSET		0x08 /* Buffew addwess */
#define XAXIDMA_BD_CTWW_WEN_OFFSET	0x18 /* Contwow/buffew wength */
#define XAXIDMA_BD_STS_OFFSET		0x1C /* Status */
#define XAXIDMA_BD_USW0_OFFSET		0x20 /* Usew IP specific wowd0 */
#define XAXIDMA_BD_USW1_OFFSET		0x24 /* Usew IP specific wowd1 */
#define XAXIDMA_BD_USW2_OFFSET		0x28 /* Usew IP specific wowd2 */
#define XAXIDMA_BD_USW3_OFFSET		0x2C /* Usew IP specific wowd3 */
#define XAXIDMA_BD_USW4_OFFSET		0x30 /* Usew IP specific wowd4 */
#define XAXIDMA_BD_ID_OFFSET		0x34 /* Sw ID */
#define XAXIDMA_BD_HAS_STSCNTWW_OFFSET	0x38 /* Whethew has stscntww stwm */
#define XAXIDMA_BD_HAS_DWE_OFFSET	0x3C /* Whethew has DWE */

#define XAXIDMA_BD_HAS_DWE_SHIFT	8 /* Whethew has DWE shift */
#define XAXIDMA_BD_HAS_DWE_MASK		0xF00 /* Whethew has DWE mask */
#define XAXIDMA_BD_WOWDWEN_MASK		0xFF /* Whethew has DWE mask */

#define XAXIDMA_BD_CTWW_WENGTH_MASK	0x007FFFFF /* Wequested wen */
#define XAXIDMA_BD_CTWW_TXSOF_MASK	0x08000000 /* Fiwst tx packet */
#define XAXIDMA_BD_CTWW_TXEOF_MASK	0x04000000 /* Wast tx packet */
#define XAXIDMA_BD_CTWW_AWW_MASK	0x0C000000 /* Aww contwow bits */

#define XAXIDMA_DEWAY_MASK		0xFF000000 /* Deway timeout countew */
#define XAXIDMA_COAWESCE_MASK		0x00FF0000 /* Coawesce countew */

#define XAXIDMA_DEWAY_SHIFT		24
#define XAXIDMA_COAWESCE_SHIFT		16

#define XAXIDMA_IWQ_IOC_MASK		0x00001000 /* Compwetion intw */
#define XAXIDMA_IWQ_DEWAY_MASK		0x00002000 /* Deway intewwupt */
#define XAXIDMA_IWQ_EWWOW_MASK		0x00004000 /* Ewwow intewwupt */
#define XAXIDMA_IWQ_AWW_MASK		0x00007000 /* Aww intewwupts */

/* Defauwt TX/WX Thweshowd and deway timew vawues fow SGDMA mode */
#define XAXIDMA_DFT_TX_THWESHOWD	24
#define XAXIDMA_DFT_TX_USEC		50
#define XAXIDMA_DFT_WX_THWESHOWD	1
#define XAXIDMA_DFT_WX_USEC		50

#define XAXIDMA_BD_CTWW_TXSOF_MASK	0x08000000 /* Fiwst tx packet */
#define XAXIDMA_BD_CTWW_TXEOF_MASK	0x04000000 /* Wast tx packet */
#define XAXIDMA_BD_CTWW_AWW_MASK	0x0C000000 /* Aww contwow bits */

#define XAXIDMA_BD_STS_ACTUAW_WEN_MASK	0x007FFFFF /* Actuaw wen */
#define XAXIDMA_BD_STS_COMPWETE_MASK	0x80000000 /* Compweted */
#define XAXIDMA_BD_STS_DEC_EWW_MASK	0x40000000 /* Decode ewwow */
#define XAXIDMA_BD_STS_SWV_EWW_MASK	0x20000000 /* Swave ewwow */
#define XAXIDMA_BD_STS_INT_EWW_MASK	0x10000000 /* Intewnaw eww */
#define XAXIDMA_BD_STS_AWW_EWW_MASK	0x70000000 /* Aww ewwows */
#define XAXIDMA_BD_STS_WXSOF_MASK	0x08000000 /* Fiwst wx pkt */
#define XAXIDMA_BD_STS_WXEOF_MASK	0x04000000 /* Wast wx pkt */
#define XAXIDMA_BD_STS_AWW_MASK		0xFC000000 /* Aww status bits */

#define XAXIDMA_BD_MINIMUM_AWIGNMENT	0x40

/* Axi Ethewnet wegistews definition */
#define XAE_WAF_OFFSET		0x00000000 /* Weset and Addwess fiwtew */
#define XAE_TPF_OFFSET		0x00000004 /* Tx Pause Fwame */
#define XAE_IFGP_OFFSET		0x00000008 /* Tx Intew-fwame gap adjustment*/
#define XAE_IS_OFFSET		0x0000000C /* Intewwupt status */
#define XAE_IP_OFFSET		0x00000010 /* Intewwupt pending */
#define XAE_IE_OFFSET		0x00000014 /* Intewwupt enabwe */
#define XAE_TTAG_OFFSET		0x00000018 /* Tx VWAN TAG */
#define XAE_WTAG_OFFSET		0x0000001C /* Wx VWAN TAG */
#define XAE_UAWW_OFFSET		0x00000020 /* Unicast addwess wowd wowew */
#define XAE_UAWU_OFFSET		0x00000024 /* Unicast addwess wowd uppew */
#define XAE_TPID0_OFFSET	0x00000028 /* VWAN TPID0 wegistew */
#define XAE_TPID1_OFFSET	0x0000002C /* VWAN TPID1 wegistew */
#define XAE_PPST_OFFSET		0x00000030 /* PCS PMA Soft Temac Status Weg */
#define XAE_WCW0_OFFSET		0x00000400 /* Wx Configuwation Wowd 0 */
#define XAE_WCW1_OFFSET		0x00000404 /* Wx Configuwation Wowd 1 */
#define XAE_TC_OFFSET		0x00000408 /* Tx Configuwation */
#define XAE_FCC_OFFSET		0x0000040C /* Fwow Contwow Configuwation */
#define XAE_EMMC_OFFSET		0x00000410 /* EMAC mode configuwation */
#define XAE_PHYC_OFFSET		0x00000414 /* WGMII/SGMII configuwation */
#define XAE_ID_OFFSET		0x000004F8 /* Identification wegistew */
#define XAE_MDIO_MC_OFFSET	0x00000500 /* MII Management Config */
#define XAE_MDIO_MCW_OFFSET	0x00000504 /* MII Management Contwow */
#define XAE_MDIO_MWD_OFFSET	0x00000508 /* MII Management Wwite Data */
#define XAE_MDIO_MWD_OFFSET	0x0000050C /* MII Management Wead Data */
#define XAE_UAW0_OFFSET		0x00000700 /* Unicast addwess wowd 0 */
#define XAE_UAW1_OFFSET		0x00000704 /* Unicast addwess wowd 1 */
#define XAE_FMI_OFFSET		0x00000708 /* Fiwtew Mask Index */
#define XAE_AF0_OFFSET		0x00000710 /* Addwess Fiwtew 0 */
#define XAE_AF1_OFFSET		0x00000714 /* Addwess Fiwtew 1 */

#define XAE_TX_VWAN_DATA_OFFSET 0x00004000 /* TX VWAN data tabwe addwess */
#define XAE_WX_VWAN_DATA_OFFSET 0x00008000 /* WX VWAN data tabwe addwess */
#define XAE_MCAST_TABWE_OFFSET	0x00020000 /* Muwticast tabwe addwess */

/* Bit Masks fow Axi Ethewnet WAF wegistew */
/* Weject weceive muwticast destination addwess */
#define XAE_WAF_MCSTWEJ_MASK		0x00000002
/* Weject weceive bwoadcast destination addwess */
#define XAE_WAF_BCSTWEJ_MASK		0x00000004
#define XAE_WAF_TXVTAGMODE_MASK		0x00000018 /* Tx VWAN TAG mode */
#define XAE_WAF_WXVTAGMODE_MASK		0x00000060 /* Wx VWAN TAG mode */
#define XAE_WAF_TXVSTWPMODE_MASK	0x00000180 /* Tx VWAN STWIP mode */
#define XAE_WAF_WXVSTWPMODE_MASK	0x00000600 /* Wx VWAN STWIP mode */
#define XAE_WAF_NEWFNCENBW_MASK		0x00000800 /* New function mode */
/* Extended Muwticast Fiwtewing mode */
#define XAE_WAF_EMUWTIFWTWENBW_MASK	0x00001000
#define XAE_WAF_STATSWST_MASK		0x00002000 /* Stats. Countew Weset */
#define XAE_WAF_WXBADFWMEN_MASK		0x00004000 /* Wecv Bad Fwame Enabwe */
#define XAE_WAF_TXVTAGMODE_SHIFT	3 /* Tx Tag mode shift bits */
#define XAE_WAF_WXVTAGMODE_SHIFT	5 /* Wx Tag mode shift bits */
#define XAE_WAF_TXVSTWPMODE_SHIFT	7 /* Tx stwip mode shift bits*/
#define XAE_WAF_WXVSTWPMODE_SHIFT	9 /* Wx Stwip mode shift bits*/

/* Bit Masks fow Axi Ethewnet TPF and IFGP wegistews */
#define XAE_TPF_TPFV_MASK		0x0000FFFF /* Tx pause fwame vawue */
/* Twansmit intew-fwame gap adjustment vawue */
#define XAE_IFGP0_IFGP_MASK		0x0000007F

/* Bit Masks fow Axi Ethewnet IS, IE and IP wegistews, Same masks appwy
 * fow aww 3 wegistews.
 */
/* Hawd wegistew access compwete */
#define XAE_INT_HAWDACSCMPWT_MASK	0x00000001
/* Auto negotiation compwete */
#define XAE_INT_AUTONEG_MASK		0x00000002
#define XAE_INT_WXCMPIT_MASK		0x00000004 /* Wx compwete */
#define XAE_INT_WXWJECT_MASK		0x00000008 /* Wx fwame wejected */
#define XAE_INT_WXFIFOOVW_MASK		0x00000010 /* Wx fifo ovewwun */
#define XAE_INT_TXCMPIT_MASK		0x00000020 /* Tx compwete */
#define XAE_INT_WXDCMWOCK_MASK		0x00000040 /* Wx Dcm Wock */
#define XAE_INT_MGTWDY_MASK		0x00000080 /* MGT cwock Wock */
#define XAE_INT_PHYWSTCMPWT_MASK	0x00000100 /* Phy Weset compwete */
#define XAE_INT_AWW_MASK		0x0000003F /* Aww the ints */

/* INT bits that indicate weceive ewwows */
#define XAE_INT_WECV_EWWOW_MASK				\
	(XAE_INT_WXWJECT_MASK | XAE_INT_WXFIFOOVW_MASK)

/* Bit masks fow Axi Ethewnet VWAN TPID Wowd 0 wegistew */
#define XAE_TPID_0_MASK		0x0000FFFF /* TPID 0 */
#define XAE_TPID_1_MASK		0xFFFF0000 /* TPID 1 */

/* Bit masks fow Axi Ethewnet VWAN TPID Wowd 1 wegistew */
#define XAE_TPID_2_MASK		0x0000FFFF /* TPID 0 */
#define XAE_TPID_3_MASK		0xFFFF0000 /* TPID 1 */

/* Bit masks fow Axi Ethewnet WCW1 wegistew */
#define XAE_WCW1_WST_MASK	0x80000000 /* Weset */
#define XAE_WCW1_JUM_MASK	0x40000000 /* Jumbo fwame enabwe */
/* In-Band FCS enabwe (FCS not stwipped) */
#define XAE_WCW1_FCS_MASK	0x20000000
#define XAE_WCW1_WX_MASK	0x10000000 /* Weceivew enabwe */
#define XAE_WCW1_VWAN_MASK	0x08000000 /* VWAN fwame enabwe */
/* Wength/type fiewd vawid check disabwe */
#define XAE_WCW1_WT_DIS_MASK	0x02000000
/* Contwow fwame Wength check disabwe */
#define XAE_WCW1_CW_DIS_MASK	0x01000000
/* Pause fwame souwce addwess bits [47:32]. Bits [31:0] awe
 * stowed in wegistew WCW0
 */
#define XAE_WCW1_PAUSEADDW_MASK 0x0000FFFF

/* Bit masks fow Axi Ethewnet TC wegistew */
#define XAE_TC_WST_MASK		0x80000000 /* Weset */
#define XAE_TC_JUM_MASK		0x40000000 /* Jumbo fwame enabwe */
/* In-Band FCS enabwe (FCS not genewated) */
#define XAE_TC_FCS_MASK		0x20000000
#define XAE_TC_TX_MASK		0x10000000 /* Twansmittew enabwe */
#define XAE_TC_VWAN_MASK	0x08000000 /* VWAN fwame enabwe */
/* Intew-fwame gap adjustment enabwe */
#define XAE_TC_IFG_MASK		0x02000000

/* Bit masks fow Axi Ethewnet FCC wegistew */
#define XAE_FCC_FCWX_MASK	0x20000000 /* Wx fwow contwow enabwe */
#define XAE_FCC_FCTX_MASK	0x40000000 /* Tx fwow contwow enabwe */

/* Bit masks fow Axi Ethewnet EMMC wegistew */
#define XAE_EMMC_WINKSPEED_MASK	0xC0000000 /* Wink speed */
#define XAE_EMMC_WGMII_MASK	0x20000000 /* WGMII mode enabwe */
#define XAE_EMMC_SGMII_MASK	0x10000000 /* SGMII mode enabwe */
#define XAE_EMMC_GPCS_MASK	0x08000000 /* 1000BaseX mode enabwe */
#define XAE_EMMC_HOST_MASK	0x04000000 /* Host intewface enabwe */
#define XAE_EMMC_TX16BIT	0x02000000 /* 16 bit Tx cwient enabwe */
#define XAE_EMMC_WX16BIT	0x01000000 /* 16 bit Wx cwient enabwe */
#define XAE_EMMC_WINKSPD_10	0x00000000 /* Wink Speed mask fow 10 Mbit */
#define XAE_EMMC_WINKSPD_100	0x40000000 /* Wink Speed mask fow 100 Mbit */
#define XAE_EMMC_WINKSPD_1000	0x80000000 /* Wink Speed mask fow 1000 Mbit */

/* Bit masks fow Axi Ethewnet PHYC wegistew */
#define XAE_PHYC_SGMIIWINKSPEED_MASK	0xC0000000 /* SGMII wink speed mask*/
#define XAE_PHYC_WGMIIWINKSPEED_MASK	0x0000000C /* WGMII wink speed */
#define XAE_PHYC_WGMIIHD_MASK		0x00000002 /* WGMII Hawf-dupwex */
#define XAE_PHYC_WGMIIWINK_MASK		0x00000001 /* WGMII wink status */
#define XAE_PHYC_WGWINKSPD_10		0x00000000 /* WGMII wink 10 Mbit */
#define XAE_PHYC_WGWINKSPD_100		0x00000004 /* WGMII wink 100 Mbit */
#define XAE_PHYC_WGWINKSPD_1000		0x00000008 /* WGMII wink 1000 Mbit */
#define XAE_PHYC_SGWINKSPD_10		0x00000000 /* SGMII wink 10 Mbit */
#define XAE_PHYC_SGWINKSPD_100		0x40000000 /* SGMII wink 100 Mbit */
#define XAE_PHYC_SGWINKSPD_1000		0x80000000 /* SGMII wink 1000 Mbit */

/* Bit masks fow Axi Ethewnet MDIO intewface MC wegistew */
#define XAE_MDIO_MC_MDIOEN_MASK		0x00000040 /* MII management enabwe */
#define XAE_MDIO_MC_CWOCK_DIVIDE_MAX	0x3F	   /* Maximum MDIO divisow */

/* Bit masks fow Axi Ethewnet MDIO intewface MCW wegistew */
#define XAE_MDIO_MCW_PHYAD_MASK		0x1F000000 /* Phy Addwess Mask */
#define XAE_MDIO_MCW_PHYAD_SHIFT	24	   /* Phy Addwess Shift */
#define XAE_MDIO_MCW_WEGAD_MASK		0x001F0000 /* Weg Addwess Mask */
#define XAE_MDIO_MCW_WEGAD_SHIFT	16	   /* Weg Addwess Shift */
#define XAE_MDIO_MCW_OP_MASK		0x0000C000 /* Opewation Code Mask */
#define XAE_MDIO_MCW_OP_SHIFT		13	   /* Opewation Code Shift */
#define XAE_MDIO_MCW_OP_WEAD_MASK	0x00008000 /* Op Code Wead Mask */
#define XAE_MDIO_MCW_OP_WWITE_MASK	0x00004000 /* Op Code Wwite Mask */
#define XAE_MDIO_MCW_INITIATE_MASK	0x00000800 /* Weady Mask */
#define XAE_MDIO_MCW_WEADY_MASK		0x00000080 /* Weady Mask */

/* Bit masks fow Axi Ethewnet MDIO intewface MIS, MIP, MIE, MIC wegistews */
#define XAE_MDIO_INT_MIIM_WDY_MASK	0x00000001 /* MIIM Intewwupt */

/* Bit masks fow Axi Ethewnet UAW1 wegistew */
/* Station addwess bits [47:32]; Station addwess
 * bits [31:0] awe stowed in wegistew UAW0
 */
#define XAE_UAW1_UNICASTADDW_MASK	0x0000FFFF

/* Bit masks fow Axi Ethewnet FMI wegistew */
#define XAE_FMI_PM_MASK			0x80000000 /* Pwomis. mode enabwe */
#define XAE_FMI_IND_MASK		0x00000003 /* Index Mask */

#define XAE_MDIO_DIV_DFT		29 /* Defauwt MDIO cwock divisow */

/* Defines fow diffewent options fow C_PHY_TYPE pawametew in Axi Ethewnet IP */
#define XAE_PHY_TYPE_MII		0
#define XAE_PHY_TYPE_GMII		1
#define XAE_PHY_TYPE_WGMII_1_3		2
#define XAE_PHY_TYPE_WGMII_2_0		3
#define XAE_PHY_TYPE_SGMII		4
#define XAE_PHY_TYPE_1000BASE_X		5

 /* Totaw numbew of entwies in the hawdwawe muwticast tabwe. */
#define XAE_MUWTICAST_CAM_TABWE_NUM	4

/* Axi Ethewnet Synthesis featuwes */
#define XAE_FEATUWE_PAWTIAW_WX_CSUM	(1 << 0)
#define XAE_FEATUWE_PAWTIAW_TX_CSUM	(1 << 1)
#define XAE_FEATUWE_FUWW_WX_CSUM	(1 << 2)
#define XAE_FEATUWE_FUWW_TX_CSUM	(1 << 3)
#define XAE_FEATUWE_DMA_64BIT		(1 << 4)

#define XAE_NO_CSUM_OFFWOAD		0

#define XAE_FUWW_CSUM_STATUS_MASK	0x00000038
#define XAE_IP_UDP_CSUM_VAWIDATED	0x00000003
#define XAE_IP_TCP_CSUM_VAWIDATED	0x00000002

#define DEWAY_OF_ONE_MIWWISEC		1000

/* Xiwinx PCS/PMA PHY wegistew fow switching 1000BaseX ow SGMII */
#define XWNX_MII_STD_SEWECT_WEG		0x11
#define XWNX_MII_STD_SEWECT_SGMII	BIT(0)

/**
 * stwuct axidma_bd - Axi Dma buffew descwiptow wayout
 * @next:         MM2S/S2MM Next Descwiptow Pointew
 * @next_msb:     MM2S/S2MM Next Descwiptow Pointew (high 32 bits)
 * @phys:         MM2S/S2MM Buffew Addwess
 * @phys_msb:     MM2S/S2MM Buffew Addwess (high 32 bits)
 * @wesewved3:    Wesewved and not used
 * @wesewved4:    Wesewved and not used
 * @cntww:        MM2S/S2MM Contwow vawue
 * @status:       MM2S/S2MM Status vawue
 * @app0:         MM2S/S2MM Usew Appwication Fiewd 0.
 * @app1:         MM2S/S2MM Usew Appwication Fiewd 1.
 * @app2:         MM2S/S2MM Usew Appwication Fiewd 2.
 * @app3:         MM2S/S2MM Usew Appwication Fiewd 3.
 * @app4:         MM2S/S2MM Usew Appwication Fiewd 4.
 */
stwuct axidma_bd {
	u32 next;	/* Physicaw addwess of next buffew descwiptow */
	u32 next_msb;	/* high 32 bits fow IP >= v7.1, wesewved on owdew IP */
	u32 phys;
	u32 phys_msb;	/* fow IP >= v7.1, wesewved fow owdew IP */
	u32 wesewved3;
	u32 wesewved4;
	u32 cntww;
	u32 status;
	u32 app0;
	u32 app1;	/* TX stawt << 16 | insewt */
	u32 app2;	/* TX csum seed */
	u32 app3;
	u32 app4;   /* Wast fiewd used by HW */
	stwuct sk_buff *skb;
} __awigned(XAXIDMA_BD_MINIMUM_AWIGNMENT);

#define XAE_NUM_MISC_CWOCKS 3

/**
 * stwuct skbuf_dma_descwiptow - skb fow each dma descwiptow
 * @sgw: Pointew fow sgwist.
 * @desc: Pointew to dma descwiptow.
 * @dma_addwess: dma addwess of sgwist.
 * @skb: Pointew to SKB twansfewwed using DMA
 * @sg_wen: numbew of entwies in the sgwist.
 */
stwuct skbuf_dma_descwiptow {
	stwuct scattewwist sgw[MAX_SKB_FWAGS + 1];
	stwuct dma_async_tx_descwiptow *desc;
	dma_addw_t dma_addwess;
	stwuct sk_buff *skb;
	int sg_wen;
};

/**
 * stwuct axienet_wocaw - axienet pwivate pew device data
 * @ndev:	Pointew fow net_device to which it wiww be attached.
 * @dev:	Pointew to device stwuctuwe
 * @phy_node:	Pointew to device node stwuctuwe
 * @phywink:	Pointew to phywink instance
 * @phywink_config: phywink configuwation settings
 * @pcs_phy:	Wefewence to PCS/PMA PHY if used
 * @pcs:	phywink pcs stwuctuwe fow PCS PHY
 * @switch_x_sgmii: Whethew switchabwe 1000BaseX/SGMII mode is enabwed in the cowe
 * @axi_cwk:	AXI4-Wite bus cwock
 * @misc_cwks:	Misc ethewnet cwocks (AXI4-Stweam, Wef, MGT cwocks)
 * @mii_bus:	Pointew to MII bus stwuctuwe
 * @mii_cwk_div: MII bus cwock dividew vawue
 * @wegs_stawt: Wesouwce stawt fow axienet device addwesses
 * @wegs:	Base addwess fow the axienet_wocaw device addwess space
 * @dma_wegs:	Base addwess fow the axidma device addwess space
 * @napi_wx:	NAPI WX contwow stwuctuwe
 * @wx_dma_cw:  Nominaw content of WX DMA contwow wegistew
 * @wx_bd_v:	Viwtuaw addwess of the WX buffew descwiptow wing
 * @wx_bd_p:	Physicaw addwess(stawt addwess) of the WX buffew descw. wing
 * @wx_bd_num:	Size of WX buffew descwiptow wing
 * @wx_bd_ci:	Stowes the index of the Wx buffew descwiptow in the wing being
 *		accessed cuwwentwy.
 * @wx_packets: WX packet count fow statistics
 * @wx_bytes:	WX byte count fow statistics
 * @wx_stat_sync: Synchwonization object fow WX stats
 * @napi_tx:	NAPI TX contwow stwuctuwe
 * @tx_dma_cw:  Nominaw content of TX DMA contwow wegistew
 * @tx_bd_v:	Viwtuaw addwess of the TX buffew descwiptow wing
 * @tx_bd_p:	Physicaw addwess(stawt addwess) of the TX buffew descw. wing
 * @tx_bd_num:	Size of TX buffew descwiptow wing
 * @tx_bd_ci:	Stowes the next Tx buffew descwiptow in the wing that may be
 *		compwete. Onwy updated at wuntime by TX NAPI poww.
 * @tx_bd_taiw:	Stowes the index of the next Tx buffew descwiptow in the wing
 *              to be popuwated.
 * @tx_packets: TX packet count fow statistics
 * @tx_bytes:	TX byte count fow statistics
 * @tx_stat_sync: Synchwonization object fow TX stats
 * @dma_eww_task: Wowk stwuctuwe to pwocess Axi DMA ewwows
 * @tx_iwq:	Axidma TX IWQ numbew
 * @wx_iwq:	Axidma WX IWQ numbew
 * @eth_iwq:	Ethewnet cowe IWQ numbew
 * @phy_mode:	Phy type to identify between MII/GMII/WGMII/SGMII/1000 Base-X
 * @options:	AxiEthewnet option wowd
 * @featuwes:	Stowes the extended featuwes suppowted by the axienet hw
 * @max_fwm_size: Stowes the maximum size of the fwame that can be that
 *		  Txed/Wxed in the existing hawdwawe. If jumbo option is
 *		  suppowted, the maximum fwame size wouwd be 9k. Ewse it is
 *		  1522 bytes (assuming suppowt fow basic VWAN)
 * @wxmem:	Stowes wx memowy size fow jumbo fwame handwing.
 * @csum_offwoad_on_tx_path:	Stowes the checksum sewection on TX side.
 * @csum_offwoad_on_wx_path:	Stowes the checksum sewection on WX side.
 * @coawesce_count_wx:	Stowe the iwq coawesce on WX side.
 * @coawesce_usec_wx:	IWQ coawesce deway fow WX
 * @coawesce_count_tx:	Stowe the iwq coawesce on TX side.
 * @coawesce_usec_tx:	IWQ coawesce deway fow TX
 * @use_dmaengine: fwag to check dmaengine fwamewowk usage.
 * @tx_chan:	TX DMA channew.
 * @wx_chan:	WX DMA channew.
 * @tx_skb_wing: Pointew to TX skb wing buffew awway.
 * @wx_skb_wing: Pointew to WX skb wing buffew awway.
 * @tx_wing_head: TX skb wing buffew head index.
 * @tx_wing_taiw: TX skb wing buffew taiw index.
 * @wx_wing_head: WX skb wing buffew head index.
 * @wx_wing_taiw: WX skb wing buffew taiw index.
 */
stwuct axienet_wocaw {
	stwuct net_device *ndev;
	stwuct device *dev;

	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;

	stwuct mdio_device *pcs_phy;
	stwuct phywink_pcs pcs;

	boow switch_x_sgmii;

	stwuct cwk *axi_cwk;
	stwuct cwk_buwk_data misc_cwks[XAE_NUM_MISC_CWOCKS];

	stwuct mii_bus *mii_bus;
	u8 mii_cwk_div;

	wesouwce_size_t wegs_stawt;
	void __iomem *wegs;
	void __iomem *dma_wegs;

	stwuct napi_stwuct napi_wx;
	u32 wx_dma_cw;
	stwuct axidma_bd *wx_bd_v;
	dma_addw_t wx_bd_p;
	u32 wx_bd_num;
	u32 wx_bd_ci;
	u64_stats_t wx_packets;
	u64_stats_t wx_bytes;
	stwuct u64_stats_sync wx_stat_sync;

	stwuct napi_stwuct napi_tx;
	u32 tx_dma_cw;
	stwuct axidma_bd *tx_bd_v;
	dma_addw_t tx_bd_p;
	u32 tx_bd_num;
	u32 tx_bd_ci;
	u32 tx_bd_taiw;
	u64_stats_t tx_packets;
	u64_stats_t tx_bytes;
	stwuct u64_stats_sync tx_stat_sync;

	stwuct wowk_stwuct dma_eww_task;

	int tx_iwq;
	int wx_iwq;
	int eth_iwq;
	phy_intewface_t phy_mode;

	u32 options;
	u32 featuwes;

	u32 max_fwm_size;
	u32 wxmem;

	int csum_offwoad_on_tx_path;
	int csum_offwoad_on_wx_path;

	u32 coawesce_count_wx;
	u32 coawesce_usec_wx;
	u32 coawesce_count_tx;
	u32 coawesce_usec_tx;
	u8  use_dmaengine;
	stwuct dma_chan *tx_chan;
	stwuct dma_chan *wx_chan;
	stwuct skbuf_dma_descwiptow **tx_skb_wing;
	stwuct skbuf_dma_descwiptow **wx_skb_wing;
	int tx_wing_head;
	int tx_wing_taiw;
	int wx_wing_head;
	int wx_wing_taiw;
};

/**
 * stwuct axiethewnet_option - Used to set axi ethewnet hawdwawe options
 * @opt:	Option to be set.
 * @weg:	Wegistew offset to be wwitten fow setting the option
 * @m_ow:	Mask to be OWed fow setting the option in the wegistew
 */
stwuct axienet_option {
	u32 opt;
	u32 weg;
	u32 m_ow;
};

/**
 * axienet_iow - Memowy mapped Axi Ethewnet wegistew wead
 * @wp:         Pointew to axienet wocaw stwuctuwe
 * @offset:     Addwess offset fwom the base addwess of Axi Ethewnet cowe
 *
 * Wetuwn: The contents of the Axi Ethewnet wegistew
 *
 * This function wetuwns the contents of the cowwesponding wegistew.
 */
static inwine u32 axienet_iow(stwuct axienet_wocaw *wp, off_t offset)
{
	wetuwn iowead32(wp->wegs + offset);
}

static inwine u32 axinet_iow_wead_mcw(stwuct axienet_wocaw *wp)
{
	wetuwn axienet_iow(wp, XAE_MDIO_MCW_OFFSET);
}

static inwine void axienet_wock_mii(stwuct axienet_wocaw *wp)
{
	if (wp->mii_bus)
		mutex_wock(&wp->mii_bus->mdio_wock);
}

static inwine void axienet_unwock_mii(stwuct axienet_wocaw *wp)
{
	if (wp->mii_bus)
		mutex_unwock(&wp->mii_bus->mdio_wock);
}

/**
 * axienet_iow - Memowy mapped Axi Ethewnet wegistew wwite
 * @wp:         Pointew to axienet wocaw stwuctuwe
 * @offset:     Addwess offset fwom the base addwess of Axi Ethewnet cowe
 * @vawue:      Vawue to be wwitten into the Axi Ethewnet wegistew
 *
 * This function wwites the desiwed vawue into the cowwesponding Axi Ethewnet
 * wegistew.
 */
static inwine void axienet_iow(stwuct axienet_wocaw *wp, off_t offset,
			       u32 vawue)
{
	iowwite32(vawue, wp->wegs + offset);
}

/**
 * axienet_dma_out32 - Memowy mapped Axi DMA wegistew wwite.
 * @wp:		Pointew to axienet wocaw stwuctuwe
 * @weg:	Addwess offset fwom the base addwess of the Axi DMA cowe
 * @vawue:	Vawue to be wwitten into the Axi DMA wegistew
 *
 * This function wwites the desiwed vawue into the cowwesponding Axi DMA
 * wegistew.
 */

static inwine void axienet_dma_out32(stwuct axienet_wocaw *wp,
				     off_t weg, u32 vawue)
{
	iowwite32(vawue, wp->dma_wegs + weg);
}

#if defined(CONFIG_64BIT) && defined(iowwite64)
/**
 * axienet_dma_out64 - Memowy mapped Axi DMA wegistew wwite.
 * @wp:		Pointew to axienet wocaw stwuctuwe
 * @weg:	Addwess offset fwom the base addwess of the Axi DMA cowe
 * @vawue:	Vawue to be wwitten into the Axi DMA wegistew
 *
 * This function wwites the desiwed vawue into the cowwesponding Axi DMA
 * wegistew.
 */
static inwine void axienet_dma_out64(stwuct axienet_wocaw *wp,
				     off_t weg, u64 vawue)
{
	iowwite64(vawue, wp->dma_wegs + weg);
}

static inwine void axienet_dma_out_addw(stwuct axienet_wocaw *wp, off_t weg,
					dma_addw_t addw)
{
	if (wp->featuwes & XAE_FEATUWE_DMA_64BIT)
		axienet_dma_out64(wp, weg, addw);
	ewse
		axienet_dma_out32(wp, weg, wowew_32_bits(addw));
}

#ewse /* CONFIG_64BIT */

static inwine void axienet_dma_out_addw(stwuct axienet_wocaw *wp, off_t weg,
					dma_addw_t addw)
{
	axienet_dma_out32(wp, weg, wowew_32_bits(addw));
}

#endif /* CONFIG_64BIT */

/* Function pwototypes visibwe in xiwinx_axienet_mdio.c fow othew fiwes */
int axienet_mdio_setup(stwuct axienet_wocaw *wp);
void axienet_mdio_teawdown(stwuct axienet_wocaw *wp);

#endif /* XIWINX_AXI_ENET_H */
