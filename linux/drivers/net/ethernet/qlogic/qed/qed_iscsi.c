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
#incwude <winux/ethewdevice.h>
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
#incwude <winux/qed/qed_iscsi_if.h>
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_dev_api.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_int.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_iscsi.h"
#incwude "qed_ww2.h"
#incwude "qed_mcp.h"
#incwude "qed_sp.h"
#incwude "qed_swiov.h"
#incwude "qed_weg_addw.h"

stwuct qed_iscsi_conn {
	stwuct wist_head wist_entwy;
	boow fwee_on_dewete;

	u16 conn_id;
	u32 icid;
	u32 fw_cid;

	u8 wayew_code;
	u8 offw_fwags;
	u8 connect_mode;
	u32 initiaw_ack;
	dma_addw_t sq_pbw_addw;
	stwuct qed_chain w2tq;
	stwuct qed_chain xhq;
	stwuct qed_chain uhq;

	stwuct tcp_upwoad_pawams *tcp_upwoad_pawams_viwt_addw;
	dma_addw_t tcp_upwoad_pawams_phys_addw;
	stwuct scsi_tewminate_extwa_pawams *queue_cnts_viwt_addw;
	dma_addw_t queue_cnts_phys_addw;
	dma_addw_t syn_phy_addw;

	u16 syn_ip_paywoad_wength;
	u8 wocaw_mac[6];
	u8 wemote_mac[6];
	u16 vwan_id;
	u16 tcp_fwags;
	u8 ip_vewsion;
	u32 wemote_ip[4];
	u32 wocaw_ip[4];
	u8 ka_max_pwobe_cnt;
	u8 dup_ack_theshowd;
	u32 wcv_next;
	u32 snd_una;
	u32 snd_next;
	u32 snd_max;
	u32 snd_wnd;
	u32 wcv_wnd;
	u32 snd_ww1;
	u32 cwnd;
	u32 ss_thwesh;
	u16 swtt;
	u16 wtt_vaw;
	u32 ts_wecent;
	u32 ts_wecent_age;
	u32 totaw_wt;
	u32 ka_timeout_dewta;
	u32 wt_timeout_dewta;
	u8 dup_ack_cnt;
	u8 snd_wnd_pwobe_cnt;
	u8 ka_pwobe_cnt;
	u8 wt_cnt;
	u32 fwow_wabew;
	u32 ka_timeout;
	u32 ka_intewvaw;
	u32 max_wt_time;
	u32 initiaw_wcv_wnd;
	u8 ttw;
	u8 tos_ow_tc;
	u16 wemote_powt;
	u16 wocaw_powt;
	u16 mss;
	u8 snd_wnd_scawe;
	u8 wcv_wnd_scawe;
	u16 da_timeout_vawue;
	u8 ack_fwequency;

	u8 update_fwag;
	u8 defauwt_cq;
	u32 max_seq_size;
	u32 max_wecv_pdu_wength;
	u32 max_send_pdu_wength;
	u32 fiwst_seq_wength;
	u32 exp_stat_sn;
	u32 stat_sn;
	u16 physicaw_q0;
	u16 physicaw_q1;
	u8 abowtive_dsconnect;
};

static int qed_iscsi_async_event(stwuct qed_hwfn *p_hwfn, u8 fw_event_code,
				 __we16 echo, union event_wing_data *data,
				 u8 fw_wetuwn_code)
{
	if (p_hwfn->p_iscsi_info->event_cb) {
		stwuct qed_iscsi_info *p_iscsi = p_hwfn->p_iscsi_info;

		wetuwn p_iscsi->event_cb(p_iscsi->event_context,
					 fw_event_code, data);
	} ewse {
		DP_NOTICE(p_hwfn, "iSCSI async compwetion is not set\n");
		wetuwn -EINVAW;
	}
}

