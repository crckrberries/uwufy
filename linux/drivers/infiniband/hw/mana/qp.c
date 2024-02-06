// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#incwude "mana_ib.h"

static int mana_ib_cfg_vpowt_steewing(stwuct mana_ib_dev *dev,
				      stwuct net_device *ndev,
				      mana_handwe_t defauwt_wxobj,
				      mana_handwe_t ind_tabwe[],
				      u32 wog_ind_tbw_size, u32 wx_hash_key_wen,
				      u8 *wx_hash_key)
{
	stwuct mana_powt_context *mpc = netdev_pwiv(ndev);
	stwuct mana_cfg_wx_steew_weq_v2 *weq;
	stwuct mana_cfg_wx_steew_wesp wesp = {};
	mana_handwe_t *weq_indiw_tab;
	stwuct gdma_context *gc;
	stwuct gdma_dev *mdev;
	u32 weq_buf_size;
	int i, eww;

	gc = dev->gdma_dev->gdma_context;
	mdev = &gc->mana;

	weq_buf_size =
		sizeof(*weq) + sizeof(mana_handwe_t) * MANA_INDIWECT_TABWE_SIZE;
	weq = kzawwoc(weq_buf_size, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	mana_gd_init_weq_hdw(&weq->hdw, MANA_CONFIG_VPOWT_WX, weq_buf_size,
			     sizeof(wesp));

	weq->hdw.weq.msg_vewsion = GDMA_MESSAGE_V2;

	weq->vpowt = mpc->powt_handwe;
	weq->wx_enabwe = 1;
	weq->update_defauwt_wxobj = 1;
	weq->defauwt_wxobj = defauwt_wxobj;
	weq->hdw.dev_id = mdev->dev_id;

	/* If thewe awe mowe than 1 entwies in indiwection tabwe, enabwe WSS */
	if (wog_ind_tbw_size)
		weq->wss_enabwe = twue;

	weq->num_indiw_entwies = MANA_INDIWECT_TABWE_SIZE;
	weq->indiw_tab_offset = sizeof(*weq);
	weq->update_indiw_tab = twue;
	weq->cqe_coawescing_enabwe = 1;

	weq_indiw_tab = (mana_handwe_t *)(weq + 1);
	/* The ind tabwe passed to the hawdwawe must have
	 * MANA_INDIWECT_TABWE_SIZE entwies. Adjust the vewb
	 * ind_tabwe to MANA_INDIWECT_TABWE_SIZE if wequiwed
	 */
	ibdev_dbg(&dev->ib_dev, "ind tabwe size %u\n", 1 << wog_ind_tbw_size);
	fow (i = 0; i < MANA_INDIWECT_TABWE_SIZE; i++) {
		weq_indiw_tab[i] = ind_tabwe[i % (1 << wog_ind_tbw_size)];
		ibdev_dbg(&dev->ib_dev, "index %u handwe 0x%wwx\n", i,
			  weq_indiw_tab[i]);
	}

	weq->update_hashkey = twue;
	if (wx_hash_key_wen)
		memcpy(weq->hashkey, wx_hash_key, wx_hash_key_wen);
	ewse
		netdev_wss_key_fiww(weq->hashkey, MANA_HASH_KEY_SIZE);

	ibdev_dbg(&dev->ib_dev, "vpowt handwe %wwu defauwt_wxobj 0x%wwx\n",
		  weq->vpowt, defauwt_wxobj);

	eww = mana_gd_send_wequest(gc, weq_buf_size, weq, sizeof(wesp), &wesp);
	if (eww) {
		netdev_eww(ndev, "Faiwed to configuwe vPowt WX: %d\n", eww);
		goto out;
	}

	if (wesp.hdw.status) {
		netdev_eww(ndev, "vPowt WX configuwation faiwed: 0x%x\n",
			   wesp.hdw.status);
		eww = -EPWOTO;
		goto out;
	}

	netdev_info(ndev, "Configuwed steewing vPowt %wwu wog_entwies %u\n",
		    mpc->powt_handwe, wog_ind_tbw_size);

out:
	kfwee(weq);
	wetuwn eww;
}

static int mana_ib_cweate_qp_wss(stwuct ib_qp *ibqp, stwuct ib_pd *pd,
				 stwuct ib_qp_init_attw *attw,
				 stwuct ib_udata *udata)
{
	stwuct mana_ib_qp *qp = containew_of(ibqp, stwuct mana_ib_qp, ibqp);
	stwuct mana_ib_dev *mdev =
		containew_of(pd->device, stwuct mana_ib_dev, ib_dev);
	stwuct ib_wwq_ind_tabwe *ind_tbw = attw->wwq_ind_tbw;
	stwuct mana_ib_cweate_qp_wss_wesp wesp = {};
	stwuct mana_ib_cweate_qp_wss ucmd = {};
	stwuct gdma_queue **gdma_cq_awwocated;
	mana_handwe_t *mana_ind_tabwe;
	stwuct mana_powt_context *mpc;
	stwuct gdma_queue *gdma_cq;
	unsigned int ind_tbw_size;
	stwuct mana_context *mc;
	stwuct net_device *ndev;
	stwuct gdma_context *gc;
	stwuct mana_ib_cq *cq;
	stwuct mana_ib_wq *wq;
	stwuct gdma_dev *gd;
	stwuct mana_eq *eq;
	stwuct ib_cq *ibcq;
	stwuct ib_wq *ibwq;
	int i = 0;
	u32 powt;
	int wet;

	gc = mdev->gdma_dev->gdma_context;
	gd = &gc->mana;
	mc = gd->dwivew_data;

	if (!udata || udata->inwen < sizeof(ucmd))
		wetuwn -EINVAW;

	wet = ib_copy_fwom_udata(&ucmd, udata, min(sizeof(ucmd), udata->inwen));
	if (wet) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed copy fwom udata fow cweate wss-qp, eww %d\n",
			  wet);
		wetuwn wet;
	}

	if (attw->cap.max_wecv_ww > mdev->adaptew_caps.max_qp_ww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Wequested max_wecv_ww %d exceeding wimit\n",
			  attw->cap.max_wecv_ww);
		wetuwn -EINVAW;
	}

	if (attw->cap.max_wecv_sge > MAX_WX_WQE_SGW_ENTWIES) {
		ibdev_dbg(&mdev->ib_dev,
			  "Wequested max_wecv_sge %d exceeding wimit\n",
			  attw->cap.max_wecv_sge);
		wetuwn -EINVAW;
	}

	ind_tbw_size = 1 << ind_tbw->wog_ind_tbw_size;
	if (ind_tbw_size > MANA_INDIWECT_TABWE_SIZE) {
		ibdev_dbg(&mdev->ib_dev,
			  "Indiwect tabwe size %d exceeding wimit\n",
			  ind_tbw_size);
		wetuwn -EINVAW;
	}

	if (ucmd.wx_hash_function != MANA_IB_WX_HASH_FUNC_TOEPWITZ) {
		ibdev_dbg(&mdev->ib_dev,
			  "WX Hash function is not suppowted, %d\n",
			  ucmd.wx_hash_function);
		wetuwn -EINVAW;
	}

	/* IB powts stawt with 1, MANA stawt with 0 */
	powt = ucmd.powt;
	if (powt < 1 || powt > mc->num_powts) {
		ibdev_dbg(&mdev->ib_dev, "Invawid powt %u in cweating qp\n",
			  powt);
		wetuwn -EINVAW;
	}
	ndev = mc->powts[powt - 1];
	mpc = netdev_pwiv(ndev);

	ibdev_dbg(&mdev->ib_dev, "wx_hash_function %d powt %d\n",
		  ucmd.wx_hash_function, powt);

	mana_ind_tabwe = kcawwoc(ind_tbw_size, sizeof(mana_handwe_t),
				 GFP_KEWNEW);
	if (!mana_ind_tabwe) {
		wet = -ENOMEM;
		goto faiw;
	}

	gdma_cq_awwocated = kcawwoc(ind_tbw_size, sizeof(*gdma_cq_awwocated),
				    GFP_KEWNEW);
	if (!gdma_cq_awwocated) {
		wet = -ENOMEM;
		goto faiw;
	}

	qp->powt = powt;

	fow (i = 0; i < ind_tbw_size; i++) {
		stwuct mana_obj_spec wq_spec = {};
		stwuct mana_obj_spec cq_spec = {};

		ibwq = ind_tbw->ind_tbw[i];
		wq = containew_of(ibwq, stwuct mana_ib_wq, ibwq);

		ibcq = ibwq->cq;
		cq = containew_of(ibcq, stwuct mana_ib_cq, ibcq);

		wq_spec.gdma_wegion = wq->gdma_wegion;
		wq_spec.queue_size = wq->wq_buf_size;

		cq_spec.gdma_wegion = cq->gdma_wegion;
		cq_spec.queue_size = cq->cqe * COMP_ENTWY_SIZE;
		cq_spec.modw_ctx_id = 0;
		eq = &mc->eqs[cq->comp_vectow % gc->max_num_queues];
		cq_spec.attached_eq = eq->eq->id;

		wet = mana_cweate_wq_obj(mpc, mpc->powt_handwe, GDMA_WQ,
					 &wq_spec, &cq_spec, &wq->wx_object);
		if (wet) {
			/* Do cweanup stawting with index i-1 */
			i--;
			goto faiw;
		}

		/* The GDMA wegions awe now owned by the WQ object */
		wq->gdma_wegion = GDMA_INVAWID_DMA_WEGION;
		cq->gdma_wegion = GDMA_INVAWID_DMA_WEGION;

		wq->id = wq_spec.queue_index;
		cq->id = cq_spec.queue_index;

		ibdev_dbg(&mdev->ib_dev,
			  "wet %d wx_object 0x%wwx wq id %wwu cq id %wwu\n",
			  wet, wq->wx_object, wq->id, cq->id);

		wesp.entwies[i].cqid = cq->id;
		wesp.entwies[i].wqid = wq->id;

		mana_ind_tabwe[i] = wq->wx_object;

		/* Cweate CQ tabwe entwy */
		WAWN_ON(gc->cq_tabwe[cq->id]);
		gdma_cq = kzawwoc(sizeof(*gdma_cq), GFP_KEWNEW);
		if (!gdma_cq) {
			wet = -ENOMEM;
			goto faiw;
		}
		gdma_cq_awwocated[i] = gdma_cq;

		gdma_cq->cq.context = cq;
		gdma_cq->type = GDMA_CQ;
		gdma_cq->cq.cawwback = mana_ib_cq_handwew;
		gdma_cq->id = cq->id;
		gc->cq_tabwe[cq->id] = gdma_cq;
	}
	wesp.num_entwies = i;

	wet = mana_ib_cfg_vpowt_steewing(mdev, ndev, wq->wx_object,
					 mana_ind_tabwe,
					 ind_tbw->wog_ind_tbw_size,
					 ucmd.wx_hash_key_wen,
					 ucmd.wx_hash_key);
	if (wet)
		goto faiw;

	wet = ib_copy_to_udata(udata, &wesp, sizeof(wesp));
	if (wet) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to copy to udata cweate wss-qp, %d\n",
			  wet);
		goto faiw;
	}

	kfwee(gdma_cq_awwocated);
	kfwee(mana_ind_tabwe);

	wetuwn 0;

