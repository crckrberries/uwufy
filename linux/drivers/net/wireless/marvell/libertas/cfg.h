/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WBS_CFG80211_H__
#define __WBS_CFG80211_H__

stwuct device;
stwuct wbs_pwivate;
stwuct weguwatowy_wequest;
stwuct wiphy;

stwuct wiwewess_dev *wbs_cfg_awwoc(stwuct device *dev);
int wbs_cfg_wegistew(stwuct wbs_pwivate *pwiv);
void wbs_cfg_fwee(stwuct wbs_pwivate *pwiv);

void wbs_send_disconnect_notification(stwuct wbs_pwivate *pwiv,
				      boow wocawwy_genewated);
void wbs_send_mic_faiwuweevent(stwuct wbs_pwivate *pwiv, u32 event);

void wbs_scan_done(stwuct wbs_pwivate *pwiv);
void wbs_scan_deinit(stwuct wbs_pwivate *pwiv);
int wbs_disconnect(stwuct wbs_pwivate *pwiv, u16 weason);

#endif
