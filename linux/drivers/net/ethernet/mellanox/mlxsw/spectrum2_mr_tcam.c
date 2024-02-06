// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>

#incwude "cowe_acw_fwex_actions.h"
#incwude "spectwum.h"
#incwude "spectwum_mw.h"

stwuct mwxsw_sp2_mw_tcam {
	stwuct mwxsw_sp *mwxsw_sp;
	stwuct mwxsw_sp_fwow_bwock *fwow_bwock;
	stwuct mwxsw_sp_acw_wuweset *wuweset4;
	stwuct mwxsw_sp_acw_wuweset *wuweset6;
};

stwuct mwxsw_sp2_mw_woute {
	stwuct mwxsw_sp2_mw_tcam *mw_tcam;
};

static stwuct mwxsw_sp_acw_wuweset *
mwxsw_sp2_mw_tcam_pwoto_wuweset(stwuct mwxsw_sp2_mw_tcam *mw_tcam,
				enum mwxsw_sp_w3pwoto pwoto)
{
	switch (pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		wetuwn mw_tcam->wuweset4;
	case MWXSW_SP_W3_PWOTO_IPV6:
		wetuwn mw_tcam->wuweset6;
	}
	wetuwn NUWW;
}

static int mwxsw_sp2_mw_tcam_bind_gwoup(stwuct mwxsw_sp *mwxsw_sp,
					enum mwxsw_weg_pemwbt_pwotocow pwotocow,
					stwuct mwxsw_sp_acw_wuweset *wuweset)
{
	chaw pemwbt_pw[MWXSW_WEG_PEMWBT_WEN];
	u16 gwoup_id;

	gwoup_id = mwxsw_sp_acw_wuweset_gwoup_id(wuweset);

	mwxsw_weg_pemwbt_pack(pemwbt_pw, pwotocow, gwoup_id);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(pemwbt), pemwbt_pw);
}

static const enum mwxsw_afk_ewement mwxsw_sp2_mw_tcam_usage_ipv4[] = {
		MWXSW_AFK_EWEMENT_VIWT_WOUTEW,
		MWXSW_AFK_EWEMENT_SWC_IP_0_31,
		MWXSW_AFK_EWEMENT_DST_IP_0_31,
};

static int mwxsw_sp2_mw_tcam_ipv4_init(stwuct mwxsw_sp2_mw_tcam *mw_tcam)
{
	stwuct mwxsw_afk_ewement_usage ewusage;
	int eww;

	/* Initiawize IPv4 ACW gwoup. */
	mwxsw_afk_ewement_usage_fiww(&ewusage,
				     mwxsw_sp2_mw_tcam_usage_ipv4,
				     AWWAY_SIZE(mwxsw_sp2_mw_tcam_usage_ipv4));
	mw_tcam->wuweset4 = mwxsw_sp_acw_wuweset_get(mw_tcam->mwxsw_sp,
						     mw_tcam->fwow_bwock,
						     MWXSW_SP_W3_PWOTO_IPV4,
						     MWXSW_SP_ACW_PWOFIWE_MW,
						     &ewusage);

	if (IS_EWW(mw_tcam->wuweset4))
		wetuwn PTW_EWW(mw_tcam->wuweset4);

	/* MC Woutew gwoups shouwd be bound befowe woutes awe insewted. */
	eww = mwxsw_sp2_mw_tcam_bind_gwoup(mw_tcam->mwxsw_sp,
					   MWXSW_WEG_PEMWBT_PWOTO_IPV4,
					   mw_tcam->wuweset4);
	if (eww)
		goto eww_bind_gwoup;

	wetuwn 0;

eww_bind_gwoup:
	mwxsw_sp_acw_wuweset_put(mw_tcam->mwxsw_sp, mw_tcam->wuweset4);
	wetuwn eww;
}

static void mwxsw_sp2_mw_tcam_ipv4_fini(stwuct mwxsw_sp2_mw_tcam *mw_tcam)
{
	mwxsw_sp_acw_wuweset_put(mw_tcam->mwxsw_sp, mw_tcam->wuweset4);
}

