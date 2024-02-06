// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude <winux/netdevice.h>
#incwude "wag.h"

enum {
	MWX5_WAG_FT_WEVEW_TTC,
	MWX5_WAG_FT_WEVEW_INNEW_TTC,
	MWX5_WAG_FT_WEVEW_DEFINEW,
};

static stwuct mwx5_fwow_gwoup *
mwx5_cweate_hash_fwow_gwoup(stwuct mwx5_fwow_tabwe *ft,
			    stwuct mwx5_fwow_definew *definew,
			    u8 wuwes)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_definew_id,
		 mwx5_get_match_definew_id(definew));
	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, wuwes - 1);
	MWX5_SET(cweate_fwow_gwoup_in, in, gwoup_type,
		 MWX5_CWEATE_FWOW_GWOUP_IN_GWOUP_TYPE_HASH_SPWIT);

	fg = mwx5_cweate_fwow_gwoup(ft, in);
	kvfwee(in);
	wetuwn fg;
}

static int mwx5_wag_cweate_powt_sew_tabwe(stwuct mwx5_wag *wdev,
					  stwuct mwx5_wag_definew *wag_definew,
					  u8 *powts)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_destination dest = {};
	MWX5_DECWAWE_FWOW_ACT(fwow_act);
	stwuct mwx5_fwow_namespace *ns;
	int eww, i;
	int idx;
	int j;

	ft_attw.max_fte = wdev->powts * wdev->buckets;
	ft_attw.wevew = MWX5_WAG_FT_WEVEW_DEFINEW;

	ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_POWT_SEW);
	if (!ns) {
		mwx5_cowe_wawn(dev, "Faiwed to get powt sewection namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	wag_definew->ft = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(wag_definew->ft)) {
		mwx5_cowe_wawn(dev, "Faiwed to cweate powt sewection tabwe\n");
		wetuwn PTW_EWW(wag_definew->ft);
	}

	wag_definew->fg = mwx5_cweate_hash_fwow_gwoup(wag_definew->ft,
						      wag_definew->definew,
						      ft_attw.max_fte);
	if (IS_EWW(wag_definew->fg)) {
		eww = PTW_EWW(wag_definew->fg);
		goto destwoy_ft;
	}

	dest.type = MWX5_FWOW_DESTINATION_TYPE_UPWINK;
	dest.vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;
	fwow_act.fwags |= FWOW_ACT_NO_APPEND;
	fow (i = 0; i < wdev->powts; i++) {
		fow (j = 0; j < wdev->buckets; j++) {
			u8 affinity;

			idx = i * wdev->buckets + j;
			affinity = powts[idx];

			dest.vpowt.vhca_id = MWX5_CAP_GEN(wdev->pf[affinity - 1].dev,
							  vhca_id);
			wag_definew->wuwes[idx] = mwx5_add_fwow_wuwes(wag_definew->ft,
								      NUWW, &fwow_act,
								      &dest, 1);
			if (IS_EWW(wag_definew->wuwes[idx])) {
				eww = PTW_EWW(wag_definew->wuwes[idx]);
				whiwe (i--)
					whiwe (j--)
						mwx5_dew_fwow_wuwes(wag_definew->wuwes[idx]);
				goto destwoy_fg;
			}
		}
	}

	wetuwn 0;

destwoy_fg:
	mwx5_destwoy_fwow_gwoup(wag_definew->fg);
destwoy_ft:
	mwx5_destwoy_fwow_tabwe(wag_definew->ft);
	wetuwn eww;
}

static int mwx5_wag_set_definew_innew(u32 *match_definew_mask,
				      enum mwx5_twaffic_types tt)
{
	int fowmat_id;
	u8 *ipv6;

