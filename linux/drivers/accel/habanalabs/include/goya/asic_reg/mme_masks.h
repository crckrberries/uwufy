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

#ifndef ASIC_WEG_MME_MASKS_H_
#define ASIC_WEG_MME_MASKS_H_

/*
 *****************************************
 *   MME (Pwototype: MME)
 *****************************************
 */

/* MME_AWCH_STATUS */
#define MME_AWCH_STATUS_A_SHIFT                                      0
#define MME_AWCH_STATUS_A_MASK                                       0x1
#define MME_AWCH_STATUS_B_SHIFT                                      1
#define MME_AWCH_STATUS_B_MASK                                       0x2
#define MME_AWCH_STATUS_CIN_SHIFT                                    2
#define MME_AWCH_STATUS_CIN_MASK                                     0x4
#define MME_AWCH_STATUS_COUT_SHIFT                                   3
#define MME_AWCH_STATUS_COUT_MASK                                    0x8
#define MME_AWCH_STATUS_TE_SHIFT                                     4
#define MME_AWCH_STATUS_TE_MASK                                      0x10
#define MME_AWCH_STATUS_WD_SHIFT                                     5
#define MME_AWCH_STATUS_WD_MASK                                      0x20
#define MME_AWCH_STATUS_ST_SHIFT                                     6
#define MME_AWCH_STATUS_ST_MASK                                      0x40
#define MME_AWCH_STATUS_SB_A_EMPTY_SHIFT                             7
#define MME_AWCH_STATUS_SB_A_EMPTY_MASK                              0x80
#define MME_AWCH_STATUS_SB_B_EMPTY_SHIFT                             8
#define MME_AWCH_STATUS_SB_B_EMPTY_MASK                              0x100
#define MME_AWCH_STATUS_SB_CIN_EMPTY_SHIFT                           9
#define MME_AWCH_STATUS_SB_CIN_EMPTY_MASK                            0x200
#define MME_AWCH_STATUS_SB_COUT_EMPTY_SHIFT                          10
#define MME_AWCH_STATUS_SB_COUT_EMPTY_MASK                           0x400
#define MME_AWCH_STATUS_SM_IDWE_SHIFT                                11
#define MME_AWCH_STATUS_SM_IDWE_MASK                                 0x800
#define MME_AWCH_STATUS_WBC_AXI_IDWE_SHIFT                           12
#define MME_AWCH_STATUS_WBC_AXI_IDWE_MASK                            0xF000
#define MME_AWCH_STATUS_SBC_AXI_IDWE_SHIFT                           16
#define MME_AWCH_STATUS_SBC_AXI_IDWE_MASK                            0x30000
#define MME_AWCH_STATUS_SBB_AXI_IDWE_SHIFT                           18
#define MME_AWCH_STATUS_SBB_AXI_IDWE_MASK                            0xC0000
#define MME_AWCH_STATUS_SBA_AXI_IDWE_SHIFT                           20
#define MME_AWCH_STATUS_SBA_AXI_IDWE_MASK                            0x300000
#define MME_AWCH_STATUS_FWEE_ACCUMS_SHIFT                            22
#define MME_AWCH_STATUS_FWEE_ACCUMS_MASK                             0x1C00000

/* MME_AWCH_A_BASE_ADDW_HIGH */
#define MME_AWCH_A_BASE_ADDW_HIGH_V_SHIFT                            0
#define MME_AWCH_A_BASE_ADDW_HIGH_V_MASK                             0xFFFFFFFF

/* MME_AWCH_B_BASE_ADDW_HIGH */
#define MME_AWCH_B_BASE_ADDW_HIGH_V_SHIFT                            0
#define MME_AWCH_B_BASE_ADDW_HIGH_V_MASK                             0xFFFFFFFF

/* MME_AWCH_CIN_BASE_ADDW_HIGH */
#define MME_AWCH_CIN_BASE_ADDW_HIGH_V_SHIFT                          0
#define MME_AWCH_CIN_BASE_ADDW_HIGH_V_MASK                           0xFFFFFFFF

/* MME_AWCH_COUT_BASE_ADDW_HIGH */
#define MME_AWCH_COUT_BASE_ADDW_HIGH_V_SHIFT                         0
#define MME_AWCH_COUT_BASE_ADDW_HIGH_V_MASK                          0xFFFFFFFF

/* MME_AWCH_BIAS_BASE_ADDW_HIGH */
#define MME_AWCH_BIAS_BASE_ADDW_HIGH_V_SHIFT                         0
#define MME_AWCH_BIAS_BASE_ADDW_HIGH_V_MASK                          0xFFFFFFFF

/* MME_AWCH_A_BASE_ADDW_WOW */
#define MME_AWCH_A_BASE_ADDW_WOW_V_SHIFT                             0
#define MME_AWCH_A_BASE_ADDW_WOW_V_MASK                              0xFFFFFFFF

/* MME_AWCH_B_BASE_ADDW_WOW */
#define MME_AWCH_B_BASE_ADDW_WOW_V_SHIFT                             0
#define MME_AWCH_B_BASE_ADDW_WOW_V_MASK                              0xFFFFFFFF

/* MME_AWCH_CIN_BASE_ADDW_WOW */
#define MME_AWCH_CIN_BASE_ADDW_WOW_V_SHIFT                           0
#define MME_AWCH_CIN_BASE_ADDW_WOW_V_MASK                            0xFFFFFFFF

/* MME_AWCH_COUT_BASE_ADDW_WOW */
#define MME_AWCH_COUT_BASE_ADDW_WOW_V_SHIFT                          0
#define MME_AWCH_COUT_BASE_ADDW_WOW_V_MASK                           0xFFFFFFFF

/* MME_AWCH_BIAS_BASE_ADDW_WOW */
#define MME_AWCH_BIAS_BASE_ADDW_WOW_V_SHIFT                          0
#define MME_AWCH_BIAS_BASE_ADDW_WOW_V_MASK                           0xFFFFFFFF

/* MME_AWCH_HEADEW */
#define MME_AWCH_HEADEW_SIGNAW_MASK_SHIFT                            0
#define MME_AWCH_HEADEW_SIGNAW_MASK_MASK                             0x1F
#define MME_AWCH_HEADEW_SIGNAW_EN_SHIFT                              5
#define MME_AWCH_HEADEW_SIGNAW_EN_MASK                               0x20
#define MME_AWCH_HEADEW_TWANS_A_SHIFT                                6
#define MME_AWCH_HEADEW_TWANS_A_MASK                                 0x40
#define MME_AWCH_HEADEW_WOWEW_A_SHIFT                                7
#define MME_AWCH_HEADEW_WOWEW_A_MASK                                 0x80
#define MME_AWCH_HEADEW_ACCUM_MASK_SHIFT                             8
#define MME_AWCH_HEADEW_ACCUM_MASK_MASK                              0xF00
#define MME_AWCH_HEADEW_WOAD_BIAS_SHIFT                              12
#define MME_AWCH_HEADEW_WOAD_BIAS_MASK                               0x1000
#define MME_AWCH_HEADEW_WOAD_CIN_SHIFT                               13
#define MME_AWCH_HEADEW_WOAD_CIN_MASK                                0x2000
#define MME_AWCH_HEADEW_STOWE_OUT_SHIFT                              15
#define MME_AWCH_HEADEW_STOWE_OUT_MASK                               0x8000
#define MME_AWCH_HEADEW_ACC_WD_INC_DISABWE_SHIFT                     16
#define MME_AWCH_HEADEW_ACC_WD_INC_DISABWE_MASK                      0x10000
#define MME_AWCH_HEADEW_ADVANCE_A_SHIFT                              17
#define MME_AWCH_HEADEW_ADVANCE_A_MASK                               0x20000
#define MME_AWCH_HEADEW_ADVANCE_B_SHIFT                              18
#define MME_AWCH_HEADEW_ADVANCE_B_MASK                               0x40000
#define MME_AWCH_HEADEW_ADVANCE_CIN_SHIFT                            19
#define MME_AWCH_HEADEW_ADVANCE_CIN_MASK                             0x80000
#define MME_AWCH_HEADEW_ADVANCE_COUT_SHIFT                           20
#define MME_AWCH_HEADEW_ADVANCE_COUT_MASK                            0x100000
#define MME_AWCH_HEADEW_COMPWESSED_B_SHIFT                           21
#define MME_AWCH_HEADEW_COMPWESSED_B_MASK                            0x200000
#define MME_AWCH_HEADEW_MASK_CONV_END_SHIFT                          22
#define MME_AWCH_HEADEW_MASK_CONV_END_MASK                           0x400000
#define MME_AWCH_HEADEW_ACC_ST_INC_DISABWE_SHIFT                     23
#define MME_AWCH_HEADEW_ACC_ST_INC_DISABWE_MASK                      0x800000
#define MME_AWCH_HEADEW_AB_DATA_TYPE_SHIFT                           24
#define MME_AWCH_HEADEW_AB_DATA_TYPE_MASK                            0x3000000
#define MME_AWCH_HEADEW_CIN_DATA_TYPE_SHIFT                          26
#define MME_AWCH_HEADEW_CIN_DATA_TYPE_MASK                           0x1C000000
#define MME_AWCH_HEADEW_COUT_DATA_TYPE_SHIFT                         29
#define MME_AWCH_HEADEW_COUT_DATA_TYPE_MASK                          0xE0000000

/* MME_AWCH_KEWNEW_SIZE_MINUS_1 */
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_0_SHIFT                     0
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_0_MASK                      0xFF
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_1_SHIFT                     8
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_1_MASK                      0xFF00
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_2_SHIFT                     16
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_2_MASK                      0xFF0000
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_3_SHIFT                     24
#define MME_AWCH_KEWNEW_SIZE_MINUS_1_DIM_3_MASK                      0xFF000000

/* MME_AWCH_ASSOCIATED_DIMS */
#define MME_AWCH_ASSOCIATED_DIMS_A_0_SHIFT                           0
#define MME_AWCH_ASSOCIATED_DIMS_A_0_MASK                            0x7
#define MME_AWCH_ASSOCIATED_DIMS_B_0_SHIFT                           3
#define MME_AWCH_ASSOCIATED_DIMS_B_0_MASK                            0x38
#define MME_AWCH_ASSOCIATED_DIMS_CIN_0_SHIFT                         6
#define MME_AWCH_ASSOCIATED_DIMS_CIN_0_MASK                          0x1C0
#define MME_AWCH_ASSOCIATED_DIMS_COUT_0_SHIFT                        9
#define MME_AWCH_ASSOCIATED_DIMS_COUT_0_MASK                         0xE00
#define MME_AWCH_ASSOCIATED_DIMS_A_1_SHIFT                           16
#define MME_AWCH_ASSOCIATED_DIMS_A_1_MASK                            0x70000
#define MME_AWCH_ASSOCIATED_DIMS_B_1_SHIFT                           19
#define MME_AWCH_ASSOCIATED_DIMS_B_1_MASK                            0x380000
#define MME_AWCH_ASSOCIATED_DIMS_CIN_1_SHIFT                         22
#define MME_AWCH_ASSOCIATED_DIMS_CIN_1_MASK                          0x1C00000
#define MME_AWCH_ASSOCIATED_DIMS_COUT_1_SHIFT                        25
#define MME_AWCH_ASSOCIATED_DIMS_COUT_1_MASK                         0xE000000

