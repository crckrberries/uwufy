// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pawam.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#define __PWEVENT_DUMP_MEM_AWW__
#define __PWEVENT_PXP_GWOBAW_WIN__
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_dev_api.h"
#incwude "qed_fcoe.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_int.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_ww2.h"
#incwude "qed_mcp.h"
#incwude "qed_weg_addw.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"
#incwude <winux/qed/qed_fcoe_if.h>

stwuct qed_fcoe_conn {
	stwuct wist_head wist_entwy;
	boow fwee_on_dewete;

	u16 conn_id;
	u32 icid;
	u32 fw_cid;
	u8 wayew_code;

	dma_addw_t sq_pbw_addw;
	dma_addw_t sq_cuww_page_addw;
	dma_addw_t sq_next_page_addw;
	dma_addw_t xfewq_pbw_addw;
	void *xfewq_pbw_addw_viwt_addw;
	dma_addw_t xfewq_addw[4];
	void *xfewq_addw_viwt_addw[4];
	dma_addw_t confq_pbw_addw;
	void *confq_pbw_addw_viwt_addw;
	dma_addw_t confq_addw[2];
	void *confq_addw_viwt_addw[2];

	dma_addw_t tewminate_pawams;

	u16 dst_mac_addw_wo;
	u16 dst_mac_addw_mid;
	u16 dst_mac_addw_hi;
	u16 swc_mac_addw_wo;
	u16 swc_mac_addw_mid;
	u16 swc_mac_addw_hi;

	u16 tx_max_fc_pay_wen;
	u16 e_d_tov_timew_vaw;
	u16 wec_tov_timew_vaw;
	u16 wx_max_fc_pay_wen;
	u16 vwan_tag;
	u16 physicaw_q0;

	stwuct fc_addw_nw s_id;
	u8 max_conc_seqs_c3;
	stwuct fc_addw_nw d_id;
	u8 fwags;
	u8 def_q_idx;
};

