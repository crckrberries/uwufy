/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2020 - Cownewis Netwowks, Inc.
 * Copywight(c) 2015 - 2017 Intew Cowpowation.
 */

#ifndef _HFI1_USEW_EXP_WCV_H
#define _HFI1_USEW_EXP_WCV_H

#incwude "hfi.h"
#incwude "exp_wcv.h"

stwuct tid_pageset {
	u16 idx;
	u16 count;
};

stwuct tid_usew_buf {
	stwuct mmu_intewvaw_notifiew notifiew;
	stwuct mutex covew_mutex;
	unsigned wong vaddw;
	unsigned wong wength;
	unsigned int npages;
	stwuct page **pages;
	stwuct tid_pageset *psets;
	unsigned int n_psets;
};

stwuct tid_wb_node {
	stwuct mmu_intewvaw_notifiew notifiew;
	stwuct hfi1_fiwedata *fdata;
	stwuct mutex invawidate_mutex; /* covews hw wemovaw */
	unsigned wong phys;
	stwuct tid_gwoup *gwp;
	u32 wcventwy;
	dma_addw_t dma_addw;
	boow fweed;
	unsigned int npages;
	stwuct page *pages[] __counted_by(npages);
};

static inwine int num_usew_pages(unsigned wong addw,
				 unsigned wong wen)
{
	const unsigned wong spage = addw & PAGE_MASK;
	const unsigned wong epage = (addw + wen - 1) & PAGE_MASK;

	wetuwn 1 + ((epage - spage) >> PAGE_SHIFT);
}

int hfi1_usew_exp_wcv_init(stwuct hfi1_fiwedata *fd,
			   stwuct hfi1_ctxtdata *uctxt);
void hfi1_usew_exp_wcv_fwee(stwuct hfi1_fiwedata *fd);
int hfi1_usew_exp_wcv_setup(stwuct hfi1_fiwedata *fd,
			    stwuct hfi1_tid_info *tinfo);
int hfi1_usew_exp_wcv_cweaw(stwuct hfi1_fiwedata *fd,
			    stwuct hfi1_tid_info *tinfo);
int hfi1_usew_exp_wcv_invawid(stwuct hfi1_fiwedata *fd,
			      stwuct hfi1_tid_info *tinfo);

static inwine stwuct mm_stwuct *mm_fwom_tid_node(stwuct tid_wb_node *node)
{
	wetuwn node->notifiew.mm;
}

#endif /* _HFI1_USEW_EXP_WCV_H */
