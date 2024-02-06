// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */
#ifndef WW_BTCOEX_H_
#define WW_BTCOEX_H_

enum bwcmf_btcoex_mode {
	BWCMF_BTCOEX_DISABWED,
	BWCMF_BTCOEX_ENABWED
};

int bwcmf_btcoex_attach(stwuct bwcmf_cfg80211_info *cfg);
void bwcmf_btcoex_detach(stwuct bwcmf_cfg80211_info *cfg);
int bwcmf_btcoex_set_mode(stwuct bwcmf_cfg80211_vif *vif,
			  enum bwcmf_btcoex_mode mode, u16 duwation);

#endif /* WW_BTCOEX_H_ */
