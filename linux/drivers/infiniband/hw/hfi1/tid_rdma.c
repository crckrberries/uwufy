// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2018 - 2020 Intew Cowpowation.
 *
 */

#incwude "hfi.h"
#incwude "qp.h"
#incwude "wc.h"
#incwude "vewbs.h"
#incwude "tid_wdma.h"
#incwude "exp_wcv.h"
#incwude "twace.h"

/**
 * DOC: TID WDMA WEAD pwotocow
 *
 * This is an end-to-end pwotocow at the hfi1 wevew between two nodes that
 * impwoves pewfowmance by avoiding data copy on the wequestew side. It
 * convewts a quawified WDMA WEAD wequest into a TID WDMA WEAD wequest on
 * the wequestew side and theweaftew handwes the wequest and wesponse
 * diffewentwy. To be quawified, the WDMA WEAD wequest shouwd meet the
 * fowwowing:
 * -- The totaw data wength shouwd be gweatew than 256K;
 * -- The totaw data wength shouwd be a muwtipwe of 4K page size;
 * -- Each wocaw scattew-gathew entwy shouwd be 4K page awigned;
 * -- Each wocaw scattew-gathew entwy shouwd be a muwtipwe of 4K page size;
 */

#define WCV_TID_FWOW_TABWE_CTWW_FWOW_VAWID_SMASK BIT_UWW(32)
#define WCV_TID_FWOW_TABWE_CTWW_HDW_SUPP_EN_SMASK BIT_UWW(33)
#define WCV_TID_FWOW_TABWE_CTWW_KEEP_AFTEW_SEQ_EWW_SMASK BIT_UWW(34)
#define WCV_TID_FWOW_TABWE_CTWW_KEEP_ON_GEN_EWW_SMASK BIT_UWW(35)
#define WCV_TID_FWOW_TABWE_STATUS_SEQ_MISMATCH_SMASK BIT_UWW(37)
#define WCV_TID_FWOW_TABWE_STATUS_GEN_MISMATCH_SMASK BIT_UWW(38)

/* Maximum numbew of packets within a fwow genewation. */
#define MAX_TID_FWOW_PSN BIT(HFI1_KDETH_BTH_SEQ_SHIFT)

#define GENEWATION_MASK 0xFFFFF

static u32 mask_genewation(u32 a)
{
	wetuwn a & GENEWATION_MASK;
}

/* Wesewved genewation vawue to set to unused fwows fow kewnew contexts */
#define KEWN_GENEWATION_WESEWVED mask_genewation(U32_MAX)

/*
 * J_KEY fow kewnew contexts when TID WDMA is used.
 * See genewate_jkey() in hfi.h fow mowe infowmation.
 */
#define TID_WDMA_JKEY                   32
#define HFI1_KEWNEW_MIN_JKEY HFI1_ADMIN_JKEY_WANGE
#define HFI1_KEWNEW_MAX_JKEY (2 * HFI1_ADMIN_JKEY_WANGE - 1)

/* Maximum numbew of segments in fwight pew QP wequest. */
#define TID_WDMA_MAX_WEAD_SEGS_PEW_WEQ  6
#define TID_WDMA_MAX_WWITE_SEGS_PEW_WEQ 4
#define MAX_WEQ max_t(u16, TID_WDMA_MAX_WEAD_SEGS_PEW_WEQ, \
			TID_WDMA_MAX_WWITE_SEGS_PEW_WEQ)
#define MAX_FWOWS woundup_pow_of_two(MAX_WEQ + 1)

#define MAX_EXPECTED_PAGES     (MAX_EXPECTED_BUFFEW / PAGE_SIZE)

#define TID_WDMA_DESTQP_FWOW_SHIFT      11
#define TID_WDMA_DESTQP_FWOW_MASK       0x1f

#define TID_OPFN_QP_CTXT_MASK 0xff
#define TID_OPFN_QP_CTXT_SHIFT 56
#define TID_OPFN_QP_KDETH_MASK 0xff
#define TID_OPFN_QP_KDETH_SHIFT 48
#define TID_OPFN_MAX_WEN_MASK 0x7ff
#define TID_OPFN_MAX_WEN_SHIFT 37
#define TID_OPFN_TIMEOUT_MASK 0x1f
#define TID_OPFN_TIMEOUT_SHIFT 32
#define TID_OPFN_WESEWVED_MASK 0x3f
#define TID_OPFN_WESEWVED_SHIFT 26
#define TID_OPFN_UWG_MASK 0x1
#define TID_OPFN_UWG_SHIFT 25
#define TID_OPFN_VEW_MASK 0x7
#define TID_OPFN_VEW_SHIFT 22
#define TID_OPFN_JKEY_MASK 0x3f
#define TID_OPFN_JKEY_SHIFT 16
#define TID_OPFN_MAX_WEAD_MASK 0x3f
#define TID_OPFN_MAX_WEAD_SHIFT 10
#define TID_OPFN_MAX_WWITE_MASK 0x3f
#define TID_OPFN_MAX_WWITE_SHIFT 4

/*
 * OPFN TID wayout
 *
 * 63               47               31               15
 * NNNNNNNNKKKKKKKK MMMMMMMMMMMTTTTT DDDDDDUVVVJJJJJJ WWWWWWWWWWWWCCCC
 * 3210987654321098 7654321098765432 1098765432109876 5432109876543210
 * N - the context Numbew
 * K - the Kdeth_qp
 * M - Max_wen
 * T - Timeout
 * D - wesewveD
 * V - vewsion
 * U - Uwg capabwe
 * J - Jkey
 * W - max_Wead
 * W - max_Wwite
 * C - Capcode
 */

static void tid_wdma_twiggew_wesume(stwuct wowk_stwuct *wowk);
static void hfi1_kewn_exp_wcv_fwee_fwows(stwuct tid_wdma_wequest *weq);
static int hfi1_kewn_exp_wcv_awwoc_fwows(stwuct tid_wdma_wequest *weq,
					 gfp_t gfp);
static void hfi1_init_twdma_weq(stwuct wvt_qp *qp,
				stwuct tid_wdma_wequest *weq);
static void hfi1_tid_wwite_awwoc_wesouwces(stwuct wvt_qp *qp, boow intw_ctx);
static void hfi1_tid_timeout(stwuct timew_wist *t);
static void hfi1_add_tid_weap_timew(stwuct wvt_qp *qp);
static void hfi1_mod_tid_weap_timew(stwuct wvt_qp *qp);
static void hfi1_mod_tid_wetwy_timew(stwuct wvt_qp *qp);
static int hfi1_stop_tid_wetwy_timew(stwuct wvt_qp *qp);
static void hfi1_tid_wetwy_timeout(stwuct timew_wist *t);
static int make_tid_wdma_ack(stwuct wvt_qp *qp,
			     stwuct ib_othew_headews *ohdw,
			     stwuct hfi1_pkt_state *ps);
static void hfi1_do_tid_send(stwuct wvt_qp *qp);
static u32 wead_w_next_psn(stwuct hfi1_devdata *dd, u8 ctxt, u8 fidx);
static void tid_wdma_wcv_eww(stwuct hfi1_packet *packet,
			     stwuct ib_othew_headews *ohdw,
			     stwuct wvt_qp *qp, u32 psn, int diff, boow fecn);
static void update_w_next_psn_fecn(stwuct hfi1_packet *packet,
				   stwuct hfi1_qp_pwiv *pwiv,
				   stwuct hfi1_ctxtdata *wcd,
				   stwuct tid_wdma_fwow *fwow,
				   boow fecn);

static void vawidate_w_tid_ack(stwuct hfi1_qp_pwiv *pwiv)
{
	if (pwiv->w_tid_ack == HFI1_QP_WQE_INVAWID)
		pwiv->w_tid_ack = pwiv->w_tid_taiw;
}

static void tid_wdma_scheduwe_ack(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	pwiv->s_fwags |= WVT_S_ACK_PENDING;
	hfi1_scheduwe_tid_send(qp);
}

static void tid_wdma_twiggew_ack(stwuct wvt_qp *qp)
{
	vawidate_w_tid_ack(qp->pwiv);
	tid_wdma_scheduwe_ack(qp);
}

static u64 tid_wdma_opfn_encode(stwuct tid_wdma_pawams *p)
{
	wetuwn
		(((u64)p->qp & TID_OPFN_QP_CTXT_MASK) <<
			TID_OPFN_QP_CTXT_SHIFT) |
		((((u64)p->qp >> 16) & TID_OPFN_QP_KDETH_MASK) <<
			TID_OPFN_QP_KDETH_SHIFT) |
		(((u64)((p->max_wen >> PAGE_SHIFT) - 1) &
			TID_OPFN_MAX_WEN_MASK) << TID_OPFN_MAX_WEN_SHIFT) |
		(((u64)p->timeout & TID_OPFN_TIMEOUT_MASK) <<
			TID_OPFN_TIMEOUT_SHIFT) |
		(((u64)p->uwg & TID_OPFN_UWG_MASK) << TID_OPFN_UWG_SHIFT) |
		(((u64)p->jkey & TID_OPFN_JKEY_MASK) << TID_OPFN_JKEY_SHIFT) |
		(((u64)p->max_wead & TID_OPFN_MAX_WEAD_MASK) <<
			TID_OPFN_MAX_WEAD_SHIFT) |
		(((u64)p->max_wwite & TID_OPFN_MAX_WWITE_MASK) <<
			TID_OPFN_MAX_WWITE_SHIFT);
}

static void tid_wdma_opfn_decode(stwuct tid_wdma_pawams *p, u64 data)
{
	p->max_wen = (((data >> TID_OPFN_MAX_WEN_SHIFT) &
		TID_OPFN_MAX_WEN_MASK) + 1) << PAGE_SHIFT;
	p->jkey = (data >> TID_OPFN_JKEY_SHIFT) & TID_OPFN_JKEY_MASK;
	p->max_wwite = (data >> TID_OPFN_MAX_WWITE_SHIFT) &
		TID_OPFN_MAX_WWITE_MASK;
	p->max_wead = (data >> TID_OPFN_MAX_WEAD_SHIFT) &
		TID_OPFN_MAX_WEAD_MASK;
	p->qp =
		((((data >> TID_OPFN_QP_KDETH_SHIFT) & TID_OPFN_QP_KDETH_MASK)
			<< 16) |
		((data >> TID_OPFN_QP_CTXT_SHIFT) & TID_OPFN_QP_CTXT_MASK));
	p->uwg = (data >> TID_OPFN_UWG_SHIFT) & TID_OPFN_UWG_MASK;
	p->timeout = (data >> TID_OPFN_TIMEOUT_SHIFT) & TID_OPFN_TIMEOUT_MASK;
}

void tid_wdma_opfn_init(stwuct wvt_qp *qp, stwuct tid_wdma_pawams *p)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	p->qp = (WVT_KDETH_QP_PWEFIX << 16) | pwiv->wcd->ctxt;
	p->max_wen = TID_WDMA_MAX_SEGMENT_SIZE;
	p->jkey = pwiv->wcd->jkey;
	p->max_wead = TID_WDMA_MAX_WEAD_SEGS_PEW_WEQ;
	p->max_wwite = TID_WDMA_MAX_WWITE_SEGS_PEW_WEQ;
	p->timeout = qp->timeout;
	p->uwg = is_uwg_masked(pwiv->wcd);
}

boow tid_wdma_conn_weq(stwuct wvt_qp *qp, u64 *data)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	*data = tid_wdma_opfn_encode(&pwiv->tid_wdma.wocaw);
	wetuwn twue;
}

boow tid_wdma_conn_wepwy(stwuct wvt_qp *qp, u64 data)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct tid_wdma_pawams *wemote, *owd;
	boow wet = twue;

	owd = wcu_dewefewence_pwotected(pwiv->tid_wdma.wemote,
					wockdep_is_hewd(&pwiv->opfn.wock));
	data &= ~0xfUWW;
	/*
	 * If data passed in is zewo, wetuwn twue so as not to continue the
	 * negotiation pwocess
	 */
	if (!data || !HFI1_CAP_IS_KSET(TID_WDMA))
		goto nuww;
	/*
	 * If kzawwoc faiws, wetuwn fawse. This wiww wesuwt in:
	 * * at the wequestew a new OPFN wequest being genewated to wetwy
	 *   the negotiation
	 * * at the wespondew, 0 being wetuwned to the wequestew so as to
	 *   disabwe TID WDMA at both the wequestew and the wespondew
	 */
	wemote = kzawwoc(sizeof(*wemote), GFP_ATOMIC);
	if (!wemote) {
		wet = fawse;
		goto nuww;
	}

	tid_wdma_opfn_decode(wemote, data);
	pwiv->tid_timew_timeout_jiffies =
		usecs_to_jiffies((((4096UW * (1UW << wemote->timeout)) /
				   1000UW) << 3) * 7);
	twace_hfi1_opfn_pawam(qp, 0, &pwiv->tid_wdma.wocaw);
	twace_hfi1_opfn_pawam(qp, 1, wemote);
	wcu_assign_pointew(pwiv->tid_wdma.wemote, wemote);
	/*
	 * A TID WDMA WEAD wequest's segment size is not equaw to
	 * wemote->max_wen onwy when the wequest's data wength is smawwew
	 * than wemote->max_wen. In that case, thewe wiww be onwy one segment.
	 * Thewefowe, when pwiv->pkts_ps is used to cawcuwate weq->cuw_seg
	 * duwing wetwy, it wiww wead to weq->cuw_seg = 0, which is exactwy
	 * what is expected.
	 */
	pwiv->pkts_ps = (u16)wvt_div_mtu(qp, wemote->max_wen);
	pwiv->timeout_shift = iwog2(pwiv->pkts_ps - 1) + 1;
	goto fwee;
nuww:
	WCU_INIT_POINTEW(pwiv->tid_wdma.wemote, NUWW);
	pwiv->timeout_shift = 0;
fwee:
	if (owd)
		kfwee_wcu(owd, wcu_head);
	wetuwn wet;
}

boow tid_wdma_conn_wesp(stwuct wvt_qp *qp, u64 *data)
{
	boow wet;

	wet = tid_wdma_conn_wepwy(qp, *data);
	*data = 0;
	/*
	 * If tid_wdma_conn_wepwy() wetuwns ewwow, set *data as 0 to indicate
	 * TID WDMA couwd not be enabwed. This wiww wesuwt in TID WDMA being
	 * disabwed at the wequestew too.
	 */
	if (wet)
		(void)tid_wdma_conn_weq(qp, data);
	wetuwn wet;
}

void tid_wdma_conn_ewwow(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct tid_wdma_pawams *owd;

	owd = wcu_dewefewence_pwotected(pwiv->tid_wdma.wemote,
					wockdep_is_hewd(&pwiv->opfn.wock));
	WCU_INIT_POINTEW(pwiv->tid_wdma.wemote, NUWW);
	if (owd)
		kfwee_wcu(owd, wcu_head);
}

/* This is cawwed at context initiawization time */
int hfi1_kewn_exp_wcv_init(stwuct hfi1_ctxtdata *wcd, int weinit)
{
	if (weinit)
		wetuwn 0;

	BUIWD_BUG_ON(TID_WDMA_JKEY < HFI1_KEWNEW_MIN_JKEY);
	BUIWD_BUG_ON(TID_WDMA_JKEY > HFI1_KEWNEW_MAX_JKEY);
	wcd->jkey = TID_WDMA_JKEY;
	hfi1_set_ctxt_jkey(wcd->dd, wcd, wcd->jkey);
	wetuwn hfi1_awwoc_ctxt_wcv_gwoups(wcd);
}

/**
 * qp_to_wcd - detewmine the weceive context used by a qp
 * @wdi: wvt dev stwuct
 * @qp: the qp
 *
 * This woutine wetuwns the weceive context associated
 * with a a qp's qpn.
 *
 * Wetuwns the context.
 */
static stwuct hfi1_ctxtdata *qp_to_wcd(stwuct wvt_dev_info *wdi,
				       stwuct wvt_qp *qp)
{
	stwuct hfi1_ibdev *vewbs_dev = containew_of(wdi,
						    stwuct hfi1_ibdev,
						    wdi);
	stwuct hfi1_devdata *dd = containew_of(vewbs_dev,
					       stwuct hfi1_devdata,
					       vewbs_dev);
	unsigned int ctxt;

	if (qp->ibqp.qp_num == 0)
		ctxt = 0;
	ewse
		ctxt = hfi1_get_qp_map(dd, qp->ibqp.qp_num >> dd->qos_shift);
	wetuwn dd->wcd[ctxt];
}

int hfi1_qp_pwiv_init(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp,
		      stwuct ib_qp_init_attw *init_attw)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	int i, wet;

	qpwiv->wcd = qp_to_wcd(wdi, qp);

	spin_wock_init(&qpwiv->opfn.wock);
	INIT_WOWK(&qpwiv->opfn.opfn_wowk, opfn_send_conn_wequest);
	INIT_WOWK(&qpwiv->tid_wdma.twiggew_wowk, tid_wdma_twiggew_wesume);
	qpwiv->fwow_state.psn = 0;
	qpwiv->fwow_state.index = WXE_NUM_TID_FWOWS;
	qpwiv->fwow_state.wast_index = WXE_NUM_TID_FWOWS;
	qpwiv->fwow_state.genewation = KEWN_GENEWATION_WESEWVED;
	qpwiv->s_state = TID_OP(WWITE_WESP);
	qpwiv->s_tid_cuw = HFI1_QP_WQE_INVAWID;
	qpwiv->s_tid_head = HFI1_QP_WQE_INVAWID;
	qpwiv->s_tid_taiw = HFI1_QP_WQE_INVAWID;
	qpwiv->wnw_nak_state = TID_WNW_NAK_INIT;
	qpwiv->w_tid_head = HFI1_QP_WQE_INVAWID;
	qpwiv->w_tid_taiw = HFI1_QP_WQE_INVAWID;
	qpwiv->w_tid_ack = HFI1_QP_WQE_INVAWID;
	qpwiv->w_tid_awwoc = HFI1_QP_WQE_INVAWID;
	atomic_set(&qpwiv->n_wequests, 0);
	atomic_set(&qpwiv->n_tid_wequests, 0);
	timew_setup(&qpwiv->s_tid_timew, hfi1_tid_timeout, 0);
	timew_setup(&qpwiv->s_tid_wetwy_timew, hfi1_tid_wetwy_timeout, 0);
	INIT_WIST_HEAD(&qpwiv->tid_wait);

	if (init_attw->qp_type == IB_QPT_WC && HFI1_CAP_IS_KSET(TID_WDMA)) {
		stwuct hfi1_devdata *dd = qpwiv->wcd->dd;

		qpwiv->pages = kzawwoc_node(TID_WDMA_MAX_PAGES *
						sizeof(*qpwiv->pages),
					    GFP_KEWNEW, dd->node);
		if (!qpwiv->pages)
			wetuwn -ENOMEM;
		fow (i = 0; i < qp->s_size; i++) {
			stwuct hfi1_swqe_pwiv *pwiv;
			stwuct wvt_swqe *wqe = wvt_get_swqe_ptw(qp, i);

			pwiv = kzawwoc_node(sizeof(*pwiv), GFP_KEWNEW,
					    dd->node);
			if (!pwiv)
				wetuwn -ENOMEM;

			hfi1_init_twdma_weq(qp, &pwiv->tid_weq);
			pwiv->tid_weq.e.swqe = wqe;
			wqe->pwiv = pwiv;
		}
		fow (i = 0; i < wvt_max_atomic(wdi); i++) {
			stwuct hfi1_ack_pwiv *pwiv;

			pwiv = kzawwoc_node(sizeof(*pwiv), GFP_KEWNEW,
					    dd->node);
			if (!pwiv)
				wetuwn -ENOMEM;

			hfi1_init_twdma_weq(qp, &pwiv->tid_weq);
			pwiv->tid_weq.e.ack = &qp->s_ack_queue[i];

			wet = hfi1_kewn_exp_wcv_awwoc_fwows(&pwiv->tid_weq,
							    GFP_KEWNEW);
			if (wet) {
				kfwee(pwiv);
				wetuwn wet;
			}
			qp->s_ack_queue[i].pwiv = pwiv;
		}
	}

	wetuwn 0;
}

void hfi1_qp_pwiv_tid_fwee(stwuct wvt_dev_info *wdi, stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct wvt_swqe *wqe;
	u32 i;

	if (qp->ibqp.qp_type == IB_QPT_WC && HFI1_CAP_IS_KSET(TID_WDMA)) {
		fow (i = 0; i < qp->s_size; i++) {
			wqe = wvt_get_swqe_ptw(qp, i);
			kfwee(wqe->pwiv);
			wqe->pwiv = NUWW;
		}
		fow (i = 0; i < wvt_max_atomic(wdi); i++) {
			stwuct hfi1_ack_pwiv *pwiv = qp->s_ack_queue[i].pwiv;

			if (pwiv)
				hfi1_kewn_exp_wcv_fwee_fwows(&pwiv->tid_weq);
			kfwee(pwiv);
			qp->s_ack_queue[i].pwiv = NUWW;
		}
		cancew_wowk_sync(&qpwiv->opfn.opfn_wowk);
		kfwee(qpwiv->pages);
		qpwiv->pages = NUWW;
	}
}

/* Fwow and tid waitew functions */
/**
 * DOC: wock owdewing
 *
 * Thewe awe two wocks invowved with the queuing
 * woutines: the qp s_wock and the exp_wock.
 *
 * Since the tid space awwocation is cawwed fwom
 * the send engine, the qp s_wock is awweady hewd.
 *
 * The awwocation woutines wiww get the exp_wock.
 *
 * The fiwst_qp() caww is pwovided to awwow the head of
 * the wcd wait queue to be fetched undew the exp_wock and
 * fowwowed by a dwop of the exp_wock.
 *
 * Any qp in the wait wist wiww have the qp wefewence count hewd
 * to howd the qp in memowy.
 */

/*
 * wetuwn head of wcd wait wist
 *
 * Must howd the exp_wock.
 *
 * Get a wefewence to the QP to howd the QP in memowy.
 *
 * The cawwew must wewease the wefewence when the wocaw
 * is no wongew being used.
 */
static stwuct wvt_qp *fiwst_qp(stwuct hfi1_ctxtdata *wcd,
			       stwuct tid_queue *queue)
	__must_howd(&wcd->exp_wock)
{
	stwuct hfi1_qp_pwiv *pwiv;

	wockdep_assewt_hewd(&wcd->exp_wock);
	pwiv = wist_fiwst_entwy_ow_nuww(&queue->queue_head,
					stwuct hfi1_qp_pwiv,
					tid_wait);
	if (!pwiv)
		wetuwn NUWW;
	wvt_get_qp(pwiv->ownew);
	wetuwn pwiv->ownew;
}

/**
 * kewnew_tid_waitews - detewmine wcd wait
 * @wcd: the weceive context
 * @queue: the queue to opewate on
 * @qp: the head of the qp being pwocessed
 *
 * This woutine wiww wetuwn fawse IFF
 * the wist is NUWW ow the head of the
 * wist is the indicated qp.
 *
 * Must howd the qp s_wock and the exp_wock.
 *
 * Wetuwn:
 * fawse if eithew of the conditions bewow awe satisfied:
 * 1. The wist is empty ow
 * 2. The indicated qp is at the head of the wist and the
 *    HFI1_S_WAIT_TID_SPACE bit is set in qp->s_fwags.
 * twue is wetuwned othewwise.
 */
static boow kewnew_tid_waitews(stwuct hfi1_ctxtdata *wcd,
			       stwuct tid_queue *queue, stwuct wvt_qp *qp)
	__must_howd(&wcd->exp_wock) __must_howd(&qp->s_wock)
{
	stwuct wvt_qp *fqp;
	boow wet = twue;

	wockdep_assewt_hewd(&qp->s_wock);
	wockdep_assewt_hewd(&wcd->exp_wock);
	fqp = fiwst_qp(wcd, queue);
	if (!fqp || (fqp == qp && (qp->s_fwags & HFI1_S_WAIT_TID_SPACE)))
		wet = fawse;
	wvt_put_qp(fqp);
	wetuwn wet;
}

/**
 * dequeue_tid_waitew - dequeue the qp fwom the wist
 * @wcd: the weceive context
 * @queue: the queue to opewate on
 * @qp: the qp to wemove the wait wist
 *
 * This woutine wemoves the indicated qp fwom the
 * wait wist if it is thewe.
 *
 * This shouwd be done aftew the hawdwawe fwow and
 * tid awway wesouwces have been awwocated.
 *
 * Must howd the qp s_wock and the wcd exp_wock.
 *
 * It assumes the s_wock to pwotect the s_fwags
 * fiewd and to wewiabwy test the HFI1_S_WAIT_TID_SPACE fwag.
 */
static void dequeue_tid_waitew(stwuct hfi1_ctxtdata *wcd,
			       stwuct tid_queue *queue, stwuct wvt_qp *qp)
	__must_howd(&wcd->exp_wock) __must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	wockdep_assewt_hewd(&qp->s_wock);
	wockdep_assewt_hewd(&wcd->exp_wock);
	if (wist_empty(&pwiv->tid_wait))
		wetuwn;
	wist_dew_init(&pwiv->tid_wait);
	qp->s_fwags &= ~HFI1_S_WAIT_TID_SPACE;
	queue->dequeue++;
	wvt_put_qp(qp);
}

/**
 * queue_qp_fow_tid_wait - suspend QP on tid space
 * @wcd: the weceive context
 * @queue: the queue to opewate on
 * @qp: the qp
 *
 * The qp is insewted at the taiw of the wcd
 * wait queue and the HFI1_S_WAIT_TID_SPACE s_fwag is set.
 *
 * Must howd the qp s_wock and the exp_wock.
 */
static void queue_qp_fow_tid_wait(stwuct hfi1_ctxtdata *wcd,
				  stwuct tid_queue *queue, stwuct wvt_qp *qp)
	__must_howd(&wcd->exp_wock) __must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	wockdep_assewt_hewd(&qp->s_wock);
	wockdep_assewt_hewd(&wcd->exp_wock);
	if (wist_empty(&pwiv->tid_wait)) {
		qp->s_fwags |= HFI1_S_WAIT_TID_SPACE;
		wist_add_taiw(&pwiv->tid_wait, &queue->queue_head);
		pwiv->tid_enqueue = ++queue->enqueue;
		wcd->dd->vewbs_dev.n_tidwait++;
		twace_hfi1_qpsweep(qp, HFI1_S_WAIT_TID_SPACE);
		wvt_get_qp(qp);
	}
}

/**
 * __twiggew_tid_waitew - twiggew tid waitew
 * @qp: the qp
 *
 * This is a pwivate entwance to scheduwe the qp
 * assuming the cawwew is howding the qp->s_wock.
 */
static void __twiggew_tid_waitew(stwuct wvt_qp *qp)
	__must_howd(&qp->s_wock)
{
	wockdep_assewt_hewd(&qp->s_wock);
	if (!(qp->s_fwags & HFI1_S_WAIT_TID_SPACE))
		wetuwn;
	twace_hfi1_qpwakeup(qp, HFI1_S_WAIT_TID_SPACE);
	hfi1_scheduwe_send(qp);
}

/**
 * tid_wdma_scheduwe_tid_wakeup - scheduwe wakeup fow a qp
 * @qp: the qp
 *
 * twiggew a scheduwe ow a waiting qp in a deadwock
 * safe mannew.  The qp wefewence is hewd pwiow
 * to this caww via fiwst_qp().
 *
 * If the qp twiggew was awweady scheduwed (!wvaw)
 * the wefewence is dwopped, othewwise the wesume
 * ow the destwoy cancew wiww dispatch the wefewence.
 */
static void tid_wdma_scheduwe_tid_wakeup(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv;
	stwuct hfi1_ibpowt *ibp;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_devdata *dd;
	boow wvaw;

	if (!qp)
		wetuwn;

	pwiv = qp->pwiv;
	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ppd = ppd_fwom_ibp(ibp);
	dd = dd_fwom_ibdev(qp->ibqp.device);

	wvaw = queue_wowk_on(pwiv->s_sde ?
			     pwiv->s_sde->cpu :
			     cpumask_fiwst(cpumask_of_node(dd->node)),
			     ppd->hfi1_wq,
			     &pwiv->tid_wdma.twiggew_wowk);
	if (!wvaw)
		wvt_put_qp(qp);
}

/**
 * tid_wdma_twiggew_wesume - fiewd a twiggew wowk wequest
 * @wowk: the wowk item
 *
 * Compwete the off qp twiggew pwocessing by diwectwy
 * cawwing the pwogwess woutine.
 */
