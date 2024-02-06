/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_EN_POST_METEW_H__
#define __MWX5_EN_POST_METEW_H__

#define packet_cowow_to_weg { \
	.mfiewd = MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_5, \
	.moffset = 0, \
	.mwen = 8, \
	.soffset = MWX5_BYTE_OFF(fte_match_pawam, \
				 misc_pawametews_2.metadata_weg_c_5), \
}

stwuct mwx5e_post_metew_pwiv;

enum mwx5e_post_metew_type {
	MWX5E_POST_METEW_WATE = 0,
	MWX5E_POST_METEW_MTU
};

#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)

stwuct mwx5_fwow_tabwe *
mwx5e_post_metew_get_ft(stwuct mwx5e_post_metew_pwiv *post_metew);

stwuct mwx5_fwow_tabwe *
mwx5e_post_metew_get_mtu_twue_ft(stwuct mwx5e_post_metew_pwiv *post_metew);

stwuct mwx5_fwow_tabwe *
mwx5e_post_metew_get_mtu_fawse_ft(stwuct mwx5e_post_metew_pwiv *post_metew);

stwuct mwx5e_post_metew_pwiv *
mwx5e_post_metew_init(stwuct mwx5e_pwiv *pwiv,
		      enum mwx5_fwow_namespace_type ns_type,
		      stwuct mwx5e_post_act *post_act,
		      enum mwx5e_post_metew_type type,
		      stwuct mwx5_fc *act_countew,
		      stwuct mwx5_fc *dwop_countew,
		      stwuct mwx5_fwow_attw *bwanch_twue,
		      stwuct mwx5_fwow_attw *bwanch_fawse);

void
mwx5e_post_metew_cweanup(stwuct mwx5_eswitch *esw, stwuct mwx5e_post_metew_pwiv *post_metew);

#ewse /* CONFIG_MWX5_CWS_ACT */

static inwine stwuct mwx5_fwow_tabwe *
mwx5e_post_metew_get_mtu_twue_ft(stwuct mwx5e_post_metew_pwiv *post_metew)
{
	wetuwn NUWW;
}

static inwine stwuct mwx5_fwow_tabwe *
mwx5e_post_metew_get_mtu_fawse_ft(stwuct mwx5e_post_metew_pwiv *post_metew)
{
	wetuwn NUWW;
}

#endif

#endif /* __MWX5_EN_POST_METEW_H__ */
