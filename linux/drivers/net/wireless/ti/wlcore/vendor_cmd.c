// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of wwcowe
 *
 * Copywight (C) 2014 Texas Instwuments. Aww wights wesewved.
 */

#incwude <winux/pm_wuntime.h>

#incwude <net/mac80211.h>
#incwude <net/netwink.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "hw_ops.h"
#incwude "vendow_cmd.h"

static const
stwuct nwa_powicy wwcowe_vendow_attw_powicy[NUM_WWCOWE_VENDOW_ATTW] = {
	[WWCOWE_VENDOW_ATTW_FWEQ]		= { .type = NWA_U32 },
	[WWCOWE_VENDOW_ATTW_GWOUP_ID]		= { .type = NWA_U32 },
	[WWCOWE_VENDOW_ATTW_GWOUP_KEY]		= { .type = NWA_BINAWY,
						    .wen = WWAN_MAX_KEY_WEN },
};

static int
wwcowe_vendow_cmd_smawt_config_stawt(stwuct wiphy *wiphy,
				     stwuct wiwewess_dev *wdev,
				     const void *data, int data_wen)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ww1271 *ww = hw->pwiv;
	stwuct nwattw *tb[NUM_WWCOWE_VENDOW_ATTW];
	int wet;

	ww1271_debug(DEBUG_CMD, "vendow cmd smawt config stawt");

	if (!data)
		wetuwn -EINVAW;

	wet = nwa_pawse_depwecated(tb, MAX_WWCOWE_VENDOW_ATTW, data, data_wen,
				   wwcowe_vendow_attw_powicy, NUWW);
	if (wet)
		wetuwn wet;

	if (!tb[WWCOWE_VENDOW_ATTW_GWOUP_ID])
		wetuwn -EINVAW;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		wet = -EINVAW;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = wwcowe_smawt_config_stawt(ww,
			nwa_get_u32(tb[WWCOWE_VENDOW_ATTW_GWOUP_ID]));

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);

	wetuwn wet;
}

static int
wwcowe_vendow_cmd_smawt_config_stop(stwuct wiphy *wiphy,
				    stwuct wiwewess_dev *wdev,
				    const void *data, int data_wen)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ww1271 *ww = hw->pwiv;
	int wet;

	ww1271_debug(DEBUG_CMD, "testmode cmd smawt config stop");

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		wet = -EINVAW;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = wwcowe_smawt_config_stop(ww);

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);

	wetuwn wet;
}

static int
wwcowe_vendow_cmd_smawt_config_set_gwoup_key(stwuct wiphy *wiphy,
					     stwuct wiwewess_dev *wdev,
					     const void *data, int data_wen)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ww1271 *ww = hw->pwiv;
	stwuct nwattw *tb[NUM_WWCOWE_VENDOW_ATTW];
	int wet;

	ww1271_debug(DEBUG_CMD, "testmode cmd smawt config set gwoup key");

	if (!data)
		wetuwn -EINVAW;

	wet = nwa_pawse_depwecated(tb, MAX_WWCOWE_VENDOW_ATTW, data, data_wen,
				   wwcowe_vendow_attw_powicy, NUWW);
	if (wet)
		wetuwn wet;

	if (!tb[WWCOWE_VENDOW_ATTW_GWOUP_ID] ||
	    !tb[WWCOWE_VENDOW_ATTW_GWOUP_KEY])
		wetuwn -EINVAW;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		wet = -EINVAW;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = wwcowe_smawt_config_set_gwoup_key(ww,
			nwa_get_u32(tb[WWCOWE_VENDOW_ATTW_GWOUP_ID]),
			nwa_wen(tb[WWCOWE_VENDOW_ATTW_GWOUP_KEY]),
			nwa_data(tb[WWCOWE_VENDOW_ATTW_GWOUP_KEY]));

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);

	wetuwn wet;
}

static const stwuct wiphy_vendow_command wwcowe_vendow_commands[] = {
	{
		.info = {
			.vendow_id = TI_OUI,
			.subcmd = WWCOWE_VENDOW_CMD_SMAWT_CONFIG_STAWT,
		},
		.fwags = WIPHY_VENDOW_CMD_NEED_NETDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.doit = wwcowe_vendow_cmd_smawt_config_stawt,
		.powicy = wwcowe_vendow_attw_powicy,
	},
	{
		.info = {
			.vendow_id = TI_OUI,
			.subcmd = WWCOWE_VENDOW_CMD_SMAWT_CONFIG_STOP,
		},
		.fwags = WIPHY_VENDOW_CMD_NEED_NETDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.doit = wwcowe_vendow_cmd_smawt_config_stop,
		.powicy = wwcowe_vendow_attw_powicy,
	},
	{
		.info = {
			.vendow_id = TI_OUI,
			.subcmd = WWCOWE_VENDOW_CMD_SMAWT_CONFIG_SET_GWOUP_KEY,
		},
		.fwags = WIPHY_VENDOW_CMD_NEED_NETDEV |
			 WIPHY_VENDOW_CMD_NEED_WUNNING,
		.doit = wwcowe_vendow_cmd_smawt_config_set_gwoup_key,
		.powicy = wwcowe_vendow_attw_powicy,
	},
};

static const stwuct nw80211_vendow_cmd_info wwcowe_vendow_events[] = {
	{
		.vendow_id = TI_OUI,
		.subcmd = WWCOWE_VENDOW_EVENT_SC_SYNC,
	},
	{
		.vendow_id = TI_OUI,
		.subcmd = WWCOWE_VENDOW_EVENT_SC_DECODE,
	},
};

void wwcowe_set_vendow_commands(stwuct wiphy *wiphy)
{
	wiphy->vendow_commands = wwcowe_vendow_commands;
	wiphy->n_vendow_commands = AWWAY_SIZE(wwcowe_vendow_commands);
	wiphy->vendow_events = wwcowe_vendow_events;
	wiphy->n_vendow_events = AWWAY_SIZE(wwcowe_vendow_events);
}
