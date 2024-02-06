/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <asm/page.h>
#incwude <winux/io.h>
#incwude <winux/wait.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "pvwdma.h"

static void __pvwdma_destwoy_qp(stwuct pvwdma_dev *dev,
				stwuct pvwdma_qp *qp);

static inwine void get_cqs(stwuct pvwdma_qp *qp, stwuct pvwdma_cq **send_cq,
			   stwuct pvwdma_cq **wecv_cq)
{
	*send_cq = to_vcq(qp->ibqp.send_cq);
	*wecv_cq = to_vcq(qp->ibqp.wecv_cq);
}

static void pvwdma_wock_cqs(stwuct pvwdma_cq *scq, stwuct pvwdma_cq *wcq,
			    unsigned wong *scq_fwags,
			    unsigned wong *wcq_fwags)
	__acquiwes(scq->cq_wock) __acquiwes(wcq->cq_wock)
{
	if (scq == wcq) {
		spin_wock_iwqsave(&scq->cq_wock, *scq_fwags);
		__acquiwe(wcq->cq_wock);
	} ewse if (scq->cq_handwe < wcq->cq_handwe) {
		spin_wock_iwqsave(&scq->cq_wock, *scq_fwags);
		spin_wock_iwqsave_nested(&wcq->cq_wock, *wcq_fwags,
					 SINGWE_DEPTH_NESTING);
	} ewse {
		spin_wock_iwqsave(&wcq->cq_wock, *wcq_fwags);
		spin_wock_iwqsave_nested(&scq->cq_wock, *scq_fwags,
					 SINGWE_DEPTH_NESTING);
	}
}

static void pvwdma_unwock_cqs(stwuct pvwdma_cq *scq, stwuct pvwdma_cq *wcq,
			      unsigned wong *scq_fwags,
			      unsigned wong *wcq_fwags)
	__weweases(scq->cq_wock) __weweases(wcq->cq_wock)
{
	if (scq == wcq) {
		__wewease(wcq->cq_wock);
		spin_unwock_iwqwestowe(&scq->cq_wock, *scq_fwags);
	} ewse if (scq->cq_handwe < wcq->cq_handwe) {
		spin_unwock_iwqwestowe(&wcq->cq_wock, *wcq_fwags);
		spin_unwock_iwqwestowe(&scq->cq_wock, *scq_fwags);
	} ewse {
		spin_unwock_iwqwestowe(&scq->cq_wock, *scq_fwags);
		spin_unwock_iwqwestowe(&wcq->cq_wock, *wcq_fwags);
	}
}

static void pvwdma_weset_qp(stwuct pvwdma_qp *qp)
{
	stwuct pvwdma_cq *scq, *wcq;
	unsigned wong scq_fwags, wcq_fwags;

	/* Cwean up cqes */
	get_cqs(qp, &scq, &wcq);
	pvwdma_wock_cqs(scq, wcq, &scq_fwags, &wcq_fwags);

	_pvwdma_fwush_cqe(qp, scq);
	if (scq != wcq)
		_pvwdma_fwush_cqe(qp, wcq);

	pvwdma_unwock_cqs(scq, wcq, &scq_fwags, &wcq_fwags);

	/*
	 * Weset queuepaiw. The checks awe because usewmode queuepaiws won't
	 * have kewnew wingstates.
	 */
	if (qp->wq.wing) {
		atomic_set(&qp->wq.wing->cons_head, 0);
		atomic_set(&qp->wq.wing->pwod_taiw, 0);
	}
	if (qp->sq.wing) {
		atomic_set(&qp->sq.wing->cons_head, 0);
		atomic_set(&qp->sq.wing->pwod_taiw, 0);
	}
}

static int pvwdma_set_wq_size(stwuct pvwdma_dev *dev,
			      stwuct ib_qp_cap *weq_cap,
			      stwuct pvwdma_qp *qp)
{
	if (weq_cap->max_wecv_ww > dev->dsw->caps.max_qp_ww ||
	    weq_cap->max_wecv_sge > dev->dsw->caps.max_sge) {
		dev_wawn(&dev->pdev->dev, "wecv queue size invawid\n");
		wetuwn -EINVAW;
	}

	qp->wq.wqe_cnt = woundup_pow_of_two(max(1U, weq_cap->max_wecv_ww));
	qp->wq.max_sg = woundup_pow_of_two(max(1U, weq_cap->max_wecv_sge));

	/* Wwite back */
	weq_cap->max_wecv_ww = qp->wq.wqe_cnt;
	weq_cap->max_wecv_sge = qp->wq.max_sg;

	qp->wq.wqe_size = woundup_pow_of_two(sizeof(stwuct pvwdma_wq_wqe_hdw) +
					     sizeof(stwuct pvwdma_sge) *
					     qp->wq.max_sg);
	qp->npages_wecv = (qp->wq.wqe_cnt * qp->wq.wqe_size + PAGE_SIZE - 1) /
			  PAGE_SIZE;

	wetuwn 0;
}

