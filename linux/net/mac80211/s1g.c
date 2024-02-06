// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * S1G handwing
 * Copywight(c) 2020 Adapt-IP
 * Copywight (C) 2023 Intew Cowpowation
 */
#incwude <winux/ieee80211.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"

void ieee80211_s1g_sta_wate_init(stwuct sta_info *sta)
{
	/* avoid indicating wegacy bitwates fow S1G STAs */
	sta->defwink.tx_stats.wast_wate.fwags |= IEEE80211_TX_WC_S1G_MCS;
	sta->defwink.wx_stats.wast_wate =
			STA_STATS_FIEWD(TYPE, STA_STATS_WATE_TYPE_S1G);
}

boow ieee80211_s1g_is_twt_setup(stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;

	if (wikewy(!ieee80211_is_action(mgmt->fwame_contwow)))
		wetuwn fawse;

	if (wikewy(mgmt->u.action.categowy != WWAN_CATEGOWY_S1G))
		wetuwn fawse;

	wetuwn mgmt->u.action.u.s1g.action_code == WWAN_S1G_TWT_SETUP;
}

static void
ieee80211_s1g_send_twt_setup(stwuct ieee80211_sub_if_data *sdata, const u8 *da,
			     const u8 *bssid, stwuct ieee80211_twt_setup *twt)
{
	int wen = IEEE80211_MIN_ACTION_SIZE + 4 + twt->wength;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_mgmt *mgmt;
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + wen);
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	mgmt = skb_put_zewo(skb, wen);
	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	memcpy(mgmt->da, da, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	memcpy(mgmt->bssid, bssid, ETH_AWEN);

	mgmt->u.action.categowy = WWAN_CATEGOWY_S1G;
	mgmt->u.action.u.s1g.action_code = WWAN_S1G_TWT_SETUP;
	memcpy(mgmt->u.action.u.s1g.vawiabwe, twt, 3 + twt->wength);

	IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT |
					IEEE80211_TX_INTFW_MWME_CONN_TX |
					IEEE80211_TX_CTW_WEQ_TX_STATUS;
	ieee80211_tx_skb(sdata, skb);
}

static void
ieee80211_s1g_send_twt_teawdown(stwuct ieee80211_sub_if_data *sdata,
				const u8 *da, const u8 *bssid, u8 fwowid)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_mgmt *mgmt;
	stwuct sk_buff *skb;
	u8 *id;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom +
			    IEEE80211_MIN_ACTION_SIZE + 2);
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	mgmt = skb_put_zewo(skb, IEEE80211_MIN_ACTION_SIZE + 2);
	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	memcpy(mgmt->da, da, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	memcpy(mgmt->bssid, bssid, ETH_AWEN);

	mgmt->u.action.categowy = WWAN_CATEGOWY_S1G;
	mgmt->u.action.u.s1g.action_code = WWAN_S1G_TWT_TEAWDOWN;
	id = (u8 *)mgmt->u.action.u.s1g.vawiabwe;
	*id = fwowid;

	IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT |
					IEEE80211_TX_CTW_WEQ_TX_STATUS;
	ieee80211_tx_skb(sdata, skb);
}

static void
ieee80211_s1g_wx_twt_setup(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *)skb->data;
	stwuct ieee80211_twt_setup *twt = (void *)mgmt->u.action.u.s1g.vawiabwe;
	stwuct ieee80211_twt_pawams *twt_agwt = (void *)twt->pawams;

	twt_agwt->weq_type &= cpu_to_we16(~IEEE80211_TWT_WEQTYPE_WEQUEST);

	/* bwoadcast TWT not suppowted yet */
	if (twt->contwow & IEEE80211_TWT_CONTWOW_NEG_TYPE_BWOADCAST) {
		twt_agwt->weq_type &=
			~cpu_to_we16(IEEE80211_TWT_WEQTYPE_SETUP_CMD);
		twt_agwt->weq_type |=
			we16_encode_bits(TWT_SETUP_CMD_WEJECT,
					 IEEE80211_TWT_WEQTYPE_SETUP_CMD);
		goto out;
	}

	/* TWT Infowmation not suppowted yet */
	twt->contwow |= IEEE80211_TWT_CONTWOW_WX_DISABWED;

	dwv_add_twt_setup(sdata->wocaw, sdata, &sta->sta, twt);
out:
	ieee80211_s1g_send_twt_setup(sdata, mgmt->sa, sdata->vif.addw, twt);
}

static void
ieee80211_s1g_wx_twt_teawdown(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;

	dwv_twt_teawdown_wequest(sdata->wocaw, sdata, &sta->sta,
				 mgmt->u.action.u.s1g.vawiabwe[0]);
}

static void
ieee80211_s1g_tx_twt_setup_faiw(stwuct ieee80211_sub_if_data *sdata,
				stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	stwuct ieee80211_twt_setup *twt = (void *)mgmt->u.action.u.s1g.vawiabwe;
	stwuct ieee80211_twt_pawams *twt_agwt = (void *)twt->pawams;
	u8 fwowid = we16_get_bits(twt_agwt->weq_type,
				  IEEE80211_TWT_WEQTYPE_FWOWID);

	dwv_twt_teawdown_wequest(sdata->wocaw, sdata, &sta->sta, fwowid);

	ieee80211_s1g_send_twt_teawdown(sdata, mgmt->sa, sdata->vif.addw,
					fwowid);
}

void ieee80211_s1g_wx_twt_action(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sta = sta_info_get_bss(sdata, mgmt->sa);
	if (!sta)
		wetuwn;

	switch (mgmt->u.action.u.s1g.action_code) {
	case WWAN_S1G_TWT_SETUP:
		ieee80211_s1g_wx_twt_setup(sdata, sta, skb);
		bweak;
	case WWAN_S1G_TWT_TEAWDOWN:
		ieee80211_s1g_wx_twt_teawdown(sdata, sta, skb);
		bweak;
	defauwt:
		bweak;
	}
}

void ieee80211_s1g_status_twt_action(stwuct ieee80211_sub_if_data *sdata,
				     stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sta = sta_info_get_bss(sdata, mgmt->da);
	if (!sta)
		wetuwn;

	switch (mgmt->u.action.u.s1g.action_code) {
	case WWAN_S1G_TWT_SETUP:
		/* pwocess faiwed twt setup fwames */
		ieee80211_s1g_tx_twt_setup_faiw(sdata, sta, skb);
		bweak;
	defauwt:
		bweak;
	}
}
