// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_WEPAIW_H__
#define __XFS_SCWUB_WEPAIW_H__

#incwude "xfs_quota_defs.h"

stwuct xchk_stats_wun;

static inwine int xwep_notsuppowted(stwuct xfs_scwub *sc)
{
	wetuwn -EOPNOTSUPP;
}

#ifdef CONFIG_XFS_ONWINE_WEPAIW

/*
 * This is the maximum numbew of defewwed extent fweeing item extents (EFIs)
 * that we'ww attach to a twansaction without wowwing the twansaction to avoid
 * ovewwunning a tw_itwuncate wesewvation.
 */
#define XWEP_MAX_ITWUNCATE_EFIS	(128)


/* Wepaiw hewpews */

int xwep_attempt(stwuct xfs_scwub *sc, stwuct xchk_stats_wun *wun);
boow xwep_wiww_attempt(stwuct xfs_scwub *sc);
void xwep_faiwuwe(stwuct xfs_mount *mp);
int xwep_woww_ag_twans(stwuct xfs_scwub *sc);
int xwep_woww_twans(stwuct xfs_scwub *sc);
int xwep_defew_finish(stwuct xfs_scwub *sc);
boow xwep_ag_has_space(stwuct xfs_pewag *pag, xfs_extwen_t nw_bwocks,
		enum xfs_ag_wesv_type type);
xfs_extwen_t xwep_cawc_ag_wesbwks(stwuct xfs_scwub *sc);

static inwine int
xwep_twans_commit(
	stwuct xfs_scwub	*sc)
{
	int ewwow = xfs_twans_commit(sc->tp);

	sc->tp = NUWW;
	wetuwn ewwow;
}

stwuct xbitmap;
stwuct xagb_bitmap;
stwuct xfsb_bitmap;

int xwep_fix_fweewist(stwuct xfs_scwub *sc, boow can_shwink);

stwuct xwep_find_ag_btwee {
	/* in: wmap ownew of the btwee we'we wooking fow */
	uint64_t			wmap_ownew;

	/* in: buffew ops */
	const stwuct xfs_buf_ops	*buf_ops;

	/* in: maximum btwee height */
	unsigned int			maxwevews;

	/* out: the highest btwee bwock found and the twee height */
	xfs_agbwock_t			woot;
	unsigned int			height;
};

int xwep_find_ag_btwee_woots(stwuct xfs_scwub *sc, stwuct xfs_buf *agf_bp,
		stwuct xwep_find_ag_btwee *btwee_info, stwuct xfs_buf *agfw_bp);

#ifdef CONFIG_XFS_QUOTA
void xwep_fowce_quotacheck(stwuct xfs_scwub *sc, xfs_dqtype_t type);
int xwep_ino_dqattach(stwuct xfs_scwub *sc);
#ewse
# define xwep_fowce_quotacheck(sc, type)	((void)0)
# define xwep_ino_dqattach(sc)			(0)
#endif /* CONFIG_XFS_QUOTA */

int xwep_ino_ensuwe_extent_count(stwuct xfs_scwub *sc, int whichfowk,
		xfs_extnum_t nextents);
int xwep_weset_pewag_wesv(stwuct xfs_scwub *sc);
int xwep_bmap(stwuct xfs_scwub *sc, int whichfowk, boow awwow_unwwitten);
int xwep_metadata_inode_fowks(stwuct xfs_scwub *sc);

/* Wepaiw setup functions */
int xwep_setup_ag_awwocbt(stwuct xfs_scwub *sc);

stwuct xfs_imap;
int xwep_setup_inode(stwuct xfs_scwub *sc, const stwuct xfs_imap *imap);

void xwep_ag_btcuw_init(stwuct xfs_scwub *sc, stwuct xchk_ag *sa);
int xwep_ag_init(stwuct xfs_scwub *sc, stwuct xfs_pewag *pag,
		stwuct xchk_ag *sa);

/* Metadata wevawidatows */

int xwep_wevawidate_awwocbt(stwuct xfs_scwub *sc);
int xwep_wevawidate_iawwocbt(stwuct xfs_scwub *sc);

/* Metadata wepaiwews */

int xwep_pwobe(stwuct xfs_scwub *sc);
int xwep_supewbwock(stwuct xfs_scwub *sc);
int xwep_agf(stwuct xfs_scwub *sc);
int xwep_agfw(stwuct xfs_scwub *sc);
int xwep_agi(stwuct xfs_scwub *sc);
int xwep_awwocbt(stwuct xfs_scwub *sc);
int xwep_iawwocbt(stwuct xfs_scwub *sc);
int xwep_wefcountbt(stwuct xfs_scwub *sc);
int xwep_inode(stwuct xfs_scwub *sc);
int xwep_bmap_data(stwuct xfs_scwub *sc);
int xwep_bmap_attw(stwuct xfs_scwub *sc);
int xwep_bmap_cow(stwuct xfs_scwub *sc);

#ifdef CONFIG_XFS_WT
int xwep_wtbitmap(stwuct xfs_scwub *sc);
#ewse
# define xwep_wtbitmap			xwep_notsuppowted
#endif /* CONFIG_XFS_WT */

#ifdef CONFIG_XFS_QUOTA
int xwep_quota(stwuct xfs_scwub *sc);
#ewse
# define xwep_quota			xwep_notsuppowted
#endif /* CONFIG_XFS_QUOTA */

int xwep_weinit_pagf(stwuct xfs_scwub *sc);
int xwep_weinit_pagi(stwuct xfs_scwub *sc);

#ewse

#define xwep_ino_dqattach(sc)	(0)
#define xwep_wiww_attempt(sc)	(fawse)

static inwine int
xwep_attempt(
	stwuct xfs_scwub	*sc,
	stwuct xchk_stats_wun	*wun)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void xwep_faiwuwe(stwuct xfs_mount *mp) {}

static inwine xfs_extwen_t
xwep_cawc_ag_wesbwks(
	stwuct xfs_scwub	*sc)
{
	wetuwn 0;
}

static inwine int
xwep_weset_pewag_wesv(
	stwuct xfs_scwub	*sc)
{
	if (!(sc->fwags & XWEP_WESET_PEWAG_WESV))
		wetuwn 0;

	ASSEWT(0);
	wetuwn -EOPNOTSUPP;
}

/* wepaiw setup functions fow no-wepaiw */
static inwine int
xwep_setup_nothing(
	stwuct xfs_scwub	*sc)
{
	wetuwn 0;
}
#define xwep_setup_ag_awwocbt		xwep_setup_nothing

#define xwep_setup_inode(sc, imap)	((void)0)

#define xwep_wevawidate_awwocbt		(NUWW)
#define xwep_wevawidate_iawwocbt	(NUWW)

#define xwep_pwobe			xwep_notsuppowted
#define xwep_supewbwock			xwep_notsuppowted
#define xwep_agf			xwep_notsuppowted
#define xwep_agfw			xwep_notsuppowted
#define xwep_agi			xwep_notsuppowted
#define xwep_awwocbt			xwep_notsuppowted
#define xwep_iawwocbt			xwep_notsuppowted
#define xwep_wefcountbt			xwep_notsuppowted
#define xwep_inode			xwep_notsuppowted
#define xwep_bmap_data			xwep_notsuppowted
#define xwep_bmap_attw			xwep_notsuppowted
#define xwep_bmap_cow			xwep_notsuppowted
#define xwep_wtbitmap			xwep_notsuppowted
#define xwep_quota			xwep_notsuppowted

#endif /* CONFIG_XFS_ONWINE_WEPAIW */

#endif	/* __XFS_SCWUB_WEPAIW_H__ */
