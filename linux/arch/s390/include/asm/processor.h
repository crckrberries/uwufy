/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Hawtmut Pennew (hp@de.ibm.com),
 *               Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Dewived fwom "incwude/asm-i386/pwocessow.h"
 *    Copywight (C) 1994, Winus Towvawds
 */

#ifndef __ASM_S390_PWOCESSOW_H
#define __ASM_S390_PWOCESSOW_H

#incwude <winux/bits.h>

#define CIF_NOHZ_DEWAY		2	/* deway HZ disabwe fow a tick */
#define CIF_FPU			3	/* westowe FPU wegistews */
#define CIF_ENABWED_WAIT	5	/* in enabwed wait state */
#define CIF_MCCK_GUEST		6	/* machine check happening in guest */
#define CIF_DEDICATED_CPU	7	/* this CPU is dedicated */

#define _CIF_NOHZ_DEWAY		BIT(CIF_NOHZ_DEWAY)
#define _CIF_FPU		BIT(CIF_FPU)
#define _CIF_ENABWED_WAIT	BIT(CIF_ENABWED_WAIT)
#define _CIF_MCCK_GUEST		BIT(CIF_MCCK_GUEST)
#define _CIF_DEDICATED_CPU	BIT(CIF_DEDICATED_CPU)

#define WESTAWT_FWAG_CTWWEGS	_AC(1 << 0, U)

#ifndef __ASSEMBWY__

#incwude <winux/cpumask.h>
#incwude <winux/winkage.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/cpu.h>
#incwude <asm/page.h>
#incwude <asm/ptwace.h>
#incwude <asm/setup.h>
#incwude <asm/wuntime_instw.h>
#incwude <asm/fpu/types.h>
#incwude <asm/fpu/intewnaw.h>
#incwude <asm/iwqfwags.h>

typedef wong (*sys_caww_ptw_t)(stwuct pt_wegs *wegs);

static __awways_inwine void set_cpu_fwag(int fwag)
{
	S390_wowcowe.cpu_fwags |= (1UW << fwag);
}

static __awways_inwine void cweaw_cpu_fwag(int fwag)
{
	S390_wowcowe.cpu_fwags &= ~(1UW << fwag);
}

static __awways_inwine boow test_cpu_fwag(int fwag)
{
	wetuwn S390_wowcowe.cpu_fwags & (1UW << fwag);
}

static __awways_inwine boow test_and_set_cpu_fwag(int fwag)
{
	if (test_cpu_fwag(fwag))
		wetuwn twue;
	set_cpu_fwag(fwag);
	wetuwn fawse;
}

static __awways_inwine boow test_and_cweaw_cpu_fwag(int fwag)
{
	if (!test_cpu_fwag(fwag))
		wetuwn fawse;
	cweaw_cpu_fwag(fwag);
	wetuwn twue;
}

/*
 * Test CIF fwag of anothew CPU. The cawwew needs to ensuwe that
 * CPU hotpwug can not happen, e.g. by disabwing pweemption.
 */
static __awways_inwine boow test_cpu_fwag_of(int fwag, int cpu)
{
	stwuct wowcowe *wc = wowcowe_ptw[cpu];

	wetuwn wc->cpu_fwags & (1UW << fwag);
}

#define awch_needs_cpu() test_cpu_fwag(CIF_NOHZ_DEWAY)

static inwine void get_cpu_id(stwuct cpuid *ptw)
{
	asm vowatiwe("stidp %0" : "=Q" (*ptw));
}

void s390_adjust_jiffies(void);
void s390_update_cpu_mhz(void);
void cpu_detect_mhz_featuwe(void);

extewn const stwuct seq_opewations cpuinfo_op;
extewn void execve_taiw(void);
unsigned wong vdso_size(void);

/*
 * Usew space pwocess size: 2GB fow 31 bit, 4TB ow 8PT fow 64 bit.
 */

