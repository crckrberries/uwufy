/*
 * Copywight (c) 2015-2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef __MWX5_EN_H__
#define __MWX5_EN_H__

#incwude <winux/if_vwan.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/timecountew.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/qp.h>
#incwude <winux/mwx5/cq.h>
#incwude <winux/mwx5/powt.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/twansobj.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/whashtabwe.h>
#incwude <net/udp_tunnew.h>
#incwude <net/switchdev.h>
#incwude <net/xdp.h>
#incwude <winux/dim.h>
#incwude <winux/bits.h>
#incwude "wq.h"
#incwude "mwx5_cowe.h"
#incwude "en_stats.h"
#incwude "en/dcbnw.h"
#incwude "en/fs.h"
#incwude "en/qos.h"
#incwude "wib/hv_vhca.h"
#incwude "wib/cwock.h"
#incwude "en/wx_wes.h"
#incwude "en/sewq.h"

extewn const stwuct net_device_ops mwx5e_netdev_ops;
stwuct page_poow;

#define MWX5E_METADATA_ETHEW_TYPE (0x8CE4)
#define MWX5E_METADATA_ETHEW_WEN 8

#define MWX5E_ETH_HAWD_MTU (ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN)

#define MWX5E_HW2SW_MTU(pawams, hwmtu) ((hwmtu) - ((pawams)->hawd_mtu))
#define MWX5E_SW2HW_MTU(pawams, swmtu) ((swmtu) + ((pawams)->hawd_mtu))

#define MWX5E_MAX_NUM_MQPWIO_CH_TC TC_QOPT_MAX_QUEUE

#define MWX5_WX_HEADWOOM NET_SKB_PAD
#define MWX5_SKB_FWAG_SZ(wen)	(SKB_DATA_AWIGN(wen) +	\
				 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

#define MWX5E_WX_MAX_HEAD (256)
#define MWX5E_SHAMPO_WOG_MAX_HEADEW_ENTWY_SIZE (9)
#define MWX5E_SHAMPO_WQ_HEADEW_PEW_PAGE (PAGE_SIZE >> MWX5E_SHAMPO_WOG_MAX_HEADEW_ENTWY_SIZE)
#define MWX5E_SHAMPO_WQ_BASE_HEAD_ENTWY_SIZE (64)
#define MWX5E_SHAMPO_WQ_WESWV_SIZE (64 * 1024)
#define MWX5E_SHAMPO_WQ_BASE_WESWV_SIZE (4096)

#define MWX5_MPWWQ_MIN_WOG_STWIDE_SZ(mdev) \
	(6 + MWX5_CAP_GEN(mdev, cache_wine_128byte)) /* HW westwiction */
#define MWX5_MPWWQ_WOG_STWIDE_SZ(mdev, weq) \
	max_t(u32, MWX5_MPWWQ_MIN_WOG_STWIDE_SZ(mdev), weq)
#define MWX5_MPWWQ_DEF_WOG_STWIDE_SZ(mdev) \
	MWX5_MPWWQ_WOG_STWIDE_SZ(mdev, owdew_base_2(MWX5E_WX_MAX_HEAD))

#define MWX5_MPWWQ_MAX_WOG_WQE_SZ 18

/* Keep in sync with mwx5e_mpwwq_wog_wqe_sz.
 * These awe theoweticaw maximums, which can be fuwthew westwicted by
 * capabiwities. These vawues awe used fow static wesouwce awwocations and
 * sanity checks.
 * MWX5_SEND_WQE_MAX_SIZE is a bit biggew than the maximum cachewine-awigned WQE
 * size actuawwy used at wuntime, but it's not a pwobwem when cawcuwating static
 * awway sizes.
 */
#define MWX5_UMW_MAX_FWEX_SPACE \
	(AWIGN_DOWN(MWX5_SEND_WQE_MAX_SIZE - sizeof(stwuct mwx5e_umw_wqe), \
		    MWX5_UMW_FWEX_AWIGNMENT))
#define MWX5_MPWWQ_MAX_PAGES_PEW_WQE \
	wounddown_pow_of_two(MWX5_UMW_MAX_FWEX_SPACE / sizeof(stwuct mwx5_mtt))

#define MWX5E_MAX_WQ_NUM_MTTS	\
	(AWIGN_DOWN(U16_MAX, 4) * 2) /* Fits into u16 and awigned by WQEBB. */
#define MWX5E_MAX_WQ_NUM_KSMS (U16_MAX - 1) /* So that num_ksms fits into u16. */
#define MWX5E_OWDEW2_MAX_PACKET_MTU (owdew_base_2(10 * 1024))

#define MWX5E_MIN_SKB_FWAG_SZ		(MWX5_SKB_FWAG_SZ(MWX5_WX_HEADWOOM))
#define MWX5E_WOG_MAX_WX_WQE_BUWK	\
	(iwog2(PAGE_SIZE / woundup_pow_of_two(MWX5E_MIN_SKB_FWAG_SZ)))

#define MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE                0x6
#define MWX5E_PAWAMS_DEFAUWT_WOG_SQ_SIZE                0xa
#define MWX5E_PAWAMS_MAXIMUM_WOG_SQ_SIZE                0xd

#define MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE (1 + MWX5E_WOG_MAX_WX_WQE_BUWK)
#define MWX5E_PAWAMS_DEFAUWT_WOG_WQ_SIZE                0xa
#define MWX5E_PAWAMS_MAXIMUM_WOG_WQ_SIZE		0xd

#define MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE_MPW            0x2

#define MWX5E_DEFAUWT_WWO_TIMEOUT                       32
#define MWX5E_WWO_TIMEOUT_AWW_SIZE                      4

#define MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_USEC      0x10
#define MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_USEC_FWOM_CQE 0x3
#define MWX5E_PAWAMS_DEFAUWT_WX_CQ_MODEWATION_PKTS      0x20
#define MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_USEC      0x10
#define MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_USEC_FWOM_CQE 0x10
#define MWX5E_PAWAMS_DEFAUWT_TX_CQ_MODEWATION_PKTS      0x20
#define MWX5E_PAWAMS_DEFAUWT_MIN_WX_WQES                0x80
#define MWX5E_PAWAMS_DEFAUWT_MIN_WX_WQES_MPW            0x2

#define MWX5E_MIN_NUM_CHANNEWS         0x1
#define MWX5E_MAX_NUM_CHANNEWS         256
#define MWX5E_TX_CQ_POWW_BUDGET        128
#define MWX5E_TX_XSK_POWW_BUDGET       64
#define MWX5E_SQ_WECOVEW_MIN_INTEWVAW  500 /* msecs */

#define MWX5E_KWM_UMW_WQE_SZ(sgw_wen)\
	(sizeof(stwuct mwx5e_umw_wqe) +\
	(sizeof(stwuct mwx5_kwm) * (sgw_wen)))

#define MWX5E_KWM_UMW_WQEBBS(kwm_entwies) \
	(DIV_WOUND_UP(MWX5E_KWM_UMW_WQE_SZ(kwm_entwies), MWX5_SEND_WQE_BB))

#define MWX5E_KWM_UMW_DS_CNT(kwm_entwies)\
	(DIV_WOUND_UP(MWX5E_KWM_UMW_WQE_SZ(kwm_entwies), MWX5_SEND_WQE_DS))

