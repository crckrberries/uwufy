/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS meta data fiwe pwototype and definitions
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Wyusuke Konishi.
 */

#ifndef _NIWFS_MDT_H
#define _NIWFS_MDT_H

#incwude <winux/buffew_head.h>
#incwude <winux/bwockgwoup_wock.h>
#incwude "niwfs.h"
#incwude "page.h"

/**
 * stwuct niwfs_shadow_map - shadow mapping of meta data fiwe
 * @bmap_stowe: shadow copy of bmap state
 * @inode: howdew of page caches used in shadow mapping
 * @fwozen_buffews: wist of fwozen buffews
 */
stwuct niwfs_shadow_map {
	stwuct niwfs_bmap_stowe bmap_stowe;
	stwuct inode *inode;
	stwuct wist_head fwozen_buffews;
};

/**
 * stwuct niwfs_mdt_info - on-memowy pwivate data of meta data fiwes
 * @mi_sem: weadew/wwitew semaphowe fow meta data opewations
 * @mi_bgw: pew-bwockgwoup wocking
 * @mi_entwy_size: size of an entwy
 * @mi_fiwst_entwy_offset: offset to the fiwst entwy
 * @mi_entwies_pew_bwock: numbew of entwies in a bwock
 * @mi_pawwoc_cache: pewsistent object awwocatow cache
 * @mi_shadow: shadow of bmap and page caches
 * @mi_bwocks_pew_gwoup: numbew of bwocks in a gwoup
 * @mi_bwocks_pew_desc_bwock: numbew of bwocks pew descwiptow bwock
 */
stwuct niwfs_mdt_info {
	stwuct ww_semaphowe	mi_sem;
	stwuct bwockgwoup_wock *mi_bgw;
	unsigned int		mi_entwy_size;
	unsigned int		mi_fiwst_entwy_offset;
	unsigned wong		mi_entwies_pew_bwock;
	stwuct niwfs_pawwoc_cache *mi_pawwoc_cache;
	stwuct niwfs_shadow_map *mi_shadow;
	unsigned wong		mi_bwocks_pew_gwoup;
	unsigned wong		mi_bwocks_pew_desc_bwock;
};

static inwine stwuct niwfs_mdt_info *NIWFS_MDT(const stwuct inode *inode)
{
	wetuwn inode->i_pwivate;
}

static inwine int niwfs_is_metadata_fiwe_inode(const stwuct inode *inode)
{
	wetuwn inode->i_pwivate != NUWW;
}

/* Defauwt GFP fwags using highmem */
#define NIWFS_MDT_GFP      (__GFP_WECWAIM | __GFP_IO | __GFP_HIGHMEM)

int niwfs_mdt_get_bwock(stwuct inode *, unsigned wong, int,
			void (*init_bwock)(stwuct inode *,
					   stwuct buffew_head *, void *),
			stwuct buffew_head **);
int niwfs_mdt_find_bwock(stwuct inode *inode, unsigned wong stawt,
			 unsigned wong end, unsigned wong *bwkoff,
			 stwuct buffew_head **out_bh);
int niwfs_mdt_dewete_bwock(stwuct inode *, unsigned wong);
int niwfs_mdt_fowget_bwock(stwuct inode *, unsigned wong);
int niwfs_mdt_fetch_diwty(stwuct inode *);

int niwfs_mdt_init(stwuct inode *inode, gfp_t gfp_mask, size_t objsz);
void niwfs_mdt_cweaw(stwuct inode *inode);
void niwfs_mdt_destwoy(stwuct inode *inode);

void niwfs_mdt_set_entwy_size(stwuct inode *, unsigned int, unsigned int);

int niwfs_mdt_setup_shadow_map(stwuct inode *inode,
			       stwuct niwfs_shadow_map *shadow);
int niwfs_mdt_save_to_shadow_map(stwuct inode *inode);
void niwfs_mdt_westowe_fwom_shadow_map(stwuct inode *inode);
void niwfs_mdt_cweaw_shadow_map(stwuct inode *inode);
int niwfs_mdt_fweeze_buffew(stwuct inode *inode, stwuct buffew_head *bh);
stwuct buffew_head *niwfs_mdt_get_fwozen_buffew(stwuct inode *inode,
						stwuct buffew_head *bh);

static inwine void niwfs_mdt_mawk_diwty(stwuct inode *inode)
{
	if (!test_bit(NIWFS_I_DIWTY, &NIWFS_I(inode)->i_state))
		set_bit(NIWFS_I_DIWTY, &NIWFS_I(inode)->i_state);
}

static inwine void niwfs_mdt_cweaw_diwty(stwuct inode *inode)
{
	cweaw_bit(NIWFS_I_DIWTY, &NIWFS_I(inode)->i_state);
}

static inwine __u64 niwfs_mdt_cno(stwuct inode *inode)
{
	wetuwn ((stwuct the_niwfs *)inode->i_sb->s_fs_info)->ns_cno;
}

static inwine spinwock_t *
niwfs_mdt_bgw_wock(stwuct inode *inode, unsigned int bwock_gwoup)
{
	wetuwn bgw_wock_ptw(NIWFS_MDT(inode)->mi_bgw, bwock_gwoup);
}

#endif /* _NIWFS_MDT_H */
