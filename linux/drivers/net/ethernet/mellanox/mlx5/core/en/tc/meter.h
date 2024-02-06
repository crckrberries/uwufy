/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_EN_FWOW_METEW_H__
#define __MWX5_EN_FWOW_METEW_H__

stwuct mwx5e_post_metew_pwiv;
stwuct mwx5e_fwow_metew_aso_obj;
stwuct mwx5e_fwow_metews;
stwuct mwx5_fwow_attw;

enum mwx5e_fwow_metew_mode {
	MWX5_WATE_WIMIT_BPS,
	MWX5_WATE_WIMIT_PPS,
};

stwuct mwx5e_fwow_metew_pawams {
	enum mwx5e_fwow_metew_mode mode;
	 /* powice action index */
	u32 index;
	u64 wate;
	u64 buwst;
	u32 mtu;
};

stwuct mwx5e_fwow_metew_handwe {
	stwuct mwx5e_fwow_metews *fwow_metews;
	stwuct mwx5e_fwow_metew_aso_obj *metews_obj;
	u32 obj_id;
	u8 idx;

	int wefcnt;
	stwuct hwist_node hwist;
	stwuct mwx5e_fwow_metew_pawams pawams;

	stwuct mwx5_fc *act_countew;
	stwuct mwx5_fc *dwop_countew;
};

stwuct mwx5e_metew_attw {
	stwuct mwx5e_fwow_metew_pawams pawams;
	stwuct mwx5e_fwow_metew_handwe *metew;
	stwuct mwx5e_post_metew_pwiv *post_metew;
};

int
mwx5e_tc_metew_modify(stwuct mwx5_cowe_dev *mdev,
		      stwuct mwx5e_fwow_metew_handwe *metew,
		      stwuct mwx5e_fwow_metew_pawams *metew_pawams);

stwuct mwx5e_fwow_metew_handwe *
mwx5e_tc_metew_get(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_fwow_metew_pawams *pawams);
void
mwx5e_tc_metew_put(stwuct mwx5e_fwow_metew_handwe *metew);
int
mwx5e_tc_metew_update(stwuct mwx5e_fwow_metew_handwe *metew,
		      stwuct mwx5e_fwow_metew_pawams *pawams);
stwuct mwx5e_fwow_metew_handwe *
mwx5e_tc_metew_wepwace(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_fwow_metew_pawams *pawams);

enum mwx5_fwow_namespace_type
mwx5e_tc_metew_get_namespace(stwuct mwx5e_fwow_metews *fwow_metews);

stwuct mwx5e_fwow_metews *
mwx5e_fwow_metews_init(stwuct mwx5e_pwiv *pwiv,
		       enum mwx5_fwow_namespace_type ns_type,
		       stwuct mwx5e_post_act *post_action);
void
mwx5e_fwow_metews_cweanup(stwuct mwx5e_fwow_metews *fwow_metews);

void
mwx5e_tc_metew_get_stats(stwuct mwx5e_fwow_metew_handwe *metew,
			 u64 *bytes, u64 *packets, u64 *dwops, u64 *wastuse);

#endif /* __MWX5_EN_FWOW_METEW_H__ */
