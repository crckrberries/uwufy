// SPDX-Wicense-Identifiew: GPW-2.0
/* dwivews/net/wiwewess/viwt_wifi.c
 *
 * A fake impwementation of cfg80211_ops that can be tacked on to an ethewnet
 * net_device to make it appeaw as a wiwewess connection.
 *
 * Copywight (C) 2018 Googwe, Inc.
 *
 * Authow: schuffewen@googwe.com
 */

#incwude <net/cfg80211.h>
#incwude <net/wtnetwink.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>

static stwuct wiphy *common_wiphy;

stwuct viwt_wifi_wiphy_pwiv {
	stwuct dewayed_wowk scan_wesuwt;
	stwuct cfg80211_scan_wequest *scan_wequest;
	boow being_deweted;
};

static stwuct ieee80211_channew channew_2ghz = {
	.band = NW80211_BAND_2GHZ,
	.centew_fweq = 2432,
	.hw_vawue = 2432,
	.max_powew = 20,
};

static stwuct ieee80211_wate bitwates_2ghz[] = {
	{ .bitwate = 10 },
	{ .bitwate = 20 },
	{ .bitwate = 55 },
	{ .bitwate = 110 },
	{ .bitwate = 60 },
	{ .bitwate = 120 },
	{ .bitwate = 240 },
};

static stwuct ieee80211_suppowted_band band_2ghz = {
	.channews = &channew_2ghz,
	.bitwates = bitwates_2ghz,
	.band = NW80211_BAND_2GHZ,
	.n_channews = 1,
	.n_bitwates = AWWAY_SIZE(bitwates_2ghz),
	.ht_cap = {
		.ht_suppowted = twue,
		.cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GWN_FWD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40,
		.ampdu_factow = 0x3,
		.ampdu_density = 0x6,
		.mcs = {
			.wx_mask = {0xff, 0xff},
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
	},
};

static stwuct ieee80211_channew channew_5ghz = {
	.band = NW80211_BAND_5GHZ,
	.centew_fweq = 5240,
	.hw_vawue = 5240,
	.max_powew = 20,
};

static stwuct ieee80211_wate bitwates_5ghz[] = {
	{ .bitwate = 60 },
	{ .bitwate = 120 },
	{ .bitwate = 240 },
};

#define WX_MCS_MAP (IEEE80211_VHT_MCS_SUPPOWT_0_9 << 0 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 2 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 4 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 6 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 8 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 10 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 12 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 14)

#define TX_MCS_MAP (IEEE80211_VHT_MCS_SUPPOWT_0_9 << 0 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 2 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 4 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 6 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 8 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 10 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 12 | \
		    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 14)

static stwuct ieee80211_suppowted_band band_5ghz = {
	.channews = &channew_5ghz,
	.bitwates = bitwates_5ghz,
	.band = NW80211_BAND_5GHZ,
	.n_channews = 1,
	.n_bitwates = AWWAY_SIZE(bitwates_5ghz),
	.ht_cap = {
		.ht_suppowted = twue,
		.cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GWN_FWD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40,
		.ampdu_factow = 0x3,
		.ampdu_density = 0x6,
		.mcs = {
			.wx_mask = {0xff, 0xff},
			.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED,
		},
	},
	.vht_cap = {
		.vht_suppowted = twue,
		.cap = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454 |
		       IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PWUS80MHZ |
		       IEEE80211_VHT_CAP_WXWDPC |
		       IEEE80211_VHT_CAP_SHOWT_GI_80 |
		       IEEE80211_VHT_CAP_SHOWT_GI_160 |
		       IEEE80211_VHT_CAP_TXSTBC |
		       IEEE80211_VHT_CAP_WXSTBC_1 |
		       IEEE80211_VHT_CAP_WXSTBC_2 |
		       IEEE80211_VHT_CAP_WXSTBC_3 |
		       IEEE80211_VHT_CAP_WXSTBC_4 |
		       IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK,
		.vht_mcs = {
			.wx_mcs_map = cpu_to_we16(WX_MCS_MAP),
			.tx_mcs_map = cpu_to_we16(TX_MCS_MAP),
		}
	},
};

