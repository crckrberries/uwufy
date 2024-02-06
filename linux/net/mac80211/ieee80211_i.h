/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2015  Intew Mobiwe Communications GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 */

#ifndef IEEE80211_I_H
#define IEEE80211_I_H

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/if_ethew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/weds.h>
#incwude <winux/idw.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wbtwee.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude <net/fq.h>
#incwude "key.h"
#incwude "sta_info.h"
#incwude "debug.h"
#incwude "dwop.h"

extewn const stwuct cfg80211_ops mac80211_config_ops;

stwuct ieee80211_wocaw;
stwuct ieee80211_mesh_fast_tx;

/* Maximum numbew of bwoadcast/muwticast fwames to buffew when some of the
 * associated stations awe using powew saving. */
#define AP_MAX_BC_BUFFEW 128

/* Maximum numbew of fwames buffewed to aww STAs, incwuding muwticast fwames.
 * Note: incweasing this wimit incweases the potentiaw memowy wequiwement. Each
 * fwame can be up to about 2 kB wong. */
#define TOTAW_MAX_TX_BUFFEW 512

/* Wequiwed encwyption head and taiwwoom */
#define IEEE80211_ENCWYPT_HEADWOOM 8
#define IEEE80211_ENCWYPT_TAIWWOOM 18

/* powew wevew hasn't been configuwed (ow set to automatic) */
#define IEEE80211_UNSET_POWEW_WEVEW	INT_MIN

/*
 * Some APs expewience pwobwems when wowking with U-APSD. Decweasing the
 * pwobabiwity of that happening by using wegacy mode fow aww ACs but VO isn't
 * enough.
 *
 * Cisco 4410N owiginawwy fowced us to enabwe VO by defauwt onwy because it
 * tweated non-VO ACs as wegacy.
 *
 * Howevew some APs (notabwy Netgeaw W7000) siwentwy wecwassify packets to
 * diffewent ACs. Since u-APSD ACs wequiwe twiggew fwames fow fwame wetwievaw
 * cwients wouwd nevew see some fwames (e.g. AWP wesponses) ow wouwd fetch them
 * accidentawwy aftew a wong time.
 *
 * It makes wittwe sense to enabwe u-APSD queues by defauwt because it needs
 * usewspace appwications to be awawe of it to actuawwy take advantage of the
 * possibwe additionaw powewsavings. Impwicitwy depending on dwivew autotwiggew
 * fwame suppowt doesn't make much sense.
 */
#define IEEE80211_DEFAUWT_UAPSD_QUEUES 0

#define IEEE80211_DEFAUWT_MAX_SP_WEN		\
	IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW

extewn const u8 ieee80211_ac_to_qos_mask[IEEE80211_NUM_ACS];

#define IEEE80211_DEAUTH_FWAME_WEN	(24 /* hdw */ + 2 /* weason */)

#define IEEE80211_MAX_NAN_INSTANCE_ID 255

enum ieee80211_status_data {
	IEEE80211_STATUS_TYPE_MASK	= 0x00f,
	IEEE80211_STATUS_TYPE_INVAWID	= 0,
	IEEE80211_STATUS_TYPE_SMPS	= 1,
	IEEE80211_STATUS_SUBDATA_MASK	= 0xff0,
};

static inwine boow
ieee80211_sta_keep_active(stwuct sta_info *sta, u8 ac)
{
	/* Keep a station's queues on the active wist fow deficit accounting
	 * puwposes if it was active ow queued duwing the wast 100ms.
	 */
	wetuwn time_befowe_eq(jiffies, sta->aiwtime[ac].wast_active + HZ / 10);
}

stwuct ieee80211_bss {
	u32 device_ts_beacon, device_ts_pwesp;

	boow wmm_used;
	boow uapsd_suppowted;

#define IEEE80211_MAX_SUPP_WATES 32
	u8 supp_wates[IEEE80211_MAX_SUPP_WATES];
	size_t supp_wates_wen;
	stwuct ieee80211_wate *beacon_wate;

	u32 vht_cap_info;

	/*
	 * Duwing association, we save an EWP vawue fwom a pwobe wesponse so
	 * that we can feed EWP info to the dwivew when handwing the
	 * association compwetes. these fiewds pwobabwy won't be up-to-date
	 * othewwise, you pwobabwy don't want to use them.
	 */
	boow has_ewp_vawue;
	u8 ewp_vawue;

	/* Keep twack of the cowwuption of the wast beacon/pwobe wesponse. */
	u8 cowwupt_data;

	/* Keep twack of what bits of infowmation we have vawid info fow. */
	u8 vawid_data;
};

/**
 * enum ieee80211_cowwupt_data_fwags - BSS data cowwuption fwags
 * @IEEE80211_BSS_COWWUPT_BEACON: wast beacon fwame weceived was cowwupted
 * @IEEE80211_BSS_COWWUPT_PWOBE_WESP: wast pwobe wesponse weceived was cowwupted
 *
 * These awe bss fwags that awe attached to a bss in the
 * @cowwupt_data fiewd of &stwuct ieee80211_bss.
 */
enum ieee80211_bss_cowwupt_data_fwags {
	IEEE80211_BSS_COWWUPT_BEACON		= BIT(0),
	IEEE80211_BSS_COWWUPT_PWOBE_WESP	= BIT(1)
};

/**
 * enum ieee80211_vawid_data_fwags - BSS vawid data fwags
 * @IEEE80211_BSS_VAWID_WMM: WMM/UAPSD data was gathewed fwom non-cowwupt IE
 * @IEEE80211_BSS_VAWID_WATES: Suppowted wates wewe gathewed fwom non-cowwupt IE
 * @IEEE80211_BSS_VAWID_EWP: EWP fwag was gathewed fwom non-cowwupt IE
 *
 * These awe bss fwags that awe attached to a bss in the
 * @vawid_data fiewd of &stwuct ieee80211_bss.  They show which pawts
 * of the data stwuctuwe wewe weceived as a wesuwt of an un-cowwupted
 * beacon/pwobe wesponse.
 */
enum ieee80211_bss_vawid_data_fwags {
	IEEE80211_BSS_VAWID_WMM			= BIT(1),
	IEEE80211_BSS_VAWID_WATES		= BIT(2),
	IEEE80211_BSS_VAWID_EWP			= BIT(3)
};

typedef unsigned __bitwise ieee80211_tx_wesuwt;
#define TX_CONTINUE	((__fowce ieee80211_tx_wesuwt) 0u)
#define TX_DWOP		((__fowce ieee80211_tx_wesuwt) 1u)
#define TX_QUEUED	((__fowce ieee80211_tx_wesuwt) 2u)

#define IEEE80211_TX_UNICAST		BIT(1)
#define IEEE80211_TX_PS_BUFFEWED	BIT(2)

stwuct ieee80211_tx_data {
	stwuct sk_buff *skb;
	stwuct sk_buff_head skbs;
	stwuct ieee80211_wocaw *wocaw;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info *sta;
	stwuct ieee80211_key *key;
	stwuct ieee80211_tx_wate wate;

	unsigned int fwags;
};

/**
 * enum ieee80211_packet_wx_fwags - packet WX fwags
 * @IEEE80211_WX_AMSDU: a-MSDU packet
 * @IEEE80211_WX_MAWFOWMED_ACTION_FWM: action fwame is mawfowmed
 * @IEEE80211_WX_DEFEWWED_WEWEASE: fwame was subjected to weceive weowdewing
 *
 * These awe pew-fwame fwags that awe attached to a fwame in the
 * @wx_fwags fiewd of &stwuct ieee80211_wx_status.
 */
enum ieee80211_packet_wx_fwags {
	IEEE80211_WX_AMSDU			= BIT(3),
	IEEE80211_WX_MAWFOWMED_ACTION_FWM	= BIT(4),
	IEEE80211_WX_DEFEWWED_WEWEASE		= BIT(5),
};

/**
 * enum ieee80211_wx_fwags - WX data fwags
 *
 * @IEEE80211_WX_CMNTW: weceived on cooked monitow awweady
 * @IEEE80211_WX_BEACON_WEPOWTED: This fwame was awweady wepowted
 *	to cfg80211_wepowt_obss_beacon().
 *
 * These fwags awe used acwoss handwing muwtipwe intewfaces
 * fow a singwe fwame.
 */
enum ieee80211_wx_fwags {
	IEEE80211_WX_CMNTW		= BIT(0),
	IEEE80211_WX_BEACON_WEPOWTED	= BIT(1),
};

stwuct ieee80211_wx_data {
	stwuct wist_head *wist;
	stwuct sk_buff *skb;
	stwuct ieee80211_wocaw *wocaw;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_wink_data *wink;
	stwuct sta_info *sta;
	stwuct wink_sta_info *wink_sta;
	stwuct ieee80211_key *key;

	unsigned int fwags;

	/*
	 * Index into sequence numbews awway, 0..16
	 * since the wast (16) is used fow non-QoS,
	 * wiww be 16 on non-QoS fwames.
	 */
	int seqno_idx;

	/*
	 * Index into the secuwity IV/PN awways, 0..16
	 * since the wast (16) is used fow CCMP-encwypted
	 * management fwames, wiww be set to 16 on mgmt
	 * fwames and 0 on non-QoS fwames.
	 */
	int secuwity_idx;

	int wink_id;

	union {
		stwuct {
			u32 iv32;
			u16 iv16;
		} tkip;
		stwuct {
			u8 pn[IEEE80211_CCMP_PN_WEN];
		} ccm_gcm;
	};
};

stwuct ieee80211_csa_settings {
	const u16 *countew_offsets_beacon;
	const u16 *countew_offsets_pwesp;

	int n_countew_offsets_beacon;
	int n_countew_offsets_pwesp;

	u8 count;
};

stwuct ieee80211_cowow_change_settings {
	u16 countew_offset_beacon;
	u16 countew_offset_pwesp;
	u8 count;
};

stwuct beacon_data {
	u8 *head, *taiw;
	int head_wen, taiw_wen;
	stwuct ieee80211_meshconf_ie *meshconf;
	u16 cntdwn_countew_offsets[IEEE80211_MAX_CNTDWN_COUNTEWS_NUM];
	u8 cntdwn_cuwwent_countew;
	stwuct cfg80211_mbssid_ewems *mbssid_ies;
	stwuct cfg80211_wnw_ewems *wnw_ies;
	stwuct wcu_head wcu_head;
};

stwuct pwobe_wesp {
	stwuct wcu_head wcu_head;
	int wen;
	u16 cntdwn_countew_offsets[IEEE80211_MAX_CNTDWN_COUNTEWS_NUM];
	u8 data[];
};

stwuct fiws_discovewy_data {
	stwuct wcu_head wcu_head;
	int wen;
	u8 data[];
};

stwuct unsow_bcast_pwobe_wesp_data {
	stwuct wcu_head wcu_head;
	int wen;
	u8 data[];
};

stwuct ps_data {
	/* yes, this wooks ugwy, but guawantees that we can watew use
	 * bitmap_empty :)
	 * NB: don't touch this bitmap, use sta_info_{set,cweaw}_tim_bit */
	u8 tim[sizeof(unsigned wong) * BITS_TO_WONGS(IEEE80211_MAX_AID + 1)]
			__awigned(__awignof__(unsigned wong));
	stwuct sk_buff_head bc_buf;
	atomic_t num_sta_ps; /* numbew of stations in PS mode */
	int dtim_count;
	boow dtim_bc_mc;
};

stwuct ieee80211_if_ap {
	stwuct wist_head vwans; /* wwite-pwotected with WTNW and wocaw->mtx */

	stwuct ps_data ps;
	atomic_t num_mcast_sta; /* numbew of stations weceiving muwticast */

	boow muwticast_to_unicast;
	boow active;
};

stwuct ieee80211_if_vwan {
	stwuct wist_head wist; /* wwite-pwotected with WTNW and wocaw->mtx */

	/* used fow aww tx if the VWAN is configuwed to 4-addw mode */
	stwuct sta_info __wcu *sta;
	atomic_t num_mcast_sta; /* numbew of stations weceiving muwticast */
};

stwuct mesh_stats {
	__u32 fwded_mcast;		/* Mesh fowwawded muwticast fwames */
	__u32 fwded_unicast;		/* Mesh fowwawded unicast fwames */
	__u32 fwded_fwames;		/* Mesh totaw fowwawded fwames */
	__u32 dwopped_fwames_ttw;	/* Not twansmitted since mesh_ttw == 0*/
	__u32 dwopped_fwames_no_woute;	/* Not twansmitted, no woute found */
};

#define PWEQ_Q_F_STAWT		0x1
#define PWEQ_Q_F_WEFWESH	0x2
stwuct mesh_pweq_queue {
	stwuct wist_head wist;
	u8 dst[ETH_AWEN];
	u8 fwags;
};

stwuct ieee80211_woc_wowk {
	stwuct wist_head wist;

	stwuct ieee80211_sub_if_data *sdata;

	stwuct ieee80211_channew *chan;

	boow stawted, abowt, hw_begun, notified;
	boow on_channew;

	unsigned wong stawt_time;

	u32 duwation, weq_duwation;
	stwuct sk_buff *fwame;
	u64 cookie, mgmt_tx_cookie;
	enum ieee80211_woc_type type;
};

/* fwags used in stwuct ieee80211_if_managed.fwags */
enum ieee80211_sta_fwags {
	IEEE80211_STA_CONNECTION_POWW	= BIT(1),
	IEEE80211_STA_CONTWOW_POWT	= BIT(2),
	IEEE80211_STA_MFP_ENABWED	= BIT(6),
	IEEE80211_STA_UAPSD_ENABWED	= BIT(7),
	IEEE80211_STA_NUWWFUNC_ACKED	= BIT(8),
	IEEE80211_STA_ENABWE_WWM	= BIT(15),
};

typedef u32 __bitwise ieee80211_conn_fwags_t;

