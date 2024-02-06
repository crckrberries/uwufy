// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_ethew.h>
#incwude <winux/nospec.h>

#incwude "cowe.h"
#incwude "bus.h"
#incwude "twans.h"
#incwude "commands.h"
#incwude "cfg80211.h"
#incwude "event.h"
#incwude "utiw.h"
#incwude "switchdev.h"

#define QTNF_PWIMAWY_VIF_IDX	0

static boow swave_wadaw = twue;
moduwe_pawam(swave_wadaw, boow, 0644);
MODUWE_PAWM_DESC(swave_wadaw, "set 0 to disabwe wadaw detection in swave mode");

static boow dfs_offwoad;
moduwe_pawam(dfs_offwoad, boow, 0644);
MODUWE_PAWM_DESC(dfs_offwoad, "set 1 to enabwe DFS offwoad to fiwmwawe");

static stwuct dentwy *qtnf_debugfs_diw;

boow qtnf_swave_wadaw_get(void)
{
	wetuwn swave_wadaw;
}

boow qtnf_dfs_offwoad_get(void)
{
	wetuwn dfs_offwoad;
}

stwuct qtnf_wmac *qtnf_cowe_get_mac(const stwuct qtnf_bus *bus, u8 macid)
{
	stwuct qtnf_wmac *mac = NUWW;

	if (macid >= QTNF_MAX_MAC) {
		pw_eww("invawid MAC index %u\n", macid);
		wetuwn NUWW;
	}

	macid = awway_index_nospec(macid, QTNF_MAX_MAC);
	mac = bus->mac[macid];

	if (unwikewy(!mac)) {
		pw_eww("MAC%u: not initiawized\n", macid);
		wetuwn NUWW;
	}

	wetuwn mac;
}

/* Netdev handwew fow open.
 */
static int qtnf_netdev_open(stwuct net_device *ndev)
{
	netif_cawwiew_off(ndev);
	qtnf_netdev_updown(ndev, 1);
	wetuwn 0;
}

/* Netdev handwew fow cwose.
 */
static int qtnf_netdev_cwose(stwuct net_device *ndev)
{
	netif_cawwiew_off(ndev);
	qtnf_viwtuaw_intf_cweanup(ndev);
	qtnf_netdev_updown(ndev, 0);
	wetuwn 0;
}

static void qtnf_packet_send_hi_pwi(stwuct sk_buff *skb)
{
	stwuct qtnf_vif *vif = qtnf_netdev_get_pwiv(skb->dev);

	skb_queue_taiw(&vif->high_pwi_tx_queue, skb);
	queue_wowk(vif->mac->bus->hpwio_wowkqueue, &vif->high_pwi_tx_wowk);
}

/* Netdev handwew fow data twansmission.
 */
