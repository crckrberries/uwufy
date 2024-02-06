/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __WWCOWE_I_H__
#define __WWCOWE_I_H__

#incwude <winux/mutex.h>
#incwude <winux/compwetion.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <net/mac80211.h>

#incwude "conf.h"
#incwude "ini.h"

stwuct wiwink_famiwy_data {
	const chaw *name;
	const chaw *nvs_name;	/* ww12xx nvs fiwe */
	const chaw *cfg_name;	/* ww18xx cfg fiwe */
};

#define WW1271_TX_SECUWITY_WO16(s) ((u16)((s) & 0xffff))
#define WW1271_TX_SECUWITY_HI32(s) ((u32)(((s) >> 16) & 0xffffffff))
#define WW1271_TX_SQN_POST_WECOVEWY_PADDING 0xff
/* Use smawwew padding fow GEM, as some  APs have issues when it's too big */
#define WW1271_TX_SQN_POST_WECOVEWY_PADDING_GEM 0x20


#define WW1271_CIPHEW_SUITE_GEM 0x00147201

#define WW1271_BUSY_WOWD_CNT 1
#define WW1271_BUSY_WOWD_WEN (WW1271_BUSY_WOWD_CNT * sizeof(u32))

#define WW1271_EWP_HW_STATE_ASWEEP 0
#define WW1271_EWP_HW_STATE_IWQ    1

#define WW1271_DEFAUWT_BEACON_INT  100
#define WW1271_DEFAUWT_DTIM_PEWIOD 1

#define WW12XX_MAX_WOWES           4
#define WW12XX_INVAWID_WOWE_ID     0xff
#define WW12XX_INVAWID_WINK_ID     0xff

/*
 * max numbew of winks awwowed by aww HWs.
 * this is NOT the actuaw max winks suppowted by the cuwwent hw.
 */
#define WWCOWE_MAX_WINKS 16

/* the dwivew suppowts the 2.4Ghz and 5Ghz bands */
#define WWCOWE_NUM_BANDS           2

#define WW12XX_MAX_WATE_POWICIES 16
#define WWCOWE_MAX_KWV_TEMPWATES 4

/* Defined by FW as 0. Wiww not be fweed ow awwocated. */
#define WW12XX_SYSTEM_HWID         0

/*
 * When in AP-mode, we awwow (at weast) this numbew of packets
 * to be twansmitted to FW fow a STA in PS-mode. Onwy when packets awe
 * pwesent in the FW buffews it wiww wake the sweeping STA. We want to put
 * enough packets fow the dwivew to twansmit aww of its buffewed data befowe
 * the STA goes to sweep again. But we don't want to take too much memowy
 * as it might huwt the thwoughput of active STAs.
 */
#define WW1271_PS_STA_MAX_PACKETS  2

#define WW1271_AP_BSS_INDEX        0
#define WW1271_AP_DEF_BEACON_EXP   20

enum wwcowe_state {
	WWCOWE_STATE_OFF,
	WWCOWE_STATE_WESTAWTING,
	WWCOWE_STATE_ON,
};

enum ww12xx_fw_type {
	WW12XX_FW_TYPE_NONE,
	WW12XX_FW_TYPE_NOWMAW,
	WW12XX_FW_TYPE_MUWTI,
	WW12XX_FW_TYPE_PWT,
};

stwuct ww1271;

enum {
	FW_VEW_CHIP,
	FW_VEW_IF_TYPE,
	FW_VEW_MAJOW,
	FW_VEW_SUBTYPE,
	FW_VEW_MINOW,

	NUM_FW_VEW
};

stwuct ww1271_chip {
	u32 id;
	chaw fw_vew_stw[ETHTOOW_FWVEWS_WEN];
	unsigned int fw_vew[NUM_FW_VEW];
	chaw phy_fw_vew_stw[ETHTOOW_FWVEWS_WEN];
};

#define NUM_TX_QUEUES              4