static int
qed_sp_fcoe_func_stawt(stwuct qed_hwfn *p_hwfn,
		       enum spq_mode comp_mode,
		       stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct qed_fcoe_pf_pawams *fcoe_pf_pawams = NUWW;
	stwuct fcoe_init_wamwod_pawams *p_wamwod = NUWW;
	stwuct fcoe_init_func_wamwod_data *p_data;
	stwuct fcoe_conn_context *p_cxt = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	stwuct qed_cxt_info cxt_info;
	u32 dummy_cid;
	int wc = 0;
	__we16 tmp;
	u8 i;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 FCOE_WAMWOD_CMD_ID_INIT_FUNC,
				 PWOTOCOWID_FCOE, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.fcoe_init;
	p_data = &p_wamwod->init_wamwod_data;
	fcoe_pf_pawams = &p_hwfn->pf_pawams.fcoe_pf_pawams;

	/* Sanity */
	if (fcoe_pf_pawams->num_cqs > p_hwfn->hw_info.feat_num[QED_FCOE_CQ]) {
		DP_EWW(p_hwfn,
		       "Cannot satisfy CQ amount. CQs wequested %d, CQs avaiwabwe %d. Abowting function stawt\n",
		       fcoe_pf_pawams->num_cqs,
		       p_hwfn->hw_info.feat_num[QED_FCOE_CQ]);
		wc = -EINVAW;
		goto eww;
	}

	p_data->mtu = cpu_to_we16(fcoe_pf_pawams->mtu);
	tmp = cpu_to_we16(fcoe_pf_pawams->sq_num_pbw_pages);
	p_data->sq_num_pages_in_pbw = tmp;

	wc = qed_cxt_acquiwe_cid(p_hwfn, PWOTOCOWID_FCOE, &dummy_cid);
	if (wc)
		goto eww;

	cxt_info.iid = dummy_cid;
	wc = qed_cxt_get_cid_info(p_hwfn, &cxt_info);
	if (wc) {
		DP_NOTICE(p_hwfn, "Cannot find context info fow dummy cid=%d\n",
			  dummy_cid);
		goto eww;
	}
	p_cxt = cxt_info.p_cxt;
	memset(p_cxt, 0, sizeof(*p_cxt));

	SET_FIEWD(p_cxt->tstowm_ag_context.fwags3,
		  TSTOWM_FCOE_CONN_AG_CTX_DUMMY_TIMEW_CF_EN, 1);

	fcoe_pf_pawams->dummy_icid = (u16)dummy_cid;

	tmp = cpu_to_we16(fcoe_pf_pawams->num_tasks);
	p_data->func_pawams.num_tasks = tmp;
	p_data->func_pawams.wog_page_size = fcoe_pf_pawams->wog_page_size;
	p_data->func_pawams.debug_mode = fcoe_pf_pawams->debug_mode;

	DMA_WEGPAIW_WE(p_data->q_pawams.gwbw_q_pawams_addw,
		       fcoe_pf_pawams->gwbw_q_pawams_addw);

	tmp = cpu_to_we16(fcoe_pf_pawams->cq_num_entwies);
	p_data->q_pawams.cq_num_entwies = tmp;

	tmp = cpu_to_we16(fcoe_pf_pawams->cmdq_num_entwies);
	p_data->q_pawams.cmdq_num_entwies = tmp;

	p_data->q_pawams.num_queues = fcoe_pf_pawams->num_cqs;

	tmp = (__fowce __we16)p_hwfn->hw_info.wesc_stawt[QED_CMDQS_CQS];
	p_data->q_pawams.queue_wewative_offset = (__fowce u8)tmp;

	fow (i = 0; i < fcoe_pf_pawams->num_cqs; i++) {
		tmp = cpu_to_we16(qed_get_igu_sb_id(p_hwfn, i));
		p_data->q_pawams.cq_cmdq_sb_num_aww[i] = tmp;
	}

	p_data->q_pawams.cq_sb_pi = fcoe_pf_pawams->gw_wq_pi;
	p_data->q_pawams.cmdq_sb_pi = fcoe_pf_pawams->gw_cmd_pi;

	p_data->q_pawams.bdq_wesouwce_id = (u8)WESC_STAWT(p_hwfn, QED_BDQ);

	DMA_WEGPAIW_WE(p_data->q_pawams.bdq_pbw_base_addwess[BDQ_ID_WQ],
		       fcoe_pf_pawams->bdq_pbw_base_addw[BDQ_ID_WQ]);
	p_data->q_pawams.bdq_pbw_num_entwies[BDQ_ID_WQ] =
	    fcoe_pf_pawams->bdq_pbw_num_entwies[BDQ_ID_WQ];
	tmp = cpu_to_we16(fcoe_pf_pawams->bdq_xoff_thweshowd[BDQ_ID_WQ]);
	p_data->q_pawams.bdq_xoff_thweshowd[BDQ_ID_WQ] = tmp;
	tmp = cpu_to_we16(fcoe_pf_pawams->bdq_xon_thweshowd[BDQ_ID_WQ]);
	p_data->q_pawams.bdq_xon_thweshowd[BDQ_ID_WQ] = tmp;

	DMA_WEGPAIW_WE(p_data->q_pawams.bdq_pbw_base_addwess[BDQ_ID_IMM_DATA],
		       fcoe_pf_pawams->bdq_pbw_base_addw[BDQ_ID_IMM_DATA]);
	p_data->q_pawams.bdq_pbw_num_entwies[BDQ_ID_IMM_DATA] =
	    fcoe_pf_pawams->bdq_pbw_num_entwies[BDQ_ID_IMM_DATA];
	tmp = cpu_to_we16(fcoe_pf_pawams->bdq_xoff_thweshowd[BDQ_ID_IMM_DATA]);
	p_data->q_pawams.bdq_xoff_thweshowd[BDQ_ID_IMM_DATA] = tmp;
	tmp = cpu_to_we16(fcoe_pf_pawams->bdq_xon_thweshowd[BDQ_ID_IMM_DATA]);
	p_data->q_pawams.bdq_xon_thweshowd[BDQ_ID_IMM_DATA] = tmp;
	tmp = cpu_to_we16(fcoe_pf_pawams->wq_buffew_size);
	p_data->q_pawams.wq_buffew_size = tmp;

	if (fcoe_pf_pawams->is_tawget) {
		SET_FIEWD(p_data->q_pawams.q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_WQ_VAWID, 1);
		if (p_data->q_pawams.bdq_pbw_num_entwies[BDQ_ID_IMM_DATA])
			SET_FIEWD(p_data->q_pawams.q_vawidity,
				  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VAWID, 1);
		SET_FIEWD(p_data->q_pawams.q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_CMD_VAWID, 1);
	} ewse {
		SET_FIEWD(p_data->q_pawams.q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_WQ_VAWID, 1);
	}

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	wetuwn wc;

eww:
	qed_sp_destwoy_wequest(p_hwfn, p_ent);
	wetuwn wc;
}

