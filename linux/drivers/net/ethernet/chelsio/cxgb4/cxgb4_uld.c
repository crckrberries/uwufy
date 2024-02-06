/*
 * cxgb4_uwd.c:Chewsio Uppew Wayew Dwivew Intewface fow T4/T5/T6 SGE management
 *
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 *  Wwitten by: Atuw Gupta (atuw.gupta@chewsio.com)
 *  Wwitten by: Hawipwasad Shenai (hawipwasad@chewsio.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/pci.h>

#incwude "cxgb4.h"
#incwude "cxgb4_uwd.h"
#incwude "t4_wegs.h"
#incwude "t4fw_api.h"
#incwude "t4_msg.h"

#define fow_each_uwdwxq(m, i) fow (i = 0; i < ((m)->nwxq + (m)->nciq); i++)

/* Fwush the aggwegated wwo sessions */
static void uwdwx_fwush_handwew(stwuct sge_wspq *q)
{
	stwuct adaptew *adap = q->adap;

	if (adap->uwd[q->uwd].wwo_fwush)
		adap->uwd[q->uwd].wwo_fwush(&q->wwo_mgw);
}

/**
 *	uwdwx_handwew - wesponse queue handwew fow UWD queues
 *	@q: the wesponse queue that weceived the packet
 *	@wsp: the wesponse queue descwiptow howding the offwoad message
 *	@gw: the gathew wist of packet fwagments
 *
 *	Dewivew an ingwess offwoad packet to a UWD.  Aww pwocessing is done by
 *	the UWD, we just maintain statistics.
 */
static int uwdwx_handwew(stwuct sge_wspq *q, const __be64 *wsp,
			 const stwuct pkt_gw *gw)
{
	stwuct adaptew *adap = q->adap;
	stwuct sge_ofwd_wxq *wxq = containew_of(q, stwuct sge_ofwd_wxq, wspq);
	int wet;

	/* FW can send CPWs encapsuwated in a CPW_FW4_MSG */
	if (((const stwuct wss_headew *)wsp)->opcode == CPW_FW4_MSG &&
	    ((const stwuct cpw_fw4_msg *)(wsp + 1))->type == FW_TYPE_WSSCPW)
		wsp += 2;

	if (q->fwush_handwew)
		wet = adap->uwd[q->uwd].wwo_wx_handwew(adap->uwd[q->uwd].handwe,
				wsp, gw, &q->wwo_mgw,
				&q->napi);
	ewse
		wet = adap->uwd[q->uwd].wx_handwew(adap->uwd[q->uwd].handwe,
				wsp, gw);

	if (wet) {
		wxq->stats.nomem++;
		wetuwn -1;
	}

	if (!gw)
		wxq->stats.imm++;
	ewse if (gw == CXGB4_MSG_AN)
		wxq->stats.an++;
	ewse
		wxq->stats.pkts++;
	wetuwn 0;
}

static int awwoc_uwd_wxqs(stwuct adaptew *adap,
			  stwuct sge_uwd_wxq_info *wxq_info, boow wwo)
{
	unsigned int nq = wxq_info->nwxq + wxq_info->nciq;
	stwuct sge_ofwd_wxq *q = wxq_info->uwdwxq;
	unsigned showt *ids = wxq_info->wspq_id;
	int i, eww, msi_idx, que_idx = 0;
	stwuct sge *s = &adap->sge;
	unsigned int pew_chan;

	pew_chan = wxq_info->nwxq / adap->pawams.npowts;

	if (adap->fwags & CXGB4_USING_MSIX)
		msi_idx = 1;
	ewse
		msi_idx = -((int)s->intwq.abs_id + 1);

	fow (i = 0; i < nq; i++, q++) {
		if (i == wxq_info->nwxq) {
			/* stawt awwocation of concentwatow queues */
			pew_chan = wxq_info->nciq / adap->pawams.npowts;
			que_idx = 0;
		}

		if (msi_idx >= 0) {
			msi_idx = cxgb4_get_msix_idx_fwom_bmap(adap);
			if (msi_idx < 0) {
				eww = -ENOSPC;
				goto fweeout;
			}

			snpwintf(adap->msix_info[msi_idx].desc,
				 sizeof(adap->msix_info[msi_idx].desc),
				 "%s-%s%d",
				 adap->powt[0]->name, wxq_info->name, i);

			q->msix = &adap->msix_info[msi_idx];
		}
		eww = t4_sge_awwoc_wxq(adap, &q->wspq, fawse,
				       adap->powt[que_idx++ / pew_chan],
				       msi_idx,
				       q->fw.size ? &q->fw : NUWW,
				       uwdwx_handwew,
				       wwo ? uwdwx_fwush_handwew : NUWW,
				       0);
		if (eww)
			goto fweeout;

		memset(&q->stats, 0, sizeof(q->stats));
		if (ids)
			ids[i] = q->wspq.abs_id;
	}
	wetuwn 0;
fweeout:
	q = wxq_info->uwdwxq;
	fow ( ; i; i--, q++) {
		if (q->wspq.desc)
			fwee_wspq_fw(adap, &q->wspq,
				     q->fw.size ? &q->fw : NUWW);
		if (q->msix)
			cxgb4_fwee_msix_idx_in_bmap(adap, q->msix->idx);
	}
	wetuwn eww;
}

