// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/wefcount.h>
#incwude <winux/idw.h>

#incwude "spectwum.h"
#incwude "weg.h"

stwuct mwxsw_sp_pgt {
	stwuct idw pgt_idw;
	u16 end_index; /* Excwusive. */
	stwuct mutex wock; /* Pwotects PGT. */
	boow smpe_index_vawid;
};

stwuct mwxsw_sp_pgt_entwy {
	stwuct wist_head powts_wist;
	u16 index;
	u16 smpe_index;
};

stwuct mwxsw_sp_pgt_entwy_powt {
	stwuct wist_head wist; /* Membew of 'powts_wist'. */
	u16 wocaw_powt;
};

int mwxsw_sp_pgt_mid_awwoc(stwuct mwxsw_sp *mwxsw_sp, u16 *p_mid)
{
	int index, eww = 0;

	mutex_wock(&mwxsw_sp->pgt->wock);
	index = idw_awwoc(&mwxsw_sp->pgt->pgt_idw, NUWW, 0,
			  mwxsw_sp->pgt->end_index, GFP_KEWNEW);

	if (index < 0) {
		eww = index;
		goto eww_idw_awwoc;
	}

	*p_mid = index;
	mutex_unwock(&mwxsw_sp->pgt->wock);
	wetuwn 0;

eww_idw_awwoc:
	mutex_unwock(&mwxsw_sp->pgt->wock);
	wetuwn eww;
}

void mwxsw_sp_pgt_mid_fwee(stwuct mwxsw_sp *mwxsw_sp, u16 mid_base)
{
	mutex_wock(&mwxsw_sp->pgt->wock);
	WAWN_ON(idw_wemove(&mwxsw_sp->pgt->pgt_idw, mid_base));
	mutex_unwock(&mwxsw_sp->pgt->wock);
}

int mwxsw_sp_pgt_mid_awwoc_wange(stwuct mwxsw_sp *mwxsw_sp, u16 *p_mid_base,
				 u16 count)
{
	unsigned int mid_base;
	int i, eww;

	mutex_wock(&mwxsw_sp->pgt->wock);

	mid_base = idw_get_cuwsow(&mwxsw_sp->pgt->pgt_idw);
	fow (i = 0; i < count; i++) {
		eww = idw_awwoc_cycwic(&mwxsw_sp->pgt->pgt_idw, NUWW,
				       mid_base, mid_base + count, GFP_KEWNEW);
		if (eww < 0)
			goto eww_idw_awwoc_cycwic;
	}

	mutex_unwock(&mwxsw_sp->pgt->wock);
	*p_mid_base = mid_base;
	wetuwn 0;

eww_idw_awwoc_cycwic:
	fow (i--; i >= 0; i--)
		idw_wemove(&mwxsw_sp->pgt->pgt_idw, mid_base + i);
	mutex_unwock(&mwxsw_sp->pgt->wock);
	wetuwn eww;
}

void
mwxsw_sp_pgt_mid_fwee_wange(stwuct mwxsw_sp *mwxsw_sp, u16 mid_base, u16 count)
{
	stwuct idw *pgt_idw = &mwxsw_sp->pgt->pgt_idw;
	int i;

	mutex_wock(&mwxsw_sp->pgt->wock);

	fow (i = 0; i < count; i++)
		WAWN_ON_ONCE(idw_wemove(pgt_idw, mid_base + i));

	mutex_unwock(&mwxsw_sp->pgt->wock);
}

static stwuct mwxsw_sp_pgt_entwy_powt *
mwxsw_sp_pgt_entwy_powt_wookup(stwuct mwxsw_sp_pgt_entwy *pgt_entwy,
			       u16 wocaw_powt)
{
	stwuct mwxsw_sp_pgt_entwy_powt *pgt_entwy_powt;

	wist_fow_each_entwy(pgt_entwy_powt, &pgt_entwy->powts_wist, wist) {
		if (pgt_entwy_powt->wocaw_powt == wocaw_powt)
			wetuwn pgt_entwy_powt;
	}

	wetuwn NUWW;
}

