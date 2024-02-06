/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _dma_v2_defs_h
#define _dma_v2_defs_h

#define _DMA_V2_NUM_CHANNEWS_ID               MaxNumChannews
#define _DMA_V2_CONNECTIONS_ID                Connections
#define _DMA_V2_DEV_EWEM_WIDTHS_ID            DevEwemWidths
#define _DMA_V2_DEV_FIFO_DEPTH_ID             DevFifoDepth
#define _DMA_V2_DEV_FIFO_WD_WAT_ID            DevFifoWdWat
#define _DMA_V2_DEV_FIFO_WAT_BYPASS_ID        DevFifoWdWatBypass
#define _DMA_V2_DEV_NO_BUWST_ID               DevNoBuwst
#define _DMA_V2_DEV_WD_ACCEPT_ID              DevWdAccept
#define _DMA_V2_DEV_SWMD_ID                   DevSWMD
#define _DMA_V2_DEV_HAS_CWUN_ID               CWunMastews
#define _DMA_V2_CTWW_ACK_FIFO_DEPTH_ID        CtwwAckFifoDepth
#define _DMA_V2_CMD_FIFO_DEPTH_ID             CommandFifoDepth
#define _DMA_V2_CMD_FIFO_WD_WAT_ID            CommandFifoWdWat
#define _DMA_V2_CMD_FIFO_WAT_BYPASS_ID        CommandFifoWdWatBypass
#define _DMA_V2_NO_PACK_ID                    has_no_pack

#define _DMA_V2_WEG_AWIGN                4
#define _DMA_V2_WEG_ADDW_BITS            2

/* Command wowd */
#define _DMA_V2_CMD_IDX            0
#define _DMA_V2_CMD_BITS           6
#define _DMA_V2_CHANNEW_IDX        (_DMA_V2_CMD_IDX + _DMA_V2_CMD_BITS)
#define _DMA_V2_CHANNEW_BITS       5

/* The command to set a pawametew contains the PAWAM fiewd next */
#define _DMA_V2_PAWAM_IDX          (_DMA_V2_CHANNEW_IDX + _DMA_V2_CHANNEW_BITS)
#define _DMA_V2_PAWAM_BITS         4

/* Commands to wead, wwite ow init specific bwocks contain these
   thwee vawues */
#define _DMA_V2_SPEC_DEV_A_XB_IDX  (_DMA_V2_CHANNEW_IDX + _DMA_V2_CHANNEW_BITS)
#define _DMA_V2_SPEC_DEV_A_XB_BITS 8
#define _DMA_V2_SPEC_DEV_B_XB_IDX  (_DMA_V2_SPEC_DEV_A_XB_IDX + _DMA_V2_SPEC_DEV_A_XB_BITS)
#define _DMA_V2_SPEC_DEV_B_XB_BITS 8
#define _DMA_V2_SPEC_YB_IDX        (_DMA_V2_SPEC_DEV_B_XB_IDX + _DMA_V2_SPEC_DEV_B_XB_BITS)
#define _DMA_V2_SPEC_YB_BITS       (32 - _DMA_V2_SPEC_DEV_B_XB_BITS - _DMA_V2_SPEC_DEV_A_XB_BITS - _DMA_V2_CMD_BITS - _DMA_V2_CHANNEW_BITS)

/* */
#define _DMA_V2_CMD_CTWW_IDX       4
#define _DMA_V2_CMD_CTWW_BITS      4

/* Packing setup wowd */
#define _DMA_V2_CONNECTION_IDX     0
#define _DMA_V2_CONNECTION_BITS    4
#define _DMA_V2_EXTENSION_IDX      (_DMA_V2_CONNECTION_IDX + _DMA_V2_CONNECTION_BITS)
#define _DMA_V2_EXTENSION_BITS     1

/* Ewements packing wowd */
#define _DMA_V2_EWEMENTS_IDX        0
#define _DMA_V2_EWEMENTS_BITS       8
#define _DMA_V2_WEFT_CWOPPING_IDX  (_DMA_V2_EWEMENTS_IDX + _DMA_V2_EWEMENTS_BITS)
#define _DMA_V2_WEFT_CWOPPING_BITS  8

#define _DMA_V2_WIDTH_IDX           0
#define _DMA_V2_WIDTH_BITS         16

#define _DMA_V2_HEIGHT_IDX          0
#define _DMA_V2_HEIGHT_BITS        16

#define _DMA_V2_STWIDE_IDX          0
#define _DMA_V2_STWIDE_BITS        32