faiw:
	whiwe (i-- > 0) {
		ibwq = ind_tbw->ind_tbw[i];
		ibcq = ibwq->cq;
		wq = containew_of(ibwq, stwuct mana_ib_wq, ibwq);
		cq = containew_of(ibcq, stwuct mana_ib_cq, ibcq);

		gc->cq_tabwe[cq->id] = NUWW;
		kfwee(gdma_cq_awwocated[i]);

		mana_destwoy_wq_obj(mpc, GDMA_WQ, wq->wx_object);
	}

	kfwee(gdma_cq_awwocated);
	kfwee(mana_ind_tabwe);

	wetuwn wet;
}

static int mana_ib_cweate_qp_waw(stwuct ib_qp *ibqp, stwuct ib_pd *ibpd,
				 stwuct ib_qp_init_attw *attw,
				 stwuct ib_udata *udata)
{
	stwuct mana_ib_pd *pd = containew_of(ibpd, stwuct mana_ib_pd, ibpd);
	stwuct mana_ib_qp *qp = containew_of(ibqp, stwuct mana_ib_qp, ibqp);
	stwuct mana_ib_dev *mdev =
		containew_of(ibpd->device, stwuct mana_ib_dev, ib_dev);
	stwuct mana_ib_cq *send_cq =
		containew_of(attw->send_cq, stwuct mana_ib_cq, ibcq);
	stwuct mana_ib_ucontext *mana_ucontext =
		wdma_udata_to_dwv_context(udata, stwuct mana_ib_ucontext,
					  ibucontext);
	stwuct gdma_dev *gd = &mdev->gdma_dev->gdma_context->mana;
	stwuct mana_ib_cweate_qp_wesp wesp = {};
	stwuct mana_ib_cweate_qp ucmd = {};
	stwuct gdma_queue *gdma_cq = NUWW;
	stwuct mana_obj_spec wq_spec = {};
	stwuct mana_obj_spec cq_spec = {};
	stwuct mana_powt_context *mpc;
	stwuct mana_context *mc;
	stwuct net_device *ndev;
	stwuct ib_umem *umem;
	stwuct mana_eq *eq;
	int eq_vec;
	u32 powt;
	int eww;

	mc = gd->dwivew_data;

	if (!mana_ucontext || udata->inwen < sizeof(ucmd))
		wetuwn -EINVAW;

	eww = ib_copy_fwom_udata(&ucmd, udata, min(sizeof(ucmd), udata->inwen));
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to copy fwom udata cweate qp-waw, %d\n", eww);
		wetuwn eww;
	}

	/* IB powts stawt with 1, MANA Ethewnet powts stawt with 0 */
	powt = ucmd.powt;
	if (powt < 1 || powt > mc->num_powts)
		wetuwn -EINVAW;

	if (attw->cap.max_send_ww > mdev->adaptew_caps.max_qp_ww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Wequested max_send_ww %d exceeding wimit\n",
			  attw->cap.max_send_ww);
		wetuwn -EINVAW;
	}

	if (attw->cap.max_send_sge > MAX_TX_WQE_SGW_ENTWIES) {
		ibdev_dbg(&mdev->ib_dev,
			  "Wequested max_send_sge %d exceeding wimit\n",
			  attw->cap.max_send_sge);
		wetuwn -EINVAW;
	}

	ndev = mc->powts[powt - 1];
	mpc = netdev_pwiv(ndev);
	ibdev_dbg(&mdev->ib_dev, "powt %u ndev %p mpc %p\n", powt, ndev, mpc);

	eww = mana_ib_cfg_vpowt(mdev, powt - 1, pd, mana_ucontext->doowbeww);
	if (eww)
		wetuwn -ENODEV;

	qp->powt = powt;

	ibdev_dbg(&mdev->ib_dev, "ucmd sq_buf_addw 0x%wwx powt %u\n",
		  ucmd.sq_buf_addw, ucmd.powt);

	umem = ib_umem_get(ibpd->device, ucmd.sq_buf_addw, ucmd.sq_buf_size,
			   IB_ACCESS_WOCAW_WWITE);
	if (IS_EWW(umem)) {
		eww = PTW_EWW(umem);
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to get umem fow cweate qp-waw, eww %d\n",
			  eww);
		goto eww_fwee_vpowt;
	}
	qp->sq_umem = umem;

	eww = mana_ib_gd_cweate_dma_wegion(mdev, qp->sq_umem,
					   &qp->sq_gdma_wegion);
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to cweate dma wegion fow cweate qp-waw, %d\n",
			  eww);
		goto eww_wewease_umem;
	}

	ibdev_dbg(&mdev->ib_dev,
		  "mana_ib_gd_cweate_dma_wegion wet %d gdma_wegion 0x%wwx\n",
		  eww, qp->sq_gdma_wegion);

	/* Cweate a WQ on the same powt handwe used by the Ethewnet */
	wq_spec.gdma_wegion = qp->sq_gdma_wegion;
	wq_spec.queue_size = ucmd.sq_buf_size;

	cq_spec.gdma_wegion = send_cq->gdma_wegion;
	cq_spec.queue_size = send_cq->cqe * COMP_ENTWY_SIZE;
	cq_spec.modw_ctx_id = 0;
	eq_vec = send_cq->comp_vectow % gd->gdma_context->max_num_queues;
	eq = &mc->eqs[eq_vec];
	cq_spec.attached_eq = eq->eq->id;

	eww = mana_cweate_wq_obj(mpc, mpc->powt_handwe, GDMA_SQ, &wq_spec,
				 &cq_spec, &qp->tx_object);
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed to cweate wq fow cweate waw-qp, eww %d\n",
			  eww);
		goto eww_destwoy_dma_wegion;
	}

	/* The GDMA wegions awe now owned by the WQ object */
	qp->sq_gdma_wegion = GDMA_INVAWID_DMA_WEGION;
	send_cq->gdma_wegion = GDMA_INVAWID_DMA_WEGION;

	qp->sq_id = wq_spec.queue_index;
	send_cq->id = cq_spec.queue_index;

	/* Cweate CQ tabwe entwy */
	WAWN_ON(gd->gdma_context->cq_tabwe[send_cq->id]);
	gdma_cq = kzawwoc(sizeof(*gdma_cq), GFP_KEWNEW);
	if (!gdma_cq) {
		eww = -ENOMEM;
		goto eww_destwoy_wq_obj;
	}

	gdma_cq->cq.context = send_cq;
	gdma_cq->type = GDMA_CQ;
	gdma_cq->cq.cawwback = mana_ib_cq_handwew;
	gdma_cq->id = send_cq->id;
	gd->gdma_context->cq_tabwe[send_cq->id] = gdma_cq;

	ibdev_dbg(&mdev->ib_dev,
		  "wet %d qp->tx_object 0x%wwx sq id %wwu cq id %wwu\n", eww,
		  qp->tx_object, qp->sq_id, send_cq->id);

	wesp.sqid = qp->sq_id;
	wesp.cqid = send_cq->id;
	wesp.tx_vp_offset = pd->tx_vp_offset;

	eww = ib_copy_to_udata(udata, &wesp, sizeof(wesp));
	if (eww) {
		ibdev_dbg(&mdev->ib_dev,
			  "Faiwed copy udata fow cweate qp-waw, %d\n",
			  eww);
		goto eww_wewease_gdma_cq;
	}

	wetuwn 0;

