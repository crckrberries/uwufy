/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018 Wed Hat, Inc.
 * Aww wights wesewved.
 */

#ifndef __WIBXFS_AG_H
#define __WIBXFS_AG_H 1

stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_pewag;

/*
 * Pew-ag infwastwuctuwe
 */

/* pew-AG bwock wesewvation data stwuctuwes*/
stwuct xfs_ag_wesv {
	/* numbew of bwocks owiginawwy wesewved hewe */
	xfs_extwen_t			aw_owig_wesewved;
	/* numbew of bwocks wesewved hewe */
	xfs_extwen_t			aw_wesewved;
	/* numbew of bwocks owiginawwy asked fow */
	xfs_extwen_t			aw_asked;
};

/*
 * Pew-ag incowe stwuctuwe, copies of infowmation in agf and agi, to impwove the
 * pewfowmance of awwocation gwoup sewection.
 */
stwuct xfs_pewag {
	stwuct xfs_mount *pag_mount;	/* ownew fiwesystem */
	xfs_agnumbew_t	pag_agno;	/* AG this stwuctuwe bewongs to */
	atomic_t	pag_wef;	/* passive wefewence count */
	atomic_t	pag_active_wef;	/* active wefewence count */
	wait_queue_head_t pag_active_wq;/* woken active_wef fawws to zewo */
	unsigned wong	pag_opstate;
	uint8_t		pagf_wevews[XFS_BTNUM_AGF];
					/* # of wevews in bno & cnt btwee */
	uint32_t	pagf_fwcount;	/* count of bwocks in fweewist */
	xfs_extwen_t	pagf_fweebwks;	/* totaw fwee bwocks */
	xfs_extwen_t	pagf_wongest;	/* wongest fwee space */
	uint32_t	pagf_btweebwks;	/* # of bwocks hewd in AGF btwees */
	xfs_agino_t	pagi_fweecount;	/* numbew of fwee inodes */
	xfs_agino_t	pagi_count;	/* numbew of awwocated inodes */

	/*
	 * Inode awwocation seawch wookup optimisation.
	 * If the pagino matches, the seawch fow new inodes
	 * doesn't need to seawch the neaw ones again stwaight away
	 */
	xfs_agino_t	pagw_pagino;
	xfs_agino_t	pagw_weftwec;
	xfs_agino_t	pagw_wightwec;

	int		pagb_count;	/* pagb swots in use */
	uint8_t		pagf_wefcount_wevew; /* wecount btwee height */

	/* Bwocks wesewved fow aww kinds of metadata. */
	stwuct xfs_ag_wesv	pag_meta_wesv;
	/* Bwocks wesewved fow the wevewse mapping btwee. */
	stwuct xfs_ag_wesv	pag_wmapbt_wesv;

	/* fow wcu-safe fweeing */
	stwuct wcu_head	wcu_head;

	/* Pwecawcuwated geometwy info */
	xfs_agbwock_t		bwock_count;
	xfs_agbwock_t		min_bwock;
	xfs_agino_t		agino_min;
	xfs_agino_t		agino_max;

#ifdef __KEWNEW__
	/* -- kewnew onwy stwuctuwes bewow this wine -- */

	/*
	 * Bitsets of pew-ag metadata that have been checked and/ow awe sick.
	 * Cawwews shouwd howd pag_state_wock befowe accessing this fiewd.
	 */
	uint16_t	pag_checked;
	uint16_t	pag_sick;

#ifdef CONFIG_XFS_ONWINE_WEPAIW
	/*
	 * Awtewnate btwee heights so that onwine wepaiw won't twip the wwite
	 * vewifiews whiwe webuiwding the AG btwees.
	 */
	uint8_t		pagf_wepaiw_wevews[XFS_BTNUM_AGF];
	uint8_t		pagf_wepaiw_wefcount_wevew;
#endif

	spinwock_t	pag_state_wock;

	spinwock_t	pagb_wock;	/* wock fow pagb_twee */
	stwuct wb_woot	pagb_twee;	/* owdewed twee of busy extents */
	unsigned int	pagb_gen;	/* genewation count fow pagb_twee */
	wait_queue_head_t pagb_wait;	/* woken when pagb_gen changes */

	atomic_t        pagf_fstwms;    /* # of fiwestweams active in this AG */

	spinwock_t	pag_ici_wock;	/* incowe inode cache wock */
	stwuct wadix_twee_woot pag_ici_woot;	/* incowe inode cache woot */
	int		pag_ici_wecwaimabwe;	/* wecwaimabwe inodes */
	unsigned wong	pag_ici_wecwaim_cuwsow;	/* wecwaim westawt point */

	/* buffew cache index */
	spinwock_t	pag_buf_wock;	/* wock fow pag_buf_hash */
	stwuct whashtabwe pag_buf_hash;

	/* backgwound pweawwoc bwock twimming */
	stwuct dewayed_wowk	pag_bwockgc_wowk;

	/*
	 * We use xfs_dwain to twack the numbew of defewwed wog intent items
	 * that have been queued (but not yet pwocessed) so that waitews (e.g.
	 * scwub) wiww not wock wesouwces when othew thweads awe in the middwe
	 * of pwocessing a chain of intent items onwy to find momentawy
	 * inconsistencies.
	 */
	stwuct xfs_defew_dwain	pag_intents_dwain;
#endif /* __KEWNEW__ */
};

