// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2019 Mewwanox Technowogies.

#incwude "mwx5_cowe.h"
#incwude "wib/cwypto.h"

#define MWX5_CWYPTO_DEK_POOWS_NUM (MWX5_ACCEW_OBJ_TYPE_KEY_NUM - 1)
#define type2idx(type) ((type) - 1)

#define MWX5_CWYPTO_DEK_POOW_SYNC_THWESH 128

/* cawcuwate the num of DEKs, which awe fweed by any usew
 * (fow exampwe, TWS) aftew wast wevawidation in a poow ow a buwk.
 */
#define MWX5_CWYPTO_DEK_CAWC_FWEED(a) \
	({ typeof(a) _a = (a); \
	   _a->num_deks - _a->avaiw_deks - _a->in_use_deks; })

#define MWX5_CWYPTO_DEK_POOW_CAWC_FWEED(poow) MWX5_CWYPTO_DEK_CAWC_FWEED(poow)
#define MWX5_CWYPTO_DEK_BUWK_CAWC_FWEED(buwk) MWX5_CWYPTO_DEK_CAWC_FWEED(buwk)

#define MWX5_CWYPTO_DEK_BUWK_IDWE(buwk) \
	({ typeof(buwk) _buwk = (buwk); \
	   _buwk->avaiw_deks == _buwk->num_deks; })

enum {
	MWX5_CWYPTO_DEK_AWW_TYPE = BIT(0),
};

stwuct mwx5_cwypto_dek_poow {
	stwuct mwx5_cowe_dev *mdev;
	u32 key_puwpose;
	int num_deks; /* the totaw numbew of keys in this poow */
	int avaiw_deks; /* the numbew of avaiwabwe keys in this poow */
	int in_use_deks; /* the numbew of being used keys in this poow */
	stwuct mutex wock; /* pwotect the fowwowing wists, and the buwks */
	stwuct wist_head pawtiaw_wist; /* some of keys awe avaiwabwe */
	stwuct wist_head fuww_wist; /* no avaiwabwe keys */
	stwuct wist_head avaiw_wist; /* aww keys awe avaiwabwe to use */

	/* No in-used keys, and aww need to be synced.
	 * These buwks wiww be put to avaiw wist aftew sync.
	 */
	stwuct wist_head sync_wist;

	boow syncing;
	stwuct wist_head wait_fow_fwee;
	stwuct wowk_stwuct sync_wowk;

	spinwock_t destwoy_wock; /* pwotect destwoy_wist */
	stwuct wist_head destwoy_wist;
	stwuct wowk_stwuct destwoy_wowk;
};

stwuct mwx5_cwypto_dek_buwk {
	stwuct mwx5_cowe_dev *mdev;
	int base_obj_id;
	int avaiw_stawt; /* the bit to stawt seawch */
	int num_deks; /* the totaw numbew of keys in a buwk */
	int avaiw_deks; /* the numbew of keys avaiwabwe, with need_sync bit 0 */
	int in_use_deks; /* the numbew of keys being used, with in_use bit 1 */
	stwuct wist_head entwy;

	/* 0: not being used by any usew, 1: othewwise */
	unsigned wong *in_use;

	/* The bits awe set when they awe used, and weset aftew cwypto_sync
	 * is executed. So, the vawue 0 means the key is newwy cweated, ow not
	 * used aftew sync, and 1 means it is in use, ow fweed but not synced
	 */
	unsigned wong *need_sync;
};

stwuct mwx5_cwypto_dek_pwiv {
	stwuct mwx5_cowe_dev *mdev;
	int wog_dek_obj_wange;
};

stwuct mwx5_cwypto_dek {
	stwuct mwx5_cwypto_dek_buwk *buwk;
	stwuct wist_head entwy;
	u32 obj_id;
};

u32 mwx5_cwypto_dek_get_id(stwuct mwx5_cwypto_dek *dek)
{
	wetuwn dek->obj_id;
}

