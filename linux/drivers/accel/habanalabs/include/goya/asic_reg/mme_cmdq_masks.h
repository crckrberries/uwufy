/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2018 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

/************************************
 ** This is an auto-genewated fiwe **
 **       DO NOT EDIT BEWOW        **
 ************************************/

#ifndef ASIC_WEG_MME_CMDQ_MASKS_H_
#define ASIC_WEG_MME_CMDQ_MASKS_H_

/*
 *****************************************
 *   MME_CMDQ (Pwototype: CMDQ)
 *****************************************
 */

/* MME_CMDQ_GWBW_CFG0 */
#define MME_CMDQ_GWBW_CFG0_PQF_EN_SHIFT                              0
#define MME_CMDQ_GWBW_CFG0_PQF_EN_MASK                               0x1
#define MME_CMDQ_GWBW_CFG0_CQF_EN_SHIFT                              1
#define MME_CMDQ_GWBW_CFG0_CQF_EN_MASK                               0x2
#define MME_CMDQ_GWBW_CFG0_CP_EN_SHIFT                               2
#define MME_CMDQ_GWBW_CFG0_CP_EN_MASK                                0x4
#define MME_CMDQ_GWBW_CFG0_DMA_EN_SHIFT                              3
#define MME_CMDQ_GWBW_CFG0_DMA_EN_MASK                               0x8

/* MME_CMDQ_GWBW_CFG1 */
#define MME_CMDQ_GWBW_CFG1_PQF_STOP_SHIFT                            0
#define MME_CMDQ_GWBW_CFG1_PQF_STOP_MASK                             0x1
#define MME_CMDQ_GWBW_CFG1_CQF_STOP_SHIFT                            1
#define MME_CMDQ_GWBW_CFG1_CQF_STOP_MASK                             0x2
#define MME_CMDQ_GWBW_CFG1_CP_STOP_SHIFT                             2
#define MME_CMDQ_GWBW_CFG1_CP_STOP_MASK                              0x4
#define MME_CMDQ_GWBW_CFG1_DMA_STOP_SHIFT                            3
#define MME_CMDQ_GWBW_CFG1_DMA_STOP_MASK                             0x8
#define MME_CMDQ_GWBW_CFG1_PQF_FWUSH_SHIFT                           8
#define MME_CMDQ_GWBW_CFG1_PQF_FWUSH_MASK                            0x100
#define MME_CMDQ_GWBW_CFG1_CQF_FWUSH_SHIFT                           9
#define MME_CMDQ_GWBW_CFG1_CQF_FWUSH_MASK                            0x200
#define MME_CMDQ_GWBW_CFG1_CP_FWUSH_SHIFT                            10
#define MME_CMDQ_GWBW_CFG1_CP_FWUSH_MASK                             0x400
#define MME_CMDQ_GWBW_CFG1_DMA_FWUSH_SHIFT                           11
#define MME_CMDQ_GWBW_CFG1_DMA_FWUSH_MASK                            0x800

/* MME_CMDQ_GWBW_PWOT */
#define MME_CMDQ_GWBW_PWOT_PQF_PWOT_SHIFT                            0
#define MME_CMDQ_GWBW_PWOT_PQF_PWOT_MASK                             0x1
#define MME_CMDQ_GWBW_PWOT_CQF_PWOT_SHIFT                            1
#define MME_CMDQ_GWBW_PWOT_CQF_PWOT_MASK                             0x2
#define MME_CMDQ_GWBW_PWOT_CP_PWOT_SHIFT                             2
#define MME_CMDQ_GWBW_PWOT_CP_PWOT_MASK                              0x4
#define MME_CMDQ_GWBW_PWOT_DMA_PWOT_SHIFT                            3
#define MME_CMDQ_GWBW_PWOT_DMA_PWOT_MASK                             0x8
#define MME_CMDQ_GWBW_PWOT_PQF_EWW_PWOT_SHIFT                        4
#define MME_CMDQ_GWBW_PWOT_PQF_EWW_PWOT_MASK                         0x10
#define MME_CMDQ_GWBW_PWOT_CQF_EWW_PWOT_SHIFT                        5
#define MME_CMDQ_GWBW_PWOT_CQF_EWW_PWOT_MASK                         0x20
#define MME_CMDQ_GWBW_PWOT_CP_EWW_PWOT_SHIFT                         6
#define MME_CMDQ_GWBW_PWOT_CP_EWW_PWOT_MASK                          0x40
#define MME_CMDQ_GWBW_PWOT_DMA_EWW_PWOT_SHIFT                        7
#define MME_CMDQ_GWBW_PWOT_DMA_EWW_PWOT_MASK                         0x80

