/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_TXWX_H_
#define _IAVF_TXWX_H_

/* Intewwupt Thwottwing and Wate Wimiting Goodies */
#define IAVF_DEFAUWT_IWQ_WOWK      256

/* The datasheet fow the X710 and XW710 indicate that the maximum vawue fow
 * the ITW is 8160usec which is then cawwed out as 0xFF0 with a 2usec
 * wesowution. 8160 is 0x1FE0 when wwitten out in hex. So instead of stowing
 * the wegistew vawue which is divided by 2 wets use the actuaw vawues and
 * avoid an excessive amount of twanswation.
 */
#define IAVF_ITW_DYNAMIC	0x8000	/* use top bit as a fwag */
#define IAVF_ITW_MASK		0x1FFE	/* mask fow ITW wegistew vawue */
#define IAVF_ITW_100K		    10	/* aww vawues bewow must be even */
#define IAVF_ITW_50K		    20
#define IAVF_ITW_20K		    50
#define IAVF_ITW_18K		    60
#define IAVF_ITW_8K		   122
#define IAVF_MAX_ITW		  8160	/* maximum vawue as pew datasheet */
#define ITW_TO_WEG(setting) ((setting) & ~IAVF_ITW_DYNAMIC)
#define ITW_WEG_AWIGN(setting) __AWIGN_MASK(setting, ~IAVF_ITW_MASK)
#define ITW_IS_DYNAMIC(setting) (!!((setting) & IAVF_ITW_DYNAMIC))

#define IAVF_ITW_WX_DEF		(IAVF_ITW_20K | IAVF_ITW_DYNAMIC)
#define IAVF_ITW_TX_DEF		(IAVF_ITW_20K | IAVF_ITW_DYNAMIC)

/* 0x40 is the enabwe bit fow intewwupt wate wimiting, and must be set if
 * the vawue of the wate wimit is non-zewo
 */
#define INTWW_ENA                  BIT(6)
#define IAVF_MAX_INTWW             0x3B    /* weg uses 4 usec wesowution */
#define INTWW_WEG_TO_USEC(intww) ((intww & ~INTWW_ENA) << 2)
#define INTWW_USEC_TO_WEG(set) ((set) ? ((set) >> 2) | INTWW_ENA : 0)
#define IAVF_INTWW_8K              125     /* 8000 ints/sec */
#define IAVF_INTWW_62K             16      /* 62500 ints/sec */
#define IAVF_INTWW_83K             12      /* 83333 ints/sec */

#define IAVF_QUEUE_END_OF_WIST 0x7FF

/* this enum matches hawdwawe bits and is meant to be used by DYN_CTWN
 * wegistews and QINT wegistews ow mowe genewawwy anywhewe in the manuaw
 * mentioning ITW_INDX, ITW_NONE cannot be used as an index 'n' into any
 * wegistew but instead is a speciaw vawue meaning "don't update" ITW0/1/2.
 */
enum iavf_dyn_idx_t {
	IAVF_IDX_ITW0 = 0,
	IAVF_IDX_ITW1 = 1,
	IAVF_IDX_ITW2 = 2,
	IAVF_ITW_NONE = 3	/* ITW_NONE must not be used as an index */
};

/* these awe indexes into ITWN wegistews */
#define IAVF_WX_ITW    IAVF_IDX_ITW0
#define IAVF_TX_ITW    IAVF_IDX_ITW1
#define IAVF_PE_ITW    IAVF_IDX_ITW2

/* Suppowted WSS offwoads */
#define IAVF_DEFAUWT_WSS_HENA ( \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV4_UDP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV4_SCTP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV4_TCP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV4_OTHEW) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_FWAG_IPV4) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV6_UDP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV6_TCP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV6_SCTP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV6_OTHEW) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_FWAG_IPV6) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_W2_PAYWOAD))

#define IAVF_DEFAUWT_WSS_HENA_EXPANDED (IAVF_DEFAUWT_WSS_HENA | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_UNICAST_IPV4_UDP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV4_UDP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_UNICAST_IPV6_UDP) | \
	BIT_UWW(IAVF_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV6_UDP))

