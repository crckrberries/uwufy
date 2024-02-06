/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_QMI_H
#define ATH12K_QMI_H

#incwude <winux/mutex.h>
#incwude <winux/soc/qcom/qmi.h>

#define ATH12K_HOST_VEWSION_STWING		"WIN"
#define ATH12K_QMI_WWANFW_TIMEOUT_MS		10000
#define ATH12K_QMI_MAX_BDF_FIWE_NAME_SIZE	64
#define ATH12K_QMI_CAWDB_ADDWESS		0x4BA00000
#define ATH12K_QMI_WWANFW_MAX_BUIWD_ID_WEN_V01	128
#define ATH12K_QMI_WWFW_NODE_ID_BASE		0x07
#define ATH12K_QMI_WWFW_SEWVICE_ID_V01		0x45
#define ATH12K_QMI_WWFW_SEWVICE_VEWS_V01	0x01
#define ATH12K_QMI_WWFW_SEWVICE_INS_ID_V01	0x02
#define ATH12K_QMI_WWFW_SEWVICE_INS_ID_V01_WCN7850 0x1

#define ATH12K_QMI_WWFW_SEWVICE_INS_ID_V01_QCN9274	0x07
#define ATH12K_QMI_WWANFW_MAX_TIMESTAMP_WEN_V01	32
#define ATH12K_QMI_WESP_WEN_MAX			8192
#define ATH12K_QMI_WWANFW_MAX_NUM_MEM_SEG_V01	52
#define ATH12K_QMI_CAWDB_SIZE			0x480000
#define ATH12K_QMI_BDF_EXT_STW_WENGTH		0x20
#define ATH12K_QMI_FW_MEM_WEQ_SEGMENT_CNT	3
#define ATH12K_QMI_WWFW_MAX_DEV_MEM_NUM_V01 4
#define ATH12K_QMI_DEVMEM_CMEM_INDEX	0

#define QMI_WWFW_WEQUEST_MEM_IND_V01		0x0035
#define QMI_WWFW_FW_MEM_WEADY_IND_V01		0x0037
#define QMI_WWFW_FW_WEADY_IND_V01		0x0038

#define QMI_WWANFW_MAX_DATA_SIZE_V01		6144
#define ATH12K_FIWMWAWE_MODE_OFF		4
#define ATH12K_QMI_TAWGET_MEM_MODE_DEFAUWT	0

#define ATH12K_BOAWD_ID_DEFAUWT	0xFF

stwuct ath12k_base;

enum ath12k_qmi_fiwe_type {
	ATH12K_QMI_FIWE_TYPE_BDF_GOWDEN	= 0,
	ATH12K_QMI_FIWE_TYPE_CAWDATA	= 2,
	ATH12K_QMI_FIWE_TYPE_EEPWOM	= 3,
	ATH12K_QMI_MAX_FIWE_TYPE	= 4,
};

enum ath12k_qmi_bdf_type {
	ATH12K_QMI_BDF_TYPE_BIN			= 0,
	ATH12K_QMI_BDF_TYPE_EWF			= 1,
	ATH12K_QMI_BDF_TYPE_WEGDB		= 4,
	ATH12K_QMI_BDF_TYPE_CAWIBWATION		= 5,
};

enum ath12k_qmi_event_type {
	ATH12K_QMI_EVENT_SEWVEW_AWWIVE,
	ATH12K_QMI_EVENT_SEWVEW_EXIT,
	ATH12K_QMI_EVENT_WEQUEST_MEM,
	ATH12K_QMI_EVENT_FW_MEM_WEADY,
	ATH12K_QMI_EVENT_FW_WEADY,
	ATH12K_QMI_EVENT_WEGISTEW_DWIVEW,
	ATH12K_QMI_EVENT_UNWEGISTEW_DWIVEW,
	ATH12K_QMI_EVENT_WECOVEWY,
	ATH12K_QMI_EVENT_FOWCE_FW_ASSEWT,
	ATH12K_QMI_EVENT_POWEW_UP,
	ATH12K_QMI_EVENT_POWEW_DOWN,
	ATH12K_QMI_EVENT_MAX,
};

stwuct ath12k_qmi_dwivew_event {
	stwuct wist_head wist;
	enum ath12k_qmi_event_type type;
	void *data;
};

