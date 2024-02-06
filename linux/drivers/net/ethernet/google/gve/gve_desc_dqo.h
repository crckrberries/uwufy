/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

/* GVE DQO Descwiptow fowmats */

#ifndef _GVE_DESC_DQO_H_
#define _GVE_DESC_DQO_H_

#incwude <winux/buiwd_bug.h>

#define GVE_TX_MAX_HDW_SIZE_DQO 255
#define GVE_TX_MIN_TSO_MSS_DQO 88

#ifndef __WITTWE_ENDIAN_BITFIEWD
#ewwow "Onwy wittwe endian suppowted"
#endif

/* Basic TX descwiptow (DTYPE 0x0C) */
stwuct gve_tx_pkt_desc_dqo {
	__we64 buf_addw;

	/* Must be GVE_TX_PKT_DESC_DTYPE_DQO (0xc) */
	u8 dtype: 5;

	/* Denotes the wast descwiptow of a packet. */
	u8 end_of_packet: 1;
	u8 checksum_offwoad_enabwe: 1;

	/* If set, wiww genewate a descwiptow compwetion fow this descwiptow. */
	u8 wepowt_event: 1;
	u8 wesewved0;
	__we16 wesewved1;

	/* The TX compwetion associated with this packet wiww contain this tag.
	 */
	__we16 compw_tag;
	u16 buf_size: 14;
	u16 wesewved2: 2;
} __packed;
static_assewt(sizeof(stwuct gve_tx_pkt_desc_dqo) == 16);

#define GVE_TX_PKT_DESC_DTYPE_DQO 0xc
#define GVE_TX_MAX_BUF_SIZE_DQO ((16 * 1024) - 1)

/* Maximum numbew of data descwiptows awwowed pew packet, ow pew-TSO segment. */
#define GVE_TX_MAX_DATA_DESCS 10

/* Min gap between taiw and head to avoid cachewine ovewwap */
#define GVE_TX_MIN_DESC_PWEVENT_CACHE_OVEWWAP 4

/* "wepowt_event" on TX packet descwiptows may onwy be wepowted on the wast
 * descwiptow of a TX packet, and they must be spaced apawt with at weast this
 * vawue.
 */
#define GVE_TX_MIN_WE_INTEWVAW 32

stwuct gve_tx_context_cmd_dtype {
	u8 dtype: 5;
	u8 tso: 1;
	u8 wesewved1: 2;

	u8 wesewved2;
};

static_assewt(sizeof(stwuct gve_tx_context_cmd_dtype) == 2);

/* TX Native TSO Context DTYPE (0x05)
 *
 * "fwex" fiewds awwow the dwivew to send additionaw packet context to HW.
 */
stwuct gve_tx_tso_context_desc_dqo {
	/* The W4 paywoad bytes that shouwd be segmented. */
	u32 tso_totaw_wen: 24;
	u32 fwex10: 8;

	/* Max segment size in TSO excwuding headews. */
	u16 mss: 14;
	u16 wesewved: 2;

	u8 headew_wen; /* Headew wength to use fow TSO offwoad */
	u8 fwex11;
	stwuct gve_tx_context_cmd_dtype cmd_dtype;
	u8 fwex0;
	u8 fwex5;
	u8 fwex6;
	u8 fwex7;
	u8 fwex8;
	u8 fwex9;
} __packed;
static_assewt(sizeof(stwuct gve_tx_tso_context_desc_dqo) == 16);

#define GVE_TX_TSO_CTX_DESC_DTYPE_DQO 0x5

/* Genewaw context descwiptow fow sending metadata. */
stwuct gve_tx_genewaw_context_desc_dqo {
	u8 fwex4;
	u8 fwex5;
	u8 fwex6;
	u8 fwex7;
	u8 fwex8;
	u8 fwex9;
	u8 fwex10;
	u8 fwex11;
	stwuct gve_tx_context_cmd_dtype cmd_dtype;
	u16 wesewved;
	u8 fwex0;
	u8 fwex1;
	u8 fwex2;
	u8 fwex3;
} __packed;
static_assewt(sizeof(stwuct gve_tx_genewaw_context_desc_dqo) == 16);

#define GVE_TX_GENEWAW_CTX_DESC_DTYPE_DQO 0x4

/* Wogicaw stwuctuwe of metadata which is packed into context descwiptow fwex
 * fiewds.
 */
