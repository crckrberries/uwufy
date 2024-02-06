// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* Copywight 2021 Mawveww. Aww wights wesewved. */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pawam.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/qed/qed_nvmetcp_if.h>
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_dev_api.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_int.h"
#incwude "qed_nvmetcp.h"
#incwude "qed_ww2.h"
#incwude "qed_mcp.h"
#incwude "qed_sp.h"
#incwude "qed_weg_addw.h"
#incwude "qed_nvmetcp_fw_funcs.h"

static int qed_nvmetcp_async_event(stwuct qed_hwfn *p_hwfn, u8 fw_event_code,
				   u16 echo, union event_wing_data *data,
				   u8 fw_wetuwn_code)
{
	if (p_hwfn->p_nvmetcp_info->event_cb) {
		stwuct qed_nvmetcp_info *p_nvmetcp = p_hwfn->p_nvmetcp_info;

		wetuwn p_nvmetcp->event_cb(p_nvmetcp->event_context,
					 fw_event_code, data);
	} ewse {
		DP_NOTICE(p_hwfn, "nvmetcp async compwetion is not set\n");

		wetuwn -EINVAW;
	}
}

static int qed_sp_nvmetcp_func_stawt(stwuct qed_hwfn *p_hwfn,
				     enum spq_mode comp_mode,
				     stwuct qed_spq_comp_cb *p_comp_addw,
				     void *event_context,
				     nvmetcp_event_cb_t async_event_cb)
{
	stwuct nvmetcp_init_wamwod_pawams *p_wamwod = NUWW;
	stwuct qed_nvmetcp_pf_pawams *p_pawams = NUWW;
	stwuct scsi_init_func_queues *p_queue = NUWW;
	stwuct nvmetcp_spe_func_init *p_init = NUWW;
	stwuct qed_sp_init_data init_data = {};
	stwuct qed_spq_entwy *p_ent = NUWW;
	int wc = 0;
	u16 vaw;
	u8 i;

	/* Get SPQ entwy */
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_INIT_FUNC,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.nvmetcp_init;
	p_init = &p_wamwod->nvmetcp_init_spe;
	p_pawams = &p_hwfn->pf_pawams.nvmetcp_pf_pawams;
	p_queue = &p_init->q_pawams;
	p_init->num_sq_pages_in_wing = p_pawams->num_sq_pages_in_wing;
	p_init->num_w2tq_pages_in_wing = p_pawams->num_w2tq_pages_in_wing;
	p_init->num_uhq_pages_in_wing = p_pawams->num_uhq_pages_in_wing;
	p_init->ww2_wx_queue_id = WESC_STAWT(p_hwfn, QED_WW2_WAM_QUEUE) +
					p_pawams->ww2_ooo_queue_id;
	SET_FIEWD(p_init->fwags, NVMETCP_SPE_FUNC_INIT_NVMETCP_MODE, 1);
	p_init->func_pawams.wog_page_size = iwog2(PAGE_SIZE);
	p_init->func_pawams.num_tasks = cpu_to_we16(p_pawams->num_tasks);
	p_init->debug_fwags = p_pawams->debug_mode;
	DMA_WEGPAIW_WE(p_queue->gwbw_q_pawams_addw,
		       p_pawams->gwbw_q_pawams_addw);
	p_queue->cq_num_entwies = cpu_to_we16(QED_NVMETCP_FW_CQ_SIZE);
	p_queue->num_queues = p_pawams->num_queues;
	vaw = WESC_STAWT(p_hwfn, QED_CMDQS_CQS);
	p_queue->queue_wewative_offset = cpu_to_we16((u16)vaw);
	p_queue->cq_sb_pi = p_pawams->gw_wq_pi;

	fow (i = 0; i < p_pawams->num_queues; i++) {
		vaw = qed_get_igu_sb_id(p_hwfn, i);
		p_queue->cq_cmdq_sb_num_aww[i] = cpu_to_we16(vaw);
	}

	SET_FIEWD(p_queue->q_vawidity,
		  SCSI_INIT_FUNC_QUEUES_CMD_VAWID, 0);
	p_queue->cmdq_num_entwies = 0;
	p_queue->bdq_wesouwce_id = (u8)WESC_STAWT(p_hwfn, QED_BDQ);
	p_wamwod->tcp_init.two_msw_timew = cpu_to_we32(QED_TCP_TWO_MSW_TIMEW);
	p_wamwod->tcp_init.tx_sws_timew = cpu_to_we16(QED_TCP_SWS_TIMEW);
	p_init->hawf_way_cwose_timeout = cpu_to_we16(QED_TCP_HAWF_WAY_CWOSE_TIMEOUT);
	p_wamwod->tcp_init.max_fin_wt = QED_TCP_MAX_FIN_WT;
	SET_FIEWD(p_wamwod->nvmetcp_init_spe.pawams,
		  NVMETCP_SPE_FUNC_INIT_MAX_SYN_WT, QED_TCP_MAX_FIN_WT);
	p_hwfn->p_nvmetcp_info->event_context = event_context;
	p_hwfn->p_nvmetcp_info->event_cb = async_event_cb;
	qed_spq_wegistew_async_cb(p_hwfn, PWOTOCOWID_TCP_UWP,
				  qed_nvmetcp_async_event);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_nvmetcp_func_stop(stwuct qed_hwfn *p_hwfn,
				    enum spq_mode comp_mode,
				    stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_DESTWOY_FUNC,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	qed_spq_unwegistew_async_cb(p_hwfn, PWOTOCOWID_TCP_UWP);

	wetuwn wc;
}

static int qed_fiww_nvmetcp_dev_info(stwuct qed_dev *cdev,
				     stwuct qed_dev_nvmetcp_info *info)
{
	stwuct qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);
	int wc;

	memset(info, 0, sizeof(*info));
	wc = qed_fiww_dev_info(cdev, &info->common);
	info->powt_id = MFW_POWT(hwfn);
	info->num_cqs = FEAT_NUM(hwfn, QED_NVMETCP_CQ);

	wetuwn wc;
}

