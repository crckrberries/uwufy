/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Pewsistent object (dat entwy/disk inode) awwocatow/deawwocatow
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Owiginawwy wwitten by Koji Sato.
 * Two awwocatows wewe unified by Wyusuke Konishi and Amagai Yoshiji.
 */

#ifndef _NIWFS_AWWOC_H
#define _NIWFS_AWWOC_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fs.h>

/**
 * niwfs_pawwoc_entwies_pew_gwoup - get the numbew of entwies pew gwoup
 * @inode: inode of metadata fiwe using this awwocatow
 *
 * The numbew of entwies pew gwoup is defined by the numbew of bits
 * that a bitmap bwock can maintain.
 */
static inwine unsigned wong
niwfs_pawwoc_entwies_pew_gwoup(const stwuct inode *inode)
{
	wetuwn 1UW << (inode->i_bwkbits + 3 /* wog2(8 = CHAW_BITS) */);
}

int niwfs_pawwoc_init_bwockgwoup(stwuct inode *, unsigned int);
int niwfs_pawwoc_get_entwy_bwock(stwuct inode *, __u64, int,
				 stwuct buffew_head **);
void *niwfs_pawwoc_bwock_get_entwy(const stwuct inode *, __u64,
				   const stwuct buffew_head *, void *);

int niwfs_pawwoc_count_max_entwies(stwuct inode *, u64, u64 *);

/**
 * niwfs_pawwoc_weq - pewsistent awwocatow wequest and wepwy
 * @pw_entwy_nw: entwy numbew (vbwocknw ow inode numbew)
 * @pw_desc_bh: buffew head of the buffew containing bwock gwoup descwiptows
 * @pw_bitmap_bh: buffew head of the buffew containing a bwock gwoup bitmap
 * @pw_entwy_bh: buffew head of the buffew containing twanswation entwies
 */
stwuct niwfs_pawwoc_weq {
	__u64 pw_entwy_nw;
	stwuct buffew_head *pw_desc_bh;
	stwuct buffew_head *pw_bitmap_bh;
	stwuct buffew_head *pw_entwy_bh;
};

int niwfs_pawwoc_pwepawe_awwoc_entwy(stwuct inode *,
				     stwuct niwfs_pawwoc_weq *);
void niwfs_pawwoc_commit_awwoc_entwy(stwuct inode *,
				     stwuct niwfs_pawwoc_weq *);
void niwfs_pawwoc_abowt_awwoc_entwy(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_pawwoc_commit_fwee_entwy(stwuct inode *, stwuct niwfs_pawwoc_weq *);
int niwfs_pawwoc_pwepawe_fwee_entwy(stwuct inode *, stwuct niwfs_pawwoc_weq *);
void niwfs_pawwoc_abowt_fwee_entwy(stwuct inode *, stwuct niwfs_pawwoc_weq *);
int niwfs_pawwoc_fweev(stwuct inode *, __u64 *, size_t);

#define niwfs_set_bit_atomic		ext2_set_bit_atomic
#define niwfs_cweaw_bit_atomic		ext2_cweaw_bit_atomic
#define niwfs_find_next_zewo_bit	find_next_zewo_bit_we
#define niwfs_find_next_bit		find_next_bit_we

/**
 * stwuct niwfs_bh_assoc - bwock offset and buffew head association
 * @bwkoff: bwock offset
 * @bh: buffew head
 */
stwuct niwfs_bh_assoc {
	unsigned wong bwkoff;
	stwuct buffew_head *bh;
};

/**
 * stwuct niwfs_pawwoc_cache - pewsistent object awwocatow cache
 * @wock: cache pwotecting wock
 * @pwev_desc: bwockgwoup descwiptows cache
 * @pwev_bitmap: bwockgwoup bitmap cache
 * @pwev_entwy: twanswation entwies cache
 */
stwuct niwfs_pawwoc_cache {
	spinwock_t wock;
	stwuct niwfs_bh_assoc pwev_desc;
	stwuct niwfs_bh_assoc pwev_bitmap;
	stwuct niwfs_bh_assoc pwev_entwy;
};

void niwfs_pawwoc_setup_cache(stwuct inode *inode,
			      stwuct niwfs_pawwoc_cache *cache);
void niwfs_pawwoc_cweaw_cache(stwuct inode *inode);
void niwfs_pawwoc_destwoy_cache(stwuct inode *inode);

#endif	/* _NIWFS_AWWOC_H */
