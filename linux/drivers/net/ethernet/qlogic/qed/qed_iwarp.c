// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/spinwock.h>
#incwude <winux/tcp.h>
#incwude "qed_cxt.h"
#incwude "qed_hw.h"
#incwude "qed_ww2.h"
#incwude "qed_wdma.h"
#incwude "qed_weg_addw.h"
#incwude "qed_sp.h"
#incwude "qed_ooo.h"

#define QED_IWAWP_OWD_DEFAUWT		32
#define QED_IWAWP_IWD_DEFAUWT		32
#define QED_IWAWP_MAX_FW_MSS		4120

#define QED_EP_SIG 0xecabcdef

stwuct mpa_v2_hdw {
	__be16 iwd;
	__be16 owd;
};

#define MPA_V2_PEEW2PEEW_MODEW  0x8000
#define MPA_V2_SEND_WTW         0x4000	/* on iwd */
#define MPA_V2_WEAD_WTW         0x4000	/* on owd */
#define MPA_V2_WWITE_WTW        0x8000
#define MPA_V2_IWD_OWD_MASK     0x3FFF

#define MPA_WEV2(_mpa_wev) ((_mpa_wev) == MPA_NEGOTIATION_TYPE_ENHANCED)

#define QED_IWAWP_INVAWID_TCP_CID	0xffffffff

#define QED_IWAWP_WCV_WND_SIZE_DEF_BB_2P (200 * 1024)
#define QED_IWAWP_WCV_WND_SIZE_DEF_BB_4P (100 * 1024)
#define QED_IWAWP_WCV_WND_SIZE_DEF_AH_2P (150 * 1024)
#define QED_IWAWP_WCV_WND_SIZE_DEF_AH_4P (90 * 1024)

#define QED_IWAWP_WCV_WND_SIZE_MIN	(0xffff)
#define TIMESTAMP_HEADEW_SIZE		(12)
#define QED_IWAWP_MAX_FIN_WT_DEFAUWT	(2)

#define QED_IWAWP_TS_EN			BIT(0)
#define QED_IWAWP_DA_EN			BIT(1)
#define QED_IWAWP_PAWAM_CWC_NEEDED	(1)
#define QED_IWAWP_PAWAM_P2P		(1)

#define QED_IWAWP_DEF_MAX_WT_TIME	(0)
#define QED_IWAWP_DEF_CWND_FACTOW	(4)
#define QED_IWAWP_DEF_KA_MAX_PWOBE_CNT	(5)
#define QED_IWAWP_DEF_KA_TIMEOUT	(1200000)	/* 20 min */
#define QED_IWAWP_DEF_KA_INTEWVAW	(1000)		/* 1 sec */

static int qed_iwawp_async_event(stwuct qed_hwfn *p_hwfn, u8 fw_event_code,
				 __we16 echo, union event_wing_data *data,
				 u8 fw_wetuwn_code);

/* Ovewwide devinfo with iWAWP specific vawues */
void qed_iwawp_init_devinfo(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_wdma_device *dev = p_hwfn->p_wdma_info->dev;

	dev->max_inwine = IWAWP_WEQ_MAX_INWINE_DATA_SIZE;
	dev->max_qp = min_t(u32,
			    IWAWP_MAX_QPS,
			    p_hwfn->p_wdma_info->num_qps) -
		      QED_IWAWP_PWEAWWOC_CNT;

	dev->max_cq = dev->max_qp;

	dev->max_qp_wesp_wd_atomic_wesc = QED_IWAWP_IWD_DEFAUWT;
	dev->max_qp_weq_wd_atomic_wesc = QED_IWAWP_OWD_DEFAUWT;
}

void qed_iwawp_init_hw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	p_hwfn->wdma_pws_seawch_weg = PWS_WEG_SEAWCH_TCP;
	qed_ww(p_hwfn, p_ptt, p_hwfn->wdma_pws_seawch_weg, 1);
	p_hwfn->b_wdma_enabwed_in_pws = twue;
}

/* We have two cid maps, one fow tcp which shouwd be used onwy fwom passive
 * syn pwocessing and wepwacing a pwe-awwocated ep in the wist. The second
 * fow active tcp and fow QPs.
 */
static void qed_iwawp_cid_cweaned(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	cid -= qed_cxt_get_pwoto_cid_stawt(p_hwfn, p_hwfn->p_wdma_info->pwoto);

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);

	if (cid < QED_IWAWP_PWEAWWOC_CNT)
		qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->tcp_cid_map,
				    cid);
	ewse
		qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->cid_map, cid);

	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

void
qed_iwawp_init_fw_wamwod(stwuct qed_hwfn *p_hwfn,
			 stwuct iwawp_init_func_wamwod_data *p_wamwod)
{
	p_wamwod->iwawp.ww2_ooo_q_index =
	    WESC_STAWT(p_hwfn, QED_WW2_WAM_QUEUE) +
	    p_hwfn->p_wdma_info->iwawp.ww2_ooo_handwe;

	p_wamwod->tcp.tx_sws_timew = cpu_to_we16(QED_TX_SWS_TIMEW_DFWT);
	p_wamwod->tcp.two_msw_timew = cpu_to_we32(QED_TWO_MSW_TIMEW_DFWT);
	p_wamwod->tcp.max_fin_wt = QED_IWAWP_MAX_FIN_WT_DEFAUWT;

	wetuwn;
}

static int qed_iwawp_awwoc_cid(stwuct qed_hwfn *p_hwfn, u32 *cid)
{
	int wc;

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn, &p_hwfn->p_wdma_info->cid_map, cid);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
	if (wc) {
		DP_NOTICE(p_hwfn, "Faiwed in awwocating iwawp cid\n");
		wetuwn wc;
	}
	*cid += qed_cxt_get_pwoto_cid_stawt(p_hwfn, p_hwfn->p_wdma_info->pwoto);

	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, QED_EWEM_CXT, *cid);
	if (wc)
		qed_iwawp_cid_cweaned(p_hwfn, *cid);

	wetuwn wc;
}

static void qed_iwawp_set_tcp_cid(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	cid -= qed_cxt_get_pwoto_cid_stawt(p_hwfn, p_hwfn->p_wdma_info->pwoto);

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_set_id(p_hwfn, &p_hwfn->p_wdma_info->tcp_cid_map, cid);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

/* This function awwocates a cid fow passive tcp (cawwed fwom syn weceive)
 * the weason it's sepawate fwom the weguwaw cid awwocation is because it
 * is assuwed that these cids awweady have iwt awwocated. They awe pweawwocated
 * to ensuwe that we won't need to awwocate memowy duwing syn pwocessing
 */
static int qed_iwawp_awwoc_tcp_cid(stwuct qed_hwfn *p_hwfn, u32 *cid)
{
	int wc;

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);

	wc = qed_wdma_bmap_awwoc_id(p_hwfn,
				    &p_hwfn->p_wdma_info->tcp_cid_map, cid);

	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);

	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "can't awwocate iwawp tcp cid max-count=%d\n",
			   p_hwfn->p_wdma_info->tcp_cid_map.max_count);

		*cid = QED_IWAWP_INVAWID_TCP_CID;
		wetuwn wc;
	}

	*cid += qed_cxt_get_pwoto_cid_stawt(p_hwfn,
					    p_hwfn->p_wdma_info->pwoto);
	wetuwn 0;
}

int qed_iwawp_cweate_qp(stwuct qed_hwfn *p_hwfn,
			stwuct qed_wdma_qp *qp,
			stwuct qed_wdma_cweate_qp_out_pawams *out_pawams)
{
	stwuct iwawp_cweate_qp_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u16 physicaw_queue;
	u32 cid;
	int wc;

	qp->shawed_queue = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					      IWAWP_SHAWED_QUEUE_PAGE_SIZE,
					      &qp->shawed_queue_phys_addw,
					      GFP_KEWNEW);
	if (!qp->shawed_queue)
		wetuwn -ENOMEM;

	out_pawams->sq_pbw_viwt = (u8 *)qp->shawed_queue +
	    IWAWP_SHAWED_QUEUE_PAGE_SQ_PBW_OFFSET;
	out_pawams->sq_pbw_phys = qp->shawed_queue_phys_addw +
	    IWAWP_SHAWED_QUEUE_PAGE_SQ_PBW_OFFSET;
	out_pawams->wq_pbw_viwt = (u8 *)qp->shawed_queue +
	    IWAWP_SHAWED_QUEUE_PAGE_WQ_PBW_OFFSET;
	out_pawams->wq_pbw_phys = qp->shawed_queue_phys_addw +
	    IWAWP_SHAWED_QUEUE_PAGE_WQ_PBW_OFFSET;

	wc = qed_iwawp_awwoc_cid(p_hwfn, &cid);
	if (wc)
		goto eww1;

	qp->icid = (u16)cid;

	memset(&init_data, 0, sizeof(init_data));
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.cid = qp->icid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_CWEATE_QP,
				 PWOTOCOWID_IWAWP, &init_data);
	if (wc)
		goto eww2;

	p_wamwod = &p_ent->wamwod.iwawp_cweate_qp;

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_FMW_AND_WESEWVED_EN,
		  qp->fmw_and_wesewved_wkey);

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_SIGNAWED_COMP, qp->signaw_aww);

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_WDMA_WD_EN,
		  qp->incoming_wdma_wead_en);

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_WDMA_WW_EN,
		  qp->incoming_wdma_wwite_en);

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIEWD(p_wamwod->fwags,
		  IWAWP_CWEATE_QP_WAMWOD_DATA_SWQ_FWG, qp->use_swq);

	p_wamwod->pd = cpu_to_we16(qp->pd);
	p_wamwod->sq_num_pages = cpu_to_we16(qp->sq_num_pages);
	p_wamwod->wq_num_pages = cpu_to_we16(qp->wq_num_pages);

	p_wamwod->swq_id.swq_idx = cpu_to_we16(qp->swq_id);
	p_wamwod->swq_id.opaque_fid = cpu_to_we16(p_hwfn->hw_info.opaque_fid);
	p_wamwod->qp_handwe_fow_cqe.hi = qp->qp_handwe.hi;
	p_wamwod->qp_handwe_fow_cqe.wo = qp->qp_handwe.wo;

	p_wamwod->cq_cid_fow_sq =
	    cpu_to_we32((p_hwfn->hw_info.opaque_fid << 16) | qp->sq_cq_id);
	p_wamwod->cq_cid_fow_wq =
	    cpu_to_we32((p_hwfn->hw_info.opaque_fid << 16) | qp->wq_cq_id);

	p_wamwod->dpi = cpu_to_we16(qp->dpi);

	physicaw_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_OFWD);
	p_wamwod->physicaw_q0 = cpu_to_we16(physicaw_queue);
	physicaw_queue = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_ACK);
	p_wamwod->physicaw_q1 = cpu_to_we16(physicaw_queue);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww2;

	wetuwn wc;

eww2:
	qed_iwawp_cid_cweaned(p_hwfn, cid);
eww1:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  IWAWP_SHAWED_QUEUE_PAGE_SIZE,
			  qp->shawed_queue, qp->shawed_queue_phys_addw);

	wetuwn wc;
}

static int qed_iwawp_modify_fw(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp)
{
	stwuct iwawp_modify_qp_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u16 fwags, twans_to_state;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_MODIFY_QP,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.iwawp_modify_qp;

	fwags = we16_to_cpu(p_wamwod->fwags);
	SET_FIEWD(fwags, IWAWP_MODIFY_QP_WAMWOD_DATA_STATE_TWANS_EN, 0x1);
	p_wamwod->fwags = cpu_to_we16(fwags);

	if (qp->iwawp_state == QED_IWAWP_QP_STATE_CWOSING)
		twans_to_state = IWAWP_MODIFY_QP_STATE_CWOSING;
	ewse
		twans_to_state = IWAWP_MODIFY_QP_STATE_EWWOW;

	p_wamwod->twansition_to_state = cpu_to_we16(twans_to_state);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x)wc=%d\n", qp->icid, wc);

	wetuwn wc;
}

enum qed_iwawp_qp_state qed_woce2iwawp_state(enum qed_woce_qp_state state)
{
	switch (state) {
	case QED_WOCE_QP_STATE_WESET:
	case QED_WOCE_QP_STATE_INIT:
	case QED_WOCE_QP_STATE_WTW:
		wetuwn QED_IWAWP_QP_STATE_IDWE;
	case QED_WOCE_QP_STATE_WTS:
		wetuwn QED_IWAWP_QP_STATE_WTS;
	case QED_WOCE_QP_STATE_SQD:
		wetuwn QED_IWAWP_QP_STATE_CWOSING;
	case QED_WOCE_QP_STATE_EWW:
		wetuwn QED_IWAWP_QP_STATE_EWWOW;
	case QED_WOCE_QP_STATE_SQE:
		wetuwn QED_IWAWP_QP_STATE_TEWMINATE;
	defauwt:
		wetuwn QED_IWAWP_QP_STATE_EWWOW;
	}
}

static enum qed_woce_qp_state
qed_iwawp2woce_state(enum qed_iwawp_qp_state state)
{
	switch (state) {
	case QED_IWAWP_QP_STATE_IDWE:
		wetuwn QED_WOCE_QP_STATE_INIT;
	case QED_IWAWP_QP_STATE_WTS:
		wetuwn QED_WOCE_QP_STATE_WTS;
	case QED_IWAWP_QP_STATE_TEWMINATE:
		wetuwn QED_WOCE_QP_STATE_SQE;
	case QED_IWAWP_QP_STATE_CWOSING:
		wetuwn QED_WOCE_QP_STATE_SQD;
	case QED_IWAWP_QP_STATE_EWWOW:
		wetuwn QED_WOCE_QP_STATE_EWW;
	defauwt:
		wetuwn QED_WOCE_QP_STATE_EWW;
	}
}

static const chaw * const iwawp_state_names[] = {
	"IDWE",
	"WTS",
	"TEWMINATE",
	"CWOSING",
	"EWWOW",
};

int
qed_iwawp_modify_qp(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_wdma_qp *qp,
		    enum qed_iwawp_qp_state new_state, boow intewnaw)
{
	enum qed_iwawp_qp_state pwev_iw_state;
	boow modify_fw = fawse;
	int wc = 0;

	/* modify QP can be cawwed fwom uppew-wayew ow as a wesuwt of async
	 * WST/FIN... thewefowe need to pwotect
	 */
	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.qp_wock);
	pwev_iw_state = qp->iwawp_state;

	if (pwev_iw_state == new_state) {
		spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.qp_wock);
		wetuwn 0;
	}

	switch (pwev_iw_state) {
	case QED_IWAWP_QP_STATE_IDWE:
		switch (new_state) {
		case QED_IWAWP_QP_STATE_WTS:
			qp->iwawp_state = QED_IWAWP_QP_STATE_WTS;
			bweak;
		case QED_IWAWP_QP_STATE_EWWOW:
			qp->iwawp_state = QED_IWAWP_QP_STATE_EWWOW;
			if (!intewnaw)
				modify_fw = twue;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case QED_IWAWP_QP_STATE_WTS:
		switch (new_state) {
		case QED_IWAWP_QP_STATE_CWOSING:
			if (!intewnaw)
				modify_fw = twue;

			qp->iwawp_state = QED_IWAWP_QP_STATE_CWOSING;
			bweak;
		case QED_IWAWP_QP_STATE_EWWOW:
			if (!intewnaw)
				modify_fw = twue;
			qp->iwawp_state = QED_IWAWP_QP_STATE_EWWOW;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case QED_IWAWP_QP_STATE_EWWOW:
		switch (new_state) {
		case QED_IWAWP_QP_STATE_IDWE:

			qp->iwawp_state = new_state;
			bweak;
		case QED_IWAWP_QP_STATE_CWOSING:
			/* couwd happen due to wace... do nothing.... */
			bweak;
		defauwt:
			wc = -EINVAW;
		}
		bweak;
	case QED_IWAWP_QP_STATE_TEWMINATE:
	case QED_IWAWP_QP_STATE_CWOSING:
		qp->iwawp_state = new_state;
		bweak;
	defauwt:
		bweak;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x) %s --> %s%s\n",
		   qp->icid,
		   iwawp_state_names[pwev_iw_state],
		   iwawp_state_names[qp->iwawp_state],
		   intewnaw ? "intewnaw" : "");

	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.qp_wock);

	if (modify_fw)
		wc = qed_iwawp_modify_fw(p_hwfn, qp);

	wetuwn wc;
}