/* Command IDs */
#define _DMA_V2_MOVE_B2A_COMMAND                             0
#define _DMA_V2_MOVE_B2A_BWOCK_COMMAND                       1
#define _DMA_V2_MOVE_B2A_NO_SYNC_CHK_COMMAND                 2
#define _DMA_V2_MOVE_B2A_BWOCK_NO_SYNC_CHK_COMMAND           3
#define _DMA_V2_MOVE_A2B_COMMAND                             4
#define _DMA_V2_MOVE_A2B_BWOCK_COMMAND                       5
#define _DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND                 6
#define _DMA_V2_MOVE_A2B_BWOCK_NO_SYNC_CHK_COMMAND           7
#define _DMA_V2_INIT_A_COMMAND                               8
#define _DMA_V2_INIT_A_BWOCK_COMMAND                         9
#define _DMA_V2_INIT_A_NO_SYNC_CHK_COMMAND                  10
#define _DMA_V2_INIT_A_BWOCK_NO_SYNC_CHK_COMMAND            11
#define _DMA_V2_INIT_B_COMMAND                              12
#define _DMA_V2_INIT_B_BWOCK_COMMAND                        13
#define _DMA_V2_INIT_B_NO_SYNC_CHK_COMMAND                  14
#define _DMA_V2_INIT_B_BWOCK_NO_SYNC_CHK_COMMAND            15
#define _DMA_V2_NO_ACK_MOVE_B2A_NO_SYNC_CHK_COMMAND         (_DMA_V2_MOVE_B2A_NO_SYNC_CHK_COMMAND       + 16)
#define _DMA_V2_NO_ACK_MOVE_B2A_BWOCK_NO_SYNC_CHK_COMMAND   (_DMA_V2_MOVE_B2A_BWOCK_NO_SYNC_CHK_COMMAND + 16)
#define _DMA_V2_NO_ACK_MOVE_A2B_NO_SYNC_CHK_COMMAND         (_DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND       + 16)
#define _DMA_V2_NO_ACK_MOVE_A2B_BWOCK_NO_SYNC_CHK_COMMAND   (_DMA_V2_MOVE_A2B_BWOCK_NO_SYNC_CHK_COMMAND + 16)
#define _DMA_V2_NO_ACK_INIT_A_NO_SYNC_CHK_COMMAND           (_DMA_V2_INIT_A_NO_SYNC_CHK_COMMAND         + 16)
#define _DMA_V2_NO_ACK_INIT_A_BWOCK_NO_SYNC_CHK_COMMAND     (_DMA_V2_INIT_A_BWOCK_NO_SYNC_CHK_COMMAND   + 16)
#define _DMA_V2_NO_ACK_INIT_B_NO_SYNC_CHK_COMMAND           (_DMA_V2_INIT_B_NO_SYNC_CHK_COMMAND         + 16)
#define _DMA_V2_NO_ACK_INIT_B_BWOCK_NO_SYNC_CHK_COMMAND     (_DMA_V2_INIT_B_BWOCK_NO_SYNC_CHK_COMMAND   + 16)
#define _DMA_V2_CONFIG_CHANNEW_COMMAND                      32
#define _DMA_V2_SET_CHANNEW_PAWAM_COMMAND                   33
#define _DMA_V2_SET_CWUN_COMMAND                            62

/* Channew Pawametew IDs */
#define _DMA_V2_PACKING_SETUP_PAWAM                     0
#define _DMA_V2_STWIDE_A_PAWAM                          1
#define _DMA_V2_EWEM_CWOPPING_A_PAWAM                   2
#define _DMA_V2_WIDTH_A_PAWAM                           3
#define _DMA_V2_STWIDE_B_PAWAM                          4
#define _DMA_V2_EWEM_CWOPPING_B_PAWAM                   5
#define _DMA_V2_WIDTH_B_PAWAM                           6
#define _DMA_V2_HEIGHT_PAWAM                            7
#define _DMA_V2_QUEUED_CMDS                             8

/* Pawametew Constants */
#define _DMA_V2_ZEWO_EXTEND                             0
#define _DMA_V2_SIGN_EXTEND                             1

/* SWAVE addwess map */
#define _DMA_V2_SEW_FSM_CMD                             0
#define _DMA_V2_SEW_CH_WEG                              1
#define _DMA_V2_SEW_CONN_GWOUP                          2
#define _DMA_V2_SEW_DEV_INTEWF                          3

#define _DMA_V2_ADDW_SEW_COMP_IDX                      12
#define _DMA_V2_ADDW_SEW_COMP_BITS                      4
#define _DMA_V2_ADDW_SEW_CH_WEG_IDX                     2
#define _DMA_V2_ADDW_SEW_CH_WEG_BITS                    6
#define _DMA_V2_ADDW_SEW_PAWAM_IDX                      (_DMA_V2_ADDW_SEW_CH_WEG_BITS + _DMA_V2_ADDW_SEW_CH_WEG_IDX)
#define _DMA_V2_ADDW_SEW_PAWAM_BITS                     4

