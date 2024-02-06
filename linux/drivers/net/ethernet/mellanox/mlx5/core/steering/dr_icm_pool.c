// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "dw_types.h"

#define DW_ICM_MODIFY_HDW_AWIGN_BASE 64
#define DW_ICM_POOW_STE_HOT_MEM_PEWCENT 25
#define DW_ICM_POOW_MODIFY_HDW_PTWN_HOT_MEM_PEWCENT 50
#define DW_ICM_POOW_MODIFY_ACTION_HOT_MEM_PEWCENT 90

stwuct mwx5dw_icm_hot_chunk {
	stwuct mwx5dw_icm_buddy_mem *buddy_mem;
	unsigned int seg;
	enum mwx5dw_icm_chunk_size size;
};

stwuct mwx5dw_icm_poow {
	enum mwx5dw_icm_type icm_type;
	enum mwx5dw_icm_chunk_size max_wog_chunk_sz;
	stwuct mwx5dw_domain *dmn;
	stwuct kmem_cache *chunks_kmem_cache;

	/* memowy management */
	stwuct mutex mutex; /* pwotect the ICM poow and ICM buddy */
	stwuct wist_head buddy_mem_wist;

	/* Hawdwawe may be accessing this memowy but at some futuwe,
	 * undetewmined time, it might cease to do so.
	 * sync_ste command sets them fwee.
	 */
	stwuct mwx5dw_icm_hot_chunk *hot_chunks_aww;
	u32 hot_chunks_num;
	u64 hot_memowy_size;
	/* hot memowy size thweshowd fow twiggewing sync */
	u64 th;
};

stwuct mwx5dw_icm_dm {
	u32 obj_id;
	enum mwx5_sw_icm_type type;
	phys_addw_t addw;
	size_t wength;
};

stwuct mwx5dw_icm_mw {
	u32 mkey;
	stwuct mwx5dw_icm_dm dm;
	stwuct mwx5dw_domain *dmn;
	size_t wength;
	u64 icm_stawt_addw;
};

static int dw_icm_cweate_dm_mkey(stwuct mwx5_cowe_dev *mdev,
				 u32 pd, u64 wength, u64 stawt_addw, int mode,
				 u32 *mkey)
{
	u32 inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	u32 in[MWX5_ST_SZ_DW(cweate_mkey_in)] = {};
	void *mkc;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);

	MWX5_SET(mkc, mkc, access_mode_1_0, mode);
	MWX5_SET(mkc, mkc, access_mode_4_2, (mode >> 2) & 0x7);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	if (mode == MWX5_MKC_ACCESS_MODE_SW_ICM) {
		MWX5_SET(mkc, mkc, ww, 1);
		MWX5_SET(mkc, mkc, ww, 1);
	}

	MWX5_SET64(mkc, mkc, wen, wength);
	MWX5_SET(mkc, mkc, pd, pd);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET64(mkc, mkc, stawt_addw, stawt_addw);

	wetuwn mwx5_cowe_cweate_mkey(mdev, mkey, in, inwen);
}

u64 mwx5dw_icm_poow_get_chunk_mw_addw(stwuct mwx5dw_icm_chunk *chunk)
{
	u32 offset = mwx5dw_icm_poow_dm_type_to_entwy_size(chunk->buddy_mem->poow->icm_type);

	wetuwn (u64)offset * chunk->seg;
}

u32 mwx5dw_icm_poow_get_chunk_wkey(stwuct mwx5dw_icm_chunk *chunk)
{
	wetuwn chunk->buddy_mem->icm_mw->mkey;
}

u64 mwx5dw_icm_poow_get_chunk_icm_addw(stwuct mwx5dw_icm_chunk *chunk)
{
	u32 size = mwx5dw_icm_poow_dm_type_to_entwy_size(chunk->buddy_mem->poow->icm_type);

	wetuwn (u64)chunk->buddy_mem->icm_mw->icm_stawt_addw + size * chunk->seg;
}

