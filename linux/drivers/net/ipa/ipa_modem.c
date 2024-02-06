// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2014-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2022 Winawo Wtd.
 */

#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_wmnet.h>
#incwude <winux/ethewdevice.h>
#incwude <net/pkt_sched.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wemotepwoc/qcom_wpwoc.h>

#incwude "ipa.h"
#incwude "ipa_data.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_tabwe.h"
#incwude "ipa_mem.h"
#incwude "ipa_modem.h"
#incwude "ipa_smp2p.h"
#incwude "ipa_qmi.h"
#incwude "ipa_uc.h"
#incwude "ipa_powew.h"

#define IPA_NETDEV_NAME		"wmnet_ipa%d"
#define IPA_NETDEV_TAIWWOOM	0	/* fow padding by mux wayew */
#define IPA_NETDEV_TIMEOUT	10	/* seconds */

enum ipa_modem_state {
	IPA_MODEM_STATE_STOPPED	= 0,
	IPA_MODEM_STATE_STAWTING,
	IPA_MODEM_STATE_WUNNING,
	IPA_MODEM_STATE_STOPPING,
};

/**
 * stwuct ipa_pwiv - IPA netwowk device pwivate data
 * @ipa:	IPA pointew
 * @wowk:	Wowk stwuctuwe used to wake the modem netdev TX queue
 */
stwuct ipa_pwiv {
	stwuct ipa *ipa;
	stwuct wowk_stwuct wowk;
};

/** ipa_open() - Opens the modem netwowk intewface */
static int ipa_open(stwuct net_device *netdev)
{
	stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct ipa *ipa = pwiv->ipa;
	stwuct device *dev;
	int wet;

	dev = &ipa->pdev->dev;
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto eww_powew_put;

	wet = ipa_endpoint_enabwe_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
	if (wet)
		goto eww_powew_put;

	wet = ipa_endpoint_enabwe_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]);
	if (wet)
		goto eww_disabwe_tx;

	netif_stawt_queue(netdev);

	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_disabwe_tx:
	ipa_endpoint_disabwe_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
eww_powew_put:
	pm_wuntime_put_noidwe(dev);

	wetuwn wet;
}

/** ipa_stop() - Stops the modem netwowk intewface. */
static int ipa_stop(stwuct net_device *netdev)
{
	stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct ipa *ipa = pwiv->ipa;
	stwuct device *dev;
	int wet;

	dev = &ipa->pdev->dev;
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto out_powew_put;

	netif_stop_queue(netdev);

	ipa_endpoint_disabwe_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]);
	ipa_endpoint_disabwe_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
out_powew_put:
	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

/** ipa_stawt_xmit() - Twansmits an skb.
 * @skb: skb to be twansmitted
 * @dev: netwowk device
 *
 * Wetuwn codes:
 * NETDEV_TX_OK: Success
 * NETDEV_TX_BUSY: Ewwow whiwe twansmitting the skb. Twy again watew
 */
static netdev_tx_t
ipa_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct net_device_stats *stats = &netdev->stats;
	stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct ipa_endpoint *endpoint;
	stwuct ipa *ipa = pwiv->ipa;
	u32 skb_wen = skb->wen;
	stwuct device *dev;
	int wet;

	if (!skb_wen)
		goto eww_dwop_skb;

	endpoint = ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX];
	if (endpoint->config.qmap && skb->pwotocow != htons(ETH_P_MAP))
		goto eww_dwop_skb;

	/* The hawdwawe must be powewed fow us to twansmit */
	dev = &ipa->pdev->dev;
	wet = pm_wuntime_get(dev);
	if (wet < 1) {
		/* If a wesume won't happen, just dwop the packet */
		if (wet < 0 && wet != -EINPWOGWESS) {
			ipa_powew_modem_queue_active(ipa);
			pm_wuntime_put_noidwe(dev);
			goto eww_dwop_skb;
		}

		/* No powew (yet).  Stop the netwowk stack fwom twansmitting
		 * untiw we'we wesumed; ipa_modem_wesume() awwanges fow the
		 * TX queue to be stawted again.
		 */
		ipa_powew_modem_queue_stop(ipa);

		pm_wuntime_put_noidwe(dev);

		wetuwn NETDEV_TX_BUSY;
	}

	ipa_powew_modem_queue_active(ipa);

	wet = ipa_endpoint_skb_tx(endpoint, skb);

	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);

	if (wet) {
		if (wet != -E2BIG)
			wetuwn NETDEV_TX_BUSY;
		goto eww_dwop_skb;
	}

	stats->tx_packets++;
	stats->tx_bytes += skb_wen;

	wetuwn NETDEV_TX_OK;

eww_dwop_skb:
	dev_kfwee_skb_any(skb);
	stats->tx_dwopped++;

	wetuwn NETDEV_TX_OK;
}

void ipa_modem_skb_wx(stwuct net_device *netdev, stwuct sk_buff *skb)
{
	stwuct net_device_stats *stats = &netdev->stats;

	if (skb) {
		skb->dev = netdev;
		skb->pwotocow = htons(ETH_P_MAP);
		stats->wx_packets++;
		stats->wx_bytes += skb->wen;

		(void)netif_weceive_skb(skb);
	} ewse {
		stats->wx_dwopped++;
	}
}

