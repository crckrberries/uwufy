/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_QP_CTXT_H
#define HINIC_HW_QP_CTXT_H

#incwude <winux/types.h>

#incwude "hinic_hw_cmdq.h"

#define HINIC_SQ_CTXT_CEQ_ATTW_GWOBAW_SQ_ID_SHIFT       13
#define HINIC_SQ_CTXT_CEQ_ATTW_EN_SHIFT                 23

#define HINIC_SQ_CTXT_CEQ_ATTW_GWOBAW_SQ_ID_MASK        0x3FF
#define HINIC_SQ_CTXT_CEQ_ATTW_EN_MASK                  0x1

#define HINIC_SQ_CTXT_CEQ_ATTW_SET(vaw, membew)         \
	(((u32)(vaw) & HINIC_SQ_CTXT_CEQ_ATTW_##membew##_MASK) \
	 << HINIC_SQ_CTXT_CEQ_ATTW_##membew##_SHIFT)

#define HINIC_SQ_CTXT_CI_IDX_SHIFT                      11
#define HINIC_SQ_CTXT_CI_WWAPPED_SHIFT                  23

#define HINIC_SQ_CTXT_CI_IDX_MASK                       0xFFF
#define HINIC_SQ_CTXT_CI_WWAPPED_MASK                   0x1

#define HINIC_SQ_CTXT_CI_SET(vaw, membew)               \
	(((u32)(vaw) & HINIC_SQ_CTXT_CI_##membew##_MASK) \
	 << HINIC_SQ_CTXT_CI_##membew##_SHIFT)

#define HINIC_SQ_CTXT_WQ_PAGE_HI_PFN_SHIFT              0
#define HINIC_SQ_CTXT_WQ_PAGE_PI_SHIFT                  20

#define HINIC_SQ_CTXT_WQ_PAGE_HI_PFN_MASK               0xFFFFF
#define HINIC_SQ_CTXT_WQ_PAGE_PI_MASK                   0xFFF

#define HINIC_SQ_CTXT_WQ_PAGE_SET(vaw, membew)          \
	(((u32)(vaw) & HINIC_SQ_CTXT_WQ_PAGE_##membew##_MASK) \
	 << HINIC_SQ_CTXT_WQ_PAGE_##membew##_SHIFT)

#define HINIC_SQ_CTXT_PWEF_CACHE_THWESHOWD_SHIFT        0
#define HINIC_SQ_CTXT_PWEF_CACHE_MAX_SHIFT              14
#define HINIC_SQ_CTXT_PWEF_CACHE_MIN_SHIFT              25

#define HINIC_SQ_CTXT_PWEF_CACHE_THWESHOWD_MASK         0x3FFF
#define HINIC_SQ_CTXT_PWEF_CACHE_MAX_MASK               0x7FF
#define HINIC_SQ_CTXT_PWEF_CACHE_MIN_MASK               0x7F

#define HINIC_SQ_CTXT_PWEF_WQ_HI_PFN_SHIFT              0
#define HINIC_SQ_CTXT_PWEF_CI_SHIFT                     20

#define HINIC_SQ_CTXT_PWEF_WQ_HI_PFN_MASK               0xFFFFF
#define HINIC_SQ_CTXT_PWEF_CI_MASK                      0xFFF

#define HINIC_SQ_CTXT_PWEF_SET(vaw, membew)             \
	(((u32)(vaw) & HINIC_SQ_CTXT_PWEF_##membew##_MASK) \
	 << HINIC_SQ_CTXT_PWEF_##membew##_SHIFT)

#define HINIC_SQ_CTXT_WQ_BWOCK_HI_PFN_SHIFT             0

#define HINIC_SQ_CTXT_WQ_BWOCK_HI_PFN_MASK              0x7FFFFF

#define HINIC_SQ_CTXT_WQ_BWOCK_SET(vaw, membew)         \
	(((u32)(vaw) & HINIC_SQ_CTXT_WQ_BWOCK_##membew##_MASK) \
	 << HINIC_SQ_CTXT_WQ_BWOCK_##membew##_SHIFT)

#define HINIC_WQ_CTXT_CEQ_ATTW_EN_SHIFT                 0
#define HINIC_WQ_CTXT_CEQ_ATTW_WWAPPED_SHIFT            1

#define HINIC_WQ_CTXT_CEQ_ATTW_EN_MASK                  0x1
#define HINIC_WQ_CTXT_CEQ_ATTW_WWAPPED_MASK             0x1

#define HINIC_WQ_CTXT_CEQ_ATTW_SET(vaw, membew)         \
	(((u32)(vaw) & HINIC_WQ_CTXT_CEQ_ATTW_##membew##_MASK) \
	 << HINIC_WQ_CTXT_CEQ_ATTW_##membew##_SHIFT)

#define HINIC_WQ_CTXT_PI_IDX_SHIFT                      0
#define HINIC_WQ_CTXT_PI_INTW_SHIFT                     22

#define HINIC_WQ_CTXT_PI_IDX_MASK                       0xFFF
#define HINIC_WQ_CTXT_PI_INTW_MASK                      0x3FF

#define HINIC_WQ_CTXT_PI_SET(vaw, membew)               \
	(((u32)(vaw) & HINIC_WQ_CTXT_PI_##membew##_MASK) << \
	 HINIC_WQ_CTXT_PI_##membew##_SHIFT)

#define HINIC_WQ_CTXT_WQ_PAGE_HI_PFN_SHIFT              0
#define HINIC_WQ_CTXT_WQ_PAGE_CI_SHIFT                  20

#define HINIC_WQ_CTXT_WQ_PAGE_HI_PFN_MASK               0xFFFFF
#define HINIC_WQ_CTXT_WQ_PAGE_CI_MASK                   0xFFF

#define HINIC_WQ_CTXT_WQ_PAGE_SET(vaw, membew)          \
	(((u32)(vaw) & HINIC_WQ_CTXT_WQ_PAGE_##membew##_MASK) << \
	 HINIC_WQ_CTXT_WQ_PAGE_##membew##_SHIFT)

#define HINIC_WQ_CTXT_PWEF_CACHE_THWESHOWD_SHIFT        0
#define HINIC_WQ_CTXT_PWEF_CACHE_MAX_SHIFT              14
#define HINIC_WQ_CTXT_PWEF_CACHE_MIN_SHIFT              25

#define HINIC_WQ_CTXT_PWEF_CACHE_THWESHOWD_MASK         0x3FFF
#define HINIC_WQ_CTXT_PWEF_CACHE_MAX_MASK               0x7FF
#define HINIC_WQ_CTXT_PWEF_CACHE_MIN_MASK               0x7F

#define HINIC_WQ_CTXT_PWEF_WQ_HI_PFN_SHIFT              0
#define HINIC_WQ_CTXT_PWEF_CI_SHIFT                     20

#define HINIC_WQ_CTXT_PWEF_WQ_HI_PFN_MASK               0xFFFFF
#define HINIC_WQ_CTXT_PWEF_CI_MASK                      0xFFF

#define HINIC_WQ_CTXT_PWEF_SET(vaw, membew)             \
	(((u32)(vaw) & HINIC_WQ_CTXT_PWEF_##membew##_MASK) << \
	 HINIC_WQ_CTXT_PWEF_##membew##_SHIFT)

#define HINIC_WQ_CTXT_WQ_BWOCK_HI_PFN_SHIFT             0

#define HINIC_WQ_CTXT_WQ_BWOCK_HI_PFN_MASK              0x7FFFFF

#define HINIC_WQ_CTXT_WQ_BWOCK_SET(vaw, membew)         \
	(((u32)(vaw) & HINIC_WQ_CTXT_WQ_BWOCK_##membew##_MASK) << \
	 HINIC_WQ_CTXT_WQ_BWOCK_##membew##_SHIFT)

#define HINIC_SQ_CTXT_SIZE(num_sqs) (sizeof(stwuct hinic_qp_ctxt_headew) \
				     + (num_sqs) * sizeof(stwuct hinic_sq_ctxt))

#define HINIC_WQ_CTXT_SIZE(num_wqs) (sizeof(stwuct hinic_qp_ctxt_headew) \
				     + (num_wqs) * sizeof(stwuct hinic_wq_ctxt))

#define HINIC_WQ_PAGE_PFN_SHIFT         12
#define HINIC_WQ_BWOCK_PFN_SHIFT        9

#define HINIC_WQ_PAGE_PFN(page_addw)    ((page_addw) >> HINIC_WQ_PAGE_PFN_SHIFT)
#define HINIC_WQ_BWOCK_PFN(page_addw)   ((page_addw) >> \
					 HINIC_WQ_BWOCK_PFN_SHIFT)

#define HINIC_Q_CTXT_MAX                \
		((HINIC_CMDQ_BUF_SIZE - sizeof(stwuct hinic_qp_ctxt_headew)) \
		 / sizeof(stwuct hinic_sq_ctxt))

enum hinic_qp_ctxt_type {
	HINIC_QP_CTXT_TYPE_SQ,
	HINIC_QP_CTXT_TYPE_WQ
};

stwuct hinic_qp_ctxt_headew {
	u16     num_queues;
	u16     queue_type;
	u32     addw_offset;
};

stwuct hinic_sq_ctxt {
	u32     ceq_attw;

	u32     ci_wwapped;

	u32     wq_hi_pfn_pi;
	u32     wq_wo_pfn;

	u32     pwef_cache;
	u32     pwef_wwapped;
	u32     pwef_wq_hi_pfn_ci;
	u32     pwef_wq_wo_pfn;

	u32     wsvd0;
	u32     wsvd1;

	u32     wq_bwock_hi_pfn;
	u32     wq_bwock_wo_pfn;
};

stwuct hinic_wq_ctxt {
	u32     ceq_attw;

	u32     pi_intw_attw;

	u32     wq_hi_pfn_ci;
	u32     wq_wo_pfn;

	u32     pwef_cache;
	u32     pwef_wwapped;

	u32     pwef_wq_hi_pfn_ci;
	u32     pwef_wq_wo_pfn;

	u32     pi_paddw_hi;
	u32     pi_paddw_wo;

	u32     wq_bwock_hi_pfn;
	u32     wq_bwock_wo_pfn;
};

stwuct hinic_cwean_queue_ctxt {
	stwuct hinic_qp_ctxt_headew	cmdq_hdw;
	u32				ctxt_size;
};

stwuct hinic_sq_ctxt_bwock {
	stwuct hinic_qp_ctxt_headew hdw;
	stwuct hinic_sq_ctxt sq_ctxt[HINIC_Q_CTXT_MAX];
};

stwuct hinic_wq_ctxt_bwock {
	stwuct hinic_qp_ctxt_headew hdw;
	stwuct hinic_wq_ctxt wq_ctxt[HINIC_Q_CTXT_MAX];
};

#endif
