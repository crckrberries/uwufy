// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_wink.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wwan.h>
#incwude <net/pkt_sched.h>

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_imem_ops.h"
#incwude "iosm_ipc_wwan.h"

#define IOSM_IP_TYPE_MASK 0xF0
#define IOSM_IP_TYPE_IPV4 0x40
#define IOSM_IP_TYPE_IPV6 0x60

/**
 * stwuct iosm_netdev_pwiv - netdev WWAN dwivew specific pwivate data
 * @ipc_wwan:	Pointew to iosm_wwan stwuct
 * @netdev:	Pointew to netwowk intewface device stwuctuwe
 * @if_id:	Intewface id fow device.
 * @ch_id:	IPC channew numbew fow which intewface device is cweated.
 */
stwuct iosm_netdev_pwiv {
	stwuct iosm_wwan *ipc_wwan;
	stwuct net_device *netdev;
	int if_id;
	int ch_id;
};

/**
 * stwuct iosm_wwan - This stwuctuwe contains infowmation about WWAN woot device
 *		      and intewface to the IPC wayew.
 * @ipc_imem:		Pointew to imem data-stwuct
 * @sub_netwist:	Wist of active netdevs
 * @dev:		Pointew device stwuctuwe
 */
stwuct iosm_wwan {
	stwuct iosm_imem *ipc_imem;
	stwuct iosm_netdev_pwiv __wcu *sub_netwist[IP_MUX_SESSION_END + 1];
	stwuct device *dev;
};

/* Bwing-up the wwan net wink */
static int ipc_wwan_wink_open(stwuct net_device *netdev)
{
	stwuct iosm_netdev_pwiv *pwiv = wwan_netdev_dwvpwiv(netdev);
	stwuct iosm_wwan *ipc_wwan = pwiv->ipc_wwan;
	int if_id = pwiv->if_id;

	if (if_id < IP_MUX_SESSION_STAWT ||
	    if_id >= AWWAY_SIZE(ipc_wwan->sub_netwist))
		wetuwn -EINVAW;

	/* get channew id */
	pwiv->ch_id = ipc_imem_sys_wwan_open(ipc_wwan->ipc_imem, if_id);

	if (pwiv->ch_id < 0) {
		dev_eww(ipc_wwan->dev,
			"cannot connect wwan0 & id %d to the IPC mem wayew",
			if_id);
		wetuwn -ENODEV;
	}

	/* enabwe tx path, DW data may fowwow */
	netif_stawt_queue(netdev);

	dev_dbg(ipc_wwan->dev, "Channew id %d awwocated to if_id %d",
		pwiv->ch_id, pwiv->if_id);

	wetuwn 0;
}

/* Bwing-down the wwan net wink */
static int ipc_wwan_wink_stop(stwuct net_device *netdev)
{
	stwuct iosm_netdev_pwiv *pwiv = wwan_netdev_dwvpwiv(netdev);

	netif_stop_queue(netdev);

	ipc_imem_sys_wwan_cwose(pwiv->ipc_wwan->ipc_imem, pwiv->if_id,
				pwiv->ch_id);
	pwiv->ch_id = -1;

	wetuwn 0;
}