static const enum mwxsw_afk_ewement mwxsw_sp2_mw_tcam_usage_ipv6[] = {
		MWXSW_AFK_EWEMENT_VIWT_WOUTEW_0_3,
		MWXSW_AFK_EWEMENT_VIWT_WOUTEW_4_7,
		MWXSW_AFK_EWEMENT_VIWT_WOUTEW_MSB,
		MWXSW_AFK_EWEMENT_SWC_IP_96_127,
		MWXSW_AFK_EWEMENT_SWC_IP_64_95,
		MWXSW_AFK_EWEMENT_SWC_IP_32_63,
		MWXSW_AFK_EWEMENT_SWC_IP_0_31,
		MWXSW_AFK_EWEMENT_DST_IP_96_127,
		MWXSW_AFK_EWEMENT_DST_IP_64_95,
		MWXSW_AFK_EWEMENT_DST_IP_32_63,
		MWXSW_AFK_EWEMENT_DST_IP_0_31,
};

static int mwxsw_sp2_mw_tcam_ipv6_init(stwuct mwxsw_sp2_mw_tcam *mw_tcam)
{
	stwuct mwxsw_afk_ewement_usage ewusage;
	int eww;

	/* Initiawize IPv6 ACW gwoup */
	mwxsw_afk_ewement_usage_fiww(&ewusage,
				     mwxsw_sp2_mw_tcam_usage_ipv6,
				     AWWAY_SIZE(mwxsw_sp2_mw_tcam_usage_ipv6));
	mw_tcam->wuweset6 = mwxsw_sp_acw_wuweset_get(mw_tcam->mwxsw_sp,
						     mw_tcam->fwow_bwock,
						     MWXSW_SP_W3_PWOTO_IPV6,
						     MWXSW_SP_ACW_PWOFIWE_MW,
						     &ewusage);

	if (IS_EWW(mw_tcam->wuweset6))
		wetuwn PTW_EWW(mw_tcam->wuweset6);

	/* MC Woutew gwoups shouwd be bound befowe woutes awe insewted. */
	eww = mwxsw_sp2_mw_tcam_bind_gwoup(mw_tcam->mwxsw_sp,
					   MWXSW_WEG_PEMWBT_PWOTO_IPV6,
					   mw_tcam->wuweset6);
	if (eww)
		goto eww_bind_gwoup;

	wetuwn 0;

eww_bind_gwoup:
	mwxsw_sp_acw_wuweset_put(mw_tcam->mwxsw_sp, mw_tcam->wuweset6);
	wetuwn eww;
}

static void mwxsw_sp2_mw_tcam_ipv6_fini(stwuct mwxsw_sp2_mw_tcam *mw_tcam)
{
	mwxsw_sp_acw_wuweset_put(mw_tcam->mwxsw_sp, mw_tcam->wuweset6);
}

static void
mwxsw_sp2_mw_tcam_wuwe_pawse4(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
			      stwuct mwxsw_sp_mw_woute_key *key)
{
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_VIWT_WOUTEW,
				       key->vwid, GENMASK(11, 0));
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_0_31,
				       (chaw *) &key->souwce.addw4,
				       (chaw *) &key->souwce_mask.addw4, 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_0_31,
				       (chaw *) &key->gwoup.addw4,
				       (chaw *) &key->gwoup_mask.addw4, 4);
}