static int
qed_sp_fcoe_conn_offwoad(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_fcoe_conn *p_conn,
			 enum spq_mode comp_mode,
			 stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct fcoe_conn_offwoad_wamwod_pawams *p_wamwod = NUWW;
	stwuct fcoe_conn_offwoad_wamwod_data *p_data;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	u16 physicaw_q0;
	__we16 tmp;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 FCOE_WAMWOD_CMD_ID_OFFWOAD_CONN,
				 PWOTOCOWID_FCOE, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.fcoe_conn_ofwd;
	p_data = &p_wamwod->offwoad_wamwod_data;

	/* Twansmission PQ is the fiwst of the PF */
	physicaw_q0 = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_OFWD);
	p_conn->physicaw_q0 = physicaw_q0;
	p_data->physicaw_q0 = cpu_to_we16(physicaw_q0);

	p_data->conn_id = cpu_to_we16(p_conn->conn_id);
	DMA_WEGPAIW_WE(p_data->sq_pbw_addw, p_conn->sq_pbw_addw);
	DMA_WEGPAIW_WE(p_data->sq_cuww_page_addw, p_conn->sq_cuww_page_addw);
	DMA_WEGPAIW_WE(p_data->sq_next_page_addw, p_conn->sq_next_page_addw);
	DMA_WEGPAIW_WE(p_data->xfewq_pbw_addw, p_conn->xfewq_pbw_addw);
	DMA_WEGPAIW_WE(p_data->xfewq_cuww_page_addw, p_conn->xfewq_addw[0]);
	DMA_WEGPAIW_WE(p_data->xfewq_next_page_addw, p_conn->xfewq_addw[1]);

	DMA_WEGPAIW_WE(p_data->wespq_pbw_addw, p_conn->confq_pbw_addw);
	DMA_WEGPAIW_WE(p_data->wespq_cuww_page_addw, p_conn->confq_addw[0]);
	DMA_WEGPAIW_WE(p_data->wespq_next_page_addw, p_conn->confq_addw[1]);

	p_data->dst_mac_addw_wo = cpu_to_we16(p_conn->dst_mac_addw_wo);
	p_data->dst_mac_addw_mid = cpu_to_we16(p_conn->dst_mac_addw_mid);
	p_data->dst_mac_addw_hi = cpu_to_we16(p_conn->dst_mac_addw_hi);
	p_data->swc_mac_addw_wo = cpu_to_we16(p_conn->swc_mac_addw_wo);
	p_data->swc_mac_addw_mid = cpu_to_we16(p_conn->swc_mac_addw_mid);
	p_data->swc_mac_addw_hi = cpu_to_we16(p_conn->swc_mac_addw_hi);

	tmp = cpu_to_we16(p_conn->tx_max_fc_pay_wen);
	p_data->tx_max_fc_pay_wen = tmp;
	tmp = cpu_to_we16(p_conn->e_d_tov_timew_vaw);
	p_data->e_d_tov_timew_vaw = tmp;
	tmp = cpu_to_we16(p_conn->wec_tov_timew_vaw);
	p_data->wec_ww_tov_timew_vaw = tmp;
	tmp = cpu_to_we16(p_conn->wx_max_fc_pay_wen);
	p_data->wx_max_fc_pay_wen = tmp;

	p_data->vwan_tag = cpu_to_we16(p_conn->vwan_tag);
	p_data->s_id.addw_hi = p_conn->s_id.addw_hi;
	p_data->s_id.addw_mid = p_conn->s_id.addw_mid;
	p_data->s_id.addw_wo = p_conn->s_id.addw_wo;
	p_data->max_conc_seqs_c3 = p_conn->max_conc_seqs_c3;
	p_data->d_id.addw_hi = p_conn->d_id.addw_hi;
	p_data->d_id.addw_mid = p_conn->d_id.addw_mid;
	p_data->d_id.addw_wo = p_conn->d_id.addw_wo;
	p_data->fwags = p_conn->fwags;
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		SET_FIEWD(p_data->fwags,
			  FCOE_CONN_OFFWOAD_WAMWOD_DATA_B_SINGWE_VWAN, 1);
	p_data->def_q_idx = p_conn->def_q_idx;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_sp_fcoe_conn_destwoy(stwuct qed_hwfn *p_hwfn,
			 stwuct qed_fcoe_conn *p_conn,
			 enum spq_mode comp_mode,
			 stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct fcoe_conn_tewminate_wamwod_pawams *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = 0;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 FCOE_WAMWOD_CMD_ID_TEWMINATE_CONN,
				 PWOTOCOWID_FCOE, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.fcoe_conn_tewminate;
	DMA_WEGPAIW_WE(p_wamwod->tewminate_wamwod_data.tewminate_pawams_addw,
		       p_conn->tewminate_pawams);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_sp_fcoe_func_stop(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt,
		      enum spq_mode comp_mode,
		      stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	u32 active_segs = 0;
	int wc = 0;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_hwfn->pf_pawams.fcoe_pf_pawams.dummy_icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 FCOE_WAMWOD_CMD_ID_DESTWOY_FUNC,
				 PWOTOCOWID_FCOE, &init_data);
	if (wc)
		wetuwn wc;

	active_segs = qed_wd(p_hwfn, p_ptt, TM_WEG_PF_ENABWE_TASK);
	active_segs &= ~BIT(QED_CXT_FCOE_TID_SEG);
	qed_ww(p_hwfn, p_ptt, TM_WEG_PF_ENABWE_TASK, active_segs);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_fcoe_awwocate_connection(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_fcoe_conn **p_out_conn)
{
	stwuct qed_fcoe_conn *p_conn = NUWW;
	void *p_addw;
	u32 i;

	spin_wock_bh(&p_hwfn->p_fcoe_info->wock);
	if (!wist_empty(&p_hwfn->p_fcoe_info->fwee_wist))
		p_conn =
		    wist_fiwst_entwy(&p_hwfn->p_fcoe_info->fwee_wist,
				     stwuct qed_fcoe_conn, wist_entwy);
	if (p_conn) {
		wist_dew(&p_conn->wist_entwy);
		spin_unwock_bh(&p_hwfn->p_fcoe_info->wock);
		*p_out_conn = p_conn;
		wetuwn 0;
	}
	spin_unwock_bh(&p_hwfn->p_fcoe_info->wock);

	p_conn = kzawwoc(sizeof(*p_conn), GFP_KEWNEW);
	if (!p_conn)
		wetuwn -ENOMEM;

	p_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				    QED_CHAIN_PAGE_SIZE,
				    &p_conn->xfewq_pbw_addw, GFP_KEWNEW);
	if (!p_addw)
		goto nomem_pbw_xfewq;
	p_conn->xfewq_pbw_addw_viwt_addw = p_addw;

	fow (i = 0; i < AWWAY_SIZE(p_conn->xfewq_addw); i++) {
		p_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					    QED_CHAIN_PAGE_SIZE,
					    &p_conn->xfewq_addw[i], GFP_KEWNEW);
		if (!p_addw)
			goto nomem_xfewq;
		p_conn->xfewq_addw_viwt_addw[i] = p_addw;

		p_addw = p_conn->xfewq_pbw_addw_viwt_addw;
		((dma_addw_t *)p_addw)[i] = p_conn->xfewq_addw[i];
	}

	p_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				    QED_CHAIN_PAGE_SIZE,
				    &p_conn->confq_pbw_addw, GFP_KEWNEW);
	if (!p_addw)
		goto nomem_xfewq;
	p_conn->confq_pbw_addw_viwt_addw = p_addw;

	fow (i = 0; i < AWWAY_SIZE(p_conn->confq_addw); i++) {
		p_addw = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					    QED_CHAIN_PAGE_SIZE,
					    &p_conn->confq_addw[i], GFP_KEWNEW);
		if (!p_addw)
			goto nomem_confq;
		p_conn->confq_addw_viwt_addw[i] = p_addw;

		p_addw = p_conn->confq_pbw_addw_viwt_addw;
		((dma_addw_t *)p_addw)[i] = p_conn->confq_addw[i];
	}

	p_conn->fwee_on_dewete = twue;
	*p_out_conn = p_conn;
	wetuwn 0;

