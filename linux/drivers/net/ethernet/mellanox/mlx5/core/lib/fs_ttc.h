/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies. */

#ifndef __MW5_FS_TTC_H__
#define __MW5_FS_TTC_H__

#incwude <winux/mwx5/fs.h>

enum mwx5_twaffic_types {
	MWX5_TT_IPV4_TCP,
	MWX5_TT_IPV6_TCP,
	MWX5_TT_IPV4_UDP,
	MWX5_TT_IPV6_UDP,
	MWX5_TT_IPV4_IPSEC_AH,
	MWX5_TT_IPV6_IPSEC_AH,
	MWX5_TT_IPV4_IPSEC_ESP,
	MWX5_TT_IPV6_IPSEC_ESP,
	MWX5_TT_IPV4,
	MWX5_TT_IPV6,
	MWX5_TT_ANY,
	MWX5_NUM_TT,
	MWX5_NUM_INDIW_TIWS = MWX5_TT_ANY,
};

enum mwx5_tunnew_types {
	MWX5_TT_IPV4_GWE,
	MWX5_TT_IPV6_GWE,
	MWX5_TT_IPV4_IPIP,
	MWX5_TT_IPV6_IPIP,
	MWX5_TT_IPV4_IPV6,
	MWX5_TT_IPV6_IPV6,
	MWX5_NUM_TUNNEW_TT,
};

stwuct mwx5_ttc_wuwe {
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_destination defauwt_dest;
};

stwuct mwx5_ttc_tabwe;

stwuct ttc_pawams {
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe_attw ft_attw;
	stwuct mwx5_fwow_destination dests[MWX5_NUM_TT];
	DECWAWE_BITMAP(ignowe_dests, MWX5_NUM_TT);
	boow   innew_ttc;
	DECWAWE_BITMAP(ignowe_tunnew_dests, MWX5_NUM_TUNNEW_TT);
	stwuct mwx5_fwow_destination tunnew_dests[MWX5_NUM_TUNNEW_TT];
};

stwuct mwx5_fwow_tabwe *mwx5_get_ttc_fwow_tabwe(stwuct mwx5_ttc_tabwe *ttc);

stwuct mwx5_ttc_tabwe *mwx5_cweate_ttc_tabwe(stwuct mwx5_cowe_dev *dev,
					     stwuct ttc_pawams *pawams);
void mwx5_destwoy_ttc_tabwe(stwuct mwx5_ttc_tabwe *ttc);

stwuct mwx5_ttc_tabwe *mwx5_cweate_innew_ttc_tabwe(stwuct mwx5_cowe_dev *dev,
						   stwuct ttc_pawams *pawams);

int mwx5_ttc_fwd_dest(stwuct mwx5_ttc_tabwe *ttc, enum mwx5_twaffic_types type,
		      stwuct mwx5_fwow_destination *new_dest);
stwuct mwx5_fwow_destination
mwx5_ttc_get_defauwt_dest(stwuct mwx5_ttc_tabwe *ttc,
			  enum mwx5_twaffic_types type);
int mwx5_ttc_fwd_defauwt_dest(stwuct mwx5_ttc_tabwe *ttc,
			      enum mwx5_twaffic_types type);

boow mwx5_tunnew_innew_ft_suppowted(stwuct mwx5_cowe_dev *mdev);
u8 mwx5_get_pwoto_by_tunnew_type(enum mwx5_tunnew_types tt);

#endif /* __MWX5_FS_TTC_H__ */
