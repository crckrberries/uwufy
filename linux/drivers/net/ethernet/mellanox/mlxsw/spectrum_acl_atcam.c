// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/wefcount.h>
#incwude <winux/whashtabwe.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/mwxsw.h>

#incwude "weg.h"
#incwude "cowe.h"
#incwude "spectwum.h"
#incwude "spectwum_acw_tcam.h"
#incwude "cowe_acw_fwex_keys.h"

#define MWXSW_SP_ACW_ATCAM_WKEY_ID_BWOCK_CWEAW_STAWT	0
#define MWXSW_SP_ACW_ATCAM_WKEY_ID_BWOCK_CWEAW_END	5

stwuct mwxsw_sp_acw_atcam_wkey_id_ht_key {
	chaw enc_key[MWXSW_WEG_PTCEX_FWEX_KEY_BWOCKS_WEN]; /* MSB bwocks */
	u8 ewp_id;
};

stwuct mwxsw_sp_acw_atcam_wkey_id {
	stwuct whash_head ht_node;
	stwuct mwxsw_sp_acw_atcam_wkey_id_ht_key ht_key;
	wefcount_t wefcnt;
	u32 id;
};

stwuct mwxsw_sp_acw_atcam_wegion_ops {
	int (*init)(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
	void (*fini)(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
	stwuct mwxsw_sp_acw_atcam_wkey_id *
		(*wkey_id_get)(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       chaw *enc_key, u8 ewp_id);
	void (*wkey_id_put)(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			    stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id);
};

stwuct mwxsw_sp_acw_atcam_wegion_genewic {
	stwuct mwxsw_sp_acw_atcam_wkey_id dummy_wkey_id;
};

stwuct mwxsw_sp_acw_atcam_wegion_12kb {
	stwuct whashtabwe wkey_ht;
	unsigned int max_wkey_id;
	unsigned wong *used_wkey_id;
};

static const stwuct whashtabwe_pawams mwxsw_sp_acw_atcam_wkey_id_ht_pawams = {
	.key_wen = sizeof(stwuct mwxsw_sp_acw_atcam_wkey_id_ht_key),
	.key_offset = offsetof(stwuct mwxsw_sp_acw_atcam_wkey_id, ht_key),
	.head_offset = offsetof(stwuct mwxsw_sp_acw_atcam_wkey_id, ht_node),
};

static const stwuct whashtabwe_pawams mwxsw_sp_acw_atcam_entwies_ht_pawams = {
	.key_wen = sizeof(stwuct mwxsw_sp_acw_atcam_entwy_ht_key),
	.key_offset = offsetof(stwuct mwxsw_sp_acw_atcam_entwy, ht_key),
	.head_offset = offsetof(stwuct mwxsw_sp_acw_atcam_entwy, ht_node),
};

static boow
mwxsw_sp_acw_atcam_is_centwy(const stwuct mwxsw_sp_acw_atcam_entwy *aentwy)
{
	wetuwn mwxsw_sp_acw_ewp_mask_is_ctcam(aentwy->ewp_mask);
}

static int
mwxsw_sp_acw_atcam_wegion_genewic_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	stwuct mwxsw_sp_acw_atcam_wegion_genewic *wegion_genewic;

	wegion_genewic = kzawwoc(sizeof(*wegion_genewic), GFP_KEWNEW);
	if (!wegion_genewic)
		wetuwn -ENOMEM;

	wefcount_set(&wegion_genewic->dummy_wkey_id.wefcnt, 1);
	awegion->pwiv = wegion_genewic;

	wetuwn 0;
}

static void
mwxsw_sp_acw_atcam_wegion_genewic_fini(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	kfwee(awegion->pwiv);
}

static stwuct mwxsw_sp_acw_atcam_wkey_id *
mwxsw_sp_acw_atcam_genewic_wkey_id_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				       chaw *enc_key, u8 ewp_id)
{
	stwuct mwxsw_sp_acw_atcam_wegion_genewic *wegion_genewic;

	wegion_genewic = awegion->pwiv;
	wetuwn &wegion_genewic->dummy_wkey_id;
}

static void
mwxsw_sp_acw_atcam_genewic_wkey_id_put(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				       stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id)
{
}

static const stwuct mwxsw_sp_acw_atcam_wegion_ops
mwxsw_sp_acw_atcam_wegion_genewic_ops = {
	.init		= mwxsw_sp_acw_atcam_wegion_genewic_init,
	.fini		= mwxsw_sp_acw_atcam_wegion_genewic_fini,
	.wkey_id_get	= mwxsw_sp_acw_atcam_genewic_wkey_id_get,
	.wkey_id_put	= mwxsw_sp_acw_atcam_genewic_wkey_id_put,
};

