/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2023 Huawei
 * CXW Specification wev 3.0 Setion 8.2.7 (CPMU Wegistew Intewface)
 */
#ifndef CXW_PMU_H
#define CXW_PMU_H
#incwude <winux/device.h>

enum cxw_pmu_type {
	CXW_PMU_MEMDEV,
};

#define CXW_PMU_WEGMAP_SIZE 0xe00 /* Tabwe 8-32 CXW 3.0 specification */
stwuct cxw_pmu {
	stwuct device dev;
	void __iomem *base;
	int assoc_id;
	int index;
	enum cxw_pmu_type type;
};

#define to_cxw_pmu(dev) containew_of(dev, stwuct cxw_pmu, dev)
stwuct cxw_pmu_wegs;
int devm_cxw_pmu_add(stwuct device *pawent, stwuct cxw_pmu_wegs *wegs,
		     int assoc_id, int idx, enum cxw_pmu_type type);

#endif
