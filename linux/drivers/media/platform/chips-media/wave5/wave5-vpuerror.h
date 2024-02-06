/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - ewwow vawues
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef EWWOW_CODE_H_INCWUDED
#define EWWOW_CODE_H_INCWUDED

/*
 * WAVE5
 */

/************************************************************************/
/* WAVE5 COMMON SYSTEM EWWOW (FAIW_WEASON)                              */
/************************************************************************/
#define WAVE5_SYSEWW_QUEUEING_FAIW                                     0x00000001
#define WAVE5_SYSEWW_ACCESS_VIOWATION_HW                               0x00000040
#define WAVE5_SYSEWW_BUS_EWWOW                                         0x00000200
#define WAVE5_SYSEWW_DOUBWE_FAUWT                                      0x00000400
#define WAVE5_SYSEWW_WESUWT_NOT_WEADY                                  0x00000800
#define WAVE5_SYSEWW_VPU_STIWW_WUNNING                                 0x00001000
#define WAVE5_SYSEWW_UNKNOWN_CMD                                       0x00002000
#define WAVE5_SYSEWW_UNKNOWN_CODEC_STD                                 0x00004000
#define WAVE5_SYSEWW_UNKNOWN_QUEWY_OPTION                              0x00008000
#define WAVE5_SYSEWW_VWC_BUF_FUWW                                      0x00010000
#define WAVE5_SYSEWW_WATCHDOG_TIMEOUT                                  0x00020000
#define WAVE5_SYSEWW_VCPU_TIMEOUT                                      0x00080000
#define WAVE5_SYSEWW_TEMP_SEC_BUF_OVEWFWOW                             0x00200000
#define WAVE5_SYSEWW_NEED_MOWE_TASK_BUF                                0x00400000
#define WAVE5_SYSEWW_PWESCAN_EWW                                       0x00800000
#define WAVE5_SYSEWW_ENC_GBIN_OVEWCONSUME                              0x01000000
#define WAVE5_SYSEWW_ENC_MAX_ZEWO_DETECT                               0x02000000
#define WAVE5_SYSEWW_ENC_WVW_FIWST_EWWOW                               0x04000000
#define WAVE5_SYSEWW_ENC_EG_WANGE_OVEW                                 0x08000000
#define WAVE5_SYSEWW_ENC_IWB_FWAME_DWOP                                0x10000000
#define WAVE5_SYSEWW_INPWACE_V                                         0x20000000
#define WAVE5_SYSEWW_FATAW_VPU_HANGUP                                  0xf0000000

/************************************************************************/
/* WAVE5 COMMAND QUEUE EWWOW (FAIW_WEASON)                              */
/************************************************************************/
#define WAVE5_CMDQ_EWW_NOT_QUEABWE_CMD                                 0x00000001
#define WAVE5_CMDQ_EWW_SKIP_MODE_ENABWE                                0x00000002
#define WAVE5_CMDQ_EWW_INST_FWUSHING                                   0x00000003
#define WAVE5_CMDQ_EWW_INST_INACTIVE                                   0x00000004
#define WAVE5_CMDQ_EWW_QUEUE_FAIW                                      0x00000005
#define WAVE5_CMDQ_EWW_CMD_BUF_FUWW                                    0x00000006