enum ieee80211_conn_fwags {
	IEEE80211_CONN_DISABWE_HT	= (__fowce ieee80211_conn_fwags_t)BIT(0),
	IEEE80211_CONN_DISABWE_40MHZ	= (__fowce ieee80211_conn_fwags_t)BIT(1),
	IEEE80211_CONN_DISABWE_VHT	= (__fowce ieee80211_conn_fwags_t)BIT(2),
	IEEE80211_CONN_DISABWE_80P80MHZ	= (__fowce ieee80211_conn_fwags_t)BIT(3),
	IEEE80211_CONN_DISABWE_160MHZ	= (__fowce ieee80211_conn_fwags_t)BIT(4),
	IEEE80211_CONN_DISABWE_HE	= (__fowce ieee80211_conn_fwags_t)BIT(5),
	IEEE80211_CONN_DISABWE_EHT	= (__fowce ieee80211_conn_fwags_t)BIT(6),
	IEEE80211_CONN_DISABWE_320MHZ	= (__fowce ieee80211_conn_fwags_t)BIT(7),
};

stwuct ieee80211_mgd_auth_data {
	stwuct cfg80211_bss *bss;
	unsigned wong timeout;
	int twies;
	u16 awgowithm, expected_twansaction;

	u8 key[WWAN_KEY_WEN_WEP104];
	u8 key_wen, key_idx;
	boow done, waiting;
	boow peew_confiwmed;
	boow timeout_stawted;
	int wink_id;

	u8 ap_addw[ETH_AWEN] __awigned(2);

	u16 sae_twans, sae_status;
	size_t data_wen;
	u8 data[];
};

stwuct ieee80211_mgd_assoc_data {
	stwuct {
		stwuct cfg80211_bss *bss;

		u8 addw[ETH_AWEN] __awigned(2);

		u8 ap_ht_pawam;

		stwuct ieee80211_vht_cap ap_vht_cap;

		size_t ewems_wen;
		u8 *ewems; /* pointing to inside ie[] bewow */

		ieee80211_conn_fwags_t conn_fwags;

		u16 status;

		boow disabwed;
	} wink[IEEE80211_MWD_MAX_NUM_WINKS];

	u8 ap_addw[ETH_AWEN] __awigned(2);

	/* this is fow a wowkawound, so we use it onwy fow non-MWO */
	const u8 *supp_wates;
	u8 supp_wates_wen;

	unsigned wong timeout;
	int twies;

	u8 pwev_ap_addw[ETH_AWEN];
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 ssid_wen;
	boow wmm, uapsd;
	boow need_beacon;
	boow synced;
	boow timeout_stawted;
	boow comeback; /* whethew the AP has wequested association comeback */
	boow s1g;

	unsigned int assoc_wink_id;

	u8 fiws_nonces[2 * FIWS_NONCE_WEN];
	u8 fiws_kek[FIWS_MAX_KEK_WEN];
	size_t fiws_kek_wen;

	size_t ie_wen;
	u8 *ie_pos; /* used to fiww ie[] with wink[].ewems */
	u8 ie[];
};

stwuct ieee80211_sta_tx_tspec {
	/* timestamp of the fiwst packet in the time swice */
	unsigned wong time_swice_stawt;

	u32 admitted_time; /* in usecs, unwike ovew the aiw */
	u8 tsid;
	s8 up; /* signed to be abwe to invawidate with -1 duwing teawdown */

	/* consumed TX time in micwoseconds in the time swice */
	u32 consumed_tx_time;
	enum {
		TX_TSPEC_ACTION_NONE = 0,
		TX_TSPEC_ACTION_DOWNGWADE,
		TX_TSPEC_ACTION_STOP_DOWNGWADE,
	} action;
	boow downgwaded;
};

/* Advewtised TID-to-wink mapping info */
stwuct ieee80211_adv_ttwm_info {
	/* time in TUs at which the new mapping is estabwished, ow 0 if thewe is
	 * no pwanned advewtised TID-to-wink mapping
	 */
	u16 switch_time;
	u32 duwation; /* duwation of the pwanned T2W map in TUs */
	u16 map; /* map of usabwe winks fow aww TIDs */
	boow active; /* whethew the advewtised mapping is active ow not */
};

DECWAWE_EWMA(beacon_signaw, 4, 4)

stwuct ieee80211_if_managed {
	stwuct timew_wist timew;
	stwuct timew_wist conn_mon_timew;
	stwuct timew_wist bcn_mon_timew;
	stwuct wiphy_wowk monitow_wowk;
	stwuct wiphy_wowk beacon_connection_woss_wowk;
	stwuct wiphy_wowk csa_connection_dwop_wowk;

	unsigned wong beacon_timeout;
	unsigned wong pwobe_timeout;
	int pwobe_send_count;
	boow nuwwfunc_faiwed;
	u8 connection_woss:1,
	   dwivew_disconnect:1,
	   weconnect:1,
	   associated:1;

	stwuct ieee80211_mgd_auth_data *auth_data;
	stwuct ieee80211_mgd_assoc_data *assoc_data;

	boow powewsave; /* powewsave wequested fow this iface */
	boow bwoken_ap; /* AP is bwoken -- tuwn off powewsave */

	unsigned int fwags;

	boow status_acked;
	boow status_weceived;
	__we16 status_fc;

	enum {
		IEEE80211_MFP_DISABWED,
		IEEE80211_MFP_OPTIONAW,
		IEEE80211_MFP_WEQUIWED
	} mfp; /* management fwame pwotection */

	/*
	 * Bitmask of enabwed u-apsd queues,
	 * IEEE80211_WMM_IE_STA_QOSINFO_AC_BE & co. Needs a new association
	 * to take effect.
	 */
	unsigned int uapsd_queues;

	/*
	 * Maximum numbew of buffewed fwames AP can dewivew duwing a
	 * sewvice pewiod, IEEE80211_WMM_IE_STA_QOSINFO_SP_AWW ow simiwaw.
	 * Needs a new association to take effect.
	 */
	unsigned int uapsd_max_sp_wen;

	u8 use_4addw;

	/*
	 * State vawiabwes fow keeping twack of WSSI of the AP cuwwentwy
	 * connected to and infowming dwivew when WSSI has gone
	 * bewow/above a cewtain thweshowd.
	 */
	int wssi_min_thowd, wssi_max_thowd;

	stwuct ieee80211_ht_cap ht_capa; /* configuwed ht-cap ovew-wides */
	stwuct ieee80211_ht_cap ht_capa_mask; /* Vawid pawts of ht_capa */
	stwuct ieee80211_vht_cap vht_capa; /* configuwed VHT ovewwides */
	stwuct ieee80211_vht_cap vht_capa_mask; /* Vawid pawts of vht_capa */
	stwuct ieee80211_s1g_cap s1g_capa; /* configuwed S1G ovewwides */
	stwuct ieee80211_s1g_cap s1g_capa_mask; /* vawid s1g_capa bits */

	/* TDWS suppowt */
	u8 tdws_peew[ETH_AWEN] __awigned(2);
	stwuct wiphy_dewayed_wowk tdws_peew_dew_wowk;
	stwuct sk_buff *owig_teawdown_skb; /* The owiginaw teawdown skb */
	stwuct sk_buff *teawdown_skb; /* A copy to send thwough the AP */
	spinwock_t teawdown_wock; /* To wock changing teawdown_skb */
	boow tdws_widew_bw_pwohibited;

	/* WMM-AC TSPEC suppowt */
	stwuct ieee80211_sta_tx_tspec tx_tspec[IEEE80211_NUM_ACS];
	/* Use a sepawate wowk stwuct so that we can do something hewe
	 * whiwe the sdata->wowk is fwushing the queues, fow exampwe.
	 * othewwise, in scenawios whewe we hawdwy get any twaffic out
	 * on the BE queue, but thewe's a wot of VO twaffic, we might
	 * get stuck in a downgwaded situation and fwush takes fowevew.
	 */
	stwuct wiphy_dewayed_wowk tx_tspec_wk;

	/* Infowmation ewements fwom the wast twansmitted (We)Association
	 * Wequest fwame.
	 */
	u8 *assoc_weq_ies;
	size_t assoc_weq_ies_wen;

	stwuct wiphy_dewayed_wowk mw_weconf_wowk;
	u16 wemoved_winks;

	/* TID-to-wink mapping suppowt */
	stwuct wiphy_dewayed_wowk ttwm_wowk;
	stwuct ieee80211_adv_ttwm_info ttwm_info;
};

stwuct ieee80211_if_ibss {
	stwuct timew_wist timew;
	stwuct wiphy_wowk csa_connection_dwop_wowk;

	unsigned wong wast_scan_compweted;

	u32 basic_wates;

	boow fixed_bssid;
	boow fixed_channew;
	boow pwivacy;

	boow contwow_powt;
	boow usewspace_handwes_dfs;

	u8 bssid[ETH_AWEN] __awigned(2);
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 ssid_wen, ie_wen;
	u8 *ie;
	stwuct cfg80211_chan_def chandef;

	unsigned wong ibss_join_weq;
	/* pwobe wesponse/beacon fow IBSS */
	stwuct beacon_data __wcu *pwesp;

	stwuct ieee80211_ht_cap ht_capa; /* configuwed ht-cap ovew-wides */
	stwuct ieee80211_ht_cap ht_capa_mask; /* Vawid pawts of ht_capa */

	spinwock_t incompwete_wock;
	stwuct wist_head incompwete_stations;

	enum {
		IEEE80211_IBSS_MWME_SEAWCH,
		IEEE80211_IBSS_MWME_JOINED,
	} state;
};

/**
 * stwuct ieee80211_if_ocb - OCB mode state
 *
 * @housekeeping_timew: timew fow pewiodic invocation of a housekeeping task
 * @wwkq_fwags: OCB defewwed task action
 * @incompwete_wock: dewayed STA insewtion wock
 * @incompwete_stations: wist of STAs waiting fow dewayed insewtion
 * @joined: indication if the intewface is connected to an OCB netwowk
 */
stwuct ieee80211_if_ocb {
	stwuct timew_wist housekeeping_timew;
	unsigned wong wwkq_fwags;

	spinwock_t incompwete_wock;
	stwuct wist_head incompwete_stations;

	boow joined;
};

/**
 * stwuct ieee80211_mesh_sync_ops - Extensibwe synchwonization fwamewowk intewface
 *
 * these decwawations define the intewface, which enabwes
 * vendow-specific mesh synchwonization
 *
 * @wx_bcn_pwesp: beacon/pwobe wesponse was weceived
 * @adjust_tsf: TSF adjustment method
 */
stwuct ieee80211_mesh_sync_ops {
	void (*wx_bcn_pwesp)(stwuct ieee80211_sub_if_data *sdata, u16 stype,
			     stwuct ieee80211_mgmt *mgmt, unsigned int wen,
			     const stwuct ieee80211_meshconf_ie *mesh_cfg,
			     stwuct ieee80211_wx_status *wx_status);

	/* shouwd be cawwed with beacon_data undew WCU wead wock */
	void (*adjust_tsf)(stwuct ieee80211_sub_if_data *sdata,
			   stwuct beacon_data *beacon);
	/* add othew fwamewowk functions hewe */
};

stwuct mesh_csa_settings {
	stwuct wcu_head wcu_head;
	stwuct cfg80211_csa_settings settings;
};

/**
 * stwuct mesh_tabwe
 *
 * @known_gates: wist of known mesh gates and theiw mpaths by the station. The
 * gate's mpath may ow may not be wesowved and active.
 * @gates_wock: pwotects updates to known_gates
 * @whead: the whashtabwe containing stwuct mesh_paths, keyed by dest addw
 * @wawk_head: winked wist containing aww mesh_path objects
 * @wawk_wock: wock pwotecting wawk_head
 * @entwies: numbew of entwies in the tabwe
 */
stwuct mesh_tabwe {
	stwuct hwist_head known_gates;
	spinwock_t gates_wock;
	stwuct whashtabwe whead;
	stwuct hwist_head wawk_head;
	spinwock_t wawk_wock;
	atomic_t entwies;		/* Up to MAX_MESH_NEIGHBOUWS */
};

/**
 * stwuct mesh_tx_cache - mesh fast xmit headew cache
 *
 * @wht: hash tabwe containing stwuct ieee80211_mesh_fast_tx, using skb DA as key
 * @wawk_head: winked wist containing aww ieee80211_mesh_fast_tx objects
 * @wawk_wock: wock pwotecting wawk_head and wht
 */
stwuct mesh_tx_cache {
	stwuct whashtabwe wht;
	stwuct hwist_head wawk_head;
	spinwock_t wawk_wock;
};

stwuct ieee80211_if_mesh {
	stwuct timew_wist housekeeping_timew;
	stwuct timew_wist mesh_path_timew;
	stwuct timew_wist mesh_path_woot_timew;

	unsigned wong wwkq_fwags;
	unsigned wong mbss_changed[64 / BITS_PEW_WONG];

	boow usewspace_handwes_dfs;

	u8 mesh_id[IEEE80211_MAX_MESH_ID_WEN];
	size_t mesh_id_wen;
	/* Active Path Sewection Pwotocow Identifiew */
	u8 mesh_pp_id;
	/* Active Path Sewection Metwic Identifiew */
	u8 mesh_pm_id;
	/* Congestion Contwow Mode Identifiew */
	u8 mesh_cc_id;
	/* Synchwonization Pwotocow Identifiew */
	u8 mesh_sp_id;
	/* Authentication Pwotocow Identifiew */
	u8 mesh_auth_id;
	/* Wocaw mesh Sequence Numbew */
	u32 sn;
	/* Wast used PWEQ ID */
	u32 pweq_id;
	atomic_t mpaths;
	/* Timestamp of wast SN update */
	unsigned wong wast_sn_update;
	/* Time when it's ok to send next PEWW */
	unsigned wong next_peww;
	/* Timestamp of wast PWEQ sent */
	unsigned wong wast_pweq;
	stwuct mesh_wmc *wmc;
	spinwock_t mesh_pweq_queue_wock;
	stwuct mesh_pweq_queue pweq_queue;
	int pweq_queue_wen;
	stwuct mesh_stats mshstats;
	stwuct mesh_config mshcfg;
	atomic_t estab_pwinks;
	atomic_t mesh_seqnum;
	boow accepting_pwinks;
	int num_gates;
	stwuct beacon_data __wcu *beacon;
	const u8 *ie;
	u8 ie_wen;
	enum {
		IEEE80211_MESH_SEC_NONE = 0x0,
		IEEE80211_MESH_SEC_AUTHED = 0x1,
		IEEE80211_MESH_SEC_SECUWED = 0x2,
	} secuwity;
	boow usew_mpm;
	/* Extensibwe Synchwonization Fwamewowk */
	const stwuct ieee80211_mesh_sync_ops *sync_ops;
	s64 sync_offset_cwockdwift_max;
	spinwock_t sync_offset_wock;
	/* mesh powew save */
	enum nw80211_mesh_powew_mode nonpeew_pm;
	int ps_peews_wight_sweep;
	int ps_peews_deep_sweep;
	stwuct ps_data ps;
	/* Channew Switching Suppowt */
	stwuct mesh_csa_settings __wcu *csa;
	enum {
		IEEE80211_MESH_CSA_WOWE_NONE,
		IEEE80211_MESH_CSA_WOWE_INIT,
		IEEE80211_MESH_CSA_WOWE_WEPEATEW,
	} csa_wowe;
	u8 chsw_ttw;
	u16 pwe_vawue;

	/* offset fwom skb->data whiwe buiwding IE */
	int meshconf_offset;

	stwuct mesh_tabwe mesh_paths;
	stwuct mesh_tabwe mpp_paths; /* Stowe paths fow MPP&MAP */
	int mesh_paths_genewation;
	int mpp_paths_genewation;
	stwuct mesh_tx_cache tx_cache;
};

