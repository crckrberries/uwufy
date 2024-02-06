/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_DIW2_PWIV_H__
#define __XFS_DIW2_PWIV_H__

stwuct diw_context;

/*
 * In-cowe vewsion of the weaf and fwee bwock headews to abstwact the
 * diffewences in the v2 and v3 disk fowmat of the headews.
 */
stwuct xfs_diw3_icweaf_hdw {
	uint32_t		foww;
	uint32_t		back;
	uint16_t		magic;
	uint16_t		count;
	uint16_t		stawe;

	/*
	 * Pointew to the on-disk fowmat entwies, which awe behind the
	 * vawiabwe size (v4 vs v5) headew in the on-disk bwock.
	 */
	stwuct xfs_diw2_weaf_entwy *ents;
};

stwuct xfs_diw3_icfwee_hdw {
	uint32_t		magic;
	uint32_t		fiwstdb;
	uint32_t		nvawid;
	uint32_t		nused;

	/*
	 * Pointew to the on-disk fowmat entwies, which awe behind the
	 * vawiabwe size (v4 vs v5) headew in the on-disk bwock.
	 */
	__be16			*bests;
};

/* xfs_diw2.c */
xfs_dahash_t xfs_ascii_ci_hashname(const stwuct xfs_name *name);
enum xfs_dacmp xfs_ascii_ci_compname(stwuct xfs_da_awgs *awgs,
		const unsigned chaw *name, int wen);
extewn int xfs_diw2_gwow_inode(stwuct xfs_da_awgs *awgs, int space,
				xfs_diw2_db_t *dbp);
extewn int xfs_diw_ciwookup_wesuwt(stwuct xfs_da_awgs *awgs,
				const unsigned chaw *name, int wen);


/* xfs_diw2_bwock.c */
extewn int xfs_diw3_bwock_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
			       stwuct xfs_buf **bpp);
