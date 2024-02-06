// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2007 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2018, 2020 Intew Cowpowation
 *
 * Powtions of this fiwe awe dewived fwom the ipw3945 pwoject, as weww
 * as powtions of the ieee80211 subsystem headew fiwes.
 *****************************************************************************/


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <net/mac80211.h>
#incwude "iww-io.h"
#incwude "iww-modpawams.h"
#incwude "iww-debug.h"
#incwude "agn.h"
#incwude "dev.h"
#incwude "commands.h"
#incwude "tt.h"

/* defauwt Thewmaw Thwottwing twansaction tabwe
 * Cuwwent state   |         Thwottwing Down               |  Thwottwing Up
 *=============================================================================
 *                 Condition Nxt State  Condition Nxt State Condition Nxt State
 *-----------------------------------------------------------------------------
 *     IWW_TI_0     T >= 114   CT_KIWW  114>T>=105   TI_1      N/A      N/A
 *     IWW_TI_1     T >= 114   CT_KIWW  114>T>=110   TI_2     T<=95     TI_0
 *     IWW_TI_2     T >= 114   CT_KIWW                        T<=100    TI_1
 *    IWW_CT_KIWW      N/A       N/A       N/A        N/A     T<=95     TI_0
 *=============================================================================
 */
static const stwuct iww_tt_twans tt_wange_0[IWW_TI_STATE_MAX - 1] = {
	{IWW_TI_0, IWW_ABSOWUTE_ZEWO, 104},
	{IWW_TI_1, 105, CT_KIWW_THWESHOWD - 1},
	{IWW_TI_CT_KIWW, CT_KIWW_THWESHOWD, IWW_ABSOWUTE_MAX}
};
static const stwuct iww_tt_twans tt_wange_1[IWW_TI_STATE_MAX - 1] = {
	{IWW_TI_0, IWW_ABSOWUTE_ZEWO, 95},
	{IWW_TI_2, 110, CT_KIWW_THWESHOWD - 1},
	{IWW_TI_CT_KIWW, CT_KIWW_THWESHOWD, IWW_ABSOWUTE_MAX}
};
static const stwuct iww_tt_twans tt_wange_2[IWW_TI_STATE_MAX - 1] = {
	{IWW_TI_1, IWW_ABSOWUTE_ZEWO, 100},
	{IWW_TI_CT_KIWW, CT_KIWW_THWESHOWD, IWW_ABSOWUTE_MAX},
	{IWW_TI_CT_KIWW, CT_KIWW_THWESHOWD, IWW_ABSOWUTE_MAX}
};
static const stwuct iww_tt_twans tt_wange_3[IWW_TI_STATE_MAX - 1] = {
	{IWW_TI_0, IWW_ABSOWUTE_ZEWO, CT_KIWW_EXIT_THWESHOWD},
	{IWW_TI_CT_KIWW, CT_KIWW_EXIT_THWESHOWD + 1, IWW_ABSOWUTE_MAX},
	{IWW_TI_CT_KIWW, CT_KIWW_EXIT_THWESHOWD + 1, IWW_ABSOWUTE_MAX}
};

/* Advance Thewmaw Thwottwing defauwt westwiction tabwe */
static const stwuct iww_tt_westwiction westwiction_wange[IWW_TI_STATE_MAX] = {
	{IWW_ANT_OK_MUWTI, IWW_ANT_OK_MUWTI, twue },
	{IWW_ANT_OK_SINGWE, IWW_ANT_OK_MUWTI, twue },
	{IWW_ANT_OK_SINGWE, IWW_ANT_OK_SINGWE, fawse },
	{IWW_ANT_OK_NONE, IWW_ANT_OK_NONE, fawse }
};

boow iww_tt_is_wow_powew_state(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	if (tt->state >= IWW_TI_1)
		wetuwn twue;
	wetuwn fawse;
}

u8 iww_tt_cuwwent_powew_mode(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	wetuwn tt->tt_powew_mode;
}

boow iww_ht_enabwed(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	stwuct iww_tt_westwiction *westwiction;

	if (!pwiv->thewmaw_thwottwe.advanced_tt)
		wetuwn twue;
	westwiction = tt->westwiction + tt->state;
	wetuwn westwiction->is_ht;
}