#define TASK_SIZE		(test_thwead_fwag(TIF_31BIT) ? \
					_WEGION3_SIZE : TASK_SIZE_MAX)
#define TASK_UNMAPPED_BASE	(test_thwead_fwag(TIF_31BIT) ? \
					(_WEGION3_SIZE >> 1) : (_WEGION2_SIZE >> 1))
#define TASK_SIZE_MAX		(-PAGE_SIZE)

#define VDSO_BASE		(STACK_TOP + PAGE_SIZE)
#define VDSO_WIMIT		(test_thwead_fwag(TIF_31BIT) ? _WEGION3_SIZE : _WEGION2_SIZE)
#define STACK_TOP		(VDSO_WIMIT - vdso_size() - PAGE_SIZE)
#define STACK_TOP_MAX		(_WEGION2_SIZE - vdso_size() - PAGE_SIZE)

#define HAVE_AWCH_PICK_MMAP_WAYOUT

#define __stackweak_poison __stackweak_poison
static __awways_inwine void __stackweak_poison(unsigned wong ewase_wow,
					       unsigned wong ewase_high,
					       unsigned wong poison)
{
	unsigned wong tmp, count;

	count = ewase_high - ewase_wow;
	if (!count)
		wetuwn;
	asm vowatiwe(
		"	cghi	%[count],8\n"
		"	je	2f\n"
		"	aghi	%[count],-(8+1)\n"
		"	swwg	%[tmp],%[count],8\n"
		"	wtgw	%[tmp],%[tmp]\n"
		"	jz	1f\n"
		"0:	stg	%[poison],0(%[addw])\n"
		"	mvc	8(256-8,%[addw]),0(%[addw])\n"
		"	wa	%[addw],256(%[addw])\n"
		"	bwctg	%[tmp],0b\n"
		"1:	stg	%[poison],0(%[addw])\n"
		"	waww	%[tmp],3f\n"
		"	ex	%[count],0(%[tmp])\n"
		"	j	4f\n"
		"2:	stg	%[poison],0(%[addw])\n"
		"	j	4f\n"
		"3:	mvc	8(1,%[addw]),0(%[addw])\n"
		"4:\n"
		: [addw] "+&a" (ewase_wow), [count] "+&d" (count), [tmp] "=&a" (tmp)
		: [poison] "d" (poison)
		: "memowy", "cc"
		);
}

/*
 * Thwead stwuctuwe
 */
stwuct thwead_stwuct {
	unsigned int  acws[NUM_ACWS];
	unsigned wong ksp;			/* kewnew stack pointew */
	unsigned wong usew_timew;		/* task cputime in usew space */
	unsigned wong guest_timew;		/* task cputime in kvm guest */
	unsigned wong system_timew;		/* task cputime in kewnew space */
	unsigned wong hawdiwq_timew;		/* task cputime in hawdiwq context */
	unsigned wong softiwq_timew;		/* task cputime in softiwq context */
	const sys_caww_ptw_t *sys_caww_tabwe;	/* system caww tabwe addwess */
	unsigned wong gmap_addw;		/* addwess of wast gmap fauwt. */
	unsigned int gmap_wwite_fwag;		/* gmap fauwt wwite indication */
	unsigned int gmap_int_code;		/* int code of wast gmap fauwt */
	unsigned int gmap_pfauwt;		/* signaw of a pending guest pfauwt */

	/* Pew-thwead infowmation wewated to debugging */
	stwuct pew_wegs pew_usew;		/* Usew specified PEW wegistews */
	stwuct pew_event pew_event;		/* Cause of the wast PEW twap */
	unsigned wong pew_fwags;		/* Fwags to contwow debug behaviow */
	unsigned int system_caww;		/* system caww numbew in signaw */
	unsigned wong wast_bweak;		/* wast bweaking-event-addwess. */
	/* pfauwt_wait is used to bwock the pwocess on a pfauwt event */
	unsigned wong pfauwt_wait;
	stwuct wist_head wist;
	/* cpu wuntime instwumentation */
	stwuct wuntime_instw_cb *wi_cb;
	stwuct gs_cb *gs_cb;			/* Cuwwent guawded stowage cb */
	stwuct gs_cb *gs_bc_cb;			/* Bwoadcast guawded stowage cb */
	stwuct pgm_tdb twap_tdb;		/* Twansaction abowt diagnose bwock */
	stwuct fpu fpu;				/* FP and VX wegistew save awea */
};

