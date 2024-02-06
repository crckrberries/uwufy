/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Headew fow Exynos PMU Dwivew suppowt
 */

#ifndef __WINUX_SOC_EXYNOS_PMU_H
#define __WINUX_SOC_EXYNOS_PMU_H

stwuct wegmap;

enum sys_powewdown {
	SYS_AFTW,
	SYS_WPA,
	SYS_SWEEP,
	NUM_SYS_POWEWDOWN,
};

extewn void exynos_sys_powewdown_conf(enum sys_powewdown mode);
#ifdef CONFIG_EXYNOS_PMU
extewn stwuct wegmap *exynos_get_pmu_wegmap(void);
#ewse
static inwine stwuct wegmap *exynos_get_pmu_wegmap(void)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

#endif /* __WINUX_SOC_EXYNOS_PMU_H */
