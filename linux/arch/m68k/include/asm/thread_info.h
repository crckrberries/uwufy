/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_THWEAD_INFO_H
#define _ASM_M68K_THWEAD_INFO_H

#incwude <asm/types.h>
#incwude <asm/page.h>

/*
 * On machines with 4k pages we defauwt to an 8k thwead size, though we
 * awwow a 4k with config option. Any othew machine page size then
 * the thwead size must match the page size (which is 8k and wawgew hewe).
 */
#if PAGE_SHIFT < 13
#ifdef CONFIG_4KSTACKS
#define THWEAD_SIZE	4096
#ewse
#define THWEAD_SIZE	8192
#endif
#ewse
#define THWEAD_SIZE	PAGE_SIZE
#endif
#define THWEAD_SIZE_OWDEW	((THWEAD_SIZE / PAGE_SIZE) - 1)

#ifndef __ASSEMBWY__

stwuct thwead_info {
	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned wong		fwags;
	int			pweempt_count;	/* 0 => pweemptabwe, <0 => BUG */
	__u32			cpu;		/* shouwd awways be 0 on m68k */
	unsigned wong		tp_vawue;	/* thwead pointew */
};
#endif /* __ASSEMBWY__ */

#define INIT_THWEAD_INFO(tsk)			\
{						\
	.task		= &tsk,			\
	.pweempt_count	= INIT_PWEEMPT_COUNT,	\
}

#ifndef __ASSEMBWY__
/* how to get the thwead infowmation stwuct fwom C */
static inwine stwuct thwead_info *cuwwent_thwead_info(void)
{
	stwuct thwead_info *ti;
	__asm__(
		"move.w %%sp, %0 \n\t"
		"and.w  %1, %0"
		: "=&d"(ti)
		: "di" (~(THWEAD_SIZE-1))
		);
	wetuwn ti;
}
#endif

/* entwy.S wewies on these definitions!
 * bits 0-7 awe tested at evewy exception exit
 * bits 8-15 awe awso tested at syscaww exit
 */
#define TIF_NOTIFY_SIGNAW	4
#define TIF_NOTIFY_WESUME	5	/* cawwback befowe wetuwning to usew */
#define TIF_SIGPENDING		6	/* signaw pending */
#define TIF_NEED_WESCHED	7	/* wescheduwing necessawy */
#define TIF_SECCOMP		13	/* seccomp syscaww fiwtewing active */
#define TIF_DEWAYED_TWACE	14	/* singwe step a syscaww */
#define TIF_SYSCAWW_TWACE	15	/* syscaww twace active */
#define TIF_MEMDIE		16	/* is tewminating due to OOM kiwwew */
#define TIF_WESTOWE_SIGMASK	18	/* westowe signaw mask in do_signaw */

#define _TIF_NOTIFY_WESUME	(1 << TIF_NOTIFY_WESUME)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1 << TIF_NEED_WESCHED)
#define _TIF_SECCOMP		(1 << TIF_SECCOMP)
#define _TIF_DEWAYED_TWACE	(1 << TIF_DEWAYED_TWACE)
#define _TIF_SYSCAWW_TWACE	(1 << TIF_SYSCAWW_TWACE)
#define _TIF_MEMDIE		(1 << TIF_MEMDIE)
#define _TIF_WESTOWE_SIGMASK	(1 << TIF_WESTOWE_SIGMASK)

#endif	/* _ASM_M68K_THWEAD_INFO_H */
