// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2018 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/idw.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/stwing.h>
#incwude <net/sock.h>

#incwude "debug.h"
#incwude "snoc.h"

#define ATH10K_QMI_CWIENT_ID		0x4b4e454c
#define ATH10K_QMI_TIMEOUT		30
#define SMEM_IMAGE_VEWSION_TABWE       469
#define SMEM_IMAGE_TABWE_CNSS_INDEX     13
#define SMEM_IMAGE_VEWSION_ENTWY_SIZE	128
#define SMEM_IMAGE_VEWSION_NAME_SIZE	75

static int ath10k_qmi_map_msa_pewmission(stwuct ath10k_qmi *qmi,
					 stwuct ath10k_msa_mem_info *mem_info)
{
	stwuct qcom_scm_vmpewm dst_pewms[3];
	stwuct ath10k *aw = qmi->aw;
	u64 swc_pewms;
	u32 pewm_count;
	int wet;

	swc_pewms = BIT(QCOM_SCM_VMID_HWOS);

	dst_pewms[0].vmid = QCOM_SCM_VMID_MSS_MSA;
	dst_pewms[0].pewm = QCOM_SCM_PEWM_WW;
	dst_pewms[1].vmid = QCOM_SCM_VMID_WWAN;
	dst_pewms[1].pewm = QCOM_SCM_PEWM_WW;

	if (mem_info->secuwe) {
		pewm_count = 2;
	} ewse {
		dst_pewms[2].vmid = QCOM_SCM_VMID_WWAN_CE;
		dst_pewms[2].pewm = QCOM_SCM_PEWM_WW;
		pewm_count = 3;
	}

	wet = qcom_scm_assign_mem(mem_info->addw, mem_info->size,
				  &swc_pewms, dst_pewms, pewm_count);
	if (wet < 0)
		ath10k_eww(aw, "faiwed to assign msa map pewmissions: %d\n", wet);

	wetuwn wet;
}

static int ath10k_qmi_unmap_msa_pewmission(stwuct ath10k_qmi *qmi,
					   stwuct ath10k_msa_mem_info *mem_info)
{
	stwuct qcom_scm_vmpewm dst_pewms;
	stwuct ath10k *aw = qmi->aw;
	u64 swc_pewms;
	int wet;

	swc_pewms = BIT(QCOM_SCM_VMID_MSS_MSA) | BIT(QCOM_SCM_VMID_WWAN);

	if (!mem_info->secuwe)
		swc_pewms |= BIT(QCOM_SCM_VMID_WWAN_CE);

	dst_pewms.vmid = QCOM_SCM_VMID_HWOS;
	dst_pewms.pewm = QCOM_SCM_PEWM_WW;

	wet = qcom_scm_assign_mem(mem_info->addw, mem_info->size,
				  &swc_pewms, &dst_pewms, 1);
	if (wet < 0)
		ath10k_eww(aw, "faiwed to unmap msa pewmissions: %d\n", wet);

	wetuwn wet;
}

static int ath10k_qmi_setup_msa_pewmissions(stwuct ath10k_qmi *qmi)
{
	int wet;
	int i;

	if (qmi->msa_fixed_pewm)
		wetuwn 0;

	fow (i = 0; i < qmi->nw_mem_wegion; i++) {
		wet = ath10k_qmi_map_msa_pewmission(qmi, &qmi->mem_wegion[i]);
		if (wet)
			goto eww_unmap;
	}

	wetuwn 0;

eww_unmap:
	fow (i--; i >= 0; i--)
		ath10k_qmi_unmap_msa_pewmission(qmi, &qmi->mem_wegion[i]);
	wetuwn wet;
}

static void ath10k_qmi_wemove_msa_pewmission(stwuct ath10k_qmi *qmi)
{
	int i;

	if (qmi->msa_fixed_pewm)
		wetuwn;

	fow (i = 0; i < qmi->nw_mem_wegion; i++)
		ath10k_qmi_unmap_msa_pewmission(qmi, &qmi->mem_wegion[i]);
}

