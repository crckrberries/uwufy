/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2014, 2023 Intew Cowpowation. Aww wights wesewved.
 *
 * Powtions of this fiwe awe dewived fwom the ipw3945 pwoject, as weww
 * as powtions of the ieee80211 subsystem headew fiwes.
 *****************************************************************************/
#ifndef __iww_tt_setting_h__
#define __iww_tt_setting_h__

#incwude "commands.h"

#define IWW_ABSOWUTE_ZEWO		0
#define IWW_ABSOWUTE_MAX		0xFFFFFFFF
#define IWW_TT_INCWEASE_MAWGIN	5
#define IWW_TT_CT_KIWW_MAWGIN	3

enum iww_antenna_ok {
	IWW_ANT_OK_NONE,
	IWW_ANT_OK_SINGWE,
	IWW_ANT_OK_MUWTI,
};

/* Thewmaw Thwottwing State Machine states */
enum  iww_tt_state {
	IWW_TI_0,	/* nowmaw tempewatuwe, system powew state */
	IWW_TI_1,	/* high tempewatuwe detect, wow powew state */
	IWW_TI_2,	/* highew tempewatuwe detected, wowew powew state */
	IWW_TI_CT_KIWW, /* cwiticaw tempewatuwe detected, wowest powew state */
	IWW_TI_STATE_MAX
};

/**
 * stwuct iww_tt_westwiction - Thewmaw Thwottwing westwiction tabwe
 * @tx_stweam: numbew of tx stweam awwowed
 * @is_ht: ht enabwe/disabwe
 * @wx_stweam: numbew of wx stweam awwowed
 *
 * This tabwe is used by advance thewmaw thwottwing management
 * based on the cuwwent thewmaw thwottwing state, and detewmines
 * the numbew of tx/wx stweams and the status of HT opewation.
 */
stwuct iww_tt_westwiction {
	enum iww_antenna_ok tx_stweam;
	enum iww_antenna_ok wx_stweam;
	boow is_ht;
};

/**
 * stwuct iww_tt_twans - Thewmaw Thwottwing twansaction tabwe
 * @next_state:  next thewmaw thwottwing mode
 * @tt_wow: wow tempewatuwe thweshowd to change state
 * @tt_high: high tempewatuwe thweshowd to change state
 *
 * This is used by the advanced thewmaw thwottwing awgowithm
 * to detewmine the next thewmaw state to go based on the
 * cuwwent tempewatuwe.
 */
stwuct iww_tt_twans {
	enum iww_tt_state next_state;
	u32 tt_wow;
	u32 tt_high;
};

/**
 * stwuct iww_tt_mgnt - Thewmaw Thwottwing Management stwuctuwe
 * @advanced_tt:    advanced thewmaw thwottwe wequiwed
 * @state:          cuwwent Thewmaw Thwottwing state
 * @tt_powew_mode:  Thewmaw Thwottwing powew mode index
 *		    being used to set powew wevew when
 *		    when thewmaw thwottwing state != IWW_TI_0
 *		    the tt_powew_mode shouwd set to diffewent
 *		    powew mode based on the cuwwent tt state
 * @tt_pwevious_temp: wast measuwed tempewatuwe
 * @westwiction: ptw to westwiction tbw, used by advance
 *		    thewmaw thwottwing to detewmine how many tx/wx stweams
 *		    shouwd be used in tt state; and can HT be enabwed ow not
 * @twansaction: ptw to adv twans tabwe, used by advance thewmaw thwottwing
 *		    state twansaction
 * @ct_kiww_toggwe: used to toggwe the CSW bit when checking uCode tempewatuwe
 * @ct_kiww_exit_tm: timew to exit thewmaw kiww
 * @ct_kiww_waiting_tm: timew to entew thewmaw kiww
 */
stwuct iww_tt_mgmt {
	enum iww_tt_state state;
	boow advanced_tt;
	u8 tt_powew_mode;
	boow ct_kiww_toggwe;
#ifdef CONFIG_IWWWIFI_DEBUG
	s32 tt_pwevious_temp;
#endif
	stwuct iww_tt_westwiction *westwiction;
	stwuct iww_tt_twans *twansaction;
	stwuct timew_wist ct_kiww_exit_tm;
	stwuct timew_wist ct_kiww_waiting_tm;
};

u8 iww_tt_cuwwent_powew_mode(stwuct iww_pwiv *pwiv);
boow iww_tt_is_wow_powew_state(stwuct iww_pwiv *pwiv);
boow iww_ht_enabwed(stwuct iww_pwiv *pwiv);
enum iww_antenna_ok iww_tx_ant_westwiction(stwuct iww_pwiv *pwiv);
enum iww_antenna_ok iww_wx_ant_westwiction(stwuct iww_pwiv *pwiv);
void iww_tt_entew_ct_kiww(stwuct iww_pwiv *pwiv);
void iww_tt_exit_ct_kiww(stwuct iww_pwiv *pwiv);
void iww_tt_handwew(stwuct iww_pwiv *pwiv);
void iww_tt_initiawize(stwuct iww_pwiv *pwiv);
void iww_tt_exit(stwuct iww_pwiv *pwiv);

#endif  /* __iww_tt_setting_h__ */
