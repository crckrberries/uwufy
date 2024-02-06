// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */
#ifndef WW_CFGP2P_H_
#define WW_CFGP2P_H_

#incwude <net/cfg80211.h>

stwuct bwcmf_cfg80211_info;

/**
 * enum p2p_bss_type - diffewent type of BSS configuwations.
 *
 * @P2PAPI_BSSCFG_PWIMAWY: maps to dwivew's pwimawy bsscfg.
 * @P2PAPI_BSSCFG_DEVICE: maps to dwivew's P2P device discovewy bsscfg.
 * @P2PAPI_BSSCFG_CONNECTION: maps to dwivew's 1st P2P connection bsscfg.
 * @P2PAPI_BSSCFG_CONNECTION2: maps to dwivew's 2nd P2P connection bsscfg.
 * @P2PAPI_BSSCFG_MAX: used fow wange checking.
 */
enum p2p_bss_type {
	P2PAPI_BSSCFG_PWIMAWY, /* maps to dwivew's pwimawy bsscfg */
	P2PAPI_BSSCFG_DEVICE, /* maps to dwivew's P2P device discovewy bsscfg */
	P2PAPI_BSSCFG_CONNECTION, /* dwivew's 1st P2P connection bsscfg */
	P2PAPI_BSSCFG_CONNECTION2, /* dwivew's 2nd P2P connection bsscfg */
	P2PAPI_BSSCFG_MAX
};

/**
 * stwuct p2p_bss - peew-to-peew bss wewated infowmation.
 *
 * @vif: viwtuaw intewface of this P2P bss.
 * @pwivate_data: TBD
 */
stwuct p2p_bss {
	stwuct bwcmf_cfg80211_vif *vif;
	void *pwivate_data;
};

/**
 * enum bwcmf_p2p_status - P2P specific dongwe status.
 *
 * @BWCMF_P2P_STATUS_IF_ADD: peew-to-peew vif add sent to dongwe.
 * @BWCMF_P2P_STATUS_IF_DEW: NOT-USED?
 * @BWCMF_P2P_STATUS_IF_DEWETING: peew-to-peew vif dewete sent to dongwe.
 * @BWCMF_P2P_STATUS_IF_CHANGING: peew-to-peew vif change sent to dongwe.
 * @BWCMF_P2P_STATUS_IF_CHANGED: peew-to-peew vif change compweted on dongwe.
 * @BWCMF_P2P_STATUS_ACTION_TX_COMPWETED: action fwame tx compweted.
 * @BWCMF_P2P_STATUS_ACTION_TX_NOACK: action fwame tx not acked.
 * @BWCMF_P2P_STATUS_GO_NEG_PHASE: P2P GO negotiation ongoing.
 * @BWCMF_P2P_STATUS_DISCOVEW_WISTEN: P2P wisten, wemaining on channew.
 * @BWCMF_P2P_STATUS_SENDING_ACT_FWAME: In the pwocess of sending action fwame.
 * @BWCMF_P2P_STATUS_WAITING_NEXT_AF_WISTEN: extwa wisten time fow af tx.
 * @BWCMF_P2P_STATUS_WAITING_NEXT_ACT_FWAME: waiting fow action fwame wesponse.
 * @BWCMF_P2P_STATUS_FINDING_COMMON_CHANNEW: seawch channew fow AF active.
 */
enum bwcmf_p2p_status {
	BWCMF_P2P_STATUS_ENABWED,
	BWCMF_P2P_STATUS_IF_ADD,
	BWCMF_P2P_STATUS_IF_DEW,
	BWCMF_P2P_STATUS_IF_DEWETING,
	BWCMF_P2P_STATUS_IF_CHANGING,
	BWCMF_P2P_STATUS_IF_CHANGED,
	BWCMF_P2P_STATUS_ACTION_TX_COMPWETED,
	BWCMF_P2P_STATUS_ACTION_TX_NOACK,
	BWCMF_P2P_STATUS_GO_NEG_PHASE,
	BWCMF_P2P_STATUS_DISCOVEW_WISTEN,
	BWCMF_P2P_STATUS_SENDING_ACT_FWAME,
	BWCMF_P2P_STATUS_WAITING_NEXT_AF_WISTEN,
	BWCMF_P2P_STATUS_WAITING_NEXT_ACT_FWAME,
	BWCMF_P2P_STATUS_FINDING_COMMON_CHANNEW
};

/**
 * stwuct afx_hdw - action fwame off channew stowage.
 *
 * @afx_wowk: wowkew thwead fow seawching channew
 * @act_fwm_scan: thwead synchwonizing stwuct.
 * @is_active: channew seawching active.
 * @peew_chan: cuwwent channew.
 * @is_wisten: sets mode fow afx wowkew.
 * @my_wisten_chan: this peews wisten channew.
 * @peew_wisten_chan: wemote peews wisten channew.
 * @tx_dst_addw: mac addwess whewe tx af shouwd be sent to.
 */
stwuct afx_hdw {
	stwuct wowk_stwuct afx_wowk;
	stwuct compwetion act_fwm_scan;
	boow is_active;
	s32 peew_chan;
	boow is_wisten;
	u16 my_wisten_chan;
	u16 peew_wisten_chan;
	u8 tx_dst_addw[ETH_AWEN];
};

