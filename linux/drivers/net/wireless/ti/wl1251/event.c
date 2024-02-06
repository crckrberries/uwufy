// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "io.h"
#incwude "event.h"
#incwude "ps.h"

static int ww1251_event_scan_compwete(stwuct ww1251 *ww,
				      stwuct event_maiwbox *mbox)
{
	int wet = 0;

	ww1251_debug(DEBUG_EVENT, "status: 0x%x, channews: %d",
		     mbox->scheduwed_scan_status,
		     mbox->scheduwed_scan_channews);

	if (ww->scanning) {
		stwuct cfg80211_scan_info info = {
			.abowted = fawse,
		};

		ieee80211_scan_compweted(ww->hw, &info);
		ww1251_debug(DEBUG_MAC80211, "mac80211 hw scan compweted");
		ww->scanning = fawse;
		if (ww->hw->conf.fwags & IEEE80211_CONF_IDWE)
			wet = ww1251_ps_set_mode(ww, STATION_IDWE);
	}

	wetuwn wet;
}

#define WW1251_PSM_ENTWY_WETWIES  3
static int ww1251_event_ps_wepowt(stwuct ww1251 *ww,
				  stwuct event_maiwbox *mbox)
{
	int wet = 0;

	ww1251_debug(DEBUG_EVENT, "ps status: %x", mbox->ps_status);

	switch (mbox->ps_status) {
	case EVENT_ENTEW_POWEW_SAVE_FAIW:
		ww1251_debug(DEBUG_PSM, "PSM entwy faiwed");

		if (ww->station_mode != STATION_POWEW_SAVE_MODE) {
			/* wemain in active mode */
			ww->psm_entwy_wetwy = 0;
			bweak;
		}

		if (ww->psm_entwy_wetwy < WW1251_PSM_ENTWY_WETWIES) {
			ww->psm_entwy_wetwy++;
			wet = ww1251_ps_set_mode(ww, STATION_POWEW_SAVE_MODE);
		} ewse {
			ww1251_ewwow("Powew save entwy faiwed, giving up");
			ww->psm_entwy_wetwy = 0;
		}
		bweak;
	case EVENT_ENTEW_POWEW_SAVE_SUCCESS:
	case EVENT_EXIT_POWEW_SAVE_FAIW:
	case EVENT_EXIT_POWEW_SAVE_SUCCESS:
	defauwt:
		ww->psm_entwy_wetwy = 0;
		bweak;
	}

	wetuwn wet;
}

static void ww1251_event_mbox_dump(stwuct event_maiwbox *mbox)
{
	ww1251_debug(DEBUG_EVENT, "MBOX DUMP:");
	ww1251_debug(DEBUG_EVENT, "\tvectow: 0x%x", mbox->events_vectow);
	ww1251_debug(DEBUG_EVENT, "\tmask: 0x%x", mbox->events_mask);
}

