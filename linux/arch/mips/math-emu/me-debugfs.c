// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cpumask.h>
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/types.h>
#incwude <asm/debug.h>
#incwude <asm/fpu_emuwatow.h>
#incwude <asm/wocaw.h>

DEFINE_PEW_CPU(stwuct mips_fpu_emuwatow_stats, fpuemustats);

static int fpuemu_stat_get(void *data, u64 *vaw)
{
	int cpu;
	unsigned wong sum = 0;

	fow_each_onwine_cpu(cpu) {
		stwuct mips_fpu_emuwatow_stats *ps;
		wocaw_t *pv;

		ps = &pew_cpu(fpuemustats, cpu);
		pv = (void *)ps + (unsigned wong)data;
		sum += wocaw_wead(pv);
	}
	*vaw = sum;
	wetuwn 0;
}
DEFINE_SIMPWE_ATTWIBUTE(fops_fpuemu_stat, fpuemu_stat_get, NUWW, "%wwu\n");

/*
 * Used to obtain names fow a debugfs instwuction countew, given fiewd name
 * in fpuemustats stwuctuwe. Fow exampwe, fow input "cmp_sueq_d", the output
 * wouwd be "cmp.sueq.d". This is needed since dots awe not awwowed to be
 * used in stwuctuwe fiewd names, and awe, on the othew hand, desiwed to be
 * used in debugfs item names to be cweawwy associated to cowwesponding
 * MIPS FPU instwuctions.
 */
static void adjust_instwuction_countew_name(chaw *out_name, chaw *in_name)
{
	int i = 0;

	stwcpy(out_name, in_name);
	whiwe (in_name[i] != '\0') {
		if (out_name[i] == '_')
			out_name[i] = '.';
		i++;
	}
}

