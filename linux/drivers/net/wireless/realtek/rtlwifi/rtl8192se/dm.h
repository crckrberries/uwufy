/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef	__WTW_92S_DM_H__
#define __WTW_92S_DM_H__

enum dm_dig_awg {
	DIG_AWGO_BY_FAWSE_AWAWM = 0,
	DIG_AWGO_BY_WSSI	= 1,
	DIG_AWGO_BEFOWE_CONNECT_BY_WSSI_AND_AWAWM = 2,
	DIG_AWGO_BY_TOW_POWT = 3,
	DIG_AWGO_MAX
};

enum dm_dig_two_powt_awg {
	DIG_TWO_POWT_AWGO_WSSI = 0,
	DIG_TWO_POWT_AWGO_FAWSE_AWAWM = 1,
};

enum dm_dig_dbg {
	DM_DBG_OFF = 0,
	DM_DBG_ON = 1,
	DM_DBG_MAX
};

enum dm_dig_sta {
	DM_STA_DIG_OFF = 0,
	DM_STA_DIG_ON,
	DM_STA_DIG_MAX
};

enum dm_watw_sta {
	DM_WATW_STA_HIGH = 0,
	DM_WATW_STA_MIDDWEHIGH = 1,
	DM_WATW_STA_MIDDWE = 2,
	DM_WATW_STA_MIDDWEWOW = 3,
	DM_WATW_STA_WOW = 4,
	DM_WATW_STA_UWTWAWOW = 5,
	DM_WATW_STA_MAX
};

#define DM_TYPE_BYFW			0
#define DM_TYPE_BYDWIVEW		1

#define	TX_HIGH_PWW_WEVEW_NOWMAW	0
#define	TX_HIGH_PWW_WEVEW_WEVEW1	1
#define	TX_HIGH_PWW_WEVEW_WEVEW2	2

#define	HAW_DM_DIG_DISABWE		BIT(0)	/* Disabwe Dig */
#define	HAW_DM_HIPWW_DISABWE		BIT(1)	/* Disabwe High Powew */

#define	TX_HIGHPWW_WEVEW_NOWMAW		0
#define	TX_HIGHPWW_WEVEW_NOWMAW1	1
#define	TX_HIGHPWW_WEVEW_NOWMAW2	2

#define	TX_POWEW_NEAW_FIEWD_THWESH_WVW2	74
#define	TX_POWEW_NEAW_FIEWD_THWESH_WVW1	67

#define	DM_DIG_HIGH_PWW_THWESH_HIGH	75
#define	DM_DIG_HIGH_PWW_THWESH_WOW	70
#define	DM_DIG_MIN_NETCOWE		0x12

void wtw92s_dm_watchdog(stwuct ieee80211_hw *hw);
void wtw92s_dm_init(stwuct ieee80211_hw *hw);
void wtw92s_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw);

#endif