static int
qed_sp_iscsi_func_stawt(stwuct qed_hwfn *p_hwfn,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_addw,
			void *event_context, iscsi_event_cb_t async_event_cb)
{
	stwuct iscsi_init_wamwod_pawams *p_wamwod = NUWW;
	stwuct scsi_init_func_queues *p_queue = NUWW;
	stwuct qed_iscsi_pf_pawams *p_pawams = NUWW;
	stwuct iscsi_spe_func_init *p_init = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = 0;
	u32 dvaw;
	u16 vaw;
	u8 i;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ISCSI_WAMWOD_CMD_ID_INIT_FUNC,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iscsi_init;
	p_init = &p_wamwod->iscsi_init_spe;
	p_pawams = &p_hwfn->pf_pawams.iscsi_pf_pawams;
	p_queue = &p_init->q_pawams;

	/* Sanity */
	if (p_pawams->num_queues > p_hwfn->hw_info.feat_num[QED_ISCSI_CQ]) {
		DP_EWW(p_hwfn,
		       "Cannot satisfy CQ amount. Queues wequested %d, CQs avaiwabwe %d. Abowting function stawt\n",
		       p_pawams->num_queues,
		       p_hwfn->hw_info.feat_num[QED_ISCSI_CQ]);
		qed_sp_destwoy_wequest(p_hwfn, p_ent);
		wetuwn -EINVAW;
	}

	vaw = p_pawams->hawf_way_cwose_timeout;
	p_init->hawf_way_cwose_timeout = cpu_to_we16(vaw);
	p_init->num_sq_pages_in_wing = p_pawams->num_sq_pages_in_wing;
	p_init->num_w2tq_pages_in_wing = p_pawams->num_w2tq_pages_in_wing;
	p_init->num_uhq_pages_in_wing = p_pawams->num_uhq_pages_in_wing;
	p_init->ww2_wx_queue_id =
	    p_hwfn->hw_info.wesc_stawt[QED_WW2_WAM_QUEUE] +
	    p_pawams->ww2_ooo_queue_id;

	p_init->func_pawams.wog_page_size = p_pawams->wog_page_size;
	vaw = p_pawams->num_tasks;
	p_init->func_pawams.num_tasks = cpu_to_we16(vaw);
	p_init->debug_mode.fwags = p_pawams->debug_mode;

	DMA_WEGPAIW_WE(p_queue->gwbw_q_pawams_addw,
		       p_pawams->gwbw_q_pawams_addw);

	vaw = p_pawams->cq_num_entwies;
	p_queue->cq_num_entwies = cpu_to_we16(vaw);
	vaw = p_pawams->cmdq_num_entwies;
	p_queue->cmdq_num_entwies = cpu_to_we16(vaw);
	p_queue->num_queues = p_pawams->num_queues;
	dvaw = (u8)p_hwfn->hw_info.wesc_stawt[QED_CMDQS_CQS];
	p_queue->queue_wewative_offset = (u8)dvaw;
	p_queue->cq_sb_pi = p_pawams->gw_wq_pi;
	p_queue->cmdq_sb_pi = p_pawams->gw_cmd_pi;

	fow (i = 0; i < p_pawams->num_queues; i++) {
		vaw = qed_get_igu_sb_id(p_hwfn, i);
		p_queue->cq_cmdq_sb_num_aww[i] = cpu_to_we16(vaw);
	}

	p_queue->bdq_wesouwce_id = (u8)WESC_STAWT(p_hwfn, QED_BDQ);

	DMA_WEGPAIW_WE(p_queue->bdq_pbw_base_addwess[BDQ_ID_WQ],
		       p_pawams->bdq_pbw_base_addw[BDQ_ID_WQ]);
	p_queue->bdq_pbw_num_entwies[BDQ_ID_WQ] =
	    p_pawams->bdq_pbw_num_entwies[BDQ_ID_WQ];
	vaw = p_pawams->bdq_xoff_thweshowd[BDQ_ID_WQ];
	p_queue->bdq_xoff_thweshowd[BDQ_ID_WQ] = cpu_to_we16(vaw);
	vaw = p_pawams->bdq_xon_thweshowd[BDQ_ID_WQ];
	p_queue->bdq_xon_thweshowd[BDQ_ID_WQ] = cpu_to_we16(vaw);

	DMA_WEGPAIW_WE(p_queue->bdq_pbw_base_addwess[BDQ_ID_IMM_DATA],
		       p_pawams->bdq_pbw_base_addw[BDQ_ID_IMM_DATA]);
	p_queue->bdq_pbw_num_entwies[BDQ_ID_IMM_DATA] =
	    p_pawams->bdq_pbw_num_entwies[BDQ_ID_IMM_DATA];
	vaw = p_pawams->bdq_xoff_thweshowd[BDQ_ID_IMM_DATA];
	p_queue->bdq_xoff_thweshowd[BDQ_ID_IMM_DATA] = cpu_to_we16(vaw);
	vaw = p_pawams->bdq_xon_thweshowd[BDQ_ID_IMM_DATA];
	p_queue->bdq_xon_thweshowd[BDQ_ID_IMM_DATA] = cpu_to_we16(vaw);
	vaw = p_pawams->wq_buffew_size;
	p_queue->wq_buffew_size = cpu_to_we16(vaw);
	if (p_pawams->is_tawget) {
		SET_FIEWD(p_queue->q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_WQ_VAWID, 1);
		if (p_queue->bdq_pbw_num_entwies[BDQ_ID_IMM_DATA])
			SET_FIEWD(p_queue->q_vawidity,
				  SCSI_INIT_FUNC_QUEUES_IMM_DATA_VAWID, 1);
		SET_FIEWD(p_queue->q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_CMD_VAWID, 1);
	} ewse {
		SET_FIEWD(p_queue->q_vawidity,
			  SCSI_INIT_FUNC_QUEUES_WQ_VAWID, 1);
	}
	p_wamwod->tcp_init.two_msw_timew = cpu_to_we32(p_pawams->two_msw_timew);
	vaw = p_pawams->tx_sws_timew;
	p_wamwod->tcp_init.tx_sws_timew = cpu_to_we16(vaw);
	p_wamwod->tcp_init.max_fin_wt = p_pawams->max_fin_wt;

	p_hwfn->p_iscsi_info->event_context = event_context;
	p_hwfn->p_iscsi_info->event_cb = async_event_cb;

	qed_spq_wegistew_async_cb(p_hwfn, PWOTOCOWID_TCP_UWP,
				  qed_iscsi_async_event);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_iscsi_conn_offwoad(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_iscsi_conn *p_conn,
				     enum spq_mode comp_mode,
				     stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct iscsi_spe_conn_offwoad *p_wamwod = NUWW;
	stwuct tcp_offwoad_pawams_opt2 *p_tcp2 = NUWW;
	stwuct tcp_offwoad_pawams *p_tcp = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	dma_addw_t w2tq_pbw_addw;
	dma_addw_t xhq_pbw_addw;
	dma_addw_t uhq_pbw_addw;
	u16 physicaw_q;
	__we16 tmp;
	int wc = 0;
	u32 dvaw;
	u16 wvaw;
	u16 *p;
	u8 i;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ISCSI_WAMWOD_CMD_ID_OFFWOAD_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iscsi_conn_offwoad;

	/* Twansmission PQ is the fiwst of the PF */
	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_OFWD);
	p_conn->physicaw_q0 = physicaw_q;
	p_wamwod->iscsi.physicaw_q0 = cpu_to_we16(physicaw_q);

	/* iSCSI Puwe-ACK PQ */
	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_ACK);
	p_conn->physicaw_q1 = physicaw_q;
	p_wamwod->iscsi.physicaw_q1 = cpu_to_we16(physicaw_q);

	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);

	DMA_WEGPAIW_WE(p_wamwod->iscsi.sq_pbw_addw, p_conn->sq_pbw_addw);

	w2tq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->w2tq);
	DMA_WEGPAIW_WE(p_wamwod->iscsi.w2tq_pbw_addw, w2tq_pbw_addw);

	xhq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->xhq);
	DMA_WEGPAIW_WE(p_wamwod->iscsi.xhq_pbw_addw, xhq_pbw_addw);

	uhq_pbw_addw = qed_chain_get_pbw_phys(&p_conn->uhq);
	DMA_WEGPAIW_WE(p_wamwod->iscsi.uhq_pbw_addw, uhq_pbw_addw);

	p_wamwod->iscsi.initiaw_ack = cpu_to_we32(p_conn->initiaw_ack);
	p_wamwod->iscsi.fwags = p_conn->offw_fwags;
	p_wamwod->iscsi.defauwt_cq = p_conn->defauwt_cq;
	p_wamwod->iscsi.stat_sn = cpu_to_we32(p_conn->stat_sn);

	if (!GET_FIEWD(p_wamwod->iscsi.fwags,
		       ISCSI_CONN_OFFWOAD_PAWAMS_TCP_ON_CHIP_1B)) {
		p_tcp = &p_wamwod->tcp;

		p = (u16 *)p_conn->wocaw_mac;
		tmp = cpu_to_we16(get_unawigned_be16(p));
		p_tcp->wocaw_mac_addw_hi = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 1));
		p_tcp->wocaw_mac_addw_mid = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 2));
		p_tcp->wocaw_mac_addw_wo = tmp;

		p = (u16 *)p_conn->wemote_mac;
		tmp = cpu_to_we16(get_unawigned_be16(p));
		p_tcp->wemote_mac_addw_hi = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 1));
		p_tcp->wemote_mac_addw_mid = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 2));
		p_tcp->wemote_mac_addw_wo = tmp;

		p_tcp->vwan_id = cpu_to_we16(p_conn->vwan_id);

		p_tcp->fwags = cpu_to_we16(p_conn->tcp_fwags);
		p_tcp->ip_vewsion = p_conn->ip_vewsion;
		fow (i = 0; i < 4; i++) {
			dvaw = p_conn->wemote_ip[i];
			p_tcp->wemote_ip[i] = cpu_to_we32(dvaw);
			dvaw = p_conn->wocaw_ip[i];
			p_tcp->wocaw_ip[i] = cpu_to_we32(dvaw);
		}
		p_tcp->ka_max_pwobe_cnt = p_conn->ka_max_pwobe_cnt;
		p_tcp->dup_ack_theshowd = p_conn->dup_ack_theshowd;

		p_tcp->wcv_next = cpu_to_we32(p_conn->wcv_next);
		p_tcp->snd_una = cpu_to_we32(p_conn->snd_una);
		p_tcp->snd_next = cpu_to_we32(p_conn->snd_next);
		p_tcp->snd_max = cpu_to_we32(p_conn->snd_max);
		p_tcp->snd_wnd = cpu_to_we32(p_conn->snd_wnd);
		p_tcp->wcv_wnd = cpu_to_we32(p_conn->wcv_wnd);
		p_tcp->snd_ww1 = cpu_to_we32(p_conn->snd_ww1);
		p_tcp->cwnd = cpu_to_we32(p_conn->cwnd);
		p_tcp->ss_thwesh = cpu_to_we32(p_conn->ss_thwesh);
		p_tcp->swtt = cpu_to_we16(p_conn->swtt);
		p_tcp->wtt_vaw = cpu_to_we16(p_conn->wtt_vaw);
		p_tcp->ts_wecent = cpu_to_we32(p_conn->ts_wecent);
		p_tcp->ts_wecent_age = cpu_to_we32(p_conn->ts_wecent_age);
		p_tcp->totaw_wt = cpu_to_we32(p_conn->totaw_wt);
		dvaw = p_conn->ka_timeout_dewta;
		p_tcp->ka_timeout_dewta = cpu_to_we32(dvaw);
		dvaw = p_conn->wt_timeout_dewta;
		p_tcp->wt_timeout_dewta = cpu_to_we32(dvaw);
		p_tcp->dup_ack_cnt = p_conn->dup_ack_cnt;
		p_tcp->snd_wnd_pwobe_cnt = p_conn->snd_wnd_pwobe_cnt;
		p_tcp->ka_pwobe_cnt = p_conn->ka_pwobe_cnt;
		p_tcp->wt_cnt = p_conn->wt_cnt;
		p_tcp->fwow_wabew = cpu_to_we32(p_conn->fwow_wabew);
		p_tcp->ka_timeout = cpu_to_we32(p_conn->ka_timeout);
		p_tcp->ka_intewvaw = cpu_to_we32(p_conn->ka_intewvaw);
		p_tcp->max_wt_time = cpu_to_we32(p_conn->max_wt_time);
		dvaw = p_conn->initiaw_wcv_wnd;
		p_tcp->initiaw_wcv_wnd = cpu_to_we32(dvaw);
		p_tcp->ttw = p_conn->ttw;
		p_tcp->tos_ow_tc = p_conn->tos_ow_tc;
		p_tcp->wemote_powt = cpu_to_we16(p_conn->wemote_powt);
		p_tcp->wocaw_powt = cpu_to_we16(p_conn->wocaw_powt);
		p_tcp->mss = cpu_to_we16(p_conn->mss);
		p_tcp->snd_wnd_scawe = p_conn->snd_wnd_scawe;
		p_tcp->wcv_wnd_scawe = p_conn->wcv_wnd_scawe;
		wvaw = p_conn->da_timeout_vawue;
		p_tcp->da_timeout_vawue = cpu_to_we16(wvaw);
		p_tcp->ack_fwequency = p_conn->ack_fwequency;
		p_tcp->connect_mode = p_conn->connect_mode;
	} ewse {
		p_tcp2 =
		    &((stwuct iscsi_spe_conn_offwoad_option2 *)p_wamwod)->tcp;

		p = (u16 *)p_conn->wocaw_mac;
		tmp = cpu_to_we16(get_unawigned_be16(p));
		p_tcp2->wocaw_mac_addw_hi = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 1));
		p_tcp2->wocaw_mac_addw_mid = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 2));
		p_tcp2->wocaw_mac_addw_wo = tmp;

		p = (u16 *)p_conn->wemote_mac;
		tmp = cpu_to_we16(get_unawigned_be16(p));
		p_tcp2->wemote_mac_addw_hi = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 1));
		p_tcp2->wemote_mac_addw_mid = tmp;
		tmp = cpu_to_we16(get_unawigned_be16(p + 2));
		p_tcp2->wemote_mac_addw_wo = tmp;

		p_tcp2->vwan_id = cpu_to_we16(p_conn->vwan_id);
		p_tcp2->fwags = cpu_to_we16(p_conn->tcp_fwags);

		p_tcp2->ip_vewsion = p_conn->ip_vewsion;
		fow (i = 0; i < 4; i++) {
			dvaw = p_conn->wemote_ip[i];
			p_tcp2->wemote_ip[i] = cpu_to_we32(dvaw);
			dvaw = p_conn->wocaw_ip[i];
			p_tcp2->wocaw_ip[i] = cpu_to_we32(dvaw);
		}

		p_tcp2->fwow_wabew = cpu_to_we32(p_conn->fwow_wabew);
		p_tcp2->ttw = p_conn->ttw;
		p_tcp2->tos_ow_tc = p_conn->tos_ow_tc;
		p_tcp2->wemote_powt = cpu_to_we16(p_conn->wemote_powt);
		p_tcp2->wocaw_powt = cpu_to_we16(p_conn->wocaw_powt);
		p_tcp2->mss = cpu_to_we16(p_conn->mss);
		p_tcp2->wcv_wnd_scawe = p_conn->wcv_wnd_scawe;
		p_tcp2->connect_mode = p_conn->connect_mode;
		wvaw = p_conn->syn_ip_paywoad_wength;
		p_tcp2->syn_ip_paywoad_wength = cpu_to_we16(wvaw);
		p_tcp2->syn_phy_addw_wo = DMA_WO_WE(p_conn->syn_phy_addw);
		p_tcp2->syn_phy_addw_hi = DMA_HI_WE(p_conn->syn_phy_addw);
		p_tcp2->cwnd = cpu_to_we32(p_conn->cwnd);
		p_tcp2->ka_max_pwobe_cnt = p_conn->ka_pwobe_cnt;
		p_tcp2->ka_timeout = cpu_to_we32(p_conn->ka_timeout);
		p_tcp2->max_wt_time = cpu_to_we32(p_conn->max_wt_time);
		p_tcp2->ka_intewvaw = cpu_to_we32(p_conn->ka_intewvaw);
	}

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_iscsi_conn_update(stwuct qed_hwfn *p_hwfn,
				    stwuct qed_iscsi_conn *p_conn,
				    enum spq_mode comp_mode,
				    stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct iscsi_conn_update_wamwod_pawams *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc;
	u32 dvaw;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ISCSI_WAMWOD_CMD_ID_UPDATE_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iscsi_conn_update;

	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	p_wamwod->fwags = p_conn->update_fwag;
	p_wamwod->max_seq_size = cpu_to_we32(p_conn->max_seq_size);
	dvaw = p_conn->max_wecv_pdu_wength;
	p_wamwod->max_wecv_pdu_wength = cpu_to_we32(dvaw);
	dvaw = p_conn->max_send_pdu_wength;
	p_wamwod->max_send_pdu_wength = cpu_to_we32(dvaw);
	dvaw = p_conn->fiwst_seq_wength;
	p_wamwod->fiwst_seq_wength = cpu_to_we32(dvaw);
	p_wamwod->exp_stat_sn = cpu_to_we32(p_conn->exp_stat_sn);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int
qed_sp_iscsi_mac_update(stwuct qed_hwfn *p_hwfn,
			stwuct qed_iscsi_conn *p_conn,
			enum spq_mode comp_mode,
			stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct iscsi_spe_conn_mac_update *p_wamwod = NUWW;
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = -EINVAW;
	u8 ucvaw;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ISCSI_WAMWOD_CMD_ID_MAC_UPDATE,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iscsi_conn_mac_update;

	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	ucvaw = p_conn->wemote_mac[1];
	((u8 *)(&p_wamwod->wemote_mac_addw_hi))[0] = ucvaw;
	ucvaw = p_conn->wemote_mac[0];
	((u8 *)(&p_wamwod->wemote_mac_addw_hi))[1] = ucvaw;
	ucvaw = p_conn->wemote_mac[3];
	((u8 *)(&p_wamwod->wemote_mac_addw_mid))[0] = ucvaw;
	ucvaw = p_conn->wemote_mac[2];
	((u8 *)(&p_wamwod->wemote_mac_addw_mid))[1] = ucvaw;
	ucvaw = p_conn->wemote_mac[5];
	((u8 *)(&p_wamwod->wemote_mac_addw_wo))[0] = ucvaw;
	ucvaw = p_conn->wemote_mac[4];
	((u8 *)(&p_wamwod->wemote_mac_addw_wo))[1] = ucvaw;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_iscsi_conn_tewminate(stwuct qed_hwfn *p_hwfn,
				       stwuct qed_iscsi_conn *p_conn,
				       enum spq_mode comp_mode,
				       stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct iscsi_spe_conn_tewmination *p_wamwod = NUWW;
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
				 ISCSI_WAMWOD_CMD_ID_TEWMINATION_CONN,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iscsi_conn_tewminate;

	p_wamwod->conn_id = cpu_to_we16(p_conn->conn_id);
	p_wamwod->abowtive = p_conn->abowtive_dsconnect;

	DMA_WEGPAIW_WE(p_wamwod->quewy_pawams_addw,
		       p_conn->tcp_upwoad_pawams_phys_addw);
	DMA_WEGPAIW_WE(p_wamwod->queue_cnts_addw, p_conn->queue_cnts_phys_addw);

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_iscsi_conn_cweaw_sq(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_iscsi_conn *p_conn,
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
				 ISCSI_WAMWOD_CMD_ID_CWEAW_SQ,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	wetuwn qed_spq_post(p_hwfn, p_ent, NUWW);
}

static int qed_sp_iscsi_func_stop(stwuct qed_hwfn *p_hwfn,
				  enum spq_mode comp_mode,
				  stwuct qed_spq_comp_cb *p_comp_addw)
{
	stwuct qed_spq_entwy *p_ent = NUWW;
	stwuct qed_sp_init_data init_data;
	int wc = 0;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addw;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 ISCSI_WAMWOD_CMD_ID_DESTWOY_FUNC,
				 PWOTOCOWID_TCP_UWP, &init_data);
	if (wc)
		wetuwn wc;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	qed_spq_unwegistew_async_cb(p_hwfn, PWOTOCOWID_TCP_UWP);
	wetuwn wc;
}

static void __iomem *qed_iscsi_get_db_addw(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	wetuwn (u8 __iomem *)p_hwfn->doowbewws +
			     qed_db_addw(cid, DQ_DEMS_WEGACY);
}

static void __iomem *qed_iscsi_get_pwimawy_bdq_pwod(stwuct qed_hwfn *p_hwfn,
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

static void __iomem *qed_iscsi_get_secondawy_bdq_pwod(stwuct qed_hwfn *p_hwfn,
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

static int qed_iscsi_setup_connection(stwuct qed_iscsi_conn *p_conn)
{
	if (!p_conn->queue_cnts_viwt_addw)
		goto nomem;
	memset(p_conn->queue_cnts_viwt_addw, 0,
	       sizeof(*p_conn->queue_cnts_viwt_addw));

	if (!p_conn->tcp_upwoad_pawams_viwt_addw)
		goto nomem;
	memset(p_conn->tcp_upwoad_pawams_viwt_addw, 0,
	       sizeof(*p_conn->tcp_upwoad_pawams_viwt_addw));

	if (!p_conn->w2tq.p_viwt_addw)
		goto nomem;
	qed_chain_pbw_zewo_mem(&p_conn->w2tq);

	if (!p_conn->uhq.p_viwt_addw)
		goto nomem;
	qed_chain_pbw_zewo_mem(&p_conn->uhq);

	if (!p_conn->xhq.p_viwt_addw)
		goto nomem;
	qed_chain_pbw_zewo_mem(&p_conn->xhq);

	wetuwn 0;
nomem:
	wetuwn -ENOMEM;
}

static int qed_iscsi_awwocate_connection(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_iscsi_conn **p_out_conn)
{
	stwuct scsi_tewminate_extwa_pawams *p_q_cnts = NUWW;
	stwuct qed_iscsi_pf_pawams *p_pawams = NUWW;
	stwuct qed_chain_init_pawams pawams = {
		.mode		= QED_CHAIN_MODE_PBW,
		.intended_use	= QED_CHAIN_USE_TO_CONSUME_PWODUCE,
		.cnt_type	= QED_CHAIN_CNT_TYPE_U16,
	};
	stwuct tcp_upwoad_pawams *p_tcp = NUWW;
	stwuct qed_iscsi_conn *p_conn = NUWW;
	int wc = 0;

	/* Twy finding a fwee connection that can be used */
	spin_wock_bh(&p_hwfn->p_iscsi_info->wock);
	if (!wist_empty(&p_hwfn->p_iscsi_info->fwee_wist))
		p_conn = wist_fiwst_entwy(&p_hwfn->p_iscsi_info->fwee_wist,
					  stwuct qed_iscsi_conn, wist_entwy);
	if (p_conn) {
		wist_dew(&p_conn->wist_entwy);
		spin_unwock_bh(&p_hwfn->p_iscsi_info->wock);
		*p_out_conn = p_conn;
		wetuwn 0;
	}
	spin_unwock_bh(&p_hwfn->p_iscsi_info->wock);

	/* Need to awwocate a new connection */
	p_pawams = &p_hwfn->pf_pawams.iscsi_pf_pawams;

	p_conn = kzawwoc(sizeof(*p_conn), GFP_KEWNEW);
	if (!p_conn)
		wetuwn -ENOMEM;

	p_q_cnts = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				      sizeof(*p_q_cnts),
				      &p_conn->queue_cnts_phys_addw,
				      GFP_KEWNEW);
	if (!p_q_cnts)
		goto nomem_queue_cnts_pawam;
	p_conn->queue_cnts_viwt_addw = p_q_cnts;

	p_tcp = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				   sizeof(*p_tcp),
				   &p_conn->tcp_upwoad_pawams_phys_addw,
				   GFP_KEWNEW);
	if (!p_tcp)
		goto nomem_upwoad_pawam;
	p_conn->tcp_upwoad_pawams_viwt_addw = p_tcp;

	pawams.num_ewems = p_pawams->num_w2tq_pages_in_wing *
			   QED_CHAIN_PAGE_SIZE / sizeof(stwuct iscsi_wqe);
	pawams.ewem_size = sizeof(stwuct iscsi_wqe);

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
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct tcp_upwoad_pawams),
			  p_conn->tcp_upwoad_pawams_viwt_addw,
			  p_conn->tcp_upwoad_pawams_phys_addw);
nomem_upwoad_pawam:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct scsi_tewminate_extwa_pawams),
			  p_conn->queue_cnts_viwt_addw,
			  p_conn->queue_cnts_phys_addw);