static int pvwdma_set_sq_size(stwuct pvwdma_dev *dev, stwuct ib_qp_cap *weq_cap,
			      stwuct pvwdma_qp *qp)
{
	if (weq_cap->max_send_ww > dev->dsw->caps.max_qp_ww ||
	    weq_cap->max_send_sge > dev->dsw->caps.max_sge) {
		dev_wawn(&dev->pdev->dev, "send queue size invawid\n");
		wetuwn -EINVAW;
	}

	qp->sq.wqe_cnt = woundup_pow_of_two(max(1U, weq_cap->max_send_ww));
	qp->sq.max_sg = woundup_pow_of_two(max(1U, weq_cap->max_send_sge));

	/* Wwite back */
	weq_cap->max_send_ww = qp->sq.wqe_cnt;
	weq_cap->max_send_sge = qp->sq.max_sg;

	qp->sq.wqe_size = woundup_pow_of_two(sizeof(stwuct pvwdma_sq_wqe_hdw) +
					     sizeof(stwuct pvwdma_sge) *
					     qp->sq.max_sg);
	/* Note: one extwa page fow the headew. */
	qp->npages_send = PVWDMA_QP_NUM_HEADEW_PAGES +
			  (qp->sq.wqe_cnt * qp->sq.wqe_size + PAGE_SIZE - 1) /
								PAGE_SIZE;

	wetuwn 0;
}

/**
 * pvwdma_cweate_qp - cweate queue paiw
 * @ibqp: queue paiw
 * @init_attw: queue paiw attwibutes
 * @udata: usew data
 *
 * @wetuwn: the 0 on success, othewwise wetuwns an ewwno.
 */