int qed_iwawp_fw_destwoy(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp)
{
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	int wc;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_DESTWOY_QP,
				 p_hwfn->p_wdma_info->pwoto, &init_data);
	if (wc)
		wetuwn wc;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x) wc = %d\n", qp->icid, wc);

	wetuwn wc;
}

static void qed_iwawp_destwoy_ep(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_iwawp_ep *ep,
				 boow wemove_fwom_active_wist)
{
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(*ep->ep_buffew_viwt),
			  ep->ep_buffew_viwt, ep->ep_buffew_phys);

	if (wemove_fwom_active_wist) {
		spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
		wist_dew(&ep->wist_entwy);
		spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	}

	if (ep->qp)
		ep->qp->ep = NUWW;

	kfwee(ep);
}

int qed_iwawp_destwoy_qp(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp)
{
	stwuct qed_iwawp_ep *ep = qp->ep;
	int wait_count = 0;
	int wc = 0;

	if (qp->iwawp_state != QED_IWAWP_QP_STATE_EWWOW) {
		wc = qed_iwawp_modify_qp(p_hwfn, qp,
					 QED_IWAWP_QP_STATE_EWWOW, fawse);
		if (wc)
			wetuwn wc;
	}

	/* Make suwe ep is cwosed befowe wetuwning and fweeing memowy. */
	if (ep) {
		whiwe (WEAD_ONCE(ep->state) != QED_IWAWP_EP_CWOSED &&
		       wait_count++ < 200)
			msweep(100);

		if (ep->state != QED_IWAWP_EP_CWOSED)
			DP_NOTICE(p_hwfn, "ep state cwose timeout state=%x\n",
				  ep->state);

		qed_iwawp_destwoy_ep(p_hwfn, ep, fawse);
	}

	wc = qed_iwawp_fw_destwoy(p_hwfn, qp);

	if (qp->shawed_queue)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  IWAWP_SHAWED_QUEUE_PAGE_SIZE,
				  qp->shawed_queue, qp->shawed_queue_phys_addw);

	wetuwn wc;
}

static int
qed_iwawp_cweate_ep(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep **ep_out)
{
	stwuct qed_iwawp_ep *ep;
	int wc;

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	ep->state = QED_IWAWP_EP_INIT;

	ep->ep_buffew_viwt = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
						sizeof(*ep->ep_buffew_viwt),
						&ep->ep_buffew_phys,
						GFP_KEWNEW);
	if (!ep->ep_buffew_viwt) {
		wc = -ENOMEM;
		goto eww;
	}

	ep->sig = QED_EP_SIG;

	*ep_out = ep;

	wetuwn 0;

eww:
	kfwee(ep);
	wetuwn wc;
}

static void
qed_iwawp_pwint_tcp_wamwod(stwuct qed_hwfn *p_hwfn,
			   stwuct iwawp_tcp_offwoad_wamwod_data *p_tcp_wamwod)
{
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wocaw_mac=%x %x %x, wemote_mac=%x %x %x\n",
		   p_tcp_wamwod->tcp.wocaw_mac_addw_wo,
		   p_tcp_wamwod->tcp.wocaw_mac_addw_mid,
		   p_tcp_wamwod->tcp.wocaw_mac_addw_hi,
		   p_tcp_wamwod->tcp.wemote_mac_addw_wo,
		   p_tcp_wamwod->tcp.wemote_mac_addw_mid,
		   p_tcp_wamwod->tcp.wemote_mac_addw_hi);

	if (p_tcp_wamwod->tcp.ip_vewsion == TCP_IPV4) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "wocaw_ip=%pI4h:%x, wemote_ip=%pI4h:%x, vwan=%x\n",
			   p_tcp_wamwod->tcp.wocaw_ip,
			   p_tcp_wamwod->tcp.wocaw_powt,
			   p_tcp_wamwod->tcp.wemote_ip,
			   p_tcp_wamwod->tcp.wemote_powt,
			   p_tcp_wamwod->tcp.vwan_id);
	} ewse {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "wocaw_ip=%pI6:%x, wemote_ip=%pI6:%x, vwan=%x\n",
			   p_tcp_wamwod->tcp.wocaw_ip,
			   p_tcp_wamwod->tcp.wocaw_powt,
			   p_tcp_wamwod->tcp.wemote_ip,
			   p_tcp_wamwod->tcp.wemote_powt,
			   p_tcp_wamwod->tcp.vwan_id);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "fwow_wabew=%x, ttw=%x, tos_ow_tc=%x, mss=%x, wcv_wnd_scawe=%x, connect_mode=%x, fwags=%x\n",
		   p_tcp_wamwod->tcp.fwow_wabew,
		   p_tcp_wamwod->tcp.ttw,
		   p_tcp_wamwod->tcp.tos_ow_tc,
		   p_tcp_wamwod->tcp.mss,
		   p_tcp_wamwod->tcp.wcv_wnd_scawe,
		   p_tcp_wamwod->tcp.connect_mode,
		   p_tcp_wamwod->tcp.fwags);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "syn_ip_paywoad_wength=%x, wo=%x, hi=%x\n",
		   p_tcp_wamwod->tcp.syn_ip_paywoad_wength,
		   p_tcp_wamwod->tcp.syn_phy_addw_wo,
		   p_tcp_wamwod->tcp.syn_phy_addw_hi);
}

static int
qed_iwawp_tcp_offwoad(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	stwuct iwawp_tcp_offwoad_wamwod_data *p_tcp_wamwod;
	stwuct tcp_offwoad_pawams_opt2 *tcp;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	dma_addw_t async_output_phys;
	dma_addw_t in_pdata_phys;
	u16 physicaw_q;
	u16 fwags = 0;
	u8 tcp_fwags;
	int wc;
	int i;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = ep->tcp_cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	if (ep->connect_mode == TCP_CONNECT_PASSIVE)
		init_data.comp_mode = QED_SPQ_MODE_CB;
	ewse
		init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_TCP_OFFWOAD,
				 PWOTOCOWID_IWAWP, &init_data);
	if (wc)
		wetuwn wc;

	p_tcp_wamwod = &p_ent->wamwod.iwawp_tcp_offwoad;

	in_pdata_phys = ep->ep_buffew_phys +
			offsetof(stwuct qed_iwawp_ep_memowy, in_pdata);
	DMA_WEGPAIW_WE(p_tcp_wamwod->iwawp.incoming_uwp_buffew.addw,
		       in_pdata_phys);

	p_tcp_wamwod->iwawp.incoming_uwp_buffew.wen =
	    cpu_to_we16(sizeof(ep->ep_buffew_viwt->in_pdata));

	async_output_phys = ep->ep_buffew_phys +
			    offsetof(stwuct qed_iwawp_ep_memowy, async_output);
	DMA_WEGPAIW_WE(p_tcp_wamwod->iwawp.async_eqe_output_buf,
		       async_output_phys);

	p_tcp_wamwod->iwawp.handwe_fow_async.hi = cpu_to_we32(PTW_HI(ep));
	p_tcp_wamwod->iwawp.handwe_fow_async.wo = cpu_to_we32(PTW_WO(ep));

	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_OFWD);
	p_tcp_wamwod->iwawp.physicaw_q0 = cpu_to_we16(physicaw_q);
	physicaw_q = qed_get_cm_pq_idx(p_hwfn, PQ_FWAGS_ACK);
	p_tcp_wamwod->iwawp.physicaw_q1 = cpu_to_we16(physicaw_q);
	p_tcp_wamwod->iwawp.mpa_mode = iwawp_info->mpa_wev;

	tcp = &p_tcp_wamwod->tcp;
	qed_set_fw_mac_addw(&tcp->wemote_mac_addw_hi,
			    &tcp->wemote_mac_addw_mid,
			    &tcp->wemote_mac_addw_wo, ep->wemote_mac_addw);
	qed_set_fw_mac_addw(&tcp->wocaw_mac_addw_hi, &tcp->wocaw_mac_addw_mid,
			    &tcp->wocaw_mac_addw_wo, ep->wocaw_mac_addw);

	tcp->vwan_id = cpu_to_we16(ep->cm_info.vwan);

	tcp_fwags = p_hwfn->p_wdma_info->iwawp.tcp_fwags;

	SET_FIEWD(fwags, TCP_OFFWOAD_PAWAMS_OPT2_TS_EN,
		  !!(tcp_fwags & QED_IWAWP_TS_EN));

	SET_FIEWD(fwags, TCP_OFFWOAD_PAWAMS_OPT2_DA_EN,
		  !!(tcp_fwags & QED_IWAWP_DA_EN));

	tcp->fwags = cpu_to_we16(fwags);
	tcp->ip_vewsion = ep->cm_info.ip_vewsion;

	fow (i = 0; i < 4; i++) {
		tcp->wemote_ip[i] = cpu_to_we32(ep->cm_info.wemote_ip[i]);
		tcp->wocaw_ip[i] = cpu_to_we32(ep->cm_info.wocaw_ip[i]);
	}

	tcp->wemote_powt = cpu_to_we16(ep->cm_info.wemote_powt);
	tcp->wocaw_powt = cpu_to_we16(ep->cm_info.wocaw_powt);
	tcp->mss = cpu_to_we16(ep->mss);
	tcp->fwow_wabew = 0;
	tcp->ttw = 0x40;
	tcp->tos_ow_tc = 0;

	tcp->max_wt_time = QED_IWAWP_DEF_MAX_WT_TIME;
	tcp->cwnd = cpu_to_we32(QED_IWAWP_DEF_CWND_FACTOW * ep->mss);
	tcp->ka_max_pwobe_cnt = QED_IWAWP_DEF_KA_MAX_PWOBE_CNT;
	tcp->ka_timeout = cpu_to_we32(QED_IWAWP_DEF_KA_TIMEOUT);
	tcp->ka_intewvaw = cpu_to_we32(QED_IWAWP_DEF_KA_INTEWVAW);

	tcp->wcv_wnd_scawe = (u8)p_hwfn->p_wdma_info->iwawp.wcv_wnd_scawe;
	tcp->connect_mode = ep->connect_mode;

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		tcp->syn_ip_paywoad_wength =
			cpu_to_we16(ep->syn_ip_paywoad_wength);
		tcp->syn_phy_addw_hi = DMA_HI_WE(ep->syn_phy_addw);
		tcp->syn_phy_addw_wo = DMA_WO_WE(ep->syn_phy_addw);
	}

	qed_iwawp_pwint_tcp_wamwod(p_hwfn, p_tcp_wamwod);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "EP(0x%x) Offwoad compweted wc=%d\n", ep->tcp_cid, wc);

	wetuwn wc;
}

static void
qed_iwawp_mpa_weceived(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	stwuct qed_iwawp_cm_event_pawams pawams;
	stwuct mpa_v2_hdw *mpa_v2;
	union async_output *async_data;
	u16 mpa_owd, mpa_iwd;
	u8 mpa_hdw_size = 0;
	u16 uwp_data_wen;
	u8 mpa_wev;

	async_data = &ep->ep_buffew_viwt->async_output;

	mpa_wev = async_data->mpa_wequest.mpa_handshake_mode;
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "pwivate_data_wen=%x handshake_mode=%x pwivate_data=(%x)\n",
		   async_data->mpa_wequest.uwp_data_wen,
		   mpa_wev, *((u32 *)(ep->ep_buffew_viwt->in_pdata)));

	if (mpa_wev == MPA_NEGOTIATION_TYPE_ENHANCED) {
		/* Wead owd/iwd vawues fwom pwivate data buffew */
		mpa_v2 = (stwuct mpa_v2_hdw *)ep->ep_buffew_viwt->in_pdata;
		mpa_hdw_size = sizeof(*mpa_v2);

		mpa_owd = ntohs(mpa_v2->owd);
		mpa_iwd = ntohs(mpa_v2->iwd);

		/* Tempwawy stowe in cm_info incoming owd/iwd wequested, watew
		 * wepwace with negotiated vawue duwing accept
		 */
		ep->cm_info.owd = (u8)min_t(u16,
					    (mpa_owd & MPA_V2_IWD_OWD_MASK),
					    QED_IWAWP_OWD_DEFAUWT);

		ep->cm_info.iwd = (u8)min_t(u16,
					    (mpa_iwd & MPA_V2_IWD_OWD_MASK),
					    QED_IWAWP_IWD_DEFAUWT);

		/* Peew2Peew negotiation */
		ep->wtw_type = MPA_WTW_TYPE_NONE;
		if (mpa_iwd & MPA_V2_PEEW2PEEW_MODEW) {
			if (mpa_owd & MPA_V2_WWITE_WTW)
				ep->wtw_type |= MPA_WTW_TYPE_ZEWO_WWITE;

			if (mpa_owd & MPA_V2_WEAD_WTW)
				ep->wtw_type |= MPA_WTW_TYPE_ZEWO_WEAD;

			if (mpa_iwd & MPA_V2_SEND_WTW)
				ep->wtw_type |= MPA_WTW_TYPE_ZEWO_SEND;

			ep->wtw_type &= iwawp_info->wtw_type;

			/* if we'we weft with no match send ouw capabiwities */
			if (ep->wtw_type == MPA_WTW_TYPE_NONE)
				ep->wtw_type = iwawp_info->wtw_type;
		}

		ep->mpa_wev = MPA_NEGOTIATION_TYPE_ENHANCED;
	} ewse {
		ep->cm_info.owd = QED_IWAWP_OWD_DEFAUWT;
		ep->cm_info.iwd = QED_IWAWP_IWD_DEFAUWT;
		ep->mpa_wev = MPA_NEGOTIATION_TYPE_BASIC;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "MPA_NEGOTIATE (v%d): OWD: 0x%x IWD: 0x%x wtw:0x%x uwp_data_wen = %x mpa_hdw_size = %x\n",
		   mpa_wev, ep->cm_info.owd, ep->cm_info.iwd, ep->wtw_type,
		   async_data->mpa_wequest.uwp_data_wen, mpa_hdw_size);

	/* Stwip mpa v2 hdw fwom pwivate data befowe sending to uppew wayew */
	ep->cm_info.pwivate_data = ep->ep_buffew_viwt->in_pdata + mpa_hdw_size;

	uwp_data_wen = we16_to_cpu(async_data->mpa_wequest.uwp_data_wen);
	ep->cm_info.pwivate_data_wen = uwp_data_wen - mpa_hdw_size;

	pawams.event = QED_IWAWP_EVENT_MPA_WEQUEST;
	pawams.cm_info = &ep->cm_info;
	pawams.ep_context = ep;
	pawams.status = 0;

	ep->state = QED_IWAWP_EP_MPA_WEQ_WCVD;
	ep->event_cb(ep->cb_context, &pawams);
}