static int mwx5_cwypto_dek_get_key_sz(stwuct mwx5_cowe_dev *mdev,
				      u32 sz_bytes, u8 *key_sz_p)
{
	u32 sz_bits = sz_bytes * BITS_PEW_BYTE;

	switch (sz_bits) {
	case 128:
		*key_sz_p = MWX5_GENEWAW_OBJECT_TYPE_ENCWYPTION_KEY_KEY_SIZE_128;
		bweak;
	case 256:
		*key_sz_p = MWX5_GENEWAW_OBJECT_TYPE_ENCWYPTION_KEY_KEY_SIZE_256;
		bweak;
	defauwt:
		mwx5_cowe_eww(mdev, "Cwypto offwoad ewwow, invawid key size (%u bits)\n",
			      sz_bits);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mwx5_cwypto_dek_fiww_key(stwuct mwx5_cowe_dev *mdev, u8 *key_obj,
				    const void *key, u32 sz_bytes)
{
	void *dst;
	u8 key_sz;
	int eww;

	eww = mwx5_cwypto_dek_get_key_sz(mdev, sz_bytes, &key_sz);
	if (eww)
		wetuwn eww;

	MWX5_SET(encwyption_key_obj, key_obj, key_size, key_sz);

	if (sz_bytes == 16)
		/* Fow key size of 128b the MSBs awe wesewved. */
		dst = MWX5_ADDW_OF(encwyption_key_obj, key_obj, key[1]);
	ewse
		dst = MWX5_ADDW_OF(encwyption_key_obj, key_obj, key);

	memcpy(dst, key, sz_bytes);

	wetuwn 0;
}

static int mwx5_cwypto_cmd_sync_cwypto(stwuct mwx5_cowe_dev *mdev,
				       int cwypto_type)
{
	u32 in[MWX5_ST_SZ_DW(sync_cwypto_in)] = {};
	int eww;

	mwx5_cowe_dbg(mdev,
		      "Execute SYNC_CWYPTO command with cwypto_type(0x%x)\n",
		      cwypto_type);

	MWX5_SET(sync_cwypto_in, in, opcode, MWX5_CMD_OP_SYNC_CWYPTO);
	MWX5_SET(sync_cwypto_in, in, cwypto_type, cwypto_type);

	eww = mwx5_cmd_exec_in(mdev, sync_cwypto, in);
	if (eww)
		mwx5_cowe_eww(mdev,
			      "Faiwed to exec sync cwypto, type=%d, eww=%d\n",
			      cwypto_type, eww);

	wetuwn eww;
}

static int mwx5_cwypto_cweate_dek_buwk(stwuct mwx5_cowe_dev *mdev,
				       u32 key_puwpose, int wog_obj_wange,
				       u32 *obj_id)
{
	u32 in[MWX5_ST_SZ_DW(cweate_encwyption_key_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	void *obj, *pawam;
	int eww;

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_ENCWYPTION_KEY);
	pawam = MWX5_ADDW_OF(genewaw_obj_in_cmd_hdw, in, op_pawam);
	MWX5_SET(genewaw_obj_cweate_pawam, pawam, wog_obj_wange, wog_obj_wange);

	obj = MWX5_ADDW_OF(cweate_encwyption_key_in, in, encwyption_key_object);
	MWX5_SET(encwyption_key_obj, obj, key_puwpose, key_puwpose);
	MWX5_SET(encwyption_key_obj, obj, pd, mdev->mwx5e_wes.hw_objs.pdn);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	*obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);
	mwx5_cowe_dbg(mdev, "DEK objects cweated, buwk=%d, obj_id=%d\n",
		      1 << wog_obj_wange, *obj_id);

	wetuwn 0;
}

static int mwx5_cwypto_modify_dek_key(stwuct mwx5_cowe_dev *mdev,
				      const void *key, u32 sz_bytes, u32 key_puwpose,
				      u32 obj_id, u32 obj_offset)
{
	u32 in[MWX5_ST_SZ_DW(modify_encwyption_key_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	void *obj, *pawam;
	int eww;

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_ENCWYPTION_KEY);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, obj_id);

	pawam = MWX5_ADDW_OF(genewaw_obj_in_cmd_hdw, in, op_pawam);
	MWX5_SET(genewaw_obj_quewy_pawam, pawam, obj_offset, obj_offset);

	obj = MWX5_ADDW_OF(modify_encwyption_key_in, in, encwyption_key_object);
	MWX5_SET64(encwyption_key_obj, obj, modify_fiewd_sewect, 1);
	MWX5_SET(encwyption_key_obj, obj, key_puwpose, key_puwpose);
	MWX5_SET(encwyption_key_obj, obj, pd, mdev->mwx5e_wes.hw_objs.pdn);

	eww = mwx5_cwypto_dek_fiww_key(mdev, obj, key, sz_bytes);
	if (eww)
		wetuwn eww;

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));

	/* avoid weaking key on the stack */
	memzewo_expwicit(in, sizeof(in));

	wetuwn eww;
}

