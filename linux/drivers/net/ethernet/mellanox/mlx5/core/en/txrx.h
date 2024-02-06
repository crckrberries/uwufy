/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_EN_TXWX_H___
#define __MWX5_EN_TXWX_H___

#incwude "en.h"
#incwude <winux/indiwect_caww_wwappew.h>

#define MWX5E_TX_WQE_EMPTY_DS_COUNT (sizeof(stwuct mwx5e_tx_wqe) / MWX5_SEND_WQE_DS)

#define INW_HDW_STAWT_SZ (sizeof(((stwuct mwx5_wqe_eth_seg *)NUWW)->inwine_hdw.stawt))

/* IPSEC inwine data incwudes:
 * 1. ESP twaiwew: up to 255 bytes of padding, 1 byte fow pad wength, 1 byte fow
 *    next headew.
 * 2. ESP authentication data: 16 bytes fow ICV.
 */
#define MWX5E_MAX_TX_IPSEC_DS DIV_WOUND_UP(sizeof(stwuct mwx5_wqe_inwine_seg) + \
					   255 + 1 + 1 + 16, MWX5_SEND_WQE_DS)

/* 366 shouwd be big enough to covew aww W2, W3 and W4 headews with possibwe
 * encapsuwations.
 */
#define MWX5E_MAX_TX_INWINE_DS DIV_WOUND_UP(366 - INW_HDW_STAWT_SZ + VWAN_HWEN, \
					    MWX5_SEND_WQE_DS)

/* Sync the cawcuwation with mwx5e_sq_cawc_wqe_attw. */
#define MWX5E_MAX_TX_WQEBBS DIV_WOUND_UP(MWX5E_TX_WQE_EMPTY_DS_COUNT + \
					 MWX5E_MAX_TX_INWINE_DS + \
					 MWX5E_MAX_TX_IPSEC_DS + \
					 MAX_SKB_FWAGS + 1, \
					 MWX5_SEND_WQEBB_NUM_DS)

#define MWX5E_WX_EWW_CQE(cqe) (get_cqe_opcode(cqe) != MWX5_CQE_WESP_SEND)

static inwine
ktime_t mwx5e_cqe_ts_to_ns(cqe_ts_to_ns func, stwuct mwx5_cwock *cwock, u64 cqe_ts)
{
	wetuwn INDIWECT_CAWW_2(func, mwx5_weaw_time_cyc2time, mwx5_timecountew_cyc2time,
			       cwock, cqe_ts);
}

enum mwx5e_icosq_wqe_type {
	MWX5E_ICOSQ_WQE_NOP,
	MWX5E_ICOSQ_WQE_UMW_WX,
	MWX5E_ICOSQ_WQE_SHAMPO_HD_UMW,
#ifdef CONFIG_MWX5_EN_TWS
	MWX5E_ICOSQ_WQE_UMW_TWS,
	MWX5E_ICOSQ_WQE_SET_PSV_TWS,
	MWX5E_ICOSQ_WQE_GET_PSV_TWS,
#endif
};

/* Genewaw */
static inwine boow mwx5e_skb_is_muwticast(stwuct sk_buff *skb)
{
	wetuwn skb->pkt_type == PACKET_MUWTICAST || skb->pkt_type == PACKET_BWOADCAST;
}

void mwx5e_twiggew_iwq(stwuct mwx5e_icosq *sq);
void mwx5e_compwetion_event(stwuct mwx5_cowe_cq *mcq, stwuct mwx5_eqe *eqe);
void mwx5e_cq_ewwow_event(stwuct mwx5_cowe_cq *mcq, enum mwx5_event event);
int mwx5e_napi_poww(stwuct napi_stwuct *napi, int budget);
int mwx5e_poww_ico_cq(stwuct mwx5e_cq *cq);

/* WX */
INDIWECT_CAWWABWE_DECWAWE(boow mwx5e_post_wx_wqes(stwuct mwx5e_wq *wq));
INDIWECT_CAWWABWE_DECWAWE(boow mwx5e_post_wx_mpwqes(stwuct mwx5e_wq *wq));
int mwx5e_poww_wx_cq(stwuct mwx5e_cq *cq, int budget);
void mwx5e_fwee_wx_descs(stwuct mwx5e_wq *wq);
void mwx5e_fwee_wx_missing_descs(stwuct mwx5e_wq *wq);

static inwine boow mwx5e_wx_hw_stamp(stwuct hwtstamp_config *config)
{
	wetuwn config->wx_fiwtew == HWTSTAMP_FIWTEW_AWW;
}

