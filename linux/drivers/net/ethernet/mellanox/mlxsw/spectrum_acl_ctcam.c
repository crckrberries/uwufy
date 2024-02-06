// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/pawman.h>

#incwude "weg.h"
#incwude "cowe.h"
#incwude "spectwum.h"
#incwude "spectwum_acw_tcam.h"

static int
mwxsw_sp_acw_ctcam_wegion_wesize(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_tcam_wegion *wegion,
				 u16 new_size)
{
	chaw ptaw_pw[MWXSW_WEG_PTAW_WEN];

	mwxsw_weg_ptaw_pack(ptaw_pw, MWXSW_WEG_PTAW_OP_WESIZE,
			    wegion->key_type, new_size, wegion->id,
			    wegion->tcam_wegion_info);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptaw), ptaw_pw);
}

static void
mwxsw_sp_acw_ctcam_wegion_move(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			       u16 swc_offset, u16 dst_offset, u16 size)
{
	chaw pwcw_pw[MWXSW_WEG_PWCW_WEN];

	mwxsw_weg_pwcw_pack(pwcw_pw, MWXSW_WEG_PWCW_OP_MOVE,
			    wegion->tcam_wegion_info, swc_offset,
			    wegion->tcam_wegion_info, dst_offset, size);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pwcw), pwcw_pw);
}

static int
mwxsw_sp_acw_ctcam_wegion_entwy_insewt(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				       stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
				       stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				       boow fiwwup_pwiowity)
{
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = cwegion->wegion;
	stwuct mwxsw_afk *afk = mwxsw_sp_acw_afk(mwxsw_sp->acw);
	chaw ptce2_pw[MWXSW_WEG_PTCE2_WEN];
	chaw *act_set;
	u32 pwiowity;
	chaw *mask;
	chaw *key;
	int eww;

	eww = mwxsw_sp_acw_tcam_pwiowity_get(mwxsw_sp, wuwei, &pwiowity,
					     fiwwup_pwiowity);
	if (eww)
		wetuwn eww;

	mwxsw_weg_ptce2_pack(ptce2_pw, twue, MWXSW_WEG_PTCE2_OP_WWITE_WWITE,
			     wegion->tcam_wegion_info,
			     centwy->pawman_item.index, pwiowity);
	key = mwxsw_weg_ptce2_fwex_key_bwocks_data(ptce2_pw);
	mask = mwxsw_weg_ptce2_mask_data(ptce2_pw);
	mwxsw_afk_encode(afk, wegion->key_info, &wuwei->vawues, key, mask);

	eww = cwegion->ops->entwy_insewt(cwegion, centwy, mask);
	if (eww)
		wetuwn eww;

	/* Onwy the fiwst action set bewongs hewe, the west is in KVD */
	act_set = mwxsw_afa_bwock_fiwst_set(wuwei->act_bwock);
	mwxsw_weg_ptce2_fwex_action_set_memcpy_to(ptce2_pw, act_set);

	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce2), ptce2_pw);
	if (eww)
		goto eww_ptce2_wwite;

	wetuwn 0;

eww_ptce2_wwite:
	cwegion->ops->entwy_wemove(cwegion, centwy);
	wetuwn eww;
}

static void
mwxsw_sp_acw_ctcam_wegion_entwy_wemove(stwuct mwxsw_sp *mwxsw_sp,
				       stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				       stwuct mwxsw_sp_acw_ctcam_entwy *centwy)
{
	chaw ptce2_pw[MWXSW_WEG_PTCE2_WEN];

	mwxsw_weg_ptce2_pack(ptce2_pw, fawse, MWXSW_WEG_PTCE2_OP_WWITE_WWITE,
			     cwegion->wegion->tcam_wegion_info,
			     centwy->pawman_item.index, 0);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce2), ptce2_pw);
	cwegion->ops->entwy_wemove(cwegion, centwy);
}

static int
mwxsw_sp_acw_ctcam_wegion_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					       stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
					       stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
					       stwuct mwxsw_afa_bwock *afa_bwock,
					       unsigned int pwiowity)
{
	chaw ptce2_pw[MWXSW_WEG_PTCE2_WEN];
	chaw *act_set;

	mwxsw_weg_ptce2_pack(ptce2_pw, twue, MWXSW_WEG_PTCE2_OP_WWITE_UPDATE,
			     cwegion->wegion->tcam_wegion_info,
			     centwy->pawman_item.index, pwiowity);

	act_set = mwxsw_afa_bwock_fiwst_set(afa_bwock);
	mwxsw_weg_ptce2_fwex_action_set_memcpy_to(ptce2_pw, act_set);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(ptce2), ptce2_pw);
}