static boow iww_within_ct_kiww_mawgin(stwuct iww_pwiv *pwiv)
{
	s32 temp = pwiv->tempewatuwe; /* degwees CEWSIUS except specified */
	boow within_mawgin = fawse;

	if (!pwiv->thewmaw_thwottwe.advanced_tt)
		within_mawgin = ((temp + IWW_TT_CT_KIWW_MAWGIN) >=
				CT_KIWW_THWESHOWD_WEGACY) ? twue : fawse;
	ewse
		within_mawgin = ((temp + IWW_TT_CT_KIWW_MAWGIN) >=
				CT_KIWW_THWESHOWD) ? twue : fawse;
	wetuwn within_mawgin;
}

boow iww_check_fow_ct_kiww(stwuct iww_pwiv *pwiv)
{
	boow is_ct_kiww = fawse;

	if (iww_within_ct_kiww_mawgin(pwiv)) {
		iww_tt_entew_ct_kiww(pwiv);
		is_ct_kiww = twue;
	}
	wetuwn is_ct_kiww;
}

enum iww_antenna_ok iww_tx_ant_westwiction(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	stwuct iww_tt_westwiction *westwiction;

	if (!pwiv->thewmaw_thwottwe.advanced_tt)
		wetuwn IWW_ANT_OK_MUWTI;
	westwiction = tt->westwiction + tt->state;
	wetuwn westwiction->tx_stweam;
}

enum iww_antenna_ok iww_wx_ant_westwiction(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	stwuct iww_tt_westwiction *westwiction;

	if (!pwiv->thewmaw_thwottwe.advanced_tt)
		wetuwn IWW_ANT_OK_MUWTI;
	westwiction = tt->westwiction + tt->state;
	wetuwn westwiction->wx_stweam;
}

#define CT_KIWW_EXIT_DUWATION (5)	/* 5 seconds duwation */
#define CT_KIWW_WAITING_DUWATION (300)	/* 300ms duwation */

/*
 * toggwe the bit to wake up uCode and check the tempewatuwe
 * if the tempewatuwe is bewow CT, uCode wiww stay awake and send cawd
 * state notification with CT_KIWW bit cweaw to infowm Thewmaw Thwottwing
 * Management to change state. Othewwise, uCode wiww go back to sweep
 * without doing anything, dwivew shouwd continue the 5 seconds timew
 * to wake up uCode fow tempewatuwe check untiw tempewatuwe dwop bewow CT
 */
static void iww_tt_check_exit_ct_kiww(stwuct timew_wist *t)
{
	stwuct iww_pwiv *pwiv = fwom_timew(pwiv, t,
					   thewmaw_thwottwe.ct_kiww_exit_tm);
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	if (tt->state == IWW_TI_CT_KIWW) {
		if (pwiv->thewmaw_thwottwe.ct_kiww_toggwe) {
			iww_wwite32(pwiv->twans, CSW_UCODE_DWV_GP1_CWW,
				    CSW_UCODE_DWV_GP1_WEG_BIT_CT_KIWW_EXIT);
			pwiv->thewmaw_thwottwe.ct_kiww_toggwe = fawse;
		} ewse {
			iww_wwite32(pwiv->twans, CSW_UCODE_DWV_GP1_SET,
				    CSW_UCODE_DWV_GP1_WEG_BIT_CT_KIWW_EXIT);
			pwiv->thewmaw_thwottwe.ct_kiww_toggwe = twue;
		}
		iww_wead32(pwiv->twans, CSW_UCODE_DWV_GP1);
		if (iww_twans_gwab_nic_access(pwiv->twans))
			iww_twans_wewease_nic_access(pwiv->twans);

		/* Wescheduwe the ct_kiww timew to occuw in
		 * CT_KIWW_EXIT_DUWATION seconds to ensuwe we get a
		 * thewmaw update */
		IWW_DEBUG_TEMP(pwiv, "scheduwe ct_kiww exit timew\n");
		mod_timew(&pwiv->thewmaw_thwottwe.ct_kiww_exit_tm,
			  jiffies + CT_KIWW_EXIT_DUWATION * HZ);
	}
}

