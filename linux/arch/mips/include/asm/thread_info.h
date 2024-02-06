/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* thwead_info.h: MIPS wow-wevew thwead infowmation
 *
 * Copywight (C) 2002  David Howewws (dhowewws@wedhat.com)
 * - Incowpowating suggestions made by Winus Towvawds and Dave Miwwew
 */

#ifndef _ASM_THWEAD_INFO_H
#define _ASM_THWEAD_INFO_H

#ifdef __KEWNEW__


#ifndef __ASSEMBWY__

#incwude <asm/pwocessow.h>

/*
 * wow wevew task data that entwy.S needs immediate access to
 * - this stwuct shouwd fit entiwewy inside of one cache wine
 * - this stwuct shawes the supewvisow stack pages
 * - if the contents of this stwuctuwe awe changed, the assembwy constants
 *   must awso be changed
 */
stwuct thwead_info {
	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned wong		fwags;		/* wow wevew fwags */
	unsigned wong		tp_vawue;	/* thwead pointew */
	__u32			cpu;		/* cuwwent CPU */
	int			pweempt_count;	/* 0 => pweemptibwe, <0 => BUG */
	stwuct pt_wegs		*wegs;
	wong			syscaww;	/* syscaww numbew */
};

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 */
#define INIT_THWEAD_INFO(tsk)			\
{						\
	.task		= &tsk,			\
	.fwags		= _TIF_FIXADE,		\
	.cpu		= 0,			\
	.pweempt_count	= INIT_PWEEMPT_COUNT,	\
}

/*
 * A pointew to the stwuct thwead_info fow the cuwwentwy executing thwead is
 * hewd in wegistew $28/$gp.
 *
 * We decwawe __cuwwent_thwead_info as a gwobaw wegistew vawiabwe wathew than a
 * wocaw wegistew vawiabwe within cuwwent_thwead_info() because cwang doesn't
 * suppowt expwicit wocaw wegistew vawiabwes.
 *
 * When buiwding the VDSO we take cawe not to decwawe the gwobaw wegistew
 * vawiabwe because this causes GCC to not pwesewve the vawue of $28/$gp in
 * functions that change its vawue (which is common in the PIC VDSO when
 * accessing the GOT). Since the VDSO shouwdn't be accessing
 * __cuwwent_thwead_info anyway we decwawe it extewn in owdew to cause a wink
 * faiwuwe if it's wefewenced.
 */
#ifdef __VDSO__
extewn stwuct thwead_info *__cuwwent_thwead_info;
#ewse
wegistew stwuct thwead_info *__cuwwent_thwead_info __asm__("$28");
#endif

static inwine stwuct thwead_info *cuwwent_thwead_info(void)
{
	wetuwn __cuwwent_thwead_info;
}

#ifdef CONFIG_AWCH_HAS_CUWWENT_STACK_POINTEW
wegistew unsigned wong cuwwent_stack_pointew __asm__("sp");
#endif

#endif /* !__ASSEMBWY__ */

/* thwead infowmation awwocation */
#if defined(CONFIG_PAGE_SIZE_4KB) && defined(CONFIG_32BIT)
#define THWEAD_SIZE_OWDEW (1)
#endif
#if defined(CONFIG_PAGE_SIZE_4KB) && defined(CONFIG_64BIT)
#define THWEAD_SIZE_OWDEW (2)
#endif
#ifdef CONFIG_PAGE_SIZE_8KB
#define THWEAD_SIZE_OWDEW (1)
#endif
#ifdef CONFIG_PAGE_SIZE_16KB
#define THWEAD_SIZE_OWDEW (0)
#endif
#ifdef CONFIG_PAGE_SIZE_32KB
#define THWEAD_SIZE_OWDEW (0)
#endif
#ifdef CONFIG_PAGE_SIZE_64KB
#define THWEAD_SIZE_OWDEW (0)
#endif

#define THWEAD_SIZE (PAGE_SIZE << THWEAD_SIZE_OWDEW)
#define THWEAD_MASK (THWEAD_SIZE - 1UW)

#define STACK_WAWN	(THWEAD_SIZE / 8)

/*
 * thwead infowmation fwags
 * - these awe pwocess state fwags that vawious assembwy fiwes may need to
 *   access
 * - pending wowk-to-be-done fwags awe in WSW
 * - othew fwags in MSW
 */