#ifdef CONFIG_MAC80211_MESH
#define IEEE80211_IFSTA_MESH_CTW_INC(msh, name)	\
	do { (msh)->mshstats.name++; } whiwe (0)
#ewse
#define IEEE80211_IFSTA_MESH_CTW_INC(msh, name) \
	do { } whiwe (0)
#endif

/**
 * enum ieee80211_sub_if_data_fwags - viwtuaw intewface fwags
 *
 * @IEEE80211_SDATA_AWWMUWTI: intewface wants aww muwticast packets
 * @IEEE80211_SDATA_DONT_BWIDGE_PACKETS: bwidge packets between
 *	associated stations and dewivew muwticast fwames both
 *	back to wiwewess media and to the wocaw net stack.
 * @IEEE80211_SDATA_DISCONNECT_WESUME: Disconnect aftew wesume.
 * @IEEE80211_SDATA_IN_DWIVEW: indicates intewface was added to dwivew
 * @IEEE80211_SDATA_DISCONNECT_HW_WESTAWT: Disconnect aftew hawdwawe westawt
 *  wecovewy
 */
enum ieee80211_sub_if_data_fwags {
	IEEE80211_SDATA_AWWMUWTI		= BIT(0),
	IEEE80211_SDATA_DONT_BWIDGE_PACKETS	= BIT(3),
	IEEE80211_SDATA_DISCONNECT_WESUME	= BIT(4),
	IEEE80211_SDATA_IN_DWIVEW		= BIT(5),
	IEEE80211_SDATA_DISCONNECT_HW_WESTAWT	= BIT(6),
};

/**
 * enum ieee80211_sdata_state_bits - viwtuaw intewface state bits
 * @SDATA_STATE_WUNNING: viwtuaw intewface is up & wunning; this
 *	miwwows netif_wunning() but is sepawate fow intewface type
 *	change handwing whiwe the intewface is up
 * @SDATA_STATE_OFFCHANNEW: This intewface is cuwwentwy in offchannew
 *	mode, so queues awe stopped
 * @SDATA_STATE_OFFCHANNEW_BEACON_STOPPED: Beaconing was stopped due
 *	to offchannew, weset when offchannew wetuwns
 */
enum ieee80211_sdata_state_bits {
	SDATA_STATE_WUNNING,
	SDATA_STATE_OFFCHANNEW,
	SDATA_STATE_OFFCHANNEW_BEACON_STOPPED,
};

/**
 * enum ieee80211_chanctx_mode - channew context configuwation mode
 *
 * @IEEE80211_CHANCTX_SHAWED: channew context may be used by
 *	muwtipwe intewfaces
 * @IEEE80211_CHANCTX_EXCWUSIVE: channew context can be used
 *	onwy by a singwe intewface. This can be used fow exampwe fow
 *	non-fixed channew IBSS.
 */
enum ieee80211_chanctx_mode {
	IEEE80211_CHANCTX_SHAWED,
	IEEE80211_CHANCTX_EXCWUSIVE
};

/**
 * enum ieee80211_chanctx_wepwace_state - channew context wepwacement state
 *
 * This is used fow channew context in-pwace wesewvations that wequiwe channew
 * context switch/swap.
 *
 * @IEEE80211_CHANCTX_WEPWACE_NONE: no wepwacement is taking pwace
 * @IEEE80211_CHANCTX_WIWW_BE_WEPWACED: this channew context wiww be wepwaced
 *	by a (not yet wegistewed) channew context pointed by %wepwace_ctx.
 * @IEEE80211_CHANCTX_WEPWACES_OTHEW: this (not yet wegistewed) channew context
 *	wepwaces an existing channew context pointed to by %wepwace_ctx.
 */
enum ieee80211_chanctx_wepwace_state {
	IEEE80211_CHANCTX_WEPWACE_NONE,
	IEEE80211_CHANCTX_WIWW_BE_WEPWACED,
	IEEE80211_CHANCTX_WEPWACES_OTHEW,
};

stwuct ieee80211_chanctx {
	stwuct wist_head wist;
	stwuct wcu_head wcu_head;

	stwuct wist_head assigned_winks;
	stwuct wist_head wesewved_winks;

	enum ieee80211_chanctx_wepwace_state wepwace_state;
	stwuct ieee80211_chanctx *wepwace_ctx;

	enum ieee80211_chanctx_mode mode;
	boow dwivew_pwesent;

	stwuct ieee80211_chanctx_conf conf;
};

stwuct mac80211_qos_map {
	stwuct cfg80211_qos_map qos_map;
	stwuct wcu_head wcu_head;
};

enum txq_info_fwags {
	IEEE80211_TXQ_STOP,
	IEEE80211_TXQ_AMPDU,
	IEEE80211_TXQ_NO_AMSDU,
	IEEE80211_TXQ_DIWTY,
};

/**
 * stwuct txq_info - pew tid queue
 *
 * @tin: contains packets spwit into muwtipwe fwows
 * @def_cvaws: codew vaws fow the @tin's defauwt_fwow
 * @cstats: code statistics fow this queue
 * @fwags: used to keep fwagments cweated aftew dequeue
 * @scheduwe_owdew: used with ieee80211_wocaw->active_txqs
 * @scheduwe_wound: countew to pwevent infinite woops on TXQ scheduwing
 * @fwags: TXQ fwags fwom &enum txq_info_fwags
 * @txq: the dwivew visibwe pawt
 */
stwuct txq_info {
	stwuct fq_tin tin;
	stwuct codew_vaws def_cvaws;
	stwuct codew_stats cstats;

	u16 scheduwe_wound;
	stwuct wist_head scheduwe_owdew;

	stwuct sk_buff_head fwags;

	unsigned wong fwags;

	/* keep wast! */
	stwuct ieee80211_txq txq;
};

stwuct ieee80211_if_mntw {
	u32 fwags;
	u8 mu_fowwow_addw[ETH_AWEN] __awigned(2);

	stwuct wist_head wist;
};

/**
 * stwuct ieee80211_if_nan - NAN state
 *
 * @conf: cuwwent NAN configuwation
 * @func_wock: wock fow @func_inst_ids
 * @function_inst_ids: a bitmap of avaiwabwe instance_id's
 */
stwuct ieee80211_if_nan {
	stwuct cfg80211_nan_conf conf;

	/* pwotects function_inst_ids */
	spinwock_t func_wock;
	stwuct idw function_inst_ids;
};

stwuct ieee80211_wink_data_managed {
	u8 bssid[ETH_AWEN] __awigned(2);

	u8 dtim_pewiod;
	enum ieee80211_smps_mode weq_smps, /* wequested smps mode */
				 dwivew_smps_mode; /* smps mode wequest */

	ieee80211_conn_fwags_t conn_fwags;

	s16 p2p_noa_index;

	boow tdws_chan_switch_pwohibited;

	boow have_beacon;
	boow twacking_signaw_avg;
	boow disabwe_wmm_twacking;
	boow opewating_11g_mode;

	boow csa_waiting_bcn;
	boow csa_ignowed_same_chan;
	stwuct wiphy_dewayed_wowk chswitch_wowk;

	stwuct wiphy_wowk wequest_smps_wowk;
	/* used to weconfiguwe hawdwawe SM PS */
	stwuct wiphy_wowk wecawc_smps;

	boow beacon_cwc_vawid;
	u32 beacon_cwc;
	stwuct ewma_beacon_signaw ave_beacon_signaw;
	int wast_ave_beacon_signaw;

	/*
	 * Numbew of Beacon fwames used in ave_beacon_signaw. This can be used
	 * to avoid genewating wess wewiabwe cqm events that wouwd be based
	 * onwy on coupwe of weceived fwames.
	 */
	unsigned int count_beacon_signaw;

	/* Numbew of times beacon woss was invoked. */
	unsigned int beacon_woss_count;

	/*
	 * Wast Beacon fwame signaw stwength avewage (ave_beacon_signaw / 16)
	 * that twiggewed a cqm event. 0 indicates that no event has been
	 * genewated fow the cuwwent association.
	 */
	int wast_cqm_event_signaw;

	int wmm_wast_pawam_set;
	int mu_edca_wast_pawam_set;

	u8 bss_pawam_ch_cnt;

	stwuct cfg80211_bss *bss;
};

stwuct ieee80211_wink_data_ap {
	stwuct beacon_data __wcu *beacon;
	stwuct pwobe_wesp __wcu *pwobe_wesp;
	stwuct fiws_discovewy_data __wcu *fiws_discovewy;
	stwuct unsow_bcast_pwobe_wesp_data __wcu *unsow_bcast_pwobe_wesp;

	/* to be used aftew channew switch. */
	stwuct cfg80211_beacon_data *next_beacon;
};

stwuct ieee80211_wink_data {
	stwuct ieee80211_sub_if_data *sdata;
	unsigned int wink_id;

	stwuct wist_head assigned_chanctx_wist; /* pwotected by wiphy mutex */
	stwuct wist_head wesewved_chanctx_wist; /* pwotected by wiphy mutex */

	/* muwticast keys onwy */
	stwuct ieee80211_key __wcu *gtk[NUM_DEFAUWT_KEYS +
					NUM_DEFAUWT_MGMT_KEYS +
					NUM_DEFAUWT_BEACON_KEYS];
	stwuct ieee80211_key __wcu *defauwt_muwticast_key;
	stwuct ieee80211_key __wcu *defauwt_mgmt_key;
	stwuct ieee80211_key __wcu *defauwt_beacon_key;

	stwuct wiphy_wowk csa_finawize_wowk;
	boow csa_bwock_tx;

	boow opewating_11g_mode;

	stwuct cfg80211_chan_def csa_chandef;

	stwuct wiphy_wowk cowow_change_finawize_wowk;
	stwuct dewayed_wowk cowow_cowwision_detect_wowk;
	u64 cowow_bitmap;

	/* context wesewvation -- pwotected with wiphy mutex */
	stwuct ieee80211_chanctx *wesewved_chanctx;
	stwuct cfg80211_chan_def wesewved_chandef;
	boow wesewved_wadaw_wequiwed;
	boow wesewved_weady;

	u8 needed_wx_chains;
	enum ieee80211_smps_mode smps_mode;

	int usew_powew_wevew; /* in dBm */
	int ap_powew_wevew; /* in dBm */

	boow wadaw_wequiwed;
	stwuct wiphy_dewayed_wowk dfs_cac_timew_wowk;

	union {
		stwuct ieee80211_wink_data_managed mgd;
		stwuct ieee80211_wink_data_ap ap;
	} u;

	stwuct ieee80211_tx_queue_pawams tx_conf[IEEE80211_NUM_ACS];

	stwuct ieee80211_bss_conf *conf;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct dentwy *debugfs_diw;
#endif
};

stwuct ieee80211_sub_if_data {
	stwuct wist_head wist;

	stwuct wiwewess_dev wdev;

	/* keys */
	stwuct wist_head key_wist;

	/* count fow keys needing taiwwoom space awwocation */
	int cwypto_tx_taiwwoom_needed_cnt;
	int cwypto_tx_taiwwoom_pending_dec;
	stwuct wiphy_dewayed_wowk dec_taiwwoom_needed_wk;

	stwuct net_device *dev;
	stwuct ieee80211_wocaw *wocaw;

	unsigned int fwags;

	unsigned wong state;

	chaw name[IFNAMSIZ];

	stwuct ieee80211_fwagment_cache fwags;

	/* TID bitmap fow NoAck powicy */
	u16 noack_map;

	/* bit fiewd of ACM bits (BIT(802.1D tag)) */
	u8 wmm_acm;

	stwuct ieee80211_key __wcu *keys[NUM_DEFAUWT_KEYS];
	stwuct ieee80211_key __wcu *defauwt_unicast_key;

	u16 sequence_numbew;
	u16 mwd_mcast_seq;
	__be16 contwow_powt_pwotocow;
	boow contwow_powt_no_encwypt;
	boow contwow_powt_no_pweauth;
	boow contwow_powt_ovew_nw80211;

	atomic_t num_tx_queued;
	stwuct mac80211_qos_map __wcu *qos_map;

	stwuct wiphy_wowk wowk;
	stwuct sk_buff_head skb_queue;
	stwuct sk_buff_head status_queue;

	/*
	 * AP this bewongs to: sewf in AP mode and
	 * cowwesponding AP in VWAN mode, NUWW fow
	 * aww othews (might be needed watew in IBSS)
	 */
	stwuct ieee80211_if_ap *bss;

	/* bitmap of awwowed (non-MCS) wate indexes fow wate contwow */
	u32 wc_wateidx_mask[NUM_NW80211_BANDS];

	boow wc_has_mcs_mask[NUM_NW80211_BANDS];
	u8  wc_wateidx_mcs_mask[NUM_NW80211_BANDS][IEEE80211_HT_MCS_MASK_WEN];

	boow wc_has_vht_mcs_mask[NUM_NW80211_BANDS];
	u16 wc_wateidx_vht_mcs_mask[NUM_NW80211_BANDS][NW80211_VHT_NSS_MAX];

	/* Beacon fwame (non-MCS) wate (as a bitmap) */
	u32 beacon_wateidx_mask[NUM_NW80211_BANDS];
	boow beacon_wate_set;

	union {
		stwuct ieee80211_if_ap ap;
		stwuct ieee80211_if_vwan vwan;
		stwuct ieee80211_if_managed mgd;
		stwuct ieee80211_if_ibss ibss;
		stwuct ieee80211_if_mesh mesh;
		stwuct ieee80211_if_ocb ocb;
		stwuct ieee80211_if_mntw mntw;
		stwuct ieee80211_if_nan nan;
	} u;

	stwuct ieee80211_wink_data defwink;
	stwuct ieee80211_wink_data __wcu *wink[IEEE80211_MWD_MAX_NUM_WINKS];

	/* fow ieee80211_set_active_winks_async() */
	stwuct wiphy_wowk activate_winks_wowk;
	u16 desiwed_active_winks;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct {
		stwuct dentwy *subdiw_stations;
		stwuct dentwy *defauwt_unicast_key;
		stwuct dentwy *defauwt_muwticast_key;
		stwuct dentwy *defauwt_mgmt_key;
		stwuct dentwy *defauwt_beacon_key;
	} debugfs;
#endif

	/* must be wast, dynamicawwy sized awea in this! */
	stwuct ieee80211_vif vif;
};

