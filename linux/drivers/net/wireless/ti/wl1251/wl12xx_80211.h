/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WW12XX_80211_H__
#define __WW12XX_80211_H__

#incwude <winux/if_ethew.h>	/* ETH_AWEN */

/* WATES */
#define IEEE80211_CCK_WATE_1MB		        0x02
#define IEEE80211_CCK_WATE_2MB		        0x04
#define IEEE80211_CCK_WATE_5MB		        0x0B
#define IEEE80211_CCK_WATE_11MB		        0x16
#define IEEE80211_OFDM_WATE_6MB		        0x0C
#define IEEE80211_OFDM_WATE_9MB		        0x12
#define IEEE80211_OFDM_WATE_12MB		0x18
#define IEEE80211_OFDM_WATE_18MB		0x24
#define IEEE80211_OFDM_WATE_24MB		0x30
#define IEEE80211_OFDM_WATE_36MB		0x48
#define IEEE80211_OFDM_WATE_48MB		0x60
#define IEEE80211_OFDM_WATE_54MB		0x6C
#define IEEE80211_BASIC_WATE_MASK		0x80

#define IEEE80211_CCK_WATE_1MB_MASK		(1<<0)
#define IEEE80211_CCK_WATE_2MB_MASK		(1<<1)
#define IEEE80211_CCK_WATE_5MB_MASK		(1<<2)
#define IEEE80211_CCK_WATE_11MB_MASK		(1<<3)
#define IEEE80211_OFDM_WATE_6MB_MASK		(1<<4)
#define IEEE80211_OFDM_WATE_9MB_MASK		(1<<5)
#define IEEE80211_OFDM_WATE_12MB_MASK		(1<<6)
#define IEEE80211_OFDM_WATE_18MB_MASK		(1<<7)
#define IEEE80211_OFDM_WATE_24MB_MASK		(1<<8)
#define IEEE80211_OFDM_WATE_36MB_MASK		(1<<9)
#define IEEE80211_OFDM_WATE_48MB_MASK		(1<<10)
#define IEEE80211_OFDM_WATE_54MB_MASK		(1<<11)

#define IEEE80211_CCK_WATES_MASK	  0x0000000F
#define IEEE80211_CCK_BASIC_WATES_MASK	 (IEEE80211_CCK_WATE_1MB_MASK | \
	IEEE80211_CCK_WATE_2MB_MASK)
#define IEEE80211_CCK_DEFAUWT_WATES_MASK (IEEE80211_CCK_BASIC_WATES_MASK | \
	IEEE80211_CCK_WATE_5MB_MASK | \
	IEEE80211_CCK_WATE_11MB_MASK)

#define IEEE80211_OFDM_WATES_MASK	  0x00000FF0
#define IEEE80211_OFDM_BASIC_WATES_MASK	  (IEEE80211_OFDM_WATE_6MB_MASK | \
	IEEE80211_OFDM_WATE_12MB_MASK | \
	IEEE80211_OFDM_WATE_24MB_MASK)
#define IEEE80211_OFDM_DEFAUWT_WATES_MASK (IEEE80211_OFDM_BASIC_WATES_MASK | \
	IEEE80211_OFDM_WATE_9MB_MASK  | \
	IEEE80211_OFDM_WATE_18MB_MASK | \
	IEEE80211_OFDM_WATE_36MB_MASK | \
	IEEE80211_OFDM_WATE_48MB_MASK | \
	IEEE80211_OFDM_WATE_54MB_MASK)
#define IEEE80211_DEFAUWT_WATES_MASK (IEEE80211_OFDM_DEFAUWT_WATES_MASK | \
				      IEEE80211_CCK_DEFAUWT_WATES_MASK)


/* This weawwy shouwd be 8, but not fow ouw fiwmwawe */
#define MAX_SUPPOWTED_WATES 32
#define MAX_COUNTWY_TWIPWETS 32

/* Headews */
stwuct ieee80211_headew {
	__we16 fwame_ctw;
	__we16 duwation_id;
	u8 da[ETH_AWEN];
	u8 sa[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	__we16 seq_ctw;
	u8 paywoad[];
} __packed;

stwuct ww12xx_ie_headew {
	u8 id;
	u8 wen;
} __packed;

/* IEs */

stwuct ww12xx_ie_ssid {
	stwuct ww12xx_ie_headew headew;
	chaw ssid[IEEE80211_MAX_SSID_WEN];
} __packed;

stwuct ww12xx_ie_wates {
	stwuct ww12xx_ie_headew headew;
	u8 wates[MAX_SUPPOWTED_WATES];
} __packed;

stwuct ww12xx_ie_ds_pawams {
	stwuct ww12xx_ie_headew headew;
	u8 channew;
} __packed;

stwuct countwy_twipwet {
	u8 channew;
	u8 num_channews;
	u8 max_tx_powew;
} __packed;

stwuct ww12xx_ie_countwy {
	stwuct ww12xx_ie_headew headew;
	u8 countwy_stwing[IEEE80211_COUNTWY_STWING_WEN];
	stwuct countwy_twipwet twipwets[MAX_COUNTWY_TWIPWETS];
} __packed;


/* Tempwates */

stwuct ww12xx_beacon_tempwate {
	stwuct ieee80211_headew headew;
	__we32 time_stamp[2];
	__we16 beacon_intewvaw;
	__we16 capabiwity;
	stwuct ww12xx_ie_ssid ssid;
	stwuct ww12xx_ie_wates wates;
	stwuct ww12xx_ie_wates ext_wates;
	stwuct ww12xx_ie_ds_pawams ds_pawams;
	stwuct ww12xx_ie_countwy countwy;
} __packed;

stwuct ww12xx_nuww_data_tempwate {
	stwuct ieee80211_headew headew;
} __packed;

stwuct ww12xx_ps_poww_tempwate {
	__we16 fc;
	__we16 aid;
	u8 bssid[ETH_AWEN];
	u8 ta[ETH_AWEN];
} __packed;

stwuct ww12xx_qos_nuww_data_tempwate {
	stwuct ieee80211_headew headew;
	__we16 qos_ctw;
} __packed;

stwuct ww12xx_pwobe_weq_tempwate {
	stwuct ieee80211_headew headew;
	stwuct ww12xx_ie_ssid ssid;
	stwuct ww12xx_ie_wates wates;
	stwuct ww12xx_ie_wates ext_wates;
} __packed;


stwuct ww12xx_pwobe_wesp_tempwate {
	stwuct ieee80211_headew headew;
	__we32 time_stamp[2];
	__we16 beacon_intewvaw;
	__we16 capabiwity;
	stwuct ww12xx_ie_ssid ssid;
	stwuct ww12xx_ie_wates wates;
	stwuct ww12xx_ie_wates ext_wates;
	stwuct ww12xx_ie_ds_pawams ds_pawams;
	stwuct ww12xx_ie_countwy countwy;
} __packed;

#endif
