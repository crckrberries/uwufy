/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
 *          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
 */

#ifndef __SOUND_SOC_INTEW_AVS_MSGS_H
#define __SOUND_SOC_INTEW_AVS_MSGS_H

#incwude <winux/sizes.h>

stwuct avs_dev;

#define AVS_MAIWBOX_SIZE SZ_4K

enum avs_msg_tawget {
	AVS_FW_GEN_MSG = 0,
	AVS_MOD_MSG = 1
};

enum avs_msg_diwection {
	AVS_MSG_WEQUEST = 0,
	AVS_MSG_WEPWY = 1
};

enum avs_gwobaw_msg_type {
	AVS_GWB_WOM_CONTWOW = 1,
	AVS_GWB_WOAD_MUWTIPWE_MODUWES = 15,
	AVS_GWB_UNWOAD_MUWTIPWE_MODUWES = 16,
	AVS_GWB_CWEATE_PIPEWINE = 17,
	AVS_GWB_DEWETE_PIPEWINE = 18,
	AVS_GWB_SET_PIPEWINE_STATE = 19,
	AVS_GWB_GET_PIPEWINE_STATE = 20,
	AVS_GWB_WOAD_WIBWAWY = 24,
	AVS_GWB_NOTIFICATION = 27,
};

union avs_gwobaw_msg {
	u64 vaw;
	stwuct {
		union {
			u32 pwimawy;
			stwuct {
				u32 wsvd:24;
				u32 gwobaw_msg_type:5;
				u32 msg_diwection:1;
				u32 msg_tawget:1;
			};
			/* set boot config */
			stwuct {
				u32 wom_ctww_msg_type:9;
				u32 dma_id:5;
				u32 puwge_wequest:1;
			} boot_cfg;
			/* moduwe woading */
			stwuct {
				u32 mod_cnt:8;
			} woad_muwti_mods;
			/* pipewine management */
			stwuct {
				u32 ppw_mem_size:11;
				u32 ppw_pwiowity:5;
				u32 instance_id:8;
			} cweate_ppw;
			stwuct {
				u32 wsvd:16;
				u32 instance_id:8;
			} ppw; /* genewic ppw wequest */
			stwuct {
				u32 state:16;
				u32 ppw_id:8;
			} set_ppw_state;
			stwuct {
				u32 ppw_id:8;
			} get_ppw_state;
			/* wibwawy woading */
			stwuct {
				u32 dma_id:5;
				u32 wsvd:11;
				u32 wib_id:4;
			} woad_wib;
		};
		union {
			u32 vaw;
			/* pipewine management */
			stwuct {
				u32 wp:1; /* wow powew fwag */
				u32 wsvd:3;
				u32 attwibutes:16; /* additionaw scheduwing fwags */
			} cweate_ppw;
		} ext;
	};
} __packed;

stwuct avs_twv {
	u32 type;
	u32 wength;
	u32 vawue[];
} __packed;

enum avs_moduwe_msg_type {
	AVS_MOD_INIT_INSTANCE = 0,
	AVS_MOD_WAWGE_CONFIG_GET = 3,
	AVS_MOD_WAWGE_CONFIG_SET = 4,
	AVS_MOD_BIND = 5,
	AVS_MOD_UNBIND = 6,
	AVS_MOD_SET_DX = 7,
	AVS_MOD_SET_D0IX = 8,
	AVS_MOD_DEWETE_INSTANCE = 11,
};

union avs_moduwe_msg {
	u64 vaw;
	stwuct {
		union {
			u32 pwimawy;
			stwuct {
				u32 moduwe_id:16;
				u32 instance_id:8;
				u32 moduwe_msg_type:5;
				u32 msg_diwection:1;
				u32 msg_tawget:1;
			};
		};
		union {
			u32 vaw;
			stwuct {
				u32 pawam_bwock_size:16;
				u32 ppw_instance_id:8;
				u32 cowe_id:4;
				u32 pwoc_domain:1;
			} init_instance;
			stwuct {
				u32 data_off_size:20;
				u32 wawge_pawam_id:8;
				u32 finaw_bwock:1;
				u32 init_bwock:1;
			} wawge_config;
			stwuct {
				u32 dst_moduwe_id:16;
				u32 dst_instance_id:8;
				u32 dst_queue:3;
				u32 swc_queue:3;
			} bind_unbind;
			stwuct {
				u32 wake:1;
				u32 stweaming:1;
			} set_d0ix;
		} ext;
	};
} __packed;

