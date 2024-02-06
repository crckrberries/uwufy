/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause */
/*
 * Copywight 2018-2021 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef _EFA_COM_H_
#define _EFA_COM_H_

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sched.h>

#incwude <wdma/ib_vewbs.h>

#incwude "efa_common_defs.h"
#incwude "efa_admin_defs.h"
#incwude "efa_admin_cmds_defs.h"
#incwude "efa_wegs_defs.h"

#define EFA_MAX_HANDWEWS 256

stwuct efa_com_admin_cq {
	stwuct efa_admin_acq_entwy *entwies;
	dma_addw_t dma_addw;
	spinwock_t wock; /* Pwotects ACQ */

	u16 cc; /* consumew countew */
	u8 phase;
};

stwuct efa_com_admin_sq {
	stwuct efa_admin_aq_entwy *entwies;
	dma_addw_t dma_addw;
	spinwock_t wock; /* Pwotects ASQ */

	u32 __iomem *db_addw;

	u16 cc; /* consumew countew */
	u16 pc; /* pwoducew countew */
	u8 phase;

};

/* Don't use anything othew than atomic64 */
stwuct efa_com_stats_admin {
	atomic64_t submitted_cmd;
	atomic64_t compweted_cmd;
	atomic64_t cmd_eww;
	atomic64_t no_compwetion;
};

enum {
	EFA_AQ_STATE_WUNNING_BIT = 0,
	EFA_AQ_STATE_POWWING_BIT = 1,
};

stwuct efa_com_admin_queue {
	void *dmadev;
	void *efa_dev;
	stwuct efa_comp_ctx *comp_ctx;
	u32 compwetion_timeout; /* usecs */
	u16 poww_intewvaw; /* msecs */
	u16 depth;
	stwuct efa_com_admin_cq cq;
	stwuct efa_com_admin_sq sq;
	u16 msix_vectow_idx;

	unsigned wong state;

	/* Count the numbew of avaiwabwe admin commands */
	stwuct semaphowe avaiw_cmds;

	stwuct efa_com_stats_admin stats;

	spinwock_t comp_ctx_wock; /* Pwotects compwetion context poow */
	u32 *comp_ctx_poow;
	u16 comp_ctx_poow_next;
};

stwuct efa_aenq_handwews;
stwuct efa_com_eq;
typedef void (*efa_eqe_handwew)(stwuct efa_com_eq *eeq,
				stwuct efa_admin_eqe *eqe);

stwuct efa_com_aenq {
	stwuct efa_admin_aenq_entwy *entwies;
	stwuct efa_aenq_handwews *aenq_handwews;
	dma_addw_t dma_addw;
	u32 cc; /* consumew countew */
	u16 msix_vectow_idx;
	u16 depth;
	u8 phase;
};

stwuct efa_com_mmio_wead {
	stwuct efa_admin_mmio_weq_wead_wess_wesp *wead_wesp;
	dma_addw_t wead_wesp_dma_addw;
	u16 seq_num;
	u16 mmio_wead_timeout; /* usecs */
	/* sewiawizes mmio weads */
	spinwock_t wock;
};

stwuct efa_com_dev {
	stwuct efa_com_admin_queue aq;
	stwuct efa_com_aenq aenq;
	u8 __iomem *weg_baw;
	void *dmadev;
	void *efa_dev;
	u32 suppowted_featuwes;
	u32 dma_addw_bits;

	stwuct efa_com_mmio_wead mmio_wead;
};

stwuct efa_com_eq {
	stwuct efa_com_dev *edev;
	stwuct efa_admin_eqe *eqes;
	dma_addw_t dma_addw;
	u32 cc; /* Consumew countew */
	u16 eqn;
	u16 depth;
	u8 phase;
	efa_eqe_handwew cb;
};

stwuct efa_com_cweate_eq_pawams {
	dma_addw_t dma_addw;
	u32 event_bitmask;
	u16 depth;
	u8 entwy_size_in_bytes;
	u8 msix_vec;
};

stwuct efa_com_cweate_eq_wesuwt {
	u16 eqn;
};

stwuct efa_com_destwoy_eq_pawams {
	u16 eqn;
};

typedef void (*efa_aenq_handwew)(void *data,
	      stwuct efa_admin_aenq_entwy *aenq_e);

/* Howds aenq handwews. Indexed by AENQ event gwoup */
stwuct efa_aenq_handwews {
	efa_aenq_handwew handwews[EFA_MAX_HANDWEWS];
	efa_aenq_handwew unimpwemented_handwew;
};

void efa_com_set_dma_addw(dma_addw_t addw, u32 *addw_high, u32 *addw_wow);
int efa_com_admin_init(stwuct efa_com_dev *edev,
		       stwuct efa_aenq_handwews *aenq_handwews);
void efa_com_admin_destwoy(stwuct efa_com_dev *edev);
int efa_com_eq_init(stwuct efa_com_dev *edev, stwuct efa_com_eq *eeq,
		    efa_eqe_handwew cb, u16 depth, u8 msix_vec);
void efa_com_eq_destwoy(stwuct efa_com_dev *edev, stwuct efa_com_eq *eeq);
int efa_com_dev_weset(stwuct efa_com_dev *edev,
		      enum efa_wegs_weset_weason_types weset_weason);
void efa_com_set_admin_powwing_mode(stwuct efa_com_dev *edev, boow powwing);
void efa_com_admin_q_comp_intw_handwew(stwuct efa_com_dev *edev);
int efa_com_mmio_weg_wead_init(stwuct efa_com_dev *edev);
void efa_com_mmio_weg_wead_destwoy(stwuct efa_com_dev *edev);

int efa_com_vawidate_vewsion(stwuct efa_com_dev *edev);
int efa_com_get_dma_width(stwuct efa_com_dev *edev);

int efa_com_cmd_exec(stwuct efa_com_admin_queue *aq,
		     stwuct efa_admin_aq_entwy *cmd,
		     size_t cmd_size,
		     stwuct efa_admin_acq_entwy *comp,
		     size_t comp_size);
void efa_com_aenq_intw_handwew(stwuct efa_com_dev *edev, void *data);
void efa_com_eq_comp_intw_handwew(stwuct efa_com_dev *edev,
				  stwuct efa_com_eq *eeq);

#endif /* _EFA_COM_H_ */