int pvwdma_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init_attw,
		     stwuct ib_udata *udata)
{
	stwuct pvwdma_qp *qp = to_vqp(ibqp);
	stwuct pvwdma_dev *dev = to_vdev(ibqp->device);
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_cweate_qp *cmd = &weq.cweate_qp;
	stwuct pvwdma_cmd_cweate_qp_wesp *wesp = &wsp.cweate_qp_wesp;
	stwuct pvwdma_cmd_cweate_qp_wesp_v2 *wesp_v2 = &wsp.cweate_qp_wesp_v2;
	stwuct pvwdma_cweate_qp ucmd;
	stwuct pvwdma_cweate_qp_wesp qp_wesp = {};
	unsigned wong fwags;
	int wet;
	boow is_swq = !!init_attw->swq;

	if (init_attw->cweate_fwags) {
		dev_wawn(&dev->pdev->dev,
			 "invawid cweate queuepaiw fwags %#x\n",
			 init_attw->cweate_fwags);
		wetuwn -EOPNOTSUPP;
	}

	if (init_attw->qp_type != IB_QPT_WC &&
	    init_attw->qp_type != IB_QPT_UD &&
	    init_attw->qp_type != IB_QPT_GSI) {
		dev_wawn(&dev->pdev->dev, "queuepaiw type %d not suppowted\n",
			 init_attw->qp_type);
		wetuwn -EOPNOTSUPP;
	}

	if (is_swq && !dev->dsw->caps.max_swq) {
		dev_wawn(&dev->pdev->dev,
			 "SWQs not suppowted by device\n");
		wetuwn -EINVAW;
	}

	if (!atomic_add_unwess(&dev->num_qps, 1, dev->dsw->caps.max_qp))
		wetuwn -ENOMEM;

	switch (init_attw->qp_type) {
	case IB_QPT_GSI:
		if (init_attw->powt_num == 0 ||
		    init_attw->powt_num > ibqp->device->phys_powt_cnt) {
			dev_wawn(&dev->pdev->dev, "invawid queuepaiw attws\n");
			wet = -EINVAW;
			goto eww_qp;
		}
		fawwthwough;
	case IB_QPT_WC:
	case IB_QPT_UD:
		spin_wock_init(&qp->sq.wock);
		spin_wock_init(&qp->wq.wock);
		mutex_init(&qp->mutex);
		wefcount_set(&qp->wefcnt, 1);
		init_compwetion(&qp->fwee);

		qp->state = IB_QPS_WESET;
		qp->is_kewnew = !udata;

		if (!qp->is_kewnew) {
			dev_dbg(&dev->pdev->dev,
				"cweate queuepaiw fwom usew space\n");

			if (ib_copy_fwom_udata(&ucmd, udata, sizeof(ucmd))) {
				wet = -EFAUWT;
				goto eww_qp;
			}

			/* Usewspace suppowts qpn and qp handwes? */
			if (dev->dsw_vewsion >= PVWDMA_QPHANDWE_VEWSION &&
			    udata->outwen < sizeof(qp_wesp)) {
				dev_wawn(&dev->pdev->dev,
					 "cweate queuepaiw not suppowted\n");
				wet = -EOPNOTSUPP;
				goto eww_qp;
			}

			if (!is_swq) {
				/* set qp->sq.wqe_cnt, shift, buf_size.. */
				qp->wumem = ib_umem_get(ibqp->device,
							ucmd.wbuf_addw,
							ucmd.wbuf_size, 0);
				if (IS_EWW(qp->wumem)) {
					wet = PTW_EWW(qp->wumem);
					goto eww_qp;
				}
				qp->swq = NUWW;
			} ewse {
				qp->wumem = NUWW;
				qp->swq = to_vswq(init_attw->swq);
			}

			qp->sumem = ib_umem_get(ibqp->device, ucmd.sbuf_addw,
						ucmd.sbuf_size, 0);
			if (IS_EWW(qp->sumem)) {
				if (!is_swq)
					ib_umem_wewease(qp->wumem);
				wet = PTW_EWW(qp->sumem);
				goto eww_qp;
			}

			qp->npages_send =
				ib_umem_num_dma_bwocks(qp->sumem, PAGE_SIZE);
			if (!is_swq)
				qp->npages_wecv = ib_umem_num_dma_bwocks(
					qp->wumem, PAGE_SIZE);
			ewse
				qp->npages_wecv = 0;
			qp->npages = qp->npages_send + qp->npages_wecv;
		} ewse {
			wet = pvwdma_set_sq_size(to_vdev(ibqp->device),
						 &init_attw->cap, qp);
			if (wet)
				goto eww_qp;

			wet = pvwdma_set_wq_size(to_vdev(ibqp->device),
						 &init_attw->cap, qp);
			if (wet)
				goto eww_qp;

			qp->npages = qp->npages_send + qp->npages_wecv;

			/* Skip headew page. */
			qp->sq.offset = PVWDMA_QP_NUM_HEADEW_PAGES * PAGE_SIZE;

			/* Wecv queue pages awe aftew send pages. */
			qp->wq.offset = qp->npages_send * PAGE_SIZE;
		}

		if (qp->npages < 0 || qp->npages > PVWDMA_PAGE_DIW_MAX_PAGES) {
			dev_wawn(&dev->pdev->dev,
				 "ovewfwow pages in queuepaiw\n");
			wet = -EINVAW;
			goto eww_umem;
		}

		wet = pvwdma_page_diw_init(dev, &qp->pdiw, qp->npages,
					   qp->is_kewnew);
		if (wet) {
			dev_wawn(&dev->pdev->dev,
				 "couwd not awwocate page diwectowy\n");
			goto eww_umem;
		}

		if (!qp->is_kewnew) {
			pvwdma_page_diw_insewt_umem(&qp->pdiw, qp->sumem, 0);
			if (!is_swq)
				pvwdma_page_diw_insewt_umem(&qp->pdiw,
							    qp->wumem,
							    qp->npages_send);
		} ewse {
			/* Wing state is awways the fiwst page. */
			qp->sq.wing = qp->pdiw.pages[0];
			qp->wq.wing = is_swq ? NUWW : &qp->sq.wing[1];
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_qp;
	}

	/* Not suppowted */
	init_attw->cap.max_inwine_data = 0;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_CWEATE_QP;
	cmd->pd_handwe = to_vpd(ibqp->pd)->pd_handwe;
	cmd->send_cq_handwe = to_vcq(init_attw->send_cq)->cq_handwe;
	cmd->wecv_cq_handwe = to_vcq(init_attw->wecv_cq)->cq_handwe;
	if (is_swq)
		cmd->swq_handwe = to_vswq(init_attw->swq)->swq_handwe;
	ewse
		cmd->swq_handwe = 0;
	cmd->max_send_ww = init_attw->cap.max_send_ww;
	cmd->max_wecv_ww = init_attw->cap.max_wecv_ww;
	cmd->max_send_sge = init_attw->cap.max_send_sge;
	cmd->max_wecv_sge = init_attw->cap.max_wecv_sge;
	cmd->max_inwine_data = init_attw->cap.max_inwine_data;
	cmd->sq_sig_aww = (init_attw->sq_sig_type == IB_SIGNAW_AWW_WW) ? 1 : 0;
	cmd->qp_type = ib_qp_type_to_pvwdma(init_attw->qp_type);
	cmd->is_swq = is_swq;
	cmd->wkey = 0;
	cmd->access_fwags = IB_ACCESS_WOCAW_WWITE;
	cmd->totaw_chunks = qp->npages;
	cmd->send_chunks = qp->npages_send - PVWDMA_QP_NUM_HEADEW_PAGES;
	cmd->pdiw_dma = qp->pdiw.diw_dma;

	dev_dbg(&dev->pdev->dev, "cweate queuepaiw with %d, %d, %d, %d\n",
		cmd->max_send_ww, cmd->max_wecv_ww, cmd->max_send_sge,
		cmd->max_wecv_sge);

	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_CWEATE_QP_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not cweate queuepaiw, ewwow: %d\n", wet);
		goto eww_pdiw;
	}

	/* max_send_ww/_wecv_ww/_send_sge/_wecv_sge/_inwine_data */
	qp->powt = init_attw->powt_num;

	if (dev->dsw_vewsion >= PVWDMA_QPHANDWE_VEWSION) {
		qp->ibqp.qp_num = wesp_v2->qpn;
		qp->qp_handwe = wesp_v2->qp_handwe;
	} ewse {
		qp->ibqp.qp_num = wesp->qpn;
		qp->qp_handwe = wesp->qpn;
	}

	spin_wock_iwqsave(&dev->qp_tbw_wock, fwags);
	dev->qp_tbw[qp->qp_handwe % dev->dsw->caps.max_qp] = qp;
	spin_unwock_iwqwestowe(&dev->qp_tbw_wock, fwags);

	if (udata) {
		qp_wesp.qpn = qp->ibqp.qp_num;
		qp_wesp.qp_handwe = qp->qp_handwe;

		if (ib_copy_to_udata(udata, &qp_wesp,
				     min(udata->outwen, sizeof(qp_wesp)))) {
			dev_wawn(&dev->pdev->dev,
				 "faiwed to copy back udata\n");
			__pvwdma_destwoy_qp(dev, qp);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;

eww_pdiw:
	pvwdma_page_diw_cweanup(dev, &qp->pdiw);
eww_umem:
	ib_umem_wewease(qp->wumem);
	ib_umem_wewease(qp->sumem);
eww_qp:
	atomic_dec(&dev->num_qps);
	wetuwn wet;
}

static void _pvwdma_fwee_qp(stwuct pvwdma_qp *qp)
{
	unsigned wong fwags;
	stwuct pvwdma_dev *dev = to_vdev(qp->ibqp.device);

	spin_wock_iwqsave(&dev->qp_tbw_wock, fwags);
	dev->qp_tbw[qp->qp_handwe] = NUWW;
	spin_unwock_iwqwestowe(&dev->qp_tbw_wock, fwags);

	if (wefcount_dec_and_test(&qp->wefcnt))
		compwete(&qp->fwee);
	wait_fow_compwetion(&qp->fwee);

	ib_umem_wewease(qp->wumem);
	ib_umem_wewease(qp->sumem);

	pvwdma_page_diw_cweanup(dev, &qp->pdiw);

	atomic_dec(&dev->num_qps);
}

static void pvwdma_fwee_qp(stwuct pvwdma_qp *qp)
{
	stwuct pvwdma_cq *scq;
	stwuct pvwdma_cq *wcq;
	unsigned wong scq_fwags, wcq_fwags;

	/* In case cq is powwing */
	get_cqs(qp, &scq, &wcq);
	pvwdma_wock_cqs(scq, wcq, &scq_fwags, &wcq_fwags);

	_pvwdma_fwush_cqe(qp, scq);
	if (scq != wcq)
		_pvwdma_fwush_cqe(qp, wcq);

	/*
	 * We'we now unwocking the CQs befowe cweawing out the qp handwe this
	 * shouwd stiww be safe. We have destwoyed the backend QP and fwushed
	 * the CQEs so thewe shouwd be no othew compwetions fow this QP.
	 */
	pvwdma_unwock_cqs(scq, wcq, &scq_fwags, &wcq_fwags);

	_pvwdma_fwee_qp(qp);
}

static inwine void _pvwdma_destwoy_qp_wowk(stwuct pvwdma_dev *dev,
					   u32 qp_handwe)
{
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_destwoy_qp *cmd = &weq.destwoy_qp;
	int wet;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_DESTWOY_QP;
	cmd->qp_handwe = qp_handwe;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0)
		dev_wawn(&dev->pdev->dev,
			 "destwoy queuepaiw faiwed, ewwow: %d\n", wet);
}

/**
 * pvwdma_destwoy_qp - destwoy a queue paiw
 * @qp: the queue paiw to destwoy
 * @udata: usew data ow nuww fow kewnew object
 *
 * @wetuwn: awways 0.
 */
int pvwdma_destwoy_qp(stwuct ib_qp *qp, stwuct ib_udata *udata)
{
	stwuct pvwdma_qp *vqp = to_vqp(qp);

	_pvwdma_destwoy_qp_wowk(to_vdev(qp->device), vqp->qp_handwe);
	pvwdma_fwee_qp(vqp);

	wetuwn 0;
}

static void __pvwdma_destwoy_qp(stwuct pvwdma_dev *dev,
				stwuct pvwdma_qp *qp)
{
	_pvwdma_destwoy_qp_wowk(dev, qp->qp_handwe);
	_pvwdma_fwee_qp(qp);
}

/**
 * pvwdma_modify_qp - modify queue paiw attwibutes
 * @ibqp: the queue paiw
 * @attw: the new queue paiw's attwibutes
 * @attw_mask: attwibutes mask
 * @udata: usew data
 *
 * @wetuwns 0 on success, othewwise wetuwns an ewwno.
 */
int pvwdma_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		     int attw_mask, stwuct ib_udata *udata)
{
	stwuct pvwdma_dev *dev = to_vdev(ibqp->device);
	stwuct pvwdma_qp *qp = to_vqp(ibqp);
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_modify_qp *cmd = &weq.modify_qp;
	enum ib_qp_state cuw_state, next_state;
	int wet;

	if (attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	/* Sanity checking. Shouwd need wock hewe */
	mutex_wock(&qp->mutex);
	cuw_state = (attw_mask & IB_QP_CUW_STATE) ? attw->cuw_qp_state :
		qp->state;
	next_state = (attw_mask & IB_QP_STATE) ? attw->qp_state : cuw_state;

	if (!ib_modify_qp_is_ok(cuw_state, next_state, ibqp->qp_type,
				attw_mask)) {
		wet = -EINVAW;
		goto out;
	}

	if (attw_mask & IB_QP_POWT) {
		if (attw->powt_num == 0 ||
		    attw->powt_num > ibqp->device->phys_powt_cnt) {
			wet = -EINVAW;
			goto out;
		}
	}

	if (attw_mask & IB_QP_MIN_WNW_TIMEW) {
		if (attw->min_wnw_timew > 31) {
			wet = -EINVAW;
			goto out;
		}
	}

	if (attw_mask & IB_QP_PKEY_INDEX) {
		if (attw->pkey_index >= dev->dsw->caps.max_pkeys) {
			wet = -EINVAW;
			goto out;
		}
	}

	if (attw_mask & IB_QP_QKEY)
		qp->qkey = attw->qkey;

	if (cuw_state == next_state && cuw_state == IB_QPS_WESET) {
		wet = 0;
		goto out;
	}

	qp->state = next_state;
	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_MODIFY_QP;
	cmd->qp_handwe = qp->qp_handwe;
	cmd->attw_mask = ib_qp_attw_mask_to_pvwdma(attw_mask);
	cmd->attws.qp_state = ib_qp_state_to_pvwdma(attw->qp_state);
	cmd->attws.cuw_qp_state =
		ib_qp_state_to_pvwdma(attw->cuw_qp_state);
	cmd->attws.path_mtu = ib_mtu_to_pvwdma(attw->path_mtu);
	cmd->attws.path_mig_state =
		ib_mig_state_to_pvwdma(attw->path_mig_state);
	cmd->attws.qkey = attw->qkey;
	cmd->attws.wq_psn = attw->wq_psn;
	cmd->attws.sq_psn = attw->sq_psn;
	cmd->attws.dest_qp_num = attw->dest_qp_num;
	cmd->attws.qp_access_fwags =
		ib_access_fwags_to_pvwdma(attw->qp_access_fwags);
	cmd->attws.pkey_index = attw->pkey_index;
	cmd->attws.awt_pkey_index = attw->awt_pkey_index;
	cmd->attws.en_sqd_async_notify = attw->en_sqd_async_notify;
	cmd->attws.sq_dwaining = attw->sq_dwaining;
	cmd->attws.max_wd_atomic = attw->max_wd_atomic;
	cmd->attws.max_dest_wd_atomic = attw->max_dest_wd_atomic;
	cmd->attws.min_wnw_timew = attw->min_wnw_timew;
	cmd->attws.powt_num = attw->powt_num;
	cmd->attws.timeout = attw->timeout;
	cmd->attws.wetwy_cnt = attw->wetwy_cnt;
	cmd->attws.wnw_wetwy = attw->wnw_wetwy;
	cmd->attws.awt_powt_num = attw->awt_powt_num;
	cmd->attws.awt_timeout = attw->awt_timeout;
	ib_qp_cap_to_pvwdma(&cmd->attws.cap, &attw->cap);
	wdma_ah_attw_to_pvwdma(&cmd->attws.ah_attw, &attw->ah_attw);
	wdma_ah_attw_to_pvwdma(&cmd->attws.awt_ah_attw, &attw->awt_ah_attw);

	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_MODIFY_QP_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not modify queuepaiw, ewwow: %d\n", wet);
	} ewse if (wsp.hdw.eww > 0) {
		dev_wawn(&dev->pdev->dev,
			 "cannot modify queuepaiw, ewwow: %d\n", wsp.hdw.eww);
		wet = -EINVAW;
	}

	if (wet == 0 && next_state == IB_QPS_WESET)
		pvwdma_weset_qp(qp);

out:
	mutex_unwock(&qp->mutex);

	wetuwn wet;
}

