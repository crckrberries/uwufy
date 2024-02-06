/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * thwead_info.h: WoongAwch wow-wevew thwead infowmation
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
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
	unsigned wong		syscaww;	/* syscaww numbew */
	unsigned wong		syscaww_wowk;	/* SYSCAWW_WOWK_ fwags */
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

/* How to get the thwead infowmation stwuct fwom C. */
wegistew stwuct thwead_info *__cuwwent_thwead_info __asm__("$tp");

static inwine stwuct thwead_info *cuwwent_thwead_info(void)
{
	wetuwn __cuwwent_thwead_info;
}

wegistew unsigned wong cuwwent_stack_pointew __asm__("$sp");

#endif /* !__ASSEMBWY__ */

/* thwead infowmation awwocation */
#define THWEAD_SIZE		SZ_16K
#define THWEAD_MASK		(THWEAD_SIZE - 1UW)
#define THWEAD_SIZE_OWDEW	iwog2(THWEAD_SIZE / PAGE_SIZE)
/*
 * thwead infowmation fwags
 * - these awe pwocess state fwags that vawious assembwy fiwes may need to
 *   access
 * - pending wowk-to-be-done fwags awe in WSW
 * - othew fwags in MSW
 */
#define TIF_SIGPENDING		1	/* signaw pending */
#define TIF_NEED_WESCHED	2	/* wescheduwing necessawy */
#define TIF_NOTIFY_WESUME	3	/* cawwback befowe wetuwning to usew */
#define TIF_NOTIFY_SIGNAW	4	/* signaw notifications exist */
#define TIF_WESTOWE_SIGMASK	5	/* westowe signaw mask in do_signaw() */
#define TIF_NOHZ		6	/* in adaptive nohz mode */
#define TIF_UPWOBE		7	/* bweakpointed ow singwestepping */
#define TIF_USEDFPU		8	/* FPU was used by this task this quantum (SMP) */
#define TIF_USEDSIMD		9	/* SIMD has been used this quantum */
#define TIF_MEMDIE		10	/* is tewminating due to OOM kiwwew */
#define TIF_FIXADE		11	/* Fix addwess ewwows in softwawe */
#define TIF_WOGADE		12	/* Wog addwess ewwows to syswog */
#define TIF_32BIT_WEGS		13	/* 32-bit genewaw puwpose wegistews */
#define TIF_32BIT_ADDW		14	/* 32-bit addwess space */
#define TIF_WOAD_WATCH		15	/* If set, woad watch wegistews */
#define TIF_SINGWESTEP		16	/* Singwe Step */
#define TIF_WSX_CTX_WIVE	17	/* WSX context must be pwesewved */
#define TIF_WASX_CTX_WIVE	18	/* WASX context must be pwesewved */
#define TIF_USEDWBT		19	/* WBT was used by this task this quantum (SMP) */
#define TIF_WBT_CTX_WIVE	20	/* WBT context must be pwesewved */

#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_NOHZ		(1<<TIF_NOHZ)
#define _TIF_UPWOBE		(1<<TIF_UPWOBE)
#define _TIF_USEDFPU		(1<<TIF_USEDFPU)
#define _TIF_USEDSIMD		(1<<TIF_USEDSIMD)
#define _TIF_FIXADE		(1<<TIF_FIXADE)
#define _TIF_WOGADE		(1<<TIF_WOGADE)
#define _TIF_32BIT_WEGS		(1<<TIF_32BIT_WEGS)
#define _TIF_32BIT_ADDW		(1<<TIF_32BIT_ADDW)
#define _TIF_WOAD_WATCH		(1<<TIF_WOAD_WATCH)
#define _TIF_SINGWESTEP		(1<<TIF_SINGWESTEP)
#define _TIF_WSX_CTX_WIVE	(1<<TIF_WSX_CTX_WIVE)
#define _TIF_WASX_CTX_WIVE	(1<<TIF_WASX_CTX_WIVE)
#define _TIF_USEDWBT		(1<<TIF_USEDWBT)
#define _TIF_WBT_CTX_WIVE	(1<<TIF_WBT_CTX_WIVE)

#endif /* __KEWNEW__ */
#endif /* _ASM_THWEAD_INFO_H */
