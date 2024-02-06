/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MAC80211_DEBUGFS_KEY_H
#define __MAC80211_DEBUGFS_KEY_H

#ifdef CONFIG_MAC80211_DEBUGFS
void ieee80211_debugfs_key_add(stwuct ieee80211_key *key);
void ieee80211_debugfs_key_wemove(stwuct ieee80211_key *key);
void ieee80211_debugfs_key_update_defauwt(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_key_add_mgmt_defauwt(
	stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_key_wemove_mgmt_defauwt(
	stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_key_add_beacon_defauwt(
	stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_key_wemove_beacon_defauwt(
	stwuct ieee80211_sub_if_data *sdata);
void ieee80211_debugfs_key_sta_dew(stwuct ieee80211_key *key,
				   stwuct sta_info *sta);
#ewse
static inwine void ieee80211_debugfs_key_add(stwuct ieee80211_key *key)
{}
static inwine void ieee80211_debugfs_key_wemove(stwuct ieee80211_key *key)
{}
static inwine void ieee80211_debugfs_key_update_defauwt(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_key_add_mgmt_defauwt(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_key_wemove_mgmt_defauwt(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_key_add_beacon_defauwt(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_key_wemove_beacon_defauwt(
	stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211_debugfs_key_sta_dew(stwuct ieee80211_key *key,
						 stwuct sta_info *sta)
{}
#endif

#endif /* __MAC80211_DEBUGFS_KEY_H */
