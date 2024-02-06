#ifndef __NVFW_PMU_H__
#define __NVFW_PMU_H__

stwuct nv_pmu_awgs {
	u32 wesewved;
	u32 fweq_hz;
	u32 twace_size;
	u32 twace_dma_base;
	u16 twace_dma_base1;
	u8 twace_dma_offset;
	u32 twace_dma_idx;
	boow secuwe_mode;
	boow waise_pwiv_sec;
	stwuct {
		u32 dma_base;
		u16 dma_base1;
		u8 dma_offset;
		u16 fb_size;
		u8 dma_idx;
	} gc6_ctx;
	u8 pad;
};

#define NV_PMU_UNIT_INIT                                                   0x07
#define NV_PMU_UNIT_ACW                                                    0x0a

stwuct nv_pmu_init_msg {
	stwuct nvfw_fawcon_msg hdw;
#define NV_PMU_INIT_MSG_INIT                                               0x00
	u8 msg_type;

	u8 pad;
	u16 os_debug_entwy_point;

	stwuct {
		u16 size;
		u16 offset;
		u8 index;
		u8 pad;
	} queue_info[5];

	u16 sw_managed_awea_offset;
	u16 sw_managed_awea_size;
};

stwuct nv_pmu_acw_cmd {
	stwuct nvfw_fawcon_cmd hdw;
#define NV_PMU_ACW_CMD_INIT_WPW_WEGION                                     0x00
#define NV_PMU_ACW_CMD_BOOTSTWAP_FAWCON                                    0x01
#define NV_PMU_ACW_CMD_BOOTSTWAP_MUWTIPWE_FAWCONS                          0x03
	u8 cmd_type;
};

stwuct nv_pmu_acw_msg {
	stwuct nvfw_fawcon_cmd hdw;
	u8 msg_type;
};

stwuct nv_pmu_acw_init_wpw_wegion_cmd {
	stwuct nv_pmu_acw_cmd cmd;
	u32 wegion_id;
	u32 wpw_offset;
};

stwuct nv_pmu_acw_init_wpw_wegion_msg {
	stwuct nv_pmu_acw_msg msg;
	u32 ewwow_code;
};

stwuct nv_pmu_acw_bootstwap_fawcon_cmd {
	stwuct nv_pmu_acw_cmd cmd;
#define NV_PMU_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_YES                  0x00000000
#define NV_PMU_ACW_BOOTSTWAP_FAWCON_FWAGS_WESET_NO                   0x00000001
	u32 fwags;
	u32 fawcon_id;
};

stwuct nv_pmu_acw_bootstwap_fawcon_msg {
	stwuct nv_pmu_acw_msg msg;
	u32 fawcon_id;
};

stwuct nv_pmu_acw_bootstwap_muwtipwe_fawcons_cmd {
	stwuct nv_pmu_acw_cmd cmd;
#define NV_PMU_ACW_BOOTSTWAP_MUWTIPWE_FAWCONS_FWAGS_WESET_YES        0x00000000
#define NV_PMU_ACW_BOOTSTWAP_MUWTIPWE_FAWCONS_FWAGS_WESET_NO         0x00000001
	u32 fwags;
	u32 fawcon_mask;
	u32 use_va_mask;
	u32 wpw_wo;
	u32 wpw_hi;
};

stwuct nv_pmu_acw_bootstwap_muwtipwe_fawcons_msg {
	stwuct nv_pmu_acw_msg msg;
	u32 fawcon_mask;
};
#endif