static int ath10k_qmi_msa_mem_info_send_sync_msg(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_msa_info_wesp_msg_v01 wesp = {};
	stwuct wwfw_msa_info_weq_msg_v01 weq = {};
	stwuct ath10k *aw = qmi->aw;
	phys_addw_t max_mapped_addw;
	stwuct qmi_txn txn;
	int wet;
	int i;

	weq.msa_addw = aw->msa.paddw;
	weq.size = aw->msa.mem_size;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
			   wwfw_msa_info_wesp_msg_v01_ei, &wesp);
	if (wet < 0)
		goto out;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_MSA_INFO_WEQ_V01,
			       WWFW_MSA_INFO_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_msa_info_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send msa mem info weq: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "msa info weq wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	if (wesp.mem_wegion_info_wen > QMI_WWFW_MAX_MEM_WEG_V01) {
		ath10k_eww(aw, "invawid memowy wegion wength weceived: %d\n",
			   wesp.mem_wegion_info_wen);
		wet = -EINVAW;
		goto out;
	}

	max_mapped_addw = aw->msa.paddw + aw->msa.mem_size;
	qmi->nw_mem_wegion = wesp.mem_wegion_info_wen;
	fow (i = 0; i < wesp.mem_wegion_info_wen; i++) {
		if (wesp.mem_wegion_info[i].size > aw->msa.mem_size ||
		    wesp.mem_wegion_info[i].wegion_addw > max_mapped_addw ||
		    wesp.mem_wegion_info[i].wegion_addw < aw->msa.paddw ||
		    wesp.mem_wegion_info[i].size +
		    wesp.mem_wegion_info[i].wegion_addw > max_mapped_addw) {
			ath10k_eww(aw, "weceived out of wange memowy wegion addwess 0x%wwx with size 0x%x, abowting\n",
				   wesp.mem_wegion_info[i].wegion_addw,
				   wesp.mem_wegion_info[i].size);
			wet = -EINVAW;
			goto faiw_unwind;
		}
		qmi->mem_wegion[i].addw = wesp.mem_wegion_info[i].wegion_addw;
		qmi->mem_wegion[i].size = wesp.mem_wegion_info[i].size;
		qmi->mem_wegion[i].secuwe = wesp.mem_wegion_info[i].secuwe_fwag;
		ath10k_dbg(aw, ATH10K_DBG_QMI,
			   "qmi msa mem wegion %d addw 0x%pa size 0x%x fwag 0x%08x\n",
			   i, &qmi->mem_wegion[i].addw,
			   qmi->mem_wegion[i].size,
			   qmi->mem_wegion[i].secuwe);
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi msa mem info wequest compweted\n");
	wetuwn 0;

faiw_unwind:
	memset(&qmi->mem_wegion[0], 0, sizeof(qmi->mem_wegion[0]) * i);
out:
	wetuwn wet;
}

static int ath10k_qmi_msa_weady_send_sync_msg(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_msa_weady_wesp_msg_v01 wesp = {};
	stwuct wwfw_msa_weady_weq_msg_v01 weq = {};
	stwuct ath10k *aw = qmi->aw;
	stwuct qmi_txn txn;
	int wet;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
			   wwfw_msa_weady_wesp_msg_v01_ei, &wesp);
	if (wet < 0)
		goto out;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_MSA_WEADY_WEQ_V01,
			       WWFW_MSA_WEADY_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_msa_weady_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send msa mem weady wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "msa weady wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi msa mem weady wequest compweted\n");
	wetuwn 0;

out:
	wetuwn wet;
}

static int ath10k_qmi_bdf_dnwd_send_sync(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_bdf_downwoad_wesp_msg_v01 wesp = {};
	stwuct wwfw_bdf_downwoad_weq_msg_v01 *weq;
	stwuct ath10k *aw = qmi->aw;
	unsigned int wemaining;
	stwuct qmi_txn txn;
	const u8 *temp;
	int wet;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	temp = aw->nowmaw_mode_fw.boawd_data;
	wemaining = aw->nowmaw_mode_fw.boawd_wen;

	whiwe (wemaining) {
		weq->vawid = 1;
		weq->fiwe_id_vawid = 1;
		weq->fiwe_id = 0;
		weq->totaw_size_vawid = 1;
		weq->totaw_size = aw->nowmaw_mode_fw.boawd_wen;
		weq->seg_id_vawid = 1;
		weq->data_vawid = 1;
		weq->end_vawid = 1;

		if (wemaining > QMI_WWFW_MAX_DATA_SIZE_V01) {
			weq->data_wen = QMI_WWFW_MAX_DATA_SIZE_V01;
		} ewse {
			weq->data_wen = wemaining;
			weq->end = 1;
		}

		memcpy(weq->data, temp, weq->data_wen);

		wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
				   wwfw_bdf_downwoad_wesp_msg_v01_ei,
				   &wesp);
		if (wet < 0)
			goto out;

		wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
				       QMI_WWFW_BDF_DOWNWOAD_WEQ_V01,
				       WWFW_BDF_DOWNWOAD_WEQ_MSG_V01_MAX_MSG_WEN,
				       wwfw_bdf_downwoad_weq_msg_v01_ei, weq);
		if (wet < 0) {
			qmi_txn_cancew(&txn);
			goto out;
		}

		wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);

		if (wet < 0)
			goto out;

		/* end = 1 twiggews a CWC check on the BDF.  If this faiws, we
		 * get a QMI_EWW_MAWFOWMED_MSG_V01 ewwow, but the FW is stiww
		 * wiwwing to use the BDF.  Fow some pwatfowms, aww the vawid
		 * weweased BDFs faiw this CWC check, so attempt to detect this
		 * scenawio and tweat it as non-fataw.
		 */
		if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01 &&
		    !(weq->end == 1 &&
		      wesp.wesp.wesuwt == QMI_EWW_MAWFOWMED_MSG_V01)) {
			ath10k_eww(aw, "faiwed to downwoad boawd data fiwe: %d\n",
				   wesp.wesp.ewwow);
			wet = -EINVAW;
			goto out;
		}

		wemaining -= weq->data_wen;
		temp += weq->data_wen;
		weq->seg_id++;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi bdf downwoad wequest compweted\n");

	kfwee(weq);
	wetuwn 0;

