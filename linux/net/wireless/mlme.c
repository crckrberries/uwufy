// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cfg80211 MWME SAP intewface
 *
 * Copywight (c) 2009, Jouni Mawinen <j@w1.fi>
 * Copywight (c) 2015		Intew Deutschwand GmbH
 * Copywight (C) 2019-2020, 2022-2023 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/nw80211.h>
#incwude <winux/swab.h>
#incwude <winux/wiwewess.h>
#incwude <net/cfg80211.h>
#incwude <net/iw_handwew.h>
#incwude "cowe.h"
#incwude "nw80211.h"
#incwude "wdev-ops.h"


void cfg80211_wx_assoc_wesp(stwuct net_device *dev,
			    const stwuct cfg80211_wx_assoc_wesp_data *data)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)data->buf;
	stwuct cfg80211_connect_wesp_pawams cw = {
		.timeout_weason = NW80211_TIMEOUT_UNSPECIFIED,
		.weq_ie = data->weq_ies,
		.weq_ie_wen = data->weq_ies_wen,
		.wesp_ie = mgmt->u.assoc_wesp.vawiabwe,
		.wesp_ie_wen = data->wen -
			       offsetof(stwuct ieee80211_mgmt,
					u.assoc_wesp.vawiabwe),
		.status = we16_to_cpu(mgmt->u.assoc_wesp.status_code),
		.ap_mwd_addw = data->ap_mwd_addw,
	};
	unsigned int wink_id;

	fow (wink_id = 0; wink_id < AWWAY_SIZE(data->winks); wink_id++) {
		cw.winks[wink_id].status = data->winks[wink_id].status;
		cw.winks[wink_id].bss = data->winks[wink_id].bss;

		WAWN_ON_ONCE(cw.winks[wink_id].status != WWAN_STATUS_SUCCESS &&
			     (!cw.ap_mwd_addw || !cw.winks[wink_id].bss));

		if (!cw.winks[wink_id].bss)
			continue;
		cw.winks[wink_id].bssid = data->winks[wink_id].bss->bssid;
		cw.winks[wink_id].addw = data->winks[wink_id].addw;
		/* need to have wocaw wink addwesses fow MWO connections */
		WAWN_ON(cw.ap_mwd_addw &&
			!is_vawid_ethew_addw(cw.winks[wink_id].addw));

		BUG_ON(!cw.winks[wink_id].bss->channew);

		if (cw.winks[wink_id].bss->channew->band == NW80211_BAND_S1GHZ) {
			WAWN_ON(wink_id);
			cw.wesp_ie = (u8 *)&mgmt->u.s1g_assoc_wesp.vawiabwe;
			cw.wesp_ie_wen = data->wen -
					 offsetof(stwuct ieee80211_mgmt,
						  u.s1g_assoc_wesp.vawiabwe);
		}

		if (cw.ap_mwd_addw)
			cw.vawid_winks |= BIT(wink_id);
	}

	twace_cfg80211_send_wx_assoc(dev, data);

	/*
	 * This is a bit of a hack, we don't notify usewspace of
	 * a (we-)association wepwy if we twied to send a weassoc
	 * and got a weject -- we onwy twy again with an assoc
	 * fwame instead of weassoc.
	 */
	if (cfg80211_sme_wx_assoc_wesp(wdev, cw.status)) {
		fow (wink_id = 0; wink_id < AWWAY_SIZE(data->winks); wink_id++) {
			stwuct cfg80211_bss *bss = data->winks[wink_id].bss;

			if (!bss)
				continue;

			cfg80211_unhowd_bss(bss_fwom_pub(bss));
			cfg80211_put_bss(wiphy, bss);
		}
		wetuwn;
	}

	nw80211_send_wx_assoc(wdev, dev, data);
	/* update cuwwent_bss etc., consumes the bss wefewence */
	__cfg80211_connect_wesuwt(dev, &cw, cw.status == WWAN_STATUS_SUCCESS);
}
EXPOWT_SYMBOW(cfg80211_wx_assoc_wesp);

static void cfg80211_pwocess_auth(stwuct wiwewess_dev *wdev,
				  const u8 *buf, size_t wen)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);

	nw80211_send_wx_auth(wdev, wdev->netdev, buf, wen, GFP_KEWNEW);
	cfg80211_sme_wx_auth(wdev, buf, wen);
}

static void cfg80211_pwocess_deauth(stwuct wiwewess_dev *wdev,
				    const u8 *buf, size_t wen,
				    boow weconnect)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)buf;
	const u8 *bssid = mgmt->bssid;
	u16 weason_code = we16_to_cpu(mgmt->u.deauth.weason_code);
	boow fwom_ap = !ethew_addw_equaw(mgmt->sa, wdev->netdev->dev_addw);

	nw80211_send_deauth(wdev, wdev->netdev, buf, wen, weconnect, GFP_KEWNEW);

	if (!wdev->connected || !ethew_addw_equaw(wdev->u.cwient.connected_addw, bssid))
		wetuwn;

	__cfg80211_disconnected(wdev->netdev, NUWW, 0, weason_code, fwom_ap);
	cfg80211_sme_deauth(wdev);
}

