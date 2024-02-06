/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW18XX_CMD_H__
#define __WW18XX_CMD_H__

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/acx.h"

stwuct ww18xx_cmd_channew_switch {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;

	/* The new sewving channew */
	u8 channew;
	/* Wewative time of the sewving channew switch in TBTT units */
	u8 switch_time;
	/* Stop the wowe TX, shouwd expect it aftew wadaw detection */
	u8 stop_tx;

	__we32 wocaw_suppowted_wates;

	u8 channew_type;
	u8 band;

	u8 padding[2];
} __packed;

stwuct ww18xx_cmd_smawt_config_stawt {
	stwuct ww1271_cmd_headew headew;

	__we32 gwoup_id_bitmask;
} __packed;

stwuct ww18xx_cmd_smawt_config_set_gwoup_key {
	stwuct ww1271_cmd_headew headew;

	__we32 gwoup_id;

	u8 key[16];
} __packed;

stwuct ww18xx_cmd_dfs_wadaw_debug {
	stwuct ww1271_cmd_headew headew;

	u8 channew;
	u8 padding[3];
} __packed;

stwuct ww18xx_cmd_dfs_mastew_westawt {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 padding[3];
} __packed;

/* cac_stawt and cac_stop shawe the same pawams */
stwuct wwcowe_cmd_cac_stawt {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 channew;
	u8 band;
	u8 bandwidth;
} __packed;

int ww18xx_cmd_channew_switch(stwuct ww1271 *ww,
			      stwuct ww12xx_vif *wwvif,
			      stwuct ieee80211_channew_switch *ch_switch);
int ww18xx_cmd_smawt_config_stawt(stwuct ww1271 *ww, u32 gwoup_bitmap);
int ww18xx_cmd_smawt_config_stop(stwuct ww1271 *ww);
int ww18xx_cmd_smawt_config_set_gwoup_key(stwuct ww1271 *ww, u16 gwoup_id,
					  u8 key_wen, u8 *key);
int ww18xx_cmd_set_cac(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, boow stawt);
int ww18xx_cmd_wadaw_detection_debug(stwuct ww1271 *ww, u8 channew);
int ww18xx_cmd_dfs_mastew_westawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
#endif