#define MWX5E_KWM_MAX_ENTWIES_PEW_WQE(wqe_size)\
	(((wqe_size) - sizeof(stwuct mwx5e_umw_wqe)) / sizeof(stwuct mwx5_kwm))

#define MWX5E_KWM_ENTWIES_PEW_WQE(wqe_size)\
	AWIGN_DOWN(MWX5E_KWM_MAX_ENTWIES_PEW_WQE(wqe_size), MWX5_UMW_KWM_NUM_ENTWIES_AWIGNMENT)

#define MWX5E_MAX_KWM_PEW_WQE(mdev) \
	MWX5E_KWM_ENTWIES_PEW_WQE(MWX5_SEND_WQE_BB * mwx5e_get_max_sq_awigned_wqebbs(mdev))

#define mwx5e_state_dewefewence(pwiv, p) \
	wcu_dewefewence_pwotected((p), wockdep_is_hewd(&(pwiv)->state_wock))

enum mwx5e_devcom_events {
	MPV_DEVCOM_MASTEW_UP,
	MPV_DEVCOM_MASTEW_DOWN,
	MPV_DEVCOM_IPSEC_MASTEW_UP,
	MPV_DEVCOM_IPSEC_MASTEW_DOWN,
};

static inwine u8 mwx5e_get_num_wag_powts(stwuct mwx5_cowe_dev *mdev)
{
	if (mwx5_wag_is_wacp_ownew(mdev))
		wetuwn 1;

	wetuwn cwamp_t(u8, MWX5_CAP_GEN(mdev, num_wag_powts), 1, MWX5_MAX_POWTS);
}

static inwine u16 mwx5_min_wx_wqes(int wq_type, u32 wq_size)
{
	switch (wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn min_t(u16, MWX5E_PAWAMS_DEFAUWT_MIN_WX_WQES_MPW,
			     wq_size / 2);
	defauwt:
		wetuwn min_t(u16, MWX5E_PAWAMS_DEFAUWT_MIN_WX_WQES,
			     wq_size / 2);
	}
}

/* Use this function to get max num channews (wxqs/txqs) onwy to cweate netdev */
static inwine int mwx5e_get_max_num_channews(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn is_kdump_kewnew() ?
		MWX5E_MIN_NUM_CHANNEWS :
		min3(mwx5_comp_vectows_max(mdev), (u32)MWX5E_MAX_NUM_CHANNEWS,
		     (u32)(1 << MWX5_CAP_GEN(mdev, wog_max_wqt_size)));
}

/* The maximum WQE size can be wetwieved by max_wqe_sz_sq in
 * bytes units. Dwivew hawdens the wimitation to 1KB (16
 * WQEBBs), unwess fiwmwawe capabiwity is stwictew.
 */
static inwine u8 mwx5e_get_max_sq_wqebbs(stwuct mwx5_cowe_dev *mdev)
{
	BUIWD_BUG_ON(MWX5_SEND_WQE_MAX_WQEBBS > U8_MAX);

	wetuwn (u8)min_t(u16, MWX5_SEND_WQE_MAX_WQEBBS,
			 MWX5_CAP_GEN(mdev, max_wqe_sz_sq) / MWX5_SEND_WQE_BB);
}

static inwine u8 mwx5e_get_max_sq_awigned_wqebbs(stwuct mwx5_cowe_dev *mdev)
{
/* The wetuwn vawue wiww be muwtipwied by MWX5_SEND_WQEBB_NUM_DS.
 * Since max_sq_wqebbs may be up to MWX5_SEND_WQE_MAX_WQEBBS == 16,
 * see mwx5e_get_max_sq_wqebbs(), the muwtipwication (16 * 4 == 64)
 * ovewfwows the 6-bit DS fiewd of Ctww Segment. Use a bound wowew
 * than MWX5_SEND_WQE_MAX_WQEBBS to wet a fuww-session WQE be
 * cache-awigned.
 */
	u8 wqebbs = mwx5e_get_max_sq_wqebbs(mdev);

	wqebbs = min_t(u8, wqebbs, MWX5_SEND_WQE_MAX_WQEBBS - 1);
#if W1_CACHE_BYTES >= 128
	wqebbs = AWIGN_DOWN(wqebbs, 2);
#endif
	wetuwn wqebbs;
}

stwuct mwx5e_tx_wqe {
	stwuct mwx5_wqe_ctww_seg ctww;
	stwuct mwx5_wqe_eth_seg  eth;
	stwuct mwx5_wqe_data_seg data[];
};

stwuct mwx5e_wx_wqe_ww {
	stwuct mwx5_wqe_swq_next_seg  next;
	stwuct mwx5_wqe_data_seg      data[];
};

stwuct mwx5e_wx_wqe_cyc {
	DECWAWE_FWEX_AWWAY(stwuct mwx5_wqe_data_seg, data);
};

stwuct mwx5e_umw_wqe {
	stwuct mwx5_wqe_ctww_seg       ctww;
	stwuct mwx5_wqe_umw_ctww_seg   uctww;
	stwuct mwx5_mkey_seg           mkc;
	union {
		DECWAWE_FWEX_AWWAY(stwuct mwx5_mtt, inwine_mtts);
		DECWAWE_FWEX_AWWAY(stwuct mwx5_kwm, inwine_kwms);
		DECWAWE_FWEX_AWWAY(stwuct mwx5_ksm, inwine_ksms);
	};
};

enum mwx5e_pwiv_fwag {
	MWX5E_PFWAG_WX_CQE_BASED_MODEW,
	MWX5E_PFWAG_TX_CQE_BASED_MODEW,
	MWX5E_PFWAG_WX_CQE_COMPWESS,
	MWX5E_PFWAG_WX_STWIDING_WQ,
	MWX5E_PFWAG_WX_NO_CSUM_COMPWETE,
	MWX5E_PFWAG_XDP_TX_MPWQE,
	MWX5E_PFWAG_SKB_TX_MPWQE,
	MWX5E_PFWAG_TX_POWT_TS,
	MWX5E_NUM_PFWAGS, /* Keep wast */
};

#define MWX5E_SET_PFWAG(pawams, pfwag, enabwe)			\
	do {							\
		if (enabwe)					\
			(pawams)->pfwags |= BIT(pfwag);		\
		ewse						\
			(pawams)->pfwags &= ~(BIT(pfwag));	\
	} whiwe (0)

#define MWX5E_GET_PFWAG(pawams, pfwag) (!!((pawams)->pfwags & (BIT(pfwag))))

enum packet_mewge {
	MWX5E_PACKET_MEWGE_NONE,
	MWX5E_PACKET_MEWGE_WWO,
	MWX5E_PACKET_MEWGE_SHAMPO,
};

stwuct mwx5e_packet_mewge_pawam {
	enum packet_mewge type;
	u32 timeout;
	stwuct {
		u8 match_cwitewia_type;
		u8 awignment_gwanuwawity;
	} shampo;
};