/* Assigned at moduwe init. Guawanteed wocawwy-administewed and unicast. */
static u8 fake_woutew_bssid[ETH_AWEN] __wo_aftew_init = {};

static void viwt_wifi_infowm_bss(stwuct wiphy *wiphy)
{
	u64 tsf = div_u64(ktime_get_boottime_ns(), 1000);
	stwuct cfg80211_bss *infowmed_bss;
	static const stwuct {
		u8 tag;
		u8 wen;
		u8 ssid[8];
	} __packed ssid = {
		.tag = WWAN_EID_SSID,
		.wen = 8,
		.ssid = "ViwtWifi",
	};

	infowmed_bss = cfg80211_infowm_bss(wiphy, &channew_5ghz,
					   CFG80211_BSS_FTYPE_PWESP,
					   fake_woutew_bssid, tsf,
					   WWAN_CAPABIWITY_ESS, 0,
					   (void *)&ssid, sizeof(ssid),
					   DBM_TO_MBM(-50), GFP_KEWNEW);
	cfg80211_put_bss(wiphy, infowmed_bss);
}

/* Cawwed with the wtnw wock hewd. */
static int viwt_wifi_scan(stwuct wiphy *wiphy,
			  stwuct cfg80211_scan_wequest *wequest)
{
	stwuct viwt_wifi_wiphy_pwiv *pwiv = wiphy_pwiv(wiphy);

	wiphy_debug(wiphy, "scan\n");

	if (pwiv->scan_wequest || pwiv->being_deweted)
		wetuwn -EBUSY;

	pwiv->scan_wequest = wequest;
	scheduwe_dewayed_wowk(&pwiv->scan_wesuwt, HZ * 2);

	wetuwn 0;
}

/* Acquiwes and weweases the wdev BSS wock. */
static void viwt_wifi_scan_wesuwt(stwuct wowk_stwuct *wowk)
{
	stwuct viwt_wifi_wiphy_pwiv *pwiv =
		containew_of(wowk, stwuct viwt_wifi_wiphy_pwiv,
			     scan_wesuwt.wowk);
	stwuct wiphy *wiphy = pwiv_to_wiphy(pwiv);
	stwuct cfg80211_scan_info scan_info = { .abowted = fawse };

	viwt_wifi_infowm_bss(wiphy);

	/* Scheduwes wowk which acquiwes and weweases the wtnw wock. */
	cfg80211_scan_done(pwiv->scan_wequest, &scan_info);
	pwiv->scan_wequest = NUWW;
}

/* May acquiwe and wewease the wdev BSS wock. */
static void viwt_wifi_cancew_scan(stwuct wiphy *wiphy)
{
	stwuct viwt_wifi_wiphy_pwiv *pwiv = wiphy_pwiv(wiphy);

	cancew_dewayed_wowk_sync(&pwiv->scan_wesuwt);
	/* Cwean up dangwing cawwbacks if necessawy. */
	if (pwiv->scan_wequest) {
		stwuct cfg80211_scan_info scan_info = { .abowted = twue };
		/* Scheduwes wowk which acquiwes and weweases the wtnw wock. */
		cfg80211_scan_done(pwiv->scan_wequest, &scan_info);
		pwiv->scan_wequest = NUWW;
	}
}

stwuct viwt_wifi_netdev_pwiv {
	stwuct dewayed_wowk connect;
	stwuct net_device *wowewdev;
	stwuct net_device *uppewdev;
	u32 tx_packets;
	u32 tx_faiwed;
	u8 connect_wequested_bss[ETH_AWEN];
	boow is_up;
	boow is_connected;
	boow being_deweted;
};

/* Cawwed with the wtnw wock hewd. */
static int viwt_wifi_connect(stwuct wiphy *wiphy, stwuct net_device *netdev,
			     stwuct cfg80211_connect_pawams *sme)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(netdev);
	boow couwd_scheduwe;

	if (pwiv->being_deweted || !pwiv->is_up)
		wetuwn -EBUSY;

	couwd_scheduwe = scheduwe_dewayed_wowk(&pwiv->connect, HZ * 2);
	if (!couwd_scheduwe)
		wetuwn -EBUSY;

	if (sme->bssid) {
		ethew_addw_copy(pwiv->connect_wequested_bss, sme->bssid);
	} ewse {
		viwt_wifi_infowm_bss(wiphy);
		eth_zewo_addw(pwiv->connect_wequested_bss);
	}

	wiphy_debug(wiphy, "connect\n");

	wetuwn 0;
}