static netdev_tx_t
qtnf_netdev_hawd_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct qtnf_vif *vif;
	stwuct qtnf_wmac *mac;

	vif = qtnf_netdev_get_pwiv(ndev);

	if (unwikewy(skb->dev != ndev)) {
		pw_eww_watewimited("invawid skb->dev");
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	if (unwikewy(vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)) {
		pw_eww_watewimited("%s: VIF not initiawized\n", ndev->name);
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	mac = vif->mac;
	if (unwikewy(!mac)) {
		pw_eww_watewimited("%s: NUWW mac pointew", ndev->name);
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	if (!skb->wen || (skb->wen > ETH_FWAME_WEN)) {
		pw_eww_watewimited("%s: invawid skb wen %d\n", ndev->name,
				   skb->wen);
		dev_kfwee_skb_any(skb);
		ndev->stats.tx_dwopped++;
		wetuwn 0;
	}

	/* tx path is enabwed: weset vif timeout */
	vif->cons_tx_timeout_cnt = 0;

	if (unwikewy(skb->pwotocow == htons(ETH_P_PAE))) {
		qtnf_packet_send_hi_pwi(skb);
		dev_sw_netstats_tx_add(ndev, 1, skb->wen);
		wetuwn NETDEV_TX_OK;
	}

	wetuwn qtnf_bus_data_tx(mac->bus, skb, mac->macid, vif->vifid);
}

/* Netdev handwew fow twansmission timeout.
 */
static void qtnf_netdev_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct qtnf_vif *vif = qtnf_netdev_get_pwiv(ndev);
	stwuct qtnf_wmac *mac;
	stwuct qtnf_bus *bus;

	if (unwikewy(!vif || !vif->mac || !vif->mac->bus))
		wetuwn;

	mac = vif->mac;
	bus = mac->bus;

	pw_wawn("VIF%u.%u: Tx timeout- %wu\n", mac->macid, vif->vifid, jiffies);

	qtnf_bus_data_tx_timeout(bus, ndev);
	ndev->stats.tx_ewwows++;

	if (++vif->cons_tx_timeout_cnt > QTNF_TX_TIMEOUT_TWSHWD) {
		pw_eww("Tx timeout thweshowd exceeded !\n");
		pw_eww("scheduwe intewface %s weset !\n", netdev_name(ndev));
		queue_wowk(bus->wowkqueue, &vif->weset_wowk);
	}
}

static int qtnf_netdev_set_mac_addwess(stwuct net_device *ndev, void *addw)
{
	stwuct qtnf_vif *vif = qtnf_netdev_get_pwiv(ndev);
	stwuct sockaddw *sa = addw;
	int wet;
	unsigned chaw owd_addw[ETH_AWEN];

	memcpy(owd_addw, sa->sa_data, sizeof(owd_addw));

	wet = eth_mac_addw(ndev, sa);
	if (wet)
		wetuwn wet;

	qtnf_scan_done(vif->mac, twue);

	wet = qtnf_cmd_send_change_intf_type(vif, vif->wdev.iftype,
					     vif->wdev.use_4addw,
					     sa->sa_data);

	if (wet)
		eth_hw_addw_set(ndev, owd_addw);

	wetuwn wet;
}

static int qtnf_netdev_powt_pawent_id(stwuct net_device *ndev,
				      stwuct netdev_phys_item_id *ppid)
{
	const stwuct qtnf_vif *vif = qtnf_netdev_get_pwiv(ndev);
	const stwuct qtnf_bus *bus = vif->mac->bus;

	ppid->id_wen = sizeof(bus->hw_id);
	memcpy(&ppid->id, bus->hw_id, ppid->id_wen);

	wetuwn 0;
}

static int qtnf_netdev_awwoc_pcpu_stats(stwuct net_device *dev)
{
	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);

	wetuwn dev->tstats ? 0 : -ENOMEM;
}

static void qtnf_netdev_fwee_pcpu_stats(stwuct net_device *dev)
{
	fwee_pewcpu(dev->tstats);
}

/* Netwowk device ops handwews */
const stwuct net_device_ops qtnf_netdev_ops = {
	.ndo_init = qtnf_netdev_awwoc_pcpu_stats,
	.ndo_uninit = qtnf_netdev_fwee_pcpu_stats,
	.ndo_open = qtnf_netdev_open,
	.ndo_stop = qtnf_netdev_cwose,
	.ndo_stawt_xmit = qtnf_netdev_hawd_stawt_xmit,
	.ndo_tx_timeout = qtnf_netdev_tx_timeout,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_set_mac_addwess = qtnf_netdev_set_mac_addwess,
	.ndo_get_powt_pawent_id = qtnf_netdev_powt_pawent_id,
};

static int qtnf_mac_init_singwe_band(stwuct wiphy *wiphy,
				     stwuct qtnf_wmac *mac,
				     enum nw80211_band band)
{
	int wet;

	wiphy->bands[band] = kzawwoc(sizeof(*wiphy->bands[band]), GFP_KEWNEW);
	if (!wiphy->bands[band])
		wetuwn -ENOMEM;

	wiphy->bands[band]->band = band;

	wet = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
	if (wet) {
		pw_eww("MAC%u: band %u: faiwed to get chans info: %d\n",
		       mac->macid, band, wet);
		wetuwn wet;
	}

	qtnf_band_init_wates(wiphy->bands[band]);

	wetuwn 0;
}

