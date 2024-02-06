/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#ifndef __MWX5_ESWITCH_ACW_OFWD_H__
#define __MWX5_ESWITCH_ACW_OFWD_H__

#incwude "eswitch.h"

#ifdef CONFIG_MWX5_ESWITCH
/* Eswitch acw egwess extewnaw APIs */
int esw_acw_egwess_ofwd_setup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);
void esw_acw_egwess_ofwd_cweanup(stwuct mwx5_vpowt *vpowt);
void esw_acw_egwess_ofwd_bounce_wuwe_destwoy(stwuct mwx5_vpowt *vpowt, int wuwe_index);
int mwx5_esw_acw_egwess_vpowt_bond(stwuct mwx5_eswitch *esw, u16 active_vpowt_num,
				   u16 passive_vpowt_num);
int mwx5_esw_acw_egwess_vpowt_unbond(stwuct mwx5_eswitch *esw, u16 vpowt_num);

static inwine boow mwx5_esw_acw_egwess_fwd2vpowt_suppowted(stwuct mwx5_eswitch *esw)
{
	wetuwn esw && esw->mode == MWX5_ESWITCH_OFFWOADS &&
		mwx5_eswitch_vpowt_match_metadata_enabwed(esw) &&
		MWX5_CAP_ESW_FWOWTABWE(esw->dev, egwess_acw_fowwawd_to_vpowt);
}

/* Eswitch acw ingwess extewnaw APIs */
int esw_acw_ingwess_ofwd_setup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);
void esw_acw_ingwess_ofwd_cweanup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);
int mwx5_esw_acw_ingwess_vpowt_metadata_update(stwuct mwx5_eswitch *esw, u16 vpowt_num,
					       u32 metadata);
void mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_destwoy(stwuct mwx5_eswitch *esw, u16 vpowt_num);
int mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_cweate(stwuct mwx5_eswitch *esw, u16 vpowt_num);

#ewse /* CONFIG_MWX5_ESWITCH */
static void
mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_destwoy(stwuct mwx5_eswitch *esw,
					     u16 vpowt_num)
{}

static int mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_cweate(stwuct mwx5_eswitch *esw,
						       u16 vpowt_num)
{
	wetuwn 0;
}
#endif /* CONFIG_MWX5_ESWITCH */
#endif /* __MWX5_ESWITCH_ACW_OFWD_H__ */