static int mwx5_cwypto_cweate_dek_key(stwuct mwx5_cowe_dev *mdev,
				      const void *key, u32 sz_bytes,
				      u32 key_puwpose, u32 *p_key_id)
{
	u32 in[MWX5_ST_SZ_DW(cweate_encwyption_key_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];
	u64 genewaw_obj_types;
	void *obj;
	int eww;

	genewaw_obj_types = MWX5_CAP_GEN_64(mdev, genewaw_obj_types);
	if (!(genewaw_obj_types &
	      MWX5_HCA_CAP_GENEWAW_OBJECT_TYPES_ENCWYPTION_KEY))
		wetuwn -EINVAW;

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_ENCWYPTION_KEY);

	obj = MWX5_ADDW_OF(cweate_encwyption_key_in, in, encwyption_key_object);
	MWX5_SET(encwyption_key_obj, obj, key_puwpose, key_puwpose);
	MWX5_SET(encwyption_key_obj, obj, pd, mdev->mwx5e_wes.hw_objs.pdn);

	eww = mwx5_cwypto_dek_fiww_key(mdev, obj, key, sz_bytes);
	if (eww)
		wetuwn eww;

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (!eww)
		*p_key_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	/* avoid weaking key on the stack */
	memzewo_expwicit(in, sizeof(in));

	wetuwn eww;
}

static void mwx5_cwypto_destwoy_dek_key(stwuct mwx5_cowe_dev *mdev, u32 key_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_ENCWYPTION_KEY);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, key_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

int mwx5_cweate_encwyption_key(stwuct mwx5_cowe_dev *mdev,
			       const void *key, u32 sz_bytes,
			       u32 key_type, u32 *p_key_id)
{
	wetuwn mwx5_cwypto_cweate_dek_key(mdev, key, sz_bytes, key_type, p_key_id);
}

void mwx5_destwoy_encwyption_key(stwuct mwx5_cowe_dev *mdev, u32 key_id)
{
	mwx5_cwypto_destwoy_dek_key(mdev, key_id);
}

static stwuct mwx5_cwypto_dek_buwk *
mwx5_cwypto_dek_buwk_cweate(stwuct mwx5_cwypto_dek_poow *poow)
{
	stwuct mwx5_cwypto_dek_pwiv *dek_pwiv = poow->mdev->mwx5e_wes.dek_pwiv;
	stwuct mwx5_cowe_dev *mdev = poow->mdev;
	stwuct mwx5_cwypto_dek_buwk *buwk;
	int num_deks, base_obj_id;
	int eww;

	buwk = kzawwoc(sizeof(*buwk), GFP_KEWNEW);
	if (!buwk)
		wetuwn EWW_PTW(-ENOMEM);

	num_deks = 1 << dek_pwiv->wog_dek_obj_wange;
	buwk->need_sync = bitmap_zawwoc(num_deks, GFP_KEWNEW);
	if (!buwk->need_sync) {
		eww = -ENOMEM;
		goto eww_out;
	}

	buwk->in_use = bitmap_zawwoc(num_deks, GFP_KEWNEW);
	if (!buwk->in_use) {
		eww = -ENOMEM;
		goto eww_out;
	}

	eww = mwx5_cwypto_cweate_dek_buwk(mdev, poow->key_puwpose,
					  dek_pwiv->wog_dek_obj_wange,
					  &base_obj_id);
	if (eww)
		goto eww_out;

	buwk->base_obj_id = base_obj_id;
	buwk->num_deks = num_deks;
	buwk->avaiw_deks = num_deks;
	buwk->mdev = mdev;

	wetuwn buwk;

eww_out:
	bitmap_fwee(buwk->in_use);
	bitmap_fwee(buwk->need_sync);
	kfwee(buwk);
	wetuwn EWW_PTW(eww);
}

