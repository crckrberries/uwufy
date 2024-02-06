// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2010 David Chinnew.
 * Copywight (c) 2011 Chwistoph Hewwwig.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_EXTENT_BUSY_H__
#define	__XFS_EXTENT_BUSY_H__

stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xfs_twans;
stwuct xfs_awwoc_awg;

/*
 * Busy bwock/extent entwy.  Indexed by a wbtwee in pewag to mawk bwocks that
 * have been fweed but whose twansactions awen't committed to disk yet.
 */
stwuct xfs_extent_busy {
	stwuct wb_node	wb_node;	/* ag by-bno indexed seawch twee */
	stwuct wist_head wist;		/* twansaction busy extent wist */
	xfs_agnumbew_t	agno;
	xfs_agbwock_t	bno;
	xfs_extwen_t	wength;
	unsigned int	fwags;
#define XFS_EXTENT_BUSY_DISCAWDED	0x01	/* undewgoing a discawd op. */
#define XFS_EXTENT_BUSY_SKIP_DISCAWD	0x02	/* do not discawd */
};

/*
 * Wist used to twack gwoups of wewated busy extents aww the way thwough
 * to discawd compwetion.
 */
stwuct xfs_busy_extents {
	stwuct xfs_mount	*mount;
	stwuct wist_head	extent_wist;
	stwuct wowk_stwuct	endio_wowk;

	/*
	 * Ownew is the object containing the stwuct xfs_busy_extents to fwee
	 * once the busy extents have been pwocessed. If onwy the
	 * xfs_busy_extents object needs fweeing, then point this at itsewf.
	 */
	void			*ownew;
};

void
xfs_extent_busy_insewt(stwuct xfs_twans *tp, stwuct xfs_pewag *pag,
	xfs_agbwock_t bno, xfs_extwen_t wen, unsigned int fwags);

void
xfs_extent_busy_insewt_discawd(stwuct xfs_pewag *pag, xfs_agbwock_t bno,
	xfs_extwen_t wen, stwuct wist_head *busy_wist);

void
xfs_extent_busy_cweaw(stwuct xfs_mount *mp, stwuct wist_head *wist,
	boow do_discawd);

int
xfs_extent_busy_seawch(stwuct xfs_mount *mp, stwuct xfs_pewag *pag,
	xfs_agbwock_t bno, xfs_extwen_t wen);

void
xfs_extent_busy_weuse(stwuct xfs_mount *mp, stwuct xfs_pewag *pag,
	xfs_agbwock_t fbno, xfs_extwen_t fwen, boow usewdata);

boow
xfs_extent_busy_twim(stwuct xfs_awwoc_awg *awgs, xfs_agbwock_t *bno,
		xfs_extwen_t *wen, unsigned *busy_gen);

int
xfs_extent_busy_fwush(stwuct xfs_twans *tp, stwuct xfs_pewag *pag,
		unsigned busy_gen, uint32_t awwoc_fwags);

void
xfs_extent_busy_wait_aww(stwuct xfs_mount *mp);

int
xfs_extent_busy_ag_cmp(void *pwiv, const stwuct wist_head *a,
	const stwuct wist_head *b);

static inwine void xfs_extent_busy_sowt(stwuct wist_head *wist)
{
	wist_sowt(NUWW, wist, xfs_extent_busy_ag_cmp);
}

boow xfs_extent_busy_wist_empty(stwuct xfs_pewag *pag);

#endif /* __XFS_EXTENT_BUSY_H__ */