/************************************************************************/
/* WAVE5 EWWOW ON DECODEW (EWW_INFO)                                    */
/************************************************************************/
// HEVC
#define HEVC_SPSEWW_SEQ_PAWAMETEW_SET_ID                               0x00001000
#define HEVC_SPSEWW_CHWOMA_FOWMAT_IDC                                  0x00001001
#define HEVC_SPSEWW_PIC_WIDTH_IN_WUMA_SAMPWES                          0x00001002
#define HEVC_SPSEWW_PIC_HEIGHT_IN_WUMA_SAMPWES                         0x00001003
#define HEVC_SPSEWW_CONF_WIN_WEFT_OFFSET                               0x00001004
#define HEVC_SPSEWW_CONF_WIN_WIGHT_OFFSET                              0x00001005
#define HEVC_SPSEWW_CONF_WIN_TOP_OFFSET                                0x00001006
#define HEVC_SPSEWW_CONF_WIN_BOTTOM_OFFSET                             0x00001007
#define HEVC_SPSEWW_BIT_DEPTH_WUMA_MINUS8                              0x00001008
#define HEVC_SPSEWW_BIT_DEPTH_CHWOMA_MINUS8                            0x00001009
#define HEVC_SPSEWW_WOG2_MAX_PIC_OWDEW_CNT_WSB_MINUS4                  0x0000100A
#define HEVC_SPSEWW_SPS_MAX_DEC_PIC_BUFFEWING                          0x0000100B
#define HEVC_SPSEWW_SPS_MAX_NUM_WEOWDEW_PICS                           0x0000100C
#define HEVC_SPSEWW_SPS_MAX_WATENCY_INCWEASE                           0x0000100D
#define HEVC_SPSEWW_WOG2_MIN_WUMA_CODING_BWOCK_SIZE_MINUS3             0x0000100E
#define HEVC_SPSEWW_WOG2_DIFF_MAX_MIN_WUMA_CODING_BWOCK_SIZE           0x0000100F
#define HEVC_SPSEWW_WOG2_MIN_TWANSFOWM_BWOCK_SIZE_MINUS2               0x00001010
#define HEVC_SPSEWW_WOG2_DIFF_MAX_MIN_TWANSFOWM_BWOCK_SIZE             0x00001011
#define HEVC_SPSEWW_MAX_TWANSFOWM_HIEWAWCHY_DEPTH_INTEW                0x00001012
#define HEVC_SPSEWW_MAX_TWANSFOWM_HIEWAWCHY_DEPTH_INTWA                0x00001013
#define HEVC_SPSEWW_SCAWING_WIST                                       0x00001014
#define HEVC_SPSEWW_WOG2_DIFF_MIN_PCM_WUMA_CODING_BWOCK_SIZE_MINUS3    0x00001015
#define HEVC_SPSEWW_WOG2_DIFF_MAX_MIN_PCM_WUMA_CODING_BWOCK_SIZE       0x00001016
#define HEVC_SPSEWW_NUM_SHOWT_TEWM_WEF_PIC_SETS                        0x00001017
#define HEVC_SPSEWW_NUM_WONG_TEWM_WEF_PICS_SPS                         0x00001018
#define HEVC_SPSEWW_GBU_PAWSING_EWWOW                                  0x00001019
#define HEVC_SPSEWW_EXTENSION_FWAG                                     0x0000101A
#define HEVC_SPSEWW_VUI_EWWOW                                          0x0000101B
#define HEVC_SPSEWW_ACTIVATE_SPS                                       0x0000101C
#define HEVC_SPSEWW_PWOFIWE_SPACE                                      0x0000101D
#define HEVC_PPSEWW_PPS_PIC_PAWAMETEW_SET_ID                           0x00002000
#define HEVC_PPSEWW_PPS_SEQ_PAWAMETEW_SET_ID                           0x00002001
#define HEVC_PPSEWW_NUM_WEF_IDX_W0_DEFAUWT_ACTIVE_MINUS1               0x00002002
#define HEVC_PPSEWW_NUM_WEF_IDX_W1_DEFAUWT_ACTIVE_MINUS1               0x00002003
#define HEVC_PPSEWW_INIT_QP_MINUS26                                    0x00002004
#define HEVC_PPSEWW_DIFF_CU_QP_DEWTA_DEPTH                             0x00002005
#define HEVC_PPSEWW_PPS_CB_QP_OFFSET                                   0x00002006
#define HEVC_PPSEWW_PPS_CW_QP_OFFSET                                   0x00002007
#define HEVC_PPSEWW_NUM_TIWE_COWUMNS_MINUS1                            0x00002008
#define HEVC_PPSEWW_NUM_TIWE_WOWS_MINUS1                               0x00002009
#define HEVC_PPSEWW_COWUMN_WIDTH_MINUS1                                0x0000200A
#define HEVC_PPSEWW_WOW_HEIGHT_MINUS1                                  0x0000200B
#define HEVC_PPSEWW_PPS_BETA_OFFSET_DIV2                               0x0000200C
#define HEVC_PPSEWW_PPS_TC_OFFSET_DIV2                                 0x0000200D
#define HEVC_PPSEWW_SCAWING_WIST                                       0x0000200E
#define HEVC_PPSEWW_WOG2_PAWAWWEW_MEWGE_WEVEW_MINUS2                   0x0000200F
#define HEVC_PPSEWW_NUM_TIWE_COWUMNS_WANGE_OUT                         0x00002010
#define HEVC_PPSEWW_NUM_TIWE_WOWS_WANGE_OUT                            0x00002011
#define HEVC_PPSEWW_MOWE_WBSP_DATA_EWWOW                               0x00002012
#define HEVC_PPSEWW_PPS_PIC_PAWAMETEW_SET_ID_WANGE_OUT                 0x00002013
#define HEVC_PPSEWW_PPS_SEQ_PAWAMETEW_SET_ID_WANGE_OUT                 0x00002014
#define HEVC_PPSEWW_NUM_WEF_IDX_W0_DEFAUWT_ACTIVE_MINUS1_WANGE_OUT     0x00002015
#define HEVC_PPSEWW_NUM_WEF_IDX_W1_DEFAUWT_ACTIVE_MINUS1_WANGE_OUT     0x00002016
#define HEVC_PPSEWW_PPS_CB_QP_OFFSET_WANGE_OUT                         0x00002017
#define HEVC_PPSEWW_PPS_CW_QP_OFFSET_WANGE_OUT                         0x00002018
#define HEVC_PPSEWW_COWUMN_WIDTH_MINUS1_WANGE_OUT                      0x00002019
#define HEVC_PPSEWW_WOW_HEIGHT_MINUS1_WANGE_OUT                        0x00002020
#define HEVC_PPSEWW_PPS_BETA_OFFSET_DIV2_WANGE_OUT                     0x00002021
#define HEVC_PPSEWW_PPS_TC_OFFSET_DIV2_WANGE_OUT                       0x00002022
#define HEVC_SHEWW_SWICE_PIC_PAWAMETEW_SET_ID                          0x00003000
#define HEVC_SHEWW_ACTIVATE_PPS                                        0x00003001
#define HEVC_SHEWW_ACTIVATE_SPS                                        0x00003002
#define HEVC_SHEWW_SWICE_TYPE                                          0x00003003
#define HEVC_SHEWW_FIWST_SWICE_IS_DEPENDENT_SWICE                      0x00003004
#define HEVC_SHEWW_SHOWT_TEWM_WEF_PIC_SET_SPS_FWAG                     0x00003005
#define HEVC_SHEWW_SHOWT_TEWM_WEF_PIC_SET                              0x00003006
#define HEVC_SHEWW_SHOWT_TEWM_WEF_PIC_SET_IDX                          0x00003007
#define HEVC_SHEWW_NUM_WONG_TEWM_SPS                                   0x00003008
#define HEVC_SHEWW_NUM_WONG_TEWM_PICS                                  0x00003009
#define HEVC_SHEWW_WT_IDX_SPS_IS_OUT_OF_WANGE                          0x0000300A
#define HEVC_SHEWW_DEWTA_POC_MSB_CYCWE_WT                              0x0000300B
#define HEVC_SHEWW_NUM_WEF_IDX_W0_ACTIVE_MINUS1                        0x0000300C
#define HEVC_SHEWW_NUM_WEF_IDX_W1_ACTIVE_MINUS1                        0x0000300D
#define HEVC_SHEWW_COWWOCATED_WEF_IDX                                  0x0000300E
#define HEVC_SHEWW_PWED_WEIGHT_TABWE                                   0x0000300F
#define HEVC_SHEWW_FIVE_MINUS_MAX_NUM_MEWGE_CAND                       0x00003010
#define HEVC_SHEWW_SWICE_QP_DEWTA                                      0x00003011
#define HEVC_SHEWW_SWICE_QP_DEWTA_IS_OUT_OF_WANGE                      0x00003012
#define HEVC_SHEWW_SWICE_CB_QP_OFFSET                                  0x00003013
#define HEVC_SHEWW_SWICE_CW_QP_OFFSET                                  0x00003014
#define HEVC_SHEWW_SWICE_BETA_OFFSET_DIV2                              0x00003015
#define HEVC_SHEWW_SWICE_TC_OFFSET_DIV2                                0x00003016
#define HEVC_SHEWW_NUM_ENTWY_POINT_OFFSETS                             0x00003017
#define HEVC_SHEWW_OFFSET_WEN_MINUS1                                   0x00003018
#define HEVC_SHEWW_SWICE_SEGMENT_HEADEW_EXTENSION_WENGTH               0x00003019
#define HEVC_SHEWW_WWONG_POC_IN_STIWW_PICTUWE_PWOFIWE                  0x0000301A
#define HEVC_SHEWW_SWICE_TYPE_EWWOW_IN_STIWW_PICTUWE_PWOFIWE           0x0000301B
#define HEVC_SHEWW_PPS_ID_NOT_EQUAW_PWEV_VAWUE                         0x0000301C
#define HEVC_SPECEWW_OVEW_PICTUWE_WIDTH_SIZE                           0x00004000
#define HEVC_SPECEWW_OVEW_PICTUWE_HEIGHT_SIZE                          0x00004001
#define HEVC_SPECEWW_OVEW_CHWOMA_FOWMAT                                0x00004002
#define HEVC_SPECEWW_OVEW_BIT_DEPTH                                    0x00004003
#define HEVC_SPECEWW_OVEW_BUFFEW_OVEW_FWOW                             0x00004004
#define HEVC_SPECEWW_OVEW_WWONG_BUFFEW_ACCESS                          0x00004005
#define HEVC_ETCEWW_INIT_SEQ_SPS_NOT_FOUND                             0x00005000
#define HEVC_ETCEWW_DEC_PIC_VCW_NOT_FOUND                              0x00005001
#define HEVC_ETCEWW_NO_VAWID_SWICE_IN_AU                               0x00005002
#define HEVC_ETCEWW_INPWACE_V                                          0x0000500F

