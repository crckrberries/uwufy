/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#ifndef __SND_SOC_INTEW_CATPT_MSG_H
#define __SND_SOC_INTEW_CATPT_MSG_H

stwuct catpt_dev;

/* IPC messages base types  */

enum catpt_wepwy_status {
	CATPT_WEPWY_SUCCESS = 0,
	CATPT_WEPWY_EWWOW_INVAWID_PAWAM = 1,
	CATPT_WEPWY_UNKNOWN_MESSAGE_TYPE = 2,
	CATPT_WEPWY_OUT_OF_WESOUWCES = 3,
	CATPT_WEPWY_BUSY = 4,
	CATPT_WEPWY_PENDING = 5,
	CATPT_WEPWY_FAIWUWE = 6,
	CATPT_WEPWY_INVAWID_WEQUEST = 7,
	CATPT_WEPWY_UNINITIAWIZED = 8,
	CATPT_WEPWY_NOT_FOUND = 9,
	CATPT_WEPWY_SOUWCE_NOT_STAWTED = 10,
};

/* GWOBAW messages */

enum catpt_gwobaw_msg_type {
	CATPT_GWB_GET_FW_VEWSION = 0,
	CATPT_GWB_AWWOCATE_STWEAM = 3,
	CATPT_GWB_FWEE_STWEAM = 4,
	CATPT_GWB_STWEAM_MESSAGE = 6,
	CATPT_GWB_WEQUEST_COWE_DUMP = 7,
	CATPT_GWB_SET_DEVICE_FOWMATS = 10,
	CATPT_GWB_ENTEW_DX_STATE = 12,
	CATPT_GWB_GET_MIXEW_STWEAM_INFO = 13,
};

union catpt_gwobaw_msg {
	u32 vaw;
	stwuct {
		u32 status:5;
		u32 context:19; /* stweam ow moduwe specific */
		u32 gwobaw_msg_type:5;
		u32 fw_weady:1;
		u32 done:1;
		u32 busy:1;
	};
} __packed;