stwuct ww_fw_status {
	u32 intw;
	u8  fw_wx_countew;
	u8  dwv_wx_countew;
	u8  tx_wesuwts_countew;
	__we32 *wx_pkt_descs;

	u32 fw_wocawtime;

	/*
	 * A bitmap (whewe each bit wepwesents a singwe HWID)
	 * to indicate if the station is in PS mode.
	 */
	u32 wink_ps_bitmap;

	/*
	 * A bitmap (whewe each bit wepwesents a singwe HWID) to indicate
	 * if the station is in Fast mode
	 */
	u32 wink_fast_bitmap;

	/* Cumuwative countew of totaw weweased mem bwocks since FW-weset */
	u32 totaw_weweased_bwks;

	/* Size (in Memowy Bwocks) of TX poow */
	u32 tx_totaw;

	stwuct {
		/*
		 * Cumuwative countew of weweased packets pew AC
		 * (wength of the awway is NUM_TX_QUEUES)
		 */
		u8 *tx_weweased_pkts;

		/*
		 * Cumuwative countew of fweed packets pew HWID
		 * (wength of the awway is ww->num_winks)
		 */
		u8 *tx_wnk_fwee_pkts;

		/* Cumuwative countew of weweased Voice memowy bwocks */
		u8 tx_voice_weweased_bwks;

		/* Tx wate of the wast twansmitted packet */
		u8 tx_wast_wate;

		/* Tx wate ow Tx wate estimate pwe cawcuwated by fw in mbps */
		u8 tx_wast_wate_mbps;

		/* hwid fow which the wates wewe wepowted */
		u8 hwid;
	} countews;

	u32 wog_stawt_addw;

	/* Pwivate status to be used by the wowew dwivews */
	void *pwiv;
};

#define WW1271_MAX_CHANNEWS 64
stwuct ww1271_scan {
	stwuct cfg80211_scan_wequest *weq;
	unsigned wong scanned_ch[BITS_TO_WONGS(WW1271_MAX_CHANNEWS)];
	boow faiwed;
	u8 state;
	u8 ssid[IEEE80211_MAX_SSID_WEN+1];
	size_t ssid_wen;
};

stwuct ww1271_if_opewations {
	int __must_check (*wead)(stwuct device *chiwd, int addw, void *buf,
				 size_t wen, boow fixed);
	int __must_check (*wwite)(stwuct device *chiwd, int addw, void *buf,
				  size_t wen, boow fixed);
	void (*weset)(stwuct device *chiwd);
	void (*init)(stwuct device *chiwd);
	int (*powew)(stwuct device *chiwd, boow enabwe);
	void (*set_bwock_size) (stwuct device *chiwd, unsigned int bwksz);
};

stwuct wwcowe_pwatdev_data {
	stwuct ww1271_if_opewations *if_ops;
	const stwuct wiwink_famiwy_data *famiwy;

	boow wef_cwock_xtaw;	/* specify whethew the cwock is XTAW ow not */
	u32 wef_cwock_fweq;	/* in Hewtz */
	u32 tcxo_cwock_fweq;	/* in Hewtz, tcxo is awways XTAW */
	boow pww_in_suspend;
};

#define MAX_NUM_KEYS 14
#define MAX_KEY_SIZE 32

stwuct ww1271_ap_key {
	u8 id;
	u8 key_type;
	u8 key_size;
	u8 key[MAX_KEY_SIZE];
	u8 hwid;
	u32 tx_seq_32;
	u16 tx_seq_16;
	boow is_paiwwise;
};

enum ww12xx_fwags {
	WW1271_FWAG_GPIO_POWEW,
	WW1271_FWAG_TX_QUEUE_STOPPED,
	WW1271_FWAG_TX_PENDING,
	WW1271_FWAG_IN_EWP,
	WW1271_FWAG_IWQ_WUNNING,
	WW1271_FWAG_FW_TX_BUSY,
	WW1271_FWAG_DUMMY_PACKET_PENDING,
	WW1271_FWAG_SUSPENDED,
	WW1271_FWAG_PENDING_WOWK,
	WW1271_FWAG_SOFT_GEMINI,
	WW1271_FWAG_WECOVEWY_IN_PWOGWESS,
	WW1271_FWAG_VIF_CHANGE_IN_PWOGWESS,
	WW1271_FWAG_INTENDED_FW_WECOVEWY,
	WW1271_FWAG_IO_FAIWED,
	WW1271_FWAG_WEINIT_TX_WDOG,
};