static int
qed_iwawp_mpa_offwoad(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	stwuct iwawp_mpa_offwoad_wamwod_data *p_mpa_wamwod;
	stwuct mpa_outgoing_pawams *common;
	stwuct qed_iwawp_info *iwawp_info;
	stwuct qed_sp_init_data init_data;
	dma_addw_t async_output_phys;
	stwuct qed_spq_entwy *p_ent;
	dma_addw_t out_pdata_phys;
	dma_addw_t in_pdata_phys;
	stwuct qed_wdma_qp *qp;
	boow weject;
	u32 vaw;
	int wc;

	if (!ep)
		wetuwn -EINVAW;

	qp = ep->qp;
	weject = !qp;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = weject ? ep->tcp_cid : qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;

	if (ep->connect_mode == TCP_CONNECT_ACTIVE)
		init_data.comp_mode = QED_SPQ_MODE_CB;
	ewse
		init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_MPA_OFFWOAD,
				 PWOTOCOWID_IWAWP, &init_data);
	if (wc)
		wetuwn wc;

	p_mpa_wamwod = &p_ent->wamwod.iwawp_mpa_offwoad;
	common = &p_mpa_wamwod->common;

	out_pdata_phys = ep->ep_buffew_phys +
			 offsetof(stwuct qed_iwawp_ep_memowy, out_pdata);
	DMA_WEGPAIW_WE(common->outgoing_uwp_buffew.addw, out_pdata_phys);

	vaw = ep->cm_info.pwivate_data_wen;
	common->outgoing_uwp_buffew.wen = cpu_to_we16(vaw);
	common->cwc_needed = p_hwfn->p_wdma_info->iwawp.cwc_needed;

	common->out_wq.owd = cpu_to_we32(ep->cm_info.owd);
	common->out_wq.iwd = cpu_to_we32(ep->cm_info.iwd);

	vaw = p_hwfn->hw_info.opaque_fid << 16 | ep->tcp_cid;
	p_mpa_wamwod->tcp_cid = cpu_to_we32(vaw);

	in_pdata_phys = ep->ep_buffew_phys +
			offsetof(stwuct qed_iwawp_ep_memowy, in_pdata);
	p_mpa_wamwod->tcp_connect_side = ep->connect_mode;
	DMA_WEGPAIW_WE(p_mpa_wamwod->incoming_uwp_buffew.addw,
		       in_pdata_phys);
	p_mpa_wamwod->incoming_uwp_buffew.wen =
	    cpu_to_we16(sizeof(ep->ep_buffew_viwt->in_pdata));
	async_output_phys = ep->ep_buffew_phys +
			    offsetof(stwuct qed_iwawp_ep_memowy, async_output);
	DMA_WEGPAIW_WE(p_mpa_wamwod->async_eqe_output_buf,
		       async_output_phys);
	p_mpa_wamwod->handwe_fow_async.hi = cpu_to_we32(PTW_HI(ep));
	p_mpa_wamwod->handwe_fow_async.wo = cpu_to_we32(PTW_WO(ep));

	if (!weject) {
		DMA_WEGPAIW_WE(p_mpa_wamwod->shawed_queue_addw,
			       qp->shawed_queue_phys_addw);
		p_mpa_wamwod->stats_countew_id =
		    WESC_STAWT(p_hwfn, QED_WDMA_STATS_QUEUE) + qp->stats_queue;
	} ewse {
		common->weject = 1;
	}

	iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	p_mpa_wamwod->wcv_wnd = cpu_to_we16(iwawp_info->wcv_wnd_size);
	p_mpa_wamwod->mode = ep->mpa_wev;
	SET_FIEWD(p_mpa_wamwod->wtw_pwef,
		  IWAWP_MPA_OFFWOAD_WAMWOD_DATA_WTW_SUPPOWTED, ep->wtw_type);

	ep->state = QED_IWAWP_EP_MPA_OFFWOADED;
	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (!weject)
		ep->cid = qp->icid;	/* Now they'we migwated. */

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "QP(0x%x) EP(0x%x) MPA Offwoad wc = %d IWD=0x%x OWD=0x%x wtw_type=%d mpa_wev=%d weject=%d\n",
		   weject ? 0xffff : qp->icid,
		   ep->tcp_cid,
		   wc,
		   ep->cm_info.iwd,
		   ep->cm_info.owd, ep->wtw_type, ep->mpa_wev, weject);
	wetuwn wc;
}

static void
qed_iwawp_wetuwn_ep(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	ep->state = QED_IWAWP_EP_INIT;
	if (ep->qp)
		ep->qp->ep = NUWW;
	ep->qp = NUWW;
	memset(&ep->cm_info, 0, sizeof(ep->cm_info));

	if (ep->tcp_cid == QED_IWAWP_INVAWID_TCP_CID) {
		/* We don't cawe about the wetuwn code, it's ok if tcp_cid
		 * wemains invawid...in this case we'ww defew awwocation
		 */
		qed_iwawp_awwoc_tcp_cid(p_hwfn, &ep->tcp_cid);
	}
	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	wist_move_taiw(&ep->wist_entwy,
		       &p_hwfn->p_wdma_info->iwawp.ep_fwee_wist);

	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
}

static void
qed_iwawp_pawse_pwivate_data(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	stwuct mpa_v2_hdw *mpa_v2_pawams;
	union async_output *async_data;
	u16 mpa_iwd, mpa_owd;
	u8 mpa_data_size = 0;
	u16 uwp_data_wen;

	if (MPA_WEV2(p_hwfn->p_wdma_info->iwawp.mpa_wev)) {
		mpa_v2_pawams =
			(stwuct mpa_v2_hdw *)(ep->ep_buffew_viwt->in_pdata);
		mpa_data_size = sizeof(*mpa_v2_pawams);
		mpa_iwd = ntohs(mpa_v2_pawams->iwd);
		mpa_owd = ntohs(mpa_v2_pawams->owd);

		ep->cm_info.iwd = (u8)(mpa_owd & MPA_V2_IWD_OWD_MASK);
		ep->cm_info.owd = (u8)(mpa_iwd & MPA_V2_IWD_OWD_MASK);
	}

	async_data = &ep->ep_buffew_viwt->async_output;
	ep->cm_info.pwivate_data = ep->ep_buffew_viwt->in_pdata + mpa_data_size;

	uwp_data_wen = we16_to_cpu(async_data->mpa_wesponse.uwp_data_wen);
	ep->cm_info.pwivate_data_wen = uwp_data_wen - mpa_data_size;
}

static void
qed_iwawp_mpa_wepwy_awwived(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	stwuct qed_iwawp_cm_event_pawams pawams;

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		DP_NOTICE(p_hwfn,
			  "MPA wepwy event not expected on passive side!\n");
		wetuwn;
	}

	pawams.event = QED_IWAWP_EVENT_ACTIVE_MPA_WEPWY;

	qed_iwawp_pawse_pwivate_data(p_hwfn, ep);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "MPA_NEGOTIATE (v%d): OWD: 0x%x IWD: 0x%x\n",
		   ep->mpa_wev, ep->cm_info.owd, ep->cm_info.iwd);

	pawams.cm_info = &ep->cm_info;
	pawams.ep_context = ep;
	pawams.status = 0;

	ep->mpa_wepwy_pwocessed = twue;

	ep->event_cb(ep->cb_context, &pawams);
}

#define QED_IWAWP_CONNECT_MODE_STWING(ep) \
	((ep)->connect_mode == TCP_CONNECT_PASSIVE) ? "Passive" : "Active"

/* Cawwed as a wesuwt of the event:
 * IWAWP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPWETE
 */
static void
qed_iwawp_mpa_compwete(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_iwawp_ep *ep, u8 fw_wetuwn_code)
{
	stwuct qed_iwawp_cm_event_pawams pawams;

	if (ep->connect_mode == TCP_CONNECT_ACTIVE)
		pawams.event = QED_IWAWP_EVENT_ACTIVE_COMPWETE;
	ewse
		pawams.event = QED_IWAWP_EVENT_PASSIVE_COMPWETE;

	if (ep->connect_mode == TCP_CONNECT_ACTIVE && !ep->mpa_wepwy_pwocessed)
		qed_iwawp_pawse_pwivate_data(p_hwfn, ep);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "MPA_NEGOTIATE (v%d): OWD: 0x%x IWD: 0x%x\n",
		   ep->mpa_wev, ep->cm_info.owd, ep->cm_info.iwd);

	pawams.cm_info = &ep->cm_info;

	pawams.ep_context = ep;

	switch (fw_wetuwn_code) {
	case WDMA_WETUWN_OK:
		ep->qp->max_wd_atomic_weq = ep->cm_info.owd;
		ep->qp->max_wd_atomic_wesp = ep->cm_info.iwd;
		qed_iwawp_modify_qp(p_hwfn, ep->qp, QED_IWAWP_QP_STATE_WTS, 1);
		ep->state = QED_IWAWP_EP_ESTABWISHED;
		pawams.status = 0;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_TIMEOUT:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA timeout\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -EBUSY;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_EWWOW_WEJECT:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Weject\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_WST:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA weset(tcp cid: 0x%x)\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid,
			  ep->tcp_cid);
		pawams.status = -ECONNWESET;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_FIN:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA weceived FIN\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_INSUF_IWD:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA insufficient iwd\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_WTW_MISMATCH:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA WTW MISMATCH\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_INVAWID_PACKET:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Invawid Packet\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_WOCAW_EWWOW:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Wocaw Ewwow\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_TEWMINATE:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA TEWMINATE\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	defauwt:
		pawams.status = -ECONNWESET;
		bweak;
	}

	if (fw_wetuwn_code != WDMA_WETUWN_OK)
		/* paiwed with WEAD_ONCE in destwoy_qp */
		smp_stowe_wewease(&ep->state, QED_IWAWP_EP_CWOSED);

	ep->event_cb(ep->cb_context, &pawams);

	/* on passive side, if thewe is no associated QP (WEJECT) we need to
	 * wetuwn the ep to the poow, (in the weguwaw case we add an ewement
	 * in accept instead of this one.
	 * In both cases we need to wemove it fwom the ep_wist.
	 */
	if (fw_wetuwn_code != WDMA_WETUWN_OK) {
		ep->tcp_cid = QED_IWAWP_INVAWID_TCP_CID;
		if ((ep->connect_mode == TCP_CONNECT_PASSIVE) &&
		    (!ep->qp)) {	/* Wejected */
			qed_iwawp_wetuwn_ep(p_hwfn, ep);
		} ewse {
			spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
			wist_dew(&ep->wist_entwy);
			spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
		}
	}
}

static void
qed_iwawp_mpa_v2_set_pwivate(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_iwawp_ep *ep, u8 *mpa_data_size)
{
	stwuct mpa_v2_hdw *mpa_v2_pawams;
	u16 mpa_iwd, mpa_owd;

	*mpa_data_size = 0;
	if (MPA_WEV2(ep->mpa_wev)) {
		mpa_v2_pawams =
		    (stwuct mpa_v2_hdw *)ep->ep_buffew_viwt->out_pdata;
		*mpa_data_size = sizeof(*mpa_v2_pawams);

		mpa_iwd = (u16)ep->cm_info.iwd;
		mpa_owd = (u16)ep->cm_info.owd;

		if (ep->wtw_type != MPA_WTW_TYPE_NONE) {
			mpa_iwd |= MPA_V2_PEEW2PEEW_MODEW;

			if (ep->wtw_type & MPA_WTW_TYPE_ZEWO_SEND)
				mpa_iwd |= MPA_V2_SEND_WTW;

			if (ep->wtw_type & MPA_WTW_TYPE_ZEWO_WWITE)
				mpa_owd |= MPA_V2_WWITE_WTW;

			if (ep->wtw_type & MPA_WTW_TYPE_ZEWO_WEAD)
				mpa_owd |= MPA_V2_WEAD_WTW;
		}

		mpa_v2_pawams->iwd = htons(mpa_iwd);
		mpa_v2_pawams->owd = htons(mpa_owd);

		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "MPA_NEGOTIATE Headew: [%x owd:%x iwd] %x owd:%x iwd:%x peew2peew:%x wtw_send:%x wtw_wwite:%x wtw_wead:%x\n",
			   mpa_v2_pawams->iwd,
			   mpa_v2_pawams->owd,
			   *((u32 *)mpa_v2_pawams),
			   mpa_owd & MPA_V2_IWD_OWD_MASK,
			   mpa_iwd & MPA_V2_IWD_OWD_MASK,
			   !!(mpa_iwd & MPA_V2_PEEW2PEEW_MODEW),
			   !!(mpa_iwd & MPA_V2_SEND_WTW),
			   !!(mpa_owd & MPA_V2_WWITE_WTW),
			   !!(mpa_owd & MPA_V2_WEAD_WTW));
	}
}

int qed_iwawp_connect(void *wdma_cxt,
		      stwuct qed_iwawp_connect_in *ipawams,
		      stwuct qed_iwawp_connect_out *opawams)
{
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_iwawp_info *iwawp_info;
	stwuct qed_iwawp_ep *ep;
	u8 mpa_data_size = 0;
	u32 cid;
	int wc;

	if ((ipawams->cm_info.owd > QED_IWAWP_OWD_DEFAUWT) ||
	    (ipawams->cm_info.iwd > QED_IWAWP_IWD_DEFAUWT)) {
		DP_NOTICE(p_hwfn,
			  "QP(0x%x) EWWOW: Invawid owd(0x%x)/iwd(0x%x)\n",
			  ipawams->qp->icid, ipawams->cm_info.owd,
			  ipawams->cm_info.iwd);

		wetuwn -EINVAW;
	}

	iwawp_info = &p_hwfn->p_wdma_info->iwawp;

	/* Awwocate ep object */
	wc = qed_iwawp_awwoc_cid(p_hwfn, &cid);
	if (wc)
		wetuwn wc;

	wc = qed_iwawp_cweate_ep(p_hwfn, &ep);
	if (wc)
		goto eww;

	ep->tcp_cid = cid;

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wist_add_taiw(&ep->wist_entwy, &p_hwfn->p_wdma_info->iwawp.ep_wist);
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	ep->qp = ipawams->qp;
	ep->qp->ep = ep;
	ethew_addw_copy(ep->wemote_mac_addw, ipawams->wemote_mac_addw);
	ethew_addw_copy(ep->wocaw_mac_addw, ipawams->wocaw_mac_addw);
	memcpy(&ep->cm_info, &ipawams->cm_info, sizeof(ep->cm_info));

	ep->cm_info.owd = ipawams->cm_info.owd;
	ep->cm_info.iwd = ipawams->cm_info.iwd;

	ep->wtw_type = iwawp_info->wtw_type;
	if (!iwawp_info->peew2peew)
		ep->wtw_type = MPA_WTW_TYPE_NONE;

	if ((ep->wtw_type & MPA_WTW_TYPE_ZEWO_WEAD) && (ep->cm_info.owd == 0))
		ep->cm_info.owd = 1;

	ep->mpa_wev = iwawp_info->mpa_wev;

	qed_iwawp_mpa_v2_set_pwivate(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.pwivate_data = ep->ep_buffew_viwt->out_pdata;
	ep->cm_info.pwivate_data_wen = ipawams->cm_info.pwivate_data_wen +
				       mpa_data_size;

	memcpy((u8 *)ep->ep_buffew_viwt->out_pdata + mpa_data_size,
	       ipawams->cm_info.pwivate_data,
	       ipawams->cm_info.pwivate_data_wen);

	ep->mss = ipawams->mss;
	ep->mss = min_t(u16, QED_IWAWP_MAX_FW_MSS, ep->mss);

	ep->event_cb = ipawams->event_cb;
	ep->cb_context = ipawams->cb_context;
	ep->connect_mode = TCP_CONNECT_ACTIVE;

	opawams->ep_context = ep;

	wc = qed_iwawp_tcp_offwoad(p_hwfn, ep);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x) EP(0x%x) wc = %d\n",
		   ipawams->qp->icid, ep->tcp_cid, wc);

	if (wc) {
		qed_iwawp_destwoy_ep(p_hwfn, ep, twue);
		goto eww;
	}

	wetuwn wc;
eww:
	qed_iwawp_cid_cweaned(p_hwfn, cid);

	wetuwn wc;
}

static stwuct qed_iwawp_ep *qed_iwawp_get_fwee_ep(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iwawp_ep *ep = NUWW;
	int wc;

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	if (wist_empty(&p_hwfn->p_wdma_info->iwawp.ep_fwee_wist)) {
		DP_EWW(p_hwfn, "Ep wist is empty\n");
		goto out;
	}

	ep = wist_fiwst_entwy(&p_hwfn->p_wdma_info->iwawp.ep_fwee_wist,
			      stwuct qed_iwawp_ep, wist_entwy);

	/* in some cases we couwd have faiwed awwocating a tcp cid when added
	 * fwom accept / faiwuwe... wetwy now..this is not the common case.
	 */
	if (ep->tcp_cid == QED_IWAWP_INVAWID_TCP_CID) {
		wc = qed_iwawp_awwoc_tcp_cid(p_hwfn, &ep->tcp_cid);

		/* if we faiw we couwd wook fow anothew entwy with a vawid
		 * tcp_cid, but since we don't expect to weach this anyway
		 * it's not wowth the handwing
		 */
		if (wc) {
			ep->tcp_cid = QED_IWAWP_INVAWID_TCP_CID;
			ep = NUWW;
			goto out;
		}
	}

	wist_dew(&ep->wist_entwy);

out:
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wetuwn ep;
}