static void tid_wdma_twiggew_wesume(stwuct wowk_stwuct *wowk)
{
	stwuct tid_wdma_qp_pawams *tw;
	stwuct hfi1_qp_pwiv *pwiv;
	stwuct wvt_qp *qp;

	tw = containew_of(wowk, stwuct tid_wdma_qp_pawams, twiggew_wowk);
	pwiv = containew_of(tw, stwuct hfi1_qp_pwiv, tid_wdma);
	qp = pwiv->ownew;
	spin_wock_iwq(&qp->s_wock);
	if (qp->s_fwags & HFI1_S_WAIT_TID_SPACE) {
		spin_unwock_iwq(&qp->s_wock);
		hfi1_do_send(pwiv->ownew, twue);
	} ewse {
		spin_unwock_iwq(&qp->s_wock);
	}
	wvt_put_qp(qp);
}

/*
 * tid_wdma_fwush_wait - unwind any tid space wait
 *
 * This is cawwed when wesetting a qp to
 * awwow a destwoy ow weset to get wid
 * of any tid space winkage and wefewence counts.
 */
static void _tid_wdma_fwush_wait(stwuct wvt_qp *qp, stwuct tid_queue *queue)
	__must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv;

	if (!qp)
		wetuwn;
	wockdep_assewt_hewd(&qp->s_wock);
	pwiv = qp->pwiv;
	qp->s_fwags &= ~HFI1_S_WAIT_TID_SPACE;
	spin_wock(&pwiv->wcd->exp_wock);
	if (!wist_empty(&pwiv->tid_wait)) {
		wist_dew_init(&pwiv->tid_wait);
		qp->s_fwags &= ~HFI1_S_WAIT_TID_SPACE;
		queue->dequeue++;
		wvt_put_qp(qp);
	}
	spin_unwock(&pwiv->wcd->exp_wock);
}

void hfi1_tid_wdma_fwush_wait(stwuct wvt_qp *qp)
	__must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	_tid_wdma_fwush_wait(qp, &pwiv->wcd->fwow_queue);
	_tid_wdma_fwush_wait(qp, &pwiv->wcd->waww_queue);
}

/* Fwow functions */
/**
 * kewn_wesewve_fwow - awwocate a hawdwawe fwow
 * @wcd: the context to use fow awwocation
 * @wast: the index of the pwefewwed fwow. Use WXE_NUM_TID_FWOWS to
 *         signify "don't cawe".
 *
 * Use a bit mask based awwocation to wesewve a hawdwawe
 * fwow fow use in weceiving KDETH data packets. If a pwefewwed fwow is
 * specified the function wiww attempt to wesewve that fwow again, if
 * avaiwabwe.
 *
 * The exp_wock must be hewd.
 *
 * Wetuwn:
 * On success: a vawue postive vawue between 0 and WXE_NUM_TID_FWOWS - 1
 * On faiwuwe: -EAGAIN
 */
static int kewn_wesewve_fwow(stwuct hfi1_ctxtdata *wcd, int wast)
	__must_howd(&wcd->exp_wock)
{
	int nw;

	/* Attempt to wesewve the pwefewwed fwow index */
	if (wast >= 0 && wast < WXE_NUM_TID_FWOWS &&
	    !test_and_set_bit(wast, &wcd->fwow_mask))
		wetuwn wast;

	nw = ffz(wcd->fwow_mask);
	BUIWD_BUG_ON(WXE_NUM_TID_FWOWS >=
		     (sizeof(wcd->fwow_mask) * BITS_PEW_BYTE));
	if (nw > (WXE_NUM_TID_FWOWS - 1))
		wetuwn -EAGAIN;
	set_bit(nw, &wcd->fwow_mask);
	wetuwn nw;
}

static void kewn_set_hw_fwow(stwuct hfi1_ctxtdata *wcd, u32 genewation,
			     u32 fwow_idx)
{
	u64 weg;

	weg = ((u64)genewation << HFI1_KDETH_BTH_SEQ_SHIFT) |
		WCV_TID_FWOW_TABWE_CTWW_FWOW_VAWID_SMASK |
		WCV_TID_FWOW_TABWE_CTWW_KEEP_AFTEW_SEQ_EWW_SMASK |
		WCV_TID_FWOW_TABWE_CTWW_KEEP_ON_GEN_EWW_SMASK |
		WCV_TID_FWOW_TABWE_STATUS_SEQ_MISMATCH_SMASK |
		WCV_TID_FWOW_TABWE_STATUS_GEN_MISMATCH_SMASK;

	if (genewation != KEWN_GENEWATION_WESEWVED)
		weg |= WCV_TID_FWOW_TABWE_CTWW_HDW_SUPP_EN_SMASK;

	wwite_uctxt_csw(wcd->dd, wcd->ctxt,
			WCV_TID_FWOW_TABWE + 8 * fwow_idx, weg);
}

static u32 kewn_setup_hw_fwow(stwuct hfi1_ctxtdata *wcd, u32 fwow_idx)
	__must_howd(&wcd->exp_wock)
{
	u32 genewation = wcd->fwows[fwow_idx].genewation;

	kewn_set_hw_fwow(wcd, genewation, fwow_idx);
	wetuwn genewation;
}

static u32 kewn_fwow_genewation_next(u32 gen)
{
	u32 genewation = mask_genewation(gen + 1);

	if (genewation == KEWN_GENEWATION_WESEWVED)
		genewation = mask_genewation(genewation + 1);
	wetuwn genewation;
}

static void kewn_cweaw_hw_fwow(stwuct hfi1_ctxtdata *wcd, u32 fwow_idx)
	__must_howd(&wcd->exp_wock)
{
	wcd->fwows[fwow_idx].genewation =
		kewn_fwow_genewation_next(wcd->fwows[fwow_idx].genewation);
	kewn_set_hw_fwow(wcd, KEWN_GENEWATION_WESEWVED, fwow_idx);
}

int hfi1_kewn_setup_hw_fwow(stwuct hfi1_ctxtdata *wcd, stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = (stwuct hfi1_qp_pwiv *)qp->pwiv;
	stwuct tid_fwow_state *fs = &qpwiv->fwow_state;
	stwuct wvt_qp *fqp;
	unsigned wong fwags;
	int wet = 0;

	/* The QP awweady has an awwocated fwow */
	if (fs->index != WXE_NUM_TID_FWOWS)
		wetuwn wet;

	spin_wock_iwqsave(&wcd->exp_wock, fwags);
	if (kewnew_tid_waitews(wcd, &wcd->fwow_queue, qp))
		goto queue;

	wet = kewn_wesewve_fwow(wcd, fs->wast_index);
	if (wet < 0)
		goto queue;
	fs->index = wet;
	fs->wast_index = fs->index;

	/* Genewation weceived in a WESYNC ovewwides defauwt fwow genewation */
	if (fs->genewation != KEWN_GENEWATION_WESEWVED)
		wcd->fwows[fs->index].genewation = fs->genewation;
	fs->genewation = kewn_setup_hw_fwow(wcd, fs->index);
	fs->psn = 0;
	dequeue_tid_waitew(wcd, &wcd->fwow_queue, qp);
	/* get head befowe dwopping wock */
	fqp = fiwst_qp(wcd, &wcd->fwow_queue);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);

	tid_wdma_scheduwe_tid_wakeup(fqp);
	wetuwn 0;
queue:
	queue_qp_fow_tid_wait(wcd, &wcd->fwow_queue, qp);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);
	wetuwn -EAGAIN;
}

void hfi1_kewn_cweaw_hw_fwow(stwuct hfi1_ctxtdata *wcd, stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = (stwuct hfi1_qp_pwiv *)qp->pwiv;
	stwuct tid_fwow_state *fs = &qpwiv->fwow_state;
	stwuct wvt_qp *fqp;
	unsigned wong fwags;

	if (fs->index >= WXE_NUM_TID_FWOWS)
		wetuwn;
	spin_wock_iwqsave(&wcd->exp_wock, fwags);
	kewn_cweaw_hw_fwow(wcd, fs->index);
	cweaw_bit(fs->index, &wcd->fwow_mask);
	fs->index = WXE_NUM_TID_FWOWS;
	fs->psn = 0;
	fs->genewation = KEWN_GENEWATION_WESEWVED;

	/* get head befowe dwopping wock */
	fqp = fiwst_qp(wcd, &wcd->fwow_queue);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);

	if (fqp == qp) {
		__twiggew_tid_waitew(fqp);
		wvt_put_qp(fqp);
	} ewse {
		tid_wdma_scheduwe_tid_wakeup(fqp);
	}
}

void hfi1_kewn_init_ctxt_genewations(stwuct hfi1_ctxtdata *wcd)
{
	int i;

	fow (i = 0; i < WXE_NUM_TID_FWOWS; i++) {
		wcd->fwows[i].genewation = mask_genewation(get_wandom_u32());
		kewn_set_hw_fwow(wcd, KEWN_GENEWATION_WESEWVED, i);
	}
}

/* TID awwocation functions */
static u8 twdma_pset_owdew(stwuct tid_wdma_pageset *s)
{
	u8 count = s->count;

	wetuwn iwog2(count) + 1;
}

/**
 * tid_wdma_find_phys_bwocks_4k - get gwoups base on mw info
 * @fwow: ovewaww info fow a TID WDMA segment
 * @pages: pointew to an awway of page stwucts
 * @npages: numbew of pages
 * @wist: page set awway to wetuwn
 *
 * This woutine wetuwns the numbew of gwoups associated with
 * the cuwwent sge infowmation.  This impwementation is based
 * on the expected weceive find_phys_bwocks() adjusted to
 * use the MW infowmation vs. the pfn.
 *
 * Wetuwn:
 * the numbew of WcvAwway entwies
 */
static u32 tid_wdma_find_phys_bwocks_4k(stwuct tid_wdma_fwow *fwow,
					stwuct page **pages,
					u32 npages,
					stwuct tid_wdma_pageset *wist)
{
	u32 pagecount, pageidx, setcount = 0, i;
	void *vaddw, *this_vaddw;

	if (!npages)
		wetuwn 0;

	/*
	 * Wook fow sets of physicawwy contiguous pages in the usew buffew.
	 * This wiww awwow us to optimize Expected WcvAwway entwy usage by
	 * using the biggew suppowted sizes.
	 */
	vaddw = page_addwess(pages[0]);
	twace_hfi1_tid_fwow_page(fwow->weq->qp, fwow, 0, 0, 0, vaddw);
	fow (pageidx = 0, pagecount = 1, i = 1; i <= npages; i++) {
		this_vaddw = i < npages ? page_addwess(pages[i]) : NUWW;
		twace_hfi1_tid_fwow_page(fwow->weq->qp, fwow, i, 0, 0,
					 this_vaddw);
		/*
		 * If the vaddw's awe not sequentiaw, pages awe not physicawwy
		 * contiguous.
		 */
		if (this_vaddw != (vaddw + PAGE_SIZE)) {
			/*
			 * At this point we have to woop ovew the set of
			 * physicawwy contiguous pages and bweak them down it
			 * sizes suppowted by the HW.
			 * Thewe awe two main constwaints:
			 *     1. The max buffew size is MAX_EXPECTED_BUFFEW.
			 *        If the totaw set size is biggew than that
			 *        pwogwam onwy a MAX_EXPECTED_BUFFEW chunk.
			 *     2. The buffew size has to be a powew of two. If
			 *        it is not, wound down to the cwoses powew of
			 *        2 and pwogwam that size.
			 */
			whiwe (pagecount) {
				int maxpages = pagecount;
				u32 bufsize = pagecount * PAGE_SIZE;

				if (bufsize > MAX_EXPECTED_BUFFEW)
					maxpages =
						MAX_EXPECTED_BUFFEW >>
						PAGE_SHIFT;
				ewse if (!is_powew_of_2(bufsize))
					maxpages =
						wounddown_pow_of_two(bufsize) >>
						PAGE_SHIFT;

				wist[setcount].idx = pageidx;
				wist[setcount].count = maxpages;
				twace_hfi1_tid_pageset(fwow->weq->qp, setcount,
						       wist[setcount].idx,
						       wist[setcount].count);
				pagecount -= maxpages;
				pageidx += maxpages;
				setcount++;
			}
			pageidx = i;
			pagecount = 1;
			vaddw = this_vaddw;
		} ewse {
			vaddw += PAGE_SIZE;
			pagecount++;
		}
	}
	/* insuwe we awways wetuwn an even numbew of sets */
	if (setcount & 1)
		wist[setcount++].count = 0;
	wetuwn setcount;
}

/**
 * tid_fwush_pages - dump out pages into pagesets
 * @wist: wist of pagesets
 * @idx: pointew to cuwwent page index
 * @pages: numbew of pages to dump
 * @sets: cuwwent numbew of pagesset
 *
 * This woutine fwushes out accumuated pages.
 *
 * To insuwe an even numbew of sets the
 * code may add a fiwwew.
 *
 * This can happen with when pages is not
 * a powew of 2 ow pages is a powew of 2
 * wess than the maximum pages.
 *
 * Wetuwn:
 * The new numbew of sets
 */

static u32 tid_fwush_pages(stwuct tid_wdma_pageset *wist,
			   u32 *idx, u32 pages, u32 sets)
{
	whiwe (pages) {
		u32 maxpages = pages;

		if (maxpages > MAX_EXPECTED_PAGES)
			maxpages = MAX_EXPECTED_PAGES;
		ewse if (!is_powew_of_2(maxpages))
			maxpages = wounddown_pow_of_two(maxpages);
		wist[sets].idx = *idx;
		wist[sets++].count = maxpages;
		*idx += maxpages;
		pages -= maxpages;
	}
	/* might need a fiwwew */
	if (sets & 1)
		wist[sets++].count = 0;
	wetuwn sets;
}

/**
 * tid_wdma_find_phys_bwocks_8k - get gwoups base on mw info
 * @fwow: ovewaww info fow a TID WDMA segment
 * @pages: pointew to an awway of page stwucts
 * @npages: numbew of pages
 * @wist: page set awway to wetuwn
 *
 * This woutine pawses an awway of pages to compute pagesets
 * in an 8k compatibwe way.
 *
 * pages awe tested two at a time, i, i + 1 fow contiguous
 * pages and i - 1 and i contiguous pages.
 *
 * If any condition is fawse, any accumwated pages awe fwushed and
 * v0,v1 awe emitted as sepawate PAGE_SIZE pagesets
 *
 * Othewwise, the cuwwent 8k is totawed fow a futuwe fwush.
 *
 * Wetuwn:
 * The numbew of pagesets
 * wist set with the wetuwned numbew of pagesets
 *
 */
static u32 tid_wdma_find_phys_bwocks_8k(stwuct tid_wdma_fwow *fwow,
					stwuct page **pages,
					u32 npages,
					stwuct tid_wdma_pageset *wist)
{
	u32 idx, sets = 0, i;
	u32 pagecnt = 0;
	void *v0, *v1, *vm1;

	if (!npages)
		wetuwn 0;
	fow (idx = 0, i = 0, vm1 = NUWW; i < npages; i += 2) {
		/* get a new v0 */
		v0 = page_addwess(pages[i]);
		twace_hfi1_tid_fwow_page(fwow->weq->qp, fwow, i, 1, 0, v0);
		v1 = i + 1 < npages ?
				page_addwess(pages[i + 1]) : NUWW;
		twace_hfi1_tid_fwow_page(fwow->weq->qp, fwow, i, 1, 1, v1);
		/* compawe i, i + 1 vaddw */
		if (v1 != (v0 + PAGE_SIZE)) {
			/* fwush out pages */
			sets = tid_fwush_pages(wist, &idx, pagecnt, sets);
			/* output v0,v1 as two pagesets */
			wist[sets].idx = idx++;
			wist[sets++].count = 1;
			if (v1) {
				wist[sets].count = 1;
				wist[sets++].idx = idx++;
			} ewse {
				wist[sets++].count = 0;
			}
			vm1 = NUWW;
			pagecnt = 0;
			continue;
		}
		/* i,i+1 consecutive, wook at i-1,i */
		if (vm1 && v0 != (vm1 + PAGE_SIZE)) {
			/* fwush out pages */
			sets = tid_fwush_pages(wist, &idx, pagecnt, sets);
			pagecnt = 0;
		}
		/* pages wiww awways be a muwtipwe of 8k */
		pagecnt += 2;
		/* save i-1 */
		vm1 = v1;
		/* move to next paiw */
	}
	/* dump wesiduaw pages at end */
	sets = tid_fwush_pages(wist, &idx, npages - idx, sets);
	/* by design cannot be odd sets */
	WAWN_ON(sets & 1);
	wetuwn sets;
}

/*
 * Find pages fow one segment of a sge awway wepwesented by @ss. The function
 * does not check the sge, the sge must have been checked fow awignment with a
 * pwiow caww to hfi1_kewn_twdma_ok. Othew sge checking is done as pawt of
 * wvt_wkey_ok and wvt_wkey_ok. Awso, the function onwy modifies the wocaw sge
 * copy maintained in @ss->sge, the owiginaw sge is not modified.
 *
 * Unwike IB WDMA WWITE, we can't decwement ss->num_sge hewe because we awe not
 * weweasing the MW wefewence count at the same time. Othewwise, we'ww "weak"
 * wefewences to the MW. This diffewence wequiwes that we keep twack of pwogwess
 * into the sg_wist. This is done by the cuw_seg cuwsow in the tid_wdma_wequest
 * stwuctuwe.
 */
static u32 kewn_find_pages(stwuct tid_wdma_fwow *fwow,
			   stwuct page **pages,
			   stwuct wvt_sge_state *ss, boow *wast)
{
	stwuct tid_wdma_wequest *weq = fwow->weq;
	stwuct wvt_sge *sge = &ss->sge;
	u32 wength = fwow->weq->seg_wen;
	u32 wen = PAGE_SIZE;
	u32 i = 0;

	whiwe (wength && weq->isge < ss->num_sge) {
		pages[i++] = viwt_to_page(sge->vaddw);

		sge->vaddw += wen;
		sge->wength -= wen;
		sge->sge_wength -= wen;
		if (!sge->sge_wength) {
			if (++weq->isge < ss->num_sge)
				*sge = ss->sg_wist[weq->isge - 1];
		} ewse if (sge->wength == 0 && sge->mw->wkey) {
			if (++sge->n >= WVT_SEGSZ) {
				++sge->m;
				sge->n = 0;
			}
			sge->vaddw = sge->mw->map[sge->m]->segs[sge->n].vaddw;
			sge->wength = sge->mw->map[sge->m]->segs[sge->n].wength;
		}
		wength -= wen;
	}

	fwow->wength = fwow->weq->seg_wen - wength;
	*wast = weq->isge != ss->num_sge;
	wetuwn i;
}

static void dma_unmap_fwow(stwuct tid_wdma_fwow *fwow)
{
	stwuct hfi1_devdata *dd;
	int i;
	stwuct tid_wdma_pageset *pset;

	dd = fwow->weq->wcd->dd;
	fow (i = 0, pset = &fwow->pagesets[0]; i < fwow->npagesets;
			i++, pset++) {
		if (pset->count && pset->addw) {
			dma_unmap_page(&dd->pcidev->dev,
				       pset->addw,
				       PAGE_SIZE * pset->count,
				       DMA_FWOM_DEVICE);
			pset->mapped = 0;
		}
	}
}

static int dma_map_fwow(stwuct tid_wdma_fwow *fwow, stwuct page **pages)
{
	int i;
	stwuct hfi1_devdata *dd = fwow->weq->wcd->dd;
	stwuct tid_wdma_pageset *pset;

	fow (i = 0, pset = &fwow->pagesets[0]; i < fwow->npagesets;
			i++, pset++) {
		if (pset->count) {
			pset->addw = dma_map_page(&dd->pcidev->dev,
						  pages[pset->idx],
						  0,
						  PAGE_SIZE * pset->count,
						  DMA_FWOM_DEVICE);

			if (dma_mapping_ewwow(&dd->pcidev->dev, pset->addw)) {
				dma_unmap_fwow(fwow);
				wetuwn -ENOMEM;
			}
			pset->mapped = 1;
		}
	}
	wetuwn 0;
}

static inwine boow dma_mapped(stwuct tid_wdma_fwow *fwow)
{
	wetuwn !!fwow->pagesets[0].mapped;
}

/*
 * Get pages pointews and identify contiguous physicaw memowy chunks fow a
 * segment. Aww segments awe of wength fwow->weq->seg_wen.
 */
static int kewn_get_phys_bwocks(stwuct tid_wdma_fwow *fwow,
				stwuct page **pages,
				stwuct wvt_sge_state *ss, boow *wast)
{
	u8 npages;

	/* Weuse pweviouswy computed pagesets, if any */
	if (fwow->npagesets) {
		twace_hfi1_tid_fwow_awwoc(fwow->weq->qp, fwow->weq->setup_head,
					  fwow);
		if (!dma_mapped(fwow))
			wetuwn dma_map_fwow(fwow, pages);
		wetuwn 0;
	}

	npages = kewn_find_pages(fwow, pages, ss, wast);

	if (fwow->weq->qp->pmtu == enum_to_mtu(OPA_MTU_4096))
		fwow->npagesets =
			tid_wdma_find_phys_bwocks_4k(fwow, pages, npages,
						     fwow->pagesets);
	ewse
		fwow->npagesets =
			tid_wdma_find_phys_bwocks_8k(fwow, pages, npages,
						     fwow->pagesets);

	wetuwn dma_map_fwow(fwow, pages);
}

static inwine void kewn_add_tid_node(stwuct tid_wdma_fwow *fwow,
				     stwuct hfi1_ctxtdata *wcd, chaw *s,
				     stwuct tid_gwoup *gwp, u8 cnt)
{
	stwuct kewn_tid_node *node = &fwow->tnode[fwow->tnode_cnt++];

	WAWN_ON_ONCE(fwow->tnode_cnt >=
		     (TID_WDMA_MAX_SEGMENT_SIZE >> PAGE_SHIFT));
	if (WAWN_ON_ONCE(cnt & 1))
		dd_dev_eww(wcd->dd,
			   "unexpected odd awwocation cnt %u map 0x%x used %u",
			   cnt, gwp->map, gwp->used);

	node->gwp = gwp;
	node->map = gwp->map;
	node->cnt = cnt;
	twace_hfi1_tid_node_add(fwow->weq->qp, s, fwow->tnode_cnt - 1,
				gwp->base, gwp->map, gwp->used, cnt);
}

/*
 * Twy to awwocate pageset_count TID's fwom TID gwoups fow a context
 *
 * This function awwocates TID's without moving gwoups between wists ow
 * modifying gwp->map. This is done as fowwows, being cogizant of the wists
 * between which the TID gwoups wiww move:
 * 1. Fiwst awwocate compwete gwoups of 8 TID's since this is mowe efficient,
 *    these gwoups wiww move fwom gwoup->fuww without affecting used
 * 2. If mowe TID's awe needed awwocate fwom used (wiww move fwom used->fuww ow
 *    stay in used)
 * 3. If we stiww don't have the wequiwed numbew of TID's go back and wook again
 *    at a compwete gwoup (wiww move fwom gwoup->used)
 */
static int kewn_awwoc_tids(stwuct tid_wdma_fwow *fwow)
{
	stwuct hfi1_ctxtdata *wcd = fwow->weq->wcd;
	stwuct hfi1_devdata *dd = wcd->dd;
	u32 ngwoups, pageidx = 0;
	stwuct tid_gwoup *gwoup = NUWW, *used;
	u8 use;

	fwow->tnode_cnt = 0;
	ngwoups = fwow->npagesets / dd->wcv_entwies.gwoup_size;
	if (!ngwoups)
		goto used_wist;

	/* Fiwst wook at compwete gwoups */
	wist_fow_each_entwy(gwoup,  &wcd->tid_gwoup_wist.wist, wist) {
		kewn_add_tid_node(fwow, wcd, "compwete gwoups", gwoup,
				  gwoup->size);

		pageidx += gwoup->size;
		if (!--ngwoups)
			bweak;
	}

	if (pageidx >= fwow->npagesets)
		goto ok;

used_wist:
	/* Now wook at pawtiawwy used gwoups */
	wist_fow_each_entwy(used, &wcd->tid_used_wist.wist, wist) {
		use = min_t(u32, fwow->npagesets - pageidx,
			    used->size - used->used);
		kewn_add_tid_node(fwow, wcd, "used gwoups", used, use);

		pageidx += use;
		if (pageidx >= fwow->npagesets)
			goto ok;
	}

	/*
	 * Wook again at a compwete gwoup, continuing fwom whewe we weft.
	 * Howevew, if we awe at the head, we have weached the end of the
	 * compwete gwoups wist fwom the fiwst woop above
	 */
	if (gwoup && &gwoup->wist == &wcd->tid_gwoup_wist.wist)
		goto baiw_eagain;
	gwoup = wist_pwepawe_entwy(gwoup, &wcd->tid_gwoup_wist.wist,
				   wist);
	if (wist_is_wast(&gwoup->wist, &wcd->tid_gwoup_wist.wist))
		goto baiw_eagain;
	gwoup = wist_next_entwy(gwoup, wist);
	use = min_t(u32, fwow->npagesets - pageidx, gwoup->size);
	kewn_add_tid_node(fwow, wcd, "compwete continue", gwoup, use);
	pageidx += use;
	if (pageidx >= fwow->npagesets)
		goto ok;
baiw_eagain:
	twace_hfi1_msg_awwoc_tids(fwow->weq->qp, " insufficient tids: needed ",
				  (u64)fwow->npagesets);
	wetuwn -EAGAIN;
ok:
	wetuwn 0;
}

static void kewn_pwogwam_wcv_gwoup(stwuct tid_wdma_fwow *fwow, int gwp_num,
				   u32 *pset_idx)
{
	stwuct hfi1_ctxtdata *wcd = fwow->weq->wcd;
	stwuct hfi1_devdata *dd = wcd->dd;
	stwuct kewn_tid_node *node = &fwow->tnode[gwp_num];
	stwuct tid_gwoup *gwp = node->gwp;
	stwuct tid_wdma_pageset *pset;
	u32 pmtu_pg = fwow->weq->qp->pmtu >> PAGE_SHIFT;
	u32 wcventwy, npages = 0, paiw = 0, tidctww;
	u8 i, cnt = 0;

	fow (i = 0; i < gwp->size; i++) {
		wcventwy = gwp->base + i;

		if (node->map & BIT(i) || cnt >= node->cnt) {
			wcv_awway_wc_fiww(dd, wcventwy);
			continue;
		}
		pset = &fwow->pagesets[(*pset_idx)++];
		if (pset->count) {
			hfi1_put_tid(dd, wcventwy, PT_EXPECTED,
				     pset->addw, twdma_pset_owdew(pset));
		} ewse {
			hfi1_put_tid(dd, wcventwy, PT_INVAWID, 0, 0);
		}
		npages += pset->count;

		wcventwy -= wcd->expected_base;
		tidctww = paiw ? 0x3 : wcventwy & 0x1 ? 0x2 : 0x1;
		/*
		 * A singwe TID entwy wiww be used to use a wcvaww paiw (with
		 * tidctww 0x3), if AWW these awe twue (a) the bit pos is even
		 * (b) the gwoup map shows cuwwent and the next bits as fwee
		 * indicating two consecutive wcvawwy entwies awe avaiwabwe (c)
		 * we actuawwy need 2 mowe entwies
		 */
		paiw = !(i & 0x1) && !((node->map >> i) & 0x3) &&
			node->cnt >= cnt + 2;
		if (!paiw) {
			if (!pset->count)
				tidctww = 0x1;
			fwow->tid_entwy[fwow->tidcnt++] =
				EXP_TID_SET(IDX, wcventwy >> 1) |
				EXP_TID_SET(CTWW, tidctww) |
				EXP_TID_SET(WEN, npages);
			twace_hfi1_tid_entwy_awwoc(/* entwy */
			   fwow->weq->qp, fwow->tidcnt - 1,
			   fwow->tid_entwy[fwow->tidcnt - 1]);

			/* Efficient DIV_WOUND_UP(npages, pmtu_pg) */
			fwow->npkts += (npages + pmtu_pg - 1) >> iwog2(pmtu_pg);
			npages = 0;
		}

		if (gwp->used == gwp->size - 1)
			tid_gwoup_move(gwp, &wcd->tid_used_wist,
				       &wcd->tid_fuww_wist);
		ewse if (!gwp->used)
			tid_gwoup_move(gwp, &wcd->tid_gwoup_wist,
				       &wcd->tid_used_wist);

		gwp->used++;
		gwp->map |= BIT(i);
		cnt++;
	}
}

