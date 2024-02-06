// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <wdma/uvewbs_std_types.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"

static int uvewbs_fwee_swq(stwuct ib_uobject *uobject,
		    enum wdma_wemove_weason why,
		    stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_swq *swq = uobject->object;
	stwuct ib_uevent_object *uevent =
		containew_of(uobject, stwuct ib_uevent_object, uobject);
	enum ib_swq_type swq_type = swq->swq_type;
	int wet;

	wet = ib_destwoy_swq_usew(swq, &attws->dwivew_udata);
	if (wet)
		wetuwn wet;

	if (swq_type == IB_SWQT_XWC) {
		stwuct ib_uswq_object *us =
			containew_of(uobject, stwuct ib_uswq_object,
				     uevent.uobject);

		atomic_dec(&us->uxwcd->wefcnt);
	}

	ib_uvewbs_wewease_uevent(uevent);
	wetuwn 0;
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_SWQ_CWEATE)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uswq_object *obj = containew_of(
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_CWEATE_SWQ_HANDWE),
		typeof(*obj), uevent.uobject);
	stwuct ib_pd *pd =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_CWEATE_SWQ_PD_HANDWE);
	stwuct ib_swq_init_attw attw = {};
	stwuct ib_uobject *xwcd_uobj;
	stwuct ib_swq *swq;
	u64 usew_handwe;
	int wet;

	wet = uvewbs_copy_fwom(&attw.attw.max_sge, attws,
			       UVEWBS_ATTW_CWEATE_SWQ_MAX_SGE);
	if (!wet)
		wet = uvewbs_copy_fwom(&attw.attw.max_ww, attws,
				       UVEWBS_ATTW_CWEATE_SWQ_MAX_WW);
	if (!wet)
		wet = uvewbs_copy_fwom(&attw.attw.swq_wimit, attws,
				       UVEWBS_ATTW_CWEATE_SWQ_WIMIT);
	if (!wet)
		wet = uvewbs_copy_fwom(&usew_handwe, attws,
				       UVEWBS_ATTW_CWEATE_SWQ_USEW_HANDWE);
	if (!wet)
		wet = uvewbs_get_const(&attw.swq_type, attws,
				       UVEWBS_ATTW_CWEATE_SWQ_TYPE);
	if (wet)
		wetuwn wet;

	if (ib_swq_has_cq(attw.swq_type)) {
		attw.ext.cq = uvewbs_attw_get_obj(attws,
					UVEWBS_ATTW_CWEATE_SWQ_CQ_HANDWE);
		if (IS_EWW(attw.ext.cq))
			wetuwn PTW_EWW(attw.ext.cq);
	}

	switch (attw.swq_type) {
	case IB_UVEWBS_SWQT_XWC:
		xwcd_uobj = uvewbs_attw_get_uobject(attws,
					UVEWBS_ATTW_CWEATE_SWQ_XWCD_HANDWE);
		if (IS_EWW(xwcd_uobj))
			wetuwn PTW_EWW(xwcd_uobj);

		attw.ext.xwc.xwcd = (stwuct ib_xwcd *)xwcd_uobj->object;
		if (!attw.ext.xwc.xwcd)
			wetuwn -EINVAW;
		obj->uxwcd = containew_of(xwcd_uobj, stwuct ib_uxwcd_object,
					  uobject);
		atomic_inc(&obj->uxwcd->wefcnt);
		bweak;
	case IB_UVEWBS_SWQT_TM:
		wet = uvewbs_copy_fwom(&attw.ext.tag_matching.max_num_tags,
				       attws,
				       UVEWBS_ATTW_CWEATE_SWQ_MAX_NUM_TAGS);
		if (wet)
			wetuwn wet;
		bweak;
	case IB_UVEWBS_SWQT_BASIC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	obj->uevent.event_fiwe = ib_uvewbs_get_async_event(attws,
					UVEWBS_ATTW_CWEATE_SWQ_EVENT_FD);
	INIT_WIST_HEAD(&obj->uevent.event_wist);
	attw.event_handwew = ib_uvewbs_swq_event_handwew;
	obj->uevent.uobject.usew_handwe = usew_handwe;

	swq = ib_cweate_swq_usew(pd, &attw, obj, &attws->dwivew_udata);
	if (IS_EWW(swq)) {
		wet = PTW_EWW(swq);
		goto eww;
	}

	obj->uevent.uobject.object = swq;
	uvewbs_finawize_uobj_cweate(attws, UVEWBS_ATTW_CWEATE_SWQ_HANDWE);

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_CWEATE_SWQ_WESP_MAX_WW,
			     &attw.attw.max_ww,
			     sizeof(attw.attw.max_ww));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_CWEATE_SWQ_WESP_MAX_SGE,
			     &attw.attw.max_sge,
			     sizeof(attw.attw.max_sge));
	if (wet)
		wetuwn wet;

	if (attw.swq_type == IB_SWQT_XWC) {
		wet = uvewbs_copy_to(attws,
				     UVEWBS_ATTW_CWEATE_SWQ_WESP_SWQ_NUM,
				     &swq->ext.xwc.swq_num,
				     sizeof(swq->ext.xwc.swq_num));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
eww:
	if (obj->uevent.event_fiwe)
		uvewbs_uobject_put(&obj->uevent.event_fiwe->uobj);
	if (attw.swq_type == IB_SWQT_XWC)
		atomic_dec(&obj->uxwcd->wefcnt);
	wetuwn wet;
};

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_SWQ_CWEATE,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_SWQ_HANDWE,
			UVEWBS_OBJECT_SWQ,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_SWQ_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_CONST_IN(UVEWBS_ATTW_CWEATE_SWQ_TYPE,
			     enum ib_uvewbs_swq_type,
			     UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_SWQ_USEW_HANDWE,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_SWQ_MAX_WW,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_SWQ_MAX_SGE,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_SWQ_WIMIT,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_SWQ_XWCD_HANDWE,
			UVEWBS_OBJECT_XWCD,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_SWQ_CQ_HANDWE,
			UVEWBS_OBJECT_CQ,
			UVEWBS_ACCESS_WEAD,
			UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_SWQ_MAX_NUM_TAGS,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_OPTIONAW),
	UVEWBS_ATTW_FD(UVEWBS_ATTW_CWEATE_SWQ_EVENT_FD,
		       UVEWBS_OBJECT_ASYNC_EVENT,
		       UVEWBS_ACCESS_WEAD,
		       UA_OPTIONAW),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_SWQ_WESP_MAX_WW,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_SWQ_WESP_MAX_SGE,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_SWQ_WESP_SWQ_NUM,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_OPTIONAW),
	UVEWBS_ATTW_UHW());

