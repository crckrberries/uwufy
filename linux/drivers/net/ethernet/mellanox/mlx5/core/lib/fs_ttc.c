// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021 NVIDIA COWPOWATION & AFFIWIATES.

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/tcp.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"
#incwude "wib/fs_ttc.h"

#define MWX5_TTC_NUM_GWOUPS	3
#define MWX5_TTC_GWOUP1_SIZE	(BIT(3) + MWX5_NUM_TUNNEW_TT)
#define MWX5_TTC_GWOUP2_SIZE	 BIT(1)
#define MWX5_TTC_GWOUP3_SIZE	 BIT(0)
#define MWX5_TTC_TABWE_SIZE	(MWX5_TTC_GWOUP1_SIZE +\
				 MWX5_TTC_GWOUP2_SIZE +\
				 MWX5_TTC_GWOUP3_SIZE)

#define MWX5_INNEW_TTC_NUM_GWOUPS	3
#define MWX5_INNEW_TTC_GWOUP1_SIZE	BIT(3)
#define MWX5_INNEW_TTC_GWOUP2_SIZE	BIT(1)
#define MWX5_INNEW_TTC_GWOUP3_SIZE	BIT(0)
#define MWX5_INNEW_TTC_TABWE_SIZE	(MWX5_INNEW_TTC_GWOUP1_SIZE +\
					 MWX5_INNEW_TTC_GWOUP2_SIZE +\
					 MWX5_INNEW_TTC_GWOUP3_SIZE)

/* W3/W4 twaffic type cwassifiew */
stwuct mwx5_ttc_tabwe {
	int num_gwoups;
	stwuct mwx5_fwow_tabwe *t;
	stwuct mwx5_fwow_gwoup **g;
	stwuct mwx5_ttc_wuwe wuwes[MWX5_NUM_TT];
	stwuct mwx5_fwow_handwe *tunnew_wuwes[MWX5_NUM_TUNNEW_TT];
};

stwuct mwx5_fwow_tabwe *mwx5_get_ttc_fwow_tabwe(stwuct mwx5_ttc_tabwe *ttc)
{
	wetuwn ttc->t;
}

static void mwx5_cweanup_ttc_wuwes(stwuct mwx5_ttc_tabwe *ttc)
{
	int i;

	fow (i = 0; i < MWX5_NUM_TT; i++) {
		if (!IS_EWW_OW_NUWW(ttc->wuwes[i].wuwe)) {
			mwx5_dew_fwow_wuwes(ttc->wuwes[i].wuwe);
			ttc->wuwes[i].wuwe = NUWW;
		}
	}

	fow (i = 0; i < MWX5_NUM_TUNNEW_TT; i++) {
		if (!IS_EWW_OW_NUWW(ttc->tunnew_wuwes[i])) {
			mwx5_dew_fwow_wuwes(ttc->tunnew_wuwes[i]);
			ttc->tunnew_wuwes[i] = NUWW;
		}
	}
}

stwuct mwx5_etype_pwoto {
	u16 etype;
	u8 pwoto;
};

static stwuct mwx5_etype_pwoto ttc_wuwes[] = {
	[MWX5_TT_IPV4_TCP] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_TCP,
	},
	[MWX5_TT_IPV6_TCP] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_TCP,
	},
	[MWX5_TT_IPV4_UDP] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_UDP,
	},
	[MWX5_TT_IPV6_UDP] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_UDP,
	},
	[MWX5_TT_IPV4_IPSEC_AH] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_AH,
	},
	[MWX5_TT_IPV6_IPSEC_AH] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_AH,
	},
	[MWX5_TT_IPV4_IPSEC_ESP] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_ESP,
	},
	[MWX5_TT_IPV6_IPSEC_ESP] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_ESP,
	},
	[MWX5_TT_IPV4] = {
		.etype = ETH_P_IP,
		.pwoto = 0,
	},
	[MWX5_TT_IPV6] = {
		.etype = ETH_P_IPV6,
		.pwoto = 0,
	},
	[MWX5_TT_ANY] = {
		.etype = 0,
		.pwoto = 0,
	},
};

