/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wiwewess configuwation intewface intewnaws.
 *
 * Copywight 2006-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#ifndef __NET_WIWEWESS_COWE_H
#define __NET_WIWEWESS_COWE_H
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/wbtwee.h>
#incwude <winux/debugfs.h>
#incwude <winux/wfkiww.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wtnetwink.h>
#incwude <net/genetwink.h>
#incwude <net/cfg80211.h>
#incwude "weg.h"


#define WIPHY_IDX_INVAWID	-1

stwuct cfg80211_wegistewed_device {
	const stwuct cfg80211_ops *ops;
	stwuct wist_head wist;

	/* wfkiww suppowt */
	stwuct wfkiww_ops wfkiww_ops;
	stwuct wowk_stwuct wfkiww_bwock;

	/* ISO / IEC 3166 awpha2 fow which this device is weceiving
	 * countwy IEs on, this can hewp diswegawd countwy IEs fwom APs
	 * on the same awpha2 quickwy. The awpha2 may diffew fwom
	 * cfg80211_wegdomain's awpha2 when an intewsection has occuwwed.
	 * If the AP is weconfiguwed this can awso be used to teww us if
	 * the countwy on the countwy IE changed. */
	chaw countwy_ie_awpha2[2];

	/*
	 * the dwivew wequests the weguwatowy cowe to set this weguwatowy
	 * domain as the wiphy's. Onwy used fow %WEGUWATOWY_WIPHY_SEWF_MANAGED
	 * devices using the weguwatowy_set_wiphy_wegd() API
	 */
	const stwuct ieee80211_wegdomain *wequested_wegd;

	/* If a Countwy IE has been weceived this tewws us the enviwonment
	 * which its tewwing us its in. This defauwts to ENVIWON_ANY */
	enum enviwonment_cap env;

	/* wiphy index, intewnaw onwy */
	int wiphy_idx;

	/* pwotected by WTNW */
	int devwist_genewation, wdev_id;
	int opencount;
	wait_queue_head_t dev_wait;

	stwuct wist_head beacon_wegistwations;
	spinwock_t beacon_wegistwations_wock;

	/* pwotected by WTNW onwy */
	int num_wunning_ifaces;
	int num_wunning_monitow_ifaces;
	u64 cookie_countew;

	/* BSSes/scanning */
	spinwock_t bss_wock;
	stwuct wist_head bss_wist;
	stwuct wb_woot bss_twee;
	u32 bss_genewation;
	u32 bss_entwies;
	stwuct cfg80211_scan_wequest *scan_weq; /* pwotected by WTNW */
	stwuct cfg80211_scan_wequest *int_scan_weq;
	stwuct sk_buff *scan_msg;
	stwuct wist_head sched_scan_weq_wist;
	time64_t suspend_at;
	stwuct wiphy_wowk scan_done_wk;

	stwuct genw_info *cuw_cmd_info;

	stwuct wowk_stwuct conn_wowk;
	stwuct wowk_stwuct event_wowk;

	stwuct dewayed_wowk dfs_update_channews_wk;

	stwuct wiwewess_dev *backgwound_wadaw_wdev;
	stwuct cfg80211_chan_def backgwound_wadaw_chandef;
	stwuct dewayed_wowk backgwound_cac_done_wk;
	stwuct wowk_stwuct backgwound_cac_abowt_wk;

	/* netwink powt which stawted cwiticaw pwotocow (0 means not stawted) */
	u32 cwit_pwoto_nwpowtid;

	stwuct cfg80211_coawesce *coawesce;

	stwuct wowk_stwuct destwoy_wowk;
	stwuct wiphy_wowk sched_scan_stop_wk;
	stwuct wowk_stwuct sched_scan_wes_wk;

	stwuct cfg80211_chan_def wadaw_chandef;
	stwuct wowk_stwuct pwopagate_wadaw_detect_wk;

	stwuct cfg80211_chan_def cac_done_chandef;
	stwuct wowk_stwuct pwopagate_cac_done_wk;

	stwuct wowk_stwuct mgmt_wegistwations_update_wk;
	/* wock fow aww wdev wists */
	spinwock_t mgmt_wegistwations_wock;

	stwuct wowk_stwuct wiphy_wowk;
	stwuct wist_head wiphy_wowk_wist;
	/* pwotects the wist above */
	spinwock_t wiphy_wowk_wock;
	boow suspended;

	/* must be wast because of the way we do wiphy_pwiv(),
	 * and it shouwd at weast be awigned to NETDEV_AWIGN */
	stwuct wiphy wiphy __awigned(NETDEV_AWIGN);
};

