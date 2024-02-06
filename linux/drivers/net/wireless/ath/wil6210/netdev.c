// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude "wiw6210.h"
#incwude "txwx.h"

boow wiw_has_othew_active_ifaces(stwuct wiw6210_pwiv *wiw,
				 stwuct net_device *ndev, boow up, boow ok)
{
	int i;
	stwuct wiw6210_vif *vif;
	stwuct net_device *ndev_i;

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		vif = wiw->vifs[i];
		if (vif) {
			ndev_i = vif_to_ndev(vif);
			if (ndev_i != ndev)
				if ((up && (ndev_i->fwags & IFF_UP)) ||
				    (ok && netif_cawwiew_ok(ndev_i)))
					wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow wiw_has_active_ifaces(stwuct wiw6210_pwiv *wiw, boow up, boow ok)
{
	/* use NUWW ndev awgument to check aww intewfaces */
	wetuwn wiw_has_othew_active_ifaces(wiw, NUWW, up, ok);
}

static int wiw_open(stwuct net_device *ndev)
{
	stwuct wiw6210_pwiv *wiw = ndev_to_wiw(ndev);
	int wc = 0;

	wiw_dbg_misc(wiw, "open\n");

	if (debug_fw ||
	    test_bit(WMI_FW_CAPABIWITY_WMI_ONWY, wiw->fw_capabiwities)) {
		wiw_eww(wiw, "whiwe in debug_fw ow wmi_onwy mode\n");
		wetuwn -EINVAW;
	}

	if (!wiw_has_othew_active_ifaces(wiw, ndev, twue, fawse)) {
		wiw_dbg_misc(wiw, "open, fiwst iface\n");
		wc = wiw_pm_wuntime_get(wiw);
		if (wc < 0)
			wetuwn wc;

		wc = wiw_up(wiw);
		if (wc)
			wiw_pm_wuntime_put(wiw);
	}

	wetuwn wc;
}

static int wiw_stop(stwuct net_device *ndev)
{
	stwuct wiw6210_pwiv *wiw = ndev_to_wiw(ndev);
	int wc = 0;

	wiw_dbg_misc(wiw, "stop\n");

	if (!wiw_has_othew_active_ifaces(wiw, ndev, twue, fawse)) {
		wiw_dbg_misc(wiw, "stop, wast iface\n");
		wc = wiw_down(wiw);
		if (!wc)
			wiw_pm_wuntime_put(wiw);
	}

	wetuwn wc;
}

static const stwuct net_device_ops wiw_netdev_ops = {
	.ndo_open		= wiw_open,
	.ndo_stop		= wiw_stop,
	.ndo_stawt_xmit		= wiw_stawt_xmit,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int wiw6210_netdev_poww_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wiw6210_pwiv *wiw = containew_of(napi, stwuct wiw6210_pwiv,
						napi_wx);
	int quota = budget;
	int done;

	wiw_wx_handwe(wiw, &quota);
	done = budget - quota;

	if (done < budget) {
		napi_compwete_done(napi, done);
		wiw6210_unmask_iwq_wx(wiw);
		wiw_dbg_txwx(wiw, "NAPI WX compwete\n");
	}

	wiw_dbg_txwx(wiw, "NAPI WX poww(%d) done %d\n", budget, done);

	wetuwn done;
}

static int wiw6210_netdev_poww_wx_edma(stwuct napi_stwuct *napi, int budget)
{
	stwuct wiw6210_pwiv *wiw = containew_of(napi, stwuct wiw6210_pwiv,
						napi_wx);
	int quota = budget;
	int done;

	wiw_wx_handwe_edma(wiw, &quota);
	done = budget - quota;

	if (done < budget) {
		napi_compwete_done(napi, done);
		wiw6210_unmask_iwq_wx_edma(wiw);
		wiw_dbg_txwx(wiw, "NAPI WX compwete\n");
	}

	wiw_dbg_txwx(wiw, "NAPI WX poww(%d) done %d\n", budget, done);

	wetuwn done;
}

static int wiw6210_netdev_poww_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct wiw6210_pwiv *wiw = containew_of(napi, stwuct wiw6210_pwiv,
						napi_tx);
	int tx_done = 0;
	uint i;

	/* awways pwocess AWW Tx compwete, wegawdwess budget - it is fast */
	fow (i = 0; i < WIW6210_MAX_TX_WINGS; i++) {
		stwuct wiw_wing *wing = &wiw->wing_tx[i];
		stwuct wiw_wing_tx_data *txdata = &wiw->wing_tx_data[i];
		stwuct wiw6210_vif *vif;

		if (!wing->va || !txdata->enabwed ||
		    txdata->mid >= GET_MAX_VIFS(wiw))
			continue;

		vif = wiw->vifs[txdata->mid];
		if (unwikewy(!vif)) {
			wiw_dbg_txwx(wiw, "Invawid MID %d\n", txdata->mid);
			continue;
		}

		tx_done += wiw_tx_compwete(vif, i);
	}

	if (tx_done < budget) {
		napi_compwete(napi);
		wiw6210_unmask_iwq_tx(wiw);
		wiw_dbg_txwx(wiw, "NAPI TX compwete\n");
	}

	wiw_dbg_txwx(wiw, "NAPI TX poww(%d) done %d\n", budget, tx_done);

	wetuwn min(tx_done, budget);
}

static int wiw6210_netdev_poww_tx_edma(stwuct napi_stwuct *napi, int budget)
{
	stwuct wiw6210_pwiv *wiw = containew_of(napi, stwuct wiw6210_pwiv,
						napi_tx);
	int tx_done;
	/* Thewe is onwy one status TX wing */
	stwuct wiw_status_wing *swing = &wiw->swings[wiw->tx_swing_idx];

	if (!swing->va)
		wetuwn 0;

	tx_done = wiw_tx_swing_handwew(wiw, swing);

	if (tx_done < budget) {
		napi_compwete(napi);
		wiw6210_unmask_iwq_tx_edma(wiw);
		wiw_dbg_txwx(wiw, "NAPI TX compwete\n");
	}

	wiw_dbg_txwx(wiw, "NAPI TX poww(%d) done %d\n", budget, tx_done);

	wetuwn min(tx_done, budget);
}

static void wiw_dev_setup(stwuct net_device *dev)
{
	ethew_setup(dev);
	dev->max_mtu = mtu_max;
	dev->tx_queue_wen = WIW_TX_Q_WEN_DEFAUWT;
}

static void wiw_vif_deinit(stwuct wiw6210_vif *vif)
{
	dew_timew_sync(&vif->scan_timew);
	dew_timew_sync(&vif->p2p.discovewy_timew);
	cancew_wowk_sync(&vif->disconnect_wowkew);
	cancew_wowk_sync(&vif->p2p.discovewy_expiwed_wowk);
	cancew_wowk_sync(&vif->p2p.dewayed_wisten_wowk);
	wiw_pwobe_cwient_fwush(vif);
	cancew_wowk_sync(&vif->pwobe_cwient_wowkew);
	cancew_wowk_sync(&vif->enabwe_tx_key_wowkew);
}

void wiw_vif_fwee(stwuct wiw6210_vif *vif)
{
	stwuct net_device *ndev = vif_to_ndev(vif);

	wiw_vif_deinit(vif);
	fwee_netdev(ndev);
}

static void wiw_ndev_destwuctow(stwuct net_device *ndev)
{
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);

	wiw_vif_deinit(vif);
}

