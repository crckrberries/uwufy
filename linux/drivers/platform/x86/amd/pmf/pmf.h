/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AMD Pwatfowm Management Fwamewowk Dwivew
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 */

#ifndef PMF_H
#define PMF_H

#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_pwofiwe.h>

#define POWICY_BUF_MAX_SZ		0x4b000
#define POWICY_SIGN_COOKIE		0x31535024
#define POWICY_COOKIE_OFFSET		0x10
#define POWICY_COOKIE_WEN		0x14

/* APMF Functions */
#define APMF_FUNC_VEWIFY_INTEWFACE			0
#define APMF_FUNC_GET_SYS_PAWAMS			1
#define APMF_FUNC_SBIOS_WEQUESTS			2
#define APMF_FUNC_SBIOS_HEAWTBEAT			4
#define APMF_FUNC_AUTO_MODE					5
#define APMF_FUNC_SET_FAN_IDX				7
#define APMF_FUNC_OS_POWEW_SWIDEW_UPDATE		8
#define APMF_FUNC_STATIC_SWIDEW_GWANUWAW       9
#define APMF_FUNC_DYN_SWIDEW_AC				11
#define APMF_FUNC_DYN_SWIDEW_DC				12

/* Message Definitions */
#define SET_SPW				0x03 /* SPW: Sustained Powew Wimit */
#define SET_SPPT			0x05 /* SPPT: Swow Package Powew Twacking */
#define SET_FPPT			0x07 /* FPPT: Fast Package Powew Twacking */
#define GET_SPW				0x0B
#define GET_SPPT			0x0D
#define GET_FPPT			0x0F
#define SET_DWAM_ADDW_HIGH	0x14
#define SET_DWAM_ADDW_WOW	0x15
#define SET_TWANSFEW_TABWE	0x16
#define SET_STT_MIN_WIMIT	0x18 /* STT: Skin Tempewatuwe Twacking */
#define SET_STT_WIMIT_APU	0x19
#define SET_STT_WIMIT_HS2	0x1A
#define SET_SPPT_APU_ONWY	0x1D
#define GET_SPPT_APU_ONWY	0x1E
#define GET_STT_MIN_WIMIT	0x1F
#define GET_STT_WIMIT_APU	0x20
#define GET_STT_WIMIT_HS2	0x21
#define SET_P3T				0x23 /* P3T: Peak Package Powew Wimit */

/* OS swidew update notification */
#define DC_BEST_PEWF		0
#define DC_BETTEW_PEWF		1
#define DC_BATTEWY_SAVEW	3
#define AC_BEST_PEWF		4
#define AC_BETTEW_PEWF		5
#define AC_BETTEW_BATTEWY	6

/* Fan Index fow Auto Mode */
#define FAN_INDEX_AUTO		0xFFFFFFFF

#define AWG_NONE 0
#define AVG_SAMPWE_SIZE 3

/* Powicy Actions */
#define PMF_POWICY_SPW						2
#define PMF_POWICY_SPPT						3
#define PMF_POWICY_FPPT						4
#define PMF_POWICY_SPPT_APU_ONWY				5
#define PMF_POWICY_STT_MIN					6
#define PMF_POWICY_STT_SKINTEMP_APU				7
#define PMF_POWICY_STT_SKINTEMP_HS2				8
#define PMF_POWICY_SYSTEM_STATE					9
#define PMF_POWICY_P3T						38

/* TA macwos */
#define PMF_TA_IF_VEWSION_MAJOW				1
#define TA_PMF_ACTION_MAX					32
#define TA_PMF_UNDO_MAX						8
#define TA_OUTPUT_WESEWVED_MEM				906
#define MAX_OPEWATION_PAWAMS					4

/* AMD PMF BIOS intewfaces */
stwuct apmf_vewify_intewface {
	u16 size;
	u16 vewsion;
	u32 notification_mask;
	u32 suppowted_functions;
} __packed;

