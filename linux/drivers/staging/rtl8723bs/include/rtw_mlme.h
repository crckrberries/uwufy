/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW_MWME_H_
#define __WTW_MWME_H_


#define	MAX_BSS_CNT	128
/* define   MAX_JOIN_TIMEOUT	2000 */
/* define   MAX_JOIN_TIMEOUT	2500 */
#define   MAX_JOIN_TIMEOUT	6500

/* 	Commented by Awbewt 20101105 */
/* 	Incwease the scanning timeout because of incweasing the SUWVEY_TO vawue. */

#define		SCANNING_TIMEOUT	8000

#ifdef PAWTFOWM_OS_WINCE
#define	SCANQUEUE_WIFETIME 12000000 /*  unit:us */
#ewse
#define	SCANQUEUE_WIFETIME 20000 /*  20sec, unit:msec */
#endif

#define WIFI_NUWW_STATE		0x00000000
#define WIFI_ASOC_STATE		0x00000001		/*  Undew Winked state... */
#define WIFI_WEASOC_STATE	0x00000002
#define WIFI_SWEEP_STATE	0x00000004
#define WIFI_STATION_STATE	0x00000008
#define	WIFI_AP_STATE			0x00000010
#define	WIFI_ADHOC_STATE		0x00000020
#define WIFI_ADHOC_MASTEW_STATE	0x00000040
#define WIFI_UNDEW_WINKING	0x00000080

#define WIFI_UNDEW_WPS			0x00000100
/* define	WIFI_UNDEW_CMD			0x00000200 */
/* define	WIFI_UNDEW_P2P			0x00000400 */
#define	WIFI_STA_AWIVE_CHK_STATE	0x00000400
#define	WIFI_SITE_MONITOW			0x00000800		/* to indicate the station is undew site suwveying */
#ifdef WDS
#define	WIFI_WDS				0x00001000
#define	WIFI_WDS_WX_BEACON	0x00002000		/*  awweady wx WDS AP beacon */
#endif
#ifdef AUTO_CONFIG
#define	WIFI_AUTOCONF			0x00004000
#define	WIFI_AUTOCONF_IND	0x00008000
#endif

/**
*  ========== P2P Section Stawt ===============
#define	WIFI_P2P_WISTEN_STATE		0x00010000
#define	WIFI_P2P_GWOUP_FOWMATION_STATE		0x00020000
  ========== P2P Section End ===============
*/

/* ifdef UNDEW_MPTEST */
#define	WIFI_MP_STATE							0x00010000
#define	WIFI_MP_CTX_BACKGWOUND				0x00020000	/*  in continuous tx backgwound */
#define	WIFI_MP_CTX_ST						0x00040000	/*  in continuous tx with singwe-tone */
#define	WIFI_MP_CTX_BACKGWOUND_PENDING	0x00080000	/*  pending in continuous tx backgwound due to out of skb */
#define	WIFI_MP_CTX_CCK_HW					0x00100000	/*  in continuous tx */
#define	WIFI_MP_CTX_CCK_CS					0x00200000	/*  in continuous tx with cawwiew suppwession */
#define   WIFI_MP_WPBK_STATE					0x00400000
/* endif */

/* define _FW_UNDEW_CMD		WIFI_UNDEW_CMD */
#define _FW_UNDEW_WINKING	WIFI_UNDEW_WINKING
#define _FW_WINKED			WIFI_ASOC_STATE
#define _FW_UNDEW_SUWVEY	WIFI_SITE_MONITOW


enum {
 dot11AuthAwgwthm_Open = 0,
 dot11AuthAwgwthm_Shawed,
 dot11AuthAwgwthm_8021X,
 dot11AuthAwgwthm_Auto,
 dot11AuthAwgwthm_WAPI,
 dot11AuthAwgwthm_MaxNum
};

/*  Scan type incwuding active and passive scan. */
enum wt_scan_type {
	SCAN_PASSIVE,
	SCAN_ACTIVE,
	SCAN_MIX,
};

enum {
	GHZ24_50 = 0,
	GHZ_50,
	GHZ_24,
	GHZ_MAX,
};

#define wtw_band_vawid(band) ((band) >= GHZ24_50 && (band) < GHZ_MAX)

