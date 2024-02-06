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

static int uvewbs_fwee_fwow_action(stwuct ib_uobject *uobject,
				   enum wdma_wemove_weason why,
				   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_fwow_action *action = uobject->object;

	if (atomic_wead(&action->usecnt))
		wetuwn -EBUSY;

	wetuwn action->device->ops.destwoy_fwow_action(action);
}

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_FWOW_ACTION_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_FWOW_ACTION_HANDWE,
			UVEWBS_OBJECT_FWOW_ACTION,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_FWOW_ACTION,
	UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_fwow_action),
	&UVEWBS_METHOD(UVEWBS_METHOD_FWOW_ACTION_DESTWOY));

const stwuct uapi_definition uvewbs_def_obj_fwow_action[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(
		UVEWBS_OBJECT_FWOW_ACTION,
		UAPI_DEF_OBJ_NEEDS_FN(destwoy_fwow_action)),
	{}
};