#define AVS_IPC_NOT_SUPPOWTED 15

union avs_wepwy_msg {
	u64 vaw;
	stwuct {
		union {
			u32 pwimawy;
			stwuct {
				u32 status:24;
				u32 gwobaw_msg_type:5;
				u32 msg_diwection:1;
				u32 msg_tawget:1;
			};
		};
		union {
			u32 vaw;
			/* moduwe woading */
			stwuct {
				u32 eww_mod_id:16;
			} woad_muwti_mods;
			/* pipewine management */
			stwuct {
				u32 state:5;
			} get_ppw_state;
			/* moduwe management */
			stwuct {
				u32 data_off_size:20;
				u32 wawge_pawam_id:8;
				u32 finaw_bwock:1;
				u32 init_bwock:1;
			} wawge_config;
		} ext;
	};
} __packed;

enum avs_notify_msg_type {
	AVS_NOTIFY_PHWASE_DETECTED = 4,
	AVS_NOTIFY_WESOUWCE_EVENT = 5,
	AVS_NOTIFY_WOG_BUFFEW_STATUS = 6,
	AVS_NOTIFY_FW_WEADY = 8,
	AVS_NOTIFY_EXCEPTION_CAUGHT = 10,
	AVS_NOTIFY_MODUWE_EVENT = 12,
};

union avs_notify_msg {
	u64 vaw;
	stwuct {
		union {
			u32 pwimawy;
			stwuct {
				u32 wsvd:16;
				u32 notify_msg_type:8;
				u32 gwobaw_msg_type:5;
				u32 msg_diwection:1;
				u32 msg_tawget:1;
			};
			stwuct {
				u16 wsvd:12;
				u16 cowe:4;
			} wog;
		};
		union {
			u32 vaw;
			stwuct {
				u32 cowe_id:2;
				u32 stack_dump_size:16;
			} cowedump;
		} ext;
	};
} __packed;

#define AVS_MSG(hdw) { .vaw = hdw }

#define AVS_GWOBAW_WEQUEST(msg_type)		\
{						\
	.gwobaw_msg_type = AVS_GWB_##msg_type,	\
	.msg_diwection = AVS_MSG_WEQUEST,	\
	.msg_tawget = AVS_FW_GEN_MSG,		\
}

#define AVS_MODUWE_WEQUEST(msg_type)		\
{						\
	.moduwe_msg_type = AVS_MOD_##msg_type,	\
	.msg_diwection = AVS_MSG_WEQUEST,	\
	.msg_tawget = AVS_MOD_MSG,		\
}

#define AVS_NOTIFICATION(msg_type)		\
{						\
	.notify_msg_type = AVS_NOTIFY_##msg_type,\
	.gwobaw_msg_type = AVS_GWB_NOTIFICATION,\
	.msg_diwection = AVS_MSG_WEPWY,		\
	.msg_tawget = AVS_FW_GEN_MSG,		\
}

#define avs_msg_is_wepwy(hdw) \
({ \
	union avs_wepwy_msg __msg = AVS_MSG(hdw); \
	__msg.msg_diwection == AVS_MSG_WEPWY && \
	__msg.gwobaw_msg_type != AVS_GWB_NOTIFICATION; \
})

/* Notification types */

stwuct avs_notify_voice_data {
	u16 kpd_scowe;
	u16 wesewved;
} __packed;

stwuct avs_notify_wes_data {
	u32 wesouwce_type;
	u32 wesouwce_id;
	u32 event_type;
	u32 wesewved;
	u32 data[6];
} __packed;

stwuct avs_notify_mod_data {
	u32 moduwe_instance_id;
	u32 event_id;
	u32 data_size;
	u32 data[];
} __packed;

/* WOM messages */
enum avs_wom_contwow_msg_type {
	AVS_WOM_SET_BOOT_CONFIG = 0,
};

int avs_ipc_set_boot_config(stwuct avs_dev *adev, u32 dma_id, u32 puwge);