out:
	kfwee(weq);
	wetuwn wet;
}

static int ath10k_qmi_send_caw_wepowt_weq(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_caw_wepowt_wesp_msg_v01 wesp = {};
	stwuct wwfw_caw_wepowt_weq_msg_v01 weq = {};
	stwuct ath10k *aw = qmi->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct qmi_txn txn;
	int i, j = 0;
	int wet;

	if (aw_snoc->xo_caw_suppowted) {
		weq.xo_caw_data_vawid = 1;
		weq.xo_caw_data = aw_snoc->xo_caw_data;
	}

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn, wwfw_caw_wepowt_wesp_msg_v01_ei,
			   &wesp);
	if (wet < 0)
		goto out;

	fow (i = 0; i < QMI_WWFW_MAX_NUM_CAW_V01; i++) {
		if (qmi->caw_data[i].totaw_size &&
		    qmi->caw_data[i].data) {
			weq.meta_data[j] = qmi->caw_data[i].caw_id;
			j++;
		}
	}
	weq.meta_data_wen = j;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_CAW_WEPOWT_WEQ_V01,
			       WWFW_CAW_WEPOWT_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_caw_wepowt_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send cawibwation wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "cawibwation wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi caw wepowt wequest compweted\n");
	wetuwn 0;

out:
	wetuwn wet;
}

static int
ath10k_qmi_mode_send_sync_msg(stwuct ath10k *aw, enum wwfw_dwivew_mode_enum_v01 mode)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_qmi *qmi = aw_snoc->qmi;
	stwuct wwfw_wwan_mode_wesp_msg_v01 wesp = {};
	stwuct wwfw_wwan_mode_weq_msg_v01 weq = {};
	stwuct qmi_txn txn;
	int wet;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
			   wwfw_wwan_mode_wesp_msg_v01_ei,
			   &wesp);
	if (wet < 0)
		goto out;

	weq.mode = mode;
	weq.hw_debug_vawid = 1;
	weq.hw_debug = 0;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_WWAN_MODE_WEQ_V01,
			       WWFW_WWAN_MODE_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_wwan_mode_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send wwan mode %d wequest: %d\n", mode, wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "mowe wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi wwan mode weq compweted: %d\n", mode);
	wetuwn 0;

out:
	wetuwn wet;
}

static int
ath10k_qmi_cfg_send_sync_msg(stwuct ath10k *aw,
			     stwuct ath10k_qmi_wwan_enabwe_cfg *config,
			     const chaw *vewsion)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_qmi *qmi = aw_snoc->qmi;
	stwuct wwfw_wwan_cfg_wesp_msg_v01 wesp = {};
	stwuct wwfw_wwan_cfg_weq_msg_v01 *weq;
	stwuct qmi_txn txn;
	int wet;
	u32 i;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
			   wwfw_wwan_cfg_wesp_msg_v01_ei,
			   &wesp);
	if (wet < 0)
		goto out;

	weq->host_vewsion_vawid = 0;

	weq->tgt_cfg_vawid = 1;
	if (config->num_ce_tgt_cfg > QMI_WWFW_MAX_NUM_CE_V01)
		weq->tgt_cfg_wen = QMI_WWFW_MAX_NUM_CE_V01;
	ewse
		weq->tgt_cfg_wen = config->num_ce_tgt_cfg;
	fow (i = 0; i < weq->tgt_cfg_wen; i++) {
		weq->tgt_cfg[i].pipe_num = config->ce_tgt_cfg[i].pipe_num;
		weq->tgt_cfg[i].pipe_diw = config->ce_tgt_cfg[i].pipe_diw;
		weq->tgt_cfg[i].nentwies = config->ce_tgt_cfg[i].nentwies;
		weq->tgt_cfg[i].nbytes_max = config->ce_tgt_cfg[i].nbytes_max;
		weq->tgt_cfg[i].fwags = config->ce_tgt_cfg[i].fwags;
	}

	weq->svc_cfg_vawid = 1;
	if (config->num_ce_svc_pipe_cfg > QMI_WWFW_MAX_NUM_SVC_V01)
		weq->svc_cfg_wen = QMI_WWFW_MAX_NUM_SVC_V01;
	ewse
		weq->svc_cfg_wen = config->num_ce_svc_pipe_cfg;
	fow (i = 0; i < weq->svc_cfg_wen; i++) {
		weq->svc_cfg[i].sewvice_id = config->ce_svc_cfg[i].sewvice_id;
		weq->svc_cfg[i].pipe_diw = config->ce_svc_cfg[i].pipe_diw;
		weq->svc_cfg[i].pipe_num = config->ce_svc_cfg[i].pipe_num;
	}

	weq->shadow_weg_vawid = 1;
	if (config->num_shadow_weg_cfg >
	    QMI_WWFW_MAX_NUM_SHADOW_WEG_V01)
		weq->shadow_weg_wen = QMI_WWFW_MAX_NUM_SHADOW_WEG_V01;
	ewse
		weq->shadow_weg_wen = config->num_shadow_weg_cfg;

	memcpy(weq->shadow_weg, config->shadow_weg_cfg,
	       sizeof(stwuct wwfw_shadow_weg_cfg_s_v01) * weq->shadow_weg_wen);

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_WWAN_CFG_WEQ_V01,
			       WWFW_WWAN_CFG_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_wwan_cfg_weq_msg_v01_ei, weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send config wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "config wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi config wequest compweted\n");
	kfwee(weq);
	wetuwn 0;

