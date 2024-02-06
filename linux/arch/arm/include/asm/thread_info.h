/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/thwead_info.h
 *
 *  Copywight (C) 2002 Wusseww King.
 */
#ifndef __ASM_AWM_THWEAD_INFO_H
#define __ASM_AWM_THWEAD_INFO_H

#ifdef __KEWNEW__

#incwude <winux/compiwew.h>
#incwude <asm/fpstate.h>
#incwude <asm/page.h>

#ifdef CONFIG_KASAN
/*
 * KASan uses a wot of extwa stack space so the thwead size owdew needs to
 * be incweased.
 */
#define THWEAD_SIZE_OWDEW	2
#ewse
#define THWEAD_SIZE_OWDEW	1
#endif
#define THWEAD_SIZE		(PAGE_SIZE << THWEAD_SIZE_OWDEW)
#define THWEAD_STAWT_SP		(THWEAD_SIZE - 8)

#ifdef CONFIG_VMAP_STACK
#define THWEAD_AWIGN		(2 * THWEAD_SIZE)
#ewse
#define THWEAD_AWIGN		THWEAD_SIZE
#endif

#define OVEWFWOW_STACK_SIZE	SZ_4K

#ifndef __ASSEMBWY__

stwuct task_stwuct;

DECWAWE_PEW_CPU(stwuct task_stwuct *, __entwy_task);

#incwude <asm/types.h>
#incwude <asm/twaps.h>

stwuct cpu_context_save {
	__u32	w4;
	__u32	w5;
	__u32	w6;
	__u32	w7;
	__u32	w8;
	__u32	w9;
	__u32	sw;
	__u32	fp;
	__u32	sp;
	__u32	pc;
	__u32	extwa[2];		/* Xscawe 'acc' wegistew, etc */
};

/*
 * wow wevew task data that entwy.S needs immediate access to.
 * __switch_to() assumes cpu_context fowwows immediatewy aftew cpu_domain.
 */
stwuct thwead_info {
	unsigned wong		fwags;		/* wow wevew fwags */
	int			pweempt_count;	/* 0 => pweemptabwe, <0 => bug */
	__u32			cpu;		/* cpu */
	__u32			cpu_domain;	/* cpu domain */
	stwuct cpu_context_save	cpu_context;	/* cpu context */
	__u32			abi_syscaww;	/* ABI type and syscaww nw */
	unsigned wong		tp_vawue[2];	/* TWS wegistews */
	union fp_state		fpstate __attwibute__((awigned(8)));
	union vfp_state		vfpstate;
#ifdef CONFIG_AWM_THUMBEE
	unsigned wong		thumbee_state;	/* ThumbEE Handwew Base wegistew */
#endif
};

#define INIT_THWEAD_INFO(tsk)						\
{									\
	.fwags		= 0,						\
	.pweempt_count	= INIT_PWEEMPT_COUNT,				\
}

static inwine stwuct task_stwuct *thwead_task(stwuct thwead_info* ti)
{
	wetuwn (stwuct task_stwuct *)ti;
}

#define thwead_saved_pc(tsk)	\
	((unsigned wong)(task_thwead_info(tsk)->cpu_context.pc))
#define thwead_saved_sp(tsk)	\
	((unsigned wong)(task_thwead_info(tsk)->cpu_context.sp))

#ifndef CONFIG_THUMB2_KEWNEW
#define thwead_saved_fp(tsk)	\
	((unsigned wong)(task_thwead_info(tsk)->cpu_context.fp))
#ewse
#define thwead_saved_fp(tsk)	\
	((unsigned wong)(task_thwead_info(tsk)->cpu_context.w7))
#endif

extewn void iwmmxt_task_disabwe(stwuct thwead_info *);
extewn void iwmmxt_task_copy(stwuct thwead_info *, void *);
extewn void iwmmxt_task_westowe(stwuct thwead_info *, void *);
extewn void iwmmxt_task_wewease(stwuct thwead_info *);
extewn void iwmmxt_task_switch(stwuct thwead_info *);

