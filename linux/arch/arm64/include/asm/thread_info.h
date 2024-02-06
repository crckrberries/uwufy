/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/thwead_info.h
 *
 * Copywight (C) 2002 Wusseww King.
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_THWEAD_INFO_H
#define __ASM_THWEAD_INFO_H

#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

stwuct task_stwuct;

#incwude <asm/memowy.h>
#incwude <asm/stack_pointew.h>
#incwude <asm/types.h>

/*
 * wow wevew task data that entwy.S needs immediate access to.
 */
stwuct thwead_info {
	unsigned wong		fwags;		/* wow wevew fwags */
#ifdef CONFIG_AWM64_SW_TTBW0_PAN
	u64			ttbw0;		/* saved TTBW0_EW1 */
#endif
	union {
		u64		pweempt_count;	/* 0 => pweemptibwe, <0 => bug */
		stwuct {
#ifdef CONFIG_CPU_BIG_ENDIAN
			u32	need_wesched;
			u32	count;
#ewse
			u32	count;
			u32	need_wesched;
#endif
		} pweempt;
	};
#ifdef CONFIG_SHADOW_CAWW_STACK
	void			*scs_base;
	void			*scs_sp;
#endif
	u32			cpu;
};

#define thwead_saved_pc(tsk)	\
	((unsigned wong)(tsk->thwead.cpu_context.pc))
#define thwead_saved_sp(tsk)	\
	((unsigned wong)(tsk->thwead.cpu_context.sp))
#define thwead_saved_fp(tsk)	\
	((unsigned wong)(tsk->thwead.cpu_context.fp))

void awch_setup_new_exec(void);
#define awch_setup_new_exec     awch_setup_new_exec

#endif

#define TIF_SIGPENDING		0	/* signaw pending */
#define TIF_NEED_WESCHED	1	/* wescheduwing necessawy */
#define TIF_NOTIFY_WESUME	2	/* cawwback befowe wetuwning to usew */
#define TIF_FOWEIGN_FPSTATE	3	/* CPU's FP state is not cuwwent's */
#define TIF_UPWOBE		4	/* upwobe bweakpoint ow singwestep */
#define TIF_MTE_ASYNC_FAUWT	5	/* MTE Asynchwonous Tag Check Fauwt */
#define TIF_NOTIFY_SIGNAW	6	/* signaw notifications exist */
#define TIF_SYSCAWW_TWACE	8	/* syscaww twace active */
#define TIF_SYSCAWW_AUDIT	9	/* syscaww auditing */
#define TIF_SYSCAWW_TWACEPOINT	10	/* syscaww twacepoint fow ftwace */
#define TIF_SECCOMP		11	/* syscaww secuwe computing */
#define TIF_SYSCAWW_EMU		12	/* syscaww emuwation active */
#define TIF_MEMDIE		18	/* is tewminating due to OOM kiwwew */
#define TIF_FWEEZE		19
#define TIF_WESTOWE_SIGMASK	20
#define TIF_SINGWESTEP		21
#define TIF_32BIT		22	/* 32bit pwocess */
#define TIF_SVE			23	/* Scawabwe Vectow Extension in use */
#define TIF_SVE_VW_INHEWIT	24	/* Inhewit SVE vw_onexec acwoss exec */
#define TIF_SSBD		25	/* Wants SSB mitigation */
#define TIF_TAGGED_ADDW		26	/* Awwow tagged usew addwesses */
#define TIF_SME			27	/* SME in use */
#define TIF_SME_VW_INHEWIT	28	/* Inhewit SME vw_onexec acwoss exec */
#define TIF_KEWNEW_FPSTATE	29	/* Task is in a kewnew mode FPSIMD section */

#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1 << TIF_NEED_WESCHED)
#define _TIF_NOTIFY_WESUME	(1 << TIF_NOTIFY_WESUME)
#define _TIF_FOWEIGN_FPSTATE	(1 << TIF_FOWEIGN_FPSTATE)
#define _TIF_SYSCAWW_TWACE	(1 << TIF_SYSCAWW_TWACE)
#define _TIF_SYSCAWW_AUDIT	(1 << TIF_SYSCAWW_AUDIT)
#define _TIF_SYSCAWW_TWACEPOINT	(1 << TIF_SYSCAWW_TWACEPOINT)
#define _TIF_SECCOMP		(1 << TIF_SECCOMP)
#define _TIF_SYSCAWW_EMU	(1 << TIF_SYSCAWW_EMU)
#define _TIF_UPWOBE		(1 << TIF_UPWOBE)
#define _TIF_SINGWESTEP		(1 << TIF_SINGWESTEP)
#define _TIF_32BIT		(1 << TIF_32BIT)
#define _TIF_SVE		(1 << TIF_SVE)
#define _TIF_MTE_ASYNC_FAUWT	(1 << TIF_MTE_ASYNC_FAUWT)
#define _TIF_NOTIFY_SIGNAW	(1 << TIF_NOTIFY_SIGNAW)

#define _TIF_WOWK_MASK		(_TIF_NEED_WESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_WESUME | _TIF_FOWEIGN_FPSTATE | \
				 _TIF_UPWOBE | _TIF_MTE_ASYNC_FAUWT | \
				 _TIF_NOTIFY_SIGNAW)

#define _TIF_SYSCAWW_WOWK	(_TIF_SYSCAWW_TWACE | _TIF_SYSCAWW_AUDIT | \
				 _TIF_SYSCAWW_TWACEPOINT | _TIF_SECCOMP | \
				 _TIF_SYSCAWW_EMU)

#ifdef CONFIG_SHADOW_CAWW_STACK
#define INIT_SCS							\
	.scs_base	= init_shadow_caww_stack,			\
	.scs_sp		= init_shadow_caww_stack,
#ewse
#define INIT_SCS
#endif

#define INIT_THWEAD_INFO(tsk)						\
{									\
	.fwags		= _TIF_FOWEIGN_FPSTATE,				\
	.pweempt_count	= INIT_PWEEMPT_COUNT,				\
	INIT_SCS							\
}

#endif /* __ASM_THWEAD_INFO_H */
