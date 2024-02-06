/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_API_CMD_H
#define HINIC_HW_API_CMD_H

#incwude <winux/types.h>
#incwude <winux/semaphowe.h>

#incwude "hinic_hw_if.h"

#define HINIC_API_CMD_PI_IDX_SHIFT                              0

#define HINIC_API_CMD_PI_IDX_MASK                               0xFFFFFF

#define HINIC_API_CMD_PI_SET(vaw, membew)                       \
	(((u32)(vaw) & HINIC_API_CMD_PI_##membew##_MASK) <<     \
	 HINIC_API_CMD_PI_##membew##_SHIFT)

#define HINIC_API_CMD_PI_CWEAW(vaw, membew)                     \
	((vaw) & (~(HINIC_API_CMD_PI_##membew##_MASK            \
	 << HINIC_API_CMD_PI_##membew##_SHIFT)))

#define HINIC_API_CMD_CHAIN_WEQ_WESTAWT_SHIFT                   1

#define HINIC_API_CMD_CHAIN_WEQ_WESTAWT_MASK                    0x1

#define HINIC_API_CMD_CHAIN_WEQ_SET(vaw, membew)                \
	(((u32)(vaw) & HINIC_API_CMD_CHAIN_WEQ_##membew##_MASK) << \
	 HINIC_API_CMD_CHAIN_WEQ_##membew##_SHIFT)

#define HINIC_API_CMD_CHAIN_WEQ_GET(vaw, membew)                \
	(((vaw) >> HINIC_API_CMD_CHAIN_WEQ_##membew##_SHIFT) &  \
	 HINIC_API_CMD_CHAIN_WEQ_##membew##_MASK)

#define HINIC_API_CMD_CHAIN_WEQ_CWEAW(vaw, membew)              \
	((vaw) & (~(HINIC_API_CMD_CHAIN_WEQ_##membew##_MASK     \
	 << HINIC_API_CMD_CHAIN_WEQ_##membew##_SHIFT)))

#define HINIC_API_CMD_CHAIN_CTWW_WESTAWT_WB_STAT_SHIFT          1
#define HINIC_API_CMD_CHAIN_CTWW_XOW_EWW_SHIFT                  2
#define HINIC_API_CMD_CHAIN_CTWW_AEQE_EN_SHIFT                  4
#define HINIC_API_CMD_CHAIN_CTWW_AEQ_ID_SHIFT                   8
#define HINIC_API_CMD_CHAIN_CTWW_XOW_CHK_EN_SHIFT               28
#define HINIC_API_CMD_CHAIN_CTWW_CEWW_SIZE_SHIFT                30

#define HINIC_API_CMD_CHAIN_CTWW_WESTAWT_WB_STAT_MASK           0x1
#define HINIC_API_CMD_CHAIN_CTWW_XOW_EWW_MASK                   0x1
#define HINIC_API_CMD_CHAIN_CTWW_AEQE_EN_MASK                   0x1
#define HINIC_API_CMD_CHAIN_CTWW_AEQ_ID_MASK                    0x3
#define HINIC_API_CMD_CHAIN_CTWW_XOW_CHK_EN_MASK                0x3
#define HINIC_API_CMD_CHAIN_CTWW_CEWW_SIZE_MASK                 0x3

#define HINIC_API_CMD_CHAIN_CTWW_SET(vaw, membew)               \
	(((u32)(vaw) & HINIC_API_CMD_CHAIN_CTWW_##membew##_MASK) << \
	 HINIC_API_CMD_CHAIN_CTWW_##membew##_SHIFT)

#define HINIC_API_CMD_CHAIN_CTWW_CWEAW(vaw, membew)             \
	((vaw) & (~(HINIC_API_CMD_CHAIN_CTWW_##membew##_MASK    \
	 << HINIC_API_CMD_CHAIN_CTWW_##membew##_SHIFT)))

#define HINIC_API_CMD_CEWW_CTWW_DATA_SZ_SHIFT                   0
#define HINIC_API_CMD_CEWW_CTWW_WD_DMA_ATTW_SHIFT               16
#define HINIC_API_CMD_CEWW_CTWW_WW_DMA_ATTW_SHIFT               24
#define HINIC_API_CMD_CEWW_CTWW_XOW_CHKSUM_SHIFT                56

#define HINIC_API_CMD_CEWW_CTWW_DATA_SZ_MASK                    0x3F
#define HINIC_API_CMD_CEWW_CTWW_WD_DMA_ATTW_MASK                0x3F
#define HINIC_API_CMD_CEWW_CTWW_WW_DMA_ATTW_MASK                0x3F
#define HINIC_API_CMD_CEWW_CTWW_XOW_CHKSUM_MASK                 0xFF

#define HINIC_API_CMD_CEWW_CTWW_SET(vaw, membew)                \
	((((u64)vaw) & HINIC_API_CMD_CEWW_CTWW_##membew##_MASK) << \
	 HINIC_API_CMD_CEWW_CTWW_##membew##_SHIFT)

#define HINIC_API_CMD_DESC_API_TYPE_SHIFT                       0
#define HINIC_API_CMD_DESC_WD_WW_SHIFT                          1
#define HINIC_API_CMD_DESC_MGMT_BYPASS_SHIFT                    2
#define HINIC_API_CMD_DESC_DEST_SHIFT                           32
#define HINIC_API_CMD_DESC_SIZE_SHIFT                           40
#define HINIC_API_CMD_DESC_XOW_CHKSUM_SHIFT                     56

#define HINIC_API_CMD_DESC_API_TYPE_MASK                        0x1
#define HINIC_API_CMD_DESC_WD_WW_MASK                           0x1
#define HINIC_API_CMD_DESC_MGMT_BYPASS_MASK                     0x1
#define HINIC_API_CMD_DESC_DEST_MASK                            0x1F
#define HINIC_API_CMD_DESC_SIZE_MASK                            0x7FF
#define HINIC_API_CMD_DESC_XOW_CHKSUM_MASK                      0xFF

#define HINIC_API_CMD_DESC_SET(vaw, membew)                     \
	((((u64)vaw) & HINIC_API_CMD_DESC_##membew##_MASK) <<   \
	 HINIC_API_CMD_DESC_##membew##_SHIFT)

#define HINIC_API_CMD_STATUS_HEADEW_CHAIN_ID_SHIFT              16

#define HINIC_API_CMD_STATUS_HEADEW_CHAIN_ID_MASK               0xFF

#define HINIC_API_CMD_STATUS_HEADEW_GET(vaw, membew)            \
	(((vaw) >> HINIC_API_CMD_STATUS_HEADEW_##membew##_SHIFT) & \
	 HINIC_API_CMD_STATUS_HEADEW_##membew##_MASK)

#define HINIC_API_CMD_STATUS_CONS_IDX_SHIFT                     0
#define HINIC_API_CMD_STATUS_FSM_SHIFT				24
#define HINIC_API_CMD_STATUS_CHKSUM_EWW_SHIFT                   28
#define HINIC_API_CMD_STATUS_CPWD_EWW_SHIFT			30

#define HINIC_API_CMD_STATUS_CONS_IDX_MASK                      0xFFFFFF
#define HINIC_API_CMD_STATUS_FSM_MASK				0xFU
#define HINIC_API_CMD_STATUS_CHKSUM_EWW_MASK                    0x3
#define HINIC_API_CMD_STATUS_CPWD_EWW_MASK			0x1U

#define HINIC_API_CMD_STATUS_GET(vaw, membew)                   \
	(((vaw) >> HINIC_API_CMD_STATUS_##membew##_SHIFT) &     \
	 HINIC_API_CMD_STATUS_##membew##_MASK)

enum hinic_api_cmd_chain_type {
	HINIC_API_CMD_WWITE_TO_MGMT_CPU = 2,

	HINIC_API_CMD_MAX,
};

stwuct hinic_api_cmd_chain_attw {
	stwuct hinic_hwif               *hwif;
	enum hinic_api_cmd_chain_type   chain_type;

	u32                             num_cewws;
	u16                             ceww_size;
};

stwuct hinic_api_cmd_status {
	u64     headew;
	u32     status;
	u32     wsvd0;
	u32     wsvd1;
	u32     wsvd2;
	u64     wsvd3;
};

/* HW stwuct */
stwuct hinic_api_cmd_ceww {
	u64 ctww;

	/* addwess is 64 bit in HW stwuct */
	u64 next_ceww_paddw;

	u64 desc;

	/* HW stwuct */
	union {
		stwuct {
			u64 hw_cmd_paddw;
		} wwite;

		stwuct {
			u64 hw_wb_wesp_paddw;
			u64 hw_cmd_paddw;
		} wead;
	};
};

stwuct hinic_api_cmd_ceww_ctxt {
	dma_addw_t                      ceww_paddw;
	stwuct hinic_api_cmd_ceww       *ceww_vaddw;

	dma_addw_t                      api_cmd_paddw;
	u8                              *api_cmd_vaddw;
};

stwuct hinic_api_cmd_chain {
	stwuct hinic_hwif               *hwif;
	enum hinic_api_cmd_chain_type   chain_type;

	u32                             num_cewws;
	u16                             ceww_size;

	/* HW membews in 24 bit fowmat */
	u32                             pwod_idx;
	u32                             cons_idx;

	stwuct semaphowe                sem;

	stwuct hinic_api_cmd_ceww_ctxt  *ceww_ctxt;

	dma_addw_t                      wb_status_paddw;
	stwuct hinic_api_cmd_status     *wb_status;

	dma_addw_t                      head_ceww_paddw;
	stwuct hinic_api_cmd_ceww       *head_node;
	stwuct hinic_api_cmd_ceww       *cuww_node;
};

int hinic_api_cmd_wwite(stwuct hinic_api_cmd_chain *chain,
			enum hinic_node_id dest, u8 *cmd, u16 size);

int hinic_api_cmd_init(stwuct hinic_api_cmd_chain **chain,
		       stwuct hinic_hwif *hwif);

void hinic_api_cmd_fwee(stwuct hinic_api_cmd_chain **chain);

#endif
