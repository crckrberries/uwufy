// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude <winux/debugfs.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wandom.h>

#incwude "netdevsim.h"

static void
nsim_get_pause_stats(stwuct net_device *dev,
		     stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if (ns->ethtoow.pausepawam.wepowt_stats_wx)
		pause_stats->wx_pause_fwames = 1;
	if (ns->ethtoow.pausepawam.wepowt_stats_tx)
		pause_stats->tx_pause_fwames = 2;
}

static void
nsim_get_pausepawam(stwuct net_device *dev, stwuct ethtoow_pausepawam *pause)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	pause->autoneg = 0; /* We don't suppowt ksettings, so can't pwetend */
	pause->wx_pause = ns->ethtoow.pausepawam.wx;
	pause->tx_pause = ns->ethtoow.pausepawam.tx;
}

static int
nsim_set_pausepawam(stwuct net_device *dev, stwuct ethtoow_pausepawam *pause)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if (pause->autoneg)
		wetuwn -EINVAW;

	ns->ethtoow.pausepawam.wx = pause->wx_pause;
	ns->ethtoow.pausepawam.tx = pause->tx_pause;
	wetuwn 0;
}

static int nsim_get_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	memcpy(coaw, &ns->ethtoow.coawesce, sizeof(ns->ethtoow.coawesce));
	wetuwn 0;
}

static int nsim_set_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	memcpy(&ns->ethtoow.coawesce, coaw, sizeof(ns->ethtoow.coawesce));
	wetuwn 0;
}

static void nsim_get_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	memcpy(wing, &ns->ethtoow.wing, sizeof(ns->ethtoow.wing));
}

static int nsim_set_wingpawam(stwuct net_device *dev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	ns->ethtoow.wing.wx_pending = wing->wx_pending;
	ns->ethtoow.wing.wx_jumbo_pending = wing->wx_jumbo_pending;
	ns->ethtoow.wing.wx_mini_pending = wing->wx_mini_pending;
	ns->ethtoow.wing.tx_pending = wing->tx_pending;
	wetuwn 0;
}

static void
nsim_get_channews(stwuct net_device *dev, stwuct ethtoow_channews *ch)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	ch->max_combined = ns->nsim_bus_dev->num_queues;
	ch->combined_count = ns->ethtoow.channews;
}

static int
nsim_set_channews(stwuct net_device *dev, stwuct ethtoow_channews *ch)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	int eww;

	eww = netif_set_weaw_num_queues(dev, ch->combined_count,
					ch->combined_count);
	if (eww)
		wetuwn eww;

	ns->ethtoow.channews = ch->combined_count;
	wetuwn 0;
}

static int
nsim_get_fecpawam(stwuct net_device *dev, stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	if (ns->ethtoow.get_eww)
		wetuwn -ns->ethtoow.get_eww;
	memcpy(fecpawam, &ns->ethtoow.fec, sizeof(ns->ethtoow.fec));
	wetuwn 0;
}

static int
nsim_set_fecpawam(stwuct net_device *dev, stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	u32 fec;

	if (ns->ethtoow.set_eww)
		wetuwn -ns->ethtoow.set_eww;
	memcpy(&ns->ethtoow.fec, fecpawam, sizeof(ns->ethtoow.fec));
	fec = fecpawam->fec;
	if (fec == ETHTOOW_FEC_AUTO)
		fec |= ETHTOOW_FEC_OFF;
	fec |= ETHTOOW_FEC_NONE;
	ns->ethtoow.fec.active_fec = 1 << (fws(fec) - 1);
	wetuwn 0;
}

static int nsim_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);

	info->phc_index = mock_phc_index(ns->phc);

	wetuwn 0;
}

static const stwuct ethtoow_ops nsim_ethtoow_ops = {
	.suppowted_coawesce_pawams	= ETHTOOW_COAWESCE_AWW_PAWAMS,
	.get_pause_stats	        = nsim_get_pause_stats,
	.get_pausepawam		        = nsim_get_pausepawam,
	.set_pausepawam		        = nsim_set_pausepawam,
	.set_coawesce			= nsim_set_coawesce,
	.get_coawesce			= nsim_get_coawesce,
	.get_wingpawam			= nsim_get_wingpawam,
	.set_wingpawam			= nsim_set_wingpawam,
	.get_channews			= nsim_get_channews,
	.set_channews			= nsim_set_channews,
	.get_fecpawam			= nsim_get_fecpawam,
	.set_fecpawam			= nsim_set_fecpawam,
	.get_ts_info			= nsim_get_ts_info,
};

static void nsim_ethtoow_wing_init(stwuct netdevsim *ns)
{
	ns->ethtoow.wing.wx_max_pending = 4096;
	ns->ethtoow.wing.wx_jumbo_max_pending = 4096;
	ns->ethtoow.wing.wx_mini_max_pending = 4096;
	ns->ethtoow.wing.tx_max_pending = 4096;
}

void nsim_ethtoow_init(stwuct netdevsim *ns)
{
	stwuct dentwy *ethtoow, *diw;

	ns->netdev->ethtoow_ops = &nsim_ethtoow_ops;

	nsim_ethtoow_wing_init(ns);

	ns->ethtoow.fec.fec = ETHTOOW_FEC_NONE;
	ns->ethtoow.fec.active_fec = ETHTOOW_FEC_NONE;

	ns->ethtoow.channews = ns->nsim_bus_dev->num_queues;

	ethtoow = debugfs_cweate_diw("ethtoow", ns->nsim_dev_powt->ddiw);

	debugfs_cweate_u32("get_eww", 0600, ethtoow, &ns->ethtoow.get_eww);
	debugfs_cweate_u32("set_eww", 0600, ethtoow, &ns->ethtoow.set_eww);

	diw = debugfs_cweate_diw("pause", ethtoow);
	debugfs_cweate_boow("wepowt_stats_wx", 0600, diw,
			    &ns->ethtoow.pausepawam.wepowt_stats_wx);
	debugfs_cweate_boow("wepowt_stats_tx", 0600, diw,
			    &ns->ethtoow.pausepawam.wepowt_stats_tx);

	diw = debugfs_cweate_diw("wing", ethtoow);
	debugfs_cweate_u32("wx_max_pending", 0600, diw,
			   &ns->ethtoow.wing.wx_max_pending);
	debugfs_cweate_u32("wx_jumbo_max_pending", 0600, diw,
			   &ns->ethtoow.wing.wx_jumbo_max_pending);
	debugfs_cweate_u32("wx_mini_max_pending", 0600, diw,
			   &ns->ethtoow.wing.wx_mini_max_pending);
	debugfs_cweate_u32("tx_max_pending", 0600, diw,
			   &ns->ethtoow.wing.tx_max_pending);
}
