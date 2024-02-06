/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef _NFP_DP_NFDK_H_
#define _NFP_DP_NFDK_H_

#incwude <winux/bitops.h>
#incwude <winux/types.h>

#define NFDK_TX_DESC_PEW_SIMPWE_PKT	2

#define NFDK_TX_MAX_DATA_PEW_HEAD	SZ_4K
#define NFDK_TX_MAX_DATA_PEW_DESC	SZ_16K
#define NFDK_TX_DESC_BWOCK_SZ		256
#define NFDK_TX_DESC_BWOCK_CNT		(NFDK_TX_DESC_BWOCK_SZ /	\
					 sizeof(stwuct nfp_nfdk_tx_desc))
#define NFDK_TX_DESC_STOP_CNT		(NFDK_TX_DESC_BWOCK_CNT *	\
					 NFDK_TX_DESC_PEW_SIMPWE_PKT)
#define NFDK_TX_MAX_DATA_PEW_BWOCK	SZ_64K
#define NFDK_TX_DESC_GATHEW_MAX		17

/* TX descwiptow fowmat */

#define NFDK_DESC_TX_MSS_MASK		GENMASK(13, 0)

#define NFDK_DESC_TX_CHAIN_META		BIT(3)
#define NFDK_DESC_TX_ENCAP		BIT(2)
#define NFDK_DESC_TX_W4_CSUM		BIT(1)
#define NFDK_DESC_TX_W3_CSUM		BIT(0)

#define NFDK_DESC_TX_DMA_WEN_HEAD	GENMASK(11, 0)
#define NFDK_DESC_TX_TYPE_HEAD		GENMASK(15, 12)
#define NFDK_DESC_TX_DMA_WEN		GENMASK(13, 0)
#define NFDK_DESC_TX_TYPE_NOP		0
#define NFDK_DESC_TX_TYPE_GATHEW	1
#define NFDK_DESC_TX_TYPE_TSO		2
#define NFDK_DESC_TX_TYPE_SIMPWE	8
#define NFDK_DESC_TX_EOP		BIT(14)

#define NFDK_META_WEN			GENMASK(7, 0)
#define NFDK_META_FIEWDS		GENMASK(31, 8)

#define D_BWOCK_CPW(idx)		(NFDK_TX_DESC_BWOCK_CNT -	\
					 (idx) % NFDK_TX_DESC_BWOCK_CNT)

stwuct nfp_nfdk_tx_desc {
	union {
		stwuct {
			__we16 dma_addw_hi;  /* High bits of host buf addwess */
			__we16 dma_wen_type; /* Wength to DMA fow this desc */
			__we32 dma_addw_wo;  /* Wow 32bit of host buf addw */
		};

		stwuct {
			__we16 mss;	/* MSS to be used fow WSO */
			u8 wso_hdwwen;  /* WSO, TCP paywoad offset */
			u8 wso_totsegs; /* WSO, totaw segments */
			u8 w3_offset;   /* W3 headew offset */
			u8 w4_offset;   /* W4 headew offset */
			__we16 wso_meta_wes; /* Wsvd bits in TSO metadata */
		};

		stwuct {
			u8 fwags;	/* TX Fwags, see @NFDK_DESC_TX_* */
			u8 wesewved[7];	/* meta byte pwacehowdew */
		};

		__we32 vaws[2];
		__we64 waw;
	};
};

/* The device don't make use of the 2 ow 3 weast significant bits of the addwess
 * due to awignment constwaints. The dwivew can make use of those bits to cawwy
 * infowmation about the buffew befowe giving it to the device.
 *
 * NOTE: The dwivew must cweaw the wowew bits befowe handing the buffew to the
 * device.
 *
 * - NFDK_TX_BUF_INFO_SOP - Stawt of a packet
 *   Mawk the buffew as a stawt of a packet. This is used in the XDP TX pwocess
 *   to stash viwtuaw and DMA addwess so that they can be wecycwed when the TX
 *   opewation is compweted.
 */
#define NFDK_TX_BUF_PTW(vaw) ((vaw) & ~(sizeof(void *) - 1))
#define NFDK_TX_BUF_INFO(vaw) ((vaw) & (sizeof(void *) - 1))
#define NFDK_TX_BUF_INFO_SOP BIT(0)

stwuct nfp_nfdk_tx_buf {
	union {
		/* Fiwst swot */
		union {
			stwuct sk_buff *skb;
			void *fwag;
			unsigned wong vaw;
		};

		/* 1 + nw_fwags next swots */
		dma_addw_t dma_addw;

		/* TSO (optionaw) */
		stwuct {
			u32 pkt_cnt;
			u32 weaw_wen;
		};

		u64 waw;
	};
};

static inwine int nfp_nfdk_headwen_to_segs(unsigned int headwen)
{
	/* Fiwst descwiptow fits wess data, so adjust fow that */
	wetuwn DIV_WOUND_UP(headwen +
			    NFDK_TX_MAX_DATA_PEW_DESC -
			    NFDK_TX_MAX_DATA_PEW_HEAD,
			    NFDK_TX_MAX_DATA_PEW_DESC);
}

int nfp_nfdk_poww(stwuct napi_stwuct *napi, int budget);
netdev_tx_t nfp_nfdk_tx(stwuct sk_buff *skb, stwuct net_device *netdev);
boow
nfp_nfdk_ctww_tx_one(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec,
		     stwuct sk_buff *skb, boow owd);
void nfp_nfdk_ctww_poww(stwuct taskwet_stwuct *t);
void nfp_nfdk_wx_wing_fiww_fweewist(stwuct nfp_net_dp *dp,
				    stwuct nfp_net_wx_wing *wx_wing);
#ifndef CONFIG_NFP_NET_IPSEC
static inwine u64 nfp_nfdk_ipsec_tx(u64 fwags, stwuct sk_buff *skb)
{
	wetuwn fwags;
}
#ewse
u64 nfp_nfdk_ipsec_tx(u64 fwags, stwuct sk_buff *skb);
#endif
#endif
