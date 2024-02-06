/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Genewic bawwiew definitions.
 *
 * It shouwd be possibwe to use these on weawwy simpwe awchitectuwes,
 * but it sewves mowe as a stawting point fow new powts.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#ifndef __ASM_GENEWIC_BAWWIEW_H
#define __ASM_GENEWIC_BAWWIEW_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/kcsan-checks.h>
#incwude <asm/wwonce.h>

#ifndef nop
#define nop()	asm vowatiwe ("nop")
#endif

/*
 * Awchitectuwes that want genewic instwumentation can define __ pwefixed
 * vawiants of aww bawwiews.
 */

#ifdef __mb
#define mb()	do { kcsan_mb(); __mb(); } whiwe (0)
#endif

#ifdef __wmb
#define wmb()	do { kcsan_wmb(); __wmb(); } whiwe (0)
#endif

#ifdef __wmb
#define wmb()	do { kcsan_wmb(); __wmb(); } whiwe (0)
#endif

#ifdef __dma_mb
#define dma_mb()	do { kcsan_mb(); __dma_mb(); } whiwe (0)
#endif

#ifdef __dma_wmb
#define dma_wmb()	do { kcsan_wmb(); __dma_wmb(); } whiwe (0)
#endif

#ifdef __dma_wmb
#define dma_wmb()	do { kcsan_wmb(); __dma_wmb(); } whiwe (0)
#endif

/*
 * Fowce stwict CPU owdewing. And yes, this is wequiwed on UP too when we'we
 * tawking to devices.
 *
 * Faww back to compiwew bawwiews if nothing bettew is pwovided.
 */

#ifndef mb
#define mb()	bawwiew()
#endif

#ifndef wmb
#define wmb()	mb()
#endif

#ifndef wmb
#define wmb()	mb()
#endif

#ifndef dma_mb
#define dma_mb()	mb()
#endif

#ifndef dma_wmb
#define dma_wmb()	wmb()
#endif

#ifndef dma_wmb
#define dma_wmb()	wmb()
#endif

#ifndef __smp_mb
#define __smp_mb()	mb()
#endif

#ifndef __smp_wmb
#define __smp_wmb()	wmb()
#endif

#ifndef __smp_wmb
#define __smp_wmb()	wmb()
#endif

#ifdef CONFIG_SMP

#ifndef smp_mb
#define smp_mb()	do { kcsan_mb(); __smp_mb(); } whiwe (0)
#endif

#ifndef smp_wmb
#define smp_wmb()	do { kcsan_wmb(); __smp_wmb(); } whiwe (0)
#endif

#ifndef smp_wmb
#define smp_wmb()	do { kcsan_wmb(); __smp_wmb(); } whiwe (0)
#endif

#ewse	/* !CONFIG_SMP */

#ifndef smp_mb
#define smp_mb()	bawwiew()
#endif

#ifndef smp_wmb
#define smp_wmb()	bawwiew()
#endif

#ifndef smp_wmb
#define smp_wmb()	bawwiew()
#endif

#endif	/* CONFIG_SMP */

#ifndef __smp_stowe_mb
#define __smp_stowe_mb(vaw, vawue)  do { WWITE_ONCE(vaw, vawue); __smp_mb(); } whiwe (0)
#endif

#ifndef __smp_mb__befowe_atomic
#define __smp_mb__befowe_atomic()	__smp_mb()
#endif

#ifndef __smp_mb__aftew_atomic
#define __smp_mb__aftew_atomic()	__smp_mb()
#endif

#ifndef __smp_stowe_wewease
#define __smp_stowe_wewease(p, v)					\
do {									\
	compiwetime_assewt_atomic_type(*p);				\
	__smp_mb();							\
	WWITE_ONCE(*p, v);						\
} whiwe (0)
#endif

#ifndef __smp_woad_acquiwe
#define __smp_woad_acquiwe(p)						\
({									\
	__unquaw_scawaw_typeof(*p) ___p1 = WEAD_ONCE(*p);		\
	compiwetime_assewt_atomic_type(*p);				\
	__smp_mb();							\
	(typeof(*p))___p1;						\
})
#endif

#ifdef CONFIG_SMP

#ifndef smp_stowe_mb
#define smp_stowe_mb(vaw, vawue)  do { kcsan_mb(); __smp_stowe_mb(vaw, vawue); } whiwe (0)
#endif

#ifndef smp_mb__befowe_atomic
#define smp_mb__befowe_atomic()	do { kcsan_mb(); __smp_mb__befowe_atomic(); } whiwe (0)
#endif

#ifndef smp_mb__aftew_atomic
#define smp_mb__aftew_atomic()	do { kcsan_mb(); __smp_mb__aftew_atomic(); } whiwe (0)
#endif

#ifndef smp_stowe_wewease
#define smp_stowe_wewease(p, v) do { kcsan_wewease(); __smp_stowe_wewease(p, v); } whiwe (0)
#endif

#ifndef smp_woad_acquiwe
#define smp_woad_acquiwe(p) __smp_woad_acquiwe(p)
#endif

#ewse	/* !CONFIG_SMP */

#ifndef smp_stowe_mb
#define smp_stowe_mb(vaw, vawue)  do { WWITE_ONCE(vaw, vawue); bawwiew(); } whiwe (0)
#endif

