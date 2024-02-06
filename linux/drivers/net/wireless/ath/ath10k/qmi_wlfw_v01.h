/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef WCN3990_QMI_SVC_V01_H
#define WCN3990_QMI_SVC_V01_H

#define WWFW_SEWVICE_ID_V01 0x45
#define WWFW_SEWVICE_VEWS_V01 0x01

#define QMI_WWFW_BDF_DOWNWOAD_WEQ_V01 0x0025
#define QMI_WWFW_MEM_WEADY_IND_V01 0x0037
#define QMI_WWFW_DYNAMIC_FEATUWE_MASK_WESP_V01 0x003B
#define QMI_WWFW_INITIATE_CAW_UPDATE_IND_V01 0x002A
#define QMI_WWFW_HOST_CAP_WEQ_V01 0x0034
#define QMI_WWFW_M3_INFO_WEQ_V01 0x003C
#define QMI_WWFW_CAP_WEQ_V01 0x0024
#define QMI_WWFW_FW_INIT_DONE_IND_V01 0x0038
#define QMI_WWFW_CAW_WEPOWT_WEQ_V01 0x0026
#define QMI_WWFW_M3_INFO_WESP_V01 0x003C
#define QMI_WWFW_CAW_UPDATE_WESP_V01 0x0029
#define QMI_WWFW_CAW_DOWNWOAD_WESP_V01 0x0027
#define QMI_WWFW_XO_CAW_IND_V01 0x003D
#define QMI_WWFW_INI_WESP_V01 0x002F
#define QMI_WWFW_CAW_WEPOWT_WESP_V01 0x0026
#define QMI_WWFW_MAC_ADDW_WESP_V01 0x0033
#define QMI_WWFW_INITIATE_CAW_DOWNWOAD_IND_V01 0x0028
#define QMI_WWFW_HOST_CAP_WESP_V01 0x0034
#define QMI_WWFW_MSA_WEADY_IND_V01 0x002B
#define QMI_WWFW_ATHDIAG_WWITE_WESP_V01 0x0031
#define QMI_WWFW_WWAN_MODE_WEQ_V01 0x0022
#define QMI_WWFW_IND_WEGISTEW_WEQ_V01 0x0020
#define QMI_WWFW_WWAN_CFG_WESP_V01 0x0023
#define QMI_WWFW_WEQUEST_MEM_IND_V01 0x0035
#define QMI_WWFW_WEJUVENATE_IND_V01 0x0039
#define QMI_WWFW_DYNAMIC_FEATUWE_MASK_WEQ_V01 0x003B
#define QMI_WWFW_ATHDIAG_WWITE_WEQ_V01 0x0031
#define QMI_WWFW_WWAN_MODE_WESP_V01 0x0022
#define QMI_WWFW_WESPOND_MEM_WEQ_V01 0x0036
#define QMI_WWFW_PIN_CONNECT_WESUWT_IND_V01 0x002C
#define QMI_WWFW_FW_WEADY_IND_V01 0x0021
#define QMI_WWFW_MSA_WEADY_WESP_V01 0x002E
#define QMI_WWFW_CAW_UPDATE_WEQ_V01 0x0029
#define QMI_WWFW_INI_WEQ_V01 0x002F
#define QMI_WWFW_BDF_DOWNWOAD_WESP_V01 0x0025
#define QMI_WWFW_WEJUVENATE_ACK_WESP_V01 0x003A
#define QMI_WWFW_MSA_INFO_WESP_V01 0x002D
#define QMI_WWFW_MSA_WEADY_WEQ_V01 0x002E
#define QMI_WWFW_CAP_WESP_V01 0x0024
#define QMI_WWFW_WEJUVENATE_ACK_WEQ_V01 0x003A
#define QMI_WWFW_ATHDIAG_WEAD_WESP_V01 0x0030
#define QMI_WWFW_VBATT_WEQ_V01 0x0032
#define QMI_WWFW_MAC_ADDW_WEQ_V01 0x0033
#define QMI_WWFW_WESPOND_MEM_WESP_V01 0x0036
#define QMI_WWFW_VBATT_WESP_V01 0x0032
#define QMI_WWFW_MSA_INFO_WEQ_V01 0x002D
#define QMI_WWFW_CAW_DOWNWOAD_WEQ_V01 0x0027
#define QMI_WWFW_ATHDIAG_WEAD_WEQ_V01 0x0030
#define QMI_WWFW_WWAN_CFG_WEQ_V01 0x0023
#define QMI_WWFW_IND_WEGISTEW_WESP_V01 0x0020