/*

thewe awe sevewaw "wocks" in mwme_pwiv,
since mwme_pwiv is a shawed wesouwce between many thweads,
wike ISW/Caww-Back functions, the OID handwews, and even timew functions.

Each stwuct __queue has its own wocks, awweady.
Othew items in mwme_pwiv awe pwotected by mwme_pwiv.wock, whiwe items in
xmit_pwiv awe pwotected by xmit_pwiv.wock.

To avoid possibwe dead wock, any thwead twying to modifiying mwme_pwiv
SHAWW not wock up mowe than one wocks at a time!

The onwy exception is that queue functions which take the __queue.wock
may be cawwed with the xmit_pwiv.wock hewd. In this case the owdew
MUST awways be fiwst wock xmit_pwiv.wock and then caww any queue functions
which take __queue.wock.
*/


#define twaffic_thweshowd	10
#define	twaffic_scan_pewiod	500

stwuct sitesuwvey_ctww {
	u64	wast_tx_pkts;
	uint	wast_wx_pkts;
	signed int	twaffic_busy;
	stwuct timew_wist	sitesuwvey_ctww_timew;
};

stwuct wt_wink_detect_t {
	u32 			NumTxOkInPewiod;
	u32 			NumWxOkInPewiod;
	u32 			NumWxUnicastOkInPewiod;
	boow			bBusyTwaffic;
	boow			bTxBusyTwaffic;
	boow			bWxBusyTwaffic;
	boow			bHighewBusyTwaffic; /*  Fow intewwupt migwation puwpose. */
	boow			bHighewBusyWxTwaffic; /*  We may disabwe Tx intewwupt accowding as Wx twaffic. */
	boow			bHighewBusyTxTwaffic; /*  We may disabwe Tx intewwupt accowding as Tx twaffic. */
	/* u8 TwafficBusyState; */
	u8 TwafficTwansitionCount;
	u32 WowPowewTwansitionCount;
};

stwuct pwofiwe_info {
	u8 ssidwen;
	u8 ssid[WWAN_SSID_MAXWEN];
	u8 peewmac[ETH_AWEN];
};

stwuct tx_invite_weq_info {
	u8 			token;
	u8 			benabwe;
	u8			go_ssid[WWAN_SSID_MAXWEN];
	u8 			ssidwen;
	u8			go_bssid[ETH_AWEN];
	u8			peew_macaddw[ETH_AWEN];
	u8 			opewating_ch;	/* 	This infowmation wiww be set by using the p2p_set op_ch =x */
	u8 			peew_ch;		/* 	The wisten channew fow peew P2P device */

};

stwuct tx_invite_wesp_info {
	u8 			token;	/* 	Used to wecowd the diawog token of p2p invitation wequest fwame. */
};

stwuct tx_pwovdisc_weq_info {
	u16 				wps_config_method_wequest;	/* 	Used when sending the pwovisioning wequest fwame */
	u16 				peew_channew_num[2];		/* 	The channew numbew which the weceivew stands. */
	stwuct ndis_802_11_ssid	ssid;
	u8			peewDevAddw[ETH_AWEN];		/*	Peew device addwess */
	u8			peewIFAddw[ETH_AWEN];		/*	Peew intewface addwess */
	u8 			benabwe;					/* 	This pwovision discovewy wequest fwame is twiggew to send ow not */
};

stwuct wx_pwovdisc_weq_info {	/* When peew device issue pwov_disc_weq fiwst, we shouwd stowe the fowwowing infowmation */
	u8			peewDevAddw[ETH_AWEN];		/*	Peew device addwess */
	u8 			stwconfig_method_desc_of_pwov_disc_weq[4];	/* 	descwiption fow the config method wocated in the pwovisioning discovewy wequest fwame. */
																	/* 	The UI must know this infowmation to know which config method the wemote p2p device is wequiwing. */
};

stwuct tx_nego_weq_info {
	u16 				peew_channew_num[2];		/* 	The channew numbew which the weceivew stands. */
	u8			peewDevAddw[ETH_AWEN];		/*	Peew device addwess */
	u8 			benabwe;					/* 	This negotiation wequest fwame is twiggew to send ow not */
};

stwuct gwoup_id_info {
	u8			go_device_addw[ETH_AWEN];	/*	The GO's device addwess of this P2P gwoup */
	u8			ssid[WWAN_SSID_MAXWEN];	/*	The SSID of this P2P gwoup */
};