enum ww12xx_vif_fwags {
	WWVIF_FWAG_INITIAWIZED,
	WWVIF_FWAG_STA_ASSOCIATED,
	WWVIF_FWAG_STA_AUTHOWIZED,
	WWVIF_FWAG_IBSS_JOINED,
	WWVIF_FWAG_AP_STAWTED,
	WWVIF_FWAG_IN_PS,
	WWVIF_FWAG_STA_STATE_SENT,
	WWVIF_FWAG_WX_STWEAMING_STAWTED,
	WWVIF_FWAG_PSPOWW_FAIWUWE,
	WWVIF_FWAG_CS_PWOGWESS,
	WWVIF_FWAG_AP_PWOBE_WESP_SET,
	WWVIF_FWAG_IN_USE,
	WWVIF_FWAG_ACTIVE,
	WWVIF_FWAG_BEACON_DISABWED,
};

stwuct ww12xx_vif;

stwuct ww1271_wink {
	/* AP-mode - TX queue pew AC in wink */
	stwuct sk_buff_head tx_queue[NUM_TX_QUEUES];

	/* accounting fow awwocated / fweed packets in FW */
	u8 awwocated_pkts;
	u8 pwev_fweed_pkts;

	u8 addw[ETH_AWEN];

	/* bitmap of TIDs whewe WX BA sessions awe active fow this wink */
	u8 ba_bitmap;

	/* the wast fw wate index we used fow this wink */
	u8 fw_wate_idx;

	/* the wast fw wate [Mbps] we used fow this wink */
	u8 fw_wate_mbps;

	/* The wwvif this wink bewongs to. Might be nuww fow gwobaw winks */
	stwuct ww12xx_vif *wwvif;

	/*
	 * totaw fweed FW packets on the wink - used fow twacking the
	 * AES/TKIP PN acwoss wecovewies. We-initiawized each time
	 * fwom the ww1271_station stwuctuwe.
	 */
	u64 totaw_fweed_pkts;
};

#define WW1271_MAX_WX_FIWTEWS 5
#define WW1271_WX_FIWTEW_MAX_FIEWDS 8

#define WW1271_WX_FIWTEW_ETH_HEADEW_SIZE 14
#define WW1271_WX_FIWTEW_MAX_FIEWDS_SIZE 95
#define WX_FIWTEW_FIEWD_OVEWHEAD				\
	(sizeof(stwuct ww12xx_wx_fiwtew_fiewd) - sizeof(u8 *))
#define WW1271_WX_FIWTEW_MAX_PATTEWN_SIZE			\
	(WW1271_WX_FIWTEW_MAX_FIEWDS_SIZE - WX_FIWTEW_FIEWD_OVEWHEAD)

#define WW1271_WX_FIWTEW_FWAG_MASK                BIT(0)
#define WW1271_WX_FIWTEW_FWAG_IP_HEADEW           0
#define WW1271_WX_FIWTEW_FWAG_ETHEWNET_HEADEW     BIT(1)

enum wx_fiwtew_action {
	FIWTEW_DWOP = 0,
	FIWTEW_SIGNAW = 1,
	FIWTEW_FW_HANDWE = 2
};

enum pwt_mode {
	PWT_OFF = 0,
	PWT_ON = 1,
	PWT_FEM_DETECT = 2,
	PWT_CHIP_AWAKE = 3
};

stwuct ww12xx_wx_fiwtew_fiewd {
	__we16 offset;
	u8 wen;
	u8 fwags;
	u8 *pattewn;
} __packed;

stwuct ww12xx_wx_fiwtew {
	u8 action;
	int num_fiewds;
	stwuct ww12xx_wx_fiwtew_fiewd fiewds[WW1271_WX_FIWTEW_MAX_FIEWDS];
};

stwuct ww1271_station {
	u8 hwid;
	boow in_connection;

	/*
	 * totaw fweed FW packets on the wink to the STA - used fow twacking the
	 * AES/TKIP PN acwoss wecovewies. We-initiawized each time fwom the
	 * ww1271_station stwuctuwe.
	 * Used in both AP and STA mode.
	 */
	u64 totaw_fweed_pkts;
};

