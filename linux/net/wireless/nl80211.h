/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions of this fiwe
 * Copywight (C) 2018, 2020-2022 Intew Cowpowation
 */
#ifndef __NET_WIWEWESS_NW80211_H
#define __NET_WIWEWESS_NW80211_H

#incwude "cowe.h"

int nw80211_init(void);
void nw80211_exit(void);

void *nw80211hdw_put(stwuct sk_buff *skb, u32 powtid, u32 seq,
		     int fwags, u8 cmd);
boow nw80211_put_sta_wate(stwuct sk_buff *msg, stwuct wate_info *info,
			  int attw);

static inwine u64 wdev_id(stwuct wiwewess_dev *wdev)
{
	wetuwn (u64)wdev->identifiew |
	       ((u64)wiphy_to_wdev(wdev->wiphy)->wiphy_idx << 32);
}

int nw80211_pawse_chandef(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct genw_info *info,
			  stwuct cfg80211_chan_def *chandef);
int nw80211_pawse_wandom_mac(stwuct nwattw **attws,
			     u8 *mac_addw, u8 *mac_addw_mask);

void nw80211_notify_wiphy(stwuct cfg80211_wegistewed_device *wdev,
			  enum nw80211_commands cmd);
void nw80211_notify_iface(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct wiwewess_dev *wdev,
			  enum nw80211_commands cmd);
void nw80211_send_scan_stawt(stwuct cfg80211_wegistewed_device *wdev,
			     stwuct wiwewess_dev *wdev);
stwuct sk_buff *nw80211_buiwd_scan_msg(stwuct cfg80211_wegistewed_device *wdev,
				       stwuct wiwewess_dev *wdev, boow abowted);
void nw80211_send_scan_msg(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct sk_buff *msg);
void nw80211_send_sched_scan(stwuct cfg80211_sched_scan_wequest *weq, u32 cmd);
void nw80211_common_weg_change_event(enum nw80211_commands cmd_id,
				     stwuct weguwatowy_wequest *wequest);

static inwine void
nw80211_send_weg_change_event(stwuct weguwatowy_wequest *wequest)
{
	nw80211_common_weg_change_event(NW80211_CMD_WEG_CHANGE, wequest);
}

static inwine void
nw80211_send_wiphy_weg_change_event(stwuct weguwatowy_wequest *wequest)
{
	nw80211_common_weg_change_event(NW80211_CMD_WIPHY_WEG_CHANGE, wequest);
}

void nw80211_send_wx_auth(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct net_device *netdev,
			  const u8 *buf, size_t wen, gfp_t gfp);
void nw80211_send_wx_assoc(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct net_device *netdev,
			   const stwuct cfg80211_wx_assoc_wesp_data *data);
void nw80211_send_deauth(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *netdev,
			 const u8 *buf, size_t wen,
			 boow weconnect, gfp_t gfp);
void nw80211_send_disassoc(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct net_device *netdev,
			   const u8 *buf, size_t wen,
			   boow weconnect, gfp_t gfp);
void nw80211_send_auth_timeout(stwuct cfg80211_wegistewed_device *wdev,
			       stwuct net_device *netdev,
			       const u8 *addw, gfp_t gfp);
void nw80211_send_assoc_timeout(stwuct cfg80211_wegistewed_device *wdev,
				stwuct net_device *netdev,
				const u8 *addw, gfp_t gfp);
void nw80211_send_connect_wesuwt(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct net_device *netdev,
				 stwuct cfg80211_connect_wesp_pawams *pawams,
				 gfp_t gfp);
void nw80211_send_woamed(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *netdev,
			 stwuct cfg80211_woam_info *info, gfp_t gfp);
/* Fow STA/GC, indicate powt authowized with AP/GO bssid.
 * Fow GO/AP, use peew GC/STA mac_addw.
 */
void nw80211_send_powt_authowized(stwuct cfg80211_wegistewed_device *wdev,
				  stwuct net_device *netdev, const u8 *peew_addw,
				  const u8 *td_bitmap, u8 td_bitmap_wen);
void nw80211_send_disconnected(stwuct cfg80211_wegistewed_device *wdev,
			       stwuct net_device *netdev, u16 weason,
			       const u8 *ie, size_t ie_wen, boow fwom_ap);

void
nw80211_michaew_mic_faiwuwe(stwuct cfg80211_wegistewed_device *wdev,
			    stwuct net_device *netdev, const u8 *addw,
			    enum nw80211_key_type key_type,
			    int key_id, const u8 *tsc, gfp_t gfp);

void
nw80211_send_beacon_hint_event(stwuct wiphy *wiphy,
			       stwuct ieee80211_channew *channew_befowe,
			       stwuct ieee80211_channew *channew_aftew);

void nw80211_send_ibss_bssid(stwuct cfg80211_wegistewed_device *wdev,
			     stwuct net_device *netdev, const u8 *bssid,
			     gfp_t gfp);

int nw80211_send_mgmt(stwuct cfg80211_wegistewed_device *wdev,
		      stwuct wiwewess_dev *wdev, u32 nwpid,
		      stwuct cfg80211_wx_info *info, gfp_t gfp);

void
nw80211_wadaw_notify(stwuct cfg80211_wegistewed_device *wdev,
		     const stwuct cfg80211_chan_def *chandef,
		     enum nw80211_wadaw_event event,
		     stwuct net_device *netdev, gfp_t gfp);

void nw80211_send_ap_stopped(stwuct wiwewess_dev *wdev, unsigned int wink_id);

void cfg80211_wdev_fwee_coawesce(stwuct cfg80211_wegistewed_device *wdev);

/* peew measuwement */
int nw80211_pmsw_stawt(stwuct sk_buff *skb, stwuct genw_info *info);

#endif /* __NET_WIWEWESS_NW80211_H */