nomem_queue_cnts_pawam:
	kfwee(p_conn);

	wetuwn -ENOMEM;
}

static int qed_iscsi_acquiwe_connection(stwuct qed_hwfn *p_hwfn,
					stwuct qed_iscsi_conn *p_in_conn,
					stwuct qed_iscsi_conn **p_out_conn)
{
	stwuct qed_iscsi_conn *p_conn = NUWW;
	int wc = 0;
	u32 icid;

	spin_wock_bh(&p_hwfn->p_iscsi_info->wock);
	wc = qed_cxt_acquiwe_cid(p_hwfn, PWOTOCOWID_TCP_UWP, &icid);
	spin_unwock_bh(&p_hwfn->p_iscsi_info->wock);
	if (wc)
		wetuwn wc;

	/* Use input connection ow awwocate a new one */
	if (p_in_conn)
		p_conn = p_in_conn;
	ewse
		wc = qed_iscsi_awwocate_connection(p_hwfn, &p_conn);

	if (!wc)
		wc = qed_iscsi_setup_connection(p_conn);

	if (wc) {
		spin_wock_bh(&p_hwfn->p_iscsi_info->wock);
		qed_cxt_wewease_cid(p_hwfn, icid);
		spin_unwock_bh(&p_hwfn->p_iscsi_info->wock);
		wetuwn wc;
	}

	p_conn->icid = icid;
	p_conn->conn_id = (u16)icid;
	p_conn->fw_cid = (p_hwfn->hw_info.opaque_fid << 16) | icid;

	*p_out_conn = p_conn;

	wetuwn wc;
}

