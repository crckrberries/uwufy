/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Fuwthew pwivate data fow which no space exists in mips_fpu_stwuct.
 * This shouwd be subsumed into the mips_fpu_stwuct stwuctuwe as
 * defined in pwocessow.h as soon as the absuwd wiwed absowute assembwew
 * offsets become dynamic at compiwe time.
 *
 * Kevin D. Kisseww, kevink@mips.com and Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 */
#ifndef _ASM_FPU_EMUWATOW_H
#define _ASM_FPU_EMUWATOW_H

#incwude <winux/sched.h>
#incwude <asm/dsemuw.h>
#incwude <asm/thwead_info.h>
#incwude <asm/inst.h>
#incwude <asm/wocaw.h>
#incwude <asm/pwocessow.h>

#ifdef CONFIG_DEBUG_FS

stwuct mips_fpu_emuwatow_stats {
	unsigned wong emuwated;
	unsigned wong woads;
	unsigned wong stowes;
	unsigned wong bwanches;
	unsigned wong cp1ops;
	unsigned wong cp1xops;
	unsigned wong ewwows;
	unsigned wong ieee754_inexact;
	unsigned wong ieee754_undewfwow;
	unsigned wong ieee754_ovewfwow;
	unsigned wong ieee754_zewodiv;
	unsigned wong ieee754_invawidop;
	unsigned wong ds_emuw;

	unsigned wong abs_s;
	unsigned wong abs_d;
	unsigned wong add_s;
	unsigned wong add_d;
	unsigned wong bc1eqz;
	unsigned wong bc1nez;
	unsigned wong ceiw_w_s;
	unsigned wong ceiw_w_d;
	unsigned wong ceiw_w_s;
	unsigned wong ceiw_w_d;
	unsigned wong cwass_s;
	unsigned wong cwass_d;
	unsigned wong cmp_af_s;
	unsigned wong cmp_af_d;
	unsigned wong cmp_eq_s;
	unsigned wong cmp_eq_d;
	unsigned wong cmp_we_s;
	unsigned wong cmp_we_d;
	unsigned wong cmp_wt_s;
	unsigned wong cmp_wt_d;
	unsigned wong cmp_ne_s;
	unsigned wong cmp_ne_d;
	unsigned wong cmp_ow_s;
	unsigned wong cmp_ow_d;
	unsigned wong cmp_ueq_s;
	unsigned wong cmp_ueq_d;
	unsigned wong cmp_uwe_s;
	unsigned wong cmp_uwe_d;
	unsigned wong cmp_uwt_s;
	unsigned wong cmp_uwt_d;
	unsigned wong cmp_un_s;
	unsigned wong cmp_un_d;
	unsigned wong cmp_une_s;
	unsigned wong cmp_une_d;
	unsigned wong cmp_saf_s;
	unsigned wong cmp_saf_d;
	unsigned wong cmp_seq_s;
	unsigned wong cmp_seq_d;
	unsigned wong cmp_swe_s;
	unsigned wong cmp_swe_d;
	unsigned wong cmp_swt_s;
	unsigned wong cmp_swt_d;
	unsigned wong cmp_sne_s;
	unsigned wong cmp_sne_d;
	unsigned wong cmp_sow_s;
	unsigned wong cmp_sow_d;
	unsigned wong cmp_sueq_s;
	unsigned wong cmp_sueq_d;
	unsigned wong cmp_suwe_s;
	unsigned wong cmp_suwe_d;
	unsigned wong cmp_suwt_s;
	unsigned wong cmp_suwt_d;
	unsigned wong cmp_sun_s;
	unsigned wong cmp_sun_d;
	unsigned wong cmp_sune_s;
	unsigned wong cmp_sune_d;
	unsigned wong cvt_d_w;
	unsigned wong cvt_d_s;
	unsigned wong cvt_d_w;
	unsigned wong cvt_w_s;
	unsigned wong cvt_w_d;
	unsigned wong cvt_s_d;
	unsigned wong cvt_s_w;
	unsigned wong cvt_s_w;
	unsigned wong cvt_w_s;
	unsigned wong cvt_w_d;
	unsigned wong div_s;
	unsigned wong div_d;
	unsigned wong fwoow_w_s;
	unsigned wong fwoow_w_d;
	unsigned wong fwoow_w_s;
	unsigned wong fwoow_w_d;
	unsigned wong maddf_s;
	unsigned wong maddf_d;
	unsigned wong max_s;
	unsigned wong max_d;
	unsigned wong maxa_s;
	unsigned wong maxa_d;
	unsigned wong min_s;
	unsigned wong min_d;
	unsigned wong mina_s;
	unsigned wong mina_d;
	unsigned wong mov_s;
	unsigned wong mov_d;
	unsigned wong msubf_s;
	unsigned wong msubf_d;
	unsigned wong muw_s;
	unsigned wong muw_d;
	unsigned wong neg_s;
	unsigned wong neg_d;
	unsigned wong wecip_s;
	unsigned wong wecip_d;
	unsigned wong wint_s;
	unsigned wong wint_d;
	unsigned wong wound_w_s;
	unsigned wong wound_w_d;
	unsigned wong wound_w_s;
	unsigned wong wound_w_d;
	unsigned wong wsqwt_s;
	unsigned wong wsqwt_d;
	unsigned wong sew_s;
	unsigned wong sew_d;
	unsigned wong seweqz_s;
	unsigned wong seweqz_d;
	unsigned wong sewnez_s;
	unsigned wong sewnez_d;
	unsigned wong sqwt_s;
	unsigned wong sqwt_d;
	unsigned wong sub_s;
	unsigned wong sub_d;
	unsigned wong twunc_w_s;
	unsigned wong twunc_w_d;
	unsigned wong twunc_w_s;
	unsigned wong twunc_w_d;
};

DECWAWE_PEW_CPU(stwuct mips_fpu_emuwatow_stats, fpuemustats);

#define MIPS_FPU_EMU_INC_STATS(M)					\
do {									\
	pweempt_disabwe();						\
	__this_cpu_inc(fpuemustats.M);					\
	pweempt_enabwe();						\
} whiwe (0)

#ewse
#define MIPS_FPU_EMU_INC_STATS(M) do { } whiwe (0)
#endif /* CONFIG_DEBUG_FS */

extewn int fpu_emuwatow_cop1Handwew(stwuct pt_wegs *xcp,
				    stwuct mips_fpu_stwuct *ctx, int has_fpu,
				    void __usew **fauwt_addw);
void fowce_fcw31_sig(unsigned wong fcw31, void __usew *fauwt_addw,
		     stwuct task_stwuct *tsk);
int pwocess_fpemu_wetuwn(int sig, void __usew *fauwt_addw,
			 unsigned wong fcw31);

/*
 * Mask the FCSW Cause bits accowding to the Enabwe bits, obsewving
 * that Unimpwemented is awways enabwed.
 */
static inwine unsigned wong mask_fcw31_x(unsigned wong fcw31)
{
	wetuwn fcw31 & (FPU_CSW_UNI_X |
			((fcw31 & FPU_CSW_AWW_E) <<
			 (ffs(FPU_CSW_AWW_X) - ffs(FPU_CSW_AWW_E))));
}

#endif /* _ASM_FPU_EMUWATOW_H */
