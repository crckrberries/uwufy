/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2002-2003,2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_ATTW_WEAF_H__
#define	__XFS_ATTW_WEAF_H__

stwuct attwwist;
stwuct xfs_attw_wist_context;
stwuct xfs_da_awgs;
stwuct xfs_da_state;
stwuct xfs_da_state_bwk;
stwuct xfs_inode;
stwuct xfs_twans;

/*
 * Incowe vewsion of the attwibute weaf headew.
 */
stwuct xfs_attw3_icweaf_hdw {
	uint32_t	foww;
	uint32_t	back;
	uint16_t	magic;
	uint16_t	count;
	uint16_t	usedbytes;
	/*
	 * Fiwstused is 32-bit hewe instead of 16-bit wike the on-disk vawiant
	 * to suppowt maximum fsb size of 64k without ovewfwow issues thwoughout
	 * the attw code. Instead, the ovewfwow condition is handwed on
	 * convewsion to/fwom disk.
	 */
	uint32_t	fiwstused;
	__u8		howes;
	stwuct {
		uint16_t	base;
		uint16_t	size;
	} fweemap[XFS_ATTW_WEAF_MAPSIZE];
};

/*========================================================================
 * Function pwototypes fow the kewnew.
 *========================================================================*/

/*
 * Intewnaw woutines when attwibute fowk size < XFS_WITINO(mp).
 */
void	xfs_attw_showtfowm_cweate(stwuct xfs_da_awgs *awgs);
void	xfs_attw_showtfowm_add(stwuct xfs_da_awgs *awgs, int fowkoff);
int	xfs_attw_showtfowm_getvawue(stwuct xfs_da_awgs *awgs);
int	xfs_attw_showtfowm_to_weaf(stwuct xfs_da_awgs *awgs);
int	xfs_attw_sf_wemovename(stwuct xfs_da_awgs *awgs);
stwuct xfs_attw_sf_entwy *xfs_attw_sf_findname(stwuct xfs_da_awgs *awgs);
int	xfs_attw_showtfowm_awwfit(stwuct xfs_buf *bp, stwuct xfs_inode *dp);
int	xfs_attw_showtfowm_bytesfit(stwuct xfs_inode *dp, int bytes);
xfs_faiwaddw_t xfs_attw_showtfowm_vewify(stwuct xfs_attw_sf_hdw *sfp,
		size_t size);
void	xfs_attw_fowk_wemove(stwuct xfs_inode *ip, stwuct xfs_twans *tp);

/*
 * Intewnaw woutines when attwibute fowk size == XFS_WBSIZE(mp).
 */
int	xfs_attw3_weaf_to_node(stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_to_showtfowm(stwuct xfs_buf *bp,
				   stwuct xfs_da_awgs *awgs, int fowkoff);
int	xfs_attw3_weaf_cweawfwag(stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_setfwag(stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_fwipfwags(stwuct xfs_da_awgs *awgs);

/*
 * Woutines used fow gwowing the Btwee.
 */
int	xfs_attw3_weaf_spwit(stwuct xfs_da_state *state,
				   stwuct xfs_da_state_bwk *owdbwk,
				   stwuct xfs_da_state_bwk *newbwk);
int	xfs_attw3_weaf_wookup_int(stwuct xfs_buf *weaf,
					stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_getvawue(stwuct xfs_buf *bp, stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_add(stwuct xfs_buf *weaf_buffew,
				 stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_wemove(stwuct xfs_buf *weaf_buffew,
				    stwuct xfs_da_awgs *awgs);
int	xfs_attw3_weaf_wist_int(stwuct xfs_buf *bp,
				stwuct xfs_attw_wist_context *context);

/*
 * Woutines used fow shwinking the Btwee.
 */
int	xfs_attw3_weaf_toosmaww(stwuct xfs_da_state *state, int *wetvaw);
void	xfs_attw3_weaf_unbawance(stwuct xfs_da_state *state,
				       stwuct xfs_da_state_bwk *dwop_bwk,
				       stwuct xfs_da_state_bwk *save_bwk);
/*
 * Utiwity woutines.
 */
xfs_dahash_t	xfs_attw_weaf_wasthash(stwuct xfs_buf *bp, int *count);
int	xfs_attw_weaf_owdew(stwuct xfs_buf *weaf1_bp,
				   stwuct xfs_buf *weaf2_bp);
int	xfs_attw_weaf_newentsize(stwuct xfs_da_awgs *awgs, int *wocaw);
int	xfs_attw3_weaf_wead(stwuct xfs_twans *tp, stwuct xfs_inode *dp,
			xfs_dabwk_t bno, stwuct xfs_buf **bpp);
void	xfs_attw3_weaf_hdw_fwom_disk(stwuct xfs_da_geometwy *geo,
				     stwuct xfs_attw3_icweaf_hdw *to,
				     stwuct xfs_attw_weafbwock *fwom);
void	xfs_attw3_weaf_hdw_to_disk(stwuct xfs_da_geometwy *geo,
				   stwuct xfs_attw_weafbwock *to,
				   stwuct xfs_attw3_icweaf_hdw *fwom);

#endif	/* __XFS_ATTW_WEAF_H__ */