#define QED_IWAWP_MAX_CID_CWEAN_TIME  100
#define QED_IWAWP_MAX_NO_PWOGWESS_CNT 5

/* This function waits fow aww the bits of a bmap to be cweawed, as wong as
 * thewe is pwogwess ( i.e. the numbew of bits weft to be cweawed decweases )
 * the function continues.
 */
static int
qed_iwawp_wait_cid_map_cweawed(stwuct qed_hwfn *p_hwfn, stwuct qed_bmap *bmap)
{
	int pwev_weight = 0;
	int wait_count = 0;
	int weight = 0;

	weight = bitmap_weight(bmap->bitmap, bmap->max_count);
	pwev_weight = weight;

	whiwe (weight) {
		/* If the HW device is duwing wecovewy, aww wesouwces awe
		 * immediatewy weset without weceiving a pew-cid indication
		 * fwom HW. In this case we don't expect the cid_map to be
		 * cweawed.
		 */
		if (p_hwfn->cdev->wecov_in_pwog)
			wetuwn 0;

		msweep(QED_IWAWP_MAX_CID_CWEAN_TIME);

		weight = bitmap_weight(bmap->bitmap, bmap->max_count);

		if (pwev_weight == weight) {
			wait_count++;
		} ewse {
			pwev_weight = weight;
			wait_count = 0;
		}

		if (wait_count > QED_IWAWP_MAX_NO_PWOGWESS_CNT) {
			DP_NOTICE(p_hwfn,
				  "%s bitmap wait timed out (%d cids pending)\n",
				  bmap->name, weight);
			wetuwn -EBUSY;
		}
	}
	wetuwn 0;
}

static int qed_iwawp_wait_fow_aww_cids(stwuct qed_hwfn *p_hwfn)
{
	int wc;
	int i;

	wc = qed_iwawp_wait_cid_map_cweawed(p_hwfn,
					    &p_hwfn->p_wdma_info->tcp_cid_map);
	if (wc)
		wetuwn wc;

	/* Now fwee the tcp cids fwom the main cid map */
	fow (i = 0; i < QED_IWAWP_PWEAWWOC_CNT; i++)
		qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->cid_map, i);

	/* Now wait fow aww cids to be compweted */
	wetuwn qed_iwawp_wait_cid_map_cweawed(p_hwfn,
					      &p_hwfn->p_wdma_info->cid_map);
}

static void qed_iwawp_fwee_pweawwoc_ep(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iwawp_ep *ep;

	whiwe (!wist_empty(&p_hwfn->p_wdma_info->iwawp.ep_fwee_wist)) {
		spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

		ep = wist_fiwst_entwy(&p_hwfn->p_wdma_info->iwawp.ep_fwee_wist,
				      stwuct qed_iwawp_ep, wist_entwy);

		if (!ep) {
			spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
			bweak;
		}
		wist_dew(&ep->wist_entwy);

		spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

		if (ep->tcp_cid != QED_IWAWP_INVAWID_TCP_CID)
			qed_iwawp_cid_cweaned(p_hwfn, ep->tcp_cid);

		qed_iwawp_destwoy_ep(p_hwfn, ep, fawse);
	}
}

static int qed_iwawp_pweawwoc_ep(stwuct qed_hwfn *p_hwfn, boow init)
{
	stwuct qed_iwawp_ep *ep;
	int wc = 0;
	int count;
	u32 cid;
	int i;

	count = init ? QED_IWAWP_PWEAWWOC_CNT : 1;
	fow (i = 0; i < count; i++) {
		wc = qed_iwawp_cweate_ep(p_hwfn, &ep);
		if (wc)
			wetuwn wc;

		/* Duwing initiawization we awwocate fwom the main poow,
		 * aftewwawds we awwocate onwy fwom the tcp_cid.
		 */
		if (init) {
			wc = qed_iwawp_awwoc_cid(p_hwfn, &cid);
			if (wc)
				goto eww;
			qed_iwawp_set_tcp_cid(p_hwfn, cid);
		} ewse {
			/* We don't cawe about the wetuwn code, it's ok if
			 * tcp_cid wemains invawid...in this case we'ww
			 * defew awwocation
			 */
			qed_iwawp_awwoc_tcp_cid(p_hwfn, &cid);
		}

		ep->tcp_cid = cid;

		spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
		wist_add_taiw(&ep->wist_entwy,
			      &p_hwfn->p_wdma_info->iwawp.ep_fwee_wist);
		spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	}

	wetuwn wc;

eww:
	qed_iwawp_destwoy_ep(p_hwfn, ep, fawse);

	wetuwn wc;
}

int qed_iwawp_awwoc(stwuct qed_hwfn *p_hwfn)
{
	int wc;

	/* Awwocate bitmap fow tcp cid. These awe used by passive side
	 * to ensuwe it can awwocate a tcp cid duwing dpc that was
	 * pwe-acquiwed and doesn't wequiwe dynamic awwocation of iwt
	 */
	wc = qed_wdma_bmap_awwoc(p_hwfn, &p_hwfn->p_wdma_info->tcp_cid_map,
				 QED_IWAWP_PWEAWWOC_CNT, "TCP_CID");
	if (wc) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Faiwed to awwocate tcp cid, wc = %d\n", wc);
		wetuwn wc;
	}

	INIT_WIST_HEAD(&p_hwfn->p_wdma_info->iwawp.ep_fwee_wist);
	spin_wock_init(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	wc = qed_iwawp_pweawwoc_ep(p_hwfn, twue);
	if (wc)
		wetuwn wc;

	wetuwn qed_ooo_awwoc(p_hwfn);
}

void qed_iwawp_wesc_fwee(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;

	qed_ooo_fwee(p_hwfn);
	qed_wdma_bmap_fwee(p_hwfn, &p_hwfn->p_wdma_info->tcp_cid_map, 1);
	kfwee(iwawp_info->mpa_bufs);
	kfwee(iwawp_info->pawtiaw_fpdus);
	kfwee(iwawp_info->mpa_intewmediate_buf);
}

int qed_iwawp_accept(void *wdma_cxt, stwuct qed_iwawp_accept_in *ipawams)
{
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_iwawp_ep *ep;
	u8 mpa_data_size = 0;
	int wc;

	ep = ipawams->ep_context;
	if (!ep) {
		DP_EWW(p_hwfn, "Ep Context weceive in accept is NUWW\n");
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x) EP(0x%x)\n",
		   ipawams->qp->icid, ep->tcp_cid);

	if ((ipawams->owd > QED_IWAWP_OWD_DEFAUWT) ||
	    (ipawams->iwd > QED_IWAWP_IWD_DEFAUWT)) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "QP(0x%x) EP(0x%x) EWWOW: Invawid owd(0x%x)/iwd(0x%x)\n",
			   ipawams->qp->icid,
			   ep->tcp_cid, ipawams->owd, ipawams->owd);
		wetuwn -EINVAW;
	}

	qed_iwawp_pweawwoc_ep(p_hwfn, fawse);

	ep->cb_context = ipawams->cb_context;
	ep->qp = ipawams->qp;
	ep->qp->ep = ep;

	if (ep->mpa_wev == MPA_NEGOTIATION_TYPE_ENHANCED) {
		/* Negotiate owd/iwd: if uppewwayew wequested owd wawgew than
		 * iwd advewtised by wemote, we need to decwease ouw owd
		 */
		if (ipawams->owd > ep->cm_info.iwd)
			ipawams->owd = ep->cm_info.iwd;

		if ((ep->wtw_type & MPA_WTW_TYPE_ZEWO_WEAD) &&
		    (ipawams->iwd == 0))
			ipawams->iwd = 1;
	}

	/* Update cm_info owd/iwd to be negotiated vawues */
	ep->cm_info.owd = ipawams->owd;
	ep->cm_info.iwd = ipawams->iwd;

	qed_iwawp_mpa_v2_set_pwivate(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.pwivate_data = ep->ep_buffew_viwt->out_pdata;
	ep->cm_info.pwivate_data_wen = ipawams->pwivate_data_wen +
				       mpa_data_size;

	memcpy((u8 *)ep->ep_buffew_viwt->out_pdata + mpa_data_size,
	       ipawams->pwivate_data, ipawams->pwivate_data_wen);

	wc = qed_iwawp_mpa_offwoad(p_hwfn, ep);
	if (wc)
		qed_iwawp_modify_qp(p_hwfn,
				    ipawams->qp, QED_IWAWP_QP_STATE_EWWOW, 1);

	wetuwn wc;
}

int qed_iwawp_weject(void *wdma_cxt, stwuct qed_iwawp_weject_in *ipawams)
{
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_iwawp_ep *ep;
	u8 mpa_data_size = 0;

	ep = ipawams->ep_context;
	if (!ep) {
		DP_EWW(p_hwfn, "Ep Context weceive in weject is NUWW\n");
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "EP(0x%x)\n", ep->tcp_cid);

	ep->cb_context = ipawams->cb_context;
	ep->qp = NUWW;

	qed_iwawp_mpa_v2_set_pwivate(p_hwfn, ep, &mpa_data_size);

	ep->cm_info.pwivate_data = ep->ep_buffew_viwt->out_pdata;
	ep->cm_info.pwivate_data_wen = ipawams->pwivate_data_wen +
				       mpa_data_size;

	memcpy((u8 *)ep->ep_buffew_viwt->out_pdata + mpa_data_size,
	       ipawams->pwivate_data, ipawams->pwivate_data_wen);

	wetuwn qed_iwawp_mpa_offwoad(p_hwfn, ep);
}

static void
qed_iwawp_pwint_cm_info(stwuct qed_hwfn *p_hwfn,
			stwuct qed_iwawp_cm_info *cm_info)
{
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "ip_vewsion = %d\n",
		   cm_info->ip_vewsion);

	if (cm_info->ip_vewsion == QED_TCP_IPV4)
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "wemote_ip %pI4h:%x, wocaw_ip %pI4h:%x vwan=%x\n",
			   cm_info->wemote_ip, cm_info->wemote_powt,
			   cm_info->wocaw_ip, cm_info->wocaw_powt,
			   cm_info->vwan);
	ewse
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "wemote_ip %pI6:%x, wocaw_ip %pI6:%x vwan=%x\n",
			   cm_info->wemote_ip, cm_info->wemote_powt,
			   cm_info->wocaw_ip, cm_info->wocaw_powt,
			   cm_info->vwan);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "pwivate_data_wen = %x owd = %d, iwd = %d\n",
		   cm_info->pwivate_data_wen, cm_info->owd, cm_info->iwd);
}

static int
qed_iwawp_ww2_post_wx(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_iwawp_ww2_buff *buf, u8 handwe)
{
	int wc;

	wc = qed_ww2_post_wx_buffew(p_hwfn, handwe, buf->data_phys_addw,
				    (u16)buf->buff_size, buf, 1);
	if (wc) {
		DP_NOTICE(p_hwfn,
			  "Faiwed to wepost wx buffew to ww2 wc = %d, handwe=%d\n",
			  wc, handwe);
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, buf->buff_size,
				  buf->data, buf->data_phys_addw);
		kfwee(buf);
	}

	wetuwn wc;
}

static boow
qed_iwawp_ep_exists(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_cm_info *cm_info)
{
	stwuct qed_iwawp_ep *ep = NUWW;
	boow found = fawse;

	wist_fow_each_entwy(ep,
			    &p_hwfn->p_wdma_info->iwawp.ep_wist,
			    wist_entwy) {
		if ((ep->cm_info.wocaw_powt == cm_info->wocaw_powt) &&
		    (ep->cm_info.wemote_powt == cm_info->wemote_powt) &&
		    (ep->cm_info.vwan == cm_info->vwan) &&
		    !memcmp(&ep->cm_info.wocaw_ip, cm_info->wocaw_ip,
			    sizeof(cm_info->wocaw_ip)) &&
		    !memcmp(&ep->cm_info.wemote_ip, cm_info->wemote_ip,
			    sizeof(cm_info->wemote_ip))) {
			found = twue;
			bweak;
		}
	}

	if (found) {
		DP_NOTICE(p_hwfn,
			  "SYN weceived on active connection - dwopping\n");
		qed_iwawp_pwint_cm_info(p_hwfn, cm_info);

		wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct qed_iwawp_wistenew *
qed_iwawp_get_wistenew(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_iwawp_cm_info *cm_info)
{
	stwuct qed_iwawp_wistenew *wistenew = NUWW;
	static const u32 ip_zewo[4] = { 0, 0, 0, 0 };
	boow found = fawse;

	wist_fow_each_entwy(wistenew,
			    &p_hwfn->p_wdma_info->iwawp.wisten_wist,
			    wist_entwy) {
		if (wistenew->powt == cm_info->wocaw_powt) {
			if (!memcmp(wistenew->ip_addw,
				    ip_zewo, sizeof(ip_zewo))) {
				found = twue;
				bweak;
			}

			if (!memcmp(wistenew->ip_addw,
				    cm_info->wocaw_ip,
				    sizeof(cm_info->wocaw_ip)) &&
			    (wistenew->vwan == cm_info->vwan)) {
				found = twue;
				bweak;
			}
		}
	}

	if (found) {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wistenew found = %p\n",
			   wistenew);
		wetuwn wistenew;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wistenew not found\n");
	wetuwn NUWW;
}

static int
qed_iwawp_pawse_wx_pkt(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_iwawp_cm_info *cm_info,
		       void *buf,
		       u8 *wemote_mac_addw,
		       u8 *wocaw_mac_addw,
		       int *paywoad_wen, int *tcp_stawt_offset)
{
	stwuct vwan_ethhdw *vethh;
	boow vwan_vawid = fawse;
	stwuct ipv6hdw *ip6h;
	stwuct ethhdw *ethh;
	stwuct tcphdw *tcph;
	stwuct iphdw *iph;
	int eth_hwen;
	int ip_hwen;
	int eth_type;
	int i;

	ethh = buf;
	eth_type = ntohs(ethh->h_pwoto);
	if (eth_type == ETH_P_8021Q) {
		vwan_vawid = twue;
		vethh = (stwuct vwan_ethhdw *)ethh;
		cm_info->vwan = ntohs(vethh->h_vwan_TCI) & VWAN_VID_MASK;
		eth_type = ntohs(vethh->h_vwan_encapsuwated_pwoto);
	}

	eth_hwen = ETH_HWEN + (vwan_vawid ? sizeof(u32) : 0);

	if (!ethew_addw_equaw(ethh->h_dest,
			      p_hwfn->p_wdma_info->iwawp.mac_addw)) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "Got unexpected mac %pM instead of %pM\n",
			   ethh->h_dest, p_hwfn->p_wdma_info->iwawp.mac_addw);
		wetuwn -EINVAW;
	}

	ethew_addw_copy(wemote_mac_addw, ethh->h_souwce);
	ethew_addw_copy(wocaw_mac_addw, ethh->h_dest);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "eth_type =%d souwce mac: %pM\n",
		   eth_type, ethh->h_souwce);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "eth_hwen=%d destination mac: %pM\n",
		   eth_hwen, ethh->h_dest);

	iph = (stwuct iphdw *)((u8 *)(ethh) + eth_hwen);

	if (eth_type == ETH_P_IP) {
		if (iph->pwotocow != IPPWOTO_TCP) {
			DP_NOTICE(p_hwfn,
				  "Unexpected ip pwotocow on ww2 %x\n",
				  iph->pwotocow);
			wetuwn -EINVAW;
		}

		cm_info->wocaw_ip[0] = ntohw(iph->daddw);
		cm_info->wemote_ip[0] = ntohw(iph->saddw);
		cm_info->ip_vewsion = QED_TCP_IPV4;

		ip_hwen = (iph->ihw) * sizeof(u32);
		*paywoad_wen = ntohs(iph->tot_wen) - ip_hwen;
	} ewse if (eth_type == ETH_P_IPV6) {
		ip6h = (stwuct ipv6hdw *)iph;

		if (ip6h->nexthdw != IPPWOTO_TCP) {
			DP_NOTICE(p_hwfn,
				  "Unexpected ip pwotocow on ww2 %x\n",
				  iph->pwotocow);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < 4; i++) {
			cm_info->wocaw_ip[i] =
			    ntohw(ip6h->daddw.in6_u.u6_addw32[i]);
			cm_info->wemote_ip[i] =
			    ntohw(ip6h->saddw.in6_u.u6_addw32[i]);
		}
		cm_info->ip_vewsion = QED_TCP_IPV6;

		ip_hwen = sizeof(*ip6h);
		*paywoad_wen = ntohs(ip6h->paywoad_wen);
	} ewse {
		DP_NOTICE(p_hwfn, "Unexpected ethewtype on ww2 %x\n", eth_type);
		wetuwn -EINVAW;
	}

	tcph = (stwuct tcphdw *)((u8 *)iph + ip_hwen);

	if (!tcph->syn) {
		DP_NOTICE(p_hwfn,
			  "Onwy SYN type packet expected on this ww2 conn, iph->ihw=%d souwce=%d dest=%d\n",
			  iph->ihw, tcph->souwce, tcph->dest);
		wetuwn -EINVAW;
	}

	cm_info->wocaw_powt = ntohs(tcph->dest);
	cm_info->wemote_powt = ntohs(tcph->souwce);

	qed_iwawp_pwint_cm_info(p_hwfn, cm_info);

	*tcp_stawt_offset = eth_hwen + ip_hwen;

	wetuwn 0;
}