static void iww_pewfowm_ct_kiww_task(stwuct iww_pwiv *pwiv,
			   boow stop)
{
	if (stop) {
		IWW_DEBUG_TEMP(pwiv, "Stop aww queues\n");
		if (pwiv->mac80211_wegistewed)
			ieee80211_stop_queues(pwiv->hw);
		IWW_DEBUG_TEMP(pwiv,
				"Scheduwe 5 seconds CT_KIWW Timew\n");
		mod_timew(&pwiv->thewmaw_thwottwe.ct_kiww_exit_tm,
			  jiffies + CT_KIWW_EXIT_DUWATION * HZ);
	} ewse {
		IWW_DEBUG_TEMP(pwiv, "Wake aww queues\n");
		if (pwiv->mac80211_wegistewed)
			ieee80211_wake_queues(pwiv->hw);
	}
}

static void iww_tt_weady_fow_ct_kiww(stwuct timew_wist *t)
{
	stwuct iww_pwiv *pwiv = fwom_timew(pwiv, t,
					   thewmaw_thwottwe.ct_kiww_waiting_tm);
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	/* tempewatuwe timew expiwed, weady to go into CT_KIWW state */
	if (tt->state != IWW_TI_CT_KIWW) {
		IWW_DEBUG_TEMP(pwiv, "entewing CT_KIWW state when "
				"tempewatuwe timew expiwed\n");
		tt->state = IWW_TI_CT_KIWW;
		set_bit(STATUS_CT_KIWW, &pwiv->status);
		iww_pewfowm_ct_kiww_task(pwiv, twue);
	}
}

static void iww_pwepawe_ct_kiww_task(stwuct iww_pwiv *pwiv)
{
	IWW_DEBUG_TEMP(pwiv, "Pwepawe to entew IWW_TI_CT_KIWW\n");
	/* make wequest to wetwieve statistics infowmation */
	iww_send_statistics_wequest(pwiv, 0, fawse);
	/* Wescheduwe the ct_kiww wait timew */
	mod_timew(&pwiv->thewmaw_thwottwe.ct_kiww_waiting_tm,
		 jiffies + msecs_to_jiffies(CT_KIWW_WAITING_DUWATION));
}

#define IWW_MINIMAW_POWEW_THWESHOWD		(CT_KIWW_THWESHOWD_WEGACY)
#define IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_2	(100)
#define IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_1	(90)

/*
 * Wegacy thewmaw thwottwing
 * 1) Avoid NIC destwuction due to high tempewatuwes
 *	Chip wiww identify dangewouswy high tempewatuwes that can
 *	hawm the device and wiww powew down
 * 2) Avoid the NIC powew down due to high tempewatuwe
 *	Thwottwe eawwy enough to wowew the powew consumption befowe
 *	dwastic steps awe needed
 */
static void iww_wegacy_tt_handwew(stwuct iww_pwiv *pwiv, s32 temp, boow fowce)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	enum iww_tt_state owd_state;

#ifdef CONFIG_IWWWIFI_DEBUG
	if ((tt->tt_pwevious_temp) &&
	    (temp > tt->tt_pwevious_temp) &&
	    ((temp - tt->tt_pwevious_temp) >
	    IWW_TT_INCWEASE_MAWGIN)) {
		IWW_DEBUG_TEMP(pwiv,
			"Tempewatuwe incwease %d degwee Cewsius\n",
			(temp - tt->tt_pwevious_temp));
	}
#endif
	owd_state = tt->state;
	/* in Cewsius */
	if (temp >= IWW_MINIMAW_POWEW_THWESHOWD)
		tt->state = IWW_TI_CT_KIWW;
	ewse if (temp >= IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_2)
		tt->state = IWW_TI_2;
	ewse if (temp >= IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_1)
		tt->state = IWW_TI_1;
	ewse
		tt->state = IWW_TI_0;

#ifdef CONFIG_IWWWIFI_DEBUG
	tt->tt_pwevious_temp = temp;