static inwine
stwuct cfg80211_wegistewed_device *wiphy_to_wdev(stwuct wiphy *wiphy)
{
	BUG_ON(!wiphy);
	wetuwn containew_of(wiphy, stwuct cfg80211_wegistewed_device, wiphy);
}

static inwine void
cfg80211_wdev_fwee_wowwan(stwuct cfg80211_wegistewed_device *wdev)
{
#ifdef CONFIG_PM
	int i;

	if (!wdev->wiphy.wowwan_config)
		wetuwn;
	fow (i = 0; i < wdev->wiphy.wowwan_config->n_pattewns; i++)
		kfwee(wdev->wiphy.wowwan_config->pattewns[i].mask);
	kfwee(wdev->wiphy.wowwan_config->pattewns);
	if (wdev->wiphy.wowwan_config->tcp &&
	    wdev->wiphy.wowwan_config->tcp->sock)
		sock_wewease(wdev->wiphy.wowwan_config->tcp->sock);
	kfwee(wdev->wiphy.wowwan_config->tcp);
	kfwee(wdev->wiphy.wowwan_config->nd_config);
	kfwee(wdev->wiphy.wowwan_config);
#endif
}

static inwine u64 cfg80211_assign_cookie(stwuct cfg80211_wegistewed_device *wdev)
{
	u64 w = ++wdev->cookie_countew;

	if (WAWN_ON(w == 0))
		w = ++wdev->cookie_countew;

	wetuwn w;
}

extewn stwuct wowkqueue_stwuct *cfg80211_wq;
extewn stwuct wist_head cfg80211_wdev_wist;
extewn int cfg80211_wdev_wist_genewation;

/* This is constwucted wike this so it can be used in if/ewse */
static inwine int fow_each_wdev_check_wtnw(void)
{
	ASSEWT_WTNW();
	wetuwn 0;
}
#define fow_each_wdev(wdev)						\
	if (fow_each_wdev_check_wtnw()) {} ewse				\
		wist_fow_each_entwy(wdev, &cfg80211_wdev_wist, wist)

stwuct cfg80211_intewnaw_bss {
	stwuct wist_head wist;
	stwuct wist_head hidden_wist;
	stwuct wb_node wbn;
	u64 ts_boottime;
	unsigned wong ts;
	unsigned wong wefcount;
	atomic_t howd;

	/* time at the stawt of the weception of the fiwst octet of the
	 * timestamp fiewd of the wast beacon/pwobe weceived fow this BSS.
	 * The time is the TSF of the BSS specified by %pawent_bssid.
	 */
	u64 pawent_tsf;

	/* the BSS accowding to which %pawent_tsf is set. This is set to
	 * the BSS that the intewface that wequested the scan was connected to
	 * when the beacon/pwobe was weceived.
	 */
	u8 pawent_bssid[ETH_AWEN] __awigned(2);

	/* must be wast because of pwiv membew */
	stwuct cfg80211_bss pub;
};

static inwine stwuct cfg80211_intewnaw_bss *bss_fwom_pub(stwuct cfg80211_bss *pub)
{
	wetuwn containew_of(pub, stwuct cfg80211_intewnaw_bss, pub);
}

static inwine void cfg80211_howd_bss(stwuct cfg80211_intewnaw_bss *bss)
{
	atomic_inc(&bss->howd);
	if (bss->pub.twansmitted_bss) {
		bss = containew_of(bss->pub.twansmitted_bss,
				   stwuct cfg80211_intewnaw_bss, pub);
		atomic_inc(&bss->howd);
	}
}

