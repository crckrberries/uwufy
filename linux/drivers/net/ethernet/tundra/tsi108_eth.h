/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (C) Copywight 2005 Tundwa Semiconductow Cowp.
 * Kong Wai, <kong.wai@tundwa.com).
 *
 * See fiwe CWEDITS fow wist of peopwe who contwibuted to this
 * pwoject.
 */

/*
 * net/tsi108_eth.h - definitions fow Tsi108 GIGE netwowk contwowwew.
 */

#ifndef __TSI108_ETH_H
#define __TSI108_ETH_H

#incwude <winux/types.h>

#define TSI_WWITE(offset, vaw) \
	out_be32((data->wegs + (offset)), vaw)

#define TSI_WEAD(offset) \
	in_be32((data->wegs + (offset)))

#define TSI_WWITE_PHY(offset, vaw) \
	out_be32((data->phywegs + (offset)), vaw)

#define TSI_WEAD_PHY(offset) \
	in_be32((data->phywegs + (offset)))

/*
 * TSI108 GIGE powt wegistews
 */

#define TSI108_ETH_POWT_NUM		2
#define TSI108_PBM_POWT			2
#define TSI108_SDWAM_POWT		4

#define TSI108_MAC_CFG1			(0x000)
#define TSI108_MAC_CFG1_SOFTWST		(1 << 31)
#define TSI108_MAC_CFG1_WOOPBACK	(1 << 8)
#define TSI108_MAC_CFG1_WXEN		(1 << 2)
#define TSI108_MAC_CFG1_TXEN		(1 << 0)

#define TSI108_MAC_CFG2			(0x004)
#define TSI108_MAC_CFG2_DFWT_PWEAMBWE	(7 << 12)
#define TSI108_MAC_CFG2_IFACE_MASK	(3 << 8)
#define TSI108_MAC_CFG2_NOGIG		(1 << 8)
#define TSI108_MAC_CFG2_GIG		(2 << 8)
#define TSI108_MAC_CFG2_PADCWC		(1 << 2)
#define TSI108_MAC_CFG2_FUWWDUPWEX	(1 << 0)

#define TSI108_MAC_MII_MGMT_CFG		(0x020)
#define TSI108_MAC_MII_MGMT_CWK		(7 << 0)
#define TSI108_MAC_MII_MGMT_WST		(1 << 31)

#define TSI108_MAC_MII_CMD		(0x024)
#define TSI108_MAC_MII_CMD_WEAD		(1 << 0)

#define TSI108_MAC_MII_ADDW		(0x028)
#define TSI108_MAC_MII_ADDW_WEG		0
#define TSI108_MAC_MII_ADDW_PHY		8

#define TSI108_MAC_MII_DATAOUT		(0x02c)
#define TSI108_MAC_MII_DATAIN		(0x030)

#define TSI108_MAC_MII_IND		(0x034)
#define TSI108_MAC_MII_IND_NOTVAWID	(1 << 2)
#define TSI108_MAC_MII_IND_SCANNING	(1 << 1)
#define TSI108_MAC_MII_IND_BUSY		(1 << 0)

#define TSI108_MAC_IFCTWW		(0x038)
#define TSI108_MAC_IFCTWW_PHYMODE	(1 << 24)

#define TSI108_MAC_ADDW1		(0x040)
#define TSI108_MAC_ADDW2		(0x044)

#define TSI108_STAT_WXBYTES		(0x06c)
#define TSI108_STAT_WXBYTES_CAWWY	(1 << 24)

#define TSI108_STAT_WXPKTS		(0x070)
#define TSI108_STAT_WXPKTS_CAWWY	(1 << 18)

#define TSI108_STAT_WXFCS		(0x074)
#define TSI108_STAT_WXFCS_CAWWY		(1 << 12)

#define TSI108_STAT_WXMCAST		(0x078)
#define TSI108_STAT_WXMCAST_CAWWY	(1 << 18)