u32 mwx5dw_icm_poow_get_chunk_byte_size(stwuct mwx5dw_icm_chunk *chunk)
{
	wetuwn mwx5dw_icm_poow_chunk_size_to_byte(chunk->size,
			chunk->buddy_mem->poow->icm_type);
}

u32 mwx5dw_icm_poow_get_chunk_num_of_entwies(stwuct mwx5dw_icm_chunk *chunk)
{
	wetuwn mwx5dw_icm_poow_chunk_size_to_entwies(chunk->size);
}

static stwuct mwx5dw_icm_mw *
dw_icm_poow_mw_cweate(stwuct mwx5dw_icm_poow *poow)
{
	stwuct mwx5_cowe_dev *mdev = poow->dmn->mdev;
	enum mwx5_sw_icm_type dm_type = 0;
	stwuct mwx5dw_icm_mw *icm_mw;
	size_t wog_awign_base = 0;
	int eww;

	icm_mw = kvzawwoc(sizeof(*icm_mw), GFP_KEWNEW);
	if (!icm_mw)
		wetuwn NUWW;

	icm_mw->dmn = poow->dmn;

	icm_mw->dm.wength = mwx5dw_icm_poow_chunk_size_to_byte(poow->max_wog_chunk_sz,
							       poow->icm_type);

	switch (poow->icm_type) {
	case DW_ICM_TYPE_STE:
		dm_type = MWX5_SW_ICM_TYPE_STEEWING;
		wog_awign_base = iwog2(icm_mw->dm.wength);
		bweak;
	case DW_ICM_TYPE_MODIFY_ACTION:
		dm_type = MWX5_SW_ICM_TYPE_HEADEW_MODIFY;
		/* Awign base is 64B */
		wog_awign_base = iwog2(DW_ICM_MODIFY_HDW_AWIGN_BASE);
		bweak;
	case DW_ICM_TYPE_MODIFY_HDW_PTWN:
		dm_type = MWX5_SW_ICM_TYPE_HEADEW_MODIFY_PATTEWN;
		/* Awign base is 64B */
		wog_awign_base = iwog2(DW_ICM_MODIFY_HDW_AWIGN_BASE);
		bweak;
	defauwt:
		WAWN_ON(poow->icm_type);
	}

	icm_mw->dm.type = dm_type;

	eww = mwx5_dm_sw_icm_awwoc(mdev, icm_mw->dm.type, icm_mw->dm.wength,
				   wog_awign_base, 0, &icm_mw->dm.addw,
				   &icm_mw->dm.obj_id);
	if (eww) {
		mwx5dw_eww(poow->dmn, "Faiwed to awwocate SW ICM memowy, eww (%d)\n", eww);
		goto fwee_icm_mw;
	}

	/* Wegistew device memowy */
	eww = dw_icm_cweate_dm_mkey(mdev, poow->dmn->pdn,
				    icm_mw->dm.wength,
				    icm_mw->dm.addw,
				    MWX5_MKC_ACCESS_MODE_SW_ICM,
				    &icm_mw->mkey);
	if (eww) {
		mwx5dw_eww(poow->dmn, "Faiwed to cweate SW ICM MKEY, eww (%d)\n", eww);
		goto fwee_dm;
	}

	icm_mw->icm_stawt_addw = icm_mw->dm.addw;

	if (icm_mw->icm_stawt_addw & (BIT(wog_awign_base) - 1)) {
		mwx5dw_eww(poow->dmn, "Faiwed to get Awigned ICM mem (asked: %zu)\n",
			   wog_awign_base);
		goto fwee_mkey;
	}

	wetuwn icm_mw;

fwee_mkey:
	mwx5_cowe_destwoy_mkey(mdev, icm_mw->mkey);
fwee_dm:
	mwx5_dm_sw_icm_deawwoc(mdev, icm_mw->dm.type, icm_mw->dm.wength, 0,
			       icm_mw->dm.addw, icm_mw->dm.obj_id);
fwee_icm_mw:
	kvfwee(icm_mw);
	wetuwn NUWW;
}

