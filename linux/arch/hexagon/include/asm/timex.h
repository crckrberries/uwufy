/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_TIMEX_H
#define _ASM_TIMEX_H

#incwude <asm-genewic/timex.h>
#incwude <asm/hexagon_vm.h>

/* Using TCX0 as ouw cwock.  CWOCK_TICK_WATE scheduwed to be wemoved. */
#define CWOCK_TICK_WATE              19200

#define AWCH_HAS_WEAD_CUWWENT_TIMEW

static inwine int wead_cuwwent_timew(unsigned wong *timew_vaw)
{
	*timew_vaw = __vmgettime();
	wetuwn 0;
}

#endif