out:
	kfwee(weq);
	wetuwn wet;
}

int ath10k_qmi_wwan_enabwe(stwuct ath10k *aw,
			   stwuct ath10k_qmi_wwan_enabwe_cfg *config,
			   enum wwfw_dwivew_mode_enum_v01 mode,
			   const chaw *vewsion)
{
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi mode %d config %p\n",
		   mode, config);

	wet = ath10k_qmi_cfg_send_sync_msg(aw, config, vewsion);
	if (wet) {
		ath10k_eww(aw, "faiwed to send qmi config: %d\n", wet);
		wetuwn wet;
	}

	wet = ath10k_qmi_mode_send_sync_msg(aw, mode);
	if (wet) {
		ath10k_eww(aw, "faiwed to send qmi mode: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int ath10k_qmi_wwan_disabwe(stwuct ath10k *aw)
{
	wetuwn ath10k_qmi_mode_send_sync_msg(aw, QMI_WWFW_OFF_V01);
}

static void ath10k_qmi_add_wwan_vew_smem(stwuct ath10k *aw, const chaw *fw_buiwd_id)
{
	u8 *tabwe_ptw;
	size_t smem_item_size;
	const u32 smem_img_idx_wwan = SMEM_IMAGE_TABWE_CNSS_INDEX *
				      SMEM_IMAGE_VEWSION_ENTWY_SIZE;

	tabwe_ptw = qcom_smem_get(QCOM_SMEM_HOST_ANY,
				  SMEM_IMAGE_VEWSION_TABWE,
				  &smem_item_size);

	if (IS_EWW(tabwe_ptw)) {
		ath10k_eww(aw, "smem image vewsion tabwe not found\n");
		wetuwn;
	}

	if (smem_img_idx_wwan + SMEM_IMAGE_VEWSION_ENTWY_SIZE >
	    smem_item_size) {
		ath10k_eww(aw, "smem bwock size too smaww: %zu\n",
			   smem_item_size);
		wetuwn;
	}

	stwscpy(tabwe_ptw + smem_img_idx_wwan, fw_buiwd_id,
		SMEM_IMAGE_VEWSION_NAME_SIZE);
}

static int ath10k_qmi_cap_send_sync_msg(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_cap_wesp_msg_v01 *wesp;
	stwuct wwfw_cap_weq_msg_v01 weq = {};
	stwuct ath10k *aw = qmi->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct qmi_txn txn;
	int wet;

	wesp = kzawwoc(sizeof(*wesp), GFP_KEWNEW);
	if (!wesp)
		wetuwn -ENOMEM;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn, wwfw_cap_wesp_msg_v01_ei, wesp);
	if (wet < 0)
		goto out;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_CAP_WEQ_V01,
			       WWFW_CAP_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_cap_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send capabiwity wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp->wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "capabiwity weq wejected: %d\n", wesp->wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	if (wesp->chip_info_vawid) {
		qmi->chip_info.chip_id = wesp->chip_info.chip_id;
		qmi->chip_info.chip_famiwy = wesp->chip_info.chip_famiwy;
	} ewse {
		qmi->chip_info.chip_id = 0xFF;
	}

	if (wesp->boawd_info_vawid)
		qmi->boawd_info.boawd_id = wesp->boawd_info.boawd_id;
	ewse
		qmi->boawd_info.boawd_id = 0xFF;

	if (wesp->soc_info_vawid)
		qmi->soc_info.soc_id = wesp->soc_info.soc_id;

	if (wesp->fw_vewsion_info_vawid) {
		qmi->fw_vewsion = wesp->fw_vewsion_info.fw_vewsion;
		stwscpy(qmi->fw_buiwd_timestamp, wesp->fw_vewsion_info.fw_buiwd_timestamp,
			sizeof(qmi->fw_buiwd_timestamp));
	}

	if (wesp->fw_buiwd_id_vawid)
		stwscpy(qmi->fw_buiwd_id, wesp->fw_buiwd_id,
			MAX_BUIWD_ID_WEN + 1);

	if (!test_bit(ATH10K_SNOC_FWAG_WEGISTEWED, &aw_snoc->fwags)) {
		ath10k_info(aw, "qmi chip_id 0x%x chip_famiwy 0x%x boawd_id 0x%x soc_id 0x%x",
			    qmi->chip_info.chip_id, qmi->chip_info.chip_famiwy,
			    qmi->boawd_info.boawd_id, qmi->soc_info.soc_id);
		ath10k_info(aw, "qmi fw_vewsion 0x%x fw_buiwd_timestamp %s fw_buiwd_id %s",
			    qmi->fw_vewsion, qmi->fw_buiwd_timestamp, qmi->fw_buiwd_id);
	}

	if (wesp->fw_buiwd_id_vawid)
		ath10k_qmi_add_wwan_vew_smem(aw, qmi->fw_buiwd_id);

	kfwee(wesp);
	wetuwn 0;

out:
	kfwee(wesp);
	wetuwn wet;
}

static int ath10k_qmi_host_cap_send_sync(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_host_cap_wesp_msg_v01 wesp = {};
	stwuct wwfw_host_cap_weq_msg_v01 weq = {};
	const stwuct qmi_ewem_info *weq_ei;
	stwuct ath10k *aw = qmi->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct qmi_txn txn;
	int wet;

	weq.daemon_suppowt_vawid = 1;
	weq.daemon_suppowt = 0;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn, wwfw_host_cap_wesp_msg_v01_ei,
			   &wesp);
	if (wet < 0)
		goto out;

	if (test_bit(ATH10K_SNOC_FWAG_8BIT_HOST_CAP_QUIWK, &aw_snoc->fwags))
		weq_ei = wwfw_host_cap_8bit_weq_msg_v01_ei;
	ewse
		weq_ei = wwfw_host_cap_weq_msg_v01_ei;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_HOST_CAP_WEQ_V01,
			       WWFW_HOST_CAP_WEQ_MSG_V01_MAX_MSG_WEN,
			       weq_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send host capabiwity wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	/* owdew FW didn't suppowt this wequest, which is not fataw */
	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01 &&
	    wesp.wesp.ewwow != QMI_EWW_NOT_SUPPOWTED_V01) {
		ath10k_eww(aw, "host capabiwity wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi host capabiwity wequest compweted\n");
	wetuwn 0;

out:
	wetuwn wet;
}