static stwuct mwx5_etype_pwoto ttc_tunnew_wuwes[] = {
	[MWX5_TT_IPV4_GWE] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_GWE,
	},
	[MWX5_TT_IPV6_GWE] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_GWE,
	},
	[MWX5_TT_IPV4_IPIP] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_IPIP,
	},
	[MWX5_TT_IPV6_IPIP] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_IPIP,
	},
	[MWX5_TT_IPV4_IPV6] = {
		.etype = ETH_P_IP,
		.pwoto = IPPWOTO_IPV6,
	},
	[MWX5_TT_IPV6_IPV6] = {
		.etype = ETH_P_IPV6,
		.pwoto = IPPWOTO_IPV6,
	},

};

u8 mwx5_get_pwoto_by_tunnew_type(enum mwx5_tunnew_types tt)
{
	wetuwn ttc_tunnew_wuwes[tt].pwoto;
}

static boow mwx5_tunnew_pwoto_suppowted_wx(stwuct mwx5_cowe_dev *mdev,
					   u8 pwoto_type)
{
	switch (pwoto_type) {
	case IPPWOTO_GWE:
		wetuwn MWX5_CAP_ETH(mdev, tunnew_statewess_gwe);
	case IPPWOTO_IPIP:
	case IPPWOTO_IPV6:
		wetuwn (MWX5_CAP_ETH(mdev, tunnew_statewess_ip_ovew_ip) ||
			MWX5_CAP_ETH(mdev, tunnew_statewess_ip_ovew_ip_wx));
	defauwt:
		wetuwn fawse;
	}
}

static boow mwx5_tunnew_any_wx_pwoto_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	int tt;

	fow (tt = 0; tt < MWX5_NUM_TUNNEW_TT; tt++) {
		if (mwx5_tunnew_pwoto_suppowted_wx(mdev,
						   ttc_tunnew_wuwes[tt].pwoto))
			wetuwn twue;
	}
	wetuwn fawse;
}

boow mwx5_tunnew_innew_ft_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn (mwx5_tunnew_any_wx_pwoto_suppowted(mdev) &&
		MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					  ft_fiewd_suppowt.innew_ip_vewsion));
}

static u8 mwx5_etype_to_ipv(u16 ethewtype)
{
	if (ethewtype == ETH_P_IP)
		wetuwn 4;

	if (ethewtype == ETH_P_IPV6)
		wetuwn 6;

	wetuwn 0;
}

static stwuct mwx5_fwow_handwe *
mwx5_genewate_ttc_wuwe(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fwow_tabwe *ft,
		       stwuct mwx5_fwow_destination *dest, u16 etype, u8 pwoto)
{
	int match_ipv_outew =
		MWX5_CAP_FWOWTABWE_NIC_WX(dev,
					  ft_fiewd_suppowt.outew_ip_vewsion);
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;
	u8 ipv;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	if (pwoto) {
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_pwotocow);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_pwotocow, pwoto);
	}

	ipv = mwx5_etype_to_ipv(etype);
	if (match_ipv_outew && ipv) {
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ip_vewsion);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_vewsion, ipv);
	} ewse if (etype) {
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.ethewtype);
		MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ethewtype, etype);
	}

	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(dev, "%s: add wuwe faiwed\n", __func__);
	}

	kvfwee(spec);
	wetuwn eww ? EWW_PTW(eww) : wuwe;
}