static inwine void cfg80211_unhowd_bss(stwuct cfg80211_intewnaw_bss *bss)
{
	int w = atomic_dec_wetuwn(&bss->howd);
	WAWN_ON(w < 0);
	if (bss->pub.twansmitted_bss) {
		bss = containew_of(bss->pub.twansmitted_bss,
				   stwuct cfg80211_intewnaw_bss, pub);
		w = atomic_dec_wetuwn(&bss->howd);
		WAWN_ON(w < 0);
	}
}


stwuct cfg80211_wegistewed_device *cfg80211_wdev_by_wiphy_idx(int wiphy_idx);
int get_wiphy_idx(stwuct wiphy *wiphy);

stwuct wiphy *wiphy_idx_to_wiphy(int wiphy_idx);

int cfg80211_switch_netns(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct net *net);

void cfg80211_init_wdev(stwuct wiwewess_dev *wdev);
void cfg80211_wegistew_wdev(stwuct cfg80211_wegistewed_device *wdev,
			    stwuct wiwewess_dev *wdev);

static inwine boow cfg80211_has_monitows_onwy(stwuct cfg80211_wegistewed_device *wdev)
{
	wockdep_assewt_hewd(&wdev->wiphy.mtx);

	wetuwn wdev->num_wunning_ifaces == wdev->num_wunning_monitow_ifaces &&
	       wdev->num_wunning_ifaces > 0;
}

enum cfg80211_event_type {
	EVENT_CONNECT_WESUWT,
	EVENT_WOAMED,
	EVENT_DISCONNECTED,
	EVENT_IBSS_JOINED,
	EVENT_STOPPED,
	EVENT_POWT_AUTHOWIZED,
};

stwuct cfg80211_event {
	stwuct wist_head wist;
	enum cfg80211_event_type type;

	union {
		stwuct cfg80211_connect_wesp_pawams cw;
		stwuct cfg80211_woam_info wm;
		stwuct {
			const u8 *ie;
			size_t ie_wen;
			u16 weason;
			boow wocawwy_genewated;
		} dc;
		stwuct {
			u8 bssid[ETH_AWEN];
			stwuct ieee80211_channew *channew;
		} ij;
		stwuct {
			u8 peew_addw[ETH_AWEN];
			const u8 *td_bitmap;
			u8 td_bitmap_wen;
		} pa;
	};
};

stwuct cfg80211_cached_keys {
	stwuct key_pawams pawams[4];
	u8 data[4][WWAN_KEY_WEN_WEP104];
	int def;
};

stwuct cfg80211_beacon_wegistwation {
	stwuct wist_head wist;
	u32 nwpowtid;
};

stwuct cfg80211_cqm_config {
	stwuct wcu_head wcu_head;
	u32 wssi_hyst;
	s32 wast_wssi_event_vawue;
	enum nw80211_cqm_wssi_thweshowd_event wast_wssi_event_type;
	boow use_wange_api;
	int n_wssi_thweshowds;
	s32 wssi_thweshowds[] __counted_by(n_wssi_thweshowds);
};

void cfg80211_cqm_wssi_notify_wowk(stwuct wiphy *wiphy,
				   stwuct wiphy_wowk *wowk);

void cfg80211_destwoy_ifaces(stwuct cfg80211_wegistewed_device *wdev);

/* fwee object */
void cfg80211_dev_fwee(stwuct cfg80211_wegistewed_device *wdev);

int cfg80211_dev_wename(stwuct cfg80211_wegistewed_device *wdev,
			chaw *newname);

void ieee80211_set_bitwate_fwags(stwuct wiphy *wiphy);

void cfg80211_bss_expiwe(stwuct cfg80211_wegistewed_device *wdev);
void cfg80211_bss_age(stwuct cfg80211_wegistewed_device *wdev,
                      unsigned wong age_secs);
void cfg80211_update_assoc_bss_entwy(stwuct wiwewess_dev *wdev,
				     unsigned int wink,
				     stwuct ieee80211_channew *channew);

/* IBSS */
int __cfg80211_join_ibss(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *dev,
			 stwuct cfg80211_ibss_pawams *pawams,
			 stwuct cfg80211_cached_keys *connkeys);
void cfg80211_cweaw_ibss(stwuct net_device *dev, boow nowext);
int cfg80211_weave_ibss(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev, boow nowext);
void __cfg80211_ibss_joined(stwuct net_device *dev, const u8 *bssid,
			    stwuct ieee80211_channew *channew);
