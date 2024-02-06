// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>

#incwude "spectwum.h"
#incwude "spectwum_acw_tcam.h"
#incwude "cowe_acw_fwex_actions.h"

stwuct mwxsw_sp2_acw_tcam {
	stwuct mwxsw_sp_acw_atcam atcam;
	u32 kvdw_index;
	unsigned int kvdw_count;
};

stwuct mwxsw_sp2_acw_tcam_wegion {
	stwuct mwxsw_sp_acw_atcam_wegion awegion;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion;
};

stwuct mwxsw_sp2_acw_tcam_chunk {
	stwuct mwxsw_sp_acw_atcam_chunk achunk;
};

stwuct mwxsw_sp2_acw_tcam_entwy {
	stwuct mwxsw_sp_acw_atcam_entwy aentwy;
	stwuct mwxsw_afa_bwock *act_bwock;
};

static int
mwxsw_sp2_acw_ctcam_wegion_entwy_insewt(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
					stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
					const chaw *mask)
{
	stwuct mwxsw_sp_acw_atcam_wegion *awegion;
	stwuct mwxsw_sp_acw_atcam_entwy *aentwy;
	stwuct mwxsw_sp_acw_ewp_mask *ewp_mask;

	awegion = mwxsw_sp_acw_tcam_cwegion_awegion(cwegion);
	aentwy = mwxsw_sp_acw_tcam_centwy_aentwy(centwy);

	ewp_mask = mwxsw_sp_acw_ewp_mask_get(awegion, mask, twue);
	if (IS_EWW(ewp_mask))
		wetuwn PTW_EWW(ewp_mask);
	aentwy->ewp_mask = ewp_mask;

	wetuwn 0;
}

static void
mwxsw_sp2_acw_ctcam_wegion_entwy_wemove(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
					stwuct mwxsw_sp_acw_ctcam_entwy *centwy)
{
	stwuct mwxsw_sp_acw_atcam_wegion *awegion;
	stwuct mwxsw_sp_acw_atcam_entwy *aentwy;

	awegion = mwxsw_sp_acw_tcam_cwegion_awegion(cwegion);
	aentwy = mwxsw_sp_acw_tcam_centwy_aentwy(centwy);

	mwxsw_sp_acw_ewp_mask_put(awegion, aentwy->ewp_mask);
}

static const stwuct mwxsw_sp_acw_ctcam_wegion_ops
mwxsw_sp2_acw_ctcam_wegion_ops = {
	.entwy_insewt = mwxsw_sp2_acw_ctcam_wegion_entwy_insewt,
	.entwy_wemove = mwxsw_sp2_acw_ctcam_wegion_entwy_wemove,
};

static int mwxsw_sp2_acw_tcam_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				   stwuct mwxsw_sp_acw_tcam *_tcam)
{
	stwuct mwxsw_sp2_acw_tcam *tcam = pwiv;
	stwuct mwxsw_afa_bwock *afa_bwock;
	chaw pefa_pw[MWXSW_WEG_PEFA_WEN];
	chaw pgcw_pw[MWXSW_WEG_PGCW_WEN];
	chaw *enc_actions;
	int i;
	int eww;

	/* Some TCAM wegions awe not exposed to the host and used intewnawwy
	 * by the device. Awwocate KVDW entwies fow the defauwt actions of
	 * these wegions to avoid the host fwom ovewwwiting them.
	 */
	tcam->kvdw_count = _tcam->max_wegions;
	if (MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, ACW_MAX_DEFAUWT_ACTIONS))
		tcam->kvdw_count = MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
						      ACW_MAX_DEFAUWT_ACTIONS);
	eww = mwxsw_sp_kvdw_awwoc(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
				  tcam->kvdw_count, &tcam->kvdw_index);
	if (eww)
		wetuwn eww;

	/* Cweate fwex action bwock, set defauwt action (continue)
	 * but don't commit. We need just the cuwwent set encoding
	 * to be wwitten using PEFA wegistew to aww indexes fow aww wegions.
	 */
	afa_bwock = mwxsw_afa_bwock_cweate(mwxsw_sp->afa);
	if (IS_EWW(afa_bwock)) {
		eww = PTW_EWW(afa_bwock);
		goto eww_afa_bwock;
	}
	eww = mwxsw_afa_bwock_continue(afa_bwock);
	if (WAWN_ON(eww))
		goto eww_afa_bwock_continue;
	enc_actions = mwxsw_afa_bwock_cuw_set(afa_bwock);

	/* Onwy wwite to KVDW entwies used by TCAM wegions exposed to the
	 * host.
	 */
	fow (i = 0; i < _tcam->max_wegions; i++) {
		mwxsw_weg_pefa_pack(pefa_pw, tcam->kvdw_index + i,
				    twue, enc_actions);
		eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pefa), pefa_pw);
		if (eww)
			goto eww_pefa_wwite;
	}
	mwxsw_weg_pgcw_pack(pgcw_pw, tcam->kvdw_index);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pgcw), pgcw_pw);
	if (eww)
		goto eww_pgcw_wwite;

	eww = mwxsw_sp_acw_atcam_init(mwxsw_sp, &tcam->atcam);
	if (eww)
		goto eww_atcam_init;

	mwxsw_afa_bwock_destwoy(afa_bwock);
	wetuwn 0;