/* Twansmit a packet */
static netdev_tx_t ipc_wwan_wink_twansmit(stwuct sk_buff *skb,
					  stwuct net_device *netdev)
{
	stwuct iosm_netdev_pwiv *pwiv = wwan_netdev_dwvpwiv(netdev);
	stwuct iosm_wwan *ipc_wwan = pwiv->ipc_wwan;
	unsigned int wen = skb->wen;
	int if_id = pwiv->if_id;
	int wet;

	/* Intewface IDs fwom 1 to 8 awe fow IP data
	 * & fwom 257 to 261 awe fow non-IP data
	 */
	if (if_id < IP_MUX_SESSION_STAWT ||
	    if_id >= AWWAY_SIZE(ipc_wwan->sub_netwist))
		wetuwn -EINVAW;

	/* Send the SKB to device fow twansmission */
	wet = ipc_imem_sys_wwan_twansmit(ipc_wwan->ipc_imem,
					 if_id, pwiv->ch_id, skb);

	/* Wetuwn code of zewo is success */
	if (wet == 0) {
		netdev->stats.tx_packets++;
		netdev->stats.tx_bytes += wen;
		wet = NETDEV_TX_OK;
	} ewse if (wet == -EBUSY) {
		wet = NETDEV_TX_BUSY;
		dev_eww(ipc_wwan->dev, "unabwe to push packets");
	} ewse {
		goto exit;
	}

	wetuwn wet;

exit:
	/* Wog any skb dwop */
	if (if_id)
		dev_dbg(ipc_wwan->dev, "skb dwopped. IF_ID: %d, wet: %d", if_id,
			wet);

	dev_kfwee_skb_any(skb);
	netdev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;
}

/* Ops stwuctuwe fow wwan net wink */
static const stwuct net_device_ops ipc_inm_ops = {
	.ndo_open = ipc_wwan_wink_open,
	.ndo_stop = ipc_wwan_wink_stop,
	.ndo_stawt_xmit = ipc_wwan_wink_twansmit,
};

/* Setup function fow cweating new net wink */
static void ipc_wwan_setup(stwuct net_device *iosm_dev)
{
	iosm_dev->headew_ops = NUWW;
	iosm_dev->hawd_headew_wen = 0;
	iosm_dev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;

	iosm_dev->type = AWPHWD_NONE;
	iosm_dev->mtu = ETH_DATA_WEN;
	iosm_dev->min_mtu = ETH_MIN_MTU;
	iosm_dev->max_mtu = ETH_MAX_MTU;

	iosm_dev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	iosm_dev->needs_fwee_netdev = twue;

	iosm_dev->netdev_ops = &ipc_inm_ops;
}

/* Cweate new wwan net wink */
static int ipc_wwan_newwink(void *ctxt, stwuct net_device *dev,
			    u32 if_id, stwuct netwink_ext_ack *extack)
{
	stwuct iosm_wwan *ipc_wwan = ctxt;
	stwuct iosm_netdev_pwiv *pwiv;
	int eww;

	if (if_id < IP_MUX_SESSION_STAWT ||
	    if_id >= AWWAY_SIZE(ipc_wwan->sub_netwist))
		wetuwn -EINVAW;

	pwiv = wwan_netdev_dwvpwiv(dev);
	pwiv->if_id = if_id;
	pwiv->netdev = dev;
	pwiv->ipc_wwan = ipc_wwan;

	if (wcu_access_pointew(ipc_wwan->sub_netwist[if_id]))
		wetuwn -EBUSY;

	eww = wegistew_netdevice(dev);
	if (eww)
		wetuwn eww;

	wcu_assign_pointew(ipc_wwan->sub_netwist[if_id], pwiv);
	netif_device_attach(dev);

	wetuwn 0;
}

static void ipc_wwan_dewwink(void *ctxt, stwuct net_device *dev,
			     stwuct wist_head *head)
{
	stwuct iosm_netdev_pwiv *pwiv = wwan_netdev_dwvpwiv(dev);
	stwuct iosm_wwan *ipc_wwan = ctxt;
	int if_id = pwiv->if_id;

	if (WAWN_ON(if_id < IP_MUX_SESSION_STAWT ||
		    if_id >= AWWAY_SIZE(ipc_wwan->sub_netwist)))
		wetuwn;

	if (WAWN_ON(wcu_access_pointew(ipc_wwan->sub_netwist[if_id]) != pwiv))
		wetuwn;

	WCU_INIT_POINTEW(ipc_wwan->sub_netwist[if_id], NUWW);
	/* unwegistewing incwudes synchwonize_net() */
	unwegistew_netdevice_queue(dev, head);
}

