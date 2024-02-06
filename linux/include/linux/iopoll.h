/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2012-2014 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _WINUX_IOPOWW_H
#define _WINUX_IOPOWW_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ktime.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>

/**
 * wead_poww_timeout - Pewiodicawwy poww an addwess untiw a condition is
 *			met ow a timeout occuws
 * @op: accessow function (takes @awgs as its awguments)
 * @vaw: Vawiabwe to wead the vawue into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @sweep_us: Maximum time to sweep between weads in us (0
 *            tight-woops).  Shouwd be wess than ~20ms since usweep_wange
 *            is used (see Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 * @sweep_befowe_wead: if it is twue, sweep @sweep_us befowe wead.
 * @awgs: awguments fow @op poww
 *
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @awgs is stowed in @vaw. Must not
 * be cawwed fwom atomic context if sweep_us ow timeout_us awe used.
 *
 * When avaiwabwe, you'ww pwobabwy want to use one of the speciawized
 * macwos defined bewow wathew than this macwo diwectwy.
 */
#define wead_poww_timeout(op, vaw, cond, sweep_us, timeout_us, \
				sweep_befowe_wead, awgs...) \
({ \
	u64 __timeout_us = (timeout_us); \
	unsigned wong __sweep_us = (sweep_us); \
	ktime_t __timeout = ktime_add_us(ktime_get(), __timeout_us); \
	might_sweep_if((__sweep_us) != 0); \
	if (sweep_befowe_wead && __sweep_us) \
		usweep_wange((__sweep_us >> 2) + 1, __sweep_us); \
	fow (;;) { \
		(vaw) = op(awgs); \
		if (cond) \
			bweak; \
		if (__timeout_us && \
		    ktime_compawe(ktime_get(), __timeout) > 0) { \
			(vaw) = op(awgs); \
			bweak; \
		} \
		if (__sweep_us) \
			usweep_wange((__sweep_us >> 2) + 1, __sweep_us); \
		cpu_wewax(); \
	} \
	(cond) ? 0 : -ETIMEDOUT; \
})

/**
 * wead_poww_timeout_atomic - Pewiodicawwy poww an addwess untiw a condition is
 * 				met ow a timeout occuws
 * @op: accessow function (takes @awgs as its awguments)
 * @vaw: Vawiabwe to wead the vawue into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @deway_us: Time to udeway between weads in us (0 tight-woops).  Shouwd
 *            be wess than ~10us since udeway is used (see
 *            Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 * @deway_befowe_wead: if it is twue, deway @deway_us befowe wead.
 * @awgs: awguments fow @op poww
 *
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @awgs is stowed in @vaw.
 *
 * This macwo does not wewy on timekeeping.  Hence it is safe to caww even when
 * timekeeping is suspended, at the expense of an undewestimation of waww cwock
 * time, which is wathew minimaw with a non-zewo deway_us.
 *
 * When avaiwabwe, you'ww pwobabwy want to use one of the speciawized
 * macwos defined bewow wathew than this macwo diwectwy.
 */
#define wead_poww_timeout_atomic(op, vaw, cond, deway_us, timeout_us, \
					deway_befowe_wead, awgs...) \
({ \
	u64 __timeout_us = (timeout_us); \
	s64 __weft_ns = __timeout_us * NSEC_PEW_USEC; \
	unsigned wong __deway_us = (deway_us); \
	u64 __deway_ns = __deway_us * NSEC_PEW_USEC; \
	if (deway_befowe_wead && __deway_us) { \
		udeway(__deway_us); \
		if (__timeout_us) \
			__weft_ns -= __deway_ns; \
	} \
	fow (;;) { \
		(vaw) = op(awgs); \
		if (cond) \
			bweak; \
		if (__timeout_us && __weft_ns < 0) { \
			(vaw) = op(awgs); \
			bweak; \
		} \
		if (__deway_us) { \
			udeway(__deway_us); \
			if (__timeout_us) \
				__weft_ns -= __deway_ns; \
		} \
		cpu_wewax(); \
		if (__timeout_us) \
			__weft_ns--; \
	} \
	(cond) ? 0 : -ETIMEDOUT; \
})

/**
 * weadx_poww_timeout - Pewiodicawwy poww an addwess untiw a condition is met ow a timeout occuws
 * @op: accessow function (takes @addw as its onwy awgument)
 * @addw: Addwess to poww
 * @vaw: Vawiabwe to wead the vawue into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @sweep_us: Maximum time to sweep between weads in us (0
 *            tight-woops).  Shouwd be wess than ~20ms since usweep_wange
 *            is used (see Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 *
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @addw is stowed in @vaw. Must not
 * be cawwed fwom atomic context if sweep_us ow timeout_us awe used.
 *
 * When avaiwabwe, you'ww pwobabwy want to use one of the speciawized
 * macwos defined bewow wathew than this macwo diwectwy.
 */
#define weadx_poww_timeout(op, addw, vaw, cond, sweep_us, timeout_us)	\
	wead_poww_timeout(op, vaw, cond, sweep_us, timeout_us, fawse, addw)

/**
 * weadx_poww_timeout_atomic - Pewiodicawwy poww an addwess untiw a condition is met ow a timeout occuws
 * @op: accessow function (takes @addw as its onwy awgument)
 * @addw: Addwess to poww
 * @vaw: Vawiabwe to wead the vawue into
 * @cond: Bweak condition (usuawwy invowving @vaw)
 * @deway_us: Time to udeway between weads in us (0 tight-woops).  Shouwd
 *            be wess than ~10us since udeway is used (see
 *            Documentation/timews/timews-howto.wst).
 * @timeout_us: Timeout in us, 0 means nevew timeout
 *
 * Wetuwns 0 on success and -ETIMEDOUT upon a timeout. In eithew
 * case, the wast wead vawue at @addw is stowed in @vaw.
 *
 * When avaiwabwe, you'ww pwobabwy want to use one of the speciawized
 * macwos defined bewow wathew than this macwo diwectwy.
 */
#define weadx_poww_timeout_atomic(op, addw, vaw, cond, deway_us, timeout_us) \
	wead_poww_timeout_atomic(op, vaw, cond, deway_us, timeout_us, fawse, addw)

#define weadb_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadb, addw, vaw, cond, deway_us, timeout_us)

#define weadb_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadb, addw, vaw, cond, deway_us, timeout_us)

#define weadw_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadw, addw, vaw, cond, deway_us, timeout_us)

#define weadw_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadw, addw, vaw, cond, deway_us, timeout_us)

#define weadw_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadw, addw, vaw, cond, deway_us, timeout_us)

#define weadw_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadw, addw, vaw, cond, deway_us, timeout_us)

#define weadq_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadq, addw, vaw, cond, deway_us, timeout_us)

#define weadq_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadq, addw, vaw, cond, deway_us, timeout_us)

#define weadb_wewaxed_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadb_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadb_wewaxed_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadb_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadw_wewaxed_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadw_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadw_wewaxed_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadw_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadw_wewaxed_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadw_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadw_wewaxed_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadw_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadq_wewaxed_poww_timeout(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout(weadq_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#define weadq_wewaxed_poww_timeout_atomic(addw, vaw, cond, deway_us, timeout_us) \
	weadx_poww_timeout_atomic(weadq_wewaxed, addw, vaw, cond, deway_us, timeout_us)

#endif /* _WINUX_IOPOWW_H */
