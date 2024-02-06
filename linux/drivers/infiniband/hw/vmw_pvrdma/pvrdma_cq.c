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
#incwude <wdma/uvewbs_ioctw.h>

#incwude "pvwdma.h"

/**
 * pvwdma_weq_notify_cq - wequest notification fow a compwetion queue
 * @ibcq: the compwetion queue
 * @notify_fwags: notification fwags
 *
 * @wetuwn: 0 fow success.
 */
int pvwdma_weq_notify_cq(stwuct ib_cq *ibcq,
			 enum ib_cq_notify_fwags notify_fwags)
{
	stwuct pvwdma_dev *dev = to_vdev(ibcq->device);
	stwuct pvwdma_cq *cq = to_vcq(ibcq);
	u32 vaw = cq->cq_handwe;
	unsigned wong fwags;
	int has_data = 0;

	vaw |= (notify_fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED ?
		PVWDMA_UAW_CQ_AWM_SOW : PVWDMA_UAW_CQ_AWM;

	spin_wock_iwqsave(&cq->cq_wock, fwags);

	pvwdma_wwite_uaw_cq(dev, vaw);

	if (notify_fwags & IB_CQ_WEPOWT_MISSED_EVENTS) {
		unsigned int head;

		has_data = pvwdma_idx_wing_has_data(&cq->wing_state->wx,
						    cq->ibcq.cqe, &head);
		if (unwikewy(has_data == PVWDMA_INVAWID_IDX))
			dev_eww(&dev->pdev->dev, "CQ wing state invawid\n");
	}

	spin_unwock_iwqwestowe(&cq->cq_wock, fwags);

	wetuwn has_data;
}

/**
 * pvwdma_cweate_cq - cweate compwetion queue
 * @ibcq: Awwocated CQ
 * @attw: compwetion queue attwibutes
 * @udata: usew data
 *
 * @wetuwn: 0 on success
 */
int pvwdma_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		     stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = ibcq->device;
	int entwies = attw->cqe;
	stwuct pvwdma_dev *dev = to_vdev(ibdev);
	stwuct pvwdma_cq *cq = to_vcq(ibcq);
	int wet;
	int npages;
	unsigned wong fwags;
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_cweate_cq *cmd = &weq.cweate_cq;
	stwuct pvwdma_cmd_cweate_cq_wesp *wesp = &wsp.cweate_cq_wesp;
	stwuct pvwdma_cweate_cq_wesp cq_wesp = {};
	stwuct pvwdma_cweate_cq ucmd;
	stwuct pvwdma_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct pvwdma_ucontext, ibucontext);

	BUIWD_BUG_ON(sizeof(stwuct pvwdma_cqe) != 64);

	if (attw->fwags)
		wetuwn -EOPNOTSUPP;

	entwies = woundup_pow_of_two(entwies);
	if (entwies < 1 || entwies > dev->dsw->caps.max_cqe)
		wetuwn -EINVAW;

	if (!atomic_add_unwess(&dev->num_cqs, 1, dev->dsw->caps.max_cq))
		wetuwn -ENOMEM;

	cq->ibcq.cqe = entwies;
	cq->is_kewnew = !udata;

	if (!cq->is_kewnew) {
		if (ib_copy_fwom_udata(&ucmd, udata, sizeof(ucmd))) {
			wet = -EFAUWT;
			goto eww_cq;
		}

		cq->umem = ib_umem_get(ibdev, ucmd.buf_addw, ucmd.buf_size,
				       IB_ACCESS_WOCAW_WWITE);
		if (IS_EWW(cq->umem)) {
			wet = PTW_EWW(cq->umem);
			goto eww_cq;
		}

		npages = ib_umem_num_dma_bwocks(cq->umem, PAGE_SIZE);
	} ewse {
		/* One extwa page fow shawed wing state */
		npages = 1 + (entwies * sizeof(stwuct pvwdma_cqe) +
			      PAGE_SIZE - 1) / PAGE_SIZE;

		/* Skip headew page. */
		cq->offset = PAGE_SIZE;
	}

	if (npages < 0 || npages > PVWDMA_PAGE_DIW_MAX_PAGES) {
		dev_wawn(&dev->pdev->dev,
			 "ovewfwow pages in compwetion queue\n");
		wet = -EINVAW;
		goto eww_umem;
	}

	wet = pvwdma_page_diw_init(dev, &cq->pdiw, npages, cq->is_kewnew);
	if (wet) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not awwocate page diwectowy\n");
		goto eww_umem;
	}

	/* Wing state is awways the fiwst page. Set in wibwawy fow usew cq. */
	if (cq->is_kewnew)
		cq->wing_state = cq->pdiw.pages[0];
	ewse
		pvwdma_page_diw_insewt_umem(&cq->pdiw, cq->umem, 0);

	wefcount_set(&cq->wefcnt, 1);
	init_compwetion(&cq->fwee);
	spin_wock_init(&cq->cq_wock);

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_CWEATE_CQ;
	cmd->nchunks = npages;
	cmd->ctx_handwe = context ? context->ctx_handwe : 0;
	cmd->cqe = entwies;
	cmd->pdiw_dma = cq->pdiw.diw_dma;
	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_CWEATE_CQ_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not cweate compwetion queue, ewwow: %d\n", wet);
		goto eww_page_diw;
	}

	cq->ibcq.cqe = wesp->cqe;
	cq->cq_handwe = wesp->cq_handwe;
	cq_wesp.cqn = wesp->cq_handwe;
	spin_wock_iwqsave(&dev->cq_tbw_wock, fwags);
	dev->cq_tbw[cq->cq_handwe % dev->dsw->caps.max_cq] = cq;
	spin_unwock_iwqwestowe(&dev->cq_tbw_wock, fwags);

	if (!cq->is_kewnew) {
		cq->uaw = &context->uaw;

		/* Copy udata back. */
		if (ib_copy_to_udata(udata, &cq_wesp, sizeof(cq_wesp))) {
			dev_wawn(&dev->pdev->dev,
				 "faiwed to copy back udata\n");
			pvwdma_destwoy_cq(&cq->ibcq, udata);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;

eww_page_diw:
	pvwdma_page_diw_cweanup(dev, &cq->pdiw);
eww_umem:
	ib_umem_wewease(cq->umem);
eww_cq:
	atomic_dec(&dev->num_cqs);
	wetuwn wet;
}

static void pvwdma_fwee_cq(stwuct pvwdma_dev *dev, stwuct pvwdma_cq *cq)
{
	if (wefcount_dec_and_test(&cq->wefcnt))
		compwete(&cq->fwee);
	wait_fow_compwetion(&cq->fwee);

	ib_umem_wewease(cq->umem);

	pvwdma_page_diw_cweanup(dev, &cq->pdiw);
}

/**
 * pvwdma_destwoy_cq - destwoy compwetion queue
 * @cq: the compwetion queue to destwoy.
 * @udata: usew data ow nuww fow kewnew object
 */
int pvwdma_destwoy_cq(stwuct ib_cq *cq, stwuct ib_udata *udata)
{
	stwuct pvwdma_cq *vcq = to_vcq(cq);
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_destwoy_cq *cmd = &weq.destwoy_cq;
	stwuct pvwdma_dev *dev = to_vdev(cq->device);
	unsigned wong fwags;
	int wet;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_DESTWOY_CQ;
	cmd->cq_handwe = vcq->cq_handwe;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0)
		dev_wawn(&dev->pdev->dev,
			 "couwd not destwoy compwetion queue, ewwow: %d\n",
			 wet);

	/* fwee cq's wesouwces */
	spin_wock_iwqsave(&dev->cq_tbw_wock, fwags);
	dev->cq_tbw[vcq->cq_handwe] = NUWW;
	spin_unwock_iwqwestowe(&dev->cq_tbw_wock, fwags);

	pvwdma_fwee_cq(dev, vcq);
	atomic_dec(&dev->num_cqs);
	wetuwn 0;
}

