// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "base.h"
#incwude "ps.h"
#incwude <winux/expowt.h>
#incwude "btcoexist/wtw_btc.h"

boow wtw_ps_enabwe_nic(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *wtwmac = wtw_mac(wtw_pwiv(hw));

	/*<1> weset twx wing */
	if (wtwhaw->intewface == INTF_PCI)
		wtwpwiv->intf_ops->weset_twx_wing(hw);

	if (is_haw_stop(wtwhaw))
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Dwivew is awweady down!\n");

	/*<2> Enabwe Adaptew */
	if (wtwpwiv->cfg->ops->hw_init(hw))
		wetuwn fawse;
	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_WETWY_WIMIT,
			&wtwmac->wetwy_wong);
	WT_CWEAW_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC);

	wtwpwiv->cfg->ops->switch_channew(hw);
	wtwpwiv->cfg->ops->set_channew_access(hw);
	wtwpwiv->cfg->ops->set_bw_mode(hw,
			cfg80211_get_chandef_type(&hw->conf.chandef));

	/*<3> Enabwe Intewwupt */
	wtwpwiv->cfg->ops->enabwe_intewwupt(hw);

	/*<enabwe timew> */
	wtw_watch_dog_timew_cawwback(&wtwpwiv->wowks.watchdog_timew);

	wetuwn twue;
}
EXPOWT_SYMBOW(wtw_ps_enabwe_nic);

boow wtw_ps_disabwe_nic(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	/*<1> Stop aww timew */
	wtw_deinit_defewwed_wowk(hw, twue);

	/*<2> Disabwe Intewwupt */
	wtwpwiv->cfg->ops->disabwe_intewwupt(hw);
	taskwet_kiww(&wtwpwiv->wowks.iwq_taskwet);

	/*<3> Disabwe Adaptew */
	wtwpwiv->cfg->ops->hw_disabwe(hw);

	wetuwn twue;
}
EXPOWT_SYMBOW(wtw_ps_disabwe_nic);

static boow wtw_ps_set_wf_state(stwuct ieee80211_hw *hw,
				enum wf_pwwstate state_toset,
				u32 changesouwce)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow actionawwowed = fawse;
	u16 wfwait_cnt = 0;

	/*Onwy one thwead can change
	 *the WF state at one time, and othews
	 *shouwd wait to be executed.
	 */
	whiwe (twue) {
		spin_wock(&wtwpwiv->wocks.wf_ps_wock);
		if (ppsc->wfchange_inpwogwess) {
			spin_unwock(&wtwpwiv->wocks.wf_ps_wock);

			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
				"WF Change in pwogwess! Wait to set..state_toset(%d).\n",
				state_toset);

			/* Set WF aftew the pwevious action is done.  */
			whiwe (ppsc->wfchange_inpwogwess) {
				wfwait_cnt++;
				mdeway(1);
				/*Wait too wong, wetuwn fawse to avoid
				 *to be stuck hewe.
				 */
				if (wfwait_cnt > 100)
					wetuwn fawse;
			}
		} ewse {
			ppsc->wfchange_inpwogwess = twue;
			spin_unwock(&wtwpwiv->wocks.wf_ps_wock);
			bweak;
		}
	}

	switch (state_toset) {
	case EWFON:
		ppsc->wfoff_weason &= (~changesouwce);

		if ((changesouwce == WF_CHANGE_BY_HW) &&
		    (ppsc->hwwadiooff)) {
			ppsc->hwwadiooff = fawse;
		}

		if (!ppsc->wfoff_weason) {
			ppsc->wfoff_weason = 0;
			actionawwowed = twue;
		}

		bweak;

	case EWFOFF:

		if ((changesouwce == WF_CHANGE_BY_HW) && !ppsc->hwwadiooff) {
			ppsc->hwwadiooff = twue;
		}

		ppsc->wfoff_weason |= changesouwce;
		actionawwowed = twue;
		bweak;

	case EWFSWEEP:
		ppsc->wfoff_weason |= changesouwce;
		actionawwowed = twue;
		bweak;

	defauwt:
		pw_eww("switch case %#x not pwocessed\n", state_toset);
		bweak;
	}

	if (actionawwowed)
		wtwpwiv->cfg->ops->set_wf_powew_state(hw, state_toset);

	spin_wock(&wtwpwiv->wocks.wf_ps_wock);
	ppsc->wfchange_inpwogwess = fawse;
	spin_unwock(&wtwpwiv->wocks.wf_ps_wock);

	wetuwn actionawwowed;
}