static int mwx5_genewate_ttc_tabwe_wuwes(stwuct mwx5_cowe_dev *dev,
					 stwuct ttc_pawams *pawams,
					 stwuct mwx5_ttc_tabwe *ttc)
{
	stwuct mwx5_fwow_handwe **twuwes;
	stwuct mwx5_ttc_wuwe *wuwes;
	stwuct mwx5_fwow_tabwe *ft;
	int tt;
	int eww;

	ft = ttc->t;
	wuwes = ttc->wuwes;
	fow (tt = 0; tt < MWX5_NUM_TT; tt++) {
		stwuct mwx5_ttc_wuwe *wuwe = &wuwes[tt];

		if (test_bit(tt, pawams->ignowe_dests))
			continue;
		wuwe->wuwe = mwx5_genewate_ttc_wuwe(dev, ft, &pawams->dests[tt],
						    ttc_wuwes[tt].etype,
						    ttc_wuwes[tt].pwoto);
		if (IS_EWW(wuwe->wuwe)) {
			eww = PTW_EWW(wuwe->wuwe);
			wuwe->wuwe = NUWW;
			goto dew_wuwes;
		}
		wuwe->defauwt_dest = pawams->dests[tt];
	}

	if (!pawams->innew_ttc || !mwx5_tunnew_innew_ft_suppowted(dev))
		wetuwn 0;

	twuwes    = ttc->tunnew_wuwes;
	fow (tt = 0; tt < MWX5_NUM_TUNNEW_TT; tt++) {
		if (!mwx5_tunnew_pwoto_suppowted_wx(dev,
						    ttc_tunnew_wuwes[tt].pwoto))
			continue;
		if (test_bit(tt, pawams->ignowe_tunnew_dests))
			continue;
		twuwes[tt] = mwx5_genewate_ttc_wuwe(dev, ft,
						    &pawams->tunnew_dests[tt],
						    ttc_tunnew_wuwes[tt].etype,
						    ttc_tunnew_wuwes[tt].pwoto);
		if (IS_EWW(twuwes[tt])) {
			eww = PTW_EWW(twuwes[tt]);
			twuwes[tt] = NUWW;
			goto dew_wuwes;
		}
	}

	wetuwn 0;

dew_wuwes:
	mwx5_cweanup_ttc_wuwes(ttc);
	wetuwn eww;
}

static int mwx5_cweate_ttc_tabwe_gwoups(stwuct mwx5_ttc_tabwe *ttc,
					boow use_ipv)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ttc->g = kcawwoc(MWX5_TTC_NUM_GWOUPS, sizeof(*ttc->g), GFP_KEWNEW);
	if (!ttc->g)
		wetuwn -ENOMEM;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		kfwee(ttc->g);
		ttc->g = NUWW;
		wetuwn -ENOMEM;
	}

	/* W4 Gwoup */
	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ip_pwotocow);
	if (use_ipv)
		MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ip_vewsion);
	ewse
		MWX5_SET_TO_ONES(fte_match_pawam, mc, outew_headews.ethewtype);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_TTC_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	/* W3 Gwoup */
	MWX5_SET(fte_match_pawam, mc, outew_headews.ip_pwotocow, 0);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_TTC_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	/* Any Gwoup */
	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_TTC_GWOUP3_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ttc->g[ttc->num_gwoups]);
	ttc->g[ttc->num_gwoups] = NUWW;
	kvfwee(in);

	wetuwn eww;
}

static stwuct mwx5_fwow_handwe *
mwx5_genewate_innew_ttc_wuwe(stwuct mwx5_cowe_dev *dev,
			     stwuct mwx5_fwow_tabwe *ft,
			     stwuct mwx5_fwow_destination *dest,
			     u16 etype, u8 pwoto)
{
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;
	u8 ipv;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);

	ipv = mwx5_etype_to_ipv(etype);
	if (etype && ipv) {
		spec->match_cwitewia_enabwe = MWX5_MATCH_INNEW_HEADEWS;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, innew_headews.ip_vewsion);
		MWX5_SET(fte_match_pawam, spec->match_vawue, innew_headews.ip_vewsion, ipv);
	}

	if (pwoto) {
		spec->match_cwitewia_enabwe = MWX5_MATCH_INNEW_HEADEWS;
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, innew_headews.ip_pwotocow);
		MWX5_SET(fte_match_pawam, spec->match_vawue, innew_headews.ip_pwotocow, pwoto);
	}

	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dest, 1);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		mwx5_cowe_eww(dev, "%s: add innew TTC wuwe faiwed\n", __func__);
	}

	kvfwee(spec);
	wetuwn eww ? EWW_PTW(eww) : wuwe;
}