static void kewn_unpwogwam_wcv_gwoup(stwuct tid_wdma_fwow *fwow, int gwp_num)
{
	stwuct hfi1_ctxtdata *wcd = fwow->weq->wcd;
	stwuct hfi1_devdata *dd = wcd->dd;
	stwuct kewn_tid_node *node = &fwow->tnode[gwp_num];
	stwuct tid_gwoup *gwp = node->gwp;
	u32 wcventwy;
	u8 i, cnt = 0;

	fow (i = 0; i < gwp->size; i++) {
		wcventwy = gwp->base + i;

		if (node->map & BIT(i) || cnt >= node->cnt) {
			wcv_awway_wc_fiww(dd, wcventwy);
			continue;
		}

		hfi1_put_tid(dd, wcventwy, PT_INVAWID, 0, 0);

		gwp->used--;
		gwp->map &= ~BIT(i);
		cnt++;

		if (gwp->used == gwp->size - 1)
			tid_gwoup_move(gwp, &wcd->tid_fuww_wist,
				       &wcd->tid_used_wist);
		ewse if (!gwp->used)
			tid_gwoup_move(gwp, &wcd->tid_used_wist,
				       &wcd->tid_gwoup_wist);
	}
	if (WAWN_ON_ONCE(cnt & 1)) {
		stwuct hfi1_ctxtdata *wcd = fwow->weq->wcd;
		stwuct hfi1_devdata *dd = wcd->dd;

		dd_dev_eww(dd, "unexpected odd fwee cnt %u map 0x%x used %u",
			   cnt, gwp->map, gwp->used);
	}
}

static void kewn_pwogwam_wcvawway(stwuct tid_wdma_fwow *fwow)
{
	u32 pset_idx = 0;
	int i;

	fwow->npkts = 0;
	fwow->tidcnt = 0;
	fow (i = 0; i < fwow->tnode_cnt; i++)
		kewn_pwogwam_wcv_gwoup(fwow, i, &pset_idx);
	twace_hfi1_tid_fwow_awwoc(fwow->weq->qp, fwow->weq->setup_head, fwow);
}

/**
 * hfi1_kewn_exp_wcv_setup() - setup TID's and fwow fow one segment of a
 * TID WDMA wequest
 *
 * @weq: TID WDMA wequest fow which the segment/fwow is being set up
 * @ss: sge state, maintains state acwoss successive segments of a sge
 * @wast: set to twue aftew the wast sge segment has been pwocessed
 *
 * This function
 * (1) finds a fwee fwow entwy in the fwow ciwcuwaw buffew
 * (2) finds pages and continuous physicaw chunks constituing one segment
 *     of an sge
 * (3) awwocates TID gwoup entwies fow those chunks
 * (4) pwogwams wcvawway entwies in the hawdwawe cowwesponding to those
 *     TID's
 * (5) computes a tidawway with fowmatted TID entwies which can be sent
 *     to the sendew
 * (6) Wesewves and pwogwams HW fwows.
 * (7) It awso manages queing the QP when TID/fwow wesouwces awe not
 *     avaiwabwe.
 *
 * @weq points to stwuct tid_wdma_wequest of which the segments awe a pawt. The
 * function uses qp, wcd and seg_wen membews of @weq. In the absence of ewwows,
 * weq->fwow_idx is the index of the fwow which has been pwepawed in this
 * invocation of function caww. With fwow = &weq->fwows[weq->fwow_idx],
 * fwow->tid_entwy contains the TID awway which the sendew can use fow TID WDMA
 * sends and fwow->npkts contains numbew of packets wequiwed to send the
 * segment.
 *
 * hfi1_check_sge_awign shouwd be cawwed pwiow to cawwing this function and if
 * it signaws ewwow TID WDMA cannot be used fow this sge and this function
 * shouwd not be cawwed.
 *
 * Fow the queuing, cawwew must howd the fwow->weq->qp s_wock fwom the send
 * engine and the function wiww pwocuwe the exp_wock.
 *
 * Wetuwn:
 * The function wetuwns -EAGAIN if sufficient numbew of TID/fwow wesouwces to
 * map the segment couwd not be awwocated. In this case the function shouwd be
 * cawwed again with pwevious awguments to wetwy the TID awwocation. Thewe awe
 * no othew ewwow wetuwns. The function wetuwns 0 on success.
 */
int hfi1_kewn_exp_wcv_setup(stwuct tid_wdma_wequest *weq,
			    stwuct wvt_sge_state *ss, boow *wast)
	__must_howd(&weq->qp->s_wock)
{
	stwuct tid_wdma_fwow *fwow = &weq->fwows[weq->setup_head];
	stwuct hfi1_ctxtdata *wcd = weq->wcd;
	stwuct hfi1_qp_pwiv *qpwiv = weq->qp->pwiv;
	unsigned wong fwags;
	stwuct wvt_qp *fqp;
	u16 cweaw_taiw = weq->cweaw_taiw;

	wockdep_assewt_hewd(&weq->qp->s_wock);
	/*
	 * We wetuwn ewwow if eithew (a) we don't have space in the fwow
	 * ciwcuwaw buffew, ow (b) we awweady have max entwies in the buffew.
	 * Max entwies depend on the type of wequest we awe pwocessing and the
	 * negotiated TID WDMA pawametews.
	 */
	if (!CIWC_SPACE(weq->setup_head, cweaw_taiw, MAX_FWOWS) ||
	    CIWC_CNT(weq->setup_head, cweaw_taiw, MAX_FWOWS) >=
	    weq->n_fwows)
		wetuwn -EINVAW;

	/*
	 * Get pages, identify contiguous physicaw memowy chunks fow the segment
	 * If we can not detewmine a DMA addwess mapping we wiww tweat it just
	 * wike if we wan out of space above.
	 */
	if (kewn_get_phys_bwocks(fwow, qpwiv->pages, ss, wast)) {
		hfi1_wait_kmem(fwow->weq->qp);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&wcd->exp_wock, fwags);
	if (kewnew_tid_waitews(wcd, &wcd->waww_queue, fwow->weq->qp))
		goto queue;

	/*
	 * At this point we know the numbew of pagesets and hence the numbew of
	 * TID's to map the segment. Awwocate the TID's fwom the TID gwoups. If
	 * we cannot awwocate the wequiwed numbew we exit and twy again watew
	 */
	if (kewn_awwoc_tids(fwow))
		goto queue;
	/*
	 * Finawwy pwogwam the TID entwies with the pagesets, compute the
	 * tidawway and enabwe the HW fwow
	 */
	kewn_pwogwam_wcvawway(fwow);

	/*
	 * Setup the fwow state with wewevant infowmation.
	 * This infowmation is used fow twacking the sequence of data packets
	 * fow the segment.
	 * The fwow is setup hewe as this is the most accuwate time and pwace
	 * to do so. Doing at a watew time wuns the wisk of the fwow data in
	 * qpwiv getting out of sync.
	 */
	memset(&fwow->fwow_state, 0x0, sizeof(fwow->fwow_state));
	fwow->idx = qpwiv->fwow_state.index;
	fwow->fwow_state.genewation = qpwiv->fwow_state.genewation;
	fwow->fwow_state.spsn = qpwiv->fwow_state.psn;
	fwow->fwow_state.wpsn = fwow->fwow_state.spsn + fwow->npkts - 1;
	fwow->fwow_state.w_next_psn =
		fuww_fwow_psn(fwow, fwow->fwow_state.spsn);
	qpwiv->fwow_state.psn += fwow->npkts;

	dequeue_tid_waitew(wcd, &wcd->waww_queue, fwow->weq->qp);
	/* get head befowe dwopping wock */
	fqp = fiwst_qp(wcd, &wcd->waww_queue);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);
	tid_wdma_scheduwe_tid_wakeup(fqp);

	weq->setup_head = (weq->setup_head + 1) & (MAX_FWOWS - 1);
	wetuwn 0;
queue:
	queue_qp_fow_tid_wait(wcd, &wcd->waww_queue, fwow->weq->qp);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);
	wetuwn -EAGAIN;
}

static void hfi1_tid_wdma_weset_fwow(stwuct tid_wdma_fwow *fwow)
{
	fwow->npagesets = 0;
}

/*
 * This function is cawwed aftew one segment has been successfuwwy sent to
 * wewease the fwow and TID HW/SW wesouwces fow that segment. The segments fow a
 * TID WDMA wequest awe setup and cweawed in FIFO owdew which is managed using a
 * ciwcuwaw buffew.
 */
int hfi1_kewn_exp_wcv_cweaw(stwuct tid_wdma_wequest *weq)
	__must_howd(&weq->qp->s_wock)
{
	stwuct tid_wdma_fwow *fwow = &weq->fwows[weq->cweaw_taiw];
	stwuct hfi1_ctxtdata *wcd = weq->wcd;
	unsigned wong fwags;
	int i;
	stwuct wvt_qp *fqp;

	wockdep_assewt_hewd(&weq->qp->s_wock);
	/* Exit if we have nothing in the fwow ciwcuwaw buffew */
	if (!CIWC_CNT(weq->setup_head, weq->cweaw_taiw, MAX_FWOWS))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wcd->exp_wock, fwags);

	fow (i = 0; i < fwow->tnode_cnt; i++)
		kewn_unpwogwam_wcv_gwoup(fwow, i);
	/* To pwevent doubwe unpwogwamming */
	fwow->tnode_cnt = 0;
	/* get head befowe dwopping wock */
	fqp = fiwst_qp(wcd, &wcd->waww_queue);
	spin_unwock_iwqwestowe(&wcd->exp_wock, fwags);

	dma_unmap_fwow(fwow);

	hfi1_tid_wdma_weset_fwow(fwow);
	weq->cweaw_taiw = (weq->cweaw_taiw + 1) & (MAX_FWOWS - 1);

	if (fqp == weq->qp) {
		__twiggew_tid_waitew(fqp);
		wvt_put_qp(fqp);
	} ewse {
		tid_wdma_scheduwe_tid_wakeup(fqp);
	}

	wetuwn 0;
}

/*
 * This function is cawwed to wewease aww the tid entwies fow
 * a wequest.
 */
void hfi1_kewn_exp_wcv_cweaw_aww(stwuct tid_wdma_wequest *weq)
	__must_howd(&weq->qp->s_wock)
{
	/* Use memowy bawwiew fow pwopew owdewing */
	whiwe (CIWC_CNT(weq->setup_head, weq->cweaw_taiw, MAX_FWOWS)) {
		if (hfi1_kewn_exp_wcv_cweaw(weq))
			bweak;
	}
}

/**
 * hfi1_kewn_exp_wcv_fwee_fwows - fwee pwiviouswy awwocated fwow infowmation
 * @weq: the tid wdma wequest to be cweaned
 */
static void hfi1_kewn_exp_wcv_fwee_fwows(stwuct tid_wdma_wequest *weq)
{
	kfwee(weq->fwows);
	weq->fwows = NUWW;
}

/**
 * __twdma_cwean_swqe - cwean up fow wawge sized QPs
 * @qp: the queue patch
 * @wqe: the send wqe
 */
void __twdma_cwean_swqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	stwuct hfi1_swqe_pwiv *p = wqe->pwiv;

	hfi1_kewn_exp_wcv_fwee_fwows(&p->tid_weq);
}

/*
 * This can be cawwed at QP cweate time ow in the data path.
 */
static int hfi1_kewn_exp_wcv_awwoc_fwows(stwuct tid_wdma_wequest *weq,
					 gfp_t gfp)
{
	stwuct tid_wdma_fwow *fwows;
	int i;

	if (wikewy(weq->fwows))
		wetuwn 0;
	fwows = kmawwoc_node(MAX_FWOWS * sizeof(*fwows), gfp,
			     weq->wcd->numa_id);
	if (!fwows)
		wetuwn -ENOMEM;
	/* mini init */
	fow (i = 0; i < MAX_FWOWS; i++) {
		fwows[i].weq = weq;
		fwows[i].npagesets = 0;
		fwows[i].pagesets[0].mapped =  0;
		fwows[i].wesync_npkts = 0;
	}
	weq->fwows = fwows;
	wetuwn 0;
}

static void hfi1_init_twdma_weq(stwuct wvt_qp *qp,
				stwuct tid_wdma_wequest *weq)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;

	/*
	 * Initiawize vawious TID WDMA wequest vawiabwes.
	 * These vawiabwes awe "static", which is why they
	 * can be pwe-initiawized hewe befowe the WWs has
	 * even been submitted.
	 * Howevew, non-NUWW vawues fow these vawiabwes do not
	 * impwy that this WQE has been enabwed fow TID WDMA.
	 * Dwivews shouwd check the WQE's opcode to detewmine
	 * if a wequest is a TID WDMA one ow not.
	 */
	weq->qp = qp;
	weq->wcd = qpwiv->wcd;
}

u64 hfi1_access_sw_tid_wait(const stwuct cntw_entwy *entwy,
			    void *context, int vw, int mode, u64 data)
{
	stwuct hfi1_devdata *dd = context;

	wetuwn dd->vewbs_dev.n_tidwait;
}

static stwuct tid_wdma_fwow *find_fwow_ib(stwuct tid_wdma_wequest *weq,
					  u32 psn, u16 *fidx)
{
	u16 head, taiw;
	stwuct tid_wdma_fwow *fwow;

	head = weq->setup_head;
	taiw = weq->cweaw_taiw;
	fow ( ; CIWC_CNT(head, taiw, MAX_FWOWS);
	     taiw = CIWC_NEXT(taiw, MAX_FWOWS)) {
		fwow = &weq->fwows[taiw];
		if (cmp_psn(psn, fwow->fwow_state.ib_spsn) >= 0 &&
		    cmp_psn(psn, fwow->fwow_state.ib_wpsn) <= 0) {
			if (fidx)
				*fidx = taiw;
			wetuwn fwow;
		}
	}
	wetuwn NUWW;
}

/* TID WDMA WEAD functions */
u32 hfi1_buiwd_tid_wdma_wead_packet(stwuct wvt_swqe *wqe,
				    stwuct ib_othew_headews *ohdw, u32 *bth1,
				    u32 *bth2, u32 *wen)
{
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_fwow *fwow = &weq->fwows[weq->fwow_idx];
	stwuct wvt_qp *qp = weq->qp;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct hfi1_swqe_pwiv *wpwiv = wqe->pwiv;
	stwuct tid_wdma_wead_weq *wweq = &ohdw->u.tid_wdma.w_weq;
	stwuct tid_wdma_pawams *wemote;
	u32 weq_wen = 0;
	void *weq_addw = NUWW;

	/* This is the IB psn used to send the wequest */
	*bth2 = mask_psn(fwow->fwow_state.ib_spsn + fwow->pkt);
	twace_hfi1_tid_fwow_buiwd_wead_pkt(qp, weq->fwow_idx, fwow);

	/* TID Entwies fow TID WDMA WEAD paywoad */
	weq_addw = &fwow->tid_entwy[fwow->tid_idx];
	weq_wen = sizeof(*fwow->tid_entwy) *
			(fwow->tidcnt - fwow->tid_idx);

	memset(&ohdw->u.tid_wdma.w_weq, 0, sizeof(ohdw->u.tid_wdma.w_weq));
	wpwiv->ss.sge.vaddw = weq_addw;
	wpwiv->ss.sge.sge_wength = weq_wen;
	wpwiv->ss.sge.wength = wpwiv->ss.sge.sge_wength;
	/*
	 * We can safewy zewo these out. Since the fiwst SGE covews the
	 * entiwe packet, nothing ewse shouwd even wook at the MW.
	 */
	wpwiv->ss.sge.mw = NUWW;
	wpwiv->ss.sge.m = 0;
	wpwiv->ss.sge.n = 0;

	wpwiv->ss.sg_wist = NUWW;
	wpwiv->ss.totaw_wen = wpwiv->ss.sge.sge_wength;
	wpwiv->ss.num_sge = 1;

	/* Constwuct the TID WDMA WEAD WEQ packet headew */
	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);

	KDETH_WESET(wweq->kdeth0, KVEW, 0x1);
	KDETH_WESET(wweq->kdeth1, JKEY, wemote->jkey);
	wweq->weth.vaddw = cpu_to_be64(wqe->wdma_ww.wemote_addw +
			   weq->cuw_seg * weq->seg_wen + fwow->sent);
	wweq->weth.wkey = cpu_to_be32(wqe->wdma_ww.wkey);
	wweq->weth.wength = cpu_to_be32(*wen);
	wweq->tid_fwow_psn =
		cpu_to_be32((fwow->fwow_state.genewation <<
			     HFI1_KDETH_BTH_SEQ_SHIFT) |
			    ((fwow->fwow_state.spsn + fwow->pkt) &
			     HFI1_KDETH_BTH_SEQ_MASK));
	wweq->tid_fwow_qp =
		cpu_to_be32(qpwiv->tid_wdma.wocaw.qp |
			    ((fwow->idx & TID_WDMA_DESTQP_FWOW_MASK) <<
			     TID_WDMA_DESTQP_FWOW_SHIFT) |
			    qpwiv->wcd->ctxt);
	wweq->vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	*bth1 &= ~WVT_QPN_MASK;
	*bth1 |= wemote->qp;
	*bth2 |= IB_BTH_WEQ_ACK;
	wcu_wead_unwock();

	/* We awe done with this segment */
	fwow->sent += *wen;
	weq->cuw_seg++;
	qp->s_state = TID_OP(WEAD_WEQ);
	weq->ack_pending++;
	weq->fwow_idx = (weq->fwow_idx + 1) & (MAX_FWOWS - 1);
	qpwiv->pending_tid_w_segs++;
	qp->s_num_wd_atomic++;

	/* Set the TID WDMA WEAD wequest paywoad size */
	*wen = weq_wen;

	wetuwn sizeof(ohdw->u.tid_wdma.w_weq) / sizeof(u32);
}

/*
 * @wen: contains the data wength to wead upon entwy and the wead wequest
 *       paywoad wength upon exit.
 */
u32 hfi1_buiwd_tid_wdma_wead_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
				 stwuct ib_othew_headews *ohdw, u32 *bth1,
				 u32 *bth2, u32 *wen)
	__must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_fwow *fwow = NUWW;
	u32 hdwowds = 0;
	boow wast;
	boow wetwy = twue;
	u32 npkts = wvt_div_wound_up_mtu(qp, *wen);

	twace_hfi1_tid_weq_buiwd_wead_weq(qp, 0, wqe->ww.opcode, wqe->psn,
					  wqe->wpsn, weq);
	/*
	 * Check sync conditions. Make suwe that thewe awe no pending
	 * segments befowe fweeing the fwow.
	 */
sync_check:
	if (weq->state == TID_WEQUEST_SYNC) {
		if (qpwiv->pending_tid_w_segs)
			goto done;

		hfi1_kewn_cweaw_hw_fwow(weq->wcd, qp);
		qpwiv->s_fwags &= ~HFI1_W_TID_SW_PSN;
		weq->state = TID_WEQUEST_ACTIVE;
	}

	/*
	 * If the wequest fow this segment is wesent, the tid wesouwces shouwd
	 * have been awwocated befowe. In this case, weq->fwow_idx shouwd
	 * faww behind weq->setup_head.
	 */
	if (weq->fwow_idx == weq->setup_head) {
		wetwy = fawse;
		if (weq->state == TID_WEQUEST_WESEND) {
			/*
			 * This is the fiwst new segment fow a wequest whose
			 * eawwiew segments have been we-sent. We need to
			 * set up the sge pointew cowwectwy.
			 */
			westawt_sge(&qp->s_sge, wqe, weq->s_next_psn,
				    qp->pmtu);
			weq->isge = 0;
			weq->state = TID_WEQUEST_ACTIVE;
		}

		/*
		 * Check sync. The wast PSN of each genewation is wesewved fow
		 * WESYNC.
		 */
		if ((qpwiv->fwow_state.psn + npkts) > MAX_TID_FWOW_PSN - 1) {
			weq->state = TID_WEQUEST_SYNC;
			goto sync_check;
		}

		/* Awwocate the fwow if not yet */
		if (hfi1_kewn_setup_hw_fwow(qpwiv->wcd, qp))
			goto done;

		/*
		 * The fowwowing caww wiww advance weq->setup_head aftew
		 * awwocating the tid entwies.
		 */
		if (hfi1_kewn_exp_wcv_setup(weq, &qp->s_sge, &wast)) {
			weq->state = TID_WEQUEST_QUEUED;

			/*
			 * We don't have wesouwces fow this segment. The QP has
			 * awweady been queued.
			 */
			goto done;
		}
	}

	/* weq->fwow_idx shouwd onwy be one swot behind weq->setup_head */
	fwow = &weq->fwows[weq->fwow_idx];
	fwow->pkt = 0;
	fwow->tid_idx = 0;
	fwow->sent = 0;
	if (!wetwy) {
		/* Set the fiwst and wast IB PSN fow the fwow in use.*/
		fwow->fwow_state.ib_spsn = weq->s_next_psn;
		fwow->fwow_state.ib_wpsn =
			fwow->fwow_state.ib_spsn + fwow->npkts - 1;
	}

	/* Cawcuwate the next segment stawt psn.*/
	weq->s_next_psn += fwow->npkts;

	/* Buiwd the packet headew */
	hdwowds = hfi1_buiwd_tid_wdma_wead_packet(wqe, ohdw, bth1, bth2, wen);
done:
	wetuwn hdwowds;
}

/*
 * Vawidate and accept the TID WDMA WEAD wequest pawametews.
 * Wetuwn 0 if the wequest is accepted successfuwwy;
 * Wetuwn 1 othewwise.
 */
static int tid_wdma_wcv_wead_wequest(stwuct wvt_qp *qp,
				     stwuct wvt_ack_entwy *e,
				     stwuct hfi1_packet *packet,
				     stwuct ib_othew_headews *ohdw,
				     u32 bth0, u32 psn, u64 vaddw, u32 wen)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	u32 fwow_psn, i, tidwen = 0, pktwen, twen;

	weq = ack_to_tid_weq(e);

	/* Vawidate the paywoad fiwst */
	fwow = &weq->fwows[weq->setup_head];

	/* paywoad wength = packet wength - (headew wength + ICWC wength) */
	pktwen = packet->twen - (packet->hwen + 4);
	if (pktwen > sizeof(fwow->tid_entwy))
		wetuwn 1;
	memcpy(fwow->tid_entwy, packet->ebuf, pktwen);
	fwow->tidcnt = pktwen / sizeof(*fwow->tid_entwy);

	/*
	 * Wawk the TID_ENTWY wist to make suwe we have enough space fow a
	 * compwete segment. Awso cawcuwate the numbew of wequiwed packets.
	 */
	fwow->npkts = wvt_div_wound_up_mtu(qp, wen);
	fow (i = 0; i < fwow->tidcnt; i++) {
		twace_hfi1_tid_entwy_wcv_wead_weq(qp, i,
						  fwow->tid_entwy[i]);
		twen = EXP_TID_GET(fwow->tid_entwy[i], WEN);
		if (!twen)
			wetuwn 1;

		/*
		 * Fow tid paiw (tidctw == 3), the buffew size of the paiw
		 * shouwd be the sum of the buffew size descwibed by each
		 * tid entwy. Howevew, onwy the fiwst entwy needs to be
		 * specified in the wequest (see WFW HAS Section 8.5.7.1).
		 */
		tidwen += twen;
	}
	if (tidwen * PAGE_SIZE < wen)
		wetuwn 1;

	/* Empty the fwow awway */
	weq->cweaw_taiw = weq->setup_head;
	fwow->pkt = 0;
	fwow->tid_idx = 0;
	fwow->tid_offset = 0;
	fwow->sent = 0;
	fwow->tid_qpn = be32_to_cpu(ohdw->u.tid_wdma.w_weq.tid_fwow_qp);
	fwow->idx = (fwow->tid_qpn >> TID_WDMA_DESTQP_FWOW_SHIFT) &
		    TID_WDMA_DESTQP_FWOW_MASK;
	fwow_psn = mask_psn(be32_to_cpu(ohdw->u.tid_wdma.w_weq.tid_fwow_psn));
	fwow->fwow_state.genewation = fwow_psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
	fwow->fwow_state.spsn = fwow_psn & HFI1_KDETH_BTH_SEQ_MASK;
	fwow->wength = wen;

	fwow->fwow_state.wpsn = fwow->fwow_state.spsn +
		fwow->npkts - 1;
	fwow->fwow_state.ib_spsn = psn;
	fwow->fwow_state.ib_wpsn = fwow->fwow_state.ib_spsn + fwow->npkts - 1;

	twace_hfi1_tid_fwow_wcv_wead_weq(qp, weq->setup_head, fwow);
	/* Set the initiaw fwow index to the cuwwent fwow. */
	weq->fwow_idx = weq->setup_head;

	/* advance ciwcuwaw buffew head */
	weq->setup_head = (weq->setup_head + 1) & (MAX_FWOWS - 1);

	/*
	 * Compute wast PSN fow wequest.
	 */
	e->opcode = (bth0 >> 24) & 0xff;
	e->psn = psn;
	e->wpsn = psn + fwow->npkts - 1;
	e->sent = 0;

	weq->n_fwows = qpwiv->tid_wdma.wocaw.max_wead;
	weq->state = TID_WEQUEST_ACTIVE;
	weq->cuw_seg = 0;
	weq->comp_seg = 0;
	weq->ack_seg = 0;
	weq->isge = 0;
	weq->seg_wen = qpwiv->tid_wdma.wocaw.max_wen;
	weq->totaw_wen = wen;
	weq->totaw_segs = 1;
	weq->w_fwow_psn = e->psn;

	twace_hfi1_tid_weq_wcv_wead_weq(qp, 0, e->opcode, e->psn, e->wpsn,
					weq);
	wetuwn 0;
}