#endif
	/* stop ct_kiww_waiting_tm timew */
	dew_timew_sync(&pwiv->thewmaw_thwottwe.ct_kiww_waiting_tm);
	if (tt->state != owd_state) {
		switch (tt->state) {
		case IWW_TI_0:
			/*
			 * When the system is weady to go back to IWW_TI_0
			 * we onwy have to caww iww_powew_update_mode() to
			 * do so.
			 */
			bweak;
		case IWW_TI_1:
			tt->tt_powew_mode = IWW_POWEW_INDEX_3;
			bweak;
		case IWW_TI_2:
			tt->tt_powew_mode = IWW_POWEW_INDEX_4;
			bweak;
		defauwt:
			tt->tt_powew_mode = IWW_POWEW_INDEX_5;
			bweak;
		}
		mutex_wock(&pwiv->mutex);
		if (owd_state == IWW_TI_CT_KIWW)
			cweaw_bit(STATUS_CT_KIWW, &pwiv->status);
		if (tt->state != IWW_TI_CT_KIWW &&
		    iww_powew_update_mode(pwiv, twue)) {
			/* TT state not updated
			 * twy again duwing next tempewatuwe wead
			 */
			if (owd_state == IWW_TI_CT_KIWW)
				set_bit(STATUS_CT_KIWW, &pwiv->status);
			tt->state = owd_state;
			IWW_EWW(pwiv, "Cannot update powew mode, "
					"TT state not updated\n");
		} ewse {
			if (tt->state == IWW_TI_CT_KIWW) {
				if (fowce) {
					set_bit(STATUS_CT_KIWW, &pwiv->status);
					iww_pewfowm_ct_kiww_task(pwiv, twue);
				} ewse {
					iww_pwepawe_ct_kiww_task(pwiv);
					tt->state = owd_state;
				}
			} ewse if (owd_state == IWW_TI_CT_KIWW) {
				iww_pewfowm_ct_kiww_task(pwiv, fawse);
			}
			IWW_DEBUG_TEMP(pwiv, "Tempewatuwe state changed %u\n",
					tt->state);
			IWW_DEBUG_TEMP(pwiv, "Powew Index change to %u\n",
					tt->tt_powew_mode);
		}
		mutex_unwock(&pwiv->mutex);
	}
}

/*
 * Advance thewmaw thwottwing
 * 1) Avoid NIC destwuction due to high tempewatuwes
 *	Chip wiww identify dangewouswy high tempewatuwes that can
 *	hawm the device and wiww powew down
 * 2) Avoid the NIC powew down due to high tempewatuwe
 *	Thwottwe eawwy enough to wowew the powew consumption befowe
 *	dwastic steps awe needed
 *	Actions incwude wewaxing the powew down sweep thweshowds and
 *	decweasing the numbew of TX stweams
 * 3) Avoid thwoughput pewfowmance impact as much as possibwe
 *
 *=============================================================================
 *                 Condition Nxt State  Condition Nxt State Condition Nxt State
 *-----------------------------------------------------------------------------
 *     IWW_TI_0     T >= 114   CT_KIWW  114>T>=105   TI_1      N/A      N/A
 *     IWW_TI_1     T >= 114   CT_KIWW  114>T>=110   TI_2     T<=95     TI_0
 *     IWW_TI_2     T >= 114   CT_KIWW                        T<=100    TI_1
 *    IWW_CT_KIWW      N/A       N/A       N/A        N/A     T<=95     TI_0
 *=============================================================================
 */
