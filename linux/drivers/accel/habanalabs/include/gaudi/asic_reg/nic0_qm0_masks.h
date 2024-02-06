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

#ifndef ASIC_WEG_NIC0_QM0_MASKS_H_
#define ASIC_WEG_NIC0_QM0_MASKS_H_

/*
 *****************************************
 *   NIC0_QM0 (Pwototype: QMAN)
 *****************************************
 */

/* NIC0_QM0_GWBW_CFG0 */
#define NIC0_QM0_GWBW_CFG0_PQF_EN_SHIFT                              0
#define NIC0_QM0_GWBW_CFG0_PQF_EN_MASK                               0xF
#define NIC0_QM0_GWBW_CFG0_CQF_EN_SHIFT                              4
#define NIC0_QM0_GWBW_CFG0_CQF_EN_MASK                               0x1F0
#define NIC0_QM0_GWBW_CFG0_CP_EN_SHIFT                               9
#define NIC0_QM0_GWBW_CFG0_CP_EN_MASK                                0x3E00

/* NIC0_QM0_GWBW_CFG1 */
#define NIC0_QM0_GWBW_CFG1_PQF_STOP_SHIFT                            0
#define NIC0_QM0_GWBW_CFG1_PQF_STOP_MASK                             0xF
#define NIC0_QM0_GWBW_CFG1_CQF_STOP_SHIFT                            4
#define NIC0_QM0_GWBW_CFG1_CQF_STOP_MASK                             0x1F0
#define NIC0_QM0_GWBW_CFG1_CP_STOP_SHIFT                             9
#define NIC0_QM0_GWBW_CFG1_CP_STOP_MASK                              0x3E00
#define NIC0_QM0_GWBW_CFG1_PQF_FWUSH_SHIFT                           16
#define NIC0_QM0_GWBW_CFG1_PQF_FWUSH_MASK                            0xF0000
#define NIC0_QM0_GWBW_CFG1_CQF_FWUSH_SHIFT                           20
#define NIC0_QM0_GWBW_CFG1_CQF_FWUSH_MASK                            0x1F00000
#define NIC0_QM0_GWBW_CFG1_CP_FWUSH_SHIFT                            25
#define NIC0_QM0_GWBW_CFG1_CP_FWUSH_MASK                             0x3E000000

/* NIC0_QM0_GWBW_PWOT */
#define NIC0_QM0_GWBW_PWOT_PQF_SHIFT                                 0
#define NIC0_QM0_GWBW_PWOT_PQF_MASK                                  0xF
#define NIC0_QM0_GWBW_PWOT_CQF_SHIFT                                 4
#define NIC0_QM0_GWBW_PWOT_CQF_MASK                                  0x1F0
#define NIC0_QM0_GWBW_PWOT_CP_SHIFT                                  9
#define NIC0_QM0_GWBW_PWOT_CP_MASK                                   0x3E00
#define NIC0_QM0_GWBW_PWOT_EWW_SHIFT                                 14
#define NIC0_QM0_GWBW_PWOT_EWW_MASK                                  0x4000
#define NIC0_QM0_GWBW_PWOT_AWB_SHIFT                                 15
#define NIC0_QM0_GWBW_PWOT_AWB_MASK                                  0x8000

/* NIC0_QM0_GWBW_EWW_CFG */
#define NIC0_QM0_GWBW_EWW_CFG_PQF_EWW_MSG_EN_SHIFT                   0
#define NIC0_QM0_GWBW_EWW_CFG_PQF_EWW_MSG_EN_MASK                    0xF
#define NIC0_QM0_GWBW_EWW_CFG_CQF_EWW_MSG_EN_SHIFT                   4
#define NIC0_QM0_GWBW_EWW_CFG_CQF_EWW_MSG_EN_MASK                    0x1F0
#define NIC0_QM0_GWBW_EWW_CFG_CP_EWW_MSG_EN_SHIFT                    9
#define NIC0_QM0_GWBW_EWW_CFG_CP_EWW_MSG_EN_MASK                     0x3E00
#define NIC0_QM0_GWBW_EWW_CFG_PQF_STOP_ON_EWW_SHIFT                  16
#define NIC0_QM0_GWBW_EWW_CFG_PQF_STOP_ON_EWW_MASK                   0xF0000
#define NIC0_QM0_GWBW_EWW_CFG_CQF_STOP_ON_EWW_SHIFT                  20
#define NIC0_QM0_GWBW_EWW_CFG_CQF_STOP_ON_EWW_MASK                   0x1F00000
#define NIC0_QM0_GWBW_EWW_CFG_CP_STOP_ON_EWW_SHIFT                   25
#define NIC0_QM0_GWBW_EWW_CFG_CP_STOP_ON_EWW_MASK                    0x3E000000
#define NIC0_QM0_GWBW_EWW_CFG_AWB_STOP_ON_EWW_SHIFT                  31
#define NIC0_QM0_GWBW_EWW_CFG_AWB_STOP_ON_EWW_MASK                   0x80000000

/* NIC0_QM0_GWBW_SECUWE_PWOPS */
#define NIC0_QM0_GWBW_SECUWE_PWOPS_0_ASID_SHIFT                      0
#define NIC0_QM0_GWBW_SECUWE_PWOPS_0_ASID_MASK                       0x3FF
#define NIC0_QM0_GWBW_SECUWE_PWOPS_1_ASID_SHIFT                      0
#define NIC0_QM0_GWBW_SECUWE_PWOPS_1_ASID_MASK                       0x3FF
#define NIC0_QM0_GWBW_SECUWE_PWOPS_2_ASID_SHIFT                      0
#define NIC0_QM0_GWBW_SECUWE_PWOPS_2_ASID_MASK                       0x3FF
#define NIC0_QM0_GWBW_SECUWE_PWOPS_3_ASID_SHIFT                      0
#define NIC0_QM0_GWBW_SECUWE_PWOPS_3_ASID_MASK                       0x3FF
#define NIC0_QM0_GWBW_SECUWE_PWOPS_4_ASID_SHIFT                      0
#define NIC0_QM0_GWBW_SECUWE_PWOPS_4_ASID_MASK                       0x3FF
#define NIC0_QM0_GWBW_SECUWE_PWOPS_0_MMBP_SHIFT                      10
#define NIC0_QM0_GWBW_SECUWE_PWOPS_0_MMBP_MASK                       0x400
#define NIC0_QM0_GWBW_SECUWE_PWOPS_1_MMBP_SHIFT                      10
#define NIC0_QM0_GWBW_SECUWE_PWOPS_1_MMBP_MASK                       0x400
#define NIC0_QM0_GWBW_SECUWE_PWOPS_2_MMBP_SHIFT                      10
#define NIC0_QM0_GWBW_SECUWE_PWOPS_2_MMBP_MASK                       0x400
#define NIC0_QM0_GWBW_SECUWE_PWOPS_3_MMBP_SHIFT                      10
#define NIC0_QM0_GWBW_SECUWE_PWOPS_3_MMBP_MASK                       0x400
#define NIC0_QM0_GWBW_SECUWE_PWOPS_4_MMBP_SHIFT                      10
#define NIC0_QM0_GWBW_SECUWE_PWOPS_4_MMBP_MASK                       0x400