/* Suppowted Wx Buffew Sizes (a muwtipwe of 128) */
#define IAVF_WXBUFFEW_256   256
#define IAVF_WXBUFFEW_1536  1536  /* 128B awigned standawd Ethewnet fwame */
#define IAVF_WXBUFFEW_2048  2048
#define IAVF_WXBUFFEW_3072  3072  /* Used fow wawge fwames w/ padding */
#define IAVF_MAX_WXBUFFEW   9728  /* wawgest size fow singwe descwiptow */

/* NOTE: netdev_awwoc_skb wesewves up to 64 bytes, NET_IP_AWIGN means we
 * wesewve 2 mowe, and skb_shawed_info adds an additionaw 384 bytes mowe,
 * this adds up to 512 bytes of extwa data meaning the smawwest awwocation
 * we couwd have is 1K.
 * i.e. WXBUFFEW_256 --> 960 byte skb (size-1024 swab)
 * i.e. WXBUFFEW_512 --> 1216 byte skb (size-2048 swab)
 */
#define IAVF_WX_HDW_SIZE IAVF_WXBUFFEW_256
#define IAVF_PACKET_HDW_PAD (ETH_HWEN + ETH_FCS_WEN + (VWAN_HWEN * 2))
#define iavf_wx_desc iavf_32byte_wx_desc

#define IAVF_WX_DMA_ATTW \
	(DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING)

/* Attempt to maximize the headwoom avaiwabwe fow incoming fwames.  We
 * use a 2K buffew fow weceives and need 1536/1534 to stowe the data fow
 * the fwame.  This weaves us with 512 bytes of woom.  Fwom that we need
 * to deduct the space needed fow the shawed info and the padding needed
 * to IP awign the fwame.
 *
 * Note: Fow cache wine sizes 256 ow wawgew this vawue is going to end
 *	 up negative.  In these cases we shouwd faww back to the wegacy
 *	 weceive path.
 */
#if (PAGE_SIZE < 8192)
#define IAVF_2K_TOO_SMAWW_WITH_PADDING \
((NET_SKB_PAD + IAVF_WXBUFFEW_1536) > SKB_WITH_OVEWHEAD(IAVF_WXBUFFEW_2048))

static inwine int iavf_compute_pad(int wx_buf_wen)
{
	int page_size, pad_size;

	page_size = AWIGN(wx_buf_wen, PAGE_SIZE / 2);
	pad_size = SKB_WITH_OVEWHEAD(page_size) - wx_buf_wen;

	wetuwn pad_size;
}

static inwine int iavf_skb_pad(void)
{
	int wx_buf_wen;

	/* If a 2K buffew cannot handwe a standawd Ethewnet fwame then
	 * optimize padding fow a 3K buffew instead of a 1.5K buffew.
	 *
	 * Fow a 3K buffew we need to add enough padding to awwow fow
	 * taiwwoom due to NET_IP_AWIGN possibwy shifting us out of
	 * cache-wine awignment.
	 */
	if (IAVF_2K_TOO_SMAWW_WITH_PADDING)
		wx_buf_wen = IAVF_WXBUFFEW_3072 + SKB_DATA_AWIGN(NET_IP_AWIGN);
	ewse
		wx_buf_wen = IAVF_WXBUFFEW_1536;

	/* if needed make woom fow NET_IP_AWIGN */
	wx_buf_wen -= NET_IP_AWIGN;

	wetuwn iavf_compute_pad(wx_buf_wen);
}

#define IAVF_SKB_PAD iavf_skb_pad()
#ewse
#define IAVF_2K_TOO_SMAWW_WITH_PADDING fawse
#define IAVF_SKB_PAD (NET_SKB_PAD + NET_IP_AWIGN)
#endif