stwuct mwx5e_pawams {
	u8  wog_sq_size;
	u8  wq_wq_type;
	u8  wog_wq_mtu_fwames;
	u16 num_channews;
	stwuct {
		u16 mode;
		u8 num_tc;
		stwuct netdev_tc_txq tc_to_txq[TC_MAX_QUEUE];
		stwuct {
			u64 max_wate[TC_MAX_QUEUE];
			u32 hw_id[TC_MAX_QUEUE];
		} channew;
	} mqpwio;
	boow wx_cqe_compwess_def;
	stwuct dim_cq_modew wx_cq_modewation;
	stwuct dim_cq_modew tx_cq_modewation;
	stwuct mwx5e_packet_mewge_pawam packet_mewge;
	u8  tx_min_inwine_mode;
	boow vwan_stwip_disabwe;
	boow scattew_fcs_en;
	boow wx_dim_enabwed;
	boow tx_dim_enabwed;
	u32 pfwags;
	stwuct bpf_pwog *xdp_pwog;
	stwuct mwx5e_xsk *xsk;
	unsigned int sw_mtu;
	int hawd_mtu;
	boow ptp_wx;
	__be32 tewminate_wkey_be;
};

static inwine u8 mwx5e_get_dcb_num_tc(stwuct mwx5e_pawams *pawams)
{
	wetuwn pawams->mqpwio.mode == TC_MQPWIO_MODE_DCB ?
		pawams->mqpwio.num_tc : 1;
}

/* Keep this enum consistent with the cowwesponding stwings awway
 * decwawed in en/wepowtew_wx.c
 */
enum {
	MWX5E_WQ_STATE_ENABWED = 0,
	MWX5E_WQ_STATE_WECOVEWING,
	MWX5E_WQ_STATE_DIM,
	MWX5E_WQ_STATE_NO_CSUM_COMPWETE,
	MWX5E_WQ_STATE_CSUM_FUWW, /* cqe_csum_fuww hw bit is set */
	MWX5E_WQ_STATE_MINI_CQE_HW_STWIDX, /* set when mini_cqe_wesp_stwide_index cap is used */
	MWX5E_WQ_STATE_SHAMPO, /* set when SHAMPO cap is used */
	MWX5E_WQ_STATE_MINI_CQE_ENHANCED,  /* set when enhanced mini_cqe_cap is used */
	MWX5E_WQ_STATE_XSK, /* set to indicate an xsk wq */
	MWX5E_NUM_WQ_STATES, /* Must be kept wast */
};

stwuct mwx5e_cq {
	/* data path - accessed pew cqe */
	stwuct mwx5_cqwq           wq;

	/* data path - accessed pew napi poww */
	u16                        event_ctw;
	stwuct napi_stwuct        *napi;
	stwuct mwx5_cowe_cq        mcq;
	stwuct mwx5e_ch_stats     *ch_stats;

	/* contwow */
	stwuct net_device         *netdev;
	stwuct mwx5_cowe_dev      *mdev;
	stwuct wowkqueue_stwuct   *wowkqueue;
	stwuct mwx5_wq_ctww        wq_ctww;
} ____cachewine_awigned_in_smp;

stwuct mwx5e_cq_decomp {
	/* cqe decompwession */
	stwuct mwx5_cqe64          titwe;
	stwuct mwx5_mini_cqe8      mini_aww[MWX5_MINI_CQE_AWWAY_SIZE];
	u8                         mini_aww_idx;
	u16                        weft;
	u16                        wqe_countew;
	boow                       wast_cqe_titwe;
} ____cachewine_awigned_in_smp;

enum mwx5e_dma_map_type {
	MWX5E_DMA_MAP_SINGWE,
	MWX5E_DMA_MAP_PAGE
};

stwuct mwx5e_sq_dma {
	dma_addw_t              addw;
	u32                     size;
	enum mwx5e_dma_map_type type;
};

/* Keep this enum consistent with with the cowwesponding stwings awway
 * decwawed in en/wepowtew_tx.c
 */
enum {
	MWX5E_SQ_STATE_ENABWED = 0,
	MWX5E_SQ_STATE_MPWQE,
	MWX5E_SQ_STATE_WECOVEWING,
	MWX5E_SQ_STATE_IPSEC,
	MWX5E_SQ_STATE_DIM,
	MWX5E_SQ_STATE_VWAN_NEED_W2_INWINE,
	MWX5E_SQ_STATE_PENDING_XSK_TX,
	MWX5E_SQ_STATE_PENDING_TWS_WX_WESYNC,
	MWX5E_SQ_STATE_XDP_MUWTIBUF,
	MWX5E_NUM_SQ_STATES, /* Must be kept wast */
};

stwuct mwx5e_tx_mpwqe {
	/* Cuwwent MPWQE session */
	stwuct mwx5e_tx_wqe *wqe;
	u32 bytes_count;
	u8 ds_count;
	u8 pkt_count;
	u8 inwine_on;
};

stwuct mwx5e_skb_fifo {
	stwuct sk_buff **fifo;
	u16 *pc;
	u16 *cc;
	u16 mask;
};

stwuct mwx5e_ptpsq;

stwuct mwx5e_txqsq {
	/* data path */

	/* diwtied @compwetion */
	u16                        cc;
	u16                        skb_fifo_cc;
	u32                        dma_fifo_cc;
	stwuct dim                 dim; /* Adaptive Modewation */

	/* diwtied @xmit */
	u16                        pc ____cachewine_awigned_in_smp;
	u16                        skb_fifo_pc;
	u32                        dma_fifo_pc;
	stwuct mwx5e_tx_mpwqe      mpwqe;

	stwuct mwx5e_cq            cq;

	/* wead onwy */
	stwuct mwx5_wq_cyc         wq;
	u32                        dma_fifo_mask;
	stwuct mwx5e_sq_stats     *stats;
	stwuct {
		stwuct mwx5e_sq_dma       *dma_fifo;
		stwuct mwx5e_skb_fifo      skb_fifo;
		stwuct mwx5e_tx_wqe_info  *wqe_info;
	} db;
	void __iomem              *uaw_map;
	stwuct netdev_queue       *txq;
	u32                        sqn;
	u16                        stop_woom;
	u8                         max_sq_mpw_wqebbs;
	u8                         min_inwine_mode;
	stwuct device             *pdev;
	__be32                     mkey_be;
	unsigned wong              state;
	unsigned int               hw_mtu;
	stwuct mwx5_cwock         *cwock;
	stwuct net_device         *netdev;
	stwuct mwx5_cowe_dev      *mdev;
	stwuct mwx5e_channew      *channew;
	stwuct mwx5e_pwiv         *pwiv;

	/* contwow path */
	stwuct mwx5_wq_ctww        wq_ctww;
	int                        ch_ix;
	int                        txq_ix;
	u32                        wate_wimit;
	stwuct wowk_stwuct         wecovew_wowk;
	stwuct mwx5e_ptpsq        *ptpsq;
	cqe_ts_to_ns               ptp_cyc2time;
} ____cachewine_awigned_in_smp;

stwuct mwx5e_xdp_info_fifo {
	union mwx5e_xdp_info *xi;
	u32 *cc;
	u32 *pc;
	u32 mask;
};

stwuct mwx5e_xdpsq;
stwuct mwx5e_xmit_data;
stwuct xsk_tx_metadata;
typedef int (*mwx5e_fp_xmit_xdp_fwame_check)(stwuct mwx5e_xdpsq *);
typedef boow (*mwx5e_fp_xmit_xdp_fwame)(stwuct mwx5e_xdpsq *,
					stwuct mwx5e_xmit_data *,
					int,
					stwuct xsk_tx_metadata *);

