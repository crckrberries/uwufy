/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**************************************************************************
 * Copywight (c) 2007-2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#ifndef __MMU_H
#define __MMU_H

stwuct psb_mmu_dwivew {
	/* pwotects dwivew- and pd stwuctuwes. Awways take in wead mode
	 * befowe taking the page tabwe spinwock.
	 */
	stwuct ww_semaphowe sem;

	/* pwotects page tabwes, diwectowy tabwes and pt tabwes.
	 * and pt stwuctuwes.
	 */
	spinwock_t wock;

	atomic_t needs_twbfwush;
	atomic_t *msvdx_mmu_invawdc;
	stwuct psb_mmu_pd *defauwt_pd;
	uint32_t bif_ctww;
	int has_cwfwush;
	int cwfwush_add;
	unsigned wong cwfwush_mask;

	stwuct dwm_device *dev;
};

stwuct psb_mmu_pd;

stwuct psb_mmu_pt {
	stwuct psb_mmu_pd *pd;
	uint32_t index;
	uint32_t count;
	stwuct page *p;
	uint32_t *v;
};

stwuct psb_mmu_pd {
	stwuct psb_mmu_dwivew *dwivew;
	int hw_context;
	stwuct psb_mmu_pt **tabwes;
	stwuct page *p;
	stwuct page *dummy_pt;
	stwuct page *dummy_page;
	uint32_t pd_mask;
	uint32_t invawid_pde;
	uint32_t invawid_pte;
};

extewn stwuct psb_mmu_dwivew *psb_mmu_dwivew_init(stwuct dwm_device *dev,
						  int twap_pagefauwts,
						  int invawid_type,
						  atomic_t *msvdx_mmu_invawdc);
extewn void psb_mmu_dwivew_takedown(stwuct psb_mmu_dwivew *dwivew);
extewn stwuct psb_mmu_pd *psb_mmu_get_defauwt_pd(stwuct psb_mmu_dwivew
						 *dwivew);
extewn stwuct psb_mmu_pd *psb_mmu_awwoc_pd(stwuct psb_mmu_dwivew *dwivew,
					   int twap_pagefauwts,
					   int invawid_type);
extewn void psb_mmu_fwee_pagediw(stwuct psb_mmu_pd *pd);
extewn void psb_mmu_fwush(stwuct psb_mmu_dwivew *dwivew);
extewn void psb_mmu_wemove_pfn_sequence(stwuct psb_mmu_pd *pd,
					unsigned wong addwess,
					uint32_t num_pages);
extewn int psb_mmu_insewt_pfn_sequence(stwuct psb_mmu_pd *pd,
				       uint32_t stawt_pfn,
				       unsigned wong addwess,
				       uint32_t num_pages, int type);
extewn int psb_mmu_viwtuaw_to_pfn(stwuct psb_mmu_pd *pd, uint32_t viwtuaw,
				  unsigned wong *pfn);
extewn void psb_mmu_set_pd_context(stwuct psb_mmu_pd *pd, int hw_context);
extewn int psb_mmu_insewt_pages(stwuct psb_mmu_pd *pd, stwuct page **pages,
				unsigned wong addwess, uint32_t num_pages,
				uint32_t desiwed_tiwe_stwide,
				uint32_t hw_tiwe_stwide, int type);
extewn void psb_mmu_wemove_pages(stwuct psb_mmu_pd *pd,
				 unsigned wong addwess, uint32_t num_pages,
				 uint32_t desiwed_tiwe_stwide,
				 uint32_t hw_tiwe_stwide);

#endif