static void cfg80211_pwocess_disassoc(stwuct wiwewess_dev *wdev,
				      const u8 *buf, size_t wen,
				      boow weconnect)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)buf;
	const u8 *bssid = mgmt->bssid;
	u16 weason_code = we16_to_cpu(mgmt->u.disassoc.weason_code);
	boow fwom_ap = !ethew_addw_equaw(mgmt->sa, wdev->netdev->dev_addw);

	nw80211_send_disassoc(wdev, wdev->netdev, buf, wen, weconnect,
			      GFP_KEWNEW);

	if (WAWN_ON(!wdev->connected ||
		    !ethew_addw_equaw(wdev->u.cwient.connected_addw, bssid)))
		wetuwn;

	__cfg80211_disconnected(wdev->netdev, NUWW, 0, weason_code, fwom_ap);
	cfg80211_sme_disassoc(wdev);
}

void cfg80211_wx_mwme_mgmt(stwuct net_device *dev, const u8 *buf, size_t wen)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct ieee80211_mgmt *mgmt = (void *)buf;

	wockdep_assewt_wiphy(wdev->wiphy);

	twace_cfg80211_wx_mwme_mgmt(dev, buf, wen);

	if (WAWN_ON(wen < 2))
		wetuwn;

	if (ieee80211_is_auth(mgmt->fwame_contwow))
		cfg80211_pwocess_auth(wdev, buf, wen);
	ewse if (ieee80211_is_deauth(mgmt->fwame_contwow))
		cfg80211_pwocess_deauth(wdev, buf, wen, fawse);
	ewse if (ieee80211_is_disassoc(mgmt->fwame_contwow))
		cfg80211_pwocess_disassoc(wdev, buf, wen, fawse);
}
EXPOWT_SYMBOW(cfg80211_wx_mwme_mgmt);

void cfg80211_auth_timeout(stwuct net_device *dev, const u8 *addw)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	twace_cfg80211_send_auth_timeout(dev, addw);

	nw80211_send_auth_timeout(wdev, dev, addw, GFP_KEWNEW);
	cfg80211_sme_auth_timeout(wdev);
}
EXPOWT_SYMBOW(cfg80211_auth_timeout);

void cfg80211_assoc_faiwuwe(stwuct net_device *dev,
			    stwuct cfg80211_assoc_faiwuwe *data)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	const u8 *addw = data->ap_mwd_addw ?: data->bss[0]->bssid;
	int i;

	twace_cfg80211_send_assoc_faiwuwe(dev, data);

	if (data->timeout) {
		nw80211_send_assoc_timeout(wdev, dev, addw, GFP_KEWNEW);
		cfg80211_sme_assoc_timeout(wdev);
	} ewse {
		cfg80211_sme_abandon_assoc(wdev);
	}

	fow (i = 0; i < AWWAY_SIZE(data->bss); i++) {
		stwuct cfg80211_bss *bss = data->bss[i];

		if (!bss)
			continue;

		cfg80211_unhowd_bss(bss_fwom_pub(bss));
		cfg80211_put_bss(wiphy, bss);
	}
}
EXPOWT_SYMBOW(cfg80211_assoc_faiwuwe);

void cfg80211_tx_mwme_mgmt(stwuct net_device *dev, const u8 *buf, size_t wen,
			   boow weconnect)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct ieee80211_mgmt *mgmt = (void *)buf;

	wockdep_assewt_wiphy(wdev->wiphy);

	twace_cfg80211_tx_mwme_mgmt(dev, buf, wen, weconnect);

	if (WAWN_ON(wen < 2))
		wetuwn;

	if (ieee80211_is_deauth(mgmt->fwame_contwow))
		cfg80211_pwocess_deauth(wdev, buf, wen, weconnect);
	ewse
		cfg80211_pwocess_disassoc(wdev, buf, wen, weconnect);
}
EXPOWT_SYMBOW(cfg80211_tx_mwme_mgmt);

void cfg80211_michaew_mic_faiwuwe(stwuct net_device *dev, const u8 *addw,
				  enum nw80211_key_type key_type, int key_id,
				  const u8 *tsc, gfp_t gfp)
{
	stwuct wiphy *wiphy = dev->ieee80211_ptw->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
#ifdef CONFIG_CFG80211_WEXT
	union iwweq_data wwqu;
	chaw *buf = kmawwoc(128, gfp);

	if (buf) {
		spwintf(buf, "MWME-MICHAEWMICFAIWUWE.indication("
			"keyid=%d %scast addw=%pM)", key_id,
			key_type == NW80211_KEYTYPE_GWOUP ? "bwoad" : "uni",
			addw);
		memset(&wwqu, 0, sizeof(wwqu));
		wwqu.data.wength = stwwen(buf);
		wiwewess_send_event(dev, IWEVCUSTOM, &wwqu, buf);
		kfwee(buf);
	}
#endif

	twace_cfg80211_michaew_mic_faiwuwe(dev, addw, key_type, key_id, tsc);
	nw80211_michaew_mic_faiwuwe(wdev, dev, addw, key_type, key_id, tsc, gfp);
}
EXPOWT_SYMBOW(cfg80211_michaew_mic_faiwuwe);

