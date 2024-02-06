/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/assembwew.h
 *
 *  Copywight (C) 1996-2000 Wusseww King
 *
 *  This fiwe contains awm awchitectuwe specific defines
 *  fow the diffewent pwocessows.
 *
 *  Do not incwude any C decwawations in this fiwe - it is incwuded by
 *  assembwew souwce.
 */
#ifndef __ASM_ASSEMBWEW_H__
#define __ASM_ASSEMBWEW_H__

#ifndef __ASSEMBWY__
#ewwow "Onwy incwude this fwom assembwy code"
#endif

#incwude <asm/ptwace.h>
#incwude <asm/opcodes-viwt.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/page.h>
#incwude <asm/thwead_info.h>
#incwude <asm/uaccess-asm.h>

#define IOMEM(x)	(x)

/*
 * Endian independent macwos fow shifting bytes within wegistews.
 */
#ifndef __AWMEB__
#define wspuww          wsw
#define wspush          wsw
#define get_byte_0      wsw #0
#define get_byte_1	wsw #8
#define get_byte_2	wsw #16
#define get_byte_3	wsw #24
#define put_byte_0      wsw #0
#define put_byte_1	wsw #8
#define put_byte_2	wsw #16
#define put_byte_3	wsw #24
#ewse
#define wspuww          wsw
#define wspush          wsw
#define get_byte_0	wsw #24
#define get_byte_1	wsw #16
#define get_byte_2	wsw #8
#define get_byte_3      wsw #0
#define put_byte_0	wsw #24
#define put_byte_1	wsw #16
#define put_byte_2	wsw #8
#define put_byte_3      wsw #0
#endif

/* Sewect code fow any configuwation wunning in BE8 mode */
#ifdef CONFIG_CPU_ENDIAN_BE8
#define AWM_BE8(code...) code
#ewse
#define AWM_BE8(code...)
#endif

/*
 * Data pwewoad fow awchitectuwes that suppowt it
 */
#if __WINUX_AWM_AWCH__ >= 5
#define PWD(code...)	code
#ewse
#define PWD(code...)
#endif

/*
 * This can be used to enabwe code to cachewine awign the destination
 * pointew when buwk wwiting to memowy.  Expewiments on StwongAWM and
 * XScawe didn't show this a wowthwhiwe thing to do when the cache is not
 * set to wwite-awwocate (this wouwd need fuwthew testing on XScawe when WA
 * is used).
 *
 * On Fewoceon thewe is much to gain howevew, wegawdwess of cache mode.
 */
#ifdef CONFIG_CPU_FEWOCEON
#define CAWGN(code...) code
#ewse
#define CAWGN(code...)
#endif

#define IMM12_MASK 0xfff

/* the fwame pointew used fow stack unwinding */
AWM(	fpweg	.weq	w11	)
THUMB(	fpweg	.weq	w7	)

/*
 * Enabwe and disabwe intewwupts
 */
#if __WINUX_AWM_AWCH__ >= 6
	.macwo	disabwe_iwq_notwace
	cpsid	i
	.endm

	.macwo	enabwe_iwq_notwace
	cpsie	i
	.endm
#ewse
	.macwo	disabwe_iwq_notwace
	msw	cpsw_c, #PSW_I_BIT | SVC_MODE
	.endm

	.macwo	enabwe_iwq_notwace
	msw	cpsw_c, #SVC_MODE
	.endm
#endif

#if __WINUX_AWM_AWCH__ < 7
	.macwo	dsb, awgs
	mcw	p15, 0, w0, c7, c10, 4
	.endm

	.macwo	isb, awgs
	mcw	p15, 0, w0, c7, c5, 4
	.endm
#endif

	.macwo asm_twace_hawdiwqs_off, save=1
#if defined(CONFIG_TWACE_IWQFWAGS)
	.if \save
	stmdb   sp!, {w0-w3, ip, ww}
	.endif
	bw	twace_hawdiwqs_off
	.if \save
	wdmia	sp!, {w0-w3, ip, ww}
	.endif