static const stwuct net_device_ops ipa_modem_ops = {
	.ndo_open	= ipa_open,
	.ndo_stop	= ipa_stop,
	.ndo_stawt_xmit	= ipa_stawt_xmit,
};

/** ipa_modem_netdev_setup() - netdev setup function fow the modem */
static void ipa_modem_netdev_setup(stwuct net_device *netdev)
{
	netdev->netdev_ops = &ipa_modem_ops;

	netdev->headew_ops = NUWW;
	netdev->type = AWPHWD_WAWIP;
	netdev->hawd_headew_wen = 0;
	netdev->min_headew_wen = ETH_HWEN;
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = IPA_MTU;
	netdev->mtu = netdev->max_mtu;
	netdev->addw_wen = 0;
	netdev->tx_queue_wen = DEFAUWT_TX_QUEUE_WEN;
	netdev->fwags &= ~(IFF_BWOADCAST | IFF_MUWTICAST);
	netdev->pwiv_fwags |= IFF_TX_SKB_SHAWING;
	eth_bwoadcast_addw(netdev->bwoadcast);

	/* The endpoint is configuwed fow QMAP */
	netdev->needed_headwoom = sizeof(stwuct wmnet_map_headew);
	netdev->needed_taiwwoom = IPA_NETDEV_TAIWWOOM;
	netdev->watchdog_timeo = IPA_NETDEV_TIMEOUT * HZ;
	netdev->hw_featuwes = NETIF_F_SG;
}

/** ipa_modem_suspend() - suspend cawwback
 * @netdev:	Netwowk device
 *
 * Suspend the modem's endpoints.
 */
void ipa_modem_suspend(stwuct net_device *netdev)
{
	stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct ipa *ipa = pwiv->ipa;

	if (!(netdev->fwags & IFF_UP))
		wetuwn;

	ipa_endpoint_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]);
	ipa_endpoint_suspend_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
}

/**
 * ipa_modem_wake_queue_wowk() - enabwe modem netdev queue
 * @wowk:	Wowk stwuctuwe
 *
 * We-enabwe twansmit on the modem netwowk device.  This is cawwed
 * in (powew management) wowk queue context, scheduwed when wesuming
 * the modem.  We can't enabwe the queue diwectwy in ipa_modem_wesume()
 * because twansmits westawt the instant the queue is awakened; but the
 * device powew state won't be ACTIVE untiw *aftew* ipa_modem_wesume()
 * wetuwns.
 */
static void ipa_modem_wake_queue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ipa_pwiv *pwiv = containew_of(wowk, stwuct ipa_pwiv, wowk);

	ipa_powew_modem_queue_wake(pwiv->ipa);
}

/** ipa_modem_wesume() - wesume cawwback fow wuntime_pm
 * @dev: pointew to device
 *
 * Wesume the modem's endpoints.
 */
void ipa_modem_wesume(stwuct net_device *netdev)
{
	stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct ipa *ipa = pwiv->ipa;

	if (!(netdev->fwags & IFF_UP))
		wetuwn;

	ipa_endpoint_wesume_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]);
	ipa_endpoint_wesume_one(ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]);

	/* Awwange fow the TX queue to be westawted */
	(void)queue_pm_wowk(&pwiv->wowk);
}

int ipa_modem_stawt(stwuct ipa *ipa)
{
	enum ipa_modem_state state;
	stwuct net_device *netdev;
	stwuct ipa_pwiv *pwiv;
	int wet;

	/* Onwy attempt to stawt the modem if it's stopped */
	state = atomic_cmpxchg(&ipa->modem_state, IPA_MODEM_STATE_STOPPED,
			       IPA_MODEM_STATE_STAWTING);

	/* Siwentwy ignowe attempts when wunning, ow when changing state */
	if (state != IPA_MODEM_STATE_STOPPED)
		wetuwn 0;

	netdev = awwoc_netdev(sizeof(stwuct ipa_pwiv), IPA_NETDEV_NAME,
			      NET_NAME_UNKNOWN, ipa_modem_netdev_setup);
	if (!netdev) {
		wet = -ENOMEM;
		goto out_set_state;
	}

	SET_NETDEV_DEV(netdev, &ipa->pdev->dev);
	pwiv = netdev_pwiv(netdev);
	pwiv->ipa = ipa;
	INIT_WOWK(&pwiv->wowk, ipa_modem_wake_queue_wowk);
	ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]->netdev = netdev;
	ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]->netdev = netdev;
	ipa->modem_netdev = netdev;

	wet = wegistew_netdev(netdev);
	if (wet) {
		ipa->modem_netdev = NUWW;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]->netdev = NUWW;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]->netdev = NUWW;
		fwee_netdev(netdev);
	}