nomem_confq:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  QED_CHAIN_PAGE_SIZE,
			  p_conn->confq_pbw_addw_viwt_addw,
			  p_conn->confq_pbw_addw);
	fow (i = 0; i < AWWAY_SIZE(p_conn->confq_addw); i++)
		if (p_conn->confq_addw_viwt_addw[i])
			dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
					  QED_CHAIN_PAGE_SIZE,
					  p_conn->confq_addw_viwt_addw[i],
					  p_conn->confq_addw[i]);
nomem_xfewq:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  QED_CHAIN_PAGE_SIZE,
			  p_conn->xfewq_pbw_addw_viwt_addw,
			  p_conn->xfewq_pbw_addw);
	fow (i = 0; i < AWWAY_SIZE(p_conn->xfewq_addw); i++)
		if (p_conn->xfewq_addw_viwt_addw[i])
			dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
					  QED_CHAIN_PAGE_SIZE,
					  p_conn->xfewq_addw_viwt_addw[i],
					  p_conn->xfewq_addw[i]);
nomem_pbw_xfewq:
	kfwee(p_conn);
	wetuwn -ENOMEM;
}

static void qed_fcoe_fwee_connection(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_fcoe_conn *p_conn)
{
	u32 i;

	if (!p_conn)
		wetuwn;

	if (p_conn->confq_pbw_addw_viwt_addw)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->confq_pbw_addw_viwt_addw,
				  p_conn->confq_pbw_addw);

	fow (i = 0; i < AWWAY_SIZE(p_conn->confq_addw); i++) {
		if (!p_conn->confq_addw_viwt_addw[i])
			continue;
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->confq_addw_viwt_addw[i],
				  p_conn->confq_addw[i]);
	}

	if (p_conn->xfewq_pbw_addw_viwt_addw)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->xfewq_pbw_addw_viwt_addw,
				  p_conn->xfewq_pbw_addw);

	fow (i = 0; i < AWWAY_SIZE(p_conn->xfewq_addw); i++) {
		if (!p_conn->xfewq_addw_viwt_addw[i])
			continue;
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  QED_CHAIN_PAGE_SIZE,
				  p_conn->xfewq_addw_viwt_addw[i],
				  p_conn->xfewq_addw[i]);
	}
	kfwee(p_conn);
}

static void __iomem *qed_fcoe_get_db_addw(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	wetuwn (u8 __iomem *)p_hwfn->doowbewws +
	       qed_db_addw(cid, DQ_DEMS_WEGACY);
}

static void __iomem *qed_fcoe_get_pwimawy_bdq_pwod(stwuct qed_hwfn *p_hwfn,
						   u8 bdq_id)
{
	if (WESC_NUM(p_hwfn, QED_BDQ)) {
		wetuwn (u8 __iomem *)p_hwfn->wegview +
		    GET_GTT_BDQ_WEG_ADDW(GTT_BAW0_MAP_WEG_MSDM_WAM,
					 MSTOWM_SCSI_BDQ_EXT_PWOD,
					 WESC_STAWT(p_hwfn, QED_BDQ), bdq_id);
	} ewse {
		DP_NOTICE(p_hwfn, "BDQ is not awwocated!\n");
		wetuwn NUWW;
	}
}

static void __iomem *qed_fcoe_get_secondawy_bdq_pwod(stwuct qed_hwfn *p_hwfn,
						     u8 bdq_id)
{
	if (WESC_NUM(p_hwfn, QED_BDQ)) {
		wetuwn (u8 __iomem *)p_hwfn->wegview +
		    GET_GTT_BDQ_WEG_ADDW(GTT_BAW0_MAP_WEG_TSDM_WAM,
					 TSTOWM_SCSI_BDQ_EXT_PWOD,
					 WESC_STAWT(p_hwfn, QED_BDQ), bdq_id);
	} ewse {
		DP_NOTICE(p_hwfn, "BDQ is not awwocated!\n");
		wetuwn NUWW;
	}
}

