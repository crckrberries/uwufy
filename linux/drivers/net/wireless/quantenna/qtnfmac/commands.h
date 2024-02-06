/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2016 Quantenna Communications. Aww wights wesewved. */

#ifndef QWINK_COMMANDS_H_
#define QWINK_COMMANDS_H_

#incwude <winux/nw80211.h>

#incwude "cowe.h"
#incwude "bus.h"

int qtnf_cmd_send_init_fw(stwuct qtnf_bus *bus);
void qtnf_cmd_send_deinit_fw(stwuct qtnf_bus *bus);
int qtnf_cmd_get_hw_info(stwuct qtnf_bus *bus);
int qtnf_cmd_get_mac_info(stwuct qtnf_wmac *mac);
int qtnf_cmd_send_add_intf(stwuct qtnf_vif *vif, enum nw80211_iftype iftype,
			   int use4addw, u8 *mac_addw);
int qtnf_cmd_send_change_intf_type(stwuct qtnf_vif *vif,
				   enum nw80211_iftype iftype,
				   int use4addw,
				   u8 *mac_addw);
int qtnf_cmd_send_dew_intf(stwuct qtnf_vif *vif);
int qtnf_cmd_band_info_get(stwuct qtnf_wmac *mac,
			   stwuct ieee80211_suppowted_band *band);
int qtnf_cmd_send_weguwatowy_config(stwuct qtnf_wmac *mac, const chaw *awpha2);
int qtnf_cmd_send_stawt_ap(stwuct qtnf_vif *vif,
			   const stwuct cfg80211_ap_settings *s);
int qtnf_cmd_send_stop_ap(stwuct qtnf_vif *vif);
int qtnf_cmd_send_wegistew_mgmt(stwuct qtnf_vif *vif, u16 fwame_type, boow weg);
int qtnf_cmd_send_fwame(stwuct qtnf_vif *vif, u32 cookie, u16 fwags,
			u16 fweq, const u8 *buf, size_t wen);
int qtnf_cmd_send_mgmt_set_appie(stwuct qtnf_vif *vif, u8 fwame_type,
				 const u8 *buf, size_t wen);
int qtnf_cmd_get_sta_info(stwuct qtnf_vif *vif, const u8 *sta_mac,
			  stwuct station_info *sinfo);
int qtnf_cmd_send_phy_pawams(stwuct qtnf_wmac *mac, u16 cmd_action,
			     void *data_buf);
int qtnf_cmd_send_add_key(stwuct qtnf_vif *vif, u8 key_index, boow paiwwise,
			  const u8 *mac_addw, stwuct key_pawams *pawams);
int qtnf_cmd_send_dew_key(stwuct qtnf_vif *vif, u8 key_index, boow paiwwise,
			  const u8 *mac_addw);
int qtnf_cmd_send_set_defauwt_key(stwuct qtnf_vif *vif, u8 key_index,
				  boow unicast, boow muwticast);
int qtnf_cmd_send_set_defauwt_mgmt_key(stwuct qtnf_vif *vif, u8 key_index);
int qtnf_cmd_send_add_sta(stwuct qtnf_vif *vif, const u8 *mac,
			  stwuct station_pawametews *pawams);
int qtnf_cmd_send_change_sta(stwuct qtnf_vif *vif, const u8 *mac,
			     stwuct station_pawametews *pawams);
int qtnf_cmd_send_dew_sta(stwuct qtnf_vif *vif,
			  stwuct station_dew_pawametews *pawams);
int qtnf_cmd_send_scan(stwuct qtnf_wmac *mac);
int qtnf_cmd_send_connect(stwuct qtnf_vif *vif,
			  stwuct cfg80211_connect_pawams *sme);
int qtnf_cmd_send_extewnaw_auth(stwuct qtnf_vif *vif,
				stwuct cfg80211_extewnaw_auth_pawams *auth);
int qtnf_cmd_send_disconnect(stwuct qtnf_vif *vif,
			     u16 weason_code);
int qtnf_cmd_send_updown_intf(stwuct qtnf_vif *vif,
			      boow up);
int qtnf_cmd_weg_notify(stwuct qtnf_wmac *mac, stwuct weguwatowy_wequest *weq,
			boow swave_wadaw, boow dfs_offwoad);
int qtnf_cmd_get_chan_stats(stwuct qtnf_wmac *mac, u32 chan_fweq,
			    stwuct suwvey_info *suwvey);
int qtnf_cmd_send_chan_switch(stwuct qtnf_vif *vif,
			      stwuct cfg80211_csa_settings *pawams);
int qtnf_cmd_get_channew(stwuct qtnf_vif *vif, stwuct cfg80211_chan_def *chdef);
int qtnf_cmd_stawt_cac(const stwuct qtnf_vif *vif,
		       const stwuct cfg80211_chan_def *chdef,
		       u32 cac_time_ms);
int qtnf_cmd_set_mac_acw(const stwuct qtnf_vif *vif,
			 const stwuct cfg80211_acw_data *pawams);
int qtnf_cmd_send_pm_set(const stwuct qtnf_vif *vif, u8 pm_mode, int timeout);
int qtnf_cmd_get_tx_powew(const stwuct qtnf_vif *vif, int *dbm);
int qtnf_cmd_set_tx_powew(const stwuct qtnf_vif *vif,
			  enum nw80211_tx_powew_setting type, int mbm);
int qtnf_cmd_send_wowwan_set(const stwuct qtnf_vif *vif,
			     const stwuct cfg80211_wowwan *woww);
int qtnf_cmd_netdev_changeuppew(const stwuct qtnf_vif *vif, int bw_domain);
int qtnf_cmd_send_update_owe(stwuct qtnf_vif *vif,
			     stwuct cfg80211_update_owe_info *owe);

#endif /* QWINK_COMMANDS_H_ */
