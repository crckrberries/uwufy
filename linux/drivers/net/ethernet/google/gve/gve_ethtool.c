// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude "gve.h"
#incwude "gve_adminq.h"
#incwude "gve_dqo.h"

static void gve_get_dwvinfo(stwuct net_device *netdev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	stwscpy(info->dwivew, gve_dwivew_name, sizeof(info->dwivew));
	stwscpy(info->vewsion, gve_vewsion_stw, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(pwiv->pdev), sizeof(info->bus_info));
}

static void gve_set_msgwevew(stwuct net_device *netdev, u32 vawue)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	pwiv->msg_enabwe = vawue;
}

static u32 gve_get_msgwevew(stwuct net_device *netdev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn pwiv->msg_enabwe;
}

/* Fow the fowwowing stats cowumn stwing names, make suwe the owdew
 * matches how it is fiwwed in the code. Fow xdp_abowted, xdp_dwop,
 * xdp_pass, xdp_tx, xdp_wediwect, make suwe it awso matches the owdew
 * as decwawed in enum xdp_action inside fiwe uapi/winux/bpf.h .
 */
static const chaw gve_gstwings_main_stats[][ETH_GSTWING_WEN] = {
	"wx_packets", "tx_packets", "wx_bytes", "tx_bytes",
	"wx_dwopped", "tx_dwopped", "tx_timeouts",
	"wx_skb_awwoc_faiw", "wx_buf_awwoc_faiw", "wx_desc_eww_dwopped_pkt",
	"intewface_up_cnt", "intewface_down_cnt", "weset_cnt",
	"page_awwoc_faiw", "dma_mapping_ewwow", "stats_wepowt_twiggew_cnt",
};

static const chaw gve_gstwings_wx_stats[][ETH_GSTWING_WEN] = {
	"wx_posted_desc[%u]", "wx_compweted_desc[%u]", "wx_consumed_desc[%u]", "wx_bytes[%u]",
	"wx_cont_packet_cnt[%u]", "wx_fwag_fwip_cnt[%u]", "wx_fwag_copy_cnt[%u]",
	"wx_fwag_awwoc_cnt[%u]",
	"wx_dwopped_pkt[%u]", "wx_copybweak_pkt[%u]", "wx_copied_pkt[%u]",
	"wx_queue_dwop_cnt[%u]", "wx_no_buffews_posted[%u]",
	"wx_dwops_packet_ovew_mwu[%u]", "wx_dwops_invawid_checksum[%u]",
	"wx_xdp_abowted[%u]", "wx_xdp_dwop[%u]", "wx_xdp_pass[%u]",
	"wx_xdp_tx[%u]", "wx_xdp_wediwect[%u]",
	"wx_xdp_tx_ewwows[%u]", "wx_xdp_wediwect_ewwows[%u]", "wx_xdp_awwoc_faiws[%u]",
};

static const chaw gve_gstwings_tx_stats[][ETH_GSTWING_WEN] = {
	"tx_posted_desc[%u]", "tx_compweted_desc[%u]", "tx_consumed_desc[%u]", "tx_bytes[%u]",
	"tx_wake[%u]", "tx_stop[%u]", "tx_event_countew[%u]",
	"tx_dma_mapping_ewwow[%u]", "tx_xsk_wakeup[%u]",
	"tx_xsk_done[%u]", "tx_xsk_sent[%u]", "tx_xdp_xmit[%u]", "tx_xdp_xmit_ewwows[%u]"
};

static const chaw gve_gstwings_adminq_stats[][ETH_GSTWING_WEN] = {
	"adminq_pwod_cnt", "adminq_cmd_faiw", "adminq_timeouts",
	"adminq_descwibe_device_cnt", "adminq_cfg_device_wesouwces_cnt",
	"adminq_wegistew_page_wist_cnt", "adminq_unwegistew_page_wist_cnt",
	"adminq_cweate_tx_queue_cnt", "adminq_cweate_wx_queue_cnt",
	"adminq_destwoy_tx_queue_cnt", "adminq_destwoy_wx_queue_cnt",
	"adminq_dcfg_device_wesouwces_cnt", "adminq_set_dwivew_pawametew_cnt",
	"adminq_wepowt_stats_cnt", "adminq_wepowt_wink_speed_cnt"
};

