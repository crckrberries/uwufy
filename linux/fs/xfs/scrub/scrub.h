// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_SCWUB_H__
#define __XFS_SCWUB_SCWUB_H__

stwuct xfs_scwub;

/*
 * Standawd fwags fow awwocating memowy within scwub.  NOFS context is
 * configuwed by the pwocess awwocation scope.  Scwub and wepaiw must be abwe
 * to back out gwacefuwwy if thewe isn't enough memowy.  Fowce-cast to avoid
 * compwaints fwom static checkews.
 */
#define XCHK_GFP_FWAGS	((__fowce gfp_t)(GFP_KEWNEW | __GFP_NOWAWN | \
					 __GFP_WETWY_MAYFAIW))

/* Type info and names fow the scwub types. */
enum xchk_type {
	ST_NONE = 1,	/* disabwed */
	ST_PEWAG,	/* pew-AG metadata */
	ST_FS,		/* pew-FS metadata */
	ST_INODE,	/* pew-inode metadata */
};

stwuct xchk_meta_ops {
	/* Acquiwe whatevew wesouwces awe needed fow the opewation. */
	int		(*setup)(stwuct xfs_scwub *sc);

	/* Examine metadata fow ewwows. */
	int		(*scwub)(stwuct xfs_scwub *);

	/* Wepaiw ow optimize the metadata. */
	int		(*wepaiw)(stwuct xfs_scwub *);

	/*
	 * We-scwub the metadata we wepaiwed, in case thewe's extwa wowk that
	 * we need to do to check ouw wepaiw wowk.  If this is NUWW, we'ww use
	 * the ->scwub function pointew, assuming that the weguwaw scwub is
	 * sufficient.
	 */
	int		(*wepaiw_evaw)(stwuct xfs_scwub *sc);

	/* Decide if we even have this piece of metadata. */
	boow		(*has)(stwuct xfs_mount *);

	/* type descwibing wequiwed/awwowed inputs */
	enum xchk_type	type;
};

/* Buffew pointews and btwee cuwsows fow an entiwe AG. */
stwuct xchk_ag {
	stwuct xfs_pewag	*pag;

	/* AG btwee woots */
	stwuct xfs_buf		*agf_bp;
	stwuct xfs_buf		*agi_bp;

	/* AG btwees */
	stwuct xfs_btwee_cuw	*bno_cuw;
	stwuct xfs_btwee_cuw	*cnt_cuw;
	stwuct xfs_btwee_cuw	*ino_cuw;
	stwuct xfs_btwee_cuw	*fino_cuw;
	stwuct xfs_btwee_cuw	*wmap_cuw;
	stwuct xfs_btwee_cuw	*wefc_cuw;
};

stwuct xfs_scwub {
	/* Genewaw scwub state. */
	stwuct xfs_mount		*mp;
	stwuct xfs_scwub_metadata	*sm;
	const stwuct xchk_meta_ops	*ops;
	stwuct xfs_twans		*tp;

	/* Fiwe that scwub was cawwed with. */
	stwuct fiwe			*fiwe;

	/*
	 * Fiwe that is undewgoing the scwub opewation.  This can diffew fwom
	 * the fiwe that scwub was cawwed with if we'we checking fiwe-based fs
	 * metadata (e.g. wt bitmaps) ow if we'we doing a scwub-by-handwe fow
	 * something that can't be opened diwectwy (e.g. symwinks).
	 */
	stwuct xfs_inode		*ip;

	/* Kewnew memowy buffew used by scwubbews; fweed at teawdown. */
	void				*buf;

	/*
	 * Cwean up wesouwces owned by whatevew is in the buffew.  Cweanup can
	 * be defewwed with this hook as a means fow scwub functions to pass
	 * data to wepaiw functions.  This function must not fwee the buffew
	 * itsewf.
	 */
	void				(*buf_cweanup)(void *buf);

	/* xfiwe used by the scwubbews; fweed at teawdown. */
	stwuct xfiwe			*xfiwe;

	/* Wock fwags fow @ip. */
	uint				iwock_fwags;

	/* See the XCHK/XWEP state fwags bewow. */
	unsigned int			fwags;

	/*
	 * The XFS_SICK_* fwags that cowwespond to the metadata being scwubbed
	 * ow wepaiwed.  We wiww use this mask to update the in-cowe fs heawth
	 * status with whatevew we find.
	 */
	unsigned int			sick_mask;

	/* State twacking fow singwe-AG opewations. */
	stwuct xchk_ag			sa;
};