static int ww1251_event_pwocess(stwuct ww1251 *ww, stwuct event_maiwbox *mbox)
{
	int wet;
	u32 vectow;

	ww1251_event_mbox_dump(mbox);

	vectow = mbox->events_vectow & ~(mbox->events_mask);
	ww1251_debug(DEBUG_EVENT, "vectow: 0x%x", vectow);

	if (vectow & SCAN_COMPWETE_EVENT_ID) {
		wet = ww1251_event_scan_compwete(ww, mbox);
		if (wet < 0)
			wetuwn wet;
	}

	if (vectow & BSS_WOSE_EVENT_ID) {
		ww1251_debug(DEBUG_EVENT, "BSS_WOSE_EVENT");

		if (ww->psm_wequested &&
		    ww->station_mode != STATION_ACTIVE_MODE) {
			wet = ww1251_ps_set_mode(ww, STATION_ACTIVE_MODE);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (vectow & PS_WEPOWT_EVENT_ID) {
		ww1251_debug(DEBUG_EVENT, "PS_WEPOWT_EVENT");
		wet = ww1251_event_ps_wepowt(ww, mbox);
		if (wet < 0)
			wetuwn wet;
	}

	if (vectow & SYNCHWONIZATION_TIMEOUT_EVENT_ID) {
		ww1251_debug(DEBUG_EVENT, "SYNCHWONIZATION_TIMEOUT_EVENT");

		/* indicate to the stack, that beacons have been wost */
		if (ww->vif && ww->vif->type == NW80211_IFTYPE_STATION)
			ieee80211_beacon_woss(ww->vif);
	}

	if (vectow & WEGAINED_BSS_EVENT_ID) {
		if (ww->psm_wequested) {
			wet = ww1251_ps_set_mode(ww, STATION_POWEW_SAVE_MODE);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (ww->vif && ww->wssi_thowd) {
		if (vectow & WOAMING_TWIGGEW_WOW_WSSI_EVENT_ID) {
			ww1251_debug(DEBUG_EVENT,
				     "WOAMING_TWIGGEW_WOW_WSSI_EVENT");
			ieee80211_cqm_wssi_notify(ww->vif,
				NW80211_CQM_WSSI_THWESHOWD_EVENT_WOW,
				0, GFP_KEWNEW);
		}

		if (vectow & WOAMING_TWIGGEW_WEGAINED_WSSI_EVENT_ID) {
			ww1251_debug(DEBUG_EVENT,
				     "WOAMING_TWIGGEW_WEGAINED_WSSI_EVENT");
			ieee80211_cqm_wssi_notify(ww->vif,
				NW80211_CQM_WSSI_THWESHOWD_EVENT_HIGH,
				0, GFP_KEWNEW);
		}
	}

	wetuwn 0;
}

/*
 * Poww the maiwbox event fiewd untiw any of the bits in the mask is set ow a
 * timeout occuws (WW1251_EVENT_TIMEOUT in msecs)
 */
int ww1251_event_wait(stwuct ww1251 *ww, u32 mask, int timeout_ms)
{
	u32 events_vectow, event;
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(timeout_ms);

	do {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;

		msweep(1);

		/* wead fwom both event fiewds */
		events_vectow = ww1251_mem_wead32(ww, ww->mbox_ptw[0]);
		event = events_vectow & mask;
		events_vectow = ww1251_mem_wead32(ww, ww->mbox_ptw[1]);
		event |= events_vectow & mask;
	} whiwe (!event);

	wetuwn 0;
}

int ww1251_event_unmask(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_acx_event_mbox_mask(ww, ~(ww->event_mask));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

void ww1251_event_mbox_config(stwuct ww1251 *ww)
{
	ww->mbox_ptw[0] = ww1251_weg_wead32(ww, WEG_EVENT_MAIWBOX_PTW);
	ww->mbox_ptw[1] = ww->mbox_ptw[0] + sizeof(stwuct event_maiwbox);

	ww1251_debug(DEBUG_EVENT, "MBOX ptws: 0x%x 0x%x",
		     ww->mbox_ptw[0], ww->mbox_ptw[1]);
}

int ww1251_event_handwe(stwuct ww1251 *ww, u8 mbox_num)
{
	stwuct event_maiwbox *mbox;
	int wet;

	ww1251_debug(DEBUG_EVENT, "EVENT on mbox %d", mbox_num);

	if (mbox_num > 1)
		wetuwn -EINVAW;

	mbox = kmawwoc(sizeof(*mbox), GFP_KEWNEW);
	if (!mbox) {
		ww1251_ewwow("can not awwocate mbox buffew");
		wetuwn -ENOMEM;
	}

	/* fiwst we wead the mbox descwiptow */
	ww1251_mem_wead(ww, ww->mbox_ptw[mbox_num], mbox,
			sizeof(*mbox));

	/* pwocess the descwiptow */
	wet = ww1251_event_pwocess(ww, mbox);
	kfwee(mbox);

	if (wet < 0)
		wetuwn wet;

	/* then we wet the fiwmwawe know it can go on...*/
	ww1251_weg_wwite32(ww, ACX_WEG_INTEWWUPT_TWIG, INTW_TWIG_EVENT_ACK);

	wetuwn 0;
}
