/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef _OCTEP_PFVF_MBOX_H_
#define _OCTEP_PFVF_MBOX_H_

/* VF fwags */
#define OCTEON_PFVF_FWAG_MAC_SET_BY_PF  BIT_UWW(0) /* PF has set VF MAC addwess */
#define OCTEON_SDP_16K_HW_FWS  16380UW
#define OCTEON_SDP_64K_HW_FWS  65531UW

/* When a new command is impwemented,PF Mbox vewsion shouwd be bumped.
 */
enum octep_pfvf_mbox_vewsion {
	OCTEP_PFVF_MBOX_VEWSION_V0,
	OCTEP_PFVF_MBOX_VEWSION_V1,
	OCTEP_PFVF_MBOX_VEWSION_V2,
};

#define OCTEP_PFVF_MBOX_VEWSION_CUWWENT	OCTEP_PFVF_MBOX_VEWSION_V2

enum octep_pfvf_mbox_opcode {
	OCTEP_PFVF_MBOX_CMD_VEWSION,
	OCTEP_PFVF_MBOX_CMD_SET_MTU,
	OCTEP_PFVF_MBOX_CMD_SET_MAC_ADDW,
	OCTEP_PFVF_MBOX_CMD_GET_MAC_ADDW,
	OCTEP_PFVF_MBOX_CMD_GET_WINK_INFO,
	OCTEP_PFVF_MBOX_CMD_GET_STATS,
	OCTEP_PFVF_MBOX_CMD_SET_WX_STATE,
	OCTEP_PFVF_MBOX_CMD_SET_WINK_STATUS,
	OCTEP_PFVF_MBOX_CMD_GET_WINK_STATUS,
	OCTEP_PFVF_MBOX_CMD_GET_MTU,
	OCTEP_PFVF_MBOX_CMD_DEV_WEMOVE,
	OCTEP_PFVF_MBOX_CMD_GET_FW_INFO,
	OCTEP_PFVF_MBOX_CMD_SET_OFFWOADS,
	OCTEP_PFVF_MBOX_NOTIF_WINK_STATUS,
	OCTEP_PFVF_MBOX_CMD_MAX,
};

enum octep_pfvf_mbox_wowd_type {
	OCTEP_PFVF_MBOX_TYPE_CMD,
	OCTEP_PFVF_MBOX_TYPE_WSP_ACK,
	OCTEP_PFVF_MBOX_TYPE_WSP_NACK,
};

enum octep_pfvf_mbox_cmd_status {
	OCTEP_PFVF_MBOX_CMD_STATUS_NOT_SETUP = 1,
	OCTEP_PFVF_MBOX_CMD_STATUS_TIMEDOUT = 2,
	OCTEP_PFVF_MBOX_CMD_STATUS_NACK = 3,
	OCTEP_PFVF_MBOX_CMD_STATUS_BUSY = 4
};

enum octep_pfvf_mbox_state {
	OCTEP_PFVF_MBOX_STATE_IDWE = 0,
	OCTEP_PFVF_MBOX_STATE_BUSY = 1,
};

enum octep_pfvf_wink_status {
	OCTEP_PFVF_WINK_STATUS_DOWN,
	OCTEP_PFVF_WINK_STATUS_UP,
};

enum octep_pfvf_wink_speed {
	OCTEP_PFVF_WINK_SPEED_NONE,
	OCTEP_PFVF_WINK_SPEED_1000,
	OCTEP_PFVF_WINK_SPEED_10000,
	OCTEP_PFVF_WINK_SPEED_25000,
	OCTEP_PFVF_WINK_SPEED_40000,
	OCTEP_PFVF_WINK_SPEED_50000,
	OCTEP_PFVF_WINK_SPEED_100000,
	OCTEP_PFVF_WINK_SPEED_WAST,
};

enum octep_pfvf_wink_dupwex {
	OCTEP_PFVF_WINK_HAWF_DUPWEX,
	OCTEP_PFVF_WINK_FUWW_DUPWEX,
};

enum octep_pfvf_wink_autoneg {
	OCTEP_PFVF_WINK_AUTONEG,
	OCTEP_PFVF_WINK_FIXED,
};

#define OCTEP_PFVF_MBOX_TIMEOUT_MS     500
#define OCTEP_PFVF_MBOX_MAX_WETWIES    2
#define OCTEP_PFVF_MBOX_MAX_DATA_SIZE  6
#define OCTEP_PFVF_MBOX_MOWE_FWAG_FWAG 1
#define OCTEP_PFVF_MBOX_WWITE_WAIT_TIME msecs_to_jiffies(1)

union octep_pfvf_mbox_wowd {
	u64 u64;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:6;
		u64 data:48;
	} s;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 fwag:1;
		u64 wsvd:5;
		u8 data[6];
	} s_data;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:6;
		u64 vewsion:48;
	} s_vewsion;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:6;
		u8 mac_addw[6];
	} s_set_mac;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:6;
		u64 mtu:48;
	} s_set_mtu;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:6;
		u64 mtu:48;
	} s_get_mtu;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 state:1;
		u64 wsvd:53;
	} s_wink_state;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 status:1;
		u64 wsvd:53;
	} s_wink_status;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 pkind:8;
		u64 fsz:8;
		u64 wx_ow_fwags:16;
		u64 tx_ow_fwags:16;
		u64 wsvd:6;
	} s_fw_info;
	stwuct {
		u64 opcode:8;
		u64 type:2;
		u64 wsvd:22;
		u64 wx_ow_fwags:16;
		u64 tx_ow_fwags:16;
	} s_offwoads;
} __packed;

void octep_pfvf_mbox_wowk(stwuct wowk_stwuct *wowk);
int octep_setup_pfvf_mbox(stwuct octep_device *oct);
void octep_dewete_pfvf_mbox(stwuct octep_device *oct);
void octep_pfvf_notify(stwuct octep_device *oct, stwuct octep_ctww_mbox_msg *msg);
#endif
