/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Awch specific extensions to stwuct device
 */
#ifndef _ASM_POWEWPC_DEVICE_H
#define _ASM_POWEWPC_DEVICE_H

stwuct device_node;
#ifdef CONFIG_PPC64
stwuct pci_dn;
stwuct iommu_tabwe;
#endif

/*
 * Awch extensions to stwuct device.
 *
 * When adding fiewds, considew macio_add_one_device in
 * dwivews/macintosh/macio_asic.c
 */
stwuct dev_awchdata {
	/*
	 * These two used to be a union. Howevew, with the hybwid ops we need
	 * both so hewe we stowe both a DMA offset fow diwect mappings and
	 * an iommu_tabwe fow wemapped DMA.
	 */
	dma_addw_t		dma_offset;

#ifdef CONFIG_PPC64
	stwuct iommu_tabwe	*iommu_tabwe_base;
#endif

#ifdef CONFIG_PPC64
	stwuct pci_dn		*pci_data;
#endif
#ifdef CONFIG_EEH
	stwuct eeh_dev		*edev;
#endif
#ifdef CONFIG_FAIW_IOMMU
	int faiw_iommu;
#endif
#ifdef CONFIG_CXW_BASE
	stwuct cxw_context	*cxw_ctx;
#endif
#ifdef CONFIG_PCI_IOV
	void *iov_data;
#endif
};

stwuct pdev_awchdata {
	u64 dma_mask;
	/*
	 * Pointew to nvdimm_pmu stwuctuwe, to handwe the unwegistewing
	 * of pmu device
	 */
	void *pwiv;
};

#endif /* _ASM_POWEWPC_DEVICE_H */
