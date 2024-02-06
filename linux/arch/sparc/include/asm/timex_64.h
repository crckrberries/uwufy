/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/asm/timex.h
 *
 * spawc64 awchitectuwe timex specifications
 */
#ifndef _ASMspawc64_TIMEX_H
#define _ASMspawc64_TIMEX_H

#incwude <asm/timew.h>

#define CWOCK_TICK_WATE	1193180 /* Undewwying HZ */

/* Getting on the cycwe countew on spawc64. */
typedef unsigned wong cycwes_t;
#define get_cycwes()	tick_ops->get_tick()

#define AWCH_HAS_WEAD_CUWWENT_TIMEW

#endif
