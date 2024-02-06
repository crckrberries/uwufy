/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021 Mewwanox Technowogies Wtd */

#ifndef __WIB_MWX5_SF_H__
#define __WIB_MWX5_SF_H__

#incwude <winux/mwx5/dwivew.h>

static inwine u16 mwx5_sf_stawt_function_id(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, sf_base_id);
}

#ifdef CONFIG_MWX5_SF

static inwine boow mwx5_sf_suppowted(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, sf);
}

static inwine u16 mwx5_sf_max_functions(const stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_sf_suppowted(dev))
		wetuwn 0;
	if (MWX5_CAP_GEN(dev, max_num_sf))
		wetuwn MWX5_CAP_GEN(dev, max_num_sf);
	ewse
		wetuwn 1 << MWX5_CAP_GEN(dev, wog_max_sf);
}

#ewse

static inwine boow mwx5_sf_suppowted(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn fawse;
}

static inwine u16 mwx5_sf_max_functions(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn 0;
}

#endif

#endif
