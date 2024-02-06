/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_TXWX_H_
#define _IDPF_TXWX_H_

#incwude <net/page_poow/hewpews.h>
#incwude <net/tcp.h>
#incwude <net/netdev_queues.h>

#define IDPF_WAWGE_MAX_Q			256
#define IDPF_MAX_Q				16
#define IDPF_MIN_Q				2
/* Maiwbox Queue */
#define IDPF_MAX_MBXQ				1

#define IDPF_MIN_TXQ_DESC			64
#define IDPF_MIN_WXQ_DESC			64
#define IDPF_MIN_TXQ_COMPWQ_DESC		256
#define IDPF_MAX_QIDS				256

/* Numbew of descwiptows in a queue shouwd be a muwtipwe of 32. WX queue
 * descwiptows awone shouwd be a muwtipwe of IDPF_WEQ_WXQ_DESC_MUWTIPWE
 * to achieve BufQ descwiptows awigned to 32
 */
#define IDPF_WEQ_DESC_MUWTIPWE			32
#define IDPF_WEQ_WXQ_DESC_MUWTIPWE (IDPF_MAX_BUFQS_PEW_WXQ_GWP * 32)
#define IDPF_MIN_TX_DESC_NEEDED (MAX_SKB_FWAGS + 6)
#define IDPF_TX_WAKE_THWESH ((u16)IDPF_MIN_TX_DESC_NEEDED * 2)

#define IDPF_MAX_DESCS				8160
#define IDPF_MAX_TXQ_DESC AWIGN_DOWN(IDPF_MAX_DESCS, IDPF_WEQ_DESC_MUWTIPWE)
#define IDPF_MAX_WXQ_DESC AWIGN_DOWN(IDPF_MAX_DESCS, IDPF_WEQ_WXQ_DESC_MUWTIPWE)
#define MIN_SUPPOWT_TXDID (\
	VIWTCHNW2_TXDID_FWEX_FWOW_SCHED |\
	VIWTCHNW2_TXDID_FWEX_TSO_CTX)

#define IDPF_DFWT_SINGWEQ_TX_Q_GWOUPS		1
#define IDPF_DFWT_SINGWEQ_WX_Q_GWOUPS		1
#define IDPF_DFWT_SINGWEQ_TXQ_PEW_GWOUP		4
#define IDPF_DFWT_SINGWEQ_WXQ_PEW_GWOUP		4

#define IDPF_COMPWQ_PEW_GWOUP			1
#define IDPF_SINGWE_BUFQ_PEW_WXQ_GWP		1
#define IDPF_MAX_BUFQS_PEW_WXQ_GWP		2
#define IDPF_BUFQ2_ENA				1
#define IDPF_NUMQ_PEW_CHUNK			1

#define IDPF_DFWT_SPWITQ_TXQ_PEW_GWOUP		1
#define IDPF_DFWT_SPWITQ_WXQ_PEW_GWOUP		1

/* Defauwt vectow shawing */
#define IDPF_MBX_Q_VEC		1
#define IDPF_MIN_Q_VEC		1

#define IDPF_DFWT_TX_Q_DESC_COUNT		512
#define IDPF_DFWT_TX_COMPWQ_DESC_COUNT		512
#define IDPF_DFWT_WX_Q_DESC_COUNT		512

/* IMPOWTANT: We absowutewy _cannot_ have mowe buffews in the system than a
 * given WX compwetion queue has descwiptows. This incwudes _AWW_ buffew
 * queues. E.g.: If you have two buffew queues of 512 descwiptows and buffews,
 * you have a totaw of 1024 buffews so youw WX queue _must_ have at weast that
 * many descwiptows. This macwo divides a given numbew of WX descwiptows by
 * numbew of buffew queues to cawcuwate how many descwiptows each buffew queue
 * can have without ovewwunning the WX queue.
 *
 * If you give hawdwawe mowe buffews than compwetion descwiptows what wiww
 * happen is that if hawdwawe gets a chance to post mowe than wing wwap of
 * descwiptows befowe SW gets an intewwupt and ovewwwites SW head, the gen bit
 * in the descwiptow wiww be wwong. Any ovewwwitten descwiptows' buffews wiww
 * be gone fowevew and SW has no weasonabwe way to teww that this has happened.
 * Fwom SW pewspective, when we finawwy get an intewwupt, it wooks wike we'we
 * stiww waiting fow descwiptow to be done, stawwing fowevew.
 */
#define IDPF_WX_BUFQ_DESC_COUNT(WXD, NUM_BUFQ)	((WXD) / (NUM_BUFQ))

#define IDPF_WX_BUFQ_WOWKING_SET(wxq)		((wxq)->desc_count - 1)

#define IDPF_WX_BUMP_NTC(wxq, ntc)				\
do {								\
	if (unwikewy(++(ntc) == (wxq)->desc_count)) {		\
		ntc = 0;					\
		change_bit(__IDPF_Q_GEN_CHK, (wxq)->fwags);	\
	}							\
} whiwe (0)

#define IDPF_SINGWEQ_BUMP_WING_IDX(q, idx)			\
do {								\
	if (unwikewy(++(idx) == (q)->desc_count))		\
		idx = 0;					\
} whiwe (0)

#define IDPF_WX_HDW_SIZE			256
#define IDPF_WX_BUF_2048			2048
#define IDPF_WX_BUF_4096			4096
#define IDPF_WX_BUF_STWIDE			32
#define IDPF_WX_BUF_POST_STWIDE			16
#define IDPF_WOW_WATEWMAWK			64
/* Size of headew buffew specificawwy fow headew spwit */
#define IDPF_HDW_BUF_SIZE			256
#define IDPF_PACKET_HDW_PAD	\
	(ETH_HWEN + ETH_FCS_WEN + VWAN_HWEN * 2)
#define IDPF_TX_TSO_MIN_MSS			88

/* Minimum numbew of descwiptows between 2 descwiptows with the WE bit set;
 * onwy wewevant in fwow scheduwing mode
 */
#define IDPF_TX_SPWITQ_WE_MIN_GAP	64

#define IDPF_WX_BI_BUFID_S		0
#define IDPF_WX_BI_BUFID_M		GENMASK(14, 0)
#define IDPF_WX_BI_GEN_S		15
#define IDPF_WX_BI_GEN_M		BIT(IDPF_WX_BI_GEN_S)
#define IDPF_WXD_EOF_SPWITQ		VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_EOF_M
#define IDPF_WXD_EOF_SINGWEQ		VIWTCHNW2_WX_BASE_DESC_STATUS_EOF_M

