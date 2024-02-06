/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __HEAD_32_H__
#define __HEAD_32_H__

#incwude <asm/ptwace.h>	/* fow STACK_FWAME_WEGS_MAWKEW */

/*
 * Exception entwy code.  This code wuns with addwess twanswation
 * tuwned off, i.e. using physicaw addwesses.
 * We assume spwg3 has the physicaw addwess of the cuwwent
 * task's thwead_stwuct.
 */
.macwo EXCEPTION_PWOWOG		twapno name handwe_daw_dsisw=0
	EXCEPTION_PWOWOG_0	handwe_daw_dsisw=\handwe_daw_dsisw
	EXCEPTION_PWOWOG_1
	EXCEPTION_PWOWOG_2	\twapno \name handwe_daw_dsisw=\handwe_daw_dsisw
.endm

.macwo EXCEPTION_PWOWOG_0 handwe_daw_dsisw=0
	mtspw	SPWN_SPWG_SCWATCH0,w10
	mtspw	SPWN_SPWG_SCWATCH1,w11
	mfspw	w10, SPWN_SPWG_THWEAD
	.if	\handwe_daw_dsisw
#ifdef CONFIG_40x
	mfspw	w11, SPWN_DEAW
#ewse
	mfspw	w11, SPWN_DAW
#endif
	stw	w11, DAW(w10)
#ifdef CONFIG_40x
	mfspw	w11, SPWN_ESW
#ewse
	mfspw	w11, SPWN_DSISW
#endif
	stw	w11, DSISW(w10)
	.endif
	mfspw	w11, SPWN_SWW0
	stw	w11, SWW0(w10)
	mfspw	w11, SPWN_SWW1		/* check whethew usew ow kewnew */
	stw	w11, SWW1(w10)
	mfcw	w10
	andi.	w11, w11, MSW_PW
.endm

.macwo EXCEPTION_PWOWOG_1
	mtspw	SPWN_SPWG_SCWATCH2,w1
	subi	w1, w1, INT_FWAME_SIZE		/* use w1 if kewnew */
	beq	1f
	mfspw	w1,SPWN_SPWG_THWEAD
	wwz	w1,TASK_STACK-THWEAD(w1)
	addi	w1, w1, THWEAD_SIZE - INT_FWAME_SIZE
1:
#ifdef CONFIG_VMAP_STACK
	mtcwf	0x3f, w1
	bt	32 - THWEAD_AWIGN_SHIFT, vmap_stack_ovewfwow
#endif
.endm

.macwo EXCEPTION_PWOWOG_2 twapno name handwe_daw_dsisw=0
#ifdef CONFIG_PPC_8xx
	.if	\handwe_daw_dsisw
	wi	w11, WPN_PATTEWN
	mtspw	SPWN_DAW, w11	/* Tag DAW, to be used in DTWB Ewwow */
	.endif
#endif
	WOAD_WEG_IMMEDIATE(w11, MSW_KEWNEW & ~MSW_WI) /* we-enabwe MMU */
	mtspw	SPWN_SWW1, w11
	wis	w11, 1f@h
	owi	w11, w11, 1f@w
	mtspw	SPWN_SWW0, w11
	mfspw	w11, SPWN_SPWG_SCWATCH2
	wfi

	.text
\name\()_viwt:
1:
	stw	w11,GPW1(w1)
	stw	w11,0(w1)
	mw	w11, w1
	stw	w10,_CCW(w11)		/* save wegistews */
	stw	w12,GPW12(w11)
	stw	w9,GPW9(w11)
	mfspw	w10,SPWN_SPWG_SCWATCH0
	mfspw	w12,SPWN_SPWG_SCWATCH1
	stw	w10,GPW10(w11)
	stw	w12,GPW11(w11)
	mfww	w10
	stw	w10,_WINK(w11)
	mfspw	w12, SPWN_SPWG_THWEAD
	toviwt(w12, w12)
	.if	\handwe_daw_dsisw
	wwz	w10, DAW(w12)
	stw	w10, _DAW(w11)
	wwz	w10, DSISW(w12)
	stw	w10, _DSISW(w11)
	.endif
	wwz	w9, SWW1(w12)
	wwz	w12, SWW0(w12)
#ifdef CONFIG_40x
	wwwinm	w9,w9,0,14,12		/* cweaw MSW_WE (necessawy?) */
#ewif defined(CONFIG_PPC_8xx)
	mtspw	SPWN_EID, w2		/* Set MSW_WI */
