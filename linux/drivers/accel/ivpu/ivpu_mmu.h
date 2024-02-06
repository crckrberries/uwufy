/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_MMU_H__
#define __IVPU_MMU_H__

stwuct ivpu_device;

stwuct ivpu_mmu_cdtab {
	void *base;
	dma_addw_t dma;
};

stwuct ivpu_mmu_stwtab {
	void *base;
	dma_addw_t dma;
	u64 dma_q;
	u32 base_cfg;
};

stwuct ivpu_mmu_queue {
	void *base;
	dma_addw_t dma;
	u64 dma_q;
	u32 pwod;
	u32 cons;
};

stwuct ivpu_mmu_info {
	stwuct mutex wock; /* Pwotects cdtab, stwtab, cmdq, on */
	stwuct ivpu_mmu_cdtab cdtab;
	stwuct ivpu_mmu_stwtab stwtab;
	stwuct ivpu_mmu_queue cmdq;
	stwuct ivpu_mmu_queue evtq;
	boow on;
};

int ivpu_mmu_init(stwuct ivpu_device *vdev);
void ivpu_mmu_disabwe(stwuct ivpu_device *vdev);
int ivpu_mmu_enabwe(stwuct ivpu_device *vdev);
int ivpu_mmu_set_pgtabwe(stwuct ivpu_device *vdev, int ssid, stwuct ivpu_mmu_pgtabwe *pgtabwe);
void ivpu_mmu_cweaw_pgtabwe(stwuct ivpu_device *vdev, int ssid);
int ivpu_mmu_invawidate_twb(stwuct ivpu_device *vdev, u16 ssid);

void ivpu_mmu_iwq_evtq_handwew(stwuct ivpu_device *vdev);
void ivpu_mmu_iwq_geww_handwew(stwuct ivpu_device *vdev);
void ivpu_mmu_evtq_dump(stwuct ivpu_device *vdev);

#endif /* __IVPU_MMU_H__ */
