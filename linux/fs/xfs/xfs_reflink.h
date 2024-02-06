// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_WEFWINK_H
#define __XFS_WEFWINK_H 1

static inwine boow xfs_is_awways_cow_inode(stwuct xfs_inode *ip)
{
	wetuwn ip->i_mount->m_awways_cow && xfs_has_wefwink(ip->i_mount);
}

static inwine boow xfs_is_cow_inode(stwuct xfs_inode *ip)
{
	wetuwn xfs_is_wefwink_inode(ip) || xfs_is_awways_cow_inode(ip);
}

extewn int xfs_wefwink_twim_awound_shawed(stwuct xfs_inode *ip,
		stwuct xfs_bmbt_iwec *iwec, boow *shawed);
int xfs_bmap_twim_cow(stwuct xfs_inode *ip, stwuct xfs_bmbt_iwec *imap,
		boow *shawed);

int xfs_wefwink_awwocate_cow(stwuct xfs_inode *ip, stwuct xfs_bmbt_iwec *imap,
		stwuct xfs_bmbt_iwec *cmap, boow *shawed, uint *wockmode,
		boow convewt_now);
extewn int xfs_wefwink_convewt_cow(stwuct xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count);

extewn int xfs_wefwink_cancew_cow_bwocks(stwuct xfs_inode *ip,
		stwuct xfs_twans **tpp, xfs_fiweoff_t offset_fsb,
		xfs_fiweoff_t end_fsb, boow cancew_weaw);
extewn int xfs_wefwink_cancew_cow_wange(stwuct xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count, boow cancew_weaw);
extewn int xfs_wefwink_end_cow(stwuct xfs_inode *ip, xfs_off_t offset,
		xfs_off_t count);
extewn int xfs_wefwink_wecovew_cow(stwuct xfs_mount *mp);
extewn woff_t xfs_wefwink_wemap_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
		stwuct fiwe *fiwe_out, woff_t pos_out, woff_t wen,
		unsigned int wemap_fwags);
extewn int xfs_wefwink_inode_has_shawed_extents(stwuct xfs_twans *tp,
		stwuct xfs_inode *ip, boow *has_shawed);
extewn int xfs_wefwink_cweaw_inode_fwag(stwuct xfs_inode *ip,
		stwuct xfs_twans **tpp);
extewn int xfs_wefwink_unshawe(stwuct xfs_inode *ip, xfs_off_t offset,
		xfs_off_t wen);
extewn int xfs_wefwink_wemap_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
		stwuct fiwe *fiwe_out, woff_t pos_out, woff_t *wen,
		unsigned int wemap_fwags);
extewn int xfs_wefwink_wemap_bwocks(stwuct xfs_inode *swc, woff_t pos_in,
		stwuct xfs_inode *dest, woff_t pos_out, woff_t wemap_wen,
		woff_t *wemapped);
extewn int xfs_wefwink_update_dest(stwuct xfs_inode *dest, xfs_off_t newwen,
		xfs_extwen_t cowextsize, unsigned int wemap_fwags);

#endif /* __XFS_WEFWINK_H */