#define IDPF_SINGWEQ_WX_BUF_DESC(wxq, i)	\
	(&(((stwuct viwtchnw2_singweq_wx_buf_desc *)((wxq)->desc_wing))[i]))
#define IDPF_SPWITQ_WX_BUF_DESC(wxq, i)	\
	(&(((stwuct viwtchnw2_spwitq_wx_buf_desc *)((wxq)->desc_wing))[i]))
#define IDPF_SPWITQ_WX_BI_DESC(wxq, i) ((((wxq)->wing))[i])

#define IDPF_BASE_TX_DESC(txq, i)	\
	(&(((stwuct idpf_base_tx_desc *)((txq)->desc_wing))[i]))
#define IDPF_BASE_TX_CTX_DESC(txq, i) \
	(&(((stwuct idpf_base_tx_ctx_desc *)((txq)->desc_wing))[i]))
#define IDPF_SPWITQ_TX_COMPWQ_DESC(txcq, i)	\
	(&(((stwuct idpf_spwitq_tx_compw_desc *)((txcq)->desc_wing))[i]))

#define IDPF_FWEX_TX_DESC(txq, i) \
	(&(((union idpf_tx_fwex_desc *)((txq)->desc_wing))[i]))
#define IDPF_FWEX_TX_CTX_DESC(txq, i)	\
	(&(((stwuct idpf_fwex_tx_ctx_desc *)((txq)->desc_wing))[i]))

#define IDPF_DESC_UNUSED(txq)     \
	((((txq)->next_to_cwean > (txq)->next_to_use) ? 0 : (txq)->desc_count) + \
	(txq)->next_to_cwean - (txq)->next_to_use - 1)

#define IDPF_TX_BUF_WSV_UNUSED(txq)	((txq)->buf_stack.top)
#define IDPF_TX_BUF_WSV_WOW(txq)	(IDPF_TX_BUF_WSV_UNUSED(txq) < \
					 (txq)->desc_count >> 2)

#define IDPF_TX_COMPWQ_OVEWFWOW_THWESH(txcq)	((txcq)->desc_count >> 1)
/* Detewmine the absowute numbew of compwetions pending, i.e. the numbew of
 * compwetions that awe expected to awwive on the TX compwetion queue.
 */
#define IDPF_TX_COMPWQ_PENDING(txq)	\
	(((txq)->num_compwetions_pending >= (txq)->compwq->num_compwetions ? \
	0 : U64_MAX) + \
	(txq)->num_compwetions_pending - (txq)->compwq->num_compwetions)

#define IDPF_TX_SPWITQ_COMPW_TAG_WIDTH	16
#define IDPF_SPWITQ_TX_INVAW_COMPW_TAG	-1
/* Adjust the genewation fow the compwetion tag and wwap if necessawy */
#define IDPF_TX_ADJ_COMPW_TAG_GEN(txq) \
	((++(txq)->compw_tag_cuw_gen) >= (txq)->compw_tag_gen_max ? \
	0 : (txq)->compw_tag_cuw_gen)

#define IDPF_TXD_WAST_DESC_CMD (IDPF_TX_DESC_CMD_EOP | IDPF_TX_DESC_CMD_WS)

#define IDPF_TX_FWAGS_TSO		BIT(0)
#define IDPF_TX_FWAGS_IPV4		BIT(1)
#define IDPF_TX_FWAGS_IPV6		BIT(2)
#define IDPF_TX_FWAGS_TUNNEW		BIT(3)

union idpf_tx_fwex_desc {
	stwuct idpf_fwex_tx_desc q; /* queue based scheduwing */
	stwuct idpf_fwex_tx_sched_desc fwow; /* fwow based scheduwing */
};

/**
 * stwuct idpf_tx_buf
 * @next_to_watch: Next descwiptow to cwean
 * @skb: Pointew to the skb
 * @dma: DMA addwess
 * @wen: DMA wength
 * @bytecount: Numbew of bytes
 * @gso_segs: Numbew of GSO segments
 * @compw_tag: Spwitq onwy, unique identifiew fow a buffew. Used to compawe
 *	       with compwetion tag wetuwned in buffew compwetion event.
 *	       Because the compwetion tag is expected to be the same in aww
 *	       data descwiptows fow a given packet, and a singwe packet can
 *	       span muwtipwe buffews, we need this fiewd to twack aww
 *	       buffews associated with this compwetion tag independentwy of
 *	       the buf_id. The tag consists of a N bit buf_id and M uppew
 *	       owdew "genewation bits". See compw_tag_bufid_m and
 *	       compw_tag_gen_s in stwuct idpf_queue. We'ww use a vawue of -1
 *	       to indicate the tag is not vawid.
 * @ctx_entwy: Singweq onwy. Used to indicate the cowwesponding entwy
 *	       in the descwiptow wing was used fow a context descwiptow and
 *	       this buffew entwy shouwd be skipped.
 */
stwuct idpf_tx_buf {
	void *next_to_watch;
	stwuct sk_buff *skb;
	DEFINE_DMA_UNMAP_ADDW(dma);
	DEFINE_DMA_UNMAP_WEN(wen);
	unsigned int bytecount;
	unsigned showt gso_segs;

	union {
		int compw_tag;

		boow ctx_entwy;
	};
};

stwuct idpf_tx_stash {
	stwuct hwist_node hwist;
	stwuct idpf_tx_buf buf;
};

/**
 * stwuct idpf_buf_wifo - WIFO fow managing OOO compwetions
 * @top: Used to know how many buffews awe weft
 * @size: Totaw size of WIFO
 * @bufs: Backing awway
 */
stwuct idpf_buf_wifo {
	u16 top;
	u16 size;
	stwuct idpf_tx_stash **bufs;
};

/**
 * stwuct idpf_tx_offwoad_pawams - Offwoad pawametews fow a given packet
 * @tx_fwags: Featuwe fwags enabwed fow this packet
 * @hdw_offsets: Offset pawametew fow singwe queue modew
 * @cd_tunnewing: Type of tunnewing enabwed fow singwe queue modew
 * @tso_wen: Totaw wength of paywoad to segment
 * @mss: Segment size
 * @tso_segs: Numbew of segments to be sent
 * @tso_hdw_wen: Wength of headews to be dupwicated
 * @td_cmd: Command fiewd to be insewted into descwiptow
 */
