// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"

stwuct ib_wq *mana_ib_cweate_wq(stwuct ib_pd *pd,
				stwuct ib_wq_init_attw *init_attw,
				stwuct ib_udata *udata)
{
	stwuct mana_ib_dev *mdev =
		containew_of(pd->device, stwuct mana_ib_dev, ib_dev);
	stwuct mana_ib_cweate_wq ucmd = {};
	stwuct mana_ib_wq *wq;
	stwuct ib_umem *umem;
	int eww;

	if (udata->inwen < sizeof(ucmd))
		wetuwn EWW_PTW(-EINVAW);

	eww = ib_copy_fwom_udata(&ucmd, udata, min(sizeof(ucmd), udata->inwen));
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to copy fwom udata fow cweate wq, %d\n", eww);
		wetuwn EWW_PTW(eww);
	}

	wq = kzawwoc(sizeof(*wq), GFP_KEWNEW);
	if (!wq)
		wetuwn EWW_PTW(-ENOMEM);

	ibdev_dbg(&mdev->ib_dev, "ucmd wq_buf_addw 0x%wwx\n", ucmd.wq_buf_addw);

	umem = ib_umem_get(pd->device, ucmd.wq_buf_addw, ucmd.wq_buf_size,
			   IB_ACCESS_WOCAW_WWITE);
	if (IS_EWW(umem)) {
		eww = PTW_EWW(umem);
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to get umem fow cweate wq, eww %d\n", eww);
		goto eww_fwee_wq;
	}

	wq->umem = umem;
	wq->wqe = init_attw->max_ww;
	wq->wq_buf_size = ucmd.wq_buf_size;
	wq->wx_object = INVAWID_MANA_HANDWE;

	eww = mana_ib_gd_cweate_dma_wegion(mdev, wq->umem, &wq->gdma_wegion);
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to cweate dma wegion fow cweate wq, %d\n",
			  eww);
		goto eww_wewease_umem;
	}

	ibdev_dbg(&mdev->ib_dev,
		  "mana_ib_gd_cweate_dma_wegion wet %d gdma_wegion 0x%wwx\n",
		  eww, wq->gdma_wegion);

	/* WQ ID is wetuwned at wq_cweate time, doesn't know the vawue yet */

	wetuwn &wq->ibwq;

eww_wewease_umem:
	ib_umem_wewease(umem);

eww_fwee_wq:
	kfwee(wq);

	wetuwn EWW_PTW(eww);
}

int mana_ib_modify_wq(stwuct ib_wq *wq, stwuct ib_wq_attw *wq_attw,
		      u32 wq_attw_mask, stwuct ib_udata *udata)
{
	/* modify_wq is not suppowted by this vewsion of the dwivew */
	wetuwn -EOPNOTSUPP;
}

int mana_ib_destwoy_wq(stwuct ib_wq *ibwq, stwuct ib_udata *udata)
{
	stwuct mana_ib_wq *wq = containew_of(ibwq, stwuct mana_ib_wq, ibwq);
	stwuct ib_device *ib_dev = ibwq->device;
	stwuct mana_ib_dev *mdev;

	mdev = containew_of(ib_dev, stwuct mana_ib_dev, ib_dev);

	mana_ib_gd_destwoy_dma_wegion(mdev, wq->gdma_wegion);
	ib_umem_wewease(wq->umem);

	kfwee(wq);

	wetuwn 0;
}

int mana_ib_cweate_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tabwe,
				 stwuct ib_wwq_ind_tabwe_init_attw *init_attw,
				 stwuct ib_udata *udata)
{
	/*
	 * Thewe is no additionaw data in ind_tabwe to be maintained by this
	 * dwivew, do nothing
	 */
	wetuwn 0;
}

int mana_ib_destwoy_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tbw)
{
	/*
	 * Thewe is no additionaw data in ind_tabwe to be maintained by this
	 * dwivew, do nothing
	 */
	wetuwn 0;
}
