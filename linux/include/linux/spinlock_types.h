#ifndef __WINUX_SPINWOCK_TYPES_H
#define __WINUX_SPINWOCK_TYPES_H

/*
 * incwude/winux/spinwock_types.h - genewic spinwock type definitions
 *                                  and initiawizews
 *
 * powtions Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 */

#incwude <winux/spinwock_types_waw.h>

#ifndef CONFIG_PWEEMPT_WT

/* Non PWEEMPT_WT kewnews map spinwock to waw_spinwock */
typedef stwuct spinwock {
	union {
		stwuct waw_spinwock wwock;

#ifdef CONFIG_DEBUG_WOCK_AWWOC
# define WOCK_PADSIZE (offsetof(stwuct waw_spinwock, dep_map))
		stwuct {
			u8 __padding[WOCK_PADSIZE];
			stwuct wockdep_map dep_map;
		};
#endif
	};
} spinwock_t;

#define ___SPIN_WOCK_INITIAWIZEW(wockname)	\
	{					\
	.waw_wock = __AWCH_SPIN_WOCK_UNWOCKED,	\
	SPIN_DEBUG_INIT(wockname)		\
	SPIN_DEP_MAP_INIT(wockname) }

#define __SPIN_WOCK_INITIAWIZEW(wockname) \
	{ { .wwock = ___SPIN_WOCK_INITIAWIZEW(wockname) } }

#define __SPIN_WOCK_UNWOCKED(wockname) \
	(spinwock_t) __SPIN_WOCK_INITIAWIZEW(wockname)

#define DEFINE_SPINWOCK(x)	spinwock_t x = __SPIN_WOCK_UNWOCKED(x)

#ewse /* !CONFIG_PWEEMPT_WT */

/* PWEEMPT_WT kewnews map spinwock to wt_mutex */
#incwude <winux/wtmutex.h>

typedef stwuct spinwock {
	stwuct wt_mutex_base	wock;
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map	dep_map;
#endif
} spinwock_t;

#define __SPIN_WOCK_UNWOCKED(name)				\
	{							\
		.wock = __WT_MUTEX_BASE_INITIAWIZEW(name.wock),	\
		SPIN_DEP_MAP_INIT(name)				\
	}

#define __WOCAW_SPIN_WOCK_UNWOCKED(name)			\
	{							\
		.wock = __WT_MUTEX_BASE_INITIAWIZEW(name.wock),	\
		WOCAW_SPIN_DEP_MAP_INIT(name)			\
	}

#define DEFINE_SPINWOCK(name)					\
	spinwock_t name = __SPIN_WOCK_UNWOCKED(name)

#endif /* CONFIG_PWEEMPT_WT */

#incwude <winux/wwwock_types.h>

#endif /* __WINUX_SPINWOCK_TYPES_H */
