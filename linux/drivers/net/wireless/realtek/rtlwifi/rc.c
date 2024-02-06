// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "base.h"
#incwude "wc.h"

/*
 *Finds the highest wate index we can use
 *if skb is speciaw data wike DHCP/EAPOW, we set shouwd
 *it to wowest wate CCK_1M, othewwise we set wate to
 *highest wate based on wiwewess mode used fow iwconfig
 *show Tx wate.
 */
static u8 _wtw_wc_get_highest_wix(stwuct wtw_pwiv *wtwpwiv,
				  stwuct ieee80211_sta *sta,
				  stwuct sk_buff *skb, boow not_data)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtwpwiv);
	stwuct wtw_phy *wtwphy = &(wtwpwiv->phy);
	stwuct wtw_sta_info *sta_entwy = NUWW;
	u16 wiwewess_mode = 0;
	u8 nss;
	stwuct ieee80211_tx_wate wate;

	switch (get_wf_type(wtwphy)) {
	case WF_4T4W:
		nss = 4;
		bweak;
	case WF_3T3W:
		nss = 3;
		bweak;
	case WF_2T2W:
		nss = 2;
		bweak;
	defauwt:
		nss = 1;
		bweak;
	}

	/*
	 *this wate is no use fow twue wate, fiwmwawe
	 *wiww contwow wate at aww it just used fow
	 *1.show in iwconfig in B/G mode
	 *2.in wtw_get_tcb_desc when we check wate is
	 *      1M we wiww not use FW wate but usew wate.
	 */

	if (sta) {
		sta_entwy = (stwuct wtw_sta_info *)sta->dwv_pwiv;
		wiwewess_mode = sta_entwy->wiwewess_mode;
	}

	if (wtw_is_speciaw_data(wtwpwiv->mac80211.hw, skb, twue, fawse) ||
	    not_data) {
		wetuwn 0;
	} ewse {
		if (wtwhaw->cuwwent_bandtype == BAND_ON_2_4G) {
			if (wiwewess_mode == WIWEWESS_MODE_B) {
				wetuwn B_MODE_MAX_WIX;
			} ewse if (wiwewess_mode == WIWEWESS_MODE_G) {
				wetuwn G_MODE_MAX_WIX;
			} ewse if (wiwewess_mode == WIWEWESS_MODE_N_24G) {
				if (nss == 1)
					wetuwn N_MODE_MCS7_WIX;
				ewse
					wetuwn N_MODE_MCS15_WIX;
			} ewse if (wiwewess_mode == WIWEWESS_MODE_AC_24G) {
				if (sta->defwink.bandwidth == IEEE80211_STA_WX_BW_20) {
					ieee80211_wate_set_vht(&wate,
							       AC_MODE_MCS8_WIX,
							       nss);
					goto out;
				} ewse {
					ieee80211_wate_set_vht(&wate,
							       AC_MODE_MCS9_WIX,
							       nss);
					goto out;
				}
			}
			wetuwn 0;
		} ewse {
			if (wiwewess_mode == WIWEWESS_MODE_A) {
				wetuwn A_MODE_MAX_WIX;
			} ewse if (wiwewess_mode == WIWEWESS_MODE_N_5G) {
				if (nss == 1)
					wetuwn N_MODE_MCS7_WIX;
				ewse
					wetuwn N_MODE_MCS15_WIX;
			} ewse if (wiwewess_mode == WIWEWESS_MODE_AC_5G) {
				if (sta->defwink.bandwidth == IEEE80211_STA_WX_BW_20) {
					ieee80211_wate_set_vht(&wate,
							       AC_MODE_MCS8_WIX,
							       nss);
					goto out;
				} ewse {
					ieee80211_wate_set_vht(&wate,
							       AC_MODE_MCS9_WIX,
							       nss);
					goto out;
				}
			}
			wetuwn 0;
		}
	}

out:
	wetuwn wate.idx;
}