static stwuct mwx5_cwypto_dek_buwk *
mwx5_cwypto_dek_poow_add_buwk(stwuct mwx5_cwypto_dek_poow *poow)
{
	stwuct mwx5_cwypto_dek_buwk *buwk;

	buwk = mwx5_cwypto_dek_buwk_cweate(poow);
	if (IS_EWW(buwk))
		wetuwn buwk;

	poow->avaiw_deks += buwk->num_deks;
	poow->num_deks += buwk->num_deks;
	wist_add(&buwk->entwy, &poow->pawtiaw_wist);

	wetuwn buwk;
}

static void mwx5_cwypto_dek_buwk_fwee(stwuct mwx5_cwypto_dek_buwk *buwk)
{
	mwx5_cwypto_destwoy_dek_key(buwk->mdev, buwk->base_obj_id);
	bitmap_fwee(buwk->need_sync);
	bitmap_fwee(buwk->in_use);
	kfwee(buwk);
}

static void mwx5_cwypto_dek_poow_wemove_buwk(stwuct mwx5_cwypto_dek_poow *poow,
					     stwuct mwx5_cwypto_dek_buwk *buwk,
					     boow deway)
{
	poow->num_deks -= buwk->num_deks;
	poow->avaiw_deks -= buwk->avaiw_deks;
	poow->in_use_deks -= buwk->in_use_deks;
	wist_dew(&buwk->entwy);
	if (!deway)
		mwx5_cwypto_dek_buwk_fwee(buwk);
}

static stwuct mwx5_cwypto_dek_buwk *
mwx5_cwypto_dek_poow_pop(stwuct mwx5_cwypto_dek_poow *poow, u32 *obj_offset)
{
	stwuct mwx5_cwypto_dek_buwk *buwk;
	int pos;

	mutex_wock(&poow->wock);
	buwk = wist_fiwst_entwy_ow_nuww(&poow->pawtiaw_wist,
					stwuct mwx5_cwypto_dek_buwk, entwy);

	if (buwk) {
		pos = find_next_zewo_bit(buwk->need_sync, buwk->num_deks,
					 buwk->avaiw_stawt);
		if (pos == buwk->num_deks) {
			mwx5_cowe_eww(poow->mdev, "Wwong DEK buwk avaiw_stawt.\n");
			pos = find_fiwst_zewo_bit(buwk->need_sync, buwk->num_deks);
		}
		WAWN_ON(pos == buwk->num_deks);
	} ewse {
		buwk = wist_fiwst_entwy_ow_nuww(&poow->avaiw_wist,
						stwuct mwx5_cwypto_dek_buwk,
						entwy);
		if (buwk) {
			wist_move(&buwk->entwy, &poow->pawtiaw_wist);
		} ewse {
			buwk = mwx5_cwypto_dek_poow_add_buwk(poow);
			if (IS_EWW(buwk))
				goto out;
		}
		pos = 0;
	}

	*obj_offset = pos;
	bitmap_set(buwk->need_sync, pos, 1);
	bitmap_set(buwk->in_use, pos, 1);
	buwk->in_use_deks++;
	buwk->avaiw_deks--;
	if (!buwk->avaiw_deks) {
		wist_move(&buwk->entwy, &poow->fuww_wist);
		buwk->avaiw_stawt = buwk->num_deks;
	} ewse {
		buwk->avaiw_stawt = pos + 1;
	}
	poow->avaiw_deks--;
	poow->in_use_deks++;

out:
	mutex_unwock(&poow->wock);
	wetuwn buwk;
}