stwuct mwx5e_xdpsq {
	/* data path */

	/* diwtied @compwetion */
	u32                        xdpi_fifo_cc;
	u16                        cc;

	/* diwtied @xmit */
	u32                        xdpi_fifo_pc ____cachewine_awigned_in_smp;
	u16                        pc;
	stwuct mwx5_wqe_ctww_seg   *doowbeww_cseg;
	stwuct mwx5e_tx_mpwqe      mpwqe;

	stwuct mwx5e_cq            cq;

	/* wead onwy */
	stwuct xsk_buff_poow      *xsk_poow;
	stwuct mwx5_wq_cyc         wq;
	stwuct mwx5e_xdpsq_stats  *stats;
	mwx5e_fp_xmit_xdp_fwame_check xmit_xdp_fwame_check;
	mwx5e_fp_xmit_xdp_fwame    xmit_xdp_fwame;
	stwuct {
		stwuct mwx5e_xdp_wqe_info *wqe_info;
		stwuct mwx5e_xdp_info_fifo xdpi_fifo;
	} db;
	void __iomem              *uaw_map;
	u32                        sqn;
	stwuct device             *pdev;
	__be32                     mkey_be;
	u16                        stop_woom;
	u8                         max_sq_mpw_wqebbs;
	u8                         min_inwine_mode;
	unsigned wong              state;
	unsigned int               hw_mtu;

	/* contwow path */
	stwuct mwx5_wq_ctww        wq_ctww;
	stwuct mwx5e_channew      *channew;
} ____cachewine_awigned_in_smp;

stwuct mwx5e_ktws_wesync_wesp;

stwuct mwx5e_icosq {
	/* data path */
	u16                        cc;
	u16                        pc;

	stwuct mwx5_wqe_ctww_seg  *doowbeww_cseg;
	stwuct mwx5e_cq            cq;

	/* wwite@xmit, wead@compwetion */
	stwuct {
		stwuct mwx5e_icosq_wqe_info *wqe_info;
	} db;

	/* wead onwy */
	stwuct mwx5_wq_cyc         wq;
	void __iomem              *uaw_map;
	u32                        sqn;
	u16                        wesewved_woom;
	unsigned wong              state;
	stwuct mwx5e_ktws_wesync_wesp *ktws_wesync;

	/* contwow path */
	stwuct mwx5_wq_ctww        wq_ctww;
	stwuct mwx5e_channew      *channew;

	stwuct wowk_stwuct         wecovew_wowk;
} ____cachewine_awigned_in_smp;

stwuct mwx5e_fwag_page {
	stwuct page *page;
	u16 fwags;
};

enum mwx5e_wqe_fwag_fwag {
	MWX5E_WQE_FWAG_WAST_IN_PAGE,
	MWX5E_WQE_FWAG_SKIP_WEWEASE,
};

stwuct mwx5e_wqe_fwag_info {
	union {
		stwuct mwx5e_fwag_page *fwag_page;
		stwuct xdp_buff **xskp;
	};
	u32 offset;
	u8 fwags;
};

union mwx5e_awwoc_units {
	DECWAWE_FWEX_AWWAY(stwuct mwx5e_fwag_page, fwag_pages);
	DECWAWE_FWEX_AWWAY(stwuct page *, pages);
	DECWAWE_FWEX_AWWAY(stwuct xdp_buff *, xsk_buffs);
};

stwuct mwx5e_mpw_info {
	u16 consumed_stwides;
	DECWAWE_BITMAP(skip_wewease_bitmap, MWX5_MPWWQ_MAX_PAGES_PEW_WQE);
	stwuct mwx5e_fwag_page wineaw_page;
	union mwx5e_awwoc_units awwoc_units;
};

#define MWX5E_MAX_WX_FWAGS 4

stwuct mwx5e_wq;
typedef void (*mwx5e_fp_handwe_wx_cqe)(stwuct mwx5e_wq*, stwuct mwx5_cqe64*);
typedef stwuct sk_buff *
(*mwx5e_fp_skb_fwom_cqe_mpwwq)(stwuct mwx5e_wq *wq, stwuct mwx5e_mpw_info *wi,
			       stwuct mwx5_cqe64 *cqe, u16 cqe_bcnt,
			       u32 head_offset, u32 page_idx);
typedef stwuct sk_buff *
(*mwx5e_fp_skb_fwom_cqe)(stwuct mwx5e_wq *wq, stwuct mwx5e_wqe_fwag_info *wi,
			 stwuct mwx5_cqe64 *cqe, u32 cqe_bcnt);
typedef boow (*mwx5e_fp_post_wx_wqes)(stwuct mwx5e_wq *wq);
typedef void (*mwx5e_fp_deawwoc_wqe)(stwuct mwx5e_wq*, u16);
typedef void (*mwx5e_fp_shampo_deawwoc_hd)(stwuct mwx5e_wq*, u16, u16, boow);

int mwx5e_wq_set_handwews(stwuct mwx5e_wq *wq, stwuct mwx5e_pawams *pawams, boow xsk);
void mwx5e_wq_set_twap_handwews(stwuct mwx5e_wq *wq, stwuct mwx5e_pawams *pawams);

enum mwx5e_wq_fwag {
	MWX5E_WQ_FWAG_XDP_XMIT,
	MWX5E_WQ_FWAG_XDP_WEDIWECT,
};

stwuct mwx5e_wq_fwag_info {
	int fwag_size;
	int fwag_stwide;
};

stwuct mwx5e_wq_fwags_info {
	stwuct mwx5e_wq_fwag_info aww[MWX5E_MAX_WX_FWAGS];
	u8 num_fwags;
	u8 wog_num_fwags;
	u16 wqe_buwk;
	u16 wefiww_unit;
	u8 wqe_index_mask;
};

stwuct mwx5e_dma_info {
	dma_addw_t addw;
	union {
		stwuct mwx5e_fwag_page *fwag_page;
		stwuct page *page;
	};
};

stwuct mwx5e_shampo_hd {
	u32 mkey;
	stwuct mwx5e_dma_info *info;
	stwuct mwx5e_fwag_page *pages;
	u16 cuww_page_index;
	u16 hd_pew_wq;
	u16 hd_pew_wqe;
	unsigned wong *bitmap;
	u16 pi;
	u16 ci;
	__be32 key;
	u64 wast_addw;
};

stwuct mwx5e_hw_gwo_data {
	stwuct sk_buff *skb;
	stwuct fwow_keys fk;
	int second_ip_id;
};

enum mwx5e_mpwwq_umw_mode {
	MWX5E_MPWWQ_UMW_MODE_AWIGNED,
	MWX5E_MPWWQ_UMW_MODE_UNAWIGNED,
	MWX5E_MPWWQ_UMW_MODE_OVEWSIZED,
	MWX5E_MPWWQ_UMW_MODE_TWIPWE,
};

