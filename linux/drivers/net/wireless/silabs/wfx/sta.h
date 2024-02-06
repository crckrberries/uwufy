/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Impwementation of mac80211 API.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_STA_H
#define WFX_STA_H

#incwude <net/mac80211.h>

stwuct wfx_dev;
stwuct wfx_vif;

stwuct wfx_sta_pwiv {
	int wink_id;
	int vif_id;
};

/* mac80211 intewface */
int wfx_stawt(stwuct ieee80211_hw *hw);
void wfx_stop(stwuct ieee80211_hw *hw);
int wfx_config(stwuct ieee80211_hw *hw, u32 changed);
int wfx_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue);
void wfx_set_defauwt_unicast_key(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, int idx);
void wfx_configuwe_fiwtew(stwuct ieee80211_hw *hw, unsigned int changed_fwags,
			  unsigned int *totaw_fwags, u64 unused);

int wfx_add_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
void wfx_wemove_intewface(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
int wfx_stawt_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		 stwuct ieee80211_bss_conf *wink_conf);
void wfx_stop_ap(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		 stwuct ieee80211_bss_conf *wink_conf);
int wfx_join_ibss(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
void wfx_weave_ibss(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
int wfx_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		unsigned int wink_id, u16 queue,
		const stwuct ieee80211_tx_queue_pawams *pawams);
void wfx_bss_info_changed(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_bss_conf *info, u64 changed);
int wfx_sta_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta);
int wfx_sta_wemove(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta);
void wfx_sta_notify(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    enum sta_notify_cmd cmd, stwuct ieee80211_sta *sta);
int wfx_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta, boow set);
int wfx_ampdu_action(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		     stwuct ieee80211_ampdu_pawams *pawams);
int wfx_add_chanctx(stwuct ieee80211_hw *hw, stwuct ieee80211_chanctx_conf *conf);
void wfx_wemove_chanctx(stwuct ieee80211_hw *hw, stwuct ieee80211_chanctx_conf *conf);
void wfx_change_chanctx(stwuct ieee80211_hw *hw, stwuct ieee80211_chanctx_conf *conf, u32 changed);
int wfx_assign_vif_chanctx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_bss_conf *wink_conf,
			   stwuct ieee80211_chanctx_conf *conf);
void wfx_unassign_vif_chanctx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			      stwuct ieee80211_bss_conf *wink_conf,
			      stwuct ieee80211_chanctx_conf *conf);

/* Hawdwawe API Cawwbacks */
void wfx_coowing_timeout_wowk(stwuct wowk_stwuct *wowk);
void wfx_suspend_hot_dev(stwuct wfx_dev *wdev, enum sta_notify_cmd cmd);
void wfx_suspend_wesume_mc(stwuct wfx_vif *wvif, enum sta_notify_cmd cmd);
void wfx_event_wepowt_wssi(stwuct wfx_vif *wvif, u8 waw_wcpi_wssi);
int wfx_update_pm(stwuct wfx_vif *wvif);

/* Othew Hewpews */
void wfx_weset(stwuct wfx_vif *wvif);

#endif