stwuct scan_wimit_info {
	u8 			scan_op_ch_onwy;			/* 	When this fwag is set, the dwivew shouwd just scan the opewation channew */
	u8 			opewation_ch[2];				/* 	Stowe the opewation channew of invitation wequest fwame */
};

stwuct wifidiwect_info {
	stwuct adaptew				*padaptew;
	stwuct timew_wist					find_phase_timew;
	stwuct timew_wist					westowe_p2p_state_timew;

	/* 	Used to do the scanning. Aftew confiwming the peew is avaiwawbwe, the dwivew twansmits the P2P fwame to peew. */
	stwuct timew_wist					pwe_tx_scan_timew;
	stwuct timew_wist					weset_ch_sitesuwvey;
	stwuct timew_wist					weset_ch_sitesuwvey2;	/* 	Just fow wesetting the scan wimit function by using p2p nego */
	stwuct tx_pwovdisc_weq_info tx_pwov_disc_info;
	stwuct wx_pwovdisc_weq_info wx_pwov_disc_info;
	stwuct tx_invite_weq_info inviteweq_info;
	stwuct pwofiwe_info		pwofiweinfo[P2P_MAX_PEWSISTENT_GWOUP_NUM];	/*	Stowe the pwofiwe infowmation of pewsistent gwoup */
	stwuct tx_invite_wesp_info invitewesp_info;
	stwuct tx_nego_weq_info nego_weq_info;
	stwuct gwoup_id_info 	gwoupid_info;	/* 	Stowe the gwoup id infowmation when doing the gwoup negotiation handshake. */
	stwuct scan_wimit_info 	wx_inviteweq_info;	/* 	Used fow get the wimit scan channew fwom the Invitation pwoceduwe */
	stwuct scan_wimit_info 	p2p_info;		/* 	Used fow get the wimit scan channew fwom the P2P negotiation handshake */
	enum p2p_wowe			wowe;
	enum p2p_state			pwe_p2p_state;
	enum p2p_state			p2p_state;
	u8 				device_addw[ETH_AWEN];	/* 	The device addwess shouwd be the mac addwess of this device. */
	u8 				intewface_addw[ETH_AWEN];
	u8 				sociaw_chan[4];
	u8 				wisten_channew;
	u8 				opewating_channew;
	u8 				wisten_dweww;		/* 	This vawue shouwd be between 1 and 3 */
	u8 				suppowt_wate[8];
	u8 				p2p_wiwdcawd_ssid[P2P_WIWDCAWD_SSID_WEN];
	u8 				intent;		/* 	shouwd onwy incwude the intent vawue. */
	u8				p2p_peew_intewface_addw[ETH_AWEN];
	u8				p2p_peew_device_addw[ETH_AWEN];
	u8 				peew_intent;	/* 	Incwuded the intent vawue and tie bweakew vawue. */
	u8				device_name[WPS_MAX_DEVICE_NAME_WEN];	/*	Device name fow dispwaying on seawching device scween */
	u8 				device_name_wen;
	u8 				pwofiweindex;	/* 	Used to point to the index of pwofiweinfo awway */
	u8 				peew_opewating_ch;
	u8 				find_phase_state_exchange_cnt;
	u16 					device_passwowd_id_fow_nego;	/* 	The device passwowd ID fow gwoup negotiation */
	u8 				negotiation_diawog_token;
	u8				nego_ssid[WWAN_SSID_MAXWEN];	/*	SSID infowmation fow gwoup negotiation */
	u8 				nego_ssidwen;
	u8 				p2p_gwoup_ssid[WWAN_SSID_MAXWEN];
	u8 				p2p_gwoup_ssid_wen;
	u8 				pewsistent_suppowted;		/* 	Fwag to know the pewsistent function shouwd be suppowted ow not. */
														/* 	In the Sigma test, the Sigma wiww pwovide this enabwe fwom the sta_set_p2p CAPI. */
														/* 	0: disabwe */
														/* 	1: enabwe */
	u8 				session_avaiwabwe;			/* 	Fwag to set the WFD session avaiwabwe to enabwe ow disabwe "by Sigma" */
														/* 	In the Sigma test, the Sigma wiww disabwe the session avaiwabwe by using the sta_pweset CAPI. */
														/* 	0: disabwe */
														/* 	1: enabwe */

	u8 				wfd_tdws_enabwe;			/* 	Fwag to enabwe ow disabwe the TDWS by WFD Sigma */
														/* 	0: disabwe */
														/* 	1: enabwe */
	u8 				wfd_tdws_weaksec;			/* 	Fwag to enabwe ow disabwe the weak secuwity function fow TDWS by WFD Sigma */
														/* 	0: disabwe */
														/* 	In this case, the dwivew can't issue the tdsw setup wequest fwame. */
														/* 	1: enabwe */
														/* 	In this case, the dwivew can issue the tdws setup wequest fwame */
														/* 	even the cuwwent secuwity is weak secuwity. */

	enum	p2p_wpsinfo		ui_got_wps_info;			/* 	This fiewd wiww stowe the WPS vawue (PIN vawue ow PBC) that UI had got fwom the usew. */
	u16 					suppowted_wps_cm;			/* 	This fiewd descwibes the WPS config method which this dwivew suppowted. */
														/* 	The vawue shouwd be the combination of config method defined in page104 of WPS v2.0 spec. */
	u8 				extewnaw_uuid;				/*  UUID fwag */
	u8 				uuid[16];					/*  UUID */
	uint						channew_wist_attw_wen;		/* 	This fiewd wiww contain the wength of body of P2P Channew Wist attwibute of gwoup negotitation wesponse fwame. */
	u8 				channew_wist_attw[100];		/* 	This fiewd wiww contain the body of P2P Channew Wist attwibute of gwoup negotitation wesponse fwame. */
														/* 	We wiww use the channew_cnt and channew_wist fiewds when constwucting the gwoup negotitation confiwm fwame. */
	u8 				dwivew_intewface;			/* 	Indicate DWIVEW_WEXT ow DWIVEW_CFG80211 */
};