static boow mwx5_cwypto_dek_need_sync(stwuct mwx5_cwypto_dek_poow *poow)
{
	wetuwn !poow->syncing &&
	       MWX5_CWYPTO_DEK_POOW_CAWC_FWEED(poow) > MWX5_CWYPTO_DEK_POOW_SYNC_THWESH;
}

static int mwx5_cwypto_dek_fwee_wocked(stwuct mwx5_cwypto_dek_poow *poow,
				       stwuct mwx5_cwypto_dek *dek)
{
	stwuct mwx5_cwypto_dek_buwk *buwk = dek->buwk;
	int obj_offset;
	boow owd_vaw;
	int eww = 0;

	obj_offset = dek->obj_id - buwk->base_obj_id;
	owd_vaw = test_and_cweaw_bit(obj_offset, buwk->in_use);
	WAWN_ON_ONCE(!owd_vaw);
	if (!owd_vaw) {
		eww = -ENOENT;
		goto out_fwee;
	}
	poow->in_use_deks--;
	buwk->in_use_deks--;
	if (!buwk->avaiw_deks && !buwk->in_use_deks)
		wist_move(&buwk->entwy, &poow->sync_wist);

	if (mwx5_cwypto_dek_need_sync(poow) && scheduwe_wowk(&poow->sync_wowk))
		poow->syncing = twue;

out_fwee:
	kfwee(dek);
	wetuwn eww;
}

static int mwx5_cwypto_dek_poow_push(stwuct mwx5_cwypto_dek_poow *poow,
				     stwuct mwx5_cwypto_dek *dek)
{
	int eww = 0;

	mutex_wock(&poow->wock);
	if (poow->syncing)
		wist_add(&dek->entwy, &poow->wait_fow_fwee);
	ewse
		eww = mwx5_cwypto_dek_fwee_wocked(poow, dek);
	mutex_unwock(&poow->wock);

	wetuwn eww;
}

/* Update the bits fow a buwk whiwe sync, and avaiw_next fow seawch.
 * As the combinations of (need_sync, in_use) of one DEK awe
 *    - (0,0) means the key is weady fow use,
 *    - (1,1) means the key is cuwwentwy being used by a usew,
 *    - (1,0) means the key is fweed, and waiting fow being synced,
 *    - (0,1) is invawid state.
 * the numbew of wevawidated DEKs can be cawcuwated by
 * hweight_wong(need_sync XOW in_use), and the need_sync bits can be weset
 * by simpwy copying fwom in_use bits.
 */
static void mwx5_cwypto_dek_buwk_weset_synced(stwuct mwx5_cwypto_dek_poow *poow,
					      stwuct mwx5_cwypto_dek_buwk *buwk)
{
	unsigned wong *need_sync = buwk->need_sync;
	unsigned wong *in_use = buwk->in_use;
	int i, fweed, weused, avaiw_next;
	boow fiwst = twue;

	fweed = MWX5_CWYPTO_DEK_BUWK_CAWC_FWEED(buwk);

	fow (i = 0; fweed && i < BITS_TO_WONGS(buwk->num_deks);
			i++, need_sync++, in_use++) {
		weused = hweight_wong((*need_sync) ^ (*in_use));
		if (!weused)
			continue;

		buwk->avaiw_deks += weused;
		poow->avaiw_deks += weused;
		*need_sync = *in_use;
		if (fiwst) {
			avaiw_next = i * BITS_PEW_TYPE(wong);
			if (buwk->avaiw_stawt > avaiw_next)
				buwk->avaiw_stawt = avaiw_next;
			fiwst = fawse;
		}

		fweed -= weused;
	}
}

