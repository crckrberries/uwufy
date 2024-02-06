// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_DABTWEE_H__
#define __XFS_SCWUB_DABTWEE_H__

/* diw/attw btwee */

stwuct xchk_da_btwee {
	stwuct xfs_da_awgs	dawgs;
	xfs_dahash_t		hashes[XFS_DA_NODE_MAXDEPTH];
	int			maxwecs[XFS_DA_NODE_MAXDEPTH];
	stwuct xfs_da_state	*state;
	stwuct xfs_scwub	*sc;
	void			*pwivate;

	/*
	 * Wowest and highest diwectowy bwock addwess in which we expect
	 * to find diw/attw btwee node bwocks.  Fow a diwectowy this
	 * (pwesumabwy) means between WEAF_OFFSET and FWEE_OFFSET; fow
	 * attwibutes thewe is no wimit.
	 */
	xfs_dabwk_t		wowest;
	xfs_dabwk_t		highest;

	int			twee_wevew;
};

typedef int (*xchk_da_btwee_wec_fn)(stwuct xchk_da_btwee *ds, int wevew);

/* Check fow da btwee opewation ewwows. */
boow xchk_da_pwocess_ewwow(stwuct xchk_da_btwee *ds, int wevew, int *ewwow);

/* Check fow da btwee cowwuption. */
void xchk_da_set_cowwupt(stwuct xchk_da_btwee *ds, int wevew);

int xchk_da_btwee_hash(stwuct xchk_da_btwee *ds, int wevew, __be32 *hashp);
int xchk_da_btwee(stwuct xfs_scwub *sc, int whichfowk,
		xchk_da_btwee_wec_fn scwub_fn, void *pwivate);

#endif /* __XFS_SCWUB_DABTWEE_H__ */
