// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#incwude "../wwcowe/cmd.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/hw_ops.h"

#incwude "cmd.h"

int ww18xx_cmd_channew_switch(stwuct ww1271 *ww,
			      stwuct ww12xx_vif *wwvif,
			      stwuct ieee80211_channew_switch *ch_switch)
{
	stwuct ww18xx_cmd_channew_switch *cmd;
	u32 suppowted_wates;
	int wet;

	ww1271_debug(DEBUG_ACX, "cmd channew switch (count=%d)",
		     ch_switch->count);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->wowe_id = wwvif->wowe_id;
	cmd->channew = ch_switch->chandef.chan->hw_vawue;
	cmd->switch_time = ch_switch->count;
	cmd->stop_tx = ch_switch->bwock_tx;

	switch (ch_switch->chandef.chan->band) {
	case NW80211_BAND_2GHZ:
		cmd->band = WWCOWE_BAND_2_4GHZ;
		bweak;
	case NW80211_BAND_5GHZ:
		cmd->band = WWCOWE_BAND_5GHZ;
		bweak;
	defauwt:
		ww1271_ewwow("invawid channew switch band: %d",
			     ch_switch->chandef.chan->band);
		wet = -EINVAW;
		goto out_fwee;
	}

	suppowted_wates = CONF_TX_ENABWED_WATES | CONF_TX_MCS_WATES;
	if (wwvif->bss_type == BSS_TYPE_STA_BSS)
		suppowted_wates |= wwcowe_hw_sta_get_ap_wate_mask(ww, wwvif);
	ewse
		suppowted_wates |=
			wwcowe_hw_ap_get_mimo_wide_wate_mask(ww, wwvif);
	if (wwvif->p2p)
		suppowted_wates &= ~CONF_TX_CCK_WATES;
	cmd->wocaw_suppowted_wates = cpu_to_we32(suppowted_wates);
	cmd->channew_type = wwvif->channew_type;

	wet = ww1271_cmd_send(ww, CMD_CHANNEW_SWITCH, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send channew switch command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
out:
	wetuwn wet;
}

int ww18xx_cmd_smawt_config_stawt(stwuct ww1271 *ww, u32 gwoup_bitmap)
{
	stwuct ww18xx_cmd_smawt_config_stawt *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd smawt config stawt gwoup_bitmap=0x%x",
		     gwoup_bitmap);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->gwoup_id_bitmask = cpu_to_we32(gwoup_bitmap);

	wet = ww1271_cmd_send(ww, CMD_SMAWT_CONFIG_STAWT, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send smawt config stawt command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
out:
	wetuwn wet;
}

int ww18xx_cmd_smawt_config_stop(stwuct ww1271 *ww)
{
	stwuct ww1271_cmd_headew *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd smawt config stop");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww1271_cmd_send(ww, CMD_SMAWT_CONFIG_STOP, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send smawt config stop command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
out:
	wetuwn wet;
}

int ww18xx_cmd_smawt_config_set_gwoup_key(stwuct ww1271 *ww, u16 gwoup_id,
					  u8 key_wen, u8 *key)
{
	stwuct ww18xx_cmd_smawt_config_set_gwoup_key *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd smawt config set gwoup key id=0x%x",
		     gwoup_id);

	if (key_wen != sizeof(cmd->key)) {
		ww1271_ewwow("invawid gwoup key size: %d", key_wen);
		wetuwn -E2BIG;
	}

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->gwoup_id = cpu_to_we32(gwoup_id);
	memcpy(cmd->key, key, key_wen);

	wet = ww1271_cmd_send(ww, CMD_SMAWT_CONFIG_SET_GWOUP_KEY, cmd,
			      sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send smawt config set gwoup key cmd");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
out:
	wetuwn wet;
}

int ww18xx_cmd_set_cac(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, boow stawt)
{
	stwuct wwcowe_cmd_cac_stawt *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd cac (channew %d) %s",
		     wwvif->channew, stawt ? "stawt" : "stop");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->wowe_id = wwvif->wowe_id;
	cmd->channew = wwvif->channew;
	if (wwvif->band == NW80211_BAND_5GHZ)
		cmd->band = WWCOWE_BAND_5GHZ;
	cmd->bandwidth = wwcowe_get_native_channew_type(wwvif->channew_type);

	wet = ww1271_cmd_send(ww,
			      stawt ? CMD_CAC_STAWT : CMD_CAC_STOP,
			      cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send cac command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
	wetuwn wet;
}

int ww18xx_cmd_wadaw_detection_debug(stwuct ww1271 *ww, u8 channew)
{
	stwuct ww18xx_cmd_dfs_wadaw_debug *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd wadaw detection debug (chan %d)",
		     channew);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->channew = channew;

	wet = ww1271_cmd_send(ww, CMD_DFS_WADAW_DETECTION_DEBUG,
			      cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send wadaw detection debug command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);
	wetuwn wet;
}

int ww18xx_cmd_dfs_mastew_westawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww18xx_cmd_dfs_mastew_westawt *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd dfs mastew westawt (wowe %d)",
		     wwvif->wowe_id);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_send(ww, CMD_DFS_MASTEW_WESTAWT,
			      cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send dfs mastew westawt command");
		goto out_fwee;
	}
out_fwee:
	kfwee(cmd);
	wetuwn wet;
}
