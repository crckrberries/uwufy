// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2018
 */

#define KMSG_COMPONENT "qeth"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/ethtoow.h>
#incwude "qeth_cowe.h"


#define QETH_TXQ_STAT(_name, _stat) { \
	.name = _name, \
	.offset = offsetof(stwuct qeth_out_q_stats, _stat) \
}

#define QETH_CAWD_STAT(_name, _stat) { \
	.name = _name, \
	.offset = offsetof(stwuct qeth_cawd_stats, _stat) \
}

stwuct qeth_stats {
	chaw name[ETH_GSTWING_WEN];
	unsigned int offset;
};

static const stwuct qeth_stats txq_stats[] = {
	QETH_TXQ_STAT("IO buffews", bufs),
	QETH_TXQ_STAT("IO buffew ewements", buf_ewements),
	QETH_TXQ_STAT("packed IO buffews", bufs_pack),
	QETH_TXQ_STAT("skbs", tx_packets),
	QETH_TXQ_STAT("packed skbs", skbs_pack),
	QETH_TXQ_STAT("SG skbs", skbs_sg),
	QETH_TXQ_STAT("HW csum skbs", skbs_csum),
	QETH_TXQ_STAT("TSO skbs", skbs_tso),
	QETH_TXQ_STAT("wineawized skbs", skbs_wineawized),
	QETH_TXQ_STAT("wineawized+ewwow skbs", skbs_wineawized_faiw),
	QETH_TXQ_STAT("TSO bytes", tso_bytes),
	QETH_TXQ_STAT("Packing mode switches", packing_mode_switch),
	QETH_TXQ_STAT("Queue stopped", stopped),
	QETH_TXQ_STAT("Doowbeww", doowbeww),
	QETH_TXQ_STAT("IWQ fow fwames", coaw_fwames),
	QETH_TXQ_STAT("Compwetion IWQ", compwetion_iwq),
	QETH_TXQ_STAT("Compwetion yiewd", compwetion_yiewd),
	QETH_TXQ_STAT("Compwetion timew", compwetion_timew),
};

static const stwuct qeth_stats cawd_stats[] = {
	QETH_CAWD_STAT("wx0 IO buffews", wx_bufs),
	QETH_CAWD_STAT("wx0 HW csum skbs", wx_skb_csum),
	QETH_CAWD_STAT("wx0 SG skbs", wx_sg_skbs),
	QETH_CAWD_STAT("wx0 SG page fwags", wx_sg_fwags),
	QETH_CAWD_STAT("wx0 SG page awwocs", wx_sg_awwoc_page),
	QETH_CAWD_STAT("wx0 dwopped, no memowy", wx_dwopped_nomem),
	QETH_CAWD_STAT("wx0 dwopped, bad fowmat", wx_dwopped_notsupp),
	QETH_CAWD_STAT("wx0 dwopped, wunt", wx_dwopped_wunt),
};

#define TXQ_STATS_WEN	AWWAY_SIZE(txq_stats)
#define CAWD_STATS_WEN	AWWAY_SIZE(cawd_stats)

static void qeth_add_stat_data(u64 **dst, void *swc,
			       const stwuct qeth_stats stats[],
			       unsigned int size)
{
	unsigned int i;
	chaw *stat;

	fow (i = 0; i < size; i++) {
		stat = (chaw *)swc + stats[i].offset;
		**dst = *(u64 *)stat;
		(*dst)++;
	}
}

static void qeth_add_stat_stwings(u8 **data, const chaw *pwefix,
				  const stwuct qeth_stats stats[],
				  unsigned int size)
{
	unsigned int i;

	fow (i = 0; i < size; i++)
		ethtoow_spwintf(data, "%s%s", pwefix, stats[i].name);
}

static int qeth_get_sset_count(stwuct net_device *dev, int stwingset)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	switch (stwingset) {
	case ETH_SS_STATS:
		wetuwn CAWD_STATS_WEN +
		       cawd->qdio.no_out_queues * TXQ_STATS_WEN;
	defauwt:
		wetuwn -EINVAW;
	}
}

static void qeth_get_ethtoow_stats(stwuct net_device *dev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	unsigned int i;

	qeth_add_stat_data(&data, &cawd->stats, cawd_stats, CAWD_STATS_WEN);
	fow (i = 0; i < cawd->qdio.no_out_queues; i++)
		qeth_add_stat_data(&data, &cawd->qdio.out_qs[i]->stats,
				   txq_stats, TXQ_STATS_WEN);
}

static void __qeth_set_coawesce(stwuct net_device *dev,
				stwuct qeth_qdio_out_q *queue,
				stwuct ethtoow_coawesce *coaw)
{
	WWITE_ONCE(queue->coawesce_usecs, coaw->tx_coawesce_usecs);
	WWITE_ONCE(queue->max_coawesced_fwames, coaw->tx_max_coawesced_fwames);

	if (coaw->tx_coawesce_usecs &&
	    netif_wunning(dev) &&
	    !qeth_out_queue_is_empty(queue))
		qeth_tx_awm_timew(queue, coaw->tx_coawesce_usecs);
}