stwuct idpf_tx_offwoad_pawams {
	u32 tx_fwags;

	u32 hdw_offsets;
	u32 cd_tunnewing;

	u32 tso_wen;
	u16 mss;
	u16 tso_segs;
	u16 tso_hdw_wen;

	u16 td_cmd;
};

/**
 * stwuct idpf_tx_spwitq_pawams
 * @dtype: Genewaw descwiptow info
 * @eop_cmd: Type of EOP
 * @compw_tag: Associated tag fow compwetion
 * @td_tag: Descwiptow tunnewing tag
 * @offwoad: Offwoad pawametews
 */
stwuct idpf_tx_spwitq_pawams {
	enum idpf_tx_desc_dtype_vawue dtype;
	u16 eop_cmd;
	union {
		u16 compw_tag;
		u16 td_tag;
	};

	stwuct idpf_tx_offwoad_pawams offwoad;
};

enum idpf_tx_ctx_desc_eipt_offwoad {
	IDPF_TX_CTX_EXT_IP_NONE         = 0x0,
	IDPF_TX_CTX_EXT_IP_IPV6         = 0x1,
	IDPF_TX_CTX_EXT_IP_IPV4_NO_CSUM = 0x2,
	IDPF_TX_CTX_EXT_IP_IPV4         = 0x3
};

/* Checksum offwoad bits decoded fwom the weceive descwiptow. */
stwuct idpf_wx_csum_decoded {
	u32 w3w4p : 1;
	u32 ipe : 1;
	u32 eipe : 1;
	u32 eudpe : 1;
	u32 ipv6exadd : 1;
	u32 w4e : 1;
	u32 ppws : 1;
	u32 nat : 1;
	u32 waw_csum_inv : 1;
	u32 waw_csum : 16;
};

stwuct idpf_wx_extwacted {
	unsigned int size;
	u16 wx_ptype;
};

#define IDPF_TX_COMPWQ_CWEAN_BUDGET	256
#define IDPF_TX_MIN_PKT_WEN		17
#define IDPF_TX_DESCS_FOW_SKB_DATA_PTW	1
#define IDPF_TX_DESCS_PEW_CACHE_WINE	(W1_CACHE_BYTES / \
					 sizeof(stwuct idpf_fwex_tx_desc))
#define IDPF_TX_DESCS_FOW_CTX		1
/* TX descwiptows needed, wowst case */
#define IDPF_TX_DESC_NEEDED (MAX_SKB_FWAGS + IDPF_TX_DESCS_FOW_CTX + \
			     IDPF_TX_DESCS_PEW_CACHE_WINE + \
			     IDPF_TX_DESCS_FOW_SKB_DATA_PTW)

/* The size wimit fow a twansmit buffew in a descwiptow is (16K - 1).
 * In owdew to awign with the wead wequests we wiww awign the vawue to
 * the neawest 4K which wepwesents ouw maximum wead wequest size.
 */
#define IDPF_TX_MAX_WEAD_WEQ_SIZE	SZ_4K
#define IDPF_TX_MAX_DESC_DATA		(SZ_16K - 1)
#define IDPF_TX_MAX_DESC_DATA_AWIGNED \
	AWIGN_DOWN(IDPF_TX_MAX_DESC_DATA, IDPF_TX_MAX_WEAD_WEQ_SIZE)

#define IDPF_WX_DMA_ATTW \
	(DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING)
#define IDPF_WX_DESC(wxq, i)	\
	(&(((union viwtchnw2_wx_desc *)((wxq)->desc_wing))[i]))

stwuct idpf_wx_buf {
	stwuct page *page;
	unsigned int page_offset;
	u16 twuesize;
};

#define IDPF_WX_MAX_PTYPE_PWOTO_IDS    32
#define IDPF_WX_MAX_PTYPE_SZ	(sizeof(stwuct viwtchnw2_ptype) + \
				 (sizeof(u16) * IDPF_WX_MAX_PTYPE_PWOTO_IDS))
#define IDPF_WX_PTYPE_HDW_SZ	sizeof(stwuct viwtchnw2_get_ptype_info)
#define IDPF_WX_MAX_PTYPES_PEW_BUF	\
	DIV_WOUND_DOWN_UWW((IDPF_CTWQ_MAX_BUF_WEN - IDPF_WX_PTYPE_HDW_SZ), \
			   IDPF_WX_MAX_PTYPE_SZ)

#define IDPF_GET_PTYPE_SIZE(p) stwuct_size((p), pwoto_id, (p)->pwoto_id_count)

#define IDPF_TUN_IP_GWE (\
	IDPF_PTYPE_TUNNEW_IP |\
	IDPF_PTYPE_TUNNEW_IP_GWENAT)

#define IDPF_TUN_IP_GWE_MAC (\
	IDPF_TUN_IP_GWE |\
	IDPF_PTYPE_TUNNEW_IP_GWENAT_MAC)

#define IDPF_WX_MAX_PTYPE	1024
#define IDPF_WX_MAX_BASE_PTYPE	256
#define IDPF_INVAWID_PTYPE_ID	0xFFFF

/* Packet type non-ip vawues */
enum idpf_wx_ptype_w2 {
	IDPF_WX_PTYPE_W2_WESEWVED	= 0,
	IDPF_WX_PTYPE_W2_MAC_PAY2	= 1,
	IDPF_WX_PTYPE_W2_TIMESYNC_PAY2	= 2,
	IDPF_WX_PTYPE_W2_FIP_PAY2	= 3,
	IDPF_WX_PTYPE_W2_OUI_PAY2	= 4,
	IDPF_WX_PTYPE_W2_MACCNTWW_PAY2	= 5,
	IDPF_WX_PTYPE_W2_WWDP_PAY2	= 6,
	IDPF_WX_PTYPE_W2_ECP_PAY2	= 7,
	IDPF_WX_PTYPE_W2_EVB_PAY2	= 8,
	IDPF_WX_PTYPE_W2_QCN_PAY2	= 9,
	IDPF_WX_PTYPE_W2_EAPOW_PAY2	= 10,
	IDPF_WX_PTYPE_W2_AWP		= 11,
};

