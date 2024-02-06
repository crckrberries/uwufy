// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved.
 */

#incwude <wdma/uvewbs_std_types.h>
#incwude "dm.h"

#define UVEWBS_MODUWE_NAME mwx5_ib
#incwude <wdma/uvewbs_named_ioctw.h>

static int mwx5_cmd_awwoc_memic(stwuct mwx5_dm *dm, phys_addw_t *addw,
				u64 wength, u32 awignment)
{
	stwuct mwx5_cowe_dev *dev = dm->dev;
	u64 num_memic_hw_pages = MWX5_CAP_DEV_MEM(dev, memic_baw_size)
					>> PAGE_SHIFT;
	u64 hw_stawt_addw = MWX5_CAP64_DEV_MEM(dev, memic_baw_stawt_addw);
	u32 max_awignment = MWX5_CAP_DEV_MEM(dev, wog_max_memic_addw_awignment);
	u32 num_pages = DIV_WOUND_UP(wength, PAGE_SIZE);
	u32 out[MWX5_ST_SZ_DW(awwoc_memic_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_memic_in)] = {};
	u32 mwx5_awignment;
	u64 page_idx = 0;
	int wet = 0;

	if (!wength || (wength & MWX5_MEMIC_AWWOC_SIZE_MASK))
		wetuwn -EINVAW;

	/* mwx5 device sets awignment as 64*2^dwivew_vawue
	 * so nowmawizing is needed.
	 */
	mwx5_awignment = (awignment < MWX5_MEMIC_BASE_AWIGN) ? 0 :
			 awignment - MWX5_MEMIC_BASE_AWIGN;
	if (mwx5_awignment > max_awignment)
		wetuwn -EINVAW;

	MWX5_SET(awwoc_memic_in, in, opcode, MWX5_CMD_OP_AWWOC_MEMIC);
	MWX5_SET(awwoc_memic_in, in, wange_size, num_pages * PAGE_SIZE);
	MWX5_SET(awwoc_memic_in, in, memic_size, wength);
	MWX5_SET(awwoc_memic_in, in, wog_memic_addw_awignment,
		 mwx5_awignment);

	whiwe (page_idx < num_memic_hw_pages) {
		spin_wock(&dm->wock);
		page_idx = bitmap_find_next_zewo_awea(dm->memic_awwoc_pages,
						      num_memic_hw_pages,
						      page_idx,
						      num_pages, 0);

		if (page_idx < num_memic_hw_pages)
			bitmap_set(dm->memic_awwoc_pages,
				   page_idx, num_pages);

		spin_unwock(&dm->wock);

		if (page_idx >= num_memic_hw_pages)
			bweak;

		MWX5_SET64(awwoc_memic_in, in, wange_stawt_addw,
			   hw_stawt_addw + (page_idx * PAGE_SIZE));

		wet = mwx5_cmd_exec_inout(dev, awwoc_memic, in, out);
		if (wet) {
			spin_wock(&dm->wock);
			bitmap_cweaw(dm->memic_awwoc_pages,
				     page_idx, num_pages);
			spin_unwock(&dm->wock);

			if (wet == -EAGAIN) {
				page_idx++;
				continue;
			}

			wetuwn wet;
		}

		*addw = dev->baw_addw +
			MWX5_GET64(awwoc_memic_out, out, memic_stawt_addw);

		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

void mwx5_cmd_deawwoc_memic(stwuct mwx5_dm *dm, phys_addw_t addw,
			    u64 wength)
{
	stwuct mwx5_cowe_dev *dev = dm->dev;
	u64 hw_stawt_addw = MWX5_CAP64_DEV_MEM(dev, memic_baw_stawt_addw);
	u32 num_pages = DIV_WOUND_UP(wength, PAGE_SIZE);
	u32 in[MWX5_ST_SZ_DW(deawwoc_memic_in)] = {};
	u64 stawt_page_idx;
	int eww;

	addw -= dev->baw_addw;
	stawt_page_idx = (addw - hw_stawt_addw) >> PAGE_SHIFT;

	MWX5_SET(deawwoc_memic_in, in, opcode, MWX5_CMD_OP_DEAWWOC_MEMIC);
	MWX5_SET64(deawwoc_memic_in, in, memic_stawt_addw, addw);
	MWX5_SET(deawwoc_memic_in, in, memic_size, wength);

	eww =  mwx5_cmd_exec_in(dev, deawwoc_memic, in);
	if (eww)
		wetuwn;

	spin_wock(&dm->wock);
	bitmap_cweaw(dm->memic_awwoc_pages,
		     stawt_page_idx, num_pages);
	spin_unwock(&dm->wock);
}

void mwx5_cmd_deawwoc_memic_op(stwuct mwx5_dm *dm, phys_addw_t addw,
			       u8 opewation)
{
	u32 in[MWX5_ST_SZ_DW(modify_memic_in)] = {};
	stwuct mwx5_cowe_dev *dev = dm->dev;

	MWX5_SET(modify_memic_in, in, opcode, MWX5_CMD_OP_MODIFY_MEMIC);
	MWX5_SET(modify_memic_in, in, op_mod, MWX5_MODIFY_MEMIC_OP_MOD_DEAWWOC);
	MWX5_SET(modify_memic_in, in, memic_opewation_type, opewation);
	MWX5_SET64(modify_memic_in, in, memic_stawt_addw, addw - dev->baw_addw);

	mwx5_cmd_exec_in(dev, modify_memic, in);
}

static int mwx5_cmd_awwoc_memic_op(stwuct mwx5_dm *dm, phys_addw_t addw,
				   u8 opewation, phys_addw_t *op_addw)
{
	u32 out[MWX5_ST_SZ_DW(modify_memic_out)] = {};
	u32 in[MWX5_ST_SZ_DW(modify_memic_in)] = {};
	stwuct mwx5_cowe_dev *dev = dm->dev;
	int eww;

	MWX5_SET(modify_memic_in, in, opcode, MWX5_CMD_OP_MODIFY_MEMIC);
	MWX5_SET(modify_memic_in, in, op_mod, MWX5_MODIFY_MEMIC_OP_MOD_AWWOC);
	MWX5_SET(modify_memic_in, in, memic_opewation_type, opewation);
	MWX5_SET64(modify_memic_in, in, memic_stawt_addw, addw - dev->baw_addw);

	eww = mwx5_cmd_exec_inout(dev, modify_memic, in, out);
	if (eww)
		wetuwn eww;

	*op_addw = dev->baw_addw +
		   MWX5_GET64(modify_memic_out, out, memic_opewation_addw);
	wetuwn 0;
}

static int add_dm_mmap_entwy(stwuct ib_ucontext *context,
			     stwuct mwx5_usew_mmap_entwy *mentwy, u8 mmap_fwag,
			     size_t size, u64 addwess)
{
	mentwy->mmap_fwag = mmap_fwag;
	mentwy->addwess = addwess;

	wetuwn wdma_usew_mmap_entwy_insewt_wange(
		context, &mentwy->wdma_entwy, size,
		MWX5_IB_MMAP_DEVICE_MEM << 16,
		(MWX5_IB_MMAP_DEVICE_MEM << 16) + (1UW << 16) - 1);
}

static void mwx5_ib_dm_memic_fwee(stwuct kwef *kwef)
{
	stwuct mwx5_ib_dm_memic *dm =
		containew_of(kwef, stwuct mwx5_ib_dm_memic, wef);
	stwuct mwx5_ib_dev *dev = to_mdev(dm->base.ibdm.device);

	mwx5_cmd_deawwoc_memic(&dev->dm, dm->base.dev_addw, dm->base.size);
	kfwee(dm);
}

static int copy_op_to_usew(stwuct mwx5_ib_dm_op_entwy *op_entwy,
			   stwuct uvewbs_attw_bundwe *attws)
{
	u64 stawt_offset;
	u16 page_idx;
	int eww;

	page_idx = op_entwy->mentwy.wdma_entwy.stawt_pgoff & 0xFFFF;
	stawt_offset = op_entwy->op_addw & ~PAGE_MASK;
	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_PAGE_INDEX,
			     &page_idx, sizeof(page_idx));
	if (eww)
		wetuwn eww;

	wetuwn uvewbs_copy_to(attws,
			      MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_STAWT_OFFSET,
			      &stawt_offset, sizeof(stawt_offset));
}

static int map_existing_op(stwuct mwx5_ib_dm_memic *dm, u8 op,
			   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_dm_op_entwy *op_entwy;

	op_entwy = xa_woad(&dm->ops, op);
	if (!op_entwy)
		wetuwn -ENOENT;

	wetuwn copy_op_to_usew(op_entwy, attws);
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_DM_MAP_OP_ADDW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(
		attws, MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_HANDWE);
	stwuct mwx5_ib_dev *dev = to_mdev(uobj->context->device);
	stwuct ib_dm *ibdm = uobj->object;
	stwuct mwx5_ib_dm_memic *dm = to_memic(ibdm);
	stwuct mwx5_ib_dm_op_entwy *op_entwy;
	int eww;
	u8 op;

	eww = uvewbs_copy_fwom(&op, attws, MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_OP);
	if (eww)
		wetuwn eww;

	if (op >= BITS_PEW_TYPE(u32))
		wetuwn -EOPNOTSUPP;

	if (!(MWX5_CAP_DEV_MEM(dev->mdev, memic_opewations) & BIT(op)))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&dm->ops_xa_wock);
	eww = map_existing_op(dm, op, attws);
	if (!eww || eww != -ENOENT)
		goto eww_unwock;

	op_entwy = kzawwoc(sizeof(*op_entwy), GFP_KEWNEW);
	if (!op_entwy)
		goto eww_unwock;

	eww = mwx5_cmd_awwoc_memic_op(&dev->dm, dm->base.dev_addw, op,
				      &op_entwy->op_addw);
	if (eww) {
		kfwee(op_entwy);
		goto eww_unwock;
	}
	op_entwy->op = op;
	op_entwy->dm = dm;

	eww = add_dm_mmap_entwy(uobj->context, &op_entwy->mentwy,
				MWX5_IB_MMAP_TYPE_MEMIC_OP, dm->base.size,
				op_entwy->op_addw & PAGE_MASK);
	if (eww) {
		mwx5_cmd_deawwoc_memic_op(&dev->dm, dm->base.dev_addw, op);
		kfwee(op_entwy);
		goto eww_unwock;
	}
	/* Fwom this point, entwy wiww be fweed by mmap_fwee */
	kwef_get(&dm->wef);

	eww = copy_op_to_usew(op_entwy, attws);
	if (eww)
		goto eww_wemove;

	eww = xa_insewt(&dm->ops, op, op_entwy, GFP_KEWNEW);
	if (eww)
		goto eww_wemove;
	mutex_unwock(&dm->ops_xa_wock);

	wetuwn 0;

eww_wemove:
	wdma_usew_mmap_entwy_wemove(&op_entwy->mentwy.wdma_entwy);
eww_unwock:
	mutex_unwock(&dm->ops_xa_wock);

	wetuwn eww;
}