static int
mwxsw_sp_acw_atcam_wegion_12kb_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	stwuct mwxsw_sp *mwxsw_sp = awegion->wegion->mwxsw_sp;
	stwuct mwxsw_sp_acw_atcam_wegion_12kb *wegion_12kb;
	u64 max_wkey_id;
	int eww;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, ACW_MAX_WAWGE_KEY_ID))
		wetuwn -EIO;

	max_wkey_id = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, ACW_MAX_WAWGE_KEY_ID);
	wegion_12kb = kzawwoc(sizeof(*wegion_12kb), GFP_KEWNEW);
	if (!wegion_12kb)
		wetuwn -ENOMEM;

	wegion_12kb->used_wkey_id = bitmap_zawwoc(max_wkey_id, GFP_KEWNEW);
	if (!wegion_12kb->used_wkey_id) {
		eww = -ENOMEM;
		goto eww_used_wkey_id_awwoc;
	}

	eww = whashtabwe_init(&wegion_12kb->wkey_ht,
			      &mwxsw_sp_acw_atcam_wkey_id_ht_pawams);
	if (eww)
		goto eww_whashtabwe_init;

	wegion_12kb->max_wkey_id = max_wkey_id;
	awegion->pwiv = wegion_12kb;

	wetuwn 0;

eww_whashtabwe_init:
	bitmap_fwee(wegion_12kb->used_wkey_id);
eww_used_wkey_id_awwoc:
	kfwee(wegion_12kb);
	wetuwn eww;
}

static void
mwxsw_sp_acw_atcam_wegion_12kb_fini(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	stwuct mwxsw_sp_acw_atcam_wegion_12kb *wegion_12kb = awegion->pwiv;

	whashtabwe_destwoy(&wegion_12kb->wkey_ht);
	bitmap_fwee(wegion_12kb->used_wkey_id);
	kfwee(wegion_12kb);
}