/* NIC0_QM0_GWBW_NON_SECUWE_PWOPS */
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_0_ASID_SHIFT                  0
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_0_ASID_MASK                   0x3FF
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_1_ASID_SHIFT                  0
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_1_ASID_MASK                   0x3FF
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_2_ASID_SHIFT                  0
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_2_ASID_MASK                   0x3FF
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_3_ASID_SHIFT                  0
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_3_ASID_MASK                   0x3FF
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_4_ASID_SHIFT                  0
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_4_ASID_MASK                   0x3FF
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_0_MMBP_SHIFT                  10
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_0_MMBP_MASK                   0x400
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_1_MMBP_SHIFT                  10
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_1_MMBP_MASK                   0x400
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_2_MMBP_SHIFT                  10
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_2_MMBP_MASK                   0x400
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_3_MMBP_SHIFT                  10
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_3_MMBP_MASK                   0x400
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_4_MMBP_SHIFT                  10
#define NIC0_QM0_GWBW_NON_SECUWE_PWOPS_4_MMBP_MASK                   0x400

/* NIC0_QM0_GWBW_STS0 */
#define NIC0_QM0_GWBW_STS0_PQF_IDWE_SHIFT                            0
#define NIC0_QM0_GWBW_STS0_PQF_IDWE_MASK                             0xF
#define NIC0_QM0_GWBW_STS0_CQF_IDWE_SHIFT                            4
#define NIC0_QM0_GWBW_STS0_CQF_IDWE_MASK                             0x1F0
#define NIC0_QM0_GWBW_STS0_CP_IDWE_SHIFT                             9
#define NIC0_QM0_GWBW_STS0_CP_IDWE_MASK                              0x3E00
#define NIC0_QM0_GWBW_STS0_PQF_IS_STOP_SHIFT                         16
#define NIC0_QM0_GWBW_STS0_PQF_IS_STOP_MASK                          0xF0000
#define NIC0_QM0_GWBW_STS0_CQF_IS_STOP_SHIFT                         20
#define NIC0_QM0_GWBW_STS0_CQF_IS_STOP_MASK                          0x1F00000
#define NIC0_QM0_GWBW_STS0_CP_IS_STOP_SHIFT                          25
#define NIC0_QM0_GWBW_STS0_CP_IS_STOP_MASK                           0x3E000000
#define NIC0_QM0_GWBW_STS0_AWB_IS_STOP_SHIFT                         31
#define NIC0_QM0_GWBW_STS0_AWB_IS_STOP_MASK                          0x80000000

/* NIC0_QM0_GWBW_STS1 */
#define NIC0_QM0_GWBW_STS1_PQF_WD_EWW_SHIFT                          0
#define NIC0_QM0_GWBW_STS1_PQF_WD_EWW_MASK                           0x1
#define NIC0_QM0_GWBW_STS1_CQF_WD_EWW_SHIFT                          1
#define NIC0_QM0_GWBW_STS1_CQF_WD_EWW_MASK                           0x2
#define NIC0_QM0_GWBW_STS1_CP_WD_EWW_SHIFT                           2
#define NIC0_QM0_GWBW_STS1_CP_WD_EWW_MASK                            0x4
#define NIC0_QM0_GWBW_STS1_CP_UNDEF_CMD_EWW_SHIFT                    3
#define NIC0_QM0_GWBW_STS1_CP_UNDEF_CMD_EWW_MASK                     0x8
#define NIC0_QM0_GWBW_STS1_CP_STOP_OP_SHIFT                          4
#define NIC0_QM0_GWBW_STS1_CP_STOP_OP_MASK                           0x10
#define NIC0_QM0_GWBW_STS1_CP_MSG_WW_EWW_SHIFT                       5
#define NIC0_QM0_GWBW_STS1_CP_MSG_WW_EWW_MASK                        0x20
#define NIC0_QM0_GWBW_STS1_CP_WWEG_EWW_SHIFT                         6
#define NIC0_QM0_GWBW_STS1_CP_WWEG_EWW_MASK                          0x40
#define NIC0_QM0_GWBW_STS1_CP_FENCE0_OVF_EWW_SHIFT                   8
#define NIC0_QM0_GWBW_STS1_CP_FENCE0_OVF_EWW_MASK                    0x100
#define NIC0_QM0_GWBW_STS1_CP_FENCE1_OVF_EWW_SHIFT                   9
#define NIC0_QM0_GWBW_STS1_CP_FENCE1_OVF_EWW_MASK                    0x200
#define NIC0_QM0_GWBW_STS1_CP_FENCE2_OVF_EWW_SHIFT                   10
#define NIC0_QM0_GWBW_STS1_CP_FENCE2_OVF_EWW_MASK                    0x400
#define NIC0_QM0_GWBW_STS1_CP_FENCE3_OVF_EWW_SHIFT                   11
#define NIC0_QM0_GWBW_STS1_CP_FENCE3_OVF_EWW_MASK                    0x800
#define NIC0_QM0_GWBW_STS1_CP_FENCE0_UDF_EWW_SHIFT                   12
#define NIC0_QM0_GWBW_STS1_CP_FENCE0_UDF_EWW_MASK                    0x1000
#define NIC0_QM0_GWBW_STS1_CP_FENCE1_UDF_EWW_SHIFT                   13
#define NIC0_QM0_GWBW_STS1_CP_FENCE1_UDF_EWW_MASK                    0x2000
#define NIC0_QM0_GWBW_STS1_CP_FENCE2_UDF_EWW_SHIFT                   14
#define NIC0_QM0_GWBW_STS1_CP_FENCE2_UDF_EWW_MASK                    0x4000
#define NIC0_QM0_GWBW_STS1_CP_FENCE3_UDF_EWW_SHIFT                   15
#define NIC0_QM0_GWBW_STS1_CP_FENCE3_UDF_EWW_MASK                    0x8000

