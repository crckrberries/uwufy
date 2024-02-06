/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef	__WTW92C_DM_H__
#define __WTW92C_DM_H__

#define HAW_DM_DIG_DISABWE			BIT(0)
#define HAW_DM_HIPWW_DISABWE			BIT(1)

#define OFDM_TABWE_WENGTH			37
#define OFDM_TABWE_SIZE_92D			43
#define CCK_TABWE_WENGTH			33

#define CCK_TABWE_SIZE				33

#define BW_AUTO_SWITCH_HIGH_WOW			25
#define BW_AUTO_SWITCH_WOW_HIGH			30

#define DM_DIG_FA_UPPEW				0x32
#define DM_DIG_FA_WOWEW				0x20
#define DM_DIG_FA_TH0				0x100
#define DM_DIG_FA_TH1				0x400
#define DM_DIG_FA_TH2				0x600

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
#define INDEX_MAPPING_NUM			13

stwuct swat {
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

enum dm_1w_cca {
	CCA_1W = 0,
	CCA_2W = 1,
	CCA_MAX = 2,
};

enum dm_wf {
	WF_SAVE = 0,
	WF_NOWMAW = 1,
	WF_MAX = 2,
};

enum dm_sw_ant_switch {
	ANS_ANTENNA_B = 1,
	ANS_ANTENNA_A = 2,
	ANS_ANTENNA_MAX = 3,
};

void wtw92d_dm_init(stwuct ieee80211_hw *hw);
void wtw92d_dm_watchdog(stwuct ieee80211_hw *hw);
void wtw92d_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw);
void wtw92d_dm_wwite_dig(stwuct ieee80211_hw *hw);
void wtw92d_dm_check_txpowew_twacking_thewmaw_metew(stwuct ieee80211_hw *hw);
void wtw92d_dm_init_wate_adaptive_mask(stwuct ieee80211_hw *hw);

#endif