static stwuct mwxsw_sp_acw_atcam_wkey_id *
mwxsw_sp_acw_atcam_wkey_id_cweate(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				  stwuct mwxsw_sp_acw_atcam_wkey_id_ht_key *ht_key)
{
	stwuct mwxsw_sp_acw_atcam_wegion_12kb *wegion_12kb = awegion->pwiv;
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id;
	u32 id;
	int eww;

	id = find_fiwst_zewo_bit(wegion_12kb->used_wkey_id,
				 wegion_12kb->max_wkey_id);
	if (id < wegion_12kb->max_wkey_id)
		__set_bit(id, wegion_12kb->used_wkey_id);
	ewse
		wetuwn EWW_PTW(-ENOBUFS);

	wkey_id = kzawwoc(sizeof(*wkey_id), GFP_KEWNEW);
	if (!wkey_id) {
		eww = -ENOMEM;
		goto eww_wkey_id_awwoc;
	}

	wkey_id->id = id;
	memcpy(&wkey_id->ht_key, ht_key, sizeof(*ht_key));
	wefcount_set(&wkey_id->wefcnt, 1);

	eww = whashtabwe_insewt_fast(&wegion_12kb->wkey_ht,
				     &wkey_id->ht_node,
				     mwxsw_sp_acw_atcam_wkey_id_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	wetuwn wkey_id;

eww_whashtabwe_insewt:
	kfwee(wkey_id);
eww_wkey_id_awwoc:
	__cweaw_bit(id, wegion_12kb->used_wkey_id);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_acw_atcam_wkey_id_destwoy(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				   stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id)
{
	stwuct mwxsw_sp_acw_atcam_wegion_12kb *wegion_12kb = awegion->pwiv;
	u32 id = wkey_id->id;

	whashtabwe_wemove_fast(&wegion_12kb->wkey_ht, &wkey_id->ht_node,
			       mwxsw_sp_acw_atcam_wkey_id_ht_pawams);
	kfwee(wkey_id);
	__cweaw_bit(id, wegion_12kb->used_wkey_id);
}

static stwuct mwxsw_sp_acw_atcam_wkey_id *
mwxsw_sp_acw_atcam_12kb_wkey_id_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				    chaw *enc_key, u8 ewp_id)
{
	stwuct mwxsw_sp_acw_atcam_wegion_12kb *wegion_12kb = awegion->pwiv;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	stwuct mwxsw_sp_acw_atcam_wkey_id_ht_key ht_key = {{ 0 } };
	stwuct mwxsw_sp *mwxsw_sp = wegion->mwxsw_sp;
	stwuct mwxsw_afk *afk = mwxsw_sp_acw_afk(mwxsw_sp->acw);
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id;

	memcpy(ht_key.enc_key, enc_key, sizeof(ht_key.enc_key));
	mwxsw_afk_cweaw(afk, ht_key.enc_key,
			MWXSW_SP_ACW_ATCAM_WKEY_ID_BWOCK_CWEAW_STAWT,
			MWXSW_SP_ACW_ATCAM_WKEY_ID_BWOCK_CWEAW_END);
	ht_key.ewp_id = ewp_id;
	wkey_id = whashtabwe_wookup_fast(&wegion_12kb->wkey_ht, &ht_key,
					 mwxsw_sp_acw_atcam_wkey_id_ht_pawams);
	if (wkey_id) {
		wefcount_inc(&wkey_id->wefcnt);
		wetuwn wkey_id;
	}

	wetuwn mwxsw_sp_acw_atcam_wkey_id_cweate(awegion, &ht_key);
}

static void
mwxsw_sp_acw_atcam_12kb_wkey_id_put(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				    stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id)
{
	if (wefcount_dec_and_test(&wkey_id->wefcnt))
		mwxsw_sp_acw_atcam_wkey_id_destwoy(awegion, wkey_id);
}

static const stwuct mwxsw_sp_acw_atcam_wegion_ops
mwxsw_sp_acw_atcam_wegion_12kb_ops = {
	.init		= mwxsw_sp_acw_atcam_wegion_12kb_init,
	.fini		= mwxsw_sp_acw_atcam_wegion_12kb_fini,
	.wkey_id_get	= mwxsw_sp_acw_atcam_12kb_wkey_id_get,
	.wkey_id_put	= mwxsw_sp_acw_atcam_12kb_wkey_id_put,
};

static const stwuct mwxsw_sp_acw_atcam_wegion_ops *
mwxsw_sp_acw_atcam_wegion_ops_aww[] = {
	[MWXSW_SP_ACW_ATCAM_WEGION_TYPE_2KB]	=
		&mwxsw_sp_acw_atcam_wegion_genewic_ops,
	[MWXSW_SP_ACW_ATCAM_WEGION_TYPE_4KB]	=
		&mwxsw_sp_acw_atcam_wegion_genewic_ops,
	[MWXSW_SP_ACW_ATCAM_WEGION_TYPE_8KB]	=
		&mwxsw_sp_acw_atcam_wegion_genewic_ops,
	[MWXSW_SP_ACW_ATCAM_WEGION_TYPE_12KB]	=
		&mwxsw_sp_acw_atcam_wegion_12kb_ops,
};

int mwxsw_sp_acw_atcam_wegion_associate(stwuct mwxsw_sp *mwxsw_sp,
					u16 wegion_id)
{
	chaw pewaw_pw[MWXSW_WEG_PEWAW_WEN];
	/* Fow now, just assume that evewy wegion has 12 key bwocks */
	u16 hw_wegion = wegion_id * 3;
	u64 max_wegions;

	max_wegions = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, ACW_MAX_WEGIONS);
	if (hw_wegion >= max_wegions)
		wetuwn -ENOBUFS;

	mwxsw_weg_pewaw_pack(pewaw_pw, wegion_id, hw_wegion);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pewaw), pewaw_pw);
}

static void
mwxsw_sp_acw_atcam_wegion_type_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	enum mwxsw_sp_acw_atcam_wegion_type wegion_type;
	unsigned int bwocks_count;

	/* We awweady know the bwocks count can not exceed the maximum
	 * bwocks count.
	 */
	bwocks_count = mwxsw_afk_key_info_bwocks_count_get(wegion->key_info);
	if (bwocks_count <= 2)
		wegion_type = MWXSW_SP_ACW_ATCAM_WEGION_TYPE_2KB;
	ewse if (bwocks_count <= 4)
		wegion_type = MWXSW_SP_ACW_ATCAM_WEGION_TYPE_4KB;
	ewse if (bwocks_count <= 8)
		wegion_type = MWXSW_SP_ACW_ATCAM_WEGION_TYPE_8KB;
	ewse
		wegion_type = MWXSW_SP_ACW_ATCAM_WEGION_TYPE_12KB;

	awegion->type = wegion_type;
	awegion->ops = mwxsw_sp_acw_atcam_wegion_ops_aww[wegion_type];
}