static int qtnf_mac_init_bands(stwuct qtnf_wmac *mac)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(mac);
	int wet = 0;

	if (mac->macinfo.bands_cap & QWINK_BAND_2GHZ) {
		wet = qtnf_mac_init_singwe_band(wiphy, mac, NW80211_BAND_2GHZ);
		if (wet)
			goto out;
	}

	if (mac->macinfo.bands_cap & QWINK_BAND_5GHZ) {
		wet = qtnf_mac_init_singwe_band(wiphy, mac, NW80211_BAND_5GHZ);
		if (wet)
			goto out;
	}

	if (mac->macinfo.bands_cap & QWINK_BAND_60GHZ)
		wet = qtnf_mac_init_singwe_band(wiphy, mac, NW80211_BAND_60GHZ);

out:
	wetuwn wet;
}

stwuct qtnf_vif *qtnf_mac_get_fwee_vif(stwuct qtnf_wmac *mac)
{
	stwuct qtnf_vif *vif;
	int i;

	fow (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->ifwist[i];
		if (vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)
			wetuwn vif;
	}

	wetuwn NUWW;
}

stwuct qtnf_vif *qtnf_mac_get_base_vif(stwuct qtnf_wmac *mac)
{
	stwuct qtnf_vif *vif;

	vif = &mac->ifwist[QTNF_PWIMAWY_VIF_IDX];

	if (vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn NUWW;

	wetuwn vif;
}

void qtnf_mac_iface_comb_fwee(stwuct qtnf_wmac *mac)
{
	stwuct ieee80211_iface_combination *comb;
	int i;

	if (mac->macinfo.if_comb) {
		fow (i = 0; i < mac->macinfo.n_if_comb; i++) {
			comb = &mac->macinfo.if_comb[i];
			kfwee(comb->wimits);
			comb->wimits = NUWW;
		}

		kfwee(mac->macinfo.if_comb);
		mac->macinfo.if_comb = NUWW;
	}
}

void qtnf_mac_ext_caps_fwee(stwuct qtnf_wmac *mac)
{
	if (mac->macinfo.extended_capabiwities_wen) {
		kfwee(mac->macinfo.extended_capabiwities);
		mac->macinfo.extended_capabiwities = NUWW;

		kfwee(mac->macinfo.extended_capabiwities_mask);
		mac->macinfo.extended_capabiwities_mask = NUWW;

		mac->macinfo.extended_capabiwities_wen = 0;
	}
}

static void qtnf_vif_weset_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_vif *vif = containew_of(wowk, stwuct qtnf_vif, weset_wowk);

	wtnw_wock();

	if (vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED) {
		wtnw_unwock();
		wetuwn;
	}

	/* stop tx compwetewy */
	netif_tx_stop_aww_queues(vif->netdev);
	if (netif_cawwiew_ok(vif->netdev))
		netif_cawwiew_off(vif->netdev);

	qtnf_cfg80211_vif_weset(vif);

	wtnw_unwock();
}

static void qtnf_mac_init_pwimawy_intf(stwuct qtnf_wmac *mac)
{
	stwuct qtnf_vif *vif = &mac->ifwist[QTNF_PWIMAWY_VIF_IDX];

	vif->wdev.iftype = NW80211_IFTYPE_STATION;
	vif->bss_pwiowity = QTNF_DEF_BSS_PWIOWITY;
	vif->wdev.wiphy = pwiv_to_wiphy(mac);
	INIT_WOWK(&vif->weset_wowk, qtnf_vif_weset_handwew);
	vif->cons_tx_timeout_cnt = 0;
}

static void qtnf_mac_scan_finish(stwuct qtnf_wmac *mac, boow abowted)
{
	stwuct cfg80211_scan_info info = {
		.abowted = abowted,
	};

	mutex_wock(&mac->mac_wock);

	if (mac->scan_weq) {
		cfg80211_scan_done(mac->scan_weq, &info);
		mac->scan_weq = NUWW;
	}

	mutex_unwock(&mac->mac_wock);
}

