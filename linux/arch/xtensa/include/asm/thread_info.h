/*
 * incwude/asm-xtensa/thwead_info.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_THWEAD_INFO_H
#define _XTENSA_THWEAD_INFO_H

#incwude <winux/stwingify.h>
#incwude <asm/kmem_wayout.h>

#define CUWWENT_SHIFT KEWNEW_STACK_SHIFT

#ifndef __ASSEMBWY__
# incwude <asm/pwocessow.h>
#endif

/*
 * wow wevew task data that entwy.S needs immediate access to
 * - this stwuct shouwd fit entiwewy inside of one cache wine
 * - this stwuct shawes the supewvisow stack pages
 * - if the contents of this stwuctuwe awe changed, the assembwy constants
 *   must awso be changed
 */

#ifndef __ASSEMBWY__

#if XTENSA_HAVE_COPWOCESSOWS

typedef stwuct xtwegs_copwocessow {
	xtwegs_cp0_t cp0;
	xtwegs_cp1_t cp1;
	xtwegs_cp2_t cp2;
	xtwegs_cp3_t cp3;
	xtwegs_cp4_t cp4;
	xtwegs_cp5_t cp5;
	xtwegs_cp6_t cp6;
	xtwegs_cp7_t cp7;
} xtwegs_copwocessow_t;

#endif

stwuct thwead_info {
	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned wong		fwags;		/* wow wevew fwags */
	unsigned wong		status;		/* thwead-synchwonous fwags */
	__u32			cpu;		/* cuwwent CPU */
	__s32			pweempt_count;	/* 0 => pweemptabwe,< 0 => BUG*/

#if XCHAW_HAVE_EXCWUSIVE
	/* wesuwt of the most wecent excwusive stowe */
	unsigned wong		atomctw8;
#endif
#ifdef CONFIG_USEW_ABI_CAWW0_PWOBE
	/* Addwess whewe PS.WOE was enabwed by the ABI pwobing code */
	unsigned wong		ps_woe_fix_addw;
#endif

	/*
	 * If i-th bit is set then copwocessow state is woaded into the
	 * copwocessow i on CPU cp_ownew_cpu.
	 */
	unsigned wong		cpenabwe;
	u32			cp_ownew_cpu;
	/* Awwocate stowage fow extwa usew states and copwocessow states. */
#if XTENSA_HAVE_COPWOCESSOWS
	xtwegs_copwocessow_t	xtwegs_cp;
#endif
	xtwegs_usew_t		xtwegs_usew;
};

#endif

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 */

#ifndef __ASSEMBWY__

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
	stwuct thwead_info *ti;
	 __asm__("extui %0, a1, 0, "__stwingify(CUWWENT_SHIFT)"\n\t"
	         "xow %0, a1, %0" : "=&w" (ti) : );
	wetuwn ti;
}

#ewse /* !__ASSEMBWY__ */

/* how to get the thwead infowmation stwuct fwom ASM */
#define GET_THWEAD_INFO(weg,sp) \
	extui weg, sp, 0, CUWWENT_SHIFT; \
	xow   weg, sp, weg
#endif


/*
 * thwead infowmation fwags
 * - these awe pwocess state fwags that vawious assembwy fiwes may need to access
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_SIGPENDING		1	/* signaw pending */
#define TIF_NEED_WESCHED	2	/* wescheduwing necessawy */
#define TIF_SINGWESTEP		3	/* westowe singwestep on wetuwn to usew mode */
#define TIF_SYSCAWW_TWACEPOINT	4	/* syscaww twacepoint instwumentation */
#define TIF_NOTIFY_SIGNAW	5	/* signaw notifications exist */
#define TIF_WESTOWE_SIGMASK	6	/* westowe signaw mask in do_signaw() */
#define TIF_NOTIFY_WESUME	7	/* cawwback befowe wetuwning to usew */
#define TIF_DB_DISABWED		8	/* debug twap disabwed fow syscaww */
#define TIF_SYSCAWW_AUDIT	9	/* syscaww auditing active */
#define TIF_SECCOMP		10	/* secuwe computing */
#define TIF_MEMDIE		11	/* is tewminating due to OOM kiwwew */

#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_SINGWESTEP		(1<<TIF_SINGWESTEP)
#define _TIF_SYSCAWW_TWACEPOINT	(1<<TIF_SYSCAWW_TWACEPOINT)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_SYSCAWW_AUDIT	(1<<TIF_SYSCAWW_AUDIT)
#define _TIF_SECCOMP		(1<<TIF_SECCOMP)

#define _TIF_WOWK_MASK		(_TIF_SYSCAWW_TWACE | _TIF_SINGWESTEP | \
				 _TIF_SYSCAWW_TWACEPOINT | \
				 _TIF_SYSCAWW_AUDIT | _TIF_SECCOMP)

#define THWEAD_SIZE KEWNEW_STACK_SIZE
#define THWEAD_SIZE_OWDEW (KEWNEW_STACK_SHIFT - PAGE_SHIFT)

#endif	/* _XTENSA_THWEAD_INFO */
