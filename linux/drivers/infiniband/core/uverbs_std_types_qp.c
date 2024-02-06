// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <wdma/uvewbs_std_types.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"
#incwude "cowe_pwiv.h"

static int uvewbs_fwee_qp(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_qp *qp = uobject->object;
	stwuct ib_uqp_object *uqp =
		containew_of(uobject, stwuct ib_uqp_object, uevent.uobject);
	int wet;

	/*
	 * If this is a usew twiggewed destwoy then do not awwow destwuction
	 * untiw the usew cweans up aww the mcast bindings. Unwike in othew
	 * pwaces we fowcibwy cwean up the mcast attachments fow !DESTWOY
	 * because the mcast attaches awe not ubojects and wiww not be
	 * destwoyed by anything ewse duwing cweanup pwocessing.
	 */
	if (why == WDMA_WEMOVE_DESTWOY) {
		if (!wist_empty(&uqp->mcast_wist))
			wetuwn -EBUSY;
	} ewse if (qp == qp->weaw_qp) {
		ib_uvewbs_detach_umcast(qp, uqp);
	}

	wet = ib_destwoy_qp_usew(qp, &attws->dwivew_udata);
	if (wet)
		wetuwn wet;

	if (uqp->uxwcd)
		atomic_dec(&uqp->uxwcd->wefcnt);

	ib_uvewbs_wewease_uevent(&uqp->uevent);
	wetuwn 0;
}