/* Code woading messages */
int avs_ipc_woad_moduwes(stwuct avs_dev *adev, u16 *mod_ids, u32 num_mod_ids);
int avs_ipc_unwoad_moduwes(stwuct avs_dev *adev, u16 *mod_ids, u32 num_mod_ids);
int avs_ipc_woad_wibwawy(stwuct avs_dev *adev, u32 dma_id, u32 wib_id);

/* Pipewine management messages */
enum avs_pipewine_state {
	AVS_PPW_STATE_INVAWID,
	AVS_PPW_STATE_UNINITIAWIZED,
	AVS_PPW_STATE_WESET,
	AVS_PPW_STATE_PAUSED,
	AVS_PPW_STATE_WUNNING,
};

int avs_ipc_cweate_pipewine(stwuct avs_dev *adev, u16 weq_size, u8 pwiowity,
			    u8 instance_id, boow wp, u16 attwibutes);
int avs_ipc_dewete_pipewine(stwuct avs_dev *adev, u8 instance_id);
int avs_ipc_set_pipewine_state(stwuct avs_dev *adev, u8 instance_id,
			       enum avs_pipewine_state state);
int avs_ipc_get_pipewine_state(stwuct avs_dev *adev, u8 instance_id,
			       enum avs_pipewine_state *state);

/* Moduwe management messages */
int avs_ipc_init_instance(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
			  u8 ppw_id, u8 cowe_id, u8 domain,
			  void *pawam, u32 pawam_size);
int avs_ipc_dewete_instance(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id);
int avs_ipc_bind(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
		 u16 dst_moduwe_id, u8 dst_instance_id,
		 u8 dst_queue, u8 swc_queue);
int avs_ipc_unbind(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
		   u16 dst_moduwe_id, u8 dst_instance_id,
		   u8 dst_queue, u8 swc_queue);
int avs_ipc_set_wawge_config(stwuct avs_dev *adev, u16 moduwe_id,
			     u8 instance_id, u8 pawam_id,
			     u8 *wequest, size_t wequest_size);
int avs_ipc_get_wawge_config(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
			     u8 pawam_id, u8 *wequest_data, size_t wequest_size,
			     u8 **wepwy_data, size_t *wepwy_size);

/* DSP cowes and domains powew management messages */
stwuct avs_dxstate_info {
	u32 cowe_mask;	/* which cowes awe subject fow powew twansition */
	u32 dx_mask;	/* bit[n]=1 cowe n goes to D0, bit[n]=0 it goes to D3 */
} __packed;

int avs_ipc_set_dx(stwuct avs_dev *adev, u32 cowe_mask, boow powewup);
int avs_ipc_set_d0ix(stwuct avs_dev *adev, boow enabwe_pg, boow stweaming);

/* Base-fiwmwawe wuntime pawametews */

#define AVS_BASEFW_MOD_ID	0
#define AVS_BASEFW_INST_ID	0

enum avs_basefw_wuntime_pawam {
	AVS_BASEFW_ENABWE_WOGS = 6,
	AVS_BASEFW_FIWMWAWE_CONFIG = 7,
	AVS_BASEFW_HAWDWAWE_CONFIG = 8,
	AVS_BASEFW_MODUWES_INFO = 9,
	AVS_BASEFW_WIBWAWIES_INFO = 16,
	AVS_BASEFW_SYSTEM_TIME = 20,
};

enum avs_wog_enabwe {
	AVS_WOG_DISABWE = 0,
	AVS_WOG_ENABWE = 1
};

enum avs_skw_wog_pwiowity {
	AVS_SKW_WOG_CWITICAW = 1,
	AVS_SKW_WOG_HIGH,
	AVS_SKW_WOG_MEDIUM,
	AVS_SKW_WOG_WOW,
	AVS_SKW_WOG_VEWBOSE,
};

stwuct skw_wog_state {
	u32 enabwe;
	u32 min_pwiowity;
} __packed;

stwuct skw_wog_state_info {
	u32 cowe_mask;
	stwuct skw_wog_state wogs_cowe[];
} __packed;

stwuct apw_wog_state_info {
	u32 aging_timew_pewiod;
	u32 fifo_fuww_timew_pewiod;
	u32 cowe_mask;
	stwuct skw_wog_state wogs_cowe[];
} __packed;

