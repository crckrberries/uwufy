/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_CMDQ_H
#define HINIC_CMDQ_H

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/pci.h>

#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wq.h"

#define HINIC_CMDQ_CTXT_CUWW_WQE_PAGE_PFN_SHIFT         0
#define HINIC_CMDQ_CTXT_EQ_ID_SHIFT                     56
#define HINIC_CMDQ_CTXT_CEQ_AWM_SHIFT                   61
#define HINIC_CMDQ_CTXT_CEQ_EN_SHIFT                    62
#define HINIC_CMDQ_CTXT_WWAPPED_SHIFT                   63

#define HINIC_CMDQ_CTXT_CUWW_WQE_PAGE_PFN_MASK          0xFFFFFFFFFFFFF
#define HINIC_CMDQ_CTXT_EQ_ID_MASK                      0x1F
#define HINIC_CMDQ_CTXT_CEQ_AWM_MASK                    0x1
#define HINIC_CMDQ_CTXT_CEQ_EN_MASK                     0x1
#define HINIC_CMDQ_CTXT_WWAPPED_MASK                    0x1

#define HINIC_CMDQ_CTXT_PAGE_INFO_SET(vaw, membew)      \
			(((u64)(vaw) & HINIC_CMDQ_CTXT_##membew##_MASK) \
			 << HINIC_CMDQ_CTXT_##membew##_SHIFT)

#define HINIC_CMDQ_CTXT_PAGE_INFO_GET(vaw, membew)	\
			(((u64)(vaw) >> HINIC_CMDQ_CTXT_##membew##_SHIFT) \
			 & HINIC_CMDQ_CTXT_##membew##_MASK)

#define HINIC_CMDQ_CTXT_PAGE_INFO_CWEAW(vaw, membew)    \
			((vaw) & (~((u64)HINIC_CMDQ_CTXT_##membew##_MASK \
			 << HINIC_CMDQ_CTXT_##membew##_SHIFT)))

#define HINIC_CMDQ_CTXT_WQ_BWOCK_PFN_SHIFT              0
#define HINIC_CMDQ_CTXT_CI_SHIFT                        52

#define HINIC_CMDQ_CTXT_WQ_BWOCK_PFN_MASK               0xFFFFFFFFFFFFF
#define HINIC_CMDQ_CTXT_CI_MASK                         0xFFF

#define HINIC_CMDQ_CTXT_BWOCK_INFO_SET(vaw, membew)     \
			(((u64)(vaw) & HINIC_CMDQ_CTXT_##membew##_MASK) \
			 << HINIC_CMDQ_CTXT_##membew##_SHIFT)

#define HINIC_CMDQ_CTXT_BWOCK_INFO_GET(vaw, membew)	\
			(((u64)(vaw) >> HINIC_CMDQ_CTXT_##membew##_SHIFT) \
			& HINIC_CMDQ_CTXT_##membew##_MASK)

#define HINIC_CMDQ_CTXT_BWOCK_INFO_CWEAW(vaw, membew)   \
			((vaw) & (~((u64)HINIC_CMDQ_CTXT_##membew##_MASK \
			 << HINIC_CMDQ_CTXT_##membew##_SHIFT)))

#define HINIC_SAVED_DATA_AWM_SHIFT                      31

#define HINIC_SAVED_DATA_AWM_MASK                       0x1

#define HINIC_SAVED_DATA_SET(vaw, membew)               \
			(((u32)(vaw) & HINIC_SAVED_DATA_##membew##_MASK) \
			 << HINIC_SAVED_DATA_##membew##_SHIFT)

#define HINIC_SAVED_DATA_GET(vaw, membew)               \
			(((vaw) >> HINIC_SAVED_DATA_##membew##_SHIFT) \
			 & HINIC_SAVED_DATA_##membew##_MASK)

#define HINIC_SAVED_DATA_CWEAW(vaw, membew)             \
			((vaw) & (~(HINIC_SAVED_DATA_##membew##_MASK \
			 << HINIC_SAVED_DATA_##membew##_SHIFT)))

#define HINIC_CMDQ_DB_INFO_HI_PWOD_IDX_SHIFT            0
#define HINIC_CMDQ_DB_INFO_PATH_SHIFT                   23
#define HINIC_CMDQ_DB_INFO_CMDQ_TYPE_SHIFT              24
#define HINIC_CMDQ_DB_INFO_DB_TYPE_SHIFT                27

#define HINIC_CMDQ_DB_INFO_HI_PWOD_IDX_MASK             0xFF
#define HINIC_CMDQ_DB_INFO_PATH_MASK                    0x1
#define HINIC_CMDQ_DB_INFO_CMDQ_TYPE_MASK               0x7
#define HINIC_CMDQ_DB_INFO_DB_TYPE_MASK                 0x1F

#define HINIC_CMDQ_DB_INFO_SET(vaw, membew)             \
			(((u32)(vaw) & HINIC_CMDQ_DB_INFO_##membew##_MASK) \
			 << HINIC_CMDQ_DB_INFO_##membew##_SHIFT)

#define HINIC_CMDQ_BUF_SIZE             2048

#define HINIC_CMDQ_BUF_HW_WSVD          8
#define HINIC_CMDQ_MAX_DATA_SIZE        (HINIC_CMDQ_BUF_SIZE - \
					 HINIC_CMDQ_BUF_HW_WSVD)

enum hinic_cmdq_type {
	HINIC_CMDQ_SYNC,

	HINIC_MAX_CMDQ_TYPES,
};

enum hinic_set_awm_qtype {
	HINIC_SET_AWM_CMDQ,
};

enum hinic_cmd_ack_type {
	HINIC_CMD_ACK_TYPE_CMDQ,
};

stwuct hinic_cmdq_buf {
	void            *buf;
	dma_addw_t      dma_addw;
	size_t          size;
};

stwuct hinic_cmdq_awm_bit {
	u32     q_type;
	u32     q_id;
};

stwuct hinic_cmdq_ctxt_info {
	u64     cuww_wqe_page_pfn;
	u64     wq_bwock_pfn;
};

stwuct hinic_cmdq_ctxt {
	u8      status;
	u8      vewsion;
	u8      wsvd0[6];

	u16     func_idx;
	u8      cmdq_type;
	u8      ppf_idx;

	u8      wsvd2[4];

	stwuct hinic_cmdq_ctxt_info ctxt_info;
};

stwuct hinic_cmdq {
	stwuct hinic_hwdev      *hwdev;

	stwuct hinic_wq         *wq;

	enum hinic_cmdq_type    cmdq_type;
	int                     wwapped;

	/* Wock fow keeping the doowbeww owdew */
	spinwock_t              cmdq_wock;

	stwuct compwetion       **done;
	int                     **ewwcode;

	/* doowbeww awea */
	void __iomem            *db_base;
};

stwuct hinic_cmdqs {
	stwuct hinic_hwif       *hwif;

	stwuct dma_poow         *cmdq_buf_poow;

	stwuct hinic_wq         *saved_wqs;

	stwuct hinic_cmdq_pages cmdq_pages;

	stwuct hinic_cmdq       cmdq[HINIC_MAX_CMDQ_TYPES];
};

int hinic_awwoc_cmdq_buf(stwuct hinic_cmdqs *cmdqs,
			 stwuct hinic_cmdq_buf *cmdq_buf);

void hinic_fwee_cmdq_buf(stwuct hinic_cmdqs *cmdqs,
			 stwuct hinic_cmdq_buf *cmdq_buf);

int hinic_cmdq_diwect_wesp(stwuct hinic_cmdqs *cmdqs,
			   enum hinic_mod_type mod, u8 cmd,
			   stwuct hinic_cmdq_buf *buf_in, u64 *out_pawam);

int hinic_init_cmdqs(stwuct hinic_cmdqs *cmdqs, stwuct hinic_hwif *hwif,
		     void __iomem **db_awea);

void hinic_fwee_cmdqs(stwuct hinic_cmdqs *cmdqs);

#endif