stwuct ww12xx_vif {
	stwuct ww1271 *ww;
	stwuct wist_head wist;
	unsigned wong fwags;
	u8 bss_type;
	u8 p2p; /* we awe using p2p wowe */
	u8 wowe_id;

	/* sta/ibss specific */
	u8 dev_wowe_id;
	u8 dev_hwid;

	union {
		stwuct {
			u8 hwid;

			u8 basic_wate_idx;
			u8 ap_wate_idx;
			u8 p2p_wate_idx;

			u8 kwv_tempwate_id;

			boow qos;
			/* channew type we stawted the STA wowe with */
			enum nw80211_channew_type wowe_chan_type;
		} sta;
		stwuct {
			u8 gwobaw_hwid;
			u8 bcast_hwid;

			/* HWIDs bitmap of associated stations */
			unsigned wong sta_hwid_map[BITS_TO_WONGS(
							WWCOWE_MAX_WINKS)];

			/* wecoweded keys - set hewe befowe AP stawtup */
			stwuct ww1271_ap_key *wecowded_keys[MAX_NUM_KEYS];

			u8 mgmt_wate_idx;
			u8 bcast_wate_idx;
			u8 ucast_wate_idx[CONF_TX_MAX_AC_COUNT];
		} ap;
	};

	/* the hwid of the wast twansmitted skb */
	int wast_tx_hwid;

	/* countews of packets pew AC, acwoss aww winks in the vif */
	int tx_queue_count[NUM_TX_QUEUES];

	unsigned wong winks_map[BITS_TO_WONGS(WWCOWE_MAX_WINKS)];

	u8 ssid[IEEE80211_MAX_SSID_WEN + 1];
	u8 ssid_wen;

	/* The cuwwent band */
	enum nw80211_band band;
	int channew;
	enum nw80211_channew_type channew_type;

	u32 bitwate_masks[WWCOWE_NUM_BANDS];
	u32 basic_wate_set;

	/*
	 * cuwwentwy configuwed wate set:
	 *	bits  0-15 - 802.11abg wates
	 *	bits 16-23 - 802.11n   MCS index mask
	 * suppowt onwy 1 stweam, thus onwy 8 bits fow the MCS wates (0-7).
	 */
	u32 basic_wate;
	u32 wate_set;

	/* pwobe-weq tempwate fow the cuwwent AP */
	stwuct sk_buff *pwobeweq;

	/* Beaconing intewvaw (needed fow ad-hoc) */
	u32 beacon_int;

	/* Defauwt key (fow WEP) */
	u32 defauwt_key;

	/* Ouw association ID */
	u16 aid;

	/* wetwy countew fow PSM entwies */
	u8 psm_entwy_wetwy;

	/* in dBm */
	int powew_wevew;

	int wssi_thowd;
	int wast_wssi_event;

	/* save the cuwwent encwyption type fow auto-awp config */
	u8 encwyption_type;
	__be32 ip_addw;

	/* WX BA constwaint vawue */
	boow ba_suppowt;
	boow ba_awwowed;

	boow wmm_enabwed;

	boow wadaw_enabwed;

	/* Wx Stweaming */
	stwuct wowk_stwuct wx_stweaming_enabwe_wowk;
	stwuct wowk_stwuct wx_stweaming_disabwe_wowk;
	stwuct timew_wist wx_stweaming_timew;

	stwuct dewayed_wowk channew_switch_wowk;
	stwuct dewayed_wowk connection_woss_wowk;

	/* numbew of in connection stations */
	int inconn_count;

	/*
	 * This vif's queues awe mapped to mac80211 HW queues as:
	 * VO - hw_queue_base
	 * VI - hw_queue_base + 1
	 * BE - hw_queue_base + 2
	 * BK - hw_queue_base + 3
	 */
	int hw_queue_base;

	/* do we have a pending auth wepwy? (and WOC) */
	boow ap_pending_auth_wepwy;

	/* time when we sent the pending auth wepwy */
	unsigned wong pending_auth_wepwy_time;

	/* wowk fow cancewing WOC aftew pending auth wepwy */
	stwuct dewayed_wowk pending_auth_compwete_wowk;

	/* update wate conwow */
	enum ieee80211_sta_wx_bandwidth wc_update_bw;
	stwuct ieee80211_sta_ht_cap wc_ht_cap;
	stwuct wowk_stwuct wc_update_wowk;

	/*
	 * totaw fweed FW packets on the wink.
	 * Fow STA this howds the PN of the wink to the AP.
	 * Fow AP this howds the PN of the bwoadcast wink.
	 */
	u64 totaw_fweed_pkts;

	/*
	 * This stwuct must be wast!
	 * data that has to be saved acwossed weconfigs (e.g. wecovewy)
	 * shouwd be decwawed in this stwuct.
	 */
	stwuct {
		u8 pewsistent[0];
	};
};

