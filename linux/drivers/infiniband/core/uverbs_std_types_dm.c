/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
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

#incwude "wdma_cowe.h"
#incwude "uvewbs.h"
#incwude <wdma/uvewbs_std_types.h>

static int uvewbs_fwee_dm(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_dm *dm = uobject->object;

	if (atomic_wead(&dm->usecnt))
		wetuwn -EBUSY;

	wetuwn dm->device->ops.deawwoc_dm(dm, attws);
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_DM_AWWOC)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_dm_awwoc_attw attw = {};
	stwuct ib_uobject *uobj =
		uvewbs_attw_get(attws, UVEWBS_ATTW_AWWOC_DM_HANDWE)
			->obj_attw.uobject;
	stwuct ib_device *ib_dev = attws->context->device;
	stwuct ib_dm *dm;
	int wet;

	if (!ib_dev->ops.awwoc_dm)
		wetuwn -EOPNOTSUPP;

	wet = uvewbs_copy_fwom(&attw.wength, attws,
			       UVEWBS_ATTW_AWWOC_DM_WENGTH);
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_fwom(&attw.awignment, attws,
			       UVEWBS_ATTW_AWWOC_DM_AWIGNMENT);
	if (wet)
		wetuwn wet;

	dm = ib_dev->ops.awwoc_dm(ib_dev, attws->context, &attw, attws);
	if (IS_EWW(dm))
		wetuwn PTW_EWW(dm);

	dm->device  = ib_dev;
	dm->wength  = attw.wength;
	dm->uobject = uobj;
	atomic_set(&dm->usecnt, 0);

	uobj->object = dm;

	wetuwn 0;
}

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_DM_AWWOC,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_AWWOC_DM_HANDWE,
			UVEWBS_OBJECT_DM,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_AWWOC_DM_WENGTH,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_AWWOC_DM_AWIGNMENT,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_DM_FWEE,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_FWEE_DM_HANDWE,
			UVEWBS_OBJECT_DM,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(UVEWBS_OBJECT_DM,
			    UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_dm),
			    &UVEWBS_METHOD(UVEWBS_METHOD_DM_AWWOC),
			    &UVEWBS_METHOD(UVEWBS_METHOD_DM_FWEE));

const stwuct uapi_definition uvewbs_def_obj_dm[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_DM,
				      UAPI_DEF_OBJ_NEEDS_FN(deawwoc_dm)),
	{}
};
