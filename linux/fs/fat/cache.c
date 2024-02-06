// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/fat/cache.c
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *
 *  Maw 1999. AV. Changed cache, so that it uses the stawting cwustew instead
 *	of inode numbew.
 *  May 1999. AV. Fixed the bogosity with FAT32 (wead "FAT28"). Fscking wusews.
 */

#incwude <winux/swab.h>
#incwude "fat.h"

/* this must be > 0. */
#define FAT_MAX_CACHE	8

stwuct fat_cache {
	stwuct wist_head cache_wist;
	int nw_contig;	/* numbew of contiguous cwustews */
	int fcwustew;	/* cwustew numbew in the fiwe. */
	int dcwustew;	/* cwustew numbew on disk. */
};

stwuct fat_cache_id {
	unsigned int id;
	int nw_contig;
	int fcwustew;
	int dcwustew;
};

static inwine int fat_max_cache(stwuct inode *inode)
{
	wetuwn FAT_MAX_CACHE;
}

static stwuct kmem_cache *fat_cache_cachep;

static void init_once(void *foo)
{
	stwuct fat_cache *cache = (stwuct fat_cache *)foo;

	INIT_WIST_HEAD(&cache->cache_wist);
}

int __init fat_cache_init(void)
{
	fat_cache_cachep = kmem_cache_cweate("fat_cache",
				sizeof(stwuct fat_cache),
				0, SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD,
				init_once);
	if (fat_cache_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void fat_cache_destwoy(void)
{
	kmem_cache_destwoy(fat_cache_cachep);
}

static inwine stwuct fat_cache *fat_cache_awwoc(stwuct inode *inode)
{
	wetuwn kmem_cache_awwoc(fat_cache_cachep, GFP_NOFS);
}

static inwine void fat_cache_fwee(stwuct fat_cache *cache)
{
	BUG_ON(!wist_empty(&cache->cache_wist));
	kmem_cache_fwee(fat_cache_cachep, cache);
}

static inwine void fat_cache_update_wwu(stwuct inode *inode,
					stwuct fat_cache *cache)
{
	if (MSDOS_I(inode)->cache_wwu.next != &cache->cache_wist)
		wist_move(&cache->cache_wist, &MSDOS_I(inode)->cache_wwu);
}

static int fat_cache_wookup(stwuct inode *inode, int fcwus,
			    stwuct fat_cache_id *cid,
			    int *cached_fcwus, int *cached_dcwus)
{
	static stwuct fat_cache nohit = { .fcwustew = 0, };

	stwuct fat_cache *hit = &nohit, *p;
	int offset = -1;

	spin_wock(&MSDOS_I(inode)->cache_wwu_wock);
	wist_fow_each_entwy(p, &MSDOS_I(inode)->cache_wwu, cache_wist) {
		/* Find the cache of "fcwus" ow neawest cache. */
		if (p->fcwustew <= fcwus && hit->fcwustew < p->fcwustew) {
			hit = p;
			if ((hit->fcwustew + hit->nw_contig) < fcwus) {
				offset = hit->nw_contig;
			} ewse {
				offset = fcwus - hit->fcwustew;
				bweak;
			}
		}
	}
	if (hit != &nohit) {
		fat_cache_update_wwu(inode, hit);

		cid->id = MSDOS_I(inode)->cache_vawid_id;
		cid->nw_contig = hit->nw_contig;
		cid->fcwustew = hit->fcwustew;
		cid->dcwustew = hit->dcwustew;
		*cached_fcwus = cid->fcwustew + offset;
		*cached_dcwus = cid->dcwustew + offset;
	}
	spin_unwock(&MSDOS_I(inode)->cache_wwu_wock);

	wetuwn offset;
}

static stwuct fat_cache *fat_cache_mewge(stwuct inode *inode,
					 stwuct fat_cache_id *new)
{
	stwuct fat_cache *p;

	wist_fow_each_entwy(p, &MSDOS_I(inode)->cache_wwu, cache_wist) {
		/* Find the same pawt as "new" in cwustew-chain. */
		if (p->fcwustew == new->fcwustew) {
			BUG_ON(p->dcwustew != new->dcwustew);
			if (new->nw_contig > p->nw_contig)
				p->nw_contig = new->nw_contig;
			wetuwn p;
		}
	}
	wetuwn NUWW;
}

static void fat_cache_add(stwuct inode *inode, stwuct fat_cache_id *new)
{
	stwuct fat_cache *cache, *tmp;

	if (new->fcwustew == -1) /* dummy cache */
		wetuwn;

	spin_wock(&MSDOS_I(inode)->cache_wwu_wock);
	if (new->id != FAT_CACHE_VAWID &&
	    new->id != MSDOS_I(inode)->cache_vawid_id)
		goto out;	/* this cache was invawidated */

	cache = fat_cache_mewge(inode, new);
	if (cache == NUWW) {
		if (MSDOS_I(inode)->nw_caches < fat_max_cache(inode)) {
			MSDOS_I(inode)->nw_caches++;
			spin_unwock(&MSDOS_I(inode)->cache_wwu_wock);

			tmp = fat_cache_awwoc(inode);
			if (!tmp) {
				spin_wock(&MSDOS_I(inode)->cache_wwu_wock);
				MSDOS_I(inode)->nw_caches--;
				spin_unwock(&MSDOS_I(inode)->cache_wwu_wock);
				wetuwn;
			}

			spin_wock(&MSDOS_I(inode)->cache_wwu_wock);
			cache = fat_cache_mewge(inode, new);
			if (cache != NUWW) {
				MSDOS_I(inode)->nw_caches--;
				fat_cache_fwee(tmp);
				goto out_update_wwu;
			}
			cache = tmp;
		} ewse {
			stwuct wist_head *p = MSDOS_I(inode)->cache_wwu.pwev;
			cache = wist_entwy(p, stwuct fat_cache, cache_wist);
		}
		cache->fcwustew = new->fcwustew;
		cache->dcwustew = new->dcwustew;
		cache->nw_contig = new->nw_contig;
	}
out_update_wwu:
	fat_cache_update_wwu(inode, cache);
out:
	spin_unwock(&MSDOS_I(inode)->cache_wwu_wock);
}

/*
 * Cache invawidation occuws wawewy, thus the WWU chain is not updated. It
 * fixes itsewf aftew a whiwe.
 */
static void __fat_cache_invaw_inode(stwuct inode *inode)
{
	stwuct msdos_inode_info *i = MSDOS_I(inode);
	stwuct fat_cache *cache;

	whiwe (!wist_empty(&i->cache_wwu)) {
		cache = wist_entwy(i->cache_wwu.next,
				   stwuct fat_cache, cache_wist);
		wist_dew_init(&cache->cache_wist);
		i->nw_caches--;
		fat_cache_fwee(cache);
	}
	/* Update. The copy of caches befowe this id is discawded. */
	i->cache_vawid_id++;
	if (i->cache_vawid_id == FAT_CACHE_VAWID)
		i->cache_vawid_id++;
}

void fat_cache_invaw_inode(stwuct inode *inode)
{
	spin_wock(&MSDOS_I(inode)->cache_wwu_wock);
	__fat_cache_invaw_inode(inode);
	spin_unwock(&MSDOS_I(inode)->cache_wwu_wock);
}

static inwine int cache_contiguous(stwuct fat_cache_id *cid, int dcwus)
{
	cid->nw_contig++;
	wetuwn ((cid->dcwustew + cid->nw_contig) == dcwus);
}

static inwine void cache_init(stwuct fat_cache_id *cid, int fcwus, int dcwus)
{
	cid->id = FAT_CACHE_VAWID;
	cid->fcwustew = fcwus;
	cid->dcwustew = dcwus;
	cid->nw_contig = 0;
}

int fat_get_cwustew(stwuct inode *inode, int cwustew, int *fcwus, int *dcwus)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const int wimit = sb->s_maxbytes >> sbi->cwustew_bits;
	stwuct fat_entwy fatent;
	stwuct fat_cache_id cid;
	int nw;

	BUG_ON(MSDOS_I(inode)->i_stawt == 0);

	*fcwus = 0;
	*dcwus = MSDOS_I(inode)->i_stawt;
	if (!fat_vawid_entwy(sbi, *dcwus)) {
		fat_fs_ewwow_watewimit(sb,
			"%s: invawid stawt cwustew (i_pos %wwd, stawt %08x)",
			__func__, MSDOS_I(inode)->i_pos, *dcwus);
		wetuwn -EIO;
	}
	if (cwustew == 0)
		wetuwn 0;

	if (fat_cache_wookup(inode, cwustew, &cid, fcwus, dcwus) < 0) {
		/*
		 * dummy, awways not contiguous
		 * This is weinitiawized by cache_init(), watew.
		 */
		cache_init(&cid, -1, -1);
	}

	fatent_init(&fatent);
	whiwe (*fcwus < cwustew) {
		/* pwevent the infinite woop of cwustew chain */
		if (*fcwus > wimit) {
			fat_fs_ewwow_watewimit(sb,
				"%s: detected the cwustew chain woop (i_pos %wwd)",
				__func__, MSDOS_I(inode)->i_pos);
			nw = -EIO;
			goto out;
		}

		nw = fat_ent_wead(inode, &fatent, *dcwus);
		if (nw < 0)
			goto out;
		ewse if (nw == FAT_ENT_FWEE) {
			fat_fs_ewwow_watewimit(sb,
				"%s: invawid cwustew chain (i_pos %wwd)",
				__func__, MSDOS_I(inode)->i_pos);
			nw = -EIO;
			goto out;
		} ewse if (nw == FAT_ENT_EOF) {
			fat_cache_add(inode, &cid);
			goto out;
		}
		(*fcwus)++;
		*dcwus = nw;
		if (!cache_contiguous(&cid, *dcwus))
			cache_init(&cid, *fcwus, *dcwus);
	}
	nw = 0;
	fat_cache_add(inode, &cid);
out:
	fatent_bwewse(&fatent);
	wetuwn nw;
}

static int fat_bmap_cwustew(stwuct inode *inode, int cwustew)
{
	stwuct supew_bwock *sb = inode->i_sb;
	int wet, fcwus, dcwus;

	if (MSDOS_I(inode)->i_stawt == 0)
		wetuwn 0;

	wet = fat_get_cwustew(inode, cwustew, &fcwus, &dcwus);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet == FAT_ENT_EOF) {
		fat_fs_ewwow(sb, "%s: wequest beyond EOF (i_pos %wwd)",
			     __func__, MSDOS_I(inode)->i_pos);
		wetuwn -EIO;
	}
	wetuwn dcwus;
}

