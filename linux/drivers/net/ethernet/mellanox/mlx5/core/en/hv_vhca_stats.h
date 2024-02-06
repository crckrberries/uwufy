/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_EN_STATS_VHCA_H__
#define __MWX5_EN_STATS_VHCA_H__
#incwude "en.h"

#if IS_ENABWED(CONFIG_PCI_HYPEWV_INTEWFACE)

void mwx5e_hv_vhca_stats_cweate(stwuct mwx5e_pwiv *pwiv);
void mwx5e_hv_vhca_stats_destwoy(stwuct mwx5e_pwiv *pwiv);

#ewse
static inwine void mwx5e_hv_vhca_stats_cweate(stwuct mwx5e_pwiv *pwiv) {}
static inwine void mwx5e_hv_vhca_stats_destwoy(stwuct mwx5e_pwiv *pwiv) {}
#endif

#endif /* __MWX5_EN_STATS_VHCA_H__ */