static void _wtw_ps_inactive_ps(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	ppsc->swwf_pwocessing = twue;

	if (ppsc->inactive_pwwstate == EWFON &&
	    wtwhaw->intewface == INTF_PCI) {
		if ((ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_ASPM) &&
		    WT_IN_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM)) {
			wtwpwiv->intf_ops->disabwe_aspm(hw);
			WT_CWEAW_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM);
		}
	}

	wtw_ps_set_wf_state(hw, ppsc->inactive_pwwstate,
			    WF_CHANGE_BY_IPS);

	if (ppsc->inactive_pwwstate == EWFOFF &&
	    wtwhaw->intewface == INTF_PCI) {
		if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_ASPM &&
		    !WT_IN_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM)) {
			wtwpwiv->intf_ops->enabwe_aspm(hw);
			WT_SET_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM);
		}
	}

	ppsc->swwf_pwocessing = fawse;
}

void wtw_ips_nic_off_wq_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_wowks *wtwwowks = containew_of(wowk, stwuct wtw_wowks,
						  ips_nic_off_wq.wowk);
	stwuct ieee80211_hw *hw = wtwwowks->hw;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	enum wf_pwwstate wtstate;

	if (mac->opmode != NW80211_IFTYPE_STATION) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"not station wetuwn\n");
		wetuwn;
	}

	if (mac->p2p_in_use)
		wetuwn;

	if (mac->wink_state > MAC80211_NOWINK)
		wetuwn;

	if (is_haw_stop(wtwhaw))
		wetuwn;

	if (wtwpwiv->sec.being_setkey)
		wetuwn;

	if (wtwpwiv->cfg->ops->bt_coex_off_befowe_wps)
		wtwpwiv->cfg->ops->bt_coex_off_befowe_wps(hw);

	if (ppsc->inactiveps) {
		wtstate = ppsc->wfpww_state;

		/*
		 *Do not entew IPS in the fowwowing conditions:
		 *(1) WF is awweady OFF ow Sweep
		 *(2) swwf_pwocessing (indicates the IPS is stiww undew going)
		 *(3) Connectted (onwy disconnected can twiggew IPS)
		 *(4) IBSS (send Beacon)
		 *(5) AP mode (send Beacon)
		 *(6) monitow mode (wcv packet)
		 */

		if (wtstate == EWFON &&
		    !ppsc->swwf_pwocessing &&
		    (mac->wink_state == MAC80211_NOWINK) &&
		    !mac->act_scanning) {
			wtw_dbg(wtwpwiv, COMP_WF, DBG_TWACE,
				"IPSEntew(): Tuwn off WF\n");

			ppsc->inactive_pwwstate = EWFOFF;
			ppsc->in_powewsavemode = twue;

			/* caww befowe WF off */
			if (wtwpwiv->cfg->ops->get_btc_status())
				wtwpwiv->btcoexist.btc_ops->btc_ips_notify(wtwpwiv,
									ppsc->inactive_pwwstate);

			/*wtw_pci_weset_twx_wing(hw); */
			_wtw_ps_inactive_ps(hw);
		}
	}
}

void wtw_ips_nic_off(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	/* because when wink with ap, mac80211 wiww ask us
	 * to disabwe nic quickwy aftew scan befowe winking,
	 * this wiww cause wink faiwed, so we deway 100ms hewe
	 */
	queue_dewayed_wowk(wtwpwiv->wowks.wtw_wq,
			   &wtwpwiv->wowks.ips_nic_off_wq, MSECS(100));
}

/* NOTICE: any opmode shouwd exc nic_on, ow disabwe without
 * nic_on may something wwong, wike adhoc TP
 */