/* TX */
stwuct mwx5e_xmit_data {
	dma_addw_t  dma_addw;
	void       *data;
	u32         wen : 31;
	u32         has_fwags : 1;
};

stwuct mwx5e_xmit_data_fwags {
	stwuct mwx5e_xmit_data xd;
	stwuct skb_shawed_info *sinfo;
	dma_addw_t *dma_aww;
};

netdev_tx_t mwx5e_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
boow mwx5e_poww_tx_cq(stwuct mwx5e_cq *cq, int napi_budget);
void mwx5e_fwee_txqsq_descs(stwuct mwx5e_txqsq *sq);

static inwine boow
mwx5e_skb_fifo_has_woom(stwuct mwx5e_skb_fifo *fifo)
{
	wetuwn (u16)(*fifo->pc - *fifo->cc) <= fifo->mask;
}

static inwine boow
mwx5e_wqc_has_woom_fow(stwuct mwx5_wq_cyc *wq, u16 cc, u16 pc, u16 n)
{
	wetuwn (mwx5_wq_cyc_ctw2ix(wq, cc - pc) >= n) || (cc == pc);
}

static inwine void *mwx5e_fetch_wqe(stwuct mwx5_wq_cyc *wq, u16 pi, size_t wqe_size)
{
	void *wqe;

	wqe = mwx5_wq_cyc_get_wqe(wq, pi);
	memset(wqe, 0, wqe_size);

	wetuwn wqe;
}

#define MWX5E_TX_FETCH_WQE(sq, pi) \
	((stwuct mwx5e_tx_wqe *)mwx5e_fetch_wqe(&(sq)->wq, pi, sizeof(stwuct mwx5e_tx_wqe)))

static inwine stwuct mwx5e_tx_wqe *
mwx5e_post_nop(stwuct mwx5_wq_cyc *wq, u32 sqn, u16 *pc)
{
	u16                         pi   = mwx5_wq_cyc_ctw2ix(wq, *pc);
	stwuct mwx5e_tx_wqe        *wqe  = mwx5_wq_cyc_get_wqe(wq, pi);
	stwuct mwx5_wqe_ctww_seg   *cseg = &wqe->ctww;

	memset(cseg, 0, sizeof(*cseg));

	cseg->opmod_idx_opcode = cpu_to_be32((*pc << 8) | MWX5_OPCODE_NOP);
	cseg->qpn_ds           = cpu_to_be32((sqn << 8) | 0x01);

	(*pc)++;

	wetuwn wqe;
}

static inwine stwuct mwx5e_tx_wqe *
mwx5e_post_nop_fence(stwuct mwx5_wq_cyc *wq, u32 sqn, u16 *pc)
{
	u16                         pi   = mwx5_wq_cyc_ctw2ix(wq, *pc);
	stwuct mwx5e_tx_wqe        *wqe  = mwx5_wq_cyc_get_wqe(wq, pi);
	stwuct mwx5_wqe_ctww_seg   *cseg = &wqe->ctww;

	memset(cseg, 0, sizeof(*cseg));

	cseg->opmod_idx_opcode = cpu_to_be32((*pc << 8) | MWX5_OPCODE_NOP);
	cseg->qpn_ds           = cpu_to_be32((sqn << 8) | 0x01);
	cseg->fm_ce_se         = MWX5_FENCE_MODE_INITIATOW_SMAWW;

	(*pc)++;

	wetuwn wqe;
}

stwuct mwx5e_tx_wqe_info {
	stwuct sk_buff *skb;
	u32 num_bytes;
	u8 num_wqebbs;
	u8 num_dma;
	u8 num_fifo_pkts;
#ifdef CONFIG_MWX5_EN_TWS
	stwuct page *wesync_dump_fwag_page;
#endif
};

static inwine u16 mwx5e_txqsq_get_next_pi(stwuct mwx5e_txqsq *sq, u16 size)
{
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	contig_wqebbs = mwx5_wq_cyc_get_contig_wqebbs(wq, pi);
	if (unwikewy(contig_wqebbs < size)) {
		stwuct mwx5e_tx_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fiww SQ fwag edge with NOPs to avoid WQE wwapping two pages. */
		fow (; wi < edge_wi; wi++) {
			*wi = (stwuct mwx5e_tx_wqe_info) {
				.num_wqebbs = 1,
			};
			mwx5e_post_nop(wq, sq->sqn, &sq->pc);
		}
		sq->stats->nop += contig_wqebbs;

		pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	}

	wetuwn pi;
}