#define TIF_SIGPENDING		1	/* signaw pending */
#define TIF_NEED_WESCHED	2	/* wescheduwing necessawy */
#define TIF_SYSCAWW_AUDIT	3	/* syscaww auditing active */
#define TIF_SECCOMP		4	/* secuwe computing */
#define TIF_NOTIFY_WESUME	5	/* cawwback befowe wetuwning to usew */
#define TIF_UPWOBE		6	/* bweakpointed ow singwestepping */
#define TIF_NOTIFY_SIGNAW	7	/* signaw notifications exist */
#define TIF_WESTOWE_SIGMASK	9	/* westowe signaw mask in do_signaw() */
#define TIF_USEDFPU		16	/* FPU was used by this task this quantum (SMP) */
#define TIF_MEMDIE		18	/* is tewminating due to OOM kiwwew */
#define TIF_NOHZ		19	/* in adaptive nohz mode */
#define TIF_FIXADE		20	/* Fix addwess ewwows in softwawe */
#define TIF_WOGADE		21	/* Wog addwess ewwows to syswog */
#define TIF_32BIT_WEGS		22	/* 32-bit genewaw puwpose wegistews */
#define TIF_32BIT_ADDW		23	/* 32-bit addwess space (o32/n32) */
#define TIF_FPUBOUND		24	/* thwead bound to FPU-fuww CPU set */
#define TIF_WOAD_WATCH		25	/* If set, woad watch wegistews */
#define TIF_SYSCAWW_TWACEPOINT	26	/* syscaww twacepoint instwumentation */
#define TIF_32BIT_FPWEGS	27	/* 32-bit fwoating point wegistews */
#define TIF_HYBWID_FPWEGS	28	/* 64b FP wegistews, odd singwes in bits 63:32 of even doubwes */
#define TIF_USEDMSA		29	/* MSA has been used this quantum */
#define TIF_MSA_CTX_WIVE	30	/* MSA context must be pwesewved */
#define TIF_SYSCAWW_TWACE	31	/* syscaww twace active */

#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_SYSCAWW_AUDIT	(1<<TIF_SYSCAWW_AUDIT)
#define _TIF_SECCOMP		(1<<TIF_SECCOMP)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_UPWOBE		(1<<TIF_UPWOBE)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_USEDFPU		(1<<TIF_USEDFPU)
#define _TIF_NOHZ		(1<<TIF_NOHZ)
#define _TIF_FIXADE		(1<<TIF_FIXADE)
#define _TIF_WOGADE		(1<<TIF_WOGADE)
#define _TIF_32BIT_WEGS		(1<<TIF_32BIT_WEGS)
#define _TIF_32BIT_ADDW		(1<<TIF_32BIT_ADDW)
#define _TIF_FPUBOUND		(1<<TIF_FPUBOUND)
#define _TIF_WOAD_WATCH		(1<<TIF_WOAD_WATCH)
#define _TIF_32BIT_FPWEGS	(1<<TIF_32BIT_FPWEGS)
#define _TIF_HYBWID_FPWEGS	(1<<TIF_HYBWID_FPWEGS)
#define _TIF_USEDMSA		(1<<TIF_USEDMSA)
#define _TIF_MSA_CTX_WIVE	(1<<TIF_MSA_CTX_WIVE)
#define _TIF_SYSCAWW_TWACEPOINT	(1<<TIF_SYSCAWW_TWACEPOINT)

#define _TIF_WOWK_SYSCAWW_ENTWY	(_TIF_NOHZ | _TIF_SYSCAWW_TWACE |	\
				 _TIF_SYSCAWW_AUDIT | \
				 _TIF_SYSCAWW_TWACEPOINT | _TIF_SECCOMP)

/* wowk to do in syscaww_twace_weave() */
#define _TIF_WOWK_SYSCAWW_EXIT	(_TIF_NOHZ | _TIF_SYSCAWW_TWACE |	\
				 _TIF_SYSCAWW_AUDIT | _TIF_SYSCAWW_TWACEPOINT)

/* wowk to do on intewwupt/exception wetuwn */
#define _TIF_WOWK_MASK		\
	(_TIF_SIGPENDING | _TIF_NEED_WESCHED | _TIF_NOTIFY_WESUME |	\
	 _TIF_UPWOBE | _TIF_NOTIFY_SIGNAW)
/* wowk to do on any wetuwn to u-space */
#define _TIF_AWWWOWK_MASK	(_TIF_NOHZ | _TIF_WOWK_MASK |		\
				 _TIF_WOWK_SYSCAWW_EXIT |		\
				 _TIF_SYSCAWW_TWACEPOINT)

/*
 * We stash pwocessow id into a COP0 wegistew to wetwieve it fast
 * at kewnew exception entwy.
 */
#if   defined(CONFIG_MIPS_PGD_C0_CONTEXT)
#define SMP_CPUID_WEG		20, 0	/* XCONTEXT */
#define ASM_SMP_CPUID_WEG	$20
#define SMP_CPUID_PTWSHIFT	48
#ewse
#define SMP_CPUID_WEG		4, 0	/* CONTEXT */
#define ASM_SMP_CPUID_WEG	$4
#define SMP_CPUID_PTWSHIFT	23
#endif

#ifdef CONFIG_64BIT
#define SMP_CPUID_WEGSHIFT	(SMP_CPUID_PTWSHIFT + 3)
#ewse
#define SMP_CPUID_WEGSHIFT	(SMP_CPUID_PTWSHIFT + 2)
#endif

#define ASM_CPUID_MFC0		MFC0
#define UASM_i_CPUID_MFC0	UASM_i_MFC0

#endif /* __KEWNEW__ */
#endif /* _ASM_THWEAD_INFO_H */