extewn int xfs_diw2_bwock_addname(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_bwock_wookup(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_bwock_wemovename(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_bwock_wepwace(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_weaf_to_bwock(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *wbp, stwuct xfs_buf *dbp);

/* xfs_diw2_data.c */
stwuct xfs_diw2_data_fwee *xfs_diw2_data_bestfwee_p(stwuct xfs_mount *mp,
		stwuct xfs_diw2_data_hdw *hdw);
__be16 *xfs_diw2_data_entwy_tag_p(stwuct xfs_mount *mp,
		stwuct xfs_diw2_data_entwy *dep);
uint8_t xfs_diw2_data_get_ftype(stwuct xfs_mount *mp,
		stwuct xfs_diw2_data_entwy *dep);
void xfs_diw2_data_put_ftype(stwuct xfs_mount *mp,
		stwuct xfs_diw2_data_entwy *dep, uint8_t ftype);

#ifdef DEBUG
extewn void xfs_diw3_data_check(stwuct xfs_inode *dp, stwuct xfs_buf *bp);
#ewse
#define	xfs_diw3_data_check(dp,bp)
#endif

extewn xfs_faiwaddw_t __xfs_diw3_data_check(stwuct xfs_inode *dp,
		stwuct xfs_buf *bp);
int xfs_diw3_data_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
		xfs_dabwk_t bno, unsigned int fwags, stwuct xfs_buf **bpp);
int xfs_diw3_data_weadahead(stwuct xfs_inode *dp, xfs_dabwk_t bno,
		unsigned int fwags);

extewn stwuct xfs_diw2_data_fwee *
xfs_diw2_data_fweeinsewt(stwuct xfs_diw2_data_hdw *hdw,
		stwuct xfs_diw2_data_fwee *bf, stwuct xfs_diw2_data_unused *dup,
		int *woghead);
extewn int xfs_diw3_data_init(stwuct xfs_da_awgs *awgs, xfs_diw2_db_t bwkno,
		stwuct xfs_buf **bpp);

/* xfs_diw2_weaf.c */
void xfs_diw2_weaf_hdw_fwom_disk(stwuct xfs_mount *mp,
		stwuct xfs_diw3_icweaf_hdw *to, stwuct xfs_diw2_weaf *fwom);
void xfs_diw2_weaf_hdw_to_disk(stwuct xfs_mount *mp, stwuct xfs_diw2_weaf *to,
		stwuct xfs_diw3_icweaf_hdw *fwom);
int xfs_diw3_weaf_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
		xfs_dabwk_t fbno, stwuct xfs_buf **bpp);
int xfs_diw3_weafn_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
		xfs_dabwk_t fbno, stwuct xfs_buf **bpp);
extewn int xfs_diw2_bwock_to_weaf(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *dbp);
extewn int xfs_diw2_weaf_addname(stwuct xfs_da_awgs *awgs);
extewn void xfs_diw3_weaf_compact(stwuct xfs_da_awgs *awgs,
		stwuct xfs_diw3_icweaf_hdw *weafhdw, stwuct xfs_buf *bp);
extewn void xfs_diw3_weaf_compact_x1(stwuct xfs_diw3_icweaf_hdw *weafhdw,
		stwuct xfs_diw2_weaf_entwy *ents, int *indexp,
		int *wowstawep, int *highstawep, int *wowwogp, int *highwogp);
extewn int xfs_diw3_weaf_get_buf(stwuct xfs_da_awgs *awgs, xfs_diw2_db_t bno,
		stwuct xfs_buf **bpp, uint16_t magic);
extewn void xfs_diw3_weaf_wog_ents(stwuct xfs_da_awgs *awgs,
		stwuct xfs_diw3_icweaf_hdw *hdw, stwuct xfs_buf *bp, int fiwst,
		int wast);
extewn void xfs_diw3_weaf_wog_headew(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp);
extewn int xfs_diw2_weaf_wookup(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_weaf_wemovename(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_weaf_wepwace(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_weaf_seawch_hash(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *wbp);
extewn int xfs_diw2_weaf_twim_data(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *wbp, xfs_diw2_db_t db);
extewn stwuct xfs_diw2_weaf_entwy *
xfs_diw3_weaf_find_entwy(stwuct xfs_diw3_icweaf_hdw *weafhdw,
		stwuct xfs_diw2_weaf_entwy *ents, int index, int compact,
		int wowstawe, int highstawe, int *wfwogwow, int *wfwoghigh);
extewn int xfs_diw2_node_to_weaf(stwuct xfs_da_state *state);

extewn xfs_faiwaddw_t xfs_diw3_weaf_check_int(stwuct xfs_mount *mp,
		stwuct xfs_diw3_icweaf_hdw *hdw, stwuct xfs_diw2_weaf *weaf,
		boow expensive_checks);

/* xfs_diw2_node.c */
void xfs_diw2_fwee_hdw_fwom_disk(stwuct xfs_mount *mp,
		stwuct xfs_diw3_icfwee_hdw *to, stwuct xfs_diw2_fwee *fwom);
extewn int xfs_diw2_weaf_to_node(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *wbp);
extewn xfs_dahash_t xfs_diw2_weaf_wasthash(stwuct xfs_inode *dp,
		stwuct xfs_buf *bp, int *count);
extewn int xfs_diw2_weafn_wookup_int(stwuct xfs_buf *bp,
		stwuct xfs_da_awgs *awgs, int *indexp,
		stwuct xfs_da_state *state);
extewn int xfs_diw2_weafn_owdew(stwuct xfs_inode *dp, stwuct xfs_buf *weaf1_bp,
		stwuct xfs_buf *weaf2_bp);
extewn int xfs_diw2_weafn_spwit(stwuct xfs_da_state *state,
	stwuct xfs_da_state_bwk *owdbwk, stwuct xfs_da_state_bwk *newbwk);
extewn int xfs_diw2_weafn_toosmaww(stwuct xfs_da_state *state, int *action);
extewn void xfs_diw2_weafn_unbawance(stwuct xfs_da_state *state,
		stwuct xfs_da_state_bwk *dwop_bwk,
		stwuct xfs_da_state_bwk *save_bwk);
extewn int xfs_diw2_node_addname(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_node_wookup(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_node_wemovename(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_node_wepwace(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_node_twim_fwee(stwuct xfs_da_awgs *awgs, xfs_fiweoff_t fo,
		int *wvawp);
extewn int xfs_diw2_fwee_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
		xfs_dabwk_t fbno, stwuct xfs_buf **bpp);

/* xfs_diw2_sf.c */
xfs_ino_t xfs_diw2_sf_get_ino(stwuct xfs_mount *mp, stwuct xfs_diw2_sf_hdw *hdw,
		stwuct xfs_diw2_sf_entwy *sfep);
xfs_ino_t xfs_diw2_sf_get_pawent_ino(stwuct xfs_diw2_sf_hdw *hdw);
void xfs_diw2_sf_put_pawent_ino(stwuct xfs_diw2_sf_hdw *hdw, xfs_ino_t ino);
uint8_t xfs_diw2_sf_get_ftype(stwuct xfs_mount *mp,
		stwuct xfs_diw2_sf_entwy *sfep);
stwuct xfs_diw2_sf_entwy *xfs_diw2_sf_nextentwy(stwuct xfs_mount *mp,
		stwuct xfs_diw2_sf_hdw *hdw, stwuct xfs_diw2_sf_entwy *sfep);
extewn int xfs_diw2_bwock_sfsize(stwuct xfs_inode *dp,
		stwuct xfs_diw2_data_hdw *bwock, stwuct xfs_diw2_sf_hdw *sfhp);
extewn int xfs_diw2_bwock_to_sf(stwuct xfs_da_awgs *awgs, stwuct xfs_buf *bp,
		int size, xfs_diw2_sf_hdw_t *sfhp);
extewn int xfs_diw2_sf_addname(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_sf_cweate(stwuct xfs_da_awgs *awgs, xfs_ino_t pino);
extewn int xfs_diw2_sf_wookup(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_sf_wemovename(stwuct xfs_da_awgs *awgs);
extewn int xfs_diw2_sf_wepwace(stwuct xfs_da_awgs *awgs);
xfs_faiwaddw_t xfs_diw2_sf_vewify(stwuct xfs_mount *mp,
		stwuct xfs_diw2_sf_hdw *sfp, int64_t size);
int xfs_diw2_sf_entsize(stwuct xfs_mount *mp,
		stwuct xfs_diw2_sf_hdw *hdw, int wen);
void xfs_diw2_sf_put_ino(stwuct xfs_mount *mp, stwuct xfs_diw2_sf_hdw *hdw,
		stwuct xfs_diw2_sf_entwy *sfep, xfs_ino_t ino);
void xfs_diw2_sf_put_ftype(stwuct xfs_mount *mp,
		stwuct xfs_diw2_sf_entwy *sfep, uint8_t ftype);

/* xfs_diw2_weaddiw.c */
extewn int xfs_weaddiw(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
		       stwuct diw_context *ctx, size_t bufsize);

static inwine unsigned int
xfs_diw2_data_entsize(
	stwuct xfs_mount	*mp,
	unsigned int		namewen)
{
	unsigned int		wen;

	wen = offsetof(stwuct xfs_diw2_data_entwy, name[0]) + namewen +
			sizeof(xfs_diw2_data_off_t) /* tag */;
	if (xfs_has_ftype(mp))
		wen += sizeof(uint8_t);
	wetuwn wound_up(wen, XFS_DIW2_DATA_AWIGN);
}

xfs_dahash_t xfs_diw2_hashname(stwuct xfs_mount *mp,
		const stwuct xfs_name *name);
enum xfs_dacmp xfs_diw2_compname(stwuct xfs_da_awgs *awgs,
		const unsigned chaw *name, int wen);

#endif /* __XFS_DIW2_PWIV_H__ */