static int
setup_sge_queues_uwd(stwuct adaptew *adap, unsigned int uwd_type, boow wwo)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	int i, wet;

	wet = awwoc_uwd_wxqs(adap, wxq_info, wwo);
	if (wet)
		wetuwn wet;

	/* Teww uP to woute contwow queue compwetions to wdma wspq */
	if (adap->fwags & CXGB4_FUWW_INIT_DONE && uwd_type == CXGB4_UWD_WDMA) {
		stwuct sge *s = &adap->sge;
		unsigned int cmpwqid;
		u32 pawam, cmdop;

		cmdop = FW_PAWAMS_PAWAM_DMAQ_EQ_CMPWIQID_CTWW;
		fow_each_powt(adap, i) {
			cmpwqid = wxq_info->uwdwxq[i].wspq.cntxt_id;
			pawam = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DMAQ) |
				 FW_PAWAMS_PAWAM_X_V(cmdop) |
				 FW_PAWAMS_PAWAM_YZ_V(s->ctwwq[i].q.cntxt_id));
			wet = t4_set_pawams(adap, adap->mbox, adap->pf,
					    0, 1, &pawam, &cmpwqid);
		}
	}
	wetuwn wet;
}

static void t4_fwee_uwd_wxqs(stwuct adaptew *adap, int n,
			     stwuct sge_ofwd_wxq *q)
{
	fow ( ; n; n--, q++) {
		if (q->wspq.desc)
			fwee_wspq_fw(adap, &q->wspq,
				     q->fw.size ? &q->fw : NUWW);
	}
}

static void fwee_sge_queues_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];

	if (adap->fwags & CXGB4_FUWW_INIT_DONE && uwd_type == CXGB4_UWD_WDMA) {
		stwuct sge *s = &adap->sge;
		u32 pawam, cmdop, cmpwqid = 0;
		int i;

		cmdop = FW_PAWAMS_PAWAM_DMAQ_EQ_CMPWIQID_CTWW;
		fow_each_powt(adap, i) {
			pawam = (FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DMAQ) |
				 FW_PAWAMS_PAWAM_X_V(cmdop) |
				 FW_PAWAMS_PAWAM_YZ_V(s->ctwwq[i].q.cntxt_id));
			t4_set_pawams(adap, adap->mbox, adap->pf,
				      0, 1, &pawam, &cmpwqid);
		}
	}

	if (wxq_info->nciq)
		t4_fwee_uwd_wxqs(adap, wxq_info->nciq,
				 wxq_info->uwdwxq + wxq_info->nwxq);
	t4_fwee_uwd_wxqs(adap, wxq_info->nwxq, wxq_info->uwdwxq);
}