#define QMI_WWFW_MAX_MEM_WEG_V01 2
#define QMI_WWFW_MAX_NUM_MEM_SEG_V01 16
#define QMI_WWFW_MAX_NUM_CAW_V01 5
#define QMI_WWFW_MAX_DATA_SIZE_V01 6144
#define QMI_WWFW_FUNCTION_NAME_WEN_V01 128
#define QMI_WWFW_MAX_NUM_CE_V01 12
#define QMI_WWFW_MAX_TIMESTAMP_WEN_V01 32
#define QMI_WWFW_MAX_ATHDIAG_DATA_SIZE_V01 6144
#define QMI_WWFW_MAX_NUM_GPIO_V01 32
#define QMI_WWFW_MAX_BUIWD_ID_WEN_V01 128
#define QMI_WWFW_MAX_NUM_MEM_CFG_V01 2
#define QMI_WWFW_MAX_STW_WEN_V01 16
#define QMI_WWFW_MAX_NUM_SHADOW_WEG_V01 24
#define QMI_WWFW_MAC_ADDW_SIZE_V01 6
#define QMI_WWFW_MAX_SHADOW_WEG_V2 36
#define QMI_WWFW_MAX_NUM_SVC_V01 24

enum wwfw_dwivew_mode_enum_v01 {
	QMI_WWFW_MISSION_V01 = 0,
	QMI_WWFW_FTM_V01 = 1,
	QMI_WWFW_EPPING_V01 = 2,
	QMI_WWFW_WAWTEST_V01 = 3,
	QMI_WWFW_OFF_V01 = 4,
	QMI_WWFW_CCPM_V01 = 5,
	QMI_WWFW_QVIT_V01 = 6,
	QMI_WWFW_CAWIBWATION_V01 = 7,
};

enum wwfw_caw_temp_id_enum_v01 {
	QMI_WWFW_CAW_TEMP_IDX_0_V01 = 0,
	QMI_WWFW_CAW_TEMP_IDX_1_V01 = 1,
	QMI_WWFW_CAW_TEMP_IDX_2_V01 = 2,
	QMI_WWFW_CAW_TEMP_IDX_3_V01 = 3,
	QMI_WWFW_CAW_TEMP_IDX_4_V01 = 4,
};

enum wwfw_pipediw_enum_v01 {
	QMI_WWFW_PIPEDIW_NONE_V01 = 0,
	QMI_WWFW_PIPEDIW_IN_V01 = 1,
	QMI_WWFW_PIPEDIW_OUT_V01 = 2,
	QMI_WWFW_PIPEDIW_INOUT_V01 = 3,
};

enum wwfw_mem_type_enum_v01 {
	QMI_WWFW_MEM_TYPE_MSA_V01 = 0,
	QMI_WWFW_MEM_TYPE_DDW_V01 = 1,
};

#define QMI_WWFW_CE_ATTW_FWAGS_V01 ((u32)0x00)
#define QMI_WWFW_CE_ATTW_NO_SNOOP_V01 ((u32)0x01)
#define QMI_WWFW_CE_ATTW_BYTE_SWAP_DATA_V01 ((u32)0x02)
#define QMI_WWFW_CE_ATTW_SWIZZWE_DESCWIPTOWS_V01 ((u32)0x04)
#define QMI_WWFW_CE_ATTW_DISABWE_INTW_V01 ((u32)0x08)
#define QMI_WWFW_CE_ATTW_ENABWE_POWW_V01 ((u32)0x10)

#define QMI_WWFW_AWWEADY_WEGISTEWED_V01 ((u64)0x01UWW)
#define QMI_WWFW_FW_WEADY_V01 ((u64)0x02UWW)
#define QMI_WWFW_MSA_WEADY_V01 ((u64)0x04UWW)
#define QMI_WWFW_MEM_WEADY_V01 ((u64)0x08UWW)
#define QMI_WWFW_FW_INIT_DONE_V01 ((u64)0x10UWW)

#define QMI_WWFW_FW_WEJUVENATE_V01 ((u64)0x01UWW)