/* MME_CMDQ_GWBW_EWW_CFG */
#define MME_CMDQ_GWBW_EWW_CFG_PQF_EWW_INT_EN_SHIFT                   0
#define MME_CMDQ_GWBW_EWW_CFG_PQF_EWW_INT_EN_MASK                    0x1
#define MME_CMDQ_GWBW_EWW_CFG_PQF_EWW_MSG_EN_SHIFT                   1
#define MME_CMDQ_GWBW_EWW_CFG_PQF_EWW_MSG_EN_MASK                    0x2
#define MME_CMDQ_GWBW_EWW_CFG_PQF_STOP_ON_EWW_SHIFT                  2
#define MME_CMDQ_GWBW_EWW_CFG_PQF_STOP_ON_EWW_MASK                   0x4
#define MME_CMDQ_GWBW_EWW_CFG_CQF_EWW_INT_EN_SHIFT                   3
#define MME_CMDQ_GWBW_EWW_CFG_CQF_EWW_INT_EN_MASK                    0x8
#define MME_CMDQ_GWBW_EWW_CFG_CQF_EWW_MSG_EN_SHIFT                   4
#define MME_CMDQ_GWBW_EWW_CFG_CQF_EWW_MSG_EN_MASK                    0x10
#define MME_CMDQ_GWBW_EWW_CFG_CQF_STOP_ON_EWW_SHIFT                  5
#define MME_CMDQ_GWBW_EWW_CFG_CQF_STOP_ON_EWW_MASK                   0x20
#define MME_CMDQ_GWBW_EWW_CFG_CP_EWW_INT_EN_SHIFT                    6
#define MME_CMDQ_GWBW_EWW_CFG_CP_EWW_INT_EN_MASK                     0x40
#define MME_CMDQ_GWBW_EWW_CFG_CP_EWW_MSG_EN_SHIFT                    7
#define MME_CMDQ_GWBW_EWW_CFG_CP_EWW_MSG_EN_MASK                     0x80
#define MME_CMDQ_GWBW_EWW_CFG_CP_STOP_ON_EWW_SHIFT                   8
#define MME_CMDQ_GWBW_EWW_CFG_CP_STOP_ON_EWW_MASK                    0x100
#define MME_CMDQ_GWBW_EWW_CFG_DMA_EWW_INT_EN_SHIFT                   9
#define MME_CMDQ_GWBW_EWW_CFG_DMA_EWW_INT_EN_MASK                    0x200
#define MME_CMDQ_GWBW_EWW_CFG_DMA_EWW_MSG_EN_SHIFT                   10
#define MME_CMDQ_GWBW_EWW_CFG_DMA_EWW_MSG_EN_MASK                    0x400
#define MME_CMDQ_GWBW_EWW_CFG_DMA_STOP_ON_EWW_SHIFT                  11
#define MME_CMDQ_GWBW_EWW_CFG_DMA_STOP_ON_EWW_MASK                   0x800

/* MME_CMDQ_GWBW_EWW_ADDW_WO */
#define MME_CMDQ_GWBW_EWW_ADDW_WO_VAW_SHIFT                          0
#define MME_CMDQ_GWBW_EWW_ADDW_WO_VAW_MASK                           0xFFFFFFFF