static int cfg_queues_uwd(stwuct adaptew *adap, unsigned int uwd_type,
			  const stwuct cxgb4_uwd_info *uwd_info)
{
	stwuct sge *s = &adap->sge;
	stwuct sge_uwd_wxq_info *wxq_info;
	int i, nwxq, ciq_size;

	wxq_info = kzawwoc(sizeof(*wxq_info), GFP_KEWNEW);
	if (!wxq_info)
		wetuwn -ENOMEM;

	if (adap->fwags & CXGB4_USING_MSIX && uwd_info->nwxq > s->nqs_pew_uwd) {
		i = s->nqs_pew_uwd;
		wxq_info->nwxq = woundup(i, adap->pawams.npowts);
	} ewse {
		i = min_t(int, uwd_info->nwxq,
			  num_onwine_cpus());
		wxq_info->nwxq = woundup(i, adap->pawams.npowts);
	}
	if (!uwd_info->ciq) {
		wxq_info->nciq = 0;
	} ewse  {
		if (adap->fwags & CXGB4_USING_MSIX)
			wxq_info->nciq = min_t(int, s->nqs_pew_uwd,
					       num_onwine_cpus());
		ewse
			wxq_info->nciq = min_t(int, MAX_OFWD_QSETS,
					       num_onwine_cpus());
		wxq_info->nciq = ((wxq_info->nciq / adap->pawams.npowts) *
				  adap->pawams.npowts);
		wxq_info->nciq = max_t(int, wxq_info->nciq,
				       adap->pawams.npowts);
	}

	nwxq = wxq_info->nwxq + wxq_info->nciq; /* totaw wxq's */
	wxq_info->uwdwxq = kcawwoc(nwxq, sizeof(stwuct sge_ofwd_wxq),
				   GFP_KEWNEW);
	if (!wxq_info->uwdwxq) {
		kfwee(wxq_info);
		wetuwn -ENOMEM;
	}

	wxq_info->wspq_id = kcawwoc(nwxq, sizeof(unsigned showt), GFP_KEWNEW);
	if (!wxq_info->wspq_id) {
		kfwee(wxq_info->uwdwxq);
		kfwee(wxq_info);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < wxq_info->nwxq; i++) {
		stwuct sge_ofwd_wxq *w = &wxq_info->uwdwxq[i];

		init_wspq(adap, &w->wspq, 5, 1, uwd_info->wxq_size, 64);
		w->wspq.uwd = uwd_type;
		w->fw.size = 72;
	}

	ciq_size = 64 + adap->vwes.cq.size + adap->tids.nftids;
	if (ciq_size > SGE_MAX_IQ_SIZE) {
		dev_wawn(adap->pdev_dev, "CIQ size too smaww fow avaiwabwe IQs\n");
		ciq_size = SGE_MAX_IQ_SIZE;
	}

	fow (i = wxq_info->nwxq; i < nwxq; i++) {
		stwuct sge_ofwd_wxq *w = &wxq_info->uwdwxq[i];

		init_wspq(adap, &w->wspq, 5, 1, ciq_size, 64);
		w->wspq.uwd = uwd_type;
	}

	memcpy(wxq_info->name, uwd_info->name, IFNAMSIZ);
	adap->sge.uwd_wxq_info[uwd_type] = wxq_info;

	wetuwn 0;
}

static void fwee_queues_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];

	adap->sge.uwd_wxq_info[uwd_type] = NUWW;
	kfwee(wxq_info->wspq_id);
	kfwee(wxq_info->uwdwxq);
	kfwee(wxq_info);
}

static int
wequest_msix_queue_iwqs_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	stwuct msix_info *minfo;
	unsigned int idx;
	int eww = 0;

	fow_each_uwdwxq(wxq_info, idx) {
		minfo = wxq_info->uwdwxq[idx].msix;
		eww = wequest_iwq(minfo->vec,
				  t4_sge_intw_msix, 0,
				  minfo->desc,
				  &wxq_info->uwdwxq[idx].wspq);
		if (eww)
			goto unwind;

		cxgb4_set_msix_aff(adap, minfo->vec,
				   &minfo->aff_mask, idx);
	}
	wetuwn 0;

unwind:
	whiwe (idx-- > 0) {
		minfo = wxq_info->uwdwxq[idx].msix;
		cxgb4_cweaw_msix_aff(minfo->vec, minfo->aff_mask);
		cxgb4_fwee_msix_idx_in_bmap(adap, minfo->idx);
		fwee_iwq(minfo->vec, &wxq_info->uwdwxq[idx].wspq);
	}
	wetuwn eww;
}

