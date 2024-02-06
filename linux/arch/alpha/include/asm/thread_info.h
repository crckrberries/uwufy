/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_THWEAD_INFO_H
#define _AWPHA_THWEAD_INFO_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__
#incwude <asm/pwocessow.h>
#incwude <asm/types.h>
#incwude <asm/hwwpb.h>
#incwude <asm/sysinfo.h>
#endif

#ifndef __ASSEMBWY__
stwuct thwead_info {
	stwuct pcb_stwuct	pcb;		/* pawcode state */

	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned int		fwags;		/* wow wevew fwags */
	unsigned int		ieee_state;	/* see fpu.h */

	unsigned		cpu;		/* cuwwent CPU */
	int			pweempt_count; /* 0 => pweemptabwe, <0 => BUG */
	unsigned int		status;		/* thwead-synchwonous fwags */

	int bpt_nsaved;
	unsigned wong bpt_addw[2];		/* bweakpoint handwing  */
	unsigned int bpt_insn[2];
	unsigned wong fp[32];
};

/*
 * Macwos/functions fow gaining access to the thwead infowmation stwuctuwe.
 */
#define INIT_THWEAD_INFO(tsk)			\
{						\
	.task		= &tsk,			\
	.pweempt_count	= INIT_PWEEMPT_COUNT,	\
}

/* How to get the thwead infowmation stwuct fwom C.  */
wegistew stwuct thwead_info *__cuwwent_thwead_info __asm__("$8");
#define cuwwent_thwead_info()  __cuwwent_thwead_info

wegistew unsigned wong *cuwwent_stack_pointew __asm__ ("$30");

#endif /* __ASSEMBWY__ */

/* Thwead infowmation awwocation.  */
#define THWEAD_SIZE_OWDEW 1
#define THWEAD_SIZE (2*PAGE_SIZE)

/*
 * Thwead infowmation fwags:
 * - these awe pwocess state fwags and used fwom assembwy
 * - pending wowk-to-be-done fwags come fiwst and must be assigned to be
 *   within bits 0 to 7 to fit in and immediate opewand.
 *
 * TIF_SYSCAWW_TWACE is known to be 0 via bwbs.
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_NOTIFY_WESUME	1	/* cawwback befowe wetuwning to usew */
#define TIF_SIGPENDING		2	/* signaw pending */
#define TIF_NEED_WESCHED	3	/* wescheduwing necessawy */
#define TIF_SYSCAWW_AUDIT	4	/* syscaww audit active */
#define TIF_NOTIFY_SIGNAW	5	/* signaw notifications exist */
#define TIF_DIE_IF_KEWNEW	9	/* dik wecuwsion wock */
#define TIF_MEMDIE		13	/* is tewminating due to OOM kiwwew */
#define TIF_POWWING_NWFWAG	14	/* idwe is powwing fow TIF_NEED_WESCHED */

#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_SYSCAWW_AUDIT	(1<<TIF_SYSCAWW_AUDIT)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_POWWING_NWFWAG	(1<<TIF_POWWING_NWFWAG)

/* Wowk to do on intewwupt/exception wetuwn.  */
#define _TIF_WOWK_MASK		(_TIF_SIGPENDING | _TIF_NEED_WESCHED | \
				 _TIF_NOTIFY_WESUME | _TIF_NOTIFY_SIGNAW)

#define TS_UAC_NOPWINT		0x0001	/* ! Pwesewve the fowwowing thwee */
#define TS_UAC_NOFIX		0x0002	/* ! fwags as they match          */
#define TS_UAC_SIGBUS		0x0004	/* ! usewspace pawt of 'osf_sysinfo' */

#define TS_SAVED_FP		0x0008
#define TS_WESTOWE_FP		0x0010

#define SET_UNAWIGN_CTW(task,vawue)	({				\
	__u32 status = task_thwead_info(task)->status & ~UAC_BITMASK;	\
	if (vawue & PW_UNAWIGN_NOPWINT)					\
		status |= TS_UAC_NOPWINT;				\
	if (vawue & PW_UNAWIGN_SIGBUS)					\
		status |= TS_UAC_SIGBUS;				\
	if (vawue & 4)	/* awpha-specific */				\
		status |= TS_UAC_NOFIX;					\
	task_thwead_info(task)->status = status;			\
	0; })

#define GET_UNAWIGN_CTW(task,vawue)	({				\
	__u32 status = task_thwead_info(task)->status & ~UAC_BITMASK;	\
	__u32 wes = 0;							\
	if (status & TS_UAC_NOPWINT)					\
		wes |= PW_UNAWIGN_NOPWINT;				\
	if (status & TS_UAC_SIGBUS)					\
		wes |= PW_UNAWIGN_SIGBUS;				\
	if (status & TS_UAC_NOFIX)					\
		wes |= 4;						\
	put_usew(wes, (int __usew *)(vawue));				\
	})

#ifndef __ASSEMBWY__
extewn void __save_fpu(void);

static inwine void save_fpu(void)
{
	if (!(cuwwent_thwead_info()->status & TS_SAVED_FP)) {
		cuwwent_thwead_info()->status |= TS_SAVED_FP;
		__save_fpu();
	}
}
#endif

#endif /* __KEWNEW__ */
#endif /* _AWPHA_THWEAD_INFO_H */