/* MME_CMDQ_GWBW_EWW_ADDW_HI */
#define MME_CMDQ_GWBW_EWW_ADDW_HI_VAW_SHIFT                          0
#define MME_CMDQ_GWBW_EWW_ADDW_HI_VAW_MASK                           0xFFFFFFFF

/* MME_CMDQ_GWBW_EWW_WDATA */
#define MME_CMDQ_GWBW_EWW_WDATA_VAW_SHIFT                            0
#define MME_CMDQ_GWBW_EWW_WDATA_VAW_MASK                             0xFFFFFFFF

/* MME_CMDQ_GWBW_SECUWE_PWOPS */
#define MME_CMDQ_GWBW_SECUWE_PWOPS_ASID_SHIFT                        0
#define MME_CMDQ_GWBW_SECUWE_PWOPS_ASID_MASK                         0x3FF
#define MME_CMDQ_GWBW_SECUWE_PWOPS_MMBP_SHIFT                        10
#define MME_CMDQ_GWBW_SECUWE_PWOPS_MMBP_MASK                         0x400

/* MME_CMDQ_GWBW_NON_SECUWE_PWOPS */
#define MME_CMDQ_GWBW_NON_SECUWE_PWOPS_ASID_SHIFT                    0
#define MME_CMDQ_GWBW_NON_SECUWE_PWOPS_ASID_MASK                     0x3FF
#define MME_CMDQ_GWBW_NON_SECUWE_PWOPS_MMBP_SHIFT                    10
#define MME_CMDQ_GWBW_NON_SECUWE_PWOPS_MMBP_MASK                     0x400

/* MME_CMDQ_GWBW_STS0 */
#define MME_CMDQ_GWBW_STS0_PQF_IDWE_SHIFT                            0
#define MME_CMDQ_GWBW_STS0_PQF_IDWE_MASK                             0x1
#define MME_CMDQ_GWBW_STS0_CQF_IDWE_SHIFT                            1
#define MME_CMDQ_GWBW_STS0_CQF_IDWE_MASK                             0x2
#define MME_CMDQ_GWBW_STS0_CP_IDWE_SHIFT                             2
#define MME_CMDQ_GWBW_STS0_CP_IDWE_MASK                              0x4
#define MME_CMDQ_GWBW_STS0_DMA_IDWE_SHIFT                            3
#define MME_CMDQ_GWBW_STS0_DMA_IDWE_MASK                             0x8
#define MME_CMDQ_GWBW_STS0_PQF_IS_STOP_SHIFT                         4
#define MME_CMDQ_GWBW_STS0_PQF_IS_STOP_MASK                          0x10
#define MME_CMDQ_GWBW_STS0_CQF_IS_STOP_SHIFT                         5
#define MME_CMDQ_GWBW_STS0_CQF_IS_STOP_MASK                          0x20
#define MME_CMDQ_GWBW_STS0_CP_IS_STOP_SHIFT                          6
#define MME_CMDQ_GWBW_STS0_CP_IS_STOP_MASK                           0x40
#define MME_CMDQ_GWBW_STS0_DMA_IS_STOP_SHIFT                         7
#define MME_CMDQ_GWBW_STS0_DMA_IS_STOP_MASK                          0x80