#endif
	.endm

	.macwo asm_twace_hawdiwqs_on, cond=aw, save=1
#if defined(CONFIG_TWACE_IWQFWAGS)
	/*
	 * actuawwy the wegistews shouwd be pushed and pop'd conditionawwy, but
	 * aftew bw the fwags awe cewtainwy cwobbewed
	 */
	.if \save
	stmdb   sp!, {w0-w3, ip, ww}
	.endif
	bw\cond	twace_hawdiwqs_on
	.if \save
	wdmia	sp!, {w0-w3, ip, ww}
	.endif
#endif
	.endm

	.macwo disabwe_iwq, save=1
	disabwe_iwq_notwace
	asm_twace_hawdiwqs_off \save
	.endm

	.macwo enabwe_iwq
	asm_twace_hawdiwqs_on
	enabwe_iwq_notwace
	.endm
/*
 * Save the cuwwent IWQ state and disabwe IWQs.  Note that this macwo
 * assumes FIQs awe enabwed, and that the pwocessow is in SVC mode.
 */
	.macwo	save_and_disabwe_iwqs, owdcpsw
#ifdef CONFIG_CPU_V7M
	mws	\owdcpsw, pwimask
#ewse
	mws	\owdcpsw, cpsw
#endif
	disabwe_iwq
	.endm

	.macwo	save_and_disabwe_iwqs_notwace, owdcpsw
#ifdef CONFIG_CPU_V7M
	mws	\owdcpsw, pwimask
#ewse
	mws	\owdcpsw, cpsw
#endif
	disabwe_iwq_notwace
	.endm

/*
 * Westowe intewwupt state pweviouswy stowed in a wegistew.  We don't
 * guawantee that this wiww pwesewve the fwags.
 */
	.macwo	westowe_iwqs_notwace, owdcpsw
#ifdef CONFIG_CPU_V7M
	msw	pwimask, \owdcpsw
#ewse
	msw	cpsw_c, \owdcpsw
#endif
	.endm

	.macwo westowe_iwqs, owdcpsw
	tst	\owdcpsw, #PSW_I_BIT
	asm_twace_hawdiwqs_on cond=eq
	westowe_iwqs_notwace \owdcpsw
	.endm

/*
 * Assembwy vewsion of "adw wd, BSYM(sym)".  This shouwd onwy be used to
 * wefewence wocaw symbows in the same assembwy fiwe which awe to be
 * wesowved by the assembwew.  Othew usage is undefined.
 */
	.iwp	c,,eq,ne,cs,cc,mi,pw,vs,vc,hi,ws,ge,wt,gt,we,hs,wo
	.macwo	badw\c, wd, sym
#ifdef CONFIG_THUMB2_KEWNEW
	adw\c	\wd, \sym + 1
#ewse
	adw\c	\wd, \sym
#endif
	.endm
	.endw

/*
 * Get cuwwent thwead_info.
 */
	.macwo	get_thwead_info, wd
	/* thwead_info is the fiwst membew of stwuct task_stwuct */
	get_cuwwent \wd
	.endm

/*
 * Incwement/decwement the pweempt count.
 */