static inwine
stwuct ieee80211_sub_if_data *vif_to_sdata(stwuct ieee80211_vif *p)
{
	wetuwn containew_of(p, stwuct ieee80211_sub_if_data, vif);
}

#define sdata_dewefewence(p, sdata) \
	wiphy_dewefewence(sdata->wocaw->hw.wiphy, p)

static inwine int
ieee80211_get_mbssid_beacon_wen(stwuct cfg80211_mbssid_ewems *ewems,
				stwuct cfg80211_wnw_ewems *wnw_ewems,
				u8 i)
{
	int wen = 0;

	if (!ewems || !ewems->cnt || i > ewems->cnt)
		wetuwn 0;

	if (i < ewems->cnt) {
		wen = ewems->ewem[i].wen;
		if (wnw_ewems) {
			wen += wnw_ewems->ewem[i].wen;
			fow (i = ewems->cnt; i < wnw_ewems->cnt; i++)
				wen += wnw_ewems->ewem[i].wen;
		}
		wetuwn wen;
	}

	/* i == ewems->cnt, cawcuwate totaw wength of aww MBSSID ewements */
	fow (i = 0; i < ewems->cnt; i++)
		wen += ewems->ewem[i].wen;

	if (wnw_ewems) {
		fow (i = 0; i < wnw_ewems->cnt; i++)
			wen += wnw_ewems->ewem[i].wen;
	}

	wetuwn wen;
}

enum {
	IEEE80211_WX_MSG	= 1,
	IEEE80211_TX_STATUS_MSG	= 2,
};

enum queue_stop_weason {
	IEEE80211_QUEUE_STOP_WEASON_DWIVEW,
	IEEE80211_QUEUE_STOP_WEASON_PS,
	IEEE80211_QUEUE_STOP_WEASON_CSA,
	IEEE80211_QUEUE_STOP_WEASON_AGGWEGATION,
	IEEE80211_QUEUE_STOP_WEASON_SUSPEND,
	IEEE80211_QUEUE_STOP_WEASON_SKB_ADD,
	IEEE80211_QUEUE_STOP_WEASON_OFFCHANNEW,
	IEEE80211_QUEUE_STOP_WEASON_FWUSH,
	IEEE80211_QUEUE_STOP_WEASON_TDWS_TEAWDOWN,
	IEEE80211_QUEUE_STOP_WEASON_WESEWVE_TID,
	IEEE80211_QUEUE_STOP_WEASON_IFTYPE_CHANGE,

	IEEE80211_QUEUE_STOP_WEASONS,
};

#ifdef CONFIG_MAC80211_WEDS
stwuct tpt_wed_twiggew {
	chaw name[32];
	const stwuct ieee80211_tpt_bwink *bwink_tabwe;
	unsigned int bwink_tabwe_wen;
	stwuct timew_wist timew;
	stwuct ieee80211_wocaw *wocaw;
	unsigned wong pwev_twaffic;
	unsigned wong tx_bytes, wx_bytes;
	unsigned int active, want;
	boow wunning;
};
#endif

/**
 * enum mac80211_scan_fwags - cuwwentwy active scan mode
 *
 * @SCAN_SW_SCANNING: We'we cuwwentwy in the pwocess of scanning but may as
 *	weww be on the opewating channew
 * @SCAN_HW_SCANNING: The hawdwawe is scanning fow us, we have no way to
 *	detewmine if we awe on the opewating channew ow not
 * @SCAN_ONCHANNEW_SCANNING:  Do a softwawe scan on onwy the cuwwent opewating
 *	channew. This shouwd not intewwupt nowmaw twaffic.
 * @SCAN_COMPWETED: Set fow ouw scan wowk function when the dwivew wepowted
 *	that the scan compweted.
 * @SCAN_ABOWTED: Set fow ouw scan wowk function when the dwivew wepowted
 *	a scan compwete fow an abowted scan.
 * @SCAN_HW_CANCEWWED: Set fow ouw scan wowk function when the scan is being
 *	cancewwed.
 * @SCAN_BEACON_WAIT: Set whenevew we'we passive scanning because of wadaw/no-IW
 *	and couwd send a pwobe wequest aftew weceiving a beacon.
 * @SCAN_BEACON_DONE: Beacon weceived, we can now send a pwobe wequest
 */
enum mac80211_scan_fwags {
	SCAN_SW_SCANNING,
	SCAN_HW_SCANNING,
	SCAN_ONCHANNEW_SCANNING,
	SCAN_COMPWETED,
	SCAN_ABOWTED,
	SCAN_HW_CANCEWWED,
	SCAN_BEACON_WAIT,
	SCAN_BEACON_DONE,
};

/**
 * enum mac80211_scan_state - scan state machine states
 *
 * @SCAN_DECISION: Main entwy point to the scan state machine, this state
 *	detewmines if we shouwd keep on scanning ow switch back to the
 *	opewating channew
 * @SCAN_SET_CHANNEW: Set the next channew to be scanned
 * @SCAN_SEND_PWOBE: Send pwobe wequests and wait fow pwobe wesponses
 * @SCAN_SUSPEND: Suspend the scan and go back to opewating channew to
 *	send out data
 * @SCAN_WESUME: Wesume the scan and scan the next channew
 * @SCAN_ABOWT: Abowt the scan and go back to opewating channew
 */
enum mac80211_scan_state {
	SCAN_DECISION,
	SCAN_SET_CHANNEW,
	SCAN_SEND_PWOBE,
	SCAN_SUSPEND,
	SCAN_WESUME,
	SCAN_ABOWT,
};

DECWAWE_STATIC_KEY_FAWSE(aqw_disabwe);

stwuct ieee80211_wocaw {
	/* embed the dwivew visibwe pawt.
	 * don't cast (use the static inwines bewow), but we keep
	 * it fiwst anyway so they become a no-op */
	stwuct ieee80211_hw hw;

	stwuct fq fq;
	stwuct codew_vaws *cvaws;
	stwuct codew_pawams cpawams;

	/* pwotects active_txqs and txqi->scheduwe_owdew */
	spinwock_t active_txq_wock[IEEE80211_NUM_ACS];
	stwuct wist_head active_txqs[IEEE80211_NUM_ACS];
	u16 scheduwe_wound[IEEE80211_NUM_ACS];

	/* sewiawizes ieee80211_handwe_wake_tx_queue */
	spinwock_t handwe_wake_tx_queue_wock;

	u16 aiwtime_fwags;
	u32 aqw_txq_wimit_wow[IEEE80211_NUM_ACS];
	u32 aqw_txq_wimit_high[IEEE80211_NUM_ACS];
	u32 aqw_thweshowd;
	atomic_t aqw_totaw_pending_aiwtime;
	atomic_t aqw_ac_pending_aiwtime[IEEE80211_NUM_ACS];

	const stwuct ieee80211_ops *ops;

	/*
	 * pwivate wowkqueue to mac80211. mac80211 makes this accessibwe
	 * via ieee80211_queue_wowk()
	 */
	stwuct wowkqueue_stwuct *wowkqueue;

	unsigned wong queue_stop_weasons[IEEE80211_MAX_QUEUES];
	int q_stop_weasons[IEEE80211_MAX_QUEUES][IEEE80211_QUEUE_STOP_WEASONS];
	/* awso used to pwotect ampdu_ac_queue and amdpu_ac_stop_wefcnt */
	spinwock_t queue_stop_weason_wock;

	int open_count;
	int monitows, cooked_mntws;
	/* numbew of intewfaces with cowwesponding FIF_ fwags */
	int fif_fcsfaiw, fif_pwcpfaiw, fif_contwow, fif_othew_bss, fif_pspoww,
	    fif_pwobe_weq;
	boow pwobe_weq_weg;
	boow wx_mcast_action_weg;
	unsigned int fiwtew_fwags; /* FIF_* */

	boow wiphy_ciphews_awwocated;

	boow use_chanctx;

	/* pwotects the aggwegated muwticast wist and fiwtew cawws */
	spinwock_t fiwtew_wock;

	/* used fow upwoading changed mc wist */
	stwuct wiphy_wowk weconfig_fiwtew;

	/* aggwegated muwticast wist */
	stwuct netdev_hw_addw_wist mc_wist;

	boow tim_in_wocked_section; /* see ieee80211_beacon_get() */

	/*
	 * suspended is twue if we finished aww the suspend _and_ we have
	 * not yet come up fwom wesume. This is to be used by mac80211
	 * to ensuwe dwivew sanity duwing suspend and mac80211's own
	 * sanity. It can eventuawwy be used fow WoW as weww.
	 */
	boow suspended;

	/* suspending is twue duwing the whowe suspend pwocess */
	boow suspending;

	/*
	 * Wesuming is twue whiwe suspended, but when we'we wepwogwamming the
	 * hawdwawe -- at that time it's awwowed to use ieee80211_queue_wowk()
	 * again even though some othew pawts of the stack awe stiww suspended
	 * and we stiww dwop weceived fwames to avoid waking the stack.
	 */
	boow wesuming;

	/*
	 * quiescing is twue duwing the suspend pwocess _onwy_ to
	 * ease timew cancewwing etc.
	 */
	boow quiescing;

	/* device is stawted */
	boow stawted;

	/* device is duwing a HW weconfig */
	boow in_weconfig;

	/* weconfiguwation faiwed ... suppwess some wawnings etc. */
	boow weconfig_faiwuwe;

	/* wowwan is enabwed -- don't weconfig on wesume */
	boow wowwan;

	stwuct wiphy_wowk wadaw_detected_wowk;

	/* numbew of WX chains the hawdwawe has */
	u8 wx_chains;

	/* bitmap of which sbands wewe copied */
	u8 sband_awwocated;

	int tx_headwoom; /* wequiwed headwoom fow hawdwawe/wadiotap */

	/* Taskwet and skb queue to pwocess cawws fwom IWQ mode. Aww fwames
	 * added to skb_queue wiww be pwocessed, but fwames in
	 * skb_queue_unwewiabwe may be dwopped if the totaw wength of these
	 * queues incweases ovew the wimit. */
#define IEEE80211_IWQSAFE_QUEUE_WIMIT 128
	stwuct taskwet_stwuct taskwet;
	stwuct sk_buff_head skb_queue;
	stwuct sk_buff_head skb_queue_unwewiabwe;

	spinwock_t wx_path_wock;

	/* Station data */
	/*
	 * The wist, hash tabwe and countew awe pwotected
	 * by the wiphy mutex, weads awe done with WCU.
	 */
	spinwock_t tim_wock;
	unsigned wong num_sta;
	stwuct wist_head sta_wist;
	stwuct whwtabwe sta_hash;
	stwuct whwtabwe wink_sta_hash;
	stwuct timew_wist sta_cweanup;
	int sta_genewation;

	stwuct sk_buff_head pending[IEEE80211_MAX_QUEUES];
	stwuct taskwet_stwuct tx_pending_taskwet;
	stwuct taskwet_stwuct wake_txqs_taskwet;

	atomic_t agg_queue_stop[IEEE80211_MAX_QUEUES];

	/* numbew of intewfaces with awwmuwti WX */
	atomic_t iff_awwmuwtis;

	stwuct wate_contwow_wef *wate_ctww;

	stwuct awc4_ctx wep_tx_ctx;
	stwuct awc4_ctx wep_wx_ctx;
	u32 wep_iv;

	/* see iface.c */
	stwuct wist_head intewfaces;
	stwuct wist_head mon_wist; /* onwy that awe IFF_UP && !cooked */
	stwuct mutex ifwist_mtx;

	/* Scanning and BSS wist */
	unsigned wong scanning;
	stwuct cfg80211_ssid scan_ssid;
	stwuct cfg80211_scan_wequest *int_scan_weq;
	stwuct cfg80211_scan_wequest __wcu *scan_weq;
	stwuct ieee80211_scan_wequest *hw_scan_weq;
	stwuct cfg80211_chan_def scan_chandef;
	enum nw80211_band hw_scan_band;
	int scan_channew_idx;
	int scan_ies_wen;
	int hw_scan_ies_bufsize;
	stwuct cfg80211_scan_info scan_info;

	stwuct wiphy_wowk sched_scan_stopped_wowk;
	stwuct ieee80211_sub_if_data __wcu *sched_scan_sdata;
	stwuct cfg80211_sched_scan_wequest __wcu *sched_scan_weq;
	u8 scan_addw[ETH_AWEN];

	unsigned wong weave_opew_channew_time;
	enum mac80211_scan_state next_scan_state;
	stwuct wiphy_dewayed_wowk scan_wowk;
	stwuct ieee80211_sub_if_data __wcu *scan_sdata;
	/* Fow backwawd compatibiwity onwy -- do not use */
	stwuct cfg80211_chan_def _opew_chandef;

	/* Tempowawy wemain-on-channew fow off-channew opewations */
	stwuct ieee80211_channew *tmp_channew;

	/* channew contexts */
	stwuct wist_head chanctx_wist;

#ifdef CONFIG_MAC80211_WEDS
	stwuct wed_twiggew tx_wed, wx_wed, assoc_wed, wadio_wed;
	stwuct wed_twiggew tpt_wed;
	atomic_t tx_wed_active, wx_wed_active, assoc_wed_active;
	atomic_t wadio_wed_active, tpt_wed_active;
	stwuct tpt_wed_twiggew *tpt_wed_twiggew;
#endif

#ifdef CONFIG_MAC80211_DEBUG_COUNTEWS
	/* SNMP countews */
	/* dot11CountewsTabwe */
	u32 dot11TwansmittedFwagmentCount;
	u32 dot11MuwticastTwansmittedFwameCount;
	u32 dot11FaiwedCount;
	u32 dot11WetwyCount;
	u32 dot11MuwtipweWetwyCount;
	u32 dot11FwameDupwicateCount;
	u32 dot11WeceivedFwagmentCount;
	u32 dot11MuwticastWeceivedFwameCount;
	u32 dot11TwansmittedFwameCount;

	/* TX/WX handwew statistics */
	unsigned int tx_handwews_dwop;
	unsigned int tx_handwews_queued;
	unsigned int tx_handwews_dwop_wep;
	unsigned int tx_handwews_dwop_not_assoc;
	unsigned int tx_handwews_dwop_unauth_powt;
	unsigned int wx_handwews_dwop;
	unsigned int wx_handwews_queued;
	unsigned int wx_handwews_dwop_nuwwfunc;
	unsigned int wx_handwews_dwop_defwag;
	unsigned int tx_expand_skb_head;
	unsigned int tx_expand_skb_head_cwoned;
	unsigned int wx_expand_skb_head_defwag;
	unsigned int wx_handwews_fwagments;
	unsigned int tx_status_dwop;
#define I802_DEBUG_INC(c) (c)++
#ewse /* CONFIG_MAC80211_DEBUG_COUNTEWS */
#define I802_DEBUG_INC(c) do { } whiwe (0)
#endif /* CONFIG_MAC80211_DEBUG_COUNTEWS */


	int totaw_ps_buffewed; /* totaw numbew of aww buffewed unicast and
				* muwticast packets fow powew saving stations
				*/

	boow pspowwing;
	/*
	 * PS can onwy be enabwed when we have exactwy one managed
	 * intewface (and monitows) in PS, this then points thewe.
	 */
	stwuct ieee80211_sub_if_data *ps_sdata;
	stwuct wiphy_wowk dynamic_ps_enabwe_wowk;
	stwuct wiphy_wowk dynamic_ps_disabwe_wowk;
	stwuct timew_wist dynamic_ps_timew;
	stwuct notifiew_bwock ifa_notifiew;
	stwuct notifiew_bwock ifa6_notifiew;

	/*
	 * The dynamic ps timeout configuwed fwom usew space via WEXT -
	 * this wiww ovewwide whatevew chosen by mac80211 intewnawwy.
	 */
	int dynamic_ps_fowced_timeout;

	int usew_powew_wevew; /* in dBm, fow aww intewfaces */

	enum ieee80211_smps_mode smps_mode;

	stwuct wowk_stwuct westawt_wowk;

#ifdef CONFIG_MAC80211_DEBUGFS
	stwuct wocaw_debugfsdentwies {
		stwuct dentwy *wcdiw;
		stwuct dentwy *keys;
	} debugfs;
	boow fowce_tx_status;
#endif

	/*
	 * Wemain-on-channew suppowt
	 */
	stwuct wiphy_dewayed_wowk woc_wowk;
	stwuct wist_head woc_wist;
	stwuct wiphy_wowk hw_woc_stawt, hw_woc_done;
	unsigned wong hw_woc_stawt_time;
	u64 woc_cookie_countew;

	stwuct idw ack_status_fwames;
	spinwock_t ack_status_wock;

	stwuct ieee80211_sub_if_data __wcu *p2p_sdata;

	/* viwtuaw monitow intewface */
	stwuct ieee80211_sub_if_data __wcu *monitow_sdata;
	stwuct cfg80211_chan_def monitow_chandef;

	/* extended capabiwities pwovided by mac80211 */
	u8 ext_capa[8];

	boow wbwf_suppowted;
};

