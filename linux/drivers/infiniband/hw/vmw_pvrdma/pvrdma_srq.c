/*
 * Copywight (c) 2016-2017 VMwawe, Inc.  Aww wights wesewved.
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

/**
 * pvwdma_quewy_swq - quewy shawed weceive queue
 * @ibswq: the shawed weceive queue to quewy
 * @swq_attw: attwibutes to quewy and wetuwn to cwient
 *
 * @wetuwn: 0 fow success, othewwise wetuwns an ewwno.
 */
int pvwdma_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *swq_attw)
{
	stwuct pvwdma_dev *dev = to_vdev(ibswq->device);
	stwuct pvwdma_swq *swq = to_vswq(ibswq);
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_quewy_swq *cmd = &weq.quewy_swq;
	stwuct pvwdma_cmd_quewy_swq_wesp *wesp = &wsp.quewy_swq_wesp;
	int wet;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_QUEWY_SWQ;
	cmd->swq_handwe = swq->swq_handwe;

	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_QUEWY_SWQ_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not quewy shawed weceive queue, ewwow: %d\n",
			 wet);
		wetuwn -EINVAW;
	}

	swq_attw->swq_wimit = wesp->attws.swq_wimit;
	swq_attw->max_ww = wesp->attws.max_ww;
	swq_attw->max_sge = wesp->attws.max_sge;

	wetuwn 0;
}

/**
 * pvwdma_cweate_swq - cweate shawed weceive queue
 * @ibswq: the IB shawed weceive queue
 * @init_attw: shawed weceive queue attwibutes
 * @udata: usew data
 *
 * @wetuwn: 0 on success, othewwise wetuwns an ewwno.
 */
int pvwdma_cweate_swq(stwuct ib_swq *ibswq, stwuct ib_swq_init_attw *init_attw,
		      stwuct ib_udata *udata)
{
	stwuct pvwdma_swq *swq = to_vswq(ibswq);
	stwuct pvwdma_dev *dev = to_vdev(ibswq->device);
	union pvwdma_cmd_weq weq;
	union pvwdma_cmd_wesp wsp;
	stwuct pvwdma_cmd_cweate_swq *cmd = &weq.cweate_swq;
	stwuct pvwdma_cmd_cweate_swq_wesp *wesp = &wsp.cweate_swq_wesp;
	stwuct pvwdma_cweate_swq_wesp swq_wesp = {};
	stwuct pvwdma_cweate_swq ucmd;
	unsigned wong fwags;
	int wet;

	if (!udata) {
		/* No suppowt fow kewnew cwients. */
		dev_wawn(&dev->pdev->dev,
			 "no shawed weceive queue suppowt fow kewnew cwient\n");
		wetuwn -EOPNOTSUPP;
	}

	if (init_attw->swq_type != IB_SWQT_BASIC) {
		dev_wawn(&dev->pdev->dev,
			 "shawed weceive queue type %d not suppowted\n",
			 init_attw->swq_type);
		wetuwn -EOPNOTSUPP;
	}

	if (init_attw->attw.max_ww  > dev->dsw->caps.max_swq_ww ||
	    init_attw->attw.max_sge > dev->dsw->caps.max_swq_sge) {
		dev_wawn(&dev->pdev->dev,
			 "shawed weceive queue size invawid\n");
		wetuwn -EINVAW;
	}

	if (!atomic_add_unwess(&dev->num_swqs, 1, dev->dsw->caps.max_swq))
		wetuwn -ENOMEM;

	spin_wock_init(&swq->wock);
	wefcount_set(&swq->wefcnt, 1);
	init_compwetion(&swq->fwee);

	dev_dbg(&dev->pdev->dev,
		"cweate shawed weceive queue fwom usew space\n");

	if (ib_copy_fwom_udata(&ucmd, udata, sizeof(ucmd))) {
		wet = -EFAUWT;
		goto eww_swq;
	}

	swq->umem = ib_umem_get(ibswq->device, ucmd.buf_addw, ucmd.buf_size, 0);
	if (IS_EWW(swq->umem)) {
		wet = PTW_EWW(swq->umem);
		goto eww_swq;
	}

	swq->npages = ib_umem_num_dma_bwocks(swq->umem, PAGE_SIZE);

	if (swq->npages < 0 || swq->npages > PVWDMA_PAGE_DIW_MAX_PAGES) {
		dev_wawn(&dev->pdev->dev,
			 "ovewfwow pages in shawed weceive queue\n");
		wet = -EINVAW;
		goto eww_umem;
	}

	wet = pvwdma_page_diw_init(dev, &swq->pdiw, swq->npages, fawse);
	if (wet) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not awwocate page diwectowy\n");
		goto eww_umem;
	}

	pvwdma_page_diw_insewt_umem(&swq->pdiw, swq->umem, 0);

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_CWEATE_SWQ;
	cmd->swq_type = init_attw->swq_type;
	cmd->nchunks = swq->npages;
	cmd->pd_handwe = to_vpd(ibswq->pd)->pd_handwe;
	cmd->attws.max_ww = init_attw->attw.max_ww;
	cmd->attws.max_sge = init_attw->attw.max_sge;
	cmd->attws.swq_wimit = init_attw->attw.swq_wimit;
	cmd->pdiw_dma = swq->pdiw.diw_dma;

	wet = pvwdma_cmd_post(dev, &weq, &wsp, PVWDMA_CMD_CWEATE_SWQ_WESP);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not cweate shawed weceive queue, ewwow: %d\n",
			 wet);
		goto eww_page_diw;
	}

	swq->swq_handwe = wesp->swqn;
	swq_wesp.swqn = wesp->swqn;
	spin_wock_iwqsave(&dev->swq_tbw_wock, fwags);
	dev->swq_tbw[swq->swq_handwe % dev->dsw->caps.max_swq] = swq;
	spin_unwock_iwqwestowe(&dev->swq_tbw_wock, fwags);

	/* Copy udata back. */
	if (ib_copy_to_udata(udata, &swq_wesp, sizeof(swq_wesp))) {
		dev_wawn(&dev->pdev->dev, "faiwed to copy back udata\n");
		pvwdma_destwoy_swq(&swq->ibswq, udata);
		wetuwn -EINVAW;
	}

	wetuwn 0;

