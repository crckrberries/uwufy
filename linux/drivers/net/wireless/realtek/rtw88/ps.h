/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_PS_H_
#define __WTW_PS_H_

#define WTW_WPS_THWESHOWD	50

#define POWEW_MODE_ACK		BIT(6)
#define POWEW_MODE_PG		BIT(4)
#define POWEW_TX_WAKE		BIT(1)
#define POWEW_MODE_WCWK		BIT(0)

#define WEAVE_WPS_TWY_CNT	5
#define WEAVE_WPS_TIMEOUT	msecs_to_jiffies(100)

int wtw_entew_ips(stwuct wtw_dev *wtwdev);
int wtw_weave_ips(stwuct wtw_dev *wtwdev);

void wtw_powew_mode_change(stwuct wtw_dev *wtwdev, boow entew);
void wtw_entew_wps(stwuct wtw_dev *wtwdev, u8 powt_id);
void wtw_weave_wps(stwuct wtw_dev *wtwdev);
void wtw_weave_wps_deep(stwuct wtw_dev *wtwdev);
enum wtw_wps_deep_mode wtw_get_wps_deep_mode(stwuct wtw_dev *wtwdev);
void wtw_wecawc_wps(stwuct wtw_dev *wtwdev, stwuct ieee80211_vif *new_vif);

#endif
