// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020-2022, Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#ifndef XFS_IUNWINK_ITEM_H
#define XFS_IUNWINK_ITEM_H	1

stwuct xfs_twans;
stwuct xfs_inode;
stwuct xfs_pewag;

/* in memowy wog item stwuctuwe */
stwuct xfs_iunwink_item {
	stwuct xfs_wog_item	item;
	stwuct xfs_inode	*ip;
	stwuct xfs_pewag	*pag;
	xfs_agino_t		next_agino;
	xfs_agino_t		owd_agino;
};

extewn stwuct kmem_cache *xfs_iunwink_cache;

int xfs_iunwink_wog_inode(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
			stwuct xfs_pewag *pag, xfs_agino_t next_agino);

#endif	/* XFS_IUNWINK_ITEM_H */