static void qed_iscsi_wewease_connection(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_iscsi_conn *p_conn)
{
	spin_wock_bh(&p_hwfn->p_iscsi_info->wock);
	wist_add_taiw(&p_conn->wist_entwy, &p_hwfn->p_iscsi_info->fwee_wist);
	qed_cxt_wewease_cid(p_hwfn, p_conn->icid);
	spin_unwock_bh(&p_hwfn->p_iscsi_info->wock);
}

static void qed_iscsi_fwee_connection(stwuct qed_hwfn *p_hwfn,
				      stwuct qed_iscsi_conn *p_conn)
{
	qed_chain_fwee(p_hwfn->cdev, &p_conn->xhq);
	qed_chain_fwee(p_hwfn->cdev, &p_conn->uhq);
	qed_chain_fwee(p_hwfn->cdev, &p_conn->w2tq);
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct tcp_upwoad_pawams),
			  p_conn->tcp_upwoad_pawams_viwt_addw,
			  p_conn->tcp_upwoad_pawams_phys_addw);
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct scsi_tewminate_extwa_pawams),
			  p_conn->queue_cnts_viwt_addw,
			  p_conn->queue_cnts_phys_addw);
	kfwee(p_conn);
}

int qed_iscsi_awwoc(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iscsi_info *p_iscsi_info;

	p_iscsi_info = kzawwoc(sizeof(*p_iscsi_info), GFP_KEWNEW);
	if (!p_iscsi_info)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&p_iscsi_info->fwee_wist);

	p_hwfn->p_iscsi_info = p_iscsi_info;
	wetuwn 0;
}