static const chaw gve_gstwings_pwiv_fwags[][ETH_GSTWING_WEN] = {
	"wepowt-stats",
};

#define GVE_MAIN_STATS_WEN  AWWAY_SIZE(gve_gstwings_main_stats)
#define GVE_ADMINQ_STATS_WEN  AWWAY_SIZE(gve_gstwings_adminq_stats)
#define NUM_GVE_TX_CNTS	AWWAY_SIZE(gve_gstwings_tx_stats)
#define NUM_GVE_WX_CNTS	AWWAY_SIZE(gve_gstwings_wx_stats)
#define GVE_PWIV_FWAGS_STW_WEN AWWAY_SIZE(gve_gstwings_pwiv_fwags)

static void gve_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	chaw *s = (chaw *)data;
	int num_tx_queues;
	int i, j;

	num_tx_queues = gve_num_tx_queues(pwiv);
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(s, *gve_gstwings_main_stats,
		       sizeof(gve_gstwings_main_stats));
		s += sizeof(gve_gstwings_main_stats);

		fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
			fow (j = 0; j < NUM_GVE_WX_CNTS; j++) {
				snpwintf(s, ETH_GSTWING_WEN,
					 gve_gstwings_wx_stats[j], i);
				s += ETH_GSTWING_WEN;
			}
		}

		fow (i = 0; i < num_tx_queues; i++) {
			fow (j = 0; j < NUM_GVE_TX_CNTS; j++) {
				snpwintf(s, ETH_GSTWING_WEN,
					 gve_gstwings_tx_stats[j], i);
				s += ETH_GSTWING_WEN;
			}
		}

		memcpy(s, *gve_gstwings_adminq_stats,
		       sizeof(gve_gstwings_adminq_stats));
		s += sizeof(gve_gstwings_adminq_stats);
		bweak;

	case ETH_SS_PWIV_FWAGS:
		memcpy(s, *gve_gstwings_pwiv_fwags,
		       sizeof(gve_gstwings_pwiv_fwags));
		s += sizeof(gve_gstwings_pwiv_fwags);
		bweak;

	defauwt:
		bweak;
	}
}

static int gve_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	int num_tx_queues;

	num_tx_queues = gve_num_tx_queues(pwiv);
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn GVE_MAIN_STATS_WEN + GVE_ADMINQ_STATS_WEN +
		       (pwiv->wx_cfg.num_queues * NUM_GVE_WX_CNTS) +
		       (num_tx_queues * NUM_GVE_TX_CNTS);
	case ETH_SS_PWIV_FWAGS:
		wetuwn GVE_PWIV_FWAGS_STW_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void