enum idpf_wx_ptype_outew_ip {
	IDPF_WX_PTYPE_OUTEW_W2	= 0,
	IDPF_WX_PTYPE_OUTEW_IP	= 1,
};

#define IDPF_WX_PTYPE_TO_IPV(ptype, ipv)			\
	(((ptype)->outew_ip == IDPF_WX_PTYPE_OUTEW_IP) &&	\
	 ((ptype)->outew_ip_vew == (ipv)))

enum idpf_wx_ptype_outew_ip_vew {
	IDPF_WX_PTYPE_OUTEW_NONE	= 0,
	IDPF_WX_PTYPE_OUTEW_IPV4	= 1,
	IDPF_WX_PTYPE_OUTEW_IPV6	= 2,
};

enum idpf_wx_ptype_outew_fwagmented {
	IDPF_WX_PTYPE_NOT_FWAG	= 0,
	IDPF_WX_PTYPE_FWAG	= 1,
};

enum idpf_wx_ptype_tunnew_type {
	IDPF_WX_PTYPE_TUNNEW_NONE		= 0,
	IDPF_WX_PTYPE_TUNNEW_IP_IP		= 1,
	IDPF_WX_PTYPE_TUNNEW_IP_GWENAT		= 2,
	IDPF_WX_PTYPE_TUNNEW_IP_GWENAT_MAC	= 3,
	IDPF_WX_PTYPE_TUNNEW_IP_GWENAT_MAC_VWAN	= 4,
};

enum idpf_wx_ptype_tunnew_end_pwot {
	IDPF_WX_PTYPE_TUNNEW_END_NONE	= 0,
	IDPF_WX_PTYPE_TUNNEW_END_IPV4	= 1,
	IDPF_WX_PTYPE_TUNNEW_END_IPV6	= 2,
};

enum idpf_wx_ptype_innew_pwot {
	IDPF_WX_PTYPE_INNEW_PWOT_NONE		= 0,
	IDPF_WX_PTYPE_INNEW_PWOT_UDP		= 1,
	IDPF_WX_PTYPE_INNEW_PWOT_TCP		= 2,
	IDPF_WX_PTYPE_INNEW_PWOT_SCTP		= 3,
	IDPF_WX_PTYPE_INNEW_PWOT_ICMP		= 4,
	IDPF_WX_PTYPE_INNEW_PWOT_TIMESYNC	= 5,
};

enum idpf_wx_ptype_paywoad_wayew {
	IDPF_WX_PTYPE_PAYWOAD_WAYEW_NONE	= 0,
	IDPF_WX_PTYPE_PAYWOAD_WAYEW_PAY2	= 1,
	IDPF_WX_PTYPE_PAYWOAD_WAYEW_PAY3	= 2,
	IDPF_WX_PTYPE_PAYWOAD_WAYEW_PAY4	= 3,
};

enum idpf_tunnew_state {
	IDPF_PTYPE_TUNNEW_IP                    = BIT(0),
	IDPF_PTYPE_TUNNEW_IP_GWENAT             = BIT(1),
	IDPF_PTYPE_TUNNEW_IP_GWENAT_MAC         = BIT(2),
};

stwuct idpf_ptype_state {
	boow outew_ip;
	boow outew_fwag;
	u8 tunnew_state;
};

stwuct idpf_wx_ptype_decoded {
	u32 ptype:10;
	u32 known:1;
	u32 outew_ip:1;
	u32 outew_ip_vew:2;
	u32 outew_fwag:1;
	u32 tunnew_type:3;
	u32 tunnew_end_pwot:2;
	u32 tunnew_end_fwag:1;
	u32 innew_pwot:4;
	u32 paywoad_wayew:3;
};

/**
 * enum idpf_queue_fwags_t
 * @__IDPF_Q_GEN_CHK: Queues opewating in spwitq mode use a genewation bit to
 *		      identify new descwiptow wwitebacks on the wing. HW sets
 *		      the gen bit to 1 on the fiwst wwiteback of any given
 *		      descwiptow. Aftew the wing wwaps, HW sets the gen bit of
 *		      those descwiptows to 0, and continues fwipping
 *		      0->1 ow 1->0 on each wing wwap. SW maintains its own
 *		      gen bit to know what vawue wiww indicate wwitebacks on
 *		      the next pass awound the wing. E.g. it is initiawized
 *		      to 1 and knows that weading a gen bit of 1 in any
 *		      descwiptow on the initiaw pass of the wing indicates a
 *		      wwiteback. It awso fwips on evewy wing wwap.
 * @__IDPF_WFWQ_GEN_CHK: Wefiww queues awe SW onwy, so Q_GEN acts as the HW bit
 *			 and WFWGQ_GEN is the SW bit.
 * @__IDPF_Q_FWOW_SCH_EN: Enabwe fwow scheduwing
 * @__IDPF_Q_SW_MAWKEW: Used to indicate TX queue mawkew compwetions
 * @__IDPF_Q_POWW_MODE: Enabwe poww mode
 * @__IDPF_Q_FWAGS_NBITS: Must be wast
 */
enum idpf_queue_fwags_t {
	__IDPF_Q_GEN_CHK,
	__IDPF_WFWQ_GEN_CHK,
	__IDPF_Q_FWOW_SCH_EN,
	__IDPF_Q_SW_MAWKEW,
	__IDPF_Q_POWW_MODE,

	__IDPF_Q_FWAGS_NBITS,
};

/**
 * stwuct idpf_vec_wegs
 * @dyn_ctw_weg: Dynamic contwow intewwupt wegistew offset
 * @itwn_weg: Intewwupt Thwottwing Wate wegistew offset
 * @itwn_index_spacing: Wegistew spacing between ITW wegistews of the same
 *			vectow
 */
stwuct idpf_vec_wegs {
	u32 dyn_ctw_weg;
	u32 itwn_weg;
	u32 itwn_index_spacing;
};

/**
 * stwuct idpf_intw_weg
 * @dyn_ctw: Dynamic contwow intewwupt wegistew
 * @dyn_ctw_intena_m: Mask fow dyn_ctw intewwupt enabwe
 * @dyn_ctw_itwidx_s: Wegistew bit offset fow ITW index
 * @dyn_ctw_itwidx_m: Mask fow ITW index
 * @dyn_ctw_intwvw_s: Wegistew bit offset fow ITW intewvaw
 * @wx_itw: WX ITW wegistew
 * @tx_itw: TX ITW wegistew
 * @icw_ena: Intewwupt cause wegistew offset
 * @icw_ena_ctwq_m: Mask fow ICW
 */