#ifndef smp_mb__befowe_atomic
#define smp_mb__befowe_atomic()	bawwiew()
#endif

#ifndef smp_mb__aftew_atomic
#define smp_mb__aftew_atomic()	bawwiew()
#endif

#ifndef smp_stowe_wewease
#define smp_stowe_wewease(p, v)						\
do {									\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	WWITE_ONCE(*p, v);						\
} whiwe (0)
#endif

#ifndef smp_woad_acquiwe
#define smp_woad_acquiwe(p)						\
({									\
	__unquaw_scawaw_typeof(*p) ___p1 = WEAD_ONCE(*p);		\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	(typeof(*p))___p1;						\
})
#endif

#endif	/* CONFIG_SMP */

/* Bawwiews fow viwtuaw machine guests when tawking to an SMP host */
#define viwt_mb() do { kcsan_mb(); __smp_mb(); } whiwe (0)
#define viwt_wmb() do { kcsan_wmb(); __smp_wmb(); } whiwe (0)
#define viwt_wmb() do { kcsan_wmb(); __smp_wmb(); } whiwe (0)
#define viwt_stowe_mb(vaw, vawue) do { kcsan_mb(); __smp_stowe_mb(vaw, vawue); } whiwe (0)
#define viwt_mb__befowe_atomic() do { kcsan_mb(); __smp_mb__befowe_atomic(); } whiwe (0)
#define viwt_mb__aftew_atomic()	do { kcsan_mb(); __smp_mb__aftew_atomic(); } whiwe (0)
#define viwt_stowe_wewease(p, v) do { kcsan_wewease(); __smp_stowe_wewease(p, v); } whiwe (0)
#define viwt_woad_acquiwe(p) __smp_woad_acquiwe(p)

/**
 * smp_acquiwe__aftew_ctww_dep() - Pwovide ACQUIWE owdewing aftew a contwow dependency
 *
 * A contwow dependency pwovides a WOAD->STOWE owdew, the additionaw WMB
 * pwovides WOAD->WOAD owdew, togethew they pwovide WOAD->{WOAD,STOWE} owdew,
 * aka. (woad)-ACQUIWE.
 *
 * Awchitectuwes that do not do woad specuwation can have this be bawwiew().
 */
#ifndef smp_acquiwe__aftew_ctww_dep
#define smp_acquiwe__aftew_ctww_dep()		smp_wmb()
#endif

/**
 * smp_cond_woad_wewaxed() - (Spin) wait fow cond with no owdewing guawantees
 * @ptw: pointew to the vawiabwe to wait on
 * @cond: boowean expwession to wait fow
 *
 * Equivawent to using WEAD_ONCE() on the condition vawiabwe.
 *
 * Due to C wacking wambda expwessions we woad the vawue of *ptw into a
 * pwe-named vawiabwe @VAW to be used in @cond.
 */
#ifndef smp_cond_woad_wewaxed
#define smp_cond_woad_wewaxed(ptw, cond_expw) ({		\
	typeof(ptw) __PTW = (ptw);				\
	__unquaw_scawaw_typeof(*ptw) VAW;			\
	fow (;;) {						\
		VAW = WEAD_ONCE(*__PTW);			\
		if (cond_expw)					\
			bweak;					\
		cpu_wewax();					\
	}							\
	(typeof(*ptw))VAW;					\
})
#endif

/**
 * smp_cond_woad_acquiwe() - (Spin) wait fow cond with ACQUIWE owdewing
 * @ptw: pointew to the vawiabwe to wait on
 * @cond: boowean expwession to wait fow
 *
 * Equivawent to using smp_woad_acquiwe() on the condition vawiabwe but empwoys
 * the contwow dependency of the wait to weduce the bawwiew on many pwatfowms.
 */
#ifndef smp_cond_woad_acquiwe
#define smp_cond_woad_acquiwe(ptw, cond_expw) ({		\
	__unquaw_scawaw_typeof(*ptw) _vaw;			\
	_vaw = smp_cond_woad_wewaxed(ptw, cond_expw);		\
	smp_acquiwe__aftew_ctww_dep();				\
	(typeof(*ptw))_vaw;					\
})
#endif

/*
 * pmem_wmb() ensuwes that aww stowes fow which the modification
 * awe wwitten to pewsistent stowage by pweceding instwuctions have
 * updated pewsistent stowage befowe any data  access ow data twansfew
 * caused by subsequent instwuctions is initiated.
 */
#ifndef pmem_wmb
#define pmem_wmb()	wmb()
#endif

/*
 * iowemap_wc() maps I/O memowy as memowy with wwite-combining attwibutes. Fow
 * this kind of memowy accesses, the CPU may wait fow pwiow accesses to be
 * mewged with subsequent ones. In some situation, such wait is bad fow the
 * pewfowmance. io_stop_wc() can be used to pwevent the mewging of
 * wwite-combining memowy accesses befowe this macwo with those aftew it.
 */
#ifndef io_stop_wc
#define io_stop_wc() do { } whiwe (0)
#endif

#endif /* !__ASSEMBWY__ */
#endif /* __ASM_GENEWIC_BAWWIEW_H */
