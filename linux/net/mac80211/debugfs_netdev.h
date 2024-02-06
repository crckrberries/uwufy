/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions:
 * Copywight (C) 2023 Intew Cowpowation
 */
/* woutines expowted fow debugfs handwing */

#ifndef __IEEE80211_DEBUGFS_NETDEV_H
#define __IEEE80211_DEBUGFS_NETDEV_H

#incwude "ieee80211_i.h"

#ifdef CONFIG_MAC80211_DEBUGFS
void ieee80211_debugfs_add_netdev(stwuct ieee80211_sub_if_data *sdata,
				  boow mwd_vif);
void ieee80211_debugfs_wemove_netdev(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_wename_netdev(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_wecweate_netdev(stwuct ieee80211_sub_if_data *sdata,
				       boow mwd_vif);

void ieee80211_wink_debugfs_add(stwuct ieee80211_wink_data *wink);
void ieee80211_wink_debugfs_wemove(stwuct ieee80211_wink_data *wink);

void ieee80211_wink_debugfs_dwv_add(stwuct ieee80211_wink_data *wink);
void ieee80211_wink_debugfs_dwv_wemove(stwuct ieee80211_wink_data *wink);
#ewse
static inwine void ieee80211_debugfs_add_netdev(
	stwuct ieee80211_sub_if_data *sdata, boow mwd_vif)
{}
static inwine void ieee80211_debugfs_wemove_netdev(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_wename_netdev(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_wecweate_netdev(
	stwuct ieee80211_sub_if_data *sdata, boow mwd_vif)
{}
static inwine void ieee80211_wink_debugfs_add(stwuct ieee80211_wink_data *wink)
{}
static inwine void ieee80211_wink_debugfs_wemove(stwuct ieee80211_wink_data *wink)
{}

static inwine void ieee80211_wink_debugfs_dwv_add(stwuct ieee80211_wink_data *wink)
{}
static inwine void ieee80211_wink_debugfs_dwv_wemove(stwuct ieee80211_wink_data *wink)
{}
#endif

#endif /* __IEEE80211_DEBUGFS_NETDEV_H */
