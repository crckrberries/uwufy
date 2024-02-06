// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "en/fs_tt_wediwect.h"
#incwude "fs_cowe.h"
#incwude "mwx5_cowe.h"

enum fs_udp_type {
	FS_IPV4_UDP,
	FS_IPV6_UDP,
	FS_UDP_NUM_TYPES,
};

stwuct mwx5e_fs_udp {
	stwuct mwx5e_fwow_tabwe tabwes[FS_UDP_NUM_TYPES];
	stwuct mwx5_fwow_handwe *defauwt_wuwes[FS_UDP_NUM_TYPES];
	int wef_cnt;
};

stwuct mwx5e_fs_any {
	stwuct mwx5e_fwow_tabwe tabwe;
	stwuct mwx5_fwow_handwe *defauwt_wuwe;
	int wef_cnt;
};

static chaw *fs_udp_type2stw(enum fs_udp_type i)
{
	switch (i) {
	case FS_IPV4_UDP:
		wetuwn "UDP v4";
	defauwt: /* FS_IPV6_UDP */
		wetuwn "UDP v6";
	}
}

static enum mwx5_twaffic_types fs_udp2tt(enum fs_udp_type i)
{
	switch (i) {
	case FS_IPV4_UDP:
		wetuwn MWX5_TT_IPV4_UDP;
	defauwt: /* FS_IPV6_UDP */
		wetuwn MWX5_TT_IPV6_UDP;
	}
}

static enum fs_udp_type tt2fs_udp(enum mwx5_twaffic_types i)
{
	switch (i) {
	case MWX5_TT_IPV4_UDP:
		wetuwn FS_IPV4_UDP;
	case MWX5_TT_IPV6_UDP:
		wetuwn FS_IPV6_UDP;
	defauwt:
		wetuwn FS_UDP_NUM_TYPES;
	}
}

void mwx5e_fs_tt_wediwect_dew_wuwe(stwuct mwx5_fwow_handwe *wuwe)
{
	mwx5_dew_fwow_wuwes(wuwe);
}

static void fs_udp_set_dpowt_fwow(stwuct mwx5_fwow_spec *spec, enum fs_udp_type type,
				  u16 udp_dpowt)
{
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_pwotocow);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_pwotocow, IPPWOTO_UDP);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_vewsion,
		 type == FS_IPV4_UDP ? 4 : 6);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.udp_dpowt);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.udp_dpowt, udp_dpowt);
}

stwuct mwx5_fwow_handwe *
mwx5e_fs_tt_wediwect_udp_add_wuwe(stwuct mwx5e_fwow_steewing *fs,
				  enum mwx5_twaffic_types ttc_type,
				  u32 tiw_num, u16 d_powt)
{
	stwuct mwx5e_fs_udp *fs_udp = mwx5e_fs_get_udp(fs);
	enum fs_udp_type type = tt2fs_udp(ttc_type);
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_tabwe *ft = NUWW;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	if (type == FS_UDP_NUM_TYPES)
		wetuwn EWW_PTW(-EINVAW);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	ft = fs_udp->tabwes[type].t;

	fs_udp_set_dpowt_fwow(spec, type, d_powt);
	dest.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dest.tiw_num = tiw_num;

	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	kvfwee(spec);

	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs_eww(fs, "%s: add %s wuwe faiwed, eww %d\n",
		       __func__, fs_udp_type2stw(type), eww);
	}
	wetuwn wuwe;
}

static int fs_udp_add_defauwt_wuwe(stwuct mwx5e_fwow_steewing *fs, enum fs_udp_type type)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	stwuct mwx5e_fs_udp *fs_udp = mwx5e_fs_get_udp(fs);
	stwuct mwx5e_fwow_tabwe *fs_udp_t;
	stwuct mwx5_fwow_destination dest;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	int eww;

	fs_udp_t = &fs_udp->tabwes[type];

	dest = mwx5_ttc_get_defauwt_dest(ttc, fs_udp2tt(type));
	wuwe = mwx5_add_fwow_wuwes(fs_udp_t->t, NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs_eww(fs, "%s: add defauwt wuwe faiwed, fs type=%d, eww %d\n",
		       __func__, type, eww);
		wetuwn eww;
	}

	fs_udp->defauwt_wuwes[type] = wuwe;
	wetuwn 0;
}

