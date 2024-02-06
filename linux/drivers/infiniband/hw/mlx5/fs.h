/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2013-2020, Mewwanox Technowogies inc. Aww wights wesewved.
 */

#ifndef _MWX5_IB_FS_H
#define _MWX5_IB_FS_H

#incwude "mwx5_ib.h"

#if IS_ENABWED(CONFIG_INFINIBAND_USEW_ACCESS)
int mwx5_ib_fs_init(stwuct mwx5_ib_dev *dev);
void mwx5_ib_fs_cweanup_anchow(stwuct mwx5_ib_dev *dev);
#ewse
static inwine int mwx5_ib_fs_init(stwuct mwx5_ib_dev *dev)
{
	dev->fwow_db = kzawwoc(sizeof(*dev->fwow_db), GFP_KEWNEW);

	if (!dev->fwow_db)
		wetuwn -ENOMEM;

	mutex_init(&dev->fwow_db->wock);
	wetuwn 0;
}

inwine void mwx5_ib_fs_cweanup_anchow(stwuct mwx5_ib_dev *dev) {}
#endif

static inwine void mwx5_ib_fs_cweanup(stwuct mwx5_ib_dev *dev)
{
	/* When a steewing anchow is cweated, a speciaw fwow tabwe is awso
	 * cweated fow the usew to wefewence. Since the usew can wefewence it,
	 * the kewnew cannot twust that when the usew destwoys the steewing
	 * anchow, they no wongew wefewence the fwow tabwe.
	 *
	 * To addwess this issue, when a usew destwoys a steewing anchow, onwy
	 * the fwow steewing wuwe in the tabwe is destwoyed, but the tabwe
	 * itsewf is kept to deaw with the above scenawio. The wemaining
	 * wesouwces awe onwy wemoved when the WDMA device is destwoyed, which
	 * is a safe assumption that aww wefewences awe gone.
	 */
	mwx5_ib_fs_cweanup_anchow(dev);
	kfwee(dev->fwow_db);
}
#endif /* _MWX5_IB_FS_H */