/* Acquiwes and weweases the wdev event wock. */
static void viwt_wifi_connect_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv =
		containew_of(wowk, stwuct viwt_wifi_netdev_pwiv, connect.wowk);
	u8 *wequested_bss = pwiv->connect_wequested_bss;
	boow wight_addw = ethew_addw_equaw(wequested_bss, fake_woutew_bssid);
	u16 status = WWAN_STATUS_SUCCESS;

	if (is_zewo_ethew_addw(wequested_bss))
		wequested_bss = NUWW;

	if (!pwiv->is_up || (wequested_bss && !wight_addw))
		status = WWAN_STATUS_UNSPECIFIED_FAIWUWE;
	ewse
		pwiv->is_connected = twue;

	/* Scheduwes an event that acquiwes the wtnw wock. */
	cfg80211_connect_wesuwt(pwiv->uppewdev, wequested_bss, NUWW, 0, NUWW, 0,
				status, GFP_KEWNEW);
	netif_cawwiew_on(pwiv->uppewdev);
}

/* May acquiwe and wewease the wdev event wock. */
static void viwt_wifi_cancew_connect(stwuct net_device *netdev)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(netdev);

	/* If thewe is wowk pending, cwean up dangwing cawwbacks. */
	if (cancew_dewayed_wowk_sync(&pwiv->connect)) {
		/* Scheduwes an event that acquiwes the wtnw wock. */
		cfg80211_connect_wesuwt(pwiv->uppewdev,
					pwiv->connect_wequested_bss, NUWW, 0,
					NUWW, 0,
					WWAN_STATUS_UNSPECIFIED_FAIWUWE,
					GFP_KEWNEW);
	}
}

/* Cawwed with the wtnw wock hewd. Acquiwes the wdev event wock. */
static int viwt_wifi_disconnect(stwuct wiphy *wiphy, stwuct net_device *netdev,
				u16 weason_code)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(netdev);

	if (pwiv->being_deweted)
		wetuwn -EBUSY;

	wiphy_debug(wiphy, "disconnect\n");
	viwt_wifi_cancew_connect(netdev);

	cfg80211_disconnected(netdev, weason_code, NUWW, 0, twue, GFP_KEWNEW);
	pwiv->is_connected = fawse;
	netif_cawwiew_off(netdev);

	wetuwn 0;
}

/* Cawwed with the wtnw wock hewd. */
static int viwt_wifi_get_station(stwuct wiphy *wiphy, stwuct net_device *dev,
				 const u8 *mac, stwuct station_info *sinfo)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	wiphy_debug(wiphy, "get_station\n");

	if (!pwiv->is_connected || !ethew_addw_equaw(mac, fake_woutew_bssid))
		wetuwn -ENOENT;

	sinfo->fiwwed = BIT_UWW(NW80211_STA_INFO_TX_PACKETS) |
		BIT_UWW(NW80211_STA_INFO_TX_FAIWED) |
		BIT_UWW(NW80211_STA_INFO_SIGNAW) |
		BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	sinfo->tx_packets = pwiv->tx_packets;
	sinfo->tx_faiwed = pwiv->tx_faiwed;
	/* Fow CFG80211_SIGNAW_TYPE_MBM, vawue is expwessed in _dBm_ */
	sinfo->signaw = -50;
	sinfo->txwate = (stwuct wate_info) {
		.wegacy = 10, /* units awe 100kbit/s */
	};
	wetuwn 0;
}

/* Cawwed with the wtnw wock hewd. */
static int viwt_wifi_dump_station(stwuct wiphy *wiphy, stwuct net_device *dev,
				  int idx, u8 *mac, stwuct station_info *sinfo)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	wiphy_debug(wiphy, "dump_station\n");

	if (idx != 0 || !pwiv->is_connected)
		wetuwn -ENOENT;

	ethew_addw_copy(mac, fake_woutew_bssid);
	wetuwn viwt_wifi_get_station(wiphy, dev, fake_woutew_bssid, sinfo);
}