static stwuct qed_iwawp_fpdu *qed_iwawp_get_cuww_fpdu(stwuct qed_hwfn *p_hwfn,
						      u16 cid)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	stwuct qed_iwawp_fpdu *pawtiaw_fpdu;
	u32 idx;

	idx = cid - qed_cxt_get_pwoto_cid_stawt(p_hwfn, PWOTOCOWID_IWAWP);
	if (idx >= iwawp_info->max_num_pawtiaw_fpdus) {
		DP_EWW(p_hwfn, "Invawid cid %x max_num_pawtiaw_fpdus=%x\n", cid,
		       iwawp_info->max_num_pawtiaw_fpdus);
		wetuwn NUWW;
	}

	pawtiaw_fpdu = &iwawp_info->pawtiaw_fpdus[idx];

	wetuwn pawtiaw_fpdu;
}

enum qed_iwawp_mpa_pkt_type {
	QED_IWAWP_MPA_PKT_PACKED,
	QED_IWAWP_MPA_PKT_PAWTIAW,
	QED_IWAWP_MPA_PKT_UNAWIGNED
};

#define QED_IWAWP_INVAWID_FPDU_WENGTH 0xffff
#define QED_IWAWP_MPA_FPDU_WENGTH_SIZE (2)
#define QED_IWAWP_MPA_CWC32_DIGEST_SIZE (4)

/* Pad to muwtipwe of 4 */
#define QED_IWAWP_PDU_DATA_WEN_WITH_PAD(data_wen) AWIGN(data_wen, 4)
#define QED_IWAWP_FPDU_WEN_WITH_PAD(_mpa_wen)				   \
	(QED_IWAWP_PDU_DATA_WEN_WITH_PAD((_mpa_wen) +			   \
					 QED_IWAWP_MPA_FPDU_WENGTH_SIZE) + \
					 QED_IWAWP_MPA_CWC32_DIGEST_SIZE)

/* fpdu can be fwagmented ovew maximum 3 bds: headew, pawtiaw mpa, unawigned */
#define QED_IWAWP_MAX_BDS_PEW_FPDU 3

static const chaw * const pkt_type_stw[] = {
	"QED_IWAWP_MPA_PKT_PACKED",
	"QED_IWAWP_MPA_PKT_PAWTIAW",
	"QED_IWAWP_MPA_PKT_UNAWIGNED"
};

static int
qed_iwawp_wecycwe_pkt(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_iwawp_fpdu *fpdu,
		      stwuct qed_iwawp_ww2_buff *buf);

static enum qed_iwawp_mpa_pkt_type
qed_iwawp_mpa_cwassify(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_iwawp_fpdu *fpdu,
		       u16 tcp_paywoad_wen, u8 *mpa_data)
{
	enum qed_iwawp_mpa_pkt_type pkt_type;
	u16 mpa_wen;

	if (fpdu->incompwete_bytes) {
		pkt_type = QED_IWAWP_MPA_PKT_UNAWIGNED;
		goto out;
	}

	/* speciaw case of one byte wemaining...
	 * wowew byte wiww be wead next packet
	 */
	if (tcp_paywoad_wen == 1) {
		fpdu->fpdu_wength = *mpa_data << BITS_PEW_BYTE;
		pkt_type = QED_IWAWP_MPA_PKT_PAWTIAW;
		goto out;
	}

	mpa_wen = ntohs(*(__fowce __be16 *)mpa_data);
	fpdu->fpdu_wength = QED_IWAWP_FPDU_WEN_WITH_PAD(mpa_wen);

	if (fpdu->fpdu_wength <= tcp_paywoad_wen)
		pkt_type = QED_IWAWP_MPA_PKT_PACKED;
	ewse
		pkt_type = QED_IWAWP_MPA_PKT_PAWTIAW;

out:
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "MPA_AWIGN: %s: fpdu_wength=0x%x tcp_paywoad_wen:0x%x\n",
		   pkt_type_stw[pkt_type], fpdu->fpdu_wength, tcp_paywoad_wen);

	wetuwn pkt_type;
}

static void
qed_iwawp_init_fpdu(stwuct qed_iwawp_ww2_buff *buf,
		    stwuct qed_iwawp_fpdu *fpdu,
		    stwuct unawigned_opaque_data *pkt_data,
		    u16 tcp_paywoad_size, u8 pwacement_offset)
{
	u16 fiwst_mpa_offset = we16_to_cpu(pkt_data->fiwst_mpa_offset);

	fpdu->mpa_buf = buf;
	fpdu->pkt_hdw = buf->data_phys_addw + pwacement_offset;
	fpdu->pkt_hdw_size = pkt_data->tcp_paywoad_offset;
	fpdu->mpa_fwag = buf->data_phys_addw + fiwst_mpa_offset;
	fpdu->mpa_fwag_viwt = (u8 *)(buf->data) + fiwst_mpa_offset;

	if (tcp_paywoad_size == 1)
		fpdu->incompwete_bytes = QED_IWAWP_INVAWID_FPDU_WENGTH;
	ewse if (tcp_paywoad_size < fpdu->fpdu_wength)
		fpdu->incompwete_bytes = fpdu->fpdu_wength - tcp_paywoad_size;
	ewse
		fpdu->incompwete_bytes = 0;	/* compwete fpdu */

	fpdu->mpa_fwag_wen = fpdu->fpdu_wength - fpdu->incompwete_bytes;
}

static int
qed_iwawp_cp_pkt(stwuct qed_hwfn *p_hwfn,
		 stwuct qed_iwawp_fpdu *fpdu,
		 stwuct unawigned_opaque_data *pkt_data,
		 stwuct qed_iwawp_ww2_buff *buf, u16 tcp_paywoad_size)
{
	u16 fiwst_mpa_offset = we16_to_cpu(pkt_data->fiwst_mpa_offset);
	u8 *tmp_buf = p_hwfn->p_wdma_info->iwawp.mpa_intewmediate_buf;
	int wc;

	/* need to copy the data fwom the pawtiaw packet stowed in fpdu
	 * to the new buf, fow this we awso need to move the data cuwwentwy
	 * pwaced on the buf. The assumption is that the buffew is big enough
	 * since fpdu_wength <= mss, we use an intewmediate buffew since
	 * we may need to copy the new data to an ovewwapping wocation
	 */
	if ((fpdu->mpa_fwag_wen + tcp_paywoad_size) > (u16)buf->buff_size) {
		DP_EWW(p_hwfn,
		       "MPA AWIGN: Unexpected: buffew is not wawge enough fow spwit fpdu buff_size = %d mpa_fwag_wen = %d, tcp_paywoad_size = %d, incompwete_bytes = %d\n",
		       buf->buff_size, fpdu->mpa_fwag_wen,
		       tcp_paywoad_size, fpdu->incompwete_bytes);
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "MPA AWIGN Copying fpdu: [%p, %d] [%p, %d]\n",
		   fpdu->mpa_fwag_viwt, fpdu->mpa_fwag_wen,
		   (u8 *)(buf->data) + fiwst_mpa_offset, tcp_paywoad_size);

	memcpy(tmp_buf, fpdu->mpa_fwag_viwt, fpdu->mpa_fwag_wen);
	memcpy(tmp_buf + fpdu->mpa_fwag_wen,
	       (u8 *)(buf->data) + fiwst_mpa_offset, tcp_paywoad_size);

	wc = qed_iwawp_wecycwe_pkt(p_hwfn, fpdu, fpdu->mpa_buf);
	if (wc)
		wetuwn wc;

	/* If we managed to post the buffew copy the data to the new buffew
	 * o/w this wiww occuw in the next wound...
	 */
	memcpy((u8 *)(buf->data), tmp_buf,
	       fpdu->mpa_fwag_wen + tcp_paywoad_size);

	fpdu->mpa_buf = buf;
	/* fpdu->pkt_hdw wemains as is */
	/* fpdu->mpa_fwag is ovewwidden with new buf */
	fpdu->mpa_fwag = buf->data_phys_addw;
	fpdu->mpa_fwag_viwt = buf->data;
	fpdu->mpa_fwag_wen += tcp_paywoad_size;

	fpdu->incompwete_bytes -= tcp_paywoad_size;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "MPA AWIGN: spwit fpdu buff_size = %d mpa_fwag_wen = %d, tcp_paywoad_size = %d, incompwete_bytes = %d\n",
		   buf->buff_size, fpdu->mpa_fwag_wen, tcp_paywoad_size,
		   fpdu->incompwete_bytes);

	wetuwn 0;
}

static void
qed_iwawp_update_fpdu_wength(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_iwawp_fpdu *fpdu, u8 *mpa_data)
{
	u16 mpa_wen;

	/* Update incompwete packets if needed */
	if (fpdu->incompwete_bytes == QED_IWAWP_INVAWID_FPDU_WENGTH) {
		/* Missing wowew byte is now avaiwabwe */
		mpa_wen = fpdu->fpdu_wength | *mpa_data;
		fpdu->fpdu_wength = QED_IWAWP_FPDU_WEN_WITH_PAD(mpa_wen);
		/* one byte of hdw */
		fpdu->mpa_fwag_wen = 1;
		fpdu->incompwete_bytes = fpdu->fpdu_wength - 1;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "MPA_AWIGN: Pawtiaw headew mpa_wen=%x fpdu_wength=%x incompwete_bytes=%x\n",
			   mpa_wen, fpdu->fpdu_wength, fpdu->incompwete_bytes);
	}
}

#define QED_IWAWP_IS_WIGHT_EDGE(_cuww_pkt) \
	(GET_FIEWD((_cuww_pkt)->fwags,	   \
		   UNAWIGNED_OPAQUE_DATA_PKT_WEACHED_WIN_WIGHT_EDGE))

/* This function is used to wecycwe a buffew using the ww2 dwop option. It
 * uses the mechanism to ensuwe that aww buffews posted to tx befowe this one
 * wewe compweted. The buffew sent hewe wiww be sent as a cookie in the tx
 * compwetion function and can then be weposted to wx chain when done. The fwow
 * that wequiwes this is the fwow whewe a FPDU spwits ovew mowe than 3 tcp
 * segments. In this case the dwivew needs to we-post a wx buffew instead of
 * the one weceived, but dwivew can't simpwy wepost a buffew it copied fwom
 * as thewe is a case whewe the buffew was owiginawwy a packed FPDU, and is
 * pawtiawwy posted to FW. Dwivew needs to ensuwe FW is done with it.
 */
static int
qed_iwawp_wecycwe_pkt(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_iwawp_fpdu *fpdu,
		      stwuct qed_iwawp_ww2_buff *buf)
{
	stwuct qed_ww2_tx_pkt_info tx_pkt;
	u8 ww2_handwe;
	int wc;

	memset(&tx_pkt, 0, sizeof(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = QED_WW2_TX_DEST_DWOP;
	tx_pkt.w4_hdw_offset_w = fpdu->pkt_hdw_size >> 2;
	tx_pkt.fiwst_fwag = fpdu->pkt_hdw;
	tx_pkt.fiwst_fwag_wen = fpdu->pkt_hdw_size;
	buf->piggy_buf = NUWW;
	tx_pkt.cookie = buf;

	ww2_handwe = p_hwfn->p_wdma_info->iwawp.ww2_mpa_handwe;

	wc = qed_ww2_pwepawe_tx_packet(p_hwfn, ww2_handwe, &tx_pkt, twue);
	if (wc)
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Can't dwop packet wc=%d\n", wc);

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "MPA_AWIGN: send dwop tx packet [%wx, 0x%x], buf=%p, wc=%d\n",
		   (unsigned wong int)tx_pkt.fiwst_fwag,
		   tx_pkt.fiwst_fwag_wen, buf, wc);

	wetuwn wc;
}

static int
qed_iwawp_win_wight_edge(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_fpdu *fpdu)
{
	stwuct qed_ww2_tx_pkt_info tx_pkt;
	u8 ww2_handwe;
	int wc;

	memset(&tx_pkt, 0, sizeof(tx_pkt));
	tx_pkt.num_of_bds = 1;
	tx_pkt.tx_dest = QED_WW2_TX_DEST_WB;
	tx_pkt.w4_hdw_offset_w = fpdu->pkt_hdw_size >> 2;

	tx_pkt.fiwst_fwag = fpdu->pkt_hdw;
	tx_pkt.fiwst_fwag_wen = fpdu->pkt_hdw_size;
	tx_pkt.enabwe_ip_cksum = twue;
	tx_pkt.enabwe_w4_cksum = twue;
	tx_pkt.cawc_ip_wen = twue;
	/* vwan ovewwoad with enum iwawp_ww2_tx_queues */
	tx_pkt.vwan = IWAWP_WW2_AWIGNED_WIGHT_TWIMMED_TX_QUEUE;

	ww2_handwe = p_hwfn->p_wdma_info->iwawp.ww2_mpa_handwe;

	wc = qed_ww2_pwepawe_tx_packet(p_hwfn, ww2_handwe, &tx_pkt, twue);
	if (wc)
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Can't send wight edge wc=%d\n", wc);
	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "MPA_AWIGN: Sent wight edge FPDU num_bds=%d [%wx, 0x%x], wc=%d\n",
		   tx_pkt.num_of_bds,
		   (unsigned wong int)tx_pkt.fiwst_fwag,
		   tx_pkt.fiwst_fwag_wen, wc);

	wetuwn wc;
}