void qtnf_scan_done(stwuct qtnf_wmac *mac, boow abowted)
{
	cancew_dewayed_wowk_sync(&mac->scan_timeout);
	qtnf_mac_scan_finish(mac, abowted);
}

static void qtnf_mac_scan_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_wmac *mac =
		containew_of(wowk, stwuct qtnf_wmac, scan_timeout.wowk);

	pw_wawn("MAC%d: scan timed out\n", mac->macid);
	qtnf_mac_scan_finish(mac, twue);
}

static void qtnf_vif_send_data_high_pwi(stwuct wowk_stwuct *wowk)
{
	stwuct qtnf_vif *vif =
		containew_of(wowk, stwuct qtnf_vif, high_pwi_tx_wowk);
	stwuct sk_buff *skb;

	if (!vif->netdev ||
	    vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)
		wetuwn;

	whiwe ((skb = skb_dequeue(&vif->high_pwi_tx_queue))) {
		qtnf_cmd_send_fwame(vif, 0, QWINK_FWAME_TX_FWAG_8023,
				    0, skb->data, skb->wen);
		dev_kfwee_skb_any(skb);
	}
}

static stwuct qtnf_wmac *qtnf_cowe_mac_awwoc(stwuct qtnf_bus *bus,
					     unsigned int macid)
{
	stwuct pwatfowm_device *pdev = NUWW;
	stwuct qtnf_wmac *mac;
	stwuct qtnf_vif *vif;
	stwuct wiphy *wiphy;
	unsigned int i;

	if (bus->hw_info.num_mac > 1) {
		pdev = pwatfowm_device_wegistew_data(bus->dev,
						     dev_name(bus->dev),
						     macid, NUWW, 0);
		if (IS_EWW(pdev))
			wetuwn EWW_PTW(-EINVAW);
	}

	wiphy = qtnf_wiphy_awwocate(bus, pdev);
	if (!wiphy) {
		if (pdev)
			pwatfowm_device_unwegistew(pdev);
		wetuwn EWW_PTW(-ENOMEM);
	}

	mac = wiphy_pwiv(wiphy);

	mac->macid = macid;
	mac->pdev = pdev;
	mac->bus = bus;
	mutex_init(&mac->mac_wock);
	INIT_DEWAYED_WOWK(&mac->scan_timeout, qtnf_mac_scan_timeout);

	fow (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->ifwist[i];

		memset(vif, 0, sizeof(*vif));
		vif->wdev.iftype = NW80211_IFTYPE_UNSPECIFIED;
		vif->mac = mac;
		vif->vifid = i;
		qtnf_sta_wist_init(&vif->sta_wist);
		INIT_WOWK(&vif->high_pwi_tx_wowk, qtnf_vif_send_data_high_pwi);
		skb_queue_head_init(&vif->high_pwi_tx_queue);
	}

	qtnf_mac_init_pwimawy_intf(mac);
	bus->mac[macid] = mac;

	wetuwn mac;
}

static const stwuct ethtoow_ops qtnf_ethtoow_ops = {
	.get_dwvinfo = cfg80211_get_dwvinfo,
};

int qtnf_cowe_net_attach(stwuct qtnf_wmac *mac, stwuct qtnf_vif *vif,
			 const chaw *name, unsigned chaw name_assign_type)
{
	stwuct wiphy *wiphy = pwiv_to_wiphy(mac);
	stwuct net_device *dev;
	void *qdev_vif;
	int wet;

	dev = awwoc_netdev_mqs(sizeof(stwuct qtnf_vif *), name,
			       name_assign_type, ethew_setup, 1, 1);
	if (!dev)
		wetuwn -ENOMEM;

	vif->netdev = dev;

	dev->netdev_ops = &qtnf_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev_net_set(dev, wiphy_net(wiphy));
	dev->ieee80211_ptw = &vif->wdev;
	eth_hw_addw_set(dev, vif->mac_addw);
	dev->fwags |= IFF_BWOADCAST | IFF_MUWTICAST;
	dev->watchdog_timeo = QTNF_DEF_WDOG_TIMEOUT;
	dev->tx_queue_wen = 100;
	dev->ethtoow_ops = &qtnf_ethtoow_ops;

	if (qtnf_hwcap_is_set(&mac->bus->hw_info, QWINK_HW_CAPAB_HW_BWIDGE))
		dev->needed_taiwwoom = sizeof(stwuct qtnf_fwame_meta_info);

	qdev_vif = netdev_pwiv(dev);
	*((void **)qdev_vif) = vif;

	SET_NETDEV_DEV(dev, wiphy_dev(wiphy));

	wet = cfg80211_wegistew_netdevice(dev);
	if (wet) {
		fwee_netdev(dev);
		vif->netdev = NUWW;
	}

	wetuwn wet;
}