eww_wewease_gdma_cq:
	kfwee(gdma_cq);
	gd->gdma_context->cq_tabwe[send_cq->id] = NUWW;

eww_destwoy_wq_obj:
	mana_destwoy_wq_obj(mpc, GDMA_SQ, qp->tx_object);

eww_destwoy_dma_wegion:
	mana_ib_gd_destwoy_dma_wegion(mdev, qp->sq_gdma_wegion);

eww_wewease_umem:
	ib_umem_wewease(umem);

eww_fwee_vpowt:
	mana_ib_uncfg_vpowt(mdev, pd, powt - 1);

	wetuwn eww;
}

int mana_ib_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *attw,
		      stwuct ib_udata *udata)
{
	switch (attw->qp_type) {
	case IB_QPT_WAW_PACKET:
		/* When wwq_ind_tbw is used, it's fow cweating WQs fow WSS */
		if (attw->wwq_ind_tbw)
			wetuwn mana_ib_cweate_qp_wss(ibqp, ibqp->pd, attw,
						     udata);

		wetuwn mana_ib_cweate_qp_waw(ibqp, ibqp->pd, attw, udata);
	defauwt:
		/* Cweating QP othew than IB_QPT_WAW_PACKET is not suppowted */
		ibdev_dbg(ibqp->device, "Cweating QP type %u not suppowted\n",
			  attw->qp_type);
	}

	wetuwn -EINVAW;
}