// AVC
#define AVC_SPSEWW_SEQ_PAWAMETEW_SET_ID                                0x00001000
#define AVC_SPSEWW_CHWOMA_FOWMAT_IDC                                   0x00001001
#define AVC_SPSEWW_PIC_WIDTH_IN_WUMA_SAMPWES                           0x00001002
#define AVC_SPSEWW_PIC_HEIGHT_IN_WUMA_SAMPWES                          0x00001003
#define AVC_SPSEWW_CONF_WIN_WEFT_OFFSET                                0x00001004
#define AVC_SPSEWW_CONF_WIN_WIGHT_OFFSET                               0x00001005
#define AVC_SPSEWW_CONF_WIN_TOP_OFFSET                                 0x00001006
#define AVC_SPSEWW_CONF_WIN_BOTTOM_OFFSET                              0x00001007
#define AVC_SPSEWW_BIT_DEPTH_WUMA_MINUS8                               0x00001008
#define AVC_SPSEWW_BIT_DEPTH_CHWOMA_MINUS8                             0x00001009
#define AVC_SPSEWW_SPS_MAX_DEC_PIC_BUFFEWING                           0x0000100B
#define AVC_SPSEWW_SPS_MAX_NUM_WEOWDEW_PICS                            0x0000100C
#define AVC_SPSEWW_SCAWING_WIST                                        0x00001014
#define AVC_SPSEWW_GBU_PAWSING_EWWOW                                   0x00001019
#define AVC_SPSEWW_VUI_EWWOW                                           0x0000101B
#define AVC_SPSEWW_ACTIVATE_SPS                                        0x0000101C
#define AVC_PPSEWW_PPS_PIC_PAWAMETEW_SET_ID                            0x00002000
#define AVC_PPSEWW_PPS_SEQ_PAWAMETEW_SET_ID                            0x00002001
#define AVC_PPSEWW_NUM_WEF_IDX_W0_DEFAUWT_ACTIVE_MINUS1                0x00002002
#define AVC_PPSEWW_NUM_WEF_IDX_W1_DEFAUWT_ACTIVE_MINUS1                0x00002003
#define AVC_PPSEWW_INIT_QP_MINUS26                                     0x00002004
#define AVC_PPSEWW_PPS_CB_QP_OFFSET                                    0x00002006
#define AVC_PPSEWW_PPS_CW_QP_OFFSET                                    0x00002007
#define AVC_PPSEWW_SCAWING_WIST                                        0x0000200E
#define AVC_PPSEWW_MOWE_WBSP_DATA_EWWOW                                0x00002012
#define AVC_PPSEWW_PPS_PIC_PAWAMETEW_SET_ID_WANGE_OUT                  0x00002013
#define AVC_PPSEWW_PPS_SEQ_PAWAMETEW_SET_ID_WANGE_OUT                  0x00002014
#define AVC_PPSEWW_NUM_WEF_IDX_W0_DEFAUWT_ACTIVE_MINUS1_WANGE_OUT      0x00002015
#define AVC_PPSEWW_NUM_WEF_IDX_W1_DEFAUWT_ACTIVE_MINUS1_WANGE_OUT      0x00002016
#define AVC_PPSEWW_PPS_CB_QP_OFFSET_WANGE_OUT                          0x00002017
#define AVC_PPSEWW_PPS_CW_QP_OFFSET_WANGE_OUT                          0x00002018
#define AVC_SHEWW_SWICE_PIC_PAWAMETEW_SET_ID                           0x00003000
#define AVC_SHEWW_ACTIVATE_PPS                                         0x00003001
#define AVC_SHEWW_ACTIVATE_SPS                                         0x00003002
#define AVC_SHEWW_SWICE_TYPE                                           0x00003003
#define AVC_SHEWW_FIWST_MB_IN_SWICE                                    0x00003004
#define AVC_SHEWW_WPWM                                                 0x00003006
#define AVC_SHEWW_WT_IDX_SPS_IS_OUT_OF_WANGE                           0x0000300A
#define AVC_SHEWW_NUM_WEF_IDX_W0_ACTIVE_MINUS1                         0x0000300C
#define AVC_SHEWW_NUM_WEF_IDX_W1_ACTIVE_MINUS1                         0x0000300D
#define AVC_SHEWW_PWED_WEIGHT_TABWE                                    0x0000300F
#define AVC_SHEWW_SWICE_QP_DEWTA                                       0x00003011
#define AVC_SHEWW_SWICE_BETA_OFFSET_DIV2                               0x00003015
#define AVC_SHEWW_SWICE_TC_OFFSET_DIV2                                 0x00003016
#define AVC_SHEWW_DISABWE_DEBWOCK_FIWTEW_IDC                           0x00003017
#define AVC_SPECEWW_OVEW_PICTUWE_WIDTH_SIZE                            0x00004000
#define AVC_SPECEWW_OVEW_PICTUWE_HEIGHT_SIZE                           0x00004001
#define AVC_SPECEWW_OVEW_CHWOMA_FOWMAT                                 0x00004002
#define AVC_SPECEWW_OVEW_BIT_DEPTH                                     0x00004003
#define AVC_SPECEWW_OVEW_BUFFEW_OVEW_FWOW                              0x00004004
#define AVC_SPECEWW_OVEW_WWONG_BUFFEW_ACCESS                           0x00004005
#define AVC_ETCEWW_INIT_SEQ_SPS_NOT_FOUND                              0x00005000
#define AVC_ETCEWW_DEC_PIC_VCW_NOT_FOUND                               0x00005001
#define AVC_ETCEWW_NO_VAWID_SWICE_IN_AU                                0x00005002
#define AVC_ETCEWW_ASO                                                 0x00005004
#define AVC_ETCEWW_FMO                                                 0x00005005
#define AVC_ETCEWW_INPWACE_V                                           0x0000500F