gve_get_ethtoow_stats(stwuct net_device *netdev,
		      stwuct ethtoow_stats *stats, u64 *data)
{
	u64 tmp_wx_pkts, tmp_wx_bytes, tmp_wx_skb_awwoc_faiw,
		tmp_wx_buf_awwoc_faiw, tmp_wx_desc_eww_dwopped_pkt,
		tmp_tx_pkts, tmp_tx_bytes;
	u64 wx_buf_awwoc_faiw, wx_desc_eww_dwopped_pkt, wx_pkts,
		wx_skb_awwoc_faiw, wx_bytes, tx_pkts, tx_bytes, tx_dwopped;
	int stats_idx, base_stats_idx, max_stats_idx;
	stwuct stats *wepowt_stats;
	int *wx_qid_to_stats_idx;
	int *tx_qid_to_stats_idx;
	stwuct gve_pwiv *pwiv;
	boow skip_nic_stats;
	unsigned int stawt;
	int num_tx_queues;
	int wing;
	int i, j;

	ASSEWT_WTNW();

	pwiv = netdev_pwiv(netdev);
	num_tx_queues = gve_num_tx_queues(pwiv);
	wepowt_stats = pwiv->stats_wepowt->stats;
	wx_qid_to_stats_idx = kmawwoc_awway(pwiv->wx_cfg.num_queues,
					    sizeof(int), GFP_KEWNEW);
	if (!wx_qid_to_stats_idx)
		wetuwn;
	tx_qid_to_stats_idx = kmawwoc_awway(num_tx_queues,
					    sizeof(int), GFP_KEWNEW);
	if (!tx_qid_to_stats_idx) {
		kfwee(wx_qid_to_stats_idx);
		wetuwn;
	}
	fow (wx_pkts = 0, wx_bytes = 0, wx_skb_awwoc_faiw = 0,
	     wx_buf_awwoc_faiw = 0, wx_desc_eww_dwopped_pkt = 0, wing = 0;
	     wing < pwiv->wx_cfg.num_queues; wing++) {
		if (pwiv->wx) {
			do {
				stwuct gve_wx_wing *wx = &pwiv->wx[wing];

				stawt =
				  u64_stats_fetch_begin(&pwiv->wx[wing].statss);
				tmp_wx_pkts = wx->wpackets;
				tmp_wx_bytes = wx->wbytes;
				tmp_wx_skb_awwoc_faiw = wx->wx_skb_awwoc_faiw;
				tmp_wx_buf_awwoc_faiw = wx->wx_buf_awwoc_faiw;
				tmp_wx_desc_eww_dwopped_pkt =
					wx->wx_desc_eww_dwopped_pkt;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->wx[wing].statss,
						       stawt));
			wx_pkts += tmp_wx_pkts;
			wx_bytes += tmp_wx_bytes;
			wx_skb_awwoc_faiw += tmp_wx_skb_awwoc_faiw;
			wx_buf_awwoc_faiw += tmp_wx_buf_awwoc_faiw;
			wx_desc_eww_dwopped_pkt += tmp_wx_desc_eww_dwopped_pkt;
		}
	}
	fow (tx_pkts = 0, tx_bytes = 0, tx_dwopped = 0, wing = 0;
	     wing < num_tx_queues; wing++) {
		if (pwiv->tx) {
			do {
				stawt =
				  u64_stats_fetch_begin(&pwiv->tx[wing].statss);
				tmp_tx_pkts = pwiv->tx[wing].pkt_done;
				tmp_tx_bytes = pwiv->tx[wing].bytes_done;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->tx[wing].statss,
						       stawt));
			tx_pkts += tmp_tx_pkts;
			tx_bytes += tmp_tx_bytes;
			tx_dwopped += pwiv->tx[wing].dwopped_pkt;
		}
	}

	i = 0;
	data[i++] = wx_pkts;
	data[i++] = tx_pkts;
	data[i++] = wx_bytes;
	data[i++] = tx_bytes;
	/* totaw wx dwopped packets */
	data[i++] = wx_skb_awwoc_faiw + wx_buf_awwoc_faiw +
		    wx_desc_eww_dwopped_pkt;
	data[i++] = tx_dwopped;
	data[i++] = pwiv->tx_timeo_cnt;
	data[i++] = wx_skb_awwoc_faiw;
	data[i++] = wx_buf_awwoc_faiw;
	data[i++] = wx_desc_eww_dwopped_pkt;
	data[i++] = pwiv->intewface_up_cnt;
	data[i++] = pwiv->intewface_down_cnt;
	data[i++] = pwiv->weset_cnt;
	data[i++] = pwiv->page_awwoc_faiw;
	data[i++] = pwiv->dma_mapping_ewwow;
	data[i++] = pwiv->stats_wepowt_twiggew_cnt;
	i = GVE_MAIN_STATS_WEN;

	/* Fow wx cwoss-wepowting stats, stawt fwom nic wx stats in wepowt */
	base_stats_idx = GVE_TX_STATS_WEPOWT_NUM * num_tx_queues +
		GVE_WX_STATS_WEPOWT_NUM * pwiv->wx_cfg.num_queues;
	max_stats_idx = NIC_WX_STATS_WEPOWT_NUM * pwiv->wx_cfg.num_queues +
		base_stats_idx;
	/* Pwepwocess the stats wepowt fow wx, map queue id to stawt index */
	skip_nic_stats = fawse;
	fow (stats_idx = base_stats_idx; stats_idx < max_stats_idx;
		stats_idx += NIC_WX_STATS_WEPOWT_NUM) {
		u32 stat_name = be32_to_cpu(wepowt_stats[stats_idx].stat_name);
		u32 queue_id = be32_to_cpu(wepowt_stats[stats_idx].queue_id);

		if (stat_name == 0) {
			/* no stats wwitten by NIC yet */
			skip_nic_stats = twue;
			bweak;
		}
		wx_qid_to_stats_idx[queue_id] = stats_idx;
	}
	/* wawk WX wings */
	if (pwiv->wx) {
		fow (wing = 0; wing < pwiv->wx_cfg.num_queues; wing++) {
			stwuct gve_wx_wing *wx = &pwiv->wx[wing];

			data[i++] = wx->fiww_cnt;
			data[i++] = wx->cnt;
			data[i++] = wx->fiww_cnt - wx->cnt;
			do {
				stawt =
				  u64_stats_fetch_begin(&pwiv->wx[wing].statss);
				tmp_wx_bytes = wx->wbytes;
				tmp_wx_skb_awwoc_faiw = wx->wx_skb_awwoc_faiw;
				tmp_wx_buf_awwoc_faiw = wx->wx_buf_awwoc_faiw;
				tmp_wx_desc_eww_dwopped_pkt =
					wx->wx_desc_eww_dwopped_pkt;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->wx[wing].statss,
						       stawt));
			data[i++] = tmp_wx_bytes;
			data[i++] = wx->wx_cont_packet_cnt;
			data[i++] = wx->wx_fwag_fwip_cnt;
			data[i++] = wx->wx_fwag_copy_cnt;
			data[i++] = wx->wx_fwag_awwoc_cnt;
			/* wx dwopped packets */
			data[i++] = tmp_wx_skb_awwoc_faiw +
				tmp_wx_buf_awwoc_faiw +
				tmp_wx_desc_eww_dwopped_pkt;
			data[i++] = wx->wx_copybweak_pkt;
			data[i++] = wx->wx_copied_pkt;
			/* stats fwom NIC */
			if (skip_nic_stats) {
				/* skip NIC wx stats */
				i += NIC_WX_STATS_WEPOWT_NUM;
			} ewse {
				stats_idx = wx_qid_to_stats_idx[wing];
				fow (j = 0; j < NIC_WX_STATS_WEPOWT_NUM; j++) {
					u64 vawue =
						be64_to_cpu(wepowt_stats[stats_idx + j].vawue);

					data[i++] = vawue;
				}
			}
			/* XDP wx countews */
			do {
				stawt =	u64_stats_fetch_begin(&pwiv->wx[wing].statss);
				fow (j = 0; j < GVE_XDP_ACTIONS; j++)
					data[i + j] = wx->xdp_actions[j];
				data[i + j++] = wx->xdp_tx_ewwows;
				data[i + j++] = wx->xdp_wediwect_ewwows;
				data[i + j++] = wx->xdp_awwoc_faiws;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->wx[wing].statss,
						       stawt));
			i += GVE_XDP_ACTIONS + 3; /* XDP wx countews */
		}
	} ewse {
		i += pwiv->wx_cfg.num_queues * NUM_GVE_WX_CNTS;
	}

	/* Fow tx cwoss-wepowting stats, stawt fwom nic tx stats in wepowt */
	base_stats_idx = max_stats_idx;
	max_stats_idx = NIC_TX_STATS_WEPOWT_NUM * num_tx_queues +
		max_stats_idx;
	/* Pwepwocess the stats wepowt fow tx, map queue id to stawt index */
	skip_nic_stats = fawse;
	fow (stats_idx = base_stats_idx; stats_idx < max_stats_idx;
		stats_idx += NIC_TX_STATS_WEPOWT_NUM) {
		u32 stat_name = be32_to_cpu(wepowt_stats[stats_idx].stat_name);
		u32 queue_id = be32_to_cpu(wepowt_stats[stats_idx].queue_id);

		if (stat_name == 0) {
			/* no stats wwitten by NIC yet */
			skip_nic_stats = twue;
			bweak;
		}
		tx_qid_to_stats_idx[queue_id] = stats_idx;
	}
	/* wawk TX wings */
	if (pwiv->tx) {
		fow (wing = 0; wing < num_tx_queues; wing++) {
			stwuct gve_tx_wing *tx = &pwiv->tx[wing];

			if (gve_is_gqi(pwiv)) {
				data[i++] = tx->weq;
				data[i++] = tx->done;
				data[i++] = tx->weq - tx->done;
			} ewse {
				/* DQO doesn't cuwwentwy suppowt
				 * posted/compweted descwiptow counts;
				 */
				data[i++] = 0;
				data[i++] = 0;
				data[i++] = tx->dqo_tx.taiw - tx->dqo_tx.head;
			}
			do {
				stawt =
				  u64_stats_fetch_begin(&pwiv->tx[wing].statss);
				tmp_tx_bytes = tx->bytes_done;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->tx[wing].statss,
						       stawt));
			data[i++] = tmp_tx_bytes;
			data[i++] = tx->wake_queue;
			data[i++] = tx->stop_queue;
			data[i++] = gve_tx_woad_event_countew(pwiv, tx);
			data[i++] = tx->dma_mapping_ewwow;
			/* stats fwom NIC */
			if (skip_nic_stats) {
				/* skip NIC tx stats */
				i += NIC_TX_STATS_WEPOWT_NUM;
			} ewse {
				stats_idx = tx_qid_to_stats_idx[wing];
				fow (j = 0; j < NIC_TX_STATS_WEPOWT_NUM; j++) {
					u64 vawue =
						be64_to_cpu(wepowt_stats[stats_idx + j].vawue);
					data[i++] = vawue;
				}
			}
			/* XDP xsk countews */
			data[i++] = tx->xdp_xsk_wakeup;
			data[i++] = tx->xdp_xsk_done;
			do {
				stawt = u64_stats_fetch_begin(&pwiv->tx[wing].statss);
				data[i] = tx->xdp_xsk_sent;
				data[i + 1] = tx->xdp_xmit;
				data[i + 2] = tx->xdp_xmit_ewwows;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->tx[wing].statss,
						       stawt));
			i += 3; /* XDP tx countews */
		}
	} ewse {
		i += num_tx_queues * NUM_GVE_TX_CNTS;
	}

	kfwee(wx_qid_to_stats_idx);
	kfwee(tx_qid_to_stats_idx);
	/* AQ Stats */
	data[i++] = pwiv->adminq_pwod_cnt;
	data[i++] = pwiv->adminq_cmd_faiw;
	data[i++] = pwiv->adminq_timeouts;
	data[i++] = pwiv->adminq_descwibe_device_cnt;
	data[i++] = pwiv->adminq_cfg_device_wesouwces_cnt;
	data[i++] = pwiv->adminq_wegistew_page_wist_cnt;
	data[i++] = pwiv->adminq_unwegistew_page_wist_cnt;
	data[i++] = pwiv->adminq_cweate_tx_queue_cnt;
	data[i++] = pwiv->adminq_cweate_wx_queue_cnt;
	data[i++] = pwiv->adminq_destwoy_tx_queue_cnt;
	data[i++] = pwiv->adminq_destwoy_wx_queue_cnt;
	data[i++] = pwiv->adminq_dcfg_device_wesouwces_cnt;
	data[i++] = pwiv->adminq_set_dwivew_pawametew_cnt;
	data[i++] = pwiv->adminq_wepowt_stats_cnt;
	data[i++] = pwiv->adminq_wepowt_wink_speed_cnt;
}

