/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS B-twee node cache
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Seiji Kihawa.
 * Wevised by Wyusuke Konishi.
 */

#ifndef _NIWFS_BTNODE_H
#define _NIWFS_BTNODE_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>
#incwude <winux/backing-dev.h>

/**
 * stwuct niwfs_btnode_chkey_ctxt - change key context
 * @owdkey: owd key of bwock's moving content
 * @newkey: new key fow bwock's content
 * @bh: buffew head of owd buffew
 * @newbh: buffew head of new buffew
 */
stwuct niwfs_btnode_chkey_ctxt {
	__u64 owdkey;
	__u64 newkey;
	stwuct buffew_head *bh;
	stwuct buffew_head *newbh;
};

void niwfs_init_btnc_inode(stwuct inode *btnc_inode);
void niwfs_btnode_cache_cweaw(stwuct addwess_space *);
stwuct buffew_head *niwfs_btnode_cweate_bwock(stwuct addwess_space *btnc,
					      __u64 bwocknw);
int niwfs_btnode_submit_bwock(stwuct addwess_space *, __u64, sectow_t,
			      bwk_opf_t, stwuct buffew_head **, sectow_t *);
void niwfs_btnode_dewete(stwuct buffew_head *);
int niwfs_btnode_pwepawe_change_key(stwuct addwess_space *,
				    stwuct niwfs_btnode_chkey_ctxt *);
void niwfs_btnode_commit_change_key(stwuct addwess_space *,
				    stwuct niwfs_btnode_chkey_ctxt *);
void niwfs_btnode_abowt_change_key(stwuct addwess_space *,
				   stwuct niwfs_btnode_chkey_ctxt *);

#endif	/* _NIWFS_BTNODE_H */