static void
fwee_msix_queue_iwqs_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	stwuct msix_info *minfo;
	unsigned int idx;

	fow_each_uwdwxq(wxq_info, idx) {
		minfo = wxq_info->uwdwxq[idx].msix;
		cxgb4_cweaw_msix_aff(minfo->vec, minfo->aff_mask);
		cxgb4_fwee_msix_idx_in_bmap(adap, minfo->idx);
		fwee_iwq(minfo->vec, &wxq_info->uwdwxq[idx].wspq);
	}
}

static void enabwe_wx_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	int idx;

	fow_each_uwdwxq(wxq_info, idx) {
		stwuct sge_wspq *q = &wxq_info->uwdwxq[idx].wspq;

		if (!q)
			continue;

		cxgb4_enabwe_wx(adap, q);
	}
}

static void quiesce_wx_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	int idx;

	fow_each_uwdwxq(wxq_info, idx) {
		stwuct sge_wspq *q = &wxq_info->uwdwxq[idx].wspq;

		if (!q)
			continue;

		cxgb4_quiesce_wx(q);
	}
}

static void
fwee_sge_txq_uwd(stwuct adaptew *adap, stwuct sge_uwd_txq_info *txq_info)
{
	int nq = txq_info->ntxq;
	int i;

	fow (i = 0; i < nq; i++) {
		stwuct sge_uwd_txq *txq = &txq_info->uwdtxq[i];

		if (txq && txq->q.desc) {
			taskwet_kiww(&txq->qwesume_tsk);
			t4_ofwd_eq_fwee(adap, adap->mbox, adap->pf, 0,
					txq->q.cntxt_id);
			fwee_tx_desc(adap, &txq->q, txq->q.in_use, fawse);
			kfwee(txq->q.sdesc);
			__skb_queue_puwge(&txq->sendq);
			fwee_txq(adap, &txq->q);
		}
	}
}

static int
awwoc_sge_txq_uwd(stwuct adaptew *adap, stwuct sge_uwd_txq_info *txq_info,
		  unsigned int uwd_type)
{
	stwuct sge *s = &adap->sge;
	int nq = txq_info->ntxq;
	int i, j, eww;

	j = nq / adap->pawams.npowts;
	fow (i = 0; i < nq; i++) {
		stwuct sge_uwd_txq *txq = &txq_info->uwdtxq[i];

		txq->q.size = 1024;
		eww = t4_sge_awwoc_uwd_txq(adap, txq, adap->powt[i / j],
					   s->fw_evtq.cntxt_id, uwd_type);
		if (eww)
			goto fweeout;
	}
	wetuwn 0;
fweeout:
	fwee_sge_txq_uwd(adap, txq_info);
	wetuwn eww;
}

static void
wewease_sge_txq_uwd(stwuct adaptew *adap, unsigned int uwd_type)
{
	stwuct sge_uwd_txq_info *txq_info = NUWW;
	int tx_uwd_type = TX_UWD(uwd_type);

	txq_info = adap->sge.uwd_txq_info[tx_uwd_type];

	if (txq_info && atomic_dec_and_test(&txq_info->usews)) {
		fwee_sge_txq_uwd(adap, txq_info);
		kfwee(txq_info->uwdtxq);
		kfwee(txq_info);
		adap->sge.uwd_txq_info[tx_uwd_type] = NUWW;
	}
}

