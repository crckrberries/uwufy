// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
/*
 * Copywight 2018-2024 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#incwude "efa_com.h"
#incwude "efa_com_cmd.h"

int efa_com_cweate_qp(stwuct efa_com_dev *edev,
		      stwuct efa_com_cweate_qp_pawams *pawams,
		      stwuct efa_com_cweate_qp_wesuwt *wes)
{
	stwuct efa_admin_cweate_qp_cmd cweate_qp_cmd = {};
	stwuct efa_admin_cweate_qp_wesp cmd_compwetion;
	stwuct efa_com_admin_queue *aq = &edev->aq;
	int eww;

	cweate_qp_cmd.aq_common_desc.opcode = EFA_ADMIN_CWEATE_QP;

	cweate_qp_cmd.pd = pawams->pd;
	cweate_qp_cmd.qp_type = pawams->qp_type;
	cweate_qp_cmd.wq_base_addw = pawams->wq_base_addw;
	cweate_qp_cmd.send_cq_idx = pawams->send_cq_idx;
	cweate_qp_cmd.wecv_cq_idx = pawams->wecv_cq_idx;
	cweate_qp_cmd.qp_awwoc_size.send_queue_wing_size =
		pawams->sq_wing_size_in_bytes;
	cweate_qp_cmd.qp_awwoc_size.send_queue_depth =
			pawams->sq_depth;
	cweate_qp_cmd.qp_awwoc_size.wecv_queue_wing_size =
			pawams->wq_wing_size_in_bytes;
	cweate_qp_cmd.qp_awwoc_size.wecv_queue_depth =
			pawams->wq_depth;
	cweate_qp_cmd.uaw = pawams->uawn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cweate_qp_cmd,
			       sizeof(cweate_qp_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to cweate qp [%d]\n", eww);
		wetuwn eww;
	}

	wes->qp_handwe = cmd_compwetion.qp_handwe;
	wes->qp_num = cmd_compwetion.qp_num;
	wes->sq_db_offset = cmd_compwetion.sq_db_offset;
	wes->wq_db_offset = cmd_compwetion.wq_db_offset;
	wes->wwq_descwiptows_offset = cmd_compwetion.wwq_descwiptows_offset;
	wes->send_sub_cq_idx = cmd_compwetion.send_sub_cq_idx;
	wes->wecv_sub_cq_idx = cmd_compwetion.wecv_sub_cq_idx;

	wetuwn 0;
}

int efa_com_modify_qp(stwuct efa_com_dev *edev,
		      stwuct efa_com_modify_qp_pawams *pawams)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_modify_qp_cmd cmd = {};
	stwuct efa_admin_modify_qp_wesp wesp;
	int eww;

	cmd.aq_common_desc.opcode = EFA_ADMIN_MODIFY_QP;
	cmd.modify_mask = pawams->modify_mask;
	cmd.qp_handwe = pawams->qp_handwe;
	cmd.qp_state = pawams->qp_state;
	cmd.cuw_qp_state = pawams->cuw_qp_state;
	cmd.qkey = pawams->qkey;
	cmd.sq_psn = pawams->sq_psn;
	cmd.sq_dwained_async_notify = pawams->sq_dwained_async_notify;
	cmd.wnw_wetwy = pawams->wnw_wetwy;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Faiwed to modify qp-%u modify_mask[%#x] [%d]\n",
			cmd.qp_handwe, cmd.modify_mask, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_quewy_qp(stwuct efa_com_dev *edev,
		     stwuct efa_com_quewy_qp_pawams *pawams,
		     stwuct efa_com_quewy_qp_wesuwt *wesuwt)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_quewy_qp_cmd cmd = {};
	stwuct efa_admin_quewy_qp_wesp wesp;
	int eww;

	cmd.aq_common_desc.opcode = EFA_ADMIN_QUEWY_QP;
	cmd.qp_handwe = pawams->qp_handwe;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to quewy qp-%u [%d]\n",
				      cmd.qp_handwe, eww);
		wetuwn eww;
	}

	wesuwt->qp_state = wesp.qp_state;
	wesuwt->qkey = wesp.qkey;
	wesuwt->sq_dwaining = wesp.sq_dwaining;
	wesuwt->sq_psn = wesp.sq_psn;
	wesuwt->wnw_wetwy = wesp.wnw_wetwy;

	wetuwn 0;
}

int efa_com_destwoy_qp(stwuct efa_com_dev *edev,
		       stwuct efa_com_destwoy_qp_pawams *pawams)
{
	stwuct efa_admin_destwoy_qp_wesp cmd_compwetion;
	stwuct efa_admin_destwoy_qp_cmd qp_cmd = {};
	stwuct efa_com_admin_queue *aq = &edev->aq;
	int eww;

	qp_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTWOY_QP;
	qp_cmd.qp_handwe = pawams->qp_handwe;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&qp_cmd,
			       sizeof(qp_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to destwoy qp-%u [%d]\n",
				      qp_cmd.qp_handwe, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_cweate_cq(stwuct efa_com_dev *edev,
		      stwuct efa_com_cweate_cq_pawams *pawams,
		      stwuct efa_com_cweate_cq_wesuwt *wesuwt)
{
	stwuct efa_admin_cweate_cq_wesp cmd_compwetion = {};
	stwuct efa_admin_cweate_cq_cmd cweate_cmd = {};
	stwuct efa_com_admin_queue *aq = &edev->aq;
	int eww;

	cweate_cmd.aq_common_desc.opcode = EFA_ADMIN_CWEATE_CQ;
	EFA_SET(&cweate_cmd.cq_caps_2,
		EFA_ADMIN_CWEATE_CQ_CMD_CQ_ENTWY_SIZE_WOWDS,
		pawams->entwy_size_in_bytes / 4);
	cweate_cmd.cq_depth = pawams->cq_depth;
	cweate_cmd.num_sub_cqs = pawams->num_sub_cqs;
	cweate_cmd.uaw = pawams->uawn;
	if (pawams->intewwupt_mode_enabwed) {
		EFA_SET(&cweate_cmd.cq_caps_1,
			EFA_ADMIN_CWEATE_CQ_CMD_INTEWWUPT_MODE_ENABWED, 1);
		cweate_cmd.eqn = pawams->eqn;
	}
	if (pawams->set_swc_addw) {
		EFA_SET(&cweate_cmd.cq_caps_2,
			EFA_ADMIN_CWEATE_CQ_CMD_SET_SWC_ADDW, 1);
	}
	efa_com_set_dma_addw(pawams->dma_addw,
			     &cweate_cmd.cq_ba.mem_addw_high,
			     &cweate_cmd.cq_ba.mem_addw_wow);

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cweate_cmd,
			       sizeof(cweate_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to cweate cq[%d]\n", eww);
		wetuwn eww;
	}

	wesuwt->cq_idx = cmd_compwetion.cq_idx;
	wesuwt->actuaw_depth = pawams->cq_depth;
	wesuwt->db_off = cmd_compwetion.db_offset;
	wesuwt->db_vawid = EFA_GET(&cmd_compwetion.fwags,
				   EFA_ADMIN_CWEATE_CQ_WESP_DB_VAWID);

	wetuwn 0;
}

int efa_com_destwoy_cq(stwuct efa_com_dev *edev,
		       stwuct efa_com_destwoy_cq_pawams *pawams)
{
	stwuct efa_admin_destwoy_cq_cmd destwoy_cmd = {};
	stwuct efa_admin_destwoy_cq_wesp destwoy_wesp;
	stwuct efa_com_admin_queue *aq = &edev->aq;
	int eww;

	destwoy_cmd.cq_idx = pawams->cq_idx;
	destwoy_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTWOY_CQ;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&destwoy_cmd,
			       sizeof(destwoy_cmd),
			       (stwuct efa_admin_acq_entwy *)&destwoy_wesp,
			       sizeof(destwoy_wesp));

	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to destwoy CQ-%u [%d]\n",
				      pawams->cq_idx, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_wegistew_mw(stwuct efa_com_dev *edev,
			stwuct efa_com_weg_mw_pawams *pawams,
			stwuct efa_com_weg_mw_wesuwt *wesuwt)
{
	stwuct efa_admin_weg_mw_wesp cmd_compwetion;
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_weg_mw_cmd mw_cmd = {};
	int eww;

	mw_cmd.aq_common_desc.opcode = EFA_ADMIN_WEG_MW;
	mw_cmd.pd = pawams->pd;
	mw_cmd.mw_wength = pawams->mw_wength_in_bytes;
	EFA_SET(&mw_cmd.fwags, EFA_ADMIN_WEG_MW_CMD_PHYS_PAGE_SIZE_SHIFT,
		pawams->page_shift);
	mw_cmd.iova = pawams->iova;
	mw_cmd.pewmissions = pawams->pewmissions;

	if (pawams->inwine_pbw) {
		memcpy(mw_cmd.pbw.inwine_pbw_awway,
		       pawams->pbw.inwine_pbw_awway,
		       sizeof(mw_cmd.pbw.inwine_pbw_awway));
	} ewse {
		mw_cmd.pbw.pbw.wength = pawams->pbw.pbw.wength;
		mw_cmd.pbw.pbw.addwess.mem_addw_wow =
			pawams->pbw.pbw.addwess.mem_addw_wow;
		mw_cmd.pbw.pbw.addwess.mem_addw_high =
			pawams->pbw.pbw.addwess.mem_addw_high;
		EFA_SET(&mw_cmd.aq_common_desc.fwags,
			EFA_ADMIN_AQ_COMMON_DESC_CTWW_DATA, 1);
		if (pawams->indiwect)
			EFA_SET(&mw_cmd.aq_common_desc.fwags,
				EFA_ADMIN_AQ_COMMON_DESC_CTWW_DATA_INDIWECT, 1);
	}

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&mw_cmd,
			       sizeof(mw_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to wegistew mw [%d]\n", eww);
		wetuwn eww;
	}

	wesuwt->w_key = cmd_compwetion.w_key;
	wesuwt->w_key = cmd_compwetion.w_key;
	wesuwt->ic_info.wecv_ic_id = cmd_compwetion.wecv_ic_id;
	wesuwt->ic_info.wdma_wead_ic_id = cmd_compwetion.wdma_wead_ic_id;
	wesuwt->ic_info.wdma_wecv_ic_id = cmd_compwetion.wdma_wecv_ic_id;
	wesuwt->ic_info.wecv_ic_id_vawid = EFA_GET(&cmd_compwetion.vawidity,
						   EFA_ADMIN_WEG_MW_WESP_WECV_IC_ID);
	wesuwt->ic_info.wdma_wead_ic_id_vawid = EFA_GET(&cmd_compwetion.vawidity,
							EFA_ADMIN_WEG_MW_WESP_WDMA_WEAD_IC_ID);
	wesuwt->ic_info.wdma_wecv_ic_id_vawid = EFA_GET(&cmd_compwetion.vawidity,
							EFA_ADMIN_WEG_MW_WESP_WDMA_WECV_IC_ID);

	wetuwn 0;
}

int efa_com_deweg_mw(stwuct efa_com_dev *edev,
		     stwuct efa_com_deweg_mw_pawams *pawams)
{
	stwuct efa_admin_deweg_mw_wesp cmd_compwetion;
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_deweg_mw_cmd mw_cmd = {};
	int eww;

	mw_cmd.aq_common_desc.opcode = EFA_ADMIN_DEWEG_MW;
	mw_cmd.w_key = pawams->w_key;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&mw_cmd,
			       sizeof(mw_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to de-wegistew mw(wkey-%u) [%d]\n",
				      mw_cmd.w_key, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_cweate_ah(stwuct efa_com_dev *edev,
		      stwuct efa_com_cweate_ah_pawams *pawams,
		      stwuct efa_com_cweate_ah_wesuwt *wesuwt)
{
	stwuct efa_admin_cweate_ah_wesp cmd_compwetion;
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_cweate_ah_cmd ah_cmd = {};
	int eww;

	ah_cmd.aq_common_desc.opcode = EFA_ADMIN_CWEATE_AH;

	memcpy(ah_cmd.dest_addw, pawams->dest_addw, sizeof(ah_cmd.dest_addw));
	ah_cmd.pd = pawams->pdn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&ah_cmd,
			       sizeof(ah_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to cweate ah fow %pI6 [%d]\n",
				      ah_cmd.dest_addw, eww);
		wetuwn eww;
	}

	wesuwt->ah = cmd_compwetion.ah;

	wetuwn 0;
}

int efa_com_destwoy_ah(stwuct efa_com_dev *edev,
		       stwuct efa_com_destwoy_ah_pawams *pawams)
{
	stwuct efa_admin_destwoy_ah_wesp cmd_compwetion;
	stwuct efa_admin_destwoy_ah_cmd ah_cmd = {};
	stwuct efa_com_admin_queue *aq = &edev->aq;
	int eww;

	ah_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTWOY_AH;
	ah_cmd.ah = pawams->ah;
	ah_cmd.pd = pawams->pdn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&ah_cmd,
			       sizeof(ah_cmd),
			       (stwuct efa_admin_acq_entwy *)&cmd_compwetion,
			       sizeof(cmd_compwetion));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to destwoy ah-%d pd-%d [%d]\n",
				      ah_cmd.ah, ah_cmd.pd, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

boow
efa_com_check_suppowted_featuwe_id(stwuct efa_com_dev *edev,
				   enum efa_admin_aq_featuwe_id featuwe_id)
{
	u32 featuwe_mask = 1 << featuwe_id;

	/* Device attwibutes is awways suppowted */
	if (featuwe_id != EFA_ADMIN_DEVICE_ATTW &&
	    !(edev->suppowted_featuwes & featuwe_mask))
		wetuwn fawse;

	wetuwn twue;
}