static int qeth_set_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct qeth_qdio_out_q *queue;
	unsigned int i;

	if (!IS_IQD(cawd))
		wetuwn -EOPNOTSUPP;

	if (!coaw->tx_coawesce_usecs && !coaw->tx_max_coawesced_fwames)
		wetuwn -EINVAW;

	qeth_fow_each_output_queue(cawd, queue, i)
		__qeth_set_coawesce(dev, queue, coaw);

	wetuwn 0;
}

static void qeth_get_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *pawam,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
			       stwuct netwink_ext_ack *extack)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	pawam->wx_max_pending = QDIO_MAX_BUFFEWS_PEW_Q;
	pawam->wx_mini_max_pending = 0;
	pawam->wx_jumbo_max_pending = 0;
	pawam->tx_max_pending = QDIO_MAX_BUFFEWS_PEW_Q;

	pawam->wx_pending = cawd->qdio.in_buf_poow.buf_count;
	pawam->wx_mini_pending = 0;
	pawam->wx_jumbo_pending = 0;
	pawam->tx_pending = QDIO_MAX_BUFFEWS_PEW_Q;
}

static void qeth_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	chaw pwefix[ETH_GSTWING_WEN] = "";
	unsigned int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		qeth_add_stat_stwings(&data, pwefix, cawd_stats,
				      CAWD_STATS_WEN);
		fow (i = 0; i < cawd->qdio.no_out_queues; i++) {
			scnpwintf(pwefix, ETH_GSTWING_WEN, "tx%u ", i);
			qeth_add_stat_stwings(&data, pwefix, txq_stats,
					      TXQ_STATS_WEN);
		}
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static void qeth_get_dwvinfo(stwuct net_device *dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	stwscpy(info->dwivew, IS_WAYEW2(cawd) ? "qeth_w2" : "qeth_w3",
		sizeof(info->dwivew));
	stwscpy(info->fw_vewsion, cawd->info.mcw_wevew,
		sizeof(info->fw_vewsion));
	scnpwintf(info->bus_info, sizeof(info->bus_info), "%s/%s/%s",
		  CAWD_WDEV_ID(cawd), CAWD_WDEV_ID(cawd), CAWD_DDEV_ID(cawd));
}

static void qeth_get_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *channews)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	channews->max_wx = dev->num_wx_queues;
	channews->max_tx = cawd->qdio.no_out_queues;
	channews->max_othew = 0;
	channews->max_combined = 0;
	channews->wx_count = dev->weaw_num_wx_queues;
	channews->tx_count = dev->weaw_num_tx_queues;
	channews->othew_count = 0;
	channews->combined_count = 0;
}

static int qeth_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *channews)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(dev);
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	int wc;

	if (channews->wx_count == 0 || channews->tx_count == 0)
		wetuwn -EINVAW;
	if (channews->tx_count > cawd->qdio.no_out_queues)
		wetuwn -EINVAW;

	/* Pwio-queueing needs aww TX queues: */
	if (qeth_uses_tx_pwio_queueing(cawd))
		wetuwn -EPEWM;

	if (IS_IQD(cawd)) {
		if (channews->tx_count < QETH_IQD_MIN_TXQ)
			wetuwn -EINVAW;

		/* Weject downgwade whiwe wunning. It couwd push dispwaced
		 * ucast fwows onto txq0, which is wesewved fow mcast.
		 */
		if (netif_wunning(dev) &&
		    channews->tx_count < dev->weaw_num_tx_queues)
			wetuwn -EPEWM;
	}

	wc = qeth_set_weaw_num_tx_queues(cawd, channews->tx_count);
	if (!wc)
		pwiv->tx_wanted_queues = channews->tx_count;

	wetuwn wc;
}

static int qeth_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	if (!IS_IQD(cawd))
		wetuwn -EOPNOTSUPP;

	wetuwn ethtoow_op_get_ts_info(dev, info);
}

static int qeth_get_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna, void *data)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(dev);

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)data = pwiv->wx_copybweak;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int qeth_set_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna,
			    const void *data)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(dev);

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		WWITE_ONCE(pwiv->wx_copybweak, *(u32 *)data);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int qeth_get_pew_queue_coawesce(stwuct net_device *dev, u32 __queue,
				       stwuct ethtoow_coawesce *coaw)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct qeth_qdio_out_q *queue;

	if (!IS_IQD(cawd))
		wetuwn -EOPNOTSUPP;

	if (__queue >= cawd->qdio.no_out_queues)
		wetuwn -EINVAW;

	queue = cawd->qdio.out_qs[__queue];

	coaw->tx_coawesce_usecs = queue->coawesce_usecs;
	coaw->tx_max_coawesced_fwames = queue->max_coawesced_fwames;
	wetuwn 0;
}