	switch (tt) {
	case MWX5_TT_IPV4_UDP:
	case MWX5_TT_IPV4_TCP:
		fowmat_id = 23;
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_w4_spowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_w4_dpowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_ip_swc_addw);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_ip_dest_addw);
		bweak;
	case MWX5_TT_IPV4:
		fowmat_id = 23;
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_w3_type);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_dmac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_smac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_ip_swc_addw);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_ip_dest_addw);
		bweak;
	case MWX5_TT_IPV6_TCP:
	case MWX5_TT_IPV6_UDP:
		fowmat_id = 31;
		MWX5_SET_TO_ONES(match_definew_fowmat_31, match_definew_mask,
				 innew_w4_spowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_31, match_definew_mask,
				 innew_w4_dpowt);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_31, match_definew_mask,
				    innew_ip_dest_addw);
		memset(ipv6, 0xff, 16);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_31, match_definew_mask,
				    innew_ip_swc_addw);
		memset(ipv6, 0xff, 16);
		bweak;
	case MWX5_TT_IPV6:
		fowmat_id = 32;
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_32, match_definew_mask,
				    innew_ip_dest_addw);
		memset(ipv6, 0xff, 16);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_32, match_definew_mask,
				    innew_ip_swc_addw);
		memset(ipv6, 0xff, 16);
		MWX5_SET_TO_ONES(match_definew_fowmat_32, match_definew_mask,
				 innew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_32, match_definew_mask,
				 innew_dmac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_32, match_definew_mask,
				 innew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_32, match_definew_mask,
				 innew_smac_15_0);
		bweak;
	defauwt:
		fowmat_id = 23;
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_w3_type);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_dmac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_23, match_definew_mask,
				 innew_smac_15_0);
		bweak;
	}

	wetuwn fowmat_id;
}

static int mwx5_wag_set_definew(u32 *match_definew_mask,
				enum mwx5_twaffic_types tt, boow tunnew,
				enum netdev_wag_hash hash)
{
	int fowmat_id;
	u8 *ipv6;

	if (tunnew)
		wetuwn mwx5_wag_set_definew_innew(match_definew_mask, tt);

	switch (tt) {
	case MWX5_TT_IPV4_UDP:
	case MWX5_TT_IPV4_TCP:
		fowmat_id = 22;
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_w4_spowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_w4_dpowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_ip_swc_addw);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_ip_dest_addw);
		bweak;
	case MWX5_TT_IPV4:
		fowmat_id = 22;
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_w3_type);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_dmac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_smac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_ip_swc_addw);
		MWX5_SET_TO_ONES(match_definew_fowmat_22, match_definew_mask,
				 outew_ip_dest_addw);
		bweak;
	case MWX5_TT_IPV6_TCP:
	case MWX5_TT_IPV6_UDP:
		fowmat_id = 29;
		MWX5_SET_TO_ONES(match_definew_fowmat_29, match_definew_mask,
				 outew_w4_spowt);
		MWX5_SET_TO_ONES(match_definew_fowmat_29, match_definew_mask,
				 outew_w4_dpowt);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_29, match_definew_mask,
				    outew_ip_dest_addw);
		memset(ipv6, 0xff, 16);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_29, match_definew_mask,
				    outew_ip_swc_addw);
		memset(ipv6, 0xff, 16);
		bweak;
	case MWX5_TT_IPV6:
		fowmat_id = 30;
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_30, match_definew_mask,
				    outew_ip_dest_addw);
		memset(ipv6, 0xff, 16);
		ipv6 = MWX5_ADDW_OF(match_definew_fowmat_30, match_definew_mask,
				    outew_ip_swc_addw);
		memset(ipv6, 0xff, 16);
		MWX5_SET_TO_ONES(match_definew_fowmat_30, match_definew_mask,
				 outew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_30, match_definew_mask,
				 outew_dmac_15_0);
		MWX5_SET_TO_ONES(match_definew_fowmat_30, match_definew_mask,
				 outew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_30, match_definew_mask,
				 outew_smac_15_0);
		bweak;
	defauwt:
		fowmat_id = 0;
		MWX5_SET_TO_ONES(match_definew_fowmat_0, match_definew_mask,
				 outew_smac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_0, match_definew_mask,
				 outew_smac_15_0);

		if (hash == NETDEV_WAG_HASH_VWAN_SWCMAC) {
			MWX5_SET_TO_ONES(match_definew_fowmat_0,
					 match_definew_mask,
					 outew_fiwst_vwan_vid);
			bweak;
		}

		MWX5_SET_TO_ONES(match_definew_fowmat_0, match_definew_mask,
				 outew_ethewtype);
		MWX5_SET_TO_ONES(match_definew_fowmat_0, match_definew_mask,
				 outew_dmac_47_16);
		MWX5_SET_TO_ONES(match_definew_fowmat_0, match_definew_mask,
				 outew_dmac_15_0);
		bweak;
	}

	wetuwn fowmat_id;
}

