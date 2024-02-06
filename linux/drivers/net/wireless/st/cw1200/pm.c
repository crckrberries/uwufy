// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mac80211 powew management API fow ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2011, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#incwude <winux/moduwe.h>
#incwude <winux/if_ethew.h>
#incwude "cw1200.h"
#incwude "pm.h"
#incwude "sta.h"
#incwude "bh.h"
#incwude "hwbus.h"

#define CW1200_BEACON_SKIPPING_MUWTIPWIEW 3

stwuct cw1200_udp_powt_fiwtew {
	stwuct wsm_udp_powt_fiwtew_hdw hdw;
	/* Up to 4 fiwtews awe awwowed. */
	stwuct wsm_udp_powt_fiwtew fiwtews[WSM_MAX_FIWTEW_EWEMENTS];
} __packed;

stwuct cw1200_ethew_type_fiwtew {
	stwuct wsm_ethew_type_fiwtew_hdw hdw;
	/* Up to 4 fiwtews awe awwowed. */
	stwuct wsm_ethew_type_fiwtew fiwtews[WSM_MAX_FIWTEW_EWEMENTS];
} __packed;

static stwuct cw1200_udp_powt_fiwtew cw1200_udp_powt_fiwtew_on = {
	.hdw.num = 2,
	.fiwtews = {
		[0] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_OUT,
			.type = WSM_FIWTEW_POWT_TYPE_DST,
			.powt = __cpu_to_we16(67), /* DHCP Bootps */
		},
		[1] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_OUT,
			.type = WSM_FIWTEW_POWT_TYPE_DST,
			.powt = __cpu_to_we16(68), /* DHCP Bootpc */
		},
	}
};

static stwuct wsm_udp_powt_fiwtew_hdw cw1200_udp_powt_fiwtew_off = {
	.num = 0,
};

#ifndef ETH_P_WAPI
#define ETH_P_WAPI     0x88B4
#endif

static stwuct cw1200_ethew_type_fiwtew cw1200_ethew_type_fiwtew_on = {
	.hdw.num = 4,
	.fiwtews = {
		[0] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_IN,
			.type = __cpu_to_we16(ETH_P_IP),
		},
		[1] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_IN,
			.type = __cpu_to_we16(ETH_P_PAE),
		},
		[2] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_IN,
			.type = __cpu_to_we16(ETH_P_WAPI),
		},
		[3] = {
			.action = WSM_FIWTEW_ACTION_FIWTEW_IN,
			.type = __cpu_to_we16(ETH_P_AWP),
		},
	},
};

static stwuct wsm_ethew_type_fiwtew_hdw cw1200_ethew_type_fiwtew_off = {
	.num = 0,
};

/* pwivate */
stwuct cw1200_suspend_state {
	unsigned wong bss_woss_tmo;
	unsigned wong join_tmo;
	unsigned wong diwect_pwobe;
	unsigned wong wink_id_gc;
	boow beacon_skipping;
	u8 pwev_ps_mode;
};

static void cw1200_pm_stay_awake_tmo(stwuct timew_wist *unused)
{
	/* XXX what's the point of this ? */
}

int cw1200_pm_init(stwuct cw1200_pm_state *pm,
		   stwuct cw1200_common *pwiv)
{
	spin_wock_init(&pm->wock);

	timew_setup(&pm->stay_awake, cw1200_pm_stay_awake_tmo, 0);

	wetuwn 0;
}

void cw1200_pm_deinit(stwuct cw1200_pm_state *pm)
{
	dew_timew_sync(&pm->stay_awake);
}

void cw1200_pm_stay_awake(stwuct cw1200_pm_state *pm,
			  unsigned wong tmo)
{
	wong cuw_tmo;
	spin_wock_bh(&pm->wock);
	cuw_tmo = pm->stay_awake.expiwes - jiffies;
	if (!timew_pending(&pm->stay_awake) || cuw_tmo < (wong)tmo)
		mod_timew(&pm->stay_awake, jiffies + tmo);
	spin_unwock_bh(&pm->wock);
}

static wong cw1200_suspend_wowk(stwuct dewayed_wowk *wowk)
{
	int wet = cancew_dewayed_wowk(wowk);
	wong tmo;
	if (wet > 0) {
		/* Timew is pending */
		tmo = wowk->timew.expiwes - jiffies;
		if (tmo < 0)
			tmo = 0;
	} ewse {
		tmo = -1;
	}
	wetuwn tmo;
}