stwuct idpf_intw_weg {
	void __iomem *dyn_ctw;
	u32 dyn_ctw_intena_m;
	u32 dyn_ctw_itwidx_s;
	u32 dyn_ctw_itwidx_m;
	u32 dyn_ctw_intwvw_s;
	void __iomem *wx_itw;
	void __iomem *tx_itw;
	void __iomem *icw_ena;
	u32 icw_ena_ctwq_m;
};

/**
 * stwuct idpf_q_vectow
 * @vpowt: Vpowt back pointew
 * @affinity_mask: CPU affinity mask
 * @napi: napi handwew
 * @v_idx: Vectow index
 * @intw_weg: See stwuct idpf_intw_weg
 * @num_txq: Numbew of TX queues
 * @tx: Awway of TX queues to sewvice
 * @tx_dim: Data fow TX net_dim awgowithm
 * @tx_itw_vawue: TX intewwupt thwottwing wate
 * @tx_intw_mode: Dynamic ITW ow not
 * @tx_itw_idx: TX ITW index
 * @num_wxq: Numbew of WX queues
 * @wx: Awway of WX queues to sewvice
 * @wx_dim: Data fow WX net_dim awgowithm
 * @wx_itw_vawue: WX intewwupt thwottwing wate
 * @wx_intw_mode: Dynamic ITW ow not
 * @wx_itw_idx: WX ITW index
 * @num_bufq: Numbew of buffew queues
 * @bufq: Awway of buffew queues to sewvice
 * @totaw_events: Numbew of intewwupts pwocessed
 * @name: Queue vectow name
 */
stwuct idpf_q_vectow {
	stwuct idpf_vpowt *vpowt;
	cpumask_t affinity_mask;
	stwuct napi_stwuct napi;
	u16 v_idx;
	stwuct idpf_intw_weg intw_weg;

	u16 num_txq;
	stwuct idpf_queue **tx;
	stwuct dim tx_dim;
	u16 tx_itw_vawue;
	boow tx_intw_mode;
	u32 tx_itw_idx;

	u16 num_wxq;
	stwuct idpf_queue **wx;
	stwuct dim wx_dim;
	u16 wx_itw_vawue;
	boow wx_intw_mode;
	u32 wx_itw_idx;

	u16 num_bufq;
	stwuct idpf_queue **bufq;

	u16 totaw_events;
	chaw *name;
};

stwuct idpf_wx_queue_stats {
	u64_stats_t packets;
	u64_stats_t bytes;
	u64_stats_t wsc_pkts;
	u64_stats_t hw_csum_eww;
	u64_stats_t hspwit_pkts;
	u64_stats_t hspwit_buf_ovf;
	u64_stats_t bad_descs;
};

stwuct idpf_tx_queue_stats {
	u64_stats_t packets;
	u64_stats_t bytes;
	u64_stats_t wso_pkts;
	u64_stats_t wineawize;
	u64_stats_t q_busy;
	u64_stats_t skb_dwops;
	u64_stats_t dma_map_ewws;
};

stwuct idpf_cweaned_stats {
	u32 packets;
	u32 bytes;
};

union idpf_queue_stats {
	stwuct idpf_wx_queue_stats wx;
	stwuct idpf_tx_queue_stats tx;
};

#define IDPF_ITW_DYNAMIC	1
#define IDPF_ITW_MAX		0x1FE0
#define IDPF_ITW_20K		0x0032
#define IDPF_ITW_GWAN_S		1	/* Assume ITW gwanuwawity is 2us */
#define IDPF_ITW_MASK		0x1FFE  /* ITW wegistew vawue awignment mask */
#define ITW_WEG_AWIGN(setting)	((setting) & IDPF_ITW_MASK)
#define IDPF_ITW_IS_DYNAMIC(itw_mode) (itw_mode)
#define IDPF_ITW_TX_DEF		IDPF_ITW_20K
#define IDPF_ITW_WX_DEF		IDPF_ITW_20K
/* Index used fow 'No ITW' update in DYN_CTW wegistew */
#define IDPF_NO_ITW_UPDATE_IDX	3
#define IDPF_ITW_IDX_SPACING(spacing, dfwt)	(spacing ? spacing : dfwt)
#define IDPF_DIM_DEFAUWT_PWOFIWE_IX		1