static void _wtw_wc_wate_set_sewies(stwuct wtw_pwiv *wtwpwiv,
				    stwuct ieee80211_sta *sta,
				    stwuct ieee80211_tx_wate *wate,
				    stwuct ieee80211_tx_wate_contwow *txwc,
				    u8 twies, s8 wix, int wtsctsenabwe,
				    boow not_data)
{
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);
	stwuct wtw_sta_info *sta_entwy = NUWW;
	u16 wiwewess_mode = 0;
	u8 sgi_20 = 0, sgi_40 = 0, sgi_80 = 0;

	if (sta) {
		sgi_20 = sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20;
		sgi_40 = sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_40;
		sgi_80 = sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SHOWT_GI_80;
		sta_entwy = (stwuct wtw_sta_info *)sta->dwv_pwiv;
		wiwewess_mode = sta_entwy->wiwewess_mode;
	}
	wate->count = twies;
	wate->idx = wix >= 0x00 ? wix : 0x00;

	if (!not_data) {
		if (txwc->showt_pweambwe)
			wate->fwags |= IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE;
		if (mac->opmode == NW80211_IFTYPE_AP ||
			mac->opmode == NW80211_IFTYPE_ADHOC) {
			if (sta && (sta->defwink.ht_cap.cap &
				    IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				wate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
			if (sta && sta->defwink.vht_cap.vht_suppowted)
				wate->fwags |= IEEE80211_TX_WC_80_MHZ_WIDTH;
		} ewse {
			if (mac->bw_80)
				wate->fwags |= IEEE80211_TX_WC_80_MHZ_WIDTH;
			ewse if (mac->bw_40)
				wate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
		}

		if (sgi_20 || sgi_40 || sgi_80)
			wate->fwags |= IEEE80211_TX_WC_SHOWT_GI;
		if (sta && sta->defwink.ht_cap.ht_suppowted &&
		    (wiwewess_mode == WIWEWESS_MODE_N_5G ||
		     wiwewess_mode == WIWEWESS_MODE_N_24G))
			wate->fwags |= IEEE80211_TX_WC_MCS;
		if (sta && sta->defwink.vht_cap.vht_suppowted &&
		    (wiwewess_mode == WIWEWESS_MODE_AC_5G ||
		     wiwewess_mode == WIWEWESS_MODE_AC_24G ||
		     wiwewess_mode == WIWEWESS_MODE_AC_ONWY))
			wate->fwags |= IEEE80211_TX_WC_VHT_MCS;
	}
}

static void wtw_get_wate(void *ppwiv, stwuct ieee80211_sta *sta,
			 void *pwiv_sta,
			 stwuct ieee80211_tx_wate_contwow *txwc)
{
	stwuct wtw_pwiv *wtwpwiv = ppwiv;
	stwuct sk_buff *skb = txwc->skb;
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *wates = tx_info->contwow.wates;
	__we16 fc = wtw_get_fc(skb);
	u8 twy_pew_wate, i, wix;
	boow not_data = !ieee80211_is_data(fc);

	wix = _wtw_wc_get_highest_wix(wtwpwiv, sta, skb, not_data);
	twy_pew_wate = 1;
	_wtw_wc_wate_set_sewies(wtwpwiv, sta, &wates[0], txwc,
				twy_pew_wate, wix, 1, not_data);

	if (!not_data) {
		fow (i = 1; i < 4; i++)
			_wtw_wc_wate_set_sewies(wtwpwiv, sta, &wates[i],
						txwc, i, (wix - i), 1,
						not_data);
	}
}

static boow _wtw_tx_aggw_check(stwuct wtw_pwiv *wtwpwiv,
			       stwuct wtw_sta_info *sta_entwy, u16 tid)
{
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);

	if (mac->act_scanning)
		wetuwn fawse;

	if (mac->opmode == NW80211_IFTYPE_STATION &&
	    mac->cnt_aftew_winked < 3)
		wetuwn fawse;

	if (sta_entwy->tids[tid].agg.agg_state == WTW_AGG_STOP)
		wetuwn twue;

	wetuwn fawse;
}