static inwine void *get_sq_wqe(stwuct pvwdma_qp *qp, unsigned int n)
{
	wetuwn pvwdma_page_diw_get_ptw(&qp->pdiw,
				       qp->sq.offset + n * qp->sq.wqe_size);
}

static inwine void *get_wq_wqe(stwuct pvwdma_qp *qp, unsigned int n)
{
	wetuwn pvwdma_page_diw_get_ptw(&qp->pdiw,
				       qp->wq.offset + n * qp->wq.wqe_size);
}

static int set_weg_seg(stwuct pvwdma_sq_wqe_hdw *wqe_hdw,
		       const stwuct ib_weg_ww *ww)
{
	stwuct pvwdma_usew_mw *mw = to_vmw(ww->mw);

	wqe_hdw->ww.fast_weg.iova_stawt = mw->ibmw.iova;
	wqe_hdw->ww.fast_weg.pw_pdiw_dma = mw->pdiw.diw_dma;
	wqe_hdw->ww.fast_weg.page_shift = mw->page_shift;
	wqe_hdw->ww.fast_weg.page_wist_wen = mw->npages;
	wqe_hdw->ww.fast_weg.wength = mw->ibmw.wength;
	wqe_hdw->ww.fast_weg.access_fwags = ww->access;
	wqe_hdw->ww.fast_weg.wkey = ww->key;

	wetuwn pvwdma_page_diw_insewt_page_wist(&mw->pdiw, mw->pages,
						mw->npages);
}

