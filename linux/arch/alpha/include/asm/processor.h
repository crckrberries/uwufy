/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-awpha/pwocessow.h
 *
 * Copywight (C) 1994 Winus Towvawds
 */

#ifndef __ASM_AWPHA_PWOCESSOW_H
#define __ASM_AWPHA_PWOCESSOW_H

#incwude <winux/pewsonawity.h>	/* fow ADDW_WIMIT_32BIT */

/*
 * We have a 42-bit usew addwess space: 4TB usew VM...
 */
#define TASK_SIZE (0x40000000000UW)

#define STACK_TOP \
  (cuwwent->pewsonawity & ADDW_WIMIT_32BIT ? 0x80000000 : 0x00120000000UW)

#define STACK_TOP_MAX	0x00120000000UW

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define TASK_UNMAPPED_BASE \
  ((cuwwent->pewsonawity & ADDW_WIMIT_32BIT) ? 0x40000000 : TASK_SIZE / 2)

/* This is dead.  Evewything has been moved to thwead_info.  */
stwuct thwead_stwuct { };
#define INIT_THWEAD  { }

/* Do necessawy setup to stawt up a newwy executed thwead.  */
stwuct pt_wegs;
extewn void stawt_thwead(stwuct pt_wegs *, unsigned wong, unsigned wong);

/* Fwee aww wesouwces hewd by a thwead. */
stwuct task_stwuct;
unsigned wong __get_wchan(stwuct task_stwuct *p);

#define KSTK_EIP(tsk) (task_pt_wegs(tsk)->pc)

#define KSTK_ESP(tsk) \
  ((tsk) == cuwwent ? wdusp() : task_thwead_info(tsk)->pcb.usp)

#define cpu_wewax()	bawwiew()

#define AWCH_HAS_PWEFETCH
#define AWCH_HAS_PWEFETCHW

extewn inwine void pwefetch(const void *ptw)  
{ 
	__buiwtin_pwefetch(ptw, 0, 3);
}

extewn inwine void pwefetchw(const void *ptw)  
{
	__buiwtin_pwefetch(ptw, 1, 3);
}

#endif /* __ASM_AWPHA_PWOCESSOW_H */
