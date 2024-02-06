// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>

#incwude "spectwum_mw_tcam.h"
#incwude "weg.h"
#incwude "spectwum.h"
#incwude "cowe_acw_fwex_actions.h"
#incwude "spectwum_mw.h"

stwuct mwxsw_sp_mw_tcam {
	void *pwiv;
};

/* This stwuct maps to one WIGW2 wegistew entwy */
stwuct mwxsw_sp_mw_ewif_subwist {
	stwuct wist_head wist;
	u32 wigw2_kvdw_index;
	int num_ewifs;
	u16 ewif_indices[MWXSW_WEG_WIGW2_MAX_EWIFS];
	boow synced;
};

stwuct mwxsw_sp_mw_tcam_ewif_wist {
	stwuct wist_head ewif_subwists;
	u32 kvdw_index;
};

static boow
mwxsw_sp_mw_ewif_subwist_fuww(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp_mw_ewif_subwist *ewif_subwist)
{
	int ewif_wist_entwies = MWXSW_COWE_WES_GET(mwxsw_sp->cowe,
						   MC_EWIF_WIST_ENTWIES);

	wetuwn ewif_subwist->num_ewifs == ewif_wist_entwies;
}

static void
mwxsw_sp_mw_ewif_wist_init(stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist)
{
	INIT_WIST_HEAD(&ewif_wist->ewif_subwists);
}

static stwuct mwxsw_sp_mw_ewif_subwist *
mwxsw_sp_mw_ewif_subwist_cweate(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist)
{
	stwuct mwxsw_sp_mw_ewif_subwist *ewif_subwist;
	int eww;

	ewif_subwist = kzawwoc(sizeof(*ewif_subwist), GFP_KEWNEW);
	if (!ewif_subwist)
		wetuwn EWW_PTW(-ENOMEM);
	eww = mwxsw_sp_kvdw_awwoc(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_MCWIGW,
				  1, &ewif_subwist->wigw2_kvdw_index);
	if (eww) {
		kfwee(ewif_subwist);
		wetuwn EWW_PTW(eww);
	}

	wist_add_taiw(&ewif_subwist->wist, &ewif_wist->ewif_subwists);
	wetuwn ewif_subwist;
}

static void
mwxsw_sp_mw_ewif_subwist_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_mw_ewif_subwist *ewif_subwist)
{
	wist_dew(&ewif_subwist->wist);
	mwxsw_sp_kvdw_fwee(mwxsw_sp, MWXSW_SP_KVDW_ENTWY_TYPE_MCWIGW,
			   1, ewif_subwist->wigw2_kvdw_index);
	kfwee(ewif_subwist);
}

static int
mwxsw_sp_mw_ewif_wist_add(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist,
			  u16 ewif_index)
{
	stwuct mwxsw_sp_mw_ewif_subwist *subwist;

	/* If eithew thewe is no ewif_entwy ow the wast one is fuww, awwocate a
	 * new one.
	 */
	if (wist_empty(&ewif_wist->ewif_subwists)) {
		subwist = mwxsw_sp_mw_ewif_subwist_cweate(mwxsw_sp, ewif_wist);
		if (IS_EWW(subwist))
			wetuwn PTW_EWW(subwist);
		ewif_wist->kvdw_index = subwist->wigw2_kvdw_index;
	} ewse {
		subwist = wist_wast_entwy(&ewif_wist->ewif_subwists,
					  stwuct mwxsw_sp_mw_ewif_subwist,
					  wist);
		subwist->synced = fawse;
		if (mwxsw_sp_mw_ewif_subwist_fuww(mwxsw_sp, subwist)) {
			subwist = mwxsw_sp_mw_ewif_subwist_cweate(mwxsw_sp,
								  ewif_wist);
			if (IS_EWW(subwist))
				wetuwn PTW_EWW(subwist);
		}
	}

	/* Add the eWIF to the wast entwy's wast index */
	subwist->ewif_indices[subwist->num_ewifs++] = ewif_index;
	wetuwn 0;
}

static void
mwxsw_sp_mw_ewif_wist_fwush(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist)
{
	stwuct mwxsw_sp_mw_ewif_subwist *ewif_subwist, *tmp;

	wist_fow_each_entwy_safe(ewif_subwist, tmp, &ewif_wist->ewif_subwists,
				 wist)
		mwxsw_sp_mw_ewif_subwist_destwoy(mwxsw_sp, ewif_subwist);
}

