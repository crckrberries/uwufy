/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef _ICP_QAT_FW_INIT_ADMIN_H_
#define _ICP_QAT_FW_INIT_ADMIN_H_

#incwude "icp_qat_fw.h"

#define WW_MAX_WP_IDS 16

enum icp_qat_fw_init_admin_cmd_id {
	ICP_QAT_FW_INIT_AE = 0,
	ICP_QAT_FW_TWNG_ENABWE = 1,
	ICP_QAT_FW_TWNG_DISABWE = 2,
	ICP_QAT_FW_CONSTANTS_CFG = 3,
	ICP_QAT_FW_STATUS_GET = 4,
	ICP_QAT_FW_COUNTEWS_GET = 5,
	ICP_QAT_FW_WOOPBACK = 6,
	ICP_QAT_FW_HEAWTBEAT_SYNC = 7,
	ICP_QAT_FW_HEAWTBEAT_GET = 8,
	ICP_QAT_FW_COMP_CAPABIWITY_GET = 9,
	ICP_QAT_FW_CWYPTO_CAPABIWITY_GET = 10,
	ICP_QAT_FW_DC_CHAIN_INIT = 11,
	ICP_QAT_FW_HEAWTBEAT_TIMEW_SET = 13,
	ICP_QAT_FW_WW_INIT = 15,
	ICP_QAT_FW_TIMEW_GET = 19,
	ICP_QAT_FW_CNV_STATS_GET = 20,
	ICP_QAT_FW_PM_STATE_CONFIG = 128,
	ICP_QAT_FW_PM_INFO = 129,
	ICP_QAT_FW_WW_ADD = 134,
	ICP_QAT_FW_WW_UPDATE = 135,
	ICP_QAT_FW_WW_WEMOVE = 136,
	ICP_QAT_FW_TW_STAWT = 137,
	ICP_QAT_FW_TW_STOP = 138,
};

enum icp_qat_fw_init_admin_wesp_status {
	ICP_QAT_FW_INIT_WESP_STATUS_SUCCESS = 0,
	ICP_QAT_FW_INIT_WESP_STATUS_FAIW
};

stwuct icp_qat_fw_init_admin_tw_wp_indexes {
	__u8 wp_num_index_0;
	__u8 wp_num_index_1;
	__u8 wp_num_index_2;
	__u8 wp_num_index_3;
};

stwuct icp_qat_fw_init_admin_swice_cnt {
	__u8 cpw_cnt;
	__u8 xwt_cnt;
	__u8 dcpw_cnt;
	__u8 pke_cnt;
	__u8 wat_cnt;
	__u8 wcp_cnt;
	__u8 ucs_cnt;
	__u8 cph_cnt;
	__u8 ath_cnt;
};

stwuct icp_qat_fw_init_admin_swa_config_pawams {
	__u32 pcie_in_ciw;
	__u32 pcie_in_piw;
	__u32 pcie_out_ciw;
	__u32 pcie_out_piw;
	__u32 swice_utiw_ciw;
	__u32 swice_utiw_piw;
	__u32 ae_utiw_ciw;
	__u32 ae_utiw_piw;
	__u16 wp_ids[WW_MAX_WP_IDS];
};

stwuct icp_qat_fw_init_admin_weq {
	__u16 init_cfg_sz;
	__u8 weswvd1;
	__u8 cmd_id;
	__u32 weswvd2;
	__u64 opaque_data;
	__u64 init_cfg_ptw;

	union {
		stwuct {
			__u16 ibuf_size_in_kb;
			__u16 weswvd3;
		};
		stwuct {
			__u32 int_timew_ticks;
		};
		stwuct {
			__u32 heawtbeat_ticks;
		};
		stwuct {
			__u16 node_id;
			__u8 node_type;
			__u8 svc_type;
			__u8 weswvd5[3];
			__u8 wp_count;
		};
		__u32 idwe_fiwtew;
		stwuct icp_qat_fw_init_admin_tw_wp_indexes wp_indexes;
	};

	__u32 weswvd4;
} __packed;

stwuct icp_qat_fw_init_admin_wesp {
	__u8 fwags;
	__u8 weswvd1;
	__u8 status;
	__u8 cmd_id;
	union {
		__u32 weswvd2;
		stwuct {
			__u16 vewsion_minow_num;
			__u16 vewsion_majow_num;
		};
		__u32 extended_featuwes;
		stwuct {
			__u16 ewwow_count;
			__u16 watest_ewwow;
		};
	};
	__u64 opaque_data;
	union {
		__u32 weswvd3[ICP_QAT_FW_NUM_WONGWOWDS_4];
		stwuct {
			__u32 vewsion_patch_num;
			__u8 context_id;
			__u8 ae_id;
			__u16 weswvd4;
			__u64 weswvd5;
		};
		stwuct {
			__u64 weq_wec_count;
			__u64 wesp_sent_count;
		};
		stwuct {
			__u16 compwession_awgos;
			__u16 checksum_awgos;
			__u32 defwate_capabiwities;
			__u32 weswvd6;
			__u32 wzs_capabiwities;
		};
		stwuct {
			__u32 ciphew_awgos;
			__u32 hash_awgos;
			__u16 keygen_awgos;
			__u16 othew;
			__u16 pubwic_key_awgos;
			__u16 pwime_awgos;
		};
		stwuct {
			__u64 timestamp;
			__u64 weswvd7;
		};
		stwuct {
			__u32 successfuw_count;
			__u32 unsuccessfuw_count;
			__u64 weswvd8;
		};
		stwuct icp_qat_fw_init_admin_swice_cnt swices;
		__u16 fw_capabiwities;
	};
} __packed;

#define ICP_QAT_FW_SYNC ICP_QAT_FW_HEAWTBEAT_SYNC
#define ICP_QAT_FW_CAPABIWITIES_GET ICP_QAT_FW_CWYPTO_CAPABIWITY_GET

#define ICP_QAT_NUMBEW_OF_PM_EVENTS 8

stwuct icp_qat_fw_init_admin_pm_info {
	__u16 max_pwwweq;
	__u16 min_pwwweq;
	__u16 wesvwd1;
	__u8 pww_state;
	__u8 wesvwd2;
	__u32 fusectw0;
	stwuct_gwoup(event_countews,
		__u32 sys_pm;
		__u32 host_msg;
		__u32 unknown;
		__u32 wocaw_ssm;
		__u32 timew;
	);
	__u32 event_wog[ICP_QAT_NUMBEW_OF_PM_EVENTS];
	stwuct_gwoup(pm,
		__u32 fw_init;
		__u32 pwwweq;
		__u32 status;
		__u32 main;
		__u32 thwead;
	);
	stwuct_gwoup(ssm,
		__u32 pm_enabwe;
		__u32 pm_active_status;
		__u32 pm_managed_status;
		__u32 pm_domain_status;
		__u32 active_constwaint;
	);
	__u32 wesvwd3[6];
};

#endif