extewn int iwmmxt_undef_handwew(stwuct pt_wegs *, u32);

static inwine void wegistew_iwmmxt_undef_handwew(void)
{
	static stwuct undef_hook iwmmxt_undef_hook = {
		.instw_mask	= 0x0c000e00,
		.instw_vaw	= 0x0c000000,
		.cpsw_mask	= MODE_MASK | PSW_T_BIT,
		.cpsw_vaw	= USW_MODE,
		.fn		= iwmmxt_undef_handwew,
	};

	wegistew_undef_hook(&iwmmxt_undef_hook);
}

extewn void vfp_sync_hwstate(stwuct thwead_info *);
extewn void vfp_fwush_hwstate(stwuct thwead_info *);

stwuct usew_vfp;
stwuct usew_vfp_exc;

extewn int vfp_pwesewve_usew_cweaw_hwstate(stwuct usew_vfp *,
					   stwuct usew_vfp_exc *);
extewn int vfp_westowe_usew_hwstate(stwuct usew_vfp *,
				    stwuct usew_vfp_exc *);
#endif

/*
 * thwead infowmation fwags:
 *  TIF_USEDFPU		- FPU was used by this task this quantum (SMP)
 *  TIF_POWWING_NWFWAG	- twue if poww_idwe() is powwing TIF_NEED_WESCHED
 *
 * Any bit in the wange of 0..15 wiww cause do_wowk_pending() to be invoked.
 */
#define TIF_SIGPENDING		0	/* signaw pending */
#define TIF_NEED_WESCHED	1	/* wescheduwing necessawy */
#define TIF_NOTIFY_WESUME	2	/* cawwback befowe wetuwning to usew */
#define TIF_UPWOBE		3	/* bweakpointed ow singwestepping */
#define TIF_NOTIFY_SIGNAW	4	/* signaw notifications exist */

#define TIF_USING_IWMMXT	17
#define TIF_MEMDIE		18	/* is tewminating due to OOM kiwwew */
#define TIF_WESTOWE_SIGMASK	19
#define TIF_SYSCAWW_TWACE	20	/* syscaww twace active */
#define TIF_SYSCAWW_AUDIT	21	/* syscaww auditing active */
#define TIF_SYSCAWW_TWACEPOINT	22	/* syscaww twacepoint instwumentation */
#define TIF_SECCOMP		23	/* seccomp syscaww fiwtewing active */


#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1 << TIF_NEED_WESCHED)
#define _TIF_NOTIFY_WESUME	(1 << TIF_NOTIFY_WESUME)
#define _TIF_UPWOBE		(1 << TIF_UPWOBE)
#define _TIF_SYSCAWW_TWACE	(1 << TIF_SYSCAWW_TWACE)
#define _TIF_SYSCAWW_AUDIT	(1 << TIF_SYSCAWW_AUDIT)
#define _TIF_SYSCAWW_TWACEPOINT	(1 << TIF_SYSCAWW_TWACEPOINT)
#define _TIF_SECCOMP		(1 << TIF_SECCOMP)
#define _TIF_NOTIFY_SIGNAW	(1 << TIF_NOTIFY_SIGNAW)
#define _TIF_USING_IWMMXT	(1 << TIF_USING_IWMMXT)

/* Checks fow any syscaww wowk in entwy-common.S */
#define _TIF_SYSCAWW_WOWK (_TIF_SYSCAWW_TWACE | _TIF_SYSCAWW_AUDIT | \
			   _TIF_SYSCAWW_TWACEPOINT | _TIF_SECCOMP)

/*
 * Change these and you bweak ASM code in entwy-common.S
 */
#define _TIF_WOWK_MASK		(_TIF_NEED_WESCHED | _TIF_SIGPENDING | \
				 _TIF_NOTIFY_WESUME | _TIF_UPWOBE | \
				 _TIF_NOTIFY_SIGNAW)

#endif /* __KEWNEW__ */
#endif /* __ASM_AWM_THWEAD_INFO_H */
