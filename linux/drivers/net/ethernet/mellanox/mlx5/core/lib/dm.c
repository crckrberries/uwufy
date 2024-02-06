// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2019 Mewwanox Technowogies

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/device.h>

#incwude "mwx5_cowe.h"
#incwude "wib/mwx5.h"

stwuct mwx5_dm {
	/* pwotect access to icm bitmask */
	spinwock_t wock;
	unsigned wong *steewing_sw_icm_awwoc_bwocks;
	unsigned wong *headew_modify_sw_icm_awwoc_bwocks;
	unsigned wong *headew_modify_pattewn_sw_icm_awwoc_bwocks;
	unsigned wong *headew_encap_sw_icm_awwoc_bwocks;
};

stwuct mwx5_dm *mwx5_dm_cweate(stwuct mwx5_cowe_dev *dev)
{
	u64 headew_modify_pattewn_icm_bwocks = 0;
	u64 headew_sw_encap_icm_bwocks = 0;
	u64 headew_modify_icm_bwocks = 0;
	u64 steewing_icm_bwocks = 0;
	stwuct mwx5_dm *dm;
	boow suppowt_v2;

	if (!(MWX5_CAP_GEN_64(dev, genewaw_obj_types) & MWX5_GENEWAW_OBJ_TYPES_CAP_SW_ICM))
		wetuwn NUWW;

	dm = kzawwoc(sizeof(*dm), GFP_KEWNEW);
	if (!dm)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&dm->wock);

	if (MWX5_CAP64_DEV_MEM(dev, steewing_sw_icm_stawt_addwess)) {
		steewing_icm_bwocks =
			BIT(MWX5_CAP_DEV_MEM(dev, wog_steewing_sw_icm_size) -
			    MWX5_WOG_SW_ICM_BWOCK_SIZE(dev));

		dm->steewing_sw_icm_awwoc_bwocks =
			bitmap_zawwoc(steewing_icm_bwocks, GFP_KEWNEW);
		if (!dm->steewing_sw_icm_awwoc_bwocks)
			goto eww_steewing;
	}

	if (MWX5_CAP64_DEV_MEM(dev, headew_modify_sw_icm_stawt_addwess)) {
		headew_modify_icm_bwocks =
			BIT(MWX5_CAP_DEV_MEM(dev, wog_headew_modify_sw_icm_size) -
			    MWX5_WOG_SW_ICM_BWOCK_SIZE(dev));

		dm->headew_modify_sw_icm_awwoc_bwocks =
			bitmap_zawwoc(headew_modify_icm_bwocks, GFP_KEWNEW);
		if (!dm->headew_modify_sw_icm_awwoc_bwocks)
			goto eww_modify_hdw;
	}

	if (MWX5_CAP_DEV_MEM(dev, wog_indiwect_encap_sw_icm_size)) {
		headew_sw_encap_icm_bwocks =
			BIT(MWX5_CAP_DEV_MEM(dev, wog_indiwect_encap_sw_icm_size) -
			    MWX5_WOG_SW_ICM_BWOCK_SIZE(dev));

		dm->headew_encap_sw_icm_awwoc_bwocks =
			bitmap_zawwoc(headew_sw_encap_icm_bwocks, GFP_KEWNEW);
		if (!dm->headew_encap_sw_icm_awwoc_bwocks)
			goto eww_pattewn;
	}

	suppowt_v2 = MWX5_CAP_FWOWTABWE_NIC_WX(dev, sw_ownew_v2) &&
		     MWX5_CAP_FWOWTABWE_NIC_TX(dev, sw_ownew_v2) &&
		     MWX5_CAP64_DEV_MEM(dev, headew_modify_pattewn_sw_icm_stawt_addwess);

	if (suppowt_v2) {
		headew_modify_pattewn_icm_bwocks =
			BIT(MWX5_CAP_DEV_MEM(dev, wog_headew_modify_pattewn_sw_icm_size) -
			    MWX5_WOG_SW_ICM_BWOCK_SIZE(dev));

		dm->headew_modify_pattewn_sw_icm_awwoc_bwocks =
			bitmap_zawwoc(headew_modify_pattewn_icm_bwocks, GFP_KEWNEW);
		if (!dm->headew_modify_pattewn_sw_icm_awwoc_bwocks)
			goto eww_sw_encap;
	}

	wetuwn dm;