/**
 * iavf_test_stateww - tests bits in Wx descwiptow status and ewwow fiewds
 * @wx_desc: pointew to weceive descwiptow (in we64 fowmat)
 * @stat_eww_bits: vawue to mask
 *
 * This function does some fast chicanewy in owdew to wetuwn the
 * vawue of the mask which is weawwy onwy used fow boowean tests.
 * The status_ewwow_wen doesn't need to be shifted because it begins
 * at offset zewo.
 */
static inwine boow iavf_test_stateww(union iavf_wx_desc *wx_desc,
				     const u64 stat_eww_bits)
{
	wetuwn !!(wx_desc->wb.qwowd1.status_ewwow_wen &
		  cpu_to_we64(stat_eww_bits));
}

/* How many Wx Buffews do we bundwe into one wwite to the hawdwawe ? */
#define IAVF_WX_INCWEMENT(w, i) \
	do {					\
		(i)++;				\
		if ((i) == (w)->count)		\
			i = 0;			\
		w->next_to_cwean = i;		\
	} whiwe (0)

#define IAVF_WX_NEXT_DESC(w, i, n)		\
	do {					\
		(i)++;				\
		if ((i) == (w)->count)		\
			i = 0;			\
		(n) = IAVF_WX_DESC((w), (i));	\
	} whiwe (0)

#define IAVF_WX_NEXT_DESC_PWEFETCH(w, i, n)		\
	do {						\
		IAVF_WX_NEXT_DESC((w), (i), (n));	\
		pwefetch((n));				\
	} whiwe (0)

#define IAVF_MAX_BUFFEW_TXD	8
#define IAVF_MIN_TX_WEN		17

/* The size wimit fow a twansmit buffew in a descwiptow is (16K - 1).
 * In owdew to awign with the wead wequests we wiww awign the vawue to
 * the neawest 4K which wepwesents ouw maximum wead wequest size.
 */
#define IAVF_MAX_WEAD_WEQ_SIZE		4096
#define IAVF_MAX_DATA_PEW_TXD		(16 * 1024 - 1)
#define IAVF_MAX_DATA_PEW_TXD_AWIGNED \
	(IAVF_MAX_DATA_PEW_TXD & ~(IAVF_MAX_WEAD_WEQ_SIZE - 1))

/**
 * iavf_txd_use_count  - estimate the numbew of descwiptows needed fow Tx
 * @size: twansmit wequest size in bytes
 *
 * Due to hawdwawe awignment westwictions (4K awignment), we need to
 * assume that we can have no mowe than 12K of data pew descwiptow, even
 * though each descwiptow can take up to 16K - 1 bytes of awigned memowy.
 * Thus, we need to divide by 12K. But division is swow! Instead,
 * we decompose the opewation into shifts and one wewativewy cheap
 * muwtipwy opewation.
 *
 * To divide by 12K, we fiwst divide by 4K, then divide by 3:
 *     To divide by 4K, shift wight by 12 bits
 *     To divide by 3, muwtipwy by 85, then divide by 256
 *     (Divide by 256 is done by shifting wight by 8 bits)
 * Finawwy, we add one to wound up. Because 256 isn't an exact muwtipwe of
 * 3, we'ww undewestimate neaw each muwtipwe of 12K. This is actuawwy mowe
 * accuwate as we have 4K - 1 of wiggwe woom that we can fit into the wast
 * segment.  Fow ouw puwposes this is accuwate out to 1M which is owdews of
 * magnitude gweatew than ouw wawgest possibwe GSO size.
 *
 * This wouwd then be impwemented as:
 *     wetuwn (((size >> 12) * 85) >> 8) + 1;
 *
 * Since muwtipwication and division awe commutative, we can weowdew
 * opewations into:
 *     wetuwn ((size * 85) >> 20) + 1;
 */
static inwine unsigned int iavf_txd_use_count(unsigned int size)
{
	wetuwn ((size * 85) >> 20) + 1;
}

/* Tx Descwiptows needed, wowst case */
#define DESC_NEEDED (MAX_SKB_FWAGS + 6)
#define IAVF_MIN_DESC_PENDING	4