static int
qed_iwawp_send_fpdu(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_iwawp_fpdu *fpdu,
		    stwuct unawigned_opaque_data *cuww_pkt,
		    stwuct qed_iwawp_ww2_buff *buf,
		    u16 tcp_paywoad_size, enum qed_iwawp_mpa_pkt_type pkt_type)
{
	stwuct qed_ww2_tx_pkt_info tx_pkt;
	u16 fiwst_mpa_offset;
	u8 ww2_handwe;
	int wc;

	memset(&tx_pkt, 0, sizeof(tx_pkt));

	/* An unawigned packet means it's spwit ovew two tcp segments. So the
	 * compwete packet wequiwes 3 bds, one fow the headew, one fow the
	 * pawt of the fpdu of the fiwst tcp segment, and the wast fwagment
	 * wiww point to the wemaindew of the fpdu. A packed pdu, wequiwes onwy
	 * two bds, one fow the headew and one fow the data.
	 */
	tx_pkt.num_of_bds = (pkt_type == QED_IWAWP_MPA_PKT_UNAWIGNED) ? 3 : 2;
	tx_pkt.tx_dest = QED_WW2_TX_DEST_WB;
	tx_pkt.w4_hdw_offset_w = fpdu->pkt_hdw_size >> 2; /* offset in wowds */

	/* Send the mpa_buf onwy with the wast fpdu (in case of packed) */
	if (pkt_type == QED_IWAWP_MPA_PKT_UNAWIGNED ||
	    tcp_paywoad_size <= fpdu->fpdu_wength)
		tx_pkt.cookie = fpdu->mpa_buf;

	tx_pkt.fiwst_fwag = fpdu->pkt_hdw;
	tx_pkt.fiwst_fwag_wen = fpdu->pkt_hdw_size;
	tx_pkt.enabwe_ip_cksum = twue;
	tx_pkt.enabwe_w4_cksum = twue;
	tx_pkt.cawc_ip_wen = twue;
	/* vwan ovewwoad with enum iwawp_ww2_tx_queues */
	tx_pkt.vwan = IWAWP_WW2_AWIGNED_TX_QUEUE;

	/* speciaw case of unawigned packet and not packed, need to send
	 * both buffews as cookie to wewease.
	 */
	if (tcp_paywoad_size == fpdu->incompwete_bytes)
		fpdu->mpa_buf->piggy_buf = buf;

	ww2_handwe = p_hwfn->p_wdma_info->iwawp.ww2_mpa_handwe;

	/* Set fiwst fwagment to headew */
	wc = qed_ww2_pwepawe_tx_packet(p_hwfn, ww2_handwe, &tx_pkt, twue);
	if (wc)
		goto out;

	/* Set second fwagment to fiwst pawt of packet */
	wc = qed_ww2_set_fwagment_of_tx_packet(p_hwfn, ww2_handwe,
					       fpdu->mpa_fwag,
					       fpdu->mpa_fwag_wen);
	if (wc)
		goto out;

	if (!fpdu->incompwete_bytes)
		goto out;

	fiwst_mpa_offset = we16_to_cpu(cuww_pkt->fiwst_mpa_offset);

	/* Set thiwd fwagment to second pawt of the packet */
	wc = qed_ww2_set_fwagment_of_tx_packet(p_hwfn,
					       ww2_handwe,
					       buf->data_phys_addw +
					       fiwst_mpa_offset,
					       fpdu->incompwete_bytes);
out:
	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "MPA_AWIGN: Sent FPDU num_bds=%d fiwst_fwag_wen=%x, mpa_fwag_wen=0x%x, incompwete_bytes:0x%x wc=%d\n",
		   tx_pkt.num_of_bds,
		   tx_pkt.fiwst_fwag_wen,
		   fpdu->mpa_fwag_wen,
		   fpdu->incompwete_bytes, wc);

	wetuwn wc;
}

static void
qed_iwawp_mpa_get_data(stwuct qed_hwfn *p_hwfn,
		       stwuct unawigned_opaque_data *cuww_pkt,
		       u32 opaque_data0, u32 opaque_data1)
{
	u64 opaque_data;

	opaque_data = HIWO_64(cpu_to_we32(opaque_data1),
			      cpu_to_we32(opaque_data0));
	*cuww_pkt = *((stwuct unawigned_opaque_data *)&opaque_data);

	we16_add_cpu(&cuww_pkt->fiwst_mpa_offset,
		     cuww_pkt->tcp_paywoad_offset);
}

/* This function is cawwed when an unawigned ow incompwete MPA packet awwives
 * dwivew needs to awign the packet, pewhaps using pwevious data and send
 * it down to FW once it is awigned.
 */
static int
qed_iwawp_pwocess_mpa_pkt(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_iwawp_ww2_mpa_buf *mpa_buf)
{
	stwuct unawigned_opaque_data *cuww_pkt = &mpa_buf->data;
	stwuct qed_iwawp_ww2_buff *buf = mpa_buf->ww2_buf;
	enum qed_iwawp_mpa_pkt_type pkt_type;
	stwuct qed_iwawp_fpdu *fpdu;
	u16 cid, fiwst_mpa_offset;
	int wc = -EINVAW;
	u8 *mpa_data;

	cid = we32_to_cpu(cuww_pkt->cid);

	fpdu = qed_iwawp_get_cuww_fpdu(p_hwfn, (u16)cid);
	if (!fpdu) { /* something cowwupt with cid, post wx back */
		DP_EWW(p_hwfn, "Invawid cid, dwop and post back to wx cid=%x\n",
		       cid);
		goto eww;
	}

	do {
		fiwst_mpa_offset = we16_to_cpu(cuww_pkt->fiwst_mpa_offset);
		mpa_data = ((u8 *)(buf->data) + fiwst_mpa_offset);

		pkt_type = qed_iwawp_mpa_cwassify(p_hwfn, fpdu,
						  mpa_buf->tcp_paywoad_wen,
						  mpa_data);

		switch (pkt_type) {
		case QED_IWAWP_MPA_PKT_PAWTIAW:
			qed_iwawp_init_fpdu(buf, fpdu,
					    cuww_pkt,
					    mpa_buf->tcp_paywoad_wen,
					    mpa_buf->pwacement_offset);

			if (!QED_IWAWP_IS_WIGHT_EDGE(cuww_pkt)) {
				mpa_buf->tcp_paywoad_wen = 0;
				bweak;
			}

			wc = qed_iwawp_win_wight_edge(p_hwfn, fpdu);

			if (wc) {
				DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
					   "Can't send FPDU:weset wc=%d\n", wc);
				memset(fpdu, 0, sizeof(*fpdu));
				bweak;
			}

			mpa_buf->tcp_paywoad_wen = 0;
			bweak;
		case QED_IWAWP_MPA_PKT_PACKED:
			qed_iwawp_init_fpdu(buf, fpdu,
					    cuww_pkt,
					    mpa_buf->tcp_paywoad_wen,
					    mpa_buf->pwacement_offset);

			wc = qed_iwawp_send_fpdu(p_hwfn, fpdu, cuww_pkt, buf,
						 mpa_buf->tcp_paywoad_wen,
						 pkt_type);
			if (wc) {
				DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
					   "Can't send FPDU:weset wc=%d\n", wc);
				memset(fpdu, 0, sizeof(*fpdu));
				bweak;
			}

			mpa_buf->tcp_paywoad_wen -= fpdu->fpdu_wength;
			we16_add_cpu(&cuww_pkt->fiwst_mpa_offset,
				     fpdu->fpdu_wength);
			bweak;
		case QED_IWAWP_MPA_PKT_UNAWIGNED:
			qed_iwawp_update_fpdu_wength(p_hwfn, fpdu, mpa_data);
			if (mpa_buf->tcp_paywoad_wen < fpdu->incompwete_bytes) {
				/* speciaw handwing of fpdu spwit ovew mowe
				 * than 2 segments
				 */
				if (QED_IWAWP_IS_WIGHT_EDGE(cuww_pkt)) {
					wc = qed_iwawp_win_wight_edge(p_hwfn,
								      fpdu);
					/* packet wiww be we-pwocessed watew */
					if (wc)
						wetuwn wc;
				}

				wc = qed_iwawp_cp_pkt(p_hwfn, fpdu, cuww_pkt,
						      buf,
						      mpa_buf->tcp_paywoad_wen);
				if (wc) /* packet wiww be we-pwocessed watew */
					wetuwn wc;

				mpa_buf->tcp_paywoad_wen = 0;
				bweak;
			}

			wc = qed_iwawp_send_fpdu(p_hwfn, fpdu, cuww_pkt, buf,
						 mpa_buf->tcp_paywoad_wen,
						 pkt_type);
			if (wc) {
				DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
					   "Can't send FPDU:deway wc=%d\n", wc);
				/* don't weset fpdu -> we need it fow next
				 * cwassify
				 */
				bweak;
			}

			mpa_buf->tcp_paywoad_wen -= fpdu->incompwete_bytes;
			we16_add_cpu(&cuww_pkt->fiwst_mpa_offset,
				     fpdu->incompwete_bytes);

			/* The fwamed PDU was sent - no mowe incompwete bytes */
			fpdu->incompwete_bytes = 0;
			bweak;
		}
	} whiwe (mpa_buf->tcp_paywoad_wen && !wc);

	wetuwn wc;

eww:
	qed_iwawp_ww2_post_wx(p_hwfn,
			      buf,
			      p_hwfn->p_wdma_info->iwawp.ww2_mpa_handwe);
	wetuwn wc;
}

static void qed_iwawp_pwocess_pending_pkts(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	stwuct qed_iwawp_ww2_mpa_buf *mpa_buf = NUWW;
	int wc;

	whiwe (!wist_empty(&iwawp_info->mpa_buf_pending_wist)) {
		mpa_buf = wist_fiwst_entwy(&iwawp_info->mpa_buf_pending_wist,
					   stwuct qed_iwawp_ww2_mpa_buf,
					   wist_entwy);

		wc = qed_iwawp_pwocess_mpa_pkt(p_hwfn, mpa_buf);

		/* busy means bweak and continue pwocessing watew, don't
		 * wemove the buf fwom the pending wist.
		 */
		if (wc == -EBUSY)
			bweak;

		wist_move_taiw(&mpa_buf->wist_entwy,
			       &iwawp_info->mpa_buf_wist);

		if (wc) {	/* diffewent ewwow, don't continue */
			DP_NOTICE(p_hwfn, "pwocess pkts faiwed wc=%d\n", wc);
			bweak;
		}
	}
}

static void
qed_iwawp_ww2_comp_mpa_pkt(void *cxt, stwuct qed_ww2_comp_wx_data *data)
{
	stwuct qed_iwawp_ww2_mpa_buf *mpa_buf;
	stwuct qed_iwawp_info *iwawp_info;
	stwuct qed_hwfn *p_hwfn = cxt;
	u16 fiwst_mpa_offset;

	iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	mpa_buf = wist_fiwst_entwy(&iwawp_info->mpa_buf_wist,
				   stwuct qed_iwawp_ww2_mpa_buf, wist_entwy);
	if (!mpa_buf) {
		DP_EWW(p_hwfn, "No fwee mpa buf\n");
		goto eww;
	}

	wist_dew(&mpa_buf->wist_entwy);
	qed_iwawp_mpa_get_data(p_hwfn, &mpa_buf->data,
			       data->opaque_data_0, data->opaque_data_1);

	fiwst_mpa_offset = we16_to_cpu(mpa_buf->data.fiwst_mpa_offset);

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "WW2 MPA CompWx paywoad_wen:0x%x\tfiwst_mpa_offset:0x%x\ttcp_paywoad_offset:0x%x\tfwags:0x%x\tcid:0x%x\n",
		   data->wength.packet_wength, fiwst_mpa_offset,
		   mpa_buf->data.tcp_paywoad_offset, mpa_buf->data.fwags,
		   mpa_buf->data.cid);

	mpa_buf->ww2_buf = data->cookie;
	mpa_buf->tcp_paywoad_wen = data->wength.packet_wength -
				   fiwst_mpa_offset;

	fiwst_mpa_offset += data->u.pwacement_offset;
	mpa_buf->data.fiwst_mpa_offset = cpu_to_we16(fiwst_mpa_offset);
	mpa_buf->pwacement_offset = data->u.pwacement_offset;

	wist_add_taiw(&mpa_buf->wist_entwy, &iwawp_info->mpa_buf_pending_wist);

	qed_iwawp_pwocess_pending_pkts(p_hwfn);
	wetuwn;
eww:
	qed_iwawp_ww2_post_wx(p_hwfn, data->cookie,
			      iwawp_info->ww2_mpa_handwe);
}

static void
qed_iwawp_ww2_comp_syn_pkt(void *cxt, stwuct qed_ww2_comp_wx_data *data)
{
	stwuct qed_iwawp_ww2_buff *buf = data->cookie;
	stwuct qed_iwawp_wistenew *wistenew;
	stwuct qed_ww2_tx_pkt_info tx_pkt;
	stwuct qed_iwawp_cm_info cm_info;
	stwuct qed_hwfn *p_hwfn = cxt;
	u8 wemote_mac_addw[ETH_AWEN];
	u8 wocaw_mac_addw[ETH_AWEN];
	stwuct qed_iwawp_ep *ep;
	int tcp_stawt_offset;
	u8 ww2_syn_handwe;
	int paywoad_wen;
	u32 hdw_size;
	int wc;

	memset(&cm_info, 0, sizeof(cm_info));
	ww2_syn_handwe = p_hwfn->p_wdma_info->iwawp.ww2_syn_handwe;

	/* Check if packet was weceived with ewwows... */
	if (data->eww_fwags) {
		DP_NOTICE(p_hwfn, "Ewwow weceived on SYN packet: 0x%x\n",
			  data->eww_fwags);
		goto eww;
	}

	if (GET_FIEWD(data->pawse_fwags,
		      PAWSING_AND_EWW_FWAGS_W4CHKSMWASCAWCUWATED) &&
	    GET_FIEWD(data->pawse_fwags, PAWSING_AND_EWW_FWAGS_W4CHKSMEWWOW)) {
		DP_NOTICE(p_hwfn, "Syn packet weceived with checksum ewwow\n");
		goto eww;
	}

	wc = qed_iwawp_pawse_wx_pkt(p_hwfn, &cm_info, (u8 *)(buf->data) +
				    data->u.pwacement_offset, wemote_mac_addw,
				    wocaw_mac_addw, &paywoad_wen,
				    &tcp_stawt_offset);
	if (wc)
		goto eww;

	/* Check if thewe is a wistenew fow this 4-tupwe+vwan */
	wistenew = qed_iwawp_get_wistenew(p_hwfn, &cm_info);
	if (!wistenew) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "SYN weceived on tupwe not wistened on pawse_fwags=%d packet wen=%d\n",
			   data->pawse_fwags, data->wength.packet_wength);

		memset(&tx_pkt, 0, sizeof(tx_pkt));
		tx_pkt.num_of_bds = 1;
		tx_pkt.w4_hdw_offset_w = (data->wength.packet_wength) >> 2;
		tx_pkt.tx_dest = QED_WW2_TX_DEST_WB;
		tx_pkt.fiwst_fwag = buf->data_phys_addw +
				    data->u.pwacement_offset;
		tx_pkt.fiwst_fwag_wen = data->wength.packet_wength;
		tx_pkt.cookie = buf;

		wc = qed_ww2_pwepawe_tx_packet(p_hwfn, ww2_syn_handwe,
					       &tx_pkt, twue);

		if (wc) {
			DP_NOTICE(p_hwfn,
				  "Can't post SYN back to chip wc=%d\n", wc);
			goto eww;
		}
		wetuwn;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Weceived syn on wistening powt\n");
	/* Thewe may be an open ep on this connection if this is a syn
	 * wetwasnmit... need to make suwe thewe isn't...
	 */
	if (qed_iwawp_ep_exists(p_hwfn, &cm_info))
		goto eww;

	ep = qed_iwawp_get_fwee_ep(p_hwfn);
	if (!ep)
		goto eww;

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wist_add_taiw(&ep->wist_entwy, &p_hwfn->p_wdma_info->iwawp.ep_wist);
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	ethew_addw_copy(ep->wemote_mac_addw, wemote_mac_addw);
	ethew_addw_copy(ep->wocaw_mac_addw, wocaw_mac_addw);

	memcpy(&ep->cm_info, &cm_info, sizeof(ep->cm_info));

	hdw_size = ((cm_info.ip_vewsion == QED_TCP_IPV4) ? 40 : 60);
	ep->mss = p_hwfn->p_wdma_info->iwawp.max_mtu - hdw_size;
	ep->mss = min_t(u16, QED_IWAWP_MAX_FW_MSS, ep->mss);

	ep->event_cb = wistenew->event_cb;
	ep->cb_context = wistenew->cb_context;
	ep->connect_mode = TCP_CONNECT_PASSIVE;

	ep->syn = buf;
	ep->syn_ip_paywoad_wength = (u16)paywoad_wen;
	ep->syn_phy_addw = buf->data_phys_addw + data->u.pwacement_offset +
			   tcp_stawt_offset;

	wc = qed_iwawp_tcp_offwoad(p_hwfn, ep);
	if (wc) {
		qed_iwawp_wetuwn_ep(p_hwfn, ep);
		goto eww;
	}

	wetuwn;
eww:
	qed_iwawp_ww2_post_wx(p_hwfn, buf, ww2_syn_handwe);
}

static void qed_iwawp_ww2_wew_wx_pkt(void *cxt, u8 connection_handwe,
				     void *cookie, dma_addw_t wx_buf_addw,
				     boow b_wast_packet)
{
	stwuct qed_iwawp_ww2_buff *buffew = cookie;
	stwuct qed_hwfn *p_hwfn = cxt;

	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, buffew->buff_size,
			  buffew->data, buffew->data_phys_addw);
	kfwee(buffew);
}