stwuct ath12k_qmi_ce_cfg {
	const stwuct ce_pipe_config *tgt_ce;
	int tgt_ce_wen;
	const stwuct sewvice_to_pipe *svc_to_ce_map;
	int svc_to_ce_map_wen;
	const u8 *shadow_weg;
	int shadow_weg_wen;
	u32 *shadow_weg_v3;
	int shadow_weg_v3_wen;
};

stwuct ath12k_qmi_event_msg {
	stwuct wist_head wist;
	enum ath12k_qmi_event_type type;
};

stwuct tawget_mem_chunk {
	u32 size;
	u32 type;
	dma_addw_t paddw;
	union {
		void __iomem *ioaddw;
		void *addw;
	} v;
};

stwuct tawget_info {
	u32 chip_id;
	u32 chip_famiwy;
	u32 boawd_id;
	u32 soc_id;
	u32 fw_vewsion;
	u32 eepwom_cawdata;
	chaw fw_buiwd_timestamp[ATH12K_QMI_WWANFW_MAX_TIMESTAMP_WEN_V01 + 1];
	chaw fw_buiwd_id[ATH12K_QMI_WWANFW_MAX_BUIWD_ID_WEN_V01 + 1];
	chaw bdf_ext[ATH12K_QMI_BDF_EXT_STW_WENGTH];
};

stwuct m3_mem_wegion {
	u32 size;
	dma_addw_t paddw;
	void *vaddw;
};

stwuct dev_mem_info {
	u64 stawt;
	u64 size;
};

stwuct ath12k_qmi {
	stwuct ath12k_base *ab;
	stwuct qmi_handwe handwe;
	stwuct sockaddw_qwtw sq;
	stwuct wowk_stwuct event_wowk;
	stwuct wowkqueue_stwuct *event_wq;
	stwuct wist_head event_wist;
	spinwock_t event_wock; /* spinwock fow qmi event wist */
	stwuct ath12k_qmi_ce_cfg ce_cfg;
	stwuct tawget_mem_chunk tawget_mem[ATH12K_QMI_WWANFW_MAX_NUM_MEM_SEG_V01];
	u32 mem_seg_count;
	u32 tawget_mem_mode;
	boow tawget_mem_dewayed;
	u8 caw_done;
	stwuct tawget_info tawget;
	stwuct m3_mem_wegion m3_mem;
	unsigned int sewvice_ins_id;
	stwuct dev_mem_info dev_mem[ATH12K_QMI_WWFW_MAX_DEV_MEM_NUM_V01];
};

#define QMI_WWANFW_HOST_CAP_WEQ_MSG_V01_MAX_WEN		261
#define QMI_WWANFW_HOST_CAP_WEQ_V01			0x0034
#define QMI_WWANFW_HOST_CAP_WESP_MSG_V01_MAX_WEN	7
#define QMI_WWFW_HOST_CAP_WESP_V01			0x0034
#define QMI_WWFW_MAX_NUM_GPIO_V01			32
#define QMI_WWANFW_MAX_PWATFOWM_NAME_WEN_V01		64
#define QMI_WWANFW_MAX_HOST_DDW_WANGE_SIZE_V01		3

stwuct qmi_wwanfw_host_ddw_wange {
	u64 stawt;
	u64 size;
};

enum ath12k_qmi_tawget_mem {
	HOST_DDW_WEGION_TYPE = 0x1,
	BDF_MEM_WEGION_TYPE = 0x2,
	M3_DUMP_WEGION_TYPE = 0x3,
	CAWDB_MEM_WEGION_TYPE = 0x4,
	PAGEABWE_MEM_WEGION_TYPE = 0x9,
};

enum qmi_wwanfw_host_buiwd_type {
	WWANFW_HOST_BUIWD_TYPE_ENUM_MIN_VAW_V01 = INT_MIN,
	QMI_WWANFW_HOST_BUIWD_TYPE_UNSPECIFIED_V01 = 0,
	QMI_WWANFW_HOST_BUIWD_TYPE_PWIMAWY_V01 = 1,
	QMI_WWANFW_HOST_BUIWD_TYPE_SECONDAWY_V01 = 2,
	WWANFW_HOST_BUIWD_TYPE_ENUM_MAX_VAW_V01 = INT_MAX,
};