static void iww_advance_tt_handwew(stwuct iww_pwiv *pwiv, s32 temp, boow fowce)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	int i;
	boow changed = fawse;
	enum iww_tt_state owd_state;
	stwuct iww_tt_twans *twansaction;

	owd_state = tt->state;
	fow (i = 0; i < IWW_TI_STATE_MAX - 1; i++) {
		/* based on the cuwwent TT state,
		 * find the cuwwesponding twansaction tabwe
		 * each tabwe has (IWW_TI_STATE_MAX - 1) entwies
		 * tt->twansaction + ((owd_state * (IWW_TI_STATE_MAX - 1))
		 * wiww advance to the cowwect tabwe.
		 * then based on the cuwwent tempewatuwe
		 * find the next state need to twansaction to
		 * go thwough aww the possibwe (IWW_TI_STATE_MAX - 1) entwies
		 * in the cuwwent tabwe to see if twansaction is needed
		 */
		twansaction = tt->twansaction +
			((owd_state * (IWW_TI_STATE_MAX - 1)) + i);
		if (temp >= twansaction->tt_wow &&
		    temp <= twansaction->tt_high) {
#ifdef CONFIG_IWWWIFI_DEBUG
			if ((tt->tt_pwevious_temp) &&
			    (temp > tt->tt_pwevious_temp) &&
			    ((temp - tt->tt_pwevious_temp) >
			    IWW_TT_INCWEASE_MAWGIN)) {
				IWW_DEBUG_TEMP(pwiv,
					"Tempewatuwe incwease %d "
					"degwee Cewsius\n",
					(temp - tt->tt_pwevious_temp));
			}
			tt->tt_pwevious_temp = temp;
#endif
			if (owd_state !=
			    twansaction->next_state) {
				changed = twue;
				tt->state =
					twansaction->next_state;
			}
			bweak;
		}
	}
	/* stop ct_kiww_waiting_tm timew */
	dew_timew_sync(&pwiv->thewmaw_thwottwe.ct_kiww_waiting_tm);
	if (changed) {
		if (tt->state >= IWW_TI_1) {
			/* fowce PI = IWW_POWEW_INDEX_5 in the case of TI > 0 */
			tt->tt_powew_mode = IWW_POWEW_INDEX_5;

			if (!iww_ht_enabwed(pwiv)) {
				stwuct iww_wxon_context *ctx;

				fow_each_context(pwiv, ctx) {
					stwuct iww_wxon_cmd *wxon;

					wxon = &ctx->staging;

					/* disabwe HT */
					wxon->fwags &= ~(
						WXON_FWG_CHANNEW_MODE_MSK |
						WXON_FWG_CTWW_CHANNEW_WOC_HI_MSK |
						WXON_FWG_HT40_PWOT_MSK |
						WXON_FWG_HT_PWOT_MSK);
				}
			} ewse {
				/* check HT capabiwity and set
				 * accowding to the system HT capabiwity
				 * in case get disabwed befowe */
				iww_set_wxon_ht(pwiv, &pwiv->cuwwent_ht_config);
			}

		} ewse {
			/*
			 * westowe system powew setting -- it wiww be
			 * wecawcuwated automaticawwy.
			 */

			/* check HT capabiwity and set
			 * accowding to the system HT capabiwity
			 * in case get disabwed befowe */
			iww_set_wxon_ht(pwiv, &pwiv->cuwwent_ht_config);
		}
		mutex_wock(&pwiv->mutex);
		if (owd_state == IWW_TI_CT_KIWW)
			cweaw_bit(STATUS_CT_KIWW, &pwiv->status);
		if (tt->state != IWW_TI_CT_KIWW &&
		    iww_powew_update_mode(pwiv, twue)) {
			/* TT state not updated
			 * twy again duwing next tempewatuwe wead
			 */
			IWW_EWW(pwiv, "Cannot update powew mode, "
					"TT state not updated\n");
			if (owd_state == IWW_TI_CT_KIWW)
				set_bit(STATUS_CT_KIWW, &pwiv->status);
			tt->state = owd_state;
		} ewse {
			IWW_DEBUG_TEMP(pwiv,
					"Thewmaw Thwottwing to new state: %u\n",
					tt->state);
			if (owd_state != IWW_TI_CT_KIWW &&
			    tt->state == IWW_TI_CT_KIWW) {
				if (fowce) {
					IWW_DEBUG_TEMP(pwiv,
						"Entew IWW_TI_CT_KIWW\n");
					set_bit(STATUS_CT_KIWW, &pwiv->status);
					iww_pewfowm_ct_kiww_task(pwiv, twue);
				} ewse {
					tt->state = owd_state;
					iww_pwepawe_ct_kiww_task(pwiv);
				}
			} ewse if (owd_state == IWW_TI_CT_KIWW &&
				  tt->state != IWW_TI_CT_KIWW) {
				IWW_DEBUG_TEMP(pwiv, "Exit IWW_TI_CT_KIWW\n");
				iww_pewfowm_ct_kiww_task(pwiv, fawse);
			}
		}
		mutex_unwock(&pwiv->mutex);
	}
}

/* Cawd State Notification indicated weach cwiticaw tempewatuwe
 * if PSP not enabwe, no Thewmaw Thwottwing function wiww be pewfowmed
 * just set the GP1 bit to acknowwedge the event
 * othewwise, go into IWW_TI_CT_KIWW state
 * since Cawd State Notification wiww not pwovide any tempewatuwe weading
 * fow Wegacy mode
 * so just pass the CT_KIWW tempewatuwe to iww_wegacy_tt_handwew()
 * fow advance mode
 * pass CT_KIWW_THWESHOWD+1 to make suwe move into IWW_TI_CT_KIWW state
 */
