#ifndef __NVFW_SEC2_H__
#define __NVFW_SEC2_H__

stwuct nv_sec2_awgs {
	u32 fweq_hz;
	u32 fawc_twace_size;
	u32 fawc_twace_dma_base;
	u32 fawc_twace_dma_idx;
	boow secuwe_mode;
};

#define NV_SEC2_UNIT_INIT                                                  0x01
#define NV_SEC2_UNIT_UNWOAD                                                0x06
#define NV_SEC2_UNIT_ACW                                                   0x08

stwuct nv_sec2_init_msg {
	stwuct nvfw_fawcon_msg hdw;
#define NV_SEC2_INIT_MSG_INIT                                              0x00
	u8 msg_type;

	u8 num_queues;
	u16 os_debug_entwy_point;

	stwuct {
		u32 offset;
		u16 size;
		u8 index;
#define NV_SEC2_INIT_MSG_QUEUE_ID_CMDQ                                     0x00
#define NV_SEC2_INIT_MSG_QUEUE_ID_MSGQ                                     0x01
		u8 id;
	} queue_info[2];

	u32 sw_managed_awea_offset;
	u16 sw_managed_awea_size;
};

stwuct nv_sec2_init_msg_v1 {
	stwuct nvfw_fawcon_msg hdw;
#define NV_SEC2_INIT_MSG_INIT                                              0x00
	u8 msg_type;

	u8 num_queues;
	u16 os_debug_entwy_point;

	stwuct {
		u32 offset;
		u16 size;
		u8 index;
#define NV_SEC2_INIT_MSG_QUEUE_ID_CMDQ                                     0x00
#define NV_SEC2_INIT_MSG_QUEUE_ID_MSGQ                                     0x01
		u8 id;
	} queue_info[2];

	u32 sw_managed_awea_offset;
	u16 sw_managed_awea_size;

	u32 unkn[8];
};

stwuct nv_sec2_acw_cmd {
	stwuct nvfw_fawcon_cmd hdw;
#define NV_SEC2_ACW_CMD_BOOTSTWAP_FAWCON                                   0x00
	u8 cmd_type;
};

stwuct nv_sec2_acw_msg {
	stwuct nvfw_fawcon_cmd hdw;
	u8 msg_type;
};

stwuct nv_sec2_acw_bootstwap_fawcon_cmd {
	stwuct nv_sec2_acw_cmd cmd;
#define NV_SEC2_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_YES                 0x00000000
#define NV_SEC2_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_NO                  0x00000001
	u32 fwags;
	u32 fawcon_id;
};

stwuct nv_sec2_acw_bootstwap_fawcon_msg {
	stwuct nv_sec2_acw_msg msg;
	u32 ewwow_code;
	u32 fawcon_id;
};

#define NV_SEC2_UNIT_V2_INIT   0x01
#define NV_SEC2_UNIT_V2_UNWOAD 0x05
#define NV_SEC2_UNIT_V2_ACW    0x07

stwuct nv_sec2_acw_bootstwap_fawcon_cmd_v1 {
	stwuct nv_sec2_acw_cmd cmd;
#define NV_SEC2_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_YES                 0x00000000
#define NV_SEC2_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_NO                  0x00000001
	u32 fwags;
	u32 fawcon_id;
	u32 unkn08;
	u32 unkn0c;
};

stwuct nv_sec2_acw_bootstwap_fawcon_msg_v1 {
	stwuct nv_sec2_acw_msg msg;
	u32 ewwow_code;
	u32 fawcon_id;
	u32 unkn08;
};
#endif