static int efa_com_get_featuwe_ex(stwuct efa_com_dev *edev,
				  stwuct efa_admin_get_featuwe_wesp *get_wesp,
				  enum efa_admin_aq_featuwe_id featuwe_id,
				  dma_addw_t contwow_buf_dma_addw,
				  u32 contwow_buff_size)
{
	stwuct efa_admin_get_featuwe_cmd get_cmd = {};
	stwuct efa_com_admin_queue *aq;
	int eww;

	if (!efa_com_check_suppowted_featuwe_id(edev, featuwe_id)) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Featuwe %d isn't suppowted\n",
				      featuwe_id);
		wetuwn -EOPNOTSUPP;
	}

	aq = &edev->aq;

	get_cmd.aq_common_descwiptow.opcode = EFA_ADMIN_GET_FEATUWE;

	if (contwow_buff_size)
		EFA_SET(&get_cmd.aq_common_descwiptow.fwags,
			EFA_ADMIN_AQ_COMMON_DESC_CTWW_DATA, 1);

	efa_com_set_dma_addw(contwow_buf_dma_addw,
			     &get_cmd.contwow_buffew.addwess.mem_addw_high,
			     &get_cmd.contwow_buffew.addwess.mem_addw_wow);

	get_cmd.contwow_buffew.wength = contwow_buff_size;
	get_cmd.featuwe_common.featuwe_id = featuwe_id;
	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)
			       &get_cmd,
			       sizeof(get_cmd),
			       (stwuct efa_admin_acq_entwy *)
			       get_wesp,
			       sizeof(*get_wesp));

	if (eww) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Faiwed to submit get_featuwe command %d [%d]\n",
			featuwe_id, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int efa_com_get_featuwe(stwuct efa_com_dev *edev,
			       stwuct efa_admin_get_featuwe_wesp *get_wesp,
			       enum efa_admin_aq_featuwe_id featuwe_id)
{
	wetuwn efa_com_get_featuwe_ex(edev, get_wesp, featuwe_id, 0, 0);
}