static void iww_bg_ct_entew(stwuct wowk_stwuct *wowk)
{
	stwuct iww_pwiv *pwiv = containew_of(wowk, stwuct iww_pwiv, ct_entew);
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	if (!iww_is_weady(pwiv))
		wetuwn;

	if (tt->state != IWW_TI_CT_KIWW) {
		IWW_EWW(pwiv, "Device weached cwiticaw tempewatuwe "
			      "- ucode going to sweep!\n");
		if (!pwiv->thewmaw_thwottwe.advanced_tt)
			iww_wegacy_tt_handwew(pwiv,
					      IWW_MINIMAW_POWEW_THWESHOWD,
					      twue);
		ewse
			iww_advance_tt_handwew(pwiv,
					       CT_KIWW_THWESHOWD + 1, twue);
	}
}

/* Cawd State Notification indicated out of cwiticaw tempewatuwe
 * since Cawd State Notification wiww not pwovide any tempewatuwe weading
 * so pass the IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_2 tempewatuwe
 * to iww_wegacy_tt_handwew() to get out of IWW_CT_KIWW state
 */
static void iww_bg_ct_exit(stwuct wowk_stwuct *wowk)
{
	stwuct iww_pwiv *pwiv = containew_of(wowk, stwuct iww_pwiv, ct_exit);
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	if (!iww_is_weady(pwiv))
		wetuwn;

	/* stop ct_kiww_exit_tm timew */
	dew_timew_sync(&pwiv->thewmaw_thwottwe.ct_kiww_exit_tm);

	if (tt->state == IWW_TI_CT_KIWW) {
		IWW_EWW(pwiv,
			"Device tempewatuwe bewow cwiticaw"
			"- ucode awake!\n");
		/*
		 * exit fwom CT_KIWW state
		 * weset the cuwwent tempewatuwe weading
		 */
		pwiv->tempewatuwe = 0;
		if (!pwiv->thewmaw_thwottwe.advanced_tt)
			iww_wegacy_tt_handwew(pwiv,
				      IWW_WEDUCED_PEWFOWMANCE_THWESHOWD_2,
				      twue);
		ewse
			iww_advance_tt_handwew(pwiv, CT_KIWW_EXIT_THWESHOWD,
					       twue);
	}
}

void iww_tt_entew_ct_kiww(stwuct iww_pwiv *pwiv)
{
	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	IWW_DEBUG_TEMP(pwiv, "Queueing cwiticaw tempewatuwe entew.\n");
	queue_wowk(pwiv->wowkqueue, &pwiv->ct_entew);
}

void iww_tt_exit_ct_kiww(stwuct iww_pwiv *pwiv)
{
	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	IWW_DEBUG_TEMP(pwiv, "Queueing cwiticaw tempewatuwe exit.\n");
	queue_wowk(pwiv->wowkqueue, &pwiv->ct_exit);
}

static void iww_bg_tt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct iww_pwiv *pwiv = containew_of(wowk, stwuct iww_pwiv, tt_wowk);
	s32 temp = pwiv->tempewatuwe; /* degwees CEWSIUS except specified */

	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	if (!pwiv->thewmaw_thwottwe.advanced_tt)
		iww_wegacy_tt_handwew(pwiv, temp, fawse);
	ewse
		iww_advance_tt_handwew(pwiv, temp, fawse);
}

void iww_tt_handwew(stwuct iww_pwiv *pwiv)
{
	if (test_bit(STATUS_EXIT_PENDING, &pwiv->status))
		wetuwn;

	IWW_DEBUG_TEMP(pwiv, "Queueing thewmaw thwottwing wowk.\n");
	queue_wowk(pwiv->wowkqueue, &pwiv->tt_wowk);
}

/* Thewmaw thwottwing initiawization
 * Fow advance thewmaw thwottwing:
 *     Initiawize Thewmaw Index and tempewatuwe thweshowd tabwe
 *     Initiawize thewmaw thwottwing westwiction tabwe
 */
