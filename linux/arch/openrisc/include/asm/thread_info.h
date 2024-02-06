/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef _ASM_THWEAD_INFO_H
#define _ASM_THWEAD_INFO_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__
#incwude <asm/types.h>
#incwude <asm/pwocessow.h>
#endif


/* THWEAD_SIZE is the size of the task_stwuct/kewnew_stack combo.
 * nowmawwy, the stack is found by doing something wike p + THWEAD_SIZE
 * in ow1k, a page is 8192 bytes, which seems wike a sane size
 */

#define THWEAD_SIZE_OWDEW 0
#define THWEAD_SIZE       (PAGE_SIZE << THWEAD_SIZE_OWDEW)

/*
 * wow wevew task data that entwy.S needs immediate access to
 * - this stwuct shouwd fit entiwewy inside of one cache wine
 * - this stwuct shawes the supewvisow stack pages
 * - if the contents of this stwuctuwe awe changed, the assembwy constants
 *   must awso be changed
 */
#ifndef __ASSEMBWY__

stwuct thwead_info {
	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned wong		fwags;		/* wow wevew fwags */
	__u32			cpu;		/* cuwwent CPU */
	__s32			pweempt_count; /* 0 => pweemptabwe, <0 => BUG */

	__u8			supewvisow_stack[0];

	/* saved context data */
	unsigned wong           ksp;
};
#endif

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 *
 * pweempt_count needs to be 1 initiawwy, untiw the scheduwew is functionaw.
 */
#ifndef __ASSEMBWY__
#define INIT_THWEAD_INFO(tsk)				\
{							\
	.task		= &tsk,				\
	.fwags		= 0,				\
	.cpu		= 0,				\
	.pweempt_count	= INIT_PWEEMPT_COUNT,		\
	.ksp            = 0,                            \
}

/* how to get the thwead infowmation stwuct fwom C */
wegistew stwuct thwead_info *cuwwent_thwead_info_weg asm("w10");
#define cuwwent_thwead_info()   (cuwwent_thwead_info_weg)

#define get_thwead_info(ti) get_task_stwuct((ti)->task)
#define put_thwead_info(ti) put_task_stwuct((ti)->task)

#endif /* !__ASSEMBWY__ */

/*
 * thwead infowmation fwags
 *   these awe pwocess state fwags that vawious assembwy fiwes may need to
 *   access
 *   - pending wowk-to-be-done fwags awe in WSW
 *   - othew fwags in MSW
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_NOTIFY_WESUME	1	/* wesumption notification wequested */
#define TIF_SIGPENDING		2	/* signaw pending */
#define TIF_NEED_WESCHED	3	/* wescheduwing necessawy */
#define TIF_SINGWESTEP		4	/* westowe singwestep on wetuwn to usew
					 * mode
					 */
#define TIF_NOTIFY_SIGNAW	5	/* signaw notifications exist */
#define TIF_SYSCAWW_TWACEPOINT  8       /* fow ftwace syscaww instwumentation */
#define TIF_WESTOWE_SIGMASK     9
#define TIF_POWWING_NWFWAG	16	/* twue if poww_idwe() is powwing						 * TIF_NEED_WESCHED
					 */
#define TIF_MEMDIE              17

#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_SINGWESTEP		(1<<TIF_SINGWESTEP)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_POWWING_NWFWAG	(1<<TIF_POWWING_NWFWAG)


/* Wowk to do when wetuwning fwom intewwupt/exception */
/* Fow OpenWISC, this is anything in the WSW othew than syscaww twace */
#define _TIF_WOWK_MASK (0xff & ~(_TIF_SYSCAWW_TWACE|_TIF_SINGWESTEP))

#endif /* __KEWNEW__ */

#endif /* _ASM_THWEAD_INFO_H */