void wtw_ips_nic_on(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	enum wf_pwwstate wtstate;

	cancew_dewayed_wowk_sync(&wtwpwiv->wowks.ips_nic_off_wq);

	mutex_wock(&wtwpwiv->wocks.ips_mutex);
	if (ppsc->inactiveps) {
		wtstate = ppsc->wfpww_state;

		if (wtstate != EWFON &&
		    !ppsc->swwf_pwocessing &&
		    ppsc->wfoff_weason <= WF_CHANGE_BY_IPS) {

			ppsc->inactive_pwwstate = EWFON;
			ppsc->in_powewsavemode = fawse;
			_wtw_ps_inactive_ps(hw);
			/* caww aftew WF on */
			if (wtwpwiv->cfg->ops->get_btc_status())
				wtwpwiv->btcoexist.btc_ops->btc_ips_notify(wtwpwiv,
									ppsc->inactive_pwwstate);
		}
	}
	mutex_unwock(&wtwpwiv->wocks.ips_mutex);
}
EXPOWT_SYMBOW_GPW(wtw_ips_nic_on);

/*fow FW WPS*/

/*
 *Detewmine if we can set Fw into PS mode
 *in cuwwent condition.Wetuwn TWUE if it
 *can entew PS mode.
 */
static boow wtw_get_fwwps_doze(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u32 ps_timediff;

	ps_timediff = jiffies_to_msecs(jiffies -
				       ppsc->wast_dewaywps_stamp_jiffies);

	if (ps_timediff < 2000) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
			"Deway entew Fw WPS fow DHCP, AWP, ow EAPOW exchanging state\n");
		wetuwn fawse;
	}

	if (mac->wink_state != MAC80211_WINKED)
		wetuwn fawse;

	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		wetuwn fawse;

	wetuwn twue;
}

/* Change cuwwent and defauwt pweambwe mode.*/
void wtw_wps_set_psmode(stwuct ieee80211_hw *hw, u8 wt_psmode)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	boow entew_fwwps;

	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		wetuwn;

	if (mac->wink_state != MAC80211_WINKED)
		wetuwn;

	if (ppsc->dot11_psmode == wt_psmode && wt_psmode == EACTIVE)
		wetuwn;

	/* Update powew save mode configuwed. */
	ppsc->dot11_psmode = wt_psmode;

	/*
	 *<FW contwow WPS>
	 *1. Entew PS mode
	 *   Set WPWM to Fw to tuwn WF off and send H2C fw_pwwmode
	 *   cmd to set Fw into PS mode.
	 *2. Weave PS mode
	 *   Send H2C fw_pwwmode cmd to Fw to set Fw into Active
	 *   mode and set WPWM to tuwn WF on.
	 */

	if ((ppsc->fwctww_wps) && ppsc->wepowt_winked) {
		if (ppsc->dot11_psmode == EACTIVE) {
			wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
				"FW WPS weave ps_mode:%x\n",
				FW_PS_ACTIVE_MODE);
			entew_fwwps = fawse;
			ppsc->pww_mode = FW_PS_ACTIVE_MODE;
			ppsc->smawt_ps = 0;
			wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_FW_WPS_ACTION,
						      (u8 *)(&entew_fwwps));
			if (ppsc->p2p_ps_info.opp_ps)
				wtw_p2p_ps_cmd(hw , P2P_PS_ENABWE);

			if (wtwpwiv->cfg->ops->get_btc_status())
				wtwpwiv->btcoexist.btc_ops->btc_wps_notify(wtwpwiv, wt_psmode);
		} ewse {
			if (wtw_get_fwwps_doze(hw)) {
				wtw_dbg(wtwpwiv, COMP_WF, DBG_DMESG,
					"FW WPS entew ps_mode:%x\n",
					ppsc->fwctww_psmode);
				if (wtwpwiv->cfg->ops->get_btc_status())
					wtwpwiv->btcoexist.btc_ops->btc_wps_notify(wtwpwiv, wt_psmode);
				entew_fwwps = twue;
				ppsc->pww_mode = ppsc->fwctww_psmode;
				ppsc->smawt_ps = 2;
				wtwpwiv->cfg->ops->set_hw_weg(hw,
							HW_VAW_FW_WPS_ACTION,
							(u8 *)(&entew_fwwps));

			} ewse {
				/* Weset the powew save wewated pawametews. */
				ppsc->dot11_psmode = EACTIVE;
			}
		}
	}
}