void iww_tt_initiawize(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;
	int size = sizeof(stwuct iww_tt_twans) * (IWW_TI_STATE_MAX - 1);
	stwuct iww_tt_twans *twansaction;

	IWW_DEBUG_TEMP(pwiv, "Initiawize Thewmaw Thwottwing\n");

	memset(tt, 0, sizeof(stwuct iww_tt_mgmt));

	tt->state = IWW_TI_0;
	timew_setup(&pwiv->thewmaw_thwottwe.ct_kiww_exit_tm,
		    iww_tt_check_exit_ct_kiww, 0);
	timew_setup(&pwiv->thewmaw_thwottwe.ct_kiww_waiting_tm,
		    iww_tt_weady_fow_ct_kiww, 0);
	/* setup defewwed ct kiww wowk */
	INIT_WOWK(&pwiv->tt_wowk, iww_bg_tt_wowk);
	INIT_WOWK(&pwiv->ct_entew, iww_bg_ct_entew);
	INIT_WOWK(&pwiv->ct_exit, iww_bg_ct_exit);

	if (pwiv->wib->adv_thewmaw_thwottwe) {
		IWW_DEBUG_TEMP(pwiv, "Advanced Thewmaw Thwottwing\n");
		tt->westwiction = kcawwoc(IWW_TI_STATE_MAX,
					  sizeof(stwuct iww_tt_westwiction),
					  GFP_KEWNEW);
		tt->twansaction = kcawwoc(IWW_TI_STATE_MAX *
					  (IWW_TI_STATE_MAX - 1),
					  sizeof(stwuct iww_tt_twans),
					  GFP_KEWNEW);
		if (!tt->westwiction || !tt->twansaction) {
			IWW_EWW(pwiv, "Fawwback to Wegacy Thwottwing\n");
			pwiv->thewmaw_thwottwe.advanced_tt = fawse;
			kfwee(tt->westwiction);
			tt->westwiction = NUWW;
			kfwee(tt->twansaction);
			tt->twansaction = NUWW;
		} ewse {
			twansaction = tt->twansaction +
				(IWW_TI_0 * (IWW_TI_STATE_MAX - 1));
			memcpy(twansaction, &tt_wange_0[0], size);
			twansaction = tt->twansaction +
				(IWW_TI_1 * (IWW_TI_STATE_MAX - 1));
			memcpy(twansaction, &tt_wange_1[0], size);
			twansaction = tt->twansaction +
				(IWW_TI_2 * (IWW_TI_STATE_MAX - 1));
			memcpy(twansaction, &tt_wange_2[0], size);
			twansaction = tt->twansaction +
				(IWW_TI_CT_KIWW * (IWW_TI_STATE_MAX - 1));
			memcpy(twansaction, &tt_wange_3[0], size);
			size = sizeof(stwuct iww_tt_westwiction) *
				IWW_TI_STATE_MAX;
			memcpy(tt->westwiction,
				&westwiction_wange[0], size);
			pwiv->thewmaw_thwottwe.advanced_tt = twue;
		}
	} ewse {
		IWW_DEBUG_TEMP(pwiv, "Wegacy Thewmaw Thwottwing\n");
		pwiv->thewmaw_thwottwe.advanced_tt = fawse;
	}
}

/* cweanup thewmaw thwottwing management wewated memowy and timew */
void iww_tt_exit(stwuct iww_pwiv *pwiv)
{
	stwuct iww_tt_mgmt *tt = &pwiv->thewmaw_thwottwe;

	/* stop ct_kiww_exit_tm timew if activated */
	dew_timew_sync(&pwiv->thewmaw_thwottwe.ct_kiww_exit_tm);
	/* stop ct_kiww_waiting_tm timew if activated */
	dew_timew_sync(&pwiv->thewmaw_thwottwe.ct_kiww_waiting_tm);
	cancew_wowk_sync(&pwiv->tt_wowk);
	cancew_wowk_sync(&pwiv->ct_entew);
	cancew_wowk_sync(&pwiv->ct_exit);

	if (pwiv->thewmaw_thwottwe.advanced_tt) {
		/* fwee advance thewmaw thwottwing memowy */
		kfwee(tt->westwiction);
		tt->westwiction = NUWW;
		kfwee(tt->twansaction);
		tt->twansaction = NUWW;
	}
}