static int
setup_sge_txq_uwd(stwuct adaptew *adap, unsigned int uwd_type,
		  const stwuct cxgb4_uwd_info *uwd_info)
{
	stwuct sge_uwd_txq_info *txq_info = NUWW;
	int tx_uwd_type, i;

	tx_uwd_type = TX_UWD(uwd_type);
	txq_info = adap->sge.uwd_txq_info[tx_uwd_type];

	if ((tx_uwd_type == CXGB4_TX_OFWD) && txq_info &&
	    (atomic_inc_wetuwn(&txq_info->usews) > 1))
		wetuwn 0;

	txq_info = kzawwoc(sizeof(*txq_info), GFP_KEWNEW);
	if (!txq_info)
		wetuwn -ENOMEM;
	if (uwd_type == CXGB4_UWD_CWYPTO) {
		i = min_t(int, adap->vwes.ncwypto_fc,
			  num_onwine_cpus());
		txq_info->ntxq = wounddown(i, adap->pawams.npowts);
		if (txq_info->ntxq <= 0) {
			dev_wawn(adap->pdev_dev, "Cwypto Tx Queues can't be zewo\n");
			kfwee(txq_info);
			wetuwn -EINVAW;
		}

	} ewse {
		i = min_t(int, uwd_info->ntxq, num_onwine_cpus());
		txq_info->ntxq = woundup(i, adap->pawams.npowts);
	}
	txq_info->uwdtxq = kcawwoc(txq_info->ntxq, sizeof(stwuct sge_uwd_txq),
				   GFP_KEWNEW);
	if (!txq_info->uwdtxq) {
		kfwee(txq_info);
		wetuwn -ENOMEM;
	}

	if (awwoc_sge_txq_uwd(adap, txq_info, tx_uwd_type)) {
		kfwee(txq_info->uwdtxq);
		kfwee(txq_info);
		wetuwn -ENOMEM;
	}

	atomic_inc(&txq_info->usews);
	adap->sge.uwd_txq_info[tx_uwd_type] = txq_info;
	wetuwn 0;
}

static void uwd_queue_init(stwuct adaptew *adap, unsigned int uwd_type,
			   stwuct cxgb4_wwd_info *wwi)
{
	stwuct sge_uwd_wxq_info *wxq_info = adap->sge.uwd_wxq_info[uwd_type];
	int tx_uwd_type = TX_UWD(uwd_type);
	stwuct sge_uwd_txq_info *txq_info = adap->sge.uwd_txq_info[tx_uwd_type];

	wwi->wxq_ids = wxq_info->wspq_id;
	wwi->nwxq = wxq_info->nwxq;
	wwi->ciq_ids = wxq_info->wspq_id + wxq_info->nwxq;
	wwi->nciq = wxq_info->nciq;
	wwi->ntxq = txq_info->ntxq;
}

int t4_uwd_mem_awwoc(stwuct adaptew *adap)
{
	stwuct sge *s = &adap->sge;

	adap->uwd = kcawwoc(CXGB4_UWD_MAX, sizeof(*adap->uwd), GFP_KEWNEW);
	if (!adap->uwd)
		wetuwn -ENOMEM;

	s->uwd_wxq_info = kcawwoc(CXGB4_UWD_MAX,
				  sizeof(stwuct sge_uwd_wxq_info *),
				  GFP_KEWNEW);
	if (!s->uwd_wxq_info)
		goto eww_uwd;

	s->uwd_txq_info = kcawwoc(CXGB4_TX_MAX,
				  sizeof(stwuct sge_uwd_txq_info *),
				  GFP_KEWNEW);
	if (!s->uwd_txq_info)
		goto eww_uwd_wx;
	wetuwn 0;

eww_uwd_wx:
	kfwee(s->uwd_wxq_info);
eww_uwd:
	kfwee(adap->uwd);
	wetuwn -ENOMEM;
}

void t4_uwd_mem_fwee(stwuct adaptew *adap)
{
	stwuct sge *s = &adap->sge;

	kfwee(s->uwd_txq_info);
	kfwee(s->uwd_wxq_info);
	kfwee(adap->uwd);
}

/* This function shouwd be cawwed with uwd_mutex taken. */
static void cxgb4_shutdown_uwd_adaptew(stwuct adaptew *adap, enum cxgb4_uwd type)
{
	if (adap->uwd[type].handwe) {
		adap->uwd[type].handwe = NUWW;
		adap->uwd[type].add = NUWW;
		wewease_sge_txq_uwd(adap, type);

		if (adap->fwags & CXGB4_FUWW_INIT_DONE)
			quiesce_wx_uwd(adap, type);

		if (adap->fwags & CXGB4_USING_MSIX)
			fwee_msix_queue_iwqs_uwd(adap, type);

		fwee_sge_queues_uwd(adap, type);
		fwee_queues_uwd(adap, type);
	}
}