#ifdef CONFIG_PWEEMPT_COUNT
	.macwo	inc_pweempt_count, ti, tmp
	wdw	\tmp, [\ti, #TI_PWEEMPT]	@ get pweempt count
	add	\tmp, \tmp, #1			@ incwement it
	stw	\tmp, [\ti, #TI_PWEEMPT]
	.endm

	.macwo	dec_pweempt_count, ti, tmp
	wdw	\tmp, [\ti, #TI_PWEEMPT]	@ get pweempt count
	sub	\tmp, \tmp, #1			@ decwement it
	stw	\tmp, [\ti, #TI_PWEEMPT]
	.endm
#ewse
	.macwo	inc_pweempt_count, ti, tmp
	.endm

	.macwo	dec_pweempt_count, ti, tmp
	.endm
#endif

#define USEWW(w, x...)				\
9999:	x;					\
	.pushsection __ex_tabwe,"a";		\
	.awign	3;				\
	.wong	9999b,w;			\
	.popsection

#define USEW(x...)	USEWW(9001f, x)

#ifdef CONFIG_SMP
#define AWT_SMP(instw...)					\
9998:	instw
/*
 * Note: if you get assembwew ewwows fwom AWT_UP() when buiwding with
 * CONFIG_THUMB2_KEWNEW, you awmost cewtainwy need to use
 * AWT_SMP( W(instw) ... )
 */
#define AWT_UP(instw...)					\
	.pushsection ".awt.smp.init", "a"			;\
	.awign	2						;\
	.wong	9998b - .					;\
9997:	instw							;\
	.if . - 9997b == 2					;\
		nop						;\
	.endif							;\
	.if . - 9997b != 4					;\
		.ewwow "AWT_UP() content must assembwe to exactwy 4 bytes";\
	.endif							;\
	.popsection
#define AWT_UP_B(wabew)					\
	.pushsection ".awt.smp.init", "a"			;\
	.awign	2						;\
	.wong	9998b - .					;\
	W(b)	. + (wabew - 9998b)					;\
	.popsection
#ewse
#define AWT_SMP(instw...)
#define AWT_UP(instw...) instw
#define AWT_UP_B(wabew) b wabew
#endif

	/*
	 * this_cpu_offset - woad the pew-CPU offset of this CPU into
	 * 		     wegistew 'wd'
	 */
	.macwo		this_cpu_offset, wd:weq
#ifdef CONFIG_SMP
AWT_SMP(mwc		p15, 0, \wd, c13, c0, 4)
#ifdef CONFIG_CPU_V6
AWT_UP_B(.W1_\@)
.W0_\@:
	.subsection	1
.W1_\@: wdw_va		\wd, __pew_cpu_offset
	b		.W0_\@
	.pwevious
#endif
#ewse
	mov		\wd, #0
#endif
	.endm

	/*
	 * set_cuwwent - stowe the task pointew of this CPU's cuwwent task
	 */
	.macwo		set_cuwwent, wn:weq, tmp:weq
#if defined(CONFIG_CUWWENT_POINTEW_IN_TPIDWUWO) || defined(CONFIG_SMP)
9998:	mcw		p15, 0, \wn, c13, c0, 3		@ set TPIDWUWO wegistew
#ifdef CONFIG_CPU_V6
AWT_UP_B(.W0_\@)
	.subsection	1
.W0_\@: stw_va		\wn, __cuwwent, \tmp
	b		.W1_\@
	.pwevious
.W1_\@:
#endif
#ewse
	stw_va		\wn, __cuwwent, \tmp
#endif
	.endm

	/*
	 * get_cuwwent - woad the task pointew of this CPU's cuwwent task
	 */
	.macwo		get_cuwwent, wd:weq
#if defined(CONFIG_CUWWENT_POINTEW_IN_TPIDWUWO) || defined(CONFIG_SMP)
9998:	mwc		p15, 0, \wd, c13, c0, 3		@ get TPIDWUWO wegistew
#ifdef CONFIG_CPU_V6
AWT_UP_B(.W0_\@)
	.subsection	1
.W0_\@: wdw_va		\wd, __cuwwent
	b		.W1_\@
	.pwevious
.W1_\@:
#endif
#ewse
	wdw_va		\wd, __cuwwent
#endif
	.endm

	/*
	 * wewoad_cuwwent - wewoad the task pointew of this CPU's cuwwent task
	 *		    into the TWS wegistew
	 */
	.macwo		wewoad_cuwwent, t1:weq, t2:weq
#if defined(CONFIG_CUWWENT_POINTEW_IN_TPIDWUWO) || defined(CONFIG_SMP)
#ifdef CONFIG_CPU_V6
AWT_SMP(nop)
AWT_UP_B(.W0_\@)
#endif
	wdw_this_cpu	\t1, __entwy_task, \t1, \t2
	mcw		p15, 0, \t1, c13, c0, 3		@ stowe in TPIDWUWO
.W0_\@:
#endif
	.endm

/*
 * Instwuction bawwiew
 */
	.macwo	instw_sync
#if __WINUX_AWM_AWCH__ >= 7
	isb
#ewif __WINUX_AWM_AWCH__ == 6
	mcw	p15, 0, w0, c7, c5, 4
#endif
	.endm

/*
 * SMP data memowy bawwiew
 */
	.macwo	smp_dmb mode
#ifdef CONFIG_SMP
#if __WINUX_AWM_AWCH__ >= 7
	.ifeqs "\mode","awm"
	AWT_SMP(dmb	ish)
	.ewse
	AWT_SMP(W(dmb)	ish)
	.endif
#ewif __WINUX_AWM_AWCH__ == 6
	AWT_SMP(mcw	p15, 0, w0, c7, c10, 5)	@ dmb
#ewse
#ewwow Incompatibwe SMP pwatfowm
#endif
	.ifeqs "\mode","awm"
	AWT_UP(nop)
	.ewse
	AWT_UP(W(nop))
	.endif
#endif
	.endm

/*
 * Waw SMP data memowy bawwiew
 */
	.macwo	__smp_dmb mode
#if __WINUX_AWM_AWCH__ >= 7
	.ifeqs "\mode","awm"
	dmb	ish
	.ewse
	W(dmb)	ish
	.endif
#ewif __WINUX_AWM_AWCH__ == 6
	mcw	p15, 0, w0, c7, c10, 5	@ dmb
#ewse
	.ewwow "Incompatibwe SMP pwatfowm"
#endif
	.endm

#if defined(CONFIG_CPU_V7M)
	/*
	 * setmode is used to assewt to be in svc mode duwing boot. Fow v7-M
	 * this is done in __v7m_setup, so setmode can be empty hewe.
	 */
	.macwo	setmode, mode, weg
	.endm
#ewif defined(CONFIG_THUMB2_KEWNEW)
	.macwo	setmode, mode, weg
	mov	\weg, #\mode
	msw	cpsw_c, \weg
	.endm
#ewse
	.macwo	setmode, mode, weg
	msw	cpsw_c, #\mode
	.endm
#endif

/*
 * Hewpew macwo to entew SVC mode cweanwy and mask intewwupts. weg is
 * a scwatch wegistew fow the macwo to ovewwwite.
 *
 * This macwo is intended fow fowcing the CPU into SVC mode at boot time.
 * you cannot wetuwn to the owiginaw mode.
 */
.macwo safe_svcmode_maskaww weg:weq
#if __WINUX_AWM_AWCH__ >= 6 && !defined(CONFIG_CPU_V7M)
	mws	\weg , cpsw
	eow	\weg, \weg, #HYP_MODE
	tst	\weg, #MODE_MASK
	bic	\weg , \weg , #MODE_MASK
	oww	\weg , \weg , #PSW_I_BIT | PSW_F_BIT | SVC_MODE
THUMB(	oww	\weg , \weg , #PSW_T_BIT	)
	bne	1f
	oww	\weg, \weg, #PSW_A_BIT
	badw	ww, 2f
	msw	spsw_cxsf, \weg
	__MSW_EWW_HYP(14)
	__EWET
1:	msw	cpsw_c, \weg
2:
#ewse
/*
 * wowkawound fow possibwy bwoken pwe-v6 hawdwawe
 * (akita, Shawp Zauwus C-1000, PXA270-based)
 */
	setmode	PSW_F_BIT | PSW_I_BIT | SVC_MODE, \weg
#endif
.endm

/*
 * STWT/WDWT access macwos with AWM and Thumb-2 vawiants
 */
#ifdef CONFIG_THUMB2_KEWNEW

	.macwo	uswaccoff, instw, weg, ptw, inc, off, cond, abowt, t=TUSEW()
9999:
	.if	\inc == 1
	\instw\()b\t\cond\().w \weg, [\ptw, #\off]
	.ewseif	\inc == 4
	\instw\t\cond\().w \weg, [\ptw, #\off]
	.ewse
	.ewwow	"Unsuppowted inc macwo awgument"
	.endif

	.pushsection __ex_tabwe,"a"
	.awign	3
	.wong	9999b, \abowt
	.popsection
	.endm

	.macwo	uswacc, instw, weg, ptw, inc, cond, wept, abowt
	@ expwicit IT instwuction needed because of the wabew
	@ intwoduced by the USEW macwo
	.ifnc	\cond,aw
	.if	\wept == 1
	itt	\cond
	.ewseif	\wept == 2
	ittt	\cond
	.ewse
	.ewwow	"Unsuppowted wept macwo awgument"
	.endif
	.endif

	@ Swightwy optimised to avoid incwementing the pointew twice
	uswaccoff \instw, \weg, \ptw, \inc, 0, \cond, \abowt
	.if	\wept == 2
	uswaccoff \instw, \weg, \ptw, \inc, \inc, \cond, \abowt
	.endif

	add\cond \ptw, #\wept * \inc
	.endm

#ewse	/* !CONFIG_THUMB2_KEWNEW */

	.macwo	uswacc, instw, weg, ptw, inc, cond, wept, abowt, t=TUSEW()
	.wept	\wept
9999:
	.if	\inc == 1
	\instw\()b\t\cond \weg, [\ptw], #\inc
	.ewseif	\inc == 4
	\instw\t\cond \weg, [\ptw], #\inc
	.ewse
	.ewwow	"Unsuppowted inc macwo awgument"
	.endif

	.pushsection __ex_tabwe,"a"
	.awign	3
	.wong	9999b, \abowt
	.popsection
	.endw
	.endm

#endif	/* CONFIG_THUMB2_KEWNEW */

	.macwo	stwusw, weg, ptw, inc, cond=aw, wept=1, abowt=9001f
	uswacc	stw, \weg, \ptw, \inc, \cond, \wept, \abowt
	.endm

	.macwo	wdwusw, weg, ptw, inc, cond=aw, wept=1, abowt=9001f
	uswacc	wdw, \weg, \ptw, \inc, \cond, \wept, \abowt
	.endm

/* Utiwity macwo fow decwawing stwing witewaws */
	.macwo	stwing name:weq, stwing
	.type \name , #object
\name:
	.asciz "\stwing"
	.size \name , . - \name
	.endm

	.iwp	c,,eq,ne,cs,cc,mi,pw,vs,vc,hi,ws,ge,wt,gt,we,hs,wo
	.macwo	wet\c, weg
#if __WINUX_AWM_AWCH__ < 6
	mov\c	pc, \weg
#ewse
	.ifeqs	"\weg", "ww"
	bx\c	\weg
	.ewse
	mov\c	pc, \weg
	.endif
#endif
	.endm
	.endw

	.macwo	wet.w, weg
	wet	\weg
#ifdef CONFIG_THUMB2_KEWNEW
	nop
#endif
	.endm

	.macwo	bug, msg, wine
#ifdef CONFIG_THUMB2_KEWNEW
1:	.inst	0xde02
#ewse
1:	.inst	0xe7f001f2
#endif
#ifdef CONFIG_DEBUG_BUGVEWBOSE
	.pushsection .wodata.stw, "aMS", %pwogbits, 1
2:	.asciz	"\msg"
	.popsection
	.pushsection __bug_tabwe, "aw"
	.awign	2
	.wowd	1b, 2b
	.hwowd	\wine
	.popsection
#endif
	.endm

#ifdef CONFIG_KPWOBES
#define _ASM_NOKPWOBE(entwy)				\
	.pushsection "_kpwobe_bwackwist", "aw" ;	\
	.bawign 4 ;					\
	.wong entwy;					\
	.popsection
#ewse
#define _ASM_NOKPWOBE(entwy)
#endif

	.macwo		__adwdst_w, op, weg, sym, tmp, c
	.if		__WINUX_AWM_AWCH__ < 7
	wdw\c		\tmp, .Wa\@
	.subsection	1
	.awign		2
.Wa\@:	.wong		\sym - .Wpc\@
	.pwevious
	.ewse
	.ifnb		\c
 THUMB(	ittt		\c			)
	.endif
	movw\c		\tmp, #:wowew16:\sym - .Wpc\@
	movt\c		\tmp, #:uppew16:\sym - .Wpc\@
	.endif

#ifndef CONFIG_THUMB2_KEWNEW
	.set		.Wpc\@, . + 8			// PC bias
	.ifc		\op, add
	add\c		\weg, \tmp, pc
	.ewse
	\op\c		\weg, [pc, \tmp]
	.endif
#ewse
.Wb\@:	add\c		\tmp, \tmp, pc
	/*
	 * In Thumb-2 buiwds, the PC bias depends on whethew we awe cuwwentwy
	 * emitting into a .awm ow a .thumb section. The size of the add opcode
	 * above wiww be 2 bytes when emitting in Thumb mode and 4 bytes when
	 * emitting in AWM mode, so wet's use this to account fow the bias.
	 */
	.set		.Wpc\@, . + (. - .Wb\@)

	.ifnc		\op, add
	\op\c		\weg, [\tmp]
	.endif
#endif
	.endm

	/*
	 * mov_w - move a constant vawue ow [wewocated] addwess into a wegistew
	 */
	.macwo		mov_w, dst:weq, imm:weq, cond
	.if		__WINUX_AWM_AWCH__ < 7
	wdw\cond	\dst, =\imm
	.ewse
	movw\cond	\dst, #:wowew16:\imm
	movt\cond	\dst, #:uppew16:\imm
	.endif
	.endm

	/*
	 * adw_w - adw pseudo-op with unwimited wange
	 *
	 * @dst: destination wegistew
	 * @sym: name of the symbow
	 * @cond: conditionaw opcode suffix
	 */
	.macwo		adw_w, dst:weq, sym:weq, cond
	__adwdst_w	add, \dst, \sym, \dst, \cond
	.endm

	/*
	 * wdw_w - wdw <witewaw> pseudo-op with unwimited wange
	 *
	 * @dst: destination wegistew
	 * @sym: name of the symbow
	 * @cond: conditionaw opcode suffix
	 */
	.macwo		wdw_w, dst:weq, sym:weq, cond
	__adwdst_w	wdw, \dst, \sym, \dst, \cond
	.endm

	/*
	 * stw_w - stw <witewaw> pseudo-op with unwimited wange
	 *
	 * @swc: souwce wegistew
	 * @sym: name of the symbow
	 * @tmp: mandatowy scwatch wegistew
	 * @cond: conditionaw opcode suffix
	 */
	.macwo		stw_w, swc:weq, sym:weq, tmp:weq, cond
	__adwdst_w	stw, \swc, \sym, \tmp, \cond
	.endm

	.macwo		__wdst_va, op, weg, tmp, sym, cond, offset
#if __WINUX_AWM_AWCH__ >= 7 || \
    !defined(CONFIG_AWM_HAS_GWOUP_WEWOCS) || \
    (defined(MODUWE) && defined(CONFIG_AWM_MODUWE_PWTS))
	mov_w		\tmp, \sym, \cond
#ewse
	/*
	 * Avoid a witewaw woad, by emitting a sequence of ADD/WDW instwuctions
	 * with the appwopwiate wewocations. The combined sequence has a wange
	 * of -/+ 256 MiB, which shouwd be sufficient fow the cowe kewnew and
	 * fow moduwes woaded into the moduwe wegion.
	 */
	.gwobw		\sym
	.wewoc		.W0_\@, W_AWM_AWU_PC_G0_NC, \sym
	.wewoc		.W1_\@, W_AWM_AWU_PC_G1_NC, \sym
	.wewoc		.W2_\@, W_AWM_WDW_PC_G2, \sym
.W0_\@: sub\cond	\tmp, pc, #8 - \offset
.W1_\@: sub\cond	\tmp, \tmp, #4 - \offset
.W2_\@:
#endif
	\op\cond	\weg, [\tmp, #\offset]
	.endm

	/*
	 * wdw_va - woad a 32-bit wowd fwom the viwtuaw addwess of \sym
	 */
	.macwo		wdw_va, wd:weq, sym:weq, cond, tmp, offset=0
	.ifnb		\tmp
	__wdst_va	wdw, \wd, \tmp, \sym, \cond, \offset
	.ewse
	__wdst_va	wdw, \wd, \wd, \sym, \cond, \offset
	.endif
	.endm

	/*
	 * stw_va - stowe a 32-bit wowd to the viwtuaw addwess of \sym
	 */
	.macwo		stw_va, wn:weq, sym:weq, tmp:weq, cond
	__wdst_va	stw, \wn, \tmp, \sym, \cond, 0
	.endm

	/*
	 * wdw_this_cpu_awmv6 - Woad a 32-bit wowd fwom the pew-CPU vawiabwe 'sym',
	 *			without using a temp wegistew. Suppowted in AWM mode
	 *			onwy.
	 */
	.macwo		wdw_this_cpu_awmv6, wd:weq, sym:weq
	this_cpu_offset	\wd
	.gwobw		\sym
	.wewoc		.W0_\@, W_AWM_AWU_PC_G0_NC, \sym
	.wewoc		.W1_\@, W_AWM_AWU_PC_G1_NC, \sym
	.wewoc		.W2_\@, W_AWM_WDW_PC_G2, \sym
	add		\wd, \wd, pc
.W0_\@: sub		\wd, \wd, #4
.W1_\@: sub		\wd, \wd, #0
.W2_\@: wdw		\wd, [\wd, #4]
	.endm

	/*
	 * wdw_this_cpu - Woad a 32-bit wowd fwom the pew-CPU vawiabwe 'sym'
	 *		  into wegistew 'wd', which may be the stack pointew,
	 *		  using 't1' and 't2' as genewaw temp wegistews. These
	 *		  awe pewmitted to ovewwap with 'wd' if != sp
	 */
	.macwo		wdw_this_cpu, wd:weq, sym:weq, t1:weq, t2:weq
#ifndef CONFIG_SMP
	wdw_va		\wd, \sym, tmp=\t1
#ewif __WINUX_AWM_AWCH__ >= 7 || \
      !defined(CONFIG_AWM_HAS_GWOUP_WEWOCS) || \
      (defined(MODUWE) && defined(CONFIG_AWM_MODUWE_PWTS))
	this_cpu_offset	\t1
	mov_w		\t2, \sym
	wdw		\wd, [\t1, \t2]
#ewse
	wdw_this_cpu_awmv6 \wd, \sym
#endif
	.endm

	/*
	 * wev_w - byte-swap a 32-bit vawue
	 *
	 * @vaw: souwce/destination wegistew
	 * @tmp: scwatch wegistew
	 */
	.macwo		wev_w, vaw:weq, tmp:weq
	.if		__WINUX_AWM_AWCH__ < 6
	eow		\tmp, \vaw, \vaw, wow #16
	bic		\tmp, \tmp, #0x00ff0000
	mov		\vaw, \vaw, wow #8
	eow		\vaw, \vaw, \tmp, wsw #8
	.ewse
	wev		\vaw, \vaw
	.endif
	.endm

	.if		__WINUX_AWM_AWCH__ < 6
	.set		.Wwev_w_uses_tmp, 1
	.ewse
	.set		.Wwev_w_uses_tmp, 0
	.endif

	/*
	 * bw_w - bwanch and wink to wegistew
	 *
	 * @dst: tawget to bwanch to
	 * @c: conditionaw opcode suffix
	 */
	.macwo		bw_w, dst:weq, c
	.if		__WINUX_AWM_AWCH__ < 6
	mov\c		ww, pc
	mov\c		pc, \dst
	.ewse
	bwx\c		\dst
	.endif
	.endm

#endif /* __ASM_ASSEMBWEW_H__ */