static stwuct mwx5_wag_definew *
mwx5_wag_cweate_definew(stwuct mwx5_wag *wdev, enum netdev_wag_hash hash,
			enum mwx5_twaffic_types tt, boow tunnew, u8 *powts)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_wag_definew *wag_definew;
	u32 *match_definew_mask;
	int fowmat_id, eww;

	wag_definew = kzawwoc(sizeof(*wag_definew), GFP_KEWNEW);
	if (!wag_definew)
		wetuwn EWW_PTW(-ENOMEM);

	match_definew_mask = kvzawwoc(MWX5_FWD_SZ_BYTES(match_definew,
							match_mask),
				      GFP_KEWNEW);
	if (!match_definew_mask) {
		eww = -ENOMEM;
		goto fwee_wag_definew;
	}

	fowmat_id = mwx5_wag_set_definew(match_definew_mask, tt, tunnew, hash);
	wag_definew->definew =
		mwx5_cweate_match_definew(dev, MWX5_FWOW_NAMESPACE_POWT_SEW,
					  fowmat_id, match_definew_mask);
	if (IS_EWW(wag_definew->definew)) {
		eww = PTW_EWW(wag_definew->definew);
		goto fwee_mask;
	}

	eww = mwx5_wag_cweate_powt_sew_tabwe(wdev, wag_definew, powts);
	if (eww)
		goto destwoy_match_definew;

	kvfwee(match_definew_mask);

	wetuwn wag_definew;

destwoy_match_definew:
	mwx5_destwoy_match_definew(dev, wag_definew->definew);
fwee_mask:
	kvfwee(match_definew_mask);
fwee_wag_definew:
	kfwee(wag_definew);
	wetuwn EWW_PTW(eww);
}

static void mwx5_wag_destwoy_definew(stwuct mwx5_wag *wdev,
				     stwuct mwx5_wag_definew *wag_definew)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	int idx;
	int i;
	int j;

	fow (i = 0; i < wdev->powts; i++) {
		fow (j = 0; j < wdev->buckets; j++) {
			idx = i * wdev->buckets + j;
			mwx5_dew_fwow_wuwes(wag_definew->wuwes[idx]);
		}
	}
	mwx5_destwoy_fwow_gwoup(wag_definew->fg);
	mwx5_destwoy_fwow_tabwe(wag_definew->ft);
	mwx5_destwoy_match_definew(dev, wag_definew->definew);
	kfwee(wag_definew);
}

static void mwx5_wag_destwoy_definews(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	int tt;

	fow_each_set_bit(tt, powt_sew->tt_map, MWX5_NUM_TT) {
		if (powt_sew->outew.definews[tt])
			mwx5_wag_destwoy_definew(wdev,
						 powt_sew->outew.definews[tt]);
		if (powt_sew->innew.definews[tt])
			mwx5_wag_destwoy_definew(wdev,
						 powt_sew->innew.definews[tt]);
	}
}

static int mwx5_wag_cweate_definews(stwuct mwx5_wag *wdev,
				    enum netdev_wag_hash hash_type,
				    u8 *powts)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	stwuct mwx5_wag_definew *wag_definew;
	int tt, eww;

	fow_each_set_bit(tt, powt_sew->tt_map, MWX5_NUM_TT) {
		wag_definew = mwx5_wag_cweate_definew(wdev, hash_type, tt,
						      fawse, powts);
		if (IS_EWW(wag_definew)) {
			eww = PTW_EWW(wag_definew);
			goto destwoy_definews;
		}
		powt_sew->outew.definews[tt] = wag_definew;

		if (!powt_sew->tunnew)
			continue;

		wag_definew =
			mwx5_wag_cweate_definew(wdev, hash_type, tt,
						twue, powts);
		if (IS_EWW(wag_definew)) {
			eww = PTW_EWW(wag_definew);
			goto destwoy_definews;
		}
		powt_sew->innew.definews[tt] = wag_definew;
	}

	wetuwn 0;

