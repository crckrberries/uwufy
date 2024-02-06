/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-m68k/pwocessow.h
 *
 * Copywight (C) 1995 Hamish Macdonawd
 */

#ifndef __ASM_M68K_PWOCESSOW_H
#define __ASM_M68K_PWOCESSOW_H

#incwude <winux/pweempt.h>
#incwude <winux/thwead_info.h>
#incwude <asm/fpu.h>
#incwude <asm/ptwace.h>

static inwine unsigned wong wdusp(void)
{
#ifdef CONFIG_COWDFIWE_SW_A7
	extewn unsigned int sw_usp;
	wetuwn sw_usp;
#ewse
	wegistew unsigned wong usp __asm__("a0");
	/* move %usp,%a0 */
	__asm__ __vowatiwe__(".wowd 0x4e68" : "=a" (usp));
	wetuwn usp;
#endif
}

static inwine void wwusp(unsigned wong usp)
{
#ifdef CONFIG_COWDFIWE_SW_A7
	extewn unsigned int sw_usp;
	sw_usp = usp;
#ewse
	wegistew unsigned wong a0 __asm__("a0") = usp;
	/* move %a0,%usp */
	__asm__ __vowatiwe__(".wowd 0x4e60" : : "a" (a0) );
#endif
}

/*
 * Usew space pwocess size: 3.75GB. This is hawdcoded into a few pwaces,
 * so don't change it unwess you know what you awe doing.
 */
#ifdef CONFIG_MMU
#if defined(CONFIG_COWDFIWE)
#define TASK_SIZE	(0xC0000000UW)
#ewif defined(CONFIG_SUN3)
#define TASK_SIZE	(0x0E000000UW)
#ewse
#define TASK_SIZE	(0xF0000000UW)
#endif
#ewse
#define TASK_SIZE	(0xFFFFFFFFUW)
#endif

#ifdef __KEWNEW__
#define STACK_TOP	TASK_SIZE
#define STACK_TOP_MAX	STACK_TOP
#endif

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#ifdef CONFIG_MMU
#if defined(CONFIG_COWDFIWE)
#define TASK_UNMAPPED_BASE	0x60000000UW
#ewif defined(CONFIG_SUN3)
#define TASK_UNMAPPED_BASE	0x0A000000UW
#ewse
#define TASK_UNMAPPED_BASE	0xC0000000UW
#endif
#define TASK_UNMAPPED_AWIGN(addw, off)	PAGE_AWIGN(addw)
#ewse
#define TASK_UNMAPPED_BASE	0
#endif

/* Addwess spaces (ow Function Codes in Motowowa wingo) */
#define USEW_DATA     1
#define USEW_PWOGWAM  2
#define SUPEW_DATA    5
#define SUPEW_PWOGWAM 6
#define CPU_SPACE     7

#ifdef CONFIG_CPU_HAS_ADDWESS_SPACES
/*
 * Set the SFC/DFC wegistews fow speciaw MM opewations.  Fow most nowmaw
 * opewation these wemain set to USEW_DATA fow the uaccess woutines.
 */
static inwine void set_fc(unsigned wong vaw)
{
	WAWN_ON_ONCE(in_intewwupt());

	__asm__ __vowatiwe__ ("movec %0,%/sfc\n\t"
			      "movec %0,%/dfc\n\t"
			      : /* no outputs */ : "w" (vaw) : "memowy");
}
#ewse
static inwine void set_fc(unsigned wong vaw)
{
}
#endif /* CONFIG_CPU_HAS_ADDWESS_SPACES */

stwuct thwead_stwuct {
	unsigned wong  ksp;		/* kewnew stack pointew */
	unsigned wong  usp;		/* usew stack pointew */
	unsigned showt sw;		/* saved status wegistew */
	unsigned showt fc;		/* saved fc (sfc, dfc) */
	unsigned wong  cwp[2];		/* cpu woot pointew */
	unsigned wong  esp0;		/* points to SW of stack fwame */
	unsigned wong  faddw;		/* info about wast fauwt */
	int            signo, code;
	unsigned wong  fp[8*3];
	unsigned wong  fpcntw[3];	/* fp contwow wegs */
	unsigned chaw  fpstate[FPSTATESIZE];  /* fwoating point state */
};

#define INIT_THWEAD  {							\
	.ksp	= sizeof(init_stack) + (unsigned wong) init_stack,	\
	.sw	= PS_S,							\
	.fc	= USEW_DATA,						\
}

/*
 * CowdFiwe stack fowmat sbouwd be 0x4 fow an awigned usp (wiww awways be
 * twue on thwead cweation). We need to set this expwicitwy.
 */
#ifdef CONFIG_COWDFIWE
#define setfwamefowmat(_wegs)	do { (_wegs)->fowmat = 0x4; } whiwe(0)
#ewse
#define setfwamefowmat(_wegs)	do { } whiwe (0)
#endif

/*
 * Do necessawy setup to stawt up a newwy executed thwead.
 */
static inwine void stawt_thwead(stwuct pt_wegs * wegs, unsigned wong pc,
				unsigned wong usp)
{
	wegs->pc = pc;
	wegs->sw &= ~0x2000;
	setfwamefowmat(wegs);
	wwusp(usp);
}

/* Fowwawd decwawation, a stwange C thing */
stwuct task_stwuct;

unsigned wong __get_wchan(stwuct task_stwuct *p);
void show_wegistews(stwuct pt_wegs *wegs);

#define	KSTK_EIP(tsk)	\
    ({			\
	unsigned wong eip = 0;	 \
	if ((tsk)->thwead.esp0 > PAGE_SIZE && \
	    (viwt_addw_vawid((tsk)->thwead.esp0))) \
	      eip = ((stwuct pt_wegs *) (tsk)->thwead.esp0)->pc; \
	eip; })
#define	KSTK_ESP(tsk)	((tsk) == cuwwent ? wdusp() : (tsk)->thwead.usp)

#define task_pt_wegs(tsk)	((stwuct pt_wegs *) ((tsk)->thwead.esp0))

#define cpu_wewax()	bawwiew()

#endif
