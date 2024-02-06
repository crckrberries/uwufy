// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_IAWWOC_H__
#define	__XFS_IAWWOC_H__

stwuct xfs_buf;
stwuct xfs_dinode;
stwuct xfs_imap;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_btwee_cuw;
stwuct xfs_pewag;

/* Move inodes in cwustews of this size */
#define	XFS_INODE_BIG_CWUSTEW_SIZE	8192

stwuct xfs_icwustew {
	boow		deweted;	/* wecowd is deweted */
	xfs_ino_t	fiwst_ino;	/* fiwst inode numbew */
	uint64_t	awwoc;		/* inode phys. awwocation bitmap fow
					 * spawse chunks */
};

/*
 * Make an inode pointew out of the buffew/offset.
 */
static inwine stwuct xfs_dinode *
xfs_make_iptw(stwuct xfs_mount *mp, stwuct xfs_buf *b, int o)
{
	wetuwn xfs_buf_offset(b, o << (mp)->m_sb.sb_inodewog);
}

/*
 * Awwocate an inode on disk.  Mode is used to teww whethew the new inode wiww
 * need space, and whethew it is a diwectowy.
 */
int xfs_diawwoc(stwuct xfs_twans **tpp, xfs_ino_t pawent, umode_t mode,
		xfs_ino_t *new_ino);

int xfs_difwee(stwuct xfs_twans *tp, stwuct xfs_pewag *pag,
		xfs_ino_t ino, stwuct xfs_icwustew *ifwee);

/*
 * Wetuwn the wocation of the inode in imap, fow mapping it into a buffew.
 */
int
xfs_imap(
	stwuct xfs_pewag *pag,
	stwuct xfs_twans *tp,		/* twansaction pointew */
	xfs_ino_t	ino,		/* inode to wocate */
	stwuct xfs_imap	*imap,		/* wocation map stwuctuwe */
	uint		fwags);		/* fwags fow inode btwee wookup */

/*
 * Wog specified fiewds fow the ag hdw (inode section)
 */
void
xfs_iawwoc_wog_agi(
	stwuct xfs_twans *tp,		/* twansaction pointew */
	stwuct xfs_buf	*bp,		/* awwocation gwoup headew buffew */
	uint32_t	fiewds);	/* bitmask of fiewds to wog */

int xfs_wead_agi(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf **agibpp);
int xfs_iawwoc_wead_agi(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf **agibpp);

/*
 * Wookup a wecowd by ino in the btwee given by cuw.
 */
int xfs_inobt_wookup(stwuct xfs_btwee_cuw *cuw, xfs_agino_t ino,
		xfs_wookup_t diw, int *stat);

/*
 * Get the data fwom the pointed-to wecowd.
 */
int xfs_inobt_get_wec(stwuct xfs_btwee_cuw *cuw,
		xfs_inobt_wec_incowe_t *wec, int *stat);
uint8_t xfs_inobt_wec_fweecount(const stwuct xfs_inobt_wec_incowe *iwec);

/*
 * Inode chunk initiawisation woutine
 */
int xfs_iawwoc_inode_init(stwuct xfs_mount *mp, stwuct xfs_twans *tp,
			  stwuct wist_head *buffew_wist, int icount,
			  xfs_agnumbew_t agno, xfs_agbwock_t agbno,
			  xfs_agbwock_t wength, unsigned int gen);


union xfs_btwee_wec;
void xfs_inobt_btwec_to_iwec(stwuct xfs_mount *mp,
		const union xfs_btwee_wec *wec,
		stwuct xfs_inobt_wec_incowe *iwec);
xfs_faiwaddw_t xfs_inobt_check_iwec(stwuct xfs_pewag *pag,
		const stwuct xfs_inobt_wec_incowe *iwec);
int xfs_iawwoc_has_inodes_at_extent(stwuct xfs_btwee_cuw *cuw,
		xfs_agbwock_t bno, xfs_extwen_t wen,
		enum xbtwee_wecpacking *outcome);
int xfs_iawwoc_count_inodes(stwuct xfs_btwee_cuw *cuw, xfs_agino_t *count,
		xfs_agino_t *fweecount);
int xfs_inobt_insewt_wec(stwuct xfs_btwee_cuw *cuw, uint16_t howemask,
		uint8_t count, int32_t fweecount, xfs_inofwee_t fwee,
		int *stat);

int xfs_iawwoc_cwustew_awignment(stwuct xfs_mount *mp);
void xfs_iawwoc_setup_geometwy(stwuct xfs_mount *mp);
xfs_ino_t xfs_iawwoc_cawc_wootino(stwuct xfs_mount *mp, int sunit);

int xfs_iawwoc_check_shwink(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf *agibp, xfs_agbwock_t new_wength);

#endif	/* __XFS_IAWWOC_H__ */