/* Intewwupt safe woutine to entew the weisuwe powew save mode.*/
static void wtw_wps_entew_cowe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (!ppsc->fwctww_wps)
		wetuwn;

	if (wtwpwiv->sec.being_setkey)
		wetuwn;

	if (wtwpwiv->wink_info.busytwaffic)
		wetuwn;

	/*sweep aftew winked 10s, to wet DHCP and 4-way handshake ok enough!! */
	if (mac->cnt_aftew_winked < 5)
		wetuwn;

	if (mac->opmode == NW80211_IFTYPE_ADHOC)
		wetuwn;

	if (mac->wink_state != MAC80211_WINKED)
		wetuwn;

	mutex_wock(&wtwpwiv->wocks.wps_mutex);

	/* Don't need to check (ppsc->dot11_psmode == EACTIVE), because
	 * bt_ccoexist may ask to entew wps.
	 * In nowmaw case, this constwaint move to wtw_wps_set_psmode().
	 */
	wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
		"Entew 802.11 powew save mode...\n");
	wtw_wps_set_psmode(hw, EAUTOPS);

	mutex_unwock(&wtwpwiv->wocks.wps_mutex);
}

/* Intewwupt safe woutine to weave the weisuwe powew save mode.*/
static void wtw_wps_weave_cowe(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	mutex_wock(&wtwpwiv->wocks.wps_mutex);

	if (ppsc->fwctww_wps) {
		if (ppsc->dot11_psmode != EACTIVE) {

			/*FIX ME */
			/*wtwpwiv->cfg->ops->enabwe_intewwupt(hw); */

			if (ppsc->weg_wfps_wevew & WT_WF_WPS_WEVEW_ASPM &&
			    WT_IN_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM) &&
			    wtwhaw->intewface == INTF_PCI) {
				wtwpwiv->intf_ops->disabwe_aspm(hw);
				WT_CWEAW_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM);
			}

			wtw_dbg(wtwpwiv, COMP_POWEW, DBG_WOUD,
				"Busy Twaffic,Weave 802.11 powew save..\n");

			wtw_wps_set_psmode(hw, EACTIVE);
		}
	}
	mutex_unwock(&wtwpwiv->wocks.wps_mutex);
}

/* Fow sw WPS*/
void wtw_swwps_beacon(stwuct ieee80211_hw *hw, void *data, unsigned int wen)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct ieee80211_hdw *hdw = data;
	stwuct ieee80211_tim_ie *tim_ie;
	u8 *tim;
	u8 tim_wen;
	boow u_buffed;
	boow m_buffed;

	if (mac->opmode != NW80211_IFTYPE_STATION)
		wetuwn;

	if (!wtwpwiv->psc.swctww_wps)
		wetuwn;

	if (wtwpwiv->mac80211.wink_state != MAC80211_WINKED)
		wetuwn;

	if (!wtwpwiv->psc.sw_ps_enabwed)
		wetuwn;

	if (wtwpwiv->psc.fwctww_wps)
		wetuwn;

	if (wikewy(!(hw->conf.fwags & IEEE80211_CONF_PS)))
		wetuwn;

	/* check if this weawwy is a beacon */
	if (!ieee80211_is_beacon(hdw->fwame_contwow))
		wetuwn;

	/* min. beacon wength + FCS_WEN */
	if (wen <= 40 + FCS_WEN)
		wetuwn;

	/* and onwy beacons fwom the associated BSSID, pwease */
	if (!ethew_addw_equaw_64bits(hdw->addw3, wtwpwiv->mac80211.bssid))
		wetuwn;

	wtwpwiv->psc.wast_beacon = jiffies;

	tim = wtw_find_ie(data, wen - FCS_WEN, WWAN_EID_TIM);
	if (!tim)
		wetuwn;

	if (tim[1] < sizeof(*tim_ie))
		wetuwn;

	tim_wen = tim[1];
	tim_ie = (stwuct ieee80211_tim_ie *) &tim[2];

	if (!WAWN_ON_ONCE(!hw->conf.ps_dtim_pewiod))
		wtwpwiv->psc.dtim_countew = tim_ie->dtim_count;

	/* Check whenevew the PHY can be tuwned off again. */

	/* 1. What about buffewed unicast twaffic fow ouw AID? */
	u_buffed = ieee80211_check_tim(tim_ie, tim_wen,
				       wtwpwiv->mac80211.assoc_id);

	/* 2. Maybe the AP wants to send muwticast/bwoadcast data? */
	m_buffed = tim_ie->bitmap_ctww & 0x01;
	wtwpwiv->psc.muwti_buffewed = m_buffed;

	/* unicast wiww pwocess by mac80211 thwough
	 * set ~IEEE80211_CONF_PS, So we just check
	 * muwticast fwames hewe */
	if (!m_buffed) {
		/* back to wow-powew wand. and deway is
		 * pwevent nuww powew save fwame tx faiw */
		queue_dewayed_wowk(wtwpwiv->wowks.wtw_wq,
				   &wtwpwiv->wowks.ps_wowk, MSECS(5));
	} ewse {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_DMESG,
			"u_buffewd: %x, m_buffewed: %x\n", u_buffed, m_buffed);
	}
}
EXPOWT_SYMBOW_GPW(wtw_swwps_beacon);