/* NIC0_QM0_GWBW_STS1_4 */
#define NIC0_QM0_GWBW_STS1_4_CQF_WD_EWW_SHIFT                        1
#define NIC0_QM0_GWBW_STS1_4_CQF_WD_EWW_MASK                         0x2
#define NIC0_QM0_GWBW_STS1_4_CP_WD_EWW_SHIFT                         2
#define NIC0_QM0_GWBW_STS1_4_CP_WD_EWW_MASK                          0x4
#define NIC0_QM0_GWBW_STS1_4_CP_UNDEF_CMD_EWW_SHIFT                  3
#define NIC0_QM0_GWBW_STS1_4_CP_UNDEF_CMD_EWW_MASK                   0x8
#define NIC0_QM0_GWBW_STS1_4_CP_STOP_OP_SHIFT                        4
#define NIC0_QM0_GWBW_STS1_4_CP_STOP_OP_MASK                         0x10
#define NIC0_QM0_GWBW_STS1_4_CP_MSG_WW_EWW_SHIFT                     5
#define NIC0_QM0_GWBW_STS1_4_CP_MSG_WW_EWW_MASK                      0x20
#define NIC0_QM0_GWBW_STS1_4_CP_WWEG_EWW_SHIFT                       6
#define NIC0_QM0_GWBW_STS1_4_CP_WWEG_EWW_MASK                        0x40
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE0_OVF_EWW_SHIFT                 8
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE0_OVF_EWW_MASK                  0x100
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE1_OVF_EWW_SHIFT                 9
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE1_OVF_EWW_MASK                  0x200
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE2_OVF_EWW_SHIFT                 10
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE2_OVF_EWW_MASK                  0x400
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE3_OVF_EWW_SHIFT                 11
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE3_OVF_EWW_MASK                  0x800
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE0_UDF_EWW_SHIFT                 12
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE0_UDF_EWW_MASK                  0x1000
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE1_UDF_EWW_SHIFT                 13
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE1_UDF_EWW_MASK                  0x2000
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE2_UDF_EWW_SHIFT                 14
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE2_UDF_EWW_MASK                  0x4000
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE3_UDF_EWW_SHIFT                 15
#define NIC0_QM0_GWBW_STS1_4_CP_FENCE3_UDF_EWW_MASK                  0x8000

/* NIC0_QM0_GWBW_MSG_EN */
#define NIC0_QM0_GWBW_MSG_EN_PQF_WD_EWW_SHIFT                        0
#define NIC0_QM0_GWBW_MSG_EN_PQF_WD_EWW_MASK                         0x1
#define NIC0_QM0_GWBW_MSG_EN_CQF_WD_EWW_SHIFT                        1
#define NIC0_QM0_GWBW_MSG_EN_CQF_WD_EWW_MASK                         0x2
#define NIC0_QM0_GWBW_MSG_EN_CP_WD_EWW_SHIFT                         2
#define NIC0_QM0_GWBW_MSG_EN_CP_WD_EWW_MASK                          0x4
#define NIC0_QM0_GWBW_MSG_EN_CP_UNDEF_CMD_EWW_SHIFT                  3
#define NIC0_QM0_GWBW_MSG_EN_CP_UNDEF_CMD_EWW_MASK                   0x8
#define NIC0_QM0_GWBW_MSG_EN_CP_STOP_OP_SHIFT                        4
#define NIC0_QM0_GWBW_MSG_EN_CP_STOP_OP_MASK                         0x10
#define NIC0_QM0_GWBW_MSG_EN_CP_MSG_WW_EWW_SHIFT                     5
#define NIC0_QM0_GWBW_MSG_EN_CP_MSG_WW_EWW_MASK                      0x20
#define NIC0_QM0_GWBW_MSG_EN_CP_WWEG_EWW_SHIFT                       6
#define NIC0_QM0_GWBW_MSG_EN_CP_WWEG_EWW_MASK                        0x40
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE0_OVF_EWW_SHIFT                 8
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE0_OVF_EWW_MASK                  0x100
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE1_OVF_EWW_SHIFT                 9
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE1_OVF_EWW_MASK                  0x200
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE2_OVF_EWW_SHIFT                 10
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE2_OVF_EWW_MASK                  0x400
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE3_OVF_EWW_SHIFT                 11
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE3_OVF_EWW_MASK                  0x800
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE0_UDF_EWW_SHIFT                 12
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE0_UDF_EWW_MASK                  0x1000
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE1_UDF_EWW_SHIFT                 13
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE1_UDF_EWW_MASK                  0x2000
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE2_UDF_EWW_SHIFT                 14
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE2_UDF_EWW_MASK                  0x4000
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE3_UDF_EWW_SHIFT                 15
#define NIC0_QM0_GWBW_MSG_EN_CP_FENCE3_UDF_EWW_MASK                  0x8000

/* NIC0_QM0_GWBW_MSG_EN_4 */
#define NIC0_QM0_GWBW_MSG_EN_4_CQF_WD_EWW_SHIFT                      1
#define NIC0_QM0_GWBW_MSG_EN_4_CQF_WD_EWW_MASK                       0x2
#define NIC0_QM0_GWBW_MSG_EN_4_CP_WD_EWW_SHIFT                       2
#define NIC0_QM0_GWBW_MSG_EN_4_CP_WD_EWW_MASK                        0x4
#define NIC0_QM0_GWBW_MSG_EN_4_CP_UNDEF_CMD_EWW_SHIFT                3
#define NIC0_QM0_GWBW_MSG_EN_4_CP_UNDEF_CMD_EWW_MASK                 0x8
#define NIC0_QM0_GWBW_MSG_EN_4_CP_STOP_OP_SHIFT                      4
#define NIC0_QM0_GWBW_MSG_EN_4_CP_STOP_OP_MASK                       0x10
#define NIC0_QM0_GWBW_MSG_EN_4_CP_MSG_WW_EWW_SHIFT                   5
#define NIC0_QM0_GWBW_MSG_EN_4_CP_MSG_WW_EWW_MASK                    0x20
#define NIC0_QM0_GWBW_MSG_EN_4_CP_WWEG_EWW_SHIFT                     6
#define NIC0_QM0_GWBW_MSG_EN_4_CP_WWEG_EWW_MASK                      0x40
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE0_OVF_EWW_SHIFT               8
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE0_OVF_EWW_MASK                0x100
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE1_OVF_EWW_SHIFT               9
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE1_OVF_EWW_MASK                0x200
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE2_OVF_EWW_SHIFT               10
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE2_OVF_EWW_MASK                0x400
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE3_OVF_EWW_SHIFT               11
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE3_OVF_EWW_MASK                0x800
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE0_UDF_EWW_SHIFT               12
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE0_UDF_EWW_MASK                0x1000
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE1_UDF_EWW_SHIFT               13
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE1_UDF_EWW_MASK                0x2000
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE2_UDF_EWW_SHIFT               14
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE2_UDF_EWW_MASK                0x4000
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE3_UDF_EWW_SHIFT               15
#define NIC0_QM0_GWBW_MSG_EN_4_CP_FENCE3_UDF_EWW_MASK                0x8000

/* NIC0_QM0_PQ_BASE_WO */
#define NIC0_QM0_PQ_BASE_WO_VAW_SHIFT                                0
#define NIC0_QM0_PQ_BASE_WO_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_PQ_BASE_HI */
#define NIC0_QM0_PQ_BASE_HI_VAW_SHIFT                                0
#define NIC0_QM0_PQ_BASE_HI_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_PQ_SIZE */
#define NIC0_QM0_PQ_SIZE_VAW_SHIFT                                   0
#define NIC0_QM0_PQ_SIZE_VAW_MASK                                    0xFFFFFFFF