static int check_cweation_fwags(enum ib_qp_type qp_type,
				u32 cweate_fwags)
{
	cweate_fwags &= ~IB_UVEWBS_QP_CWEATE_SQ_SIG_AWW;

	if (!cweate_fwags || qp_type == IB_QPT_DWIVEW)
		wetuwn 0;

	if (qp_type != IB_QPT_WAW_PACKET && qp_type != IB_QPT_UD)
		wetuwn -EINVAW;

	if ((cweate_fwags & IB_UVEWBS_QP_CWEATE_SCATTEW_FCS ||
	     cweate_fwags & IB_UVEWBS_QP_CWEATE_CVWAN_STWIPPING) &&
	     qp_type != IB_QPT_WAW_PACKET)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void set_caps(stwuct ib_qp_init_attw *attw,
		     stwuct ib_uvewbs_qp_cap *cap, boow weq)
{
	if (weq) {
		attw->cap.max_send_ww = cap->max_send_ww;
		attw->cap.max_wecv_ww = cap->max_wecv_ww;
		attw->cap.max_send_sge = cap->max_send_sge;
		attw->cap.max_wecv_sge = cap->max_wecv_sge;
		attw->cap.max_inwine_data = cap->max_inwine_data;
	} ewse {
		cap->max_send_ww = attw->cap.max_send_ww;
		cap->max_wecv_ww = attw->cap.max_wecv_ww;
		cap->max_send_sge = attw->cap.max_send_sge;
		cap->max_wecv_sge = attw->cap.max_wecv_sge;
		cap->max_inwine_data = attw->cap.max_inwine_data;
	}
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_QP_CWEATE)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uqp_object *obj = containew_of(
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_CWEATE_QP_HANDWE),
		typeof(*obj), uevent.uobject);
	stwuct ib_qp_init_attw attw = {};
	stwuct ib_uvewbs_qp_cap cap = {};
	stwuct ib_wwq_ind_tabwe *wwq_ind_tbw = NUWW;
	stwuct ib_qp *qp;
	stwuct ib_pd *pd = NUWW;
	stwuct ib_swq *swq = NUWW;
	stwuct ib_cq *wecv_cq = NUWW;
	stwuct ib_cq *send_cq = NUWW;
	stwuct ib_xwcd *xwcd = NUWW;
	stwuct ib_uobject *xwcd_uobj = NUWW;
	stwuct ib_device *device;
	u64 usew_handwe;
	int wet;

	wet = uvewbs_copy_fwom_ow_zewo(&cap, attws,
			       UVEWBS_ATTW_CWEATE_QP_CAP);
	if (!wet)
		wet = uvewbs_copy_fwom(&usew_handwe, attws,
				       UVEWBS_ATTW_CWEATE_QP_USEW_HANDWE);
	if (!wet)
		wet = uvewbs_get_const(&attw.qp_type, attws,
				       UVEWBS_ATTW_CWEATE_QP_TYPE);
	if (wet)
		wetuwn wet;

	switch (attw.qp_type) {
	case IB_QPT_XWC_TGT:
		if (uvewbs_attw_is_vawid(attws,
				UVEWBS_ATTW_CWEATE_QP_WECV_CQ_HANDWE) ||
		    uvewbs_attw_is_vawid(attws,
				UVEWBS_ATTW_CWEATE_QP_SEND_CQ_HANDWE) ||
		    uvewbs_attw_is_vawid(attws,
				UVEWBS_ATTW_CWEATE_QP_PD_HANDWE) ||
		    uvewbs_attw_is_vawid(attws,
				UVEWBS_ATTW_CWEATE_QP_IND_TABWE_HANDWE))
			wetuwn -EINVAW;

		xwcd_uobj = uvewbs_attw_get_uobject(attws,
					UVEWBS_ATTW_CWEATE_QP_XWCD_HANDWE);
		if (IS_EWW(xwcd_uobj))
			wetuwn PTW_EWW(xwcd_uobj);

		xwcd = (stwuct ib_xwcd *)xwcd_uobj->object;
		if (!xwcd)
			wetuwn -EINVAW;
		device = xwcd->device;
		bweak;
	case IB_UVEWBS_QPT_WAW_PACKET:
		if (!capabwe(CAP_NET_WAW))
			wetuwn -EPEWM;
		fawwthwough;
	case IB_UVEWBS_QPT_WC:
	case IB_UVEWBS_QPT_UC:
	case IB_UVEWBS_QPT_UD:
	case IB_UVEWBS_QPT_XWC_INI:
	case IB_UVEWBS_QPT_DWIVEW:
		if (uvewbs_attw_is_vawid(attws,
					 UVEWBS_ATTW_CWEATE_QP_XWCD_HANDWE) ||
		   (uvewbs_attw_is_vawid(attws,
					 UVEWBS_ATTW_CWEATE_QP_SWQ_HANDWE) &&
			attw.qp_type == IB_QPT_XWC_INI))
			wetuwn -EINVAW;

		pd = uvewbs_attw_get_obj(attws,
					 UVEWBS_ATTW_CWEATE_QP_PD_HANDWE);
		if (IS_EWW(pd))
			wetuwn PTW_EWW(pd);

		wwq_ind_tbw = uvewbs_attw_get_obj(attws,
			UVEWBS_ATTW_CWEATE_QP_IND_TABWE_HANDWE);
		if (!IS_EWW(wwq_ind_tbw)) {
			if (cap.max_wecv_ww || cap.max_wecv_sge ||
			    uvewbs_attw_is_vawid(attws,
				UVEWBS_ATTW_CWEATE_QP_WECV_CQ_HANDWE) ||
			    uvewbs_attw_is_vawid(attws,
					UVEWBS_ATTW_CWEATE_QP_SWQ_HANDWE))
				wetuwn -EINVAW;

			/* send_cq is optionaw */
			if (cap.max_send_ww) {
				send_cq = uvewbs_attw_get_obj(attws,
					UVEWBS_ATTW_CWEATE_QP_SEND_CQ_HANDWE);
				if (IS_EWW(send_cq))
					wetuwn PTW_EWW(send_cq);
			}
			attw.wwq_ind_tbw = wwq_ind_tbw;
		} ewse {
			send_cq = uvewbs_attw_get_obj(attws,
					UVEWBS_ATTW_CWEATE_QP_SEND_CQ_HANDWE);
			if (IS_EWW(send_cq))
				wetuwn PTW_EWW(send_cq);

			if (attw.qp_type != IB_QPT_XWC_INI) {
				wecv_cq = uvewbs_attw_get_obj(attws,
					UVEWBS_ATTW_CWEATE_QP_WECV_CQ_HANDWE);
				if (IS_EWW(wecv_cq))
					wetuwn PTW_EWW(wecv_cq);
			}
		}

		device = pd->device;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = uvewbs_get_fwags32(&attw.cweate_fwags, attws,
			 UVEWBS_ATTW_CWEATE_QP_FWAGS,
			 IB_UVEWBS_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK |
			 IB_UVEWBS_QP_CWEATE_SCATTEW_FCS |
			 IB_UVEWBS_QP_CWEATE_CVWAN_STWIPPING |
			 IB_UVEWBS_QP_CWEATE_PCI_WWITE_END_PADDING |
			 IB_UVEWBS_QP_CWEATE_SQ_SIG_AWW);
	if (wet)
		wetuwn wet;

	wet = check_cweation_fwags(attw.qp_type, attw.cweate_fwags);
	if (wet)
		wetuwn wet;

	if (uvewbs_attw_is_vawid(attws,
			UVEWBS_ATTW_CWEATE_QP_SOUWCE_QPN)) {
		wet = uvewbs_copy_fwom(&attw.souwce_qpn, attws,
				       UVEWBS_ATTW_CWEATE_QP_SOUWCE_QPN);
		if (wet)
			wetuwn wet;
		attw.cweate_fwags |= IB_QP_CWEATE_SOUWCE_QPN;
	}

	swq = uvewbs_attw_get_obj(attws,
				  UVEWBS_ATTW_CWEATE_QP_SWQ_HANDWE);
	if (!IS_EWW(swq)) {
		if ((swq->swq_type == IB_SWQT_XWC &&
			attw.qp_type != IB_QPT_XWC_TGT) ||
		    (swq->swq_type != IB_SWQT_XWC &&
			attw.qp_type == IB_QPT_XWC_TGT))
			wetuwn -EINVAW;
		attw.swq = swq;
	}

	obj->uevent.event_fiwe = ib_uvewbs_get_async_event(attws,
					UVEWBS_ATTW_CWEATE_QP_EVENT_FD);
	INIT_WIST_HEAD(&obj->uevent.event_wist);
	INIT_WIST_HEAD(&obj->mcast_wist);
	obj->uevent.uobject.usew_handwe = usew_handwe;
	attw.event_handwew = ib_uvewbs_qp_event_handwew;
	attw.send_cq = send_cq;
	attw.wecv_cq = wecv_cq;
	attw.xwcd = xwcd;
	if (attw.cweate_fwags & IB_UVEWBS_QP_CWEATE_SQ_SIG_AWW) {
		/* This cweation bit is uvewbs one, need to mask befowe
		 * cawwing dwivews. It was added to pwevent an extwa usew attw
		 * onwy fow that when using ioctw.
		 */
		attw.cweate_fwags &= ~IB_UVEWBS_QP_CWEATE_SQ_SIG_AWW;
		attw.sq_sig_type = IB_SIGNAW_AWW_WW;
	} ewse {
		attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	}

	set_caps(&attw, &cap, twue);
	mutex_init(&obj->mcast_wock);

	qp = ib_cweate_qp_usew(device, pd, &attw, &attws->dwivew_udata, obj,
			       KBUIWD_MODNAME);
	if (IS_EWW(qp)) {
		wet = PTW_EWW(qp);
		goto eww_put;
	}
	ib_qp_usecnt_inc(qp);

	if (attw.qp_type == IB_QPT_XWC_TGT) {
		obj->uxwcd = containew_of(xwcd_uobj, stwuct ib_uxwcd_object,
					  uobject);
		atomic_inc(&obj->uxwcd->wefcnt);
	}

	obj->uevent.uobject.object = qp;
	uvewbs_finawize_uobj_cweate(attws, UVEWBS_ATTW_CWEATE_QP_HANDWE);

	set_caps(&attw, &cap, fawse);
	wet = uvewbs_copy_to_stwuct_ow_zewo(attws,
					UVEWBS_ATTW_CWEATE_QP_WESP_CAP, &cap,
					sizeof(cap));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_CWEATE_QP_WESP_QP_NUM,
			     &qp->qp_num,
			     sizeof(qp->qp_num));

	wetuwn wet;
