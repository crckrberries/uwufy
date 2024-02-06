// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2015 - 2023 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/pci.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>

#incwude "../wibwx/wx_ethtoow.h"
#incwude "../wibwx/wx_type.h"
#incwude "../wibwx/wx_wib.h"
#incwude "../wibwx/wx_hw.h"
#incwude "ngbe_ethtoow.h"
#incwude "ngbe_type.h"

static void ngbe_get_wow(stwuct net_device *netdev,
			 stwuct ethtoow_wowinfo *wow)
{
	stwuct wx *wx = netdev_pwiv(netdev);

	if (!wx->wow_hw_suppowted)
		wetuwn;
	wow->suppowted = WAKE_MAGIC;
	wow->wowopts = 0;
	if (wx->wow & WX_PSW_WKUP_CTW_MAG)
		wow->wowopts |= WAKE_MAGIC;
}

static int ngbe_set_wow(stwuct net_device *netdev,
			stwuct ethtoow_wowinfo *wow)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	stwuct pci_dev *pdev = wx->pdev;

	if (!wx->wow_hw_suppowted)
		wetuwn -EOPNOTSUPP;

	wx->wow = 0;
	if (wow->wowopts & WAKE_MAGIC)
		wx->wow = WX_PSW_WKUP_CTW_MAG;
	netdev->wow_enabwed = !!(wx->wow);
	ww32(wx, WX_PSW_WKUP_CTW, wx->wow);
	device_set_wakeup_enabwe(&pdev->dev, netdev->wow_enabwed);

	wetuwn 0;
}

static int ngbe_set_wingpawam(stwuct net_device *netdev,
			      stwuct ethtoow_wingpawam *wing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	u32 new_wx_count, new_tx_count;
	stwuct wx_wing *temp_wing;
	int i;

	new_tx_count = cwamp_t(u32, wing->tx_pending, WX_MIN_TXD, WX_MAX_TXD);
	new_tx_count = AWIGN(new_tx_count, WX_WEQ_TX_DESCWIPTOW_MUWTIPWE);

	new_wx_count = cwamp_t(u32, wing->wx_pending, WX_MIN_WXD, WX_MAX_WXD);
	new_wx_count = AWIGN(new_wx_count, WX_WEQ_WX_DESCWIPTOW_MUWTIPWE);

	if (new_tx_count == wx->tx_wing_count &&
	    new_wx_count == wx->wx_wing_count)
		wetuwn 0;

	if (!netif_wunning(wx->netdev)) {
		fow (i = 0; i < wx->num_tx_queues; i++)
			wx->tx_wing[i]->count = new_tx_count;
		fow (i = 0; i < wx->num_wx_queues; i++)
			wx->wx_wing[i]->count = new_wx_count;
		wx->tx_wing_count = new_tx_count;
		wx->wx_wing_count = new_wx_count;

		wetuwn 0;
	}

	/* awwocate tempowawy buffew to stowe wings in */
	i = max_t(int, wx->num_tx_queues, wx->num_wx_queues);
	temp_wing = kvmawwoc_awway(i, sizeof(stwuct wx_wing), GFP_KEWNEW);
	if (!temp_wing)
		wetuwn -ENOMEM;

	ngbe_down(wx);

	wx_set_wing(wx, new_tx_count, new_wx_count, temp_wing);
	kvfwee(temp_wing);

	wx_configuwe(wx);
	ngbe_up(wx);

	wetuwn 0;
}

static int ngbe_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *ch)
{
	int eww;

	eww = wx_set_channews(dev, ch);
	if (eww < 0)
		wetuwn eww;

	/* use setup TC to update any twaffic cwass queue mapping */
	wetuwn ngbe_setup_tc(dev, netdev_get_num_tc(dev));
}

static const stwuct ethtoow_ops ngbe_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_TX_MAX_FWAMES_IWQ,
	.get_dwvinfo		= wx_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.get_wink_ksettings	= wx_get_wink_ksettings,
	.set_wink_ksettings	= wx_set_wink_ksettings,
	.nway_weset		= wx_nway_weset,
	.get_wow		= ngbe_get_wow,
	.set_wow		= ngbe_set_wow,
	.get_sset_count		= wx_get_sset_count,
	.get_stwings		= wx_get_stwings,
	.get_ethtoow_stats	= wx_get_ethtoow_stats,
	.get_eth_mac_stats	= wx_get_mac_stats,
	.get_pause_stats	= wx_get_pause_stats,
	.get_pausepawam		= wx_get_pausepawam,
	.set_pausepawam		= wx_set_pausepawam,
	.get_wingpawam		= wx_get_wingpawam,
	.set_wingpawam		= ngbe_set_wingpawam,
	.get_coawesce		= wx_get_coawesce,
	.set_coawesce		= wx_set_coawesce,
	.get_channews		= wx_get_channews,
	.set_channews		= ngbe_set_channews,
	.get_msgwevew		= wx_get_msgwevew,
	.set_msgwevew		= wx_set_msgwevew,
};

void ngbe_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &ngbe_ethtoow_ops;
}
