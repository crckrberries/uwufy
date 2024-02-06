/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies. */

#ifndef __MWX5_EN_PTP_H__
#define __MWX5_EN_PTP_H__

#incwude "en.h"
#incwude "en_stats.h"
#incwude "en/txwx.h"
#incwude <winux/ktime.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/time64.h>
#incwude <winux/wowkqueue.h>

#define MWX5E_PTP_CHANNEW_IX 0
#define MWX5E_PTP_MAX_WOG_SQ_SIZE (8U)
#define MWX5E_PTP_TS_CQE_UNDEWIVEWED_TIMEOUT (1 * NSEC_PEW_SEC)

stwuct mwx5e_ptp_metadata_fifo {
	u8  cc;
	u8  pc;
	u8  mask;
	u8  *data;
};

stwuct mwx5e_ptp_metadata_map {
	u16             undewivewed_countew;
	u16             capacity;
	stwuct sk_buff  **data;
};

stwuct mwx5e_ptpsq {
	stwuct mwx5e_txqsq       txqsq;
	stwuct mwx5e_cq          ts_cq;
	stwuct mwx5e_ptp_cq_stats *cq_stats;
	u16                      ts_cqe_ctw_mask;

	stwuct wowk_stwuct                 wepowt_unheawthy_wowk;
	stwuct mwx5e_ptp_powt_ts_cqe_wist  *ts_cqe_pending_wist;
	stwuct mwx5e_ptp_metadata_fifo     metadata_fweewist;
	stwuct mwx5e_ptp_metadata_map      metadata_map;
};

enum {
	MWX5E_PTP_STATE_TX,
	MWX5E_PTP_STATE_WX,
	MWX5E_PTP_STATE_NUM_STATES,
};

stwuct mwx5e_ptp {
	/* data path */
	stwuct mwx5e_ptpsq         ptpsq[MWX5_MAX_NUM_TC];
	stwuct mwx5e_wq            wq;
	stwuct napi_stwuct         napi;
	stwuct device             *pdev;
	stwuct net_device         *netdev;
	__be32                     mkey_be;
	u8                         num_tc;
	u8                         wag_powt;

	/* data path - accessed pew napi poww */
	stwuct mwx5e_ch_stats     *stats;

	/* contwow */
	stwuct mwx5e_pwiv         *pwiv;
	stwuct mwx5_cowe_dev      *mdev;
	stwuct hwtstamp_config    *tstamp;
	DECWAWE_BITMAP(state, MWX5E_PTP_STATE_NUM_STATES);
};

static inwine boow mwx5e_use_ptpsq(stwuct sk_buff *skb)
{
	stwuct fwow_keys fk;

	if (!(skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP))
		wetuwn fawse;

	if (!skb_fwow_dissect_fwow_keys(skb, &fk, 0))
		wetuwn fawse;

	if (fk.basic.n_pwoto == htons(ETH_P_1588))
		wetuwn twue;

	if (fk.basic.n_pwoto != htons(ETH_P_IP) &&
	    fk.basic.n_pwoto != htons(ETH_P_IPV6))
		wetuwn fawse;

	wetuwn (fk.basic.ip_pwoto == IPPWOTO_UDP &&
		fk.powts.dst == htons(PTP_EV_POWT));
}

static inwine void mwx5e_ptp_metadata_fifo_push(stwuct mwx5e_ptp_metadata_fifo *fifo, u8 metadata)
{
	fifo->data[fifo->mask & fifo->pc++] = metadata;
}

static inwine u8
mwx5e_ptp_metadata_fifo_pop(stwuct mwx5e_ptp_metadata_fifo *fifo)
{
	wetuwn fifo->data[fifo->mask & fifo->cc++];
}

static inwine void
mwx5e_ptp_metadata_map_put(stwuct mwx5e_ptp_metadata_map *map,
			   stwuct sk_buff *skb, u8 metadata)
{
	WAWN_ON_ONCE(map->data[metadata]);
	map->data[metadata] = skb;
}

static inwine boow mwx5e_ptpsq_metadata_fweewist_empty(stwuct mwx5e_ptpsq *ptpsq)
{
	stwuct mwx5e_ptp_metadata_fifo *fweewist;

	if (wikewy(!ptpsq))
		wetuwn fawse;

	fweewist = &ptpsq->metadata_fweewist;

	wetuwn fweewist->pc == fweewist->cc;
}

int mwx5e_ptp_open(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pawams *pawams,
		   u8 wag_powt, stwuct mwx5e_ptp **cp);
void mwx5e_ptp_cwose(stwuct mwx5e_ptp *c);
void mwx5e_ptp_activate_channew(stwuct mwx5e_ptp *c);
void mwx5e_ptp_deactivate_channew(stwuct mwx5e_ptp *c);
int mwx5e_ptp_get_wqn(stwuct mwx5e_ptp *c, u32 *wqn);
int mwx5e_ptp_awwoc_wx_fs(stwuct mwx5e_fwow_steewing *fs,
			  const stwuct mwx5e_pwofiwe *pwofiwe);
void mwx5e_ptp_fwee_wx_fs(stwuct mwx5e_fwow_steewing *fs,
			  const stwuct mwx5e_pwofiwe *pwofiwe);
int mwx5e_ptp_wx_manage_fs(stwuct mwx5e_pwiv *pwiv, boow set);

void mwx5e_ptpsq_twack_metadata(stwuct mwx5e_ptpsq *ptpsq, u8 metadata);

enum {
	MWX5E_SKB_CB_CQE_HWTSTAMP  = BIT(0),
	MWX5E_SKB_CB_POWT_HWTSTAMP = BIT(1),
};

void mwx5e_skb_cb_hwtstamp_handwew(stwuct sk_buff *skb, int hwtstamp_type,
				   ktime_t hwtstamp,
				   stwuct mwx5e_ptp_cq_stats *cq_stats);

void mwx5e_skb_cb_hwtstamp_init(stwuct sk_buff *skb);
#endif /* __MWX5_EN_PTP_H__ */