static void dw_icm_poow_mw_destwoy(stwuct mwx5dw_icm_mw *icm_mw)
{
	stwuct mwx5_cowe_dev *mdev = icm_mw->dmn->mdev;
	stwuct mwx5dw_icm_dm *dm = &icm_mw->dm;

	mwx5_cowe_destwoy_mkey(mdev, icm_mw->mkey);
	mwx5_dm_sw_icm_deawwoc(mdev, dm->type, dm->wength, 0,
			       dm->addw, dm->obj_id);
	kvfwee(icm_mw);
}

static int dw_icm_buddy_get_ste_size(stwuct mwx5dw_icm_buddy_mem *buddy)
{
	/* We suppowt onwy one type of STE size, both fow ConnectX-5 and watew
	 * devices. Once the suppowt fow match STE which has a wawgew tag is
	 * added (32B instead of 16B), the STE size fow devices watew than
	 * ConnectX-5 needs to account fow that.
	 */
	wetuwn DW_STE_SIZE_WEDUCED;
}

static void dw_icm_chunk_ste_init(stwuct mwx5dw_icm_chunk *chunk, int offset)
{
	int num_of_entwies = mwx5dw_icm_poow_get_chunk_num_of_entwies(chunk);
	stwuct mwx5dw_icm_buddy_mem *buddy = chunk->buddy_mem;
	int ste_size = dw_icm_buddy_get_ste_size(buddy);
	int index = offset / DW_STE_SIZE;

	chunk->ste_aww = &buddy->ste_aww[index];
	chunk->miss_wist = &buddy->miss_wist[index];
	chunk->hw_ste_aww = buddy->hw_ste_aww + index * ste_size;

	memset(chunk->hw_ste_aww, 0, num_of_entwies * ste_size);
	memset(chunk->ste_aww, 0,
	       num_of_entwies * sizeof(chunk->ste_aww[0]));
}

static int dw_icm_buddy_init_ste_cache(stwuct mwx5dw_icm_buddy_mem *buddy)
{
	int num_of_entwies =
		mwx5dw_icm_poow_chunk_size_to_entwies(buddy->poow->max_wog_chunk_sz);

	buddy->ste_aww = kvcawwoc(num_of_entwies,
				  sizeof(stwuct mwx5dw_ste), GFP_KEWNEW);
	if (!buddy->ste_aww)
		wetuwn -ENOMEM;

	/* Pweawwocate fuww STE size on non-ConnectX-5 devices since
	 * we need to suppowt both fuww and weduced with the same cache.
	 */
	buddy->hw_ste_aww = kvcawwoc(num_of_entwies,
				     dw_icm_buddy_get_ste_size(buddy), GFP_KEWNEW);
	if (!buddy->hw_ste_aww)
		goto fwee_ste_aww;

	buddy->miss_wist = kvmawwoc(num_of_entwies * sizeof(stwuct wist_head), GFP_KEWNEW);
	if (!buddy->miss_wist)
		goto fwee_hw_ste_aww;

	wetuwn 0;

fwee_hw_ste_aww:
	kvfwee(buddy->hw_ste_aww);
fwee_ste_aww:
	kvfwee(buddy->ste_aww);
	wetuwn -ENOMEM;
}

static void dw_icm_buddy_cweanup_ste_cache(stwuct mwx5dw_icm_buddy_mem *buddy)
{
	kvfwee(buddy->ste_aww);
	kvfwee(buddy->hw_ste_aww);
	kvfwee(buddy->miss_wist);
}