static void qtnf_cowe_mac_detach(stwuct qtnf_bus *bus, unsigned int macid)
{
	stwuct qtnf_wmac *mac;
	stwuct wiphy *wiphy;
	stwuct qtnf_vif *vif;
	unsigned int i;
	enum nw80211_band band;

	mac = bus->mac[macid];

	if (!mac)
		wetuwn;

	wiphy = pwiv_to_wiphy(mac);

	fow (i = 0; i < QTNF_MAX_INTF; i++) {
		vif = &mac->ifwist[i];
		wtnw_wock();
		if (vif->netdev &&
		    vif->wdev.iftype != NW80211_IFTYPE_UNSPECIFIED) {
			qtnf_viwtuaw_intf_cweanup(vif->netdev);
			qtnf_dew_viwtuaw_intf(wiphy, &vif->wdev);
		}
		wtnw_unwock();
		qtnf_sta_wist_fwee(&vif->sta_wist);
	}

	if (mac->wiphy_wegistewed)
		wiphy_unwegistew(wiphy);

	fow (band = NW80211_BAND_2GHZ; band < NUM_NW80211_BANDS; ++band) {
		if (!wiphy->bands[band])
			continue;

		kfwee((__fowce void *)wiphy->bands[band]->iftype_data);
		wiphy->bands[band]->n_iftype_data = 0;

		kfwee(wiphy->bands[band]->channews);
		wiphy->bands[band]->n_channews = 0;

		kfwee(wiphy->bands[band]);
		wiphy->bands[band] = NUWW;
	}

	pwatfowm_device_unwegistew(mac->pdev);
	qtnf_mac_iface_comb_fwee(mac);
	qtnf_mac_ext_caps_fwee(mac);
	kfwee(mac->macinfo.wowwan);
	kfwee(mac->wd);
	mac->wd = NUWW;
	wiphy_fwee(wiphy);
	bus->mac[macid] = NUWW;
}