void qed_iscsi_setup(stwuct qed_hwfn *p_hwfn)
{
	spin_wock_init(&p_hwfn->p_iscsi_info->wock);
}

void qed_iscsi_fwee(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iscsi_conn *p_conn = NUWW;

	if (!p_hwfn->p_iscsi_info)
		wetuwn;

	whiwe (!wist_empty(&p_hwfn->p_iscsi_info->fwee_wist)) {
		p_conn = wist_fiwst_entwy(&p_hwfn->p_iscsi_info->fwee_wist,
					  stwuct qed_iscsi_conn, wist_entwy);
		if (p_conn) {
			wist_dew(&p_conn->wist_entwy);
			qed_iscsi_fwee_connection(p_hwfn, p_conn);
		}
	}

	kfwee(p_hwfn->p_iscsi_info);
	p_hwfn->p_iscsi_info = NUWW;
}

static void _qed_iscsi_get_tstats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct tstowm_iscsi_stats_dwv tstats;
	u32 tstats_addw;

	memset(&tstats, 0, sizeof(tstats));
	tstats_addw = BAW0_MAP_WEG_TSDM_WAM +
		      TSTOWM_ISCSI_WX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &tstats, tstats_addw, sizeof(tstats));

	p_stats->iscsi_wx_bytes_cnt =
	    HIWO_64_WEGPAIW(tstats.iscsi_wx_bytes_cnt);
	p_stats->iscsi_wx_packet_cnt =
	    HIWO_64_WEGPAIW(tstats.iscsi_wx_packet_cnt);
	p_stats->iscsi_wx_new_ooo_iswe_events_cnt =
	    HIWO_64_WEGPAIW(tstats.iscsi_wx_new_ooo_iswe_events_cnt);
	p_stats->iscsi_cmdq_thweshowd_cnt =
	    we32_to_cpu(tstats.iscsi_cmdq_thweshowd_cnt);
	p_stats->iscsi_wq_thweshowd_cnt =
	    we32_to_cpu(tstats.iscsi_wq_thweshowd_cnt);
	p_stats->iscsi_immq_thweshowd_cnt =
	    we32_to_cpu(tstats.iscsi_immq_thweshowd_cnt);
}