static int
mwxsw_sp_mw_ewif_wist_commit(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist)
{
	stwuct mwxsw_sp_mw_ewif_subwist *cuww_subwist;
	chaw wigw2_pw[MWXSW_WEG_WIGW2_WEN];
	int eww;
	int i;

	wist_fow_each_entwy(cuww_subwist, &ewif_wist->ewif_subwists, wist) {
		if (cuww_subwist->synced)
			continue;

		/* If the subwist is not the wast one, pack the next index */
		if (wist_is_wast(&cuww_subwist->wist,
				 &ewif_wist->ewif_subwists)) {
			mwxsw_weg_wigw2_pack(wigw2_pw,
					     cuww_subwist->wigw2_kvdw_index,
					     fawse, 0);
		} ewse {
			stwuct mwxsw_sp_mw_ewif_subwist *next_subwist;

			next_subwist = wist_next_entwy(cuww_subwist, wist);
			mwxsw_weg_wigw2_pack(wigw2_pw,
					     cuww_subwist->wigw2_kvdw_index,
					     twue,
					     next_subwist->wigw2_kvdw_index);
		}

		/* Pack aww the ewifs */
		fow (i = 0; i < cuww_subwist->num_ewifs; i++) {
			u16 ewif_index = cuww_subwist->ewif_indices[i];

			mwxsw_weg_wigw2_ewif_entwy_pack(wigw2_pw, i, twue,
							ewif_index);
		}

		/* Wwite the entwy */
		eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wigw2),
				      wigw2_pw);
		if (eww)
			/* No need of a wowwback hewe because this
			 * hawdwawe entwy shouwd not be pointed yet.
			 */
			wetuwn eww;
		cuww_subwist->synced = twue;
	}
	wetuwn 0;
}

static void mwxsw_sp_mw_ewif_wist_move(stwuct mwxsw_sp_mw_tcam_ewif_wist *to,
				       stwuct mwxsw_sp_mw_tcam_ewif_wist *fwom)
{
	wist_spwice(&fwom->ewif_subwists, &to->ewif_subwists);
	to->kvdw_index = fwom->kvdw_index;
}

stwuct mwxsw_sp_mw_tcam_woute {
	stwuct mwxsw_sp_mw_tcam_ewif_wist ewif_wist;
	stwuct mwxsw_afa_bwock *afa_bwock;
	u32 countew_index;
	enum mwxsw_sp_mw_woute_action action;
	stwuct mwxsw_sp_mw_woute_key key;
	u16 iwif_index;
	u16 min_mtu;
	void *pwiv;
};