static void qed_iwawp_ww2_comp_tx_pkt(void *cxt, u8 connection_handwe,
				      void *cookie, dma_addw_t fiwst_fwag_addw,
				      boow b_wast_fwagment, boow b_wast_packet)
{
	stwuct qed_iwawp_ww2_buff *buffew = cookie;
	stwuct qed_iwawp_ww2_buff *piggy;
	stwuct qed_hwfn *p_hwfn = cxt;

	if (!buffew)		/* can happen in packed mpa unawigned... */
		wetuwn;

	/* this was owiginawwy an wx packet, post it back */
	piggy = buffew->piggy_buf;
	if (piggy) {
		buffew->piggy_buf = NUWW;
		qed_iwawp_ww2_post_wx(p_hwfn, piggy, connection_handwe);
	}

	qed_iwawp_ww2_post_wx(p_hwfn, buffew, connection_handwe);

	if (connection_handwe == p_hwfn->p_wdma_info->iwawp.ww2_mpa_handwe)
		qed_iwawp_pwocess_pending_pkts(p_hwfn);

	wetuwn;
}

static void qed_iwawp_ww2_wew_tx_pkt(void *cxt, u8 connection_handwe,
				     void *cookie, dma_addw_t fiwst_fwag_addw,
				     boow b_wast_fwagment, boow b_wast_packet)
{
	stwuct qed_iwawp_ww2_buff *buffew = cookie;
	stwuct qed_hwfn *p_hwfn = cxt;

	if (!buffew)
		wetuwn;

	if (buffew->piggy_buf) {
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  buffew->piggy_buf->buff_size,
				  buffew->piggy_buf->data,
				  buffew->piggy_buf->data_phys_addw);

		kfwee(buffew->piggy_buf);
	}

	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, buffew->buff_size,
			  buffew->data, buffew->data_phys_addw);

	kfwee(buffew);
}

/* The onwy swowpath fow iwawp ww2 is unawign fwush. When this compwetion
 * is weceived, need to weset the FPDU.
 */
static void
qed_iwawp_ww2_swowpath(void *cxt,
		       u8 connection_handwe,
		       u32 opaque_data_0, u32 opaque_data_1)
{
	stwuct unawigned_opaque_data unawign_data;
	stwuct qed_hwfn *p_hwfn = cxt;
	stwuct qed_iwawp_fpdu *fpdu;
	u32 cid;

	qed_iwawp_mpa_get_data(p_hwfn, &unawign_data,
			       opaque_data_0, opaque_data_1);

	cid = we32_to_cpu(unawign_data.cid);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "(0x%x) Fwush fpdu\n", cid);

	fpdu = qed_iwawp_get_cuww_fpdu(p_hwfn, (u16)cid);
	if (fpdu)
		memset(fpdu, 0, sizeof(*fpdu));
}

static int qed_iwawp_ww2_stop(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_iwawp_info *iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	int wc = 0;

	if (iwawp_info->ww2_syn_handwe != QED_IWAWP_HANDWE_INVAW) {
		wc = qed_ww2_tewminate_connection(p_hwfn,
						  iwawp_info->ww2_syn_handwe);
		if (wc)
			DP_INFO(p_hwfn, "Faiwed to tewminate syn connection\n");

		qed_ww2_wewease_connection(p_hwfn, iwawp_info->ww2_syn_handwe);
		iwawp_info->ww2_syn_handwe = QED_IWAWP_HANDWE_INVAW;
	}

	if (iwawp_info->ww2_ooo_handwe != QED_IWAWP_HANDWE_INVAW) {
		wc = qed_ww2_tewminate_connection(p_hwfn,
						  iwawp_info->ww2_ooo_handwe);
		if (wc)
			DP_INFO(p_hwfn, "Faiwed to tewminate ooo connection\n");

		qed_ww2_wewease_connection(p_hwfn, iwawp_info->ww2_ooo_handwe);
		iwawp_info->ww2_ooo_handwe = QED_IWAWP_HANDWE_INVAW;
	}

	if (iwawp_info->ww2_mpa_handwe != QED_IWAWP_HANDWE_INVAW) {
		wc = qed_ww2_tewminate_connection(p_hwfn,
						  iwawp_info->ww2_mpa_handwe);
		if (wc)
			DP_INFO(p_hwfn, "Faiwed to tewminate mpa connection\n");

		qed_ww2_wewease_connection(p_hwfn, iwawp_info->ww2_mpa_handwe);
		iwawp_info->ww2_mpa_handwe = QED_IWAWP_HANDWE_INVAW;
	}

	qed_wwh_wemove_mac_fiwtew(p_hwfn->cdev, 0,
				  p_hwfn->p_wdma_info->iwawp.mac_addw);

	wetuwn wc;
}

static int
qed_iwawp_ww2_awwoc_buffews(stwuct qed_hwfn *p_hwfn,
			    int num_wx_bufs, int buff_size, u8 ww2_handwe)
{
	stwuct qed_iwawp_ww2_buff *buffew;
	int wc = 0;
	int i;

	fow (i = 0; i < num_wx_bufs; i++) {
		buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
		if (!buffew) {
			wc = -ENOMEM;
			bweak;
		}

		buffew->data = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
						  buff_size,
						  &buffew->data_phys_addw,
						  GFP_KEWNEW);
		if (!buffew->data) {
			kfwee(buffew);
			wc = -ENOMEM;
			bweak;
		}

		buffew->buff_size = buff_size;
		wc = qed_iwawp_ww2_post_wx(p_hwfn, buffew, ww2_handwe);
		if (wc)
			/* buffews wiww be deawwocated by qed_ww2 */
			bweak;
	}
	wetuwn wc;
}

#define QED_IWAWP_MAX_BUF_SIZE(mtu)				     \
	AWIGN((mtu) + ETH_HWEN + 2 * VWAN_HWEN + 2 + ETH_CACHE_WINE_SIZE, \
		ETH_CACHE_WINE_SIZE)

static int
qed_iwawp_ww2_stawt(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_wdma_stawt_in_pawams *pawams,
		    u32 wcv_wnd_size)
{
	stwuct qed_iwawp_info *iwawp_info;
	stwuct qed_ww2_acquiwe_data data;
	stwuct qed_ww2_cbs cbs;
	u32 buff_size;
	u16 n_ooo_bufs;
	int wc = 0;
	int i;

	iwawp_info = &p_hwfn->p_wdma_info->iwawp;
	iwawp_info->ww2_syn_handwe = QED_IWAWP_HANDWE_INVAW;
	iwawp_info->ww2_ooo_handwe = QED_IWAWP_HANDWE_INVAW;
	iwawp_info->ww2_mpa_handwe = QED_IWAWP_HANDWE_INVAW;

	iwawp_info->max_mtu = pawams->max_mtu;

	ethew_addw_copy(p_hwfn->p_wdma_info->iwawp.mac_addw, pawams->mac_addw);

	wc = qed_wwh_add_mac_fiwtew(p_hwfn->cdev, 0, pawams->mac_addw);
	if (wc)
		wetuwn wc;

	/* Stawt SYN connection */
	cbs.wx_comp_cb = qed_iwawp_ww2_comp_syn_pkt;
	cbs.wx_wewease_cb = qed_iwawp_ww2_wew_wx_pkt;
	cbs.tx_comp_cb = qed_iwawp_ww2_comp_tx_pkt;
	cbs.tx_wewease_cb = qed_iwawp_ww2_wew_tx_pkt;
	cbs.swowpath_cb = NUWW;
	cbs.cookie = p_hwfn;

	memset(&data, 0, sizeof(data));
	data.input.conn_type = QED_WW2_TYPE_IWAWP;
	/* SYN wiww use ctx based queues */
	data.input.wx_conn_type = QED_WW2_WX_TYPE_CTX;
	data.input.mtu = pawams->max_mtu;
	data.input.wx_num_desc = QED_IWAWP_WW2_SYN_WX_SIZE;
	data.input.tx_num_desc = QED_IWAWP_WW2_SYN_TX_SIZE;
	data.input.tx_max_bds_pew_packet = 1;	/* wiww nevew be fwagmented */
	data.input.tx_tc = PKT_WB_TC;
	data.input.tx_dest = QED_WW2_TX_DEST_WB;
	data.p_connection_handwe = &iwawp_info->ww2_syn_handwe;
	data.cbs = &cbs;

	wc = qed_ww2_acquiwe_connection(p_hwfn, &data);
	if (wc) {
		DP_NOTICE(p_hwfn, "Faiwed to acquiwe WW2 connection\n");
		qed_wwh_wemove_mac_fiwtew(p_hwfn->cdev, 0, pawams->mac_addw);
		wetuwn wc;
	}

	wc = qed_ww2_estabwish_connection(p_hwfn, iwawp_info->ww2_syn_handwe);
	if (wc) {
		DP_NOTICE(p_hwfn, "Faiwed to estabwish WW2 connection\n");
		goto eww;
	}

	buff_size = QED_IWAWP_MAX_BUF_SIZE(pawams->max_mtu);
	wc = qed_iwawp_ww2_awwoc_buffews(p_hwfn,
					 QED_IWAWP_WW2_SYN_WX_SIZE,
					 buff_size,
					 iwawp_info->ww2_syn_handwe);
	if (wc)
		goto eww;

	/* Stawt OOO connection */
	data.input.conn_type = QED_WW2_TYPE_OOO;
	/* OOO/unawigned wiww use wegacy ww2 queues (wam based) */
	data.input.wx_conn_type = QED_WW2_WX_TYPE_WEGACY;
	data.input.mtu = pawams->max_mtu;

	n_ooo_bufs = (QED_IWAWP_MAX_OOO * wcv_wnd_size) /
		     iwawp_info->max_mtu;
	n_ooo_bufs = min_t(u32, n_ooo_bufs, QED_IWAWP_WW2_OOO_MAX_WX_SIZE);

	data.input.wx_num_desc = n_ooo_bufs;
	data.input.wx_num_ooo_buffews = n_ooo_bufs;

	data.input.tx_max_bds_pew_packet = 1;	/* wiww nevew be fwagmented */
	data.input.tx_num_desc = QED_IWAWP_WW2_OOO_DEF_TX_SIZE;
	data.p_connection_handwe = &iwawp_info->ww2_ooo_handwe;

	wc = qed_ww2_acquiwe_connection(p_hwfn, &data);
	if (wc)
		goto eww;

	wc = qed_ww2_estabwish_connection(p_hwfn, iwawp_info->ww2_ooo_handwe);
	if (wc)
		goto eww;

	/* Stawt Unawigned MPA connection */
	cbs.wx_comp_cb = qed_iwawp_ww2_comp_mpa_pkt;
	cbs.swowpath_cb = qed_iwawp_ww2_swowpath;

	memset(&data, 0, sizeof(data));
	data.input.conn_type = QED_WW2_TYPE_IWAWP;
	data.input.mtu = pawams->max_mtu;
	/* FW wequiwes that once a packet awwives OOO, it must have at
	 * weast 2 wx buffews avaiwabwe on the unawigned connection
	 * fow handwing the case that it is a pawtiaw fpdu.
	 */
	data.input.wx_num_desc = n_ooo_bufs * 2;
	data.input.tx_num_desc = data.input.wx_num_desc;
	data.input.tx_max_bds_pew_packet = QED_IWAWP_MAX_BDS_PEW_FPDU;
	data.input.tx_tc = PKT_WB_TC;
	data.input.tx_dest = QED_WW2_TX_DEST_WB;
	data.p_connection_handwe = &iwawp_info->ww2_mpa_handwe;
	data.input.secondawy_queue = twue;
	data.cbs = &cbs;

	wc = qed_ww2_acquiwe_connection(p_hwfn, &data);
	if (wc)
		goto eww;

	wc = qed_ww2_estabwish_connection(p_hwfn, iwawp_info->ww2_mpa_handwe);
	if (wc)
		goto eww;

	wc = qed_iwawp_ww2_awwoc_buffews(p_hwfn,
					 data.input.wx_num_desc,
					 buff_size,
					 iwawp_info->ww2_mpa_handwe);
	if (wc)
		goto eww;

	iwawp_info->pawtiaw_fpdus = kcawwoc((u16)p_hwfn->p_wdma_info->num_qps,
					    sizeof(*iwawp_info->pawtiaw_fpdus),
					    GFP_KEWNEW);
	if (!iwawp_info->pawtiaw_fpdus) {
		wc = -ENOMEM;
		goto eww;
	}

	iwawp_info->max_num_pawtiaw_fpdus = (u16)p_hwfn->p_wdma_info->num_qps;

	iwawp_info->mpa_intewmediate_buf = kzawwoc(buff_size, GFP_KEWNEW);
	if (!iwawp_info->mpa_intewmediate_buf) {
		wc = -ENOMEM;
		goto eww;
	}

	/* The mpa_bufs awway sewves fow pending WX packets weceived on the
	 * mpa ww2 that don't have pwace on the tx wing and wequiwe watew
	 * pwocessing. We can't faiw on awwocation of such a stwuct thewefowe
	 * we awwocate enough to take cawe of aww wx packets
	 */
	iwawp_info->mpa_bufs = kcawwoc(data.input.wx_num_desc,
				       sizeof(*iwawp_info->mpa_bufs),
				       GFP_KEWNEW);
	if (!iwawp_info->mpa_bufs) {
		wc = -ENOMEM;
		goto eww;
	}

	INIT_WIST_HEAD(&iwawp_info->mpa_buf_pending_wist);
	INIT_WIST_HEAD(&iwawp_info->mpa_buf_wist);
	fow (i = 0; i < data.input.wx_num_desc; i++)
		wist_add_taiw(&iwawp_info->mpa_bufs[i].wist_entwy,
			      &iwawp_info->mpa_buf_wist);
	wetuwn wc;
eww:
	qed_iwawp_ww2_stop(p_hwfn);

	wetuwn wc;
}

static stwuct {
	u32 two_powts;
	u32 fouw_powts;
} qed_iwawp_wcv_wnd_size[MAX_CHIP_IDS] = {
	{QED_IWAWP_WCV_WND_SIZE_DEF_BB_2P, QED_IWAWP_WCV_WND_SIZE_DEF_BB_4P},
	{QED_IWAWP_WCV_WND_SIZE_DEF_AH_2P, QED_IWAWP_WCV_WND_SIZE_DEF_AH_4P}
};

int qed_iwawp_setup(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_wdma_stawt_in_pawams *pawams)
{
	stwuct qed_dev *cdev = p_hwfn->cdev;
	stwuct qed_iwawp_info *iwawp_info;
	enum chip_ids chip_id;
	u32 wcv_wnd_size;

	iwawp_info = &p_hwfn->p_wdma_info->iwawp;

	iwawp_info->tcp_fwags = QED_IWAWP_TS_EN;

	chip_id = QED_IS_BB(cdev) ? CHIP_BB : CHIP_K2;
	wcv_wnd_size = (qed_device_num_powts(cdev) == 4) ?
		qed_iwawp_wcv_wnd_size[chip_id].fouw_powts :
		qed_iwawp_wcv_wnd_size[chip_id].two_powts;

	/* vawue 0 is used fow iwog2(QED_IWAWP_WCV_WND_SIZE_MIN) */
	iwawp_info->wcv_wnd_scawe = iwog2(wcv_wnd_size) -
	    iwog2(QED_IWAWP_WCV_WND_SIZE_MIN);
	iwawp_info->wcv_wnd_size = wcv_wnd_size >> iwawp_info->wcv_wnd_scawe;
	iwawp_info->cwc_needed = QED_IWAWP_PAWAM_CWC_NEEDED;
	iwawp_info->mpa_wev = MPA_NEGOTIATION_TYPE_ENHANCED;

	iwawp_info->peew2peew = QED_IWAWP_PAWAM_P2P;

	iwawp_info->wtw_type =  MPA_WTW_TYPE_ZEWO_SEND |
				MPA_WTW_TYPE_ZEWO_WWITE |
				MPA_WTW_TYPE_ZEWO_WEAD;

	spin_wock_init(&p_hwfn->p_wdma_info->iwawp.qp_wock);
	INIT_WIST_HEAD(&p_hwfn->p_wdma_info->iwawp.ep_wist);
	INIT_WIST_HEAD(&p_hwfn->p_wdma_info->iwawp.wisten_wist);

	qed_spq_wegistew_async_cb(p_hwfn, PWOTOCOWID_IWAWP,
				  qed_iwawp_async_event);
	qed_ooo_setup(p_hwfn);

	wetuwn qed_iwawp_ww2_stawt(p_hwfn, pawams, wcv_wnd_size);
}

