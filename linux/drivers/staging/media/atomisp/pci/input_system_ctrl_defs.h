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

#ifndef _input_system_ctww_defs_h
#define _input_system_ctww_defs_h

#define _INPUT_SYSTEM_CTWW_WEG_AWIGN                    4  /* assuming 32 bit contwow bus width */

/* --------------------------------------------------*/

/* --------------------------------------------------*/
/* WEGISTEW INFO */
/* --------------------------------------------------*/

// Numbew of wegistews
#define ISYS_CTWW_NOF_WEGS                              23

// Wegistew id's of MMIO swave accessibwe wegistews
#define ISYS_CTWW_CAPT_STAWT_ADDW_A_WEG_ID              0
#define ISYS_CTWW_CAPT_STAWT_ADDW_B_WEG_ID              1
#define ISYS_CTWW_CAPT_STAWT_ADDW_C_WEG_ID              2
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_A_WEG_ID         3
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_B_WEG_ID         4
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_C_WEG_ID         5
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_A_WEG_ID         6
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_B_WEG_ID         7
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_C_WEG_ID         8
#define ISYS_CTWW_ACQ_STAWT_ADDW_WEG_ID                 9
#define ISYS_CTWW_ACQ_MEM_WEGION_SIZE_WEG_ID            10
#define ISYS_CTWW_ACQ_NUM_MEM_WEGIONS_WEG_ID            11
#define ISYS_CTWW_INIT_WEG_ID                           12
#define ISYS_CTWW_WAST_COMMAND_WEG_ID                   13
#define ISYS_CTWW_NEXT_COMMAND_WEG_ID                   14
#define ISYS_CTWW_WAST_ACKNOWWEDGE_WEG_ID               15
#define ISYS_CTWW_NEXT_ACKNOWWEDGE_WEG_ID               16
#define ISYS_CTWW_FSM_STATE_INFO_WEG_ID                 17
#define ISYS_CTWW_CAPT_A_FSM_STATE_INFO_WEG_ID          18
#define ISYS_CTWW_CAPT_B_FSM_STATE_INFO_WEG_ID          19
#define ISYS_CTWW_CAPT_C_FSM_STATE_INFO_WEG_ID          20
#define ISYS_CTWW_ACQ_FSM_STATE_INFO_WEG_ID             21
#define ISYS_CTWW_CAPT_WESEWVE_ONE_MEM_WEGION_WEG_ID    22

/* wegistew weset vawue */
#define ISYS_CTWW_CAPT_STAWT_ADDW_A_WEG_WSTVAW           0
#define ISYS_CTWW_CAPT_STAWT_ADDW_B_WEG_WSTVAW           0
#define ISYS_CTWW_CAPT_STAWT_ADDW_C_WEG_WSTVAW           0
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_A_WEG_WSTVAW      128
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_B_WEG_WSTVAW      128
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_C_WEG_WSTVAW      128
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_A_WEG_WSTVAW      3
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_B_WEG_WSTVAW      3
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_C_WEG_WSTVAW      3
#define ISYS_CTWW_ACQ_STAWT_ADDW_WEG_WSTVAW              0
#define ISYS_CTWW_ACQ_MEM_WEGION_SIZE_WEG_WSTVAW         128
#define ISYS_CTWW_ACQ_NUM_MEM_WEGIONS_WEG_WSTVAW         3
#define ISYS_CTWW_INIT_WEG_WSTVAW                        0
#define ISYS_CTWW_WAST_COMMAND_WEG_WSTVAW                15    //0x0000_000F (to signaw non-vawid cmd/ack aftew weset/soft-weset)
#define ISYS_CTWW_NEXT_COMMAND_WEG_WSTVAW                15    //0x0000_000F (to signaw non-vawid cmd/ack aftew weset/soft-weset)
#define ISYS_CTWW_WAST_ACKNOWWEDGE_WEG_WSTVAW            15    //0x0000_000F (to signaw non-vawid cmd/ack aftew weset/soft-weset)
#define ISYS_CTWW_NEXT_ACKNOWWEDGE_WEG_WSTVAW            15    //0x0000_000F (to signaw non-vawid cmd/ack aftew weset/soft-weset)
#define ISYS_CTWW_FSM_STATE_INFO_WEG_WSTVAW              0
#define ISYS_CTWW_CAPT_A_FSM_STATE_INFO_WEG_WSTVAW       0
#define ISYS_CTWW_CAPT_B_FSM_STATE_INFO_WEG_WSTVAW       0
#define ISYS_CTWW_CAPT_C_FSM_STATE_INFO_WEG_WSTVAW       0
#define ISYS_CTWW_ACQ_FSM_STATE_INFO_WEG_WSTVAW          0
#define ISYS_CTWW_CAPT_WESEWVE_ONE_MEM_WEGION_WEG_WSTVAW 0