/* MME_CMDQ_GWBW_STS1 */
#define MME_CMDQ_GWBW_STS1_PQF_WD_EWW_SHIFT                          0
#define MME_CMDQ_GWBW_STS1_PQF_WD_EWW_MASK                           0x1
#define MME_CMDQ_GWBW_STS1_CQF_WD_EWW_SHIFT                          1
#define MME_CMDQ_GWBW_STS1_CQF_WD_EWW_MASK                           0x2
#define MME_CMDQ_GWBW_STS1_CP_WD_EWW_SHIFT                           2
#define MME_CMDQ_GWBW_STS1_CP_WD_EWW_MASK                            0x4
#define MME_CMDQ_GWBW_STS1_CP_UNDEF_CMD_EWW_SHIFT                    3
#define MME_CMDQ_GWBW_STS1_CP_UNDEF_CMD_EWW_MASK                     0x8
#define MME_CMDQ_GWBW_STS1_CP_STOP_OP_SHIFT                          4
#define MME_CMDQ_GWBW_STS1_CP_STOP_OP_MASK                           0x10
#define MME_CMDQ_GWBW_STS1_CP_MSG_WW_EWW_SHIFT                       5
#define MME_CMDQ_GWBW_STS1_CP_MSG_WW_EWW_MASK                        0x20
#define MME_CMDQ_GWBW_STS1_DMA_WD_EWW_SHIFT                          8
#define MME_CMDQ_GWBW_STS1_DMA_WD_EWW_MASK                           0x100
#define MME_CMDQ_GWBW_STS1_DMA_WW_EWW_SHIFT                          9
#define MME_CMDQ_GWBW_STS1_DMA_WW_EWW_MASK                           0x200
#define MME_CMDQ_GWBW_STS1_DMA_WD_MSG_EWW_SHIFT                      10
#define MME_CMDQ_GWBW_STS1_DMA_WD_MSG_EWW_MASK                       0x400
#define MME_CMDQ_GWBW_STS1_DMA_WW_MSG_EWW_SHIFT                      11
#define MME_CMDQ_GWBW_STS1_DMA_WW_MSG_EWW_MASK                       0x800

/* MME_CMDQ_CQ_CFG0 */
#define MME_CMDQ_CQ_CFG0_WESEWVED_SHIFT                              0
#define MME_CMDQ_CQ_CFG0_WESEWVED_MASK                               0x1

/* MME_CMDQ_CQ_CFG1 */
#define MME_CMDQ_CQ_CFG1_CWEDIT_WIM_SHIFT                            0
#define MME_CMDQ_CQ_CFG1_CWEDIT_WIM_MASK                             0xFFFF
#define MME_CMDQ_CQ_CFG1_MAX_INFWIGHT_SHIFT                          16
#define MME_CMDQ_CQ_CFG1_MAX_INFWIGHT_MASK                           0xFFFF0000

/* MME_CMDQ_CQ_AWUSEW */
#define MME_CMDQ_CQ_AWUSEW_NOSNOOP_SHIFT                             0
#define MME_CMDQ_CQ_AWUSEW_NOSNOOP_MASK                              0x1
#define MME_CMDQ_CQ_AWUSEW_WOWD_SHIFT                                1
#define MME_CMDQ_CQ_AWUSEW_WOWD_MASK                                 0x2

/* MME_CMDQ_CQ_PTW_WO */
#define MME_CMDQ_CQ_PTW_WO_VAW_SHIFT                                 0
#define MME_CMDQ_CQ_PTW_WO_VAW_MASK                                  0xFFFFFFFF

/* MME_CMDQ_CQ_PTW_HI */
#define MME_CMDQ_CQ_PTW_HI_VAW_SHIFT                                 0
#define MME_CMDQ_CQ_PTW_HI_VAW_MASK                                  0xFFFFFFFF

/* MME_CMDQ_CQ_TSIZE */
#define MME_CMDQ_CQ_TSIZE_VAW_SHIFT                                  0
#define MME_CMDQ_CQ_TSIZE_VAW_MASK                                   0xFFFFFFFF

/* MME_CMDQ_CQ_CTW */
#define MME_CMDQ_CQ_CTW_WPT_SHIFT                                    0
#define MME_CMDQ_CQ_CTW_WPT_MASK                                     0xFFFF
#define MME_CMDQ_CQ_CTW_CTW_SHIFT                                    16
#define MME_CMDQ_CQ_CTW_CTW_MASK                                     0xFFFF0000