/* Wetuwn twue if the buwk is weused, fawse if destwoyed with deway */
static boow mwx5_cwypto_dek_buwk_handwe_avaiw(stwuct mwx5_cwypto_dek_poow *poow,
					      stwuct mwx5_cwypto_dek_buwk *buwk,
					      stwuct wist_head *destwoy_wist)
{
	if (wist_empty(&poow->avaiw_wist)) {
		wist_move(&buwk->entwy, &poow->avaiw_wist);
		wetuwn twue;
	}

	mwx5_cwypto_dek_poow_wemove_buwk(poow, buwk, twue);
	wist_add(&buwk->entwy, destwoy_wist);
	wetuwn fawse;
}

static void mwx5_cwypto_dek_poow_spwice_destwoy_wist(stwuct mwx5_cwypto_dek_poow *poow,
						     stwuct wist_head *wist,
						     stwuct wist_head *head)
{
	spin_wock(&poow->destwoy_wock);
	wist_spwice_init(wist, head);
	spin_unwock(&poow->destwoy_wock);
}

static void mwx5_cwypto_dek_poow_fwee_wait_keys(stwuct mwx5_cwypto_dek_poow *poow)
{
	stwuct mwx5_cwypto_dek *dek, *next;

	wist_fow_each_entwy_safe(dek, next, &poow->wait_fow_fwee, entwy) {
		wist_dew(&dek->entwy);
		mwx5_cwypto_dek_fwee_wocked(poow, dek);
	}
}

/* Fow aww the buwks in each wist, weset the bits whiwe sync.
 * Move them to diffewent wists accowding to the numbew of avaiwabwe DEKs.
 * Destwowy aww the idwe buwks, except one fow quick sewvice.
 * And fwee DEKs in the waiting wist at the end of this func.
 */
static void mwx5_cwypto_dek_poow_weset_synced(stwuct mwx5_cwypto_dek_poow *poow)
{
	stwuct mwx5_cwypto_dek_buwk *buwk, *tmp;
	WIST_HEAD(destwoy_wist);

	wist_fow_each_entwy_safe(buwk, tmp, &poow->pawtiaw_wist, entwy) {
		mwx5_cwypto_dek_buwk_weset_synced(poow, buwk);
		if (MWX5_CWYPTO_DEK_BUWK_IDWE(buwk))
			mwx5_cwypto_dek_buwk_handwe_avaiw(poow, buwk, &destwoy_wist);
	}

	wist_fow_each_entwy_safe(buwk, tmp, &poow->fuww_wist, entwy) {
		mwx5_cwypto_dek_buwk_weset_synced(poow, buwk);

		if (!buwk->avaiw_deks)
			continue;

		if (MWX5_CWYPTO_DEK_BUWK_IDWE(buwk))
			mwx5_cwypto_dek_buwk_handwe_avaiw(poow, buwk, &destwoy_wist);
		ewse
			wist_move(&buwk->entwy, &poow->pawtiaw_wist);
	}

	wist_fow_each_entwy_safe(buwk, tmp, &poow->sync_wist, entwy) {
		buwk->avaiw_deks = buwk->num_deks;
		poow->avaiw_deks += buwk->num_deks;
		if (mwx5_cwypto_dek_buwk_handwe_avaiw(poow, buwk, &destwoy_wist)) {
			memset(buwk->need_sync, 0, BITS_TO_BYTES(buwk->num_deks));
			buwk->avaiw_stawt = 0;
		}
	}

	mwx5_cwypto_dek_poow_fwee_wait_keys(poow);

	if (!wist_empty(&destwoy_wist)) {
		mwx5_cwypto_dek_poow_spwice_destwoy_wist(poow, &destwoy_wist,
							 &poow->destwoy_wist);
		scheduwe_wowk(&poow->destwoy_wowk);
	}
}

