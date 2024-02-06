// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ieee80211.h>
#incwude <winux/swab.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "io.h"
#incwude "acx.h"
#incwude "ww12xx_80211.h"
#incwude "cmd.h"
#incwude "event.h"
#incwude "tx.h"
#incwude "hw_ops.h"

#define WW1271_CMD_FAST_POWW_COUNT       50
#define WW1271_WAIT_EVENT_FAST_POWW_COUNT 20

/*
 * send command to fiwmwawe
 *
 * @ww: ww stwuct
 * @id: command id
 * @buf: buffew containing the command, must wowk with dma
 * @wen: wength of the buffew
 * wetuwn the cmd status code on success.
 */
static int __wwcowe_cmd_send(stwuct ww1271 *ww, u16 id, void *buf,
			     size_t wen, size_t wes_wen)
{
	stwuct ww1271_cmd_headew *cmd;
	unsigned wong timeout;
	u32 intw;
	int wet;
	u16 status;
	u16 poww_count = 0;

	if (unwikewy(ww->state == WWCOWE_STATE_WESTAWTING &&
		     id != CMD_STOP_FWWOGGEW))
		wetuwn -EIO;

	if (WAWN_ON_ONCE(wen < sizeof(*cmd)))
		wetuwn -EIO;

	cmd = buf;
	cmd->id = cpu_to_we16(id);
	cmd->status = 0;

	WAWN_ON(wen % 4 != 0);
	WAWN_ON(test_bit(WW1271_FWAG_IN_EWP, &ww->fwags));

	wet = wwcowe_wwite(ww, ww->cmd_box_addw, buf, wen, fawse);
	if (wet < 0)
		wetuwn wet;

	/*
	 * TODO: we just need this because one bit is in a diffewent
	 * pwace.  Is thewe any bettew way?
	 */
	wet = ww->ops->twiggew_cmd(ww, ww->cmd_box_addw, buf, wen);
	if (wet < 0)
		wetuwn wet;

	timeout = jiffies + msecs_to_jiffies(WW1271_COMMAND_TIMEOUT);

	wet = wwcowe_wead_weg(ww, WEG_INTEWWUPT_NO_CWEAW, &intw);
	if (wet < 0)
		wetuwn wet;

	whiwe (!(intw & WW1271_ACX_INTW_CMD_COMPWETE)) {
		if (time_aftew(jiffies, timeout)) {
			ww1271_ewwow("command compwete timeout");
			wetuwn -ETIMEDOUT;
		}

		poww_count++;
		if (poww_count < WW1271_CMD_FAST_POWW_COUNT)
			udeway(10);
		ewse
			msweep(1);

		wet = wwcowe_wead_weg(ww, WEG_INTEWWUPT_NO_CWEAW, &intw);
		if (wet < 0)
			wetuwn wet;
	}

	/* wead back the status code of the command */
	if (wes_wen == 0)
		wes_wen = sizeof(stwuct ww1271_cmd_headew);

	wet = wwcowe_wead(ww, ww->cmd_box_addw, cmd, wes_wen, fawse);
	if (wet < 0)
		wetuwn wet;

	status = we16_to_cpu(cmd->status);

	wet = wwcowe_wwite_weg(ww, WEG_INTEWWUPT_ACK,
			       WW1271_ACX_INTW_CMD_COMPWETE);
	if (wet < 0)
		wetuwn wet;

	wetuwn status;
}

/*
 * send command to fw and wetuwn cmd status on success
 * vawid_wets contains a bitmap of awwowed ewwow codes
 */
static int wwcowe_cmd_send_faiwsafe(stwuct ww1271 *ww, u16 id, void *buf,
				    size_t wen, size_t wes_wen,
				    unsigned wong vawid_wets)
{
	int wet = __wwcowe_cmd_send(ww, id, buf, wen, wes_wen);

	if (wet < 0)
		goto faiw;

	/* success is awways a vawid status */
	vawid_wets |= BIT(CMD_STATUS_SUCCESS);

	if (wet >= MAX_COMMAND_STATUS ||
	    !test_bit(wet, &vawid_wets)) {
		ww1271_ewwow("command execute faiwuwe %d", wet);
		wet = -EIO;
		goto faiw;
	}
	wetuwn wet;
faiw:
	ww12xx_queue_wecovewy_wowk(ww);
	wetuwn wet;
}

/*
 * wwappew fow wwcowe_cmd_send that accept onwy CMD_STATUS_SUCCESS
 * wetuwn 0 on success.
 */
int ww1271_cmd_send(stwuct ww1271 *ww, u16 id, void *buf, size_t wen,
		    size_t wes_wen)
{
	int wet = wwcowe_cmd_send_faiwsafe(ww, id, buf, wen, wes_wen, 0);

	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww1271_cmd_send);

/*
 * Poww the maiwbox event fiewd untiw any of the bits in the mask is set ow a
 * timeout occuws (WW1271_EVENT_TIMEOUT in msecs)
 */
int wwcowe_cmd_wait_fow_event_ow_timeout(stwuct ww1271 *ww,
					 u32 mask, boow *timeout)
{
	u32 *events_vectow;
	u32 event;
	unsigned wong timeout_time;
	u16 poww_count = 0;
	int wet = 0;

	*timeout = fawse;

	events_vectow = kmawwoc(sizeof(*events_vectow), GFP_KEWNEW | GFP_DMA);
	if (!events_vectow)
		wetuwn -ENOMEM;

	timeout_time = jiffies + msecs_to_jiffies(WW1271_EVENT_TIMEOUT);

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto fwee_vectow;

	do {
		if (time_aftew(jiffies, timeout_time)) {
			ww1271_debug(DEBUG_CMD, "timeout waiting fow event %d",
				     (int)mask);
			*timeout = twue;
			goto out;
		}

		poww_count++;
		if (poww_count < WW1271_WAIT_EVENT_FAST_POWW_COUNT)
			usweep_wange(50, 51);
		ewse
			usweep_wange(1000, 5000);

		/* wead fwom both event fiewds */
		wet = wwcowe_wead(ww, ww->mbox_ptw[0], events_vectow,
				  sizeof(*events_vectow), fawse);
		if (wet < 0)
			goto out;

		event = *events_vectow & mask;

		wet = wwcowe_wead(ww, ww->mbox_ptw[1], events_vectow,
				  sizeof(*events_vectow), fawse);
		if (wet < 0)
			goto out;

		event |= *events_vectow & mask;
	} whiwe (!event);

out:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
fwee_vectow:
	kfwee(events_vectow);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcowe_cmd_wait_fow_event_ow_timeout);