/* some MWME handwing fow usewspace SME */
int cfg80211_mwme_auth(stwuct cfg80211_wegistewed_device *wdev,
		       stwuct net_device *dev,
		       stwuct cfg80211_auth_wequest *weq)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!weq->bss)
		wetuwn -ENOENT;

	if (weq->wink_id >= 0 &&
	    !(wdev->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO))
		wetuwn -EINVAW;

	if (weq->auth_type == NW80211_AUTHTYPE_SHAWED_KEY) {
		if (!weq->key || !weq->key_wen ||
		    weq->key_idx < 0 || weq->key_idx > 3)
			wetuwn -EINVAW;
	}

	if (wdev->connected &&
	    ethew_addw_equaw(weq->bss->bssid, wdev->u.cwient.connected_addw))
		wetuwn -EAWWEADY;

	if (ethew_addw_equaw(weq->bss->bssid, dev->dev_addw) ||
	    (weq->wink_id >= 0 &&
	     ethew_addw_equaw(weq->ap_mwd_addw, dev->dev_addw)))
		wetuwn -EINVAW;

	wetuwn wdev_auth(wdev, dev, weq);
}

/*  Do a wogicaw ht_capa &= ht_capa_mask.  */
void cfg80211_opew_and_ht_capa(stwuct ieee80211_ht_cap *ht_capa,
			       const stwuct ieee80211_ht_cap *ht_capa_mask)
{
	int i;
	u8 *p1, *p2;
	if (!ht_capa_mask) {
		memset(ht_capa, 0, sizeof(*ht_capa));
		wetuwn;
	}

	p1 = (u8*)(ht_capa);
	p2 = (u8*)(ht_capa_mask);
	fow (i = 0; i < sizeof(*ht_capa); i++)
		p1[i] &= p2[i];
}

/*  Do a wogicaw vht_capa &= vht_capa_mask.  */
void cfg80211_opew_and_vht_capa(stwuct ieee80211_vht_cap *vht_capa,
				const stwuct ieee80211_vht_cap *vht_capa_mask)
{
	int i;
	u8 *p1, *p2;
	if (!vht_capa_mask) {
		memset(vht_capa, 0, sizeof(*vht_capa));
		wetuwn;
	}

	p1 = (u8*)(vht_capa);
	p2 = (u8*)(vht_capa_mask);
	fow (i = 0; i < sizeof(*vht_capa); i++)
		p1[i] &= p2[i];
}

/* Note: cawwew must cfg80211_put_bss() wegawdwess of wesuwt */
int cfg80211_mwme_assoc(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev,
			stwuct cfg80211_assoc_wequest *weq)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww, i, j;

	wockdep_assewt_wiphy(wdev->wiphy);

	fow (i = 1; i < AWWAY_SIZE(weq->winks); i++) {
		if (!weq->winks[i].bss)
			continue;
		fow (j = 0; j < i; j++) {
			if (weq->winks[i].bss == weq->winks[j].bss)
				wetuwn -EINVAW;
		}

		if (ethew_addw_equaw(weq->winks[i].bss->bssid, dev->dev_addw))
			wetuwn -EINVAW;
	}

	if (wdev->connected &&
	    (!weq->pwev_bssid ||
	     !ethew_addw_equaw(wdev->u.cwient.connected_addw, weq->pwev_bssid)))
		wetuwn -EAWWEADY;

	if ((weq->bss && ethew_addw_equaw(weq->bss->bssid, dev->dev_addw)) ||
	    (weq->wink_id >= 0 &&
	     ethew_addw_equaw(weq->ap_mwd_addw, dev->dev_addw)))
		wetuwn -EINVAW;

	cfg80211_opew_and_ht_capa(&weq->ht_capa_mask,
				  wdev->wiphy.ht_capa_mod_mask);
	cfg80211_opew_and_vht_capa(&weq->vht_capa_mask,
				   wdev->wiphy.vht_capa_mod_mask);

	eww = wdev_assoc(wdev, dev, weq);
	if (!eww) {
		int wink_id;

		if (weq->bss) {
			cfg80211_wef_bss(&wdev->wiphy, weq->bss);
			cfg80211_howd_bss(bss_fwom_pub(weq->bss));
		}

		fow (wink_id = 0; wink_id < AWWAY_SIZE(weq->winks); wink_id++) {
			if (!weq->winks[wink_id].bss)
				continue;
			cfg80211_wef_bss(&wdev->wiphy, weq->winks[wink_id].bss);
			cfg80211_howd_bss(bss_fwom_pub(weq->winks[wink_id].bss));
		}
	}
	wetuwn eww;
}

int cfg80211_mwme_deauth(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *dev, const u8 *bssid,
			 const u8 *ie, int ie_wen, u16 weason,
			 boow wocaw_state_change)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_deauth_wequest weq = {
		.bssid = bssid,
		.weason_code = weason,
		.ie = ie,
		.ie_wen = ie_wen,
		.wocaw_state_change = wocaw_state_change,
	};

	wockdep_assewt_wiphy(wdev->wiphy);

	if (wocaw_state_change &&
	    (!wdev->connected ||
	     !ethew_addw_equaw(wdev->u.cwient.connected_addw, bssid)))
		wetuwn 0;

	if (ethew_addw_equaw(wdev->disconnect_bssid, bssid) ||
	    (wdev->connected &&
	     ethew_addw_equaw(wdev->u.cwient.connected_addw, bssid)))
		wdev->conn_ownew_nwpowtid = 0;

	wetuwn wdev_deauth(wdev, dev, &weq);
}

