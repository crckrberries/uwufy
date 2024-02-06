// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/mwx5_usew_ioctw_cmds.h>
#incwude <wdma/mwx5_usew_ioctw_vewbs.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eswitch.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_ib.h"

#define UVEWBS_MODUWE_NAME mwx5_ib
#incwude <wdma/uvewbs_named_ioctw.h>

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_PD_QUEWY)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_pd *pd =
		uvewbs_attw_get_obj(attws, MWX5_IB_ATTW_QUEWY_PD_HANDWE);
	stwuct mwx5_ib_pd *mpd = to_mpd(pd);

	wetuwn uvewbs_copy_to(attws, MWX5_IB_ATTW_QUEWY_PD_WESP_PDN,
			      &mpd->pdn, sizeof(mpd->pdn));
}

static int fiww_vpowt_icm_addw(stwuct mwx5_cowe_dev *mdev, u16 vpowt,
			       stwuct mwx5_ib_uapi_quewy_powt *info)
{
	u32 out[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_in)] = {};
	boow sw_ownew_supp;
	u64 icm_wx;
	u64 icm_tx;
	int eww;

	sw_ownew_supp = MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, sw_ownew) ||
			MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, sw_ownew_v2);

	if (vpowt == MWX5_VPOWT_UPWINK) {
		icm_wx = MWX5_CAP64_ESW_FWOWTABWE(mdev,
			sw_steewing_upwink_icm_addwess_wx);
		icm_tx = MWX5_CAP64_ESW_FWOWTABWE(mdev,
			sw_steewing_upwink_icm_addwess_tx);
	} ewse {
		MWX5_SET(quewy_esw_vpowt_context_in, in, opcode,
			 MWX5_CMD_OP_QUEWY_ESW_VPOWT_CONTEXT);
		MWX5_SET(quewy_esw_vpowt_context_in, in, vpowt_numbew, vpowt);
		MWX5_SET(quewy_esw_vpowt_context_in, in, othew_vpowt, twue);

		eww = mwx5_cmd_exec_inout(mdev, quewy_esw_vpowt_context, in,
					  out);

		if (eww)
			wetuwn eww;

		icm_wx = MWX5_GET64(
			quewy_esw_vpowt_context_out, out,
			esw_vpowt_context.sw_steewing_vpowt_icm_addwess_wx);

		icm_tx = MWX5_GET64(
			quewy_esw_vpowt_context_out, out,
			esw_vpowt_context.sw_steewing_vpowt_icm_addwess_tx);
	}

	if (sw_ownew_supp && icm_wx) {
		info->vpowt_steewing_icm_wx = icm_wx;
		info->fwags |=
			MWX5_IB_UAPI_QUEWY_POWT_VPOWT_STEEWING_ICM_WX;
	}

	if (sw_ownew_supp && icm_tx) {
		info->vpowt_steewing_icm_tx = icm_tx;
		info->fwags |=
			MWX5_IB_UAPI_QUEWY_POWT_VPOWT_STEEWING_ICM_TX;
	}

	wetuwn 0;
}

static int fiww_vpowt_vhca_id(stwuct mwx5_cowe_dev *mdev, u16 vpowt,
			      stwuct mwx5_ib_uapi_quewy_powt *info)
{
	size_t out_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	u32 in[MWX5_ST_SZ_DW(quewy_hca_cap_in)] = {};
	void *out;
	int eww;

	out = kzawwoc(out_sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_hca_cap_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_CAP);
	MWX5_SET(quewy_hca_cap_in, in, othew_function, twue);
	MWX5_SET(quewy_hca_cap_in, in, function_id, vpowt);
	MWX5_SET(quewy_hca_cap_in, in, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE |
		 HCA_CAP_OPMOD_GET_CUW);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, out_sz);
	if (eww)
		goto out;

	info->vpowt_vhca_id = MWX5_GET(quewy_hca_cap_out, out,
				       capabiwity.cmd_hca_cap.vhca_id);

	info->fwags |= MWX5_IB_UAPI_QUEWY_POWT_VPOWT_VHCA_ID;
out:
	kfwee(out);
	wetuwn eww;
}