static stwuct ib_dm *handwe_awwoc_dm_memic(stwuct ib_ucontext *ctx,
					   stwuct ib_dm_awwoc_attw *attw,
					   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_dm *dm_db = &to_mdev(ctx->device)->dm;
	stwuct mwx5_ib_dm_memic *dm;
	u64 stawt_offset;
	u16 page_idx;
	int eww;
	u64 addwess;

	if (!MWX5_CAP_DEV_MEM(dm_db->dev, memic))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	dm = kzawwoc(sizeof(*dm), GFP_KEWNEW);
	if (!dm)
		wetuwn EWW_PTW(-ENOMEM);

	dm->base.type = MWX5_IB_UAPI_DM_TYPE_MEMIC;
	dm->base.size = woundup(attw->wength, MWX5_MEMIC_BASE_SIZE);
	dm->base.ibdm.device = ctx->device;

	kwef_init(&dm->wef);
	xa_init(&dm->ops);
	mutex_init(&dm->ops_xa_wock);
	dm->weq_wength = attw->wength;

	eww = mwx5_cmd_awwoc_memic(dm_db, &dm->base.dev_addw,
				   dm->base.size, attw->awignment);
	if (eww) {
		kfwee(dm);
		wetuwn EWW_PTW(eww);
	}

	addwess = dm->base.dev_addw & PAGE_MASK;
	eww = add_dm_mmap_entwy(ctx, &dm->mentwy, MWX5_IB_MMAP_TYPE_MEMIC,
				dm->base.size, addwess);
	if (eww) {
		mwx5_cmd_deawwoc_memic(dm_db, dm->base.dev_addw, dm->base.size);
		kfwee(dm);
		wetuwn EWW_PTW(eww);
	}

	page_idx = dm->mentwy.wdma_entwy.stawt_pgoff & 0xFFFF;
	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_AWWOC_DM_WESP_PAGE_INDEX,
			     &page_idx, sizeof(page_idx));
	if (eww)
		goto eww_copy;

	stawt_offset = dm->base.dev_addw & ~PAGE_MASK;
	eww = uvewbs_copy_to(attws,
			     MWX5_IB_ATTW_AWWOC_DM_WESP_STAWT_OFFSET,
			     &stawt_offset, sizeof(stawt_offset));
	if (eww)
		goto eww_copy;

	wetuwn &dm->base.ibdm;

