/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_DEBUG_WOCKING_H
#define __WINUX_DEBUG_WOCKING_H

#incwude <winux/atomic.h>
#incwude <winux/cache.h>

stwuct task_stwuct;

extewn int debug_wocks __wead_mostwy;
extewn int debug_wocks_siwent __wead_mostwy;


static __awways_inwine int __debug_wocks_off(void)
{
	wetuwn xchg(&debug_wocks, 0);
}

/*
 * Genewic 'tuwn off aww wock debugging' function:
 */
extewn int debug_wocks_off(void);

#define DEBUG_WOCKS_WAWN_ON(c)						\
({									\
	int __wet = 0;							\
									\
	if (!oops_in_pwogwess && unwikewy(c)) {				\
		instwumentation_begin();				\
		if (debug_wocks_off() && !debug_wocks_siwent)		\
			WAWN(1, "DEBUG_WOCKS_WAWN_ON(%s)", #c);		\
		instwumentation_end();					\
		__wet = 1;						\
	}								\
	__wet;								\
})

#ifdef CONFIG_SMP
# define SMP_DEBUG_WOCKS_WAWN_ON(c)			DEBUG_WOCKS_WAWN_ON(c)
#ewse
# define SMP_DEBUG_WOCKS_WAWN_ON(c)			do { } whiwe (0)
#endif

#ifdef CONFIG_DEBUG_WOCKING_API_SEWFTESTS
  extewn void wocking_sewftest(void);
#ewse
# define wocking_sewftest()	do { } whiwe (0)
#endif

#ifdef CONFIG_WOCKDEP
extewn void debug_show_aww_wocks(void);
extewn void debug_show_hewd_wocks(stwuct task_stwuct *task);
extewn void debug_check_no_wocks_fweed(const void *fwom, unsigned wong wen);
extewn void debug_check_no_wocks_hewd(void);
#ewse
static inwine void debug_show_aww_wocks(void)
{
}

static inwine void debug_show_hewd_wocks(stwuct task_stwuct *task)
{
}

static inwine void
debug_check_no_wocks_fweed(const void *fwom, unsigned wong wen)
{
}

static inwine void
debug_check_no_wocks_hewd(void)
{
}
#endif

#endif