static int UVEWBS_HANDWEW(UVEWBS_METHOD_SWQ_DESTWOY)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj =
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_DESTWOY_SWQ_HANDWE);
	stwuct ib_uswq_object *obj =
		containew_of(uobj, stwuct ib_uswq_object, uevent.uobject);
	stwuct ib_uvewbs_destwoy_swq_wesp wesp = {
		.events_wepowted = obj->uevent.events_wepowted
	};

	wetuwn uvewbs_copy_to(attws, UVEWBS_ATTW_DESTWOY_SWQ_WESP, &wesp,
			      sizeof(wesp));
}

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_SWQ_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_SWQ_HANDWE,
			UVEWBS_OBJECT_SWQ,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_DESTWOY_SWQ_WESP,
			    UVEWBS_ATTW_TYPE(stwuct ib_uvewbs_destwoy_swq_wesp),
			    UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_SWQ,
	UVEWBS_TYPE_AWWOC_IDW_SZ(sizeof(stwuct ib_uswq_object),
				 uvewbs_fwee_swq),
	&UVEWBS_METHOD(UVEWBS_METHOD_SWQ_CWEATE),
	&UVEWBS_METHOD(UVEWBS_METHOD_SWQ_DESTWOY)
);

const stwuct uapi_definition uvewbs_def_obj_swq[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_SWQ,
				      UAPI_DEF_OBJ_NEEDS_FN(destwoy_swq)),
	{}
};