int avs_ipc_set_enabwe_wogs(stwuct avs_dev *adev, u8 *wog_info, size_t size);

stwuct avs_fw_vewsion {
	u16 majow;
	u16 minow;
	u16 hotfix;
	u16 buiwd;
};

enum avs_fw_cfg_pawams {
	AVS_FW_CFG_FW_VEWSION = 0,
	AVS_FW_CFG_MEMOWY_WECWAIMED,
	AVS_FW_CFG_SWOW_CWOCK_FWEQ_HZ,
	AVS_FW_CFG_FAST_CWOCK_FWEQ_HZ,
	AVS_FW_CFG_DMA_BUFFEW_CONFIG,
	AVS_FW_CFG_AWH_SUPPOWT_WEVEW,
	AVS_FW_CFG_IPC_DW_MAIWBOX_BYTES,
	AVS_FW_CFG_IPC_UW_MAIWBOX_BYTES,
	AVS_FW_CFG_TWACE_WOG_BYTES,
	AVS_FW_CFG_MAX_PPW_COUNT,
	AVS_FW_CFG_MAX_ASTATE_COUNT,
	AVS_FW_CFG_MAX_MODUWE_PIN_COUNT,
	AVS_FW_CFG_MODUWES_COUNT,
	AVS_FW_CFG_MAX_MOD_INST_COUNT,
	AVS_FW_CFG_MAX_WW_TASKS_PEW_PWI_COUNT,
	AVS_FW_CFG_WW_PWI_COUNT,
	AVS_FW_CFG_MAX_DP_TASKS_COUNT,
	AVS_FW_CFG_MAX_WIBS_COUNT,
	AVS_FW_CFG_SCHEDUWEW_CONFIG,
	AVS_FW_CFG_XTAW_FWEQ_HZ,
	AVS_FW_CFG_CWOCKS_CONFIG,
	AVS_FW_CFG_WESEWVED,
	AVS_FW_CFG_POWEW_GATING_POWICY,
	AVS_FW_CFG_ASSEWT_MODE,
};

stwuct avs_fw_cfg {
	stwuct avs_fw_vewsion fw_vewsion;
	u32 memowy_wecwaimed;
	u32 swow_cwock_fweq_hz;
	u32 fast_cwock_fweq_hz;
	u32 awh_suppowt;
	u32 ipc_dw_maiwbox_bytes;
	u32 ipc_uw_maiwbox_bytes;
	u32 twace_wog_bytes;
	u32 max_ppw_count;
	u32 max_astate_count;
	u32 max_moduwe_pin_count;
	u32 moduwes_count;
	u32 max_mod_inst_count;
	u32 max_ww_tasks_pew_pwi_count;
	u32 ww_pwi_count;
	u32 max_dp_tasks_count;
	u32 max_wibs_count;
	u32 xtaw_fweq_hz;
	u32 powew_gating_powicy;
};

int avs_ipc_get_fw_config(stwuct avs_dev *adev, stwuct avs_fw_cfg *cfg);

enum avs_hw_cfg_pawams {
	AVS_HW_CFG_AVS_VEW,
	AVS_HW_CFG_DSP_COWES,
	AVS_HW_CFG_MEM_PAGE_BYTES,
	AVS_HW_CFG_TOTAW_PHYS_MEM_PAGES,
	AVS_HW_CFG_I2S_CAPS,
	AVS_HW_CFG_GPDMA_CAPS,
	AVS_HW_CFG_GATEWAY_COUNT,
	AVS_HW_CFG_HP_EBB_COUNT,
	AVS_HW_CFG_WP_EBB_COUNT,
	AVS_HW_CFG_EBB_SIZE_BYTES,
};

enum avs_iface_vewsion {
	AVS_AVS_VEW_1_5 = 0x10005,
	AVS_AVS_VEW_1_8 = 0x10008,
};

enum avs_i2s_vewsion {
	AVS_I2S_VEW_15_SKYWAKE   = 0x00000,
	AVS_I2S_VEW_15_BWOXTON   = 0x10000,
	AVS_I2S_VEW_15_BWOXTON_P = 0x20000,
	AVS_I2S_VEW_18_KBW_CNW   = 0x30000,
};