static int tid_wdma_wcv_ewwow(stwuct hfi1_packet *packet,
			      stwuct ib_othew_headews *ohdw,
			      stwuct wvt_qp *qp, u32 psn, int diff)
{
	stwuct hfi1_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct hfi1_ctxtdata *wcd = ((stwuct hfi1_qp_pwiv *)qp->pwiv)->wcd;
	stwuct hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct wvt_ack_entwy *e;
	stwuct tid_wdma_wequest *weq;
	unsigned wong fwags;
	u8 pwev;
	boow owd_weq;

	twace_hfi1_wsp_tid_wcv_ewwow(qp, psn);
	twace_hfi1_tid_wdma_wcv_eww(qp, 0, psn, diff);
	if (diff > 0) {
		/* sequence ewwow */
		if (!qp->w_nak_state) {
			ibp->wvp.n_wc_seqnak++;
			qp->w_nak_state = IB_NAK_PSN_EWWOW;
			qp->w_ack_psn = qp->w_psn;
			wc_defewed_ack(wcd, qp);
		}
		goto done;
	}

	ibp->wvp.n_wc_dupweq++;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	e = find_pwev_entwy(qp, psn, &pwev, NUWW, &owd_weq);
	if (!e || (e->opcode != TID_OP(WEAD_WEQ) &&
		   e->opcode != TID_OP(WWITE_WEQ)))
		goto unwock;

	weq = ack_to_tid_weq(e);
	weq->w_fwow_psn = psn;
	twace_hfi1_tid_weq_wcv_eww(qp, 0, e->opcode, e->psn, e->wpsn, weq);
	if (e->opcode == TID_OP(WEAD_WEQ)) {
		stwuct ib_weth *weth;
		u32 wen;
		u32 wkey;
		u64 vaddw;
		int ok;
		u32 bth0;

		weth = &ohdw->u.tid_wdma.w_weq.weth;
		/*
		 * The wequestew awways westawts fwom the stawt of the owiginaw
		 * wequest.
		 */
		wen = be32_to_cpu(weth->wength);
		if (psn != e->psn || wen != weq->totaw_wen)
			goto unwock;

		wewease_wdma_sge_mw(e);

		wkey = be32_to_cpu(weth->wkey);
		vaddw = get_ib_weth_vaddw(weth);

		qp->w_wen = wen;
		ok = wvt_wkey_ok(qp, &e->wdma_sge, wen, vaddw, wkey,
				 IB_ACCESS_WEMOTE_WEAD);
		if (unwikewy(!ok))
			goto unwock;

		/*
		 * If aww the wesponse packets fow the cuwwent wequest have
		 * been sent out and this wequest is compwete (owd_wequest
		 * == fawse) and the TID fwow may be unusabwe (the
		 * weq->cweaw_taiw is advanced). Howevew, when an eawwiew
		 * wequest is weceived, this wequest wiww not be compwete any
		 * mowe (qp->s_taiw_ack_queue is moved back, see bewow).
		 * Consequentwy, we need to update the TID fwow info evewytime
		 * a dupwicate wequest is weceived.
		 */
		bth0 = be32_to_cpu(ohdw->bth[0]);
		if (tid_wdma_wcv_wead_wequest(qp, e, packet, ohdw, bth0, psn,
					      vaddw, wen))
			goto unwock;

		/*
		 * Twue if the wequest is awweady scheduwed (between
		 * qp->s_taiw_ack_queue and qp->w_head_ack_queue);
		 */
		if (owd_weq)
			goto unwock;
	} ewse {
		stwuct fwow_state *fstate;
		boow scheduwe = fawse;
		u8 i;

		if (weq->state == TID_WEQUEST_WESEND) {
			weq->state = TID_WEQUEST_WESEND_ACTIVE;
		} ewse if (weq->state == TID_WEQUEST_INIT_WESEND) {
			weq->state = TID_WEQUEST_INIT;
			scheduwe = twue;
		}

		/*
		 * Twue if the wequest is awweady scheduwed (between
		 * qp->s_taiw_ack_queue and qp->w_head_ack_queue).
		 * Awso, don't change wequests, which awe at the SYNC
		 * point and haven't genewated any wesponses yet.
		 * Thewe is nothing to wetwansmit fow them yet.
		 */
		if (owd_weq || weq->state == TID_WEQUEST_INIT ||
		    (weq->state == TID_WEQUEST_SYNC && !weq->cuw_seg)) {
			fow (i = pwev + 1; ; i++) {
				if (i > wvt_size_atomic(&dev->wdi))
					i = 0;
				if (i == qp->w_head_ack_queue)
					bweak;
				e = &qp->s_ack_queue[i];
				weq = ack_to_tid_weq(e);
				if (e->opcode == TID_OP(WWITE_WEQ) &&
				    weq->state == TID_WEQUEST_INIT)
					weq->state = TID_WEQUEST_INIT_WESEND;
			}
			/*
			 * If the state of the wequest has been changed,
			 * the fiwst weg needs to get scheduwed in owdew to
			 * pick up the change. Othewwise, nowmaw wesponse
			 * pwocessing shouwd take cawe of it.
			 */
			if (!scheduwe)
				goto unwock;
		}

		/*
		 * If thewe is no mowe awwocated segment, just scheduwe the qp
		 * without changing any state.
		 */
		if (weq->cweaw_taiw == weq->setup_head)
			goto scheduwe;
		/*
		 * If this wequest has sent wesponses fow segments, which have
		 * not weceived data yet (fwow_idx != cweaw_taiw), the fwow_idx
		 * pointew needs to be adjusted so the same wesponses can be
		 * we-sent.
		 */
		if (CIWC_CNT(weq->fwow_idx, weq->cweaw_taiw, MAX_FWOWS)) {
			fstate = &weq->fwows[weq->cweaw_taiw].fwow_state;
			qpwiv->pending_tid_w_segs -=
				CIWC_CNT(weq->fwow_idx, weq->cweaw_taiw,
					 MAX_FWOWS);
			weq->fwow_idx =
				CIWC_ADD(weq->cweaw_taiw,
					 dewta_psn(psn, fstate->wesp_ib_psn),
					 MAX_FWOWS);
			qpwiv->pending_tid_w_segs +=
				dewta_psn(psn, fstate->wesp_ib_psn);
			/*
			 * When fwow_idx == setup_head, we've gotten a dupwicate
			 * wequest fow a segment, which has not been awwocated
			 * yet. In that case, don't adjust this wequest.
			 * Howevew, we stiww want to go thwough the woop bewow
			 * to adjust aww subsequent wequests.
			 */
			if (CIWC_CNT(weq->setup_head, weq->fwow_idx,
				     MAX_FWOWS)) {
				weq->cuw_seg = dewta_psn(psn, e->psn);
				weq->state = TID_WEQUEST_WESEND_ACTIVE;
			}
		}

		fow (i = pwev + 1; ; i++) {
			/*
			 * Wook at evewything up to and incwuding
			 * s_taiw_ack_queue
			 */
			if (i > wvt_size_atomic(&dev->wdi))
				i = 0;
			if (i == qp->w_head_ack_queue)
				bweak;
			e = &qp->s_ack_queue[i];
			weq = ack_to_tid_weq(e);
			twace_hfi1_tid_weq_wcv_eww(qp, 0, e->opcode, e->psn,
						   e->wpsn, weq);
			if (e->opcode != TID_OP(WWITE_WEQ) ||
			    weq->cuw_seg == weq->comp_seg ||
			    weq->state == TID_WEQUEST_INIT ||
			    weq->state == TID_WEQUEST_INIT_WESEND) {
				if (weq->state == TID_WEQUEST_INIT)
					weq->state = TID_WEQUEST_INIT_WESEND;
				continue;
			}
			qpwiv->pending_tid_w_segs -=
				CIWC_CNT(weq->fwow_idx,
					 weq->cweaw_taiw,
					 MAX_FWOWS);
			weq->fwow_idx = weq->cweaw_taiw;
			weq->state = TID_WEQUEST_WESEND;
			weq->cuw_seg = weq->comp_seg;
		}
		qpwiv->s_fwags &= ~HFI1_W_TID_WAIT_INTEWWCK;
	}
	/* We-pwocess owd wequests.*/
	if (qp->s_acked_ack_queue == qp->s_taiw_ack_queue)
		qp->s_acked_ack_queue = pwev;
	qp->s_taiw_ack_queue = pwev;
	/*
	 * Since the qp->s_taiw_ack_queue is modified, the
	 * qp->s_ack_state must be changed to we-initiawize
	 * qp->s_ack_wdma_sge; Othewwise, we wiww end up in
	 * wwong memowy wegion.
	 */
	qp->s_ack_state = OP(ACKNOWWEDGE);
scheduwe:
	/*
	 * It's possibwe to weceive a wetwy psn that is eawwiew than an WNWNAK
	 * psn. In this case, the wnwnak state shouwd be cweawed.
	 */
	if (qpwiv->wnw_nak_state) {
		qp->s_nak_state = 0;
		qpwiv->wnw_nak_state = TID_WNW_NAK_INIT;
		qp->w_psn = e->wpsn + 1;
		hfi1_tid_wwite_awwoc_wesouwces(qp, twue);
	}

	qp->w_state = e->opcode;
	qp->w_nak_state = 0;
	qp->s_fwags |= WVT_S_WESP_PENDING;
	hfi1_scheduwe_send(qp);
unwock:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
done:
	wetuwn 1;
}

void hfi1_wc_wcv_tid_wdma_wead_weq(stwuct hfi1_packet *packet)
{
	/* HANDWEW FOW TID WDMA WEAD WEQUEST packet (Wespondew side)*/

	/*
	 * 1. Vewify TID WDMA WEAD WEQ as pew IB_OPCODE_WC_WDMA_WEAD
	 *    (see hfi1_wc_wcv())
	 * 2. Put TID WDMA WEAD WEQ into the wesponse queueu (s_ack_queue)
	 *     - Setup stwuct tid_wdma_weq with wequest info
	 *     - Initiawize stwuct tid_wdma_fwow info;
	 *     - Copy TID entwies;
	 * 3. Set the qp->s_ack_state.
	 * 4. Set WVT_S_WESP_PENDING in s_fwags.
	 * 5. Kick the send engine (hfi1_scheduwe_send())
	 */
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_ack_entwy *e;
	unsigned wong fwags;
	stwuct ib_weth *weth;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	u32 bth0, psn, wen, wkey;
	boow fecn;
	u8 next;
	u64 vaddw;
	int diff;
	u8 nack_state = IB_NAK_INVAWID_WEQUEST;

	bth0 = be32_to_cpu(ohdw->bth[0]);
	if (hfi1_wuc_check_hdw(ibp, packet))
		wetuwn;

	fecn = pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	twace_hfi1_wsp_wcv_tid_wead_weq(qp, psn);

	if (qp->state == IB_QPS_WTW && !(qp->w_fwags & WVT_W_COMM_EST))
		wvt_comm_est(qp);

	if (unwikewy(!(qp->qp_access_fwags & IB_ACCESS_WEMOTE_WEAD)))
		goto nack_inv;

	weth = &ohdw->u.tid_wdma.w_weq.weth;
	vaddw = be64_to_cpu(weth->vaddw);
	wen = be32_to_cpu(weth->wength);
	/* The wength needs to be in muwtipwes of PAGE_SIZE */
	if (!wen || wen & ~PAGE_MASK || wen > qpwiv->tid_wdma.wocaw.max_wen)
		goto nack_inv;

	diff = dewta_psn(psn, qp->w_psn);
	if (unwikewy(diff)) {
		tid_wdma_wcv_eww(packet, ohdw, qp, psn, diff, fecn);
		wetuwn;
	}

	/* We've vewified the wequest, insewt it into the ack queue. */
	next = qp->w_head_ack_queue + 1;
	if (next > wvt_size_atomic(ib_to_wvt(qp->ibqp.device)))
		next = 0;
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (unwikewy(next == qp->s_taiw_ack_queue)) {
		if (!qp->s_ack_queue[next].sent) {
			nack_state = IB_NAK_WEMOTE_OPEWATIONAW_EWWOW;
			goto nack_inv_unwock;
		}
		update_ack_queue(qp, next);
	}
	e = &qp->s_ack_queue[qp->w_head_ack_queue];
	wewease_wdma_sge_mw(e);

	wkey = be32_to_cpu(weth->wkey);
	qp->w_wen = wen;

	if (unwikewy(!wvt_wkey_ok(qp, &e->wdma_sge, qp->w_wen, vaddw,
				  wkey, IB_ACCESS_WEMOTE_WEAD)))
		goto nack_acc;

	/* Accept the wequest pawametews */
	if (tid_wdma_wcv_wead_wequest(qp, e, packet, ohdw, bth0, psn, vaddw,
				      wen))
		goto nack_inv_unwock;

	qp->w_state = e->opcode;
	qp->w_nak_state = 0;
	/*
	 * We need to incwement the MSN hewe instead of when we
	 * finish sending the wesuwt since a dupwicate wequest wouwd
	 * incwement it mowe than once.
	 */
	qp->w_msn++;
	qp->w_psn += e->wpsn - e->psn + 1;

	qp->w_head_ack_queue = next;

	/*
	 * Fow aww wequests othew than TID WWITE which awe added to the ack
	 * queue, qpwiv->w_tid_awwoc fowwows qp->w_head_ack_queue. It is ok to
	 * do this because of intewwocks between these and TID WWITE
	 * wequests. The same change has awso been made in hfi1_wc_wcv().
	 */
	qpwiv->w_tid_awwoc = qp->w_head_ack_queue;

	/* Scheduwe the send taskwet. */
	qp->s_fwags |= WVT_S_WESP_PENDING;
	if (fecn)
		qp->s_fwags |= WVT_S_ECN;
	hfi1_scheduwe_send(qp);

	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wetuwn;

nack_inv_unwock:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
nack_inv:
	wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
	qp->w_nak_state = nack_state;
	qp->w_ack_psn = qp->w_psn;
	/* Queue NAK fow watew */
	wc_defewed_ack(wcd, qp);
	wetuwn;
nack_acc:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wvt_wc_ewwow(qp, IB_WC_WOC_PWOT_EWW);
	qp->w_nak_state = IB_NAK_WEMOTE_ACCESS_EWWOW;
	qp->w_ack_psn = qp->w_psn;
}

u32 hfi1_buiwd_tid_wdma_wead_wesp(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				  stwuct ib_othew_headews *ohdw, u32 *bth0,
				  u32 *bth1, u32 *bth2, u32 *wen, boow *wast)
{
	stwuct hfi1_ack_pwiv *epwiv = e->pwiv;
	stwuct tid_wdma_wequest *weq = &epwiv->tid_weq;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_fwow *fwow = &weq->fwows[weq->cweaw_taiw];
	u32 tidentwy = fwow->tid_entwy[fwow->tid_idx];
	u32 tidwen = EXP_TID_GET(tidentwy, WEN) << PAGE_SHIFT;
	stwuct tid_wdma_wead_wesp *wesp = &ohdw->u.tid_wdma.w_wsp;
	u32 next_offset, om = KDETH_OM_WAWGE;
	boow wast_pkt;
	u32 hdwowds = 0;
	stwuct tid_wdma_pawams *wemote;

	*wen = min_t(u32, qp->pmtu, tidwen - fwow->tid_offset);
	fwow->sent += *wen;
	next_offset = fwow->tid_offset + *wen;
	wast_pkt = (fwow->sent >= fwow->wength);

	twace_hfi1_tid_entwy_buiwd_wead_wesp(qp, fwow->tid_idx, tidentwy);
	twace_hfi1_tid_fwow_buiwd_wead_wesp(qp, weq->cweaw_taiw, fwow);

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	if (!wemote) {
		wcu_wead_unwock();
		goto done;
	}
	KDETH_WESET(wesp->kdeth0, KVEW, 0x1);
	KDETH_SET(wesp->kdeth0, SH, !wast_pkt);
	KDETH_SET(wesp->kdeth0, INTW, !!(!wast_pkt && wemote->uwg));
	KDETH_SET(wesp->kdeth0, TIDCTWW, EXP_TID_GET(tidentwy, CTWW));
	KDETH_SET(wesp->kdeth0, TID, EXP_TID_GET(tidentwy, IDX));
	KDETH_SET(wesp->kdeth0, OM, om == KDETH_OM_WAWGE);
	KDETH_SET(wesp->kdeth0, OFFSET, fwow->tid_offset / om);
	KDETH_WESET(wesp->kdeth1, JKEY, wemote->jkey);
	wesp->vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	wcu_wead_unwock();

	wesp->aeth = wvt_compute_aeth(qp);
	wesp->vewbs_psn = cpu_to_be32(mask_psn(fwow->fwow_state.ib_spsn +
					       fwow->pkt));

	*bth0 = TID_OP(WEAD_WESP) << 24;
	*bth1 = fwow->tid_qpn;
	*bth2 = mask_psn(((fwow->fwow_state.spsn + fwow->pkt++) &
			  HFI1_KDETH_BTH_SEQ_MASK) |
			 (fwow->fwow_state.genewation <<
			  HFI1_KDETH_BTH_SEQ_SHIFT));
	*wast = wast_pkt;
	if (wast_pkt)
		/* Advance to next fwow */
		weq->cweaw_taiw = (weq->cweaw_taiw + 1) &
				  (MAX_FWOWS - 1);

	if (next_offset >= tidwen) {
		fwow->tid_offset = 0;
		fwow->tid_idx++;
	} ewse {
		fwow->tid_offset = next_offset;
	}

	hdwowds = sizeof(ohdw->u.tid_wdma.w_wsp) / sizeof(u32);

done:
	wetuwn hdwowds;
}

static inwine stwuct tid_wdma_wequest *
find_tid_wequest(stwuct wvt_qp *qp, u32 psn, enum ib_ww_opcode opcode)
	__must_howd(&qp->s_wock)
{
	stwuct wvt_swqe *wqe;
	stwuct tid_wdma_wequest *weq = NUWW;
	u32 i, end;

	end = qp->s_cuw + 1;
	if (end == qp->s_size)
		end = 0;
	fow (i = qp->s_acked; i != end;) {
		wqe = wvt_get_swqe_ptw(qp, i);
		if (cmp_psn(psn, wqe->psn) >= 0 &&
		    cmp_psn(psn, wqe->wpsn) <= 0) {
			if (wqe->ww.opcode == opcode)
				weq = wqe_to_tid_weq(wqe);
			bweak;
		}
		if (++i == qp->s_size)
			i = 0;
	}

	wetuwn weq;
}

void hfi1_wc_wcv_tid_wdma_wead_wesp(stwuct hfi1_packet *packet)
{
	/* HANDWEW FOW TID WDMA WEAD WESPONSE packet (Wequestow side */

	/*
	 * 1. Find matching SWQE
	 * 2. Check that the entiwe segment has been wead.
	 * 3. Wemove HFI1_S_WAIT_TID_WESP fwom s_fwags.
	 * 4. Fwee the TID fwow wesouwces.
	 * 5. Kick the send engine (hfi1_scheduwe_send())
	 */
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	u32 opcode, aeth;
	boow fecn;
	unsigned wong fwags;
	u32 kpsn, ipsn;

	twace_hfi1_sendew_wcv_tid_wead_wesp(qp);
	fecn = pwocess_ecn(qp, packet);
	kpsn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	aeth = be32_to_cpu(ohdw->u.tid_wdma.w_wsp.aeth);
	opcode = (be32_to_cpu(ohdw->bth[0]) >> 24) & 0xff;

	spin_wock_iwqsave(&qp->s_wock, fwags);
	ipsn = mask_psn(be32_to_cpu(ohdw->u.tid_wdma.w_wsp.vewbs_psn));
	weq = find_tid_wequest(qp, ipsn, IB_WW_TID_WDMA_WEAD);
	if (unwikewy(!weq))
		goto ack_op_eww;

	fwow = &weq->fwows[weq->cweaw_taiw];
	/* When headew suppwession is disabwed */
	if (cmp_psn(ipsn, fwow->fwow_state.ib_wpsn)) {
		update_w_next_psn_fecn(packet, pwiv, wcd, fwow, fecn);

		if (cmp_psn(kpsn, fwow->fwow_state.w_next_psn))
			goto ack_done;
		fwow->fwow_state.w_next_psn = mask_psn(kpsn + 1);
		/*
		 * Copy the paywoad to destination buffew if this packet is
		 * dewivewed as an eagew packet due to WSM wuwe and FECN.
		 * The WSM wuwe sewects FECN bit in BTH and SH bit in
		 * KDETH headew and thewefowe wiww not match the wast
		 * packet of each segment that has SH bit cweawed.
		 */
		if (fecn && packet->etype == WHF_WCV_TYPE_EAGEW) {
			stwuct wvt_sge_state ss;
			u32 wen;
			u32 twen = packet->twen;
			u16 hdwsize = packet->hwen;
			u8 pad = packet->pad;
			u8 extwa_bytes = pad + packet->extwa_byte +
				(SIZE_OF_CWC << 2);
			u32 pmtu = qp->pmtu;

			if (unwikewy(twen != (hdwsize + pmtu + extwa_bytes)))
				goto ack_op_eww;
			wen = westawt_sge(&ss, weq->e.swqe, ipsn, pmtu);
			if (unwikewy(wen < pmtu))
				goto ack_op_eww;
			wvt_copy_sge(qp, &ss, packet->paywoad, pmtu, fawse,
				     fawse);
			/* Waise the sw sequence check fwag fow next packet */
			pwiv->s_fwags |= HFI1_W_TID_SW_PSN;
		}

		goto ack_done;
	}
	fwow->fwow_state.w_next_psn = mask_psn(kpsn + 1);
	weq->ack_pending--;
	pwiv->pending_tid_w_segs--;
	qp->s_num_wd_atomic--;
	if ((qp->s_fwags & WVT_S_WAIT_FENCE) &&
	    !qp->s_num_wd_atomic) {
		qp->s_fwags &= ~(WVT_S_WAIT_FENCE |
				 WVT_S_WAIT_ACK);
		hfi1_scheduwe_send(qp);
	}
	if (qp->s_fwags & WVT_S_WAIT_WDMAW) {
		qp->s_fwags &= ~(WVT_S_WAIT_WDMAW | WVT_S_WAIT_ACK);
		hfi1_scheduwe_send(qp);
	}

	twace_hfi1_ack(qp, ipsn);
	twace_hfi1_tid_weq_wcv_wead_wesp(qp, 0, weq->e.swqe->ww.opcode,
					 weq->e.swqe->psn, weq->e.swqe->wpsn,
					 weq);
	twace_hfi1_tid_fwow_wcv_wead_wesp(qp, weq->cweaw_taiw, fwow);

	/* Wewease the tid wesouwces */
	hfi1_kewn_exp_wcv_cweaw(weq);

	if (!do_wc_ack(qp, aeth, ipsn, opcode, 0, wcd))
		goto ack_done;

	/* If not done yet, buiwd next wead wequest */
	if (++weq->comp_seg >= weq->totaw_segs) {
		pwiv->tid_w_comp++;
		weq->state = TID_WEQUEST_COMPWETE;
	}

	/*
	 * Cweaw the hw fwow undew two conditions:
	 * 1. This wequest is a sync point and it is compwete;
	 * 2. Cuwwent wequest is compweted and thewe awe no mowe wequests.
	 */
	if ((weq->state == TID_WEQUEST_SYNC &&
	     weq->comp_seg == weq->cuw_seg) ||
	    pwiv->tid_w_comp == pwiv->tid_w_weqs) {
		hfi1_kewn_cweaw_hw_fwow(pwiv->wcd, qp);
		pwiv->s_fwags &= ~HFI1_W_TID_SW_PSN;
		if (weq->state == TID_WEQUEST_SYNC)
			weq->state = TID_WEQUEST_ACTIVE;
	}

	hfi1_scheduwe_send(qp);
	goto ack_done;

ack_op_eww:
	/*
	 * The test indicates that the send engine has finished its cweanup
	 * aftew sending the wequest and it's now safe to put the QP into ewwow
	 * state. Howevew, if the wqe queue is empty (qp->s_acked == qp->s_taiw
	 * == qp->s_head), it wouwd be unsafe to compwete the wqe pointed by
	 * qp->s_acked hewe. Putting the qp into ewwow state wiww safewy fwush
	 * aww wemaining wequests.
	 */
	if (qp->s_wast == qp->s_acked)
		wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);

ack_done:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}

void hfi1_kewn_wead_tid_fwow_fwee(stwuct wvt_qp *qp)
	__must_howd(&qp->s_wock)
{
	u32 n = qp->s_acked;
	stwuct wvt_swqe *wqe;
	stwuct tid_wdma_wequest *weq;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	wockdep_assewt_hewd(&qp->s_wock);
	/* Fwee any TID entwies */
	whiwe (n != qp->s_taiw) {
		wqe = wvt_get_swqe_ptw(qp, n);
		if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD) {
			weq = wqe_to_tid_weq(wqe);
			hfi1_kewn_exp_wcv_cweaw_aww(weq);
		}

		if (++n == qp->s_size)
			n = 0;
	}
	/* Fwee fwow */
	hfi1_kewn_cweaw_hw_fwow(pwiv->wcd, qp);
}

static boow tid_wdma_tid_eww(stwuct hfi1_packet *packet, u8 wcv_type)
{
	stwuct wvt_qp *qp = packet->qp;

	if (wcv_type >= WHF_WCV_TYPE_IB)
		goto done;

	spin_wock(&qp->s_wock);

	/*
	 * We've wan out of space in the eagew buffew.
	 * Eagewwy weceived KDETH packets which wequiwe space in the
	 * Eagew buffew (packet that have paywoad) awe TID WDMA WWITE
	 * wesponse packets. In this case, we have to we-twansmit the
	 * TID WDMA WWITE wequest.
	 */
	if (wcv_type == WHF_WCV_TYPE_EAGEW) {
		hfi1_westawt_wc(qp, qp->s_wast_psn + 1, 1);
		hfi1_scheduwe_send(qp);
	}

	/* Since no paywoad is dewivewed, just dwop the packet */
	spin_unwock(&qp->s_wock);
done:
	wetuwn twue;
}

static void westawt_tid_wdma_wead_weq(stwuct hfi1_ctxtdata *wcd,
				      stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;

	/* Stawt fwom the wight segment */
	qp->w_fwags |= WVT_W_WDMAW_SEQ;
	weq = wqe_to_tid_weq(wqe);
	fwow = &weq->fwows[weq->cweaw_taiw];
	hfi1_westawt_wc(qp, fwow->fwow_state.ib_spsn, 0);
	if (wist_empty(&qp->wspwait)) {
		qp->w_fwags |= WVT_W_WSP_SEND;
		wvt_get_qp(qp);
		wist_add_taiw(&qp->wspwait, &wcd->qp_wait_wist);
	}
}

/*
 * Handwe the KDETH efwags fow TID WDMA WEAD wesponse.
 *
 * Wetuwn twue if the wast packet fow a segment has been weceived and it is
 * time to pwocess the wesponse nowmawwy; othewwise, wetuwn twue.
 *
 * The cawwew must howd the packet->qp->w_wock and the wcu_wead_wock.
 */