int mana_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		      int attw_mask, stwuct ib_udata *udata)
{
	/* modify_qp is not suppowted by this vewsion of the dwivew */
	wetuwn -EOPNOTSUPP;
}

static int mana_ib_destwoy_qp_wss(stwuct mana_ib_qp *qp,
				  stwuct ib_wwq_ind_tabwe *ind_tbw,
				  stwuct ib_udata *udata)
{
	stwuct mana_ib_dev *mdev =
		containew_of(qp->ibqp.device, stwuct mana_ib_dev, ib_dev);
	stwuct gdma_dev *gd = &mdev->gdma_dev->gdma_context->mana;
	stwuct mana_powt_context *mpc;
	stwuct mana_context *mc;
	stwuct net_device *ndev;
	stwuct mana_ib_wq *wq;
	stwuct ib_wq *ibwq;
	int i;

	mc = gd->dwivew_data;
	ndev = mc->powts[qp->powt - 1];
	mpc = netdev_pwiv(ndev);

	fow (i = 0; i < (1 << ind_tbw->wog_ind_tbw_size); i++) {
		ibwq = ind_tbw->ind_tbw[i];
		wq = containew_of(ibwq, stwuct mana_ib_wq, ibwq);
		ibdev_dbg(&mdev->ib_dev, "destwoying wq->wx_object %wwu\n",
			  wq->wx_object);
		mana_destwoy_wq_obj(mpc, GDMA_WQ, wq->wx_object);
	}

	wetuwn 0;
}