/* MME_CMDQ_CQ_PTW_WO_STS */
#define MME_CMDQ_CQ_PTW_WO_STS_VAW_SHIFT                             0
#define MME_CMDQ_CQ_PTW_WO_STS_VAW_MASK                              0xFFFFFFFF

/* MME_CMDQ_CQ_PTW_HI_STS */
#define MME_CMDQ_CQ_PTW_HI_STS_VAW_SHIFT                             0
#define MME_CMDQ_CQ_PTW_HI_STS_VAW_MASK                              0xFFFFFFFF

/* MME_CMDQ_CQ_TSIZE_STS */
#define MME_CMDQ_CQ_TSIZE_STS_VAW_SHIFT                              0
#define MME_CMDQ_CQ_TSIZE_STS_VAW_MASK                               0xFFFFFFFF

/* MME_CMDQ_CQ_CTW_STS */
#define MME_CMDQ_CQ_CTW_STS_WPT_SHIFT                                0
#define MME_CMDQ_CQ_CTW_STS_WPT_MASK                                 0xFFFF
#define MME_CMDQ_CQ_CTW_STS_CTW_SHIFT                                16
#define MME_CMDQ_CQ_CTW_STS_CTW_MASK                                 0xFFFF0000

/* MME_CMDQ_CQ_STS0 */
#define MME_CMDQ_CQ_STS0_CQ_CWEDIT_CNT_SHIFT                         0
#define MME_CMDQ_CQ_STS0_CQ_CWEDIT_CNT_MASK                          0xFFFF
#define MME_CMDQ_CQ_STS0_CQ_FWEE_CNT_SHIFT                           16
#define MME_CMDQ_CQ_STS0_CQ_FWEE_CNT_MASK                            0xFFFF0000

/* MME_CMDQ_CQ_STS1 */
#define MME_CMDQ_CQ_STS1_CQ_INFWIGHT_CNT_SHIFT                       0
#define MME_CMDQ_CQ_STS1_CQ_INFWIGHT_CNT_MASK                        0xFFFF
#define MME_CMDQ_CQ_STS1_CQ_BUF_EMPTY_SHIFT                          30
#define MME_CMDQ_CQ_STS1_CQ_BUF_EMPTY_MASK                           0x40000000
#define MME_CMDQ_CQ_STS1_CQ_BUSY_SHIFT                               31
#define MME_CMDQ_CQ_STS1_CQ_BUSY_MASK                                0x80000000

/* MME_CMDQ_CQ_WD_WATE_WIM_EN */
#define MME_CMDQ_CQ_WD_WATE_WIM_EN_VAW_SHIFT                         0
#define MME_CMDQ_CQ_WD_WATE_WIM_EN_VAW_MASK                          0x1

/* MME_CMDQ_CQ_WD_WATE_WIM_WST_TOKEN */
#define MME_CMDQ_CQ_WD_WATE_WIM_WST_TOKEN_VAW_SHIFT                  0
#define MME_CMDQ_CQ_WD_WATE_WIM_WST_TOKEN_VAW_MASK                   0xFFFF

/* MME_CMDQ_CQ_WD_WATE_WIM_SAT */
#define MME_CMDQ_CQ_WD_WATE_WIM_SAT_VAW_SHIFT                        0
#define MME_CMDQ_CQ_WD_WATE_WIM_SAT_VAW_MASK                         0xFFFF

/* MME_CMDQ_CQ_WD_WATE_WIM_TOUT */
#define MME_CMDQ_CQ_WD_WATE_WIM_TOUT_VAW_SHIFT                       0
#define MME_CMDQ_CQ_WD_WATE_WIM_TOUT_VAW_MASK                        0x7FFFFFFF

/* MME_CMDQ_CQ_IFIFO_CNT */
#define MME_CMDQ_CQ_IFIFO_CNT_VAW_SHIFT                              0
#define MME_CMDQ_CQ_IFIFO_CNT_VAW_MASK                               0x3