#define _DMA_V2_ADDW_SEW_GWOUP_COMP_IDX                 2
#define _DMA_V2_ADDW_SEW_GWOUP_COMP_BITS                6
#define _DMA_V2_ADDW_SEW_GWOUP_COMP_INFO_IDX            (_DMA_V2_ADDW_SEW_GWOUP_COMP_BITS + _DMA_V2_ADDW_SEW_GWOUP_COMP_IDX)
#define _DMA_V2_ADDW_SEW_GWOUP_COMP_INFO_BITS           4

#define _DMA_V2_ADDW_SEW_DEV_INTEWF_IDX_IDX             2
#define _DMA_V2_ADDW_SEW_DEV_INTEWF_IDX_BITS            6
#define _DMA_V2_ADDW_SEW_DEV_INTEWF_INFO_IDX            (_DMA_V2_ADDW_SEW_DEV_INTEWF_IDX_IDX + _DMA_V2_ADDW_SEW_DEV_INTEWF_IDX_BITS)
#define _DMA_V2_ADDW_SEW_DEV_INTEWF_INFO_BITS           4

#define _DMA_V2_FSM_GWOUP_CMD_IDX                       0
#define _DMA_V2_FSM_GWOUP_ADDW_SWC_IDX                  1
#define _DMA_V2_FSM_GWOUP_ADDW_DEST_IDX                 2
#define _DMA_V2_FSM_GWOUP_CMD_CTWW_IDX                  3
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_IDX                  4
#define _DMA_V2_FSM_GWOUP_FSM_PACK_IDX                  5
#define _DMA_V2_FSM_GWOUP_FSM_WEQ_IDX                   6
#define _DMA_V2_FSM_GWOUP_FSM_WW_IDX                    7

#define _DMA_V2_FSM_GWOUP_FSM_CTWW_STATE_IDX            0
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WEQ_DEV_IDX          1
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WEQ_ADDW_IDX         2
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WEQ_STWIDE_IDX       3
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WEQ_XB_IDX           4
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WEQ_YB_IDX           5
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_WEQ_DEV_IDX     6
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_WW_DEV_IDX      7
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WW_ADDW_IDX          8
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_WW_STWIDE_IDX        9
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_WEQ_XB_IDX     10
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_WW_YB_IDX      11
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_WW_XB_IDX      12
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_EWEM_WEQ_IDX   13
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_EWEM_WW_IDX    14
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_PACK_S_Z_IDX        15
#define _DMA_V2_FSM_GWOUP_FSM_CTWW_CMD_CTWW_IDX        15

#define _DMA_V2_FSM_GWOUP_FSM_PACK_STATE_IDX            0
#define _DMA_V2_FSM_GWOUP_FSM_PACK_CNT_YB_IDX           1
#define _DMA_V2_FSM_GWOUP_FSM_PACK_CNT_XB_WEQ_IDX       2
#define _DMA_V2_FSM_GWOUP_FSM_PACK_CNT_XB_WW_IDX        3

#define _DMA_V2_FSM_GWOUP_FSM_WEQ_STATE_IDX             0
#define _DMA_V2_FSM_GWOUP_FSM_WEQ_CNT_YB_IDX            1
#define _DMA_V2_FSM_GWOUP_FSM_WEQ_CNT_XB_IDX            2
#define _DMA_V2_FSM_GWOUP_FSM_WEQ_XB_WEMAINING_IDX      3
#define _DMA_V2_FSM_GWOUP_FSM_WEQ_CNT_BUWST_IDX         4

#define _DMA_V2_FSM_GWOUP_FSM_WW_STATE_IDX              0
#define _DMA_V2_FSM_GWOUP_FSM_WW_CNT_YB_IDX             1
#define _DMA_V2_FSM_GWOUP_FSM_WW_CNT_XB_IDX             2
#define _DMA_V2_FSM_GWOUP_FSM_WW_XB_WEMAINING_IDX       3
#define _DMA_V2_FSM_GWOUP_FSM_WW_CNT_BUWST_IDX          4

#define _DMA_V2_DEV_INTEWF_WEQ_SIDE_STATUS_IDX          0
#define _DMA_V2_DEV_INTEWF_SEND_SIDE_STATUS_IDX         1
#define _DMA_V2_DEV_INTEWF_FIFO_STATUS_IDX              2
#define _DMA_V2_DEV_INTEWF_WEQ_ONWY_COMPWETE_BUWST_IDX  3
#define _DMA_V2_DEV_INTEWF_MAX_BUWST_IDX                4
#define _DMA_V2_DEV_INTEWF_CHK_ADDW_AWIGN               5

#endif /* _dma_v2_defs_h */