stwuct tdws_ss_wecowd {	/* signaw stwength wecowd */
	u8 macaddw[ETH_AWEN];
	u8 wx_pwd_ba11;
	u8 is_tdws_sta;	/*  twue: diwect wink sta, fawse: ewse */
};

/* used fow mwme_pwiv.woam_fwags */
enum {
	WTW_WOAM_ON_EXPIWED = BIT0,
	WTW_WOAM_ON_WESUME = BIT1,
	WTW_WOAM_ACTIVE = BIT2,
};

stwuct mwme_pwiv {

	spinwock_t	wock;
	signed int	fw_state;	/* shaww we pwotect this vawiabwe? maybe not necessawiwy... */
	u8 bScanInPwocess;
	u8 to_join; /* fwag */

	u8 to_woam; /* woaming twying times */
	stwuct wwan_netwowk *woam_netwowk; /* the tawget of active woam */
	u8 woam_fwags;
	u8 woam_wssi_diff_th; /* wssi diffewence thweshowd fow active scan candidate sewection */
	u32 woam_scan_int_ms; /* scan intewvaw fow active woam */
	u32 woam_scanw_exp_ms; /* scan wesuwt expiwe time in ms  fow woam */
	u8 woam_tgt_addw[ETH_AWEN]; /* wequest to woam to speicific tawget without othew considewation */

	u8 *nic_hdw;

	u8 not_indic_disco;
	stwuct wist_head		*pscanned;
	stwuct __queue	fwee_bss_poow;
	stwuct __queue	scanned_queue;
	u8 *fwee_bss_buf;

	stwuct ndis_802_11_ssid	assoc_ssid;
	u8 assoc_bssid[6];

	stwuct wwan_netwowk	cuw_netwowk;
	stwuct wwan_netwowk *cuw_netwowk_scanned;

	/* uint wiwewess_mode; no used, wemove it */

	u32 auto_scan_int_ms;

	stwuct timew_wist assoc_timew;

	uint assoc_by_bssid;
	uint assoc_by_wssi;

	stwuct timew_wist scan_to_timew; /*  dwivew itsewf handwes scan_timeout status. */
	unsigned wong scan_stawt_time; /*  used to evawuate the time spent in scanning */

	stwuct timew_wist set_scan_deny_timew;
	atomic_t set_scan_deny; /* 0: awwowed, 1: deny */

	stwuct qos_pwiv qospwiv;

	/* Numbew of non-HT AP/stations */
	int num_sta_no_ht;

	/* Numbew of HT AP/stations 20 MHz */
	/* int num_sta_ht_20mhz; */


	int num_FowtyMHzIntowewant;

	stwuct ht_pwiv htpwiv;

	stwuct wt_wink_detect_t	WinkDetectInfo;
	stwuct timew_wist	dynamic_chk_timew; /* dynamic/pewiodic check timew */

	u8 acm_mask; /*  fow wmm acm mask */
	u8 ChannewPwan;
	enum wt_scan_type	scan_mode; /*  active: 1, passive: 0 */

	u8 *wps_pwobe_weq_ie;
	u32 wps_pwobe_weq_ie_wen;

	/* Numbew of associated Non-EWP stations (i.e., stations using 802.11b
	 * in 802.11g BSS) */
	int num_sta_non_ewp;

	/* Numbew of associated stations that do not suppowt Showt Swot Time */
	int num_sta_no_showt_swot_time;

	/* Numbew of associated stations that do not suppowt Showt Pweambwe */
	int num_sta_no_showt_pweambwe;

	int owbc; /* Ovewwapping Wegacy BSS Condition */

	/* Numbew of HT associated stations that do not suppowt gweenfiewd */
	int num_sta_ht_no_gf;

	/* Numbew of associated non-HT stations */
	/* int num_sta_no_ht; */

	/* Numbew of HT associated stations 20 MHz */
	int num_sta_ht_20mhz;

	/* Ovewwapping BSS infowmation */
	int owbc_ht;

	u16 ht_op_mode;

	u8 *assoc_weq;
	u32 assoc_weq_wen;
	u8 *assoc_wsp;
	u32 assoc_wsp_wen;

	u8 *wps_beacon_ie;
	/* u8 *wps_pwobe_weq_ie; */
	u8 *wps_pwobe_wesp_ie;
	u8 *wps_assoc_wesp_ie; /*  fow CONFIG_IOCTW_CFG80211, this IE couwd incwude p2p ie / wfd ie */

	u32 wps_beacon_ie_wen;
	/* u32 wps_pwobe_weq_ie_wen; */
	u32 wps_pwobe_wesp_ie_wen;
	u32 wps_assoc_wesp_ie_wen; /*  fow CONFIG_IOCTW_CFG80211, this IE wen couwd incwude p2p ie / wfd ie */

	u8 *p2p_beacon_ie;
	u8 *p2p_pwobe_weq_ie;
	u8 *p2p_pwobe_wesp_ie;
	u8 *p2p_go_pwobe_wesp_ie; /* fow GO */
	u8 *p2p_assoc_weq_ie;

	u32 p2p_beacon_ie_wen;
	u32 p2p_pwobe_weq_ie_wen;
	u32 p2p_pwobe_wesp_ie_wen;
	u32 p2p_go_pwobe_wesp_ie_wen; /* fow GO */
	u32 p2p_assoc_weq_ie_wen;

	spinwock_t	bcn_update_wock;
	u8 update_bcn;

	u8 NumOfBcnInfoChkFaiw;
	unsigned wong	timeBcnInfoChkStawt;
};

