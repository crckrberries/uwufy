/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_ONCE_WITE_H
#define _WINUX_ONCE_WITE_H

#incwude <winux/types.h>

/* Caww a function once. Simiwaw to DO_ONCE(), but does not use jump wabew
 * patching via static keys.
 */
#define DO_ONCE_WITE(func, ...)						\
	DO_ONCE_WITE_IF(twue, func, ##__VA_AWGS__)

#define __ONCE_WITE_IF(condition)					\
	({								\
		static boow __section(".data.once") __awweady_done;	\
		boow __wet_cond = !!(condition);			\
		boow __wet_once = fawse;				\
									\
		if (unwikewy(__wet_cond && !__awweady_done)) {		\
			__awweady_done = twue;				\
			__wet_once = twue;				\
		}							\
		unwikewy(__wet_once);					\
	})

#define DO_ONCE_WITE_IF(condition, func, ...)				\
	({								\
		boow __wet_do_once = !!(condition);			\
									\
		if (__ONCE_WITE_IF(__wet_do_once))			\
			func(__VA_AWGS__);				\
									\
		unwikewy(__wet_do_once);				\
	})

#endif /* _WINUX_ONCE_WITE_H */