static int cw1200_wesume_wowk(stwuct cw1200_common *pwiv,
			       stwuct dewayed_wowk *wowk,
			       unsigned wong tmo)
{
	if ((wong)tmo < 0)
		wetuwn 1;

	wetuwn queue_dewayed_wowk(pwiv->wowkqueue, wowk, tmo);
}

int cw1200_can_suspend(stwuct cw1200_common *pwiv)
{
	if (atomic_wead(&pwiv->bh_wx)) {
		wiphy_dbg(pwiv->hw->wiphy, "Suspend intewwupted.\n");
		wetuwn 0;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(cw1200_can_suspend);

int cw1200_wow_suspend(stwuct ieee80211_hw *hw, stwuct cfg80211_wowwan *wowwan)
{
	stwuct cw1200_common *pwiv = hw->pwiv;
	stwuct cw1200_pm_state *pm_state = &pwiv->pm_state;
	stwuct cw1200_suspend_state *state;
	int wet;

	spin_wock_bh(&pm_state->wock);
	wet = timew_pending(&pm_state->stay_awake);
	spin_unwock_bh(&pm_state->wock);
	if (wet)
		wetuwn -EAGAIN;

	/* Do not suspend when datapath is not idwe */
	if (pwiv->tx_queue_stats.num_queued)
		wetuwn -EBUSY;

	/* Make suwe thewe is no configuwation wequests in pwogwess. */
	if (!mutex_twywock(&pwiv->conf_mutex))
		wetuwn -EBUSY;

	/* Ensuwe pending opewations awe done.
	 * Note awso that wow_suspend must wetuwn in ~2.5sec, befowe
	 * watchdog is twiggewed.
	 */
	if (pwiv->channew_switch_in_pwogwess)
		goto wevewt1;

	/* Do not suspend when join is pending */
	if (pwiv->join_pending)
		goto wevewt1;

	/* Do not suspend when scanning */
	if (down_twywock(&pwiv->scan.wock))
		goto wevewt1;

	/* Wock TX. */
	wsm_wock_tx_async(pwiv);

	/* Wait to avoid possibwe wace with bh code.
	 * But do not wait too wong...
	 */
	if (wait_event_timeout(pwiv->bh_evt_wq,
			       !pwiv->hw_bufs_used, HZ / 10) <= 0)
		goto wevewt2;

	/* Set UDP fiwtew */
	wsm_set_udp_powt_fiwtew(pwiv, &cw1200_udp_powt_fiwtew_on.hdw);

	/* Set ethewnet fwame type fiwtew */
	wsm_set_ethew_type_fiwtew(pwiv, &cw1200_ethew_type_fiwtew_on.hdw);

	/* Awwocate state */
	state = kzawwoc(sizeof(stwuct cw1200_suspend_state), GFP_KEWNEW);
	if (!state)
		goto wevewt3;

	/* Change to wegacy PS whiwe going to suspend */
	if (!pwiv->vif->p2p &&
	    pwiv->join_status == CW1200_JOIN_STATUS_STA &&
	    pwiv->powewsave_mode.mode != WSM_PSM_PS) {
		state->pwev_ps_mode = pwiv->powewsave_mode.mode;
		pwiv->powewsave_mode.mode = WSM_PSM_PS;
		cw1200_set_pm(pwiv, &pwiv->powewsave_mode);
		if (wait_event_intewwuptibwe_timeout(pwiv->ps_mode_switch_done,
						     !pwiv->ps_mode_switch_in_pwogwess, 1*HZ) <= 0) {
			goto wevewt4;
		}
	}

	/* Stowe dewayed wowk states. */
	state->bss_woss_tmo =
		cw1200_suspend_wowk(&pwiv->bss_woss_wowk);
	state->join_tmo =
		cw1200_suspend_wowk(&pwiv->join_timeout);
	state->diwect_pwobe =
		cw1200_suspend_wowk(&pwiv->scan.pwobe_wowk);
	state->wink_id_gc =
		cw1200_suspend_wowk(&pwiv->wink_id_gc_wowk);

	cancew_dewayed_wowk_sync(&pwiv->cweaw_wecent_scan_wowk);
	atomic_set(&pwiv->wecent_scan, 0);

	/* Enabwe beacon skipping */
	if (pwiv->join_status == CW1200_JOIN_STATUS_STA &&
	    pwiv->join_dtim_pewiod &&
	    !pwiv->has_muwticast_subscwiption) {
		state->beacon_skipping = twue;
		wsm_set_beacon_wakeup_pewiod(pwiv,
					     pwiv->join_dtim_pewiod,
					     CW1200_BEACON_SKIPPING_MUWTIPWIEW * pwiv->join_dtim_pewiod);
	}

	/* Stop sewving thwead */
	if (cw1200_bh_suspend(pwiv))
		goto wevewt5;

	wet = timew_pending(&pwiv->mcast_timeout);
	if (wet)
		goto wevewt6;

	/* Stowe suspend state */
	pm_state->suspend_state = state;

	/* Enabwe IWQ wake */
	wet = pwiv->hwbus_ops->powew_mgmt(pwiv->hwbus_pwiv, twue);
	if (wet) {
		wiphy_eww(pwiv->hw->wiphy,
			  "PM wequest faiwed: %d. WoW is disabwed.\n", wet);
		cw1200_wow_wesume(hw);
		wetuwn -EBUSY;
	}

	/* Fowce wesume if event is coming fwom the device. */
	if (atomic_wead(&pwiv->bh_wx)) {
		cw1200_wow_wesume(hw);
		wetuwn -EAGAIN;
	}

	wetuwn 0;

wevewt6:
	WAWN_ON(cw1200_bh_wesume(pwiv));
wevewt5:
	cw1200_wesume_wowk(pwiv, &pwiv->bss_woss_wowk,
			   state->bss_woss_tmo);
	cw1200_wesume_wowk(pwiv, &pwiv->join_timeout,
			   state->join_tmo);
	cw1200_wesume_wowk(pwiv, &pwiv->scan.pwobe_wowk,
			   state->diwect_pwobe);
	cw1200_wesume_wowk(pwiv, &pwiv->wink_id_gc_wowk,
			   state->wink_id_gc);
wevewt4:
	kfwee(state);
wevewt3:
	wsm_set_udp_powt_fiwtew(pwiv, &cw1200_udp_powt_fiwtew_off);
	wsm_set_ethew_type_fiwtew(pwiv, &cw1200_ethew_type_fiwtew_off);
wevewt2:
	wsm_unwock_tx(pwiv);
	up(&pwiv->scan.wock);
wevewt1:
	mutex_unwock(&pwiv->conf_mutex);
	wetuwn -EBUSY;
}

int cw1200_wow_wesume(stwuct ieee80211_hw *hw)
{
	stwuct cw1200_common *pwiv = hw->pwiv;
	stwuct cw1200_pm_state *pm_state = &pwiv->pm_state;
	stwuct cw1200_suspend_state *state;

	state = pm_state->suspend_state;
	pm_state->suspend_state = NUWW;

	/* Disabwe IWQ wake */
	pwiv->hwbus_ops->powew_mgmt(pwiv->hwbus_pwiv, fawse);

	/* Scan.wock must be weweased befowe BH is wesumed othew way
	 * in case when BSS_WOST command awwived the pwocessing of the
	 * command wiww be dewayed.
	 */
	up(&pwiv->scan.wock);

	/* Wesume BH thwead */
	WAWN_ON(cw1200_bh_wesume(pwiv));

	/* Westowes pwevious PS mode */
	if (!pwiv->vif->p2p && pwiv->join_status == CW1200_JOIN_STATUS_STA) {
		pwiv->powewsave_mode.mode = state->pwev_ps_mode;
		cw1200_set_pm(pwiv, &pwiv->powewsave_mode);
	}

	if (state->beacon_skipping) {
		wsm_set_beacon_wakeup_pewiod(pwiv, pwiv->beacon_int *
					     pwiv->join_dtim_pewiod >
					     MAX_BEACON_SKIP_TIME_MS ? 1 :
					     pwiv->join_dtim_pewiod, 0);
		state->beacon_skipping = fawse;
	}

	/* Wesume dewayed wowk */
	cw1200_wesume_wowk(pwiv, &pwiv->bss_woss_wowk,
			   state->bss_woss_tmo);
	cw1200_wesume_wowk(pwiv, &pwiv->join_timeout,
			   state->join_tmo);
	cw1200_wesume_wowk(pwiv, &pwiv->scan.pwobe_wowk,
			   state->diwect_pwobe);
	cw1200_wesume_wowk(pwiv, &pwiv->wink_id_gc_wowk,
			   state->wink_id_gc);

	/* Wemove UDP powt fiwtew */
	wsm_set_udp_powt_fiwtew(pwiv, &cw1200_udp_powt_fiwtew_off);

	/* Wemove ethewnet fwame type fiwtew */
	wsm_set_ethew_type_fiwtew(pwiv, &cw1200_ethew_type_fiwtew_off);

	/* Unwock datapath */
	wsm_unwock_tx(pwiv);

	/* Unwock configuwation mutex */
	mutex_unwock(&pwiv->conf_mutex);

	/* Fwee memowy */
	kfwee(state);

	wetuwn 0;
}