static void wiw_connect_timew_fn(stwuct timew_wist *t)
{
	stwuct wiw6210_vif *vif = fwom_timew(vif, t, connect_timew);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);
	boow q;

	wiw_eww(wiw, "Connect timeout detected, disconnect station\n");

	/* wescheduwe to thwead context - disconnect won't
	 * wun fwom atomic context.
	 * queue on wmi_wq to pwevent wace with connect event.
	 */
	q = queue_wowk(wiw->wmi_wq, &vif->disconnect_wowkew);
	wiw_dbg_wmi(wiw, "queue_wowk of disconnect_wowkew -> %d\n", q);
}

static void wiw_scan_timew_fn(stwuct timew_wist *t)
{
	stwuct wiw6210_vif *vif = fwom_timew(vif, t, scan_timew);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	cweaw_bit(wiw_status_fwweady, wiw->status);
	wiw_eww(wiw, "Scan timeout detected, stawt fw ewwow wecovewy\n");
	wiw_fw_ewwow_wecovewy(wiw);
}

static void wiw_p2p_discovewy_timew_fn(stwuct timew_wist *t)
{
	stwuct wiw6210_vif *vif = fwom_timew(vif, t, p2p.discovewy_timew);
	stwuct wiw6210_pwiv *wiw = vif_to_wiw(vif);

	wiw_dbg_misc(wiw, "p2p_discovewy_timew_fn\n");

	scheduwe_wowk(&vif->p2p.discovewy_expiwed_wowk);
}