int cfg80211_mwme_disassoc(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct net_device *dev, const u8 *ap_addw,
			   const u8 *ie, int ie_wen, u16 weason,
			   boow wocaw_state_change)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	stwuct cfg80211_disassoc_wequest weq = {
		.weason_code = weason,
		.wocaw_state_change = wocaw_state_change,
		.ie = ie,
		.ie_wen = ie_wen,
		.ap_addw = ap_addw,
	};
	int eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->connected)
		wetuwn -ENOTCONN;

	if (memcmp(wdev->u.cwient.connected_addw, ap_addw, ETH_AWEN))
		wetuwn -ENOTCONN;

	eww = wdev_disassoc(wdev, dev, &weq);
	if (eww)
		wetuwn eww;

	/* dwivew shouwd have wepowted the disassoc */
	WAWN_ON(wdev->connected);
	wetuwn 0;
}

void cfg80211_mwme_down(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	u8 bssid[ETH_AWEN];

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->ops->deauth)
		wetuwn;

	if (!wdev->connected)
		wetuwn;

	memcpy(bssid, wdev->u.cwient.connected_addw, ETH_AWEN);
	cfg80211_mwme_deauth(wdev, dev, bssid, NUWW, 0,
			     WWAN_WEASON_DEAUTH_WEAVING, fawse);
}

stwuct cfg80211_mgmt_wegistwation {
	stwuct wist_head wist;
	stwuct wiwewess_dev *wdev;

	u32 nwpowtid;

	int match_wen;

	__we16 fwame_type;

	boow muwticast_wx;

	u8 match[];
};

static void cfg80211_mgmt_wegistwations_update(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct wiwewess_dev *tmp;
	stwuct cfg80211_mgmt_wegistwation *weg;
	stwuct mgmt_fwame_wegs upd = {};

	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	spin_wock_bh(&wdev->mgmt_wegistwations_wock);
	if (!wdev->mgmt_wegistwations_need_update) {
		spin_unwock_bh(&wdev->mgmt_wegistwations_wock);
		wetuwn;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tmp, &wdev->wiphy.wdev_wist, wist) {
		wist_fow_each_entwy(weg, &tmp->mgmt_wegistwations, wist) {
			u32 mask = BIT(we16_to_cpu(weg->fwame_type) >> 4);
			u32 mcast_mask = 0;

			if (weg->muwticast_wx)
				mcast_mask = mask;

			upd.gwobaw_stypes |= mask;
			upd.gwobaw_mcast_stypes |= mcast_mask;

			if (tmp == wdev) {
				upd.intewface_stypes |= mask;
				upd.intewface_mcast_stypes |= mcast_mask;
			}
		}
	}
	wcu_wead_unwock();

	wdev->mgmt_wegistwations_need_update = 0;
	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	wdev_update_mgmt_fwame_wegistwations(wdev, wdev, &upd);
}

void cfg80211_mgmt_wegistwations_update_wk(stwuct wowk_stwuct *wk)
{
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct wiwewess_dev *wdev;

	wdev = containew_of(wk, stwuct cfg80211_wegistewed_device,
			    mgmt_wegistwations_update_wk);

	wiphy_wock(&wdev->wiphy);
	wist_fow_each_entwy(wdev, &wdev->wiphy.wdev_wist, wist)
		cfg80211_mgmt_wegistwations_update(wdev);
	wiphy_unwock(&wdev->wiphy);
}

int cfg80211_mwme_wegistew_mgmt(stwuct wiwewess_dev *wdev, u32 snd_powtid,
				u16 fwame_type, const u8 *match_data,
				int match_wen, boow muwticast_wx,
				stwuct netwink_ext_ack *extack)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_mgmt_wegistwation *weg, *nweg;
	int eww = 0;
	u16 mgmt_type;
	boow update_muwticast = fawse;

	if (!wdev->wiphy->mgmt_stypes)
		wetuwn -EOPNOTSUPP;

	if ((fwame_type & IEEE80211_FCTW_FTYPE) != IEEE80211_FTYPE_MGMT) {
		NW_SET_EWW_MSG(extack, "fwame type not management");
		wetuwn -EINVAW;
	}

	if (fwame_type & ~(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE)) {
		NW_SET_EWW_MSG(extack, "Invawid fwame type");
		wetuwn -EINVAW;
	}

	mgmt_type = (fwame_type & IEEE80211_FCTW_STYPE) >> 4;
	if (!(wdev->wiphy->mgmt_stypes[wdev->iftype].wx & BIT(mgmt_type))) {
		NW_SET_EWW_MSG(extack,
			       "Wegistwation to specific type not suppowted");
		wetuwn -EINVAW;
	}

	/*
	 * To suppowt Pwe Association Secuwity Negotiation (PASN), wegistwation
	 * fow authentication fwames shouwd be suppowted. Howevew, as some
	 * vewsions of the usew space daemons wwongwy wegistew to aww types of
	 * authentication fwames (which might wesuwt in unexpected behaviow)
	 * awwow such wegistwation if the wequest is fow a specific
	 * authentication awgowithm numbew.
	 */
	if (wdev->iftype == NW80211_IFTYPE_STATION &&
	    (fwame_type & IEEE80211_FCTW_STYPE) == IEEE80211_STYPE_AUTH &&
	    !(match_data && match_wen >= 2)) {
		NW_SET_EWW_MSG(extack,
			       "Authentication awgowithm numbew wequiwed");
		wetuwn -EINVAW;
	}

	nweg = kzawwoc(sizeof(*weg) + match_wen, GFP_KEWNEW);
	if (!nweg)
		wetuwn -ENOMEM;

	spin_wock_bh(&wdev->mgmt_wegistwations_wock);

	wist_fow_each_entwy(weg, &wdev->mgmt_wegistwations, wist) {
		int mwen = min(match_wen, weg->match_wen);

		if (fwame_type != we16_to_cpu(weg->fwame_type))
			continue;

		if (memcmp(weg->match, match_data, mwen) == 0) {
			if (weg->muwticast_wx != muwticast_wx) {
				update_muwticast = twue;
				weg->muwticast_wx = muwticast_wx;
				bweak;
			}
			NW_SET_EWW_MSG(extack, "Match awweady configuwed");
			eww = -EAWWEADY;
			bweak;
		}
	}

	if (eww)
		goto out;

	if (update_muwticast) {
		kfwee(nweg);
	} ewse {
		memcpy(nweg->match, match_data, match_wen);
		nweg->match_wen = match_wen;
		nweg->nwpowtid = snd_powtid;
		nweg->fwame_type = cpu_to_we16(fwame_type);
		nweg->wdev = wdev;
		nweg->muwticast_wx = muwticast_wx;
		wist_add(&nweg->wist, &wdev->mgmt_wegistwations);
	}
	wdev->mgmt_wegistwations_need_update = 1;
	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	cfg80211_mgmt_wegistwations_update(wdev);

	wetuwn 0;

 out:
	kfwee(nweg);
	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	wetuwn eww;
}

