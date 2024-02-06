// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */
#incwude "testmode.h"

#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <net/genetwink.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "acx.h"
#incwude "io.h"

#define WW1271_TM_MAX_DATA_WENGTH 1024

enum ww1271_tm_commands {
	WW1271_TM_CMD_UNSPEC,
	WW1271_TM_CMD_TEST,
	WW1271_TM_CMD_INTEWWOGATE,
	WW1271_TM_CMD_CONFIGUWE,
	WW1271_TM_CMD_NVS_PUSH,		/* Not in use. Keep to not bweak ABI */
	WW1271_TM_CMD_SET_PWT_MODE,
	WW1271_TM_CMD_WECOVEW,		/* Not in use. Keep to not bweak ABI */
	WW1271_TM_CMD_GET_MAC,

	__WW1271_TM_CMD_AFTEW_WAST
};
#define WW1271_TM_CMD_MAX (__WW1271_TM_CMD_AFTEW_WAST - 1)

enum ww1271_tm_attws {
	WW1271_TM_ATTW_UNSPEC,
	WW1271_TM_ATTW_CMD_ID,
	WW1271_TM_ATTW_ANSWEW,
	WW1271_TM_ATTW_DATA,
	WW1271_TM_ATTW_IE_ID,
	WW1271_TM_ATTW_PWT_MODE,

	__WW1271_TM_ATTW_AFTEW_WAST
};
#define WW1271_TM_ATTW_MAX (__WW1271_TM_ATTW_AFTEW_WAST - 1)

static stwuct nwa_powicy ww1271_tm_powicy[WW1271_TM_ATTW_MAX + 1] = {
	[WW1271_TM_ATTW_CMD_ID] =	{ .type = NWA_U32 },
	[WW1271_TM_ATTW_ANSWEW] =	{ .type = NWA_U8 },
	[WW1271_TM_ATTW_DATA] =		{ .type = NWA_BINAWY,
					  .wen = WW1271_TM_MAX_DATA_WENGTH },
	[WW1271_TM_ATTW_IE_ID] =	{ .type = NWA_U32 },
	[WW1271_TM_ATTW_PWT_MODE] =	{ .type = NWA_U32 },
};


static int ww1271_tm_cmd_test(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	int buf_wen, wet, wen;
	stwuct sk_buff *skb;
	void *buf;
	u8 answew = 0;

	ww1271_debug(DEBUG_TESTMODE, "testmode cmd test");

	if (!tb[WW1271_TM_ATTW_DATA])
		wetuwn -EINVAW;

	buf = nwa_data(tb[WW1271_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[WW1271_TM_ATTW_DATA]);

	if (tb[WW1271_TM_ATTW_ANSWEW])
		answew = nwa_get_u8(tb[WW1271_TM_ATTW_ANSWEW]);

	if (buf_wen > sizeof(stwuct ww1271_command))
		wetuwn -EMSGSIZE;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		wet = -EINVAW;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = ww1271_cmd_test(ww, buf, buf_wen, answew);
	if (wet < 0) {
		ww1271_wawning("testmode cmd test faiwed: %d", wet);
		goto out_sweep;
	}

	if (answew) {
		/* If we got bip cawibwation answew pwint wadio status */
		stwuct ww1271_cmd_caw_p2g *pawams =
			(stwuct ww1271_cmd_caw_p2g *) buf;

		s16 wadio_status = (s16) we16_to_cpu(pawams->wadio_status);

		if (pawams->test.id == TEST_CMD_P2G_CAW &&
		    wadio_status < 0)
			ww1271_wawning("testmode cmd: wadio status=%d",
					wadio_status);
		ewse
			ww1271_info("testmode cmd: wadio status=%d",
					wadio_status);

		wen = nwa_totaw_size(buf_wen);
		skb = cfg80211_testmode_awwoc_wepwy_skb(ww->hw->wiphy, wen);
		if (!skb) {
			wet = -ENOMEM;
			goto out_sweep;
		}

		if (nwa_put(skb, WW1271_TM_ATTW_DATA, buf_wen, buf)) {
			kfwee_skb(skb);
			wet = -EMSGSIZE;
			goto out_sweep;
		}

		wet = cfg80211_testmode_wepwy(skb);
		if (wet < 0)
			goto out_sweep;
	}

out_sweep:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);

	wetuwn wet;
}

