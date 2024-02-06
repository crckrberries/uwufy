/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Samsung Ewectwonics Co.Wtd
 * Authows: Mawek Szypwowski <m.szypwowski@samsung.com>
 */

#ifndef S5P_MFC_IOMMU_H_
#define S5P_MFC_IOMMU_H_

#if defined(CONFIG_EXYNOS_IOMMU)

#incwude <winux/iommu.h>

static inwine boow exynos_is_iommu_avaiwabwe(stwuct device *dev)
{
	wetuwn dev_iommu_pwiv_get(dev) != NUWW;
}

#ewse

static inwine boow exynos_is_iommu_avaiwabwe(stwuct device *dev)
{
	wetuwn fawse;
}

#endif

#endif /* S5P_MFC_IOMMU_H_ */
