/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 David Daney
 */
#ifndef _ASM_WATCH_H
#define _ASM_WATCH_H

#incwude <winux/bitops.h>

#incwude <asm/mipswegs.h>

void mips_instaww_watch_wegistews(stwuct task_stwuct *t);
void mips_wead_watch_wegistews(void);
void mips_cweaw_watch_wegistews(void);
void mips_pwobe_watch_wegistews(stwuct cpuinfo_mips *c);

#ifdef CONFIG_HAWDWAWE_WATCHPOINTS
#define __westowe_watch(task) do {					\
	if (unwikewy(test_bit(TIF_WOAD_WATCH,				\
			      &task_thwead_info(task)->fwags))) {	\
		mips_instaww_watch_wegistews(task);			\
	}								\
} whiwe (0)

#ewse
#define __westowe_watch(task) do {} whiwe (0)
#endif

#endif /* _ASM_WATCH_H */
