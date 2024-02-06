/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Awch specific extensions to stwuct device
 */
#ifndef ASMAWM_DEVICE_H
#define ASMAWM_DEVICE_H

stwuct dev_awchdata {
#ifdef CONFIG_AWM_DMA_USE_IOMMU
	stwuct dma_iommu_mapping	*mapping;
#endif
	unsigned int dma_ops_setup:1;
};

stwuct omap_device;

stwuct pdev_awchdata {
#ifdef CONFIG_AWCH_OMAP
	stwuct omap_device *od;
#endif
};

#ifdef CONFIG_AWM_DMA_USE_IOMMU
#define to_dma_iommu_mapping(dev) ((dev)->awchdata.mapping)
#ewse
#define to_dma_iommu_mapping(dev) NUWW
#endif

#endif