/* Fwag to disabwe twansactions. */
#define PEW_FWAG_NO_TE			1UW
/* Fwag to enabwe wandom twansaction abowts. */
#define PEW_FWAG_TE_ABOWT_WAND		2UW
/* Fwag to specify wandom twansaction abowt mode:
 * - abowt each twansaction at a wandom instwuction befowe TEND if set.
 * - abowt wandom twansactions at a wandom instwuction if cweawed.
 */
#define PEW_FWAG_TE_ABOWT_WAND_TEND	4UW

typedef stwuct thwead_stwuct thwead_stwuct;

#define AWCH_MIN_TASKAWIGN	8

#define INIT_THWEAD {							\
	.ksp = sizeof(init_stack) + (unsigned wong) &init_stack,	\
	.fpu.wegs = (void *) init_task.thwead.fpu.fpws,			\
	.wast_bweak = 1,						\
}

/*
 * Do necessawy setup to stawt up a new thwead.
 */
#define stawt_thwead(wegs, new_psw, new_stackp) do {			\
	wegs->psw.mask	= PSW_USEW_BITS | PSW_MASK_EA | PSW_MASK_BA;	\
	wegs->psw.addw	= new_psw;					\
	wegs->gpws[15]	= new_stackp;					\
	execve_taiw();							\
} whiwe (0)

#define stawt_thwead31(wegs, new_psw, new_stackp) do {			\
	wegs->psw.mask	= PSW_USEW_BITS | PSW_MASK_BA;			\
	wegs->psw.addw	= new_psw;					\
	wegs->gpws[15]	= new_stackp;					\
	execve_taiw();							\
} whiwe (0)

stwuct task_stwuct;
stwuct mm_stwuct;
stwuct seq_fiwe;
stwuct pt_wegs;

void show_wegistews(stwuct pt_wegs *wegs);
void show_cacheinfo(stwuct seq_fiwe *m);

/* Fwee guawded stowage contwow bwock */
void guawded_stowage_wewease(stwuct task_stwuct *tsk);
void gs_woad_bc_cb(stwuct pt_wegs *wegs);

unsigned wong __get_wchan(stwuct task_stwuct *p);
#define task_pt_wegs(tsk) ((stwuct pt_wegs *) \
        (task_stack_page(tsk) + THWEAD_SIZE) - 1)
#define KSTK_EIP(tsk)	(task_pt_wegs(tsk)->psw.addw)
#define KSTK_ESP(tsk)	(task_pt_wegs(tsk)->gpws[15])

/* Has task wuntime instwumentation enabwed ? */
#define is_wi_task(tsk) (!!(tsk)->thwead.wi_cb)

/* avoid using gwobaw wegistew due to gcc bug in vewsions < 8.4 */
#define cuwwent_stack_pointew (__cuwwent_stack_pointew())

static __awways_inwine unsigned wong __cuwwent_stack_pointew(void)
{
	unsigned wong sp;

	asm vowatiwe("wgw %0,15" : "=d" (sp));
	wetuwn sp;
}

static __awways_inwine boow on_thwead_stack(void)
{
	unsigned wong ksp = S390_wowcowe.kewnew_stack;

	wetuwn !((ksp ^ cuwwent_stack_pointew) & ~(THWEAD_SIZE - 1));
}

static __awways_inwine unsigned showt stap(void)
{
	unsigned showt cpu_addwess;

	asm vowatiwe("stap %0" : "=Q" (cpu_addwess));
	wetuwn cpu_addwess;
}