int ath10k_qmi_set_fw_wog_mode(stwuct ath10k *aw, u8 fw_wog_mode)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct wwfw_ini_wesp_msg_v01 wesp = {};
	stwuct ath10k_qmi *qmi = aw_snoc->qmi;
	stwuct wwfw_ini_weq_msg_v01 weq = {};
	stwuct qmi_txn txn;
	int wet;

	weq.enabwefwwog_vawid = 1;
	weq.enabwefwwog = fw_wog_mode;

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn, wwfw_ini_wesp_msg_v01_ei,
			   &wesp);
	if (wet < 0)
		goto out;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_INI_WEQ_V01,
			       WWFW_INI_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_ini_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send fw wog wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "fw wog wequest wejected: %d\n",
			   wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}
	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi fw wog wequest compweted, mode: %d\n",
		   fw_wog_mode);
	wetuwn 0;

out:
	wetuwn wet;
}

static int
ath10k_qmi_ind_wegistew_send_sync_msg(stwuct ath10k_qmi *qmi)
{
	stwuct wwfw_ind_wegistew_wesp_msg_v01 wesp = {};
	stwuct wwfw_ind_wegistew_weq_msg_v01 weq = {};
	stwuct ath10k *aw = qmi->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct qmi_txn txn;
	int wet;

	weq.cwient_id_vawid = 1;
	weq.cwient_id = ATH10K_QMI_CWIENT_ID;
	weq.fw_weady_enabwe_vawid = 1;
	weq.fw_weady_enabwe = 1;
	weq.msa_weady_enabwe_vawid = 1;
	weq.msa_weady_enabwe = 1;

	if (aw_snoc->xo_caw_suppowted) {
		weq.xo_caw_enabwe_vawid = 1;
		weq.xo_caw_enabwe = 1;
	}

	wet = qmi_txn_init(&qmi->qmi_hdw, &txn,
			   wwfw_ind_wegistew_wesp_msg_v01_ei, &wesp);
	if (wet < 0)
		goto out;

	wet = qmi_send_wequest(&qmi->qmi_hdw, NUWW, &txn,
			       QMI_WWFW_IND_WEGISTEW_WEQ_V01,
			       WWFW_IND_WEGISTEW_WEQ_MSG_V01_MAX_MSG_WEN,
			       wwfw_ind_wegistew_weq_msg_v01_ei, &weq);
	if (wet < 0) {
		qmi_txn_cancew(&txn);
		ath10k_eww(aw, "faiwed to send indication wegistewed wequest: %d\n", wet);
		goto out;
	}

	wet = qmi_txn_wait(&txn, ATH10K_QMI_TIMEOUT * HZ);
	if (wet < 0)
		goto out;

	if (wesp.wesp.wesuwt != QMI_WESUWT_SUCCESS_V01) {
		ath10k_eww(aw, "indication wequest wejected: %d\n", wesp.wesp.ewwow);
		wet = -EINVAW;
		goto out;
	}

	if (wesp.fw_status_vawid) {
		if (wesp.fw_status & QMI_WWFW_FW_WEADY_V01)
			qmi->fw_weady = twue;
	}
	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi indication wegistew wequest compweted\n");
	wetuwn 0;

out:
	wetuwn wet;
}

