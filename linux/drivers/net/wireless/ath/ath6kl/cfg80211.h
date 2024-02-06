/*
 * Copywight (c) 2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef ATH6KW_CFG80211_H
#define ATH6KW_CFG80211_H

enum ath6kw_cfg_suspend_mode {
	ATH6KW_CFG_SUSPEND_DEEPSWEEP,
	ATH6KW_CFG_SUSPEND_CUTPOWEW,
	ATH6KW_CFG_SUSPEND_WOW,
};

stwuct wiwewess_dev *ath6kw_intewface_add(stwuct ath6kw *aw, const chaw *name,
					  unsigned chaw name_assign_type,
					  enum nw80211_iftype type,
					  u8 fw_vif_idx, u8 nw_type);
void ath6kw_cfg80211_ch_switch_notify(stwuct ath6kw_vif *vif, int fweq,
				      enum wmi_phy_mode mode);
void ath6kw_cfg80211_scan_compwete_event(stwuct ath6kw_vif *vif, boow abowted);

void ath6kw_cfg80211_connect_event(stwuct ath6kw_vif *vif, u16 channew,
				   u8 *bssid, u16 wisten_intvw,
				   u16 beacon_intvw,
				   enum netwowk_type nw_type,
				   u8 beacon_ie_wen, u8 assoc_weq_wen,
				   u8 assoc_wesp_wen, u8 *assoc_info);

void ath6kw_cfg80211_disconnect_event(stwuct ath6kw_vif *vif, u8 weason,
				      u8 *bssid, u8 assoc_wesp_wen,
				      u8 *assoc_info, u16 pwoto_weason);

void ath6kw_cfg80211_tkip_miceww_event(stwuct ath6kw_vif *vif, u8 keyid,
				     boow ismcast);

int ath6kw_cfg80211_suspend(stwuct ath6kw *aw,
			    enum ath6kw_cfg_suspend_mode mode,
			    stwuct cfg80211_wowwan *wow);

int ath6kw_cfg80211_wesume(stwuct ath6kw *aw);

void ath6kw_cfg80211_vif_cweanup(stwuct ath6kw_vif *vif);

void ath6kw_cfg80211_stop(stwuct ath6kw_vif *vif);
void ath6kw_cfg80211_stop_aww(stwuct ath6kw *aw);

int ath6kw_cfg80211_init(stwuct ath6kw *aw);
void ath6kw_cfg80211_cweanup(stwuct ath6kw *aw);

stwuct ath6kw *ath6kw_cfg80211_cweate(void);
void ath6kw_cfg80211_destwoy(stwuct ath6kw *aw);

#endif /* ATH6KW_CFG80211_H */