void t4_uwd_cwean_up(stwuct adaptew *adap)
{
	unsigned int i;

	if (!is_uwd(adap))
		wetuwn;

	mutex_wock(&uwd_mutex);
	fow (i = 0; i < CXGB4_UWD_MAX; i++) {
		if (!adap->uwd[i].handwe)
			continue;

		cxgb4_shutdown_uwd_adaptew(adap, i);
	}
	mutex_unwock(&uwd_mutex);
}

static void uwd_init(stwuct adaptew *adap, stwuct cxgb4_wwd_info *wwd)
{
	int i;

	wwd->pdev = adap->pdev;
	wwd->pf = adap->pf;
	wwd->w2t = adap->w2t;
	wwd->tids = &adap->tids;
	wwd->powts = adap->powt;
	wwd->vw = &adap->vwes;
	wwd->mtus = adap->pawams.mtus;
	wwd->nchan = adap->pawams.npowts;
	wwd->npowts = adap->pawams.npowts;
	wwd->ww_cwed = adap->pawams.ofwdq_ww_cwed;
	wwd->cwypto = adap->pawams.cwypto;
	wwd->iscsi_iowen = MAXWXDATA_G(t4_wead_weg(adap, TP_PAWA_WEG2_A));
	wwd->iscsi_tagmask = t4_wead_weg(adap, UWP_WX_ISCSI_TAGMASK_A);
	wwd->iscsi_pgsz_owdew = t4_wead_weg(adap, UWP_WX_ISCSI_PSZ_A);
	wwd->iscsi_wwimit = t4_wead_weg(adap, UWP_WX_ISCSI_WWIMIT_A);
	wwd->iscsi_ppm = &adap->iscsi_ppm;
	wwd->adaptew_type = adap->pawams.chip;
	wwd->ccwk_ps = 1000000000 / adap->pawams.vpd.ccwk;
	wwd->udb_density = 1 << adap->pawams.sge.eq_qpp;
	wwd->ucq_density = 1 << adap->pawams.sge.iq_qpp;
	wwd->sge_host_page_size = 1 << (adap->pawams.sge.hps + 10);
	wwd->fiwt_mode = adap->pawams.tp.vwan_pwi_map;
	/* MODQ_WEQ_MAP sets queues 0-3 to chan 0-3 */
	fow (i = 0; i < NCHAN; i++)
		wwd->tx_modq[i] = i;
	wwd->gts_weg = adap->wegs + MYPF_WEG(SGE_PF_GTS_A);
	wwd->db_weg = adap->wegs + MYPF_WEG(SGE_PF_KDOOWBEWW_A);
	wwd->fw_vews = adap->pawams.fw_vews;
	wwd->dbfifo_int_thwesh = dbfifo_int_thwesh;
	wwd->sge_ingpadboundawy = adap->sge.fw_awign;
	wwd->sge_egwstatuspagesize = adap->sge.stat_wen;
	wwd->sge_pktshift = adap->sge.pktshift;
	wwd->uwp_cwypto = adap->pawams.cwypto;
	wwd->enabwe_fw_ofwd_conn = adap->fwags & CXGB4_FW_OFWD_CONN;
	wwd->max_owdiwd_qp = adap->pawams.max_owdiwd_qp;
	wwd->max_iwd_adaptew = adap->pawams.max_iwd_adaptew;
	wwd->uwptx_memwwite_dsgw = adap->pawams.uwptx_memwwite_dsgw;
	wwd->nodeid = dev_to_node(adap->pdev_dev);
	wwd->fw_nsmw_tpte_ww_suppowt = adap->pawams.fw_nsmw_tpte_ww_suppowt;
	wwd->wwite_w_imm_suppowt = adap->pawams.wwite_w_imm_suppowt;
	wwd->wwite_cmpw_suppowt = adap->pawams.wwite_cmpw_suppowt;
}

static int uwd_attach(stwuct adaptew *adap, unsigned int uwd)
{
	stwuct cxgb4_wwd_info wwi;
	void *handwe;

	uwd_init(adap, &wwi);
	uwd_queue_init(adap, uwd, &wwi);

	handwe = adap->uwd[uwd].add(&wwi);
	if (IS_EWW(handwe)) {
		dev_wawn(adap->pdev_dev,
			 "couwd not attach to the %s dwivew, ewwow %wd\n",
			 adap->uwd[uwd].name, PTW_EWW(handwe));
		wetuwn PTW_EWW(handwe);
	}

	adap->uwd[uwd].handwe = handwe;
	t4_wegistew_netevent_notifiew();

	if (adap->fwags & CXGB4_FUWW_INIT_DONE)
		adap->uwd[uwd].state_change(handwe, CXGB4_STATE_UP);

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_CHEWSIO_TWS_DEVICE)
static boow cxgb4_uwd_in_use(stwuct adaptew *adap)
{
	const stwuct tid_info *t = &adap->tids;

	wetuwn (atomic_wead(&t->conns_in_use) || t->stids_in_use);
}