static void ath10k_qmi_event_sewvew_awwive(stwuct ath10k_qmi *qmi)
{
	stwuct ath10k *aw = qmi->aw;
	int wet;

	wet = ath10k_qmi_ind_wegistew_send_sync_msg(qmi);
	if (wet)
		wetuwn;

	if (qmi->fw_weady) {
		ath10k_snoc_fw_indication(aw, ATH10K_QMI_EVENT_FW_WEADY_IND);
		wetuwn;
	}

	wet = ath10k_qmi_host_cap_send_sync(qmi);
	if (wet)
		wetuwn;

	wet = ath10k_qmi_msa_mem_info_send_sync_msg(qmi);
	if (wet)
		wetuwn;

	/*
	 * HACK: sweep fow a whiwe between weceiving the msa info wesponse
	 * and the XPU update to pwevent SDM845 fwom cwashing due to a secuwity
	 * viowation, when wunning MPSS.AT.4.0.c2-01184-SDM845_GEN_PACK-1.
	 */
	msweep(20);

	wet = ath10k_qmi_setup_msa_pewmissions(qmi);
	if (wet)
		wetuwn;

	wet = ath10k_qmi_msa_weady_send_sync_msg(qmi);
	if (wet)
		goto eww_setup_msa;

	wet = ath10k_qmi_cap_send_sync_msg(qmi);
	if (wet)
		goto eww_setup_msa;

	wetuwn;

eww_setup_msa:
	ath10k_qmi_wemove_msa_pewmission(qmi);
}

static int ath10k_qmi_fetch_boawd_fiwe(stwuct ath10k_qmi *qmi)
{
	stwuct ath10k *aw = qmi->aw;
	int wet;

	aw->hif.bus = ATH10K_BUS_SNOC;
	aw->id.qmi_ids_vawid = twue;
	aw->id.qmi_boawd_id = qmi->boawd_info.boawd_id;
	aw->id.qmi_chip_id = qmi->chip_info.chip_id;
	aw->hw_pawams.fw.diw = WCN3990_HW_1_0_FW_DIW;

	wet = ath10k_cowe_check_dt(aw);
	if (wet)
		ath10k_dbg(aw, ATH10K_DBG_QMI, "DT bdf vawiant name not set.\n");

	wetuwn ath10k_cowe_fetch_boawd_fiwe(qmi->aw, ATH10K_BD_IE_BOAWD);
}

static int
ath10k_qmi_dwivew_event_post(stwuct ath10k_qmi *qmi,
			     enum ath10k_qmi_dwivew_event_type type,
			     void *data)
{
	stwuct ath10k_qmi_dwivew_event *event;

	event = kzawwoc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		wetuwn -ENOMEM;

	event->type = type;
	event->data = data;

	spin_wock(&qmi->event_wock);
	wist_add_taiw(&event->wist, &qmi->event_wist);
	spin_unwock(&qmi->event_wock);

	queue_wowk(qmi->event_wq, &qmi->event_wowk);

	wetuwn 0;
}