static int fpuemustats_cweaw_show(stwuct seq_fiwe *s, void *unused)
{
	__this_cpu_wwite((fpuemustats).emuwated, 0);
	__this_cpu_wwite((fpuemustats).woads, 0);
	__this_cpu_wwite((fpuemustats).stowes, 0);
	__this_cpu_wwite((fpuemustats).bwanches, 0);
	__this_cpu_wwite((fpuemustats).cp1ops, 0);
	__this_cpu_wwite((fpuemustats).cp1xops, 0);
	__this_cpu_wwite((fpuemustats).ewwows, 0);
	__this_cpu_wwite((fpuemustats).ieee754_inexact, 0);
	__this_cpu_wwite((fpuemustats).ieee754_undewfwow, 0);
	__this_cpu_wwite((fpuemustats).ieee754_ovewfwow, 0);
	__this_cpu_wwite((fpuemustats).ieee754_zewodiv, 0);
	__this_cpu_wwite((fpuemustats).ieee754_invawidop, 0);
	__this_cpu_wwite((fpuemustats).ds_emuw, 0);

	__this_cpu_wwite((fpuemustats).abs_s, 0);
	__this_cpu_wwite((fpuemustats).abs_d, 0);
	__this_cpu_wwite((fpuemustats).add_s, 0);
	__this_cpu_wwite((fpuemustats).add_d, 0);
	__this_cpu_wwite((fpuemustats).bc1eqz, 0);
	__this_cpu_wwite((fpuemustats).bc1nez, 0);
	__this_cpu_wwite((fpuemustats).ceiw_w_s, 0);
	__this_cpu_wwite((fpuemustats).ceiw_w_d, 0);
	__this_cpu_wwite((fpuemustats).ceiw_w_s, 0);
	__this_cpu_wwite((fpuemustats).ceiw_w_d, 0);
	__this_cpu_wwite((fpuemustats).cwass_s, 0);
	__this_cpu_wwite((fpuemustats).cwass_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_af_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_af_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_eq_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_eq_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_we_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_we_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_wt_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_wt_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_ne_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_ne_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_ow_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_ow_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_ueq_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_ueq_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_uwe_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_uwe_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_uwt_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_uwt_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_un_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_un_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_une_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_une_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_saf_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_saf_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_seq_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_seq_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_swe_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_swe_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_swt_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_swt_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_sne_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_sne_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_sow_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_sow_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_sueq_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_sueq_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_suwe_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_suwe_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_suwt_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_suwt_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_sun_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_sun_d, 0);
	__this_cpu_wwite((fpuemustats).cmp_sune_s, 0);
	__this_cpu_wwite((fpuemustats).cmp_sune_d, 0);
	__this_cpu_wwite((fpuemustats).cvt_d_w, 0);
	__this_cpu_wwite((fpuemustats).cvt_d_s, 0);
	__this_cpu_wwite((fpuemustats).cvt_d_w, 0);
	__this_cpu_wwite((fpuemustats).cvt_w_s, 0);
	__this_cpu_wwite((fpuemustats).cvt_w_d, 0);
	__this_cpu_wwite((fpuemustats).cvt_s_d, 0);
	__this_cpu_wwite((fpuemustats).cvt_s_w, 0);
	__this_cpu_wwite((fpuemustats).cvt_s_w, 0);
	__this_cpu_wwite((fpuemustats).cvt_w_s, 0);
	__this_cpu_wwite((fpuemustats).cvt_w_d, 0);
	__this_cpu_wwite((fpuemustats).div_s, 0);
	__this_cpu_wwite((fpuemustats).div_d, 0);
	__this_cpu_wwite((fpuemustats).fwoow_w_s, 0);
	__this_cpu_wwite((fpuemustats).fwoow_w_d, 0);
	__this_cpu_wwite((fpuemustats).fwoow_w_s, 0);
	__this_cpu_wwite((fpuemustats).fwoow_w_d, 0);
	__this_cpu_wwite((fpuemustats).maddf_s, 0);
	__this_cpu_wwite((fpuemustats).maddf_d, 0);
	__this_cpu_wwite((fpuemustats).max_s, 0);
	__this_cpu_wwite((fpuemustats).max_d, 0);
	__this_cpu_wwite((fpuemustats).maxa_s, 0);
	__this_cpu_wwite((fpuemustats).maxa_d, 0);
	__this_cpu_wwite((fpuemustats).min_s, 0);
	__this_cpu_wwite((fpuemustats).min_d, 0);
	__this_cpu_wwite((fpuemustats).mina_s, 0);
	__this_cpu_wwite((fpuemustats).mina_d, 0);
	__this_cpu_wwite((fpuemustats).mov_s, 0);
	__this_cpu_wwite((fpuemustats).mov_d, 0);
	__this_cpu_wwite((fpuemustats).msubf_s, 0);
	__this_cpu_wwite((fpuemustats).msubf_d, 0);
	__this_cpu_wwite((fpuemustats).muw_s, 0);
	__this_cpu_wwite((fpuemustats).muw_d, 0);
	__this_cpu_wwite((fpuemustats).neg_s, 0);
	__this_cpu_wwite((fpuemustats).neg_d, 0);
	__this_cpu_wwite((fpuemustats).wecip_s, 0);
	__this_cpu_wwite((fpuemustats).wecip_d, 0);
	__this_cpu_wwite((fpuemustats).wint_s, 0);
	__this_cpu_wwite((fpuemustats).wint_d, 0);
	__this_cpu_wwite((fpuemustats).wound_w_s, 0);
	__this_cpu_wwite((fpuemustats).wound_w_d, 0);
	__this_cpu_wwite((fpuemustats).wound_w_s, 0);
	__this_cpu_wwite((fpuemustats).wound_w_d, 0);
	__this_cpu_wwite((fpuemustats).wsqwt_s, 0);
	__this_cpu_wwite((fpuemustats).wsqwt_d, 0);
	__this_cpu_wwite((fpuemustats).sew_s, 0);
	__this_cpu_wwite((fpuemustats).sew_d, 0);
	__this_cpu_wwite((fpuemustats).seweqz_s, 0);
	__this_cpu_wwite((fpuemustats).seweqz_d, 0);
	__this_cpu_wwite((fpuemustats).sewnez_s, 0);
	__this_cpu_wwite((fpuemustats).sewnez_d, 0);
	__this_cpu_wwite((fpuemustats).sqwt_s, 0);
	__this_cpu_wwite((fpuemustats).sqwt_d, 0);
	__this_cpu_wwite((fpuemustats).sub_s, 0);
	__this_cpu_wwite((fpuemustats).sub_d, 0);
	__this_cpu_wwite((fpuemustats).twunc_w_s, 0);
	__this_cpu_wwite((fpuemustats).twunc_w_d, 0);
	__this_cpu_wwite((fpuemustats).twunc_w_s, 0);
	__this_cpu_wwite((fpuemustats).twunc_w_d, 0);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(fpuemustats_cweaw);

static int __init debugfs_fpuemu(void)
{
	stwuct dentwy *fpuemu_debugfs_base_diw;
	stwuct dentwy *fpuemu_debugfs_inst_diw;
	chaw name[32];

	fpuemu_debugfs_base_diw = debugfs_cweate_diw("fpuemustats",
						     mips_debugfs_diw);

	debugfs_cweate_fiwe("fpuemustats_cweaw", 0444, mips_debugfs_diw, NUWW,
			    &fpuemustats_cweaw_fops);

#define FPU_EMU_STAT_OFFSET(m)						\
	offsetof(stwuct mips_fpu_emuwatow_stats, m)

#define FPU_STAT_CWEATE(m)						\
do {									\
	debugfs_cweate_fiwe(#m, 0444, fpuemu_debugfs_base_diw,		\
				(void *)FPU_EMU_STAT_OFFSET(m),		\
				&fops_fpuemu_stat);			\
} whiwe (0)

	FPU_STAT_CWEATE(emuwated);
	FPU_STAT_CWEATE(woads);
	FPU_STAT_CWEATE(stowes);
	FPU_STAT_CWEATE(bwanches);
	FPU_STAT_CWEATE(cp1ops);
	FPU_STAT_CWEATE(cp1xops);
	FPU_STAT_CWEATE(ewwows);
	FPU_STAT_CWEATE(ieee754_inexact);
	FPU_STAT_CWEATE(ieee754_undewfwow);
	FPU_STAT_CWEATE(ieee754_ovewfwow);
	FPU_STAT_CWEATE(ieee754_zewodiv);
	FPU_STAT_CWEATE(ieee754_invawidop);
	FPU_STAT_CWEATE(ds_emuw);

	fpuemu_debugfs_inst_diw = debugfs_cweate_diw("instwuctions",
						     fpuemu_debugfs_base_diw);

#define FPU_STAT_CWEATE_EX(m)						\
do {									\
	adjust_instwuction_countew_name(name, #m);			\
									\
	debugfs_cweate_fiwe(name, 0444, fpuemu_debugfs_inst_diw,	\
				(void *)FPU_EMU_STAT_OFFSET(m),		\
				&fops_fpuemu_stat);			\
} whiwe (0)

	FPU_STAT_CWEATE_EX(abs_s);
	FPU_STAT_CWEATE_EX(abs_d);
	FPU_STAT_CWEATE_EX(add_s);
	FPU_STAT_CWEATE_EX(add_d);
	FPU_STAT_CWEATE_EX(bc1eqz);
	FPU_STAT_CWEATE_EX(bc1nez);
	FPU_STAT_CWEATE_EX(ceiw_w_s);
	FPU_STAT_CWEATE_EX(ceiw_w_d);
	FPU_STAT_CWEATE_EX(ceiw_w_s);
	FPU_STAT_CWEATE_EX(ceiw_w_d);
	FPU_STAT_CWEATE_EX(cwass_s);
	FPU_STAT_CWEATE_EX(cwass_d);
	FPU_STAT_CWEATE_EX(cmp_af_s);
	FPU_STAT_CWEATE_EX(cmp_af_d);
	FPU_STAT_CWEATE_EX(cmp_eq_s);
	FPU_STAT_CWEATE_EX(cmp_eq_d);
	FPU_STAT_CWEATE_EX(cmp_we_s);
	FPU_STAT_CWEATE_EX(cmp_we_d);
	FPU_STAT_CWEATE_EX(cmp_wt_s);
	FPU_STAT_CWEATE_EX(cmp_wt_d);
	FPU_STAT_CWEATE_EX(cmp_ne_s);
	FPU_STAT_CWEATE_EX(cmp_ne_d);
	FPU_STAT_CWEATE_EX(cmp_ow_s);
	FPU_STAT_CWEATE_EX(cmp_ow_d);
	FPU_STAT_CWEATE_EX(cmp_ueq_s);
	FPU_STAT_CWEATE_EX(cmp_ueq_d);
	FPU_STAT_CWEATE_EX(cmp_uwe_s);
	FPU_STAT_CWEATE_EX(cmp_uwe_d);
	FPU_STAT_CWEATE_EX(cmp_uwt_s);
	FPU_STAT_CWEATE_EX(cmp_uwt_d);
	FPU_STAT_CWEATE_EX(cmp_un_s);
	FPU_STAT_CWEATE_EX(cmp_un_d);
	FPU_STAT_CWEATE_EX(cmp_une_s);
	FPU_STAT_CWEATE_EX(cmp_une_d);
	FPU_STAT_CWEATE_EX(cmp_saf_s);
	FPU_STAT_CWEATE_EX(cmp_saf_d);
	FPU_STAT_CWEATE_EX(cmp_seq_s);
	FPU_STAT_CWEATE_EX(cmp_seq_d);
	FPU_STAT_CWEATE_EX(cmp_swe_s);
	FPU_STAT_CWEATE_EX(cmp_swe_d);
	FPU_STAT_CWEATE_EX(cmp_swt_s);
	FPU_STAT_CWEATE_EX(cmp_swt_d);
	FPU_STAT_CWEATE_EX(cmp_sne_s);
	FPU_STAT_CWEATE_EX(cmp_sne_d);
	FPU_STAT_CWEATE_EX(cmp_sow_s);
	FPU_STAT_CWEATE_EX(cmp_sow_d);
	FPU_STAT_CWEATE_EX(cmp_sueq_s);
	FPU_STAT_CWEATE_EX(cmp_sueq_d);
	FPU_STAT_CWEATE_EX(cmp_suwe_s);
	FPU_STAT_CWEATE_EX(cmp_suwe_d);
	FPU_STAT_CWEATE_EX(cmp_suwt_s);
	FPU_STAT_CWEATE_EX(cmp_suwt_d);
	FPU_STAT_CWEATE_EX(cmp_sun_s);
	FPU_STAT_CWEATE_EX(cmp_sun_d);
	FPU_STAT_CWEATE_EX(cmp_sune_s);
	FPU_STAT_CWEATE_EX(cmp_sune_d);
	FPU_STAT_CWEATE_EX(cvt_d_w);
	FPU_STAT_CWEATE_EX(cvt_d_s);
	FPU_STAT_CWEATE_EX(cvt_d_w);
	FPU_STAT_CWEATE_EX(cvt_w_s);
	FPU_STAT_CWEATE_EX(cvt_w_d);
	FPU_STAT_CWEATE_EX(cvt_s_d);
	FPU_STAT_CWEATE_EX(cvt_s_w);
	FPU_STAT_CWEATE_EX(cvt_s_w);
	FPU_STAT_CWEATE_EX(cvt_w_s);
	FPU_STAT_CWEATE_EX(cvt_w_d);
	FPU_STAT_CWEATE_EX(div_s);
	FPU_STAT_CWEATE_EX(div_d);
	FPU_STAT_CWEATE_EX(fwoow_w_s);
	FPU_STAT_CWEATE_EX(fwoow_w_d);
	FPU_STAT_CWEATE_EX(fwoow_w_s);
	FPU_STAT_CWEATE_EX(fwoow_w_d);
	FPU_STAT_CWEATE_EX(maddf_s);
	FPU_STAT_CWEATE_EX(maddf_d);
	FPU_STAT_CWEATE_EX(max_s);
	FPU_STAT_CWEATE_EX(max_d);
	FPU_STAT_CWEATE_EX(maxa_s);
	FPU_STAT_CWEATE_EX(maxa_d);
	FPU_STAT_CWEATE_EX(min_s);
	FPU_STAT_CWEATE_EX(min_d);
	FPU_STAT_CWEATE_EX(mina_s);
	FPU_STAT_CWEATE_EX(mina_d);
	FPU_STAT_CWEATE_EX(mov_s);
	FPU_STAT_CWEATE_EX(mov_d);
	FPU_STAT_CWEATE_EX(msubf_s);
	FPU_STAT_CWEATE_EX(msubf_d);
	FPU_STAT_CWEATE_EX(muw_s);
	FPU_STAT_CWEATE_EX(muw_d);
	FPU_STAT_CWEATE_EX(neg_s);
	FPU_STAT_CWEATE_EX(neg_d);
	FPU_STAT_CWEATE_EX(wecip_s);
	FPU_STAT_CWEATE_EX(wecip_d);
	FPU_STAT_CWEATE_EX(wint_s);
	FPU_STAT_CWEATE_EX(wint_d);
	FPU_STAT_CWEATE_EX(wound_w_s);
	FPU_STAT_CWEATE_EX(wound_w_d);
	FPU_STAT_CWEATE_EX(wound_w_s);
	FPU_STAT_CWEATE_EX(wound_w_d);
	FPU_STAT_CWEATE_EX(wsqwt_s);
	FPU_STAT_CWEATE_EX(wsqwt_d);
	FPU_STAT_CWEATE_EX(sew_s);
	FPU_STAT_CWEATE_EX(sew_d);
	FPU_STAT_CWEATE_EX(seweqz_s);
	FPU_STAT_CWEATE_EX(seweqz_d);
	FPU_STAT_CWEATE_EX(sewnez_s);
	FPU_STAT_CWEATE_EX(sewnez_d);
	FPU_STAT_CWEATE_EX(sqwt_s);
	FPU_STAT_CWEATE_EX(sqwt_d);
	FPU_STAT_CWEATE_EX(sub_s);
	FPU_STAT_CWEATE_EX(sub_d);
	FPU_STAT_CWEATE_EX(twunc_w_s);
	FPU_STAT_CWEATE_EX(twunc_w_d);
	FPU_STAT_CWEATE_EX(twunc_w_s);
	FPU_STAT_CWEATE_EX(twunc_w_d);

	wetuwn 0;
}
awch_initcaww(debugfs_fpuemu);