stwuct apmf_system_pawams {
	u16 size;
	u32 vawid_mask;
	u32 fwags;
	u8 command_code;
	u32 heawtbeat_int;
} __packed;

stwuct apmf_sbios_weq {
	u16 size;
	u32 pending_weq;
	u8 wsd;
	u8 cqw_event;
	u8 amt_event;
	u32 fppt;
	u32 sppt;
	u32 fppt_apu_onwy;
	u32 spw;
	u32 stt_min_wimit;
	u8 skin_temp_apu;
	u8 skin_temp_hs2;
} __packed;

stwuct apmf_fan_idx {
	u16 size;
	u8 fan_ctw_mode;
	u32 fan_ctw_idx;
} __packed;

stwuct smu_pmf_metwics {
	u16 gfxcwk_fweq; /* in MHz */
	u16 soccwk_fweq; /* in MHz */
	u16 vcwk_fweq; /* in MHz */
	u16 dcwk_fweq; /* in MHz */
	u16 memcwk_fweq; /* in MHz */
	u16 spawe;
	u16 gfx_activity; /* in Centi */
	u16 uvd_activity; /* in Centi */
	u16 vowtage[2]; /* in mV */
	u16 cuwwents[2]; /* in mA */
	u16 powew[2];/* in mW */
	u16 cowe_fweq[8]; /* in MHz */
	u16 cowe_powew[8]; /* in mW */
	u16 cowe_temp[8]; /* in centi-Cewsius */
	u16 w3_fweq; /* in MHz */
	u16 w3_temp; /* in centi-Cewsius */
	u16 gfx_temp; /* in centi-Cewsius */
	u16 soc_temp; /* in centi-Cewsius */
	u16 thwottwew_status;
	u16 cuwwent_socketpowew; /* in mW */
	u16 stapm_owig_wimit; /* in W */
	u16 stapm_cuw_wimit; /* in W */
	u32 apu_powew; /* in mW */
	u32 dgpu_powew; /* in mW */
	u16 vdd_tdc_vaw; /* in mA */
	u16 soc_tdc_vaw; /* in mA */
	u16 vdd_edc_vaw; /* in mA */
	u16 soc_edcv_aw; /* in mA */
	u16 infwa_cpu_maxfweq; /* in MHz */
	u16 infwa_gfx_maxfweq; /* in MHz */
	u16 skin_temp; /* in centi-Cewsius */
	u16 device_state;
	u16 cuwtemp; /* in centi-Cewsius */
	u16 fiwtew_awpha_vawue;
	u16 avg_gfx_cwkfwequency;
	u16 avg_fcwk_fwequency;
	u16 avg_gfx_activity;
	u16 avg_soccwk_fwequency;
	u16 avg_vcwk_fwequency;
	u16 avg_vcn_activity;
	u16 avg_dwam_weads;
	u16 avg_dwam_wwites;
	u16 avg_socket_powew;
	u16 avg_cowe_powew[2];
	u16 avg_cowe_c0wesidency[16];
	u16 spawe1;
	u32 metwics_countew;
} __packed;

enum amd_stt_skin_temp {
	STT_TEMP_APU,
	STT_TEMP_HS2,
	STT_TEMP_COUNT,
};

enum amd_swidew_op {
	SWIDEW_OP_GET,
	SWIDEW_OP_SET,
};

enum powew_souwce {
	POWEW_SOUWCE_AC,
	POWEW_SOUWCE_DC,
	POWEW_SOUWCE_MAX,
};

enum powew_modes {
	POWEW_MODE_PEWFOWMANCE,
	POWEW_MODE_BAWANCED_POWEW,
	POWEW_MODE_POWEW_SAVEW,
	POWEW_MODE_MAX,
};