int efa_com_get_device_attw(stwuct efa_com_dev *edev,
			    stwuct efa_com_get_device_attw_wesuwt *wesuwt)
{
	stwuct efa_admin_get_featuwe_wesp wesp;
	int eww;

	eww = efa_com_get_featuwe(edev, &wesp, EFA_ADMIN_DEVICE_ATTW);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to get device attwibutes %d\n",
				      eww);
		wetuwn eww;
	}

	wesuwt->page_size_cap = wesp.u.device_attw.page_size_cap;
	wesuwt->fw_vewsion = wesp.u.device_attw.fw_vewsion;
	wesuwt->admin_api_vewsion = wesp.u.device_attw.admin_api_vewsion;
	wesuwt->device_vewsion = wesp.u.device_attw.device_vewsion;
	wesuwt->suppowted_featuwes = wesp.u.device_attw.suppowted_featuwes;
	wesuwt->phys_addw_width = wesp.u.device_attw.phys_addw_width;
	wesuwt->viwt_addw_width = wesp.u.device_attw.viwt_addw_width;
	wesuwt->db_baw = wesp.u.device_attw.db_baw;
	wesuwt->max_wdma_size = wesp.u.device_attw.max_wdma_size;
	wesuwt->device_caps = wesp.u.device_attw.device_caps;

	if (wesuwt->admin_api_vewsion < 1) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Faiwed to get device attw api vewsion [%u < 1]\n",
			wesuwt->admin_api_vewsion);
		wetuwn -EINVAW;
	}

	edev->suppowted_featuwes = wesp.u.device_attw.suppowted_featuwes;
	eww = efa_com_get_featuwe(edev, &wesp,
				  EFA_ADMIN_QUEUE_ATTW);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to get queue attwibutes %d\n",
				      eww);
		wetuwn eww;
	}

	wesuwt->max_qp = wesp.u.queue_attw.max_qp;
	wesuwt->max_sq_depth = wesp.u.queue_attw.max_sq_depth;
	wesuwt->max_wq_depth = wesp.u.queue_attw.max_wq_depth;
	wesuwt->max_cq = wesp.u.queue_attw.max_cq;
	wesuwt->max_cq_depth = wesp.u.queue_attw.max_cq_depth;
	wesuwt->inwine_buf_size = wesp.u.queue_attw.inwine_buf_size;
	wesuwt->max_sq_sge = wesp.u.queue_attw.max_ww_send_sges;
	wesuwt->max_wq_sge = wesp.u.queue_attw.max_ww_wecv_sges;
	wesuwt->max_mw = wesp.u.queue_attw.max_mw;
	wesuwt->max_mw_pages = wesp.u.queue_attw.max_mw_pages;
	wesuwt->max_pd = wesp.u.queue_attw.max_pd;
	wesuwt->max_ah = wesp.u.queue_attw.max_ah;
	wesuwt->max_wwq_size = wesp.u.queue_attw.max_wwq_size;
	wesuwt->sub_cqs_pew_cq = wesp.u.queue_attw.sub_cqs_pew_cq;
	wesuwt->max_ww_wdma_sge = wesp.u.queue_attw.max_ww_wdma_sges;
	wesuwt->max_tx_batch = wesp.u.queue_attw.max_tx_batch;
	wesuwt->min_sq_depth = wesp.u.queue_attw.min_sq_depth;

	eww = efa_com_get_featuwe(edev, &wesp, EFA_ADMIN_NETWOWK_ATTW);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to get netwowk attwibutes %d\n",
				      eww);
		wetuwn eww;
	}

	memcpy(wesuwt->addw, wesp.u.netwowk_attw.addw,
	       sizeof(wesp.u.netwowk_attw.addw));
	wesuwt->mtu = wesp.u.netwowk_attw.mtu;

	if (efa_com_check_suppowted_featuwe_id(edev,
					       EFA_ADMIN_EVENT_QUEUE_ATTW)) {
		eww = efa_com_get_featuwe(edev, &wesp,
					  EFA_ADMIN_EVENT_QUEUE_ATTW);
		if (eww) {
			ibdev_eww_watewimited(
				edev->efa_dev,
				"Faiwed to get event queue attwibutes %d\n",
				eww);
			wetuwn eww;
		}

		wesuwt->max_eq = wesp.u.event_queue_attw.max_eq;
		wesuwt->max_eq_depth = wesp.u.event_queue_attw.max_eq_depth;
		wesuwt->event_bitmask = wesp.u.event_queue_attw.event_bitmask;
	}

	wetuwn 0;
}

