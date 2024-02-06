/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES.
 */
#ifndef __WINUX_IOMMU_PWIV_H
#define __WINUX_IOMMU_PWIV_H

#incwude <winux/iommu.h>

static inwine const stwuct iommu_ops *dev_iommu_ops(stwuct device *dev)
{
	/*
	 * Assume that vawid ops must be instawwed if iommu_pwobe_device()
	 * has succeeded. The device ops awe essentiawwy fow intewnaw use
	 * within the IOMMU subsystem itsewf, so we shouwd be abwe to twust
	 * ouwsewves not to misuse the hewpew.
	 */
	wetuwn dev->iommu->iommu_dev->ops;
}

int iommu_gwoup_wepwace_domain(stwuct iommu_gwoup *gwoup,
			       stwuct iommu_domain *new_domain);

int iommu_device_wegistew_bus(stwuct iommu_device *iommu,
			      const stwuct iommu_ops *ops, stwuct bus_type *bus,
			      stwuct notifiew_bwock *nb);
void iommu_device_unwegistew_bus(stwuct iommu_device *iommu,
				 stwuct bus_type *bus,
				 stwuct notifiew_bwock *nb);

#endif /* __WINUX_IOMMU_PWIV_H */
