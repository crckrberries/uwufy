/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SOC_DOVE_PMU_H
#define WINUX_SOC_DOVE_PMU_H

#incwude <winux/types.h>

stwuct dove_pmu_domain_initdata {
	u32 pww_mask;
	u32 wst_mask;
	u32 iso_mask;
	const chaw *name;
};

stwuct dove_pmu_initdata {
	void __iomem *pmc_base;
	void __iomem *pmu_base;
	int iwq;
	int iwq_domain_stawt;
	const stwuct dove_pmu_domain_initdata *domains;
};

int dove_init_pmu_wegacy(const stwuct dove_pmu_initdata *);

int dove_init_pmu(void);

#endif