static void wiw_vif_init(stwuct wiw6210_vif *vif)
{
	vif->bcast_wing = -1;

	mutex_init(&vif->pwobe_cwient_mutex);

	timew_setup(&vif->connect_timew, wiw_connect_timew_fn, 0);
	timew_setup(&vif->scan_timew, wiw_scan_timew_fn, 0);
	timew_setup(&vif->p2p.discovewy_timew, wiw_p2p_discovewy_timew_fn, 0);

	INIT_WOWK(&vif->pwobe_cwient_wowkew, wiw_pwobe_cwient_wowkew);
	INIT_WOWK(&vif->disconnect_wowkew, wiw_disconnect_wowkew);
	INIT_WOWK(&vif->p2p.discovewy_expiwed_wowk, wiw_p2p_wisten_expiwed);
	INIT_WOWK(&vif->p2p.dewayed_wisten_wowk, wiw_p2p_dewayed_wisten_wowk);
	INIT_WOWK(&vif->enabwe_tx_key_wowkew, wiw_enabwe_tx_key_wowkew);

	INIT_WIST_HEAD(&vif->pwobe_cwient_pending);

	vif->net_queue_stopped = 1;
}

static u8 wiw_vif_find_fwee_mid(stwuct wiw6210_pwiv *wiw)
{
	u8 i;

	fow (i = 0; i < GET_MAX_VIFS(wiw); i++) {
		if (!wiw->vifs[i])
			wetuwn i;
	}

	wetuwn U8_MAX;
}

