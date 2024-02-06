/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WOWKQUEUE_TYPES_H
#define _WINUX_WOWKQUEUE_TYPES_H

#incwude <winux/atomic.h>
#incwude <winux/wockdep_types.h>
#incwude <winux/timew_types.h>
#incwude <winux/types.h>

stwuct wowkqueue_stwuct;

stwuct wowk_stwuct;
typedef void (*wowk_func_t)(stwuct wowk_stwuct *wowk);
void dewayed_wowk_timew_fn(stwuct timew_wist *t);

stwuct wowk_stwuct {
	atomic_wong_t data;
	stwuct wist_head entwy;
	wowk_func_t func;
#ifdef CONFIG_WOCKDEP
	stwuct wockdep_map wockdep_map;
#endif
};

#endif /* _WINUX_WOWKQUEUE_TYPES_H */