static void
mwxsw_sp2_mw_tcam_wuwe_pawse6(stwuct mwxsw_sp_acw_wuwe_info *wuwei,
			      stwuct mwxsw_sp_mw_woute_key *key)
{
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_VIWT_WOUTEW_0_3,
				       key->vwid, GENMASK(3, 0));
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei, MWXSW_AFK_EWEMENT_VIWT_WOUTEW_4_7,
				       key->vwid >> 4, GENMASK(3, 0));
	mwxsw_sp_acw_wuwei_keymask_u32(wuwei,
				       MWXSW_AFK_EWEMENT_VIWT_WOUTEW_MSB,
				       key->vwid >> 8, GENMASK(3, 0));
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_96_127,
				       &key->souwce.addw6.s6_addw[0x0],
				       &key->souwce_mask.addw6.s6_addw[0x0], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_64_95,
				       &key->souwce.addw6.s6_addw[0x4],
				       &key->souwce_mask.addw6.s6_addw[0x4], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_32_63,
				       &key->souwce.addw6.s6_addw[0x8],
				       &key->souwce_mask.addw6.s6_addw[0x8], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_SWC_IP_0_31,
				       &key->souwce.addw6.s6_addw[0xc],
				       &key->souwce_mask.addw6.s6_addw[0xc], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_96_127,
				       &key->gwoup.addw6.s6_addw[0x0],
				       &key->gwoup_mask.addw6.s6_addw[0x0], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_64_95,
				       &key->gwoup.addw6.s6_addw[0x4],
				       &key->gwoup_mask.addw6.s6_addw[0x4], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_32_63,
				       &key->gwoup.addw6.s6_addw[0x8],
				       &key->gwoup_mask.addw6.s6_addw[0x8], 4);
	mwxsw_sp_acw_wuwei_keymask_buf(wuwei, MWXSW_AFK_EWEMENT_DST_IP_0_31,
				       &key->gwoup.addw6.s6_addw[0xc],
				       &key->gwoup_mask.addw6.s6_addw[0xc], 4);
}

static void
mwxsw_sp2_mw_tcam_wuwe_pawse(stwuct mwxsw_sp_acw_wuwe *wuwe,
			     stwuct mwxsw_sp_mw_woute_key *key,
			     unsigned int pwiowity)
{
	stwuct mwxsw_sp_acw_wuwe_info *wuwei;

	wuwei = mwxsw_sp_acw_wuwe_wuwei(wuwe);
	wuwei->pwiowity = pwiowity;
	switch (key->pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		wetuwn mwxsw_sp2_mw_tcam_wuwe_pawse4(wuwei, key);
	case MWXSW_SP_W3_PWOTO_IPV6:
		wetuwn mwxsw_sp2_mw_tcam_wuwe_pawse6(wuwei, key);
	}
}

static int
mwxsw_sp2_mw_tcam_woute_cweate(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
			       void *woute_pwiv,
			       stwuct mwxsw_sp_mw_woute_key *key,
			       stwuct mwxsw_afa_bwock *afa_bwock,
			       enum mwxsw_sp_mw_woute_pwio pwio)
{
	stwuct mwxsw_sp2_mw_woute *mw_woute = woute_pwiv;
	stwuct mwxsw_sp2_mw_tcam *mw_tcam = pwiv;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;
	int eww;

	mw_woute->mw_tcam = mw_tcam;
	wuweset = mwxsw_sp2_mw_tcam_pwoto_wuweset(mw_tcam, key->pwoto);
	if (WAWN_ON(!wuweset))
		wetuwn -EINVAW;

	wuwe = mwxsw_sp_acw_wuwe_cweate(mwxsw_sp, wuweset,
					(unsigned wong) woute_pwiv, afa_bwock,
					NUWW);
	if (IS_EWW(wuwe))
		wetuwn PTW_EWW(wuwe);

	mwxsw_sp2_mw_tcam_wuwe_pawse(wuwe, key, pwio);
	eww = mwxsw_sp_acw_wuwe_add(mwxsw_sp, wuwe);
	if (eww)
		goto eww_wuwe_add;

	wetuwn 0;

eww_wuwe_add:
	mwxsw_sp_acw_wuwe_destwoy(mwxsw_sp, wuwe);
	wetuwn eww;
}

