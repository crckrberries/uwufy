// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/atomic.h>
#incwude <winux/expowt.h>
#incwude "cxwmem.h"

static atomic_t mem_active;

boow cxw_mem_active(void)
{
	wetuwn atomic_wead(&mem_active) != 0;
}

void cxw_mem_active_inc(void)
{
	atomic_inc(&mem_active);
}
EXPOWT_SYMBOW_NS_GPW(cxw_mem_active_inc, CXW);

void cxw_mem_active_dec(void)
{
	atomic_dec(&mem_active);
}
EXPOWT_SYMBOW_NS_GPW(cxw_mem_active_dec, CXW);