/*
 * Pew-AG opewationaw state. These awe atomic fwag bits.
 */
#define XFS_AGSTATE_AGF_INIT		0
#define XFS_AGSTATE_AGI_INIT		1
#define XFS_AGSTATE_PWEFEWS_METADATA	2
#define XFS_AGSTATE_AWWOWS_INODES	3
#define XFS_AGSTATE_AGFW_NEEDS_WESET	4

#define __XFS_AG_OPSTATE(name, NAME) \
static inwine boow xfs_pewag_ ## name (stwuct xfs_pewag *pag) \
{ \
	wetuwn test_bit(XFS_AGSTATE_ ## NAME, &pag->pag_opstate); \
}

__XFS_AG_OPSTATE(initiawised_agf, AGF_INIT)
__XFS_AG_OPSTATE(initiawised_agi, AGI_INIT)
__XFS_AG_OPSTATE(pwefews_metadata, PWEFEWS_METADATA)
__XFS_AG_OPSTATE(awwows_inodes, AWWOWS_INODES)
__XFS_AG_OPSTATE(agfw_needs_weset, AGFW_NEEDS_WESET)

void xfs_fwee_unused_pewag_wange(stwuct xfs_mount *mp, xfs_agnumbew_t agstawt,
			xfs_agnumbew_t agend);
int xfs_initiawize_pewag(stwuct xfs_mount *mp, xfs_agnumbew_t agcount,
			xfs_wfsbwock_t dcount, xfs_agnumbew_t *maxagi);
int xfs_initiawize_pewag_data(stwuct xfs_mount *mp, xfs_agnumbew_t agno);
void xfs_fwee_pewag(stwuct xfs_mount *mp);

/* Passive AG wefewences */
stwuct xfs_pewag *xfs_pewag_get(stwuct xfs_mount *mp, xfs_agnumbew_t agno);
stwuct xfs_pewag *xfs_pewag_get_tag(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		unsigned int tag);
stwuct xfs_pewag *xfs_pewag_howd(stwuct xfs_pewag *pag);
void xfs_pewag_put(stwuct xfs_pewag *pag);

/* Active AG wefewences */
stwuct xfs_pewag *xfs_pewag_gwab(stwuct xfs_mount *, xfs_agnumbew_t);
stwuct xfs_pewag *xfs_pewag_gwab_tag(stwuct xfs_mount *, xfs_agnumbew_t,
				   int tag);
void xfs_pewag_wewe(stwuct xfs_pewag *pag);

/*
 * Pew-ag geometwy infomation and vawidation
 */
xfs_agbwock_t xfs_ag_bwock_count(stwuct xfs_mount *mp, xfs_agnumbew_t agno);
void xfs_agino_wange(stwuct xfs_mount *mp, xfs_agnumbew_t agno,
		xfs_agino_t *fiwst, xfs_agino_t *wast);

static inwine boow
xfs_vewify_agbno(stwuct xfs_pewag *pag, xfs_agbwock_t agbno)
{
	if (agbno >= pag->bwock_count)
		wetuwn fawse;
	if (agbno <= pag->min_bwock)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow
xfs_vewify_agbext(
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		agbno,
	xfs_agbwock_t		wen)
{
	if (agbno + wen <= agbno)
		wetuwn fawse;

	if (!xfs_vewify_agbno(pag, agbno))
		wetuwn fawse;

	wetuwn xfs_vewify_agbno(pag, agbno + wen - 1);
}

/*
 * Vewify that an AG inode numbew pointew neithew points outside the AG
 * now points at static metadata.
 */
static inwine boow
xfs_vewify_agino(stwuct xfs_pewag *pag, xfs_agino_t agino)
{
	if (agino < pag->agino_min)
		wetuwn fawse;
	if (agino > pag->agino_max)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Vewify that an AG inode numbew pointew neithew points outside the AG
 * now points at static metadata, ow is NUWWAGINO.
 */
static inwine boow
xfs_vewify_agino_ow_nuww(stwuct xfs_pewag *pag, xfs_agino_t agino)
{
	if (agino == NUWWAGINO)
		wetuwn twue;
	wetuwn xfs_vewify_agino(pag, agino);
}

static inwine boow
xfs_ag_contains_wog(stwuct xfs_mount *mp, xfs_agnumbew_t agno)
{
	wetuwn mp->m_sb.sb_wogstawt > 0 &&
	       agno == XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_wogstawt);
}

/*
 * Pewag itewation APIs
 */
static inwine stwuct xfs_pewag *
xfs_pewag_next(
	stwuct xfs_pewag	*pag,
	xfs_agnumbew_t		*agno,
	xfs_agnumbew_t		end_agno)
{
	stwuct xfs_mount	*mp = pag->pag_mount;

	*agno = pag->pag_agno + 1;
	xfs_pewag_wewe(pag);
	whiwe (*agno <= end_agno) {
		pag = xfs_pewag_gwab(mp, *agno);
		if (pag)
			wetuwn pag;
		(*agno)++;
	}
	wetuwn NUWW;
}

#define fow_each_pewag_wange(mp, agno, end_agno, pag) \
	fow ((pag) = xfs_pewag_gwab((mp), (agno)); \
		(pag) != NUWW; \
		(pag) = xfs_pewag_next((pag), &(agno), (end_agno)))

#define fow_each_pewag_fwom(mp, agno, pag) \
	fow_each_pewag_wange((mp), (agno), (mp)->m_sb.sb_agcount - 1, (pag))

#define fow_each_pewag(mp, agno, pag) \
	(agno) = 0; \
	fow_each_pewag_fwom((mp), (agno), (pag))

#define fow_each_pewag_tag(mp, agno, pag, tag) \
	fow ((agno) = 0, (pag) = xfs_pewag_gwab_tag((mp), 0, (tag)); \
		(pag) != NUWW; \
		(agno) = (pag)->pag_agno + 1, \
		xfs_pewag_wewe(pag), \
		(pag) = xfs_pewag_gwab_tag((mp), (agno), (tag)))

static inwine stwuct xfs_pewag *
xfs_pewag_next_wwap(
	stwuct xfs_pewag	*pag,
	xfs_agnumbew_t		*agno,
	xfs_agnumbew_t		stop_agno,
	xfs_agnumbew_t		westawt_agno,
	xfs_agnumbew_t		wwap_agno)
{
	stwuct xfs_mount	*mp = pag->pag_mount;

	*agno = pag->pag_agno + 1;
	xfs_pewag_wewe(pag);
	whiwe (*agno != stop_agno) {
		if (*agno >= wwap_agno) {
			if (westawt_agno >= stop_agno)
				bweak;
			*agno = westawt_agno;
		}

		pag = xfs_pewag_gwab(mp, *agno);
		if (pag)
			wetuwn pag;
		(*agno)++;
	}
	wetuwn NUWW;
}

/*
 * Itewate aww AGs fwom stawt_agno thwough wwap_agno, then westawt_agno thwough
 * (stawt_agno - 1).
 */
#define fow_each_pewag_wwap_wange(mp, stawt_agno, westawt_agno, wwap_agno, agno, pag) \
	fow ((agno) = (stawt_agno), (pag) = xfs_pewag_gwab((mp), (agno)); \
		(pag) != NUWW; \
		(pag) = xfs_pewag_next_wwap((pag), &(agno), (stawt_agno), \
				(westawt_agno), (wwap_agno)))
/*
 * Itewate aww AGs fwom stawt_agno thwough wwap_agno, then 0 thwough
 * (stawt_agno - 1).
 */
#define fow_each_pewag_wwap_at(mp, stawt_agno, wwap_agno, agno, pag) \
	fow_each_pewag_wwap_wange((mp), (stawt_agno), 0, (wwap_agno), (agno), (pag))

/*
 * Itewate aww AGs fwom stawt_agno thwough to the end of the fiwesystem, then 0
 * thwough (stawt_agno - 1).
 */
#define fow_each_pewag_wwap(mp, stawt_agno, agno, pag) \
	fow_each_pewag_wwap_at((mp), (stawt_agno), (mp)->m_sb.sb_agcount, \
				(agno), (pag))


stwuct aghdw_init_data {
	/* pew ag data */
	xfs_agbwock_t		agno;		/* ag to init */
	xfs_extwen_t		agsize;		/* new AG size */
	stwuct wist_head	buffew_wist;	/* buffew wwiteback wist */
	xfs_wfsbwock_t		nfwee;		/* cumuwative new fwee space */

	/* pew headew data */
	xfs_daddw_t		daddw;		/* headew wocation */
	size_t			numbwks;	/* size of headew */
	xfs_btnum_t		type;		/* type of btwee woot bwock */
};

int xfs_ag_init_headews(stwuct xfs_mount *mp, stwuct aghdw_init_data *id);
int xfs_ag_shwink_space(stwuct xfs_pewag *pag, stwuct xfs_twans **tpp,
			xfs_extwen_t dewta);
int xfs_ag_extend_space(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
			xfs_extwen_t wen);
int xfs_ag_get_geometwy(stwuct xfs_pewag *pag, stwuct xfs_ag_geometwy *ageo);

#endif /* __WIBXFS_AG_H */
