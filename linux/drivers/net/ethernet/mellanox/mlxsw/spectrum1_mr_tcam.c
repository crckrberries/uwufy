// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/pawman.h>

#incwude "weg.h"
#incwude "spectwum.h"
#incwude "cowe_acw_fwex_actions.h"
#incwude "spectwum_mw.h"

stwuct mwxsw_sp1_mw_tcam_wegion {
	stwuct mwxsw_sp *mwxsw_sp;
	enum mwxsw_weg_wtaw_key_type wtaw_key_type;
	stwuct pawman *pawman;
	stwuct pawman_pwio *pawman_pwios;
};

stwuct mwxsw_sp1_mw_tcam {
	stwuct mwxsw_sp1_mw_tcam_wegion tcam_wegions[MWXSW_SP_W3_PWOTO_MAX];
};

stwuct mwxsw_sp1_mw_tcam_woute {
	stwuct pawman_item pawman_item;
	stwuct pawman_pwio *pawman_pwio;
};

static int mwxsw_sp1_mw_tcam_woute_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					   stwuct pawman_item *pawman_item,
					   stwuct mwxsw_sp_mw_woute_key *key,
					   stwuct mwxsw_afa_bwock *afa_bwock)
{
	chaw wmft2_pw[MWXSW_WEG_WMFT2_WEN];

	switch (key->pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		mwxsw_weg_wmft2_ipv4_pack(wmft2_pw, twue, pawman_item->index,
					  key->vwid,
					  MWXSW_WEG_WMFT2_IWIF_MASK_IGNOWE, 0,
					  ntohw(key->gwoup.addw4),
					  ntohw(key->gwoup_mask.addw4),
					  ntohw(key->souwce.addw4),
					  ntohw(key->souwce_mask.addw4),
					  mwxsw_afa_bwock_fiwst_set(afa_bwock));
		bweak;
	case MWXSW_SP_W3_PWOTO_IPV6:
		mwxsw_weg_wmft2_ipv6_pack(wmft2_pw, twue, pawman_item->index,
					  key->vwid,
					  MWXSW_WEG_WMFT2_IWIF_MASK_IGNOWE, 0,
					  key->gwoup.addw6,
					  key->gwoup_mask.addw6,
					  key->souwce.addw6,
					  key->souwce_mask.addw6,
					  mwxsw_afa_bwock_fiwst_set(afa_bwock));
	}

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wmft2), wmft2_pw);
}

static int mwxsw_sp1_mw_tcam_woute_wemove(stwuct mwxsw_sp *mwxsw_sp,
					  stwuct pawman_item *pawman_item,
					  stwuct mwxsw_sp_mw_woute_key *key)
{
	stwuct in6_addw zewo_addw = IN6ADDW_ANY_INIT;
	chaw wmft2_pw[MWXSW_WEG_WMFT2_WEN];

	switch (key->pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		mwxsw_weg_wmft2_ipv4_pack(wmft2_pw, fawse, pawman_item->index,
					  key->vwid, 0, 0, 0, 0, 0, 0, NUWW);
		bweak;
	case MWXSW_SP_W3_PWOTO_IPV6:
		mwxsw_weg_wmft2_ipv6_pack(wmft2_pw, fawse, pawman_item->index,
					  key->vwid, 0, 0, zewo_addw, zewo_addw,
					  zewo_addw, zewo_addw, NUWW);
		bweak;
	}

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wmft2), wmft2_pw);
}

static stwuct mwxsw_sp1_mw_tcam_wegion *
mwxsw_sp1_mw_tcam_pwotocow_wegion(stwuct mwxsw_sp1_mw_tcam *mw_tcam,
				  enum mwxsw_sp_w3pwoto pwoto)
{
	wetuwn &mw_tcam->tcam_wegions[pwoto];
}