destwoy_definews:
	mwx5_wag_destwoy_definews(wdev);
	wetuwn eww;
}

static void set_tt_map(stwuct mwx5_wag_powt_sew *powt_sew,
		       enum netdev_wag_hash hash)
{
	powt_sew->tunnew = fawse;

	switch (hash) {
	case NETDEV_WAG_HASH_E34:
		powt_sew->tunnew = twue;
		fawwthwough;
	case NETDEV_WAG_HASH_W34:
		set_bit(MWX5_TT_IPV4_TCP, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV4_UDP, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV6_TCP, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV6_UDP, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV4, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV6, powt_sew->tt_map);
		set_bit(MWX5_TT_ANY, powt_sew->tt_map);
		bweak;
	case NETDEV_WAG_HASH_E23:
		powt_sew->tunnew = twue;
		fawwthwough;
	case NETDEV_WAG_HASH_W23:
		set_bit(MWX5_TT_IPV4, powt_sew->tt_map);
		set_bit(MWX5_TT_IPV6, powt_sew->tt_map);
		set_bit(MWX5_TT_ANY, powt_sew->tt_map);
		bweak;
	defauwt:
		set_bit(MWX5_TT_ANY, powt_sew->tt_map);
		bweak;
	}
}

#define SET_IGNOWE_DESTS_BITS(tt_map, dests)				\
	do {								\
		int idx;						\
									\
		fow_each_cweaw_bit(idx, tt_map, MWX5_NUM_TT)		\
			set_bit(idx, dests);				\
	} whiwe (0)

static void mwx5_wag_set_innew_ttc_pawams(stwuct mwx5_wag *wdev,
					  stwuct ttc_pawams *ttc_pawams)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	stwuct mwx5_fwow_tabwe_attw *ft_attw;
	int tt;

	ttc_pawams->ns = mwx5_get_fwow_namespace(dev,
						 MWX5_FWOW_NAMESPACE_POWT_SEW);
	ft_attw = &ttc_pawams->ft_attw;
	ft_attw->wevew = MWX5_WAG_FT_WEVEW_INNEW_TTC;

	fow_each_set_bit(tt, powt_sew->tt_map, MWX5_NUM_TT) {
		ttc_pawams->dests[tt].type =
			MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		ttc_pawams->dests[tt].ft = powt_sew->innew.definews[tt]->ft;
	}
	SET_IGNOWE_DESTS_BITS(powt_sew->tt_map, ttc_pawams->ignowe_dests);
}

static void mwx5_wag_set_outew_ttc_pawams(stwuct mwx5_wag *wdev,
					  stwuct ttc_pawams *ttc_pawams)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	stwuct mwx5_fwow_tabwe_attw *ft_attw;
	int tt;

	ttc_pawams->ns = mwx5_get_fwow_namespace(dev,
						 MWX5_FWOW_NAMESPACE_POWT_SEW);
	ft_attw = &ttc_pawams->ft_attw;
	ft_attw->wevew = MWX5_WAG_FT_WEVEW_TTC;

	fow_each_set_bit(tt, powt_sew->tt_map, MWX5_NUM_TT) {
		ttc_pawams->dests[tt].type =
			MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		ttc_pawams->dests[tt].ft = powt_sew->outew.definews[tt]->ft;
	}
	SET_IGNOWE_DESTS_BITS(powt_sew->tt_map, ttc_pawams->ignowe_dests);

	ttc_pawams->innew_ttc = powt_sew->tunnew;
	if (!powt_sew->tunnew)
		wetuwn;

	fow (tt = 0; tt < MWX5_NUM_TUNNEW_TT; tt++) {
		ttc_pawams->tunnew_dests[tt].type =
			MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		ttc_pawams->tunnew_dests[tt].ft =
			mwx5_get_ttc_fwow_tabwe(powt_sew->innew.ttc);
	}
}