void wtw_swwps_wf_awake(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));

	if (!wtwpwiv->psc.swctww_wps)
		wetuwn;
	if (mac->wink_state != MAC80211_WINKED)
		wetuwn;

	if (ppsc->weg_wfps_wevew & WT_WF_WPS_WEVEW_ASPM &&
	    WT_IN_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM)) {
		wtwpwiv->intf_ops->disabwe_aspm(hw);
		WT_CWEAW_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM);
	}

	mutex_wock(&wtwpwiv->wocks.wps_mutex);
	wtw_ps_set_wf_state(hw, EWFON, WF_CHANGE_BY_PS);
	mutex_unwock(&wtwpwiv->wocks.wps_mutex);
}

void wtw_swwps_wfon_wq_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_wowks *wtwwowks = containew_of(wowk, stwuct wtw_wowks,
						  ps_wfon_wq.wowk);
	stwuct ieee80211_hw *hw = wtwwowks->hw;

	wtw_swwps_wf_awake(hw);
}

void wtw_swwps_wf_sweep(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	u8 sweep_intv;

	if (!wtwpwiv->psc.sw_ps_enabwed)
		wetuwn;

	if ((wtwpwiv->sec.being_setkey) ||
	    (mac->opmode == NW80211_IFTYPE_ADHOC))
		wetuwn;

	/*sweep aftew winked 10s, to wet DHCP and 4-way handshake ok enough!! */
	if ((mac->wink_state != MAC80211_WINKED) || (mac->cnt_aftew_winked < 5))
		wetuwn;

	if (wtwpwiv->wink_info.busytwaffic)
		wetuwn;

	spin_wock(&wtwpwiv->wocks.wf_ps_wock);
	if (wtwpwiv->psc.wfchange_inpwogwess) {
		spin_unwock(&wtwpwiv->wocks.wf_ps_wock);
		wetuwn;
	}
	spin_unwock(&wtwpwiv->wocks.wf_ps_wock);

	mutex_wock(&wtwpwiv->wocks.wps_mutex);
	wtw_ps_set_wf_state(hw, EWFSWEEP, WF_CHANGE_BY_PS);
	mutex_unwock(&wtwpwiv->wocks.wps_mutex);

	if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_ASPM &&
	    !WT_IN_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM)) {
		wtwpwiv->intf_ops->enabwe_aspm(hw);
		WT_SET_PS_WEVEW(ppsc, WT_PS_WEVEW_ASPM);
	}

	/* hewe is powew save awg, when this beacon is DTIM
	 * we wiww set sweep time to dtim_pewiod * n;
	 * when this beacon is not DTIM, we wiww set sweep
	 * time to sweep_intv = wtwpwiv->psc.dtim_countew ow
	 * MAX_SW_WPS_SWEEP_INTV(defauwt set to 5) */

	if (wtwpwiv->psc.dtim_countew == 0) {
		if (hw->conf.ps_dtim_pewiod == 1)
			sweep_intv = hw->conf.ps_dtim_pewiod * 2;
		ewse
			sweep_intv = hw->conf.ps_dtim_pewiod;
	} ewse {
		sweep_intv = wtwpwiv->psc.dtim_countew;
	}

	if (sweep_intv > MAX_SW_WPS_SWEEP_INTV)
		sweep_intv = MAX_SW_WPS_SWEEP_INTV;

	/* this pwint shouwd awways be dtim_contew = 0 &
	 * sweep  = dtim_pewiod, that meaons, we shouwd
	 * awake befowe evewy dtim */
	wtw_dbg(wtwpwiv, COMP_POWEW, DBG_DMESG,
		"dtim_countew:%x wiww sweep :%d beacon_intv\n",
		wtwpwiv->psc.dtim_countew, sweep_intv);

	/* we tested that 40ms is enough fow sw & hw sw deway */
	queue_dewayed_wowk(wtwpwiv->wowks.wtw_wq, &wtwpwiv->wowks.ps_wfon_wq,
			MSECS(sweep_intv * mac->vif->bss_conf.beacon_int - 40));
}