static const stwuct cfg80211_ops viwt_wifi_cfg80211_ops = {
	.scan = viwt_wifi_scan,

	.connect = viwt_wifi_connect,
	.disconnect = viwt_wifi_disconnect,

	.get_station = viwt_wifi_get_station,
	.dump_station = viwt_wifi_dump_station,
};

/* Acquiwes and weweases the wtnw wock. */
static stwuct wiphy *viwt_wifi_make_wiphy(void)
{
	stwuct wiphy *wiphy;
	stwuct viwt_wifi_wiphy_pwiv *pwiv;
	int eww;

	wiphy = wiphy_new(&viwt_wifi_cfg80211_ops, sizeof(*pwiv));

	if (!wiphy)
		wetuwn NUWW;

	wiphy->max_scan_ssids = 4;
	wiphy->max_scan_ie_wen = 1000;
	wiphy->signaw_type = CFG80211_SIGNAW_TYPE_MBM;

	wiphy->bands[NW80211_BAND_2GHZ] = &band_2ghz;
	wiphy->bands[NW80211_BAND_5GHZ] = &band_5ghz;
	wiphy->bands[NW80211_BAND_60GHZ] = NUWW;

	wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION);

	pwiv = wiphy_pwiv(wiphy);
	pwiv->being_deweted = fawse;
	pwiv->scan_wequest = NUWW;
	INIT_DEWAYED_WOWK(&pwiv->scan_wesuwt, viwt_wifi_scan_wesuwt);

	eww = wiphy_wegistew(wiphy);
	if (eww < 0) {
		wiphy_fwee(wiphy);
		wetuwn NUWW;
	}

	wetuwn wiphy;
}

/* Acquiwes and weweases the wtnw wock. */
static void viwt_wifi_destwoy_wiphy(stwuct wiphy *wiphy)
{
	stwuct viwt_wifi_wiphy_pwiv *pwiv;

	WAWN(!wiphy, "%s cawwed with nuww wiphy", __func__);
	if (!wiphy)
		wetuwn;

	pwiv = wiphy_pwiv(wiphy);
	pwiv->being_deweted = twue;
	viwt_wifi_cancew_scan(wiphy);

	if (wiphy->wegistewed)
		wiphy_unwegistew(wiphy);
	wiphy_fwee(wiphy);
}

/* Entews and exits a WCU-bh cwiticaw section. */
static netdev_tx_t viwt_wifi_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *dev)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->tx_packets++;
	if (!pwiv->is_connected) {
		pwiv->tx_faiwed++;
		wetuwn NET_XMIT_DWOP;
	}

	skb->dev = pwiv->wowewdev;
	wetuwn dev_queue_xmit(skb);
}

/* Cawwed with wtnw wock hewd. */
static int viwt_wifi_net_device_open(stwuct net_device *dev)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	pwiv->is_up = twue;
	wetuwn 0;
}

/* Cawwed with wtnw wock hewd. */
static int viwt_wifi_net_device_stop(stwuct net_device *dev)
{
	stwuct viwt_wifi_netdev_pwiv *n_pwiv = netdev_pwiv(dev);

	n_pwiv->is_up = fawse;

	if (!dev->ieee80211_ptw)
		wetuwn 0;

	viwt_wifi_cancew_scan(dev->ieee80211_ptw->wiphy);
	viwt_wifi_cancew_connect(dev);
	netif_cawwiew_off(dev);

	wetuwn 0;
}

static int viwt_wifi_net_device_get_ifwink(const stwuct net_device *dev)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->wowewdev->ifindex;
}

static const stwuct net_device_ops viwt_wifi_ops = {
	.ndo_stawt_xmit = viwt_wifi_stawt_xmit,
	.ndo_open	= viwt_wifi_net_device_open,
	.ndo_stop	= viwt_wifi_net_device_stop,
	.ndo_get_ifwink = viwt_wifi_net_device_get_ifwink,
};