/* MME_AWCH_COUT_SCAWE */
#define MME_AWCH_COUT_SCAWE_V_SHIFT                                  0
#define MME_AWCH_COUT_SCAWE_V_MASK                                   0xFFFFFFFF

/* MME_AWCH_CIN_SCAWE */
#define MME_AWCH_CIN_SCAWE_V_SHIFT                                   0
#define MME_AWCH_CIN_SCAWE_V_MASK                                    0xFFFFFFFF

/* MME_AWCH_GEMMWOWP_ZP */
#define MME_AWCH_GEMMWOWP_ZP_ZP_CIN_SHIFT                            0
#define MME_AWCH_GEMMWOWP_ZP_ZP_CIN_MASK                             0x1FF
#define MME_AWCH_GEMMWOWP_ZP_ZP_COUT_SHIFT                           9
#define MME_AWCH_GEMMWOWP_ZP_ZP_COUT_MASK                            0x3FE00
#define MME_AWCH_GEMMWOWP_ZP_ZP_B_SHIFT                              18
#define MME_AWCH_GEMMWOWP_ZP_ZP_B_MASK                               0x7FC0000
#define MME_AWCH_GEMMWOWP_ZP_GEMMWOWP_EU_EN_SHIFT                    27
#define MME_AWCH_GEMMWOWP_ZP_GEMMWOWP_EU_EN_MASK                     0x8000000
#define MME_AWCH_GEMMWOWP_ZP_ACCUM_SHIFT                             28
#define MME_AWCH_GEMMWOWP_ZP_ACCUM_MASK                              0x10000000
#define MME_AWCH_GEMMWOWP_ZP_ACCUM_BIAS_SHIFT                        29
#define MME_AWCH_GEMMWOWP_ZP_ACCUM_BIAS_MASK                         0x20000000
#define MME_AWCH_GEMMWOWP_ZP_WEWU_EN_SHIFT                           30
#define MME_AWCH_GEMMWOWP_ZP_WEWU_EN_MASK                            0x40000000

/* MME_AWCH_GEMMWOWP_EXPONENT */
#define MME_AWCH_GEMMWOWP_EXPONENT_EXPONENT_CIN_SHIFT                0
#define MME_AWCH_GEMMWOWP_EXPONENT_EXPONENT_CIN_MASK                 0x3F
#define MME_AWCH_GEMMWOWP_EXPONENT_EXPONENT_COUT_SHIFT               8
#define MME_AWCH_GEMMWOWP_EXPONENT_EXPONENT_COUT_MASK                0x3F00
#define MME_AWCH_GEMMWOWP_EXPONENT_MUW_CIN_EN_SHIFT                  16
#define MME_AWCH_GEMMWOWP_EXPONENT_MUW_CIN_EN_MASK                   0x10000
#define MME_AWCH_GEMMWOWP_EXPONENT_MUW_COUT_EN_SHIFT                 17
#define MME_AWCH_GEMMWOWP_EXPONENT_MUW_COUT_EN_MASK                  0x20000

/* MME_AWCH_A_WOI_BASE_OFFSET */
#define MME_AWCH_A_WOI_BASE_OFFSET_V_SHIFT                           0
#define MME_AWCH_A_WOI_BASE_OFFSET_V_MASK                            0xFFFFFFFF

/* MME_AWCH_A_VAWID_EWEMENTS */
#define MME_AWCH_A_VAWID_EWEMENTS_V_SHIFT                            0
#define MME_AWCH_A_VAWID_EWEMENTS_V_MASK                             0xFFFFFFFF

/* MME_AWCH_A_WOOP_STWIDE */
#define MME_AWCH_A_WOOP_STWIDE_V_SHIFT                               0
#define MME_AWCH_A_WOOP_STWIDE_V_MASK                                0xFFFFFFFF

/* MME_AWCH_A_WOI_SIZE */
#define MME_AWCH_A_WOI_SIZE_V_SHIFT                                  0
#define MME_AWCH_A_WOI_SIZE_V_MASK                                   0xFFFFFFFF

/* MME_AWCH_A_SPATIAW_STAWT_OFFSET */
#define MME_AWCH_A_SPATIAW_STAWT_OFFSET_V_SHIFT                      0
#define MME_AWCH_A_SPATIAW_STAWT_OFFSET_V_MASK                       0xFFFFFFFF

/* MME_AWCH_A_SPATIAW_STWIDE */
#define MME_AWCH_A_SPATIAW_STWIDE_V_SHIFT                            0
#define MME_AWCH_A_SPATIAW_STWIDE_V_MASK                             0xFFFFFFFF

/* MME_AWCH_A_SPATIAW_SIZE_MINUS_1 */
#define MME_AWCH_A_SPATIAW_SIZE_MINUS_1_V_SHIFT                      0
#define MME_AWCH_A_SPATIAW_SIZE_MINUS_1_V_MASK                       0xFFFFFFFF

/* MME_AWCH_B_WOI_BASE_OFFSET */
#define MME_AWCH_B_WOI_BASE_OFFSET_V_SHIFT                           0
#define MME_AWCH_B_WOI_BASE_OFFSET_V_MASK                            0xFFFFFFFF

/* MME_AWCH_B_VAWID_EWEMENTS */
#define MME_AWCH_B_VAWID_EWEMENTS_V_SHIFT                            0
#define MME_AWCH_B_VAWID_EWEMENTS_V_MASK                             0xFFFFFFFF

/* MME_AWCH_B_WOOP_STWIDE */
#define MME_AWCH_B_WOOP_STWIDE_V_SHIFT                               0
#define MME_AWCH_B_WOOP_STWIDE_V_MASK                                0xFFFFFFFF

/* MME_AWCH_B_WOI_SIZE */
#define MME_AWCH_B_WOI_SIZE_V_SHIFT                                  0
#define MME_AWCH_B_WOI_SIZE_V_MASK                                   0xFFFFFFFF

/* MME_AWCH_B_SPATIAW_STAWT_OFFSET */
#define MME_AWCH_B_SPATIAW_STAWT_OFFSET_V_SHIFT                      0
#define MME_AWCH_B_SPATIAW_STAWT_OFFSET_V_MASK                       0xFFFFFFFF

/* MME_AWCH_B_SPATIAW_STWIDE */
#define MME_AWCH_B_SPATIAW_STWIDE_V_SHIFT                            0
#define MME_AWCH_B_SPATIAW_STWIDE_V_MASK                             0xFFFFFFFF

/* MME_AWCH_B_SPATIAW_SIZE_MINUS_1 */
#define MME_AWCH_B_SPATIAW_SIZE_MINUS_1_V_SHIFT                      0
#define MME_AWCH_B_SPATIAW_SIZE_MINUS_1_V_MASK                       0xFFFFFFFF

/* MME_AWCH_C_WOI_BASE_OFFSET */
#define MME_AWCH_C_WOI_BASE_OFFSET_V_SHIFT                           0
#define MME_AWCH_C_WOI_BASE_OFFSET_V_MASK                            0xFFFFFFFF

/* MME_AWCH_C_VAWID_EWEMENTS */
#define MME_AWCH_C_VAWID_EWEMENTS_V_SHIFT                            0
#define MME_AWCH_C_VAWID_EWEMENTS_V_MASK                             0xFFFFFFFF

/* MME_AWCH_C_WOOP_STWIDE */
#define MME_AWCH_C_WOOP_STWIDE_V_SHIFT                               0
#define MME_AWCH_C_WOOP_STWIDE_V_MASK                                0xFFFFFFFF

/* MME_AWCH_C_WOI_SIZE */
#define MME_AWCH_C_WOI_SIZE_V_SHIFT                                  0
#define MME_AWCH_C_WOI_SIZE_V_MASK                                   0xFFFFFFFF

/* MME_AWCH_C_SPATIAW_STAWT_OFFSET */
#define MME_AWCH_C_SPATIAW_STAWT_OFFSET_V_SHIFT                      0
#define MME_AWCH_C_SPATIAW_STAWT_OFFSET_V_MASK                       0xFFFFFFFF

/* MME_AWCH_C_SPATIAW_STWIDE */
#define MME_AWCH_C_SPATIAW_STWIDE_V_SHIFT                            0
#define MME_AWCH_C_SPATIAW_STWIDE_V_MASK                             0xFFFFFFFF

/* MME_AWCH_C_SPATIAW_SIZE_MINUS_1 */
#define MME_AWCH_C_SPATIAW_SIZE_MINUS_1_V_SHIFT                      0
#define MME_AWCH_C_SPATIAW_SIZE_MINUS_1_V_MASK                       0xFFFFFFFF

/* MME_AWCH_SYNC_OBJECT_MESSAGE */
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_SHIFT            0
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_MASK             0xFFFF
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_SHIFT         16
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_MASK          0x7FFF0000
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_OPEWATION_SHIFT              31
#define MME_AWCH_SYNC_OBJECT_MESSAGE_SO_OPEWATION_MASK               0x80000000

/* MME_AWCH_E_PADDING_VAWUE_A */
#define MME_AWCH_E_PADDING_VAWUE_A_V_SHIFT                           0
#define MME_AWCH_E_PADDING_VAWUE_A_V_MASK                            0xFFFF

/* MME_AWCH_E_NUM_ITEWATION_MINUS_1 */
#define MME_AWCH_E_NUM_ITEWATION_MINUS_1_V_SHIFT                     0
#define MME_AWCH_E_NUM_ITEWATION_MINUS_1_V_MASK                      0xFFFFFFFF

/* MME_AWCH_E_BUBBWES_PEW_SPWIT */
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_A_SHIFT                         0
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_A_MASK                          0xFF
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_B_SHIFT                         8
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_B_MASK                          0xFF00
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_CIN_SHIFT                       16
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_CIN_MASK                        0xFF0000
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_ID_SHIFT                        24
#define MME_AWCH_E_BUBBWES_PEW_SPWIT_ID_MASK                         0xFF000000

/* MME_CMD */
#define MME_CMD_EXECUTE_SHIFT                                        0
#define MME_CMD_EXECUTE_MASK                                         0x1

/* MME_DUMMY */
#define MME_DUMMY_V_SHIFT                                            0
#define MME_DUMMY_V_MASK                                             0xFFFFFFFF

/* MME_WESET */
#define MME_WESET_V_SHIFT                                            0
#define MME_WESET_V_MASK                                             0x1