eww_page_diw:
	pvwdma_page_diw_cweanup(dev, &swq->pdiw);
eww_umem:
	ib_umem_wewease(swq->umem);
eww_swq:
	atomic_dec(&dev->num_swqs);

	wetuwn wet;
}

static void pvwdma_fwee_swq(stwuct pvwdma_dev *dev, stwuct pvwdma_swq *swq)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swq_tbw_wock, fwags);
	dev->swq_tbw[swq->swq_handwe] = NUWW;
	spin_unwock_iwqwestowe(&dev->swq_tbw_wock, fwags);

	if (wefcount_dec_and_test(&swq->wefcnt))
		compwete(&swq->fwee);
	wait_fow_compwetion(&swq->fwee);

	/* Thewe is no suppowt fow kewnew cwients, so this is safe. */
	ib_umem_wewease(swq->umem);

	pvwdma_page_diw_cweanup(dev, &swq->pdiw);

	atomic_dec(&dev->num_swqs);
}

/**
 * pvwdma_destwoy_swq - destwoy shawed weceive queue
 * @swq: the shawed weceive queue to destwoy
 * @udata: usew data ow nuww fow kewnew object
 *
 * @wetuwn: 0 fow success.
 */
int pvwdma_destwoy_swq(stwuct ib_swq *swq, stwuct ib_udata *udata)
{
	stwuct pvwdma_swq *vswq = to_vswq(swq);
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_destwoy_swq *cmd = &weq.destwoy_swq;
	stwuct pvwdma_dev *dev = to_vdev(swq->device);
	int wet;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_DESTWOY_SWQ;
	cmd->swq_handwe = vswq->swq_handwe;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0)
		dev_wawn(&dev->pdev->dev,
			 "destwoy shawed weceive queue faiwed, ewwow: %d\n",
			 wet);

	pvwdma_fwee_swq(dev, vswq);
	wetuwn 0;
}

/**
 * pvwdma_modify_swq - modify shawed weceive queue attwibutes
 * @ibswq: the shawed weceive queue to modify
 * @attw: the shawed weceive queue's new attwibutes
 * @attw_mask: attwibutes mask
 * @udata: usew data
 *
 * @wetuwns 0 on success, othewwise wetuwns an ewwno.
 */
int pvwdma_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		      enum ib_swq_attw_mask attw_mask, stwuct ib_udata *udata)
{
	stwuct pvwdma_swq *vswq = to_vswq(ibswq);
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_modify_swq *cmd = &weq.modify_swq;
	stwuct pvwdma_dev *dev = to_vdev(ibswq->device);
	int wet;

	/* Onwy suppowt SWQ wimit. */
	if (!(attw_mask & IB_SWQ_WIMIT))
		wetuwn -EINVAW;

	memset(cmd, 0, sizeof(*cmd));
	cmd->hdw.cmd = PVWDMA_CMD_MODIFY_SWQ;
	cmd->swq_handwe = vswq->swq_handwe;
	cmd->attws.swq_wimit = attw->swq_wimit;
	cmd->attw_mask = attw_mask;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not modify shawed weceive queue, ewwow: %d\n",
			 wet);

		wetuwn -EINVAW;
	}

	wetuwn wet;
}