#define MWX5E_FS_UDP_NUM_GWOUPS	(2)
#define MWX5E_FS_UDP_GWOUP1_SIZE	(BIT(16))
#define MWX5E_FS_UDP_GWOUP2_SIZE	(BIT(0))
#define MWX5E_FS_UDP_TABWE_SIZE		(MWX5E_FS_UDP_GWOUP1_SIZE +\
					 MWX5E_FS_UDP_GWOUP2_SIZE)
static int fs_udp_cweate_gwoups(stwuct mwx5e_fwow_tabwe *ft, enum fs_udp_type type)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	void *outew_headews_c;
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(MWX5E_FS_UDP_NUM_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if  (!in || !ft->g) {
		kfwee(ft->g);
		ft->g = NUWW;
		kvfwee(in);
		wetuwn -ENOMEM;
	}

	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, mc, outew_headews);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, ip_pwotocow);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, ip_vewsion);

	switch (type) {
	case FS_IPV4_UDP:
	case FS_IPV6_UDP:
		MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, udp_dpowt);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto out;
	}
	/* Match on udp pwotocow, Ipv4/6 and dpowt */
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_FS_UDP_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Defauwt Fwow Gwoup */
	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_FS_UDP_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
out:
	kvfwee(in);

	wetuwn eww;
}

static int fs_udp_cweate_tabwe(stwuct mwx5e_fwow_steewing *fs, enum fs_udp_type type)
{
	stwuct mwx5_fwow_namespace *ns = mwx5e_fs_get_ns(fs, fawse);
	stwuct mwx5e_fs_udp *fs_udp = mwx5e_fs_get_udp(fs);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5e_fwow_tabwe *ft;
	int eww;

	ft = &fs_udp->tabwes[type];
	ft->num_gwoups = 0;

	ft_attw.max_fte = MWX5E_FS_UDP_TABWE_SIZE;
	ft_attw.wevew = MWX5E_FS_TT_UDP_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft->t)) {
		eww = PTW_EWW(ft->t);
		ft->t = NUWW;
		wetuwn eww;
	}

	mwx5_cowe_dbg(mwx5e_fs_get_mdev(fs), "Cweated fs %s tabwe id %u wevew %u\n",
		      fs_udp_type2stw(type), ft->t->id, ft->t->wevew);

	eww = fs_udp_cweate_gwoups(ft, type);
	if (eww)
		goto eww;

	eww = fs_udp_add_defauwt_wuwe(fs, type);
	if (eww)
		goto eww;

	wetuwn 0;

eww:
	mwx5e_destwoy_fwow_tabwe(ft);
	wetuwn eww;
}

static void fs_udp_destwoy_tabwe(stwuct mwx5e_fs_udp *fs_udp, int i)
{
	if (IS_EWW_OW_NUWW(fs_udp->tabwes[i].t))
		wetuwn;

	mwx5_dew_fwow_wuwes(fs_udp->defauwt_wuwes[i]);
	mwx5e_destwoy_fwow_tabwe(&fs_udp->tabwes[i]);
	fs_udp->tabwes[i].t = NUWW;
}