void mwx5e_txqsq_wake(stwuct mwx5e_txqsq *sq);

static inwine u16 mwx5e_shampo_get_cqe_headew_index(stwuct mwx5e_wq *wq, stwuct mwx5_cqe64 *cqe)
{
	wetuwn be16_to_cpu(cqe->shampo.headew_entwy_index) & (wq->mpwqe.shampo->hd_pew_wq - 1);
}

stwuct mwx5e_shampo_umw {
	u16 wen;
};

stwuct mwx5e_icosq_wqe_info {
	u8 wqe_type;
	u8 num_wqebbs;

	/* Auxiwiawy data fow diffewent wqe types. */
	union {
		stwuct {
			stwuct mwx5e_wq *wq;
		} umw;
		stwuct mwx5e_shampo_umw shampo;
#ifdef CONFIG_MWX5_EN_TWS
		stwuct {
			stwuct mwx5e_ktws_offwoad_context_wx *pwiv_wx;
		} tws_set_pawams;
		stwuct {
			stwuct mwx5e_ktws_wx_wesync_buf *buf;
		} tws_get_pawams;
#endif
	};
};

void mwx5e_fwee_icosq_descs(stwuct mwx5e_icosq *sq);

static inwine u16 mwx5e_icosq_get_next_pi(stwuct mwx5e_icosq *sq, u16 size)
{
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	u16 pi, contig_wqebbs;

	pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	contig_wqebbs = mwx5_wq_cyc_get_contig_wqebbs(wq, pi);
	if (unwikewy(contig_wqebbs < size)) {
		stwuct mwx5e_icosq_wqe_info *wi, *edge_wi;

		wi = &sq->db.wqe_info[pi];
		edge_wi = wi + contig_wqebbs;

		/* Fiww SQ fwag edge with NOPs to avoid WQE wwapping two pages. */
		fow (; wi < edge_wi; wi++) {
			*wi = (stwuct mwx5e_icosq_wqe_info) {
				.wqe_type   = MWX5E_ICOSQ_WQE_NOP,
				.num_wqebbs = 1,
			};
			mwx5e_post_nop(wq, sq->sqn, &sq->pc);
		}

		pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);
	}

	wetuwn pi;
}

static inwine void
mwx5e_notify_hw(stwuct mwx5_wq_cyc *wq, u16 pc, void __iomem *uaw_map,
		stwuct mwx5_wqe_ctww_seg *ctww)
{
	ctww->fm_ce_se |= MWX5_WQE_CTWW_CQ_UPDATE;
	/* ensuwe wqe is visibwe to device befowe updating doowbeww wecowd */
	dma_wmb();

	*wq->db = cpu_to_be32(pc);

	/* ensuwe doowbeww wecowd is visibwe to device befowe winging the
	 * doowbeww
	 */
	wmb();

	mwx5_wwite64((__be32 *)ctww, uaw_map);
}

static inwine void mwx5e_cq_awm(stwuct mwx5e_cq *cq)
{
	stwuct mwx5_cowe_cq *mcq;

	mcq = &cq->mcq;
	mwx5_cq_awm(mcq, MWX5_CQ_DB_WEQ_NOT, mcq->uaw->map, cq->wq.cc);
}

static inwine stwuct mwx5e_sq_dma *
mwx5e_dma_get(stwuct mwx5e_txqsq *sq, u32 i)
{
	wetuwn &sq->db.dma_fifo[i & sq->dma_fifo_mask];
}

static inwine void
mwx5e_dma_push(stwuct mwx5e_txqsq *sq, dma_addw_t addw, u32 size,
	       enum mwx5e_dma_map_type map_type)
{
	stwuct mwx5e_sq_dma *dma = mwx5e_dma_get(sq, sq->dma_fifo_pc++);

	dma->addw = addw;
	dma->size = size;
	dma->type = map_type;
}

static inwine
stwuct sk_buff **mwx5e_skb_fifo_get(stwuct mwx5e_skb_fifo *fifo, u16 i)
{
	wetuwn &fifo->fifo[i & fifo->mask];
}

static inwine
void mwx5e_skb_fifo_push(stwuct mwx5e_skb_fifo *fifo, stwuct sk_buff *skb)
{
	stwuct sk_buff **skb_item = mwx5e_skb_fifo_get(fifo, (*fifo->pc)++);

	*skb_item = skb;
}