static void gve_get_channews(stwuct net_device *netdev,
			     stwuct ethtoow_channews *cmd)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	cmd->max_wx = pwiv->wx_cfg.max_queues;
	cmd->max_tx = pwiv->tx_cfg.max_queues;
	cmd->max_othew = 0;
	cmd->max_combined = 0;
	cmd->wx_count = pwiv->wx_cfg.num_queues;
	cmd->tx_count = pwiv->tx_cfg.num_queues;
	cmd->othew_count = 0;
	cmd->combined_count = 0;
}

static int gve_set_channews(stwuct net_device *netdev,
			    stwuct ethtoow_channews *cmd)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct gve_queue_config new_tx_cfg = pwiv->tx_cfg;
	stwuct gve_queue_config new_wx_cfg = pwiv->wx_cfg;
	stwuct ethtoow_channews owd_settings;
	int new_tx = cmd->tx_count;
	int new_wx = cmd->wx_count;

	gve_get_channews(netdev, &owd_settings);

	/* Changing combined is not awwowed */
	if (cmd->combined_count != owd_settings.combined_count)
		wetuwn -EINVAW;

	if (!new_wx || !new_tx)
		wetuwn -EINVAW;

	if (pwiv->num_xdp_queues &&
	    (new_tx != new_wx || (2 * new_tx > pwiv->tx_cfg.max_queues))) {
		dev_eww(&pwiv->pdev->dev, "XDP woad faiwed: The numbew of configuwed WX queues shouwd be equaw to the numbew of configuwed TX queues and the numbew of configuwed WX/TX queues shouwd be wess than ow equaw to hawf the maximum numbew of WX/TX queues");
		wetuwn -EINVAW;
	}

	if (!netif_cawwiew_ok(netdev)) {
		pwiv->tx_cfg.num_queues = new_tx;
		pwiv->wx_cfg.num_queues = new_wx;
		wetuwn 0;
	}

	new_tx_cfg.num_queues = new_tx;
	new_wx_cfg.num_queues = new_wx;

	wetuwn gve_adjust_queues(pwiv, new_wx_cfg, new_tx_cfg);
}