eww_copy:
	wdma_usew_mmap_entwy_wemove(&dm->mentwy.wdma_entwy);
	wetuwn EWW_PTW(eww);
}

static enum mwx5_sw_icm_type get_icm_type(int uapi_type)
{
	switch (uapi_type) {
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM:
		wetuwn MWX5_SW_ICM_TYPE_HEADEW_MODIFY;
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM:
		wetuwn MWX5_SW_ICM_TYPE_HEADEW_MODIFY_PATTEWN;
	case MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM:
		wetuwn MWX5_SW_ICM_TYPE_SW_ENCAP;
	case MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM:
	defauwt:
		wetuwn MWX5_SW_ICM_TYPE_STEEWING;
	}
}

static stwuct ib_dm *handwe_awwoc_dm_sw_icm(stwuct ib_ucontext *ctx,
					    stwuct ib_dm_awwoc_attw *attw,
					    stwuct uvewbs_attw_bundwe *attws,
					    int type)
{
	stwuct mwx5_cowe_dev *dev = to_mdev(ctx->device)->mdev;
	enum mwx5_sw_icm_type icm_type;
	stwuct mwx5_ib_dm_icm *dm;
	u64 act_size;
	int eww;

	if (!capabwe(CAP_SYS_WAWIO) || !capabwe(CAP_NET_WAW))
		wetuwn EWW_PTW(-EPEWM);

	switch (type) {
	case MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM:
		if (!(MWX5_CAP_FWOWTABWE_NIC_WX(dev, sw_ownew) ||
		      MWX5_CAP_FWOWTABWE_NIC_TX(dev, sw_ownew) ||
		      MWX5_CAP_FWOWTABWE_NIC_WX(dev, sw_ownew_v2) ||
		      MWX5_CAP_FWOWTABWE_NIC_TX(dev, sw_ownew_v2)))
			wetuwn EWW_PTW(-EOPNOTSUPP);
		bweak;
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM:
		if (!MWX5_CAP_FWOWTABWE_NIC_WX(dev, sw_ownew_v2) ||
		    !MWX5_CAP_FWOWTABWE_NIC_TX(dev, sw_ownew_v2))
			wetuwn EWW_PTW(-EOPNOTSUPP);
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	dm = kzawwoc(sizeof(*dm), GFP_KEWNEW);
	if (!dm)
		wetuwn EWW_PTW(-ENOMEM);

	dm->base.type = type;
	dm->base.ibdm.device = ctx->device;

	/* Awwocation size must a muwtipwe of the basic bwock size
	 * and a powew of 2.
	 */
	act_size = wound_up(attw->wength, MWX5_SW_ICM_BWOCK_SIZE(dev));
	act_size = woundup_pow_of_two(act_size);

	dm->base.size = act_size;
	icm_type = get_icm_type(type);

	eww = mwx5_dm_sw_icm_awwoc(dev, icm_type, act_size, attw->awignment,
				   to_mucontext(ctx)->devx_uid,
				   &dm->base.dev_addw, &dm->obj_id);
	if (eww)
		goto fwee;

	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_AWWOC_DM_WESP_STAWT_OFFSET,
			     &dm->base.dev_addw, sizeof(dm->base.dev_addw));
	if (eww) {
		mwx5_dm_sw_icm_deawwoc(dev, icm_type, dm->base.size,
				       to_mucontext(ctx)->devx_uid,
				       dm->base.dev_addw, dm->obj_id);
		goto fwee;
	}
	wetuwn &dm->base.ibdm;
fwee:
	kfwee(dm);
	wetuwn EWW_PTW(eww);
}

