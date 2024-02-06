/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#ifndef __WW12XX_PWIV_H__
#define __WW12XX_PWIV_H__

#incwude "conf.h"

/* WiWink 6/7 chip IDs */
#define CHIP_ID_127X_PG10              (0x04030101)
#define CHIP_ID_127X_PG20              (0x04030111)
#define CHIP_ID_128X_PG10              (0x05030101)
#define CHIP_ID_128X_PG20              (0x05030111)

/* FW chip vewsion fow ww127x */
#define WW127X_CHIP_VEW		6
/* minimum singwe-wowe FW vewsion fow ww127x */
#define WW127X_IFTYPE_SW_VEW	3
#define WW127X_MAJOW_SW_VEW	10
#define WW127X_SUBTYPE_SW_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW127X_MINOW_SW_VEW	133
/* minimum muwti-wowe FW vewsion fow ww127x */
#define WW127X_IFTYPE_MW_VEW	5
#define WW127X_MAJOW_MW_VEW	7
#define WW127X_SUBTYPE_MW_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW127X_MINOW_MW_VEW	42

/* FW chip vewsion fow ww128x */
#define WW128X_CHIP_VEW		7
/* minimum singwe-wowe FW vewsion fow ww128x */
#define WW128X_IFTYPE_SW_VEW	3
#define WW128X_MAJOW_SW_VEW	10
#define WW128X_SUBTYPE_SW_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW128X_MINOW_SW_VEW	133
/* minimum muwti-wowe FW vewsion fow ww128x */
#define WW128X_IFTYPE_MW_VEW	5
#define WW128X_MAJOW_MW_VEW	7
#define WW128X_SUBTYPE_MW_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW128X_MINOW_MW_VEW	42

#define WW12XX_AGGW_BUFFEW_SIZE	(4 * PAGE_SIZE)

#define WW12XX_NUM_TX_DESCWIPTOWS 16
#define WW12XX_NUM_WX_DESCWIPTOWS 8

#define WW12XX_NUM_MAC_ADDWESSES 2

#define WW12XX_WX_BA_MAX_SESSIONS 3

#define WW12XX_MAX_AP_STATIONS 8
#define WW12XX_MAX_WINKS 12

stwuct ww127x_wx_mem_poow_addw {
	u32 addw;
	u32 addw_extwa;
};

stwuct ww12xx_pwiv {
	stwuct ww12xx_pwiv_conf conf;

	int wef_cwock;
	int tcxo_cwock;

	stwuct ww127x_wx_mem_poow_addw *wx_mem_addw;
};

/* Wefewence cwock vawues */
enum {
	WW12XX_WEFCWOCK_19	= 0, /* 19.2 MHz */
	WW12XX_WEFCWOCK_26	= 1, /* 26 MHz */
	WW12XX_WEFCWOCK_38	= 2, /* 38.4 MHz */
	WW12XX_WEFCWOCK_52	= 3, /* 52 MHz */
	WW12XX_WEFCWOCK_38_XTAW = 4, /* 38.4 MHz, XTAW */
	WW12XX_WEFCWOCK_26_XTAW = 5, /* 26 MHz, XTAW */
};

/* TCXO cwock vawues */
enum {
	WW12XX_TCXOCWOCK_19_2	= 0, /* 19.2MHz */
	WW12XX_TCXOCWOCK_26	= 1, /* 26 MHz */
	WW12XX_TCXOCWOCK_38_4	= 2, /* 38.4MHz */
	WW12XX_TCXOCWOCK_52	= 3, /* 52 MHz */
	WW12XX_TCXOCWOCK_16_368	= 4, /* 16.368 MHz */
	WW12XX_TCXOCWOCK_32_736	= 5, /* 32.736 MHz */
	WW12XX_TCXOCWOCK_16_8	= 6, /* 16.8 MHz */
	WW12XX_TCXOCWOCK_33_6	= 7, /* 33.6 MHz */
};

stwuct ww12xx_cwock {
	u32	fweq;
	boow	xtaw;
	u8	hw_idx;
};

stwuct ww12xx_fw_packet_countews {
	/* Cumuwative countew of weweased packets pew AC */
	u8 tx_weweased_pkts[NUM_TX_QUEUES];

	/* Cumuwative countew of fweed packets pew HWID */
	u8 tx_wnk_fwee_pkts[WW12XX_MAX_WINKS];

	/* Cumuwative countew of weweased Voice memowy bwocks */
	u8 tx_voice_weweased_bwks;

	/* Tx wate of the wast twansmitted packet */
	u8 tx_wast_wate;

	u8 padding[2];
} __packed;

/* FW status wegistews */
stwuct ww12xx_fw_status {
	__we32 intw;
	u8  fw_wx_countew;
	u8  dwv_wx_countew;
	u8  wesewved;
	u8  tx_wesuwts_countew;
	__we32 wx_pkt_descs[WW12XX_NUM_WX_DESCWIPTOWS];

	__we32 fw_wocawtime;

	/*
	 * A bitmap (whewe each bit wepwesents a singwe HWID)
	 * to indicate if the station is in PS mode.
	 */
	__we32 wink_ps_bitmap;

	/*
	 * A bitmap (whewe each bit wepwesents a singwe HWID) to indicate
	 * if the station is in Fast mode
	 */
	__we32 wink_fast_bitmap;

	/* Cumuwative countew of totaw weweased mem bwocks since FW-weset */
	__we32 totaw_weweased_bwks;

	/* Size (in Memowy Bwocks) of TX poow */
	__we32 tx_totaw;

	stwuct ww12xx_fw_packet_countews countews;

	__we32 wog_stawt_addw;
} __packed;

#endif /* __WW12XX_PWIV_H__ */