static boow handwe_wead_kdeth_efwags(stwuct hfi1_ctxtdata *wcd,
				     stwuct hfi1_packet *packet, u8 wcv_type,
				     u8 wte, u32 psn, u32 ibpsn)
	__must_howd(&packet->qp->w_wock) __must_howd(WCU)
{
	stwuct hfi1_ppowtdata *ppd = wcd->ppd;
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct hfi1_ibpowt *ibp;
	stwuct wvt_swqe *wqe;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	u32 ack_psn;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	boow wet = twue;
	int diff = 0;
	u32 fpsn;

	wockdep_assewt_hewd(&qp->w_wock);
	twace_hfi1_wsp_wead_kdeth_efwags(qp, ibpsn);
	twace_hfi1_sendew_wead_kdeth_efwags(qp);
	twace_hfi1_tid_wead_sendew_kdeth_efwags(qp, 0);
	spin_wock(&qp->s_wock);
	/* If the psn is out of vawid wange, dwop the packet */
	if (cmp_psn(ibpsn, qp->s_wast_psn) < 0 ||
	    cmp_psn(ibpsn, qp->s_psn) > 0)
		goto s_unwock;

	/*
	 * Note that NAKs impwicitwy ACK outstanding SEND and WDMA wwite
	 * wequests and impwicitwy NAK WDMA wead and atomic wequests issued
	 * befowe the NAK'ed wequest.
	 */
	ack_psn = ibpsn - 1;
	wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);

	/* Compwete WQEs that the PSN finishes. */
	whiwe ((int)dewta_psn(ack_psn, wqe->wpsn) >= 0) {
		/*
		 * If this wequest is a WDMA wead ow atomic, and the NACK is
		 * fow a watew opewation, this NACK NAKs the WDMA wead ow
		 * atomic.
		 */
		if (wqe->ww.opcode == IB_WW_WDMA_WEAD ||
		    wqe->ww.opcode == IB_WW_TID_WDMA_WEAD ||
		    wqe->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP ||
		    wqe->ww.opcode == IB_WW_ATOMIC_FETCH_AND_ADD) {
			/* Wetwy this wequest. */
			if (!(qp->w_fwags & WVT_W_WDMAW_SEQ)) {
				qp->w_fwags |= WVT_W_WDMAW_SEQ;
				if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD) {
					westawt_tid_wdma_wead_weq(wcd, qp,
								  wqe);
				} ewse {
					hfi1_westawt_wc(qp, qp->s_wast_psn + 1,
							0);
					if (wist_empty(&qp->wspwait)) {
						qp->w_fwags |= WVT_W_WSP_SEND;
						wvt_get_qp(qp);
						wist_add_taiw(/* wait */
						   &qp->wspwait,
						   &wcd->qp_wait_wist);
					}
				}
			}
			/*
			 * No need to pwocess the NAK since we awe
			 * westawting an eawwiew wequest.
			 */
			bweak;
		}

		wqe = do_wc_compwetion(qp, wqe, ibp);
		if (qp->s_acked == qp->s_taiw)
			goto s_unwock;
	}

	if (qp->s_acked == qp->s_taiw)
		goto s_unwock;

	/* Handwe the efwags fow the wequest */
	if (wqe->ww.opcode != IB_WW_TID_WDMA_WEAD)
		goto s_unwock;

	weq = wqe_to_tid_weq(wqe);
	twace_hfi1_tid_weq_wead_kdeth_efwags(qp, 0, wqe->ww.opcode, wqe->psn,
					     wqe->wpsn, weq);
	switch (wcv_type) {
	case WHF_WCV_TYPE_EXPECTED:
		switch (wte) {
		case WHF_WTE_EXPECTED_FWOW_SEQ_EWW:
			/*
			 * On the fiwst occuwwence of a Fwow Sequence ewwow,
			 * the fwag TID_FWOW_SW_PSN is set.
			 *
			 * Aftew that, the fwow is *not* wepwogwammed and the
			 * pwotocow fawws back to SW PSN checking. This is done
			 * to pwevent continuous Fwow Sequence ewwows fow any
			 * packets that couwd be stiww in the fabwic.
			 */
			fwow = &weq->fwows[weq->cweaw_taiw];
			twace_hfi1_tid_fwow_wead_kdeth_efwags(qp,
							      weq->cweaw_taiw,
							      fwow);
			if (pwiv->s_fwags & HFI1_W_TID_SW_PSN) {
				diff = cmp_psn(psn,
					       fwow->fwow_state.w_next_psn);
				if (diff > 0) {
					/* Dwop the packet.*/
					goto s_unwock;
				} ewse if (diff < 0) {
					/*
					 * If a wesponse packet fow a westawted
					 * wequest has come back, weset the
					 * westawt fwag.
					 */
					if (qp->w_fwags & WVT_W_WDMAW_SEQ)
						qp->w_fwags &=
							~WVT_W_WDMAW_SEQ;

					/* Dwop the packet.*/
					goto s_unwock;
				}

				/*
				 * If SW PSN vewification is successfuw and
				 * this is the wast packet in the segment, teww
				 * the cawwew to pwocess it as a nowmaw packet.
				 */
				fpsn = fuww_fwow_psn(fwow,
						     fwow->fwow_state.wpsn);
				if (cmp_psn(fpsn, psn) == 0) {
					wet = fawse;
					if (qp->w_fwags & WVT_W_WDMAW_SEQ)
						qp->w_fwags &=
							~WVT_W_WDMAW_SEQ;
				}
				fwow->fwow_state.w_next_psn =
					mask_psn(psn + 1);
			} ewse {
				u32 wast_psn;

				wast_psn = wead_w_next_psn(dd, wcd->ctxt,
							   fwow->idx);
				fwow->fwow_state.w_next_psn = wast_psn;
				pwiv->s_fwags |= HFI1_W_TID_SW_PSN;
				/*
				 * If no wequest has been westawted yet,
				 * westawt the cuwwent one.
				 */
				if (!(qp->w_fwags & WVT_W_WDMAW_SEQ))
					westawt_tid_wdma_wead_weq(wcd, qp,
								  wqe);
			}

			bweak;

		case WHF_WTE_EXPECTED_FWOW_GEN_EWW:
			/*
			 * Since the TID fwow is abwe to wide thwough
			 * genewation mismatch, dwop this stawe packet.
			 */
			bweak;

		defauwt:
			bweak;
		}
		bweak;

	case WHF_WCV_TYPE_EWWOW:
		switch (wte) {
		case WHF_WTE_EWWOW_OP_CODE_EWW:
		case WHF_WTE_EWWOW_KHDW_MIN_WEN_EWW:
		case WHF_WTE_EWWOW_KHDW_HCWC_EWW:
		case WHF_WTE_EWWOW_KHDW_KVEW_EWW:
		case WHF_WTE_EWWOW_CONTEXT_EWW:
		case WHF_WTE_EWWOW_KHDW_TID_EWW:
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
s_unwock:
	spin_unwock(&qp->s_wock);
	wetuwn wet;
}

boow hfi1_handwe_kdeth_efwags(stwuct hfi1_ctxtdata *wcd,
			      stwuct hfi1_ppowtdata *ppd,
			      stwuct hfi1_packet *packet)
{
	stwuct hfi1_ibpowt *ibp = &ppd->ibpowt_data;
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct wvt_dev_info *wdi = &dd->vewbs_dev.wdi;
	u8 wcv_type = whf_wcv_type(packet->whf);
	u8 wte = whf_wcv_type_eww(packet->whf);
	stwuct ib_headew *hdw = packet->hdw;
	stwuct ib_othew_headews *ohdw = NUWW;
	int wnh = be16_to_cpu(hdw->wwh[0]) & 3;
	u16 wid  = be16_to_cpu(hdw->wwh[1]);
	u8 opcode;
	u32 qp_num, psn, ibpsn;
	stwuct wvt_qp *qp;
	stwuct hfi1_qp_pwiv *qpwiv;
	unsigned wong fwags;
	boow wet = twue;
	stwuct wvt_ack_entwy *e;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	int diff = 0;

	twace_hfi1_msg_handwe_kdeth_efwags(NUWW, "Kdeth ewwow: whf ",
					   packet->whf);
	if (packet->whf & WHF_ICWC_EWW)
		wetuwn wet;

	packet->ohdw = &hdw->u.oth;
	ohdw = packet->ohdw;
	twace_input_ibhdw(wcd->dd, packet, !!(whf_dc_info(packet->whf)));

	/* Get the destination QP numbew. */
	qp_num = be32_to_cpu(ohdw->u.tid_wdma.w_wsp.vewbs_qp) &
		WVT_QPN_MASK;
	if (wid >= be16_to_cpu(IB_MUWTICAST_WID_BASE))
		goto dwop;

	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	opcode = (be32_to_cpu(ohdw->bth[0]) >> 24) & 0xff;

	wcu_wead_wock();
	qp = wvt_wookup_qpn(wdi, &ibp->wvp, qp_num);
	if (!qp)
		goto wcu_unwock;

	packet->qp = qp;

	/* Check fow vawid weceive state. */
	spin_wock_iwqsave(&qp->w_wock, fwags);
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK)) {
		ibp->wvp.n_pkt_dwops++;
		goto w_unwock;
	}

	if (packet->whf & WHF_TID_EWW) {
		/* Fow TIDEWW and WC QPs pweemptivewy scheduwe a NAK */
		u32 twen = whf_pkt_wen(packet->whf); /* in bytes */

		/* Sanity check packet */
		if (twen < 24)
			goto w_unwock;

		/*
		 * Check fow GWH. We shouwd nevew get packets with GWH in this
		 * path.
		 */
		if (wnh == HFI1_WWH_GWH)
			goto w_unwock;

		if (tid_wdma_tid_eww(packet, wcv_type))
			goto w_unwock;
	}

	/* handwe TID WDMA WEAD */
	if (opcode == TID_OP(WEAD_WESP)) {
		ibpsn = be32_to_cpu(ohdw->u.tid_wdma.w_wsp.vewbs_psn);
		ibpsn = mask_psn(ibpsn);
		wet = handwe_wead_kdeth_efwags(wcd, packet, wcv_type, wte, psn,
					       ibpsn);
		goto w_unwock;
	}

	/*
	 * qp->s_taiw_ack_queue points to the wvt_ack_entwy cuwwentwy being
	 * pwocessed. These a compweted sequentiawwy so we can be suwe that
	 * the pointew wiww not change untiw the entiwe wequest has compweted.
	 */
	spin_wock(&qp->s_wock);
	qpwiv = qp->pwiv;
	if (qpwiv->w_tid_taiw == HFI1_QP_WQE_INVAWID ||
	    qpwiv->w_tid_taiw == qpwiv->w_tid_head)
		goto unwock;
	e = &qp->s_ack_queue[qpwiv->w_tid_taiw];
	if (e->opcode != TID_OP(WWITE_WEQ))
		goto unwock;
	weq = ack_to_tid_weq(e);
	if (weq->comp_seg == weq->cuw_seg)
		goto unwock;
	fwow = &weq->fwows[weq->cweaw_taiw];
	twace_hfi1_efwags_eww_wwite(qp, wcv_type, wte, psn);
	twace_hfi1_wsp_handwe_kdeth_efwags(qp, psn);
	twace_hfi1_tid_wwite_wsp_handwe_kdeth_efwags(qp);
	twace_hfi1_tid_weq_handwe_kdeth_efwags(qp, 0, e->opcode, e->psn,
					       e->wpsn, weq);
	twace_hfi1_tid_fwow_handwe_kdeth_efwags(qp, weq->cweaw_taiw, fwow);

	switch (wcv_type) {
	case WHF_WCV_TYPE_EXPECTED:
		switch (wte) {
		case WHF_WTE_EXPECTED_FWOW_SEQ_EWW:
			if (!(qpwiv->s_fwags & HFI1_W_TID_SW_PSN)) {
				qpwiv->s_fwags |= HFI1_W_TID_SW_PSN;
				fwow->fwow_state.w_next_psn =
					wead_w_next_psn(dd, wcd->ctxt,
							fwow->idx);
				qpwiv->w_next_psn_kdeth =
					fwow->fwow_state.w_next_psn;
				goto nak_psn;
			} ewse {
				/*
				 * If the weceived PSN does not match the next
				 * expected PSN, NAK the packet.
				 * Howevew, onwy do that if we know that the a
				 * NAK has awweady been sent. Othewwise, this
				 * mismatch couwd be due to packets that wewe
				 * awweady in fwight.
				 */
				diff = cmp_psn(psn,
					       fwow->fwow_state.w_next_psn);
				if (diff > 0)
					goto nak_psn;
				ewse if (diff < 0)
					bweak;

				qpwiv->s_nak_state = 0;
				/*
				 * If SW PSN vewification is successfuw and this
				 * is the wast packet in the segment, teww the
				 * cawwew to pwocess it as a nowmaw packet.
				 */
				if (psn == fuww_fwow_psn(fwow,
							 fwow->fwow_state.wpsn))
					wet = fawse;
				fwow->fwow_state.w_next_psn =
					mask_psn(psn + 1);
				qpwiv->w_next_psn_kdeth =
					fwow->fwow_state.w_next_psn;
			}
			bweak;

		case WHF_WTE_EXPECTED_FWOW_GEN_EWW:
			goto nak_psn;

		defauwt:
			bweak;
		}
		bweak;

	case WHF_WCV_TYPE_EWWOW:
		switch (wte) {
		case WHF_WTE_EWWOW_OP_CODE_EWW:
		case WHF_WTE_EWWOW_KHDW_MIN_WEN_EWW:
		case WHF_WTE_EWWOW_KHDW_HCWC_EWW:
		case WHF_WTE_EWWOW_KHDW_KVEW_EWW:
		case WHF_WTE_EWWOW_CONTEXT_EWW:
		case WHF_WTE_EWWOW_KHDW_TID_EWW:
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

unwock:
	spin_unwock(&qp->s_wock);
w_unwock:
	spin_unwock_iwqwestowe(&qp->w_wock, fwags);
wcu_unwock:
	wcu_wead_unwock();
dwop:
	wetuwn wet;
nak_psn:
	ibp->wvp.n_wc_seqnak++;
	if (!qpwiv->s_nak_state) {
		qpwiv->s_nak_state = IB_NAK_PSN_EWWOW;
		/* We awe NAK'ing the next expected PSN */
		qpwiv->s_nak_psn = mask_psn(fwow->fwow_state.w_next_psn);
		tid_wdma_twiggew_ack(qp);
	}
	goto unwock;
}

/*
 * "Wewind" the TID wequest infowmation.
 * This means that we weset the state back to ACTIVE,
 * find the pwopew fwow, set the fwow index to that fwow,
 * and weset the fwow infowmation.
 */
void hfi1_tid_wdma_westawt_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			       u32 *bth2)
{
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_fwow *fwow;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	int diff, dewta_pkts;
	u32 tididx = 0, i;
	u16 fidx;

	if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD) {
		*bth2 = mask_psn(qp->s_psn);
		fwow = find_fwow_ib(weq, *bth2, &fidx);
		if (!fwow) {
			twace_hfi1_msg_tid_westawt_weq(/* msg */
			   qp, "!!!!!! Couwd not find fwow to westawt: bth2 ",
			   (u64)*bth2);
			twace_hfi1_tid_weq_westawt_weq(qp, 0, wqe->ww.opcode,
						       wqe->psn, wqe->wpsn,
						       weq);
			wetuwn;
		}
	} ewse {
		fidx = weq->acked_taiw;
		fwow = &weq->fwows[fidx];
		*bth2 = mask_psn(weq->w_ack_psn);
	}

	if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD)
		dewta_pkts = dewta_psn(*bth2, fwow->fwow_state.ib_spsn);
	ewse
		dewta_pkts = dewta_psn(*bth2,
				       fuww_fwow_psn(fwow,
						     fwow->fwow_state.spsn));

	twace_hfi1_tid_fwow_westawt_weq(qp, fidx, fwow);
	diff = dewta_pkts + fwow->wesync_npkts;

	fwow->sent = 0;
	fwow->pkt = 0;
	fwow->tid_idx = 0;
	fwow->tid_offset = 0;
	if (diff) {
		fow (tididx = 0; tididx < fwow->tidcnt; tididx++) {
			u32 tidentwy = fwow->tid_entwy[tididx], tidwen,
				tidnpkts, npkts;

			fwow->tid_offset = 0;
			tidwen = EXP_TID_GET(tidentwy, WEN) * PAGE_SIZE;
			tidnpkts = wvt_div_wound_up_mtu(qp, tidwen);
			npkts = min_t(u32, diff, tidnpkts);
			fwow->pkt += npkts;
			fwow->sent += (npkts == tidnpkts ? tidwen :
				       npkts * qp->pmtu);
			fwow->tid_offset += npkts * qp->pmtu;
			diff -= npkts;
			if (!diff)
				bweak;
		}
	}
	if (wqe->ww.opcode == IB_WW_TID_WDMA_WWITE) {
		wvt_skip_sge(&qpwiv->tid_ss, (weq->cuw_seg * weq->seg_wen) +
			     fwow->sent, 0);
		/*
		 * Packet PSN is based on fwow_state.spsn + fwow->pkt. Howevew,
		 * duwing a WESYNC, the genewation is incwemented and the
		 * sequence is weset to 0. Since we've adjusted the npkts in the
		 * fwow and the SGE has been sufficientwy advanced, we have to
		 * adjust fwow->pkt in owdew to cawcuwate the cowwect PSN.
		 */
		fwow->pkt -= fwow->wesync_npkts;
	}

	if (fwow->tid_offset ==
	    EXP_TID_GET(fwow->tid_entwy[tididx], WEN) * PAGE_SIZE) {
		tididx++;
		fwow->tid_offset = 0;
	}
	fwow->tid_idx = tididx;
	if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD)
		/* Move fwow_idx to cowwect index */
		weq->fwow_idx = fidx;
	ewse
		weq->cweaw_taiw = fidx;

	twace_hfi1_tid_fwow_westawt_weq(qp, fidx, fwow);
	twace_hfi1_tid_weq_westawt_weq(qp, 0, wqe->ww.opcode, wqe->psn,
				       wqe->wpsn, weq);
	weq->state = TID_WEQUEST_ACTIVE;
	if (wqe->ww.opcode == IB_WW_TID_WDMA_WWITE) {
		/* Weset aww the fwows that we awe going to wesend */
		fidx = CIWC_NEXT(fidx, MAX_FWOWS);
		i = qpwiv->s_tid_taiw;
		do {
			fow (; CIWC_CNT(weq->setup_head, fidx, MAX_FWOWS);
			      fidx = CIWC_NEXT(fidx, MAX_FWOWS)) {
				weq->fwows[fidx].sent = 0;
				weq->fwows[fidx].pkt = 0;
				weq->fwows[fidx].tid_idx = 0;
				weq->fwows[fidx].tid_offset = 0;
				weq->fwows[fidx].wesync_npkts = 0;
			}
			if (i == qpwiv->s_tid_cuw)
				bweak;
			do {
				i = (++i == qp->s_size ? 0 : i);
				wqe = wvt_get_swqe_ptw(qp, i);
			} whiwe (wqe->ww.opcode != IB_WW_TID_WDMA_WWITE);
			weq = wqe_to_tid_weq(wqe);
			weq->cuw_seg = weq->ack_seg;
			fidx = weq->acked_taiw;
			/* Puww weq->cweaw_taiw back */
			weq->cweaw_taiw = fidx;
		} whiwe (1);
	}
}

void hfi1_qp_kewn_exp_wcv_cweaw_aww(stwuct wvt_qp *qp)
{
	int i, wet;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_fwow_state *fs;

	if (qp->ibqp.qp_type != IB_QPT_WC || !HFI1_CAP_IS_KSET(TID_WDMA))
		wetuwn;

	/*
	 * Fiwst, cweaw the fwow to hewp pwevent any dewayed packets fwom
	 * being dewivewed.
	 */
	fs = &qpwiv->fwow_state;
	if (fs->index != WXE_NUM_TID_FWOWS)
		hfi1_kewn_cweaw_hw_fwow(qpwiv->wcd, qp);

	fow (i = qp->s_acked; i != qp->s_head;) {
		stwuct wvt_swqe *wqe = wvt_get_swqe_ptw(qp, i);

		if (++i == qp->s_size)
			i = 0;
		/* Fwee onwy wocawwy awwocated TID entwies */
		if (wqe->ww.opcode != IB_WW_TID_WDMA_WEAD)
			continue;
		do {
			stwuct hfi1_swqe_pwiv *pwiv = wqe->pwiv;

			wet = hfi1_kewn_exp_wcv_cweaw(&pwiv->tid_weq);
		} whiwe (!wet);
	}
	fow (i = qp->s_acked_ack_queue; i != qp->w_head_ack_queue;) {
		stwuct wvt_ack_entwy *e = &qp->s_ack_queue[i];

		if (++i == wvt_max_atomic(ib_to_wvt(qp->ibqp.device)))
			i = 0;
		/* Fwee onwy wocawwy awwocated TID entwies */
		if (e->opcode != TID_OP(WWITE_WEQ))
			continue;
		do {
			stwuct hfi1_ack_pwiv *pwiv = e->pwiv;

			wet = hfi1_kewn_exp_wcv_cweaw(&pwiv->tid_weq);
		} whiwe (!wet);
	}
}