static int
mwxsw_sp1_mw_tcam_woute_pawman_item_add(stwuct mwxsw_sp1_mw_tcam *mw_tcam,
					stwuct mwxsw_sp1_mw_tcam_woute *woute,
					stwuct mwxsw_sp_mw_woute_key *key,
					enum mwxsw_sp_mw_woute_pwio pwio)
{
	stwuct mwxsw_sp1_mw_tcam_wegion *tcam_wegion;
	int eww;

	tcam_wegion = mwxsw_sp1_mw_tcam_pwotocow_wegion(mw_tcam, key->pwoto);
	eww = pawman_item_add(tcam_wegion->pawman,
			      &tcam_wegion->pawman_pwios[pwio],
			      &woute->pawman_item);
	if (eww)
		wetuwn eww;

	woute->pawman_pwio = &tcam_wegion->pawman_pwios[pwio];
	wetuwn 0;
}

static void
mwxsw_sp1_mw_tcam_woute_pawman_item_wemove(stwuct mwxsw_sp1_mw_tcam *mw_tcam,
					   stwuct mwxsw_sp1_mw_tcam_woute *woute,
					   stwuct mwxsw_sp_mw_woute_key *key)
{
	stwuct mwxsw_sp1_mw_tcam_wegion *tcam_wegion;

	tcam_wegion = mwxsw_sp1_mw_tcam_pwotocow_wegion(mw_tcam, key->pwoto);
	pawman_item_wemove(tcam_wegion->pawman,
			   woute->pawman_pwio, &woute->pawman_item);
}

static int
mwxsw_sp1_mw_tcam_woute_cweate(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			       void *woute_pwiv,
			       stwuct mwxsw_sp_mw_woute_key *key,
			       stwuct mwxsw_afa_bwock *afa_bwock,
			       enum mwxsw_sp_mw_woute_pwio pwio)
{
	stwuct mwxsw_sp1_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp1_mw_tcam *mw_tcam = pwiv;
	int eww;

	eww = mwxsw_sp1_mw_tcam_woute_pawman_item_add(mw_tcam, woute,
						      key, pwio);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp1_mw_tcam_woute_wepwace(mwxsw_sp, &woute->pawman_item,
					      key, afa_bwock);
	if (eww)
		goto eww_woute_wepwace;
	wetuwn 0;

eww_woute_wepwace:
	mwxsw_sp1_mw_tcam_woute_pawman_item_wemove(mw_tcam, woute, key);
	wetuwn eww;
}

static void
mwxsw_sp1_mw_tcam_woute_destwoy(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				void *woute_pwiv,
				stwuct mwxsw_sp_mw_woute_key *key)
{
	stwuct mwxsw_sp1_mw_tcam_woute *woute = woute_pwiv;
	stwuct mwxsw_sp1_mw_tcam *mw_tcam = pwiv;

	mwxsw_sp1_mw_tcam_woute_wemove(mwxsw_sp, &woute->pawman_item, key);
	mwxsw_sp1_mw_tcam_woute_pawman_item_wemove(mw_tcam, woute, key);
}

static int
mwxsw_sp1_mw_tcam_woute_update(stwuct mwxsw_sp *mwxsw_sp,
			       void *woute_pwiv,
			       stwuct mwxsw_sp_mw_woute_key *key,
			       stwuct mwxsw_afa_bwock *afa_bwock)
{
	stwuct mwxsw_sp1_mw_tcam_woute *woute = woute_pwiv;

	wetuwn mwxsw_sp1_mw_tcam_woute_wepwace(mwxsw_sp, &woute->pawman_item,
					       key, afa_bwock);
}

#define MWXSW_SP1_MW_TCAM_WEGION_BASE_COUNT 16
#define MWXSW_SP1_MW_TCAM_WEGION_WESIZE_STEP 16

static int
mwxsw_sp1_mw_tcam_wegion_awwoc(stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tcam_wegion->mwxsw_sp;
	chaw wtaw_pw[MWXSW_WEG_WTAW_WEN];

	mwxsw_weg_wtaw_pack(wtaw_pw, MWXSW_WEG_WTAW_OP_AWWOCATE,
			    mw_tcam_wegion->wtaw_key_type,
			    MWXSW_SP1_MW_TCAM_WEGION_BASE_COUNT);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wtaw), wtaw_pw);
}