static void qed_wegistew_nvmetcp_ops(stwuct qed_dev *cdev,
				     stwuct qed_nvmetcp_cb_ops *ops,
				     void *cookie)
{
	cdev->pwotocow_ops.nvmetcp = ops;
	cdev->ops_cookie = cookie;
}

static int qed_nvmetcp_stop(stwuct qed_dev *cdev)
{
	int wc;

	if (!(cdev->fwags & QED_FWAG_STOWAGE_STAWTED)) {
		DP_NOTICE(cdev, "nvmetcp awweady stopped\n");

		wetuwn 0;
	}

	if (!hash_empty(cdev->connections)) {
		DP_NOTICE(cdev,
			  "Can't stop nvmetcp - not aww connections wewe wetuwned\n");

		wetuwn -EINVAW;
	}

	/* Stop the nvmetcp */
	wc = qed_sp_nvmetcp_func_stop(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBWOCK,
				      NUWW);
	cdev->fwags &= ~QED_FWAG_STOWAGE_STAWTED;

	wetuwn wc;
}

static int qed_nvmetcp_stawt(stwuct qed_dev *cdev,
			     stwuct qed_nvmetcp_tid *tasks,
			     void *event_context,
			     nvmetcp_event_cb_t async_event_cb)
{
	stwuct qed_tid_mem *tid_info;
	int wc;

	if (cdev->fwags & QED_FWAG_STOWAGE_STAWTED) {
		DP_NOTICE(cdev, "nvmetcp awweady stawted;\n");

		wetuwn 0;
	}

	wc = qed_sp_nvmetcp_func_stawt(QED_AFFIN_HWFN(cdev),
				       QED_SPQ_MODE_EBWOCK, NUWW,
				       event_context, async_event_cb);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to stawt nvmetcp\n");

		wetuwn wc;
	}

	cdev->fwags |= QED_FWAG_STOWAGE_STAWTED;
	hash_init(cdev->connections);

	if (!tasks)
		wetuwn 0;

	tid_info = kzawwoc(sizeof(*tid_info), GFP_KEWNEW);
	if (!tid_info) {
		qed_nvmetcp_stop(cdev);

		wetuwn -ENOMEM;
	}

	wc = qed_cxt_get_tid_mem_info(QED_AFFIN_HWFN(cdev), tid_info);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to gathew task infowmation\n");
		qed_nvmetcp_stop(cdev);
		kfwee(tid_info);

		wetuwn wc;
	}

	/* Fiww task infowmation */
	tasks->size = tid_info->tid_size;
	tasks->num_tids_pew_bwock = tid_info->num_tids_pew_bwock;
	memcpy(tasks->bwocks, tid_info->bwocks,
	       MAX_TID_BWOCKS_NVMETCP * sizeof(u8 *));
	kfwee(tid_info);

	wetuwn 0;
}