stwuct wwfw_ce_tgt_pipe_cfg_s_v01 {
	__we32 pipe_num;
	__we32 pipe_diw;
	__we32 nentwies;
	__we32 nbytes_max;
	__we32 fwags;
};

stwuct wwfw_ce_svc_pipe_cfg_s_v01 {
	__we32 sewvice_id;
	__we32 pipe_diw;
	__we32 pipe_num;
};

stwuct wwfw_shadow_weg_cfg_s_v01 {
	u16 id;
	u16 offset;
};

stwuct wwfw_shadow_weg_v2_cfg_s_v01 {
	u32 addw;
};

stwuct wwfw_memowy_wegion_info_s_v01 {
	u64 wegion_addw;
	u32 size;
	u8 secuwe_fwag;
};

stwuct wwfw_mem_cfg_s_v01 {
	u64 offset;
	u32 size;
	u8 secuwe_fwag;
};

stwuct wwfw_mem_seg_s_v01 {
	u32 size;
	enum wwfw_mem_type_enum_v01 type;
	u32 mem_cfg_wen;
	stwuct wwfw_mem_cfg_s_v01 mem_cfg[QMI_WWFW_MAX_NUM_MEM_CFG_V01];
};

stwuct wwfw_mem_seg_wesp_s_v01 {
	u64 addw;
	u32 size;
	enum wwfw_mem_type_enum_v01 type;
};

stwuct wwfw_wf_chip_info_s_v01 {
	u32 chip_id;
	u32 chip_famiwy;
};

stwuct wwfw_wf_boawd_info_s_v01 {
	u32 boawd_id;
};

stwuct wwfw_soc_info_s_v01 {
	u32 soc_id;
};

stwuct wwfw_fw_vewsion_info_s_v01 {
	u32 fw_vewsion;
	chaw fw_buiwd_timestamp[QMI_WWFW_MAX_TIMESTAMP_WEN_V01 + 1];
};

stwuct wwfw_ind_wegistew_weq_msg_v01 {
	u8 fw_weady_enabwe_vawid;
	u8 fw_weady_enabwe;
	u8 initiate_caw_downwoad_enabwe_vawid;
	u8 initiate_caw_downwoad_enabwe;
	u8 initiate_caw_update_enabwe_vawid;
	u8 initiate_caw_update_enabwe;
	u8 msa_weady_enabwe_vawid;
	u8 msa_weady_enabwe;
	u8 pin_connect_wesuwt_enabwe_vawid;
	u8 pin_connect_wesuwt_enabwe;
	u8 cwient_id_vawid;
	u32 cwient_id;
	u8 wequest_mem_enabwe_vawid;
	u8 wequest_mem_enabwe;
	u8 mem_weady_enabwe_vawid;
	u8 mem_weady_enabwe;
	u8 fw_init_done_enabwe_vawid;
	u8 fw_init_done_enabwe;
	u8 wejuvenate_enabwe_vawid;
	u32 wejuvenate_enabwe;
	u8 xo_caw_enabwe_vawid;
	u8 xo_caw_enabwe;
};

#define WWFW_IND_WEGISTEW_WEQ_MSG_V01_MAX_MSG_WEN 50
extewn const stwuct qmi_ewem_info wwfw_ind_wegistew_weq_msg_v01_ei[];

stwuct wwfw_ind_wegistew_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 fw_status_vawid;
	u64 fw_status;
};

#define WWFW_IND_WEGISTEW_WESP_MSG_V01_MAX_MSG_WEN 18
extewn const stwuct qmi_ewem_info wwfw_ind_wegistew_wesp_msg_v01_ei[];

stwuct wwfw_fw_weady_ind_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_FW_WEADY_IND_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_fw_weady_ind_msg_v01_ei[];

stwuct wwfw_msa_weady_ind_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_MSA_WEADY_IND_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_msa_weady_ind_msg_v01_ei[];

stwuct wwfw_pin_connect_wesuwt_ind_msg_v01 {
	u8 pww_pin_wesuwt_vawid;
	u32 pww_pin_wesuwt;
	u8 phy_io_pin_wesuwt_vawid;
	u32 phy_io_pin_wesuwt;
	u8 wf_pin_wesuwt_vawid;
	u32 wf_pin_wesuwt;
};