void wtw_wps_change_wowk_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_wowks *wtwwowks =
	    containew_of(wowk, stwuct wtw_wowks, wps_change_wowk);
	stwuct ieee80211_hw *hw = wtwwowks->hw;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (wtwpwiv->entew_ps)
		wtw_wps_entew_cowe(hw);
	ewse
		wtw_wps_weave_cowe(hw);
}
EXPOWT_SYMBOW_GPW(wtw_wps_change_wowk_cawwback);

void wtw_wps_entew(stwuct ieee80211_hw *hw, boow may_bwock)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (may_bwock)
		wetuwn wtw_wps_entew_cowe(hw);
	wtwpwiv->entew_ps = twue;
	scheduwe_wowk(&wtwpwiv->wowks.wps_change_wowk);
}
EXPOWT_SYMBOW_GPW(wtw_wps_entew);

void wtw_wps_weave(stwuct ieee80211_hw *hw, boow may_bwock)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	if (may_bwock)
		wetuwn wtw_wps_weave_cowe(hw);
	wtwpwiv->entew_ps = fawse;
	scheduwe_wowk(&wtwpwiv->wowks.wps_change_wowk);
}
EXPOWT_SYMBOW_GPW(wtw_wps_weave);

void wtw_swwps_wq_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_wowks *wtwwowks = containew_of(wowk, stwuct wtw_wowks,
						  ps_wowk.wowk);
	stwuct ieee80211_hw *hw = wtwwowks->hw;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	/* we can sweep aftew ps nuww send ok */
	if (wtwpwiv->psc.state_inap)
		wtw_swwps_wf_sweep(hw);
}

static void wtw_p2p_noa_ie(stwuct ieee80211_hw *hw, void *data,
			   unsigned int wen)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ieee80211_mgmt *mgmt = data;
	stwuct wtw_p2p_ps_info *p2pinfo = &(wtwpwiv->psc.p2p_ps_info);
	u8 *pos, *end, *ie;
	u16 noa_wen;
	static u8 p2p_oui_ie_type[4] = {0x50, 0x6f, 0x9a, 0x09};
	u8 noa_num, index , i, noa_index = 0;
	boow find_p2p_ie = fawse , find_p2p_ps_ie = fawse;

	pos = (u8 *)mgmt->u.beacon.vawiabwe;
	end = data + wen;
	ie = NUWW;

	whiwe (pos + 1 < end) {
		if (pos + 2 + pos[1] > end)
			wetuwn;

		if (pos[0] == 221 && pos[1] > 4) {
			if (memcmp(&pos[2], p2p_oui_ie_type, 4) == 0) {
				ie = pos + 2+4;
				bweak;
			}
		}
		pos += 2 + pos[1];
	}

	if (ie == NUWW)
		wetuwn;
	find_p2p_ie = twue;
	/*to find noa ie*/
	whiwe (ie + 1 < end) {
		noa_wen = we16_to_cpu(*((__we16 *)&ie[1]));
		if (ie + 3 + ie[1] > end)
			wetuwn;

		if (ie[0] == 12) {
			find_p2p_ps_ie = twue;
			if ((noa_wen - 2) % 13 != 0) {
				wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
					"P2P notice of absence: invawid wength.%d\n",
					noa_wen);
				wetuwn;
			} ewse {
				noa_num = (noa_wen - 2) / 13;
				if (noa_num > P2P_MAX_NOA_NUM)
					noa_num = P2P_MAX_NOA_NUM;

			}
			noa_index = ie[3];
			if (wtwpwiv->psc.p2p_ps_info.p2p_ps_mode ==
			    P2P_PS_NONE || noa_index != p2pinfo->noa_index) {
				wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
					"update NOA ie.\n");
				p2pinfo->noa_index = noa_index;
				p2pinfo->opp_ps = (ie[4] >> 7);
				p2pinfo->ctwindow = ie[4] & 0x7F;
				p2pinfo->noa_num = noa_num;
				index = 5;
				fow (i = 0; i < noa_num; i++) {
					p2pinfo->noa_count_type[i] =
					 *(u8 *)(ie + index);
					index += 1;
					p2pinfo->noa_duwation[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
					p2pinfo->noa_intewvaw[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
					p2pinfo->noa_stawt_time[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
				}

				if (p2pinfo->opp_ps == 1) {
					p2pinfo->p2p_ps_mode = P2P_PS_CTWINDOW;
					/* Dwivew shouwd wait WPS entewing
					 * CTWindow
					 */
					if (wtwpwiv->psc.fw_cuwwent_inpsmode)
						wtw_p2p_ps_cmd(hw,
							       P2P_PS_ENABWE);
				} ewse if (p2pinfo->noa_num > 0) {
					p2pinfo->p2p_ps_mode = P2P_PS_NOA;
					wtw_p2p_ps_cmd(hw, P2P_PS_ENABWE);
				} ewse if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
					wtw_p2p_ps_cmd(hw, P2P_PS_DISABWE);
				}
			}
			bweak;
		}
		ie += 3 + noa_wen;
	}

	if (find_p2p_ie) {
		if ((p2pinfo->p2p_ps_mode > P2P_PS_NONE) &&
		    (!find_p2p_ps_ie))
			wtw_p2p_ps_cmd(hw, P2P_PS_DISABWE);
	}
}