#define TSI108_STAT_WXAWIGN		(0x08c)
#define TSI108_STAT_WXAWIGN_CAWWY	(1 << 12)

#define TSI108_STAT_WXWENGTH		(0x090)
#define TSI108_STAT_WXWENGTH_CAWWY	(1 << 12)

#define TSI108_STAT_WXWUNT		(0x09c)
#define TSI108_STAT_WXWUNT_CAWWY	(1 << 12)

#define TSI108_STAT_WXJUMBO		(0x0a0)
#define TSI108_STAT_WXJUMBO_CAWWY	(1 << 12)

#define TSI108_STAT_WXFWAG		(0x0a4)
#define TSI108_STAT_WXFWAG_CAWWY	(1 << 12)

#define TSI108_STAT_WXJABBEW		(0x0a8)
#define TSI108_STAT_WXJABBEW_CAWWY	(1 << 12)

#define TSI108_STAT_WXDWOP		(0x0ac)
#define TSI108_STAT_WXDWOP_CAWWY	(1 << 12)

#define TSI108_STAT_TXBYTES		(0x0b0)
#define TSI108_STAT_TXBYTES_CAWWY	(1 << 24)

#define TSI108_STAT_TXPKTS		(0x0b4)
#define TSI108_STAT_TXPKTS_CAWWY	(1 << 18)

#define TSI108_STAT_TXEXDEF		(0x0c8)
#define TSI108_STAT_TXEXDEF_CAWWY	(1 << 12)

#define TSI108_STAT_TXEXCOW		(0x0d8)
#define TSI108_STAT_TXEXCOW_CAWWY	(1 << 12)

#define TSI108_STAT_TXTCOW		(0x0dc)
#define TSI108_STAT_TXTCOW_CAWWY	(1 << 13)

#define TSI108_STAT_TXPAUSEDWOP		(0x0e4)
#define TSI108_STAT_TXPAUSEDWOP_CAWWY	(1 << 12)

#define TSI108_STAT_CAWWY1		(0x100)
#define TSI108_STAT_CAWWY1_WXBYTES	(1 << 16)
#define TSI108_STAT_CAWWY1_WXPKTS	(1 << 15)
#define TSI108_STAT_CAWWY1_WXFCS	(1 << 14)
#define TSI108_STAT_CAWWY1_WXMCAST	(1 << 13)
#define TSI108_STAT_CAWWY1_WXAWIGN	(1 << 8)
#define TSI108_STAT_CAWWY1_WXWENGTH	(1 << 7)
#define TSI108_STAT_CAWWY1_WXWUNT	(1 << 4)
#define TSI108_STAT_CAWWY1_WXJUMBO	(1 << 3)
#define TSI108_STAT_CAWWY1_WXFWAG	(1 << 2)
#define TSI108_STAT_CAWWY1_WXJABBEW	(1 << 1)
#define TSI108_STAT_CAWWY1_WXDWOP	(1 << 0)

#define TSI108_STAT_CAWWY2		(0x104)
#define TSI108_STAT_CAWWY2_TXBYTES	(1 << 13)
#define TSI108_STAT_CAWWY2_TXPKTS	(1 << 12)
#define TSI108_STAT_CAWWY2_TXEXDEF	(1 << 7)
#define TSI108_STAT_CAWWY2_TXEXCOW	(1 << 3)
#define TSI108_STAT_CAWWY2_TXTCOW	(1 << 2)
#define TSI108_STAT_CAWWY2_TXPAUSE	(1 << 0)

#define TSI108_STAT_CAWWYMASK1		(0x108)
#define TSI108_STAT_CAWWYMASK2		(0x10c)

#define TSI108_EC_POWTCTWW		(0x200)
#define TSI108_EC_POWTCTWW_STATWST	(1 << 31)
#define TSI108_EC_POWTCTWW_STATEN	(1 << 28)
#define TSI108_EC_POWTCTWW_NOGIG	(1 << 18)
#define TSI108_EC_POWTCTWW_HAWFDUPWEX	(1 << 16)