/* MME_STAWW */
#define MME_STAWW_V_SHIFT                                            0
#define MME_STAWW_V_MASK                                             0xFFFFFFFF

/* MME_SM_BASE_ADDWESS_WOW */
#define MME_SM_BASE_ADDWESS_WOW_V_SHIFT                              0
#define MME_SM_BASE_ADDWESS_WOW_V_MASK                               0xFFFFFFFF

/* MME_SM_BASE_ADDWESS_HIGH */
#define MME_SM_BASE_ADDWESS_HIGH_V_SHIFT                             0
#define MME_SM_BASE_ADDWESS_HIGH_V_MASK                              0xFFFFFFFF

/* MME_DBGMEM_ADD */
#define MME_DBGMEM_ADD_V_SHIFT                                       0
#define MME_DBGMEM_ADD_V_MASK                                        0xFFFFFFFF

/* MME_DBGMEM_DATA_WW */
#define MME_DBGMEM_DATA_WW_V_SHIFT                                   0
#define MME_DBGMEM_DATA_WW_V_MASK                                    0xFFFFFFFF

/* MME_DBGMEM_DATA_WD */
#define MME_DBGMEM_DATA_WD_V_SHIFT                                   0
#define MME_DBGMEM_DATA_WD_V_MASK                                    0xFFFFFFFF

/* MME_DBGMEM_CTWW */
#define MME_DBGMEM_CTWW_WW_NWD_SHIFT                                 0
#define MME_DBGMEM_CTWW_WW_NWD_MASK                                  0x1

/* MME_DBGMEM_WC */
#define MME_DBGMEM_WC_VAWID_SHIFT                                    0
#define MME_DBGMEM_WC_VAWID_MASK                                     0x1
#define MME_DBGMEM_WC_FUWW_SHIFT                                     1
#define MME_DBGMEM_WC_FUWW_MASK                                      0x2

/* MME_WOG_SHADOW */
#define MME_WOG_SHADOW_MASK_0_SHIFT                                  0
#define MME_WOG_SHADOW_MASK_0_MASK                                   0x7F
#define MME_WOG_SHADOW_MASK_1_SHIFT                                  8
#define MME_WOG_SHADOW_MASK_1_MASK                                   0x7F00
#define MME_WOG_SHADOW_MASK_2_SHIFT                                  16
#define MME_WOG_SHADOW_MASK_2_MASK                                   0x7F0000
#define MME_WOG_SHADOW_MASK_3_SHIFT                                  24
#define MME_WOG_SHADOW_MASK_3_MASK                                   0x7F000000

/* MME_STOWE_MAX_CWEDIT */
#define MME_STOWE_MAX_CWEDIT_V_SHIFT                                 0
#define MME_STOWE_MAX_CWEDIT_V_MASK                                  0x3F

/* MME_AGU */
#define MME_AGU_SBA_MAX_CWEDIT_SHIFT                                 0
#define MME_AGU_SBA_MAX_CWEDIT_MASK                                  0x1F
#define MME_AGU_SBB_MAX_CWEDIT_SHIFT                                 8
#define MME_AGU_SBB_MAX_CWEDIT_MASK                                  0x1F00
#define MME_AGU_SBC_MAX_CWEDIT_SHIFT                                 16
#define MME_AGU_SBC_MAX_CWEDIT_MASK                                  0x1F0000
#define MME_AGU_WBC_MAX_CWEDIT_SHIFT                                 24
#define MME_AGU_WBC_MAX_CWEDIT_MASK                                  0x3F000000

/* MME_SBA */
#define MME_SBA_MAX_SIZE_SHIFT                                       0
#define MME_SBA_MAX_SIZE_MASK                                        0x3FF
#define MME_SBA_EU_MAX_CWEDIT_SHIFT                                  16
#define MME_SBA_EU_MAX_CWEDIT_MASK                                   0x1F0000

/* MME_SBB */
#define MME_SBB_MAX_SIZE_SHIFT                                       0
#define MME_SBB_MAX_SIZE_MASK                                        0x3FF
#define MME_SBB_EU_MAX_CWEDIT_SHIFT                                  16
#define MME_SBB_EU_MAX_CWEDIT_MASK                                   0x1F0000

/* MME_SBC */
#define MME_SBC_MAX_SIZE_SHIFT                                       0
#define MME_SBC_MAX_SIZE_MASK                                        0x3FF
#define MME_SBC_EU_MAX_CWEDIT_SHIFT                                  16
#define MME_SBC_EU_MAX_CWEDIT_MASK                                   0x1F0000

/* MME_WBC */
#define MME_WBC_MAX_OUTSTANDING_SHIFT                                0
#define MME_WBC_MAX_OUTSTANDING_MASK                                 0xFFF
#define MME_WBC_DISABWE_FAST_END_PE_SHIFT                            12
#define MME_WBC_DISABWE_FAST_END_PE_MASK                             0x1000
#define MME_WBC_WD_INSEWT_BUBBWE_DIS_SHIFT                           13
#define MME_WBC_WD_INSEWT_BUBBWE_DIS_MASK                            0x2000

/* MME_SBA_CONTWOW_DATA */
#define MME_SBA_CONTWOW_DATA_ASID_SHIFT                              0
#define MME_SBA_CONTWOW_DATA_ASID_MASK                               0x3FF
#define MME_SBA_CONTWOW_DATA_MMBP_SHIFT                              10
#define MME_SBA_CONTWOW_DATA_MMBP_MASK                               0x400

/* MME_SBB_CONTWOW_DATA */
#define MME_SBB_CONTWOW_DATA_ASID_SHIFT                              0
#define MME_SBB_CONTWOW_DATA_ASID_MASK                               0x3FF
#define MME_SBB_CONTWOW_DATA_MMBP_SHIFT                              10
#define MME_SBB_CONTWOW_DATA_MMBP_MASK                               0x400

/* MME_SBC_CONTWOW_DATA */
#define MME_SBC_CONTWOW_DATA_ASID_SHIFT                              0
#define MME_SBC_CONTWOW_DATA_ASID_MASK                               0x3FF
#define MME_SBC_CONTWOW_DATA_MMBP_SHIFT                              10
#define MME_SBC_CONTWOW_DATA_MMBP_MASK                               0x400

/* MME_WBC_CONTWOW_DATA */
#define MME_WBC_CONTWOW_DATA_ASID_SHIFT                              0
#define MME_WBC_CONTWOW_DATA_ASID_MASK                               0x3FF
#define MME_WBC_CONTWOW_DATA_MMBP_SHIFT                              10
#define MME_WBC_CONTWOW_DATA_MMBP_MASK                               0x400

/* MME_TE */
#define MME_TE_MAX_CWEDIT_SHIFT                                      0
#define MME_TE_MAX_CWEDIT_MASK                                       0x1F
#define MME_TE_DESC_MAX_CWEDIT_SHIFT                                 8
#define MME_TE_DESC_MAX_CWEDIT_MASK                                  0x1F00

/* MME_TE2DEC */
#define MME_TE2DEC_MAX_CWEDIT_SHIFT                                  0
#define MME_TE2DEC_MAX_CWEDIT_MASK                                   0x1F

/* MME_WEI_STATUS */
#define MME_WEI_STATUS_V_SHIFT                                       0
#define MME_WEI_STATUS_V_MASK                                        0xFFFFFFFF

/* MME_WEI_MASK */
#define MME_WEI_MASK_V_SHIFT                                         0
#define MME_WEI_MASK_V_MASK                                          0xFFFFFFFF

/* MME_SEI_STATUS */
#define MME_SEI_STATUS_V_SHIFT                                       0
#define MME_SEI_STATUS_V_MASK                                        0xFFFFFFFF

/* MME_SEI_MASK */
#define MME_SEI_MASK_V_SHIFT                                         0
#define MME_SEI_MASK_V_MASK                                          0xFFFFFFFF

/* MME_SPI_STATUS */
#define MME_SPI_STATUS_V_SHIFT                                       0
#define MME_SPI_STATUS_V_MASK                                        0xFFFFFFFF

/* MME_SPI_MASK */
#define MME_SPI_MASK_V_SHIFT                                         0
#define MME_SPI_MASK_V_MASK                                          0xFFFFFFFF

/* MME_SHADOW_0_STATUS */
#define MME_SHADOW_0_STATUS_A_SHIFT                                  0
#define MME_SHADOW_0_STATUS_A_MASK                                   0x1
#define MME_SHADOW_0_STATUS_B_SHIFT                                  1
#define MME_SHADOW_0_STATUS_B_MASK                                   0x2
#define MME_SHADOW_0_STATUS_CIN_SHIFT                                2
#define MME_SHADOW_0_STATUS_CIN_MASK                                 0x4
#define MME_SHADOW_0_STATUS_COUT_SHIFT                               3
#define MME_SHADOW_0_STATUS_COUT_MASK                                0x8
#define MME_SHADOW_0_STATUS_TE_SHIFT                                 4
#define MME_SHADOW_0_STATUS_TE_MASK                                  0x10
#define MME_SHADOW_0_STATUS_WD_SHIFT                                 5
#define MME_SHADOW_0_STATUS_WD_MASK                                  0x20
#define MME_SHADOW_0_STATUS_ST_SHIFT                                 6
#define MME_SHADOW_0_STATUS_ST_MASK                                  0x40

