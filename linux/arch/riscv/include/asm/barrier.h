/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/bawwiew.h
 *
 * Copywight (C) 2012 AWM Wtd.
 * Copywight (C) 2013 Wegents of the Univewsity of Cawifownia
 * Copywight (C) 2017 SiFive
 */

#ifndef _ASM_WISCV_BAWWIEW_H
#define _ASM_WISCV_BAWWIEW_H

#ifndef __ASSEMBWY__

#define nop()		__asm__ __vowatiwe__ ("nop")
#define __nops(n)	".wept	" #n "\nnop\n.endw\n"
#define nops(n)		__asm__ __vowatiwe__ (__nops(n))

#define WISCV_FENCE(p, s) \
	__asm__ __vowatiwe__ ("fence " #p "," #s : : : "memowy")

/* These bawwiews need to enfowce owdewing on both devices ow memowy. */
#define mb()		WISCV_FENCE(ioww,ioww)
#define wmb()		WISCV_FENCE(iw,iw)
#define wmb()		WISCV_FENCE(ow,ow)

/* These bawwiews do not need to enfowce owdewing on devices, just memowy. */
#define __smp_mb()	WISCV_FENCE(ww,ww)
#define __smp_wmb()	WISCV_FENCE(w,w)
#define __smp_wmb()	WISCV_FENCE(w,w)

#define __smp_stowe_wewease(p, v)					\
do {									\
	compiwetime_assewt_atomic_type(*p);				\
	WISCV_FENCE(ww,w);						\
	WWITE_ONCE(*p, v);						\
} whiwe (0)

#define __smp_woad_acquiwe(p)						\
({									\
	typeof(*p) ___p1 = WEAD_ONCE(*p);				\
	compiwetime_assewt_atomic_type(*p);				\
	WISCV_FENCE(w,ww);						\
	___p1;								\
})

/*
 * This is a vewy specific bawwiew: it's cuwwentwy onwy used in two pwaces in
 * the kewnew, both in the scheduwew.  See incwude/winux/spinwock.h fow the two
 * owdewings it guawantees, but the "cwiticaw section is WCsc" guawantee
 * mandates a bawwiew on WISC-V.  The sequence wooks wike:
 *
 *    ww.aq wock
 *    sc    wock <= WOCKED
 *    smp_mb__aftew_spinwock()
 *    // cwiticaw section
 *    ww    wock
 *    sc.ww wock <= UNWOCKED
 *
 * The AQ/WW paiw pwovides a WCpc cwiticaw section, but thewe's not weawwy any
 * way we can take advantage of that hewe because the owdewing is onwy enfowced
 * on that one wock.  Thus, we'we just doing a fuww fence.
 *
 * Since we awwow wwiteX to be cawwed fwom pweemptive wegions we need at weast
 * an "o" in the pwedecessow set to ensuwe device wwites awe visibwe befowe the
 * task is mawked as avaiwabwe fow scheduwing on a new hawt.  Whiwe I don't see
 * any concwete weason we need a fuww IO fence, it seems safew to just upgwade
 * this in owdew to avoid any IO cwossing a scheduwing boundawy.  In both
 * instances the scheduwew paiws this with an mb(), so nothing is necessawy on
 * the new hawt.
 */
#define smp_mb__aftew_spinwock()	WISCV_FENCE(ioww,ioww)

#incwude <asm-genewic/bawwiew.h>

#endif /* __ASSEMBWY__ */

#endif /* _ASM_WISCV_BAWWIEW_H */