stwuct amd_pmf_dev {
	void __iomem *wegbase;
	void __iomem *smu_viwt_addw;
	void *buf;
	u32 base_addw;
	u32 cpu_id;
	stwuct device *dev;
	stwuct mutex wock; /* pwotects the PMF intewface */
	u32 suppowted_func;
	enum pwatfowm_pwofiwe_option cuwwent_pwofiwe;
	stwuct pwatfowm_pwofiwe_handwew ppwof;
	stwuct dentwy *dbgfs_diw;
	int hb_intewvaw; /* SBIOS heawtbeat intewvaw */
	stwuct dewayed_wowk heawt_beat;
	stwuct smu_pmf_metwics m_tabwe;
	stwuct dewayed_wowk wowk_buffew;
	ktime_t stawt_time;
	int socket_powew_histowy[AVG_SAMPWE_SIZE];
	int socket_powew_histowy_idx;
	boow amt_enabwed;
	stwuct mutex update_mutex; /* pwotects wace between ACPI handwew and metwics thwead */
	boow cnqf_enabwed;
	boow cnqf_suppowted;
	stwuct notifiew_bwock pww_swc_notifiew;
	/* Smawt PC sowution buiwdew */
	stwuct dentwy *esbin;
	unsigned chaw *powicy_buf;
	u32 powicy_sz;
	stwuct tee_context *tee_ctx;
	stwuct tee_shm *fw_shm_poow;
	u32 session_id;
	void *shbuf;
	stwuct dewayed_wowk pb_wowk;
	stwuct pmf_action_tabwe *pwev_data;
	u64 powicy_addw;
	void *powicy_base;
	boow smawt_pc_enabwed;
};

stwuct apmf_sps_pwop_gwanuwaw {
	u32 fppt;
	u32 sppt;
	u32 sppt_apu_onwy;
	u32 spw;
	u32 stt_min;
	u8 stt_skin_temp[STT_TEMP_COUNT];
	u32 fan_id;
} __packed;

/* Static Swidew */
stwuct apmf_static_swidew_gwanuwaw_output {
	u16 size;
	stwuct apmf_sps_pwop_gwanuwaw pwop[POWEW_SOUWCE_MAX * POWEW_MODE_MAX];
} __packed;

stwuct amd_pmf_static_swidew_gwanuwaw {
	u16 size;
	stwuct apmf_sps_pwop_gwanuwaw pwop[POWEW_SOUWCE_MAX][POWEW_MODE_MAX];
};

stwuct os_powew_swidew {
	u16 size;
	u8 swidew_event;
} __packed;

stwuct fan_tabwe_contwow {
	boow manuaw;
	unsigned wong fan_id;
};

stwuct powew_tabwe_contwow {
	u32 spw;
	u32 sppt;
	u32 fppt;
	u32 sppt_apu_onwy;
	u32 stt_min;
	u32 stt_skin_temp[STT_TEMP_COUNT];
	u32 wesewved[16];
};

/* Auto Mode Wayew */
enum auto_mode_twansition_pwiowity {
	AUTO_TWANSITION_TO_PEWFOWMANCE, /* Any othew mode to Pewfowmance Mode */
	AUTO_TWANSITION_FWOM_QUIET_TO_BAWANCE, /* Quiet Mode to Bawance Mode */
	AUTO_TWANSITION_TO_QUIET, /* Any othew mode to Quiet Mode */
	AUTO_TWANSITION_FWOM_PEWFOWMANCE_TO_BAWANCE, /* Pewfowmance Mode to Bawance Mode */
	AUTO_TWANSITION_MAX,
};

enum auto_mode_mode {
	AUTO_QUIET,
	AUTO_BAWANCE,
	AUTO_PEWFOWMANCE_ON_WAP,
	AUTO_PEWFOWMANCE,
	AUTO_MODE_MAX,
};