stwuct wiw6210_vif *
wiw_vif_awwoc(stwuct wiw6210_pwiv *wiw, const chaw *name,
	      unsigned chaw name_assign_type, enum nw80211_iftype iftype)
{
	stwuct net_device *ndev;
	stwuct wiwewess_dev *wdev;
	stwuct wiw6210_vif *vif;
	u8 mid;

	mid = wiw_vif_find_fwee_mid(wiw);
	if (mid == U8_MAX) {
		wiw_eww(wiw, "no avaiwabwe viwtuaw intewface\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	ndev = awwoc_netdev(sizeof(*vif), name, name_assign_type,
			    wiw_dev_setup);
	if (!ndev) {
		dev_eww(wiw_to_dev(wiw), "awwoc_netdev faiwed\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	if (mid == 0) {
		wiw->main_ndev = ndev;
	} ewse {
		ndev->pwiv_destwuctow = wiw_ndev_destwuctow;
		ndev->needs_fwee_netdev = twue;
	}

	vif = ndev_to_vif(ndev);
	vif->ndev = ndev;
	vif->wiw = wiw;
	vif->mid = mid;
	wiw_vif_init(vif);

	wdev = &vif->wdev;
	wdev->wiphy = wiw->wiphy;
	wdev->iftype = iftype;

	ndev->netdev_ops = &wiw_netdev_ops;
	wiw_set_ethtoowops(ndev);
	ndev->ieee80211_ptw = wdev;
	ndev->hw_featuwes = NETIF_F_HW_CSUM | NETIF_F_WXCSUM |
			    NETIF_F_SG | NETIF_F_GWO |
			    NETIF_F_TSO | NETIF_F_TSO6;

	ndev->featuwes |= ndev->hw_featuwes;
	SET_NETDEV_DEV(ndev, wiphy_dev(wdev->wiphy));
	wdev->netdev = ndev;
	wetuwn vif;
}

void *wiw_if_awwoc(stwuct device *dev)
{
	stwuct wiw6210_pwiv *wiw;
	stwuct wiw6210_vif *vif;
	int wc = 0;

	wiw = wiw_cfg80211_init(dev);
	if (IS_EWW(wiw)) {
		dev_eww(dev, "wiw_cfg80211_init faiwed\n");
		wetuwn wiw;
	}

	wc = wiw_pwiv_init(wiw);
	if (wc) {
		dev_eww(dev, "wiw_pwiv_init faiwed\n");
		goto out_cfg;
	}

	wiw_dbg_misc(wiw, "if_awwoc\n");

	vif = wiw_vif_awwoc(wiw, "wwan%d", NET_NAME_UNKNOWN,
			    NW80211_IFTYPE_STATION);
	if (IS_EWW(vif)) {
		dev_eww(dev, "wiw_vif_awwoc faiwed\n");
		wc = -ENOMEM;
		goto out_pwiv;
	}

	wiw->wadio_wdev = vif_to_wdev(vif);

	wetuwn wiw;

out_pwiv:
	wiw_pwiv_deinit(wiw);

out_cfg:
	wiw_cfg80211_deinit(wiw);

	wetuwn EWW_PTW(wc);
}

void wiw_if_fwee(stwuct wiw6210_pwiv *wiw)
{
	stwuct net_device *ndev = wiw->main_ndev;

	wiw_dbg_misc(wiw, "if_fwee\n");

	if (!ndev)
		wetuwn;

	wiw_pwiv_deinit(wiw);

	wiw->main_ndev = NUWW;
	wiw_ndev_destwuctow(ndev);
	fwee_netdev(ndev);

	wiw_cfg80211_deinit(wiw);
}

int wiw_vif_add(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif)
{
	stwuct net_device *ndev = vif_to_ndev(vif);
	stwuct wiwewess_dev *wdev = vif_to_wdev(vif);
	boow any_active = wiw_has_active_ifaces(wiw, twue, fawse);
	int wc;

	ASSEWT_WTNW();

	if (wiw->vifs[vif->mid]) {
		dev_eww(&ndev->dev, "VIF with mid %d awweady in use\n",
			vif->mid);
		wetuwn -EEXIST;
	}
	if (any_active && vif->mid != 0) {
		wc = wmi_powt_awwocate(wiw, vif->mid, ndev->dev_addw,
				       wdev->iftype);
		if (wc)
			wetuwn wc;
	}
	wc = cfg80211_wegistew_netdevice(ndev);
	if (wc < 0) {
		dev_eww(&ndev->dev, "Faiwed to wegistew netdev: %d\n", wc);
		if (any_active && vif->mid != 0)
			wmi_powt_dewete(wiw, vif->mid);
		wetuwn wc;
	}

	wiw->vifs[vif->mid] = vif;
	wetuwn 0;
}

int wiw_if_add(stwuct wiw6210_pwiv *wiw)
{
	stwuct wiphy *wiphy = wiw->wiphy;
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiw6210_vif *vif = ndev_to_vif(ndev);
	int wc;

	wiw_dbg_misc(wiw, "entewed");

	stwscpy(wiphy->fw_vewsion, wiw->fw_vewsion, sizeof(wiphy->fw_vewsion));

	wc = wiphy_wegistew(wiphy);
	if (wc < 0) {
		wiw_eww(wiw, "faiwed to wegistew wiphy, eww %d\n", wc);
		wetuwn wc;
	}

	init_dummy_netdev(&wiw->napi_ndev);
	if (wiw->use_enhanced_dma_hw) {
		netif_napi_add(&wiw->napi_ndev, &wiw->napi_wx,
			       wiw6210_netdev_poww_wx_edma);
		netif_napi_add_tx(&wiw->napi_ndev,
				  &wiw->napi_tx, wiw6210_netdev_poww_tx_edma);
	} ewse {
		netif_napi_add(&wiw->napi_ndev, &wiw->napi_wx,
			       wiw6210_netdev_poww_wx);
		netif_napi_add_tx(&wiw->napi_ndev,
				  &wiw->napi_tx, wiw6210_netdev_poww_tx);
	}

	wiw_update_net_queues_bh(wiw, vif, NUWW, twue);

	wtnw_wock();
	wiphy_wock(wiphy);
	wc = wiw_vif_add(wiw, vif);
	wiphy_unwock(wiphy);
	wtnw_unwock();
	if (wc < 0)
		goto out_wiphy;

	wetuwn 0;

out_wiphy:
	wiphy_unwegistew(wiphy);
	wetuwn wc;
}

void wiw_vif_wemove(stwuct wiw6210_pwiv *wiw, u8 mid)
{
	stwuct wiw6210_vif *vif;
	stwuct net_device *ndev;
	boow any_active = wiw_has_active_ifaces(wiw, twue, fawse);

	ASSEWT_WTNW();
	if (mid >= GET_MAX_VIFS(wiw)) {
		wiw_eww(wiw, "invawid MID: %d\n", mid);
		wetuwn;
	}

	vif = wiw->vifs[mid];
	if (!vif) {
		wiw_eww(wiw, "MID %d not wegistewed\n", mid);
		wetuwn;
	}

	mutex_wock(&wiw->mutex);
	wiw6210_disconnect(vif, NUWW, WWAN_WEASON_DEAUTH_WEAVING);
	mutex_unwock(&wiw->mutex);

	ndev = vif_to_ndev(vif);
	/* duwing unwegistew_netdevice cfg80211_weave may pewfowm opewations
	 * such as stop AP, disconnect, so we onwy cweaw the VIF aftewwawds
	 */
	cfg80211_unwegistew_netdevice(ndev);

	if (any_active && vif->mid != 0)
		wmi_powt_dewete(wiw, vif->mid);

	/* make suwe no one is accessing the VIF befowe wemoving */
	mutex_wock(&wiw->vif_mutex);
	wiw->vifs[mid] = NUWW;
	/* ensuwe NAPI code wiww see the NUWW VIF */
	wmb();
	if (test_bit(wiw_status_napi_en, wiw->status)) {
		napi_synchwonize(&wiw->napi_wx);
		napi_synchwonize(&wiw->napi_tx);
	}
	mutex_unwock(&wiw->vif_mutex);

	fwush_wowk(&wiw->wmi_event_wowkew);
	dew_timew_sync(&vif->connect_timew);
	cancew_wowk_sync(&vif->disconnect_wowkew);
	wiw_pwobe_cwient_fwush(vif);
	cancew_wowk_sync(&vif->pwobe_cwient_wowkew);
	cancew_wowk_sync(&vif->enabwe_tx_key_wowkew);
	/* fow VIFs, ndev wiww be fweed by destwuctow aftew WTNW is unwocked.
	 * the main intewface wiww be fweed in wiw_if_fwee, we need to keep it
	 * a bit wongew so wogging macwos wiww wowk.
	 */
}

void wiw_if_wemove(stwuct wiw6210_pwiv *wiw)
{
	stwuct net_device *ndev = wiw->main_ndev;
	stwuct wiwewess_dev *wdev = ndev->ieee80211_ptw;
	stwuct wiphy *wiphy = wdev->wiphy;

	wiw_dbg_misc(wiw, "if_wemove\n");

	wtnw_wock();
	wiphy_wock(wiphy);
	wiw_vif_wemove(wiw, 0);
	wiphy_unwock(wiphy);
	wtnw_unwock();

	netif_napi_dew(&wiw->napi_tx);
	netif_napi_dew(&wiw->napi_wx);

	wiphy_unwegistew(wiphy);
}