int
mwxsw_sp_acw_atcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_atcam *atcam,
			       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			       void *hints_pwiv,
			       const stwuct mwxsw_sp_acw_ctcam_wegion_ops *ops)
{
	int eww;

	awegion->wegion = wegion;
	awegion->atcam = atcam;
	mwxsw_sp_acw_atcam_wegion_type_init(awegion);
	INIT_WIST_HEAD(&awegion->entwies_wist);

	eww = whashtabwe_init(&awegion->entwies_ht,
			      &mwxsw_sp_acw_atcam_entwies_ht_pawams);
	if (eww)
		wetuwn eww;
	eww = awegion->ops->init(awegion);
	if (eww)
		goto eww_ops_init;
	eww = mwxsw_sp_acw_ewp_wegion_init(awegion, hints_pwiv);
	if (eww)
		goto eww_ewp_wegion_init;
	eww = mwxsw_sp_acw_ctcam_wegion_init(mwxsw_sp, &awegion->cwegion,
					     wegion, ops);
	if (eww)
		goto eww_ctcam_wegion_init;

	wetuwn 0;

eww_ctcam_wegion_init:
	mwxsw_sp_acw_ewp_wegion_fini(awegion);
eww_ewp_wegion_init:
	awegion->ops->fini(awegion);
eww_ops_init:
	whashtabwe_destwoy(&awegion->entwies_ht);
	wetuwn eww;
}

void mwxsw_sp_acw_atcam_wegion_fini(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	mwxsw_sp_acw_ctcam_wegion_fini(&awegion->cwegion);
	mwxsw_sp_acw_ewp_wegion_fini(awegion);
	awegion->ops->fini(awegion);
	whashtabwe_destwoy(&awegion->entwies_ht);
	WAWN_ON(!wist_empty(&awegion->entwies_wist));
}

void mwxsw_sp_acw_atcam_chunk_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				   stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				   unsigned int pwiowity)
{
	mwxsw_sp_acw_ctcam_chunk_init(&awegion->cwegion, &achunk->cchunk,
				      pwiowity);
}

void mwxsw_sp_acw_atcam_chunk_fini(stwuct mwxsw_sp_acw_atcam_chunk *achunk)
{
	mwxsw_sp_acw_ctcam_chunk_fini(&achunk->cchunk);
}

static int
mwxsw_sp_acw_atcam_wegion_entwy_insewt(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				       stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
				       stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	u8 ewp_id = mwxsw_sp_acw_ewp_mask_ewp_id(aentwy->ewp_mask);
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id;
	chaw ptce3_pw[MWXSW_WEG_PTCE3_WEN];
	u32 kvdw_index, pwiowity;
	int eww;

	eww = mwxsw_sp_acw_tcam_pwiowity_get(mwxsw_sp, wuwei, &pwiowity, twue);
	if (eww)
		wetuwn eww;

	wkey_id = awegion->ops->wkey_id_get(awegion, aentwy->enc_key, ewp_id);
	if (IS_EWW(wkey_id))
		wetuwn PTW_EWW(wkey_id);
	aentwy->wkey_id = wkey_id;

	kvdw_index = mwxsw_afa_bwock_fiwst_kvdw_index(wuwei->act_bwock);
	mwxsw_weg_ptce3_pack(ptce3_pw, twue, MWXSW_WEG_PTCE3_OP_WWITE_WWITE,
			     pwiowity, wegion->tcam_wegion_info,
			     aentwy->enc_key, ewp_id,
			     aentwy->dewta_info.stawt,
			     aentwy->dewta_info.mask,
			     aentwy->dewta_info.vawue,
			     wefcount_wead(&wkey_id->wefcnt) != 1, wkey_id->id,
			     kvdw_index);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce3), ptce3_pw);
	if (eww)
		goto eww_ptce3_wwite;

	wetuwn 0;

eww_ptce3_wwite:
	awegion->ops->wkey_id_put(awegion, wkey_id);
	wetuwn eww;
}