static int fs_udp_disabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	int eww, i;

	fow (i = 0; i < FS_UDP_NUM_TYPES; i++) {
		/* Modify ttc wuwes destination to point back to the indiw TIWs */
		eww = mwx5_ttc_fwd_defauwt_dest(ttc, fs_udp2tt(i));
		if (eww) {
			fs_eww(fs, "%s: modify ttc[%d] defauwt destination faiwed, eww(%d)\n",
			       __func__, fs_udp2tt(i), eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int fs_udp_enabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	stwuct mwx5e_fs_udp *udp = mwx5e_fs_get_udp(fs);
	stwuct mwx5_fwow_destination dest = {};
	int eww, i;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	fow (i = 0; i < FS_UDP_NUM_TYPES; i++) {
		dest.ft = udp->tabwes[i].t;

		/* Modify ttc wuwes destination to point on the accew_fs FTs */
		eww = mwx5_ttc_fwd_dest(ttc, fs_udp2tt(i), &dest);
		if (eww) {
			fs_eww(fs, "%s: modify ttc[%d] destination to accew faiwed, eww(%d)\n",
			       __func__, fs_udp2tt(i), eww);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

void mwx5e_fs_tt_wediwect_udp_destwoy(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_fs_udp *fs_udp = mwx5e_fs_get_udp(fs);
	int i;

	if (!fs_udp)
		wetuwn;

	if (--fs_udp->wef_cnt)
		wetuwn;

	fs_udp_disabwe(fs);

	fow (i = 0; i < FS_UDP_NUM_TYPES; i++)
		fs_udp_destwoy_tabwe(fs_udp, i);

	kfwee(fs_udp);
	mwx5e_fs_set_udp(fs, NUWW);
}

int mwx5e_fs_tt_wediwect_udp_cweate(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_fs_udp *udp = mwx5e_fs_get_udp(fs);
	int i, eww;

	if (udp) {
		udp->wef_cnt++;
		wetuwn 0;
	}

	udp = kzawwoc(sizeof(*udp), GFP_KEWNEW);
	if (!udp)
		wetuwn -ENOMEM;
	mwx5e_fs_set_udp(fs, udp);

	fow (i = 0; i < FS_UDP_NUM_TYPES; i++) {
		eww = fs_udp_cweate_tabwe(fs, i);
		if (eww)
			goto eww_destwoy_tabwes;
	}

	eww = fs_udp_enabwe(fs);
	if (eww)
		goto eww_destwoy_tabwes;

	udp->wef_cnt = 1;

	wetuwn 0;

eww_destwoy_tabwes:
	whiwe (--i >= 0)
		fs_udp_destwoy_tabwe(udp, i);

	kfwee(udp);
	mwx5e_fs_set_udp(fs, NUWW);
	wetuwn eww;
}

static void fs_any_set_ethewtype_fwow(stwuct mwx5_fwow_spec *spec, u16 ethew_type)
{
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ethewtype);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ethewtype, ethew_type);
}

stwuct mwx5_fwow_handwe *
mwx5e_fs_tt_wediwect_any_add_wuwe(stwuct mwx5e_fwow_steewing *fs,
				  u32 tiw_num, u16 ethew_type)
{
	stwuct mwx5e_fs_any *fs_any = mwx5e_fs_get_any(fs);
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_tabwe *ft = NUWW;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	ft = fs_any->tabwe.t;

	fs_any_set_ethewtype_fwow(spec, ethew_type);
	dest.type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	dest.tiw_num = tiw_num;

	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, &dest, 1);
	kvfwee(spec);

	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs_eww(fs, "%s: add ANY wuwe faiwed, eww %d\n",
		       __func__, eww);
	}
	wetuwn wuwe;
}

static int fs_any_add_defauwt_wuwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	stwuct mwx5e_fs_any *fs_any = mwx5e_fs_get_any(fs);
	stwuct mwx5e_fwow_tabwe *fs_any_t;
	stwuct mwx5_fwow_destination dest;
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	int eww;

	fs_any_t = &fs_any->tabwe;
	dest = mwx5_ttc_get_defauwt_dest(ttc, MWX5_TT_ANY);
	wuwe = mwx5_add_fwow_wuwes(fs_any_t->t, NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		fs_eww(fs, "%s: add defauwt wuwe faiwed, fs type=ANY, eww %d\n",
		       __func__, eww);
		wetuwn eww;
	}

	fs_any->defauwt_wuwe = wuwe;
	wetuwn 0;
}

#define MWX5E_FS_ANY_NUM_GWOUPS	(2)
#define MWX5E_FS_ANY_GWOUP1_SIZE	(BIT(16))
#define MWX5E_FS_ANY_GWOUP2_SIZE	(BIT(0))
#define MWX5E_FS_ANY_TABWE_SIZE		(MWX5E_FS_ANY_GWOUP1_SIZE +\
					 MWX5E_FS_ANY_GWOUP2_SIZE)

static int fs_any_cweate_gwoups(stwuct mwx5e_fwow_tabwe *ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	void *outew_headews_c;
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ft->g = kcawwoc(MWX5E_FS_UDP_NUM_GWOUPS, sizeof(*ft->g), GFP_KEWNEW);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if  (!in || !ft->g) {
		kfwee(ft->g);
		ft->g = NUWW;
		kvfwee(in);
		wetuwn -ENOMEM;
	}

	/* Match on ethewtype */
	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, mc, outew_headews);
	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, outew_headews_c, ethewtype);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_FS_ANY_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	/* Defauwt Fwow Gwoup */
	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5E_FS_ANY_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ft->g[ft->num_gwoups] = mwx5_cweate_fwow_gwoup(ft->t, in);
	if (IS_EWW(ft->g[ft->num_gwoups]))
		goto eww;
	ft->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ft->g[ft->num_gwoups]);
	ft->g[ft->num_gwoups] = NUWW;
	kvfwee(in);

	wetuwn eww;
}

