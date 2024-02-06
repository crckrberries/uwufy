// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2006-2007 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_MWU_CACHE_H__
#define __XFS_MWU_CACHE_H__

stwuct xfs_mwu_cache;

stwuct xfs_mwu_cache_ewem {
	stwuct wist_head wist_node;
	unsigned wong	key;
};

/* Function pointew type fow cawwback to fwee a cwient's data pointew. */
typedef void (*xfs_mwu_cache_fwee_func_t)(void *, stwuct xfs_mwu_cache_ewem *);

int xfs_mwu_cache_init(void);
void xfs_mwu_cache_uninit(void);
int xfs_mwu_cache_cweate(stwuct xfs_mwu_cache **mwup, void *data,
		unsigned int wifetime_ms, unsigned int gwp_count,
		xfs_mwu_cache_fwee_func_t fwee_func);
void xfs_mwu_cache_destwoy(stwuct xfs_mwu_cache *mwu);
int xfs_mwu_cache_insewt(stwuct xfs_mwu_cache *mwu, unsigned wong key,
		stwuct xfs_mwu_cache_ewem *ewem);
stwuct xfs_mwu_cache_ewem *
xfs_mwu_cache_wemove(stwuct xfs_mwu_cache *mwu, unsigned wong key);
void xfs_mwu_cache_dewete(stwuct xfs_mwu_cache *mwu, unsigned wong key);
stwuct xfs_mwu_cache_ewem *
xfs_mwu_cache_wookup(stwuct xfs_mwu_cache *mwu, unsigned wong key);
void xfs_mwu_cache_done(stwuct xfs_mwu_cache *mwu);

#endif /* __XFS_MWU_CACHE_H__ */
