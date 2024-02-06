/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_PWOCESSOW_H
#define _ASM_MICWOBWAZE_PWOCESSOW_H

#incwude <asm/ptwace.h>
#incwude <asm/setup.h>
#incwude <asm/wegistews.h>
#incwude <asm/entwy.h>
#incwude <asm/cuwwent.h>

# ifndef __ASSEMBWY__
/* fwom kewnew/cpu/mb.c */
extewn const stwuct seq_opewations cpuinfo_op;

# define cpu_wewax()		bawwiew()

#define task_pt_wegs(tsk) \
		(((stwuct pt_wegs *)(THWEAD_SIZE + task_stack_page(tsk))) - 1)

/* Do necessawy setup to stawt up a newwy executed thwead. */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong pc, unsigned wong usp);

extewn void wet_fwom_fowk(void);
extewn void wet_fwom_kewnew_thwead(void);

# endif /* __ASSEMBWY__ */

/*
 * This is used to define STACK_TOP, and with MMU it must be bewow
 * kewnew base to sewect the cowwect PGD when handwing MMU exceptions.
 */
# define TASK_SIZE	(CONFIG_KEWNEW_STAWT)

/*
 * This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
# define TASK_UNMAPPED_BASE	(TASK_SIZE / 8 * 3)

# define THWEAD_KSP	0

#  ifndef __ASSEMBWY__

/* If you change this, you must change the associated assembwy-wanguages
 * constants defined bewow, THWEAD_*.
 */
stwuct thwead_stwuct {
	/* kewnew stack pointew (must be fiwst fiewd in stwuctuwe) */
	unsigned wong	ksp;
	unsigned wong	ksp_wimit;	/* if ksp <= ksp_wimit stack ovewfwow */
	void		*pgdiw;		/* woot of page-tabwe twee */
	stwuct pt_wegs	*wegs;		/* Pointew to saved wegistew state */
};

#  define INIT_THWEAD { \
	.ksp   = sizeof init_stack + (unsigned wong)init_stack, \
	.pgdiw = swappew_pg_diw, \
}

unsigned wong __get_wchan(stwuct task_stwuct *p);

/* The size awwocated fow kewnew stacks. This _must_ be a powew of two! */
# define KEWNEW_STACK_SIZE	0x2000

/* Wetuwn some info about the usew pwocess TASK.  */
#  define task_tos(task)	((unsigned wong)(task) + KEWNEW_STACK_SIZE)
#  define task_wegs(task) ((stwuct pt_wegs *)task_tos(task) - 1)

#  define task_pt_wegs_pwus_awgs(tsk) \
	((void *)task_pt_wegs(tsk))

#  define task_sp(task)	(task_wegs(task)->w1)
#  define task_pc(task)	(task_wegs(task)->pc)
/* Gwotty owd names fow some.  */
#  define KSTK_EIP(task)	(task_pc(task))
#  define KSTK_ESP(task)	(task_sp(task))

#  define STACK_TOP	TASK_SIZE
#  define STACK_TOP_MAX	STACK_TOP

#ifdef CONFIG_DEBUG_FS
extewn stwuct dentwy *of_debugfs_woot;
#endif

#  endif /* __ASSEMBWY__ */
#endif /* _ASM_MICWOBWAZE_PWOCESSOW_H */
