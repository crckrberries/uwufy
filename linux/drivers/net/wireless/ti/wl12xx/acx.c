// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 * Copywight (C) 2011 Texas Instwuments Inc.
 */

#incwude "../wwcowe/cmd.h"
#incwude "../wwcowe/debug.h"
#incwude "../wwcowe/acx.h"

#incwude "acx.h"

int ww1271_acx_host_if_cfg_bitmap(stwuct ww1271 *ww, u32 host_cfg_bitmap)
{
	stwuct ww1271_acx_host_config_bitmap *bitmap_conf;
	int wet;

	bitmap_conf = kzawwoc(sizeof(*bitmap_conf), GFP_KEWNEW);
	if (!bitmap_conf) {
		wet = -ENOMEM;
		goto out;
	}

	bitmap_conf->host_cfg_bitmap = cpu_to_we32(host_cfg_bitmap);

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