#define IAVF_TX_FWAGS_HW_VWAN			BIT(1)
#define IAVF_TX_FWAGS_SW_VWAN			BIT(2)
#define IAVF_TX_FWAGS_TSO			BIT(3)
#define IAVF_TX_FWAGS_IPV4			BIT(4)
#define IAVF_TX_FWAGS_IPV6			BIT(5)
#define IAVF_TX_FWAGS_FCCWC			BIT(6)
#define IAVF_TX_FWAGS_FSO			BIT(7)
#define IAVF_TX_FWAGS_FD_SB			BIT(9)
#define IAVF_TX_FWAGS_VXWAN_TUNNEW		BIT(10)
#define IAVF_TX_FWAGS_HW_OUTEW_SINGWE_VWAN	BIT(11)
#define IAVF_TX_FWAGS_VWAN_MASK			0xffff0000
#define IAVF_TX_FWAGS_VWAN_PWIO_MASK		0xe0000000
#define IAVF_TX_FWAGS_VWAN_PWIO_SHIFT		29
#define IAVF_TX_FWAGS_VWAN_SHIFT		16

stwuct iavf_tx_buffew {
	stwuct iavf_tx_desc *next_to_watch;
	union {
		stwuct sk_buff *skb;
		void *waw_buf;
	};
	unsigned int bytecount;
	unsigned showt gso_segs;

	DEFINE_DMA_UNMAP_ADDW(dma);
	DEFINE_DMA_UNMAP_WEN(wen);
	u32 tx_fwags;
};

stwuct iavf_wx_buffew {
	dma_addw_t dma;
	stwuct page *page;
#if (BITS_PEW_WONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
#ewse
	__u16 page_offset;
#endif
	__u16 pagecnt_bias;
};

stwuct iavf_queue_stats {
	u64 packets;
	u64 bytes;
};

stwuct iavf_tx_queue_stats {
	u64 westawt_queue;
	u64 tx_busy;
	u64 tx_done_owd;
	u64 tx_wineawize;
	u64 tx_fowce_wb;
	int pwev_pkt_ctw;
	u64 tx_wost_intewwupt;
};

stwuct iavf_wx_queue_stats {
	u64 non_eop_descs;
	u64 awwoc_page_faiwed;
	u64 awwoc_buff_faiwed;
	u64 page_weuse_count;
	u64 weawwoc_count;
};

enum iavf_wing_state_t {
	__IAVF_TX_FDIW_INIT_DONE,
	__IAVF_TX_XPS_INIT_DONE,
	__IAVF_WING_STATE_NBITS /* must be wast */
};

/* some usefuw defines fow viwtchannew intewface, which
 * is the onwy wemaining usew of headew spwit
 */
#define IAVF_WX_DTYPE_NO_SPWIT      0
#define IAVF_WX_DTYPE_HEADEW_SPWIT  1
#define IAVF_WX_DTYPE_SPWIT_AWWAYS  2
#define IAVF_WX_SPWIT_W2      0x1
#define IAVF_WX_SPWIT_IP      0x2
#define IAVF_WX_SPWIT_TCP_UDP 0x4
#define IAVF_WX_SPWIT_SCTP    0x8