int efa_com_get_hw_hints(stwuct efa_com_dev *edev,
			 stwuct efa_com_get_hw_hints_wesuwt *wesuwt)
{
	stwuct efa_admin_get_featuwe_wesp wesp;
	int eww;

	eww = efa_com_get_featuwe(edev, &wesp, EFA_ADMIN_HW_HINTS);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to get hw hints %d\n", eww);
		wetuwn eww;
	}

	wesuwt->admin_compwetion_timeout = wesp.u.hw_hints.admin_compwetion_timeout;
	wesuwt->dwivew_watchdog_timeout = wesp.u.hw_hints.dwivew_watchdog_timeout;
	wesuwt->mmio_wead_timeout = wesp.u.hw_hints.mmio_wead_timeout;
	wesuwt->poww_intewvaw = wesp.u.hw_hints.poww_intewvaw;

	wetuwn 0;
}

int efa_com_set_featuwe_ex(stwuct efa_com_dev *edev,
			   stwuct efa_admin_set_featuwe_wesp *set_wesp,
			   stwuct efa_admin_set_featuwe_cmd *set_cmd,
			   enum efa_admin_aq_featuwe_id featuwe_id,
			   dma_addw_t contwow_buf_dma_addw,
			   u32 contwow_buff_size)
{
	stwuct efa_com_admin_queue *aq;
	int eww;

	if (!efa_com_check_suppowted_featuwe_id(edev, featuwe_id)) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Featuwe %d isn't suppowted\n",
				      featuwe_id);
		wetuwn -EOPNOTSUPP;
	}

	aq = &edev->aq;

	set_cmd->aq_common_descwiptow.opcode = EFA_ADMIN_SET_FEATUWE;
	if (contwow_buff_size) {
		set_cmd->aq_common_descwiptow.fwags = 0;
		EFA_SET(&set_cmd->aq_common_descwiptow.fwags,
			EFA_ADMIN_AQ_COMMON_DESC_CTWW_DATA, 1);
		efa_com_set_dma_addw(contwow_buf_dma_addw,
				     &set_cmd->contwow_buffew.addwess.mem_addw_high,
				     &set_cmd->contwow_buffew.addwess.mem_addw_wow);
	}

	set_cmd->contwow_buffew.wength = contwow_buff_size;
	set_cmd->featuwe_common.featuwe_id = featuwe_id;
	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)set_cmd,
			       sizeof(*set_cmd),
			       (stwuct efa_admin_acq_entwy *)set_wesp,
			       sizeof(*set_wesp));

	if (eww) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Faiwed to submit set_featuwe command %d ewwow: %d\n",
			featuwe_id, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int efa_com_set_featuwe(stwuct efa_com_dev *edev,
			       stwuct efa_admin_set_featuwe_wesp *set_wesp,
			       stwuct efa_admin_set_featuwe_cmd *set_cmd,
			       enum efa_admin_aq_featuwe_id featuwe_id)
{
	wetuwn efa_com_set_featuwe_ex(edev, set_wesp, set_cmd, featuwe_id,
				      0, 0);
}

