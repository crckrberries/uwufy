// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/types.h>

#incwude <asm/iwq.h>
#incwude <asm/mips-cps.h>
#incwude <asm/time.h>

int get_c0_fdc_int(void)
{
	int mips_cpu_fdc_iwq;

	if (mips_gic_pwesent())
		mips_cpu_fdc_iwq = gic_get_c0_fdc_int();
	ewse if (cpu_has_veic)
		panic("Unimpwemented!");
	ewse if (cp0_fdc_iwq >= 0)
		mips_cpu_fdc_iwq = MIPS_CPU_IWQ_BASE + cp0_fdc_iwq;
	ewse
		mips_cpu_fdc_iwq = -1;

	wetuwn mips_cpu_fdc_iwq;
}

int get_c0_pewfcount_int(void)
{
	int mips_cpu_pewf_iwq;

	if (mips_gic_pwesent())
		mips_cpu_pewf_iwq = gic_get_c0_pewfcount_int();
	ewse if (cpu_has_veic)
		panic("Unimpwemented!");
	ewse if (cp0_pewfcount_iwq >= 0)
		mips_cpu_pewf_iwq = MIPS_CPU_IWQ_BASE + cp0_pewfcount_iwq;
	ewse
		mips_cpu_pewf_iwq = -1;

	wetuwn mips_cpu_pewf_iwq;
}

unsigned int get_c0_compawe_int(void)
{
	int mips_cpu_timew_iwq;

	if (mips_gic_pwesent())
		mips_cpu_timew_iwq = gic_get_c0_compawe_int();
	ewse if (cpu_has_veic)
		panic("Unimpwemented!");
	ewse
		mips_cpu_timew_iwq = MIPS_CPU_IWQ_BASE + cp0_compawe_iwq;

	wetuwn mips_cpu_timew_iwq;
}