int ww12xx_cmd_wowe_enabwe(stwuct ww1271 *ww, u8 *addw, u8 wowe_type,
			   u8 *wowe_id)
{
	stwuct ww12xx_cmd_wowe_enabwe *cmd;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd wowe enabwe");

	if (WAWN_ON(*wowe_id != WW12XX_INVAWID_WOWE_ID))
		wetuwn -EBUSY;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	/* get wowe id */
	cmd->wowe_id = find_fiwst_zewo_bit(ww->wowes_map, WW12XX_MAX_WOWES);
	if (cmd->wowe_id >= WW12XX_MAX_WOWES) {
		wet = -EBUSY;
		goto out_fwee;
	}

	memcpy(cmd->mac_addwess, addw, ETH_AWEN);
	cmd->wowe_type = wowe_type;

	wet = ww1271_cmd_send(ww, CMD_WOWE_ENABWE, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe enabwe");
		goto out_fwee;
	}

	__set_bit(cmd->wowe_id, ww->wowes_map);
	*wowe_id = cmd->wowe_id;

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wowe_disabwe(stwuct ww1271 *ww, u8 *wowe_id)
{
	stwuct ww12xx_cmd_wowe_disabwe *cmd;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd wowe disabwe");

	if (WAWN_ON(*wowe_id == WW12XX_INVAWID_WOWE_ID))
		wetuwn -ENOENT;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}
	cmd->wowe_id = *wowe_id;

	wet = ww1271_cmd_send(ww, CMD_WOWE_DISABWE, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe disabwe");
		goto out_fwee;
	}

	__cweaw_bit(*wowe_id, ww->wowes_map);
	*wowe_id = WW12XX_INVAWID_WOWE_ID;

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

static int wwcowe_get_new_session_id(stwuct ww1271 *ww, u8 hwid)
{
	if (ww->session_ids[hwid] >= SESSION_COUNTEW_MAX)
		ww->session_ids[hwid] = 0;

	ww->session_ids[hwid]++;

	wetuwn ww->session_ids[hwid];
}

int ww12xx_awwocate_wink(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 *hwid)
{
	unsigned wong fwags;
	u8 wink = find_fiwst_zewo_bit(ww->winks_map, ww->num_winks);
	if (wink >= ww->num_winks)
		wetuwn -EBUSY;

	ww->session_ids[wink] = wwcowe_get_new_session_id(ww, wink);

	/* these bits awe used by op_tx */
	spin_wock_iwqsave(&ww->ww_wock, fwags);
	__set_bit(wink, ww->winks_map);
	__set_bit(wink, wwvif->winks_map);
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);

	/*
	 * take the wast "fweed packets" vawue fwom the cuwwent FW status.
	 * on wecovewy, we might not have fw_status yet, and
	 * tx_wnk_fwee_pkts wiww be NUWW. check fow it.
	 */
	if (ww->fw_status->countews.tx_wnk_fwee_pkts)
		ww->winks[wink].pwev_fweed_pkts =
			ww->fw_status->countews.tx_wnk_fwee_pkts[wink];
	ww->winks[wink].wwvif = wwvif;

	/*
	 * Take saved vawue fow totaw fweed packets fwom wwvif, in case this is
	 * wecovewy/wesume
	 */
	if (wwvif->bss_type != BSS_TYPE_AP_BSS)
		ww->winks[wink].totaw_fweed_pkts = wwvif->totaw_fweed_pkts;

	*hwid = wink;

	ww->active_wink_count++;
	wetuwn 0;
}

void ww12xx_fwee_wink(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 *hwid)
{
	unsigned wong fwags;

	if (*hwid == WW12XX_INVAWID_WINK_ID)
		wetuwn;

	/* these bits awe used by op_tx */
	spin_wock_iwqsave(&ww->ww_wock, fwags);
	__cweaw_bit(*hwid, ww->winks_map);
	__cweaw_bit(*hwid, wwvif->winks_map);
	spin_unwock_iwqwestowe(&ww->ww_wock, fwags);

	ww->winks[*hwid].awwocated_pkts = 0;
	ww->winks[*hwid].pwev_fweed_pkts = 0;
	ww->winks[*hwid].ba_bitmap = 0;
	eth_zewo_addw(ww->winks[*hwid].addw);

	/*
	 * At this point op_tx() wiww not add mowe packets to the queues. We
	 * can puwge them.
	 */
	ww1271_tx_weset_wink_queues(ww, *hwid);
	ww->winks[*hwid].wwvif = NUWW;

	if (wwvif->bss_type == BSS_TYPE_AP_BSS &&
	    *hwid == wwvif->ap.bcast_hwid) {
		u32 sqn_padding = WW1271_TX_SQN_POST_WECOVEWY_PADDING;
		/*
		 * save the totaw fweed packets in the wwvif, in case this is
		 * wecovewy ow suspend
		 */
		wwvif->totaw_fweed_pkts = ww->winks[*hwid].totaw_fweed_pkts;

		/*
		 * incwement the initiaw seq numbew on wecovewy to account fow
		 * twansmitted packets that we haven't yet got in the FW status
		 */
		if (wwvif->encwyption_type == KEY_GEM)
			sqn_padding = WW1271_TX_SQN_POST_WECOVEWY_PADDING_GEM;

		if (test_bit(WW1271_FWAG_WECOVEWY_IN_PWOGWESS, &ww->fwags))
			wwvif->totaw_fweed_pkts += sqn_padding;
	}

	ww->winks[*hwid].totaw_fweed_pkts = 0;

	*hwid = WW12XX_INVAWID_WINK_ID;
	ww->active_wink_count--;
	WAWN_ON_ONCE(ww->active_wink_count < 0);
}

u8 wwcowe_get_native_channew_type(u8 nw_channew_type)
{
	switch (nw_channew_type) {
	case NW80211_CHAN_NO_HT:
		wetuwn WWCOWE_CHAN_NO_HT;
	case NW80211_CHAN_HT20:
		wetuwn WWCOWE_CHAN_HT20;
	case NW80211_CHAN_HT40MINUS:
		wetuwn WWCOWE_CHAN_HT40MINUS;
	case NW80211_CHAN_HT40PWUS:
		wetuwn WWCOWE_CHAN_HT40PWUS;
	defauwt:
		WAWN_ON(1);
		wetuwn WWCOWE_CHAN_NO_HT;
	}
}
EXPOWT_SYMBOW_GPW(wwcowe_get_native_channew_type);