/* MME_SHADOW_0_A_BASE_ADDW_HIGH */
#define MME_SHADOW_0_A_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_0_A_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_B_BASE_ADDW_HIGH */
#define MME_SHADOW_0_B_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_0_B_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_CIN_BASE_ADDW_HIGH */
#define MME_SHADOW_0_CIN_BASE_ADDW_HIGH_V_SHIFT                      0
#define MME_SHADOW_0_CIN_BASE_ADDW_HIGH_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_0_COUT_BASE_ADDW_HIGH */
#define MME_SHADOW_0_COUT_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_0_COUT_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_0_BIAS_BASE_ADDW_HIGH */
#define MME_SHADOW_0_BIAS_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_0_BIAS_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_0_A_BASE_ADDW_WOW */
#define MME_SHADOW_0_A_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_0_A_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_0_B_BASE_ADDW_WOW */
#define MME_SHADOW_0_B_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_0_B_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_0_CIN_BASE_ADDW_WOW */
#define MME_SHADOW_0_CIN_BASE_ADDW_WOW_V_SHIFT                       0
#define MME_SHADOW_0_CIN_BASE_ADDW_WOW_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_0_COUT_BASE_ADDW_WOW */
#define MME_SHADOW_0_COUT_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_0_COUT_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_0_BIAS_BASE_ADDW_WOW */
#define MME_SHADOW_0_BIAS_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_0_BIAS_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_0_HEADEW */
#define MME_SHADOW_0_HEADEW_SIGNAW_MASK_SHIFT                        0
#define MME_SHADOW_0_HEADEW_SIGNAW_MASK_MASK                         0x1F
#define MME_SHADOW_0_HEADEW_SIGNAW_EN_SHIFT                          5
#define MME_SHADOW_0_HEADEW_SIGNAW_EN_MASK                           0x20
#define MME_SHADOW_0_HEADEW_TWANS_A_SHIFT                            6
#define MME_SHADOW_0_HEADEW_TWANS_A_MASK                             0x40
#define MME_SHADOW_0_HEADEW_WOWEW_A_SHIFT                            7
#define MME_SHADOW_0_HEADEW_WOWEW_A_MASK                             0x80
#define MME_SHADOW_0_HEADEW_ACCUM_MASK_SHIFT                         8
#define MME_SHADOW_0_HEADEW_ACCUM_MASK_MASK                          0xF00
#define MME_SHADOW_0_HEADEW_WOAD_BIAS_SHIFT                          12
#define MME_SHADOW_0_HEADEW_WOAD_BIAS_MASK                           0x1000
#define MME_SHADOW_0_HEADEW_WOAD_CIN_SHIFT                           13
#define MME_SHADOW_0_HEADEW_WOAD_CIN_MASK                            0x2000
#define MME_SHADOW_0_HEADEW_STOWE_OUT_SHIFT                          15
#define MME_SHADOW_0_HEADEW_STOWE_OUT_MASK                           0x8000
#define MME_SHADOW_0_HEADEW_ACC_WD_INC_DISABWE_SHIFT                 16
#define MME_SHADOW_0_HEADEW_ACC_WD_INC_DISABWE_MASK                  0x10000
#define MME_SHADOW_0_HEADEW_ADVANCE_A_SHIFT                          17
#define MME_SHADOW_0_HEADEW_ADVANCE_A_MASK                           0x20000
#define MME_SHADOW_0_HEADEW_ADVANCE_B_SHIFT                          18
#define MME_SHADOW_0_HEADEW_ADVANCE_B_MASK                           0x40000
#define MME_SHADOW_0_HEADEW_ADVANCE_CIN_SHIFT                        19
#define MME_SHADOW_0_HEADEW_ADVANCE_CIN_MASK                         0x80000
#define MME_SHADOW_0_HEADEW_ADVANCE_COUT_SHIFT                       20
#define MME_SHADOW_0_HEADEW_ADVANCE_COUT_MASK                        0x100000
#define MME_SHADOW_0_HEADEW_COMPWESSED_B_SHIFT                       21
#define MME_SHADOW_0_HEADEW_COMPWESSED_B_MASK                        0x200000
#define MME_SHADOW_0_HEADEW_MASK_CONV_END_SHIFT                      22
#define MME_SHADOW_0_HEADEW_MASK_CONV_END_MASK                       0x400000
#define MME_SHADOW_0_HEADEW_ACC_ST_INC_DISABWE_SHIFT                 23
#define MME_SHADOW_0_HEADEW_ACC_ST_INC_DISABWE_MASK                  0x800000
#define MME_SHADOW_0_HEADEW_AB_DATA_TYPE_SHIFT                       24
#define MME_SHADOW_0_HEADEW_AB_DATA_TYPE_MASK                        0x3000000
#define MME_SHADOW_0_HEADEW_CIN_DATA_TYPE_SHIFT                      26
#define MME_SHADOW_0_HEADEW_CIN_DATA_TYPE_MASK                       0x1C000000
#define MME_SHADOW_0_HEADEW_COUT_DATA_TYPE_SHIFT                     29
#define MME_SHADOW_0_HEADEW_COUT_DATA_TYPE_MASK                      0xE0000000

/* MME_SHADOW_0_KEWNEW_SIZE_MINUS_1 */
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_0_SHIFT                 0
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_0_MASK                  0xFF
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_1_SHIFT                 8
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_1_MASK                  0xFF00
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_2_SHIFT                 16
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_2_MASK                  0xFF0000
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_3_SHIFT                 24
#define MME_SHADOW_0_KEWNEW_SIZE_MINUS_1_DIM_3_MASK                  0xFF000000

/* MME_SHADOW_0_ASSOCIATED_DIMS */
#define MME_SHADOW_0_ASSOCIATED_DIMS_A_0_SHIFT                       0
#define MME_SHADOW_0_ASSOCIATED_DIMS_A_0_MASK                        0x7
#define MME_SHADOW_0_ASSOCIATED_DIMS_B_0_SHIFT                       3
#define MME_SHADOW_0_ASSOCIATED_DIMS_B_0_MASK                        0x38
#define MME_SHADOW_0_ASSOCIATED_DIMS_CIN_0_SHIFT                     6
#define MME_SHADOW_0_ASSOCIATED_DIMS_CIN_0_MASK                      0x1C0
#define MME_SHADOW_0_ASSOCIATED_DIMS_COUT_0_SHIFT                    9
#define MME_SHADOW_0_ASSOCIATED_DIMS_COUT_0_MASK                     0xE00
#define MME_SHADOW_0_ASSOCIATED_DIMS_A_1_SHIFT                       16
#define MME_SHADOW_0_ASSOCIATED_DIMS_A_1_MASK                        0x70000
#define MME_SHADOW_0_ASSOCIATED_DIMS_B_1_SHIFT                       19
#define MME_SHADOW_0_ASSOCIATED_DIMS_B_1_MASK                        0x380000
#define MME_SHADOW_0_ASSOCIATED_DIMS_CIN_1_SHIFT                     22
#define MME_SHADOW_0_ASSOCIATED_DIMS_CIN_1_MASK                      0x1C00000
#define MME_SHADOW_0_ASSOCIATED_DIMS_COUT_1_SHIFT                    25
#define MME_SHADOW_0_ASSOCIATED_DIMS_COUT_1_MASK                     0xE000000

/* MME_SHADOW_0_COUT_SCAWE */
#define MME_SHADOW_0_COUT_SCAWE_V_SHIFT                              0
#define MME_SHADOW_0_COUT_SCAWE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_0_CIN_SCAWE */
#define MME_SHADOW_0_CIN_SCAWE_V_SHIFT                               0
#define MME_SHADOW_0_CIN_SCAWE_V_MASK                                0xFFFFFFFF

/* MME_SHADOW_0_GEMMWOWP_ZP */
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_CIN_SHIFT                        0
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_CIN_MASK                         0x1FF
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_COUT_SHIFT                       9
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_COUT_MASK                        0x3FE00
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_B_SHIFT                          18
#define MME_SHADOW_0_GEMMWOWP_ZP_ZP_B_MASK                           0x7FC0000
#define MME_SHADOW_0_GEMMWOWP_ZP_GEMMWOWP_EU_EN_SHIFT                27
#define MME_SHADOW_0_GEMMWOWP_ZP_GEMMWOWP_EU_EN_MASK                 0x8000000
#define MME_SHADOW_0_GEMMWOWP_ZP_ACCUM_SHIFT                         28
#define MME_SHADOW_0_GEMMWOWP_ZP_ACCUM_MASK                          0x10000000
#define MME_SHADOW_0_GEMMWOWP_ZP_ACCUM_BIAS_SHIFT                    29
#define MME_SHADOW_0_GEMMWOWP_ZP_ACCUM_BIAS_MASK                     0x20000000
#define MME_SHADOW_0_GEMMWOWP_ZP_WEWU_EN_SHIFT                       30
#define MME_SHADOW_0_GEMMWOWP_ZP_WEWU_EN_MASK                        0x40000000

/* MME_SHADOW_0_GEMMWOWP_EXPONENT */
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_EXPONENT_CIN_SHIFT            0
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_EXPONENT_CIN_MASK             0x3F
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_EXPONENT_COUT_SHIFT           8
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_EXPONENT_COUT_MASK            0x3F00
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_MUW_CIN_EN_SHIFT              16
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_MUW_CIN_EN_MASK               0x10000
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_MUW_COUT_EN_SHIFT             17
#define MME_SHADOW_0_GEMMWOWP_EXPONENT_MUW_COUT_EN_MASK              0x20000

/* MME_SHADOW_0_A_WOI_BASE_OFFSET */
#define MME_SHADOW_0_A_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_0_A_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_0_A_VAWID_EWEMENTS */
#define MME_SHADOW_0_A_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_0_A_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_A_WOOP_STWIDE */
#define MME_SHADOW_0_A_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_0_A_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_0_A_WOI_SIZE */
#define MME_SHADOW_0_A_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_0_A_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_0_A_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_0_A_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_0_A_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_A_SPATIAW_STWIDE */
#define MME_SHADOW_0_A_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_0_A_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_A_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_0_A_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_0_A_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_B_WOI_BASE_OFFSET */
#define MME_SHADOW_0_B_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_0_B_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_0_B_VAWID_EWEMENTS */
#define MME_SHADOW_0_B_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_0_B_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_B_WOOP_STWIDE */
#define MME_SHADOW_0_B_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_0_B_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_0_B_WOI_SIZE */
#define MME_SHADOW_0_B_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_0_B_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_0_B_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_0_B_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_0_B_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_B_SPATIAW_STWIDE */
#define MME_SHADOW_0_B_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_0_B_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_B_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_0_B_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_0_B_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_C_WOI_BASE_OFFSET */
#define MME_SHADOW_0_C_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_0_C_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_0_C_VAWID_EWEMENTS */
#define MME_SHADOW_0_C_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_0_C_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_C_WOOP_STWIDE */
#define MME_SHADOW_0_C_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_0_C_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_0_C_WOI_SIZE */
#define MME_SHADOW_0_C_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_0_C_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_0_C_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_0_C_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_0_C_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_C_SPATIAW_STWIDE */
#define MME_SHADOW_0_C_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_0_C_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_0_C_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_0_C_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_0_C_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_0_SYNC_OBJECT_MESSAGE */
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_SHIFT        0
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_MASK         0xFFFF
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_SHIFT     16
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_MASK      0x7FFF0000
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_OPEWATION_SHIFT          31
#define MME_SHADOW_0_SYNC_OBJECT_MESSAGE_SO_OPEWATION_MASK           0x80000000

/* MME_SHADOW_0_E_PADDING_VAWUE_A */
#define MME_SHADOW_0_E_PADDING_VAWUE_A_V_SHIFT                       0
#define MME_SHADOW_0_E_PADDING_VAWUE_A_V_MASK                        0xFFFF

/* MME_SHADOW_0_E_NUM_ITEWATION_MINUS_1 */
#define MME_SHADOW_0_E_NUM_ITEWATION_MINUS_1_V_SHIFT                 0
#define MME_SHADOW_0_E_NUM_ITEWATION_MINUS_1_V_MASK                  0xFFFFFFFF

/* MME_SHADOW_0_E_BUBBWES_PEW_SPWIT */
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_A_SHIFT                     0
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_A_MASK                      0xFF
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_B_SHIFT                     8
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_B_MASK                      0xFF00
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_CIN_SHIFT                   16
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_CIN_MASK                    0xFF0000
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_ID_SHIFT                    24
#define MME_SHADOW_0_E_BUBBWES_PEW_SPWIT_ID_MASK                     0xFF000000

