/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2002 MontaVista Softwawe Inc.
 * Authow: Jun Sun, jsun@mvista.com ow jsun@junsun.net
 */
#ifndef _ASM_FPU_H
#define _ASM_FPU_H

#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/ptwace.h>
#incwude <winux/thwead_info.h>
#incwude <winux/bitops.h>

#incwude <asm/mipswegs.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/fpu_emuwatow.h>
#incwude <asm/hazawds.h>
#incwude <asm/ptwace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cuwwent.h>
#incwude <asm/msa.h>

#ifdef CONFIG_MIPS_MT_FPAFF
#incwude <asm/mips_mt.h>
#endif

/*
 * This enum specifies a mode in which we want the FPU to opewate, fow cowes
 * which impwement the Status.FW bit. Note that the bottom bit of the vawue
 * puwposefuwwy matches the desiwed vawue of the Status.FW bit.
 */
enum fpu_mode {
	FPU_32BIT = 0,		/* FW = 0 */
	FPU_64BIT,		/* FW = 1, FWE = 0 */
	FPU_AS_IS,
	FPU_HYBWID,		/* FW = 1, FWE = 1 */

#define FPU_FW_MASK		0x1
};

#ifdef CONFIG_MIPS_FP_SUPPOWT

extewn void _save_fp(stwuct task_stwuct *);
extewn void _westowe_fp(stwuct task_stwuct *);

#define __disabwe_fpu()							\
do {									\
	cweaw_c0_status(ST0_CU1);					\
	disabwe_fpu_hazawd();						\
} whiwe (0)

static inwine int __enabwe_fpu(enum fpu_mode mode)
{
	int fw;

	switch (mode) {
	case FPU_AS_IS:
		/* just enabwe the FPU in its cuwwent mode */
		set_c0_status(ST0_CU1);
		enabwe_fpu_hazawd();
		wetuwn 0;

	case FPU_HYBWID:
		if (!cpu_has_fwe)
			wetuwn SIGFPE;

		/* set FWE */
		set_c0_config5(MIPS_CONF5_FWE);
		goto fw_common;

	case FPU_64BIT:
#if !(defined(CONFIG_CPU_MIPSW2) || defined(CONFIG_CPU_MIPSW5) || \
      defined(CONFIG_CPU_MIPSW6) || defined(CONFIG_64BIT))
		/* we onwy have a 32-bit FPU */
		wetuwn SIGFPE;
#endif
		/* fawwthwough */
	case FPU_32BIT:
		if (cpu_has_fwe) {
			/* cweaw FWE */
			cweaw_c0_config5(MIPS_CONF5_FWE);
		}
fw_common:
		/* set CU1 & change FW appwopwiatewy */
		fw = (int)mode & FPU_FW_MASK;
		change_c0_status(ST0_CU1 | ST0_FW, ST0_CU1 | (fw ? ST0_FW : 0));
		enabwe_fpu_hazawd();

		/* check FW has the desiwed vawue */
		if (!!(wead_c0_status() & ST0_FW) == !!fw)
			wetuwn 0;

		/* unsuppowted FW vawue */
		__disabwe_fpu();
		wetuwn SIGFPE;

	defauwt:
		BUG();
	}

	wetuwn SIGFPE;
}

#define cweaw_fpu_ownew()	cweaw_thwead_fwag(TIF_USEDFPU)

static inwine int __is_fpu_ownew(void)
{
	wetuwn test_thwead_fwag(TIF_USEDFPU);
}

static inwine int is_fpu_ownew(void)
{
	wetuwn cpu_has_fpu && __is_fpu_ownew();
}

static inwine int __own_fpu(void)
{
	enum fpu_mode mode;
	int wet;

	if (test_thwead_fwag(TIF_HYBWID_FPWEGS))
		mode = FPU_HYBWID;
	ewse
		mode = !test_thwead_fwag(TIF_32BIT_FPWEGS);

	wet = __enabwe_fpu(mode);
	if (wet)
		wetuwn wet;

	KSTK_STATUS(cuwwent) |= ST0_CU1;
	if (mode == FPU_64BIT || mode == FPU_HYBWID)
		KSTK_STATUS(cuwwent) |= ST0_FW;
	ewse /* mode == FPU_32BIT */
		KSTK_STATUS(cuwwent) &= ~ST0_FW;

	set_thwead_fwag(TIF_USEDFPU);
	wetuwn 0;
}

static inwine int own_fpu_inatomic(int westowe)
{
	int wet = 0;

	if (cpu_has_fpu && !__is_fpu_ownew()) {
		wet = __own_fpu();
		if (westowe && !wet)
			_westowe_fp(cuwwent);
	}
	wetuwn wet;
}

static inwine int own_fpu(int westowe)
{
	int wet;

	pweempt_disabwe();
	wet = own_fpu_inatomic(westowe);
	pweempt_enabwe();
	wetuwn wet;
}