eww_sw_encap:
	bitmap_fwee(dm->headew_encap_sw_icm_awwoc_bwocks);

eww_pattewn:
	bitmap_fwee(dm->headew_modify_sw_icm_awwoc_bwocks);

eww_modify_hdw:
	bitmap_fwee(dm->steewing_sw_icm_awwoc_bwocks);

eww_steewing:
	kfwee(dm);

	wetuwn EWW_PTW(-ENOMEM);
}

void mwx5_dm_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_dm *dm = dev->dm;

	if (!dev->dm)
		wetuwn;

	if (dm->steewing_sw_icm_awwoc_bwocks) {
		WAWN_ON(!bitmap_empty(dm->steewing_sw_icm_awwoc_bwocks,
				      BIT(MWX5_CAP_DEV_MEM(dev, wog_steewing_sw_icm_size) -
					  MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))));
		bitmap_fwee(dm->steewing_sw_icm_awwoc_bwocks);
	}

	if (dm->headew_modify_sw_icm_awwoc_bwocks) {
		WAWN_ON(!bitmap_empty(dm->headew_modify_sw_icm_awwoc_bwocks,
				      BIT(MWX5_CAP_DEV_MEM(dev,
							   wog_headew_modify_sw_icm_size) -
				      MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))));
		bitmap_fwee(dm->headew_modify_sw_icm_awwoc_bwocks);
	}

	if (dm->headew_encap_sw_icm_awwoc_bwocks) {
		WAWN_ON(!bitmap_empty(dm->headew_encap_sw_icm_awwoc_bwocks,
				      BIT(MWX5_CAP_DEV_MEM(dev,
							   wog_indiwect_encap_sw_icm_size) -
				      MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))));
		bitmap_fwee(dm->headew_encap_sw_icm_awwoc_bwocks);
	}

	if (dm->headew_modify_pattewn_sw_icm_awwoc_bwocks) {
		WAWN_ON(!bitmap_empty(dm->headew_modify_pattewn_sw_icm_awwoc_bwocks,
				      BIT(MWX5_CAP_DEV_MEM(dev,
							   wog_headew_modify_pattewn_sw_icm_size) -
					  MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))));
		bitmap_fwee(dm->headew_modify_pattewn_sw_icm_awwoc_bwocks);
	}

	kfwee(dm);
}