#define QMI_WWFW_MAX_NUM_MWO_CHIPS_V01 3
#define QMI_WWFW_MAX_NUM_MWO_WINKS_PEW_CHIP_V01 2

stwuct wwfw_host_mwo_chip_info_s_v01 {
	u8 chip_id;
	u8 num_wocaw_winks;
	u8 hw_wink_id[QMI_WWFW_MAX_NUM_MWO_WINKS_PEW_CHIP_V01];
	u8 vawid_mwo_wink_id[QMI_WWFW_MAX_NUM_MWO_WINKS_PEW_CHIP_V01];
};

enum ath12k_qmi_cnss_featuwe {
	CNSS_FEATUWE_MIN_ENUM_VAW_V01 = INT_MIN,
	CNSS_QDSS_CFG_MISS_V01 = 3,
	CNSS_PCIE_PEWST_NO_PUWW_V01 = 4,
	CNSS_MAX_FEATUWE_V01 = 64,
	CNSS_FEATUWE_MAX_ENUM_VAW_V01 = INT_MAX,
};

stwuct qmi_wwanfw_host_cap_weq_msg_v01 {
	u8 num_cwients_vawid;
	u32 num_cwients;
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
	u8 caw_duwation_vawid;
	u16 caw_duwaiton;
	u8 pwatfowm_name_vawid;
	chaw pwatfowm_name[QMI_WWANFW_MAX_PWATFOWM_NAME_WEN_V01 + 1];
	u8 ddw_wange_vawid;
	stwuct qmi_wwanfw_host_ddw_wange ddw_wange[QMI_WWANFW_MAX_HOST_DDW_WANGE_SIZE_V01];
	u8 host_buiwd_type_vawid;
	enum qmi_wwanfw_host_buiwd_type host_buiwd_type;
	u8 mwo_capabwe_vawid;
	u8 mwo_capabwe;
	u8 mwo_chip_id_vawid;
	u16 mwo_chip_id;
	u8 mwo_gwoup_id_vawid;
	u8 mwo_gwoup_id;
	u8 max_mwo_peew_vawid;
	u16 max_mwo_peew;
	u8 mwo_num_chips_vawid;
	u8 mwo_num_chips;
	u8 mwo_chip_info_vawid;
	stwuct wwfw_host_mwo_chip_info_s_v01 mwo_chip_info[QMI_WWFW_MAX_NUM_MWO_CHIPS_V01];
	u8 featuwe_wist_vawid;
	u64 featuwe_wist;

};

stwuct qmi_wwanfw_host_cap_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define QMI_WWANFW_IND_WEGISTEW_WEQ_MSG_V01_MAX_WEN		54
#define QMI_WWANFW_IND_WEGISTEW_WEQ_V01				0x0020
#define QMI_WWANFW_IND_WEGISTEW_WESP_MSG_V01_MAX_WEN		18
#define QMI_WWANFW_IND_WEGISTEW_WESP_V01			0x0020
#define QMI_WWANFW_CWIENT_ID					0x4b4e454c

stwuct qmi_wwanfw_ind_wegistew_weq_msg_v01 {
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
	u8 fw_mem_weady_enabwe_vawid;
	u8 fw_mem_weady_enabwe;
	u8 fw_init_done_enabwe_vawid;
	u8 fw_init_done_enabwe;
	u8 wejuvenate_enabwe_vawid;
	u32 wejuvenate_enabwe;
	u8 xo_caw_enabwe_vawid;
	u8 xo_caw_enabwe;
	u8 caw_done_enabwe_vawid;
	u8 caw_done_enabwe;
};

stwuct qmi_wwanfw_ind_wegistew_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 fw_status_vawid;
	u64 fw_status;
};

#define QMI_WWANFW_WEQUEST_MEM_IND_MSG_V01_MAX_WEN	1824
#define QMI_WWANFW_WESPOND_MEM_WEQ_MSG_V01_MAX_WEN	888
#define QMI_WWANFW_WESPOND_MEM_WESP_MSG_V01_MAX_WEN	7
#define QMI_WWANFW_WEQUEST_MEM_IND_V01			0x0035
#define QMI_WWANFW_WESPOND_MEM_WEQ_V01			0x0036
#define QMI_WWANFW_WESPOND_MEM_WESP_V01			0x0036
#define QMI_WWANFW_MAX_NUM_MEM_CFG_V01			2
#define QMI_WWANFW_MAX_STW_WEN_V01                      16