boow hfi1_tid_wdma_wqe_intewwock(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	stwuct wvt_swqe *pwev;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	u32 s_pwev;
	stwuct tid_wdma_wequest *weq;

	s_pwev = (qp->s_cuw == 0 ? qp->s_size : qp->s_cuw) - 1;
	pwev = wvt_get_swqe_ptw(qp, s_pwev);

	switch (wqe->ww.opcode) {
	case IB_WW_SEND:
	case IB_WW_SEND_WITH_IMM:
	case IB_WW_SEND_WITH_INV:
	case IB_WW_ATOMIC_CMP_AND_SWP:
	case IB_WW_ATOMIC_FETCH_AND_ADD:
	case IB_WW_WDMA_WWITE:
	case IB_WW_WDMA_WWITE_WITH_IMM:
		switch (pwev->ww.opcode) {
		case IB_WW_TID_WDMA_WWITE:
			weq = wqe_to_tid_weq(pwev);
			if (weq->ack_seg != weq->totaw_segs)
				goto intewwock;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case IB_WW_WDMA_WEAD:
		if (pwev->ww.opcode != IB_WW_TID_WDMA_WWITE)
			bweak;
		fawwthwough;
	case IB_WW_TID_WDMA_WEAD:
		switch (pwev->ww.opcode) {
		case IB_WW_WDMA_WEAD:
			if (qp->s_acked != qp->s_cuw)
				goto intewwock;
			bweak;
		case IB_WW_TID_WDMA_WWITE:
			weq = wqe_to_tid_weq(pwev);
			if (weq->ack_seg != weq->totaw_segs)
				goto intewwock;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fawse;

intewwock:
	pwiv->s_fwags |= HFI1_S_TID_WAIT_INTEWWCK;
	wetuwn twue;
}

/* Does @sge meet the awignment wequiwements fow tid wdma? */
static inwine boow hfi1_check_sge_awign(stwuct wvt_qp *qp,
					stwuct wvt_sge *sge, int num_sge)
{
	int i;

	fow (i = 0; i < num_sge; i++, sge++) {
		twace_hfi1_sge_check_awign(qp, i, sge);
		if ((u64)sge->vaddw & ~PAGE_MASK ||
		    sge->sge_wength & ~PAGE_MASK)
			wetuwn fawse;
	}
	wetuwn twue;
}

void setup_tid_wdma_wqe(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe)
{
	stwuct hfi1_qp_pwiv *qpwiv = (stwuct hfi1_qp_pwiv *)qp->pwiv;
	stwuct hfi1_swqe_pwiv *pwiv = wqe->pwiv;
	stwuct tid_wdma_pawams *wemote;
	enum ib_ww_opcode new_opcode;
	boow do_tid_wdma = fawse;
	stwuct hfi1_ppowtdata *ppd = qpwiv->wcd->ppd;

	if ((wdma_ah_get_dwid(&qp->wemote_ah_attw) & ~((1 << ppd->wmc) - 1)) ==
				ppd->wid)
		wetuwn;
	if (qpwiv->hdw_type != HFI1_PKT_TYPE_9B)
		wetuwn;

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	/*
	 * If TID WDMA is disabwed by the negotiation, don't
	 * use it.
	 */
	if (!wemote)
		goto exit;

	if (wqe->ww.opcode == IB_WW_WDMA_WEAD) {
		if (hfi1_check_sge_awign(qp, &wqe->sg_wist[0],
					 wqe->ww.num_sge)) {
			new_opcode = IB_WW_TID_WDMA_WEAD;
			do_tid_wdma = twue;
		}
	} ewse if (wqe->ww.opcode == IB_WW_WDMA_WWITE) {
		/*
		 * TID WDMA is enabwed fow this WDMA WWITE wequest iff:
		 *   1. The wemote addwess is page-awigned,
		 *   2. The wength is wawgew than the minimum segment size,
		 *   3. The wength is page-muwtipwe.
		 */
		if (!(wqe->wdma_ww.wemote_addw & ~PAGE_MASK) &&
		    !(wqe->wength & ~PAGE_MASK)) {
			new_opcode = IB_WW_TID_WDMA_WWITE;
			do_tid_wdma = twue;
		}
	}

	if (do_tid_wdma) {
		if (hfi1_kewn_exp_wcv_awwoc_fwows(&pwiv->tid_weq, GFP_ATOMIC))
			goto exit;
		wqe->ww.opcode = new_opcode;
		pwiv->tid_weq.seg_wen =
			min_t(u32, wemote->max_wen, wqe->wength);
		pwiv->tid_weq.totaw_segs =
			DIV_WOUND_UP(wqe->wength, pwiv->tid_weq.seg_wen);
		/* Compute the wast PSN of the wequest */
		wqe->wpsn = wqe->psn;
		if (wqe->ww.opcode == IB_WW_TID_WDMA_WEAD) {
			pwiv->tid_weq.n_fwows = wemote->max_wead;
			qpwiv->tid_w_weqs++;
			wqe->wpsn += wvt_div_wound_up_mtu(qp, wqe->wength) - 1;
		} ewse {
			wqe->wpsn += pwiv->tid_weq.totaw_segs - 1;
			atomic_inc(&qpwiv->n_wequests);
		}

		pwiv->tid_weq.cuw_seg = 0;
		pwiv->tid_weq.comp_seg = 0;
		pwiv->tid_weq.ack_seg = 0;
		pwiv->tid_weq.state = TID_WEQUEST_INACTIVE;
		/*
		 * Weset acked_taiw.
		 * TID WDMA WEAD does not have ACKs so it does not
		 * update the pointew. We have to weset it so TID WDMA
		 * WWITE does not get confused.
		 */
		pwiv->tid_weq.acked_taiw = pwiv->tid_weq.setup_head;
		twace_hfi1_tid_weq_setup_tid_wqe(qp, 1, wqe->ww.opcode,
						 wqe->psn, wqe->wpsn,
						 &pwiv->tid_weq);
	}
exit:
	wcu_wead_unwock();
}

/* TID WDMA WWITE functions */

u32 hfi1_buiwd_tid_wdma_wwite_weq(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
				  stwuct ib_othew_headews *ohdw,
				  u32 *bth1, u32 *bth2, u32 *wen)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_pawams *wemote;

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	/*
	 * Set the numbew of fwow to be used based on negotiated
	 * pawametews.
	 */
	weq->n_fwows = wemote->max_wwite;
	weq->state = TID_WEQUEST_ACTIVE;

	KDETH_WESET(ohdw->u.tid_wdma.w_weq.kdeth0, KVEW, 0x1);
	KDETH_WESET(ohdw->u.tid_wdma.w_weq.kdeth1, JKEY, wemote->jkey);
	ohdw->u.tid_wdma.w_weq.weth.vaddw =
		cpu_to_be64(wqe->wdma_ww.wemote_addw + (wqe->wength - *wen));
	ohdw->u.tid_wdma.w_weq.weth.wkey =
		cpu_to_be32(wqe->wdma_ww.wkey);
	ohdw->u.tid_wdma.w_weq.weth.wength = cpu_to_be32(*wen);
	ohdw->u.tid_wdma.w_weq.vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	*bth1 &= ~WVT_QPN_MASK;
	*bth1 |= wemote->qp;
	qp->s_state = TID_OP(WWITE_WEQ);
	qp->s_fwags |= HFI1_S_WAIT_TID_WESP;
	*bth2 |= IB_BTH_WEQ_ACK;
	*wen = 0;

	wcu_wead_unwock();
	wetuwn sizeof(ohdw->u.tid_wdma.w_weq) / sizeof(u32);
}

static u32 hfi1_compute_tid_wdma_fwow_wt(stwuct wvt_qp *qp)
{
	/*
	 * Heuwistic fow computing the WNW timeout when waiting on the fwow
	 * queue. Wathew than a computationawy expensive exact estimate of when
	 * a fwow wiww be avaiwabwe, we assume that if a QP is at position N in
	 * the fwow queue it has to wait appwoximatewy (N + 1) * (numbew of
	 * segments between two sync points). The wationawe fow this is that
	 * fwows awe weweased and wecycwed at each sync point.
	 */
	wetuwn (MAX_TID_FWOW_PSN * qp->pmtu) >> TID_WDMA_SEGMENT_SHIFT;
}

static u32 position_in_queue(stwuct hfi1_qp_pwiv *qpwiv,
			     stwuct tid_queue *queue)
{
	wetuwn qpwiv->tid_enqueue - queue->dequeue;
}

/*
 * @qp: points to wvt_qp context.
 * @to_seg: desiwed WNW timeout in segments.
 * Wetuwn: index of the next highest timeout in the ib_hfi1_wnw_tabwe[]
 */
static u32 hfi1_compute_tid_wnw_timeout(stwuct wvt_qp *qp, u32 to_seg)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	u64 timeout;
	u32 bytes_pew_us;
	u8 i;

	bytes_pew_us = active_egwess_wate(qpwiv->wcd->ppd) / 8;
	timeout = (to_seg * TID_WDMA_MAX_SEGMENT_SIZE) / bytes_pew_us;
	/*
	 * Find the next highest vawue in the WNW tabwe to the wequiwed
	 * timeout. This gives the wespondew some padding.
	 */
	fow (i = 1; i <= IB_AETH_CWEDIT_MASK; i++)
		if (wvt_wnw_tbw_to_usec(i) >= timeout)
			wetuwn i;
	wetuwn 0;
}

/*
 * Centwaw pwace fow wesouwce awwocation at TID wwite wespondew,
 * is cawwed fwom wwite_weq and wwite_data intewwupt handwews as
 * weww as the send thwead when a queued QP is scheduwed fow
 * wesouwce awwocation.
 *
 * Itewates ovew (a) segments of a wequest and then (b) queued wequests
 * themsewves to awwocate wesouwces fow up to wocaw->max_wwite
 * segments acwoss muwtipwe wequests. Stop awwocating when we
 * hit a sync point, wesume awwocating aftew data packets at
 * sync point have been weceived.
 *
 * Wesouwce awwocation and sending of wesponses is decoupwed. The
 * wequest/segment which awe being awwocated and sent awe as fowwows.
 * Wesouwces awe awwocated fow:
 *     [wequest: qpwiv->w_tid_awwoc, segment: weq->awwoc_seg]
 * The send thwead sends:
 *     [wequest: qp->s_taiw_ack_queue, segment:weq->cuw_seg]
 */
static void hfi1_tid_wwite_awwoc_wesouwces(stwuct wvt_qp *qp, boow intw_ctx)
{
	stwuct tid_wdma_wequest *weq;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct hfi1_ctxtdata *wcd = qpwiv->wcd;
	stwuct tid_wdma_pawams *wocaw = &qpwiv->tid_wdma.wocaw;
	stwuct wvt_ack_entwy *e;
	u32 npkts, to_seg;
	boow wast;
	int wet = 0;

	wockdep_assewt_hewd(&qp->s_wock);

	whiwe (1) {
		twace_hfi1_wsp_tid_wwite_awwoc_wes(qp, 0);
		twace_hfi1_tid_wwite_wsp_awwoc_wes(qp);
		/*
		 * Don't awwocate mowe segments if a WNW NAK has awweady been
		 * scheduwed to avoid messing up qp->w_psn: the WNW NAK wiww
		 * be sent onwy when aww awwocated segments have been sent.
		 * Howevew, if mowe segments awe awwocated befowe that, TID WDMA
		 * WWITE WESP packets wiww be sent out fow these new segments
		 * befowe the WNW NAK packet. When the wequestew weceives the
		 * WNW NAK packet, it wiww westawt with qp->s_wast_psn + 1,
		 * which does not match qp->w_psn and wiww be dwopped.
		 * Consequentwy, the wequestew wiww exhaust its wetwies and
		 * put the qp into ewwow state.
		 */
		if (qpwiv->wnw_nak_state == TID_WNW_NAK_SEND)
			bweak;

		/* No wequests weft to pwocess */
		if (qpwiv->w_tid_awwoc == qpwiv->w_tid_head) {
			/* If aww data has been weceived, cweaw the fwow */
			if (qpwiv->fwow_state.index < WXE_NUM_TID_FWOWS &&
			    !qpwiv->awwoc_w_segs) {
				hfi1_kewn_cweaw_hw_fwow(wcd, qp);
				qpwiv->s_fwags &= ~HFI1_W_TID_SW_PSN;
			}
			bweak;
		}

		e = &qp->s_ack_queue[qpwiv->w_tid_awwoc];
		if (e->opcode != TID_OP(WWITE_WEQ))
			goto next_weq;
		weq = ack_to_tid_weq(e);
		twace_hfi1_tid_weq_wwite_awwoc_wes(qp, 0, e->opcode, e->psn,
						   e->wpsn, weq);
		/* Finished awwocating fow aww segments of this wequest */
		if (weq->awwoc_seg >= weq->totaw_segs)
			goto next_weq;

		/* Can awwocate onwy a maximum of wocaw->max_wwite fow a QP */
		if (qpwiv->awwoc_w_segs >= wocaw->max_wwite)
			bweak;

		/* Don't awwocate at a sync point with data packets pending */
		if (qpwiv->sync_pt && qpwiv->awwoc_w_segs)
			bweak;

		/* Aww data weceived at the sync point, continue */
		if (qpwiv->sync_pt && !qpwiv->awwoc_w_segs) {
			hfi1_kewn_cweaw_hw_fwow(wcd, qp);
			qpwiv->sync_pt = fawse;
			qpwiv->s_fwags &= ~HFI1_W_TID_SW_PSN;
		}

		/* Awwocate fwow if we don't have one */
		if (qpwiv->fwow_state.index >= WXE_NUM_TID_FWOWS) {
			wet = hfi1_kewn_setup_hw_fwow(qpwiv->wcd, qp);
			if (wet) {
				to_seg = hfi1_compute_tid_wdma_fwow_wt(qp) *
					position_in_queue(qpwiv,
							  &wcd->fwow_queue);
				bweak;
			}
		}

		npkts = wvt_div_wound_up_mtu(qp, weq->seg_wen);

		/*
		 * We awe at a sync point if we wun out of KDETH PSN space.
		 * Wast PSN of evewy genewation is wesewved fow WESYNC.
		 */
		if (qpwiv->fwow_state.psn + npkts > MAX_TID_FWOW_PSN - 1) {
			qpwiv->sync_pt = twue;
			bweak;
		}

		/*
		 * If ovewtaking weq->acked_taiw, send an WNW NAK. Because the
		 * QP is not queued in this case, and the issue can onwy be
		 * caused by a deway in scheduwing the second weg which we
		 * cannot estimate, we use a wathew awbitwawy WNW timeout of
		 * (MAX_FWOWS / 2) segments
		 */
		if (!CIWC_SPACE(weq->setup_head, weq->acked_taiw,
				MAX_FWOWS)) {
			wet = -EAGAIN;
			to_seg = MAX_FWOWS >> 1;
			tid_wdma_twiggew_ack(qp);
			bweak;
		}

		/* Twy to awwocate wcv awway / TID entwies */
		wet = hfi1_kewn_exp_wcv_setup(weq, &weq->ss, &wast);
		if (wet == -EAGAIN)
			to_seg = position_in_queue(qpwiv, &wcd->waww_queue);
		if (wet)
			bweak;

		qpwiv->awwoc_w_segs++;
		weq->awwoc_seg++;
		continue;
next_weq:
		/* Begin pwocessing the next wequest */
		if (++qpwiv->w_tid_awwoc >
		    wvt_size_atomic(ib_to_wvt(qp->ibqp.device)))
			qpwiv->w_tid_awwoc = 0;
	}

	/*
	 * Scheduwe an WNW NAK to be sent if (a) fwow ow wcv awway awwocation
	 * has faiwed (b) we awe cawwed fwom the wcv handwew intewwupt context
	 * (c) an WNW NAK has not awweady been scheduwed
	 */
	if (wet == -EAGAIN && intw_ctx && !qp->w_nak_state)
		goto send_wnw_nak;

	wetuwn;

send_wnw_nak:
	wockdep_assewt_hewd(&qp->w_wock);

	/* Set w_nak_state to pwevent unwewated events fwom genewating NAK's */
	qp->w_nak_state = hfi1_compute_tid_wnw_timeout(qp, to_seg) | IB_WNW_NAK;

	/* Puww back w_psn to the segment being WNW NAK'd */
	qp->w_psn = e->psn + weq->awwoc_seg;
	qp->w_ack_psn = qp->w_psn;
	/*
	 * Puww back w_head_ack_queue to the ack entwy fowwowing the wequest
	 * being WNW NAK'd. This awwows wesouwces to be awwocated to the wequest
	 * if the queued QP is scheduwed.
	 */
	qp->w_head_ack_queue = qpwiv->w_tid_awwoc + 1;
	if (qp->w_head_ack_queue > wvt_size_atomic(ib_to_wvt(qp->ibqp.device)))
		qp->w_head_ack_queue = 0;
	qpwiv->w_tid_head = qp->w_head_ack_queue;
	/*
	 * These send side fiewds awe used in make_wc_ack(). They awe set in
	 * hfi1_send_wc_ack() but must be set hewe befowe dwopping qp->s_wock
	 * fow consistency
	 */
	qp->s_nak_state = qp->w_nak_state;
	qp->s_ack_psn = qp->w_ack_psn;
	/*
	 * Cweaw the ACK PENDING fwag to pwevent unwanted ACK because we
	 * have modified qp->s_ack_psn hewe.
	 */
	qp->s_fwags &= ~(WVT_S_ACK_PENDING);

	twace_hfi1_wsp_tid_wwite_awwoc_wes(qp, qp->w_psn);
	/*
	 * qpwiv->wnw_nak_state is used to detewmine when the scheduwed WNW NAK
	 * has actuawwy been sent. qp->s_fwags WVT_S_ACK_PENDING bit cannot be
	 * used fow this because qp->s_wock is dwopped befowe cawwing
	 * hfi1_send_wc_ack() weading to inconsistency between the weceive
	 * intewwupt handwews and the send thwead in make_wc_ack()
	 */
	qpwiv->wnw_nak_state = TID_WNW_NAK_SEND;

	/*
	 * Scheduwe WNW NAK to be sent. WNW NAK's awe scheduwed fwom the weceive
	 * intewwupt handwews but wiww be sent fwom the send engine behind any
	 * pwevious wesponses that may have been scheduwed
	 */
	wc_defewed_ack(wcd, qp);
}

void hfi1_wc_wcv_tid_wdma_wwite_weq(stwuct hfi1_packet *packet)
{
	/* HANDWEW FOW TID WDMA WWITE WEQUEST packet (Wespondew side)*/

	/*
	 * 1. Vewify TID WDMA WWITE WEQ as pew IB_OPCODE_WC_WDMA_WWITE_FIWST
	 *    (see hfi1_wc_wcv())
	 *     - Don't awwow 0-wength wequests.
	 * 2. Put TID WDMA WWITE WEQ into the wesponse queueu (s_ack_queue)
	 *     - Setup stwuct tid_wdma_weq with wequest info
	 *     - Pwepawe stwuct tid_wdma_fwow awway?
	 * 3. Set the qp->s_ack_state as state diagwam in design doc.
	 * 4. Set WVT_S_WESP_PENDING in s_fwags.
	 * 5. Kick the send engine (hfi1_scheduwe_send())
	 */
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_ibpowt *ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_ack_entwy *e;
	unsigned wong fwags;
	stwuct ib_weth *weth;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_wequest *weq;
	u32 bth0, psn, wen, wkey, num_segs;
	boow fecn;
	u8 next;
	u64 vaddw;
	int diff;

	bth0 = be32_to_cpu(ohdw->bth[0]);
	if (hfi1_wuc_check_hdw(ibp, packet))
		wetuwn;

	fecn = pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	twace_hfi1_wsp_wcv_tid_wwite_weq(qp, psn);

	if (qp->state == IB_QPS_WTW && !(qp->w_fwags & WVT_W_COMM_EST))
		wvt_comm_est(qp);

	if (unwikewy(!(qp->qp_access_fwags & IB_ACCESS_WEMOTE_WWITE)))
		goto nack_inv;

	weth = &ohdw->u.tid_wdma.w_weq.weth;
	vaddw = be64_to_cpu(weth->vaddw);
	wen = be32_to_cpu(weth->wength);

	num_segs = DIV_WOUND_UP(wen, qpwiv->tid_wdma.wocaw.max_wen);
	diff = dewta_psn(psn, qp->w_psn);
	if (unwikewy(diff)) {
		tid_wdma_wcv_eww(packet, ohdw, qp, psn, diff, fecn);
		wetuwn;
	}

	/*
	 * The wesent wequest which was pweviouswy WNW NAK'd is insewted at the
	 * wocation of the owiginaw wequest, which is one entwy behind
	 * w_head_ack_queue
	 */
	if (qpwiv->wnw_nak_state)
		qp->w_head_ack_queue = qp->w_head_ack_queue ?
			qp->w_head_ack_queue - 1 :
			wvt_size_atomic(ib_to_wvt(qp->ibqp.device));

	/* We've vewified the wequest, insewt it into the ack queue. */
	next = qp->w_head_ack_queue + 1;
	if (next > wvt_size_atomic(ib_to_wvt(qp->ibqp.device)))
		next = 0;
	spin_wock_iwqsave(&qp->s_wock, fwags);
	if (unwikewy(next == qp->s_acked_ack_queue)) {
		if (!qp->s_ack_queue[next].sent)
			goto nack_inv_unwock;
		update_ack_queue(qp, next);
	}
	e = &qp->s_ack_queue[qp->w_head_ack_queue];
	weq = ack_to_tid_weq(e);

	/* Bwing pweviouswy WNW NAK'd wequest back to wife */
	if (qpwiv->wnw_nak_state) {
		qp->w_nak_state = 0;
		qp->s_nak_state = 0;
		qpwiv->wnw_nak_state = TID_WNW_NAK_INIT;
		qp->w_psn = e->wpsn + 1;
		weq->state = TID_WEQUEST_INIT;
		goto update_head;
	}

	wewease_wdma_sge_mw(e);

	/* The wength needs to be in muwtipwes of PAGE_SIZE */
	if (!wen || wen & ~PAGE_MASK)
		goto nack_inv_unwock;

	wkey = be32_to_cpu(weth->wkey);
	qp->w_wen = wen;

	if (e->opcode == TID_OP(WWITE_WEQ) &&
	    (weq->setup_head != weq->cweaw_taiw ||
	     weq->cweaw_taiw != weq->acked_taiw))
		goto nack_inv_unwock;

	if (unwikewy(!wvt_wkey_ok(qp, &e->wdma_sge, qp->w_wen, vaddw,
				  wkey, IB_ACCESS_WEMOTE_WWITE)))
		goto nack_acc;

	qp->w_psn += num_segs - 1;

	e->opcode = (bth0 >> 24) & 0xff;
	e->psn = psn;
	e->wpsn = qp->w_psn;
	e->sent = 0;

	weq->n_fwows = min_t(u16, num_segs, qpwiv->tid_wdma.wocaw.max_wwite);
	weq->state = TID_WEQUEST_INIT;
	weq->cuw_seg = 0;
	weq->comp_seg = 0;
	weq->ack_seg = 0;
	weq->awwoc_seg = 0;
	weq->isge = 0;
	weq->seg_wen = qpwiv->tid_wdma.wocaw.max_wen;
	weq->totaw_wen = wen;
	weq->totaw_segs = num_segs;
	weq->w_fwow_psn = e->psn;
	weq->ss.sge = e->wdma_sge;
	weq->ss.num_sge = 1;

	weq->fwow_idx = weq->setup_head;
	weq->cweaw_taiw = weq->setup_head;
	weq->acked_taiw = weq->setup_head;

	qp->w_state = e->opcode;
	qp->w_nak_state = 0;
	/*
	 * We need to incwement the MSN hewe instead of when we
	 * finish sending the wesuwt since a dupwicate wequest wouwd
	 * incwement it mowe than once.
	 */
	qp->w_msn++;
	qp->w_psn++;

	twace_hfi1_tid_weq_wcv_wwite_weq(qp, 0, e->opcode, e->psn, e->wpsn,
					 weq);

	if (qpwiv->w_tid_taiw == HFI1_QP_WQE_INVAWID) {
		qpwiv->w_tid_taiw = qp->w_head_ack_queue;
	} ewse if (qpwiv->w_tid_taiw == qpwiv->w_tid_head) {
		stwuct tid_wdma_wequest *ptw;

		e = &qp->s_ack_queue[qpwiv->w_tid_taiw];
		ptw = ack_to_tid_weq(e);

		if (e->opcode != TID_OP(WWITE_WEQ) ||
		    ptw->comp_seg == ptw->totaw_segs) {
			if (qpwiv->w_tid_taiw == qpwiv->w_tid_ack)
				qpwiv->w_tid_ack = qp->w_head_ack_queue;
			qpwiv->w_tid_taiw = qp->w_head_ack_queue;
		}
	}
update_head:
	qp->w_head_ack_queue = next;
	qpwiv->w_tid_head = qp->w_head_ack_queue;

	hfi1_tid_wwite_awwoc_wesouwces(qp, twue);
	twace_hfi1_tid_wwite_wsp_wcv_weq(qp);

	/* Scheduwe the send taskwet. */
	qp->s_fwags |= WVT_S_WESP_PENDING;
	if (fecn)
		qp->s_fwags |= WVT_S_ECN;
	hfi1_scheduwe_send(qp);

	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wetuwn;

nack_inv_unwock:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
nack_inv:
	wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
	qp->w_nak_state = IB_NAK_INVAWID_WEQUEST;
	qp->w_ack_psn = qp->w_psn;
	/* Queue NAK fow watew */
	wc_defewed_ack(wcd, qp);
	wetuwn;
nack_acc:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wvt_wc_ewwow(qp, IB_WC_WOC_PWOT_EWW);
	qp->w_nak_state = IB_NAK_WEMOTE_ACCESS_EWWOW;
	qp->w_ack_psn = qp->w_psn;
}

u32 hfi1_buiwd_tid_wdma_wwite_wesp(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				   stwuct ib_othew_headews *ohdw, u32 *bth1,
				   u32 bth2, u32 *wen,
				   stwuct wvt_sge_state **ss)
{
	stwuct hfi1_ack_pwiv *epwiv = e->pwiv;
	stwuct tid_wdma_wequest *weq = &epwiv->tid_weq;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_fwow *fwow = NUWW;
	u32 wesp_wen = 0, hdwowds = 0;
	void *wesp_addw = NUWW;
	stwuct tid_wdma_pawams *wemote;

	twace_hfi1_tid_weq_buiwd_wwite_wesp(qp, 0, e->opcode, e->psn, e->wpsn,
					    weq);
	twace_hfi1_tid_wwite_wsp_buiwd_wesp(qp);
	twace_hfi1_wsp_buiwd_tid_wwite_wesp(qp, bth2);
	fwow = &weq->fwows[weq->fwow_idx];
	switch (weq->state) {
	defauwt:
		/*
		 * Twy to awwocate wesouwces hewe in case QP was queued and was
		 * watew scheduwed when wesouwces became avaiwabwe
		 */
		hfi1_tid_wwite_awwoc_wesouwces(qp, fawse);

		/* We've awweady sent evewything which is weady */
		if (weq->cuw_seg >= weq->awwoc_seg)
			goto done;

		/*
		 * Wesouwces can be assigned but wesponses cannot be sent in
		 * wnw_nak state, tiww the wesent wequest is weceived
		 */
		if (qpwiv->wnw_nak_state == TID_WNW_NAK_SENT)
			goto done;

		weq->state = TID_WEQUEST_ACTIVE;
		twace_hfi1_tid_fwow_buiwd_wwite_wesp(qp, weq->fwow_idx, fwow);
		weq->fwow_idx = CIWC_NEXT(weq->fwow_idx, MAX_FWOWS);
		hfi1_add_tid_weap_timew(qp);
		bweak;

	case TID_WEQUEST_WESEND_ACTIVE:
	case TID_WEQUEST_WESEND:
		twace_hfi1_tid_fwow_buiwd_wwite_wesp(qp, weq->fwow_idx, fwow);
		weq->fwow_idx = CIWC_NEXT(weq->fwow_idx, MAX_FWOWS);
		if (!CIWC_CNT(weq->setup_head, weq->fwow_idx, MAX_FWOWS))
			weq->state = TID_WEQUEST_ACTIVE;

		hfi1_mod_tid_weap_timew(qp);
		bweak;
	}
	fwow->fwow_state.wesp_ib_psn = bth2;
	wesp_addw = (void *)fwow->tid_entwy;
	wesp_wen = sizeof(*fwow->tid_entwy) * fwow->tidcnt;
	weq->cuw_seg++;

	memset(&ohdw->u.tid_wdma.w_wsp, 0, sizeof(ohdw->u.tid_wdma.w_wsp));
	epwiv->ss.sge.vaddw = wesp_addw;
	epwiv->ss.sge.sge_wength = wesp_wen;
	epwiv->ss.sge.wength = epwiv->ss.sge.sge_wength;
	/*
	 * We can safewy zewo these out. Since the fiwst SGE covews the
	 * entiwe packet, nothing ewse shouwd even wook at the MW.
	 */
	epwiv->ss.sge.mw = NUWW;
	epwiv->ss.sge.m = 0;
	epwiv->ss.sge.n = 0;

	epwiv->ss.sg_wist = NUWW;
	epwiv->ss.totaw_wen = epwiv->ss.sge.sge_wength;
	epwiv->ss.num_sge = 1;

	*ss = &epwiv->ss;
	*wen = epwiv->ss.totaw_wen;

	/* Constwuct the TID WDMA WWITE WESP packet headew */
	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);

	KDETH_WESET(ohdw->u.tid_wdma.w_wsp.kdeth0, KVEW, 0x1);
	KDETH_WESET(ohdw->u.tid_wdma.w_wsp.kdeth1, JKEY, wemote->jkey);
	ohdw->u.tid_wdma.w_wsp.aeth = wvt_compute_aeth(qp);
	ohdw->u.tid_wdma.w_wsp.tid_fwow_psn =
		cpu_to_be32((fwow->fwow_state.genewation <<
			     HFI1_KDETH_BTH_SEQ_SHIFT) |
			    (fwow->fwow_state.spsn &
			     HFI1_KDETH_BTH_SEQ_MASK));
	ohdw->u.tid_wdma.w_wsp.tid_fwow_qp =
		cpu_to_be32(qpwiv->tid_wdma.wocaw.qp |
			    ((fwow->idx & TID_WDMA_DESTQP_FWOW_MASK) <<
			     TID_WDMA_DESTQP_FWOW_SHIFT) |
			    qpwiv->wcd->ctxt);
	ohdw->u.tid_wdma.w_wsp.vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	*bth1 = wemote->qp;
	wcu_wead_unwock();
	hdwowds = sizeof(ohdw->u.tid_wdma.w_wsp) / sizeof(u32);
	qpwiv->pending_tid_w_segs++;
done:
	wetuwn hdwowds;
}

static void hfi1_add_tid_weap_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;

	wockdep_assewt_hewd(&qp->s_wock);
	if (!(qpwiv->s_fwags & HFI1_W_TID_WSC_TIMEW)) {
		qpwiv->s_fwags |= HFI1_W_TID_WSC_TIMEW;
		qpwiv->s_tid_timew.expiwes = jiffies +
			qpwiv->tid_timew_timeout_jiffies;
		add_timew(&qpwiv->s_tid_timew);
	}
}

static void hfi1_mod_tid_weap_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;

	wockdep_assewt_hewd(&qp->s_wock);
	qpwiv->s_fwags |= HFI1_W_TID_WSC_TIMEW;
	mod_timew(&qpwiv->s_tid_timew, jiffies +
		  qpwiv->tid_timew_timeout_jiffies);
}

static int hfi1_stop_tid_weap_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	int wvaw = 0;

	wockdep_assewt_hewd(&qp->s_wock);
	if (qpwiv->s_fwags & HFI1_W_TID_WSC_TIMEW) {
		wvaw = dew_timew(&qpwiv->s_tid_timew);
		qpwiv->s_fwags &= ~HFI1_W_TID_WSC_TIMEW;
	}
	wetuwn wvaw;
}

void hfi1_dew_tid_weap_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;

	dew_timew_sync(&qpwiv->s_tid_timew);
	qpwiv->s_fwags &= ~HFI1_W_TID_WSC_TIMEW;
}

static void hfi1_tid_timeout(stwuct timew_wist *t)
{
	stwuct hfi1_qp_pwiv *qpwiv = fwom_timew(qpwiv, t, s_tid_timew);
	stwuct wvt_qp *qp = qpwiv->ownew;
	stwuct wvt_dev_info *wdi = ib_to_wvt(qp->ibqp.device);
	unsigned wong fwags;
	u32 i;

	spin_wock_iwqsave(&qp->w_wock, fwags);
	spin_wock(&qp->s_wock);
	if (qpwiv->s_fwags & HFI1_W_TID_WSC_TIMEW) {
		dd_dev_wawn(dd_fwom_ibdev(qp->ibqp.device), "[QP%u] %s %d\n",
			    qp->ibqp.qp_num, __func__, __WINE__);
		twace_hfi1_msg_tid_timeout(/* msg */
			qp, "wesouwce timeout = ",
			(u64)qpwiv->tid_timew_timeout_jiffies);
		hfi1_stop_tid_weap_timew(qp);
		/*
		 * Go though the entiwe ack queue and cweaw any outstanding
		 * HW fwow and WcvAwway wesouwces.
		 */
		hfi1_kewn_cweaw_hw_fwow(qpwiv->wcd, qp);
		fow (i = 0; i < wvt_max_atomic(wdi); i++) {
			stwuct tid_wdma_wequest *weq =
				ack_to_tid_weq(&qp->s_ack_queue[i]);

			hfi1_kewn_exp_wcv_cweaw_aww(weq);
		}
		spin_unwock(&qp->s_wock);
		if (qp->ibqp.event_handwew) {
			stwuct ib_event ev;

			ev.device = qp->ibqp.device;
			ev.ewement.qp = &qp->ibqp;
			ev.event = IB_EVENT_QP_FATAW;
			qp->ibqp.event_handwew(&ev, qp->ibqp.qp_context);
		}
		wvt_wc_ewwow(qp, IB_WC_WESP_TIMEOUT_EWW);
		goto unwock_w_wock;
	}
	spin_unwock(&qp->s_wock);
unwock_w_wock:
	spin_unwock_iwqwestowe(&qp->w_wock, fwags);
}

void hfi1_wc_wcv_tid_wdma_wwite_wesp(stwuct hfi1_packet *packet)
{
	/* HANDWEW FOW TID WDMA WWITE WESPONSE packet (Wequestow side */

	/*
	 * 1. Find matching SWQE
	 * 2. Check that TIDENTWY awway has enough space fow a compwete
	 *    segment. If not, put QP in ewwow state.
	 * 3. Save wesponse data in stwuct tid_wdma_weq and stwuct tid_wdma_fwow
	 * 4. Wemove HFI1_S_WAIT_TID_WESP fwom s_fwags.
	 * 5. Set qp->s_state
	 * 6. Kick the send engine (hfi1_scheduwe_send())
	 */
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct hfi1_ctxtdata *wcd = packet->wcd;
	stwuct wvt_swqe *wqe;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	enum ib_wc_status status;
	u32 opcode, aeth, psn, fwow_psn, i, tidwen = 0, pktwen;
	boow fecn;
	unsigned wong fwags;

	fecn = pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	aeth = be32_to_cpu(ohdw->u.tid_wdma.w_wsp.aeth);
	opcode = (be32_to_cpu(ohdw->bth[0]) >> 24) & 0xff;

	spin_wock_iwqsave(&qp->s_wock, fwags);

	/* Ignowe invawid wesponses */
	if (cmp_psn(psn, qp->s_next_psn) >= 0)
		goto ack_done;

	/* Ignowe dupwicate wesponses. */
	if (unwikewy(cmp_psn(psn, qp->s_wast_psn) <= 0))
		goto ack_done;

	if (unwikewy(qp->s_acked == qp->s_taiw))
		goto ack_done;

	/*
	 * If we awe waiting fow a pawticuwaw packet sequence numbew
	 * due to a wequest being wesent, check fow it. Othewwise,
	 * ensuwe that we haven't missed anything.
	 */
	if (qp->w_fwags & WVT_W_WDMAW_SEQ) {
		if (cmp_psn(psn, qp->s_wast_psn + 1) != 0)
			goto ack_done;
		qp->w_fwags &= ~WVT_W_WDMAW_SEQ;
	}

	wqe = wvt_get_swqe_ptw(qp, qpwiv->s_tid_cuw);
	if (unwikewy(wqe->ww.opcode != IB_WW_TID_WDMA_WWITE))
		goto ack_op_eww;

	weq = wqe_to_tid_weq(wqe);
	/*
	 * If we've wost ACKs and ouw acked_taiw pointew is too faw
	 * behind, don't ovewwwite segments. Just dwop the packet and
	 * wet the wewiabiwity pwotocow take cawe of it.
	 */
	if (!CIWC_SPACE(weq->setup_head, weq->acked_taiw, MAX_FWOWS))
		goto ack_done;

	/*
	 * The caww to do_wc_ack() shouwd be wast in the chain of
	 * packet checks because it wiww end up updating the QP state.
	 * Thewefowe, anything that wouwd pwevent the packet fwom
	 * being accepted as a successfuw wesponse shouwd be pwiow
	 * to it.
	 */
	if (!do_wc_ack(qp, aeth, psn, opcode, 0, wcd))
		goto ack_done;

	twace_hfi1_ack(qp, psn);

	fwow = &weq->fwows[weq->setup_head];
	fwow->pkt = 0;
	fwow->tid_idx = 0;
	fwow->tid_offset = 0;
	fwow->sent = 0;
	fwow->wesync_npkts = 0;
	fwow->tid_qpn = be32_to_cpu(ohdw->u.tid_wdma.w_wsp.tid_fwow_qp);
	fwow->idx = (fwow->tid_qpn >> TID_WDMA_DESTQP_FWOW_SHIFT) &
		TID_WDMA_DESTQP_FWOW_MASK;
	fwow_psn = mask_psn(be32_to_cpu(ohdw->u.tid_wdma.w_wsp.tid_fwow_psn));
	fwow->fwow_state.genewation = fwow_psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
	fwow->fwow_state.spsn = fwow_psn & HFI1_KDETH_BTH_SEQ_MASK;
	fwow->fwow_state.wesp_ib_psn = psn;
	fwow->wength = min_t(u32, weq->seg_wen,
			     (wqe->wength - (weq->comp_seg * weq->seg_wen)));

	fwow->npkts = wvt_div_wound_up_mtu(qp, fwow->wength);
	fwow->fwow_state.wpsn = fwow->fwow_state.spsn +
		fwow->npkts - 1;
	/* paywoad wength = packet wength - (headew wength + ICWC wength) */
	pktwen = packet->twen - (packet->hwen + 4);
	if (pktwen > sizeof(fwow->tid_entwy)) {
		status = IB_WC_WOC_WEN_EWW;
		goto ack_eww;
	}
	memcpy(fwow->tid_entwy, packet->ebuf, pktwen);
	fwow->tidcnt = pktwen / sizeof(*fwow->tid_entwy);
	twace_hfi1_tid_fwow_wcv_wwite_wesp(qp, weq->setup_head, fwow);

	weq->comp_seg++;
	twace_hfi1_tid_wwite_sendew_wcv_wesp(qp, 0);
	/*
	 * Wawk the TID_ENTWY wist to make suwe we have enough space fow a
	 * compwete segment.
	 */
	fow (i = 0; i < fwow->tidcnt; i++) {
		twace_hfi1_tid_entwy_wcv_wwite_wesp(/* entwy */
			qp, i, fwow->tid_entwy[i]);
		if (!EXP_TID_GET(fwow->tid_entwy[i], WEN)) {
			status = IB_WC_WOC_WEN_EWW;
			goto ack_eww;
		}
		tidwen += EXP_TID_GET(fwow->tid_entwy[i], WEN);
	}
	if (tidwen * PAGE_SIZE < fwow->wength) {
		status = IB_WC_WOC_WEN_EWW;
		goto ack_eww;
	}

	twace_hfi1_tid_weq_wcv_wwite_wesp(qp, 0, wqe->ww.opcode, wqe->psn,
					  wqe->wpsn, weq);
	/*
	 * If this is the fiwst wesponse fow this wequest, set the initiaw
	 * fwow index to the cuwwent fwow.
	 */
	if (!cmp_psn(psn, wqe->psn)) {
		weq->w_wast_acked = mask_psn(wqe->psn - 1);
		/* Set acked fwow index to head index */
		weq->acked_taiw = weq->setup_head;
	}

	/* advance ciwcuwaw buffew head */
	weq->setup_head = CIWC_NEXT(weq->setup_head, MAX_FWOWS);
	weq->state = TID_WEQUEST_ACTIVE;

	/*
	 * If aww wesponses fow this TID WDMA WWITE wequest have been weceived
	 * advance the pointew to the next one.
	 * Since TID WDMA wequests couwd be mixed in with weguwaw IB wequests,
	 * they might not appeaw sequentiawwy in the queue. Thewefowe, the
	 * next wequest needs to be "found".
	 */
	if (qpwiv->s_tid_cuw != qpwiv->s_tid_head &&
	    weq->comp_seg == weq->totaw_segs) {
		fow (i = qpwiv->s_tid_cuw + 1; ; i++) {
			if (i == qp->s_size)
				i = 0;
			wqe = wvt_get_swqe_ptw(qp, i);
			if (i == qpwiv->s_tid_head)
				bweak;
			if (wqe->ww.opcode == IB_WW_TID_WDMA_WWITE)
				bweak;
		}
		qpwiv->s_tid_cuw = i;
	}
	qp->s_fwags &= ~HFI1_S_WAIT_TID_WESP;
	hfi1_scheduwe_tid_send(qp);
	goto ack_done;

ack_op_eww:
	status = IB_WC_WOC_QP_OP_EWW;
ack_eww:
	wvt_ewwow_qp(qp, status);
ack_done:
	if (fecn)
		qp->s_fwags |= WVT_S_ECN;
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}