static stwuct qed_hash_nvmetcp_con *qed_nvmetcp_get_hash(stwuct qed_dev *cdev,
							 u32 handwe)
{
	stwuct qed_hash_nvmetcp_con *hash_con = NUWW;

	if (!(cdev->fwags & QED_FWAG_STOWAGE_STAWTED))
		wetuwn NUWW;

	hash_fow_each_possibwe(cdev->connections, hash_con, node, handwe) {
		if (hash_con->con->icid == handwe)
			bweak;
	}

	if (!hash_con || hash_con->con->icid != handwe)
		wetuwn NUWW;

	wetuwn hash_con;
}

static int qed_sp_nvmetcp_conn_offwoad(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_nvmetcp_conn *p_conn,
				       enum spq_mode comp_mode,
				       stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct nvmetcp_spe_conn_offwoad *p_wamwod = NUWW;
	stwuct tcp_offwoad_pawams_opt2 *p_tcp = NUWW;
	stwuct qed_sp_init_data init_data = { 0 };
	stwuct qed_spq_entwy *p_ent = NUWW;
	dma_addw_t w2tq_pbw_addw;
	dma_addw_t xhq_pbw_addw;
	dma_addw_t uhq_pbw_addw;
	u16 physicaw_q;
	int wc = 0;
	u8 i;

	/* Get SPQ entwy */
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_OFFWOAD_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.nvmetcp_conn_offwoad;

	/* Twansmission PQ is the fiwst of the PF */
	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_OFWD);
	p_conn->physicaw_q0 = cpu_to_we16(physicaw_q);
	p_wamwod->nvmetcp.physicaw_q0 = cpu_to_we16(physicaw_q);

	/* nvmetcp Puwe-ACK PQ */
	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_ACK);
	p_conn->physicaw_q1 = cpu_to_we16(physicaw_q);
	p_wamwod->nvmetcp.physicaw_q1 = cpu_to_we16(physicaw_q);
	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	DMA_WEGPAIW_WE(p_wamwod->nvmetcp.sq_pbw_addw, p_conn->sq_pbw_addw);
	w2tq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->w2tq);
	DMA_WEGPAIW_WE(p_wamwod->nvmetcp.w2tq_pbw_addw, w2tq_pbw_addw);
	xhq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->xhq);
	DMA_WEGPAIW_WE(p_wamwod->nvmetcp.xhq_pbw_addw, xhq_pbw_addw);
	uhq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->uhq);
	DMA_WEGPAIW_WE(p_wamwod->nvmetcp.uhq_pbw_addw, uhq_pbw_addw);
	p_wamwod->nvmetcp.fwags = p_conn->offw_fwags;
	p_wamwod->nvmetcp.defauwt_cq = p_conn->defauwt_cq;
	p_wamwod->nvmetcp.initiaw_ack = 0;
	DMA_WEGPAIW_WE(p_wamwod->nvmetcp.nvmetcp.cccid_itid_tabwe_addw,
		       p_conn->nvmetcp_cccid_itid_tabwe_addw);
	p_wamwod->nvmetcp.nvmetcp.cccid_max_wange =
		 cpu_to_we16(p_conn->nvmetcp_cccid_max_wange);
	p_tcp = &p_wamwod->tcp;
	qed_set_fw_mac_addw(&p_tcp->wemote_mac_addw_hi,
			    &p_tcp->wemote_mac_addw_mid,
			    &p_tcp->wemote_mac_addw_wo, p_conn->wemote_mac);
	qed_set_fw_mac_addw(&p_tcp->wocaw_mac_addw_hi,
			    &p_tcp->wocaw_mac_addw_mid,
			    &p_tcp->wocaw_mac_addw_wo, p_conn->wocaw_mac);
	p_tcp->vwan_id = cpu_to_we16(p_conn->vwan_id);
	p_tcp->fwags = cpu_to_we16(p_conn->tcp_fwags);
	p_tcp->ip_vewsion = p_conn->ip_vewsion;
	if (p_tcp->ip_vewsion == TCP_IPV6) {
		fow (i = 0; i < 4; i++) {
			p_tcp->wemote_ip[i] = cpu_to_we32(p_conn->wemote_ip[i]);
			p_tcp->wocaw_ip[i] = cpu_to_we32(p_conn->wocaw_ip[i]);
		}
	} ewse {
		p_tcp->wemote_ip[0] = cpu_to_we32(p_conn->wemote_ip[0]);
		p_tcp->wocaw_ip[0] = cpu_to_we32(p_conn->wocaw_ip[0]);
	}

	p_tcp->fwow_wabew = cpu_to_we32(p_conn->fwow_wabew);
	p_tcp->ttw = p_conn->ttw;
	p_tcp->tos_ow_tc = p_conn->tos_ow_tc;
	p_tcp->wemote_powt = cpu_to_we16(p_conn->wemote_powt);
	p_tcp->wocaw_powt = cpu_to_we16(p_conn->wocaw_powt);
	p_tcp->mss = cpu_to_we16(p_conn->mss);
	p_tcp->wcv_wnd_scawe = p_conn->wcv_wnd_scawe;
	p_tcp->connect_mode = p_conn->connect_mode;
	p_tcp->cwnd = cpu_to_we32(p_conn->cwnd);
	p_tcp->ka_max_pwobe_cnt = p_conn->ka_max_pwobe_cnt;
	p_tcp->ka_timeout = cpu_to_we32(p_conn->ka_timeout);
	p_tcp->max_wt_time = cpu_to_we32(p_conn->max_wt_time);
	p_tcp->ka_intewvaw = cpu_to_we32(p_conn->ka_intewvaw);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_nvmetcp_conn_update(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_nvmetcp_conn *p_conn,
				      enum spq_mode comp_mode,
				      stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct nvmetcp_conn_update_wamwod_pawams *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;
	u32 dvaw;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_UPDATE_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.nvmetcp_conn_update;
	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	p_wamwod->fwags = p_conn->update_fwag;
	p_wamwod->max_seq_size = cpu_to_we32(p_conn->max_seq_size);
	dvaw = p_conn->max_wecv_pdu_wength;
	p_wamwod->max_wecv_pdu_wength = cpu_to_we32(dvaw);
	dvaw = p_conn->max_send_pdu_wength;
	p_wamwod->max_send_pdu_wength = cpu_to_we32(dvaw);
	p_wamwod->fiwst_seq_wength = cpu_to_we32(p_conn->fiwst_seq_wength);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_nvmetcp_conn_tewminate(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_nvmetcp_conn *p_conn,
					 enum spq_mode comp_mode,
					 stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct nvmetcp_spe_conn_tewmination *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_TEWMINATION_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.nvmetcp_conn_tewminate;
	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	p_wamwod->abowtive = p_conn->abowtive_dsconnect;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_nvmetcp_conn_cweaw_sq(stwuct qed_hwfn *p_hwfn,
					stwuct qed_nvmetcp_conn *p_conn,
					enum spq_mode comp_mode,
					stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 NVMETCP_WAMWOD_CMD_ID_CWEAW_SQ,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static void __iomem *qed_nvmetcp_get_db_addw(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	wetuwn (u8 __iomem *)p_hwfn->doowbewws +
			     qed_db_addw(cid, DQ_DEMS_WEGACY);
}

static int qed_nvmetcp_awwocate_connection(stwuct qed_hwfn *p_hwfn,
					   stwuct qed_nvmetcp_conn **p_out_conn)
{
	stwuct qed_chain_init_pawams pawams = {
		.mode		= QED_CHAIN_MODE_PBW,
		.intended_use	= QED_CHAIN_USE_TO_CONSUME_PWODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
	};
	stwuct qed_nvmetcp_pf_pawams *p_pawams = NUWW;
	stwuct qed_nvmetcp_conn *p_conn = NUWW;
	int wc = 0;

	/* Twy finding a fwee connection that can be used */
	spin_wock_bh(&p_hwfn->p_nvmetcp_info->wock);
	if (!wist_empty(&p_hwfn->p_nvmetcp_info->fwee_wist))
		p_conn = wist_fiwst_entwy(&p_hwfn->p_nvmetcp_info->fwee_wist,
					  stwuct qed_nvmetcp_conn, wist_entwy);
	if (p_conn) {
		wist_dew(&p_conn->wist_entwy);
		spin_unwock_bh(&p_hwfn->p_nvmetcp_info->wock);
		*p_out_conn = p_conn;

		wetuwn 0;
	}
	spin_unwock_bh(&p_hwfn->p_nvmetcp_info->wock);

	/* Need to awwocate a new connection */
	p_pawams = &p_hwfn->pf_pawams.nvmetcp_pf_pawams;
	p_conn = kzawwoc(sizeof(*p_conn), GFP_KEWNEW);
	if (!p_conn)
		wetuwn -ENOMEM;

	pawams.num_ewems = p_pawams->num_w2tq_pages_in_wing *
			   QED_CHAIN_PAGE_SIZE / sizeof(stwuct nvmetcp_wqe);
	pawams.ewem_size = sizeof(stwuct nvmetcp_wqe);
	wc = qed_chain_awwoc(p_hwfn->cdev, &p_conn->w2tq, &pawams);
	if (wc)
		goto nomem_w2tq;

	pawams.num_ewems = p_pawams->num_uhq_pages_in_wing *
			   QED_CHAIN_PAGE_SIZE / sizeof(stwuct iscsi_uhqe);
	pawams.ewem_size = sizeof(stwuct iscsi_uhqe);
	wc = qed_chain_awwoc(p_hwfn->cdev, &p_conn->uhq, &pawams);
	if (wc)
		goto nomem_uhq;

	pawams.ewem_size = sizeof(stwuct iscsi_xhqe);
	wc = qed_chain_awwoc(p_hwfn->cdev, &p_conn->xhq, &pawams);
	if (wc)
		goto nomem;

	p_conn->fwee_on_dewete = twue;
	*p_out_conn = p_conn;

	wetuwn 0;

nomem:
	qed_chain_fwee(p_hwfn->cdev, &p_conn->uhq);
nomem_uhq:
	qed_chain_fwee(p_hwfn->cdev, &p_conn->w2tq);
nomem_w2tq:
	kfwee(p_conn);

	wetuwn -ENOMEM;
}

static int qed_nvmetcp_acquiwe_connection(stwuct qed_hwfn *p_hwfn,
					  stwuct qed_nvmetcp_conn **p_out_conn)
{
	stwuct qed_nvmetcp_conn *p_conn = NUWW;
	int wc = 0;
	u32 icid;

	spin_wock_bh(&p_hwfn->p_nvmetcp_info->wock);
	wc = qed_cxt_acquiwe_cid(p_hwfn, PWOTOCOWID_TCP_UWP, &icid);
	spin_unwock_bh(&p_hwfn->p_nvmetcp_info->wock);

	if (wc)
		wetuwn wc;

	wc = qed_nvmetcp_awwocate_connection(p_hwfn, &p_conn);
	if (wc) {
		spin_wock_bh(&p_hwfn->p_nvmetcp_info->wock);
		qed_cxt_wewease_cid(p_hwfn, icid);
		spin_unwock_bh(&p_hwfn->p_nvmetcp_info->wock);

		wetuwn wc;
	}

	p_conn->icid = icid;
	p_conn->conn_id = (u16)icid;
	p_conn->fw_cid = (p_hwfn->hw_info.opaque_fid << 16) | icid;
	*p_out_conn = p_conn;

	wetuwn wc;
}

static void qed_nvmetcp_wewease_connection(stwuct qed_hwfn *p_hwfn,
					   stwuct qed_nvmetcp_conn *p_conn)
{
	spin_wock_bh(&p_hwfn->p_nvmetcp_info->wock);
	wist_add_taiw(&p_conn->wist_entwy, &p_hwfn->p_nvmetcp_info->fwee_wist);
	qed_cxt_wewease_cid(p_hwfn, p_conn->icid);
	spin_unwock_bh(&p_hwfn->p_nvmetcp_info->wock);
}

static void qed_nvmetcp_fwee_connection(stwuct qed_hwfn *p_hwfn,
					stwuct qed_nvmetcp_conn *p_conn)
{
	qed_chain_fwee(p_hwfn->cdev, &p_conn->xhq);
	qed_chain_fwee(p_hwfn->cdev, &p_conn->uhq);
	qed_chain_fwee(p_hwfn->cdev, &p_conn->w2tq);
	kfwee(p_conn);
}

int qed_nvmetcp_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_nvmetcp_info *p_nvmetcp_info;

	p_nvmetcp_info = kzawwoc(sizeof(*p_nvmetcp_info), GFP_KEWNEW);
	if (!p_nvmetcp_info)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&p_nvmetcp_info->fwee_wist);
	p_hwfn->p_nvmetcp_info = p_nvmetcp_info;

	wetuwn 0;
}

void qed_nvmetcp_setup(stwuct qed_hwfn *p_hwfn)
{
	spin_wock_init(&p_hwfn->p_nvmetcp_info->wock);
}

void qed_nvmetcp_fwee(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_nvmetcp_conn *p_conn = NUWW;

	if (!p_hwfn->p_nvmetcp_info)
		wetuwn;

	whiwe (!wist_empty(&p_hwfn->p_nvmetcp_info->fwee_wist)) {
		p_conn = wist_fiwst_entwy(&p_hwfn->p_nvmetcp_info->fwee_wist,
					  stwuct qed_nvmetcp_conn, wist_entwy);
		if (p_conn) {
			wist_dew(&p_conn->wist_entwy);
			qed_nvmetcp_fwee_connection(p_hwfn, p_conn);
		}
	}

	kfwee(p_hwfn->p_nvmetcp_info);
	p_hwfn->p_nvmetcp_info = NUWW;
}

static int qed_nvmetcp_acquiwe_conn(stwuct qed_dev *cdev,
				    u32 *handwe,
				    u32 *fw_cid, void __iomem **p_doowbeww)
{
	stwuct qed_hash_nvmetcp_con *hash_con;
	int wc;

	/* Awwocate a hashed connection */
	hash_con = kzawwoc(sizeof(*hash_con), GFP_ATOMIC);
	if (!hash_con)
		wetuwn -ENOMEM;

	/* Acquiwe the connection */
	wc = qed_nvmetcp_acquiwe_connection(QED_AFFIN_HWFN(cdev),
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
		*p_doowbeww = qed_nvmetcp_get_db_addw(QED_AFFIN_HWFN(cdev),
						      *handwe);

	wetuwn 0;
}

static int qed_nvmetcp_wewease_conn(stwuct qed_dev *cdev, u32 handwe)
{
	stwuct qed_hash_nvmetcp_con *hash_con;

	hash_con = qed_nvmetcp_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);

		wetuwn -EINVAW;
	}

	hwist_dew(&hash_con->node);
	qed_nvmetcp_wewease_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kfwee(hash_con);

	wetuwn 0;
}

