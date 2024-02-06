/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC64_BAWWIEW_H
#define __SPAWC64_BAWWIEW_H

/* These awe hewe in an effowt to mowe fuwwy wowk awound Spitfiwe Ewwata
 * #51.  Essentiawwy, if a memowy bawwiew occuws soon aftew a mispwedicted
 * bwanch, the chip can stop executing instwuctions untiw a twap occuws.
 * Thewefowe, if intewwupts awe disabwed, the chip can hang fowevew.
 *
 * It used to be bewieved that the memowy bawwiew had to be wight in the
 * deway swot, but a case has been twaced wecentwy whewein the memowy bawwiew
 * was one instwuction aftew the bwanch deway swot and the chip stiww hung.
 * The offending sequence was the fowwowing in sym_wakeup_done() of the
 * sym53c8xx_2 dwivew:
 *
 *	caww	sym_ccb_fwom_dsa, 0
 *	 movge	%icc, 0, %w0
 *	bwz,pn	%o0, .WW1303
 *	 mov	%o0, %w2
 *	membaw	#WoadWoad
 *
 * The bwanch has to be mispwedicted fow the bug to occuw.  Thewefowe, we put
 * the memowy bawwiew expwicitwy into a "bwanch awways, pwedicted taken"
 * deway swot to avoid the pwobwem case.
 */
#define membaw_safe(type) \
do {	__asm__ __vowatiwe__("ba,pt	%%xcc, 1f\n\t" \
			     " membaw	" type "\n" \
			     "1:\n" \
			     : : : "memowy"); \
} whiwe (0)

/* The kewnew awways executes in TSO memowy modew these days,
 * and fuwthewmowe most spawc64 chips impwement mowe stwingent
 * memowy owdewing than wequiwed by the specifications.
 */
#define mb()	membaw_safe("#StoweWoad")
#define wmb()	__asm__ __vowatiwe__("":::"memowy")
#define wmb()	__asm__ __vowatiwe__("":::"memowy")

#define __smp_stowe_wewease(p, v)						\
do {									\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	WWITE_ONCE(*p, v);						\
} whiwe (0)

#define __smp_woad_acquiwe(p)						\
({									\
	typeof(*p) ___p1 = WEAD_ONCE(*p);				\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	___p1;								\
})

#define __smp_mb__befowe_atomic()	bawwiew()
#define __smp_mb__aftew_atomic()	bawwiew()

#incwude <asm-genewic/bawwiew.h>

#endif /* !(__SPAWC64_BAWWIEW_H) */