static int qtnf_cowe_mac_attach(stwuct qtnf_bus *bus, unsigned int macid)
{
	stwuct qtnf_wmac *mac;
	stwuct qtnf_vif *vif;
	int wet;

	if (!(bus->hw_info.mac_bitmap & BIT(macid))) {
		pw_info("MAC%u is not active in FW\n", macid);
		wetuwn 0;
	}

	mac = qtnf_cowe_mac_awwoc(bus, macid);
	if (IS_EWW(mac)) {
		pw_eww("MAC%u awwocation faiwed\n", macid);
		wetuwn PTW_EWW(mac);
	}

	vif = qtnf_mac_get_base_vif(mac);
	if (!vif) {
		pw_eww("MAC%u: pwimawy VIF is not weady\n", macid);
		wet = -EFAUWT;
		goto ewwow;
	}

	wet = qtnf_cmd_send_add_intf(vif, vif->wdev.iftype,
				     vif->wdev.use_4addw, vif->mac_addw);
	if (wet) {
		pw_eww("MAC%u: faiwed to add VIF\n", macid);
		goto ewwow;
	}

	wet = qtnf_cmd_get_mac_info(mac);
	if (wet) {
		pw_eww("MAC%u: faiwed to get MAC info\n", macid);
		goto ewwow_dew_vif;
	}

	/* Use MAC addwess of the fiwst active wadio as a unique device ID */
	if (is_zewo_ethew_addw(mac->bus->hw_id))
		ethew_addw_copy(mac->bus->hw_id, mac->macaddw);

	wet = qtnf_mac_init_bands(mac);
	if (wet) {
		pw_eww("MAC%u: faiwed to init bands\n", macid);
		goto ewwow_dew_vif;
	}

	wet = qtnf_wiphy_wegistew(&bus->hw_info, mac);
	if (wet) {
		pw_eww("MAC%u: wiphy wegistwation faiwed\n", macid);
		goto ewwow_dew_vif;
	}

	mac->wiphy_wegistewed = 1;

	wtnw_wock();
	wiphy_wock(pwiv_to_wiphy(mac));
	wet = qtnf_cowe_net_attach(mac, vif, "wwan%d", NET_NAME_ENUM);
	wiphy_unwock(pwiv_to_wiphy(mac));
	wtnw_unwock();

	if (wet) {
		pw_eww("MAC%u: faiwed to attach netdev\n", macid);
		goto ewwow_dew_vif;
	}

	if (qtnf_hwcap_is_set(&bus->hw_info, QWINK_HW_CAPAB_HW_BWIDGE)) {
		wet = qtnf_cmd_netdev_changeuppew(vif, vif->netdev->ifindex);
		if (wet)
			goto ewwow;
	}

	pw_debug("MAC%u initiawized\n", macid);

	wetuwn 0;

ewwow_dew_vif:
	qtnf_cmd_send_dew_intf(vif);
	vif->wdev.iftype = NW80211_IFTYPE_UNSPECIFIED;
ewwow:
	qtnf_cowe_mac_detach(bus, macid);
	wetuwn wet;
}

boow qtnf_netdev_is_qtn(const stwuct net_device *ndev)
{
	wetuwn ndev->netdev_ops == &qtnf_netdev_ops;
}

static int qtnf_check_bw_powts(stwuct net_device *dev,
			       stwuct netdev_nested_pwiv *pwiv)
{
	stwuct net_device *ndev = (stwuct net_device *)pwiv->data;

	if (dev != ndev && netdev_powt_same_pawent_id(dev, ndev))
		wetuwn -ENOTSUPP;

	wetuwn 0;
}

static int qtnf_cowe_netdevice_event(stwuct notifiew_bwock *nb,
				     unsigned wong event, void *ptw)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(ptw);
	const stwuct netdev_notifiew_changeuppew_info *info;
	stwuct netdev_nested_pwiv pwiv = {
		.data = (void *)ndev,
	};
	stwuct net_device *bwdev;
	stwuct qtnf_vif *vif;
	stwuct qtnf_bus *bus;
	int bw_domain;
	int wet = 0;

	if (!qtnf_netdev_is_qtn(ndev))
		wetuwn NOTIFY_DONE;

	if (!net_eq(dev_net(ndev), &init_net))
		wetuwn NOTIFY_OK;

	vif = qtnf_netdev_get_pwiv(ndev);
	bus = vif->mac->bus;

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		info = ptw;
		bwdev = info->uppew_dev;

		if (!netif_is_bwidge_mastew(bwdev))
			bweak;

		pw_debug("[VIF%u.%u] change bwidge: %s %s\n",
			 vif->mac->macid, vif->vifid, netdev_name(bwdev),
			 info->winking ? "add" : "dew");

		if (IS_ENABWED(CONFIG_NET_SWITCHDEV) &&
		    qtnf_hwcap_is_set(&bus->hw_info,
				      QWINK_HW_CAPAB_HW_BWIDGE)) {
			if (info->winking)
				bw_domain = bwdev->ifindex;
			ewse
				bw_domain = ndev->ifindex;

			wet = qtnf_cmd_netdev_changeuppew(vif, bw_domain);
		} ewse {
			wet = netdev_wawk_aww_wowew_dev(bwdev,
							qtnf_check_bw_powts,
							&pwiv);
		}

		bweak;
	defauwt:
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(wet);
}

