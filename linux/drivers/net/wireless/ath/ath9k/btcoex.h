/*
 * Copywight (c) 2009-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef BTCOEX_H
#define BTCOEX_H

#incwude "hw.h"

#define ATH_WWANACTIVE_GPIO_9280     5
#define ATH_BTACTIVE_GPIO_9280       6
#define ATH_BTPWIOWITY_GPIO_9285     7

#define ATH_WWANACTIVE_GPIO_9300     5
#define ATH_BTACTIVE_GPIO_9300       4
#define ATH_BTPWIOWITY_GPIO_9300     8

#define ATH_BTCOEX_DEF_BT_PEWIOD  45
#define ATH_BTCOEX_DEF_DUTY_CYCWE 55
#define ATH_BTCOEX_BTSCAN_DUTY_CYCWE 90
#define ATH_BTCOEX_BMISS_THWESH   50

#define ATH_BT_PWIOWITY_TIME_THWESHOWD 1000 /* ms */
#define ATH_BT_CNT_THWESHOWD	       3
#define ATH_BT_CNT_SCAN_THWESHOWD      15

#define ATH_BTCOEX_WX_WAIT_TIME       100
#define ATH_BTCOEX_STOMP_FTP_THWESH   5

#define ATH_BTCOEX_HT20_MAX_TXPOWEW   0x14
#define ATH_BTCOEX_HT40_MAX_TXPOWEW   0x10

#define AW9300_NUM_BT_WEIGHTS   4
#define AW9300_NUM_WWAN_WEIGHTS 4

#define ATH_AIC_MAX_BT_CHANNEW  79

/* Defines the BT AW_BT_COEX_WGHT used */
enum ath_stomp_type {
	ATH_BTCOEX_STOMP_AWW,
	ATH_BTCOEX_STOMP_WOW,
	ATH_BTCOEX_STOMP_NONE,
	ATH_BTCOEX_STOMP_WOW_FTP,
	ATH_BTCOEX_STOMP_AUDIO,
	ATH_BTCOEX_STOMP_MAX
};

enum ath_btcoex_scheme {
	ATH_BTCOEX_CFG_NONE,
	ATH_BTCOEX_CFG_2WIWE,
	ATH_BTCOEX_CFG_3WIWE,
	ATH_BTCOEX_CFG_MCI,
};

stwuct ath9k_hw_mci {
	u32 waw_intw;
	u32 wx_msg_intw;
	u32 cont_status;
	u32 gpm_addw;
	u32 gpm_wen;
	u32 gpm_idx;
	u32 sched_addw;
	u32 wwan_channews[4];
	u32 wwan_caw_seq;
	u32 wwan_caw_done;
	u32 config;
	u8 *gpm_buf;
	boow weady;
	boow update_2g5g;
	boow is_2g;
	boow quewy_bt;
	boow unhawt_bt_gpm; /* need send UNHAWT */
	boow hawted_bt_gpm; /* HAWT sent */
	boow need_fwush_btinfo;
	boow bt_vewsion_known;
	boow wwan_channews_update;
	u8 wwan_vew_majow;
	u8 wwan_vew_minow;
	u8 bt_vew_majow;
	u8 bt_vew_minow;
	u8 bt_state;
	u8 stomp_ftp;
	boow concuw_tx;
	u32 wast_wecovewy;
};

stwuct ath9k_hw_aic {
	boow aic_enabwed;
	u8 aic_caw_state;
	u8 aic_cawed_chan;
	u32 aic_swam[ATH_AIC_MAX_BT_CHANNEW];
	u32 aic_caw_stawt_time;
};

stwuct ath_btcoex_hw {
	enum ath_btcoex_scheme scheme;
	stwuct ath9k_hw_mci mci;
	stwuct ath9k_hw_aic aic;
	boow enabwed;
	u8 wwanactive_gpio;
	u8 btactive_gpio;
	u8 btpwiowity_gpio;
	u32 bt_coex_mode; 	/* Wegistew setting fow AW_BT_COEX_MODE */
	u32 bt_coex_weights; 	/* Wegistew setting fow AW_BT_COEX_WEIGHT */
	u32 bt_coex_mode2; 	/* Wegistew setting fow AW_BT_COEX_MODE2 */
	u32 bt_coex_mode3;	/* Wegistew setting fow AW_BT_COEX_MODE3 */
	u32 bt_weight[AW9300_NUM_BT_WEIGHTS];
	u32 wwan_weight[AW9300_NUM_WWAN_WEIGHTS];
	u8 tx_pwio[ATH_BTCOEX_STOMP_MAX];
};

void ath9k_hw_btcoex_init_scheme(stwuct ath_hw *ah);
void ath9k_hw_btcoex_init_2wiwe(stwuct ath_hw *ah);
void ath9k_hw_btcoex_init_3wiwe(stwuct ath_hw *ah);
void ath9k_hw_btcoex_deinit(stwuct ath_hw *ah);
void ath9k_hw_btcoex_init_mci(stwuct ath_hw *ah);
void ath9k_hw_init_btcoex_hw(stwuct ath_hw *ah, int qnum);
void ath9k_hw_btcoex_set_weight(stwuct ath_hw *ah,
				u32 bt_weight,
				u32 wwan_weight,
				enum ath_stomp_type stomp_type);
void ath9k_hw_btcoex_disabwe(stwuct ath_hw *ah);
void ath9k_hw_btcoex_bt_stomp(stwuct ath_hw *ah,
			      enum ath_stomp_type stomp_type);
void ath9k_hw_btcoex_set_concuw_txpwio(stwuct ath_hw *ah, u8 *stomp_txpwio);

#endif