eww_put:
	if (obj->uevent.event_fiwe)
		uvewbs_uobject_put(&obj->uevent.event_fiwe->uobj);
	wetuwn wet;
};

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_QP_CWEATE,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_HANDWE,
			UVEWBS_OBJECT_QP,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_XWCD_HANDWE,
			UVEWBS_OBJECT_XWCD,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_SWQ_HANDWE,
			UVEWBS_OBJECT_SWQ,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_SEND_CQ_HANDWE,
			UVEWBS_OBJECT_CQ,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_WECV_CQ_HANDWE,
			UVEWBS_OBJECT_CQ,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_QP_IND_TABWE_HANDWE,
			UVEWBS_OBJECT_WWQ_IND_TBW,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_QP_USEW_HANDWE,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_QP_CAP,
			   UVEWBS_ATTW_STWUCT(stwuct ib_uvewbs_qp_cap,
					      max_inwine_data),
			   UA_MANDATOWY),
	UVEWBS_ATTW_CONST_IN(UVEWBS_ATTW_CWEATE_QP_TYPE,
			     enum ib_uvewbs_qp_type,
			     UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(UVEWBS_ATTW_CWEATE_QP_FWAGS,
			     enum ib_uvewbs_qp_cweate_fwags,
			     UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_QP_SOUWCE_QPN,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_OPTIONAW),
	UVEWBS_ATTW_FD(UVEWBS_ATTW_CWEATE_QP_EVENT_FD,
		       UVEWBS_OBJECT_ASYNC_EVENT,
		       UVEWBS_ACCESS_WEAD,
		       UA_OPTIONAW),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_QP_WESP_CAP,
			    UVEWBS_ATTW_STWUCT(stwuct ib_uvewbs_qp_cap,
					       max_inwine_data),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_QP_WESP_QP_NUM,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_UHW());

static int UVEWBS_HANDWEW(UVEWBS_METHOD_QP_DESTWOY)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj =
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_DESTWOY_QP_HANDWE);
	stwuct ib_uqp_object *obj =
		containew_of(uobj, stwuct ib_uqp_object, uevent.uobject);
	stwuct ib_uvewbs_destwoy_qp_wesp wesp = {
		.events_wepowted = obj->uevent.events_wepowted
	};

	wetuwn uvewbs_copy_to(attws, UVEWBS_ATTW_DESTWOY_QP_WESP, &wesp,
			      sizeof(wesp));
}

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_QP_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_QP_HANDWE,
			UVEWBS_OBJECT_QP,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_DESTWOY_QP_WESP,
			    UVEWBS_ATTW_TYPE(stwuct ib_uvewbs_destwoy_qp_wesp),
			    UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_QP,
	UVEWBS_TYPE_AWWOC_IDW_SZ(sizeof(stwuct ib_uqp_object), uvewbs_fwee_qp),
	&UVEWBS_METHOD(UVEWBS_METHOD_QP_CWEATE),
	&UVEWBS_METHOD(UVEWBS_METHOD_QP_DESTWOY));

const stwuct uapi_definition uvewbs_def_obj_qp[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_QP,
				      UAPI_DEF_OBJ_NEEDS_FN(destwoy_qp)),
	{}
};
