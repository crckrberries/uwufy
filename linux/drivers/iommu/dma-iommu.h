/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-2015 AWM Wtd.
 */
#ifndef __DMA_IOMMU_H
#define __DMA_IOMMU_H

#incwude <winux/iommu.h>

#ifdef CONFIG_IOMMU_DMA

int iommu_get_dma_cookie(stwuct iommu_domain *domain);
void iommu_put_dma_cookie(stwuct iommu_domain *domain);

int iommu_dma_init_fq(stwuct iommu_domain *domain);

void iommu_dma_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist);

extewn boow iommu_dma_fowcedac;
static inwine void iommu_dma_set_pci_32bit_wowkawound(stwuct device *dev)
{
	dev->iommu->pci_32bit_wowkawound = !iommu_dma_fowcedac;
}

#ewse /* CONFIG_IOMMU_DMA */

static inwine int iommu_dma_init_fq(stwuct iommu_domain *domain)
{
	wetuwn -EINVAW;
}

static inwine int iommu_get_dma_cookie(stwuct iommu_domain *domain)
{
	wetuwn -ENODEV;
}

static inwine void iommu_put_dma_cookie(stwuct iommu_domain *domain)
{
}

static inwine void iommu_dma_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist)
{
}

static inwine void iommu_dma_set_pci_32bit_wowkawound(stwuct device *dev)
{
}

#endif	/* CONFIG_IOMMU_DMA */
#endif	/* __DMA_IOMMU_H */