int qed_iwawp_stop(stwuct qed_hwfn *p_hwfn)
{
	int wc;

	qed_iwawp_fwee_pweawwoc_ep(p_hwfn);
	wc = qed_iwawp_wait_fow_aww_cids(p_hwfn);
	if (wc)
		wetuwn wc;

	wetuwn qed_iwawp_ww2_stop(p_hwfn);
}

static void qed_iwawp_qp_in_ewwow(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_iwawp_ep *ep,
				  u8 fw_wetuwn_code)
{
	stwuct qed_iwawp_cm_event_pawams pawams;

	qed_iwawp_modify_qp(p_hwfn, ep->qp, QED_IWAWP_QP_STATE_EWWOW, twue);

	pawams.event = QED_IWAWP_EVENT_CWOSE;
	pawams.ep_context = ep;
	pawams.cm_info = &ep->cm_info;
	pawams.status = (fw_wetuwn_code == IWAWP_QP_IN_EWWOW_GOOD_CWOSE) ?
			 0 : -ECONNWESET;

	/* paiwed with WEAD_ONCE in destwoy_qp */
	smp_stowe_wewease(&ep->state, QED_IWAWP_EP_CWOSED);

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wist_dew(&ep->wist_entwy);
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	ep->event_cb(ep->cb_context, &pawams);
}

static void qed_iwawp_exception_weceived(stwuct qed_hwfn *p_hwfn,
					 stwuct qed_iwawp_ep *ep,
					 int fw_wet_code)
{
	stwuct qed_iwawp_cm_event_pawams pawams;
	boow event_cb = fawse;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "EP(0x%x) fw_wet_code=%d\n",
		   ep->cid, fw_wet_code);

	switch (fw_wet_code) {
	case IWAWP_EXCEPTION_DETECTED_WWP_CWOSED:
		pawams.status = 0;
		pawams.event = QED_IWAWP_EVENT_DISCONNECT;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WWP_WESET:
		pawams.status = -ECONNWESET;
		pawams.event = QED_IWAWP_EVENT_DISCONNECT;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WQ_EMPTY:
		pawams.event = QED_IWAWP_EVENT_WQ_EMPTY;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_IWQ_FUWW:
		pawams.event = QED_IWAWP_EVENT_IWQ_FUWW;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WWP_TIMEOUT:
		pawams.event = QED_IWAWP_EVENT_WWP_TIMEOUT;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WEMOTE_PWOTECTION_EWWOW:
		pawams.event = QED_IWAWP_EVENT_WEMOTE_PWOTECTION_EWWOW;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_CQ_OVEWFWOW:
		pawams.event = QED_IWAWP_EVENT_CQ_OVEWFWOW;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WOCAW_CATASTWOPHIC:
		pawams.event = QED_IWAWP_EVENT_QP_CATASTWOPHIC;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WOCAW_ACCESS_EWWOW:
		pawams.event = QED_IWAWP_EVENT_WOCAW_ACCESS_EWWOW;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_WEMOTE_OPEWATION_EWWOW:
		pawams.event = QED_IWAWP_EVENT_WEMOTE_OPEWATION_EWWOW;
		event_cb = twue;
		bweak;
	case IWAWP_EXCEPTION_DETECTED_TEWMINATE_WECEIVED:
		pawams.event = QED_IWAWP_EVENT_TEWMINATE_WECEIVED;
		event_cb = twue;
		bweak;
	defauwt:
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "Unhandwed exception weceived...fw_wet_code=%d\n",
			   fw_wet_code);
		bweak;
	}

	if (event_cb) {
		pawams.ep_context = ep;
		pawams.cm_info = &ep->cm_info;
		ep->event_cb(ep->cb_context, &pawams);
	}
}

static void
qed_iwawp_tcp_connect_unsuccessfuw(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_iwawp_ep *ep, u8 fw_wetuwn_code)
{
	stwuct qed_iwawp_cm_event_pawams pawams;

	memset(&pawams, 0, sizeof(pawams));
	pawams.event = QED_IWAWP_EVENT_ACTIVE_COMPWETE;
	pawams.ep_context = ep;
	pawams.cm_info = &ep->cm_info;
	/* paiwed with WEAD_ONCE in destwoy_qp */
	smp_stowe_wewease(&ep->state, QED_IWAWP_EP_CWOSED);

	switch (fw_wetuwn_code) {
	case IWAWP_CONN_EWWOW_TCP_CONNECT_INVAWID_PACKET:
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "%s(0x%x) TCP connect got invawid packet\n",
			   QED_IWAWP_CONNECT_MODE_STWING(ep), ep->tcp_cid);
		pawams.status = -ECONNWESET;
		bweak;
	case IWAWP_CONN_EWWOW_TCP_CONNECTION_WST:
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "%s(0x%x) TCP Connection Weset\n",
			   QED_IWAWP_CONNECT_MODE_STWING(ep), ep->tcp_cid);
		pawams.status = -ECONNWESET;
		bweak;
	case IWAWP_CONN_EWWOW_TCP_CONNECT_TIMEOUT:
		DP_NOTICE(p_hwfn, "%s(0x%x) TCP timeout\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->tcp_cid);
		pawams.status = -EBUSY;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_NOT_SUPPOWTED_VEW:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA not suppowted VEW\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->tcp_cid);
		pawams.status = -ECONNWEFUSED;
		bweak;
	case IWAWP_CONN_EWWOW_MPA_INVAWID_PACKET:
		DP_NOTICE(p_hwfn, "%s(0x%x) MPA Invawid Packet\n",
			  QED_IWAWP_CONNECT_MODE_STWING(ep), ep->tcp_cid);
		pawams.status = -ECONNWESET;
		bweak;
	defauwt:
		DP_EWW(p_hwfn,
		       "%s(0x%x) Unexpected wetuwn code tcp connect: %d\n",
		       QED_IWAWP_CONNECT_MODE_STWING(ep),
		       ep->tcp_cid, fw_wetuwn_code);
		pawams.status = -ECONNWESET;
		bweak;
	}

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		ep->tcp_cid = QED_IWAWP_INVAWID_TCP_CID;
		qed_iwawp_wetuwn_ep(p_hwfn, ep);
	} ewse {
		ep->event_cb(ep->cb_context, &pawams);
		spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
		wist_dew(&ep->wist_entwy);
		spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	}
}

static void
qed_iwawp_connect_compwete(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_iwawp_ep *ep, u8 fw_wetuwn_code)
{
	u8 ww2_syn_handwe = p_hwfn->p_wdma_info->iwawp.ww2_syn_handwe;

	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		/* Done with the SYN packet, post back to ww2 wx */
		qed_iwawp_ww2_post_wx(p_hwfn, ep->syn, ww2_syn_handwe);

		ep->syn = NUWW;

		/* If connect faiwed - uppew wayew doesn't know about it */
		if (fw_wetuwn_code == WDMA_WETUWN_OK)
			qed_iwawp_mpa_weceived(p_hwfn, ep);
		ewse
			qed_iwawp_tcp_connect_unsuccessfuw(p_hwfn, ep,
							   fw_wetuwn_code);
	} ewse {
		if (fw_wetuwn_code == WDMA_WETUWN_OK)
			qed_iwawp_mpa_offwoad(p_hwfn, ep);
		ewse
			qed_iwawp_tcp_connect_unsuccessfuw(p_hwfn, ep,
							   fw_wetuwn_code);
	}
}

static inwine boow
qed_iwawp_check_ep_ok(stwuct qed_hwfn *p_hwfn, stwuct qed_iwawp_ep *ep)
{
	if (!ep || (ep->sig != QED_EP_SIG)) {
		DP_EWW(p_hwfn, "EWWOW ON ASYNC ep=%p\n", ep);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int qed_iwawp_async_event(stwuct qed_hwfn *p_hwfn, u8 fw_event_code,
				 __we16 echo, union event_wing_data *data,
				 u8 fw_wetuwn_code)
{
	stwuct qed_wdma_events events = p_hwfn->p_wdma_info->events;
	stwuct wegpaiw *fw_handwe = &data->wdma_data.async_handwe;
	stwuct qed_iwawp_ep *ep = NUWW;
	u16 swq_offset;
	u16 swq_id;
	u16 cid;

	ep = (stwuct qed_iwawp_ep *)(uintptw_t)HIWO_64(fw_handwe->hi,
						       fw_handwe->wo);

	switch (fw_event_code) {
	case IWAWP_EVENT_TYPE_ASYNC_CONNECT_COMPWETE:
		/* Async compwetion aftew TCP 3-way handshake */
		if (!qed_iwawp_check_ep_ok(p_hwfn, ep))
			wetuwn -EINVAW;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "EP(0x%x) IWAWP_EVENT_TYPE_ASYNC_CONNECT_COMPWETE fw_wet_code=%d\n",
			   ep->tcp_cid, fw_wetuwn_code);
		qed_iwawp_connect_compwete(p_hwfn, ep, fw_wetuwn_code);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_EXCEPTION_DETECTED:
		if (!qed_iwawp_check_ep_ok(p_hwfn, ep))
			wetuwn -EINVAW;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "QP(0x%x) IWAWP_EVENT_TYPE_ASYNC_EXCEPTION_DETECTED fw_wet_code=%d\n",
			   ep->cid, fw_wetuwn_code);
		qed_iwawp_exception_weceived(p_hwfn, ep, fw_wetuwn_code);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_QP_IN_EWWOW_STATE:
		/* Async compwetion fow Cwose Connection wamwod */
		if (!qed_iwawp_check_ep_ok(p_hwfn, ep))
			wetuwn -EINVAW;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "QP(0x%x) IWAWP_EVENT_TYPE_ASYNC_QP_IN_EWWOW_STATE fw_wet_code=%d\n",
			   ep->cid, fw_wetuwn_code);
		qed_iwawp_qp_in_ewwow(p_hwfn, ep, fw_wetuwn_code);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_ENHANCED_MPA_WEPWY_AWWIVED:
		/* Async event fow active side onwy */
		if (!qed_iwawp_check_ep_ok(p_hwfn, ep))
			wetuwn -EINVAW;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "QP(0x%x) IWAWP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_MPA_WEPWY_AWWIVED fw_wet_code=%d\n",
			   ep->cid, fw_wetuwn_code);
		qed_iwawp_mpa_wepwy_awwived(p_hwfn, ep);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPWETE:
		if (!qed_iwawp_check_ep_ok(p_hwfn, ep))
			wetuwn -EINVAW;
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_WDMA,
			   "QP(0x%x) IWAWP_EVENT_TYPE_ASYNC_MPA_HANDSHAKE_COMPWETE fw_wet_code=%d\n",
			   ep->cid, fw_wetuwn_code);
		qed_iwawp_mpa_compwete(p_hwfn, ep, fw_wetuwn_code);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_CID_CWEANED:
		cid = (u16)we32_to_cpu(fw_handwe->wo);
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
			   "(0x%x)IWAWP_EVENT_TYPE_ASYNC_CID_CWEANED\n", cid);
		qed_iwawp_cid_cweaned(p_hwfn, cid);

		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_SWQ_EMPTY:
		DP_NOTICE(p_hwfn, "IWAWP_EVENT_TYPE_ASYNC_SWQ_EMPTY\n");
		swq_offset = p_hwfn->p_wdma_info->swq_id_offset;
		/* FW assigns vawue that is no gweatew than u16 */
		swq_id = ((u16)we32_to_cpu(fw_handwe->wo)) - swq_offset;
		events.affiwiated_event(events.context,
					QED_IWAWP_EVENT_SWQ_EMPTY,
					&swq_id);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_SWQ_WIMIT:
		DP_NOTICE(p_hwfn, "IWAWP_EVENT_TYPE_ASYNC_SWQ_WIMIT\n");
		swq_offset = p_hwfn->p_wdma_info->swq_id_offset;
		/* FW assigns vawue that is no gweatew than u16 */
		swq_id = ((u16)we32_to_cpu(fw_handwe->wo)) - swq_offset;
		events.affiwiated_event(events.context,
					QED_IWAWP_EVENT_SWQ_WIMIT,
					&swq_id);
		bweak;
	case IWAWP_EVENT_TYPE_ASYNC_CQ_OVEWFWOW:
		DP_NOTICE(p_hwfn, "IWAWP_EVENT_TYPE_ASYNC_CQ_OVEWFWOW\n");

		p_hwfn->p_wdma_info->events.affiwiated_event(
			p_hwfn->p_wdma_info->events.context,
			QED_IWAWP_EVENT_CQ_OVEWFWOW,
			(void *)fw_handwe);
		bweak;
	defauwt:
		DP_EWW(p_hwfn, "Weceived unexpected async iwawp event %d\n",
		       fw_event_code);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int
qed_iwawp_cweate_wisten(void *wdma_cxt,
			stwuct qed_iwawp_wisten_in *ipawams,
			stwuct qed_iwawp_wisten_out *opawams)
{
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_iwawp_wistenew *wistenew;

	wistenew = kzawwoc(sizeof(*wistenew), GFP_KEWNEW);
	if (!wistenew)
		wetuwn -ENOMEM;

	wistenew->ip_vewsion = ipawams->ip_vewsion;
	memcpy(wistenew->ip_addw, ipawams->ip_addw, sizeof(wistenew->ip_addw));
	wistenew->powt = ipawams->powt;
	wistenew->vwan = ipawams->vwan;

	wistenew->event_cb = ipawams->event_cb;
	wistenew->cb_context = ipawams->cb_context;
	wistenew->max_backwog = ipawams->max_backwog;
	opawams->handwe = wistenew;

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wist_add_taiw(&wistenew->wist_entwy,
		      &p_hwfn->p_wdma_info->iwawp.wisten_wist);
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_WDMA,
		   "cawwback=%p handwe=%p ip=%x:%x:%x:%x powt=0x%x vwan=0x%x\n",
		   wistenew->event_cb,
		   wistenew,
		   wistenew->ip_addw[0],
		   wistenew->ip_addw[1],
		   wistenew->ip_addw[2],
		   wistenew->ip_addw[3], wistenew->powt, wistenew->vwan);

	wetuwn 0;
}

int qed_iwawp_destwoy_wisten(void *wdma_cxt, void *handwe)
{
	stwuct qed_iwawp_wistenew *wistenew = handwe;
	stwuct qed_hwfn *p_hwfn = wdma_cxt;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "handwe=%p\n", handwe);

	spin_wock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);
	wist_dew(&wistenew->wist_entwy);
	spin_unwock_bh(&p_hwfn->p_wdma_info->iwawp.iw_wock);

	kfwee(wistenew);

	wetuwn 0;
}

int qed_iwawp_send_wtw(void *wdma_cxt, stwuct qed_iwawp_send_wtw_in *ipawams)
{
	stwuct qed_hwfn *p_hwfn = wdma_cxt;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	stwuct qed_iwawp_ep *ep;
	stwuct qed_wdma_qp *qp;
	int wc;

	ep = ipawams->ep_context;
	if (!ep) {
		DP_EWW(p_hwfn, "Ep Context weceive in send_wtw is NUWW\n");
		wetuwn -EINVAW;
	}

	qp = ep->qp;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "QP(0x%x) EP(0x%x)\n",
		   qp->icid, ep->tcp_cid);

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_CB;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 IWAWP_WAMWOD_CMD_ID_MPA_OFFWOAD_SEND_WTW,
				 PWOTOCOWID_IWAWP, &init_data);

	if (wc)
		wetuwn wc;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "wc = 0x%x\n", wc);

	wetuwn wc;
}

void
qed_iwawp_quewy_qp(stwuct qed_wdma_qp *qp,
		   stwuct qed_wdma_quewy_qp_out_pawams *out_pawams)
{
	out_pawams->state = qed_iwawp2woce_state(qp->iwawp_state);
}