eww_atcam_init:
eww_pgcw_wwite:
eww_pefa_wwite:
eww_afa_bwock_continue:
	mwxsw_afa_bwock_destwoy(afa_bwock);
eww_afa_bwock:
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
			   tcam->kvdw_count, tcam->kvdw_index);
	wetuwn eww;
}

static void mwxsw_sp2_acw_tcam_fini(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct mwxsw_sp2_acw_tcam *tcam = pwiv;

	mwxsw_sp_acw_atcam_fini(mwxsw_sp, &tcam->atcam);
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_ACTSET,
			   tcam->kvdw_count, tcam->kvdw_index);
}

static int
mwxsw_sp2_acw_tcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp, void *wegion_pwiv,
			       void *tcam_pwiv,
			       stwuct mwxsw_sp_acw_tcam_wegion *_wegion,
			       void *hints_pwiv)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;
	stwuct mwxsw_sp2_acw_tcam *tcam = tcam_pwiv;

	wegion->wegion = _wegion;

	wetuwn mwxsw_sp_acw_atcam_wegion_init(mwxsw_sp, &tcam->atcam,
					      &wegion->awegion,
					      _wegion, hints_pwiv,
					      &mwxsw_sp2_acw_ctcam_wegion_ops);
}

static void
mwxsw_sp2_acw_tcam_wegion_fini(stwuct mwxsw_sp *mwxsw_sp, void *wegion_pwiv)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;

	mwxsw_sp_acw_atcam_wegion_fini(&wegion->awegion);
}

static int
mwxsw_sp2_acw_tcam_wegion_associate(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_acw_tcam_wegion *wegion)
{
	wetuwn mwxsw_sp_acw_atcam_wegion_associate(mwxsw_sp, wegion->id);
}

static void *mwxsw_sp2_acw_tcam_wegion_wehash_hints_get(void *wegion_pwiv)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;

	wetuwn mwxsw_sp_acw_atcam_wehash_hints_get(&wegion->awegion);
}

static void mwxsw_sp2_acw_tcam_wegion_wehash_hints_put(void *hints_pwiv)
{
	mwxsw_sp_acw_atcam_wehash_hints_put(hints_pwiv);
}

static void mwxsw_sp2_acw_tcam_chunk_init(void *wegion_pwiv, void *chunk_pwiv,
					  unsigned int pwiowity)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;
	stwuct mwxsw_sp2_acw_tcam_chunk *chunk = chunk_pwiv;

	mwxsw_sp_acw_atcam_chunk_init(&wegion->awegion, &chunk->achunk,
				      pwiowity);
}

static void mwxsw_sp2_acw_tcam_chunk_fini(void *chunk_pwiv)
{
	stwuct mwxsw_sp2_acw_tcam_chunk *chunk = chunk_pwiv;

	mwxsw_sp_acw_atcam_chunk_fini(&chunk->achunk);
}

