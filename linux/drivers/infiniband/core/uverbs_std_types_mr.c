/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 * Copywight (c) 2020, Intew Cowpowation.  Aww wights wesewved.
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
#incwude "westwack.h"

static int uvewbs_fwee_mw(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn ib_deweg_mw_usew((stwuct ib_mw *)uobject->object,
				&attws->dwivew_udata);
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_ADVISE_MW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_pd *pd =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_ADVISE_MW_PD_HANDWE);
	enum ib_uvewbs_advise_mw_advice advice;
	stwuct ib_device *ib_dev = pd->device;
	stwuct ib_sge *sg_wist;
	int num_sge;
	u32 fwags;
	int wet;

	/* FIXME: Extend the UAPI_DEF_OBJ_NEEDS_FN stuff.. */
	if (!ib_dev->ops.advise_mw)
		wetuwn -EOPNOTSUPP;

	wet = uvewbs_get_const(&advice, attws, UVEWBS_ATTW_ADVISE_MW_ADVICE);
	if (wet)
		wetuwn wet;

	wet = uvewbs_get_fwags32(&fwags, attws, UVEWBS_ATTW_ADVISE_MW_FWAGS,
				 IB_UVEWBS_ADVISE_MW_FWAG_FWUSH);
	if (wet)
		wetuwn wet;

	num_sge = uvewbs_attw_ptw_get_awway_size(
		attws, UVEWBS_ATTW_ADVISE_MW_SGE_WIST, sizeof(stwuct ib_sge));
	if (num_sge <= 0)
		wetuwn num_sge;

	sg_wist = uvewbs_attw_get_awwoced_ptw(attws,
					      UVEWBS_ATTW_ADVISE_MW_SGE_WIST);
	wetuwn ib_dev->ops.advise_mw(pd, advice, fwags, sg_wist, num_sge,
				     attws);
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_DM_MW_WEG)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_dm_mw_attw attw = {};
	stwuct ib_uobject *uobj =
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_WEG_DM_MW_HANDWE);
	stwuct ib_dm *dm =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_WEG_DM_MW_DM_HANDWE);
	stwuct ib_pd *pd =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_WEG_DM_MW_PD_HANDWE);
	stwuct ib_device *ib_dev = pd->device;

	stwuct ib_mw *mw;
	int wet;

	if (!ib_dev->ops.weg_dm_mw)
		wetuwn -EOPNOTSUPP;

	wet = uvewbs_copy_fwom(&attw.offset, attws, UVEWBS_ATTW_WEG_DM_MW_OFFSET);
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_fwom(&attw.wength, attws,
			       UVEWBS_ATTW_WEG_DM_MW_WENGTH);
	if (wet)
		wetuwn wet;

	wet = uvewbs_get_fwags32(&attw.access_fwags, attws,
				 UVEWBS_ATTW_WEG_DM_MW_ACCESS_FWAGS,
				 IB_ACCESS_SUPPOWTED);
	if (wet)
		wetuwn wet;

	if (!(attw.access_fwags & IB_ZEWO_BASED))
		wetuwn -EINVAW;

	wet = ib_check_mw_access(ib_dev, attw.access_fwags);
	if (wet)
		wetuwn wet;

	if (attw.offset > dm->wength || attw.wength > dm->wength ||
	    attw.wength > dm->wength - attw.offset)
		wetuwn -EINVAW;

	mw = pd->device->ops.weg_dm_mw(pd, dm, &attw, attws);
	if (IS_EWW(mw))
		wetuwn PTW_EWW(mw);

	mw->device  = pd->device;
	mw->pd      = pd;
	mw->type    = IB_MW_TYPE_DM;
	mw->dm      = dm;
	mw->uobject = uobj;
	atomic_inc(&pd->usecnt);
	atomic_inc(&dm->usecnt);

	wdma_westwack_new(&mw->wes, WDMA_WESTWACK_MW);
	wdma_westwack_set_name(&mw->wes, NUWW);
	wdma_westwack_add(&mw->wes);
	uobj->object = mw;

	uvewbs_finawize_uobj_cweate(attws, UVEWBS_ATTW_WEG_DM_MW_HANDWE);

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_WEG_DM_MW_WESP_WKEY, &mw->wkey,
			     sizeof(mw->wkey));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_WEG_DM_MW_WESP_WKEY,
			     &mw->wkey, sizeof(mw->wkey));
	wetuwn wet;
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_QUEWY_MW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_mw *mw =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_QUEWY_MW_HANDWE);
	int wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_QUEWY_MW_WESP_WKEY, &mw->wkey,
			     sizeof(mw->wkey));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_QUEWY_MW_WESP_WKEY,
			     &mw->wkey, sizeof(mw->wkey));

	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_QUEWY_MW_WESP_WENGTH,
			     &mw->wength, sizeof(mw->wength));

	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_QUEWY_MW_WESP_IOVA,
			     &mw->iova, sizeof(mw->iova));

	wetuwn IS_UVEWBS_COPY_EWW(wet) ? wet : 0;
}