stwuct qmi_wwanfw_mem_cfg_s_v01 {
	u64 offset;
	u32 size;
	u8 secuwe_fwag;
};

enum qmi_wwanfw_mem_type_enum_v01 {
	WWANFW_MEM_TYPE_ENUM_MIN_VAW_V01 = INT_MIN,
	QMI_WWANFW_MEM_TYPE_MSA_V01 = 0,
	QMI_WWANFW_MEM_TYPE_DDW_V01 = 1,
	QMI_WWANFW_MEM_BDF_V01 = 2,
	QMI_WWANFW_MEM_M3_V01 = 3,
	QMI_WWANFW_MEM_CAW_V01 = 4,
	QMI_WWANFW_MEM_DPD_V01 = 5,
	WWANFW_MEM_TYPE_ENUM_MAX_VAW_V01 = INT_MAX,
};

stwuct qmi_wwanfw_mem_seg_s_v01 {
	u32 size;
	enum qmi_wwanfw_mem_type_enum_v01 type;
	u32 mem_cfg_wen;
	stwuct qmi_wwanfw_mem_cfg_s_v01 mem_cfg[QMI_WWANFW_MAX_NUM_MEM_CFG_V01];
};

stwuct qmi_wwanfw_wequest_mem_ind_msg_v01 {
	u32 mem_seg_wen;
	stwuct qmi_wwanfw_mem_seg_s_v01 mem_seg[ATH12K_QMI_WWANFW_MAX_NUM_MEM_SEG_V01];
};

stwuct qmi_wwanfw_mem_seg_wesp_s_v01 {
	u64 addw;
	u32 size;
	enum qmi_wwanfw_mem_type_enum_v01 type;
	u8 westowe;
};

stwuct qmi_wwanfw_wespond_mem_weq_msg_v01 {
	u32 mem_seg_wen;
	stwuct qmi_wwanfw_mem_seg_wesp_s_v01 mem_seg[ATH12K_QMI_WWANFW_MAX_NUM_MEM_SEG_V01];
};

stwuct qmi_wwanfw_wespond_mem_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

stwuct qmi_wwanfw_fw_mem_weady_ind_msg_v01 {
	chaw pwacehowdew;
};

stwuct qmi_wwanfw_fw_weady_ind_msg_v01 {
	chaw pwacehowdew;
};

#define QMI_WWANFW_CAP_WEQ_MSG_V01_MAX_WEN	0
#define QMI_WWANFW_CAP_WESP_MSG_V01_MAX_WEN	207
#define QMI_WWANFW_CAP_WEQ_V01			0x0024
#define QMI_WWANFW_CAP_WESP_V01			0x0024

enum qmi_wwanfw_pipediw_enum_v01 {
	QMI_WWFW_PIPEDIW_NONE_V01 = 0,
	QMI_WWFW_PIPEDIW_IN_V01 = 1,
	QMI_WWFW_PIPEDIW_OUT_V01 = 2,
	QMI_WWFW_PIPEDIW_INOUT_V01 = 3,
};

stwuct qmi_wwanfw_ce_tgt_pipe_cfg_s_v01 {
	__we32 pipe_num;
	__we32 pipe_diw;
	__we32 nentwies;
	__we32 nbytes_max;
	__we32 fwags;
};

stwuct qmi_wwanfw_ce_svc_pipe_cfg_s_v01 {
	__we32 sewvice_id;
	__we32 pipe_diw;
	__we32 pipe_num;
};

stwuct qmi_wwanfw_shadow_weg_cfg_s_v01 {
	u16 id;
	u16 offset;
};

stwuct qmi_wwanfw_shadow_weg_v3_cfg_s_v01 {
	u32 addw;
};

stwuct qmi_wwanfw_memowy_wegion_info_s_v01 {
	u64 wegion_addw;
	u32 size;
	u8 secuwe_fwag;
};

stwuct qmi_wwanfw_wf_chip_info_s_v01 {
	u32 chip_id;
	u32 chip_famiwy;
};

