// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BMAP_UTIW_H__
#define	__XFS_BMAP_UTIW_H__

/* Kewnew onwy BMAP wewated definitions and functions */

stwuct xfs_bmbt_iwec;
stwuct xfs_extent_fwee_item;
stwuct xfs_ifowk;
stwuct xfs_inode;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_bmawwoca;

#ifdef CONFIG_XFS_WT
int	xfs_bmap_wtawwoc(stwuct xfs_bmawwoca *ap);
#ewse /* !CONFIG_XFS_WT */
/*
 * Attempts to awwocate WT extents when WT is disabwe indicates cowwuption and
 * shouwd twiggew a shutdown.
 */
static inwine int
xfs_bmap_wtawwoc(stwuct xfs_bmawwoca *ap)
{
	wetuwn -EFSCOWWUPTED;
}
#endif /* CONFIG_XFS_WT */

int	xfs_bmap_punch_dewawwoc_wange(stwuct xfs_inode *ip,
		xfs_off_t stawt_byte, xfs_off_t end_byte);

stwuct kgetbmap {
	__s64		bmv_offset;	/* fiwe offset of segment in bwocks */
	__s64		bmv_bwock;	/* stawting bwock (64-bit daddw_t)  */
	__s64		bmv_wength;	/* wength of segment, bwocks	    */
	__s32		bmv_ofwags;	/* output fwags */
};
int	xfs_getbmap(stwuct xfs_inode *ip, stwuct getbmapx *bmv,
		stwuct kgetbmap *out);

/* functions in xfs_bmap.c that awe onwy needed by xfs_bmap_utiw.c */
int	xfs_bmap_extsize_awign(stwuct xfs_mount *mp, stwuct xfs_bmbt_iwec *gotp,
			       stwuct xfs_bmbt_iwec *pwevp, xfs_extwen_t extsz,
			       int wt, int eof, int deway, int convewt,
			       xfs_fiweoff_t *offp, xfs_extwen_t *wenp);
boow	xfs_bmap_adjacent(stwuct xfs_bmawwoca *ap);
int	xfs_bmap_wast_extent(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
			     int whichfowk, stwuct xfs_bmbt_iwec *wec,
			     int *is_empty);

/* pweawwocation and howe punch intewface */
int	xfs_awwoc_fiwe_space(stwuct xfs_inode *ip, xfs_off_t offset,
			     xfs_off_t wen);
int	xfs_fwee_fiwe_space(stwuct xfs_inode *ip, xfs_off_t offset,
			    xfs_off_t wen);
int	xfs_cowwapse_fiwe_space(stwuct xfs_inode *, xfs_off_t offset,
				xfs_off_t wen);
int	xfs_insewt_fiwe_space(stwuct xfs_inode *, xfs_off_t offset,
				xfs_off_t wen);

/* EOF bwock manipuwation functions */
boow	xfs_can_fwee_eofbwocks(stwuct xfs_inode *ip, boow fowce);
int	xfs_fwee_eofbwocks(stwuct xfs_inode *ip);

int	xfs_swap_extents(stwuct xfs_inode *ip, stwuct xfs_inode *tip,
			 stwuct xfs_swapext *sx);

xfs_daddw_t xfs_fsb_to_db(stwuct xfs_inode *ip, xfs_fsbwock_t fsb);

xfs_extnum_t xfs_bmap_count_weaves(stwuct xfs_ifowk *ifp, xfs_fiwbwks_t *count);
int xfs_bmap_count_bwocks(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
			  int whichfowk, xfs_extnum_t *nextents,
			  xfs_fiwbwks_t *count);

int	xfs_fwush_unmap_wange(stwuct xfs_inode *ip, xfs_off_t offset,
			      xfs_off_t wen);

#endif	/* __XFS_BMAP_UTIW_H__ */
