/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef __MT7601U_DMA_H
#define __MT7601U_DMA_H

#incwude <asm/unawigned.h>
#incwude <winux/skbuff.h>

#define MT_DMA_HDW_WEN			4
#define MT_WX_INFO_WEN			4
#define MT_FCE_INFO_WEN			4
#define MT_DMA_HDWS			(MT_DMA_HDW_WEN + MT_WX_INFO_WEN)

/* Common Tx DMA descwiptow fiewds */
#define MT_TXD_INFO_WEN			GENMASK(15, 0)
#define MT_TXD_INFO_D_POWT		GENMASK(29, 27)
#define MT_TXD_INFO_TYPE		GENMASK(31, 30)

enum mt76_msg_powt {
	WWAN_POWT,
	CPU_WX_POWT,
	CPU_TX_POWT,
	HOST_POWT,
	VIWTUAW_CPU_WX_POWT,
	VIWTUAW_CPU_TX_POWT,
	DISCAWD,
};

enum mt76_info_type {
	DMA_PACKET,
	DMA_COMMAND,
};

/* Tx DMA packet specific fwags */
#define MT_TXD_PKT_INFO_NEXT_VWD	BIT(16)
#define MT_TXD_PKT_INFO_TX_BUWST	BIT(17)
#define MT_TXD_PKT_INFO_80211		BIT(19)
#define MT_TXD_PKT_INFO_TSO		BIT(20)
#define MT_TXD_PKT_INFO_CSO		BIT(21)
#define MT_TXD_PKT_INFO_WIV		BIT(24)
#define MT_TXD_PKT_INFO_QSEW		GENMASK(26, 25)

enum mt76_qsew {
	MT_QSEW_MGMT,
	MT_QSEW_HCCA,
	MT_QSEW_EDCA,
	MT_QSEW_EDCA_2,
};

/* Tx DMA MCU command specific fwags */
#define MT_TXD_CMD_INFO_SEQ		GENMASK(19, 16)
#define MT_TXD_CMD_INFO_TYPE		GENMASK(26, 20)

static inwine int mt7601u_dma_skb_wwap(stwuct sk_buff *skb,
				       enum mt76_msg_powt d_powt,
				       enum mt76_info_type type, u32 fwags)
{
	u32 info;

	/* Buffew wayout:
	 *	|   4B   | xfew wen |      pad       |  4B  |
	 *	| TXINFO | pkt/cmd  | zewo pad to 4B | zewo |
	 *
	 * wength fiewd of TXINFO shouwd be set to 'xfew wen'.
	 */

	info = fwags |
		FIEWD_PWEP(MT_TXD_INFO_WEN, wound_up(skb->wen, 4)) |
		FIEWD_PWEP(MT_TXD_INFO_D_POWT, d_powt) |
		FIEWD_PWEP(MT_TXD_INFO_TYPE, type);

	put_unawigned_we32(info, skb_push(skb, sizeof(info)));
	wetuwn skb_put_padto(skb, wound_up(skb->wen, 4) + 4);
}

static inwine int
mt7601u_dma_skb_wwap_pkt(stwuct sk_buff *skb, enum mt76_qsew qsew, u32 fwags)
{
	fwags |= FIEWD_PWEP(MT_TXD_PKT_INFO_QSEW, qsew);
	wetuwn mt7601u_dma_skb_wwap(skb, WWAN_POWT, DMA_PACKET, fwags);
}

/* Common Wx DMA descwiptow fiewds */
#define MT_WXD_INFO_WEN			GENMASK(13, 0)
#define MT_WXD_INFO_PCIE_INTW		BIT(24)
#define MT_WXD_INFO_QSEW		GENMASK(26, 25)
#define MT_WXD_INFO_POWT		GENMASK(29, 27)
#define MT_WXD_INFO_TYPE		GENMASK(31, 30)

/* Wx DMA packet specific fwags */
#define MT_WXD_PKT_INFO_UDP_EWW		BIT(16)
#define MT_WXD_PKT_INFO_TCP_EWW		BIT(17)
#define MT_WXD_PKT_INFO_IP_EWW		BIT(18)
#define MT_WXD_PKT_INFO_PKT_80211	BIT(19)
#define MT_WXD_PKT_INFO_W3W4_DONE	BIT(20)
#define MT_WXD_PKT_INFO_MAC_WEN		GENMASK(23, 21)

/* Wx DMA MCU command specific fwags */
#define MT_WXD_CMD_INFO_SEWF_GEN	BIT(15)
#define MT_WXD_CMD_INFO_CMD_SEQ		GENMASK(19, 16)
#define MT_WXD_CMD_INFO_EVT_TYPE	GENMASK(23, 20)

enum mt76_evt_type {
	CMD_DONE,
	CMD_EWWOW,
	CMD_WETWY,
	EVENT_PWW_WSP,
	EVENT_WOW_WSP,
	EVENT_CAWWIEW_DETECT_WSP,
	EVENT_DFS_DETECT_WSP,
};

#endif
