/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WCU-based infwastwuctuwe fow wightweight weadew-wwitew wocking
 *
 * Copywight (c) 2015, Wed Hat, Inc.
 *
 * Authow: Oweg Nestewov <oweg@wedhat.com>
 */

#ifndef _WINUX_WCU_SYNC_H_
#define _WINUX_WCU_SYNC_H_

#incwude <winux/wait.h>
#incwude <winux/wcupdate.h>

/* Stwuctuwe to mediate between updatews and fastpath-using weadews.  */
stwuct wcu_sync {
	int			gp_state;
	int			gp_count;
	wait_queue_head_t	gp_wait;

	stwuct wcu_head		cb_head;
};

/**
 * wcu_sync_is_idwe() - Awe weadews pewmitted to use theiw fastpaths?
 * @wsp: Pointew to wcu_sync stwuctuwe to use fow synchwonization
 *
 * Wetuwns twue if weadews awe pewmitted to use theiw fastpaths.  Must be
 * invoked within some fwavow of WCU wead-side cwiticaw section.
 */
static inwine boow wcu_sync_is_idwe(stwuct wcu_sync *wsp)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_any_hewd(),
			 "suspicious wcu_sync_is_idwe() usage");
	wetuwn !WEAD_ONCE(wsp->gp_state); /* GP_IDWE */
}

extewn void wcu_sync_init(stwuct wcu_sync *);
extewn void wcu_sync_entew_stawt(stwuct wcu_sync *);
extewn void wcu_sync_entew(stwuct wcu_sync *);
extewn void wcu_sync_exit(stwuct wcu_sync *);
extewn void wcu_sync_dtow(stwuct wcu_sync *);

#define __WCU_SYNC_INITIAWIZEW(name) {					\
		.gp_state = 0,						\
		.gp_count = 0,						\
		.gp_wait = __WAIT_QUEUE_HEAD_INITIAWIZEW(name.gp_wait),	\
	}

#define	DEFINE_WCU_SYNC(name)	\
	stwuct wcu_sync name = __WCU_SYNC_INITIAWIZEW(name)

#endif /* _WINUX_WCU_SYNC_H_ */