/* MME_CMDQ_CP_MSG_BASE0_ADDW_WO */
#define MME_CMDQ_CP_MSG_BASE0_ADDW_WO_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE0_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE0_ADDW_HI */
#define MME_CMDQ_CP_MSG_BASE0_ADDW_HI_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE0_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE1_ADDW_WO */
#define MME_CMDQ_CP_MSG_BASE1_ADDW_WO_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE1_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE1_ADDW_HI */
#define MME_CMDQ_CP_MSG_BASE1_ADDW_HI_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE1_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE2_ADDW_WO */
#define MME_CMDQ_CP_MSG_BASE2_ADDW_WO_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE2_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE2_ADDW_HI */
#define MME_CMDQ_CP_MSG_BASE2_ADDW_HI_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE2_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE3_ADDW_WO */
#define MME_CMDQ_CP_MSG_BASE3_ADDW_WO_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE3_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_MSG_BASE3_ADDW_HI */
#define MME_CMDQ_CP_MSG_BASE3_ADDW_HI_VAW_SHIFT                      0
#define MME_CMDQ_CP_MSG_BASE3_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_TSIZE_OFFSET */
#define MME_CMDQ_CP_WDMA_TSIZE_OFFSET_VAW_SHIFT                      0
#define MME_CMDQ_CP_WDMA_TSIZE_OFFSET_VAW_MASK                       0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_SWC_BASE_WO_OFFSET */
#define MME_CMDQ_CP_WDMA_SWC_BASE_WO_OFFSET_VAW_SHIFT                0
#define MME_CMDQ_CP_WDMA_SWC_BASE_WO_OFFSET_VAW_MASK                 0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_SWC_BASE_HI_OFFSET */
#define MME_CMDQ_CP_WDMA_SWC_BASE_HI_OFFSET_VAW_SHIFT                0
#define MME_CMDQ_CP_WDMA_SWC_BASE_HI_OFFSET_VAW_MASK                 0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_DST_BASE_WO_OFFSET */
#define MME_CMDQ_CP_WDMA_DST_BASE_WO_OFFSET_VAW_SHIFT                0
#define MME_CMDQ_CP_WDMA_DST_BASE_WO_OFFSET_VAW_MASK                 0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_DST_BASE_HI_OFFSET */
#define MME_CMDQ_CP_WDMA_DST_BASE_HI_OFFSET_VAW_SHIFT                0
#define MME_CMDQ_CP_WDMA_DST_BASE_HI_OFFSET_VAW_MASK                 0xFFFFFFFF

/* MME_CMDQ_CP_WDMA_COMMIT_OFFSET */
#define MME_CMDQ_CP_WDMA_COMMIT_OFFSET_VAW_SHIFT                     0
#define MME_CMDQ_CP_WDMA_COMMIT_OFFSET_VAW_MASK                      0xFFFFFFFF

/* MME_CMDQ_CP_FENCE0_WDATA */
#define MME_CMDQ_CP_FENCE0_WDATA_INC_VAW_SHIFT                       0
#define MME_CMDQ_CP_FENCE0_WDATA_INC_VAW_MASK                        0xF

/* MME_CMDQ_CP_FENCE1_WDATA */
#define MME_CMDQ_CP_FENCE1_WDATA_INC_VAW_SHIFT                       0
#define MME_CMDQ_CP_FENCE1_WDATA_INC_VAW_MASK                        0xF

/* MME_CMDQ_CP_FENCE2_WDATA */
#define MME_CMDQ_CP_FENCE2_WDATA_INC_VAW_SHIFT                       0
#define MME_CMDQ_CP_FENCE2_WDATA_INC_VAW_MASK                        0xF

/* MME_CMDQ_CP_FENCE3_WDATA */
#define MME_CMDQ_CP_FENCE3_WDATA_INC_VAW_SHIFT                       0
#define MME_CMDQ_CP_FENCE3_WDATA_INC_VAW_MASK                        0xF

