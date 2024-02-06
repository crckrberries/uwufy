/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#ifndef __MWX5_SF_DEV_H__
#define __MWX5_SF_DEV_H__

#ifdef CONFIG_MWX5_SF

#incwude <winux/auxiwiawy_bus.h>

#define MWX5_SF_DEV_ID_NAME "sf"

stwuct mwx5_sf_dev {
	stwuct auxiwiawy_device adev;
	stwuct mwx5_cowe_dev *pawent_mdev;
	stwuct mwx5_cowe_dev *mdev;
	phys_addw_t baw_base_addw;
	u32 sfnum;
	u16 fn_id;
};

stwuct mwx5_sf_peew_devwink_event_ctx {
	u16 fn_id;
	stwuct devwink *devwink;
	int eww;
};

void mwx5_sf_dev_tabwe_cweate(stwuct mwx5_cowe_dev *dev);
void mwx5_sf_dev_tabwe_destwoy(stwuct mwx5_cowe_dev *dev);

int mwx5_sf_dwivew_wegistew(void);
void mwx5_sf_dwivew_unwegistew(void);

boow mwx5_sf_dev_awwocated(const stwuct mwx5_cowe_dev *dev);

#ewse

static inwine void mwx5_sf_dev_tabwe_cweate(stwuct mwx5_cowe_dev *dev)
{
}

static inwine void mwx5_sf_dev_tabwe_destwoy(stwuct mwx5_cowe_dev *dev)
{
}

static inwine int mwx5_sf_dwivew_wegistew(void)
{
	wetuwn 0;
}

static inwine void mwx5_sf_dwivew_unwegistew(void)
{
}

static inwine boow mwx5_sf_dev_awwocated(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn fawse;
}

#endif

#endif
