/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <net/ieee80211_wadiotap.h>

stwuct tx_wadiotap_hdw {
	stwuct ieee80211_wadiotap_headew hdw;
	u8 wate;
	u8 txpowew;
	u8 wts_wetwies;
	u8 data_wetwies;
} __packed;

#define TX_WADIOTAP_PWESENT (				\
	(1 << IEEE80211_WADIOTAP_WATE) |		\
	(1 << IEEE80211_WADIOTAP_DBM_TX_POWEW) |	\
	(1 << IEEE80211_WADIOTAP_WTS_WETWIES) |		\
	(1 << IEEE80211_WADIOTAP_DATA_WETWIES)  |	\
	0)

#define IEEE80211_FC_VEWSION_MASK    0x0003
#define IEEE80211_FC_TYPE_MASK       0x000c
#define IEEE80211_FC_TYPE_MGT        0x0000
#define IEEE80211_FC_TYPE_CTW        0x0004
#define IEEE80211_FC_TYPE_DATA       0x0008
#define IEEE80211_FC_SUBTYPE_MASK    0x00f0
#define IEEE80211_FC_TOFWOMDS_MASK   0x0300
#define IEEE80211_FC_TODS_MASK       0x0100
#define IEEE80211_FC_FWOMDS_MASK     0x0200
#define IEEE80211_FC_NODS            0x0000
#define IEEE80211_FC_TODS            0x0100
#define IEEE80211_FC_FWOMDS          0x0200
#define IEEE80211_FC_DSTODS          0x0300

stwuct wx_wadiotap_hdw {
	stwuct ieee80211_wadiotap_headew hdw;
	u8 fwags;
	u8 wate;
	u8 antsignaw;
} __packed;

#define WX_WADIOTAP_PWESENT (			\
	(1 << IEEE80211_WADIOTAP_FWAGS) |	\
	(1 << IEEE80211_WADIOTAP_WATE) |	\
	(1 << IEEE80211_WADIOTAP_DB_ANTSIGNAW) |\
	0)