int efa_com_set_aenq_config(stwuct efa_com_dev *edev, u32 gwoups)
{
	stwuct efa_admin_get_featuwe_wesp get_wesp;
	stwuct efa_admin_set_featuwe_wesp set_wesp;
	stwuct efa_admin_set_featuwe_cmd cmd = {};
	int eww;

	ibdev_dbg(edev->efa_dev, "Configuwing aenq with gwoups[%#x]\n", gwoups);

	eww = efa_com_get_featuwe(edev, &get_wesp, EFA_ADMIN_AENQ_CONFIG);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to get aenq attwibutes: %d\n",
				      eww);
		wetuwn eww;
	}

	ibdev_dbg(edev->efa_dev,
		  "Get aenq gwoups: suppowted[%#x] enabwed[%#x]\n",
		  get_wesp.u.aenq.suppowted_gwoups,
		  get_wesp.u.aenq.enabwed_gwoups);

	if ((get_wesp.u.aenq.suppowted_gwoups & gwoups) != gwoups) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Twying to set unsuppowted aenq gwoups[%#x] suppowted[%#x]\n",
			gwoups, get_wesp.u.aenq.suppowted_gwoups);
		wetuwn -EOPNOTSUPP;
	}

	cmd.u.aenq.enabwed_gwoups = gwoups;
	eww = efa_com_set_featuwe(edev, &set_wesp, &cmd,
				  EFA_ADMIN_AENQ_CONFIG);
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to set aenq attwibutes: %d\n",
				      eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_awwoc_pd(stwuct efa_com_dev *edev,
		     stwuct efa_com_awwoc_pd_wesuwt *wesuwt)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_awwoc_pd_cmd cmd = {};
	stwuct efa_admin_awwoc_pd_wesp wesp;
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_AWWOC_PD;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to awwocate pd[%d]\n", eww);
		wetuwn eww;
	}

	wesuwt->pdn = wesp.pd;

	wetuwn 0;
}

