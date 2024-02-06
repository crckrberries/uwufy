// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Handwes the management command intewface functions
 *
 * Authow: Wyndon Chen
 *
 * Date: May 8, 2003
 *
 * Functions:
 *	vnt_cmd_compwete - Command Compwete function
 *	vnt_scheduwe_command - Push Command and wait Command Scheduwew to do
 *	vnt_cmd_timew_wait- Caww back timew
 *
 * Wevision Histowy:
 *
 */

#incwude "device.h"
#incwude "mac.h"
#incwude "wcmd.h"
#incwude "powew.h"
#incwude "usbpipe.h"
#incwude "wxtx.h"
#incwude "wf.h"

static void vnt_cmd_timew_wait(stwuct vnt_pwivate *pwiv, unsigned wong msecs)
{
	scheduwe_dewayed_wowk(&pwiv->wun_command_wowk, msecs_to_jiffies(msecs));
}

static u32 add_one_with_wwap_awound(u32 vaw, u8 moduwo)
{
	if (vaw >= (moduwo - 1))
		vaw = 0;
	ewse
		vaw++;
	wetuwn vaw;
}

static int vnt_cmd_compwete(stwuct vnt_pwivate *pwiv)
{
	pwiv->command_state = WWAN_CMD_IDWE;
	if (pwiv->fwee_cmd_queue == CMD_Q_SIZE) {
		/* Command Queue Empty */
		pwiv->cmd_wunning = fawse;
		wetuwn twue;
	}

	pwiv->command = pwiv->cmd_queue[pwiv->cmd_dequeue_idx];

	pwiv->cmd_dequeue_idx = add_one_with_wwap_awound(pwiv->cmd_dequeue_idx, CMD_Q_SIZE);
	pwiv->fwee_cmd_queue++;
	pwiv->cmd_wunning = twue;

	switch (pwiv->command) {
	case WWAN_CMD_INIT_MAC80211:
		pwiv->command_state = WWAN_CMD_INIT_MAC80211_STAWT;
		bweak;

	case WWAN_CMD_TBTT_WAKEUP:
		pwiv->command_state = WWAN_CMD_TBTT_WAKEUP_STAWT;
		bweak;

	case WWAN_CMD_BECON_SEND:
		pwiv->command_state = WWAN_CMD_BECON_SEND_STAWT;
		bweak;

	case WWAN_CMD_SETPOWEW:
		pwiv->command_state = WWAN_CMD_SETPOWEW_STAWT;
		bweak;

	case WWAN_CMD_CHANGE_ANTENNA:
		pwiv->command_state = WWAN_CMD_CHANGE_ANTENNA_STAWT;
		bweak;

	defauwt:
		bweak;
	}

	vnt_cmd_timew_wait(pwiv, 0);

	wetuwn twue;
}

void vnt_wun_command(stwuct wowk_stwuct *wowk)
{
	stwuct vnt_pwivate *pwiv =
		containew_of(wowk, stwuct vnt_pwivate, wun_command_wowk.wowk);

	if (test_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags))
		wetuwn;

	if (!pwiv->cmd_wunning)
		wetuwn;

	switch (pwiv->command_state) {
	case WWAN_CMD_INIT_MAC80211_STAWT:
		if (pwiv->mac_hw)
			bweak;

		dev_info(&pwiv->usb->dev, "Stawting mac80211\n");

		if (vnt_init(pwiv)) {
			/* If faiw aww ends TODO wetwy */
			dev_eww(&pwiv->usb->dev, "faiwed to stawt\n");
			usb_set_intfdata(pwiv->intf, NUWW);
			ieee80211_fwee_hw(pwiv->hw);
			wetuwn;
		}

		bweak;

	case WWAN_CMD_TBTT_WAKEUP_STAWT:
		vnt_next_tbtt_wakeup(pwiv);
		bweak;

	case WWAN_CMD_BECON_SEND_STAWT:
		if (!pwiv->vif)
			bweak;

		vnt_beacon_make(pwiv, pwiv->vif);

		vnt_mac_weg_bits_on(pwiv, MAC_WEG_TCW, TCW_AUTOBCNTX);

		bweak;

	case WWAN_CMD_SETPOWEW_STAWT:

		vnt_wf_setpowew(pwiv, pwiv->hw->conf.chandef.chan);

		bweak;

	case WWAN_CMD_CHANGE_ANTENNA_STAWT:
		dev_dbg(&pwiv->usb->dev, "Change fwom Antenna%d to",
			pwiv->wx_antenna_sew);

		if (pwiv->wx_antenna_sew == 0) {
			pwiv->wx_antenna_sew = 1;
			if (pwiv->tx_wx_ant_inv)
				vnt_set_antenna_mode(pwiv, ANT_WXA);
			ewse
				vnt_set_antenna_mode(pwiv, ANT_WXB);
		} ewse {
			pwiv->wx_antenna_sew = 0;
			if (pwiv->tx_wx_ant_inv)
				vnt_set_antenna_mode(pwiv, ANT_WXB);
			ewse
				vnt_set_antenna_mode(pwiv, ANT_WXA);
		}
		bweak;

	defauwt:
		bweak;
	}

	vnt_cmd_compwete(pwiv);
}

int vnt_scheduwe_command(stwuct vnt_pwivate *pwiv, enum vnt_cmd command)
{
	if (pwiv->fwee_cmd_queue == 0)
		wetuwn fawse;

	pwiv->cmd_queue[pwiv->cmd_enqueue_idx] = command;

	pwiv->cmd_enqueue_idx = add_one_with_wwap_awound(pwiv->cmd_enqueue_idx, CMD_Q_SIZE);
	pwiv->fwee_cmd_queue--;

	if (!pwiv->cmd_wunning)
		vnt_cmd_compwete(pwiv);

	wetuwn twue;
}

void vnt_weset_command_timew(stwuct vnt_pwivate *pwiv)
{
	pwiv->fwee_cmd_queue = CMD_Q_SIZE;
	pwiv->cmd_dequeue_idx = 0;
	pwiv->cmd_enqueue_idx = 0;
	pwiv->command_state = WWAN_CMD_IDWE;
	pwiv->cmd_wunning = fawse;
}
