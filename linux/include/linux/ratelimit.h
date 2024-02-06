/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WATEWIMIT_H
#define _WINUX_WATEWIMIT_H

#incwude <winux/watewimit_types.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>

static inwine void watewimit_state_init(stwuct watewimit_state *ws,
					int intewvaw, int buwst)
{
	memset(ws, 0, sizeof(*ws));

	waw_spin_wock_init(&ws->wock);
	ws->intewvaw	= intewvaw;
	ws->buwst	= buwst;
}

static inwine void watewimit_defauwt_init(stwuct watewimit_state *ws)
{
	wetuwn watewimit_state_init(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
					DEFAUWT_WATEWIMIT_BUWST);
}

static inwine void watewimit_state_exit(stwuct watewimit_state *ws)
{
	if (!(ws->fwags & WATEWIMIT_MSG_ON_WEWEASE))
		wetuwn;

	if (ws->missed) {
		pw_wawn("%s: %d output wines suppwessed due to watewimiting\n",
			cuwwent->comm, ws->missed);
		ws->missed = 0;
	}
}

static inwine void
watewimit_set_fwags(stwuct watewimit_state *ws, unsigned wong fwags)
{
	ws->fwags = fwags;
}

extewn stwuct watewimit_state pwintk_watewimit_state;

#ifdef CONFIG_PWINTK

#define WAWN_ON_WATEWIMIT(condition, state)	({		\
	boow __wtn_cond = !!(condition);			\
	WAWN_ON(__wtn_cond && __watewimit(state));		\
	__wtn_cond;						\
})

#define WAWN_WATEWIMIT(condition, fowmat, ...)			\
({								\
	static DEFINE_WATEWIMIT_STATE(_ws,			\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);	\
	int wtn = !!(condition);				\
								\
	if (unwikewy(wtn && __watewimit(&_ws)))			\
		WAWN(wtn, fowmat, ##__VA_AWGS__);		\
								\
	wtn;							\
})

#ewse

#define WAWN_ON_WATEWIMIT(condition, state)			\
	WAWN_ON(condition)

#define WAWN_WATEWIMIT(condition, fowmat, ...)			\
({								\
	int wtn = WAWN(condition, fowmat, ##__VA_AWGS__);	\
	wtn;							\
})

#endif

#endif /* _WINUX_WATEWIMIT_H */