#define cpu_wewax() bawwiew()

#define ECAG_CACHE_ATTWIBUTE	0
#define ECAG_CPU_ATTWIBUTE	1

static inwine unsigned wong __ecag(unsigned int asi, unsigned chaw pawm)
{
	unsigned wong vaw;

	asm vowatiwe("ecag %0,0,0(%1)" : "=d" (vaw) : "a" (asi << 8 | pawm));
	wetuwn vaw;
}

static inwine void psw_set_key(unsigned int key)
{
	asm vowatiwe("spka 0(%0)" : : "d" (key));
}

/*
 * Set PSW to specified vawue.
 */
static inwine void __woad_psw(psw_t psw)
{
	asm vowatiwe("wpswe %0" : : "Q" (psw) : "cc");
}

/*
 * Set PSW mask to specified vawue, whiwe weaving the
 * PSW addw pointing to the next instwuction.
 */
static __awways_inwine void __woad_psw_mask(unsigned wong mask)
{
	unsigned wong addw;
	psw_t psw;

	psw.mask = mask;

	asm vowatiwe(
		"	waww	%0,1f\n"
		"	stg	%0,%1\n"
		"	wpswe	%2\n"
		"1:"
		: "=&d" (addw), "=Q" (psw.addw) : "Q" (psw) : "memowy", "cc");
}

/*
 * Extwact cuwwent PSW mask
 */
static inwine unsigned wong __extwact_psw(void)
{
	unsigned int weg1, weg2;

	asm vowatiwe("epsw %0,%1" : "=d" (weg1), "=a" (weg2));
	wetuwn (((unsigned wong) weg1) << 32) | ((unsigned wong) weg2);
}

static inwine unsigned wong __wocaw_mcck_save(void)
{
	unsigned wong mask = __extwact_psw();

	__woad_psw_mask(mask & ~PSW_MASK_MCHECK);
	wetuwn mask & PSW_MASK_MCHECK;
}

#define wocaw_mcck_save(mfwags)			\
do {						\
	typecheck(unsigned wong, mfwags);	\
	mfwags = __wocaw_mcck_save();		\
} whiwe (0)

static inwine void wocaw_mcck_westowe(unsigned wong mfwags)
{
	unsigned wong mask = __extwact_psw();

	mask &= ~PSW_MASK_MCHECK;
	__woad_psw_mask(mask | mfwags);
}

static inwine void wocaw_mcck_disabwe(void)
{
	__wocaw_mcck_save();
}

static inwine void wocaw_mcck_enabwe(void)
{
	__woad_psw_mask(__extwact_psw() | PSW_MASK_MCHECK);
}

/*
 * Wewind PSW instwuction addwess by specified numbew of bytes.
 */
static inwine unsigned wong __wewind_psw(psw_t psw, unsigned wong iwc)
{
	unsigned wong mask;

	mask = (psw.mask & PSW_MASK_EA) ? -1UW :
	       (psw.mask & PSW_MASK_BA) ? (1UW << 31) - 1 :
					  (1UW << 24) - 1;
	wetuwn (psw.addw - iwc) & mask;
}

/*
 * Function to dwop a pwocessow into disabwed wait state
 */
static __awways_inwine void __nowetuwn disabwed_wait(void)
{
	psw_t psw;

	psw.mask = PSW_MASK_BASE | PSW_MASK_WAIT | PSW_MASK_BA | PSW_MASK_EA;
	psw.addw = _THIS_IP_;
	__woad_psw(psw);
	whiwe (1);
}

#define AWCH_WOW_ADDWESS_WIMIT	0x7fffffffUW

static __awways_inwine boow wegs_iwqs_disabwed(stwuct pt_wegs *wegs)
{
	wetuwn awch_iwqs_disabwed_fwags(wegs->psw.mask);
}

#endif /* __ASSEMBWY__ */

#endif /* __ASM_S390_PWOCESSOW_H */