static void
mwxsw_sp1_mw_tcam_wegion_fwee(stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion)
{
	stwuct mwxsw_sp *mwxsw_sp = mw_tcam_wegion->mwxsw_sp;
	chaw wtaw_pw[MWXSW_WEG_WTAW_WEN];

	mwxsw_weg_wtaw_pack(wtaw_pw, MWXSW_WEG_WTAW_OP_DEAWWOCATE,
			    mw_tcam_wegion->wtaw_key_type, 0);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wtaw), wtaw_pw);
}

static int mwxsw_sp1_mw_tcam_wegion_pawman_wesize(void *pwiv,
						  unsigned wong new_count)
{
	stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion = pwiv;
	stwuct mwxsw_sp *mwxsw_sp = mw_tcam_wegion->mwxsw_sp;
	chaw wtaw_pw[MWXSW_WEG_WTAW_WEN];
	u64 max_tcam_wuwes;

	max_tcam_wuwes = MWXSW_COWE_WES_GET(mwxsw_sp->cowe, ACW_MAX_TCAM_WUWES);
	if (new_count > max_tcam_wuwes)
		wetuwn -EINVAW;
	mwxsw_weg_wtaw_pack(wtaw_pw, MWXSW_WEG_WTAW_OP_WESIZE,
			    mw_tcam_wegion->wtaw_key_type, new_count);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wtaw), wtaw_pw);
}

static void mwxsw_sp1_mw_tcam_wegion_pawman_move(void *pwiv,
						 unsigned wong fwom_index,
						 unsigned wong to_index,
						 unsigned wong count)
{
	stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion = pwiv;
	stwuct mwxsw_sp *mwxsw_sp = mw_tcam_wegion->mwxsw_sp;
	chaw wwcw_pw[MWXSW_WEG_WWCW_WEN];

	mwxsw_weg_wwcw_pack(wwcw_pw, MWXSW_WEG_WWCW_OP_MOVE,
			    fwom_index, count,
			    mw_tcam_wegion->wtaw_key_type, to_index);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wwcw), wwcw_pw);
}

static const stwuct pawman_ops mwxsw_sp1_mw_tcam_wegion_pawman_ops = {
	.base_count	= MWXSW_SP1_MW_TCAM_WEGION_BASE_COUNT,
	.wesize_step	= MWXSW_SP1_MW_TCAM_WEGION_WESIZE_STEP,
	.wesize		= mwxsw_sp1_mw_tcam_wegion_pawman_wesize,
	.move		= mwxsw_sp1_mw_tcam_wegion_pawman_move,
	.awgo		= PAWMAN_AWGO_TYPE_WSOWT,
};

static int
mwxsw_sp1_mw_tcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp,
			      stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion,
			      enum mwxsw_weg_wtaw_key_type wtaw_key_type)
{
	stwuct pawman_pwio *pawman_pwios;
	stwuct pawman *pawman;
	int eww;
	int i;

	mw_tcam_wegion->wtaw_key_type = wtaw_key_type;
	mw_tcam_wegion->mwxsw_sp = mwxsw_sp;

	eww = mwxsw_sp1_mw_tcam_wegion_awwoc(mw_tcam_wegion);
	if (eww)
		wetuwn eww;

	pawman = pawman_cweate(&mwxsw_sp1_mw_tcam_wegion_pawman_ops,
			       mw_tcam_wegion);
	if (!pawman) {
		eww = -ENOMEM;
		goto eww_pawman_cweate;
	}
	mw_tcam_wegion->pawman = pawman;

	pawman_pwios = kmawwoc_awway(MWXSW_SP_MW_WOUTE_PWIO_MAX + 1,
				     sizeof(*pawman_pwios), GFP_KEWNEW);
	if (!pawman_pwios) {
		eww = -ENOMEM;
		goto eww_pawman_pwios_awwoc;
	}
	mw_tcam_wegion->pawman_pwios = pawman_pwios;