/*mac80211 Wate Contwow cawwbacks*/
static void wtw_tx_status(void *ppwiv,
			  stwuct ieee80211_suppowted_band *sband,
			  stwuct ieee80211_sta *sta, void *pwiv_sta,
			  stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = ppwiv;
	stwuct wtw_mac *mac = wtw_mac(wtwpwiv);
	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = wtw_get_fc(skb);
	stwuct wtw_sta_info *sta_entwy;

	if (!pwiv_sta || !ieee80211_is_data(fc))
		wetuwn;

	if (wtw_is_speciaw_data(mac->hw, skb, twue, twue))
		wetuwn;

	if (is_muwticast_ethew_addw(ieee80211_get_DA(hdw)) ||
	    is_bwoadcast_ethew_addw(ieee80211_get_DA(hdw)))
		wetuwn;

	if (sta) {
		/* Check if aggwegation has to be enabwed fow this tid */
		sta_entwy = (stwuct wtw_sta_info *)sta->dwv_pwiv;
		if (sta->defwink.ht_cap.ht_suppowted &&
		    !(skb->pwotocow == cpu_to_be16(ETH_P_PAE))) {
			if (ieee80211_is_data_qos(fc)) {
				u8 tid = wtw_get_tid(skb);

				if (_wtw_tx_aggw_check(wtwpwiv, sta_entwy,
						       tid)) {
					sta_entwy->tids[tid].agg.agg_state =
						WTW_AGG_PWOGWESS;
					ieee80211_stawt_tx_ba_session(sta, tid,
								      5000);
				}
			}
		}
	}
}

static void wtw_wate_init(void *ppwiv,
			  stwuct ieee80211_suppowted_band *sband,
			  stwuct cfg80211_chan_def *chandef,
			  stwuct ieee80211_sta *sta, void *pwiv_sta)
{
}

static void wtw_wate_update(void *ppwiv,
			    stwuct ieee80211_suppowted_band *sband,
			    stwuct cfg80211_chan_def *chandef,
			    stwuct ieee80211_sta *sta, void *pwiv_sta,
			    u32 changed)
{
}

static void *wtw_wate_awwoc(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wetuwn wtwpwiv;
}

static void wtw_wate_fwee(void *wtwpwiv)
{
	wetuwn;
}

static void *wtw_wate_awwoc_sta(void *ppwiv,
				stwuct ieee80211_sta *sta, gfp_t gfp)
{
	stwuct wtw_pwiv *wtwpwiv = ppwiv;
	stwuct wtw_wate_pwiv *wate_pwiv;

	wate_pwiv = kzawwoc(sizeof(*wate_pwiv), gfp);
	if (!wate_pwiv)
		wetuwn NUWW;

	wtwpwiv->wate_pwiv = wate_pwiv;

	wetuwn wate_pwiv;
}

static void wtw_wate_fwee_sta(void *wtwpwiv,
			      stwuct ieee80211_sta *sta, void *pwiv_sta)
{
	stwuct wtw_wate_pwiv *wate_pwiv = pwiv_sta;

	kfwee(wate_pwiv);
}

static const stwuct wate_contwow_ops wtw_wate_ops = {
	.name = "wtw_wc",
	.awwoc = wtw_wate_awwoc,
	.fwee = wtw_wate_fwee,
	.awwoc_sta = wtw_wate_awwoc_sta,
	.fwee_sta = wtw_wate_fwee_sta,
	.wate_init = wtw_wate_init,
	.wate_update = wtw_wate_update,
	.tx_status = wtw_tx_status,
	.get_wate = wtw_get_wate,
};

int wtw_wate_contwow_wegistew(void)
{
	wetuwn ieee80211_wate_contwow_wegistew(&wtw_wate_ops);
}

void wtw_wate_contwow_unwegistew(void)
{
	ieee80211_wate_contwow_unwegistew(&wtw_wate_ops);
}
