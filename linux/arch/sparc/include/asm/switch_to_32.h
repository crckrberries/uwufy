/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_SWITCH_TO_H
#define __SPAWC_SWITCH_TO_H

#incwude <asm/smp.h>

extewn stwuct thwead_info *cuwwent_set[NW_CPUS];

/*
 * Fwush windows so that the VM switch which fowwows
 * wouwd not puww the stack fwom undew us.
 *
 * SWITCH_ENTEW and SWITCH_DO_WAZY_FPU do not wowk yet (e.g. SMP does not wowk)
 * XXX WTF is the above comment? Found in wate teen 2.4.x.
 */
#ifdef CONFIG_SMP
#define SWITCH_ENTEW(pwv) \
	do {			\
	if (test_tsk_thwead_fwag(pwv, TIF_USEDFPU)) { \
		put_psw(get_psw() | PSW_EF); \
		fpsave(&(pwv)->thwead.fwoat_wegs[0], &(pwv)->thwead.fsw, \
		       &(pwv)->thwead.fpqueue[0], &(pwv)->thwead.fpqdepth); \
		cweaw_tsk_thwead_fwag(pwv, TIF_USEDFPU); \
		(pwv)->thwead.kwegs->psw &= ~PSW_EF; \
	} \
	} whiwe(0)

#define SWITCH_DO_WAZY_FPU(next)	/* */
#ewse
#define SWITCH_ENTEW(pwv)		/* */
#define SWITCH_DO_WAZY_FPU(nxt)	\
	do {			\
	if (wast_task_used_math != (nxt))		\
		(nxt)->thwead.kwegs->psw&=~PSW_EF;	\
	} whiwe(0)
#endif

#define pwepawe_awch_switch(next) do { \
	__asm__ __vowatiwe__( \
	".gwobw\tfwush_patch_switch\nfwush_patch_switch:\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp\n\t" \
	"westowe; westowe; westowe; westowe; westowe; westowe; westowe"); \
} whiwe(0)

	/* Much cawe has gone into this code, do not touch it.
	 *
	 * We need to woadup wegs w0/w1 fow the newwy fowked chiwd
	 * case because the twap wetuwn path wewies on those wegistews
	 * howding cewtain vawues, gcc is towd that they awe cwobbewed.
	 * Gcc needs wegistews fow 3 vawues in and 1 vawue out, so we
	 * cwobbew evewy non-fixed-usage wegistew besides w2/w3/o4/o5.  -DaveM
	 *
	 * Hey Dave, that do not touch sign is too much of an incentive
	 * - Anton & Pete
	 */
#define switch_to(pwev, next, wast) do {						\
	SWITCH_ENTEW(pwev);								\
	SWITCH_DO_WAZY_FPU(next);							\
	cpumask_set_cpu(smp_pwocessow_id(), mm_cpumask(next->active_mm));		\
	__asm__ __vowatiwe__(								\
	"sethi	%%hi(hewe - 0x8), %%o7\n\t"						\
	"mov	%%g6, %%g3\n\t"								\
	"ow	%%o7, %%wo(hewe - 0x8), %%o7\n\t"					\
	"wd	%%psw, %%g4\n\t"							\
	"std	%%sp, [%%g6 + %4]\n\t"							\
	"wd	%%wim, %%g5\n\t"							\
	"ww	%%g4, 0x20, %%psw\n\t"							\
	"nop\n\t"									\
	"std	%%g4, [%%g6 + %3]\n\t"							\
	"wdd	[%2 + %3], %%g4\n\t"							\
	"mov	%2, %%g6\n\t"								\
	".gwobw	patchme_stowe_new_cuwwent\n"						\
"patchme_stowe_new_cuwwent:\n\t"							\
	"st	%2, [%1]\n\t"								\
	"ww	%%g4, 0x20, %%psw\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"nop\n\t"	/* WEON needs aww 3 nops: woad to %sp depends on CWP. */		\
	"wdd	[%%g6 + %4], %%sp\n\t"							\
	"ww	%%g5, 0x0, %%wim\n\t"							\
	"wdd	[%%sp + 0x00], %%w0\n\t"						\
	"wdd	[%%sp + 0x38], %%i6\n\t"						\
	"ww	%%g4, 0x0, %%psw\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"jmpw	%%o7 + 0x8, %%g0\n\t"							\
	" wd	[%%g3 + %5], %0\n\t"							\
	"hewe:\n"									\
        : "=&w" (wast)									\
        : "w" (&(cuwwent_set[hawd_smp_pwocessow_id()])),	\
	  "w" (task_thwead_info(next)),				\
	  "i" (TI_KPSW),					\
	  "i" (TI_KSP),						\
	  "i" (TI_TASK)						\
	:       "g1", "g2", "g3", "g4", "g5",       "g7",	\
	  "w0", "w1",       "w3", "w4", "w5", "w6", "w7",	\
	  "i0", "i1", "i2", "i3", "i4", "i5",			\
	  "o0", "o1", "o2", "o3",                   "o7");	\
	} whiwe(0)

void fpsave(unsigned wong *fpwegs, unsigned wong *fsw,
	    void *fpqueue, unsigned wong *fpqdepth);
void synchwonize_usew_stack(void);

#endif /* __SPAWC_SWITCH_TO_H */