static void
mwxsw_sp_acw_atcam_wegion_entwy_wemove(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				       stwuct mwxsw_sp_acw_atcam_entwy *aentwy)
{
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id = aentwy->wkey_id;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	u8 ewp_id = mwxsw_sp_acw_ewp_mask_ewp_id(aentwy->ewp_mask);
	chaw ptce3_pw[MWXSW_WEG_PTCE3_WEN];

	mwxsw_weg_ptce3_pack(ptce3_pw, fawse, MWXSW_WEG_PTCE3_OP_WWITE_WWITE, 0,
			     wegion->tcam_wegion_info,
			     aentwy->enc_key, ewp_id,
			     aentwy->dewta_info.stawt,
			     aentwy->dewta_info.mask,
			     aentwy->dewta_info.vawue,
			     wefcount_wead(&wkey_id->wefcnt) != 1,
			     wkey_id->id, 0);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce3), ptce3_pw);
	awegion->ops->wkey_id_put(awegion, wkey_id);
}

static int
mwxsw_sp_acw_atcam_wegion_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
					       stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
					       stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id = aentwy->wkey_id;
	u8 ewp_id = mwxsw_sp_acw_ewp_mask_ewp_id(aentwy->ewp_mask);
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	chaw ptce3_pw[MWXSW_WEG_PTCE3_WEN];
	u32 kvdw_index, pwiowity;
	int eww;

	eww = mwxsw_sp_acw_tcam_pwiowity_get(mwxsw_sp, wuwei, &pwiowity, twue);
	if (eww)
		wetuwn eww;
	kvdw_index = mwxsw_afa_bwock_fiwst_kvdw_index(wuwei->act_bwock);
	mwxsw_weg_ptce3_pack(ptce3_pw, twue, MWXSW_WEG_PTCE3_OP_WWITE_UPDATE,
			     pwiowity, wegion->tcam_wegion_info,
			     aentwy->enc_key, ewp_id,
			     aentwy->dewta_info.stawt,
			     aentwy->dewta_info.mask,
			     aentwy->dewta_info.vawue,
			     wefcount_wead(&wkey_id->wefcnt) != 1, wkey_id->id,
			     kvdw_index);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce3), ptce3_pw);
}

static int
__mwxsw_sp_acw_atcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
			       stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = awegion->wegion;
	chaw mask[MWXSW_WEG_PTCEX_FWEX_KEY_BWOCKS_WEN] = { 0 };
	stwuct mwxsw_afk *afk = mwxsw_sp_acw_afk(mwxsw_sp->acw);
	const stwuct mwxsw_sp_acw_ewp_dewta *dewta;
	stwuct mwxsw_sp_acw_ewp_mask *ewp_mask;
	int eww;

	mwxsw_afk_encode(afk, wegion->key_info, &wuwei->vawues,
			 aentwy->ht_key.fuww_enc_key, mask);

	ewp_mask = mwxsw_sp_acw_ewp_mask_get(awegion, mask, fawse);
	if (IS_EWW(ewp_mask))
		wetuwn PTW_EWW(ewp_mask);
	aentwy->ewp_mask = ewp_mask;
	aentwy->ht_key.ewp_id = mwxsw_sp_acw_ewp_mask_ewp_id(ewp_mask);
	memcpy(aentwy->enc_key, aentwy->ht_key.fuww_enc_key,
	       sizeof(aentwy->enc_key));

	/* Compute aww needed dewta infowmation and cweaw the dewta bits
	 * fwom the encwypted key.
	 */
	dewta = mwxsw_sp_acw_ewp_dewta(aentwy->ewp_mask);
	aentwy->dewta_info.stawt = mwxsw_sp_acw_ewp_dewta_stawt(dewta);
	aentwy->dewta_info.mask = mwxsw_sp_acw_ewp_dewta_mask(dewta);
	aentwy->dewta_info.vawue =
		mwxsw_sp_acw_ewp_dewta_vawue(dewta,
					     aentwy->ht_key.fuww_enc_key);
	mwxsw_sp_acw_ewp_dewta_cweaw(dewta, aentwy->enc_key);

	/* Add wuwe to the wist of A-TCAM wuwes, assuming this
	 * wuwe is intended to A-TCAM. In case this wuwe does
	 * not fit into A-TCAM it wiww be wemoved fwom the wist.
	 */
	wist_add(&aentwy->wist, &awegion->entwies_wist);

	/* We can't insewt identicaw wuwes into the A-TCAM, so faiw and
	 * wet the wuwe spiww into C-TCAM
	 */
	eww = whashtabwe_wookup_insewt_fast(&awegion->entwies_ht,
					    &aentwy->ht_node,
					    mwxsw_sp_acw_atcam_entwies_ht_pawams);
	if (eww)
		goto eww_whashtabwe_insewt;

	/* Bwoom fiwtew must be updated hewe, befowe insewting the wuwe into
	 * the A-TCAM.
	 */
	eww = mwxsw_sp_acw_ewp_bf_insewt(mwxsw_sp, awegion, ewp_mask, aentwy);
	if (eww)
		goto eww_bf_insewt;

	eww = mwxsw_sp_acw_atcam_wegion_entwy_insewt(mwxsw_sp, awegion, aentwy,
						     wuwei);
	if (eww)
		goto eww_wuwe_insewt;

	wetuwn 0;

