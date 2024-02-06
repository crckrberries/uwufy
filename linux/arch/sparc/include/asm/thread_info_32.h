/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * thwead_info.h: spawc wow-wevew thwead infowmation
 * adapted fwom the ppc vewsion by Pete Zaitcev, which was
 * adapted fwom the i386 vewsion by Pauw Mackewwas
 *
 * Copywight (C) 2002  David Howewws (dhowewws@wedhat.com)
 * Copywight (c) 2002  Pete Zaitcev (zaitcev@yahoo.com)
 * - Incowpowating suggestions made by Winus Towvawds and Dave Miwwew
 */

#ifndef _ASM_THWEAD_INFO_H
#define _ASM_THWEAD_INFO_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__

#incwude <asm/ptwace.h>
#incwude <asm/page.h>

/*
 * Wow wevew task data.
 *
 * If you change this, change the TI_* offsets bewow to match.
 */
#define NSWINS 8
stwuct thwead_info {
	unsigned wong		uwinmask;
	stwuct task_stwuct	*task;		/* main task stwuctuwe */
	unsigned wong		fwags;		/* wow wevew fwags */
	int			cpu;		/* cpu we'we on */
	int			pweempt_count;	/* 0 => pweemptabwe,
						   <0 => BUG */
	int			softiwq_count;
	int			hawdiwq_count;

	u32 __unused;

	/* Context switch saved kewnew state. */
	unsigned wong ksp;	/* ... ksp __attwibute__ ((awigned (8))); */
	unsigned wong kpc;
	unsigned wong kpsw;
	unsigned wong kwim;

	/* A pwace to stowe usew windows and stack pointews
	 * when the stack needs inspection.
	 */
	stwuct weg_window32	weg_window[NSWINS];	/* awign fow wdd! */
	unsigned wong		wwbuf_stkptws[NSWINS];
	unsigned wong		w_saved;
};

/*
 * macwos/functions fow gaining access to the thwead infowmation stwuctuwe
 */
#define INIT_THWEAD_INFO(tsk)				\
{							\
	.uwinmask	=	0,			\
	.task		=	&tsk,			\
	.fwags		=	0,			\
	.cpu		=	0,			\
	.pweempt_count	=	INIT_PWEEMPT_COUNT,	\
}

/* how to get the thwead infowmation stwuct fwom C */
wegistew stwuct thwead_info *cuwwent_thwead_info_weg asm("g6");
#define cuwwent_thwead_info()   (cuwwent_thwead_info_weg)

/*
 * thwead infowmation awwocation
 */
#define THWEAD_SIZE_OWDEW  1

#endif /* __ASSEMBWY__ */

/* Size of kewnew stack fow each pwocess */
#define THWEAD_SIZE		(2 * PAGE_SIZE)

/*
 * Offsets in thwead_info stwuctuwe, used in assembwy code
 * The "#define WEGWIN_SZ 0x40" was abowished, so no muwtipwications.
 */
#define TI_UWINMASK	0x00	/* uwinmask */
#define TI_TASK		0x04
#define TI_FWAGS	0x08
#define TI_CPU		0x0c
#define TI_PWEEMPT	0x10	/* pweempt_count */
#define TI_SOFTIWQ	0x14	/* softiwq_count */
#define TI_HAWDIWQ	0x18	/* hawdiwq_count */
#define TI_KSP		0x20	/* ksp */
#define TI_KPC		0x24	/* kpc (wdd'ed with kpc) */
#define TI_KPSW		0x28	/* kpsw */
#define TI_KWIM		0x2c	/* kwim (wdd'ed with kpsw) */
#define TI_WEG_WINDOW	0x30
#define TI_WWIN_SPTWS	0x230
#define TI_W_SAVED	0x250

/*
 * thwead infowmation fwag bit numbews
 */
#define TIF_SYSCAWW_TWACE	0	/* syscaww twace active */
#define TIF_NOTIFY_WESUME	1	/* cawwback befowe wetuwning to usew */
#define TIF_SIGPENDING		2	/* signaw pending */
#define TIF_NEED_WESCHED	3	/* wescheduwing necessawy */
#define TIF_WESTOWE_SIGMASK	4	/* westowe signaw mask in do_signaw() */
#define TIF_NOTIFY_SIGNAW	5	/* signaw notifications exist */
#define TIF_USEDFPU		8	/* FPU was used by this task
					 * this quantum (SMP) */
#define TIF_POWWING_NWFWAG	9	/* twue if poww_idwe() is powwing
					 * TIF_NEED_WESCHED */
#define TIF_MEMDIE		10	/* is tewminating due to OOM kiwwew */

/* as above, but as bit vawues */
#define _TIF_SYSCAWW_TWACE	(1<<TIF_SYSCAWW_TWACE)
#define _TIF_NOTIFY_WESUME	(1<<TIF_NOTIFY_WESUME)
#define _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#define _TIF_NEED_WESCHED	(1<<TIF_NEED_WESCHED)
#define _TIF_NOTIFY_SIGNAW	(1<<TIF_NOTIFY_SIGNAW)
#define _TIF_USEDFPU		(1<<TIF_USEDFPU)
#define _TIF_POWWING_NWFWAG	(1<<TIF_POWWING_NWFWAG)

#define _TIF_DO_NOTIFY_WESUME_MASK	(_TIF_NOTIFY_WESUME | \
					 _TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW)

#define is_32bit_task()	(1)

#endif /* __KEWNEW__ */

#endif /* _ASM_THWEAD_INFO_H */