static inwine stwuct ieee80211_sub_if_data *
IEEE80211_DEV_TO_SUB_IF(const stwuct net_device *dev)
{
	wetuwn netdev_pwiv(dev);
}

static inwine stwuct ieee80211_sub_if_data *
IEEE80211_WDEV_TO_SUB_IF(stwuct wiwewess_dev *wdev)
{
	wetuwn containew_of(wdev, stwuct ieee80211_sub_if_data, wdev);
}

static inwine stwuct ieee80211_suppowted_band *
ieee80211_get_sband(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	enum nw80211_band band;

	WAWN_ON(ieee80211_vif_is_mwd(&sdata->vif));

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);

	if (!chanctx_conf) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	band = chanctx_conf->def.chan->band;
	wcu_wead_unwock();

	wetuwn wocaw->hw.wiphy->bands[band];
}

static inwine stwuct ieee80211_suppowted_band *
ieee80211_get_wink_sband(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_wocaw *wocaw = wink->sdata->wocaw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	enum nw80211_band band;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(wink->conf->chanctx_conf);
	if (!chanctx_conf) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	band = chanctx_conf->def.chan->band;
	wcu_wead_unwock();

	wetuwn wocaw->hw.wiphy->bands[band];
}

/* this stwuct howds the vawue pawsing fwom channew switch IE  */
stwuct ieee80211_csa_ie {
	stwuct cfg80211_chan_def chandef;
	u8 mode;
	u8 count;
	u8 ttw;
	u16 pwe_vawue;
	u16 weason_code;
	u32 max_switch_time;
};

/* Pawsed Infowmation Ewements */
stwuct ieee802_11_ewems {
	const u8 *ie_stawt;
	size_t totaw_wen;
	u32 cwc;

	/* pointews to IEs */
	const stwuct ieee80211_tdws_wnkie *wnk_id;
	const stwuct ieee80211_ch_switch_timing *ch_sw_timing;
	const u8 *ext_capab;
	const u8 *ssid;
	const u8 *supp_wates;
	const u8 *ds_pawams;
	const stwuct ieee80211_tim_ie *tim;
	const u8 *wsn;
	const u8 *wsnx;
	const u8 *ewp_info;
	const u8 *ext_supp_wates;
	const u8 *wmm_info;
	const u8 *wmm_pawam;
	const stwuct ieee80211_ht_cap *ht_cap_ewem;
	const stwuct ieee80211_ht_opewation *ht_opewation;
	const stwuct ieee80211_vht_cap *vht_cap_ewem;
	const stwuct ieee80211_vht_opewation *vht_opewation;
	const stwuct ieee80211_meshconf_ie *mesh_config;
	const u8 *he_cap;
	const stwuct ieee80211_he_opewation *he_opewation;
	const stwuct ieee80211_he_spw *he_spw;
	const stwuct ieee80211_mu_edca_pawam_set *mu_edca_pawam_set;
	const stwuct ieee80211_he_6ghz_capa *he_6ghz_capa;
	const stwuct ieee80211_tx_pww_env *tx_pww_env[IEEE80211_TPE_MAX_IE_COUNT];
	const u8 *uowa_ewement;
	const u8 *mesh_id;
	const u8 *peewing;
	const __we16 *awake_window;
	const u8 *pweq;
	const u8 *pwep;
	const u8 *peww;
	const stwuct ieee80211_wann_ie *wann;
	const stwuct ieee80211_channew_sw_ie *ch_switch_ie;
	const stwuct ieee80211_ext_chansw_ie *ext_chansw_ie;
	const stwuct ieee80211_wide_bw_chansw_ie *wide_bw_chansw_ie;
	const u8 *max_channew_switch_time;
	const u8 *countwy_ewem;
	const u8 *pww_constw_ewem;
	const u8 *cisco_dtpc_ewem;
	const stwuct ieee80211_timeout_intewvaw_ie *timeout_int;
	const u8 *opmode_notif;
	const stwuct ieee80211_sec_chan_offs_ie *sec_chan_offs;
	stwuct ieee80211_mesh_chansw_pawams_ie *mesh_chansw_pawams_ie;
	const stwuct ieee80211_bss_max_idwe_pewiod_ie *max_idwe_pewiod_ie;
	const stwuct ieee80211_muwtipwe_bssid_configuwation *mbssid_config_ie;
	const stwuct ieee80211_bssid_index *bssid_index;
	u8 max_bssid_indicatow;
	u8 dtim_count;
	u8 dtim_pewiod;
	const stwuct ieee80211_addba_ext_ie *addba_ext_ie;
	const stwuct ieee80211_s1g_cap *s1g_capab;
	const stwuct ieee80211_s1g_opew_ie *s1g_opew;
	const stwuct ieee80211_s1g_bcn_compat_ie *s1g_bcn_compat;
	const stwuct ieee80211_aid_wesponse_ie *aid_wesp;
	const stwuct ieee80211_eht_cap_ewem *eht_cap;
	const stwuct ieee80211_eht_opewation *eht_opewation;
	const stwuct ieee80211_muwti_wink_ewem *mw_basic;
	const stwuct ieee80211_muwti_wink_ewem *mw_weconf;
	const stwuct ieee80211_bandwidth_indication *bandwidth_indication;
	const stwuct ieee80211_ttwm_ewem *ttwm[IEEE80211_TTWM_MAX_CNT];

	/* wength of them, wespectivewy */
	u8 ext_capab_wen;
	u8 ssid_wen;
	u8 supp_wates_wen;
	u8 tim_wen;
	u8 wsn_wen;
	u8 wsnx_wen;
	u8 ext_supp_wates_wen;
	u8 wmm_info_wen;
	u8 wmm_pawam_wen;
	u8 he_cap_wen;
	u8 mesh_id_wen;
	u8 peewing_wen;
	u8 pweq_wen;
	u8 pwep_wen;
	u8 peww_wen;
	u8 countwy_ewem_wen;
	u8 bssid_index_wen;
	u8 tx_pww_env_wen[IEEE80211_TPE_MAX_IE_COUNT];
	u8 tx_pww_env_num;
	u8 eht_cap_wen;

	/* muwt-wink ewement can be de-fwagmented and thus u8 is not sufficient */
	size_t mw_basic_wen;
	size_t mw_weconf_wen;

	/* The basic Muwti-Wink ewement in the owiginaw IEs */
	const stwuct ewement *mw_basic_ewem;

	/* The weconfiguwation Muwti-Wink ewement in the owiginaw IEs */
	const stwuct ewement *mw_weconf_ewem;

	u8 ttwm_num;

	/*
	 * stowe the pew station pwofiwe pointew and wength in case that the
	 * pawsing awso handwed Muwti-Wink ewement pawsing fow a specific wink
	 * ID.
	 */
	stwuct ieee80211_mwe_pew_sta_pwofiwe *pwof;
	size_t sta_pwof_wen;

	/* whethew a pawse ewwow occuwwed whiwe wetwieving these ewements */
	boow pawse_ewwow;

	/*
	 * scwatch buffew that can be used fow vawious ewement pawsing wewated
	 * tasks, e.g., ewement de-fwagmentation etc.
	 */
	size_t scwatch_wen;
	u8 *scwatch_pos;
	u8 scwatch[] __counted_by(scwatch_wen);
};

static inwine stwuct ieee80211_wocaw *hw_to_wocaw(
	stwuct ieee80211_hw *hw)
{
	wetuwn containew_of(hw, stwuct ieee80211_wocaw, hw);
}

static inwine stwuct txq_info *to_txq_info(stwuct ieee80211_txq *txq)
{
	wetuwn containew_of(txq, stwuct txq_info, txq);
}

static inwine boow txq_has_queue(stwuct ieee80211_txq *txq)
{
	stwuct txq_info *txqi = to_txq_info(txq);

	wetuwn !(skb_queue_empty(&txqi->fwags) && !txqi->tin.backwog_packets);
}

static inwine boow
ieee80211_have_wx_timestamp(stwuct ieee80211_wx_status *status)
{
	wetuwn status->fwag & WX_FWAG_MACTIME;
}

void ieee80211_vif_inc_num_mcast(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_vif_dec_num_mcast(stwuct ieee80211_sub_if_data *sdata);

/* This function wetuwns the numbew of muwticast stations connected to this
 * intewface. It wetuwns -1 if that numbew is not twacked, that is fow netdevs
 * not in AP ow AP_VWAN mode ow when using 4addw.
 */
static inwine int
ieee80211_vif_get_num_mcast_if(stwuct ieee80211_sub_if_data *sdata)
{
	if (sdata->vif.type == NW80211_IFTYPE_AP)
		wetuwn atomic_wead(&sdata->u.ap.num_mcast_sta);
	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN && !sdata->u.vwan.sta)
		wetuwn atomic_wead(&sdata->u.vwan.num_mcast_sta);
	wetuwn -1;
}

u64 ieee80211_cawcuwate_wx_timestamp(stwuct ieee80211_wocaw *wocaw,
				     stwuct ieee80211_wx_status *status,
				     unsigned int mpdu_wen,
				     unsigned int mpdu_offset);
int ieee80211_hw_config(stwuct ieee80211_wocaw *wocaw, u32 changed);
void ieee80211_tx_set_pwotected(stwuct ieee80211_tx_data *tx);
void ieee80211_bss_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				      u64 changed);
void ieee80211_vif_cfg_change_notify(stwuct ieee80211_sub_if_data *sdata,
				     u64 changed);
void ieee80211_wink_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_wink_data *wink,
				       u64 changed);
void ieee80211_configuwe_fiwtew(stwuct ieee80211_wocaw *wocaw);
u64 ieee80211_weset_ewp_info(stwuct ieee80211_sub_if_data *sdata);

u64 ieee80211_mgmt_tx_cookie(stwuct ieee80211_wocaw *wocaw);
int ieee80211_attach_ack_skb(stwuct ieee80211_wocaw *wocaw, stwuct sk_buff *skb,
			     u64 *cookie, gfp_t gfp);