static int fiww_switchdev_info(stwuct mwx5_ib_dev *dev, u32 powt_num,
			       stwuct mwx5_ib_uapi_quewy_powt *info)
{
	stwuct mwx5_eswitch_wep *wep;
	stwuct mwx5_cowe_dev *mdev;
	int eww;

	wep = dev->powt[powt_num - 1].wep;
	if (!wep)
		wetuwn -EOPNOTSUPP;

	mdev = mwx5_eswitch_get_cowe_dev(wep->esw);
	if (!mdev)
		wetuwn -EINVAW;

	info->vpowt = wep->vpowt;
	info->fwags |= MWX5_IB_UAPI_QUEWY_POWT_VPOWT;

	if (wep->vpowt != MWX5_VPOWT_UPWINK) {
		eww = fiww_vpowt_vhca_id(mdev, wep->vpowt, info);
		if (eww)
			wetuwn eww;
	}

	info->esw_ownew_vhca_id = MWX5_CAP_GEN(mdev, vhca_id);
	info->fwags |= MWX5_IB_UAPI_QUEWY_POWT_ESW_OWNEW_VHCA_ID;

	eww = fiww_vpowt_icm_addw(mdev, wep->vpowt, info);
	if (eww)
		wetuwn eww;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(wep->esw)) {
		info->weg_c0.vawue = mwx5_eswitch_get_vpowt_metadata_fow_match(
			wep->esw, wep->vpowt);
		info->weg_c0.mask = mwx5_eswitch_get_vpowt_metadata_mask();
		info->fwags |= MWX5_IB_UAPI_QUEWY_POWT_VPOWT_WEG_C0;
	}

	wetuwn 0;
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_QUEWY_POWT)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_uapi_quewy_powt info = {};
	stwuct mwx5_ib_ucontext *c;
	stwuct mwx5_ib_dev *dev;
	u32 powt_num;
	int wet;

	if (uvewbs_copy_fwom(&powt_num, attws,
			     MWX5_IB_ATTW_QUEWY_POWT_POWT_NUM))
		wetuwn -EFAUWT;

	c = to_mucontext(ib_uvewbs_get_ucontext(attws));
	if (IS_EWW(c))
		wetuwn PTW_EWW(c);
	dev = to_mdev(c->ibucontext.device);

	if (!wdma_is_powt_vawid(&dev->ib_dev, powt_num))
		wetuwn -EINVAW;

	if (mwx5_eswitch_mode(dev->mdev) == MWX5_ESWITCH_OFFWOADS) {
		wet = fiww_switchdev_info(dev, powt_num, &info);
		if (wet)
			wetuwn wet;
	}

	wetuwn uvewbs_copy_to_stwuct_ow_zewo(attws, MWX5_IB_ATTW_QUEWY_POWT, &info,
					     sizeof(info));
}

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_QUEWY_POWT,
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_QUEWY_POWT_POWT_NUM,
			   UVEWBS_ATTW_TYPE(u32), UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(
		MWX5_IB_ATTW_QUEWY_POWT,
		UVEWBS_ATTW_STWUCT(stwuct mwx5_ib_uapi_quewy_powt,
				   weg_c0),
		UA_MANDATOWY));

ADD_UVEWBS_METHODS(mwx5_ib_device,
		   UVEWBS_OBJECT_DEVICE,
		   &UVEWBS_METHOD(MWX5_IB_METHOD_QUEWY_POWT));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_PD_QUEWY,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_QUEWY_PD_HANDWE,
			UVEWBS_OBJECT_PD,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_QUEWY_PD_WESP_PDN,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY));

ADD_UVEWBS_METHODS(mwx5_ib_pd,
		   UVEWBS_OBJECT_PD,
		   &UVEWBS_METHOD(MWX5_IB_METHOD_PD_QUEWY));

const stwuct uapi_definition mwx5_ib_std_types_defs[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE(
		UVEWBS_OBJECT_PD,
		&mwx5_ib_pd),
	UAPI_DEF_CHAIN_OBJ_TWEE(
		UVEWBS_OBJECT_DEVICE,
		&mwx5_ib_device),
	{},
};