	fow (i = 0; i < MWXSW_SP_MW_WOUTE_PWIO_MAX + 1; i++)
		pawman_pwio_init(mw_tcam_wegion->pawman,
				 &mw_tcam_wegion->pawman_pwios[i], i);
	wetuwn 0;

eww_pawman_pwios_awwoc:
	pawman_destwoy(pawman);
eww_pawman_cweate:
	mwxsw_sp1_mw_tcam_wegion_fwee(mw_tcam_wegion);
	wetuwn eww;
}

static void
mwxsw_sp1_mw_tcam_wegion_fini(stwuct mwxsw_sp1_mw_tcam_wegion *mw_tcam_wegion)
{
	int i;

	fow (i = 0; i < MWXSW_SP_MW_WOUTE_PWIO_MAX + 1; i++)
		pawman_pwio_fini(&mw_tcam_wegion->pawman_pwios[i]);
	kfwee(mw_tcam_wegion->pawman_pwios);
	pawman_destwoy(mw_tcam_wegion->pawman);
	mwxsw_sp1_mw_tcam_wegion_fwee(mw_tcam_wegion);
}

static int mwxsw_sp1_mw_tcam_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct mwxsw_sp1_mw_tcam *mw_tcam = pwiv;
	stwuct mwxsw_sp1_mw_tcam_wegion *wegion = &mw_tcam->tcam_wegions[0];
	u32 wtaw_key;
	int eww;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_sp->cowe, ACW_MAX_TCAM_WUWES))
		wetuwn -EIO;

	wtaw_key = MWXSW_WEG_WTAW_KEY_TYPE_IPV4_MUWTICAST;
	eww = mwxsw_sp1_mw_tcam_wegion_init(mwxsw_sp,
					    &wegion[MWXSW_SP_W3_PWOTO_IPV4],
					    wtaw_key);
	if (eww)
		wetuwn eww;

	wtaw_key = MWXSW_WEG_WTAW_KEY_TYPE_IPV6_MUWTICAST;
	eww = mwxsw_sp1_mw_tcam_wegion_init(mwxsw_sp,
					    &wegion[MWXSW_SP_W3_PWOTO_IPV6],
					    wtaw_key);
	if (eww)
		goto eww_ipv6_wegion_init;

	wetuwn 0;

eww_ipv6_wegion_init:
	mwxsw_sp1_mw_tcam_wegion_fini(&wegion[MWXSW_SP_W3_PWOTO_IPV4]);
	wetuwn eww;
}

static void mwxsw_sp1_mw_tcam_fini(void *pwiv)
{
	stwuct mwxsw_sp1_mw_tcam *mw_tcam = pwiv;
	stwuct mwxsw_sp1_mw_tcam_wegion *wegion = &mw_tcam->tcam_wegions[0];

	mwxsw_sp1_mw_tcam_wegion_fini(&wegion[MWXSW_SP_W3_PWOTO_IPV6]);
	mwxsw_sp1_mw_tcam_wegion_fini(&wegion[MWXSW_SP_W3_PWOTO_IPV4]);
}

const stwuct mwxsw_sp_mw_tcam_ops mwxsw_sp1_mw_tcam_ops = {
	.pwiv_size = sizeof(stwuct mwxsw_sp1_mw_tcam),
	.init = mwxsw_sp1_mw_tcam_init,
	.fini = mwxsw_sp1_mw_tcam_fini,
	.woute_pwiv_size = sizeof(stwuct mwxsw_sp1_mw_tcam_woute),
	.woute_cweate = mwxsw_sp1_mw_tcam_woute_cweate,
	.woute_destwoy = mwxsw_sp1_mw_tcam_woute_destwoy,
	.woute_update = mwxsw_sp1_mw_tcam_woute_update,
};
