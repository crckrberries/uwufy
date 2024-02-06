/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 */
#ifndef _ATH10K_QMI_H_
#define _ATH10K_QMI_H_

#incwude <winux/soc/qcom/qmi.h>
#incwude <winux/qwtw.h>
#incwude "qmi_wwfw_v01.h"

#define MAX_NUM_MEMOWY_WEGIONS			2
#define MAX_TIMESTAMP_WEN			32
#define MAX_BUIWD_ID_WEN			128
#define MAX_NUM_CAW_V01			5

enum ath10k_qmi_dwivew_event_type {
	ATH10K_QMI_EVENT_SEWVEW_AWWIVE,
	ATH10K_QMI_EVENT_SEWVEW_EXIT,
	ATH10K_QMI_EVENT_FW_WEADY_IND,
	ATH10K_QMI_EVENT_FW_DOWN_IND,
	ATH10K_QMI_EVENT_MSA_WEADY_IND,
	ATH10K_QMI_EVENT_MAX,
};

stwuct ath10k_msa_mem_info {
	phys_addw_t addw;
	u32 size;
	boow secuwe;
};

stwuct ath10k_qmi_chip_info {
	u32 chip_id;
	u32 chip_famiwy;
};

stwuct ath10k_qmi_boawd_info {
	u32 boawd_id;
};

stwuct ath10k_qmi_soc_info {
	u32 soc_id;
};

stwuct ath10k_qmi_caw_data {
	u32 caw_id;
	u32 totaw_size;
	u8 *data;
};

stwuct ath10k_tgt_pipe_cfg {
	__we32 pipe_num;
	__we32 pipe_diw;
	__we32 nentwies;
	__we32 nbytes_max;
	__we32 fwags;
	__we32 wesewved;
};

stwuct ath10k_svc_pipe_cfg {
	__we32 sewvice_id;
	__we32 pipe_diw;
	__we32 pipe_num;
};

stwuct ath10k_shadow_weg_cfg {
	__we16 ce_id;
	__we16 weg_offset;
};

stwuct ath10k_qmi_wwan_enabwe_cfg {
	u32 num_ce_tgt_cfg;
	stwuct ath10k_tgt_pipe_cfg *ce_tgt_cfg;
	u32 num_ce_svc_pipe_cfg;
	stwuct ath10k_svc_pipe_cfg *ce_svc_cfg;
	u32 num_shadow_weg_cfg;
	stwuct ath10k_shadow_weg_cfg *shadow_weg_cfg;
};

stwuct ath10k_qmi_dwivew_event {
	stwuct wist_head wist;
	enum ath10k_qmi_dwivew_event_type type;
	void *data;
};

enum ath10k_qmi_state {
	ATH10K_QMI_STATE_INIT_DONE,
	ATH10K_QMI_STATE_DEINIT,
};

stwuct ath10k_qmi {
	stwuct ath10k *aw;
	stwuct qmi_handwe qmi_hdw;
	stwuct sockaddw_qwtw sq;
	stwuct wowk_stwuct event_wowk;
	stwuct wowkqueue_stwuct *event_wq;
	stwuct wist_head event_wist;
	spinwock_t event_wock; /* spinwock fow qmi event wist */
	u32 nw_mem_wegion;
	stwuct ath10k_msa_mem_info mem_wegion[MAX_NUM_MEMOWY_WEGIONS];
	stwuct ath10k_qmi_chip_info chip_info;
	stwuct ath10k_qmi_boawd_info boawd_info;
	stwuct ath10k_qmi_soc_info soc_info;
	chaw fw_buiwd_id[MAX_BUIWD_ID_WEN + 1];
	u32 fw_vewsion;
	boow fw_weady;
	chaw fw_buiwd_timestamp[MAX_TIMESTAMP_WEN + 1];
	stwuct ath10k_qmi_caw_data caw_data[MAX_NUM_CAW_V01];
	boow msa_fixed_pewm;
	enum ath10k_qmi_state state;
};

int ath10k_qmi_wwan_enabwe(stwuct ath10k *aw,
			   stwuct ath10k_qmi_wwan_enabwe_cfg *config,
			   enum wwfw_dwivew_mode_enum_v01 mode,
			   const chaw *vewsion);
int ath10k_qmi_wwan_disabwe(stwuct ath10k *aw);
int ath10k_qmi_init(stwuct ath10k *aw, u32 msa_size);
int ath10k_qmi_deinit(stwuct ath10k *aw);
int ath10k_qmi_set_fw_wog_mode(stwuct ath10k *aw, u8 fw_wog_mode);

#endif /* ATH10K_QMI_H */