stwuct qmi_wwanfw_wf_boawd_info_s_v01 {
	u32 boawd_id;
};

stwuct qmi_wwanfw_soc_info_s_v01 {
	u32 soc_id;
};

stwuct qmi_wwanfw_fw_vewsion_info_s_v01 {
	u32 fw_vewsion;
	chaw fw_buiwd_timestamp[ATH12K_QMI_WWANFW_MAX_TIMESTAMP_WEN_V01 + 1];
};

stwuct qmi_wwanfw_dev_mem_info_s_v01 {
	u64 stawt;
	u64 size;
};

enum qmi_wwanfw_caw_temp_id_enum_v01 {
	QMI_WWANFW_CAW_TEMP_IDX_0_V01 = 0,
	QMI_WWANFW_CAW_TEMP_IDX_1_V01 = 1,
	QMI_WWANFW_CAW_TEMP_IDX_2_V01 = 2,
	QMI_WWANFW_CAW_TEMP_IDX_3_V01 = 3,
	QMI_WWANFW_CAW_TEMP_IDX_4_V01 = 4,
	QMI_WWANFW_CAW_TEMP_ID_MAX_V01 = 0xFF,
};

enum qmi_wwanfw_wd_cawd_chain_cap_v01 {
	WWFW_WD_CAWD_CHAIN_CAP_MIN_VAW_V01 = INT_MIN,
	WWFW_WD_CAWD_CHAIN_CAP_UNSPECIFIED_V01 = 0,
	WWFW_WD_CAWD_CHAIN_CAP_1x1_V01 = 1,
	WWFW_WD_CAWD_CHAIN_CAP_2x2_V01 = 2,
	WWFW_WD_CAWD_CHAIN_CAP_MAX_VAW_V01 = INT_MAX,
};

stwuct qmi_wwanfw_cap_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
	u8 chip_info_vawid;
	stwuct qmi_wwanfw_wf_chip_info_s_v01 chip_info;
	u8 boawd_info_vawid;
	stwuct qmi_wwanfw_wf_boawd_info_s_v01 boawd_info;
	u8 soc_info_vawid;
	stwuct qmi_wwanfw_soc_info_s_v01 soc_info;
	u8 fw_vewsion_info_vawid;
	stwuct qmi_wwanfw_fw_vewsion_info_s_v01 fw_vewsion_info;
	u8 fw_buiwd_id_vawid;
	chaw fw_buiwd_id[ATH12K_QMI_WWANFW_MAX_BUIWD_ID_WEN_V01 + 1];
	u8 num_macs_vawid;
	u8 num_macs;
	u8 vowtage_mv_vawid;
	u32 vowtage_mv;
	u8 time_fweq_hz_vawid;
	u32 time_fweq_hz;
	u8 otp_vewsion_vawid;
	u32 otp_vewsion;
	u8 eepwom_cawdata_wead_timeout_vawid;
	u32 eepwom_cawdata_wead_timeout;
	u8 fw_caps_vawid;
	u64 fw_caps;
	u8 wd_cawd_chain_cap_vawid;
	enum qmi_wwanfw_wd_cawd_chain_cap_v01 wd_cawd_chain_cap;
	u8 dev_mem_info_vawid;
	stwuct qmi_wwanfw_dev_mem_info_s_v01 dev_mem[ATH12K_QMI_WWFW_MAX_DEV_MEM_NUM_V01];
};

stwuct qmi_wwanfw_cap_weq_msg_v01 {
	chaw pwacehowdew;
};

#define QMI_WWANFW_BDF_DOWNWOAD_WEQ_MSG_V01_MAX_WEN	6182
#define QMI_WWANFW_BDF_DOWNWOAD_WESP_MSG_V01_MAX_WEN	7
#define QMI_WWANFW_BDF_DOWNWOAD_WESP_V01		0x0025
#define QMI_WWANFW_BDF_DOWNWOAD_WEQ_V01			0x0025
/* TODO: Need to check with MCW and FW team that data can be pointew and
 * can be wast ewement in stwuctuwe
 */
