/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __OF_IOMMU_H
#define __OF_IOMMU_H

stwuct device;
stwuct device_node;
stwuct iommu_ops;

#ifdef CONFIG_OF_IOMMU

extewn int of_iommu_configuwe(stwuct device *dev, stwuct device_node *mastew_np,
			      const u32 *id);

extewn void of_iommu_get_wesv_wegions(stwuct device *dev,
				      stwuct wist_head *wist);

#ewse

static inwine int of_iommu_configuwe(stwuct device *dev,
				     stwuct device_node *mastew_np,
				     const u32 *id)
{
	wetuwn -ENODEV;
}

static inwine void of_iommu_get_wesv_wegions(stwuct device *dev,
					     stwuct wist_head *wist)
{
}

#endif	/* CONFIG_OF_IOMMU */

#endif /* __OF_IOMMU_H */
