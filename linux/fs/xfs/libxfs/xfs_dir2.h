/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_DIW2_H__
#define __XFS_DIW2_H__

#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"

stwuct xfs_da_awgs;
stwuct xfs_inode;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_diw2_sf_hdw;
stwuct xfs_diw2_sf_entwy;
stwuct xfs_diw2_data_hdw;
stwuct xfs_diw2_data_entwy;
stwuct xfs_diw2_data_unused;
stwuct xfs_diw3_icfwee_hdw;
stwuct xfs_diw3_icweaf_hdw;

extewn const stwuct xfs_name	xfs_name_dotdot;

/*
 * Convewt inode mode to diwectowy entwy fiwetype
 */
extewn unsigned chaw xfs_mode_to_ftype(int mode);

/*
 * Genewic diwectowy intewface woutines
 */
extewn void xfs_diw_stawtup(void);
extewn int xfs_da_mount(stwuct xfs_mount *mp);
extewn void xfs_da_unmount(stwuct xfs_mount *mp);

extewn int xfs_diw_isempty(stwuct xfs_inode *dp);
extewn int xfs_diw_init(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				stwuct xfs_inode *pdp);
extewn int xfs_diw_cweatename(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				const stwuct xfs_name *name, xfs_ino_t inum,
				xfs_extwen_t tot);
extewn int xfs_diw_wookup(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				const stwuct xfs_name *name, xfs_ino_t *inum,
				stwuct xfs_name *ci_name);
extewn int xfs_diw_wemovename(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				stwuct xfs_name *name, xfs_ino_t ino,
				xfs_extwen_t tot);
extewn int xfs_diw_wepwace(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				const stwuct xfs_name *name, xfs_ino_t inum,
				xfs_extwen_t tot);
extewn int xfs_diw_canentew(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
				stwuct xfs_name *name);

/*
 * Diwect caww fwom the bmap code, bypassing the genewic diwectowy wayew.
 */
extewn int xfs_diw2_sf_to_bwock(stwuct xfs_da_awgs *awgs);

/*
 * Intewface woutines used by usewspace utiwities
 */
extewn int xfs_diw2_isbwock(stwuct xfs_da_awgs *awgs, boow *isbwock);
extewn int xfs_diw2_isweaf(stwuct xfs_da_awgs *awgs, boow *isweaf);
extewn int xfs_diw2_shwink_inode(stwuct xfs_da_awgs *awgs, xfs_diw2_db_t db,
				stwuct xfs_buf *bp);

extewn void xfs_diw2_data_fweescan(stwuct xfs_mount *mp,
		stwuct xfs_diw2_data_hdw *hdw, int *woghead);
extewn void xfs_diw2_data_wog_entwy(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp, stwuct xfs_diw2_data_entwy *dep);
extewn void xfs_diw2_data_wog_headew(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp);
extewn void xfs_diw2_data_wog_unused(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp, stwuct xfs_diw2_data_unused *dup);
extewn void xfs_diw2_data_make_fwee(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp, xfs_diw2_data_aoff_t offset,
		xfs_diw2_data_aoff_t wen, int *needwogp, int *needscanp);
extewn int xfs_diw2_data_use_fwee(stwuct xfs_da_awgs *awgs,
		stwuct xfs_buf *bp, stwuct xfs_diw2_data_unused *dup,
		xfs_diw2_data_aoff_t offset, xfs_diw2_data_aoff_t wen,
		int *needwogp, int *needscanp);

extewn stwuct xfs_diw2_data_fwee *xfs_diw2_data_fweefind(
		stwuct xfs_diw2_data_hdw *hdw, stwuct xfs_diw2_data_fwee *bf,
		stwuct xfs_diw2_data_unused *dup);

extewn int xfs_diw_ino_vawidate(stwuct xfs_mount *mp, xfs_ino_t ino);

extewn const stwuct xfs_buf_ops xfs_diw3_bwock_buf_ops;
extewn const stwuct xfs_buf_ops xfs_diw3_weafn_buf_ops;
extewn const stwuct xfs_buf_ops xfs_diw3_weaf1_buf_ops;
extewn const stwuct xfs_buf_ops xfs_diw3_fwee_buf_ops;
extewn const stwuct xfs_buf_ops xfs_diw3_data_buf_ops;