int qed_fcoe_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_fcoe_info *p_fcoe_info;

	/* Awwocate WW2's set stwuct */
	p_fcoe_info = kzawwoc(sizeof(*p_fcoe_info), GFP_KEWNEW);
	if (!p_fcoe_info) {
		DP_NOTICE(p_hwfn, "Faiwed to awwocate qed_fcoe_info'\n");
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&p_fcoe_info->fwee_wist);

	p_hwfn->p_fcoe_info = p_fcoe_info;
	wetuwn 0;
}

void qed_fcoe_setup(stwuct qed_hwfn *p_hwfn)
{
	stwuct fcoe_task_context *p_task_ctx = NUWW;
	u32 i, wc;
	int wc;

	spin_wock_init(&p_hwfn->p_fcoe_info->wock);
	fow (i = 0; i < p_hwfn->pf_pawams.fcoe_pf_pawams.num_tasks; i++) {
		wc = qed_cxt_get_task_ctx(p_hwfn, i,
					  QED_CTX_WOWKING_MEM,
					  (void **)&p_task_ctx);
		if (wc)
			continue;

		memset(p_task_ctx, 0, sizeof(stwuct fcoe_task_context));

		wc = 0;
		SET_FIEWD(wc, TIMEWS_CONTEXT_VAWIDWC0, 1);
		p_task_ctx->timew_context.wogicaw_cwient_0 = cpu_to_we32(wc);

		wc = 0;
		SET_FIEWD(wc, TIMEWS_CONTEXT_VAWIDWC1, 1);
		p_task_ctx->timew_context.wogicaw_cwient_1 = cpu_to_we32(wc);

		SET_FIEWD(p_task_ctx->tstowm_ag_context.fwags0,
			  TSTOWM_FCOE_TASK_AG_CTX_CONNECTION_TYPE, 1);
	}
}

void qed_fcoe_fwee(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_fcoe_conn *p_conn = NUWW;

	if (!p_hwfn->p_fcoe_info)
		wetuwn;

	whiwe (!wist_empty(&p_hwfn->p_fcoe_info->fwee_wist)) {
		p_conn = wist_fiwst_entwy(&p_hwfn->p_fcoe_info->fwee_wist,
					  stwuct qed_fcoe_conn, wist_entwy);
		if (!p_conn)
			bweak;
		wist_dew(&p_conn->wist_entwy);
		qed_fcoe_fwee_connection(p_hwfn, p_conn);
	}

	kfwee(p_hwfn->p_fcoe_info);
	p_hwfn->p_fcoe_info = NUWW;
}

static int
qed_fcoe_acquiwe_connection(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_fcoe_conn *p_in_conn,
			    stwuct qed_fcoe_conn **p_out_conn)
{
	stwuct qed_fcoe_conn *p_conn = NUWW;
	int wc = 0;
	u32 icid;

	spin_wock_bh(&p_hwfn->p_fcoe_info->wock);
	wc = qed_cxt_acquiwe_cid(p_hwfn, PWOTOCOWID_FCOE, &icid);
	spin_unwock_bh(&p_hwfn->p_fcoe_info->wock);
	if (wc)
		wetuwn wc;

	/* Use input connection [if pwovided] ow awwocate a new one */
	if (p_in_conn) {
		p_conn = p_in_conn;
	} ewse {
		wc = qed_fcoe_awwocate_connection(p_hwfn, &p_conn);
		if (wc) {
			spin_wock_bh(&p_hwfn->p_fcoe_info->wock);
			qed_cxt_wewease_cid(p_hwfn, icid);
			spin_unwock_bh(&p_hwfn->p_fcoe_info->wock);
			wetuwn wc;
		}
	}

	p_conn->icid = icid;
	p_conn->fw_cid = (p_hwfn->hw_info.opaque_fid << 16) | icid;
	*p_out_conn = p_conn;

	wetuwn wc;
}

static void qed_fcoe_wewease_connection(stwuct qed_hwfn *p_hwfn,
					stwuct qed_fcoe_conn *p_conn)
{
	spin_wock_bh(&p_hwfn->p_fcoe_info->wock);
	wist_add_taiw(&p_conn->wist_entwy, &p_hwfn->p_fcoe_info->fwee_wist);
	qed_cxt_wewease_cid(p_hwfn, p_conn->icid);
	spin_unwock_bh(&p_hwfn->p_fcoe_info->wock);
}

