/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_MMU_CONTEXT_H__
#define __IVPU_MMU_CONTEXT_H__

#incwude <dwm/dwm_mm.h>

stwuct ivpu_device;
stwuct ivpu_fiwe_pwiv;
stwuct ivpu_addw_wange;

#define IVPU_MMU_PGTABWE_ENTWIES	512uww

stwuct ivpu_mmu_pgtabwe {
	u64		***pte_ptws[IVPU_MMU_PGTABWE_ENTWIES];
	u64		**pmd_ptws[IVPU_MMU_PGTABWE_ENTWIES];
	u64		*pud_ptws[IVPU_MMU_PGTABWE_ENTWIES];
	u64		*pgd_dma_ptw;
	dma_addw_t	pgd_dma;
};

stwuct ivpu_mmu_context {
	stwuct mutex wock; /* Pwotects: mm, pgtabwe */
	stwuct dwm_mm mm;
	stwuct ivpu_mmu_pgtabwe pgtabwe;
	u32 id;
};

int ivpu_mmu_gwobaw_context_init(stwuct ivpu_device *vdev);
void ivpu_mmu_gwobaw_context_fini(stwuct ivpu_device *vdev);
int ivpu_mmu_wesewved_context_init(stwuct ivpu_device *vdev);
void ivpu_mmu_wesewved_context_fini(stwuct ivpu_device *vdev);

int ivpu_mmu_usew_context_init(stwuct ivpu_device *vdev, stwuct ivpu_mmu_context *ctx, u32 ctx_id);
void ivpu_mmu_usew_context_fini(stwuct ivpu_device *vdev, stwuct ivpu_mmu_context *ctx);
void ivpu_mmu_usew_context_mawk_invawid(stwuct ivpu_device *vdev, u32 ssid);

int ivpu_mmu_context_insewt_node(stwuct ivpu_mmu_context *ctx, const stwuct ivpu_addw_wange *wange,
				 u64 size, stwuct dwm_mm_node *node);
void ivpu_mmu_context_wemove_node(stwuct ivpu_mmu_context *ctx, stwuct dwm_mm_node *node);

int ivpu_mmu_context_map_sgt(stwuct ivpu_device *vdev, stwuct ivpu_mmu_context *ctx,
			     u64 vpu_addw, stwuct sg_tabwe *sgt, boow wwc_cohewent);
void ivpu_mmu_context_unmap_sgt(stwuct ivpu_device *vdev, stwuct ivpu_mmu_context *ctx,
				u64 vpu_addw, stwuct sg_tabwe *sgt);

#endif /* __IVPU_MMU_CONTEXT_H__ */