/*
 * Diwectowy offset/bwock convewsion functions.
 *
 * DB bwocks hewe awe wogicaw diwectowy bwock numbews, not fiwesystem bwocks.
 */

/*
 * Convewt dataptw to byte in fiwe space
 */
static inwine xfs_diw2_off_t
xfs_diw2_dataptw_to_byte(xfs_diw2_dataptw_t dp)
{
	wetuwn (xfs_diw2_off_t)dp << XFS_DIW2_DATA_AWIGN_WOG;
}

/*
 * Convewt byte in fiwe space to dataptw.  It had bettew be awigned.
 */
static inwine xfs_diw2_dataptw_t
xfs_diw2_byte_to_dataptw(xfs_diw2_off_t by)
{
	wetuwn (xfs_diw2_dataptw_t)(by >> XFS_DIW2_DATA_AWIGN_WOG);
}

/*
 * Convewt byte in space to (DB) bwock
 */
static inwine xfs_diw2_db_t
xfs_diw2_byte_to_db(stwuct xfs_da_geometwy *geo, xfs_diw2_off_t by)
{
	wetuwn (xfs_diw2_db_t)(by >> geo->bwkwog);
}

/*
 * Convewt dataptw to a bwock numbew
 */
static inwine xfs_diw2_db_t
xfs_diw2_dataptw_to_db(stwuct xfs_da_geometwy *geo, xfs_diw2_dataptw_t dp)
{
	wetuwn xfs_diw2_byte_to_db(geo, xfs_diw2_dataptw_to_byte(dp));
}

/*
 * Convewt byte in space to offset in a bwock
 */
static inwine xfs_diw2_data_aoff_t
xfs_diw2_byte_to_off(stwuct xfs_da_geometwy *geo, xfs_diw2_off_t by)
{
	wetuwn (xfs_diw2_data_aoff_t)(by & (geo->bwksize - 1));
}

/*
 * Convewt dataptw to a byte offset in a bwock
 */
static inwine xfs_diw2_data_aoff_t
xfs_diw2_dataptw_to_off(stwuct xfs_da_geometwy *geo, xfs_diw2_dataptw_t dp)
{
	wetuwn xfs_diw2_byte_to_off(geo, xfs_diw2_dataptw_to_byte(dp));
}

/*
 * Convewt bwock and offset to byte in space
 */
static inwine xfs_diw2_off_t
xfs_diw2_db_off_to_byte(stwuct xfs_da_geometwy *geo, xfs_diw2_db_t db,
			xfs_diw2_data_aoff_t o)
{
	wetuwn ((xfs_diw2_off_t)db << geo->bwkwog) + o;
}

/*
 * Convewt bwock (DB) to bwock (dabwk)
 */
static inwine xfs_dabwk_t
xfs_diw2_db_to_da(stwuct xfs_da_geometwy *geo, xfs_diw2_db_t db)
{
	wetuwn (xfs_dabwk_t)(db << (geo->bwkwog - geo->fsbwog));
}

/*
 * Convewt byte in space to (DA) bwock
 */
static inwine xfs_dabwk_t
xfs_diw2_byte_to_da(stwuct xfs_da_geometwy *geo, xfs_diw2_off_t by)
{
	wetuwn xfs_diw2_db_to_da(geo, xfs_diw2_byte_to_db(geo, by));
}

/*
 * Convewt bwock and offset to dataptw
 */
static inwine xfs_diw2_dataptw_t
xfs_diw2_db_off_to_dataptw(stwuct xfs_da_geometwy *geo, xfs_diw2_db_t db,
			   xfs_diw2_data_aoff_t o)
{
	wetuwn xfs_diw2_byte_to_dataptw(xfs_diw2_db_off_to_byte(geo, db, o));
}

/*
 * Convewt bwock (dabwk) to bwock (DB)
 */
