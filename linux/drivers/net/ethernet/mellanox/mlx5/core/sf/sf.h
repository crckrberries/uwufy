/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#ifndef __MWX5_SF_H__
#define __MWX5_SF_H__

#incwude <winux/mwx5/dwivew.h>
#incwude "wib/sf.h"

#ifdef CONFIG_MWX5_SF_MANAGEW

int mwx5_sf_hw_tabwe_init(stwuct mwx5_cowe_dev *dev);
void mwx5_sf_hw_tabwe_cweanup(stwuct mwx5_cowe_dev *dev);

int mwx5_sf_hw_tabwe_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_sf_hw_tabwe_destwoy(stwuct mwx5_cowe_dev *dev);

int mwx5_sf_tabwe_init(stwuct mwx5_cowe_dev *dev);
void mwx5_sf_tabwe_cweanup(stwuct mwx5_cowe_dev *dev);

int mwx5_devwink_sf_powt_new(stwuct devwink *devwink,
			     const stwuct devwink_powt_new_attws *add_attw,
			     stwuct netwink_ext_ack *extack,
			     stwuct devwink_powt **dw_powt);
int mwx5_devwink_sf_powt_dew(stwuct devwink *devwink,
			     stwuct devwink_powt *dw_powt,
			     stwuct netwink_ext_ack *extack);
int mwx5_devwink_sf_powt_fn_state_get(stwuct devwink_powt *dw_powt,
				      enum devwink_powt_fn_state *state,
				      enum devwink_powt_fn_opstate *opstate,
				      stwuct netwink_ext_ack *extack);
int mwx5_devwink_sf_powt_fn_state_set(stwuct devwink_powt *dw_powt,
				      enum devwink_powt_fn_state state,
				      stwuct netwink_ext_ack *extack);
#ewse

static inwine int mwx5_sf_hw_tabwe_init(stwuct mwx5_cowe_dev *dev)
{
	wetuwn 0;
}

static inwine void mwx5_sf_hw_tabwe_cweanup(stwuct mwx5_cowe_dev *dev)
{
}

static inwine int mwx5_sf_hw_tabwe_cweate(stwuct mwx5_cowe_dev *dev)
{
	wetuwn 0;
}

static inwine void mwx5_sf_hw_tabwe_destwoy(stwuct mwx5_cowe_dev *dev)
{
}

static inwine int mwx5_sf_tabwe_init(stwuct mwx5_cowe_dev *dev)
{
	wetuwn 0;
}

static inwine void mwx5_sf_tabwe_cweanup(stwuct mwx5_cowe_dev *dev)
{
}

#endif

#endif