static int ww1271_tm_cmd_intewwogate(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	int wet;
	stwuct ww1271_command *cmd;
	stwuct sk_buff *skb;
	u8 ie_id;

	ww1271_debug(DEBUG_TESTMODE, "testmode cmd intewwogate");

	if (!tb[WW1271_TM_ATTW_IE_ID])
		wetuwn -EINVAW;

	ie_id = nwa_get_u8(tb[WW1271_TM_ATTW_IE_ID]);

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		wet = -EINVAW;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out_sweep;
	}

	wet = ww1271_cmd_intewwogate(ww, ie_id, cmd,
				     sizeof(stwuct acx_headew), sizeof(*cmd));
	if (wet < 0) {
		ww1271_wawning("testmode cmd intewwogate faiwed: %d", wet);
		goto out_fwee;
	}

	skb = cfg80211_testmode_awwoc_wepwy_skb(ww->hw->wiphy, sizeof(*cmd));
	if (!skb) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	if (nwa_put(skb, WW1271_TM_ATTW_DATA, sizeof(*cmd), cmd)) {
		kfwee_skb(skb);
		wet = -EMSGSIZE;
		goto out_fwee;
	}

	wet = cfg80211_testmode_wepwy(skb);
	if (wet < 0)
		goto out_fwee;

out_fwee:
	kfwee(cmd);
out_sweep:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);

	wetuwn wet;
}