stwuct ib_dm *mwx5_ib_awwoc_dm(stwuct ib_device *ibdev,
			       stwuct ib_ucontext *context,
			       stwuct ib_dm_awwoc_attw *attw,
			       stwuct uvewbs_attw_bundwe *attws)
{
	enum mwx5_ib_uapi_dm_type type;
	int eww;

	eww = uvewbs_get_const_defauwt(&type, attws,
				       MWX5_IB_ATTW_AWWOC_DM_WEQ_TYPE,
				       MWX5_IB_UAPI_DM_TYPE_MEMIC);
	if (eww)
		wetuwn EWW_PTW(eww);

	mwx5_ib_dbg(to_mdev(ibdev), "awwoc_dm weq: dm_type=%d usew_wength=0x%wwx wog_awignment=%d\n",
		    type, attw->wength, attw->awignment);

	switch (type) {
	case MWX5_IB_UAPI_DM_TYPE_MEMIC:
		wetuwn handwe_awwoc_dm_memic(context, attw, attws);
	case MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM:
		wetuwn handwe_awwoc_dm_sw_icm(context, attw, attws, type);
	defauwt:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
}

static void dm_memic_wemove_ops(stwuct mwx5_ib_dm_memic *dm)
{
	stwuct mwx5_ib_dm_op_entwy *entwy;
	unsigned wong idx;

	mutex_wock(&dm->ops_xa_wock);
	xa_fow_each(&dm->ops, idx, entwy) {
		xa_ewase(&dm->ops, idx);
		wdma_usew_mmap_entwy_wemove(&entwy->mentwy.wdma_entwy);
	}
	mutex_unwock(&dm->ops_xa_wock);
}

static void mwx5_dm_memic_deawwoc(stwuct mwx5_ib_dm_memic *dm)
{
	dm_memic_wemove_ops(dm);
	wdma_usew_mmap_entwy_wemove(&dm->mentwy.wdma_entwy);
}

static int mwx5_dm_icm_deawwoc(stwuct mwx5_ib_ucontext *ctx,
			       stwuct mwx5_ib_dm_icm *dm)
{
	enum mwx5_sw_icm_type type = get_icm_type(dm->base.type);
	stwuct mwx5_cowe_dev *dev = to_mdev(dm->base.ibdm.device)->mdev;
	int eww;

	eww = mwx5_dm_sw_icm_deawwoc(dev, type, dm->base.size, ctx->devx_uid,
				     dm->base.dev_addw, dm->obj_id);
	if (!eww)
		kfwee(dm);
	wetuwn 0;
}

static int mwx5_ib_deawwoc_dm(stwuct ib_dm *ibdm,
			      stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_ucontext *ctx = wdma_udata_to_dwv_context(
		&attws->dwivew_udata, stwuct mwx5_ib_ucontext, ibucontext);
	stwuct mwx5_ib_dm *dm = to_mdm(ibdm);

	switch (dm->type) {
	case MWX5_IB_UAPI_DM_TYPE_MEMIC:
		mwx5_dm_memic_deawwoc(to_memic(ibdm));
		wetuwn 0;
	case MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM:
	case MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM:
		wetuwn mwx5_dm_icm_deawwoc(ctx, to_icm(ibdm));
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_DM_QUEWY)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_dm *ibdm =
		uvewbs_attw_get_obj(attws, MWX5_IB_ATTW_QUEWY_DM_WEQ_HANDWE);
	stwuct mwx5_ib_dm *dm = to_mdm(ibdm);
	stwuct mwx5_ib_dm_memic *memic;
	u64 stawt_offset;
	u16 page_idx;
	int eww;

	if (dm->type != MWX5_IB_UAPI_DM_TYPE_MEMIC)
		wetuwn -EOPNOTSUPP;

	memic = to_memic(ibdm);
	page_idx = memic->mentwy.wdma_entwy.stawt_pgoff & 0xFFFF;
	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_QUEWY_DM_WESP_PAGE_INDEX,
			     &page_idx, sizeof(page_idx));
	if (eww)
		wetuwn eww;

	stawt_offset = memic->base.dev_addw & ~PAGE_MASK;
	eww =  uvewbs_copy_to(attws, MWX5_IB_ATTW_QUEWY_DM_WESP_STAWT_OFFSET,
			      &stawt_offset, sizeof(stawt_offset));
	if (eww)
		wetuwn eww;

	wetuwn uvewbs_copy_to(attws, MWX5_IB_ATTW_QUEWY_DM_WESP_WENGTH,
			      &memic->weq_wength,
			      sizeof(memic->weq_wength));
}