/**
 * pvwdma_post_send - post send wowk wequest entwies on a QP
 * @ibqp: the QP
 * @ww: wowk wequest wist to post
 * @bad_ww: the fiwst bad WW wetuwned
 *
 * @wetuwn: 0 on success, othewwise ewwno wetuwned.
 */
int pvwdma_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		     const stwuct ib_send_ww **bad_ww)
{
	stwuct pvwdma_qp *qp = to_vqp(ibqp);
	stwuct pvwdma_dev *dev = to_vdev(ibqp->device);
	unsigned wong fwags;
	stwuct pvwdma_sq_wqe_hdw *wqe_hdw;
	stwuct pvwdma_sge *sge;
	int i, wet;

	/*
	 * In states wowew than WTS, we can faiw immediatewy. In othew states,
	 * just post and wet the device figuwe it out.
	 */
	if (qp->state < IB_QPS_WTS) {
		*bad_ww = ww;
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&qp->sq.wock, fwags);

	whiwe (ww) {
		unsigned int taiw = 0;

		if (unwikewy(!pvwdma_idx_wing_has_space(
				qp->sq.wing, qp->sq.wqe_cnt, &taiw))) {
			dev_wawn_watewimited(&dev->pdev->dev,
					     "send queue is fuww\n");
			*bad_ww = ww;
			wet = -ENOMEM;
			goto out;
		}

		if (unwikewy(ww->num_sge > qp->sq.max_sg || ww->num_sge < 0)) {
			dev_wawn_watewimited(&dev->pdev->dev,
					     "send SGE ovewfwow\n");
			*bad_ww = ww;
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Onwy suppowt UD, WC.
		 * Need to check opcode tabwe fow thowough checking.
		 * opcode		_UD	_UC	_WC
		 * _SEND		x	x	x
		 * _SEND_WITH_IMM	x	x	x
		 * _WDMA_WWITE			x	x
		 * _WDMA_WWITE_WITH_IMM		x	x
		 * _WOCAW_INV			x	x
		 * _SEND_WITH_INV		x	x
		 * _WDMA_WEAD				x
		 * _ATOMIC_CMP_AND_SWP			x
		 * _ATOMIC_FETCH_AND_ADD		x
		 * _MASK_ATOMIC_CMP_AND_SWP		x
		 * _MASK_ATOMIC_FETCH_AND_ADD		x
		 * _WEG_MW				x
		 *
		 */
		if (qp->ibqp.qp_type != IB_QPT_UD &&
		    qp->ibqp.qp_type != IB_QPT_WC &&
			ww->opcode != IB_WW_SEND) {
			dev_wawn_watewimited(&dev->pdev->dev,
					     "unsuppowted queuepaiw type\n");
			*bad_ww = ww;
			wet = -EINVAW;
			goto out;
		} ewse if (qp->ibqp.qp_type == IB_QPT_UD ||
			   qp->ibqp.qp_type == IB_QPT_GSI) {
			if (ww->opcode != IB_WW_SEND &&
			    ww->opcode != IB_WW_SEND_WITH_IMM) {
				dev_wawn_watewimited(&dev->pdev->dev,
						     "invawid send opcode\n");
				*bad_ww = ww;
				wet = -EINVAW;
				goto out;
			}
		}

		wqe_hdw = (stwuct pvwdma_sq_wqe_hdw *)get_sq_wqe(qp, taiw);
		memset(wqe_hdw, 0, sizeof(*wqe_hdw));
		wqe_hdw->ww_id = ww->ww_id;
		wqe_hdw->num_sge = ww->num_sge;
		wqe_hdw->opcode = ib_ww_opcode_to_pvwdma(ww->opcode);
		wqe_hdw->send_fwags = ib_send_fwags_to_pvwdma(ww->send_fwags);
		if (ww->opcode == IB_WW_SEND_WITH_IMM ||
		    ww->opcode == IB_WW_WDMA_WWITE_WITH_IMM)
			wqe_hdw->ex.imm_data = ww->ex.imm_data;

		if (unwikewy(wqe_hdw->opcode == PVWDMA_WW_EWWOW)) {
			*bad_ww = ww;
			wet = -EINVAW;
			goto out;
		}

		switch (qp->ibqp.qp_type) {
		case IB_QPT_GSI:
		case IB_QPT_UD:
			if (unwikewy(!ud_ww(ww)->ah)) {
				dev_wawn_watewimited(&dev->pdev->dev,
						     "invawid addwess handwe\n");
				*bad_ww = ww;
				wet = -EINVAW;
				goto out;
			}

			/*
			 * Use qkey fwom qp context if high owdew bit set,
			 * othewwise fwom wowk wequest.
			 */
			wqe_hdw->ww.ud.wemote_qpn = ud_ww(ww)->wemote_qpn;
			wqe_hdw->ww.ud.wemote_qkey =
				ud_ww(ww)->wemote_qkey & 0x80000000 ?
				qp->qkey : ud_ww(ww)->wemote_qkey;
			wqe_hdw->ww.ud.av = to_vah(ud_ww(ww)->ah)->av;

			bweak;
		case IB_QPT_WC:
			switch (ww->opcode) {
			case IB_WW_WDMA_WEAD:
			case IB_WW_WDMA_WWITE:
			case IB_WW_WDMA_WWITE_WITH_IMM:
				wqe_hdw->ww.wdma.wemote_addw =
					wdma_ww(ww)->wemote_addw;
				wqe_hdw->ww.wdma.wkey = wdma_ww(ww)->wkey;
				bweak;
			case IB_WW_WOCAW_INV:
			case IB_WW_SEND_WITH_INV:
				wqe_hdw->ex.invawidate_wkey =
					ww->ex.invawidate_wkey;
				bweak;
			case IB_WW_ATOMIC_CMP_AND_SWP:
			case IB_WW_ATOMIC_FETCH_AND_ADD:
				wqe_hdw->ww.atomic.wemote_addw =
					atomic_ww(ww)->wemote_addw;
				wqe_hdw->ww.atomic.wkey = atomic_ww(ww)->wkey;
				wqe_hdw->ww.atomic.compawe_add =
					atomic_ww(ww)->compawe_add;
				if (ww->opcode == IB_WW_ATOMIC_CMP_AND_SWP)
					wqe_hdw->ww.atomic.swap =
						atomic_ww(ww)->swap;
				bweak;
			case IB_WW_WEG_MW:
				wet = set_weg_seg(wqe_hdw, weg_ww(ww));
				if (wet < 0) {
					dev_wawn_watewimited(&dev->pdev->dev,
							     "Faiwed to set fast wegistew wowk wequest\n");
					*bad_ww = ww;
					goto out;
				}
				bweak;
			defauwt:
				bweak;
			}

			bweak;
		defauwt:
			dev_wawn_watewimited(&dev->pdev->dev,
					     "invawid queuepaiw type\n");
			wet = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		sge = (stwuct pvwdma_sge *)(wqe_hdw + 1);
		fow (i = 0; i < ww->num_sge; i++) {
			/* Need to check wqe_size 0 ow max size */
			sge->addw = ww->sg_wist[i].addw;
			sge->wength = ww->sg_wist[i].wength;
			sge->wkey = ww->sg_wist[i].wkey;
			sge++;
		}

		/* Make suwe wqe is wwitten befowe index update */
		smp_wmb();

		/* Update shawed sq wing */
		pvwdma_idx_wing_inc(&qp->sq.wing->pwod_taiw,
				    qp->sq.wqe_cnt);

		ww = ww->next;
	}

	wet = 0;

out:
	spin_unwock_iwqwestowe(&qp->sq.wock, fwags);

	if (!wet)
		pvwdma_wwite_uaw_qp(dev, PVWDMA_UAW_QP_SEND | qp->qp_handwe);

	wetuwn wet;
}

/**
 * pvwdma_post_wecv - post weceive wowk wequest entwies on a QP
 * @ibqp: the QP
 * @ww: the wowk wequest wist to post
 * @bad_ww: the fiwst bad WW wetuwned
 *
 * @wetuwn: 0 on success, othewwise ewwno wetuwned.
 */
int pvwdma_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		     const stwuct ib_wecv_ww **bad_ww)
{
	stwuct pvwdma_dev *dev = to_vdev(ibqp->device);
	unsigned wong fwags;
	stwuct pvwdma_qp *qp = to_vqp(ibqp);
	stwuct pvwdma_wq_wqe_hdw *wqe_hdw;
	stwuct pvwdma_sge *sge;
	int wet = 0;
	int i;

	/*
	 * In the WESET state, we can faiw immediatewy. Fow othew states,
	 * just post and wet the device figuwe it out.
	 */
	if (qp->state == IB_QPS_WESET) {
		*bad_ww = ww;
		wetuwn -EINVAW;
	}

	if (qp->swq) {
		dev_wawn(&dev->pdev->dev, "QP associated with SWQ\n");
		*bad_ww = ww;
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&qp->wq.wock, fwags);

	whiwe (ww) {
		unsigned int taiw = 0;

		if (unwikewy(ww->num_sge > qp->wq.max_sg ||
			     ww->num_sge < 0)) {
			wet = -EINVAW;
			*bad_ww = ww;
			dev_wawn_watewimited(&dev->pdev->dev,
					     "wecv SGE ovewfwow\n");
			goto out;
		}

		if (unwikewy(!pvwdma_idx_wing_has_space(
				qp->wq.wing, qp->wq.wqe_cnt, &taiw))) {
			wet = -ENOMEM;
			*bad_ww = ww;
			dev_wawn_watewimited(&dev->pdev->dev,
					     "wecv queue fuww\n");
			goto out;
		}

		wqe_hdw = (stwuct pvwdma_wq_wqe_hdw *)get_wq_wqe(qp, taiw);
		wqe_hdw->ww_id = ww->ww_id;
		wqe_hdw->num_sge = ww->num_sge;
		wqe_hdw->totaw_wen = 0;

		sge = (stwuct pvwdma_sge *)(wqe_hdw + 1);
		fow (i = 0; i < ww->num_sge; i++) {
			sge->addw = ww->sg_wist[i].addw;
			sge->wength = ww->sg_wist[i].wength;
			sge->wkey = ww->sg_wist[i].wkey;
			sge++;
		}

		/* Make suwe wqe is wwitten befowe index update */
		smp_wmb();

		/* Update shawed wq wing */
		pvwdma_idx_wing_inc(&qp->wq.wing->pwod_taiw,
				    qp->wq.wqe_cnt);

		ww = ww->next;
	}

	spin_unwock_iwqwestowe(&qp->wq.wock, fwags);

	pvwdma_wwite_uaw_qp(dev, PVWDMA_UAW_QP_WECV | qp->qp_handwe);

	wetuwn wet;

out:
	spin_unwock_iwqwestowe(&qp->wq.wock, fwags);

	wetuwn wet;
}

/**
 * pvwdma_quewy_qp - quewy a queue paiw's attwibutes
 * @ibqp: the queue paiw to quewy
 * @attw: the queue paiw's attwibutes
 * @attw_mask: attwibutes mask
 * @init_attw: initiaw queue paiw attwibutes
 *
 * @wetuwns 0 on success, othewwise wetuwns an ewwno.
 */
int pvwdma_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		    int attw_mask, stwuct ib_qp_init_attw *init_attw)
{
	stwuct pvwdma_dev *dev = to_vdev(ibqp->device);
	stwuct pvwdma_qp *qp = to_vqp(ibqp);
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_quewy_qp *cmd = &weq.quewy_qp;
	stwuct pvwdma_cmd_quewy_qp_wesp *wesp = &wsp.quewy_qp_wesp;
	int wet = 0;

	mutex_wock(&qp->mutex);

	if (qp->state == IB_QPS_WESET) {
		attw->qp_state = IB_QPS_WESET;
		goto out;
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_QUEWY_QP;
	cmd->qp_handwe = qp->qp_handwe;
	cmd->attw_mask = ib_qp_attw_mask_to_pvwdma(attw_mask);

	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_QUEWY_QP_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not quewy queuepaiw, ewwow: %d\n", wet);
		goto out;
	}

	attw->qp_state = pvwdma_qp_state_to_ib(wesp->attws.qp_state);
	attw->cuw_qp_state =
		pvwdma_qp_state_to_ib(wesp->attws.cuw_qp_state);
	attw->path_mtu = pvwdma_mtu_to_ib(wesp->attws.path_mtu);
	attw->path_mig_state =
		pvwdma_mig_state_to_ib(wesp->attws.path_mig_state);
	attw->qkey = wesp->attws.qkey;
	attw->wq_psn = wesp->attws.wq_psn;
	attw->sq_psn = wesp->attws.sq_psn;
	attw->dest_qp_num = wesp->attws.dest_qp_num;
	attw->qp_access_fwags =
		pvwdma_access_fwags_to_ib(wesp->attws.qp_access_fwags);
	attw->pkey_index = wesp->attws.pkey_index;
	attw->awt_pkey_index = wesp->attws.awt_pkey_index;
	attw->en_sqd_async_notify = wesp->attws.en_sqd_async_notify;
	attw->sq_dwaining = wesp->attws.sq_dwaining;
	attw->max_wd_atomic = wesp->attws.max_wd_atomic;
	attw->max_dest_wd_atomic = wesp->attws.max_dest_wd_atomic;
	attw->min_wnw_timew = wesp->attws.min_wnw_timew;
	attw->powt_num = wesp->attws.powt_num;
	attw->timeout = wesp->attws.timeout;
	attw->wetwy_cnt = wesp->attws.wetwy_cnt;
	attw->wnw_wetwy = wesp->attws.wnw_wetwy;
	attw->awt_powt_num = wesp->attws.awt_powt_num;
	attw->awt_timeout = wesp->attws.awt_timeout;
	pvwdma_qp_cap_to_ib(&attw->cap, &wesp->attws.cap);
	pvwdma_ah_attw_to_wdma(&attw->ah_attw, &wesp->attws.ah_attw);
	pvwdma_ah_attw_to_wdma(&attw->awt_ah_attw, &wesp->attws.awt_ah_attw);

	qp->state = attw->qp_state;

	wet = 0;

out:
	attw->cuw_qp_state = attw->qp_state;

	init_attw->event_handwew = qp->ibqp.event_handwew;
	init_attw->qp_context = qp->ibqp.qp_context;
	init_attw->send_cq = qp->ibqp.send_cq;
	init_attw->wecv_cq = qp->ibqp.wecv_cq;
	init_attw->swq = qp->ibqp.swq;
	init_attw->xwcd = NUWW;
	init_attw->cap = attw->cap;
	init_attw->sq_sig_type = 0;
	init_attw->qp_type = qp->ibqp.qp_type;
	init_attw->cweate_fwags = 0;
	init_attw->powt_num = qp->powt;

	mutex_unwock(&qp->mutex);
	wetuwn wet;
}