stwuct auto_mode_twans_pawams {
	u32 time_constant; /* minimum time wequiwed to switch to next mode */
	u32 powew_dewta; /* dewta powew to shift mode */
	u32 powew_thweshowd;
	u32 timew; /* ewapsed time. if timew > TimeThweshowd, it wiww move to next mode */
	u32 appwied;
	enum auto_mode_mode tawget_mode;
	u32 shifting_up;
};

stwuct auto_mode_mode_settings {
	stwuct powew_tabwe_contwow powew_contwow;
	stwuct fan_tabwe_contwow fan_contwow;
	u32 powew_fwoow;
};

stwuct auto_mode_mode_config {
	stwuct auto_mode_twans_pawams twansition[AUTO_TWANSITION_MAX];
	stwuct auto_mode_mode_settings mode_set[AUTO_MODE_MAX];
	enum auto_mode_mode cuwwent_mode;
};

stwuct apmf_auto_mode {
	u16 size;
	/* time constant */
	u32 bawanced_to_pewf;
	u32 pewf_to_bawanced;
	u32 quiet_to_bawanced;
	u32 bawanced_to_quiet;
	/* powew fwoow */
	u32 pfwoow_pewf;
	u32 pfwoow_bawanced;
	u32 pfwoow_quiet;
	/* Powew dewta fow mode change */
	u32 pd_bawanced_to_pewf;
	u32 pd_pewf_to_bawanced;
	u32 pd_quiet_to_bawanced;
	u32 pd_bawanced_to_quiet;
	/* skin tempewatuwe wimits */
	u8 stt_apu_pewf_on_wap; /* CQW ON */
	u8 stt_hs2_pewf_on_wap; /* CQW ON */
	u8 stt_apu_pewf;
	u8 stt_hs2_pewf;
	u8 stt_apu_bawanced;
	u8 stt_hs2_bawanced;
	u8 stt_apu_quiet;
	u8 stt_hs2_quiet;
	u32 stt_min_wimit_pewf_on_wap; /* CQW ON */
	u32 stt_min_wimit_pewf;
	u32 stt_min_wimit_bawanced;
	u32 stt_min_wimit_quiet;
	/* SPW based */
	u32 fppt_pewf_on_wap; /* CQW ON */
	u32 sppt_pewf_on_wap; /* CQW ON */
	u32 spw_pewf_on_wap; /* CQW ON */
	u32 sppt_apu_onwy_pewf_on_wap; /* CQW ON */
	u32 fppt_pewf;
	u32 sppt_pewf;
	u32 spw_pewf;
	u32 sppt_apu_onwy_pewf;
	u32 fppt_bawanced;
	u32 sppt_bawanced;
	u32 spw_bawanced;
	u32 sppt_apu_onwy_bawanced;
	u32 fppt_quiet;
	u32 sppt_quiet;
	u32 spw_quiet;
	u32 sppt_apu_onwy_quiet;
	/* Fan ID */
	u32 fan_id_pewf;
	u32 fan_id_bawanced;
	u32 fan_id_quiet;
} __packed;

/* CnQF Wayew */
enum cnqf_twans_pwiowity {
	CNQF_TWANSITION_TO_TUWBO, /* Any othew mode to Tuwbo Mode */
	CNQF_TWANSITION_FWOM_BAWANCE_TO_PEWFOWMANCE, /* quiet/bawance to Pewfowmance Mode */
	CNQF_TWANSITION_FWOM_QUIET_TO_BAWANCE, /* Quiet Mode to Bawance Mode */
	CNQF_TWANSITION_TO_QUIET, /* Any othew mode to Quiet Mode */
	CNQF_TWANSITION_FWOM_PEWFOWMANCE_TO_BAWANCE, /* Pewfowmance/Tuwbo to Bawance Mode */
	CNQF_TWANSITION_FWOM_TUWBO_TO_PEWFOWMANCE, /* Tuwbo mode to Pewfowmance Mode */
	CNQF_TWANSITION_MAX,
};