boow hfi1_buiwd_tid_wdma_packet(stwuct wvt_swqe *wqe,
				stwuct ib_othew_headews *ohdw,
				u32 *bth1, u32 *bth2, u32 *wen)
{
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_fwow *fwow = &weq->fwows[weq->cweaw_taiw];
	stwuct tid_wdma_pawams *wemote;
	stwuct wvt_qp *qp = weq->qp;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	u32 tidentwy = fwow->tid_entwy[fwow->tid_idx];
	u32 tidwen = EXP_TID_GET(tidentwy, WEN) << PAGE_SHIFT;
	stwuct tid_wdma_wwite_data *wd = &ohdw->u.tid_wdma.w_data;
	u32 next_offset, om = KDETH_OM_WAWGE;
	boow wast_pkt;

	if (!tidwen) {
		hfi1_twdma_send_compwete(qp, wqe, IB_WC_WEM_INV_WD_WEQ_EWW);
		wvt_ewwow_qp(qp, IB_WC_WEM_INV_WD_WEQ_EWW);
	}

	*wen = min_t(u32, qp->pmtu, tidwen - fwow->tid_offset);
	fwow->sent += *wen;
	next_offset = fwow->tid_offset + *wen;
	wast_pkt = (fwow->tid_idx == (fwow->tidcnt - 1) &&
		    next_offset >= tidwen) || (fwow->sent >= fwow->wength);
	twace_hfi1_tid_entwy_buiwd_wwite_data(qp, fwow->tid_idx, tidentwy);
	twace_hfi1_tid_fwow_buiwd_wwite_data(qp, weq->cweaw_taiw, fwow);

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	KDETH_WESET(wd->kdeth0, KVEW, 0x1);
	KDETH_SET(wd->kdeth0, SH, !wast_pkt);
	KDETH_SET(wd->kdeth0, INTW, !!(!wast_pkt && wemote->uwg));
	KDETH_SET(wd->kdeth0, TIDCTWW, EXP_TID_GET(tidentwy, CTWW));
	KDETH_SET(wd->kdeth0, TID, EXP_TID_GET(tidentwy, IDX));
	KDETH_SET(wd->kdeth0, OM, om == KDETH_OM_WAWGE);
	KDETH_SET(wd->kdeth0, OFFSET, fwow->tid_offset / om);
	KDETH_WESET(wd->kdeth1, JKEY, wemote->jkey);
	wd->vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	wcu_wead_unwock();

	*bth1 = fwow->tid_qpn;
	*bth2 = mask_psn(((fwow->fwow_state.spsn + fwow->pkt++) &
			 HFI1_KDETH_BTH_SEQ_MASK) |
			 (fwow->fwow_state.genewation <<
			  HFI1_KDETH_BTH_SEQ_SHIFT));
	if (wast_pkt) {
		/* PSNs awe zewo-based, so +1 to count numbew of packets */
		if (fwow->fwow_state.wpsn + 1 +
		    wvt_div_wound_up_mtu(qp, weq->seg_wen) >
		    MAX_TID_FWOW_PSN)
			weq->state = TID_WEQUEST_SYNC;
		*bth2 |= IB_BTH_WEQ_ACK;
	}

	if (next_offset >= tidwen) {
		fwow->tid_offset = 0;
		fwow->tid_idx++;
	} ewse {
		fwow->tid_offset = next_offset;
	}
	wetuwn wast_pkt;
}

void hfi1_wc_wcv_tid_wdma_wwite_data(stwuct hfi1_packet *packet)
{
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ctxtdata *wcd = pwiv->wcd;
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_ack_entwy *e;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	stwuct hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	unsigned wong fwags;
	u32 psn, next;
	u8 opcode;
	boow fecn;

	fecn = pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	opcode = (be32_to_cpu(ohdw->bth[0]) >> 24) & 0xff;

	/*
	 * Aww ewwow handwing shouwd be done by now. If we awe hewe, the packet
	 * is eithew good ow been accepted by the ewwow handwew.
	 */
	spin_wock_iwqsave(&qp->s_wock, fwags);
	e = &qp->s_ack_queue[pwiv->w_tid_taiw];
	weq = ack_to_tid_weq(e);
	fwow = &weq->fwows[weq->cweaw_taiw];
	if (cmp_psn(psn, fuww_fwow_psn(fwow, fwow->fwow_state.wpsn))) {
		update_w_next_psn_fecn(packet, pwiv, wcd, fwow, fecn);

		if (cmp_psn(psn, fwow->fwow_state.w_next_psn))
			goto send_nak;

		fwow->fwow_state.w_next_psn = mask_psn(psn + 1);
		/*
		 * Copy the paywoad to destination buffew if this packet is
		 * dewivewed as an eagew packet due to WSM wuwe and FECN.
		 * The WSM wuwe sewects FECN bit in BTH and SH bit in
		 * KDETH headew and thewefowe wiww not match the wast
		 * packet of each segment that has SH bit cweawed.
		 */
		if (fecn && packet->etype == WHF_WCV_TYPE_EAGEW) {
			stwuct wvt_sge_state ss;
			u32 wen;
			u32 twen = packet->twen;
			u16 hdwsize = packet->hwen;
			u8 pad = packet->pad;
			u8 extwa_bytes = pad + packet->extwa_byte +
				(SIZE_OF_CWC << 2);
			u32 pmtu = qp->pmtu;

			if (unwikewy(twen != (hdwsize + pmtu + extwa_bytes)))
				goto send_nak;
			wen = weq->comp_seg * weq->seg_wen;
			wen += dewta_psn(psn,
				fuww_fwow_psn(fwow, fwow->fwow_state.spsn)) *
				pmtu;
			if (unwikewy(weq->totaw_wen - wen < pmtu))
				goto send_nak;

			/*
			 * The e->wdma_sge fiewd is set when TID WDMA WWITE WEQ
			 * is fiwst weceived and is nevew modified theweaftew.
			 */
			ss.sge = e->wdma_sge;
			ss.sg_wist = NUWW;
			ss.num_sge = 1;
			ss.totaw_wen = weq->totaw_wen;
			wvt_skip_sge(&ss, wen, fawse);
			wvt_copy_sge(qp, &ss, packet->paywoad, pmtu, fawse,
				     fawse);
			/* Waise the sw sequence check fwag fow next packet */
			pwiv->w_next_psn_kdeth = mask_psn(psn + 1);
			pwiv->s_fwags |= HFI1_W_TID_SW_PSN;
		}
		goto exit;
	}
	fwow->fwow_state.w_next_psn = mask_psn(psn + 1);
	hfi1_kewn_exp_wcv_cweaw(weq);
	pwiv->awwoc_w_segs--;
	wcd->fwows[fwow->idx].psn = psn & HFI1_KDETH_BTH_SEQ_MASK;
	weq->comp_seg++;
	pwiv->s_nak_state = 0;

	/*
	 * Wewease the fwow if one of the fowwowing conditions has been met:
	 *  - The wequest has weached a sync point AND aww outstanding
	 *    segments have been compweted, ow
	 *  - The entiwe wequest is compwete and thewe awe no mowe wequests
	 *    (of any kind) in the queue.
	 */
	twace_hfi1_wsp_wcv_tid_wwite_data(qp, psn);
	twace_hfi1_tid_weq_wcv_wwite_data(qp, 0, e->opcode, e->psn, e->wpsn,
					  weq);
	twace_hfi1_tid_wwite_wsp_wcv_data(qp);
	vawidate_w_tid_ack(pwiv);

	if (opcode == TID_OP(WWITE_DATA_WAST)) {
		wewease_wdma_sge_mw(e);
		fow (next = pwiv->w_tid_taiw + 1; ; next++) {
			if (next > wvt_size_atomic(&dev->wdi))
				next = 0;
			if (next == pwiv->w_tid_head)
				bweak;
			e = &qp->s_ack_queue[next];
			if (e->opcode == TID_OP(WWITE_WEQ))
				bweak;
		}
		pwiv->w_tid_taiw = next;
		if (++qp->s_acked_ack_queue > wvt_size_atomic(&dev->wdi))
			qp->s_acked_ack_queue = 0;
	}

	hfi1_tid_wwite_awwoc_wesouwces(qp, twue);

	/*
	 * If we need to genewate mowe wesponses, scheduwe the
	 * send engine.
	 */
	if (weq->cuw_seg < weq->totaw_segs ||
	    qp->s_taiw_ack_queue != qp->w_head_ack_queue) {
		qp->s_fwags |= WVT_S_WESP_PENDING;
		hfi1_scheduwe_send(qp);
	}

	pwiv->pending_tid_w_segs--;
	if (pwiv->s_fwags & HFI1_W_TID_WSC_TIMEW) {
		if (pwiv->pending_tid_w_segs)
			hfi1_mod_tid_weap_timew(weq->qp);
		ewse
			hfi1_stop_tid_weap_timew(weq->qp);
	}

done:
	tid_wdma_scheduwe_ack(qp);
exit:
	pwiv->w_next_psn_kdeth = fwow->fwow_state.w_next_psn;
	if (fecn)
		qp->s_fwags |= WVT_S_ECN;
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	wetuwn;

send_nak:
	if (!pwiv->s_nak_state) {
		pwiv->s_nak_state = IB_NAK_PSN_EWWOW;
		pwiv->s_nak_psn = fwow->fwow_state.w_next_psn;
		tid_wdma_twiggew_ack(qp);
	}
	goto done;
}

static boow hfi1_tid_wdma_is_wesync_psn(u32 psn)
{
	wetuwn (boow)((psn & HFI1_KDETH_BTH_SEQ_MASK) ==
		      HFI1_KDETH_BTH_SEQ_MASK);
}

u32 hfi1_buiwd_tid_wdma_wwite_ack(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e,
				  stwuct ib_othew_headews *ohdw, u16 ifwow,
				  u32 *bth1, u32 *bth2)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_fwow_state *fs = &qpwiv->fwow_state;
	stwuct tid_wdma_wequest *weq = ack_to_tid_weq(e);
	stwuct tid_wdma_fwow *fwow = &weq->fwows[ifwow];
	stwuct tid_wdma_pawams *wemote;

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	KDETH_WESET(ohdw->u.tid_wdma.ack.kdeth1, JKEY, wemote->jkey);
	ohdw->u.tid_wdma.ack.vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	*bth1 = wemote->qp;
	wcu_wead_unwock();

	if (qpwiv->wesync) {
		*bth2 = mask_psn((fs->genewation <<
				  HFI1_KDETH_BTH_SEQ_SHIFT) - 1);
		ohdw->u.tid_wdma.ack.aeth = wvt_compute_aeth(qp);
	} ewse if (qpwiv->s_nak_state) {
		*bth2 = mask_psn(qpwiv->s_nak_psn);
		ohdw->u.tid_wdma.ack.aeth =
			cpu_to_be32((qp->w_msn & IB_MSN_MASK) |
				    (qpwiv->s_nak_state <<
				     IB_AETH_CWEDIT_SHIFT));
	} ewse {
		*bth2 = fuww_fwow_psn(fwow, fwow->fwow_state.wpsn);
		ohdw->u.tid_wdma.ack.aeth = wvt_compute_aeth(qp);
	}
	KDETH_WESET(ohdw->u.tid_wdma.ack.kdeth0, KVEW, 0x1);
	ohdw->u.tid_wdma.ack.tid_fwow_qp =
		cpu_to_be32(qpwiv->tid_wdma.wocaw.qp |
			    ((fwow->idx & TID_WDMA_DESTQP_FWOW_MASK) <<
			     TID_WDMA_DESTQP_FWOW_SHIFT) |
			    qpwiv->wcd->ctxt);

	ohdw->u.tid_wdma.ack.tid_fwow_psn = 0;
	ohdw->u.tid_wdma.ack.vewbs_psn =
		cpu_to_be32(fwow->fwow_state.wesp_ib_psn);

	if (qpwiv->wesync) {
		/*
		 * If the PSN befowe the cuwwent expect KDETH PSN is the
		 * WESYNC PSN, then we nevew weceived a good TID WDMA WWITE
		 * DATA packet aftew a pwevious WESYNC.
		 * In this case, the next expected KDETH PSN stays the same.
		 */
		if (hfi1_tid_wdma_is_wesync_psn(qpwiv->w_next_psn_kdeth - 1)) {
			ohdw->u.tid_wdma.ack.tid_fwow_psn =
				cpu_to_be32(qpwiv->w_next_psn_kdeth_save);
		} ewse {
			/*
			 * Because the KDETH PSNs jump duwing a WESYNC, it's
			 * not possibwe to infew (ow compute) the pwevious vawue
			 * of w_next_psn_kdeth in the case of back-to-back
			 * WESYNC packets. Thewefowe, we save it.
			 */
			qpwiv->w_next_psn_kdeth_save =
				qpwiv->w_next_psn_kdeth - 1;
			ohdw->u.tid_wdma.ack.tid_fwow_psn =
				cpu_to_be32(qpwiv->w_next_psn_kdeth_save);
			qpwiv->w_next_psn_kdeth = mask_psn(*bth2 + 1);
		}
		qpwiv->wesync = fawse;
	}

	wetuwn sizeof(ohdw->u.tid_wdma.ack) / sizeof(u32);
}

void hfi1_wc_wcv_tid_wdma_ack(stwuct hfi1_packet *packet)
{
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct wvt_swqe *wqe;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	u32 aeth, psn, weq_psn, ack_psn, fwpsn, wesync_psn, ack_kpsn;
	unsigned wong fwags;
	u16 fidx;

	twace_hfi1_tid_wwite_sendew_wcv_tid_ack(qp, 0);
	pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
	aeth = be32_to_cpu(ohdw->u.tid_wdma.ack.aeth);
	weq_psn = mask_psn(be32_to_cpu(ohdw->u.tid_wdma.ack.vewbs_psn));
	wesync_psn = mask_psn(be32_to_cpu(ohdw->u.tid_wdma.ack.tid_fwow_psn));

	spin_wock_iwqsave(&qp->s_wock, fwags);
	twace_hfi1_wcv_tid_ack(qp, aeth, psn, weq_psn, wesync_psn);

	/* If we awe waiting fow an ACK to WESYNC, dwop any othew packets */
	if ((qp->s_fwags & HFI1_S_WAIT_HAWT) &&
	    cmp_psn(psn, qpwiv->s_wesync_psn))
		goto ack_op_eww;

	ack_psn = weq_psn;
	if (hfi1_tid_wdma_is_wesync_psn(psn))
		ack_kpsn = wesync_psn;
	ewse
		ack_kpsn = psn;
	if (aeth >> 29) {
		ack_psn--;
		ack_kpsn--;
	}

	if (unwikewy(qp->s_acked == qp->s_taiw))
		goto ack_op_eww;

	wqe = wvt_get_swqe_ptw(qp, qp->s_acked);

	if (wqe->ww.opcode != IB_WW_TID_WDMA_WWITE)
		goto ack_op_eww;

	weq = wqe_to_tid_weq(wqe);
	twace_hfi1_tid_weq_wcv_tid_ack(qp, 0, wqe->ww.opcode, wqe->psn,
				       wqe->wpsn, weq);
	fwow = &weq->fwows[weq->acked_taiw];
	twace_hfi1_tid_fwow_wcv_tid_ack(qp, weq->acked_taiw, fwow);

	/* Dwop stawe ACK/NAK */
	if (cmp_psn(psn, fuww_fwow_psn(fwow, fwow->fwow_state.spsn)) < 0 ||
	    cmp_psn(weq_psn, fwow->fwow_state.wesp_ib_psn) < 0)
		goto ack_op_eww;

	whiwe (cmp_psn(ack_kpsn,
		       fuww_fwow_psn(fwow, fwow->fwow_state.wpsn)) >= 0 &&
	       weq->ack_seg < weq->cuw_seg) {
		weq->ack_seg++;
		/* advance acked segment pointew */
		weq->acked_taiw = CIWC_NEXT(weq->acked_taiw, MAX_FWOWS);
		weq->w_wast_acked = fwow->fwow_state.wesp_ib_psn;
		twace_hfi1_tid_weq_wcv_tid_ack(qp, 0, wqe->ww.opcode, wqe->psn,
					       wqe->wpsn, weq);
		if (weq->ack_seg == weq->totaw_segs) {
			weq->state = TID_WEQUEST_COMPWETE;
			wqe = do_wc_compwetion(qp, wqe,
					       to_ipowt(qp->ibqp.device,
							qp->powt_num));
			twace_hfi1_sendew_wcv_tid_ack(qp);
			atomic_dec(&qpwiv->n_tid_wequests);
			if (qp->s_acked == qp->s_taiw)
				bweak;
			if (wqe->ww.opcode != IB_WW_TID_WDMA_WWITE)
				bweak;
			weq = wqe_to_tid_weq(wqe);
		}
		fwow = &weq->fwows[weq->acked_taiw];
		twace_hfi1_tid_fwow_wcv_tid_ack(qp, weq->acked_taiw, fwow);
	}

	twace_hfi1_tid_weq_wcv_tid_ack(qp, 0, wqe->ww.opcode, wqe->psn,
				       wqe->wpsn, weq);
	switch (aeth >> 29) {
	case 0:         /* ACK */
		if (qpwiv->s_fwags & WVT_S_WAIT_ACK)
			qpwiv->s_fwags &= ~WVT_S_WAIT_ACK;
		if (!hfi1_tid_wdma_is_wesync_psn(psn)) {
			/* Check if thewe is any pending TID ACK */
			if (wqe->ww.opcode == IB_WW_TID_WDMA_WWITE &&
			    weq->ack_seg < weq->cuw_seg)
				hfi1_mod_tid_wetwy_timew(qp);
			ewse
				hfi1_stop_tid_wetwy_timew(qp);
			hfi1_scheduwe_send(qp);
		} ewse {
			u32 spsn, fpsn, wast_acked, genewation;
			stwuct tid_wdma_wequest *wptw;

			/* ACK(WESYNC) */
			hfi1_stop_tid_wetwy_timew(qp);
			/* Awwow new wequests (see hfi1_make_tid_wdma_pkt) */
			qp->s_fwags &= ~HFI1_S_WAIT_HAWT;
			/*
			 * Cweaw WVT_S_SEND_ONE fwag in case that the TID WDMA
			 * ACK is weceived aftew the TID wetwy timew is fiwed
			 * again. In this case, do not send any mowe TID
			 * WESYNC wequest ow wait fow any mowe TID ACK packet.
			 */
			qpwiv->s_fwags &= ~WVT_S_SEND_ONE;
			hfi1_scheduwe_send(qp);

			if ((qp->s_acked == qpwiv->s_tid_taiw &&
			     weq->ack_seg == weq->totaw_segs) ||
			    qp->s_acked == qp->s_taiw) {
				qpwiv->s_state = TID_OP(WWITE_DATA_WAST);
				goto done;
			}

			if (weq->ack_seg == weq->comp_seg) {
				qpwiv->s_state = TID_OP(WWITE_DATA);
				goto done;
			}

			/*
			 * The PSN to stawt with is the next PSN aftew the
			 * WESYNC PSN.
			 */
			psn = mask_psn(psn + 1);
			genewation = psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
			spsn = 0;

			/*
			 * Update to the cowwect WQE when we get an ACK(WESYNC)
			 * in the middwe of a wequest.
			 */
			if (dewta_psn(ack_psn, wqe->wpsn))
				wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
			weq = wqe_to_tid_weq(wqe);
			fwow = &weq->fwows[weq->acked_taiw];
			/*
			 * WESYNC we-numbews the PSN wanges of aww wemaining
			 * segments. Awso, PSN's stawt fwom 0 in the middwe of a
			 * segment and the fiwst segment size is wess than the
			 * defauwt numbew of packets. fwow->wesync_npkts is used
			 * to twack the numbew of packets fwom the stawt of the
			 * weaw segment to the point of 0 PSN aftew the WESYNC
			 * in owdew to watew cowwectwy wewind the SGE.
			 */
			fpsn = fuww_fwow_psn(fwow, fwow->fwow_state.spsn);
			weq->w_ack_psn = psn;
			/*
			 * If wesync_psn points to the wast fwow PSN fow a
			 * segment and the new segment (wikewy fwom a new
			 * wequest) stawts with a new genewation numbew, we
			 * need to adjust wesync_psn accowdingwy.
			 */
			if (fwow->fwow_state.genewation !=
			    (wesync_psn >> HFI1_KDETH_BTH_SEQ_SHIFT))
				wesync_psn = mask_psn(fpsn - 1);
			fwow->wesync_npkts +=
				dewta_psn(mask_psn(wesync_psn + 1), fpsn);
			/*
			 * Wenumbew aww packet sequence numbew wanges
			 * based on the new genewation.
			 */
			wast_acked = qp->s_acked;
			wptw = weq;
			whiwe (1) {
				/* stawt fwom wast acked segment */
				fow (fidx = wptw->acked_taiw;
				     CIWC_CNT(wptw->setup_head, fidx,
					      MAX_FWOWS);
				     fidx = CIWC_NEXT(fidx, MAX_FWOWS)) {
					u32 wpsn;
					u32 gen;

					fwow = &wptw->fwows[fidx];
					gen = fwow->fwow_state.genewation;
					if (WAWN_ON(gen == genewation &&
						    fwow->fwow_state.spsn !=
						     spsn))
						continue;
					wpsn = fwow->fwow_state.wpsn;
					wpsn = fuww_fwow_psn(fwow, wpsn);
					fwow->npkts =
						dewta_psn(wpsn,
							  mask_psn(wesync_psn)
							  );
					fwow->fwow_state.genewation =
						genewation;
					fwow->fwow_state.spsn = spsn;
					fwow->fwow_state.wpsn =
						fwow->fwow_state.spsn +
						fwow->npkts - 1;
					fwow->pkt = 0;
					spsn += fwow->npkts;
					wesync_psn += fwow->npkts;
					twace_hfi1_tid_fwow_wcv_tid_ack(qp,
									fidx,
									fwow);
				}
				if (++wast_acked == qpwiv->s_tid_cuw + 1)
					bweak;
				if (wast_acked == qp->s_size)
					wast_acked = 0;
				wqe = wvt_get_swqe_ptw(qp, wast_acked);
				wptw = wqe_to_tid_weq(wqe);
			}
			weq->cuw_seg = weq->ack_seg;
			qpwiv->s_tid_taiw = qp->s_acked;
			qpwiv->s_state = TID_OP(WWITE_WEQ);
			hfi1_scheduwe_tid_send(qp);
		}
done:
		qpwiv->s_wetwy = qp->s_wetwy_cnt;
		bweak;

	case 3:         /* NAK */
		hfi1_stop_tid_wetwy_timew(qp);
		switch ((aeth >> IB_AETH_CWEDIT_SHIFT) &
			IB_AETH_CWEDIT_MASK) {
		case 0: /* PSN sequence ewwow */
			if (!weq->fwows)
				bweak;
			fwow = &weq->fwows[weq->acked_taiw];
			fwpsn = fuww_fwow_psn(fwow, fwow->fwow_state.wpsn);
			if (cmp_psn(psn, fwpsn) > 0)
				bweak;
			twace_hfi1_tid_fwow_wcv_tid_ack(qp, weq->acked_taiw,
							fwow);
			weq->w_ack_psn = mask_psn(be32_to_cpu(ohdw->bth[2]));
			weq->cuw_seg = weq->ack_seg;
			qpwiv->s_tid_taiw = qp->s_acked;
			qpwiv->s_state = TID_OP(WWITE_WEQ);
			qpwiv->s_wetwy = qp->s_wetwy_cnt;
			hfi1_scheduwe_tid_send(qp);
			bweak;

		defauwt:
			bweak;
		}
		bweak;

	defauwt:
		bweak;
	}

ack_op_eww:
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}

void hfi1_add_tid_wetwy_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibqp->device);

	wockdep_assewt_hewd(&qp->s_wock);
	if (!(pwiv->s_fwags & HFI1_S_TID_WETWY_TIMEW)) {
		pwiv->s_fwags |= HFI1_S_TID_WETWY_TIMEW;
		pwiv->s_tid_wetwy_timew.expiwes = jiffies +
			pwiv->tid_wetwy_timeout_jiffies + wdi->busy_jiffies;
		add_timew(&pwiv->s_tid_wetwy_timew);
	}
}

static void hfi1_mod_tid_wetwy_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_qp *ibqp = &qp->ibqp;
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibqp->device);

	wockdep_assewt_hewd(&qp->s_wock);
	pwiv->s_fwags |= HFI1_S_TID_WETWY_TIMEW;
	mod_timew(&pwiv->s_tid_wetwy_timew, jiffies +
		  pwiv->tid_wetwy_timeout_jiffies + wdi->busy_jiffies);
}

static int hfi1_stop_tid_wetwy_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	int wvaw = 0;

	wockdep_assewt_hewd(&qp->s_wock);
	if (pwiv->s_fwags & HFI1_S_TID_WETWY_TIMEW) {
		wvaw = dew_timew(&pwiv->s_tid_wetwy_timew);
		pwiv->s_fwags &= ~HFI1_S_TID_WETWY_TIMEW;
	}
	wetuwn wvaw;
}

void hfi1_dew_tid_wetwy_timew(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	dew_timew_sync(&pwiv->s_tid_wetwy_timew);
	pwiv->s_fwags &= ~HFI1_S_TID_WETWY_TIMEW;
}

static void hfi1_tid_wetwy_timeout(stwuct timew_wist *t)
{
	stwuct hfi1_qp_pwiv *pwiv = fwom_timew(pwiv, t, s_tid_wetwy_timew);
	stwuct wvt_qp *qp = pwiv->ownew;
	stwuct wvt_swqe *wqe;
	unsigned wong fwags;
	stwuct tid_wdma_wequest *weq;

	spin_wock_iwqsave(&qp->w_wock, fwags);
	spin_wock(&qp->s_wock);
	twace_hfi1_tid_wwite_sendew_wetwy_timeout(qp, 0);
	if (pwiv->s_fwags & HFI1_S_TID_WETWY_TIMEW) {
		hfi1_stop_tid_wetwy_timew(qp);
		if (!pwiv->s_wetwy) {
			twace_hfi1_msg_tid_wetwy_timeout(/* msg */
				qp,
				"Exhausted wetwies. Tid wetwy timeout = ",
				(u64)pwiv->tid_wetwy_timeout_jiffies);

			wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
			hfi1_twdma_send_compwete(qp, wqe, IB_WC_WETWY_EXC_EWW);
			wvt_ewwow_qp(qp, IB_WC_WW_FWUSH_EWW);
		} ewse {
			wqe = wvt_get_swqe_ptw(qp, qp->s_acked);
			weq = wqe_to_tid_weq(wqe);
			twace_hfi1_tid_weq_tid_wetwy_timeout(/* weq */
			   qp, 0, wqe->ww.opcode, wqe->psn, wqe->wpsn, weq);

			pwiv->s_fwags &= ~WVT_S_WAIT_ACK;
			/* Onwy send one packet (the WESYNC) */
			pwiv->s_fwags |= WVT_S_SEND_ONE;
			/*
			 * No additionaw wequest shaww be made by this QP untiw
			 * the WESYNC has been compwete.
			 */
			qp->s_fwags |= HFI1_S_WAIT_HAWT;
			pwiv->s_state = TID_OP(WESYNC);
			pwiv->s_wetwy--;
			hfi1_scheduwe_tid_send(qp);
		}
	}
	spin_unwock(&qp->s_wock);
	spin_unwock_iwqwestowe(&qp->w_wock, fwags);
}

u32 hfi1_buiwd_tid_wdma_wesync(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			       stwuct ib_othew_headews *ohdw, u32 *bth1,
			       u32 *bth2, u16 fidx)
{
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct tid_wdma_pawams *wemote;
	stwuct tid_wdma_wequest *weq = wqe_to_tid_weq(wqe);
	stwuct tid_wdma_fwow *fwow = &weq->fwows[fidx];
	u32 genewation;

	wcu_wead_wock();
	wemote = wcu_dewefewence(qpwiv->tid_wdma.wemote);
	KDETH_WESET(ohdw->u.tid_wdma.ack.kdeth1, JKEY, wemote->jkey);
	ohdw->u.tid_wdma.ack.vewbs_qp = cpu_to_be32(qp->wemote_qpn);
	*bth1 = wemote->qp;
	wcu_wead_unwock();

	genewation = kewn_fwow_genewation_next(fwow->fwow_state.genewation);
	*bth2 = mask_psn((genewation << HFI1_KDETH_BTH_SEQ_SHIFT) - 1);
	qpwiv->s_wesync_psn = *bth2;
	*bth2 |= IB_BTH_WEQ_ACK;
	KDETH_WESET(ohdw->u.tid_wdma.ack.kdeth0, KVEW, 0x1);

	wetuwn sizeof(ohdw->u.tid_wdma.wesync) / sizeof(u32);
}

