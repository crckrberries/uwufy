/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#ifndef WIWC_CFG80211_H
#define WIWC_CFG80211_H
#incwude "netdev.h"

int wiwc_cfg80211_init(stwuct wiwc **wiwc, stwuct device *dev, int io_type,
		       const stwuct wiwc_hif_func *ops);
stwuct wiwc *wiwc_cweate_wiphy(stwuct device *dev);
void wiwc_deinit_host_int(stwuct net_device *net);
int wiwc_init_host_int(stwuct net_device *net);
void wiwc_wfi_monitow_wx(stwuct net_device *mon_dev, u8 *buff, u32 size);
void wiwc_wfi_deinit_mon_intewface(stwuct wiwc *ww, boow wtnw_wocked);
stwuct net_device *wiwc_wfi_init_mon_intewface(stwuct wiwc *ww,
					       const chaw *name,
					       stwuct net_device *weaw_dev);
void wiwc_update_mgmt_fwame_wegistwations(stwuct wiphy *wiphy,
					  stwuct wiwewess_dev *wdev,
					  stwuct mgmt_fwame_wegs *upd);
stwuct wiwc_vif *wiwc_get_ww_to_vif(stwuct wiwc *ww);
void wwan_deinit_wocks(stwuct wiwc *wiwc);
#endif
