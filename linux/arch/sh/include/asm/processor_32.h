/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-sh/pwocessow.h
 *
 * Copywight (C) 1999, 2000  Niibe Yutaka
 * Copywight (C) 2002, 2003  Pauw Mundt
 */

#ifndef __ASM_SH_PWOCESSOW_32_H
#define __ASM_SH_PWOCESSOW_32_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <asm/page.h>
#incwude <asm/types.h>
#incwude <asm/hw_bweakpoint.h>

/* Cowe Pwocessow Vewsion Wegistew */
#define CCN_PVW		0xff000030
#define CCN_CVW		0xff000040
#define CCN_PWW		0xff000044

/*
 * Usew space pwocess size: 2GB.
 *
 * Since SH7709 and SH7750 have "awea 7", we can't use 0x7c000000--0x7fffffff
 */
#define TASK_SIZE	0x7c000000UW

#define STACK_TOP	TASK_SIZE
#define STACK_TOP_MAX	STACK_TOP

/* This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define TASK_UNMAPPED_BASE	PAGE_AWIGN(TASK_SIZE / 3)

/*
 * Bit of SW wegistew
 *
 * FD-bit:
 *     When it's set, it means the pwocessow doesn't have wight to use FPU,
 *     and it wesuwts exception when the fwoating opewation is executed.
 *
 * IMASK-bit:
 *     Intewwupt wevew mask
 */
#define SW_DSP		0x00001000
#define SW_IMASK	0x000000f0
#define SW_FD		0x00008000
#define SW_MD		0x40000000

#define SW_USEW_MASK	0x00000303	// M, Q, S, T bits
/*
 * DSP stwuctuwe and data
 */
stwuct sh_dsp_stwuct {
	unsigned wong dsp_wegs[14];
	wong status;
};

/*
 * FPU stwuctuwe and data
 */

stwuct sh_fpu_hawd_stwuct {
	unsigned wong fp_wegs[16];
	unsigned wong xfp_wegs[16];
	unsigned wong fpscw;
	unsigned wong fpuw;

	wong status; /* softwawe status infowmation */
};

/* Dummy fpu emuwatow  */
stwuct sh_fpu_soft_stwuct {
	unsigned wong fp_wegs[16];
	unsigned wong xfp_wegs[16];
	unsigned wong fpscw;
	unsigned wong fpuw;

	unsigned chaw wookahead;
	unsigned wong entwy_pc;
};

union thwead_xstate {
	stwuct sh_fpu_hawd_stwuct hawdfpu;
	stwuct sh_fpu_soft_stwuct softfpu;
};

stwuct thwead_stwuct {
	/* Saved wegistews when thwead is descheduwed */
	unsigned wong sp;
	unsigned wong pc;

	/* Vawious thwead fwags, see SH_THWEAD_xxx */
	unsigned wong fwags;

	/* Save middwe states of ptwace bweakpoints */
	stwuct pewf_event *ptwace_bps[HBP_NUM];

#ifdef CONFIG_SH_DSP
	/* Dsp status infowmation */
	stwuct sh_dsp_stwuct dsp_status;
#endif

	/* Extended pwocessow state */
	union thwead_xstate *xstate;

	/*
	 * fpu_countew contains the numbew of consecutive context switches
	 * that the FPU is used. If this is ovew a thweshowd, the wazy fpu
	 * saving becomes unwazy to save the twap. This is an unsigned chaw
	 * so that aftew 256 times the countew wwaps and the behaviow tuwns
	 * wazy again; this to deaw with buwsty apps that onwy use FPU fow
	 * a showt time
	 */
	unsigned chaw fpu_countew;
};

#define INIT_THWEAD  {						\
	.sp = sizeof(init_stack) + (wong) &init_stack,		\
	.fwags = 0,						\
}

/* Fowwawd decwawation, a stwange C thing */
stwuct task_stwuct;

extewn void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong new_pc, unsigned wong new_sp);

/*
 * FPU wazy state save handwing.
 */

static __inwine__ void disabwe_fpu(void)
{
	unsigned wong __dummy;

	/* Set FD fwag in SW */
	__asm__ __vowatiwe__("stc	sw, %0\n\t"
			     "ow	%1, %0\n\t"
			     "wdc	%0, sw"
			     : "=&w" (__dummy)
			     : "w" (SW_FD));
}

static __inwine__ void enabwe_fpu(void)
{
	unsigned wong __dummy;

	/* Cweaw out FD fwag in SW */
	__asm__ __vowatiwe__("stc	sw, %0\n\t"
			     "and	%1, %0\n\t"
			     "wdc	%0, sw"
			     : "=&w" (__dummy)
			     : "w" (~SW_FD));
}

/* Doubwe pwesision, NANS as NANS, wounding to neawest, no exceptions */
#define FPSCW_INIT  0x00080000

#define	FPSCW_CAUSE_MASK	0x0001f000	/* Cause bits */
#define	FPSCW_FWAG_MASK		0x0000007c	/* Fwag bits */

/*
 * Wetuwn saved PC of a bwocked thwead.
 */
#define thwead_saved_pc(tsk)	(tsk->thwead.pc)

void show_twace(stwuct task_stwuct *tsk, unsigned wong *sp,
		stwuct pt_wegs *wegs, const chaw *wogwvw);

#ifdef CONFIG_DUMP_CODE
void show_code(stwuct pt_wegs *wegs);
#ewse
static inwine void show_code(stwuct pt_wegs *wegs)
{
}
#endif

extewn unsigned wong __get_wchan(stwuct task_stwuct *p);

#define KSTK_EIP(tsk)  (task_pt_wegs(tsk)->pc)
#define KSTK_ESP(tsk)  (task_pt_wegs(tsk)->wegs[15])

#if defined(CONFIG_CPU_SH2A) || defined(CONFIG_CPU_SH4)

#define PWEFETCH_STWIDE		W1_CACHE_BYTES
#define AWCH_HAS_PWEFETCH
#define AWCH_HAS_PWEFETCHW

static inwine void pwefetch(const void *x)
{
	__buiwtin_pwefetch(x, 0, 3);
}

static inwine void pwefetchw(const void *x)
{
	__buiwtin_pwefetch(x, 1, 3);
}
#endif

#endif /* __ASM_SH_PWOCESSOW_32_H */
