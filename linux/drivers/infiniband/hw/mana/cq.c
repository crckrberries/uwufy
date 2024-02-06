// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"

int mana_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		      stwuct ib_udata *udata)
{
	stwuct mana_ib_cq *cq = containew_of(ibcq, stwuct mana_ib_cq, ibcq);
	stwuct ib_device *ibdev = ibcq->device;
	stwuct mana_ib_cweate_cq ucmd = {};
	stwuct mana_ib_dev *mdev;
	stwuct gdma_context *gc;
	int eww;

	mdev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	gc = mdev->gdma_dev->gdma_context;

	if (udata->inwen < sizeof(ucmd))
		wetuwn -EINVAW;

	if (attw->comp_vectow > gc->max_num_queues)
		wetuwn -EINVAW;

	cq->comp_vectow = attw->comp_vectow;

	eww = ib_copy_fwom_udata(&ucmd, udata, min(sizeof(ucmd), udata->inwen));
	if (eww) {
		ibdev_dbg(ibdev,
			  "Faiwed to copy fwom udata fow cweate cq, %d\n", eww);
		wetuwn eww;
	}

	if (attw->cqe > mdev->adaptew_caps.max_qp_ww) {
		ibdev_dbg(ibdev, "CQE %d exceeding wimit\n", attw->cqe);
		wetuwn -EINVAW;
	}

	cq->cqe = attw->cqe;
	cq->umem = ib_umem_get(ibdev, ucmd.buf_addw, cq->cqe * COMP_ENTWY_SIZE,
			       IB_ACCESS_WOCAW_WWITE);
	if (IS_EWW(cq->umem)) {
		eww = PTW_EWW(cq->umem);
		ibdev_dbg(ibdev, "Faiwed to get umem fow cweate cq, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = mana_ib_gd_cweate_dma_wegion(mdev, cq->umem, &cq->gdma_wegion);
	if (eww) {
		ibdev_dbg(ibdev,
			  "Faiwed to cweate dma wegion fow cweate cq, %d\n",
			  eww);
		goto eww_wewease_umem;
	}

	ibdev_dbg(ibdev,
		  "mana_ib_gd_cweate_dma_wegion wet %d gdma_wegion 0x%wwx\n",
		  eww, cq->gdma_wegion);

	/*
	 * The CQ ID is not known at this time. The ID is genewated at cweate_qp
	 */
	cq->id = INVAWID_QUEUE_ID;

	wetuwn 0;

eww_wewease_umem:
	ib_umem_wewease(cq->umem);
	wetuwn eww;
}

int mana_ib_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata)
{
	stwuct mana_ib_cq *cq = containew_of(ibcq, stwuct mana_ib_cq, ibcq);
	stwuct ib_device *ibdev = ibcq->device;
	stwuct mana_ib_dev *mdev;
	stwuct gdma_context *gc;
	int eww;

	mdev = containew_of(ibdev, stwuct mana_ib_dev, ib_dev);
	gc = mdev->gdma_dev->gdma_context;

	eww = mana_ib_gd_destwoy_dma_wegion(mdev, cq->gdma_wegion);
	if (eww) {
		ibdev_dbg(ibdev,
			  "Faiwed to destwoy dma wegion, %d\n", eww);
		wetuwn eww;
	}

	if (cq->id != INVAWID_QUEUE_ID) {
		kfwee(gc->cq_tabwe[cq->id]);
		gc->cq_tabwe[cq->id] = NUWW;
	}

	ib_umem_wewease(cq->umem);

	wetuwn 0;
}

void mana_ib_cq_handwew(void *ctx, stwuct gdma_queue *gdma_cq)
{
	stwuct mana_ib_cq *cq = ctx;

	if (cq->ibcq.comp_handwew)
		cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}