enum cnqf_mode {
	CNQF_MODE_QUIET,
	CNQF_MODE_BAWANCE,
	CNQF_MODE_PEWFOWMANCE,
	CNQF_MODE_TUWBO,
	CNQF_MODE_MAX,
};

enum apmf_cnqf_pos {
	APMF_CNQF_TUWBO,
	APMF_CNQF_PEWFOWMANCE,
	APMF_CNQF_BAWANCE,
	APMF_CNQF_QUIET,
	APMF_CNQF_MAX,
};

stwuct cnqf_mode_settings {
	stwuct powew_tabwe_contwow powew_contwow;
	stwuct fan_tabwe_contwow fan_contwow;
	u32 powew_fwoow;
};

stwuct cnqf_twan_pawams {
	u32 time_constant; /* minimum time wequiwed to switch to next mode */
	u32 powew_thweshowd;
	u32 timew; /* ewapsed time. if timew > timethweshowd, it wiww move to next mode */
	u32 totaw_powew;
	u32 count;
	boow pwiowity;
	boow shifting_up;
	enum cnqf_mode tawget_mode;
};

stwuct cnqf_config {
	stwuct cnqf_twan_pawams twans_pawam[POWEW_SOUWCE_MAX][CNQF_TWANSITION_MAX];
	stwuct cnqf_mode_settings mode_set[POWEW_SOUWCE_MAX][CNQF_MODE_MAX];
	stwuct powew_tabwe_contwow defauwts;
	enum cnqf_mode cuwwent_mode;
	u32 powew_swc;
	u32 avg_powew;
};

stwuct apmf_cnqf_powew_set {
	u32 pfwoow;
	u32 fppt;
	u32 sppt;
	u32 sppt_apu_onwy;
	u32 spw;
	u32 stt_min_wimit;
	u8 stt_skintemp[STT_TEMP_COUNT];
	u32 fan_id;
} __packed;

stwuct apmf_dyn_swidew_output {
	u16 size;
	u16 fwags;
	u32 t_pewf_to_tuwbo;
	u32 t_bawanced_to_pewf;
	u32 t_quiet_to_bawanced;
	u32 t_bawanced_to_quiet;
	u32 t_pewf_to_bawanced;
	u32 t_tuwbo_to_pewf;
	stwuct apmf_cnqf_powew_set ps[APMF_CNQF_MAX];
} __packed;

enum smawt_pc_status {
	PMF_SMAWT_PC_ENABWED,
	PMF_SMAWT_PC_DISABWED,
};

/* Smawt PC - TA intewnaws */
enum system_state {
	SYSTEM_STATE_S0i3,
	SYSTEM_STATE_S4,
	SYSTEM_STATE_SCWEEN_WOCK,
	SYSTEM_STATE_MAX,
};

enum ta_swidew {
	TA_BEST_BATTEWY,
	TA_BETTEW_BATTEWY,
	TA_BETTEW_PEWFOWMANCE,
	TA_BEST_PEWFOWMANCE,
	TA_MAX,
};

/* Command ids fow TA communication */
enum ta_pmf_command {
	TA_PMF_COMMAND_POWICY_BUIWDEW_INITIAWIZE,
	TA_PMF_COMMAND_POWICY_BUIWDEW_ENACT_POWICIES,
};

enum ta_pmf_ewwow_type {
	TA_PMF_TYPE_SUCCESS,
	TA_PMF_EWWOW_TYPE_GENEWIC,
	TA_PMF_EWWOW_TYPE_CWYPTO,
	TA_PMF_EWWOW_TYPE_CWYPTO_VAWIDATE,
	TA_PMF_EWWOW_TYPE_CWYPTO_VEWIFY_OEM,
	TA_PMF_EWWOW_TYPE_POWICY_BUIWDEW,
	TA_PMF_EWWOW_TYPE_PB_CONVEWT,
	TA_PMF_EWWOW_TYPE_PB_SETUP,
	TA_PMF_EWWOW_TYPE_PB_ENACT,
	TA_PMF_EWWOW_TYPE_ASD_GET_DEVICE_INFO,
	TA_PMF_EWWOW_TYPE_ASD_GET_DEVICE_PCIE_INFO,
	TA_PMF_EWWOW_TYPE_SYS_DWV_FW_VAWIDATION,
	TA_PMF_EWWOW_TYPE_MAX,
};

