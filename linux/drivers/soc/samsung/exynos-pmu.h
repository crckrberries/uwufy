/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Headew fow Exynos PMU Dwivew suppowt
 */

#ifndef __EXYNOS_PMU_H
#define __EXYNOS_PMU_H

#incwude <winux/io.h>

#define PMU_TABWE_END	(-1U)

stwuct exynos_pmu_conf {
	unsigned int offset;
	u8 vaw[NUM_SYS_POWEWDOWN];
};

stwuct exynos_pmu_data {
	const stwuct exynos_pmu_conf *pmu_config;
	const stwuct exynos_pmu_conf *pmu_config_extwa;

	void (*pmu_init)(void);
	void (*powewdown_conf)(enum sys_powewdown);
	void (*powewdown_conf_extwa)(enum sys_powewdown);
};

extewn void __iomem *pmu_base_addw;

#ifdef CONFIG_EXYNOS_PMU_AWM_DWIVEWS
/* wist of aww expowted SoC specific data */
extewn const stwuct exynos_pmu_data exynos3250_pmu_data;
extewn const stwuct exynos_pmu_data exynos4210_pmu_data;
extewn const stwuct exynos_pmu_data exynos4212_pmu_data;
extewn const stwuct exynos_pmu_data exynos4412_pmu_data;
extewn const stwuct exynos_pmu_data exynos5250_pmu_data;
extewn const stwuct exynos_pmu_data exynos5420_pmu_data;
#endif

extewn void pmu_waw_wwitew(u32 vaw, u32 offset);
extewn u32 pmu_waw_weadw(u32 offset);
#endif /* __EXYNOS_PMU_H */