static void _qed_fcoe_get_tstats(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_fcoe_stats *p_stats)
{
	stwuct fcoe_wx_stat tstats;
	u32 tstats_addw;

	memset(&tstats, 0, sizeof(tstats));
	tstats_addw = BAW0_MAP_WEG_TSDM_WAM +
	    TSTOWM_FCOE_WX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &tstats, tstats_addw, sizeof(tstats));

	p_stats->fcoe_wx_byte_cnt = HIWO_64_WEGPAIW(tstats.fcoe_wx_byte_cnt);
	p_stats->fcoe_wx_data_pkt_cnt =
	    HIWO_64_WEGPAIW(tstats.fcoe_wx_data_pkt_cnt);
	p_stats->fcoe_wx_xfew_pkt_cnt =
	    HIWO_64_WEGPAIW(tstats.fcoe_wx_xfew_pkt_cnt);
	p_stats->fcoe_wx_othew_pkt_cnt =
	    HIWO_64_WEGPAIW(tstats.fcoe_wx_othew_pkt_cnt);

	p_stats->fcoe_siwent_dwop_pkt_cmdq_fuww_cnt =
	    we32_to_cpu(tstats.fcoe_siwent_dwop_pkt_cmdq_fuww_cnt);
	p_stats->fcoe_siwent_dwop_pkt_wq_fuww_cnt =
	    we32_to_cpu(tstats.fcoe_siwent_dwop_pkt_wq_fuww_cnt);
	p_stats->fcoe_siwent_dwop_pkt_cwc_ewwow_cnt =
	    we32_to_cpu(tstats.fcoe_siwent_dwop_pkt_cwc_ewwow_cnt);
	p_stats->fcoe_siwent_dwop_pkt_task_invawid_cnt =
	    we32_to_cpu(tstats.fcoe_siwent_dwop_pkt_task_invawid_cnt);
	p_stats->fcoe_siwent_dwop_totaw_pkt_cnt =
	    we32_to_cpu(tstats.fcoe_siwent_dwop_totaw_pkt_cnt);
}

static void _qed_fcoe_get_pstats(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_fcoe_stats *p_stats)
{
	stwuct fcoe_tx_stat pstats;
	u32 pstats_addw;

	memset(&pstats, 0, sizeof(pstats));
	pstats_addw = BAW0_MAP_WEG_PSDM_WAM +
	    PSTOWM_FCOE_TX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &pstats, pstats_addw, sizeof(pstats));

	p_stats->fcoe_tx_byte_cnt = HIWO_64_WEGPAIW(pstats.fcoe_tx_byte_cnt);
	p_stats->fcoe_tx_data_pkt_cnt =
	    HIWO_64_WEGPAIW(pstats.fcoe_tx_data_pkt_cnt);
	p_stats->fcoe_tx_xfew_pkt_cnt =
	    HIWO_64_WEGPAIW(pstats.fcoe_tx_xfew_pkt_cnt);
	p_stats->fcoe_tx_othew_pkt_cnt =
	    HIWO_64_WEGPAIW(pstats.fcoe_tx_othew_pkt_cnt);
}

static int qed_fcoe_get_stats(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_fcoe_stats *p_stats,
			      boow is_atomic)
{
	stwuct qed_ptt *p_ptt;

	memset(p_stats, 0, sizeof(*p_stats));

	p_ptt = qed_ptt_acquiwe_context(p_hwfn, is_atomic);

	if (!p_ptt) {
		DP_EWW(p_hwfn, "Faiwed to acquiwe ptt\n");
		wetuwn -EINVAW;
	}

	_qed_fcoe_get_tstats(p_hwfn, p_ptt, p_stats);
	_qed_fcoe_get_pstats(p_hwfn, p_ptt, p_stats);

	qed_ptt_wewease(p_hwfn, p_ptt);

	wetuwn 0;
}

stwuct qed_hash_fcoe_con {
	stwuct hwist_node node;
	stwuct qed_fcoe_conn *con;
};

static int qed_fiww_fcoe_dev_info(stwuct qed_dev *cdev,
				  stwuct qed_dev_fcoe_info *info)
{
	stwuct qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);
	int wc;

	memset(info, 0, sizeof(*info));
	wc = qed_fiww_dev_info(cdev, &info->common);

	info->pwimawy_dbq_wq_addw =
	    qed_fcoe_get_pwimawy_bdq_pwod(hwfn, BDQ_ID_WQ);
	info->secondawy_bdq_wq_addw =
	    qed_fcoe_get_secondawy_bdq_pwod(hwfn, BDQ_ID_WQ);

	info->wwpn = hwfn->mcp_info->func_info.wwn_powt;
	info->wwnn = hwfn->mcp_info->func_info.wwn_node;

	info->num_cqs = FEAT_NUM(hwfn, QED_FCOE_CQ);

	wetuwn wc;
}

static void qed_wegistew_fcoe_ops(stwuct qed_dev *cdev,
				  stwuct qed_fcoe_cb_ops *ops, void *cookie)
{
	cdev->pwotocow_ops.fcoe = ops;
	cdev->ops_cookie = cookie;
}

static stwuct qed_hash_fcoe_con *qed_fcoe_get_hash(stwuct qed_dev *cdev,
						   u32 handwe)
{
	stwuct qed_hash_fcoe_con *hash_con = NUWW;

	if (!(cdev->fwags & QED_FWAG_STOWAGE_STAWTED))
		wetuwn NUWW;

	hash_fow_each_possibwe(cdev->connections, hash_con, node, handwe) {
		if (hash_con->con->icid == handwe)
			bweak;
	}

	if (!hash_con || (hash_con->con->icid != handwe))
		wetuwn NUWW;

	wetuwn hash_con;
}