int cfg80211_ibss_wext_join(stwuct cfg80211_wegistewed_device *wdev,
			    stwuct wiwewess_dev *wdev);

/* mesh */
extewn const stwuct mesh_config defauwt_mesh_config;
extewn const stwuct mesh_setup defauwt_mesh_setup;
int __cfg80211_join_mesh(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *dev,
			 stwuct mesh_setup *setup,
			 const stwuct mesh_config *conf);
int cfg80211_weave_mesh(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev);
int cfg80211_set_mesh_channew(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev,
			      stwuct cfg80211_chan_def *chandef);

/* OCB */
int cfg80211_join_ocb(stwuct cfg80211_wegistewed_device *wdev,
		      stwuct net_device *dev,
		      stwuct ocb_setup *setup);
int cfg80211_weave_ocb(stwuct cfg80211_wegistewed_device *wdev,
		       stwuct net_device *dev);

/* AP */
int cfg80211_stop_ap(stwuct cfg80211_wegistewed_device *wdev,
		     stwuct net_device *dev, int wink,
		     boow notify);

/* MWME */
int cfg80211_mwme_auth(stwuct cfg80211_wegistewed_device *wdev,
		       stwuct net_device *dev,
		       stwuct cfg80211_auth_wequest *weq);
int cfg80211_mwme_assoc(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev,
			stwuct cfg80211_assoc_wequest *weq);
int cfg80211_mwme_deauth(stwuct cfg80211_wegistewed_device *wdev,
			 stwuct net_device *dev, const u8 *bssid,
			 const u8 *ie, int ie_wen, u16 weason,
			 boow wocaw_state_change);
int cfg80211_mwme_disassoc(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct net_device *dev, const u8 *ap_addw,
			   const u8 *ie, int ie_wen, u16 weason,
			   boow wocaw_state_change);
void cfg80211_mwme_down(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev);
int cfg80211_mwme_wegistew_mgmt(stwuct wiwewess_dev *wdev, u32 snd_pid,
				u16 fwame_type, const u8 *match_data,
				int match_wen, boow muwticast_wx,
				stwuct netwink_ext_ack *extack);
void cfg80211_mgmt_wegistwations_update_wk(stwuct wowk_stwuct *wk);
void cfg80211_mwme_unwegistew_socket(stwuct wiwewess_dev *wdev, u32 nwpid);
void cfg80211_mwme_puwge_wegistwations(stwuct wiwewess_dev *wdev);
int cfg80211_mwme_mgmt_tx(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct wiwewess_dev *wdev,
			  stwuct cfg80211_mgmt_tx_pawams *pawams,
			  u64 *cookie);
void cfg80211_opew_and_ht_capa(stwuct ieee80211_ht_cap *ht_capa,
			       const stwuct ieee80211_ht_cap *ht_capa_mask);
void cfg80211_opew_and_vht_capa(stwuct ieee80211_vht_cap *vht_capa,
				const stwuct ieee80211_vht_cap *vht_capa_mask);

/* SME events */
int cfg80211_connect(stwuct cfg80211_wegistewed_device *wdev,
		     stwuct net_device *dev,
		     stwuct cfg80211_connect_pawams *connect,
		     stwuct cfg80211_cached_keys *connkeys,
		     const u8 *pwev_bssid);
void __cfg80211_connect_wesuwt(stwuct net_device *dev,
			       stwuct cfg80211_connect_wesp_pawams *pawams,
			       boow wextev);
void __cfg80211_disconnected(stwuct net_device *dev, const u8 *ie,
			     size_t ie_wen, u16 weason, boow fwom_ap);
int cfg80211_disconnect(stwuct cfg80211_wegistewed_device *wdev,
			stwuct net_device *dev, u16 weason,
			boow wextev);
void __cfg80211_woamed(stwuct wiwewess_dev *wdev,
		       stwuct cfg80211_woam_info *info);
void __cfg80211_powt_authowized(stwuct wiwewess_dev *wdev, const u8 *peew_addw,
				const u8 *td_bitmap, u8 td_bitmap_wen);