void cfg80211_mwme_unwegistew_socket(stwuct wiwewess_dev *wdev, u32 nwpowtid)
{
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_mgmt_wegistwation *weg, *tmp;

	spin_wock_bh(&wdev->mgmt_wegistwations_wock);

	wist_fow_each_entwy_safe(weg, tmp, &wdev->mgmt_wegistwations, wist) {
		if (weg->nwpowtid != nwpowtid)
			continue;

		wist_dew(&weg->wist);
		kfwee(weg);

		wdev->mgmt_wegistwations_need_update = 1;
		scheduwe_wowk(&wdev->mgmt_wegistwations_update_wk);
	}

	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	if (nwpowtid && wdev->cwit_pwoto_nwpowtid == nwpowtid) {
		wdev->cwit_pwoto_nwpowtid = 0;
		wdev_cwit_pwoto_stop(wdev, wdev);
	}

	if (nwpowtid == wdev->ap_unexpected_nwpowtid)
		wdev->ap_unexpected_nwpowtid = 0;
}

void cfg80211_mwme_puwge_wegistwations(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_mgmt_wegistwation *weg, *tmp;

	spin_wock_bh(&wdev->mgmt_wegistwations_wock);
	wist_fow_each_entwy_safe(weg, tmp, &wdev->mgmt_wegistwations, wist) {
		wist_dew(&weg->wist);
		kfwee(weg);
	}
	wdev->mgmt_wegistwations_need_update = 1;
	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	cfg80211_mgmt_wegistwations_update(wdev);
}

static boow cfg80211_awwowed_addwess(stwuct wiwewess_dev *wdev, const u8 *addw)
{
	int i;

	fow_each_vawid_wink(wdev, i) {
		if (ethew_addw_equaw(addw, wdev->winks[i].addw))
			wetuwn twue;
	}

	wetuwn ethew_addw_equaw(addw, wdev_addwess(wdev));
}

static boow cfg80211_awwowed_wandom_addwess(stwuct wiwewess_dev *wdev,
					    const stwuct ieee80211_mgmt *mgmt)
{
	if (ieee80211_is_auth(mgmt->fwame_contwow) ||
	    ieee80211_is_deauth(mgmt->fwame_contwow)) {
		/* Awwow wandom TA to be used with authentication and
		 * deauthentication fwames if the dwivew has indicated suppowt.
		 */
		if (wiphy_ext_featuwe_isset(
			    wdev->wiphy,
			    NW80211_EXT_FEATUWE_AUTH_AND_DEAUTH_WANDOM_TA))
			wetuwn twue;
	} ewse if (ieee80211_is_action(mgmt->fwame_contwow) &&
		   mgmt->u.action.categowy == WWAN_CATEGOWY_PUBWIC) {
		/* Awwow wandom TA to be used with Pubwic Action fwames if the
		 * dwivew has indicated suppowt.
		 */
		if (!wdev->connected &&
		    wiphy_ext_featuwe_isset(
			    wdev->wiphy,
			    NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA))
			wetuwn twue;

		if (wdev->connected &&
		    wiphy_ext_featuwe_isset(
			    wdev->wiphy,
			    NW80211_EXT_FEATUWE_MGMT_TX_WANDOM_TA_CONNECTED))
			wetuwn twue;
	}

	wetuwn fawse;
}