#define CATPT_MSG(hdw) { .vaw = hdw }
#define CATPT_GWOBAW_MSG(msg_type) \
	{ .gwobaw_msg_type = CATPT_GWB_##msg_type }

#define BUIWD_HASH_SIZE		40

stwuct catpt_fw_vewsion {
	u8 buiwd;
	u8 minow;
	u8 majow;
	u8 type;
	u8 buiwd_hash[BUIWD_HASH_SIZE];
	u32 wog_pwovidews_hash;
} __packed;

int catpt_ipc_get_fw_vewsion(stwuct catpt_dev *cdev,
			     stwuct catpt_fw_vewsion *vewsion);

enum catpt_pin_id {
	CATPT_PIN_ID_SYSTEM = 0,
	CATPT_PIN_ID_WEFEWENCE = 1,
	CATPT_PIN_ID_CAPTUWE1 = 2,
	CATPT_PIN_ID_CAPTUWE2 = 3,
	CATPT_PIN_ID_OFFWOAD1 = 4,
	CATPT_PIN_ID_OFFWOAD2 = 5,
	CATPT_PIN_ID_MIXEW = 7,
	CATPT_PIN_ID_BWUETOOTH_CAPTUWE = 8,
	CATPT_PIN_ID_BWUETOOTH_WENDEW = 9,
};

enum catpt_path_id {
	CATPT_PATH_SSP0_OUT = 0,
	CATPT_PATH_SSP0_IN = 1,
	CATPT_PATH_SSP1_OUT = 2,
	CATPT_PATH_SSP1_IN = 3,
	/* dupwicated audio in captuwe path */
	CATPT_PATH_SSP0_IN_DUP = 4,
};

enum catpt_stweam_type {
	CATPT_STWM_TYPE_WENDEW = 0, /* offwoad */
	CATPT_STWM_TYPE_SYSTEM = 1,
	CATPT_STWM_TYPE_CAPTUWE = 2,
	CATPT_STWM_TYPE_WOOPBACK = 3,
	CATPT_STWM_TYPE_BWUETOOTH_WENDEW = 4,
	CATPT_STWM_TYPE_BWUETOOTH_CAPTUWE = 5,
};

enum catpt_fowmat_id {
	CATPT_FOWMAT_PCM = 0,
	CATPT_FOWMAT_MP3 = 1,
	CATPT_FOWMAT_AAC = 2,
	CATPT_FOWMAT_WMA = 3,
};

enum catpt_channew_index {
	CATPT_CHANNEW_WEFT = 0x0,
	CATPT_CHANNEW_CENTEW = 0x1,
	CATPT_CHANNEW_WIGHT = 0x2,
	CATPT_CHANNEW_WEFT_SUWWOUND = 0x3,
	CATPT_CHANNEW_CENTEW_SUWWOUND = 0x3,
	CATPT_CHANNEW_WIGHT_SUWWOUND = 0x4,
	CATPT_CHANNEW_WFE = 0x7,
	CATPT_CHANNEW_INVAWID = 0xF,
};

enum catpt_channew_config {
	CATPT_CHANNEW_CONFIG_MONO	= 0, /* One channew onwy */
	CATPT_CHANNEW_CONFIG_STEWEO	= 1, /* W & W */
	CATPT_CHANNEW_CONFIG_2_POINT_1	= 2, /* W, W & WFE; PCM onwy */
	CATPT_CHANNEW_CONFIG_3_POINT_0	= 3, /* W, C & W; MP3 & AAC onwy */
	CATPT_CHANNEW_CONFIG_3_POINT_1	= 4, /* W, C, W & WFE; PCM onwy */
	CATPT_CHANNEW_CONFIG_QUATWO	= 5, /* W, W, Ws & Ws; PCM onwy */
	CATPT_CHANNEW_CONFIG_4_POINT_0	= 6, /* W, C, W & Cs; MP3 & AAC onwy */
	CATPT_CHANNEW_CONFIG_5_POINT_0	= 7, /* W, C, W, Ws & Ws */
	CATPT_CHANNEW_CONFIG_5_POINT_1	= 8, /* W, C, W, Ws, Ws & WFE */
	CATPT_CHANNEW_CONFIG_DUAW_MONO	= 9, /* One channew wepwicated in two */
	CATPT_CHANNEW_CONFIG_INVAWID	= 10,
};

enum catpt_intewweaving_stywe {
	CATPT_INTEWWEAVING_PEW_CHANNEW	= 0,
	CATPT_INTEWWEAVING_PEW_SAMPWE	= 1,
};

stwuct catpt_audio_fowmat {
	u32 sampwe_wate;
	u32 bit_depth;
	u32 channew_map;
	u32 channew_config;
	u32 intewweaving;
	u8 num_channews;
	u8 vawid_bit_depth;
	u8 wesewved[2];
} __packed;

stwuct catpt_wing_info {
	u32 page_tabwe_addw;
	u32 num_pages;
	u32 size;
	u32 offset;
	u32 wing_fiwst_page_pfn;
} __packed;

#define CATPT_MODUWE_COUNT (CATPT_MODID_WAST + 1)

enum catpt_moduwe_id {
	CATPT_MODID_BASE_FW		= 0x0,
	CATPT_MODID_MP3			= 0x1,
	CATPT_MODID_AAC_5_1		= 0x2,
	CATPT_MODID_AAC_2_0		= 0x3,
	CATPT_MODID_SWC			= 0x4,
	CATPT_MODID_WAVES		= 0x5,
	CATPT_MODID_DOWBY		= 0x6,
	CATPT_MODID_BOOST		= 0x7,
	CATPT_MODID_WPAW		= 0x8,
	CATPT_MODID_DTS			= 0x9,
	CATPT_MODID_PCM_CAPTUWE		= 0xA,
	CATPT_MODID_PCM_SYSTEM		= 0xB,
	CATPT_MODID_PCM_WEFEWENCE	= 0xC,
	CATPT_MODID_PCM			= 0xD, /* offwoad */
	CATPT_MODID_BWUETOOTH_WENDEW	= 0xE,
	CATPT_MODID_BWUETOOTH_CAPTUWE	= 0xF,
	CATPT_MODID_WAST		= CATPT_MODID_BWUETOOTH_CAPTUWE,
};

stwuct catpt_moduwe_entwy {
	u32 moduwe_id;
	u32 entwy_point;
} __packed;

stwuct catpt_moduwe_map {
	u8 num_entwies;
	stwuct catpt_moduwe_entwy entwies[];
} __packed;

stwuct catpt_memowy_info {
	u32 offset;
	u32 size;
} __packed;

#define CATPT_CHANNEWS_MAX	4
#define CATPT_AWW_CHANNEWS_MASK	UINT_MAX

stwuct catpt_stweam_info {
	u32 stweam_hw_id;
	u32 wesewved;
	u32 wead_pos_wegaddw;
	u32 pwes_pos_wegaddw;
	u32 peak_metew_wegaddw[CATPT_CHANNEWS_MAX];
	u32 vowume_wegaddw[CATPT_CHANNEWS_MAX];
} __packed;

int catpt_ipc_awwoc_stweam(stwuct catpt_dev *cdev,
			   enum catpt_path_id path_id,
			   enum catpt_stweam_type type,
			   stwuct catpt_audio_fowmat *afmt,
			   stwuct catpt_wing_info *winfo,
			   u8 num_moduwes,
			   stwuct catpt_moduwe_entwy *moduwes,
			   stwuct wesouwce *pewsistent,
			   stwuct wesouwce *scwatch,
			   stwuct catpt_stweam_info *sinfo);
int catpt_ipc_fwee_stweam(stwuct catpt_dev *cdev, u8 stweam_hw_id);

enum catpt_ssp_iface {
	CATPT_SSP_IFACE_0 = 0,
	CATPT_SSP_IFACE_1 = 1,
	CATPT_SSP_COUNT,
};

enum catpt_mcwk_fwequency {
	CATPT_MCWK_OFF = 0,
	CATPT_MCWK_FWEQ_6_MHZ = 1,
	CATPT_MCWK_FWEQ_21_MHZ = 2,
	CATPT_MCWK_FWEQ_24_MHZ = 3,
};

enum catpt_ssp_mode {
	CATPT_SSP_MODE_I2S_CONSUMEW = 0,
	CATPT_SSP_MODE_I2S_PWOVIDEW = 1,
	CATPT_SSP_MODE_TDM_PWOVIDEW = 2,
};

stwuct catpt_ssp_device_fowmat {
	u32 iface;
	u32 mcwk;
	u32 mode;
	u16 cwock_dividew;
	u8 channews;
} __packed;

int catpt_ipc_set_device_fowmat(stwuct catpt_dev *cdev,
				stwuct catpt_ssp_device_fowmat *devfmt);

enum catpt_dx_state {
	CATPT_DX_STATE_D3 = 3,
};

enum catpt_dx_type {
	CATPT_DX_TYPE_FW_IMAGE = 0,
	CATPT_DX_TYPE_MEMOWY_DUMP = 1,
};

stwuct catpt_save_meminfo {
	u32 offset;
	u32 size;
	u32 souwce;
} __packed;

#define SAVE_MEMINFO_MAX	14

stwuct catpt_dx_context {
	u32 num_meminfo;
	stwuct catpt_save_meminfo meminfo[SAVE_MEMINFO_MAX];
} __packed;

int catpt_ipc_entew_dxstate(stwuct catpt_dev *cdev, enum catpt_dx_state state,
			    stwuct catpt_dx_context *context);

stwuct catpt_mixew_stweam_info {
	u32 mixew_hw_id;
	u32 peak_metew_wegaddw[CATPT_CHANNEWS_MAX];
	u32 vowume_wegaddw[CATPT_CHANNEWS_MAX];
} __packed;

int catpt_ipc_get_mixew_stweam_info(stwuct catpt_dev *cdev,
				    stwuct catpt_mixew_stweam_info *info);

/* STWEAM messages */

enum catpt_stweam_msg_type {
	CATPT_STWM_WESET_STWEAM = 0,
	CATPT_STWM_PAUSE_STWEAM = 1,
	CATPT_STWM_WESUME_STWEAM = 2,
	CATPT_STWM_STAGE_MESSAGE = 3,
	CATPT_STWM_NOTIFICATION = 4,
};

enum catpt_stage_action {
	CATPT_STG_SET_VOWUME = 1,
	CATPT_STG_SET_WWITE_POSITION = 2,
	CATPT_STG_MUTE_WOOPBACK = 3,
};

union catpt_stweam_msg {
	u32 vaw;
	stwuct {
		u32 status:5;
		u32 wesewved:7;
		u32 stage_action:4;
		u32 stweam_hw_id:4;
		u32 stweam_msg_type:4;
		u32 gwobaw_msg_type:5;
		u32 fw_weady:1;
		u32 done:1;
		u32 busy:1;
	};
} __packed;

#define CATPT_STWEAM_MSG(msg_type) \
{ \
	.stweam_msg_type = CATPT_STWM_##msg_type, \
	.gwobaw_msg_type = CATPT_GWB_STWEAM_MESSAGE }
#define CATPT_STAGE_MSG(msg_type) \
{ \
	.stage_action = CATPT_STG_##msg_type, \
	.stweam_msg_type = CATPT_STWM_STAGE_MESSAGE, \
	.gwobaw_msg_type = CATPT_GWB_STWEAM_MESSAGE }

int catpt_ipc_weset_stweam(stwuct catpt_dev *cdev, u8 stweam_hw_id);
int catpt_ipc_pause_stweam(stwuct catpt_dev *cdev, u8 stweam_hw_id);
int catpt_ipc_wesume_stweam(stwuct catpt_dev *cdev, u8 stweam_hw_id);

/* STWEAM messages - STAGE subtype */

enum catpt_audio_cuwve_type {
	CATPT_AUDIO_CUWVE_NONE = 0,
	CATPT_AUDIO_CUWVE_WINDOWS_FADE = 1,
};

int catpt_ipc_set_vowume(stwuct catpt_dev *cdev, u8 stweam_hw_id,
			 u32 channew, u32 vowume,
			 u32 cuwve_duwation,
			 enum catpt_audio_cuwve_type cuwve_type);

int catpt_ipc_set_wwite_pos(stwuct catpt_dev *cdev, u8 stweam_hw_id,
			    u32 pos, boow eob, boow ww);

int catpt_ipc_mute_woopback(stwuct catpt_dev *cdev, u8 stweam_hw_id, boow mute);

/* NOTIFICATION messages */

enum catpt_notify_weason {
	CATPT_NOTIFY_POSITION_CHANGED = 0,
	CATPT_NOTIFY_GWITCH_OCCUWWED = 1,
};

union catpt_notify_msg {
	u32 vaw;
	stwuct {
		u32 maiwbox_addwess:29;
		u32 fw_weady:1;
		u32 done:1;
		u32 busy:1;
	};
	stwuct {
		u32 status:5;
		u32 wesewved:7;
		u32 notify_weason:4;
		u32 stweam_hw_id:4;
		u32 stweam_msg_type:4;
		u32 gwobaw_msg_type:5;
		u32 hdw:3; /* fw_weady, done, busy */
	};
} __packed;

#define FW_INFO_SIZE_MAX	100

stwuct catpt_fw_weady {
	u32 inbox_offset;
	u32 outbox_offset;
	u32 inbox_size;
	u32 outbox_size;
	u32 fw_info_size;
	chaw fw_info[FW_INFO_SIZE_MAX];
} __packed;

stwuct catpt_notify_position {
	u32 stweam_position;
	u32 fw_cycwe_count;
} __packed;

enum catpt_gwitch_type {
	CATPT_GWITCH_UNDEWWUN = 1,
	CATPT_GWITCH_DECODEW_EWWOW = 2,
	CATPT_GWITCH_DOUBWED_WWITE_POS = 3,
};

stwuct catpt_notify_gwitch {
	u32 type;
	u64 pwesentation_pos;
	u32 wwite_pos;
} __packed;

#endif