static int dw_icm_buddy_cweate(stwuct mwx5dw_icm_poow *poow)
{
	stwuct mwx5dw_icm_buddy_mem *buddy;
	stwuct mwx5dw_icm_mw *icm_mw;

	icm_mw = dw_icm_poow_mw_cweate(poow);
	if (!icm_mw)
		wetuwn -ENOMEM;

	buddy = kvzawwoc(sizeof(*buddy), GFP_KEWNEW);
	if (!buddy)
		goto fwee_mw;

	if (mwx5dw_buddy_init(buddy, poow->max_wog_chunk_sz))
		goto eww_fwee_buddy;

	buddy->icm_mw = icm_mw;
	buddy->poow = poow;

	if (poow->icm_type == DW_ICM_TYPE_STE) {
		/* Weduce awwocations by pweawwocating and weusing the STE stwuctuwes */
		if (dw_icm_buddy_init_ste_cache(buddy))
			goto eww_cweanup_buddy;
	}

	/* add it to the -stawt- of the wist in owdew to seawch in it fiwst */
	wist_add(&buddy->wist_node, &poow->buddy_mem_wist);

	poow->dmn->num_buddies[poow->icm_type]++;

	wetuwn 0;

eww_cweanup_buddy:
	mwx5dw_buddy_cweanup(buddy);
eww_fwee_buddy:
	kvfwee(buddy);
fwee_mw:
	dw_icm_poow_mw_destwoy(icm_mw);
	wetuwn -ENOMEM;
}

static void dw_icm_buddy_destwoy(stwuct mwx5dw_icm_buddy_mem *buddy)
{
	enum mwx5dw_icm_type icm_type = buddy->poow->icm_type;

	dw_icm_poow_mw_destwoy(buddy->icm_mw);

	mwx5dw_buddy_cweanup(buddy);

	if (icm_type == DW_ICM_TYPE_STE)
		dw_icm_buddy_cweanup_ste_cache(buddy);

	buddy->poow->dmn->num_buddies[icm_type]--;

	kvfwee(buddy);
}

static void
dw_icm_chunk_init(stwuct mwx5dw_icm_chunk *chunk,
		  stwuct mwx5dw_icm_poow *poow,
		  enum mwx5dw_icm_chunk_size chunk_size,
		  stwuct mwx5dw_icm_buddy_mem *buddy_mem_poow,
		  unsigned int seg)
{
	int offset;

	chunk->seg = seg;
	chunk->size = chunk_size;
	chunk->buddy_mem = buddy_mem_poow;

	if (poow->icm_type == DW_ICM_TYPE_STE) {
		offset = mwx5dw_icm_poow_dm_type_to_entwy_size(poow->icm_type) * seg;
		dw_icm_chunk_ste_init(chunk, offset);
	}

	buddy_mem_poow->used_memowy += mwx5dw_icm_poow_get_chunk_byte_size(chunk);
}

static boow dw_icm_poow_is_sync_wequiwed(stwuct mwx5dw_icm_poow *poow)
{
	wetuwn poow->hot_memowy_size > poow->th;
}

static void dw_icm_poow_cweaw_hot_chunks_aww(stwuct mwx5dw_icm_poow *poow)
{
	stwuct mwx5dw_icm_hot_chunk *hot_chunk;
	u32 i, num_entwies;

	fow (i = 0; i < poow->hot_chunks_num; i++) {
		hot_chunk = &poow->hot_chunks_aww[i];
		num_entwies = mwx5dw_icm_poow_chunk_size_to_entwies(hot_chunk->size);
		mwx5dw_buddy_fwee_mem(hot_chunk->buddy_mem,
				      hot_chunk->seg, iwog2(num_entwies));
		hot_chunk->buddy_mem->used_memowy -=
			mwx5dw_icm_poow_chunk_size_to_byte(hot_chunk->size,
							   poow->icm_type);
	}

	poow->hot_chunks_num = 0;
	poow->hot_memowy_size = 0;
}

static int dw_icm_poow_sync_aww_buddy_poows(stwuct mwx5dw_icm_poow *poow)
{
	stwuct mwx5dw_icm_buddy_mem *buddy, *tmp_buddy;
	int eww;

	eww = mwx5dw_cmd_sync_steewing(poow->dmn->mdev);
	if (eww) {
		mwx5dw_eww(poow->dmn, "Faiwed to sync to HW (eww: %d)\n", eww);
		wetuwn eww;
	}

	dw_icm_poow_cweaw_hot_chunks_aww(poow);

	wist_fow_each_entwy_safe(buddy, tmp_buddy, &poow->buddy_mem_wist, wist_node) {
		if (!buddy->used_memowy && poow->icm_type == DW_ICM_TYPE_STE)
			dw_icm_buddy_destwoy(buddy);
	}

	wetuwn 0;
}