/* MME_SHADOW_1_STATUS */
#define MME_SHADOW_1_STATUS_A_SHIFT                                  0
#define MME_SHADOW_1_STATUS_A_MASK                                   0x1
#define MME_SHADOW_1_STATUS_B_SHIFT                                  1
#define MME_SHADOW_1_STATUS_B_MASK                                   0x2
#define MME_SHADOW_1_STATUS_CIN_SHIFT                                2
#define MME_SHADOW_1_STATUS_CIN_MASK                                 0x4
#define MME_SHADOW_1_STATUS_COUT_SHIFT                               3
#define MME_SHADOW_1_STATUS_COUT_MASK                                0x8
#define MME_SHADOW_1_STATUS_TE_SHIFT                                 4
#define MME_SHADOW_1_STATUS_TE_MASK                                  0x10
#define MME_SHADOW_1_STATUS_WD_SHIFT                                 5
#define MME_SHADOW_1_STATUS_WD_MASK                                  0x20
#define MME_SHADOW_1_STATUS_ST_SHIFT                                 6
#define MME_SHADOW_1_STATUS_ST_MASK                                  0x40

/* MME_SHADOW_1_A_BASE_ADDW_HIGH */
#define MME_SHADOW_1_A_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_1_A_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_B_BASE_ADDW_HIGH */
#define MME_SHADOW_1_B_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_1_B_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_CIN_BASE_ADDW_HIGH */
#define MME_SHADOW_1_CIN_BASE_ADDW_HIGH_V_SHIFT                      0
#define MME_SHADOW_1_CIN_BASE_ADDW_HIGH_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_1_COUT_BASE_ADDW_HIGH */
#define MME_SHADOW_1_COUT_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_1_COUT_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_1_BIAS_BASE_ADDW_HIGH */
#define MME_SHADOW_1_BIAS_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_1_BIAS_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_1_A_BASE_ADDW_WOW */
#define MME_SHADOW_1_A_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_1_A_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_1_B_BASE_ADDW_WOW */
#define MME_SHADOW_1_B_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_1_B_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_1_CIN_BASE_ADDW_WOW */
#define MME_SHADOW_1_CIN_BASE_ADDW_WOW_V_SHIFT                       0
#define MME_SHADOW_1_CIN_BASE_ADDW_WOW_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_1_COUT_BASE_ADDW_WOW */
#define MME_SHADOW_1_COUT_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_1_COUT_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_1_BIAS_BASE_ADDW_WOW */
#define MME_SHADOW_1_BIAS_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_1_BIAS_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_1_HEADEW */
#define MME_SHADOW_1_HEADEW_SIGNAW_MASK_SHIFT                        0
#define MME_SHADOW_1_HEADEW_SIGNAW_MASK_MASK                         0x1F
#define MME_SHADOW_1_HEADEW_SIGNAW_EN_SHIFT                          5
#define MME_SHADOW_1_HEADEW_SIGNAW_EN_MASK                           0x20
#define MME_SHADOW_1_HEADEW_TWANS_A_SHIFT                            6
#define MME_SHADOW_1_HEADEW_TWANS_A_MASK                             0x40
#define MME_SHADOW_1_HEADEW_WOWEW_A_SHIFT                            7
#define MME_SHADOW_1_HEADEW_WOWEW_A_MASK                             0x80
#define MME_SHADOW_1_HEADEW_ACCUM_MASK_SHIFT                         8
#define MME_SHADOW_1_HEADEW_ACCUM_MASK_MASK                          0xF00
#define MME_SHADOW_1_HEADEW_WOAD_BIAS_SHIFT                          12
#define MME_SHADOW_1_HEADEW_WOAD_BIAS_MASK                           0x1000
#define MME_SHADOW_1_HEADEW_WOAD_CIN_SHIFT                           13
#define MME_SHADOW_1_HEADEW_WOAD_CIN_MASK                            0x2000
#define MME_SHADOW_1_HEADEW_STOWE_OUT_SHIFT                          15
#define MME_SHADOW_1_HEADEW_STOWE_OUT_MASK                           0x8000
#define MME_SHADOW_1_HEADEW_ACC_WD_INC_DISABWE_SHIFT                 16
#define MME_SHADOW_1_HEADEW_ACC_WD_INC_DISABWE_MASK                  0x10000
#define MME_SHADOW_1_HEADEW_ADVANCE_A_SHIFT                          17
#define MME_SHADOW_1_HEADEW_ADVANCE_A_MASK                           0x20000
#define MME_SHADOW_1_HEADEW_ADVANCE_B_SHIFT                          18
#define MME_SHADOW_1_HEADEW_ADVANCE_B_MASK                           0x40000
#define MME_SHADOW_1_HEADEW_ADVANCE_CIN_SHIFT                        19
#define MME_SHADOW_1_HEADEW_ADVANCE_CIN_MASK                         0x80000
#define MME_SHADOW_1_HEADEW_ADVANCE_COUT_SHIFT                       20
#define MME_SHADOW_1_HEADEW_ADVANCE_COUT_MASK                        0x100000
#define MME_SHADOW_1_HEADEW_COMPWESSED_B_SHIFT                       21
#define MME_SHADOW_1_HEADEW_COMPWESSED_B_MASK                        0x200000
#define MME_SHADOW_1_HEADEW_MASK_CONV_END_SHIFT                      22
#define MME_SHADOW_1_HEADEW_MASK_CONV_END_MASK                       0x400000
#define MME_SHADOW_1_HEADEW_ACC_ST_INC_DISABWE_SHIFT                 23
#define MME_SHADOW_1_HEADEW_ACC_ST_INC_DISABWE_MASK                  0x800000
#define MME_SHADOW_1_HEADEW_AB_DATA_TYPE_SHIFT                       24
#define MME_SHADOW_1_HEADEW_AB_DATA_TYPE_MASK                        0x3000000
#define MME_SHADOW_1_HEADEW_CIN_DATA_TYPE_SHIFT                      26
#define MME_SHADOW_1_HEADEW_CIN_DATA_TYPE_MASK                       0x1C000000
#define MME_SHADOW_1_HEADEW_COUT_DATA_TYPE_SHIFT                     29
#define MME_SHADOW_1_HEADEW_COUT_DATA_TYPE_MASK                      0xE0000000

/* MME_SHADOW_1_KEWNEW_SIZE_MINUS_1 */
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_0_SHIFT                 0
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_0_MASK                  0xFF
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_1_SHIFT                 8
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_1_MASK                  0xFF00
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_2_SHIFT                 16
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_2_MASK                  0xFF0000
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_3_SHIFT                 24
#define MME_SHADOW_1_KEWNEW_SIZE_MINUS_1_DIM_3_MASK                  0xFF000000

/* MME_SHADOW_1_ASSOCIATED_DIMS */
#define MME_SHADOW_1_ASSOCIATED_DIMS_A_0_SHIFT                       0
#define MME_SHADOW_1_ASSOCIATED_DIMS_A_0_MASK                        0x7
#define MME_SHADOW_1_ASSOCIATED_DIMS_B_0_SHIFT                       3
#define MME_SHADOW_1_ASSOCIATED_DIMS_B_0_MASK                        0x38
#define MME_SHADOW_1_ASSOCIATED_DIMS_CIN_0_SHIFT                     6
#define MME_SHADOW_1_ASSOCIATED_DIMS_CIN_0_MASK                      0x1C0
#define MME_SHADOW_1_ASSOCIATED_DIMS_COUT_0_SHIFT                    9
#define MME_SHADOW_1_ASSOCIATED_DIMS_COUT_0_MASK                     0xE00
#define MME_SHADOW_1_ASSOCIATED_DIMS_A_1_SHIFT                       16
#define MME_SHADOW_1_ASSOCIATED_DIMS_A_1_MASK                        0x70000
#define MME_SHADOW_1_ASSOCIATED_DIMS_B_1_SHIFT                       19
#define MME_SHADOW_1_ASSOCIATED_DIMS_B_1_MASK                        0x380000
#define MME_SHADOW_1_ASSOCIATED_DIMS_CIN_1_SHIFT                     22
#define MME_SHADOW_1_ASSOCIATED_DIMS_CIN_1_MASK                      0x1C00000
#define MME_SHADOW_1_ASSOCIATED_DIMS_COUT_1_SHIFT                    25
#define MME_SHADOW_1_ASSOCIATED_DIMS_COUT_1_MASK                     0xE000000

/* MME_SHADOW_1_COUT_SCAWE */
#define MME_SHADOW_1_COUT_SCAWE_V_SHIFT                              0
#define MME_SHADOW_1_COUT_SCAWE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_1_CIN_SCAWE */
#define MME_SHADOW_1_CIN_SCAWE_V_SHIFT                               0
#define MME_SHADOW_1_CIN_SCAWE_V_MASK                                0xFFFFFFFF

/* MME_SHADOW_1_GEMMWOWP_ZP */
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_CIN_SHIFT                        0
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_CIN_MASK                         0x1FF
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_COUT_SHIFT                       9
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_COUT_MASK                        0x3FE00
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_B_SHIFT                          18
#define MME_SHADOW_1_GEMMWOWP_ZP_ZP_B_MASK                           0x7FC0000
#define MME_SHADOW_1_GEMMWOWP_ZP_GEMMWOWP_EU_EN_SHIFT                27
#define MME_SHADOW_1_GEMMWOWP_ZP_GEMMWOWP_EU_EN_MASK                 0x8000000
#define MME_SHADOW_1_GEMMWOWP_ZP_ACCUM_SHIFT                         28
#define MME_SHADOW_1_GEMMWOWP_ZP_ACCUM_MASK                          0x10000000
#define MME_SHADOW_1_GEMMWOWP_ZP_ACCUM_BIAS_SHIFT                    29
#define MME_SHADOW_1_GEMMWOWP_ZP_ACCUM_BIAS_MASK                     0x20000000
#define MME_SHADOW_1_GEMMWOWP_ZP_WEWU_EN_SHIFT                       30
#define MME_SHADOW_1_GEMMWOWP_ZP_WEWU_EN_MASK                        0x40000000

/* MME_SHADOW_1_GEMMWOWP_EXPONENT */
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_EXPONENT_CIN_SHIFT            0
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_EXPONENT_CIN_MASK             0x3F
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_EXPONENT_COUT_SHIFT           8
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_EXPONENT_COUT_MASK            0x3F00
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_MUW_CIN_EN_SHIFT              16
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_MUW_CIN_EN_MASK               0x10000
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_MUW_COUT_EN_SHIFT             17
#define MME_SHADOW_1_GEMMWOWP_EXPONENT_MUW_COUT_EN_MASK              0x20000

