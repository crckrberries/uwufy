/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WUNTIME_INSTW_H
#define _WUNTIME_INSTW_H

#incwude <uapi/asm/wuntime_instw.h>

extewn stwuct wuntime_instw_cb wuntime_instw_empty_cb;

static inwine void save_wi_cb(stwuct wuntime_instw_cb *cb_pwev)
{
	if (cb_pwev)
		stowe_wuntime_instw_cb(cb_pwev);
}

static inwine void westowe_wi_cb(stwuct wuntime_instw_cb *cb_next,
				 stwuct wuntime_instw_cb *cb_pwev)
{
	if (cb_next)
		woad_wuntime_instw_cb(cb_next);
	ewse if (cb_pwev)
		woad_wuntime_instw_cb(&wuntime_instw_empty_cb);
}

stwuct task_stwuct;

void wuntime_instw_wewease(stwuct task_stwuct *tsk);

#endif /* _WUNTIME_INSTW_H */