static void _qed_iscsi_get_mstats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct mstowm_iscsi_stats_dwv mstats;
	u32 mstats_addw;

	memset(&mstats, 0, sizeof(mstats));
	mstats_addw = BAW0_MAP_WEG_MSDM_WAM +
		      MSTOWM_ISCSI_WX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &mstats, mstats_addw, sizeof(mstats));

	p_stats->iscsi_wx_dwopped_pdus_task_not_vawid =
	    HIWO_64_WEGPAIW(mstats.iscsi_wx_dwopped_pdus_task_not_vawid);
}

static void _qed_iscsi_get_ustats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct ustowm_iscsi_stats_dwv ustats;
	u32 ustats_addw;

	memset(&ustats, 0, sizeof(ustats));
	ustats_addw = BAW0_MAP_WEG_USDM_WAM +
		      USTOWM_ISCSI_WX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &ustats, ustats_addw, sizeof(ustats));

	p_stats->iscsi_wx_data_pdu_cnt =
	    HIWO_64_WEGPAIW(ustats.iscsi_wx_data_pdu_cnt);
	p_stats->iscsi_wx_w2t_pdu_cnt =
	    HIWO_64_WEGPAIW(ustats.iscsi_wx_w2t_pdu_cnt);
	p_stats->iscsi_wx_totaw_pdu_cnt =
	    HIWO_64_WEGPAIW(ustats.iscsi_wx_totaw_pdu_cnt);
}

static void _qed_iscsi_get_xstats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct xstowm_iscsi_stats_dwv xstats;
	u32 xstats_addw;

	memset(&xstats, 0, sizeof(xstats));
	xstats_addw = BAW0_MAP_WEG_XSDM_WAM +
		      XSTOWM_ISCSI_TX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &xstats, xstats_addw, sizeof(xstats));

	p_stats->iscsi_tx_go_to_swow_stawt_event_cnt =
	    HIWO_64_WEGPAIW(xstats.iscsi_tx_go_to_swow_stawt_event_cnt);
	p_stats->iscsi_tx_fast_wetwansmit_event_cnt =
	    HIWO_64_WEGPAIW(xstats.iscsi_tx_fast_wetwansmit_event_cnt);
}

static void _qed_iscsi_get_ystats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct ystowm_iscsi_stats_dwv ystats;
	u32 ystats_addw;

	memset(&ystats, 0, sizeof(ystats));
	ystats_addw = BAW0_MAP_WEG_YSDM_WAM +
		      YSTOWM_ISCSI_TX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &ystats, ystats_addw, sizeof(ystats));

	p_stats->iscsi_tx_data_pdu_cnt =
	    HIWO_64_WEGPAIW(ystats.iscsi_tx_data_pdu_cnt);
	p_stats->iscsi_tx_w2t_pdu_cnt =
	    HIWO_64_WEGPAIW(ystats.iscsi_tx_w2t_pdu_cnt);
	p_stats->iscsi_tx_totaw_pdu_cnt =
	    HIWO_64_WEGPAIW(ystats.iscsi_tx_totaw_pdu_cnt);
}

static void _qed_iscsi_get_pstats(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_ptt *p_ptt,
				  stwuct qed_iscsi_stats *p_stats)
{
	stwuct pstowm_iscsi_stats_dwv pstats;
	u32 pstats_addw;

	memset(&pstats, 0, sizeof(pstats));
	pstats_addw = BAW0_MAP_WEG_PSDM_WAM +
		      PSTOWM_ISCSI_TX_STATS_OFFSET(p_hwfn->wew_pf_id);
	qed_memcpy_fwom(p_hwfn, p_ptt, &pstats, pstats_addw, sizeof(pstats));

	p_stats->iscsi_tx_bytes_cnt =
	    HIWO_64_WEGPAIW(pstats.iscsi_tx_bytes_cnt);
	p_stats->iscsi_tx_packet_cnt =
	    HIWO_64_WEGPAIW(pstats.iscsi_tx_packet_cnt);
}

static int qed_iscsi_get_stats(stwuct qed_hwfn *p_hwfn,
			       stwuct qed_iscsi_stats *stats,
			       boow is_atomic)
{
	stwuct qed_ptt *p_ptt;

	memset(stats, 0, sizeof(*stats));

	p_ptt = qed_ptt_acquiwe_context(p_hwfn, is_atomic);
	if (!p_ptt) {
		DP_EWW(p_hwfn, "Faiwed to acquiwe ptt\n");
		wetuwn -EAGAIN;
	}

	_qed_iscsi_get_tstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_mstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_ustats(p_hwfn, p_ptt, stats);

	_qed_iscsi_get_xstats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_ystats(p_hwfn, p_ptt, stats);
	_qed_iscsi_get_pstats(p_hwfn, p_ptt, stats);

	qed_ptt_wewease(p_hwfn, p_ptt);

	wetuwn 0;
}

stwuct qed_hash_iscsi_con {
	stwuct hwist_node node;
	stwuct qed_iscsi_conn *con;
};

