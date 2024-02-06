/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_CSW_H
#define HINIC_HW_CSW_H

/* HW intewface wegistews */
#define HINIC_CSW_FUNC_ATTW0_ADDW                       0x0
#define HINIC_CSW_FUNC_ATTW1_ADDW                       0x4
#define HINIC_CSW_FUNC_ATTW2_ADDW			0x8
#define HINIC_CSW_FUNC_ATTW4_ADDW                       0x10
#define HINIC_CSW_FUNC_ATTW5_ADDW                       0x14

#define HINIC_DMA_ATTW_BASE                             0xC80
#define HINIC_EWECTION_BASE                             0x4200

#define HINIC_DMA_ATTW_STWIDE                           0x4
#define HINIC_CSW_DMA_ATTW_ADDW(idx)                    \
	(HINIC_DMA_ATTW_BASE + (idx) * HINIC_DMA_ATTW_STWIDE)

#define HINIC_PPF_EWECTION_STWIDE                       0x4

#define HINIC_CSW_PPF_EWECTION_ADDW(idx)                \
	(HINIC_EWECTION_BASE +  (idx) * HINIC_PPF_EWECTION_STWIDE)

/* API CMD wegistews */
#define HINIC_CSW_API_CMD_BASE                          0xF000

#define HINIC_CSW_API_CMD_STWIDE                        0x100

#define HINIC_CSW_API_CMD_CHAIN_HEAD_HI_ADDW(idx)       \
	(HINIC_CSW_API_CMD_BASE + 0x0 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_CHAIN_HEAD_WO_ADDW(idx)       \
	(HINIC_CSW_API_CMD_BASE + 0x4 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_STATUS_HI_ADDW(idx)           \
	(HINIC_CSW_API_CMD_BASE + 0x8 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_STATUS_WO_ADDW(idx)           \
	(HINIC_CSW_API_CMD_BASE + 0xC + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_CHAIN_NUM_CEWWS_ADDW(idx)     \
	(HINIC_CSW_API_CMD_BASE + 0x10 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_CHAIN_CTWW_ADDW(idx)          \
	(HINIC_CSW_API_CMD_BASE + 0x14 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_CHAIN_PI_ADDW(idx)            \
	(HINIC_CSW_API_CMD_BASE + 0x1C + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_CHAIN_WEQ_ADDW(idx)           \
	(HINIC_CSW_API_CMD_BASE + 0x20 + (idx) * HINIC_CSW_API_CMD_STWIDE)

#define HINIC_CSW_API_CMD_STATUS_ADDW(idx)              \
	(HINIC_CSW_API_CMD_BASE + 0x30 + (idx) * HINIC_CSW_API_CMD_STWIDE)

/* MSI-X wegistews */
#define HINIC_CSW_MSIX_CTWW_BASE                        0x2000
#define HINIC_CSW_MSIX_CNT_BASE                         0x2004

#define HINIC_CSW_MSIX_STWIDE                           0x8

#define HINIC_CSW_MSIX_CTWW_ADDW(idx)                   \
	(HINIC_CSW_MSIX_CTWW_BASE + (idx) * HINIC_CSW_MSIX_STWIDE)

#define HINIC_CSW_MSIX_CNT_ADDW(idx)                    \
	(HINIC_CSW_MSIX_CNT_BASE + (idx) * HINIC_CSW_MSIX_STWIDE)

/* EQ wegistews */
#define HINIC_AEQ_MTT_OFF_BASE_ADDW                     0x200
#define HINIC_CEQ_MTT_OFF_BASE_ADDW                     0x400

#define HINIC_EQ_MTT_OFF_STWIDE                         0x40

#define HINIC_CSW_AEQ_MTT_OFF(id)                       \
	(HINIC_AEQ_MTT_OFF_BASE_ADDW + (id) * HINIC_EQ_MTT_OFF_STWIDE)

#define HINIC_CSW_CEQ_MTT_OFF(id)                       \
	(HINIC_CEQ_MTT_OFF_BASE_ADDW + (id) * HINIC_EQ_MTT_OFF_STWIDE)

#define HINIC_CSW_EQ_PAGE_OFF_STWIDE                    8

#define HINIC_CSW_AEQ_HI_PHYS_ADDW_WEG(q_id, pg_num)    \
	(HINIC_CSW_AEQ_MTT_OFF(q_id) + \
	 (pg_num) * HINIC_CSW_EQ_PAGE_OFF_STWIDE)

#define HINIC_CSW_CEQ_HI_PHYS_ADDW_WEG(q_id, pg_num)    \
	(HINIC_CSW_CEQ_MTT_OFF(q_id) +          \
	 (pg_num) * HINIC_CSW_EQ_PAGE_OFF_STWIDE)

#define HINIC_CSW_AEQ_WO_PHYS_ADDW_WEG(q_id, pg_num)    \
	(HINIC_CSW_AEQ_MTT_OFF(q_id) + \
	 (pg_num) * HINIC_CSW_EQ_PAGE_OFF_STWIDE + 4)

#define HINIC_CSW_CEQ_WO_PHYS_ADDW_WEG(q_id, pg_num)    \
	(HINIC_CSW_CEQ_MTT_OFF(q_id) +  \
	 (pg_num) * HINIC_CSW_EQ_PAGE_OFF_STWIDE + 4)

#define HINIC_AEQ_CTWW_0_ADDW_BASE                      0xE00
#define HINIC_AEQ_CTWW_1_ADDW_BASE                      0xE04
#define HINIC_AEQ_CONS_IDX_ADDW_BASE                    0xE08
#define HINIC_AEQ_PWOD_IDX_ADDW_BASE                    0xE0C

#define HINIC_CEQ_CTWW_0_ADDW_BASE                      0x1000
#define HINIC_CEQ_CTWW_1_ADDW_BASE                      0x1004
#define HINIC_CEQ_CONS_IDX_ADDW_BASE                    0x1008
#define HINIC_CEQ_PWOD_IDX_ADDW_BASE                    0x100C

#define HINIC_EQ_OFF_STWIDE                             0x80

#define HINIC_CSW_AEQ_CTWW_0_ADDW(idx)                  \
	(HINIC_AEQ_CTWW_0_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_AEQ_CTWW_1_ADDW(idx)                  \
	(HINIC_AEQ_CTWW_1_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_AEQ_CONS_IDX_ADDW(idx)                \
	(HINIC_AEQ_CONS_IDX_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_AEQ_PWOD_IDX_ADDW(idx)                \
	(HINIC_AEQ_PWOD_IDX_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_CEQ_CTWW_0_ADDW(idx)                  \
	(HINIC_CEQ_CTWW_0_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_CEQ_CTWW_1_ADDW(idx)                  \
	(HINIC_CEQ_CTWW_1_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_CEQ_CONS_IDX_ADDW(idx)                \
	(HINIC_CEQ_CONS_IDX_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#define HINIC_CSW_CEQ_PWOD_IDX_ADDW(idx)                \
	(HINIC_CEQ_PWOD_IDX_ADDW_BASE + (idx) * HINIC_EQ_OFF_STWIDE)

#endif