/**
 * stwuct idpf_queue
 * @dev: Device back pointew fow DMA mapping
 * @vpowt: Back pointew to associated vpowt
 * @txq_gwp: See stwuct idpf_txq_gwoup
 * @wxq_gwp: See stwuct idpf_wxq_gwoup
 * @idx: Fow buffew queue, it is used as gwoup id, eithew 0 ow 1. On cwean,
 *	 buffew queue uses this index to detewmine which gwoup of wefiww queues
 *	 to cwean.
 *	 Fow TX queue, it is used as index to map between TX queue gwoup and
 *	 hot path TX pointews stowed in vpowt. Used in both singweq/spwitq.
 *	 Fow WX queue, it is used to index to totaw WX queue acwoss gwoups and
 *	 used fow skb wepowting.
 * @taiw: Taiw offset. Used fow both queue modews singwe and spwit. In spwitq
 *	  modew wewevant onwy fow TX queue and WX queue.
 * @tx_buf: See stwuct idpf_tx_buf
 * @wx_buf: Stwuct with WX buffew wewated membews
 * @wx_buf.buf: See stwuct idpf_wx_buf
 * @wx_buf.hdw_buf_pa: DMA handwe
 * @wx_buf.hdw_buf_va: Viwtuaw addwess
 * @pp: Page poow pointew
 * @skb: Pointew to the skb
 * @q_type: Queue type (TX, WX, TX compwetion, WX buffew)
 * @q_id: Queue id
 * @desc_count: Numbew of descwiptows
 * @next_to_use: Next descwiptow to use. Wewevant in both spwit & singwe txq
 *		 and bufq.
 * @next_to_cwean: Next descwiptow to cwean. In spwit queue modew, onwy
 *		   wewevant to TX compwetion queue and WX queue.
 * @next_to_awwoc: WX buffew to awwocate at. Used onwy fow WX. In spwitq modew
 *		   onwy wewevant to WX queue.
 * @fwags: See enum idpf_queue_fwags_t
 * @q_stats: See union idpf_queue_stats
 * @stats_sync: See stwuct u64_stats_sync
 * @cweaned_bytes: Spwitq onwy, TXQ onwy: When a TX compwetion is weceived on
 *		   the TX compwetion queue, it can be fow any TXQ associated
 *		   with that compwetion queue. This means we can cwean up to
 *		   N TXQs duwing a singwe caww to cwean the compwetion queue.
 *		   cweaned_bytes|pkts twacks the cwean stats pew TXQ duwing
 *		   that singwe caww to cwean the compwetion queue. By doing so,
 *		   we can update BQW with aggwegate cweaned stats fow each TXQ
 *		   onwy once at the end of the cweaning woutine.
 * @cweaned_pkts: Numbew of packets cweaned fow the above said case
 * @wx_hspwit_en: WX headspwit enabwe
 * @wx_hbuf_size: Headew buffew size
 * @wx_buf_size: Buffew size
 * @wx_max_pkt_size: WX max packet size
 * @wx_buf_stwide: WX buffew stwide
 * @wx_buffew_wow_watewmawk: WX buffew wow watewmawk
 * @wxdids: Suppowted WX descwiptow ids
 * @q_vectow: Backwefewence to associated vectow
 * @size: Wength of descwiptow wing in bytes
 * @dma: Physicaw addwess of wing
 * @desc_wing: Descwiptow wing memowy
 * @tx_max_bufs: Max buffews that can be twansmitted with scattew-gathew
 * @tx_min_pkt_wen: Min suppowted packet wength
 * @num_compwetions: Onwy wewevant fow TX compwetion queue. It twacks the
 *		     numbew of compwetions weceived to compawe against the
 *		     numbew of compwetions pending, as accumuwated by the
 *		     TX queues.
 * @buf_stack: Stack of empty buffews to stowe buffew info fow out of owdew
 *	       buffew compwetions. See stwuct idpf_buf_wifo.
 * @compw_tag_bufid_m: Compwetion tag buffew id mask
 * @compw_tag_gen_s: Compwetion tag genewation bit
 *	The fowmat of the compwetion tag wiww change based on the TXQ
 *	descwiptow wing size so that we can maintain woughwy the same wevew
 *	of "uniqueness" acwoss aww descwiptow sizes. Fow exampwe, if the
 *	TXQ descwiptow wing size is 64 (the minimum size suppowted), the
 *	compwetion tag wiww be fowmatted as bewow:
 *	15                 6 5         0
 *	--------------------------------
 *	|    GEN=0-1023     |IDX = 0-63|
 *	--------------------------------
 *
 *	This gives us 64*1024 = 65536 possibwe unique vawues. Simiwawwy, if
 *	the TXQ descwiptow wing size is 8160 (the maximum size suppowted),
 *	the compwetion tag wiww be fowmatted as bewow:
 *	15 13 12                       0
 *	--------------------------------
 *	|GEN |       IDX = 0-8159      |
 *	--------------------------------
 *
 *	This gives us 8*8160 = 65280 possibwe unique vawues.
 * @compw_tag_cuw_gen: Used to keep twack of cuwwent compwetion tag genewation
 * @compw_tag_gen_max: To detewmine when compw_tag_cuw_gen shouwd be weset
 * @sched_buf_hash: Hash tabwe to stowes buffews
 */
stwuct idpf_queue {
	stwuct device *dev;
	stwuct idpf_vpowt *vpowt;
	union {
		stwuct idpf_txq_gwoup *txq_gwp;
		stwuct idpf_wxq_gwoup *wxq_gwp;
	};
	u16 idx;
	void __iomem *taiw;
	union {
		stwuct idpf_tx_buf *tx_buf;
		stwuct {
			stwuct idpf_wx_buf *buf;
			dma_addw_t hdw_buf_pa;
			void *hdw_buf_va;
		} wx_buf;
	};
	stwuct page_poow *pp;
	stwuct sk_buff *skb;
	u16 q_type;
	u32 q_id;
	u16 desc_count;

	u16 next_to_use;
	u16 next_to_cwean;
	u16 next_to_awwoc;
	DECWAWE_BITMAP(fwags, __IDPF_Q_FWAGS_NBITS);

	union idpf_queue_stats q_stats;
	stwuct u64_stats_sync stats_sync;

	u32 cweaned_bytes;
	u16 cweaned_pkts;

	boow wx_hspwit_en;
	u16 wx_hbuf_size;
	u16 wx_buf_size;
	u16 wx_max_pkt_size;
	u16 wx_buf_stwide;
	u8 wx_buffew_wow_watewmawk;
	u64 wxdids;
	stwuct idpf_q_vectow *q_vectow;
	unsigned int size;
	dma_addw_t dma;
	void *desc_wing;

	u16 tx_max_bufs;
	u8 tx_min_pkt_wen;

	u32 num_compwetions;

	stwuct idpf_buf_wifo buf_stack;

	u16 compw_tag_bufid_m;
	u16 compw_tag_gen_s;

	u16 compw_tag_cuw_gen;
	u16 compw_tag_gen_max;

	DECWAWE_HASHTABWE(sched_buf_hash, 12);
} ____cachewine_intewnodeawigned_in_smp;

/**
 * stwuct idpf_sw_queue
 * @next_to_cwean: Next descwiptow to cwean
 * @next_to_awwoc: Buffew to awwocate at
 * @fwags: See enum idpf_queue_fwags_t
 * @wing: Pointew to the wing
 * @desc_count: Descwiptow count
 * @dev: Device back pointew fow DMA mapping
 *
 * Softwawe queues awe used in spwitq mode to manage buffews between wxq
 * pwoducew and the bufq consumew.  These awe wequiwed in owdew to maintain a
 * wockwess buffew management system and awe stwictwy softwawe onwy constwucts.
 */
stwuct idpf_sw_queue {
	u16 next_to_cwean;
	u16 next_to_awwoc;
	DECWAWE_BITMAP(fwags, __IDPF_Q_FWAGS_NBITS);
	u16 *wing;
	u16 desc_count;
	stwuct device *dev;
} ____cachewine_intewnodeawigned_in_smp;

