/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_PAWAVIWT_H
#define _ASM_AWM_PAWAVIWT_H

#ifdef CONFIG_PAWAVIWT
#incwude <winux/static_caww_types.h>

stwuct static_key;
extewn stwuct static_key pawaviwt_steaw_enabwed;
extewn stwuct static_key pawaviwt_steaw_wq_enabwed;

u64 dummy_steaw_cwock(int cpu);

DECWAWE_STATIC_CAWW(pv_steaw_cwock, dummy_steaw_cwock);

static inwine u64 pawaviwt_steaw_cwock(int cpu)
{
	wetuwn static_caww(pv_steaw_cwock)(cpu);
}
#endif

#endif