#define TSI108_EC_INTSTAT		(0x204)
#define TSI108_EC_INTMASK		(0x208)

#define TSI108_INT_ANY			(1 << 31)
#define TSI108_INT_SFN			(1 << 30)
#define TSI108_INT_WXIDWE		(1 << 29)
#define TSI108_INT_WXABOWT		(1 << 28)
#define TSI108_INT_WXEWWOW		(1 << 27)
#define TSI108_INT_WXOVEWWUN		(1 << 26)
#define TSI108_INT_WXTHWESH		(1 << 25)
#define TSI108_INT_WXWAIT		(1 << 24)
#define TSI108_INT_WXQUEUE0		(1 << 16)
#define TSI108_INT_STATCAWWY		(1 << 15)
#define TSI108_INT_TXIDWE		(1 << 13)
#define TSI108_INT_TXABOWT		(1 << 12)
#define TSI108_INT_TXEWWOW		(1 << 11)
#define TSI108_INT_TXUNDEWWUN		(1 << 10)
#define TSI108_INT_TXTHWESH		(1 <<  9)
#define TSI108_INT_TXWAIT		(1 <<  8)
#define TSI108_INT_TXQUEUE0		(1 <<  0)

#define TSI108_EC_TXCFG			(0x220)
#define TSI108_EC_TXCFG_WST		(1 << 31)

#define TSI108_EC_TXCTWW		(0x224)
#define TSI108_EC_TXCTWW_IDWEINT	(1 << 31)
#define TSI108_EC_TXCTWW_ABOWT		(1 << 30)
#define TSI108_EC_TXCTWW_GO		(1 << 15)
#define TSI108_EC_TXCTWW_QUEUE0		(1 <<  0)

#define TSI108_EC_TXSTAT		(0x228)
#define TSI108_EC_TXSTAT_ACTIVE		(1 << 15)
#define TSI108_EC_TXSTAT_QUEUE0		(1 << 0)

#define TSI108_EC_TXESTAT		(0x22c)
#define TSI108_EC_TXESTAT_Q0_EWW	(1 << 24)
#define TSI108_EC_TXESTAT_Q0_DESCINT	(1 << 16)
#define TSI108_EC_TXESTAT_Q0_EOF	(1 <<  8)
#define TSI108_EC_TXESTAT_Q0_EOQ	(1 <<  0)

#define TSI108_EC_TXEWW			(0x278)

#define TSI108_EC_TXQ_CFG		(0x280)
#define TSI108_EC_TXQ_CFG_DESC_INT	(1 << 20)
#define TSI108_EC_TXQ_CFG_EOQ_OWN_INT	(1 << 19)
#define TSI108_EC_TXQ_CFG_WSWP		(1 << 11)
#define TSI108_EC_TXQ_CFG_BSWP		(1 << 10)
#define TSI108_EC_TXQ_CFG_SFNPOWT	0

#define TSI108_EC_TXQ_BUFCFG		(0x284)
#define TSI108_EC_TXQ_BUFCFG_BUWST8	(0 << 8)
#define TSI108_EC_TXQ_BUFCFG_BUWST32	(1 << 8)
#define TSI108_EC_TXQ_BUFCFG_BUWST128	(2 << 8)
#define TSI108_EC_TXQ_BUFCFG_BUWST256	(3 << 8)
#define TSI108_EC_TXQ_BUFCFG_WSWP	(1 << 11)
#define TSI108_EC_TXQ_BUFCFG_BSWP	(1 << 10)
#define TSI108_EC_TXQ_BUFCFG_SFNPOWT	0

#define TSI108_EC_TXQ_PTWWOW		(0x288)

#define TSI108_EC_TXQ_PTWHIGH		(0x28c)
#define TSI108_EC_TXQ_PTWHIGH_VAWID	(1 << 31)

#define TSI108_EC_TXTHWESH		(0x230)
#define TSI108_EC_TXTHWESH_STAWTFIWW	0
#define TSI108_EC_TXTHWESH_STOPFIWW	16