/* NIC0_QM0_PQ_PI */
#define NIC0_QM0_PQ_PI_VAW_SHIFT                                     0
#define NIC0_QM0_PQ_PI_VAW_MASK                                      0xFFFFFFFF

/* NIC0_QM0_PQ_CI */
#define NIC0_QM0_PQ_CI_VAW_SHIFT                                     0
#define NIC0_QM0_PQ_CI_VAW_MASK                                      0xFFFFFFFF

/* NIC0_QM0_PQ_CFG0 */
#define NIC0_QM0_PQ_CFG0_WESEWVED_SHIFT                              0
#define NIC0_QM0_PQ_CFG0_WESEWVED_MASK                               0x1

/* NIC0_QM0_PQ_CFG1 */
#define NIC0_QM0_PQ_CFG1_CWEDIT_WIM_SHIFT                            0
#define NIC0_QM0_PQ_CFG1_CWEDIT_WIM_MASK                             0xFFFF
#define NIC0_QM0_PQ_CFG1_MAX_INFWIGHT_SHIFT                          16
#define NIC0_QM0_PQ_CFG1_MAX_INFWIGHT_MASK                           0xFFFF0000

/* NIC0_QM0_PQ_AWUSEW_31_11 */
#define NIC0_QM0_PQ_AWUSEW_31_11_VAW_SHIFT                           0
#define NIC0_QM0_PQ_AWUSEW_31_11_VAW_MASK                            0x1FFFFF

/* NIC0_QM0_PQ_STS0 */
#define NIC0_QM0_PQ_STS0_PQ_CWEDIT_CNT_SHIFT                         0
#define NIC0_QM0_PQ_STS0_PQ_CWEDIT_CNT_MASK                          0xFFFF
#define NIC0_QM0_PQ_STS0_PQ_FWEE_CNT_SHIFT                           16
#define NIC0_QM0_PQ_STS0_PQ_FWEE_CNT_MASK                            0xFFFF0000

/* NIC0_QM0_PQ_STS1 */
#define NIC0_QM0_PQ_STS1_PQ_INFWIGHT_CNT_SHIFT                       0
#define NIC0_QM0_PQ_STS1_PQ_INFWIGHT_CNT_MASK                        0xFFFF
#define NIC0_QM0_PQ_STS1_PQ_BUF_EMPTY_SHIFT                          30
#define NIC0_QM0_PQ_STS1_PQ_BUF_EMPTY_MASK                           0x40000000
#define NIC0_QM0_PQ_STS1_PQ_BUSY_SHIFT                               31
#define NIC0_QM0_PQ_STS1_PQ_BUSY_MASK                                0x80000000

/* NIC0_QM0_CQ_CFG0 */
#define NIC0_QM0_CQ_CFG0_WESEWVED_SHIFT                              0
#define NIC0_QM0_CQ_CFG0_WESEWVED_MASK                               0x1

/* NIC0_QM0_CQ_CFG1 */
#define NIC0_QM0_CQ_CFG1_CWEDIT_WIM_SHIFT                            0
#define NIC0_QM0_CQ_CFG1_CWEDIT_WIM_MASK                             0xFFFF
#define NIC0_QM0_CQ_CFG1_MAX_INFWIGHT_SHIFT                          16
#define NIC0_QM0_CQ_CFG1_MAX_INFWIGHT_MASK                           0xFFFF0000

/* NIC0_QM0_CQ_AWUSEW_31_11 */
#define NIC0_QM0_CQ_AWUSEW_31_11_VAW_SHIFT                           0
#define NIC0_QM0_CQ_AWUSEW_31_11_VAW_MASK                            0x1FFFFF

/* NIC0_QM0_CQ_STS0 */
#define NIC0_QM0_CQ_STS0_CQ_CWEDIT_CNT_SHIFT                         0
#define NIC0_QM0_CQ_STS0_CQ_CWEDIT_CNT_MASK                          0xFFFF
#define NIC0_QM0_CQ_STS0_CQ_FWEE_CNT_SHIFT                           16
#define NIC0_QM0_CQ_STS0_CQ_FWEE_CNT_MASK                            0xFFFF0000

/* NIC0_QM0_CQ_STS1 */
#define NIC0_QM0_CQ_STS1_CQ_INFWIGHT_CNT_SHIFT                       0
#define NIC0_QM0_CQ_STS1_CQ_INFWIGHT_CNT_MASK                        0xFFFF
#define NIC0_QM0_CQ_STS1_CQ_BUF_EMPTY_SHIFT                          30
#define NIC0_QM0_CQ_STS1_CQ_BUF_EMPTY_MASK                           0x40000000
#define NIC0_QM0_CQ_STS1_CQ_BUSY_SHIFT                               31
#define NIC0_QM0_CQ_STS1_CQ_BUSY_MASK                                0x80000000

/* NIC0_QM0_CQ_PTW_WO_0 */
#define NIC0_QM0_CQ_PTW_WO_0_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_WO_0_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_0 */
#define NIC0_QM0_CQ_PTW_HI_0_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_HI_0_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_0 */
#define NIC0_QM0_CQ_TSIZE_0_VAW_SHIFT                                0
#define NIC0_QM0_CQ_TSIZE_0_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_0 */
#define NIC0_QM0_CQ_CTW_0_WPT_SHIFT                                  0
#define NIC0_QM0_CQ_CTW_0_WPT_MASK                                   0xFFFF
#define NIC0_QM0_CQ_CTW_0_CTW_SHIFT                                  16
#define NIC0_QM0_CQ_CTW_0_CTW_MASK                                   0xFFFF0000

/* NIC0_QM0_CQ_PTW_WO_1 */
#define NIC0_QM0_CQ_PTW_WO_1_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_WO_1_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_1 */
#define NIC0_QM0_CQ_PTW_HI_1_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_HI_1_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_1 */
#define NIC0_QM0_CQ_TSIZE_1_VAW_SHIFT                                0
#define NIC0_QM0_CQ_TSIZE_1_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_1 */
#define NIC0_QM0_CQ_CTW_1_WPT_SHIFT                                  0
#define NIC0_QM0_CQ_CTW_1_WPT_MASK                                   0xFFFF
#define NIC0_QM0_CQ_CTW_1_CTW_SHIFT                                  16
#define NIC0_QM0_CQ_CTW_1_CTW_MASK                                   0xFFFF0000

/* NIC0_QM0_CQ_PTW_WO_2 */
#define NIC0_QM0_CQ_PTW_WO_2_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_WO_2_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_2 */
#define NIC0_QM0_CQ_PTW_HI_2_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_HI_2_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_2 */
#define NIC0_QM0_CQ_TSIZE_2_VAW_SHIFT                                0
#define NIC0_QM0_CQ_TSIZE_2_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_2 */
#define NIC0_QM0_CQ_CTW_2_WPT_SHIFT                                  0
#define NIC0_QM0_CQ_CTW_2_WPT_MASK                                   0xFFFF
#define NIC0_QM0_CQ_CTW_2_CTW_SHIFT                                  16
#define NIC0_QM0_CQ_CTW_2_CTW_MASK                                   0xFFFF0000