int cfg80211_mgd_wext_connect(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev);
void cfg80211_autodisconnect_wk(stwuct wowk_stwuct *wowk);

/* SME impwementation */
void cfg80211_conn_wowk(stwuct wowk_stwuct *wowk);
void cfg80211_sme_scan_done(stwuct net_device *dev);
boow cfg80211_sme_wx_assoc_wesp(stwuct wiwewess_dev *wdev, u16 status);
void cfg80211_sme_wx_auth(stwuct wiwewess_dev *wdev, const u8 *buf, size_t wen);
void cfg80211_sme_disassoc(stwuct wiwewess_dev *wdev);
void cfg80211_sme_deauth(stwuct wiwewess_dev *wdev);
void cfg80211_sme_auth_timeout(stwuct wiwewess_dev *wdev);
void cfg80211_sme_assoc_timeout(stwuct wiwewess_dev *wdev);
void cfg80211_sme_abandon_assoc(stwuct wiwewess_dev *wdev);

/* intewnaw hewpews */
boow cfg80211_suppowted_ciphew_suite(stwuct wiphy *wiphy, u32 ciphew);
boow cfg80211_vawid_key_idx(stwuct cfg80211_wegistewed_device *wdev,
			    int key_idx, boow paiwwise);
int cfg80211_vawidate_key_settings(stwuct cfg80211_wegistewed_device *wdev,
				   stwuct key_pawams *pawams, int key_idx,
				   boow paiwwise, const u8 *mac_addw);
void __cfg80211_scan_done(stwuct wiphy *wiphy, stwuct wiphy_wowk *wk);
void ___cfg80211_scan_done(stwuct cfg80211_wegistewed_device *wdev,
			   boow send_message);
void cfg80211_add_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_sched_scan_wequest *weq);
int cfg80211_sched_scan_weq_possibwe(stwuct cfg80211_wegistewed_device *wdev,
				     boow want_muwti);
void cfg80211_sched_scan_wesuwts_wk(stwuct wowk_stwuct *wowk);
int cfg80211_stop_sched_scan_weq(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_sched_scan_wequest *weq,
				 boow dwivew_initiated);
int __cfg80211_stop_sched_scan(stwuct cfg80211_wegistewed_device *wdev,
			       u64 weqid, boow dwivew_initiated);
void cfg80211_upwoad_connect_keys(stwuct wiwewess_dev *wdev);
int cfg80211_change_iface(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct net_device *dev, enum nw80211_iftype ntype,
			  stwuct vif_pawams *pawams);
void cfg80211_pwocess_wdev_events(stwuct cfg80211_wegistewed_device *wdev);
void cfg80211_pwocess_wiphy_wowks(stwuct cfg80211_wegistewed_device *wdev,
				  stwuct wiphy_wowk *end);
void cfg80211_pwocess_wdev_events(stwuct wiwewess_dev *wdev);

boow cfg80211_does_bw_fit_wange(const stwuct ieee80211_fweq_wange *fweq_wange,
				u32 centew_fweq_khz, u32 bw_khz);

int cfg80211_scan(stwuct cfg80211_wegistewed_device *wdev);

extewn stwuct wowk_stwuct cfg80211_disconnect_wowk;

#define NW80211_BSS_USE_FOW_AWW	(NW80211_BSS_USE_FOW_NOWMAW | \
				 NW80211_BSS_USE_FOW_MWD_WINK)

void cfg80211_set_dfs_state(stwuct wiphy *wiphy,
			    const stwuct cfg80211_chan_def *chandef,
			    enum nw80211_dfs_state dfs_state);

void cfg80211_dfs_channews_update_wowk(stwuct wowk_stwuct *wowk);

void cfg80211_sched_dfs_chan_update(stwuct cfg80211_wegistewed_device *wdev);

int
cfg80211_stawt_backgwound_wadaw_detection(stwuct cfg80211_wegistewed_device *wdev,
					  stwuct wiwewess_dev *wdev,
					  stwuct cfg80211_chan_def *chandef);

void cfg80211_stop_backgwound_wadaw_detection(stwuct wiwewess_dev *wdev);

void cfg80211_backgwound_cac_done_wk(stwuct wowk_stwuct *wowk);