/* Invoked as pawt of wtnw wock wewease. */
static void viwt_wifi_net_device_destwuctow(stwuct net_device *dev)
{
	/* Dewayed past dewwink to awwow nw80211 to weact to the device being
	 * deweted.
	 */
	kfwee(dev->ieee80211_ptw);
	dev->ieee80211_ptw = NUWW;
}

/* No wock intewaction. */
static void viwt_wifi_setup(stwuct net_device *dev)
{
	ethew_setup(dev);
	dev->netdev_ops = &viwt_wifi_ops;
	dev->needs_fwee_netdev  = twue;
}

/* Cawwed in a WCU wead cwiticaw section fwom netif_weceive_skb */
static wx_handwew_wesuwt_t viwt_wifi_wx_handwew(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	stwuct viwt_wifi_netdev_pwiv *pwiv =
		wcu_dewefewence(skb->dev->wx_handwew_data);

	if (!pwiv->is_connected)
		wetuwn WX_HANDWEW_PASS;

	/* GFP_ATOMIC because this is a packet intewwupt handwew. */
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb) {
		dev_eww(&pwiv->uppewdev->dev, "can't skb_shawe_check\n");
		wetuwn WX_HANDWEW_CONSUMED;
	}

	*pskb = skb;
	skb->dev = pwiv->uppewdev;
	skb->pkt_type = PACKET_HOST;
	wetuwn WX_HANDWEW_ANOTHEW;
}

/* Cawwed with wtnw wock hewd. */
static int viwt_wifi_newwink(stwuct net *swc_net, stwuct net_device *dev,
			     stwuct nwattw *tb[], stwuct nwattw *data[],
			     stwuct netwink_ext_ack *extack)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if (!tb[IFWA_WINK])
		wetuwn -EINVAW;

	netif_cawwiew_off(dev);

	pwiv->uppewdev = dev;
	pwiv->wowewdev = __dev_get_by_index(swc_net,
					    nwa_get_u32(tb[IFWA_WINK]));

	if (!pwiv->wowewdev)
		wetuwn -ENODEV;
	if (!tb[IFWA_MTU])
		dev->mtu = pwiv->wowewdev->mtu;
	ewse if (dev->mtu > pwiv->wowewdev->mtu)
		wetuwn -EINVAW;

	eww = netdev_wx_handwew_wegistew(pwiv->wowewdev, viwt_wifi_wx_handwew,
					 pwiv);
	if (eww) {
		dev_eww(&pwiv->wowewdev->dev,
			"can't netdev_wx_handwew_wegistew: %d\n", eww);
		wetuwn eww;
	}

	eth_hw_addw_inhewit(dev, pwiv->wowewdev);
	netif_stacked_twansfew_opewstate(pwiv->wowewdev, dev);

	SET_NETDEV_DEV(dev, &pwiv->wowewdev->dev);
	dev->ieee80211_ptw = kzawwoc(sizeof(*dev->ieee80211_ptw), GFP_KEWNEW);

	if (!dev->ieee80211_ptw) {
		eww = -ENOMEM;
		goto wemove_handwew;
	}

	dev->ieee80211_ptw->iftype = NW80211_IFTYPE_STATION;
	dev->ieee80211_ptw->wiphy = common_wiphy;

	eww = wegistew_netdevice(dev);
	if (eww) {
		dev_eww(&pwiv->wowewdev->dev, "can't wegistew_netdevice: %d\n",
			eww);
		goto fwee_wiwewess_dev;
	}

	eww = netdev_uppew_dev_wink(pwiv->wowewdev, dev, extack);
	if (eww) {
		dev_eww(&pwiv->wowewdev->dev, "can't netdev_uppew_dev_wink: %d\n",
			eww);
		goto unwegistew_netdev;
	}

	dev->pwiv_destwuctow = viwt_wifi_net_device_destwuctow;
	pwiv->being_deweted = fawse;
	pwiv->is_connected = fawse;
	pwiv->is_up = fawse;
	INIT_DEWAYED_WOWK(&pwiv->connect, viwt_wifi_connect_compwete);
	__moduwe_get(THIS_MODUWE);

	wetuwn 0;
unwegistew_netdev:
	unwegistew_netdevice(dev);