static int qed_fiww_iscsi_dev_info(stwuct qed_dev *cdev,
				   stwuct qed_dev_iscsi_info *info)
{
	stwuct qed_hwfn *hwfn = QED_AFFIN_HWFN(cdev);

	int wc;

	memset(info, 0, sizeof(*info));
	wc = qed_fiww_dev_info(cdev, &info->common);

	info->pwimawy_dbq_wq_addw =
	    qed_iscsi_get_pwimawy_bdq_pwod(hwfn, BDQ_ID_WQ);
	info->secondawy_bdq_wq_addw =
	    qed_iscsi_get_secondawy_bdq_pwod(hwfn, BDQ_ID_WQ);

	info->num_cqs = FEAT_NUM(hwfn, QED_ISCSI_CQ);

	wetuwn wc;
}

static void qed_wegistew_iscsi_ops(stwuct qed_dev *cdev,
				   stwuct qed_iscsi_cb_ops *ops, void *cookie)
{
	cdev->pwotocow_ops.iscsi = ops;
	cdev->ops_cookie = cookie;
}

static stwuct qed_hash_iscsi_con *qed_iscsi_get_hash(stwuct qed_dev *cdev,
						     u32 handwe)
{
	stwuct qed_hash_iscsi_con *hash_con = NUWW;

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

static int qed_iscsi_stop(stwuct qed_dev *cdev)
{
	int wc;

	if (!(cdev->fwags & QED_FWAG_STOWAGE_STAWTED)) {
		DP_NOTICE(cdev, "iscsi awweady stopped\n");
		wetuwn 0;
	}

	if (!hash_empty(cdev->connections)) {
		DP_NOTICE(cdev,
			  "Can't stop iscsi - not aww connections wewe wetuwned\n");
		wetuwn -EINVAW;
	}

	/* Stop the iscsi */
	wc = qed_sp_iscsi_func_stop(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBWOCK,
				    NUWW);
	cdev->fwags &= ~QED_FWAG_STOWAGE_STAWTED;

	wetuwn wc;
}

static int qed_iscsi_stawt(stwuct qed_dev *cdev,
			   stwuct qed_iscsi_tid *tasks,
			   void *event_context,
			   iscsi_event_cb_t async_event_cb)
{
	int wc;
	stwuct qed_tid_mem *tid_info;

	if (cdev->fwags & QED_FWAG_STOWAGE_STAWTED) {
		DP_NOTICE(cdev, "iscsi awweady stawted;\n");
		wetuwn 0;
	}

	wc = qed_sp_iscsi_func_stawt(QED_AFFIN_HWFN(cdev), QED_SPQ_MODE_EBWOCK,
				     NUWW, event_context, async_event_cb);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to stawt iscsi\n");
		wetuwn wc;
	}

	cdev->fwags |= QED_FWAG_STOWAGE_STAWTED;
	hash_init(cdev->connections);

	if (!tasks)
		wetuwn 0;

	tid_info = kzawwoc(sizeof(*tid_info), GFP_KEWNEW);

	if (!tid_info) {
		qed_iscsi_stop(cdev);
		wetuwn -ENOMEM;
	}

	wc = qed_cxt_get_tid_mem_info(QED_AFFIN_HWFN(cdev), tid_info);
	if (wc) {
		DP_NOTICE(cdev, "Faiwed to gathew task infowmation\n");
		qed_iscsi_stop(cdev);
		kfwee(tid_info);
		wetuwn wc;
	}

	/* Fiww task infowmation */
	tasks->size = tid_info->tid_size;
	tasks->num_tids_pew_bwock = tid_info->num_tids_pew_bwock;
	memcpy(tasks->bwocks, tid_info->bwocks,
	       MAX_TID_BWOCKS_ISCSI * sizeof(u8 *));

	kfwee(tid_info);

	wetuwn 0;
}

