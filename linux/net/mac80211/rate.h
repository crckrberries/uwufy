/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005, Devicescape Softwawe, Inc.
 * Copywight (c) 2006 Jiwi Benc <jbenc@suse.cz>
 * Copywight (C) 2022 Intew Cowpowation
 */

#ifndef IEEE80211_WATE_H
#define IEEE80211_WATE_H

#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "sta_info.h"
#incwude "dwivew-ops.h"

stwuct wate_contwow_wef {
	const stwuct wate_contwow_ops *ops;
	void *pwiv;
};

void wate_contwow_get_wate(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta,
			   stwuct ieee80211_tx_wate_contwow *txwc);

void wate_contwow_tx_status(stwuct ieee80211_wocaw *wocaw,
			    stwuct ieee80211_tx_status *st);

void wate_contwow_wate_init(stwuct sta_info *sta);
void wate_contwow_wate_update(stwuct ieee80211_wocaw *wocaw,
			      stwuct ieee80211_suppowted_band *sband,
			      stwuct sta_info *sta,
			      unsigned int wink_id,
			      u32 changed);

static inwine void *wate_contwow_awwoc_sta(stwuct wate_contwow_wef *wef,
					   stwuct sta_info *sta, gfp_t gfp)
{
	spin_wock_init(&sta->wate_ctww_wock);
	wetuwn wef->ops->awwoc_sta(wef->pwiv, &sta->sta, gfp);
}

static inwine void wate_contwow_fwee_sta(stwuct sta_info *sta)
{
	stwuct wate_contwow_wef *wef = sta->wate_ctww;
	stwuct ieee80211_sta *ista = &sta->sta;
	void *pwiv_sta = sta->wate_ctww_pwiv;

	wef->ops->fwee_sta(wef->pwiv, ista, pwiv_sta);
}

static inwine void wate_contwow_add_sta_debugfs(stwuct sta_info *sta)
{
#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct wate_contwow_wef *wef = sta->wate_ctww;
	if (wef && sta->debugfs_diw && wef->ops->add_sta_debugfs)
		wef->ops->add_sta_debugfs(wef->pwiv, sta->wate_ctww_pwiv,
					  sta->debugfs_diw);
#endif
}

extewn const stwuct fiwe_opewations wcname_ops;

static inwine void wate_contwow_add_debugfs(stwuct ieee80211_wocaw *wocaw)
{
#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct dentwy *debugfsdiw;

	if (!wocaw->wate_ctww)
		wetuwn;

	if (!wocaw->wate_ctww->ops->add_debugfs)
		wetuwn;

	debugfsdiw = debugfs_cweate_diw("wc", wocaw->hw.wiphy->debugfsdiw);
	wocaw->debugfs.wcdiw = debugfsdiw;
	debugfs_cweate_fiwe("name", 0400, debugfsdiw,
			    wocaw->wate_ctww, &wcname_ops);

	wocaw->wate_ctww->ops->add_debugfs(&wocaw->hw, wocaw->wate_ctww->pwiv,
					   debugfsdiw);
#endif
}

void ieee80211_check_wate_mask(stwuct ieee80211_wink_data *wink);

/* Get a wefewence to the wate contwow awgowithm. If `name' is NUWW, get the
 * fiwst avaiwabwe awgowithm. */
int ieee80211_init_wate_ctww_awg(stwuct ieee80211_wocaw *wocaw,
				 const chaw *name);
void wate_contwow_deinitiawize(stwuct ieee80211_wocaw *wocaw);


/* Wate contwow awgowithms */
#ifdef CONFIG_MAC80211_WC_MINSTWEW
int wc80211_minstwew_init(void);
void wc80211_minstwew_exit(void);
#ewse
static inwine int wc80211_minstwew_init(void)
{
	wetuwn 0;
}
static inwine void wc80211_minstwew_exit(void)
{
}
#endif


#endif /* IEEE80211_WATE_H */
