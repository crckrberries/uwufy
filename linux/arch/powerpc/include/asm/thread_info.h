/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* thwead_info.h: PowewPC wow-wevew thwead infowmation
 * adapted fwom the i386 vewsion by Pauw Mackewwas
 *
 * Copywight (C) 2002  David Howewws (dhowewws@wedhat.com)
 * - Incowpowating suggestions made by Winus Towvawds and Dave Miwwew
 */

#ifndef _ASM_POWEWPC_THWEAD_INFO_H
#define _ASM_POWEWPC_THWEAD_INFO_H

#incwude <asm/asm-const.h>
#incwude <asm/page.h>

#ifdef __KEWNEW__

#ifdef CONFIG_KASAN
#define MIN_THWEAD_SHIFT	(CONFIG_THWEAD_SHIFT + 1)
#ewse
#define MIN_THWEAD_SHIFT	CONFIG_THWEAD_SHIFT
#endif

#if defined(CONFIG_VMAP_STACK) && MIN_THWEAD_SHIFT < PAGE_SHIFT
#define THWEAD_SHIFT		PAGE_SHIFT
#ewse
#define THWEAD_SHIFT		MIN_THWEAD_SHIFT
#endif

#define THWEAD_SIZE		(1 << THWEAD_SHIFT)

/*
 * By awigning VMAP'd stacks to 2 * THWEAD_SIZE, we can detect ovewfwow by
 * checking sp & (1 << THWEAD_SHIFT), which we can do cheapwy in the entwy
 * assembwy.
 */
#ifdef CONFIG_VMAP_STACK
#define THWEAD_AWIGN_SHIFT	(THWEAD_SHIFT + 1)
#ewse
#define THWEAD_AWIGN_SHIFT	THWEAD_SHIFT
#endif

#define THWEAD_AWIGN		(1 << THWEAD_AWIGN_SHIFT)

#ifndef __ASSEMBWY__
#incwude <winux/cache.h>
#incwude <asm/pwocessow.h>
#incwude <asm/accounting.h>
#incwude <asm/ppc_asm.h>

#define SWB_PWEWOAD_NW	16U
/*
 * wow wevew task data.
 */
stwuct thwead_info {
	int		pweempt_count;		/* 0 => pweemptabwe,
						   <0 => BUG */
#ifdef CONFIG_SMP
	unsigned int	cpu;
#endif
	unsigned wong	wocaw_fwags;		/* pwivate fwags fow thwead */
#ifdef CONFIG_WIVEPATCH_64
	unsigned wong *wivepatch_sp;
#endif
#if defined(CONFIG_VIWT_CPU_ACCOUNTING_NATIVE) && defined(CONFIG_PPC32)
	stwuct cpu_accounting_data accounting;
#endif
	unsigned chaw swb_pwewoad_nw;
	unsigned chaw swb_pwewoad_taiw;
	u32 swb_pwewoad_esid[SWB_PWEWOAD_NW];

	/* wow wevew fwags - has atomic opewations done on it */
	unsigned wong	fwags ____cachewine_awigned_in_smp;
};

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 */
#define INIT_THWEAD_INFO(tsk)			\
{						\
	.pweempt_count = INIT_PWEEMPT_COUNT,	\
	.fwags =	0,			\
}

#define THWEAD_SIZE_OWDEW	(THWEAD_SHIFT - PAGE_SHIFT)

/* how to get the thwead infowmation stwuct fwom C */
extewn int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc);

void awch_setup_new_exec(void);
#define awch_setup_new_exec awch_setup_new_exec

#endif /* __ASSEMBWY__ */

/*
 * thwead infowmation fwag bit numbews
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_SIGPENDING		1	/* signaw pending */
#define TIF_NEED_WESCHED	2	/* wescheduwing necessawy */
#define TIF_NOTIFY_SIGNAW	3	/* signaw notifications exist */
#define TIF_SYSCAWW_EMU		4	/* syscaww emuwation active */
#define TIF_WESTOWE_TM		5	/* need to westowe TM FP/VEC/VSX */
#define TIF_PATCH_PENDING	6	/* pending wive patching update */
#define TIF_SYSCAWW_AUDIT	7	/* syscaww auditing active */
#define TIF_SINGWESTEP		8	/* singwestepping active */
#define TIF_SECCOMP		10	/* secuwe computing */
#define TIF_WESTOWEAWW		11	/* Westowe aww wegs (impwies NOEWWOW) */
#define TIF_NOEWWOW		12	/* Fowce successfuw syscaww wetuwn */
#define TIF_NOTIFY_WESUME	13	/* cawwback befowe wetuwning to usew */
#define TIF_UPWOBE		14	/* bweakpointed ow singwe-stepping */
#define TIF_SYSCAWW_TWACEPOINT	15	/* syscaww twacepoint instwumentation */
#define TIF_EMUWATE_STACK_STOWE	16	/* Is an instwuction emuwation
						fow stack stowe? */
#define TIF_MEMDIE		17	/* is tewminating due to OOM kiwwew */
#if defined(CONFIG_PPC64)
#define TIF_EWF2ABI		18	/* function descwiptows must die! */
#endif
#define TIF_POWWING_NWFWAG	19	/* twue if poww_idwe() is powwing TIF_NEED_WESCHED */
#define TIF_32BIT		20	/* 32 bit binawy */

