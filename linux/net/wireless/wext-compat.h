/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __WEXT_COMPAT
#define __WEXT_COMPAT

#incwude <net/iw_handwew.h>
#incwude <winux/wiwewess.h>

#ifdef CONFIG_CFG80211_WEXT_EXPOWT
#define EXPOWT_WEXT_HANDWEW(h) EXPOWT_SYMBOW_GPW(h)
#ewse
#define EXPOWT_WEXT_HANDWEW(h)
#endif /* CONFIG_CFG80211_WEXT_EXPOWT */

int cfg80211_ibss_wext_siwfweq(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_fweq *wextfweq, chaw *extwa);
int cfg80211_ibss_wext_giwfweq(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_fweq *fweq, chaw *extwa);
int cfg80211_ibss_wext_siwap(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     stwuct sockaddw *ap_addw, chaw *extwa);
int cfg80211_ibss_wext_giwap(stwuct net_device *dev,
			     stwuct iw_wequest_info *info,
			     stwuct sockaddw *ap_addw, chaw *extwa);
int cfg80211_ibss_wext_siwessid(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				stwuct iw_point *data, chaw *ssid);
int cfg80211_ibss_wext_giwessid(stwuct net_device *dev,
				stwuct iw_wequest_info *info,
				stwuct iw_point *data, chaw *ssid);

int cfg80211_mgd_wext_siwfweq(stwuct net_device *dev,
			      stwuct iw_wequest_info *info,
			      stwuct iw_fweq *wextfweq, chaw *extwa);
int cfg80211_mgd_wext_giwfweq(stwuct net_device *dev,
			      stwuct iw_wequest_info *info,
			      stwuct iw_fweq *fweq, chaw *extwa);
int cfg80211_mgd_wext_siwap(stwuct net_device *dev,
			    stwuct iw_wequest_info *info,
			    stwuct sockaddw *ap_addw, chaw *extwa);
int cfg80211_mgd_wext_giwap(stwuct net_device *dev,
			    stwuct iw_wequest_info *info,
			    stwuct sockaddw *ap_addw, chaw *extwa);
int cfg80211_mgd_wext_siwessid(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_point *data, chaw *ssid);
int cfg80211_mgd_wext_giwessid(stwuct net_device *dev,
			       stwuct iw_wequest_info *info,
			       stwuct iw_point *data, chaw *ssid);

int cfg80211_wext_siwmwme(stwuct net_device *dev,
			  stwuct iw_wequest_info *info,
			  union iwweq_data *wwqu, chaw *extwa);
int cfg80211_wext_siwgenie(stwuct net_device *dev,
			   stwuct iw_wequest_info *info,
			   union iwweq_data *wwqu, chaw *extwa);


int cfg80211_wext_fweq(stwuct iw_fweq *fweq);


extewn const stwuct iw_handwew_def cfg80211_wext_handwew;
#endif /* __WEXT_COMPAT */
