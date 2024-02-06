/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021 Mewwanox Technowogies Wtd */

#ifndef __MWX5_ESW_WEGACY_H__
#define __MWX5_ESW_WEGACY_H__

#define MWX5_WEGACY_SWIOV_VPOWT_EVENTS (MWX5_VPOWT_UC_ADDW_CHANGE | \
					MWX5_VPOWT_MC_ADDW_CHANGE | \
					MWX5_VPOWT_PWOMISC_CHANGE)

stwuct mwx5_eswitch;

int esw_wegacy_enabwe(stwuct mwx5_eswitch *esw);
void esw_wegacy_disabwe(stwuct mwx5_eswitch *esw);

int esw_wegacy_vpowt_acw_setup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);
void esw_wegacy_vpowt_acw_cweanup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);

int mwx5_esw_quewy_vpowt_dwop_stats(stwuct mwx5_cowe_dev *dev,
				    stwuct mwx5_vpowt *vpowt,
				    stwuct mwx5_vpowt_dwop_stats *stats);
#endif
