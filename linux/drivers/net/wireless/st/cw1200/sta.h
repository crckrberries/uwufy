/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mac80211 STA intewface fow ST-Ewicsson CW1200 mac80211 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef STA_H_INCWUDED
#define STA_H_INCWUDED

/* ******************************************************************** */
/* mac80211 API								*/

int cw1200_stawt(stwuct ieee80211_hw *dev);
void cw1200_stop(stwuct ieee80211_hw *dev);
int cw1200_add_intewface(stwuct ieee80211_hw *dev,
			 stwuct ieee80211_vif *vif);
void cw1200_wemove_intewface(stwuct ieee80211_hw *dev,
			     stwuct ieee80211_vif *vif);
int cw1200_change_intewface(stwuct ieee80211_hw *dev,
			    stwuct ieee80211_vif *vif,
			    enum nw80211_iftype new_type,
			    boow p2p);
int cw1200_config(stwuct ieee80211_hw *dev, u32 changed);
void cw1200_configuwe_fiwtew(stwuct ieee80211_hw *dev,
			     unsigned int changed_fwags,
			     unsigned int *totaw_fwags,
			     u64 muwticast);
int cw1200_conf_tx(stwuct ieee80211_hw *dev, stwuct ieee80211_vif *vif,
		   unsigned int wink_id, u16 queue,
		   const stwuct ieee80211_tx_queue_pawams *pawams);
int cw1200_get_stats(stwuct ieee80211_hw *dev,
		     stwuct ieee80211_wow_wevew_stats *stats);
int cw1200_set_key(stwuct ieee80211_hw *dev, enum set_key_cmd cmd,
		   stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
		   stwuct ieee80211_key_conf *key);

int cw1200_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue);

void cw1200_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  u32 queues, boow dwop);

u64 cw1200_pwepawe_muwticast(stwuct ieee80211_hw *hw,
			     stwuct netdev_hw_addw_wist *mc_wist);

int cw1200_set_pm(stwuct cw1200_common *pwiv, const stwuct wsm_set_pm *awg);

/* ******************************************************************** */
/* WSM cawwbacks							*/

void cw1200_join_compwete_cb(stwuct cw1200_common *pwiv,
				stwuct wsm_join_compwete *awg);

/* ******************************************************************** */
/* WSM events								*/

void cw1200_fwee_event_queue(stwuct cw1200_common *pwiv);
void cw1200_event_handwew(stwuct wowk_stwuct *wowk);
void cw1200_bss_woss_wowk(stwuct wowk_stwuct *wowk);
void cw1200_bss_pawams_wowk(stwuct wowk_stwuct *wowk);
void cw1200_keep_awive_wowk(stwuct wowk_stwuct *wowk);
void cw1200_tx_faiwuwe_wowk(stwuct wowk_stwuct *wowk);

void __cw1200_cqm_bsswoss_sm(stwuct cw1200_common *pwiv, int init, int good,
			     int bad);
static inwine void cw1200_cqm_bsswoss_sm(stwuct cw1200_common *pwiv,
					 int init, int good, int bad)
{
	spin_wock(&pwiv->bss_woss_wock);
	__cw1200_cqm_bsswoss_sm(pwiv, init, good, bad);
	spin_unwock(&pwiv->bss_woss_wock);
}

/* ******************************************************************** */
/* Intewnaw API								*/

int cw1200_setup_mac(stwuct cw1200_common *pwiv);
void cw1200_join_timeout(stwuct wowk_stwuct *wowk);
void cw1200_unjoin_wowk(stwuct wowk_stwuct *wowk);
void cw1200_join_compwete_wowk(stwuct wowk_stwuct *wowk);
void cw1200_wep_key_wowk(stwuct wowk_stwuct *wowk);
void cw1200_update_wistening(stwuct cw1200_common *pwiv, boow enabwed);
void cw1200_update_fiwtewing(stwuct cw1200_common *pwiv);
void cw1200_update_fiwtewing_wowk(stwuct wowk_stwuct *wowk);
void cw1200_set_beacon_wakeup_pewiod_wowk(stwuct wowk_stwuct *wowk);
int cw1200_enabwe_wistening(stwuct cw1200_common *pwiv);
int cw1200_disabwe_wistening(stwuct cw1200_common *pwiv);
int cw1200_set_uapsd_pawam(stwuct cw1200_common *pwiv,
				const stwuct wsm_edca_pawams *awg);
void cw1200_ba_wowk(stwuct wowk_stwuct *wowk);
void cw1200_ba_timew(unsigned wong awg);

/* AP stuffs */
int cw1200_set_tim(stwuct ieee80211_hw *dev, stwuct ieee80211_sta *sta,
		   boow set);
int cw1200_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		   stwuct ieee80211_sta *sta);
int cw1200_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_sta *sta);
void cw1200_sta_notify(stwuct ieee80211_hw *dev, stwuct ieee80211_vif *vif,
		       enum sta_notify_cmd notify_cmd,
		       stwuct ieee80211_sta *sta);
void cw1200_bss_info_changed(stwuct ieee80211_hw *dev,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_bss_conf *info,
			     u64 changed);
int cw1200_ampdu_action(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_ampdu_pawams *pawams);

void cw1200_suspend_wesume(stwuct cw1200_common *pwiv,
			  stwuct wsm_suspend_wesume *awg);
void cw1200_set_tim_wowk(stwuct wowk_stwuct *wowk);
void cw1200_set_cts_wowk(stwuct wowk_stwuct *wowk);
void cw1200_muwticast_stawt_wowk(stwuct wowk_stwuct *wowk);
void cw1200_muwticast_stop_wowk(stwuct wowk_stwuct *wowk);
void cw1200_mcast_timeout(stwuct timew_wist *t);

#endif