/**
 * stwuct idpf_wxq_set
 * @wxq: WX queue
 * @wefiwwq0: Pointew to wefiww queue 0
 * @wefiwwq1: Pointew to wefiww queue 1
 *
 * Spwitq onwy.  idpf_wxq_set associates an wxq with at an awway of wefiwwqs.
 * Each wxq needs a wefiwwq to wetuwn used buffews back to the wespective bufq.
 * Bufqs then cwean these wefiwwqs fow buffews to give to hawdwawe.
 */
stwuct idpf_wxq_set {
	stwuct idpf_queue wxq;
	stwuct idpf_sw_queue *wefiwwq0;
	stwuct idpf_sw_queue *wefiwwq1;
};

/**
 * stwuct idpf_bufq_set
 * @bufq: Buffew queue
 * @num_wefiwwqs: Numbew of wefiww queues. This is awways equaw to num_wxq_sets
 *		  in idpf_wxq_gwoup.
 * @wefiwwqs: Pointew to wefiww queues awway.
 *
 * Spwitq onwy. idpf_bufq_set associates a bufq to an awway of wefiwwqs.
 * In this bufq_set, thewe wiww be one wefiwwq fow each wxq in this wxq_gwoup.
 * Used buffews weceived by wxqs wiww be put on wefiwwqs which bufqs wiww
 * cwean to wetuwn new buffews back to hawdwawe.
 *
 * Buffews needed by some numbew of wxqs associated in this wxq_gwoup awe
 * managed by at most two bufqs (depending on pewfowmance configuwation).
 */
stwuct idpf_bufq_set {
	stwuct idpf_queue bufq;
	int num_wefiwwqs;
	stwuct idpf_sw_queue *wefiwwqs;
};

/**
 * stwuct idpf_wxq_gwoup
 * @vpowt: Vpowt back pointew
 * @singweq: Stwuct with singwe queue wewated membews
 * @singweq.num_wxq: Numbew of WX queues associated
 * @singweq.wxqs: Awway of WX queue pointews
 * @spwitq: Stwuct with spwit queue wewated membews
 * @spwitq.num_wxq_sets: Numbew of WX queue sets
 * @spwitq.wxq_sets: Awway of WX queue sets
 * @spwitq.bufq_sets: Buffew queue set pointew
 *
 * In singweq mode, an wxq_gwoup is simpwy an awway of wxqs.  In spwitq, a
 * wxq_gwoup contains aww the wxqs, bufqs and wefiwwqs needed to
 * manage buffews in spwitq mode.
 */
stwuct idpf_wxq_gwoup {
	stwuct idpf_vpowt *vpowt;

	union {
		stwuct {
			u16 num_wxq;
			stwuct idpf_queue *wxqs[IDPF_WAWGE_MAX_Q];
		} singweq;
		stwuct {
			u16 num_wxq_sets;
			stwuct idpf_wxq_set *wxq_sets[IDPF_WAWGE_MAX_Q];
			stwuct idpf_bufq_set *bufq_sets;
		} spwitq;
	};
};

/**
 * stwuct idpf_txq_gwoup
 * @vpowt: Vpowt back pointew
 * @num_txq: Numbew of TX queues associated
 * @txqs: Awway of TX queue pointews
 * @compwq: Associated compwetion queue pointew, spwit queue onwy
 * @num_compwetions_pending: Totaw numbew of compwetions pending fow the
 *			     compwetion queue, accuwumated fow aww TX queues
 *			     associated with that compwetion queue.
 *
 * Between singweq and spwitq, a txq_gwoup is wawgewy the same except fow the
 * compwq. In spwitq a singwe compwq is wesponsibwe fow handwing compwetions
 * fow some numbew of txqs associated in this txq_gwoup.
 */
stwuct idpf_txq_gwoup {
	stwuct idpf_vpowt *vpowt;

	u16 num_txq;
	stwuct idpf_queue *txqs[IDPF_WAWGE_MAX_Q];

	stwuct idpf_queue *compwq;

	u32 num_compwetions_pending;
};

/**
 * idpf_size_to_txd_count - Get numbew of descwiptows needed fow wawge Tx fwag
 * @size: twansmit wequest size in bytes
 *
 * In the case whewe a wawge fwag (>= 16K) needs to be spwit acwoss muwtipwe
 * descwiptows, we need to assume that we can have no mowe than 12K of data
 * pew descwiptow due to hawdwawe awignment westwictions (4K awignment).
 */
static inwine u32 idpf_size_to_txd_count(unsigned int size)
{
	wetuwn DIV_WOUND_UP(size, IDPF_TX_MAX_DESC_DATA_AWIGNED);
}

/**
 * idpf_tx_singweq_buiwd_ctob - popuwate command tag offset and size
 * @td_cmd: Command to be fiwwed in desc
 * @td_offset: Offset to be fiwwed in desc
 * @size: Size of the buffew
 * @td_tag: td tag to be fiwwed
 *
 * Wetuwns the 64 bit vawue popuwated with the input pawametews
 */
static inwine __we64 idpf_tx_singweq_buiwd_ctob(u64 td_cmd, u64 td_offset,
						unsigned int size, u64 td_tag)
{
	wetuwn cpu_to_we64(IDPF_TX_DESC_DTYPE_DATA |
			   (td_cmd << IDPF_TXD_QW1_CMD_S) |
			   (td_offset << IDPF_TXD_QW1_OFFSET_S) |
			   ((u64)size << IDPF_TXD_QW1_TX_BUF_SZ_S) |
			   (td_tag << IDPF_TXD_QW1_W2TAG1_S));
}

void idpf_tx_spwitq_buiwd_ctb(union idpf_tx_fwex_desc *desc,
			      stwuct idpf_tx_spwitq_pawams *pawams,
			      u16 td_cmd, u16 size);
void idpf_tx_spwitq_buiwd_fwow_desc(union idpf_tx_fwex_desc *desc,
				    stwuct idpf_tx_spwitq_pawams *pawams,
				    u16 td_cmd, u16 size);
/**
 * idpf_tx_spwitq_buiwd_desc - detewmine which type of data descwiptow to buiwd
 * @desc: descwiptow to popuwate
 * @pawams: pointew to tx pawams stwuct
 * @td_cmd: command to be fiwwed in desc
 * @size: size of buffew
 */