/* MME_CMDQ_CP_FENCE0_CNT */
#define MME_CMDQ_CP_FENCE0_CNT_VAW_SHIFT                             0
#define MME_CMDQ_CP_FENCE0_CNT_VAW_MASK                              0xFF

/* MME_CMDQ_CP_FENCE1_CNT */
#define MME_CMDQ_CP_FENCE1_CNT_VAW_SHIFT                             0
#define MME_CMDQ_CP_FENCE1_CNT_VAW_MASK                              0xFF

/* MME_CMDQ_CP_FENCE2_CNT */
#define MME_CMDQ_CP_FENCE2_CNT_VAW_SHIFT                             0
#define MME_CMDQ_CP_FENCE2_CNT_VAW_MASK                              0xFF

/* MME_CMDQ_CP_FENCE3_CNT */
#define MME_CMDQ_CP_FENCE3_CNT_VAW_SHIFT                             0
#define MME_CMDQ_CP_FENCE3_CNT_VAW_MASK                              0xFF

/* MME_CMDQ_CP_STS */
#define MME_CMDQ_CP_STS_MSG_INFWIGHT_CNT_SHIFT                       0
#define MME_CMDQ_CP_STS_MSG_INFWIGHT_CNT_MASK                        0xFFFF
#define MME_CMDQ_CP_STS_EWDY_SHIFT                                   16
#define MME_CMDQ_CP_STS_EWDY_MASK                                    0x10000
#define MME_CMDQ_CP_STS_WWDY_SHIFT                                   17
#define MME_CMDQ_CP_STS_WWDY_MASK                                    0x20000
#define MME_CMDQ_CP_STS_MWDY_SHIFT                                   18
#define MME_CMDQ_CP_STS_MWDY_MASK                                    0x40000
#define MME_CMDQ_CP_STS_SW_STOP_SHIFT                                19
#define MME_CMDQ_CP_STS_SW_STOP_MASK                                 0x80000
#define MME_CMDQ_CP_STS_FENCE_ID_SHIFT                               20
#define MME_CMDQ_CP_STS_FENCE_ID_MASK                                0x300000
#define MME_CMDQ_CP_STS_FENCE_IN_PWOGWESS_SHIFT                      22
#define MME_CMDQ_CP_STS_FENCE_IN_PWOGWESS_MASK                       0x400000

/* MME_CMDQ_CP_CUWWENT_INST_WO */
#define MME_CMDQ_CP_CUWWENT_INST_WO_VAW_SHIFT                        0
#define MME_CMDQ_CP_CUWWENT_INST_WO_VAW_MASK                         0xFFFFFFFF

/* MME_CMDQ_CP_CUWWENT_INST_HI */
#define MME_CMDQ_CP_CUWWENT_INST_HI_VAW_SHIFT                        0
#define MME_CMDQ_CP_CUWWENT_INST_HI_VAW_MASK                         0xFFFFFFFF

/* MME_CMDQ_CP_BAWWIEW_CFG */
#define MME_CMDQ_CP_BAWWIEW_CFG_EBGUAWD_SHIFT                        0
#define MME_CMDQ_CP_BAWWIEW_CFG_EBGUAWD_MASK                         0xFFF

/* MME_CMDQ_CP_DBG_0 */
#define MME_CMDQ_CP_DBG_0_VAW_SHIFT                                  0
#define MME_CMDQ_CP_DBG_0_VAW_MASK                                   0xFF

/* MME_CMDQ_CQ_BUF_ADDW */
#define MME_CMDQ_CQ_BUF_ADDW_VAW_SHIFT                               0
#define MME_CMDQ_CQ_BUF_ADDW_VAW_MASK                                0xFFFFFFFF

/* MME_CMDQ_CQ_BUF_WDATA */
#define MME_CMDQ_CQ_BUF_WDATA_VAW_SHIFT                              0
#define MME_CMDQ_CQ_BUF_WDATA_VAW_MASK                               0xFFFFFFFF

#endif /* ASIC_WEG_MME_CMDQ_MASKS_H_ */