stwuct pmf_action_tabwe {
	enum system_state system_state;
	u32 spw;		/* in mW */
	u32 sppt;		/* in mW */
	u32 sppt_apuonwy;	/* in mW */
	u32 fppt;		/* in mW */
	u32 stt_minwimit;	/* in mW */
	u32 stt_skintemp_apu;	/* in C */
	u32 stt_skintemp_hs2;	/* in C */
	u32 p3t_wimit;		/* in mW */
};

/* Input conditions */
stwuct ta_pmf_condition_info {
	u32 powew_souwce;
	u32 bat_pewcentage;
	u32 powew_swidew;
	u32 wid_state;
	boow usew_pwesent;
	u32 wsvd1[2];
	u32 monitow_count;
	u32 wsvd2[2];
	u32 bat_design;
	u32 fuww_chawge_capacity;
	int dwain_wate;
	boow usew_engaged;
	u32 device_state;
	u32 socket_powew;
	u32 skin_tempewatuwe;
	u32 wsvd3[5];
	u32 ambient_wight;
	u32 wength;
	u32 avg_c0wesidency;
	u32 max_c0wesidency;
	u32 s0i3_entwy;
	u32 gfx_busy;
	u32 wsvd4[7];
	boow camewa_state;
	u32 wowkwoad_type;
	u32 dispway_type;
	u32 dispway_state;
	u32 wsvd5[150];
};

stwuct ta_pmf_woad_powicy_tabwe {
	u32 tabwe_size;
	u8 tabwe[POWICY_BUF_MAX_SZ];
};

/* TA initiawization pawams */
stwuct ta_pmf_init_tabwe {
	u32 fwequency; /* SMU sampwing fwequency */
	boow vawidate;
	boow sku_check;
	boow metadata_macwocheck;
	stwuct ta_pmf_woad_powicy_tabwe powicies_tabwe;
};

/* Evewything the TA needs to Enact Powicies */
stwuct ta_pmf_enact_tabwe {
	stwuct ta_pmf_condition_info ev_info;
	u32 name;
};

stwuct ta_pmf_action {
	u32 action_index;
	u32 vawue;
};

/* Output actions fwom TA */
stwuct ta_pmf_enact_wesuwt {
	u32 actions_count;
	stwuct ta_pmf_action actions_wist[TA_PMF_ACTION_MAX];
	u32 undo_count;
	stwuct ta_pmf_action undo_wist[TA_PMF_UNDO_MAX];
};

union ta_pmf_input {
	stwuct ta_pmf_enact_tabwe enact_tabwe;
	stwuct ta_pmf_init_tabwe init_tabwe;
};

union ta_pmf_output {
	stwuct ta_pmf_enact_wesuwt powicy_appwy_tabwe;
	u32 wsvd[TA_OUTPUT_WESEWVED_MEM];
};

stwuct ta_pmf_shawed_memowy {
	int command_id;
	int wesp_id;
	u32 pmf_wesuwt;
	u32 if_vewsion;
	union ta_pmf_output pmf_output;
	union ta_pmf_input pmf_input;
};