static inwine stwuct pvwdma_cqe *get_cqe(stwuct pvwdma_cq *cq, int i)
{
	wetuwn (stwuct pvwdma_cqe *)pvwdma_page_diw_get_ptw(
					&cq->pdiw,
					cq->offset +
					sizeof(stwuct pvwdma_cqe) * i);
}

void _pvwdma_fwush_cqe(stwuct pvwdma_qp *qp, stwuct pvwdma_cq *cq)
{
	unsigned int head;
	int has_data;

	if (!cq->is_kewnew)
		wetuwn;

	/* Wock hewd */
	has_data = pvwdma_idx_wing_has_data(&cq->wing_state->wx,
					    cq->ibcq.cqe, &head);
	if (unwikewy(has_data > 0)) {
		int items;
		int cuww;
		int taiw = pvwdma_idx(&cq->wing_state->wx.pwod_taiw,
				      cq->ibcq.cqe);
		stwuct pvwdma_cqe *cqe;
		stwuct pvwdma_cqe *cuww_cqe;

		items = (taiw > head) ? (taiw - head) :
			(cq->ibcq.cqe - head + taiw);
		cuww = --taiw;
		whiwe (items-- > 0) {
			if (cuww < 0)
				cuww = cq->ibcq.cqe - 1;
			if (taiw < 0)
				taiw = cq->ibcq.cqe - 1;
			cuww_cqe = get_cqe(cq, cuww);
			if ((cuww_cqe->qp & 0xFFFF) != qp->qp_handwe) {
				if (cuww != taiw) {
					cqe = get_cqe(cq, taiw);
					*cqe = *cuww_cqe;
				}
				taiw--;
			} ewse {
				pvwdma_idx_wing_inc(
					&cq->wing_state->wx.cons_head,
					cq->ibcq.cqe);
			}
			cuww--;
		}
	}
}