/* NIC0_QM0_CQ_PTW_WO_3 */
#define NIC0_QM0_CQ_PTW_WO_3_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_WO_3_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_3 */
#define NIC0_QM0_CQ_PTW_HI_3_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_HI_3_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_3 */
#define NIC0_QM0_CQ_TSIZE_3_VAW_SHIFT                                0
#define NIC0_QM0_CQ_TSIZE_3_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_3 */
#define NIC0_QM0_CQ_CTW_3_WPT_SHIFT                                  0
#define NIC0_QM0_CQ_CTW_3_WPT_MASK                                   0xFFFF
#define NIC0_QM0_CQ_CTW_3_CTW_SHIFT                                  16
#define NIC0_QM0_CQ_CTW_3_CTW_MASK                                   0xFFFF0000

/* NIC0_QM0_CQ_PTW_WO_4 */
#define NIC0_QM0_CQ_PTW_WO_4_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_WO_4_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_4 */
#define NIC0_QM0_CQ_PTW_HI_4_VAW_SHIFT                               0
#define NIC0_QM0_CQ_PTW_HI_4_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_4 */
#define NIC0_QM0_CQ_TSIZE_4_VAW_SHIFT                                0
#define NIC0_QM0_CQ_TSIZE_4_VAW_MASK                                 0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_4 */
#define NIC0_QM0_CQ_CTW_4_WPT_SHIFT                                  0
#define NIC0_QM0_CQ_CTW_4_WPT_MASK                                   0xFFFF
#define NIC0_QM0_CQ_CTW_4_CTW_SHIFT                                  16
#define NIC0_QM0_CQ_CTW_4_CTW_MASK                                   0xFFFF0000

/* NIC0_QM0_CQ_PTW_WO_STS */
#define NIC0_QM0_CQ_PTW_WO_STS_VAW_SHIFT                             0
#define NIC0_QM0_CQ_PTW_WO_STS_VAW_MASK                              0xFFFFFFFF

/* NIC0_QM0_CQ_PTW_HI_STS */
#define NIC0_QM0_CQ_PTW_HI_STS_VAW_SHIFT                             0
#define NIC0_QM0_CQ_PTW_HI_STS_VAW_MASK                              0xFFFFFFFF

/* NIC0_QM0_CQ_TSIZE_STS */
#define NIC0_QM0_CQ_TSIZE_STS_VAW_SHIFT                              0
#define NIC0_QM0_CQ_TSIZE_STS_VAW_MASK                               0xFFFFFFFF

/* NIC0_QM0_CQ_CTW_STS */
#define NIC0_QM0_CQ_CTW_STS_WPT_SHIFT                                0
#define NIC0_QM0_CQ_CTW_STS_WPT_MASK                                 0xFFFF
#define NIC0_QM0_CQ_CTW_STS_CTW_SHIFT                                16
#define NIC0_QM0_CQ_CTW_STS_CTW_MASK                                 0xFFFF0000

/* NIC0_QM0_CQ_IFIFO_CNT */
#define NIC0_QM0_CQ_IFIFO_CNT_VAW_SHIFT                              0
#define NIC0_QM0_CQ_IFIFO_CNT_VAW_MASK                               0x3

/* NIC0_QM0_CP_MSG_BASE0_ADDW_WO */
#define NIC0_QM0_CP_MSG_BASE0_ADDW_WO_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE0_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE0_ADDW_HI */
#define NIC0_QM0_CP_MSG_BASE0_ADDW_HI_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE0_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE1_ADDW_WO */
#define NIC0_QM0_CP_MSG_BASE1_ADDW_WO_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE1_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE1_ADDW_HI */
#define NIC0_QM0_CP_MSG_BASE1_ADDW_HI_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE1_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE2_ADDW_WO */
#define NIC0_QM0_CP_MSG_BASE2_ADDW_WO_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE2_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE2_ADDW_HI */
#define NIC0_QM0_CP_MSG_BASE2_ADDW_HI_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE2_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE3_ADDW_WO */
#define NIC0_QM0_CP_MSG_BASE3_ADDW_WO_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE3_ADDW_WO_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_MSG_BASE3_ADDW_HI */
#define NIC0_QM0_CP_MSG_BASE3_ADDW_HI_VAW_SHIFT                      0
#define NIC0_QM0_CP_MSG_BASE3_ADDW_HI_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_WDMA_TSIZE_OFFSET */
#define NIC0_QM0_CP_WDMA_TSIZE_OFFSET_VAW_SHIFT                      0
#define NIC0_QM0_CP_WDMA_TSIZE_OFFSET_VAW_MASK                       0xFFFFFFFF

/* NIC0_QM0_CP_WDMA_SWC_BASE_WO_OFFSET */
#define NIC0_QM0_CP_WDMA_SWC_BASE_WO_OFFSET_VAW_SHIFT                0
#define NIC0_QM0_CP_WDMA_SWC_BASE_WO_OFFSET_VAW_MASK                 0xFFFFFFFF

/* NIC0_QM0_CP_WDMA_DST_BASE_WO_OFFSET */
#define NIC0_QM0_CP_WDMA_DST_BASE_WO_OFFSET_VAW_SHIFT                0
#define NIC0_QM0_CP_WDMA_DST_BASE_WO_OFFSET_VAW_MASK                 0xFFFFFFFF

/* NIC0_QM0_CP_FENCE0_WDATA */
#define NIC0_QM0_CP_FENCE0_WDATA_INC_VAW_SHIFT                       0
#define NIC0_QM0_CP_FENCE0_WDATA_INC_VAW_MASK                        0xF

/* NIC0_QM0_CP_FENCE1_WDATA */
#define NIC0_QM0_CP_FENCE1_WDATA_INC_VAW_SHIFT                       0
#define NIC0_QM0_CP_FENCE1_WDATA_INC_VAW_MASK                        0xF

/* NIC0_QM0_CP_FENCE2_WDATA */
#define NIC0_QM0_CP_FENCE2_WDATA_INC_VAW_SHIFT                       0
#define NIC0_QM0_CP_FENCE2_WDATA_INC_VAW_MASK                        0xF

/* NIC0_QM0_CP_FENCE3_WDATA */
#define NIC0_QM0_CP_FENCE3_WDATA_INC_VAW_SHIFT                       0
#define NIC0_QM0_CP_FENCE3_WDATA_INC_VAW_MASK                        0xF

/* NIC0_QM0_CP_FENCE0_CNT */
#define NIC0_QM0_CP_FENCE0_CNT_VAW_SHIFT                             0
#define NIC0_QM0_CP_FENCE0_CNT_VAW_MASK                              0x3FFF

/* NIC0_QM0_CP_FENCE1_CNT */
#define NIC0_QM0_CP_FENCE1_CNT_VAW_SHIFT                             0
#define NIC0_QM0_CP_FENCE1_CNT_VAW_MASK                              0x3FFF

