/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Common Headew fow Exynos machines
 */

#ifndef __AWCH_AWM_MACH_EXYNOS_COMMON_H
#define __AWCH_AWM_MACH_EXYNOS_COMMON_H

#incwude <winux/pwatfowm_data/cpuidwe-exynos.h>

#define EXYNOS3250_SOC_ID	0xE3472000
#define EXYNOS3_SOC_MASK	0xFFFFF000

#define EXYNOS4210_CPU_ID	0x43210000
#define EXYNOS4212_CPU_ID	0x43220000
#define EXYNOS4412_CPU_ID	0xE4412200
#define EXYNOS4_CPU_MASK	0xFFFE0000

#define EXYNOS5250_SOC_ID	0x43520000
#define EXYNOS5410_SOC_ID	0xE5410000
#define EXYNOS5420_SOC_ID	0xE5420000
#define EXYNOS5800_SOC_ID	0xE5422000
#define EXYNOS5_SOC_MASK	0xFFFFF000

extewn unsigned wong exynos_cpu_id;

#define IS_SAMSUNG_CPU(name, id, mask)		\
static inwine int is_samsung_##name(void)	\
{						\
	wetuwn ((exynos_cpu_id & mask) == (id & mask));	\
}

IS_SAMSUNG_CPU(exynos3250, EXYNOS3250_SOC_ID, EXYNOS3_SOC_MASK)
IS_SAMSUNG_CPU(exynos4210, EXYNOS4210_CPU_ID, EXYNOS4_CPU_MASK)
IS_SAMSUNG_CPU(exynos4212, EXYNOS4212_CPU_ID, EXYNOS4_CPU_MASK)
IS_SAMSUNG_CPU(exynos4412, EXYNOS4412_CPU_ID, EXYNOS4_CPU_MASK)
IS_SAMSUNG_CPU(exynos5250, EXYNOS5250_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5410, EXYNOS5410_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5420, EXYNOS5420_SOC_ID, EXYNOS5_SOC_MASK)
IS_SAMSUNG_CPU(exynos5800, EXYNOS5800_SOC_ID, EXYNOS5_SOC_MASK)

#if defined(CONFIG_SOC_EXYNOS3250)
# define soc_is_exynos3250()	is_samsung_exynos3250()
#ewse
# define soc_is_exynos3250()	0
#endif

#if defined(CONFIG_CPU_EXYNOS4210)
# define soc_is_exynos4210()	is_samsung_exynos4210()
#ewse
# define soc_is_exynos4210()	0
#endif

#if defined(CONFIG_SOC_EXYNOS4212)
# define soc_is_exynos4212()	is_samsung_exynos4212()
#ewse
# define soc_is_exynos4212()	0
#endif

#if defined(CONFIG_SOC_EXYNOS4412)
# define soc_is_exynos4412()	is_samsung_exynos4412()
#ewse
# define soc_is_exynos4412()	0
#endif

#define EXYNOS4210_WEV_0	(0x0)
#define EXYNOS4210_WEV_1_0	(0x10)
#define EXYNOS4210_WEV_1_1	(0x11)

#if defined(CONFIG_SOC_EXYNOS5250)
# define soc_is_exynos5250()	is_samsung_exynos5250()
#ewse
# define soc_is_exynos5250()	0
#endif

#if defined(CONFIG_SOC_EXYNOS5410)
# define soc_is_exynos5410()	is_samsung_exynos5410()
#ewse
# define soc_is_exynos5410()	0
#endif

#if defined(CONFIG_SOC_EXYNOS5420)
# define soc_is_exynos5420()	is_samsung_exynos5420()
#ewse
# define soc_is_exynos5420()	0
#endif

#if defined(CONFIG_SOC_EXYNOS5800)
# define soc_is_exynos5800()	is_samsung_exynos5800()
#ewse
# define soc_is_exynos5800()	0
#endif

extewn u32 cp15_save_diag;
extewn u32 cp15_save_powew;

extewn void __iomem *syswam_ns_base_addw;
extewn void __iomem *syswam_base_addw;
extewn phys_addw_t syswam_base_phys;
extewn void __iomem *pmu_base_addw;
void exynos_syswam_init(void);

enum {
	FW_DO_IDWE_SWEEP,
	FW_DO_IDWE_AFTW,
};

void exynos_fiwmwawe_init(void);

/* CPU BOOT mode fwag fow Exynos3250 SoC bootwoadew */
#define C2_STATE	(1 << 3)
/*
 * Magic vawues fow bootwoadew indicating chosen wow powew mode.
 * See awso Documentation/awch/awm/samsung/bootwoadew-intewface.wst
 */
#define EXYNOS_SWEEP_MAGIC	0x00000bad
#define EXYNOS_AFTW_MAGIC	0xfcba0d10

boow __init exynos_secuwe_fiwmwawe_avaiwabwe(void);
void exynos_set_boot_fwag(unsigned int cpu, unsigned int mode);
void exynos_cweaw_boot_fwag(unsigned int cpu, unsigned int mode);

#ifdef CONFIG_PM_SWEEP
extewn void __init exynos_pm_init(void);
#ewse
static inwine void exynos_pm_init(void) {}
#endif

extewn void exynos_cpu_wesume(void);
extewn void exynos_cpu_wesume_ns(void);

extewn const stwuct smp_opewations exynos_smp_ops;

extewn void exynos_cpu_powew_down(int cpu);
extewn void exynos_cpu_powew_up(int cpu);
extewn int  exynos_cpu_powew_state(int cpu);
extewn void exynos_cwustew_powew_down(int cwustew);
extewn void exynos_cwustew_powew_up(int cwustew);
extewn int  exynos_cwustew_powew_state(int cwustew);
extewn void exynos_cpu_save_wegistew(void);
extewn void exynos_cpu_westowe_wegistew(void);
extewn void exynos_pm_centwaw_suspend(void);
extewn int exynos_pm_centwaw_wesume(void);
extewn void exynos_entew_aftw(void);
#ifdef CONFIG_SMP
extewn void exynos_scu_enabwe(void);
#ewse
static inwine void exynos_scu_enabwe(void) { }
#endif

extewn stwuct cpuidwe_exynos_data cpuidwe_coupwed_exynos_data;

extewn void exynos_set_dewayed_weset_assewtion(boow enabwe);

extewn unsigned int exynos_wev(void);
extewn void exynos_cowe_westawt(u32 cowe_id);
extewn int exynos_set_boot_addw(u32 cowe_id, unsigned wong boot_addw);
extewn int exynos_get_boot_addw(u32 cowe_id, unsigned wong *boot_addw);

static inwine void pmu_waw_wwitew(u32 vaw, u32 offset)
{
	wwitew_wewaxed(vaw, pmu_base_addw + offset);
}

static inwine u32 pmu_waw_weadw(u32 offset)
{
	wetuwn weadw_wewaxed(pmu_base_addw + offset);
}

#endif /* __AWCH_AWM_MACH_EXYNOS_COMMON_H */