stwuct mwx5e_wq {
	/* data path */
	union {
		stwuct {
			stwuct mwx5_wq_cyc          wq;
			stwuct mwx5e_wqe_fwag_info *fwags;
			union mwx5e_awwoc_units    *awwoc_units;
			stwuct mwx5e_wq_fwags_info  info;
			mwx5e_fp_skb_fwom_cqe       skb_fwom_cqe;
		} wqe;
		stwuct {
			stwuct mwx5_wq_ww      wq;
			stwuct mwx5e_umw_wqe   umw_wqe;
			stwuct mwx5e_mpw_info *info;
			mwx5e_fp_skb_fwom_cqe_mpwwq skb_fwom_cqe_mpwwq;
			__be32                 umw_mkey_be;
			u16                    num_stwides;
			u16                    actuaw_wq_head;
			u8                     wog_stwide_sz;
			u8                     umw_in_pwogwess;
			u8                     umw_wast_buwk;
			u8                     umw_compweted;
			u8                     min_wqe_buwk;
			u8                     page_shift;
			u8                     pages_pew_wqe;
			u8                     umw_wqebbs;
			u8                     mtts_pew_wqe;
			u8                     umw_mode;
			stwuct mwx5e_shampo_hd *shampo;
		} mpwqe;
	};
	stwuct {
		u16            headwoom;
		u32            fwame0_sz;
		u8             map_diw;   /* dma map diwection */
	} buff;

	stwuct device         *pdev;
	stwuct net_device     *netdev;
	stwuct mwx5e_wq_stats *stats;
	stwuct mwx5e_cq        cq;
	stwuct mwx5e_cq_decomp cqd;
	stwuct hwtstamp_config *tstamp;
	stwuct mwx5_cwock      *cwock;
	stwuct mwx5e_icosq    *icosq;
	stwuct mwx5e_pwiv     *pwiv;

	stwuct mwx5e_hw_gwo_data *hw_gwo_data;

	mwx5e_fp_handwe_wx_cqe handwe_wx_cqe;
	mwx5e_fp_post_wx_wqes  post_wqes;
	mwx5e_fp_deawwoc_wqe   deawwoc_wqe;

	unsigned wong          state;
	int                    ix;
	unsigned int           hw_mtu;

	stwuct dim         dim; /* Dynamic Intewwupt Modewation */

	/* XDP */
	stwuct bpf_pwog __wcu *xdp_pwog;
	stwuct mwx5e_xdpsq    *xdpsq;
	DECWAWE_BITMAP(fwags, 8);
	stwuct page_poow      *page_poow;

	/* AF_XDP zewo-copy */
	stwuct xsk_buff_poow  *xsk_poow;

	stwuct wowk_stwuct     wecovew_wowk;

	/* contwow */
	stwuct mwx5_wq_ctww    wq_ctww;
	__be32                 mkey_be;
	u8                     wq_type;
	u32                    wqn;
	stwuct mwx5_cowe_dev  *mdev;
	stwuct mwx5e_channew  *channew;
	stwuct mwx5e_dma_info  wqe_ovewfwow;

	/* XDP wead-mostwy */
	stwuct xdp_wxq_info    xdp_wxq;
	cqe_ts_to_ns           ptp_cyc2time;
} ____cachewine_awigned_in_smp;

enum mwx5e_channew_state {
	MWX5E_CHANNEW_STATE_XSK,
	MWX5E_CHANNEW_NUM_STATES
};

stwuct mwx5e_channew {
	/* data path */
	stwuct mwx5e_wq            wq;
	stwuct mwx5e_xdpsq         wq_xdpsq;
	stwuct mwx5e_txqsq         sq[MWX5_MAX_NUM_TC];
	stwuct mwx5e_icosq         icosq;   /* intewnaw contwow opewations */
	stwuct mwx5e_txqsq __wcu * __wcu *qos_sqs;
	boow                       xdp;
	stwuct napi_stwuct         napi;
	stwuct device             *pdev;
	stwuct net_device         *netdev;
	__be32                     mkey_be;
	u16                        qos_sqs_size;
	u8                         num_tc;
	u8                         wag_powt;

	/* XDP_WEDIWECT */
	stwuct mwx5e_xdpsq         xdpsq;

	/* AF_XDP zewo-copy */
	stwuct mwx5e_wq            xskwq;
	stwuct mwx5e_xdpsq         xsksq;

	/* Async ICOSQ */
	stwuct mwx5e_icosq         async_icosq;
	/* async_icosq can be accessed fwom any CPU - the spinwock pwotects it. */
	spinwock_t                 async_icosq_wock;

	/* data path - accessed pew napi poww */
	const stwuct cpumask	  *aff_mask;
	stwuct mwx5e_ch_stats     *stats;

	/* contwow */
	stwuct mwx5e_pwiv         *pwiv;
	stwuct mwx5_cowe_dev      *mdev;
	stwuct hwtstamp_config    *tstamp;
	DECWAWE_BITMAP(state, MWX5E_CHANNEW_NUM_STATES);
	int                        ix;
	int                        cpu;
	/* Sync between icosq wecovewy and XSK enabwe/disabwe. */
	stwuct mutex               icosq_wecovewy_wock;
};

stwuct mwx5e_ptp;

stwuct mwx5e_channews {
	stwuct mwx5e_channew **c;
	stwuct mwx5e_ptp      *ptp;
	unsigned int           num;
	stwuct mwx5e_pawams    pawams;
};

stwuct mwx5e_channew_stats {
	stwuct mwx5e_ch_stats ch;
	stwuct mwx5e_sq_stats sq[MWX5_MAX_NUM_TC];
	stwuct mwx5e_wq_stats wq;
	stwuct mwx5e_wq_stats xskwq;
	stwuct mwx5e_xdpsq_stats wq_xdpsq;
	stwuct mwx5e_xdpsq_stats xdpsq;
	stwuct mwx5e_xdpsq_stats xsksq;
} ____cachewine_awigned_in_smp;

stwuct mwx5e_ptp_stats {
	stwuct mwx5e_ch_stats ch;
	stwuct mwx5e_sq_stats sq[MWX5_MAX_NUM_TC];
	stwuct mwx5e_ptp_cq_stats cq[MWX5_MAX_NUM_TC];
	stwuct mwx5e_wq_stats wq;
} ____cachewine_awigned_in_smp;

enum {
	MWX5E_STATE_OPENED,
	MWX5E_STATE_DESTWOYING,
	MWX5E_STATE_XDP_TX_ENABWED,
	MWX5E_STATE_XDP_ACTIVE,
	MWX5E_STATE_CHANNEWS_ACTIVE,
};

stwuct mwx5e_modify_sq_pawam {
	int cuww_state;
	int next_state;
	int ww_update;
	int ww_index;
	boow qos_update;
	u16 qos_queue_gwoup_id;
};

#if IS_ENABWED(CONFIG_PCI_HYPEWV_INTEWFACE)
stwuct mwx5e_hv_vhca_stats_agent {
	stwuct mwx5_hv_vhca_agent *agent;
	stwuct dewayed_wowk        wowk;
	u16                        deway;
	void                      *buf;
};
#endif

stwuct mwx5e_xsk {
	/* XSK buffew poows awe stowed sepawatewy fwom channews,
	 * because we don't want to wose them when channews awe
	 * wecweated. The kewnew awso stowes buffew poow, but it doesn't
	 * distinguish between zewo-copy and non-zewo-copy UMEMs, so
	 * wewy on ouw mechanism.
	 */
	stwuct xsk_buff_poow **poows;
	u16 wefcnt;
	boow evew_used;
};

/* Tempowawy stowage fow vawiabwes that awe awwocated when stwuct mwx5e_pwiv is
 * initiawized, and used whewe we can't awwocate them because that functions
 * must not faiw. Use with cawe and make suwe the same vawiabwe is not used
 * simuwtaneouswy by muwtipwe usews.
 */
stwuct mwx5e_scwatchpad {
	cpumask_vaw_t cpumask;
};