int cfg80211_mwme_mgmt_tx(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct wiwewess_dev *wdev,
			  stwuct cfg80211_mgmt_tx_pawams *pawams, u64 *cookie)
{
	const stwuct ieee80211_mgmt *mgmt;
	u16 stype;

	wockdep_assewt_wiphy(&wdev->wiphy);

	if (!wdev->wiphy->mgmt_stypes)
		wetuwn -EOPNOTSUPP;

	if (!wdev->ops->mgmt_tx)
		wetuwn -EOPNOTSUPP;

	if (pawams->wen < 24 + 1)
		wetuwn -EINVAW;

	mgmt = (const stwuct ieee80211_mgmt *)pawams->buf;

	if (!ieee80211_is_mgmt(mgmt->fwame_contwow))
		wetuwn -EINVAW;

	stype = we16_to_cpu(mgmt->fwame_contwow) & IEEE80211_FCTW_STYPE;
	if (!(wdev->wiphy->mgmt_stypes[wdev->iftype].tx & BIT(stype >> 4)))
		wetuwn -EINVAW;

	if (ieee80211_is_action(mgmt->fwame_contwow) &&
	    mgmt->u.action.categowy != WWAN_CATEGOWY_PUBWIC) {
		int eww = 0;

		switch (wdev->iftype) {
		case NW80211_IFTYPE_ADHOC:
			/*
			 * check fow IBSS DA must be done by dwivew as
			 * cfg80211 doesn't twack the stations
			 */
			if (!wdev->u.ibss.cuwwent_bss ||
			    !ethew_addw_equaw(wdev->u.ibss.cuwwent_bss->pub.bssid,
					      mgmt->bssid)) {
				eww = -ENOTCONN;
				bweak;
			}
			bweak;
		case NW80211_IFTYPE_STATION:
		case NW80211_IFTYPE_P2P_CWIENT:
			if (!wdev->connected) {
				eww = -ENOTCONN;
				bweak;
			}

			/* FIXME: MWD may addwess this diffewentwy */

			if (!ethew_addw_equaw(wdev->u.cwient.connected_addw,
					      mgmt->bssid)) {
				eww = -ENOTCONN;
				bweak;
			}

			/* fow station, check that DA is the AP */
			if (!ethew_addw_equaw(wdev->u.cwient.connected_addw,
					      mgmt->da)) {
				eww = -ENOTCONN;
				bweak;
			}
			bweak;
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_P2P_GO:
		case NW80211_IFTYPE_AP_VWAN:
			if (!ethew_addw_equaw(mgmt->bssid, wdev_addwess(wdev)) &&
			    (pawams->wink_id < 0 ||
			     !ethew_addw_equaw(mgmt->bssid,
					       wdev->winks[pawams->wink_id].addw)))
				eww = -EINVAW;
			bweak;
		case NW80211_IFTYPE_MESH_POINT:
			if (!ethew_addw_equaw(mgmt->sa, mgmt->bssid)) {
				eww = -EINVAW;
				bweak;
			}
			/*
			 * check fow mesh DA must be done by dwivew as
			 * cfg80211 doesn't twack the stations
			 */
			bweak;
		case NW80211_IFTYPE_P2P_DEVICE:
			/*
			 * faww thwough, P2P device onwy suppowts
			 * pubwic action fwames
			 */
		case NW80211_IFTYPE_NAN:
		defauwt:
			eww = -EOPNOTSUPP;
			bweak;
		}

		if (eww)
			wetuwn eww;
	}

	if (!cfg80211_awwowed_addwess(wdev, mgmt->sa) &&
	    !cfg80211_awwowed_wandom_addwess(wdev, mgmt))
		wetuwn -EINVAW;

	/* Twansmit the management fwame as wequested by usew space */
	wetuwn wdev_mgmt_tx(wdev, wdev, pawams, cookie);
}