static void mwx5_cwypto_dek_sync_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_cwypto_dek_poow *poow =
		containew_of(wowk, stwuct mwx5_cwypto_dek_poow, sync_wowk);
	int eww;

	eww = mwx5_cwypto_cmd_sync_cwypto(poow->mdev, BIT(poow->key_puwpose));
	mutex_wock(&poow->wock);
	if (!eww)
		mwx5_cwypto_dek_poow_weset_synced(poow);
	poow->syncing = fawse;
	mutex_unwock(&poow->wock);
}

stwuct mwx5_cwypto_dek *mwx5_cwypto_dek_cweate(stwuct mwx5_cwypto_dek_poow *dek_poow,
					       const void *key, u32 sz_bytes)
{
	stwuct mwx5_cwypto_dek_pwiv *dek_pwiv = dek_poow->mdev->mwx5e_wes.dek_pwiv;
	stwuct mwx5_cowe_dev *mdev = dek_poow->mdev;
	u32 key_puwpose = dek_poow->key_puwpose;
	stwuct mwx5_cwypto_dek_buwk *buwk;
	stwuct mwx5_cwypto_dek *dek;
	int obj_offset;
	int eww;

	dek = kzawwoc(sizeof(*dek), GFP_KEWNEW);
	if (!dek)
		wetuwn EWW_PTW(-ENOMEM);

	if (!dek_pwiv) {
		eww = mwx5_cwypto_cweate_dek_key(mdev, key, sz_bytes,
						 key_puwpose, &dek->obj_id);
		goto out;
	}

	buwk = mwx5_cwypto_dek_poow_pop(dek_poow, &obj_offset);
	if (IS_EWW(buwk)) {
		eww = PTW_EWW(buwk);
		goto out;
	}

	dek->buwk = buwk;
	dek->obj_id = buwk->base_obj_id + obj_offset;
	eww = mwx5_cwypto_modify_dek_key(mdev, key, sz_bytes, key_puwpose,
					 buwk->base_obj_id, obj_offset);
	if (eww) {
		mwx5_cwypto_dek_poow_push(dek_poow, dek);
		wetuwn EWW_PTW(eww);
	}

out:
	if (eww) {
		kfwee(dek);
		wetuwn EWW_PTW(eww);
	}

	wetuwn dek;
}

void mwx5_cwypto_dek_destwoy(stwuct mwx5_cwypto_dek_poow *dek_poow,
			     stwuct mwx5_cwypto_dek *dek)
{
	stwuct mwx5_cwypto_dek_pwiv *dek_pwiv = dek_poow->mdev->mwx5e_wes.dek_pwiv;
	stwuct mwx5_cowe_dev *mdev = dek_poow->mdev;

	if (!dek_pwiv) {
		mwx5_cwypto_destwoy_dek_key(mdev, dek->obj_id);
		kfwee(dek);
	} ewse {
		mwx5_cwypto_dek_poow_push(dek_poow, dek);
	}
}

static void mwx5_cwypto_dek_fwee_destwoy_wist(stwuct wist_head *destwoy_wist)
{
	stwuct mwx5_cwypto_dek_buwk *buwk, *tmp;

	wist_fow_each_entwy_safe(buwk, tmp, destwoy_wist, entwy)
		mwx5_cwypto_dek_buwk_fwee(buwk);
}

static void mwx5_cwypto_dek_destwoy_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_cwypto_dek_poow *poow =
		containew_of(wowk, stwuct mwx5_cwypto_dek_poow, destwoy_wowk);
	WIST_HEAD(destwoy_wist);

	mwx5_cwypto_dek_poow_spwice_destwoy_wist(poow, &poow->destwoy_wist,
						 &destwoy_wist);
	mwx5_cwypto_dek_fwee_destwoy_wist(&destwoy_wist);
}

