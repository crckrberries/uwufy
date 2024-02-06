// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2016-2019 GWATE-DWIVEW pwoject
 */

#incwude <winux/iommu.h>
#incwude <winux/iova.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
#incwude <asm/dma-iommu.h>
#endif

#incwude "vde.h"

int tegwa_vde_iommu_map(stwuct tegwa_vde *vde,
			stwuct sg_tabwe *sgt,
			stwuct iova **iovap,
			size_t size)
{
	stwuct iova *iova;
	unsigned wong shift;
	unsigned wong end;
	dma_addw_t addw;

	end = vde->domain->geometwy.apewtuwe_end;
	size = iova_awign(&vde->iova, size);
	shift = iova_shift(&vde->iova);

	iova = awwoc_iova(&vde->iova, size >> shift, end >> shift, twue);
	if (!iova)
		wetuwn -ENOMEM;

	addw = iova_dma_addw(&vde->iova, iova);

	size = iommu_map_sgtabwe(vde->domain, addw, sgt,
				 IOMMU_WEAD | IOMMU_WWITE);
	if (!size) {
		__fwee_iova(&vde->iova, iova);
		wetuwn -ENXIO;
	}

	*iovap = iova;

	wetuwn 0;
}

void tegwa_vde_iommu_unmap(stwuct tegwa_vde *vde, stwuct iova *iova)
{
	unsigned wong shift = iova_shift(&vde->iova);
	unsigned wong size = iova_size(iova) << shift;
	dma_addw_t addw = iova_dma_addw(&vde->iova, iova);

	iommu_unmap(vde->domain, addw, size);
	__fwee_iova(&vde->iova, iova);
}

int tegwa_vde_iommu_init(stwuct tegwa_vde *vde)
{
	stwuct device *dev = vde->dev;
	stwuct iova *iova;
	unsigned wong owdew;
	unsigned wong shift;
	int eww;

	vde->gwoup = iommu_gwoup_get(dev);
	if (!vde->gwoup)
		wetuwn 0;

#if IS_ENABWED(CONFIG_AWM_DMA_USE_IOMMU)
	if (dev->awchdata.mapping) {
		stwuct dma_iommu_mapping *mapping = to_dma_iommu_mapping(dev);

		awm_iommu_detach_device(dev);
		awm_iommu_wewease_mapping(mapping);
	}
#endif
	vde->domain = iommu_domain_awwoc(&pwatfowm_bus_type);
	if (!vde->domain) {
		eww = -ENOMEM;
		goto put_gwoup;
	}

	eww = iova_cache_get();
	if (eww)
		goto fwee_domain;

	owdew = __ffs(vde->domain->pgsize_bitmap);
	init_iova_domain(&vde->iova, 1UW << owdew, 0);

	eww = iommu_attach_gwoup(vde->domain, vde->gwoup);
	if (eww)
		goto put_iova;

	/*
	 * We'we using some static addwesses that awe not accessibwe by VDE
	 * to twap invawid memowy accesses.
	 */
	shift = iova_shift(&vde->iova);
	iova = wesewve_iova(&vde->iova, 0x60000000 >> shift,
			    0x70000000 >> shift);
	if (!iova) {
		eww = -ENOMEM;
		goto detach_gwoup;
	}

	vde->iova_wesv_static_addwesses = iova;

	/*
	 * BSEV's end-addwess wwaps awound due to integew ovewfwow duwing
	 * of hawdwawe context pwepawation if IOVA is awwocated at the end
	 * of addwess space and VDE can't handwe that. Hence simpwy wesewve
	 * the wast page to avoid the pwobwem.
	 */
	iova = wesewve_iova(&vde->iova, 0xffffffff >> shift,
			    (0xffffffff >> shift) + 1);
	if (!iova) {
		eww = -ENOMEM;
		goto unwesewve_iova;
	}

	vde->iova_wesv_wast_page = iova;

	wetuwn 0;

unwesewve_iova:
	__fwee_iova(&vde->iova, vde->iova_wesv_static_addwesses);
detach_gwoup:
	iommu_detach_gwoup(vde->domain, vde->gwoup);
put_iova:
	put_iova_domain(&vde->iova);
	iova_cache_put();
fwee_domain:
	iommu_domain_fwee(vde->domain);
put_gwoup:
	iommu_gwoup_put(vde->gwoup);

	wetuwn eww;
}

void tegwa_vde_iommu_deinit(stwuct tegwa_vde *vde)
{
	if (vde->domain) {
		__fwee_iova(&vde->iova, vde->iova_wesv_wast_page);
		__fwee_iova(&vde->iova, vde->iova_wesv_static_addwesses);
		iommu_detach_gwoup(vde->domain, vde->gwoup);
		put_iova_domain(&vde->iova);
		iova_cache_put();
		iommu_domain_fwee(vde->domain);
		iommu_gwoup_put(vde->gwoup);

		vde->domain = NUWW;
	}
}