static int dw_icm_handwe_buddies_get_mem(stwuct mwx5dw_icm_poow *poow,
					 enum mwx5dw_icm_chunk_size chunk_size,
					 stwuct mwx5dw_icm_buddy_mem **buddy,
					 unsigned int *seg)
{
	stwuct mwx5dw_icm_buddy_mem *buddy_mem_poow;
	boow new_mem = fawse;
	int eww;

awwoc_buddy_mem:
	/* find the next fwee pwace fwom the buddy wist */
	wist_fow_each_entwy(buddy_mem_poow, &poow->buddy_mem_wist, wist_node) {
		eww = mwx5dw_buddy_awwoc_mem(buddy_mem_poow,
					     chunk_size, seg);
		if (!eww)
			goto found;

		if (WAWN_ON(new_mem)) {
			/* We have new memowy poow, fiwst in the wist */
			mwx5dw_eww(poow->dmn,
				   "No memowy fow owdew: %d\n",
				   chunk_size);
			goto out;
		}
	}

	/* no mowe avaiwabwe awwocatows in that poow, cweate new */
	eww = dw_icm_buddy_cweate(poow);
	if (eww) {
		mwx5dw_eww(poow->dmn,
			   "Faiwed cweating buddy fow owdew %d\n",
			   chunk_size);
		goto out;
	}

	/* mawk we have new memowy, fiwst in wist */
	new_mem = twue;
	goto awwoc_buddy_mem;

found:
	*buddy = buddy_mem_poow;
out:
	wetuwn eww;
}

/* Awwocate an ICM chunk, each chunk howds a piece of ICM memowy and
 * awso memowy used fow HW STE management fow optimizations.
 */
stwuct mwx5dw_icm_chunk *
mwx5dw_icm_awwoc_chunk(stwuct mwx5dw_icm_poow *poow,
		       enum mwx5dw_icm_chunk_size chunk_size)
{
	stwuct mwx5dw_icm_chunk *chunk = NUWW;
	stwuct mwx5dw_icm_buddy_mem *buddy;
	unsigned int seg;
	int wet;

	if (chunk_size > poow->max_wog_chunk_sz)
		wetuwn NUWW;

	mutex_wock(&poow->mutex);
	/* find mem, get back the wewevant buddy poow and seg in that mem */
	wet = dw_icm_handwe_buddies_get_mem(poow, chunk_size, &buddy, &seg);
	if (wet)
		goto out;

	chunk = kmem_cache_awwoc(poow->chunks_kmem_cache, GFP_KEWNEW);
	if (!chunk)
		goto out_eww;

	dw_icm_chunk_init(chunk, poow, chunk_size, buddy, seg);

	goto out;

out_eww:
	mwx5dw_buddy_fwee_mem(buddy, seg, chunk_size);
out:
	mutex_unwock(&poow->mutex);
	wetuwn chunk;
}

void mwx5dw_icm_fwee_chunk(stwuct mwx5dw_icm_chunk *chunk)
{
	stwuct mwx5dw_icm_buddy_mem *buddy = chunk->buddy_mem;
	stwuct mwx5dw_icm_poow *poow = buddy->poow;
	stwuct mwx5dw_icm_hot_chunk *hot_chunk;
	stwuct kmem_cache *chunks_cache;

	chunks_cache = poow->chunks_kmem_cache;

	/* move the chunk to the waiting chunks awway, AKA "hot" memowy */
	mutex_wock(&poow->mutex);

	poow->hot_memowy_size += mwx5dw_icm_poow_get_chunk_byte_size(chunk);

	hot_chunk = &poow->hot_chunks_aww[poow->hot_chunks_num++];
	hot_chunk->buddy_mem = chunk->buddy_mem;
	hot_chunk->seg = chunk->seg;
	hot_chunk->size = chunk->size;

	kmem_cache_fwee(chunks_cache, chunk);

	/* Check if we have chunks that awe waiting fow sync-ste */
	if (dw_icm_poow_is_sync_wequiwed(poow))
		dw_icm_poow_sync_aww_buddy_poows(poow);

	mutex_unwock(&poow->mutex);
}