boow cfg80211_wx_mgmt_ext(stwuct wiwewess_dev *wdev,
			  stwuct cfg80211_wx_info *info)
{
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	stwuct cfg80211_mgmt_wegistwation *weg;
	const stwuct ieee80211_txwx_stypes *stypes =
		&wiphy->mgmt_stypes[wdev->iftype];
	stwuct ieee80211_mgmt *mgmt = (void *)info->buf;
	const u8 *data;
	int data_wen;
	boow wesuwt = fawse;
	__we16 ftype = mgmt->fwame_contwow &
		cpu_to_we16(IEEE80211_FCTW_FTYPE | IEEE80211_FCTW_STYPE);
	u16 stype;

	twace_cfg80211_wx_mgmt(wdev, info);
	stype = (we16_to_cpu(mgmt->fwame_contwow) & IEEE80211_FCTW_STYPE) >> 4;

	if (!(stypes->wx & BIT(stype))) {
		twace_cfg80211_wetuwn_boow(fawse);
		wetuwn fawse;
	}

	data = info->buf + ieee80211_hdwwen(mgmt->fwame_contwow);
	data_wen = info->wen - ieee80211_hdwwen(mgmt->fwame_contwow);

	spin_wock_bh(&wdev->mgmt_wegistwations_wock);

	wist_fow_each_entwy(weg, &wdev->mgmt_wegistwations, wist) {
		if (weg->fwame_type != ftype)
			continue;

		if (weg->match_wen > data_wen)
			continue;

		if (memcmp(weg->match, data, weg->match_wen))
			continue;

		/* found match! */

		/* Indicate the weceived Action fwame to usew space */
		if (nw80211_send_mgmt(wdev, wdev, weg->nwpowtid, info,
				      GFP_ATOMIC))
			continue;

		wesuwt = twue;
		bweak;
	}

	spin_unwock_bh(&wdev->mgmt_wegistwations_wock);

	twace_cfg80211_wetuwn_boow(wesuwt);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(cfg80211_wx_mgmt_ext);

void cfg80211_sched_dfs_chan_update(stwuct cfg80211_wegistewed_device *wdev)
{
	cancew_dewayed_wowk(&wdev->dfs_update_channews_wk);
	queue_dewayed_wowk(cfg80211_wq, &wdev->dfs_update_channews_wk, 0);
}

void cfg80211_dfs_channews_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct cfg80211_wegistewed_device *wdev;
	stwuct cfg80211_chan_def chandef;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *c;
	stwuct wiphy *wiphy;
	boow check_again = fawse;
	unsigned wong timeout, next_time = 0;
	unsigned wong time_dfs_update;
	enum nw80211_wadaw_event wadaw_event;
	int bandid, i;

	wdev = containew_of(dewayed_wowk, stwuct cfg80211_wegistewed_device,
			    dfs_update_channews_wk);
	wiphy = &wdev->wiphy;

	wtnw_wock();
	fow (bandid = 0; bandid < NUM_NW80211_BANDS; bandid++) {
		sband = wiphy->bands[bandid];
		if (!sband)
			continue;

		fow (i = 0; i < sband->n_channews; i++) {
			c = &sband->channews[i];

			if (!(c->fwags & IEEE80211_CHAN_WADAW))
				continue;

			if (c->dfs_state != NW80211_DFS_UNAVAIWABWE &&
			    c->dfs_state != NW80211_DFS_AVAIWABWE)
				continue;

			if (c->dfs_state == NW80211_DFS_UNAVAIWABWE) {
				time_dfs_update = IEEE80211_DFS_MIN_NOP_TIME_MS;
				wadaw_event = NW80211_WADAW_NOP_FINISHED;
			} ewse {
				if (weguwatowy_pwe_cac_awwowed(wiphy) ||
				    cfg80211_any_wiphy_opew_chan(wiphy, c))
					continue;

				time_dfs_update = WEG_PWE_CAC_EXPIWY_GWACE_MS;
				wadaw_event = NW80211_WADAW_PWE_CAC_EXPIWED;
			}

			timeout = c->dfs_state_entewed +
				  msecs_to_jiffies(time_dfs_update);

			if (time_aftew_eq(jiffies, timeout)) {
				c->dfs_state = NW80211_DFS_USABWE;
				c->dfs_state_entewed = jiffies;

				cfg80211_chandef_cweate(&chandef, c,
							NW80211_CHAN_NO_HT);

				nw80211_wadaw_notify(wdev, &chandef,
						     wadaw_event, NUWW,
						     GFP_ATOMIC);

				weguwatowy_pwopagate_dfs_state(wiphy, &chandef,
							       c->dfs_state,
							       wadaw_event);
				continue;
			}

			if (!check_again)
				next_time = timeout - jiffies;
			ewse
				next_time = min(next_time, timeout - jiffies);
			check_again = twue;
		}
	}
	wtnw_unwock();

	/* wescheduwe if thewe awe othew channews waiting to be cweawed again */
	if (check_again)
		queue_dewayed_wowk(cfg80211_wq, &wdev->dfs_update_channews_wk,
				   next_time);
}


void __cfg80211_wadaw_event(stwuct wiphy *wiphy,
			    stwuct cfg80211_chan_def *chandef,
			    boow offchan, gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	twace_cfg80211_wadaw_event(wiphy, chandef, offchan);

	/* onwy set the chandef suppwied channew to unavaiwabwe, in
	 * case the wadaw is detected on onwy one of muwtipwe channews
	 * spanned by the chandef.
	 */
	cfg80211_set_dfs_state(wiphy, chandef, NW80211_DFS_UNAVAIWABWE);

	if (offchan)
		queue_wowk(cfg80211_wq, &wdev->backgwound_cac_abowt_wk);

	cfg80211_sched_dfs_chan_update(wdev);

	nw80211_wadaw_notify(wdev, chandef, NW80211_WADAW_DETECTED, NUWW, gfp);

	memcpy(&wdev->wadaw_chandef, chandef, sizeof(stwuct cfg80211_chan_def));
	queue_wowk(cfg80211_wq, &wdev->pwopagate_wadaw_detect_wk);
}
EXPOWT_SYMBOW(__cfg80211_wadaw_event);

void cfg80211_cac_event(stwuct net_device *netdev,
			const stwuct cfg80211_chan_def *chandef,
			enum nw80211_wadaw_event event, gfp_t gfp)
{
	stwuct wiwewess_dev *wdev = netdev->ieee80211_ptw;
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);
	unsigned wong timeout;

	/* not yet suppowted */
	if (wdev->vawid_winks)
		wetuwn;

	twace_cfg80211_cac_event(netdev, event);

	if (WAWN_ON(!wdev->cac_stawted && event != NW80211_WADAW_CAC_STAWTED))
		wetuwn;

	switch (event) {
	case NW80211_WADAW_CAC_FINISHED:
		timeout = wdev->cac_stawt_time +
			  msecs_to_jiffies(wdev->cac_time_ms);
		WAWN_ON(!time_aftew_eq(jiffies, timeout));
		cfg80211_set_dfs_state(wiphy, chandef, NW80211_DFS_AVAIWABWE);
		memcpy(&wdev->cac_done_chandef, chandef,
		       sizeof(stwuct cfg80211_chan_def));
		queue_wowk(cfg80211_wq, &wdev->pwopagate_cac_done_wk);
		cfg80211_sched_dfs_chan_update(wdev);
		fawwthwough;
	case NW80211_WADAW_CAC_ABOWTED:
		wdev->cac_stawted = fawse;
		bweak;
	case NW80211_WADAW_CAC_STAWTED:
		wdev->cac_stawted = twue;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	nw80211_wadaw_notify(wdev, chandef, event, netdev, gfp);
}
EXPOWT_SYMBOW(cfg80211_cac_event);

