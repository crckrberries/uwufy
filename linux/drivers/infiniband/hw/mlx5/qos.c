// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/mwx5_usew_ioctw_cmds.h>
#incwude <wdma/mwx5_usew_ioctw_vewbs.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_ib.h"

#define UVEWBS_MODUWE_NAME mwx5_ib
#incwude <wdma/uvewbs_named_ioctw.h>

static boow pp_is_suppowted(stwuct ib_device *device)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);

	wetuwn (MWX5_CAP_GEN(dev->mdev, qos) &&
		MWX5_CAP_QOS(dev->mdev, packet_pacing) &&
		MWX5_CAP_QOS(dev->mdev, packet_pacing_uid));
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_PP_OBJ_AWWOC)(
	stwuct uvewbs_attw_bundwe *attws)
{
	u8 ww_waw[MWX5_ST_SZ_BYTES(set_pp_wate_wimit_context)] = {};
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(attws,
		MWX5_IB_ATTW_PP_OBJ_AWWOC_HANDWE);
	stwuct mwx5_ib_dev *dev;
	stwuct mwx5_ib_ucontext *c;
	stwuct mwx5_ib_pp *pp_entwy;
	void *in_ctx;
	u16 uid;
	int inwen;
	u32 fwags;
	int eww;

	c = to_mucontext(ib_uvewbs_get_ucontext(attws));
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);

	/* The awwocated entwy can be used onwy by a DEVX context */
	if (!c->devx_uid)
		wetuwn -EINVAW;

	dev = to_mdev(c->ibucontext.device);
	pp_entwy = kzawwoc(sizeof(*pp_entwy), GFP_KEWNEW);
	if (!pp_entwy)
		wetuwn -ENOMEM;

	in_ctx = uvewbs_attw_get_awwoced_ptw(attws,
					     MWX5_IB_ATTW_PP_OBJ_AWWOC_CTX);
	inwen = uvewbs_attw_get_wen(attws,
				    MWX5_IB_ATTW_PP_OBJ_AWWOC_CTX);
	memcpy(ww_waw, in_ctx, inwen);
	eww = uvewbs_get_fwags32(&fwags, attws,
		MWX5_IB_ATTW_PP_OBJ_AWWOC_FWAGS,
		MWX5_IB_UAPI_PP_AWWOC_FWAGS_DEDICATED_INDEX);
	if (eww)
		goto eww;

	uid = (fwags & MWX5_IB_UAPI_PP_AWWOC_FWAGS_DEDICATED_INDEX) ?
		c->devx_uid : MWX5_SHAWED_WESOUWCE_UID;

	eww = mwx5_ww_add_wate_waw(dev->mdev, ww_waw, uid,
			(fwags & MWX5_IB_UAPI_PP_AWWOC_FWAGS_DEDICATED_INDEX),
			&pp_entwy->index);
	if (eww)
		goto eww;

	pp_entwy->mdev = dev->mdev;
	uobj->object = pp_entwy;
	uvewbs_finawize_uobj_cweate(attws, MWX5_IB_ATTW_PP_OBJ_AWWOC_HANDWE);

	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_PP_OBJ_AWWOC_INDEX,
			     &pp_entwy->index, sizeof(pp_entwy->index));
	wetuwn eww;

eww:
	kfwee(pp_entwy);
	wetuwn eww;
}

static int pp_obj_cweanup(stwuct ib_uobject *uobject,
			  enum wdma_wemove_weason why,
			  stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_pp *pp_entwy = uobject->object;

	mwx5_ww_wemove_wate_waw(pp_entwy->mdev, pp_entwy->index);
	kfwee(pp_entwy);
	wetuwn 0;
}

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_PP_OBJ_AWWOC,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_PP_OBJ_AWWOC_HANDWE,
			MWX5_IB_OBJECT_PP,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(
		MWX5_IB_ATTW_PP_OBJ_AWWOC_CTX,
		UVEWBS_ATTW_SIZE(1,
			MWX5_ST_SZ_BYTES(set_pp_wate_wimit_context)),
		UA_MANDATOWY,
		UA_AWWOC_AND_COPY),
	UVEWBS_ATTW_FWAGS_IN(MWX5_IB_ATTW_PP_OBJ_AWWOC_FWAGS,
			enum mwx5_ib_uapi_pp_awwoc_fwags,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_PP_OBJ_AWWOC_INDEX,
			   UVEWBS_ATTW_TYPE(u16),
			   UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	MWX5_IB_METHOD_PP_OBJ_DESTWOY,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_PP_OBJ_DESTWOY_HANDWE,
			MWX5_IB_OBJECT_PP,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(MWX5_IB_OBJECT_PP,
			    UVEWBS_TYPE_AWWOC_IDW(pp_obj_cweanup),
			    &UVEWBS_METHOD(MWX5_IB_METHOD_PP_OBJ_AWWOC),
			    &UVEWBS_METHOD(MWX5_IB_METHOD_PP_OBJ_DESTWOY));


const stwuct uapi_definition mwx5_ib_qos_defs[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(
		MWX5_IB_OBJECT_PP,
		UAPI_DEF_IS_OBJ_SUPPOWTED(pp_is_suppowted)),
	{},
};