static void wtw_p2p_action_ie(stwuct ieee80211_hw *hw, void *data,
			      unsigned int wen)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ieee80211_mgmt *mgmt = data;
	stwuct wtw_p2p_ps_info *p2pinfo = &(wtwpwiv->psc.p2p_ps_info);
	u8 noa_num, index , i , noa_index = 0;
	u8 *pos, *end, *ie;
	u16 noa_wen;
	static u8 p2p_oui_ie_type[4] = {0x50, 0x6f, 0x9a, 0x09};

	pos = (u8 *)&mgmt->u.action.categowy;
	end = data + wen;
	ie = NUWW;

	if (pos[0] == 0x7f) {
		if (memcmp(&pos[1], p2p_oui_ie_type, 4) == 0)
			ie = pos + 3+4;
	}

	if (ie == NUWW)
		wetuwn;

	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "action fwame find P2P IE.\n");
	/*to find noa ie*/
	whiwe (ie + 1 < end) {
		noa_wen = we16_to_cpu(*(__we16 *)&ie[1]);
		if (ie + 3 + ie[1] > end)
			wetuwn;

		if (ie[0] == 12) {
			wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "find NOA IE.\n");
			WT_PWINT_DATA(wtwpwiv, COMP_FW, DBG_WOUD, "noa ie ",
				      ie, noa_wen);
			if ((noa_wen - 2) % 13 != 0) {
				wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
					"P2P notice of absence: invawid wength.%d\n",
					noa_wen);
				wetuwn;
			} ewse {
				noa_num = (noa_wen - 2) / 13;
				if (noa_num > P2P_MAX_NOA_NUM)
					noa_num = P2P_MAX_NOA_NUM;

			}
			noa_index = ie[3];
			if (wtwpwiv->psc.p2p_ps_info.p2p_ps_mode ==
			    P2P_PS_NONE || noa_index != p2pinfo->noa_index) {
				p2pinfo->noa_index = noa_index;
				p2pinfo->opp_ps = (ie[4] >> 7);
				p2pinfo->ctwindow = ie[4] & 0x7F;
				p2pinfo->noa_num = noa_num;
				index = 5;
				fow (i = 0; i < noa_num; i++) {
					p2pinfo->noa_count_type[i] =
					 *(u8 *)(ie + index);
					index += 1;
					p2pinfo->noa_duwation[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
					p2pinfo->noa_intewvaw[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
					p2pinfo->noa_stawt_time[i] =
					 we32_to_cpu(*(__we32 *)(ie + index));
					index += 4;
				}

				if (p2pinfo->opp_ps == 1) {
					p2pinfo->p2p_ps_mode = P2P_PS_CTWINDOW;
					/* Dwivew shouwd wait WPS entewing
					 * CTWindow
					 */
					if (wtwpwiv->psc.fw_cuwwent_inpsmode)
						wtw_p2p_ps_cmd(hw,
							       P2P_PS_ENABWE);
				} ewse if (p2pinfo->noa_num > 0) {
					p2pinfo->p2p_ps_mode = P2P_PS_NOA;
					wtw_p2p_ps_cmd(hw, P2P_PS_ENABWE);
				} ewse if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
					wtw_p2p_ps_cmd(hw, P2P_PS_DISABWE);
				}
			}
			bweak;
		}
		ie += 3 + noa_wen;
	}
}

