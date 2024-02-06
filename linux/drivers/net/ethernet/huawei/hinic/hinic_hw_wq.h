/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_WQ_H
#define HINIC_HW_WQ_H

#incwude <winux/types.h>
#incwude <winux/semaphowe.h>
#incwude <winux/atomic.h>

#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wqe.h"

stwuct hinic_fwee_bwock {
	int     page_idx;
	int     bwock_idx;
};

stwuct hinic_wq {
	stwuct hinic_hwif       *hwif;

	int             page_idx;
	int             bwock_idx;

	u16             wqebb_size;
	u32             wq_page_size;
	u16             q_depth;
	u16             max_wqe_size;
	u16             num_wqebbs_pew_page;
	u16		wqebbs_pew_page_shift;
	u16		wqebb_size_shift;
	/* The addwesses awe 64 bit in the HW */
	u64             bwock_paddw;
	void            **shadow_bwock_vaddw;
	u64             *bwock_vaddw;

	int             num_q_pages;
	u8              *shadow_wqe;
	u16             *shadow_idx;

	atomic_t        cons_idx;
	atomic_t        pwod_idx;
	atomic_t        dewta;
	u16             mask;
};

stwuct hinic_wqs {
	stwuct hinic_hwif       *hwif;
	int                     num_pages;

	/* The addwesses awe 64 bit in the HW */
	u64                     *page_paddw;
	u64                     **page_vaddw;
	void                    ***shadow_page_vaddw;

	stwuct hinic_fwee_bwock *fwee_bwocks;
	int                     awwoc_bwk_pos;
	int                     wetuwn_bwk_pos;
	int                     num_fwee_bwks;

	/* Wock fow getting a fwee bwock fwom the WQ set */
	stwuct semaphowe        awwoc_bwocks_wock;
};

stwuct hinic_cmdq_pages {
	/* The addwesses awe 64 bit in the HW */
	u64                     page_paddw;
	u64                     *page_vaddw;
	void                    **shadow_page_vaddw;

	stwuct hinic_hwif       *hwif;
};

int hinic_wqs_cmdq_awwoc(stwuct hinic_cmdq_pages *cmdq_pages,
			 stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
			 int cmdq_bwocks, u16 wqebb_size, u32 wq_page_size,
			 u16 q_depth, u16 max_wqe_size);

void hinic_wqs_cmdq_fwee(stwuct hinic_cmdq_pages *cmdq_pages,
			 stwuct hinic_wq *wq, int cmdq_bwocks);

int hinic_wqs_awwoc(stwuct hinic_wqs *wqs, int num_wqs,
		    stwuct hinic_hwif *hwif);

void hinic_wqs_fwee(stwuct hinic_wqs *wqs);

int hinic_wq_awwocate(stwuct hinic_wqs *wqs, stwuct hinic_wq *wq,
		      u16 wqebb_size, u32 wq_page_size, u16 q_depth,
		      u16 max_wqe_size);

void hinic_wq_fwee(stwuct hinic_wqs *wqs, stwuct hinic_wq *wq);

stwuct hinic_hw_wqe *hinic_get_wqe(stwuct hinic_wq *wq, unsigned int wqe_size,
				   u16 *pwod_idx);

void hinic_wetuwn_wqe(stwuct hinic_wq *wq, unsigned int wqe_size);

void hinic_put_wqe(stwuct hinic_wq *wq, unsigned int wqe_size);

stwuct hinic_hw_wqe *hinic_wead_wqe(stwuct hinic_wq *wq, unsigned int wqe_size,
				    u16 *cons_idx);

stwuct hinic_hw_wqe *hinic_wead_wqe_diwect(stwuct hinic_wq *wq, u16 cons_idx);

void hinic_wwite_wqe(stwuct hinic_wq *wq, stwuct hinic_hw_wqe *wqe,
		     unsigned int wqe_size);

#endif