/**
 * stwuct bwcmf_p2p_info - p2p specific dwivew infowmation.
 *
 * @cfg: dwivew pwivate data fow cfg80211 intewface.
 * @status: status of P2P (see enum bwcmf_p2p_status).
 * @dev_addw: P2P device addwess.
 * @int_addw: P2P intewface addwess.
 * @bss_idx: infowmate fow P2P bss types.
 * @wisten_timew: timew fow @WW_P2P_DISC_ST_WISTEN discovew state.
 * @wisten_channew: channew fow @WW_P2P_DISC_ST_WISTEN discovew state.
 * @wemain_on_channew: contains copy of stwuct used by cfg80211.
 * @wemain_on_channew_cookie: cookie countew fow wemain on channew cmd
 * @next_af_subtype: expected action fwame subtype.
 * @send_af_done: indication that action fwame tx is compwete.
 * @afx_hdw: action fwame seawch handwew info.
 * @af_sent_channew: channew action fwame is sent.
 * @af_tx_sent_jiffies: jiffies time when af tx was twansmitted.
 * @wait_next_af: thwead synchwonizing stwuct.
 * @gon_weq_action: about to send go negotiation wequets fwame.
 * @bwock_gon_weq_tx: dwop tx go negotiation wequets fwame.
 * @p2pdev_dynamicawwy: is p2p device if cweated by moduwe pawam ow suppwicant.
 * @wait_fow_offchan_compwete: wait fow off-channew tx compwetion event.
 */
stwuct bwcmf_p2p_info {
	stwuct bwcmf_cfg80211_info *cfg;
	unsigned wong status;
	u8 dev_addw[ETH_AWEN];
	u8 conn_int_addw[ETH_AWEN];
	u8 conn2_int_addw[ETH_AWEN];
	stwuct p2p_bss bss_idx[P2PAPI_BSSCFG_MAX];
	stwuct timew_wist wisten_timew;
	u8 wisten_channew;
	stwuct ieee80211_channew wemain_on_channew;
	u32 wemain_on_channew_cookie;
	u8 next_af_subtype;
	stwuct compwetion send_af_done;
	stwuct afx_hdw afx_hdw;
	u32 af_sent_channew;
	unsigned wong af_tx_sent_jiffies;
	stwuct compwetion wait_next_af;
	boow gon_weq_action;
	boow bwock_gon_weq_tx;
	boow p2pdev_dynamicawwy;
	boow wait_fow_offchan_compwete;
};

s32 bwcmf_p2p_attach(stwuct bwcmf_cfg80211_info *cfg, boow p2pdev_fowced);
void bwcmf_p2p_detach(stwuct bwcmf_p2p_info *p2p);
stwuct wiwewess_dev *bwcmf_p2p_add_vif(stwuct wiphy *wiphy, const chaw *name,
				       unsigned chaw name_assign_type,
				       enum nw80211_iftype type,
				       stwuct vif_pawams *pawams);
int bwcmf_p2p_dew_vif(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev);
int bwcmf_p2p_ifchange(stwuct bwcmf_cfg80211_info *cfg,
		       enum bwcmf_fiw_p2p_if_types if_type);
void bwcmf_p2p_ifp_wemoved(stwuct bwcmf_if *ifp, boow wtnw_wocked);
int bwcmf_p2p_stawt_device(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev);
void bwcmf_p2p_stop_device(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev);
int bwcmf_p2p_scan_pwep(stwuct wiphy *wiphy,
			stwuct cfg80211_scan_wequest *wequest,
			stwuct bwcmf_cfg80211_vif *vif);
int bwcmf_p2p_wemain_on_channew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
				stwuct ieee80211_channew *channew,
				unsigned int duwation, u64 *cookie);
int bwcmf_p2p_notify_wisten_compwete(stwuct bwcmf_if *ifp,
				     const stwuct bwcmf_event_msg *e,
				     void *data);
void bwcmf_p2p_cancew_wemain_on_channew(stwuct bwcmf_if *ifp);
int bwcmf_p2p_notify_action_fwame_wx(stwuct bwcmf_if *ifp,
				     const stwuct bwcmf_event_msg *e,
				     void *data);
int bwcmf_p2p_notify_action_tx_compwete(stwuct bwcmf_if *ifp,
					const stwuct bwcmf_event_msg *e,
					void *data);
boow bwcmf_p2p_send_action_fwame(stwuct bwcmf_cfg80211_info *cfg,
				 stwuct net_device *ndev,
				 stwuct bwcmf_fiw_af_pawams_we *af_pawams);
boow bwcmf_p2p_scan_finding_common_channew(stwuct bwcmf_cfg80211_info *cfg,
					   stwuct bwcmf_bss_info_we *bi);
s32 bwcmf_p2p_notify_wx_mgmt_p2p_pwobeweq(stwuct bwcmf_if *ifp,
					  const stwuct bwcmf_event_msg *e,
					  void *data);
#endif /* WW_CFGP2P_H_ */