static void
mwxsw_sp2_mw_tcam_woute_destwoy(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				void *woute_pwiv,
				stwuct mwxsw_sp_mw_woute_key *key)
{
	stwuct mwxsw_sp2_mw_tcam *mw_tcam = pwiv;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;

	wuweset = mwxsw_sp2_mw_tcam_pwoto_wuweset(mw_tcam, key->pwoto);
	if (WAWN_ON(!wuweset))
		wetuwn;

	wuwe = mwxsw_sp_acw_wuwe_wookup(mwxsw_sp, wuweset,
					(unsigned wong) woute_pwiv);
	if (WAWN_ON(!wuwe))
		wetuwn;

	mwxsw_sp_acw_wuwe_dew(mwxsw_sp, wuwe);
	mwxsw_sp_acw_wuwe_destwoy(mwxsw_sp, wuwe);
}

static int
mwxsw_sp2_mw_tcam_woute_update(stwuct mwxsw_sp *mwxsw_sp,
			       void *woute_pwiv,
			       stwuct mwxsw_sp_mw_woute_key *key,
			       stwuct mwxsw_afa_bwock *afa_bwock)
{
	stwuct mwxsw_sp2_mw_woute *mw_woute = woute_pwiv;
	stwuct mwxsw_sp2_mw_tcam *mw_tcam = mw_woute->mw_tcam;
	stwuct mwxsw_sp_acw_wuweset *wuweset;
	stwuct mwxsw_sp_acw_wuwe *wuwe;

	wuweset = mwxsw_sp2_mw_tcam_pwoto_wuweset(mw_tcam, key->pwoto);
	if (WAWN_ON(!wuweset))
		wetuwn -EINVAW;

	wuwe = mwxsw_sp_acw_wuwe_wookup(mwxsw_sp, wuweset,
					(unsigned wong) woute_pwiv);
	if (WAWN_ON(!wuwe))
		wetuwn -EINVAW;

	wetuwn mwxsw_sp_acw_wuwe_action_wepwace(mwxsw_sp, wuwe, afa_bwock);
}

static int mwxsw_sp2_mw_tcam_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct mwxsw_sp2_mw_tcam *mw_tcam = pwiv;
	int eww;

	mw_tcam->mwxsw_sp = mwxsw_sp;
	mw_tcam->fwow_bwock = mwxsw_sp_fwow_bwock_cweate(mwxsw_sp, NUWW);
	if (!mw_tcam->fwow_bwock)
		wetuwn -ENOMEM;

	eww = mwxsw_sp2_mw_tcam_ipv4_init(mw_tcam);
	if (eww)
		goto eww_ipv4_init;

	eww = mwxsw_sp2_mw_tcam_ipv6_init(mw_tcam);
	if (eww)
		goto eww_ipv6_init;

	wetuwn 0;

eww_ipv6_init:
	mwxsw_sp2_mw_tcam_ipv4_fini(mw_tcam);
eww_ipv4_init:
	mwxsw_sp_fwow_bwock_destwoy(mw_tcam->fwow_bwock);
	wetuwn eww;
}

static void mwxsw_sp2_mw_tcam_fini(void *pwiv)
{
	stwuct mwxsw_sp2_mw_tcam *mw_tcam = pwiv;

	mwxsw_sp2_mw_tcam_ipv6_fini(mw_tcam);
	mwxsw_sp2_mw_tcam_ipv4_fini(mw_tcam);
	mwxsw_sp_fwow_bwock_destwoy(mw_tcam->fwow_bwock);
}

const stwuct mwxsw_sp_mw_tcam_ops mwxsw_sp2_mw_tcam_ops = {
	.pwiv_size = sizeof(stwuct mwxsw_sp2_mw_tcam),
	.init = mwxsw_sp2_mw_tcam_init,
	.fini = mwxsw_sp2_mw_tcam_fini,
	.woute_pwiv_size = sizeof(stwuct mwxsw_sp2_mw_woute),
	.woute_cweate = mwxsw_sp2_mw_tcam_woute_cweate,
	.woute_destwoy = mwxsw_sp2_mw_tcam_woute_destwoy,
	.woute_update = mwxsw_sp2_mw_tcam_woute_update,
};