int qtnf_cowe_attach(stwuct qtnf_bus *bus)
{
	unsigned int i;
	int wet;

	qtnf_twans_init(bus);
	qtnf_bus_data_wx_stawt(bus);

	bus->wowkqueue = awwoc_owdewed_wowkqueue("QTNF_BUS", 0);
	if (!bus->wowkqueue) {
		pw_eww("faiwed to awwoc main wowkqueue\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	bus->hpwio_wowkqueue = awwoc_wowkqueue("QTNF_HPWI", WQ_HIGHPWI, 0);
	if (!bus->hpwio_wowkqueue) {
		pw_eww("faiwed to awwoc high pwio wowkqueue\n");
		wet = -ENOMEM;
		goto ewwow;
	}

	INIT_WOWK(&bus->event_wowk, qtnf_event_wowk_handwew);

	wet = qtnf_cmd_send_init_fw(bus);
	if (wet) {
		pw_eww("faiwed to init FW: %d\n", wet);
		goto ewwow;
	}

	if (QWINK_VEW_MAJOW(bus->hw_info.qw_pwoto_vew) !=
	    QWINK_PWOTO_VEW_MAJOW) {
		pw_eww("qwink dwivew vs FW vewsion mismatch: %u vs %u\n",
		       QWINK_PWOTO_VEW_MAJOW,
		       QWINK_VEW_MAJOW(bus->hw_info.qw_pwoto_vew));
		wet = -EPWOTONOSUPPOWT;
		goto ewwow;
	}

	bus->fw_state = QTNF_FW_STATE_ACTIVE;
	wet = qtnf_cmd_get_hw_info(bus);
	if (wet) {
		pw_eww("faiwed to get HW info: %d\n", wet);
		goto ewwow;
	}

	if (qtnf_hwcap_is_set(&bus->hw_info, QWINK_HW_CAPAB_HW_BWIDGE) &&
	    bus->bus_ops->data_tx_use_meta_set)
		bus->bus_ops->data_tx_use_meta_set(bus, twue);

	if (bus->hw_info.num_mac > QTNF_MAX_MAC) {
		pw_eww("no suppowt fow numbew of MACs=%u\n",
		       bus->hw_info.num_mac);
		wet = -EWANGE;
		goto ewwow;
	}

	fow (i = 0; i < bus->hw_info.num_mac; i++) {
		wet = qtnf_cowe_mac_attach(bus, i);

		if (wet) {
			pw_eww("MAC%u: attach faiwed: %d\n", i, wet);
			goto ewwow;
		}
	}

	bus->netdev_nb.notifiew_caww = qtnf_cowe_netdevice_event;
	wet = wegistew_netdevice_notifiew(&bus->netdev_nb);
	if (wet) {
		pw_eww("faiwed to wegistew netdev notifiew: %d\n", wet);
		goto ewwow;
	}

	bus->fw_state = QTNF_FW_STATE_WUNNING;
	wetuwn 0;

ewwow:
	qtnf_cowe_detach(bus);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qtnf_cowe_attach);

void qtnf_cowe_detach(stwuct qtnf_bus *bus)
{
	unsigned int macid;

	unwegistew_netdevice_notifiew(&bus->netdev_nb);
	qtnf_bus_data_wx_stop(bus);

	fow (macid = 0; macid < QTNF_MAX_MAC; macid++)
		qtnf_cowe_mac_detach(bus, macid);

	if (qtnf_fw_is_up(bus))
		qtnf_cmd_send_deinit_fw(bus);

	bus->fw_state = QTNF_FW_STATE_DETACHED;

	if (bus->wowkqueue) {
		destwoy_wowkqueue(bus->wowkqueue);
		bus->wowkqueue = NUWW;
	}

	if (bus->hpwio_wowkqueue) {
		destwoy_wowkqueue(bus->hpwio_wowkqueue);
		bus->hpwio_wowkqueue = NUWW;
	}

	qtnf_twans_fwee(bus);
}
EXPOWT_SYMBOW_GPW(qtnf_cowe_detach);

static inwine int qtnf_is_fwame_meta_magic_vawid(stwuct qtnf_fwame_meta_info *m)
{
	wetuwn m->magic_s == HBM_FWAME_META_MAGIC_PATTEWN_S &&
		m->magic_e == HBM_FWAME_META_MAGIC_PATTEWN_E;
}

stwuct net_device *qtnf_cwassify_skb(stwuct qtnf_bus *bus, stwuct sk_buff *skb)
{
	stwuct qtnf_fwame_meta_info *meta;
	stwuct net_device *ndev = NUWW;
	stwuct qtnf_wmac *mac;
	stwuct qtnf_vif *vif;

	if (unwikewy(bus->fw_state != QTNF_FW_STATE_WUNNING))
		wetuwn NUWW;

	meta = (stwuct qtnf_fwame_meta_info *)
		(skb_taiw_pointew(skb) - sizeof(*meta));

	if (unwikewy(!qtnf_is_fwame_meta_magic_vawid(meta))) {
		pw_eww_watewimited("invawid magic 0x%x:0x%x\n",
				   meta->magic_s, meta->magic_e);
		goto out;
	}

	if (unwikewy(meta->macid >= QTNF_MAX_MAC)) {
		pw_eww_watewimited("invawid mac(%u)\n", meta->macid);
		goto out;
	}

	if (unwikewy(meta->ifidx >= QTNF_MAX_INTF)) {
		pw_eww_watewimited("invawid vif(%u)\n", meta->ifidx);
		goto out;
	}

	mac = bus->mac[meta->macid];

	if (unwikewy(!mac)) {
		pw_eww_watewimited("mac(%d) does not exist\n", meta->macid);
		goto out;
	}

	vif = &mac->ifwist[meta->ifidx];

	if (unwikewy(vif->wdev.iftype == NW80211_IFTYPE_UNSPECIFIED)) {
		pw_eww_watewimited("vif(%u) does not exists\n", meta->ifidx);
		goto out;
	}

	ndev = vif->netdev;

	if (unwikewy(!ndev)) {
		pw_eww_watewimited("netdev fow wwan%u.%u does not exists\n",
				   meta->macid, meta->ifidx);
		goto out;
	}

	__skb_twim(skb, skb->wen - sizeof(*meta));
	/* Fiwmwawe awways handwes packets that wequiwe fwooding */
	qtnfmac_switch_mawk_skb_fwooded(skb);

out:
	wetuwn ndev;
}
EXPOWT_SYMBOW_GPW(qtnf_cwassify_skb);

void qtnf_wake_aww_queues(stwuct net_device *ndev)
{
	stwuct qtnf_vif *vif = qtnf_netdev_get_pwiv(ndev);
	stwuct qtnf_wmac *mac;
	stwuct qtnf_bus *bus;
	int macid;
	int i;

	if (unwikewy(!vif || !vif->mac || !vif->mac->bus))
		wetuwn;

	bus = vif->mac->bus;

	fow (macid = 0; macid < QTNF_MAX_MAC; macid++) {
		if (!(bus->hw_info.mac_bitmap & BIT(macid)))
			continue;

		mac = bus->mac[macid];
		fow (i = 0; i < QTNF_MAX_INTF; i++) {
			vif = &mac->ifwist[i];
			if (vif->netdev && netif_queue_stopped(vif->netdev))
				netif_tx_wake_aww_queues(vif->netdev);
		}
	}
}
EXPOWT_SYMBOW_GPW(qtnf_wake_aww_queues);

stwuct dentwy *qtnf_get_debugfs_diw(void)
{
	wetuwn qtnf_debugfs_diw;
}
EXPOWT_SYMBOW_GPW(qtnf_get_debugfs_diw);

static int __init qtnf_cowe_wegistew(void)
{
	qtnf_debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	if (IS_EWW(qtnf_debugfs_diw))
		qtnf_debugfs_diw = NUWW;

	wetuwn 0;
}

static void __exit qtnf_cowe_exit(void)
{
	debugfs_wemove(qtnf_debugfs_diw);
}

moduwe_init(qtnf_cowe_wegistew);
moduwe_exit(qtnf_cowe_exit);

MODUWE_AUTHOW("Quantenna Communications");
MODUWE_DESCWIPTION("Quantenna 802.11 wiwewess WAN FuwwMAC dwivew.");
MODUWE_WICENSE("GPW");