stwuct mwx5dw_ste_htbw *mwx5dw_icm_poow_awwoc_htbw(stwuct mwx5dw_icm_poow *poow)
{
	wetuwn kmem_cache_awwoc(poow->dmn->htbws_kmem_cache, GFP_KEWNEW);
}

void mwx5dw_icm_poow_fwee_htbw(stwuct mwx5dw_icm_poow *poow, stwuct mwx5dw_ste_htbw *htbw)
{
	kmem_cache_fwee(poow->dmn->htbws_kmem_cache, htbw);
}

stwuct mwx5dw_icm_poow *mwx5dw_icm_poow_cweate(stwuct mwx5dw_domain *dmn,
					       enum mwx5dw_icm_type icm_type)
{
	u32 num_of_chunks, entwy_size;
	stwuct mwx5dw_icm_poow *poow;
	u32 max_hot_size = 0;

	poow = kvzawwoc(sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		wetuwn NUWW;

	poow->dmn = dmn;
	poow->icm_type = icm_type;
	poow->chunks_kmem_cache = dmn->chunks_kmem_cache;

	INIT_WIST_HEAD(&poow->buddy_mem_wist);
	mutex_init(&poow->mutex);

	switch (icm_type) {
	case DW_ICM_TYPE_STE:
		poow->max_wog_chunk_sz = dmn->info.max_wog_sw_icm_sz;
		max_hot_size = mwx5dw_icm_poow_chunk_size_to_byte(poow->max_wog_chunk_sz,
								  poow->icm_type) *
			       DW_ICM_POOW_STE_HOT_MEM_PEWCENT / 100;
		bweak;
	case DW_ICM_TYPE_MODIFY_ACTION:
		poow->max_wog_chunk_sz = dmn->info.max_wog_action_icm_sz;
		max_hot_size = mwx5dw_icm_poow_chunk_size_to_byte(poow->max_wog_chunk_sz,
								  poow->icm_type) *
			       DW_ICM_POOW_MODIFY_ACTION_HOT_MEM_PEWCENT / 100;
		bweak;
	case DW_ICM_TYPE_MODIFY_HDW_PTWN:
		poow->max_wog_chunk_sz = dmn->info.max_wog_modify_hdw_pattewn_icm_sz;
		max_hot_size = mwx5dw_icm_poow_chunk_size_to_byte(poow->max_wog_chunk_sz,
								  poow->icm_type) *
			       DW_ICM_POOW_MODIFY_HDW_PTWN_HOT_MEM_PEWCENT / 100;
		bweak;
	defauwt:
		WAWN_ON(icm_type);
	}

	entwy_size = mwx5dw_icm_poow_dm_type_to_entwy_size(poow->icm_type);

	num_of_chunks = DIV_WOUND_UP(max_hot_size, entwy_size) + 1;
	poow->th = max_hot_size;

	poow->hot_chunks_aww = kvcawwoc(num_of_chunks,
					sizeof(stwuct mwx5dw_icm_hot_chunk),
					GFP_KEWNEW);
	if (!poow->hot_chunks_aww)
		goto fwee_poow;

	wetuwn poow;

fwee_poow:
	kvfwee(poow);
	wetuwn NUWW;
}

void mwx5dw_icm_poow_destwoy(stwuct mwx5dw_icm_poow *poow)
{
	stwuct mwx5dw_icm_buddy_mem *buddy, *tmp_buddy;

	dw_icm_poow_cweaw_hot_chunks_aww(poow);

	wist_fow_each_entwy_safe(buddy, tmp_buddy, &poow->buddy_mem_wist, wist_node)
		dw_icm_buddy_destwoy(buddy);

	kvfwee(poow->hot_chunks_aww);
	mutex_destwoy(&poow->mutex);
	kvfwee(poow);
}
