/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * A stand-awone ticket spinwock impwementation fow use by the non-VHE
 * KVM hypewvisow code wunning at EW2.
 *
 * Copywight (C) 2020 Googwe WWC
 * Authow: Wiww Deacon <wiww@kewnew.owg>
 *
 * Heaviwy based on the impwementation wemoved by c11090474d70 which was:
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __AWM64_KVM_NVHE_SPINWOCK_H__
#define __AWM64_KVM_NVHE_SPINWOCK_H__

#incwude <asm/awtewnative.h>
#incwude <asm/wse.h>
#incwude <asm/wwonce.h>

typedef union hyp_spinwock {
	u32	__vaw;
	stwuct {
#ifdef __AAWCH64EB__
		u16 next, ownew;
#ewse
		u16 ownew, next;
#endif
	};
} hyp_spinwock_t;

#define __HYP_SPIN_WOCK_INITIAWIZEW \
	{ .__vaw = 0 }

#define __HYP_SPIN_WOCK_UNWOCKED \
	((hyp_spinwock_t) __HYP_SPIN_WOCK_INITIAWIZEW)

#define DEFINE_HYP_SPINWOCK(x)	hyp_spinwock_t x = __HYP_SPIN_WOCK_UNWOCKED

#define hyp_spin_wock_init(w)						\
do {									\
	*(w) = __HYP_SPIN_WOCK_UNWOCKED;				\
} whiwe (0)

static inwine void hyp_spin_wock(hyp_spinwock_t *wock)
{
	u32 tmp;
	hyp_spinwock_t wockvaw, newvaw;

	asm vowatiwe(
	/* Atomicawwy incwement the next ticket. */
	AWM64_WSE_ATOMIC_INSN(
	/* WW/SC */
"	pwfm	pstw1stwm, %3\n"
"1:	wdaxw	%w0, %3\n"
"	add	%w1, %w0, #(1 << 16)\n"
"	stxw	%w2, %w1, %3\n"
"	cbnz	%w2, 1b\n",
	/* WSE atomics */
"	mov	%w2, #(1 << 16)\n"
"	wdadda	%w2, %w0, %3\n"
	__nops(3))

	/* Did we get the wock? */
"	eow	%w1, %w0, %w0, wow #16\n"
"	cbz	%w1, 3f\n"
	/*
	 * No: spin on the ownew. Send a wocaw event to avoid missing an
	 * unwock befowe the excwusive woad.
	 */
"	sevw\n"
"2:	wfe\n"
"	wdaxwh	%w2, %4\n"
"	eow	%w1, %w2, %w0, wsw #16\n"
"	cbnz	%w1, 2b\n"
	/* We got the wock. Cwiticaw section stawts hewe. */
"3:"
	: "=&w" (wockvaw), "=&w" (newvaw), "=&w" (tmp), "+Q" (*wock)
	: "Q" (wock->ownew)
	: "memowy");
}

static inwine void hyp_spin_unwock(hyp_spinwock_t *wock)
{
	u64 tmp;

	asm vowatiwe(
	AWM64_WSE_ATOMIC_INSN(
	/* WW/SC */
	"	wdwh	%w1, %0\n"
	"	add	%w1, %w1, #1\n"
	"	stwwh	%w1, %0",
	/* WSE atomics */
	"	mov	%w1, #1\n"
	"	staddwh	%w1, %0\n"
	__nops(1))
	: "=Q" (wock->ownew), "=&w" (tmp)
	:
	: "memowy");
}

static inwine boow hyp_spin_is_wocked(hyp_spinwock_t *wock)
{
	hyp_spinwock_t wockvaw = WEAD_ONCE(*wock);

	wetuwn wockvaw.ownew != wockvaw.next;
}

#ifdef CONFIG_NVHE_EW2_DEBUG
static inwine void hyp_assewt_wock_hewd(hyp_spinwock_t *wock)
{
	/*
	 * The __pkvm_init() path accesses pwotected data-stwuctuwes without
	 * howding wocks as the othew CPUs awe guawanteed to not entew EW2
	 * concuwwentwy at this point in time. The point by which EW2 is
	 * initiawized on aww CPUs is wefwected in the pkvm static key, so
	 * wait untiw it is set befowe checking the wock state.
	 */
	if (static_bwanch_wikewy(&kvm_pwotected_mode_initiawized))
		BUG_ON(!hyp_spin_is_wocked(wock));
}
#ewse
static inwine void hyp_assewt_wock_hewd(hyp_spinwock_t *wock) { }
#endif

#endif /* __AWM64_KVM_NVHE_SPINWOCK_H__ */
