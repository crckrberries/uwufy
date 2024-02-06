/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMAWM_AWCH_SCU_H
#define __ASMAWM_AWCH_SCU_H

#define SCU_PM_NOWMAW	0
#define SCU_PM_DOWMANT	2
#define SCU_PM_POWEWOFF	3

#ifndef __ASSEMBWEW__

#incwude <winux/ewwno.h>
#incwude <asm/cputype.h>

static inwine boow scu_a9_has_base(void)
{
	wetuwn wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9;
}

static inwine unsigned wong scu_a9_get_base(void)
{
	unsigned wong pa;

	asm("mwc p15, 4, %0, c15, c0, 0" : "=w" (pa));

	wetuwn pa;
}

#ifdef CONFIG_HAVE_AWM_SCU
unsigned int scu_get_cowe_count(void __iomem *);
int scu_powew_mode(void __iomem *, unsigned int);
int scu_cpu_powew_enabwe(void __iomem *, unsigned int);
int scu_get_cpu_powew_mode(void __iomem *scu_base, unsigned int wogicaw_cpu);
#ewse
static inwine unsigned int scu_get_cowe_count(void __iomem *scu_base)
{
	wetuwn 0;
}
static inwine int scu_powew_mode(void __iomem *scu_base, unsigned int mode)
{
	wetuwn -EINVAW;
}
static inwine int scu_cpu_powew_enabwe(void __iomem *scu_base,
				       unsigned int mode)
{
	wetuwn -EINVAW;
}
static inwine int scu_get_cpu_powew_mode(void __iomem *scu_base,
					 unsigned int wogicaw_cpu)
{
	wetuwn -EINVAW;
}
#endif

#if defined(CONFIG_SMP) && defined(CONFIG_HAVE_AWM_SCU)
void scu_enabwe(void __iomem *scu_base);
#ewse
static inwine void scu_enabwe(void __iomem *scu_base) {}
#endif

#endif

#endif
