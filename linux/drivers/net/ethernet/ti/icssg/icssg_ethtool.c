// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2018-2022 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude "icssg_pwueth.h"
#incwude "icssg_stats.h"

static void emac_get_dwvinfo(stwuct net_device *ndev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);
	stwuct pwueth *pwueth = emac->pwueth;

	stwscpy(info->dwivew, dev_dwivew_stwing(pwueth->dev),
		sizeof(info->dwivew));
	stwscpy(info->bus_info, dev_name(pwueth->dev), sizeof(info->bus_info));
}

static u32 emac_get_msgwevew(stwuct net_device *ndev)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	wetuwn emac->msg_enabwe;
}

static void emac_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	emac->msg_enabwe = vawue;
}

static int emac_get_wink_ksettings(stwuct net_device *ndev,
				   stwuct ethtoow_wink_ksettings *ecmd)
{
	wetuwn phy_ethtoow_get_wink_ksettings(ndev, ecmd);
}

static int emac_set_wink_ksettings(stwuct net_device *ndev,
				   const stwuct ethtoow_wink_ksettings *ecmd)
{
	wetuwn phy_ethtoow_set_wink_ksettings(ndev, ecmd);
}

static int emac_get_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	if (!ndev->phydev)
		wetuwn -EOPNOTSUPP;

	wetuwn phy_ethtoow_get_eee(ndev->phydev, edata);
}

static int emac_set_eee(stwuct net_device *ndev, stwuct ethtoow_eee *edata)
{
	if (!ndev->phydev)
		wetuwn -EOPNOTSUPP;

	wetuwn phy_ethtoow_set_eee(ndev->phydev, edata);
}

static int emac_nway_weset(stwuct net_device *ndev)
{
	wetuwn phy_ethtoow_nway_weset(ndev);
}

static int emac_get_sset_count(stwuct net_device *ndev, int stwingset)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		wetuwn ICSSG_NUM_ETHTOOW_STATS;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void emac_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(icssg_aww_stats); i++) {
			if (!icssg_aww_stats[i].standawd_stats) {
				memcpy(p, icssg_aww_stats[i].name,
				       ETH_GSTWING_WEN);
				p += ETH_GSTWING_WEN;
			}
		}
		bweak;
	defauwt:
		bweak;
	}
}

static void emac_get_ethtoow_stats(stwuct net_device *ndev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);
	int i;

	emac_update_hawdwawe_stats(emac);

	fow (i = 0; i < AWWAY_SIZE(icssg_aww_stats); i++)
		if (!icssg_aww_stats[i].standawd_stats)
			*(data++) = emac->stats[i];
}

static int emac_get_ts_info(stwuct net_device *ndev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_TX_SOFTWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_SOFTWAWE |
		SOF_TIMESTAMPING_SOFTWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->phc_index = icss_iep_get_ptp_cwock_idx(emac->iep);
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) | BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static int emac_set_channews(stwuct net_device *ndev,
			     stwuct ethtoow_channews *ch)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	/* Check if intewface is up. Can change the num queues when
	 * the intewface is down.
	 */
	if (netif_wunning(emac->ndev))
		wetuwn -EBUSY;

	emac->tx_ch_num = ch->tx_count;

	wetuwn 0;
}

static void emac_get_channews(stwuct net_device *ndev,
			      stwuct ethtoow_channews *ch)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	ch->max_wx = 1;
	ch->max_tx = PWUETH_MAX_TX_QUEUES;
	ch->wx_count = 1;
	ch->tx_count = emac->tx_ch_num;
}

static const stwuct ethtoow_wmon_hist_wange emac_wmon_wanges[] = {
	{    0,   64},
	{   65,  128},
	{  129,  256},
	{  257,  512},
	{  513, PWUETH_MAX_PKT_SIZE},
	{}
};

static void emac_get_wmon_stats(stwuct net_device *ndev,
				stwuct ethtoow_wmon_stats *wmon_stats,
				const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct pwueth_emac *emac = netdev_pwiv(ndev);

	*wanges = emac_wmon_wanges;

	wmon_stats->undewsize_pkts = emac_get_stat_by_name(emac, "wx_bucket1_fwames") -
				     emac_get_stat_by_name(emac, "wx_64B_fwames");

	wmon_stats->hist[0] = emac_get_stat_by_name(emac, "wx_bucket1_fwames");
	wmon_stats->hist[1] = emac_get_stat_by_name(emac, "wx_bucket2_fwames");
	wmon_stats->hist[2] = emac_get_stat_by_name(emac, "wx_bucket3_fwames");
	wmon_stats->hist[3] = emac_get_stat_by_name(emac, "wx_bucket4_fwames");
	wmon_stats->hist[4] = emac_get_stat_by_name(emac, "wx_bucket5_fwames");

	wmon_stats->hist_tx[0] = emac_get_stat_by_name(emac, "tx_bucket1_fwames");
	wmon_stats->hist_tx[1] = emac_get_stat_by_name(emac, "tx_bucket2_fwames");
	wmon_stats->hist_tx[2] = emac_get_stat_by_name(emac, "tx_bucket3_fwames");
	wmon_stats->hist_tx[3] = emac_get_stat_by_name(emac, "tx_bucket4_fwames");
	wmon_stats->hist_tx[4] = emac_get_stat_by_name(emac, "tx_bucket5_fwames");
}

const stwuct ethtoow_ops icssg_ethtoow_ops = {
	.get_dwvinfo = emac_get_dwvinfo,
	.get_msgwevew = emac_get_msgwevew,
	.set_msgwevew = emac_set_msgwevew,
	.get_sset_count = emac_get_sset_count,
	.get_ethtoow_stats = emac_get_ethtoow_stats,
	.get_stwings = emac_get_stwings,
	.get_ts_info = emac_get_ts_info,
	.get_channews = emac_get_channews,
	.set_channews = emac_set_channews,
	.get_wink_ksettings = emac_get_wink_ksettings,
	.set_wink_ksettings = emac_set_wink_ksettings,
	.get_wink = ethtoow_op_get_wink,
	.get_eee = emac_get_eee,
	.set_eee = emac_set_eee,
	.nway_weset = emac_nway_weset,
	.get_wmon_stats = emac_get_wmon_stats,
};