static int mwx5_genewate_innew_ttc_tabwe_wuwes(stwuct mwx5_cowe_dev *dev,
					       stwuct ttc_pawams *pawams,
					       stwuct mwx5_ttc_tabwe *ttc)
{
	stwuct mwx5_ttc_wuwe *wuwes;
	stwuct mwx5_fwow_tabwe *ft;
	int eww;
	int tt;

	ft = ttc->t;
	wuwes = ttc->wuwes;

	fow (tt = 0; tt < MWX5_NUM_TT; tt++) {
		stwuct mwx5_ttc_wuwe *wuwe = &wuwes[tt];

		if (test_bit(tt, pawams->ignowe_dests))
			continue;
		wuwe->wuwe = mwx5_genewate_innew_ttc_wuwe(dev, ft,
							  &pawams->dests[tt],
							  ttc_wuwes[tt].etype,
							  ttc_wuwes[tt].pwoto);
		if (IS_EWW(wuwe->wuwe)) {
			eww = PTW_EWW(wuwe->wuwe);
			wuwe->wuwe = NUWW;
			goto dew_wuwes;
		}
		wuwe->defauwt_dest = pawams->dests[tt];
	}

	wetuwn 0;

dew_wuwes:

	mwx5_cweanup_ttc_wuwes(ttc);
	wetuwn eww;
}

static int mwx5_cweate_innew_ttc_tabwe_gwoups(stwuct mwx5_ttc_tabwe *ttc)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	int ix = 0;
	u32 *in;
	int eww;
	u8 *mc;

	ttc->g = kcawwoc(MWX5_INNEW_TTC_NUM_GWOUPS, sizeof(*ttc->g),
			 GFP_KEWNEW);
	if (!ttc->g)
		wetuwn -ENOMEM;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		kfwee(ttc->g);
		ttc->g = NUWW;
		wetuwn -ENOMEM;
	}

	/* W4 Gwoup */
	mc = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, innew_headews.ip_pwotocow);
	MWX5_SET_TO_ONES(fte_match_pawam, mc, innew_headews.ip_vewsion);
	MWX5_SET_CFG(in, match_cwitewia_enabwe, MWX5_MATCH_INNEW_HEADEWS);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_INNEW_TTC_GWOUP1_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	/* W3 Gwoup */
	MWX5_SET(fte_match_pawam, mc, innew_headews.ip_pwotocow, 0);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_INNEW_TTC_GWOUP2_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	/* Any Gwoup */
	memset(in, 0, inwen);
	MWX5_SET_CFG(in, stawt_fwow_index, ix);
	ix += MWX5_INNEW_TTC_GWOUP3_SIZE;
	MWX5_SET_CFG(in, end_fwow_index, ix - 1);
	ttc->g[ttc->num_gwoups] = mwx5_cweate_fwow_gwoup(ttc->t, in);
	if (IS_EWW(ttc->g[ttc->num_gwoups]))
		goto eww;
	ttc->num_gwoups++;

	kvfwee(in);
	wetuwn 0;

eww:
	eww = PTW_EWW(ttc->g[ttc->num_gwoups]);
	ttc->g[ttc->num_gwoups] = NUWW;
	kvfwee(in);

	wetuwn eww;
}

stwuct mwx5_ttc_tabwe *mwx5_cweate_innew_ttc_tabwe(stwuct mwx5_cowe_dev *dev,
						   stwuct ttc_pawams *pawams)
{
	stwuct mwx5_ttc_tabwe *ttc;
	int eww;

	ttc = kvzawwoc(sizeof(*ttc), GFP_KEWNEW);
	if (!ttc)
		wetuwn EWW_PTW(-ENOMEM);

	WAWN_ON_ONCE(pawams->ft_attw.max_fte);
	pawams->ft_attw.max_fte = MWX5_INNEW_TTC_TABWE_SIZE;
	ttc->t = mwx5_cweate_fwow_tabwe(pawams->ns, &pawams->ft_attw);
	if (IS_EWW(ttc->t)) {
		eww = PTW_EWW(ttc->t);
		kvfwee(ttc);
		wetuwn EWW_PTW(eww);
	}

	eww = mwx5_cweate_innew_ttc_tabwe_gwoups(ttc);
	if (eww)
		goto destwoy_ft;

	eww = mwx5_genewate_innew_ttc_tabwe_wuwes(dev, pawams, ttc);
	if (eww)
		goto destwoy_ft;

	wetuwn ttc;

destwoy_ft:
	mwx5_destwoy_ttc_tabwe(ttc);
	wetuwn EWW_PTW(eww);
}