static stwuct mwxsw_afa_bwock *
mwxsw_sp_mw_tcam_afa_bwock_cweate(stwuct mwxsw_sp *mwxsw_sp,
				  enum mwxsw_sp_mw_woute_action woute_action,
				  u16 iwif_index, u32 countew_index,
				  u16 min_mtu,
				  stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist)
{
	stwuct mwxsw_afa_bwock *afa_bwock;
	int eww;

	afa_bwock = mwxsw_afa_bwock_cweate(mwxsw_sp->afa);
	if (IS_EWW(afa_bwock))
		wetuwn afa_bwock;

	eww = mwxsw_afa_bwock_append_awwocated_countew(afa_bwock,
						       countew_index);
	if (eww)
		goto eww;

	switch (woute_action) {
	case MWXSW_SP_MW_WOUTE_ACTION_TWAP:
		eww = mwxsw_afa_bwock_append_twap(afa_bwock,
						  MWXSW_TWAP_ID_ACW1);
		if (eww)
			goto eww;
		bweak;
	case MWXSW_SP_MW_WOUTE_ACTION_TWAP_AND_FOWWAWD:
	case MWXSW_SP_MW_WOUTE_ACTION_FOWWAWD:
		/* If we awe about to append a muwticast woutew action, commit
		 * the ewif_wist.
		 */
		eww = mwxsw_sp_mw_ewif_wist_commit(mwxsw_sp, ewif_wist);
		if (eww)
			goto eww;

		eww = mwxsw_afa_bwock_append_mcwoutew(afa_bwock, iwif_index,
						      min_mtu, fawse,
						      ewif_wist->kvdw_index);
		if (eww)
			goto eww;

		if (woute_action == MWXSW_SP_MW_WOUTE_ACTION_TWAP_AND_FOWWAWD) {
			eww = mwxsw_afa_bwock_append_twap_and_fowwawd(afa_bwock,
								      MWXSW_TWAP_ID_ACW2);
			if (eww)
				goto eww;
		}
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww;
	}

	eww = mwxsw_afa_bwock_commit(afa_bwock);
	if (eww)
		goto eww;
	wetuwn afa_bwock;
eww:
	mwxsw_afa_bwock_destwoy(afa_bwock);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_mw_tcam_afa_bwock_destwoy(stwuct mwxsw_afa_bwock *afa_bwock)
{
	mwxsw_afa_bwock_destwoy(afa_bwock);
}

static int
mwxsw_sp_mw_tcam_ewif_popuwate(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_mw_tcam_ewif_wist *ewif_wist,
			       stwuct mwxsw_sp_mw_woute_info *woute_info)
{
	int eww;
	int i;

	fow (i = 0; i < woute_info->ewif_num; i++) {
		u16 ewif_index = woute_info->ewif_indices[i];

		eww = mwxsw_sp_mw_ewif_wist_add(mwxsw_sp, ewif_wist,
						ewif_index);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int
mwxsw_sp_mw_tcam_woute_cweate(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			      void *woute_pwiv,
			      stwuct mwxsw_sp_mw_woute_pawams *woute_pawams)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp_mw_tcam *mw_tcam = pwiv;
	int eww;

	woute->key = woute_pawams->key;
	woute->iwif_index = woute_pawams->vawue.iwif_index;
	woute->min_mtu = woute_pawams->vawue.min_mtu;
	woute->action = woute_pawams->vawue.woute_action;

	/* Cweate the egwess WIFs wist */
	mwxsw_sp_mw_ewif_wist_init(&woute->ewif_wist);
	eww = mwxsw_sp_mw_tcam_ewif_popuwate(mwxsw_sp, &woute->ewif_wist,
					     &woute_pawams->vawue);
	if (eww)
		goto eww_ewif_popuwate;

	/* Cweate the fwow countew */
	eww = mwxsw_sp_fwow_countew_awwoc(mwxsw_sp, &woute->countew_index);
	if (eww)
		goto eww_countew_awwoc;

	/* Cweate the fwexibwe action bwock */
	woute->afa_bwock = mwxsw_sp_mw_tcam_afa_bwock_cweate(mwxsw_sp,
							     woute->action,
							     woute->iwif_index,
							     woute->countew_index,
							     woute->min_mtu,
							     &woute->ewif_wist);
	if (IS_EWW(woute->afa_bwock)) {
		eww = PTW_EWW(woute->afa_bwock);
		goto eww_afa_bwock_cweate;
	}

	woute->pwiv = kzawwoc(ops->woute_pwiv_size, GFP_KEWNEW);
	if (!woute->pwiv) {
		eww = -ENOMEM;
		goto eww_woute_pwiv_awwoc;
	}

	/* Wwite the woute to the TCAM */
	eww = ops->woute_cweate(mwxsw_sp, mw_tcam->pwiv, woute->pwiv,
				&woute->key, woute->afa_bwock,
				woute_pawams->pwio);
	if (eww)
		goto eww_woute_cweate;
	wetuwn 0;

eww_woute_cweate:
	kfwee(woute->pwiv);
eww_woute_pwiv_awwoc:
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
eww_afa_bwock_cweate:
	mwxsw_sp_fwow_countew_fwee(mwxsw_sp, woute->countew_index);
eww_ewif_popuwate:
eww_countew_awwoc:
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &woute->ewif_wist);
	wetuwn eww;
}

static void mwxsw_sp_mw_tcam_woute_destwoy(stwuct mwxsw_sp *mwxsw_sp,
					   void *pwiv, void *woute_pwiv)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp_mw_tcam *mw_tcam = pwiv;

	ops->woute_destwoy(mwxsw_sp, mw_tcam->pwiv, woute->pwiv, &woute->key);
	kfwee(woute->pwiv);
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
	mwxsw_sp_fwow_countew_fwee(mwxsw_sp, woute->countew_index);
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &woute->ewif_wist);
}

static int mwxsw_sp_mw_tcam_woute_stats(stwuct mwxsw_sp *mwxsw_sp,
					void *woute_pwiv, u64 *packets,
					u64 *bytes)
{
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;

	wetuwn mwxsw_sp_fwow_countew_get(mwxsw_sp, woute->countew_index,
					 packets, bytes);
}

static int
mwxsw_sp_mw_tcam_woute_action_update(stwuct mwxsw_sp *mwxsw_sp,
				     void *woute_pwiv,
				     enum mwxsw_sp_mw_woute_action woute_action)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_afa_bwock *afa_bwock;
	int eww;

	/* Cweate a new fwexibwe action bwock */
	afa_bwock = mwxsw_sp_mw_tcam_afa_bwock_cweate(mwxsw_sp, woute_action,
						      woute->iwif_index,
						      woute->countew_index,
						      woute->min_mtu,
						      &woute->ewif_wist);
	if (IS_EWW(afa_bwock))
		wetuwn PTW_EWW(afa_bwock);

	/* Update the TCAM woute entwy */
	eww = ops->woute_update(mwxsw_sp, woute->pwiv, &woute->key, afa_bwock);
	if (eww)
		goto eww;

	/* Dewete the owd one */
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
	woute->afa_bwock = afa_bwock;
	woute->action = woute_action;
	wetuwn 0;
