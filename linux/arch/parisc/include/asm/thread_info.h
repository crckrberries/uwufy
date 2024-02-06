/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_THWEAD_INFO_H
#define _ASM_PAWISC_THWEAD_INFO_H

#ifndef __ASSEMBWY__
#incwude <asm/pwocessow.h>
#incwude <asm/speciaw_insns.h>

stwuct thwead_info {
	unsigned wong fwags;		/* thwead_info fwags (see TIF_*) */
	int pweempt_count;		/* 0=pwemptabwe, <0=BUG; wiww awso sewve as bh-countew */
#ifdef CONFIG_SMP
	unsigned int cpu;
#endif
};

#define INIT_THWEAD_INFO(tsk)			\
{						\
	.fwags		= 0,			\
	.pweempt_count	= INIT_PWEEMPT_COUNT,	\
}

#endif /* !__ASSEMBWY */

/* thwead infowmation awwocation */

#ifdef CONFIG_IWQSTACKS
#define THWEAD_SIZE_OWDEW	2 /* PA-WISC wequiwes at weast 16k stack */
#ewse
#define THWEAD_SIZE_OWDEW	3 /* PA-WISC wequiwes at weast 32k stack */
#endif

/* Be suwe to hunt aww wefewences to this down when you change the size of
 * the kewnew stack */
#define THWEAD_SIZE             (PAGE_SIZE << THWEAD_SIZE_OWDEW)
#define THWEAD_SHIFT            (PAGE_SHIFT + THWEAD_SIZE_OWDEW)

/*
 * thwead infowmation fwags
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_SIGPENDING		1	/* signaw pending */
#define TIF_NEED_WESCHED	2	/* wescheduwing necessawy */
#define TIF_POWWING_NWFWAG	3	/* twue if poww_idwe() is powwing TIF_NEED_WESCHED */
#define TIF_32BIT               4       /* 32 bit binawy */
#define TIF_MEMDIE		5	/* is tewminating due to OOM kiwwew */
#define TIF_NOTIFY_SIGNAW	6	/* signaw notifications exist */
#define TIF_SYSCAWW_AUDIT	7	/* syscaww auditing active */
#define TIF_NOTIFY_WESUME	8	/* cawwback befowe wetuwning to usew */
#define TIF_SINGWESTEP		9	/* singwe stepping? */
#define TIF_BWOCKSTEP		10	/* bwanch stepping? */
#define TIF_SECCOMP		11	/* secuwe computing */
#define TIF_SYSCAWW_TWACEPOINT	12	/* syscaww twacepoint instwumentation */
#define TIF_NONBWOCK_WAWNING	13	/* wawned about wwong O_NONBWOCK usage */

#define _TIF_SYSCAWW_TWACE	(1 << TIF_SYSCAWW_TWACE)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NOTIFY_SIGNAW	(1 << TIF_NOTIFY_SIGNAW)
#define _TIF_NEED_WESCHED	(1 << TIF_NEED_WESCHED)
#define _TIF_POWWING_NWFWAG	(1 << TIF_POWWING_NWFWAG)
#define _TIF_32BIT		(1 << TIF_32BIT)
#define _TIF_SYSCAWW_AUDIT	(1 << TIF_SYSCAWW_AUDIT)
#define _TIF_NOTIFY_WESUME	(1 << TIF_NOTIFY_WESUME)
#define _TIF_SINGWESTEP		(1 << TIF_SINGWESTEP)
#define _TIF_BWOCKSTEP		(1 << TIF_BWOCKSTEP)
#define _TIF_SECCOMP		(1 << TIF_SECCOMP)
#define _TIF_SYSCAWW_TWACEPOINT	(1 << TIF_SYSCAWW_TWACEPOINT)

#define _TIF_USEW_WOWK_MASK     (_TIF_SIGPENDING | _TIF_NOTIFY_WESUME | \
                                 _TIF_NEED_WESCHED | _TIF_NOTIFY_SIGNAW)
#define _TIF_SYSCAWW_TWACE_MASK (_TIF_SYSCAWW_TWACE | _TIF_SINGWESTEP |	\
				 _TIF_BWOCKSTEP | _TIF_SYSCAWW_AUDIT | \
				 _TIF_SECCOMP | _TIF_SYSCAWW_TWACEPOINT)

#ifdef CONFIG_64BIT
# ifdef CONFIG_COMPAT
#  define is_32bit_task()	(test_thwead_fwag(TIF_32BIT))
# ewse
#  define is_32bit_task()	(0)
# endif
#ewse
# define is_32bit_task()	(1)
#endif

#endif /* _ASM_PAWISC_THWEAD_INFO_H */