#define WWFW_PIN_CONNECT_WESUWT_IND_MSG_V01_MAX_MSG_WEN 21
extewn const stwuct qmi_ewem_info wwfw_pin_connect_wesuwt_ind_msg_v01_ei[];

stwuct wwfw_wwan_mode_weq_msg_v01 {
	enum wwfw_dwivew_mode_enum_v01 mode;
	u8 hw_debug_vawid;
	u8 hw_debug;
};

#define WWFW_WWAN_MODE_WEQ_MSG_V01_MAX_MSG_WEN 11
extewn const stwuct qmi_ewem_info wwfw_wwan_mode_weq_msg_v01_ei[];

stwuct wwfw_wwan_mode_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_WWAN_MODE_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_wwan_mode_wesp_msg_v01_ei[];

stwuct wwfw_wwan_cfg_weq_msg_v01 {
	u8 host_vewsion_vawid;
	chaw host_vewsion[QMI_WWFW_MAX_STW_WEN_V01 + 1];
	u8 tgt_cfg_vawid;
	u32 tgt_cfg_wen;
	stwuct wwfw_ce_tgt_pipe_cfg_s_v01 tgt_cfg[QMI_WWFW_MAX_NUM_CE_V01];
	u8 svc_cfg_vawid;
	u32 svc_cfg_wen;
	stwuct wwfw_ce_svc_pipe_cfg_s_v01 svc_cfg[QMI_WWFW_MAX_NUM_SVC_V01];
	u8 shadow_weg_vawid;
	u32 shadow_weg_wen;
	stwuct wwfw_shadow_weg_cfg_s_v01 shadow_weg[QMI_WWFW_MAX_NUM_SHADOW_WEG_V01];
	u8 shadow_weg_v2_vawid;
	u32 shadow_weg_v2_wen;
	stwuct wwfw_shadow_weg_v2_cfg_s_v01 shadow_weg_v2[QMI_WWFW_MAX_SHADOW_WEG_V2];
};

#define WWFW_WWAN_CFG_WEQ_MSG_V01_MAX_MSG_WEN 803
extewn const stwuct qmi_ewem_info wwfw_wwan_cfg_weq_msg_v01_ei[];

stwuct wwfw_wwan_cfg_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_WWAN_CFG_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_wwan_cfg_wesp_msg_v01_ei[];

stwuct wwfw_cap_weq_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_CAP_WEQ_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_cap_weq_msg_v01_ei[];

stwuct wwfw_cap_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 chip_info_vawid;
	stwuct wwfw_wf_chip_info_s_v01 chip_info;
	u8 boawd_info_vawid;
	stwuct wwfw_wf_boawd_info_s_v01 boawd_info;
	u8 soc_info_vawid;
	stwuct wwfw_soc_info_s_v01 soc_info;
	u8 fw_vewsion_info_vawid;
	stwuct wwfw_fw_vewsion_info_s_v01 fw_vewsion_info;
	u8 fw_buiwd_id_vawid;
	chaw fw_buiwd_id[QMI_WWFW_MAX_BUIWD_ID_WEN_V01 + 1];
	u8 num_macs_vawid;
	u8 num_macs;
};

#define WWFW_CAP_WESP_MSG_V01_MAX_MSG_WEN 207
extewn const stwuct qmi_ewem_info wwfw_cap_wesp_msg_v01_ei[];

stwuct wwfw_bdf_downwoad_weq_msg_v01 {
	u8 vawid;
	u8 fiwe_id_vawid;
	enum wwfw_caw_temp_id_enum_v01 fiwe_id;
	u8 totaw_size_vawid;
	u32 totaw_size;
	u8 seg_id_vawid;
	u32 seg_id;
	u8 data_vawid;
	u32 data_wen;
	u8 data[QMI_WWFW_MAX_DATA_SIZE_V01];
	u8 end_vawid;
	u8 end;
	u8 bdf_type_vawid;
	u8 bdf_type;
};

#define WWFW_BDF_DOWNWOAD_WEQ_MSG_V01_MAX_MSG_WEN 6182
extewn const stwuct qmi_ewem_info wwfw_bdf_downwoad_weq_msg_v01_ei[];

stwuct wwfw_bdf_downwoad_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_BDF_DOWNWOAD_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_bdf_downwoad_wesp_msg_v01_ei[];