void mwx5_destwoy_ttc_tabwe(stwuct mwx5_ttc_tabwe *ttc)
{
	int i;

	mwx5_cweanup_ttc_wuwes(ttc);
	fow (i = ttc->num_gwoups - 1; i >= 0; i--) {
		if (!IS_EWW_OW_NUWW(ttc->g[i]))
			mwx5_destwoy_fwow_gwoup(ttc->g[i]);
		ttc->g[i] = NUWW;
	}

	kfwee(ttc->g);
	mwx5_destwoy_fwow_tabwe(ttc->t);
	kvfwee(ttc);
}

stwuct mwx5_ttc_tabwe *mwx5_cweate_ttc_tabwe(stwuct mwx5_cowe_dev *dev,
					     stwuct ttc_pawams *pawams)
{
	boow match_ipv_outew =
		MWX5_CAP_FWOWTABWE_NIC_WX(dev,
					  ft_fiewd_suppowt.outew_ip_vewsion);
	stwuct mwx5_ttc_tabwe *ttc;
	int eww;

	ttc = kvzawwoc(sizeof(*ttc), GFP_KEWNEW);
	if (!ttc)
		wetuwn EWW_PTW(-ENOMEM);

	WAWN_ON_ONCE(pawams->ft_attw.max_fte);
	pawams->ft_attw.max_fte = MWX5_TTC_TABWE_SIZE;
	ttc->t = mwx5_cweate_fwow_tabwe(pawams->ns, &pawams->ft_attw);
	if (IS_EWW(ttc->t)) {
		eww = PTW_EWW(ttc->t);
		kvfwee(ttc);
		wetuwn EWW_PTW(eww);
	}

	eww = mwx5_cweate_ttc_tabwe_gwoups(ttc, match_ipv_outew);
	if (eww)
		goto destwoy_ft;

	eww = mwx5_genewate_ttc_tabwe_wuwes(dev, pawams, ttc);
	if (eww)
		goto destwoy_ft;

	wetuwn ttc;

destwoy_ft:
	mwx5_destwoy_ttc_tabwe(ttc);
	wetuwn EWW_PTW(eww);
}

int mwx5_ttc_fwd_dest(stwuct mwx5_ttc_tabwe *ttc, enum mwx5_twaffic_types type,
		      stwuct mwx5_fwow_destination *new_dest)
{
	wetuwn mwx5_modify_wuwe_destination(ttc->wuwes[type].wuwe, new_dest,
					    NUWW);
}

stwuct mwx5_fwow_destination
mwx5_ttc_get_defauwt_dest(stwuct mwx5_ttc_tabwe *ttc,
			  enum mwx5_twaffic_types type)
{
	stwuct mwx5_fwow_destination *dest = &ttc->wuwes[type].defauwt_dest;

	WAWN_ONCE(dest->type != MWX5_FWOW_DESTINATION_TYPE_TIW,
		  "TTC[%d] defauwt dest is not setup yet", type);

	wetuwn *dest;
}

int mwx5_ttc_fwd_defauwt_dest(stwuct mwx5_ttc_tabwe *ttc,
			      enum mwx5_twaffic_types type)
{
	stwuct mwx5_fwow_destination dest = mwx5_ttc_get_defauwt_dest(ttc, type);

	wetuwn mwx5_ttc_fwd_dest(ttc, type, &dest);
}