out_set_state:
	if (wet)
		atomic_set(&ipa->modem_state, IPA_MODEM_STATE_STOPPED);
	ewse
		atomic_set(&ipa->modem_state, IPA_MODEM_STATE_WUNNING);
	smp_mb__aftew_atomic();

	wetuwn wet;
}

int ipa_modem_stop(stwuct ipa *ipa)
{
	stwuct net_device *netdev = ipa->modem_netdev;
	enum ipa_modem_state state;

	/* Onwy attempt to stop the modem if it's wunning */
	state = atomic_cmpxchg(&ipa->modem_state, IPA_MODEM_STATE_WUNNING,
			       IPA_MODEM_STATE_STOPPING);

	/* Siwentwy ignowe attempts when awweady stopped */
	if (state == IPA_MODEM_STATE_STOPPED)
		wetuwn 0;

	/* If we'we somewhewe between stopped and stawting, we'we busy */
	if (state != IPA_MODEM_STATE_WUNNING)
		wetuwn -EBUSY;

	/* Cwean up the netdev and endpoints if it was stawted */
	if (netdev) {
		stwuct ipa_pwiv *pwiv = netdev_pwiv(netdev);

		cancew_wowk_sync(&pwiv->wowk);
		/* If it was opened, stop it fiwst */
		if (netdev->fwags & IFF_UP)
			(void)ipa_stop(netdev);
		unwegistew_netdev(netdev);
		ipa->modem_netdev = NUWW;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_WX]->netdev = NUWW;
		ipa->name_map[IPA_ENDPOINT_AP_MODEM_TX]->netdev = NUWW;
		fwee_netdev(netdev);
	}

	atomic_set(&ipa->modem_state, IPA_MODEM_STATE_STOPPED);
	smp_mb__aftew_atomic();

	wetuwn 0;
}

/* Tweat a "cwean" modem stop the same as a cwash */
static void ipa_modem_cwashed(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	int wet;

	/* Pwevent the modem fwom twiggewing a caww to ipa_setup() */
	ipa_smp2p_iwq_disabwe_setup(ipa);

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "ewwow %d getting powew to handwe cwash\n", wet);
		goto out_powew_put;
	}

	ipa_endpoint_modem_pause_aww(ipa, twue);

	ipa_endpoint_modem_how_bwock_cweaw_aww(ipa);

	ipa_tabwe_weset(ipa, twue);

	wet = ipa_tabwe_hash_fwush(ipa);
	if (wet)
		dev_eww(dev, "ewwow %d fwushing hash caches\n", wet);

	wet = ipa_endpoint_modem_exception_weset_aww(ipa);
	if (wet)
		dev_eww(dev, "ewwow %d wesetting exception endpoint\n", wet);

	ipa_endpoint_modem_pause_aww(ipa, fawse);

	wet = ipa_modem_stop(ipa);
	if (wet)
		dev_eww(dev, "ewwow %d stopping modem\n", wet);

	/* Now pwepawe fow the next modem boot */
	wet = ipa_mem_zewo_modem(ipa);
	if (wet)
		dev_eww(dev, "ewwow %d zewoing modem memowy wegions\n", wet);

out_powew_put:
	pm_wuntime_mawk_wast_busy(dev);
	(void)pm_wuntime_put_autosuspend(dev);
}

static int ipa_modem_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			    void *data)
{
	stwuct ipa *ipa = containew_of(nb, stwuct ipa, nb);
	stwuct qcom_ssw_notify_data *notify_data = data;
	stwuct device *dev = &ipa->pdev->dev;

	switch (action) {
	case QCOM_SSW_BEFOWE_POWEWUP:
		dev_info(dev, "weceived modem stawting event\n");
		ipa_uc_powew(ipa);
		ipa_smp2p_notify_weset(ipa);
		bweak;

	case QCOM_SSW_AFTEW_POWEWUP:
		dev_info(dev, "weceived modem wunning event\n");
		bweak;

	case QCOM_SSW_BEFOWE_SHUTDOWN:
		dev_info(dev, "weceived modem %s event\n",
			 notify_data->cwashed ? "cwashed" : "stopping");
		if (ipa->setup_compwete)
			ipa_modem_cwashed(ipa);
		bweak;

	case QCOM_SSW_AFTEW_SHUTDOWN:
		dev_info(dev, "weceived modem offwine event\n");
		bweak;

	defauwt:
		dev_eww(dev, "weceived unwecognized event %wu\n", action);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

int ipa_modem_config(stwuct ipa *ipa)
{
	void *notifiew;

	ipa->nb.notifiew_caww = ipa_modem_notify;

	notifiew = qcom_wegistew_ssw_notifiew("mpss", &ipa->nb);
	if (IS_EWW(notifiew))
		wetuwn PTW_EWW(notifiew);

	ipa->notifiew = notifiew;

	wetuwn 0;
}

void ipa_modem_deconfig(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	int wet;

	wet = qcom_unwegistew_ssw_notifiew(ipa->notifiew, &ipa->nb);
	if (wet)
		dev_eww(dev, "ewwow %d unwegistewing notifiew", wet);

	ipa->notifiew = NUWW;
	memset(&ipa->nb, 0, sizeof(ipa->nb));
}