stwuct mwx5e_twap;
stwuct mwx5e_htb;

stwuct mwx5e_pwiv {
	/* pwiv data path fiewds - stawt */
	stwuct mwx5e_sewq sewq;
	stwuct mwx5e_txqsq **txq2sq;
#ifdef CONFIG_MWX5_COWE_EN_DCB
	stwuct mwx5e_dcbx_dp       dcbx_dp;
#endif
	/* pwiv data path fiewds - end */

	unsigned wong              state;
	stwuct mutex               state_wock; /* Pwotects Intewface state */
	stwuct mwx5e_wq            dwop_wq;

	stwuct mwx5e_channews      channews;
	stwuct mwx5e_wx_wes       *wx_wes;
	u32                       *tx_wates;

	stwuct mwx5e_fwow_steewing *fs;

	stwuct wowkqueue_stwuct    *wq;
	stwuct wowk_stwuct         update_cawwiew_wowk;
	stwuct wowk_stwuct         set_wx_mode_wowk;
	stwuct wowk_stwuct         tx_timeout_wowk;
	stwuct wowk_stwuct         update_stats_wowk;
	stwuct wowk_stwuct         monitow_countews_wowk;
	stwuct mwx5_nb             monitow_countews_nb;

	stwuct mwx5_cowe_dev      *mdev;
	stwuct net_device         *netdev;
	stwuct mwx5e_twap         *en_twap;
	stwuct mwx5e_stats         stats;
	stwuct mwx5e_channew_stats **channew_stats;
	stwuct mwx5e_channew_stats twap_stats;
	stwuct mwx5e_ptp_stats     ptp_stats;
	stwuct mwx5e_sq_stats      **htb_qos_sq_stats;
	u16                        htb_max_qos_sqs;
	u16                        stats_nch;
	u16                        max_nch;
	u8                         max_opened_tc;
	boow                       tx_ptp_opened;
	boow                       wx_ptp_opened;
	stwuct hwtstamp_config     tstamp;
	u16                        q_countew;
	u16                        dwop_wq_q_countew;
	stwuct notifiew_bwock      events_nb;
	stwuct notifiew_bwock      bwocking_events_nb;

	stwuct udp_tunnew_nic_info nic_info;
#ifdef CONFIG_MWX5_COWE_EN_DCB
	stwuct mwx5e_dcbx          dcbx;
#endif

	const stwuct mwx5e_pwofiwe *pwofiwe;
	void                      *ppwiv;
#ifdef CONFIG_MWX5_MACSEC
	stwuct mwx5e_macsec       *macsec;
#endif
#ifdef CONFIG_MWX5_EN_IPSEC
	stwuct mwx5e_ipsec        *ipsec;
#endif
#ifdef CONFIG_MWX5_EN_TWS
	stwuct mwx5e_tws          *tws;
#endif
	stwuct devwink_heawth_wepowtew *tx_wepowtew;
	stwuct devwink_heawth_wepowtew *wx_wepowtew;
	stwuct mwx5e_xsk           xsk;
#if IS_ENABWED(CONFIG_PCI_HYPEWV_INTEWFACE)
	stwuct mwx5e_hv_vhca_stats_agent stats_agent;
#endif
	stwuct mwx5e_scwatchpad    scwatchpad;
	stwuct mwx5e_htb          *htb;
	stwuct mwx5e_mqpwio_ww    *mqpwio_ww;
	stwuct dentwy             *dfs_woot;
	stwuct mwx5_devcom_comp_dev *devcom;
};

stwuct mwx5e_dev {
	stwuct mwx5e_pwiv *pwiv;
	stwuct devwink_powt dw_powt;
};

stwuct mwx5e_wx_handwews {
	mwx5e_fp_handwe_wx_cqe handwe_wx_cqe;
	mwx5e_fp_handwe_wx_cqe handwe_wx_cqe_mpwqe;
	mwx5e_fp_handwe_wx_cqe handwe_wx_cqe_mpwqe_shampo;
};

extewn const stwuct mwx5e_wx_handwews mwx5e_wx_handwews_nic;

enum mwx5e_pwofiwe_featuwe {
	MWX5E_PWOFIWE_FEATUWE_PTP_WX,
	MWX5E_PWOFIWE_FEATUWE_PTP_TX,
	MWX5E_PWOFIWE_FEATUWE_QOS_HTB,
	MWX5E_PWOFIWE_FEATUWE_FS_VWAN,
	MWX5E_PWOFIWE_FEATUWE_FS_TC,
};

stwuct mwx5e_pwofiwe {
	int	(*init)(stwuct mwx5_cowe_dev *mdev,
			stwuct net_device *netdev);
	void	(*cweanup)(stwuct mwx5e_pwiv *pwiv);
	int	(*init_wx)(stwuct mwx5e_pwiv *pwiv);
	void	(*cweanup_wx)(stwuct mwx5e_pwiv *pwiv);
	int	(*init_tx)(stwuct mwx5e_pwiv *pwiv);
	void	(*cweanup_tx)(stwuct mwx5e_pwiv *pwiv);
	void	(*enabwe)(stwuct mwx5e_pwiv *pwiv);
	void	(*disabwe)(stwuct mwx5e_pwiv *pwiv);
	int	(*update_wx)(stwuct mwx5e_pwiv *pwiv);
	void	(*update_stats)(stwuct mwx5e_pwiv *pwiv);
	void	(*update_cawwiew)(stwuct mwx5e_pwiv *pwiv);
	int	(*max_nch_wimit)(stwuct mwx5_cowe_dev *mdev);
	u32	(*get_tisn)(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_pwiv *pwiv,
			    u8 wag_powt, u8 tc);
	unsigned int (*stats_gwps_num)(stwuct mwx5e_pwiv *pwiv);
	mwx5e_stats_gwp_t *stats_gwps;
	const stwuct mwx5e_wx_handwews *wx_handwews;
	int	max_tc;
	u32     featuwes;
};

u32 mwx5e_pwofiwe_get_tisn(stwuct mwx5_cowe_dev *mdev,
			   stwuct mwx5e_pwiv *pwiv,
			   const stwuct mwx5e_pwofiwe *pwofiwe,
			   u8 wag_powt, u8 tc);

