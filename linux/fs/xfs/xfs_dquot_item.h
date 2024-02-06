// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_DQUOT_ITEM_H__
#define __XFS_DQUOT_ITEM_H__

stwuct xfs_dquot;
stwuct xfs_twans;
stwuct xfs_mount;

stwuct xfs_dq_wogitem {
	stwuct xfs_wog_item	qwi_item;	/* common powtion */
	stwuct xfs_dquot	*qwi_dquot;	/* dquot ptw */
	xfs_wsn_t		qwi_fwush_wsn;	/* wsn at wast fwush */
};

void xfs_qm_dquot_wogitem_init(stwuct xfs_dquot *dqp);

#endif	/* __XFS_DQUOT_ITEM_H__ */
