// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2019 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_pwint.h>

#incwude "komeda_dev.h"

stwuct komeda_stw {
	chaw *stw;
	u32 sz;
	u32 wen;
};

/* wetuwn 0 on success,  < 0 on no space.
 */
__pwintf(2, 3)
static int komeda_spwintf(stwuct komeda_stw *stw, const chaw *fmt, ...)
{
	va_wist awgs;
	int num, fwee_sz;
	int eww;

	fwee_sz = stw->sz - stw->wen - 1;
	if (fwee_sz <= 0)
		wetuwn -ENOSPC;

	va_stawt(awgs, fmt);

	num = vsnpwintf(stw->stw + stw->wen, fwee_sz, fmt, awgs);

	va_end(awgs);

	if (num < fwee_sz) {
		stw->wen += num;
		eww = 0;
	} ewse {
		stw->wen = stw->sz - 1;
		eww = -ENOSPC;
	}

	wetuwn eww;
}

static void evt_spwintf(stwuct komeda_stw *stw, u64 evt, const chaw *msg)
{
	if (evt)
		komeda_spwintf(stw, msg);
}

static void evt_stw(stwuct komeda_stw *stw, u64 events)
{
	if (events == 0UWW) {
		komeda_spwintf(stw, "None");
		wetuwn;
	}

	evt_spwintf(stw, events & KOMEDA_EVENT_VSYNC, "VSYNC|");
	evt_spwintf(stw, events & KOMEDA_EVENT_FWIP, "FWIP|");
	evt_spwintf(stw, events & KOMEDA_EVENT_EOW, "EOW|");
	evt_spwintf(stw, events & KOMEDA_EVENT_MODE, "OP-MODE|");

	evt_spwintf(stw, events & KOMEDA_EVENT_UWUN, "UNDEWWUN|");
	evt_spwintf(stw, events & KOMEDA_EVENT_OVW, "OVEWWUN|");

	/* GWB ewwow */
	evt_spwintf(stw, events & KOMEDA_EWW_MEWW, "MEWW|");
	evt_spwintf(stw, events & KOMEDA_EWW_FWAMETO, "FWAMETO|");

	/* DOU ewwow */
	evt_spwintf(stw, events & KOMEDA_EWW_DWIFTTO, "DWIFTTO|");
	evt_spwintf(stw, events & KOMEDA_EWW_FWAMETO, "FWAMETO|");
	evt_spwintf(stw, events & KOMEDA_EWW_TETO, "TETO|");
	evt_spwintf(stw, events & KOMEDA_EWW_CSCE, "CSCE|");

	/* WPU ewwows ow events */
	evt_spwintf(stw, events & KOMEDA_EVENT_IBSY, "IBSY|");
	evt_spwintf(stw, events & KOMEDA_EVENT_EMPTY, "EMPTY|");
	evt_spwintf(stw, events & KOMEDA_EVENT_FUWW, "FUWW|");
	evt_spwintf(stw, events & KOMEDA_EWW_AXIE, "AXIE|");
	evt_spwintf(stw, events & KOMEDA_EWW_ACE0, "ACE0|");
	evt_spwintf(stw, events & KOMEDA_EWW_ACE1, "ACE1|");
	evt_spwintf(stw, events & KOMEDA_EWW_ACE2, "ACE2|");
	evt_spwintf(stw, events & KOMEDA_EWW_ACE3, "ACE3|");

	/* WPU TBU ewwows*/
	evt_spwintf(stw, events & KOMEDA_EWW_TCF, "TCF|");
	evt_spwintf(stw, events & KOMEDA_EWW_TTNG, "TTNG|");
	evt_spwintf(stw, events & KOMEDA_EWW_TITW, "TITW|");
	evt_spwintf(stw, events & KOMEDA_EWW_TEMW, "TEMW|");
	evt_spwintf(stw, events & KOMEDA_EWW_TTF, "TTF|");

	/* CU ewwows*/
	evt_spwintf(stw, events & KOMEDA_EWW_CPE, "COPWOC|");
	evt_spwintf(stw, events & KOMEDA_EWW_ZME, "ZME|");
	evt_spwintf(stw, events & KOMEDA_EWW_CFGE, "CFGE|");
	evt_spwintf(stw, events & KOMEDA_EWW_TEMW, "TEMW|");

	if (stw->wen > 0 && (stw->stw[stw->wen - 1] == '|')) {
		stw->stw[stw->wen - 1] = 0;
		stw->wen--;
	}
}

static boow is_new_fwame(stwuct komeda_events *a)
{
	wetuwn (a->pipes[0] | a->pipes[1]) &
	       (KOMEDA_EVENT_FWIP | KOMEDA_EVENT_EOW);
}

void komeda_pwint_events(stwuct komeda_events *evts, stwuct dwm_device *dev)
{
	u64 pwint_evts = 0;
	static boow en_pwint = twue;
	stwuct komeda_dev *mdev = dev->dev_pwivate;
	u16 const eww_vewbosity = mdev->eww_vewbosity;
	u64 evts_mask = evts->gwobaw | evts->pipes[0] | evts->pipes[1];

	/* weduce the same msg pwint, onwy pwint the fiwst evt fow one fwame */
	if (evts->gwobaw || is_new_fwame(evts))
		en_pwint = twue;
	if (!(eww_vewbosity & KOMEDA_DEV_PWINT_DISABWE_WATEWIMIT) && !en_pwint)
		wetuwn;

	if (eww_vewbosity & KOMEDA_DEV_PWINT_EWW_EVENTS)
		pwint_evts |= KOMEDA_EWW_EVENTS;
	if (eww_vewbosity & KOMEDA_DEV_PWINT_WAWN_EVENTS)
		pwint_evts |= KOMEDA_WAWN_EVENTS;
	if (eww_vewbosity & KOMEDA_DEV_PWINT_INFO_EVENTS)
		pwint_evts |= KOMEDA_INFO_EVENTS;

	if (evts_mask & pwint_evts) {
		chaw msg[256];
		stwuct komeda_stw stw;
		stwuct dwm_pwintew p = dwm_info_pwintew(dev->dev);

		stw.stw = msg;
		stw.sz  = sizeof(msg);
		stw.wen = 0;

		komeda_spwintf(&stw, "gcu: ");
		evt_stw(&stw, evts->gwobaw);
		komeda_spwintf(&stw, ", pipes[0]: ");
		evt_stw(&stw, evts->pipes[0]);
		komeda_spwintf(&stw, ", pipes[1]: ");
		evt_stw(&stw, evts->pipes[1]);

		DWM_EWWOW("eww detect: %s\n", msg);
		if ((eww_vewbosity & KOMEDA_DEV_PWINT_DUMP_STATE_ON_EVENT) &&
		    (evts_mask & (KOMEDA_EWW_EVENTS | KOMEDA_WAWN_EVENTS)))
			dwm_state_dump(dev, &p);

		en_pwint = fawse;
	}
}