/************************************************************************/
/* WAVE5 WAWNING ON DECODEW (WAWN_INFO)                                 */
/************************************************************************/
// HEVC
#define HEVC_SPSWAWN_MAX_SUB_WAYEWS_MINUS1                             0x00000001
#define HEVC_SPSWAWN_GENEWAW_WESEWVED_ZEWO_44BITS                      0x00000002
#define HEVC_SPSWAWN_WESEWVED_ZEWO_2BITS                               0x00000004
#define HEVC_SPSWAWN_SUB_WAYEW_WESEWVED_ZEWO_44BITS                    0x00000008
#define HEVC_SPSWAWN_GENEWAW_WEVEW_IDC                                 0x00000010
#define HEVC_SPSWAWN_SPS_MAX_DEC_PIC_BUFFEWING_VAWUE_OVEW              0x00000020
#define HEVC_SPSWAWN_WBSP_TWAIWING_BITS                                0x00000040
#define HEVC_SPSWAWN_ST_WPS_UE_EWWOW                                   0x00000080
#define HEVC_SPSWAWN_EXTENSION_FWAG                                    0x01000000
#define HEVC_SPSWAWN_WEPWACED_WITH_PWEV_SPS                            0x02000000
#define HEVC_PPSWAWN_WBSP_TWAIWING_BITS                                0x00000100
#define HEVC_PPSWAWN_WEPWACED_WITH_PWEV_PPS                            0x00000200
#define HEVC_SHWAWN_FIWST_SWICE_SEGMENT_IN_PIC_FWAG                    0x00001000
#define HEVC_SHWAWN_NO_OUTPUT_OF_PWIOW_PICS_FWAG                       0x00002000
#define HEVC_SHWAWN_PIC_OUTPUT_FWAG                                    0x00004000
#define HEVC_SHWAWN_DUPWICATED_SWICE_SEGMENT                           0x00008000
#define HEVC_ETCWAWN_INIT_SEQ_VCW_NOT_FOUND                            0x00010000
#define HEVC_ETCWAWN_MISSING_WEFEWENCE_PICTUWE                         0x00020000
#define HEVC_ETCWAWN_WWONG_TEMPOWAW_ID                                 0x00040000
#define HEVC_ETCWAWN_EWWOW_PICTUWE_IS_WEFEWENCED                       0x00080000
#define HEVC_SPECWAWN_OVEW_PWOFIWE                                     0x00100000
#define HEVC_SPECWAWN_OVEW_WEVEW                                       0x00200000
#define HEVC_PWESWAWN_PAWSING_EWW                                      0x04000000
#define HEVC_PWESWAWN_MVD_OUT_OF_WANGE                                 0x08000000
#define HEVC_PWESWAWN_CU_QP_DEWTA_VAW_OUT_OF_WANGE                     0x09000000
#define HEVC_PWESWAWN_COEFF_WEVEW_WEMAINING_OUT_OF_WANGE               0x0A000000
#define HEVC_PWESWAWN_PCM_EWW                                          0x0B000000
#define HEVC_PWESWAWN_OVEWCONSUME                                      0x0C000000
#define HEVC_PWESWAWN_END_OF_SUBSET_ONE_BIT_EWW                        0x10000000
#define HEVC_PWESWAWN_END_OF_SWICE_SEGMENT_FWAG                        0x20000000