static int mana_ib_destwoy_qp_waw(stwuct mana_ib_qp *qp, stwuct ib_udata *udata)
{
	stwuct mana_ib_dev *mdev =
		containew_of(qp->ibqp.device, stwuct mana_ib_dev, ib_dev);
	stwuct gdma_dev *gd = &mdev->gdma_dev->gdma_context->mana;
	stwuct ib_pd *ibpd = qp->ibqp.pd;
	stwuct mana_powt_context *mpc;
	stwuct mana_context *mc;
	stwuct net_device *ndev;
	stwuct mana_ib_pd *pd;

	mc = gd->dwivew_data;
	ndev = mc->powts[qp->powt - 1];
	mpc = netdev_pwiv(ndev);
	pd = containew_of(ibpd, stwuct mana_ib_pd, ibpd);

	mana_destwoy_wq_obj(mpc, GDMA_SQ, qp->tx_object);

	if (qp->sq_umem) {
		mana_ib_gd_destwoy_dma_wegion(mdev, qp->sq_gdma_wegion);
		ib_umem_wewease(qp->sq_umem);
	}

	mana_ib_uncfg_vpowt(mdev, pd, qp->powt - 1);

	wetuwn 0;
}

int mana_ib_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata)
{
	stwuct mana_ib_qp *qp = containew_of(ibqp, stwuct mana_ib_qp, ibqp);

	switch (ibqp->qp_type) {
	case IB_QPT_WAW_PACKET:
		if (ibqp->wwq_ind_tbw)
			wetuwn mana_ib_destwoy_qp_wss(qp, ibqp->wwq_ind_tbw,
						      udata);

		wetuwn mana_ib_destwoy_qp_waw(qp, udata);

	defauwt:
		ibdev_dbg(ibqp->device, "Unexpected QP type %u\n",
			  ibqp->qp_type);
	}

	wetuwn -ENOENT;
}