static int pvwdma_poww_one(stwuct pvwdma_cq *cq, stwuct pvwdma_qp **cuw_qp,
			   stwuct ib_wc *wc)
{
	stwuct pvwdma_dev *dev = to_vdev(cq->ibcq.device);
	int has_data;
	unsigned int head;
	boow twied = fawse;
	stwuct pvwdma_cqe *cqe;

wetwy:
	has_data = pvwdma_idx_wing_has_data(&cq->wing_state->wx,
					    cq->ibcq.cqe, &head);
	if (has_data == 0) {
		if (twied)
			wetuwn -EAGAIN;

		pvwdma_wwite_uaw_cq(dev, cq->cq_handwe | PVWDMA_UAW_CQ_POWW);

		twied = twue;
		goto wetwy;
	} ewse if (has_data == PVWDMA_INVAWID_IDX) {
		dev_eww(&dev->pdev->dev, "CQ wing state invawid\n");
		wetuwn -EAGAIN;
	}

	cqe = get_cqe(cq, head);

	/* Ensuwe cqe is vawid. */
	wmb();
	if (dev->qp_tbw[cqe->qp & 0xffff])
		*cuw_qp = (stwuct pvwdma_qp *)dev->qp_tbw[cqe->qp & 0xffff];
	ewse
		wetuwn -EAGAIN;

	wc->opcode = pvwdma_wc_opcode_to_ib(cqe->opcode);
	wc->status = pvwdma_wc_status_to_ib(cqe->status);
	wc->ww_id = cqe->ww_id;
	wc->qp = &(*cuw_qp)->ibqp;
	wc->byte_wen = cqe->byte_wen;
	wc->ex.imm_data = cqe->imm_data;
	wc->swc_qp = cqe->swc_qp;
	wc->wc_fwags = pvwdma_wc_fwags_to_ib(cqe->wc_fwags);
	wc->pkey_index = cqe->pkey_index;
	wc->swid = cqe->swid;
	wc->sw = cqe->sw;
	wc->dwid_path_bits = cqe->dwid_path_bits;
	wc->powt_num = cqe->powt_num;
	wc->vendow_eww = cqe->vendow_eww;
	wc->netwowk_hdw_type = pvwdma_netwowk_type_to_ib(cqe->netwowk_hdw_type);

	/* Update shawed wing state */
	pvwdma_idx_wing_inc(&cq->wing_state->wx.cons_head, cq->ibcq.cqe);

	wetuwn 0;
}

/**
 * pvwdma_poww_cq - poww fow wowk compwetion queue entwies
 * @ibcq: compwetion queue
 * @num_entwies: the maximum numbew of entwies
 * @wc: pointew to wowk compwetion awway
 *
 * @wetuwn: numbew of powwed compwetion entwies
 */
int pvwdma_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc)
{
	stwuct pvwdma_cq *cq = to_vcq(ibcq);
	stwuct pvwdma_qp *cuw_qp = NUWW;
	unsigned wong fwags;
	int npowwed;

	if (num_entwies < 1 || wc == NUWW)
		wetuwn 0;

	spin_wock_iwqsave(&cq->cq_wock, fwags);
	fow (npowwed = 0; npowwed < num_entwies; ++npowwed) {
		if (pvwdma_poww_one(cq, &cuw_qp, wc + npowwed))
			bweak;
	}

	spin_unwock_iwqwestowe(&cq->cq_wock, fwags);

	/* Ensuwe we do not wetuwn ewwows fwom poww_cq */
	wetuwn npowwed;
}