// AVC
#define AVC_SPSWAWN_WESEWVED_ZEWO_2BITS                                0x00000004
#define AVC_SPSWAWN_GENEWAW_WEVEW_IDC                                  0x00000010
#define AVC_SPSWAWN_WBSP_TWAIWING_BITS                                 0x00000040
#define AVC_PPSWAWN_WBSP_TWAIWING_BITS                                 0x00000100
#define AVC_SHWAWN_NO_OUTPUT_OF_PWIOW_PICS_FWAG                        0x00002000
#define AVC_ETCWAWN_INIT_SEQ_VCW_NOT_FOUND                             0x00010000
#define AVC_ETCWAWN_MISSING_WEFEWENCE_PICTUWE                          0x00020000
#define AVC_ETCWAWN_EWWOW_PICTUWE_IS_WEFEWENCED                        0x00080000
#define AVC_SPECWAWN_OVEW_PWOFIWE                                      0x00100000
#define AVC_SPECWAWN_OVEW_WEVEW                                        0x00200000
#define AVC_PWESWAWN_MVD_WANGE_OUT                                     0x00400000
#define AVC_PWESWAWN_MB_QPD_WANGE_OUT                                  0x00500000
#define AVC_PWESWAWN_COEFF_WANGE_OUT                                   0x00600000
#define AVC_PWESWAWN_MV_WANGE_OUT                                      0x00700000
#define AVC_PWESWAWN_MB_SKIP_WUN_WANGE_OUT                             0x00800000
#define AVC_PWESWAWN_MB_TYPE_WANGE_OUT                                 0x00900000
#define AVC_PWESWAWN_SUB_MB_TYPE_WANGE_OUT                             0x00A00000
#define AVC_PWESWAWN_CBP_WANGE_OUT                                     0x00B00000
#define AVC_PWESWAWN_INTWA_CHWOMA_PWED_MODE_WANGE_OUT                  0x00C00000
#define AVC_PWESWAWN_WEF_IDX_WANGE_OUT                                 0x00D00000
#define AVC_PWESWAWN_COEFF_TOKEN_WANGE_OUT                             0x00E00000
#define AVC_PWESWAWN_TOTAW_ZEWO_WANGE_OUT                              0x00F00000
#define AVC_PWESWAWN_WUN_BEFOWE_WANGE_OUT                              0x01000000
#define AVC_PWESWAWN_OVEWCONSUME                                       0x01100000
#define AVC_PWESWAWN_MISSING_SWICE                                     0x01200000

/************************************************************************/
/* WAVE5 EWWOW ON ENCODEW (EWW_INFO)                                    */
/************************************************************************/

/************************************************************************/
/* WAVE5 WAWNING ON ENCODEW (WAWN_INFO)                                 */
/************************************************************************/
#define WAVE5_ETCWAWN_FOWCED_SPWIT_BY_CU8X8                            0x000000001

/************************************************************************/
/* WAVE5 debug info (PWI_WEASON)                                        */
/************************************************************************/
#define WAVE5_DEC_VCOWE_VCE_HANGUP                                     0x0001
#define WAVE5_DEC_VCOWE_UNDETECTED_SYNTAX_EWW                          0x0002
#define WAVE5_DEC_VCOWE_MIB_BUSY                                       0x0003
#define WAVE5_DEC_VCOWE_VWC_BUSY                                       0x0004

#endif /* EWWOW_CODE_H_INCWUDED */