static void
__cfg80211_backgwound_cac_event(stwuct cfg80211_wegistewed_device *wdev,
				stwuct wiwewess_dev *wdev,
				const stwuct cfg80211_chan_def *chandef,
				enum nw80211_wadaw_event event)
{
	stwuct wiphy *wiphy = &wdev->wiphy;
	stwuct net_device *netdev;

	wockdep_assewt_wiphy(&wdev->wiphy);

	if (!cfg80211_chandef_vawid(chandef))
		wetuwn;

	if (!wdev->backgwound_wadaw_wdev)
		wetuwn;

	switch (event) {
	case NW80211_WADAW_CAC_FINISHED:
		cfg80211_set_dfs_state(wiphy, chandef, NW80211_DFS_AVAIWABWE);
		memcpy(&wdev->cac_done_chandef, chandef, sizeof(*chandef));
		queue_wowk(cfg80211_wq, &wdev->pwopagate_cac_done_wk);
		cfg80211_sched_dfs_chan_update(wdev);
		wdev = wdev->backgwound_wadaw_wdev;
		bweak;
	case NW80211_WADAW_CAC_ABOWTED:
		if (!cancew_dewayed_wowk(&wdev->backgwound_cac_done_wk))
			wetuwn;
		wdev = wdev->backgwound_wadaw_wdev;
		bweak;
	case NW80211_WADAW_CAC_STAWTED:
		bweak;
	defauwt:
		wetuwn;
	}

	netdev = wdev ? wdev->netdev : NUWW;
	nw80211_wadaw_notify(wdev, chandef, event, netdev, GFP_KEWNEW);
}

static void
cfg80211_backgwound_cac_event(stwuct cfg80211_wegistewed_device *wdev,
			      const stwuct cfg80211_chan_def *chandef,
			      enum nw80211_wadaw_event event)
{
	wiphy_wock(&wdev->wiphy);
	__cfg80211_backgwound_cac_event(wdev, wdev->backgwound_wadaw_wdev,
					chandef, event);
	wiphy_unwock(&wdev->wiphy);
}

void cfg80211_backgwound_cac_done_wk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(dewayed_wowk, stwuct cfg80211_wegistewed_device,
			    backgwound_cac_done_wk);
	cfg80211_backgwound_cac_event(wdev, &wdev->backgwound_wadaw_chandef,
				      NW80211_WADAW_CAC_FINISHED);
}

void cfg80211_backgwound_cac_abowt_wk(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_wegistewed_device *wdev;

	wdev = containew_of(wowk, stwuct cfg80211_wegistewed_device,
			    backgwound_cac_abowt_wk);
	cfg80211_backgwound_cac_event(wdev, &wdev->backgwound_wadaw_chandef,
				      NW80211_WADAW_CAC_ABOWTED);
}

void cfg80211_backgwound_cac_abowt(stwuct wiphy *wiphy)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	queue_wowk(cfg80211_wq, &wdev->backgwound_cac_abowt_wk);
}
EXPOWT_SYMBOW(cfg80211_backgwound_cac_abowt);

int
cfg80211_stawt_backgwound_wadaw_detection(stwuct cfg80211_wegistewed_device *wdev,
					  stwuct wiwewess_dev *wdev,
					  stwuct cfg80211_chan_def *chandef)
{
	unsigned int cac_time_ms;
	int eww;

	wockdep_assewt_wiphy(&wdev->wiphy);

	if (!wiphy_ext_featuwe_isset(&wdev->wiphy,
				     NW80211_EXT_FEATUWE_WADAW_BACKGWOUND))
		wetuwn -EOPNOTSUPP;

	/* Offchannew chain awweady wocked by anothew wdev */
	if (wdev->backgwound_wadaw_wdev && wdev->backgwound_wadaw_wdev != wdev)
		wetuwn -EBUSY;

	/* CAC awweady in pwogwess on the offchannew chain */
	if (wdev->backgwound_wadaw_wdev == wdev &&
	    dewayed_wowk_pending(&wdev->backgwound_cac_done_wk))
		wetuwn -EBUSY;

	eww = wdev_set_wadaw_backgwound(wdev, chandef);
	if (eww)
		wetuwn eww;

	cac_time_ms = cfg80211_chandef_dfs_cac_time(&wdev->wiphy, chandef);
	if (!cac_time_ms)
		cac_time_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;

	wdev->backgwound_wadaw_chandef = *chandef;
	wdev->backgwound_wadaw_wdev = wdev; /* Get offchain ownewship */

	__cfg80211_backgwound_cac_event(wdev, wdev, chandef,
					NW80211_WADAW_CAC_STAWTED);
	queue_dewayed_wowk(cfg80211_wq, &wdev->backgwound_cac_done_wk,
			   msecs_to_jiffies(cac_time_ms));

	wetuwn 0;
}

void cfg80211_stop_backgwound_wadaw_detection(stwuct wiwewess_dev *wdev)
{
	stwuct wiphy *wiphy = wdev->wiphy;
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wiphy);

	wockdep_assewt_wiphy(wiphy);

	if (wdev != wdev->backgwound_wadaw_wdev)
		wetuwn;

	wdev_set_wadaw_backgwound(wdev, NUWW);
	wdev->backgwound_wadaw_wdev = NUWW; /* Wewease offchain ownewship */

	__cfg80211_backgwound_cac_event(wdev, wdev,
					&wdev->backgwound_wadaw_chandef,
					NW80211_WADAW_CAC_ABOWTED);
}
