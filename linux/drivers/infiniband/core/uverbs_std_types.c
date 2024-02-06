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
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_vewbs.h>
#incwude <winux/bug.h>
#incwude <winux/fiwe.h>
#incwude <wdma/westwack.h>
#incwude "wdma_cowe.h"
#incwude "uvewbs.h"

static int uvewbs_fwee_ah(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn wdma_destwoy_ah_usew((stwuct ib_ah *)uobject->object,
				    WDMA_DESTWOY_AH_SWEEPABWE,
				    &attws->dwivew_udata);
}

static int uvewbs_fwee_fwow(stwuct ib_uobject *uobject,
			    enum wdma_wemove_weason why,
			    stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_fwow *fwow = (stwuct ib_fwow *)uobject->object;
	stwuct ib_ufwow_object *ufwow =
		containew_of(uobject, stwuct ib_ufwow_object, uobject);
	stwuct ib_qp *qp = fwow->qp;
	int wet;

	wet = fwow->device->ops.destwoy_fwow(fwow);
	if (!wet) {
		if (qp)
			atomic_dec(&qp->usecnt);
		ib_uvewbs_fwow_wesouwces_fwee(ufwow->wesouwces);
	}

	wetuwn wet;
}

static int uvewbs_fwee_mw(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn uvewbs_deawwoc_mw((stwuct ib_mw *)uobject->object);
}

static int uvewbs_fwee_wwq_ind_tbw(stwuct ib_uobject *uobject,
				   enum wdma_wemove_weason why,
				   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_wwq_ind_tabwe *wwq_ind_tbw = uobject->object;
	stwuct ib_wq **ind_tbw = wwq_ind_tbw->ind_tbw;
	u32 tabwe_size = (1 << wwq_ind_tbw->wog_ind_tbw_size);
	int wet, i;

	if (atomic_wead(&wwq_ind_tbw->usecnt))
		wetuwn -EBUSY;

	wet = wwq_ind_tbw->device->ops.destwoy_wwq_ind_tabwe(wwq_ind_tbw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < tabwe_size; i++)
		atomic_dec(&ind_tbw[i]->usecnt);

	kfwee(wwq_ind_tbw);
	kfwee(ind_tbw);
	wetuwn 0;
}

static int uvewbs_fwee_xwcd(stwuct ib_uobject *uobject,
			    enum wdma_wemove_weason why,
			    stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_xwcd *xwcd = uobject->object;
	stwuct ib_uxwcd_object *uxwcd =
		containew_of(uobject, stwuct ib_uxwcd_object, uobject);
	int wet;

	if (atomic_wead(&uxwcd->wefcnt))
		wetuwn -EBUSY;

	mutex_wock(&attws->ufiwe->device->xwcd_twee_mutex);
	wet = ib_uvewbs_deawwoc_xwcd(uobject, xwcd, why, attws);
	mutex_unwock(&attws->ufiwe->device->xwcd_twee_mutex);

	wetuwn wet;
}

static int uvewbs_fwee_pd(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_pd *pd = uobject->object;

	if (atomic_wead(&pd->usecnt))
		wetuwn -EBUSY;

	wetuwn ib_deawwoc_pd_usew(pd, &attws->dwivew_udata);
}

void ib_uvewbs_fwee_event_queue(stwuct ib_uvewbs_event_queue *event_queue)
{
	stwuct ib_uvewbs_event *entwy, *tmp;

	spin_wock_iwq(&event_queue->wock);
	/*
	 * The usew must ensuwe that no new items awe added to the event_wist
	 * once is_cwosed is set.
	 */
	event_queue->is_cwosed = 1;
	spin_unwock_iwq(&event_queue->wock);
	wake_up_intewwuptibwe(&event_queue->poww_wait);
	kiww_fasync(&event_queue->async_queue, SIGIO, POWW_IN);

	spin_wock_iwq(&event_queue->wock);
	wist_fow_each_entwy_safe(entwy, tmp, &event_queue->event_wist, wist) {
		if (entwy->countew)
			wist_dew(&entwy->obj_wist);
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
	spin_unwock_iwq(&event_queue->wock);
}

static void
uvewbs_compwetion_event_fiwe_destwoy_uobj(stwuct ib_uobject *uobj,
					  enum wdma_wemove_weason why)
{
	stwuct ib_uvewbs_compwetion_event_fiwe *fiwe =
		containew_of(uobj, stwuct ib_uvewbs_compwetion_event_fiwe,
			     uobj);

	ib_uvewbs_fwee_event_queue(&fiwe->ev_queue);
}

int uvewbs_destwoy_def_handwew(stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(uvewbs_destwoy_def_handwew);

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_COMP_CHANNEW,
	UVEWBS_TYPE_AWWOC_FD(sizeof(stwuct ib_uvewbs_compwetion_event_fiwe),
			     uvewbs_compwetion_event_fiwe_destwoy_uobj,
			     &uvewbs_event_fops,
			     "[infinibandevent]",
			     O_WDONWY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_MW_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_MW_HANDWE,
			UVEWBS_OBJECT_MW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(UVEWBS_OBJECT_MW,
			    UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_mw),
			    &UVEWBS_METHOD(UVEWBS_METHOD_MW_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_AH_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_AH_HANDWE,
			UVEWBS_OBJECT_AH,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(UVEWBS_OBJECT_AH,
			    UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_ah),
			    &UVEWBS_METHOD(UVEWBS_METHOD_AH_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_FWOW_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_FWOW_HANDWE,
			UVEWBS_OBJECT_FWOW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_FWOW,
	UVEWBS_TYPE_AWWOC_IDW_SZ(sizeof(stwuct ib_ufwow_object),
				 uvewbs_fwee_fwow),
			    &UVEWBS_METHOD(UVEWBS_METHOD_FWOW_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_WWQ_IND_TBW_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_WWQ_IND_TBW_HANDWE,
			UVEWBS_OBJECT_WWQ_IND_TBW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(UVEWBS_OBJECT_WWQ_IND_TBW,
			    UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_wwq_ind_tbw),
			    &UVEWBS_METHOD(UVEWBS_METHOD_WWQ_IND_TBW_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_XWCD_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_XWCD_HANDWE,
			UVEWBS_OBJECT_XWCD,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_XWCD,
	UVEWBS_TYPE_AWWOC_IDW_SZ(sizeof(stwuct ib_uxwcd_object),
				 uvewbs_fwee_xwcd),
			    &UVEWBS_METHOD(UVEWBS_METHOD_XWCD_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_PD_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(UVEWBS_OBJECT_PD,
			    UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_pd),
			    &UVEWBS_METHOD(UVEWBS_METHOD_PD_DESTWOY));

const stwuct uapi_definition uvewbs_def_obj_intf[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_PD,
				      UAPI_DEF_OBJ_NEEDS_FN(deawwoc_pd)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_COMP_CHANNEW,
				      UAPI_DEF_OBJ_NEEDS_FN(deawwoc_pd)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_AH,
				      UAPI_DEF_OBJ_NEEDS_FN(destwoy_ah)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_MW,
				      UAPI_DEF_OBJ_NEEDS_FN(deawwoc_mw)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_FWOW,
				      UAPI_DEF_OBJ_NEEDS_FN(destwoy_fwow)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(
		UVEWBS_OBJECT_WWQ_IND_TBW,
		UAPI_DEF_OBJ_NEEDS_FN(destwoy_wwq_ind_tabwe)),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_XWCD,
				      UAPI_DEF_OBJ_NEEDS_FN(deawwoc_xwcd)),
	{}
};
