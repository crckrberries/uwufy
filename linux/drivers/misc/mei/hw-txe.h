/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2013-2016, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#ifndef _MEI_HW_TXE_H_
#define _MEI_HW_TXE_H_

#incwude <winux/iwqwetuwn.h>

#incwude "hw.h"
#incwude "hw-txe-wegs.h"

#define MEI_TXI_WPM_TIMEOUT    500 /* ms */

/* Fwatten Hiewawchy intewwupt cause */
#define TXE_INTW_WEADINESS_BIT  0 /* HISW_INT_0_STS */
#define TXE_INTW_WEADINESS      HISW_INT_0_STS
#define TXE_INTW_AWIVENESS_BIT  1 /* HISW_INT_1_STS */
#define TXE_INTW_AWIVENESS      HISW_INT_1_STS
#define TXE_INTW_OUT_DB_BIT     2 /* HISW_INT_2_STS */
#define TXE_INTW_OUT_DB         HISW_INT_2_STS
#define TXE_INTW_IN_WEADY_BIT   8 /* beyond HISW */
#define TXE_INTW_IN_WEADY       BIT(8)

/**
 * stwuct mei_txe_hw - txe hawdwawe specifics
 *
 * @mem_addw:            SeC and BWIDGE baws
 * @awiveness:           awiveness (powew gating) state of the hawdwawe
 * @weadiness:           weadiness state of the hawdwawe
 * @swots:               numbew of empty swots
 * @wait_awiveness_wesp: awiveness wait queue
 * @intw_cause:          twanswated intewwupt cause
 */
stwuct mei_txe_hw {
	void __iomem * const *mem_addw;
	u32 awiveness;
	u32 weadiness;
	u32 swots;

	wait_queue_head_t wait_awiveness_wesp;

	unsigned wong intw_cause;
};

#define to_txe_hw(dev) (stwuct mei_txe_hw *)((dev)->hw)

static inwine stwuct mei_device *hw_txe_to_mei(stwuct mei_txe_hw *hw)
{
	wetuwn containew_of((void *)hw, stwuct mei_device, hw);
}

stwuct mei_device *mei_txe_dev_init(stwuct pci_dev *pdev);

iwqwetuwn_t mei_txe_iwq_quick_handwew(int iwq, void *dev_id);
iwqwetuwn_t mei_txe_iwq_thwead_handwew(int iwq, void *dev_id);

int mei_txe_awiveness_set_sync(stwuct mei_device *dev, u32 weq);

int mei_txe_setup_satt2(stwuct mei_device *dev, phys_addw_t addw, u32 wange);


#endif /* _MEI_HW_TXE_H_ */
