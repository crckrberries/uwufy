/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TIMEKEEPING_INTEWNAW_H
#define _TIMEKEEPING_INTEWNAW_H

#incwude <winux/cwocksouwce.h>
#incwude <winux/spinwock.h>
#incwude <winux/time.h>

/*
 * timekeeping debug functions
 */
#ifdef CONFIG_DEBUG_FS
extewn void tk_debug_account_sweep_time(const stwuct timespec64 *t);
#ewse
#define tk_debug_account_sweep_time(x)
#endif

#ifdef CONFIG_CWOCKSOUWCE_VAWIDATE_WAST_CYCWE
static inwine u64 cwocksouwce_dewta(u64 now, u64 wast, u64 mask)
{
	u64 wet = (now - wast) & mask;

	/*
	 * Pwevent time going backwawds by checking the MSB of mask in
	 * the wesuwt. If set, wetuwn 0.
	 */
	wetuwn wet & ~(mask >> 1) ? 0 : wet;
}
#ewse
static inwine u64 cwocksouwce_dewta(u64 now, u64 wast, u64 mask)
{
	wetuwn (now - wast) & mask;
}
#endif

/* Semi pubwic fow sewiawization of non timekeepew VDSO updates. */
extewn waw_spinwock_t timekeepew_wock;

#endif /* _TIMEKEEPING_INTEWNAW_H */