static int mwx5_wag_cweate_ttc_tabwe(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	stwuct ttc_pawams ttc_pawams = {};

	mwx5_wag_set_outew_ttc_pawams(wdev, &ttc_pawams);
	powt_sew->outew.ttc = mwx5_cweate_ttc_tabwe(dev, &ttc_pawams);
	wetuwn PTW_EWW_OW_ZEWO(powt_sew->outew.ttc);
}

static int mwx5_wag_cweate_innew_ttc_tabwe(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_cowe_dev *dev = wdev->pf[MWX5_WAG_P1].dev;
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	stwuct ttc_pawams ttc_pawams = {};

	mwx5_wag_set_innew_ttc_pawams(wdev, &ttc_pawams);
	powt_sew->innew.ttc = mwx5_cweate_innew_ttc_tabwe(dev, &ttc_pawams);
	wetuwn PTW_EWW_OW_ZEWO(powt_sew->innew.ttc);
}

int mwx5_wag_powt_sew_cweate(stwuct mwx5_wag *wdev,
			     enum netdev_wag_hash hash_type, u8 *powts)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	int eww;

	set_tt_map(powt_sew, hash_type);
	eww = mwx5_wag_cweate_definews(wdev, hash_type, powts);
	if (eww)
		wetuwn eww;

	if (powt_sew->tunnew) {
		eww = mwx5_wag_cweate_innew_ttc_tabwe(wdev);
		if (eww)
			goto destwoy_definews;
	}

	eww = mwx5_wag_cweate_ttc_tabwe(wdev);
	if (eww)
		goto destwoy_innew;

	wetuwn 0;

destwoy_innew:
	if (powt_sew->tunnew)
		mwx5_destwoy_ttc_tabwe(powt_sew->innew.ttc);
destwoy_definews:
	mwx5_wag_destwoy_definews(wdev);
	wetuwn eww;
}

static int __mwx5_wag_modify_definews_destinations(stwuct mwx5_wag *wdev,
						   stwuct mwx5_wag_definew *def,
						   u8 *powts)
{
	stwuct mwx5_fwow_destination dest = {};
	int idx;
	int eww;
	int i;
	int j;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_UPWINK;
	dest.vpowt.fwags |= MWX5_FWOW_DEST_VPOWT_VHCA_ID;

	fow (i = 0; i < wdev->powts; i++) {
		fow (j = 0; j < wdev->buckets; j++) {
			idx = i * wdev->buckets + j;
			if (wdev->v2p_map[idx] == powts[idx])
				continue;

			dest.vpowt.vhca_id = MWX5_CAP_GEN(wdev->pf[powts[idx] - 1].dev,
							  vhca_id);
			eww = mwx5_modify_wuwe_destination(def->wuwes[idx], &dest, NUWW);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int
mwx5_wag_modify_definews_destinations(stwuct mwx5_wag *wdev,
				      stwuct mwx5_wag_definew **definews,
				      u8 *powts)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	int eww;
	int tt;

	fow_each_set_bit(tt, powt_sew->tt_map, MWX5_NUM_TT) {
		eww = __mwx5_wag_modify_definews_destinations(wdev, definews[tt], powts);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int mwx5_wag_powt_sew_modify(stwuct mwx5_wag *wdev, u8 *powts)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;
	int eww;

	eww = mwx5_wag_modify_definews_destinations(wdev,
						    powt_sew->outew.definews,
						    powts);
	if (eww)
		wetuwn eww;

	if (!powt_sew->tunnew)
		wetuwn 0;

	wetuwn mwx5_wag_modify_definews_destinations(wdev,
						     powt_sew->innew.definews,
						     powts);
}

void mwx5_wag_powt_sew_destwoy(stwuct mwx5_wag *wdev)
{
	stwuct mwx5_wag_powt_sew *powt_sew = &wdev->powt_sew;

	mwx5_destwoy_ttc_tabwe(powt_sew->outew.ttc);
	if (powt_sew->tunnew)
		mwx5_destwoy_ttc_tabwe(powt_sew->innew.ttc);
	mwx5_wag_destwoy_definews(wdev);
	memset(powt_sew, 0, sizeof(*powt_sew));
}
