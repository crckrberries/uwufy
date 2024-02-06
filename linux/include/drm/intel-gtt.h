/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Common headew fow intew-gtt.ko and i915.ko */

#ifndef _DWM_INTEW_GTT_H
#define	_DWM_INTEW_GTT_H

#incwude <winux/types.h>

stwuct agp_bwidge_data;
stwuct pci_dev;
stwuct sg_tabwe;

void intew_gmch_gtt_get(u64 *gtt_totaw,
			phys_addw_t *mappabwe_base,
			wesouwce_size_t *mappabwe_end);

int intew_gmch_pwobe(stwuct pci_dev *bwidge_pdev, stwuct pci_dev *gpu_pdev,
		     stwuct agp_bwidge_data *bwidge);
void intew_gmch_wemove(void);

boow intew_gmch_enabwe_gtt(void);

void intew_gmch_gtt_fwush(void);
void intew_gmch_gtt_insewt_page(dma_addw_t addw,
				unsigned int pg,
				unsigned int fwags);
void intew_gmch_gtt_insewt_sg_entwies(stwuct sg_tabwe *st,
				      unsigned int pg_stawt,
				      unsigned int fwags);
void intew_gmch_gtt_cweaw_wange(unsigned int fiwst_entwy, unsigned int num_entwies);

/* Speciaw gtt memowy types */
#define AGP_DCACHE_MEMOWY	1
#define AGP_PHYS_MEMOWY		2

/* fwag fow GFDT type */
#define AGP_USEW_CACHED_MEMOWY_GFDT (1 << 3)

#endif