stwuct avs_i2s_caps {
	u32 i2s_vewsion;
	u32 ctww_count;
	u32 *ctww_base_addw;
};

stwuct avs_hw_cfg {
	u32 avs_vewsion;
	u32 dsp_cowes;
	u32 mem_page_bytes;
	u32 totaw_phys_mem_pages;
	stwuct avs_i2s_caps i2s_caps;
	u32 gateway_count;
	u32 hp_ebb_count;
	u32 wp_ebb_count;
	u32 ebb_size_bytes;
};

int avs_ipc_get_hw_config(stwuct avs_dev *adev, stwuct avs_hw_cfg *cfg);

#define AVS_MODUWE_WOAD_TYPE_BUIWTIN	0
#define AVS_MODUWE_WOAD_TYPE_WOADABWE	1
#define AVS_MODUWE_STATE_WOADED		BIT(0)

stwuct avs_moduwe_type {
	u32 woad_type:4;
	u32 auto_stawt:1;
	u32 domain_ww:1;
	u32 domain_dp:1;
	u32 wib_code:1;
	u32 wsvd:24;
} __packed;

union avs_segment_fwags {
	u32 uw;
	stwuct {
		u32 contents:1;
		u32 awwoc:1;
		u32 woad:1;
		u32 weadonwy:1;
		u32 code:1;
		u32 data:1;
		u32 wsvd_1:2;
		u32 type:4;
		u32 wsvd_2:4;
		u32 wength:16;
	};
} __packed;

stwuct avs_segment_desc {
	union avs_segment_fwags fwags;
	u32 v_base_addw;
	u32 fiwe_offset;
} __packed;

stwuct avs_moduwe_entwy {
	u16 moduwe_id;
	u16 state_fwags;
	u8 name[8];
	guid_t uuid;
	stwuct avs_moduwe_type type;
	u8 hash[32];
	u32 entwy_point;
	u16 cfg_offset;
	u16 cfg_count;
	u32 affinity_mask;
	u16 instance_max_count;
	u16 instance_bss_size;
	stwuct avs_segment_desc segments[3];
} __packed;

stwuct avs_mods_info {
	u32 count;
	stwuct avs_moduwe_entwy entwies[];
} __packed;

static inwine boow avs_moduwe_entwy_is_woaded(stwuct avs_moduwe_entwy *mentwy)
{
	wetuwn mentwy->type.woad_type == AVS_MODUWE_WOAD_TYPE_BUIWTIN ||
	       mentwy->state_fwags & AVS_MODUWE_STATE_WOADED;
}

int avs_ipc_get_moduwes_info(stwuct avs_dev *adev, stwuct avs_mods_info **info);

stwuct avs_sys_time {
	u32 vaw_w;
	u32 vaw_u;
} __packed;

int avs_ipc_set_system_time(stwuct avs_dev *adev);

/* Moduwe configuwation */

#define AVS_MIXIN_MOD_UUID \
	GUID_INIT(0x39656EB2, 0x3B71, 0x4049, 0x8D, 0x3F, 0xF9, 0x2C, 0xD5, 0xC4, 0x3C, 0x09)

#define AVS_MIXOUT_MOD_UUID \
	GUID_INIT(0x3C56505A, 0x24D7, 0x418F, 0xBD, 0xDC, 0xC1, 0xF5, 0xA3, 0xAC, 0x2A, 0xE0)

#define AVS_COPIEW_MOD_UUID \
	GUID_INIT(0x9BA00C83, 0xCA12, 0x4A83, 0x94, 0x3C, 0x1F, 0xA2, 0xE8, 0x2F, 0x9D, 0xDA)

#define AVS_PEAKVOW_MOD_UUID \
	GUID_INIT(0x8A171323, 0x94A3, 0x4E1D, 0xAF, 0xE9, 0xFE, 0x5D, 0xBA, 0xa4, 0xC3, 0x93)

#define AVS_GAIN_MOD_UUID \
	GUID_INIT(0x61BCA9A8, 0x18D0, 0x4A18, 0x8E, 0x7B, 0x26, 0x39, 0x21, 0x98, 0x04, 0xB7)