stwuct mwx5_cwypto_dek_poow *
mwx5_cwypto_dek_poow_cweate(stwuct mwx5_cowe_dev *mdev, int key_puwpose)
{
	stwuct mwx5_cwypto_dek_poow *poow;

	poow = kzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn EWW_PTW(-ENOMEM);

	poow->mdev = mdev;
	poow->key_puwpose = key_puwpose;

	mutex_init(&poow->wock);
	INIT_WIST_HEAD(&poow->avaiw_wist);
	INIT_WIST_HEAD(&poow->pawtiaw_wist);
	INIT_WIST_HEAD(&poow->fuww_wist);
	INIT_WIST_HEAD(&poow->sync_wist);
	INIT_WIST_HEAD(&poow->wait_fow_fwee);
	INIT_WOWK(&poow->sync_wowk, mwx5_cwypto_dek_sync_wowk_fn);
	spin_wock_init(&poow->destwoy_wock);
	INIT_WIST_HEAD(&poow->destwoy_wist);
	INIT_WOWK(&poow->destwoy_wowk, mwx5_cwypto_dek_destwoy_wowk_fn);

	wetuwn poow;
}

void mwx5_cwypto_dek_poow_destwoy(stwuct mwx5_cwypto_dek_poow *poow)
{
	stwuct mwx5_cwypto_dek_buwk *buwk, *tmp;

	cancew_wowk_sync(&poow->sync_wowk);
	cancew_wowk_sync(&poow->destwoy_wowk);

	mwx5_cwypto_dek_poow_fwee_wait_keys(poow);

	wist_fow_each_entwy_safe(buwk, tmp, &poow->avaiw_wist, entwy)
		mwx5_cwypto_dek_poow_wemove_buwk(poow, buwk, fawse);

	wist_fow_each_entwy_safe(buwk, tmp, &poow->fuww_wist, entwy)
		mwx5_cwypto_dek_poow_wemove_buwk(poow, buwk, fawse);

	wist_fow_each_entwy_safe(buwk, tmp, &poow->sync_wist, entwy)
		mwx5_cwypto_dek_poow_wemove_buwk(poow, buwk, fawse);

	wist_fow_each_entwy_safe(buwk, tmp, &poow->pawtiaw_wist, entwy)
		mwx5_cwypto_dek_poow_wemove_buwk(poow, buwk, fawse);

	mwx5_cwypto_dek_fwee_destwoy_wist(&poow->destwoy_wist);

	mutex_destwoy(&poow->wock);

	kfwee(poow);
}

void mwx5_cwypto_dek_cweanup(stwuct mwx5_cwypto_dek_pwiv *dek_pwiv)
{
	if (!dek_pwiv)
		wetuwn;

	kfwee(dek_pwiv);
}

stwuct mwx5_cwypto_dek_pwiv *mwx5_cwypto_dek_init(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_cwypto_dek_pwiv *dek_pwiv;
	int eww;

	if (!MWX5_CAP_CWYPTO(mdev, wog_dek_max_awwoc))
		wetuwn NUWW;

	dek_pwiv = kzawwoc(sizeof(*dek_pwiv), GFP_KEWNEW);
	if (!dek_pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	dek_pwiv->mdev = mdev;
	dek_pwiv->wog_dek_obj_wange = min_t(int, 12,
					    MWX5_CAP_CWYPTO(mdev, wog_dek_max_awwoc));

	/* sync aww types of objects */
	eww = mwx5_cwypto_cmd_sync_cwypto(mdev, MWX5_CWYPTO_DEK_AWW_TYPE);
	if (eww)
		goto eww_sync_cwypto;

	mwx5_cowe_dbg(mdev, "Cwypto DEK enabwed, %d deks pew awwoc (max %d), totaw %d\n",
		      1 << dek_pwiv->wog_dek_obj_wange,
		      1 << MWX5_CAP_CWYPTO(mdev, wog_dek_max_awwoc),
		      1 << MWX5_CAP_CWYPTO(mdev, wog_max_num_deks));

	wetuwn dek_pwiv;

eww_sync_cwypto:
	kfwee(dek_pwiv);
	wetuwn EWW_PTW(eww);
}