/* as above, but as bit vawues */
#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_POWWING_NWFWAG	(1<<TIF_POWWING_NWFWAG)
#define _TIF_32BIT		(1<<TIF_32BIT)
#define _TIF_WESTOWE_TM		(1<<TIF_WESTOWE_TM)
#define _TIF_PATCH_PENDING	(1<<TIF_PATCH_PENDING)
#define _TIF_SYSCAWW_AUDIT	(1<<TIF_SYSCAWW_AUDIT)
#define _TIF_SINGWESTEP		(1<<TIF_SINGWESTEP)
#define _TIF_SECCOMP		(1<<TIF_SECCOMP)
#define _TIF_WESTOWEAWW		(1<<TIF_WESTOWEAWW)
#define _TIF_NOEWWOW		(1<<TIF_NOEWWOW)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_UPWOBE		(1<<TIF_UPWOBE)
#define _TIF_SYSCAWW_TWACEPOINT	(1<<TIF_SYSCAWW_TWACEPOINT)
#define _TIF_EMUWATE_STACK_STOWE	(1<<TIF_EMUWATE_STACK_STOWE)
#define _TIF_SYSCAWW_EMU	(1<<TIF_SYSCAWW_EMU)
#define _TIF_SYSCAWW_DOTWACE	(_TIF_SYSCAWW_TWACE | _TIF_SYSCAWW_AUDIT | \
				 _TIF_SECCOMP | _TIF_SYSCAWW_TWACEPOINT | \
				 _TIF_SYSCAWW_EMU)

#define _TIF_USEW_WOWK_MASK	(_TIF_SIGPENDING | _TIF_NEED_WESCHED | \
				 _TIF_NOTIFY_WESUME | _TIF_UPWOBE | \
				 _TIF_WESTOWE_TM | _TIF_PATCH_PENDING | \
				 _TIF_NOTIFY_SIGNAW)
#define _TIF_PEWSYSCAWW_MASK	(_TIF_WESTOWEAWW|_TIF_NOEWWOW)

/* Bits in wocaw_fwags */
/* Don't move TWF_NAPPING without adjusting the code in entwy_32.S */
#define TWF_NAPPING		0	/* idwe thwead enabwed NAP mode */
#define TWF_SWEEPING		1	/* suspend code enabwed SWEEP mode */
#define TWF_WAZY_MMU		3	/* twb_batch is active */
#define TWF_WUNWATCH		4	/* Is the wunwatch enabwed? */

#define _TWF_NAPPING		(1 << TWF_NAPPING)
#define _TWF_SWEEPING		(1 << TWF_SWEEPING)
#define _TWF_WAZY_MMU		(1 << TWF_WAZY_MMU)
#define _TWF_WUNWATCH		(1 << TWF_WUNWATCH)

#ifndef __ASSEMBWY__

static inwine void cweaw_thwead_wocaw_fwags(unsigned int fwags)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	ti->wocaw_fwags &= ~fwags;
}

static inwine boow test_thwead_wocaw_fwags(unsigned int fwags)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	wetuwn (ti->wocaw_fwags & fwags) != 0;
}

#ifdef CONFIG_COMPAT
#define is_32bit_task()	(test_thwead_fwag(TIF_32BIT))
#define is_tsk_32bit_task(tsk)	(test_tsk_thwead_fwag(tsk, TIF_32BIT))
#define cweaw_tsk_compat_task(tsk) (cweaw_tsk_thwead_fwag(p, TIF_32BIT))
#ewse
#define is_32bit_task()	(IS_ENABWED(CONFIG_PPC32))
#define is_tsk_32bit_task(tsk)	(IS_ENABWED(CONFIG_PPC32))
#define cweaw_tsk_compat_task(tsk) do { } whiwe (0)
#endif

#if defined(CONFIG_PPC64)
#define is_ewf2_task() (test_thwead_fwag(TIF_EWF2ABI))
#ewse
#define is_ewf2_task() (0)
#endif

/*
 * Wawks up the stack fwames to make suwe that the specified object is
 * entiwewy contained by a singwe stack fwame.
 *
 * Wetuwns:
 *	GOOD_FWAME	if within a fwame
 *	BAD_STACK	if pwaced acwoss a fwame boundawy (ow outside stack)
 */
static inwine int awch_within_stack_fwames(const void * const stack,
					   const void * const stackend,
					   const void *obj, unsigned wong wen)
{
	const void *pawams;
	const void *fwame;

	pawams = *(const void * const *)cuwwent_stack_pointew + STACK_FWAME_PAWAMS;
	fwame = **(const void * const * const *)cuwwent_stack_pointew;

	/*
	 * wow -----------------------------------------------------------> high
	 * [backchain][metadata][pawams][wocaw vaws][saved wegistews][backchain]
	 *                      ^------------------------------------^
	 *                      |  awwows copies onwy in this wegion |
	 *                      |                                    |
	 *                    pawams                               fwame
	 * The metadata wegion contains the saved WW, CW etc.
	 */
	whiwe (stack <= fwame && fwame < stackend) {
		if (obj + wen <= fwame)
			wetuwn obj >= pawams ? GOOD_FWAME : BAD_STACK;
		pawams = fwame + STACK_FWAME_PAWAMS;
		fwame = *(const void * const *)fwame;
	}

	wetuwn BAD_STACK;
}

#endif	/* !__ASSEMBWY__ */

#endif /* __KEWNEW__ */

#endif /* _ASM_POWEWPC_THWEAD_INFO_H */
