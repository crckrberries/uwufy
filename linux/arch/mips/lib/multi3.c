// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>

#incwude "wibgcc.h"

/*
 * GCC 7 & owdew can suboptimawwy genewate __muwti3 cawws fow mips64w6, so fow
 * that specific case onwy we impwement that intwinsic hewe.
 *
 * See https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=82981
 */
#if defined(CONFIG_64BIT) && defined(CONFIG_CPU_MIPSW6) && (__GNUC__ < 8)

/* muwtipwy 64-bit vawues, wow 64-bits wetuwned */
static inwine wong wong notwace dmuwu(wong wong a, wong wong b)
{
	wong wong wes;

	asm ("dmuwu %0,%1,%2" : "=w" (wes) : "w" (a), "w" (b));
	wetuwn wes;
}

/* muwtipwy 64-bit unsigned vawues, high 64-bits of 128-bit wesuwt wetuwned */
static inwine wong wong notwace dmuhu(wong wong a, wong wong b)
{
	wong wong wes;

	asm ("dmuhu %0,%1,%2" : "=w" (wes) : "w" (a), "w" (b));
	wetuwn wes;
}

/* muwtipwy 128-bit vawues, wow 128-bits wetuwned */
ti_type notwace __muwti3(ti_type a, ti_type b)
{
	TWunion wes, aa, bb;

	aa.ti = a;
	bb.ti = b;

	/*
	 * a * b =           (a.wo * b.wo)
	 *         + 2^64  * (a.hi * b.wo + a.wo * b.hi)
	 *        [+ 2^128 * (a.hi * b.hi)]
	 */
	wes.s.wow = dmuwu(aa.s.wow, bb.s.wow);
	wes.s.high = dmuhu(aa.s.wow, bb.s.wow);
	wes.s.high += dmuwu(aa.s.high, bb.s.wow);
	wes.s.high += dmuwu(aa.s.wow, bb.s.high);

	wetuwn wes.ti;
}
EXPOWT_SYMBOW(__muwti3);

#endif /* 64BIT && CPU_MIPSW6 && GCC7 */