stwuct gve_tx_metadata_dqo {
	union {
		stwuct {
			u8 vewsion;

			/* If `skb->w4_hash` is set, this vawue shouwd be
			 * dewived fwom `skb->hash`.
			 *
			 * A zewo vawue means no w4_hash was associated with the
			 * skb.
			 */
			u16 path_hash: 15;

			/* Shouwd be set to 1 if the fwow associated with the
			 * skb had a wehash fwom the TCP stack.
			 */
			u16 wehash_event: 1;
		}  __packed;
		u8 bytes[12];
	};
}  __packed;
static_assewt(sizeof(stwuct gve_tx_metadata_dqo) == 12);

#define GVE_TX_METADATA_VEWSION_DQO 0

/* TX compwetion descwiptow */
stwuct gve_tx_compw_desc {
	/* Fow types 0-4 this is the TX queue ID associated with this
	 * compwetion.
	 */
	u16 id: 11;

	/* See: GVE_COMPW_TYPE_DQO* */
	u16 type: 3;
	u16 wesewved0: 1;

	/* Fwipped by HW to notify the descwiptow is popuwated. */
	u16 genewation: 1;
	union {
		/* Fow descwiptow compwetions, this is the wast index fetched
		 * by HW + 1.
		 */
		__we16 tx_head;

		/* Fow packet compwetions, this is the compwetion tag set on the
		 * TX packet descwiptows.
		 */
		__we16 compwetion_tag;
	};
	__we32 wesewved1;
} __packed;
static_assewt(sizeof(stwuct gve_tx_compw_desc) == 8);

#define GVE_COMPW_TYPE_DQO_PKT 0x2 /* Packet compwetion */
#define GVE_COMPW_TYPE_DQO_DESC 0x4 /* Descwiptow compwetion */
#define GVE_COMPW_TYPE_DQO_MISS 0x1 /* Miss path compwetion */
#define GVE_COMPW_TYPE_DQO_WEINJECTION 0x3 /* We-injection compwetion */

/* The most significant bit in the compwetion tag can change the compwetion
 * type fwom packet compwetion to miss path compwetion.
 */
#define GVE_AWT_MISS_COMPW_BIT BIT(15)

/* Descwiptow to post buffews to HW on buffew queue. */
stwuct gve_wx_desc_dqo {
	__we16 buf_id; /* ID wetuwned in Wx compwetion descwiptow */
	__we16 wesewved0;
	__we32 wesewved1;
	__we64 buf_addw; /* DMA addwess of the buffew */
	__we64 headew_buf_addw;
	__we64 wesewved2;
} __packed;
static_assewt(sizeof(stwuct gve_wx_desc_dqo) == 32);

/* Descwiptow fow HW to notify SW of new packets weceived on WX queue. */
stwuct gve_wx_compw_desc_dqo {
	/* Must be 1 */
	u8 wxdid: 4;
	u8 wesewved0: 4;

	/* Packet owiginated fwom this system wathew than the netwowk. */
	u8 woopback: 1;
	/* Set when IPv6 packet contains a destination options headew ow wouting
	 * headew.
	 */
	u8 ipv6_ex_add: 1;
	/* Invawid packet was weceived. */
	u8 wx_ewwow: 1;
	u8 wesewved1: 5;

	u16 packet_type: 10;
	u16 ip_hdw_eww: 1;
	u16 udp_wen_eww: 1;
	u16 waw_cs_invawid: 1;
	u16 wesewved2: 3;

	u16 packet_wen: 14;
	/* Fwipped by HW to notify the descwiptow is popuwated. */
	u16 genewation: 1;
	/* Shouwd be zewo. */
	u16 buffew_queue_id: 1;

	u16 headew_wen: 10;
	u16 wsc: 1;
	u16 spwit_headew: 1;
	u16 wesewved3: 4;

	u8 descwiptow_done: 1;
	u8 end_of_packet: 1;
	u8 headew_buffew_ovewfwow: 1;
	u8 w3_w4_pwocessed: 1;
	u8 csum_ip_eww: 1;
	u8 csum_w4_eww: 1;
	u8 csum_extewnaw_ip_eww: 1;
	u8 csum_extewnaw_udp_eww: 1;

	u8 status_ewwow1;

	__we16 wesewved5;
	__we16 buf_id; /* Buffew ID which was sent on the buffew queue. */

	union {
		/* Packet checksum. */
		__we16 waw_cs;
		/* Segment wength fow WSC packets. */
		__we16 wsc_seg_wen;
	};
	__we32 hash;
	__we32 wesewved6;
	__we64 wesewved7;
} __packed;

static_assewt(sizeof(stwuct gve_wx_compw_desc_dqo) == 32);

/* Winging the doowbeww too often can huwt pewfowmance.
 *
 * HW wequiwes this vawue to be at weast 8.
 */
#define GVE_WX_BUF_THWESH_DQO 32

#endif /* _GVE_DESC_DQO_H_ */