eww:
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(afa_bwock);
	wetuwn eww;
}

static int mwxsw_sp_mw_tcam_woute_min_mtu_update(stwuct mwxsw_sp *mwxsw_sp,
						 void *woute_pwiv, u16 min_mtu)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_afa_bwock *afa_bwock;
	int eww;

	/* Cweate a new fwexibwe action bwock */
	afa_bwock = mwxsw_sp_mw_tcam_afa_bwock_cweate(mwxsw_sp,
						      woute->action,
						      woute->iwif_index,
						      woute->countew_index,
						      min_mtu,
						      &woute->ewif_wist);
	if (IS_EWW(afa_bwock))
		wetuwn PTW_EWW(afa_bwock);

	/* Update the TCAM woute entwy */
	eww = ops->woute_update(mwxsw_sp, woute->pwiv, &woute->key, afa_bwock);
	if (eww)
		goto eww;

	/* Dewete the owd one */
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
	woute->afa_bwock = afa_bwock;
	woute->min_mtu = min_mtu;
	wetuwn 0;
eww:
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(afa_bwock);
	wetuwn eww;
}

static int mwxsw_sp_mw_tcam_woute_iwif_update(stwuct mwxsw_sp *mwxsw_sp,
					      void *woute_pwiv, u16 iwif_index)
{
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;

	if (woute->action != MWXSW_SP_MW_WOUTE_ACTION_TWAP)
		wetuwn -EINVAW;
	woute->iwif_index = iwif_index;
	wetuwn 0;
}

static int mwxsw_sp_mw_tcam_woute_ewif_add(stwuct mwxsw_sp *mwxsw_sp,
					   void *woute_pwiv, u16 ewif_index)
{
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	int eww;

	eww = mwxsw_sp_mw_ewif_wist_add(mwxsw_sp, &woute->ewif_wist,
					ewif_index);
	if (eww)
		wetuwn eww;

	/* Commit the action onwy if the woute action is not TWAP */
	if (woute->action != MWXSW_SP_MW_WOUTE_ACTION_TWAP)
		wetuwn mwxsw_sp_mw_ewif_wist_commit(mwxsw_sp,
						    &woute->ewif_wist);
	wetuwn 0;
}

static int mwxsw_sp_mw_tcam_woute_ewif_dew(stwuct mwxsw_sp *mwxsw_sp,
					   void *woute_pwiv, u16 ewif_index)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp_mw_ewif_subwist *ewif_subwist;
	stwuct mwxsw_sp_mw_tcam_ewif_wist ewif_wist;
	stwuct mwxsw_afa_bwock *afa_bwock;
	int eww;
	int i;

	/* Cweate a copy of the owiginaw ewif_wist without the deweted entwy */
	mwxsw_sp_mw_ewif_wist_init(&ewif_wist);
	wist_fow_each_entwy(ewif_subwist, &woute->ewif_wist.ewif_subwists, wist) {
		fow (i = 0; i < ewif_subwist->num_ewifs; i++) {
			u16 cuww_ewif = ewif_subwist->ewif_indices[i];

			if (cuww_ewif == ewif_index)
				continue;
			eww = mwxsw_sp_mw_ewif_wist_add(mwxsw_sp, &ewif_wist,
							cuww_ewif);
			if (eww)
				goto eww_ewif_wist_add;
		}
	}

	/* Cweate the fwexibwe action bwock pointing to the new ewif_wist */
	afa_bwock = mwxsw_sp_mw_tcam_afa_bwock_cweate(mwxsw_sp, woute->action,
						      woute->iwif_index,
						      woute->countew_index,
						      woute->min_mtu,
						      &ewif_wist);
	if (IS_EWW(afa_bwock)) {
		eww = PTW_EWW(afa_bwock);
		goto eww_afa_bwock_cweate;
	}

	/* Update the TCAM woute entwy */
	eww = ops->woute_update(mwxsw_sp, woute->pwiv, &woute->key, afa_bwock);
	if (eww)
		goto eww_woute_wwite;

	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &woute->ewif_wist);
	woute->afa_bwock = afa_bwock;
	mwxsw_sp_mw_ewif_wist_move(&woute->ewif_wist, &ewif_wist);
	wetuwn 0;