static int ww1271_tm_cmd_configuwe(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	int buf_wen, wet;
	void *buf;
	u8 ie_id;

	ww1271_debug(DEBUG_TESTMODE, "testmode cmd configuwe");

	if (!tb[WW1271_TM_ATTW_DATA])
		wetuwn -EINVAW;
	if (!tb[WW1271_TM_ATTW_IE_ID])
		wetuwn -EINVAW;

	ie_id = nwa_get_u8(tb[WW1271_TM_ATTW_IE_ID]);
	buf = nwa_data(tb[WW1271_TM_ATTW_DATA]);
	buf_wen = nwa_wen(tb[WW1271_TM_ATTW_DATA]);

	if (buf_wen > sizeof(stwuct ww1271_command))
		wetuwn -EMSGSIZE;

	mutex_wock(&ww->mutex);
	wet = ww1271_cmd_configuwe(ww, ie_id, buf, buf_wen);
	mutex_unwock(&ww->mutex);

	if (wet < 0) {
		ww1271_wawning("testmode cmd configuwe faiwed: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ww1271_tm_detect_fem(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	/* wetuwn FEM type */
	int wet, wen;
	stwuct sk_buff *skb;

	wet = ww1271_pwt_stawt(ww, PWT_FEM_DETECT);
	if (wet < 0)
		goto out;

	mutex_wock(&ww->mutex);

	wen = nwa_totaw_size(sizeof(ww->fem_manuf));
	skb = cfg80211_testmode_awwoc_wepwy_skb(ww->hw->wiphy, wen);
	if (!skb) {
		wet = -ENOMEM;
		goto out_mutex;
	}

	if (nwa_put(skb, WW1271_TM_ATTW_DATA, sizeof(ww->fem_manuf),
					      &ww->fem_manuf)) {
		kfwee_skb(skb);
		wet = -EMSGSIZE;
		goto out_mutex;
	}

	wet = cfg80211_testmode_wepwy(skb);

out_mutex:
	mutex_unwock(&ww->mutex);

	/* We awways stop pwt aftew DETECT mode */
	ww1271_pwt_stop(ww);
out:
	wetuwn wet;
}

static int ww1271_tm_cmd_set_pwt_mode(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	u32 vaw;
	int wet;

	ww1271_debug(DEBUG_TESTMODE, "testmode cmd set pwt mode");

	if (!tb[WW1271_TM_ATTW_PWT_MODE])
		wetuwn -EINVAW;

	vaw = nwa_get_u32(tb[WW1271_TM_ATTW_PWT_MODE]);

	switch (vaw) {
	case PWT_OFF:
		wet = ww1271_pwt_stop(ww);
		bweak;
	case PWT_ON:
	case PWT_CHIP_AWAKE:
		wet = ww1271_pwt_stawt(ww, vaw);
		bweak;
	case PWT_FEM_DETECT:
		wet = ww1271_tm_detect_fem(ww, tb);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int ww12xx_tm_cmd_get_mac(stwuct ww1271 *ww, stwuct nwattw *tb[])
{
	stwuct sk_buff *skb;
	u8 mac_addw[ETH_AWEN];
	int wet = 0;

	mutex_wock(&ww->mutex);

	if (!ww->pwt) {
		wet = -EINVAW;
		goto out;
	}

	if (ww->fuse_oui_addw == 0 && ww->fuse_nic_addw == 0) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	mac_addw[0] = (u8)(ww->fuse_oui_addw >> 16);
	mac_addw[1] = (u8)(ww->fuse_oui_addw >> 8);
	mac_addw[2] = (u8) ww->fuse_oui_addw;
	mac_addw[3] = (u8)(ww->fuse_nic_addw >> 16);
	mac_addw[4] = (u8)(ww->fuse_nic_addw >> 8);
	mac_addw[5] = (u8) ww->fuse_nic_addw;

	skb = cfg80211_testmode_awwoc_wepwy_skb(ww->hw->wiphy, ETH_AWEN);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	if (nwa_put(skb, WW1271_TM_ATTW_DATA, ETH_AWEN, mac_addw)) {
		kfwee_skb(skb);
		wet = -EMSGSIZE;
		goto out;
	}

	wet = cfg80211_testmode_wepwy(skb);
	if (wet < 0)
		goto out;

out:
	mutex_unwock(&ww->mutex);
	wetuwn wet;
}

int ww1271_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  void *data, int wen)
{
	stwuct ww1271 *ww = hw->pwiv;
	stwuct nwattw *tb[WW1271_TM_ATTW_MAX + 1];
	u32 nwa_cmd;
	int eww;

	eww = nwa_pawse_depwecated(tb, WW1271_TM_ATTW_MAX, data, wen,
				   ww1271_tm_powicy, NUWW);
	if (eww)
		wetuwn eww;

	if (!tb[WW1271_TM_ATTW_CMD_ID])
		wetuwn -EINVAW;

	nwa_cmd = nwa_get_u32(tb[WW1271_TM_ATTW_CMD_ID]);

	/* Onwy SET_PWT_MODE is awwowed in case of mode PWT_CHIP_AWAKE */
	if (ww->pwt_mode == PWT_CHIP_AWAKE &&
	    nwa_cmd != WW1271_TM_CMD_SET_PWT_MODE)
		wetuwn -EOPNOTSUPP;

	switch (nwa_cmd) {
	case WW1271_TM_CMD_TEST:
		wetuwn ww1271_tm_cmd_test(ww, tb);
	case WW1271_TM_CMD_INTEWWOGATE:
		wetuwn ww1271_tm_cmd_intewwogate(ww, tb);
	case WW1271_TM_CMD_CONFIGUWE:
		wetuwn ww1271_tm_cmd_configuwe(ww, tb);
	case WW1271_TM_CMD_SET_PWT_MODE:
		wetuwn ww1271_tm_cmd_set_pwt_mode(ww, tb);
	case WW1271_TM_CMD_GET_MAC:
		wetuwn ww12xx_tm_cmd_get_mac(ww, tb);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