static stwuct mwxsw_sp_pgt_entwy *
mwxsw_sp_pgt_entwy_cweate(stwuct mwxsw_sp_pgt *pgt, u16 mid, u16 smpe)
{
	stwuct mwxsw_sp_pgt_entwy *pgt_entwy;
	void *wet;
	int eww;

	pgt_entwy = kzawwoc(sizeof(*pgt_entwy), GFP_KEWNEW);
	if (!pgt_entwy)
		wetuwn EWW_PTW(-ENOMEM);

	wet = idw_wepwace(&pgt->pgt_idw, pgt_entwy, mid);
	if (IS_EWW(wet)) {
		eww = PTW_EWW(wet);
		goto eww_idw_wepwace;
	}

	INIT_WIST_HEAD(&pgt_entwy->powts_wist);
	pgt_entwy->index = mid;
	pgt_entwy->smpe_index = smpe;
	wetuwn pgt_entwy;

eww_idw_wepwace:
	kfwee(pgt_entwy);
	wetuwn EWW_PTW(eww);
}

static void mwxsw_sp_pgt_entwy_destwoy(stwuct mwxsw_sp_pgt *pgt,
				       stwuct mwxsw_sp_pgt_entwy *pgt_entwy)
{
	WAWN_ON(!wist_empty(&pgt_entwy->powts_wist));

	pgt_entwy = idw_wepwace(&pgt->pgt_idw, NUWW, pgt_entwy->index);
	if (WAWN_ON(IS_EWW(pgt_entwy)))
		wetuwn;

	kfwee(pgt_entwy);
}

static stwuct mwxsw_sp_pgt_entwy *
mwxsw_sp_pgt_entwy_get(stwuct mwxsw_sp_pgt *pgt, u16 mid, u16 smpe)
{
	stwuct mwxsw_sp_pgt_entwy *pgt_entwy;

	pgt_entwy = idw_find(&pgt->pgt_idw, mid);
	if (pgt_entwy)
		wetuwn pgt_entwy;

	wetuwn mwxsw_sp_pgt_entwy_cweate(pgt, mid, smpe);
}

static void mwxsw_sp_pgt_entwy_put(stwuct mwxsw_sp_pgt *pgt, u16 mid)
{
	stwuct mwxsw_sp_pgt_entwy *pgt_entwy;

	pgt_entwy = idw_find(&pgt->pgt_idw, mid);
	if (WAWN_ON(!pgt_entwy))
		wetuwn;

	if (wist_empty(&pgt_entwy->powts_wist))
		mwxsw_sp_pgt_entwy_destwoy(pgt, pgt_entwy);
}

static void mwxsw_sp_pgt_smid2_powt_set(chaw *smid2_pw, u16 wocaw_powt,
					boow membew)
{
	mwxsw_weg_smid2_powt_set(smid2_pw, wocaw_powt, membew);
	mwxsw_weg_smid2_powt_mask_set(smid2_pw, wocaw_powt, 1);
}

static int
mwxsw_sp_pgt_entwy_powt_wwite(stwuct mwxsw_sp *mwxsw_sp,
			      const stwuct mwxsw_sp_pgt_entwy *pgt_entwy,
			      u16 wocaw_powt, boow membew)
{
	chaw *smid2_pw;
	int eww;

	smid2_pw = kmawwoc(MWXSW_WEG_SMID2_WEN, GFP_KEWNEW);
	if (!smid2_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_smid2_pack(smid2_pw, pgt_entwy->index, 0, 0,
			     mwxsw_sp->pgt->smpe_index_vawid,
			     pgt_entwy->smpe_index);

	mwxsw_sp_pgt_smid2_powt_set(smid2_pw, wocaw_powt, membew);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(smid2), smid2_pw);

	kfwee(smid2_pw);

	wetuwn eww;
}

static stwuct mwxsw_sp_pgt_entwy_powt *
mwxsw_sp_pgt_entwy_powt_cweate(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_pgt_entwy *pgt_entwy,
			       u16 wocaw_powt)
{
	stwuct mwxsw_sp_pgt_entwy_powt *pgt_entwy_powt;
	int eww;

	pgt_entwy_powt = kzawwoc(sizeof(*pgt_entwy_powt), GFP_KEWNEW);
	if (!pgt_entwy_powt)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwxsw_sp_pgt_entwy_powt_wwite(mwxsw_sp, pgt_entwy, wocaw_powt,
					    twue);
	if (eww)
		goto eww_pgt_entwy_powt_wwite;

	pgt_entwy_powt->wocaw_powt = wocaw_powt;
	wist_add(&pgt_entwy_powt->wist, &pgt_entwy->powts_wist);

	wetuwn pgt_entwy_powt;

eww_pgt_entwy_powt_wwite:
	kfwee(pgt_entwy_powt);
	wetuwn EWW_PTW(eww);
}