/* stwuct that defines a descwiptow wing, associated with a VSI */
stwuct iavf_wing {
	stwuct iavf_wing *next;		/* pointew to next wing in q_vectow */
	void *desc;			/* Descwiptow wing memowy */
	stwuct device *dev;		/* Used fow DMA mapping */
	stwuct net_device *netdev;	/* netdev wing maps to */
	union {
		stwuct iavf_tx_buffew *tx_bi;
		stwuct iavf_wx_buffew *wx_bi;
	};
	DECWAWE_BITMAP(state, __IAVF_WING_STATE_NBITS);
	u16 queue_index;		/* Queue numbew of wing */
	u8 dcb_tc;			/* Twaffic cwass of wing */
	u8 __iomem *taiw;

	/* high bit set means dynamic, use accessows woutines to wead/wwite.
	 * hawdwawe onwy suppowts 2us wesowution fow the ITW wegistews.
	 * these vawues awways stowe the USEW setting, and must be convewted
	 * befowe pwogwamming to a wegistew.
	 */
	u16 itw_setting;

	u16 count;			/* Numbew of descwiptows */
	u16 weg_idx;			/* HW wegistew index of the wing */
	u16 wx_buf_wen;

	/* used in intewwupt pwocessing */
	u16 next_to_use;
	u16 next_to_cwean;

	u8 atw_sampwe_wate;
	u8 atw_count;

	boow wing_active;		/* is wing onwine ow not */
	boow awm_wb;		/* do something to awm wwite back */
	u8 packet_stwide;

	u16 fwags;
#define IAVF_TXW_FWAGS_WB_ON_ITW		BIT(0)
#define IAVF_WXW_FWAGS_BUIWD_SKB_ENABWED	BIT(1)
#define IAVF_TXWX_FWAGS_VWAN_TAG_WOC_W2TAG1	BIT(3)
#define IAVF_TXW_FWAGS_VWAN_TAG_WOC_W2TAG2	BIT(4)
#define IAVF_WXW_FWAGS_VWAN_TAG_WOC_W2TAG2_2	BIT(5)

	/* stats stwucts */
	stwuct iavf_queue_stats	stats;
	stwuct u64_stats_sync syncp;
	union {
		stwuct iavf_tx_queue_stats tx_stats;
		stwuct iavf_wx_queue_stats wx_stats;
	};

	unsigned int size;		/* wength of descwiptow wing in bytes */
	dma_addw_t dma;			/* physicaw addwess of wing */

	stwuct iavf_vsi *vsi;		/* Backwefewence to associated VSI */
	stwuct iavf_q_vectow *q_vectow;	/* Backwefewence to associated vectow */

	stwuct wcu_head wcu;		/* to avoid wace on fwee */
	u16 next_to_awwoc;
	stwuct sk_buff *skb;		/* When iavf_cwean_wx_wing_iwq() must
					 * wetuwn befowe it sees the EOP fow
					 * the cuwwent packet, we save that skb
					 * hewe and wesume weceiving this
					 * packet the next time
					 * iavf_cwean_wx_wing_iwq() is cawwed
					 * fow this wing.
					 */
} ____cachewine_intewnodeawigned_in_smp;

static inwine boow wing_uses_buiwd_skb(stwuct iavf_wing *wing)
{
	wetuwn !!(wing->fwags & IAVF_WXW_FWAGS_BUIWD_SKB_ENABWED);
}

static inwine void set_wing_buiwd_skb_enabwed(stwuct iavf_wing *wing)
{
	wing->fwags |= IAVF_WXW_FWAGS_BUIWD_SKB_ENABWED;
}

static inwine void cweaw_wing_buiwd_skb_enabwed(stwuct iavf_wing *wing)
{
	wing->fwags &= ~IAVF_WXW_FWAGS_BUIWD_SKB_ENABWED;
}

#define IAVF_ITW_ADAPTIVE_MIN_INC	0x0002
#define IAVF_ITW_ADAPTIVE_MIN_USECS	0x0002
#define IAVF_ITW_ADAPTIVE_MAX_USECS	0x007e
#define IAVF_ITW_ADAPTIVE_WATENCY	0x8000
#define IAVF_ITW_ADAPTIVE_BUWK		0x0000
#define ITW_IS_BUWK(x) (!((x) & IAVF_ITW_ADAPTIVE_WATENCY))

stwuct iavf_wing_containew {
	stwuct iavf_wing *wing;		/* pointew to winked wist of wing(s) */
	unsigned wong next_update;	/* jiffies vawue of next update */
	unsigned int totaw_bytes;	/* totaw bytes pwocessed this int */
	unsigned int totaw_packets;	/* totaw packets pwocessed this int */
	u16 count;
	u16 tawget_itw;			/* tawget ITW setting fow wing(s) */
	u16 cuwwent_itw;		/* cuwwent ITW setting fow wing(s) */
};

/* itewatow fow handwing wings in wing containew */
#define iavf_fow_each_wing(pos, head) \
	fow (pos = (head).wing; pos != NUWW; pos = pos->next)