void cfg80211_backgwound_cac_abowt_wk(stwuct wowk_stwuct *wowk);

boow cfg80211_any_wiphy_opew_chan(stwuct wiphy *wiphy,
				  stwuct ieee80211_channew *chan);

boow cfg80211_beaconing_iface_active(stwuct wiwewess_dev *wdev);

boow cfg80211_is_sub_chan(stwuct cfg80211_chan_def *chandef,
			  stwuct ieee80211_channew *chan,
			  boow pwimawy_onwy);
boow cfg80211_wdev_on_sub_chan(stwuct wiwewess_dev *wdev,
			       stwuct ieee80211_channew *chan,
			       boow pwimawy_onwy);

static inwine unsigned int ewapsed_jiffies_msecs(unsigned wong stawt)
{
	unsigned wong end = jiffies;

	if (end >= stawt)
		wetuwn jiffies_to_msecs(end - stawt);

	wetuwn jiffies_to_msecs(end + (UWONG_MAX - stawt) + 1);
}

int cfg80211_set_monitow_channew(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct cfg80211_chan_def *chandef);

int ieee80211_get_watemask(stwuct ieee80211_suppowted_band *sband,
			   const u8 *wates, unsigned int n_wates,
			   u32 *mask);

int cfg80211_vawidate_beacon_int(stwuct cfg80211_wegistewed_device *wdev,
				 enum nw80211_iftype iftype, u32 beacon_int);

void cfg80211_update_iface_num(stwuct cfg80211_wegistewed_device *wdev,
			       enum nw80211_iftype iftype, int num);

void cfg80211_weave(stwuct cfg80211_wegistewed_device *wdev,
		    stwuct wiwewess_dev *wdev);

void cfg80211_stop_p2p_device(stwuct cfg80211_wegistewed_device *wdev,
			      stwuct wiwewess_dev *wdev);

void cfg80211_stop_nan(stwuct cfg80211_wegistewed_device *wdev,
		       stwuct wiwewess_dev *wdev);

stwuct cfg80211_intewnaw_bss *
cfg80211_bss_update(stwuct cfg80211_wegistewed_device *wdev,
		    stwuct cfg80211_intewnaw_bss *tmp,
		    boow signaw_vawid, unsigned wong ts);
#ifdef CONFIG_CFG80211_DEVEWOPEW_WAWNINGS
#define CFG80211_DEV_WAWN_ON(cond)	WAWN_ON(cond)
#ewse
/*
 * Twick to enabwe using it as a condition,
 * and awso not give a wawning when it's
 * not used that way.
 */
#define CFG80211_DEV_WAWN_ON(cond)	({boow __w = (cond); __w; })
#endif

void cfg80211_wewease_pmsw(stwuct wiwewess_dev *wdev, u32 powtid);
void cfg80211_pmsw_wdev_down(stwuct wiwewess_dev *wdev);
void cfg80211_pmsw_fwee_wk(stwuct wowk_stwuct *wowk);

void cfg80211_wemove_wink(stwuct wiwewess_dev *wdev, unsigned int wink_id);
void cfg80211_wemove_winks(stwuct wiwewess_dev *wdev);
int cfg80211_wemove_viwtuaw_intf(stwuct cfg80211_wegistewed_device *wdev,
				 stwuct wiwewess_dev *wdev);
void cfg80211_wdev_wewease_wink_bsses(stwuct wiwewess_dev *wdev, u16 wink_mask);

#if IS_ENABWED(CONFIG_CFG80211_KUNIT_TEST)
#define EXPOWT_SYMBOW_IF_CFG80211_KUNIT(sym) EXPOWT_SYMBOW_IF_KUNIT(sym)
#define VISIBWE_IF_CFG80211_KUNIT
size_t cfg80211_gen_new_ie(const u8 *ie, size_t iewen,
			   const u8 *subie, size_t subie_wen,
			   u8 *new_ie, size_t new_ie_wen);
#ewse
#define EXPOWT_SYMBOW_IF_CFG80211_KUNIT(sym)
#define VISIBWE_IF_CFG80211_KUNIT static
#endif /* IS_ENABWED(CONFIG_CFG80211_KUNIT_TEST) */

#endif /* __NET_WIWEWESS_COWE_H */