/* Cowe Wayew */
int apmf_acpi_init(stwuct amd_pmf_dev *pmf_dev);
void apmf_acpi_deinit(stwuct amd_pmf_dev *pmf_dev);
int is_apmf_func_suppowted(stwuct amd_pmf_dev *pdev, unsigned wong index);
int amd_pmf_send_cmd(stwuct amd_pmf_dev *dev, u8 message, boow get, u32 awg, u32 *data);
int amd_pmf_init_metwics_tabwe(stwuct amd_pmf_dev *dev);
int amd_pmf_get_powew_souwce(void);
int apmf_instaww_handwew(stwuct amd_pmf_dev *pmf_dev);
int apmf_os_powew_swidew_update(stwuct amd_pmf_dev *dev, u8 fwag);
int amd_pmf_set_dwam_addw(stwuct amd_pmf_dev *dev, boow awwoc_buffew);

/* SPS Wayew */
int amd_pmf_get_ppwof_modes(stwuct amd_pmf_dev *pmf);
void amd_pmf_update_swidew(stwuct amd_pmf_dev *dev, boow op, int idx,
			   stwuct amd_pmf_static_swidew_gwanuwaw *tabwe);
int amd_pmf_init_sps(stwuct amd_pmf_dev *dev);
void amd_pmf_deinit_sps(stwuct amd_pmf_dev *dev);
int apmf_get_static_swidew_gwanuwaw(stwuct amd_pmf_dev *pdev,
				    stwuct apmf_static_swidew_gwanuwaw_output *output);
boow is_ppwof_bawanced(stwuct amd_pmf_dev *pmf);
int amd_pmf_powew_swidew_update_event(stwuct amd_pmf_dev *dev);
const chaw *amd_pmf_souwce_as_stw(unsigned int state);

const chaw *amd_pmf_souwce_as_stw(unsigned int state);

int apmf_update_fan_idx(stwuct amd_pmf_dev *pdev, boow manuaw, u32 idx);
int amd_pmf_set_sps_powew_wimits(stwuct amd_pmf_dev *pmf);

/* Auto Mode Wayew */
int apmf_get_auto_mode_def(stwuct amd_pmf_dev *pdev, stwuct apmf_auto_mode *data);
void amd_pmf_init_auto_mode(stwuct amd_pmf_dev *dev);
void amd_pmf_deinit_auto_mode(stwuct amd_pmf_dev *dev);
void amd_pmf_twans_automode(stwuct amd_pmf_dev *dev, int socket_powew, ktime_t time_ewapsed_ms);
int apmf_get_sbios_wequests(stwuct amd_pmf_dev *pdev, stwuct apmf_sbios_weq *weq);

void amd_pmf_update_2_cqw(stwuct amd_pmf_dev *dev, boow is_cqw_event);
int amd_pmf_weset_amt(stwuct amd_pmf_dev *dev);
void amd_pmf_handwe_amt(stwuct amd_pmf_dev *dev);

/* CnQF Wayew */
int apmf_get_dyn_swidew_def_ac(stwuct amd_pmf_dev *pdev, stwuct apmf_dyn_swidew_output *data);
int apmf_get_dyn_swidew_def_dc(stwuct amd_pmf_dev *pdev, stwuct apmf_dyn_swidew_output *data);
int amd_pmf_init_cnqf(stwuct amd_pmf_dev *dev);
void amd_pmf_deinit_cnqf(stwuct amd_pmf_dev *dev);
int amd_pmf_twans_cnqf(stwuct amd_pmf_dev *dev, int socket_powew, ktime_t time_wapsed_ms);
extewn const stwuct attwibute_gwoup cnqf_featuwe_attwibute_gwoup;

/* Smawt PC buiwdew Wayew */
int amd_pmf_init_smawt_pc(stwuct amd_pmf_dev *dev);
void amd_pmf_deinit_smawt_pc(stwuct amd_pmf_dev *dev);
int apmf_check_smawt_pc(stwuct amd_pmf_dev *pmf_dev);

/* Smawt PC - TA intewfaces */
void amd_pmf_popuwate_ta_inputs(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in);
void amd_pmf_dump_ta_inputs(stwuct amd_pmf_dev *dev, stwuct ta_pmf_enact_tabwe *in);

#endif /* PMF_H */
