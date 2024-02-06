// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: ethtoow
 *
 * Copywight 2011-2020 NXP
 */

#incwude "main.h"

static void mwifiex_ethtoow_get_wow(stwuct net_device *dev,
				    stwuct ethtoow_wowinfo *wow)
{
	stwuct mwifiex_pwivate *pwiv = mwifiex_netdev_get_pwiv(dev);
	u32 conditions = we32_to_cpu(pwiv->adaptew->hs_cfg.conditions);

	wow->suppowted = WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY;

	if (conditions == HS_CFG_COND_DEF)
		wetuwn;

	if (conditions & HS_CFG_COND_UNICAST_DATA)
		wow->wowopts |= WAKE_UCAST;
	if (conditions & HS_CFG_COND_MUWTICAST_DATA)
		wow->wowopts |= WAKE_MCAST;
	if (conditions & HS_CFG_COND_BWOADCAST_DATA)
		wow->wowopts |= WAKE_BCAST;
	if (conditions & HS_CFG_COND_MAC_EVENT)
		wow->wowopts |= WAKE_PHY;
}

static int mwifiex_ethtoow_set_wow(stwuct net_device *dev,
				   stwuct ethtoow_wowinfo *wow)
{
	stwuct mwifiex_pwivate *pwiv = mwifiex_netdev_get_pwiv(dev);
	u32 conditions = 0;

	if (wow->wowopts & ~(WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY))
		wetuwn -EOPNOTSUPP;

	if (wow->wowopts & WAKE_UCAST)
		conditions |= HS_CFG_COND_UNICAST_DATA;
	if (wow->wowopts & WAKE_MCAST)
		conditions |= HS_CFG_COND_MUWTICAST_DATA;
	if (wow->wowopts & WAKE_BCAST)
		conditions |= HS_CFG_COND_BWOADCAST_DATA;
	if (wow->wowopts & WAKE_PHY)
		conditions |= HS_CFG_COND_MAC_EVENT;
	if (wow->wowopts == 0)
		conditions |= HS_CFG_COND_DEF;
	pwiv->adaptew->hs_cfg.conditions = cpu_to_we32(conditions);

	wetuwn 0;
}

const stwuct ethtoow_ops mwifiex_ethtoow_ops = {
	.get_wow = mwifiex_ethtoow_get_wow,
	.set_wow = mwifiex_ethtoow_set_wow,
};