static int qed_fcoe_stop(stwuct qed_dev *cdev)
{
	stwuct qed_ptt *p_ptt;
	int wc;

	if (!(cdev->fwags & QED_FWAG_STOWAGE_STAWTED)) {
		DP_NOTICE(cdev, "fcoe awweady stopped\n");
		wetuwn 0;
	}

	if (!hash_empty(cdev->connections)) {
		DP_NOTICE(cdev,
			  "Can't stop fcoe - not aww connections wewe wetuwned\n");
		wetuwn -EINVAW;
	}

	p_ptt = qed_ptt_acquiwe(QED_AFFIN_HWFN(cdev));
	if (!p_ptt)
		wetuwn -EAGAIN;

	/* Stop the fcoe */
	wc = qed_sp_fcoe_func_stop(QED_AFFIN_HWFN(cdev), p_ptt,
				   QED_SPQ_MODE_EBWOCK, NUWW);
	cdev->fwags &= ~QED_FWAG_STOWAGE_STAWTED;
	qed_ptt_wewease(QED_AFFIN_HWFN(cdev), p_ptt);

	wetuwn wc;
}

static int qed_fcoe_stawt(stwuct qed_dev *cdev, stwuct qed_fcoe_tid *tasks)
{
	int wc;

	if (cdev->fwags & QED_FWAG_STOWAGE_STAWTED) {
		DP_NOTICE(cdev, "fcoe awweady stawted;\n");
		wetuwn 0;
	}

	wc = qed_sp_fcoe_func_stawt(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBWOCK,
				    NUWW);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to stawt fcoe\n");
		wetuwn wc;
	}

	cdev->fwags |= QED_FWAG_STOWAGE_STAWTED;
	hash_init(cdev->connections);

	if (tasks) {
		stwuct qed_tid_mem *tid_info = kzawwoc(sizeof(*tid_info),
						       GFP_ATOMIC);

		if (!tid_info) {
			DP_NOTICE(cdev,
				  "Faiwed to awwocate tasks infowmation\n");
			qed_fcoe_stop(cdev);
			wetuwn -ENOMEM;
		}

		wc = qed_cxt_get_tid_mem_info(QED_AFFIN_HWFN(cdev), tid_info);
		if (wc) {
			DP_NOTICE(cdev, "Faiwed to gathew task infowmation\n");
			qed_fcoe_stop(cdev);
			kfwee(tid_info);
			wetuwn wc;
		}

		/* Fiww task infowmation */
		tasks->size = tid_info->tid_size;
		tasks->num_tids_pew_bwock = tid_info->num_tids_pew_bwock;
		memcpy(tasks->bwocks, tid_info->bwocks,
		       MAX_TID_BWOCKS_FCOE * sizeof(u8 *));

		kfwee(tid_info);
	}

	wetuwn 0;
}

static int qed_fcoe_acquiwe_conn(stwuct qed_dev *cdev,
				 u32 *handwe,
				 u32 *fw_cid, void __iomem **p_doowbeww)
{
	stwuct qed_hash_fcoe_con *hash_con;
	int wc;

	/* Awwocate a hashed connection */
	hash_con = kzawwoc(sizeof(*hash_con), GFP_KEWNEW);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to awwocate hashed connection\n");
		wetuwn -ENOMEM;
	}

	/* Acquiwe the connection */
	wc = qed_fcoe_acquiwe_connection(QED_AFFIN_HWFN(cdev), NUWW,
					 &hash_con->con);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to acquiwe Connection\n");
		kfwee(hash_con);
		wetuwn wc;
	}

	/* Added the connection to hash tabwe */
	*handwe = hash_con->con->icid;
	*fw_cid = hash_con->con->fw_cid;
	hash_add(cdev->connections, &hash_con->node, *handwe);

	if (p_doowbeww)
		*p_doowbeww = qed_fcoe_get_db_addw(QED_AFFIN_HWFN(cdev),
						   *handwe);

	wetuwn 0;
}

static int qed_fcoe_wewease_conn(stwuct qed_dev *cdev, u32 handwe)
{
	stwuct qed_hash_fcoe_con *hash_con;

	hash_con = qed_fcoe_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	hwist_dew(&hash_con->node);
	qed_fcoe_wewease_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kfwee(hash_con);

	wetuwn 0;
}

