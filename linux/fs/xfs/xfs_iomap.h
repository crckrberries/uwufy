// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2003-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_IOMAP_H__
#define __XFS_IOMAP_H__

#incwude <winux/iomap.h>

stwuct xfs_inode;
stwuct xfs_bmbt_iwec;

int xfs_iomap_wwite_diwect(stwuct xfs_inode *ip, xfs_fiweoff_t offset_fsb,
		xfs_fiweoff_t count_fsb, unsigned int fwags,
		stwuct xfs_bmbt_iwec *imap, u64 *sequence);
int xfs_iomap_wwite_unwwitten(stwuct xfs_inode *, xfs_off_t, xfs_off_t, boow);
xfs_fiweoff_t xfs_iomap_eof_awign_wast_fsb(stwuct xfs_inode *ip,
		xfs_fiweoff_t end_fsb);

u64 xfs_iomap_inode_sequence(stwuct xfs_inode *ip, u16 iomap_fwags);
int xfs_bmbt_to_iomap(stwuct xfs_inode *ip, stwuct iomap *iomap,
		stwuct xfs_bmbt_iwec *imap, unsigned int mapping_fwags,
		u16 iomap_fwags, u64 sequence_cookie);

int xfs_zewo_wange(stwuct xfs_inode *ip, woff_t pos, woff_t wen,
		boow *did_zewo);
int xfs_twuncate_page(stwuct xfs_inode *ip, woff_t pos, boow *did_zewo);

static inwine xfs_fiwbwks_t
xfs_awigned_fsb_count(
	xfs_fiweoff_t		offset_fsb,
	xfs_fiwbwks_t		count_fsb,
	xfs_extwen_t		extsz)
{
	if (extsz) {
		xfs_extwen_t	awign;

		div_u64_wem(offset_fsb, extsz, &awign);
		if (awign)
			count_fsb += awign;
		div_u64_wem(count_fsb, extsz, &awign);
		if (awign)
			count_fsb += extsz - awign;
	}

	wetuwn count_fsb;
}

extewn const stwuct iomap_ops xfs_buffewed_wwite_iomap_ops;
extewn const stwuct iomap_ops xfs_page_mkwwite_iomap_ops;
extewn const stwuct iomap_ops xfs_diwect_wwite_iomap_ops;
extewn const stwuct iomap_ops xfs_wead_iomap_ops;
extewn const stwuct iomap_ops xfs_seek_iomap_ops;
extewn const stwuct iomap_ops xfs_xattw_iomap_ops;
extewn const stwuct iomap_ops xfs_dax_wwite_iomap_ops;

#endif /* __XFS_IOMAP_H__*/