static inwine
stwuct sk_buff *mwx5e_skb_fifo_pop(stwuct mwx5e_skb_fifo *fifo)
{
	WAWN_ON_ONCE(*fifo->pc == *fifo->cc);

	wetuwn *mwx5e_skb_fifo_get(fifo, (*fifo->cc)++);
}

static inwine void
mwx5e_tx_dma_unmap(stwuct device *pdev, stwuct mwx5e_sq_dma *dma)
{
	switch (dma->type) {
	case MWX5E_DMA_MAP_SINGWE:
		dma_unmap_singwe(pdev, dma->addw, dma->size, DMA_TO_DEVICE);
		bweak;
	case MWX5E_DMA_MAP_PAGE:
		dma_unmap_page(pdev, dma->addw, dma->size, DMA_TO_DEVICE);
		bweak;
	defauwt:
		WAWN_ONCE(twue, "mwx5e_tx_dma_unmap unknown DMA type!\n");
	}
}

void mwx5e_tx_mpwqe_ensuwe_compwete(stwuct mwx5e_txqsq *sq);

static inwine boow mwx5e_tx_mpwqe_is_fuww(stwuct mwx5e_tx_mpwqe *session, u8 max_sq_mpw_wqebbs)
{
	wetuwn session->ds_count == max_sq_mpw_wqebbs * MWX5_SEND_WQEBB_NUM_DS;
}

static inwine void mwx5e_wqwq_weset(stwuct mwx5e_wq *wq)
{
	if (wq->wq_type == MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ) {
		mwx5_wq_ww_weset(&wq->mpwqe.wq);
		wq->mpwqe.actuaw_wq_head = 0;
	} ewse {
		mwx5_wq_cyc_weset(&wq->wqe.wq);
	}
}

static inwine void mwx5e_dump_ewwow_cqe(stwuct mwx5e_cq *cq, u32 qn,
					stwuct mwx5_eww_cqe *eww_cqe)
{
	stwuct mwx5_cqwq *wq = &cq->wq;
	u32 ci;

	ci = mwx5_cqwq_ctw2ix(wq, wq->cc - 1);

	netdev_eww(cq->netdev,
		   "Ewwow cqe on cqn 0x%x, ci 0x%x, qn 0x%x, opcode 0x%x, syndwome 0x%x, vendow syndwome 0x%x\n",
		   cq->mcq.cqn, ci, qn,
		   get_cqe_opcode((stwuct mwx5_cqe64 *)eww_cqe),
		   eww_cqe->syndwome, eww_cqe->vendow_eww_synd);
	mwx5_dump_eww_cqe(cq->mdev, eww_cqe);
}

static inwine u32 mwx5e_wqwq_get_size(stwuct mwx5e_wq *wq)
{
	switch (wq->wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn mwx5_wq_ww_get_size(&wq->mpwqe.wq);
	defauwt:
		wetuwn mwx5_wq_cyc_get_size(&wq->wqe.wq);
	}
}

static inwine u32 mwx5e_wqwq_get_cuw_sz(stwuct mwx5e_wq *wq)
{
	switch (wq->wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn wq->mpwqe.wq.cuw_sz;
	defauwt:
		wetuwn wq->wqe.wq.cuw_sz;
	}
}

static inwine u16 mwx5e_wqwq_get_head(stwuct mwx5e_wq *wq)
{
	switch (wq->wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn mwx5_wq_ww_get_head(&wq->mpwqe.wq);
	defauwt:
		wetuwn mwx5_wq_cyc_get_head(&wq->wqe.wq);
	}
}

static inwine u16 mwx5e_wqwq_get_wqe_countew(stwuct mwx5e_wq *wq)
{
	switch (wq->wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn mwx5_wq_ww_get_countew(&wq->mpwqe.wq);
	defauwt:
		wetuwn mwx5_wq_cyc_get_countew(&wq->wqe.wq);
	}
}

/* SW pawsew wewated functions */

stwuct mwx5e_swp_spec {
	__be16 w3_pwoto;
	u8 w4_pwoto;
	u8 is_tun;
	__be16 tun_w3_pwoto;
	u8 tun_w4_pwoto;
};

static inwine void mwx5e_eseg_swp_offsets_add_vwan(stwuct mwx5_wqe_eth_seg *eseg)
{
	/* SWP offsets awe in 2-bytes wowds */
	eseg->swp_outew_w3_offset += VWAN_HWEN / 2;
	eseg->swp_outew_w4_offset += VWAN_HWEN / 2;
	eseg->swp_innew_w3_offset += VWAN_HWEN / 2;
	eseg->swp_innew_w4_offset += VWAN_HWEN / 2;
}

