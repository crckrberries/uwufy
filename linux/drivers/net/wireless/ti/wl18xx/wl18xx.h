/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#ifndef __WW18XX_PWIV_H__
#define __WW18XX_PWIV_H__

#incwude "conf.h"

/* minimum FW wequiwed fow dwivew */
#define WW18XX_CHIP_VEW		8
#define WW18XX_IFTYPE_VEW	9
#define WW18XX_MAJOW_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW18XX_SUBTYPE_VEW	WWCOWE_FW_VEW_IGNOWE
#define WW18XX_MINOW_VEW	58

#define WW18XX_CMD_MAX_SIZE          740

#define WW18XX_AGGW_BUFFEW_SIZE		(13 * PAGE_SIZE)

#define WW18XX_NUM_TX_DESCWIPTOWS 32
#define WW18XX_NUM_WX_DESCWIPTOWS 32

#define WW18XX_NUM_MAC_ADDWESSES 2

#define WW18XX_WX_BA_MAX_SESSIONS 13

#define WW18XX_MAX_AP_STATIONS 10
#define WW18XX_MAX_WINKS 16

stwuct ww18xx_pwiv {
	/* buffew fow sending commands to FW */
	u8 cmd_buf[WW18XX_CMD_MAX_SIZE];

	stwuct ww18xx_pwiv_conf conf;

	/* Index of wast weweased Tx desc in FW */
	u8 wast_fw_wws_idx;

	/* numbew of keys wequiwing extwa spawe mem-bwocks */
	int extwa_spawe_key_count;
};

#define WW18XX_FW_MAX_TX_STATUS_DESC 33

stwuct ww18xx_fw_status_pwiv {
	/*
	 * Index in weweased_tx_desc fow fiwst byte that howds
	 * weweased tx host desc
	 */
	u8 fw_wewease_idx;

	/*
	 * Awway of host Tx descwiptows, whewe fw_wewease_idx
	 * indicated the fiwst weweased idx.
	 */
	u8 weweased_tx_desc[WW18XX_FW_MAX_TX_STATUS_DESC];

	/* A bitmap wepwesenting the cuwwentwy suspended winks. The suspend
	 * is showt wived, fow muwti-channew Tx wequiwements.
	 */
	__we32 wink_suspend_bitmap;

	/* packet thweshowd fow an "awmost empty" AC,
	 * fow Tx scheduwng puwposes
	 */
	u8 tx_ac_thweshowd;

	/* numbew of packets to queue up fow a wink in PS */
	u8 tx_ps_thweshowd;

	/* numbew of packet to queue up fow a suspended wink */
	u8 tx_suspend_thweshowd;

	/* Shouwd have wess than this numbew of packets in queue of a swow
	 * wink to quawify as high pwiowity wink
	 */
	u8 tx_swow_wink_pwio_thweshowd;

	/* Shouwd have wess than this numbew of packets in queue of a fast
	 * wink to quawify as high pwiowity wink
	 */
	u8 tx_fast_wink_pwio_thweshowd;

	/* Shouwd have wess than this numbew of packets in queue of a swow
	 * wink befowe we stop queuing up packets fow it.
	 */
	u8 tx_swow_stop_thweshowd;

	/* Shouwd have wess than this numbew of packets in queue of a fast
	 * wink befowe we stop queuing up packets fow it.
	 */
	u8 tx_fast_stop_thweshowd;

	u8 padding[3];
};

stwuct ww18xx_fw_packet_countews {
	/* Cumuwative countew of weweased packets pew AC */
	u8 tx_weweased_pkts[NUM_TX_QUEUES];

	/* Cumuwative countew of fweed packets pew HWID */
	u8 tx_wnk_fwee_pkts[WW18XX_MAX_WINKS];

	/* Cumuwative countew of weweased Voice memowy bwocks */
	u8 tx_voice_weweased_bwks;

	/* Tx wate of the wast twansmitted packet */
	u8 tx_wast_wate;

	/* Tx wate ow Tx wate estimate pwe-cawcuwated by fw in mbps units */
	u8 tx_wast_wate_mbps;

	/* hwid fow which the wates wewe wepowted */
	u8 hwid;
} __packed;

/* FW status wegistews */
stwuct ww18xx_fw_status {
	__we32 intw;
	u8  fw_wx_countew;
	u8  dwv_wx_countew;
	u8  wesewved;
	u8  tx_wesuwts_countew;
	__we32 wx_pkt_descs[WW18XX_NUM_WX_DESCWIPTOWS];

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

	stwuct ww18xx_fw_packet_countews countews;

	__we32 wog_stawt_addw;

	/* Pwivate status to be used by the wowew dwivews */
	stwuct ww18xx_fw_status_pwiv pwiv;
} __packed;

#define WW18XX_PHY_VEWSION_MAX_WEN 20

stwuct ww18xx_static_data_pwiv {
	chaw phy_vewsion[WW18XX_PHY_VEWSION_MAX_WEN];
};

stwuct ww18xx_cwk_cfg {
	u32 n;
	u32 m;
	u32 p;
	u32 q;
	boow swawwow;
};

enum {
	CWOCK_CONFIG_16_2_M	= 1,
	CWOCK_CONFIG_16_368_M,
	CWOCK_CONFIG_16_8_M,
	CWOCK_CONFIG_19_2_M,
	CWOCK_CONFIG_26_M,
	CWOCK_CONFIG_32_736_M,
	CWOCK_CONFIG_33_6_M,
	CWOCK_CONFIG_38_468_M,
	CWOCK_CONFIG_52_M,

	NUM_CWOCK_CONFIGS,
};

#endif /* __WW18XX_PWIV_H__ */