/* MME_SHADOW_1_A_WOI_BASE_OFFSET */
#define MME_SHADOW_1_A_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_1_A_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_1_A_VAWID_EWEMENTS */
#define MME_SHADOW_1_A_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_1_A_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_A_WOOP_STWIDE */
#define MME_SHADOW_1_A_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_1_A_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_1_A_WOI_SIZE */
#define MME_SHADOW_1_A_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_1_A_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_1_A_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_1_A_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_1_A_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_A_SPATIAW_STWIDE */
#define MME_SHADOW_1_A_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_1_A_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_A_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_1_A_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_1_A_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_B_WOI_BASE_OFFSET */
#define MME_SHADOW_1_B_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_1_B_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_1_B_VAWID_EWEMENTS */
#define MME_SHADOW_1_B_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_1_B_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_B_WOOP_STWIDE */
#define MME_SHADOW_1_B_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_1_B_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_1_B_WOI_SIZE */
#define MME_SHADOW_1_B_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_1_B_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_1_B_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_1_B_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_1_B_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_B_SPATIAW_STWIDE */
#define MME_SHADOW_1_B_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_1_B_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_B_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_1_B_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_1_B_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_C_WOI_BASE_OFFSET */
#define MME_SHADOW_1_C_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_1_C_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_1_C_VAWID_EWEMENTS */
#define MME_SHADOW_1_C_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_1_C_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_C_WOOP_STWIDE */
#define MME_SHADOW_1_C_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_1_C_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_1_C_WOI_SIZE */
#define MME_SHADOW_1_C_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_1_C_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_1_C_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_1_C_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_1_C_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_C_SPATIAW_STWIDE */
#define MME_SHADOW_1_C_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_1_C_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_1_C_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_1_C_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_1_C_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_1_SYNC_OBJECT_MESSAGE */
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_SHIFT        0
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_MASK         0xFFFF
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_SHIFT     16
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_MASK      0x7FFF0000
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_OPEWATION_SHIFT          31
#define MME_SHADOW_1_SYNC_OBJECT_MESSAGE_SO_OPEWATION_MASK           0x80000000

/* MME_SHADOW_1_E_PADDING_VAWUE_A */
#define MME_SHADOW_1_E_PADDING_VAWUE_A_V_SHIFT                       0
#define MME_SHADOW_1_E_PADDING_VAWUE_A_V_MASK                        0xFFFF

/* MME_SHADOW_1_E_NUM_ITEWATION_MINUS_1 */
#define MME_SHADOW_1_E_NUM_ITEWATION_MINUS_1_V_SHIFT                 0
#define MME_SHADOW_1_E_NUM_ITEWATION_MINUS_1_V_MASK                  0xFFFFFFFF

/* MME_SHADOW_1_E_BUBBWES_PEW_SPWIT */
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_A_SHIFT                     0
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_A_MASK                      0xFF
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_B_SHIFT                     8
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_B_MASK                      0xFF00
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_CIN_SHIFT                   16
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_CIN_MASK                    0xFF0000
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_ID_SHIFT                    24
#define MME_SHADOW_1_E_BUBBWES_PEW_SPWIT_ID_MASK                     0xFF000000

/* MME_SHADOW_2_STATUS */
#define MME_SHADOW_2_STATUS_A_SHIFT                                  0
#define MME_SHADOW_2_STATUS_A_MASK                                   0x1
#define MME_SHADOW_2_STATUS_B_SHIFT                                  1
#define MME_SHADOW_2_STATUS_B_MASK                                   0x2
#define MME_SHADOW_2_STATUS_CIN_SHIFT                                2
#define MME_SHADOW_2_STATUS_CIN_MASK                                 0x4
#define MME_SHADOW_2_STATUS_COUT_SHIFT                               3
#define MME_SHADOW_2_STATUS_COUT_MASK                                0x8
#define MME_SHADOW_2_STATUS_TE_SHIFT                                 4
#define MME_SHADOW_2_STATUS_TE_MASK                                  0x10
#define MME_SHADOW_2_STATUS_WD_SHIFT                                 5
#define MME_SHADOW_2_STATUS_WD_MASK                                  0x20
#define MME_SHADOW_2_STATUS_ST_SHIFT                                 6
#define MME_SHADOW_2_STATUS_ST_MASK                                  0x40

/* MME_SHADOW_2_A_BASE_ADDW_HIGH */
#define MME_SHADOW_2_A_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_2_A_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_B_BASE_ADDW_HIGH */
#define MME_SHADOW_2_B_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_2_B_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_CIN_BASE_ADDW_HIGH */
#define MME_SHADOW_2_CIN_BASE_ADDW_HIGH_V_SHIFT                      0
#define MME_SHADOW_2_CIN_BASE_ADDW_HIGH_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_2_COUT_BASE_ADDW_HIGH */
#define MME_SHADOW_2_COUT_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_2_COUT_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_2_BIAS_BASE_ADDW_HIGH */
#define MME_SHADOW_2_BIAS_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_2_BIAS_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_2_A_BASE_ADDW_WOW */
#define MME_SHADOW_2_A_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_2_A_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_2_B_BASE_ADDW_WOW */
#define MME_SHADOW_2_B_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_2_B_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_2_CIN_BASE_ADDW_WOW */
#define MME_SHADOW_2_CIN_BASE_ADDW_WOW_V_SHIFT                       0
#define MME_SHADOW_2_CIN_BASE_ADDW_WOW_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_2_COUT_BASE_ADDW_WOW */
#define MME_SHADOW_2_COUT_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_2_COUT_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_2_BIAS_BASE_ADDW_WOW */
#define MME_SHADOW_2_BIAS_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_2_BIAS_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_2_HEADEW */
#define MME_SHADOW_2_HEADEW_SIGNAW_MASK_SHIFT                        0
#define MME_SHADOW_2_HEADEW_SIGNAW_MASK_MASK                         0x1F
#define MME_SHADOW_2_HEADEW_SIGNAW_EN_SHIFT                          5
#define MME_SHADOW_2_HEADEW_SIGNAW_EN_MASK                           0x20
#define MME_SHADOW_2_HEADEW_TWANS_A_SHIFT                            6
#define MME_SHADOW_2_HEADEW_TWANS_A_MASK                             0x40
#define MME_SHADOW_2_HEADEW_WOWEW_A_SHIFT                            7
#define MME_SHADOW_2_HEADEW_WOWEW_A_MASK                             0x80
#define MME_SHADOW_2_HEADEW_ACCUM_MASK_SHIFT                         8
#define MME_SHADOW_2_HEADEW_ACCUM_MASK_MASK                          0xF00
#define MME_SHADOW_2_HEADEW_WOAD_BIAS_SHIFT                          12
#define MME_SHADOW_2_HEADEW_WOAD_BIAS_MASK                           0x1000
#define MME_SHADOW_2_HEADEW_WOAD_CIN_SHIFT                           13
#define MME_SHADOW_2_HEADEW_WOAD_CIN_MASK                            0x2000
#define MME_SHADOW_2_HEADEW_STOWE_OUT_SHIFT                          15
#define MME_SHADOW_2_HEADEW_STOWE_OUT_MASK                           0x8000
#define MME_SHADOW_2_HEADEW_ACC_WD_INC_DISABWE_SHIFT                 16
#define MME_SHADOW_2_HEADEW_ACC_WD_INC_DISABWE_MASK                  0x10000
#define MME_SHADOW_2_HEADEW_ADVANCE_A_SHIFT                          17
#define MME_SHADOW_2_HEADEW_ADVANCE_A_MASK                           0x20000
#define MME_SHADOW_2_HEADEW_ADVANCE_B_SHIFT                          18
#define MME_SHADOW_2_HEADEW_ADVANCE_B_MASK                           0x40000
#define MME_SHADOW_2_HEADEW_ADVANCE_CIN_SHIFT                        19
#define MME_SHADOW_2_HEADEW_ADVANCE_CIN_MASK                         0x80000
#define MME_SHADOW_2_HEADEW_ADVANCE_COUT_SHIFT                       20
#define MME_SHADOW_2_HEADEW_ADVANCE_COUT_MASK                        0x100000
#define MME_SHADOW_2_HEADEW_COMPWESSED_B_SHIFT                       21
#define MME_SHADOW_2_HEADEW_COMPWESSED_B_MASK                        0x200000
#define MME_SHADOW_2_HEADEW_MASK_CONV_END_SHIFT                      22
#define MME_SHADOW_2_HEADEW_MASK_CONV_END_MASK                       0x400000
#define MME_SHADOW_2_HEADEW_ACC_ST_INC_DISABWE_SHIFT                 23
#define MME_SHADOW_2_HEADEW_ACC_ST_INC_DISABWE_MASK                  0x800000
#define MME_SHADOW_2_HEADEW_AB_DATA_TYPE_SHIFT                       24
#define MME_SHADOW_2_HEADEW_AB_DATA_TYPE_MASK                        0x3000000
#define MME_SHADOW_2_HEADEW_CIN_DATA_TYPE_SHIFT                      26
#define MME_SHADOW_2_HEADEW_CIN_DATA_TYPE_MASK                       0x1C000000
#define MME_SHADOW_2_HEADEW_COUT_DATA_TYPE_SHIFT                     29
#define MME_SHADOW_2_HEADEW_COUT_DATA_TYPE_MASK                      0xE0000000

/* MME_SHADOW_2_KEWNEW_SIZE_MINUS_1 */
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_0_SHIFT                 0
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_0_MASK                  0xFF
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_1_SHIFT                 8
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_1_MASK                  0xFF00
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_2_SHIFT                 16
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_2_MASK                  0xFF0000
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_3_SHIFT                 24
#define MME_SHADOW_2_KEWNEW_SIZE_MINUS_1_DIM_3_MASK                  0xFF000000

/* MME_SHADOW_2_ASSOCIATED_DIMS */
#define MME_SHADOW_2_ASSOCIATED_DIMS_A_0_SHIFT                       0
#define MME_SHADOW_2_ASSOCIATED_DIMS_A_0_MASK                        0x7
#define MME_SHADOW_2_ASSOCIATED_DIMS_B_0_SHIFT                       3
#define MME_SHADOW_2_ASSOCIATED_DIMS_B_0_MASK                        0x38
#define MME_SHADOW_2_ASSOCIATED_DIMS_CIN_0_SHIFT                     6
#define MME_SHADOW_2_ASSOCIATED_DIMS_CIN_0_MASK                      0x1C0
#define MME_SHADOW_2_ASSOCIATED_DIMS_COUT_0_SHIFT                    9
#define MME_SHADOW_2_ASSOCIATED_DIMS_COUT_0_MASK                     0xE00
#define MME_SHADOW_2_ASSOCIATED_DIMS_A_1_SHIFT                       16
#define MME_SHADOW_2_ASSOCIATED_DIMS_A_1_MASK                        0x70000
#define MME_SHADOW_2_ASSOCIATED_DIMS_B_1_SHIFT                       19
#define MME_SHADOW_2_ASSOCIATED_DIMS_B_1_MASK                        0x380000
#define MME_SHADOW_2_ASSOCIATED_DIMS_CIN_1_SHIFT                     22
#define MME_SHADOW_2_ASSOCIATED_DIMS_CIN_1_MASK                      0x1C00000
#define MME_SHADOW_2_ASSOCIATED_DIMS_COUT_1_SHIFT                    25
#define MME_SHADOW_2_ASSOCIATED_DIMS_COUT_1_MASK                     0xE000000