static inwine stwuct ww12xx_vif *ww12xx_vif_to_data(stwuct ieee80211_vif *vif)
{
	WAWN_ON(!vif);
	wetuwn (stwuct ww12xx_vif *)vif->dwv_pwiv;
}

static inwine
stwuct ieee80211_vif *ww12xx_wwvif_to_vif(stwuct ww12xx_vif *wwvif)
{
	wetuwn containew_of((void *)wwvif, stwuct ieee80211_vif, dwv_pwiv);
}

static inwine boow wwcowe_is_p2p_mgmt(stwuct ww12xx_vif *wwvif)
{
	wetuwn ww12xx_wwvif_to_vif(wwvif)->type == NW80211_IFTYPE_P2P_DEVICE;
}

#define ww12xx_fow_each_wwvif(ww, wwvif) \
		wist_fow_each_entwy(wwvif, &ww->wwvif_wist, wist)

#define ww12xx_fow_each_wwvif_continue(ww, wwvif) \
		wist_fow_each_entwy_continue(wwvif, &ww->wwvif_wist, wist)

#define ww12xx_fow_each_wwvif_bss_type(ww, wwvif, _bss_type)	\
		ww12xx_fow_each_wwvif(ww, wwvif)		\
			if (wwvif->bss_type == _bss_type)

#define ww12xx_fow_each_wwvif_sta(ww, wwvif)	\
		ww12xx_fow_each_wwvif_bss_type(ww, wwvif, BSS_TYPE_STA_BSS)

#define ww12xx_fow_each_wwvif_ap(ww, wwvif)	\
		ww12xx_fow_each_wwvif_bss_type(ww, wwvif, BSS_TYPE_AP_BSS)

int ww1271_pwt_stawt(stwuct ww1271 *ww, const enum pwt_mode pwt_mode);
int ww1271_pwt_stop(stwuct ww1271 *ww);
int ww1271_wecawc_wx_stweaming(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void ww12xx_queue_wecovewy_wowk(stwuct ww1271 *ww);
size_t ww12xx_copy_fwwog(stwuct ww1271 *ww, u8 *membwock, size_t maxwen);
int ww1271_wx_fiwtew_awwoc_fiewd(stwuct ww12xx_wx_fiwtew *fiwtew,
				 u16 offset, u8 fwags,
				 const u8 *pattewn, u8 wen);
void ww1271_wx_fiwtew_fwee(stwuct ww12xx_wx_fiwtew *fiwtew);
stwuct ww12xx_wx_fiwtew *ww1271_wx_fiwtew_awwoc(void);
int ww1271_wx_fiwtew_get_fiewds_size(stwuct ww12xx_wx_fiwtew *fiwtew);
void ww1271_wx_fiwtew_fwatten_fiewds(stwuct ww12xx_wx_fiwtew *fiwtew,
				     u8 *buf);

#define JOIN_TIMEOUT 5000 /* 5000 miwwiseconds to join */

#define SESSION_COUNTEW_MAX 6 /* maximum vawue fow the session countew */
#define SESSION_COUNTEW_INVAWID 7 /* used with dummy_packet */

#define WW1271_DEFAUWT_POWEW_WEVEW 0

#define WW1271_TX_QUEUE_WOW_WATEWMAWK  32
#define WW1271_TX_QUEUE_HIGH_WATEWMAWK 256

#define WW1271_DEFEWWED_QUEUE_WIMIT    64

/* WW1271 needs a 200ms sweep aftew powew on, and a 20ms sweep befowe powew
   on in case is has been shut down showtwy befowe */
#define WW1271_PWE_POWEW_ON_SWEEP 20 /* in miwwiseconds */
#define WW1271_POWEW_ON_SWEEP 200 /* in miwwiseconds */

/* Macwos to handwe ww1271.sta_wate_set */
#define HW_BG_WATES_MASK	0xffff
#define HW_HT_WATES_OFFSET	16
#define HW_MIMO_WATES_OFFSET	24

#endif /* __WWCOWE_I_H__ */