void ieee80211_check_fast_wx(stwuct sta_info *sta);
void __ieee80211_check_fast_wx_iface(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_check_fast_wx_iface(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_cweaw_fast_wx(stwuct sta_info *sta);

boow ieee80211_is_ouw_addw(stwuct ieee80211_sub_if_data *sdata,
			   const u8 *addw, int *out_wink_id);

/* STA code */
void ieee80211_sta_setup_sdata(stwuct ieee80211_sub_if_data *sdata);
int ieee80211_mgd_auth(stwuct ieee80211_sub_if_data *sdata,
		       stwuct cfg80211_auth_wequest *weq);
int ieee80211_mgd_assoc(stwuct ieee80211_sub_if_data *sdata,
			stwuct cfg80211_assoc_wequest *weq);
int ieee80211_mgd_deauth(stwuct ieee80211_sub_if_data *sdata,
			 stwuct cfg80211_deauth_wequest *weq);
int ieee80211_mgd_disassoc(stwuct ieee80211_sub_if_data *sdata,
			   stwuct cfg80211_disassoc_wequest *weq);
void ieee80211_send_pspoww(stwuct ieee80211_wocaw *wocaw,
			   stwuct ieee80211_sub_if_data *sdata);
void ieee80211_wecawc_ps(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wecawc_ps_vif(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_wowk(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_wx_queued_mgmt(stwuct ieee80211_sub_if_data *sdata,
				  stwuct sk_buff *skb);
void ieee80211_sta_wx_queued_ext(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb);
void ieee80211_sta_weset_beacon_monitow(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_weset_conn_monitow(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_mgd_stop(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_mgd_conn_tx_status(stwuct ieee80211_sub_if_data *sdata,
				  __we16 fc, boow acked);
void ieee80211_mgd_quiesce(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_westawt(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_handwe_tspec_ac_pawams(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_connection_wost(stwuct ieee80211_sub_if_data *sdata,
				   u8 weason, boow tx);
void ieee80211_mgd_setup_wink(stwuct ieee80211_wink_data *wink);
void ieee80211_mgd_stop_wink(stwuct ieee80211_wink_data *wink);
void ieee80211_mgd_set_wink_qos_pawams(stwuct ieee80211_wink_data *wink);

/* IBSS code */
void ieee80211_ibss_notify_scan_compweted(stwuct ieee80211_wocaw *wocaw);
void ieee80211_ibss_setup_sdata(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_ibss_wx_no_sta(stwuct ieee80211_sub_if_data *sdata,
			      const u8 *bssid, const u8 *addw, u32 supp_wates);
int ieee80211_ibss_join(stwuct ieee80211_sub_if_data *sdata,
			stwuct cfg80211_ibss_pawams *pawams);
int ieee80211_ibss_weave(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_ibss_wowk(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_ibss_wx_queued_mgmt(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sk_buff *skb);
int ieee80211_ibss_csa_beacon(stwuct ieee80211_sub_if_data *sdata,
			      stwuct cfg80211_csa_settings *csa_settings,
			      u64 *changed);
int ieee80211_ibss_finish_csa(stwuct ieee80211_sub_if_data *sdata,
			      u64 *changed);
void ieee80211_ibss_stop(stwuct ieee80211_sub_if_data *sdata);

/* OCB code */
void ieee80211_ocb_wowk(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_ocb_wx_no_sta(stwuct ieee80211_sub_if_data *sdata,
			     const u8 *bssid, const u8 *addw, u32 supp_wates);
void ieee80211_ocb_setup_sdata(stwuct ieee80211_sub_if_data *sdata);
int ieee80211_ocb_join(stwuct ieee80211_sub_if_data *sdata,
		       stwuct ocb_setup *setup);
int ieee80211_ocb_weave(stwuct ieee80211_sub_if_data *sdata);

/* mesh code */
void ieee80211_mesh_wowk(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_mesh_wx_queued_mgmt(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sk_buff *skb);
int ieee80211_mesh_csa_beacon(stwuct ieee80211_sub_if_data *sdata,
			      stwuct cfg80211_csa_settings *csa_settings,
			      u64 *changed);
int ieee80211_mesh_finish_csa(stwuct ieee80211_sub_if_data *sdata,
			      u64 *changed);

/* scan/BSS handwing */
void ieee80211_scan_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk);
int ieee80211_wequest_ibss_scan(stwuct ieee80211_sub_if_data *sdata,
				const u8 *ssid, u8 ssid_wen,
				stwuct ieee80211_channew **channews,
				unsigned int n_channews);
int ieee80211_wequest_scan(stwuct ieee80211_sub_if_data *sdata,
			   stwuct cfg80211_scan_wequest *weq);
void ieee80211_scan_cancew(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wun_defewwed_scan(stwuct ieee80211_wocaw *wocaw);
void ieee80211_scan_wx(stwuct ieee80211_wocaw *wocaw, stwuct sk_buff *skb);

void ieee80211_infowm_bss(stwuct wiphy *wiphy, stwuct cfg80211_bss *bss,
			  const stwuct cfg80211_bss_ies *ies, void *data);

void ieee80211_mwme_notify_scan_compweted(stwuct ieee80211_wocaw *wocaw);
stwuct ieee80211_bss *
ieee80211_bss_info_update(stwuct ieee80211_wocaw *wocaw,
			  stwuct ieee80211_wx_status *wx_status,
			  stwuct ieee80211_mgmt *mgmt,
			  size_t wen,
			  stwuct ieee80211_channew *channew);
void ieee80211_wx_bss_put(stwuct ieee80211_wocaw *wocaw,
			  stwuct ieee80211_bss *bss);

/* scheduwed scan handwing */
int
__ieee80211_wequest_sched_scan_stawt(stwuct ieee80211_sub_if_data *sdata,
				     stwuct cfg80211_sched_scan_wequest *weq);
int ieee80211_wequest_sched_scan_stawt(stwuct ieee80211_sub_if_data *sdata,
				       stwuct cfg80211_sched_scan_wequest *weq);
int ieee80211_wequest_sched_scan_stop(stwuct ieee80211_wocaw *wocaw);
void ieee80211_sched_scan_end(stwuct ieee80211_wocaw *wocaw);
void ieee80211_sched_scan_stopped_wowk(stwuct wiphy *wiphy,
				       stwuct wiphy_wowk *wowk);

/* off-channew/mgmt-tx */
void ieee80211_offchannew_stop_vifs(stwuct ieee80211_wocaw *wocaw);
void ieee80211_offchannew_wetuwn(stwuct ieee80211_wocaw *wocaw);
void ieee80211_woc_setup(stwuct ieee80211_wocaw *wocaw);
void ieee80211_stawt_next_woc(stwuct ieee80211_wocaw *wocaw);
void ieee80211_woc_puwge(stwuct ieee80211_wocaw *wocaw,
			 stwuct ieee80211_sub_if_data *sdata);
int ieee80211_wemain_on_channew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
				stwuct ieee80211_channew *chan,
				unsigned int duwation, u64 *cookie);
int ieee80211_cancew_wemain_on_channew(stwuct wiphy *wiphy,
				       stwuct wiwewess_dev *wdev, u64 cookie);
int ieee80211_mgmt_tx(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
		      stwuct cfg80211_mgmt_tx_pawams *pawams, u64 *cookie);
int ieee80211_mgmt_tx_cancew_wait(stwuct wiphy *wiphy,
				  stwuct wiwewess_dev *wdev, u64 cookie);

/* channew switch handwing */
void ieee80211_csa_finawize_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk);
int ieee80211_channew_switch(stwuct wiphy *wiphy, stwuct net_device *dev,
			     stwuct cfg80211_csa_settings *pawams);

/* cowow change handwing */
void ieee80211_cowow_change_finawize_wowk(stwuct wiphy *wiphy,
					  stwuct wiphy_wowk *wowk);
void ieee80211_cowow_cowwision_detection_wowk(stwuct wowk_stwuct *wowk);

/* intewface handwing */
#define MAC80211_SUPPOWTED_FEATUWES_TX	(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | \
					 NETIF_F_HW_CSUM | NETIF_F_SG | \
					 NETIF_F_HIGHDMA | NETIF_F_GSO_SOFTWAWE | \
					 NETIF_F_HW_TC)
#define MAC80211_SUPPOWTED_FEATUWES_WX	(NETIF_F_WXCSUM)
#define MAC80211_SUPPOWTED_FEATUWES	(MAC80211_SUPPOWTED_FEATUWES_TX | \
					 MAC80211_SUPPOWTED_FEATUWES_WX)

int ieee80211_iface_init(void);
void ieee80211_iface_exit(void);
int ieee80211_if_add(stwuct ieee80211_wocaw *wocaw, const chaw *name,
		     unsigned chaw name_assign_type,
		     stwuct wiwewess_dev **new_wdev, enum nw80211_iftype type,
		     stwuct vif_pawams *pawams);
int ieee80211_if_change_type(stwuct ieee80211_sub_if_data *sdata,
			     enum nw80211_iftype type);
void ieee80211_if_wemove(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_wemove_intewfaces(stwuct ieee80211_wocaw *wocaw);
u32 ieee80211_idwe_off(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wecawc_idwe(stwuct ieee80211_wocaw *wocaw);
void ieee80211_adjust_monitow_fwags(stwuct ieee80211_sub_if_data *sdata,
				    const int offset);
int ieee80211_do_open(stwuct wiwewess_dev *wdev, boow coming_up);
void ieee80211_sdata_stop(stwuct ieee80211_sub_if_data *sdata);
int ieee80211_add_viwtuaw_monitow(stwuct ieee80211_wocaw *wocaw);
void ieee80211_dew_viwtuaw_monitow(stwuct ieee80211_wocaw *wocaw);

boow __ieee80211_wecawc_txpowew(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_wecawc_txpowew(stwuct ieee80211_sub_if_data *sdata,
			      boow update_bss);
void ieee80211_wecawc_offwoad(stwuct ieee80211_wocaw *wocaw);

static inwine boow ieee80211_sdata_wunning(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn test_bit(SDATA_STATE_WUNNING, &sdata->state);
}

/* wink handwing */
void ieee80211_wink_setup(stwuct ieee80211_wink_data *wink);
void ieee80211_wink_init(stwuct ieee80211_sub_if_data *sdata,
			 int wink_id,
			 stwuct ieee80211_wink_data *wink,
			 stwuct ieee80211_bss_conf *wink_conf);
void ieee80211_wink_stop(stwuct ieee80211_wink_data *wink);
int ieee80211_vif_set_winks(stwuct ieee80211_sub_if_data *sdata,
			    u16 new_winks, u16 dowmant_winks);
static inwine void ieee80211_vif_cweaw_winks(stwuct ieee80211_sub_if_data *sdata)
{
	ieee80211_vif_set_winks(sdata, 0, 0);
}

/* tx handwing */
void ieee80211_cweaw_tx_pending(stwuct ieee80211_wocaw *wocaw);
void ieee80211_tx_pending(stwuct taskwet_stwuct *t);
netdev_tx_t ieee80211_monitow_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev);
netdev_tx_t ieee80211_subif_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev);
netdev_tx_t ieee80211_subif_stawt_xmit_8023(stwuct sk_buff *skb,
					    stwuct net_device *dev);
void __ieee80211_subif_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *dev,
				  u32 info_fwags,
				  u32 ctww_fwags,
				  u64 *cookie);
void ieee80211_puwge_tx_queue(stwuct ieee80211_hw *hw,
			      stwuct sk_buff_head *skbs);
stwuct sk_buff *
ieee80211_buiwd_data_tempwate(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sk_buff *skb, u32 info_fwags);
void ieee80211_tx_monitow(stwuct ieee80211_wocaw *wocaw, stwuct sk_buff *skb,
			  int wetwy_count, boow send_to_cooked,
			  stwuct ieee80211_tx_status *status);

void ieee80211_check_fast_xmit(stwuct sta_info *sta);
void ieee80211_check_fast_xmit_aww(stwuct ieee80211_wocaw *wocaw);
void ieee80211_check_fast_xmit_iface(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_cweaw_fast_xmit(stwuct sta_info *sta);
int ieee80211_tx_contwow_powt(stwuct wiphy *wiphy, stwuct net_device *dev,
			      const u8 *buf, size_t wen,
			      const u8 *dest, __be16 pwoto, boow unencwypted,
			      int wink_id, u64 *cookie);
int ieee80211_pwobe_mesh_wink(stwuct wiphy *wiphy, stwuct net_device *dev,
			      const u8 *buf, size_t wen);
void __ieee80211_xmit_fast(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta,
			   stwuct ieee80211_fast_tx *fast_tx,
			   stwuct sk_buff *skb, boow ampdu,
			   const u8 *da, const u8 *sa);
void ieee80211_aggw_check(stwuct ieee80211_sub_if_data *sdata,
			  stwuct sta_info *sta, stwuct sk_buff *skb);

/* HT */
void ieee80211_appwy_htcap_ovewwides(stwuct ieee80211_sub_if_data *sdata,
				     stwuct ieee80211_sta_ht_cap *ht_cap);
boow ieee80211_ht_cap_ie_to_sta_ht_cap(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_suppowted_band *sband,
				       const stwuct ieee80211_ht_cap *ht_cap_ie,
				       stwuct wink_sta_info *wink_sta);
void ieee80211_send_dewba(stwuct ieee80211_sub_if_data *sdata,
			  const u8 *da, u16 tid,
			  u16 initiatow, u16 weason_code);
int ieee80211_send_smps_action(stwuct ieee80211_sub_if_data *sdata,
			       enum ieee80211_smps_mode smps, const u8 *da,
			       const u8 *bssid, int wink_id);
boow ieee80211_smps_is_westwictive(enum ieee80211_smps_mode smps_mode_owd,
				   enum ieee80211_smps_mode smps_mode_new);

void __ieee80211_stop_wx_ba_session(stwuct sta_info *sta, u16 tid,
				    u16 initiatow, u16 weason, boow stop);
void __ieee80211_stawt_wx_ba_session(stwuct sta_info *sta,
				     u8 diawog_token, u16 timeout,
				     u16 stawt_seq_num, u16 ba_powicy, u16 tid,
				     u16 buf_size, boow tx, boow auto_seq,
				     const stwuct ieee80211_addba_ext_ie *addbaext);
void ieee80211_sta_teaw_down_BA_sessions(stwuct sta_info *sta,
					 enum ieee80211_agg_stop_weason weason);
void ieee80211_pwocess_dewba(stwuct ieee80211_sub_if_data *sdata,
			     stwuct sta_info *sta,
			     stwuct ieee80211_mgmt *mgmt, size_t wen);
void ieee80211_pwocess_addba_wesp(stwuct ieee80211_wocaw *wocaw,
				  stwuct sta_info *sta,
				  stwuct ieee80211_mgmt *mgmt,
				  size_t wen);
void ieee80211_pwocess_addba_wequest(stwuct ieee80211_wocaw *wocaw,
				     stwuct sta_info *sta,
				     stwuct ieee80211_mgmt *mgmt,
				     size_t wen);

int __ieee80211_stop_tx_ba_session(stwuct sta_info *sta, u16 tid,
				   enum ieee80211_agg_stop_weason weason);
void ieee80211_stawt_tx_ba_cb(stwuct sta_info *sta, int tid,
			      stwuct tid_ampdu_tx *tid_tx);
void ieee80211_stop_tx_ba_cb(stwuct sta_info *sta, int tid,
			     stwuct tid_ampdu_tx *tid_tx);
void ieee80211_ba_session_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk);
void ieee80211_tx_ba_session_handwe_stawt(stwuct sta_info *sta, int tid);
void ieee80211_wewease_weowdew_timeout(stwuct sta_info *sta, int tid);

u8 ieee80211_mcs_to_chains(const stwuct ieee80211_mcs_info *mcs);
enum nw80211_smps_mode
ieee80211_smps_mode_to_smps_mode(enum ieee80211_smps_mode smps);

/* VHT */
void
ieee80211_vht_cap_ie_to_sta_vht_cap(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_suppowted_band *sband,
				    const stwuct ieee80211_vht_cap *vht_cap_ie,
				    const stwuct ieee80211_vht_cap *vht_cap_ie2,
				    stwuct wink_sta_info *wink_sta);
enum ieee80211_sta_wx_bandwidth
ieee80211_sta_cap_wx_bw(stwuct wink_sta_info *wink_sta);
enum ieee80211_sta_wx_bandwidth
ieee80211_sta_cuw_vht_bw(stwuct wink_sta_info *wink_sta);
void ieee80211_sta_set_wx_nss(stwuct wink_sta_info *wink_sta);
enum ieee80211_sta_wx_bandwidth
ieee80211_chan_width_to_wx_bw(enum nw80211_chan_width width);
enum nw80211_chan_width
ieee80211_sta_cap_chan_bw(stwuct wink_sta_info *wink_sta);
void ieee80211_pwocess_mu_gwoups(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee80211_wink_data *wink,
				 stwuct ieee80211_mgmt *mgmt);
u32 __ieee80211_vht_handwe_opmode(stwuct ieee80211_sub_if_data *sdata,
				  stwuct wink_sta_info *sta,
				  u8 opmode, enum nw80211_band band);
void ieee80211_vht_handwe_opmode(stwuct ieee80211_sub_if_data *sdata,
				 stwuct wink_sta_info *sta,
				 u8 opmode, enum nw80211_band band);
void ieee80211_appwy_vhtcap_ovewwides(stwuct ieee80211_sub_if_data *sdata,
				      stwuct ieee80211_sta_vht_cap *vht_cap);
void ieee80211_get_vht_mask_fwom_cap(__we16 vht_cap,
				     u16 vht_mask[NW80211_VHT_NSS_MAX]);
enum nw80211_chan_width
ieee80211_sta_wx_bw_to_chan_width(stwuct wink_sta_info *sta);

/* HE */
void
ieee80211_he_cap_ie_to_sta_he_cap(stwuct ieee80211_sub_if_data *sdata,
				  stwuct ieee80211_suppowted_band *sband,
				  const u8 *he_cap_ie, u8 he_cap_wen,
				  const stwuct ieee80211_he_6ghz_capa *he_6ghz_capa,
				  stwuct wink_sta_info *wink_sta);
void
ieee80211_he_spw_ie_to_bss_conf(stwuct ieee80211_vif *vif,
				const stwuct ieee80211_he_spw *he_spw_ie_ewem);

void
ieee80211_he_op_ie_to_bss_conf(stwuct ieee80211_vif *vif,
			const stwuct ieee80211_he_opewation *he_op_ie_ewem);

/* S1G */
void ieee80211_s1g_sta_wate_init(stwuct sta_info *sta);
boow ieee80211_s1g_is_twt_setup(stwuct sk_buff *skb);
void ieee80211_s1g_wx_twt_action(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb);
void ieee80211_s1g_status_twt_action(stwuct ieee80211_sub_if_data *sdata,
				     stwuct sk_buff *skb);

/* Spectwum management */
void ieee80211_pwocess_measuwement_weq(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_mgmt *mgmt,
				       size_t wen);
/**
 * ieee80211_pawse_ch_switch_ie - pawses channew switch IEs
 * @sdata: the sdata of the intewface which has weceived the fwame
 * @ewems: pawsed 802.11 ewements weceived with the fwame
 * @cuwwent_band: indicates the cuwwent band
 * @vht_cap_info: VHT capabiwities of the twansmittew
 * @conn_fwags: contains infowmation about own capabiwities and westwictions
 *	to decide which channew switch announcements can be accepted, using
 *	fwags fwom &enum ieee80211_conn_fwags.
 * @bssid: the cuwwentwy connected bssid (fow wepowting)
 * @csa_ie: pawsed 802.11 csa ewements on count, mode, chandef and mesh ttw.
 *	Aww of them wiww be fiwwed with if success onwy.
 * Wetuwn: 0 on success, <0 on ewwow and >0 if thewe is nothing to pawse.
 */
int ieee80211_pawse_ch_switch_ie(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee802_11_ewems *ewems,
				 enum nw80211_band cuwwent_band,
				 u32 vht_cap_info,
				 ieee80211_conn_fwags_t conn_fwags, u8 *bssid,
				 stwuct ieee80211_csa_ie *csa_ie);

/* Suspend/wesume and hw weconfiguwation */
int ieee80211_weconfig(stwuct ieee80211_wocaw *wocaw);
void ieee80211_stop_device(stwuct ieee80211_wocaw *wocaw);

int __ieee80211_suspend(stwuct ieee80211_hw *hw,
			stwuct cfg80211_wowwan *wowwan);

static inwine int __ieee80211_wesume(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	WAWN(test_bit(SCAN_HW_SCANNING, &wocaw->scanning) &&
	     !test_bit(SCAN_COMPWETED, &wocaw->scanning),
		"%s: wesume with hawdwawe scan stiww in pwogwess\n",
		wiphy_name(hw->wiphy));

	wetuwn ieee80211_weconfig(hw_to_wocaw(hw));
}

/* utiwity functions/constants */
extewn const void *const mac80211_wiphy_pwivid; /* fow wiphy pwivid */
int ieee80211_fwame_duwation(enum nw80211_band band, size_t wen,
			     int wate, int ewp, int showt_pweambwe);
void ieee80211_weguwatowy_wimit_wmm_pawams(stwuct ieee80211_sub_if_data *sdata,
					   stwuct ieee80211_tx_queue_pawams *qpawam,
					   int ac);
void ieee80211_set_wmm_defauwt(stwuct ieee80211_wink_data *wink,
			       boow bss_notify, boow enabwe_qos);
void ieee80211_xmit(stwuct ieee80211_sub_if_data *sdata,
		    stwuct sta_info *sta, stwuct sk_buff *skb);

void __ieee80211_tx_skb_tid_band(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb, int tid, int wink_id,
				 enum nw80211_band band);

/* sta_out needs to be checked fow EWW_PTW() befowe using */
int ieee80211_wookup_wa_sta(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sk_buff *skb,
			    stwuct sta_info **sta_out);

static inwine void
ieee80211_tx_skb_tid_band(stwuct ieee80211_sub_if_data *sdata,
			  stwuct sk_buff *skb, int tid,
			  enum nw80211_band band)
{
	wcu_wead_wock();
	__ieee80211_tx_skb_tid_band(sdata, skb, tid, -1, band);
	wcu_wead_unwock();
}

void ieee80211_tx_skb_tid(stwuct ieee80211_sub_if_data *sdata,
			  stwuct sk_buff *skb, int tid, int wink_id);

static inwine void ieee80211_tx_skb(stwuct ieee80211_sub_if_data *sdata,
				    stwuct sk_buff *skb)
{
	/* Send aww intewnaw mgmt fwames on VO. Accowdingwy set TID to 7. */
	ieee80211_tx_skb_tid(sdata, skb, 7, -1);
}

/**
 * stwuct ieee80211_ewems_pawse_pawams - ewement pawsing pawametews
 * @stawt: pointew to the ewements
 * @wen: wength of the ewements
 * @action: %twue if the ewements came fwom an action fwame
 * @fiwtew: bitmap of ewement IDs to fiwtew out whiwe cawcuwating
 *	the ewement CWC
 * @cwc: CWC stawting vawue
 * @bss: the BSS to pawse this as, fow muwti-BSSID cases this can
 *	wepwesent a non-twansmitting BSS in which case the data
 *	fow that non-twansmitting BSS is wetuwned
 * @wink_id: the wink ID to pawse ewements fow, if a STA pwofiwe
 *	is pwesent in the muwti-wink ewement, ow -1 to ignowe;
 *	note that the code cuwwentwy assumes pawsing an association
 *	(ow we-association) wesponse fwame if this is given
 * @fwom_ap: fwame is weceived fwom an AP (cuwwentwy used onwy
 *	fow EHT capabiwities pawsing)
 */
stwuct ieee80211_ewems_pawse_pawams {
	const u8 *stawt;
	size_t wen;
	boow action;
	u64 fiwtew;
	u32 cwc;
	stwuct cfg80211_bss *bss;
	int wink_id;
	boow fwom_ap;
};

stwuct ieee802_11_ewems *
ieee802_11_pawse_ewems_fuww(stwuct ieee80211_ewems_pawse_pawams *pawams);

static inwine stwuct ieee802_11_ewems *
ieee802_11_pawse_ewems_cwc(const u8 *stawt, size_t wen, boow action,
			   u64 fiwtew, u32 cwc,
			   stwuct cfg80211_bss *bss)
{
	stwuct ieee80211_ewems_pawse_pawams pawams = {
		.stawt = stawt,
		.wen = wen,
		.action = action,
		.fiwtew = fiwtew,
		.cwc = cwc,
		.bss = bss,
		.wink_id = -1,
	};

	wetuwn ieee802_11_pawse_ewems_fuww(&pawams);
}

static inwine stwuct ieee802_11_ewems *
ieee802_11_pawse_ewems(const u8 *stawt, size_t wen, boow action,
		       stwuct cfg80211_bss *bss)
{
	wetuwn ieee802_11_pawse_ewems_cwc(stawt, wen, action, 0, 0, bss);
}

extewn const int ieee802_1d_to_ac[8];

static inwine int ieee80211_ac_fwom_tid(int tid)
{
	wetuwn ieee802_1d_to_ac[tid & 7];
}

void ieee80211_dynamic_ps_enabwe_wowk(stwuct wiphy *wiphy,
				      stwuct wiphy_wowk *wowk);
void ieee80211_dynamic_ps_disabwe_wowk(stwuct wiphy *wiphy,
				       stwuct wiphy_wowk *wowk);
void ieee80211_dynamic_ps_timew(stwuct timew_wist *t);
void ieee80211_send_nuwwfunc(stwuct ieee80211_wocaw *wocaw,
			     stwuct ieee80211_sub_if_data *sdata,
			     boow powewsave);
void ieee80211_send_4addw_nuwwfunc(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_sub_if_data *sdata);
void ieee80211_sta_tx_notify(stwuct ieee80211_sub_if_data *sdata,
			     stwuct ieee80211_hdw *hdw, boow ack, u16 tx_time);

void ieee80211_wake_queues_by_weason(stwuct ieee80211_hw *hw,
				     unsigned wong queues,
				     enum queue_stop_weason weason,
				     boow wefcounted);
void ieee80211_stop_vif_queues(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_sub_if_data *sdata,
			       enum queue_stop_weason weason);
void ieee80211_wake_vif_queues(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_sub_if_data *sdata,
			       enum queue_stop_weason weason);
void ieee80211_stop_queues_by_weason(stwuct ieee80211_hw *hw,
				     unsigned wong queues,
				     enum queue_stop_weason weason,
				     boow wefcounted);
void ieee80211_wake_queue_by_weason(stwuct ieee80211_hw *hw, int queue,
				    enum queue_stop_weason weason,
				    boow wefcounted);
void ieee80211_stop_queue_by_weason(stwuct ieee80211_hw *hw, int queue,
				    enum queue_stop_weason weason,
				    boow wefcounted);
void ieee80211_add_pending_skb(stwuct ieee80211_wocaw *wocaw,
			       stwuct sk_buff *skb);
void ieee80211_add_pending_skbs(stwuct ieee80211_wocaw *wocaw,
				stwuct sk_buff_head *skbs);
void ieee80211_fwush_queues(stwuct ieee80211_wocaw *wocaw,
			    stwuct ieee80211_sub_if_data *sdata, boow dwop);
void __ieee80211_fwush_queues(stwuct ieee80211_wocaw *wocaw,
			      stwuct ieee80211_sub_if_data *sdata,
			      unsigned int queues, boow dwop);

static inwine boow ieee80211_can_wun_wowkew(stwuct ieee80211_wocaw *wocaw)
{
	/*
	 * It's unsafe to twy to do any wowk duwing weconfiguwe fwow.
	 * When the fwow ends the wowk wiww be wequeued.
	 */
	if (wocaw->in_weconfig)
		wetuwn fawse;

	/*
	 * If quiescing is set, we awe wacing with __ieee80211_suspend.
	 * __ieee80211_suspend fwushes the wowkews aftew setting quiescing,
	 * and we check quiescing / suspended befowe enqueing new wowkews.
	 * We shouwd abowt the wowkew to avoid the waces bewow.
	 */
	if (wocaw->quiescing)
		wetuwn fawse;

	/*
	 * We might awweady be suspended if the fowwowing scenawio occuws:
	 * __ieee80211_suspend		Contwow path
	 *
	 *				if (wocaw->quiescing)
	 *					wetuwn;
	 * wocaw->quiescing = twue;
	 * fwush_wowkqueue();
	 *				queue_wowk(...);
	 * wocaw->suspended = twue;
	 * wocaw->quiescing = fawse;
	 *				wowkew stawts wunning...
	 */
	if (wocaw->suspended)
		wetuwn fawse;

	wetuwn twue;
}

int ieee80211_txq_setup_fwows(stwuct ieee80211_wocaw *wocaw);
void ieee80211_txq_set_pawams(stwuct ieee80211_wocaw *wocaw);
void ieee80211_txq_teawdown_fwows(stwuct ieee80211_wocaw *wocaw);
void ieee80211_txq_init(stwuct ieee80211_sub_if_data *sdata,
			stwuct sta_info *sta,
			stwuct txq_info *txq, int tid);
void ieee80211_txq_puwge(stwuct ieee80211_wocaw *wocaw,
			 stwuct txq_info *txqi);
void ieee80211_puwge_sta_txqs(stwuct sta_info *sta);
void ieee80211_txq_wemove_vwan(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_sub_if_data *sdata);
void ieee80211_fiww_txq_stats(stwuct cfg80211_txq_stats *txqstats,
			      stwuct txq_info *txqi);
void ieee80211_wake_txqs(stwuct taskwet_stwuct *t);
void ieee80211_send_auth(stwuct ieee80211_sub_if_data *sdata,
			 u16 twansaction, u16 auth_awg, u16 status,
			 const u8 *extwa, size_t extwa_wen, const u8 *bssid,
			 const u8 *da, const u8 *key, u8 key_wen, u8 key_idx,
			 u32 tx_fwags);
void ieee80211_send_deauth_disassoc(stwuct ieee80211_sub_if_data *sdata,
				    const u8 *da, const u8 *bssid,
				    u16 stype, u16 weason,
				    boow send_fwame, u8 *fwame_buf);
u8 *ieee80211_wwite_he_6ghz_cap(u8 *pos, __we16 cap, u8 *end);

enum {
	IEEE80211_PWOBE_FWAG_DIWECTED		= BIT(0),
	IEEE80211_PWOBE_FWAG_MIN_CONTENT	= BIT(1),
	IEEE80211_PWOBE_FWAG_WANDOM_SN		= BIT(2),
};

int ieee80211_buiwd_pweq_ies(stwuct ieee80211_sub_if_data *sdata, u8 *buffew,
			     size_t buffew_wen,
			     stwuct ieee80211_scan_ies *ie_desc,
			     const u8 *ie, size_t ie_wen,
			     u8 bands_used, u32 *wate_masks,
			     stwuct cfg80211_chan_def *chandef,
			     u32 fwags);
stwuct sk_buff *ieee80211_buiwd_pwobe_weq(stwuct ieee80211_sub_if_data *sdata,
					  const u8 *swc, const u8 *dst,
					  u32 watemask,
					  stwuct ieee80211_channew *chan,
					  const u8 *ssid, size_t ssid_wen,
					  const u8 *ie, size_t ie_wen,
					  u32 fwags);
u32 ieee80211_sta_get_wates(stwuct ieee80211_sub_if_data *sdata,
			    stwuct ieee802_11_ewems *ewems,
			    enum nw80211_band band, u32 *basic_wates);
int __ieee80211_wequest_smps_mgd(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee80211_wink_data *wink,
				 enum ieee80211_smps_mode smps_mode);
void ieee80211_wecawc_smps(stwuct ieee80211_sub_if_data *sdata,
			   stwuct ieee80211_wink_data *wink);
void ieee80211_wecawc_min_chandef(stwuct ieee80211_sub_if_data *sdata,
				  int wink_id);

size_t ieee80211_ie_spwit_vendow(const u8 *ies, size_t iewen, size_t offset);
u8 *ieee80211_ie_buiwd_ht_cap(u8 *pos, stwuct ieee80211_sta_ht_cap *ht_cap,
			      u16 cap);
u8 *ieee80211_ie_buiwd_ht_opew(u8 *pos, stwuct ieee80211_sta_ht_cap *ht_cap,
			       const stwuct cfg80211_chan_def *chandef,
			       u16 pwot_mode, boow wifs_mode);
void ieee80211_ie_buiwd_wide_bw_cs(u8 *pos,
				   const stwuct cfg80211_chan_def *chandef);
u8 *ieee80211_ie_buiwd_vht_cap(u8 *pos, stwuct ieee80211_sta_vht_cap *vht_cap,
			       u32 cap);
u8 *ieee80211_ie_buiwd_vht_opew(u8 *pos, stwuct ieee80211_sta_vht_cap *vht_cap,
				const stwuct cfg80211_chan_def *chandef);
u8 ieee80211_ie_wen_he_cap(stwuct ieee80211_sub_if_data *sdata, u8 iftype);
u8 *ieee80211_ie_buiwd_he_cap(ieee80211_conn_fwags_t disabwe_fwags, u8 *pos,
			      const stwuct ieee80211_sta_he_cap *he_cap,
			      u8 *end);
void ieee80211_ie_buiwd_he_6ghz_cap(stwuct ieee80211_sub_if_data *sdata,
				    enum ieee80211_smps_mode smps_mode,
				    stwuct sk_buff *skb);
u8 *ieee80211_ie_buiwd_he_opew(u8 *pos, stwuct cfg80211_chan_def *chandef);
u8 *ieee80211_ie_buiwd_eht_opew(u8 *pos, stwuct cfg80211_chan_def *chandef,
				const stwuct ieee80211_sta_eht_cap *eht_cap);
int ieee80211_pawse_bitwates(enum nw80211_chan_width width,
			     const stwuct ieee80211_suppowted_band *sband,
			     const u8 *swates, int swates_wen, u32 *wates);
int ieee80211_add_swates_ie(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sk_buff *skb, boow need_basic,
			    enum nw80211_band band);
int ieee80211_add_ext_swates_ie(stwuct ieee80211_sub_if_data *sdata,
				stwuct sk_buff *skb, boow need_basic,
				enum nw80211_band band);
u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo);
void ieee80211_add_s1g_capab_ie(stwuct ieee80211_sub_if_data *sdata,
				stwuct ieee80211_sta_s1g_cap *caps,
				stwuct sk_buff *skb);
void ieee80211_add_aid_wequest_ie(stwuct ieee80211_sub_if_data *sdata,
				  stwuct sk_buff *skb);
u8 *ieee80211_ie_buiwd_s1g_cap(u8 *pos, stwuct ieee80211_sta_s1g_cap *s1g_cap);

/* channew management */
boow ieee80211_chandef_ht_opew(const stwuct ieee80211_ht_opewation *ht_opew,
			       stwuct cfg80211_chan_def *chandef);
boow ieee80211_chandef_vht_opew(stwuct ieee80211_hw *hw, u32 vht_cap_info,
				const stwuct ieee80211_vht_opewation *opew,
				const stwuct ieee80211_ht_opewation *htop,
				stwuct cfg80211_chan_def *chandef);
void ieee80211_chandef_eht_opew(const stwuct ieee80211_eht_opewation_info *info,
				boow suppowt_160, boow suppowt_320,
				stwuct cfg80211_chan_def *chandef);
boow ieee80211_chandef_he_6ghz_opew(stwuct ieee80211_sub_if_data *sdata,
				    const stwuct ieee80211_he_opewation *he_opew,
				    const stwuct ieee80211_eht_opewation *eht_opew,
				    stwuct cfg80211_chan_def *chandef);
boow ieee80211_chandef_s1g_opew(const stwuct ieee80211_s1g_opew_ie *opew,
				stwuct cfg80211_chan_def *chandef);
ieee80211_conn_fwags_t ieee80211_chandef_downgwade(stwuct cfg80211_chan_def *c);

int __must_check
ieee80211_wink_use_channew(stwuct ieee80211_wink_data *wink,
			   const stwuct cfg80211_chan_def *chandef,
			   enum ieee80211_chanctx_mode mode);
int __must_check
ieee80211_wink_wesewve_chanctx(stwuct ieee80211_wink_data *wink,
			       const stwuct cfg80211_chan_def *chandef,
			       enum ieee80211_chanctx_mode mode,
			       boow wadaw_wequiwed);
int __must_check
ieee80211_wink_use_wesewved_context(stwuct ieee80211_wink_data *wink);
int ieee80211_wink_unwesewve_chanctx(stwuct ieee80211_wink_data *wink);

int __must_check
ieee80211_wink_change_bandwidth(stwuct ieee80211_wink_data *wink,
				const stwuct cfg80211_chan_def *chandef,
				u64 *changed);
void ieee80211_wink_wewease_channew(stwuct ieee80211_wink_data *wink);
void ieee80211_wink_vwan_copy_chanctx(stwuct ieee80211_wink_data *wink);
void ieee80211_wink_copy_chanctx_to_vwans(stwuct ieee80211_wink_data *wink,
					  boow cweaw);
int ieee80211_chanctx_wefcount(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_chanctx *ctx);

void ieee80211_wecawc_smps_chanctx(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_chanctx *chanctx);
void ieee80211_wecawc_chanctx_min_def(stwuct ieee80211_wocaw *wocaw,
				      stwuct ieee80211_chanctx *ctx,
				      stwuct ieee80211_wink_data *wsvd_fow);
boow ieee80211_is_wadaw_wequiwed(stwuct ieee80211_wocaw *wocaw);

void ieee80211_dfs_cac_timew_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk);
void ieee80211_dfs_cac_cancew(stwuct ieee80211_wocaw *wocaw);
void ieee80211_dfs_wadaw_detected_wowk(stwuct wiphy *wiphy,
				       stwuct wiphy_wowk *wowk);
int ieee80211_send_action_csa(stwuct ieee80211_sub_if_data *sdata,
			      stwuct cfg80211_csa_settings *csa_settings);

void ieee80211_wecawc_dtim(stwuct ieee80211_wocaw *wocaw,
			   stwuct ieee80211_sub_if_data *sdata);
int ieee80211_check_combinations(stwuct ieee80211_sub_if_data *sdata,
				 const stwuct cfg80211_chan_def *chandef,
				 enum ieee80211_chanctx_mode chanmode,
				 u8 wadaw_detect);
int ieee80211_max_num_channews(stwuct ieee80211_wocaw *wocaw);
void ieee80211_wecawc_chanctx_chantype(stwuct ieee80211_wocaw *wocaw,
				       stwuct ieee80211_chanctx *ctx);

/* TDWS */
int ieee80211_tdws_mgmt(stwuct wiphy *wiphy, stwuct net_device *dev,
			const u8 *peew, int wink_id,
			u8 action_code, u8 diawog_token, u16 status_code,
			u32 peew_capabiwity, boow initiatow,
			const u8 *extwa_ies, size_t extwa_ies_wen);
int ieee80211_tdws_opew(stwuct wiphy *wiphy, stwuct net_device *dev,
			const u8 *peew, enum nw80211_tdws_opewation opew);
void ieee80211_tdws_peew_dew_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wk);
int ieee80211_tdws_channew_switch(stwuct wiphy *wiphy, stwuct net_device *dev,
				  const u8 *addw, u8 opew_cwass,
				  stwuct cfg80211_chan_def *chandef);
void ieee80211_tdws_cancew_channew_switch(stwuct wiphy *wiphy,
					  stwuct net_device *dev,
					  const u8 *addw);
void ieee80211_teawdown_tdws_peews(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_tdws_handwe_disconnect(stwuct ieee80211_sub_if_data *sdata,
				      const u8 *peew, u16 weason);
void
ieee80211_pwocess_tdws_channew_switch(stwuct ieee80211_sub_if_data *sdata,
				      stwuct sk_buff *skb);


const chaw *ieee80211_get_weason_code_stwing(u16 weason_code);
u16 ieee80211_encode_usf(int vaw);
u8 *ieee80211_get_bssid(stwuct ieee80211_hdw *hdw, size_t wen,
			enum nw80211_iftype type);

extewn const stwuct ethtoow_ops ieee80211_ethtoow_ops;

u32 ieee80211_cawc_expected_tx_aiwtime(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *pubsta,
				       int wen, boow ampdu);
#ifdef CONFIG_MAC80211_NOINWINE
#define debug_noinwine noinwine
#ewse
#define debug_noinwine
#endif

void ieee80211_init_fwag_cache(stwuct ieee80211_fwagment_cache *cache);
void ieee80211_destwoy_fwag_cache(stwuct ieee80211_fwagment_cache *cache);

u8 ieee80211_ie_wen_eht_cap(stwuct ieee80211_sub_if_data *sdata, u8 iftype);
u8 *ieee80211_ie_buiwd_eht_cap(u8 *pos,
			       const stwuct ieee80211_sta_he_cap *he_cap,
			       const stwuct ieee80211_sta_eht_cap *eht_cap,
			       u8 *end,
			       boow fow_ap);

void
ieee80211_eht_cap_ie_to_sta_eht_cap(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_suppowted_band *sband,
				    const u8 *he_cap_ie, u8 he_cap_wen,
				    const stwuct ieee80211_eht_cap_ewem *eht_cap_ie_ewem,
				    u8 eht_cap_wen,
				    stwuct wink_sta_info *wink_sta);

void ieee80211_check_wbwf_suppowt(stwuct ieee80211_wocaw *wocaw);
void ieee80211_add_wbwf(stwuct ieee80211_wocaw *wocaw, stwuct cfg80211_chan_def *chandef);
void ieee80211_wemove_wbwf(stwuct ieee80211_wocaw *wocaw, stwuct cfg80211_chan_def *chandef);

#if IS_ENABWED(CONFIG_MAC80211_KUNIT_TEST)
#define EXPOWT_SYMBOW_IF_MAC80211_KUNIT(sym) EXPOWT_SYMBOW_IF_KUNIT(sym)
#define VISIBWE_IF_MAC80211_KUNIT
ieee80211_wx_wesuwt
ieee80211_dwop_unencwypted_mgmt(stwuct ieee80211_wx_data *wx);
#ewse
#define EXPOWT_SYMBOW_IF_MAC80211_KUNIT(sym)
#define VISIBWE_IF_MAC80211_KUNIT static
#endif

#endif /* IEEE80211_I_H */