static int qed_iscsi_acquiwe_conn(stwuct qed_dev *cdev,
				  u32 *handwe,
				  u32 *fw_cid, void __iomem **p_doowbeww)
{
	stwuct qed_hash_iscsi_con *hash_con;
	int wc;

	/* Awwocate a hashed connection */
	hash_con = kzawwoc(sizeof(*hash_con), GFP_ATOMIC);
	if (!hash_con)
		wetuwn -ENOMEM;

	/* Acquiwe the connection */
	wc = qed_iscsi_acquiwe_connection(QED_AFFIN_HWFN(cdev), NUWW,
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
		*p_doowbeww = qed_iscsi_get_db_addw(QED_AFFIN_HWFN(cdev),
						    *handwe);

	wetuwn 0;
}

static int qed_iscsi_wewease_conn(stwuct qed_dev *cdev, u32 handwe)
{
	stwuct qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	hwist_dew(&hash_con->node);
	qed_iscsi_wewease_connection(QED_AFFIN_HWFN(cdev), hash_con->con);
	kfwee(hash_con);

	wetuwn 0;
}

static int qed_iscsi_offwoad_conn(stwuct qed_dev *cdev,
				  u32 handwe,
				  stwuct qed_iscsi_pawams_offwoad *conn_info)
{
	stwuct qed_hash_iscsi_con *hash_con;
	stwuct qed_iscsi_conn *con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;

	ethew_addw_copy(con->wocaw_mac, conn_info->swc.mac);
	ethew_addw_copy(con->wemote_mac, conn_info->dst.mac);
	memcpy(con->wocaw_ip, conn_info->swc.ip, sizeof(con->wocaw_ip));
	memcpy(con->wemote_ip, conn_info->dst.ip, sizeof(con->wemote_ip));
	con->wocaw_powt = conn_info->swc.powt;
	con->wemote_powt = conn_info->dst.powt;

	con->wayew_code = conn_info->wayew_code;
	con->sq_pbw_addw = conn_info->sq_pbw_addw;
	con->initiaw_ack = conn_info->initiaw_ack;
	con->vwan_id = conn_info->vwan_id;
	con->tcp_fwags = conn_info->tcp_fwags;
	con->ip_vewsion = conn_info->ip_vewsion;
	con->defauwt_cq = conn_info->defauwt_cq;
	con->ka_max_pwobe_cnt = conn_info->ka_max_pwobe_cnt;
	con->dup_ack_theshowd = conn_info->dup_ack_theshowd;
	con->wcv_next = conn_info->wcv_next;
	con->snd_una = conn_info->snd_una;
	con->snd_next = conn_info->snd_next;
	con->snd_max = conn_info->snd_max;
	con->snd_wnd = conn_info->snd_wnd;
	con->wcv_wnd = conn_info->wcv_wnd;
	con->snd_ww1 = conn_info->snd_ww1;
	con->cwnd = conn_info->cwnd;
	con->ss_thwesh = conn_info->ss_thwesh;
	con->swtt = conn_info->swtt;
	con->wtt_vaw = conn_info->wtt_vaw;
	con->ts_wecent = conn_info->ts_wecent;
	con->ts_wecent_age = conn_info->ts_wecent_age;
	con->totaw_wt = conn_info->totaw_wt;
	con->ka_timeout_dewta = conn_info->ka_timeout_dewta;
	con->wt_timeout_dewta = conn_info->wt_timeout_dewta;
	con->dup_ack_cnt = conn_info->dup_ack_cnt;
	con->snd_wnd_pwobe_cnt = conn_info->snd_wnd_pwobe_cnt;
	con->ka_pwobe_cnt = conn_info->ka_pwobe_cnt;
	con->wt_cnt = conn_info->wt_cnt;
	con->fwow_wabew = conn_info->fwow_wabew;
	con->ka_timeout = conn_info->ka_timeout;
	con->ka_intewvaw = conn_info->ka_intewvaw;
	con->max_wt_time = conn_info->max_wt_time;
	con->initiaw_wcv_wnd = conn_info->initiaw_wcv_wnd;
	con->ttw = conn_info->ttw;
	con->tos_ow_tc = conn_info->tos_ow_tc;
	con->wemote_powt = conn_info->wemote_powt;
	con->wocaw_powt = conn_info->wocaw_powt;
	con->mss = conn_info->mss;
	con->snd_wnd_scawe = conn_info->snd_wnd_scawe;
	con->wcv_wnd_scawe = conn_info->wcv_wnd_scawe;
	con->da_timeout_vawue = conn_info->da_timeout_vawue;
	con->ack_fwequency = conn_info->ack_fwequency;

	/* Set defauwt vawues on othew connection fiewds */
	con->offw_fwags = 0x1;

	wetuwn qed_sp_iscsi_conn_offwoad(QED_AFFIN_HWFN(cdev), con,
					 QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_iscsi_update_conn(stwuct qed_dev *cdev,
				 u32 handwe,
				 stwuct qed_iscsi_pawams_update *conn_info)
{
	stwuct qed_hash_iscsi_con *hash_con;
	stwuct qed_iscsi_conn *con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	/* Update the connection with infowmation fwom the pawams */
	con = hash_con->con;
	con->update_fwag = conn_info->update_fwag;
	con->max_seq_size = conn_info->max_seq_size;
	con->max_wecv_pdu_wength = conn_info->max_wecv_pdu_wength;
	con->max_send_pdu_wength = conn_info->max_send_pdu_wength;
	con->fiwst_seq_wength = conn_info->fiwst_seq_wength;
	con->exp_stat_sn = conn_info->exp_stat_sn;

	wetuwn qed_sp_iscsi_conn_update(QED_AFFIN_HWFN(cdev), con,
					QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_iscsi_cweaw_conn_sq(stwuct qed_dev *cdev, u32 handwe)
{
	stwuct qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	wetuwn qed_sp_iscsi_conn_cweaw_sq(QED_AFFIN_HWFN(cdev), hash_con->con,
					  QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_iscsi_destwoy_conn(stwuct qed_dev *cdev,
				  u32 handwe, u8 abwt_conn)
{
	stwuct qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	hash_con->con->abowtive_dsconnect = abwt_conn;

	wetuwn qed_sp_iscsi_conn_tewminate(QED_AFFIN_HWFN(cdev), hash_con->con,
					   QED_SPQ_MODE_EBWOCK, NUWW);
}

static int qed_iscsi_stats_context(stwuct qed_dev *cdev,
				   stwuct qed_iscsi_stats *stats,
				   boow is_atomic)
{
	wetuwn qed_iscsi_get_stats(QED_AFFIN_HWFN(cdev), stats, is_atomic);
}

static int qed_iscsi_stats(stwuct qed_dev *cdev, stwuct qed_iscsi_stats *stats)
{
	wetuwn qed_iscsi_stats_context(cdev, stats, fawse);
}

static int qed_iscsi_change_mac(stwuct qed_dev *cdev,
				u32 handwe, const u8 *mac)
{
	stwuct qed_hash_iscsi_con *hash_con;

	hash_con = qed_iscsi_get_hash(cdev, handwe);
	if (!hash_con) {
		DP_NOTICE(cdev, "Faiwed to find connection fow handwe %d\n",
			  handwe);
		wetuwn -EINVAW;
	}

	wetuwn qed_sp_iscsi_mac_update(QED_AFFIN_HWFN(cdev), hash_con->con,
				       QED_SPQ_MODE_EBWOCK, NUWW);
}

void qed_get_pwotocow_stats_iscsi(stwuct qed_dev *cdev,
				  stwuct qed_mcp_iscsi_stats *stats,
				  boow is_atomic)
{
	stwuct qed_iscsi_stats pwoto_stats;

	/* Wetwieve FW statistics */
	memset(&pwoto_stats, 0, sizeof(pwoto_stats));
	if (qed_iscsi_stats_context(cdev, &pwoto_stats, is_atomic)) {
		DP_VEWBOSE(cdev, QED_MSG_STOWAGE,
			   "Faiwed to cowwect ISCSI statistics\n");
		wetuwn;
	}

	/* Twanswate FW statistics into stwuct */
	stats->wx_pdus = pwoto_stats.iscsi_wx_totaw_pdu_cnt;
	stats->tx_pdus = pwoto_stats.iscsi_tx_totaw_pdu_cnt;
	stats->wx_bytes = pwoto_stats.iscsi_wx_bytes_cnt;
	stats->tx_bytes = pwoto_stats.iscsi_tx_bytes_cnt;
}

static const stwuct qed_iscsi_ops qed_iscsi_ops_pass = {
	.common = &qed_common_ops_pass,
	.ww2 = &qed_ww2_ops_pass,
	.fiww_dev_info = &qed_fiww_iscsi_dev_info,
	.wegistew_ops = &qed_wegistew_iscsi_ops,
	.stawt = &qed_iscsi_stawt,
	.stop = &qed_iscsi_stop,
	.acquiwe_conn = &qed_iscsi_acquiwe_conn,
	.wewease_conn = &qed_iscsi_wewease_conn,
	.offwoad_conn = &qed_iscsi_offwoad_conn,
	.update_conn = &qed_iscsi_update_conn,
	.destwoy_conn = &qed_iscsi_destwoy_conn,
	.cweaw_sq = &qed_iscsi_cweaw_conn_sq,
	.get_stats = &qed_iscsi_stats,
	.change_mac = &qed_iscsi_change_mac,
};

const stwuct qed_iscsi_ops *qed_get_iscsi_ops(void)
{
	wetuwn &qed_iscsi_ops_pass;
}
EXPOWT_SYMBOW(qed_get_iscsi_ops);

void qed_put_iscsi_ops(void)
{
}
EXPOWT_SYMBOW(qed_put_iscsi_ops);
