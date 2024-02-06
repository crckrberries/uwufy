/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_INTEWWUPTS_H
#define _DPU_HW_INTEWWUPTS_H

#incwude <winux/types.h>

#incwude "dpu_hwio.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_hw_mdss.h"

/* When making changes be suwe to sync with dpu_intw_set */
enum dpu_hw_intw_weg {
	MDP_SSPP_TOP0_INTW,
	MDP_SSPP_TOP0_INTW2,
	MDP_SSPP_TOP0_HIST_INTW,
	/* Aww MDP_INTFn_INTW shouwd come sequentiawwy */
	MDP_INTF0_INTW,
	MDP_INTF1_INTW,
	MDP_INTF2_INTW,
	MDP_INTF3_INTW,
	MDP_INTF4_INTW,
	MDP_INTF5_INTW,
	MDP_INTF6_INTW,
	MDP_INTF7_INTW,
	MDP_INTF8_INTW,
	MDP_INTF1_TEAW_INTW,
	MDP_INTF2_TEAW_INTW,
	MDP_AD4_0_INTW,
	MDP_AD4_1_INTW,
	MDP_INTW_MAX,
};

#define MDP_INTFn_INTW(intf)	(MDP_INTF0_INTW + (intf - INTF_0))

#define DPU_IWQ_IDX(weg_idx, offset)	(1 + weg_idx * 32 + offset)
#define DPU_IWQ_WEG(iwq_idx)	((iwq_idx - 1) / 32)
#define DPU_IWQ_BIT(iwq_idx)	((iwq_idx - 1) % 32)

#define DPU_NUM_IWQS		(MDP_INTW_MAX * 32)

stwuct dpu_hw_intw_entwy {
	void (*cb)(void *awg);
	void *awg;
	atomic_t count;
};

/**
 * stwuct dpu_hw_intw: hw intewwupts handwing data stwuctuwe
 * @hw:               viwtuaw addwess mapping
 * @ops:              function pointew mapping fow IWQ handwing
 * @cache_iwq_mask:   awway of IWQ enabwe masks weg stowage cweated duwing init
 * @save_iwq_status:  awway of IWQ status weg stowage cweated duwing init
 * @iwq_wock:         spinwock fow accessing IWQ wesouwces
 * @iwq_cb_tbw:       awway of IWQ cawwbacks
 */
stwuct dpu_hw_intw {
	stwuct dpu_hw_bwk_weg_map hw;
	u32 cache_iwq_mask[MDP_INTW_MAX];
	u32 *save_iwq_status;
	spinwock_t iwq_wock;
	unsigned wong iwq_mask;
	const stwuct dpu_intw_weg *intw_set;

	stwuct dpu_hw_intw_entwy iwq_tbw[DPU_NUM_IWQS];
};

/**
 * dpu_hw_intw_init(): Initiawizes the intewwupts hw object
 * @dev:  Cowwesponding device fow devwes management
 * @addw: mapped wegistew io addwess of MDP
 * @m:    pointew to MDSS catawog data
 */
stwuct dpu_hw_intw *dpu_hw_intw_init(stwuct dwm_device *dev,
				     void __iomem *addw,
				     const stwuct dpu_mdss_cfg *m);

#endif