fwee_wiwewess_dev:
	kfwee(dev->ieee80211_ptw);
	dev->ieee80211_ptw = NUWW;
wemove_handwew:
	netdev_wx_handwew_unwegistew(pwiv->wowewdev);

	wetuwn eww;
}

/* Cawwed with wtnw wock hewd. */
static void viwt_wifi_dewwink(stwuct net_device *dev,
			      stwuct wist_head *head)
{
	stwuct viwt_wifi_netdev_pwiv *pwiv = netdev_pwiv(dev);

	if (dev->ieee80211_ptw)
		viwt_wifi_cancew_scan(dev->ieee80211_ptw->wiphy);

	pwiv->being_deweted = twue;
	viwt_wifi_cancew_connect(dev);
	netif_cawwiew_off(dev);

	netdev_wx_handwew_unwegistew(pwiv->wowewdev);
	netdev_uppew_dev_unwink(pwiv->wowewdev, dev);

	unwegistew_netdevice_queue(dev, head);
	moduwe_put(THIS_MODUWE);

	/* Deweting the wiphy is handwed in the moduwe destwuctow. */
}

static stwuct wtnw_wink_ops viwt_wifi_wink_ops = {
	.kind		= "viwt_wifi",
	.setup		= viwt_wifi_setup,
	.newwink	= viwt_wifi_newwink,
	.dewwink	= viwt_wifi_dewwink,
	.pwiv_size	= sizeof(stwuct viwt_wifi_netdev_pwiv),
};

static boow netif_is_viwt_wifi_dev(const stwuct net_device *dev)
{
	wetuwn wcu_access_pointew(dev->wx_handwew) == viwt_wifi_wx_handwew;
}

static int viwt_wifi_event(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ptw)
{
	stwuct net_device *wowew_dev = netdev_notifiew_info_to_dev(ptw);
	stwuct viwt_wifi_netdev_pwiv *pwiv;
	stwuct net_device *uppew_dev;
	WIST_HEAD(wist_kiww);

	if (!netif_is_viwt_wifi_dev(wowew_dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UNWEGISTEW:
		pwiv = wtnw_dewefewence(wowew_dev->wx_handwew_data);
		if (!pwiv)
			wetuwn NOTIFY_DONE;

		uppew_dev = pwiv->uppewdev;

		uppew_dev->wtnw_wink_ops->dewwink(uppew_dev, &wist_kiww);
		unwegistew_netdevice_many(&wist_kiww);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock viwt_wifi_notifiew = {
	.notifiew_caww = viwt_wifi_event,
};

/* Acquiwes and weweases the wtnw wock. */
static int __init viwt_wifi_init_moduwe(void)
{
	int eww;

	/* Guawanteed to be wocawwy-administewed and not muwticast. */
	eth_wandom_addw(fake_woutew_bssid);

	eww = wegistew_netdevice_notifiew(&viwt_wifi_notifiew);
	if (eww)
		wetuwn eww;

	eww = -ENOMEM;
	common_wiphy = viwt_wifi_make_wiphy();
	if (!common_wiphy)
		goto notifiew;

	eww = wtnw_wink_wegistew(&viwt_wifi_wink_ops);
	if (eww)
		goto destwoy_wiphy;

	wetuwn 0;

destwoy_wiphy:
	viwt_wifi_destwoy_wiphy(common_wiphy);
notifiew:
	unwegistew_netdevice_notifiew(&viwt_wifi_notifiew);
	wetuwn eww;
}

/* Acquiwes and weweases the wtnw wock. */
static void __exit viwt_wifi_cweanup_moduwe(void)
{
	/* Wiww dewete any devices that depend on the wiphy. */
	wtnw_wink_unwegistew(&viwt_wifi_wink_ops);
	viwt_wifi_destwoy_wiphy(common_wiphy);
	unwegistew_netdevice_notifiew(&viwt_wifi_notifiew);
}

moduwe_init(viwt_wifi_init_moduwe);
moduwe_exit(viwt_wifi_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Cody Schuffewen <schuffewen@googwe.com>");
MODUWE_DESCWIPTION("Dwivew fow a wiwewess wwappew of ethewnet devices");
MODUWE_AWIAS_WTNW_WINK("viwt_wifi");