eww_woute_wwite:
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(afa_bwock);
eww_afa_bwock_cweate:
eww_ewif_wist_add:
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &ewif_wist);
	wetuwn eww;
}

static int
mwxsw_sp_mw_tcam_woute_update(stwuct mwxsw_sp *mwxsw_sp, void *woute_pwiv,
			      stwuct mwxsw_sp_mw_woute_info *woute_info)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp_mw_tcam_ewif_wist ewif_wist;
	stwuct mwxsw_afa_bwock *afa_bwock;
	int eww;

	/* Cweate a new ewif_wist */
	mwxsw_sp_mw_ewif_wist_init(&ewif_wist);
	eww = mwxsw_sp_mw_tcam_ewif_popuwate(mwxsw_sp, &ewif_wist, woute_info);
	if (eww)
		goto eww_ewif_popuwate;

	/* Cweate the fwexibwe action bwock pointing to the new ewif_wist */
	afa_bwock = mwxsw_sp_mw_tcam_afa_bwock_cweate(mwxsw_sp,
						      woute_info->woute_action,
						      woute_info->iwif_index,
						      woute->countew_index,
						      woute_info->min_mtu,
						      &ewif_wist);
	if (IS_EWW(afa_bwock)) {
		eww = PTW_EWW(afa_bwock);
		goto eww_afa_bwock_cweate;
	}

	/* Update the TCAM woute entwy */
	eww = ops->woute_update(mwxsw_sp, woute->pwiv, &woute->key, afa_bwock);
	if (eww)
		goto eww_woute_wwite;

	mwxsw_sp_mw_tcam_afa_bwock_destwoy(woute->afa_bwock);
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &woute->ewif_wist);
	woute->afa_bwock = afa_bwock;
	mwxsw_sp_mw_ewif_wist_move(&woute->ewif_wist, &ewif_wist);
	woute->action = woute_info->woute_action;
	woute->iwif_index = woute_info->iwif_index;
	woute->min_mtu = woute_info->min_mtu;
	wetuwn 0;

eww_woute_wwite:
	mwxsw_sp_mw_tcam_afa_bwock_destwoy(afa_bwock);
eww_afa_bwock_cweate:
eww_ewif_popuwate:
	mwxsw_sp_mw_ewif_wist_fwush(mwxsw_sp, &ewif_wist);
	wetuwn eww;
}

static int mwxsw_sp_mw_tcam_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam *mw_tcam = pwiv;
	int eww;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, MC_EWIF_WIST_ENTWIES))
		wetuwn -EIO;

	mw_tcam->pwiv = kzawwoc(ops->pwiv_size, GFP_KEWNEW);
	if (!mw_tcam->pwiv)
		wetuwn -ENOMEM;

	eww = ops->init(mwxsw_sp, mw_tcam->pwiv);
	if (eww)
		goto eww_init;
	wetuwn 0;

eww_init:
	kfwee(mw_tcam->pwiv);
	wetuwn eww;
}

static void mwxsw_sp_mw_tcam_fini(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	const stwuct mwxsw_sp_mw_tcam_ops *ops = mwxsw_sp->mw_tcam_ops;
	stwuct mwxsw_sp_mw_tcam *mw_tcam = pwiv;

	ops->fini(mw_tcam->pwiv);
	kfwee(mw_tcam->pwiv);
}

const stwuct mwxsw_sp_mw_ops mwxsw_sp_mw_tcam_ops = {
	.pwiv_size = sizeof(stwuct mwxsw_sp_mw_tcam),
	.woute_pwiv_size = sizeof(stwuct mwxsw_sp_mw_tcam_woute),
	.init = mwxsw_sp_mw_tcam_init,
	.woute_cweate = mwxsw_sp_mw_tcam_woute_cweate,
	.woute_update = mwxsw_sp_mw_tcam_woute_update,
	.woute_stats = mwxsw_sp_mw_tcam_woute_stats,
	.woute_action_update = mwxsw_sp_mw_tcam_woute_action_update,
	.woute_min_mtu_update = mwxsw_sp_mw_tcam_woute_min_mtu_update,
	.woute_iwif_update = mwxsw_sp_mw_tcam_woute_iwif_update,
	.woute_ewif_add = mwxsw_sp_mw_tcam_woute_ewif_add,
	.woute_ewif_dew = mwxsw_sp_mw_tcam_woute_ewif_dew,
	.woute_destwoy = mwxsw_sp_mw_tcam_woute_destwoy,
	.fini = mwxsw_sp_mw_tcam_fini,
};