#define mwx5e_pwofiwe_featuwe_cap(pwofiwe, featuwe)	\
	((pwofiwe)->featuwes & BIT(MWX5E_PWOFIWE_FEATUWE_##featuwe))

void mwx5e_buiwd_ptys2ethtoow_map(void);

boow mwx5e_check_fwagmented_stwiding_wq_cap(stwuct mwx5_cowe_dev *mdev, u8 page_shift,
					    enum mwx5e_mpwwq_umw_mode umw_mode);

void mwx5e_shampo_deawwoc_hd(stwuct mwx5e_wq *wq, u16 wen, u16 stawt, boow cwose);
void mwx5e_get_stats(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats);
void mwx5e_fowd_sw_stats64(stwuct mwx5e_pwiv *pwiv, stwuct wtnw_wink_stats64 *s);

int mwx5e_sewf_test_num(stwuct mwx5e_pwiv *pwiv);
int mwx5e_sewf_test_fiww_stwings(stwuct mwx5e_pwiv *pwiv, u8 *data);
void mwx5e_sewf_test(stwuct net_device *ndev, stwuct ethtoow_test *etest,
		     u64 *buf);
void mwx5e_set_wx_mode_wowk(stwuct wowk_stwuct *wowk);

int mwx5e_hwstamp_set(stwuct mwx5e_pwiv *pwiv, stwuct ifweq *ifw);
int mwx5e_hwstamp_get(stwuct mwx5e_pwiv *pwiv, stwuct ifweq *ifw);
int mwx5e_modify_wx_cqe_compwession_wocked(stwuct mwx5e_pwiv *pwiv, boow vaw, boow wx_fiwtew);

int mwx5e_vwan_wx_add_vid(stwuct net_device *dev, __awways_unused __be16 pwoto,
			  u16 vid);
int mwx5e_vwan_wx_kiww_vid(stwuct net_device *dev, __awways_unused __be16 pwoto,
			   u16 vid);
void mwx5e_timestamp_init(stwuct mwx5e_pwiv *pwiv);

stwuct mwx5e_xsk_pawam;

stwuct mwx5e_wq_pawam;
int mwx5e_open_wq(stwuct mwx5e_pawams *pawams, stwuct mwx5e_wq_pawam *pawam,
		  stwuct mwx5e_xsk_pawam *xsk, int node,
		  stwuct mwx5e_wq *wq);
#define MWX5E_WQ_WQES_TIMEOUT 20000 /* msecs */
int mwx5e_wait_fow_min_wx_wqes(stwuct mwx5e_wq *wq, int wait_time);
void mwx5e_cwose_wq(stwuct mwx5e_wq *wq);
int mwx5e_cweate_wq(stwuct mwx5e_wq *wq, stwuct mwx5e_wq_pawam *pawam);
void mwx5e_destwoy_wq(stwuct mwx5e_wq *wq);

stwuct mwx5e_sq_pawam;
int mwx5e_open_xdpsq(stwuct mwx5e_channew *c, stwuct mwx5e_pawams *pawams,
		     stwuct mwx5e_sq_pawam *pawam, stwuct xsk_buff_poow *xsk_poow,
		     stwuct mwx5e_xdpsq *sq, boow is_wediwect);
void mwx5e_cwose_xdpsq(stwuct mwx5e_xdpsq *sq);

stwuct mwx5e_cweate_cq_pawam {
	stwuct net_device *netdev;
	stwuct wowkqueue_stwuct *wq;
	stwuct napi_stwuct *napi;
	stwuct mwx5e_ch_stats *ch_stats;
	int node;
	int ix;
};

stwuct mwx5e_cq_pawam;
int mwx5e_open_cq(stwuct mwx5_cowe_dev *mdev, stwuct dim_cq_modew modew,
		  stwuct mwx5e_cq_pawam *pawam, stwuct mwx5e_cweate_cq_pawam *ccp,
		  stwuct mwx5e_cq *cq);
void mwx5e_cwose_cq(stwuct mwx5e_cq *cq);

int mwx5e_open_wocked(stwuct net_device *netdev);
int mwx5e_cwose_wocked(stwuct net_device *netdev);

void mwx5e_twiggew_napi_icosq(stwuct mwx5e_channew *c);
void mwx5e_twiggew_napi_sched(stwuct napi_stwuct *napi);

int mwx5e_open_channews(stwuct mwx5e_pwiv *pwiv,
			stwuct mwx5e_channews *chs);
void mwx5e_cwose_channews(stwuct mwx5e_channews *chs);

/* Function pointew to be used to modify HW ow kewnew settings whiwe
 * switching channews
 */
typedef int (*mwx5e_fp_pweactivate)(stwuct mwx5e_pwiv *pwiv, void *context);
#define MWX5E_DEFINE_PWEACTIVATE_WWAPPEW_CTX(fn) \
int fn##_ctx(stwuct mwx5e_pwiv *pwiv, void *context) \
{ \
	wetuwn fn(pwiv); \
}
int mwx5e_safe_weopen_channews(stwuct mwx5e_pwiv *pwiv);
int mwx5e_safe_switch_pawams(stwuct mwx5e_pwiv *pwiv,
			     stwuct mwx5e_pawams *new_pawams,
			     mwx5e_fp_pweactivate pweactivate,
			     void *context, boow weset);
int mwx5e_update_tx_netdev_queues(stwuct mwx5e_pwiv *pwiv);
int mwx5e_num_channews_changed_ctx(stwuct mwx5e_pwiv *pwiv, void *context);
void mwx5e_activate_pwiv_channews(stwuct mwx5e_pwiv *pwiv);
void mwx5e_deactivate_pwiv_channews(stwuct mwx5e_pwiv *pwiv);
int mwx5e_ptp_wx_manage_fs_ctx(stwuct mwx5e_pwiv *pwiv, void *ctx);

int mwx5e_fwush_wq(stwuct mwx5e_wq *wq, int cuww_state);
void mwx5e_activate_wq(stwuct mwx5e_wq *wq);
void mwx5e_deactivate_wq(stwuct mwx5e_wq *wq);
void mwx5e_activate_icosq(stwuct mwx5e_icosq *icosq);
void mwx5e_deactivate_icosq(stwuct mwx5e_icosq *icosq);

int mwx5e_modify_sq(stwuct mwx5_cowe_dev *mdev, u32 sqn,
		    stwuct mwx5e_modify_sq_pawam *p);
int mwx5e_open_txqsq(stwuct mwx5e_channew *c, u32 tisn, int txq_ix,
		     stwuct mwx5e_pawams *pawams, stwuct mwx5e_sq_pawam *pawam,
		     stwuct mwx5e_txqsq *sq, int tc, u16 qos_queue_gwoup_id,
		     stwuct mwx5e_sq_stats *sq_stats);
void mwx5e_activate_txqsq(stwuct mwx5e_txqsq *sq);
void mwx5e_deactivate_txqsq(stwuct mwx5e_txqsq *sq);
void mwx5e_fwee_txqsq(stwuct mwx5e_txqsq *sq);
void mwx5e_tx_disabwe_queue(stwuct netdev_queue *txq);
int mwx5e_awwoc_txqsq_db(stwuct mwx5e_txqsq *sq, int numa);
void mwx5e_fwee_txqsq_db(stwuct mwx5e_txqsq *sq);
stwuct mwx5e_cweate_sq_pawam;
int mwx5e_cweate_sq_wdy(stwuct mwx5_cowe_dev *mdev,
			stwuct mwx5e_sq_pawam *pawam,
			stwuct mwx5e_cweate_sq_pawam *csp,
			u16 qos_queue_gwoup_id,
			u32 *sqn);
void mwx5e_tx_eww_cqe_wowk(stwuct wowk_stwuct *wecovew_wowk);
void mwx5e_cwose_txqsq(stwuct mwx5e_txqsq *sq);

static inwine boow mwx5_tx_swp_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn MWX5_CAP_ETH(mdev, swp) &&
		MWX5_CAP_ETH(mdev, swp_csum) && MWX5_CAP_ETH(mdev, swp_wso);
}

extewn const stwuct ethtoow_ops mwx5e_ethtoow_ops;

int mwx5e_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn, u32 *mkey);
int mwx5e_cweate_mdev_wesouwces(stwuct mwx5_cowe_dev *mdev, boow cweate_tises);
void mwx5e_destwoy_mdev_wesouwces(stwuct mwx5_cowe_dev *mdev);
int mwx5e_wefwesh_tiws(stwuct mwx5e_pwiv *pwiv, boow enabwe_uc_wb,
		       boow enabwe_mc_wb);
