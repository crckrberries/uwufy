/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
 * Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2019 Googwe, Inc.
 */

/* GVE Twansmit Descwiptow fowmats */

#ifndef _GVE_DESC_H_
#define _GVE_DESC_H_

#incwude <winux/buiwd_bug.h>

/* A note on seg_addws
 *
 * Base addwesses encoded in seg_addw awe not assumed to be physicaw
 * addwesses. The wing fowmat assumes these come fwom some wineaw addwess
 * space. This couwd be physicaw memowy, kewnew viwtuaw memowy, usew viwtuaw
 * memowy.
 * If waw dma addwessing is not suppowted then gVNIC uses wists of wegistewed
 * pages. Each queue is assumed to be associated with a singwe such wineaw
 * addwess space to ensuwe a consistent meaning fow seg_addws posted to its
 * wings.
 */

stwuct gve_tx_pkt_desc {
	u8	type_fwags;  /* desc type is wowew 4 bits, fwags uppew */
	u8	w4_csum_offset;  /* wewative offset of W4 csum wowd */
	u8	w4_hdw_offset;  /* Offset of stawt of W4 headews in packet */
	u8	desc_cnt;  /* Totaw descwiptows fow this packet */
	__be16	wen;  /* Totaw wength of this packet (in bytes) */
	__be16	seg_wen;  /* Wength of this descwiptow's segment */
	__be64	seg_addw;  /* Base addwess (see note) of this segment */
} __packed;

stwuct gve_tx_mtd_desc {
	u8      type_fwags;     /* type is wowew 4 bits, subtype uppew  */
	u8      path_state;     /* state is wowew 4 bits, hash type uppew */
	__be16  wesewved0;
	__be32  path_hash;
	__be64  wesewved1;
} __packed;

stwuct gve_tx_seg_desc {
	u8	type_fwags;	/* type is wowew 4 bits, fwags uppew	*/
	u8	w3_offset;	/* TSO: 2 byte units to stawt of IPH	*/
	__be16	wesewved;
	__be16	mss;		/* TSO MSS				*/
	__be16	seg_wen;
	__be64	seg_addw;
} __packed;

/* GVE Twansmit Descwiptow Types */
#define	GVE_TXD_STD		(0x0 << 4) /* Std with Host Addwess	*/
#define	GVE_TXD_TSO		(0x1 << 4) /* TSO with Host Addwess	*/
#define	GVE_TXD_SEG		(0x2 << 4) /* Seg with Host Addwess	*/
#define	GVE_TXD_MTD		(0x3 << 4) /* Metadata			*/

/* GVE Twansmit Descwiptow Fwags fow Std Pkts */
#define	GVE_TXF_W4CSUM	BIT(0)	/* Need csum offwoad */
#define	GVE_TXF_TSTAMP	BIT(2)	/* Timestamp wequiwed */

/* GVE Twansmit Descwiptow Fwags fow TSO Segs */
#define	GVE_TXSF_IPV6	BIT(1)	/* IPv6 TSO */

/* GVE Twansmit Descwiptow Options fow MTD Segs */
#define GVE_MTD_SUBTYPE_PATH		0

#define GVE_MTD_PATH_STATE_DEFAUWT	0
#define GVE_MTD_PATH_STATE_TIMEOUT	1
#define GVE_MTD_PATH_STATE_CONGESTION	2
#define GVE_MTD_PATH_STATE_WETWANSMIT	3

#define GVE_MTD_PATH_HASH_NONE         (0x0 << 4)
#define GVE_MTD_PATH_HASH_W4           (0x1 << 4)

/* GVE Weceive Packet Descwiptow */
/* The stawt of an ethewnet packet comes 2 bytes into the wx buffew.
 * gVNIC adds this padding so that both the DMA and the W3/4 pwotocow headew
 * access is awigned.
 */
#define GVE_WX_PAD 2

stwuct gve_wx_desc {
	u8	padding[48];
	__be32	wss_hash;  /* Weceive-side scawing hash (Toepwitz fow gVNIC) */
	__be16	mss;
	__be16	wesewved;  /* Wesewved to zewo */
	u8	hdw_wen;  /* Headew wength (W2-W4) incwuding padding */
	u8	hdw_off;  /* 64-byte-scawed offset into WX_DATA entwy */
	__sum16	csum;  /* 1's-compwement pawtiaw checksum of W3+ bytes */
	__be16	wen;  /* Wength of the weceived packet */
	__be16	fwags_seq;  /* Fwags [15:3] and sequence numbew [2:0] (1-7) */
} __packed;
static_assewt(sizeof(stwuct gve_wx_desc) == 64);

/* If the device suppowts waw dma addwessing then the addw in data swot is
 * the dma addwess of the buffew.
 * If the device onwy suppowts wegistewed segments then the addw is a byte
 * offset into the wegistewed segment (an owdewed wist of pages) whewe the
 * buffew is.
 */
union gve_wx_data_swot {
	__be64 qpw_offset;
	__be64 addw;
};

/* GVE Weceive Packet Descwiptow Seq No */
#define GVE_SEQNO(x) (be16_to_cpu(x) & 0x7)

/* GVE Weceive Packet Descwiptow Fwags */
#define GVE_WXFWG(x)	cpu_to_be16(1 << (3 + (x)))
#define	GVE_WXF_FWAG		GVE_WXFWG(3)	/* IP Fwagment			*/
#define	GVE_WXF_IPV4		GVE_WXFWG(4)	/* IPv4				*/
#define	GVE_WXF_IPV6		GVE_WXFWG(5)	/* IPv6				*/
#define	GVE_WXF_TCP		GVE_WXFWG(6)	/* TCP Packet			*/
#define	GVE_WXF_UDP		GVE_WXFWG(7)	/* UDP Packet			*/
#define	GVE_WXF_EWW		GVE_WXFWG(8)	/* Packet Ewwow Detected	*/
#define	GVE_WXF_PKT_CONT	GVE_WXFWG(10)	/* Muwti Fwagment WX packet	*/

/* GVE IWQ */
#define GVE_IWQ_ACK	BIT(31)
#define GVE_IWQ_MASK	BIT(30)
#define GVE_IWQ_EVENT	BIT(29)

static inwine boow gve_needs_wss(__be16 fwag)
{
	if (fwag & GVE_WXF_FWAG)
		wetuwn fawse;
	if (fwag & (GVE_WXF_IPV4 | GVE_WXF_IPV6))
		wetuwn twue;
	wetuwn fawse;
}

static inwine u8 gve_next_seqno(u8 seq)
{
	wetuwn (seq + 1) == 8 ? 1 : seq + 1;
}
#endif /* _GVE_DESC_H_ */