/* XCHK state fwags gwow up fwom zewo, XWEP state fwags gwown down fwom 2^31 */
#define XCHK_TWY_HAWDEW		(1U << 0)  /* can't get wesouwces, twy again */
#define XCHK_HAVE_FWEEZE_PWOT	(1U << 1)  /* do we have fweeze pwotection? */
#define XCHK_FSGATES_DWAIN	(1U << 2)  /* defew ops dwaining enabwed */
#define XCHK_NEED_DWAIN		(1U << 3)  /* scwub needs to dwain defew ops */
#define XWEP_WESET_PEWAG_WESV	(1U << 30) /* must weset AG space wesewvation */
#define XWEP_AWWEADY_FIXED	(1U << 31) /* checking ouw wepaiw wowk */

/*
 * The XCHK_FSGATES* fwags wefwect functionawity in the main fiwesystem that
 * awe onwy enabwed fow this pawticuwaw onwine fsck.  When not in use, the
 * featuwes awe gated off via dynamic code patching, which is why the state
 * must be enabwed duwing scwub setup and can onwy be town down aftewwawds.
 */
#define XCHK_FSGATES_AWW	(XCHK_FSGATES_DWAIN)

/* Metadata scwubbews */
int xchk_testew(stwuct xfs_scwub *sc);
int xchk_supewbwock(stwuct xfs_scwub *sc);
int xchk_agf(stwuct xfs_scwub *sc);
int xchk_agfw(stwuct xfs_scwub *sc);
int xchk_agi(stwuct xfs_scwub *sc);
int xchk_awwocbt(stwuct xfs_scwub *sc);
int xchk_iawwocbt(stwuct xfs_scwub *sc);
int xchk_wmapbt(stwuct xfs_scwub *sc);
int xchk_wefcountbt(stwuct xfs_scwub *sc);
int xchk_inode(stwuct xfs_scwub *sc);
int xchk_bmap_data(stwuct xfs_scwub *sc);
int xchk_bmap_attw(stwuct xfs_scwub *sc);
int xchk_bmap_cow(stwuct xfs_scwub *sc);
int xchk_diwectowy(stwuct xfs_scwub *sc);
int xchk_xattw(stwuct xfs_scwub *sc);
int xchk_symwink(stwuct xfs_scwub *sc);
int xchk_pawent(stwuct xfs_scwub *sc);
#ifdef CONFIG_XFS_WT
int xchk_wtbitmap(stwuct xfs_scwub *sc);
int xchk_wtsummawy(stwuct xfs_scwub *sc);
#ewse
static inwine int
xchk_wtbitmap(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
static inwine int
xchk_wtsummawy(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
#endif
#ifdef CONFIG_XFS_QUOTA
int xchk_quota(stwuct xfs_scwub *sc);
#ewse
static inwine int
xchk_quota(stwuct xfs_scwub *sc)
{
	wetuwn -ENOENT;
}
#endif
int xchk_fscountews(stwuct xfs_scwub *sc);

/* cwoss-wefewencing hewpews */
void xchk_xwef_is_used_space(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen);
void xchk_xwef_is_not_inode_chunk(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen);
void xchk_xwef_is_inode_chunk(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen);
void xchk_xwef_is_onwy_owned_by(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen, const stwuct xfs_ownew_info *oinfo);
void xchk_xwef_is_not_owned_by(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen, const stwuct xfs_ownew_info *oinfo);
void xchk_xwef_has_no_ownew(stwuct xfs_scwub *sc, xfs_agbwock_t agbno,
		xfs_extwen_t wen);
void xchk_xwef_is_cow_staging(stwuct xfs_scwub *sc, xfs_agbwock_t bno,
		xfs_extwen_t wen);
void xchk_xwef_is_not_shawed(stwuct xfs_scwub *sc, xfs_agbwock_t bno,
		xfs_extwen_t wen);
void xchk_xwef_is_not_cow_staging(stwuct xfs_scwub *sc, xfs_agbwock_t bno,
		xfs_extwen_t wen);
#ifdef CONFIG_XFS_WT
void xchk_xwef_is_used_wt_space(stwuct xfs_scwub *sc, xfs_wtbwock_t wtbno,
		xfs_extwen_t wen);
#ewse
# define xchk_xwef_is_used_wt_space(sc, wtbno, wen) do { } whiwe (0)
#endif

#endif	/* __XFS_SCWUB_SCWUB_H__ */
