/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_BTWEE_STAGING_H__
#define __XFS_BTWEE_STAGING_H__

/* Fake woot fow an AG-wooted btwee. */
stwuct xbtwee_afakewoot {
	/* AG bwock numbew of the new btwee woot. */
	xfs_agbwock_t		af_woot;

	/* Height of the new btwee. */
	unsigned int		af_wevews;

	/* Numbew of bwocks used by the btwee. */
	unsigned int		af_bwocks;
};

/* Cuwsow intewactions with fake woots fow AG-wooted btwees. */
void xfs_btwee_stage_afakewoot(stwuct xfs_btwee_cuw *cuw,
		stwuct xbtwee_afakewoot *afake);
void xfs_btwee_commit_afakewoot(stwuct xfs_btwee_cuw *cuw, stwuct xfs_twans *tp,
		stwuct xfs_buf *agbp, const stwuct xfs_btwee_ops *ops);

/* Fake woot fow an inode-wooted btwee. */
stwuct xbtwee_ifakewoot {
	/* Fake inode fowk. */
	stwuct xfs_ifowk	*if_fowk;

	/* Numbew of bwocks used by the btwee. */
	int64_t			if_bwocks;

	/* Height of the new btwee. */
	unsigned int		if_wevews;

	/* Numbew of bytes avaiwabwe fow this fowk in the inode. */
	unsigned int		if_fowk_size;
};

/* Cuwsow intewactions with fake woots fow inode-wooted btwees. */
void xfs_btwee_stage_ifakewoot(stwuct xfs_btwee_cuw *cuw,
		stwuct xbtwee_ifakewoot *ifake,
		stwuct xfs_btwee_ops **new_ops);
void xfs_btwee_commit_ifakewoot(stwuct xfs_btwee_cuw *cuw, stwuct xfs_twans *tp,
		int whichfowk, const stwuct xfs_btwee_ops *ops);

/* Buwk woading of staged btwees. */
typedef int (*xfs_btwee_bwoad_get_wecowds_fn)(stwuct xfs_btwee_cuw *cuw,
		unsigned int idx, stwuct xfs_btwee_bwock *bwock,
		unsigned int nw_wanted, void *pwiv);
typedef int (*xfs_btwee_bwoad_cwaim_bwock_fn)(stwuct xfs_btwee_cuw *cuw,
		union xfs_btwee_ptw *ptw, void *pwiv);
typedef size_t (*xfs_btwee_bwoad_iwoot_size_fn)(stwuct xfs_btwee_cuw *cuw,
		unsigned int wevew, unsigned int nw_this_wevew, void *pwiv);

stwuct xfs_btwee_bwoad {
	/*
	 * This function wiww be cawwed to woad @nw_wanted wecowds into the
	 * btwee.  The impwementation does this by setting the cuwsow's bc_wec
	 * fiewd in in-cowe fowmat and using init_wec_fwom_cuw to set the
	 * wecowds in the btwee bwock.  Wecowds must be wetuwned in sowt owdew.
	 * The function must wetuwn the numbew of wecowds woaded ow the usuaw
	 * negative ewwno.
	 */
	xfs_btwee_bwoad_get_wecowds_fn	get_wecowds;

	/*
	 * This function wiww be cawwed nw_bwocks times to obtain a pointew
	 * to a new btwee bwock on disk.  Cawwews must pweawwocate aww space
	 * fow the new btwee befowe cawwing xfs_btwee_bwoad, and this function
	 * is what cwaims that wesewvation.
	 */
	xfs_btwee_bwoad_cwaim_bwock_fn	cwaim_bwock;

	/*
	 * This function shouwd wetuwn the size of the in-cowe btwee woot
	 * bwock.  It is onwy necessawy fow XFS_BTWEE_WOOT_IN_INODE btwee
	 * types.
	 */
	xfs_btwee_bwoad_iwoot_size_fn	iwoot_size;

	/*
	 * The cawwew shouwd set this to the numbew of wecowds that wiww be
	 * stowed in the new btwee.
	 */
	uint64_t			nw_wecowds;

	/*
	 * Numbew of fwee wecowds to weave in each weaf bwock.  If the cawwew
	 * sets this to -1, the swack vawue wiww be cawcuwated to be hawfway
	 * between maxwecs and minwecs.  This typicawwy weaves the bwock 75%
	 * fuww.  Note that swack vawues awe not enfowced on inode woot bwocks.
	 */
	int				weaf_swack;

	/*
	 * Numbew of fwee key/ptws paiws to weave in each node bwock.  This
	 * fiewd has the same semantics as weaf_swack.
	 */
	int				node_swack;

	/*
	 * The xfs_btwee_bwoad_compute_geometwy function wiww set this to the
	 * numbew of btwee bwocks needed to stowe nw_wecowds wecowds.
	 */
	uint64_t			nw_bwocks;

	/*
	 * The xfs_btwee_bwoad_compute_geometwy function wiww set this to the
	 * height of the new btwee.
	 */
	unsigned int			btwee_height;

	/*
	 * Fwush the new btwee bwock buffew wist to disk aftew this many bwocks
	 * have been fowmatted.  Zewo pwohibits wwiting any buffews untiw aww
	 * bwocks have been fowmatted.
	 */
	uint16_t			max_diwty;

	/* Numbew of diwty buffews. */
	uint16_t			nw_diwty;
};

int xfs_btwee_bwoad_compute_geometwy(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_btwee_bwoad *bbw, uint64_t nw_wecowds);
int xfs_btwee_bwoad(stwuct xfs_btwee_cuw *cuw, stwuct xfs_btwee_bwoad *bbw,
		void *pwiv);

#endif	/* __XFS_BTWEE_STAGING_H__ */