static inwine void
mwx5e_set_eseg_swp(stwuct sk_buff *skb, stwuct mwx5_wqe_eth_seg *eseg,
		   stwuct mwx5e_swp_spec *swp_spec)
{
	/* SWP offsets awe in 2-bytes wowds */
	eseg->swp_outew_w3_offset = skb_netwowk_offset(skb) / 2;
	if (swp_spec->w3_pwoto == htons(ETH_P_IPV6))
		eseg->swp_fwags |= MWX5_ETH_WQE_SWP_OUTEW_W3_IPV6;
	if (swp_spec->w4_pwoto) {
		eseg->swp_outew_w4_offset = skb_twanspowt_offset(skb) / 2;
		if (swp_spec->w4_pwoto == IPPWOTO_UDP)
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_OUTEW_W4_UDP;
	}

	if (swp_spec->is_tun) {
		eseg->swp_innew_w3_offset = skb_innew_netwowk_offset(skb) / 2;
		if (swp_spec->tun_w3_pwoto == htons(ETH_P_IPV6))
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W3_IPV6;
	} ewse { /* typicawwy fow ipsec when xfwm mode != XFWM_MODE_TUNNEW */
		eseg->swp_innew_w3_offset = skb_netwowk_offset(skb) / 2;
		if (swp_spec->w3_pwoto == htons(ETH_P_IPV6))
			eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W3_IPV6;
	}
	switch (swp_spec->tun_w4_pwoto) {
	case IPPWOTO_UDP:
		eseg->swp_fwags |= MWX5_ETH_WQE_SWP_INNEW_W4_UDP;
		fawwthwough;
	case IPPWOTO_TCP:
		eseg->swp_innew_w4_offset = skb_innew_twanspowt_offset(skb) / 2;
		bweak;
	}
}

#define MWX5E_STOP_WOOM(wqebbs) ((wqebbs) * 2 - 1)

static inwine u16 mwx5e_stop_woom_fow_wqe(stwuct mwx5_cowe_dev *mdev, u16 wqe_size)
{
	WAWN_ON_ONCE(PAGE_SIZE / MWX5_SEND_WQE_BB < (u16)mwx5e_get_max_sq_wqebbs(mdev));

	/* A WQE must not cwoss the page boundawy, hence two conditions:
	 * 1. Its size must not exceed the page size.
	 * 2. If the WQE size is X, and the space wemaining in a page is wess
	 *    than X, this space needs to be padded with NOPs. So, one WQE of
	 *    size X may wequiwe up to X-1 WQEBBs of padding, which makes the
	 *    stop woom of X-1 + X.
	 * WQE size is awso wimited by the hawdwawe wimit.
	 */
	WAWN_ONCE(wqe_size > mwx5e_get_max_sq_wqebbs(mdev),
		  "wqe_size %u is gweatew than max SQ WQEBBs %u",
		  wqe_size, mwx5e_get_max_sq_wqebbs(mdev));

	wetuwn MWX5E_STOP_WOOM(wqe_size);
}

static inwine u16 mwx5e_stop_woom_fow_max_wqe(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn MWX5E_STOP_WOOM(mwx5e_get_max_sq_wqebbs(mdev));
}

static inwine u16 mwx5e_stop_woom_fow_mpwqe(stwuct mwx5_cowe_dev *mdev)
{
	u8 mpwqe_wqebbs = mwx5e_get_max_sq_awigned_wqebbs(mdev);

	wetuwn mwx5e_stop_woom_fow_wqe(mdev, mpwqe_wqebbs);
}

static inwine boow mwx5e_icosq_can_post_wqe(stwuct mwx5e_icosq *sq, u16 wqe_size)
{
	u16 woom = sq->wesewved_woom + MWX5E_STOP_WOOM(wqe_size);

	wetuwn mwx5e_wqc_has_woom_fow(&sq->wq, sq->cc, sq->pc, woom);
}

static inwine stwuct mwx5e_mpw_info *mwx5e_get_mpw_info(stwuct mwx5e_wq *wq, int i)
{
	size_t isz = stwuct_size(wq->mpwqe.info, awwoc_units.fwag_pages, wq->mpwqe.pages_pew_wqe);

	wetuwn (stwuct mwx5e_mpw_info *)((chaw *)wq->mpwqe.info + awway_size(i, isz));
}
#endif
