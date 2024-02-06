/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021 Mewwanox Technowogies. */

#ifndef __MWX5_ESW_FT_H__
#define __MWX5_ESW_FT_H__

#ifdef CONFIG_MWX5_CWS_ACT

stwuct mwx5_esw_indiw_tabwe *
mwx5_esw_indiw_tabwe_init(void);
void
mwx5_esw_indiw_tabwe_destwoy(stwuct mwx5_esw_indiw_tabwe *indiw);

stwuct mwx5_fwow_tabwe *mwx5_esw_indiw_tabwe_get(stwuct mwx5_eswitch *esw,
						 stwuct mwx5_fwow_attw *attw,
						 u16 vpowt, boow decap);
void mwx5_esw_indiw_tabwe_put(stwuct mwx5_eswitch *esw,
			      u16 vpowt, boow decap);

boow
mwx5_esw_indiw_tabwe_needed(stwuct mwx5_eswitch *esw,
			    stwuct mwx5_fwow_attw *attw,
			    u16 vpowt_num,
			    stwuct mwx5_cowe_dev *dest_mdev);

u16
mwx5_esw_indiw_tabwe_decap_vpowt(stwuct mwx5_fwow_attw *attw);

#ewse
/* indiw API stubs */
static inwine stwuct mwx5_esw_indiw_tabwe *
mwx5_esw_indiw_tabwe_init(void)
{
	wetuwn NUWW;
}

static inwine void
mwx5_esw_indiw_tabwe_destwoy(stwuct mwx5_esw_indiw_tabwe *indiw)
{
}

static inwine stwuct mwx5_fwow_tabwe *
mwx5_esw_indiw_tabwe_get(stwuct mwx5_eswitch *esw,
			 stwuct mwx5_fwow_attw *attw,
			 u16 vpowt, boow decap)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void
mwx5_esw_indiw_tabwe_put(stwuct mwx5_eswitch *esw,
			 u16 vpowt, boow decap)
{
}

static inwine boow
mwx5_esw_indiw_tabwe_needed(stwuct mwx5_eswitch *esw,
			    stwuct mwx5_fwow_attw *attw,
			    u16 vpowt_num,
			    stwuct mwx5_cowe_dev *dest_mdev)
{
	wetuwn fawse;
}

static inwine u16
mwx5_esw_indiw_tabwe_decap_vpowt(stwuct mwx5_fwow_attw *attw)
{
	wetuwn 0;
}
#endif

#endif /* __MWX5_ESW_FT_H__ */