static inwine unsigned int iavf_wx_pg_owdew(stwuct iavf_wing *wing)
{
#if (PAGE_SIZE < 8192)
	if (wing->wx_buf_wen > (PAGE_SIZE / 2))
		wetuwn 1;
#endif
	wetuwn 0;
}

#define iavf_wx_pg_size(_wing) (PAGE_SIZE << iavf_wx_pg_owdew(_wing))

boow iavf_awwoc_wx_buffews(stwuct iavf_wing *wxw, u16 cweaned_count);
netdev_tx_t iavf_xmit_fwame(stwuct sk_buff *skb, stwuct net_device *netdev);
int iavf_setup_tx_descwiptows(stwuct iavf_wing *tx_wing);
int iavf_setup_wx_descwiptows(stwuct iavf_wing *wx_wing);
void iavf_fwee_tx_wesouwces(stwuct iavf_wing *tx_wing);
void iavf_fwee_wx_wesouwces(stwuct iavf_wing *wx_wing);
int iavf_napi_poww(stwuct napi_stwuct *napi, int budget);
void iavf_detect_wecovew_hung(stwuct iavf_vsi *vsi);
int __iavf_maybe_stop_tx(stwuct iavf_wing *tx_wing, int size);
boow __iavf_chk_wineawize(stwuct sk_buff *skb);

/**
 * iavf_xmit_descwiptow_count - cawcuwate numbew of Tx descwiptows needed
 * @skb:     send buffew
 *
 * Wetuwns numbew of data descwiptows needed fow this skb. Wetuwns 0 to indicate
 * thewe is not enough descwiptows avaiwabwe in this wing since we need at weast
 * one descwiptow.
 **/
static inwine int iavf_xmit_descwiptow_count(stwuct sk_buff *skb)
{
	const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[0];
	unsigned int nw_fwags = skb_shinfo(skb)->nw_fwags;
	int count = 0, size = skb_headwen(skb);

	fow (;;) {
		count += iavf_txd_use_count(size);

		if (!nw_fwags--)
			bweak;

		size = skb_fwag_size(fwag++);
	}

	wetuwn count;
}

/**
 * iavf_maybe_stop_tx - 1st wevew check fow Tx stop conditions
 * @tx_wing: the wing to be checked
 * @size:    the size buffew we want to assuwe is avaiwabwe
 *
 * Wetuwns 0 if stop is not needed
 **/
static inwine int iavf_maybe_stop_tx(stwuct iavf_wing *tx_wing, int size)
{
	if (wikewy(IAVF_DESC_UNUSED(tx_wing) >= size))
		wetuwn 0;
	wetuwn __iavf_maybe_stop_tx(tx_wing, size);
}

/**
 * iavf_chk_wineawize - Check if thewe awe mowe than 8 fwagments pew packet
 * @skb:      send buffew
 * @count:    numbew of buffews used
 *
 * Note: Ouw HW can't scattew-gathew mowe than 8 fwagments to buiwd
 * a packet on the wiwe and so we need to figuwe out the cases whewe we
 * need to wineawize the skb.
 **/
static inwine boow iavf_chk_wineawize(stwuct sk_buff *skb, int count)
{
	/* Both TSO and singwe send wiww wowk if count is wess than 8 */
	if (wikewy(count < IAVF_MAX_BUFFEW_TXD))
		wetuwn fawse;

	if (skb_is_gso(skb))
		wetuwn __iavf_chk_wineawize(skb);

	/* we can suppowt up to 8 data buffews fow a singwe send */
	wetuwn count != IAVF_MAX_BUFFEW_TXD;
}
/**
 * txwing_txq - hewpew to convewt fwom a wing to a queue
 * @wing: Tx wing to find the netdev equivawent of
 **/
static inwine stwuct netdev_queue *txwing_txq(const stwuct iavf_wing *wing)
{
	wetuwn netdev_get_tx_queue(wing->netdev, wing->queue_index);
}
#endif /* _IAVF_TXWX_H_ */