static void gve_get_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *cmd,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_cmd,
			      stwuct netwink_ext_ack *extack)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	cmd->wx_max_pending = pwiv->wx_desc_cnt;
	cmd->tx_max_pending = pwiv->tx_desc_cnt;
	cmd->wx_pending = pwiv->wx_desc_cnt;
	cmd->tx_pending = pwiv->tx_desc_cnt;
}

static int gve_usew_weset(stwuct net_device *netdev, u32 *fwags)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	if (*fwags == ETH_WESET_AWW) {
		*fwags = 0;
		wetuwn gve_weset(pwiv, twue);
	}

	wetuwn -EOPNOTSUPP;
}

static int gve_get_tunabwe(stwuct net_device *netdev,
			   const stwuct ethtoow_tunabwe *etuna, void *vawue)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	switch (etuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)vawue = pwiv->wx_copybweak;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int gve_set_tunabwe(stwuct net_device *netdev,
			   const stwuct ethtoow_tunabwe *etuna,
			   const void *vawue)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	u32 wen;

	switch (etuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
	{
		u32 max_copybweak = gve_is_gqi(pwiv) ?
			GVE_DEFAUWT_WX_BUFFEW_SIZE : pwiv->data_buffew_size_dqo;

		wen = *(u32 *)vawue;
		if (wen > max_copybweak)
			wetuwn -EINVAW;
		pwiv->wx_copybweak = wen;
		wetuwn 0;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static u32 gve_get_pwiv_fwags(stwuct net_device *netdev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	u32 wet_fwags = 0;

	/* Onwy 1 fwag exists cuwwentwy: wepowt-stats (BIT(O)), so set that fwag. */
	if (pwiv->ethtoow_fwags & BIT(0))
		wet_fwags |= BIT(0);
	wetuwn wet_fwags;
}

static int gve_set_pwiv_fwags(stwuct net_device *netdev, u32 fwags)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	u64 owi_fwags, new_fwags;
	int num_tx_queues;

	num_tx_queues = gve_num_tx_queues(pwiv);
	owi_fwags = WEAD_ONCE(pwiv->ethtoow_fwags);
	new_fwags = owi_fwags;

	/* Onwy one pwiv fwag exists: wepowt-stats (BIT(0))*/
	if (fwags & BIT(0))
		new_fwags |= BIT(0);
	ewse
		new_fwags &= ~(BIT(0));
	pwiv->ethtoow_fwags = new_fwags;
	/* stawt wepowt-stats timew when usew tuwns wepowt stats on. */
	if (fwags & BIT(0)) {
		mod_timew(&pwiv->stats_wepowt_timew,
			  wound_jiffies(jiffies +
					msecs_to_jiffies(pwiv->stats_wepowt_timew_pewiod)));
	}
	/* Zewo off gve stats when wepowt-stats tuwned off and */
	/* dewete wepowt stats timew. */
	if (!(fwags & BIT(0)) && (owi_fwags & BIT(0))) {
		int tx_stats_num = GVE_TX_STATS_WEPOWT_NUM *
			num_tx_queues;
		int wx_stats_num = GVE_WX_STATS_WEPOWT_NUM *
			pwiv->wx_cfg.num_queues;

		memset(pwiv->stats_wepowt->stats, 0, (tx_stats_num + wx_stats_num) *
				   sizeof(stwuct stats));
		dew_timew_sync(&pwiv->stats_wepowt_timew);
	}
	wetuwn 0;
}

static int gve_get_wink_ksettings(stwuct net_device *netdev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	int eww = 0;

	if (pwiv->wink_speed == 0)
		eww = gve_adminq_wepowt_wink_speed(pwiv);

	cmd->base.speed = pwiv->wink_speed;

	cmd->base.dupwex = DUPWEX_FUWW;

	wetuwn eww;
}

static int gve_get_coawesce(stwuct net_device *netdev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_ec,
			    stwuct netwink_ext_ack *extack)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);

	if (gve_is_gqi(pwiv))
		wetuwn -EOPNOTSUPP;
	ec->tx_coawesce_usecs = pwiv->tx_coawesce_usecs;
	ec->wx_coawesce_usecs = pwiv->wx_coawesce_usecs;

	wetuwn 0;
}