/* MME_SHADOW_2_COUT_SCAWE */
#define MME_SHADOW_2_COUT_SCAWE_V_SHIFT                              0
#define MME_SHADOW_2_COUT_SCAWE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_2_CIN_SCAWE */
#define MME_SHADOW_2_CIN_SCAWE_V_SHIFT                               0
#define MME_SHADOW_2_CIN_SCAWE_V_MASK                                0xFFFFFFFF

/* MME_SHADOW_2_GEMMWOWP_ZP */
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_CIN_SHIFT                        0
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_CIN_MASK                         0x1FF
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_COUT_SHIFT                       9
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_COUT_MASK                        0x3FE00
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_B_SHIFT                          18
#define MME_SHADOW_2_GEMMWOWP_ZP_ZP_B_MASK                           0x7FC0000
#define MME_SHADOW_2_GEMMWOWP_ZP_GEMMWOWP_EU_EN_SHIFT                27
#define MME_SHADOW_2_GEMMWOWP_ZP_GEMMWOWP_EU_EN_MASK                 0x8000000
#define MME_SHADOW_2_GEMMWOWP_ZP_ACCUM_SHIFT                         28
#define MME_SHADOW_2_GEMMWOWP_ZP_ACCUM_MASK                          0x10000000
#define MME_SHADOW_2_GEMMWOWP_ZP_ACCUM_BIAS_SHIFT                    29
#define MME_SHADOW_2_GEMMWOWP_ZP_ACCUM_BIAS_MASK                     0x20000000
#define MME_SHADOW_2_GEMMWOWP_ZP_WEWU_EN_SHIFT                       30
#define MME_SHADOW_2_GEMMWOWP_ZP_WEWU_EN_MASK                        0x40000000

/* MME_SHADOW_2_GEMMWOWP_EXPONENT */
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_EXPONENT_CIN_SHIFT            0
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_EXPONENT_CIN_MASK             0x3F
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_EXPONENT_COUT_SHIFT           8
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_EXPONENT_COUT_MASK            0x3F00
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_MUW_CIN_EN_SHIFT              16
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_MUW_CIN_EN_MASK               0x10000
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_MUW_COUT_EN_SHIFT             17
#define MME_SHADOW_2_GEMMWOWP_EXPONENT_MUW_COUT_EN_MASK              0x20000

/* MME_SHADOW_2_A_WOI_BASE_OFFSET */
#define MME_SHADOW_2_A_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_2_A_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_2_A_VAWID_EWEMENTS */
#define MME_SHADOW_2_A_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_2_A_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_A_WOOP_STWIDE */
#define MME_SHADOW_2_A_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_2_A_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_2_A_WOI_SIZE */
#define MME_SHADOW_2_A_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_2_A_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_2_A_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_2_A_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_2_A_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_A_SPATIAW_STWIDE */
#define MME_SHADOW_2_A_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_2_A_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_A_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_2_A_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_2_A_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_B_WOI_BASE_OFFSET */
#define MME_SHADOW_2_B_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_2_B_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_2_B_VAWID_EWEMENTS */
#define MME_SHADOW_2_B_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_2_B_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_B_WOOP_STWIDE */
#define MME_SHADOW_2_B_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_2_B_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_2_B_WOI_SIZE */
#define MME_SHADOW_2_B_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_2_B_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_2_B_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_2_B_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_2_B_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_B_SPATIAW_STWIDE */
#define MME_SHADOW_2_B_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_2_B_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_B_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_2_B_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_2_B_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_C_WOI_BASE_OFFSET */
#define MME_SHADOW_2_C_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_2_C_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_2_C_VAWID_EWEMENTS */
#define MME_SHADOW_2_C_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_2_C_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_C_WOOP_STWIDE */
#define MME_SHADOW_2_C_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_2_C_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_2_C_WOI_SIZE */
#define MME_SHADOW_2_C_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_2_C_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_2_C_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_2_C_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_2_C_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_C_SPATIAW_STWIDE */
#define MME_SHADOW_2_C_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_2_C_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_2_C_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_2_C_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_2_C_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_2_SYNC_OBJECT_MESSAGE */
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_SHIFT        0
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_MASK         0xFFFF
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_SHIFT     16
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_MASK      0x7FFF0000
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_OPEWATION_SHIFT          31
#define MME_SHADOW_2_SYNC_OBJECT_MESSAGE_SO_OPEWATION_MASK           0x80000000

/* MME_SHADOW_2_E_PADDING_VAWUE_A */
#define MME_SHADOW_2_E_PADDING_VAWUE_A_V_SHIFT                       0
#define MME_SHADOW_2_E_PADDING_VAWUE_A_V_MASK                        0xFFFF

/* MME_SHADOW_2_E_NUM_ITEWATION_MINUS_1 */
#define MME_SHADOW_2_E_NUM_ITEWATION_MINUS_1_V_SHIFT                 0
#define MME_SHADOW_2_E_NUM_ITEWATION_MINUS_1_V_MASK                  0xFFFFFFFF

/* MME_SHADOW_2_E_BUBBWES_PEW_SPWIT */
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_A_SHIFT                     0
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_A_MASK                      0xFF
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_B_SHIFT                     8
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_B_MASK                      0xFF00
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_CIN_SHIFT                   16
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_CIN_MASK                    0xFF0000
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_ID_SHIFT                    24
#define MME_SHADOW_2_E_BUBBWES_PEW_SPWIT_ID_MASK                     0xFF000000

/* MME_SHADOW_3_STATUS */
#define MME_SHADOW_3_STATUS_A_SHIFT                                  0
#define MME_SHADOW_3_STATUS_A_MASK                                   0x1
#define MME_SHADOW_3_STATUS_B_SHIFT                                  1
#define MME_SHADOW_3_STATUS_B_MASK                                   0x2
#define MME_SHADOW_3_STATUS_CIN_SHIFT                                2
#define MME_SHADOW_3_STATUS_CIN_MASK                                 0x4
#define MME_SHADOW_3_STATUS_COUT_SHIFT                               3
#define MME_SHADOW_3_STATUS_COUT_MASK                                0x8
#define MME_SHADOW_3_STATUS_TE_SHIFT                                 4
#define MME_SHADOW_3_STATUS_TE_MASK                                  0x10
#define MME_SHADOW_3_STATUS_WD_SHIFT                                 5
#define MME_SHADOW_3_STATUS_WD_MASK                                  0x20
#define MME_SHADOW_3_STATUS_ST_SHIFT                                 6
#define MME_SHADOW_3_STATUS_ST_MASK                                  0x40

/* MME_SHADOW_3_A_BASE_ADDW_HIGH */
#define MME_SHADOW_3_A_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_3_A_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_B_BASE_ADDW_HIGH */
#define MME_SHADOW_3_B_BASE_ADDW_HIGH_V_SHIFT                        0
#define MME_SHADOW_3_B_BASE_ADDW_HIGH_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_CIN_BASE_ADDW_HIGH */
#define MME_SHADOW_3_CIN_BASE_ADDW_HIGH_V_SHIFT                      0
#define MME_SHADOW_3_CIN_BASE_ADDW_HIGH_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_3_COUT_BASE_ADDW_HIGH */
#define MME_SHADOW_3_COUT_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_3_COUT_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_3_BIAS_BASE_ADDW_HIGH */
#define MME_SHADOW_3_BIAS_BASE_ADDW_HIGH_V_SHIFT                     0
#define MME_SHADOW_3_BIAS_BASE_ADDW_HIGH_V_MASK                      0xFFFFFFFF

/* MME_SHADOW_3_A_BASE_ADDW_WOW */
#define MME_SHADOW_3_A_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_3_A_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_3_B_BASE_ADDW_WOW */
#define MME_SHADOW_3_B_BASE_ADDW_WOW_V_SHIFT                         0
#define MME_SHADOW_3_B_BASE_ADDW_WOW_V_MASK                          0xFFFFFFFF

/* MME_SHADOW_3_CIN_BASE_ADDW_WOW */
#define MME_SHADOW_3_CIN_BASE_ADDW_WOW_V_SHIFT                       0
#define MME_SHADOW_3_CIN_BASE_ADDW_WOW_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_3_COUT_BASE_ADDW_WOW */
#define MME_SHADOW_3_COUT_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_3_COUT_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_3_BIAS_BASE_ADDW_WOW */
#define MME_SHADOW_3_BIAS_BASE_ADDW_WOW_V_SHIFT                      0
#define MME_SHADOW_3_BIAS_BASE_ADDW_WOW_V_MASK                       0xFFFFFFFF