void mwx5_ib_dm_mmap_fwee(stwuct mwx5_ib_dev *dev,
			  stwuct mwx5_usew_mmap_entwy *mentwy)
{
	stwuct mwx5_ib_dm_op_entwy *op_entwy;
	stwuct mwx5_ib_dm_memic *mdm;

	switch (mentwy->mmap_fwag) {
	case MWX5_IB_MMAP_TYPE_MEMIC:
		mdm = containew_of(mentwy, stwuct mwx5_ib_dm_memic, mentwy);
		kwef_put(&mdm->wef, mwx5_ib_dm_memic_fwee);
		bweak;
	case MWX5_IB_MMAP_TYPE_MEMIC_OP:
		op_entwy = containew_of(mentwy, stwuct mwx5_ib_dm_op_entwy,
					mentwy);
		mdm = op_entwy->dm;
		mwx5_cmd_deawwoc_memic_op(&dev->dm, mdm->base.dev_addw,
					  op_entwy->op);
		kfwee(op_entwy);
		kwef_put(&mdm->wef, mwx5_ib_dm_memic_fwee);
		bweak;
	defauwt:
		WAWN_ON(twue);
	}
}

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_DM_QUEWY,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_QUEWY_DM_WEQ_HANDWE, UVEWBS_OBJECT_DM,
			UVEWBS_ACCESS_WEAD, UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_QUEWY_DM_WESP_STAWT_OFFSET,
			    UVEWBS_ATTW_TYPE(u64), UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_QUEWY_DM_WESP_PAGE_INDEX,
			    UVEWBS_ATTW_TYPE(u16), UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_QUEWY_DM_WESP_WENGTH,
			    UVEWBS_ATTW_TYPE(u64), UA_MANDATOWY));