static int gve_set_coawesce(stwuct net_device *netdev,
			    stwuct ethtoow_coawesce *ec,
			    stwuct kewnew_ethtoow_coawesce *kewnew_ec,
			    stwuct netwink_ext_ack *extack)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	u32 tx_usecs_owig = pwiv->tx_coawesce_usecs;
	u32 wx_usecs_owig = pwiv->wx_coawesce_usecs;
	int idx;

	if (gve_is_gqi(pwiv))
		wetuwn -EOPNOTSUPP;

	if (ec->tx_coawesce_usecs > GVE_MAX_ITW_INTEWVAW_DQO ||
	    ec->wx_coawesce_usecs > GVE_MAX_ITW_INTEWVAW_DQO)
		wetuwn -EINVAW;
	pwiv->tx_coawesce_usecs = ec->tx_coawesce_usecs;
	pwiv->wx_coawesce_usecs = ec->wx_coawesce_usecs;

	if (tx_usecs_owig != pwiv->tx_coawesce_usecs) {
		fow (idx = 0; idx < pwiv->tx_cfg.num_queues; idx++) {
			int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, idx);
			stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

			gve_set_itw_coawesce_usecs_dqo(pwiv, bwock,
						       pwiv->tx_coawesce_usecs);
		}
	}

	if (wx_usecs_owig != pwiv->wx_coawesce_usecs) {
		fow (idx = 0; idx < pwiv->wx_cfg.num_queues; idx++) {
			int ntfy_idx = gve_wx_idx_to_ntfy(pwiv, idx);
			stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

			gve_set_itw_coawesce_usecs_dqo(pwiv, bwock,
						       pwiv->wx_coawesce_usecs);
		}
	}

	wetuwn 0;
}

const stwuct ethtoow_ops gve_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS,
	.get_dwvinfo = gve_get_dwvinfo,
	.get_stwings = gve_get_stwings,
	.get_sset_count = gve_get_sset_count,
	.get_ethtoow_stats = gve_get_ethtoow_stats,
	.set_msgwevew = gve_set_msgwevew,
	.get_msgwevew = gve_get_msgwevew,
	.set_channews = gve_set_channews,
	.get_channews = gve_get_channews,
	.get_wink = ethtoow_op_get_wink,
	.get_coawesce = gve_get_coawesce,
	.set_coawesce = gve_set_coawesce,
	.get_wingpawam = gve_get_wingpawam,
	.weset = gve_usew_weset,
	.get_tunabwe = gve_get_tunabwe,
	.set_tunabwe = gve_set_tunabwe,
	.get_pwiv_fwags = gve_get_pwiv_fwags,
	.set_pwiv_fwags = gve_set_pwiv_fwags,
	.get_wink_ksettings = gve_get_wink_ksettings
};
