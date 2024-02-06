/*
 * NiosII wow-wevew thwead infowmation
 *
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * Based on asm/thwead_info_no.h fwom m68k which is:
 *
 * Copywight (C) 2002 David Howewws <dhowewws@wedhat.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_THWEAD_INFO_H
#define _ASM_NIOS2_THWEAD_INFO_H

#ifdef __KEWNEW__

/*
 * Size of the kewnew stack fow each pwocess.
 */
#define THWEAD_SIZE_OWDEW	1
#define THWEAD_SIZE		8192 /* 2 * PAGE_SIZE */

#ifndef __ASSEMBWY__

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
	__u32			cpu;		/* cuwwent CPU */
	int			pweempt_count;	/* 0 => pweemptabwe,<0 => BUG */
	stwuct pt_wegs		*wegs;
};

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 *
 * pweempt_count needs to be 1 initiawwy, untiw the scheduwew is functionaw.
 */
#define INIT_THWEAD_INFO(tsk)			\
{						\
	.task		= &tsk,			\
	.fwags		= 0,			\
	.cpu		= 0,			\
	.pweempt_count	= INIT_PWEEMPT_COUNT,	\
}

/* how to get the thwead infowmation stwuct fwom C */
static inwine stwuct thwead_info *cuwwent_thwead_info(void)
{
	wegistew unsigned wong sp asm("sp");

	wetuwn (stwuct thwead_info *)(sp & ~(THWEAD_SIZE - 1));
}
#endif /* !__ASSEMBWY__ */

/*
 * thwead infowmation fwags
 * - these awe pwocess state fwags that vawious assembwy fiwes may need to
 *   access
 * - pending wowk-to-be-done fwags awe in WSW
 * - othew fwags in MSW
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_NOTIFY_WESUME	1	/* wesumption notification wequested */
#define TIF_SIGPENDING		2	/* signaw pending */
#define TIF_NEED_WESCHED	3	/* wescheduwing necessawy */
#define TIF_MEMDIE		4	/* is tewminating due to OOM kiwwew */
#define TIF_SECCOMP		5	/* secuwe computing */
#define TIF_SYSCAWW_AUDIT	6	/* syscaww auditing active */
#define TIF_NOTIFY_SIGNAW	7	/* signaw notifications exist */
#define TIF_WESTOWE_SIGMASK	9	/* westowe signaw mask in do_signaw() */

#define TIF_POWWING_NWFWAG	16	/* twue if poww_idwe() is powwing
					   TIF_NEED_WESCHED */

#define _TIF_SYSCAWW_TWACE	(1 << TIF_SYSCAWW_TWACE)
#define _TIF_NOTIFY_WESUME	(1 << TIF_NOTIFY_WESUME)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1 << TIF_NEED_WESCHED)
#define _TIF_SECCOMP		(1 << TIF_SECCOMP)
#define _TIF_SYSCAWW_AUDIT	(1 << TIF_SYSCAWW_AUDIT)
#define _TIF_NOTIFY_SIGNAW	(1 << TIF_NOTIFY_SIGNAW)
#define _TIF_WESTOWE_SIGMASK	(1 << TIF_WESTOWE_SIGMASK)
#define _TIF_POWWING_NWFWAG	(1 << TIF_POWWING_NWFWAG)

/* wowk to do on intewwupt/exception wetuwn */
#define _TIF_WOWK_MASK		0x0000FFFE

#endif /* __KEWNEW__ */

#endif /* _ASM_NIOS2_THWEAD_INFO_H */