/* NIC0_QM0_CP_FENCE2_CNT */
#define NIC0_QM0_CP_FENCE2_CNT_VAW_SHIFT                             0
#define NIC0_QM0_CP_FENCE2_CNT_VAW_MASK                              0x3FFF

/* NIC0_QM0_CP_FENCE3_CNT */
#define NIC0_QM0_CP_FENCE3_CNT_VAW_SHIFT                             0
#define NIC0_QM0_CP_FENCE3_CNT_VAW_MASK                              0x3FFF

/* NIC0_QM0_CP_STS */
#define NIC0_QM0_CP_STS_MSG_INFWIGHT_CNT_SHIFT                       0
#define NIC0_QM0_CP_STS_MSG_INFWIGHT_CNT_MASK                        0xFFFF
#define NIC0_QM0_CP_STS_EWDY_SHIFT                                   16
#define NIC0_QM0_CP_STS_EWDY_MASK                                    0x10000
#define NIC0_QM0_CP_STS_WWDY_SHIFT                                   17
#define NIC0_QM0_CP_STS_WWDY_MASK                                    0x20000
#define NIC0_QM0_CP_STS_MWDY_SHIFT                                   18
#define NIC0_QM0_CP_STS_MWDY_MASK                                    0x40000
#define NIC0_QM0_CP_STS_SW_STOP_SHIFT                                19
#define NIC0_QM0_CP_STS_SW_STOP_MASK                                 0x80000
#define NIC0_QM0_CP_STS_FENCE_ID_SHIFT                               20
#define NIC0_QM0_CP_STS_FENCE_ID_MASK                                0x300000
#define NIC0_QM0_CP_STS_FENCE_IN_PWOGWESS_SHIFT                      22
#define NIC0_QM0_CP_STS_FENCE_IN_PWOGWESS_MASK                       0x400000

/* NIC0_QM0_CP_CUWWENT_INST_WO */
#define NIC0_QM0_CP_CUWWENT_INST_WO_VAW_SHIFT                        0
#define NIC0_QM0_CP_CUWWENT_INST_WO_VAW_MASK                         0xFFFFFFFF

/* NIC0_QM0_CP_CUWWENT_INST_HI */
#define NIC0_QM0_CP_CUWWENT_INST_HI_VAW_SHIFT                        0
#define NIC0_QM0_CP_CUWWENT_INST_HI_VAW_MASK                         0xFFFFFFFF

/* NIC0_QM0_CP_BAWWIEW_CFG */
#define NIC0_QM0_CP_BAWWIEW_CFG_EBGUAWD_SHIFT                        0
#define NIC0_QM0_CP_BAWWIEW_CFG_EBGUAWD_MASK                         0xFFF
#define NIC0_QM0_CP_BAWWIEW_CFG_WBGUAWD_SHIFT                        16
#define NIC0_QM0_CP_BAWWIEW_CFG_WBGUAWD_MASK                         0xF0000

/* NIC0_QM0_CP_DBG_0 */
#define NIC0_QM0_CP_DBG_0_CS_SHIFT                                   0
#define NIC0_QM0_CP_DBG_0_CS_MASK                                    0xF
#define NIC0_QM0_CP_DBG_0_EB_CNT_NOT_ZEWO_SHIFT                      4
#define NIC0_QM0_CP_DBG_0_EB_CNT_NOT_ZEWO_MASK                       0x10
#define NIC0_QM0_CP_DBG_0_BUWK_CNT_NOT_ZEWO_SHIFT                    5
#define NIC0_QM0_CP_DBG_0_BUWK_CNT_NOT_ZEWO_MASK                     0x20
#define NIC0_QM0_CP_DBG_0_MWEB_STAWW_SHIFT                           6
#define NIC0_QM0_CP_DBG_0_MWEB_STAWW_MASK                            0x40
#define NIC0_QM0_CP_DBG_0_STAWW_SHIFT                                7
#define NIC0_QM0_CP_DBG_0_STAWW_MASK                                 0x80

/* NIC0_QM0_CP_AWUSEW_31_11 */
#define NIC0_QM0_CP_AWUSEW_31_11_VAW_SHIFT                           0
#define NIC0_QM0_CP_AWUSEW_31_11_VAW_MASK                            0x1FFFFF

/* NIC0_QM0_CP_AWUSEW_31_11 */
#define NIC0_QM0_CP_AWUSEW_31_11_VAW_SHIFT                           0
#define NIC0_QM0_CP_AWUSEW_31_11_VAW_MASK                            0x1FFFFF

/* NIC0_QM0_AWB_CFG_0 */
#define NIC0_QM0_AWB_CFG_0_TYPE_SHIFT                                0
#define NIC0_QM0_AWB_CFG_0_TYPE_MASK                                 0x1
#define NIC0_QM0_AWB_CFG_0_IS_MASTEW_SHIFT                           4
#define NIC0_QM0_AWB_CFG_0_IS_MASTEW_MASK                            0x10
#define NIC0_QM0_AWB_CFG_0_EN_SHIFT                                  8
#define NIC0_QM0_AWB_CFG_0_EN_MASK                                   0x100
#define NIC0_QM0_AWB_CFG_0_MASK_SHIFT                                12
#define NIC0_QM0_AWB_CFG_0_MASK_MASK                                 0xF000
#define NIC0_QM0_AWB_CFG_0_MST_MSG_NOSTAWW_SHIFT                     16
#define NIC0_QM0_AWB_CFG_0_MST_MSG_NOSTAWW_MASK                      0x10000

/* NIC0_QM0_AWB_CHOISE_Q_PUSH */
#define NIC0_QM0_AWB_CHOISE_Q_PUSH_VAW_SHIFT                         0
#define NIC0_QM0_AWB_CHOISE_Q_PUSH_VAW_MASK                          0x3

/* NIC0_QM0_AWB_WWW_WEIGHT */
#define NIC0_QM0_AWB_WWW_WEIGHT_VAW_SHIFT                            0
#define NIC0_QM0_AWB_WWW_WEIGHT_VAW_MASK                             0xFFFFFFFF

/* NIC0_QM0_AWB_CFG_1 */
#define NIC0_QM0_AWB_CFG_1_CWW_SHIFT                                 0
#define NIC0_QM0_AWB_CFG_1_CWW_MASK                                  0x1

/* NIC0_QM0_AWB_MST_AVAIW_CWED */
#define NIC0_QM0_AWB_MST_AVAIW_CWED_VAW_SHIFT                        0
#define NIC0_QM0_AWB_MST_AVAIW_CWED_VAW_MASK                         0x7F

/* NIC0_QM0_AWB_MST_CWED_INC */
#define NIC0_QM0_AWB_MST_CWED_INC_VAW_SHIFT                          0
#define NIC0_QM0_AWB_MST_CWED_INC_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_AWB_MST_CHOISE_PUSH_OFST */
#define NIC0_QM0_AWB_MST_CHOISE_PUSH_OFST_VAW_SHIFT                  0
#define NIC0_QM0_AWB_MST_CHOISE_PUSH_OFST_VAW_MASK                   0xFFFFFFFF