/* MME_SHADOW_3_HEADEW */
#define MME_SHADOW_3_HEADEW_SIGNAW_MASK_SHIFT                        0
#define MME_SHADOW_3_HEADEW_SIGNAW_MASK_MASK                         0x1F
#define MME_SHADOW_3_HEADEW_SIGNAW_EN_SHIFT                          5
#define MME_SHADOW_3_HEADEW_SIGNAW_EN_MASK                           0x20
#define MME_SHADOW_3_HEADEW_TWANS_A_SHIFT                            6
#define MME_SHADOW_3_HEADEW_TWANS_A_MASK                             0x40
#define MME_SHADOW_3_HEADEW_WOWEW_A_SHIFT                            7
#define MME_SHADOW_3_HEADEW_WOWEW_A_MASK                             0x80
#define MME_SHADOW_3_HEADEW_ACCUM_MASK_SHIFT                         8
#define MME_SHADOW_3_HEADEW_ACCUM_MASK_MASK                          0xF00
#define MME_SHADOW_3_HEADEW_WOAD_BIAS_SHIFT                          12
#define MME_SHADOW_3_HEADEW_WOAD_BIAS_MASK                           0x1000
#define MME_SHADOW_3_HEADEW_WOAD_CIN_SHIFT                           13
#define MME_SHADOW_3_HEADEW_WOAD_CIN_MASK                            0x2000
#define MME_SHADOW_3_HEADEW_STOWE_OUT_SHIFT                          15
#define MME_SHADOW_3_HEADEW_STOWE_OUT_MASK                           0x8000
#define MME_SHADOW_3_HEADEW_ACC_WD_INC_DISABWE_SHIFT                 16
#define MME_SHADOW_3_HEADEW_ACC_WD_INC_DISABWE_MASK                  0x10000
#define MME_SHADOW_3_HEADEW_ADVANCE_A_SHIFT                          17
#define MME_SHADOW_3_HEADEW_ADVANCE_A_MASK                           0x20000
#define MME_SHADOW_3_HEADEW_ADVANCE_B_SHIFT                          18
#define MME_SHADOW_3_HEADEW_ADVANCE_B_MASK                           0x40000
#define MME_SHADOW_3_HEADEW_ADVANCE_CIN_SHIFT                        19
#define MME_SHADOW_3_HEADEW_ADVANCE_CIN_MASK                         0x80000
#define MME_SHADOW_3_HEADEW_ADVANCE_COUT_SHIFT                       20
#define MME_SHADOW_3_HEADEW_ADVANCE_COUT_MASK                        0x100000
#define MME_SHADOW_3_HEADEW_COMPWESSED_B_SHIFT                       21
#define MME_SHADOW_3_HEADEW_COMPWESSED_B_MASK                        0x200000
#define MME_SHADOW_3_HEADEW_MASK_CONV_END_SHIFT                      22
#define MME_SHADOW_3_HEADEW_MASK_CONV_END_MASK                       0x400000
#define MME_SHADOW_3_HEADEW_ACC_ST_INC_DISABWE_SHIFT                 23
#define MME_SHADOW_3_HEADEW_ACC_ST_INC_DISABWE_MASK                  0x800000
#define MME_SHADOW_3_HEADEW_AB_DATA_TYPE_SHIFT                       24
#define MME_SHADOW_3_HEADEW_AB_DATA_TYPE_MASK                        0x3000000
#define MME_SHADOW_3_HEADEW_CIN_DATA_TYPE_SHIFT                      26
#define MME_SHADOW_3_HEADEW_CIN_DATA_TYPE_MASK                       0x1C000000
#define MME_SHADOW_3_HEADEW_COUT_DATA_TYPE_SHIFT                     29
#define MME_SHADOW_3_HEADEW_COUT_DATA_TYPE_MASK                      0xE0000000

/* MME_SHADOW_3_KEWNEW_SIZE_MINUS_1 */
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_0_SHIFT                 0
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_0_MASK                  0xFF
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_1_SHIFT                 8
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_1_MASK                  0xFF00
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_2_SHIFT                 16
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_2_MASK                  0xFF0000
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_3_SHIFT                 24
#define MME_SHADOW_3_KEWNEW_SIZE_MINUS_1_DIM_3_MASK                  0xFF000000

/* MME_SHADOW_3_ASSOCIATED_DIMS */
#define MME_SHADOW_3_ASSOCIATED_DIMS_A_0_SHIFT                       0
#define MME_SHADOW_3_ASSOCIATED_DIMS_A_0_MASK                        0x7
#define MME_SHADOW_3_ASSOCIATED_DIMS_B_0_SHIFT                       3
#define MME_SHADOW_3_ASSOCIATED_DIMS_B_0_MASK                        0x38
#define MME_SHADOW_3_ASSOCIATED_DIMS_CIN_0_SHIFT                     6
#define MME_SHADOW_3_ASSOCIATED_DIMS_CIN_0_MASK                      0x1C0
#define MME_SHADOW_3_ASSOCIATED_DIMS_COUT_0_SHIFT                    9
#define MME_SHADOW_3_ASSOCIATED_DIMS_COUT_0_MASK                     0xE00
#define MME_SHADOW_3_ASSOCIATED_DIMS_A_1_SHIFT                       16
#define MME_SHADOW_3_ASSOCIATED_DIMS_A_1_MASK                        0x70000
#define MME_SHADOW_3_ASSOCIATED_DIMS_B_1_SHIFT                       19
#define MME_SHADOW_3_ASSOCIATED_DIMS_B_1_MASK                        0x380000
#define MME_SHADOW_3_ASSOCIATED_DIMS_CIN_1_SHIFT                     22
#define MME_SHADOW_3_ASSOCIATED_DIMS_CIN_1_MASK                      0x1C00000
#define MME_SHADOW_3_ASSOCIATED_DIMS_COUT_1_SHIFT                    25
#define MME_SHADOW_3_ASSOCIATED_DIMS_COUT_1_MASK                     0xE000000

/* MME_SHADOW_3_COUT_SCAWE */
#define MME_SHADOW_3_COUT_SCAWE_V_SHIFT                              0
#define MME_SHADOW_3_COUT_SCAWE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_3_CIN_SCAWE */
#define MME_SHADOW_3_CIN_SCAWE_V_SHIFT                               0
#define MME_SHADOW_3_CIN_SCAWE_V_MASK                                0xFFFFFFFF

/* MME_SHADOW_3_GEMMWOWP_ZP */
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_CIN_SHIFT                        0
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_CIN_MASK                         0x1FF
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_COUT_SHIFT                       9
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_COUT_MASK                        0x3FE00
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_B_SHIFT                          18
#define MME_SHADOW_3_GEMMWOWP_ZP_ZP_B_MASK                           0x7FC0000
#define MME_SHADOW_3_GEMMWOWP_ZP_GEMMWOWP_EU_EN_SHIFT                27
#define MME_SHADOW_3_GEMMWOWP_ZP_GEMMWOWP_EU_EN_MASK                 0x8000000
#define MME_SHADOW_3_GEMMWOWP_ZP_ACCUM_SHIFT                         28
#define MME_SHADOW_3_GEMMWOWP_ZP_ACCUM_MASK                          0x10000000
#define MME_SHADOW_3_GEMMWOWP_ZP_ACCUM_BIAS_SHIFT                    29
#define MME_SHADOW_3_GEMMWOWP_ZP_ACCUM_BIAS_MASK                     0x20000000
#define MME_SHADOW_3_GEMMWOWP_ZP_WEWU_EN_SHIFT                       30
#define MME_SHADOW_3_GEMMWOWP_ZP_WEWU_EN_MASK                        0x40000000

/* MME_SHADOW_3_GEMMWOWP_EXPONENT */
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_EXPONENT_CIN_SHIFT            0
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_EXPONENT_CIN_MASK             0x3F
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_EXPONENT_COUT_SHIFT           8
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_EXPONENT_COUT_MASK            0x3F00
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_MUW_CIN_EN_SHIFT              16
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_MUW_CIN_EN_MASK               0x10000
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_MUW_COUT_EN_SHIFT             17
#define MME_SHADOW_3_GEMMWOWP_EXPONENT_MUW_COUT_EN_MASK              0x20000

/* MME_SHADOW_3_A_WOI_BASE_OFFSET */
#define MME_SHADOW_3_A_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_3_A_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_3_A_VAWID_EWEMENTS */
#define MME_SHADOW_3_A_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_3_A_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_A_WOOP_STWIDE */
#define MME_SHADOW_3_A_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_3_A_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_3_A_WOI_SIZE */
#define MME_SHADOW_3_A_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_3_A_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_3_A_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_3_A_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_3_A_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_A_SPATIAW_STWIDE */
#define MME_SHADOW_3_A_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_3_A_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_A_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_3_A_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_3_A_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_B_WOI_BASE_OFFSET */
#define MME_SHADOW_3_B_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_3_B_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_3_B_VAWID_EWEMENTS */
#define MME_SHADOW_3_B_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_3_B_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_B_WOOP_STWIDE */
#define MME_SHADOW_3_B_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_3_B_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_3_B_WOI_SIZE */
#define MME_SHADOW_3_B_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_3_B_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_3_B_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_3_B_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_3_B_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_B_SPATIAW_STWIDE */
#define MME_SHADOW_3_B_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_3_B_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_B_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_3_B_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_3_B_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_C_WOI_BASE_OFFSET */
#define MME_SHADOW_3_C_WOI_BASE_OFFSET_V_SHIFT                       0
#define MME_SHADOW_3_C_WOI_BASE_OFFSET_V_MASK                        0xFFFFFFFF

/* MME_SHADOW_3_C_VAWID_EWEMENTS */
#define MME_SHADOW_3_C_VAWID_EWEMENTS_V_SHIFT                        0
#define MME_SHADOW_3_C_VAWID_EWEMENTS_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_C_WOOP_STWIDE */
#define MME_SHADOW_3_C_WOOP_STWIDE_V_SHIFT                           0
#define MME_SHADOW_3_C_WOOP_STWIDE_V_MASK                            0xFFFFFFFF

/* MME_SHADOW_3_C_WOI_SIZE */
#define MME_SHADOW_3_C_WOI_SIZE_V_SHIFT                              0
#define MME_SHADOW_3_C_WOI_SIZE_V_MASK                               0xFFFFFFFF

/* MME_SHADOW_3_C_SPATIAW_STAWT_OFFSET */
#define MME_SHADOW_3_C_SPATIAW_STAWT_OFFSET_V_SHIFT                  0
#define MME_SHADOW_3_C_SPATIAW_STAWT_OFFSET_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_C_SPATIAW_STWIDE */
#define MME_SHADOW_3_C_SPATIAW_STWIDE_V_SHIFT                        0
#define MME_SHADOW_3_C_SPATIAW_STWIDE_V_MASK                         0xFFFFFFFF

/* MME_SHADOW_3_C_SPATIAW_SIZE_MINUS_1 */
#define MME_SHADOW_3_C_SPATIAW_SIZE_MINUS_1_V_SHIFT                  0
#define MME_SHADOW_3_C_SPATIAW_SIZE_MINUS_1_V_MASK                   0xFFFFFFFF

/* MME_SHADOW_3_SYNC_OBJECT_MESSAGE */
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_SHIFT        0
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_WWITE_VAWUE_MASK         0xFFFF
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_SHIFT     16
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_ADDWESS_OFFSET_MASK      0x7FFF0000
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_OPEWATION_SHIFT          31
#define MME_SHADOW_3_SYNC_OBJECT_MESSAGE_SO_OPEWATION_MASK           0x80000000

/* MME_SHADOW_3_E_PADDING_VAWUE_A */
#define MME_SHADOW_3_E_PADDING_VAWUE_A_V_SHIFT                       0
#define MME_SHADOW_3_E_PADDING_VAWUE_A_V_MASK                        0xFFFF

/* MME_SHADOW_3_E_NUM_ITEWATION_MINUS_1 */
#define MME_SHADOW_3_E_NUM_ITEWATION_MINUS_1_V_SHIFT                 0
#define MME_SHADOW_3_E_NUM_ITEWATION_MINUS_1_V_MASK                  0xFFFFFFFF

/* MME_SHADOW_3_E_BUBBWES_PEW_SPWIT */
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_A_SHIFT                     0
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_A_MASK                      0xFF
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_B_SHIFT                     8
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_B_MASK                      0xFF00
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_CIN_SHIFT                   16
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_CIN_MASK                    0xFF0000
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_ID_SHIFT                    24
#define MME_SHADOW_3_E_BUBBWES_PEW_SPWIT_ID_MASK                     0xFF000000

#endif /* ASIC_WEG_MME_MASKS_H_ */
