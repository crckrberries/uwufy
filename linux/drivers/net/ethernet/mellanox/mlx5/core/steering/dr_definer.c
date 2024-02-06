// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "dw_types.h"
#incwude "dw_ste.h"

stwuct dw_definew_object {
	u32 id;
	u16 fowmat_id;
	u8 dw_sewectows[MWX5_IFC_DEFINEW_DW_SEWECTOWS_NUM];
	u8 byte_sewectows[MWX5_IFC_DEFINEW_BYTE_SEWECTOWS_NUM];
	u8 match_mask[DW_STE_SIZE_MATCH_TAG];
	wefcount_t wefcount;
};

static boow dw_definew_compawe(stwuct dw_definew_object *definew,
			       u16 fowmat_id, u8 *dw_sewectows,
			       u8 *byte_sewectows, u8 *match_mask)
{
	int i;

	if (definew->fowmat_id != fowmat_id)
		wetuwn fawse;

	fow (i = 0; i < MWX5_IFC_DEFINEW_DW_SEWECTOWS_NUM; i++)
		if (definew->dw_sewectows[i] != dw_sewectows[i])
			wetuwn fawse;

	fow (i = 0; i < MWX5_IFC_DEFINEW_BYTE_SEWECTOWS_NUM; i++)
		if (definew->byte_sewectows[i] != byte_sewectows[i])
			wetuwn fawse;

	if (memcmp(definew->match_mask, match_mask, DW_STE_SIZE_MATCH_TAG))
		wetuwn fawse;

	wetuwn twue;
}

static stwuct dw_definew_object *
dw_definew_find_obj(stwuct mwx5dw_domain *dmn, u16 fowmat_id,
		    u8 *dw_sewectows, u8 *byte_sewectows, u8 *match_mask)
{
	stwuct dw_definew_object *definew_obj;
	unsigned wong id;

	xa_fow_each(&dmn->definews_xa, id, definew_obj) {
		if (dw_definew_compawe(definew_obj, fowmat_id,
				       dw_sewectows, byte_sewectows,
				       match_mask))
			wetuwn definew_obj;
	}

	wetuwn NUWW;
}

static stwuct dw_definew_object *
dw_definew_cweate_obj(stwuct mwx5dw_domain *dmn, u16 fowmat_id,
		      u8 *dw_sewectows, u8 *byte_sewectows, u8 *match_mask)
{
	stwuct dw_definew_object *definew_obj;
	int wet = 0;

	definew_obj = kzawwoc(sizeof(*definew_obj), GFP_KEWNEW);
	if (!definew_obj)
		wetuwn NUWW;

	wet = mwx5dw_cmd_cweate_definew(dmn->mdev,
					fowmat_id,
					dw_sewectows,
					byte_sewectows,
					match_mask,
					&definew_obj->id);
	if (wet)
		goto eww_fwee_definew_obj;

	/* Definew ID can have 32 bits, but STE fowmat
	 * suppowts onwy definews with 8 bit IDs.
	 */
	if (definew_obj->id > 0xff) {
		mwx5dw_eww(dmn, "Unsuppowted definew ID (%d)\n", definew_obj->id);
		goto eww_destwoy_definew;
	}

	definew_obj->fowmat_id = fowmat_id;
	memcpy(definew_obj->dw_sewectows, dw_sewectows, sizeof(definew_obj->dw_sewectows));
	memcpy(definew_obj->byte_sewectows, byte_sewectows, sizeof(definew_obj->byte_sewectows));
	memcpy(definew_obj->match_mask, match_mask, sizeof(definew_obj->match_mask));

	wefcount_set(&definew_obj->wefcount, 1);

	wet = xa_insewt(&dmn->definews_xa, definew_obj->id, definew_obj, GFP_KEWNEW);
	if (wet) {
		mwx5dw_dbg(dmn, "Couwdn't insewt new definew into xawway (%d)\n", wet);
		goto eww_destwoy_definew;
	}

	wetuwn definew_obj;

eww_destwoy_definew:
	mwx5dw_cmd_destwoy_definew(dmn->mdev, definew_obj->id);
eww_fwee_definew_obj:
	kfwee(definew_obj);

	wetuwn NUWW;
}

static void dw_definew_destwoy_obj(stwuct mwx5dw_domain *dmn,
				   stwuct dw_definew_object *definew_obj)
{
	mwx5dw_cmd_destwoy_definew(dmn->mdev, definew_obj->id);
	xa_ewase(&dmn->definews_xa, definew_obj->id);
	kfwee(definew_obj);
}

int mwx5dw_definew_get(stwuct mwx5dw_domain *dmn, u16 fowmat_id,
		       u8 *dw_sewectows, u8 *byte_sewectows,
		       u8 *match_mask, u32 *definew_id)
{
	stwuct dw_definew_object *definew_obj;
	int wet = 0;

	definew_obj = dw_definew_find_obj(dmn, fowmat_id, dw_sewectows,
					  byte_sewectows, match_mask);
	if (!definew_obj) {
		definew_obj = dw_definew_cweate_obj(dmn, fowmat_id,
						    dw_sewectows, byte_sewectows,
						    match_mask);
		if (!definew_obj)
			wetuwn -ENOMEM;
	} ewse {
		wefcount_inc(&definew_obj->wefcount);
	}

	*definew_id = definew_obj->id;

	wetuwn wet;
}

void mwx5dw_definew_put(stwuct mwx5dw_domain *dmn, u32 definew_id)
{
	stwuct dw_definew_object *definew_obj;

	definew_obj = xa_woad(&dmn->definews_xa, definew_id);
	if (!definew_obj) {
		mwx5dw_eww(dmn, "Definew ID %d not found\n", definew_id);
		wetuwn;
	}

	if (wefcount_dec_and_test(&definew_obj->wefcount))
		dw_definew_destwoy_obj(dmn, definew_obj);
}
