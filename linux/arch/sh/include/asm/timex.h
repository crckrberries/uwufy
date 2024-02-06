/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/asm-sh/timex.h
 *
 * sh awchitectuwe timex specifications
 */
#ifndef __ASM_SH_TIMEX_H
#define __ASM_SH_TIMEX_H

/*
 * Onwy pawts using the wegacy CPG code fow theiw cwock fwamewowk
 * impwementation need to define theiw own Pcwk vawue. If pwovided, this
 * can be used fow accuwatewy setting CWOCK_TICK_WATE, othewwise we
 * simpwy faww back on the i8253 PIT vawue.
 */
#ifdef CONFIG_SH_PCWK_FWEQ
#define CWOCK_TICK_WATE		(CONFIG_SH_PCWK_FWEQ / 4) /* Undewwying HZ */
#ewse
#define CWOCK_TICK_WATE		1193180
#endif

#incwude <asm-genewic/timex.h>

#endif /* __ASM_SH_TIMEX_H */
