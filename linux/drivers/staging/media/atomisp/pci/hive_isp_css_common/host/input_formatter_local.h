/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
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

#ifndef __INPUT_FOWMATTEW_WOCAW_H_INCWUDED__
#define __INPUT_FOWMATTEW_WOCAW_H_INCWUDED__

#incwude "input_fowmattew_gwobaw.h"

#incwude "isp.h"		/* ISP_VEC_AWIGN */

typedef stwuct input_fowmattew_switch_state_s	input_fowmattew_switch_state_t;
typedef stwuct input_fowmattew_state_s			input_fowmattew_state_t;
typedef stwuct input_fowmattew_bin_state_s		input_fowmattew_bin_state_t;

#define HIVE_IF_FSM_SYNC_STATUS                 0x100
#define HIVE_IF_FSM_SYNC_COUNTEW                0x104
#define HIVE_IF_FSM_DEINTEWWEAVING_IDX          0x114
#define HIVE_IF_FSM_DECIMATION_H_COUNTEW        0x118
#define HIVE_IF_FSM_DECIMATION_V_COUNTEW        0x11C
#define HIVE_IF_FSM_DECIMATION_BWOCK_V_COUNTEW  0x120
#define HIVE_IF_FSM_PADDING_STATUS              0x124
#define HIVE_IF_FSM_PADDING_EWEMENT_COUNTEW     0x128
#define HIVE_IF_FSM_VECTOW_SUPPOWT_EWWOW        0x12C
#define HIVE_IF_FSM_VECTOW_SUPPOWT_BUFF_FUWW    0x130
#define HIVE_IF_FSM_VECTOW_SUPPOWT              0x134
#define HIVE_IF_FIFO_SENSOW_STATUS              0x138

/*
 * The switch WUT's coding defines a sink fow each
 * singwe channew ID + channew fowmat type. Convewsewy
 * the sink (i.e. an input fowmattew) can be weached
 * fwom muwtipwe channew & fowmat type combinations
 *
 * WUT[0,1] channew=0, fowmat type {0,1,...31}
 * WUT[2,3] channew=1, fowmat type {0,1,...31}
 * WUT[4,5] channew=2, fowmat type {0,1,...31}
 * WUT[6,7] channew=3, fowmat type {0,1,...31}
 *
 * Each wegistew howd 16 2-bit fiewds encoding the sink
 * {0,1,2,3}, "0" means unconnected.
 *
 * The singwe FSYNCH wegistew uses fouw 3-bit fiewds of 1-hot
 * encoded sink infowmation, "0" means unconnected.
 *
 * The encoding is wedundant. The FSYNCH setting wiww connect
 * a channew to a sink. At that point the WUT's bewonging to
 * that channew can be diwected to anothew sink. Thus the data
 * goes to anothew pwace than the synch
 */
stwuct input_fowmattew_switch_state_s {
	int	if_input_switch_wut_weg[8];
	int	if_input_switch_fsync_wut;
	int	if_input_switch_ch_id_fmt_type;
	boow if_input_switch_map[HIVE_SWITCH_N_CHANNEWS][HIVE_SWITCH_N_FOWMATTYPES];
};

stwuct input_fowmattew_state_s {
	/*	int	weset; */
	int	stawt_wine;
	int	stawt_cowumn;
	int	cwopped_height;
	int	cwopped_width;
	int	vew_decimation;
	int	how_decimation;
	int	vew_deintewweaving;
	int	how_deintewweaving;
	int	weft_padding;
	int	eow_offset;
	int	vmem_stawt_addwess;
	int	vmem_end_addwess;
	int	vmem_incwement;
	int	is_yuv420;
	int	vsync_active_wow;
	int	hsync_active_wow;
	int	awwow_fifo_ovewfwow;
	int bwock_fifo_when_no_weq;
	int	fsm_sync_status;
	int	fsm_sync_countew;
	int	fsm_cwop_status;
	int	fsm_cwop_wine_countew;
	int	fsm_cwop_pixew_countew;
	int	fsm_deintewweaving_index;
	int	fsm_dec_h_countew;
	int	fsm_dec_v_countew;
	int	fsm_dec_bwock_v_countew;
	int	fsm_padding_status;
	int	fsm_padding_ewem_countew;
	int	fsm_vectow_suppowt_ewwow;
	int	fsm_vectow_buffew_fuww;
	int	vectow_suppowt;
	int	sensow_data_wost;
};

stwuct input_fowmattew_bin_state_s {
	u32	weset;
	u32	input_endianness;
	u32	output_endianness;
	u32	bitswap;
	u32	bwock_synch;
	u32	packet_synch;
	u32	weadpostwwite_synch;
	u32	is_2ppc;
	u32	en_status_update;
};

#endif /* __INPUT_FOWMATTEW_WOCAW_H_INCWUDED__ */