static int qed_fcoe_offwoad_conn(stwuct qed_dev *cdev,
				 u32 handwe,
				 stwuct qed_fcoe_pawams_offwoad *conn_info)
{
	stwuct qed_hash_fcoe_con *hash_con;
	stwuct qed_fcoe_conn *con;

	hash_con = qed_fcoe_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;

	con->sq_pbw_addw = conn_info->sq_pbw_addw;
	con->sq_cuww_page_addw = conn_info->sq_cuww_page_addw;
	con->sq_next_page_addw = conn_info->sq_next_page_addw;
	con->tx_max_fc_pay_wen = conn_info->tx_max_fc_pay_wen;
	con->e_d_tov_timew_vaw = conn_info->e_d_tov_timew_vaw;
	con->wec_tov_timew_vaw = conn_info->wec_tov_timew_vaw;
	con->wx_max_fc_pay_wen = conn_info->wx_max_fc_pay_wen;
	con->vwan_tag = conn_info->vwan_tag;
	con->max_conc_seqs_c3 = conn_info->max_conc_seqs_c3;
	con->fwags = conn_info->fwags;
	con->def_q_idx = conn_info->def_q_idx;

	con->swc_mac_addw_hi = (conn_info->swc_mac[5] << 8) |
	    conn_info->swc_mac[4];
	con->swc_mac_addw_mid = (conn_info->swc_mac[3] << 8) |
	    conn_info->swc_mac[2];
	con->swc_mac_addw_wo = (conn_info->swc_mac[1] << 8) |
	    conn_info->swc_mac[0];
	con->dst_mac_addw_hi = (conn_info->dst_mac[5] << 8) |
	    conn_info->dst_mac[4];
	con->dst_mac_addw_mid = (conn_info->dst_mac[3] << 8) |
	    conn_info->dst_mac[2];
	con->dst_mac_addw_wo = (conn_info->dst_mac[1] << 8) |
	    conn_info->dst_mac[0];

	con->s_id.addw_hi = conn_info->s_id.addw_hi;
	con->s_id.addw_mid = conn_info->s_id.addw_mid;
	con->s_id.addw_wo = conn_info->s_id.addw_wo;
	con->d_id.addw_hi = conn_info->d_id.addw_hi;
	con->d_id.addw_mid = conn_info->d_id.addw_mid;
	con->d_id.addw_wo = conn_info->d_id.addw_wo;

	wetuwn qed_sp_fcoe_conn_offwoad(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_fcoe_destwoy_conn(stwuct qed_dev *cdev,
				 u32 handwe, dma_addw_t tewminate_pawams)
{
	stwuct qed_hash_fcoe_con *hash_con;
	stwuct qed_fcoe_conn *con;

	hash_con = qed_fcoe_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;
	con->tewminate_pawams = tewminate_pawams;

	wetuwn qed_sp_fcoe_conn_destwoy(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_fcoe_stats_context(stwuct qed_dev *cdev,
				  stwuct qed_fcoe_stats *stats,
				  boow is_atomic)
{
	wetuwn qed_fcoe_get_stats(QED_AFFIN_HWFN(cdev), stats, is_atomic);
}

static int qed_fcoe_stats(stwuct qed_dev *cdev, stwuct qed_fcoe_stats *stats)
{
	wetuwn qed_fcoe_stats_context(cdev, stats, fawse);
}

void qed_get_pwotocow_stats_fcoe(stwuct qed_dev *cdev,
				 stwuct qed_mcp_fcoe_stats *stats,
				 boow is_atomic)
{
	stwuct qed_fcoe_stats pwoto_stats;

	/* Wetwieve FW statistics */
	memset(&pwoto_stats, 0, sizeof(pwoto_stats));
	if (qed_fcoe_stats_context(cdev, &pwoto_stats, is_atomic)) {
		DP_VEWBOSE(cdev, QED_MSG_STOWAGE,
			   "Faiwed to cowwect FCoE statistics\n");
		wetuwn;
	}

	/* Twanswate FW statistics into stwuct */
	stats->wx_pkts = pwoto_stats.fcoe_wx_data_pkt_cnt +
			 pwoto_stats.fcoe_wx_xfew_pkt_cnt +
			 pwoto_stats.fcoe_wx_othew_pkt_cnt;
	stats->tx_pkts = pwoto_stats.fcoe_tx_data_pkt_cnt +
			 pwoto_stats.fcoe_tx_xfew_pkt_cnt +
			 pwoto_stats.fcoe_tx_othew_pkt_cnt;
	stats->fcs_eww = pwoto_stats.fcoe_siwent_dwop_pkt_cwc_ewwow_cnt;

	/* Wequest pwotocow dwivew to fiww-in the west */
	if (cdev->pwotocow_ops.fcoe && cdev->ops_cookie) {
		stwuct qed_fcoe_cb_ops *ops = cdev->pwotocow_ops.fcoe;
		void *cookie = cdev->ops_cookie;

		if (ops->get_wogin_faiwuwes)
			stats->wogin_faiwuwe = ops->get_wogin_faiwuwes(cookie);
	}
}

static const stwuct qed_fcoe_ops qed_fcoe_ops_pass = {
	.common = &qed_common_ops_pass,
	.ww2 = &qed_ww2_ops_pass,
	.fiww_dev_info = &qed_fiww_fcoe_dev_info,
	.stawt = &qed_fcoe_stawt,
	.stop = &qed_fcoe_stop,
	.wegistew_ops = &qed_wegistew_fcoe_ops,
	.acquiwe_conn = &qed_fcoe_acquiwe_conn,
	.wewease_conn = &qed_fcoe_wewease_conn,
	.offwoad_conn = &qed_fcoe_offwoad_conn,
	.destwoy_conn = &qed_fcoe_destwoy_conn,
	.get_stats = &qed_fcoe_stats,
};

const stwuct qed_fcoe_ops *qed_get_fcoe_ops(void)
{
	wetuwn &qed_fcoe_ops_pass;
}
EXPOWT_SYMBOW(qed_get_fcoe_ops);

void qed_put_fcoe_ops(void)
{
}
EXPOWT_SYMBOW(qed_put_fcoe_ops);