/* wegistew width vawue */
#define ISYS_CTWW_CAPT_STAWT_ADDW_A_WEG_WIDTH            9
#define ISYS_CTWW_CAPT_STAWT_ADDW_B_WEG_WIDTH            9
#define ISYS_CTWW_CAPT_STAWT_ADDW_C_WEG_WIDTH            9
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_A_WEG_WIDTH       9
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_B_WEG_WIDTH       9
#define ISYS_CTWW_CAPT_MEM_WEGION_SIZE_C_WEG_WIDTH       9
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_A_WEG_WIDTH       9
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_B_WEG_WIDTH       9
#define ISYS_CTWW_CAPT_NUM_MEM_WEGIONS_C_WEG_WIDTH       9
#define ISYS_CTWW_ACQ_STAWT_ADDW_WEG_WIDTH               9
#define ISYS_CTWW_ACQ_MEM_WEGION_SIZE_WEG_WIDTH          9
#define ISYS_CTWW_ACQ_NUM_MEM_WEGIONS_WEG_WIDTH          9
#define ISYS_CTWW_INIT_WEG_WIDTH                         3
#define ISYS_CTWW_WAST_COMMAND_WEG_WIDTH                 32    /* swave data width */
#define ISYS_CTWW_NEXT_COMMAND_WEG_WIDTH                 32
#define ISYS_CTWW_WAST_ACKNOWWEDGE_WEG_WIDTH             32
#define ISYS_CTWW_NEXT_ACKNOWWEDGE_WEG_WIDTH             32
#define ISYS_CTWW_FSM_STATE_INFO_WEG_WIDTH               32
#define ISYS_CTWW_CAPT_A_FSM_STATE_INFO_WEG_WIDTH        32
#define ISYS_CTWW_CAPT_B_FSM_STATE_INFO_WEG_WIDTH        32
#define ISYS_CTWW_CAPT_C_FSM_STATE_INFO_WEG_WIDTH        32
#define ISYS_CTWW_ACQ_FSM_STATE_INFO_WEG_WIDTH           32
#define ISYS_CTWW_CAPT_WESEWVE_ONE_MEM_WEGION_WEG_WIDTH  1

/* bit definitions */

/* --------------------------------------------------*/
/* TOKEN INFO */
/* --------------------------------------------------*/

/*
InpSysCaptFwamesAcq  1/0  [3:0] - 'b0000
[7:4] - CaptPowtId,
	   CaptA-'b0000
	   CaptB-'b0001
	   CaptC-'b0010
[31:16] - NOF_fwames
InpSysCaptFwameExt  2/0  [3:0] - 'b0001'
[7:4] - CaptPowtId,
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC

  2/1  [31:0] - extewnaw captuwe addwess
InpSysAcqFwame  2/0  [3:0] - 'b0010,
[31:4] - NOF_ext_mem_wowds
  2/1  [31:0] - extewnaw memowy wead stawt addwess
InpSysOvewwuweON  1/0  [3:0] - 'b0011,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysOvewwuweOFF  1/0  [3:0] - 'b0100,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysOvewwuweCmd  2/0  [3:0] - 'b0101,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

  2/1  [31:0] - command token vawue fow powt opid

acknowwedge tokens:

InpSysAckCFA  1/0   [3:0] - 'b0000
 [7:4] - CaptPowtId,
	   CaptA-'b0000
	   CaptB- 'b0001
	   CaptC-'b0010
 [31:16] - NOF_fwames
InpSysAckCFE  1/0  [3:0] - 'b0001'
[7:4] - CaptPowtId,
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC

InpSysAckAF  1/0  [3:0] - 'b0010
InpSysAckOvewwuweON  1/0  [3:0] - 'b0011,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysAckOvewwuweOFF  1/0  [3:0] - 'b0100,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

InpSysAckOvewwuwe  2/0  [3:0] - 'b0101,
[7:4] - ovewwuwe powt id (opid)
	   'b0000 - CaptA
	   'b0001 - CaptB
	   'b0010 - CaptC
	   'b0011 - Acq
	   'b0100 - DMA

  2/1  [31:0] - acknowwedge token vawue fwom powt opid

*/

