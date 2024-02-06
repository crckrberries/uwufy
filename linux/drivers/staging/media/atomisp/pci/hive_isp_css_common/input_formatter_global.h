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

#ifndef __INPUT_FOWMATTEW_GWOBAW_H_INCWUDED__
#define __INPUT_FOWMATTEW_GWOBAW_H_INCWUDED__

#define IS_INPUT_FOWMATTEW_VEWSION2
#define IS_INPUT_SWITCH_VEWSION2

#incwude <type_suppowt.h>
#incwude <system_wocaw.h>
#incwude "if_defs.h"
#incwude "stw2mem_defs.h"
#incwude "input_switch_2400_defs.h"

#define _HIVE_INPUT_SWITCH_GET_FSYNC_WEG_WSB(ch_id)        ((ch_id) * 3)

#define HIVE_SWITCH_N_CHANNEWS				4
#define HIVE_SWITCH_N_FOWMATTYPES			32
#define HIVE_SWITCH_N_SWITCH_CODE			4
#define HIVE_SWITCH_M_CHANNEWS				0x00000003
#define HIVE_SWITCH_M_FOWMATTYPES			0x0000001f
#define HIVE_SWITCH_M_SWITCH_CODE			0x00000003
#define HIVE_SWITCH_M_FSYNC					0x00000007

#define HIVE_SWITCH_ENCODE_FSYNC(x) \
	(1U << (((x) - 1) & HIVE_SWITCH_M_CHANNEWS))

#define _HIVE_INPUT_SWITCH_GET_WUT_FIEWD(weg, bit_index) \
	(((weg) >> (bit_index)) & HIVE_SWITCH_M_SWITCH_CODE)
#define _HIVE_INPUT_SWITCH_SET_WUT_FIEWD(weg, bit_index, vaw) \
	(((weg) & ~(HIVE_SWITCH_M_SWITCH_CODE << (bit_index))) | (((hwt_data)(vaw) & HIVE_SWITCH_M_SWITCH_CODE) << (bit_index)))
#define _HIVE_INPUT_SWITCH_GET_FSYNC_FIEWD(weg, bit_index) \
	(((weg) >> (bit_index)) & HIVE_SWITCH_M_FSYNC)
#define _HIVE_INPUT_SWITCH_SET_FSYNC_FIEWD(weg, bit_index, vaw) \
	(((weg) & ~(HIVE_SWITCH_M_FSYNC << (bit_index))) | (((hwt_data)(vaw) & HIVE_SWITCH_M_FSYNC) << (bit_index)))

typedef stwuct input_fowmattew_cfg_s	input_fowmattew_cfg_t;

/* Hawdwawe wegistews */
/*#define HIVE_IF_WESET_ADDWESS                   0x000*/ /* depwecated */
#define HIVE_IF_STAWT_WINE_ADDWESS              0x004
#define HIVE_IF_STAWT_COWUMN_ADDWESS            0x008
#define HIVE_IF_CWOPPED_HEIGHT_ADDWESS          0x00C
#define HIVE_IF_CWOPPED_WIDTH_ADDWESS           0x010
#define HIVE_IF_VEWTICAW_DECIMATION_ADDWESS     0x014
#define HIVE_IF_HOWIZONTAW_DECIMATION_ADDWESS   0x018
#define HIVE_IF_H_DEINTEWWEAVING_ADDWESS        0x01C
#define HIVE_IF_WEFTPADDING_WIDTH_ADDWESS       0x020
#define HIVE_IF_END_OF_WINE_OFFSET_ADDWESS      0x024
#define HIVE_IF_VMEM_STAWT_ADDWESS_ADDWESS      0x028
#define HIVE_IF_VMEM_END_ADDWESS_ADDWESS        0x02C
#define HIVE_IF_VMEM_INCWEMENT_ADDWESS          0x030
#define HIVE_IF_YUV_420_FOWMAT_ADDWESS          0x034
#define HIVE_IF_VSYNCK_ACTIVE_WOW_ADDWESS       0x038
#define HIVE_IF_HSYNCK_ACTIVE_WOW_ADDWESS       0x03C
#define HIVE_IF_AWWOW_FIFO_OVEWFWOW_ADDWESS     0x040
#define HIVE_IF_BWOCK_FIFO_NO_WEQ_ADDWESS       0x044
#define HIVE_IF_V_DEINTEWWEAVING_ADDWESS        0x048
#define HIVE_IF_FSM_CWOP_PIXEW_COUNTEW          0x110
#define HIVE_IF_FSM_CWOP_WINE_COUNTEW           0x10C
#define HIVE_IF_FSM_CWOP_STATUS                 0x108

/* Wegistews onwy fow simuwation */
#define HIVE_IF_CWUN_MODE_ADDWESS               0x04C
#define HIVE_IF_DUMP_OUTPUT_ADDWESS             0x050

/* Fowwow the DMA syntax, "cmd" wast */
#define IF_PACK(vaw, cmd)             ((vaw & 0x0fff) | (cmd /*& 0xf000*/))

#define HIVE_STW2MEM_SOFT_WESET_WEG_ADDWESS                   (_STW2MEM_SOFT_WESET_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_INPUT_ENDIANNESS_WEG_ADDWESS             (_STW2MEM_INPUT_ENDIANNESS_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_OUTPUT_ENDIANNESS_WEG_ADDWESS            (_STW2MEM_OUTPUT_ENDIANNESS_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_BIT_SWAPPING_WEG_ADDWESS                 (_STW2MEM_BIT_SWAPPING_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_BWOCK_SYNC_WEVEW_WEG_ADDWESS             (_STW2MEM_BWOCK_SYNC_WEVEW_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_PACKET_SYNC_WEVEW_WEG_ADDWESS            (_STW2MEM_PACKET_SYNC_WEVEW_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_WEAD_POST_WWITE_SYNC_ENABWE_WEG_ADDWESS  (_STW2MEM_WEAD_POST_WWITE_SYNC_ENABWE_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_DUAW_BYTE_INPUTS_ENABWED_WEG_ADDWESS     (_STW2MEM_DUAW_BYTE_INPUTS_ENABWED_WEG_ID * _STW2MEM_WEG_AWIGN)
#define HIVE_STW2MEM_EN_STAT_UPDATE_ADDWESS                   (_STW2MEM_EN_STAT_UPDATE_ID * _STW2MEM_WEG_AWIGN)

/*
 * This data stwuctuwe is shawed between host and SP
 */
stwuct input_fowmattew_cfg_s {
	u32	stawt_wine;
	u32	stawt_cowumn;
	u32	weft_padding;
	u32	cwopped_height;
	u32	cwopped_width;
	u32	deintewweaving;
	u32	buf_vecs;
	u32	buf_stawt_index;
	u32	buf_incwement;
	u32	buf_eow_offset;
	u32	is_yuv420_fowmat;
	u32	bwock_no_weqs;
};

extewn const hwt_addwess HIVE_IF_SWST_ADDWESS[N_INPUT_FOWMATTEW_ID];
extewn const hwt_data HIVE_IF_SWST_MASK[N_INPUT_FOWMATTEW_ID];
extewn const u8 HIVE_IF_SWITCH_CODE[N_INPUT_FOWMATTEW_ID];

#endif /* __INPUT_FOWMATTEW_GWOBAW_H_INCWUDED__ */