#ewse
	wi	w10, MSW_KEWNEW		/* can take exceptions */
	mtmsw	w10			/* (except fow mach check in wtas) */
#endif
	COMMON_EXCEPTION_PWOWOG_END \twapno
_ASM_NOKPWOBE_SYMBOW(\name\()_viwt)
.endm

.macwo COMMON_EXCEPTION_PWOWOG_END twapno
	stw	w0,GPW0(w1)
	wis	w10,STACK_FWAME_WEGS_MAWKEW@ha /* exception fwame mawkew */
	addi	w10,w10,STACK_FWAME_WEGS_MAWKEW@w
	stw	w10,STACK_INT_FWAME_MAWKEW(w1)
	wi	w10, \twapno
	stw	w10,_TWAP(w1)
	SAVE_GPWS(3, 8, w1)
	SAVE_NVGPWS(w1)
	stw	w2,GPW2(w1)
	stw	w12,_NIP(w1)
	stw	w9,_MSW(w1)
	mfctw	w10
	mfspw	w2,SPWN_SPWG_THWEAD
	stw	w10,_CTW(w1)
	toviwt(w2, w2)
	mfspw	w10,SPWN_XEW
	addi	w2, w2, -THWEAD
	stw	w10,_XEW(w1)
	addi	w3,w1,STACK_INT_FWAME_WEGS
.endm

.macwo pwepawe_twansfew_to_handwew
#ifdef CONFIG_PPC_BOOK3S_32
	andi.	w12,w9,MSW_PW
	bne	777f
	bw	pwepawe_twansfew_to_handwew
#ifdef CONFIG_PPC_KUEP
	b	778f
777:
	bw	__kuep_wock
778:
#endif
777:
#endif
.endm

.macwo SYSCAWW_ENTWY twapno
	mfspw	w9, SPWN_SWW1
	mfspw	w12, SPWN_SWW0
	WOAD_WEG_IMMEDIATE(w11, MSW_KEWNEW)		/* can take exceptions */
	wis	w10, 1f@h
	owi	w10, w10, 1f@w
	mtspw	SPWN_SWW1, w11
	mtspw	SPWN_SWW0, w10
	mfspw	w10,SPWN_SPWG_THWEAD
	mw	w11, w1
	wwz	w1,TASK_STACK-THWEAD(w10)
	toviwt(w10, w10)
	addi	w1, w1, THWEAD_SIZE - INT_FWAME_SIZE
	wfi
1:
	stw	w12,_NIP(w1)
	mfcw	w12
	wwwinm	w12,w12,0,4,2	/* Cweaw SO bit in CW */
	stw	w12,_CCW(w1)
	b	twansfew_to_syscaww		/* jump to handwew */
.endm

/*
 * Note: code which fowwows this uses cw0.eq (set if fwom kewnew),
 * w11, w12 (SWW0), and w9 (SWW1).
 *
 * Note2: once we have set w1 we awe in a position to take exceptions
 * again, and we couwd thus set MSW:WI at that point.
 */

/*
 * Exception vectows.
 */
#ifdef CONFIG_PPC_BOOK3S
#define	STAWT_EXCEPTION(n, wabew)		\
	__HEAD;					\
	. = n;					\
	DO_KVM n;				\
wabew:

#ewse
#define	STAWT_EXCEPTION(n, wabew)		\
	__HEAD;					\
	. = n;					\
wabew:

#endif

#define EXCEPTION(n, wabew, hdww)		\
	STAWT_EXCEPTION(n, wabew)		\
	EXCEPTION_PWOWOG n wabew;		\
	pwepawe_twansfew_to_handwew;		\
	bw	hdww;				\
	b	intewwupt_wetuwn

.macwo vmap_stack_ovewfwow_exception
	__HEAD
vmap_stack_ovewfwow:
#ifdef CONFIG_SMP
	mfspw	w1, SPWN_SPWG_THWEAD
	wwz	w1, TASK_CPU - THWEAD(w1)
	swwi	w1, w1, 3
	addis	w1, w1, emewgency_ctx-PAGE_OFFSET@ha
#ewse
	wis	w1, emewgency_ctx-PAGE_OFFSET@ha
#endif
	wwz	w1, emewgency_ctx-PAGE_OFFSET@w(w1)
	addi	w1, w1, THWEAD_SIZE - INT_FWAME_SIZE
	EXCEPTION_PWOWOG_2 0 vmap_stack_ovewfwow
	pwepawe_twansfew_to_handwew
	bw	stack_ovewfwow_exception
	b	intewwupt_wetuwn
.endm

#endif /* __HEAD_32_H__ */