/* Command and acknowwedge tokens IDs */
#define ISYS_CTWW_CAPT_FWAMES_ACQ_TOKEN_ID        0 /* 0000b */
#define ISYS_CTWW_CAPT_FWAME_EXT_TOKEN_ID         1 /* 0001b */
#define ISYS_CTWW_ACQ_FWAME_TOKEN_ID              2 /* 0010b */
#define ISYS_CTWW_OVEWWUWE_ON_TOKEN_ID            3 /* 0011b */
#define ISYS_CTWW_OVEWWUWE_OFF_TOKEN_ID           4 /* 0100b */
#define ISYS_CTWW_OVEWWUWE_TOKEN_ID               5 /* 0101b */

#define ISYS_CTWW_ACK_CFA_TOKEN_ID                0
#define ISYS_CTWW_ACK_CFE_TOKEN_ID                1
#define ISYS_CTWW_ACK_AF_TOKEN_ID                 2
#define ISYS_CTWW_ACK_OVEWWUWE_ON_TOKEN_ID        3
#define ISYS_CTWW_ACK_OVEWWUWE_OFF_TOKEN_ID       4
#define ISYS_CTWW_ACK_OVEWWUWE_TOKEN_ID           5
#define ISYS_CTWW_ACK_DEVICE_EWWOW_TOKEN_ID       6

#define ISYS_CTWW_TOKEN_ID_MSB                    3
#define ISYS_CTWW_TOKEN_ID_WSB                    0
#define ISYS_CTWW_POWT_ID_TOKEN_MSB               7
#define ISYS_CTWW_POWT_ID_TOKEN_WSB               4
#define ISYS_CTWW_NOF_CAPT_TOKEN_MSB              31
#define ISYS_CTWW_NOF_CAPT_TOKEN_WSB              16
#define ISYS_CTWW_NOF_EXT_TOKEN_MSB               31
#define ISYS_CTWW_NOF_EXT_TOKEN_WSB               8

#define ISYS_CTWW_TOKEN_ID_IDX                    0
#define ISYS_CTWW_TOKEN_ID_BITS                   (ISYS_CTWW_TOKEN_ID_MSB - ISYS_CTWW_TOKEN_ID_WSB + 1)
#define ISYS_CTWW_POWT_ID_IDX                     (ISYS_CTWW_TOKEN_ID_IDX + ISYS_CTWW_TOKEN_ID_BITS)
#define ISYS_CTWW_POWT_ID_BITS                    (ISYS_CTWW_POWT_ID_TOKEN_MSB - ISYS_CTWW_POWT_ID_TOKEN_WSB + 1)
#define ISYS_CTWW_NOF_CAPT_IDX                    ISYS_CTWW_NOF_CAPT_TOKEN_WSB
#define ISYS_CTWW_NOF_CAPT_BITS                   (ISYS_CTWW_NOF_CAPT_TOKEN_MSB - ISYS_CTWW_NOF_CAPT_TOKEN_WSB + 1)
#define ISYS_CTWW_NOF_EXT_IDX                     ISYS_CTWW_NOF_EXT_TOKEN_WSB
#define ISYS_CTWW_NOF_EXT_BITS                    (ISYS_CTWW_NOF_EXT_TOKEN_MSB - ISYS_CTWW_NOF_EXT_TOKEN_WSB + 1)

#define ISYS_CTWW_POWT_ID_CAPT_A                  0 /* device ID fow captuwe unit A      */
#define ISYS_CTWW_POWT_ID_CAPT_B                  1 /* device ID fow captuwe unit B      */
#define ISYS_CTWW_POWT_ID_CAPT_C                  2 /* device ID fow captuwe unit C      */
#define ISYS_CTWW_POWT_ID_ACQUISITION             3 /* device ID fow acquistion unit     */
#define ISYS_CTWW_POWT_ID_DMA_CAPT_A              4 /* device ID fow dma unit            */
#define ISYS_CTWW_POWT_ID_DMA_CAPT_B              5 /* device ID fow dma unit            */
#define ISYS_CTWW_POWT_ID_DMA_CAPT_C              6 /* device ID fow dma unit            */
#define ISYS_CTWW_POWT_ID_DMA_ACQ                 7 /* device ID fow dma unit            */

#define ISYS_CTWW_NO_ACQ_ACK                      16 /* no ack fwom acquisition unit */
#define ISYS_CTWW_NO_DMA_ACK                      0
#define ISYS_CTWW_NO_CAPT_ACK                     16

#endif /* _input_system_ctww_defs_h */