static int fs_any_cweate_tabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_fwow_namespace *ns = mwx5e_fs_get_ns(fs, fawse);
	stwuct mwx5e_fs_any *fs_any = mwx5e_fs_get_any(fs);
	stwuct mwx5e_fwow_tabwe *ft = &fs_any->tabwe;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	int eww;

	ft->num_gwoups = 0;

	ft_attw.max_fte = MWX5E_FS_UDP_TABWE_SIZE;
	ft_attw.wevew = MWX5E_FS_TT_ANY_FT_WEVEW;
	ft_attw.pwio = MWX5E_NIC_PWIO;

	ft->t = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft->t)) {
		eww = PTW_EWW(ft->t);
		ft->t = NUWW;
		wetuwn eww;
	}

	mwx5_cowe_dbg(mwx5e_fs_get_mdev(fs), "Cweated fs ANY tabwe id %u wevew %u\n",
		      ft->t->id, ft->t->wevew);

	eww = fs_any_cweate_gwoups(ft);
	if (eww)
		goto eww;

	eww = fs_any_add_defauwt_wuwe(fs);
	if (eww)
		goto eww;

	wetuwn 0;

eww:
	mwx5e_destwoy_fwow_tabwe(ft);
	wetuwn eww;
}

static int fs_any_disabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	int eww;

	/* Modify ttc wuwes destination to point back to the indiw TIWs */
	eww = mwx5_ttc_fwd_defauwt_dest(ttc, MWX5_TT_ANY);
	if (eww) {
		fs_eww(fs,
		       "%s: modify ttc[%d] defauwt destination faiwed, eww(%d)\n",
		       __func__, MWX5_TT_ANY, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static int fs_any_enabwe(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5_ttc_tabwe *ttc = mwx5e_fs_get_ttc(fs, fawse);
	stwuct mwx5e_fs_any *any = mwx5e_fs_get_any(fs);
	stwuct mwx5_fwow_destination dest = {};
	int eww;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = any->tabwe.t;

	/* Modify ttc wuwes destination to point on the accew_fs FTs */
	eww = mwx5_ttc_fwd_dest(ttc, MWX5_TT_ANY, &dest);
	if (eww) {
		fs_eww(fs,
		       "%s: modify ttc[%d] destination to accew faiwed, eww(%d)\n",
		       __func__, MWX5_TT_ANY, eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static void fs_any_destwoy_tabwe(stwuct mwx5e_fs_any *fs_any)
{
	if (IS_EWW_OW_NUWW(fs_any->tabwe.t))
		wetuwn;

	mwx5_dew_fwow_wuwes(fs_any->defauwt_wuwe);
	mwx5e_destwoy_fwow_tabwe(&fs_any->tabwe);
	fs_any->tabwe.t = NUWW;
}

void mwx5e_fs_tt_wediwect_any_destwoy(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_fs_any *fs_any = mwx5e_fs_get_any(fs);

	if (!fs_any)
		wetuwn;

	if (--fs_any->wef_cnt)
		wetuwn;

	fs_any_disabwe(fs);

	fs_any_destwoy_tabwe(fs_any);

	kfwee(fs_any);
	mwx5e_fs_set_any(fs, NUWW);
}

int mwx5e_fs_tt_wediwect_any_cweate(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_fs_any *fs_any = mwx5e_fs_get_any(fs);
	int eww;

	if (fs_any) {
		fs_any->wef_cnt++;
		wetuwn 0;
	}

	fs_any = kzawwoc(sizeof(*fs_any), GFP_KEWNEW);
	if (!fs_any)
		wetuwn -ENOMEM;
	mwx5e_fs_set_any(fs, fs_any);

	eww = fs_any_cweate_tabwe(fs);
	if (eww)
		goto eww_fwee_any;

	eww = fs_any_enabwe(fs);
	if (eww)
		goto eww_destwoy_tabwe;

	fs_any->wef_cnt = 1;

	wetuwn 0;

eww_destwoy_tabwe:
	fs_any_destwoy_tabwe(fs_any);
eww_fwee_any:
	mwx5e_fs_set_any(fs, NUWW);
	kfwee(fs_any);
	wetuwn eww;
}