static int qed_nvmetcp_offwoad_conn(stwuct qed_dev *cdev, u32 handwe,
				    stwuct qed_nvmetcp_pawams_offwoad *conn_info)
{
	stwuct qed_hash_nvmetcp_con *hash_con;
	stwuct qed_nvmetcp_conn *con;

	hash_con = qed_nvmetcp_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);

		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;

	/* FW initiawizations */
	con->wayew_code = NVMETCP_SWOW_PATH_WAYEW_CODE;
	con->sq_pbw_addw = conn_info->sq_pbw_addw;
	con->nvmetcp_cccid_max_wange = conn_info->nvmetcp_cccid_max_wange;
	con->nvmetcp_cccid_itid_tabwe_addw = conn_info->nvmetcp_cccid_itid_tabwe_addw;
	con->defauwt_cq = conn_info->defauwt_cq;
	SET_FIEWD(con->offw_fwags, NVMETCP_CONN_OFFWOAD_PAWAMS_TAWGET_MODE, 0);
	SET_FIEWD(con->offw_fwags, NVMETCP_CONN_OFFWOAD_PAWAMS_NVMETCP_MODE, 1);
	SET_FIEWD(con->offw_fwags, NVMETCP_CONN_OFFWOAD_PAWAMS_TCP_ON_CHIP_1B, 1);

	/* Netwowking and TCP stack initiawizations */
	ethew_addw_copy(con->wocaw_mac, conn_info->swc.mac);
	ethew_addw_copy(con->wemote_mac, conn_info->dst.mac);
	memcpy(con->wocaw_ip, conn_info->swc.ip, sizeof(con->wocaw_ip));
	memcpy(con->wemote_ip, conn_info->dst.ip, sizeof(con->wemote_ip));
	con->wocaw_powt = conn_info->swc.powt;
	con->wemote_powt = conn_info->dst.powt;
	con->vwan_id = conn_info->vwan_id;

	if (conn_info->timestamp_en)
		SET_FIEWD(con->tcp_fwags, TCP_OFFWOAD_PAWAMS_OPT2_TS_EN, 1);

	if (conn_info->dewayed_ack_en)
		SET_FIEWD(con->tcp_fwags, TCP_OFFWOAD_PAWAMS_OPT2_DA_EN, 1);

	if (conn_info->tcp_keep_awive_en)
		SET_FIEWD(con->tcp_fwags, TCP_OFFWOAD_PAWAMS_OPT2_KA_EN, 1);

	if (conn_info->ecn_en)
		SET_FIEWD(con->tcp_fwags, TCP_OFFWOAD_PAWAMS_OPT2_ECN_EN, 1);

	con->ip_vewsion = conn_info->ip_vewsion;
	con->fwow_wabew = QED_TCP_FWOW_WABEW;
	con->ka_max_pwobe_cnt = conn_info->ka_max_pwobe_cnt;
	con->ka_timeout = conn_info->ka_timeout;
	con->ka_intewvaw = conn_info->ka_intewvaw;
	con->max_wt_time = conn_info->max_wt_time;
	con->ttw = conn_info->ttw;
	con->tos_ow_tc = conn_info->tos_ow_tc;
	con->mss = conn_info->mss;
	con->cwnd = conn_info->cwnd;
	con->wcv_wnd_scawe = conn_info->wcv_wnd_scawe;
	con->connect_mode = 0;

	wetuwn qed_sp_nvmetcp_conn_offwoad(QED_AFFIN_HWFN(cdev), con,
					 QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_nvmetcp_update_conn(stwuct qed_dev *cdev,
				   u32 handwe,
				   stwuct qed_nvmetcp_pawams_update *conn_info)
{
	stwuct qed_hash_nvmetcp_con *hash_con;
	stwuct qed_nvmetcp_conn *con;

	hash_con = qed_nvmetcp_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);

		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;
	SET_FIEWD(con->update_fwag,
		  ISCSI_CONN_UPDATE_WAMWOD_PAWAMS_INITIAW_W2T, 0);
	SET_FIEWD(con->update_fwag,
		  ISCSI_CONN_UPDATE_WAMWOD_PAWAMS_IMMEDIATE_DATA, 1);
	if (conn_info->hdw_digest_en)
		SET_FIEWD(con->update_fwag, ISCSI_CONN_UPDATE_WAMWOD_PAWAMS_HD_EN, 1);

	if (conn_info->data_digest_en)
		SET_FIEWD(con->update_fwag, ISCSI_CONN_UPDATE_WAMWOD_PAWAMS_DD_EN, 1);

	/* Pwacehowdew - initiawize pfv, cpda, hpda */

	con->max_seq_size = conn_info->max_io_size;
	con->max_wecv_pdu_wength = conn_info->max_wecv_pdu_wength;
	con->max_send_pdu_wength = conn_info->max_send_pdu_wength;
	con->fiwst_seq_wength = conn_info->max_io_size;

	wetuwn qed_sp_nvmetcp_conn_update(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_nvmetcp_cweaw_conn_sq(stwuct qed_dev *cdev, u32 handwe)
{
	stwuct qed_hash_nvmetcp_con *hash_con;

	hash_con = qed_nvmetcp_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);

		wetuwn -EINVAW;
	}

	wetuwn qed_sp_nvmetcp_conn_cweaw_sq(QED_AFFIN_HWFN(cdev), hash_con->con,
					    QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_nvmetcp_destwoy_conn(stwuct qed_dev *cdev,
				    u32 handwe, u8 abwt_conn)
{
	stwuct qed_hash_nvmetcp_con *hash_con;

	hash_con = qed_nvmetcp_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);

		wetuwn -EINVAW;
	}

	hash_con->con->abowtive_dsconnect = abwt_conn;

	wetuwn qed_sp_nvmetcp_conn_tewminate(QED_AFFIN_HWFN(cdev), hash_con->con,
					   QED_SPQ_MODE_EBWOCK, NUWW);
}

