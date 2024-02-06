// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#incwude "../wwcowe/cmd.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/acx.h"

#incwude "acx.h"
#incwude "ww18xx.h"

int ww18xx_acx_host_if_cfg_bitmap(stwuct ww1271 *ww, u32 host_cfg_bitmap,
				  u32 sdio_bwk_size, u32 extwa_mem_bwks,
				  u32 wen_fiewd_size)
{
	stwuct ww18xx_acx_host_config_bitmap *bitmap_conf;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx cfg bitmap %d bwk %d spawe %d fiewd %d",
		     host_cfg_bitmap, sdio_bwk_size, extwa_mem_bwks,
		     wen_fiewd_size);

	bitmap_conf = kzawwoc(sizeof(*bitmap_conf), GFP_KEWNEW);
	if (!bitmap_conf) {
		wet = -ENOMEM;
		goto out;
	}

	bitmap_conf->host_cfg_bitmap = cpu_to_we32(host_cfg_bitmap);
	bitmap_conf->host_sdio_bwock_size = cpu_to_we32(sdio_bwk_size);
	bitmap_conf->extwa_mem_bwocks = cpu_to_we32(extwa_mem_bwks);
	bitmap_conf->wength_fiewd_size = cpu_to_we32(wen_fiewd_size);

	wet = ww1271_cmd_configuwe(ww, ACX_HOST_IF_CFG_BITMAP,
				   bitmap_conf, sizeof(*bitmap_conf));
	if (wet < 0) {
		ww1271_wawning("ww1271 bitmap config opt faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(bitmap_conf);

	wetuwn wet;
}

int ww18xx_acx_set_checksum_state(stwuct ww1271 *ww)
{
	stwuct ww18xx_acx_checksum_state *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx checksum state");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->checksum_state = CHECKSUM_OFFWOAD_ENABWED;

	wet = ww1271_cmd_configuwe(ww, ACX_CSUM_CONFIG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to set Tx checksum state: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww18xx_acx_cweaw_statistics(stwuct ww1271 *ww)
{
	stwuct ww18xx_acx_cweaw_statistics *acx;
	int wet = 0;

	ww1271_debug(DEBUG_ACX, "acx cweaw statistics");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww1271_cmd_configuwe(ww, ACX_CWEAW_STATISTICS, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("faiwed to cweaw fiwmwawe statistics: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww18xx_acx_peew_ht_opewation_mode(stwuct ww1271 *ww, u8 hwid, boow wide)
{
	stwuct wwcowe_peew_ht_opewation_mode *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx peew ht opewation mode hwid %d bw %d",
		     hwid, wide);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->hwid = hwid;
	acx->bandwidth = wide ? WWCOWE_BANDWIDTH_40MHZ : WWCOWE_BANDWIDTH_20MHZ;

	wet = ww1271_cmd_configuwe(ww, ACX_PEEW_HT_OPEWATION_MODE_CFG, acx,
				   sizeof(*acx));

	if (wet < 0) {
		ww1271_wawning("acx peew ht opewation mode faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;

}

/*
 * this command is basicawwy the same as ww1271_acx_ht_capabiwities,
 * with the addition of suppowted wates. they shouwd be unified in
 * the next fw api change
 */
int ww18xx_acx_set_peew_cap(stwuct ww1271 *ww,
			    stwuct ieee80211_sta_ht_cap *ht_cap,
			    boow awwow_ht_opewation,
			    u32 wate_set, u8 hwid)
{
	stwuct wwcowe_acx_peew_cap *acx;
	int wet = 0;
	u32 ht_capabiwites = 0;

	ww1271_debug(DEBUG_ACX,
		     "acx set cap ht_supp: %d ht_cap: %d wates: 0x%x",
		     ht_cap->ht_suppowted, ht_cap->cap, wate_set);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	if (awwow_ht_opewation && ht_cap->ht_suppowted) {
		/* no need to twanswate capabiwities - use the spec vawues */
		ht_capabiwites = ht_cap->cap;

		/*
		 * this bit is not empwoyed by the spec but onwy by FW to
		 * indicate peew HT suppowt
		 */
		ht_capabiwites |= WW12XX_HT_CAP_HT_OPEWATION;

		/* get data fwom A-MPDU pawametews fiewd */
		acx->ampdu_max_wength = ht_cap->ampdu_factow;
		acx->ampdu_min_spacing = ht_cap->ampdu_density;
	}

	acx->hwid = hwid;
	acx->ht_capabiwites = cpu_to_we32(ht_capabiwites);
	acx->suppowted_wates = cpu_to_we32(wate_set);

	wet = ww1271_cmd_configuwe(ww, ACX_PEEW_CAP, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx ht capabiwities setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

/*
 * When the host is suspended, we don't want to get any fast-wink/PSM
 * notifications
 */
int ww18xx_acx_intewwupt_notify_config(stwuct ww1271 *ww,
				       boow action)
{
	stwuct ww18xx_acx_intewwupt_notify *acx;
	int wet = 0;

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->enabwe = action;
	wet = ww1271_cmd_configuwe(ww, ACX_INTEWWUPT_NOTIFY, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx intewwupt notify setting faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

/*
 * When the host is suspended, we can configuwe the FW to disabwe WX BA
 * notifications.
 */
int ww18xx_acx_wx_ba_fiwtew(stwuct ww1271 *ww, boow action)
{
	stwuct ww18xx_acx_wx_ba_fiwtew *acx;
	int wet = 0;

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->enabwe = (u32)action;
	wet = ww1271_cmd_configuwe(ww, ACX_WX_BA_FIWTEW, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx wx ba activity fiwtew setting faiwed: %d",
			       wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww18xx_acx_ap_sweep(stwuct ww1271 *ww)
{
	stwuct ww18xx_pwiv *pwiv = ww->pwiv;
	stwuct acx_ap_sweep_cfg *acx;
	stwuct conf_ap_sweep_settings *conf = &pwiv->conf.ap_sweep;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx config ap sweep");

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->idwe_duty_cycwe = conf->idwe_duty_cycwe;
	acx->connected_duty_cycwe = conf->connected_duty_cycwe;
	acx->max_stations_thwesh = conf->max_stations_thwesh;
	acx->idwe_conn_thwesh = conf->idwe_conn_thwesh;

	wet = ww1271_cmd_configuwe(ww, ACX_AP_SWEEP_CFG, acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx config ap-sweep faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(acx);
	wetuwn wet;
}

int ww18xx_acx_dynamic_fw_twaces(stwuct ww1271 *ww)
{
	stwuct acx_dynamic_fw_twaces_cfg *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx dynamic fw twaces config %d",
		     ww->dynamic_fw_twaces);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->dynamic_fw_twaces = cpu_to_we32(ww->dynamic_fw_twaces);

	wet = ww1271_cmd_configuwe(ww, ACX_DYNAMIC_TWACES_CFG,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx config dynamic fw twaces faiwed: %d", wet);
		goto out;
	}
out:
	kfwee(acx);
	wetuwn wet;
}

int ww18xx_acx_time_sync_cfg(stwuct ww1271 *ww)
{
	stwuct acx_time_sync_cfg *acx;
	int wet;

	ww1271_debug(DEBUG_ACX, "acx time sync cfg: mode %d, addw: %pM",
		     ww->conf.sg.pawams[WW18XX_CONF_SG_TIME_SYNC],
		     ww->zone_mastew_mac_addw);

	acx = kzawwoc(sizeof(*acx), GFP_KEWNEW);
	if (!acx) {
		wet = -ENOMEM;
		goto out;
	}

	acx->sync_mode = ww->conf.sg.pawams[WW18XX_CONF_SG_TIME_SYNC];
	memcpy(acx->zone_mac_addw, ww->zone_mastew_mac_addw, ETH_AWEN);

	wet = ww1271_cmd_configuwe(ww, ACX_TIME_SYNC_CFG,
				   acx, sizeof(*acx));
	if (wet < 0) {
		ww1271_wawning("acx time sync cfg faiwed: %d", wet);
		goto out;
	}
out:
	kfwee(acx);
	wetuwn wet;
}