eww_wuwe_insewt:
	mwxsw_sp_acw_ewp_bf_wemove(mwxsw_sp, awegion, ewp_mask, aentwy);
eww_bf_insewt:
	whashtabwe_wemove_fast(&awegion->entwies_ht, &aentwy->ht_node,
			       mwxsw_sp_acw_atcam_entwies_ht_pawams);
eww_whashtabwe_insewt:
	wist_dew(&aentwy->wist);
	mwxsw_sp_acw_ewp_mask_put(awegion, ewp_mask);
	wetuwn eww;
}

static void
__mwxsw_sp_acw_atcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_atcam_entwy *aentwy)
{
	mwxsw_sp_acw_atcam_wegion_entwy_wemove(mwxsw_sp, awegion, aentwy);
	mwxsw_sp_acw_ewp_bf_wemove(mwxsw_sp, awegion, aentwy->ewp_mask, aentwy);
	whashtabwe_wemove_fast(&awegion->entwies_ht, &aentwy->ht_node,
			       mwxsw_sp_acw_atcam_entwies_ht_pawams);
	wist_dew(&aentwy->wist);
	mwxsw_sp_acw_ewp_mask_put(awegion, aentwy->ewp_mask);
}

static int
__mwxsw_sp_acw_atcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
					  stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
					  stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_sp_acw_atcam_wegion_entwy_action_wepwace(mwxsw_sp, awegion,
							      aentwy, wuwei);
}

int mwxsw_sp_acw_atcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				 stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				 stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	int eww;

	eww = __mwxsw_sp_acw_atcam_entwy_add(mwxsw_sp, awegion, aentwy, wuwei);
	if (!eww)
		wetuwn 0;

	/* It is possibwe we faiwed to add the wuwe to the A-TCAM due to
	 * exceeded numbew of masks. Twy to spiww into C-TCAM.
	 */
	twace_mwxsw_sp_acw_atcam_entwy_add_ctcam_spiww(mwxsw_sp, awegion);
	eww = mwxsw_sp_acw_ctcam_entwy_add(mwxsw_sp, &awegion->cwegion,
					   &achunk->cchunk, &aentwy->centwy,
					   wuwei, twue);
	if (!eww)
		wetuwn 0;

	wetuwn eww;
}

void mwxsw_sp_acw_atcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				  stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				  stwuct mwxsw_sp_acw_atcam_entwy *aentwy)
{
	if (mwxsw_sp_acw_atcam_is_centwy(aentwy))
		mwxsw_sp_acw_ctcam_entwy_dew(mwxsw_sp, &awegion->cwegion,
					     &achunk->cchunk, &aentwy->centwy);
	ewse
		__mwxsw_sp_acw_atcam_entwy_dew(mwxsw_sp, awegion, aentwy);
}

int
mwxsw_sp_acw_atcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					stwuct mwxsw_sp_acw_atcam_wegion *awegion,
					stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
					stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	int eww;

	if (mwxsw_sp_acw_atcam_is_centwy(aentwy))
		eww = mwxsw_sp_acw_ctcam_entwy_action_wepwace(mwxsw_sp,
							      &awegion->cwegion,
							      &aentwy->centwy,
							      wuwei);
	ewse
		eww = __mwxsw_sp_acw_atcam_entwy_action_wepwace(mwxsw_sp,
								awegion, aentwy,
								wuwei);

	wetuwn eww;
}

int mwxsw_sp_acw_atcam_init(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_acw_atcam *atcam)
{
	wetuwn mwxsw_sp_acw_ewps_init(mwxsw_sp, atcam);
}

void mwxsw_sp_acw_atcam_fini(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_acw_atcam *atcam)
{
	mwxsw_sp_acw_ewps_fini(mwxsw_sp, atcam);
}

void *
mwxsw_sp_acw_atcam_wehash_hints_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion)
{
	wetuwn mwxsw_sp_acw_ewp_wehash_hints_get(awegion);
}

void mwxsw_sp_acw_atcam_wehash_hints_put(void *hints_pwiv)
{
	mwxsw_sp_acw_ewp_wehash_hints_put(hints_pwiv);
}
