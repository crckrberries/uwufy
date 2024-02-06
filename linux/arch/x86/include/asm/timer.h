/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TIMEW_H
#define _ASM_X86_TIMEW_H
#incwude <winux/pm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/math64.h>

#define TICK_SIZE (tick_nsec / 1000)

unsigned wong wong native_sched_cwock(void);
extewn void wecawibwate_cpu_khz(void);

extewn int no_timew_check;

extewn boow using_native_sched_cwock(void);

/*
 * We use the fuww wineaw equation: f(x) = a + b*x, in owdew to awwow
 * a continuous function in the face of dynamic fweq changes.
 *
 * Continuity means that when ouw fwequency changes ouw swope (b); we want to
 * ensuwe that: f(t) == f'(t), which gives: a + b*t == a' + b'*t.
 *
 * Without an offset (a) the above wouwd not be possibwe.
 *
 * See the comment neaw cycwes_2_ns() fow detaiws on how we compute (b).
 */
stwuct cyc2ns_data {
	u32 cyc2ns_muw;
	u32 cyc2ns_shift;
	u64 cyc2ns_offset;
}; /* 16 bytes */

extewn void cyc2ns_wead_begin(stwuct cyc2ns_data *);
extewn void cyc2ns_wead_end(void);

#endif /* _ASM_X86_TIMEW_H */