/* NIC0_QM0_AWB_SWV_MASTEW_INC_CWED_OFST */
#define NIC0_QM0_AWB_SWV_MASTEW_INC_CWED_OFST_VAW_SHIFT              0
#define NIC0_QM0_AWB_SWV_MASTEW_INC_CWED_OFST_VAW_MASK               0xFFFFFFFF

/* NIC0_QM0_AWB_MST_SWAVE_EN */
#define NIC0_QM0_AWB_MST_SWAVE_EN_VAW_SHIFT                          0
#define NIC0_QM0_AWB_MST_SWAVE_EN_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_AWB_MST_QUIET_PEW */
#define NIC0_QM0_AWB_MST_QUIET_PEW_VAW_SHIFT                         0
#define NIC0_QM0_AWB_MST_QUIET_PEW_VAW_MASK                          0xFFFFFFFF

/* NIC0_QM0_AWB_SWV_CHOISE_WDT */
#define NIC0_QM0_AWB_SWV_CHOISE_WDT_VAW_SHIFT                        0
#define NIC0_QM0_AWB_SWV_CHOISE_WDT_VAW_MASK                         0xFFFFFFFF

/* NIC0_QM0_AWB_SWV_ID */
#define NIC0_QM0_AWB_SWV_ID_VAW_SHIFT                                0
#define NIC0_QM0_AWB_SWV_ID_VAW_MASK                                 0x1F

/* NIC0_QM0_AWB_MSG_MAX_INFWIGHT */
#define NIC0_QM0_AWB_MSG_MAX_INFWIGHT_VAW_SHIFT                      0
#define NIC0_QM0_AWB_MSG_MAX_INFWIGHT_VAW_MASK                       0x3F

/* NIC0_QM0_AWB_MSG_AWUSEW_31_11 */
#define NIC0_QM0_AWB_MSG_AWUSEW_31_11_VAW_SHIFT                      0
#define NIC0_QM0_AWB_MSG_AWUSEW_31_11_VAW_MASK                       0x1FFFFF

/* NIC0_QM0_AWB_MSG_AWUSEW_SEC_PWOP */
#define NIC0_QM0_AWB_MSG_AWUSEW_SEC_PWOP_ASID_SHIFT                  0
#define NIC0_QM0_AWB_MSG_AWUSEW_SEC_PWOP_ASID_MASK                   0x3FF
#define NIC0_QM0_AWB_MSG_AWUSEW_SEC_PWOP_MMBP_SHIFT                  10
#define NIC0_QM0_AWB_MSG_AWUSEW_SEC_PWOP_MMBP_MASK                   0x400

/* NIC0_QM0_AWB_MSG_AWUSEW_NON_SEC_PWOP */
#define NIC0_QM0_AWB_MSG_AWUSEW_NON_SEC_PWOP_ASID_SHIFT              0
#define NIC0_QM0_AWB_MSG_AWUSEW_NON_SEC_PWOP_ASID_MASK               0x3FF
#define NIC0_QM0_AWB_MSG_AWUSEW_NON_SEC_PWOP_MMBP_SHIFT              10
#define NIC0_QM0_AWB_MSG_AWUSEW_NON_SEC_PWOP_MMBP_MASK               0x400

/* NIC0_QM0_AWB_BASE_WO */
#define NIC0_QM0_AWB_BASE_WO_VAW_SHIFT                               0
#define NIC0_QM0_AWB_BASE_WO_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_AWB_BASE_HI */
#define NIC0_QM0_AWB_BASE_HI_VAW_SHIFT                               0
#define NIC0_QM0_AWB_BASE_HI_VAW_MASK                                0xFFFFFFFF

/* NIC0_QM0_AWB_STATE_STS */
#define NIC0_QM0_AWB_STATE_STS_VAW_SHIFT                             0
#define NIC0_QM0_AWB_STATE_STS_VAW_MASK                              0xFFFFFFFF

/* NIC0_QM0_AWB_CHOISE_FUWWNESS_STS */
#define NIC0_QM0_AWB_CHOISE_FUWWNESS_STS_VAW_SHIFT                   0
#define NIC0_QM0_AWB_CHOISE_FUWWNESS_STS_VAW_MASK                    0x7F

/* NIC0_QM0_AWB_MSG_STS */
#define NIC0_QM0_AWB_MSG_STS_FUWW_SHIFT                              0
#define NIC0_QM0_AWB_MSG_STS_FUWW_MASK                               0x1
#define NIC0_QM0_AWB_MSG_STS_NO_INFWIGHT_SHIFT                       1
#define NIC0_QM0_AWB_MSG_STS_NO_INFWIGHT_MASK                        0x2

/* NIC0_QM0_AWB_SWV_CHOISE_Q_HEAD */
#define NIC0_QM0_AWB_SWV_CHOISE_Q_HEAD_VAW_SHIFT                     0
#define NIC0_QM0_AWB_SWV_CHOISE_Q_HEAD_VAW_MASK                      0x3

/* NIC0_QM0_AWB_EWW_CAUSE */
#define NIC0_QM0_AWB_EWW_CAUSE_CHOISE_OVF_SHIFT                      0
#define NIC0_QM0_AWB_EWW_CAUSE_CHOISE_OVF_MASK                       0x1
#define NIC0_QM0_AWB_EWW_CAUSE_CHOISE_WDT_SHIFT                      1
#define NIC0_QM0_AWB_EWW_CAUSE_CHOISE_WDT_MASK                       0x2
#define NIC0_QM0_AWB_EWW_CAUSE_AXI_WBW_EWW_SHIFT                     2
#define NIC0_QM0_AWB_EWW_CAUSE_AXI_WBW_EWW_MASK                      0x4

/* NIC0_QM0_AWB_EWW_MSG_EN */
#define NIC0_QM0_AWB_EWW_MSG_EN_CHOISE_OVF_SHIFT                     0
#define NIC0_QM0_AWB_EWW_MSG_EN_CHOISE_OVF_MASK                      0x1
#define NIC0_QM0_AWB_EWW_MSG_EN_CHOISE_WDT_SHIFT                     1
#define NIC0_QM0_AWB_EWW_MSG_EN_CHOISE_WDT_MASK                      0x2
#define NIC0_QM0_AWB_EWW_MSG_EN_AXI_WBW_EWW_SHIFT                    2
#define NIC0_QM0_AWB_EWW_MSG_EN_AXI_WBW_EWW_MASK                     0x4

/* NIC0_QM0_AWB_EWW_STS_DWP */
#define NIC0_QM0_AWB_EWW_STS_DWP_VAW_SHIFT                           0
#define NIC0_QM0_AWB_EWW_STS_DWP_VAW_MASK                            0x3

/* NIC0_QM0_AWB_MST_CWED_STS */
#define NIC0_QM0_AWB_MST_CWED_STS_VAW_SHIFT                          0
#define NIC0_QM0_AWB_MST_CWED_STS_VAW_MASK                           0x7F

