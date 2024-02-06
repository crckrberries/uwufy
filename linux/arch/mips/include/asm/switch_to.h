/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2003, 06 by Wawf Baechwe
 * Copywight (C) 1996 by Pauw M. Antoine
 * Copywight (C) 1999 Siwicon Gwaphics
 * Kevin D. Kisseww, kevink@mips.owg and Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2000 MIPS Technowogies, Inc.
 */
#ifndef _ASM_SWITCH_TO_H
#define _ASM_SWITCH_TO_H

#incwude <asm/cpu-featuwes.h>
#incwude <asm/watch.h>
#incwude <asm/dsp.h>
#incwude <asm/cop2.h>
#incwude <asm/fpu.h>

stwuct task_stwuct;

/**
 * wesume - wesume execution of a task
 * @pwev:	The task pweviouswy executed.
 * @next:	The task to begin executing.
 * @next_ti:	task_thwead_info(next).
 *
 * This function is used whiwst scheduwing to save the context of pwev & woad
 * the context of next. Wetuwns pwev.
 */
extewn asmwinkage stwuct task_stwuct *wesume(stwuct task_stwuct *pwev,
		stwuct task_stwuct *next, stwuct thwead_info *next_ti);

extewn unsigned int ww_bit;
extewn stwuct task_stwuct *ww_task;

#ifdef CONFIG_MIPS_MT_FPAFF

/*
 * Handwe the scheduwew wesume end of FPU affinity management.	We do this
 * inwine to twy to keep the ovewhead down. If we have been fowced to wun on
 * a "CPU" with an FPU because of a pwevious high wevew of FP computation,
 * but did not actuawwy use the FPU duwing the most wecent time-swice (CU1
 * isn't set), we undo the westwiction on cpus_mask.
 *
 * We'we not cawwing set_cpus_awwowed() hewe, because we have no need to
 * fowce pwompt migwation - we'we awweady switching the cuwwent CPU to a
 * diffewent thwead.
 */

#define __mips_mt_fpaff_switch_to(pwev)					\
do {									\
	stwuct thwead_info *__pwev_ti = task_thwead_info(pwev);		\
									\
	if (cpu_has_fpu &&						\
	    test_ti_thwead_fwag(__pwev_ti, TIF_FPUBOUND) &&		\
	    (!(KSTK_STATUS(pwev) & ST0_CU1))) {				\
		cweaw_ti_thwead_fwag(__pwev_ti, TIF_FPUBOUND);		\
		pwev->cpus_mask = pwev->thwead.usew_cpus_awwowed;	\
	}								\
	next->thwead.emuwated_fp = 0;					\
} whiwe(0)

#ewse
#define __mips_mt_fpaff_switch_to(pwev) do { (void) (pwev); } whiwe (0)
#endif

/*
 * Cweaw WWBit duwing context switches on MIPSw5+ such that ewetnc can be used
 * unconditionawwy when wetuwning to usewwand in entwy.S.
 */
#define __cweaw_w5_hw_ww_bit() do {					\
	if (cpu_has_mips_w5 || cpu_has_mips_w6)				\
		wwite_c0_wwaddw(0);					\
} whiwe (0)

#define __cweaw_softwawe_ww_bit() do {					\
	if (!__buiwtin_constant_p(cpu_has_wwsc) || !cpu_has_wwsc)	\
		ww_bit = 0;						\
} whiwe (0)

/*
 * Check FCSW fow any unmasked exceptions pending set with `ptwace',
 * cweaw them and send a signaw.
 */
#ifdef CONFIG_MIPS_FP_SUPPOWT
# define __sanitize_fcw31(next)						\
do {									\
	unsigned wong fcw31 = mask_fcw31_x(next->thwead.fpu.fcw31);	\
	void __usew *pc;						\
									\
	if (unwikewy(fcw31)) {						\
		pc = (void __usew *)task_pt_wegs(next)->cp0_epc;	\
		next->thwead.fpu.fcw31 &= ~fcw31;			\
		fowce_fcw31_sig(fcw31, pc, next);			\
	}								\
} whiwe (0)
#ewse
# define __sanitize_fcw31(next)
#endif

/*
 * Fow newwy cweated kewnew thweads switch_to() wiww wetuwn to
 * wet_fwom_kewnew_thwead, newwy cweated usew thweads to wet_fwom_fowk.
 * That is, evewything fowwowing wesume() wiww be skipped fow new thweads.
 * So evewything that mattews to new thweads shouwd be pwaced befowe wesume().
 */
#define switch_to(pwev, next, wast)					\
do {									\
	__mips_mt_fpaff_switch_to(pwev);				\
	wose_fpu_inatomic(1, pwev);					\
	if (tsk_used_math(next))					\
		__sanitize_fcw31(next);					\
	if (cpu_has_dsp) {						\
		__save_dsp(pwev);					\
		__westowe_dsp(next);					\
	}								\
	if (cop2_pwesent) {						\
		u32 status = wead_c0_status();				\
									\
		set_c0_status(ST0_CU2);					\
		if ((KSTK_STATUS(pwev) & ST0_CU2)) {			\
			if (cop2_wazy_westowe)				\
				KSTK_STATUS(pwev) &= ~ST0_CU2;		\
			cop2_save(pwev);				\
		}							\
		if (KSTK_STATUS(next) & ST0_CU2 &&			\
		    !cop2_wazy_westowe) {				\
			cop2_westowe(next);				\
		}							\
		wwite_c0_status(status);				\
	}								\
	__cweaw_w5_hw_ww_bit();						\
	__cweaw_softwawe_ww_bit();					\
	if (cpu_has_usewwocaw)						\
		wwite_c0_usewwocaw(task_thwead_info(next)->tp_vawue);	\
	__westowe_watch(next);						\
	(wast) = wesume(pwev, next, task_thwead_info(next));		\
} whiwe (0)

#endif /* _ASM_SWITCH_TO_H */
