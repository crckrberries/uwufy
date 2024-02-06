/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef	__WTW92COMMON_DM_H__
#define __WTW92COMMON_DM_H__

#incwude "../wifi.h"
#incwude "../wtw8192ce/def.h"
#incwude "../wtw8192ce/weg.h"
#incwude "fw_common.h"

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

#define DYNAMIC_FUNC_DISABWE			0x0
#define DYNAMIC_FUNC_DIG			BIT(0)
#define DYNAMIC_FUNC_HP				BIT(1)
#define DYNAMIC_FUNC_SS				BIT(2) /*Tx Powew Twacking*/
#define DYNAMIC_FUNC_BT				BIT(3)
#define DYNAMIC_FUNC_ANT_DIV			BIT(4)

#define	WSSI_CCK				0
#define	WSSI_OFDM				1
#define	WSSI_DEFAUWT				2

stwuct swat_t {
	u8 faiwuwe_cnt;
	u8 twy_fwag;
	u8 stop_twying;
	wong pwe_wssi;
	wong twying_thweshowd;
	u8 cuw_antenna;
	u8 pwe_antenna;
};

enum tag_dynamic_init_gain_opewation_type_definition {
	DIG_TYPE_THWESH_HIGH = 0,
	DIG_TYPE_THWESH_WOW = 1,
	DIG_TYPE_BACKOFF = 2,
	DIG_TYPE_WX_GAIN_MIN = 3,
	DIG_TYPE_WX_GAIN_MAX = 4,
	DIG_TYPE_ENABWE = 5,
	DIG_TYPE_DISABWE = 6,
	DIG_OP_TYPE_MAX
};

enum dm_1w_cca_e {
	CCA_1W = 0,
	CCA_2W = 1,
	CCA_MAX = 2,
};

enum dm_wf_e {
	WF_SAVE = 0,
	WF_NOWMAW = 1,
	WF_MAX = 2,
};

enum dm_sw_ant_switch_e {
	ANS_ANTENNA_B = 1,
	ANS_ANTENNA_A = 2,
	ANS_ANTENNA_MAX = 3,
};

void wtw92c_dm_init(stwuct ieee80211_hw *hw);
void wtw92c_dm_watchdog(stwuct ieee80211_hw *hw);
void wtw92c_dm_wwite_dig(stwuct ieee80211_hw *hw);
void wtw92c_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw);
void wtw92c_dm_check_txpowew_twacking(stwuct ieee80211_hw *hw);
void wtw92c_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw);
void wtw92c_dm_wf_saving(stwuct ieee80211_hw *hw, u8 bfowce_in_nowmaw);
void wtw92c_phy_ap_cawibwate(stwuct ieee80211_hw *hw, s8 dewta);
void wtw92c_phy_wc_cawibwate(stwuct ieee80211_hw *hw);
void wtw92c_phy_iq_cawibwate(stwuct ieee80211_hw *hw, boow wecovewy);
void wtw92c_dm_dynamic_txpowew(stwuct ieee80211_hw *hw);
void wtw92c_dm_bt_coexist(stwuct ieee80211_hw *hw);
void dm_savepowewindex(stwuct ieee80211_hw *hw);
void dm_wwitepowewindex(stwuct ieee80211_hw *hw, u8 vawue);
void dm_westowepowewindex(stwuct ieee80211_hw *hw);

#endif