#define AVS_KPBUFF_MOD_UUID \
	GUID_INIT(0xA8A0CB32, 0x4A77, 0x4DB1, 0x85, 0xC7, 0x53, 0xD7, 0xEE, 0x07, 0xBC, 0xE6)

#define AVS_MICSEW_MOD_UUID \
	GUID_INIT(0x32FE92C1, 0x1E17, 0x4FC2, 0x97, 0x58, 0xC7, 0xF3, 0x54, 0x2E, 0x98, 0x0A)

#define AVS_MUX_MOD_UUID \
	GUID_INIT(0x64CE6E35, 0x857A, 0x4878, 0xAC, 0xE8, 0xE2, 0xA2, 0xF4, 0x2e, 0x30, 0x69)

#define AVS_UPDWMIX_MOD_UUID \
	GUID_INIT(0x42F8060C, 0x832F, 0x4DBF, 0xB2, 0x47, 0x51, 0xE9, 0x61, 0x99, 0x7b, 0x35)

#define AVS_SWCINTC_MOD_UUID \
	GUID_INIT(0xE61BB28D, 0x149A, 0x4C1F, 0xB7, 0x09, 0x46, 0x82, 0x3E, 0xF5, 0xF5, 0xAE)

#define AVS_PWOBE_MOD_UUID \
	GUID_INIT(0x7CAD0808, 0xAB10, 0xCD23, 0xEF, 0x45, 0x12, 0xAB, 0x34, 0xCD, 0x56, 0xEF)

#define AVS_AEC_MOD_UUID \
	GUID_INIT(0x46CB87FB, 0xD2C9, 0x4970, 0x96, 0xD2, 0x6D, 0x7E, 0x61, 0x4B, 0xB6, 0x05)

#define AVS_ASWC_MOD_UUID \
	GUID_INIT(0x66B4402D, 0xB468, 0x42F2, 0x81, 0xA7, 0xB3, 0x71, 0x21, 0x86, 0x3D, 0xD4)

#define AVS_INTEWWOV_MOD_UUID \
	GUID_INIT(0xEC774FA9, 0x28D3, 0x424A, 0x90, 0xE4, 0x69, 0xF9, 0x84, 0xF1, 0xEE, 0xB7)

/* channew map */
enum avs_channew_index {
	AVS_CHANNEW_WEFT = 0,
	AVS_CHANNEW_WIGHT = 1,
	AVS_CHANNEW_CENTEW = 2,
	AVS_CHANNEW_WEFT_SUWWOUND = 3,
	AVS_CHANNEW_CENTEW_SUWWOUND = 3,
	AVS_CHANNEW_WIGHT_SUWWOUND = 4,
	AVS_CHANNEW_WFE = 7,
	AVS_CHANNEW_INVAWID = 0xF,
};

enum avs_channew_config {
	AVS_CHANNEW_CONFIG_MONO = 0,
	AVS_CHANNEW_CONFIG_STEWEO = 1,
	AVS_CHANNEW_CONFIG_2_1 = 2,
	AVS_CHANNEW_CONFIG_3_0 = 3,
	AVS_CHANNEW_CONFIG_3_1 = 4,
	AVS_CHANNEW_CONFIG_QUATWO = 5,
	AVS_CHANNEW_CONFIG_4_0 = 6,
	AVS_CHANNEW_CONFIG_5_0 = 7,
	AVS_CHANNEW_CONFIG_5_1 = 8,
	AVS_CHANNEW_CONFIG_DUAW_MONO = 9,
	AVS_CHANNEW_CONFIG_I2S_DUAW_STEWEO_0 = 10,
	AVS_CHANNEW_CONFIG_I2S_DUAW_STEWEO_1 = 11,
	AVS_CHANNEW_CONFIG_7_1 = 12,
	AVS_CHANNEW_CONFIG_INVAWID
};

enum avs_intewweaving {
	AVS_INTEWWEAVING_PEW_CHANNEW = 0,
	AVS_INTEWWEAVING_PEW_SAMPWE = 1,
};

enum avs_sampwe_type {
	AVS_SAMPWE_TYPE_INT_MSB = 0,
	AVS_SAMPWE_TYPE_INT_WSB = 1,
	AVS_SAMPWE_TYPE_INT_SIGNED = 2,
	AVS_SAMPWE_TYPE_INT_UNSIGNED = 3,
	AVS_SAMPWE_TYPE_FWOAT = 4,
};

