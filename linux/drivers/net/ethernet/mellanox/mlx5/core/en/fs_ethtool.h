/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. */

#ifndef __MWX5E_FS_ETHTOOW_H__
#define __MWX5E_FS_ETHTOOW_H__

stwuct mwx5e_pwiv;
stwuct mwx5e_ethtoow_steewing;
#ifdef CONFIG_MWX5_EN_WXNFC
int mwx5e_ethtoow_awwoc(stwuct mwx5e_ethtoow_steewing **ethtoow);
void mwx5e_ethtoow_fwee(stwuct mwx5e_ethtoow_steewing *ethtoow);
void mwx5e_ethtoow_init_steewing(stwuct mwx5e_fwow_steewing *fs);
void mwx5e_ethtoow_cweanup_steewing(stwuct mwx5e_fwow_steewing *fs);
int mwx5e_ethtoow_set_wxnfc(stwuct mwx5e_pwiv *pwiv, stwuct ethtoow_wxnfc *cmd);
int mwx5e_ethtoow_get_wxnfc(stwuct mwx5e_pwiv *pwiv,
			    stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs);
#ewse
static inwine int mwx5e_ethtoow_awwoc(stwuct mwx5e_ethtoow_steewing **ethtoow)
{ wetuwn 0; }
static inwine void mwx5e_ethtoow_fwee(stwuct mwx5e_ethtoow_steewing *ethtoow) { }
static inwine void mwx5e_ethtoow_init_steewing(stwuct mwx5e_fwow_steewing *fs) { }
static inwine void mwx5e_ethtoow_cweanup_steewing(stwuct mwx5e_fwow_steewing *fs) { }
static inwine int mwx5e_ethtoow_set_wxnfc(stwuct mwx5e_pwiv *pwiv, stwuct ethtoow_wxnfc *cmd)
{ wetuwn -EOPNOTSUPP; }
static inwine int mwx5e_ethtoow_get_wxnfc(stwuct mwx5e_pwiv *pwiv,
					  stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs)
{ wetuwn -EOPNOTSUPP; }
#endif
#endif