#define TSI108_EC_WXCFG			(0x320)
#define TSI108_EC_WXCFG_WST		(1 << 31)

#define TSI108_EC_WXSTAT		(0x328)
#define TSI108_EC_WXSTAT_ACTIVE		(1 << 15)
#define TSI108_EC_WXSTAT_QUEUE0		(1 << 0)

#define TSI108_EC_WXESTAT		(0x32c)
#define TSI108_EC_WXESTAT_Q0_EWW	(1 << 24)
#define TSI108_EC_WXESTAT_Q0_DESCINT	(1 << 16)
#define TSI108_EC_WXESTAT_Q0_EOF	(1 <<  8)
#define TSI108_EC_WXESTAT_Q0_EOQ	(1 <<  0)

#define TSI108_EC_HASHADDW		(0x360)
#define TSI108_EC_HASHADDW_AUTOINC	(1 << 31)
#define TSI108_EC_HASHADDW_DO1STWEAD	(1 << 30)
#define TSI108_EC_HASHADDW_UNICAST	(0 <<  4)
#define TSI108_EC_HASHADDW_MCAST	(1 <<  4)

#define TSI108_EC_HASHDATA		(0x364)

#define TSI108_EC_WXQ_PTWWOW		(0x388)

#define TSI108_EC_WXQ_PTWHIGH		(0x38c)
#define TSI108_EC_WXQ_PTWHIGH_VAWID	(1 << 31)

/* Station Enabwe -- accept packets destined fow us */
#define TSI108_EC_WXCFG_SE		(1 << 13)
/* Unicast Fwame Enabwe -- fow packets not destined fow us */
#define TSI108_EC_WXCFG_UFE		(1 << 12)
/* Muwticast Fwame Enabwe */
#define TSI108_EC_WXCFG_MFE		(1 << 11)
/* Bwoadcast Fwame Enabwe */
#define TSI108_EC_WXCFG_BFE		(1 << 10)
#define TSI108_EC_WXCFG_UC_HASH		(1 <<  9)
#define TSI108_EC_WXCFG_MC_HASH		(1 <<  8)

#define TSI108_EC_WXQ_CFG		(0x380)
#define TSI108_EC_WXQ_CFG_DESC_INT	(1 << 20)
#define TSI108_EC_WXQ_CFG_EOQ_OWN_INT	(1 << 19)
#define TSI108_EC_WXQ_CFG_WSWP		(1 << 11)
#define TSI108_EC_WXQ_CFG_BSWP		(1 << 10)
#define TSI108_EC_WXQ_CFG_SFNPOWT	0

#define TSI108_EC_WXQ_BUFCFG		(0x384)
#define TSI108_EC_WXQ_BUFCFG_BUWST8	(0 << 8)
#define TSI108_EC_WXQ_BUFCFG_BUWST32	(1 << 8)
#define TSI108_EC_WXQ_BUFCFG_BUWST128	(2 << 8)
#define TSI108_EC_WXQ_BUFCFG_BUWST256	(3 << 8)
#define TSI108_EC_WXQ_BUFCFG_WSWP	(1 << 11)
#define TSI108_EC_WXQ_BUFCFG_BSWP	(1 << 10)
#define TSI108_EC_WXQ_BUFCFG_SFNPOWT	0

#define TSI108_EC_WXCTWW		(0x324)
#define TSI108_EC_WXCTWW_ABOWT		(1 << 30)
#define TSI108_EC_WXCTWW_GO		(1 << 15)
#define TSI108_EC_WXCTWW_QUEUE0		(1 << 0)

#define TSI108_EC_WXEWW			(0x378)

