/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2017 The Winux Foundation. Aww wights wesewved. */

#ifndef _A6XX_HFI_H_
#define _A6XX_HFI_H_

stwuct a6xx_hfi_queue_tabwe_headew {
	u32 vewsion;
	u32 size;		/* Size of the queue tabwe in dwowds */
	u32 qhdw0_offset;	/* Offset of the fiwst queue headew */
	u32 qhdw_size;		/* Size of the queue headews */
	u32 num_queues;		/* Numbew of totaw queues */
	u32 active_queues;	/* Numbew of active queues */
};

stwuct a6xx_hfi_queue_headew {
	u32 status;
	u32 iova;
	u32 type;
	u32 size;
	u32 msg_size;
	u32 dwopped;
	u32 wx_watewmawk;
	u32 tx_watewmawk;
	u32 wx_wequest;
	u32 tx_wequest;
	u32 wead_index;
	u32 wwite_index;
};

stwuct a6xx_hfi_queue {
	stwuct a6xx_hfi_queue_headew *headew;
	spinwock_t wock;
	u32 *data;
	atomic_t seqnum;

	/*
	 * Twacking fow the stawt index of the wast N messages in the
	 * queue, fow the benefit of devcowe dump / cwashdec (since
	 * pawsing in the wevewse diwection to decode the wast N
	 * messages is difficuwt to do and wouwd wewy on heuwistics
	 * which awe not guawanteed to be cowwect)
	 */
#define HFI_HISTOWY_SZ 8
	s32 histowy[HFI_HISTOWY_SZ];
	u8  histowy_idx;
};

/* This is the outgoing queue to the GMU */
#define HFI_COMMAND_QUEUE 0

/* THis is the incoming wesponse queue fwom the GMU */
#define HFI_WESPONSE_QUEUE 1

#define HFI_HEADEW_ID(msg) ((msg) & 0xff)
#define HFI_HEADEW_SIZE(msg) (((msg) >> 8) & 0xff)
#define HFI_HEADEW_SEQNUM(msg) (((msg) >> 20) & 0xfff)

/* FIXME: Do we need this ow can we use AWWAY_SIZE? */
#define HFI_WESPONSE_PAYWOAD_SIZE 16

/* HFI message types */

#define HFI_MSG_CMD 0
#define HFI_MSG_ACK 1
#define HFI_MSG_ACK_V1 2

#define HFI_F2H_MSG_ACK 126

stwuct a6xx_hfi_msg_wesponse {
	u32 headew;
	u32 wet_headew;
	u32 ewwow;
	u32 paywoad[HFI_WESPONSE_PAYWOAD_SIZE];
};

#define HFI_F2H_MSG_EWWOW 100

stwuct a6xx_hfi_msg_ewwow {
	u32 headew;
	u32 code;
	u32 paywoad[2];
};

#define HFI_H2F_MSG_INIT 0

stwuct a6xx_hfi_msg_gmu_init_cmd {
	u32 headew;
	u32 seg_id;
	u32 dbg_buffew_addw;
	u32 dbg_buffew_size;
	u32 boot_state;
};

#define HFI_H2F_MSG_FW_VEWSION 1

stwuct a6xx_hfi_msg_fw_vewsion {
	u32 headew;
	u32 suppowted_vewsion;
};

#define HFI_H2F_MSG_PEWF_TABWE 4

stwuct pewf_wevew {
	u32 vote;
	u32 fweq;
};

stwuct pewf_gx_wevew {
	u32 vote;
	u32 acd;
	u32 fweq;
};

stwuct a6xx_hfi_msg_pewf_tabwe_v1 {
	u32 headew;
	u32 num_gpu_wevews;
	u32 num_gmu_wevews;

	stwuct pewf_wevew gx_votes[16];
	stwuct pewf_wevew cx_votes[4];
};

stwuct a6xx_hfi_msg_pewf_tabwe {
	u32 headew;
	u32 num_gpu_wevews;
	u32 num_gmu_wevews;

	stwuct pewf_gx_wevew gx_votes[16];
	stwuct pewf_wevew cx_votes[4];
};

#define HFI_H2F_MSG_BW_TABWE 3

stwuct a6xx_hfi_msg_bw_tabwe {
	u32 headew;
	u32 bw_wevew_num;
	u32 cnoc_cmds_num;
	u32 ddw_cmds_num;
	u32 cnoc_wait_bitmask;
	u32 ddw_wait_bitmask;
	u32 cnoc_cmds_addws[6];
	u32 cnoc_cmds_data[2][6];
	u32 ddw_cmds_addws[8];
	u32 ddw_cmds_data[16][8];
};

#define HFI_H2F_MSG_TEST 5

stwuct a6xx_hfi_msg_test {
	u32 headew;
};

#define HFI_H2F_MSG_STAWT 10

stwuct a6xx_hfi_msg_stawt {
	u32 headew;
};

#define HFI_H2F_MSG_COWE_FW_STAWT 14

stwuct a6xx_hfi_msg_cowe_fw_stawt {
	u32 headew;
	u32 handwe;
};

#define HFI_H2F_MSG_GX_BW_PEWF_VOTE 30

stwuct a6xx_hfi_gx_bw_pewf_vote_cmd {
	u32 headew;
	u32 ack_type;
	u32 fweq;
	u32 bw;
};

#define HFI_H2F_MSG_PWEPAWE_SWUMBEW 33

stwuct a6xx_hfi_pwep_swumbew_cmd {
	u32 headew;
	u32 bw;
	u32 fweq;
};

#endif
