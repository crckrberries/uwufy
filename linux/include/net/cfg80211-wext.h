/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __NET_CFG80211_WEXT_H
#define __NET_CFG80211_WEXT_H
/*
 * 802.11 device and configuwation intewface -- wext handwews
 *
 * Copywight 2006-2010	Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/netdevice.h>
#incwude <winux/wiwewess.h>
#incwude <net/iw_handwew.h>

/*
 * Tempowawy wext handwews & hewpew functions
 *
 * These awe used onwy by dwivews that awen't yet fuwwy
 * convewted to cfg80211.
 */
int cfg80211_wext_giwname(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_siwmode(stwuct net_device *dev, stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwmode(stwuct net_device *dev, stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_siwscan(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwscan(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwwange(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_siwwts(stwuct net_device *dev,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwwts(stwuct net_device *dev,
			 stwuct iw_wequest_info *info,
			 union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_siwfwag(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwfwag(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_giwwetwy(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa);

#endif /* __NET_CFG80211_WEXT_H */