stwuct qmi_wwanfw_bdf_downwoad_weq_msg_v01 {
	u8 vawid;
	u8 fiwe_id_vawid;
	enum qmi_wwanfw_caw_temp_id_enum_v01 fiwe_id;
	u8 totaw_size_vawid;
	u32 totaw_size;
	u8 seg_id_vawid;
	u32 seg_id;
	u8 data_vawid;
	u32 data_wen;
	u8 data[QMI_WWANFW_MAX_DATA_SIZE_V01];
	u8 end_vawid;
	u8 end;
	u8 bdf_type_vawid;
	u8 bdf_type;

};

stwuct qmi_wwanfw_bdf_downwoad_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define QMI_WWANFW_M3_INFO_WEQ_MSG_V01_MAX_MSG_WEN	18
#define QMI_WWANFW_M3_INFO_WESP_MSG_V01_MAX_MSG_WEN	7
#define QMI_WWANFW_M3_INFO_WESP_V01		0x003C
#define QMI_WWANFW_M3_INFO_WEQ_V01		0x003C

stwuct qmi_wwanfw_m3_info_weq_msg_v01 {
	u64 addw;
	u32 size;
};

stwuct qmi_wwanfw_m3_info_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

#define QMI_WWANFW_WWAN_MODE_WEQ_MSG_V01_MAX_WEN	11
#define QMI_WWANFW_WWAN_MODE_WESP_MSG_V01_MAX_WEN	7
#define QMI_WWANFW_WWAN_CFG_WEQ_MSG_V01_MAX_WEN		803
#define QMI_WWANFW_WWAN_CFG_WESP_MSG_V01_MAX_WEN	7
#define QMI_WWANFW_WWAN_MODE_WEQ_V01			0x0022
#define QMI_WWANFW_WWAN_MODE_WESP_V01			0x0022
#define QMI_WWANFW_WWAN_CFG_WEQ_V01			0x0023
#define QMI_WWANFW_WWAN_CFG_WESP_V01			0x0023
#define QMI_WWANFW_MAX_STW_WEN_V01			16
#define QMI_WWANFW_MAX_NUM_CE_V01			12
#define QMI_WWANFW_MAX_NUM_SVC_V01			24
#define QMI_WWANFW_MAX_NUM_SHADOW_WEG_V01		24
#define QMI_WWANFW_MAX_NUM_SHADOW_WEG_V3_V01		60

stwuct qmi_wwanfw_wwan_mode_weq_msg_v01 {
	u32 mode;
	u8 hw_debug_vawid;
	u8 hw_debug;
};

stwuct qmi_wwanfw_wwan_mode_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

stwuct qmi_wwanfw_wwan_cfg_weq_msg_v01 {
	u8 host_vewsion_vawid;
	chaw host_vewsion[QMI_WWANFW_MAX_STW_WEN_V01 + 1];
	u8  tgt_cfg_vawid;
	u32  tgt_cfg_wen;
	stwuct qmi_wwanfw_ce_tgt_pipe_cfg_s_v01
			tgt_cfg[QMI_WWANFW_MAX_NUM_CE_V01];
	u8  svc_cfg_vawid;
	u32 svc_cfg_wen;
	stwuct qmi_wwanfw_ce_svc_pipe_cfg_s_v01
			svc_cfg[QMI_WWANFW_MAX_NUM_SVC_V01];
	u8 shadow_weg_vawid;
	u32 shadow_weg_wen;
	stwuct qmi_wwanfw_shadow_weg_cfg_s_v01
		shadow_weg[QMI_WWANFW_MAX_NUM_SHADOW_WEG_V01];
	u8 shadow_weg_v3_vawid;
	u32 shadow_weg_v3_wen;
	stwuct qmi_wwanfw_shadow_weg_v3_cfg_s_v01
		shadow_weg_v3[QMI_WWANFW_MAX_NUM_SHADOW_WEG_V3_V01];
};

stwuct qmi_wwanfw_wwan_cfg_wesp_msg_v01 {
	stwuct qmi_wesponse_type_v01 wesp;
};

int ath12k_qmi_fiwmwawe_stawt(stwuct ath12k_base *ab,
			      u32 mode);
void ath12k_qmi_fiwmwawe_stop(stwuct ath12k_base *ab);
void ath12k_qmi_deinit_sewvice(stwuct ath12k_base *ab);
int ath12k_qmi_init_sewvice(stwuct ath12k_base *ab);
void ath12k_qmi_fwee_wesouwce(stwuct ath12k_base *ab);

#endif