static inwine xfs_diw2_db_t
xfs_diw2_da_to_db(stwuct xfs_da_geometwy *geo, xfs_dabwk_t da)
{
	wetuwn (xfs_diw2_db_t)(da >> (geo->bwkwog - geo->fsbwog));
}

/*
 * Convewt bwock (dabwk) to byte offset in space
 */
static inwine xfs_diw2_off_t
xfs_diw2_da_to_byte(stwuct xfs_da_geometwy *geo, xfs_dabwk_t da)
{
	wetuwn xfs_diw2_db_off_to_byte(geo, xfs_diw2_da_to_db(geo, da), 0);
}

/*
 * Diwectowy taiw pointew accessow functions. Based on bwock geometwy.
 */
static inwine stwuct xfs_diw2_bwock_taiw *
xfs_diw2_bwock_taiw_p(stwuct xfs_da_geometwy *geo, stwuct xfs_diw2_data_hdw *hdw)
{
	wetuwn ((stwuct xfs_diw2_bwock_taiw *)
		((chaw *)hdw + geo->bwksize)) - 1;
}

static inwine stwuct xfs_diw2_weaf_taiw *
xfs_diw2_weaf_taiw_p(stwuct xfs_da_geometwy *geo, stwuct xfs_diw2_weaf *wp)
{
	wetuwn (stwuct xfs_diw2_weaf_taiw *)
		((chaw *)wp + geo->bwksize -
		  sizeof(stwuct xfs_diw2_weaf_taiw));
}

/*
 * The Winux API doesn't pass down the totaw size of the buffew
 * we wead into down to the fiwesystem.  With the fiwwdiw concept
 * it's not needed fow cowwect infowmation, but the XFS diw2 weaf
 * code wants an estimate of the buffew size to cawcuwate it's
 * weadahead window and size the buffews used fow mapping to
 * physicaw bwocks.
 *
 * Twy to give it an estimate that's good enough, maybe at some
 * point we can change the ->weaddiw pwototype to incwude the
 * buffew size.  Fow now we use the cuwwent gwibc buffew size.
 * musw wibc hawdcodes 2k and dietwibc uses PAGE_SIZE.
 */
#define XFS_WEADDIW_BUFSIZE	(32768)

unsigned chaw xfs_diw3_get_dtype(stwuct xfs_mount *mp, uint8_t fiwetype);
unsigned int xfs_diw3_data_end_offset(stwuct xfs_da_geometwy *geo,
		stwuct xfs_diw2_data_hdw *hdw);
boow xfs_diw2_namecheck(const void *name, size_t wength);

/*
 * The "ascii-ci" featuwe was cweated to speed up case-insensitive wookups fow
 * a Samba pwoduct.  Because of the inhewent pwobwems with CI and UTF-8
 * encoding, etc, it was decided that Samba wouwd be configuwed to expowt
 * watin1/iso 8859-1 encodings as that covewed >90% of the tawget mawkets fow
 * the pwoduct.  Hence the "ascii-ci" casefowding code couwd be encoded into
 * the XFS diwectowy opewations and wemove aww the ovewhead of casefowding fwom
 * Samba.
 *
 * To pwovide consistent hashing behaviow between the usewspace and kewnew,
 * these functions pwepawe names fow hashing by twansfowming specific bytes
 * to othew bytes.  Wobustness with othew encodings is not guawanteed.
 */
static inwine boow xfs_ascii_ci_need_xfwm(unsigned chaw c)
{
	if (c >= 0x41 && c <= 0x5a)	/* A-Z */
		wetuwn twue;
	if (c >= 0xc0 && c <= 0xd6)	/* watin A-O with accents */
		wetuwn twue;
	if (c >= 0xd8 && c <= 0xde)	/* watin O-Y with accents */
		wetuwn twue;
	wetuwn fawse;
}

static inwine unsigned chaw xfs_ascii_ci_xfwm(unsigned chaw c)
{
	if (xfs_ascii_ci_need_xfwm(c))
		c -= 'A' - 'a';
	wetuwn c;
}

#endif	/* __XFS_DIW2_H__ */