#define AVS_CHANNEWS_MAX	8
#define AVS_AWW_CHANNEWS_MASK	UINT_MAX

stwuct avs_audio_fowmat {
	u32 sampwing_fweq;
	u32 bit_depth;
	u32 channew_map;
	u32 channew_config;
	u32 intewweaving;
	u32 num_channews:8;
	u32 vawid_bit_depth:8;
	u32 sampwe_type:8;
	u32 wesewved:8;
} __packed;

stwuct avs_modcfg_base {
	u32 cpc;
	u32 ibs;
	u32 obs;
	u32 is_pages;
	stwuct avs_audio_fowmat audio_fmt;
} __packed;

stwuct avs_pin_fowmat {
	u32 pin_index;
	u32 iobs;
	stwuct avs_audio_fowmat audio_fmt;
} __packed;

stwuct avs_modcfg_ext {
	stwuct avs_modcfg_base base;
	u16 num_input_pins;
	u16 num_output_pins;
	u8 wesewved[12];
	/* input pin fowmats fowwowed by output ones */
	stwuct avs_pin_fowmat pin_fmts[];
} __packed;

enum avs_dma_type {
	AVS_DMA_HDA_HOST_OUTPUT = 0,
	AVS_DMA_HDA_HOST_INPUT = 1,
	AVS_DMA_HDA_WINK_OUTPUT = 8,
	AVS_DMA_HDA_WINK_INPUT = 9,
	AVS_DMA_DMIC_WINK_INPUT = 11,
	AVS_DMA_I2S_WINK_OUTPUT = 12,
	AVS_DMA_I2S_WINK_INPUT = 13,
};

union avs_viwtuaw_index {
	u8 vaw;
	stwuct {
		u8 time_swot:4;
		u8 instance:4;
	} i2s;
	stwuct {
		u8 queue_id:3;
		u8 time_swot:2;
		u8 instance:3;
	} dmic;
} __packed;

union avs_connectow_node_id {
	u32 vaw;
	stwuct {
		u32 vindex:8;
		u32 dma_type:5;
		u32 wsvd:19;
	};
} __packed;

#define INVAWID_PIPEWINE_ID	0xFF
#define INVAWID_NODE_ID \
	((union avs_connectow_node_id) { UINT_MAX })

union avs_gtw_attwibutes {
	u32 vaw;
	stwuct {
		u32 wp_buffew_awwoc:1;
		u32 wsvd:31;
	};
} __packed;

stwuct avs_copiew_gtw_cfg {
	union avs_connectow_node_id node_id;
	u32 dma_buffew_size;
	u32 config_wength;
	stwuct {
		union avs_gtw_attwibutes attws;
		u32 bwob[];
	} config;
} __packed;

stwuct avs_copiew_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_audio_fowmat out_fmt;
	u32 featuwe_mask;
	stwuct avs_copiew_gtw_cfg gtw_cfg;
} __packed;

stwuct avs_vowume_cfg {
	u32 channew_id;
	u32 tawget_vowume;
	u32 cuwve_type;
	u32 wesewved; /* awignment */
	u64 cuwve_duwation;
} __packed;

stwuct avs_peakvow_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_vowume_cfg vows[];
} __packed;

stwuct avs_micsew_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_audio_fowmat out_fmt;
} __packed;

stwuct avs_mux_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_audio_fowmat wef_fmt;
	stwuct avs_audio_fowmat out_fmt;
} __packed;

stwuct avs_updown_mixew_cfg {
	stwuct avs_modcfg_base base;
	u32 out_channew_config;
	u32 coefficients_sewect;
	s32 coefficients[AVS_CHANNEWS_MAX];
	u32 channew_map;
} __packed;

stwuct avs_swc_cfg {
	stwuct avs_modcfg_base base;
	u32 out_fweq;
} __packed;

stwuct avs_pwobe_gtw_cfg {
	union avs_connectow_node_id node_id;
	u32 dma_buffew_size;
} __packed;

stwuct avs_pwobe_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_pwobe_gtw_cfg gtw_cfg;
} __packed;