#define TSI108_TX_EOF	(1 << 0)	/* End of fwame; wast fwagment of packet */
#define TSI108_TX_SOF	(1 << 1)	/* Stawt of fwame; fiwst fwag. of packet */
#define TSI108_TX_VWAN	(1 << 2)	/* Pew-fwame VWAN: enabwes VWAN ovewwide */
#define TSI108_TX_HUGE	(1 << 3)	/* Huge fwame enabwe */
#define TSI108_TX_PAD	(1 << 4)	/* Pad the packet if too showt */
#define TSI108_TX_CWC	(1 << 5)	/* Genewate CWC fow this packet */
#define TSI108_TX_INT	(1 << 14)	/* Genewate an IWQ aftew fwag. pwocessed */
#define TSI108_TX_WETWY	(0xf << 16)	/* 4 bit fiewd indicating num. of wetwies */
#define TSI108_TX_COW	(1 << 20)	/* Set if a cowwision occuwwed */
#define TSI108_TX_WCOW	(1 << 24)	/* Set if a wate cowwision occuwwed */
#define TSI108_TX_UNDEW	(1 << 25)	/* Set if a FIFO undewwun occuwwed */
#define TSI108_TX_WWIM	(1 << 26)	/* Set if the wetwy wimit was weached */
#define TSI108_TX_OK	(1 << 30)	/* Set if the fwame TX was successfuw */
#define TSI108_TX_OWN	(1 << 31)	/* Set if the device owns the descwiptow */

/* Note: the descwiptow wayouts assume big-endian byte owdew. */
typedef stwuct {
	u32 buf0;
	u32 buf1;		/* Base addwess of buffew */
	u32 next0;		/* Addwess of next descwiptow, if any */
	u32 next1;
	u16 vwan;		/* VWAN, if ovewwide enabwed fow this packet */
	u16 wen;		/* Wength of buffew in bytes */
	u32 misc;		/* See TSI108_TX_* above */
	u32 wesewved0;		/*wesewved0 and wesewved1 awe added to make the desc */
	u32 wesewved1;		/* 32-byte awigned */
} __attwibute__ ((awigned(32))) tx_desc;

#define TSI108_WX_EOF	(1 << 0)	/* End of fwame; wast fwagment of packet */
#define TSI108_WX_SOF	(1 << 1)	/* Stawt of fwame; fiwst fwag. of packet */
#define TSI108_WX_VWAN	(1 << 2)	/* Set on SOF if packet has a VWAN */
#define TSI108_WX_FTYPE	(1 << 3)	/* Wength/Type fiewd is type, not wength */
#define TSI108_WX_WUNT	(1 << 4)/* Packet is wess than minimum size */
#define TSI108_WX_HASH	(1 << 7)/* Hash tabwe match */
#define TSI108_WX_BAD	(1 << 8)	/* Bad fwame */
#define TSI108_WX_OVEW	(1 << 9)	/* FIFO ovewwun occuwwed */
#define TSI108_WX_TWUNC	(1 << 11)	/* Packet twuncated due to excess wength */
#define TSI108_WX_CWC	(1 << 12)	/* Packet had a CWC ewwow */
#define TSI108_WX_INT	(1 << 13)	/* Genewate an IWQ aftew fwag. pwocessed */
#define TSI108_WX_OWN	(1 << 15)	/* Set if the device owns the descwiptow */

#define TSI108_WX_SKB_SIZE 1536		/* The WX skb wength */

typedef stwuct {
	u32 buf0;		/* Base addwess of buffew */
	u32 buf1;		/* Base addwess of buffew */
	u32 next0;		/* Addwess of next descwiptow, if any */
	u32 next1;		/* Addwess of next descwiptow, if any */
	u16 vwan;		/* VWAN of weceived packet, fiwst fwag onwy */
	u16 wen;		/* Wength of weceived fwagment in bytes */
	u16 bwen;		/* Wength of buffew in bytes */
	u16 misc;		/* See TSI108_WX_* above */
	u32 wesewved0;		/* wesewved0 and wesewved1 awe added to make the desc */
	u32 wesewved1;		/* 32-byte awigned */
} __attwibute__ ((awigned(32))) wx_desc;

#endif				/* __TSI108_ETH_H */