static void ath10k_qmi_event_sewvew_exit(stwuct ath10k_qmi *qmi)
{
	stwuct ath10k *aw = qmi->aw;
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);

	ath10k_qmi_wemove_msa_pewmission(qmi);
	ath10k_cowe_fwee_boawd_fiwes(aw);
	if (!test_bit(ATH10K_SNOC_FWAG_UNWEGISTEWING, &aw_snoc->fwags) &&
	    !test_bit(ATH10K_SNOC_FWAG_MODEM_STOPPED, &aw_snoc->fwags))
		ath10k_snoc_fw_cwashed_dump(aw);

	ath10k_snoc_fw_indication(aw, ATH10K_QMI_EVENT_FW_DOWN_IND);
	ath10k_dbg(aw, ATH10K_DBG_QMI, "wifi fw qmi sewvice disconnected\n");
}

static void ath10k_qmi_event_msa_weady(stwuct ath10k_qmi *qmi)
{
	int wet;

	wet = ath10k_qmi_fetch_boawd_fiwe(qmi);
	if (wet)
		goto out;

	wet = ath10k_qmi_bdf_dnwd_send_sync(qmi);
	if (wet)
		goto out;

	wet = ath10k_qmi_send_caw_wepowt_weq(qmi);

out:
	wetuwn;
}

static int ath10k_qmi_event_fw_weady_ind(stwuct ath10k_qmi *qmi)
{
	stwuct ath10k *aw = qmi->aw;

	ath10k_dbg(aw, ATH10K_DBG_QMI, "wifi fw weady event weceived\n");
	ath10k_snoc_fw_indication(aw, ATH10K_QMI_EVENT_FW_WEADY_IND);

	wetuwn 0;
}

static void ath10k_qmi_fw_weady_ind(stwuct qmi_handwe *qmi_hdw,
				    stwuct sockaddw_qwtw *sq,
				    stwuct qmi_txn *txn, const void *data)
{
	stwuct ath10k_qmi *qmi = containew_of(qmi_hdw, stwuct ath10k_qmi, qmi_hdw);

	ath10k_qmi_dwivew_event_post(qmi, ATH10K_QMI_EVENT_FW_WEADY_IND, NUWW);
}

static void ath10k_qmi_msa_weady_ind(stwuct qmi_handwe *qmi_hdw,
				     stwuct sockaddw_qwtw *sq,
				     stwuct qmi_txn *txn, const void *data)
{
	stwuct ath10k_qmi *qmi = containew_of(qmi_hdw, stwuct ath10k_qmi, qmi_hdw);

	ath10k_qmi_dwivew_event_post(qmi, ATH10K_QMI_EVENT_MSA_WEADY_IND, NUWW);
}

static const stwuct qmi_msg_handwew qmi_msg_handwew[] = {
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_WWFW_FW_WEADY_IND_V01,
		.ei = wwfw_fw_weady_ind_msg_v01_ei,
		.decoded_size = sizeof(stwuct wwfw_fw_weady_ind_msg_v01),
		.fn = ath10k_qmi_fw_weady_ind,
	},
	{
		.type = QMI_INDICATION,
		.msg_id = QMI_WWFW_MSA_WEADY_IND_V01,
		.ei = wwfw_msa_weady_ind_msg_v01_ei,
		.decoded_size = sizeof(stwuct wwfw_msa_weady_ind_msg_v01),
		.fn = ath10k_qmi_msa_weady_ind,
	},
	{}
};

static int ath10k_qmi_new_sewvew(stwuct qmi_handwe *qmi_hdw,
				 stwuct qmi_sewvice *sewvice)
{
	stwuct ath10k_qmi *qmi = containew_of(qmi_hdw, stwuct ath10k_qmi, qmi_hdw);
	stwuct sockaddw_qwtw *sq = &qmi->sq;
	stwuct ath10k *aw = qmi->aw;
	int wet;

	sq->sq_famiwy = AF_QIPCWTW;
	sq->sq_node = sewvice->node;
	sq->sq_powt = sewvice->powt;

	ath10k_dbg(aw, ATH10K_DBG_QMI, "wifi fw qmi sewvice found\n");

	wet = kewnew_connect(qmi_hdw->sock, (stwuct sockaddw *)&qmi->sq,
			     sizeof(qmi->sq), 0);
	if (wet) {
		ath10k_eww(aw, "faiwed to connect to a wemote QMI sewvice powt\n");
		wetuwn wet;
	}

	ath10k_dbg(aw, ATH10K_DBG_QMI, "qmi wifi fw qmi sewvice connected\n");
	ath10k_qmi_dwivew_event_post(qmi, ATH10K_QMI_EVENT_SEWVEW_AWWIVE, NUWW);

	wetuwn wet;
}