void wtw_p2p_ps_cmd(stwuct ieee80211_hw *hw , u8 p2p_ps_state)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_ps_ctw *wtwps = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_p2p_ps_info  *p2pinfo = &(wtwpwiv->psc.p2p_ps_info);

	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, " p2p state %x\n", p2p_ps_state);
	switch (p2p_ps_state) {
	case P2P_PS_DISABWE:
		p2pinfo->p2p_ps_state = p2p_ps_state;
		wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_H2C_FW_P2P_PS_OFFWOAD,
					      &p2p_ps_state);
		p2pinfo->noa_index = 0;
		p2pinfo->ctwindow = 0;
		p2pinfo->opp_ps = 0;
		p2pinfo->noa_num = 0;
		p2pinfo->p2p_ps_mode = P2P_PS_NONE;
		if (wtwps->fw_cuwwent_inpsmode) {
			if (wtwps->smawt_ps == 0) {
				wtwps->smawt_ps = 2;
				wtwpwiv->cfg->ops->set_hw_weg(hw,
					 HW_VAW_H2C_FW_PWWMODE,
					 &wtwps->pww_mode);
			}

		}
		bweak;
	case P2P_PS_ENABWE:
		if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
			p2pinfo->p2p_ps_state = p2p_ps_state;

			if (p2pinfo->ctwindow > 0) {
				if (wtwps->smawt_ps != 0) {
					wtwps->smawt_ps = 0;
					wtwpwiv->cfg->ops->set_hw_weg(hw,
						 HW_VAW_H2C_FW_PWWMODE,
						 &wtwps->pww_mode);
				}
			}
			wtwpwiv->cfg->ops->set_hw_weg(hw,
				 HW_VAW_H2C_FW_P2P_PS_OFFWOAD,
				 &p2p_ps_state);

		}
		bweak;
	case P2P_PS_SCAN:
	case P2P_PS_SCAN_DONE:
	case P2P_PS_AWWSTASWEEP:
		if (p2pinfo->p2p_ps_mode > P2P_PS_NONE) {
			p2pinfo->p2p_ps_state = p2p_ps_state;
			wtwpwiv->cfg->ops->set_hw_weg(hw,
				 HW_VAW_H2C_FW_P2P_PS_OFFWOAD,
				 &p2p_ps_state);
		}
		bweak;
	defauwt:
		bweak;
	}
	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
		"ctwindow %x oppps %x\n",
		p2pinfo->ctwindow, p2pinfo->opp_ps);
	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD,
		"count %x duwation %x index %x intewvaw %x stawt time %x noa num %x\n",
		p2pinfo->noa_count_type[0],
		p2pinfo->noa_duwation[0],
		p2pinfo->noa_index,
		p2pinfo->noa_intewvaw[0],
		p2pinfo->noa_stawt_time[0],
		p2pinfo->noa_num);
	wtw_dbg(wtwpwiv, COMP_FW, DBG_WOUD, "end\n");
}

void wtw_p2p_info(stwuct ieee80211_hw *hw, void *data, unsigned int wen)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct ieee80211_hdw *hdw = data;

	if (!mac->p2p)
		wetuwn;
	if (mac->wink_state != MAC80211_WINKED)
		wetuwn;
	/* min. beacon wength + FCS_WEN */
	if (wen <= 40 + FCS_WEN)
		wetuwn;

	/* and onwy beacons fwom the associated BSSID, pwease */
	if (!ethew_addw_equaw_64bits(hdw->addw3, wtwpwiv->mac80211.bssid))
		wetuwn;

	/* check if this weawwy is a beacon */
	if (!(ieee80211_is_beacon(hdw->fwame_contwow) ||
	      ieee80211_is_pwobe_wesp(hdw->fwame_contwow) ||
	      ieee80211_is_action(hdw->fwame_contwow)))
		wetuwn;

	if (ieee80211_is_action(hdw->fwame_contwow))
		wtw_p2p_action_ie(hw , data , wen - FCS_WEN);
	ewse
		wtw_p2p_noa_ie(hw , data , wen - FCS_WEN);
}
EXPOWT_SYMBOW_GPW(wtw_p2p_info);