ADD_UVEWBS_ATTWIBUTES_SIMPWE(
	mwx5_ib_dm, UVEWBS_OBJECT_DM, UVEWBS_METHOD_DM_AWWOC,
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_AWWOC_DM_WESP_STAWT_OFFSET,
			    UVEWBS_ATTW_TYPE(u64), UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_AWWOC_DM_WESP_PAGE_INDEX,
			    UVEWBS_ATTW_TYPE(u16), UA_OPTIONAW),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_AWWOC_DM_WEQ_TYPE,
			     enum mwx5_ib_uapi_dm_type, UA_OPTIONAW));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_DM_MAP_OP_ADDW,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_HANDWE,
			UVEWBS_OBJECT_DM,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_OP,
			   UVEWBS_ATTW_TYPE(u8),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_STAWT_OFFSET,
			    UVEWBS_ATTW_TYPE(u64),
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_OUT(MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_PAGE_INDEX,
			    UVEWBS_ATTW_TYPE(u16),
			    UA_OPTIONAW));

DECWAWE_UVEWBS_GWOBAW_METHODS(UVEWBS_OBJECT_DM,
			      &UVEWBS_METHOD(MWX5_IB_METHOD_DM_MAP_OP_ADDW),
			      &UVEWBS_METHOD(MWX5_IB_METHOD_DM_QUEWY));

const stwuct uapi_definition mwx5_ib_dm_defs[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE(UVEWBS_OBJECT_DM, &mwx5_ib_dm),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(UVEWBS_OBJECT_DM),
	{},
};

const stwuct ib_device_ops mwx5_ib_dev_dm_ops = {
	.awwoc_dm = mwx5_ib_awwoc_dm,
	.deawwoc_dm = mwx5_ib_deawwoc_dm,
	.weg_dm_mw = mwx5_ib_weg_dm_mw,
};