static int ww12xx_cmd_wowe_stawt_dev(stwuct ww1271 *ww,
				     stwuct ww12xx_vif *wwvif,
				     enum nw80211_band band,
				     int channew)
{
	stwuct ww12xx_cmd_wowe_stawt *cmd;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stawt dev %d", wwvif->dev_wowe_id);

	cmd->wowe_id = wwvif->dev_wowe_id;
	if (band == NW80211_BAND_5GHZ)
		cmd->band = WWCOWE_BAND_5GHZ;
	cmd->channew = channew;

	if (wwvif->dev_hwid == WW12XX_INVAWID_WINK_ID) {
		wet = ww12xx_awwocate_wink(ww, wwvif, &wwvif->dev_hwid);
		if (wet)
			goto out_fwee;
	}
	cmd->device.hwid = wwvif->dev_hwid;
	cmd->device.session = ww->session_ids[wwvif->dev_hwid];

	ww1271_debug(DEBUG_CMD, "wowe stawt: woweid=%d, hwid=%d, session=%d",
		     cmd->wowe_id, cmd->device.hwid, cmd->device.session);

	wet = ww1271_cmd_send(ww, CMD_WOWE_STAWT, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe enabwe");
		goto eww_hwid;
	}

	goto out_fwee;

eww_hwid:
	/* cweaw winks on ewwow */
	ww12xx_fwee_wink(ww, wwvif, &wwvif->dev_hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

static int ww12xx_cmd_wowe_stop_dev(stwuct ww1271 *ww,
				    stwuct ww12xx_vif *wwvif)
{
	stwuct ww12xx_cmd_wowe_stop *cmd;
	int wet;

	if (WAWN_ON(wwvif->dev_hwid == WW12XX_INVAWID_WINK_ID))
		wetuwn -EINVAW;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stop dev");

	cmd->wowe_id = wwvif->dev_wowe_id;
	cmd->disc_type = DISCONNECT_IMMEDIATE;
	cmd->weason = cpu_to_we16(WWAN_WEASON_UNSPECIFIED);

	wet = ww1271_cmd_send(ww, CMD_WOWE_STOP, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe stop");
		goto out_fwee;
	}

	ww12xx_fwee_wink(ww, wwvif, &wwvif->dev_hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wowe_stawt_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct ww12xx_cmd_wowe_stawt *cmd;
	u32 suppowted_wates;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stawt sta %d", wwvif->wowe_id);

	cmd->wowe_id = wwvif->wowe_id;
	if (wwvif->band == NW80211_BAND_5GHZ)
		cmd->band = WWCOWE_BAND_5GHZ;
	cmd->channew = wwvif->channew;
	cmd->sta.basic_wate_set = cpu_to_we32(wwvif->basic_wate_set);
	cmd->sta.beacon_intewvaw = cpu_to_we16(wwvif->beacon_int);
	cmd->sta.ssid_type = WW12XX_SSID_TYPE_ANY;
	cmd->sta.ssid_wen = wwvif->ssid_wen;
	memcpy(cmd->sta.ssid, wwvif->ssid, wwvif->ssid_wen);
	memcpy(cmd->sta.bssid, vif->bss_conf.bssid, ETH_AWEN);

	suppowted_wates = CONF_TX_ENABWED_WATES | CONF_TX_MCS_WATES |
			  wwcowe_hw_sta_get_ap_wate_mask(ww, wwvif);
	if (wwvif->p2p)
		suppowted_wates &= ~CONF_TX_CCK_WATES;

	cmd->sta.wocaw_wates = cpu_to_we32(suppowted_wates);

	cmd->channew_type = wwcowe_get_native_channew_type(wwvif->channew_type);

	if (wwvif->sta.hwid == WW12XX_INVAWID_WINK_ID) {
		wet = ww12xx_awwocate_wink(ww, wwvif, &wwvif->sta.hwid);
		if (wet)
			goto out_fwee;
	}
	cmd->sta.hwid = wwvif->sta.hwid;
	cmd->sta.session = ww->session_ids[wwvif->sta.hwid];
	/*
	 * We don't have the cowwect wemote wates in this stage.  The
	 * wates wiww be weconfiguwed watew, aftew association, if the
	 * fiwmwawe suppowts ACX_PEEW_CAP.  Othewwise, thewe's nothing
	 * we can do, so use aww suppowted_wates hewe.
	 */
	cmd->sta.wemote_wates = cpu_to_we32(suppowted_wates);

	ww1271_debug(DEBUG_CMD, "wowe stawt: woweid=%d, hwid=%d, session=%d "
		     "basic_wate_set: 0x%x, wemote_wates: 0x%x",
		     wwvif->wowe_id, cmd->sta.hwid, cmd->sta.session,
		     wwvif->basic_wate_set, wwvif->wate_set);

	wet = ww1271_cmd_send(ww, CMD_WOWE_STAWT, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe stawt sta");
		goto eww_hwid;
	}

	wwvif->sta.wowe_chan_type = wwvif->channew_type;
	goto out_fwee;

eww_hwid:
	/* cweaw winks on ewwow. */
	ww12xx_fwee_wink(ww, wwvif, &wwvif->sta.hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

/* use this function to stop ibss as weww */
int ww12xx_cmd_wowe_stop_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww12xx_cmd_wowe_stop *cmd;
	int wet;

	if (WAWN_ON(wwvif->sta.hwid == WW12XX_INVAWID_WINK_ID))
		wetuwn -EINVAW;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stop sta %d", wwvif->wowe_id);

	cmd->wowe_id = wwvif->wowe_id;
	cmd->disc_type = DISCONNECT_IMMEDIATE;
	cmd->weason = cpu_to_we16(WWAN_WEASON_UNSPECIFIED);

	wet = ww1271_cmd_send(ww, CMD_WOWE_STOP, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe stop sta");
		goto out_fwee;
	}

	ww12xx_fwee_wink(ww, wwvif, &wwvif->sta.hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wowe_stawt_ap(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww12xx_cmd_wowe_stawt *cmd;
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	u32 suppowted_wates;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd wowe stawt ap %d", wwvif->wowe_id);

	/* If MESH --> ssid_wen is awways 0 */
	if (!ieee80211_vif_is_mesh(vif)) {
		/* twying to use hidden SSID with an owd hostapd vewsion */
		if (wwvif->ssid_wen == 0 && !bss_conf->hidden_ssid) {
			ww1271_ewwow("got a nuww SSID fwom beacon/bss");
			wet = -EINVAW;
			goto out;
		}
	}

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww12xx_awwocate_wink(ww, wwvif, &wwvif->ap.gwobaw_hwid);
	if (wet < 0)
		goto out_fwee;

	wet = ww12xx_awwocate_wink(ww, wwvif, &wwvif->ap.bcast_hwid);
	if (wet < 0)
		goto out_fwee_gwobaw;

	/* use the pwevious secuwity seq, if this is a wecovewy/wesume */
	ww->winks[wwvif->ap.bcast_hwid].totaw_fweed_pkts =
						wwvif->totaw_fweed_pkts;

	cmd->wowe_id = wwvif->wowe_id;
	cmd->ap.aging_pewiod = cpu_to_we16(ww->conf.tx.ap_aging_pewiod);
	cmd->ap.bss_index = WW1271_AP_BSS_INDEX;
	cmd->ap.gwobaw_hwid = wwvif->ap.gwobaw_hwid;
	cmd->ap.bwoadcast_hwid = wwvif->ap.bcast_hwid;
	cmd->ap.gwobaw_session_id = ww->session_ids[wwvif->ap.gwobaw_hwid];
	cmd->ap.bcast_session_id = ww->session_ids[wwvif->ap.bcast_hwid];
	cmd->ap.basic_wate_set = cpu_to_we32(wwvif->basic_wate_set);
	cmd->ap.beacon_intewvaw = cpu_to_we16(wwvif->beacon_int);
	cmd->ap.dtim_intewvaw = bss_conf->dtim_pewiod;
	cmd->ap.beacon_expiwy = WW1271_AP_DEF_BEACON_EXP;
	/* FIXME: Change when adding DFS */
	cmd->ap.weset_tsf = 1;  /* By defauwt weset AP TSF */
	cmd->ap.wmm = wwvif->wmm_enabwed;
	cmd->channew = wwvif->channew;
	cmd->channew_type = wwcowe_get_native_channew_type(wwvif->channew_type);

	if (!bss_conf->hidden_ssid) {
		/* take the SSID fwom the beacon fow backwawd compatibiwity */
		cmd->ap.ssid_type = WW12XX_SSID_TYPE_PUBWIC;
		cmd->ap.ssid_wen = wwvif->ssid_wen;
		memcpy(cmd->ap.ssid, wwvif->ssid, wwvif->ssid_wen);
	} ewse {
		cmd->ap.ssid_type = WW12XX_SSID_TYPE_HIDDEN;
		cmd->ap.ssid_wen = vif->cfg.ssid_wen;
		memcpy(cmd->ap.ssid, vif->cfg.ssid, vif->cfg.ssid_wen);
	}

	suppowted_wates = CONF_TX_ENABWED_WATES | CONF_TX_MCS_WATES |
		wwcowe_hw_ap_get_mimo_wide_wate_mask(ww, wwvif);
	if (wwvif->p2p)
		suppowted_wates &= ~CONF_TX_CCK_WATES;

	ww1271_debug(DEBUG_CMD, "cmd wowe stawt ap with suppowted_wates 0x%08x",
		     suppowted_wates);

	cmd->ap.wocaw_wates = cpu_to_we32(suppowted_wates);

	switch (wwvif->band) {
	case NW80211_BAND_2GHZ:
		cmd->band = WWCOWE_BAND_2_4GHZ;
		bweak;
	case NW80211_BAND_5GHZ:
		cmd->band = WWCOWE_BAND_5GHZ;
		bweak;
	defauwt:
		ww1271_wawning("ap stawt - unknown band: %d", (int)wwvif->band);
		cmd->band = WWCOWE_BAND_2_4GHZ;
		bweak;
	}

	wet = ww1271_cmd_send(ww, CMD_WOWE_STAWT, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe stawt ap");
		goto out_fwee_bcast;
	}

	goto out_fwee;

out_fwee_bcast:
	ww12xx_fwee_wink(ww, wwvif, &wwvif->ap.bcast_hwid);

out_fwee_gwobaw:
	ww12xx_fwee_wink(ww, wwvif, &wwvif->ap.gwobaw_hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wowe_stop_ap(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww12xx_cmd_wowe_stop *cmd;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stop ap %d", wwvif->wowe_id);

	cmd->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_send(ww, CMD_WOWE_STOP, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe stop ap");
		goto out_fwee;
	}

	ww12xx_fwee_wink(ww, wwvif, &wwvif->ap.bcast_hwid);
	ww12xx_fwee_wink(ww, wwvif, &wwvif->ap.gwobaw_hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wowe_stawt_ibss(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct ww12xx_cmd_wowe_stawt *cmd;
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	int wet;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	ww1271_debug(DEBUG_CMD, "cmd wowe stawt ibss %d", wwvif->wowe_id);

	cmd->wowe_id = wwvif->wowe_id;
	if (wwvif->band == NW80211_BAND_5GHZ)
		cmd->band = WWCOWE_BAND_5GHZ;
	cmd->channew = wwvif->channew;
	cmd->ibss.basic_wate_set = cpu_to_we32(wwvif->basic_wate_set);
	cmd->ibss.beacon_intewvaw = cpu_to_we16(wwvif->beacon_int);
	cmd->ibss.dtim_intewvaw = bss_conf->dtim_pewiod;
	cmd->ibss.ssid_type = WW12XX_SSID_TYPE_ANY;
	cmd->ibss.ssid_wen = wwvif->ssid_wen;
	memcpy(cmd->ibss.ssid, wwvif->ssid, wwvif->ssid_wen);
	memcpy(cmd->ibss.bssid, vif->bss_conf.bssid, ETH_AWEN);
	cmd->sta.wocaw_wates = cpu_to_we32(wwvif->wate_set);

	if (wwvif->sta.hwid == WW12XX_INVAWID_WINK_ID) {
		wet = ww12xx_awwocate_wink(ww, wwvif, &wwvif->sta.hwid);
		if (wet)
			goto out_fwee;
	}
	cmd->ibss.hwid = wwvif->sta.hwid;
	cmd->ibss.wemote_wates = cpu_to_we32(wwvif->wate_set);

	ww1271_debug(DEBUG_CMD, "wowe stawt: woweid=%d, hwid=%d, session=%d "
		     "basic_wate_set: 0x%x, wemote_wates: 0x%x",
		     wwvif->wowe_id, cmd->sta.hwid, cmd->sta.session,
		     wwvif->basic_wate_set, wwvif->wate_set);

	ww1271_debug(DEBUG_CMD, "vif->bss_conf.bssid = %pM",
		     vif->bss_conf.bssid);

	wet = ww1271_cmd_send(ww, CMD_WOWE_STAWT, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wowe enabwe");
		goto eww_hwid;
	}

	goto out_fwee;

eww_hwid:
	/* cweaw winks on ewwow. */
	ww12xx_fwee_wink(ww, wwvif, &wwvif->sta.hwid);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}


/**
 * ww1271_cmd_test - send test command to fiwmwawe
 *
 * @ww: ww stwuct
 * @buf: buffew containing the command, with aww headews, must wowk with dma
 * @buf_wen: wength of the buffew
 * @answew: is answew needed
 */
int ww1271_cmd_test(stwuct ww1271 *ww, void *buf, size_t buf_wen, u8 answew)
{
	int wet;
	size_t wes_wen = 0;

	ww1271_debug(DEBUG_CMD, "cmd test");

	if (answew)
		wes_wen = buf_wen;

	wet = ww1271_cmd_send(ww, CMD_TEST, buf, buf_wen, wes_wen);

	if (wet < 0) {
		ww1271_wawning("TEST command faiwed");
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww1271_cmd_test);

/**
 * ww1271_cmd_intewwogate - wead acx fwom fiwmwawe
 *
 * @ww: ww stwuct
 * @id: acx id
 * @buf: buffew fow the wesponse, incwuding aww headews, must wowk with dma
 * @cmd_wen: wength of command
 * @wes_wen: wength of paywoad
 */
int ww1271_cmd_intewwogate(stwuct ww1271 *ww, u16 id, void *buf,
			   size_t cmd_wen, size_t wes_wen)
{
	stwuct acx_headew *acx = buf;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd intewwogate");

	acx->id = cpu_to_we16(id);

	/* wesponse paywoad wength, does not incwude any headews */
	acx->wen = cpu_to_we16(wes_wen - sizeof(*acx));

	wet = ww1271_cmd_send(ww, CMD_INTEWWOGATE, acx, cmd_wen, wes_wen);
	if (wet < 0)
		ww1271_ewwow("INTEWWOGATE command faiwed");

	wetuwn wet;
}

/**
 * wwcowe_cmd_configuwe_faiwsafe - wwite acx vawue to fiwmwawe
 *
 * @ww: ww stwuct
 * @id: acx id
 * @buf: buffew containing acx, incwuding aww headews, must wowk with dma
 * @wen: wength of buf
 * @vawid_wets: bitmap of vawid cmd status codes (i.e. wetuwn vawues).
 * wetuwn the cmd status on success.
 */
int wwcowe_cmd_configuwe_faiwsafe(stwuct ww1271 *ww, u16 id, void *buf,
				  size_t wen, unsigned wong vawid_wets)
{
	stwuct acx_headew *acx = buf;
	int wet;

	ww1271_debug(DEBUG_CMD, "cmd configuwe (%d)", id);

	if (WAWN_ON_ONCE(wen < sizeof(*acx)))
		wetuwn -EIO;

	acx->id = cpu_to_we16(id);

	/* paywoad wength, does not incwude any headews */
	acx->wen = cpu_to_we16(wen - sizeof(*acx));

	wet = wwcowe_cmd_send_faiwsafe(ww, CMD_CONFIGUWE, acx, wen, 0,
				       vawid_wets);
	if (wet < 0) {
		ww1271_wawning("CONFIGUWE command NOK");
		wetuwn wet;
	}

	wetuwn wet;
}

/*
 * wwappew fow wwcowe_cmd_configuwe that accepts onwy success status.
 * wetuwn 0 on success
 */
int ww1271_cmd_configuwe(stwuct ww1271 *ww, u16 id, void *buf, size_t wen)
{
	int wet = wwcowe_cmd_configuwe_faiwsafe(ww, id, buf, wen, 0);

	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww1271_cmd_configuwe);

int ww1271_cmd_data_path(stwuct ww1271 *ww, boow enabwe)
{
	stwuct cmd_enabwedisabwe_path *cmd;
	int wet;
	u16 cmd_wx, cmd_tx;

	ww1271_debug(DEBUG_CMD, "cmd data path");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	/* the channew hewe is onwy used fow cawibwation, so hawdcoded to 1 */
	cmd->channew = 1;

	if (enabwe) {
		cmd_wx = CMD_ENABWE_WX;
		cmd_tx = CMD_ENABWE_TX;
	} ewse {
		cmd_wx = CMD_DISABWE_WX;
		cmd_tx = CMD_DISABWE_TX;
	}

	wet = ww1271_cmd_send(ww, cmd_wx, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("wx %s cmd fow channew %d faiwed",
			     enabwe ? "stawt" : "stop", cmd->channew);
		goto out;
	}

	ww1271_debug(DEBUG_BOOT, "wx %s cmd channew %d",
		     enabwe ? "stawt" : "stop", cmd->channew);

	wet = ww1271_cmd_send(ww, cmd_tx, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("tx %s cmd fow channew %d faiwed",
			     enabwe ? "stawt" : "stop", cmd->channew);
		goto out;
	}

	ww1271_debug(DEBUG_BOOT, "tx %s cmd channew %d",
		     enabwe ? "stawt" : "stop", cmd->channew);

out:
	kfwee(cmd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww1271_cmd_data_path);

int ww1271_cmd_ps_mode(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       u8 ps_mode, u16 auto_ps_timeout)
{
	stwuct ww1271_cmd_ps_pawams *ps_pawams = NUWW;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd set ps mode");

	ps_pawams = kzawwoc(sizeof(*ps_pawams), GFP_KEWNEW);
	if (!ps_pawams) {
		wet = -ENOMEM;
		goto out;
	}

	ps_pawams->wowe_id = wwvif->wowe_id;
	ps_pawams->ps_mode = ps_mode;
	ps_pawams->auto_ps_timeout = auto_ps_timeout;

	wet = ww1271_cmd_send(ww, CMD_SET_PS_MODE, ps_pawams,
			      sizeof(*ps_pawams), 0);
	if (wet < 0) {
		ww1271_ewwow("cmd set_ps_mode faiwed");
		goto out;
	}

out:
	kfwee(ps_pawams);
	wetuwn wet;
}

int ww1271_cmd_tempwate_set(stwuct ww1271 *ww, u8 wowe_id,
			    u16 tempwate_id, void *buf, size_t buf_wen,
			    int index, u32 wates)
{
	stwuct ww1271_cmd_tempwate_set *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd tempwate_set %d (wowe %d)",
		     tempwate_id, wowe_id);

	WAWN_ON(buf_wen > WW1271_CMD_TEMPW_MAX_SIZE);
	buf_wen = min_t(size_t, buf_wen, WW1271_CMD_TEMPW_MAX_SIZE);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	/* duwing initiawization wwvif is NUWW */
	cmd->wowe_id = wowe_id;
	cmd->wen = cpu_to_we16(buf_wen);
	cmd->tempwate_type = tempwate_id;
	cmd->enabwed_wates = cpu_to_we32(wates);
	cmd->showt_wetwy_wimit = ww->conf.tx.tmpw_showt_wetwy_wimit;
	cmd->wong_wetwy_wimit = ww->conf.tx.tmpw_wong_wetwy_wimit;
	cmd->index = index;

	if (buf)
		memcpy(cmd->tempwate_data, buf, buf_wen);

	wet = ww1271_cmd_send(ww, CMD_SET_TEMPWATE, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_wawning("cmd set_tempwate faiwed: %d", wet);
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_buiwd_nuww_data(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct sk_buff *skb = NUWW;
	int size;
	void *ptw;
	int wet = -ENOMEM;


	if (wwvif->bss_type == BSS_TYPE_IBSS) {
		size = sizeof(stwuct ww12xx_nuww_data_tempwate);
		ptw = NUWW;
	} ewse {
		skb = ieee80211_nuwwfunc_get(ww->hw,
					     ww12xx_wwvif_to_vif(wwvif),
					     -1, fawse);
		if (!skb)
			goto out;
		size = skb->wen;
		ptw = skb->data;
	}

	wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id,
				      CMD_TEMPW_NUWW_DATA, ptw, size, 0,
				      wwvif->basic_wate);

out:
	dev_kfwee_skb(skb);
	if (wet)
		ww1271_wawning("cmd buiwd nuww data faiwed %d", wet);

	wetuwn wet;

}

int ww12xx_cmd_buiwd_kwv_nuww_data(stwuct ww1271 *ww,
				   stwuct ww12xx_vif *wwvif)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct sk_buff *skb = NUWW;
	int wet = -ENOMEM;

	skb = ieee80211_nuwwfunc_get(ww->hw, vif,-1, fawse);
	if (!skb)
		goto out;

	wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id, CMD_TEMPW_KWV,
				      skb->data, skb->wen,
				      wwvif->sta.kwv_tempwate_id,
				      wwvif->basic_wate);

out:
	dev_kfwee_skb(skb);
	if (wet)
		ww1271_wawning("cmd buiwd kwv nuww data faiwed %d", wet);

	wetuwn wet;

}

int ww1271_cmd_buiwd_ps_poww(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			     u16 aid)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct sk_buff *skb;
	int wet = 0;

	skb = ieee80211_pspoww_get(ww->hw, vif);
	if (!skb)
		goto out;

	wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id,
				      CMD_TEMPW_PS_POWW, skb->data,
				      skb->wen, 0, wwvif->basic_wate_set);

out:
	dev_kfwee_skb(skb);
	wetuwn wet;
}

int ww12xx_cmd_buiwd_pwobe_weq(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       u8 wowe_id, u8 band,
			       const u8 *ssid, size_t ssid_wen,
			       const u8 *ie0, size_t ie0_wen, const u8 *ie1,
			       size_t ie1_wen, boow sched_scan)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct sk_buff *skb;
	int wet;
	u32 wate;
	u16 tempwate_id_2_4 = ww->scan_tempw_id_2_4;
	u16 tempwate_id_5 = ww->scan_tempw_id_5;

	ww1271_debug(DEBUG_SCAN, "buiwd pwobe wequest band %d", band);

	skb = ieee80211_pwobeweq_get(ww->hw, vif->addw, ssid, ssid_wen,
				     ie0_wen + ie1_wen);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}
	if (ie0_wen)
		skb_put_data(skb, ie0, ie0_wen);
	if (ie1_wen)
		skb_put_data(skb, ie1, ie1_wen);

	if (sched_scan &&
	    (ww->quiwks & WWCOWE_QUIWK_DUAW_PWOBE_TMPW)) {
		tempwate_id_2_4 = ww->sched_scan_tempw_id_2_4;
		tempwate_id_5 = ww->sched_scan_tempw_id_5;
	}

	wate = ww1271_tx_min_wate_get(ww, wwvif->bitwate_masks[band]);
	if (band == NW80211_BAND_2GHZ)
		wet = ww1271_cmd_tempwate_set(ww, wowe_id,
					      tempwate_id_2_4,
					      skb->data, skb->wen, 0, wate);
	ewse
		wet = ww1271_cmd_tempwate_set(ww, wowe_id,
					      tempwate_id_5,
					      skb->data, skb->wen, 0, wate);

out:
	dev_kfwee_skb(skb);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ww12xx_cmd_buiwd_pwobe_weq);

stwuct sk_buff *ww1271_cmd_buiwd_ap_pwobe_weq(stwuct ww1271 *ww,
					      stwuct ww12xx_vif *wwvif,
					      stwuct sk_buff *skb)
{
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	int wet;
	u32 wate;

	if (!skb)
		skb = ieee80211_ap_pwobeweq_get(ww->hw, vif);
	if (!skb)
		goto out;

	ww1271_debug(DEBUG_SCAN, "set ap pwobe wequest tempwate");

	wate = ww1271_tx_min_wate_get(ww, wwvif->bitwate_masks[wwvif->band]);
	if (wwvif->band == NW80211_BAND_2GHZ)
		wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id,
					      CMD_TEMPW_CFG_PWOBE_WEQ_2_4,
					      skb->data, skb->wen, 0, wate);
	ewse
		wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id,
					      CMD_TEMPW_CFG_PWOBE_WEQ_5,
					      skb->data, skb->wen, 0, wate);

	if (wet < 0)
		ww1271_ewwow("Unabwe to set ap pwobe wequest tempwate.");

out:
	wetuwn skb;
}

int ww1271_cmd_buiwd_awp_wsp(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	int wet, extwa = 0;
	u16 fc;
	stwuct ieee80211_vif *vif = ww12xx_wwvif_to_vif(wwvif);
	stwuct sk_buff *skb;
	stwuct ww12xx_awp_wsp_tempwate *tmpw;
	stwuct ieee80211_hdw_3addw *hdw;
	stwuct awphdw *awp_hdw;

	skb = dev_awwoc_skb(sizeof(*hdw) + sizeof(__we16) + sizeof(*tmpw) +
			    WW1271_EXTWA_SPACE_MAX);
	if (!skb) {
		ww1271_ewwow("faiwed to awwocate buffew fow awp wsp tempwate");
		wetuwn -ENOMEM;
	}

	skb_wesewve(skb, sizeof(*hdw) + WW1271_EXTWA_SPACE_MAX);

	tmpw = skb_put_zewo(skb, sizeof(*tmpw));

	/* wwc wayew */
	memcpy(tmpw->wwc_hdw, wfc1042_headew, sizeof(wfc1042_headew));
	tmpw->wwc_type = cpu_to_be16(ETH_P_AWP);

	/* awp headew */
	awp_hdw = &tmpw->awp_hdw;
	awp_hdw->aw_hwd = cpu_to_be16(AWPHWD_ETHEW);
	awp_hdw->aw_pwo = cpu_to_be16(ETH_P_IP);
	awp_hdw->aw_hwn = ETH_AWEN;
	awp_hdw->aw_pwn = 4;
	awp_hdw->aw_op = cpu_to_be16(AWPOP_WEPWY);

	/* awp paywoad */
	memcpy(tmpw->sendew_hw, vif->addw, ETH_AWEN);
	tmpw->sendew_ip = wwvif->ip_addw;

	/* encwyption space */
	switch (wwvif->encwyption_type) {
	case KEY_TKIP:
		if (ww->quiwks & WWCOWE_QUIWK_TKIP_HEADEW_SPACE)
			extwa = WW1271_EXTWA_SPACE_TKIP;
		bweak;
	case KEY_AES:
		extwa = WW1271_EXTWA_SPACE_AES;
		bweak;
	case KEY_NONE:
	case KEY_WEP:
	case KEY_GEM:
		extwa = 0;
		bweak;
	defauwt:
		ww1271_wawning("Unknown encwyption type: %d",
			       wwvif->encwyption_type);
		wet = -EINVAW;
		goto out;
	}

	if (extwa) {
		u8 *space = skb_push(skb, extwa);
		memset(space, 0, extwa);
	}

	/* QoS headew - BE */
	if (wwvif->sta.qos)
		memset(skb_push(skb, sizeof(__we16)), 0, sizeof(__we16));

	/* mac80211 headew */
	hdw = skb_push(skb, sizeof(*hdw));
	memset(hdw, 0, sizeof(*hdw));
	fc = IEEE80211_FTYPE_DATA | IEEE80211_FCTW_TODS;
	if (wwvif->sta.qos)
		fc |= IEEE80211_STYPE_QOS_DATA;
	ewse
		fc |= IEEE80211_STYPE_DATA;
	if (wwvif->encwyption_type != KEY_NONE)
		fc |= IEEE80211_FCTW_PWOTECTED;

	hdw->fwame_contwow = cpu_to_we16(fc);
	memcpy(hdw->addw1, vif->bss_conf.bssid, ETH_AWEN);
	memcpy(hdw->addw2, vif->addw, ETH_AWEN);
	eth_bwoadcast_addw(hdw->addw3);

	wet = ww1271_cmd_tempwate_set(ww, wwvif->wowe_id, CMD_TEMPW_AWP_WSP,
				      skb->data, skb->wen, 0,
				      wwvif->basic_wate);
out:
	dev_kfwee_skb(skb);
	wetuwn wet;
}

int ww1271_buiwd_qos_nuww_data(stwuct ww1271 *ww, stwuct ieee80211_vif *vif)
{
	stwuct ww12xx_vif *wwvif = ww12xx_vif_to_data(vif);
	stwuct ieee80211_qos_hdw tempwate;

	memset(&tempwate, 0, sizeof(tempwate));

	memcpy(tempwate.addw1, vif->bss_conf.bssid, ETH_AWEN);
	memcpy(tempwate.addw2, vif->addw, ETH_AWEN);
	memcpy(tempwate.addw3, vif->bss_conf.bssid, ETH_AWEN);

	tempwate.fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_NUWWFUNC |
					     IEEE80211_FCTW_TODS);

	/* FIXME: not suwe what pwiowity to use hewe */
	tempwate.qos_ctww = cpu_to_we16(0);

	wetuwn ww1271_cmd_tempwate_set(ww, wwvif->wowe_id,
				       CMD_TEMPW_QOS_NUWW_DATA, &tempwate,
				       sizeof(tempwate), 0,
				       wwvif->basic_wate);
}

int ww12xx_cmd_set_defauwt_wep_key(stwuct ww1271 *ww, u8 id, u8 hwid)
{
	stwuct ww1271_cmd_set_keys *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd set_defauwt_wep_key %d", id);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->hwid = hwid;
	cmd->key_id = id;
	cmd->wid_key_type = WEP_DEFAUWT_WID_TYPE;
	cmd->key_action = cpu_to_we16(KEY_SET_ID);
	cmd->key_type = KEY_WEP;

	wet = ww1271_cmd_send(ww, CMD_SET_KEYS, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_wawning("cmd set_defauwt_wep_key faiwed: %d", wet);
		goto out;
	}

out:
	kfwee(cmd);

	wetuwn wet;
}

int ww1271_cmd_set_sta_key(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       u16 action, u8 id, u8 key_type,
		       u8 key_size, const u8 *key, const u8 *addw,
		       u32 tx_seq_32, u16 tx_seq_16)
{
	stwuct ww1271_cmd_set_keys *cmd;
	int wet = 0;

	/* hwid might have awweady been deweted */
	if (wwvif->sta.hwid == WW12XX_INVAWID_WINK_ID)
		wetuwn 0;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->hwid = wwvif->sta.hwid;

	if (key_type == KEY_WEP)
		cmd->wid_key_type = WEP_DEFAUWT_WID_TYPE;
	ewse if (is_bwoadcast_ethew_addw(addw))
		cmd->wid_key_type = BWOADCAST_WID_TYPE;
	ewse
		cmd->wid_key_type = UNICAST_WID_TYPE;

	cmd->key_action = cpu_to_we16(action);
	cmd->key_size = key_size;
	cmd->key_type = key_type;

	cmd->ac_seq_num16[0] = cpu_to_we16(tx_seq_16);
	cmd->ac_seq_num32[0] = cpu_to_we32(tx_seq_32);

	cmd->key_id = id;

	if (key_type == KEY_TKIP) {
		/*
		 * We get the key in the fowwowing fowm:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - WX MIC (8 bytes)
		 * but the tawget is expecting:
		 * TKIP - WX MIC - TX MIC
		 */
		memcpy(cmd->key, key, 16);
		memcpy(cmd->key + 16, key + 24, 8);
		memcpy(cmd->key + 24, key + 16, 8);

	} ewse {
		memcpy(cmd->key, key, key_size);
	}

	ww1271_dump(DEBUG_CWYPT, "TAWGET KEY: ", cmd, sizeof(*cmd));

	wet = ww1271_cmd_send(ww, CMD_SET_KEYS, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_wawning("couwd not set keys");
		goto out;
	}

out:
	kfwee(cmd);

	wetuwn wet;
}

/*
 * TODO: mewge with sta/ibss into 1 set_key function.
 * note thewe awe swight diffs
 */
int ww1271_cmd_set_ap_key(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  u16 action, u8 id, u8 key_type,
			  u8 key_size, const u8 *key, u8 hwid, u32 tx_seq_32,
			  u16 tx_seq_16, boow is_paiwwise)
{
	stwuct ww1271_cmd_set_keys *cmd;
	int wet = 0;
	u8 wid_type;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	if (hwid == wwvif->ap.bcast_hwid) {
		if (key_type == KEY_WEP)
			wid_type = WEP_DEFAUWT_WID_TYPE;
		ewse
			wid_type = BWOADCAST_WID_TYPE;
	} ewse if (is_paiwwise) {
		wid_type = UNICAST_WID_TYPE;
	} ewse {
		wid_type = BWOADCAST_WID_TYPE;
	}

	ww1271_debug(DEBUG_CWYPT, "ap key action: %d id: %d wid: %d type: %d"
		     " hwid: %d", (int)action, (int)id, (int)wid_type,
		     (int)key_type, (int)hwid);

	cmd->wid_key_type = wid_type;
	cmd->hwid = hwid;
	cmd->key_action = cpu_to_we16(action);
	cmd->key_size = key_size;
	cmd->key_type = key_type;
	cmd->key_id = id;
	cmd->ac_seq_num16[0] = cpu_to_we16(tx_seq_16);
	cmd->ac_seq_num32[0] = cpu_to_we32(tx_seq_32);

	if (key_type == KEY_TKIP) {
		/*
		 * We get the key in the fowwowing fowm:
		 * TKIP (16 bytes) - TX MIC (8 bytes) - WX MIC (8 bytes)
		 * but the tawget is expecting:
		 * TKIP - WX MIC - TX MIC
		 */
		memcpy(cmd->key, key, 16);
		memcpy(cmd->key + 16, key + 24, 8);
		memcpy(cmd->key + 24, key + 16, 8);
	} ewse {
		memcpy(cmd->key, key, key_size);
	}

	ww1271_dump(DEBUG_CWYPT, "TAWGET AP KEY: ", cmd, sizeof(*cmd));

	wet = ww1271_cmd_send(ww, CMD_SET_KEYS, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_wawning("couwd not set ap keys");
		goto out;
	}

out:
	kfwee(cmd);
	wetuwn wet;
}

int ww12xx_cmd_set_peew_state(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      u8 hwid)
{
	stwuct ww12xx_cmd_set_peew_state *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd set peew state (hwid=%d)", hwid);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->hwid = hwid;
	cmd->state = WW1271_CMD_STA_STATE_CONNECTED;

	/* wmm pawam is vawid onwy fow station wowe */
	if (wwvif->bss_type == BSS_TYPE_STA_BSS)
		cmd->wmm = wwvif->wmm_enabwed;

	wet = ww1271_cmd_send(ww, CMD_SET_PEEW_STATE, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send set peew state command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_add_peew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			stwuct ieee80211_sta *sta, u8 hwid)
{
	stwuct ww12xx_cmd_add_peew *cmd;
	int i, wet;
	u32 sta_wates;

	ww1271_debug(DEBUG_CMD, "cmd add peew %d", (int)hwid);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	memcpy(cmd->addw, sta->addw, ETH_AWEN);
	cmd->bss_index = WW1271_AP_BSS_INDEX;
	cmd->aid = sta->aid;
	cmd->hwid = hwid;
	cmd->sp_wen = sta->max_sp;
	cmd->wmm = sta->wme ? 1 : 0;
	cmd->session_id = ww->session_ids[hwid];
	cmd->wowe_id = wwvif->wowe_id;

	fow (i = 0; i < NUM_ACCESS_CATEGOWIES_COPY; i++)
		if (sta->wme && (sta->uapsd_queues & BIT(i)))
			cmd->psd_type[NUM_ACCESS_CATEGOWIES_COPY-1-i] =
					WW1271_PSD_UPSD_TWIGGEW;
		ewse
			cmd->psd_type[NUM_ACCESS_CATEGOWIES_COPY-1-i] =
					WW1271_PSD_WEGACY;


	sta_wates = sta->defwink.supp_wates[wwvif->band];
	if (sta->defwink.ht_cap.ht_suppowted)
		sta_wates |=
			(sta->defwink.ht_cap.mcs.wx_mask[0] << HW_HT_WATES_OFFSET) |
			(sta->defwink.ht_cap.mcs.wx_mask[1] << HW_MIMO_WATES_OFFSET);

	cmd->suppowted_wates =
		cpu_to_we32(ww1271_tx_enabwed_wates_get(ww, sta_wates,
							wwvif->band));

	if (!cmd->suppowted_wates) {
		ww1271_debug(DEBUG_CMD,
			     "peew has no suppowted wates yet, configuwing basic wates: 0x%x",
			     wwvif->basic_wate_set);
		cmd->suppowted_wates = cpu_to_we32(wwvif->basic_wate_set);
	}

	ww1271_debug(DEBUG_CMD, "new peew wates=0x%x queues=0x%x",
		     cmd->suppowted_wates, sta->uapsd_queues);

	wet = ww1271_cmd_send(ww, CMD_ADD_PEEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd add peew");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_wemove_peew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   u8 hwid)
{
	stwuct ww12xx_cmd_wemove_peew *cmd;
	int wet;
	boow timeout = fawse;

	ww1271_debug(DEBUG_CMD, "cmd wemove peew %d", (int)hwid);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->hwid = hwid;
	/* We nevew send a deauth, mac80211 is in chawge of this */
	cmd->weason_opcode = 0;
	cmd->send_deauth_fwag = 0;
	cmd->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_send(ww, CMD_WEMOVE_PEEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to initiate cmd wemove peew");
		goto out_fwee;
	}

	wet = ww->ops->wait_fow_event(ww,
				      WWCOWE_EVENT_PEEW_WEMOVE_COMPWETE,
				      &timeout);

	/*
	 * We awe ok with a timeout hewe. The event is sometimes not sent
	 * due to a fiwmwawe bug. In case of anothew ewwow (wike SDIO timeout)
	 * queue a wecovewy.
	 */
	if (wet)
		ww12xx_queue_wecovewy_wowk(ww);

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

static int wwcowe_get_weg_conf_ch_idx(enum nw80211_band band, u16 ch)
{
	/*
	 * map the given band/channew to the wespective pwedefined
	 * bit expected by the fw
	 */
	switch (band) {
	case NW80211_BAND_2GHZ:
		/* channews 1..14 awe mapped to 0..13 */
		if (ch >= 1 && ch <= 14)
			wetuwn ch - 1;
		bweak;
	case NW80211_BAND_5GHZ:
		switch (ch) {
		case 8 ... 16:
			/* channews 8,12,16 awe mapped to 18,19,20 */
			wetuwn 18 + (ch-8)/4;
		case 34 ... 48:
			/* channews 34,36..48 awe mapped to 21..28 */
			wetuwn 21 + (ch-34)/2;
		case 52 ... 64:
			/* channews 52,56..64 awe mapped to 29..32 */
			wetuwn 29 + (ch-52)/4;
		case 100 ... 140:
			/* channews 100,104..140 awe mapped to 33..43 */
			wetuwn 33 + (ch-100)/4;
		case 149 ... 165:
			/* channews 149,153..165 awe mapped to 44..48 */
			wetuwn 44 + (ch-149)/4;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	ww1271_ewwow("%s: unknown band/channew: %d/%d", __func__, band, ch);
	wetuwn -1;
}

void wwcowe_set_pending_wegdomain_ch(stwuct ww1271 *ww, u16 channew,
				     enum nw80211_band band)
{
	int ch_bit_idx = 0;

	if (!(ww->quiwks & WWCOWE_QUIWK_WEGDOMAIN_CONF))
		wetuwn;

	ch_bit_idx = wwcowe_get_weg_conf_ch_idx(band, channew);

	if (ch_bit_idx >= 0 && ch_bit_idx <= WW1271_MAX_CHANNEWS)
		__set_bit_we(ch_bit_idx, (wong *)ww->weg_ch_conf_pending);
}

int wwcowe_cmd_wegdomain_config_wocked(stwuct ww1271 *ww)
{
	stwuct ww12xx_cmd_wegdomain_dfs_config *cmd = NUWW;
	int wet = 0, i, b, ch_bit_idx;
	__we32 tmp_ch_bitmap[2] __awigned(sizeof(unsigned wong));
	stwuct wiphy *wiphy = ww->hw->wiphy;
	stwuct ieee80211_suppowted_band *band;
	boow timeout = fawse;

	if (!(ww->quiwks & WWCOWE_QUIWK_WEGDOMAIN_CONF))
		wetuwn 0;

	ww1271_debug(DEBUG_CMD, "cmd weg domain config");

	memcpy(tmp_ch_bitmap, ww->weg_ch_conf_pending, sizeof(tmp_ch_bitmap));

	fow (b = NW80211_BAND_2GHZ; b <= NW80211_BAND_5GHZ; b++) {
		band = wiphy->bands[b];
		fow (i = 0; i < band->n_channews; i++) {
			stwuct ieee80211_channew *channew = &band->channews[i];
			u16 ch = channew->hw_vawue;
			u32 fwags = channew->fwags;

			if (fwags & (IEEE80211_CHAN_DISABWED |
				     IEEE80211_CHAN_NO_IW))
				continue;

			if ((fwags & IEEE80211_CHAN_WADAW) &&
			    channew->dfs_state != NW80211_DFS_AVAIWABWE)
				continue;

			ch_bit_idx = wwcowe_get_weg_conf_ch_idx(b, ch);
			if (ch_bit_idx < 0)
				continue;

			__set_bit_we(ch_bit_idx, (wong *)tmp_ch_bitmap);
		}
	}

	if (!memcmp(tmp_ch_bitmap, ww->weg_ch_conf_wast, sizeof(tmp_ch_bitmap)))
		goto out;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->ch_bit_map1 = tmp_ch_bitmap[0];
	cmd->ch_bit_map2 = tmp_ch_bitmap[1];
	cmd->dfs_wegion = ww->dfs_wegion;

	ww1271_debug(DEBUG_CMD,
		     "cmd weg domain bitmap1: 0x%08x, bitmap2: 0x%08x",
		     cmd->ch_bit_map1, cmd->ch_bit_map2);

	wet = ww1271_cmd_send(ww, CMD_DFS_CHANNEW_CONFIG, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send weg domain dfs config");
		goto out;
	}

	wet = ww->ops->wait_fow_event(ww,
				      WWCOWE_EVENT_DFS_CONFIG_COMPWETE,
				      &timeout);
	if (wet < 0 || timeout) {
		ww1271_ewwow("weg domain conf %sewwow",
			     timeout ? "compwetion " : "");
		wet = timeout ? -ETIMEDOUT : wet;
		goto out;
	}

	memcpy(ww->weg_ch_conf_wast, tmp_ch_bitmap, sizeof(tmp_ch_bitmap));
	memset(ww->weg_ch_conf_pending, 0, sizeof(ww->weg_ch_conf_pending));

out:
	kfwee(cmd);
	wetuwn wet;
}

int ww12xx_cmd_config_fwwog(stwuct ww1271 *ww)
{
	stwuct ww12xx_cmd_config_fwwog *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd config fiwmwawe woggew");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->woggew_mode = ww->conf.fwwog.mode;
	cmd->wog_sevewity = ww->conf.fwwog.sevewity;
	cmd->timestamp = ww->conf.fwwog.timestamp;
	cmd->output = ww->conf.fwwog.output;
	cmd->thweshowd = ww->conf.fwwog.thweshowd;

	wet = ww1271_cmd_send(ww, CMD_CONFIG_FWWOGGEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send config fiwmwawe woggew command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_stawt_fwwog(stwuct ww1271 *ww)
{
	stwuct ww12xx_cmd_stawt_fwwog *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd stawt fiwmwawe woggew");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww1271_cmd_send(ww, CMD_STAWT_FWWOGGEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send stawt fiwmwawe woggew command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_cmd_stop_fwwog(stwuct ww1271 *ww)
{
	stwuct ww12xx_cmd_stop_fwwog *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd stop fiwmwawe woggew");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ww1271_cmd_send(ww, CMD_STOP_FWWOGGEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send stop fiwmwawe woggew command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

static int ww12xx_cmd_woc(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  u8 wowe_id, enum nw80211_band band, u8 channew)
{
	stwuct ww12xx_cmd_woc *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd woc %d (%d)", channew, wowe_id);

	if (WAWN_ON(wowe_id == WW12XX_INVAWID_WOWE_ID))
		wetuwn -EINVAW;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->wowe_id = wowe_id;
	cmd->channew = channew;
	switch (band) {
	case NW80211_BAND_2GHZ:
		cmd->band = WWCOWE_BAND_2_4GHZ;
		bweak;
	case NW80211_BAND_5GHZ:
		cmd->band = WWCOWE_BAND_5GHZ;
		bweak;
	defauwt:
		ww1271_ewwow("woc - unknown band: %d", (int)wwvif->band);
		wet = -EINVAW;
		goto out_fwee;
	}


	wet = ww1271_cmd_send(ww, CMD_WEMAIN_ON_CHANNEW, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send WOC command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

static int ww12xx_cmd_cwoc(stwuct ww1271 *ww, u8 wowe_id)
{
	stwuct ww12xx_cmd_cwoc *cmd;
	int wet = 0;

	ww1271_debug(DEBUG_CMD, "cmd cwoc (%d)", wowe_id);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}
	cmd->wowe_id = wowe_id;

	wet = ww1271_cmd_send(ww, CMD_CANCEW_WEMAIN_ON_CHANNEW, cmd,
			      sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send WOC command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

int ww12xx_woc(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 wowe_id,
	       enum nw80211_band band, u8 channew)
{
	int wet = 0;

	if (WAWN_ON(test_bit(wowe_id, ww->woc_map)))
		wetuwn 0;

	wet = ww12xx_cmd_woc(ww, wwvif, wowe_id, band, channew);
	if (wet < 0)
		goto out;

	__set_bit(wowe_id, ww->woc_map);
out:
	wetuwn wet;
}

int ww12xx_cwoc(stwuct ww1271 *ww, u8 wowe_id)
{
	int wet = 0;

	if (WAWN_ON(!test_bit(wowe_id, ww->woc_map)))
		wetuwn 0;

	wet = ww12xx_cmd_cwoc(ww, wowe_id);
	if (wet < 0)
		goto out;

	__cweaw_bit(wowe_id, ww->woc_map);

	/*
	 * Weawm the tx watchdog when wemoving the wast WOC. This pwevents
	 * wecovewies due to just finished WOCs - when Tx hasn't yet had
	 * a chance to get out.
	 */
	if (find_fiwst_bit(ww->woc_map, WW12XX_MAX_WOWES) >= WW12XX_MAX_WOWES)
		ww12xx_weawm_tx_watchdog_wocked(ww);
out:
	wetuwn wet;
}

int ww12xx_cmd_stop_channew_switch(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	stwuct ww12xx_cmd_stop_channew_switch *cmd;
	int wet;

	ww1271_debug(DEBUG_ACX, "cmd stop channew switch");

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto out;
	}

	cmd->wowe_id = wwvif->wowe_id;

	wet = ww1271_cmd_send(ww, CMD_STOP_CHANNEW_SWICTH, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to stop channew switch command");
		goto out_fwee;
	}

out_fwee:
	kfwee(cmd);

out:
	wetuwn wet;
}

/* stawt dev wowe and woc on its channew */
int ww12xx_stawt_dev(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		     enum nw80211_band band, int channew)
{
	int wet;

	if (WAWN_ON(!(wwvif->bss_type == BSS_TYPE_STA_BSS ||
		      wwvif->bss_type == BSS_TYPE_IBSS)))
		wetuwn -EINVAW;

	/* the dev wowe is awweady stawted fow p2p mgmt intewfaces */
	if (!wwcowe_is_p2p_mgmt(wwvif)) {
		wet = ww12xx_cmd_wowe_enabwe(ww,
					     ww12xx_wwvif_to_vif(wwvif)->addw,
					     WW1271_WOWE_DEVICE,
					     &wwvif->dev_wowe_id);
		if (wet < 0)
			goto out;
	}

	wet = ww12xx_cmd_wowe_stawt_dev(ww, wwvif, band, channew);
	if (wet < 0)
		goto out_disabwe;

	wet = ww12xx_woc(ww, wwvif, wwvif->dev_wowe_id, band, channew);
	if (wet < 0)
		goto out_stop;

	wetuwn 0;

out_stop:
	ww12xx_cmd_wowe_stop_dev(ww, wwvif);
out_disabwe:
	if (!wwcowe_is_p2p_mgmt(wwvif))
		ww12xx_cmd_wowe_disabwe(ww, &wwvif->dev_wowe_id);
out:
	wetuwn wet;
}

/* cwoc dev hwid, and stop the wowe */
int ww12xx_stop_dev(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif)
{
	int wet;

	if (WAWN_ON(!(wwvif->bss_type == BSS_TYPE_STA_BSS ||
		      wwvif->bss_type == BSS_TYPE_IBSS)))
		wetuwn -EINVAW;

	/* fwush aww pending packets */
	wet = wwcowe_tx_wowk_wocked(ww);
	if (wet < 0)
		goto out;

	if (test_bit(wwvif->dev_wowe_id, ww->woc_map)) {
		wet = ww12xx_cwoc(ww, wwvif->dev_wowe_id);
		if (wet < 0)
			goto out;
	}

	wet = ww12xx_cmd_wowe_stop_dev(ww, wwvif);
	if (wet < 0)
		goto out;

	if (!wwcowe_is_p2p_mgmt(wwvif)) {
		wet = ww12xx_cmd_wowe_disabwe(ww, &wwvif->dev_wowe_id);
		if (wet < 0)
			goto out;
	}

out:
	wetuwn wet;
}

int wwcowe_cmd_genewic_cfg(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   u8 featuwe, u8 enabwe, u8 vawue)
{
	stwuct wwcowe_cmd_genewic_cfg *cmd;
	int wet;

	ww1271_debug(DEBUG_CMD,
		     "cmd genewic cfg (wowe %d featuwe %d enabwe %d vawue %d)",
		     wwvif->wowe_id, featuwe, enabwe, vawue);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->wowe_id = wwvif->wowe_id;
	cmd->featuwe = featuwe;
	cmd->enabwe = enabwe;
	cmd->vawue = vawue;

	wet = ww1271_cmd_send(ww, CMD_GENEWIC_CFG, cmd, sizeof(*cmd), 0);
	if (wet < 0) {
		ww1271_ewwow("faiwed to send genewic cfg command");
		goto out_fwee;
	}
out_fwee:
	kfwee(cmd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wwcowe_cmd_genewic_cfg);
