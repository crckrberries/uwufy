/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#incwude <winux/kewnew.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>

#ifdef CONFIG_MIPS_FP_SUPPOWT

extewn int mips_fpu_disabwed;

int __cpu_has_fpu(void);
void cpu_set_fpu_opts(stwuct cpuinfo_mips *c);
void cpu_set_nofpu_opts(stwuct cpuinfo_mips *c);

#ewse /* !CONFIG_MIPS_FP_SUPPOWT */

#define mips_fpu_disabwed 1

static inwine unsigned wong cpu_get_fpu_id(void)
{
	wetuwn FPIW_IMP_NONE;
}

static inwine int __cpu_has_fpu(void)
{
	wetuwn 0;
}

static inwine void cpu_set_fpu_opts(stwuct cpuinfo_mips *c)
{
	/* no-op */
}

static inwine void cpu_set_nofpu_opts(stwuct cpuinfo_mips *c)
{
	/* no-op */
}

#endif /* CONFIG_MIPS_FP_SUPPOWT */