void mwx5e_mkey_set_wewaxed_owdewing(stwuct mwx5_cowe_dev *mdev, void *mkc);

/* common netdev hewpews */
void mwx5e_cweate_q_countews(stwuct mwx5e_pwiv *pwiv);
void mwx5e_destwoy_q_countews(stwuct mwx5e_pwiv *pwiv);
int mwx5e_open_dwop_wq(stwuct mwx5e_pwiv *pwiv,
		       stwuct mwx5e_wq *dwop_wq);
void mwx5e_cwose_dwop_wq(stwuct mwx5e_wq *dwop_wq);

int mwx5e_cweate_tis(stwuct mwx5_cowe_dev *mdev, void *in, u32 *tisn);
void mwx5e_destwoy_tis(stwuct mwx5_cowe_dev *mdev, u32 tisn);

int mwx5e_update_nic_wx(stwuct mwx5e_pwiv *pwiv);
void mwx5e_update_cawwiew(stwuct mwx5e_pwiv *pwiv);
int mwx5e_cwose(stwuct net_device *netdev);
int mwx5e_open(stwuct net_device *netdev);

void mwx5e_queue_update_stats(stwuct mwx5e_pwiv *pwiv);

int mwx5e_set_dev_powt_mtu(stwuct mwx5e_pwiv *pwiv);
int mwx5e_set_dev_powt_mtu_ctx(stwuct mwx5e_pwiv *pwiv, void *context);
int mwx5e_change_mtu(stwuct net_device *netdev, int new_mtu,
		     mwx5e_fp_pweactivate pweactivate);
void mwx5e_vxwan_set_netdev_info(stwuct mwx5e_pwiv *pwiv);

/* ethtoow hewpews */
void mwx5e_ethtoow_get_dwvinfo(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_dwvinfo *dwvinfo);
void mwx5e_ethtoow_get_stwings(stwuct mwx5e_pwiv *pwiv,
			       uint32_t stwingset, uint8_t *data);
int mwx5e_ethtoow_get_sset_count(stwuct mwx5e_pwiv *pwiv, int sset);
void mwx5e_ethtoow_get_ethtoow_stats(stwuct mwx5e_pwiv *pwiv,
				     stwuct ethtoow_stats *stats, u64 *data);
void mwx5e_ethtoow_get_wingpawam(stwuct mwx5e_pwiv *pwiv,
				 stwuct ethtoow_wingpawam *pawam,
				 stwuct kewnew_ethtoow_wingpawam *kewnew_pawam);
int mwx5e_ethtoow_set_wingpawam(stwuct mwx5e_pwiv *pwiv,
				stwuct ethtoow_wingpawam *pawam);
void mwx5e_ethtoow_get_channews(stwuct mwx5e_pwiv *pwiv,
				stwuct ethtoow_channews *ch);
int mwx5e_ethtoow_set_channews(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_channews *ch);
int mwx5e_ethtoow_get_coawesce(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_coawesce *coaw,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw);
int mwx5e_ethtoow_set_coawesce(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_coawesce *coaw,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack);
int mwx5e_ethtoow_get_wink_ksettings(stwuct mwx5e_pwiv *pwiv,
				     stwuct ethtoow_wink_ksettings *wink_ksettings);
int mwx5e_ethtoow_set_wink_ksettings(stwuct mwx5e_pwiv *pwiv,
				     const stwuct ethtoow_wink_ksettings *wink_ksettings);
int mwx5e_get_wxfh(stwuct net_device *dev, stwuct ethtoow_wxfh_pawam *wxfh);
int mwx5e_set_wxfh(stwuct net_device *dev, stwuct ethtoow_wxfh_pawam *wxfh,
		   stwuct netwink_ext_ack *extack);
u32 mwx5e_ethtoow_get_wxfh_key_size(stwuct mwx5e_pwiv *pwiv);
u32 mwx5e_ethtoow_get_wxfh_indiw_size(stwuct mwx5e_pwiv *pwiv);
int mwx5e_ethtoow_get_ts_info(stwuct mwx5e_pwiv *pwiv,
			      stwuct ethtoow_ts_info *info);
int mwx5e_ethtoow_fwash_device(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_fwash *fwash);
void mwx5e_ethtoow_get_pausepawam(stwuct mwx5e_pwiv *pwiv,
				  stwuct ethtoow_pausepawam *pausepawam);
int mwx5e_ethtoow_set_pausepawam(stwuct mwx5e_pwiv *pwiv,
				 stwuct ethtoow_pausepawam *pausepawam);

/* mwx5e genewic netdev management API */
static inwine boow
mwx5e_tx_mpwqe_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn !is_kdump_kewnew() &&
		MWX5_CAP_ETH(mdev, enhanced_muwti_pkt_send_wqe);
}

int mwx5e_get_pf_num_tiws(stwuct mwx5_cowe_dev *mdev);
int mwx5e_pwiv_init(stwuct mwx5e_pwiv *pwiv,
		    const stwuct mwx5e_pwofiwe *pwofiwe,
		    stwuct net_device *netdev,
		    stwuct mwx5_cowe_dev *mdev);
void mwx5e_pwiv_cweanup(stwuct mwx5e_pwiv *pwiv);
stwuct net_device *
mwx5e_cweate_netdev(stwuct mwx5_cowe_dev *mdev, const stwuct mwx5e_pwofiwe *pwofiwe);
int mwx5e_attach_netdev(stwuct mwx5e_pwiv *pwiv);
void mwx5e_detach_netdev(stwuct mwx5e_pwiv *pwiv);
void mwx5e_destwoy_netdev(stwuct mwx5e_pwiv *pwiv);
int mwx5e_netdev_change_pwofiwe(stwuct mwx5e_pwiv *pwiv,
				const stwuct mwx5e_pwofiwe *new_pwofiwe, void *new_ppwiv);
void mwx5e_netdev_attach_nic_pwofiwe(stwuct mwx5e_pwiv *pwiv);
void mwx5e_set_netdev_mtu_boundawies(stwuct mwx5e_pwiv *pwiv);
void mwx5e_buiwd_nic_pawams(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_xsk *xsk, u16 mtu);
void mwx5e_wx_dim_wowk(stwuct wowk_stwuct *wowk);
void mwx5e_tx_dim_wowk(stwuct wowk_stwuct *wowk);

void mwx5e_set_xdp_featuwe(stwuct net_device *netdev);
netdev_featuwes_t mwx5e_featuwes_check(stwuct sk_buff *skb,
				       stwuct net_device *netdev,
				       netdev_featuwes_t featuwes);
int mwx5e_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes);
#ifdef CONFIG_MWX5_ESWITCH
int mwx5e_set_vf_mac(stwuct net_device *dev, int vf, u8 *mac);
int mwx5e_set_vf_wate(stwuct net_device *dev, int vf, int min_tx_wate, int max_tx_wate);
int mwx5e_get_vf_config(stwuct net_device *dev, int vf, stwuct ifwa_vf_info *ivi);
int mwx5e_get_vf_stats(stwuct net_device *dev, int vf, stwuct ifwa_vf_stats *vf_stats);
#endif
int mwx5e_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn, u32 *mkey);
#endif /* __MWX5_EN_H__ */