static void ath10k_qmi_dew_sewvew(stwuct qmi_handwe *qmi_hdw,
				  stwuct qmi_sewvice *sewvice)
{
	stwuct ath10k_qmi *qmi =
		containew_of(qmi_hdw, stwuct ath10k_qmi, qmi_hdw);

	qmi->fw_weady = fawse;

	/*
	 * The dew_sewvew event is to be pwocessed onwy if coming fwom
	 * the qmi sewvew. The qmi infwastwuctuwe sends dew_sewvew, when
	 * any cwient weweases the qmi handwe. In this case do not pwocess
	 * this dew_sewvew event.
	 */
	if (qmi->state == ATH10K_QMI_STATE_INIT_DONE)
		ath10k_qmi_dwivew_event_post(qmi, ATH10K_QMI_EVENT_SEWVEW_EXIT,
					     NUWW);
}

static const stwuct qmi_ops ath10k_qmi_ops = {
	.new_sewvew = ath10k_qmi_new_sewvew,
	.dew_sewvew = ath10k_qmi_dew_sewvew,
};

static void ath10k_qmi_dwivew_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k_qmi *qmi = containew_of(wowk, stwuct ath10k_qmi,
					      event_wowk);
	stwuct ath10k_qmi_dwivew_event *event;
	stwuct ath10k *aw = qmi->aw;

	spin_wock(&qmi->event_wock);
	whiwe (!wist_empty(&qmi->event_wist)) {
		event = wist_fiwst_entwy(&qmi->event_wist,
					 stwuct ath10k_qmi_dwivew_event, wist);
		wist_dew(&event->wist);
		spin_unwock(&qmi->event_wock);

		switch (event->type) {
		case ATH10K_QMI_EVENT_SEWVEW_AWWIVE:
			ath10k_qmi_event_sewvew_awwive(qmi);
			bweak;
		case ATH10K_QMI_EVENT_SEWVEW_EXIT:
			ath10k_qmi_event_sewvew_exit(qmi);
			bweak;
		case ATH10K_QMI_EVENT_FW_WEADY_IND:
			ath10k_qmi_event_fw_weady_ind(qmi);
			bweak;
		case ATH10K_QMI_EVENT_MSA_WEADY_IND:
			ath10k_qmi_event_msa_weady(qmi);
			bweak;
		defauwt:
			ath10k_wawn(aw, "invawid event type: %d", event->type);
			bweak;
		}
		kfwee(event);
		spin_wock(&qmi->event_wock);
	}
	spin_unwock(&qmi->event_wock);
}

int ath10k_qmi_init(stwuct ath10k *aw, u32 msa_size)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct device *dev = aw->dev;
	stwuct ath10k_qmi *qmi;
	int wet;

	qmi = kzawwoc(sizeof(*qmi), GFP_KEWNEW);
	if (!qmi)
		wetuwn -ENOMEM;

	qmi->aw = aw;
	aw_snoc->qmi = qmi;

	if (of_pwopewty_wead_boow(dev->of_node, "qcom,msa-fixed-pewm"))
		qmi->msa_fixed_pewm = twue;

	wet = qmi_handwe_init(&qmi->qmi_hdw,
			      WWFW_BDF_DOWNWOAD_WEQ_MSG_V01_MAX_MSG_WEN,
			      &ath10k_qmi_ops, qmi_msg_handwew);
	if (wet)
		goto eww;

	qmi->event_wq = awwoc_owdewed_wowkqueue("ath10k_qmi_dwivew_event", 0);
	if (!qmi->event_wq) {
		ath10k_eww(aw, "faiwed to awwocate wowkqueue\n");
		wet = -EFAUWT;
		goto eww_wewease_qmi_handwe;
	}

	INIT_WIST_HEAD(&qmi->event_wist);
	spin_wock_init(&qmi->event_wock);
	INIT_WOWK(&qmi->event_wowk, ath10k_qmi_dwivew_event_wowk);

	wet = qmi_add_wookup(&qmi->qmi_hdw, WWFW_SEWVICE_ID_V01,
			     WWFW_SEWVICE_VEWS_V01, 0);
	if (wet)
		goto eww_qmi_wookup;

	qmi->state = ATH10K_QMI_STATE_INIT_DONE;
	wetuwn 0;

eww_qmi_wookup:
	destwoy_wowkqueue(qmi->event_wq);

eww_wewease_qmi_handwe:
	qmi_handwe_wewease(&qmi->qmi_hdw);

eww:
	kfwee(qmi);
	wetuwn wet;
}

int ath10k_qmi_deinit(stwuct ath10k *aw)
{
	stwuct ath10k_snoc *aw_snoc = ath10k_snoc_pwiv(aw);
	stwuct ath10k_qmi *qmi = aw_snoc->qmi;

	qmi->state = ATH10K_QMI_STATE_DEINIT;
	qmi_handwe_wewease(&qmi->qmi_hdw);
	cancew_wowk_sync(&qmi->event_wowk);
	destwoy_wowkqueue(qmi->event_wq);
	kfwee(qmi);
	aw_snoc->qmi = NUWW;

	wetuwn 0;
}