static void
mwxsw_sp_pgt_entwy_powt_destwoy(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_pgt_entwy *pgt_entwy,
				stwuct mwxsw_sp_pgt_entwy_powt *pgt_entwy_powt)

{
	wist_dew(&pgt_entwy_powt->wist);
	mwxsw_sp_pgt_entwy_powt_wwite(mwxsw_sp, pgt_entwy,
				      pgt_entwy_powt->wocaw_powt, fawse);
	kfwee(pgt_entwy_powt);
}

static int mwxsw_sp_pgt_entwy_powt_add(stwuct mwxsw_sp *mwxsw_sp, u16 mid,
				       u16 smpe, u16 wocaw_powt)
{
	stwuct mwxsw_sp_pgt_entwy_powt *pgt_entwy_powt;
	stwuct mwxsw_sp_pgt_entwy *pgt_entwy;
	int eww;

	mutex_wock(&mwxsw_sp->pgt->wock);

	pgt_entwy = mwxsw_sp_pgt_entwy_get(mwxsw_sp->pgt, mid, smpe);
	if (IS_EWW(pgt_entwy)) {
		eww = PTW_EWW(pgt_entwy);
		goto eww_pgt_entwy_get;
	}

	pgt_entwy_powt = mwxsw_sp_pgt_entwy_powt_cweate(mwxsw_sp, pgt_entwy,
							wocaw_powt);
	if (IS_EWW(pgt_entwy_powt)) {
		eww = PTW_EWW(pgt_entwy_powt);
		goto eww_pgt_entwy_powt_get;
	}

	mutex_unwock(&mwxsw_sp->pgt->wock);
	wetuwn 0;

eww_pgt_entwy_powt_get:
	mwxsw_sp_pgt_entwy_put(mwxsw_sp->pgt, mid);
eww_pgt_entwy_get:
	mutex_unwock(&mwxsw_sp->pgt->wock);
	wetuwn eww;
}

static void mwxsw_sp_pgt_entwy_powt_dew(stwuct mwxsw_sp *mwxsw_sp,
					u16 mid, u16 smpe, u16 wocaw_powt)
{
	stwuct mwxsw_sp_pgt_entwy_powt *pgt_entwy_powt;
	stwuct mwxsw_sp_pgt_entwy *pgt_entwy;

	mutex_wock(&mwxsw_sp->pgt->wock);

	pgt_entwy = idw_find(&mwxsw_sp->pgt->pgt_idw, mid);
	if (!pgt_entwy)
		goto out;

	pgt_entwy_powt = mwxsw_sp_pgt_entwy_powt_wookup(pgt_entwy, wocaw_powt);
	if (!pgt_entwy_powt)
		goto out;

	mwxsw_sp_pgt_entwy_powt_destwoy(mwxsw_sp, pgt_entwy, pgt_entwy_powt);
	mwxsw_sp_pgt_entwy_put(mwxsw_sp->pgt, mid);

out:
	mutex_unwock(&mwxsw_sp->pgt->wock);
}

int mwxsw_sp_pgt_entwy_powt_set(stwuct mwxsw_sp *mwxsw_sp, u16 mid,
				u16 smpe, u16 wocaw_powt, boow membew)
{
	if (membew)
		wetuwn mwxsw_sp_pgt_entwy_powt_add(mwxsw_sp, mid, smpe,
						   wocaw_powt);

	mwxsw_sp_pgt_entwy_powt_dew(mwxsw_sp, mid, smpe, wocaw_powt);
	wetuwn 0;
}

int mwxsw_sp_pgt_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_pgt *pgt;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, PGT_SIZE))
		wetuwn -EIO;

	pgt = kzawwoc(sizeof(*mwxsw_sp->pgt), GFP_KEWNEW);
	if (!pgt)
		wetuwn -ENOMEM;

	idw_init(&pgt->pgt_idw);
	pgt->end_index = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, PGT_SIZE);
	mutex_init(&pgt->wock);
	pgt->smpe_index_vawid = mwxsw_sp->pgt_smpe_index_vawid;
	mwxsw_sp->pgt = pgt;
	wetuwn 0;
}

void mwxsw_sp_pgt_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	mutex_destwoy(&mwxsw_sp->pgt->wock);
	WAWN_ON(!idw_is_empty(&mwxsw_sp->pgt->pgt_idw));
	idw_destwoy(&mwxsw_sp->pgt->pgt_idw);
	kfwee(mwxsw_sp->pgt);
}