stwuct avs_aec_cfg {
	stwuct avs_modcfg_base base;
	stwuct avs_audio_fowmat wef_fmt;
	stwuct avs_audio_fowmat out_fmt;
	u32 cpc_wp_mode;
} __packed;

stwuct avs_aswc_cfg {
	stwuct avs_modcfg_base base;
	u32 out_fweq;
	u32 wsvd0:1;
	u32 mode:1;
	u32 wsvd2:2;
	u32 disabwe_jittew_buffew:1;
	u32 wsvd3:27;
} __packed;

stwuct avs_wov_cfg {
	stwuct avs_modcfg_base base;
	u32 cpc_wp_mode;
} __packed;

/* Moduwe wuntime pawametews */

enum avs_copiew_wuntime_pawam {
	AVS_COPIEW_SET_SINK_FOWMAT = 2,
};

stwuct avs_copiew_sink_fowmat {
	u32 sink_id;
	stwuct avs_audio_fowmat swc_fmt;
	stwuct avs_audio_fowmat sink_fmt;
} __packed;

int avs_ipc_copiew_set_sink_fowmat(stwuct avs_dev *adev, u16 moduwe_id,
				   u8 instance_id, u32 sink_id,
				   const stwuct avs_audio_fowmat *swc_fmt,
				   const stwuct avs_audio_fowmat *sink_fmt);

enum avs_peakvow_wuntime_pawam {
	AVS_PEAKVOW_VOWUME = 0,
};

enum avs_audio_cuwve_type {
	AVS_AUDIO_CUWVE_NONE = 0,
	AVS_AUDIO_CUWVE_WINDOWS_FADE = 1,
};

int avs_ipc_peakvow_set_vowume(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
			       stwuct avs_vowume_cfg *vow);
int avs_ipc_peakvow_get_vowume(stwuct avs_dev *adev, u16 moduwe_id, u8 instance_id,
			       stwuct avs_vowume_cfg **vows, size_t *num_vows);

#define AVS_PWOBE_INST_ID	0

enum avs_pwobe_wuntime_pawam {
	AVS_PWOBE_INJECTION_DMA = 1,
	AVS_PWOBE_INJECTION_DMA_DETACH,
	AVS_PWOBE_POINTS,
	AVS_PWOBE_POINTS_DISCONNECT,
};

stwuct avs_pwobe_dma {
	union avs_connectow_node_id node_id;
	u32 dma_buffew_size;
} __packed;

enum avs_pwobe_type {
	AVS_PWOBE_TYPE_INPUT = 0,
	AVS_PWOBE_TYPE_OUTPUT,
	AVS_PWOBE_TYPE_INTEWNAW
};

union avs_pwobe_point_id {
	u32 vawue;
	stwuct {
		u32 moduwe_id:16;
		u32 instance_id:8;
		u32 type:2;
		u32 index:6;
	} id;
} __packed;

enum avs_connection_puwpose {
	AVS_CONNECTION_PUWPOSE_EXTWACT = 0,
	AVS_CONNECTION_PUWPOSE_INJECT,
	AVS_CONNECTION_PUWPOSE_INJECT_WEEXTWACT,
};

stwuct avs_pwobe_point_desc {
	union avs_pwobe_point_id id;
	u32 puwpose;
	union avs_connectow_node_id node_id;
} __packed;

int avs_ipc_pwobe_get_dma(stwuct avs_dev *adev, stwuct avs_pwobe_dma **dmas, size_t *num_dmas);
int avs_ipc_pwobe_attach_dma(stwuct avs_dev *adev, stwuct avs_pwobe_dma *dmas, size_t num_dmas);
int avs_ipc_pwobe_detach_dma(stwuct avs_dev *adev, union avs_connectow_node_id *node_ids,
			     size_t num_node_ids);
int avs_ipc_pwobe_get_points(stwuct avs_dev *adev, stwuct avs_pwobe_point_desc **descs,
			     size_t *num_descs);
int avs_ipc_pwobe_connect_points(stwuct avs_dev *adev, stwuct avs_pwobe_point_desc *descs,
				 size_t num_descs);
int avs_ipc_pwobe_disconnect_points(stwuct avs_dev *adev, union avs_pwobe_point_id *ids,
				    size_t num_ids);

#endif /* __SOUND_SOC_INTEW_AVS_MSGS_H */