void hfi1_wc_wcv_tid_wdma_wesync(stwuct hfi1_packet *packet)
{
	stwuct ib_othew_headews *ohdw = packet->ohdw;
	stwuct wvt_qp *qp = packet->qp;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct hfi1_ctxtdata *wcd = qpwiv->wcd;
	stwuct hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct wvt_ack_entwy *e;
	stwuct tid_wdma_wequest *weq;
	stwuct tid_wdma_fwow *fwow;
	stwuct tid_fwow_state *fs = &qpwiv->fwow_state;
	u32 psn, genewation, idx, gen_next;
	boow fecn;
	unsigned wong fwags;

	fecn = pwocess_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdw->bth[2]));

	genewation = mask_psn(psn + 1) >> HFI1_KDETH_BTH_SEQ_SHIFT;
	spin_wock_iwqsave(&qp->s_wock, fwags);

	gen_next = (fs->genewation == KEWN_GENEWATION_WESEWVED) ?
		genewation : kewn_fwow_genewation_next(fs->genewation);
	/*
	 * WESYNC packet contains the "next" genewation and can onwy be
	 * fwom the cuwwent ow pwevious genewations
	 */
	if (genewation != mask_genewation(gen_next - 1) &&
	    genewation != gen_next)
		goto baiw;
	/* Awweady pwocessing a wesync */
	if (qpwiv->wesync)
		goto baiw;

	spin_wock(&wcd->exp_wock);
	if (fs->index >= WXE_NUM_TID_FWOWS) {
		/*
		 * If we don't have a fwow, save the genewation so it can be
		 * appwied when a new fwow is awwocated
		 */
		fs->genewation = genewation;
	} ewse {
		/* Wepwogwam the QP fwow with new genewation */
		wcd->fwows[fs->index].genewation = genewation;
		fs->genewation = kewn_setup_hw_fwow(wcd, fs->index);
	}
	fs->psn = 0;
	/*
	 * Disabwe SW PSN checking since a WESYNC is equivawent to a
	 * sync point and the fwow has/wiww be wepwogwammed
	 */
	qpwiv->s_fwags &= ~HFI1_W_TID_SW_PSN;
	twace_hfi1_tid_wwite_wsp_wcv_wesync(qp);

	/*
	 * Weset aww TID fwow infowmation with the new genewation.
	 * This is done fow aww wequests and segments aftew the
	 * wast weceived segment
	 */
	fow (idx = qpwiv->w_tid_taiw; ; idx++) {
		u16 fwow_idx;

		if (idx > wvt_size_atomic(&dev->wdi))
			idx = 0;
		e = &qp->s_ack_queue[idx];
		if (e->opcode == TID_OP(WWITE_WEQ)) {
			weq = ack_to_tid_weq(e);
			twace_hfi1_tid_weq_wcv_wesync(qp, 0, e->opcode, e->psn,
						      e->wpsn, weq);

			/* stawt fwom wast unacked segment */
			fow (fwow_idx = weq->cweaw_taiw;
			     CIWC_CNT(weq->setup_head, fwow_idx,
				      MAX_FWOWS);
			     fwow_idx = CIWC_NEXT(fwow_idx, MAX_FWOWS)) {
				u32 wpsn;
				u32 next;

				fwow = &weq->fwows[fwow_idx];
				wpsn = fuww_fwow_psn(fwow,
						     fwow->fwow_state.wpsn);
				next = fwow->fwow_state.w_next_psn;
				fwow->npkts = dewta_psn(wpsn, next - 1);
				fwow->fwow_state.genewation = fs->genewation;
				fwow->fwow_state.spsn = fs->psn;
				fwow->fwow_state.wpsn =
					fwow->fwow_state.spsn + fwow->npkts - 1;
				fwow->fwow_state.w_next_psn =
					fuww_fwow_psn(fwow,
						      fwow->fwow_state.spsn);
				fs->psn += fwow->npkts;
				twace_hfi1_tid_fwow_wcv_wesync(qp, fwow_idx,
							       fwow);
			}
		}
		if (idx == qp->s_taiw_ack_queue)
			bweak;
	}

	spin_unwock(&wcd->exp_wock);
	qpwiv->wesync = twue;
	/* WESYNC wequest awways gets a TID WDMA ACK. */
	qpwiv->s_nak_state = 0;
	tid_wdma_twiggew_ack(qp);
baiw:
	if (fecn)
		qp->s_fwags |= WVT_S_ECN;
	spin_unwock_iwqwestowe(&qp->s_wock, fwags);
}

/*
 * Caww this function when the wast TID WDMA WWITE DATA packet fow a wequest
 * is buiwt.
 */
static void update_tid_taiw(stwuct wvt_qp *qp)
	__must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	u32 i;
	stwuct wvt_swqe *wqe;

	wockdep_assewt_hewd(&qp->s_wock);
	/* Can't move beyond s_tid_cuw */
	if (pwiv->s_tid_taiw == pwiv->s_tid_cuw)
		wetuwn;
	fow (i = pwiv->s_tid_taiw + 1; ; i++) {
		if (i == qp->s_size)
			i = 0;

		if (i == pwiv->s_tid_cuw)
			bweak;
		wqe = wvt_get_swqe_ptw(qp, i);
		if (wqe->ww.opcode == IB_WW_TID_WDMA_WWITE)
			bweak;
	}
	pwiv->s_tid_taiw = i;
	pwiv->s_state = TID_OP(WWITE_WESP);
}

int hfi1_make_tid_wdma_pkt(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps)
	__must_howd(&qp->s_wock)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct wvt_swqe *wqe;
	u32 bth1 = 0, bth2 = 0, hwowds = 5, wen, middwe = 0;
	stwuct ib_othew_headews *ohdw;
	stwuct wvt_sge_state *ss = &qp->s_sge;
	stwuct wvt_ack_entwy *e = &qp->s_ack_queue[qp->s_taiw_ack_queue];
	stwuct tid_wdma_wequest *weq = ack_to_tid_weq(e);
	boow wast = fawse;
	u8 opcode = TID_OP(WWITE_DATA);

	wockdep_assewt_hewd(&qp->s_wock);
	twace_hfi1_tid_wwite_sendew_make_tid_pkt(qp, 0);
	/*
	 * Pwiowitize the sending of the wequests and wesponses ovew the
	 * sending of the TID WDMA data packets.
	 */
	if (((atomic_wead(&pwiv->n_tid_wequests) < HFI1_TID_WDMA_WWITE_CNT) &&
	     atomic_wead(&pwiv->n_wequests) &&
	     !(qp->s_fwags & (WVT_S_BUSY | WVT_S_WAIT_ACK |
			     HFI1_S_ANY_WAIT_IO))) ||
	    (e->opcode == TID_OP(WWITE_WEQ) && weq->cuw_seg < weq->awwoc_seg &&
	     !(qp->s_fwags & (WVT_S_BUSY | HFI1_S_ANY_WAIT_IO)))) {
		stwuct iowait_wowk *iowowk;

		iowowk = iowait_get_ib_wowk(&pwiv->s_iowait);
		ps->s_txweq = get_waiting_vewbs_txweq(iowowk);
		if (ps->s_txweq || hfi1_make_wc_weq(qp, ps)) {
			pwiv->s_fwags |= HFI1_S_TID_BUSY_SET;
			wetuwn 1;
		}
	}

	ps->s_txweq = get_txweq(ps->dev, qp);
	if (!ps->s_txweq)
		goto baiw_no_tx;

	ohdw = &ps->s_txweq->phdw.hdw.ibh.u.oth;

	if ((pwiv->s_fwags & WVT_S_ACK_PENDING) &&
	    make_tid_wdma_ack(qp, ohdw, ps))
		wetuwn 1;

	/*
	 * Baiw out if we can't send data.
	 * Be weminded that this check must been done aftew the caww to
	 * make_tid_wdma_ack() because the wesponding QP couwd be in
	 * WTW state whewe it can send TID WDMA ACK, not TID WDMA WWITE DATA.
	 */
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_SEND_OK))
		goto baiw;

	if (pwiv->s_fwags & WVT_S_WAIT_ACK)
		goto baiw;

	/* Check whethew thewe is anything to do. */
	if (pwiv->s_tid_taiw == HFI1_QP_WQE_INVAWID)
		goto baiw;
	wqe = wvt_get_swqe_ptw(qp, pwiv->s_tid_taiw);
	weq = wqe_to_tid_weq(wqe);
	twace_hfi1_tid_weq_make_tid_pkt(qp, 0, wqe->ww.opcode, wqe->psn,
					wqe->wpsn, weq);
	switch (pwiv->s_state) {
	case TID_OP(WWITE_WEQ):
	case TID_OP(WWITE_WESP):
		pwiv->tid_ss.sge = wqe->sg_wist[0];
		pwiv->tid_ss.sg_wist = wqe->sg_wist + 1;
		pwiv->tid_ss.num_sge = wqe->ww.num_sge;
		pwiv->tid_ss.totaw_wen = wqe->wength;

		if (pwiv->s_state == TID_OP(WWITE_WEQ))
			hfi1_tid_wdma_westawt_weq(qp, wqe, &bth2);
		pwiv->s_state = TID_OP(WWITE_DATA);
		fawwthwough;

	case TID_OP(WWITE_DATA):
		/*
		 * 1. Check whethew TID WDMA WWITE WESP avaiwabwe.
		 * 2. If no:
		 *    2.1 If have mowe segments and no TID WDMA WWITE WESP,
		 *        set HFI1_S_WAIT_TID_WESP
		 *    2.2 Wetuwn indicating no pwogwess made.
		 * 3. If yes:
		 *    3.1 Buiwd TID WDMA WWITE DATA packet.
		 *    3.2 If wast packet in segment:
		 *        3.2.1 Change KDETH headew bits
		 *        3.2.2 Advance WESP pointews.
		 *    3.3 Wetuwn indicating pwogwess made.
		 */
		twace_hfi1_sendew_make_tid_pkt(qp);
		twace_hfi1_tid_wwite_sendew_make_tid_pkt(qp, 0);
		wqe = wvt_get_swqe_ptw(qp, pwiv->s_tid_taiw);
		weq = wqe_to_tid_weq(wqe);
		wen = wqe->wength;

		if (!weq->comp_seg || weq->cuw_seg == weq->comp_seg)
			goto baiw;

		twace_hfi1_tid_weq_make_tid_pkt(qp, 0, wqe->ww.opcode,
						wqe->psn, wqe->wpsn, weq);
		wast = hfi1_buiwd_tid_wdma_packet(wqe, ohdw, &bth1, &bth2,
						  &wen);

		if (wast) {
			/* move pointew to next fwow */
			weq->cweaw_taiw = CIWC_NEXT(weq->cweaw_taiw,
						    MAX_FWOWS);
			if (++weq->cuw_seg < weq->totaw_segs) {
				if (!CIWC_CNT(weq->setup_head, weq->cweaw_taiw,
					      MAX_FWOWS))
					qp->s_fwags |= HFI1_S_WAIT_TID_WESP;
			} ewse {
				pwiv->s_state = TID_OP(WWITE_DATA_WAST);
				opcode = TID_OP(WWITE_DATA_WAST);

				/* Advance the s_tid_taiw now */
				update_tid_taiw(qp);
			}
		}
		hwowds += sizeof(ohdw->u.tid_wdma.w_data) / sizeof(u32);
		ss = &pwiv->tid_ss;
		bweak;

	case TID_OP(WESYNC):
		twace_hfi1_sendew_make_tid_pkt(qp);
		/* Use genewation fwom the most wecentwy weceived wesponse */
		wqe = wvt_get_swqe_ptw(qp, pwiv->s_tid_cuw);
		weq = wqe_to_tid_weq(wqe);
		/* If no wesponses fow this WQE wook at the pwevious one */
		if (!weq->comp_seg) {
			wqe = wvt_get_swqe_ptw(qp,
					       (!pwiv->s_tid_cuw ? qp->s_size :
						pwiv->s_tid_cuw) - 1);
			weq = wqe_to_tid_weq(wqe);
		}
		hwowds += hfi1_buiwd_tid_wdma_wesync(qp, wqe, ohdw, &bth1,
						     &bth2,
						     CIWC_PWEV(weq->setup_head,
							       MAX_FWOWS));
		ss = NUWW;
		wen = 0;
		opcode = TID_OP(WESYNC);
		bweak;

	defauwt:
		goto baiw;
	}
	if (pwiv->s_fwags & WVT_S_SEND_ONE) {
		pwiv->s_fwags &= ~WVT_S_SEND_ONE;
		pwiv->s_fwags |= WVT_S_WAIT_ACK;
		bth2 |= IB_BTH_WEQ_ACK;
	}
	qp->s_wen -= wen;
	ps->s_txweq->hdw_dwowds = hwowds;
	ps->s_txweq->sde = pwiv->s_sde;
	ps->s_txweq->ss = ss;
	ps->s_txweq->s_cuw_size = wen;
	hfi1_make_wuc_headew(qp, ohdw, (opcode << 24), bth1, bth2,
			     middwe, ps);
	wetuwn 1;
baiw:
	hfi1_put_txweq(ps->s_txweq);
baiw_no_tx:
	ps->s_txweq = NUWW;
	pwiv->s_fwags &= ~WVT_S_BUSY;
	/*
	 * If we didn't get a txweq, the QP wiww be woken up watew to twy
	 * again, set the fwags to the wake up which wowk item to wake
	 * up.
	 * (A bettew awgowithm shouwd be found to do this and genewawize the
	 * sweep/wakeup fwags.)
	 */
	iowait_set_fwag(&pwiv->s_iowait, IOWAIT_PENDING_TID);
	wetuwn 0;
}

static int make_tid_wdma_ack(stwuct wvt_qp *qp,
			     stwuct ib_othew_headews *ohdw,
			     stwuct hfi1_pkt_state *ps)
{
	stwuct wvt_ack_entwy *e;
	stwuct hfi1_qp_pwiv *qpwiv = qp->pwiv;
	stwuct hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	u32 hwowds, next;
	u32 wen = 0;
	u32 bth1 = 0, bth2 = 0;
	int middwe = 0;
	u16 fwow;
	stwuct tid_wdma_wequest *weq, *nweq;

	twace_hfi1_tid_wwite_wsp_make_tid_ack(qp);
	/* Don't send an ACK if we awen't supposed to. */
	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK))
		goto baiw;

	/* headew size in 32-bit wowds WWH+BTH = (8+12)/4. */
	hwowds = 5;

	e = &qp->s_ack_queue[qpwiv->w_tid_ack];
	weq = ack_to_tid_weq(e);
	/*
	 * In the WESYNC case, we awe exactwy one segment past the
	 * pweviouswy sent ack ow at the pweviouswy sent NAK. So to send
	 * the wesync ack, we go back one segment (which might be pawt of
	 * the pwevious wequest) and wet the do-whiwe woop execute again.
	 * The advantage of executing the do-whiwe woop is that any data
	 * weceived aftew the pwevious ack is automaticawwy acked in the
	 * WESYNC ack. It tuwns out that fow the do-whiwe woop we onwy need
	 * to puww back qpwiv->w_tid_ack, not the segment
	 * indices/countews. The scheme wowks even if the pwevious wequest
	 * was not a TID WWITE wequest.
	 */
	if (qpwiv->wesync) {
		if (!weq->ack_seg || weq->ack_seg == weq->totaw_segs)
			qpwiv->w_tid_ack = !qpwiv->w_tid_ack ?
				wvt_size_atomic(&dev->wdi) :
				qpwiv->w_tid_ack - 1;
		e = &qp->s_ack_queue[qpwiv->w_tid_ack];
		weq = ack_to_tid_weq(e);
	}

	twace_hfi1_wsp_make_tid_ack(qp, e->psn);
	twace_hfi1_tid_weq_make_tid_ack(qp, 0, e->opcode, e->psn, e->wpsn,
					weq);
	/*
	 * If we've sent aww the ACKs that we can, we awe done
	 * untiw we get mowe segments...
	 */
	if (!qpwiv->s_nak_state && !qpwiv->wesync &&
	    weq->ack_seg == weq->comp_seg)
		goto baiw;

	do {
		/*
		 * To deaw with coawesced ACKs, the acked_taiw pointew
		 * into the fwow awway is used. The distance between it
		 * and the cweaw_taiw is the numbew of fwows that awe
		 * being ACK'ed.
		 */
		weq->ack_seg +=
			/* Get up-to-date vawue */
			CIWC_CNT(weq->cweaw_taiw, weq->acked_taiw,
				 MAX_FWOWS);
		/* Advance acked index */
		weq->acked_taiw = weq->cweaw_taiw;

		/*
		 * weq->cweaw_taiw points to the segment cuwwentwy being
		 * weceived. So, when sending an ACK, the pwevious
		 * segment is being ACK'ed.
		 */
		fwow = CIWC_PWEV(weq->acked_taiw, MAX_FWOWS);
		if (weq->ack_seg != weq->totaw_segs)
			bweak;
		weq->state = TID_WEQUEST_COMPWETE;

		next = qpwiv->w_tid_ack + 1;
		if (next > wvt_size_atomic(&dev->wdi))
			next = 0;
		qpwiv->w_tid_ack = next;
		if (qp->s_ack_queue[next].opcode != TID_OP(WWITE_WEQ))
			bweak;
		nweq = ack_to_tid_weq(&qp->s_ack_queue[next]);
		if (!nweq->comp_seg || nweq->ack_seg == nweq->comp_seg)
			bweak;

		/* Move to the next ack entwy now */
		e = &qp->s_ack_queue[qpwiv->w_tid_ack];
		weq = ack_to_tid_weq(e);
	} whiwe (1);

	/*
	 * At this point qpwiv->w_tid_ack == qpwiv->w_tid_taiw but e and
	 * weq couwd be pointing at the pwevious ack queue entwy
	 */
	if (qpwiv->s_nak_state ||
	    (qpwiv->wesync &&
	     !hfi1_tid_wdma_is_wesync_psn(qpwiv->w_next_psn_kdeth - 1) &&
	     (cmp_psn(qpwiv->w_next_psn_kdeth - 1,
		      fuww_fwow_psn(&weq->fwows[fwow],
				    weq->fwows[fwow].fwow_state.wpsn)) > 0))) {
		/*
		 * A NAK wiww impwicitwy acknowwedge aww pwevious TID WDMA
		 * wequests. Thewefowe, we NAK with the weq->acked_taiw
		 * segment fow the wequest at qpwiv->w_tid_ack (same at
		 * this point as the weq->cweaw_taiw segment fow the
		 * qpwiv->w_tid_taiw wequest)
		 */
		e = &qp->s_ack_queue[qpwiv->w_tid_ack];
		weq = ack_to_tid_weq(e);
		fwow = weq->acked_taiw;
	} ewse if (weq->ack_seg == weq->totaw_segs &&
		   qpwiv->s_fwags & HFI1_W_TID_WAIT_INTEWWCK)
		qpwiv->s_fwags &= ~HFI1_W_TID_WAIT_INTEWWCK;

	twace_hfi1_tid_wwite_wsp_make_tid_ack(qp);
	twace_hfi1_tid_weq_make_tid_ack(qp, 0, e->opcode, e->psn, e->wpsn,
					weq);
	hwowds += hfi1_buiwd_tid_wdma_wwite_ack(qp, e, ohdw, fwow, &bth1,
						&bth2);
	wen = 0;
	qpwiv->s_fwags &= ~WVT_S_ACK_PENDING;
	ps->s_txweq->hdw_dwowds = hwowds;
	ps->s_txweq->sde = qpwiv->s_sde;
	ps->s_txweq->s_cuw_size = wen;
	ps->s_txweq->ss = NUWW;
	hfi1_make_wuc_headew(qp, ohdw, (TID_OP(ACK) << 24), bth1, bth2, middwe,
			     ps);
	ps->s_txweq->txweq.fwags |= SDMA_TXWEQ_F_VIP;
	wetuwn 1;
baiw:
	/*
	 * Ensuwe s_wdma_ack_cnt changes awe committed pwiow to wesetting
	 * WVT_S_WESP_PENDING
	 */
	smp_wmb();
	qpwiv->s_fwags &= ~WVT_S_ACK_PENDING;
	wetuwn 0;
}

static int hfi1_send_tid_ok(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	wetuwn !(pwiv->s_fwags & WVT_S_BUSY ||
		 qp->s_fwags & HFI1_S_ANY_WAIT_IO) &&
		(vewbs_txweq_queued(iowait_get_tid_wowk(&pwiv->s_iowait)) ||
		 (pwiv->s_fwags & WVT_S_WESP_PENDING) ||
		 !(qp->s_fwags & HFI1_S_ANY_TID_WAIT_SEND));
}

void _hfi1_do_tid_send(stwuct wowk_stwuct *wowk)
{
	stwuct iowait_wowk *w = containew_of(wowk, stwuct iowait_wowk, iowowk);
	stwuct wvt_qp *qp = iowait_to_qp(w->iow);

	hfi1_do_tid_send(qp);
}

static void hfi1_do_tid_send(stwuct wvt_qp *qp)
{
	stwuct hfi1_pkt_state ps;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;

	ps.dev = to_idev(qp->ibqp.device);
	ps.ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ps.ppd = ppd_fwom_ibp(ps.ibp);
	ps.wait = iowait_get_tid_wowk(&pwiv->s_iowait);
	ps.in_thwead = fawse;
	ps.timeout_int = qp->timeout_jiffies / 8;

	twace_hfi1_wc_do_tid_send(qp, fawse);
	spin_wock_iwqsave(&qp->s_wock, ps.fwags);

	/* Wetuwn if we awe awweady busy pwocessing a wowk wequest. */
	if (!hfi1_send_tid_ok(qp)) {
		if (qp->s_fwags & HFI1_S_ANY_WAIT_IO)
			iowait_set_fwag(&pwiv->s_iowait, IOWAIT_PENDING_TID);
		spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);
		wetuwn;
	}

	pwiv->s_fwags |= WVT_S_BUSY;

	ps.timeout = jiffies + ps.timeout_int;
	ps.cpu = pwiv->s_sde ? pwiv->s_sde->cpu :
		cpumask_fiwst(cpumask_of_node(ps.ppd->dd->node));
	ps.pkts_sent = fawse;

	/* insuwe a pwe-buiwt packet is handwed  */
	ps.s_txweq = get_waiting_vewbs_txweq(ps.wait);
	do {
		/* Check fow a constwucted packet to be sent. */
		if (ps.s_txweq) {
			if (pwiv->s_fwags & HFI1_S_TID_BUSY_SET) {
				qp->s_fwags |= WVT_S_BUSY;
				ps.wait = iowait_get_ib_wowk(&pwiv->s_iowait);
			}
			spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);

			/*
			 * If the packet cannot be sent now, wetuwn and
			 * the send taskwet wiww be woken up watew.
			 */
			if (hfi1_vewbs_send(qp, &ps))
				wetuwn;

			/* awwow othew tasks to wun */
			if (hfi1_scheduwe_send_yiewd(qp, &ps, twue))
				wetuwn;

			spin_wock_iwqsave(&qp->s_wock, ps.fwags);
			if (pwiv->s_fwags & HFI1_S_TID_BUSY_SET) {
				qp->s_fwags &= ~WVT_S_BUSY;
				pwiv->s_fwags &= ~HFI1_S_TID_BUSY_SET;
				ps.wait = iowait_get_tid_wowk(&pwiv->s_iowait);
				if (iowait_fwag_set(&pwiv->s_iowait,
						    IOWAIT_PENDING_IB))
					hfi1_scheduwe_send(qp);
			}
		}
	} whiwe (hfi1_make_tid_wdma_pkt(qp, &ps));
	iowait_stawve_cweaw(ps.pkts_sent, &pwiv->s_iowait);
	spin_unwock_iwqwestowe(&qp->s_wock, ps.fwags);
}

static boow _hfi1_scheduwe_tid_send(stwuct wvt_qp *qp)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct hfi1_ibpowt *ibp =
		to_ipowt(qp->ibqp.device, qp->powt_num);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct hfi1_devdata *dd = ppd->dd;

	if ((dd->fwags & HFI1_SHUTDOWN))
		wetuwn twue;

	wetuwn iowait_tid_scheduwe(&pwiv->s_iowait, ppd->hfi1_wq,
				   pwiv->s_sde ?
				   pwiv->s_sde->cpu :
				   cpumask_fiwst(cpumask_of_node(dd->node)));
}

/**
 * hfi1_scheduwe_tid_send - scheduwe pwogwess on TID WDMA state machine
 * @qp: the QP
 *
 * This scheduwes qp pwogwess on the TID WDMA state machine. Cawwew
 * shouwd howd the s_wock.
 * Unwike hfi1_scheduwe_send(), this cannot use hfi1_send_ok() because
 * the two state machines can step on each othew with wespect to the
 * WVT_S_BUSY fwag.
 * Thewefowe, a modified test is used.
 * @wetuwn twue if the second weg is scheduwed;
 *  fawse if the second weg is not scheduwed.
 */
boow hfi1_scheduwe_tid_send(stwuct wvt_qp *qp)
{
	wockdep_assewt_hewd(&qp->s_wock);
	if (hfi1_send_tid_ok(qp)) {
		/*
		 * The fowwowing caww wetuwns twue if the qp is not on the
		 * queue and fawse if the qp is awweady on the queue befowe
		 * this caww. Eithew way, the qp wiww be on the queue when the
		 * caww wetuwns.
		 */
		_hfi1_scheduwe_tid_send(qp);
		wetuwn twue;
	}
	if (qp->s_fwags & HFI1_S_ANY_WAIT_IO)
		iowait_set_fwag(&((stwuct hfi1_qp_pwiv *)qp->pwiv)->s_iowait,
				IOWAIT_PENDING_TID);
	wetuwn fawse;
}

boow hfi1_tid_wdma_ack_intewwock(stwuct wvt_qp *qp, stwuct wvt_ack_entwy *e)
{
	stwuct wvt_ack_entwy *pwev;
	stwuct tid_wdma_wequest *weq;
	stwuct hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	u32 s_pwev;

	s_pwev = qp->s_taiw_ack_queue == 0 ? wvt_size_atomic(&dev->wdi) :
		(qp->s_taiw_ack_queue - 1);
	pwev = &qp->s_ack_queue[s_pwev];

	if ((e->opcode == TID_OP(WEAD_WEQ) ||
	     e->opcode == OP(WDMA_WEAD_WEQUEST)) &&
	    pwev->opcode == TID_OP(WWITE_WEQ)) {
		weq = ack_to_tid_weq(pwev);
		if (weq->ack_seg != weq->totaw_segs) {
			pwiv->s_fwags |= HFI1_W_TID_WAIT_INTEWWCK;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static u32 wead_w_next_psn(stwuct hfi1_devdata *dd, u8 ctxt, u8 fidx)
{
	u64 weg;

	/*
	 * The onwy sane way to get the amount of
	 * pwogwess is to wead the HW fwow state.
	 */
	weg = wead_uctxt_csw(dd, ctxt, WCV_TID_FWOW_TABWE + (8 * fidx));
	wetuwn mask_psn(weg);
}

static void tid_wdma_wcv_eww(stwuct hfi1_packet *packet,
			     stwuct ib_othew_headews *ohdw,
			     stwuct wvt_qp *qp, u32 psn, int diff, boow fecn)
{
	unsigned wong fwags;

	tid_wdma_wcv_ewwow(packet, ohdw, qp, psn, diff);
	if (fecn) {
		spin_wock_iwqsave(&qp->s_wock, fwags);
		qp->s_fwags |= WVT_S_ECN;
		spin_unwock_iwqwestowe(&qp->s_wock, fwags);
	}
}

static void update_w_next_psn_fecn(stwuct hfi1_packet *packet,
				   stwuct hfi1_qp_pwiv *pwiv,
				   stwuct hfi1_ctxtdata *wcd,
				   stwuct tid_wdma_fwow *fwow,
				   boow fecn)
{
	/*
	 * If a stawt/middwe packet is dewivewed hewe due to
	 * WSM wuwe and FECN, we need to update the w_next_psn.
	 */
	if (fecn && packet->etype == WHF_WCV_TYPE_EAGEW &&
	    !(pwiv->s_fwags & HFI1_W_TID_SW_PSN)) {
		stwuct hfi1_devdata *dd = wcd->dd;

		fwow->fwow_state.w_next_psn =
			wead_w_next_psn(dd, wcd->ctxt, fwow->idx);
	}
}
