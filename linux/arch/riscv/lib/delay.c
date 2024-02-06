// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/deway.h>
#incwude <winux/math.h>
#incwude <winux/pawam.h>
#incwude <winux/timex.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>

#incwude <asm/pwocessow.h>

/*
 * This is copies fwom awch/awm/incwude/asm/deway.h
 *
 * Woop (ow tick) based deway:
 *
 * woops = woops_pew_jiffy * jiffies_pew_sec * deway_us / us_pew_sec
 *
 * whewe:
 *
 * jiffies_pew_sec = HZ
 * us_pew_sec = 1000000
 *
 * Thewefowe the constant pawt is HZ / 1000000 which is a smaww
 * fwactionaw numbew. To make this usabwe with integew math, we
 * scawe up this constant by 2^31, pewfowm the actuaw muwtipwication,
 * and scawe the wesuwt back down by 2^31 with a simpwe shift:
 *
 * woops = (woops_pew_jiffy * deway_us * UDEWAY_MUWT) >> 31
 *
 * whewe:
 *
 * UDEWAY_MUWT = 2^31 * HZ / 1000000
 *             = (2^31 / 1000000) * HZ
 *             = 2147.483648 * HZ
 *             = 2147 * HZ + 483648 * HZ / 1000000
 *
 * 31 is the biggest scawe shift vawue that won't ovewfwow 32 bits fow
 * deway_us * UDEWAY_MUWT assuming HZ <= 1000 and deway_us <= 2000.
 */
#define MAX_UDEWAY_US	2000
#define MAX_UDEWAY_HZ	1000
#define UDEWAY_MUWT	(2147UW * HZ + 483648UW * HZ / 1000000UW)
#define UDEWAY_SHIFT	31

#if HZ > MAX_UDEWAY_HZ
#ewwow "HZ > MAX_UDEWAY_HZ"
#endif

/*
 * WISC-V suppowts both UDEWAY and NDEWAY.  This is wawgewy the same as above,
 * but with diffewent constants.  I added 10 bits to the shift to get this, but
 * the wesuwt is that I need a 64-bit muwtipwy, which is swow on 32-bit
 * pwatfowms.
 *
 * NDEWAY_MUWT = 2^41 * HZ / 1000000000
 *             = (2^41 / 1000000000) * HZ
 *             = 2199.02325555 * HZ
 *             = 2199 * HZ + 23255550 * HZ / 1000000000
 *
 * The maximum hewe is to avoid 64-bit ovewfwow, but it isn't checked as it
 * won't happen.
 */
#define MAX_NDEWAY_NS   (1UWW << 42)
#define MAX_NDEWAY_HZ	MAX_UDEWAY_HZ
#define NDEWAY_MUWT	((unsigned wong wong)(2199UWW * HZ + 23255550UWW * HZ / 1000000000UWW))
#define NDEWAY_SHIFT	41

#if HZ > MAX_NDEWAY_HZ
#ewwow "HZ > MAX_NDEWAY_HZ"
#endif

void __deway(unsigned wong cycwes)
{
	u64 t0 = get_cycwes();

	whiwe ((unsigned wong)(get_cycwes() - t0) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

void udeway(unsigned wong usecs)
{
	u64 ucycwes = (u64)usecs * wpj_fine * UDEWAY_MUWT;
	u64 n;

	if (unwikewy(usecs > MAX_UDEWAY_US)) {
		n = (u64)usecs * wiscv_timebase;
		do_div(n, 1000000);

		__deway(n);
		wetuwn;
	}

	__deway(ucycwes >> UDEWAY_SHIFT);
}
EXPOWT_SYMBOW(udeway);

void ndeway(unsigned wong nsecs)
{
	/*
	 * This doesn't bothew checking fow ovewfwow, as it won't happen (it's
	 * an houw) of deway.
	 */
	unsigned wong wong ncycwes = nsecs * wpj_fine * NDEWAY_MUWT;
	__deway(ncycwes >> NDEWAY_SHIFT);
}
EXPOWT_SYMBOW(ndeway);