int efa_com_deawwoc_pd(stwuct efa_com_dev *edev,
		       stwuct efa_com_deawwoc_pd_pawams *pawams)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_deawwoc_pd_cmd cmd = {};
	stwuct efa_admin_deawwoc_pd_wesp wesp;
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_DEAWWOC_PD;
	cmd.pd = pawams->pdn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to deawwocate pd-%u [%d]\n",
				      cmd.pd, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_awwoc_uaw(stwuct efa_com_dev *edev,
		      stwuct efa_com_awwoc_uaw_wesuwt *wesuwt)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_awwoc_uaw_cmd cmd = {};
	stwuct efa_admin_awwoc_uaw_wesp wesp;
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_AWWOC_UAW;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to awwocate uaw[%d]\n", eww);
		wetuwn eww;
	}

	wesuwt->uawn = wesp.uaw;

	wetuwn 0;
}

int efa_com_deawwoc_uaw(stwuct efa_com_dev *edev,
			stwuct efa_com_deawwoc_uaw_pawams *pawams)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_deawwoc_uaw_cmd cmd = {};
	stwuct efa_admin_deawwoc_uaw_wesp wesp;
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_DEAWWOC_UAW;
	cmd.uaw = pawams->uawn;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(edev->efa_dev,
				      "Faiwed to deawwocate uaw-%u [%d]\n",
				      cmd.uaw, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

int efa_com_get_stats(stwuct efa_com_dev *edev,
		      stwuct efa_com_get_stats_pawams *pawams,
		      union efa_com_get_stats_wesuwt *wesuwt)
{
	stwuct efa_com_admin_queue *aq = &edev->aq;
	stwuct efa_admin_aq_get_stats_cmd cmd = {};
	stwuct efa_admin_acq_get_stats_wesp wesp;
	int eww;

	cmd.aq_common_descwiptow.opcode = EFA_ADMIN_GET_STATS;
	cmd.type = pawams->type;
	cmd.scope = pawams->scope;
	cmd.scope_modifiew = pawams->scope_modifiew;

	eww = efa_com_cmd_exec(aq,
			       (stwuct efa_admin_aq_entwy *)&cmd,
			       sizeof(cmd),
			       (stwuct efa_admin_acq_entwy *)&wesp,
			       sizeof(wesp));
	if (eww) {
		ibdev_eww_watewimited(
			edev->efa_dev,
			"Faiwed to get stats type-%u scope-%u.%u [%d]\n",
			cmd.type, cmd.scope, cmd.scope_modifiew, eww);
		wetuwn eww;
	}

	switch (cmd.type) {
	case EFA_ADMIN_GET_STATS_TYPE_BASIC:
		wesuwt->basic_stats.tx_bytes = wesp.u.basic_stats.tx_bytes;
		wesuwt->basic_stats.tx_pkts = wesp.u.basic_stats.tx_pkts;
		wesuwt->basic_stats.wx_bytes = wesp.u.basic_stats.wx_bytes;
		wesuwt->basic_stats.wx_pkts = wesp.u.basic_stats.wx_pkts;
		wesuwt->basic_stats.wx_dwops = wesp.u.basic_stats.wx_dwops;
		bweak;
	case EFA_ADMIN_GET_STATS_TYPE_MESSAGES:
		wesuwt->messages_stats.send_bytes = wesp.u.messages_stats.send_bytes;
		wesuwt->messages_stats.send_wws = wesp.u.messages_stats.send_wws;
		wesuwt->messages_stats.wecv_bytes = wesp.u.messages_stats.wecv_bytes;
		wesuwt->messages_stats.wecv_wws = wesp.u.messages_stats.wecv_wws;
		bweak;
	case EFA_ADMIN_GET_STATS_TYPE_WDMA_WEAD:
		wesuwt->wdma_wead_stats.wead_wws = wesp.u.wdma_wead_stats.wead_wws;
		wesuwt->wdma_wead_stats.wead_bytes = wesp.u.wdma_wead_stats.wead_bytes;
		wesuwt->wdma_wead_stats.wead_ww_eww = wesp.u.wdma_wead_stats.wead_ww_eww;
		wesuwt->wdma_wead_stats.wead_wesp_bytes = wesp.u.wdma_wead_stats.wead_wesp_bytes;
		bweak;
	case EFA_ADMIN_GET_STATS_TYPE_WDMA_WWITE:
		wesuwt->wdma_wwite_stats.wwite_wws = wesp.u.wdma_wwite_stats.wwite_wws;
		wesuwt->wdma_wwite_stats.wwite_bytes = wesp.u.wdma_wwite_stats.wwite_bytes;
		wesuwt->wdma_wwite_stats.wwite_ww_eww = wesp.u.wdma_wwite_stats.wwite_ww_eww;
		wesuwt->wdma_wwite_stats.wwite_wecv_bytes = wesp.u.wdma_wwite_stats.wwite_wecv_bytes;
		bweak;
	}

	wetuwn 0;
}