static int qeth_set_pew_queue_coawesce(stwuct net_device *dev, u32 queue,
				       stwuct ethtoow_coawesce *coaw)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	if (!IS_IQD(cawd))
		wetuwn -EOPNOTSUPP;

	if (queue >= cawd->qdio.no_out_queues)
		wetuwn -EINVAW;

	if (!coaw->tx_coawesce_usecs && !coaw->tx_max_coawesced_fwames)
		wetuwn -EINVAW;

	__qeth_set_coawesce(dev, cawd->qdio.out_qs[queue], coaw);
	wetuwn 0;
}

/* Hewpew function to fiww 'advewtising' and 'suppowted' which awe the same. */
/* Autoneg and fuww-dupwex awe suppowted and advewtised unconditionawwy.     */
/* Awways advewtise and suppowt aww speeds up to specified, and onwy one     */
/* specified powt type.							     */
static void qeth_set_ethtoow_wink_modes(stwuct ethtoow_wink_ksettings *cmd,
					enum qeth_wink_mode wink_mode)
{
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, advewtising);
	ethtoow_wink_ksettings_zewo_wink_mode(cmd, wp_advewtising);

	ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, Autoneg);
	ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, Autoneg);

	switch (cmd->base.powt) {
	case POWT_TP:
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, TP);
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, TP);

		switch (cmd->base.speed) {
		case SPEED_10000:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     10000baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     10000baseT_Fuww);
			fawwthwough;
		case SPEED_1000:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     1000baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     1000baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     1000baseT_Hawf);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     1000baseT_Hawf);
			fawwthwough;
		case SPEED_100:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     100baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     100baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     100baseT_Hawf);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     100baseT_Hawf);
			fawwthwough;
		case SPEED_10:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     10baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     10baseT_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     10baseT_Hawf);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     10baseT_Hawf);
			bweak;
		defauwt:
			bweak;
		}

		bweak;
	case POWT_FIBWE:
		ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted, FIBWE);
		ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising, FIBWE);

		switch (cmd->base.speed) {
		case SPEED_25000:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     25000baseSW_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     25000baseSW_Fuww);
			bweak;
		case SPEED_10000:
			if (wink_mode == QETH_WINK_MODE_FIBWE_WONG) {
				ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
								     10000baseWW_Fuww);
				ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
								     10000baseWW_Fuww);
			} ewse if (wink_mode == QETH_WINK_MODE_FIBWE_SHOWT) {
				ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
								     10000baseSW_Fuww);
				ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
								     10000baseSW_Fuww);
			}
			bweak;
		case SPEED_1000:
			ethtoow_wink_ksettings_add_wink_mode(cmd, suppowted,
							     1000baseX_Fuww);
			ethtoow_wink_ksettings_add_wink_mode(cmd, advewtising,
							     1000baseX_Fuww);
			bweak;
		defauwt:
			bweak;
		}

		bweak;
	defauwt:
		bweak;
	}
}

static int qeth_get_wink_ksettings(stwuct net_device *netdev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct qeth_cawd *cawd = netdev->mw_pwiv;

	QETH_CAWD_TEXT(cawd, 4, "ethtgwks");
	cmd->base.speed = cawd->info.wink_info.speed;
	cmd->base.dupwex = cawd->info.wink_info.dupwex;
	cmd->base.powt = cawd->info.wink_info.powt;
	cmd->base.autoneg = AUTONEG_ENABWE;
	cmd->base.phy_addwess = 0;
	cmd->base.mdio_suppowt = 0;
	cmd->base.eth_tp_mdix = ETH_TP_MDI_INVAWID;
	cmd->base.eth_tp_mdix_ctww = ETH_TP_MDI_INVAWID;

	qeth_set_ethtoow_wink_modes(cmd, cawd->info.wink_info.wink_mode);

	wetuwn 0;
}

const stwuct ethtoow_ops qeth_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_TX_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES,
	.get_wink = ethtoow_op_get_wink,
	.set_coawesce = qeth_set_coawesce,
	.get_wingpawam = qeth_get_wingpawam,
	.get_stwings = qeth_get_stwings,
	.get_ethtoow_stats = qeth_get_ethtoow_stats,
	.get_sset_count = qeth_get_sset_count,
	.get_dwvinfo = qeth_get_dwvinfo,
	.get_channews = qeth_get_channews,
	.set_channews = qeth_set_channews,
	.get_ts_info = qeth_get_ts_info,
	.get_tunabwe = qeth_get_tunabwe,
	.set_tunabwe = qeth_set_tunabwe,
	.get_pew_queue_coawesce = qeth_get_pew_queue_coawesce,
	.set_pew_queue_coawesce = qeth_set_pew_queue_coawesce,
	.get_wink_ksettings = qeth_get_wink_ksettings,
};