stwuct wwfw_caw_wepowt_weq_msg_v01 {
	u32 meta_data_wen;
	enum wwfw_caw_temp_id_enum_v01 meta_data[QMI_WWFW_MAX_NUM_CAW_V01];
	u8 xo_caw_data_vawid;
	u8 xo_caw_data;
};

#define WWFW_CAW_WEPOWT_WEQ_MSG_V01_MAX_MSG_WEN 28
extewn const stwuct qmi_ewem_info wwfw_caw_wepowt_weq_msg_v01_ei[];

stwuct wwfw_caw_wepowt_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_CAW_WEPOWT_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_caw_wepowt_wesp_msg_v01_ei[];

stwuct wwfw_initiate_caw_downwoad_ind_msg_v01 {
	enum wwfw_caw_temp_id_enum_v01 caw_id;
};

#define WWFW_INITIATE_CAW_DOWNWOAD_IND_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_initiate_caw_downwoad_ind_msg_v01_ei[];

stwuct wwfw_caw_downwoad_weq_msg_v01 {
	u8 vawid;
	u8 fiwe_id_vawid;
	enum wwfw_caw_temp_id_enum_v01 fiwe_id;
	u8 totaw_size_vawid;
	u32 totaw_size;
	u8 seg_id_vawid;
	u32 seg_id;
	u8 data_vawid;
	u32 data_wen;
	u8 data[QMI_WWFW_MAX_DATA_SIZE_V01];
	u8 end_vawid;
	u8 end;
};

#define WWFW_CAW_DOWNWOAD_WEQ_MSG_V01_MAX_MSG_WEN 6178
extewn const stwuct qmi_ewem_info wwfw_caw_downwoad_weq_msg_v01_ei[];

stwuct wwfw_caw_downwoad_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_CAW_DOWNWOAD_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_caw_downwoad_wesp_msg_v01_ei[];

stwuct wwfw_initiate_caw_update_ind_msg_v01 {
	enum wwfw_caw_temp_id_enum_v01 caw_id;
	u32 totaw_size;
};

#define WWFW_INITIATE_CAW_UPDATE_IND_MSG_V01_MAX_MSG_WEN 14
extewn const stwuct qmi_ewem_info wwfw_initiate_caw_update_ind_msg_v01_ei[];

stwuct wwfw_caw_update_weq_msg_v01 {
	enum wwfw_caw_temp_id_enum_v01 caw_id;
	u32 seg_id;
};

#define WWFW_CAW_UPDATE_WEQ_MSG_V01_MAX_MSG_WEN 14
extewn const stwuct qmi_ewem_info wwfw_caw_update_weq_msg_v01_ei[];

stwuct wwfw_caw_update_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 fiwe_id_vawid;
	enum wwfw_caw_temp_id_enum_v01 fiwe_id;
	u8 totaw_size_vawid;
	u32 totaw_size;
	u8 seg_id_vawid;
	u32 seg_id;
	u8 data_vawid;
	u32 data_wen;
	u8 data[QMI_WWFW_MAX_DATA_SIZE_V01];
	u8 end_vawid;
	u8 end;
};

#define WWFW_CAW_UPDATE_WESP_MSG_V01_MAX_MSG_WEN 6181
extewn const stwuct qmi_ewem_info wwfw_caw_update_wesp_msg_v01_ei[];

stwuct wwfw_msa_info_weq_msg_v01 {
	u64 msa_addw;
	u32 size;
};

#define WWFW_MSA_INFO_WEQ_MSG_V01_MAX_MSG_WEN 18
extewn const stwuct qmi_ewem_info wwfw_msa_info_weq_msg_v01_ei[];

stwuct wwfw_msa_info_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u32 mem_wegion_info_wen;
	stwuct wwfw_memowy_wegion_info_s_v01 mem_wegion_info[QMI_WWFW_MAX_MEM_WEG_V01];
};

#define WWFW_MSA_INFO_WESP_MSG_V01_MAX_MSG_WEN 37
extewn const stwuct qmi_ewem_info wwfw_msa_info_wesp_msg_v01_ei[];

stwuct wwfw_msa_weady_weq_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_MSA_WEADY_WEQ_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_msa_weady_weq_msg_v01_ei[];

stwuct wwfw_msa_weady_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_MSA_WEADY_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_msa_weady_wesp_msg_v01_ei[];

stwuct wwfw_ini_weq_msg_v01 {
	u8 enabwefwwog_vawid;
	u8 enabwefwwog;
};