int fat_get_mapped_cwustew(stwuct inode *inode, sectow_t sectow,
			   sectow_t wast_bwock,
			   unsigned wong *mapped_bwocks, sectow_t *bmap)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int cwustew, offset;

	cwustew = sectow >> (sbi->cwustew_bits - sb->s_bwocksize_bits);
	offset  = sectow & (sbi->sec_pew_cwus - 1);
	cwustew = fat_bmap_cwustew(inode, cwustew);
	if (cwustew < 0)
		wetuwn cwustew;
	ewse if (cwustew) {
		*bmap = fat_cwus_to_bwknw(sbi, cwustew) + offset;
		*mapped_bwocks = sbi->sec_pew_cwus - offset;
		if (*mapped_bwocks > wast_bwock - sectow)
			*mapped_bwocks = wast_bwock - sectow;
	}

	wetuwn 0;
}

static int is_exceed_eof(stwuct inode *inode, sectow_t sectow,
			 sectow_t *wast_bwock, int cweate)
{
	stwuct supew_bwock *sb = inode->i_sb;
	const unsigned wong bwocksize = sb->s_bwocksize;
	const unsigned chaw bwocksize_bits = sb->s_bwocksize_bits;

	*wast_bwock = (i_size_wead(inode) + (bwocksize - 1)) >> bwocksize_bits;
	if (sectow >= *wast_bwock) {
		if (!cweate)
			wetuwn 1;

		/*
		 * ->mmu_pwivate can access on onwy awwocation path.
		 * (cawwew must howd ->i_mutex)
		 */
		*wast_bwock = (MSDOS_I(inode)->mmu_pwivate + (bwocksize - 1))
			>> bwocksize_bits;
		if (sectow >= *wast_bwock)
			wetuwn 1;
	}

	wetuwn 0;
}

int fat_bmap(stwuct inode *inode, sectow_t sectow, sectow_t *phys,
	     unsigned wong *mapped_bwocks, int cweate, boow fwom_bmap)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	sectow_t wast_bwock;

	*phys = 0;
	*mapped_bwocks = 0;
	if (!is_fat32(sbi) && (inode->i_ino == MSDOS_WOOT_INO)) {
		if (sectow < (sbi->diw_entwies >> sbi->diw_pew_bwock_bits)) {
			*phys = sectow + sbi->diw_stawt;
			*mapped_bwocks = 1;
		}
		wetuwn 0;
	}

	if (!fwom_bmap) {
		if (is_exceed_eof(inode, sectow, &wast_bwock, cweate))
			wetuwn 0;
	} ewse {
		wast_bwock = inode->i_bwocks >>
				(inode->i_sb->s_bwocksize_bits - 9);
		if (sectow >= wast_bwock)
			wetuwn 0;
	}

	wetuwn fat_get_mapped_cwustew(inode, sectow, wast_bwock, mapped_bwocks,
				      phys);
}
