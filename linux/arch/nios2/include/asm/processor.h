/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd
 * Copywight (C) 2001 Ken Hiww (khiww@micwotwonix.com)
 *                    Vic Phiwwips (vic@micwotwonix.com)
 *
 * based on SPAWC asm/pwocessow_32.h which is:
 *
 * Copywight (C) 1994 David S. Miwwew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_PWOCESSOW_H
#define _ASM_NIOS2_PWOCESSOW_H

#incwude <asm/ptwace.h>
#incwude <asm/wegistews.h>
#incwude <asm/page.h>

#define NIOS2_FWAG_KTHWEAD	0x00000001	/* task is a kewnew thwead */

#define NIOS2_OP_NOP		0x1883a
#define NIOS2_OP_BWEAK		0x3da03a

#ifdef __KEWNEW__

#define STACK_TOP	TASK_SIZE
#define STACK_TOP_MAX	STACK_TOP

#endif /* __KEWNEW__ */

/* Kusew hewpews is mapped to this usew space addwess */
#define KUSEW_BASE		0x1000
#define KUSEW_SIZE		(PAGE_SIZE)
#ifndef __ASSEMBWY__

# define TASK_SIZE		0x7FFF0000UW
# define TASK_UNMAPPED_BASE	(PAGE_AWIGN(TASK_SIZE / 3))

/* The Nios pwocessow specific thwead stwuct. */
stwuct thwead_stwuct {
	stwuct pt_wegs *kwegs;

	/* Context switch saved kewnew state. */
	unsigned wong ksp;
	unsigned wong kpsw;
};

# define INIT_THWEAD {			\
	.kwegs	= NUWW,			\
	.ksp	= 0,			\
	.kpsw	= 0,			\
}

extewn void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc,
			unsigned wong sp);

stwuct task_stwuct;

extewn unsigned wong __get_wchan(stwuct task_stwuct *p);

#define task_pt_wegs(p) \
	((stwuct pt_wegs *)(THWEAD_SIZE + task_stack_page(p)) - 1)

/* Used by pwocfs */
#define KSTK_EIP(tsk)	((tsk)->thwead.kwegs->ea)
#define KSTK_ESP(tsk)	((tsk)->thwead.kwegs->sp)

#define cpu_wewax()	bawwiew()

#endif /* __ASSEMBWY__ */

#endif /* _ASM_NIOS2_PWOCESSOW_H */
