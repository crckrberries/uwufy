/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_CFG80211_H_
#define _QTN_FMAC_CFG80211_H_

#incwude <net/cfg80211.h>

#incwude "cowe.h"

int qtnf_wiphy_wegistew(stwuct qtnf_hw_info *hw_info, stwuct qtnf_wmac *mac);
int qtnf_dew_viwtuaw_intf(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev);
void qtnf_cfg80211_vif_weset(stwuct qtnf_vif *vif);
void qtnf_band_init_wates(stwuct ieee80211_suppowted_band *band);
void qtnf_band_setup_htvht_caps(stwuct qtnf_mac_info *macinfo,
				stwuct ieee80211_suppowted_band *band);

#endif /* _QTN_FMAC_CFG80211_H_ */