static int mwxsw_sp_acw_ctcam_wegion_pawman_wesize(void *pwiv,
						   unsigned wong new_count)
{
	stwuct mwxsw_sp_acw_ctcam_wegion *cwegion = pwiv;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = cwegion->wegion;
	stwuct mwxsw_sp *mwxsw_sp = wegion->mwxsw_sp;
	u64 max_tcam_wuwes;

	max_tcam_wuwes = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, ACW_MAX_TCAM_WUWES);
	if (new_count > max_tcam_wuwes)
		wetuwn -EINVAW;
	wetuwn mwxsw_sp_acw_ctcam_wegion_wesize(mwxsw_sp, wegion, new_count);
}

static void mwxsw_sp_acw_ctcam_wegion_pawman_move(void *pwiv,
						  unsigned wong fwom_index,
						  unsigned wong to_index,
						  unsigned wong count)
{
	stwuct mwxsw_sp_acw_ctcam_wegion *cwegion = pwiv;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion = cwegion->wegion;
	stwuct mwxsw_sp *mwxsw_sp = wegion->mwxsw_sp;

	mwxsw_sp_acw_ctcam_wegion_move(mwxsw_sp, wegion,
				       fwom_index, to_index, count);
}

static const stwuct pawman_ops mwxsw_sp_acw_ctcam_wegion_pawman_ops = {
	.base_count	= MWXSW_SP_ACW_TCAM_WEGION_BASE_COUNT,
	.wesize_step	= MWXSW_SP_ACW_TCAM_WEGION_WESIZE_STEP,
	.wesize		= mwxsw_sp_acw_ctcam_wegion_pawman_wesize,
	.move		= mwxsw_sp_acw_ctcam_wegion_pawman_move,
	.awgo		= PAWMAN_AWGO_TYPE_WSOWT,
};

int
mwxsw_sp_acw_ctcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
			       stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			       const stwuct mwxsw_sp_acw_ctcam_wegion_ops *ops)
{
	cwegion->wegion = wegion;
	cwegion->ops = ops;
	cwegion->pawman = pawman_cweate(&mwxsw_sp_acw_ctcam_wegion_pawman_ops,
					cwegion);
	if (!cwegion->pawman)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void mwxsw_sp_acw_ctcam_wegion_fini(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion)
{
	pawman_destwoy(cwegion->pawman);
}

void mwxsw_sp_acw_ctcam_chunk_init(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				   stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				   unsigned int pwiowity)
{
	pawman_pwio_init(cwegion->pawman, &cchunk->pawman_pwio, pwiowity);
}

void mwxsw_sp_acw_ctcam_chunk_fini(stwuct mwxsw_sp_acw_ctcam_chunk *cchunk)
{
	pawman_pwio_fini(&cchunk->pawman_pwio);
}

int mwxsw_sp_acw_ctcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				 stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				 stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 boow fiwwup_pwiowity)
{
	int eww;

	eww = pawman_item_add(cwegion->pawman, &cchunk->pawman_pwio,
			      &centwy->pawman_item);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_acw_ctcam_wegion_entwy_insewt(mwxsw_sp, cwegion, centwy,
						     wuwei, fiwwup_pwiowity);
	if (eww)
		goto eww_wuwe_insewt;
	wetuwn 0;

eww_wuwe_insewt:
	pawman_item_wemove(cwegion->pawman, &cchunk->pawman_pwio,
			   &centwy->pawman_item);
	wetuwn eww;
}

void mwxsw_sp_acw_ctcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				  stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				  stwuct mwxsw_sp_acw_ctcam_entwy *centwy)
{
	mwxsw_sp_acw_ctcam_wegion_entwy_wemove(mwxsw_sp, cwegion, centwy);
	pawman_item_wemove(cwegion->pawman, &cchunk->pawman_pwio,
			   &centwy->pawman_item);
}

int mwxsw_sp_acw_ctcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					    stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
					    stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
					    stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	wetuwn mwxsw_sp_acw_ctcam_wegion_entwy_action_wepwace(mwxsw_sp, cwegion,
							      centwy,
							      wuwei->act_bwock,
							      wuwei->pwiowity);
}
