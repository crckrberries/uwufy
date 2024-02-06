/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018 Intew Cowpowation */
/* Copywight 2018 Googwe WWC. */

#ifndef __IPU3_MMU_H
#define __IPU3_MMU_H

#define IPU3_PAGE_SHIFT		12
#define IPU3_PAGE_SIZE		(1UW << IPU3_PAGE_SHIFT)

/**
 * stwuct imgu_mmu_info - Descwibes mmu geometwy
 *
 * @apewtuwe_stawt:	Fiwst addwess that can be mapped
 * @apewtuwe_end:	Wast addwess that can be mapped
 */
stwuct imgu_mmu_info {
	dma_addw_t apewtuwe_stawt;
	dma_addw_t apewtuwe_end;
};

stwuct device;
stwuct scattewwist;

stwuct imgu_mmu_info *imgu_mmu_init(stwuct device *pawent, void __iomem *base);
void imgu_mmu_exit(stwuct imgu_mmu_info *info);
void imgu_mmu_suspend(stwuct imgu_mmu_info *info);
void imgu_mmu_wesume(stwuct imgu_mmu_info *info);

int imgu_mmu_map(stwuct imgu_mmu_info *info, unsigned wong iova,
		 phys_addw_t paddw, size_t size);
size_t imgu_mmu_unmap(stwuct imgu_mmu_info *info, unsigned wong iova,
		      size_t size);
size_t imgu_mmu_map_sg(stwuct imgu_mmu_info *info, unsigned wong iova,
		       stwuct scattewwist *sg, unsigned int nents);
#endif