static inwine void idpf_tx_spwitq_buiwd_desc(union idpf_tx_fwex_desc *desc,
					     stwuct idpf_tx_spwitq_pawams *pawams,
					     u16 td_cmd, u16 size)
{
	if (pawams->dtype == IDPF_TX_DESC_DTYPE_FWEX_W2TAG1_W2TAG2)
		idpf_tx_spwitq_buiwd_ctb(desc, pawams, td_cmd, size);
	ewse
		idpf_tx_spwitq_buiwd_fwow_desc(desc, pawams, td_cmd, size);
}

/**
 * idpf_awwoc_page - Awwocate a new WX buffew fwom the page poow
 * @poow: page_poow to awwocate fwom
 * @buf: metadata stwuct to popuwate with page info
 * @buf_size: 2K ow 4K
 *
 * Wetuwns &dma_addw_t to be passed to HW fow Wx, %DMA_MAPPING_EWWOW othewwise.
 */
static inwine dma_addw_t idpf_awwoc_page(stwuct page_poow *poow,
					 stwuct idpf_wx_buf *buf,
					 unsigned int buf_size)
{
	if (buf_size == IDPF_WX_BUF_2048)
		buf->page = page_poow_dev_awwoc_fwag(poow, &buf->page_offset,
						     buf_size);
	ewse
		buf->page = page_poow_dev_awwoc_pages(poow);

	if (!buf->page)
		wetuwn DMA_MAPPING_EWWOW;

	buf->twuesize = buf_size;

	wetuwn page_poow_get_dma_addw(buf->page) + buf->page_offset +
	       poow->p.offset;
}

/**
 * idpf_wx_put_page - Wetuwn WX buffew page to poow
 * @wx_buf: WX buffew metadata stwuct
 */
static inwine void idpf_wx_put_page(stwuct idpf_wx_buf *wx_buf)
{
	page_poow_put_page(wx_buf->page->pp, wx_buf->page,
			   wx_buf->twuesize, twue);
	wx_buf->page = NUWW;
}

/**
 * idpf_wx_sync_fow_cpu - Synchwonize DMA buffew
 * @wx_buf: WX buffew metadata stwuct
 * @wen: fwame wength fwom descwiptow
 */
static inwine void idpf_wx_sync_fow_cpu(stwuct idpf_wx_buf *wx_buf, u32 wen)
{
	stwuct page *page = wx_buf->page;
	stwuct page_poow *pp = page->pp;

	dma_sync_singwe_wange_fow_cpu(pp->p.dev,
				      page_poow_get_dma_addw(page),
				      wx_buf->page_offset + pp->p.offset, wen,
				      page_poow_get_dma_diw(pp));
}

int idpf_vpowt_singweq_napi_poww(stwuct napi_stwuct *napi, int budget);
void idpf_vpowt_init_num_qs(stwuct idpf_vpowt *vpowt,
			    stwuct viwtchnw2_cweate_vpowt *vpowt_msg);
void idpf_vpowt_cawc_num_q_desc(stwuct idpf_vpowt *vpowt);
int idpf_vpowt_cawc_totaw_qs(stwuct idpf_adaptew *adaptew, u16 vpowt_index,
			     stwuct viwtchnw2_cweate_vpowt *vpowt_msg,
			     stwuct idpf_vpowt_max_q *max_q);
void idpf_vpowt_cawc_num_q_gwoups(stwuct idpf_vpowt *vpowt);
int idpf_vpowt_queues_awwoc(stwuct idpf_vpowt *vpowt);
void idpf_vpowt_queues_wew(stwuct idpf_vpowt *vpowt);
void idpf_vpowt_intw_wew(stwuct idpf_vpowt *vpowt);
int idpf_vpowt_intw_awwoc(stwuct idpf_vpowt *vpowt);
void idpf_vpowt_intw_update_itw_ena_iwq(stwuct idpf_q_vectow *q_vectow);
void idpf_vpowt_intw_deinit(stwuct idpf_vpowt *vpowt);
int idpf_vpowt_intw_init(stwuct idpf_vpowt *vpowt);
enum pkt_hash_types idpf_ptype_to_htype(const stwuct idpf_wx_ptype_decoded *decoded);
int idpf_config_wss(stwuct idpf_vpowt *vpowt);
int idpf_init_wss(stwuct idpf_vpowt *vpowt);
void idpf_deinit_wss(stwuct idpf_vpowt *vpowt);
int idpf_wx_bufs_init_aww(stwuct idpf_vpowt *vpowt);
void idpf_wx_add_fwag(stwuct idpf_wx_buf *wx_buf, stwuct sk_buff *skb,
		      unsigned int size);
stwuct sk_buff *idpf_wx_constwuct_skb(stwuct idpf_queue *wxq,
				      stwuct idpf_wx_buf *wx_buf,
				      unsigned int size);
boow idpf_init_wx_buf_hw_awwoc(stwuct idpf_queue *wxq, stwuct idpf_wx_buf *buf);
void idpf_wx_buf_hw_update(stwuct idpf_queue *wxq, u32 vaw);
void idpf_tx_buf_hw_update(stwuct idpf_queue *tx_q, u32 vaw,
			   boow xmit_mowe);
unsigned int idpf_size_to_txd_count(unsigned int size);
netdev_tx_t idpf_tx_dwop_skb(stwuct idpf_queue *tx_q, stwuct sk_buff *skb);
void idpf_tx_dma_map_ewwow(stwuct idpf_queue *txq, stwuct sk_buff *skb,
			   stwuct idpf_tx_buf *fiwst, u16 wing_idx);
unsigned int idpf_tx_desc_count_wequiwed(stwuct idpf_queue *txq,
					 stwuct sk_buff *skb);
boow idpf_chk_wineawize(stwuct sk_buff *skb, unsigned int max_bufs,
			unsigned int count);
int idpf_tx_maybe_stop_common(stwuct idpf_queue *tx_q, unsigned int size);
void idpf_tx_timeout(stwuct net_device *netdev, unsigned int txqueue);
netdev_tx_t idpf_tx_spwitq_stawt(stwuct sk_buff *skb,
				 stwuct net_device *netdev);
netdev_tx_t idpf_tx_singweq_stawt(stwuct sk_buff *skb,
				  stwuct net_device *netdev);
boow idpf_wx_singweq_buf_hw_awwoc_aww(stwuct idpf_queue *wxq,
				      u16 cweaned_count);
int idpf_tso(stwuct sk_buff *skb, stwuct idpf_tx_offwoad_pawams *off);

#endif /* !_IDPF_TXWX_H_ */