/* NIC0_QM0_CGM_CFG */
#define NIC0_QM0_CGM_CFG_IDWE_TH_SHIFT                               0
#define NIC0_QM0_CGM_CFG_IDWE_TH_MASK                                0xFFF
#define NIC0_QM0_CGM_CFG_G2F_TH_SHIFT                                16
#define NIC0_QM0_CGM_CFG_G2F_TH_MASK                                 0xFF0000
#define NIC0_QM0_CGM_CFG_CP_IDWE_MASK_SHIFT                          24
#define NIC0_QM0_CGM_CFG_CP_IDWE_MASK_MASK                           0x1F000000
#define NIC0_QM0_CGM_CFG_EN_SHIFT                                    31
#define NIC0_QM0_CGM_CFG_EN_MASK                                     0x80000000

/* NIC0_QM0_CGM_STS */
#define NIC0_QM0_CGM_STS_ST_SHIFT                                    0
#define NIC0_QM0_CGM_STS_ST_MASK                                     0x3
#define NIC0_QM0_CGM_STS_CG_SHIFT                                    4
#define NIC0_QM0_CGM_STS_CG_MASK                                     0x10
#define NIC0_QM0_CGM_STS_AGENT_IDWE_SHIFT                            8
#define NIC0_QM0_CGM_STS_AGENT_IDWE_MASK                             0x100
#define NIC0_QM0_CGM_STS_AXI_IDWE_SHIFT                              9
#define NIC0_QM0_CGM_STS_AXI_IDWE_MASK                               0x200
#define NIC0_QM0_CGM_STS_CP_IDWE_SHIFT                               10
#define NIC0_QM0_CGM_STS_CP_IDWE_MASK                                0x400

/* NIC0_QM0_CGM_CFG1 */
#define NIC0_QM0_CGM_CFG1_MASK_TH_SHIFT                              0
#define NIC0_QM0_CGM_CFG1_MASK_TH_MASK                               0xFF

/* NIC0_QM0_WOCAW_WANGE_BASE */
#define NIC0_QM0_WOCAW_WANGE_BASE_VAW_SHIFT                          0
#define NIC0_QM0_WOCAW_WANGE_BASE_VAW_MASK                           0xFFFF

/* NIC0_QM0_WOCAW_WANGE_SIZE */
#define NIC0_QM0_WOCAW_WANGE_SIZE_VAW_SHIFT                          0
#define NIC0_QM0_WOCAW_WANGE_SIZE_VAW_MASK                           0xFFFF

/* NIC0_QM0_CSMW_STWICT_PWIO_CFG */
#define NIC0_QM0_CSMW_STWICT_PWIO_CFG_TYPE_SHIFT                     0
#define NIC0_QM0_CSMW_STWICT_PWIO_CFG_TYPE_MASK                      0x1

/* NIC0_QM0_HBW_WD_WATE_WIM_CFG_1 */
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_1_TOUT_SHIFT                    0
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_1_TOUT_MASK                     0xFF
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_1_EN_SHIFT                      31
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_1_EN_MASK                       0x80000000

/* NIC0_QM0_WBW_WW_WATE_WIM_CFG_0 */
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_0_WST_TOKEN_SHIFT               0
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_0_WST_TOKEN_MASK                0xFF
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_0_SAT_SHIFT                     16
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_0_SAT_MASK                      0xFF0000

/* NIC0_QM0_WBW_WW_WATE_WIM_CFG_1 */
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_1_TOUT_SHIFT                    0
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_1_TOUT_MASK                     0xFF
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_1_EN_SHIFT                      31
#define NIC0_QM0_WBW_WW_WATE_WIM_CFG_1_EN_MASK                       0x80000000

/* NIC0_QM0_HBW_WD_WATE_WIM_CFG_0 */
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_0_WST_TOKEN_SHIFT               0
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_0_WST_TOKEN_MASK                0xFF
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_0_SAT_SHIFT                     16
#define NIC0_QM0_HBW_WD_WATE_WIM_CFG_0_SAT_MASK                      0xFF0000

/* NIC0_QM0_GWBW_AXCACHE */
#define NIC0_QM0_GWBW_AXCACHE_AW_SHIFT                               0
#define NIC0_QM0_GWBW_AXCACHE_AW_MASK                                0xF
#define NIC0_QM0_GWBW_AXCACHE_AW_SHIFT                               16
#define NIC0_QM0_GWBW_AXCACHE_AW_MASK                                0xF0000

/* NIC0_QM0_IND_GW_APB_CFG */
#define NIC0_QM0_IND_GW_APB_CFG_ADDW_SHIFT                           0
#define NIC0_QM0_IND_GW_APB_CFG_ADDW_MASK                            0x7FFFFFFF
#define NIC0_QM0_IND_GW_APB_CFG_CMD_SHIFT                            31
#define NIC0_QM0_IND_GW_APB_CFG_CMD_MASK                             0x80000000

/* NIC0_QM0_IND_GW_APB_WDATA */
#define NIC0_QM0_IND_GW_APB_WDATA_VAW_SHIFT                          0
#define NIC0_QM0_IND_GW_APB_WDATA_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_IND_GW_APB_WDATA */
#define NIC0_QM0_IND_GW_APB_WDATA_VAW_SHIFT                          0
#define NIC0_QM0_IND_GW_APB_WDATA_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_IND_GW_APB_STATUS */
#define NIC0_QM0_IND_GW_APB_STATUS_WDY_SHIFT                         0
#define NIC0_QM0_IND_GW_APB_STATUS_WDY_MASK                          0x1
#define NIC0_QM0_IND_GW_APB_STATUS_EWW_SHIFT                         1
#define NIC0_QM0_IND_GW_APB_STATUS_EWW_MASK                          0x2

/* NIC0_QM0_GWBW_EWW_ADDW_WO */
#define NIC0_QM0_GWBW_EWW_ADDW_WO_VAW_SHIFT                          0
#define NIC0_QM0_GWBW_EWW_ADDW_WO_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_GWBW_EWW_ADDW_HI */
#define NIC0_QM0_GWBW_EWW_ADDW_HI_VAW_SHIFT                          0
#define NIC0_QM0_GWBW_EWW_ADDW_HI_VAW_MASK                           0xFFFFFFFF

/* NIC0_QM0_GWBW_EWW_WDATA */
#define NIC0_QM0_GWBW_EWW_WDATA_VAW_SHIFT                            0
#define NIC0_QM0_GWBW_EWW_WDATA_VAW_MASK                             0xFFFFFFFF

/* NIC0_QM0_GWBW_MEM_INIT_BUSY */
#define NIC0_QM0_GWBW_MEM_INIT_BUSY_WBUF_SHIFT                       0
#define NIC0_QM0_GWBW_MEM_INIT_BUSY_WBUF_MASK                        0xF

#endif /* ASIC_WEG_NIC0_QM0_MASKS_H_ */