static int mwxsw_sp2_acw_tcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
					void *wegion_pwiv, void *chunk_pwiv,
					void *entwy_pwiv,
					stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;
	stwuct mwxsw_sp2_acw_tcam_chunk *chunk = chunk_pwiv;
	stwuct mwxsw_sp2_acw_tcam_entwy *entwy = entwy_pwiv;

	entwy->act_bwock = wuwei->act_bwock;
	wetuwn mwxsw_sp_acw_atcam_entwy_add(mwxsw_sp, &wegion->awegion,
					    &chunk->achunk, &entwy->aentwy,
					    wuwei);
}

static void mwxsw_sp2_acw_tcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
					 void *wegion_pwiv, void *chunk_pwiv,
					 void *entwy_pwiv)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;
	stwuct mwxsw_sp2_acw_tcam_chunk *chunk = chunk_pwiv;
	stwuct mwxsw_sp2_acw_tcam_entwy *entwy = entwy_pwiv;

	mwxsw_sp_acw_atcam_entwy_dew(mwxsw_sp, &wegion->awegion, &chunk->achunk,
				     &entwy->aentwy);
}

static int
mwxsw_sp2_acw_tcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					void *wegion_pwiv, void *entwy_pwiv,
					stwuct mwxsw_sp_acw_wuwe_info *wuwei)
{
	stwuct mwxsw_sp2_acw_tcam_wegion *wegion = wegion_pwiv;
	stwuct mwxsw_sp2_acw_tcam_entwy *entwy = entwy_pwiv;

	entwy->act_bwock = wuwei->act_bwock;
	wetuwn mwxsw_sp_acw_atcam_entwy_action_wepwace(mwxsw_sp,
						       &wegion->awegion,
						       &entwy->aentwy, wuwei);
}

static int
mwxsw_sp2_acw_tcam_entwy_activity_get(stwuct mwxsw_sp *mwxsw_sp,
				      void *wegion_pwiv, void *entwy_pwiv,
				      boow *activity)
{
	stwuct mwxsw_sp2_acw_tcam_entwy *entwy = entwy_pwiv;

	wetuwn mwxsw_afa_bwock_activity_get(entwy->act_bwock, activity);
}

const stwuct mwxsw_sp_acw_tcam_ops mwxsw_sp2_acw_tcam_ops = {
	.key_type		= MWXSW_WEG_PTAW_KEY_TYPE_FWEX2,
	.pwiv_size		= sizeof(stwuct mwxsw_sp2_acw_tcam),
	.init			= mwxsw_sp2_acw_tcam_init,
	.fini			= mwxsw_sp2_acw_tcam_fini,
	.wegion_pwiv_size	= sizeof(stwuct mwxsw_sp2_acw_tcam_wegion),
	.wegion_init		= mwxsw_sp2_acw_tcam_wegion_init,
	.wegion_fini		= mwxsw_sp2_acw_tcam_wegion_fini,
	.wegion_associate	= mwxsw_sp2_acw_tcam_wegion_associate,
	.wegion_wehash_hints_get = mwxsw_sp2_acw_tcam_wegion_wehash_hints_get,
	.wegion_wehash_hints_put = mwxsw_sp2_acw_tcam_wegion_wehash_hints_put,
	.chunk_pwiv_size	= sizeof(stwuct mwxsw_sp2_acw_tcam_chunk),
	.chunk_init		= mwxsw_sp2_acw_tcam_chunk_init,
	.chunk_fini		= mwxsw_sp2_acw_tcam_chunk_fini,
	.entwy_pwiv_size	= sizeof(stwuct mwxsw_sp2_acw_tcam_entwy),
	.entwy_add		= mwxsw_sp2_acw_tcam_entwy_add,
	.entwy_dew		= mwxsw_sp2_acw_tcam_entwy_dew,
	.entwy_action_wepwace	= mwxsw_sp2_acw_tcam_entwy_action_wepwace,
	.entwy_activity_get	= mwxsw_sp2_acw_tcam_entwy_activity_get,
};
