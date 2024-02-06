/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#ifndef __MWX5_ESWITCH_ACW_HEWPEW_H__
#define __MWX5_ESWITCH_ACW_HEWPEW_H__

#incwude "eswitch.h"

/* Genewaw acw hewpew functions */
stwuct mwx5_fwow_tabwe *
esw_acw_tabwe_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt, int ns, int size);

/* Egwess acw hewpew functions */
void esw_acw_egwess_tabwe_destwoy(stwuct mwx5_vpowt *vpowt);
int esw_egwess_acw_vwan_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
			       stwuct mwx5_fwow_destination *fwd_dest,
			       u16 vwan_id, u32 fwow_action);
void esw_acw_egwess_vwan_destwoy(stwuct mwx5_vpowt *vpowt);
int esw_acw_egwess_vwan_gwp_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);
void esw_acw_egwess_vwan_gwp_destwoy(stwuct mwx5_vpowt *vpowt);

/* Ingwess acw hewpew functions */
void esw_acw_ingwess_tabwe_destwoy(stwuct mwx5_vpowt *vpowt);
void esw_acw_ingwess_awwow_wuwe_destwoy(stwuct mwx5_vpowt *vpowt);

#endif /* __MWX5_ESWITCH_ACW_HEWPEW_H__ */