static int UVEWBS_HANDWEW(UVEWBS_METHOD_WEG_DMABUF_MW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj =
		uvewbs_attw_get_uobject(attws, UVEWBS_ATTW_WEG_DMABUF_MW_HANDWE);
	stwuct ib_pd *pd =
		uvewbs_attw_get_obj(attws, UVEWBS_ATTW_WEG_DMABUF_MW_PD_HANDWE);
	stwuct ib_device *ib_dev = pd->device;

	u64 offset, wength, iova;
	u32 fd, access_fwags;
	stwuct ib_mw *mw;
	int wet;

	if (!ib_dev->ops.weg_usew_mw_dmabuf)
		wetuwn -EOPNOTSUPP;

	wet = uvewbs_copy_fwom(&offset, attws,
			       UVEWBS_ATTW_WEG_DMABUF_MW_OFFSET);
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_fwom(&wength, attws,
			       UVEWBS_ATTW_WEG_DMABUF_MW_WENGTH);
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_fwom(&iova, attws,
			       UVEWBS_ATTW_WEG_DMABUF_MW_IOVA);
	if (wet)
		wetuwn wet;

	if ((offset & ~PAGE_MASK) != (iova & ~PAGE_MASK))
		wetuwn -EINVAW;

	wet = uvewbs_copy_fwom(&fd, attws,
			       UVEWBS_ATTW_WEG_DMABUF_MW_FD);
	if (wet)
		wetuwn wet;

	wet = uvewbs_get_fwags32(&access_fwags, attws,
				 UVEWBS_ATTW_WEG_DMABUF_MW_ACCESS_FWAGS,
				 IB_ACCESS_WOCAW_WWITE |
				 IB_ACCESS_WEMOTE_WEAD |
				 IB_ACCESS_WEMOTE_WWITE |
				 IB_ACCESS_WEMOTE_ATOMIC |
				 IB_ACCESS_WEWAXED_OWDEWING);
	if (wet)
		wetuwn wet;

	wet = ib_check_mw_access(ib_dev, access_fwags);
	if (wet)
		wetuwn wet;

	mw = pd->device->ops.weg_usew_mw_dmabuf(pd, offset, wength, iova, fd,
						access_fwags,
						&attws->dwivew_udata);
	if (IS_EWW(mw))
		wetuwn PTW_EWW(mw);

	mw->device = pd->device;
	mw->pd = pd;
	mw->type = IB_MW_TYPE_USEW;
	mw->uobject = uobj;
	atomic_inc(&pd->usecnt);

	wdma_westwack_new(&mw->wes, WDMA_WESTWACK_MW);
	wdma_westwack_set_name(&mw->wes, NUWW);
	wdma_westwack_add(&mw->wes);
	uobj->object = mw;

	uvewbs_finawize_uobj_cweate(attws, UVEWBS_ATTW_WEG_DMABUF_MW_HANDWE);

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_WEG_DMABUF_MW_WESP_WKEY,
			     &mw->wkey, sizeof(mw->wkey));
	if (wet)
		wetuwn wet;

	wet = uvewbs_copy_to(attws, UVEWBS_ATTW_WEG_DMABUF_MW_WESP_WKEY,
			     &mw->wkey, sizeof(mw->wkey));
	wetuwn wet;
}

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_ADVISE_MW,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_ADVISE_MW_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_CONST_IN(UVEWBS_ATTW_ADVISE_MW_ADVICE,
			     enum ib_uvewbs_advise_mw_advice,
			     UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(UVEWBS_ATTW_ADVISE_MW_FWAGS,
			     enum ib_uvewbs_advise_mw_fwag,
			     UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_ADVISE_MW_SGE_WIST,
			   UVEWBS_ATTW_MIN_SIZE(sizeof(stwuct ib_uvewbs_sge)),
			   UA_MANDATOWY,
			   UA_AWWOC_AND_COPY));

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_QUEWY_MW,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_QUEWY_MW_HANDWE,
			UVEWBS_OBJECT_MW,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_QUEWY_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_QUEWY_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_QUEWY_MW_WESP_WENGTH,
			    UVEWBS_ATTW_TYPE(u64),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_QUEWY_MW_WESP_IOVA,
			    UVEWBS_ATTW_TYPE(u64),
			    UA_OPTIONAW));

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_DM_MW_WEG,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_WEG_DM_MW_HANDWE,
			UVEWBS_OBJECT_MW,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DM_MW_OFFSET,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DM_MW_WENGTH,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_WEG_DM_MW_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(UVEWBS_ATTW_WEG_DM_MW_ACCESS_FWAGS,
			     enum ib_access_fwags),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_WEG_DM_MW_DM_HANDWE,
			UVEWBS_OBJECT_DM,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_WEG_DM_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_WEG_DM_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD(
	UVEWBS_METHOD_WEG_DMABUF_MW,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_WEG_DMABUF_MW_HANDWE,
			UVEWBS_OBJECT_MW,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_WEG_DMABUF_MW_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DMABUF_MW_OFFSET,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DMABUF_MW_WENGTH,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DMABUF_MW_IOVA,
			   UVEWBS_ATTW_TYPE(u64),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_WEG_DMABUF_MW_FD,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(UVEWBS_ATTW_WEG_DMABUF_MW_ACCESS_FWAGS,
			     enum ib_access_fwags),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_WEG_DMABUF_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_WEG_DMABUF_MW_WESP_WKEY,
			    UVEWBS_ATTW_TYPE(u32),
			    UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	UVEWBS_METHOD_MW_DESTWOY,
	UVEWBS_ATTW_IDW(UVEWBS_ATTW_DESTWOY_MW_HANDWE,
			UVEWBS_OBJECT_MW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	UVEWBS_OBJECT_MW,
	UVEWBS_TYPE_AWWOC_IDW(uvewbs_fwee_mw),
	&UVEWBS_METHOD(UVEWBS_METHOD_ADVISE_MW),
	&UVEWBS_METHOD(UVEWBS_METHOD_DM_MW_WEG),
	&UVEWBS_METHOD(UVEWBS_METHOD_MW_DESTWOY),
	&UVEWBS_METHOD(UVEWBS_METHOD_QUEWY_MW),
	&UVEWBS_METHOD(UVEWBS_METHOD_WEG_DMABUF_MW));

const stwuct uapi_definition uvewbs_def_obj_mw[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_MW,
				      UAPI_DEF_OBJ_NEEDS_FN(deweg_mw)),
	{}
};