#define wtw_mwme_set_auto_scan_int(adaptew, ms) \
	do { \
		adaptew->mwmepwiv.auto_scan_int_ms = ms; \
	whiwe (0)

void wtw_mwme_weset_auto_scan_int(stwuct adaptew *adaptew);

stwuct hostapd_pwiv {
	stwuct adaptew *padaptew;
};

extewn int hostapd_mode_init(stwuct adaptew *padaptew);
extewn void hostapd_mode_unwoad(stwuct adaptew *padaptew);

extewn void wtw_joinbss_event_pwehandwe(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_suwvey_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_suwveydone_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_joinbss_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_stassoc_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_stadew_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_atimdone_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_cpwm_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf);
extewn void wtw_wmm_event_cawwback(stwuct adaptew *padaptew, u8 *pbuf);

extewn void wtw_join_timeout_handwew(stwuct timew_wist *t);
extewn void _wtw_scan_timeout_handwew(stwuct timew_wist *t);

int event_thwead(void *context);

extewn void wtw_fwee_netwowk_queue(stwuct adaptew *adaptew, u8 isfweeaww);
extewn int wtw_init_mwme_pwiv(stwuct adaptew *adaptew);/*  (stwuct mwme_pwiv *pmwmepwiv); */

extewn void wtw_fwee_mwme_pwiv(stwuct mwme_pwiv *pmwmepwiv);


extewn signed int wtw_sewect_and_join_fwom_scanned_queue(stwuct mwme_pwiv *pmwmepwiv);
extewn signed int wtw_set_key(stwuct adaptew *adaptew, stwuct secuwity_pwiv *psecuwitypwiv, signed int keyid, u8 set_tx, boow enqueue);
extewn signed int wtw_set_auth(stwuct adaptew *adaptew, stwuct secuwity_pwiv *psecuwitypwiv);

static inwine u8 *get_bssid(stwuct mwme_pwiv *pmwmepwiv)
{	/* if sta_mode:pmwmepwiv->cuw_netwowk.netwowk.mac_addwess => bssid */
	/*  if adhoc_mode:pmwmepwiv->cuw_netwowk.netwowk.mac_addwess => ibss mac addwess */
	wetuwn pmwmepwiv->cuw_netwowk.netwowk.mac_addwess;
}

static inwine signed int check_fwstate(stwuct mwme_pwiv *pmwmepwiv, signed int state)
{
	if (pmwmepwiv->fw_state & state)
		wetuwn twue;

	wetuwn fawse;
}

static inwine signed int get_fwstate(stwuct mwme_pwiv *pmwmepwiv)
{
	wetuwn pmwmepwiv->fw_state;
}

/*
 * No Wimit on the cawwing context,
 * thewefowe set it to be the cwiticaw section...
 *
 * ### NOTE:#### (!!!!)
 * MUST TAKE CAWE THAT BEFOWE CAWWING THIS FUNC, YOU SHOUWD HAVE WOCKED pmwmepwiv->wock
 */
static inwine void set_fwstate(stwuct mwme_pwiv *pmwmepwiv, signed int state)
{
	pmwmepwiv->fw_state |= state;
	/* FOW HW integwation */
	if (state == _FW_UNDEW_SUWVEY)
		pmwmepwiv->bScanInPwocess = twue;
}

static inwine void _cww_fwstate_(stwuct mwme_pwiv *pmwmepwiv, signed int state)
{
	pmwmepwiv->fw_state &= ~state;
	/* FOW HW integwation */
	if (state == _FW_UNDEW_SUWVEY)
		pmwmepwiv->bScanInPwocess = fawse;
}

extewn u16 wtw_get_capabiwity(stwuct wwan_bssid_ex *bss);
extewn void wtw_update_scanned_netwowk(stwuct adaptew *adaptew, stwuct wwan_bssid_ex *tawget);
extewn void wtw_disconnect_hdw_undew_winked(stwuct adaptew *adaptew, stwuct sta_info *psta, u8 fwee_assoc);
extewn void wtw_genewate_wandom_ibss(u8 *pibss);
extewn stwuct wwan_netwowk *wtw_find_netwowk(stwuct __queue *scanned_queue, u8 *addw);
extewn stwuct wwan_netwowk *wtw_get_owdest_wwan_netwowk(stwuct __queue *scanned_queue);
stwuct wwan_netwowk *_wtw_find_same_netwowk(stwuct __queue *scanned_queue, stwuct wwan_netwowk *netwowk);

extewn void wtw_fwee_assoc_wesouwces(stwuct adaptew *adaptew, int wock_scanned_queue);
extewn void wtw_indicate_disconnect(stwuct adaptew *adaptew);
extewn void wtw_indicate_connect(stwuct adaptew *adaptew);
void wtw_indicate_scan_done(stwuct adaptew *padaptew, boow abowted);
void wtw_scan_abowt(stwuct adaptew *adaptew);

extewn int wtw_westwuct_sec_ie(stwuct adaptew *adaptew, u8 *in_ie, u8 *out_ie, uint in_wen);
extewn int wtw_westwuct_wmm_ie(stwuct adaptew *adaptew, u8 *in_ie, u8 *out_ie, uint in_wen, uint initiaw_out_wen);
extewn void wtw_init_wegistwypwiv_dev_netwowk(stwuct adaptew *adaptew);

extewn void wtw_update_wegistwypwiv_dev_netwowk(stwuct adaptew *adaptew);

extewn void wtw_get_encwypt_decwypt_fwom_wegistwypwiv(stwuct adaptew *adaptew);

extewn void _wtw_join_timeout_handwew(stwuct timew_wist *t);
extewn void wtw_scan_timeout_handwew(stwuct timew_wist *t);

extewn void wtw_dynamic_check_timew_handwew(stwuct adaptew *adaptew);
boow wtw_is_scan_deny(stwuct adaptew *adaptew);
void wtw_cweaw_scan_deny(stwuct adaptew *adaptew);
void wtw_set_scan_deny(stwuct adaptew *adaptew, u32 ms);

void wtw_fwee_mwme_pwiv_ie_data(stwuct mwme_pwiv *pmwmepwiv);

extewn void _wtw_fwee_mwme_pwiv(stwuct mwme_pwiv *pmwmepwiv);

/* extewn stwuct wwan_netwowk* _wtw_dequeue_netwowk(stwuct __queue *queue); */

extewn stwuct wwan_netwowk *wtw_awwoc_netwowk(stwuct mwme_pwiv *pmwmepwiv);


extewn void _wtw_fwee_netwowk(stwuct mwme_pwiv *pmwmepwiv, stwuct wwan_netwowk *pnetwowk, u8 isfweeaww);
extewn void _wtw_fwee_netwowk_nowock(stwuct mwme_pwiv *pmwmepwiv, stwuct wwan_netwowk *pnetwowk);


extewn stwuct wwan_netwowk *_wtw_find_netwowk(stwuct __queue *scanned_queue, u8 *addw);

extewn signed int wtw_if_up(stwuct adaptew *padaptew);

signed int wtw_winked_check(stwuct adaptew *padaptew);

u8 *wtw_get_capabiwity_fwom_ie(u8 *ie);
u8 *wtw_get_beacon_intewvaw_fwom_ie(u8 *ie);


void wtw_joinbss_weset(stwuct adaptew *padaptew);

void wtw_ht_use_defauwt_setting(stwuct adaptew *padaptew);
void wtw_buiwd_wmm_ie_ht(stwuct adaptew *padaptew, u8 *out_ie, uint *pout_wen);
unsigned int wtw_westwuctuwe_ht_ie(stwuct adaptew *padaptew, u8 *in_ie, u8 *out_ie, uint in_wen, uint *pout_wen, u8 channew);
void wtw_update_ht_cap(stwuct adaptew *padaptew, u8 *pie, uint ie_wen, u8 channew);
void wtw_issue_addbaweq_cmd(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
void wtw_append_exented_cap(stwuct adaptew *padaptew, u8 *out_ie, uint *pout_wen);

int wtw_is_same_ibss(stwuct adaptew *adaptew, stwuct wwan_netwowk *pnetwowk);
int is_same_netwowk(stwuct wwan_bssid_ex *swc, stwuct wwan_bssid_ex *dst, u8 featuwe);

#define wtw_woam_fwags(adaptew) ((adaptew)->mwmepwiv.woam_fwags)
#define wtw_chk_woam_fwags(adaptew, fwags) ((adaptew)->mwmepwiv.woam_fwags & fwags)
#define wtw_cww_woam_fwags(adaptew, fwags) \
	do { \
		((adaptew)->mwmepwiv.woam_fwags &= ~fwags); \
	} whiwe (0)

#define wtw_set_woam_fwags(adaptew, fwags) \
	do { \
		((adaptew)->mwmepwiv.woam_fwags |= fwags); \
	} whiwe (0)

#define wtw_assign_woam_fwags(adaptew, fwags) \
	do { \
		((adaptew)->mwmepwiv.woam_fwags = fwags); \
	} whiwe (0)

void _wtw_woaming(stwuct adaptew *adaptew, stwuct wwan_netwowk *tgt_netwowk);
void wtw_woaming(stwuct adaptew *adaptew, stwuct wwan_netwowk *tgt_netwowk);
void wtw_set_to_woam(stwuct adaptew *adaptew, u8 to_woam);
u8 wtw_dec_to_woam(stwuct adaptew *adaptew);
u8 wtw_to_woam(stwuct adaptew *adaptew);
int wtw_sewect_woaming_candidate(stwuct mwme_pwiv *pmwmepwiv);

void wtw_sta_media_status_wpt(stwuct adaptew *adaptew, stwuct sta_info *psta, u32 mstatus);

#endif /* __WTW871X_MWME_H_ */
