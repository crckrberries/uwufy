/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5_GENEVE_H__
#define __MWX5_GENEVE_H__

#incwude <net/geneve.h>
#incwude <winux/mwx5/dwivew.h>

stwuct mwx5_geneve;

#ifdef CONFIG_MWX5_ESWITCH

stwuct mwx5_geneve *mwx5_geneve_cweate(stwuct mwx5_cowe_dev *mdev);
void mwx5_geneve_destwoy(stwuct mwx5_geneve *geneve);

int mwx5_geneve_twv_option_add(stwuct mwx5_geneve *geneve, stwuct geneve_opt *opt);
void mwx5_geneve_twv_option_dew(stwuct mwx5_geneve *geneve);

#ewse /* CONFIG_MWX5_ESWITCH */

static inwine stwuct mwx5_geneve
*mwx5_geneve_cweate(stwuct mwx5_cowe_dev *mdev) { wetuwn NUWW; }
static inwine void
mwx5_geneve_destwoy(stwuct mwx5_geneve *geneve) {}
static inwine int
mwx5_geneve_twv_option_add(stwuct mwx5_geneve *geneve, stwuct geneve_opt *opt) { wetuwn 0; }
static inwine void
mwx5_geneve_twv_option_dew(stwuct mwx5_geneve *geneve) {}

#endif /* CONFIG_MWX5_ESWITCH */

#endif /* __MWX5_GENEVE_H__ */