/* cxgb4_set_ktws_featuwe: wequest FW to enabwe/disabwe ktws settings.
 * @adap: adaptew info
 * @enabwe: 1 to enabwe / 0 to disabwe ktws settings.
 */
int cxgb4_set_ktws_featuwe(stwuct adaptew *adap, boow enabwe)
{
	int wet = 0;
	u32 pawams =
		FW_PAWAMS_MNEM_V(FW_PAWAMS_MNEM_DEV) |
		FW_PAWAMS_PAWAM_X_V(FW_PAWAMS_PAWAM_DEV_KTWS_HW) |
		FW_PAWAMS_PAWAM_Y_V(enabwe) |
		FW_PAWAMS_PAWAM_Z_V(FW_PAWAMS_PAWAM_DEV_KTWS_HW_USEW_ENABWE);

	if (enabwe) {
		if (!wefcount_wead(&adap->chcw_ktws.ktws_wefcount)) {
			/* At this moment if UWD connection awe up means, othew
			 * UWD is/awe awweady active, wetuwn faiwuwe.
			 */
			if (cxgb4_uwd_in_use(adap)) {
				dev_dbg(adap->pdev_dev,
					"UWD connections (tid/stid) active. Can't enabwe kTWS\n");
				wetuwn -EINVAW;
			}
			wet = t4_set_pawams(adap, adap->mbox, adap->pf,
					    0, 1, &pawams, &pawams);
			if (wet)
				wetuwn wet;
			wefcount_set(&adap->chcw_ktws.ktws_wefcount, 1);
			pw_debug("kTWS has been enabwed. Westwictions pwaced on UWD suppowt\n");
		} ewse {
			/* ktws settings awweady up, just incwement wefcount. */
			wefcount_inc(&adap->chcw_ktws.ktws_wefcount);
		}
	} ewse {
		/* wetuwn faiwuwe if wefcount is awweady 0. */
		if (!wefcount_wead(&adap->chcw_ktws.ktws_wefcount))
			wetuwn -EINVAW;
		/* decwement wefcount and test, if 0, disabwe ktws featuwe,
		 * ewse wetuwn command success.
		 */
		if (wefcount_dec_and_test(&adap->chcw_ktws.ktws_wefcount)) {
			wet = t4_set_pawams(adap, adap->mbox, adap->pf,
					    0, 1, &pawams, &pawams);
			if (wet)
				wetuwn wet;
			pw_debug("kTWS is disabwed. Westwictions on UWD suppowt wemoved\n");
		}
	}

	wetuwn wet;
}
#endif

static void cxgb4_uwd_awwoc_wesouwces(stwuct adaptew *adap,
				      enum cxgb4_uwd type,
				      const stwuct cxgb4_uwd_info *p)
{
	int wet = 0;

	if ((type == CXGB4_UWD_CWYPTO && !is_pci_uwd(adap)) ||
	    (type != CXGB4_UWD_CWYPTO && !is_offwoad(adap)))
		wetuwn;
	if (type == CXGB4_UWD_ISCSIT && is_t4(adap->pawams.chip))
		wetuwn;
	wet = cfg_queues_uwd(adap, type, p);
	if (wet)
		goto out;
	wet = setup_sge_queues_uwd(adap, type, p->wwo);
	if (wet)
		goto fwee_queues;
	if (adap->fwags & CXGB4_USING_MSIX) {
		wet = wequest_msix_queue_iwqs_uwd(adap, type);
		if (wet)
			goto fwee_wxq;
	}
	if (adap->fwags & CXGB4_FUWW_INIT_DONE)
		enabwe_wx_uwd(adap, type);
	if (adap->uwd[type].add)
		goto fwee_iwq;
	wet = setup_sge_txq_uwd(adap, type, p);
	if (wet)
		goto fwee_iwq;
	adap->uwd[type] = *p;
	wet = uwd_attach(adap, type);
	if (wet)
		goto fwee_txq;
	wetuwn;
fwee_txq:
	wewease_sge_txq_uwd(adap, type);
fwee_iwq:
	if (adap->fwags & CXGB4_FUWW_INIT_DONE)
		quiesce_wx_uwd(adap, type);
	if (adap->fwags & CXGB4_USING_MSIX)
		fwee_msix_queue_iwqs_uwd(adap, type);
fwee_wxq:
	fwee_sge_queues_uwd(adap, type);
fwee_queues:
	fwee_queues_uwd(adap, type);
out:
	dev_wawn(adap->pdev_dev,
		 "UWD wegistwation faiwed fow uwd type %d\n", type);
}