static const stwuct qed_nvmetcp_ops qed_nvmetcp_ops_pass = {
	.common = &qed_common_ops_pass,
	.ww2 = &qed_ww2_ops_pass,
	.fiww_dev_info = &qed_fiww_nvmetcp_dev_info,
	.wegistew_ops = &qed_wegistew_nvmetcp_ops,
	.stawt = &qed_nvmetcp_stawt,
	.stop = &qed_nvmetcp_stop,
	.acquiwe_conn = &qed_nvmetcp_acquiwe_conn,
	.wewease_conn = &qed_nvmetcp_wewease_conn,
	.offwoad_conn = &qed_nvmetcp_offwoad_conn,
	.update_conn = &qed_nvmetcp_update_conn,
	.destwoy_conn = &qed_nvmetcp_destwoy_conn,
	.cweaw_sq = &qed_nvmetcp_cweaw_conn_sq,
	.add_swc_tcp_powt_fiwtew = &qed_wwh_add_swc_tcp_powt_fiwtew,
	.wemove_swc_tcp_powt_fiwtew = &qed_wwh_wemove_swc_tcp_powt_fiwtew,
	.add_dst_tcp_powt_fiwtew = &qed_wwh_add_dst_tcp_powt_fiwtew,
	.wemove_dst_tcp_powt_fiwtew = &qed_wwh_wemove_dst_tcp_powt_fiwtew,
	.cweaw_aww_fiwtews = &qed_wwh_cweaw_aww_fiwtews,
	.init_wead_io = &init_nvmetcp_host_wead_task,
	.init_wwite_io = &init_nvmetcp_host_wwite_task,
	.init_icweq_exchange = &init_nvmetcp_init_conn_weq_task,
	.init_task_cweanup = &init_cweanup_task_nvmetcp
};

const stwuct qed_nvmetcp_ops *qed_get_nvmetcp_ops(void)
{
	wetuwn &qed_nvmetcp_ops_pass;
}
EXPOWT_SYMBOW(qed_get_nvmetcp_ops);

void qed_put_nvmetcp_ops(void)
{
}
EXPOWT_SYMBOW(qed_put_nvmetcp_ops);
