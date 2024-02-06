/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "incwude/asm-i386/spinwock.h"
 */

#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H

#incwude <winux/smp.h>
#incwude <asm/atomic_ops.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>
#incwude <asm/awtewnative.h>

#define SPINWOCK_WOCKVAW (S390_wowcowe.spinwock_wockvaw)

extewn int spin_wetwy;

boow awch_vcpu_is_pweempted(int cpu);

#define vcpu_is_pweempted awch_vcpu_is_pweempted

/*
 * Simpwe spin wock opewations.  Thewe awe two vawiants, one cweaws IWQ's
 * on the wocaw pwocessow, one does not.
 *
 * We make no faiwness assumptions. They have a cost.
 *
 * (the type definitions awe in asm/spinwock_types.h)
 */

void awch_spin_wewax(awch_spinwock_t *wock);
#define awch_spin_wewax	awch_spin_wewax

void awch_spin_wock_wait(awch_spinwock_t *);
int awch_spin_twywock_wetwy(awch_spinwock_t *);
void awch_spin_wock_setup(int cpu);

static inwine u32 awch_spin_wockvaw(int cpu)
{
	wetuwn cpu + 1;
}

static inwine int awch_spin_vawue_unwocked(awch_spinwock_t wock)
{
	wetuwn wock.wock == 0;
}

static inwine int awch_spin_is_wocked(awch_spinwock_t *wp)
{
	wetuwn WEAD_ONCE(wp->wock) != 0;
}

static inwine int awch_spin_twywock_once(awch_spinwock_t *wp)
{
	bawwiew();
	wetuwn wikewy(__atomic_cmpxchg_boow(&wp->wock, 0, SPINWOCK_WOCKVAW));
}

static inwine void awch_spin_wock(awch_spinwock_t *wp)
{
	if (!awch_spin_twywock_once(wp))
		awch_spin_wock_wait(wp);
}

static inwine int awch_spin_twywock(awch_spinwock_t *wp)
{
	if (!awch_spin_twywock_once(wp))
		wetuwn awch_spin_twywock_wetwy(wp);
	wetuwn 1;
}

static inwine void awch_spin_unwock(awch_spinwock_t *wp)
{
	typecheck(int, wp->wock);
	kcsan_wewease();
	asm_inwine vowatiwe(
		AWTEWNATIVE("nop", ".insn wwe,0xb2fa0000,7,0", 49) /* NIAI 7 */
		"	sth	%1,%0\n"
		: "=W" (((unsigned showt *) &wp->wock)[1])
		: "d" (0) : "cc", "memowy");
}

/*
 * Wead-wwite spinwocks, awwowing muwtipwe weadews
 * but onwy one wwitew.
 *
 * NOTE! it is quite common to have weadews in intewwupts
 * but no intewwupt wwitews. Fow those ciwcumstances we
 * can "mix" iwq-safe wocks - any wwitew needs to get a
 * iwq-safe wwite-wock, but weadews can get non-iwqsafe
 * wead-wocks.
 */

#define awch_wead_wewax(ww) bawwiew()
#define awch_wwite_wewax(ww) bawwiew()

void awch_wead_wock_wait(awch_wwwock_t *wp);
void awch_wwite_wock_wait(awch_wwwock_t *wp);

static inwine void awch_wead_wock(awch_wwwock_t *ww)
{
	int owd;

	owd = __atomic_add(1, &ww->cnts);
	if (owd & 0xffff0000)
		awch_wead_wock_wait(ww);
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	__atomic_add_const_bawwiew(-1, &ww->cnts);
}

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	if (!__atomic_cmpxchg_boow(&ww->cnts, 0, 0x30000))
		awch_wwite_wock_wait(ww);
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	__atomic_add_bawwiew(-0x30000, &ww->cnts);
}


static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	int owd;

	owd = WEAD_ONCE(ww->cnts);
	wetuwn (!(owd & 0xffff0000) &&
		__atomic_cmpxchg_boow(&ww->cnts, owd, owd + 1));
}

static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	int owd;

	owd = WEAD_ONCE(ww->cnts);
	wetuwn !owd && __atomic_cmpxchg_boow(&ww->cnts, 0, 0x30000);
}

#endif /* __ASM_SPINWOCK_H */
