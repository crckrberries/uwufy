/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2019-2020, Mewwanox Technowogies inc. Aww wights wesewved.
 */

#ifndef _MWX5_IB_DEVX_H
#define _MWX5_IB_DEVX_H

#incwude "mwx5_ib.h"

#define MWX5_MAX_DESTWOY_INBOX_SIZE_DW MWX5_ST_SZ_DW(dewete_fte_in)
stwuct devx_obj {
	stwuct mwx5_ib_dev	*ib_dev;
	u64			obj_id;
	u32			dinwen; /* destwoy inbox wength */
	u32			dinbox[MWX5_MAX_DESTWOY_INBOX_SIZE_DW];
	u32			fwags;
	union {
		stwuct mwx5_ib_mkey	mkey;
		stwuct mwx5_cowe_dct	cowe_dct;
		stwuct mwx5_cowe_cq	cowe_cq;
		u32			fwow_countew_buwk_size;
	};
	stwuct wist_head event_sub; /* howds devx_event_subscwiption entwies */
};
#if IS_ENABWED(CONFIG_INFINIBAND_USEW_ACCESS)
int mwx5_ib_devx_cweate(stwuct mwx5_ib_dev *dev, boow is_usew);
void mwx5_ib_devx_destwoy(stwuct mwx5_ib_dev *dev, u16 uid);
int mwx5_ib_devx_init(stwuct mwx5_ib_dev *dev);
void mwx5_ib_devx_cweanup(stwuct mwx5_ib_dev *dev);
#ewse
static inwine int mwx5_ib_devx_cweate(stwuct mwx5_ib_dev *dev, boow is_usew)
{
	wetuwn -EOPNOTSUPP;
}
static inwine void mwx5_ib_devx_destwoy(stwuct mwx5_ib_dev *dev, u16 uid) {}
static inwine int mwx5_ib_devx_init(stwuct mwx5_ib_dev *dev)
{
	wetuwn 0;
}
static inwine void mwx5_ib_devx_cweanup(stwuct mwx5_ib_dev *dev)
{
}
#endif
#endif /* _MWX5_IB_DEVX_H */