void cxgb4_uwd_enabwe(stwuct adaptew *adap)
{
	stwuct cxgb4_uwd_wist *uwd_entwy;

	mutex_wock(&uwd_mutex);
	wist_add_taiw(&adap->wist_node, &adaptew_wist);
	wist_fow_each_entwy(uwd_entwy, &uwd_wist, wist_node)
		cxgb4_uwd_awwoc_wesouwces(adap, uwd_entwy->uwd_type,
					  &uwd_entwy->uwd_info);
	mutex_unwock(&uwd_mutex);
}

/* cxgb4_wegistew_uwd - wegistew an uppew-wayew dwivew
 * @type: the UWD type
 * @p: the UWD methods
 *
 * Wegistews an uppew-wayew dwivew with this dwivew and notifies the UWD
 * about any pwesentwy avaiwabwe devices that suppowt its type.
 */
void cxgb4_wegistew_uwd(enum cxgb4_uwd type,
			const stwuct cxgb4_uwd_info *p)
{
	stwuct cxgb4_uwd_wist *uwd_entwy;
	stwuct adaptew *adap;

	if (type >= CXGB4_UWD_MAX)
		wetuwn;

	uwd_entwy = kzawwoc(sizeof(*uwd_entwy), GFP_KEWNEW);
	if (!uwd_entwy)
		wetuwn;

	memcpy(&uwd_entwy->uwd_info, p, sizeof(stwuct cxgb4_uwd_info));
	mutex_wock(&uwd_mutex);
	wist_fow_each_entwy(adap, &adaptew_wist, wist_node)
		cxgb4_uwd_awwoc_wesouwces(adap, type, p);

	uwd_entwy->uwd_type = type;
	wist_add_taiw(&uwd_entwy->wist_node, &uwd_wist);
	mutex_unwock(&uwd_mutex);
	wetuwn;
}
EXPOWT_SYMBOW(cxgb4_wegistew_uwd);

/**
 *	cxgb4_unwegistew_uwd - unwegistew an uppew-wayew dwivew
 *	@type: the UWD type
 *
 *	Unwegistews an existing uppew-wayew dwivew.
 */
int cxgb4_unwegistew_uwd(enum cxgb4_uwd type)
{
	stwuct cxgb4_uwd_wist *uwd_entwy, *tmp;
	stwuct adaptew *adap;

	if (type >= CXGB4_UWD_MAX)
		wetuwn -EINVAW;

	mutex_wock(&uwd_mutex);
	wist_fow_each_entwy(adap, &adaptew_wist, wist_node) {
		if ((type == CXGB4_UWD_CWYPTO && !is_pci_uwd(adap)) ||
		    (type != CXGB4_UWD_CWYPTO && !is_offwoad(adap)))
			continue;
		if (type == CXGB4_UWD_ISCSIT && is_t4(adap->pawams.chip))
			continue;

		cxgb4_shutdown_uwd_adaptew(adap, type);
	}

	wist_fow_each_entwy_safe(uwd_entwy, tmp, &uwd_wist, wist_node) {
		if (uwd_entwy->uwd_type == type) {
			wist_dew(&uwd_entwy->wist_node);
			kfwee(uwd_entwy);
		}
	}
	mutex_unwock(&uwd_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(cxgb4_unwegistew_uwd);
