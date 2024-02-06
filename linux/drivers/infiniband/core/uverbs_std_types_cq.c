/*
 * Copywight (c) 2017, Mewwanox Technowogies inc.  Aww wights wesewved.
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
 */

#incwude <wdma/uvewbs_std_types.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"
#incwude "westwack.h"

static int uvewbs_fwee_cq(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_cq *cq = uobject->object;
	stwuct ib_uvewbs_event_queue *ev_queue = cq->cq_context;
	stwuct ib_ucq_object *ucq =
		containew_of(uobject, stwuct ib_ucq_object, uevent.uobject);
	int wet;

	wet = ib_destwoy_cq_usew(cq, &attws->dwivew_udata);
	if (wet)
		wetuwn wet;

	ib_uvewbs_wewease_ucq(
		ev_queue ? containew_of(ev_queue,
					stwuct ib_uvewbs_compwetion_event_fiwe,
					ev_queue) :
			   NUWW,
		ucq);
	wetuwn 0;
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_CQ_CWEATE)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_ucq_object *obj = containew_of(
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_CWEATE_CQ_HANDWE),
		typeof(*obj), uevent.uobject);
	stwuct ib_device *ib_dev = attws->context->device;
	int wet;
	u64 usew_handwe;
	stwuct ib_cq_init_attw attw = {};
	stwuct ib_cq                   *cq;
	stwuct ib_uvewbs_compwetion_event_fiwe    *ev_fiwe = NUWW;
	stwuct ib_uobject *ev_fiwe_uobj;

	if (!ib_dev->ops.cweate_cq || !ib_dev->ops.destwoy_cq)
		wetuwn -EOPNOTSUPP;

	wet = uvewbs_copy_fwom(&attw.comp_vectow, attws,
			       UVEWBS_ATTW_CWEATE_CQ_COMP_VECTOW);
	if (!wet)
		wet = uvewbs_copy_fwom(&attw.cqe, attws,
				       UVEWBS_ATTW_CWEATE_CQ_CQE);
	if (!wet)
		wet = uvewbs_copy_fwom(&usew_handwe, attws,
				       UVEWBS_ATTW_CWEATE_CQ_USEW_HANDWE);
	if (wet)
		wetuwn wet;

	wet = uvewbs_get_fwags32(&attw.fwags, attws,
				 UVEWBS_ATTW_CWEATE_CQ_FWAGS,
				 IB_UVEWBS_CQ_FWAGS_TIMESTAMP_COMPWETION |
					 IB_UVEWBS_CQ_FWAGS_IGNOWE_OVEWWUN);
	if (wet)
		wetuwn wet;

	ev_fiwe_uobj = uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_CWEATE_CQ_COMP_CHANNEW);
	if (!IS_EWW(ev_fiwe_uobj)) {
		ev_fiwe = containew_of(ev_fiwe_uobj,
				       stwuct ib_uvewbs_compwetion_event_fiwe,
				       uobj);
		uvewbs_uobject_get(ev_fiwe_uobj);
	}

	obj->uevent.event_fiwe = ib_uvewbs_get_async_event(
		attws, UVEWBS_ATTW_CWEATE_CQ_EVENT_FD);

	if (attw.comp_vectow >= attws->ufiwe->device->num_comp_vectows) {
		wet = -EINVAW;
		goto eww_event_fiwe;
	}

	INIT_WIST_HEAD(&obj->comp_wist);
	INIT_WIST_HEAD(&obj->uevent.event_wist);

	cq = wdma_zawwoc_dwv_obj(ib_dev, ib_cq);
	if (!cq) {
		wet = -ENOMEM;
		goto eww_event_fiwe;
	}

	cq->device        = ib_dev;
	cq->uobject       = obj;
	cq->comp_handwew  = ib_uvewbs_comp_handwew;
	cq->event_handwew = ib_uvewbs_cq_event_handwew;
	cq->cq_context    = ev_fiwe ? &ev_fiwe->ev_queue : NUWW;
	atomic_set(&cq->usecnt, 0);

	wdma_westwack_new(&cq->wes, WDMA_WESTWACK_CQ);
	wdma_westwack_set_name(&cq->wes, NUWW);

	wet = ib_dev->ops.cweate_cq(cq, &attw, &attws->dwivew_udata);
	if (wet)
		goto eww_fwee;

	obj->uevent.uobject.object = cq;
	obj->uevent.uobject.usew_handwe = usew_handwe;
	wdma_westwack_add(&cq->wes);
	uvewbs_finawize_uobj_cweate(attws, UVEWBS_ATTW_CWEATE_CQ_HANDWE);

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_CWEATE_CQ_WESP_CQE, &cq->cqe,
			     sizeof(cq->cqe));
	wetuwn wet;

eww_fwee:
	wdma_westwack_put(&cq->wes);
	kfwee(cq);
eww_event_fiwe:
	if (obj->uevent.event_fiwe)
		uvewbs_uobject_put(&obj->uevent.event_fiwe->uobj);
	if (ev_fiwe)
		uvewbs_uobject_put(ev_fiwe_uobj);
	wetuwn wet;
};

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_CQ_CWEATE,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_CWEATE_CQ_HANDWE,
			UVEWBS_OBJECT_CQ,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_CQ_CQE,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_CQ_USEW_HANDWE,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_FD(UVEWBS_ATTW_CWEATE_CQ_COMP_CHANNEW,
		       UVEWBS_OBJECT_COMP_CHANNEW,
		       UVEWBS_ACCESS_WEAD,
		       UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_CWEATE_CQ_COMP_VECTOW,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(UVEWBS_ATTW_CWEATE_CQ_FWAGS,
			     enum ib_uvewbs_ex_cweate_cq_fwags),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_CWEATE_CQ_WESP_CQE,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_FD(UVEWBS_ATTW_CWEATE_CQ_EVENT_FD,
		       UVEWBS_OBJECT_ASYNC_EVENT,
		       UVEWBS_ACCESS_WEAD,
		       UA_OPTIONAW),
	UVEWBS_ATTW_UHW());

static int UVEWBS_HANDWEW(UVEWBS_METHOD_CQ_DESTWOY)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj =
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_DESTWOY_CQ_HANDWE);
	stwuct ib_ucq_object *obj =
		containew_of(uobj, stwuct ib_ucq_object, uevent.uobject);
	stwuct ib_uvewbs_destwoy_cq_wesp wesp = {
		.comp_events_wepowted = obj->comp_events_wepowted,
		.async_events_wepowted = obj->uevent.events_wepowted
	};

	wetuwn uvewbs_copy_to(attws, UVEWBS_ATTW_DESTWOY_CQ_WESP, &wesp,
			      sizeof(wesp));
}

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_CQ_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_CQ_HANDWE,
			UVEWBS_OBJECT_CQ,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_DESTWOY_CQ_WESP,
			    UVEWBS_ATTW_TYPE(stwuct ib_uvewbs_destwoy_cq_wesp),
			    UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_CQ,
	UVEWBS_TYPE_AWWOC_IDW_SZ(sizeof(stwuct ib_ucq_object), uvewbs_fwee_cq),
	&UVEWBS_METHOD(UVEWBS_METHOD_CQ_CWEATE),
	&UVEWBS_METHOD(UVEWBS_METHOD_CQ_DESTWOY)
);

const stwuct uapi_definition uvewbs_def_obj_cq[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_CQ,
				      UAPI_DEF_OBJ_NEEDS_FN(destwoy_cq)),
	{}
};