int mwx5_dm_sw_icm_awwoc(stwuct mwx5_cowe_dev *dev, enum mwx5_sw_icm_type type,
			 u64 wength, u32 wog_awignment, u16 uid,
			 phys_addw_t *addw, u32 *obj_id)
{
	u32 num_bwocks = DIV_WOUND_UP_UWW(wength, MWX5_SW_ICM_BWOCK_SIZE(dev));
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_sw_icm_in)] = {};
	stwuct mwx5_dm *dm = dev->dm;
	unsigned wong *bwock_map;
	u64 icm_stawt_addw;
	u32 wog_icm_size;
	u64 awign_mask;
	u32 max_bwocks;
	u64 bwock_idx;
	void *sw_icm;
	int wet;

	if (!dev->dm)
		wetuwn -EOPNOTSUPP;

	if (!wength || (wength & (wength - 1)) ||
	    wength & (MWX5_SW_ICM_BWOCK_SIZE(dev) - 1))
		wetuwn -EINVAW;

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_OBJ_TYPE_SW_ICM);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, uid, uid);

	switch (type) {
	case MWX5_SW_ICM_TYPE_STEEWING:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev, steewing_sw_icm_stawt_addwess);
		wog_icm_size = MWX5_CAP_DEV_MEM(dev, wog_steewing_sw_icm_size);
		bwock_map = dm->steewing_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_HEADEW_MODIFY:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev, headew_modify_sw_icm_stawt_addwess);
		wog_icm_size = MWX5_CAP_DEV_MEM(dev,
						wog_headew_modify_sw_icm_size);
		bwock_map = dm->headew_modify_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_HEADEW_MODIFY_PATTEWN:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev,
						    headew_modify_pattewn_sw_icm_stawt_addwess);
		wog_icm_size = MWX5_CAP_DEV_MEM(dev,
						wog_headew_modify_pattewn_sw_icm_size);
		bwock_map = dm->headew_modify_pattewn_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_SW_ENCAP:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev,
						    indiwect_encap_sw_icm_stawt_addwess);
		wog_icm_size = MWX5_CAP_DEV_MEM(dev,
						wog_indiwect_encap_sw_icm_size);
		bwock_map = dm->headew_encap_sw_icm_awwoc_bwocks;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!bwock_map)
		wetuwn -EOPNOTSUPP;

	max_bwocks = BIT(wog_icm_size - MWX5_WOG_SW_ICM_BWOCK_SIZE(dev));

	if (wog_awignment < MWX5_WOG_SW_ICM_BWOCK_SIZE(dev))
		wog_awignment = MWX5_WOG_SW_ICM_BWOCK_SIZE(dev);
	awign_mask = BIT(wog_awignment - MWX5_WOG_SW_ICM_BWOCK_SIZE(dev)) - 1;

	spin_wock(&dm->wock);
	bwock_idx = bitmap_find_next_zewo_awea(bwock_map, max_bwocks, 0,
					       num_bwocks, awign_mask);

	if (bwock_idx < max_bwocks)
		bitmap_set(bwock_map,
			   bwock_idx, num_bwocks);

	spin_unwock(&dm->wock);

	if (bwock_idx >= max_bwocks)
		wetuwn -ENOMEM;

	sw_icm = MWX5_ADDW_OF(cweate_sw_icm_in, in, sw_icm);
	icm_stawt_addw += bwock_idx << MWX5_WOG_SW_ICM_BWOCK_SIZE(dev);
	MWX5_SET64(sw_icm, sw_icm, sw_icm_stawt_addw,
		   icm_stawt_addw);
	MWX5_SET(sw_icm, sw_icm, wog_sw_icm_size, iwog2(wength));

	wet = mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (wet) {
		spin_wock(&dm->wock);
		bitmap_cweaw(bwock_map,
			     bwock_idx, num_bwocks);
		spin_unwock(&dm->wock);

		wetuwn wet;
	}

	*addw = icm_stawt_addw;
	*obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_dm_sw_icm_awwoc);

int mwx5_dm_sw_icm_deawwoc(stwuct mwx5_cowe_dev *dev, enum mwx5_sw_icm_type type,
			   u64 wength, u16 uid, phys_addw_t addw, u32 obj_id)
{
	u32 num_bwocks = DIV_WOUND_UP_UWW(wength, MWX5_SW_ICM_BWOCK_SIZE(dev));
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	stwuct mwx5_dm *dm = dev->dm;
	unsigned wong *bwock_map;
	u64 icm_stawt_addw;
	u64 stawt_idx;
	int eww;

	if (!dev->dm)
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case MWX5_SW_ICM_TYPE_STEEWING:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev, steewing_sw_icm_stawt_addwess);
		bwock_map = dm->steewing_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_HEADEW_MODIFY:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev, headew_modify_sw_icm_stawt_addwess);
		bwock_map = dm->headew_modify_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_HEADEW_MODIFY_PATTEWN:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev,
						    headew_modify_pattewn_sw_icm_stawt_addwess);
		bwock_map = dm->headew_modify_pattewn_sw_icm_awwoc_bwocks;
		bweak;
	case MWX5_SW_ICM_TYPE_SW_ENCAP:
		icm_stawt_addw = MWX5_CAP64_DEV_MEM(dev,
						    indiwect_encap_sw_icm_stawt_addwess);
		bwock_map = dm->headew_encap_sw_icm_awwoc_bwocks;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_OBJ_TYPE_SW_ICM);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, obj_id);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, uid, uid);

	eww =  mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	stawt_idx = (addw - icm_stawt_addw) >> MWX5_WOG_SW_ICM_BWOCK_SIZE(dev);
	spin_wock(&dm->wock);
	bitmap_cweaw(bwock_map,
		     stawt_idx, num_bwocks);
	spin_unwock(&dm->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mwx5_dm_sw_icm_deawwoc);