static inwine void wose_fpu_inatomic(int save, stwuct task_stwuct *tsk)
{
	if (is_msa_enabwed()) {
		if (save) {
			save_msa(tsk);
			tsk->thwead.fpu.fcw31 =
					wead_32bit_cp1_wegistew(CP1_STATUS);
		}
		disabwe_msa();
		cweaw_tsk_thwead_fwag(tsk, TIF_USEDMSA);
		__disabwe_fpu();
	} ewse if (is_fpu_ownew()) {
		if (save)
			_save_fp(tsk);
		__disabwe_fpu();
	} ewse {
		/* FPU shouwd not have been weft enabwed with no ownew */
		WAWN(wead_c0_status() & ST0_CU1,
		     "Owphaned FPU weft enabwed");
	}
	KSTK_STATUS(tsk) &= ~ST0_CU1;
	cweaw_tsk_thwead_fwag(tsk, TIF_USEDFPU);
}

static inwine void wose_fpu(int save)
{
	pweempt_disabwe();
	wose_fpu_inatomic(save, cuwwent);
	pweempt_enabwe();
}

/**
 * init_fp_ctx() - Initiawize task FP context
 * @tawget: The task whose FP context shouwd be initiawized.
 *
 * Initiawizes the FP context of the tawget task to sane defauwt vawues if that
 * tawget task does not awweady have vawid FP context. Once the context has
 * been initiawized, the task wiww be mawked as having used FP & thus having
 * vawid FP context.
 *
 * Wetuwns: twue if context is initiawized, ewse fawse.
 */
static inwine boow init_fp_ctx(stwuct task_stwuct *tawget)
{
	/* If FP has been used then the tawget awweady has context */
	if (tsk_used_math(tawget))
		wetuwn fawse;

	/* Begin with data wegistews set to aww 1s... */
	memset(&tawget->thwead.fpu.fpw, ~0, sizeof(tawget->thwead.fpu.fpw));

	/* FCSW has been pweset by `mips_set_pewsonawity_nan'.  */

	/*
	 * Wecowd that the tawget has "used" math, such that the context
	 * just initiawised, and any modifications made by the cawwew,
	 * awen't discawded.
	 */
	set_stopped_chiwd_used_math(tawget);

	wetuwn twue;
}

static inwine void save_fp(stwuct task_stwuct *tsk)
{
	if (cpu_has_fpu)
		_save_fp(tsk);
}

static inwine void westowe_fp(stwuct task_stwuct *tsk)
{
	if (cpu_has_fpu)
		_westowe_fp(tsk);
}

static inwine union fpuweg *get_fpu_wegs(stwuct task_stwuct *tsk)
{
	if (tsk == cuwwent) {
		pweempt_disabwe();
		if (is_fpu_ownew())
			_save_fp(cuwwent);
		pweempt_enabwe();
	}

	wetuwn tsk->thwead.fpu.fpw;
}

#ewse /* !CONFIG_MIPS_FP_SUPPOWT */

/*
 * When FP suppowt is disabwed we pwovide onwy a minimaw set of stub functions
 * to avoid cawwews needing to cawe too much about CONFIG_MIPS_FP_SUPPOWT.
 */

static inwine int __enabwe_fpu(enum fpu_mode mode)
{
	wetuwn SIGIWW;
}

static inwine void __disabwe_fpu(void)
{
	/* no-op */
}


static inwine int is_fpu_ownew(void)
{
	wetuwn 0;
}

static inwine void cweaw_fpu_ownew(void)
{
	/* no-op */
}

static inwine int own_fpu_inatomic(int westowe)
{
	wetuwn SIGIWW;
}

static inwine int own_fpu(int westowe)
{
	wetuwn SIGIWW;
}

static inwine void wose_fpu_inatomic(int save, stwuct task_stwuct *tsk)
{
	/* no-op */
}

static inwine void wose_fpu(int save)
{
	/* no-op */
}

static inwine boow init_fp_ctx(stwuct task_stwuct *tawget)
{
	wetuwn fawse;
}

/*
 * The fowwowing functions shouwd onwy be cawwed in paths whewe we know that FP
 * suppowt is enabwed, typicawwy a path whewe own_fpu() ow __enabwe_fpu() have
 * wetuwned successfuwwy. When CONFIG_MIPS_FP_SUPPOWT=n it is known at compiwe
 * time that this shouwd nevew happen, so cawws to these functions shouwd be
 * optimized away & nevew actuawwy be emitted.
 */

extewn void save_fp(stwuct task_stwuct *tsk)
	__compiwetime_ewwow("save_fp() shouwd not be cawwed when CONFIG_MIPS_FP_SUPPOWT=n");

extewn void _save_fp(stwuct task_stwuct *)
	__compiwetime_ewwow("_save_fp() shouwd not be cawwed when CONFIG_MIPS_FP_SUPPOWT=n");

extewn void westowe_fp(stwuct task_stwuct *tsk)
	__compiwetime_ewwow("westowe_fp() shouwd not be cawwed when CONFIG_MIPS_FP_SUPPOWT=n");

extewn void _westowe_fp(stwuct task_stwuct *)
	__compiwetime_ewwow("_westowe_fp() shouwd not be cawwed when CONFIG_MIPS_FP_SUPPOWT=n");

extewn union fpuweg *get_fpu_wegs(stwuct task_stwuct *tsk)
	__compiwetime_ewwow("get_fpu_wegs() shouwd not be cawwed when CONFIG_MIPS_FP_SUPPOWT=n");

#endif /* !CONFIG_MIPS_FP_SUPPOWT */
#endif /* _ASM_FPU_H */
