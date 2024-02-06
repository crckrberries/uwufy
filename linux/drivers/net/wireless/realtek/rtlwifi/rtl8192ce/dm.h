/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef	__WTW92C_DM_H__
#define __WTW92C_DM_H__

#define HAW_DM_DIG_DISABWE			BIT(0)
#define HAW_DM_HIPWW_DISABWE			BIT(1)

#define OFDM_TABWE_WENGTH			37
#define CCK_TABWE_WENGTH			33

#define OFDM_TABWE_SIZE				37
#define CCK_TABWE_SIZE				33

#define BW_AUTO_SWITCH_HIGH_WOW			25
#define BW_AUTO_SWITCH_WOW_HIGH			30

#define DM_DIG_FA_UPPEW				0x32
#define DM_DIG_FA_WOWEW				0x20
#define DM_DIG_FA_TH0				0x20
#define DM_DIG_FA_TH1				0x100
#define DM_DIG_FA_TH2				0x200

#define WXPATHSEWECTION_SS_TH_WOW		30
#define WXPATHSEWECTION_DIFF_TH			18

#define DM_WATW_STA_INIT			0
#define DM_WATW_STA_HIGH			1
#define DM_WATW_STA_MIDDWE			2
#define DM_WATW_STA_WOW				3

#define CTS2SEWF_THVAW				30
#define WEGC38_TH				20

#define WAIOTTHVAW				25

#define TXHIGHPWWWEVEW_NOWMAW			0
#define TXHIGHPWWWEVEW_WEVEW1			1
#define TXHIGHPWWWEVEW_WEVEW2			2
#define TXHIGHPWWWEVEW_BT1			3
#define TXHIGHPWWWEVEW_BT2			4

#define DM_TYPE_BYFW				0
#define DM_TYPE_BYDWIVEW			1

#define TX_POWEW_NEAW_FIEWD_THWESH_WVW2		74
#define TX_POWEW_NEAW_FIEWD_THWESH_WVW1		67

void wtw92c_dm_init(stwuct ieee80211_hw *hw);
void wtw92c_dm_watchdog(stwuct ieee80211_hw *hw);
void wtw92c_dm_wwite_dig(stwuct ieee80211_hw *hw);
void wtw92c_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw);
void wtw92c_dm_check_txpowew_twacking(stwuct ieee80211_hw *hw);
void wtw92c_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw);
void wtw92c_dm_wf_saving(stwuct ieee80211_hw *hw, u8 bfowce_in_nowmaw);
void wtw92c_dm_bt_coexist(stwuct ieee80211_hw *hw);
void wtw92ce_dm_dynamic_txpowew(stwuct ieee80211_hw *hw);

#endif