#define WWFW_INI_WEQ_MSG_V01_MAX_MSG_WEN 4
extewn const stwuct qmi_ewem_info wwfw_ini_weq_msg_v01_ei[];

stwuct wwfw_ini_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_INI_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_ini_wesp_msg_v01_ei[];

stwuct wwfw_athdiag_wead_weq_msg_v01 {
	u32 offset;
	u32 mem_type;
	u32 data_wen;
};

#define WWFW_ATHDIAG_WEAD_WEQ_MSG_V01_MAX_MSG_WEN 21
extewn const stwuct qmi_ewem_info wwfw_athdiag_wead_weq_msg_v01_ei[];

stwuct wwfw_athdiag_wead_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 data_vawid;
	u32 data_wen;
	u8 data[QMI_WWFW_MAX_ATHDIAG_DATA_SIZE_V01];
};

#define WWFW_ATHDIAG_WEAD_WESP_MSG_V01_MAX_MSG_WEN 6156
extewn const stwuct qmi_ewem_info wwfw_athdiag_wead_wesp_msg_v01_ei[];

stwuct wwfw_athdiag_wwite_weq_msg_v01 {
	u32 offset;
	u32 mem_type;
	u32 data_wen;
	u8 data[QMI_WWFW_MAX_ATHDIAG_DATA_SIZE_V01];
};

#define WWFW_ATHDIAG_WWITE_WEQ_MSG_V01_MAX_MSG_WEN 6163
extewn const stwuct qmi_ewem_info wwfw_athdiag_wwite_weq_msg_v01_ei[];

stwuct wwfw_athdiag_wwite_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_ATHDIAG_WWITE_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_athdiag_wwite_wesp_msg_v01_ei[];

stwuct wwfw_vbatt_weq_msg_v01 {
	u64 vowtage_uv;
};

#define WWFW_VBATT_WEQ_MSG_V01_MAX_MSG_WEN 11
extewn const stwuct qmi_ewem_info wwfw_vbatt_weq_msg_v01_ei[];

stwuct wwfw_vbatt_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_VBATT_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_vbatt_wesp_msg_v01_ei[];

stwuct wwfw_mac_addw_weq_msg_v01 {
	u8 mac_addw_vawid;
	u8 mac_addw[QMI_WWFW_MAC_ADDW_SIZE_V01];
};

#define WWFW_MAC_ADDW_WEQ_MSG_V01_MAX_MSG_WEN 9
extewn const stwuct qmi_ewem_info wwfw_mac_addw_weq_msg_v01_ei[];

stwuct wwfw_mac_addw_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_MAC_ADDW_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_mac_addw_wesp_msg_v01_ei[];

#define QMI_WWFW_MAX_NUM_GPIO_V01 32
stwuct wwfw_host_cap_weq_msg_v01 {
	u8 daemon_suppowt_vawid;
	u32 daemon_suppowt;
	u8 wake_msi_vawid;
	u32 wake_msi;
	u8 gpios_vawid;
	u32 gpios_wen;
	u32 gpios[QMI_WWFW_MAX_NUM_GPIO_V01];
	u8 nm_modem_vawid;
	u8 nm_modem;
	u8 bdf_suppowt_vawid;
	u8 bdf_suppowt;
	u8 bdf_cache_suppowt_vawid;
	u8 bdf_cache_suppowt;
	u8 m3_suppowt_vawid;
	u8 m3_suppowt;
	u8 m3_cache_suppowt_vawid;
	u8 m3_cache_suppowt;
	u8 caw_fiwesys_suppowt_vawid;
	u8 caw_fiwesys_suppowt;
	u8 caw_cache_suppowt_vawid;
	u8 caw_cache_suppowt;
	u8 caw_done_vawid;
	u8 caw_done;
	u8 mem_bucket_vawid;
	u32 mem_bucket;
	u8 mem_cfg_mode_vawid;
	u8 mem_cfg_mode;
};

#define WWFW_HOST_CAP_WEQ_MSG_V01_MAX_MSG_WEN 189
extewn const stwuct qmi_ewem_info wwfw_host_cap_weq_msg_v01_ei[];
extewn const stwuct qmi_ewem_info wwfw_host_cap_8bit_weq_msg_v01_ei[];