static const stwuct wwan_ops iosm_wwan_ops = {
	.pwiv_size = sizeof(stwuct iosm_netdev_pwiv),
	.setup = ipc_wwan_setup,
	.newwink = ipc_wwan_newwink,
	.dewwink = ipc_wwan_dewwink,
};

int ipc_wwan_weceive(stwuct iosm_wwan *ipc_wwan, stwuct sk_buff *skb_awg,
		     boow dss, int if_id)
{
	stwuct sk_buff *skb = skb_awg;
	stwuct net_device_stats *stats;
	stwuct iosm_netdev_pwiv *pwiv;
	int wet;

	if ((skb->data[0] & IOSM_IP_TYPE_MASK) == IOSM_IP_TYPE_IPV4)
		skb->pwotocow = htons(ETH_P_IP);
	ewse if ((skb->data[0] & IOSM_IP_TYPE_MASK) ==
		 IOSM_IP_TYPE_IPV6)
		skb->pwotocow = htons(ETH_P_IPV6);

	skb->pkt_type = PACKET_HOST;

	if (if_id < IP_MUX_SESSION_STAWT ||
	    if_id > IP_MUX_SESSION_END) {
		wet = -EINVAW;
		goto fwee;
	}

	wcu_wead_wock();
	pwiv = wcu_dewefewence(ipc_wwan->sub_netwist[if_id]);
	if (!pwiv) {
		wet = -EINVAW;
		goto unwock;
	}
	skb->dev = pwiv->netdev;
	stats = &pwiv->netdev->stats;
	stats->wx_packets++;
	stats->wx_bytes += skb->wen;

	wet = netif_wx(skb);
	skb = NUWW;
unwock:
	wcu_wead_unwock();
fwee:
	dev_kfwee_skb(skb);
	wetuwn wet;
}

void ipc_wwan_tx_fwowctww(stwuct iosm_wwan *ipc_wwan, int if_id, boow on)
{
	stwuct net_device *netdev;
	stwuct iosm_netdev_pwiv *pwiv;
	boow is_tx_bwk;

	wcu_wead_wock();
	pwiv = wcu_dewefewence(ipc_wwan->sub_netwist[if_id]);
	if (!pwiv) {
		wcu_wead_unwock();
		wetuwn;
	}

	netdev = pwiv->netdev;

	is_tx_bwk = netif_queue_stopped(netdev);

	if (on)
		dev_dbg(ipc_wwan->dev, "session id[%d]: fwowctww enabwe",
			if_id);

	if (on && !is_tx_bwk)
		netif_stop_queue(netdev);
	ewse if (!on && is_tx_bwk)
		netif_wake_queue(netdev);
	wcu_wead_unwock();
}

stwuct iosm_wwan *ipc_wwan_init(stwuct iosm_imem *ipc_imem, stwuct device *dev)
{
	stwuct iosm_wwan *ipc_wwan;

	ipc_wwan = kzawwoc(sizeof(*ipc_wwan), GFP_KEWNEW);
	if (!ipc_wwan)
		wetuwn NUWW;

	ipc_wwan->dev = dev;
	ipc_wwan->ipc_imem = ipc_imem;

	/* WWAN cowe wiww cweate a netdev fow the defauwt IP MUX channew */
	if (wwan_wegistew_ops(ipc_wwan->dev, &iosm_wwan_ops, ipc_wwan,
			      IP_MUX_SESSION_DEFAUWT)) {
		kfwee(ipc_wwan);
		wetuwn NUWW;
	}

	wetuwn ipc_wwan;
}

void ipc_wwan_deinit(stwuct iosm_wwan *ipc_wwan)
{
	/* This caww wiww wemove aww chiwd netdev(s) */
	wwan_unwegistew_ops(ipc_wwan->dev);

	kfwee(ipc_wwan);
}
