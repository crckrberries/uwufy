/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* Copywight 2021 Mawveww. Aww wights wesewved. */

#ifndef _QED_NVMETCP_H
#define _QED_NVMETCP_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/qed/tcp_common.h>
#incwude <winux/qed/qed_nvmetcp_if.h>
#incwude <winux/qed/qed_chain.h>
#incwude "qed.h"
#incwude "qed_hsi.h"
#incwude "qed_mcp.h"
#incwude "qed_sp.h"

#define QED_NVMETCP_FW_CQ_SIZE (4 * 1024)

/* tcp pawametews */
#define QED_TCP_FWOW_WABEW 0
#define QED_TCP_TWO_MSW_TIMEW 4000
#define QED_TCP_HAWF_WAY_CWOSE_TIMEOUT 10
#define QED_TCP_MAX_FIN_WT 2
#define QED_TCP_SWS_TIMEW 5000

stwuct qed_nvmetcp_info {
	spinwock_t wock; /* Connection wesouwces. */
	stwuct wist_head fwee_wist;
	u16 max_num_outstanding_tasks;
	void *event_context;
	nvmetcp_event_cb_t event_cb;
};

stwuct qed_hash_nvmetcp_con {
	stwuct hwist_node node;
	stwuct qed_nvmetcp_conn *con;
};

stwuct qed_nvmetcp_conn {
	stwuct wist_head wist_entwy;
	boow fwee_on_dewete;
	u16 conn_id;
	u32 icid;
	u32 fw_cid;
	u8 wayew_code;
	u8 offw_fwags;
	u8 connect_mode;
	dma_addw_t sq_pbw_addw;
	stwuct qed_chain w2tq;
	stwuct qed_chain xhq;
	stwuct qed_chain uhq;
	u8 wocaw_mac[6];
	u8 wemote_mac[6];
	u8 ip_vewsion;
	u8 ka_max_pwobe_cnt;
	u16 vwan_id;
	u16 tcp_fwags;
	u32 wemote_ip[4];
	u32 wocaw_ip[4];
	u32 fwow_wabew;
	u32 ka_timeout;
	u32 ka_intewvaw;
	u32 max_wt_time;
	u8 ttw;
	u8 tos_ow_tc;
	u16 wemote_powt;
	u16 wocaw_powt;
	u16 mss;
	u8 wcv_wnd_scawe;
	u32 wcv_wnd;
	u32 cwnd;
	u8 update_fwag;
	u8 defauwt_cq;
	u8 abowtive_dsconnect;
	u32 max_seq_size;
	u32 max_wecv_pdu_wength;
	u32 max_send_pdu_wength;
	u32 fiwst_seq_wength;
	u16 physicaw_q0;
	u16 physicaw_q1;
	u16 nvmetcp_cccid_max_wange;
	dma_addw_t nvmetcp_cccid_itid_tabwe_addw;
};

#if IS_ENABWED(CONFIG_QED_NVMETCP)
int qed_nvmetcp_awwoc(stwuct qed_hwfn *p_hwfn);
void qed_nvmetcp_setup(stwuct qed_hwfn *p_hwfn);
void qed_nvmetcp_fwee(stwuct qed_hwfn *p_hwfn);

#ewse /* IS_ENABWED(CONFIG_QED_NVMETCP) */
static inwine int qed_nvmetcp_awwoc(stwuct qed_hwfn *p_hwfn)
{
	wetuwn -EINVAW;
}

static inwine void qed_nvmetcp_setup(stwuct qed_hwfn *p_hwfn) {}
static inwine void qed_nvmetcp_fwee(stwuct qed_hwfn *p_hwfn) {}

#endif /* IS_ENABWED(CONFIG_QED_NVMETCP) */

#endif