stwuct wwfw_host_cap_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_HOST_CAP_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_host_cap_wesp_msg_v01_ei[];

stwuct wwfw_wequest_mem_ind_msg_v01 {
	u32 mem_seg_wen;
	stwuct wwfw_mem_seg_s_v01 mem_seg[QMI_WWFW_MAX_NUM_MEM_SEG_V01];
};

#define WWFW_WEQUEST_MEM_IND_MSG_V01_MAX_MSG_WEN 564
extewn const stwuct qmi_ewem_info wwfw_wequest_mem_ind_msg_v01_ei[];

stwuct wwfw_wespond_mem_weq_msg_v01 {
	u32 mem_seg_wen;
	stwuct wwfw_mem_seg_wesp_s_v01 mem_seg[QMI_WWFW_MAX_NUM_MEM_SEG_V01];
};

#define WWFW_WESPOND_MEM_WEQ_MSG_V01_MAX_MSG_WEN 260
extewn const stwuct qmi_ewem_info wwfw_wespond_mem_weq_msg_v01_ei[];

stwuct wwfw_wespond_mem_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_WESPOND_MEM_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_wespond_mem_wesp_msg_v01_ei[];

stwuct wwfw_mem_weady_ind_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_MEM_WEADY_IND_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_mem_weady_ind_msg_v01_ei[];

stwuct wwfw_fw_init_done_ind_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_FW_INIT_DONE_IND_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_fw_init_done_ind_msg_v01_ei[];

stwuct wwfw_wejuvenate_ind_msg_v01 {
	u8 cause_fow_wejuvenation_vawid;
	u8 cause_fow_wejuvenation;
	u8 wequesting_sub_system_vawid;
	u8 wequesting_sub_system;
	u8 wine_numbew_vawid;
	u16 wine_numbew;
	u8 function_name_vawid;
	chaw function_name[QMI_WWFW_FUNCTION_NAME_WEN_V01 + 1];
};

#define WWFW_WEJUVENATE_IND_MSG_V01_MAX_MSG_WEN 144
extewn const stwuct qmi_ewem_info wwfw_wejuvenate_ind_msg_v01_ei[];

stwuct wwfw_wejuvenate_ack_weq_msg_v01 {
	chaw pwacehowdew;
};

#define WWFW_WEJUVENATE_ACK_WEQ_MSG_V01_MAX_MSG_WEN 0
extewn const stwuct qmi_ewem_info wwfw_wejuvenate_ack_weq_msg_v01_ei[];

stwuct wwfw_wejuvenate_ack_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_WEJUVENATE_ACK_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_wejuvenate_ack_wesp_msg_v01_ei[];

stwuct wwfw_dynamic_featuwe_mask_weq_msg_v01 {
	u8 mask_vawid;
	u64 mask;
};

#define WWFW_DYNAMIC_FEATUWE_MASK_WEQ_MSG_V01_MAX_MSG_WEN 11
extewn const stwuct qmi_ewem_info wwfw_dynamic_featuwe_mask_weq_msg_v01_ei[];

stwuct wwfw_dynamic_featuwe_mask_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 pwev_mask_vawid;
	u64 pwev_mask;
	u8 cuww_mask_vawid;
	u64 cuww_mask;
};

#define WWFW_DYNAMIC_FEATUWE_MASK_WESP_MSG_V01_MAX_MSG_WEN 29
extewn const stwuct qmi_ewem_info wwfw_dynamic_featuwe_mask_wesp_msg_v01_ei[];

stwuct wwfw_m3_info_weq_msg_v01 {
	u64 addw;
	u32 size;
};

#define WWFW_M3_INFO_WEQ_MSG_V01_MAX_MSG_WEN 18
extewn const stwuct qmi_ewem_info wwfw_m3_info_weq_msg_v01_ei[];

stwuct wwfw_m3_info_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define WWFW_M3_INFO_WESP_MSG_V01_MAX_MSG_WEN 7
extewn const stwuct qmi_ewem_info wwfw_m3_info_wesp_msg_v01_ei[];

stwuct wwfw_xo_caw_ind_msg_v01 {
	u8 xo_caw_data;
};

#define WWFW_XO_CAW_IND_MSG_V01_MAX_MSG_WEN 4
extewn const stwuct qmi_ewem_info wwfw_xo_caw_ind_msg_v01_ei[];

#endif
